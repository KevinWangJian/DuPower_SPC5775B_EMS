

#ifndef DCMDSPUDS_REQUESTUPLOAD_PRIV_H
#define DCMDSPUDS_REQUESTUPLOAD_PRIV_H

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

/**
 ***************************************************************************************************
            RequestUpload Service (0x35)
 ***************************************************************************************************
 */


#define DCM_DSP_REQUESTUPLOAD_MINREQLEN 0x04u

typedef enum
{
    DCM_DSP_REQUESTUPLOAD_IDLE = 0,     /* Idle state */
    DCM_DSP_REQUESTUPLOAD_GETBLOCKNUM ,
    DCM_DSP_REQUESTUPLOAD_ERROR

}Dcm_DspRequestUploadStates_ten;


#endif
#endif   /* _DCMDSPUDS_REQUESTUPLOAD_PRIV_H */

