


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


#if (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/*******************************************************************************
 * Function name    : ComM_LimitECUToNoComMode
 * Syntax           : Std_ReturnType ComM_LimitChannelToNoComMode( NetworkHandleType Channel, ComM_StateType* State )
 * Description      : API to enable or disable limit to no com for the ECU.
 * Parameters       : Channel-> The Network Channel for the requested state of ComM state machine.
 *                    Status-> Status of limit to no com
 * Return value     : E_OK: Successfully changed inhibition status for the channel
 *                    E_NOT_OK: Changed of inhibition status for the channel failed
 *                    COMM_E_UNINIT: ComM not initialized
 ******************************************************************************/

FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode
                                        (
                                        VAR(boolean, COMM_VAR) Status
                                        )
{
    /* Local variable declaration */
    uint8 channelId_u8;
    uint8 userId_u8;
    #if (COMM_PNC_ENABLED != STD_OFF)
    uint8 pncId_u8;
    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    #endif/*  (COMM_PNC_ENABLED != STD_OFF)  */

    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

    /*  Rename globalRamPtr_ps to globalRamPtr_ps  */
    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
    /* Local variable initialization */
    /************************************DET CHECK STARTS HERE*********************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)

    /* Check for ComM Initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_LIMIT_CHNLTO_NOCOMMODE_APIID,COMM_E_NOT_INITED);
        return E_NOT_INITIALIZED;
    }
    #endif  /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */

    /************************************DET CHECK ENDS HERE**********************************/

    /* Proceed only if the request has changed from previous request */

    globalRamPtr_ps = &ComM_GlobalStruct;

    if((globalRamPtr_ps->ComM_LimitECUToNoCom_b) != Status)
    {
        /* Update the global limit ecu to no com status */
        globalRamPtr_ps->ComM_LimitECUToNoCom_b = Status;

        SchM_Enter_ComM_LimitationNoNest();

        /* If limit ECU to no com is requested */
        if(Status != FALSE)
        {
            /* Set limit to no com for all channels */
            /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                               * Hence it is an incorrect warning reported by Misra */
            for(channelId_u8 = C_ZERO, channelRamPtr_ps = &ComM_ChannelStruct[C_ZERO]; channelId_u8 < COMM_NO_OF_CHANNELS; ++channelId_u8,++channelRamPtr_ps)
            {
                COMM_SET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8));
            }

            /* Reevaluate limit to no com counter for all PNC's and Users */
            /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                               * Hence it is an incorrect warning reported by Misra */
            for(userId_u8 = C_ZERO, userRamPtr_ps = &ComM_UserStruct[C_ZERO]; userId_u8 < COMM_NO_OF_USERS; ++userId_u8,++userRamPtr_ps)
            {
                /* counter value is set as '1' here, as this is the master feature and limit to no com is ignored
                 * as long as this is enabled.The value of the counter is not valid here. It is sufficient if it is a non zero value*/
                userRamPtr_ps->LimitToNoComCtr_u16 = C_ONE;
            }

            #if(COMM_PNC_ENABLED != STD_OFF)
            /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
            if(COMM_GET_FEATURE_PNC_ENABLED)
            {
                /* If PNC is enabled, reevaluate limit to no com counter for all PNC's as the number of channels of PNC*/
                /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                                   * Hence it is an incorrect warning reported by Misra */
                for(pncId_u8 = C_ZERO, pncRamPtr_ps = &ComM_PncRamStruct[C_ZERO] ; pncId_u8 < COMM_NO_OF_PNCS; ++pncId_u8,++pncRamPtr_ps)
                {
                    /* counter value is set as '1' here, as this is the master feature and limit to no com is ignored
                     * as long as this is enabled.The value of the counter is not valid here. It is sufficient if it is a non zero value*/
                    pncRamPtr_ps->LimitToNoComCtr_u16 = C_ONE;
                }
            }
            #endif  /*  (COMM_PNC_ENABLED != STD_OFF)  */
        }
        /* If limit ECU to no com is released */
        else
        {
            /* Clear limit to no com for all channels */
            /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                   * Hence it is an incorrect warning reported by Misra */
            for(channelId_u8 = C_ZERO, channelRamPtr_ps = &ComM_ChannelStruct[channelId_u8]; channelId_u8 < COMM_NO_OF_CHANNELS; channelId_u8++,channelRamPtr_ps++)
            {
                COMM_CLR_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8));
            }

            /* Reset limit to no com counter for all Users */
            /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                   * Hence it is an incorrect warning reported by Misra */
            for(userId_u8 = C_ZERO, userRamPtr_ps = &ComM_UserStruct[C_ZERO]; userId_u8 < COMM_NO_OF_USERS; ++userId_u8, ++userRamPtr_ps )
            {
                userRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
            }

            #if(COMM_PNC_ENABLED != STD_OFF)
            /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
            if(COMM_GET_FEATURE_PNC_ENABLED)
            {
                /* If PNC is enabled, reset limit to no com counter for all PNC's */
                /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
                       * Hence it is an incorrect warning reported by Misra */
                for(pncId_u8 = C_ZERO, pncRamPtr_ps = &ComM_PncRamStruct[C_ZERO]; pncId_u8 < COMM_NO_OF_PNCS; ++pncId_u8, ++pncRamPtr_ps)
                {
                    pncRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
                }
            }
            #endif  /*  (COMM_PNC_ENABLED != STD_OFF)  */

        }

        SchM_Exit_ComM_LimitationNoNest();
    }
    return E_OK;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif  /*  (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */

