

#ifndef DCMDSPUDS_UDS_INF_H
#define DCMDSPUDS_UDS_INF_H


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */
#include "Dcm.h"
#include "rba_BswSrv.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "Rte_Dcm.h"
#endif


#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */

#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF))
#include "SchM_Dcm.h"
#endif
#endif

#include "DcmCore_DslDsd_Prot.h"
#include "DcmDspUds_Uds_Prot.h"

#if (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Er_Prot.h"
#endif
#if (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dsc_Prot.h"
#endif
#if (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
#include "BswM_Dcm.h"
#endif
#include "DcmDspUds_CC_Prot.h"
#endif

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdbi_Prot.h"
#endif

#if (DCM_CFG_DSP_REQUESTUPLOAD_ENABLED!=DCM_CFG_OFF)
#include "DcmDspUds_Memaddress_Calc_Prot.h"
#endif
#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif
#include "Dcm_Cfg_SchM.h"
#include "DcmAppl.h"

/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */

#endif
/* _DCMDSPUDS_UDS_INF_H                                                                          */
#endif
