

#ifndef DCMDSPUDS_CC_PROT_H
#define DCMDSPUDS_CC_PROT_H

/**
 ***************************************************************************************************
            Communication Control service Protected Header
 ***************************************************************************************************
 */

/* Definitions of states of DSC service */
typedef enum
{
    DCM_DSP_CC_INITIAL  = 1,                          /* CC Initialization state         */
    DCM_DSP_CC_CHECKDATA,                             /* CC Service Check data           */
    DCM_DSP_CC_PROCESSSERVICE,                        /* Send Positive response state    */
    DCM_DSP_CC_ERROR                                  /* Send negative response state    */
}Dcm_CCStateType_ten;

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF))
extern FUNC(void, DCM_CODE) Dcm_Prv_DspCommCntrlConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
														 );




/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */

LOCAL_INLINE boolean Dcm_Prv_CC_IsSupportedInSession( VAR(Dcm_SesCtrlType,DCM_VAR) ActiveSession_u8)
{

    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    VAR(uint8,AUTOMATIC) nrSessions_u8;
    VAR(boolean,AUTOMATIC)  flgStatus_b;


    VAR(uint32,AUTOMATIC) dataSessionsAllowed_u32;
    VAR(uint8,AUTOMATIC) nrService_u8;


    flgStatus_b = TRUE;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
            /*Check if the return value is TRUE*/
            if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
            {
                nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
            }
            else
#endif
            {
                nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
            }

             /* get the index of requested session id in session look up table */
             for(idxIndex_qu8 = 0x1; idxIndex_qu8 < nrSessions_u8 ; idxIndex_qu8++)
             {
                 //if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== dataSesCtrlType_u8)
                 if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== ActiveSession_u8)
                 {
                     /* session found */
                     break;
                 }
             }
             if(idxIndex_qu8 != nrSessions_u8)
             {

                 nrService_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].num_services_u8;
                 /*check whether the service is supported in the current protocol*/
                  for(idxIndex_qu8 = 0x0; idxIndex_qu8 < nrService_u8 ; idxIndex_qu8++)
                  {
                      /*Check if the service existing in DSP and active service id is 0x28 for communication control*/
                      if(( Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].sid_u8 == DCM_DSP_SID_COMMUNICATIONCONTROL)&&(Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].servicelocator_b !=FALSE ) )
                      {
                          /* service found */
                          break;
                      }
                  }
                  dataSessionsAllowed_u32 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxIndex_qu8].allowed_session_b32;
                  if((idxIndex_qu8 >= nrService_u8) || ((Dcm_DsldGetActiveSessionMask_u32() &  dataSessionsAllowed_u32) == 0u))
                  {
                      /*Service not found,Now reset the communication mode to the default mode
                       *                                        or
                       *  Session is not supported for the service,Now reset the communication mode to the default mode */
                      /*Reset the flag status to false*/
                      flgStatus_b = FALSE;
                  }


            }

return flgStatus_b;
}


#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif   /* DCMDSPUDS_CC_PROT_H */

