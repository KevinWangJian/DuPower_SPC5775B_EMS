

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ReceiveSignalGroup
 Syntax           : uint8 Com_ReceiveSignalGroup(Com_SignalGroupIdType    SignalGroupId)
 Description      : Service used to copy the SignalGroup content from IpduBuffer to Shadowbuffer
 Parameter        : SignalGroupId -> Id of the SignalGroup
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
#ifdef COM_RX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
    Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
    Com_RxGrpSigConstPtrType RxGrpSigConstPtr; /* Local pointer to hold the address of the Rx GroupSignal static configuration */
    VAR(uint16_least, AUTOMATIC) index_ui;
    VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC) rxGrpSignalBuffIndex;
    VAR(uint8, AUTOMATIC) Type; /* Type of the signal */
    VAR(uint8, AUTOMATIC) Status_u8;

    /* Start: Det */

    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_ReceiveSignalGroup, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalGroupId >= COM_GET_NUM_RX_SIGNALGRP), COMServiceId_ReceiveSignalGroup, COM_E_PARAM)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    SignalGroupId = COM_GET_RXSIGNALGRP_ID(SignalGroupId);

    Status_u8 = E_OK;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SignalGroupId);

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

    /* If IPDU Group is Stopped */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(!(COM_CheckRxIPduStatus(RxSigGrpConstPtr->IpduRef)))
    {
        Status_u8 = COM_SERVICE_NOT_AVAILABLE;
    }

    /* Lock the interrupts because second buffer could be updated by interrupt
     * in function Com_RxIndication()
     */
    /* The complete copy operation from the second buffer to primary buffer should be
     * interrupt safe,this is because, the whole signal group should be copied atomically
     * As the lock is around the loop for all the group signals the Interrupt locking time can vary depending on configuration
     */
    SchM_Enter_Com_RxGrpSigSecBuff();
    for (index_ui =  RxSigGrpConstPtr->No_Of_GrpSig; index_ui != 0u; index_ui--)
    {
        /* Type = RxGrpSigConstPtr->rxGrpSigFields.Type */
        Type =  Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
        rxGrpSignalBuffIndex = RxGrpSigConstPtr->RxGrpSigBuff_Index;

        switch(Type >> 1u)
        {
        case 0x00u: /* COM_UINT8, COM_SINT8 */
        case 0x03u: /* COM_BOOLEAN          */
        {
            COM_GET_RXGRPSIGTYPEUINT8_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxGrpSignalBuffIndex);
        }
            break;

        case 0x01u: /* COM_UINT16, COM_SINT16 */
        {
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            COM_GET_RXGRPSIGTYPEUINT16_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU16_BUFF(rxGrpSignalBuffIndex);
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
        }
            break;

        case 0x02u: /* COM_UINT32, COM_SINT32 */
        {
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            COM_GET_RXGRPSIGTYPEUINT32_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU32_BUFF(rxGrpSignalBuffIndex);
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
        }
            break;
/* FC_VariationPoint_START */
#ifdef COM_GRPSIGFLOAT32SUPP
        case (COM_FLOAT32 >> 1u): /* FLOAT32 signal */
        {
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            COM_GET_RXGRPSIGTYPEUINT32_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU32_BUFF(rxGrpSignalBuffIndex);
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
        }
            break;
#endif

#ifdef COM_RXGRPSIG_INT64
        case 0x08u: /* COM_UINT64, COM_SINT64 */
        {
            SchM_Enter_Com_RxGrpSigBuff();
            COM_GET_RXGRPSIGTYPEUINT64_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEU64_BUFF(rxGrpSignalBuffIndex);
            SchM_Exit_Com_RxGrpSigBuff();
        }
            break;
#endif /* #ifdef COM_RXGRPSIG_INT64 */

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        case (COM_FLOAT64 >> 1u):
        {
            /* FLOAT64 signal */
            SchM_Enter_Com_RxGrpSigBuff();
            COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(rxGrpSignalBuffIndex) = COM_GET_SECRXGRPSIGTYPEFLOAT64_BUFF(rxGrpSignalBuffIndex);
            SchM_Exit_Com_RxGrpSigBuff();
        }
            break;
#endif
/* FC_VariationPoint_END */

        case 0x04u:
        {
            /* UINT8_N signal */
            SchM_Enter_Com_RxGrpSigBuff();
            Com_ByteCopy(&COM_GET_RXGRPSIGTYPEUINT8_BUFF(rxGrpSignalBuffIndex),
                         &COM_GET_SECRXGRPSIGTYPEU8_BUFF(rxGrpSignalBuffIndex),RxGrpSigConstPtr->BitSize);
            SchM_Exit_Com_RxGrpSigBuff();
        }
            break;

        default:
            /**
             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal types are allowed
             * to be configured, hence default case is intentionally left empty.
             */
            break;
        }

        RxGrpSigConstPtr++;
    }
    /* [SWS_Com_00461] The AUTOSAR COM module shall always copy the last known data, or the ComSignalInitValue(s)
     * if not yet written, of the I-PDU to the shadow buffer by a call to Com_ReceiveSignalGroup()
     * even if the I-PDU is stopped and COM_SERVICE_NOT_AVAILABLE is returned. */
    SchM_Exit_Com_RxGrpSigSecBuff();

    return (Status_u8);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

