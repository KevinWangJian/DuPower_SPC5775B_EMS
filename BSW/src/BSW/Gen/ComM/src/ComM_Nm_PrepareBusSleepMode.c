

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


/***************************************************************************************************
 Function name    : ComM_Nm_PrepareBusSleepMode
 Syntax           : void ComM_Nm_PrepareBusSleepMode(NetworkHandleType Channel)
 Description      : Notification that the network management has entered Prepare Bus-Sleep Mode.
 Parameter        : Channel -> Id of the channel
 Return value     : void
 ***************************************************************************************************/
FUNC(void,COMM_CODE) ComM_Nm_PrepareBusSleepMode
                                            (
                                            VAR(NetworkHandleType,AUTOMATIC) Channel
                                            )
{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
    /* Local variable initialization */
    channelRamPtr_ps = &ComM_ChannelStruct[Channel];
    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);
    /*****************************************DET START************************************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* DET check for communication manager initialization */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_PREPARE_BUSSLEEPMODE,COMM_E_NOT_INITED);
        return;
    }
    /* Check if the channel is present in the configured channels */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        /* Report DET with Invalid channel parameter*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_PREPARE_BUSSLEEPMODE,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /*********************************************DET END************************************************/

    /* Process prepare bus sleep indication only if Channel's NmVariant is FULL or PASSIVE */
    /* Bus sleep indication is considered only in COMM_FULL_COM_READY_SLEEP state */

    if ((channelConfigPtr_pcs->ComMNmVariant_e==PASSIVE)||(channelConfigPtr_pcs->ComMNmVariant_e==FULL))
    {
        SchM_Enter_ComM_ChannelNoNest();

        if(channelRamPtr_ps->ChannelState_e == COMM_FULL_COM_READY_SLEEP)
        {
            channelRamPtr_ps -> NmPrepareBusSleepIndicationStatus_b = TRUE;
        }

        SchM_Exit_ComM_ChannelNoNest();
    }

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

