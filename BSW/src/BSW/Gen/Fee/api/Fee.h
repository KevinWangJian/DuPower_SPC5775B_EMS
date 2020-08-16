


#ifndef FEE_H
#define FEE_H

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 ****************************************************************************************************
 * Includes
 ****************************************************************************************************
 */
#include "Std_Types.h"
#include "Fee_Cfg.h"
#include "MemIf_Types.h"

#if (FEE_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
/* FEE_PRV_DEBUGGING */
#endif

/* Fee debug monitor */
#define FEE_PRV_DEBUG_MONITOR FALSE

#if (!defined(FLS_RB_BLANK_CHECK_API))
#define Fls_Rb_BlankCheck(a,b,c) Fls_BlankCheck(a,c)
#endif

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#if (FEE_AR_RELEASE_MAJOR_VERSION < 4) ||\
    (\
        (FEE_AR_RELEASE_MAJOR_VERSION == 4) &&\
        (FEE_AR_RELEASE_MINOR_VERSION < 2)\
    )
#define FEE_AR42_API_COMPLIANCE STD_OFF
#else
#define FEE_AR42_API_COMPLIANCE STD_ON
#endif

/********************  Code Section for Memory Mapping  starts here *******************************/


/*
 ***************************************************************************************************
 * Type definition and enums
 ***************************************************************************************************
 */
#if (FEE_PRV_DEBUGGING != FALSE)
/* Time measurements */
typedef struct
{
    uint32 Fee_InitTimeDiff_u32;
    uint32 Eep_InitTimeDiff_u32;
    uint32 Fee_InitTimeComplete_u32;
    uint32 Fee_CacheInitTime_u32;
    uint32 Fee_FindEmptyPageTime_u32;
    uint32 Fee_CacheCntSect_u8;
    uint32 BuildUpCacheStart_u32;
    uint32 BuildUpCacheDiff_u32;
    uint32 BuildUpCacheMax_u32;
    uint32 BuildUpCacheRemainInsideMax_u32;
    uint32 BuildUpCacheDiffRemainInside_u32;
    uint32 Eep_FirstIniDiff_u32;
    uint32 Eep_MigrationIniDiff_u32;
    uint32 Eep_EepRamIniDiff_u32;
    uint32 Eep_EnvRamIniDiff_u32;
    uint32 Fee_SearchNextBlockHeaderNum_u32;
    uint32 Fee_SearchSpecificBlockHeaderNum_u32;
    uint32 Fee_SearchNextBlockHeaderNumReload_u32;
    uint32 Fee_SearchNextBlockHeaderLoopRamDiff_u32;
    uint32 Fee_DataReadStart_u32;
    uint32 Fee_DataReadEnd_u32;
    uint32 Fee_DataReadDiff_u32;
    uint32 Fee_DataReadNumBytes_u32;
    uint32 Fee_WriteTimeStart_u32;
    uint32 Fee_WriteTimeEnd_u32;
    uint32 Fee_WriteTimeDiff_u32;
 #if(FEE_RB_MAINTAIN != FALSE)
    uint32 Fee_MaintainTimeStart_u32;
    uint32 Fee_MaintainTimeEnd_u32;
    uint32 Fee_MaintainTimeDiff_u32;
 #endif
    uint32 Fee_ReadTimeStart_u32;
    uint32 Fee_ReadTimeEnd_u32;
    uint32 Fee_ReadTimeDiff_u32;
    uint32 Fee_EraseTimeStart_u32;
    uint32 Fee_EraseTimeEnd_u32;
    uint32 Fee_EraseTimeDiff_u32;
    uint32 Fee_EraseTimeDiffMax_u32;
    uint32 Fee_ReorgTimeStart_u32;
    uint32 Fee_ReorgTimeEnd_u32;
    uint32 Fee_ReorgTimeDiff_u32;
    uint32 Fee_ReorgTimeDiffMax_u32;
    uint32 Fee_ReorgCntStart_u32;
    uint32 Fee_ReorgCntDiffMax_u32;
}Fee_Prv_stModuleTest_tst;
/* FEE_PRV_DEBUGGING */
#endif

/* Fee Main type */
typedef enum
{
    FEE_POLLING_MODE_E,
    FEE_NORMAL_MODE_E
}Fee_stMainType;

