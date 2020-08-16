

#ifndef DCMDSPOBD_MODE2_INF_H
#define DCMDSPOBD_MODE2_INF_H

/*
 ***************************************************************************************************
 * Public Includes
 ***************************************************************************************************
 */

#include "Dcm.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif

#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)
#include "Dem.h"
#endif

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
/* _DCMDSPOBD_MODE2_INF_H                                                                          */
#endif

