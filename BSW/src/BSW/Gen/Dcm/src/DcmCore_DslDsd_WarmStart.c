

#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Programming conditions information */
VAR(Dcm_ProgConditionsType,DCM_VAR) Dcm_ProgConditions_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 VAR(boolean,DCM_VAR) Dcm_SesChgOnWarmResp_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetActiveConnectionIdx_u8 : To retrieve the "Connection" Index of to be started Protocol so as
 * to inform ComM for Active Diagnosis
 * This Index is to be retrieved only in case of Warm request/Warm Response
 * \param           None
 * \retval          uint8 - Index to Connection of "to-be-started" Protocol
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(uint8,DCM_CODE) Dcm_GetActiveConnectionIdx_u8 (void)
{
    VAR(uint8_least,AUTOMATIC)  idxProtcol_qu8;      /* Protocol index used in search loop */
    VAR(uint8_least,AUTOMATIC)  idxSession_qu8;      /* Session index used in search loop */
    VAR(uint8_least,AUTOMATIC)  idxIndex1_qu8;
    VAR(uint8_least,AUTOMATIC)  idxIndex2_qu8;
    VAR(uint8, AUTOMATIC)       idxConn_u8;
    idxConn_u8 = 0;


    /* Search all protocols available to start matching protocol */
    for (idxProtcol_qu8 = 0; idxProtcol_qu8 < DCM_CFG_NUM_PROTOCOL; idxProtcol_qu8++)
    {
        if (Dcm_ProgConditions_st.ProtocolId == Dcm_DsldProtocol_pcst[idxProtcol_qu8].protocolid_u8)
        {   /* Matching protocol found */
            break;
        }
    }
    /* Check if there was a matching protocol */
    if (idxProtcol_qu8 >= DCM_CFG_NUM_PROTOCOL)
    {   /* Matching protocol was not found, use the first protocol configured to restore information */
        idxProtcol_qu8 = 0;
        for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_CONN; idxIndex1_qu8++)
        {   /* Check for the connection which has protocol index as 0 */
            if(Dcm_DsldConnTable_pcst[idxIndex1_qu8].protocol_num_u8 == 0x0)
            {   /* Loop to get the Tester Address of first connection in protocol index 0 */
                break;
            }
        }
    }

    /* Find the programming session */
    for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
    {   /* Check whether the Session is configured */
        if (Dcm_ProgConditions_st.SessionLevel == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
        {   /* Matching session found */
            break;
        }
    }
    if (idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
    {
        /* Set the protocol index first */
        Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = (uint8)idxProtcol_qu8;

        /* Find the connection index of the protocol to start */
        for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_RX_PDUID; idxIndex1_qu8++)
        {   /* Check the connection of the protocol belongs to the restored protocol */
            if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].protocol_num_u8 == idxProtcol_qu8)
            {   /* Check if the tester address matches */
                if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].testaddr_u16 == Dcm_ProgConditions_st.TesterSourceAddr)
                {   /* Update the active connection variable */
                    idxConn_u8 = Dcm_DsldRxTable_pcu8[idxIndex1_qu8];
                    break;
                }
            }
        }
        /* If the Tester address restored is invalid / not configured*/
        if(idxIndex1_qu8 >= DCM_CFG_NUM_RX_PDUID)
        {   /* Get the tester address from the first connection of this protocol */
            for(idxIndex2_qu8=0; idxIndex2_qu8<DCM_CFG_NUM_CONN; idxIndex2_qu8++)
            {   /* If the protocol matches */
                if(Dcm_DsldConnTable_pcst[idxIndex2_qu8].protocol_num_u8 == idxProtcol_qu8)
                {   /* Assign the first connection */
                    idxConn_u8 = (uint8)idxIndex2_qu8;
                    break;
                }
            }
        }
    }
    else
    {
        idxConn_u8 = 0;
    }
    return idxConn_u8;
}

