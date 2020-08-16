

#include "DcmCore_DslDsd_Inf.h"

#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_SetActiveServiceTable : API used to set the new service table from the application
 *
 *
 * \param           Sid_tableid_u8: new Sid table to going to set
 *
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveServiceTable(VAR(uint8,AUTOMATIC) Sid_tableid_u8)
{
    VAR(Std_ReturnType,AUTOMATIC) dataReturnValue_u8;
    VAR(uint8,AUTOMATIC) tempNrc_u8; /* Variable used to send NegativeResponseCode Parameter in case of Dcm Cancellation */
    VAR(Std_ReturnType,AUTOMATIC) stCancelTx_u8;/* Status of cancel transmit function */


    /* check Sid table id is in valid range */
    if(DCM_CFG_NUM_SID_TABLE > Sid_tableid_u8 )
    {


        /* if the session active is non-default session then go to default session */
        if( Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX )
        {
			/* Call SchM_Switch function */
#if (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
    #if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
			(void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
	#endif
        	/* Call the DcmAppl API to inform application regarding session change */
			(void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif

            /* set the default session and default timing */
            Dcm_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);

        }
        /* Call the Cancel Transmit function to cancel ongoing transmission in Lower layers  */
        /*  Cancel The running Service   */

        if((Dcm_DsldGlobal_st.stDsdState_en!=DSD_IDLE) && (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR))
        {
            tempNrc_u8 =0x00;
            Dcm_DsldGlobal_st.dataOldtxPduId_u8 = Dcm_DsldGlobal_st.dataActiveTxPduId_u8;
            stCancelTx_u8 = Dcm_CancelTransmit_u8();
            if(stCancelTx_u8 != E_OK)
            {
                /*There is no Ongoing tranmission in lower layer*/
            }
            (void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp)(DCM_CANCEL,&Dcm_DsldMsgContext_st,&tempNrc_u8);
        }
        /*Initialize the Service state machine   */
        SchM_Enter_Dcm_Global_NoNest();
        Dcm_DsldGlobal_st.stDsdState_en =  DSD_IDLE;
        Dcm_DsldGlobal_st.stDslState_en =  DSL_READY_FOR_RECEPTION;
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        SchM_Exit_Dcm_Global_NoNest();

        /* set the new sid table id which is given by Application */
        Dcm_DsldGlobal_st.datActiveSrvtable_u8 = Sid_tableid_u8;

        /* get the active service table pointer from Sid table*/
        Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Sid_tableid_u8].ptr_service_table_pcs;

        DCM_DSLD_COOPSCHEDULER_SHIFTINI(Sid_tableid_u8)
        /* call the service initializations of new table */
        Dcm_DsldCallServiceIni(Sid_tableid_u8);

        /* setting of table is successful */
        dataReturnValue_u8 = E_OK;

    }
    else
    {
        /* Report development error "DCM_E_SERVICE_TABLE_OUTOFBOUNDS " to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_SETSRVTABLE_ID , DCM_E_SERVICE_TABLE_OUTOFBOUNDS )
        /* setting of table is unsuccessful */
        dataReturnValue_u8 = E_NOT_OK;

    }
    return(dataReturnValue_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
