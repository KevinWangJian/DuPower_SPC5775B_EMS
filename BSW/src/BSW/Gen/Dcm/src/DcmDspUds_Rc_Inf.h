

#ifndef DCMDSPUDS_RC_INF_H
#define DCMDSPUDS_RC_INF_H

#include "Dcm.h"


#include "DcmCore_DslDsd_Prot.h"
#include "Dcm_Cfg_SchM.h"
#if ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rc_Prot.h"
#if((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF) && (DCM_CFG_IN_PARAM_MAXLEN > 0u))
#include "rba_BswSrv.h"
#endif /* DCM_CFG_DSP_ROUTINECONTROL_ENABLED && DCM_CFG_ROUTINEVARLENGTH && DCM_CFG_IN_PARAM_MAXLEN */
#endif /* DCM_CFG_DSPUDSSUPPORT_ENABLED */
#include "DcmAppl.h"

#endif /* _DCMDSPUDS_RC_INF_H */

