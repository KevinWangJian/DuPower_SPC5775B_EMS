

#ifndef DCMDSPUDS_DSC_INF_H
#define DCMDSPUDS_DSC_INF_H


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.h"
#endif
#include "Dcm_Cfg_SchM.h"


/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dsc_Prot.h"
#endif
#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif
#endif

#include "DcmAppl.h"
/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */


/* _DCMDSPUDS_DSC_INF_H                                                                          */
#endif

