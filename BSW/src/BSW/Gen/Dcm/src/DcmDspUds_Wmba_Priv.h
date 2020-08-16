

#ifndef DCMDSPUDS_WMBA_PRIV_H
#define DCMDSPUDS_WMBA_PRIV_H



/**
 ***************************************************************************************************
            Write Data by Identifier service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

typedef enum
{
    DCM_DSP_WMBA_IDLE = 0,     /* Idle state */
    DCM_DSP_WMBA_VALDATALEN,   /* Validate request length state */
    DCM_DSP_WMBA_CHECKACCESS,  /* State to check session and Security */
    DCM_DSP_WMBA_WRITEDATAREC  /* State to Write the Data Record */
}Dcm_DspWmbaStates_ten;

#define DCM_DSP_WMBA_MINREQLEN 0x04u /* Minimum Request length for WMBA service  */

#endif


#endif   /* _DCMDSPUDS_WMBA_PRIV_H */
