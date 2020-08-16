

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


/*
 ***************************************************************************************************
 * Interface functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_GetSocket()  - By this API service the TCP stack is requested a new Tcp socket                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** Domain_u32              - Internet domain (address family AF_INET or AF_INET6)                                              **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** SocketIdPtr_puo         - Pointer to the allocated Tcp socket                                                               **/
/**                                                                                                                             **/
/** Return value:           - Std_ReturnType                                                                                    **/
/**                             E_OK: The request has been accepted                                                             **/
/**                             E_NOT_OK: The request has not been accepted                                                     **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_GetSocket( VAR( TcpIp_DomainType, AUTOMATIC )                    Domain_u32,
                                                              P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )     SocketIdPtr_puo )
{
    /* Declare local variables */
    VAR( TcpIp_SocketIdType, AUTOMATIC )            lIdx_uo;
    VAR( Std_ReturnType, AUTOMATIC )                lFunctionRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                       lDetErrorFlag_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Check for DET errors */
    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_GETSOCKET , RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if SocketIdPtr_puo is a NULL pointer */
    rba_EthTcp_CheckDetError( (SocketIdPtr_puo == NULL_PTR), RBA_ETHTCP_E_GETSOCKET , RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* If there are remaining free Tcp sockets */
        if( rba_EthTcp_SockConnCntr_u16 < TCPIP_TCPSOCKETMAX )
        {
            /* Check if Socket is available */
           for( lIdx_uo = 0; (lIdx_uo < TCPIP_TCPSOCKETMAX); lIdx_uo++ )
           {
               /* State should either be RBA_ETHTCP_SOCK_CLOSED_E  */
               if( rba_EthTcp_DynSockTbl_ast[lIdx_uo].SockState_en == RBA_ETHTCP_SOCK_CLOSED_E )
               {
                   /* Now socket is allocated */
                   rba_EthTcp_DynSockTbl_ast[lIdx_uo].SockState_en = RBA_ETHTCP_SOCK_ALLOCATED_E;

                   /* Set socket table with Domain */
                   rba_EthTcp_DynSockTbl_ast[lIdx_uo].DomainType_u32 = Domain_u32;

                   /* Set the socket number as return value */
                   ( * SocketIdPtr_puo ) = lIdx_uo;

                   /* Increment the total number of used Tcp sockets */
                   rba_EthTcp_SockConnCntr_u16++;

                   /* Set return value to E_OK */
                   lFunctionRetVal_en = E_OK;

                   break;
               }
            }
        }
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FindTcpSockId()  - By this API service the Tcp stack is requested a a index of the socket                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** LocalAddr_cpst              - Pointer to Local address information                                                          **/
/** RemoteAddr_cpst             - pointer to Remote address information                                                         **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** SocketIdPtr_puo             - Pointer to the found Tcp socket                                                               **/
/**                                                                                                                             **/
/** Return value                - Std_ReturnType                                                                                **/
/**                                 E_OK: Socket found with corresponding remote/local address                                  **/
/**                                 E_NOT_OK: Socket didnot found with corresponding remote/local address                       **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC (Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FindTcpSockId (  P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)   LocalAddr_cpst,
                                                                    P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)   RemoteAddr_cpst,
                                                                    P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )   SocketIdPtr_puo )

{
    /* Declare local variables */
	P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )		lLocalAddrConfig_pcst;
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    P2VAR( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )        lIPAddrParamType_pun;
    VAR( TcpIp_SocketIdType, AUTOMATIC )                            lIdx_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                       lDetErrorFlag_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en	= E_NOT_OK;
	lRetVal_en 			= E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_FINDTCPSOCKID , RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if lLocalAddr_st is NULL pointer */
    rba_EthTcp_CheckDetError( (LocalAddr_cpst == NULL_PTR), RBA_ETHTCP_FINDTCPSOCKID , RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );
    /* Report DET if lLocalAddr_st is invalid socket address structure */
    /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
    rba_EthTcp_CheckDetError( ( ( LocalAddr_cpst != NULL_PTR ) && RBA_ETHTCP_SOCKADDR_HAS_INVALID_IP(LocalAddr_cpst) ),
                              RBA_ETHTCP_FINDTCPSOCKID , RBA_ETHTCP_E_INV_SOCKADDR, &lDetErrorFlag_b );
    /* Report DET if lRemoteAddr_st is NULL pointer */
    rba_EthTcp_CheckDetError( (RemoteAddr_cpst == NULL_PTR), RBA_ETHTCP_FINDTCPSOCKID , RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );
    /* Report DET if SocketIdPtr_puo is a NULL pointer */
    rba_EthTcp_CheckDetError( (SocketIdPtr_puo == NULL_PTR), RBA_ETHTCP_FINDTCPSOCKID , RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Loop through all Tcp sockets */
        for ( lIdx_uo = 0U; lIdx_uo < TCPIP_TCPSOCKETMAX; lIdx_uo++ )
        {
            /* Retrieve the local address IP */
            lTcpDynSockTbl_pst	= &(rba_EthTcp_DynSockTbl_ast[lIdx_uo]);
            lRetVal_en      	= TcpIp_GetLocalAddrIdProperties( lTcpDynSockTbl_pst->LocalAddrId_u8, &lLocalAddrConfig_pcst );

            if( lRetVal_en == E_OK)
            {
                lIPAddrParamType_pun    = &(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un);

               /* Check if Domain, IP and Port values match */
                if ( (lTcpDynSockTbl_pst->DomainType_u32 == (uint16)LocalAddr_cpst->domain)             &&
                     /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                     RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_PORT_EQUAL( lTcpDynSockTbl_pst, LocalAddr_cpst )   &&
                     /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                     RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_PORT_EQUAL( lTcpDynSockTbl_pst, RemoteAddr_cpst ) &&
                     /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                     RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_IP_EQUAL( lIPAddrParamType_pun, LocalAddr_cpst )   &&
                     /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
                     RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_IP_EQUAL( &(lTcpDynSockTbl_pst->RemoteIPAddr_un), RemoteAddr_cpst ) )
                {
                    ( * SocketIdPtr_puo ) = lIdx_uo;
                    lFunctionRetVal_en = E_OK;
                    break;
                }
            }
        }
    }

    return lFunctionRetVal_en;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */














