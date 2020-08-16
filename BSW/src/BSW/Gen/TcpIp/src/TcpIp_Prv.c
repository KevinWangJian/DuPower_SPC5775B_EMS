

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#include "TcpIp_Prv.h"
#include "EthIf.h"

#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched - EthIf and TcpIp"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - EthIf and TcpIp"
#endif

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif


/********************************************************************************************************************/
/* TcpIp_CheckValidityOfLocalAddrId()  - This API checks whether the IP address mapped to the LocalAddrId is valid  */
/*                                                                                                                  */
/* Input Parameters : 																			  					*/
/*	LocalAddrId_u8 		- Local address id reference to IPv4 address config and EthIf controller index  			*/
/*                                                                                                                  */
/* Output Parameters : 																			  					*/
/*                                                                                                                  */
/* Std_ReturnType 		- 	Result of operation																		*/
/*                          E_OK - The out parameter - LocalAddrId_u8 has a valid IP address                        */
/*                          E_NOT_OK - The out parameter - LocalAddrId_u8 has a invalid IP address                  */
/*                                                                                                                  */
/********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_CheckValidityOfLocalAddrId( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )    LocalAddrId_u8 )
{
	/* Local variable declaration */
	VAR( Std_ReturnType, AUTOMATIC )       	lRetVal_en;

    /* Local variable initialisation */
    lRetVal_en = E_NOT_OK;

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),          \
                                      TCPIP_E_CHECK_VALIDITY_OF_LOCALADDRID_API_ID  , TCPIP_E_INV_ARG, E_NOT_OK )

    /* Check whether localAddress has IP assigned  */
    if( TCPIP_IPADDR_ASSIGNMENT_INVALID != (TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en) )
    {
        lRetVal_en = E_OK;
    }

    return(lRetVal_en);
}


/********************************************************************************************************************/
/* TcpIp_GetFramePrioFrmLocalAddrId() - This API returns the Frame priority configured for TcpIpCtrl mapped         */
/*                                      to the requested LocalAddress.                                              */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrId_u8      - Local address id reference to IPv4 address config and EthIf controller index          */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*      FramePrio_pu8    - Holds the priority configured for TcpIpCtrl mapped to the requested LocalAddress         */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request was not successful,                                                 */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetFramePrioFrmLocalAddrId(
                                                        VAR( TcpIp_LocalAddrIdType, AUTOMATIC )     LocalAddrId_u8,
                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        FramePrio_pu8 )
{
    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),          \
                                       TCPIP_E_GET_FRAMEPRIO_FRM_LOCALADDRID_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if FramePrio_pu8 is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == FramePrio_pu8 ), TCPIP_E_GET_FRAMEPRIO_FRM_LOCALADDRID_API_ID,   \
                                      TCPIP_E_NULL_PTR, E_NOT_OK )

    ( * FramePrio_pu8 ) = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].TcpIpCtrlFramePrio_u8 );

    return ( E_OK );
}


#if (TCPIP_IPV6_ENABLED == STD_ON)
/********************************************************************************************************************/
/* TcpIp_IPv6AddrCompareWithMask() - This API compares the value of two IPv6 addresses depending on the provided netmask: */
/*                             - If netmask == 128, then compare the whole addresses                                */
/*                             - If netmask < 128, then compare only the first number of bits specified             */
/*                             by the netmask                                                                       */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      IPv6Addr1_pcu32     - The first IPv6 address to be compared                                                 */
/*      IPv6Addr2_pcu32     - The second IPv6 address to be compared                                                */
/*      Netmask_u8          - The number of bits to be compared                                                     */
/*                                                                                                                  */
/* Output Parameters :      None.                                                                                   */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      boolean             - TRUE: The IPv6 addresses are equal when comparing for specified netmask.              */
/*                          - FALSE: The IPv6 addresses are NOT equal when comparing for specified netmask.         */
/*                                                                                                                  */
/* Design Decision:                                                                                                 */
/*      In order to speed up the comparison, perform UINT32 comparisons instead of UINT8 comparisons.               */
/*      Split the IP in UINT32 words and perform the comparison.                                                    */
/********************************************************************************************************************/
FUNC( boolean, TCPIP_CODE ) TcpIp_IPv6AddrCompareWithMask(
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )		IPv6Addr1_pcu32,
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )   	IPv6Addr2_pcu32,
                                        VAR( uint8, AUTOMATIC )                 	Netmask_u8 )
{
    VAR( boolean, AUTOMATIC )   lRetValue_b;

    lRetValue_b = TRUE;

    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == IPv6Addr1_pcu32 ), TCPIP_E_IPV6_ADDR_COMPARE_WITH_MASK_API_ID, TCPIP_E_NULL_PTR, FALSE )
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == IPv6Addr2_pcu32 ), TCPIP_E_IPV6_ADDR_COMPARE_WITH_MASK_API_ID, TCPIP_E_NULL_PTR, FALSE )
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( Netmask_u8 == 0) || (Netmask_u8 > TCPIP_IPV6_CIDR_MASK_128) ), TCPIP_E_IPV6_ADDR_COMPARE_WITH_MASK_API_ID, TCPIP_E_INV_ARG, FALSE )

    /* If netmask is 128, then compare the whole IPv6 addresses */
    if(Netmask_u8 == TCPIP_IPV6_CIDR_MASK_128)
    {
        if( ( IPv6Addr1_pcu32[0] != IPv6Addr2_pcu32[0] ) ||
            ( IPv6Addr1_pcu32[1] != IPv6Addr2_pcu32[1] ) ||
            ( IPv6Addr1_pcu32[2] != IPv6Addr2_pcu32[2] ) ||
            ( IPv6Addr1_pcu32[3] != IPv6Addr2_pcu32[3] ) )
        {
            lRetValue_b = FALSE;
        }
    }
    else
    {
        /* Compare the first Netmask_u8 bits from the IPv6 addresses, each uint32 bit group at a time */
        VAR( uint8, AUTOMATIC )     lCurrIndex_u8 = 0;
        VAR( uint32, AUTOMATIC )    lNetmask_u32;
        VAR( uint8, AUTOMATIC )     lNetmaskPrfx_u8 = Netmask_u8;

        while( lNetmaskPrfx_u8 > 0 )
        {
            if( lNetmaskPrfx_u8 >= TCPIP_TYPE_LENGTH_UINT32 ) /* If the mask length is bigger than one UINT32 word length, split it in UINT32 words and compare each one for faster processing. */
            {
                if( IPv6Addr1_pcu32[lCurrIndex_u8] != IPv6Addr2_pcu32[lCurrIndex_u8] )
                {
                    lRetValue_b = FALSE;
                    break;  /* break while loop */
                }

                lCurrIndex_u8++;
                lNetmaskPrfx_u8 = lNetmaskPrfx_u8 - TCPIP_TYPE_LENGTH_UINT32;
            }
            else
            {
                /* Convert the rest of the netmask prefix into a 32 bit mask */
                lNetmask_u32 = ( 0xFFFFFFFFuL << (TCPIP_NETMASK_MAX_VAL - lNetmaskPrfx_u8) );

                /* Last uint32 bit group compared for this netmask */
                if( ( IPv6Addr1_pcu32[lCurrIndex_u8] & lNetmask_u32 ) != ( IPv6Addr2_pcu32[lCurrIndex_u8] & lNetmask_u32 ) )
                {
                    lRetValue_b = FALSE;
                }

				/* MR12 RULE 15.4 VIOLATION: The break instruction is used for speed optimization. */
                break;  /*  This is the final comparison. Break while loop anyway. */
            }
        }
    }

    return lRetValue_b;
}


