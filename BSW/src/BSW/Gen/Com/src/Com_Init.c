

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/* FC_VariationPoint_START */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_StatusType,COM_VAR)         Com_Uninit_Flag;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
/* FC_VariationPoint_END */

/* Note: Com_Prv_Config_pcst pointer variable should always be under Pre-Compile MemMap section, or else it can lead to
 * RAM corruption */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST) Com_Prv_Config_pcst;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"

/*
 ***************************************************************************************************
 * Prototypes
 ***************************************************************************************************
 */

#if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_CompareVersionInfo(
                                               P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) srcVersionInfo,
                                               P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) destVersionInfo
                                                            );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #if(COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_Init
 Syntax           : void Com_Init(const Com_ConfigType* config)
 Description      : Service for initializing COM module
 Parameter        : config -> Pointer to Com module's configuration data
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_DATA) config)
                                        {

    Com_TxIpduRamPtrType          TxIpduRamPtr; /* Local pointer to hold the address of Tx ipdu status structure */
    Com_RxIpduRamPtrType          RxIPduRamPtr; /* Local pointer to hold the address of Rx ipdu status structure */
    Com_TxIpduConstPtrType        TxIPduConstPtr; /* Local pointer to hold the address of Tx ipdu static configuration */
    Com_RxIpduConstPtrType        RxIPduConstPtr; /* Local pointer to hold the address of Rx ipdu static configuration */
    Com_TxSigConstPtrType         TxSigConstPtr;  /* Local pointer to hold the address of Tx signal static configuration */
    Com_RxSigConstPtrType         RxSigConstPtr;  /* Local pointer to hold the address of Rx signal static configuration */
    VAR(uint16_least, AUTOMATIC)  Ipdu_Size_ui;  /* holds the size of ipdu */
    VAR(uint16_least, AUTOMATIC)  Idx_ui;
    VAR(uint16_least, AUTOMATIC)  Idx_ByteNSig_ui;
    VAR(Com_SigMaxType, AUTOMATIC) TxSigNewVal;

#if defined(COM_TX_SIGNALGROUP) || defined(COM_RX_SIGNALGROUP)
    VAR(uint16_least, AUTOMATIC)  Idx_SigGrp_ui;
#endif

#ifdef COM_TX_SIGNALGROUP
    VAR(uint16_least, AUTOMATIC)  Idx_TxGrpSig_ui;
    Com_TxSigGrpConstPtrType      TxSigGrpConstPtr;
    Com_TxGrpSigConstPtrType      TxGrpSigConstPtr;
    VAR(Com_SigMaxType, AUTOMATIC) TxGrpSig_NewVal;
#endif /* #ifdef COM_TX_SIGNALGROUP */

#ifdef COM_RX_SIGNALGROUP
    Com_RxSigGrpConstPtrType      RxSigGrpConstPtr;       /* Local pointer to Rx GroupSignal configuration */
#endif /* #ifdef COM_RX_SIGNALGROUP */

#if defined (COM_TxSigUpdateBit)|| defined(COM_TxSigGrpUpdateBit)
    VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
#endif

    VAR(uint8, AUTOMATIC)         ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)         Type;
    Com_RxSigRamPtrType           RxSigRamPtr;
    VAR(Com_SigMaxType,AUTOMATIC) RxSigVal;

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    Com_RxGwQueuePtrType          l_RxGwQueuePtr_struc;
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */

#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
{
    /* variable to read version info from Com_GetVersionInfo */
    VAR(Std_VersionInfoType, AUTOMATIC) versionInfo_s;
    /* Read the pre-compile version info */
    Com_GetVersionInfo(&versionInfo_s);

    /* Start: Det */
    COM_REPORT_ERROR((config == NULL_PTR), COMServiceId_Init, COM_E_PARAM_POINTER)
    /* End: Det */

    /* Compare pre-compile & post-build version info */
    if(Com_CompareVersionInfo(&versionInfo_s, config->versionInfo))
    {
        /* versionInfo doesnt match .. Inform application */
        ComAppl_IncompatibleGenerator();

        /* Abort further initialisation ..Com will remain in COM_UNINIT state */
        return;
    }

    /* MR12 RULE 11.5 VIOLATION: On assignment, target pointer will reference to the memory address, and there are
     * no side effects. Hence suppressed the warning. */
    Com_Prv_Config_pcst = (P2CONST(Com_ConfigData_tst,AUTOMATIC,COM_APPL_CONST))config->Com_ConfigData;

}
#else
    (void)config;
