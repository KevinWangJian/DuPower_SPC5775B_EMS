

#include "TcpIp.h"
#include "TcpIp_Lib.h"
#ifdef TCPIP_CONFIGURED

#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_RandNumXor64()  - This API Generates the pseudo random number based on XorShift with 2 seed                */
/*                         Basic formula is to generate random number based on a ^ (a shift[Left and Right] count)  */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* NIL                                                                                                              */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  NIL                                                                                                             */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* uint32 - Generated random Number                                                                                 */
/*                                                                                                                  */
/********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( uint32, TCPIP_CODE ) TcpIp_RandNumXor64( void )
{
    VAR( uint32, TCPIP_VAR ) lTemp_u32;

    lTemp_u32 = ( TcpIp_RandNumSeed1_u32 ^ ( TcpIp_RandNumSeed1_u32 << 23u ) );

    TcpIp_RandNumSeed1_u32 = TcpIp_RandNumSeed2_u32;
    TcpIp_RandNumSeed2_u32 = ( ( TcpIp_RandNumSeed2_u32 ^ (TcpIp_RandNumSeed2_u32 >> 17u ) ) ^ ( lTemp_u32 ^ ( lTemp_u32 >> 5u ) ) );

    return ( TcpIp_RandNumSeed2_u32 );
}

/********************************************************************************************************************/
/* TcpIp_OnesComplChkSum() - Function to calculate ones compliment checksum                                         */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* Parameter- Data_pcv       	: Buffer pointer to void that contains data on which the checksum must be calculated*/
/*          - PseudoHdr_pcst 	: Pointer to pseudo header structure. Contains information about protocol type,		*/
/*                             	  local IP and Remote IP in Tx/Rx buffer. 											*/
/*                                If it's NULL_PTR, indicates Pseudo header is not required. Eg: Ipv4, Icmp         */
/*          - Length_u16     	: Length of data in the buffer                                                      */
/*																													*/
/* Output Parameters :                                                                                              */
/*          - OutputChkSum_pu16	: The calculated ones compliment checksum                                           */
/*                                                                                                                  */
/* Return   - Result status of operation :                                                                          */
/*          - Std_ReturnType	: E_OK if checksum calculation is successful                                        */
/*          					: E_NOT_OK if checksum calculation failed  		                                    */
/*                                                                                                                  */
/********************************************************************************************************************/

/* API TcpIp_OnesComplChkSum() is required only if checksum is configured for either IPv4, Udp, Tcp or Icmp */
/* and the corresponding protocols are enabled */
#if ( TCPIP_ONES_COMPL_CHKSUM_ENABLED == STD_ON )

FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_OnesComplChkSum (
                                            P2CONST( void, AUTOMATIC, AUTOMATIC )                   Data_pcv,
                                            P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_pcst ,
                                            VAR( uint16, AUTOMATIC )                                Length_u16,
											P2VAR( uint16, AUTOMATIC, AUTOMATIC )                   OutputChkSum_pu16 )
{
    /* Local variable declaration */
    P2CONST( uint16, AUTOMATIC, AUTOMATIC )               	lBuf_pcu16;
    VAR( uint32, AUTOMATIC )                            	lShiftLeft_u32;
    VAR( uint32, AUTOMATIC )                            	lPseudoHdrSum_u32;
    VAR( uint32, AUTOMATIC )                            	lSumAlign_u32;
	VAR( Std_ReturnType, AUTOMATIC )    					lRetType_en;

    /* Initialisation */
    lShiftLeft_u32      	= Length_u16;
    lSumAlign_u32       	= 0;
    /* MR12 RULE 11.5 VIOLATION: Cast uint16 pointer is required for faster checksum calculation. It is done on the Tx/Rx buffer that should be 2 byte aligned */
    lBuf_pcu16           	= ( ( const uint16 * )Data_pcv );
    lPseudoHdrSum_u32   	= 0;
	lRetType_en 			= E_OK;

	/* Report DET if Data_pcv is a null pointer */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR ==  Data_pcv ), TCPIP_E_ONES_COMPL_CHKSUM_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

	/* Report DET if OutputChkSum_pu16 is a null pointer */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR ==  OutputChkSum_pu16 ), TCPIP_E_ONES_COMPL_CHKSUM_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

	/* Algorithm : Using a 32 bit accumulator (lSumAlign_u32), we add sequential 16 bit words to it */
	/* it, and at the end, fold back all the carry bits from the top 16 bits into the lower 16 bits */
	while( lShiftLeft_u32 > 1u )
	{
		lSumAlign_u32   = ( lSumAlign_u32 + ( *lBuf_pcu16 ) );
		lBuf_pcu16++;
		lShiftLeft_u32  = ( lShiftLeft_u32 - 2u );
	}

	/* Mop up an odd byte, if necessary */
	if( 1u == lShiftLeft_u32 )
	{
		#if ( TCPIP_ENDIANESS == TCPIP_LITTLE_ENDIAN )
		lSumAlign_u32   = lSumAlign_u32 + ( ( *lBuf_pcu16 ) & 0x00FFu );
		#else
		/* In case of big endian, odd byte from buffer shall be appended with zero */
		lSumAlign_u32   = lSumAlign_u32 + ( ( *lBuf_pcu16 ) & 0xFF00u );
		#endif
	}

	/* Include pseudo header for checksum calculation only for Tcp and Udp */
	/* Tcp and Udp shall pass valid pointer for PseudoHdr_pcst, and other protocols (IPv4 and Icmp) shall pass NULL_PTR */
	if( PseudoHdr_pcst != NULL_PTR )
	{

		switch (PseudoHdr_pcst->IpDomainType_t)
		{
			#if (TCPIP_IPV4_ENABLED == STD_ON)
			case TCPIP_AF_INET:
			{
				VAR( uint32, AUTOMATIC )	lLocalAddr_u32 	= PseudoHdr_pcst->LocalIpAddr_un.IPv4Addr_u32;
				VAR( uint32, AUTOMATIC )	lRemoteAddr_u32	= PseudoHdr_pcst->RemoteIpAddr_un.IPv4Addr_u32;

				lPseudoHdrSum_u32 = ( lLocalAddr_u32 & 0x0000FFFFuL )  + (( lLocalAddr_u32 & 0xFFFF0000uL ) >> 16u );
				lPseudoHdrSum_u32 += ( lRemoteAddr_u32 & 0x0000FFFFuL ) + (( lRemoteAddr_u32 & 0xFFFF0000uL ) >> 16u );
			}
			break;
			#endif

			#if (TCPIP_IPV6_ENABLED == STD_ON)
			case TCPIP_AF_INET6:
			{
				VAR( uint32, AUTOMATIC )	lIdx_u32;
				VAR( uint32, AUTOMATIC )	lAddr_u32;

				for (lIdx_u32 = 0; lIdx_u32 < 4u; lIdx_u32++)
				{
					lAddr_u32 = PseudoHdr_pcst->LocalIpAddr_un.IPv6Addr_pcu32[lIdx_u32];
					lPseudoHdrSum_u32 += (lAddr_u32 & 0x0000FFFFuL ) + (( lAddr_u32 & 0xFFFF0000uL ) >> 16u );

					lAddr_u32 = PseudoHdr_pcst->RemoteIpAddr_un.IPv6Addr_pcu32[lIdx_u32];
					lPseudoHdrSum_u32 += (lAddr_u32 & 0x0000FFFFuL ) + (( lAddr_u32 & 0xFFFF0000uL ) >> 16u );
				}
			}
			break;
			#endif

			default:
				TCPIP_DET_REPORT_ERROR_TRUE_NO_RET( TCPIP_E_ONES_COMPL_CHKSUM_API_ID, TCPIP_E_NOPROTOOPT )
				lRetType_en = E_NOT_OK;
			break;
		}

		lPseudoHdrSum_u32 += (uint32)PseudoHdr_pcst->ProtoType_en + Length_u16;
		/* If the controller is little endian, swap the pseudo header sum to network byte order */
		#if ( TCPIP_ENDIANESS == TCPIP_LITTLE_ENDIAN )
		if( ( lPseudoHdrSum_u32 >> 16u ) != 0u )
		{   /* Add higher 16 bits to lower 16 bits */
			lPseudoHdrSum_u32 = ( lPseudoHdrSum_u32 & 0x0000FFFFuL ) + ( lPseudoHdrSum_u32 >> 16u ) ;

		}

		lPseudoHdrSum_u32 = ( ( lPseudoHdrSum_u32 & 0x000000FFuL ) << 8u )|
							( ( lPseudoHdrSum_u32 & 0x0000FF00uL ) >> 8u );
		#endif

		lSumAlign_u32 += lPseudoHdrSum_u32;
	}

	/* Add back carry outs from top 16 bits to low 16 bits */
	while ( ( lSumAlign_u32 >> 16u ) != 0u )
	{   /* Add higher 16 bits to lower 16 bits */
		lSumAlign_u32 = ( lSumAlign_u32 & 0x0000FFFFuL ) + ( lSumAlign_u32 >> 16u ) ;
	}

	/* Truncate to 16 bits */
	(* OutputChkSum_pu16 )   = ( ~(uint16)lSumAlign_u32 );

	/* If the controller is little endian, swap the checksum to network byte order */
	#if ( TCPIP_ENDIANESS == TCPIP_LITTLE_ENDIAN )
	(* OutputChkSum_pu16 )   = ( (uint16)( (* OutputChkSum_pu16 ) >> 8u ) | (uint16)( (* OutputChkSum_pu16 ) << 8u ) );
	#endif

    return ( lRetType_en );
}

