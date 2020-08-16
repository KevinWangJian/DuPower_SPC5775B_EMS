

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ShadowBuffToIpduBuff
 Syntax           : void Com_ShadowBuffToIpduBuff(Com_SignalGroupIdType SignalGrpId)
 Description      : Internal function used for copying the Signal Group data from the shadow buffer to IPDU buffer
 Parameter        : SignalGrpId -> Id of the SignalGroup
 Return value     : None
 ***************************************************************************************************/
#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ShadowBuffToIpduBuff(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGrpId)
{

    Com_TxIpduConstPtrType         TxIPduConstPtr;
    Com_TxGrpSigConstPtrType       TxGrpSigConstPtr;
    Com_TxSigGrpConstPtrType       TxSigGrpConstPtr;
    VAR(Com_SigMaxType,AUTOMATIC)  TxGrpSig_NewVal;
    VAR(uint16_least, AUTOMATIC)   index_ui;
    VAR(uint8, AUTOMATIC)          SigType_u8;
    VAR(uint8, AUTOMATIC)          ConstByteValue_u8;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGrpId);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr ->FirstGrpSig_Index);

    TxIPduConstPtr   = COM_GET_TX_IPDU_CONSTDATA(TxSigGrpConstPtr->IpduRef);

    /*To avoid misra warning*/
    TxGrpSig_NewVal  = 0;

    for (index_ui = TxSigGrpConstPtr->No_Of_GrpSig; index_ui != 0u; index_ui--)
    {

        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
        /*     Type = TxGrpSigConstPtr->txGrpSigFields.Type; */
        SigType_u8 = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
        if(SigType_u8 != (uint8)COM_UINT8_N)
        {
            VAR(uint8, AUTOMATIC) SigEndianess;

            SigEndianess = Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8);

            /* Now copy the bytes to shadow buffer */
            /* Size of the shadow buffer */
            switch(SigType_u8 >> 1u)
            {
            case 0x00u:
                /* UINT08 signal */
                TxGrpSig_NewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

            case 0x01u:
                /* UINT16 signal */
                TxGrpSig_NewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU16_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

            case 0x02u:
                /* UINT32 signal */
                /* FC_VariationPoint_START */
            case (COM_FLOAT32 >> 1u):
                /* FLOAT32 signal */
                /* FC_VariationPoint_END */
                TxGrpSig_NewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU32_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

#ifdef COM_TXGRPSIG_INT64
            case 0x08u:
                /* UINT64 signal */
                TxGrpSig_NewVal = COM_GET_TXGRPSIGTYPEU64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */

            case 0x03u:
                /*Boolean Signal*/
                TxGrpSig_NewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index);
                break;

            default:
                /**
                 * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal types are
                 * allowed to be configured, hence default case is intentionally left empty.
                 */
                break;

            }
            /* FC_VariationPoint_START */
#ifdef COM_TXGRPSIG_FLOAT64SUPP
            if(SigType_u8 == COM_FLOAT64)
            {
                /* Convert the float value into 32 bit stream and then pack the value */
/*                 Com_PackFloatSignal(TxGrpSigConstPtr->txGrpSigFields.Endianess,TxGrpSigConstPtr->Bit_Pos,
                        COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index), TxIPduConstPtr->BuffPtr); */
                Com_PackFloatSignal(SigEndianess,TxGrpSigConstPtr->Bit_Pos,
                        COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index), TxIPduConstPtr->BuffPtr);
            }
            else
#endif /* #ifdef COM_TXGRPSIG_FLOAT64SUPP */
            {
            /* FC_VariationPoint_END */
                /*Now Update the Ipdu buffer with the value obtained*/
/*                 Com_PackSignal(TxGrpSigConstPtr->txGrpSigFields.Endianess,TxGrpSigConstPtr->Bit_Pos,TxGrpSigConstPtr->BitSize,
                        TxGrpSig_NewVal,TxIPduConstPtr->BuffPtr); */
                Com_PackSignal(SigEndianess,TxGrpSigConstPtr->Bit_Pos,TxGrpSigConstPtr->BitSize,
                        TxGrpSig_NewVal,TxIPduConstPtr->BuffPtr);
                        /* FC_VariationPoint_START */
            }
/* FC_VariationPoint_END */
        }
        else
        {
            /* SigType_u8 == COM_UINT8_N */
            PduLengthType ByteNo_uo;
            /* Find the starting byte position(ByteNo_uo) of ComGroupSignal in the IPDU buffer */
            ByteNo_uo = ( PduLengthType )( TxGrpSigConstPtr->Bit_Pos >> 3 );
            /* Now copy the Group Signal into the SignalDataPtr from Shadow Buffer */
            Com_ByteCopy( ( TxIPduConstPtr->BuffPtr + ByteNo_uo ),
                            &COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index),
                            TxGrpSigConstPtr->BitSize );
        }

        TxGrpSigConstPtr++;
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /*#ifdef COM_TX_SIGNALGROUP*/

