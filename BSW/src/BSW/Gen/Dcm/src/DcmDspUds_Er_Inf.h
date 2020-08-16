

#ifndef DCMDSPUDS_ER_INF_H
#define DCMDSPUDS_ER_INF_H


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"


/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.h"
#endif

#include "DcmDspUds_Er_Prot.h"
#endif
#include "DcmCore_DslDsd_Prot.h"

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif
#include "DcmAppl.h"
#endif

/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */


/* _DCMDSPUDS_ER_INF_H                                                                          */
#endif

