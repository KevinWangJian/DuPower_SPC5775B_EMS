


/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "ComM_Priv.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */

#if (COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/*******************************************************************************
 * Function name    : ComM_ResetInhibitCounter
 * Syntax           : Std_ReturnType ComM_ResetInhibitCounter( void )
 * Description      : Reset the inhibition counter.
 * Parameters       : none
 * Return value     : E_OK: Successfully reset of Inhibit COMM_FULL_COMMUNICATION Counter
 *                    E_NOT_OK: Reset of Inhibit COMM_FULL_COMMUNICATION Counter failed
 *                    COMM_E_UNINIT: ComM not initialized
 ******************************************************************************/

FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter
                                        (
                                        void
                                        )
{
    /* Local Variables Declaration */
    /* Local variable initialization */
    /************************************DET CHECK STARTS HERE*********************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    /* Check for ComM Initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_RESET_INHIBIT_COUNTER_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /************************************DET CHECK ENDS HERE**********************************/


    /* Reset the inhibition counter */
    ComM_GlobalStruct.ComM_InhibitCounter_u16 = C_ZERO;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /* #if (COMM_INHIBITION_ENABLED) */

