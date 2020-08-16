
#include "Ea.h"

#if (EA_PRESENT == 1)
#include "Ea_Prv.h"
#include "Eep.h"


/* *********************************************************************************************************************
 * Req:                 EA085
 *
 * Service name:        EA_SetMode
 * Syntax:
 *                      void EA_SetMode( MemIf_ModeType Mode )
 * Service ID[hex]:     0x01
 * Sync/Async:          Synchronous
 * Reentrancy:          Non Reentrant
 * Parameters (in):     Mode = Desired mode for the underlying flash driver
 * Parameters (inout):  None
 * Parameters (out):    None
 * Return value:        None
 * Description:         Service to call the Ea_SetMode function of the underlying flash driver.
 * ****************************************************************************************************************** */
/* [EA150]:
 * The function Ea_SetMode shall be enabled / disabled via the pre-compile time parameter EaSetModeSupported such that
 * the function is completely removed from the code if it is disabled. */
#if (EA_SET_MODE_SUPPORTED != FALSE)
#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
FUNC(void,EA_CODE) Ea_SetMode( VAR(MemIf_ModeType,AUTOMATIC) Mode)
{
    /* [EA129]:
     * If development error detection for the module EA is enabled: the function Ea_SetMode shall check that the module
     * has been initialized. If this check fails, the function Ea_SetMode shall raise the development error
     * EA_E_NOT_INITIALIZED and return without performing the requested function. */

    if (Ea_Rb_CheckInit(EA_SID_SETMODE) != E_OK)
    {
        /* Do nothing */
    }
    else
    {
        if (Ea_GlobModuleState_st != MEMIF_BUSY)
        {

            /* [EA020]:
             * If supported by the underlying hardware and device driver, the function EA_SetMode shall call the function
             * Ea_SetMode of the underlying flash driver with the given Mode parameter.
             *
             * Example:
             * During normal operation of an ECU the EA module and underlying device driver shall use as few (runtime)
             * resources as possible, therefore the flash driver is switched to slow mode. During startup and especially
             * during shutdown it might be desirable to read / write the NV memory blocks as fast as possible, therefore the
             * EA and the underlying device driver could be switched into fast mode.*/

            Eep_SetMode(Mode);
        }
    }
}
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
#endif
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

