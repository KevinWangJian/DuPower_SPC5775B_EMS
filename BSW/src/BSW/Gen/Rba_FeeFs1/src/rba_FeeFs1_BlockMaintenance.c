


/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Fee.h"
#include "rba_FeeFs1_Prv.h"

#if (FEE_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
#endif

#if(STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
/* Version check deactivated due to incompatabality with CC-AS (AR3.1)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
*/
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
 #if(FEE_RB_MAINTAIN != FALSE)

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
/**
 *********************************************************************
 * Fee_Rb_Maintenance(): Service to initiate a write job
 *
 * This function places a write job to the FEE order queue.
 * If Development Error Detection is enabled, the function checks
 * the FEE module status, the user's block number and the data
 * buffer pointer additionaly.
 *
 * \param    Blocknumber:   Auto generated Fee block number which
 *                          corresponds to the respective persistent ID
 * \param    DataBufferPtr: Pointer to data buffer
 * \return   Function success
 * \retval   E_OK:              Order was successfully placed
 * \retval   E_NOT_OK:          Order was not placed because the
 *                              respective order queue entry is
 *                              not empty or the module has not been
 *                              initialized yet
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Std_ReturnType, FEE_CODE) Fee_Rb_BlockMaintenance(VAR(uint16, AUTOMATIC) Blocknumber)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_NOT_OK;      /* Default return value */
    Std_ReturnType retModuleState_u8 , retBlockCfg_u8;

    retModuleState_u8 = Fee_CheckModuleSt(FEE_SID_MAINTAIN);
    retBlockCfg_u8    = Fee_CheckBlockCfg(FEE_SID_MAINTAIN, Blocknumber);

    /* Check the FEE module status, the user's block number and the data buffer pointer */
    /* MR12 RULE 13.5 VIOLATION: Same error must be reported either if module is not idle or incorrect id is passed. */
    if((retModuleState_u8 != E_OK) ||
       (retBlockCfg_u8 != E_OK))
    {
        /* Return with an error */
        return (E_NOT_OK);
    }

    /* Hint: The FEE module status will be set to MEMIF_BUSY / _INTERNAL inside the function Fee_HLPlaceOrder.
     *       The FEE job result will be set to MEMIF_JOB_PENDING inside the Fee_MainFunction.
     *       Contraray to the AR specification Eep - Orders can be added if NvM or internal orders are
     *       currently being processed or vice versa. Only if an order of the same user is already in the
     *       queue the function Fee_HLPlaceOrder will return with E_NOT_OK.
     *       --> No check of the FEE module status (MEMIF_IDLE || MEMIF_BUSY_INTERNAL) before placing
     *           the order */

    /* Place the order only if the module has been intialized (already checked in Fee_CheckModuleSt()) */
    xRetVal = Fee_HLPlaceOrder(Blocknumber, 0, NULL_PTR, 0, FEE_MAINTAIN_ORDER);


    /* Only for debugging purposes */
    #if (FEE_PRV_DEBUGGING != FALSE)
    if(xRetVal == E_OK)
    {
        Fee_Prv_stModuleTest_st.Fee_MaintainTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
    }
    /* FEE_PRV_DEBUGGING */
    #endif

    return (xRetVal);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
 /* FEE_RB_MAINTAIN != FALSE */
 #endif
/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
