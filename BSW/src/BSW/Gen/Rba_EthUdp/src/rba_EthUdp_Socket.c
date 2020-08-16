
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )
#include "rba_EthUdp.h"

#include "SoAd_Cbk.h"
#include "TcpIp_Prv.h"
#include "rba_EthUdp_Prv.h"

#define RBA_ETHUDP_START_SEC_CODE
#include "rba_EthUdp_MemMap.h"
/*********************************************************************************************************************/
/* rba_EthUdp_GetSocket() -  By this API service the rba_EthUdp is requested to allocate a new socket.               */
/*                                                                                                                   */
/* Input Parameters :                                                                                                */
/* Domain_u32          - IP address family.                                                                          */
/*                                                                                                                   */
/* Output Parameters :                                                                                               */
/* SocketIdPtr_pu16 - Pointer to socket identifier representing the requested socket.                                */
/*                                                                                                                   */
/* Std_ReturnType     - E_OK or E_NOT_OK - Result of operation                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_GetSocket( VAR( TcpIp_DomainType,                AUTOMATIC )   Domain_u32,
                                                              P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )   SocketIdPtr_pu16 )
{
    /* Local variable declaration */
    VAR( TcpIp_SocketIdType, AUTOMATIC )                     lSocIdx_u16;
    VAR( Std_ReturnType, AUTOMATIC )             lRetValStdType_en;

    /* Local variable initialization */
    lRetValStdType_en = E_NOT_OK;

    /* Report DET if rba_EthUdp module is uninitialized */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == rba_EthUdp_Config_pco ), RBA_ETHUDP_E_GET_SOCKET_API_ID, RBA_ETHUDP_E_NOTINIT, E_NOT_OK )

    /* Report DET if requested domain type is not TCPIP_AF_INET (IPv4) or TCPIP_AF_INET6 (IPv6).*/
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ((TCPIP_AF_INET != Domain_u32) && (TCPIP_AF_INET6 != Domain_u32)) , RBA_ETHUDP_E_GET_SOCKET_API_ID, RBA_ETHUDP_E_AFNOSUPPORT, E_NOT_OK )

    /* Report DET if SocketIdPtr is a Null Pointer */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == SocketIdPtr_pu16 ), RBA_ETHUDP_E_GET_SOCKET_API_ID, RBA_ETHUDP_E_NULL_PTR, E_NOT_OK )

    /* Check if any Udp socket is available */
    if(rba_EthUdp_UsedSocCnt_u16 < TCPIP_UDPSOCKETMAX)
    {
        /* Loop through all sockets to find free socket */
        for(lSocIdx_u16 = 0; lSocIdx_u16 < TCPIP_UDPSOCKETMAX; lSocIdx_u16++)
        {
            if(RBA_ETHUDP_SOCK_CLOSED == rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].SockState_en)
            {
                rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].DomainType_u32 = Domain_u32;              /* Update socket properties - domain and state */
                rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].SockState_en  = RBA_ETHUDP_SOCK_OPEN;

                *SocketIdPtr_pu16 = lSocIdx_u16;
                rba_EthUdp_UsedSocCnt_u16++;                                                  /* Increment used socket count */
                lRetValStdType_en = E_OK;
                break;
            }

        }
    }

    return lRetValStdType_en;
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* rba_EthUdp_Bind() - By this API rba_EthUdp is requested to bind a UDP socket to a local resource                 */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* SocketId_u16     - Socket identifier of the related local socket resource.                                       */
/* LocalAddrId_u8   - IP address identifier representing the local IP address to be bound to the socket             */
/* FramePrio_u8     - Frame priority to be set the socket                                                           */
/*                                                                                                                  */
/* InOut Parameters :                                                                                               */
/* Port_pu16           - Local port to which the socket shall be bound. In case the parameter Port is specified as  */
/*                        TCPIP_PORT_ANY, the TCP/IP stack shall choose the local port automatically from the range */
/*                        49152 to 65535 and shall update the parameter Port to the chosen value.                   */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/* Std_ReturnType   - E_OK or E_NOT_OK - Result of operation                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_Bind( VAR( TcpIp_SocketIdType,               AUTOMATIC )       SocketId_u16,
                                                         VAR( TcpIp_LocalAddrIdType,            AUTOMATIC )       LocalAddrId_u8,
                                                         P2VAR( uint16,              AUTOMATIC, AUTOMATIC )       Port_pu16,
                                                         VAR( uint8,                            AUTOMATIC )       FramePrio_u8)
{
    /* Local variable declaration */
    VAR( Std_ReturnType,           AUTOMATIC )         lRetValStdType_en;
    VAR( uint8,                    AUTOMATIC )         lEthIfCtrl_u8;
    VAR( TcpIp_SocketIdType,       AUTOMATIC )         lSocIdx_u16;
    VAR( boolean,                  AUTOMATIC )         lWildCardPort_b;
    VAR( boolean,                  AUTOMATIC )         lAddrInUse_b;

    /* Local variable initialization */
    lWildCardPort_b = FALSE;
    lAddrInUse_b    = FALSE;
    lSocIdx_u16     = 0;

    /* Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == rba_EthUdp_Config_pco ), RBA_ETHUDP_E_BIND_API_ID, RBA_ETHUDP_E_NOTINIT, E_NOT_OK )

    /* Report DET if SocketId is not valid */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( (TCPIP_UDPSOCKETMAX <= SocketId_u16 ), RBA_ETHUDP_E_BIND_API_ID, RBA_ETHUDP_E_INV_ARG, E_NOT_OK )

    /* Report DET if Port_pu16 is a Null Pointer */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == Port_pu16 ), RBA_ETHUDP_E_BIND_API_ID, RBA_ETHUDP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) <= LocalAddrId_u8 ), RBA_ETHUDP_E_BIND_API_ID , RBA_ETHUDP_E_INV_ARG, E_NOT_OK )

    /* Report DET if domain associated with Socket table and LocalAddrId is not same. This also ensures that socket state is either RBA_ETHUDP_SOCK_OPEN or RBA_ETHUDP_SOCK_BOUND */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32 != ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].IpDomainType_u32 ) ), \
                                        RBA_ETHUDP_E_BIND_API_ID , RBA_ETHUDP_E_INV_ARG, E_NOT_OK )

    /* Get EthIfCtrlIdx mapped to the localAddress */
    lEthIfCtrl_u8 = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].EthIfCtrlRef_u8 );

    /* Check whether the LocalAddress has IP assigned */
    lRetValStdType_en = TcpIp_CheckValidityOfLocalAddrId( LocalAddrId_u8 ) ;

    /* Raise DET if local address id is invalid. For Dhcp sockets binding is allowed even if IP address is unassigned */
	RBA_ETHUDP_DET_REPORT_ERROR_NO_RET( ( ( E_NOT_OK == lRetValStdType_en ) && ( TCPIP_DHCPCLIENT_PORT != *(Port_pu16) )),
	                                        RBA_ETHUDP_E_BIND_API_ID , RBA_ETHUDP_E_ADDRNOTAVAIL )

    if( ( RBA_ETHUDP_SOCK_OPEN == rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en ) &&                             /* Check whether the socket state OPEN                                                                        */
        ( ( (E_OK  == lRetValStdType_en) && (TCPIP_STATE_ONLINE == TcpIp_EthIfCtrlSt_aen[lEthIfCtrl_u8]) )||            /* For Non-Dhcp sockets binding localAddress must have IP assigned and Ctrl state shall be TCPIP_STATE_ONLINE */
          ( (TCPIP_DHCPCLIENT_PORT == *Port_pu16) && (TCPIP_STATE_STARTUP == TcpIp_EthIfCtrlSt_aen[lEthIfCtrl_u8]) ) ) ) /* For Dhcp sockets binding is allowed even if the TcpIp Ctrl state is STARTUP                                */
    {
        /* In case the parameter is specified as TCPIP_PORT_ANY, the TCP/IP stack shall choose the local port automatically */
        /* from the range 49152(0xC000) to 65535(0xFFFF) and shall update the parameter to the chosen value                 */
        if( TCPIP_PORT_ANY == *Port_pu16 )
        {
            *Port_pu16 = rba_EthUdp_PortAny_u16;
            rba_EthUdp_PortAny_u16++;

            /* Set flag indicating PORT_ANY to true */
            lWildCardPort_b = TRUE;

            /* If rba_EthUdp_PortAny_u16 >= 65535, then set rba_EthUdp_PortAny_u16 to 49152 (0xC000) */
            if ( TCPIP_LOCAL_PORT_ANY_END == rba_EthUdp_PortAny_u16  )
            {
                rba_EthUdp_PortAny_u16 = TCPIP_LOCAL_PORT_ANY_START;
            }
        }

        /* Check if the local addrId and port combination passed as input parameters, is already bound by another UDP socket */
        while( lSocIdx_u16 < TCPIP_UDPSOCKETMAX )
        {
            /* The check is valid for unicast IP address and it should not be the same socket */
            if( ( SocketId_u16 != lSocIdx_u16 ) &&
                ( LocalAddrId_u8 == rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalAddrId_u8 ) &&
                ( *(Port_pu16) == rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalPort_u16) &&
                ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].IpAddressType_en  == TCPIP_UNICAST ) )
            {
                if( FALSE == lWildCardPort_b )
                {
                    /* Report DET as local addrId and port combination is already in use */
                    RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_BIND_API_ID , RBA_ETHUDP_E_ADDRINUSE )

                    lRetValStdType_en = E_NOT_OK;
                    lAddrInUse_b      = TRUE;

                    break;
                }
                else
                {
                    /* If assigned port in PORT_ANY range is already in use, increment rba_EthUdp_PortAny_u16 and assign the new port number */
                    *Port_pu16 = rba_EthUdp_PortAny_u16;
                    rba_EthUdp_PortAny_u16++;

                    /* If rba_EthUdp_PortAny_u16 >= 65535, then set rba_EthUdp_PortAny_u16 to 49152 (0xC000) */
                    if ( TCPIP_LOCAL_PORT_ANY_END == rba_EthUdp_PortAny_u16  )
                    {
                        rba_EthUdp_PortAny_u16 = TCPIP_LOCAL_PORT_ANY_START;
                    }

                    /* Check again for all sockets if the newly assigned port number is in use */
                    lSocIdx_u16 = 0;
                }
            }
            else
            {
                lSocIdx_u16++;
            }
        }

        if( lAddrInUse_b == FALSE )
        {
            /* Bind the socket with local address information and set the state to RBA_ETHUDP_SOCK_BOUND */
            rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8   = LocalAddrId_u8;
            rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalPort_u16    = *Port_pu16;
            rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en     = RBA_ETHUDP_SOCK_BOUND;

            /* Update FramePrio value if not updated previously by rba_EthUdp_ChangeParameter() */
            if( rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8 == 0xFFu )
            {
                rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8 = FramePrio_u8;
            }

            lRetValStdType_en = E_OK;
        }

    }   /* Check whether the bind is requested for the socket which is aready in state RBA_ETHUDP_SOCK_BOUND */
    else if( RBA_ETHUDP_SOCK_BOUND == rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en )
    {
        /* If bind is requested for the socket which is aready in state RBA_ETHUDP_SOCK_BOUND and  */
        /* requested socket properties are same as current assigned properties return with E_OK */
        if( (LocalAddrId_u8 == rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8) &&
            (*Port_pu16 == rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalPort_u16) &&
            (FramePrio_u8 == rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8) )
        {
            lRetValStdType_en = E_OK;
        }
        else   /* If requested socket properties are different than current assigned rpoperties throw DET */
        {
            /* Report DET if rba_EthUdp_Bind() is called for the socket which is already in state RBA_ETHUDP_SOCK_BOUND */
            RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_BIND_API_ID , RBA_ETHUDP_E_INV_ARG )

            lRetValStdType_en = E_NOT_OK;
        }
    }
    else
    {
        lRetValStdType_en = E_NOT_OK;
    }

    return lRetValStdType_en;
}



/********************************************************************************************************************/
/* rba_EthUdp_TerminateSocUsingLocalAddr - This API closes all Udp sockets excpt Dhcp client if input parameter     */
/*                LocalAddrId_u8 is TCPIP_LOCALADDRID_INVALID else closes only sockets mapped to the LocalAddrId_u8 */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* LocalAddrId_u8      -  Local adress for whcih sockets needs to be closed                                         */
/*                                                                                                                  */
/* Return type :        void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_TerminateSocUsingLocalAddr(VAR( TcpIp_LocalAddrIdType, AUTOMATIC )          LocalAddrId_u8)
{
    /* Local Variable declaration */
    VAR( TcpIp_SocketIdType, AUTOMATIC )                     lSocIdx_u16;

    /* Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( (NULL_PTR == rba_EthUdp_Config_pco), RBA_ETHUDP_E_TERMINATE_SOC_USING_LOCALADDR_API_ID, RBA_ETHUDP_E_NOTINIT )

    /* Loop through Udp socket table and close all the sockets mapped to the requested localAddress */
    for(lSocIdx_u16 = 0; lSocIdx_u16 < TCPIP_UDPSOCKETMAX; lSocIdx_u16++)
    {
        if( ( (LocalAddrId_u8 == rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalAddrId_u8 ) ||
              (LocalAddrId_u8 == TCPIP_LOCALADDRID_INVALID) )&&
            ( TCPIP_DHCPCLIENT_PORT != rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalPort_u16 ) )
        {
            rba_EthUdp_Close(lSocIdx_u16);
        }
    }

}


/********************************************************************************************************************/
/* rba_EthUdp_Close     -By this API service rba_EthUdp stack is requested to close the socket                      */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* SocketId_u16         - Socket identifier of the related local socket resource.                                   */
/*                                                                                                                  */
/* Return type :        void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, RBA_ETHUDP_CODE )  rba_EthUdp_Close(    VAR( TcpIp_SocketIdType, AUTOMATIC )        SocketId_u16 )
{

    /* Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( (NULL_PTR == rba_EthUdp_Config_pco), RBA_ETHUDP_E_CLOSE_API_ID, RBA_ETHUDP_E_NOTINIT )

    /* Report DET if SocketId_u16 is invalid */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( (TCPIP_UDPSOCKETMAX <= SocketId_u16 ), RBA_ETHUDP_E_CLOSE_API_ID, RBA_ETHUDP_E_INV_ARG )

    /* Check whether the socket is already closed */
    if(RBA_ETHUDP_SOCK_CLOSED != rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en)
    {
        /* Decrement used socket counter by 1 */
        rba_EthUdp_UsedSocCnt_u16--;

        /* If the socket is not Dhcp socket inform SoAd about closing of socket */
        if(TCPIP_DHCPCLIENT_PORT != rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalPort_u16)
        {
            SoAd_TcpIpEvent( TCPIP_UDP_SOCKET_OFFSET + SocketId_u16, TCPIP_UDP_CLOSED );
        }
    }

    /* Reset socket properties to initial value */
    rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32    = TCPIP_AF_NONE;
    rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8    = (TcpIp_LocalAddrIdType) TCPIP_LOCALADDRID_INVALID;
    rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalPort_u16     = TCPIP_PORT_ANY;
    rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8  = 0xFFu;
    rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en      = RBA_ETHUDP_SOCK_CLOSED;

}