#endif
#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    l_RxGwQueuePtr_struc = COM_GET_RXGWQUEUE_S;
    l_RxGwQueuePtr_struc->Com_RxGwQueueRead_ux = 0;
    l_RxGwQueuePtr_struc->Com_RxGwQueueWrite_ux = 0;
    l_RxGwQueuePtr_struc->RxGwQueuePtr = &COM_GET_RXGWQUEUE_AUX(0);
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */

    for (Idx_ui=0;Idx_ui < COM_NUM_ARR_IPDUGRPVECT ;Idx_ui++ )
    {
        Com_IpduGrpVector[Idx_ui] = (uint8)0;
        Com_IpduGrpVector_DM[Idx_ui] = (uint8)0;
    }

/* FC_VariationPoint_START */
#if (COM_COMMON_TX_PERIOD == STD_ON)
    /* Reset common IPDU Tx period feature , if active */
    Com_ReducedPeriod_u16 = 0;
#endif /* COM_COMMON_TX_PERIOD */
/* FC_VariationPoint_END */

#ifdef COM_F_ONEEVERYN
    /* Initialize RAM structure Com_OneEveryN */
    for ( Idx_ui = 0; Idx_ui < COM_GET_NUM_SIG_GRPSIG_WITH_ONE_EVERY_N_FILTER; Idx_ui++ )
    {
        COM_GET_ONEEVERYN( Idx_ui ).Period     = COM_GET_ONEEVERYN_CONST( Idx_ui ).Period;
        COM_GET_ONEEVERYN( Idx_ui ).Offset     = COM_GET_ONEEVERYN_CONST( Idx_ui ).Offset;
        COM_GET_ONEEVERYN( Idx_ui ).Occurrence = COM_GET_ONEEVERYN_CONST( Idx_ui ).Occurrence;
    }
#endif /* #ifdef COM_F_ONEEVERYN */

    /* Start: Reset all Rx Flags */
    RxIPduRamPtr   = &COM_GET_RXPDURAM_S(0);

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(0);

    for(Idx_ui=0; Idx_ui < COM_GET_NUM_RX_IPDU; Idx_ui++)
    {
        COM_GET_IPDUCOUNTER_S(Idx_ui)  = (uint8)0;
        COM_GET_IPDUCOUNTER_DM(Idx_ui) = (uint8)0;
        /*Reset all the Rx Ipdu flags*/
        RxIPduRamPtr ->RxFlags = (uint8)0;
        RxIPduRamPtr ->RxIPduLength = 0;
        /* Here the Ipdu entry is popped out of the queue, The flag is reset to capture the changes in Com_RxIndication */
        Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIPduRamPtr->RxFlags,COM_FALSE);

        /* AUTOSAR COM shall initialize all signals on receiver side with the configured init values */
        RxSigRamPtr = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

        for( Idx_ByteNSig_ui  = (uint16_least)(RxIPduConstPtr->No_Of_Sig_Ref);
             Idx_ByteNSig_ui != (uint16_least)0;
             Idx_ByteNSig_ui-- )
        {
            /* Reset all the flags in the rxSigRAMFields */
            RxSigRamPtr->rxSigRAMFields = (uint8)0;
            /* Get the init value of the signal */
            /* Sign extension to be performed on Init value
             * But when a signed value is assigned to a uint32 variable,it is sign extended by default */
            RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

#if defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP )

            Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif

#ifdef COM_RXSIG_INT64
            /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value (ComSignalInitValue) of a signal
             * to the size of its ComSignalType.
             * Init_Val by default will be sign extended only for 32bits. Currently for COM_SINT64 signal types,
             * if the signal is of Negative, it is required to perform the sign extension till 64bits explicitly. */
            if ( Type == COM_SINT64 )
            {
                RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
            }
            else
            {
                /* do nothing for other signal types */
            }
#endif /* #ifdef COM_RXSIG_INT64 */

/* FC_VariationPoint_START */
#ifdef COM_RXSIG_FLOAT64SUPP

            if(Type == COM_FLOAT64)
            {
                /* For float64 signals, RxSigConstPtr->Init_Val holds index to float array holding init values.*/
                COM_GET_SIGTYPEFLOAT64_BUFF(RxSigConstPtr->SigBuff_Index) = Com_getfloat64InitValue(RxSigVal);
            }
            else
#endif /* #ifdef COM_RXSIG_FLOAT64SUPP */
/* FC_VariationPoint_END */
            {
                Com_UpdateRxSignalBuffer(RxSigConstPtr,RxSigVal);
            }

#ifdef COM_RxFilters
#ifdef COM_F_MASKEDNEWDIFFERSOLD

            ConstByteValue_u8 = RxSigConstPtr->rxSignalFields;
            /*     if(RxSigConstPtr->rxSignalFields.FilterAlgorithm == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD) */
            if(Com_GetValue(RXSIG,_FILTRALG,ConstByteValue_u8) == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
            {
                COM_GET_F_OLDVALUE(RxSigConstPtr->Filter_Index) = (uint32)RxSigVal;
            }
#endif /* #ifdef COM_F_MASKEDNEWDIFFERSOLD */
#endif /* #ifdef COM_RxFilters */
            RxSigRamPtr++;
            RxSigConstPtr++;
        }

#ifdef COM_RX_SIGNALGROUP
        {
             Com_RxSigGrpRamPtrType RxSigGrpRamPtr;    /* Local RAM pointer to SignalGroup RAM structure */
             RxSigGrpRamPtr = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);

            /* AUTOSAR COM shall initialize all Rx-SignalGroup Array(if any) and Secondary GroupSignal Buffers
             * on receiver side with the configured init values */

            RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( RxIPduConstPtr->FirstRxSigGrp_Index );

            for ( Idx_SigGrp_ui  = (uint16_least)RxIPduConstPtr->No_Of_SigGrp_Ref;
                  Idx_SigGrp_ui != (uint16_least)0;
                  Idx_SigGrp_ui-- )
            {
                Com_InternalSigGrpReplaceToInit( RxSigGrpConstPtr );
                /* Reset all the flags in the rxSigGrpRAMFields */
                RxSigGrpRamPtr->rxSigGrpRAMFields = (uint8)0;

                RxSigGrpRamPtr++;
                RxSigGrpConstPtr++;
            }
        }
#endif  /* #ifdef COM_RX_SIGNALGROUP */

        /* As per this requirement there is no need of updating the Rx Shadowbuffer*/
        RxIPduRamPtr++;
        RxIPduConstPtr++;
    }
    /* End: Reset all Rx Falgs */


    /* START: Reset all IPDU Buffer with the padding Bytes */
    /*Update the bytes with Initial Value*/
    TxIpduRamPtr   = &COM_GET_TXPDURAM_S(0);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

    for(Idx_ui=0;Idx_ui<COM_GET_NUM_TX_IPDU;Idx_ui++)
    {
        Ipdu_Size_ui = (uint32)TxIPduConstPtr->Size;
        COM_GET_IPDUCOUNTER_S(Idx_ui + COM_GET_NUM_RX_IPDU) = 0;
        /*Reset all the Tx Flags*/
        TxIpduRamPtr ->Com_TxFlags = (uint16)0;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
        TxIpduRamPtr->Com_DynLength= 0;
#endif
        TxIpduRamPtr->CurrentTxModePtr = TxIPduConstPtr->Com_TMConstPtr;

        /*Update the IPDU buffer with Padding Bytes/Unused Area default*/
        for(Idx_ByteNSig_ui=0;Idx_ByteNSig_ui<Ipdu_Size_ui;Idx_ByteNSig_ui++)
        {
            *((TxIPduConstPtr->BuffPtr) + Idx_ByteNSig_ui) = TxIPduConstPtr->PaddingByte;
        }

        /* Start: Reset all Tx Flags */

        /* Update Com_TxModeState[] to NONE */
        /* TxIpduRamPtr->Com_TransMode.TxModeState = COM_TRUE */
        Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_TRUE);
        /* TxIpduRamPtr->Com_TransMode.LatestTransMode = COM_TXMODE_NONE */
        Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,(uint8)COM_TXMODE_NONE);
/* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
        /* TxIpduRamPtr->Com_TransMode.MixedPhaseShift = COM_FALSE */
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,COM_FALSE); /* Disable MixedPhaseShift by default */
#endif /* #ifdef COM_MIXEDPHASESHIFT */
/* FC_VariationPoint_END */
        /*Reset all other Tx Global variables including Min Delays*/
#ifdef COM_TxIPduTimeOut
        TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif /* #ifdef COM_TxIPduTimeOut */
#if defined(COM_METADATA_SUPPORT)
        /* If IPdu have MetaDataDefault configured */
        if ((NULL_PTR != TxIPduConstPtr->MetaDataPtr) && (Com_GetValue( TXIPDU, _ISMETADATASUPPORTED, TxIPduConstPtr->txIPduFields )))
        {
            /* Add default metadata in position of metadata in Tx buffer */
			Com_ByteCopy(
				   ( P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) )( TxIPduConstPtr->BuffPtr + TxIPduConstPtr->Size ),
				( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )(  &TxIPduConstPtr->MetaDataPtr->MetaDataDefaultValue[0] ),
															   ( TxIPduConstPtr->MetaDataPtr->MetaDataLength ) );
        }
#endif /* #if defined(COM_METADATA_SUPPORT)  */

        TxIpduRamPtr->Com_TMSTrueCounter_u8 = 0;
        TxIpduRamPtr->Com_n = 0;

        TxIpduRamPtr->Com_MinDelayTick = 0; /*Minimum Delay Tick for the Tx IPDU's */

        /* End: Reset all Tx Flags */
        /* AUTOSAR COM shall initialize all signals on sender side with
        the configured init values */
        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

        for(Idx_ByteNSig_ui = TxIPduConstPtr->No_Of_Sig_Ref;Idx_ByteNSig_ui != 0u;Idx_ByteNSig_ui--)
        {
            ConstByteValue_u8 = TxSigConstPtr->General;

            /* Type = TxSigConstPtr->General.Type */
            Type = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

            /* Sign extension to be performed on Init value
             * But when a signed value is assigned to a uint32 variable,it is sign extended by default*/
            TxSigNewVal = (Com_SigMaxType)TxSigConstPtr->Init_Val;

#ifdef COM_TXSIG_INT64
            /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value (ComSignalInitValue) of a signal
             * to the size of its ComSignalType.
             * Currently for COM_SINT64 signal type, ComSignalInitValue is supported for maximum 32bits.
             * If negative values are configured, by default these values will be sign extended only till 32bits.
             * so, for COM_SINT64, it is required to perform the sign extension till 64bits explicitly. */
            if ( Type == COM_SINT64 )
            {
                TxSigNewVal = (Com_SigMaxType)((sint64)((sint32)TxSigNewVal));
            }
            else
            {
                /* do nothing for other signal types */
            }
#endif /* #ifdef COM_TXSIG_INT64 */

            Com_InitializePduBuffWithSignalInitValue( TxIPduConstPtr->BuffPtr,
                                                      TxSigNewVal,
                                                      TxSigConstPtr->Bit_Pos,
                                                      TxSigConstPtr->BitSize, Type,
                                                      Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8)  );

#ifdef COM_TxFilters
#ifdef COM_F_MASKEDNEWDIFFERSOLD

            ConstByteValue_u8 = TxSigConstPtr->txSignalFields;

            /* The old value of the filter is set to Initial value */
            /* if(TxSigConstPtr->txSignalFields.FilterAlgorithm == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD) */
            if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8) == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)
            {
                COM_GET_F_OLDVALUE(TxSigConstPtr->Filter_Index) = (uint32)TxSigNewVal;
            }
