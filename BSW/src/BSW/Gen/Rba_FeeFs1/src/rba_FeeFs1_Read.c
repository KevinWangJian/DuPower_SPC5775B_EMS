


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
/**
 *********************************************************************
 * Fee_Read(): Service to initiate a read job
 *
 * This function places a read job to the FEE order queue.
 * If Development Error Detection is enabled, the function checks
 * the FEE module status, the user's block number and the data
 * buffer pointer additionaly.
 *
 * \param    Blocknumber:   Auto generated Fee block number which
 *                          corresponds to the respective persistent ID
 * \param    BlockOffset:   Offset within the data block
 * \param    DataBufferPtr: Pointer to data buffer
 * \param    Length:        Data length
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
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Std_ReturnType, FEE_CODE) Fee_Read(VAR(uint16, AUTOMATIC) Blocknumber,
                                        VAR(uint16, AUTOMATIC) BlockOffset,
                                        P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
                                        VAR(uint16, AUTOMATIC) Length)
{
    VAR(Std_ReturnType,AUTOMATIC) xRetVal = E_NOT_OK;       /* Default return value */
    Std_ReturnType retModuleState_u8 , retAdrPtr_u8 , retBlkCfg_u8 , retBlkOfs_u8 , retBlkLen_u8 ;
    /* Check the FEE module status, the user's block number/offset/length and the data buffer pointer */
    /* MR12 RULE 13.5 VIOLATION: Multiple parameter validation required for robust design. */
    retModuleState_u8 = Fee_CheckModuleSt(FEE_SID_READ);
    retAdrPtr_u8      = Fee_CheckAdrPtr(FEE_SID_READ, (const uint8*)DataBufferPtr);
    retBlkCfg_u8      = Fee_CheckBlockCfg(FEE_SID_READ , Blocknumber);
    retBlkOfs_u8      = Fee_CheckBlkOfs(FEE_SID_READ, Blocknumber, BlockOffset);
    retBlkLen_u8      = Fee_CheckBlkLen(FEE_SID_READ, Blocknumber, BlockOffset, Length);

    if(     (retModuleState_u8 != E_OK ) ||
            (retAdrPtr_u8      != E_OK ) ||
            (retBlkCfg_u8      != E_OK ) ||
            (retBlkOfs_u8      != E_OK ) ||
            (retBlkLen_u8      != E_OK ))
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
    xRetVal = Fee_HLPlaceOrder(Blocknumber, BlockOffset, DataBufferPtr, Length, FEE_READ_ORDER);

    return (xRetVal);
}

/**
 *********************************************************************
 * Fee_Rb_VarLenRead(): Service to initiate a read job
 *                      with variable length
 *
 * This functionality is not supported in Fs1. Therefore this function
 * returns always E_NOT_OK. This is just a stub to pass the linker in
 * case FEE is used and FS1 target.
 *
 * \param    Blocknumber:   Auto generated Fee block number which
 *                          corresponds to the respective persistent ID
 * \param    DataBufferPtr: Pointer to data buffer
 * \param    Length:        Block length
 *
 * \retval   E_NOT_OK:      Order was not placed
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.13 VIOLATION: This is a dummy function for FeeFs1. */
FUNC(Std_ReturnType, FEE_CODE) Fee_Rb_VarLenRead(VAR(uint16, AUTOMATIC) Blocknumber,
                                                 VAR(uint16, AUTOMATIC) BlockOffset,
                                                 P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
                                                 VAR(uint16, AUTOMATIC) Length)
{
    /* unused parameters */
    (void)(Blocknumber);
    (void)(BlockOffset);
    (void)(DataBufferPtr);
    (void)(Length);

   /* Return with an error */
   return (E_NOT_OK);
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
