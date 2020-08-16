

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "Det.h"

#include "SoAd_Prv.h"
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Prototype for Static functions: Start
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if ( SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF )
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_SetIfRgTransmitReq( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo );
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TriggerIfRgTransmit( P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRRouteDest_cpst );

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_IfRoutingGroupTransmitDetChk( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo );
#endif /* ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#endif /* ( SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF ) */

/**
 **********************************************************************************************************************
 * \Function Name : SoAd_IfRoutingGroupTransmit()
 *
 * \function description
 * This API Triggers the transmission of all If-TxPDUs identified by the parameter id after requesting
 * the data from the related upper layer.
.
 *
 * Parameters (in) :
 * \param   SoAd_RoutingGroupIdType
 * \arg     id - This parameter contains the routing group identifier indirectly specifying PDUs to be transmitted
 *                          and thereby specifying the socket to be used for transmission of the data.
 *
 * Parameters (inout): None
 *
 * Parameters (out):   None
 *
 * Return Parameter :
 * \return   Std_ReturnType
 * \retval   E_OK             - The request was successful
 *           E_NOT_OK         - The request was not successful,
 *
 *
 **********************************************************************************************************************
 */
/* Upper shall ask for below function, Then SoAd shall store the request across each PDuRouteDest which are linked with this routing
 * group Id, then in next SoAd_MainFunction(), UL_TriggerTransmit is called for all the PduRouteDests which are already stored */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_IfRoutingGroupTransmit( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  id )
{
#if ( SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF )

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8           = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_IfRoutingGroupTransmitDetChk(id);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        lFunctionRetVal_u8 = SoAd_SetIfRgTransmitReq(id);

    }/*End of If condition: Det Check */

    return(lFunctionRetVal_u8);

#else
    (void)id;
    return(E_NOT_OK);
#endif /* SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF */

}