/* Possible order types */
typedef enum
{
    FEE_NO_ORDER = 0,           /* there is no order active */
    FEE_READ_ORDER,             /* order-entry belongs to an read job */
    FEE_WRITE_ORDER,            /* order-entry belongs to an write job */
    FEE_INVALIDATE_ORDER,       /* order-entry belongs to an invalidate job  */
 #if(FEE_RB_MAINTAIN != FALSE)
    FEE_MAINTAIN_ORDER,         /* order-entry belongs to an maintenance job */
 #endif
    FEE_FORCED_READ_ORDER       /* order-entry belongs to an forced read job */
}Fee_HlMode_ten;

/* Error codes for API used for DET module (FEE010) */
#define FEE_E_UNINIT                    0x01u    /* API service called when module was not initialized */
#define FEE_E_INVALID_BLOCK_NO          0x02u    /* API service called with invalid block number */
#define FEE_E_INVALID_BLOCK_OFS         0x03u    /* API service called with invalid block offset */
#define FEE_E_INVALID_DATA_PTR          0x04u    /* API service called with invalid data pointer */
#define FEE_E_INVALID_BLOCK_LEN         0x05u    /* API service called with invalid length information */
#define FEE_E_BUSY                      0x06u    /* API service called while module still busy */
#define FEE_E_BUSY_INTERNAL             0x07u    /* API service called while module is busing doing internal management operation */
#define FEE_E_INCOMPATIBLE_VERSIONS     0x08u    /* Included module versions are incompatible */
#define FEE_E_INVALID_VAR_BLK_LEN_CFG   0xFFu    /* API service called with invalid variable block length configuration */
#define FEE_E_INVALID_MIGRATION_CFG     0xFEu    /* API service called with invalid block migration configuration */

/* API Service IDs used for DET module */
#define FEE_SID_INIT                0x00u    /* Service ID for the FEE Init function */
#define FEE_SID_INVALIDATE          0x01u    /* Service ID for the FEE invalidate function */
#define FEE_SID_WRITE               0x02u    /* Service ID for the FEE write function */
#define FEE_SID_CANCEL              0x03u    /* Service ID for the FEE job cancel function */
#define FEE_SID_GETJOBRESULT        0x04u    /* Service ID for the FEE get job result function for NvM requests */
#define FEE_SID_READ                0x05u    /* Service ID for the FEE read function */
#define FEE_SID_SETMODE             0x06u    /* Service ID for the FEE set mode function */
#define FEE_SID_GETVERSIONINFO      0x07u    /* Service ID for the FEE get version info function */
 #if(FEE_RB_MAINTAIN != FALSE)
    #define FEE_SID_MAINTAIN            0x08u    /* Service ID for the FEE maintenance function */
 #endif
#define FEE_SID_RB_ADAPTERGETJOBRESULT  0x09u    /* Service ID for the FEE get job result function for adapter layer requests */
#define FEE_SID_RB_VARLENWRITE          0x0Au    /* Service ID for the FEE Rb variable length write function */
#define FEE_SID_RB_VARLENREAD           0x0Bu    /* Service ID for the FEE Rb variable length read function */
#define FEE_SID_GETMIGRATIONRESULT      0x0Cu    /* Service ID for the FEE to read the migration result */

/* Global Fee_MainFunction state machine type
 * Necessary in public header because it is needed by the Mx17 Adapter for the Eep_GetState function */
typedef enum
{
    FEE_RB_IDLE_E,                   /* Nothing to do, check order queue */
    FEE_RB_WRITE_MODE_E,             /* A write order is currently being proceeded */
    FEE_RB_READ_MODE_E,              /* A read order is currently being proceeded */
    FEE_RB_INVALIDATE_MODE_E,        /* An invalidation is requested */
 #if(FEE_RB_MAINTAIN != FALSE)
    FEE_RB_MAINTAIN_MODE_E,          /* An block maintenance is requested */
 #endif
    FEE_RB_SOFT_SECTOR_REORG_MODE_E, /* Perform a sector reorganization in the background */
    FEE_RB_HARD_SECTOR_REORG_MODE_E, /* Perform a sector reorganization without allowing interruptions */
    FEE_RB_SECTOR_ERASE_E,           /* The sector will be erased */
    FEE_RB_STOPMODE_E                /* Stop mode requested   */
}Fee_Rb_WorkingStateType_ten;


