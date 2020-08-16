


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
 * Function name    : ComM_EcuM_WakeUpIndication
 * Syntax           : void ComM_EcuM_WakeUpIndication( NetworkHandleType Channel )
 * Description      : Notification of a wake up on the corresponding channel.
 * Parameters       : Channel
 * Return value     : void
 ******************************************************************************/
FUNC (void,COMM_CODE) ComM_EcuM_WakeUpIndication
                                            (
                                                VAR(NetworkHandleType,AUTOMATIC) Channel
                                            )
{

    /* Local variables declaration */
    #if (COMM_SYNCHRONOUS_WAKE_UP == STD_OFF )
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    #endif

    /*****************************************DET START************************************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* Check if ComM is initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_WAKEUP_INDICATION,COMM_E_NOT_INITED);
        return;
    }
    /* Check if the channel is present in the configured channels */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        /* Report DET if the channel is not valid*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_WAKEUP_INDICATION,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /*********************************************DET END************************************************/

    /* If COMM_SYNCHRONOUS_WAKE_UP is enabled,
    change state of all channels to Wait For RunMode State */
    #if (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

    /*  As synchronous wake up is enabled, all channels needs to be waken up*/
    /*  Wake up detected on a particular channel should wake up all channels */
    ComM_LSyncWakeUpIndication();

    #else  /* COMM_SYNCHRONOUS_WAKE_UP disabled */

    /* Wake up only the requested channel */
    channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    SchM_Enter_ComM_ChannelNoNest();
    /* Wake up indication is processed only in COMM_NO_COMMUNICATION mode, in other modes it is ignored */
    if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
    {

        COMM_SET_BIT((channelRamPtr_ps ->PassiveRequestState_u8 ),(0x01));

    }
    SchM_Exit_ComM_ChannelNoNest();

    #endif  /*  (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )  */

    (void)(Channel);

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

