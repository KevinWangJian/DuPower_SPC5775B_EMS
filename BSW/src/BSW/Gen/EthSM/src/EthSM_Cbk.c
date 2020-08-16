
#include "EthSM.h"

#ifdef ETHSM_CONFIGURED
#include "EthSM_Cbk.h"
#include "EthSM_Prv.h"

#define ETHSM_START_SEC_CODE
#include "EthSM_MemMap.h"
/**
 ***************************************************************************************************
 * \module description
 * ETHSM0109: This service is called by the Ethernet Interface to report a transceiver link state change.
 * \par Service ID 0x06, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx : Index of the Ethernet controller within the context of the Ethernet Interface
 * \param TransceiverLinkState  : Actual transceiver link state of the specific network handle
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC( void, RBA_ETHSM_CODE ) EthSM_TrcvLinkStateChg(    VAR( uint8, AUTOMATIC )                 CtrlIdx,
                                                        VAR( EthTrcv_LinkStateType, AUTOMATIC ) TransceiverLinkState )
{
    /* Local variable declaration */
    VAR( uint8,                           AUTOMATIC )       lLoopIdx_u8;

    /* Report DET : Development Error: Module not initialized */
    ETHSM_REPORT_ERROR_RET_VOID( ( NULL_PTR == EthSM_EthChnlPtr_pco ),         \
							ETHSM_SID_ETHSM_TRCVLINKSTATECHG, ETHSM_E_UNINIT )

    /* Report DET : Development Error: Invalid Transceiver Link State */
    ETHSM_REPORT_ERROR_RET_VOID( ( ( TransceiverLinkState != ETHTRCV_LINK_STATE_ACTIVE ) &&              \
                          ( TransceiverLinkState != ETHTRCV_LINK_STATE_DOWN ) ),                  \
                            ETHSM_SID_ETHSM_TRCVLINKSTATECHG, ETHSM_E_INVALID_TRCV_LINK_STATE )

    /* Report DET if CrlIdx is invalid */
    ETHSM_REPORT_ERROR_RET_VOID( ( ETHSM_NUM_OF_ETHIFCTRL <= CtrlIdx ),            \
										   ETHSM_SID_ETHSM_TRCVLINKSTATECHG, ETHSM_E_PARAM_CONTROLLER )

    /* Store the TransceiverLinkState */
	EthSM_TrcvLinkState_aen[CtrlIdx] = TransceiverLinkState;

    /* If one of the network user is CDD, then inform about link state change */
    if(( EthSM_EthChnlPtr_pco[CtrlIdx].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_CDD ) ||
       ( EthSM_EthChnlPtr_pco[CtrlIdx].NumOfNetworkUsers_u8 > 1U ))
    {
        /* Loop through all network users for the EthSM network */
        for( lLoopIdx_u8 = 0; lLoopIdx_u8 < ( EthSM_EthChnlPtr_pco[CtrlIdx].NumOfNetworkUsers_u8 ); lLoopIdx_u8++ )
        {
            if( EthSM_EthChnlPtr_pco[CtrlIdx].NetworkUserConfig_pcst[lLoopIdx_u8].UserTrcvLinkStateChgFunc != NULL_PTR )
            {
                /* Call configured User_TrcvlinkStateChg API  */
                EthSM_EthChnlPtr_pco[CtrlIdx].NetworkUserConfig_pcst[lLoopIdx_u8].UserTrcvLinkStateChgFunc( CtrlIdx,
                                                                                                            TransceiverLinkState );
            }
        }
    }

    /* Check whether the DEM error is configured for the network. DemEventId 0 indicates no DEM error is configured */
	if( 0 != EthSM_EthChnlPtr_pco[CtrlIdx].DemEventId_u16)
	{
		if( (ETHTRCV_LINK_STATE_ACTIVE == TransceiverLinkState) &&
			(ETHSM_STATE_ONHOLD == EthSM_NetState_aen[CtrlIdx]) )
		{
			Dem_ReportErrorStatus( EthSM_EthChnlPtr_pco[CtrlIdx].DemEventId_u16,
								   DEM_EVENT_STATUS_PASSED);
		}
		else if( (ETHTRCV_LINK_STATE_DOWN == TransceiverLinkState) &&
			     (ETHSM_STATE_ONLINE == EthSM_NetState_aen[CtrlIdx]) )
		{
			Dem_ReportErrorStatus( EthSM_EthChnlPtr_pco[CtrlIdx].DemEventId_u16,
					               DEM_EVENT_STATUS_FAILED);
		}
		else
		{/* Do nothing */
		}
	}
}


