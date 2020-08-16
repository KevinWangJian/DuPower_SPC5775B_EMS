

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

Std_ReturnType NvM_Rb_GetMigrationResult(NvM_BlockIdType BlockId, NvM_Rb_MigrationResult_ten *MigrationResultPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3052] Service to get the result of migration operation
    Std_ReturnType stReturn_u8 = E_NOT_OK;
    MemIf_Rb_MigrationResult_ten migrationResult_en;

    if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_RB_GET_MIGRATION_RESULT, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM635] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if(MigrationResultPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_GET_MIGRATION_RESULT, NVM_E_PARAM_DATA);
    }
    else
    {
        migrationResult_en = MemIf_Rb_GetMigrationResult(
                NvM_Prv_BlockDescriptors_acst[BlockId].idxDevice_u8,
                NvM_Prv_BlockDescriptors_acst[BlockId].idBlockMemIf_u16
                );

        switch(migrationResult_en)
        {
            case MEMIF_RB_MIGRATION_RESULT_INIT_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_INIT_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_NOT_NECESSARY_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_NOT_NECESSARY_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_NOT_DONE_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_NOT_DONE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_DEACTIVATED_E:
                *MigrationResultPtr = NVM_RB_MIGRATION_RESULT_DEACTIVATED_E;
            break;

            default:
                /* MR12 RULE 16.4 VIOLATION: Default can not be reached and has no effect here */
            break;
        }

        stReturn_u8 = E_OK;
    }

    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
