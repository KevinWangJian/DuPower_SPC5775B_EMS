

#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "EthIf_Cbk.h"
#include "EthSM_Cbk.h"
#include "EthIf_Prv.h"
#include "EthTrcv.h"

 /**
 ***************************************************************************************************
 * \module description
 * ETHIF085: Handles a received frame received by the indexed controller
 * \par Service ID 0x10, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 * \param FrameType     Frame type of received Ethernet frame
 * \param IsBroadcast   parameter to indicate a broadcast frame
 * \param PhysAddrPtr   Pointer to Physical source address (MAC address in network byte order) of received Ethernet frame
 * \param DataPtr       Payload of the received frame
 * \param LenByte       Length of the received frame bytes
 *
 * \return  None
 *
 ***************************************************************************************************
 */
#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: P2VAR is defined in AUTOSAR for PhysAddrPtr */
FUNC(void, RBA_ETHIF_CODE) EthIf_RxIndication(  VAR( uint8,             AUTOMATIC )               CtrlIdx,
                                                VAR( Eth_FrameType,     AUTOMATIC )               FrameType,
                                                VAR( boolean,           AUTOMATIC )               IsBroadcast,
                                                P2VAR( uint8,           AUTOMATIC, AUTOMATIC )    PhysAddrPtr,
                                                P2VAR( Eth_DataType,    AUTOMATIC, AUTOMATIC )    DataPtr,
                                                VAR( uint16,            AUTOMATIC )               LenByte )
{
    /* Local variable declaration */
    uint8*      lBuf_pu8;
    uint16      lEthType_u16;
    uint16      lVlanId_u16;
    uint8       lEthIfCtrlNr_u8;
    uint8       lEthIfFrameOwner_u8;
    uint16      lLenByte_u16;

    /* Local variable initialization */
    lEthType_u16                    = 0;
    lVlanId_u16                     = 0xFFFF;
    lBuf_pu8                        = (uint8 *) DataPtr;
    lEthIfCtrlNr_u8                 = 0;
    lEthIfFrameOwner_u8             = 0;
    lLenByte_u16                    = LenByte;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en!=ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_CBK_RXINDICATION, ETHIF_E_NOT_INITIALIZED )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VOID( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthCtrl_cu8 ),      \
                                     ETHIF_SID_ETHIF_CBK_RXINDICATION,                                             \
                                     ETHIF_E_INV_CTRL_IDX)

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID( ( ( NULL_PTR == DataPtr ) || ( NULL_PTR == PhysAddrPtr ) ), ETHIF_SID_ETHIF_CBK_RXINDICATION, ETHIF_E_PARAM_POINTER )

    /* Check Ethernet type to check is Frame is of VLAN Type */
    if( ETHIF_FRAMETYP_VLAN == FrameType )
    {
        /* Extract VLANid */
        lVlanId_u16     = ( ( (uint16)(lBuf_pu8[ETHIF_VLANTAG_BYTE1] & 0x0FU) ) << 8U );
        lVlanId_u16     |=  ( lBuf_pu8[ETHIF_VLANTAG_BYTE2] );

        /* Extract EthernetType */
        lEthType_u16    = ( ( (uint16)(lBuf_pu8[ETHIF_ETHTYPE_IN_VLAN_BYTE1]) ) << 8U );
        lEthType_u16    |= ( lBuf_pu8[ETHIF_ETHTYPE_IN_VLAN_BYTE2] );

        /* Increment the buffer pointer by 4, so that buffer pointer points to IP header */
        lBuf_pu8     += ETHIF_VLANTAG_LENGTH;
        lLenByte_u16 -= ETHIF_VLANTAG_LENGTH;
    }
    else
    {
        lVlanId_u16  = 0xffff;
        lEthType_u16 = FrameType;
    }

    /* Identify EthIfCtrl */
    for( lEthIfCtrlNr_u8 = 0; lEthIfCtrlNr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ; lEthIfCtrlNr_u8++ )
    {
        if ( ( lVlanId_u16 == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlNr_u8].VlanId_cu16 ) ) &&
             ( CtrlIdx     == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlNr_u8].idxEthCtrRef_cu8 ) ) )
        {
            break;
        }
    }

    /* If EthType is a AVB pass whole DataPtr */
    if( ETHIF_FRAMETYP_AVB == lEthType_u16 )
    {
        if( 0xffffU == lVlanId_u16)
        {
            lBuf_pu8     -= ETHIF_OFFSET_PAYLOAD_NOVLAN;
            lLenByte_u16 += ETHIF_OFFSET_PAYLOAD_NOVLAN;
        }
        else
        {
            lBuf_pu8     -= ETHIF_OFFSET_PAYLOAD_VLAN;
            lLenByte_u16 += ETHIF_OFFSET_PAYLOAD_VLAN;
        }
    }

    /* Identify upper layer Rx indication to be called based on frame type field in the received frame */
    for( lEthIfFrameOwner_u8 = 0; lEthIfFrameOwner_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfFrameOwners_cu8 ); lEthIfFrameOwner_u8++ )
    {
        if( ( ( EthIf_CfgPtr_pco->EthIfFrameOwnerConfig_pst[lEthIfFrameOwner_u8].FrameType_tcu16 ) == lEthType_u16 ) &&
            ( lEthIfCtrlNr_u8 != EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) &&                            /* Check whether EthIfCtrl is valid                                      */
            ( ETH_MODE_DOWN != EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lEthIfCtrlNr_u8] )  )              /* Check whether EthIfCtrl is ETH_MODE_ACTIVE                            */
        {
                EthIf_CfgPtr_pco->EthIfFrameOwnerConfig_pst[ lEthIfFrameOwner_u8 ].EthIfRxIndication(
                                                                    lEthIfCtrlNr_u8,    /* EthIf controller on which the frame is received   */
                                                                    lEthType_u16,       /* Type of the Eth frame received                    */
                                                                    IsBroadcast,        /* Indicates whether the received frame is broadcast */
                                                                    PhysAddrPtr,        /* Offset to MAC address of the sending node         */
                                                                    lBuf_pu8,           /* Upper layer payload start from here               */
                                                                    lLenByte_u16 );     /* Length of upper layer payload                     */

            break;
        }
    }
}

