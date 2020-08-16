
#include "IpduM.h"
#include "IpduM_Priv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Ipdum_MainFunctionTx
 Syntax           : void Ipdum_MainFunctionTx(void)
 Description      : This function performs the processing of the transmission activities that are not directly handled within the calls from PduR.
 Parameter        : None.
 Return value     : None.
 ***************************************************************************************************/
 FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void)
 {
     /* pointer to SW Timer */
     P2VAR(IpduM_TimerType, AUTOMATIC, IPDUM_APPL_DATA)    TimerPtr;

     /*The variables will only be used if the IpduM TxPathways are configured*/
#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)
     /* Index to MPdu */
     VAR(uint8_least, AUTOMATIC) MpduIdx;

     /* pointer to Tx MPdu configuration data */
     P2CONST(IpduM_TxMPduType, AUTOMATIC, IPDUM_APPL_CONST)    TxMpduPtr;

     /* pointer to Tx RAM data */
     P2VAR(IpduM_TxRamType, AUTOMATIC, IPDUM_APPL_DATA)    TxRamPtr;

     /* Number of Tx MPDUS */
     VAR(uint8_least, AUTOMATIC) NumTxMpdus;

#endif

     /**** End Of Declarations ****/

     /* Start: Det */
     /* Return Type: void */
     IPDUM_REPORT_ERROR((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_MainFunctionTx, IPDUM_E_UNINIT)
     /* End: Det */

     TimerPtr = &IpduM_SwTimer;

    TimerPtr->SwFRTimer += IPDUM_CONFIGURATION_TIMEBASE_TX;


#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)


    NumTxMpdus = (uint8_least)IPDUM_NUM_TX_MPDUS;

    for(MpduIdx = 0; MpduIdx < NumTxMpdus; MpduIdx++)
    {
        TxMpduPtr = &IpduM_TxMPduTable[MpduIdx];
        if((TxMpduPtr->TxConfirmTimeout) > 0u)
        {
            TxRamPtr = &IpduM_TxRamData[MpduIdx];
            if(TxRamPtr->TxState == IPDUM_TX_REQUESTED)
            {
                if((TimerPtr->SwFRTimer - TxRamPtr->TxConfirmTimer) >= TxMpduPtr->TxConfirmTimeout)
                {
                    TxRamPtr->TxState = IPDUM_TX_READY;
                }
            }
        }
    }

#endif


#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)
    {
        /*Index to Container Tx Pdu*/
        VAR(uint16, AUTOMATIC) CrTxPduIdx;

        /* Pointer to Container(Cr) Tx table*/
        P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContainerPduConstPtr_pst;

        /*Pointer to Tx ContainerPduDynamicType table*/
        P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_DATA) TxContainerPduRAMptr_pst;

        VAR(boolean, AUTOMATIC) SendPduFlag_b;

        for (CrTxPduIdx = 0 ; CrTxPduIdx < IPDUM_NUM_CONTAINER_TX_PDUS ;CrTxPduIdx++)
        {
            /* Initialise the SendPdu flag for every TxContainerPdu */
            SendPduFlag_b = FALSE;
            /*Initailise the pointer with Tx container Pdu RAM variables */
            TxContainerPduRAMptr_pst = &IpduM_TxContainerPduDynData[CrTxPduIdx];

            /*Initialise the pointer with Tx Container Pdu table*/
            TxContainerPduConstPtr_pst = &IpduM_TxContainerPdu[CrTxPduIdx];

                /* Check if the TxSendTimeOut is configured for this TxContainerPdu */
                if(TxContainerPduRAMptr_pst->TxSendTimeOutTicks != 0xFFFFu)
                {
                    /*Check if TxSendTimeOut has expired or not*/
                    if(TxContainerPduRAMptr_pst->TxSendTimeOutTicks == 0u)
                    {
                        /*[SWS_IpduM_00190] : TxSendTimeOut has elapsed, so this Pdu can be transmitted in this call of IpduM_MainFunctionTx */
                        SendPduFlag_b = TRUE;
                        /*[SWS_IpduM_00183] : As per this req TT container instance will be incremented only if it is queued.
                         * Only in case of Direct increment the Container instance.*/
                        if(TxContainerPduConstPtr_pst->ContainerTxTriggerMode == IPDUM_DIRECT)
                        {
                            /*Before calling  : means current container cannot accommodate further contained Pdus
                            * 1) Queue size need to be incremented.
                            * 2) Write pointer should be pointing to next queue instance base Address.
                            */
                            TxContainerPduRAMptr_pst->CurrentQueueInstance = ((TxContainerPduRAMptr_pst->CurrentQueueInstance + 1) % (TxContainerPduConstPtr_pst->InstancesInQueue)) ;
                            IpduM_GetCurInstanceBaseAddress(CrTxPduIdx);
                        }
                    }
                    else
                    {
                        /*Decrement the TxSendTimeOutTicks value*/
                        TxContainerPduRAMptr_pst->TxSendTimeOutTicks--;
                    }
                }

                /*Check if TxConfirmationTimeOut is configured with a non zero value */
                if((TxContainerPduConstPtr_pst->TxConfConstTicks) > 0u)
                {
                    /*Check if TxConfirmationTimeOut has expired or not*/
                    if(TxContainerPduRAMptr_pst->TxConfRAMTicks != 0u)
                    {
                        /*Decrement the TxConfRAMTicks value*/
                        TxContainerPduRAMptr_pst->TxConfRAMTicks--;
                    }
                }

                /*[SWS_IpduM_00190] : Check if TxConfirmationTimeOut has expired or not*/
                if(TxContainerPduRAMptr_pst->TxConfRAMTicks == 0u)
                {
                    /*[SWS_IpduM_00198] : If TxConfRAMTicks is elapsed then discard the pending TxConf*/
                    if(TxContainerPduRAMptr_pst->TxConfPtr != NULL_PTR)
                    {
                        (IPDUM_CUR_CNTNR_SDU_LEN(TxContainerPduRAMptr_pst->TxConfPtr,TxContainerPduConstPtr_pst->TxContainerPduLen)) = 0;
                    }
                    /* If there is an outstanding transmission request in the queue and TxConfirmationTimeout has elapsed,
                     * Then new transmit request can be placed */
                    if((TxContainerPduRAMptr_pst->WritePtr != TxContainerPduRAMptr_pst->ReadPtr) && (TxContainerPduRAMptr_pst->TxSendTimeOutTicks == 0xFFFFu))
                    {
                        /* Set the flag for transmission of the queued instance */
                        SendPduFlag_b = TRUE;
                    }

                }

                /* Check if this call to IpduM_MainfunctionTx, leads to any new transmission
				or as per req SWS_IpduM_00195, the previous instance have to be retried in the next mainfunction */
                if((SendPduFlag_b != FALSE) || (TxContainerPduRAMptr_pst->RetransmissionRequired != FALSE))
                {
                    /* Prepare to call PduR_IpduMTransmit() */
                    (void)IpduM_PreparePduRTransmit(CrTxPduIdx);
                }

        }

    }

#endif/* #if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF) */


}


/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