#if ( SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF )
/**
 **************************************************************************************************************************************
 * \Function Name : SoAd_SetIfRgTransmitReq()
 *
 * \Function description
 * This function shall set the flag and it will be used in SoAdMainFunction to trgger the transmission req.
 *
 * Parameters (in):
 * \param   SoAd_RoutingGroupIdType
 * \arg     RgId_uo - This parameter contains the routing group identifier indirectly specifying PDUs to be transmitted
 *                          and thereby specifying the socket to be used for transmission of the data.
 *
 * Parameters (inout): None
 *
 * Parameters (out):    None
 *
 * \return  Std_ReturnType
 * \retval   E_OK               - The request was successful
 *           E_NOT_OK           - The request was not successful
 *
 ***************************************************************************************************************************************
 */
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_SetIfRgTransmitReq( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo )
{
    /* Pointer to hold the Pdu route destination structure*/
    P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)     lPduRouteDest_cpst;

    /* Local pointer to store the Tx pdu array one by one */
    P2CONST(SoAd_TxPduConfigType_tst, AUTOMATIC, AUTOMATIC) lSoAdTxPduConfig_cpst;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* variable to store the return value of internal function call */
    VAR(Std_ReturnType, AUTOMATIC)                          lRetVal_u8;

    /* Variable to hold the number of PduRouteDests configured for this PduRoute*/
    VAR(PduIdType, AUTOMATIC)                               lNumberofPduRouteDests_uo;

    /* Variable to hold the index of PduRouteDests configured for this PduRoute*/
    VAR(PduIdType, AUTOMATIC)                               lIdxOfPduRouteDest_uo;

    /* Loop through for NumofTxRoutingGroups Mapping to PduRouteDests */
    VAR( SoAd_RoutingGroupIdType, AUTOMATIC )               lIdxOfRoutingGroup_uo;

    /* Variable to hold the index of PduRoute configured */
    VAR(PduIdType, AUTOMATIC)                               lTxPduId_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8           = E_NOT_OK;

    /* Initialize the local variables which are declared above */
    /* Loop through all the Tx PDU route Group */
    for(lTxPduId_uo = 0; lTxPduId_uo < SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo; lTxPduId_uo++)
    {
        /* Get the Local pointer for SoAd_TxPduConfig_cpst for locall access */
        lSoAdTxPduConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lTxPduId_uo]);

        /* Condition check: the UL type is PDU-IF and the SoAdIfTriggerTransmit of the UL is set to TRUE
         * If both are TRUE, Get the number of PduRouteDests configured with this PduRoute, else 0 */
        lNumberofPduRouteDests_uo = ( ( SOAD_IF == lSoAdTxPduConfig_cpst->txUpperLayerType_en ) &&
                                      ( 0 < lSoAdTxPduConfig_cpst->idxTriggerTransmitCallback_u8 ) ) ? \
                                              lSoAdTxPduConfig_cpst->PduRouteDestNum_uo : 0U;

        /* Loop through all the PDU route Group dests */
        for(lIdxOfPduRouteDest_uo = 0; lIdxOfPduRouteDest_uo <  lNumberofPduRouteDests_uo; lIdxOfPduRouteDest_uo++)
        {
            /* Extract pointer to element of Pdu route destination structure one by one */
            lPduRouteDest_cpst = &( lSoAdTxPduConfig_cpst->PduRouteDestConf_cpst [lIdxOfPduRouteDest_uo] );

            /* Loop through for all routing groups configured for this PduRouteDest */
            for( lIdxOfRoutingGroup_uo = 0; lIdxOfRoutingGroup_uo < lPduRouteDest_cpst->numOfTxRoutingGroups_uo; lIdxOfRoutingGroup_uo++ )
            {
                /* Condition Check:
                 * 1. the Routing group id given by the upper layer is matches with configured Id's.
                 * 2. Trigger Transmit callback is registered.
                 */
                if( ( RgId_uo == lPduRouteDest_cpst->txRoutingGroupConf_cpuo[lIdxOfRoutingGroup_uo] )  && \
                    ( NULL_PTR != SoAd_CurrConfig_cpst->SoAd_IfTriggerTransmitCallbacks_cpst \
                            [SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lTxPduId_uo].idxTriggerTransmitCallback_u8].TriggerTransmit_pfn ))
                {
                    /* Call the below function to set the triggerTransmissionInfo_puo member if SoConId match is found */
                    lRetVal_u8 = SoAd_TriggerIfRgTransmit(lPduRouteDest_cpst);

                    /* If lRetVal_u8 is E_OK, then only update the lFunctionRetVal_u8, since if any one of pdu routes
                     * dests or any one of the socket connections triggerTransmissionInfo_puo->triggerTransmitRequest_u8 is set to STD_ON,
                     * SoAd_IfSpecificRoutingGroupTransmit shall return E_OK. Default valud of lFunctionRetVal_u8 is E_NOT_OK.
                     */
                    lFunctionRetVal_u8 = ( E_OK == lRetVal_u8 ) ? E_OK : lFunctionRetVal_u8;

                    /* same routing group reference cannot be configured in single PduRouteDest */
                    break;
                }
            }/* End of Routing Group for loop */
        }/* End of PduRoute Dest for loop */
    } /* End of TxPdu for loop */

    return lFunctionRetVal_u8;
}
/**
 **************************************************************************************************************************************
 * \Function Name : SoAd_TriggerIfSpecificRgTransmit()
 *
 * \Function description
 * This function shall call the update the triggerTransmissionInfo_puo structure for given pduRouteDest if SoConId match found.
 *
 * Parameters (in):
 * \param   PduRouteDestType_tst *
 * \arg     PduRRouteDest_cpst  - Pointer to a PduRouteDest structure
 *
 * Parameters (inout): None
 *
 * Parameters (out):    None
 *
 * \return  Std_ReturnType
 * \retval   E_OK               - The request was successful
 *           E_NOT_OK           - The request was not successful
 *
 ***************************************************************************************************************************************
 */
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TriggerIfRgTransmit( P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRRouteDest_cpst )
{
    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
    /* Index for looping across static sockets*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxSocketForLoop_uo ;

    /* variable to store index of the static socket connection one by one for the group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lStaticSocketId_uo ;
#endif /* SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF */

    /* Variable to hold the index of the dynamic socket connection table*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
    /* if Socket reference is linked to socket connection group */
    if( SOAD_SOCKET_BUNDLE_REFERENCE == PduRRouteDest_cpst->identifyTxSocketConnOrGroupRef_b )
    {
        /* fetch the start socket id from Group table and loop through for max socket count */
        lStaticSocketId_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRRouteDest_cpst->txStaticSocketOrGroupIdx_uo].startSoConIdx_uo;

        /* loop through all the sockets connection through the socket connection group for the processing */
        for( lIdxSocketForLoop_uo = 0 ; \
                        lIdxSocketForLoop_uo < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRRouteDest_cpst->txStaticSocketOrGroupIdx_uo].maxSoConChannel_uo; \
                                lIdxSocketForLoop_uo++ )
        {
            /* Get "index of the dynamic socket table" from static socket table */
            lIdxDynSocket_uo = ( *SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lStaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo );

            /* Condition checks:
             * 1. Check Dynamic socket index is valid.
             * 2. Check for socket connection is ONLINE or
             * 3. Check SoAd_OpenSoCon is triggered by UL and SoAd_MainFunction was triggered or
             * 4. Check atleast SoAd_OpenSoCon is triggered by UL
             */
            /* Check for the elements, whether a routing group is referenced to this PduRouteDest */
            if ( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo ) && \
                 ( ( SOAD_SOCON_ACTIVE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en ) || \
                   ( SOAD_EVENT_ONLINEREQ == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en ) || \
                   ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConCloseReqCnt_u16 < SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConOpenReqCnt_u16 ) ) )
            {

                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00662] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** At SoAd_IfRoutingGroupTransmit() SoAd shall store a trigger transmit request for each SoAdPduRouteDest   ***/
                /*** that contains a reference to the routing group identified by the parameter id for transmission in        ***/
                /*** the SoAd_MainFunction()                                                                                  ***/
                /****************************************************************************************************************/

                /* Store the triggerTransmitRequest_u8 of the related PduRouteDestination with STD_ON */
                PduRRouteDest_cpst->triggerTransmissionInfo_puo->triggerTransmitRequest_u8 = STD_ON;

                /* Set the lFunctionRetVal_u8 to E_OK*/
                lFunctionRetVal_u8 = E_OK ;
            }

            /* increment the lStaticSocketId_uo by 1 to loop the next socket id */
            lStaticSocketId_uo++;
        }

    }
    /* if Socket reference is linked to socket connection */
    else
