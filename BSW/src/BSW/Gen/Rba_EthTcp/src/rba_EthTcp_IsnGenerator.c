

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Lib.h"
#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"
#include "rba_BswSrv.h"


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
static FUNC( uint32, RBA_ETHTCP_CODE ) rba_EthTcp_ComputeMd4Hash(   P2VAR( uint8, AUTOMATIC, AUTOMATIC )        Data_pu8,
                                                                    VAR( uint16, AUTOMATIC )                    Size_u16 );

static P2VAR( uint8, AUTOMATIC, AUTOMATIC ) rba_EthTcp_ProcessMd4Block( P2VAR( uint8, AUTOMATIC, AUTOMATIC )    Data_pu8,
                                                                        VAR( uint16, AUTOMATIC )                Size_u16,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   A_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   B_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   C_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   D_pu32 );

#endif
#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_InitIsnGenerator()   - Initialize the Initial Sequence Number generator to default values                        **/
/**                                                                                                                             **/
/** Parameters (in):                None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_InitIsnGenerator( void )
{
    /* Initialize ISN clock to 0 */
    rba_EthTcp_IsnContext_st.IsnClock_u32 = 0U;

#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
    /* Reset secret to 0 */
    /* (the secret will be initialized with random value at the first MainFunction) */
    rba_EthTcp_IsnContext_st.IsnSecret_u32 = 0U;

    /* Reset the secret timer to 0 */
    rba_EthTcp_IsnContext_st.IsnSecretTimer_u16 = 0U;

    /* Reset number of time the secret has been used to 0 */
    rba_EthTcp_IsnContext_st.IsnSecretUsageCntr_u8 = 0U;
#endif
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_IncrIsnGenerator()   - This function increment the ISN clock and the ISN secret timer                            **/
/**                                                                                                                             **/
/** Parameters (in):                None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrIsnGenerator( void )
{
    /* Increment the clock used for CLOCK_DRIVEN and CLOCK_HASH_BASED generation of the ISN */
    rba_EthTcp_IsnContext_st.IsnClock_u32 += rba_EthTcp_CurrConfig_cpo->IsnClockFactor_u32;

#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
    /* Increment the secret timer */
    rba_EthTcp_IsnContext_st.IsnSecretTimer_u16++;

    /* If the secret has not been selected randomly yet or if the secret timer is expired */
    if( (rba_EthTcp_IsnContext_st.IsnSecret_u32 == 0U)                                              ||
        (rba_EthTcp_IsnContext_st.IsnSecretTimer_u16 >= rba_EthTcp_CurrConfig_cpo->IsnSecretTimeOut_u32) )
    {
        /* Select another secret pseudo randomly */
        rba_EthTcp_IsnContext_st.IsnSecret_u32 = TcpIp_RandNumXor64();

        /* Reset the secret timer */
        rba_EthTcp_IsnContext_st.IsnSecretTimer_u16 = 0U;

        /* Reset number of time the secret has been used */
        rba_EthTcp_IsnContext_st.IsnSecretUsageCntr_u8 = 0U;
    }
#endif
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GenerateIsn()        - Generate the Initial Sequence Number according to the algorithm selected by configuration **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table for which ISN should be computed                                 **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   - uint32                                                                                    **/
/**                                     Value of the initial sequence number (will be included in the SYN or SYN-ACK being sent)**/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( uint32, RBA_ETHTCP_CODE ) rba_EthTcp_GenerateIsn( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    VAR( uint32, AUTOMATIC )                                        lGeneratedIsn_u32;
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )		lLocalAddrConfig_pcst;
    P2VAR( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )        lIPAddrParamType_pun;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( uint32, AUTOMATIC )                                        lFResult_u32;
#endif

#if ( RBA_ETHTCP_ISN_PSEUDO_RANDOM_ENABLED == STD_ON )

    /* -------------------------------- */
    /* Pseudo Random generation         */
    /* -------------------------------- */

    /* Cast argument to void as it is not used */
    (void)TcpDynSockTblIdx_uo;

    /* Generate the ISN using pseudo random generation function */
    lGeneratedIsn_u32 = TcpIp_RandNumXor64();

#elif ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON )

    /* -------------------------------- */
    /* Clock Driven generation          */
    /* -------------------------------- */

    /* Cast argument to void as it is not used */
    (void)TcpDynSockTblIdx_uo;

    /* The ISN corresponds to the actual values of the clock */
    /* (RFC1122 p87 : A TCP MUST use the specified clock-driven selection of initial sequence numbers) */
    lGeneratedIsn_u32 = rba_EthTcp_IsnContext_st.IsnClock_u32;

