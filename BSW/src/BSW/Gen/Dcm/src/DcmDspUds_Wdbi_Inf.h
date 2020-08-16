

#ifndef DCMDSPUDS_WDBI_INF_H
#define DCMDSPUDS_WDBI_INF_H


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */

#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"

#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Wdbi_Prot.h"
#include "Dcm_Lcfg_DspUds.h"
#endif
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


/* _DCMDSPUDS_WDBI_INF_H                                                                          */
#endif

