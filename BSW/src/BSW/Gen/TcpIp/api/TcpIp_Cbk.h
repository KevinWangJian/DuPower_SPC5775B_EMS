

#ifndef TCPIP_CBK_H
#define TCPIP_CBK_H

#include "TcpIp_Cfg.h"		/* Required for TCPIP_CONFIGURED */
#ifdef TCPIP_CONFIGURED

#include "Eth_GeneralTypes.h"            /* Required for Eth_FrameType */

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
extern FUNC( void, TCPIP_CODE )	TcpIp_RxIndication(	VAR( uint8, AUTOMATIC ) 	CtrlIdx,
									VAR( Eth_FrameType, AUTOMATIC ) 			FrameType,
									VAR( boolean, AUTOMATIC )                   IsBroadcast,
									P2VAR( uint8, AUTOMATIC, AUTOMATIC )		PhysAddrPtr,
									P2VAR( uint8, AUTOMATIC, AUTOMATIC )		DataPtr,
									VAR( uint16, AUTOMATIC ) 					LenByte );
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_CBK_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
