

#ifndef SOAD_PRV_H
#define SOAD_PRV_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComStack_Types.h"
#include "SoAd.h"
#include "SoAd_Prv_Domain.h"
#include "Det.h"

/**************************************************************************************************/
/*  Common Published Information                                                                  */
/**************************************************************************************************/

/****************************************************************************************************************
**                                   External Variables Declarations                                           **
****************************************************************************************************************/
#if ( SOAD_NUM_TX_IF_UDP_PDU > 0 )
#define SOAD_START_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"

extern VAR(boolean, SOAD_VAR) SoAd_ULIfUdpTxConfirmFlag_ab[];

#define SOAD_STOP_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"
#endif /* SOAD_NUM_TX_IF_UDP_PDU > 0 */

#define SOAD_START_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"
extern VAR(boolean, AUTOMATIC) SoAd_InitFlag_b;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
extern VAR(Std_ReturnType, AUTOMATIC) SoAd_DetErrFlag_u8;
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF  */

#define SOAD_STOP_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"
extern VAR(TcpIp_IpAddrStateType, SOAD_VAR) SoAd_LocalAddrIdx_State_aen[];
extern VAR(SoAd_SoConIdType, SOAD_VAR) SoAd_DynSockIndx_auo[];
extern VAR(SoAd_SoConIdType, SOAD_VAR) SoAd_TcpIpSocHandleToDynSockIdx_auo[];
extern VAR(TcpIp_SocketIdType, SOAD_VAR) SoAd_GroupTcpIpSocketId_auo[];

#if (SOAD_NUM_TX_IF_TCP_PDU > 0)
extern VAR(SoAd_IfTcpPduTxPendingStatus_tst, SOAD_VAR) SoAd_IfTcpPduTxPendingStatus_ast[];
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */

/* Dynamic socket table */
extern VAR(SoAd_DyncSocConfigType_tst , SOAD_VAR)  SoAd_DyncSocConfig_ast[];
/* List of all remote IPv4 address (together with port) for dynamic sockets */
extern P2VAR(SoAd_SockAddrInetType, SOAD_CONST, SOAD_CONST)   SoAd_DynSoConRemoteAddrInet_pst;
/* List of all remote IPv6 address (together with port) for dynamic sockets */
extern P2VAR(SoAd_SockAddrInet6Type, SOAD_CONST, SOAD_CONST)  SoAd_DynSoConRemoteAddrInet6_pst;


#define SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_32
#include "SoAd_MemMap.h"
extern P2CONST( SoAd_ConfigType, SOAD_CONST, SOAD_CONST ) SoAd_CurrConfig_cpst;
#define SOAD_STOP_SEC_VAR_INIT_32
#include "SoAd_MemMap.h"

#if ( TCPIP_TCP_ENABLED == STD_ON )
#define SOAD_TCPIP_TCPSOCKET_MAX    TCPIP_TCPSOCKETMAX
#else
#define SOAD_TCPIP_TCPSOCKET_MAX    SOAD_NUM_TCPIP_SOCKETS
#endif

#define SOAD_FORCE_RETRIEVE_TRANSMISSION_TRUE       TRUE
#define SOAD_FORCE_RETRIEVE_TRANSMISSION_FALSE      FALSE

#define SOAD_SOCKET_CONNECTION_REFERENCE            TRUE
#define SOAD_SOCKET_BUNDLE_REFERENCE                FALSE

#ifndef SOAD_PDUHDR_SIZE
/* Size of the PDU header of SoAd */
#define SOAD_PDUHDR_SIZE                            8U
#endif

/* Size of the PDU ID part in the PDU header of SoAd(Header Id / length) */
#define SOAD_PDUHDR_PDUID_LENGTH_SIZE               4U

