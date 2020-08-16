


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

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

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


#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_EraseImmediateBlock(): Service to erase a logical block
 *
 * The functionality of this interface is not supported. This is a
 * dummy function to ensure compatability with the MemIf and Ea.
 *
 * \param    BlockNumber:   Number of logical block(persistent ID)
 * \return   Function success
 * \retval   E_OK:          Order was successfully placed
 * \retval   E_NOT_OK:      Order was not placed because the
 *                          respective order queue entry is
 *                          not empty or the module has not been
 *                          initialized yet.
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Std_ReturnType, FEE_CODE) Fee_EraseImmediateBlock(VAR(uint16, AUTOMATIC) BlockNumber)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_NOT_OK;      /* Default return value */

	(void)BlockNumber;

	return (xRetVal);
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
