

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "SoAd_Cbk.h"

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

/*
 ***************************************************************************************************
 * Prototype for Static functions: Start
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF)

static FUNC( void, SOAD_CODE ) SoAd_TcpIpTcpClosedForServerSocket       ( VAR(TcpIp_SocketIdType,   AUTOMATIC)      TcpIpSocketId_uo );

#endif /* SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF */

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
static FUNC( void, SOAD_CODE ) SoAd_TcpIpUdpClosedForGroupSocket        ( VAR(TcpIp_SocketIdType,   AUTOMATIC )     TcpIpSocketId_uo );
#endif/*SOAD_UDP_GRP_PRESENT != STD_OFF*/

static FUNC( void, SOAD_CODE ) SoAd_ChangeMode                          ( VAR(SoAd_SoConIdType,     AUTOMATIC)      StaticSocketId_uo, \
                                                                          VAR( SoAd_SoConIdType,    AUTOMATIC )     DynSocketId_uo );

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_TcpIpEventDetChk                    ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo, \
                                                                          VAR( TcpIp_EventType,    AUTOMATIC )  Event_en);
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpIpEvent()
 *
 * \Function description
 *  SoAd_TcpIpEvent() gets called if the stack encounters a condition described by the values in TcpIpEvent.
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     SocketId - Socket identifier of the related local socket resource.
 * \param   TcpIp_EventType
 * \arg     Event - This parameter contains a description of the event just encountered
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 *
 ***************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_TcpIpEvent( VAR( TcpIp_SocketIdType, AUTOMATIC )  SocketId , \
                                         VAR( TcpIp_EventType,    AUTOMATIC )  Event )
{
    /* Variable to store the Index of the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Variable to store the Index of the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

#if ( (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF) || (SOAD_UDP_GRP_PRESENT != STD_OFF) )
    /* variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxSoConGroup_uo;
#endif /* (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF) || (SOAD_UDP_GRP_PRESENT != STD_OFF) */

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_TcpIpEventDetChk(SocketId, Event);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {

        /* Note:
         * SoAd_TcpIpEvent shall be called by lower layer in following cases:
         * Case 1: When applications wants to close the socket, SoAd calls TcpIp_Close(socket),
         *          then TcpIp shall perform all activities which shall release the resources for this socket in TcpIp module,
         *          And after that, TcpIp informs SoAd_TcpIpEvent(Socket, Closed).
         *
         * Case 2: If Remote node wants to close the TCP established socket, it sends FIN to TcpIp,
         *          then TcpIp shall perform all activities which shall release the resources for this socket in TcpIp module,
         *          And after that, TcpIp informs SoAd_TcpIpEvent(Socket, TCPIP_TCP_CLOSED) for established socket.
         *
         * Case 3: If EthSM of source wants to go to NO_COMM mode, then TcpIp shall close TCP Listen sockets and Established sockets linked to that.
         *          then TcpIp shall perform all activities which shall release the resources for all the TCP sockets in TcpIp module,
         *          And after that, TcpIp informs SoAd_TcpIpEvent(Socket, Closed) for listen socket and then immediately Estd sockets (most probable case).
         *
         * Actions taken in SoAd case 3: For Tcp sockets,
         * If TCPIP_TCP_CLOSED called for listen socket then all open but not established sockets which are linked with this listen sockets are set to reconnected,
         * but already established sockets depending upon this listen socket are not reconnected.
         * These established  sockets shall be reconnect only if the TCPIP_TCP_CLOSED called for the established sockets directly via SoAd_TcpIpEvent().
         * So, It is understood from TcpIp module developer that, TCPIP_TCP_CLOSED is called for listen socket and established
         * sockets at a time, but sequence of calling is not guaranteed.
         */

        /* choose the appropriate event to be handled in a specified manner */
        switch(Event)
        {
#if (SOAD_TCP_PRESENT != STD_OFF)
            case TCPIP_TCP_FIN_RECEIVED:
            {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00688] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** Within SoAd_TcpIpEvent() with Event set to TCPIP_TCP_FIN_RECEIVED SoAd shall close the related socket    ***/
                /*** by calling TcpIp_Close() with parameter abort set FALSE                                                  ***/
                /****************************************************************************************************************/

                /* Call the TcpIp_Close() with parameter abort set FALSE  as per SWS_SoAd_00688 */
                (void)TcpIp_Close(SocketId, FALSE);

                lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

                if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
                {
                    SoAd_TerminateActiveSession(lIdxDynSocket_uo);

                    /* set the global variables to skip the further transmission and reception */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;
                }

                break;
            }

            case TCPIP_TCP_RESET:           /* intentionally passed to next switch case */
            case TCPIP_TCP_CLOSED:
            {
                /* Get the index of dynamic config table from the given SocketId by using array */
                lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

                /* Condition check: dynamic socket index is valid */
                if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
                {
                    /* Get the static socket index from dynamic socket table */
                    lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

#if (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF)
                    /* Get the static group socket index from static socket table */
                    lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo ;

                    /* Check Tcp server socket is closed */
                    if( STD_OFF == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].tcpProtocolConf_cpst->tcpInitiate_u8 )
                    {
                        /* call the function to perform the close action */
                        SoAd_TcpIpTcpClosedForServerSocket(SocketId);
                    }
                    else
#endif /*SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF*/
                    {
                        SoAd_TerminateActiveSession(lIdxDynSocket_uo);

                        /* set the global variables to skip the further transmission and reception */
                        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;

                        /* Reset the entry in SoAd_TcpIpSocHandleToDynSockIdx_auo[] */
                        SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId] = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

                        /* call for a function which shall close or reconnect the SoAd sockets */
                        SoAd_ChangeMode(lIdxStaticSocket_uo, lIdxDynSocket_uo);
                    }
                }

                break;
            }
#endif /* SOAD_TCP_PRESENT != STD_OFF */

#if (SOAD_UDP_PRESENT != STD_OFF)
            case TCPIP_UDP_CLOSED:
            {
                /* Get the index of dynamic config table from the given SocketId by using array */
                lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

                /* Condition check: dynamic socket index is valid */
                if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
                {
                    /* Get the static socket index from dynamic socket table */
                    lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
                    /* Get the static group socket index from static socket table */
                    lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo ;

                    if( 1U < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo )
                    {
                        SoAd_TcpIpUdpClosedForGroupSocket(SocketId);
                    }
                    else
#endif/*SOAD_UDP_GRP_PRESENT != STD_OFF*/
                    {
                        SoAd_TerminateActiveSession(lIdxDynSocket_uo);

                        /* set the global variables to skip the further transmission and reception */
                        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;

                        /* Reset the entry in SoAd_TcpIpSocHandleToDynSockIdx_auo[] */
                        SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId] = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

                        /* call for a function which shall close or reconnect the SoAd sockets */
                        SoAd_ChangeMode(lIdxStaticSocket_uo, lIdxDynSocket_uo);
                    }
                }

                break;
            }
#endif /* SOAD_UDP_PRESENT != STD_OFF */

            default:
            {
                /* Nothing to do */
                break;
            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */
}

#if (SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF)
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpIpTcpClosedForServerSocket()
 *
 * \Function description
 *  SoAd shall perform the action needs to be taken for the closer of Tcp server socket by Tcp module.
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TcpIpTcpClosedForServerSocket( VAR(TcpIp_SocketIdType, AUTOMATIC)    TcpIpSocketId_uo )
{
    /* Local pointer to store the Dynamic array */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Variable to store the Index of the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Variable to store the Index of the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxOtherActiveDynSocket_uo;

    /* Variable to store the Index of the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

    /* variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxSoConGroup_uo;

    VAR(TcpIp_SocketIdType, AUTOMATIC)                      lTcpIpListenSocketId_uo;

    /* variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lRetVal_u8;

    /* Variable to hold the other active sockets availability */
    VAR(boolean, AUTOMATIC)                                 lOtherActiveSocketPresent;

    /* Variable to store the Index of the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocketLoop_uo;

    /* Variable to hold the index in for loop, only used if TCP server */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxForLoop_uo ;

    /*Initialization of local variables */
    lIdxOtherActiveDynSocket_uo = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

    /* Note: If the SoAd_TcpIpEvent is called for a TCP established socket,
     * Reset the established socket Id in SoAd_TcpServerConfig_ast table,
     * and It shall be requested to go into RECONNECT.*/

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00646]: step(2) *******************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /*** Within SoAd_TcpIpEvent() with Event set to TCPIP_TCP_CLOSED or TCPIP_TCP_RESET, SoAd shall               ***/
    /*** (2)close the socket connection if it is in SOAD_SOCON_ONLINE (i.e. perform the specified closing actions ***/
    /*** with the exception of closing related TcpIp socket)                                                      ***/
    /****************************************************************************************************************/

    /*****************************************************************************
    * Check if the socket is Established socket: start
    ******************************************************************************/

    /* Get the index of dynamic config table from the given SocketId by using array */
    lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo];

    /* Get the static socket index from dynamic socket table */
    lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

    /* Get the static group socket index from static socket table */
    lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo ;

	/* get the listen socket id for the group */
    lTcpIpListenSocketId_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].groupTcpIpSocketId_puo);

	/* condition check: listen socket id is requseted to close, if socket id is not matching with group socket id, then close request is triggered for established socket id either from UL or LL. */
    if( lTcpIpListenSocketId_uo != TcpIpSocketId_uo )
    {
        /* Terminate the action sesstion if any */
        SoAd_TerminateActiveSession(lIdxDynSocket_uo);

        /* set the global variables to skip the further transmission and reception */
        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;

        /* Extract pointer to Dynamic structrue for given index */
        lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

        /**************************************************************************************
        * Check if it is the last socket in the group and close the Listen socket: Start
        **************************************************************************************/

        /* check if any other socket in the same group is being active,
         * if so please get the matched dynamic socket index of the active static socket */
        lOtherActiveSocketPresent = SoAd_GetOtherActiveDynSocketForGroup(lIdxStaticSocket_uo, &lIdxOtherActiveDynSocket_uo);

        /* check lOtherActiveSocketPresent is TRUE to confirm some other socket in the same group is active */
        if( TRUE == lOtherActiveSocketPresent )
        {
            /* Assume 2 sockets(soc1 and soc2) are opened successfully, now SoAd_TcpIpSocHandleToDynSockIdx_auo[listen]
             * array will pointing to soc2's dynamic index.
             * when we get the close request from UL for soc2(last opened socket) and if we reset the
             * SoAd_TcpIpSocHandleToDynSockIdx_auo[listen] array, then linking willbe destroyed, afterwards we can't use the
             * SoAd_TcpIpSocHandleToDynSockIdx_auo[listen] array for future access.
             *
             * So, whenever we are closing the socket which is pointed by SoAd_TcpIpSocHandleToDynSockIdx_auo[listen] array,
             * SoAd has to reassign the dynamic index which is still open/active.
             */
            SoAd_TcpIpSocHandleToDynSockIdx_auo[lTcpIpListenSocketId_uo] = lIdxOtherActiveDynSocket_uo;
        }
        else
        {
            /* call TcpIp to close the listen socket, Abort value for listen socket close is of no significance
             * here Abort value sent as last socket close request abort value retrieved from Dynamic table
             * Example: there are 4 sockets in the group and all are ONLINE, then if first 3 sockets are closed via
             * SoAd_CloseSoCon with ABORT TRUE, then all estd are closed but listen is still not asked for close beacuse
             * 4th socket is still ONLINE. Then SoAd_CloseSoCon called for 4th socket with ABORT FALSE, then Listen socket is
             * also closed after 4th socket's estd is closed. Listen socket close is called with FALSE, which is the request
             * given for the last socket in the group.SWS_SoAd_00642 (1.b) */
            lRetVal_u8 = TcpIp_Close( lTcpIpListenSocketId_uo,
                                      lSoAdDyncSocConfig_pst->statusAbort_b);

            /* check if, TcpIp close is E_OK */
            if( ( lRetVal_u8 == E_OK ) &&
                ( lSoAdDyncSocConfig_pst->socConSubMode_en != SOAD_SOCON_READYTOCLOSE ) )
            {
                /* goto a state where SoAd shall wait for SoAd_TcpIpEvent call back */
                lSoAdDyncSocConfig_pst->socConSubMode_en = SOAD_SOCON_WAITFORCLOSE ;
            }
        }

        /******************************************************************************
        * Check if it is the last socket in the group and close the Listen socket: End
        *******************************************************************************/

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00646]: step(1) *******************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /*** Within SoAd_TcpIpEvent() with Event set to TCPIP_TCP_CLOSED or TCPIP_TCP_RESET, SoAd shall               ***/
        /*** (1)remove the assignment of the TcpIp socket identified by SocketId from the related socket connection   ***/
        /****************************************************************************************************************/

        /* Reset the entry in SoAd_TcpIpSocHandleToDynSockIdx_auo[] */
        SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo] = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

        /* call for a function which shall close or reconnect the SoAd sockets */
        SoAd_ChangeMode(lIdxStaticSocket_uo, lIdxDynSocket_uo);
    }
    /*****************************************************************************
    * Check if the socket is Established socket: end
    ***************************************************************************** */

    /*****************************************************************************
    * Check if the socket is Listen socket: start
    ***************************************************************************** */
    else
    {
        /* fetch the start socket id from Group table and loop through for max socket couent */
        lIdxStaticSocketLoop_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].startSoConIdx_uo;

        for( lIdxForLoop_uo = 0; lIdxForLoop_uo < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo; lIdxForLoop_uo++ )
        {
            /* Get the index of the dynamic soc table */
            lIdxDynSocket_uo             = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocketLoop_uo].SoAd_Prv_idxDynSocTable_puo);

            /* check dynamic socket index and tcpip socket id are valid */
            if( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo ) && \
                ( SOAD_NUM_TCPIP_SOCKETS > SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo ) )
            {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00645] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** Within SoAd_TcpIpEvent() with Event set to TCPIP_TCP_CLOSED for a Listen-Socket, SoAd shall remove the   ***/
                /*** assignment of the TcpIp socket identified by SocketId from the related TCP socket connection group       ***/
                /****************************************************************************************************************/

                /* Reset the entry in SoAd_TcpIpSocHandleToDynSockIdx_auo[] */
                SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo] = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

                /* reset the listen socket id in group table if we got the close request for listen socket id */
                (*SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocketLoop_uo].soConGrpId_uo].groupTcpIpSocketId_puo) = SOAD_CFG_SOCKET_ID_DEFAULT_VALUE;

                /* Check for sockets which are connected with this listen socket and already established connections.
                 * Just reset the listen socket inside group,
                 * because SoAd_TcpIpEvent shall be called immediately for all established sockets related to this listen socket.
                 * Then perform the closing actions(SOAD_SOCON_RECONNECT) of all established sockets related to this listen.
                 *
                 * [SWS_SoAd_00646] Within SoAd_TcpIpEvent() with Event set to TCPIP_TCP_CLOSED,
                 * SoAd shall change the state of the socket connection related to the TCP socket to SOAD_SOCON_RECONNECT */

                if( SOAD_SOCON_ACTIVE != SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en )
                {
                    /* call for a function which shall close or reconnect the SoAd sockets */
                    SoAd_ChangeMode(lIdxStaticSocketLoop_uo, lIdxDynSocket_uo);
                }
            }

            ++lIdxStaticSocketLoop_uo;
        }
    }
    /*****************************************************************************
    * Check if the socket is Listen socket: end
    ***************************************************************************** */
}
#endif /* SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF */

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpIpUdpClosedForGroupSocket()
 *
 * \Function description
 *  SoAd shall perform the action needs to be taken for the closer of Udp Group socket by Tcp module.
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TcpIpUdpClosedForGroupSocket( VAR(TcpIp_SocketIdType, AUTOMATIC)    TcpIpSocketId_uo )
{
    /* Local pointer to store the Dynamic array */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdDyncSocConfig_pst ;

    /* variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                            lIdxSoConGroup_uo;

    /* Variable to store the Index of the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                            lIdxStaticSocketLoop_uo;

    /* Variable to store the Index of the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                            lIdxDynSocket_uo;

    /* Variable to Loop through all the configurations */
    VAR(uint16, AUTOMATIC)              lIdxForLoop_uo ;

    lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo];

    /* get the value of socket group Id*/
    lIdxSoConGroup_uo           = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo].soConGrpId_uo ;

    /* fetch the start socket id from Group table and loop through for max socket couent */
    lIdxStaticSocketLoop_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].startSoConIdx_uo;

    for( lIdxForLoop_uo = 0; lIdxForLoop_uo < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo; lIdxForLoop_uo++)
    {
        /* Get the index of the dynamic soc table */
        lIdxDynSocket_uo             = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocketLoop_uo].SoAd_Prv_idxDynSocTable_puo);

        /* check dynamic socket index and tcpip socket id are valid */
        if( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo ) && \
            ( SOAD_NUM_TCPIP_SOCKETS > SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo ) )
        {
            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00643]: step(1) *******************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /***            Within SoAd_TcpIpEvent() with Event set to TCPIP_UDP_CLOSED, SoAd shall                       ***/
            /***     remove the assignment of the TcpIp socket identified by SocketId from the related UDP socket         ***/
            /***                                            connection group                                              ***/
            /****************************************************************************************************************/

            /* reset the UDP Group socket id in group table if we got the close request for group */
            (*SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocketLoop_uo].soConGrpId_uo].groupTcpIpSocketId_puo) = SOAD_CFG_SOCKET_ID_DEFAULT_VALUE;

            /* Extract pointer to Dynamic structrue for given index */
            lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

            SoAd_TerminateActiveSession(lIdxDynSocket_uo);

            /* set the global variables to skip the further transmission and reception */
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;

            /* Reset the entry in SoAd_TcpIpSocHandleToDynSockIdx_auo[] */
            SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo] = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

            /* call for a function which shall close or reconnect the SoAd sockets */
            SoAd_ChangeMode(lIdxStaticSocketLoop_uo, lIdxDynSocket_uo);

            /* If socConSubMode_en is SOAD_SOCON_READYTOCLOSE means, socket close was triggered by UL, so no need of looping for next matched socket.
             * State change has been done in SoAd_ChangeMode function.
             * SoAd will call the TcpIp_Close only when close requests has been triggered for all the opened sockets by UL and
             * TcpIp_Close() function will be called only once for for last sockets, for remaining SoAd sockets, data structure will be resetted.
             *
             * So break the loop if close was triggered by UL, Otherwise loop through for all matched sockets and reset the data structure.
             *
             * During IP address unassignment, UDP will call the TcpIpEvent() callback function for all the matched sockets which has the same local IP address Id,
             * this is the only one possible scenario, UDP can call the TcpIpEvent() callback function before TcpIpclose() calls.
             */
            if( SOAD_SOCON_READYTOCLOSE == lSoAdDyncSocConfig_pst->socConSubMode_en )
            {
                break;
            }
        }

        /* increment the static socket id to move the next socket in the group */
        ++lIdxStaticSocketLoop_uo;
    }
}
#endif/*SOAD_UDP_GRP_PRESENT != STD_OFF*/

