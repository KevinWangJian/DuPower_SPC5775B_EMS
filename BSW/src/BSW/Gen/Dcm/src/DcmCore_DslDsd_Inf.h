

#ifndef DCMCORE_DSLDSD_INF_H
#define DCMCORE_DSLDSD_INF_H

/**
 ***************************************************************************************************
 * \moduledescription
 *                      Interfaces header file for DcmCore DSLDSD
 *
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"
#include "Rte_Dcm.h"
#include "Dcm_Cbk.h"
#include "PduR_Dcm.h"
#include "ComM_Dcm.h"

#include "Dcm_Cfg_SchM.h"
#include "rba_BswSrv.h"
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.h"
#endif

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif



/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */
#include "DcmCore_DslDsd_Prot.h"



#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Uds_Prot.h"

#if((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Memaddress_Calc_Prot.h"
#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Priv.h"
#endif

#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Er_Prot.h"
#endif

#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"
#endif
#if(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdpi_Prot.h"
#endif
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdbi_Prot.h"
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Iocbi_Prot.h"
#endif

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dsc_Prot.h"
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Er_Prot.h"
#endif

#if((DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Cdtcs_Prot.h"
#endif

#if ((DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)))
#include "BswM_Dcm.h"
#endif

#if (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_CC_Prot.h"
#endif

#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rc_Inf.h"
#endif
#endif

#include "DcmAppl.h"
/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */
#include "DcmCore_DslDsd_Inl.h"


/* _DCMCORE_DSLDSD_INF_H                                                                          */
#endif

