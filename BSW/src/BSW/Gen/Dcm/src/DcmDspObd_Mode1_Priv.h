

#ifndef DCMDSPOBD_MODE1_PRIV_H
#define DCMDSPOBD_MODE1_PRIV_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/

/**
 ***************************************************************************************************
            OBD Service 0x01 ( request current powertrain diagnostic information )
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)

#define DCM_OBDMODE01_REQ_LEN_MIN   0x00u     /* Minimum Request Length for OBD MODE 0x01 */
#define DCM_OBDMODE01_REQ_LEN_MAX   0x07u     /* Maximum Request Length for OBD MODE 0x01 is 6bytes */
#define DCM_OBDMODE01_SUPPPID       0x20u    /* Supported PIDS are multiples of 0x20*/
#define DCM_SUPPORT_INFO_BITMASK    0x80u     /* To calculate the support information byte */

#endif    /* DCM_CFG_DSP_OBDMODE1_ENABLED */

#endif   /* _DCMDSPOBD_MODE1_PRIV_H */
