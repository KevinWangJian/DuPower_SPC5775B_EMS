

#ifndef DET_PRV_H
#define DET_PRV_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Det_Types.h"
#include "Det_Cfg.h"
#include "rba_DiagLib_MemUtils.h"

/*
 **********************************************************************************************************************
 * Macros
 **********************************************************************************************************************
 */

/* Abstraction to the MemSet function */
#define DET_MEMSET(xDest_pv, xPattern_u32, numBytes_u32)  RBA_DIAGLIB_MEMSET((xDest_pv),(xPattern_u32),(numBytes_u32))

/* Abstraction to void cast */
#define DET_UNUSED_PARAM(P)   ((void)(P))

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */
#define DET_START_SEC_RAM_CLEARED
#include "Det_MemMap.h"

extern boolean Det_Initialized_b;

#if (DET_CFG_ERRORBUFFER_ENABLED)
extern Det_ErrorEntryBufferType Det_ErrorEntryBuffer[];
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED) */

#define DET_STOP_SEC_RAM_CLEARED
#include "Det_MemMap.h"

#endif /* #ifndef DET_PRV_H */