#endif
#endif /* #ifdef COM_TxFilters */

#ifdef COM_SigTriggeredOnChange
            ConstByteValue_u8 = TxSigConstPtr->txSignalFields;
            /* if(TxSigConstPtr->txSignalFields.TransProp == (uint8)COM_TRIGGERED_ON_CHANGE) */
            if(Com_GetValue(TXSIG,_TP,ConstByteValue_u8) == (uint8)COM_TRIGGERED_ON_CHANGE)
            {
                COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxSigNewVal;
            }
#endif

#ifdef COM_TxSigUpdateBit
            /* Only the first byte of txIPduFields is needed */
            ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit != (uint8)COM_CLRUPDATEBIT_NONE)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE)
            {

                /* Clear Update bits*/
                /* if(TxSigConstPtr->General.UpdBitConf != COM_FALSE) */
                if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
                {
                    /*Find the Byte No*/
                    ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Update_Bit_Pos>>3u);

                    /*Update the Bit in IPDU Buffer*/
                    Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigConstPtr->Update_Bit_Pos, ByteNo_u8)
                }
            }

#endif/*COM_TxSigUpdateBit*/
            TxSigConstPtr++;
        }

#ifdef COM_TX_SIGNALGROUP

        Idx_ByteNSig_ui = (uint16_least)TxIPduConstPtr->FirstTxSigGrp_Index +
                          (uint16_least)TxIPduConstPtr->No_Of_SigGrp_Ref;

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

        for(Idx_SigGrp_ui=(uint16_least)TxIPduConstPtr->FirstTxSigGrp_Index; Idx_SigGrp_ui < Idx_ByteNSig_ui;
                                                                             Idx_SigGrp_ui++ )
        {
#ifdef COM_TX_SIGNALGROUP_ARRAY
            boolean               ConstIsSigGrpOfArrayType_b;
            ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

#ifdef COM_SIGNALGROUPGATEWAY
            /* TxSigGrpRamPtr ->txSigGrpRAMFields.IsGwUpdated = COM_FALSE */
            Com_SetRamValue(TXSIGGRP,_ISGWUPDTD,COM_GET_TXSIGGRPFLAG(Idx_SigGrp_ui).txSigGrpRAMFields, COM_FALSE);
#endif /* #ifdef COM_SIGNALGROUPGATEWAY */

            TxGrpSigConstPtr= COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr-> FirstGrpSig_Index);

            for( Idx_TxGrpSig_ui  = (uint16_least)TxSigGrpConstPtr->No_Of_GrpSig; Idx_TxGrpSig_ui != (uint16_least)0;
                                                                                  Idx_TxGrpSig_ui-- )
            {
                /* Shadowbuffer of a signal Group(group signal buffers) on sender-side shall be initialized*/
                /* Sign extension to be performed on Init valu, when a signed value is assigned to a uint32 variable,
                 * it is sign extended by default*/
                TxGrpSig_NewVal = (Com_SigMaxType)TxGrpSigConstPtr->Init_Val;

                /* Get the value of the ComSignaltype bit field */
                ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
                /* Type = TxGrpSigConstPtr->txGrpSigFields.Type */
                Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);

#ifdef COM_TXGRPSIG_INT64
                /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value (ComSignalInitValue) of a
                 * signal to the size of its ComSignalType.
                 * Currently for COM_SINT64 signal type, ComSignalInitValue is supported for maximum 32bits.
                 * If negative values are configured, by default these values will be sign extended only till 32bits.
                 * so, for COM_SINT64, it is required to perform the sign extension till 64bits explicitly. */
                if ( Type == COM_SINT64 )
                {
                    TxGrpSig_NewVal = (Com_SigMaxType)((sint64)((sint32)TxGrpSig_NewVal));
                }
                else
                {
                    /* do nothing for other signal types */
                }
#endif /* #ifdef COM_TXGRPSIG_INT64 */

