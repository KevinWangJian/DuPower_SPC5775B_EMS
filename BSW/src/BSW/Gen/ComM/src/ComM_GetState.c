


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
 * Function name    : ComM_GetState
 * Syntax           : Std_ReturnType ComM_GetState( NetworkHandleType Channel, ComM_StateType* State )
 * Description      : Read the current state of ComM Channel.
 * Parameters       : Channel-> The Network Channel for the requested state of ComM state machine.
 *                    State-> State of the ComM state machine
 * Return value     : E_OK: Successfully return current state of ComM state machine
 *                    E_NOT_OK: Return of current state of ComM state machine failed
 *                    COMM_E_UNINIT: ComM not initialized
 ******************************************************************************/

FUNC(Std_ReturnType, COMM_CODE) ComM_GetState
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        P2VAR(ComM_StateType, AUTOMATIC, COMM_VAR) State
                                        )
{
    /* Local Variables Declaration */
    /* Local variable initialization */
    /************************************DET CHECK STARTS HERE*********************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    /* Check for ComM Initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    /* Check if the channel passed is valid */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }

    /* Check if the pointer passed is null pointer */
    if (State == NULL_PTR)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_GET_STATE_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /************************************DET CHECK ENDS HERE**********************************/

    /* Update the channel's current state */
    *State = ComM_ChannelStruct[Channel].ChannelState_e;
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

