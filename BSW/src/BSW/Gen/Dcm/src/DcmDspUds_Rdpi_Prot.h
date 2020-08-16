

#ifndef DCMDSPUDS_RDPI_PROT_H
#define DCMDSPUDS_RDPI_PROT_H


/**
 ***************************************************************************************************
            Read Data By Periodic Identifier(RDPI) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_DSP_RDPI_NONSTOPSENDINGMINREQLEN        0x2u        /* Minimum request length */
#define DCM_DSP_RDPI_STOPSENDINGMINREQLEN        0x1u        /* Minimum request length */
#define DCM_DSP_RDPI_POSTXMODE       0x0u

#define DCM_DSP_RDPI_SLOW_RATE      0x01u
#define DCM_DSP_RDPI_MEDIUM_RATE    0x02u
#define DCM_DSP_RDPI_FAST_RATE      0x03u
#define DCM_DSP_RDPI_STOP_SENDING   0x04u


#define DCMRDPIMINLENGTHCHECK(len,mode)   (((mode)==(DCM_DSP_RDPI_STOP_SENDING)))?(((len)>=DCM_DSP_RDPI_STOPSENDINGMINREQLEN) ? (TRUE) : (FALSE)):(((len)>=DCM_DSP_RDPI_NONSTOPSENDINGMINREQLEN) ? (TRUE) : (FALSE))

#define DCMRDPIMAXLENGTHCHECK(len)   (((len)<=(DCM_CFG_MAX_PERIODIC_DID_READ+1u)) ? (TRUE) : (FALSE))


/* Definitions of states of RDPI service */
typedef enum
{
    DCM_DSP_RDPI_INIT,              /* Initialization state            */
    DCM_DSP_RDPI_CHECKPERMISSION    /* RDPI state to check permissions */
}Dcm_DspRdpiState_ten;

#endif  /* DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED */

#endif   /* _DCMDSPUDS_RDPI_PROT_H */

