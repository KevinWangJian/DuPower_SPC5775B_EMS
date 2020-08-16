

#ifndef DCMDSPUDS_WDBI_PRIV_H
#define DCMDSPUDS_WDBI_PRIV_H



/**
 ***************************************************************************************************
            Write Data by Identifier service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

typedef enum
{
    DCM_DSP_WDBI_IDLE = 0,     /* Idle state */
    DCM_DSP_WDBI_VALDATALEN,   /* Validate request length state */
    DCM_DSP_WDBI_CHECKACCESS,  /* State to check session and Security */
    DCM_DSP_WDBI_WRITEDATAREC  /* State to Write the Data Record */
}Dcm_DspWDBIStates_ten;

#define DCM_DSP_WDBI_MINREQLEN 0x03u /* Minimum Request length for WDBI service */

#endif


#endif   /* _DCMDSPUDS_WDBI_PRIV_H */