#else /* #if(RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON) */
    /* initialize the generated ISN  */
    lGeneratedIsn_u32 = rba_EthTcp_IsnContext_st.IsnClock_u32;
    lTcpDynSockTbl_pst              = &(rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo]);
    lRetVal_en                      = TcpIp_GetLocalAddrIdProperties( lTcpDynSockTbl_pst->LocalAddrId_u8, &lLocalAddrConfig_pcst );

	if( lRetVal_en == E_OK )
	{
		lIPAddrParamType_pun		= &(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un);

		/* -------------------------------- */
		/* Clock Hash Based generation      */
		/* -------------------------------- */

		/* Concatenate data to be hashed as per RFC6528 (localip, localport, remoteip, remoteport, secretkey) */
		switch( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].DomainType_u32 )
		{
			#if ( TCPIP_IPV4_ENABLED == STD_ON )
			case TCPIP_AF_INET:
			{
				VAR( uint8, AUTOMATIC )		lDataToHash_au8[16];

				/* Local IP */
				lDataToHash_au8[0] = (uint8)( (lIPAddrParamType_pun->IPv4Par_st.IpAddr_u32 & 0xFF000000U) >> 24U );
				lDataToHash_au8[1] = (uint8)( (lIPAddrParamType_pun->IPv4Par_st.IpAddr_u32 & 0x00FF0000U) >> 16U );
				lDataToHash_au8[2] = (uint8)( (lIPAddrParamType_pun->IPv4Par_st.IpAddr_u32 & 0x0000FF00U) >> 8U );
				lDataToHash_au8[3] = (uint8)( (lIPAddrParamType_pun->IPv4Par_st.IpAddr_u32 & 0x000000FFU) );

				/* Local Port */
				lDataToHash_au8[4] = (uint8)( (lTcpDynSockTbl_pst->LocalPort_u16 & 0xFF00U) >> 8U );
				lDataToHash_au8[5] = (uint8)( (lTcpDynSockTbl_pst->LocalPort_u16 & 0x00FFU) );

				/* Remote IP */
				lDataToHash_au8[6] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32 & 0xFF000000U) >> 24U );
				lDataToHash_au8[7] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32 & 0x00FF0000U) >> 16U );
				lDataToHash_au8[8] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32 & 0x0000FF00U) >> 8U );
				lDataToHash_au8[9] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32 & 0x000000FFU) );

				/* Remote Port */
				lDataToHash_au8[10] = (uint8)( (lTcpDynSockTbl_pst->RemotePort_u16 & 0xFF00U) >> 8U );
				lDataToHash_au8[11] = (uint8)( (lTcpDynSockTbl_pst->RemotePort_u16 & 0x00FFU) );

				/* Secret */
				lDataToHash_au8[12] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0xFF000000U) >> 24U );
				lDataToHash_au8[13] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x00FF0000U) >> 16U );
				lDataToHash_au8[14] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x0000FF00U) >> 8U );
				lDataToHash_au8[15] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x000000FFU) );

				/* Call MD4 function to compute the hash */
				lFResult_u32 = rba_EthTcp_ComputeMd4Hash( lDataToHash_au8, 16U );
			}
			break;
			#endif

			#if ( TCPIP_IPV6_ENABLED == STD_ON )
			case TCPIP_AF_INET6:
			{
				VAR( uint8, AUTOMATIC )		lDataToHash_au8[40];
				VAR( uint32, AUTOMATIC )	lLoopIdx_u32;
				VAR( uint32, AUTOMATIC )	lCurrIdx_u32 = 0;

				/* Local IP */
				for(lLoopIdx_u32 = 0; lLoopIdx_u32 < 4u; lLoopIdx_u32++)
				{
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lIPAddrParamType_pun->IPv6Par_st.IpAddr_st.Addr_au32[lLoopIdx_u32] & 0xFF000000U) >> 24U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lIPAddrParamType_pun->IPv6Par_st.IpAddr_st.Addr_au32[lLoopIdx_u32] & 0x00FF0000U) >> 16U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lIPAddrParamType_pun->IPv6Par_st.IpAddr_st.Addr_au32[lLoopIdx_u32] & 0x0000FF00U) >> 8U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lIPAddrParamType_pun->IPv6Par_st.IpAddr_st.Addr_au32[lLoopIdx_u32] & 0x000000FFU) );
				}

				/* Local Port */
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].LocalPort_u16 & 0xFF00U) >> 8U );
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].LocalPort_u16 & 0x00FFU) );

				/* Remote IP */
				for(lLoopIdx_u32 = 0; lLoopIdx_u32 < 4u; lLoopIdx_u32++)
				{
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv6Addr_au32[lLoopIdx_u32] & 0xFF000000U) >> 24U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv6Addr_au32[lLoopIdx_u32] & 0x00FF0000U) >> 16U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv6Addr_au32[lLoopIdx_u32] & 0x0000FF00U) >> 8U );
					lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (lTcpDynSockTbl_pst->RemoteIPAddr_un.IPv6Addr_au32[lLoopIdx_u32] & 0x000000FFU) );
				}

				/* Remote Port */
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RemotePort_u16 & 0xFF00U) >> 8U );
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RemotePort_u16 & 0x00FFU) );

				/* Secret */
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0xFF000000U) >> 24U );
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x00FF0000U) >> 16U );
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x0000FF00U) >> 8U );
				lDataToHash_au8[lCurrIdx_u32++] = (uint8)( (rba_EthTcp_IsnContext_st.IsnSecret_u32 & 0x000000FFU) );

				/* Call MD4 function to compute the hash */
				lFResult_u32 = rba_EthTcp_ComputeMd4Hash( lDataToHash_au8, 40U );
			}
			break;
			#endif

			default:
			{
				/* If execution reaches here, then the IP support for the specified domain is not enabled; set return value to E_NOT_OK. */
				lRetVal_en = E_NOT_OK;
			}
			break;
		}

		if( lRetVal_en == E_OK )
		{
			/* Compute the Initial Sequence Number as per expression in RFC6528 */
			/* (ISN = M + F(localip, localport, remoteip, remoteport, secretkey)) */
			lGeneratedIsn_u32 = rba_EthTcp_IsnContext_st.IsnClock_u32 + lFResult_u32;

			/* Increment the number of time the current secret has been used */
			rba_EthTcp_IsnContext_st.IsnSecretUsageCntr_u8++;

			/* Check if the current secret has been used too much */
			if( rba_EthTcp_IsnContext_st.IsnSecretUsageCntr_u8 >= RBA_ETHTCP_ISN_MAX_SECRET_USAGE )
			{
				/* Select another secret pseudo randomly */
				rba_EthTcp_IsnContext_st.IsnSecret_u32 = TcpIp_RandNumXor64();

				/* Reset the secret timer */
				rba_EthTcp_IsnContext_st.IsnSecretTimer_u16 = 0U;

				/* Reset number of time the secret has been used */
				rba_EthTcp_IsnContext_st.IsnSecretUsageCntr_u8 = 0U;
			}
		}
	}