/********************************************************************************************************************/
/* TcpIp_IsIPv6AddrEqualToNetworkAddr() - This API verifies if an IPv6 address is equal to its corresponding        */
/*                                        network address.                                                          */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      IPv6Addr_pcu32      - The first IPv6 address to be verified                                                 */
/*      Netmask_u8          - The netmask of the IPv6 network                                                       */
/*                                                                                                                  */
/* Output Parameters :      None.                                                                                   */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      boolean             - TRUE: The IPv6 address is equal to its corresponding network address.                 */
/*                          - FALSE: The IPv6 address is NOT equal to its corresponding network address.            */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( boolean, TCPIP_CODE ) TcpIp_IsIPv6AddrEqualToNetworkAddr(
                                        P2CONST( uint32, AUTOMATIC, AUTOMATIC )		IPv6Addr_pcu32,
                                        VAR( uint8, AUTOMATIC )                 	Netmask_u8 )
{
    VAR( uint8, AUTOMATIC )			lLoopIdx_u8;
    VAR( uint8, AUTOMATIC )			lCurrIndex_u8;
    VAR( uint8, AUTOMATIC )			lNetworkSuffix_u8;
    VAR( boolean, AUTOMATIC )		lRetValue_b;
    VAR( uint32, AUTOMATIC )		lMaskValue_u32;
    VAR( uint32, AUTOMATIC )		lIPv6NetworkAddr_au32[4];

    lRetValue_b = TRUE;

    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == IPv6Addr_pcu32 ), TCPIP_E_IS_IPV6_ADDR_EQUAL_TO_NETWORK_ADDR_ID, TCPIP_E_NULL_PTR, FALSE )
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( Netmask_u8 == 0) || (Netmask_u8 > TCPIP_IPV6_CIDR_MASK_128) ), TCPIP_E_IS_IPV6_ADDR_EQUAL_TO_NETWORK_ADDR_ID, TCPIP_E_INV_ARG, FALSE )

    /* First, copy the IPv6 address to the network address */
    for( lLoopIdx_u8 = 0; lLoopIdx_u8 < 4u; lLoopIdx_u8++ )
    {
        lIPv6NetworkAddr_au32[lLoopIdx_u8] = IPv6Addr_pcu32[lLoopIdx_u8];
    }

    /* Obtain the network address by setting the last (128 - Netmask_u8) bits to 0 */
    lNetworkSuffix_u8   = TCPIP_IPV6_CIDR_MASK_128 - Netmask_u8;
    lCurrIndex_u8       = 3u;     /* Start from the last uint32 bit group of the IPv6 address */
    while( lNetworkSuffix_u8 > 0 )
    {
        if( lNetworkSuffix_u8 >= TCPIP_TYPE_LENGTH_UINT32 )
        {
            /* Set the whole uint32 bit group to 0 */
            lIPv6NetworkAddr_au32[lCurrIndex_u8] = 0;

            lCurrIndex_u8--;
            lNetworkSuffix_u8 = lNetworkSuffix_u8 - TCPIP_TYPE_LENGTH_UINT32;
        }
        else
        {
            /* Convert the rest of the netmask suffix into a 32 bit mask. */
            lMaskValue_u32 = ( 0xFFFFFFFFuL << lNetworkSuffix_u8 );

            /* Apply the mask to the current uint32 bit group, to set the last remaining bits to 0. */
            lIPv6NetworkAddr_au32[lCurrIndex_u8] &= lMaskValue_u32;

            break;  /* All bits from the netmask suffix have been processed. */
        }
    }

    /* Compare all 128 bits for the two IPv6 addresses */
    lRetValue_b = TcpIp_IPv6AddrCompareWithMask(IPv6Addr_pcu32, &(lIPv6NetworkAddr_au32[0]), TCPIP_IPV6_CIDR_MASK_128);

    return lRetValue_b;
}
#endif


