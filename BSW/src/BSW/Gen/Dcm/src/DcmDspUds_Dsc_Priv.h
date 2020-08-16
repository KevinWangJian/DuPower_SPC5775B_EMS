

#ifndef DCMDSPUDS_DSC_PRIV_H
#define DCMDSPUDS_DSC_PRIV_H


/**
 ***************************************************************************************************
            DSC service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

#define DCM_DSP_DSC_REQ_LEN              0x01u     /* length of DSC request message                  */

#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
#define DCM_DSP_DSC_RESP_LEN             0x05u     /* length of DCS positive response                */
#else
#define DCM_DSP_DSC_RESP_LEN             0x01u     /* length of DCS positive response                */
#endif

#define DCM_DSP_DSC_POSITION_SUBFUNC     0x00u     /* DSC position of parameter 'response required'  */

#endif


#endif   /* _DCMDSPUDS_DSC_PRIV_H */

