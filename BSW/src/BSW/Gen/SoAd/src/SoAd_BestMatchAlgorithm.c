

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

#ifdef SOAD_DEBUG_AND_TEST
#include "TestSoAdApplication.h"
#endif

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#define SOAD_BEST_MATCH_ALGO_MAX_PRIORITY_NUM       3

/*
 ***************************************************************************************************
 * Prototype for Static functions: Start
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

LOCAL_INLINE FUNC( void, SOAD_CODE )      SoAd_RunBestMatchAlgoWithRmtAddr  ( VAR(SoAd_SoConIdType, AUTOMATIC)                   DynSocketId_uo, \
                                                                              P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)  RemoteAddr_cpst, \
                                                                              P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 MatchId_pu8 );

/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_BestMatchAlgorithm()
 *
 * \Function description
 * The function implements the best match algorithm according to below steps.
 *  SWS_SoAd_00680SoAd shall use the following best match algorithm to select a socket connection of a socket
 *  connection group based on a provided (specific) remote address:
 *  1   socket connections that have no (specific or wildcard) remote address set shall be ignored
 *  2   the remote address of the remaining socket connections shall be compared with the provided remote address and
 *  the socket connection with the best match according to the following ordered list (item listed earlier has
 *  higher priority towards items listed later) shall be selected:
 *  a   IP address and port match
 *  b   IP address match (and wildcard set for port)
 *  c   Port match (and wildcard set for IP address)
 *  d   Wildcards are used for both IP address and port
 *  e   No match (i.e. no socket connections can be selected)
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo : Socket connection Id
 * \param   SoAd_SoConIdType
 * \arg     SoConGrpId_uo: Socket connection group Id.
 * \param   uint32
 * \arg     RxHeaderId_32: Rx Pdu Header Id.
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddrPtr_cpst: pointer to IP address and port of the remote host.
 *
 * Parameters (inout):   * \param   uint8
 * \arg     SocketIdBestMatch_puo : socket Id for which best match of the remote address is occurred.
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK :      Best match found for the given entry
 *          E_NOT_OK:   not found
 *
 ***********************************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_BestMatchAlgorithm( VAR  ( SoAd_SoConIdType, AUTOMATIC )                 SoConId_uo, \
                                                           VAR( SoAd_SoConIdType, AUTOMATIC )                   SoConGrpId_uo , \
                                                           VAR( uint32, AUTOMATIC )                             RxHeaderId_32 , \
                                                           P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr_cpst, \
                                                           P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )      SocketIdBestMatch_puo )
{
    /* End of socket id in the group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lEndSocketId_uo ;

	/* variable to store index of the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lStaticSocketId_uo ;

    /* variable to signalize that the index found */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxFind_auo[4];

    /* Variable to store the dynamic config table id*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo ;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lRetVal_u8;

    /* Index for looping across the finding socket */
    VAR(uint8, AUTOMATIC)                                   lIdxMatch_u8 ;

    /* Index for looping across the finding socket */
    VAR(uint8, AUTOMATIC)                                   lIdxHighPrioMatch_u8 ;

    /* variable to identify that the index found */
    VAR(boolean, AUTOMATIC)                                 lIsIdxFindMask_ab[4];

    /* Variable to store the status */
    VAR(boolean, AUTOMATIC)                                 lSoConIdFound_b;

    /*Initialization of local variables */
    lIdxFind_auo[0]        = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
    lIdxFind_auo[1]        = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
    lIdxFind_auo[2]        = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
    lIdxFind_auo[3]        = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
    lRetVal_u8             = E_NOT_OK;
    lIdxMatch_u8           = 0xFF;
    lIdxHighPrioMatch_u8   = 0xFF;
    lIsIdxFindMask_ab[0]   = FALSE;
    lIsIdxFindMask_ab[1]   = FALSE;
    lIsIdxFindMask_ab[2]   = FALSE;
    lIsIdxFindMask_ab[3]   = FALSE;
    lSoConIdFound_b        = FALSE;

    /* Calculate the end socket id from Group table and max socket count */
    lEndSocketId_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoConGrpId_uo].startSoConIdx_uo + \
                      SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoConGrpId_uo].maxSoConChannel_uo;

    /* loop through all the sockets connection through the socket connection group for the processing */
    for( lStaticSocketId_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoConGrpId_uo].startSoConIdx_uo ; \
                    ((lStaticSocketId_uo < lEndSocketId_uo) && \
                     ((FALSE == lIsIdxFindMask_ab[0]) || (lStaticSocketId_uo == SoConId_uo) )); \
            lStaticSocketId_uo++ )
    {
        /* Reset the lSoConIdFound_b flag to FALSE for each loop */
        lSoConIdFound_b = FALSE;

        /* Get the dynamic socket from static socket table */
        lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lStaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

        /* Check dynamic socket is valid */
        if(lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo)
        {
            /* Call the below function to apply the best match algorithm and to get the match id to which romote address matched */
            SoAd_RunBestMatchAlgoWithRmtAddr(lIdxDynSocket_uo, RemoteAddrPtr_cpst, &lIdxMatch_u8 );

            /* If SoAd_RunBestMatchAlgoWithRmtAddr failed (means that no matching has been found) or if the priority of the matching rule is not high enough */
            if( (0xFFU == lIdxMatch_u8 )  || \
                (lIdxMatch_u8 > lIdxHighPrioMatch_u8) || \
                 ( (lIdxMatch_u8 == lIdxHighPrioMatch_u8) && \
                   ( (SoConId_uo == SOAD_CFG_SOCON_ID_DEFAULT_VALUE) || \
                   (lStaticSocketId_uo != SoConId_uo) ) ) )
            {
                continue;
            }

            /* ------------------------------------- */
            /* Best Match Algorithm performs from LL */
            /* ------------------------------------- */

            /* 1. SoConId_uo == SOAD_CFG_SOCON_ID_DEFAULT_VALUE */
            /*    Condition will be applicable for Rx path when its called from SoAd_TcpAccepted() for Tcp server socket or from SoAd_RxIndication() for UDP multi sockets */
            if( SoConId_uo == SOAD_CFG_SOCON_ID_DEFAULT_VALUE )
            {
                /* --------------- */
                /* Header disabled */
                /* --------------- */

                /* Specific configuration: First Tx pdu socket and then Rx pdu socket in group */
                /* If sockets are configured in the above order, suppose if we are receiving the packet from remote and */
                /* Best Match Algo ran and returns the socket which matches first(Tx pdu socket) in the group, */
                /* SoAd will discard the packet since no Rx Pdu mapped because it is Tx only socket. */

                /* In the scenario, Best Match Algo has to fetch the Rx pdu socket if any instead of Tx Pdu socket. */
                /* 1. succeed for 1st socket in the group */
                /* 2,3 & 4. If earlier matched socket is mapped to Tx pdu socket, but new matched socket has mapped to Rx Pdu, */
                /*          then Best match Algo has to fetch the socket which is mapped to Rx pdu(second match) */
                if( (RxHeaderId_32 == 0U)                           && \
                    ((FALSE == lIsIdxFindMask_ab[lIdxMatch_u8])  || \
                     ((TRUE  == lIsIdxFindMask_ab[lIdxMatch_u8]) && \
                      (0U == SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxFind_auo[lIdxMatch_u8]].numberOfRxPdusConfigured_u8) && \
                      (0 < SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lStaticSocketId_uo].numberOfRxPdusConfigured_u8))) )
                {
                    lSoConIdFound_b = TRUE;
                }

                /* --------------- */
                /* Header enabled  */
                /* --------------- */
                /* If header is enabled, then match the RxPdu header id as well along the Remote info */
                /* Bug fix scenario: Header Id will be diff for each Rx Pdu's, If Header Id is not compared, */
                /* then there is chance to fetch the socket id which not belongs to corresponding UL(header id wont match), so packet will be discarded. */
                if( RxHeaderId_32 != 0U )
                {
                    lSoConIdFound_b = SoAd_IsMatchRxPduFound(lStaticSocketId_uo, RxHeaderId_32);
                }
            }

            /* ------------------------------------- */
            /* Best Match Algorithm performs from UL */
            /* ------------------------------------- */
            else
            {
                lSoConIdFound_b = TRUE;
            }

            /* If any of the socket Best Match Algo success, then store the following information
             * 1. Prio Match according to function SoAd_RunBestMatchAlgoWithRmtAddr()
             * 2. set the flag to TRUE to notify match found for the praticular match index
             * 3. store the static socon id to which Best match found
             * */
            if( TRUE == lSoConIdFound_b )
            {
                lIdxHighPrioMatch_u8 = lIdxMatch_u8;
                lIsIdxFindMask_ab[lIdxMatch_u8] = TRUE;
                lIdxFind_auo[lIdxMatch_u8] = lStaticSocketId_uo;
            }
        }
    }

    /* Finally load the static socket index which we found after applying the
    * Best Match Algo by looking all the sockets which are presents in group */
    if(SOAD_BEST_MATCH_ALGO_MAX_PRIORITY_NUM >= lIdxHighPrioMatch_u8)
    {
        /* load the found socon id to out param  SocketIdBestMatch_puo */
        ( *SocketIdBestMatch_puo ) = lIdxFind_auo[lIdxHighPrioMatch_u8];
        lRetVal_u8  = E_OK;
    }

#ifdef SOAD_DEBUG_AND_TEST
    SoAd_RetVal_BestMatch_tst = lRetVal_u8;
#endif

    return(lRetVal_u8);
}

/**
 ***************************************************************************************************
 * \Function Name : SoAd_RunBestMatchAlgoWithRmtAddr()
 *
 * \Function description
 * The function implements the best match algorithm according to below steps.
 *  a   IP address and port match
 *  b   IP address match (and wildcard set for port)
 *  c   Port match (and wildcard set for IP address)
 *  d   Wildcards are used for both IP address and port
 *  e   No match (i.e. no socket connections can be selected)
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo : Dynamic socket id mapped to static socket id
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddr_cpst: pointer to IP address and port of the remote host.
 *
 *
 * Parameters (inout):
 * \param   uint8*
 * \arg     MatchId_pu8 : socket Id for which best match of the remote address is occurred.
 *
 * Parameters (out):    None
 *
 * Return value: None
 ***************************************************************************************************
 */
LOCAL_INLINE FUNC( void, SOAD_CODE ) SoAd_RunBestMatchAlgoWithRmtAddr( VAR(SoAd_SoConIdType, AUTOMATIC)                   DynSocketId_uo, \
                                                                 P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)  RemoteAddr_cpst, \
                                                                 P2VAR(uint8, AUTOMATIC, AUTOMATIC)                 MatchId_pu8 )
{
    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Variable to hold if the remote address and the address from dynamic socket are equal */
    VAR(boolean, AUTOMATIC)                                 lAddressesAreEqual_b;

    /* Variable to store the port for dynamic socket */
    VAR(uint16, AUTOMATIC)                                  lDyncSocPort_u16;

    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)                                  lRemoteAddrPort_u16;

    /* Variable to store if the remote address of dynamic socket is wildcard (ANY)  */
    VAR(boolean, AUTOMATIC)                                 lDyncSocConfigHasWildcardAnyAddr_b;

    /* Get the index of related socket connection group */
    lSoAdDyncSocConfig_pst   =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

	/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
    lAddressesAreEqual_b               = SOAD_SOCK_IPADDR_IS_EQUAL_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR(RemoteAddr_cpst, lSoAdDyncSocConfig_pst);
    lDyncSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG(lSoAdDyncSocConfig_pst);
	/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
    lRemoteAddrPort_u16                = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddr_cpst);
    lDyncSocConfigHasWildcardAnyAddr_b = SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR(lSoAdDyncSocConfig_pst);



    /* if the remote IP address and port match */
    if( lAddressesAreEqual_b && ( lRemoteAddrPort_u16 == lDyncSocPort_u16 ) )
    {
        ( *MatchId_pu8 ) = 0;
    }
    /* if the remote IP address is match and port is wildcard */
    else if( lAddressesAreEqual_b && ( TCPIP_PORT_ANY == lDyncSocPort_u16 ) )
    {
        ( *MatchId_pu8 ) = 1;
    }
    /* if the remote port is match and IP is wildcard */
    else if( lDyncSocConfigHasWildcardAnyAddr_b && ( lRemoteAddrPort_u16 == lDyncSocPort_u16 ) )
    {
        ( *MatchId_pu8 ) = 2;
    }
    /* Remote IP and port are wildcard */
    else if( lDyncSocConfigHasWildcardAnyAddr_b && ( TCPIP_PORT_ANY == lDyncSocPort_u16 ) )
    {

        ( *MatchId_pu8 ) = 3;
    }
    /* No match, so update FF to the variable */
    else
    {
        ( *MatchId_pu8 ) = 0xFF;
    }

}

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */

