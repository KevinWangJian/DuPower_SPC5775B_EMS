

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_TxIPduStop
 Syntax           : void Com_TxIPduStop(Com_IpduIdType   IpduId)
 Description      : Service to stop the ipdu
 Parameter        : IpduId -> Id of the ipdu
 Return value     : None
***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_TxIPduStop(VAR(Com_IpduIdType, AUTOMATIC) IpduId)
{
#ifdef COM_ERRORNOTIFICATION
    Com_TxIpduConstPtrType TxIPduConstPtr;
#endif
    Com_TxIpduRamPtrType TxIpduRamPtr;

#ifdef COM_ERRORNOTIFICATION


    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId);

#endif
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId);

#ifdef COM_ERRORNOTIFICATION
    /* All outstanding not confirmed transmitted signals/ signal groups shall
    immediately receive an error notification if configured */
    /*Check the variable TickTxTimeout_Flag, if it is STARTED,
    then call the error Notification and Set this variable to STOPPED*/
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
     * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
     * system behaviour. Hence suppressed. */
    /*if(TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag == COM_START) */
    if(((Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START) ||(TxIpduRamPtr->Com_n != 0))
            /* (TxIpduRamPtr->Com_TxFlags.TxConfirFlag == COM_RESET) */
            && (Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags) == COM_FALSE))
        /*Here TxIpduRamPtr->Com_n != 0 is checked for Direct-N/Mixed TM, whereas COM_START is for Periodic*/
    {

        if (TxIPduConstPtr->NotificationError_Cbk != NULL_PTR)
        {
            TxIPduConstPtr->NotificationError_Cbk();

        }
    }
#endif /* #ifdef COM_ERRORNOTIFICATION */
    /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_STOP */
    Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP); /*Disabling Tx deadline monitoring*/

                /* Update Com_TxModeState[] to NONE */
    /* TxIpduRamPtr->Com_TransMode.TxModeState = COM_NONE */
    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_FALSE);
    /*Com_LatestTransMode[i] = NONE;*/

    /*Reset all other Tx Global variables including Min Delays*/
    /* TxIpduRamPtr->Com_TxFlags.TxConfirFlag = COM_RESET */
    Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#ifdef COM_TxIPduTimeOut
    TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif /* #ifdef COM_TxIPduTimeOut */
    TxIpduRamPtr->Com_n = 0;
    /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
    Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
    TxIpduRamPtr->Com_MinDelayTick = 0;

    /* Reset the large data Tx Pdu flag, if the Ipdu group is stopped */
    Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

