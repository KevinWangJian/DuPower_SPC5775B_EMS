

#ifndef DCMDSPUDS_RDTC_INF_H
#define DCMDSPUDS_RDTC_INF_H


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#include "Dem.h"

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation(
        VAR(Dcm_IdContextType,AUTOMATIC) idContext,
        VAR(PduIdType,AUTOMATIC) dcmRxPduId,
        VAR(uint16,AUTOMATIC) SourceAddress,
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                        );



/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */

#include "DcmCore_DslDsd_Prot.h"

/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */
#endif

/* _DCMDSPUDS_RDTC_INF_H                                                                          */
#endif

