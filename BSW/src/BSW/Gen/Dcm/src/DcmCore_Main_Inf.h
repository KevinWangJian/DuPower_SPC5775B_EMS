

#ifndef DCMCORE_MAIN_INF_H
#define DCMCORE_MAIN_INF_H

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
#include "ComM_Dcm.h"


#include "Dcm_Cfg_SchM.h"
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
#include "SchM_Dcm.h"
#endif
#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

/*
 ***************************************************************************************************
 * Protected Includes (package wide includes)
 ***************************************************************************************************
 */
#include "DcmCore_DslDsd_Prot.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Uds_Prot.h"
#include "DcmDspUds_Rc_Prot.h"

#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
#include "DcmDspUds_Dddi_Prot.h"
#endif

#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Iocbi_Prot.h"
#endif

#endif
#include "DcmAppl.h"
/*
 ***************************************************************************************************
 * Other Inline Functions
 ***************************************************************************************************
 */
#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF))
#include "DcmCore_DslDsd_Inl.h"
#endif

/* _DCMCORE_MAIN_INF_H                                                                          */
#endif

