

/********************************************************************************************************************/
/* Preprocessor includes                                                                                            */
/********************************************************************************************************************/
#include "Com_Priv.h"
/********************************************************************************************************************/
/* Global functions (declared in header files )                                                                     */
/********************************************************************************************************************/
/*********************************************************************************************************************
 Function name    : Com_TriggerIPDUSendWithMetaData
 Syntax           : Std_ReturnType Com_TriggerIPDUSendWithMetaData( PduIdType PduId, uint8* MetaData )
 Description      : By a call to this API, the AUTOSAR COM module updates
                    its internal metadata for the I-PDU with the given ID by copying the metadata
                    from the given position and with respect to the globally configured metadata
                    length of the I-PDU. Then the I-PDU is triggered for transmission.
 Parameters       : PduId   -> The I-PDU-ID of the I-PDU that shall be triggered for sending
                    Metdata -> A pointer to the metadata for the triggered send-request
 Return value     : Std_ReturnType
                     E_OK     -  I-PDU was triggered for transmission
                     E_NOT_OK -  I-PDU is stopped, the transmission could not be triggered
 ********************************************************************************************************************/
#if defined COM_METADATA_SUPPORT
# define COM_START_SEC_CODE
# include "Com_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: A pointer parameter(MetaData) in a function prototype should be declared as pointer to
 * const if the pointer is not used to modify the addressed object. But AUTOSAR SWS specification signature is as below.
 * Hence suppressed */
FUNC( Std_ReturnType, COM_CODE ) Com_TriggerIPDUSendWithMetaData( VAR( PduIdType, AUTOMATIC ) PduId,
                                                     P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) MetaData )
{
    VAR( Std_ReturnType, AUTOMATIC ) returnVal_uo;  /* Return value */

    /* Start: DET Check */
    /* Check if the module is initialized */
    COM_REPORT_ERROR4( ( Com_Uninit_Flag == COM_UNINIT ), COMServiceId_TriggerIPDUSendWithMetaData, COM_E_UNINIT )
    /* Check if the given IPdu Id is valid */
    COM_REPORT_ERROR4( ( PduId >= COM_GET_NUM_TX_IPDU ),  COMServiceId_TriggerIPDUSendWithMetaData, COM_E_PARAM )
    /* End: DET Check   */

    returnVal_uo = ( Std_ReturnType )E_NOT_OK;

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */
    PduId = COM_GET_TX_IPDU_ID(PduId);

    /* Check if IPdu Group containing the given IPdu is started */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if ( COM_CheckTxIPduStatus( PduId ) )
    {
        Com_TxIpduConstPtrType TxIPduConstPtr;      /* Local pointer to Tx Ipdu static configuration   */

        TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA( PduId );

        /* Check if the given IPdu supports MetaData */
        if ( Com_GetValue( TXIPDU, _ISMETADATASUPPORTED, TxIPduConstPtr->txIPduFields ) )
        {
            Com_TxIpduRamPtrType TxIpduRamPtr;      /* Local pointer to the Tx Ipdu status structure   */

            TxIpduRamPtr = &COM_GET_TXPDURAM_S( PduId );

            /* Check whether the Large Data IPdu flag has been reset */
            if ( COM_TRUE != Com_GetRamValue( TXIPDU, _LARGEDATAINPROG, TxIpduRamPtr->Com_TxFlags ) )
            {
                P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) MetaDataConstPtr;
                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                sendIpduFlag_u16.isEventTrig      = COM_SET;
                sendIpduFlag_u16.isTriggerIpduSendWithMetadata = COM_SET;

#  ifdef COM_TxIPduTimeOut
                /**
                 * For a MIXED IPdu, as the signal transfer property information is not known.
                 * It is assumed that, for transmission from this API, the signal transfer property is PENDING
                 * Time out monitoring cannot be performed for the event part
                 * The timeout handling should happen as usual
                 */
                if ( ( uint16 )0 != TxIPduConstPtr->Timeout_Fact )
                {
                    sendIpduFlag_u16.isTimeoutReq  = COM_SET;
                }
#  endif /* COM_TxIPduTimeOut */

                if ( NULL_PTR == MetaData )
                {
                    /**
                     * If no explicit meta data is given for a send request, the AUTOSAR COM module uses configured
                     * ComMetaDataDefault value for sending.
                     */
                    MetaDataConstPtr = ( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )
                                       ( &TxIPduConstPtr->MetaDataPtr->MetaDataDefaultValue[0] );
                }
                else
                {
                    /* Otherwise, Copy the MetaData provided by application */
                    MetaDataConstPtr = ( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )( MetaData );
                }

                /* Lock the given TxIPdu buffer from updation in other API's */
                SchM_Enter_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );

                /* Copy the given MetaData into TxIPdu Buffer */
                Com_ByteCopy(
                        ( P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) )( TxIPduConstPtr->BuffPtr + TxIPduConstPtr->Size ),
                     ( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )( MetaDataConstPtr ),
                                                                    ( TxIPduConstPtr->MetaDataPtr->MetaDataLength ) );

                /* Release-Lock for the given TxIPdu buffer updation in other API's */
                SchM_Exit_Com_TxIpduProtArea( TRIGGERIPDUSENDWITHMETADATA );

                /* Send the given TxIPdu to the lower layer */
                Com_SendIpdu( PduId, sendIpduFlag_u16 );

                returnVal_uo = ( Std_ReturnType )E_OK;
            }
        }
    }
    return returnVal_uo;
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"
#endif /* COM_METADATA_SUPPORT */