/**
 ***************************************************************************************************
 * \Function Name : SoAd_ChangeMode()
 *
 * \Function description
 * This service shall change the mode of the socket connection depending on the current state.
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - Index of static socket connection table.
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 ***************************************************************************************************
 */

static FUNC( void, SOAD_CODE ) SoAd_ChangeMode( VAR(SoAd_SoConIdType, AUTOMATIC)    StaticSocketId_uo, \
                                                VAR( SoAd_SoConIdType, AUTOMATIC )  DynSocketId_uo )
{

    /* If SoAd_TcpIpEvent is called because of internal decision taken by TcpIp layer,
     * but not because of UL or by SoAd, Then SoAd shall do all activities as per SWS_SoAd_00643/SWS_SoAd_00645 */
    if( ( SOAD_EVENT_OFFLINEREQ_UL != SoAd_DyncSocConfig_ast[DynSocketId_uo].socConRequestedMode_en ) && \
        ( ( 0U == SoAd_DyncSocConfig_ast[DynSocketId_uo].socConCloseReqCnt_u16 ) || \
          ( SoAd_DyncSocConfig_ast[DynSocketId_uo].socConCloseReqCnt_u16 < SoAd_DyncSocConfig_ast[DynSocketId_uo].socConOpenReqCnt_u16 ) ) )
    {
        /* call a function which resets the members of dynamic structure and dynamic index link from static structure */
        SoAd_ResetDynSockTblByEntry( StaticSocketId_uo, DynSocketId_uo, SOAD_SOCON_RECONNECT );

        /* call a function which shall invoke the upper layer call back for mode change after mode updated*/
        SoAd_ModeChgCallbackToUl( StaticSocketId_uo, DynSocketId_uo, SOAD_SOCON_RECONNECT );
    }
    else
    {
        /*If SoAd_TcpIpEvent is called because of either Upper layer or by SoAd,
         *  socket sub mode is set to SOAD_SOCON_READYTOCLOSE, action taken in next MainFunction */
        SoAd_DyncSocConfig_ast[DynSocketId_uo].socConSubMode_en = SOAD_SOCON_READYTOCLOSE;
    }

}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpIpEventDetChk()
 *
 * \Function description
 *  This function is called from SoAd_TcpIpEvent to handle the DET error for function arguments.
 * It covers SWS_SoAd_00276, SWS_SoAd_00277 & SWS_SoAd_00278 requirements
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource.
 * \param   TcpIp_EventType
 * \arg     Event_en - This parameter contains a description of the event just encountered
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TcpIpEventDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo, \
                                                      VAR( TcpIp_EventType,    AUTOMATIC )  Event_en)
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TCPIP_EVENT_API_ID, SOAD_E_NOTINIT )

    /* Check whether SocketId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SOAD_NUM_TCPIP_SOCKETS <= TcpIpSocketId_uo ), SOAD_TCPIP_EVENT_API_ID, SOAD_E_INV_SOCKETID )

    /* Check whether Event is valid or not */
    SOAD_DET_REPORT_ERROR( ( ( TCPIP_TCP_RESET > Event_en ) || ( TCPIP_UDP_CLOSED < Event_en ) ), SOAD_TCPIP_EVENT_API_ID, SOAD_E_INV_ARG )
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
