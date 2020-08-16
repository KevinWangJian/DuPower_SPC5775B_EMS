
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_TCP_ENABLED == STD_ON )
#include "rba_EthTcp.h"
#endif

#if ( TCPIP_UDP_ENABLED == STD_ON )
#include "rba_EthUdp.h"
#endif

#include "TcpIp_Prv.h"

/*********************************************************************************************************************/
/*                                                                                                                   */
/* TcpIp_GetSocket() - By this API service the TCP/IP stack is requested to allocate a new socket.                   */
/*                        Note: Each accepted incoming TCP connection also allocates a socket resource.              */
/*                                                                                                                   */
/* Input Parameters :                                                                                                */
/* Domain              - IP address family.                                                                          */
/* Protocol            - Socket protocol as sub-family of parameter type.                                            */
/*                                                                                                                   */
/* Output Parameters :                                                                                               */
/* SocketIdPtr      - Pointer to socket identifier representing the requested socket. This socket identifier must be */
/*                    provided for all further API calls which requires a SocketId. Note: SocketIdPtr is only valid  */
/*                    if return value is E_OK.                                                                       */
/*                                                                                                                   */
/* Std_ReturnType     - E_OK or E_NOT_OK - Result of operation                                                       */
/*                                                                                                                   */
/*********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetSocket( VAR( TcpIp_DomainType,                AUTOMATIC )   Domain,
                                                    VAR( TcpIp_ProtocolType,              AUTOMATIC )   Protocol,
                                                    P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )   SocketIdPtr )
{
    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )              lRetVal_en;

    /* Initialise local variable */
    lRetVal_en      = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_GET_SOCKET_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if  Protocol is invalid. Only TCPIP_IPPROTO_TCP or TCPIP_IPPROTO_UDP are valid  */
    TCPIP_DET_REPORT_ERROR_RET_VALUE((( TCPIP_IPPROTO_TCP != Protocol ) && ( TCPIP_IPPROTO_UDP != Protocol )),         \
    		                         TCPIP_E_GET_SOCKET_API_ID, TCPIP_E_PROTOTYPE, E_NOT_OK )

    if( TCPIP_IPPROTO_TCP == Protocol )
    {
        #if ( TCPIP_TCP_ENABLED == STD_ON )
        lRetVal_en = rba_EthTcp_GetSocket(Domain, SocketIdPtr);
        #else
        /* Report DET if Protocol is not enabled. */
        TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_GET_SOCKET_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
        #endif

    }
    else if( TCPIP_IPPROTO_UDP == Protocol )
    {
        #if ( TCPIP_UDP_ENABLED == STD_ON )
        lRetVal_en = rba_EthUdp_GetSocket(Domain, SocketIdPtr);

        if(E_OK == lRetVal_en)
        {
            /* Offset shall be added to Udp socket index to give the feeling of single socket table being used for Tcp and Udp */
            (*SocketIdPtr) += TCPIP_UDP_SOCKET_OFFSET;
        }

        #else
        /* Report DET if Protocol is not enabled. */
        TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_GET_SOCKET_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
        #endif
    }
    else
    {  /* Do nothing */
    }

    return lRetVal_en;
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_Bind() - By this API service the TCP/IP stack is requested to bind a UDP or TCP socket to a local resource */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* SocketId         - Socket identifier of the related local socket resource.                                       */
/* LocalAddrId      - IP address identifier representing the local IP address and EthIf controller to bind the      */
/*                        socket to.                                                                                */
/* InOut Parameters :                                                                                               */
/* PortPtr             - Local port to which the socket shall be bound.                                             */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/* Std_ReturnType   - E_OK or E_NOT_OK - Result of operation                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_Bind(  VAR( TcpIp_SocketIdType,              AUTOMATIC )               SocketId,
                                                VAR( TcpIp_LocalAddrIdType,           AUTOMATIC )               LocalAddrId,
                                                P2VAR( uint16,             AUTOMATIC, AUTOMATIC )               PortPtr )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,                        AUTOMATIC )        lRetValStdType_en;


    /* Initialise local variables */
    lRetValStdType_en       = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_BIND_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if SocketId is not valid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( TCPIP_SOCKETMAX <= SocketId ), TCPIP_E_BIND_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if LocalAddrId is not valid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( (TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 <= LocalAddrId), TCPIP_E_BIND_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Check whether socket index is in Tcp socket range                                                                                          */
    /* (Tcp socket index range is 0 to TCPIP_UDP_SOCKET_OFFSET - 1 and Udp socket index range is TCPIP_UDP_SOCKET_OFFSET to TCPIP_SOCKETMAX - 1 ) */
    if(SocketId < TCPIP_TCPSOCKETMAX)
    {
#if ( TCPIP_TCP_ENABLED == STD_ON )
        lRetValStdType_en = rba_EthTcp_Bind( SocketId,
                                             LocalAddrId,
                                             PortPtr,
                                             TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId].TcpIpCtrlFramePrio_u8 );
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_BIND_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif
    }
    else
    {
#if ( TCPIP_UDP_ENABLED == STD_ON )
        lRetValStdType_en = rba_EthUdp_Bind( (SocketId - TCPIP_UDP_SOCKET_OFFSET),          /* Udp API needs socket index to be zero based index */
                                             LocalAddrId,
                                             PortPtr,
                                             TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId].TcpIpCtrlFramePrio_u8 );
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_BIND_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif
    }

    return lRetValStdType_en;

}


/********************************************************************************************************************/
/* TcpIp_Close -By this API service the TCP/IP stack is requested to close the socket and release all related resources*/
/* Input Parameters :                                                                                               */
/* SocketId             - Socket identifier of the related local socket resource.                                   */
/* Abort                - TRUE: Connection will immediately be terminated by sending a RST-Segment and releasing    */
/*                        all related resources.                                                                    */
/*                        FALSE: Connection will be terminated after performing a regular connection termination    */
/*                        handshake and releasing all related resources.                                            */
/*                        socket to.                                                                                */
/* Output Parameters :                                                                                              */
/* Std_ReturnType        - E_OK / E_NOT_OK - Result of operation                                                    */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_Close(    VAR( TcpIp_SocketIdType, AUTOMATIC )        SocketId,
                                                    VAR( boolean, AUTOMATIC )                   Abort )
{
    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )            lRetVal_en;

    /* Initialise local variables */
    lRetVal_en = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_CLOSE_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if SocketId is not less than the total number of sockets */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( TCPIP_SOCKETMAX <= SocketId ), TCPIP_E_CLOSE_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Check whether socket index is in Tcp socket range                                                                                          */
    /* (Tcp socket index range is 0 to TCPIP_UDP_SOCKET_OFFSET - 1 and Udp socket index range is TCPIP_UDP_SOCKET_OFFSET to TCPIP_SOCKETMAX - 1 ) */
    if(SocketId < TCPIP_TCPSOCKETMAX)
    {
#if ( TCPIP_TCP_ENABLED == STD_ON )
        lRetVal_en = rba_EthTcp_Close( SocketId, Abort  );
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_CLOSE_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif

    }
    else
    {
#if ( TCPIP_UDP_ENABLED == STD_ON )
        rba_EthUdp_Close( SocketId - TCPIP_UDP_SOCKET_OFFSET);                   /* Udp API needs socket index to be zero based index */
        lRetVal_en = E_OK;
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_CLOSE_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif

    }

    return lRetVal_en;
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

