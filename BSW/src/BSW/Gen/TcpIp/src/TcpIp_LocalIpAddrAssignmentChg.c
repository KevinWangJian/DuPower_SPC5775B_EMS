

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#include "SoAd_Cbk.h"
#include "EthSM_Cbk.h"

#if ( TCPIP_ARP_ENABLED == STD_ON )
#include "rba_EthArp.h"
#endif

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif

#if ( TCPIP_TCP_ENABLED == STD_ON )
#include "rba_EthTcp.h"
#endif

#if ( TCPIP_UDP_ENABLED == STD_ON )
#include "rba_EthUdp.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif

#include "TcpIp_Prv.h"

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/
static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StateAssigned( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                     LocalAddrId_u8,
                                                                P2CONST( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )  IPAddrParam_pcun,
                                                                VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )                IPAddrAssignMethod_en );

static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StateUnassigned(   VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                 LocalAddrId_u8,
                                                                    CONST(TcpIp_DomainType, AUTOMATIC )                     IpDomainType_cu32);

static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StopCurrAssigned(   VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                LocalAddrId_u8,
                                                                     VAR( TcpIp_AssignmentPrio_tu8,    AUTOMATIC )          IPAsgnPrioNew_u8 );

/********************************************************************************************************************/
/* TcpIp_LocalIpAddrAssignmentChg() - This API is callback function called from modules such as AutoIp or DHCP after*/
/*                       a new IP address has been created. The new IP address is assigned to the corresponding     */
/*                       local address id                                                                           */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8        - IP address index specifying the IP address for which an assignment shall be initiated.  */
/*  State_en              - IP address is assigned or unassigned.                                                   */
/*  IPAddrParam_pcun      - Pointer to a structure containing the assigned IP address, net mask and default router  */
/*                          IP address                                                                              */
/*  IPAddrAssignMethod_en - IP address assignment method - DHCP / AutoIp                                            */
/*  IpDomainType_cu32     - IP address domain type - TCPIP_AF_INET/ TCPIP_AF_INET6                                                               */
/*                                                                                                                  */
/* Return :               void                                                                                      */
/*                                                                                                                  */
/********************************************************************************************************************/
void TcpIp_LocalIpAddrAssignmentChg(    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                     LocalAddrId_u8,
                                        VAR( TcpIp_IpAddrStateType, AUTOMATIC )                     State_en,
                                        P2CONST( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC ) 	IPAddrParam_pcun,
                                        VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )                IPAddrAssignMethod_en,
										CONST( TcpIp_DomainType, AUTOMATIC )			            IpDomainType_cu32 )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialized */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_LOCAL_IP_ADDRASSIGNMENTCHG_API_ID, TCPIP_E_NOTINIT )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),  TCPIP_E_LOCAL_IP_ADDRASSIGNMENTCHG_API_ID , TCPIP_E_INV_ARG )

    /* Retrieve the local address configuration pointer*/
    lLocalAddrConfig_pcst   = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* check if the domain fits*/
    TCPIP_DET_REPORT_ERROR_RET_VOID((lLocalAddrConfig_pcst->IpDomainType_u32 != IpDomainType_cu32),  TCPIP_E_LOCAL_IP_ADDRASSIGNMENTCHG_API_ID , TCPIP_E_INV_ARG )

    if( TCPIP_IPADDR_STATE_ASSIGNED == State_en )
    {
        /* If the state of the IP address is TCPIP_IPADDR_STATE_ASSIGNED, call the corresponding API */
        TcpIp_IpAddr_StateAssigned(  LocalAddrId_u8,
                                     IPAddrParam_pcun,
                                     IPAddrAssignMethod_en );
    }
    else if( (TCPIP_IPADDR_STATE_UNASSIGNED == State_en ) &&
        (IPAddrAssignMethod_en == (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en) ) )
    {
        /* If the state of the IP address is TCPIP_IPADDR_STATE_UNASSIGNED, call the corresponding API */
        TcpIp_IpAddr_StateUnassigned( LocalAddrId_u8,
                                      IpDomainType_cu32 );
    }
    else
    {   /* Do nothing */
    }

    return;
}

