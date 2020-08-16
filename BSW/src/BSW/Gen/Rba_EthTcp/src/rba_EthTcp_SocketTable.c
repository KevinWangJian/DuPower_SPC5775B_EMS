

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "SoAd.h"
#include "SoAd_Cbk.h"					/* Required for SoAd call-back functions */

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"

#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - TcpIp and SoAd"
#endif

#if (!defined(SOAD_AR_RELEASE_MINOR_VERSION) || (SOAD_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - TcpIp and SoAd"
#endif


/*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_GetNewSock()  	- Open a new Tcp socket                                                                         **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** RxFrame_cpst 				- Tcp frame structure containing all the received packet information 							**/
/** FramePrio_u8                - Frame priority which will be used for new socket                                              **/
/**          																													**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):																											**/
/** TcpDynSockTblIdx_puo 		- Index of the rba_EthTcp internal socket table	(new socket)									**/
/**                                                                                                                             **/
/** Return value:        		- Std_ReturnType                                                                                **/
/**                         		E_OK: Socket is successfully opened                                                         **/
/**                          		E_NOT_OK: Socket is not opened                                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_GetNewSock ( P2CONST( rba_EthTcp_NewSockInfo_tst, AUTOMATIC, AUTOMATIC )		NewSockInfo_cpst,
                                                                P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )				TcpDynSockTblIdx_puo )
{
	/* Declare local variables */
	VAR( TcpIp_SocketIdType, AUTOMATIC ) 			lTcpSockId_uo;
	VAR( Std_ReturnType, AUTOMATIC )                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                lRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get a new Tcp socket */
	lRetVal_en = rba_EthTcp_GetSocket(NewSockInfo_cpst->DomainType_u32, &lTcpSockId_uo );

	if ( lRetVal_en == E_OK )
	{
        /* Update local address id in socket table */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].LocalAddrId_u8     = NewSockInfo_cpst->LocalAddrId_u8;

        /* Update local port in socket table */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].LocalPort_u16      = NewSockInfo_cpst->LocalPort_u16;

        /* Update destination IPv4 address in the socket table */
        RBA_ETHTCP_COPY_IPADDR( rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].DomainType_u32, &(rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].RemoteIPAddr_un), &(NewSockInfo_cpst->RemoteIPAddr_un) )

        /* Update destination port in socket table */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].RemotePort_u16     = NewSockInfo_cpst->RemotePort_u16;

        /* Update the socket frame priority value to statically configured TcpIpIpFramePrioDefault */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].SockFramePrio_u8   = NewSockInfo_cpst->FramePrio_u8;

        /* Update the calculated local MSS in socket table */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].LocalMss_u16       = rba_EthTcp_MSS_cau16[NewSockInfo_cpst->LocalAddrId_u8];

        /* As local and remote address is assigned,change the socket state to RESERVED */
        rba_EthTcp_DynSockTbl_ast[lTcpSockId_uo].SockState_en       = RBA_ETHTCP_SOCK_RESERVED_E;

        /* Set the out argument of the function (index of the new Tcp socket) */
        ( * TcpDynSockTblIdx_puo )                                  = lTcpSockId_uo;

        /* Set the return value of the function to E_OK */
        lFunctionRetVal_en                                          = E_OK;
    }

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ReopenSock()     - Reopen a new Tcp socket (after reception of SYN from TIME_WAIT or LAST_ACK)                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_puo        - Tcp dynamic socket table index of the socket which need to be reopened                        **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Std_ReturnType                                                                                **/
/**                                 E_OK: Socket is successfully reopened                                                       **/
/**                                 E_NOT_OK: Socket is not reopened correctly                                                  **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ReopenSock ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    VAR( rba_EthTcp_ConnState_ten, AUTOMATIC )                      lSavedState_en;
    VAR( uint32, AUTOMATIC )                                        lSavedSndSeqNum_u32;
    VAR( rba_EthTcp_IPAddr_tun, AUTOMATIC )                         lDestIPAddr_un;
    VAR( uint16, AUTOMATIC )                                        lLocalPort_u16;
    VAR( uint16, AUTOMATIC )                                        lDestPort_u16;
    VAR( uint16, AUTOMATIC )                                        lLocalMss_u16;
    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                         lLocalAddrId_u8;
    VAR( TcpIp_DomainType, AUTOMATIC )                         		lDomainType_u32;
    VAR( uint8, AUTOMATIC )                                         lFramePrio_u8;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------- */
    /* Save info of the current socket        */
    /* -------------------------------------- */

    /* Save address information */
    lLocalAddrId_u8 = lTcpDynSockTbl_pst->LocalAddrId_u8;
    lDomainType_u32 = lTcpDynSockTbl_pst->DomainType_u32;
    lLocalPort_u16  = lTcpDynSockTbl_pst->LocalPort_u16;
    lDestIPAddr_un  = lTcpDynSockTbl_pst->RemoteIPAddr_un;
    lDestPort_u16   = lTcpDynSockTbl_pst->RemotePort_u16;

    /* Save the Frame Prio value */
    lFramePrio_u8 = lTcpDynSockTbl_pst->SockFramePrio_u8;

    /* Save the local MSS value */
    lLocalMss_u16 = lTcpDynSockTbl_pst->LocalMss_u16;

    /* Save the send sequence number of the Tcp socket */
    lSavedSndSeqNum_u32 = lTcpDynSockTbl_pst->SndSeqNum_u32;

    /* Save the actual state of the Tcp socket */
    lSavedState_en = lTcpDynSockTbl_pst->State_en;

    /* -------------------------------------- */
    /* Reopen socket                          */
    /* -------------------------------------- */

    /* Reset entry in Tcp dynamic socket table */
    rba_EthTcp_ResetTcpTableEntry( TcpDynSockTblIdx_uo );

    /* If we are in TIME_WAIT state */
    if( lSavedState_en == RBA_ETHTCP_CONN_TIME_WAIT_E )
    {
        /* For a reopening from TIME_WAIT, a callback need to be give to the UL to inform about the closing of the socket */
        /* (As SoAd has initiated the closing, then the callback is required) */

        /* Callback to SoAd */
        SoAd_TcpIpEvent( TcpDynSockTblIdx_uo, TCPIP_TCP_CLOSED );

        /* Keep the connection state of the socket to CLOSED and set the socket state to RESERVED */
        /* (the socket will be set back to TIME_WAIT and OPENED after successful linking to listening socket) */
        lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_RESERVED_E;
    }

    /* If we are in LAST_ACK */
    else
    {
        /* For a reopening from LAST_ACK, it is not necessary to give a callback to the UL, SoAd does not need to be informed */
        /* (the reopening can be done internally because SoAd did not initiated the closing, this is the remote that has initiated the closing) */

        /* Set back the connection state to LAST_ACK */
        rba_EthTcp_SetConnectionState( TcpDynSockTblIdx_uo, RBA_ETHTCP_CONN_LAST_ACK_E );

        /* Set back the socket state to OPENED */
        lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_OPENED_E;
    }

    /* -------------------------------------- */
    /* Set back info of the reopened socket   */
    /* -------------------------------------- */

    /* Set back address information */
    lTcpDynSockTbl_pst->LocalAddrId_u8      = lLocalAddrId_u8;
	lTcpDynSockTbl_pst->DomainType_u32 		= lDomainType_u32;
    lTcpDynSockTbl_pst->LocalPort_u16       = lLocalPort_u16;
    lTcpDynSockTbl_pst->RemoteIPAddr_un     = lDestIPAddr_un;
    lTcpDynSockTbl_pst->RemotePort_u16      = lDestPort_u16;

    /* Set back frame priority */
    lTcpDynSockTbl_pst->SockFramePrio_u8 = lFramePrio_u8;

    /* Set back frame local MSS value */
    lTcpDynSockTbl_pst->LocalMss_u16 = lLocalMss_u16;

    /* Set back the send sequence number of the Tcp socket */
    /* (this information will be needed to choose an ISS which is larger than the largest sequence number of the previous connection) */
    rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, lSavedSndSeqNum_u32 );

    /* -------------------------------------- */
    /* Link reopened socket                   */
    /* -------------------------------------- */

    /* Link the reopened socket to the corresponding listening socket */
    /* (the reopened socket must be a channel socket because a reopening from TIME_WAIT or LAST_ACK is a passive open) */
    lRetVal_en = rba_EthTcp_LinkToListeningSock( TcpDynSockTblIdx_uo );

    if ( lRetVal_en == E_OK )
    {
        /* Set back the connection state of the Tcp socket */
        rba_EthTcp_SetConnectionState( TcpDynSockTblIdx_uo, lSavedState_en );

        /* Set back the socket state to OPENED */
        lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_OPENED_E;

        /* Set the return value of the function to E_OK */
        lFunctionRetVal_en = E_OK;
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_LinkToListeningSock()	- Link a Tcp socket to an existing listening socket   									**/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo					- Tcp dynamic socket table index of the socket which need to be linked 					**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:        				- Std_ReturnType                                                                        **/
/**                         				E_OK: Socket is successfully linked                                                 **/
/**                          				E_NOT_OK: Socket is not linked                                                      **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_LinkToListeningSock( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lCurrTcpSocket_pst;
	VAR( TcpIp_SocketIdType, AUTOMATIC ) 								lIdx_uo;
	VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* -------------------------------------- */
	/* Find listening TcpIp socket            */
	/* -------------------------------------- */

	/* Find the listening Tcp socket */
	for (  lIdx_uo = 0U; lIdx_uo < TCPIP_TCPSOCKETMAX; lIdx_uo++ )
	{
        /* Get Tcp dynamic table entry of the current socket index */
        lCurrTcpSocket_pst = ( & ( rba_EthTcp_DynSockTbl_ast[lIdx_uo] ) );

		/* Check if we have found the listening Tcp socket with same local Ip and port of the socket which need to be linked */
		if (  ( ( lCurrTcpSocket_pst->LocalAddrId_u8 )     == rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].LocalAddrId_u8  ) &&
		        ( ( lCurrTcpSocket_pst->LocalPort_u16 )     == rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].LocalPort_u16 ) &&
			 ( ( lCurrTcpSocket_pst->RemotePort_u16 )    == ( TCPIP_PORT_ANY ) ) &&
             RBA_ETHTCP_IS_IPADDR_ANY( lCurrTcpSocket_pst->DomainType_u32, &(lCurrTcpSocket_pst->RemoteIPAddr_un) ) )
		{
		    /* -------------------------------------- */
			/* Link sockets		                      */
		    /* -------------------------------------- */

            /* Check if the listening Tcp socket is in the right state and has remaining channels */
            if( (lCurrTcpSocket_pst->State_en == RBA_ETHTCP_CONN_LISTEN_E) &&
                (lCurrTcpSocket_pst->RemainChannels_u16 > 0U) )
            {
                /* Reduce the number of remaining channels of the listening Tcp socket. One more is now in use. */
                lCurrTcpSocket_pst->RemainChannels_u16--;

                /* Link the actual Tcp socket with the listening Tcp socket*/
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].ListenTcpSockIdx_uo = lIdx_uo;

                /* Tcp socket inherit socket options from Listen socket */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SOKeepAlvIntl_u32       = lCurrTcpSocket_pst->TcpSockOpt_pst->SOKeepAlvIntl_u32;
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SOKeepAlvTime_u32       = lCurrTcpSocket_pst->TcpSockOpt_pst->SOKeepAlvTime_u32;
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SOKeepAlvProbesMax_u16  = lCurrTcpSocket_pst->TcpSockOpt_pst->SOKeepAlvProbesMax_u16;
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SOKeepAlvEnad_u8        = lCurrTcpSocket_pst->TcpSockOpt_pst->SOKeepAlvEnad_u8;
#endif
#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SONaglesEnad_u8         = lCurrTcpSocket_pst->TcpSockOpt_pst->SONaglesEnad_u8;
#endif
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TcpSockOpt_pst->SORxWindowMax_u16       = lCurrTcpSocket_pst->TcpSockOpt_pst->SORxWindowMax_u16;

                /* Update initial send window size based on the Socket Option RxWindowMax */
                rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndWndSize_u16 = lCurrTcpSocket_pst->TcpSockOpt_pst->SORxWindowMax_u16;

                /* Set the return value of the function to E_OK */
                lFunctionRetVal_en = E_OK;
            }

			/* Break the loop */
			break;
		}
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ResetSock()  - Reset the entries in Tcp dynamic socket table and give a callback to SoAd if necessary	        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo		- Tcp dynamic socket table index 																	**/
/** CloseType_en 			- Type of socket closing                         													**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:        	None                                                                  								**/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_ResetSock(	VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
													VAR( TcpIp_EventType, AUTOMATIC ) 			CloseType_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( uint8, AUTOMATIC )         									lCbkReqd_u8;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* -------------------------------------- */
	/* Determine if callback need to be given */
	/* -------------------------------------- */
	/* State of the socket connection is CLOSED */
	/* UL did not requested for opening socket*/
	if( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSED_E )                &&
	    ((lTcpDynSockTbl_pst->SockState_en == RBA_ETHTCP_SOCK_RESERVED_E ) || (lTcpDynSockTbl_pst->SockState_en == RBA_ETHTCP_SOCK_CLOSED_E)) )
	{
		lCbkReqd_u8 = TCPIP_CBK_NOT_REQD;
	}

	/* State of the socket is LISTEN and the socket is a forked socket */
	/* (The connection was initiated with a passive open) */
	else if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LISTEN_E)			&&
			  (lTcpDynSockTbl_pst->ListenTcpSockIdx_uo < TCPIP_TCPSOCKETMAX) )
	{
		lCbkReqd_u8 = TCPIP_CBK_NOT_REQD;
	}

	/* State of the socket is SYN RCVD state and previous state was LISTEN or TIME_WAIT */
	/* (The connection was initiated with a passive open - Normal case or reopening from TIME_WAIT) */
	else if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_RCVD_E) 			&&
			  ((lTcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_LISTEN_E) || (lTcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_TIME_WAIT_E)) )
	{
		lCbkReqd_u8 = TCPIP_CBK_NOT_REQD;
	}

	/* If we are in other states */
	else
	{
		lCbkReqd_u8 = TCPIP_CBK_REQD;
	}

	/* -------------------------------------- */
	/* Reset Tcp socket                       */
	/* -------------------------------------- */

	/* Reset entry in Tcp dynamic socket table */
    rba_EthTcp_ResetTcpTableEntry( TcpDynSockTblIdx_uo );

	/* Decrement the total number of used Tcp sockets */
	rba_EthTcp_SockConnCntr_u16-- ;

	/* -------------------------------------- */
	/* SoAd callback                          */
	/* -------------------------------------- */

	/* Check if a callback needs to be sent to SoAd */
    if( lCbkReqd_u8 == TCPIP_CBK_REQD )
    {
    	/* Callback to SoAd */
    	SoAd_TcpIpEvent( TcpDynSockTblIdx_uo, CloseType_en );
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ResetTcpTableEntry()	- Reset all the fields of a Tcp socket (the Tcp dynamic table entry of the socket is reset  **/
/**									to the default values)		    															**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 			- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:        			None                                                                                  		**/
/**																																**/
/*********************************************************************************************************************************/
/* HIS METRIC STMT VIOLATION IN rba_EthTcp_ResetTcpTableEntry: Number of statement is exceeded to to the number of fields of the dynamic socket table */
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_ResetTcpTableEntry( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* --------------------------------------------- */
    /* Increment remaining channels if forked socket */
    /* --------------------------------------------- */

    /* If a listening Tcp socket is linked with the socket to reset */
    if( lTcpDynSockTbl_pst->ListenTcpSockIdx_uo < TCPIP_TCPSOCKETMAX )
    {
        /* If the listening socket is in the right state (LISTEN state) */
        if( rba_EthTcp_DynSockTbl_ast[lTcpDynSockTbl_pst->ListenTcpSockIdx_uo].State_en == RBA_ETHTCP_CONN_LISTEN_E )
        {
            /* Increment the remaining channels count of the listening socket */
            /* (the listening socket has now one more channel free because we are reseting the Tcp dynamic table entry of one of its channel) */
            rba_EthTcp_DynSockTbl_ast[lTcpDynSockTbl_pst->ListenTcpSockIdx_uo].RemainChannels_u16++;
        }
    }

    /* -------------------------------------- */
    /* Reset Tcp table entry                  */
    /* -------------------------------------- */

	/* State and Tcp flag */
	lTcpDynSockTbl_pst->SockState_en                    = RBA_ETHTCP_SOCK_CLOSED_E;
	lTcpDynSockTbl_pst->State_en						= RBA_ETHTCP_CONN_CLOSED_E;
	lTcpDynSockTbl_pst->PrevState_en					= RBA_ETHTCP_CONN_CLOSED_E;
	lTcpDynSockTbl_pst->TcpFlag_en						= RBA_ETHTCP_NOTHING_E;

	/* Addresses */
	lTcpDynSockTbl_pst->DomainType_u32                  = TCPIP_AF_NONE;
	lTcpDynSockTbl_pst->LocalAddrId_u8                  = (uint8)TCPIP_LOCALADDRID_INVALID;
	lTcpDynSockTbl_pst->LocalPort_u16                   = TCPIP_PORT_ANY;
    lTcpDynSockTbl_pst->RemotePort_u16                  = TCPIP_PORT_ANY;
    RBA_ETHTCP_RESET_REMOTE_IP( &(lTcpDynSockTbl_pst->RemoteIPAddr_un) );

    /* Link to listening socket */
    lTcpDynSockTbl_pst->ListenTcpSockIdx_uo             = (TcpIp_SocketIdType)RBA_ETHTCP_TCPSOCK_UNUSED;

    /* Local data */
    lTcpDynSockTbl_pst->RemainChannels_u16              = 0x00U;
	lTcpDynSockTbl_pst->SockFramePrio_u8                = 0xFFU;
	lTcpDynSockTbl_pst->LocalMss_u16                    = RBA_ETHTCP_DFL_MSS;

	/* Tcp Tx buffer pointers */
	/* Initially, all pointers will be pointing to the start of the Tcp Tx buffer */
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	lTcpDynSockTbl_pst->TxWndUnAckedData_pu8			= lTcpDynSockTbl_pst->TxWndStrt_pu8;
	lTcpDynSockTbl_pst->TxWndNxtSnd_pu8					= lTcpDynSockTbl_pst->TxWndStrt_pu8;
	lTcpDynSockTbl_pst->TxWndNxtFree_pu8				= lTcpDynSockTbl_pst->TxWndStrt_pu8;
#endif

	/* Occupied sizes in the Tcp Tx buffer */
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16			= 0x00U;
	lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 		= 0x00U;
#endif

	/* Transmission information */
	lTcpDynSockTbl_pst->IniSndSeqNum_u32       	 		= 0x00U;
	lTcpDynSockTbl_pst->SndSeqNum_u32 					= 0x00U;
	lTcpDynSockTbl_pst->SndAckNum_u32 					= 0x00U;
	lTcpDynSockTbl_pst->SndHdrFlag_u8 					= 0x00U;
	lTcpDynSockTbl_pst->SndWndSize_u16					= rba_EthTcp_CurrConfig_cpo->RxWindowMax_u16;

	/* Reception information */
	lTcpDynSockTbl_pst->IniRcvdSeqNum_u32       		= 0x00U;
	lTcpDynSockTbl_pst->RcvdSeqNum_u32	 				= 0x00U;
	lTcpDynSockTbl_pst->RcvdAckNum_u32	 				= 0x00U;
	lTcpDynSockTbl_pst->RcvdHdrFlag_u8		 			= 0x00U;
	lTcpDynSockTbl_pst->RcvdWndSize_u16		 			= 0x00U;
	lTcpDynSockTbl_pst->RcvdMss_u16						= RBA_ETHTCP_DFL_MSS;
	lTcpDynSockTbl_pst->RcvdDataLen_u16		 			= 0x00U;
	lTcpDynSockTbl_pst->RcvdDataOffset_u16				= 0x00U;
	lTcpDynSockTbl_pst->TotalRcvdDataLen_u16			= 0x00U;

	/* Current unacknowledged data */
	lTcpDynSockTbl_pst->UnAckedSeqNum_u32 				= 0x00U;

	/* Oldest unacknowledged segment length */
	lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 	= 0x00U;

	/* Last window update */
	lTcpDynSockTbl_pst->WndUpdSeqNum_u32        		= 0x00U;
	lTcpDynSockTbl_pst->WndUpdAckNum_u32        		= 0x00U;

	/* Received duplicate ack counter */
	lTcpDynSockTbl_pst->DuplicateAckCntr_u8	 			= 0x00U;

	/* Postpone flags */
	lTcpDynSockTbl_pst->PostponeSyn_b 					= FALSE;
	lTcpDynSockTbl_pst->PostponeFin_b 					= FALSE;

	/* General Timer */
	lTcpDynSockTbl_pst->GeneralTmrSt_en					= RBA_ETHTCP_TMR_STOPPED_E;
	lTcpDynSockTbl_pst->GeneralTmr_u32            		= 0x00U;
	lTcpDynSockTbl_pst->GeneralRetryCntr_u8	 			= 0x00U;

	/* Retransmission */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->RetransmissionFlg_b				= FALSE;
#endif

	/* Dynamic retransmission */
#if ( RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON )
	lTcpDynSockTbl_pst->SRtt_u32      					= 0x00U;
	lTcpDynSockTbl_pst->RttVar_u32       				= 0x00U;
	lTcpDynSockTbl_pst->Rto_u32   						= 0x00U;
	lTcpDynSockTbl_pst->RttInProgress_b   				= FALSE;
#endif

	/* Keep alive */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->KeepAlvTmrSt_en					= RBA_ETHTCP_TMR_STOPPED_E;
	lTcpDynSockTbl_pst->KeepAlvTmr_u32	 				= 0x00U;
	lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16	 		= 0x00U;
#endif

	/* Delayed ack */
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->DlyAckTmrSt_en					= RBA_ETHTCP_TMR_STOPPED_E;
	lTcpDynSockTbl_pst->DlyAckTmr_u8	 				= 0x00U;
#endif

	/* User Timeout */
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->UtoTmrSt_en						= RBA_ETHTCP_TMR_STOPPED_E;
	lTcpDynSockTbl_pst->UtoTmr_u32   					= 0x00U;
#endif

	/* Socket option */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvIntl_u32      = rba_EthTcp_CurrConfig_cpo->KeepAlvIntl_u32;
	lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvTime_u32      = rba_EthTcp_CurrConfig_cpo->KeepAlvTime_u32;
	lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvProbesMax_u16 = rba_EthTcp_CurrConfig_cpo->KeepAlvProbesMax_u16;
	lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvEnad_u8       = STD_ON;
#endif

#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
	lTcpDynSockTbl_pst->TcpSockOpt_pst->SONaglesEnad_u8        = STD_ON;
#endif

	lTcpDynSockTbl_pst->TcpSockOpt_pst->SORxWindowMax_u16      = rba_EthTcp_CurrConfig_cpo->RxWindowMax_u16;

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_SetSeqNum()		- Set the next sequence number to be sent in the Tcp dynamic table entry of the socket			**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/** SeqNum_u32   		 		- Sequence number to be set																		**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:        		None                                                                                  			**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetSeqNum(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
							                        VAR( uint32, AUTOMATIC ) 		SeqNum_u32 )
{
	/* Set the sequence number in the Tcp dynamic table entry of the socket */
	rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndSeqNum_u32 = SeqNum_u32;

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_SetAckNum()		- Set the next acknowledgement number to be sent in the Tcp dynamic table entry of the socket	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/** AckNum_u32   		 		- Acknowledgement number to be set																**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:        		None                                                                                  			**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetAckNum(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
							                        		VAR( uint32, AUTOMATIC ) 	AckNum_u32 )
{
	/* Set the acknowledgment number in the Tcp dynamic table entry of the socket */
	rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndAckNum_u32 = AckNum_u32;

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_SetNextSendFrame()	- Set the next frame to be sent in the Tcp dynamic table entry of the socket (frame to 		**/
/**									send in the next MainFunction)																**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 			- Tcp dynamic socket table index															**/
/** TcpFlag_en   		 			- Tcp flag that represent the next frame to send											**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- Std_ReturnType																			**/
/** 									E_OK: The request has been accepted														**/
/** 									E_NOT_OK: The request has not been accepted												**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_SetNextSendFrame(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
																		VAR( rba_EthTcp_Flag_ten, AUTOMATIC )	TcpFlag_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );


	/* -------------------------------------- */
	/* Postpone frame if possible 			  */
	/* -------------------------------------- */

	/* If SEND_SYN need to be overwritten by a flag which is not NOTHING */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_SYN_E) 	&&
		(lTcpDynSockTbl_pst->RetransmissionFlg_b == FALSE)			&&
		(TcpFlag_en != RBA_ETHTCP_NOTHING_E) )
#else
	if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_SYN_E) 	&&
		(TcpFlag_en != RBA_ETHTCP_NOTHING_E) )
