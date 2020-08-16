

#ifndef DCMDSPUDS_CDTCS_INF_H
#define DCMDSPUDS_CDTCS_INF_H

/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"
#if (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.h"
#endif
#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"
#include "DcmDspUds_Cdtcs_Prot.h"
#include "Dcm_Cfg_SchM.h"
#endif
#include "DcmAppl.h"

#endif

