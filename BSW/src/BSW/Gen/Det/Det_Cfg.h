
/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DET_CFG_H
#define DET_CFG_H

#include "Det_Cfg_Version.h"
/* Configuration status of GetVersionInfo API */
#define DET_CFG_VERSIONINFO_SUPPORTED       FALSE
/* Configuration status of Dlt forwarding */
#define DET_CFG_FORWARDTODLT_SUPPORTED      FALSE
/* Configuration status of API consistency check */
#define DET_CFG_CHECK_API_CONSISTENCY       TRUE

/* Configuration status of runtime error callout */
#define DET_CFG_RUNTIMECALLOUT_SUPPORTED    FALSE

/* Configuration status of transient fault callout */
#define DET_CFG_TRANSIENTCALLOUT_SUPPORTED  FALSE

/* Configuration status of Error Hooks */
#define DET_CFG_HOOKCOUNT                   0

/* Configuration status of Error Buffer */
#define DET_CFG_ERRORBUFFER_ENABLED         TRUE
#define DET_CFG_ERRORBUFFERAPI_SUPPORTED    FALSE
#define DET_CFG_ERRORBUFFERSIZE             10

#if (DET_CFG_HOOKCOUNT > 0)
#define DET_START_SEC_ROM_CODE
#include "Det_MemMap.h"
#define DET_STOP_SEC_ROM_CODE
#include "Det_MemMap.h"

#define DET_CFG_CALLERRORHOOKS(ModuleId, InstanceId, ApiId, ErrorId) \
do{ \
}while (0)
#endif /* #if  (DET_CFG_HOOKCOUNT > 0) */

#endif	/* DET_CFG_H */

