/*
 * Zvt_Driver.h
 *
 *  Created on: 2019年12月30日
 *      Author: admin
 */

#ifndef CDD_ETHCOMM_ZVT_DRIVER_H_
#define CDD_ETHCOMM_ZVT_DRIVER_H_

#include "EthComm.h"
#include "Zvt_Types.h"
#include "Platform_Types.h"
#include "string.h"
#include "stdlib.h"

#define  ZVT_NULL								(void* 0u)

#define COM_ZVT_TEST_CONST       0xC0C0C0C0  //开关值

#define  ZVT_EXT_FORMAT_FLAG   					(0xff)
#define  ZVT_RX_STD_DATA_MAX_LENGH				(1460u)
#define  ZVT_RX_EXT_DATA_MAX_LENGH				(1460u)
#define  ZVT_REMOTE_PORT						(10007u)
#define  ZVT_LOCAL_PORT							(20008u)
#define  ZVT_LANGUAGE_BUFF_LENGTH				(4U)

#define  ZVT_SOCKET_ID							(0u)
#define  ZVT_HEAD_LEN_STD						(3u)
#define  ZVT_HEAD_LEN_EXT						(5u)


#define  TCP_PAYLOAD_MAX_LENGTH					(1460u)
#define  ZVT_CTRL_FIELD_LEN						(2u)
#define  ANALISIS_RX_CMD						(1u)

#define CMDTAG_POLL_MAX_TIMES					(20u)
#define CMD040F_POLL_MAX_TIMES					(20u)
#define CMD04FF_POLL_MAX_TIMES					(20u)
#define CMD060F_POLL_MAX_TIMES					(20u)

#define LLVAR_HEAD_LEN							(3U)
#define LLLVAR_HEAD_LEN							(4U)

#define Bitmap27_ResultCode_EXT_POS				(5u)
#define Bitmap29_TID_EXT_POS					(7u)
#define Bitmap04_AmounMinorCurrencyUnits_EXT_POS		(12u)
#define Bitmap0B_TraceNumber_EXT_POS			(19u)
#define Bitmap87_ReceiptNumber_EXT_POS			(51u)

#define Bitmap27_ResultCode_STD_POS				(3u)
#define Bitmap29_TID_STD_POS					(5u)
#define Bitmap04_AmounMinorCurrencyUnits_STD_POS		(12u)
#define Bitmap0B_TraceNumber_STD_POS			(19u)
#define Bitmap87_ReceiptNumber_STD_POS			(51u)

#define CTRL_IDX	(0u)
#define ARP_LENGTH_FRAME		42u
#define LENGTH_PAYLOAD		28u
#define OFFSET_PAYLOAD		14u
#define OFFSET_FRAMETYPE	12u
#define TXCOMFIRMATION_OFF	0u
#define TXCOMFIRMATION_ON	1u

extern zvt_debugflag_t debugFlagList;


extern zvt_apdu_err_id Zvt_Uint32DivedTo4Uint8Bcd(uint32* u32_data, uint8* u8_data);

extern uint8 Zvt_ReadCard(void);
extern uint8 Zvt_ReadRfidUID(void);
extern uint8 Zvt_PtCheckReceive8000Ack(void);

extern uint8 Zvt_Pt142IpStatusEnquiry0501(void);
extern uint8 Zvt_PtUserIpStatusEnquiry0501(void);
extern uint8 Zvt_PtFactoryRegistration0600(void);
extern uint8 Zvt_PtUserRegistration0600(void);
extern uint8 Zvt_PtPreAuthorized0622(uint32* PreAuthorizedMoney);
extern uint8 Zvt_PtPreAuthorized0622SID(uint8* PreAuthorizedMoney);
extern uint8 Zvt_PtReturnRemainingAmount0623(uint8*Receiptnumber, uint8* RemainingMoney);
extern uint8 Zvt_PtEmvConfigurationDiagnosis0670_4(void);
extern uint8 Zvt_PtInitilisation0693(void);
extern uint8 Zvt_PtAbort06B0(void);
extern uint8 Zvt_PtReadCard06C0UID(void);
extern uint8 Zvt_PtReadCard06C0SID(void);
extern uint8 Zvt_PtFactoryConfiguration0813(uint8* Tid_Ascii_8B,uint8* Ip_Ascii_15B, uint8* Netmask_Ascii_15B,uint8* Gateway_Ascii_15B);
extern uint8 Zvt_PtUserConfiguration0813(uint8* Tid_Ascii_8B,uint8* Ip_Ascii_15B, uint8* Netmask_Ascii_15B,uint8* Gateway_Ascii_15B);
extern uint8 Zvt_PtTxPositiveAck8000(void);
extern uint8 Zvt_PtTxFactoryPositiveAck8000(void);
extern uint8 Zvt_PtTxPositiveAck8400(void);

extern void Switch_FuncStateFlag_100ms(void);

extern uint8 Zvt_Transmit2Pt(TcpIp_PortType zvtLocalPort, uint8* pZvtTxDatabuf, uint16 zvtTxLength);
extern uint8 Zvt_Receive2Pt(uint8* pZvtRxBuf, uint16* zvtRxLength);
extern uint8 Zvt_Transmit2Pt1_42(TcpIp_PortType zvtLocalPort, uint8* pZvtTxDatabuf, uint16 zvtTxLength);
extern uint8 Zvt_PtMainFunctionTx(void);
extern uint8 Zvt_PtSortReceivedCommand(void);
extern void Zvt_10msTask(void);
extern void StateTask(void);



extern Std_ReturnType  Zvt_ArpSniffer(void);



#endif /* CDD_ETHCOMM_ZVT_DRIVER_H_ */
