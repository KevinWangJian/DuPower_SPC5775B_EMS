


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
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
   // #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
  //  #error "AUTOSAR minor version undefined or mismatched"
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
#if (STD_ON == FEE_SET_MODE_SUPPORTED)
/**
 *********************************************************************
 * Fee_SetMode(): Change the Fls mode type
 *
 * This function sets the mode of the underlying Fls driver either
 * to fast or slow mode. The number of bytes that read / written
 * during one main function call will be changed.
 *
 * Note:
 * During normal operation of an ECU the FEE module and underlying
 * device driver shall use as few (runtime) resources as possible,
 * therefore the flash driver is switched to slow mode.
 * During startup and especially during shutdown it might be
 * desirable to read / write the NV memory blocks as fast as possible,
 * therefore the FEE and the underlying device driver could be
 * switched into fast mode.
 *
 * \param    Mode:          MEMIF_MODE_SLOW, MEMIF_MODE_FAST
 * \return   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_SetMode(VAR(MemIf_ModeType, AUTOMATIC) Mode)
{
    /* Check the FEE module status */
    if(Fee_CheckModuleSt(FEE_SID_SETMODE) != E_OK)
    {
        /* Return to the caller */
        return;
    }

    /* Place the order only if the module state is MEMIF_IDLE (independent from the DET setting) */
    if(Fee_GlobModuleState_st == MEMIF_IDLE)
    {
        /* Reset the mode type */
        Fls_SetMode(Mode);
    }
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* (STD_ON == FEE_SET_MODE_SUPPORTED) */
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