#endif

    return lGeneratedIsn_u32;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ComputeMd4Hash()     - This function compute the MD4 hash according to RFC1320                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** Data_cpu8                       - Pointer to a linear buffer containing the data to hashed                                  **/
/** Size_u16                        - Length of the data array                                                                  **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   - uint32                                                                                    **/
/**                                     MD4 hash generated from the input data array                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
static FUNC( uint32, RBA_ETHTCP_CODE ) rba_EthTcp_ComputeMd4Hash(   P2VAR( uint8, AUTOMATIC, AUTOMATIC )            Data_pu8,
                                                                    VAR( uint16, AUTOMATIC )                        Size_u16 )
{
    /* Declare local variables */
    VAR( uint32, AUTOMATIC )                lA_u32;
    VAR( uint32, AUTOMATIC )                lB_u32;
    VAR( uint32, AUTOMATIC )                lC_u32;
    VAR( uint32, AUTOMATIC )                lD_u32;
    VAR( uint32, AUTOMATIC )                lOutputHash_u32;
    VAR( uint16, AUTOMATIC )                lUsed_u16;
    VAR( uint16, AUTOMATIC )                lAvailable_u16;
    VAR( uint16, AUTOMATIC )                lIdx_u16;
    VAR( uint8, AUTOMATIC )                 lBuffer_au8[64];

    /* -------------------------------- */
    /* MD4 Init                         */
    /* -------------------------------- */

    /* Initialize A, B, C and D */
    lA_u32 = 0x67452301U;
    lB_u32 = 0xEFCDAB89U;
    lC_u32 = 0x98BADCFEU;
    lD_u32 = 0x10325476U;

    /* -------------------------------- */
    /* Process data above 64 bytes      */
    /* -------------------------------- */
    if( Size_u16 >= 64U )
    {
        /* Process Md4 block */
        Data_pu8 = rba_EthTcp_ProcessMd4Block(  Data_pu8,
                                                Size_u16 & ~(uint16)( 0x3FU ),
                                                &lA_u32,
                                                &lB_u32,
                                                &lC_u32,
                                                &lD_u32 );

        /* Update size */
        Size_u16 &= 0x3FU;
    }

    /* -------------------------------- */
    /* Copy rest of data in MD4 buffer  */
    /* -------------------------------- */

    /* Copy the rest of the data into Md4 buffer */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    (void)rba_BswSrv_MemCopy( lBuffer_au8,
                              Data_pu8,
                              Size_u16 );

    /* ---------------------------------- */
    /* Compute used and available length  */
    /* ---------------------------------- */

    /* Compute used length */
    lUsed_u16 = Size_u16 & 0x3FU;

    /* Set 0x80 after the used part in the buffer */
    lBuffer_au8[lUsed_u16] = 0x80U;

    /* Increment used length by 1 */
    lUsed_u16++;

    /* Compute available length */
    lAvailable_u16 = 64U - lUsed_u16;

    /* --------------------------------------- */
    /* Process if available size is too small  */
    /* --------------------------------------- */
    if( lAvailable_u16 < 8U )
    {
        /* Set memory to 0 in the unused part of the Md4 buffer */
        for( lIdx_u16 = 0U; lIdx_u16 < lAvailable_u16; lIdx_u16++ )
        {
            lBuffer_au8[lUsed_u16 + lIdx_u16] = 0U;
        }

        /* Process Md4 block */
        (void)rba_EthTcp_ProcessMd4Block(  lBuffer_au8,
                                           64U,
                                           &lA_u32,
                                           &lB_u32,
                                           &lC_u32,
                                           &lD_u32 );

        lUsed_u16 = 0U;
        lAvailable_u16 = 64U;
    }

    /* -------------------------------- */
    /* Append padding bits              */
    /* -------------------------------- */

    /* Set memory to 0 in the unused part of the Md4 buffer */
    for( lIdx_u16 = 0U; lIdx_u16 < (lAvailable_u16 - 8U); lIdx_u16++ )
    {
        lBuffer_au8[lUsed_u16 + lIdx_u16] = 0U;
    }

    /* -------------------------------- */
    /* Append length                    */
    /* -------------------------------- */

    /* Set the end of the Md4 buffer */
    Size_u16 = (uint16)( Size_u16 << 3U );
    lBuffer_au8[56] = (uint8)( Size_u16 );
    lBuffer_au8[57] = (uint8)( Size_u16 >> 8U );
    lBuffer_au8[58] = (uint8)( Size_u16 >> 16U );
    lBuffer_au8[59] = (uint8)( Size_u16 >> 24U );
    lBuffer_au8[60] = 0U;
    lBuffer_au8[61] = 0U;
    lBuffer_au8[62] = 0U;
    lBuffer_au8[63] = 0U;

    /* ---------------------------------- */
    /* Process last 16-Word block         */
    /* ---------------------------------- */

    /* Process Md4 block */
    (void)rba_EthTcp_ProcessMd4Block(  lBuffer_au8,
                                       64U,
                                       &lA_u32,
                                       &lB_u32,
                                       &lC_u32,
                                       &lD_u32 );

    /* -------------------------------- */
    /* Output                           */
    /* -------------------------------- */

    /* Compute the hash from A only */
    /* (we want a 32b MD4 hash) */
    lOutputHash_u32 =   (uint32)( (lA_u32 & 0x000000FF) << 24U )                    |
                        (uint32)( (uint32)((lA_u32 & 0x0000FF00) >> 8U ) << 16U )   |
                        (uint32)( (uint32)((lA_u32 & 0x00FF0000) >> 16U ) << 8U )   |
                        (uint32)( (uint32)((lA_u32 & 0xFF000000) >> 24U ) );

    return lOutputHash_u32;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_ProcessMd4Block()    - This function processes one or more 64-byte data blocks                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** Data_pu8                        - Pointer to a linear buffer containing the data block to be hashed                         **/