#endif /* If checksum is configured for either IPv4, Udp, Tcp or Icmp */

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_ReadU16	- This API packs or read two consecutive uint8 memory locations into a uint16 variable			*/
/*                                                                                                                  */
/* Input Parameters :																								*/
/*  Data_pu8		- Pointer to uint8 memory location                                                              */
/*                                                                                                                  */
/* Output Parameters :																					 			*/
/*  Data_pu16		- Pointer to uint16 memory location updated with two uint8 variables	                      	*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, TCPIP_CODE ) TcpIp_ReadU16(
                               P2CONST( uint8, AUTOMATIC, AUTOMATIC )		Data_pu8,
                               P2VAR( uint16, AUTOMATIC, AUTOMATIC )		Data_pu16 )
{

	/* Report DET if Data_pu8 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu8 ), TCPIP_E_READ_U16_API_ID, TCPIP_E_NULL_PTR )

	/* Report DET if Data_pu16 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu16 ), TCPIP_E_READ_U16_API_ID, TCPIP_E_NULL_PTR )

	( * (uint16 *)Data_pu16 ) = (uint16)((uint16)((uint16)Data_pu8[0] << 8u ) |
										                 (Data_pu8[1] ));

	return;
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_ReadU32	- This API packs or read four consecutive uint8 memory locations into a uint32 variable			*/
/*                                                                                                                  */
/* Input Parameters :																								*/
/*  Data_pu8		- Pointer to uint8 memory location                                                              */
/*                                                                                                                  */
/* Output Parameters :																					 			*/
/*  Data_pu32		- Pointer to uint32 memory location updated with four uint8 variables	                      	*/
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, TCPIP_CODE ) TcpIp_ReadU32(
                               P2CONST( uint8, AUTOMATIC, AUTOMATIC )		Data_pu8,
                               P2VAR( uint32, AUTOMATIC, AUTOMATIC )		Data_pu32 )
{
	/* Report DET if Data_pu8 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu8 ), TCPIP_E_READ_U32_API_ID, TCPIP_E_NULL_PTR )

	/* Report DET if Data_pu32 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu32 ), TCPIP_E_READ_U32_API_ID, TCPIP_E_NULL_PTR )

	( * (uint32 *)Data_pu32 ) = (uint32)( ( (uint32)Data_pu8[0] << 24u ) |
			                              ( (uint32)Data_pu8[1] << 16u ) |
			                              ( (uint32)Data_pu8[2] <<  8u ) |
			                                (uint32)Data_pu8[3] );

	return;
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_WriteU16	- This API unpacks or writes into two consecutive uint8 memory locations from a uint16 variable	*/
/*					 in Network Byte Order																			*/
/*                                                                                                                  */
/* Input Parameters :																								*/
/*  Data_u16		- Input uint16 variable which is to be unpacked	                      							*/
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  Data_pu8		- The unpacked uint16 variable is updated into an address pointed by this variable              */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, TCPIP_CODE ) TcpIp_WriteU16(
                               P2VAR( uint8, AUTOMATIC, AUTOMATIC )		Data_pu8,
                               CONST( uint16, AUTOMATIC )					Data_u16 )
{
	/* Report DET if Data_pu8 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu8 ), TCPIP_E_WRITE_U16_API_ID, TCPIP_E_NULL_PTR )

	Data_pu8[0] = (uint8)( ( Data_u16 & 0xFF00uL ) >> 8u );
	Data_pu8[1] = (uint8)(   Data_u16 & 0x00FFuL );

	return;
}


/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_WriteU32	- This API unpacks or writes into four consecutive uint8 memory locations from a uint32 variable*/
/*					in Network Byte Order																			*/
/*                                                                                                                  */
/* Input Parameters :																								*/
/*  Data_u32		- Input uint32 variable which is to be unpacked	                      							*/
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  Data_pu8		- The unpacked uint32 variable is updated into an address pointed by this variable              */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, TCPIP_CODE ) TcpIp_WriteU32(
                               P2VAR( uint8, AUTOMATIC, AUTOMATIC )		Data_pu8,
                               CONST( uint32, AUTOMATIC )				Data_u32 )
{
	/* Report DET if Data_pu8 is a Null Pointer */
	TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == Data_pu8 ), TCPIP_E_WRITE_U32_API_ID, TCPIP_E_NULL_PTR )

	Data_pu8[0] = (uint8)( ( Data_u32 & 0xFF000000uL ) >> 24u );
	Data_pu8[1] = (uint8)( ( Data_u32 & 0x00FF0000uL ) >> 16u );
	Data_pu8[2] = (uint8)( ( Data_u32 & 0x0000FF00uL ) >>  8u );
	Data_pu8[3] = (uint8)(   Data_u32 & 0x000000FFuL );

	return;
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */


/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/
