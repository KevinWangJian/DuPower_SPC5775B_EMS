

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
 Function name    : ComM_Nm_RestartIndication
 Syntax           : void ComM_Nm_RestartIndication(NetworkHandleType Channel)
 Description      : Restart indication service
 Parameter        : Channel -> Id of the channel
 Return value     : void
 ***************************************************************************************************/
FUNC(void,COMM_CODE) ComM_Nm_RestartIndication (VAR(NetworkHandleType,AUTOMATIC) Channel)
{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
    /* Local variable initialization */
    channelRamPtr_ps = &ComM_ChannelStruct[Channel];
    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);

    /*****************************************DET START************************************************/
    /* Check if ComM is initialized */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_RESTARTINDICATION,COMM_E_NOT_INITED);
        return;
    }
    /* Check if the channel is present in the configured channels */
    if (Channel >= COMM_NO_OF_CHANNELS)
    {
        /* Report DET with Invalid channel parameter*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_NM_RESTARTINDICATION,COMM_E_WRONG_PARAMETERS);\
        return;
    }
    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /*********************************************DET END************************************************/

    /* Check if the Channel's NmVariant is FULL or PASSIVE */
    /* Restart indication is only processed in No communication mode.*/
    /* In other modes, it is ignored*/

    if ((channelConfigPtr_pcs->ComMNmVariant_e==FULL)||(channelConfigPtr_pcs->ComMNmVariant_e==PASSIVE))
    {
        SchM_Enter_ComM_ChannelNoNest();

        if( channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION )
        {
            COMM_SET_BIT((channelRamPtr_ps->PassiveRequestState_u8),(0x02));
        }

        SchM_Exit_ComM_ChannelNoNest();

    }

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

