
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED
#include "SoAd.h"
#include "SoAd_Cbk.h"
#include "EthIf.h"

#if ( TCPIP_ARP_ENABLED == STD_ON )
#include "rba_EthArp.h"
#endif

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#include "TcpIp_Prv.h"

#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched - SoAd and TcpIp"
#endif
#if (!defined(SOAD_AR_RELEASE_MINOR_VERSION) || (SOAD_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched - EthIf and TcpIp"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - EthIf and TcpIp"
#endif

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"

static FUNC( void, TCPIP_CODE ) TcpIp_StTransStartUpToOffline(VAR( TcpIp_LocalAddrIdType, AUTOMATIC )           LocalAddrId_u8 );

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_StartIPAssign( VAR( TcpIp_LocalAddrIdType,       AUTOMATIC )    LocalAddrId_u8,
                                                               VAR( TcpIp_IpAddrAssignmentType,  AUTOMATIC )    AddrAssignment_Meth_en );

/********************************************************************************************************************/
/* TcpIp_StateMachine() - This API is called from TcpIp_MainFunction(). The TcpIp_RequestComMode() stores the state */
/*                      transition requests from EthSM and are processed in TcpIp_StateMachine()                    */
/*                                                                                                                  */
/* Input Parameters : void                                                                                          */
/*                                                                                                                  */
/* Return           : void                                                                                          */
/*                                                                                                                  */
/********************************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN TcpIp_StateMachine: This API contains if-elseif-else-case for various combinations of TcpIp states and is not possible to avoid these HIS in-compliances.*/
FUNC( void, TCPIP_CODE ) TcpIp_StateMachine( void )
{
    /* Local variables declaration */
    VAR( TcpIp_StateType,       AUTOMATIC )                     lEthIfCtrlCurrSt_en;
    VAR( TcpIp_StateType,       AUTOMATIC )                     lEthIfCtrlStBeforeTrans_aen[TCPIP_NUMETHIFCTRL];
    VAR( TcpIp_StateType,       AUTOMATIC )                     lEthIfCtrlReqSt_en;
    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                     lLocalAddrId_u8;
    VAR( uint8, AUTOMATIC )                                     lEthIfCtrlIdx_u8;
    VAR( Std_ReturnType, AUTOMATIC )                            lStdRetType_en;
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( uint8, AUTOMATIC )                                     lAddrAssgntMethIdx_u8;

    /* Ctrl state will updated while looping though lLocalAddrId_u8(below), and required current state information will be lost */
    /* Hence it's necessary to have transition based on the locally stored initial controller state */
    for( lEthIfCtrlIdx_u8 = 0; lEthIfCtrlIdx_u8 <TCPIP_NUMETHIFCTRL ; lEthIfCtrlIdx_u8++)
    {
        lEthIfCtrlStBeforeTrans_aen[lEthIfCtrlIdx_u8] = TcpIp_EthIfCtrlSt_aen[lEthIfCtrlIdx_u8];
    }

    /* Loop through all configured LocalAddr */
    for( lLocalAddrId_u8 = 0; lLocalAddrId_u8 < TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ; lLocalAddrId_u8++ )
    {
        lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + lLocalAddrId_u8 );

        lEthIfCtrlCurrSt_en   = ( lEthIfCtrlStBeforeTrans_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] );
        lEthIfCtrlReqSt_en    = ( TcpIp_EthIfCtrlReqSt_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8  ] );

        /************ Initiate IP assignment for the local Address ************/
        if( (TCPIP_STATE_ONLINE == lEthIfCtrlReqSt_en) &&                                         /* Initiate IP assignment only if requested state is TCPIP_STATE_ONLINE */
            ( (TCPIP_STATE_OFFLINE == lEthIfCtrlCurrSt_en) ||                                     /* Condition for assignment of AUTOMATIC IP                             */
              (0x00u != lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8) ) )       /* Condition for assignment of MANUAL IP                                */
        {
            /* Loop through all AddressAssignments configured for the requested LocalAddress */
            /* If the current state is TCPIP_STATE_OFFLINE */
            for( lAddrAssgntMethIdx_u8 = 0;
                  (( lAddrAssgntMethIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8) && (TCPIP_STATE_OFFLINE == lEthIfCtrlCurrSt_en));
                    lAddrAssgntMethIdx_u8++ )
            {
                /* If the IP assignment trigger is AUTOMATIC set the corresponding bit. */
                /* Note: This bit is also set by TcpIp_RequestIpAddrAssignment() for MANUAL IP assignment trigger.    */
                if(TCPIP_AUTOMATIC == (lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentTrig_en) )
                {
                    (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8) |=  ((uint8)(1u << lAddrAssgntMethIdx_u8)) ;
                }
            }

            if (TCPIP_STATE_OFFLINE == TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8])
            {
                TcpIp_EthIfCtrlSt_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] = TCPIP_STATE_STARTUP;
            }

            TcpIp_InitiateIpAssgn( lLocalAddrId_u8 );
        }

        /******************************* Transition from TCPIP_STATE_STARTUP to TCPIP_STATE_OFFLINE ************************************/
        else if( ( TCPIP_STATE_STARTUP == lEthIfCtrlCurrSt_en ) && ( TCPIP_STATE_OFFLINE == lEthIfCtrlReqSt_en ) )
        {
            TcpIp_StTransStartUpToOffline( lLocalAddrId_u8 );
        }

        /************************************ Transition from TCPIP_STATE_ONLINE to TCPIP_STATE_ONHOLD ************************************/
        else if( ( TCPIP_STATE_ONLINE == lEthIfCtrlCurrSt_en ) && ( TCPIP_STATE_ONHOLD == lEthIfCtrlReqSt_en ) )
        {
            /* Check whether this LocalAddress has IP assigned already */
            if(TCPIP_IPADDR_ASSIGNMENT_INVALID != lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en)
            {
                TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] = TCPIP_STATE_ONHOLD;

                /* Inform SoAd that corresponding LocalAddress has enter ONHOLD state */
                SoAd_LocalIpAddrAssignmentChg( lLocalAddrId_u8, TCPIP_IPADDR_STATE_ONHOLD );
            }
        }

        /************************************ Transition from TCPIP_STATE_ONHOLD to TCPIP_STATE_ONLINE ************************************/
        else if( ( TCPIP_STATE_ONHOLD == lEthIfCtrlCurrSt_en ) && ( TCPIP_STATE_ONLINE == lEthIfCtrlReqSt_en ) )
        {
            /* Check whether this LocalAddress has IP assigned already */
            if(TCPIP_IPADDR_ASSIGNMENT_INVALID != lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en)
            {
                TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] = TCPIP_STATE_ONLINE;

                /* Inform SoAd that corresponding LocalAddress has enter ONLINE state */
                SoAd_LocalIpAddrAssignmentChg( lLocalAddrId_u8, TCPIP_IPADDR_STATE_ASSIGNED );
            }
        }

        /****************************** Transition from TCPIP_STATE_ONLINE/TCPIP_STATE_ONHOLD to TCPIP_STATE_OFFLINE ******************************/
        else if( ( (TCPIP_STATE_ONLINE == lEthIfCtrlCurrSt_en) || (TCPIP_STATE_ONHOLD == lEthIfCtrlCurrSt_en) ) &&
                 ( TCPIP_STATE_OFFLINE == lEthIfCtrlReqSt_en ) )
        {
            lStdRetType_en = TcpIp_ReleaseIpAddrAssignment( lLocalAddrId_u8 );

            /* If the TcpIpCtrl has not yet gone to TCPIP_STATE_OFFLINE, set it to TCPIP_STATE_SHUTDOWN */
            /* TcpIpCtrl can enter state TCPIP_STATE_OFFLINE in this context only if it has only STATIC IP assigned */
            if((E_OK == lStdRetType_en) &&
               (TCPIP_STATE_OFFLINE != TcpIp_EthIfCtrlSt_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ]))
             {
                 /* Set the TcpIpCtrl state to SHUTDOWN */
                 ( TcpIp_EthIfCtrlSt_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] ) = TCPIP_STATE_SHUTDOWN ;
             }
        }
        else
        {
            /* Do nothing */
        }

    }

    return;
}


