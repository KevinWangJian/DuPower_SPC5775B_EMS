


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
FUNC (void,COMM_CODE) ComM_EcuM_PNCWakeUpIndication
                                            (
                                            VAR(PNCHandleType,AUTOMATIC) PNCid
                                            )
{
    #if (COMM_PNC_ENABLED != STD_OFF)
    /* Local variables declaration */

    #if(COMM_SYNCHRONOUS_WAKE_UP == STD_OFF)

    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
    uint8 numChannels;
    VAR(uint8,AUTOMATIC) loopCtr_u8;

    #endif

    /*****************************************DET START************************************************/
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* Check if ComM is initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_NOT_INITED);
        return;
    }
    /* Check if the channel is present in the configured channels */
    if (PNCid >= COMM_NO_OF_PNCS)
    {
        /* Report DET if the channel is not valid*/

        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /*********************************************DET END************************************************/

    /* If COMM_SYNCHRONOUS_WAKE_UP is enabled */
    #if (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

    /*  As synchronous wake up is enabled, all channels and all PNC's needs to be waken up*/
    /*  Wake up detected on a particular PNC should wake up all channels and PNC's */

    /* Check if PNC is enabled, done for Postbuild as PN can later be dis/enabled postbuild time */

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        ComM_LSyncWakeUpIndication();
    }

    #else  /* COMM_SYNCHRONOUS_WAKE_UP disabled */

    /* Set Wake up indication for the PNC on which wake up is indicated and its linked channels*/

    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PNCid]);
    numChannels = pncConfigPtr_pcs->NumChannels;

    pncRamPtr_ps = &ComM_PncRamStruct[PNCid];

    /* Check if PNC is enabled, done for Postbuild as PN can later be dis/enabled postbuild time */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        /* If PNC is in state NO_COMMUNICATION, set WakeUpStatus_b flag */
        SchM_Enter_ComM_PNCWakeUpNoNest();
        if(pncRamPtr_ps->PncState_e == PNC_NO_COMMUNICATION)
        {
            pncRamPtr_ps->WakeUpStatus_b = TRUE;
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();

        /* Lock required for consistent update of PassiveRequestState_u8 in API's and main function along with channel state */
        SchM_Enter_ComM_ChannelNoNest();
        for(loopCtr_u8 = 0; loopCtr_u8 < numChannels ;loopCtr_u8++)
        {
            uint8 ChannelId;

            ChannelId = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

            channelRamPtr_ps = &ComM_ChannelStruct[ChannelId];

            if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
            {
                COMM_SET_BIT((channelRamPtr_ps -> PassiveRequestState_u8),(0x01));
            }
        }
        SchM_Exit_ComM_ChannelNoNest();
    }

    #endif  /*  (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )  */

    #if ((COMM_DEV_ERROR_DETECT == STD_OFF) && (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF))
    (void)(PNCid);
    #endif

    #else   /* #if (COMM_PNC_ENABLED != STD_OFF) */

    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* This API shouldnt be called if PN is disabled. However, it is not put under feature switch as EcuM
     * expects this interface always independent of availability of PN
     * Hence report to DET */

    (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_ECUM_PNCWAKEUP_INDICATION,COMM_E_ERROR_IN_PROV_SERVICE);
    return;

    #endif  /* #if (COMM_DEV_ERROR_DETECT != STD_OFF) */

    #endif  /* #if (COMM_PNC_ENABLED != STD_OFF) */
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"



