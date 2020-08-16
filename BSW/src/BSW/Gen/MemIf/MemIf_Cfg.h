

#ifndef MEMIF_CFG_H
#define MEMIF_CFG_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "MemIf_Types.h"
 

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/
#define MEMIF_VENDOR_ID                   6
#define MEMIF_MODULE_ID                   22
#define MEMIF_INSTANCE_ID                 0

#define MEMIF_SW_MAJOR_VERSION            11
#define MEMIF_SW_MINOR_VERSION            0
#define MEMIF_SW_PATCH_VERSION            0

#define MEMIF_AR_RELEASE_MAJOR_VERSION    4
#define MEMIF_AR_RELEASE_MINOR_VERSION    2
#define MEMIF_AR_RELEASE_REVISION_VERSION 2

/* Switch for version info api */
#define MEMIF_VERSION_INFO_API      STD_ON

/* Switch for dev error detect */
#define MEMIF_DEV_ERROR_DETECT      STD_OFF
#define MEMIF_FEE_USED      STD_OFF
#define MEMIF_NUM_OF_EA_DEVICES      1
#define MEMIF_FEE_AND_EA_USED      STD_OFF
#define MEMIF_MIN_NUM_DEVICES            1
#define MEMIF_MAX_NUM_DEVICES            2


/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define MemIf_Read(DeviceIndex,BlockNumber,BlockOffset,DataBufferPtr,Length)            Ea_Read(BlockNumber,BlockOffset,DataBufferPtr,Length)
#define MemIf_Write(DeviceIndex,BlockNumber,DataBufferPtr)                              Ea_Write(BlockNumber,DataBufferPtr)
#define MemIf_InvalidateBlock(DeviceIndex,BlockNumber)                                  Ea_InvalidateBlock(BlockNumber)
#define MemIf_GetStatus(DeviceIndex)                                                    Ea_GetStatus()
#define MemIf_GetJobResult(DeviceIndex)                                                 Ea_GetJobResult()
#define MemIf_Cancel(DeviceIndex)                                                       Ea_Cancel()
#define MemIf_EraseImmediateBlock(DeviceIndex,BlockNumber)                              Ea_EraseImmediateBlock(BlockNumber)
#define MemIf_Rb_BlockMaintenance(DeviceIndex,BlockNumber)                              Ea_Rb_BlockMaintenance(BlockNumber)

/* Problem 72560 / Defect 72919 / Defect Fix 72958: EA only configured ? --> MemIf functions should be mapped to:
 *      Ea_Rb_VarLenRead(BlockNumber,BlockOffset,DataBufferPtr,Length)
 *      Ea_Rb_VarLenWrite(BlockNumber,DataBufferPtr,Length)
 *      Ea_Rb_GetMigrationResult(BlockNumber)
 * But the features behind these functions are not available for EA (only for Fee, if used).
 *
 * Consequently:
 * - These APIs are missing within the Ea
 * - Generating the a.m. Ea function mapping within MemIf will therefore end up in compiler errors within projects just using Ea
 * - As a consequence, just default returns (refer to C implementation in MemIf_Rb_MainFunction.c) are generated 
*/
#define MemIf_Rb_VarLenRead(DeviceIndex,BlockNumber,BlockOffset,DataBufferPtr,Length)   (E_NOT_OK)
#define MemIf_Rb_VarLenWrite(DeviceIndex,BlockNumber,DataBufferPtr,Length)              (E_NOT_OK)
#define MemIf_Rb_GetMigrationResult(DeviceIndex,BlockNumber)                            (MEMIF_RB_MIGRATION_RESULT_INIT_E)


/* MEMIF_CFG_H */
#endif