/********************************************************************************************************************/
/* TcpIp_IpAddr_StateAssigned() - This API is called from  function TcpIp_LocalIpAddrAssignmentChg()                */
/*                                when the state of the IP address is  TCPIP_IPADDR_STATE_ASSIGNED                  */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8    - Local address index for which IP address was assigned.                                      */
/*  IPAddrParam_pcun  - Pointer to a structure containing the assigned IP address, net mask and default router      */
/*                          IP address                                                                              */
/*  IPAddrAssignMethod_en - IP address assignment method - DHCP / AutoIp                                            */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*                      void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StateAssigned( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                     LocalAddrId_u8,
                                                                P2CONST( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )  IPAddrParam_pcun,
                                                                VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )                IPAddrAssignMethod_en )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( TcpIp_AssignmentPrio_tu8,                AUTOMATIC )   lIPAsgnPrioCurr_u8;
    VAR( TcpIp_AssignmentPrio_tu8,                AUTOMATIC )   lIPAsgnPrioNew_u8;
    VAR( uint16,                                  AUTOMATIC )   lIdx_u16;

    /* Local variables initialization */
    lIPAsgnPrioCurr_u8              = 0xFFu;
    lIPAsgnPrioNew_u8               = 0xFFu;

    /* Retrieve the local address configuration pointer*/
    lLocalAddrConfig_pcst   = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* Report DET if IPAddrParam_pcun is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == IPAddrParam_pcun ), TCPIP_E_LOCAL_IP_ADDRASSIGNMENTCHG_API_ID, TCPIP_E_NULL_PTR )

    /* Get the current assigned IP address priority */
    lIPAsgnPrioCurr_u8  = ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8 );

    /* Get the assignment priority of IP to be assigned */
    for( lIdx_u16 = 0; lIdx_u16 < ( lLocalAddrConfig_pcst->NumAddrAsgnment_u8 ); lIdx_u16++ )
    {
        if ( IPAddrAssignMethod_en == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AddrAsgnmentMeth_en ) )
        {
            lIPAsgnPrioNew_u8 = ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AsgnmentPrio_u8 );
            break;
        }
    }

    /* Check whether the new assignment priority is higher than current assigned priority (Lower the value higher the priority) */
    if( lIPAsgnPrioNew_u8 <= lIPAsgnPrioCurr_u8 )
    {
        /* If another IP is already assigned to the LocalAddress, inform SoAd that current assigned IP is unassigned   */
        if(TCPIP_IPADDR_ASSIGNMENT_INVALID != lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AddrAsgnmentMeth_en)
        {
            SoAd_LocalIpAddrAssignmentChg( LocalAddrId_u8, TCPIP_IPADDR_STATE_UNASSIGNED );
        }

        /* Stop current assigned IP addresses with lower priority */
        TcpIp_IpAddr_StopCurrAssigned( LocalAddrId_u8, lIPAsgnPrioNew_u8 );

        /* Close Tcp and Udp sockets using this LocalAddrId, except Dhcp client  */
        #if (TCPIP_TCP_ENABLED == STD_ON)
        rba_EthTcp_AbortByLocalAddrId(LocalAddrId_u8);
        #endif

        #if (TCPIP_UDP_ENABLED == STD_ON)
        rba_EthUdp_TerminateSocUsingLocalAddr(LocalAddrId_u8);
        #endif

        /* Update the IP address into the dynamic field*/
        ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en )    = IPAddrAssignMethod_en;
        ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8 )    = lIPAsgnPrioNew_u8;
        lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un = *(IPAddrParam_pcun);

        /* If the Ctrl is in STARTUP or OFFLINE set the Ctrl to ONLINE and inform EthSM */
        if( (TCPIP_STATE_OFFLINE == TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8]) ||
        (TCPIP_STATE_STARTUP == TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8]) )
        {
            ( TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8] ) = TCPIP_STATE_ONLINE ;

            (void)EthSM_TcpIpModeIndication( lLocalAddrConfig_pcst->EthIfCtrlRef_u8, TCPIP_STATE_ONLINE );
        }

        /* Call back shall not be provided if the Ctrl state is ONHOLD. Call back will be provided to SoAd once Ctrl reaches to ONLINE  */
        if(TCPIP_STATE_ONHOLD != TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8])
        {
            SoAd_LocalIpAddrAssignmentChg( LocalAddrId_u8, TCPIP_IPADDR_STATE_ASSIGNED );
        }

    }   /* if( lIPAsgnPrioNew_u8 <= lIPAsgnPrioCurr_u8 ) */
}


