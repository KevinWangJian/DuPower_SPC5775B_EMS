

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_SwitchIpduTxMode
 Syntax           : void Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode)
 Description      : The service Com_SwitchIpduTxMode sets the transmission mode of the I-PDU referenced by PduId to Mode.
 Parameter        : PduId,Mode
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_SwitchIpduTxMode(VAR(PduIdType, AUTOMATIC) PduId, VAR(boolean, AUTOMATIC) Mode)
{
    Com_TxIpduConstPtrType TxIPduConstPtr;
    Com_TxIpduRamPtrType TxIpduRamPtr;
    VAR(uint8, AUTOMATIC) LatestTransMode_u8;

    /* Start: Det */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_SwitchIpduTxMode, COM_E_UNINIT)

    COM_REPORT_ERROR((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_SwitchIpduTxMode, COM_E_PARAM)

    COM_REPORT_ERROR(((Mode!=COM_TRUE) &&(Mode!=COM_FALSE)), COMServiceId_SwitchIpduTxMode, COM_E_PARAM)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    PduId = COM_GET_TX_IPDU_ID(PduId);


    TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);


    /* If a change of the TMS causes a change of the transmission mode for one I-PDU, the timer for the cycle
    time of the periodic and the Mixed Tx Mode shall be restarted */

    /* if(TxIpduRamPtr->Com_TransMode.TxModeState != COM_NONE) */
    if((Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode))
        /*Check if requested mode is already active */
    {
        /* Update the Mode state with the Mode */
        /* TxIpduRamPtr->Com_TransMode.TxModeState = Mode */
        Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);
        /* Update the Com_LatestTransMode and the Timers */
        /*Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,TxIPduConstPtr->txIPduFields.TMSCalclation,Mode)*/
        Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);
        /* TxIpduRamPtr->Com_TransMode.LatestTransMode = TxIpduRamPtr->CurrentTxModePtr->Mode */
        Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);
        LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;

/* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
        /* Initialise MixedPhaseShift state, when IPdu tx mode is calculated in Com_IPduGroupStart() */
        /* TxIpduRamPtr->Com_TransMode.MixedPhaseShift = TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift */
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif /* #ifdef COM_MIXEDPHASESHIFT */
/* FC_VariationPoint_END */
        if (LatestTransMode_u8 != COM_TXMODE_NONE)
        {

            /* All unused flags are reset here */
            Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
            sendIpduFlag_u16.isEventTrig      =  COM_SET;
            /* Call Com_SendIpdu,for the Ipdu, indicating mode change */
            sendIpduFlag_u16.isModeChangd     =  COM_SET;
            /* For a MIXED Ipdu, as the signal transfer property information is not known.
             * It is assumed, for transmission from this APi,the signal transfer property is Pending */
            /* Time out monitoring cannot be performed for event part */

            Com_SendIpdu((PduIdType)PduId, sendIpduFlag_u16);
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

