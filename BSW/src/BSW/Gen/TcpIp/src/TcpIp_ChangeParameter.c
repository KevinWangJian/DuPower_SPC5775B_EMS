

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_TCP_ENABLED == STD_ON )
#include "rba_EthTcp.h"
#endif

#if ( TCPIP_UDP_ENABLED == STD_ON )
#include "rba_EthUdp.h"
#endif

#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_ChangeParameter() By this API service the TCP/IP stack is requested to change a parameter of a socket.     */
/*                          E.g. the Nagle algorithm may be controlled by this API.                                 */
/*                                                                                                                  */
/* Parameter IN:                                                                                                    */
/*  SocketId            - Socket identifier of the related local socket resource.                                   */
/*  ParameterId          - Identifier of the parameter to be changed                                                */
/*  ParameterValue      - Pointer to memory containing the new parameter value                                      */
/*                                                                                                                  */
/* Std_ReturnType       Result of operation                                                                         */
/*      E_OK                The parameter has been changed successfully                                             */
/*      E_NOT_OK            The parameter could not be changed.                                                     */
/*                                                                                                                  */
/********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_ChangeParameter(
                                    VAR( TcpIp_SocketIdType, AUTOMATIC )                    SocketId,
                                    VAR( TcpIp_ParamIdType, AUTOMATIC )                     ParameterId,
                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )                  ParameterValue )
{
    /* Local Variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )        lRetValStdType_en;

    /* Local Variable initialization */
    lRetValStdType_en = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_CHANGE_PARAMETER_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if ParameterValue is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == ParameterValue ), TCPIP_E_CHANGE_PARAMETER_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if SocketId is not valid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( SocketId >= TCPIP_SOCKETMAX  ), TCPIP_E_CHANGE_PARAMETER_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Check whether socket index is in Tcp socket range                                                                                          */
    /* (Tcp socket index range is 0 to TCPIP_UDP_SOCKET_OFFSET - 1 and Udp socket index range is TCPIP_UDP_SOCKET_OFFSET to TCPIP_SOCKETMAX - 1 ) */
    if(SocketId < TCPIP_UDP_SOCKET_OFFSET)
    {
#if ( TCPIP_TCP_ENABLED == STD_ON )
        lRetValStdType_en = rba_EthTcp_ChangeParameter( SocketId,
                                                        ParameterId,
                                                        ParameterValue );
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_CHANGE_PARAMETER_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif

    }
    else
    {
#if ( TCPIP_UDP_ENABLED == STD_ON )
        lRetValStdType_en = rba_EthUdp_ChangeParameter( (SocketId - TCPIP_UDP_SOCKET_OFFSET),    /* Udp API needs socket index to be zero based index */
                                                        ParameterId,
                                                        ParameterValue );
#else
/* Report DET if Protocol is not enabled. */
TCPIP_DET_REPORT_ERROR_RET_VALUE(TRUE, TCPIP_E_CHANGE_PARAMETER_API_ID, TCPIP_E_NOPROTOOPT, E_NOT_OK)
#endif

    }

    return( lRetValStdType_en );
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"
#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

