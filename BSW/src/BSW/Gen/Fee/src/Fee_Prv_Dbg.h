

#ifndef FEE_PRV_DBG_H
#define FEE_PRV_DBG_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 * The Dbg unit contains several helpers useful for debugging. It can do:
 * - Timing measurement
 * - Create dumps during development in case of errors
 * ...
 * For a productive release the Dbg unit should be turned off.
*/

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

typedef struct
{
    uint32 hist_au32[FEE_PRV_CFG_DBG_TIME_HISTOGRAM_BASKETNUM];
    uint32 tiAcc_u32;
    uint32 tiMax_u32;
    uint32 tiLast_u32;
    uint32 tiTmp_u32;
} Fee_Prv_DbgTimeEntry_tst;

typedef struct
{
    Fee_Prv_DbgTimeEntry_tst orderInvalidate_st;
    Fee_Prv_DbgTimeEntry_tst orderRead_st;
    Fee_Prv_DbgTimeEntry_tst orderWrite_st;
    Fee_Prv_DbgTimeEntry_tst procInit_st;
    Fee_Prv_DbgTimeEntry_tst procMain_st;
    Fee_Prv_DbgTimeEntry_tst secChngDat_st;
    Fee_Prv_DbgTimeEntry_tst secChngFat_st;
} Fee_Prv_DgbTime_tst;

typedef struct
{
    uint32  sectorDeleteAbs_au32    [FEE_PRV_CFG_NUM_SECTORS];
    uint32  sectorDeleteDelta_aau32 [FEE_PRV_CFG_NUM_SECTORS][FEE_PRV_CFG_DBG_ERASECOUNTERS_HISTOGRAM_BASKETNUM];
} Fee_Prv_DbgEraseCounters_tst;

typedef struct
{
#if (TRUE == FEE_PRV_CFG_DBG_TIME)
    Fee_Prv_DgbTime_tst             time_st;
#endif
#if (TRUE == FEE_PRV_CFG_DBG_ERASECOUNTERS)
    Fee_Prv_DbgEraseCounters_tst    eraseCounters_st;
#endif
    boolean dummy_b;
} Fee_Prv_DbgInfo_tst;

typedef struct
{
    uint32              nrDump_u32;
    uint32              nrDbgBlockWrites_u32;
    boolean             isDebugBlockWriteRequested_b;
    boolean volatile    freeze_b;
} Fee_Prv_Dbg_tst;

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

LOCAL_INLINE void Fee_Prv_DbgDummyFunc(void)
{
}

#if (TRUE == FEE_PRV_CFG_DBG)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgMainFunction(void);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgMainFunction()   Fee_Prv_DbgDummyFunc()
#endif

#if (TRUE == FEE_PRV_CFG_DBG_TIME)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgWatchStart(Fee_Prv_DbgTimeEntry_tst * time_pst);
extern void Fee_Prv_DbgWatchStop(Fee_Prv_DbgTimeEntry_tst * time_pst, boolean updateDebugBlock_b);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgWatchStart(A)    Fee_Prv_DbgDummyFunc()
#define Fee_Prv_DbgWatchStop(A, B)  Fee_Prv_DbgDummyFunc()
#endif

#if (TRUE == FEE_PRV_CFG_DBG_ERASECOUNTERS)
#include "rba_FeeFs2_Prv_Sector.h"
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgEraseCountersTrack(rba_FeeFs2_Prv_Sector_tst const * sector_pcst);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgEraseCountersTrack(A)    Fee_Prv_DbgDummyFunc()
#endif

#if (TRUE == FEE_PRV_CFG_DBG_CHECKLAYOUT)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgCheckLayout(void);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgCheckLayout()    Fee_Prv_DbgDummyFunc()
#endif

#if (TRUE == FEE_PRV_CFG_DBG_DUMP)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgDump(void);
extern void Fee_Prv_DbgFailDump(MemIf_JobResultType result_en);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgDump()       Fee_Prv_DbgDummyFunc()
#define Fee_Prv_DbgFailDump(A)  Fee_Prv_DbgDummyFunc()
#endif

#if (TRUE == FEE_PRV_CFG_DBG_BLOCK)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_DbgBlockRead(void);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#else
#define Fee_Prv_DbgBlockRead()  Fee_Prv_DbgDummyFunc()
#endif

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#if (TRUE == FEE_PRV_CFG_DBG)
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_Prv_DbgInfo_tst Fee_Prv_DbgInfo_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

/* Buffer needed to write the debug struct */
#if (TRUE == FEE_PRV_CFG_DBG_BLOCK)
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
extern uint8 Fee_Prv_DbgBfr_au8[FEE_PRV_CFG_DBG_BLOCK_SIZE];
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
#endif

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_DBG_H */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
 **********************************************************************************************************************
 * End of header file: $Name______:$
 **********************************************************************************************************************
</BASDKey>*/
