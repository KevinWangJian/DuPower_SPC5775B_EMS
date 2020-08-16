


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
 * Function name    : ComM_DeInit
 * Syntax           : void ComM_DeInit(void)
 * Description      : De-initializes the AUTOSAR Communication Manager.
 * Parameters       : void
 * Return value     : void
 ******************************************************************************/
FUNC(void,COMM_CODE) ComM_DeInit(void)
{
    /* Local Variables Declaration */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    VAR(uint8 ,AUTOMATIC)  ChannelIndexCtr;
    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
    globalRamPtr_ps = &ComM_GlobalStruct;
    /* Local variable initialization */
    /* DET check for communication manger initialization */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* check if communication manager in initialized. Else report DET */
    if (/* check if communication manager in initialized.
        Else report DET */
    globalRamPtr_ps->ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialised status*/
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DEINIT_APIID,COMM_E_NOT_INITED);
        return;
    }
    else
    {
        /* do nothing */
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */

    /* Set the init status as Uninit */
    /* De-initializes (terminates) the AUTOSAR Communication Manager*/
    globalRamPtr_ps->ComM_InitStatus = COMM_UNINIT;
    for (ChannelIndexCtr = C_ZERO ; ChannelIndexCtr < COMM_NO_OF_CHANNELS ; ChannelIndexCtr++)
    {
        /* loop thro all the ComM channel,and if any of the channel is found to
        be not in NO_COMMUNICATION state then deinit call is ignored */
        /* Check if the current channel mode of all the channel is No communication .
        If yes change the INIT status as Uninit */
        if (ComM_ChannelStruct[ChannelIndexCtr].ChannelState_e != COMM_NO_COM_NO_PENDING_REQUEST)
        {
            /*  Initialize the status if any one of the channel is not in No communication mode and break it */
            globalRamPtr_ps->ComM_InitStatus = COMM_INIT;
            break;
        }
    }
    return;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

