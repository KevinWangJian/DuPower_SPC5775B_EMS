/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */





#ifndef DCM_CFG_SCHM_H
#define DCM_CFG_SCHM_H

/*TESTCODE-START
#include "rba_BswSrv.h"
TESTCODE-END*/
#include "SchM_Default.h"

/**
 * @ingroup DCM_TPL
 * SchM_Enter_Dcm_Global_NoNest :-\n
 * This API is used to disable/lock the interrupt.\n
 * It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence.\n
 * This API has been used in the following "Dcm Global" group\n
 *  1.Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16\n
 *  2.Dcm_DsldRoeScheduler_st.stRoeQueueState_st\n
 *  3.Dcm_DsldGlobal_st.stDslState_en\n
 *  4.Dcm_DslDsdRxPduArray_ast[idxLengthIndex_u16].Dcm_DsldSId_u16\n
 *  5.Dcm_DsldGlobal_st.dataActiveRxPduId_u8\n
 *
 * @param[in]     None
 * @param[out]    None
 *
 * @retval     None
 *
 */
LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Enter_Dcm_Global_NoNest(void)
{
	/*The integrator shall place his code here which would disable/lock the interrupt*/
    /* It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence */
	SCHM_ENTER_DEFAULT();
}


/**
 * @ingroup DCM_TPL
 * SchM_Exit_Dcm_Global_NoNest :-\n
 * This API is used to enable/unlock the interrupt.\n
 * It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence.\n
 * This API has been used in the following "Dcm Global" group\n
 *  1.Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16\n
 *  2.Dcm_DsldRoeScheduler_st.stRoeQueueState_st\n
 *  3.Dcm_DsldGlobal_st.stDslState_en\n
 *  4.Dcm_DslDsdRxPduArray_ast[idxLengthIndex_u16].Dcm_DsldSId_u16\n
 *  5.Dcm_DsldGlobal_st.dataActiveRxPduId_u8\n
 *
 * @param[in]     None
 * @param[out]    None
 *
 * @retval     None
 *
 */
LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Exit_Dcm_Global_NoNest(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    /* It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence */
	SCHM_EXIT_DEFAULT();
}


/**
 * @ingroup DCM_TPL
 * SchM_Enter_Dcm_DsldTimer_NoNest :-\n
 * This API is used to disable/lock the interrupt.\n
 * This API is mainly introduced to maintain data consistency between P2Max,P2StrMax and P3Max. The data consistency comes up when there is parallel access write or read P2Max or P2StrMax and P3Max
 * and that due to data inconsistency it so happens that for e.g. old value of P2Max and new value of P3Max is established for the connection. It is required to ensure that either the old set or new set is active but not few parameters from the old set and few parameters from the new set are active.\n
 * Thus, this lock is introduced in the below "Dcm Timings Group P2/P3/P2Star"\n
 * 1.Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32\n
 * 2.Dcm_DsldTimer_st.dataTimeoutP3max_u32\n
 * 3.Dcm_DsldTimer_st.dataTimeoutP2max_u32\n
 * 4.Dcm_DsldKwpReqTiming_st.P3_max_u32\n
 * 5.Dcm_DsldKwpReqTiming_st.P2_max_u32\n
 * 6.Dcm_DsldTimer_st.dataTimeoutP3max_u32\n
 *
 * @param[in]     None
 * @param[out]    None
 *
 * @retval     None
 *
 */
LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Enter_Dcm_DsldTimer_NoNest(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    /* It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence */
	SCHM_ENTER_DEFAULT();
}


/**
 * @ingroup DCM_TPL
 * SchM_Exit_Dcm_DsldTimer_NoNest :-\n
 * This API is used to enable/unlock the interrupt.\n
 * This API is mainly introduced to maintain data consistency between P2Max,P2StrMax and P3Max. The data consistency comes up when there is parallel access write or read P2Max or P2StrMax and P3Max
 * and that due to data inconsistency it so happens that for e.g. old value of P2Max and new value of P3Max is established for the connection. It is required to ensure that either the old set or new set is active but not few parameters from the old set and few parameters from the new set are active.\n
 * Thus, this lock is introduced in the below "Dcm Timings Group P2/P3/P2Star"\n
 * 1.Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32\n
 * 2.Dcm_DsldTimer_st.dataTimeoutP3max_u32\n
 * 3.Dcm_DsldTimer_st.dataTimeoutP2max_u32\n
 * 4.Dcm_DsldKwpReqTiming_st.P3_max_u32\n
 * 5.Dcm_DsldKwpReqTiming_st.P2_max_u32\n
 * 6.Dcm_DsldTimer_st.dataTimeoutP3max_u32\n
 *
 * @param[in]     None
 * @param[out]    None
 *
 * @retval     None
 *
 */
LOCAL_INLINE FUNC(void,DCM_CODE) SchM_Exit_Dcm_DsldTimer_NoNest(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    /* It is recommended that the projects use Common lock here as it uses LESS runtime. NoNest locks if used will only reduce cross core runtime influence */
	SCHM_EXIT_DEFAULT();
}

#endif /* _DCM_SCHM_H */