#endif
	{
		/* Postpone our SYN */
		lTcpDynSockTbl_pst->PostponeSyn_b = TRUE;

		/* Set our Tcp flag to NOTHING */
		lTcpDynSockTbl_pst->TcpFlag_en = RBA_ETHTCP_NOTHING_E;
	}

	/* If SEND_FIN_ACK need to be overwritten by a flag which is not NOTHING */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_FIN_ACK_E) 	&&
		(lTcpDynSockTbl_pst->RetransmissionFlg_b == FALSE)				&&
		(TcpFlag_en != RBA_ETHTCP_NOTHING_E) )
#else
	if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_FIN_ACK_E) 	&&
		(TcpFlag_en != RBA_ETHTCP_NOTHING_E) )
#endif
	{
		/* Postpone our FIN ACK */
		lTcpDynSockTbl_pst->PostponeFin_b = TRUE;

		/* Set our Tcp flag to NOTHING */
		lTcpDynSockTbl_pst->TcpFlag_en = RBA_ETHTCP_NOTHING_E;
	}

	/* --------------------------------------- */
	/* Protection against Tcp flag overwriting */
	/* --------------------------------------- */

	/* Priorities for Tcp flag overwriting : */
		/* Priority 1 - SEND_RST */
		/* Priority 2 - SEND_RST_ACK */
		/* Priority 3 - SEND_ACK_FOR_FIN_ACK */
		/* Priority 4 - SEND_FIN_ACK */
		/* Priority 5 - SEND_SYN */
		/* Priority 6 - SEND_ACK_FOR_SYN_ACK */
		/* Priority 7 - SEND_SYN_ACK */
		/* Priority 8 - SEND_ZWP */
		/* Priority 9 - SEND_DATA */
		/* Priority 10 - SEND_ACK */
		/* Priority 11 - SEND_KEEP_ALIVE */

	/* If the new priority is higher or equal to the actual priority or if the actual flag is NOTHING, the overwriting is possible */
	if( (TcpFlag_en <= lTcpDynSockTbl_pst->TcpFlag_en) || (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_NOTHING_E) )
	{
		/* If the new flag is different from the actual flag */
		if( TcpFlag_en != lTcpDynSockTbl_pst->TcpFlag_en )
		{
		    /* ------------------------------------- */
			/* Change Tcp flag                       */
		    /* ------------------------------------- */

			/* Set the new Tcp flag in the Tcp dynamic table entry of the socket */
			lTcpDynSockTbl_pst->TcpFlag_en = TcpFlag_en;

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
			/* Tcp Flag has been changed so reset the flag indicating if retransmission is running */
			/* (a frame retransmission might have been overwritten by a normal Tcp frame) */
			lTcpDynSockTbl_pst->RetransmissionFlg_b = FALSE;
#endif

            /* -------------------------------------- */
            /* Change header flag                     */
            /* -------------------------------------- */

			/* Initialize the send header flag to 0 */
			lTcpDynSockTbl_pst->SndHdrFlag_u8 = 0U;

            /* If ACK bit need to be set in next frame */
            if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_SYN_ACK_E)           ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ACK_FOR_SYN_ACK_E)   ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E)              ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ACK_E)               ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_KEEP_ALIVE_E)        ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E)               ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_FIN_ACK_E)           ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E)   ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_RST_ACK_E) )
            {
                /* Set the ACK bit in the send header flag */
                lTcpDynSockTbl_pst->SndHdrFlag_u8 |= RBA_ETHTCP_ACK_MSK;
            }

            /* If SYN bit need to be set in next frame */
            if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_SYN_E)               ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_SYN_ACK_E) )
            {
                /* Set the SYN bit in the send header flag */
                lTcpDynSockTbl_pst->SndHdrFlag_u8 |= RBA_ETHTCP_SYN_MSK;

                /* Clear the flag that indicate if the sending of the SYN needed to be postponed */
                lTcpDynSockTbl_pst->PostponeSyn_b = FALSE;
            }

            /* If FIN bit need to be set in next frame */
            if (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_FIN_ACK_E)
            {
                /* Set the FIN bit in the send header flag */
                lTcpDynSockTbl_pst->SndHdrFlag_u8 |= RBA_ETHTCP_FIN_MSK;

                /* Clear the flag that indicate if the sending of the FIN ACK needed to be postponed */
                lTcpDynSockTbl_pst->PostponeFin_b = FALSE;
            }

            /* If RST bit need to be set in next frame */
            if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_RST_E)               ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_RST_ACK_E) )
            {
                /* Set the RST bit in the send header flag */
                lTcpDynSockTbl_pst->SndHdrFlag_u8 |= RBA_ETHTCP_RST_MSK;
            }
		}

		/* Set the return value of the function to E_OK */
		lFunctionRetVal_en = E_OK;
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_SetRcvdWnd()		- Set the received window size value in the Tcp dynamic table entry of the socket				**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/** SeqNum_u32 	    			- Received sequence number																		**/
/** AckNum_u32 	    			- Received acknowledgement number																**/
/** WinSize_u16 	    		- Received Window Size from the remote which need to be saved									**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:        		None                                                                                  			**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetRcvdWnd(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
														VAR( uint32, AUTOMATIC ) 	SeqNum_u32,
														VAR( uint32, AUTOMATIC ) 	AckNum_u32,
														VAR( uint16, AUTOMATIC )	WinSize_u16	)
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( uint32, AUTOMATIC )                    						lWndRngEnd_u32;
	VAR( boolean, AUTOMATIC )                    						lWindowUpdateNeeded_b;

	/* Set the window update needed flag to FALSE */
	lWindowUpdateNeeded_b = FALSE;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst 	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Compute the sequence number corresponding to the end of our Tcp window */
	/* (SndAckNum corresponds to the next expected receive sequence number, this is the beginning of our window) */
    lWndRngEnd_u32 = ( lTcpDynSockTbl_pst->SndAckNum_u32 + (uint32)(lTcpDynSockTbl_pst->SndWndSize_u16) );

    /* -------------------------------------- */
	/* Check if window update is needed   	  */
    /* -------------------------------------- */
    switch ( lTcpDynSockTbl_pst->State_en )
    {
        /* If the socket is in SYN_SENT or SYN_RCVD state */
        case RBA_ETHTCP_CONN_SYN_SENT_E:
        case RBA_ETHTCP_CONN_SYN_RCVD_E:
        {
            /* No more check need to be done, update directly - see RFC1122 p94 */

            /* Window update is needed */
            lWindowUpdateNeeded_b = TRUE;
        }
        break;

        /* If the socket is in other state where the window update can be done */
        /* (ESTABLISHED, FIN_WAIT_1, FIN_WAIT_2, CLOSE_WAIT or CLOSING state) */
        case RBA_ETHTCP_CONN_ESTABLISHED_E:
        case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
        case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
        case RBA_ETHTCP_CONN_CLOSE_WAIT_E:
        case RBA_ETHTCP_CONN_CLOSING_E:
        {
            /* Check if the received acknowledgment number is in the right range */
            /* (RFC1122 p94 : the window should be updated if SND.UNA =< SEG.ACK =< SND.NXT) */
            if( ((lTcpDynSockTbl_pst->UnAckedSeqNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)				&&		/* Normal case */
                 ((AckNum_u32 >= lTcpDynSockTbl_pst->UnAckedSeqNum_u32) && (AckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)))
                ||
                ((lTcpDynSockTbl_pst->UnAckedSeqNum_u32 > lTcpDynSockTbl_pst->SndSeqNum_u32)				&&		/* Wrap around */
                 ((AckNum_u32 >= lTcpDynSockTbl_pst->UnAckedSeqNum_u32) || (AckNum_u32 <=  lTcpDynSockTbl_pst->SndSeqNum_u32))) )
            {
                /* RFC793 p72 : */
                /* The received window size can be updated if (SND.WL1 < SEG.SEQ or (SND.WL1 = SEG.SEQ and SND.WL2 =< SEG.ACK)) */

                /* Check for window update (no wrap around of sequence number)*/
                if( /* No wrap around of sequence number space, no wrap around of acknowledgment number space */
                    ((lTcpDynSockTbl_pst->WndUpdSeqNum_u32 <= lWndRngEnd_u32) && (lTcpDynSockTbl_pst->WndUpdAckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)                                &&
                     (((SeqNum_u32 > lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && (SeqNum_u32 <= lWndRngEnd_u32))														                        ||	/* SND.WL1 < SEG.SEQ */
                      ((SeqNum_u32 == lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && ((AckNum_u32 >= lTcpDynSockTbl_pst->WndUpdAckNum_u32) && (AckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)))))   /* SND.WL1 = SEG.SEQ and SND.WL2 =< SEG.ACK */
                    ||
                    /* No wrap around of sequence number space, wrap around of acknowledgment number space */
                    ((lTcpDynSockTbl_pst->WndUpdSeqNum_u32 <= lWndRngEnd_u32) && (lTcpDynSockTbl_pst->WndUpdAckNum_u32 > lTcpDynSockTbl_pst->SndSeqNum_u32)                                 &&
                     (((SeqNum_u32 > lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && (SeqNum_u32 <= lWndRngEnd_u32))                                                                               ||  /* SND.WL1 < SEG.SEQ */
                      ((SeqNum_u32 == lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && ((AckNum_u32 >= lTcpDynSockTbl_pst->WndUpdAckNum_u32) || (AckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32))))) ) /* SND.WL1 = SEG.SEQ and SND.WL2 =< SEG.ACK */
                {
                    /* Window update is needed */
                    lWindowUpdateNeeded_b = TRUE;
                }

                /* Check for window update (wrap around of sequence number)*/
                else if( /* Wrap around of sequence number space, no wrap around of acknowledgment number space */
                    ((lTcpDynSockTbl_pst->WndUpdSeqNum_u32 > lWndRngEnd_u32) && (lTcpDynSockTbl_pst->WndUpdAckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)                                 &&
                     (((SeqNum_u32 > lTcpDynSockTbl_pst->WndUpdSeqNum_u32) || (SeqNum_u32 <= lWndRngEnd_u32))                                                                               ||  /* SND.WL1 < SEG.SEQ */
                      ((SeqNum_u32 == lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && ((AckNum_u32 >= lTcpDynSockTbl_pst->WndUpdAckNum_u32) && (AckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32)))))   /* SND.WL1 = SEG.SEQ and SND.WL2 =< SEG.ACK */
                    ||
                    /* Wrap around of sequence number space, wrap around of acknowledgment number space */
                    ((lTcpDynSockTbl_pst->WndUpdSeqNum_u32 > lWndRngEnd_u32) && (lTcpDynSockTbl_pst->WndUpdAckNum_u32 > lTcpDynSockTbl_pst->SndSeqNum_u32)                                  &&
                     (((SeqNum_u32 > lTcpDynSockTbl_pst->WndUpdSeqNum_u32) || (SeqNum_u32 <= lWndRngEnd_u32))                                                                               ||  /* SND.WL1 < SEG.SEQ */
                      ((SeqNum_u32 == lTcpDynSockTbl_pst->WndUpdSeqNum_u32) && ((AckNum_u32 >= lTcpDynSockTbl_pst->WndUpdAckNum_u32) || (AckNum_u32 <= lTcpDynSockTbl_pst->SndSeqNum_u32))))) ) /* SND.WL1 = SEG.SEQ and SND.WL2 =< SEG.ACK */
                {
                    /* Window update is needed */
                    lWindowUpdateNeeded_b = TRUE;
                }

                /* In other cases */
                else
                {
                    /* No window update required */
                }
            }
        }
        break;

        /* If the socket is in other state */
        default:
        {
            /* Window update is not needed */
        }
        break;
    }

    /* -------------------------------------- */
	/* Execute window update  				  */
    /* -------------------------------------- */

	/* If the window update is needed */
    if( lWindowUpdateNeeded_b != FALSE )
    {
		/* Update received window size */
		lTcpDynSockTbl_pst->RcvdWndSize_u16 = WinSize_u16;

		/* Record sequence and acknowledgment numbers with received window size update */
		lTcpDynSockTbl_pst->WndUpdSeqNum_u32 = SeqNum_u32;
		lTcpDynSockTbl_pst->WndUpdAckNum_u32 = AckNum_u32;
    }

	return;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */






