/**
 ***************************************************************************************************
 * \module description
 * ETHIF091: Confirms frame transmission by the indexed controller
 * \par Service ID 0x11, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 * \param BufIdx        Index of the transmitted buffer
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC(void, RBA_ETHIF_CODE) EthIf_TxConfirmation(    VAR( uint8,             AUTOMATIC )             CtrlIdx,
                                                    VAR( uint8,             AUTOMATIC )             BufIdx)
{
    /* Local variable declaration */
    uint8   lEthIfCtrlNr_u8;
    uint8   lEthIfFrameOwner_u8;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_CBK_TXCONFIRMATION, ETHIF_E_NOT_INITIALIZED )

        /* Mapping VLANid to CtrlIdx. If VLAN is not configured Physical Ctrl Idx is mapped to EthIf CtrlIdx */
    for( lEthIfCtrlNr_u8 = 0; lEthIfCtrlNr_u8  < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ); lEthIfCtrlNr_u8++ )
    {
		if ( CtrlIdx   == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlNr_u8].idxEthCtrRef_cu8 ) ) 
        {
            break;
        }
     }

    /* For the transmitted Ethernet frame, check to which upper layer protocol Tx confirmation shall be given */
    /* Based on the transmitted frame's EthType, loop through the configuration to check the owner of this frame */
    for( lEthIfFrameOwner_u8 = 0; lEthIfFrameOwner_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfFrameOwners_cu8 ); lEthIfFrameOwner_u8++ )
    {
        if( ( lEthIfCtrlNr_u8 != EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) &&
            ( NULL_PTR !=  EthIf_CfgPtr_pco->EthIfFrameOwnerConfig_pst[lEthIfFrameOwner_u8].EthIfTxConfirmation ) )
        {
            /* Call configured TxConfirmationFunction */
            EthIf_CfgPtr_pco->EthIfFrameOwnerConfig_pst[lEthIfFrameOwner_u8].EthIfTxConfirmation( lEthIfCtrlNr_u8,
                                                                                                  BufIdx );
            break;
        }
    }
}

