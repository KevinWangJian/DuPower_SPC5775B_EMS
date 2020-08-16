

#ifndef DCMDSPUDS_RMBA_PRIV_H
#define DCMDSPUDS_RMBA_PRIV_H



/**
 ***************************************************************************************************
            Write Data by Identifier service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)


typedef enum
{
    DCM_DSP_RMBA_IDLE = 0,     /* Idle state */
    DCM_DSP_RMBA_VALDATALEN,   /* Validate request length state */
    DCM_DSP_RMBA_CHECKACCESS,  /* State to check session and Security */
    DCM_DSP_RMBA_READDATAREC  /* State to Read the DataRecord From the physical address*/
}Dcm_DspRmbaStates_ten;


#define DCM_DSP_RMBA_MINREQLEN 		0x03u /* Minimum Request length for RMBA service  */
#endif


#endif   /* _DCMDSPUDS_RMBA_PRIV_H */

