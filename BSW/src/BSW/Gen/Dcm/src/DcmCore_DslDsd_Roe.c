

#include "DcmCore_DslDsd_Inf.h"


#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Pointer to hold the active ROE conf structure */
P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoeRdpi_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_RoeRdpiType1TimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_RoeType2TimerStatus_uchr ; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
static VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) s_dataNrc_u8;
static VAR (Dcm_OpStatusType, DCM_VAR) s_RoeOpstatus_u8;
#endif
VAR (uint8, DCM_VAR) DcmRoeQueueIndex_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DsldDsdStatesType_ten,DCM_VAR) Dcm_DsdRoe2State_en;      /* ROE2 DSD state */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Roe2MesContext_st;        /* ROE2 message context table */
VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Roe2ResponseType_en;    /* ROE2 response type */
VAR(PduInfoType,DCM_VAR) Dcm_DsldRoe2PduInfo_st;             /* ROE2 PDU info structure*/
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR) Dcm_DsldSrvIndex_u8;                     /* ROE2 Index to service in table*/
VAR(Std_ReturnType,DCM_VAR) Dcm_Roe2TxResult_u8;              /* ROE2 Tx confirmation result */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe2_pcst; /* Ptr to Roe info structure */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/**
 **************************************************************************************************
 * Dcm_GetRoeProtValidity : This function is used only to init the circular queue
 *                                      to default value 0xFF
 *
 * \param           Void
 *
 *
 *
 * \retval         void
 *
 * \seealso
 *
 **************************************************************************************************
 **/
static FUNC(Dcm_StatusType,DCM_CODE) Dcm_GetRoeProtValidity(VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) idxProtocol_u8);
static FUNC(Dcm_StatusType,DCM_CODE) Dcm_GetRoeProtValidity(VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) idxProtocol_u8)
        {
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;

    /*Initialize the local variables*/
    *idxProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8;

    /* Check if the protocol corresponding to the RxPduId passed supports ROE */
    if(Dcm_DsldProtocol_pcst[*idxProtocol_u8].roe_info_pcs != NULL_PTR)
    {
        dataReturnValue_u8   = E_OK;
    }
    /* RxPduId passed by application is owned by protocol that does not support ROE */
    else
    {
        dataReturnValue_u8   = DCM_E_ROE_NOT_ACCEPTED;
    }

    return dataReturnValue_u8;
        }


/**
 **************************************************************************************************
 * Dcm_UpdateROEQueue:
 * This function will be invoked incase any of the event needs to be queued and postpone the processing
 * since DCM is busy currently.
 *
 * \parameters           RoeEventId
 * \return value         void
 *
 **************************************************************************************************
 */
static FUNC(Dcm_StatusType,DCM_CODE) Dcm_UpdateROEQueue( uint8 RoeEventId , PduIdType RxPdu);
static FUNC(Dcm_StatusType,DCM_CODE) Dcm_UpdateROEQueue( uint8 RoeEventId,  PduIdType RxPdu)
                                                                        {
    VAR(uint8,AUTOMATIC) index_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    dataReturnValue_u8=DCM_E_ROE_NOT_ACCEPTED;
    for(index_u8=0;index_u8<DCM_MAX_SETUPROEEVENTS;index_u8++)
    {
        if(Dcm_DcmDspEventQueue[index_u8].EventId_u8 == RoeEventId)
        {
            Dcm_DcmDspEventQueue[index_u8].Is_Queued   = TRUE;
            Dcm_DcmDspEventQueue[index_u8].RxPduId_u8  = RxPdu;
            dataReturnValue_u8 = DCM_E_OK;
            break;

        }

    }

    return  dataReturnValue_u8;

                                                                        }
/**
 **************************************************************************************************
 * Dcm_ResponseOnOneEvent : Function called by the ROE service whenever the event occurred.
 *                          This function is not re-entrant function and it not called in other than
 *                          Dcm_MainFunction() task.
 *
 * \param          Dcm_MsgType MsgPtr :    Pointer to buffer which contains the request
 *                 Dcm_MsgLenType MsgLen : Length of the request
 *                 PduIdType DcmRxPduId  : Rx PDU id on which ROE request is received.
 *
 * \retval         DCM_E_OK: ResponseOnOneEvent request is accepted by DCM ,
 *                 DCM_E_ROE_NOT_ACCEPTED: ResponseOnOneEvent request is not accepted by DCM
 * \seealso
 *
 **************************************************************************************************
 **/

