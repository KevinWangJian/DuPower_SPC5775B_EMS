

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
 Function name    : ComM_Nm_BusSleepMode
 Syntax           : void ComM_Nm_BusSleepMode(NetworkHandleType Channel)
 Description      : Notification that the network management has entered Bus-Sleep Mode.
 Parameter        : Channel -> Channel Id
 Return value     : void
 ***************************************************************************************************/
FUNC(void,COMM_CODE) ComM_Nm_BusSleepMode
                                        (
                                        VAR(NetworkHandleType,AUTOMATIC) Channel
                                        )
{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    channelRamPtr_ps = &ComM_ChannelStruct[Channel];
    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);
    /* Local Variables Declaration */
    /*****************************************DET START************************************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* Check if ComM is initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_BUS_SLEEPMODE,COMM_E_NOT_INITED);
        return;
    }
    /* Check if the channel is present in the configured channels */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        /* Report DET with Invalid channel parameter*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_BUS_SLEEPMODE,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /*********************************************DET END************************************************/

    /* Check if the channel's Nm variant is FULL or PASSIVE */
    /* Bus sleep indication is processed only if the channel is in COMM_FULL_COMMUNICATION or COMM_SILENT_COMMUNICATION
     * mode.In other modes, it is ignored*/

    if ((channelConfigPtr_pcs->ComMNmVariant_e==FULL)||(channelConfigPtr_pcs->ComMNmVariant_e==PASSIVE))
    {
        SchM_Enter_ComM_ChannelNoNest();

        if((channelRamPtr_ps->ChannelMode_u8 == COMM_FULL_COMMUNICATION)|| (channelRamPtr_ps->ChannelMode_u8 == COMM_SILENT_COMMUNICATION))
        {
            channelRamPtr_ps -> NmBusSleepIndicationStatus_b = TRUE;
        }

        SchM_Exit_ComM_ChannelNoNest();
    }


}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

