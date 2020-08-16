/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/



/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "SoAd.h"
#include "PduR_SoAdIf.h"    /* The upper layer modules that provide the CBK functions must be included*/

#include "SoAd_Prv.h"



#define SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"

VAR(TcpIp_IpAddrStateType, SOAD_VAR) SoAd_LocalAddrIdx_State_aen[SOAD_MAX_TCPIP_LOCALADDRIDX] = {  TCPIP_IPADDR_STATE_UNASSIGNED  };

VAR(SoAd_SoConIdType, SOAD_VAR) SoAd_DynSockIndx_auo[SOAD_CFG_NUM_ACTIVESOCK]  = {  SOAD_CFG_SOCON_ID_DEFAULT_VALUE };

VAR(SoAd_SoConIdType, SOAD_VAR) SoAd_TcpIpSocHandleToDynSockIdx_auo[SOAD_NUM_TCPIP_SOCKETS] = {  SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE , SOAD_CFG_SOCON_ID_DEFAULT_VALUE };

VAR(TcpIp_SocketIdType, SOAD_VAR) SoAd_GroupTcpIpSocketId_auo[SOAD_CONFIG_NUM_STATIC_SOCKETGRP] = {  SOAD_CFG_SOCKET_ID_DEFAULT_VALUE };

#define SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_CONST_8
#include "SoAd_MemMap.h"

static CONST(boolean, SOAD_CONST) SoAd_Config_RoutingGroup_ROM_cab[SOAD_CONFIG_ACTIVE_NUM_ROUTING_GROUPS]= {  TRUE , TRUE  };


#define SOAD_STOP_SEC_CONST_8
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"


#define SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"


#define SOAD_STOP_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"

/* Routing Groups configured for SoAdSocketRoute_ComRx and SoAdSocketRouteDest */
static CONST(SoAd_RoutingGroupIdType, SOAD_CONST) SoAd_Config_SocketRoute0_SocketRouteDest0_RgId_cauo[1] = 
{
    0,
};


/* Routing Groups configured for PduTriggering_TX_EthernetPhysicalChannel and SoAdPduRouteDest_0 */
static CONST(SoAd_RoutingGroupIdType, SOAD_CONST) SoAd_Config_PduRoute0_PduRouteDest0_RgId_cauo[1] = 
{
    1,
};


/* Socket connection group PduTriggering_TX_EthernetPhysicalChannel */
static CONST(PduRouteDestType_tst, SOAD_CONST) SoAd_Config_PduTriggering_TX_EthernetPhysicalChannel_cast[1]=
{
    { 0xffffffffu,     &SoAd_Config_PduRoute0_PduRouteDest0_RgId_cauo[0],              1,     (SoAd_SoConIdType)0, SOAD_SOCKET_BUNDLE_REFERENCE,},
};


#define SOAD_STOP_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"

/*Tx confirm flag for IF Tx UDP Pdus*/
VAR(boolean, SOAD_VAR) SoAd_ULIfUdpTxConfirmFlag_ab[SOAD_CFG_NUM_TXPDU] = {  FALSE };

#define SOAD_STOP_SEC_VAR_INIT_8
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_CONST_16
#include "SoAd_MemMap.h"

/* index for Tx confirm  for Tx IF UDP Pdus*/
static CONST(uint16, SOAD_CONST) SoAd_Config_IfUdpTxPduIndex_cau16[SOAD_CONFIG_NUM_TX_IF_UDP_PDU] = { 0 };

#define SOAD_STOP_SEC_CONST_16
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"


static CONST(PduIdType, SOAD_CONST) SoAd_Socket0RxPduIds_cauo[1] = {0 };

#define SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"




#define SOAD_START_SEC_CONST_32
#include "SoAd_MemMap.h"




#define SOAD_STOP_SEC_CONST_32
#include "SoAd_MemMap.h"


#define SOAD_START_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"

/* Tx PDUs Configuration */
static CONST(SoAd_TxPduConfigType_tst, SOAD_CONST) SoAd_Config_TxPduConfig_cast[SOAD_CONFIG_NUM_TXPDU]=
{
      /*Index*/                 /*SoAdtxPduId*/             /*SoAdULtxPduId*/               /*NumberOfPduRoutDests*/    /*UpperLayerType*/              /*User*/                    /*PduRouteDestContainers Info {PduRouteDestHeaderId, RoutingGroupId, SocketConnectionId, TriggerMode}*/                /*txPduLength*/                        /*idxIfTxConfirm*/        
     { (PduIdType)0,          (PduIdType)0,              (PduIdType)0,                    (PduIdType)1,                   SOAD_IF,                    SOAD_USER_PDUR,                 &SoAd_Config_PduTriggering_TX_EthernetPhysicalChannel_cast[0],                                                                           (PduLengthType)4,                                 1,                     },
};

/* Rx PDUs Configuration */
static CONST(SoAd_RxPduConfigType_tst, SOAD_CONST) SoAd_Config_RxPduConfig_cast[SOAD_CONFIG_NUM_RXPDU]=
{
         /*Index*/   /*SoAdrxPduId*/        /*SoAdULrxPduId*/              /*reserved*/               /*rxPduHeaderId*/           /*UpperLayerType*/                /*User*/                /*rxPduLength*/                     /*ReservedPduLen*/                            /*idxSocket*/                       /*reservedSoConIdx*/                                /*rxRoutingGroupConf_cpuo*/              /*numOfRxRoutingGroups_uo*//*idxIfRxInd*/         /*identifyRxSocketConnOrBundRef_b*/
     { (PduIdType)0,  (PduIdType)0,          (PduIdType)0,      SOAD_CFG_PDU_ID_DEFAULT_VALUE,            0xffffffffu,                 SOAD_IF,                SOAD_USER_PDUR,         (PduLengthType)4,             SOAD_CFG_PDU_LENGTH_DEFAULT_VALUE,              (SoAd_SoConIdType)0,            SOAD_CFG_SOCON_ID_DEFAULT_VALUE,                   &SoAd_Config_SocketRoute0_SocketRouteDest0_RgId_cauo[0],    1,               1,                                    SOAD_SOCKET_BUNDLE_REFERENCE,},
};

/* Static SoAd Socket Configuration */
static CONST(SoAd_StaticSocConfigType_tst, SOAD_CONST)  SoAd_Config_StaticSocConfig_cast[SOAD_CONFIG_NUM_STATIC_SOCKETCONNECT] =
{
        /*Index*/                       /*socketId*/                /*socGroupId*/                         /*reserved*/                                /*idxDynSocTable*/                         /*rxPduIds_pcuo*/                /*idxStatSoConRemoteAddr_uo*/                               /*No.ofULsConfigured*/  /*IdxSocModeChgCbk*/            /*idxLocalAddrChgCbk*/     /*numberOfRxPdusConfigured_u8*/

     { (SoAd_SoConIdType)0,        (SoAd_SoConIdType)0,          (SoAd_SoConIdType)0,            SOAD_CFG_SOCON_ID_DEFAULT_VALUE,                (SoAd_SoConIdType *)&SoAd_DynSockIndx_auo[0],                           &SoAd_Socket0RxPduIds_cauo[0],         (SoAd_SoConIdType)0,          1,                           0,                        0,               1},
};

/* List of all remote IPv4 address (together with port) for static sockets */
static CONST(SoAd_SockAddrInetType, SOAD_CONST) SoAd_Config_StatSoConRemoteAddrInet_cast[] =
{   /* IP, port */
    { 0xC0A80A05u, 0x4c7 },
};



/* Static SoAd SocketConnectionGroup UDP Configuration */
static CONST(SoAd_StaticUdpConfigType_tst, SOAD_CONST)  SoAd_Config_StaticUdpConfig_cast[SOAD_CONFIG_NUM_STATIC_UDP_SOCKETGRP] =
{
/*listenOnlyUDP*/   /*udpStrictHdrLenChkEnabled*/                        /*udpTrigTimoutIdx*/

     { /*udpIndex  0*/      STD_ON,                     STD_OFF,                       (SoAd_UdpSocGrpIndexType)0xFFFFFFFFu},
};


