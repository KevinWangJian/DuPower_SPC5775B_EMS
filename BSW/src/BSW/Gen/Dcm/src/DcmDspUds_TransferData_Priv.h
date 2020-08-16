

#ifndef DCMDSPUDS_TRANSFERDATA_PRIV_H
#define DCMDSPUDS_TRANSFERDATA_PRIV_H


/**
 ***************************************************************************************************
            TransferData (0x36) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_TRANSFERDATA_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_DSP_TRANSFERDATA_IDLE = 0,     /* Idle state */
    DCM_DSP_TRANSFERDATA_CHECKACCESS,  /* State to check session and Security */
    DCM_DSP_TRANSFERDATA_READWRITE,  /* State to check session and Security */
    DCM_DSP_TRANSFERDATA_ERROR  /* State to Write the Data Record */
}Dcm_DspTransferDataStates_ten;

#define DCM_TRANSFERDATAUPLOAD_MIN_LEN              0x01u     /* length of request message if the previous request was RequestUpload service */
#define DCM_TRANSFERDATADOWNLOAD_MIN_LEN              0x02u     /* length of request message if the previous request was RequestDownload service */
#endif

#endif   /* _DCMDSPUDS_TRANSFERDATA_PRIV_H */

