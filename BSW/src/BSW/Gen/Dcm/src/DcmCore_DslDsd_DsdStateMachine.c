

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static FUNC(void,DCM_CODE) Dcm_DsldVerifyData(void);
static FUNC(uint8,DCM_CODE) Dcm_DsldSearchDataSid_u8( VAR(uint8, AUTOMATIC) nrElements_u8, CONST(uint8, AUTOMATIC) dataSid_cu8);
static FUNC(void,DCM_CODE) Dcm_DsldInitiateResponseTransmission(VAR(Std_ReturnType,AUTOMATIC) retVal_u8);
#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
static FUNC(Std_ReturnType,DCM_CODE) Dcm_DsldManufacturerNotification_u8(void);
#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
/* definition of message context table */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_MsgContextType,DCM_VAR) Dcm_DsldMsgContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) s_dataNrc_u8;
VAR (Dcm_SrvOpStatusType, DCM_VAR) Dcm_SrvOpstatus_u8;
VAR(Std_ReturnType,DCM_VAR) Dcm_retVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/**
 **************************************************************************************************
 * Dcm_DsldVerifyData : Function to verify the diagnostic data partially. i.e For requested Sid
 *                       session, security and environment conditions are checked. if verification fail
 *                       Negative response is sent with proper NRC.
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_DsldVerifyData(void)
{
    /* bit mask to represent session */
    VAR(uint32,AUTOMATIC) dataSessionActive_u32;
    /* bit mask to represent security */
    VAR(uint32,AUTOMATIC) dataSecurityActive_u32;
    /* local pointer to service configuration structure*/
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrService_pcst;
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
    /* result of call back function */
    VAR(uint8,AUTOMATIC) dataResult_u8;