/********************************************************************************************************************/
/*                                                                                                                  */
/* rba_EthUdp_ChangeParameter() By this API service the rba_EthUdp is requested to change a parameter of a socket   */
/*                                                                                                                  */
/* Parameter IN:                                                                                                    */
/*  SocketId_u16            - Socket identifier of the related local socket resource.                               */
/*  ParameterId_en          - Identifier of the parameter to be changed                                             */
/*  ParameterValue_u8       - Pointer to memory containing the new parameter value                                  */
/*                                                                                                                  */
/* Std_ReturnType       Result of operation                                                                         */
/*      E_OK                The parameter has been changed successfully                                             */
/*      E_NOT_OK            The parameter could not be changed.                                                     */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_ChangeParameter( VAR( TcpIp_SocketIdType, AUTOMATIC )                    SocketId_u16,
                                                                    VAR( TcpIp_ParamIdType, AUTOMATIC )                     ParameterId_en,
                                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )                  ParameterValue_pcu8 )
{
    /* Local Variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )        lRetValStdType_en;

    /* Report DET if rba_EthUdp is not initialized */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == rba_EthUdp_Config_pco ), RBA_ETHUDP_E_CHANGE_PARAMETER_API_ID, RBA_ETHUDP_E_NOTINIT, E_NOT_OK )

    /* Local Variable initialization */
    lRetValStdType_en = E_NOT_OK;

    if( ( TCPIP_PARAMID_FRAMEPRIO == ParameterId_en ) &&                                             /* Check whether the parameter to be changed is frame priority */
        ( RBA_ETHUDP_SOCK_CLOSED != (rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en) ) )       /* Check whether the requested socket is not closed         */
    {
        /* Report DET if frame priority value is not within the valid range */
        RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( *ParameterValue_pcu8 > TCPIP_FRAMEPRIO_MAXVAL ), RBA_ETHUDP_E_CHANGE_PARAMETER_API_ID, RBA_ETHUDP_E_INV_ARG, E_NOT_OK )

        /* Update frame priority value in the socket structure */
        rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8 = *ParameterValue_pcu8;

        lRetValStdType_en = E_OK;
    }

    return lRetValStdType_en;
}


#define RBA_ETHUDP_STOP_SEC_CODE
#include "rba_EthUdp_MemMap.h"

#endif /* ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */
