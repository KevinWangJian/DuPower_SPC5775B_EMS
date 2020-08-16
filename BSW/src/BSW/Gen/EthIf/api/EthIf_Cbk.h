


#ifndef ETHIF_CBK_H
#define ETHIF_CBK_H

#include "EthIf_Types.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
/* ETHIF085: Handles a received frame received by the indexed controller */
FUNC(void, RBA_ETHIF_CODE) EthIf_RxIndication(  VAR( uint8,             AUTOMATIC )               CtrlIdx,
                                                VAR( Eth_FrameType,     AUTOMATIC )               FrameType,
                                                VAR( boolean,           AUTOMATIC )               IsBroadcast,
                                                P2VAR( uint8,           AUTOMATIC, AUTOMATIC )    PhysAddrPtr,
                                                P2VAR( Eth_DataType,    AUTOMATIC, AUTOMATIC )    DataPtr,
                                                VAR( uint16,            AUTOMATIC )               LenByte );

/* ETHIF091: Confirms frame transmission by the indexed controller */
FUNC(void, RBA_ETHIF_CODE) EthIf_TxConfirmation(	VAR( uint8,				AUTOMATIC )				CtrlIdx,
		                                            VAR( uint8,				AUTOMATIC )				BufIdx);

/* ETHIF231: Called asynchronously when mode has been read out. Triggered by previous Eth_SetControllerMode call. 
   Can directly be called within the trigger functions. */
FUNC(void, RBA_ETHIF_CODE) EthIf_CtrlModeIndication(   VAR( uint8,             AUTOMATIC )       CtrlIdx,
                                                       VAR( Eth_ModeType,    AUTOMATIC )     CtrlMode);
 
FUNC(void, RBA_ETHIF_CODE) EthIf_TrcvModeIndication(   VAR( uint8,             AUTOMATIC )       TrcvIdx,
		                                               VAR( EthTrcv_ModeType,    AUTOMATIC )     TrcvMode );

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif /* ETHIF_CBK_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
