

#ifndef MEMIF_H
#define MEMIF_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "MemIf_Cfg.h"
#if (MEMIF_FEE_USED == STD_ON)
#include "Fee.h"
#endif
#if (MEMIF_NUM_OF_EA_DEVICES > 0)
#include "Ea.h"
#endif

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/
#define FEE_DEVICE_INDEX   1
#define EA_DEVICE_INDEX    2

#if (MEMIF_DEV_ERROR_DETECT != FALSE)
/* Error codes for API used for DET module */
#define MEMIF_E_PARAM_DEVICE          0x01      /* Error code for wrong device index */

/* API Service IDs used for DET module */
#define MEMIF_SID_CHECK_INDEX       0x81        /* Service ID for Memif chcek device index function.
                                                AUTOSAR spec doesn't specify any value for this checking and
                                                hence 0x81 is used */
#endif

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

/* Functions: asynchronous */
#define MEMIF_START_SEC_CODE
#include "MemIf_MemMap.h"

#if(MEMIF_VERSION_INFO_API == STD_ON)
extern void MemIf_GetVersionInfo( Std_VersionInfoType* VersionInfoPtr );
#endif /* MEMIF_VERSION_INFO_API */

extern MemIf_StatusType MemIf_Rb_GetStatus(void);
extern void MemIf_CheckDeviceIndex(uint8 DeviceIndex);

/* Functions: scheduled */
extern void MemIf_Rb_MainFunction(void);

#define MEMIF_STOP_SEC_CODE
#include "MemIf_MemMap.h"

/* MEMIF_H */
#endif
