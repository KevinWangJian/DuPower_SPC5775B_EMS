

#ifndef TCPIP_ETHSM_H_
#define TCPIP_ETHSM_H_

#include "TcpIp_Cfg.h"		/* Required for TCPIP_CONFIGURED */
#ifdef TCPIP_CONFIGURED

#include "TcpIp_GeneralTypes.h"

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestComMode(
											        VAR( uint8, AUTOMATIC ) 					CtrlIdx,
											        VAR( TcpIp_StateType, AUTOMATIC ) 			State );

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */
#endif /* TCPIP_ETHSM_H_ */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
