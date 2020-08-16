

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

Std_ReturnType NvM_Rb_GetBlockId(uint16 PersistentId, NvM_BlockIdType *BlockIdPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2840] Service to get the NvM block ID using the persistent ID input parameter
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    if (BlockIdPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3114] Set block ID to 0 if NvM service does not use any block ID
        NvM_Prv_SetBlockIdCausingLastDetError(0u);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_GET_BLOCK_ID, NVM_E_PARAM_DATA);
    }

    else
    {
        uint16 left_u16 = 0;                                            // left_u16   : [0  .. 65534]
        sint32 right_s32 = (sint32)(NVM_PRV_NR_PERSISTENT_IDS - 1u);    // right_s32  : [-1 .. 65533]   ;   #Persis IDs : [0 .. 65534]
        uint16 middle_u16;                                              // middle_u16 : [0  .. 65533]

        while((sint32)left_u16 <= right_s32)
        {
            middle_u16 = left_u16 + (uint16)(((uint16)right_s32 - left_u16) / 2);

            if (PersistentId == NvM_Prv_PersId_BlockId_acst[middle_u16].PersistentId_u16)
            {
                *BlockIdPtr = NvM_Prv_PersId_BlockId_acst[middle_u16].BlockId_u16;
                stReturn_u8 = E_OK;
                break;
            }
            else if (PersistentId > NvM_Prv_PersId_BlockId_acst[middle_u16].PersistentId_u16)
            {
                left_u16 = middle_u16 + 1;
            }
            else
            {
                right_s32 = middle_u16 - 1;
            }
        }
        // The persistent ID is not found if (left_u16 > right_s32) after the while loop. In this case E_NOT_OK is returned.
    }

    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