#ifdef COM_TX_SIGNALGROUP_ARRAY
                if ( ConstIsSigGrpOfArrayType_b )
                {
                    Com_InitializePduBuffWithSignalInitValue( TxIPduConstPtr->BuffPtr,
                                                              TxGrpSig_NewVal,
                                                              TxGrpSigConstPtr->Bit_Pos,
                                                              TxGrpSigConstPtr->BitSize, Type,
                                                              Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8) );
                }
                else
#endif
                {
                    if(Type != (uint8)COM_UINT8_N)
                    {
                        switch(Type)
                        {
                        case COM_UINT8:
                        case COM_BOOLEAN:
                        case COM_SINT8:COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint8)TxGrpSig_NewVal;
                        break;
                        case COM_UINT16:
                        case COM_SINT16:COM_GET_TXGRPSIGTYPEU16_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint16)TxGrpSig_NewVal;
                        break;
                        case COM_UINT32:
                        /* FC_VariationPoint_START */
                        /* Before packing the signal value, the float signal init value is converted
                         * into Integer value as per IEEE754 format in OAW */
                        case COM_FLOAT32:
                        /* FC_VariationPoint_END */
                        case COM_SINT32:COM_GET_TXGRPSIGTYPEU32_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint32)TxGrpSig_NewVal;
                        break;
#ifdef COM_TXGRPSIG_INT64
                        case COM_UINT64:
                        case COM_SINT64:
                            COM_GET_TXGRPSIGTYPEU64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index) = TxGrpSig_NewVal;
                        break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */
                        /* FC_VariationPoint_START */
#ifdef COM_TXGRPSIG_FLOAT64SUPP
                        case COM_FLOAT64:
                        /* FLOAT64 signal */
                        /* For float64 signals, TxGrpSig_NewVal holds index to float array holding init values.*/
                            COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index) = Com_getfloat64InitValue(TxGrpSig_NewVal);
                        break;
#endif /* #ifdef COM_TXGRPSIG_FLOAT64SUPP */
                        /* FC_VariationPoint_END */
                        default:
                            /**
                             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal
                             * types are allowed to be configured, hence default case is intentionally left empty.
                             */
                            break;
                        }
                    }
                    else /* UINT8_N signal */
                    {
                        Com_ByteCopyInit(&COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index),
                                         (uint32)TxGrpSig_NewVal,(uint32)TxGrpSigConstPtr->BitSize);
                    }
                }

                /*COM_230: The old value of the filter is set to Initial value */
#ifdef COM_TxFilters
#ifdef COM_F_MASKEDNEWDIFFERSOLD
                if(TxGrpSigConstPtr->Filter_Algo == (uint8)COM_MASKED_NEW_DIFFERS_MASKED_OLD)

                {
                    COM_GET_F_OLDVALUE(TxGrpSigConstPtr->Filter_Index) = (uint32)TxGrpSig_NewVal;
                }

#endif
#endif /* #ifdef COM_TxFilters */
#ifdef COM_SigGrpTriggeredOnChange
                /* if(TxGrpSigConstPtr->txGrpSigFields.TransProp != (uint8)COM_FALSE) */
                if(Com_GetValue(TXGRPSIG,_TP,ConstByteValue_u8))
                {
                    COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) =
                                                                             (Com_OldValTrigOnChngType)TxGrpSig_NewVal;
                }
#endif
                TxGrpSigConstPtr++;
            }
#ifdef COM_SigGrpTriggeredOnChange
            /* if(TxSigGrpConstPtr->txSignalGrpFields.TransProp == (uint8)COM_TRIGGERED_ON_CHANGE) */
            if(Com_GetValue(TXSIGGRP,_TP,TxSigGrpConstPtr->txSignalGrpFields) == (uint8)COM_TRIGGERED_ON_CHANGE)
            {
                /* COM_GET_TXSIGGRPFLAG(Idx_SigGrp_ui).txSigGrpRAMFields.TrigOnChange = COM_FALSE */
                Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,COM_GET_TXSIGGRPFLAG(Idx_SigGrp_ui).txSigGrpRAMFields,COM_FALSE);
            }
#endif
#ifdef COM_TX_SIGNALGROUP_ARRAY
            if ( ConstIsSigGrpOfArrayType_b != COM_TRUE )
#endif
            {
                /*Copy the data which is present in Shadow buffer to IPDU buffer*/
                Com_ShadowBuffToIpduBuff((Com_SignalGroupIdType)Idx_SigGrp_ui);
            }
#ifdef COM_TX_SIGNALGROUP_ARRAY
            else
            {
                /* GroupSignal's SignalInitValues are already updated into the IPduBuffer
                 * in Com_InitializePduBuffWithSignalInitValue() */
            }
#endif

#ifdef COM_TxSigGrpUpdateBit
            /* Only the first byte of txIPduFields is needed */
            ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit != (uint8)COM_CLRUPDATEBIT_NONE)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) != (uint16)COM_CLRUPDATEBIT_NONE)
            {

                /* Clear Update bits*/
                /* if(TxSigGrpConstPtr->txSignalGrpFields.UpdBitConf != COM_FALSE) */
                if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
                {
                    /*Find the Byte No*/
                    ByteNo_u8 = (PduLengthType)(TxSigGrpConstPtr ->Update_Bit_Pos>>3u);

                    /*Update the Bit in IPDU Buffer*/
                    Com_ClearUpdateBitValue(TxIPduConstPtr, TxSigGrpConstPtr->Update_Bit_Pos, ByteNo_u8)
                }
            }
#endif  /*COM_TxSigGrpUpdateBit*/

            TxSigGrpConstPtr++;
        }

#endif  /*COM_TX_SIGNALGROUP*/

        TxIPduConstPtr++;
        TxIpduRamPtr++;

    } /*end of for(Idx_ui=0;Idx_ui<COM_GET_NUM_TX_IPDU;Idx_ui++)*/

    /* END: Reset all IPDU Buffer with the padding Bytes */
/* FC_VariationPoint_START */
#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
    /* Initial value for all the TxIpdus should be set for IpduControl Via Rba_Nds_EcuVariant feature */
    for (Idx_ui = 0; Idx_ui < COM_NUM_ARR_TXIPDUCONTROLVECTOR; Idx_ui++)
    {
        Com_TxIpduControlVector[Idx_ui] = (uint8)0xFFu;
    }
#endif /* #ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
    /* Initial value for all the RxIpdus should be set for IpduControl Via Rba_Nds_EcuVariant feature */
    for (Idx_ui = 0; Idx_ui < COM_NUM_ARR_RXIPDUCONTROLVECTOR; Idx_ui++)
    {
        Com_RxIpduControlVector[Idx_ui] = (uint8)0xFFu;
    }
#endif /* #ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
/* FC_VariationPoint_END */

    /* Reset the UNINIT flag */
    Com_Uninit_Flag = COM_INIT;

                                        }
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 ***************************************************************************************************
 * Com_CompareVersionInfo - compare version info structures ie of type Std_VersionInfoType
 *
 * compare version info structures ie of type Std_VersionInfoType.
 *
 * \param   srcVersionInfo      pointer to first Std_VersionInfoType structure
 * \param   destVersionInfo     pointer to second Std_VersionInfoType structure
 * \return  stEqual_u32         result of comparison
 * \retval  0                   memory area contents are equal
 * \retval  1                   memory area contents differ
  ***************************************************************************************************
 */
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
LOCAL_INLINE FUNC(boolean, COM_CODE) Com_CompareVersionInfo(
                                                                P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) srcVersionInfo,
                                                                P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST) destVersionInfo
                                                              )
{
    VAR(boolean, AUTOMATIC)   stEqual_b;
    stEqual_b = COM_TRUE;
    if ((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
        (srcVersionInfo->moduleID == destVersionInfo->moduleID) &&
        (srcVersionInfo->sw_major_version == destVersionInfo->sw_major_version) &&
        (srcVersionInfo->sw_minor_version == destVersionInfo->sw_minor_version) &&
        (srcVersionInfo->sw_patch_version == destVersionInfo->sw_patch_version)
    )
    {
        stEqual_b = COM_FALSE;
    }
    return stEqual_b;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */


