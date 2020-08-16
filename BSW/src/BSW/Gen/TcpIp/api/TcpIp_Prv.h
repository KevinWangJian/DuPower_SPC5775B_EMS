

#ifndef TCPIP_PRV_H
#define TCPIP_PRV_H

#include "TcpIp_Cfg.h"
#ifdef TCPIP_CONFIGURED

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/* DHCP Client port number defined by IANA */
#define TCPIP_DHCPSERVER_PORT				67U

/* DHCP Server port number defined by IANA */
#define TCPIP_DHCPCLIENT_PORT				68U

/* Source port offset in Transport Protocol header */
#define TCPIP_TP_SRCPORT_OFFSET				0U

/* Destination port offset in Transport Protocol header*/
#define TCPIP_TP_DESTPORT_OFFSET			2U

/* Offset to be added to Udp socket index to give the feeling of single socket table being used for Tcp and Udp */
#define TCPIP_UDP_SOCKET_OFFSET                TCPIP_TCPSOCKETMAX

/* 169.254.0.0 */
#define TCPIP_AUTOIP_NET         			    0xA9FE0000UL

/* 169.254.1.0 */
#define TCPIP_AUTOIP_RANGE_START 			    ( TCPIP_AUTOIP_NET | 0x0100U )

/* 169.254.254.255 */
#define TCPIP_AUTOIP_RANGE_END   			    ( TCPIP_AUTOIP_NET | 0xFEFFU )

/* 169.254.255.255 */
#define TCPIP_AUTOIP_BROADCAST   			0xA9FEFFFFUL

/* Mask to check AutoIp range */
#define TCPIP_AUTOIP_MASK					0xFFFF0000UL

#define TCPIP_NETMASK_MAX_VAL				32U

/* IP address ANY */
#define     TCPIP_IPV4_ADDR_ANY							0x00000000UL

/* Loopback address */
#define     TCPIP_IPV4_LOOPBACK                        	0x7F000000UL

/* Mask to check loop back IP */
#define     TCPIP_IPV4_LOOPBACK_MASK                   	0xFF000000UL

/* Reserved IP range 240.0.0.0/4 */
#define     TCPIP_IPV4_RESERVED_IP                     	0xF0000000UL

/* IPv6 generic multicast address mask (RFC 4291 - Section 2.7) */
#define 	TCPIP_IPV6_MULTICAST_MASK					0xFF000000uL

/* IPv6 multicast SCOP flag mask (RFC 4291 - Section 2.7)  */
#define 	TCPIP_IPV6_MULTICAST_SCOP_FLAG_MASK			0xFF0F0000uL

/* Reserved Multicast IPv6 addresses, based on the SCOP flag (RFC 4291 - Section 2.7) */
#define 	TCPIP_IPV6_MULTICAST_RESERVED_SCOP_0		0xFF000000uL
#define 	TCPIP_IPV6_MULTICAST_RESERVED_SCOP_3		0xFF030000uL
#define 	TCPIP_IPV6_MULTICAST_RESERVED_SCOP_F		0xFF0F0000uL

/* CallBack required or not */
#define TCPIP_CBK_NOT_REQD					0x00U
#define TCPIP_CBK_REQD						0xFFU

/* Checksum field offset */
#define TCPIP_UDPFRAMELENGTH_UB             4U
#define TCPIP_UDPCHKSUM_UB                  6U
#define TCPIP_TCPCHKSUM_UB                  16U
#define TCPIP_ICMPCHKSUM_UB                 2U
#define TCPIP_UDPHDRLENGTH                  8U

#define TCPIP_MAXUINT32						(0xFFFFFFFFUL)
#define TCPIP_MINUINT32						(0x0UL)

/* FramePrio is a 3 bit field in Vlan header, it's maximun value is 7 */
#define TCPIP_FRAMEPRIO_MAXVAL				7U

/* API IDs of TcpIp */

/* Indicates that Api Id passed in the call of Det_ReportError */

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_Init()  */
#define TCPIP_E_INIT_API_ID                                       (0x01U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetVersionInfo()  */
#define TCPIP_E_GET_VERSIONINFO_API_ID                            (0x02U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetSocket() */
#define TCPIP_E_GET_SOCKET_API_ID  						          (0x03U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_Close() */
#define TCPIP_E_CLOSE_API_ID  					                  (0x04U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_Bind() */
#define TCPIP_E_BIND_API_ID  				                      (0x05U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_TcpConnect()  */
#define TCPIP_E_TCP_CONNECT_API_ID  			                  (0x06U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_TcpListen()     */
#define TCPIP_E_TCP_LISTEN_API_ID   		                      (0x07U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_TcpReceived()  */
#define TCPIP_E_TCP_RECEIVED_API_ID  	                          (0x08U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_RequestComMode()  */
#define TCPIP_E_REQUEST_COM_MODE_API_ID  	                      (0x09U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_RequestIpAddrAssignment()   */
#define TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID  	              (0x0AU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ReleaseIpAddrAssignment()   */
#define TCPIP_E_RELEASE_IP_ADDRASSIGNMENT_API_ID  	              (0x0BU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_IcmpTransmit()    */
#define TCPIP_E_ICMP_TRANSMIT_API_ID  	                          (0x0CU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_DhcpReadOption()   */
#define TCPIP_E_DHCP_READOPTION_API_ID                            (0x0DU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_DhcpWriteOption()   */
#define TCPIP_E_DHCP_WRITEOPTION_API_ID                           (0x0EU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ChangeParameter()   */
#define TCPIP_E_CHANGE_PARAMETER_API_ID                           (0x0FU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetIpAddr()   */
#define TCPIP_E_GET_IPADDR_API_ID                                 (0x10U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetPhysAddr()   */
#define TCPIP_E_GET_PHYSADDR_API_ID                               (0x11U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_UdpTransmit()   */
#define TCPIP_E_UDP_TRANSMIT_API_ID                               (0x12U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_TcpTransmit()   */
#define TCPIP_E_TCP_TRANSMIT_API_ID                               (0x13U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_RxIndication()   */
#define TCPIP_E_RXINDICATION_API_ID                               (0x14U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_MainFunction()   */
#define TCPIP_E_MAIN_FUNCTION_API_ID                              (0x15U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetCtrlIdx()     */
#define TCPIP_E_GET_CTRLIDX_API_ID                                (0x17U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_AllocBaseIpAddr()   */
#define TCPIP_E_ALLOC_BASE_IPADDR_API_ID                          (0x18U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ReadArpTable()   */
#define TCPIP_E_READ_ARPTABLE_API_ID                              (0x19U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_OnesComplChkSum()  */
#define TCPIP_E_ONES_COMPL_CHKSUM_API_ID                          (0x1AU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_LocalIpAddrAssignmentChg()  */
#define TCPIP_E_LOCAL_IP_ADDRASSIGNMENTCHG_API_ID                 (0x1BU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_SubnetMskChkRemoteIpAddr() */
#define TCPIP_E_SUBNETMSK_CHK_REMOTEIPADDR_API_ID                 (0x21U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ChkComAllowed() */
#define TCPIP_E_CHK_COMALLOWED_API_ID                             (0x22U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetIPAddrAsgnMethFrmCrtlIdx() */
#define TCPIP_E_GET_IPADDR_ASGNMETH_FRM_CRTLIDX_API_ID            (0x28U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetIPv4AddrFrmCtrlIdx() */
#define TCPIP_E_GET_IPV4ADDR_FRM_CTRLIDX_API_ID                   (0x2CU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetLocalAddrIdForRxFrame() */
#define TCPIP_E_GET_LOCALADDRID_FOR_RXFRAME_API_ID                (0x2DU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_CheckValidityOfLocalAddrId() */
#define TCPIP_E_CHECK_VALIDITY_OF_LOCALADDRID_API_ID              (0x2FU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ReadU16() */
#define TCPIP_E_READ_U16_API_ID                                   (0x32U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_ReadU32() */
#define TCPIP_E_READ_U32_API_ID                                   (0x33U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_WriteU16() */
#define TCPIP_E_WRITE_U16_API_ID                                  (0x34U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_WriteU32() */
#define TCPIP_E_WRITE_U32_API_ID                                  (0x35U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetFramePrioFrmLocalAddrId() */
#define TCPIP_E_GET_FRAMEPRIO_FRM_LOCALADDRID_API_ID              (0x36U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_StateMachine()   */
#define TCPIP_E_STATE_MACHINE_API_ID  	              			  (0x37U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_InitiateIpAssgn()   */
#define TCPIP_E_INITIATE_IP_ASSGN_API_ID  	              		  (0x38U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_GetLocalAddrIdProperties()   */
#define TCPIP_E_GET_LOCALADDRID_PROPERTIES_API_ID                 (0x39U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_IPv6AddrCompareWithMask() */
#define TCPIP_E_IPV6_ADDR_COMPARE_WITH_MASK_API_ID				  (0x40U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_IsIPv6AddrEqualToNetworkAddr() */
#define TCPIP_E_IS_IPV6_ADDR_EQUAL_TO_NETWORK_ADDR_ID             (0x41U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to TcpIp_UpdateMulticastPhysFilter() */
#define TCPIP_E_UPDATE_MULTICAST_PHYS_FILTER_ADDR_ID             (0x42U)

#define TCPIP_E_NOTINIT							0x01U       /* API service called before initializing the module */
#define TCPIP_E_NULL_PTR						0x02U       /* API service called with NULL pointer */
#define TCPIP_E_INV_ARG							0x03U       /* Invalid argument */
#define TCPIP_E_NOBUFS							0x04U       /* No buffer space available */
#define TCPIP_E_INV_SOCKADDR					0x05U       /* Invalid socket address */
#define TCPIP_E_DESTADDRREQ						0x06U       /* Destination address required */
#define TCPIP_E_MSGSIZE							0x07U       /* Message too long */
#define TCPIP_E_PROTOTYPE						0x08U       /* Protocol wrong type for socket */
#define TCPIP_E_ADDRINUSE						0x09U       /* Address already in use */
#define TCPIP_E_ADDRNOTAVAIL					0x0AU       /* Can't assign requested address */
#define TCPIP_E_ISCONN							0x0BU       /* Socket is already connected */
#define TCPIP_E_NOTCONN							0x0CU       /* Socket is not connected */
#define TCPIP_E_NOPROTOOPT						0x0DU       /* Protocol not available */
#define TCPIP_E_AFNOSUPPORT						0x0EU       /* Address family not supported by protocol family */
#define TCPIP_E_INIT_FAILED                     0x0FU       /* Invalid configuration set selection */

#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )

    /* DET Macro for functions with return type as 'void' */
    #define TCPIP_DET_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                  \
		    if( CONDITION )                                                                         \
		    {                                                                                       \
		   	    (void)Det_ReportError( (TCPIP_MODULE_ID), (TCPIP_INSTANCE_ID), (API), (ERROR) ) ;   \
			    return;                                                                             \
            }

    /* DET Macro for functions with a return value */
    #define TCPIP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )                       \
            if( CONDITION )                                                                 	    \
            {                                                                               	    \
                (void)Det_ReportError( (TCPIP_MODULE_ID), (TCPIP_INSTANCE_ID), (API), (ERROR) ) ; 	\
                return ( RETVAL );                                                                  \
            }

	/*  Macro For functions to report DET but does not return to calling function */
    #define TCPIP_DET_REPORT_ERROR_NO_RET( CONDITION, API, ERROR )                                  \
			if( CONDITION )                                                                         \
			{                                                                                       \
				(void)Det_ReportError( (TCPIP_MODULE_ID), (TCPIP_INSTANCE_ID), (API), (ERROR) );    \
			}

    /*  Macro for functions to report DET always, but does not return to calling function */
    #define TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( API, ERROR )                                        \
                (void)Det_ReportError( (TCPIP_MODULE_ID), (TCPIP_INSTANCE_ID), (API), (ERROR) );    \


#else
    #define TCPIP_DET_REPORT_ERROR_RET_VOID( CONDITION, API, ERROR )

    #define TCPIP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )

	#define TCPIP_DET_REPORT_ERROR_NO_RET( CONDITION, API, ERROR )

    #define TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( API, ERROR )

#endif /* #if TCPIP_DEV_ERROR_DETECT */


#define TCPIP_START_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"
extern P2CONST( TcpIp_ConfigType, TCPIP_VAR, TCPIP_VAR )			TcpIp_CurrConfig_pco;
#define TCPIP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_VAR_INIT_8
#include "TcpIp_MemMap.h"
extern VAR( boolean, 	TCPIP_VAR )									TcpIp_InitFlag_b;
#define TCPIP_STOP_SEC_VAR_INIT_8
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_VAR_INIT_32
#include "TcpIp_MemMap.h"
extern VAR( uint32,     TCPIP_VAR )                                TcpIp_RandNumSeed1_u32;
extern VAR( uint32,     TCPIP_VAR )                                TcpIp_RandNumSeed2_u32;
#define TCPIP_STOP_SEC_VAR_INIT_32
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_CheckValidityOfLocalAddrId( VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) LocalAddrId_u8 );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetFramePrioFrmLocalAddrId(
                                                        VAR( TcpIp_LocalAddrIdType, AUTOMATIC )     LocalAddrId_u8,
                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        FramePrio_pu8 );


extern FUNC( TcpIp_StateType, TCPIP_CODE ) TcpIp_GetEthIfCtrlState(	VAR( uint8, AUTOMATIC )			EthIfCtrlIdx_u8	);


extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetIPv4AddrFrmCtrlIdx(
													VAR( uint8, AUTOMATIC )							EthIfCtrlIdx_u8 ,
													P2VAR( uint32, AUTOMATIC, AUTOMATIC )   		SrcIPv4Addr_pu32,
													P2VAR( uint32, AUTOMATIC, AUTOMATIC )			NetMask_pu32 );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetIPAddrAsgnMethFrmCrtlIdx(
													VAR( uint8, AUTOMATIC )							EthIfCtrlIdx_u8 ,
													P2VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC, AUTOMATIC )   	IpAddrAsgnMethType_pen );

extern FUNC( void, TCPIP_CODE )     TcpIp_StateMachine( void );


extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_SubnetMskChkRemoteIpAddr(
														VAR( uint8, AUTOMATIC )						EthIfCtrlIdx_u8,
														VAR( uint32, AUTOMATIC )					RemoteIPv4Addr_u32,
										P2VAR( TcpIp_IPv4AddrType_ten, AUTOMATIC, AUTOMATIC ) 		IPv4AddrType_pen );


extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetLocalAddrIdForRxFrame(
                                                      VAR( uint8, AUTOMATIC )                               EthIfCtrlIdx_u8,
                                                      VAR( uint32, AUTOMATIC )                              IPv4Addr_u32,
                                                      P2VAR( TcpIp_LocalAddrIdType, AUTOMATIC, AUTOMATIC )  LocalAddrId_pu8 );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_ChkComAllowed( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  LocalAddrId_u8 );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetLocalAddrIdProperties(
                                                    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                          LocalAddrId_u8,
                                                    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )        *TcpIp_LocalAddrConfig_ppcst );

extern FUNC( void, TCPIP_CODE ) TcpIp_InitiateIpAssgn( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId_u8 );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_UpdateMulticastPhysFilter( P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )	LocalAddrConfig_pcst,
																		   VAR( Eth_FilterActionType, AUTOMATIC )						FilterActionType_en );

#if (TCPIP_IPV6_ENABLED == STD_ON)
extern FUNC( boolean, TCPIP_CODE ) TcpIp_IPv6AddrCompareWithMask(
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )		IPv6Addr1_pcu32,
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )		IPv6Addr2_pcu32,
                                        VAR( uint8, AUTOMATIC )                 	Netmask_u8 );

extern FUNC( boolean, TCPIP_CODE ) TcpIp_IsIPv6AddrEqualToNetworkAddr(
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )		IPv6Addr_pcu32,
                                        VAR( uint8, AUTOMATIC )                 	Netmask_u8 );
#endif

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"
#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_PRV_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
