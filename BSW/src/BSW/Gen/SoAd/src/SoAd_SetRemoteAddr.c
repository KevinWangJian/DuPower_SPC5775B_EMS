

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

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

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_SetRemoteAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                    SoConId_uo, \
                                                         P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC) RemoteAddrPtr_cpst);
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_SetRemoteAddr()
 *
 * \Function description
 *  By this API service the remote address (IP address and port) of the specified socket connection shall be set.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index specifying the socket connection for which the remote address shall be set.
 * \param   TcpIp_SockAddrType*
 * \arg     RemoteAddrPtr - Struct contain the IP address and port to be set.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK: The request has been accepted
 *          E_NOT_OK: The request has not been accepted
 *
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_SetRemoteAddr( VAR( SoAd_SoConIdType, AUTOMATIC )                 SoConId , \
                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr )
{
    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* Index to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)                                  lRemoteAddrPort_u16;

    /* Variable to store the port for dynamic socket */
    VAR(uint16, AUTOMATIC)                                  lDyncSocPort_u16;

    /* Variable to hold if the address from RemoteAddrPtr is wildcard (ANY) */
    VAR(boolean, AUTOMATIC)                                 lRemoteIpAddrIsWildcard_b;

    /* Variable to store if the remote IP address of dynamic socket is wildcard (ANY) */
    VAR(boolean, AUTOMATIC)                                 lDyncSocConfigHasWildcardAnyAddr_b;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_SetRemoteAddrDetChk(SoConId, RemoteAddrPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* Get the "index of dynamic socket table" from static socket table */
        lIdxDynSocket_uo = (* SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].SoAd_Prv_idxDynSocTable_puo) ;

        /* Dynamic socket is not yet assigned for the static socket, That means no SoAd_OpenSoCon is called for this socket.
         * So, first get the available dynamic socket and link it with the static socket and update the remote address in dync table */
        if(lIdxDynSocket_uo >= SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo)
        {
            /* Get the available dynamic socket from the list by calling a function */
            SoAd_ReserveFreeDynSocket(SoConId, &lIdxDynSocket_uo);
        }

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00532] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** The function SoAd_SetRemoteAddr() shall only proceed if SoConId refers to                                 ***/
        /**  (1) a socket connection that is in the mode SOAD_SOCON_OFFLINE or                                        ***/
        /**  (2) a UDP socket connection that has no active TP session (i.e. no reception or transmission via the     ***/
        /**      TP-API ongoing). Otherwise the request shall be rejected and return with E_NOT_OK                    ***/
        /****************************************************************************************************************/
        /****************************************************************************************************************/

        /* Condition checks:
         * 1. The dynamic socket is valid or not
         * 2. The remote address is updated for TCP only if socket connection is closed. or
         * 3. Remote address shall be updated for UDP sockets if there are no active TP processing on this socket connection,
         *    even though socket is ONLINE
         */
        if( ( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo) &&
            ( ( SOAD_SOCON_OFFLINE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConMode_en )
#if (SOAD_UDP_PRESENT != STD_OFF )
         || ( ( TCPIP_IPPROTO_UDP == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].soConGrpId_uo].soConGrpProtocol_en )
#if (SOAD_TP_PRESENT != STD_OFF )
         && ( FALSE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmissionOnGoing_b )
         && ( FALSE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b )
#endif /* SOAD_TP_PRESENT != STD_OFF */
                )
#endif /* SOAD_UDP_PRESENT != STD_OFF */
            ) )
        {
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            lRemoteAddrPort_u16 = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddrPtr);

            /* As per SoAd old design 0xFFFFU was treated as wildcard remote address
             * As per Diamler Importer scripts, 0 has to be treated as wild card.
             * So, SoAd will treat both 0xFFFFU and 0 as wildcard by considering the backward compatibility and TCPIP_PORT_ANY will be used
             * as wildcard inside SoAd component. So It will be overwritten with TCPIP_PORT_ANY if port is 0xFFFFU */
            if( 0xFFFFU == lRemoteAddrPort_u16)
            {
				/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
                SOAD_SET_PORT_TO_SOCK_ADDR(RemoteAddrPtr, TCPIP_PORT_ANY)
            }

			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            lRemoteIpAddrIsWildcard_b = SOAD_SOCK_ADDR_HAS_WILDCARD_IPADDR(RemoteAddrPtr);
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            lRemoteAddrPort_u16       = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddrPtr);

            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00687] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /** If the function SoAd_SetRemoteAddr() is used to set the remote address of a socket connection that is in  ***/
            /** the mode SOAD_SOCON_ONLINE to a value that contains wildcards, SoAd shall change the mode of the socket   ***/
            /** connection to SOAD_SOCON_RECONNECT                                                                        ***/
            /****************************************************************************************************************/
            /****************************************************************************************************************/

            /* Condition checks:
             * 1. socket connection state is ONLINE.
             * 2. Remote address is wild card,
             */
            /*  If socket connection state is ONLINE and remote address is wild card then change the state of the socket connection to RECONNECT state*/
            if( ( SOAD_SOCON_ONLINE  == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConMode_en ) && \
                ( ( TCPIP_PORT_ANY   == lRemoteAddrPort_u16 ) || lRemoteIpAddrIsWildcard_b ) )
            {
                /* Set the connection request state to reconnect such that it shall be tried in next main function */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en  = SOAD_SOCON_BOUND;

                /* call a function which shall invoke the upper layer call back for mode change */
                SoAd_ModeChgCallbackToUl( SoConId, lIdxDynSocket_uo, SOAD_SOCON_RECONNECT );
            }
            else
            {
                lDyncSocConfigHasWildcardAnyAddr_b = SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( ((SoAd_DyncSocConfigType_tst *) &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])) );
                lDyncSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG( ((SoAd_DyncSocConfigType_tst *)  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])) );

                if( ( SOAD_SOCON_RECONNECT  == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConMode_en ) && \
                     ( SOAD_SOCON_BOUND == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en ) && \
                     ( ( TCPIP_PORT_ANY   ==  lDyncSocPort_u16) || lDyncSocConfigHasWildcardAnyAddr_b) && \
                     ( ( TCPIP_PORT_ANY   != lRemoteAddrPort_u16 ) && !lRemoteIpAddrIsWildcard_b ) )
                {
                    /* Set the connection request state to reconnect such that it shall be tried in next main function */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en  = SOAD_SOCON_ACTIVE;

                    /* call a function which shall invoke the upper layer call back for mode change */
                    SoAd_ModeChgCallbackToUl( SoConId, lIdxDynSocket_uo, SOAD_SOCON_ONLINE );
                }
            }

            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00533] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /** The function SoAd_SetRemoteAddr() shall set the remote address of the socket connection referred by       ***/
            /** parameter SoConId according to the IP address and port specified by parameter RemoteAddrPtr               ***/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /* Load the remote address value in dynamic socket table */
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_ADDR(RemoteAddrPtr, ((SoAd_DyncSocConfigType_tst *)  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])) )

            /*  the return value set to E_OK*/
            lFunctionRetVal_u8 = E_OK;

        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);

}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_SetRemoteAddrDetChk()
 *
 * \function description
 * This function is called from SoAd_SetyRemoteAddr to handle the DET error for function arguments.
 * It covers SWS_SoAd_00628, SWS_SoAd_00531 & SWS_SoAd_00699 requirements
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection for which the remote address shall be set.
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddrPtr_cpst - Struct contain the IP address and port to be set.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_SetRemoteAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                 SoConId_uo, \
                                                         P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)  RemoteAddrPtr_cpst)
{
    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)  lRemoteAddrPort_u16;

    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_SET_REMOTE_ADDRESS_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ), SOAD_SET_REMOTE_ADDRESS_API_ID, SOAD_E_INV_ARG )

    /* Check whether RemoteAddrPtr pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == RemoteAddrPtr_cpst ), SOAD_SET_REMOTE_ADDRESS_API_ID, SOAD_E_PARAM_POINTER )

    if(SoAd_DetErrFlag_u8 == E_NOT_OK)
    {
        /* get the port for the socket AFTER checking the socket for null pointer*/
		/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        lRemoteAddrPort_u16 = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddrPtr_cpst);

        /* Check whether Domain and port are valid */
        SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].domain_en != RemoteAddrPtr_cpst->domain)  || \
                                 ( lRemoteAddrPort_u16 == SOAD_DHCP_RESERVED_CLIENT_PORT ) || \
                                 ( lRemoteAddrPort_u16 == SOAD_DHCP_RESERVED_SERVER_PORT ) ), \
                                     SOAD_SET_REMOTE_ADDRESS_API_ID, SOAD_E_INV_ARG )

        /* Check whether Automatic socket is enabled or not */
        SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].soConGrpAutoConSetup_b ) == TRUE ), SOAD_SET_REMOTE_ADDRESS_API_ID, SOAD_E_INV_ARG )
    }
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
