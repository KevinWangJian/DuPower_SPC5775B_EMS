

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM.h"

#include "NvM_Prv.h"
#include "NvM_Prv_ErrorDetection.h"

/*
 **********************************************************************************************************************
 * NvM-private code
 **********************************************************************************************************************
 */
/**
 * \brief
 * This private function checks the initialization of the NvM and reports the DET error NVM_E_NOT_INITIALIZED
 * when the NvM is not yet initialized.
 *
 * \param[in] idService_u8
 * ID of the service which checks the NvM initialization. This ID will be reported together with DET error.
 * \param[in] idBlock_uo
 * Block ID used in NvM service causing last DET error.
 *
 * \return
 * Initialization status of the NvM:
 * - TRUE = NvM initialized
 * - FALSE = NvM not initialized
 */
/* MR12 RULE 2.7 VIOLATION: For disabled DET parameter idService_u8 will not be used and this has no effect here */
boolean NvM_Prv_IsNvmInitialized(uint8 idService_u8, NvM_BlockIdType idBlock_uo)
{
    if (!NvM_Prv_Main_st.isInitialized_rAM_b)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(idBlock_uo);
        NVM_PRV_REPORT_DET_ERROR(idService_u8, NVM_E_NOT_INITIALIZED);
    }

    return (NvM_Prv_Main_st.isInitialized_rAM_b);
}

/**
 * \brief
 * This NvM private function checks the passed block ID and reports the DET error NVM_E_PARAM_BLOCK_ID
 * if this ID is invalid.
 *
 * \param[in] idService_uo
 * ID of the service which checks the block ID. This service ID will be reported together with DET error.
 * \param[in] idBlock_uo
 * Block ID to be checked for validness.
 * \param[in] idBlockCausingError_uo
 * Block ID to be reported as one which has caused last DET error.
 * Primarily auxiliary services sets different block ID as one which has caused last error.
 *
 * \return
 * Validness of the passed block ID:
 * - TRUE = block ID is valid
 * - FALSE = block ID is invalid
 */
/* MR12 RULE 2.7 VIOLATION: For disabled DET parameter idService_u8 will not be used and this has no effect here */
boolean NvM_Prv_IsBlockIdValid(uint8 idService_u8, NvM_BlockIdType idBlock_uo, NvM_BlockIdType idBlockCausingError_uo)
{
    // TRACE[NVM311] Allow applications to send requests for block ID 1
    boolean isBlockIdValid_b = (idBlock_uo >= NVM_CFG_FIRST_USED_BLOCK) && (idBlock_uo < NVM_CFG_NR_BLOCKS);

    if (!isBlockIdValid_b)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(idBlockCausingError_uo);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        // TRACE[NVM023] Report DET errors when NvM is called with wrong parameters
        NVM_PRV_REPORT_DET_ERROR(idService_u8, NVM_E_PARAM_BLOCK_ID);
    }

    return isBlockIdValid_b;
}