#endif
    /* Variable to store the negative response code */
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNrc_u8;
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    dataNrc_u8 = 0x00;
    /* get the active service configuration structure */
    adrService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);

    /* generate bit mask for active session */
    dataSessionActive_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSession_u8);

    /* check requested service is allowed in this session */
    if((adrService_pcst->allowed_session_b32 & dataSessionActive_u32)== (dataSessionActive_u32))
    {
        /* generate bit mask for active security level */
        dataSecurityActive_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

        /* check requested service is allowed in this security level */
        if((adrService_pcst->allowed_security_b32 & dataSecurityActive_u32)== (dataSecurityActive_u32))
        {
            if(adrService_pcst->adrUserServiceModeRule_pfct !=NULL_PTR)
            {
                /* Call the configured Callback to check for any pre-conditions for the SID */
                retVal_u8 = (*adrService_pcst->adrUserServiceModeRule_pfct)(&dataNrc_u8,Dcm_DsldGlobal_st.dataSid_u8);
            }
            else
            {
                /* Call the DcmAppl Callback to check for any pre-conditions for the SID */
                retVal_u8 = DcmAppl_UserServiceModeRuleService(&dataNrc_u8,Dcm_DsldGlobal_st.dataSid_u8);
            }

            /* If the DcmAppl API returns E_OK with unset NRC value, proceed further to the processing of the service */
            if (retVal_u8 == E_OK)
            {
                dataNrc_u8=0;
#if(DCM_CFG_DSD_MODERULESERVICE_ENABLED!=DCM_CFG_OFF)
            /* Check if mode rule function pointer is a null pointer and proper NRC was sent for the requested service */
                if (( adrService_pcst->moderule_fp == NULL_PTR ) || ( (*adrService_pcst->moderule_fp)(&dataNrc_u8) != FALSE ) )
#endif
                {

                    /* fill the message context table with suppress positive response info */
                    /* Even Service also can set this bit, but service should not reset this bit */
                    /*Check if the Dcm_DsldMsgContext for the reqData is supported and equal to 0x80 and subfunction_exist for the requested service is supported */
                    if(((((*Dcm_DsldMsgContext_st.reqData) & (0x80u)) == 0x80u) &&(adrService_pcst->subfunction_exist_b != FALSE)))
                    {
                        /*Set the suppressPosResponse flag to True */
                        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;

                        /* remove the MSB(suppress positive bit) of sub function */
                        (*Dcm_DsldMsgContext_st.reqData) = ((*Dcm_DsldMsgContext_st.reqData) & (0x7fu));
                    }
                    else
                    {
                        /*Set the suppressPosResponse flag to False*/
                        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
                    }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
                    /* Take the request only if ROE Type2 state mcahine is free OR ROE Type2 is not processing the DID service/same service */

                    if((Dcm_DsdRoe2State_en == DSD_IDLE) || (Dcm_ChkIfDidServiceIsActive(Dcm_DsldGlobal_st.dataSid_u8,Dcm_Roe2MesContext_st.idContext)))
 #endif
                    {
                    /* check pre-compile time configuration "DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED" enabled or not */
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

                        /* For ROE requested request no need to call this Appl function */
                        if(Dcm_DsldGlobal_st.stDslState_en != DSL_ROETYPE1_RECIEVED)
                        {
                            /* call the Appl callback function to check the permission before calling the service */
                            dataResult_u8 = Dcm_SupplierNotification(   Dcm_DsldGlobal_st.dataSid_u8,
                                    Dcm_DsldMsgContext_st.reqData,
                                    (uint16)Dcm_DsldMsgContext_st.reqDataLen,
                                    Dcm_DsldMsgContext_st.msgAddInfo.reqType,
                                    Dcm_DsldMsgContext_st.dcmRxPduId,
                                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                                    &dataNrc_u8);
                            if(dataResult_u8 == E_OK)
                            {

                                    /* If subfunction is supported and subservices are configured in DSD */
                                    if(adrService_pcst->subfunction_exist_b != FALSE)
                                    {
                                        /* Call the API to do sub-function related checks */
                                        Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
                                    }

                                if(dataNrc_u8==0x00)
                                {
                                    /* change the DSD state to call service state */
                                    Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
                                    /* If an ROE Type 2 Event is not being processed */
                                  
                                    if(DCM_DSLD_SERVICEBUSY() == FALSE)
                                    {
                                        if(adrService_pcst->service_handler_fp != NULL_PTR)
                                        {
                                            /* Call the service based on whether it uses cooperative scheduler */
                                            /* ROE service will always configure mail scheduler, hence ROE service is always
                                           called from here  */
                                            s_dataNrc_u8 =0x00;
                                            DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE_FIRSTCALL(Dcm_SrvOpstatus_u8,adrService_pcst,&s_dataNrc_u8)
                                            Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                                        }
                                    }
                                }
                            }
                            else if(dataResult_u8 == DCM_E_REQUEST_NOT_ACCEPTED)
                            {
                                /* request is not accepted, Ignore the request. Move the DSD and DSL to default state */
                                /* to reset the DSL, simulate suppress positive response */
                                /*Set the suppressPosResponse flag to True.*/
                                Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
                            }
                            else if(dataResult_u8 == DCM_E_PENDING)
                            {
                                dataNrc_u8=0x00;
                                Dcm_DsldGlobal_st.stDsdState_en = DSD_VERIFY_DATA_PENDING;
                            }
                            else
                            {
                                /* Do nothing NRC is already updated */
                            }
                        }
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
                        else
                        {
                            /* If subfunction is supported and subservices are configured in DSD */
                            /*Check if the subfunction_exist for the requested service is supported */
                            if(adrService_pcst->subfunction_exist_b != FALSE)
                            {
                                /* Call the API to do sub-function related checks */
                                Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
                            }
                            if(dataNrc_u8==0x00)
                            {
                                /* change the DSD state to call service state */
                                Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
                                /* If an ROE Type 2 Event is not being processed */
                                /*Check if the DCM_DSLD_SERVICEBUSY is set to False */
                       
                                if(DCM_DSLD_SERVICEBUSY() == FALSE)
                                {
                                    if(adrService_pcst->service_handler_fp != NULL_PTR)
                                    {
                                        s_dataNrc_u8 =0x00;
                                        Dcm_retVal_u8=(*adrService_pcst->service_handler_fp)( Dcm_SrvOpstatus_u8,& Dcm_DsldMsgContext_st,&s_dataNrc_u8);
                                        Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                                    }
                                }
                            }
                        }
#endif
#else
                        /* If subfunction is supported and subservices are configured in DSD */
                        /*Check if the subfunction_exist is supported in the configured service in DSD */
                        if(adrService_pcst->subfunction_exist_b != FALSE)
                        {
                            /* Call the API to do sub-function related checks */
                            Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
                        }
                        if(dataNrc_u8==0x00)
                        {
                            /* change the DSD state to call service state */
                            Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
                            /* If an ROE Type 2 Event is not being processed */
                            /*Check if the DCM_DSLD_SERVICEBUSY is set to False */
                         
                            if(DCM_DSLD_SERVICEBUSY() == FALSE)
                            {
                                /* no need to check the environment condition, Directly call the service */
                                if(adrService_pcst->service_handler_fp != NULL_PTR)
                                {
                                    s_dataNrc_u8 =0x00;
                                    /* Call the service based on whether it uses cooperative scheduler */
                                    DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE_FIRSTCALL((Dcm_SrvOpstatus_u8),( adrService_pcst), (&s_dataNrc_u8))
                                    Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                                }
                            }
                        }
#endif
                    }

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
                    else
                    {
                        /* Set the state to PENDING so that the request is processed in next cycle */
                        Dcm_DsldGlobal_st.stDsdState_en = DSD_VERIFY_DATA_PENDING;
                    }
#endif
                }
            }
            /* If the DcmAppl API DcmAppl_UserServiceModeRuleService returns any other value other than E_OK or an NRC value, proceed further to the processing of the service */
            else
            {
                /* If NRC is not set by application */
                if(dataNrc_u8==0x00)
                {
                    dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
        }
        else
        {
            /* send negative response, with NRC 'security not allowed' */
            dataNrc_u8 = DCM_E_SECURITYACCESSDENIED;
        }
    }
    else
    {
        /* send negative response, with NRC 'session not supported' */
        dataNrc_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].nrc_sessnot_supported_u8;

    }

    if(Dcm_DsldGlobal_st.stDsdState_en == DSD_VERIFY_DIAGNOSTIC_DATA)
    {
        /* set response given by DSD to true */

        Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
        /* Check if the NRC is set */
        if(dataNrc_u8 != 0x00u)
        {
            Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,dataNrc_u8);
        }
        Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st);
    }
}

/**
 **************************************************************************************************
 * Dcm_DsldManufacturerNotification_u8 : Function to call DcmAppl_ManufacturerNotification function for
 * manufacturer specific checks
 *
 * \param
 * \retval          Std_ReturnType (E_OK,E_NOT_OK)
 * \seealso
 * \usedresources

 **************************************************************************************************
 */
