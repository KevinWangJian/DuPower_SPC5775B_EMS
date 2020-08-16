

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/


/***************************************************************************************************
 Function name    : Com_DeInit
 Syntax           : void Com_DeInit(void)
 Description      : Service for COM DeInitialization
 Parameter        : void
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_DeInit(void)
{

    VAR(uint16_least, AUTOMATIC) Idx_ui;
    Com_TxIpduRamPtrType TxIpduRamPtr;
    Com_RxIpduRamPtrType RxIPduRamPtr;
    /*Interrupt is locked due to the updation of Com_Uninit_Flag, Ipdu Group Status & IPdu Group DM Status
      In most of the API's, if Ipdu group is stopped, no further processing of data is performed.*/

    /* Check if the module is already Initialised */
    if(Com_Uninit_Flag == COM_INIT)
    {
        /* Reset the UNINIT flag */
        Com_Uninit_Flag = COM_UNINIT;

        for (Idx_ui=0;Idx_ui < COM_NUM_ARR_IPDUGRPVECT ;Idx_ui++ )
        {
            Com_IpduGrpVector[Idx_ui] = (uint8)0;  /* reset the Ipdu Group vector array */
            Com_IpduGrpVector_DM[Idx_ui] = (uint8)0;    /* reset the Dealine Monitoring */
        }

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);
        /* Start: Reset all Tx Flags */
        for(Idx_ui=0 ; Idx_ui < COM_GET_NUM_TX_IPDU;Idx_ui++)
        {
            COM_GET_IPDUCOUNTER_S(Idx_ui + COM_GET_NUM_RX_IPDU) = 0;
            /*Disabling Tx deadline monitoring*/
            /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_STOP */
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);

            /* Update Com_TxModeState[] to NONE */
            /* TxIpduRamPtr->Com_TransMode.TxModeState = COM_NONE */
            Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,COM_FALSE);

            /*Reset all other Tx Global variables including Min Delays*/
            /* TxIpduRamPtr->Com_TxFlags.TxConfirFlag = COM_RESET */
            Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

#ifdef COM_TxIPduTimeOut
            TxIpduRamPtr->Com_TickTxTimeout = 0;
#endif /* #ifdef COM_TxIPduTimeOut */
            TxIpduRamPtr->Com_n = 0;
            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
            TxIpduRamPtr->Com_MinDelayTick = 0; /*Minimum Delay Tick for the Tx IPDU's */
            TxIpduRamPtr++;

        }
        /* End: Reset all Tx Flags */

        /* Start: Reset all Rx Flags */
        RxIPduRamPtr = &COM_GET_RXPDURAM_S(0);
        for(Idx_ui=0 ; Idx_ui < COM_GET_NUM_RX_IPDU;Idx_ui++)
        {
            /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_RESET */
            Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags,COM_FALSE);   /* reset of Rx ipdu indication flag */
            RxIPduRamPtr++;
            COM_GET_IPDUCOUNTER_S(Idx_ui) = 0;        /* reset of the Rx ipdu status */
            COM_GET_IPDUCOUNTER_DM(Idx_ui) = 0;        /* reset of the Rx dealine monitoring */
        }

        /* End: Reset all Rx Flags */
    }



}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

