

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */
#include "Ea.h"

#if (EA_PRESENT == 1)
/*
 *********************************************************************
 * Includes
 *********************************************************************
 */

#include "Ea_Cfg_SchM.h"
#include "Ea_Prv.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/**
 *********************************************************************
 * Ea_Cancel():
 *
 * [EA088]
 * Cancels an ongoing job
 *
 * This function cancels an ongoing EA job. The read, write and compare
 * functionality will be stopped after the configured number of bytes for one
 * main function call have been written or read
 * (EaMaxReadFastMode/EaMaxReadNormalMode,
 * EaMaxWriteFastMode/EaMaxWriteNormalMode).
 * An ongoing erase order will not be aborted (the suspend/resume feature
 * must be used instead).
 * Nevertheless, the EA will be able to accept new orders immediately.
 * A new job (read, write, compare, ...) is only accepted immediately for the device
 * that requested the cancel operation. A MEMIF_BUSY is returned to all other
 * devices until the underlying HW has finished its operation.
 *
 * \param   none
 * \return
 * \retval  none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Cancel(void)
{

    /* [EA132]:
     * If development error detection for the module EA is enabled: the function
     * Ea_Cancel shall check that the module has been initialized. If this check
     * fails, the function Ea_Cancel shall raise the development error
     * EA_E_NOT_INITIALIZED and return without performing the requested function.
     */

    if(Ea_Rb_CheckInit(EA_SID_CANCEL) != E_OK)
    {
        /* Det Check not ok: do nothing */
    }
    else
    {
        if((Ea_GlobModuleState_st == MEMIF_BUSY) || (Ea_GlobModuleState_st == MEMIF_BUSY_INTERNAL))
        {
            /* Disable interrupts */
            SchM_Enter_Ea_Order();

            /* Set cancel request status */
            Ea_Rb_stCancel_u8 = EA_RB_ST_CANCEL_REQUESTED;

            /* Reset the Ea job result */
            Ea_JobResult = MEMIF_JOB_CANCELED;

            Ea_Rb_Order_st.OrderType_en = EA_RB_NO_ORDER_E;

            /* Reset Ea main state */
            Ea_GlobModuleState_st = MEMIF_IDLE;

            /* Enable interrupts */
            SchM_Exit_Ea_Order();
        }
    }
}
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