#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
static FUNC(Std_ReturnType,DCM_CODE) Dcm_DsldManufacturerNotification_u8(void)
{
    VAR(uint8,AUTOMATIC) dataNrc_u8;          /* Variable to store error code */
    VAR(Std_ReturnType,AUTOMATIC) dataManufacturerResult_u8;
    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrActiveProtocolTable_pcst;
    P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA) adrRxBuffer_pu8;

    dataNrc_u8 = 0x00;
    dataManufacturerResult_u8 = E_OK;
    /* Multicore: No lock needed here as Dsl state read is an atomic operation.
     * When this part of the code is reached when active request is being processed, so there is no chance that the DSL state is
     * modified in parallel as new requests are accepted only when DCM is free. Also the DSL states transitions only happens in
     * Dcm_MainFunction when there is a request active.*/
    if(Dcm_DsldGlobal_st.stDslState_en != DSL_ROETYPE1_RECIEVED)
    {
        /* Get the address of protocol table to local pointer */
        adrActiveProtocolTable_pcst = &(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]);

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
#else
        adrRxBuffer_pu8 = &(adrActiveProtocolTable_pcst->rx_buffer1_pa[0]);
#endif
        /* Get the SID from request*/
        Dcm_DsldGlobal_st.dataSid_u8 = adrRxBuffer_pu8[0];

        Dcm_DsldMsgContext_st.idContext = Dcm_DsldGlobal_st.dataSid_u8;

        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
           there is no parallel writing due to DSL state machine handling */
        Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                   there is no parallel writing due to DSL state machine handling */
        /* Get the request type */
        if(Dcm_DsldGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)
        {
            Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
        }
        else
        {
            Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
        }

        /* By default make the response type as Positive response */
        Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;

        /* Fill the request length excluding SID */
        Dcm_DsldMsgContext_st.reqDataLen = (Dcm_MsgLenType)Dcm_DsldGlobal_st.dataRequestLength_u16 - 0x01u;

        /* Fill the Rx buffer pointer excluding SID */
        Dcm_DsldMsgContext_st.reqData = &(adrRxBuffer_pu8[1]);


        dataManufacturerResult_u8 = Dcm_ManufacturerNotification(Dcm_DsldGlobal_st.dataSid_u8,
                                                           Dcm_DsldMsgContext_st.reqData,
                                                           (uint16)Dcm_DsldMsgContext_st.reqDataLen,
                                                           Dcm_DsldMsgContext_st.msgAddInfo.reqType,
                                                           Dcm_DsldMsgContext_st.dcmRxPduId,
                                                           Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                                                           &dataNrc_u8);


            if(dataManufacturerResult_u8 == DCM_E_REQUEST_NOT_ACCEPTED)
            {

                /*suppressPosResponse flag is set to True in the requested DSL states */
                Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
                /* Set the result to E_NOT_OK to ignore the request */

                dataManufacturerResult_u8 = E_NOT_OK;
            }

        if(dataManufacturerResult_u8 == E_NOT_OK)
        {
            /* response given by DSD itself */
            /*Set the data response given by DSD to True*/
            Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;

            /* Check if the negative response is set */
            if(dataNrc_u8 != 0x00u)
            {
                Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,dataNrc_u8);
            }

            Dcm_ProcessingDone ( &Dcm_DsldMsgContext_st);
        }
    }
    return(dataManufacturerResult_u8);
}
#endif

/**
 **************************************************************************************************
 * Dcm_DsldSearchDataSid_u8 - Linear search to find out the element(Key, SID) in the array of structure
 *
 * \param           nrElements_u8 - Number of elements,
 *
 * \retval          dataSid_cu8 -  index of the key in array of structure.
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(uint8,DCM_CODE) Dcm_DsldSearchDataSid_u8( VAR(uint8, AUTOMATIC) nrElements_u8, CONST(uint8, AUTOMATIC) dataSid_cu8)
{
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;

    for(idxIndex_qu8 = 0x00u; idxIndex_qu8 < nrElements_u8; idxIndex_qu8++)
    {
        if(Dcm_DsldSrvTable_pcst[idxIndex_qu8].sid_u8 == dataSid_cu8)
        {
            break;
        }
    }
    return((uint8)idxIndex_qu8);
}



/**
 **************************************************************************************************
 * Dcm_DsldCallServiceIni - Calling the Initialisations of all services in the
 active service table
 *
 * \param           idxSrvTable_u8 : Id of the service table to be initialised
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldCallServiceIni (VAR(uint8, AUTOMATIC) idxSrvTable_u8)
{
    /* Pointer to the service table */
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSrvTable_pcst;
    VAR(uint8_least,AUTOMATIC) idxIndex_qu32;
    /* number of services in Service table */
    VAR(uint8,AUTOMATIC) nrServices_u8;
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    /* Pending requests to be processed in cooperative scheduler */
    VAR(uint8,AUTOMATIC) flgPendingRequest_u8;
    flgPendingRequest_u8 = Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8;
#endif


    /* get the number of services in the service table and service table */
    nrServices_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[idxSrvTable_u8].num_services_u8;

    adrSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[idxSrvTable_u8].ptr_service_table_pcs;

    /* call the initialisations of all services in the service table */
    for(idxIndex_qu32 = nrServices_u8; idxIndex_qu32 != 0x0u  ; idxIndex_qu32--)
    {
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
        /* If there is a request to shift the call of service initialisation function , based on the configuration
        value mainscheduler_b, shift the service initialisation call to Dcm_CoOpr_MainFunction(),
        otherwise call from here */
        /*Check if the service initialization function pointer is not NULL and mainscheduler in the service table is set */
        if((adrSrvTable_pcst->Service_init_fp != NULL_PTR) && ((!((flgPendingRequest_u8 & DCM_DSLD_COOPSCHEDULER_INI) > 0x00u)) ||(adrSrvTable_pcst->mainscheduler_b != FALSE)))
        {
            (*adrSrvTable_pcst->Service_init_fp)();
        }
#else
        if(adrSrvTable_pcst->Service_init_fp != NULL_PTR )
        {
            (*adrSrvTable_pcst->Service_init_fp)();

        }
#endif


        adrSrvTable_pcst++;
    }
}




