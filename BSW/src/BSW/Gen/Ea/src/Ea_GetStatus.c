

#include "Ea.h"

#if (EA_PRESENT == 1)

#include "Ea_Prv.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/* *********************************************************************************************************************
 * Req:                 EA089:
 *
 * Service name:        Ea_GetStatus
 * Syntax:
 *          MemIf_StatusType Ea_GetStatus( void )
 *
 * Service ID[hex]:     0x05
 * Sync/Async:          Synchronous
 * Reentrancy:          Non Reentrant
 * Parameters (in):     None
 * Parameters (inout):  None
 * Parameters (out):    None
 * Return value:        MemIf_StatusType - MEMIF_UNINIT: The Ea module has not been initialized.
 *                                         MEMIF_IDLE: The Ea module is currently idle.
 *                                         MEMIF_BUSY: The Ea module is currently busy.
 *                                         MEMIF_BUSY_INTERNAL: The Ea module is busy with internal management
 *                                                              operations.
 * Description:         Service to return the status.
 * ****************************************************************************************************************** */
MemIf_StatusType Ea_GetStatus(void)
{
    MemIf_StatusType stStatusLoc_st = Ea_GlobModuleState_st;

    /* Check Ea initialization status */
    /* [EA133]:
     * If development error detection for the module EA is enabled: the function Ea_GetStatus shall check that the module has been
     * initialized. If this check fails, the function Ea_GetStatus shall raise the development error EA_E_NOT_INITIALIZED and return
     * MEMIF_UNINIT to the caller without performing the requested function. */
    if(Ea_Rb_CheckInit(EA_SID_GETSTATUS) != E_OK)
    {
        stStatusLoc_st = MEMIF_UNINIT;
    }

    return stStatusLoc_st;
}
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/*#if (EA_PRESENT == 1)*/
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

