

#ifndef DCMDSPOBD_MODE9_PRIV_H
#define DCMDSPOBD_MODE9_PRIV_H


/**
 ***************************************************************************************************
            OBD service 0x09
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

#define DCM_OBDMODE09_REQ_LEN_MIN   0x00u     /* Minimum Request Length for OBD MODE 0x09              */
#define DCM_OBDMODE09_REQ_LEN       0x01u     /* Request Length for INFOTYPEs which report data values */
#define DCM_OBDMODE09_REQ_LEN_MAX   0x07u     /* Maximum Request Length for OBD MODE 0x09 is 6 bytes   */
#define DCM_OBDMODE09_SUPPINFOTYPE  0x20u     /* supported INFOTYPES are multiples of 0x20             */


/* Definitions of States in the service */
typedef enum
{
    DCM_DSP_MODE09_UNINIT,                 /* Uninit state */
    DCM_DSP_MODE09_INIT,                   /* Default state */
    DCM_DSP_MODE09_RUNNING                 /* State to process non-supported Infotypes  */
}Dcm_DspMode09Type_ten;

#endif


#endif   /* _DCMDSPOBD_MODE9_PRIV_H */
