

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

#include "NvM.h"

#include "Rte_NvM.h"

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 * This function returns the block ID used in NvM service which has caused the last DET error.
 *
 * Typical use case for this function is to be used as callback within the DET.
 * If NvM service which has caused the last DET error does not use any block or no DET error has occured yet,
 * then this function returns 0.
 *
 * \param[global in] NvM_Prv_idBlockCausingLastDetError_uo
 * Global variable to store block ID used in NvM service which has caused the last DET error
 *
 * \return
 * Block identifier used in NvM service which has caused the last DET error.
 */
NvM_BlockIdType NvM_Rb_GetBlockIdCausingLastDetError(void)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Service to get the block ID used in NvM service
    //                                               which has caused the last DET error

    return (NvM_Prv_idBlockCausingLastDetError_uo);
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
