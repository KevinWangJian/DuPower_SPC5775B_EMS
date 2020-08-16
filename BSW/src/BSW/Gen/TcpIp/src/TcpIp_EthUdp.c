
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_UDP_ENABLED == STD_ON )
#include "rba_EthUdp.h"

#include "SoAd_Cbk.h"
#include "TcpIp_Prv.h"

#include "rba_BswSrv.h"

/********************************************************************************************************************************/
/* TcpIp_UdpTransmit()  - This service transmits data via UDP to a remote node. The transmission of the data is immediately     */
/*                        performed with this function call by forwarding it to EthIf.                                          */
/*                                                                                                                              */
/* Input Parameters :                                                                                                           */
/* SocketId             - Socket identifier of the related local socket resource.                                               */
/* DataPtr              - Pointer to a linear buffer of TotalLength bytes containing the data to be transmitted. In case DataPtr*/
/*                        is a NULL_PTR, TcpIp shall retrieve data from SoAd via callback SoAd_CopyTxData().                    */
/* RemoteAddrPtr        - IP address and port of the remote host to transmit to.                                                */
/* TotalLength          - Indicates the payload size of the UDP datagram.                                                       */
/*                                                                                                                              */
/* InOut Parameters :                                                                                                           */
/*                                                                                                                              */
/* Return value:                                                                                                                */
/* TcpIp_ReturnType    - TCPIP_OK: UDP message has been forwarded to EthIf for transmission.                                    */
/*                       TCPIP_E_NOT_OK: UDP message could not be sent because of a permanent error, e.g. message is too long.  */
/*                       TCPIP_E_ARP_CACHE_MISS: UDP message could not be sent because of an ARP cache miss, ARP request has    */
/*                       been sent and upper layer may retry transmission by calling this function later again.                 */
/********************************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( TcpIp_ReturnType, TCPIP_CODE ) TcpIp_UdpTransmit (
                                        VAR( TcpIp_SocketIdType, AUTOMATIC )                    SocketId,
                                        P2CONST( uint8, AUTOMATIC, AUTOMATIC )                  DataPtr,
                                        P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     RemoteAddrPtr,
                                        VAR( uint16, AUTOMATIC )                                TotalLength )
{
    /* Local variable declaration */
    P2VAR( uint8,                   AUTOMATIC, AUTOMATIC )     lBuffer_pu8;
    VAR( BufReq_ReturnType,                    AUTOMATIC )     lProvideTxBuffRetVal_en;
    VAR( TcpIp_ReturnType,                     AUTOMATIC )     lTcpIpRetVal_en;
    VAR( TcpIp_SocketIdType,                   AUTOMATIC )     lUdpSocIdx_u16;
    VAR( uint8,                                AUTOMATIC )     lBufIdx_u8;
    VAR( uint16,                               AUTOMATIC )     lPort_u16;
    VAR( uint32,                               AUTOMATIC )     lIPv4AddrHolder_u32;

    /* Local variable initialisation */
    lTcpIpRetVal_en             = TCPIP_OK;	/* Optimistic initialization; will be set to NOT_OK in case of invalid domain. */
    lProvideTxBuffRetVal_en     = BUFREQ_E_NOT_OK;
    lBuffer_pu8                 = NULL_PTR;
    lBufIdx_u8                  = 0xFFu;
    lPort_u16                   = 0;
    lIPv4AddrHolder_u32         = 0;

    /* Check for DET errors */
    /* Check whether TcpIp_Init() has been called or not */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_UDP_TRANSMIT_API_ID, TCPIP_E_NOTINIT, TCPIP_E_NOT_OK )

    /* Check whether socket Id is valid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( (TCPIP_UDP_SOCKET_OFFSET > SocketId) || (TCPIP_SOCKETMAX <= SocketId) ), TCPIP_E_UDP_TRANSMIT_API_ID, TCPIP_E_INV_ARG, TCPIP_E_NOT_OK )

    /* Check whether the RemoteAddrPtr is a null pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR ==  RemoteAddrPtr ),TCPIP_E_UDP_TRANSMIT_API_ID, TCPIP_E_NULL_PTR, TCPIP_E_NOT_OK )

    /* Retrieve the port number based on domain */
    switch(RemoteAddrPtr->domain)
    {
        #if (TCPIP_IPV4_ENABLED == STD_ON)
        case TCPIP_AF_INET:
			/* MR12 RULE 11.3, 11.8 VIOLATION: typecasted to TcpIp_SockAddrInetType* to match the local parameter Type definition */
            lPort_u16       	= ((TcpIp_SockAddrInetType*) RemoteAddrPtr)->port;
            /* lIPv4AddrHolder will hold the IPv4 address, as it is used in the rba_EthUdp_ProvideTxBuffer() function. */
			/* MR12 RULE 11.3, 11.8 VIOLATION: typecasted to TcpIp_SockAddrInetType* to match the local parameter Type definition */
            lIPv4AddrHolder_u32	= ((TcpIp_SockAddrInetType*) RemoteAddrPtr)->addr[0];
            break;
        #endif

        #if (TCPIP_IPV6_ENABLED == STD_ON)
        case TCPIP_AF_INET6:
			/* MR12 RULE 11.3, 11.8 VIOLATION: typecasted to TcpIp_SockAddrInet6Type* to match the local parameter Type definition */
            lPort_u16       	= ((TcpIp_SockAddrInet6Type*) RemoteAddrPtr)->port;
            /* lIPv4AddrHolder will be set to 0, as it is NOT used in IPv6 specific implementation (to keep the compatibility with rba_EthUdp_ProvideTxBuffer). */
            lIPv4AddrHolder_u32 = 0;
            break;
        #endif

        default:
            /* Unknown domain. Throw DET report and set invalid domain flag. */
            TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_UDP_TRANSMIT_API_ID, TCPIP_E_AFNOSUPPORT )

            lTcpIpRetVal_en = TCPIP_E_NOT_OK;
            break;
    }

    /* If domain is invalid, exit the function */
    if(lTcpIpRetVal_en == TCPIP_OK)
    {
	    /* Check whether the destination port is NULL */
	    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( 0 == lPort_u16 ),TCPIP_E_UDP_TRANSMIT_API_ID, TCPIP_E_INV_ARG, TCPIP_E_NOT_OK )

	    lUdpSocIdx_u16 = SocketId - TCPIP_UDP_SOCKET_OFFSET;       /* Udp API needs socket index to be zero based index */

	    /* Discard the transmission if message length is zero */
	    if( TotalLength > 0 )
	    {
	        /* Call lower layer API to allocate memory */
	        lProvideTxBuffRetVal_en = rba_EthUdp_ProvideTxBuffer(   lUdpSocIdx_u16,
	                                                                lIPv4AddrHolder_u32,
	                                                                &lBufIdx_u8,
	                                                                &lBuffer_pu8,
	                                                                &TotalLength );
	    }

	    /* Check whether lower layer has provided valid buffer */
	    if( BUFREQ_OK == lProvideTxBuffRetVal_en )
	    {
	        /* Copy the upper layer data into the buffer provided by lower layer */
	        if( NULL_PTR == DataPtr )
	        {
	            lProvideTxBuffRetVal_en = SoAd_CopyTxData( SocketId,                 /* For SoAd socket index shall be consecutive numbers of Tcp and udp socket index */
	                                                       lBuffer_pu8,
	                                                       TotalLength );
	        }
	        else
	        {
	            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
                (void)rba_BswSrv_MemCopy( lBuffer_pu8,
                                          DataPtr,
                                          TotalLength );

                lProvideTxBuffRetVal_en = BUFREQ_OK;
	        }

	        /* If copying of upper layer payload into the buffer is failed release the buffer */
	        if( BUFREQ_OK != lProvideTxBuffRetVal_en )
	        {
	            TotalLength = 0;
	        }

	        /* Call lower layer transmit API */
	        lTcpIpRetVal_en = rba_EthUdp_Transmit(  lUdpSocIdx_u16,
	                                                RemoteAddrPtr,
	                                                lBuffer_pu8,
	                                                lBufIdx_u8,
	                                                TotalLength );

        if( 0 == TotalLength)                      /* If SoAd_CopyTxData() failed, return TCPIP_E_NOT_OK */
	        {
	            lTcpIpRetVal_en = TCPIP_E_NOT_OK;
	        }
	    }
        else
        {
            lTcpIpRetVal_en = TCPIP_E_NOT_OK;   /* Provide Tx buffer API has failed; set return value to TCPIP_E_NOT_OK for the upper layer. */
        }
    }
	else
	{
		/* nothing to do. return error due to invalid domain */
	}

    return lTcpIpRetVal_en;
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"
#endif  /* TCPIP_UDP_ENABLED */

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

