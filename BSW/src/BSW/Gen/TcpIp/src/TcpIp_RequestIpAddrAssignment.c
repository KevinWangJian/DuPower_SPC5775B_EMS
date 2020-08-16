
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#include "TcpIp_Prv.h"

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"

#if (TCPIP_IPV4_ENABLED == STD_ON)
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment_IPv4(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst );

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformMulticastIPAddrChecks_IPv4(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst );

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformUnicastIPAddrChecks_IPv4(
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8 );

static FUNC( void, TCPIP_CODE ) TcpIp_StoreIpAddrAssignment_IPv4(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst );
#endif /* TCPIP_IPV4_ENABLED */

#if (TCPIP_IPV6_ENABLED == STD_ON)
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment_IPv6(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst );

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformMulticastIPAddrChecks_IPv6(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst );

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformUnicastIPAddrChecks_IPv6(
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8 );

static FUNC( void, TCPIP_CODE ) TcpIp_StoreIpAddrAssignment_IPv6(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst );
#endif /* TCPIP_IPV6_ENABLED */


/********************************************************************************************************************/
/* TcpIp_RequestIpAddrAssignment() - This API stores the IP assignment requests for assignment methods with trigger MANUAL */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrId     - IP address index specifying the IP address for which an assignment shall be initiated.    */
/*      Type            - Type of IP address assignment which shall be initiated.                                   */
/*      LocalIpAddrPtr  - Pointer to structure containing the IP address which shall be assigned to EthIf controller*/
/*                        indirectly specified via LocalAddrId. Note: This parameter is only used in case the       */
/*                      parameters  Type is set to  TCPIP_IPADDR_ASSIGNMENT_STATIC, can be set to NULL_PTR otherwise*/
/*      Netmask        - Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation. Note: This*/
/*                       parameter is only used in case the parameter Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC.*/
/*      DefaultRouterPtr - Pointer to structure containing the IP address of the default router (gateway) which     */
/*                        shall be assigned. Note: This parameter is only used in case the parameter Type is set to */
/*                        TCPIP_IPADDR_ASSIGNMENT_STATIC, can be set to NULL_PTR otherwise.                         */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment(
                                            VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                 LocalAddrId,
                                            VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )            Type,
                                            P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     LocalIpAddrPtr,
                                            VAR( uint8, AUTOMATIC )                                 Netmask,
                                            P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     DefaultRouterPtr )
{
    /* Local variables declaration */
    VAR( Std_ReturnType, AUTOMATIC )                            lStdRetType_en;
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( uint8, AUTOMATIC )                                     lAddrAssignmentlIdx_u8; /* Stores the index of the assignment search */
    #if (TCPIP_IPV4_ENABLED == STD_ON)
    P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     lIPv4IPAddr_pcst;
    P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     lIPv4DefaultRouter_pcst;
    #endif
    #if (TCPIP_IPV6_ENABLED == STD_ON)
    P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    lIPv6IPAddr_pcst;
    P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    lIPv6DefaultRouter_pcst;
    #endif

    /* Report DET if TcpIp module is uninitialized */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Address of the requested LocalAddress configuration structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId );

    /* Check whether the requested IP assignment method is configured for the LocalAdddress */
	lStdRetType_en = E_NOT_OK; /* this is a flag that stores the result of the search */
    for( lAddrAssignmentlIdx_u8 = 0; (lAddrAssignmentlIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8) ; lAddrAssignmentlIdx_u8++ )
    {
        if( (TCPIP_MANUAL == lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssignmentlIdx_u8].AddrAsgnmentTrig_en) &&
            (Type == lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssignmentlIdx_u8].AddrAsgnmentMeth_en) )
        {
            lStdRetType_en = E_OK;
            break;
        }
    }

    /* Report DET if requested IP assignment method is not configured or IP assignment trigger is not MANUAL */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( E_NOT_OK == lStdRetType_en ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID,  TCPIP_E_INV_ARG, E_NOT_OK )

    /* If the TcpIpCtrl is TCPIP_STATE_SHUTDOWN, the API shall not accept any new IP assignment requests.          */
    /* API shall reject the request, if requested IP assignment is of lesser priority than the current assigned IP */
    if( ( lStdRetType_en == E_OK ) &&
		( ( TCPIP_STATE_SHUTDOWN == TcpIp_EthIfCtrlSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8] ) ||
        ( (lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssignmentlIdx_u8].AsgnmentPrio_u8) >= (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrPrio_u8) ) ) )
    {
        lStdRetType_en = E_NOT_OK;
    }

    /* If the requested IP assignment method is STATIC, validate static IP, default router IP and netmask */
    if( (E_OK == lStdRetType_en) && (TCPIP_IPADDR_ASSIGNMENT_STATIC == Type) )
    {
        /* Report DET if LocalIpAddrPtr is a Null Pointer */
        TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == LocalIpAddrPtr ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

        /* Report DET if domain of LocalIpAddrPtr is different than domain of current local IP address configuration */
        TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalIpAddrPtr->domain != lLocalAddrConfig_pcst->IpDomainType_u32 ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

        /* Report DET if domain of LocalIpAddrPtr is different than domain of current local IP address configuration */
        TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( NULL_PTR != DefaultRouterPtr ) && ( DefaultRouterPtr->domain != lLocalAddrConfig_pcst->IpDomainType_u32 ) ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

        /* Check domain here as address pointer is checked for null value */
        switch(LocalIpAddrPtr->domain)
        {
            #if (TCPIP_IPV4_ENABLED == STD_ON)
            case TCPIP_AF_INET:
                /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrInetType to match the local parameter Type definition */
                lIPv4IPAddr_pcst        = ( (  const TcpIp_SockAddrInetType * ) LocalIpAddrPtr );
                /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrInetType to match the local parameter Type definition */
				lIPv4DefaultRouter_pcst = ( ( const TcpIp_SockAddrInetType * ) DefaultRouterPtr );      /* Get full default IPv4 router info */

				lStdRetType_en          = TcpIp_RequestIpAddrAssignment_IPv4(lLocalAddrConfig_pcst, lIPv4IPAddr_pcst, Netmask, lIPv4DefaultRouter_pcst);
                break;
            #endif

            #if (TCPIP_IPV6_ENABLED == STD_ON)
            case TCPIP_AF_INET6:
                /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrInet6Type to match the local parameter Type definition */
                lIPv6IPAddr_pcst        = ( (  const TcpIp_SockAddrInet6Type * ) LocalIpAddrPtr );
                /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrInet6Type to match the local parameter Type definition */
				lIPv6DefaultRouter_pcst = ( ( const TcpIp_SockAddrInet6Type * ) DefaultRouterPtr );     /* Get full default IPv6 router info */

				lStdRetType_en          = TcpIp_RequestIpAddrAssignment_IPv6(lLocalAddrConfig_pcst, lIPv6IPAddr_pcst, Netmask, lIPv6DefaultRouter_pcst);
                break;
            #endif

            default:
                /* Domain type is invalid! Report error to DET */
                TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_AFNOSUPPORT )
				lStdRetType_en = E_NOT_OK;
                break;
        }

		/* Report DET if input parameters are invalid */
        TCPIP_DET_REPORT_ERROR_RET_VALUE( ( E_NOT_OK == lStdRetType_en ), TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID,  TCPIP_E_INV_ARG, E_NOT_OK )
	}

    /* Store the assignment request in bit form corresponding to index of configured assignment method array */
    if(E_OK == lStdRetType_en)
    {
        (lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8) |= ((uint8)(1u << lAddrAssignmentlIdx_u8)) ;
    }

    return ( lStdRetType_en );
}

