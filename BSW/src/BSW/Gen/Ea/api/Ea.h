

#ifndef EA_H
#define EA_H

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 ****************************************************************************************************
 * Includes
 ****************************************************************************************************
 */
#include "Std_Types.h"
#include "Ea_Cfg.h"
#include "Ea_Stubs.h"

/* For Ea test purposes only */
#define EA_PRV_DEBUGGING FALSE
#if (EA_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
/* EA_PRV_DEBUGGING */
#endif

#if (EA_PRESENT == 1)

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/* EA013: Check whether AR versions are defined correctly */
#if (!defined(STD_TYPES_AR_RELEASE_MAJOR_VERSION) || \
    (STD_TYPES_AR_RELEASE_MAJOR_VERSION != EA_AR_RELEASE_MAJOR_VERSION))
// #error "AUTOSAR major version undefined or mismatch"
#endif

#if (!defined(STD_TYPES_AR_RELEASE_MINOR_VERSION) || ((STD_TYPES_AR_RELEASE_MINOR_VERSION != 0) && \
                                                      (STD_TYPES_AR_RELEASE_MINOR_VERSION != 2)))
//#error "AUTOSAR minor version undefined or mismatched"
#endif
/*
 ***************************************************************************************************
 * Type definition and structures
 ***************************************************************************************************
 */

/* Error codes for API used for Ea module */
/* [EA049]: Development error values are of type uint8 */
#define EA_E_NOT_INITIALIZED            0x01        /* Error code for an uninitialized module */
#define EA_E_INVALID_BLOCK_NO           0x02        /* Error code for invalid block number */
#define EA_E_INCOMPATIBLE_VERSIONS      0x03        /* Error code for included incompatible module versions */
#define EA_E_RB_BLOCK_LENGTH_MISMATCH   0x10        /* Error code for block length mismatch */
#define EA_E_RB_MIGRATION_FAILED        0x11        /* Error code for unsuccessful migration */
#define EA_E_RB_MIGRATION_NOT_POSSIBLE  0x12        /* Error code for migration not possible: not enough free space*/

/* API Service IDs used for DET module */
#define EA_SID_INIT                 0x00        /* Service ID for the EA Init function */
#define EA_SID_SETMODE              0x01        /* Service ID for the EA set mode function */
#define EA_SID_READ                 0x02        /* Service ID for the EA read function */
#define EA_SID_WRITE                0x03        /* Service ID for the EA write function */
#define EA_SID_CANCEL               0x04        /* Service ID for the EA job cancel function */
#define EA_SID_GETSTATUS            0x05        /* Service ID for the EA get status function */
#define EA_SID_GETJOBRESULT         0x06        /* Service ID for the EA get job result function */
#define EA_SID_INVALIDATEBLOCK      0x07        /* Service ID for the EA invalidate block function */
#define EA_SID_GETVERSIONINFO       0x08        /* Service ID for the EA get version info function */
#define EA_SID_ERASE                0x09        /* Service ID for the EA erase immediate block function */
#define EA_SID_RB_MAINTENANCE       0x0A        /* Service ID for the EA repair redundant block function */
#define EA_SID_MAINFUNCTION         0x12        /* Service ID for the EA main function */
#define EA_SID_RB_MIGRATIONINIT     0x13        /* Service ID for the EA migration init */
#define EA_SID_RB_MIGRATION         0x14        /* Service ID for the EA migration */

/* Ea Migration possible states, Migration is not applicable for Boot Mode */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
#define EA_RB_MIGRATION_NOTNEEDED 	0x00			/* Migration Marker is Not changed Migration is Not Needed */
#define EA_RB_MIGRATION_RUNNING		0x01			/* Migration is Currently Running */
#define EA_RB_MIGRATION_FINISHED	0x02			/* Migration is completed sucessfully*/
#define EA_RB_MIGRATION_ERROR		0x03			/* Migration Exited with Error */
#endif

/* Internal Ea debug structure for time measurement */
#if (EA_PRV_DEBUGGING != FALSE)
/* Time measurements */
typedef struct
{
    uint32 Ea_InitTimeDiff_u32;                 /* Diff time for the EA initialization function */
    uint32 Ea_DataReadDiff_u32;                 /* Diff time for the EA read all block header */
    uint32 Ea_WriteTimeStart_u32;               /* Start time for the EA write function */
    uint32 Ea_WriteTimeEnd_u32;                 /* End time for the EA write function */
    uint32 Ea_WriteTimeDiff_u32;                /* Diff time for the EA write function */
    uint32 Ea_ReadTimeStart_u32;                /* Start time for the EA read function */
    uint32 Ea_ReadTimeEnd_u32;                  /* End time for the EA read function */
    uint32 Ea_ReadTimeDiff_u32;                 /* Diff time for the EA read function */
    uint32 Ea_MigrationTimeStart_u32;           /* Start time for the EA migration function, same to Initialization start */
    uint32 Ea_MigrationTimeDiff_u32;            /* Diff time for the EA migration function */
}Ea_Prv_stModuleTest_tst;
/* EA_PRV_DEBUGGING */
#endif

/*
 ***************************************************************************************************
 * Type definition and enums
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Externals
 ***************************************************************************************************
 */
#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
extern MemIf_JobResultType Ea_JobResult;                /* Job Result of latest job */
#if (EA_PRV_DEBUGGING != FALSE)
extern Ea_Prv_stModuleTest_tst Ea_Prv_stModuleTest_st;
#endif
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"
extern MemIf_StatusType Ea_GlobModuleState_st;          /* Main state of the EA driver */
#define EA_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
extern void Ea_MainFunction(void);
extern void Ea_Init(void);
extern void Ea_Rb_EndInit(void);
extern Std_ReturnType Ea_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length);
extern Std_ReturnType Ea_Write(uint16 BlockNumber, uint8* DataBufferPtr);
extern Std_ReturnType Ea_Rb_BlockMaintenance(uint16 BlockNumber);
extern void Ea_Cancel(void);
extern MemIf_JobResultType Ea_GetJobResult(void);
extern MemIf_StatusType Ea_GetStatus(void);
extern void Ea_SetMode(MemIf_ModeType Mode);
extern void Ea_GetVersionInfo(Std_VersionInfoType* VersioninfoPtr);
extern Std_ReturnType  Ea_EraseImmediateBlock(uint16 BlockNumber);
extern Std_ReturnType  Ea_InvalidateBlock(uint16 BlockNumber);
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
extern uint8 Ea_Rb_MigrationStatus(void);
#endif

#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* End of #if (EA_PRESENT == 1) */
#endif
/* EA_H */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name___:$
**********************************************************************************************************************
</BASDKey>*/