/********************************************************************************************************************/
/* TcpIp_IpAddr_StateUnassigned() -   This API is called from  function TcpIp_LocalIpAddrAssignmentChg()            */
/*                                    when the state of the IP address is  TCPIP_IPADDR_STATE_UNASSIGNED            */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8        -  Local address index for which IP address was unassigned.                               */
/*  IpDomainType_cu32     - IP address domain type - TCPIP_AF_INET/ TCPIP_AF_INET6                                  */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*                      void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StateUnassigned(   VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  LocalAddrId_u8,
                                                                    CONST(TcpIp_DomainType, AUTOMATIC )      IpDomainType_cu32 )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( uint16,                                  AUTOMATIC )   lIdx_u16;
    VAR( TcpIp_LocalAddrIdType,                   AUTOMATIC )   lActiveLocalAddrMappedToCtrl_u8;
    VAR( TcpIp_LocalAddrIdType,                   AUTOMATIC )   lTotalActiveLocalAddr_u8;
    VAR( uint8,                                   AUTOMATIC )   lAddrAssgntMethIdx_u8;

    /* Local variables initialization */
    lActiveLocalAddrMappedToCtrl_u8 = 0;
    lTotalActiveLocalAddr_u8        = 0;

    /* Retrieve the local address configuration pointer*/
    lLocalAddrConfig_pcst   = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* If all other localAddress mapped to the EthIfCtrl has no IP assigned set the Ctrl state to OFFLINE  */
    for( lIdx_u16 = 0; lIdx_u16 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ); lIdx_u16++ )
    {
        /* Count localAddress which has IP assigned */
        if( TCPIP_IPADDR_ASSIGNMENT_INVALID != ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx_u16].CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en ) )
        {
            lTotalActiveLocalAddr_u8++;

            /* Count the number of active localAddr mapped to the requested TcpIpCtrl */
            if( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 == TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx_u16].EthIfCtrlRef_u8 )
            {
                lActiveLocalAddrMappedToCtrl_u8++;
            }
        }
    }

    /* If no other localAddress has Ipassigned close all the socket. If LocalAddrId is set to TCPIP_LOCALADDRID_INVALID */
    /* rba_EthUdp_TerminateSocUsingLocalAddr() and rba_EthTcp_AbortByLocalAddrId() will close all the sockets */
    if(1u == lTotalActiveLocalAddr_u8)
    {
        /* Close all sockets, except Dhcp client  */
        #if (TCPIP_TCP_ENABLED == STD_ON)
        rba_EthTcp_AbortByLocalAddrId(TCPIP_LOCALADDRID_INVALID);
        #endif

        #if (TCPIP_UDP_ENABLED == STD_ON)
        rba_EthUdp_TerminateSocUsingLocalAddr(TCPIP_LOCALADDRID_INVALID);
        #endif
    }
    else
    {
        /* Close all sockets using this localAddrId, except Dhcp client */
        #if (TCPIP_TCP_ENABLED == STD_ON)
        rba_EthTcp_AbortByLocalAddrId(LocalAddrId_u8);
        #endif

        #if (TCPIP_UDP_ENABLED == STD_ON)
        rba_EthUdp_TerminateSocUsingLocalAddr(LocalAddrId_u8);
        #endif
    }

    /* Release IP address by setting the IP address to ZERO. */
    ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en )    = TCPIP_IPADDR_ASSIGNMENT_INVALID;
    ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8 )    = TCPIP_IPADDR_ASSIGNPRIO_INVALID;

    switch(IpDomainType_cu32)
    {
        #if (TCPIP_IPV4_ENABLED == STD_ON)
        case TCPIP_AF_INET:
            ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 )     = TCPIP_IPADDR_ZERO;
            ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.DftRtr_u32 )     = TCPIP_IPADDR_ZERO;
            ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.NetMask_u32 )    = TCPIP_IPV4_NETMASK_INVALID;
        break;
        #endif
        #if (TCPIP_IPV6_ENABLED == STD_ON)
        case TCPIP_AF_INET6:
            rba_EthIPv6_SetIPv6AddrTo0(&(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.IpAddr_st.Addr_au32[0]));
            rba_EthIPv6_SetIPv6AddrTo0(&(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.DftRtr_st.Addr_au32[0]));
            ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.NetMask_u8 )    = 0;
        break;
        #endif
        default: /* not reacheable because the param is validated at function start */
        break;
    }

    /* Inform upper layer about un-assignment of IP address */
    SoAd_LocalIpAddrAssignmentChg( LocalAddrId_u8, TCPIP_IPADDR_STATE_UNASSIGNED );

    /* If there is no LocalAddrId mapped to the EthIfCtrl that has IP address assigned, then change the state of that EthIfCtrl to OFFLINE */
    if(1u == lActiveLocalAddrMappedToCtrl_u8)
    {
        #if (TCPIP_ARP_ENABLED == STD_ON)
        if( lLocalAddrConfig_pcst->IpDomainType_u32 == TCPIP_AF_INET ) /* ARP APIs cannot be called at all for IPv6 addresses */
        {
            /* Clean the ARP table corresponding to the current EthIf controller */
            rba_EthArp_CleanArpTable( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ); /* Applicable only for IPv4 specific addresses */
        }
        #endif

        /* Set the Ctrl state to OFFLINE */
        TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8] = TCPIP_STATE_OFFLINE;

        /* Inform EthSM about change in Ctrl state to OFFLINE */
        (void)EthSM_TcpIpModeIndication( lLocalAddrConfig_pcst->EthIfCtrlRef_u8,
                                         TCPIP_STATE_OFFLINE );

      /* If the local Address has an assignment method with trigger AUTOMATIC try to retrigger IP assignment */
    }else if( (TCPIP_STATE_OFFLINE != TcpIp_EthIfCtrlReqSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8]) &&   /* If the TcpIpCtrl requested state is ONLINE or ONHOLD  */
              (TCPIP_UNICAST == lLocalAddrConfig_pcst->IpAddressType_en) )                                   /* If the localAddress is of type UNICAST                */
    {
        /* Loop through all AddressAssignments configured for the requested LocalAddress */
        for( lAddrAssgntMethIdx_u8 = 0; (lAddrAssgntMethIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8); lAddrAssgntMethIdx_u8++ )
        {
            /* If the IP assignment trigger is AUTOMATIC set the corresponding bit. */
            if(TCPIP_AUTOMATIC == (lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentTrig_en) )
            {
                (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8) |=  ((uint8)(1u << lAddrAssgntMethIdx_u8)) ;
            }
        }

        TcpIp_InitiateIpAssgn(LocalAddrId_u8);
    }
    else
    {   /* Do nothing */
    }
}

