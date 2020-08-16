

#ifndef DCMDSPUDS_TP_PRIV_H
#define DCMDSPUDS_TP_PRIV_H


/**
 ***************************************************************************************************
            Tester present service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_TESTERPRESENT_ENABLED != DCM_CFG_OFF || DCM_CFG_DSP_TESTERPRESENTSB_ENABLED != DCM_CFG_OFF)
#define DCM_TPR_REQ_LEN              0x01u     /* length of request message for TesterPresent   */
#define DCM_TPR_POSITIVE_RESP_LEN    0x01u     /* length of positive response for TesterPresent */
#define DCM_TPR_POSITION_SUBFUNC     0x00u     /* position of parameter 'response required'for TesterPresent */
#define DCM_TPR_RESP_REQUIRED        0x00u     /* response required for TesterPresent */
#endif


#endif   /* _DCMDSPUDS_TP_PRIV_H */

