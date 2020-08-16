


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
#include "Fls.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if(STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
/* Version check deactivated due to incompatabality with CC-AS (AR3.1)
 * #if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
*/
#endif


#if(FEE_PRESENT == 1)

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
/**
 *********************************************************************
 * Fee_Cancel(): Cancel the currently running NvM job
 *
 * This function cancels the currently ongoing NvM job.
 *
 * Hint: This interface is currently not supported!
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_Cancel(void)
{
    /* This interface is currently not supported */
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