/**
 **************************************************************************************************
 * Dcm_DsldDsdStateMachine : State machine of DSD. this function is called in Dcm_MainFunction()
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldDsdStateMachine(void)
{
    /* Number of services */
    VAR(uint8,AUTOMATIC) nrServices_u8;
    VAR(uint8,AUTOMATIC) idxIndex_qu8;
    /* Confirmation status */
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) stConfirm_u8;
    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrActiveProtocolTable_pcst;
    P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA) adrRxBuffer_pu8;
    /* Pointer to the service table */
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrServiceTable_pcst;
#if ((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF) || (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF))
    VAR(Std_ReturnType,AUTOMATIC) dataResult_u8;
#endif
#if ((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
    /* local pointer to service configuration structure*/
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrService_pcst;
    /* Variable to store the negative response code */
    VAR(uint8,AUTOMATIC) dataNrc_u8;
#endif
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    VAR(Dcm_DsldDslStatesType_ten,  AUTOMATIC) stDslState_en;
    /* Multicore: No lock needed here as Dsl state is an atomic read operation.
     * The lock here does not make sense as if there is a parallel update then it is only possible when DSL is free
     * Its ok to work on the local copy when Dcm is free and parallel update happens
     * Also if DCM is busy there is no parallel write possible */
    stDslState_en = Dcm_DsldGlobal_st.stDslState_en;

#endif

    switch(Dcm_DsldGlobal_st.stDsdState_en)
    {
    case DSD_IDLE:

        break;

    case DSD_VERIFY_DIAGNOSTIC_DATA:

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        /* Check if the status is for ROE requested service */
        if(stDslState_en == DSL_ROETYPE1_RECIEVED)
        {
            /* Pointer Tx buffer */
            Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = Dcm_DsldRoeRdpi_pcst->txbuffer_ptr;

            /* Fill the maximum possible response length */
            Dcm_DsldMsgContext_st.resMaxDataLen = Dcm_DsldRoeRdpi_pcst->txbuffer_length_u32 - 0x01uL;

            /* Get the Rx buffer */
            adrRxBuffer_pu8 = Dcm_DsldRoeRdpi_pcst->txbuffer_ptr;

            /* Start ROE timer */
            DCM_TimerStart(Dcm_DsldGlobal_st.dataRoeRdpiTimeout_u32,DCM_CFG_ROERDPI_TIMEOUT,Dcm_RoerdpiStartTick_u32,Dcm_RoeRdpiType1TimerStatus_uchr)

        }
        else
#endif
        {
            /* Get the address of protocol table to local pointer */
            adrActiveProtocolTable_pcst = &(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]);

            /* Pointer to the Tx buffer */
            Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = adrActiveProtocolTable_pcst->tx_buffer_pa;

            /* Fill the maximum possible response length */
            Dcm_DsldMsgContext_st.resMaxDataLen = adrActiveProtocolTable_pcst->tx_buffer_size_u32 - 0x01u;

            /* tester requested service */
            Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_UDS_TESTER_SOURCE;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
            adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
#else
            adrRxBuffer_pu8 = &(adrActiveProtocolTable_pcst->rx_buffer1_pa[0]);
#endif
        }
        /* Initialise the service locater bit */
        /*Data response given by DSD is set to False*/
        Dcm_DsldGlobal_st.dataResponseByDsd_b = FALSE;

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
        dataResult_u8 = Dcm_DsldManufacturerNotification_u8();
        if(dataResult_u8 == E_OK)
#endif
        {
            /* Store SID in a global variable */
            Dcm_DsldGlobal_st.dataSid_u8 = adrRxBuffer_pu8[0];

            /* Index of requested service is initialised to zero */
            Dcm_DsldGlobal_st.idxService_u8 = 0x00u;

            /*  Make the Positive response as the default response */
            Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;

            /* Response length (filled by the service) */
            Dcm_DsldMsgContext_st.resDataLen = 0x0u;

            Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x00u;

            nrServices_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;

            /* Search the SID in active SID table  */
            idxIndex_qu8 = Dcm_DsldSearchDataSid_u8(nrServices_u8,Dcm_DsldGlobal_st.dataSid_u8);

            /* Fill the message context structure with proper data */
            /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
               there is no parallel writing due to DSL state machine handling */
            Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;
            if(idxIndex_qu8 != nrServices_u8)
            {
                /* Id context is used as SID */
                Dcm_DsldMsgContext_st.idContext = Dcm_DsldGlobal_st.dataSid_u8;

#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
                if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE)
                {
                    /* For RDPI, re-write SID as 0x2A because 0x22 is just for simulation to read data */
                    /* On bus periodic response should go with SID 0x2A                               */
                    Dcm_DsldGlobal_st.dataSid_u8 = 0x2A;
                }
#endif

                /* SID found here, store the index of requested service */
                Dcm_DsldGlobal_st.idxService_u8 = idxIndex_qu8;

                /* Fill the addressing mode info (physical or functional) */
                /* For RDPI it is always Physical                        */
                /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                   there is no parallel writing due to DSL state machine handling */
                if((Dcm_DsldGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)&&
                        (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE))
                {
                    Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
                }
                else
                {
                    Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
                }

                /* Fill the request length excluding SID */
                Dcm_DsldMsgContext_st.reqDataLen = (Dcm_MsgLenType)Dcm_DsldGlobal_st.dataRequestLength_u16 - 0x01u;

                /* Fill the Rx buffer poniter excluding SID */
                Dcm_DsldMsgContext_st.reqData = &(adrRxBuffer_pu8[1]);

                /* Fill the Tx buffer pointer */
                Dcm_DsldMsgContext_st.resData = &(Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[3]);

                /* Check the session and security then call the service */
                Dcm_DsldVerifyData();
            }
            else
            {
                /* Response given by DSD itself */
                /*Data response given by DSD is set to True*/
                Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;

#if(DCM_CFG_RESPOND_ALLREQUEST == DCM_CFG_OFF)
                /* Check whether the configured service is in proper range as specified in SWS */
                if(((Dcm_DsldGlobal_st.dataSid_u8 < 0x40u) || (Dcm_DsldGlobal_st.dataSid_u8 > 0x7fu))
                        && (Dcm_DsldGlobal_st.dataSid_u8 < 0xc0u)
                )
                {
                    /* Send negative response with NRC service not supported because non configured service is in proper range */
                    Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,DCM_E_SERVICENOTSUPPORTED);
                }
                else
                {
                    /* SID is out of range, ignore the request */
                    /*Set the suppressPosResponse flag is set to True*/
                    Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
                }