/**
 ***************************************************************************************************
 * \module description
 * ETHIF231: Called asynchronously when mode has been read out. Triggered by previous
 * Eth_SetControllerMode call. Can directly be called within the trigger functions.
 * \par Service ID 0x0E, Non Reentrant for the same CtrlIdx, reentrant for different
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 * \param CtrlMode        Notified Ethernet controller mode
 *
 * \return  None
 *
 ***************************************************************************************************
 */
void EthIf_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType CtrlMode)
{
    /* This function is not supported*/
}

/**
 ***************************************************************************************************
 * \module description
 * Called asynchronously when mode has been read out. Triggered by previous Eth_SetTransceiverMode call.
 * Can directly be called within the trigger functions.
 * \par Service ID 0x0f, Synchronous, Non Reentrant for the same CtrlIdx, reentrant for different
 *
 * Parameter In:
 * \param TrcvIdx       Index of the Ethernet transceiver within the context of the Ethernet Interface.
 * \param TrcvMode      Notified Ethernet transceiver mode
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC(void, RBA_ETHIF_CODE) EthIf_TrcvModeIndication (  VAR( uint8,             AUTOMATIC )       TrcvIdx,
                                                       VAR( EthTrcv_ModeType,  AUTOMATIC )       TrcvMode )
{
#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )

    uint8                         lEthIfCtrlIdx_u8;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_TRCVMODEINDICATION, ETHIF_E_NOT_INITIALIZED )

    /* Report DET : Development Error: TrcvIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VOID( ( ( TrcvIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfTrcv_cu8),          \
                                     ETHIF_SID_ETHIF_TRCVMODEINDICATION,                                           \
                                     ETHIF_E_INV_TRCV_IDX )

#if (ETHIF_DEV_ERROR_DETECT  == STD_ON)
        /* Report DET : If EthIf has not requested EthTrcv for ACTIVE state and EthTrcv is giving call back EthIf_TrcvModeIndication(ETHTRCV_MODE_ACTIVE) */
        for( lEthIfCtrlIdx_u8 = 0;
            (( lEthIfCtrlIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 )) && (ETHTRCV_MODE_ACTIVE == TrcvMode) );
            lEthIfCtrlIdx_u8++ )
        {
            /* If EthTrcv indicates mode ACTIVE check atleast one of EthIfCtrl mapped to EthTrcv is in state ETHIF_TRCV_STATE_WAIT_TRCV_ACTIVE */
            if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvIdx_cu8 == TrcvIdx ) &&
               ( ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE == EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ))
            {
                break;
            }
        }

        ETHIF_REPORT_ERROR_RET_VOID( (lEthIfCtrlIdx_u8 == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 )),          \
                                   ETHIF_SID_ETHIF_TRCVMODEINDICATION,                                                           \
                                   ETHIF_E_INV_PARAM )
#endif

    if( ETHTRCV_MODE_DOWN == TrcvMode )
    {
        for( lEthIfCtrlIdx_u8 = 0;
           ( lEthIfCtrlIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ));
             lEthIfCtrlIdx_u8++ )
        {
            /* If EthTrcv indicates mode DOWN check atleast one of EthIfTrcv mapped to EthTrcv is in state ETHIF_TRCV_STATE_WAIT_TRCV_ACTIVE/ETHIF_ETHIFCTRL_STATE_ACTIVE */
            if (( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvIdx_cu8 == TrcvIdx ) &&
                (( ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE == EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) ||
                ( ETHIF_ETHIFCTRL_STATE_ACTIVE == EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en )))
            {
                /*If yes, set the transceiver error flag to true for the corresponding EthIfCtrlIdx */
                EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[lEthIfCtrlIdx_u8] = TRUE;

            }
        }
    }

   	/* Store the transceiver mode indicated. The mode will be processed in the next main function */
   	EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[TrcvIdx] = TrcvMode;

#else /* ( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON ) */
   	(void)TrcvIdx;
   	(void)TrcvMode;
#endif
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