/********************************************************************************************************************/
/* TcpIp_GetEthIfCtrlState()	- This API returns the state of TcpIpEthIf controller. TcpIp-EthIf controller can be*/
/*								in ONLINE, ONHOLD, OFFLINE, STARTUP, SHUTDOWN states.								*/
/*                                                                                               					*/
/* Input Parameters :																								*/
/*	EthIfCtrlIdx_u8		- EthIf controller index whose state is to be returned. 									*/
/*                                                                                               					*/
/* Return  :																					 					*/
/*	TcpIp_StateType	  	- TCPIP_STATE_ONLINE: 	Communication via at least one IP address is possible.				*/
/*						  TCPIP_STATE_ONHOLD: 	No communication is currently possible (e.g. link down).			*/
/*						  TCPIP_STATE_OFFLINE:	No communication is possible.										*/
/* 						  TCPIP_STATE_STARTUP:  IP address assignment in progress or ready for manual start			*/
/* 						  TCPIP_STATE_SHUTDOWN:	Release of resources using the EthIf controller, release of IP 		*/
/*												address assignment.													*/
/*                                                                                               					*/
/********************************************************************************************************************/
FUNC( TcpIp_StateType, TCPIP_CODE ) TcpIp_GetEthIfCtrlState(	VAR( uint8, AUTOMATIC )			EthIfCtrlIdx_u8	)
{
	return ( TcpIp_EthIfCtrlSt_aen[EthIfCtrlIdx_u8] );
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_GetIPAddrAsgnMethFrmCrtlIdx  - This API returns IP address assignment for controller index.				*/
/*																													*/
/*                                                                                                                  */
/* Input Parameters : 																			  					*/
/* EthIfCtrlIdx_u8	- 	EthIf controller index							     										*/
/*                                                                                                                  */
/* Output Parameters : 																			  					*/
/* IpAddrAsgnMethType_pen	-	IP address assignment used for the Controller										*/
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType 	- 	Result of operation																			*/
/*                      E_OK - The out parameter - IpAddrAsgnMethType_pen has a valid value                         	 	*/
/*                      E_NOT_OK - The out parameter - IpAddrAsgnMethType_pen has a invalid value                      	*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetIPAddrAsgnMethFrmCrtlIdx(
													VAR( uint8, AUTOMATIC )							EthIfCtrlIdx_u8 ,
													P2VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC, AUTOMATIC )   	IpAddrAsgnMethType_pen )
{
	/* Local variable declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
	VAR( Std_ReturnType, AUTOMATIC )       		lRetVal_en;
	VAR( uint8, AUTOMATIC )                		lIdx1_u8;

    /* Local variable initialisation */
    lRetVal_en = E_NOT_OK;

    /* Report DET if IpAddrAsgnMethType_pen is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == IpAddrAsgnMethType_pen ), TCPIP_E_GET_IPADDR_ASGNMETH_FRM_CRTLIDX_API_ID,     \
            		                  TCPIP_E_NULL_PTR, E_NOT_OK )

	/* Loop through the IP config table, which is part of the TcpIp config table */
	for( lIdx1_u8 = 0; ( lIdx1_u8 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ); lIdx1_u8++ )
	{
	    /* Check if the IP address matches the IP address in the config table */
		lLocalAddrConfig_pcst = ( &( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8] ) );

		if ( ( EthIfCtrlIdx_u8 	== ( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ) ) &&
			 ( TCPIP_UNICAST 	== ( lLocalAddrConfig_pcst->IpAddressType_en ) ) &&
			 ( TCPIP_IPADDR_ASSIGNMENT_INVALID 	!= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en ) ) )
		{
		    /* Update the corresponding IPv4 address into the local variable */
			*IpAddrAsgnMethType_pen	= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en );

			/* Set return value to E_OK and abort the "for" loop */
			lRetVal_en   = E_OK;
			break;
		}
	}

	return(lRetVal_en);
}


#if ( TCPIP_IPV4_ENABLED == STD_ON )
/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_GetIPv4AddrFrmCtrlIdx  - This API returns source IPv4 address for controller index. This returned IPv4 	*/
/*						address shall be a Unicast and valid IPv4 address											*/
/*                                                                                                                  */
/* Input Parameters : 																			  					*/
/* EthIfCtrlIdx_u8	- 	EthIf controller index							     										*/
/*                                                                                                                  */
/* Output Parameters : 																			  					*/
/* SrcIPv4Addr_pu32	-	Unicast IP address assigned to the EthIf controller 										*/
/* NetMask_pu32		-	Netmask configured for the EthIf controller 	 											*/
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType 	- 	Result of operation																			*/
/*                      E_OK - The out parameter - SrcIPv4Addr_pu32 has a valid value                         	 	*/
/*                      E_NOT_OK - The out parameter - SrcIPv4Addr_pu32 has a invalid value                      	*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetIPv4AddrFrmCtrlIdx(
													VAR( uint8, AUTOMATIC )							EthIfCtrlIdx_u8 ,
													P2VAR( uint32, AUTOMATIC, AUTOMATIC )   		SrcIPv4Addr_pu32,
													P2VAR( uint32, AUTOMATIC, AUTOMATIC )			NetMask_pu32 )
{
	/* Local variable declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
	VAR( Std_ReturnType, AUTOMATIC )       		lRetVal_en;
	VAR( uint8, AUTOMATIC )                		lIdx1_u8;

    /* Local variable initialisation */
    lRetVal_en = E_NOT_OK;

    /* Report DET if SrcIPv4Addr_pu32 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == SrcIPv4Addr_pu32 ), TCPIP_E_GET_IPV4ADDR_FRM_CTRLIDX_API_ID,     \
							          TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if NetMask_pu32 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == NetMask_pu32 ), TCPIP_E_GET_IPV4ADDR_FRM_CTRLIDX_API_ID,         \
							          TCPIP_E_NULL_PTR, E_NOT_OK )

	/* Loop through the IP config table, which is part of the TcpIp config table */
	for( lIdx1_u8 = 0; ( lIdx1_u8 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ); lIdx1_u8++ )
	{   /* Check if the IP address matches the IP address in the config table */
		lLocalAddrConfig_pcst = ( &( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8] ) );
		if ( ( EthIfCtrlIdx_u8 	== ( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ) ) &&
			 ( TCPIP_UNICAST 	== ( lLocalAddrConfig_pcst->IpAddressType_en ) ) &&
			 ( TCPIP_IPADDR_ASSIGNMENT_INVALID 	!= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en ) ) )
		{
			/* Update output parameters */
			( *NetMask_pu32 )	= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.NetMask_u32 );
			( *SrcIPv4Addr_pu32 )	= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 );

			lRetVal_en = E_OK;

			break;
		}
	}

	return(lRetVal_en);
}

/********************************************************************************************************************/
/*                                                                                               					*/
/* TcpIp_SubnetMskChkRemoteIpAddr()	- This API checks whether the remote IP is in the same subnet as the local IP. 	*/
/*  					  The netmask for all LocalAddrIds belonging to an EthIf controller shall be configured 	*/
/*                        with same value                                                          					*/
/*                                                                                               					*/
/* Input Parameters :																								*/
/*	EthIfCtrlIdx_u8		- EthIf controller index on which the frame has been received. 								*/
/* 	RemoteIPv4Addr_u32	- IPv4 address of the remote host					   										*/
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*	IPv4AddrType_en		- In/Out parameter. Indicates whether the remote IP address is in the same 					*/
/*						  subnet as the local IP address															*/
/*                                                                                               					*/
/* Return  :																					 					*/
/*	Std_ReturnType	  		E_OK: The request has been accepted.													*/
/*						 	E_NOT_OK: The request was not successful,												*/
/*                                                                                               					*/
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_SubnetMskChkRemoteIpAddr(
														VAR( uint8, AUTOMATIC )									EthIfCtrlIdx_u8,
														VAR( uint32, AUTOMATIC )								RemoteIPv4Addr_u32,
														P2VAR( TcpIp_IPv4AddrType_ten, AUTOMATIC, AUTOMATIC ) 	IPv4AddrType_pen )
{
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
	VAR( Std_ReturnType, AUTOMATIC )	    lStdRetType_en;
	VAR( uint32, AUTOMATIC )				lNetMask_u32;
	VAR( uint32, AUTOMATIC )				lSrcIPv4Addr_u32;
	VAR( uint8, AUTOMATIC )					lIdx1_u8;

	lStdRetType_en	= E_NOT_OK;

	/* Report DET if IPv4AddrType_pen is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == IPv4AddrType_pen ), TCPIP_E_SUBNETMSK_CHK_REMOTEIPADDR_API_ID,    \
			                          TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Loop through all LocalAddrIds with the requested EthIf controller */
    for( lIdx1_u8 = 0; lIdx1_u8 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ); lIdx1_u8++ )
    {
    	lLocalAddrConfig_pcst = ( & ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8] ) );

        if( ( EthIfCtrlIdx_u8 == ( lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ) ) &&
        	( TCPIP_UNICAST == ( lLocalAddrConfig_pcst->IpAddressType_en ) ) &&
        	( TCPIP_IPADDR_ASSIGNMENT_INVALID 	!= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en ) ) )
        {	/* Extract the netmask and the current assigned IP address */
        	/* The netmask for all LocalAddrIds belonging to an EthIf controller shall be same */
        	lSrcIPv4Addr_u32	= ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32 );

            lNetMask_u32 = ( lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.NetMask_u32 );

            /* Check whether the remote IPv4 address is in the same network as the local IPv4 address */
            if ( ( RemoteIPv4Addr_u32 & lNetMask_u32 ) == ( lSrcIPv4Addr_u32 & lNetMask_u32 ) )
            {
                ( * ( TcpIp_IPv4AddrType_ten * ) IPv4AddrType_pen ) = TCPIP_SUBNET_INT_IPV4ADDR;
            }
            else
            {
                ( * ( TcpIp_IPv4AddrType_ten * ) IPv4AddrType_pen ) = TCPIP_SUBNET_EXT_IPV4ADDR;
            }

            lStdRetType_en = E_OK;

            break;
        }
    }

	return ( lStdRetType_en );
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_GetLocalAddrIdForRxFrame  -  This API returns LocalAddrId to which the IPv4 address                        */
/*		                              and the EthIf Ctrl Idx is mapped.              								*/
/*                                                                                                                  */
/* Input Parameters : 																			  					*/
/*  EthIfCtrlIdx_u8			- EthIf controller index.								                                */
/*  IPv4Addr_u32	        - Input IPv4 address for verifying with the IPv4 address mapped to the EthIfCtrl       	*/
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  LocalAddrId_pu8         - Local address Id reference to IPv4 address config and EthIf controller index.         */
/*                                                                                                                  */
/*                                                                                                                  */
/* Return : 																			  					        */
/*	Std_ReturnType	  		E_OK: The request has been accepted.													*/
/*						 	E_NOT_OK: The request was not successful.												*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetLocalAddrIdForRxFrame(
												VAR( uint8,  AUTOMATIC )  	 			             EthIfCtrlIdx_u8,
												VAR( uint32, AUTOMATIC )				             IPv4Addr_u32,
												P2VAR( TcpIp_LocalAddrIdType, AUTOMATIC, AUTOMATIC ) LocalAddrId_pu8 )
{
	/* Local variable declaration */
	VAR( Std_ReturnType, AUTOMATIC )        	lRetVal_en;
	VAR( uint8, AUTOMATIC )                 	lIdx1_u8;

	lRetVal_en = E_NOT_OK;

    /* Report DET if LocalAddrId_pu8 is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == LocalAddrId_pu8 ), TCPIP_E_GET_LOCALADDRID_FOR_RXFRAME_API_ID,           \
                                      TCPIP_E_NULL_PTR, E_NOT_OK )

	/* Loop through all localAddrId */
	for( lIdx1_u8 = 0; ( lIdx1_u8 < ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ) ; lIdx1_u8++ )
	{
		/* If the input IP address matches the IP address mapped to one of the EthICtrl, break the loop */
		if( ( EthIfCtrlIdx_u8 == ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8].EthIfCtrlRef_u8 ) ) &&
			( IPv4Addr_u32 == (TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8].CurrAsgnedAddr_pst->IpAddrParams_un.IPv4Par_st.IpAddr_u32) ) &&
			( TCPIP_IPADDR_ASSIGNMENT_INVALID   != (TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[lIdx1_u8].CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en) ) )
		{
		    ( * LocalAddrId_pu8 )   = lIdx1_u8;

		    lRetVal_en = E_OK;
			break;
		}
	}

	return ( lRetVal_en );
}
#endif

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_ChkComAllowed  - This API checks whether communication is allowed in IP layer based on EthIf 				*/
/*						  controller state and address assignment method configured for the LocalAddrId. 			*/
/* 						  Communication is allowed:  																*/
/* 						  1. If EthIf controller state is ONLINE 													*/
/* 						  2. If EthIf controller state is STARTUP or SHUTDOWN and address assignment method is DHCP */
/*						     for the requested localAddrId															*/
/*                                                                                                                  */
/* Input Parameters : 																			  					*/
/*  LocalAddrId_u8			-LocalAddrId on which communication status check is to be done.		 					*/
/*                                                                                                                  */
/* Return : 																			  					        */
/*	Std_ReturnType	  		E_OK	: EthIf controller is in valid state for communication.							*/
/*						 	E_NOT_OK: EthIf controller is in invalid state for communication.						*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_ChkComAllowed( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  	 LocalAddrId_u8 )
{
    /* Local variable declaration */
	P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   	lLocalAddrConfig_pcst;
	VAR( Std_ReturnType, AUTOMATIC )	  							lRetVal_en;
	VAR( uint8,	AUTOMATIC )	  										lAddrAsgnmentIdx_u8;

	/* Initialize local variable */
    lRetVal_en = E_NOT_OK;

	/* Report DET if local address ID is invalid */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),   \
			                          TCPIP_E_CHK_COMALLOWED_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    lLocalAddrConfig_pcst 	= ( &( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8] ) );

    switch( TcpIp_EthIfCtrlSt_aen[ lLocalAddrConfig_pcst->EthIfCtrlRef_u8 ] )
    {
        /* API TcpIp_ChkComAllowed () should return E_OK if the requested EthIf controller is in  TCPIP_STATE_ONLINE.*/
        case TCPIP_STATE_ONLINE:
        {
            lRetVal_en = E_OK;
        }
        break;

        /* Return E_OK if the requested TcpIpEthIf controller is in TCPIP_STATE_STARTUP or TCPIP_STATE_SHUTDOWN and TcpIpAssignmentMethod 	*/
        /* is  TCPIP_IPADDR_ASSIGNMENT_DHCP. */
        case TCPIP_STATE_STARTUP:
        case TCPIP_STATE_SHUTDOWN:
        {
            for( lAddrAsgnmentIdx_u8 = 0;
                ( ( lAddrAsgnmentIdx_u8 < ( lLocalAddrConfig_pcst->NumAddrAsgnment_u8 ) ) && ( lRetVal_en != E_OK ) );
                lAddrAsgnmentIdx_u8++ )
            {
                if( TCPIP_IPADDR_ASSIGNMENT_DHCP == ( lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAsgnmentIdx_u8].AddrAsgnmentMeth_en ) )
                {
                    lRetVal_en = E_OK;
                }
            }
        }
        break;

        /* Return E_NOT_OK if the requested TcpIpEthIf controller is in  TCPIP_STATE_ONHOLD or TCPIP_STATE_OFFLINE or invalid state. */
        default:
        {
            lRetVal_en = E_NOT_OK;
        }
        break;
    }

	return lRetVal_en;
}

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_GetLocalAddrIdProperties  -  This API returns the base address of local address configuration structure.   */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8                 - Index of local address requesting configuration information                    */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  TcpIp_LocalAddrConfig_ppst     - Pointer to store the address of requested local address configuration.         */
/*                                                                                                                  */
/*                                                                                                                  */
/* Return :                                                                                                         */
/*  Std_ReturnType          E_OK: The request has been accepted.                                                    */
/*                          E_NOT_OK: The request was not successful.                                               */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetLocalAddrIdProperties(
                                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                          LocalAddrId_u8,
                                                P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )        *TcpIp_LocalAddrConfig_ppcst )
{

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),   \
                                        TCPIP_E_GET_LOCALADDRID_PROPERTIES_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if TcpIp_LocalAddrConfig_ppst is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == TcpIp_LocalAddrConfig_ppcst ), TCPIP_E_GET_LOCALADDRID_PROPERTIES_API_ID,           \
                                      TCPIP_E_NULL_PTR, E_NOT_OK )

     /* Update output parameter with the base address of localAddress configuration strcuture */
     *TcpIp_LocalAddrConfig_ppcst = &(TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8]);

    return ( E_OK );
}

/********************************************************************************************************************/
/* TcpIp_UpdateMulticastPhysFilter() - This is a helper function which performs the actual physical address update  */
/*						in the Eth filter list. The purpose of his function is to separate the processing depending */
/* 						on the address domain family (IPv4/IPv6). This function must be called  only for addresses 	*/
/*						of Multicast type.																			*/
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*	LocalAddrConfig_pcst - Pointer to the local IP address configuration   											*/
/*	FilterActionType_en  - The action desired to be applied to the specified MAC address							*/
/*                         Allowed values: ADD_TO_FILTER/ETH_ADD_TO_FILTER or REMOVE_FROM_FILTER/ETH_REMOVE_FROM_FILTER*/
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*	Std_ReturnType		E_OK: The specified multicast address has been successfully updated in the filter list.		*/
/*						E_NOT_OK: An error occured during physical filter update for the specified multicast address.*/
/*                                                                                                                  */
/* Note :                                                                                                          	*/
/* 	1. When the selected action is ADD_TO_FILTER / ETH_ADD_TO_FILTER, the MAC address is generated from the Static	*/
/*     configured IP address, because this step is a part of the Multicast IP Address Assignment process.			*/
/* 	2. When the selected action is REMOVE_FROM_FILTER / ETH_REMOVE_FROM_FILTER, the MAC address is generated from the*/
/*     Current configured IP address, because this step is a part of the Multicast IP Address Release process.		*/
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_UpdateMulticastPhysFilter( P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )	LocalAddrConfig_pcst,
																	 VAR( Eth_FilterActionType, AUTOMATIC )						FilterActionType_en )
{
	P2CONST( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )	lIpAddrParams_pcun;
	VAR( uint8, AUTOMATIC )										lMulticastMACAddr_au8[6];
	VAR( Std_ReturnType, AUTOMATIC )							lStdRetType_en = E_OK;		/* Optimistic initialization */

	switch(FilterActionType_en)
	{
		case ADD_TO_FILTER:
			/* In the case of adding a physical address filter, the MAC address is generated from the Static configured address. */
			lIpAddrParams_pcun = (const TcpIp_IPAddrParamType_tun*) (LocalAddrConfig_pcst->StaticIpAddr_pun);
			break;

		case REMOVE_FROM_FILTER:
			/* In the case of removing a physical address filter, the MAC address is generated from the Current allocated address. */
			lIpAddrParams_pcun = (const TcpIp_IPAddrParamType_tun*) ( &(LocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un) );
			break;

		default:
			/* Invalid action specified! Report to DET and return E_NOT_OK. */
		    TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_UPDATE_MULTICAST_PHYS_FILTER_ADDR_ID, TCPIP_E_INV_ARG )
			lStdRetType_en = E_NOT_OK;

			break;
	}

	if(lStdRetType_en == E_OK)
	{
		switch (LocalAddrConfig_pcst->IpDomainType_u32)
		{
			#if (TCPIP_IPV4_ENABLED == STD_ON)
			case TCPIP_AF_INET:
				/* Generate the multicast MAC address */
				rba_EthIPv4_GetIPMulticastDestEthAddr( (lIpAddrParams_pcun->IPv4Par_st.IpAddr_u32), &lMulticastMACAddr_au8[0] );

				/* Call the lower layer API to update the physical address filter */
				lStdRetType_en = EthIf_UpdatePhysAddrFilter( LocalAddrConfig_pcst->EthIfCtrlRef_u8, &lMulticastMACAddr_au8[0], FilterActionType_en );
			break;
			#endif

			#if (TCPIP_IPV6_ENABLED == STD_ON)
			case TCPIP_AF_INET6:
				/* Generate the multicast MAC address */
				rba_EthIPv6_GetIPMulticastDestEthAddr( &(lIpAddrParams_pcun->IPv6Par_st.IpAddr_st), &lMulticastMACAddr_au8[0] );

				/* Call the lower layer API to update the physical address filter */
				lStdRetType_en = EthIf_UpdatePhysAddrFilter( LocalAddrConfig_pcst->EthIfCtrlRef_u8, &lMulticastMACAddr_au8[0], FilterActionType_en );
			break;
			#endif
			default:
				/* Domain not supported. */
			    TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_UPDATE_MULTICAST_PHYS_FILTER_ADDR_ID, TCPIP_E_NOPROTOOPT )
				lStdRetType_en = E_NOT_OK;
			break;
		}
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