#endif /* SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF */
    {

        /* Get "index of the dynamic socket table" from static socket table */
        lIdxDynSocket_uo = ( *SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[PduRRouteDest_cpst->txStaticSocketOrGroupIdx_uo].SoAd_Prv_idxDynSocTable_puo );

        /* Condition checks:
         * 1. Check Dynamic socket index is valid.
         * 2. Check for socket connection is ONLINE or
         * 3. Check SoAd_OpenSoCon is triggered by UL and SoAd_MainFunction was triggered or
         * 4. Check atleast SoAd_OpenSoCon is triggered by UL
         */
        /* Check for the elements, whether a routing group is referenced to this PduRouteDest */
        if( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo ) && \
            ( ( SOAD_SOCON_ACTIVE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en ) || \
              ( SOAD_EVENT_ONLINEREQ == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en ) || \
              ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConCloseReqCnt_u16 < SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConOpenReqCnt_u16 ) ) )
        {
            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00662] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /*** At SoAd_IfRoutingGroupTransmit() SoAd shall store a trigger transmit request for each SoAdPduRouteDest   ***/
            /*** that contains a reference to the routing group identified by the parameter id for transmission in        ***/
            /*** the SoAd_MainFunction()                                                                                  ***/
            /****************************************************************************************************************/

            /* Store the triggerTransmitRequest_u8 of the related PduRouteDestination with STD_ON */
            PduRRouteDest_cpst->triggerTransmissionInfo_puo->triggerTransmitRequest_u8 = STD_ON;

            /* Set the lFunctionRetVal_u8 to E_OK*/
            lFunctionRetVal_u8 = E_OK ;
        }
    }

    return lFunctionRetVal_u8;
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_IfRoutingGroupTransmitDetChk()
 *
 * \function description
 * This function is called from SoAd_IfRoutingGroupTransmit to handle the DET error for function arguments.
 * It covers SWS_SoAd_00661 & SWS_SoAd_00658 requirements
 *
 * Parameters (in) :
 * \param   SoAd_RoutingGroupIdType
 * \arg     RgId_uo - This parameter contains the routing group identifier indirectly specifying PDUs to be transmitted
 *                          and thereby specifying the socket to be used for transmission of the data.
 *
 * Parameters (inout): None
 *
 * Parameters (out):   None
 *
 * Return value:        None
 *
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_IfRoutingGroupTransmitDetChk( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_IF_ROUTING_GROUP_TRANSMIT_API_ID, SOAD_E_NOTINIT )

    /* Check whether id is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noRoutingGrps_cuo <= RgId_uo ), SOAD_IF_ROUTING_GROUP_TRANSMIT_API_ID, SOAD_E_INV_ARG )

    /* Check Configuration parameter SoAdRoutingGroupTxTriggerable set to TRUE for this Routing Group Id */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst ->SoAd_RoutingGrTriggerable_ROM_cpb[RgId_uo] == FALSE ) , SOAD_IF_ROUTING_GROUP_TRANSMIT_API_ID, SOAD_E_INV_ARG )

}
#endif /* ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */
#endif /* ( SOAD_IF_TRIGGER_TX_ENABLED != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
