


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
/* ComM_EcuM_RunModeIndication */
/*******************************************************************************
 * Function name    : ComM_CommunicationAllowed
 * Syntax           : void ComM_CommunicationAllowed( NetworkHandleType Channel, boolean Allowed )
 * Description      : EcuM or BswM shall indicate to ComM when communication is allowed.
 *                    If EcuM/Fixed is used: EcuM/Fixed.
 *                    If EcuM/Flex is used: BswM
 * Parameters       : Channel
 *                    Allowed -> TRUE: Communication is allowed
 *                               FALSE: Communication is not allowed
 * Return value     : void
 ******************************************************************************/
FUNC (void,COMM_CODE)ComM_CommunicationAllowed
                                                (
                                                        VAR(NetworkHandleType,AUTOMATIC) Channel,
                                                        VAR(boolean,AUTOMATIC) Allowed
                                                )
{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    /* Local variable initialization */
    channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    /* DET check for communication manager initialization */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_NOT_INITED);
        return;
    }

    /* Check if the channel is present in the configured channels */
    /* Raise DET if the channel is not valid */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        /* Report DET if the channel is not valid*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_COMMUNICATION_ALLOWED,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */

    /* Update the status of Communication Allowed for the channel */

    channelRamPtr_ps->CommunicationAllowed_b = Allowed;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

