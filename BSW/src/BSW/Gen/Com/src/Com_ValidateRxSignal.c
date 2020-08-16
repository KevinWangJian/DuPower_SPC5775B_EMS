

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ValidateRxSignal
 Syntax           : boolean Com_ValidateRxSignal(Com_SignalIdType SignalId, Com_SigMaxType * RxNewValPtr)
 Description      : Internal function used for validating Rx signal
 Parameter        : SignalId -> Id of the Signal
                  : RxNewValPtr -> Pointer to New Signal value
 Return value     : boolean
                    COM_TRUE : Copy new signal value in  to signal buffer
                    COM_FALSE : Do not copy new signal value in  to signal buffer
 ***************************************************************************************************/
#if (defined(COM_RxSigInvalid) || defined (COM_RxFilters))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_ValidateRxSignal( VAR(Com_SignalIdType, AUTOMATIC) SignalId,
                                             P2VAR(Com_SigMaxType, AUTOMATIC, COM_APPL_DATA) RxNewValPtr )
{
    Com_RxSigConstPtrType   RxSigConstPtr;    /* Local pointer to Rx Signal static configuration */
    Com_RxSigRamPtrType     RxSigRamPtr;      /* Local poinetr to Rx Signal Status structure     */
    VAR(uint8, AUTOMATIC)   ConstByteValue_u8;
    VAR(boolean, AUTOMATIC) filterVal_b;

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SignalId);
    filterVal_b   = COM_TRUE;

    RxSigRamPtr = &COM_GET_RXSIGNALFLAG(SignalId);
    ConstByteValue_u8 = RxSigConstPtr->rxSignalFields;
    /*Check For the Data Invalid Action and the value*/
#ifdef COM_RxSigInvalid
    {
        VAR(uint8, AUTOMATIC) InvAction;

        InvAction = Com_GetValue(RXSIG,_INVACTION,ConstByteValue_u8);

        /* For Float signals the invalid value is type casted to UNIT32 before comaparing */
        /* Check if the signal has invalid value configured and the newly received value is invalid value */
        /*if (RxSigConstPtr->rxSignalFields.DataInvalidType != (uint8)COM_NONE) &&
         *   (RxSigConstPtr->DataInvalid_Val == *RxNewValPtr))*/
        if ((InvAction != (uint8)COM_NONE) && ((Com_SigMaxType)RxSigConstPtr->DataInvalid_Val == *RxNewValPtr))
        {
            /* if (RxSigConstPtr->rxSignalFields.DataInvalidType == (uint8)COM_REPLACE) */
            if ( InvAction == (uint8)COM_REPLACE )
            {
                VAR(Com_SigMaxType,AUTOMATIC) RxSigVal;

                /* Sign extension is performed on Init value during the below copy */
                /* Read the initial value */
                RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

#ifdef COM_RXSIG_INT64
                /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value (ComSignalInitValue) of a signal
                 * to the size of its ComSignalType.
                 * Init_Val by default will be sign extended only for 32bits. Currently for COM_SINT64 signal types,
                 * if the signal is of Negative, it is required to perform the sign extension till 64bits explicity. */
                if ( Com_GetValue(GEN,_TYPE,RxSigConstPtr->General) == COM_SINT64 )
                {
                    RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
                }
                else
                {
                    /* do nothing for other signal types */
                }
#endif /* #ifdef COM_RXSIG_INT64 */

                /* [SWS_Com_00681] The AUTOSAR COM module shall replace the signals value by its configured
                 * ComSignalInitValue. After the replacement, the normal signal processing like filtering and
                 * notification shall take place as if the ComSignalInitValue would have been received instead of
                 * the ComSignalDataInvalidValue */
                (*RxNewValPtr) = RxSigVal;
            }
            /* If invalid value is not configured ie if flag rxSignalFields.DataInvalidType is COM_NONE, then this
             * check is performed at the beginning itself.
             * Hence the other value will be COM_NOTIFY.
             */
#ifdef COM_RxSigInvalidNotify
            else
            {
                /* [SWS_Com_00680] The AUTOSAR COM module shall notify the RTE via the configured
                 * ComInvalidNotification function. In this case, no other signal processing like filtering or the
                 * normal signal indication shall take place. */
                /* Signal is invalid,and the Invalid Action is configured
                 * hence do not copy new value of signal into signal buffer */
                filterVal_b = COM_FALSE;
                /* If this flag is set, do not call regular signal notification function */
                /* RxSigRamPtr ->rxSigRAMFields.SigNotify_Flag = COM_FALSE */
                /* Call Invalid Notification */
                if(RxSigConstPtr->Sig_DataInvalid_Indication_Cbk != NULL_PTR)
                {
                    RxSigConstPtr->Sig_DataInvalid_Indication_Cbk();
                }
                /* In this case, the signal buffer should contain the previous value of the signal,
                 * leave the signal buffer unchanged
                 */
            }
#endif /* #ifdef COM_RxSigInvalidNotify */
        }
    }
#endif /* #ifdef COM_RxSigInvalid */

#ifdef COM_RxFilters
    {
        VAR(uint8, AUTOMATIC) filterAlgo_u8;

        filterAlgo_u8 = Com_GetValue(RXSIG,_FILTRALG,ConstByteValue_u8);

        /* Proceed only if the signal filter is configured */
        if ( ( COM_FALSE != filterVal_b ) && ( COM_NOTCONFIGURED != filterAlgo_u8 ) )
        {
            /* The signal is valid, hence perform filtering */
            /* Get The Return value of the Filter which need not be returned if signal is invalid */
            /* The last parameter is Information from where the call to Com_Filter happens */
            /* NOTE on last parameter:
            * 1.Currently the values for the parameter callContext_u8 are COM_TRUE/COM_FALSE
            * 2.It is used only for filter ONE_EVERYN */
#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
            /* If the filter algo is COM_MASKED_NEW_DIFFERS_MASKED_OLD and the first valid reception of the signal after
             * the reception deadline monitoring timeout should not be filtered out */
            if(!((Com_GetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields) == COM_TRUE) &&
                 (COM_MASKED_NEW_DIFFERS_MASKED_OLD == filterAlgo_u8)))
            {
#endif /* #if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout)) */
                filterVal_b = Com_Filter((uint32)(*RxNewValPtr), filterAlgo_u8, RxSigConstPtr->Filter_Index, COM_TRUE);
#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout))
            }
            else
            {
                /* Resetting this flag, for further reception of the signal, if Rx deadline monitoring timer elapses,
                 * again this flag shall be set in Com_MainFunctionRx() */
                Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
            }
#endif /* #if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout)) */
        }
    }
#endif /* #ifdef COM_RxFilters   */

    /* If filterVal_b flag is set to false, do not call regular signal notification function */
    Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,filterVal_b);

    return (filterVal_b);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #if (defined(COM_RxSigInvalid) || defined (COM_RxFilters)) */

