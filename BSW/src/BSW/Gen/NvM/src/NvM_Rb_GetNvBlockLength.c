

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#if (NVM_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"    // TRACE[NVM556] NvM module shall include Det.h
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

Std_ReturnType NvM_Rb_GetNvBlockLength(NvM_BlockIdType BlockId, uint16 *NvBlockLengthPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2791] Service for getting the configured NV block length in bytes of an NvM block
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_ERASE_NV_BLOCK, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
    }
    else if(NvBlockLengthPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_GET_NV_BLOCK_LENGTH, NVM_E_PARAM_DATA);
    }
    else
    {
        *NvBlockLengthPtr = *NvM_Prv_BlockDescriptors_acst[BlockId].nrBlockBytes_pu16;
        stReturn_u8 = E_OK;
    }

    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
