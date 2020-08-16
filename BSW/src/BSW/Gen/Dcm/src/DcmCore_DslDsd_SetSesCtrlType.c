

#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/*
 ***********************************************************************************************************
 *  Dcm_SetSesCtrlType :To set the new session control type value in DCM
 *  \param   dataSesCtrlType_u8  New session control type value, Content is according to diagnosticSessionType
 *                         parameter of DiagnosticSessionControl request
 *  \retval        None
 *  \seealso
 *
 ***********************************************************************************************************/

FUNC(void,DCM_CODE) Dcm_SetSesCtrlType (VAR(Dcm_SesCtrlType, AUTOMATIC) dataSesCtrlType_u8)
{
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
    VAR(uint32,AUTOMATIC) dataSessionMask_u32;							/*Active session Mask*/
#endif
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    VAR(uint8,AUTOMATIC) nrSessions_u8;
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) idxKwpTiming_u8;
#endif
    /*Check if the Dcm Session flag is set to true */
    if(Dcm_DsldSessionflag_b == TRUE)
    {

        dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];
        /*Initialize the Dcm Session flag value to false*/
        Dcm_DsldSessionflag_b   = FALSE;
    }
    else
    {
        /* get current session */
        dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
    }
    /* session going to set is default session do the following actions (this action is not required if running */
    /* session is default session)                                                                                 */
    if(dataSesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
    {
        /* To maintain consistency between P2Max, P2StarMax, P3Max */
        SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
        /*Check if the return value is FALSE */
        if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
        {
            /* set the default session time for UDS session change */
            Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
            Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
        }
        else
        {
            /* Set the default timings after default session transition */
            idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
            Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
            Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P3_max_u32;
            Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
        }
#else
        /* set the default session time for UDS session change */
        Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
        Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
#endif
        SchM_Exit_Dcm_DsldTimer_NoNest();

        /* lock the ECU */
        Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;
        /* set the session index */
        Dcm_DsldGlobal_st.idxActiveSession_u8 = 0x00u;

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
        /**The code which would loop through all the IOCBI DIDs and call all the returncontrol to ECU functions to reset all the  active IOctrls
           supported in the current session level*/

        Dcm_ResetActiveIoCtrl(0x1,0x1,TRUE);
#endif


        /*Stopping of all the strted routines on transition to default session*/
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
        Dcm_RoutineSetSesCtrlType(dataSesCtrlType_u8);
#endif

            /*Check if transition is from NON-Default to Default session*/
        if(dataCurrentSession_u8 != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
        {

#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
            /* Reset the RDPI state machine */
        	Dcm_DsldResetRDPI();
#endif



#if((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
            /* Reset the RoeEvents which where started before session transition */
            Dcm_ResetRoeDidevents();
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
            Dcm_ResetRoeOnDtcevents();
#endif

#endif
        }

    }
    else
    {
        /* Calculate the number  of sessions configured in ECU for particular protocol*/
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
        /*Check if the return value is TRUE*/
        if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
        {
            nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
        }
        else
        {
            nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
        }
#else
        nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
#endif
        /* get the index of requested session id in session look up table */
        for(idxIndex_qu8 = 0x1; idxIndex_qu8 < nrSessions_u8 ; idxIndex_qu8++)
        {
            if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== dataSesCtrlType_u8)
            {
                /* session found */
                break;
            }
        }

        if(idxIndex_qu8 != nrSessions_u8)
        {
            /* set the session index */
            Dcm_DsldGlobal_st.idxActiveSession_u8 = (uint8)idxIndex_qu8;
            /*Check if the return value is FALSE*/
            if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
            {
                /* lock the ECU in any UDS session transition*/
                Dcm_DsldGlobal_st.idxActiveSecurity_u8 = 0x00u;
            }

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
            Dcm_RoutineSetSesCtrlType(dataSesCtrlType_u8);
#endif


#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
            /* Reset the RoeEvents which where started before session transition */
            Dcm_ResetRoeDidevents();
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
            Dcm_ResetRoeOnDtcevents();
#endif
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
        dataSessionMask_u32 = Dcm_DsldGetActiveSessionMask_u32();
        /*The below function code will loop through all the IOCBI DIDs and call all the returncontrol to ECU functions to reset all the  active IOctrls
           supported in the current session level*/

        Dcm_ResetActiveIoCtrl(dataSessionMask_u32,0x1u,TRUE);
#endif
		}
        else
        {
            /* Report development error "DCM_E_SESSION_NOT_CONFIGURED " to DET module if the DET module is enabled */
            DCM_DET_ERROR(DCM_SETSESSIONLEVEL , DCM_E_SESSION_NOT_CONFIGURED )
            /* requested session is not configured in DSC service give indication to Application */
            /* without changing the session.                                              */
            dataSesCtrlType_u8 = dataCurrentSession_u8;

        }

        /**The below function code will loop through all the IOCBI DIDs and call all the returncontrol to ECU functions to reset all the  active IOctrls
           supported in the current session level*/

    }

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
    /* SECA state moved to INIT after session change */
    Dcm_Dsp_SecaSessIni();
#endif
#endif

    /* Call the function to enable the control Dtc setting*/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
    Dcm_ControlDtcSettingExit();
#endif
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!=DCM_CFG_OFF)) )
    Dcm_DspDeactivateRequestUploadDownloadPermission();
#endif
    /* indicate to application regarding the session change */
    (void)Dcm_SesCtrlChangeIndication(dataCurrentSession_u8, dataSesCtrlType_u8);

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
