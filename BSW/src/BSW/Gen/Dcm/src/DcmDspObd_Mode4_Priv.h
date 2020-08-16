

#ifndef DCMDSPOBD_MODE4_PRIV_H
#define DCMDSPOBD_MODE4_PRIV_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/


/**
 ***************************************************************************************************
            OBD Service 0x04 (clear or reset all emission related diagnostic information)
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)

#define DCM_OBDMODE04_REQ_LEN        0x00u     /* Request Length for OBD MODE 0x04 */

/* Definitions of States of OBD Mode 04 */
typedef enum
{
    DCM_DSP_MODE04_UNINIT,                           /* uninit state */
    DCM_DSP_MODE04_INIT,                             /* Default state */
    DCM_DSP_MODE04_CLEAR                             /* State to Clear all emission related diagnostic information */
}Dcm_DspObdMode04Type_ten;

#endif    /* DCM_CFG_DSP_OBDMODE4_ENABLED */


#endif   /* _DCMDSPOBD_MODE4_PRIV_H */