/********************************************************************************************************************/
/*TcpIp_InitiateIpAssgn() -This API is called from TcpIp_StateMachine(). This API triggers IP address assignment for*/
/*                          the LocalAddress.                                                                       */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8     - Idx of the LocalAddress for which IP needs to be assigned.                                 */
/*                                                                                                                  */
/* Return  :            void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/

FUNC( void, TCPIP_CODE ) TcpIp_InitiateIpAssgn( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )         LocalAddrId_u8 )
{
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )       lLocalAddrConfig_pcst;
    VAR( Std_ReturnType,                          AUTOMATIC )       lStdRetType_en;
    VAR( uint8,                                   AUTOMATIC )       lAddrAssgntMethIdx_u8;
    boolean                                                         lDhcpAlreadyAssigned_b;

    /* Initialize local variables */
    lStdRetType_en            = E_NOT_OK;
    lDhcpAlreadyAssigned_b    = FALSE;

    /* Initialize the pointer to the local address configuration structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* If Dhcp IP is alreday assigned, release the IP before assigning new one */
    /* This is required as Dhcp release frame should have assigned Dhcp IP in the source IP field of IP header */
    #if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
    if(TCPIP_IPADDR_ASSIGNMENT_DHCP ==  lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en)
    {
       (void)rba_EthDHCP_Stop(LocalAddrId_u8);

       lDhcpAlreadyAssigned_b = TRUE;
    }
    #endif

    /* Loop through all AddresAssignments configured for the requested LocalAddress */
    for( lAddrAssgntMethIdx_u8 = 0; ((lAddrAssgntMethIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8) && (lDhcpAlreadyAssigned_b == FALSE)); lAddrAssgntMethIdx_u8++ )
    {
        /* Initiate IP assignment for all assignment methods with trigger AUTOMATIC mapped to the EthIfCtrl OR */
        /* Manual IP assignment is requested for the corresponding address assignment */
        if( 0 != (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8 & ( (uint8)(1u << lAddrAssgntMethIdx_u8)) ) )
        {
            lStdRetType_en= TcpIp_StartIPAssign( LocalAddrId_u8,
                                                 lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentMeth_en );

            /* If the IP assignmnet process is initiated successfully clear the bit */
            if( E_OK == lStdRetType_en )
            {
                lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8 &= (uint8)( ~(uint8)(1U << lAddrAssgntMethIdx_u8) );
            }
        }
    }

    return;
}


