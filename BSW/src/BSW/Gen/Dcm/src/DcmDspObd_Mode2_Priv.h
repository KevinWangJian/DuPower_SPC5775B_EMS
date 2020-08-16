

#ifndef DCMDSPOBD_MODE2_PRIV_H
#define DCMDSPOBD_MODE2_PRIV_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/


/**
 ***************************************************************************************************
            OBD MODE 02 (To read freeze frame data )
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)

#define DCM_DSPMODE02_PID02   0x02u       /*PID 02 number which reports DTC number */
#define MAX_PID_LENGTH_DATA   0xffu       /*Maximum length of data bytes associated with PID */
#define DCM_OBDMODE02_SUPPPID 0x20u     /* Supported PIDS are multiples of 0x20*/

#endif /*DCM_CFG_DSP_OBDMODE2_ENABLED*/

#endif   /* _DCMDSPOBD_MODE2_PRIV_H */

