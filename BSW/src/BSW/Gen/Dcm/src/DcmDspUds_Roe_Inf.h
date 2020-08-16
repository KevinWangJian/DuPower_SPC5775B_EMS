

#ifndef DCMDSPUDS_ROE_INF_H
#define DCMDSPUDS_ROE_INF_H

/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.h"
#endif
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) )
/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */

#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"


 #include "DcmAppl.h"
#endif

/* _DCMDSPUDS_ROE_INF_H */
#endif

