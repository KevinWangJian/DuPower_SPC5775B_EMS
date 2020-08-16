


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
 * Function name    : ComM_ReadInhibitCounter
 * Syntax           : Std_ReturnType ComM_GetState( uint16 * CounterValue )
 * Description      : API to get the inhibition counter value
 * Parameters       : CounterValue-> pointer to update inhibition counter value.
 * Return value     : E_OK: Successfully returned Inhibition Counter
 *                    E_NOT_OK: Return of Inhibition Counter failed
 *                    COMM_E_UNINIT: ComM not initialized
 ******************************************************************************/

FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter
                                        (
                                          P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
                                        )
{
    /* Local Variables Declaration */
    /* Local variable initialization */
    /************************************DET CHECK STARTS HERE*********************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    /* Check for ComM Initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_READ_INHIBIT_COUNTER_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    /* Check if the pointer passed is null pointer */
    if (CounterValue == NULL_PTR)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_READ_INHIBIT_COUNTER_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /************************************DET CHECK ENDS HERE**********************************/


    /* Update the inhibition counter value */
    *CounterValue = ComM_GlobalStruct.ComM_InhibitCounter_u16;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif  /* #if (COMM_INHIBITION_ENABLED) */