/** Size_u16                        - Length of the data array                                                                  **/
/**                                                                                                                             **/
/** Parameters (inout):                                                                                                         **/
/** A_pu32                          - Md4 A value                                                                               **/
/** B_pu32                          - Md4 B value                                                                               **/
/** C_pu32                          - Md4 C value                                                                               **/
/** D_pu32                          - Md4 D value                                                                               **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   - uint8*                                                                                    **/
/**                                     Pointer to the next data block to be processed                                          **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
static P2VAR( uint8, AUTOMATIC, AUTOMATIC ) rba_EthTcp_ProcessMd4Block( P2VAR( uint8, AUTOMATIC, AUTOMATIC )    Data_pu8,
                                                                        VAR( uint16, AUTOMATIC )                Size_u16,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   A_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   B_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   C_pu32,
                                                                        P2VAR( uint32, AUTOMATIC, AUTOMATIC )   D_pu32 )
{
    /* Declare local variables */
    VAR( uint32, AUTOMATIC )                lA_u32;
    VAR( uint32, AUTOMATIC )                lB_u32;
    VAR( uint32, AUTOMATIC )                lC_u32;
    VAR( uint32, AUTOMATIC )                lD_u32;
    VAR( uint32, AUTOMATIC )                lSavedA_u32;
    VAR( uint32, AUTOMATIC )                lSavedB_u32;
    VAR( uint32, AUTOMATIC )                lSavedC_u32;
    VAR( uint32, AUTOMATIC )                lSavedD_u32;
    VAR( uint32, AUTOMATIC )                lBlock_au32[16];
    VAR( uint16, AUTOMATIC )                lBlockIdx_u16;
    VAR( uint16, AUTOMATIC )                lIdx_u16;

    /* Get values of A, B, C and D */
    lA_u32 = ( * A_pu32 );
    lB_u32 = ( * B_pu32 );
    lC_u32 = ( * C_pu32 );
    lD_u32 = ( * D_pu32 );

    /* Process each 16 word block */
    for( lBlockIdx_u16 = 0U; lBlockIdx_u16 < (Size_u16 / 64U); lBlockIdx_u16++ )
    {
        /* Convert data to a block (array of 32 bits) */
        for( lIdx_u16 = 0U; lIdx_u16 < 16U; lIdx_u16++ )
        {
            lBlock_au32[lIdx_u16] = (uint32)( Data_pu8[(lIdx_u16 * 4U)] )                              |
                                    (uint32)( (uint32)( Data_pu8[(lIdx_u16 * 4U) + 1U] ) << 8U )       |
                                    (uint32)( (uint32)( Data_pu8[(lIdx_u16 * 4U) + 2U] ) << 16U )      |
                                    (uint32)( (uint32)( Data_pu8[(lIdx_u16 * 4U) + 3U] ) << 24U);
        }

        /* Save previous values of A, B, C and D */
        lSavedA_u32 = lA_u32;
        lSavedB_u32 = lB_u32;
        lSavedC_u32 = lC_u32;
        lSavedD_u32 = lD_u32;

        /* Round 1 */
        RBA_ETHTCP_MD4_STEP_F( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[0U], 3U )
        RBA_ETHTCP_MD4_STEP_F( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[1U], 7U )
        RBA_ETHTCP_MD4_STEP_F( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[2U], 11U )
        RBA_ETHTCP_MD4_STEP_F( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[3U], 19U )
        RBA_ETHTCP_MD4_STEP_F( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[4U], 3U )
        RBA_ETHTCP_MD4_STEP_F( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[5U], 7U )
        RBA_ETHTCP_MD4_STEP_F( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[6U], 11U )
        RBA_ETHTCP_MD4_STEP_F( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[7U], 19U )
        RBA_ETHTCP_MD4_STEP_F( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[8U], 3U )
        RBA_ETHTCP_MD4_STEP_F( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[9U], 7U )
        RBA_ETHTCP_MD4_STEP_F( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[10U], 11U )
        RBA_ETHTCP_MD4_STEP_F( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[11U], 19U )
        RBA_ETHTCP_MD4_STEP_F( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[12U], 3U )
        RBA_ETHTCP_MD4_STEP_F( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[13U], 7U )
        RBA_ETHTCP_MD4_STEP_F( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[14U], 11U )
        RBA_ETHTCP_MD4_STEP_F( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[15U], 19U )

        /* Round 2 */
        RBA_ETHTCP_MD4_STEP_G( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[0U] + 0x5A827999U, 3U )
        RBA_ETHTCP_MD4_STEP_G( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[4U] + 0x5A827999U, 5U )
        RBA_ETHTCP_MD4_STEP_G( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[8U] + 0x5A827999U, 9U )
        RBA_ETHTCP_MD4_STEP_G( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[12U] + 0x5A827999U, 13U )
        RBA_ETHTCP_MD4_STEP_G( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[1U] + 0x5A827999U, 3U )
        RBA_ETHTCP_MD4_STEP_G( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[5U] + 0x5A827999U, 5U )
        RBA_ETHTCP_MD4_STEP_G( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[9U] + 0x5A827999U, 9U )
        RBA_ETHTCP_MD4_STEP_G( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[13U] + 0x5A827999U, 13U )
        RBA_ETHTCP_MD4_STEP_G( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[2U] + 0x5A827999U, 3U )
        RBA_ETHTCP_MD4_STEP_G( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[6U] + 0x5A827999U, 5U )
        RBA_ETHTCP_MD4_STEP_G( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[10U] + 0x5A827999U, 9U )
        RBA_ETHTCP_MD4_STEP_G( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[14U] + 0x5A827999U, 13U )
        RBA_ETHTCP_MD4_STEP_G( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[3U] + 0x5A827999U, 3U )
        RBA_ETHTCP_MD4_STEP_G( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[7U] + 0x5A827999U, 5U )
        RBA_ETHTCP_MD4_STEP_G( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[11U] + 0x5A827999U, 9U )
        RBA_ETHTCP_MD4_STEP_G( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[15U] + 0x5A827999U, 13U )

        /* Round 3 */
        RBA_ETHTCP_MD4_STEP_H( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[0U] + 0x6ED9EBA1U, 3U )
        RBA_ETHTCP_MD4_STEP_H( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[8U] + 0x6ED9EBA1U, 9U )
        RBA_ETHTCP_MD4_STEP_H( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[4U] + 0x6ED9EBA1U, 11U )
        RBA_ETHTCP_MD4_STEP_H( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[12U] + 0x6ED9EBA1U, 15U )
        RBA_ETHTCP_MD4_STEP_H( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[2U] + 0x6ED9EBA1U, 3U )
        RBA_ETHTCP_MD4_STEP_H( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[10U] + 0x6ED9EBA1U, 9U )
        RBA_ETHTCP_MD4_STEP_H( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[6U] + 0x6ED9EBA1U, 11U )
        RBA_ETHTCP_MD4_STEP_H( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[14U] + 0x6ED9EBA1U, 15U )
        RBA_ETHTCP_MD4_STEP_H( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[1U] + 0x6ED9EBA1U, 3U )
        RBA_ETHTCP_MD4_STEP_H( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[9U] + 0x6ED9EBA1U, 9U )
        RBA_ETHTCP_MD4_STEP_H( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[5U] + 0x6ED9EBA1U, 11U )
        RBA_ETHTCP_MD4_STEP_H( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[13U] + 0x6ED9EBA1U, 15U )
        RBA_ETHTCP_MD4_STEP_H( lA_u32, lB_u32, lC_u32, lD_u32, lBlock_au32[3U] + 0x6ED9EBA1U, 3U )
        RBA_ETHTCP_MD4_STEP_H( lD_u32, lA_u32, lB_u32, lC_u32, lBlock_au32[11U] + 0x6ED9EBA1U, 9U )
        RBA_ETHTCP_MD4_STEP_H( lC_u32, lD_u32, lA_u32, lB_u32, lBlock_au32[7U] + 0x6ED9EBA1U, 11U )
        RBA_ETHTCP_MD4_STEP_H( lB_u32, lC_u32, lD_u32, lA_u32, lBlock_au32[15U] + 0x6ED9EBA1U, 15U )

        /* Update A, B, C and D */
        lA_u32 += lSavedA_u32;
        lB_u32 += lSavedB_u32;
        lC_u32 += lSavedC_u32;
        lD_u32 += lSavedD_u32;

        /* Increment the data pointer as 64 bytes of data have been processed */
        Data_pu8 += 64U;
    }

    /* Set the new values of A, B, C and D as out argument of the function */
    ( * A_pu32 ) = lA_u32;
    ( * B_pu32 ) = lB_u32;
    ( * C_pu32 ) = lC_u32;
    ( * D_pu32 ) = lD_u32;

    return Data_pu8;
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */



