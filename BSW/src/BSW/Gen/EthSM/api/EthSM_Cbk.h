

#ifndef ETHSM_CBK_H_
#define ETHSM_CBK_H_

#include "EthSM_Cfg.h"
#ifdef ETHSM_CONFIGURED

#include "TcpIp_Types.h"
#include "EthTrcv_GeneralTypes.h"

#define ETHSM_START_SEC_CODE
#include "EthSM_MemMap.h"

extern FUNC( void, RBA_ETHSM_CODE ) EthSM_CtrlModeIndication(	VAR( uint8, AUTOMATIC )             CtrlIdx,
                                                                VAR( Eth_ModeType, AUTOMATIC )      CtrlMode  );

extern FUNC(void, RBA_ETHSM_CODE) EthSM_TrcvLinkStateChg (VAR(uint8, AUTOMATIC) CtrlIdx,
		                                           VAR(EthTrcv_LinkStateType, AUTOMATIC) TransceiverLinkState);

extern FUNC(Std_ReturnType, RBA_ETHSM_CODE) EthSM_TcpIpModeIndication (VAR(uint8, AUTOMATIC) CtrlIdx,
		                                                        VAR(TcpIp_StateType, AUTOMATIC) TcpIpState);

#define ETHSM_STOP_SEC_CODE
#include "EthSM_MemMap.h"

#endif /* ETHSM_CONFIGURED */

#endif /* ETHSM_CBK_H_ */