/**
 ***************************************************************************************************
 * \module description
 * ETHSM0110: This service is called by the TcpIp to report the actual TcpIp state (e.g. online, offline).
 * \par Service ID 0x08, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       : EthIf controller index to identify the communication network where the TcpIp state is changed
 * \param TcpIpState    : Actual TcpIp state of the specific network handle
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  Std_ReturnType {E_OK: Service accepted; E_NOT_OK: Service denied}
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, RBA_ETHSM_CODE ) EthSM_TcpIpModeIndication (  VAR( uint8, AUTOMATIC )             CtrlIdx,
                                                                    VAR( TcpIp_StateType, AUTOMATIC )   TcpIpState )
{
    /* Report DET : Development Error: Module not initialized */
    ETHSM_REPORT_ERROR_RET_VALUE( ( NULL_PTR == EthSM_EthChnlPtr_pco ),     \
                                    ETHSM_SID_ETHSM_TCPIPMODEINDICATION, ETHSM_E_UNINIT, E_NOT_OK )

    /* Report DET : Development Error: Invalid TcpIpCtrl State */
    ETHSM_REPORT_ERROR_RET_VALUE( ( ( TcpIpState != TCPIP_STATE_ONLINE ) &&           \
                                    ( TcpIpState != TCPIP_STATE_ONHOLD )  &&          \
                                    ( TcpIpState != TCPIP_STATE_OFFLINE )  &&         \
                                    ( TcpIpState != TCPIP_STATE_STARTUP )  &&         \
                                    ( TcpIpState != TCPIP_STATE_SHUTDOWN ) ),         \
                                 ETHSM_SID_ETHSM_TCPIPMODEINDICATION, ETHSM_E_INVALID_TCPIP_MODE, E_NOT_OK )

    /* Report DET if CtrlIdx  is invalid */
    ETHSM_REPORT_ERROR_RET_VALUE( ( ETHSM_NUM_OF_ETHIFCTRL <= CtrlIdx ),           \
                                    ETHSM_SID_ETHSM_TCPIPMODEINDICATION, ETHSM_E_PARAM_CONTROLLER, E_NOT_OK )

	 /* Report DET : If EthSM receives EthSM_TcpIpModeIndication(TCPIP_STATE_ONLINE) without requesting TcpIp ( without calling TcpIp_RequestComMode(TCPIP_STATE_ONLINE) )*/
	 ETHSM_REPORT_ERROR_RET_VALUE( ( (ETHSM_STATE_WAIT_ONLINE != EthSM_NetState_aen[CtrlIdx]) &&   \
			                         (ETHSM_STATE_ONHOLD != EthSM_NetState_aen[CtrlIdx]) &&        \
			                         (ETHSM_STATE_ONLINE != EthSM_NetState_aen[CtrlIdx]) &&        \
			                         (TCPIP_STATE_ONLINE == TcpIpState) ),                            \
								      ETHSM_SID_ETHSM_TCPIPMODEINDICATION, ETHSM_E_INVALID_TCPIP_MODE, E_NOT_OK )

	 /* Report DET : If EthSM receives EthSM_TcpIpModeIndication(TCPIP_STATE_ONHOLD) and EthSM state is not in ETHSM_STATE_ONHOLD */
	 ETHSM_REPORT_ERROR_RET_VALUE( ( (ETHSM_STATE_ONHOLD != EthSM_NetState_aen[CtrlIdx]) &&        \
									 (TCPIP_STATE_ONHOLD == TcpIpState) ),                            \
									  ETHSM_SID_ETHSM_TCPIPMODEINDICATION, ETHSM_E_INVALID_TCPIP_MODE, E_NOT_OK )

    /* Store the TcpIpState state */
	EthSM_TcpIpState_aen[CtrlIdx] = TcpIpState;


    return E_OK ;
}

/**
 ***************************************************************************************************
 * \module description
 * Called when mode has been read out. Triggered by previous EthIf_SetControllerMode call.
 * Can directly be called within the trigger functions.
 * \par Service ID 0x0a, Synchronous, Reentrant (only for different Ethernet controllers)
 *
 * Parameter In:
 * \param CtrlIdx       : Index of the Ethernet controller within the context of the Ethernet Interface
 * \param CtrlMode      : Notified Ethernet Controller mode
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC( void, RBA_ETHSM_CODE ) EthSM_CtrlModeIndication(  VAR( uint8, AUTOMATIC )             CtrlIdx,
                                                        VAR( Eth_ModeType, AUTOMATIC )      CtrlMode  )
{
    /* Report DET : Development Error: Module not initialized */
    ETHSM_REPORT_ERROR_RET_VOID( ( NULL_PTR == EthSM_EthChnlPtr_pco ),     \
                                   ETHSM_SID_ETHSM_CTRLMODEINDICATION, ETHSM_E_UNINIT )

    /* Report DET if CrlIdx is invalid */
    ETHSM_REPORT_ERROR_RET_VOID( ( ETHSM_NUM_OF_ETHIFCTRL <= CtrlIdx ),           \
                                   ETHSM_SID_ETHSM_CTRLMODEINDICATION, ETHSM_E_PARAM_CONTROLLER )

    /* Store the indicated EthIfCtrl mode and process it in the next main function */
    EthSM_EthIfCtrlMode_aen[CtrlIdx] = CtrlMode;

    if( CtrlMode == ETH_MODE_DOWN )
    {
        /* EthSM_CtrlModeIndication(ETH_MODE_DOWN) is expected only at ETHSM_STATE_OFFLINE. */
        /* At any other EthSM state it means error in the hardware and EthSM network shall be brought back to ETHSM_STATE_OFFLINE */
        if( ETHSM_STATE_OFFLINE != EthSM_NetState_aen[CtrlIdx] )
        {
            /* Set error flag for the EthSM network */
            EthSM_HwError_ab[CtrlIdx] = TRUE;
        }
    }
}

#define ETHSM_STOP_SEC_CODE
#include "EthSM_MemMap.h"

#endif /* ETHSM_CONFIGURED */

