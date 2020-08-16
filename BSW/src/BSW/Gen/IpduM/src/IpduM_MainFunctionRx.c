
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
 Function name    : Ipdum_MainFunctionRx
 Syntax           : void Ipdum_MainFunctionRx(void)
 Description      : This function performs the processing of the reception activities that are not directly handled within the calls from PduR.
 Parameter        : None.
 Return value     : None.
 ***************************************************************************************************/
 FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void)
 {
     /* pointer to SW Timer */
     P2VAR(IpduM_TimerType, AUTOMATIC, IPDUM_APPL_DATA)    TimerPtr;

     /* Start: Det */
     /* Return Type: void */
     IPDUM_REPORT_ERROR((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_MainFunctionRx, IPDUM_E_UNINIT)
     /* End: Det */

     TimerPtr = &IpduM_SwTimer;

     TimerPtr->SwFRTimer += IPDUM_CONFIGURATION_TIMEBASE_RX;

#if (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF))
        {
            /*Index to Container Rx Pdu*/
            VAR(uint16, AUTOMATIC) CrRxPduIdx;

            /* Pointer to Container(Cr) Rx table*/
            P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst;

            /*Pointer to Rx ContainerPduDynamicType table*/
            P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_DATA) RxContainerPduRAMPtr_pst;

            for (CrRxPduIdx = 0 ; CrRxPduIdx < IPDUM_NUM_CONTAINER_RX_PDUS ; CrRxPduIdx++)
            {
                /*Initailise the pointer with Rx container Pdu RAM variables */
                RxContainerPduRAMPtr_pst = &IpduM_RxContainerPduDynData[CrRxPduIdx];

                /*Initialise the pointer with Rx Container Pdu table*/
                RxContainerPduConstPtr_pst = &IpduM_RxContainerPdu[CrRxPduIdx];

                /*Check if the PduProcessing is deferred */
                if(RxContainerPduConstPtr_pst->PduProcessing == (boolean)IPDUM_PROCESSING_DEFERRED)
                {
                    PduInfoType pduInfoPtr_l;

                    /* Loop through all the instances of the container queue which have container pdu's to be processed */
                    while(IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr,RxContainerPduConstPtr_pst->RxContainerPduLen) > 0)
                    {
                        


                        /*Copy the contents from the buffer */
                        pduInfoPtr_l.SduDataPtr = RxContainerPduRAMPtr_pst->ReadPtr;
                        pduInfoPtr_l.SduLength =  IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr , RxContainerPduConstPtr_pst->RxContainerPduLen);

                        /*Process of deferred Rx Pdu*/
                        IpduM_ProcessRxContainerPdu(RxContainerPduConstPtr_pst->ContainerRxPduId, &pduInfoPtr_l,RxContainerPduConstPtr_pst);

                        /* Reset current container RAM pdu length after processing this container Pdu */
                        IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr,RxContainerPduConstPtr_pst->RxContainerPduLen) = 0;

                        /* Check if the queue is configured */
                        if(RxContainerPduConstPtr_pst->InstancesInQueue > 1)
                          {
                            /* Update the read pointer  */
                            RxContainerPduRAMPtr_pst->ReadPtr += (RxContainerPduConstPtr_pst->RxContainerPduLen + 1u);
                            /*At anytime if the readPtr reaches last address in the buffer then reset it to starting address*/
                            if(RxContainerPduRAMPtr_pst->ReadPtr == ((RxContainerPduConstPtr_pst->BufferPtr) +( RxContainerPduConstPtr_pst->RxContainerPduLen *
                               RxContainerPduConstPtr_pst->InstancesInQueue) + (RxContainerPduConstPtr_pst->InstancesInQueue)))
                                {
                                  /* Update the read pointer  */
                                  RxContainerPduRAMPtr_pst->ReadPtr = RxContainerPduConstPtr_pst->BufferPtr;
                                }
                          }
                    } /* while(IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr,RxContainerPduConstPtr_pst->RxContainerPduLen) > 0) */

                }/* if( (RxContainerPduConstPtr_pst->PduProcessing == IPDUM_PROCESSING_DEFERRED) && (IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr,RxContainerPduConstPtr_pst->RxContainerPduLen) != 0)) */

            }
        }

#endif /* #if defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF) */

}


/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