/********************************************************************************************************************/
/* TcpIp_IpAddr_StopCurrAssigned() -   This API is called from function TcpIp_IpAddr_StateAssigned()                */
/*                                    to stop all lower priority current assigned IP addresses.                     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8      - Local address index for which IP address assignment shall be stopped.                     */
/*  IPAsgnPrioNew_u8    - new assignment priority (Lower the value higher the priority).                            */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*                      void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( void, RBA_ETHIF_CODE ) TcpIp_IpAddr_StopCurrAssigned(  VAR( TcpIp_LocalAddrIdType,            AUTOMATIC )   LocalAddrId_u8,
                                                                    VAR( TcpIp_AssignmentPrio_tu8,         AUTOMATIC )   IPAsgnPrioNew_u8  )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( uint16,                                  AUTOMATIC )   lIdx_u16;

    /* Retrieve the local address configuration pointer*/
    lLocalAddrConfig_pcst   = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* Loop through all the current assigned IP addresses */
    for( lIdx_u16 = 0; lIdx_u16 < ( lLocalAddrConfig_pcst->NumAddrAsgnment_u8 ); lIdx_u16++ )
    {
        /* If any other address assignment process (lower priority) is triggered but not yet completed, then stop that process */
        if( IPAsgnPrioNew_u8 < ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AsgnmentPrio_u8 ) )
        {
            if( ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AddrAsgnmentMeth_en ) ) ||
            ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AddrAsgnmentMeth_en ) ) )
            {
                /* Stop AutoIp process */
                #if ( TCPIP_AUTOIP_ENABLED == STD_ON )
                (void)rba_EthAutoIp_Stop( LocalAddrId_u8 );
                #endif
            }
            else if( TCPIP_IPADDR_ASSIGNMENT_DHCP == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lIdx_u16].AddrAsgnmentMeth_en ) )
            {
                /* Stop Dhcp process */
                #if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
                (void)rba_EthDHCP_Stop( LocalAddrId_u8 );
                #endif
            }
            else
            {   /* No actions required in case of STATIC IP address */
            }
        }
    }
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

