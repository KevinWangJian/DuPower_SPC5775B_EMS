

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "Com_Priv.h"

/*
**********************************************************************************************************************
* Global function Definitions (declared in header files)
**********************************************************************************************************************
*/

/* Com_ReceiveSignalGroupArray() API shall only be available when the configuration switch
 *  ComEnableSignalGroupArrayApi is enabled */
#if defined ( COM_RX_SIGNALGROUP_ARRAY )
/*
**********************************************************************************************************************
* Function name    : Com_ReceiveSignalGroupArray
* Syntax           : uint8
*                    Com_ReceiveSignalGroupArray( Com_SignalGroupIdType SignalGroupId, uint8* SignalGroupArrayPtr )
* Description      : The service Com_ReceiveSignalGroupArray copies the received signal group array representation
*                    from the PDU to the location designated by SignalGroupArrayPtr.
* Parameters   IN  : SignalGroupId - Id of signal group to be received.
               OUT : SignalGroupArrayPtr - reference to the location where the
                                           received signal group array shall be stored
* Sync/Async       : Synchronous
* Reentrancy       : Non Reentrant for the same signal group. Reentrant for different signal groups.
* Return value     : E_OK                      : service has been accepted
*                    COM_SERVICE_NOT_AVAILABLE : corresponding I-PDU group was stopped
*                                                (or service failed due to development error)
**********************************************************************************************************************
*/
# define COM_START_SEC_CODE
# include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray( Com_SignalGroupIdType SignalGroupId, uint8 * SignalGroupArrayPtr )
{
    Com_RxSigGrpConstPtrType      RxSigGrpConstPtr; /* Local pointer to Rx SignalGroup static configuration */
    uint8                         returnValue_u8;

    /* Start : Perform Det check and Report to Det only if COM_CONFIGURATION_USE_DET generated with STD_ON */
    /* If service is called when Com Module is in Un-Initialized state */
    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT),             COMServiceId_ReceiveSignalGroupArray, COM_E_UNINIT )
    /* If service is called with invalid SignalGroupId  */
    COM_REPORT_ERROR1((SignalGroupId >= COM_GET_NUM_RX_SIGNALGRP), COMServiceId_ReceiveSignalGroupArray, COM_E_PARAM  )
    /* If service is called with NULL_PTR in SignalGroupArrayPtr parameter */
    COM_REPORT_ERROR1((SignalGroupArrayPtr == NULL_PTR),     COMServiceId_ReceiveSignalGroupArray, COM_E_PARAM_POINTER)
    /* End   : Det */

    returnValue_u8   = E_OK;

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */
    SignalGroupId    = COM_GET_RXSIGNALGRP_ID( SignalGroupId );

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA( SignalGroupId );

    /* Check if ArrayAccess is enabled for this Rx-Signal Group */
    if ( Com_GetValue(RXSIGGRP,_ARRAYACCESS,RxSigGrpConstPtr->rxSignalGrpFields) )
    {
        Com_RxSigGrpArrayConstPtrType        RxSigGrpArrayConstPtr; /* Pointer to Rx SignalGroupArray static config */
        P2VAR(uint8,AUTOMATIC,COM_APPL_DATA) RxSigGrpArrayBufRamPtr;

        RxSigGrpArrayConstPtr  = COM_GET_RXSIGGRP_ARRAY_CONSTDATA( RxSigGrpConstPtr->SigGrpArray_Index );

        RxSigGrpArrayBufRamPtr = &COM_GET_RXSIGGRP_ARRAY_BUFF( RxSigGrpArrayConstPtr->RxSigGrpBuf_Index );

        /**
         * A call to Com_ReceiveSignalGroupArray() on a Rx-SignalGroup that belongs to a stopped I-PDU shall result in
         * the return code COM_SERVICE_NOT_AVAILABLE.
         * But nevertheless copy the last known data (or the init value) of the I-PDU to the SignalGroupArrayPtr
         */
        /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
         * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
         * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
         * Hence the warning is suppressed. */
        if ( !COM_CheckRxIPduStatus( RxSigGrpConstPtr->IpduRef ) )
        {

            returnValue_u8 = COM_SERVICE_NOT_AVAILABLE;
        }

        SchM_Enter_Com_RxSigGrpArrayBuff();

        /**
         * Copy RxSignalGroup Data(uint8[n]) from IPdu Buffer into *SignalGroupArrayPtr
         * Design: Here in Rx-SignalGroup, LastByte is generated as (LastByteNo + 1), so the Length is derived as just
         *         ( LastByte - FirstByte ) instead of ( LastByte - FirstByte + 1 )
         */
        Com_ByteCopy(   ( P2VAR(uint8,AUTOMATIC,COM_APPL_DATA) )( SignalGroupArrayPtr    ),
                      ( P2CONST(uint8,AUTOMATIC,COM_APPL_DATA) )( RxSigGrpArrayBufRamPtr ),
                                                      ( uint32 )( RxSigGrpConstPtr->lastByte_u8 -
                                                                  RxSigGrpArrayConstPtr->FirstByteNo ) );

        SchM_Exit_Com_RxSigGrpArrayBuff();
    }
    else
    {
        returnValue_u8 = COM_SERVICE_NOT_AVAILABLE;
    }

    return returnValue_u8;
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

#endif /* #if defined ( COM_RX_SIGNALGROUP_ARRAY ) */