#else
                /* Send negative response for all range of SID with NRC service not supported because non configured service */
                Dcm_SetNegResponse( & Dcm_DsldMsgContext_st,DCM_E_SERVICENOTSUPPORTED);
#endif
                Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st );
            }
        }
        break;
#if ((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
    case DSD_VERIFY_DATA_PENDING:
    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
/* Take the request only if ROE Type2 state mcahine is free OR ROE Type2 is not processing the DID service/same service */

    if((Dcm_DsdRoe2State_en == DSD_IDLE) || (Dcm_ChkIfDidServiceIsActive(Dcm_DsldGlobal_st.dataSid_u8,Dcm_Roe2MesContext_st.idContext)))
    #endif
    {
        /* Initialize the nrc value*/
        dataNrc_u8 = 0x00;
        /* get the active service configuration structure */
        adrService_pcst = &(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]);

    #if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
        /* For ROE requested request no need to call this Appl function */
        /* Multicore: No lock needed here as Dsl state read is an atomic operation.
         * When this part of the code is reached when active request is being processed, so there is no chance that the DSL state is
         * modified in parallel as new requests are accepted only when DCM is free. Also the DSL states transitions only happens in
         * Dcm_MainFunction when there is a request active.*/
        if(Dcm_DsldGlobal_st.stDslState_en != DSL_ROETYPE1_RECIEVED)
        {
            /* call the Appl callback function to check the permission before calling the service */
            dataResult_u8 = Dcm_SupplierNotification(   Dcm_DsldGlobal_st.dataSid_u8,
                    Dcm_DsldMsgContext_st.reqData,
                    (uint16)Dcm_DsldMsgContext_st.reqDataLen,
                    Dcm_DsldMsgContext_st.msgAddInfo.reqType,
                    Dcm_DsldMsgContext_st.dcmRxPduId,
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                    &dataNrc_u8);
            if(dataResult_u8 == E_OK)
            {
                if(dataNrc_u8==0x00)
                {
                    /* If subfunction is supported and subservices are configured in DSD */
                    /*Check if the subfunction_exist is supported for the requested service */
                    if(adrService_pcst->subfunction_exist_b != FALSE)
                    {
                        /* Call the API to do sub-function related checks */
                        Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
                    }
                }
                if(dataNrc_u8==0x00)
                {
                    /* change the DSD state to call service state */
                    Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
                    /* If an ROE Type 2 Event is not being processed */
                    
                    /*Check if DCM_DSLD_SERVICEBUSY is set to False */
                    if(DCM_DSLD_SERVICEBUSY() == FALSE)
                    {
                        if(adrService_pcst->service_handler_fp != NULL_PTR)
                        {
                            /* Call the service based on whether it uses cooperative scheduler */
                            /* ROE service will always configure mail scheduler, hence ROE service is always
                                   called from here  */
                            DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE_FIRSTCALL(Dcm_SrvOpstatus_u8,adrService_pcst,&s_dataNrc_u8)
                            Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                        }
                    }
                }
            }
            else if(dataResult_u8 == DCM_E_REQUEST_NOT_ACCEPTED)
            {
                /*Data response given by DSD is Set to True*/
                Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
                if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0x00)
                {
                    /* request is not accepted, Ignore the request. Move the DSD and DSL to default state */
                    /* to reset the DSL, simulate suppress positive response */
                    /*suppressPosResponse flag is set to True*/
                    Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = TRUE;
                }
                else
                {
                    /* Set the NRC code */
                    Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,DCM_E_GENERALREJECT);
                }
                /* Finish processing */
                Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st);
                /* Set the NRC value to 0x0 so that Dcm_ProcessingDone is not called below again */
                dataNrc_u8 = 0x0;
            }
            else if((dataResult_u8 == DCM_E_PENDING) && (dataNrc_u8==0x00))
            {
                /* Do nothing, wait for next cycle*/
            }
            else
            {
                /* Do nothing NRC is already updated */
            }
        }
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        else
        {
            /* If subfunction is supported and subservices are configured in DSD */
            /*Check if the subfunction_exist is supported in the requested service */
            if(adrService_pcst->subfunction_exist_b != FALSE)
            {
                /* Call the API to do sub-function related checks */
                Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
            }
            if(dataNrc_u8==0x00)
            {
                /* change the DSD state to call service state */
                Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
                /* If an ROE Type 2 Event is not being processed */
                /*Check if the DCM_DSLD_SERVICEBUSY flag is to False*/
              
                if(DCM_DSLD_SERVICEBUSY() == FALSE)
                {
                    if(adrService_pcst->service_handler_fp != NULL_PTR)
                    {
                        Dcm_retVal_u8=(*adrService_pcst->service_handler_fp)( Dcm_SrvOpstatus_u8,& Dcm_DsldMsgContext_st,&s_dataNrc_u8);
                        /*Invoke the response transmission API handling*/
                        Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                    }
                }
            }
        }