FUNC(Dcm_StatusType,DCM_CODE) Dcm_ResponseOnOneEvent( CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
        VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
        VAR(uint16,AUTOMATIC) TesterSrcAddr
)
{

    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(PduIdType,AUTOMATIC) dcmRxPduId_u8;
    VAR(uint8,AUTOMATIC) idxIndex_u8;
    VAR(boolean,AUTOMATIC) dataStartProtocol_b;
    VAR(uint16_least,AUTOMATIC) idxIndex_qu16;
    VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8;
    VAR(Dcm_MsgType,AUTOMATIC) adrDest_pu8;
    VAR(boolean,AUTOMATIC) roeReqAccepted_b;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
#endif

#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_ROE_QUEUE_ENABLED != DCM_CFG_OFF))
    VAR(uint8,AUTOMATIC) idxTxQueue_u8;     /* Local variable for Queue Index */
    VAR(uint8,AUTOMATIC) idxTxResponse_u8;  /* Local variable for Response Index */
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) nrService_u8;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST)  adrSrvTable_pcst;
#endif
    /* Copy the buffer pointer */
    adrDest_pu8 = MsgPtr;
    /*Initialize the data start protocol flag to value False*/
    dataStartProtocol_b = FALSE;
    idxProtocol_u8 = 0x0;
    adrSrc_pu8 = NULL_PTR;
    /* Initialize the flag to reject ROE event during initialization */

    roeReqAccepted_b = FALSE;

    /* Initialize the value to ROE not accepted */
    dataReturnValue_u8 = DCM_E_ROE_NOT_ACCEPTED;

    for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RX_PDUID;idxIndex_u8++)
    {
        if(Dcm_Dsld_RoeRxToTestSrcMappingTable[idxIndex_u8].testsrcaddr_u16 == TesterSrcAddr)
        {
            break;
        }

    }
    if(idxIndex_u8<DCM_CFG_NUM_RX_PDUID)
    {
    /*Copy the RxPduID corresponding to the tester source address */
    dcmRxPduId_u8 =Dcm_Dsld_RoeRxToTestSrcMappingTable[idxIndex_u8].rxpduid_num_u8;

    /* Check if Dcm is initialized and ready to accept the the request */
    if((Dcm_isInitialised_b!=FALSE) && (Dcm_acceptRequests_b !=FALSE))
    {
        /* Check for validity of RxPdu before accepting for processing */
        if((dcmRxPduId_u8 < DCM_CFG_NUM_RX_PDUID)&&(adrDest_pu8 != NULL_PTR))
        {   /* Update the local variables */
            dataReturnValue_u8 = Dcm_GetRoeProtValidity(dcmRxPduId_u8, &idxProtocol_u8);
        }

        /* Protocols buffer should be greater than or equal to request length and check if the protocol is available
        in the current active config set*/
        if((dataReturnValue_u8 == DCM_E_OK) &&
                (DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dcmRxPduId_u8]].channel_idx_u8)) &&
                (MsgLen <= Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs->txbuffer_length_u32)

        )
        {
            adrSrc_pu8        = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs->txbuffer_ptr;
            /* Lock required here to maintain consistency within Dcm_DsldGlobal_st structure */
            SchM_Enter_Dcm_Global_NoNest();
            /* check whether any protocol is active in DCM */
            /*Check if Dsl state is ready for receving the request*/
            if((Dcm_DsldGlobal_st.flgCommActive_b == FALSE)&&(Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                    &&      \
                    ((Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL_RECEIVING) && (Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL))
#endif
            )
            {
                /* Activate the protocol */
                /* Update the global variables  */
                Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
                Dcm_DsldGlobal_st.nrActiveConn_u8      = Dcm_DsldRxTable_pcu8[dcmRxPduId_u8];
                Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldProtocol_pcst[idxProtocol_u8].sid_tableid_u8;
                /*Initialize the flag for Comm Active protocol*/
                Dcm_DsldGlobal_st.flgCommActive_b       = TRUE;
                /*Initialize the data start protocol to get protocol id*/
                dataStartProtocol_b = TRUE;
            }/*Dcm is busy, queue the DTCs*/
            SchM_Exit_Dcm_Global_NoNest();
            /*Check if the data protocol id is set to get the protocol id*/
            if(dataStartProtocol_b != FALSE)
            {
                /* Start the application function */
                if(Dcm_StartProtocol(Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8)== E_OK )
                {
                    /* If cooperative scheduler is enabled, shift the service initializations to cooperative scheduler based on
                       individual service configuration */
                    DCM_DSLD_COOPSCHEDULER_SHIFTINI(Dcm_DsldGlobal_st.datActiveSrvtable_u8)
                                                                                            /* Call the Initialisation function of service */
                                                                                            Dcm_DsldCallServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

                    /* Get the active service table of the protocol */
                    Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
                }
                else
                {
                    /* reject the request because unable to start protocol */
                    /* Report development error "DCM_E_PROTOCOL_NOT_STARTED " to DET module if the DET module is enabled */
                    DCM_DET_ERROR(DCM_ROE_ID , DCM_E_PROTOCOL_NOT_STARTED )

                                                                                /*Initialize the Comm Active flag to the value false*/
                                                                                            Dcm_DsldGlobal_st.flgCommActive_b       = FALSE;
                    dataReturnValue_u8   = DCM_E_ROE_NOT_ACCEPTED;
                }
            }

            /* Check the type of ROE */
            if((DCM_PRV_DSLD_TYPE1 == (Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs)->roerdpi_type_u8)
                    &&(dataReturnValue_u8 == DCM_E_OK))
            {
                /* Check whether the DCM is free */
                /* Below section of the code is to protect the state transition from IDLE or
                 * READY_FOR_RECEPTION to ROETYPE1_RECEIVED, it is possible that other state
                 * transitions from these states can also be triggered in parallel from other
                 * contexts, thus this lock is needed
                 */
                SchM_Enter_Dcm_Global_NoNest();
                /* Multicore: Lock needed here to avoid parallel DSL state update in Rx and Tx confirmation calls */
                if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&&
                        (Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE) &&
                        (adrDest_pu8 != NULL_PTR) && (adrSrc_pu8 != NULL_PTR))
                {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                    stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
                    /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
                    if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
#endif
                    {
                        /* By moving the DSL state ignore request from tester */
                        Dcm_DsldGlobal_st.stDslState_en = DSL_ROETYPE1_RECIEVED;
                        Dcm_DsldGlobal_st.stDsdState_en = DSD_VERIFY_DIAGNOSTIC_DATA ;
                        Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                        /*Initialize the flag to accept ROE event during initialization*/
                        roeReqAccepted_b = TRUE;
                    }
                }



                SchM_Exit_Dcm_Global_NoNest();
                if(roeReqAccepted_b)
                {
                    /* Multicore: No lock necessary as the DSL state machine will ensure data consistency */
                    /* Only when Dcm is free there is a possibility that code reaches here */
                    Dcm_DsldGlobal_st.dataActiveRxPduId_u8 = dcmRxPduId_u8;
                    Dcm_DsldGlobal_st.dataRequestLength_u16 = (PduLengthType)MsgLen;
                    Dcm_DsldRoeRdpi_pcst = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs;

                    Dcm_DsldGlobal_st.dataSid_u8 = adrDest_pu8[0];

                    /* Set the ROE service table by storing active service table Id */
                    Dcm_DsldGlobal_st.dataOldSrvtable_u8 = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
                    Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldRoeRdpi_pcst->servicetable_Id_u8;
                    Dcm_DsldSrvTable_pcst =
                            Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
                    /* Store the RXPduid */
                    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                       there is no parallel writing due to DSL state machine handling */
                    Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

                    /* This is ROE requested service */
                    Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;

                    /* Copy the request and free the buffer */
                    for(idxIndex_qu16 = (uint16)MsgLen; idxIndex_qu16 != 0x00u; idxIndex_qu16--)
                    {

                        *adrSrc_pu8 = *adrDest_pu8;

                        adrSrc_pu8++;

                        adrDest_pu8++;

                    }
                }
                else
                {
                    /* pass the event Id to the function Dcm_UpdateROEQueue ()to queue the event since DCM is currently busy. */
                    dataReturnValue_u8=  Dcm_UpdateROEQueue(*(MsgPtr+MsgLen) , dcmRxPduId_u8);
                }
            }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
            else if((dataReturnValue_u8 == DCM_E_OK) &&
                    (DCM_PRV_DSLD_TYPE2 == (Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs)->roerdpi_type_u8))
            {
                /* Check if any event response under processing*/
                if((Dcm_DsdRoe2State_en == DSD_IDLE) &&
                        (dataReturnValue_u8 == DCM_E_OK) &&
                        (adrDest_pu8 != NULL_PTR) && (adrSrc_pu8 != NULL_PTR))
                {

                    /* Copy the request and free the buffer */
                    for(idxIndex_qu16 = (uint16)MsgLen; idxIndex_qu16 != 0x00u; idxIndex_qu16--)
                    {
                        *adrSrc_pu8 = *adrDest_pu8;

                        adrSrc_pu8++;

                        adrDest_pu8++;
                    }
                    /* Get the ROE structure */
                    Dcm_DsldRoe2_pcst = Dcm_DsldProtocol_pcst[idxProtocol_u8].roe_info_pcs;
                    /* Store the request length */
                    Dcm_Roe2MesContext_st.reqDataLen = MsgLen - 1u;
                    /* Store the RxPdu Id */
                    Dcm_Roe2MesContext_st.dcmRxPduId = dcmRxPduId_u8;
                    /* Get the number of services present in the ROE service table */
                    nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].num_services_u8;
                    /* Get the pointer to service table*/
                    adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

                    Dcm_Roe2MesContext_st.idContext  = Dcm_DsldRoe2_pcst->txbuffer_ptr[0];

                    /* Search the requested service in ROE service table */
                    for(idxIndex_u8 = 0x00u; idxIndex_u8 != nrService_u8; idxIndex_u8++)
                    {
                        if(Dcm_Roe2MesContext_st.idContext == adrSrvTable_pcst[idxIndex_u8].sid_u8)
                        {
                            /* SID Found, break the loop */
                            break;
                        }
                    }
                    /* Is SID exists in table? */
                    if(idxIndex_u8 != nrService_u8)
                    {
                        /* Store the index of the service */
                        Dcm_DsldSrvIndex_u8 = idxIndex_u8;
                        /* Process the request in next call of Dcm_MainFunction() */
                        Dcm_DsdRoe2State_en = DSD_VERIFY_DIAGNOSTIC_DATA;
                    }
                    else
                    {
                        /* Service requested by ROE is not configured in ROE service table */
                        dataReturnValue_u8   = DCM_E_ROE_NOT_ACCEPTED;
                    }
                }
                else
                {
                    /* pass the event Id to the function Dcm_UpdateROEQueue ()to queue the event since DCM is currently busy. */
                    dataReturnValue_u8=  Dcm_UpdateROEQueue(*(adrDest_pu8+MsgLen+1) , dcmRxPduId_u8);
                }
            }
#endif
            else
            {
                /* Reject the request because unable to start protocol */
                dataReturnValue_u8   = DCM_E_ROE_NOT_ACCEPTED;
            }

        }
        else
        {
            /* reject the request because unable to buffer is not enough to hold request */
            dataReturnValue_u8  = DCM_E_ROE_NOT_ACCEPTED;
        }
    }


    else
    {
        /* ROE request cannot be accepted as Dcm is not initialized.Return value dataReturnValue_u8 is already initialized */
    }

    }
    else
    {
        /* ROE request cannot be accepted as Dcm is not initialized.Return value dataReturnValue_u8 is already initialized */
    }
    return(dataReturnValue_u8);
}


/**
 *********************************************************************************************************************
 * Dcm_ChkIfDidServiceIsActive :  This API is called from ROE Type2 state machine/DSD to check if  DID service is active
 * for Roe Event and in DslDsd for tester request. Also this API checks if the tester request is processing DID
 * service and ROE events also wants to access the DID service. There is no possibility to run the DID services in
 * parallel due to re-enterancy/data consistency issues
 *
 * \param           TesterReqSid_u8: Service ID of the active tester request
 *                  RoeType2Sid_u8 : Service ID of the Roe Type2 event triggered
 *
 * \retval          TRUE : Parallel processing of tester request and ROE event is possible
 *                  FALSE: Parallel processing of tester request and ROE event is not possible
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
FUNC(boolean,DCM_CODE) Dcm_ChkIfDidServiceIsActive(VAR(uint8, AUTOMATIC) TesterReqSid_u8, VAR(uint8, AUTOMATIC) RoeType2Sid_u8)
                                                                        {
    VAR(boolean,AUTOMATIC)  retval_b;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST)  adrSrvTable_pcst;
    adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;
    /*initialize the return value to true*/
    retval_b = TRUE;

    /* If the Service requested by tester and the service triggered by ROE are both located in DCM */
    if((Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b)&& \
            (adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].servicelocator_b))
    {
        /* If the tester requested service is same as the ROE requested service */
        if(TesterReqSid_u8 == RoeType2Sid_u8)
        {
            /*Initialize the return val to false*/
            retval_b = FALSE;
        }
        /* If the tester requested service and ROE requested service are both DID services */
        else if( \
                ((TesterReqSid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER) || \
                        (TesterReqSid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)|| \
                        (TesterReqSid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)|| \
                        (TesterReqSid_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)) \
                        && \
                        ((RoeType2Sid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER) || \
                                (RoeType2Sid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)|| \
                                (RoeType2Sid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)|| \
                                (RoeType2Sid_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)) \
        )
        {
            /*Initialize the return value to false*/
            retval_b = FALSE;
        }
        else
        {
            /* nothing to set */
        }
    }
    return(retval_b);
                                                                        }

/**
 **************************************************************************************************
 * Dcm_DsldRoeInitiateResponseTransmission :
 * The  function is a generic library introduced to invoke the triggering of positive, negative
 * response or Response Pending operation (NRC0x78) or PENDING return
 * \param           retVal_u8    :   Type of operation to be carried out
 *
 * \retval          None
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_DsldRoeInitiateResponseTransmission(VAR(Std_ReturnType,AUTOMATIC) retVal_u8);
static FUNC(void,DCM_CODE) Dcm_DsldRoeInitiateResponseTransmission(VAR(Std_ReturnType,AUTOMATIC) retVal_u8)
                                                                        {
    if(retVal_u8 == E_OK)
    {
        s_RoeOpstatus_u8 = DCM_INITIAL;
        /*Trigger transmission of positive response*/
        Dcm_ProcessingDone ( & Dcm_Roe2MesContext_st);
    }
    else if (retVal_u8 == DCM_E_PENDING)
    {
        /*Do nothing here, just set opstatus to pendin operation*/
        s_RoeOpstatus_u8 = DCM_PENDING;
    }
    else if (retVal_u8 == DCM_E_FORCE_RCRRP)
    {
        /*Do we need to tigger a force response pend*/
        if(Dcm_ForceRespPend() == E_OK)
        {
            /* Do nothing.State is already changed */
            s_RoeOpstatus_u8 = DCM_FORCE_RCRRP_OK;
        }
        /* If transmission of WaitPend response is not successful */
        else
        {
            /*Do nothing here*/
        }
    }
    else
    {
        /*If no NRC is set by the service send NRC22 as default service, ideally this should nevery occur*/
        if(s_dataNrc_u8 ==0x00)
        {
            s_dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
        }
        s_RoeOpstatus_u8 = DCM_INITIAL;
        /*Trigger transmission of negative response*/
        Dcm_SetNegResponse( & Dcm_Roe2MesContext_st ,s_dataNrc_u8);
        Dcm_ProcessingDone ( & Dcm_Roe2MesContext_st);
    }
                                                                        }
/**
 **************************************************************************************************
 * Dcm_DsldRoe2StateMachine :  This function called from Dcm_MainFunction() to process ROE requested
 *                              service in parallel to normal tester request
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_DsldRoe2StateMachine(void)
                                                                        {
    VAR(uint8,AUTOMATIC) nrService_u8;
    VAR(uint8,AUTOMATIC) idxIndex_u8;
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC)  stConfirm_u8;
    VAR(uint8,AUTOMATIC) dataNrc_u8;  /* Variable to store negative response code */
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST)  adrSrvTable_pcst;

    switch(Dcm_DsdRoe2State_en)
    {
        case DSD_IDLE:
            break;

        case DSD_VERIFY_DIAGNOSTIC_DATA:
            /* Initializing the negative response code */
            dataNrc_u8=0x00;

            /* Fill the default response type */
            Dcm_Roe2ResponseType_en = DCM_DSLD_POS_RESPONSE;

            /* Response length (filled by the service) */
            Dcm_Roe2MesContext_st.resDataLen = 0x0u;

            /* Get the number of services present in the ROE service table */
            nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].num_services_u8;

            /* Get the pointer to service table*/
            adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

            /* Fill the Sid */
            Dcm_Roe2MesContext_st.idContext  = Dcm_DsldRoe2_pcst->txbuffer_ptr[0];

            /* This is ROE requested service */
            Dcm_Roe2MesContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;
            /* Search the requested service in ROE service table */
            for(idxIndex_u8 = 0x00; idxIndex_u8 != nrService_u8; idxIndex_u8++)
            {
                if(Dcm_Roe2MesContext_st.idContext == adrSrvTable_pcst[idxIndex_u8].sid_u8)
                {
                    /* SID Found, break the loop */
                    break;
                }
            }

            /* Is SID exists in table? */
            if(idxIndex_u8 != nrService_u8)
            {
                /* Store the index of the service */
                Dcm_DsldSrvIndex_u8 = idxIndex_u8;

                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues*/
                /* If there is a parallel update to DSL state there is no functionality problems observed*/
                /*If requested sid for the is supported*/
                if(((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&&(Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE)) || (Dcm_ChkIfDidServiceIsActive(Dcm_DsldGlobal_st.dataSid_u8,Dcm_Roe2MesContext_st.idContext)!=FALSE))
                {
                    /* Fill the addressing mode info (physical or functional) */
                    if(Dcm_Roe2MesContext_st.dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID)
                    {
                        Dcm_Roe2MesContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
                    }
                    else
                    {
                        Dcm_Roe2MesContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
                    }

                    /* Fill the Rx buffer pointer excluding Sid */
                    Dcm_Roe2MesContext_st.reqData = &(Dcm_DsldRoe2_pcst->txbuffer_ptr[1]);

                    /* Fill the Tx buffer pointer */
                    Dcm_Roe2MesContext_st.resData = &(Dcm_DsldRoe2_pcst->txbuffer_ptr[3]);

                    /* Fill the maximum possible response length */
                    Dcm_Roe2MesContext_st.resMaxDataLen = Dcm_DsldRoe2_pcst->txbuffer_length_u32 - 1u;


                    /* Check whether the suppressed positive bit is enabled for this request*/

                    if((adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].subfunction_exist_b != FALSE)&&((Dcm_DsldRoe2_pcst->txbuffer_ptr[1]&0x80u) == 0x80u))
                    {
                        /*suppressed positive bit is always set to true*/
                        Dcm_Roe2MesContext_st.msgAddInfo.suppressPosResponse = TRUE;

                        /* Remove the suppress positive bit from the sub-function byte*/
                        (*Dcm_Roe2MesContext_st.reqData) = ((*Dcm_Roe2MesContext_st.reqData) & 0x7Fu);
                    }
                    /* If sub-function is supported and sub-services are configured in DSD */

                    if((adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].subfunction_exist_b!= FALSE) &&  (adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].num_sf_u8!=0))
                    {
                        /* Call the API to do sub-function related checks */
                        Dcm_Dsld_CheckSubFunction (&Dcm_Roe2MesContext_st,adrSrvTable_pcst,&dataNrc_u8);
                    }
                    if(dataNrc_u8 == 0x00)
                    {
                        /* Change state to call the service */
                        Dcm_DsdRoe2State_en = DSD_CALL_SERVICE;

                        /* Start ROE2 timer */

                        DCM_TimerStart(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,DCM_CFG_ROERDPI_TIMEOUT,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr)

                        /* Call the service first time */
                        dataRetVal_u8=(*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].service_handler_fp)(DCM_INITIAL,&Dcm_Roe2MesContext_st,&dataNrc_u8);

                        Dcm_DsldRoeInitiateResponseTransmission(dataRetVal_u8);
                    }
                    else
                    {
                        Dcm_SetNegResponse(&Dcm_Roe2MesContext_st,dataNrc_u8);
                        Dcm_ProcessingDone(&Dcm_Roe2MesContext_st );
                    }
                }
                else
                {
                    /* SID not found, send the negative response */
                    Dcm_SetNegResponse(&Dcm_Roe2MesContext_st,DCM_E_SERVICENOTSUPPORTED);
                    Dcm_ProcessingDone(&Dcm_Roe2MesContext_st );

                }
            }
            break;

        case DSD_CALL_SERVICE:

            /* Get the pointer to service table*/
            adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs;

            /* Check whether the RDPI timeout has occurred  */
                        if(DCM_TimerElapsed(Dcm_DsldGlobal_st.datRoeType2Timeout_u32)== FALSE)
            {
            /* Start ROE2 timer */
                DCM_TimerProcess(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr)

                                                                                    /* Call the service if it located inside the DCM */
                                                                                    /*Is Service existing in DSP*/
                                                                                    if(adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].servicelocator_b != FALSE)
                                                                                    {
                                                                                        dataRetVal_u8=(*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].service_handler_fp)(DCM_INITIAL,&Dcm_Roe2MesContext_st,&dataNrc_u8);

                                                                                        Dcm_DsldRoeInitiateResponseTransmission(dataRetVal_u8);
                                                                                    }
            }
            else
            {
                /* Give the confirmation to ROE application */
                DcmAppl_DcmConfirmation(Dcm_Roe2MesContext_st.idContext,
                        Dcm_Roe2MesContext_st.dcmRxPduId,
                        Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_Roe2MesContext_st.dcmRxPduId].testsrcaddr_u16,
                        DCM_RES_POS_NOT_OK);


                if(adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].Service_init_fp != NULL_PTR)
                {
                    /* Call initialization of the active service */
                    (*adrSrvTable_pcst[Dcm_DsldSrvIndex_u8].Service_init_fp)();
                }
                /* reset the DCM states */
                Dcm_DsdRoe2State_en = DSD_IDLE;
            }
            break;

        case DSD_SEND:
            /* DCM is sending the response */
            break;


        case DSD_TX_CONFIRMATION:

            /* Is previous response sent successfully by PduR? */
            if(Dcm_Roe2TxResult_u8 == E_OK)
            {
                if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
                {
                    /* POS response sent successfully */
                    stConfirm_u8 = DCM_RES_POS_OK;
                }
                else
                {
                    /* NEG response sent successfully */
                    stConfirm_u8 = DCM_RES_NEG_OK;
                }
            }
            else
            {
                if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE )
                {
                    /* Unable to send positive response */
                    stConfirm_u8 = DCM_RES_POS_NOT_OK;
                }
                else
                {
                    /* Unable to send negative response response */
                    stConfirm_u8 = DCM_RES_NEG_NOT_OK;
                }
            }



            if(Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed !=FALSE)
            {
                Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = FALSE;
            }


            /* Give the confirmation to application */
            DcmAppl_DcmConfirmation(Dcm_Roe2MesContext_st.idContext,
                    Dcm_Roe2MesContext_st.dcmRxPduId,
                    Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_Roe2MesContext_st.dcmRxPduId].testsrcaddr_u16,
                    stConfirm_u8);

            /* DSD state made to Idle */
            Dcm_DsdRoe2State_en = DSD_IDLE;
            /* Start ROE2 timer */

            DCM_TimerStart(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,DCM_CFG_ROETYPE2_INTERMSGTIME,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr)


            break;

        default:
            break;
    }
                                                                       }


#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/**
 **************************************************************************************************
 * Dcm_DsldRoeRdpiTimeOut :  Monitoring of ROE timer
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(void,DCM_CODE) Dcm_DsldRoeRdpiTimeOut(void)
                                                                        {
    /* Is this ROE call */
    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */
    /* And this API is called only when DSL is processing RDPI/ROE event and hence no parallel write is possible */
    if(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)
    {
        /* Is ROE timeout occurred? */
        if(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataRoeRdpiTimeout_u32)== FALSE)
        {
            /* Start ROE2 timer */
            DCM_TimerProcess(Dcm_DsldGlobal_st.dataRoeRdpiTimeout_u32,Dcm_RoerdpiStartTick_u32,Dcm_RoeRdpiType1TimerStatus_uchr)
        }
        else
        {
            if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
            {
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
                /* Give the confirmation to ROE application */
                DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                        Dcm_DsldMsgContext_st.dcmRxPduId,
                        Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                        DCM_RES_POS_NOT_OK);
#endif
            }
            else
            {
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
                /* Give the confirmation to RDPI application */
                DcmAppl_DcmConfirmationRDPI(0x2A,
                        Dcm_DsldMsgContext_st.dcmRxPduId,
                        DCM_RES_POS_NOT_OK);
#endif
            }
            /* reset the DCM states */
            Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;


#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||((DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_RDPITYPE2_ENABLED == DCM_CFG_OFF)))
            if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
            {
                /* Change the service table to originally active table */
                Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
            }
            Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].
                    ptr_service_table_pcs;
#endif
            /* Multicore: No lock needed here as Dsl state is an atomic operation */
            /* DSL state machine handling ensures that there is no data consistency issues */
            /* Also this API is called from DSD state machine after DSL state machine, hence no parallel write */
            Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;
        }
    }
                                                                        }

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_TriggerOnEvent:
 * The call to this function allows to trigger an event linked to a ResponseOnEvent request.
 * On the function call, the DCM will execute the associated service. This function
 * shall be called only if the associated event has been activated through a
 * xxx_ActivateEvent() call.
 *
 * \parameters           RoeEventId
 * \return value         Std_ReturnType
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_TriggerOnEvent( uint8 RoeEventId )
                                                                        {
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
    VAR(uint16,AUTOMATIC) idxRoeDid_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataRetStartFunc_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataRoeStatus_u8;
    VAR(uint8,AUTOMATIC) dataSrc_u8[4];
    VAR(uint32,AUTOMATIC) datatMsgLen_u32;

    idxRoeDid_u8=0x0;
    dataRetStartFunc_u8=E_NOT_OK;
    datatMsgLen_u32=0;

    /*Loop through all the ROE dids and chk if the event id is valid*/
    for(idxRoeDid_u8=0;idxRoeDid_u8<DCM_MAX_DIDROEEVENTS;idxRoeDid_u8++)
    {
        if(RoeEventId==DcmDspRoeDidEvents[idxRoeDid_u8].RoeEventId_u8)
        {
            /*Valid ROEEVENT ID*/
            break;
        }
    }
    /*Check if the event is valid and is in the started state & if not return value is already
     * set to E_NOT_OK if the event is not found or cleared.*/
    if(idxRoeDid_u8<DCM_MAX_DIDROEEVENTS)
    {
        /*Chk if the event is started*/
        if(DCM_ROE_STARTED==DcmDspRoeDidStateVariables[idxRoeDid_u8].RoeEventStatus)
        {
            /*Enters here only if the event is started and the event id is valid*/
            dataRetStartFunc_u8=E_OK;
        }
    }

    if(E_OK==dataRetStartFunc_u8)
    {
        /**Simulate the request in the buffer and invoke Dcm_ResponseOnOneEvent*/
        dataSrc_u8[0]=0x22u;  /*RDBI service ID*/
        dataSrc_u8[1]=(uint8)((DcmDspRoeDidStateVariables[idxRoeDid_u8].stSrvToRespDid_u16)>>8u);  /*DID high byte*/
        dataSrc_u8[2]=(uint8)(DcmDspRoeDidStateVariables[idxRoeDid_u8].stSrvToRespDid_u16);  /*DID low byte*/
        dataSrc_u8[3]= RoeEventId;/*Roe Event ID is passed to the Dcm_ResponseOnOneEvent as an implicit parameter,the datatMsgLen_u32 will not be changed,it is intentional*/
        datatMsgLen_u32=3;
        dataRoeStatus_u8=Dcm_ResponseOnOneEvent(dataSrc_u8,datatMsgLen_u32,DcmDspRoeDidStateVariables[idxRoeDid_u8].SourceAddress_u16);
        /*  Check if DCM Is free or busy processing another request, if DCM is busy return E_NOT_OK*/
        if(dataRoeStatus_u8!=DCM_E_OK)
        {
            dataRetStartFunc_u8=E_NOT_OK;
        }
    }
    return dataRetStartFunc_u8;
#else
    (void)RoeEventId;
    return E_NOT_OK;
#endif

                                                                        }



/**
 **************************************************************************************************
 * Dcm_DemTriggerOnDTCStatus :  This function is invoked by Dem on an interrupt context to inform DCM about the
 * status mask change for a particular DTC, this information can be used by DTC
 * to check if RDTC service has to be invoked or not based on the DTC if it was
 * setup by tester for ROE onchangeofDTC.
 *
 * \param           Dtc                 :   This is the DTC the change trigger is assigned
 *                  DTCStatusOld        :   Old Status
 *                  DTCStatusNew        :   New Status
 * \retval          E_OK          :   This value is always returned
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DemTriggerOnDTCStatus( uint32 Dtc, uint8 DTCStatusOld, uint8 DTCStatusNew )
                                                                        {
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&&(DCM_ROE_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
    VAR(uint8,AUTOMATIC)  dataRoeStatus_u8;
    VAR(uint8,AUTOMATIC)  dataSid_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataRetStartFunc_u8;
    VAR(uint8,AUTOMATIC) dataSrc_u8[3];
    VAR(uint32,AUTOMATIC) datatMsgLen_u32;


    /* Multicore: The read needs to be locked as there could be parallel Rx and ROE requests */
    SchM_Enter_Dcm_Global_NoNest();
    dataSid_u8=Dcm_DsldGlobal_st.dataSid_u8;
    SchM_Exit_Dcm_Global_NoNest();

    /*Make sure the current active service is not CDI service and SID variable is not in init state (SID value as 0)*/
    if((dataSid_u8 != 0x14) && (dataSid_u8 != 0x0))
    {
        /*Check if ROE for DTC is already started*/
        if(DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus)
        {
            /*Has the DTC status changed and if the mask bit provided by the tester is changed*/
            if(((DTCStatusOld & DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8) ^ (DTCStatusNew & DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8)) != 0x0)
            {
                /**Simulate the request in the buffer and invoke Dcm_ResponseOnOneEvent*/
                dataSrc_u8[0]=0x19u;  /*RDTC service ID*/
                dataSrc_u8[1]=0x0Eu;  /*DID high byte*/
                dataSrc_u8[2]= DcmDspRoeDtcEvent.RoeEventId_u8;/*Roe Event ID is passed to the Dcm_ResponseOnOneEvent as an implicit parameter,the datatMsgLen_u32 will not be changed,it is intentional*/
                datatMsgLen_u32=0x02u;
                dataRoeStatus_u8=Dcm_ResponseOnOneEvent(dataSrc_u8,datatMsgLen_u32, DcmDspRoeDtcStateVariable.SourceAddress_u16);
                /*  Check if DCM Is free or busy processing another request, if DCM is busy return E_NOT_OK*/
                if(dataRoeStatus_u8!=DCM_E_OK)
                {
                    dataRetStartFunc_u8=E_NOT_OK;
                }

            }
        }
    }
    return E_OK;
#else

    DCM_UNUSED_PARAM(DTCStatusOld);
    DCM_UNUSED_PARAM(DTCStatusNew);
    return E_OK;
#endif

    DCM_UNUSED_PARAM(Dtc);

                                                                        }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF && DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

/**
 **************************************************************************************************
 * Dcm_RestoreROEEvents:
 * This function will be invoked from the Dcm_Init().
 * In this function handling of the event window time restoring and storing of information from and to application happens.
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_RestoreROEEvents(void)
                                                                                {
    VAR(uint8,AUTOMATIC) dataidxLoop_u8;/*Loop index*/
    VAR(uint8, AUTOMATIC) roeEventWindowTime_u8;/*local varaible to store the event windowtime*/
    VAR(Std_ReturnType,AUTOMATIC) dataResult_u8;/* local variable to store the return value from the application */
    roeEventWindowTime_u8 =0x0u;/*initialize the local variable*/
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
    /*Check the initial event status from the configuration ,if the event is preconfigured inform the application through API call*/
    if(TRUE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
    {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
    }
    /*Call the application API to retrieve the roe evnet information stored in the NvM*/
    dataResult_u8 = DcmAppl_DcmGetRoeDTCInfo(DcmDspRoeDtcEvent.RoeEventId_u8,
            &DcmDspRoeDtcStateVariable.RoeEventStatus,
            &roeEventWindowTime_u8,
            &DcmDspRoeDtcStateVariable.SourceAddress_u16,
            &DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8,
            &DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b,
            &DcmDspRoeDtcStateVariable.stDspRoeStorageState_b,
            &DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b);
    if(E_OK == dataResult_u8)
    {
        /*Status change in conbination with current staus STARTED*/
        if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus))
        {
            if((roeEventWindowTime_u8 == 0x02u) || (roeEventWindowTime_u8 == 0x04u))
            {
                /*Restart the events which are started in the default session ans the storage state is set TRUE fro both the control start request and the set up request
                 * and the event window  time supports the storage state(event window time is infinity(0x02) or current and following cycle(0x04u))*/
                if((TRUE == DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b )&& (TRUE == DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b)  \
                        &&(TRUE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b))
                {
                    /*Inform application to restsrt the roe event*/
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STARTED);
#endif
                    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STARTED);

                }
                else
                {
                    /*Conditions does not support  to restart the ROE ,therefore stop it and inform application*/
                    DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
                    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
                }
            }
            /*Check if the event window time is CURRENT_CYCLE, then the window period is over .Stop the event and inform the application */
            else if(roeEventWindowTime_u8 == 0x03u)
            {
                /*Check whether the event is preconfigured*/
                if(FALSE != DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
                {
                    DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
                }
                else
                {
                    /*The set up is done by the tester,if the set up is stored in NVM update the status as stopped,else cleared*/
                    if(FALSE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b)
                    {
                        DcmDspRoeDtcStateVariable.RoeEventStatus = DCM_ROE_CLEARED;
                    }
                    else
                    {
                        DcmDspRoeDtcStateVariable.RoeEventStatus = DCM_ROE_STOPPED;
                    }
                }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);
            }
            else
            {

                /*dummy else*/
            }
        }
   else  if(DCM_ROE_STOPPED == DcmDspRoeDtcStateVariable.RoeEventStatus)
        {
            /*Remain in the stopped state if the  the events are stopped in the default session ans the storage state is set TRUE fro both the control start request and the set up request
                            * and the event window  time supports the storage state(event window time is infinity(0x02) or current and following cycle(0x04u))*/

            if(((roeEventWindowTime_u8 == 0x02u) ||(roeEventWindowTime_u8 == 0x04u)) && (TRUE == DcmDspRoeDtcStateVariable.stDspRoeCtrlStorageState_b) &&(TRUE == DcmDspRoeDtcStateVariable.stDspRoeStorageState_b) )
            {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
            }
            else
            {
                /*Conditions does not support  to continue in the stopped state of  ROE ,therefore clear it and inform application*/
                if(FALSE == DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
                {
                    DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);
                }
            }
        }
        else
        {
            /*Event status is cleared*/
            if(FALSE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
               {

                DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
           #if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                   (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_CLEARED);
           #endif
                   DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_CLEARED);
               }
        }
        if(roeEventWindowTime_u8 == 0x04u)
        {
            /*Now one cycle is already over ,reset the event windowtime CURRENT_FOLLOWING_CYCLE to CURRENT_CYCLE*/
            DcmAppl_DcmStoreROEcycleCounter(DcmDspRoeDtcEvent.RoeEventId_u8,0x03u);
        }
    }
    else
    {
        if(FALSE==DcmDspRoeDtcStateVariable.Is_PreConfigured_b)
        {
            /*The information could not be taken from the Nvm,move evnt status to CLEARED*/
            DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_CLEARED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_CLEARED);
        }
    }
#endif
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
    {
        roeEventWindowTime_u8 =0x0u;/*Reset the loacal variable*/
        /*Check the initial event status from the configuration ,if the event is preconfigured inform the application through API call*/
        if(TRUE==DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
        {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);
        }
        /*Call the application API to retrieve the roe evnet information stored in the NvM*/
        dataResult_u8 = DcmAppl_DcmGetROEDidInfo(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16,
                DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus,
                &roeEventWindowTime_u8,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].SourceAddress_u16,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b,
                &DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b);

        if(E_OK == dataResult_u8)
        {
            /*Status change in conbination with current staus STARTED*/
            if((DCM_ROE_STARTED==DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus))
            {
                if((roeEventWindowTime_u8 == 0x02u) || (roeEventWindowTime_u8 == 0x04u))
                {
                    /*Restart the events which are started in the default session ans the storage state is set TRUE fro both the control start request and the set up request
                     * and the event window  time supports the storage state(event window time is infinity(0x02) or current and following cycle(0x04u))*/
                    if((TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b )&& (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b)  \
                            &&(TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b) )
                    {
                        /*Inform application to restsrt the roe event*/
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                        (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STARTED);
#endif
                        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STARTED);

                    }
                    else
                    {
                        /*Conditions does not support  to restart the ROE ,therefore stop it and inform application*/
                        DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                        (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
                        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);
                    }
                }
                /*Check if the event window time is CURRENT_CYCLE, then the window period is over .Stop the event and inform the application */
                else
                {
                    if(roeEventWindowTime_u8 == 0x03u)
					{
                        if(FALSE != DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
                        {
                            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;
                        }
                        else
                        {
                            /*The set up is done by the tester,if the set up is stored in NVM update the status as stopped,else cleared*/
                            if(FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b)
                            {
                                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus = DCM_ROE_CLEARED;
                            }
                            else
                            {
                                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus = DCM_ROE_STOPPED;
                            }
                        }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                        (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
                        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
                   }
				}

            }
            else if  (DCM_ROE_STOPPED == DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus)
            {
                /*Remain in the stopped state if the  the events are stopped in the default session ans the storage state is set TRUE fro both the control start request and the set up request
                                            * and the event window  time supports the storage state(event window time is infinity(0x02) or current and following cycle(0x04u))*/
          if(((roeEventWindowTime_u8 == 0x02u) ||(roeEventWindowTime_u8 == 0x04u)) && (TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeCtrlStorageState_b) &&(TRUE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b) )
                {

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
                    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);

                }
                else
                {
                    /*Conditions does not support  to continue in the stopped state of  ROE ,therefore clear it and inform application*/
                    if(FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
                    {
                      DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_CLEARED;

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
                    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
                    }
                }
            }
            else
            {
                if(FALSE==DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
                       {

                    DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_CLEARED;
               #if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                           (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_CLEARED);
               #endif
                           DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_CLEARED);
                       }
            }

            if(roeEventWindowTime_u8 == 0x04u)
            {
                /*Now one cycle is already over ,reset the event windowtime CURRENT_FOLLOWING_CYCLE to CURRENT_CYCLE*/
                DcmAppl_DcmStoreROEcycleCounter(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,0x03u);
            }
        }
        else
        {
            if(FALSE==DcmDspRoeDidStateVariables[dataidxLoop_u8].Is_PreConfigured_b)
            {
                /*The information could not be taken from the Nvm,move evnt status to CLEARED*/
                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_CLEARED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_CLEARED);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_CLEARED);
            }
        }
    }
#endif
                                                                                }



/**
 **************************************************************************************************
 * Dcm_ResetROEEvents:
 * This function will be invoked whenever a session change occurs from Dcm_DspConfirmation.
 * In this function will stop all the events which are already started in the previous session.
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ResetROEEvents(void)
        {
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) dataidxLoop_u8 ;/*Loop index*/
#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
    /*Move the already started ROE events to the STOPPED state if it is started in any non-default session */
    if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus) && (DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b == FALSE))
    {
        DcmDspRoeDtcStateVariable.RoeEventStatus =DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);
    }
#endif

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
    for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
    {

        if((DCM_ROE_STARTED==DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus) && (FALSE == DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b ))

        {

            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus =DCM_ROE_STOPPED;
            /*Inform application to reset the roe event*/
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus);

        }


    }
#endif

                                                                                }

#if(DCM_CFG_ROETYPE2_ENABLED == DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_DsldProcessRoeType1:
 * The API will be invoked from the Dcm_DsldProcessRoeQueue(),this will intern trigger the processing of the RoeType1.
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_DsldProcessRoeType1(void);
static FUNC(void,DCM_CODE) Dcm_DsldProcessRoeType1(void)
{
    VAR(uint8,AUTOMATIC) RoeEventId_u8;
    VAR(uint8,AUTOMATIC) RxPduId_u8;
    VAR(Dcm_MsgType,AUTOMATIC) adrSrc_pu8;
    VAR(boolean,AUTOMATIC) dataStartProtocol_b = FALSE;

    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
    VAR(boolean,AUTOMATIC) roeReqAccepted_b;
    VAR(uint8,AUTOMATIC) dataidxLoop_u8;/*Loop index*/

    RoeEventId_u8 =Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].EventId_u8 ;
    RxPduId_u8 = (uint8)Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].RxPduId_u8;

    if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].channel_idx_u8))

    {
        adrSrc_pu8        = Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8].roe_info_pcs->txbuffer_ptr;
        /* Lock required here to maintain consistency within Dcm_DsldGlobal_st structure */
        SchM_Enter_Dcm_Global_NoNest();
        /* check whether any protocol is active in DCM */
        /*If the Dsl state is Ready for receving the request*/
        if((Dcm_DsldGlobal_st.flgCommActive_b == FALSE)&&(Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                &&      \
                ((Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL_RECEIVING) && (Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL))
#endif
        )
        {
            /* Activate the protocol */
            /* Update the global variables  */
            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8;
            Dcm_DsldGlobal_st.nrActiveConn_u8      = Dcm_DsldRxTable_pcu8[RxPduId_u8];
            Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[RxPduId_u8]].protocol_num_u8].sid_tableid_u8;
            /*Initialize the Comm Active flag to value true */
            Dcm_DsldGlobal_st.flgCommActive_b       = TRUE;
            /*Initialize the data start protocol value to true */
            dataStartProtocol_b = TRUE;
        }/*Dcm is busy, queue the DTCs*/
        SchM_Exit_Dcm_Global_NoNest();
        /*Check if data start protocol value is set to get the protocol id*/
        if(dataStartProtocol_b != FALSE)
        {
            /* Start the application function */
            if(Dcm_StartProtocol(Dcm_DsldProtocol_pcst[ Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8)== E_OK )
            {
                /* If cooperative scheduler is enabled, shift the service initializations to cooperative scheduler based on
                                   individual service configuration */
                DCM_DSLD_COOPSCHEDULER_SHIFTINI(Dcm_DsldGlobal_st.datActiveSrvtable_u8)
                                                                                        /* Call the Initialisation function of service */
                                                                                        Dcm_DsldCallServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

                /* Get the active service table of the protocol */
                Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
            }
            else
            {
                /*Initialize the Comm Active flag to false*/
                Dcm_DsldGlobal_st.flgCommActive_b       = FALSE;
            }
        }



        SchM_Enter_Dcm_Global_NoNest();
        /* Multicore: Lock needed here to avoid parallel DSL state update in Rx and Tx confirmation calls */
        if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&&
                (Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE) &&
                (adrSrc_pu8 != NULL_PTR))
        {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
            /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
            if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
#endif
            {
                /* By moving the DSL state ignore request from tester */
                Dcm_DsldGlobal_st.stDslState_en = DSL_ROETYPE1_RECIEVED;
                Dcm_DsldGlobal_st.stDsdState_en = DSD_VERIFY_DIAGNOSTIC_DATA ;
                Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                /*Initialize the flag to accept ROE event during initialization*/
                roeReqAccepted_b = TRUE;
            }
        }
SchM_Exit_Dcm_Global_NoNest();
        /* Multicore: No lock necessary as the DSL state machine will ensure data consistency */
        /* Only when Dcm is free there is a possibility that code reaches here */
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8 =RxPduId_u8;

        Dcm_DsldRoeRdpi_pcst = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].roe_info_pcs;


#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

        if( Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].EventId_u8  ==  DCM_ROE_DTCEVENTID)
        {
            Dcm_DsldGlobal_st.dataSid_u8=0x19u;  /*RDTC service ID*/
            (*adrSrc_pu8)= 0x19;
            adrSrc_pu8++;
            *adrSrc_pu8 = 0x0Eu;

            Dcm_DsldGlobal_st.dataRequestLength_u16 =(PduLengthType)2u;

        }



        else
#endif
        {

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
            for(dataidxLoop_u8 =0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
            {
                if( DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8 == Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].EventId_u8)
                {
                    break;
                }
            }

            Dcm_DsldGlobal_st.dataSid_u8=0x22u;  /*RDBI service ID*/

            (*adrSrc_pu8)= 0x22;
             adrSrc_pu8++;
            *(adrSrc_pu8) = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16>>8u);
             adrSrc_pu8++;
            *(adrSrc_pu8) = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16);
            Dcm_DsldGlobal_st.dataRequestLength_u16 =(PduLengthType)3u;

#endif

        }


        Dcm_DsldGlobal_st.dataOldSrvtable_u8 = Dcm_DsldGlobal_st.datActiveSrvtable_u8;
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Dcm_DsldRoeRdpi_pcst->servicetable_Id_u8;
        Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
        /* Store the RXPduid */
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                                   there is no parallel writing due to DSL state machine handling */
        Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

        /* This is ROE requested service */
        Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_ROE_SOURCE;
    }
}
#endif

/**
 **************************************************************************************************
 * Dcm_DsldProcessRoeQueue:
 * The API will be invoked from the Dcm_main(),this will intern trigger the processing of the RoeType1 and RoeType2
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldProcessRoeQueue(void)
                                 {

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    /*Check if ROE timeout is occured?*/
    if(DCM_TimerElapsed(Dcm_DsldGlobal_st.datRoeType2Timeout_u32)== FALSE)
    {
        /* Start ROE2 timer */
        DCM_TimerProcess(Dcm_DsldGlobal_st.datRoeType2Timeout_u32,Dcm_Roe2StartTick_u32,Dcm_RoeType2TimerStatus_uchr)

    }
    else
#endif

    {

        if(DcmRoeQueueIndex_u8 == DCM_MAX_SETUPROEEVENTS)
        {
            DcmRoeQueueIndex_u8 = 0x00u;
        }

        while(DcmRoeQueueIndex_u8<DCM_MAX_SETUPROEEVENTS)
        {
            if(Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Queued == TRUE)
            {
                Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Queued = FALSE;
                Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = TRUE;
                break;

            }
        DcmRoeQueueIndex_u8++;

        }
        if(DcmRoeQueueIndex_u8!=DCM_MAX_SETUPROEEVENTS)
        {


#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
            if(Dcm_DsdRoe2State_en == DSD_IDLE)
            {
                Dcm_DsdRoe2State_en = DSD_VERIFY_DIAGNOSTIC_DATA;
                /* Roe type 2 handling */
                Dcm_DsldRoe2StateMachine();
            }
#else
            Dcm_DsldProcessRoeType1();
#endif
        }
    }
                                 }

#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
