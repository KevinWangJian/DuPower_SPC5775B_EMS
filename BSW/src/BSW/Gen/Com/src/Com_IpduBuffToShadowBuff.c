

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

#ifdef COM_RX_SIGNALGROUP
/***************************************************************************************************
 Function name    : Com_IpduBuffToSecondBuff
 Syntax           : void Com_IpduBuffToSecondBuff(                 Com_RxSigGrpConstPtrType  RxSigGrpConstPtr,
                                                   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)  Buffer,
                                                                       VAR(uint8,AUTOMATIC)  ValidateSigGrp_u8 )
 Description      : Internal function used for copying the signal group contents from IPdu buffer to second buffer
 Parameter        : RxSigGrpConstPtr -> Pointer to Rx SignalGroup static configuration
                  : Buffer -> Address where the data is available
                  : ValidateSigGrp_u8 -> Flag to tell if the group signal value should be copied
                                        with Initial values/received value
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Copy the signal group contents from IPdu buffer to second buffer */
FUNC(void, COM_CODE) Com_IpduBuffToSecondBuff(                 Com_RxSigGrpConstPtrType  RxSigGrpConstPtr,
                                               P2CONST(uint8, AUTOMATIC, COM_APPL_DATA)  Buffer,
                                                                   VAR(uint8,AUTOMATIC)  ValidateSigGrp_u8 )
{
    Com_RxGrpSigConstPtrType  RxGrpSigConstPtr; /* Local pointer to hold the address of Rx GroupSignal static configuration */

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA( RxSigGrpConstPtr->FirstGrpSig_Index );

    if ( ValidateSigGrp_u8 != COM_REPLACE_TO_INIT )
    {
# ifdef COM_RX_SIGNALGROUP_ARRAY
        if ( Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields) )
        {
            Com_RxSigGrpArrayConstPtrType RxSigGrpArrayConstPtr; /* Local pointer to Rx SignalGroup Array configuration */
            uint8                       * RxSigGrpArrayBufRamPtr;

            RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

            RxSigGrpArrayBufRamPtr = &COM_GET_RXSIGGRP_ARRAY_BUFF( RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

            SchM_Enter_Com_RxSigGrpArrayBuff();

            /* Copy GroupSignal's received data into RxSignalGroupArray Buffer from IPdu Buffer.
             * As it is UINT8 array copy, so RxSignalGroupArray Buffer can also hold other
             * interleaved Signal's received data of the same IPdu */
            Com_ByteCopy(       ( uint8 * )( RxSigGrpArrayBufRamPtr ),
                          ( const uint8 * )( Buffer + RxSigGrpArrayConstPtr->FirstByteNo ),
                                           ( RxSigGrpConstPtr->lastByte_u8 - RxSigGrpArrayConstPtr->FirstByteNo ) );

            SchM_Exit_Com_RxSigGrpArrayBuff();
        }
        else
# endif /* #ifdef COM_RX_SIGNALGROUP_ARRAY */
        {
            VAR(uint16_least, AUTOMATIC)  index_ui;
            VAR(uint8, AUTOMATIC)         SigType;

            SchM_Enter_Com_RxGrpSigSecBuff();
            for (index_ui =  (uint16_least)RxSigGrpConstPtr->No_Of_GrpSig; index_ui != (uint16_least)0; index_ui--)
            {
                /* SigType = RxGrpSigConstPtr->rxGrpSigFields.SigType */
                SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);

                if(SigType != (uint8)COM_UINT8_N)
                {
                    VAR(uint8, AUTOMATIC) SigEndianess;

                    SigEndianess = Com_GetValue(RXGRPSIG,_ENDIANESS,RxGrpSigConstPtr->rxGrpSigFields);

/* FC_VariationPoint_START */
# ifdef COM_RXGRPSIG_FLOAT64SUPP
                    if(SigType == COM_FLOAT64)
                    {
                        float64 RxNewVal_f64;
                        /* RxNewVal_f64 = Com_UnPackFloatSignal(RxGrpSigConstPtr->rxGrpSigFields.Endianess,
                         *                                               RxGrpSigConstPtr->Bit_Pos,Buffer); */
                        RxNewVal_f64 = Com_UnPackFloatSignal( SigEndianess, RxGrpSigConstPtr->Bit_Pos, Buffer );

                        COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(RxGrpSigConstPtr->RxGrpSigBuff_Index) = RxNewVal_f64;
                    }
                    else
# endif
/* FC_VariationPoint_END */
                    {
                        VAR(Com_SigMaxType,AUTOMATIC) RxGrpSig_NewVal;

                        RxGrpSig_NewVal = Com_UnpackSignal( SigEndianess, RxGrpSigConstPtr->Bit_Pos,
                                                                          RxGrpSigConstPtr->BitSize, Buffer);

                        /* Sign Extension if the signal is of Negative (Check RxGrpSig_NewVal) this is performed
                         * before hand so that the values are sign extended and properly obtained while reading */
                        if( COM_RESET != ( SigType & (uint8)0x1 ) )
                        {
                            if ((RxGrpSig_NewVal & ((Com_SigMaxType)0x1u << (RxGrpSigConstPtr->BitSize - 1))) != 0u)
                            {
                                RxGrpSig_NewVal = Com_PerformSignExtension(RxGrpSig_NewVal,RxGrpSigConstPtr->BitSize);
                            }
                        }
                        /* Now copy corresponding Group signal buffer with the received value */
                        Com_UpdateRxGroupSignalSecondBuffer(RxGrpSigConstPtr,RxGrpSig_NewVal);
                    }
                }
                else
                {
                    Com_ByteCopy( &COM_GET_SECRXGRPSIGTYPEU8_BUFF(RxGrpSigConstPtr->RxGrpSigBuff_Index),
                                                            (Buffer +(RxGrpSigConstPtr->Bit_Pos >> 3u)),
                                                                              RxGrpSigConstPtr->BitSize );
                }
                RxGrpSigConstPtr++;
            }
            SchM_Exit_Com_RxGrpSigSecBuff();
        }
    }
    else
    {
        /* Discard GroupSignal's received data and place its SignalInitValues in RxSignalGroupArray Buffer */
        Com_InternalSigGrpReplaceToInit( RxSigGrpConstPtr );
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_RX_SIGNALGROUP */