/* Static SoAd SocketConnectionGroup Configuration */
static CONST(SoAd_StaticSoConGrpConfigType_tst, SOAD_CONST)  SoAd_Config_StaticSoConGrpConfig_cast[SOAD_CONFIG_NUM_STATIC_SOCKETGRP] =
{
            /*Index*/                   /*socketGrpId*/                 /*StartSocConId*/                   /*MaxSoConCount*/                                      /*udpProtocolIdx_pst*/                                                /*Protocol*/            /*Domain*/              /*localPort*/            /*LocalAddrId*/        /*FramePriority*/      /*HeaderEnable*/        /*rsrcMgtEnable*/           /*socConAuto*/       /*ipAddrNtfy*/          /*MsgAccptEnable*/        /*ModeChgEnable*/

     { (SoAd_SoConIdType)0,           (SoAd_SoConIdType)0,         (SoAd_SoConIdType)0,               (SoAd_SoConIdType)1,                    &SoAd_Config_StaticUdpConfig_cast[0],                              TCPIP_IPPROTO_UDP,         TCPIP_AF_INET,                 0x45f,                  0,                    255,                     FALSE,                       FALSE,                   TRUE,                    FALSE,              TRUE,                     FALSE},
};

#define SOAD_STOP_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"


#define SOAD_START_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"

/* Dynamic SoAd Socket Configuration */
VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR) SoAd_DyncSocConfig_ast[SOAD_CFG_NUM_ACTIVESOCK]=
{
    /*RxPduInfoPtr*/ /*TxPduInfoPtr*/      /*SocketState*/          /*SocConSubMode*/      /*socConReqMode_e*/         /*idxDynSoConRemoteAddr_uo*/          /*DyncLocalPort*/  /*socConOpenReqCnt_u16*/ /*socConCloseReqCnt_u16*/      /*txPduHeaderId_u32*/    /*ifTcpBufferLen_uo*/  /*reserved_uo*/  /*Dynamic Sock Index*/               /*StaticSocInd*/                  /*idxTxPduId_uo*/                   /*idxRxPduId_uo*/                    /*socketHandleTcpIp*/              /*IfTransmissionOngoing_b*//*statusAbort_b*//*DiscardNewTxRxReq_b*//*ifTpTxSoAdHdrCopied_b*/
    { NULL_PTR,        NULL_PTR,         SOAD_SOCON_OFFLINE,        SOAD_SOCON_IDLE,       SOAD_EVENT_IDLE,          (SoAd_SoConIdType)0,        SOAD_DEFAULT_PORT,               0,                  0,                        SOAD_DEFAULT_PDU_HDR_ID, 0,          0,        (SoAd_SoConIdType)0,      SOAD_CFG_SOCON_ID_DEFAULT_VALUE,    SOAD_CFG_PDU_ID_DEFAULT_VALUE,     SOAD_CFG_PDU_ID_DEFAULT_VALUE,        SOAD_CFG_SOCKET_ID_DEFAULT_VALUE,              FALSE,               FALSE,           FALSE,                   FALSE,},
};

/* List of all remote IPv4 address (together with port) for dynamic sockets */
static VAR(SoAd_SockAddrInetType, SOAD_VAR) SoAd_DynSoConRemoteAddrInet_ast[(SoAd_SoConIdType)1] =
{
    { SOAD_DEFAULT_IP, SOAD_DEFAULT_PORT },
};


/* List of all remote IPv4 address (together with port) for dynamic sockets */
P2VAR(SoAd_SockAddrInetType, SOAD_VAR, SOAD_VAR) SoAd_DynSoConRemoteAddrInet_pst = &(SoAd_DynSoConRemoteAddrInet_ast[0]);

/* List of all remote IPv6 address (together with port) for dynamic sockets */
P2VAR(SoAd_SockAddrInet6Type, SOAD_VAR, SOAD_VAR) SoAd_DynSoConRemoteAddrInet6_pst = NULL_PTR; /* is null because we don't have any IPv6 sockets */

static VAR(SoAd_RoutingGroupSoConMap_tst, SOAD_VAR) SoAd_RoutingGroupId0SoConMap_ast[1]=
{
    {0, FALSE},
};

static VAR(SoAd_RoutingGroupSoConMap_tst, SOAD_VAR) SoAd_RoutingGroupId1SoConMap_ast[1]=
{
    {0, FALSE},
};


static CONST(SoAd_RoutingGroupSoConStructMap_tst, SOAD_CONST)   SoAd_RoutingGroupSoConStructMap_ast[SOAD_CONFIG_ACTIVE_NUM_ROUTING_GROUPS] =
{
    {&SoAd_RoutingGroupId0SoConMap_ast[0], 1},
    {&SoAd_RoutingGroupId1SoConMap_ast[0], 1},
};


#define SOAD_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SoAd_MemMap.h"





#define SOAD_START_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"

