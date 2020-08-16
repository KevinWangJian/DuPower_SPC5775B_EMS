

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"

#include "TcpIp_Prv.h"

/************************************************************************************************************************/
/* TcpIp_DhcpReadOption() 	- By this API service the TCP/IP stack retrieves DHCP option data identified by parameter	*/
/* 								option for already received DHCP options.			       								*/
/*                                                                                               						*/
/* Input Parameters :																									*/
/*		LocalIpAddrId       - IP address identifier representing the local IP address and EthIf controller for which	*/
/*								the DHCP option shall be read.															*/
/*		Option  			- DHCP option.																				*/
/* 		DataLength      	- As input parameter, contains the length of the provided data buffer. Will be overwritten 	*/
/*								with the length of the actual data.														*/
/* 		DataPtr  		    - Pointer to memory containing DHCP option data												*/
/*						 																								*/
/* Return  :																					 						*/
/*		Std_ReturnType	  E_OK: The request has been accepted.															*/
/*						  E_NOT_OK: The request has not been accepted.													*/
/*                                                                                               						*/
/************************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: P2VAR is defined in AUTOSAR for DataLength and DataPtr */
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_DhcpReadOption(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 	LocalIpAddrId,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 					Option,
		 	 	 	 	 	 	 	 	 	P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		DataLength,
		 	 	 	 	 	 	 	 	 	P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		DataPtr )
{
	/* Local variables declaration */
    VAR( Std_ReturnType, AUTOMATIC )						lStdRetType_en;


	/* Initialise local variables */
	lStdRetType_en					= E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( TRUE != TcpIp_InitFlag_b), TCPIP_E_DHCP_READOPTION_API_ID,           \
    		                     TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalIpAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),                \
    								TCPIP_E_DHCP_READOPTION_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if DataLength OR DataPtr is a null pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( NULL_PTR ==  DataLength ) || ( NULL_PTR ==  DataPtr ) ),     \
    								TCPIP_E_DHCP_READOPTION_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK  )

    lStdRetType_en = rba_EthDHCP_ReadOption( LocalIpAddrId,Option,DataLength,DataPtr);

	return( lStdRetType_en );
}

/************************************************************************************************************************/
/* TcpIp_DhcpWriteOption() 	- By this API service the TCP/IP stack retrieves DHCP option data identified by parameter   */
/* 								option for already received DHCP options.			       								*/
/*                                                                                               						*/
/* Input Parameters :																									*/
/*		LocalIpAddrId       - IP address identifier representing the local IP address and EthIf controller for which 	*/
/*								the DHCP option shall be written														*/
/*		Option	    		- DHCP option, e.g. Host Name																*/
/* 		DataLength      	- Length of DHCP option data															    */
/* 		DataPtr     		- Pointer to memory containing DHCP option data												*/
/*						 																								*/
/* Return  :																					 						*/
/*		Std_ReturnType	  E_OK: The request has been accepted.															*/
/*						  E_NOT_OK: The request has not been accepted.													*/
/*                                                                                               						*/
/************************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_DhcpWriteOption(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 	LocalIpAddrId,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 					Option,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 					DataLength,
		 	 	 	 	 	 	 	 	 	P2CONST( uint8, AUTOMATIC, AUTOMATIC  ) 	DataPtr )
{
	/* Local variables declaration */
    VAR( Std_ReturnType, AUTOMATIC )						lStdRetType_en;


	/* Initialise local variables */
	lStdRetType_en					= E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( TRUE != TcpIp_InitFlag_b), TCPIP_E_DHCP_WRITEOPTION_API_ID,           \
    		                     TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalIpAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),      \
    								TCPIP_E_DHCP_WRITEOPTION_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if DataLength OR DataPtr is a null pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE(( NULL_PTR ==  DataPtr ) ,     											\
    								TCPIP_E_DHCP_WRITEOPTION_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK  )

    lStdRetType_en		=  rba_EthDHCP_WriteOption		( LocalIpAddrId,Option,DataLength,DataPtr);

	return( lStdRetType_en );
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON ) */

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/