/**
 **************************************************************************************************
 * Dcm_DslDsdWarmStart : Warm Start initialization of DCM module.
 * This initialization is required only in case of Warm request/ Warm Init/ Warm Response
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DslDsdWarmStart(void)
{
    VAR(uint8_least,AUTOMATIC)  idxProtcol_qu8;      /* Protocol index used in search loop */
    VAR(uint8_least,AUTOMATIC)  idxSession_qu8;      /* Session index used in search loop */
    VAR(uint8,      AUTOMATIC)  dataSessionId_u8;      /* Session ID value */
    VAR(uint8_least,AUTOMATIC)  nrReqLength_qu8;    /* Length of the request */
    VAR(uint8_least,AUTOMATIC)  idxIndex1_qu8;
    VAR(uint8_least,AUTOMATIC)  idxIndex2_qu8;
    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) protocol_table_pcs; /* Pointer to protocol table */
    Dcm_SesChgOnWarmResp_b =FALSE;
    if (Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
    {
        /* Retrieve the request length information */
        nrReqLength_qu8 = Dcm_ProgConditions_st.ReqResLen;

        /* Search all protocols available to start matching protocol */
        for (idxProtcol_qu8 = 0; idxProtcol_qu8 < DCM_CFG_NUM_PROTOCOL; idxProtcol_qu8++)
        {
            if (Dcm_ProgConditions_st.ProtocolId == Dcm_DsldProtocol_pcst[idxProtcol_qu8].protocolid_u8)
            {   /* Matching protocol found */
                break;
            }
        }

        /* Check if there was a matching protocol */
        if (idxProtcol_qu8 >= DCM_CFG_NUM_PROTOCOL)
        {   /* Matching protocol was not found, use the first protocol configured to restore information */
            idxProtcol_qu8 = 0;
            /* Report development error "DCM_E_PROTOCOL_NOT_FOUND " to DET module if the DET module is enabled */
            DCM_DET_ERROR(DCM_WARMSTART_ID , DCM_E_PROTOCOL_NOT_FOUND )
            for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_CONN; idxIndex1_qu8++)
            {   /* Check for the connection which has protocol index as 0 */
                if(Dcm_DsldConnTable_pcst[idxIndex1_qu8].protocol_num_u8 == 0x0)
                {   /* Loop to get the Tester Address of first connection in protocol index 0 */
                    Dcm_ProgConditions_st.TesterSourceAddr = Dcm_DsldConnTable_pcst[idxIndex1_qu8].testaddr_u16;
                    break;
                }
            }
        }
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        if((Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET) ||  (Dcm_ProgConditions_st.Sid == 0x51))
        {
         idxSession_qu8 = DCM_DEFAULT_SESSION_IDX;
        }
        else
#endif
        {
            /* Find the programming session */
            for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
            {   /* Check whether the Session is configured */
                if (Dcm_ProgConditions_st.SessionLevel == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
                {   /* Matching session found */
                    break;
                }
            }
        }

        if (idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
        {
            /* Set the protocol index first */
            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = (uint8)idxProtcol_qu8;

            /* Find the connection index of the protocol to start */
            for(idxIndex1_qu8=0; idxIndex1_qu8 < DCM_CFG_NUM_RX_PDUID; idxIndex1_qu8++)
            {   /* Check the connection of the protocol belongs to the restored protocol */
                if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].protocol_num_u8 == idxProtcol_qu8)
                {   /* Check if the tester address matches */
                    if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex1_qu8]].testaddr_u16 == Dcm_ProgConditions_st.TesterSourceAddr)
                    {   /* Update the active connection variable */
                        Dcm_DsldGlobal_st.nrActiveConn_u8 = Dcm_DsldRxTable_pcu8[idxIndex1_qu8];
                        break;
                    }
                }
            }
            /* If the Tester address restored is invalid / not configured*/
            if(idxIndex1_qu8 >= DCM_CFG_NUM_RX_PDUID)
            {   /* Get the tester address from the first connection of this protocol */
                for(idxIndex2_qu8=0; idxIndex2_qu8<DCM_CFG_NUM_CONN; idxIndex2_qu8++)
                {   /* If the protocol matches */
                    if(Dcm_DsldConnTable_pcst[idxIndex2_qu8].protocol_num_u8 == idxProtcol_qu8)
                    {   /* Assign the first connection */
                        Dcm_DsldGlobal_st.nrActiveConn_u8 = (uint8)idxIndex2_qu8;
                        break;
                    }
                }
            }



