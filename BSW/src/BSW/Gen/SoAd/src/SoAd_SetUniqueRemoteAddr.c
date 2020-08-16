

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
static FUNC( void, SOAD_CODE ) SoAd_SetUniqueRemoteAddrDetChk( VAR  ( SoAd_SoConIdType, AUTOMATIC )                 SoConId_uo, \
                                                               P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst, \
                                                               P2CONST( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )    AssignedSoConId_cpst);
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_SetUniqueRemoteAddr()
 *
 * \Function description
 * The TCP/IP stack calls this function after a socket was set into the listen state with TcpIp_TcpListen() and a
 * TCP connection is requested by the peer.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId : Index of any socket connection that is part of the SoAdSocketConnectionGroup.
 * \param   TcpIp_SockAddrType
 * \arg     RemoteAddrPtr : Pointer to the structure containing the requested remote IP address and port..
 * \param   SoAd_SoConIdType
 * \arg     AssignedSoConIdPtr: Pointer to the SoAd_SoConIdType where the index of the socket connection
 *                              configured with the remote address (IpAddrPtr) shall be stored..
 *
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK :      The request was accepted.
 *          E_NOT_OK:   The request was rejected and AssignedSoConIdPtr remains unchanged.
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_SetUniqueRemoteAddr( VAR  ( SoAd_SoConIdType, AUTOMATIC )                SoConId, \
                                                            P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr, \
                                                            P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )     AssignedSoConIdPtr)
{
    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* variable to store the return value of internal function */
    VAR( Std_ReturnType, AUTOMATIC )                        lRetVal_u8;

    /* variable to hold index of static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

    /* variable to store the dynamic socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Variable to get the socket connection groupe Id */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lSoConGrpId_uo;

    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)                                  lRemoteAddrPort_u16;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_SetUniqueRemoteAddrDetChk(SoConId, RemoteAddrPtr, (const SoAd_SoConIdType*)AssignedSoConIdPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        lIdxStaticSocket_uo     = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

        /* Get the socket connection group Id */
        lSoConGrpId_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].soConGrpId_uo;
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

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00675] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** The function SoAd_SetUniqueRemoteAddr() shall check if one of the socket connections of the socket        ***/
        /** connection group, identified by SoConId, is already configured with the address specified by              ***/
        /** RemoteAddrPtr. In this case, it shall return the socket connection index via AssignedSoConIdPtr           ***/
        /**                             and return E_OK                                                               ***/
        /****************************************************************************************************************/

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00676] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** If no socket connection is already configured with the address specified by RemoteAddrPtr,                ***/
        /** SoAd_SetUniqueRemoteAddr() shall                                                                          ***/
        /** (1) choose an unused socket connection using the best match algorithm described in [SWS_SoAd_00680]       ***/
        /** (2) set it to the remote address specified by RemoteAddrPtr                                               ***/
        /** (3) set AssignedSoConIdPtr to the index of the chosen socket connection and                               ***/
        /** (4) return E_OK.                                                                                          ***/
        /** A socket connection is 'unused' if its actual remote address has an IP address wildcard and/or port       ***/
        /** wildcard                                                                                                  ***/
        /****************************************************************************************************************/

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00678] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** SoAd_SetUniqueRemoteAddr() shall reject the request and return E_NOT_OK if there are no unused socket     ***/
        /** connections within the socket connection group identified by SoConId                                      ***/
        /****************************************************************************************************************/

        /* Above listed all 3 requirements are covered at below function */
        /* get the Best Macht Algorithm */
        lRetVal_u8 = SoAd_BestMatchAlgorithm( SoConId, lSoConGrpId_uo, 0, RemoteAddrPtr, &lIdxStaticSocket_uo );

        if ( E_OK == lRetVal_u8 )
        {
            /* Get the dynamic socketId of the static socketId */
            lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].SoAd_Prv_idxDynSocTable_puo);

            lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

            /* overwrite the remote address by the source socket address (IP address and port) of the received message */
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_ADDR(RemoteAddrPtr, lSoAdDyncSocConfig_pst)

            /* return the socket connection index via AssignedSoConIdPtr */
            *AssignedSoConIdPtr = lIdxStaticSocket_uo;

            /* The request was accepted */
            lFunctionRetVal_u8 = E_OK;
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
}


#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_SetUniqueRemoteAddrDetChk()
 *
 * \function description
 * This function is called from SoAd_OpenSoCon to handle the DET error for function arguments.
 * It covers SWS_SoAd_00672, SWS_SoAd_00673 & SWS_SoAd_00699 requirements
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo : Index of any socket connection that is part of the SoAdSocketConnectionGroup.
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddr_cpst : Pointer to the structure containing the requested remote IP address and port..
 * \param   const SoAd_SoConIdType*
 * \arg     AssignedSoConId_cpst: Pointer to the SoAd_SoConIdType where the index of the socket connection
 *                                configured with the remote address (IpAddrPtr) shall be stored.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_SetUniqueRemoteAddrDetChk( VAR  ( SoAd_SoConIdType, AUTOMATIC )                 SoConId_uo, \
                                                               P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst, \
                                                               P2CONST( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )    AssignedSoConId_cpst)
{
    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)                                  lRemoteAddrPort_u16;


    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_SET_UNIQUE_REMOTE_ADDRESS_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ), SOAD_SET_UNIQUE_REMOTE_ADDRESS_API_ID, SOAD_E_INV_ARG )

    /* Check whether AssignedSoConIdPtr & RemoteAddrPtr pointers are valid or not */
    SOAD_DET_REPORT_ERROR( ( ( NULL_PTR == AssignedSoConId_cpst ) || ( NULL_PTR == RemoteAddr_cpst ) ), SOAD_SET_UNIQUE_REMOTE_ADDRESS_API_ID, SOAD_E_PARAM_POINTER )

    if(SoAd_DetErrFlag_u8 == E_NOT_OK)
    {
        /* get the port from socket AFTER checking socket pointer for NULL value */
		/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        lRemoteAddrPort_u16 = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddr_cpst);

        /* Check whether Domain and port are valid */
        SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].domain_en != RemoteAddr_cpst->domain ) || \
                                 ( lRemoteAddrPort_u16 == SOAD_DHCP_RESERVED_CLIENT_PORT) || \
                                 ( lRemoteAddrPort_u16 == SOAD_DHCP_RESERVED_SERVER_PORT ) ), \
                                     SOAD_SET_UNIQUE_REMOTE_ADDRESS_API_ID, SOAD_E_INV_ARG )
    }
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