#endif /* End of #if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)) */
    #else /* Else for #if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF) */
        /* If subfunction is supported and subservices are configured in DSD */
        /*Check if the subfunction_exist is supported in the requested service*/
        if(adrService_pcst->subfunction_exist_b != FALSE)
        {
            /* Call the API to do sub-function related checks */
            Dcm_Dsld_CheckSubFunction(&Dcm_DsldMsgContext_st,adrService_pcst,&dataNrc_u8);
        }
        if(dataNrc_u8==0x00)
        {
            /* change the DSD state to call service state */
            Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
            /* If an ROE Type 2 Event is not being processed */
            /*Check if the DCM_DSLD_SERVICEBUSY flag is to False*/
          
            if(DCM_DSLD_SERVICEBUSY() == FALSE)
            {
                if(adrService_pcst->service_handler_fp != NULL_PTR)
                {
                    Dcm_retVal_u8=(*adrService_pcst->service_handler_fp)( Dcm_SrvOpstatus_u8,& Dcm_DsldMsgContext_st,&s_dataNrc_u8);
                    /*Invoke the response transmission API handling*/
                    Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);
                }
            }
        }
    #endif
        /* Check if the NRC is set */
        if(dataNrc_u8 != 0x00u)
        {
            /* set response given by DSD to true */
            /*Set the data response given by DSD is set to True*/
            Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
            Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,dataNrc_u8);
            Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st);
        }
    }
    break;
#endif
    case DSD_CALL_SERVICE:

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
        /* Paged buffer timeout monitoring */
        Dcm_DsldPagedBufferTimeout();
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        Dcm_DsldRoeRdpiTimeOut();
#endif
        /* If an ROE Type 2 Event is not being processed */
        /*Check if the DCM_DSLD_SERVICEBUSY flag is set to false*/
      
        if(DCM_DSLD_SERVICEBUSY() == FALSE)
        {
            /* If state of DSD is changed (by above function call) then no need to call service */

            if(Dcm_DsldGlobal_st.stDsdState_en == DSD_CALL_SERVICE)
            {
                adrServiceTable_pcst = &Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8];

                     /* Check whether the service exists in DSP or not */
                    /* Service exist in DSP. Call the service again  */
                    /* (scheduling of the DSP services done by the DCM proc only) */
                    /* Call the service based on whether it uses cooperative scheduler */
                    DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE(Dcm_SrvOpstatus_u8,adrServiceTable_pcst,&s_dataNrc_u8)

                    Dcm_DsldInitiateResponseTransmission(Dcm_retVal_u8);


            }
        }
        break;

    case DSD_SEND:

        /* Lower layer is sending the data, wait till confirmation comes from PduR */
        break;

    case DSD_TX_CONFIRMATION:
        /* Check whether the previous response is sent successfully */
        if(Dcm_DsldGlobal_st.dataResult_u8 == E_OK)
        {
            if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)
            {
                /* Positive response sent successfully */
                stConfirm_u8 = DCM_RES_POS_OK;
            }
            else
            {
                /* Negative response sent successfully */
                stConfirm_u8 = DCM_RES_NEG_OK;
            }
        }
        else
        {
            if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE )
            {
                /* Unable to send positive response */
                stConfirm_u8 = DCM_RES_POS_NOT_OK;
            }
            else
            {
                /* Unable to send negative response */
                stConfirm_u8 = DCM_RES_NEG_NOT_OK;
            }
        }

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
        /*Check if paged buffer flag is active*/
        if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
        {
            /* Full response is sent on Paged buffer */
            /*Set the paged buffer flag to False*/
            Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;

            if(stConfirm_u8 == DCM_RES_POS_NOT_OK)
            {
                /* If during the transmission of Paged buffer, error occurred in lower layer */
                /* Since service is not finished the processing, call callback application. */
                DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);
            }
        }
#endif

        if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)
        {
            /* Check if the response is given by service or not */
            /*Check if data response given by DSD is set to False*/
            if(Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE)
            {
                /* Response is given by service and service wants confirmation */
                /* hence DSLD has to call Tx confirmation                      */
                /*Check if the servicelocator is set set to True*/
                if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].servicelocator_b != FALSE)
                {
                    /* Service exists in DSP. Give the confirmation to DSP */
                    Dcm_DspConfirmation(Dcm_DsldMsgContext_st.idContext,
                            Dcm_DsldMsgContext_st.dcmRxPduId,
                            Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                            stConfirm_u8);

                }
                else
                {
                    /* Service exists out side the DSP. Give the confirmation to Application */
                    DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                            Dcm_DsldMsgContext_st.dcmRxPduId,
                            Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                            stConfirm_u8);
                }

            }
            else
            {
#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)

                if ((stConfirm_u8 == DCM_RES_NEG_OK) || (stConfirm_u8 == DCM_RES_NEG_NOT_OK))
                {
                    /* Negative response created inside DSD. Give separate confirmation to application. */
                    DcmAppl_DcmConfirmation_DcmNegResp(Dcm_DsldMsgContext_st.idContext,
                            Dcm_DsldMsgContext_st.dcmRxPduId,
                            stConfirm_u8);
                }
#endif
                /*Check if the max number of configured NRC 0x78 is transmitted*/
                if(Dcm_DsldGenRejectSent_b != FALSE)
                {
                    DcmAppl_DcmConfirmation_GeneralReject(Dcm_DsldMsgContext_st.idContext,
                            Dcm_DsldMsgContext_st.dcmRxPduId,
                            stConfirm_u8);
                    /* Reset the variable to FALSE */
                    /*Set the Dcm_DsldGenRejectSent flag is to False*/
                    Dcm_DsldGenRejectSent_b = FALSE;
                }

                if ((stConfirm_u8 == DCM_RES_POS_OK) || (stConfirm_u8 == DCM_RES_POS_NOT_OK))
                {
                    /* Service exist out side the DSP. Give the confirmation to Application */
                    DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                            Dcm_DsldMsgContext_st.dcmRxPduId,
                            Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                            stConfirm_u8);
                }


            }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            Dcm_CallRTEConfirmation(stConfirm_u8);
