

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_CheckValidityOfLocalAddr ( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId_u8 );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_CheckLocalAddrNotInUse	( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId_u8,
																					  P2VAR( uint16, AUTOMATIC, AUTOMATIC )  	PortPtr_pu16 );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_ExecuteBind              ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                                      VAR( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId_u8,
                                                                                      VAR( uint16, AUTOMATIC )                  LocalPort_u16,
                                                                                      VAR( uint8, AUTOMATIC )                   FramePrio_u8 );
#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Interface functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_Bind()	- By this API service the TCP/IP stack is requested to bind a TCP socket to a local resource 			**/
/**                                                                                                                  			**/
/** Parameters (in):                                                                                                 			**/
/** TcpSockId_uo      	- Tcp Socket id                                    														**/
/** LocalAddrId_u8    	- Local address identifier representing the local IP address and EthIf controller to bind the   	    **/
/**                     socket to.                                                                                              **/
/** FramePrio_u8        - Frame priority configured for the socket identified by socketId                                       **/
/**                                                                                                                  			**/
/** Parameters (inout):                                                                                              			**/
/** PortPtr_pu16        - Local port to which the socket shall be bound.                                           				**/
/**                                                                                                                  			**/
/** Parameters (out):  	None                                                                                          			**/
/**                                                                                                                             **/
/** Return value:    	- Std_ReturnType                                                                    					**/
/**                     	E_OK: Socket is successfully bound                                               					**/
/**                      	E_NOT_OK: Socket is not bound                                                    					**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_Bind( VAR( TcpIp_SocketIdType, AUTOMATIC )       TcpSockId_uo,
                                                         VAR( TcpIp_LocalAddrIdType, AUTOMATIC )    LocalAddrId_u8,
                                                         P2VAR( uint16, AUTOMATIC, AUTOMATIC )      PortPtr_pu16,
                                                         VAR( uint8, AUTOMATIC )                    FramePrio_u8 )

{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                       lDetErrorFlag_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if received socket id is more than no of configured TCP sockets  */
    rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if PortPtr_pu16 is NULL pointer */
    rba_EthTcp_CheckDetError( (PortPtr_pu16 == NULL_PTR), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );
    /* Report DET if received local address id is more than number of configured local address id */
    rba_EthTcp_CheckDetError( (LocalAddrId_u8 >= TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if there is Address family mismatch  */
    rba_EthTcp_CheckDetError( ((TcpSockId_uo < TCPIP_TCPSOCKETMAX) && (LocalAddrId_u8 < TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8) &&
                              (rba_EthTcp_DynSockTbl_ast[TcpSockId_uo].DomainType_u32 != TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].IpDomainType_u32)),
                              RBA_ETHTCP_E_BIND, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
        lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

        /* Process only when the socket is ALLOCATED */
        if( lTcpDynSockTbl_pst->SockState_en == RBA_ETHTCP_SOCK_ALLOCATED_E )
        {
            /* -------------------------------------- */
            /* Check validity of local address        */
            /* -------------------------------------- */

			/* Check the validity of the local address given in argument */
			lRetVal_en = rba_EthTcp_CheckValidityOfLocalAddr( LocalAddrId_u8 );

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
            /* Report DET error in case an error occured during local address validation */
			rba_EthTcp_CheckDetError( (lRetVal_en == E_NOT_OK), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_ADDRNOTAVAIL, &lDetErrorFlag_b );
#endif

            /* If no error occured previously */
            if( lRetVal_en == E_OK )
            {
                /* -------------------------------------- */
                /* Check if local address is not in use   */
                /* -------------------------------------- */

				/* Check if the local address to bind to is already in use by another socket */
				lRetVal_en = rba_EthTcp_CheckLocalAddrNotInUse( LocalAddrId_u8, PortPtr_pu16 );

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
				/* Report DET in case local address is already in use */
				rba_EthTcp_CheckDetError( (lRetVal_en == E_NOT_OK), RBA_ETHTCP_E_BIND , RBA_ETHTCP_E_ADDRINUSE, &lDetErrorFlag_b );
#endif

                /* If no error occured previously */
                if( lRetVal_en == E_OK )
                {
                    /* -------------------------------------- */
                    /* Bind Tcp socket                        */
                    /* -------------------------------------- */

                    /* Set the local address information of the Tcp socket */
                    rba_EthTcp_ExecuteBind( TcpSockId_uo,
                                            LocalAddrId_u8,
                                            (*PortPtr_pu16),
                                            FramePrio_u8 );

                    /* Set the return value of the function to E_OK */
                    lFunctionRetVal_en = E_OK;
                }
            }
        }
    }

    return lFunctionRetVal_en;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_CheckValidityOfLocalAddr - This function check if the local address to bind is valid and return the local IP     **/
/**                                     address as out argument                                                                 **/
/**																																**/
/**	Parameters (in):																											**/
/** LocalAddrId_u8 					    - Local address id to be checked														**/
/**																																**/
/** Parameters (inout):				    None																				    **/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:                	    - Std_ReturnType                                                                    	**/
/**                                 	    E_OK: Local address is valid                                               			**/
/**                                 	    E_NOT_OK: Local address is invalid                                             		**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CheckValidityOfLocalAddr( VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) LocalAddrId_u8 )
{
	/* Declare local variables */
	P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )		lLocalAddrConfig_pcst;
    P2VAR( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )        lIPAddrParamType_pun;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

	/* Check if the IP address mapped to the LocalAddrId is valid */
	lRetVal_en = TcpIp_CheckValidityOfLocalAddrId( LocalAddrId_u8 );
	if( lRetVal_en == E_OK )
	{
		/* Get local address info from TcpIp cfg table */
        lRetVal_en = TcpIp_GetLocalAddrIdProperties( LocalAddrId_u8, &lLocalAddrConfig_pcst );
        if( lRetVal_en == E_OK )
        {
			lIPAddrParamType_pun = &(lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->IpAddrParams_un);
			switch( lLocalAddrConfig_pcst->IpDomainType_u32 )
			{
				#if ( TCPIP_IPV4_ENABLED == STD_ON )
				case TCPIP_AF_INET:
				{
					/* Check whether the local IPv4 address is not in the Multicast address range or in reserved address group - 224.0.0.0 to 255.255.255.254 */
					if( lIPAddrParamType_pun->IPv4Par_st.IpAddr_u32 < RBA_ETHIPV4_MULTICASTADDR_MIN )
					{
						/* Local IPv4 address in not in the reserved range so the local address is validated */
						lFunctionRetVal_en = E_OK;
					}
				}
				break;
				#endif

				#if ( TCPIP_IPV6_ENABLED == STD_ON )
				case TCPIP_AF_INET6:
				{
					/* Check whether the local IPv6 address is not of Multicast type (the range 0xFF00::/8 is reserved for multicast). */
					if( rba_EthIPv6_IsIPv6AddrTypeMulticast( &(lIPAddrParamType_pun->IPv6Par_st.IpAddr_st) ) != TRUE )
					{
						lFunctionRetVal_en = E_OK;
					}
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
        }
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_CheckLocalAddrNotInUse   - This check if the local address to bind to is not already in use by another socket	**/
/**																																**/
/**	Parameters (in):																											**/
/** LocalAddrId_u8 					    - Local address id to which the socket shall be bound									**/
/**																																**/
/** Parameters (inout):																											**/
/** PortPtr_pu16        			    - Local port to which the socket shall be bound. In case PORT_ANY is given, the next 	**/
/**									    available local port will be selected automatically and returned as out argument        **/
/**																																**/
/** Parameters (out):				    None																					**/
/**																																**/
/** Return value:                	    - Std_ReturnType                                                                        **/
/**                                 	    E_OK: Local address is not used (socket can be bound to this local address)         **/
/**                                 	    E_NOT_OK: Local address is already in use                                           **/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CheckLocalAddrNotInUse( 	VAR( TcpIp_LocalAddrIdType, AUTOMATIC )    	LocalAddrId_u8,
																				    P2VAR( uint16, AUTOMATIC, AUTOMATIC )  		PortPtr_pu16 )
{
	/* Declare local variables */
    VAR( TcpIp_SocketIdType, AUTOMATIC )                            lSocIdx_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
	VAR( boolean, AUTOMATIC )                                		lPortAny_b;

	/* Initialize the return value of the function to E_OK */
    lFunctionRetVal_en = E_OK;

	/* Initialize the port ANY flag to FALSE */
	lPortAny_b = FALSE;

	/* -------------------------------------- */
	/* Determine local Port if ANY            */
	/* -------------------------------------- */

	/* If Port ANY is given in argument of the function */
	if( (*PortPtr_pu16) == TCPIP_PORT_ANY )
	{
		/* Use the next available Port in the range 49152(0xC000) to 65535(0xFFFF) */
		(*PortPtr_pu16) = rba_EthTcp_PortAny_u16;

		/* Set a flag to remember that we are in case of Port ANY */
		lPortAny_b = TRUE;
	}

	/* -------------------------------------- */
	/* Check if local address is not in use   */
	/* -------------------------------------- */

	/* Initialize loop index to 0 */
	lSocIdx_uo = 0;

	/* Loop through Tcp socket table and check if another socket is bound to to same local address id and local port */
	while( lSocIdx_uo < TCPIP_TCPSOCKETMAX )
	{
		/* Check if the local address id and Port are already in use by current socket */
		if( (rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].SockState_en >= RBA_ETHTCP_SOCK_BOUND_E)   &&
			(rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].LocalAddrId_u8 == LocalAddrId_u8)        &&
			(rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].LocalPort_u16 == (*PortPtr_pu16)) )
		{
			/* If Port ANY was given in argument of the function */
			if( lPortAny_b != FALSE )
			{
				/* Select the next available Port within the range 49152(0xC000) to 65535(0xFFFF) */
				rba_EthTcp_PortAny_u16++;

				/* If rba_EthTcp_PortAny_u16 is equal to 65535, then set rba_EthTcp_PortAny_u16 to 49152 (0xC000) */
				if ( rba_EthTcp_PortAny_u16 == TCPIP_LOCAL_PORT_ANY_END )
				{
					rba_EthTcp_PortAny_u16 = TCPIP_LOCAL_PORT_ANY_START;
				}

				/* Use the next available port in the range 49152(0xC000) to 65535(0xFFFF) */
				(*PortPtr_pu16) = rba_EthTcp_PortAny_u16;

				/* Start again the checking of local address not already in use */
				lSocIdx_uo = 0U;
			}
			else
			{
				/* Address is already in use */
				lFunctionRetVal_en = E_NOT_OK;
				break;
			}
		}
		else
		{
			/* Increment loop iteration variable */
			lSocIdx_uo++;
		}
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ExecuteBind          - Execute the binding of the Tcp socket (update the dynamic table of the socket)            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/** LocalAddrId_u8                  - Local address id to which the socket shall be bound                                       **/
/** LocalPort_u16                   - Local Port to which the socket shall be bound                                             **/
/** FramePrio_u8                    - Frame Priority to be used                                                                 **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_ExecuteBind(    VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )     LocalAddrId_u8,
                                                                VAR( uint16, AUTOMATIC )                    LocalPort_u16,
                                                                VAR( uint8, AUTOMATIC )                     FramePrio_u8 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Update the local address Id (reference to the local IP address and to the TcpIpCtrl/EthIfCtrl) used by this socket */
    lTcpDynSockTbl_pst->LocalAddrId_u8 = LocalAddrId_u8;

    /* Update the local port */
    lTcpDynSockTbl_pst->LocalPort_u16 = LocalPort_u16;

    /* Change the socket state to BOUND */
    lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_BOUND_E;

    /* In case the Frame Priority is invalid in the dynamic table */
    /* ( means that the Frame Priority was not previously updated by ChangeParameter ) */
    if( lTcpDynSockTbl_pst->SockFramePrio_u8 > TCPIP_FRAMEPRIO_MAXVAL)
    {
        /* Update the socket Frame Priority value to statically configured value given by TcpIp */
        lTcpDynSockTbl_pst->SockFramePrio_u8 = FramePrio_u8;
    }

    /* Update the calculated local MSS in Tcp socket table */
    lTcpDynSockTbl_pst->LocalMss_u16 = rba_EthTcp_MSS_cau16[LocalAddrId_u8];

    return;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */




