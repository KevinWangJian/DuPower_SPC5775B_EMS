

#ifndef RBA_ETHUDP_PRV_H
#define RBA_ETHUDP_PRV_H

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*
 ***************************************************************************************************
 * Global variable declaration
 ***************************************************************************************************
 */
#define RBA_ETHUDP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

extern P2CONST( rba_EthUdp_Config_to, AUTOMATIC, AUTOMATIC )    rba_EthUdp_Config_pco;   /* Pointer will be initialized in the Init Function */
extern VAR( uint16,                              AUTOMATIC )    rba_EthUdp_UsedSocCnt_u16;
extern VAR( uint16,                              AUTOMATIC )    rba_EthUdp_PortAny_u16;

#define RBA_ETHUDP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

/* In UDP header datagram length upper byte offset */
#define     RBA_ETHUDP_UDPFRAMELENGTH_UB        4U

/* In UDP header datagram length lower byte offset */
#define     RBA_ETHUDP_UDPFRAMELENGTH_LB        5U

/* In UDP header checksum upper byte offset */
#define     RBA_ETHUDP_UDPCHKSUM_UB             6U

/* In UDP header checksum lower byte offset */
#define     RBA_ETHUDP_UDPCHKSUM_LB             7U


/*********************************************/
/* Development Error Codes for DET Support   */
/*********************************************/

/*RBA_ETHUDP_E_NOTINIT: API service used without rba_EthUdp_Init module initialisation */
#define RBA_ETHUDP_E_NOTINIT                        TCPIP_E_NOTINIT

/* RBA_ETHUDP_E_INV_ARG: Invalid argument received */
#define RBA_ETHUDP_E_INV_ARG                        TCPIP_E_INV_ARG

/* RBA_ETHUDP_E_NULL_PTR: API service called with NULL pointer as an argument */
#define RBA_ETHUDP_E_NULL_PTR                       TCPIP_E_NULL_PTR

/* RBA_ETHUDP_E_INIT_FAILED: API service called without TcpIp module initialization */
#define RBA_ETHUDP_E_INIT_FAILED                   TCPIP_E_INIT_FAILED

/* RBA_ETHUDP_E_AFNOSUPPORT: Address family not supported by protocol family */
#define RBA_ETHUDP_E_AFNOSUPPORT                   TCPIP_E_AFNOSUPPORT

/* RBA_ETHUDP_E_ADDRNOTAVAIL: Can't assign requested address */
#define RBA_ETHUDP_E_ADDRNOTAVAIL                  TCPIP_E_ADDRNOTAVAIL

/* RBA_ETHUDP_E_ADDRINUSE: Address already in use */
#define RBA_ETHUDP_E_ADDRINUSE                     TCPIP_E_ADDRINUSE

/* RBA_ETHUDP_E_NOPROTOOPT: Protocol not available */
#define RBA_ETHUDP_E_NOPROTOOPT					   TCPIP_E_NOPROTOOPT

/* RBA_ETHUDP_E_ZERO_CHECKSUM_IPV6: Checksum fied in the UDP header for an IPv6 packet is zero */
#define RBA_ETHUDP_E_ZERO_CHECKSUM_IPV6           (0x10)    /* Continue numbering from last value for Development Error Codes in TcpIp: 0x0FU */


/*********************************************/
/* DET macros                                */
/*********************************************/

/* API IDs of rba_EthUdp */

/* Indicates the Api Id passed in the call of Det_ReportError */

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_Init()  */
#define RBA_ETHUDP_E_INIT_API_ID                                  (0x01U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_ProvideTxBuffer()  */
#define RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID                      (0x02U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_Transmit()  */
#define RBA_ETHUDP_E_TRANSMIT_API_ID                              (0x03U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_RxIndication() */
#define RBA_ETHUDP_E_RX_INDICATION_API_ID                         (0x04U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_GetSocket() */
#define RBA_ETHUDP_E_GET_SOCKET_API_ID                            (0x05U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_Bind() */
#define RBA_ETHUDP_E_BIND_API_ID                                  (0x06U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_ChangeParameter() */
#define RBA_ETHUDP_E_CHANGE_PARAMETER_API_ID                      (0x07U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_TerminateSocUsingLocalAddr() */
#define RBA_ETHUDP_E_TERMINATE_SOC_USING_LOCALADDR_API_ID         (0x08U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthUdp_Close() */
#define RBA_ETHUDP_E_CLOSE_API_ID                                 (0x09U)


#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )

    /* DET For functions with return type as 'void' */
    #define RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                     \
            if( CONDITION )                                                                                 \
            {                                                                                               \
                (void)Det_ReportError( (RBA_ETHUDP_MODULE_ID), (RBA_ETHUDP_INSTANCE_ID), (API), (ERROR) ) ; \
                return;                                                                                     \
            }

    /* For functions with a return value */
    #define RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )                          \
            if( CONDITION )                                                                                 \
            {                                                                                               \
                (void)Det_ReportError( (RBA_ETHUDP_MODULE_ID), (RBA_ETHUDP_INSTANCE_ID), (API), (ERROR) ) ; \
                return ( RETVAL );                                                                          \
            }

    /*  Macro For functions to report DET but does not return to calling function */
    #define RBA_ETHUDP_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )                                      \
        if( CONDITION )                                                                                     \
        {                                                                                                   \
            (void)Det_ReportError( (RBA_ETHUDP_MODULE_ID), (RBA_ETHUDP_INSTANCE_ID), (API), (ERROR) );      \
        }

    /*  Macro for functions to report DET always, but does not return to calling function */
    #define RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( API, ERROR )                                         \
            (void)Det_ReportError( (RBA_ETHUDP_MODULE_ID), (RBA_ETHUDP_INSTANCE_ID), (API), (ERROR) );    \

    /*  Macro for functions to report DET always, and returns to calling function */
    #define RBA_ETHUDP_DET_REPORT_ERROR_TRUE_RET_VALUE( API, ERROR, RETVAL )                              \
         {                                                                                                \
            (void)Det_ReportError( (RBA_ETHUDP_MODULE_ID), (RBA_ETHUDP_INSTANCE_ID), (API), (ERROR) );    \
            return ( RETVAL );                                                                            \
         }

#else
    #define RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( CONDITION, API, ERROR )

    #define RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )

    #define RBA_ETHUDP_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )

    #define RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( API, ERROR )

    #define RBA_ETHUDP_DET_REPORT_ERROR_TRUE_RET_VALUE( API, ERROR, RETVAL )

#endif /* #if TCPIP_DEV_ERROR_DETECT */

#endif  /* ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHUDP_PRV_H */
