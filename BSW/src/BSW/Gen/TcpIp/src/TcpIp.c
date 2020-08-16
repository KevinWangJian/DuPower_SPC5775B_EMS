
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_ARP_ENABLED == STD_ON )
#include "rba_EthArp.h"
#endif

#if ( TCPIP_NDP_ENABLED == STD_ON )
#include "rba_EthNdp.h"
#endif

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif

#if ( TCPIP_UDP_ENABLED == STD_ON )
#include "rba_EthUdp.h"
#endif

#if ( TCPIP_TCP_ENABLED == STD_ON )
#include "rba_EthTcp.h"
#endif

#if ( TCPIP_ICMP_ENABLED == STD_ON )
#include "rba_EthIcmp.h"
#endif

#if ( TCPIP_ICMPV6_ENABLED == STD_ON )
#include "rba_EthIcmpV6.h"
#endif

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#include "TcpIp_Prv.h"

#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* ( TCPIP_DEV_ERROR_DETECT != STD_OFF ) */

/*
 ***************************************************************************************************
 * Global Variables
 ***************************************************************************************************
 */

#define TCPIP_START_SEC_VAR_INIT_8
#include "TcpIp_MemMap.h"
/* Flag to indicate whether TcpIp_Init has been executed or not since power ON */
VAR( boolean,     TCPIP_VAR )                         TcpIp_InitFlag_b   = FALSE;
#define TCPIP_STOP_SEC_VAR_INIT_8
#include "TcpIp_MemMap.h"


#define TCPIP_START_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"
P2CONST( TcpIp_ConfigType, TCPIP_VAR, TCPIP_VAR )   TcpIp_CurrConfig_pco = NULL_PTR;
#define TCPIP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_VAR_INIT_32
#include "TcpIp_MemMap.h"
VAR( uint32,                        TCPIP_VAR )    TcpIp_RandNumSeed1_u32 = 100uL;
VAR( uint32,                        TCPIP_VAR )    TcpIp_RandNumSeed2_u32 = 200uL;
#define TCPIP_STOP_SEC_VAR_INIT_32
#include "TcpIp_MemMap.h"

/*********************************************************************************************************************/
/*                                                                                                                   */
/* TcpIp_Init()     - This service initializes the TCP/IP Stack. TcpIp_Init may not block the start-up process for   */
/*                  an indefinite amount of time.                                                                    */
/*                                                                                                                   */
/* Input Parameters :                                                                                                */
/* ConfigPtr        - Pointer to the configuration data of the TcpIp module.                                         */
/*                                                                                                                   */
/* Output Parameters :  void                                                                                         */
/*                                                                                                                   */
/*********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
void TcpIp_Init(    P2CONST( TcpIp_ConfigType, AUTOMATIC, AUTOMATIC )   ConfigPtr )
{
    /* Local variable declaration */
    P2VAR( TcpIp_CurrAsgnedAddr_tst, AUTOMATIC, AUTOMATIC )       lCurrAsgnedAddr_pst;
    VAR( uint8, AUTOMATIC )                     lIdx1_u8;

    /* Local variable initialization. */
    TcpIp_InitFlag_b           	= FALSE;
    TcpIp_CurrConfig_pco        = NULL_PTR;

#if ( TCPIP_CFG_CONFIGURATION_VARIANT != TCPIP_CFG_VARIANT_PRE_COMPILE )

    #if ( TCPIP_DEV_ERROR_DETECT == STD_ON )

    boolean lCfgValid_b = FALSE;

    for( lIdx1_u8 = 0; lIdx1_u8 < TCPIP_NUM_CONFIG; lIdx1_u8++ )
    {
        if ( ( &TcpIp_ConfigSet[lIdx1_u8] ) == ConfigPtr ) /* TcpIp_Config is the post build dataset */
        {
            lCfgValid_b = TRUE;
            break;
        }
    }

    /* Report DET if ConfigPtr does not contain a valid configuration */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( FALSE == lCfgValid_b ), TCPIP_E_INIT_API_ID, TCPIP_E_INIT_FAILED )

    #endif /* #if (TCPIP_DEV_ERROR_DETECT  == STD_ON) */

    TcpIp_CurrConfig_pco = ConfigPtr;

#else

    /* Report DET if ConfigPtr is not NULL_PTR */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR != ConfigPtr ), TCPIP_E_INIT_API_ID, TCPIP_E_INIT_FAILED )

    /* If the variant is pre-compile (NULL_PTR is passed as input parameter), */
    /* intialize global configuration pointer with default configuration. */
    TcpIp_CurrConfig_pco = &TcpIp_ConfigSet[0];

    /* Ignore passed parameter. */
    (void)ConfigPtr;

#endif

    /* Copy configured IP address table to RAM. Because it should also be possible to change IP addresses during runtime */
    for( lIdx1_u8 = 0; ( lIdx1_u8 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ); lIdx1_u8++ )
    {
        /* Initialise the pointer */
        lCurrAsgnedAddr_pst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8].CurrAsgnedAddr_pst );

		switch(TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8].IpDomainType_u32)
		{
			#if (TCPIP_IPV4_ENABLED == STD_ON)
			case TCPIP_AF_INET:
				( lCurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.DftRtr_u32 )   = TCPIP_IPADDR_ZERO;
				( lCurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 )   = TCPIP_IPADDR_ZERO;
				( lCurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.NetMask_u32 )  = TCPIP_IPV4_NETMASK_INVALID;
			break;
			#endif

			#if (TCPIP_IPV6_ENABLED == STD_ON)
			case TCPIP_AF_INET6:
				rba_EthIPv6_SetIPv6AddrTo0(&(lCurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.IpAddr_st.Addr_au32[0]));
				rba_EthIPv6_SetIPv6AddrTo0(&(lCurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.DftRtr_st.Addr_au32[0]));
				lCurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.NetMask_u8 = 0;
			break;
			#endif

			default:
			    /* Do nothing */
			break;
		}

        ( lCurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8 )  = TCPIP_IPADDR_ASSIGNPRIO_INVALID;
        ( lCurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en )  = TCPIP_IPADDR_ASSIGNMENT_INVALID;
        ( lCurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8 )    = 0x00;
    }

    /* Set all EthIf controller state configured in TcpIp to TCPIP_STATE_OFFLINE */
    for( lIdx1_u8 = 0; lIdx1_u8 < TCPIP_NUMETHIFCTRL; lIdx1_u8++ )
    {
        TcpIp_EthIfCtrlSt_aen[lIdx1_u8]     = TCPIP_STATE_OFFLINE;
        TcpIp_EthIfCtrlReqSt_aen[lIdx1_u8]  = TCPIP_STATE_OFFLINE;
    }

	#if (TCPIP_IPV4_ENABLED == STD_ON)
    rba_EthIPv4_Init( TcpIp_CurrConfig_pco->EthIPv4Config_pco );
	#endif

	#if (TCPIP_IPV6_ENABLED == STD_ON)
    rba_EthIPv6_Init( TcpIp_CurrConfig_pco->EthIPv6Config_pco );
	#endif

    #if (TCPIP_ARP_ENABLED == STD_ON)
    rba_EthArp_Init( TcpIp_CurrConfig_pco->EthArpConfig_pco );
    #endif

	#if (TCPIP_UDP_ENABLED == STD_ON)
    rba_EthUdp_Init( TcpIp_CurrConfig_pco->EthUdpConfig_pco );
    #endif

	#if (TCPIP_TCP_ENABLED == STD_ON)
    rba_EthTcp_Init( TcpIp_CurrConfig_pco->EthTcpConfig_pco );
    #endif

	#if (TCPIP_AUTOIP_ENABLED == STD_ON)
    rba_EthAutoIp_Init( TcpIp_CurrConfig_pco->EthAutoIpConfig_pco );
    #endif

    #if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
    rba_EthDHCP_Init( TcpIp_CurrConfig_pco->EthDHCPConfig_pco );
    #endif

	#if (TCPIP_ICMP_ENABLED == STD_ON)
    rba_EthIcmp_Init( TcpIp_CurrConfig_pco->EthIcmpConfig_pco );
    #endif

    #if (TCPIP_ICMPV6_ENABLED == STD_ON)
    rba_EthIcmpV6_Init( TcpIp_CurrConfig_pco->EthIcmpV6Config_pco );
    #endif

    #if (TCPIP_NDP_ENABLED == STD_ON)
    rba_EthNdp_Init( TcpIp_CurrConfig_pco->EthNdpConfig_pco );
    #endif

    /* Set a flag, to indicate that the TcpIp_Init() has been called */
    TcpIp_InitFlag_b = TRUE;

    TcpIp_RandNumSeed1_u32 = 100uL;
    TcpIp_RandNumSeed2_u32 = 200uL;

    return;
}






/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_MainFunction  - Schedules the TCP/IP stack. (Entry point for scheduling)                                   */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*                                                                                                                  */
/********************************************************************************************************************/

FUNC( void, TCPIP_CODE ) TcpIp_MainFunction( void )
{
    /* Check whether TcpIp_Init() has been called */
    if( FALSE != TcpIp_InitFlag_b )
    {
        TcpIp_StateMachine();

        #if ( TCPIP_TCP_ENABLED == STD_ON )
        rba_EthTcp_MainFunction();
        #endif

        #if ( TCPIP_ARP_ENABLED == STD_ON )
        rba_EthArp_MainFunction();
        #endif

        #if ( TCPIP_AUTOIP_ENABLED == STD_ON )
        rba_EthAutoIp_MainFunction();
        #endif

        #if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
        rba_EthDHCP_MainFunction();
        #endif

        #if ( defined(RBA_ETHIPV4_REASSEMBLY_ENABLED) && ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) )
        rba_EthIPv4_MainFunction();
        #endif

        #if ( TCPIP_NDP_ENABLED == STD_ON )
        rba_EthNdp_MainFunction();
        #endif
    }
    return;
}



/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_AllocBaseIpAddr()  - This API provides the interface between SoAd and the rba_EthAutoIp module,            */
/*                            to provide the baseIp address stored in the NVM.                                      */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* LocalAddrId_u8       - Local address id reference to IPv4 address config and EthIf controller index              */
/* IpAddrAsgnMethType_en - Address assignment method (Static/DHCP/AutoIp) used by this LocalAddrId                  */
/* LocalIpAddr_pst          - Pointer holding the BaseIp address to be used by the AutoIp                           */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  NIL                                                                                                             */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - Request processed successfully                                                   */
/*                          E_NOT_OK - Request NOT processed successfully                                           */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_AllocBaseIpAddr(
                                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                     LocalAddrId_u8,
                                                VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )                IpAddrAsgnMethType_en,
                                                P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         LocalIpAddr_pst        )
{

    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )       lRetVal_en;
    lRetVal_en = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_ALLOC_BASE_IPADDR_API_ID,        \
    		                          TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),  \
    		                          TCPIP_E_ALLOC_BASE_IPADDR_API_ID , TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if LocalIpAddr_pst is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == LocalIpAddr_pst ), TCPIP_E_ALLOC_BASE_IPADDR_API_ID,      \
    		                          TCPIP_E_NULL_PTR, E_NOT_OK )


    #if ( TCPIP_AUTOIP_ENABLED == STD_ON )
	{
	    P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )   lIPv4IPAddrPort_pst = NULL_PTR;

        if( ( (TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL == IpAddrAsgnMethType_en) ||
              (TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP == IpAddrAsgnMethType_en) ) &&
            ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].IpDomainType_u32  == LocalIpAddr_pst->domain ) )
        {
            /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrInetType to match the local parameter Type definition */
            lIPv4IPAddrPort_pst = ( (const TcpIp_SockAddrInetType * ) LocalIpAddr_pst ) ;

            /* Check whether the IP address of the remote node is in the AutoIp address range */
            if( ( TCPIP_AUTOIP_RANGE_START          <= ( lIPv4IPAddrPort_pst->addr[0] ) ) &&
                ( ( lIPv4IPAddrPort_pst->addr[0] )  <= TCPIP_AUTOIP_RANGE_END ) )
            {
                lRetVal_en = rba_EthAutoIp_AllocBaseIpAddr( LocalAddrId_u8, lIPv4IPAddrPort_pst );
            }
        }
	}
    #endif

    return lRetVal_en;
}

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_GetCtrlIdx()  - TcpIp_GetCtrlIdx returns the index of the controller related to LocalAddrId.               */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* LocalAddrId       - Local address identifier implicitly specifying the EthIf controller that shall be returned.  */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/* CtrlIdxPtr        - Pointer to the memory where the index of the controller related to LocalAddrId is stored     */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - Request processed successfully                                                   */
/*                          E_NOT_OK - Request NOT processed successfully                                           */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_GetCtrlIdx(
                                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                   LocalAddrId,
                                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      CtrlIdxPtr )
{
    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )                lRetVal_en;

    /* Initialize local variables */
    lRetVal_en = E_NOT_OK;

    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_GET_CTRLIDX_API_ID,                   \
                                      TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),          \
                                        TCPIP_E_GET_CTRLIDX_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if CtrlIdxPtr is a null pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == CtrlIdxPtr ), TCPIP_E_GET_CTRLIDX_API_ID,                      \
                                      TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Fetch the EthIf CtrlIdx corresponding to the LocalAddrId */
    ( *( uint8 * ) CtrlIdxPtr ) = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId].EthIfCtrlRef_u8 );

    /* return E_OK */
    lRetVal_en = E_OK;

    return ( lRetVal_en );
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */


/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