#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
            if((Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET) ||  (Dcm_ProgConditions_st.Sid == 0x51))
            {
                /* set the session as default session */
                Dcm_DsldGlobal_st.idxActiveSession_u8 = DCM_DEFAULT_SESSION_IDX;
                /* set the default session time */
                Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
                Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
                /* lock the ECU */
                Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;

            }
            else
#endif
            {
                    /* Set the active session information */
                        Dcm_DsldGlobal_st.idxActiveSession_u8 = (uint8)idxSession_qu8;
                        /* Copy the session Id */
                        dataSessionId_u8 = Dcm_ProgConditions_st.SessionLevel;
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                        /* Get the timings of the active session */
                        Dcm_GetP2Timings(&Dcm_DsldTimer_st.dataTimeoutP2max_u32, &Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32,
                                         (Dcm_SesCtrlType)dataSessionId_u8);
#else
                        DcmAppl_DcmGetP2Timings(&Dcm_DsldTimer_st.dataTimeoutP2max_u32, &Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32,
                                                (Dcm_SesCtrlType)dataSessionId_u8);
#endif
                /* Set the security value */
                Dcm_SetSecurityLevel(Dcm_ProgConditions_st.SecurityLevel);
            }


            /* Check for Warm request type of jump */
            /*If nrRequest Length is valid and Response has to be sent by flashloader or application*/
            if ((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE) && (nrReqLength_qu8 != 0x0u) && (Dcm_ProgConditions_st.ResponseRequired != FALSE))
            {
                /* store the request length, including SID */
                Dcm_DsldGlobal_st.dataRequestLength_u16  = (uint16)nrReqLength_qu8;

                /* Get the Rx buffer and it's length */
                protocol_table_pcs = &Dcm_DsldProtocol_pcst[idxProtcol_qu8];

                /* Copy SID to the Rx buffer */
                protocol_table_pcs->rx_buffer1_pa[0] = Dcm_ProgConditions_st.Sid;
                nrReqLength_qu8--;
                /* If the sub-function is applicable */
                if(nrReqLength_qu8 > 0x0u)
                {
                    /* Copy the sub-function to Rx buffer */
                    protocol_table_pcs->rx_buffer1_pa[1] = Dcm_ProgConditions_st.SubFncId;
                    nrReqLength_qu8--;
                }
              /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
                DCM_MEMCOPY(&(protocol_table_pcs->rx_buffer1_pa[0x02]), Dcm_ProgConditions_st.ReqResBuf,nrReqLength_qu8);

                /* DcmAppl_DcmStartProtocol() is not called here as it is not a start of new protocol only a
                   a reinitialization */

                /* Mark that wait pend is sent, so that always a response goes to the tester. */
                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = Dcm_ProgConditions_st.NumWaitPend;

                /* Change the state so that the service is called in the first execution of the Dcm_MainFunction */
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues */
                Dcm_DsldGlobal_st.stDslState_en = DSL_REQUEST_RECEIVED;

                if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 != 0)
                {
                    /* Start P2* timer */

                    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                     * where P2, P3 and P2Star is involved, this is case where only P2StrMax_u32 is being accessed */
                    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
                                  (Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2StarTmrAdjust),
                                   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                }
                else
                {
                    /* Start P2 timer */

                    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                     * where P2, P3 and P2Star is involved, this is case where only P2StrMax_u32 is being accessed */
                    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
                                  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
                                   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                }
            }

           /* Check for Warm Init type of jump */
            if (Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
            {
                /* Start S3 timer */
                Dcm_StartS3MaxMonitoring();
            }

           /* Check for Warm response type of jump */
            /*If nrRequest Length is valid and Response has to be sent by flashloader or application*/
            if((Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE) && (nrReqLength_qu8 != 0x0u) && (Dcm_ProgConditions_st.ResponseRequired != FALSE))
            {

                /* Store the response length and buffer pointer */
                Dcm_DsldTransmit_st.dataTxDataLength_u32  = nrReqLength_qu8;

                /* Arrange the buffer to fill in SID and Sub-function */
                for(idxIndex1_qu8 = (nrReqLength_qu8-1u); idxIndex1_qu8 > 0x1u; idxIndex1_qu8--)
                {
                    Dcm_ProgConditions_st.ReqResBuf[idxIndex1_qu8]= Dcm_ProgConditions_st.ReqResBuf[idxIndex1_qu8-0x2u];
                }
                /* Copy the sub-function and SID */
                Dcm_ProgConditions_st.ReqResBuf[0] = Dcm_ProgConditions_st.Sid;
                Dcm_ProgConditions_st.ReqResBuf[1] = Dcm_ProgConditions_st.SubFncId;

                Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = &Dcm_ProgConditions_st.ReqResBuf[0];

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                /*Check if the service for which response to be send is DSC.check positive resp value*/
                if (Dcm_ProgConditions_st.Sid == 0x50u)
                {
                for(idxSession_qu8 = 0; idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS; idxSession_qu8++)
                        {   /* Check whether the Session is configured */
                            if (Dcm_ProgConditions_st.SubFncId == Dcm_DsldSessionTable_pcu8[idxSession_qu8])
                            {   /* Matching session found */
                                break;
                            }
                        }
                        if (idxSession_qu8 < DCM_CFG_NUM_UDS_SESSIONS)
                        {
                            Dcm_ctDiaSess_u8=(uint8)idxSession_qu8;
                            Dcm_SesChgOnWarmResp_b=TRUE;
                        }
                }
#endif
                /* DcmAppl_DcmStartProtocol() is not called here as it is not a start of new protocol only a
                   a reinitialization */

                /* Change the state so that next call of Dcm_MainFunction() send the warm response */
                /* DSD state still in IDLE because no need to give confirmation to application    */
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues */
                Dcm_DsldGlobal_st.stDslState_en = DSL_SEND_FINAL_RESPONSE;

                /* Calculate the TX PduId from active connection */
                Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].
                                                      txpduid_num_u8;
            }
            /* Communication is started */

            Dcm_DsldGlobal_st.flgCommActive_b = TRUE;

            /* Set the service table from protocol table */
            Dcm_DsldGlobal_st.datActiveSrvtable_u8= Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
                                                  sid_tableid_u8;

            /* Get the active service table pointer from Sid table*/
            Dcm_DsldSrvTable_pcst = \
                  Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

            /* Call initialisation of all services */
            Dcm_DsldCallServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);
        }
        else
        {
            /* !!!This part of code should not be reached */
            /* The programming session should used in drive should also exist in boot */
        }
        /* Check whether the application is reprogrammed*/

        if(Dcm_ProgConditions_st.ApplUpdated != FALSE)
        {
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            /* Inform BswM Module regarding the application software change*/
            BswM_Dcm_ApplicationUpdated();
#endif
            /* Clear the ApplUpdated flag*/

            Dcm_ProgConditions_st.ApplUpdated = FALSE;
         }
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
         /*Check if  Reset the reprogramming flag to TRUE */

         if(Dcm_ProgConditions_st.ReprogramingRequest != FALSE)
         {
             /*Set the reprogramming flag to FALSE*/
             Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
         }
#endif
         /* Reset the response required flag*/

         Dcm_ProgConditions_st.ResponseRequired = FALSE;
         /* Clear the Communication state descriptor and set it to INACTIVE */
         Dcm_ProgConditions_st.StoreType = DCM_NOTVALID_TYPE;
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