#if (FEE_AR42_API_COMPLIANCE == STD_ON)
typedef struct
{
    uint8 dummy_u8;
} Fee_ConfigType;// Postcompile configuration is not supported; the Fee_Init always has to get a NULL_PTR

#endif

/*
 ***************************************************************************************************
 * Externals
 ***************************************************************************************************
 */
/* Externals for variables and structures */
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern VAR(Fee_Rb_WorkingStateType_ten, FEE_VAR) Fee_Rb_WorkingState_en;
extern VAR(Fee_stMainType, AUTOMATIC) Fee_stMain;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_32
#include "Fee_MemMap.h"
extern VAR(uint32, AUTOMATIC) Fee_SecChngCnt_u32;
#define FEE_STOP_SEC_VAR_INIT_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#if (FEE_PRV_DEBUGGING != FALSE)
extern Fee_Prv_stModuleTest_tst Fee_Prv_stModuleTest_st;
/* FEE_PRV_DEBUGGING */
#endif
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

/* Externals for functions */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"

#if (FEE_AR42_API_COMPLIANCE == STD_ON)
extern FUNC(void, FEE_CODE) Fee_Init(Fee_ConfigType const * ConfigPtr);
#else
extern FUNC(void, FEE_CODE) Fee_Init(void);
#endif

extern FUNC(void, FEE_CODE) Fee_Rb_EndInit(void);
extern FUNC(uint32, FEE_CODE) Fee_Rb_GetSectChngCnt(void);
extern FUNC(void, FEE_CODE) Fee_Cancel(void);
extern FUNC(void, FEE_CODE) Fee_MainFunction(void);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_Write(VAR(uint16, AUTOMATIC) Blocknumber,
                                                P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_Rb_VarLenWrite(VAR(uint16, AUTOMATIC) Blocknumber,
                                                         P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
                                                         VAR(uint16, AUTOMATIC) Length);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_Read(VAR(uint16, AUTOMATIC) Blocknumber,
                                               VAR(uint16, AUTOMATIC) BlockOffset,
                                               P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
                                               VAR(uint16, AUTOMATIC) Length);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_Rb_VarLenRead(VAR(uint16, AUTOMATIC) Blocknumber,
                                                        VAR(uint16, AUTOMATIC) BlockOffset,
                                                        P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
                                                        VAR(uint16, AUTOMATIC) Length);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_InvalidateBlock(VAR(uint16, AUTOMATIC) Blocknumber);
extern FUNC(Std_ReturnType, FEE_CODE) Fee_EraseImmediateBlock(VAR(uint16, AUTOMATIC) BlockNumber);
 #if(FEE_RB_MAINTAIN != FALSE)
    extern FUNC(Std_ReturnType, FEE_CODE) Fee_Rb_BlockMaintenance(VAR(uint16, AUTOMATIC) Blocknumber);
 #endif
extern FUNC(MemIf_StatusType, FEE_CODE) Fee_GetStatus(void);
extern FUNC(MemIf_JobResultType, FEE_CODE) Fee_GetJobResult(void);

extern FUNC(MemIf_JobResultType, FEE_CODE) Fee_Rb_GetAdapterJobResult(void);

extern FUNC(MemIf_Rb_MigrationResult_ten, FEE_CODE) Fee_Rb_GetMigrationResult(VAR(uint16, AUTOMATIC) Blocknumber);

extern FUNC(void, FEE_CODE) Fee_Rb_DisableBackgroundOperation(void);
extern FUNC(void, FEE_CODE) Fee_Rb_EnableBackgroundOperation(void);

#if (STD_ON == FEE_SET_MODE_SUPPORTED)
extern FUNC(void, FEE_CODE) Fee_SetMode(VAR(MemIf_ModeType, AUTOMATIC) Mode);
#endif

#if (STD_ON == FEE_VERSION_INFO_API)
extern FUNC(void, FEE_CODE) Fee_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr);
/* FEE_VERSION_INFO_API */
#endif

/* End of Fee section */
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/**************************  Code Section for Memory Mapping  stops here **************************/

/* FEE_H */
#endif


/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name___:$
**********************************************************************************************************************
</BASDKey>*/