#if (TCPIP_IPV4_ENABLED == STD_ON)
/********************************************************************************************************************/
/* TcpIp_RequestIpAddrAssignment_IPv4() - This is a helper function called by the TcpIp_RequestIpAddrAssignment() API*/
/*                        which performs all the IPv4 domain specific required validation checks and stores the 	*/
/*                        asignment request. The actual IP adress assignment will be performed by the 				*/
/*                        TcpIp_StateMachine() API.                                                              	*/
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv4 address config structure.                                  */
/*      IPv4IPAddr_pcst - Pointer to structure containing the IP address which shall be assigned to EthIf controller*/
/*                        indirectly specified via LocalAddrId.                                                     */
/*      Netmask_cu8     - Network mask of IPv4.                                                                     */
/*      IPv4DefaultRouter_pcst - Pointer to structure containing the IP address of the default router (gateway) which*/
/*                        shall be assigned. Note: This parameter is only used in case the parameter Type is set to */
/*                        TCPIP_IPADDR_ASSIGNMENT_STATIC, can be set to NULL_PTR otherwise.                         */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment_IPv4(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst )
{
	VAR( Std_ReturnType, AUTOMATIC ) lStdRetType_en = E_OK; /* Init with optimistic value; for each check failed, set to E_NOT_OK. */

	do
	{
		/* Discard the request, if the static IP to be assigned is                 */
		/* 1. 0x00000000                                                           */
		/* 2. Is loop back IP                                                      */
		/* 3. Reserved IP range 240.0.0.0/4 ( 0xffffffff  )                        */
		/* 4. AutoIp address                                                       */
		if ( (TCPIP_IPADDR_ZERO      == IPv4IPAddr_pcst->addr[0]) ||
			 (TCPIP_IPV4_LOOPBACK    == (IPv4IPAddr_pcst->addr[0] & TCPIP_IPV4_LOOPBACK_MASK))  ||
			 (TCPIP_IPV4_RESERVED_IP == (IPv4IPAddr_pcst->addr[0] & TCPIP_IPV4_RESERVED_IP)) ||
			 (TCPIP_AUTOIP_NET       == (IPv4IPAddr_pcst->addr[0] & TCPIP_AUTOIP_MASK)) )
		{
			lStdRetType_en = E_NOT_OK;
            break;
		}

        if( TCPIP_MULTICAST == LocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_PerformMulticastIPAddrChecks_IPv4( LocalAddrConfig_pcst, IPv4IPAddr_pcst );
            if (lStdRetType_en != E_OK)
            {
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
                break;
            }
        }

        if( TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_PerformUnicastIPAddrChecks_IPv4( IPv4IPAddr_pcst, IPv4DefaultRouter_pcst, Netmask_cu8 );
            if (lStdRetType_en != E_OK)
            {
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
                break;
            }
        }

		TcpIp_StoreIpAddrAssignment_IPv4( LocalAddrConfig_pcst, IPv4IPAddr_pcst, Netmask_cu8, IPv4DefaultRouter_pcst );
	}
	while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation. */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_PerformMulticastIPAddrChecks_IPv4() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv4*/
/* 										and performs some basic checks on the IPv4 address to be assigned of        */
/*                                      MULTICAST type.                                                             */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv4 address config structure.                                  */
/*      IPv4IPAddr_pcst      - Pointer to structure containing the IPv4 address which shall be assigned to EthIf    */
/*                        controller indirectly specified via LocalAddrId. 										    */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The specified IP address has passed all the multicast checks.						*/
/*                        E_NOT_OK: The specified IP address did not pass all the multicast checks.					*/
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformMulticastIPAddrChecks_IPv4(
                                                P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                                P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst )
{
	/* Local variables declaration */
    VAR( Std_ReturnType, AUTOMATIC )    lStdRetType_en = E_OK; /* Init with optimistic value; for each check failed, set to E_NOT_OK. */
    VAR( uint8, AUTOMATIC )             lLocalAddrId_u8;

	do
	{
		/* If LocalAddress is configured as multicast, Static IP shall be in multicast address range */
		if( (IPv4IPAddr_pcst->addr[0] < RBA_ETHIPV4_MULTICASTADDR_MIN) ||
			(IPv4IPAddr_pcst->addr[0] > RBA_ETHIPV4_MULTICASTADDR_MAX) )
		{
			lStdRetType_en = E_NOT_OK;
			break;
		}

		/* If the requested multicast IP to be assigned is already assigned to the EthIfCtrl return E_NOT_OK */
		for(lLocalAddrId_u8 = 0; lLocalAddrId_u8 < TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ; lLocalAddrId_u8++)
		{
			/* Do not assign requested IPv4 multicast address if:
				1. Current assigned EthIfCtrl index is the same with the requested EthIfCtrl index
				2. Current assigned IP address domain family is also TCPIP_AF_INET
				3. Current assigned IPv4 address is equal to the requested IPv4 address to be assigned */
			if( ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].EthIfCtrlRef_u8 == LocalAddrConfig_pcst->EthIfCtrlRef_u8 ) &&
				( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].IpDomainType_u32 == TCPIP_AF_INET ) &&
				( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 == IPv4IPAddr_pcst->addr[0] ) )
			{
                lStdRetType_en = E_NOT_OK;

                TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_ADDRINUSE )

				break;
			}
		}

		if ( lStdRetType_en == E_NOT_OK )
		{
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

		lStdRetType_en = E_OK;
	}
    while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation. */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_PerformUnicastIPAddrChecks_IPv4() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv4().*/
/* 							    It performs some basic checks on the IP address to be assigned of UNICAST type.     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      IPv4IPAddr_pcst - Pointer to structure containing the IPv4 address which shall be assigned to EthIf         */
/*                      controller indirectly specified via LocalAddrId. 										    */
/*      IPv4DefaultRouter_pcst - Pointer to structure containing the IPv4 address of the default router (gateway)   */
/*                      which shall be assigned.                        											*/
/*      Netmask_cu8     - Network mask of IPv4 address. 		                                                    */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The specified IP address has passed all the unicast checks.							*/
/*                        E_NOT_OK: The specified IP address did not pass all the unicast checks.					*/
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformUnicastIPAddrChecks_IPv4(
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8 )
{
	VAR( uint32, AUTOMATIC )			lNetmask_u32;
	VAR( Std_ReturnType, AUTOMATIC )	lStdRetType_en = E_OK; /* Init with optimistic value; for each check failed, set to E_NOT_OK. */

	do
	{
		/* -Netmask shall be in valid range (1 to 30)          */
		/* -Static IP shall not be in multicast address range  */
		if( (0 == Netmask_cu8) || (30u < Netmask_cu8) ||
			((IPv4IPAddr_pcst->addr[0] >= RBA_ETHIPV4_MULTICASTADDR_MIN) && (IPv4IPAddr_pcst->addr[0] <= RBA_ETHIPV4_MULTICASTADDR_MAX)) )
		{
			lStdRetType_en = E_NOT_OK;
			break;
		}

		/* Get netmask in 32 bit format */
		lNetmask_u32 = ( 0xFFFFFFFFuL << (TCPIP_NETMASK_MAX_VAL - Netmask_cu8) );

		if( (( (IPv4IPAddr_pcst->addr[0] & lNetmask_u32 )   == IPv4IPAddr_pcst->addr[0] ) ||     /* Static IP shall not be network address           */
			 ((IPv4IPAddr_pcst->addr[0] | (~lNetmask_u32) ) == IPv4IPAddr_pcst->addr[0])) )      /* Static IP shall not be network broadcast address */
		{
			lStdRetType_en = E_NOT_OK;
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

		/* If IPv4DefaultRouter_pcst pointer is not NULL, implies that default router is required and shall be within the valid range */
        /* The domain for the default router is already verified in a DET check in the main API */
		if( (NULL_PTR != IPv4DefaultRouter_pcst) )
		{
			if( ( (IPv4IPAddr_pcst->addr[0] & lNetmask_u32) != (IPv4DefaultRouter_pcst->addr[0] & lNetmask_u32) ) ||    /* Static IP and default router shall have same network address ( This implicitly covers - 0x0, loopback, reserved IP, AutoIp ) */
				( (IPv4DefaultRouter_pcst->addr[0] | (~lNetmask_u32) ) == IPv4DefaultRouter_pcst->addr[0] ) ||  /* Default router IP shall not be network broadcast address */
				( IPv4IPAddr_pcst->addr[0] == IPv4DefaultRouter_pcst->addr[0] ) ||                     /* Static IP and default router IP shall not be same */
				( (IPv4DefaultRouter_pcst->addr[0] & lNetmask_u32) == IPv4DefaultRouter_pcst->addr[0] ) )   /* Default router IP shall not be network address */
			{
				lStdRetType_en = E_NOT_OK;
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
				break;
			}

			/* Discard the request if default router IP is                             */
			/* 1. Is loop back IP                                                      */
			/* 2. Reserved IP range 240.0.0.0/4 ( 0xffffffff  )                        */
			/* 3. AutoIp address                                                       */
			/* 4. Multicast address                                                    */
			if ( (TCPIP_IPV4_LOOPBACK    == (IPv4DefaultRouter_pcst->addr[0] & TCPIP_IPV4_LOOPBACK_MASK))  ||
				 (TCPIP_IPV4_RESERVED_IP == (IPv4DefaultRouter_pcst->addr[0] & TCPIP_IPV4_RESERVED_IP)) ||
				 (TCPIP_AUTOIP_NET       == (IPv4DefaultRouter_pcst->addr[0] & TCPIP_AUTOIP_MASK)) ||
				 ( (IPv4DefaultRouter_pcst->addr[0] >= RBA_ETHIPV4_MULTICASTADDR_MIN) && (IPv4DefaultRouter_pcst->addr[0] <= RBA_ETHIPV4_MULTICASTADDR_MAX) ) )
			{
				lStdRetType_en = E_NOT_OK;
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
				break;
			}
		}
	}
    while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation. */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_StoreIpAddrAssignment_IPv4() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv4() and*/
/*                        stores the provided local IPv4 address, default router address and netmask info.          */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv4 address config structure.                                  */
/*      IPv4IPAddr_pcst - Pointer to structure containing the IP address which shall be assigned to EthIf controller*/
/*                        indirectly specified via LocalAddrId.                                                     */
/*      Netmask_cu8     - Network mask of IPv4.                                                                     */
/*      IPv4DefaultRouter_pcst - Pointer to structure containing the IP address of the default router (gateway) which*/
/*                        shall be assigned.                                                                        */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( void, TCPIP_CODE ) TcpIp_StoreIpAddrAssignment_IPv4(
                                        P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                        P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4IPAddr_pcst,
                                        CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                        P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )     IPv4DefaultRouter_pcst )
{
	LocalAddrConfig_pcst->StaticIpAddr_pun->IPv4Par_st.IpAddr_u32  = IPv4IPAddr_pcst->addr[0];
	LocalAddrConfig_pcst->StaticIpAddr_pun->IPv4Par_st.NetMask_u32 = TCPIP_IPV4_NETMASK_INVALID; /* Initializing with default value */
	LocalAddrConfig_pcst->StaticIpAddr_pun->IPv4Par_st.DftRtr_u32  = TCPIP_IPADDR_ZERO;          /* Initializing with default value */

	/* Netmask and default router are valid only for unicast IP */
	if(TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en)
	{
		LocalAddrConfig_pcst->StaticIpAddr_pun->IPv4Par_st.NetMask_u32 = ( 0xFFFFFFFFuL << (32u - Netmask_cu8));

		/* If IPv4DefaultRouter_pcst is not NULL store default router IP */
		if(NULL_PTR != IPv4DefaultRouter_pcst)
		{
			LocalAddrConfig_pcst->StaticIpAddr_pun->IPv4Par_st.DftRtr_u32 = IPv4DefaultRouter_pcst->addr[0];
		}
	}
}
#endif /* TCPIP_IPV4_ENABLED */


#if (TCPIP_IPV6_ENABLED == STD_ON)
/********************************************************************************************************************/
/* TcpIp_RequestIpAddrAssignment_IPv6() - This is a helper function called by the TcpIp_RequestIpAddrAssignment() API*/
/*                        which performs all the IPv6 domain specific required validation checks and stores the 	*/
/*                        asignment request. The actual IP adress assignment will be performed by the 				*/
/*                        TcpIp_StateMachine() API.                                                              	*/
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv6 address config structure.                                  */
/*      IPv6IPAddr_pcst - Pointer to structure containing the IP address which shall be assigned to EthIf controller*/
/*                        indirectly specified via LocalAddrId.                                                     */
/*      Netmask_cu8     - Mask prefix of IPv6 address in CIDR Notation.                                             */
/*      IPv6DefaultRouter_pcst - Pointer to structure containing the IP address of the default router (gateway) which*/
/*                        shall be assigned. Note: This parameter is only used in case the parameter Type is set to */
/*                        TCPIP_IPADDR_ASSIGNMENT_STATIC, can be set to NULL_PTR otherwise.                         */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment_IPv6(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                            CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst )
{
	VAR( Std_ReturnType, AUTOMATIC ) lStdRetType_en = E_OK; /* Init with optimistic value; for each check failed, set to E_NOT_OK. */

	do
	{
		/* Discard the request, if the static IP to be assigned is: */
		/* 1. 0x00000000 */
		if( ( IPv6IPAddr_pcst->addr[0] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[1] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[2] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[3] == 0uL ) )
		{
			lStdRetType_en = E_NOT_OK;
            break;
		}

		/* 2. Loop back IP  */
		if( ( IPv6IPAddr_pcst->addr[0] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[1] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[2] == 0uL ) &&
			( IPv6IPAddr_pcst->addr[3] == 1uL ) )
		{
			lStdRetType_en = E_NOT_OK;
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

        if( TCPIP_MULTICAST == LocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_PerformMulticastIPAddrChecks_IPv6( LocalAddrConfig_pcst, IPv6IPAddr_pcst );
            if ( lStdRetType_en != E_OK )
            {
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
                break;
            }
        }

        if( TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_PerformUnicastIPAddrChecks_IPv6( IPv6IPAddr_pcst, IPv6DefaultRouter_pcst, Netmask_cu8 );
            if ( lStdRetType_en != E_OK)
            {
				/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
                break;
            }
        }

		TcpIp_StoreIpAddrAssignment_IPv6( LocalAddrConfig_pcst, IPv6IPAddr_pcst, Netmask_cu8, IPv6DefaultRouter_pcst );
	}
	while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_PerformMulticastIPAddrChecks_IPv6() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv6*/
/* 										and performs some basic checks on the IPv6 address to be assigned of        */
/*                                      MULTICAST type.                                                             */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv6 address config structure.                                  */
/*      IPv6IPAddr_pcst      - Pointer to structure containing the IPv6 address which shall be assigned to EthIf    */
/*                        controller indirectly specified via LocalAddrId. 										    */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The specified IP address has passed all the multicast checks.						*/
/*                        E_NOT_OK: The specified IP address did not pass all the multicast checks.					*/
/*                                                                                                                  */
/* Steps:                                                                                                          	*/
/*		1. Check that whatever the multicast address type (Interface-Local, Link-Local, Global scoped), it is not a */
/* 		reserved IPv6 multicast address -> extract from RFC 4291, Section 2.7 (Multicast Addresses).				*/
/* 		2. Check that the requested IPv6 address is not already assigned for the local address index cfg.			*/
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformMulticastIPAddrChecks_IPv6(
                                            P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst )
{
	/* Local variables declaration */
    VAR( Std_ReturnType, AUTOMATIC ) lStdRetType_en = E_OK; /* Init with optimistic value; for each check failed, set to E_NOT_OK. */

	do
	{
		VAR( uint32, AUTOMATIC )    lfirstIpv6AddrByte_u32;
        VAR( uint8, AUTOMATIC )     lLocalAddrId_u8;

		/* 1. Check that whatever the multicast address type (Interface-Local, Link-Local, Global scoped),
			it is not a reserved IPv6 multicast address =>
			begins with 0xFF and the 'scop' field does NOT have one of the following values:
			a) 0x0  reserved
			b) 0x3  reserved
			c) 0xF  reserved */
		lfirstIpv6AddrByte_u32 = IPv6IPAddr_pcst->addr[0];
		if( ( ( lfirstIpv6AddrByte_u32 & TCPIP_IPV6_MULTICAST_MASK ) 		   != TCPIP_IPV6_MULTICAST_MASK ) ||	   		/* Must start with 0xFF (IPv6 multicast type) */
			( ( lfirstIpv6AddrByte_u32 & TCPIP_IPV6_MULTICAST_SCOP_FLAG_MASK ) == TCPIP_IPV6_MULTICAST_RESERVED_SCOP_0 ) || /* Must not start with 0xFF00 (reserved) */
			( ( lfirstIpv6AddrByte_u32 & TCPIP_IPV6_MULTICAST_SCOP_FLAG_MASK ) == TCPIP_IPV6_MULTICAST_RESERVED_SCOP_3 ) || /* Must not start with 0xFF03 (reserved) */
			( ( lfirstIpv6AddrByte_u32 & TCPIP_IPV6_MULTICAST_SCOP_FLAG_MASK ) == TCPIP_IPV6_MULTICAST_RESERVED_SCOP_F ) )  /* Must not start with 0xFF0F (reserved) */
		{
			lStdRetType_en = E_NOT_OK;
			break;
		}

		/* 2. If the requested multicast IP to be assigned is already assigned to the EthIfCtrl return E_NOT_OK */
		for(lLocalAddrId_u8 = 0; lLocalAddrId_u8 < TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ; lLocalAddrId_u8++)
		{
			/* Do not assign requested IPv6 multicast address if:
				1. Current assigned EthIfCtrl index is the same with the requested EthIfCtrl index
				2. Current assigned IP address domain family is also TCPIP_AF_INET6 */
			if( ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].EthIfCtrlRef_u8 == LocalAddrConfig_pcst->EthIfCtrlRef_u8 ) &&
				( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].IpDomainType_u32 == TCPIP_AF_INET6 ) )
			{
			/*  3. Current assigned IPv6 address is equal to the requested IPv6 address to be assigned */
				/* Call the comparison function only if the first 2 conditions are fulfilled. */
				if( TcpIp_IPv6AddrCompareWithMask(
					&( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lLocalAddrId_u8].CurrAsgnedAddr_pst->IpAddrParams_un.IPv6Par_st.IpAddr_st.Addr_au32[0] ),
					&( IPv6IPAddr_pcst->addr[0] ), TCPIP_IPV6_CIDR_MASK_128 ) != FALSE )
				{
				    TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_REQUEST_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_ADDRINUSE )
					lStdRetType_en = E_NOT_OK;
					break;
				}
			}
		}

		if (lStdRetType_en == E_NOT_OK)
		{
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

		lStdRetType_en = E_OK;
	}
	while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation. */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_PerformUnicastIPAddrChecks_IPv6() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv6().*/
/* 								It performs some basic checks on the IP address to be assigned of UNICAST type.     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      IPv6IPAddr_pcst - Pointer to structure containing the IPv6 address which shall be assigned to EthIf         */
/*                      controller indirectly specified via LocalAddrId. 										    */
/*      IPv6DefaultRouter_pcst - Pointer to structure containing the IPv6 address of the default router (gateway)   */
/*                      which shall be assigned.                        											*/
/*      Netmask_cu8     - Mask prefix of IPv6 address in CIDR Notation. 		                                    */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The specified IP address has passed all the unicast checks.							*/
/*                        E_NOT_OK: The specified IP address did not pass all the unicast checks.					*/
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_PerformUnicastIPAddrChecks_IPv6(
                                                P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                                P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst,
                                                CONST( uint8, AUTOMATIC )                                   Netmask_cu8 )
{
	VAR( Std_ReturnType, AUTOMATIC ) lStdRetType_en = E_OK;		/* Init with optimistic value; for each check failed, set to E_NOT_OK. */

	do
	{
		VAR( uint32, AUTOMATIC ) lfirstIpv6AddrByte_u32 = IPv6IPAddr_pcst->addr[0];

		/* Netmask must be in valid range: [1, 128] */
		if( (Netmask_cu8 == 0) || (Netmask_cu8 > TCPIP_IPV6_CIDR_MASK_128) )
		{
			lStdRetType_en = E_NOT_OK;
			break;
		}

		/* Static IP must not be of type Multicast (must not start with 0xFF) */
		if( (lfirstIpv6AddrByte_u32 & TCPIP_IPV6_MULTICAST_MASK) == TCPIP_IPV6_MULTICAST_MASK )
		{
			lStdRetType_en = E_NOT_OK;
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

		/* Static IP shall not be network address */
		if( TcpIp_IsIPv6AddrEqualToNetworkAddr( &(IPv6IPAddr_pcst->addr[0]), Netmask_cu8 ) != FALSE )
		{
			lStdRetType_en = E_NOT_OK;
			/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
			break;
		}

		/* If IPv6DefaultRouter_pcst pointer is not NULL, implies that default router is required and shall be within the valid range */
        /* The domain for the default router is already verified in a DET check in the main API */
		if( (NULL_PTR != IPv6DefaultRouter_pcst) )
		{
			/* Check Default router IPv6 address only if it is configured! (different than 0:0:0:0:0:0:0:0/128) */
			/* The 0:0:0:0:0:0:0:0/128 (Unspecified) IPv6 address for Default router is acceptable */
			if( ( ( IPv6DefaultRouter_pcst->addr[0] == 0uL ) &&
				  ( IPv6DefaultRouter_pcst->addr[1] == 0uL ) &&
				  ( IPv6DefaultRouter_pcst->addr[2] == 0uL ) &&
				  ( IPv6DefaultRouter_pcst->addr[3] == 0uL ) ) == FALSE )
			{
                /* Static IP and default router shall NOT have the same address */
                if( TcpIp_IPv6AddrCompareWithMask( &( IPv6IPAddr_pcst->addr[0] ), &( IPv6DefaultRouter_pcst->addr[0] ), TCPIP_IPV6_CIDR_MASK_128 ) != FALSE )
				{
					lStdRetType_en = E_NOT_OK;
					/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
					break;
				}

				/* Static IP and default router shall have same network address */
				if( TcpIp_IPv6AddrCompareWithMask( &( IPv6IPAddr_pcst->addr[0] ), &( IPv6DefaultRouter_pcst->addr[0] ), Netmask_cu8 ) == FALSE )
				{
					lStdRetType_en = E_NOT_OK;
					/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
					break;
				}

				/* Discard the request if default router IP is: */
				/* 1. Loop back IP (::1/128) */
				if( ( IPv6DefaultRouter_pcst->addr[0] == 0uL ) &&
					( IPv6DefaultRouter_pcst->addr[1] == 0uL ) &&
					( IPv6DefaultRouter_pcst->addr[2] == 0uL ) &&
					( IPv6DefaultRouter_pcst->addr[3] == 1uL ) )
				{
					lStdRetType_en = E_NOT_OK;
					/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
					break;
				}

				/* 2. Multicast address */
				if( ( IPv6DefaultRouter_pcst->addr[0] & TCPIP_IPV6_MULTICAST_MASK ) == TCPIP_IPV6_MULTICAST_MASK )
				{
					lStdRetType_en = E_NOT_OK;
					/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
					break;
				}

				/* 3. Network address */
				if( TcpIp_IsIPv6AddrEqualToNetworkAddr( &(IPv6DefaultRouter_pcst->addr[0]), Netmask_cu8 ) != FALSE )
				{
					lStdRetType_en = E_NOT_OK;
					/* MR12 RULE 15.4 VIOLATION: The break instruction is used to reduce the level of IF indentation. */
					break;
				}
			}
		}
	}
	while(FALSE); /* This is not a loop. This construct is used only to allow for break statements at each failed check. Reduces the level of IF() identation. */

	return lStdRetType_en;
}

/********************************************************************************************************************/
/* TcpIp_StoreIpAddrAssignment_IPv6() - This is a helper function called by TcpIp_RequestIpAddrAssignment_IPv6() and*/
/*                        stores the provided local IPv6 address, default router address and netmask info.          */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrConfig_pcst - Pointer to the local IPv6 address config structure.                                  */
/*      IPv6IPAddr_pcst - Pointer to structure containing the IP address which shall be assigned to EthIf controller*/
/*                        indirectly specified via LocalAddrId.                                                     */
/*      Netmask_cu8     - Mask prefix of IPv6 address in CIDR Notation.                                             */
/*      IPv6DefaultRouter_pcst - Pointer to structure containing the IP address of the default router (gateway)     */
/*                        which shall be assigned.                                                                  */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( void, TCPIP_CODE ) TcpIp_StoreIpAddrAssignment_IPv6(
                                    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                    P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6IPAddr_pcst,
                                    CONST( uint8, AUTOMATIC )                                   Netmask_cu8,
                                    P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC )    IPv6DefaultRouter_pcst )
{
	VAR( uint8, AUTOMATIC)  lLoopIndex_u8;

	for(lLoopIndex_u8 = 0; lLoopIndex_u8 < 4u; lLoopIndex_u8++)
	{
		/* Copy IPv6 address param to static IPv6 address config */
		LocalAddrConfig_pcst->StaticIpAddr_pun->IPv6Par_st.IpAddr_st.Addr_au32[lLoopIndex_u8] = IPv6IPAddr_pcst->addr[lLoopIndex_u8];

		/* Initialize Default Router IPv6 address with default value */
		LocalAddrConfig_pcst->StaticIpAddr_pun->IPv6Par_st.DftRtr_st.Addr_au32[lLoopIndex_u8] = 0;
	}

	LocalAddrConfig_pcst->StaticIpAddr_pun->IPv6Par_st.NetMask_u8 = 0;   /* Initialize netmask prefix with default value */

	/* Netmask and default router are valid only for unicast IP */
	if(TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en)
	{
		/* For the IPv6 structure, the netmask is stored in CIDR notation (prefix). */
		LocalAddrConfig_pcst->StaticIpAddr_pun->IPv6Par_st.NetMask_u8 = Netmask_cu8;

		/* If IPv6DefaultRouter_pcst is not NULL, store default router IP from received param */
		if(NULL_PTR != IPv6DefaultRouter_pcst)
		{
			for(lLoopIndex_u8 = 0; lLoopIndex_u8 < 4u; lLoopIndex_u8++)
			{
				LocalAddrConfig_pcst->StaticIpAddr_pun->IPv6Par_st.DftRtr_st.Addr_au32[lLoopIndex_u8] = IPv6DefaultRouter_pcst->addr[lLoopIndex_u8];
			}
		}
	}
}

#endif /* TCPIP_IPV6_ENABLED */


#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

