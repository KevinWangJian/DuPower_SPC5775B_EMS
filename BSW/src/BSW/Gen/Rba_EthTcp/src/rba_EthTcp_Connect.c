

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CheckValidityOfRemoteAddr ( VAR( TcpIp_SocketIdType, AUTOMATIC )					TcpDynSockTblIdx_uo,
                                                                                      P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )	RemoteAddr_cpst );
#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Interface functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_Connect()	- By this API, the rba_EthTcp module is requested to establish a TCP connection to the configured	**/
/** 						peer																								**/
/**																																**/
/** Parameters (in):																											**/
/** TcpSockId_uo 		    - Tcp Socket id																		                **/
/** RemoteAddr_cpst 		- IP address and port of the remote host to connect to												**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			- Std_ReturnType																					**/
/** 							E_OK: The request has been accepted																**/
/** 							E_NOT_OK: The request has not been accepted														**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_Connect( VAR( TcpIp_SocketIdType, AUTOMATIC ) 					TcpSockId_uo,
															P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) 	RemoteAddr_cpst )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
	VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                       lDetErrorFlag_b;
#endif

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Check for DET errors */
    /* Report DET if rba_EthTcp module is uninitialized */
	rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if TcpSockId_uo is invalid */
	rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if RemoteAddr_cpst is NULL pointer */
    rba_EthTcp_CheckDetError( (RemoteAddr_cpst == NULL_PTR), RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );
    /* Report DET if remote domain is invalid */
    rba_EthTcp_CheckDetError( ( (RemoteAddr_cpst != NULL_PTR) && (TcpSockId_uo < TCPIP_TCPSOCKETMAX) && (rba_EthTcp_DynSockTbl_ast[TcpSockId_uo].DomainType_u32 != RemoteAddr_cpst->domain) ),
                                RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if remote IP address is invalid */
    /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
	rba_EthTcp_CheckDetError( ( (RemoteAddr_cpst != NULL_PTR) && RBA_ETHTCP_SOCKADDR_HAS_INVALID_IP(RemoteAddr_cpst) ),
                                RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_INV_SOCKADDR, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
        lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

        /* Process further only if socket is BOUND or OPENED (From LISTEN state, Connect can be called ). */
        if( lTcpDynSockTbl_pst->SockState_en >= RBA_ETHTCP_SOCK_BOUND_E )
        {
            /* -------------------------------------- */
            /* Check validity of remote address       */
            /* -------------------------------------- */

            /* Check if the remote address is a valid UNICAST address */
            lRetVal_en = rba_EthTcp_CheckValidityOfRemoteAddr( TcpSockId_uo, RemoteAddr_cpst );

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
            /* Report DET error in case remote address is MULTICAST or BROADCAST address */
            rba_EthTcp_CheckDetError( (lRetVal_en == E_NOT_OK), RBA_ETHTCP_E_CONNECT, RBA_ETHTCP_E_INV_SOCKADDR, &lDetErrorFlag_b );
#endif

            if ( lRetVal_en == E_OK )
            {
                /* ------------------------------------------------ */
                /* Connect for Tcp socket in CLOSED or LISTEN state */
                /* ------------------------------------------------ */
                if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSED_E)     ||
                     (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LISTEN_E) )
                {
                    /* Set destination port in the Tcp socket */
                    /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
					RBA_ETHTCP_COPY_SOCKADDR_TO_PORT( lTcpDynSockTbl_pst, RemoteAddr_cpst )

                    /* Set destination IP address in the Tcp socket */
                    /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                    RBA_ETHTCP_COPY_SOCKADDR_TO_IP( &(lTcpDynSockTbl_pst->RemoteIPAddr_un), RemoteAddr_cpst )

                    /* Call generator for Initial Sequence Number selection */
                    lTcpDynSockTbl_pst->IniSndSeqNum_u32 = rba_EthTcp_GenerateIsn( TcpSockId_uo );

                    /* Set the sequence number of the next frame to be sent */
                    rba_EthTcp_SetSeqNum( TcpSockId_uo, lTcpDynSockTbl_pst->IniSndSeqNum_u32 );

                    /* Send a SYN in the next MainFunction */
                    (void)rba_EthTcp_SetNextSendFrame( TcpSockId_uo, RBA_ETHTCP_SEND_SYN_E );

                    /* Socket is now OPENED for communication */
                    lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_OPENED_E;

                    /* Set the return value of the function to E_OK */
                    lFunctionRetVal_en = E_OK;
                }
            }
        }
	}

	return lFunctionRetVal_en;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_CheckValidityOfRemoteAddr    - This function check if the remote address address to connect is valid             **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RemoteAddr_cpst                         - Remote address to be checked                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: Remote address is valid (address is UNICAST)                              **/
/**                                             E_NOT_OK: Remote address is invalid                                             **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CheckValidityOfRemoteAddr( VAR( TcpIp_SocketIdType, AUTOMATIC )                   TcpDynSockTblIdx_uo,
                                                                                     P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )    RemoteAddr_cpst )
{
    /* Declare local variables */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )		lLocalAddrConfig_pcst;
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    P2VAR( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )        lIPAddrParamType_pun;
    VAR( TcpIp_AddressType, AUTOMATIC )                             lRetValAddrType_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( &( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );
    /* Get local address info from TcpIp cfg table */
    lRetVal_en = TcpIp_GetLocalAddrIdProperties( lTcpDynSockTbl_pst->LocalAddrId_u8, &lLocalAddrConfig_pcst );

    if ( lRetVal_en == E_OK )
    {
        lIPAddrParamType_pun = &(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un);

        switch( lTcpDynSockTbl_pst->DomainType_u32 )
        {
			#if ( TCPIP_IPV4_ENABLED == STD_ON )
            case TCPIP_AF_INET:
			{
                /* Check if destination IPv4 is a UNICAST, MULTICAST or BROADCAST address */
				/* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                lRetValAddrType_en = rba_EthIPv4_ChkIPv4AddrType( ((const TcpIp_SockAddrInetType*) RemoteAddr_cpst)->addr[0], lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32, lIPAddrParamType_pun->IPv4Par_st.NetMask_u32 );

                /* If destination is UNICAST */
                if( lRetValAddrType_en == TCPIP_UNICAST )
                {
                    lFunctionRetVal_en = E_OK;  /* Remote IP address in UNICAST so the remote address is validated */
                }
			}
            break;
			#endif

			#if ( TCPIP_IPV6_ENABLED == STD_ON )
            case TCPIP_AF_INET6:
			{
                /* Verify that the remote IPv6 address is not of multicast type */
                if( rba_EthIPv6_IsIPv6AddrTypeMulticast( &(lIPAddrParamType_pun->IPv6Par_st.IpAddr_st) ) != FALSE )
                {
                    lFunctionRetVal_en = E_OK;  /* Remote IP address in UNICAST so the remote address is validated */
                }
			}
            break;
			#endif

            default:
			{
                /* If execution reaches here, then the IP support for the specified domain is not enabled; set return value to E_NOT_OK. */
				lFunctionRetVal_en = E_NOT_OK;
			}
            break;
        }
    }

    return lFunctionRetVal_en;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */















