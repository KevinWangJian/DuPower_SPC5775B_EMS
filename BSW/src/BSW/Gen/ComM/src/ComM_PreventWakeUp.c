


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

#if (COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/*******************************************************************************
 * Function name    : ComM_PreventWakeUp
 * Syntax           : Std_ReturnType ComM_PreventWakeUp( NetworkHandleType Channel, boolean Status )
 * Description      : API to request or release buswake up inhibition for a channel
 * Parameters       : Channel-> The Network Channel for the requested state of ComM state machine.
 *                    Status-> Desired state of wakeup inhibition.
 * Return value     : E_OK: Successfully changed wake up status for the channel
 *                    E_NOT_OK: Changed of wake up status for the channel failed
 *                    COMM_E_UNINIT: ComM not initialized
 ******************************************************************************/
/* MR12 RULE 8.3 VIOLATION:Two declarations exists for this api. One is in ComM.h & another generated by RTE. Hence,the difference in identifiers.*/
FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        VAR(boolean, COMM_VAR) Status
                                        )
{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

    /* Local variable initialization */
   channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    /************************************DET CHECK STARTS HERE*********************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    /* Check for ComM Initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PREVENT_WAKEUP_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }

    /* Check if the channel passed is valid */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PREVENT_WAKEUP_APIID,COMM_E_WRONG_PARAMETERS);
        return E_NOT_OK;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /************************************DET CHECK ENDS HERE**********************************/


    /* Update the channel's inhibition status, this update is done irrespective of ECUGroupClassification,
     * But, while processing this in Main function ECUGroupClassification is considered */

    if((COMM_GET_PREVENT_WAKEUP((channelRamPtr_ps->InhibitionReqStatus_u8))) != Status)
    {
        SchM_Enter_ComM_LimitationNoNest();

        if(Status != FALSE)
        {
            COMM_SET_PREVENT_WAKEUP((channelRamPtr_ps->InhibitionReqStatus_u8));
        }
        else
        {
            COMM_CLR_PREVENT_WAKEUP((channelRamPtr_ps->InhibitionReqStatus_u8));
        }

        /* For all users and PNC's of the channel, evaluate the Wakeup inhibition counter */
        ComM_LTranslateInhibitionStatus(Channel,COMM_PREVENTWAKEUP,Status);

        SchM_Exit_ComM_LimitationNoNest();
    }
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif  /*  (COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)  */
