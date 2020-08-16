

#ifndef RBA_ETHIPV4_PRV_H
#define RBA_ETHIPV4_PRV_H

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#define RBA_ETHIPV4_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

/* Pointer to IPv4 configuration structure */
extern CONSTP2CONST( rba_EthIPv4_CtrlCfg_tst, AUTOMATIC, AUTOMATIC ) * rba_EthIPv4_CtrlCfg_pcpcst;

#define RBA_ETHIPV4_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"
/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

#define     RBA_ETHIPV4_ADDR_ANY                        0x00000000UL     /* IP address ANY                          */

#define     RBA_ETHIPV4_LOOPBACK                        0x7F000000UL     /* Loopback address                        */

#define     RBA_ETHIPV4_LOOPBACK_MASK                   0xFF000000UL     /* Mask to check loop back IP              */

#define     RBA_ETHIPV4_RESERVED_IP                     0xF0000000UL     /* Reserved IP range 240.0.0.0/4           */

#define     RBA_ETHIPV4_IPV4_VERSION_NUM                0x4U             /* IPv4 version number used in IPv4 header */

#define     RBA_ETHIPV4_MORE_FRAG_FLAG                  0x2000U          /* More fragments flag                     */

#define     RBA_ETHIPV4_FRAG_OFFSET_MASK                 0x1fffU         /* Mask for fragmentation offset field     */

#define     RBA_ETHIPV4_TTL_VALUE                       0x01U            /* Default TimeToLive value                */

#define     RBA_ETHIPV4_TOS_VALUE                       0x00U            /* Default TypeOfService value             */

#define     RBA_ETHIPV4_MACADDR_LEN                     6U               /* Number of bytes in MAC address          */

#define     RBA_ETHIPV4_HIDDEN_HDR_LEN                  12U               /* Two bytes to store buffer length, one byte is required to store frame priority, six bytes to store destination MAC and */
                                                                          /*  an additional three bytes padding to make buffer word bounded */

#define     RBA_ETHIPV4_HIDDEN_HDR_FRAMEPRIO_OFFSET     2U                /* Position of frame priority within the hidden header section of the fragmentation buffer */

#define     RBA_ETHIPV4_HIDDEN_HDR_DSTMAC_OFFSET        3U                /* Position of destination MAC within the hidden header section of the fragmentation buffer */

#define     RBA_ETHIPV4_INVALID_REASSEMBLY_HOLEPOS      0xffffU

/* IPv4 header fields */
#define     RBA_ETHIPV4_IPV4VER_HDRLEN_TOS_UB           0U               /* Position of upper byte of version number, HeaderLength and TypeOfService in IPv4 header */
#define     RBA_ETHIPV4_TOTLEN_UB                       2U               /* Position of upper byte of IPv4 datagram length in IPv4 header                           */
#define     RBA_ETHIPV4_FRAGID_UB                       4U               /* Position of upper byte of fragmentation identifier in IPv4 header                       */
#define     RBA_ETHIPV4_FRAGOFFSET_UB                   6U               /* Position of upper byte of fragmentation offset in IPv4 header                           */
#define     RBA_ETHIPV4_TTL_OFFSET                      8U               /* Position of TimeToLive value in IPv4 header                                             */
#define     RBA_ETHIPV4_IPHDRCHECKSUM_UB                10U              /* Position of upper byte of IPv4 header checksum in IPv4 header                           */
#define     RBA_ETHIPV4_MORE_FRAGMENT_FLAG_POS          13U              /* Position of more fragment bit within word comprising of bytes 7 and 8 of IPV4 header    */


#define RBA_ETHIPV4_START_SEC_VAR_INIT_16
#include "rba_EthIPv4_MemMap.h"
extern VAR( uint16, RBA_ETHIPV4_VAR )                   rba_EthIPv4_FragID_u16;
#define RBA_ETHIPV4_STOP_SEC_VAR_INIT_16
#include "rba_EthIPv4_MemMap.h"

/* Development Error Codes for DET Support   */
#define RBA_ETHIPV4_E_NOTINIT                                 TCPIP_E_NOTINIT       /* API service used without rba_EthIPv4_Init module initialisation */
#define RBA_ETHIPV4_E_INV_ARG                                 TCPIP_E_INV_ARG       /* Invalid argument received                                       */
#define RBA_ETHIPV4_E_NULL_PTR                                TCPIP_E_NULL_PTR      /* API service called with NULL pointer as an argument             */
#define RBA_ETHIPV4_E_INIT_FAILED                             TCPIP_E_INIT_FAILED   /* API service called without TcpIp module initialization          */
#define RBA_ETHIPV4_E_MSGSIZE                                 TCPIP_E_MSGSIZE       /* Message too long */
#define RBA_ETHIPV4_E_BUFRELEASE_FAILED                       0xF0u                 /* API rba_EthIPv4_FragBufHandler() failed to release the buffer.  */

/* API IDs used to report DET error */
#define RBA_ETHIPV4_E_INIT_API_ID                            (0x01U)               /* API ID for rba_EthIPv4_Init()                      */
#define RBA_ETHIPV4_E_GET_IPMULTICAST_DESTETHADDR_API_ID     (0x02U)               /* API ID for rba_EthIPv4_GetIPMulticastDestEthAddr() */
#define RBA_ETHIPV4_E_PROVIDE_TXBUFFER_API_ID                (0x03U)               /* API ID for rba_EthIPv4_ProvideTxBuffer()           */
#define RBA_ETHIPV4_E_TRANSMIT_API_ID                        (0x04U)               /* API ID for rba_EthIPv4_Transmit()                  */
#define RBA_ETHIPV4_E_RX_INDICATION_API_ID                   (0x05U)               /* API ID for rba_EthIPv4_RxIndication()              */
#define RBA_ETHIPV4_E_CHK_IPV4ADDR_TYPE_API_ID               (0x07U)               /* API ID for rba_EthIPv4_ChkIPv4AddrType()           */
#define RBA_ETHIPV4_E_FRAGBUFHANDLER_API_ID                  (0x08U)               /* API ID for rba_EthIPv4_FragBufHandler()            */
#define RBA_ETHIPV4_E_VALIDATE_RXFRAME_API_ID                (0x09U)               /* API ID for rba_EthIPv4_ValidateRxFrame()           */
#define RBA_ETHIPV4_E_MAIN_FUNCTION_API_ID                   (0x0AU)               /* API ID for rba_EthIPv4_MainFunction()              */

/* Compiler switch for rba_EthIPv4_UpdateTPLayerChkSum() */
/* rba_EthIPv4_UpdateTPLayerChkSum() shall be available if software checksum offload needs to be done for Udp/Icmp or fragmentation is enabled */
#define RBA_ETHIPV4_UPDATE_TPLAYERCHKSUM_ENABLED             ( ((TCPIP_UDP_ENABLED ==  STD_ON) && (RBA_ETHIPV4_SW_CHKSUM_TX_UDP == STD_ON)) ||    \
                                                               ((TCPIP_ICMP_ENABLED == STD_ON) && (RBA_ETHIPV4_SW_CHKSUM_TX_ICMP == STD_ON)) ||   \
                                                               (RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) )

/* Compiler switch for rba_EthIPv4_VerifyTPLayerChkSum() */
/* rba_EthIPv4_VerifyTPLayerChkSum() shall be available if software checksum verification needs to be done for Udp/Icmp or reassembly is enabled */
#define RBA_ETHIPV4_VERIFY_TPLAYERCHKSUM_ENABLED             ( ((TCPIP_UDP_ENABLED ==  STD_ON) && (RBA_ETHIPV4_SW_CHKSUM_RX_UDP == STD_ON)) ||    \
                                                               ((TCPIP_ICMP_ENABLED == STD_ON) && (RBA_ETHIPV4_SW_CHKSUM_RX_ICMP == STD_ON)) ||   \
                                                               (RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) )


#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )

    /* DET For functions with return type as 'void' */
    #define RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                      \
            if( CONDITION )                                                                                   \
            {                                                                                                 \
                (void)Det_ReportError( (RBA_ETHIPV4_MODULE_ID), (RBA_ETHIPV4_INSTANCE_ID), (API), (ERROR) );  \
                return;                                                                                       \
            }

    /* For functions with a return value */
    #define RBA_ETHIPV4_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )                           \
            if( CONDITION )                                                                                   \
            {                                                                                                 \
                (void)Det_ReportError( (RBA_ETHIPV4_MODULE_ID), (RBA_ETHIPV4_INSTANCE_ID), (API), (ERROR) );  \
                return ( RETVAL );                                                                            \
            }

     /*  Macro For functions to report DET but does not return to calling function */
     #define RBA_ETHIPV4_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )                                     \
            if( CONDITION )                                                                                  \
            {                                                                                                \
                (void)Det_ReportError( (RBA_ETHIPV4_MODULE_ID), (RBA_ETHIPV4_INSTANCE_ID), (API), (ERROR) ); \
            }

    /*  Macro for functions to report DET always, and returns to calling function */
    #define RBA_ETHIPV4_DET_REPORT_ERROR_TRUE_RET_VOID( API, ERROR)                                       \
         {                                                                                                \
            (void)Det_ReportError( (RBA_ETHIPV4_MODULE_ID), (RBA_ETHIPV4_INSTANCE_ID), (API), (ERROR) );  \
            return;                                                                                       \
         }

#else
    #define RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( CONDITION, API, ERROR )

    #define RBA_ETHIPV4_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )

    #define RBA_ETHIPV4_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )

    #define RBA_ETHIPV4_DET_REPORT_ERROR_TRUE_RET_VOID( API, ERROR)

#endif /* #if TCPIP_DEV_ERROR_DETECT */

/* This structure contains information needs to be filled in IPv4 header during rba_EthIPv4_Transmit() call */
typedef struct
{
    VAR( TcpIp_ProtocolType,    AUTOMATIC )     ProtoType_en;          /* Transport layer protocol                                            */
    VAR( uint32,                AUTOMATIC )     SrcIp_u32;             /* Source IP to be present in the transmitted frame                    */
    VAR( uint32,                AUTOMATIC )     DstIp_u32;             /* Destination IP to be present in the transmitted frame               */
    VAR( uint16,                AUTOMATIC )     TotalLen_u16;          /* Value of the total length field in the frame to be transmitted      */
    VAR( uint16,                AUTOMATIC )     FragId_u16;             /* Value of fragmentation Id in the frame to be transmitted            */
    VAR( uint16,                AUTOMATIC )     FragFlagOffset_u16;    /* Byte 6 and 7 of the IPv4 header - Flags and fragmentation offset    */
    VAR( uint8,                AUTOMATIC )      TTL_u8;                /* TTL value to be present in the transmitted frame                    */
}rba_EthIPv4_HdrFields_tst;

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHIPV4_PRV_H */