#endif



        }
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        else
        {
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
            if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
            {
                if(Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed !=FALSE)
                {
                    Dcm_DcmDspEventQueue[DcmRoeQueueIndex_u8].Is_Processed = FALSE;
                }
            /* Change the service table to original active table */
            Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
                        Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
            }
#endif

            if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
            {
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
                /* Give the confirmation to application */
               DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                        Dcm_DsldMsgContext_st.dcmRxPduId,
                        Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16,
                        stConfirm_u8);
#endif
            }
            else
            {
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
                /* Give the confirmation to application */
                DcmAppl_DcmConfirmationRDPI(0x2A,
                        Dcm_DsldMsgContext_st.dcmRxPduId,
                        stConfirm_u8);
#endif
            }

        }
#endif


        /* Change the DSD state to Idle state */
        Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;
        break;

    default:
        /*Since All the DSD states are handled already , there is nothing to do in Default */
        break;
    }
}

/**
 **************************************************************************************************
 * Dcm_Dsld_CheckSubFunction : Function to do subservice specific checks in DSD
 *
 * \param           Msgcontext_s       - Pointer to Message structure
 *                  service_pcs        - Pointer to the service configuration structure
 *                  ErrorCode_u8       - Variable to  store negative response code
 *
 * \retval          void
 * \seealso
 * \usedresources

 **************************************************************************************************
 */
 FUNC(void,DCM_CODE) Dcm_Dsld_CheckSubFunction (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) Msgcontext_s,
                                                P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) service_pcs,
                                                P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) ErrorCode_u8 )
{
    /* Index to loop through the sub-service table */
    VAR(uint8,AUTOMATIC) idxSubservice_u8;
    /* Variable to store the sub-function byte from the request */
    VAR(uint8,AUTOMATIC) dataSubfunction_u8;
    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC) retVal_u8;
    /* bit mask to represent session */
    VAR(uint32,AUTOMATIC) dataSessionActive_u32;
    /* bit mask to represent security */
    VAR(uint32,AUTOMATIC) dataSecurityActive_u32;
    /* local pointer to sub-service configuration structure*/
    P2CONST(Dcm_Dsld_SubServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSubservice_pcst;

    /* Reset the error code to 0x00 */
    *ErrorCode_u8=0x00;
    /* Check if there is at least one byte (sub function byte) exists */
    if(Msgcontext_s->reqDataLen > 0x00u)
    {
        /* Get the sub service configuration structure */
        adrSubservice_pcst= service_pcs->ptr_subservice_table_pcs;

        /* If sub services are configured in DSD for the service */
        if((service_pcs->num_sf_u8 != 0) && (adrSubservice_pcst!=NULL_PTR))
        {
            /* Get the sub-service byte from the request */
            dataSubfunction_u8=Msgcontext_s->reqData[0];
            if(Dcm_DsldGlobal_st.dataSid_u8 ==0x86)
            {
                dataSubfunction_u8 =  (dataSubfunction_u8 & ((uint8)(~(0x40u))));
            }

            /* Search if the sub-service in request is configured for the requested service */
            for(idxSubservice_u8=0;idxSubservice_u8<service_pcs->num_sf_u8;idxSubservice_u8++)
            {
                if(dataSubfunction_u8==adrSubservice_pcst[idxSubservice_u8].subservice_id_u8)
                {
                    break;
                }
            }

            /* If sub service is configured*/
            if(idxSubservice_u8<service_pcs->num_sf_u8)
            {
                /* Generate bit mask for active session */
                dataSessionActive_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSession_u8);

                /* Check requested sub service is allowed in this session */
                if((adrSubservice_pcst[idxSubservice_u8].allowed_session_b32 & dataSessionActive_u32)== (dataSessionActive_u32))
                {

                    /* generate bit mask for active security level */
                    dataSecurityActive_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSecurity_u8);

                    /* Check if the requested sub-service is allowed in current security */
                    if((adrSubservice_pcst[idxSubservice_u8].allowed_security_b32 & dataSecurityActive_u32)== (dataSecurityActive_u32))
                    {
                        if(adrSubservice_pcst[idxSubservice_u8].adrUserSubServiceModeRule_pfct !=NULL_PTR)
                        {
                            /* Call the configured Call back to do checks on the subfunction */
                            retVal_u8 =(*adrSubservice_pcst[idxSubservice_u8].adrUserSubServiceModeRule_pfct)(ErrorCode_u8,Dcm_DsldGlobal_st.dataSid_u8,dataSubfunction_u8);
                        }
                        else
                        {
                            /* Call the Dcm Appl Call back to do checks on the subfunction */
                            retVal_u8 =DcmAppl_UserSubServiceModeRuleService(ErrorCode_u8,Dcm_DsldGlobal_st.dataSid_u8,dataSubfunction_u8);
                        }

                        /* If the function returns any other value other than E_OK or a set NRC value */
                        if (retVal_u8!=E_OK)
                        {
                            /* If error code is not set by the application in case of values other than E_OK */
                            if(*ErrorCode_u8 ==0x00)
                            {
                                *ErrorCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            }
                        }
                        else
                        {
                            *ErrorCode_u8=0;
                        }
#if(DCM_CFG_DSD_MODERULESUBFNC_ENABLED != DCM_CFG_OFF)
                        /* Check if the mode rule is configured for the sub function */
                        if ((*ErrorCode_u8 ==0x00) && (adrSubservice_pcst[idxSubservice_u8].moderule_fp != NULL_PTR) )
                        {
                            /* Call the mode rule API configured */
                            (boolean)(*adrSubservice_pcst[idxSubservice_u8].moderule_fp)(ErrorCode_u8);
                        }
#endif
                    }
                    /* If sub service is not allowed in  current security */
                    else
                    {
                        *ErrorCode_u8 = DCM_E_SECURITYACCESSDENIED;
                    }
                }
                /* If sub service is not allowed in current session */
                else
                {
                    *ErrorCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
                }
            }
            /* If the sub service is not supported */
            else
            {
                *ErrorCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
    }
    else
    {
        /* If service is outside DSP */
        /*Set the servicelocator flag is set to False*/
        if(service_pcs->servicelocator_b==FALSE)
        {
            /* Call the DcmAppl API to get the NRC to be returned in case minimum length check  fails for project/vendor specific services  */
            DcmAppl_DcmGetNRCForMinLengthCheck(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8,service_pcs->sid_u8,ErrorCode_u8);
        }
        /* Check if the NRC to be returned is updated by application */
        if (*ErrorCode_u8 ==0x00)
        {
            /* Set NRC to 0x13 as sub function byte is missing in the service request */
            *ErrorCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
        else
        {
            /* Do nothing. ErrorCode is already set  */
        }
    }
#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
    /*Check if Error Code is supported for the requested service shall have sid 0x27 and servicelocator is set to True */
    if((*ErrorCode_u8!=0x00u) && (service_pcs->sid_u8==0x27u) && (service_pcs->servicelocator_b!=FALSE))
    {
        /* To Reset the stored AccessType when the NRC is returned for Seca Service(0x27) from DsdStateMachine*/
        Dcm_ResetAccessType();

    }
#endif
}

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
 /**
  ************************************************************************************************************************
  * Dcm_CallRTEConfirmation : Function to give the confirmation to Supplier/Manufacturer in case the RTE is enabled
  * \param           None
  *
  *
  * \retval          None
  * \seealso
  * \usedresources
  ************************************************************************************************************************
  */
FUNC(void,DCM_CODE) Dcm_CallRTEConfirmation(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) stConfirm_u8)
{
                     VAR(uint8,AUTOMATIC) idxIndex_qu8;
#if((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_MANUNOT_NUM_PORTS != 0))
                    for(idxIndex_qu8=0x00; idxIndex_qu8<DCM_CFG_MANUNOT_NUM_PORTS; idxIndex_qu8++)
                    {
                        (void)(*Dcm_Rte_ManufacturerConfirmation_a[idxIndex_qu8])(Dcm_DsldMsgContext_st.idContext,
                                                                                Dcm_DsldMsgContext_st.msgAddInfo.reqType,
                                                                                Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                                                                                stConfirm_u8);
                    }
#endif
#if((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED!=DCM_CFG_OFF) && (DCM_CFG_SUPPNOT_NUM_PORTS !=0))
                    for(idxIndex_qu8=0x00; idxIndex_qu8<DCM_CFG_SUPPNOT_NUM_PORTS; idxIndex_qu8++)
                    {
                        (void)(*Dcm_Rte_SupplierConfirmation_a[idxIndex_qu8])(Dcm_DsldMsgContext_st.idContext,
                                                                                Dcm_DsldMsgContext_st.msgAddInfo.reqType,
                                                                                Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                                                                                stConfirm_u8);
                    }
#endif
                    (void)idxIndex_qu8;
}
#endif

