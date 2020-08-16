#ifndef LEMPowerEnergyMeter_H
#define LEMPowerEnergyMeter_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"


#include "EthComm.h"
#include "Platform_Types.h"
#include "string.h"
#include "stdlib.h"



/*LEM*/
#define  TCP_PAYLOAD_MAX_LENGTH					(1460u)
#define  ANALISIS_RX_CMD						(1u)
#define  LEMWH_REMOTE_PORT1						(10017)
#define  LEMWH_REMOTE_PORT2						(10027)
/*LEM*/






/*LEM*/
typedef enum
{
	LEMWHSniffer_Stop = 0u,
	LEMWHSniffer_Start
}LEMWH_arpsniffer;

typedef enum
{
	LEMWH_RET_OK 	 = 0,
	LEMWH_RET_N_OK = 1
}LEMWH_retvalue;


extern uint8 LEMWH_PtMainFunctionTx(void);
extern uint8 LEMWH_PtMainFunctionRx(void);
//extern Std_ReturnType  LEMWH_ArpSniffer(void);
//extern uint8 LEMWH_Transmit2Pt(TcpIp_PortType LEMWHLocalPort, TcpIp_SockAddrInetType pRemoteAddrPtr, uint8* pLEMWHTxDatabuf, uint16 LEMWHTxLength);
extern uint8 LEMWH_Receive2Pt(uint8* pLEMWHRxBuf, uint16* LEMWHRxLength);
extern void WH_LEMWH_TASK_100ms(void);
extern void WH_LEMWH_TASK_10ms(void);

/*LEM*/







#endif