/* Size of the PDU LEN part in the PDU header of SoAd */
#define INVALID                                     7U
#define SOAD_NULL                                   0U
#define SOAD_CFG_SOCON_ID_DEFAULT_VALUE             (SoAd_SoConIdType)0xFFFFU
#define SOAD_CFG_SOCKET_ID_DEFAULT_VALUE            (TcpIp_SocketIdType)0xFFFFU
#define SOAD_CFG_PDU_ID_DEFAULT_VALUE               (PduIdType)0xFFFFU
#define SOAD_CFG_RGRP_DEFAULT_VALUE                 (SoAd_RoutingGroupIdType)0xFFFFU
#define SOAD_CFG_PDU_LENGTH_DEFAULT_VALUE           (PduLengthType)0xFFFFFFFFU
#define SOAD_CFG_TCPKEEPALIVE_DEFAULT_VALUE         (SoAd_TcpSocGrpIndexType)0xFFFFFFFFU
#define SOAD_CFG_TP_UDP_TXBUFFER_DEFAULT_VALUE      (SoAd_TpUdpTxBuffIndexType)0xFFFFFFFFU
#define SOAD_CFG_nPDU_UDP_TX_DEFAULT_VALUE          (SoAd_nPduUdpTxIndexType)0xFFFFFFFFU
#define SOAD_CFG_UDPALIVESUPERVISION_DEFAULT_VALUE  (SoAd_UdpSocGrpIndexType)0xFFFFFFFFU
#define SOAD_DEFAULT_PORT                           0xFFFFU
#define SOAD_DEFAULT_IP                             0xFFFFFFFFU
#define SOAD_DEFAULT_PDU_HDR_ID                     0xFFFFFFFFU

/* SoAd DET Errors */
#define SOAD_E_NOTINIT                      0x01U
#define SOAD_E_PARAM_POINTER                0x02U
#define SOAD_E_INV_ARG                      0x03U
#define SOAD_E_NOBUFS                       0x04U
#define SOAD_E_INV_PDUHEADER_ID             0x05U
#define SOAD_E_INV_PDUID                    0x06U
#define SOAD_E_INV_SOCKETID                 0x07U
#define SOAD_E_INIT_FAILED                  0x08U

/* FramePriority is a 3 bit field in VLAN header, so it's maximum value is 7 only */
#define SOAD_ETH_VLAN_FRAMEPRIO_MAXVAL      7U

#define SOAD_DHCP_RESERVED_SERVER_PORT      67U
#define SOAD_DHCP_RESERVED_CLIENT_PORT      68U

/* SoAd API Id's */
#define SOAD_INIT_API_ID                                    0x01U
#define SOAD_GET_VERSION_INFO_API_ID                        0x02U
#define SOAD_IF_TRANSMIT_API_ID                             0x03U
#define SOAD_TP_TRANSMIT_API_ID                             0x04U
#define SOAD_TP_CANCEL_TRANSMIT_API_ID                      0x05U
#define SOAD_TP_CANCEL_RECEIVE_API_ID                       0x06U
#define SOAD_GET_SOCON_API_ID                               0x07U
#define SOAD_OPEN_SOCON_API_ID                              0x08U
#define SOAD_CLOSE_SOCON_API_ID                             0x09U
#define SOAD_REQUEST_IPADDR_ASSIGNMENT_API_ID               0x0AU
#define SOAD_RELEASE_IPADDR_ASSIGNMENT_API_ID               0x0BU
#define SOAD_GET_LOCAL_ADDR_API_ID                          0x0CU
#define SOAD_GET_PHYS_ADDR_API_ID                           0x0DU
#define SOAD_ENABLE_ROUTING_API_ID                          0x0EU
#define SOAD_DISABLE_ROUTING_API_ID                         0x0FU
#define SOAD_SET_REMOTE_ADDRESS_API_ID                      0x10U
#define SOAD_CHANGE_PARAMETER_API_ID                        0x11U
#define SOAD_RX_INDICATION_API_ID                           0x12U
#define SOAD_COPY_TX_DATA_API_ID                            0x13U
#define SOAD_TX_CONFIRMATION_API_ID                         0x14U
#define SOAD_TCP_ACCEPTED_API_ID                            0x15U
#define SOAD_TCP_CONNECTED_API_ID                           0x16U
#define SOAD_TCPIP_EVENT_API_ID                             0x17U
#define SOAD_LOCAL_IPADDR_ASSIGNMENT_CHG_API_ID             0x18U
#define SOAD_MAIN_FUNCTION_API_ID                           0x19U
#define SOAD_READ_DHCP_HOST_NAME_OPTION_API_ID              0x1AU
#define SOAD_WRITE_DHCP_HOST_NAME_OPTION_API_ID             0x1BU
#define SOAD_GET_REMOTE_ADDR_API_ID                         0x1CU
#define SOAD_IF_ROUTING_GROUP_TRANSMIT_API_ID               0x1DU
#define SOAD_SET_UNIQUE_REMOTE_ADDRESS_API_ID               0x1EU
#define SOAD_IF_SPECIFIC_ROUTING_GROUP_TRANSMIT_API_ID      0x1FU
#define SOAD_ENABLE_SPECIFIC_ROUTING_API_ID                 0x20U
#define SOAD_DISABLE_SPECIFIC_ROUTING_API_ID                0x21U
#define SOAD_INFORM_START_OF_RECEPTION_API_ID               0x22U
#define SOAD_TP_TX_CONFIRMATION_TO_UL_API_ID                0x23U
#define SOAD_TCPIP_CLOSE_API_ID                             0x24U
#define SOAD_GET_ROUTING_GROUP_STATUS_API_ID                0x25U
#define SOAD_MAIN_FUNCTION_1MS_API_ID                       0x26U

/* DET macro definition */
#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
        /* For functions which should not be exit */
    #define SOAD_DET_REPORT_ERROR( CONDITION, API, ERROR ) \
        SoAd_DetErrFlag_u8 = ((( E_NOT_OK == SoAd_DetErrFlag_u8 ) && (CONDITION)) ? Det_ReportError( (SOAD_MODULE_ID), (SOAD_INSTANCE_ID), (API), (ERROR) ) : SoAd_DetErrFlag_u8 );
#else
    /* For functions which should not be exit */
    #define SOAD_DET_REPORT_ERROR( CONDITION, API, ERROR )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF  */

/****************************************************************************************************************
**                                   Function Prototypes                                                       **
****************************************************************************************************************/
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF )
LOCAL_INLINE FUNC( boolean, SOAD_CODE ) SoAd_GetRoutingGroupsEnabledStatus( \
                                            P2CONST( SoAd_RoutingGroupIdType, AUTOMATIC, AUTOMATIC )  RoutingGroups_cpuo, \
                                            VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 NumOfTxRoutingGroups_uo, \
                                            VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId_uo );

/**
 *******************************************************************************************************************
 * \Function Name : SoAd_GetRoutingGroupsEnabledStatus()
 *
 * \Function description
 * This service shall be invoked to get the Routing Group enabled status for particular pduRouteDest or socketRouteDest.
 * If multiple routing groups are configured for any pduRouteDest/socketRouteDest, then this service shall loop through for all
 * routing groups to identify any one of the routing group is enabled for the given SoConId combination.
 *
 * Parameters (in):
 * \param   const SoAd_RoutingGroupIdType*
 * \arg     RoutingGroups_cpuo - list of Routing Group id's for particular PduRouteDest
 * \param   SoAd_RoutingGroupIdType
 * \arg     NumOfTxRoutingGroups_uo - Number of Routing Group id's passed in RoutingGroups_cpuo argument
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - static socket id
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: boolean
 *               TRUE - Routing group is enbaled for atleast one of routing group available at RoutingGroups_cpuo[]
 *               FALSE - Routing group is disbaled for all routing groups available at RoutingGroups_cpuo[]
 *
 ********************************************************************************************************************
 */
LOCAL_INLINE FUNC( boolean, SOAD_CODE ) SoAd_GetRoutingGroupsEnabledStatus( P2CONST( SoAd_RoutingGroupIdType, AUTOMATIC, AUTOMATIC )  RoutingGroups_cpuo, \
                                                                      VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 NumOfTxRoutingGroups_uo, \
                                                                      VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId_uo )
{
    /* Local pointer to store the SoAd_RoutingGroupSoConStructMap_tst array for given index*/
    P2CONST(SoAd_RoutingGroupSoConStructMap_tst, AUTOMATIC, AUTOMATIC)  lSoAdRoutingGroupSoConStructMap_cpst;

    /* Loop through for NumofSocket Mapping to RG Id */
    VAR( SoAd_SoConIdType, AUTOMATIC )                                  lIdxSoCon_uo;

    /* Loop through for NumofTxRoutingGroups Mapping to PduRouteDests */
    VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                           lIdxOfRoutingGroup_uo;

    /* Variable to hold the Routing group Id */
    VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                           lRgId_uo;

    /* Routing Group Status */
    VAR(boolean, AUTOMATIC)                                             lRgStatus_b;

    /* Initialize the local variables which are declared above */
    lRgStatus_b                             = FALSE;

    for( lIdxOfRoutingGroup_uo = 0;
                ( ( lIdxOfRoutingGroup_uo < NumOfTxRoutingGroups_uo ) && ( FALSE == lRgStatus_b ) ); lIdxOfRoutingGroup_uo++)
    {
        /* fetch the Routing Group Id ono by one for checking the routing group status for this pduroute dest,
         * If any one of Routing group status is enabled then packet will be trnasmitted to LL or forwarded to UL */
        lRgId_uo = RoutingGroups_cpuo[lIdxOfRoutingGroup_uo];

        /* check routing group id is valid */
        if(lRgId_uo < SoAd_CurrConfig_cpst->SoAd_noRoutingGrps_cuo)
        {
            /* copy the global array address to local pointer for given index */
            lSoAdRoutingGroupSoConStructMap_cpst    = &(SoAd_CurrConfig_cpst->SoAd_RoutingGroupSoConStructMap_cpst[lRgId_uo]);

            /* Loop for each SoConId's whcih are mapped to given Routing Group Id */
            for(lIdxSoCon_uo = 0; \
                    lIdxSoCon_uo < lSoAdRoutingGroupSoConStructMap_cpst->numOfSoConIdMapped_uo; \
                    lIdxSoCon_uo++)
            {
                /* Check for matched SoconId for the given Routing Group Id */
                if(lSoAdRoutingGroupSoConStructMap_cpst->routingGrpSoConMap_pst[lIdxSoCon_uo].mappedSoConId_uo == SoConId_uo)
                {
                    /* Get the Routing Group status */
                    lRgStatus_b = lSoAdRoutingGroupSoConStructMap_cpst->routingGrpSoConMap_pst[lIdxSoCon_uo].rg_status_b;
                    break;
                }
            }

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
        /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
         * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
         * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
         * for the same function.
         */
        SoAd_DetErrFlag_u8 = E_NOT_OK;

        SOAD_DET_REPORT_ERROR( (lIdxSoCon_uo == lSoAdRoutingGroupSoConStructMap_cpst->numOfSoConIdMapped_uo ) , SOAD_GET_ROUTING_GROUP_STATUS_API_ID, SOAD_E_INV_ARG )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF  */
        }
    }

    return lRgStatus_b;
}

#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

FUNC( void, SOAD_CODE )                 SoAd_ResetDynSockTblByEntry                         ( VAR( SoAd_SoConIdType, AUTOMATIC )    StaticSocketId_uo,\
                                                                                              VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo, \
                                                                                              VAR(SoAd_SoConModeType, AUTOMATIC )   Mode_en );

FUNC( void, SOAD_CODE )                 SoAd_ModeChgCallbackToUl                            ( VAR( SoAd_SoConIdType, AUTOMATIC )    StaticSocketId_uo,\
                                                                                              VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo, \
                                                                                              VAR(SoAd_SoConModeType, AUTOMATIC )   Mode_en);

FUNC( void, SOAD_CODE )                 SoAd_ReserveFreeDynSocket                           ( VAR( SoAd_SoConIdType, AUTOMATIC )             StaticSocketId_uo,\
                                                                                              P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)  DynSocketId_puo);

#if (SOAD_TP_PRESENT != STD_OFF)
FUNC( void, SOAD_CODE )                 SoAd_InformTpStartOfReception                       ( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,\
                                                                                              VAR(PduIdType,         AUTOMATIC)   RxPduId_uo);

FUNC( void, SOAD_CODE )                 SoAd_TpTxConfirmationToUl                           ( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,\
                                                                                              VAR(PduIdType, AUTOMATIC)           TxPduId_uo,\
                                                                                              VAR( PduLengthType, AUTOMATIC )     PduLength_uo );

FUNC( void, SOAD_CODE )                 SoAd_ResetTpTxDyncParameters                        ( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo,\
                                                                                              VAR(PduIdType, AUTOMATIC)           TxPduId_uo,\
                                                                                              VAR(Std_ReturnType, AUTOMATIC)      Result_u8 );
#endif /* SOAD_TP_PRESENT != STD_OFF */

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_BestMatchAlgorithm                             ( VAR  ( SoAd_SoConIdType, AUTOMATIC )                  SoConId_uo, \
                                                                                              VAR( SoAd_SoConIdType, AUTOMATIC )                    SoConGrpId_uo , \
                                                                                              VAR( uint32, AUTOMATIC )                              RxHeaderId_32 , \
                                                                                              P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr_cpst, \
                                                                                              P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )       SocketIdBestMatch_puo );

FUNC( boolean, SOAD_CODE )              SoAd_IsMatchRxPduFound                              ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,\
                                                                                              VAR( uint32, AUTOMATIC )                              RxPduHdrId_32 );

FUNC( void, SOAD_CODE )                 SoAd_PerformPostPduTransmissionAction               ( VAR( SoAd_SoConIdType, AUTOMATIC )    StaticSocketId_uo );

FUNC( void, SOAD_CODE )                 SoAd_InsertPduHdrToBuffer                           ( VAR(uint32, AUTOMATIC)                PduHeaderId_u32,\
                                                                                              VAR(uint32, AUTOMATIC)                PduLength_u32,\
                                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )  Buffer_pu8 );

FUNC( void, SOAD_CODE )                 SoAd_TerminateActiveSession                         ( VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo );

/* nPdu */
#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
FUNC( void, SOAD_CODE )                 SoAd_ResetnPduUdpTx                                 ( VAR(SoAd_SoConIdType, AUTOMATIC)          StaticSocketId_uo );

FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE )   SoAd_nPduUdpTransmit                      ( VAR(SoAd_SoConIdType, AUTOMATIC)          StaticSocketId_uo, \
                                                                                              VAR(PduLengthType, AUTOMATIC)             PduLength_uo, \
                                                                                              P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)  PduRouteDest_cpst );

#if ( SOAD_TIMEOUT_HANDLING_ENABLED == STD_ON )
FUNC( void, SOAD_CODE )                  SoAd_nPduUdpTxSendAllPdus                          ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo );
#endif

FUNC( BufReq_ReturnType, SOAD_CODE )    SoAd_nPduUdpTxCopyPdusToTcpIpBuffer                 ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo,
                                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )      Buffer_pu8,
                                                                                              VAR( uint16, AUTOMATIC )                  BufferLength_u16 );
#endif /* SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 */

#if ( (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF) || (SOAD_UDP_GRP_PRESENT != STD_OFF) )
FUNC( boolean, SOAD_CODE )              SoAd_GetOtherActiveDynSocketForGroup                ( VAR( SoAd_SoConIdType, AUTOMATIC )             StaticSocketId_uo,\
                                                                                              P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)  DynSocketId_puo );
#endif /* (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF) || (SOAD_UDP_GRP_PRESENT != STD_OFF) */

#if (SOAD_NUM_TX_IF_TCP_PDU > 0)
FUNC( void, SOAD_CODE )                 SoAd_IfTcpTxConfirmationToUl                        ( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo, \
                                                                                              VAR(PduIdType, AUTOMATIC)           TxPduId_uo, \
                                                                                              VAR(uint16, AUTOMATIC)              Length_u16, \
                                                                                              VAR(boolean, AUTOMATIC)             CloseReq_b);
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */


/* RxIndication */
FUNC( Std_ReturnType, SOAD_CODE )       SoAd_SelectRxSocketRoute                            ( VAR(SoAd_SoConIdType, AUTOMATIC)                  StaticSocketId_uo,
                                                                                              VAR( uint32, AUTOMATIC )                          RxHeaderId_32,
                                                                                              VAR( boolean, AUTOMATIC )                         HeaderEnableFlag_b,
                                                                                              P2VAR( PduIdType, AUTOMATIC, AUTOMATIC )          RxPduId_puo );

/* RxBuffer */
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( void, SOAD_CODE )                 SoAd_ResetRxBuffer                                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo );

FUNC( uint16, SOAD_CODE )               SoAd_GetRxBufLnrFreeLen                             ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo );

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_AddFragmentedHeaderInRxBuffer                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            SrcPtr_cpu8,
                                                                                              VAR( uint16, AUTOMATIC )                          SrcLen_u16,
                                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )              CopiedLength_pu8 );

FUNC( void, SOAD_CODE )                 SoAd_GetFragmentedHeaderFromRxBuffer                ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2VAR( uint8*, AUTOMATIC, AUTOMATIC )             PduHeaderPointer_ppu8 );

FUNC( void, SOAD_CODE )                 SoAd_ClearFragmentedHeaderFromRxBuffer              ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo );

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_StartFragmentedDataInRxBuffer                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC ) RxPduDesc_cpst,
                                                                                              P2VAR( boolean, AUTOMATIC, AUTOMATIC )            HeaderSavedInBuff_pb );

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_AddFragmentedDataInRxBuffer                    ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            SrcPtr_cpu8,
                                                                                              VAR( uint16, AUTOMATIC )                          SrcLen_u16 );

FUNC( void, SOAD_CODE )                 SoAd_GetFragmentedDataFromRxBuffer                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2VAR( uint8*, AUTOMATIC, AUTOMATIC )             PduDataPointer_ppu8 );

FUNC( uint16, SOAD_CODE )               SoAd_ClearFragmentedDataFromRxBuffer                ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2VAR( uint32, AUTOMATIC, AUTOMATIC )             RemainingPduDataLength_pu32 );
#endif

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
FUNC( void, SOAD_CODE )                 SoAd_StartTpDataInRxBuffer                          ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC ) RxPduDesc_cpst,
                                                                                              VAR( uint16, AUTOMATIC )                          ForwardedDataLenToUl_u16 );

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_AddTpDataInRxBuffer                            ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            SrcPtr_cpu8,
                                                                                              VAR( uint16, AUTOMATIC )                          SrcLen_u16 );

FUNC( Std_ReturnType, SOAD_CODE )       SoAd_AddExtraTpDataInRxBuffer                       ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC ) RxPduDesc_cpst,
                                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            SrcPtr_cpu8,
                                                                                              VAR( uint16, AUTOMATIC )                          SrcLen_u16 );

FUNC( void, SOAD_CODE )                 SoAd_CopyTpDataFromRxBufferToUl                     ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                                              VAR( boolean, AUTOMATIC )                         TerminationRequested_b );
#endif


#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_PRV_H */
