

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_TriggerIPDUSend
 Syntax           : void Com_TriggerIPDUSend(PduIdType PduId)
 Description      : Service used within the Ipdu-Callout.
                    The I-PDU with the given ID is triggered for transmission
 Parameter        : PduId-> Id of the Tx ipdu
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_TriggerIPDUSend(VAR(PduIdType, AUTOMATIC) PduId)
{
#ifdef COM_TxIPduTimeOut
    Com_TxIpduConstPtrType TxIPduConstPtr;    /* Loca pointer to Tx ipdu static configuration */
#endif
    Com_TxIpduRamPtrType TxIpduRamPtr;          /* Local pointer to the Tx ipdu status structure */

    /* Start: Det */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_TriggerIpduSend, COM_E_UNINIT)

    COM_REPORT_ERROR((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TriggerIpduSend, COM_E_PARAM)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
    * to internal Id which is generated through configuration
    * If PC variant is selected, then no mapping table will be used. */

    PduId = COM_GET_TX_IPDU_ID(PduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

#ifdef COM_TxIPduTimeOut

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);

#endif

    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(PduId))
    {

        /* Check whether the large data pdu flag has been reset */
       if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
       {
        /* All unused flags are reset here */
        Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
        sendIpduFlag_u16.isEventTrig      =  COM_SET;
        /* Call Com_SendIpdu,for the Ipdu, indicating mode change */
        sendIpduFlag_u16.isModeChangd     =  COM_RESET;
        /* For a MIXED Ipdu, as the signal transfer property information is not known.
         * It is assumed, for transmission from this APi,the signal transfer property is Pending */
        /* Time out monitoring cannot be performed for event part */
        /* The timeout handling should happen as usual*/
#ifdef COM_TxIPduTimeOut
        if(TxIPduConstPtr ->Timeout_Fact != 0)
        {
            sendIpduFlag_u16.isTimeoutReq = COM_SET;
        }
#endif
        sendIpduFlag_u16.isTriggerIpduSend = COM_SET;
        Com_SendIpdu((PduIdType)PduId,sendIpduFlag_u16);
       }

    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