#if((DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) || ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ))
 /**
  **************************************************************************************************
  * Dcm_DsldDspModeStateMachine : This function is called in Dcm_MainFunction()
  * This function checks for the mode condition.
  *
  * \param           None
  *
  *
  * \retval          None
  * \seealso
  * \usedresources
  **************************************************************************************************
  */
 FUNC(void,DCM_CODE) Dcm_DsldDspModeStateMachine(void)
{
#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
     Dcm_CDTCModeStatusCheck();
#endif

}


#endif
/**
**************************************************************************************************
* Dcm_DsldInitiateResponseTransmission :
* The  function is a generic library introduced to invoke the triggering of positive, negative
* response or Response Pending operation (NRC0x78) or PENDING return
* \param           retVal_u8    :   Type of operation to be carried out
*
* \retval          None
*
**************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_DsldInitiateResponseTransmission(VAR(Std_ReturnType,AUTOMATIC) retVal_u8)
{
    if(retVal_u8 == E_OK)
    {
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        /*Trigger transmission of positive response*/
        Dcm_ProcessingDone (&Dcm_DsldMsgContext_st);
    }
    else if (retVal_u8 == DCM_E_PENDING)
    {
        /*Do nothing here, The Global  Opstatus will be set to required state by the service*/
    }
    else if (retVal_u8 == DCM_E_FORCE_RCRRP)
    {
        /*Do we need to tigger a force response pend*/
        if(Dcm_ForceRespPend() == E_OK)
        {
            /*Do nothing here, The Global  Opstatus will be set to required state by the service*/
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
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        /*Trigger transmission of negative response*/
        Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,s_dataNrc_u8);
        Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st);
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