/* List of callbacks for IF-Tx Confirmation */
static CONST(SoAd_IfTxCallbacks_tst, SOAD_CONST)    SoAdIf_TxCbks_cast[SOAD_NUM_IFTXCALLBACKS] =
{
    { NULL_PTR },
    {&PduR_SoAdIfTxConfirmation},
    { NULL_PTR }

};

/* List of callbacks for IF-Rx Indication  */
static CONST(SoAd_IfRxCallbacks_tst, SOAD_CONST)    SoAdIf_RxCbks_cast[SOAD_NUM_IFRXCALLBACKS] =
{
    { NULL_PTR },
    {&PduR_SoAdIfRxIndication},
    { NULL_PTR }
};


/* List of callbacks for soc copy tx data to upper layer */
static CONST(SoAd_LocalIpAddrAsgnChgCbk_tst, SOAD_CONST)   SoAd_LocalIpAddrAsgnChgCbk_cast[SOAD_NUM_LOCALIPADDRASGNCHGCBK] =
{
    { NULL_PTR },
    { NULL_PTR }
};

/* List of callbacks for soc connection mode change notification to upper layer */
static CONST(SoAd_SoConModeChgCallbacks_tst, SOAD_CONST)    SoAd_SoConModeChgCbks_cast[SOAD_NUM_SOCONMODECHGCALLBACKS] =
{
    { NULL_PTR },
    { NULL_PTR }
};



/* SoAd PB Configuration table. Derived from SoAd SWS */
CONST( SoAd_ConfigType, SOAD_CONST )     SoAd_ConfigSet[SOAD_NUM_CONFIG] =
{
    /* Configuration */
    {
        /* Routing Grp's in configuration */
        (&(SoAd_Config_RoutingGroup_ROM_cab[0])),



        /* Tx PDUs Configuration */
        (&(SoAd_Config_TxPduConfig_cast[0])),

        /* Rx PDUs Configuration */
        (&(SoAd_Config_RxPduConfig_cast[0])),

        /* Static SoAd Socket Configuration */
        (&(SoAd_Config_StaticSocConfig_cast[0])),

        /* List of all remote IPv4 address (together with port) for static sockets */
        (&(SoAd_Config_StatSoConRemoteAddrInet_cast[0])),

        /* List of all remote IPv6 address (together with port) for static sockets */
        NULL_PTR, /* NULL because we don't have IPv6 addresses */

        /* Static SoAd SocketConnectionGroup Configuration */
        (&(SoAd_Config_StaticSoConGrpConfig_cast[0])),


        /* index for Tx confirm  for Tx IF UDP Pdus*/
        (&(SoAd_Config_IfUdpTxPduIndex_cau16[0])),




        /* List of callbacks for IF-Tx Confirmation */
        (&(SoAdIf_TxCbks_cast[0])),

        /* List of callbacks for IF-Rx Indication  */
        (&(SoAdIf_RxCbks_cast[0])),


        /* List of callbacks for soc connection mode change notification to upper layer */
        (&(SoAd_SoConModeChgCbks_cast[0])),

        /* List of callbacks for soc copy tx data to upper layer */
        (&(SoAd_LocalIpAddrAsgnChgCbk_cast[0])),

        /* List of SoConId mapping for each Routing Group Id */
        (&(SoAd_RoutingGroupSoConStructMap_ast[0])),

        /* Number of Static SoAd Socket in Configuration */
        SOAD_CONFIG_NUM_STATIC_SOCKETCONNECT,

        /* Number of Static SoAd SocketConnectionGroup in Configuration */
        SOAD_CONFIG_NUM_STATIC_SOCKETGRP,

        /* Number of Active Socket in Configuration */
        (SoAd_SoConIdType)1,

        /* Number of IPv4 Active Socket in Configuration */
        (SoAd_SoConIdType)1,

        /* Number of Rx PDUs in Configuration */
        SOAD_CONFIG_NUM_RXPDU,

        /* Number of Tx PDUs in Configuration */
        SOAD_CONFIG_NUM_TXPDU,

        /* Number of UDP Tx IF PDUs in Configuration */
        SOAD_CONFIG_NUM_TX_IF_UDP_PDU,

        /* Reserved for future use and word aligned purpose */
        0,


        /* Number of Routing Grp's in Configuration */
        SOAD_CONFIG_ACTIVE_NUM_ROUTING_GROUPS,

    }
};

#define SOAD_STOP_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"


