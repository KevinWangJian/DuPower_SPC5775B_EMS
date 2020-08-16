

#ifndef DCMDSPOBD_MODE8_PRIV_H
#define DCMDSPOBD_MODE8_PRIV_H



/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/


/**
 ***************************************************************************************************
            OBD service 0x08
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE8_ENABLED != DCM_CFG_OFF)

#define  DCM_OBDMODE08_SUPPTID     0x20u        /* supported INFOTYPES are multiples of 0x20 */
#define  DCM_OBDMODE08_REQ_LEN_MIN 0x00u    /* Minimum Request Length for OBD MODE 0x08 in case of supported Tids */
#define  DCM_OBDMODE08_REQ_LEN_MAX 0x07u    /* Maximum Request Length for OBD MODE 0x08 in case of supported Tids */

#endif


#endif   /* _DCMDSPOBD_MODE8_PRIV_H */

