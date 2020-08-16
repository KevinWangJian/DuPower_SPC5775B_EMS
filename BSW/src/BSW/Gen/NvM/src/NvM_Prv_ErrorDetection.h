


#ifndef NVM_PRV_ERRORDETECTION_H
#define NVM_PRV_ERRORDETECTION_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM_Cfg.h"

#if (NVM_DEV_ERROR_DETECT == STD_ON)
// TRACE[NVM556] NvM module shall include Det.h
# include "Det.h"
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

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
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

extern boolean NvM_Prv_IsNvmInitialized(uint8 idService_u8, NvM_BlockIdType idBlock_uo);
extern boolean NvM_Prv_IsBlockIdValid(uint8 idService_u8,
                                      NvM_BlockIdType idBlock_uo,
                                      NvM_BlockIdType idBlockCausingError_uo);

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"


/* NVM_PRV_ERRORDETECTION_H */
#endif
