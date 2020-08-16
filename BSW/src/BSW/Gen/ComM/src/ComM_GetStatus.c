


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

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/*******************************************************************************
 * Function name    : ComM_GetStatus
 * Syntax           : Std_ReturnType ComM_GetStatus( ComM_InitStatusType* Status )
 * Description      : Returns the initialization status of the AUTOSAR Communication Manager.
 * Parameters       : Status -> COMM_UNINIT: The ComM is not initialized or not usable/
 *                              COMM_INIT: The ComM is initialized and usable.
 * Return value     : E_OK: Successfully return of initialization status
 *                    E_NOT_OK: Return of initialization status failed
 ******************************************************************************/

FUNC(Std_ReturnType,COMM_CODE) ComM_GetStatus
                                        (
                                        P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_VAR) Status
                                        )
{
    /* Local Variables Declaration */
    /* Local variable initialization */
    /****************************************DET STARTS HERE*****************************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* Check for Null pointer */
    if (Status == NULL_PTR)
    {
        /* Report DET with NULL parameter*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    /* DET Check for ComM initialization */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized status*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATUS_APIID,COMM_E_NOT_INITED);

        *Status = COMM_UNINIT;
        return E_NOT_INITIALIZED;
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */

    /****************************************DET ENDS HERE*****************************************/

    /* Update ComM initialization status */
    *Status = ComM_GlobalStruct.ComM_InitStatus;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