/********************************************************************************************************************/
/* TcpIp_StTransStartUpToOffline() - This API is called from TcpIp_StateMachine(). It handles the transition        */
/*                      requests from STARTUP to OFFLINE.                                                           */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8     - Idx of the LocalAddress for which IP assignment process needs to be stopped                */
/*                                                                                                                  */
/* Return  :            void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/

static FUNC( void, TCPIP_CODE ) TcpIp_StTransStartUpToOffline( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )         LocalAddrId_u8 )
{
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )       lLocalAddrConfig_pcst;
    VAR( uint8,                                   AUTOMATIC )       lAddrAssgntMethIdx_u8;

    /* Initialize the pointer to the local address configuration structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* Loop through all AddresAssignments configured for the requested LocalAddress */
    for( lAddrAssgntMethIdx_u8 = 0; ( lAddrAssgntMethIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8 ); lAddrAssgntMethIdx_u8++ )
    {
        /* If AutoIp is configured for the LocalAddress, stop AutoIp process */
        if( ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentMeth_en ) ) ||
            ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentMeth_en ) ) )
        {
            #if (TCPIP_AUTOIP_ENABLED == STD_ON)
            (void)rba_EthAutoIp_Stop( LocalAddrId_u8 );
            #endif
        }
        /* If Dhcp is configured for the LocalAddress, stop Dhcp process */
        else if( TCPIP_IPADDR_ASSIGNMENT_DHCP == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentMeth_en ) )
        {
            #if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
            (void)rba_EthDHCP_Stop( LocalAddrId_u8 );
            #endif
        }
        else
        {
            /* Do nothing */
        }
    }

    /* Clear all structure members as EthSM has requested TCPIP_STATE_OFFLINE */
    ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8 )    = TCPIP_IPADDR_ASSIGNPRIO_INVALID;
    ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en )    = TCPIP_IPADDR_ASSIGNMENT_INVALID;
    ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8 )      = 0x00u;

	switch(lLocalAddrConfig_pcst->IpDomainType_u32)
	{
		#if (TCPIP_IPV4_ENABLED == STD_ON)
		case TCPIP_AF_INET:
			( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.DftRtr_u32 )   = TCPIP_IPADDR_ZERO;
			( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 )   = TCPIP_IPADDR_ZERO;
			( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.NetMask_u32 )  = TCPIP_IPV4_NETMASK_INVALID;
		break;
		#endif

		#if (TCPIP_IPV6_ENABLED == STD_ON)
		case TCPIP_AF_INET6:
			rba_EthIPv6_SetIPv6AddrTo0(&(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.IpAddr_st.Addr_au32[0]));
			rba_EthIPv6_SetIPv6AddrTo0(&(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.DftRtr_st.Addr_au32[0]));
			lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.NetMask_u8 = 0;
		break;
		#endif

		default:
		    /* Do nothing */
		break;
	}

    /* Set TcpIpCtrl state to OFFLINE */
    TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8] = TCPIP_STATE_OFFLINE;


    #if (TCPIP_ARP_ENABLED == STD_ON)
	if( lLocalAddrConfig_pcst->IpDomainType_u32 == TCPIP_AF_INET )
	{
		/* Clean the ARP table corresponding to the EthIf controller */
		rba_EthArp_CleanArpTable( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 );	/* Applicable only for IPv4 specific addresses */
	}
    #endif

    return;
}


/********************************************************************************************************************/
/* TcpIp_StartIPAssign() - This API is called from TcpIp_InitiateIpAssgn(). It starts the IP address assignment of  */
/*                          IP address assignment method AddrAssignment_Meth_en                                     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8        - Idx of the LocalAddress for which IP assignment process needs to be started             */
/* AddrAssignment_Meth_en - IP address assignment method                                                            */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - Request processed successfully                                                   */
/*                          E_NOT_OK - Request NOT processed successfully                                           */
/*                                                                                                                  */
/********************************************************************************************************************/

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_StartIPAssign( VAR( TcpIp_LocalAddrIdType,           AUTOMATIC )         LocalAddrId_u8,
                                                               VAR( TcpIp_IpAddrAssignmentType,      AUTOMATIC )         AddrAssignment_Meth_en )
{
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )       lLocalAddrConfig_pcst;
    VAR( Std_ReturnType,                          AUTOMATIC )       lStdRetType_en;

    lStdRetType_en = E_NOT_OK;

    /* Initialize the pointer to the local address configuration structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId_u8 );

    /* Initiation of AUTOIP assignment if the LocalAddress is configured so */
    if( ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL == AddrAssignment_Meth_en ) ||
        ( TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP ==  AddrAssignment_Meth_en ) )
    {
        #if (TCPIP_AUTOIP_ENABLED == STD_ON)
        lStdRetType_en = rba_EthAutoIp_Start( LocalAddrId_u8 );
        #endif
    }

    /* Initiation of DHCP assignment if the LocalAddress is configured so */
    else if( TCPIP_IPADDR_ASSIGNMENT_DHCP ==  AddrAssignment_Meth_en )
    {
        #if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
        lStdRetType_en = rba_EthDHCP_Start( LocalAddrId_u8 );
        #endif
    }
    /* Assignment of STATIC if the LocalAddress is configured so */
    else if( TCPIP_IPADDR_ASSIGNMENT_STATIC ==  AddrAssignment_Meth_en )
    {
        /* Initialize lStdRetType_en to E_OK */
        lStdRetType_en = E_OK;

        /* Check whether the LocalAddress is multicast. If yes, a MAC filter has to be added all the way down to the driver level */
        if( TCPIP_MULTICAST == lLocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_UpdateMulticastPhysFilter(lLocalAddrConfig_pcst, ADD_TO_FILTER);
        }

        /* Assign IP to the localAddress */
        if( E_OK == lStdRetType_en )
        {
            TcpIp_LocalIpAddrAssignmentChg( LocalAddrId_u8,
                                            TCPIP_IPADDR_STATE_ASSIGNED,
                                            lLocalAddrConfig_pcst->StaticIpAddr_pun,
                                            TCPIP_IPADDR_ASSIGNMENT_STATIC,
                                            lLocalAddrConfig_pcst->IpDomainType_u32);
        }
    }
    else
    {   /* Do nothing */
    }

    return lStdRetType_en;
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"


#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

