/*
 * Zvt_AswCom.h
 *
 *  Created on: 2020Äê3ÔÂ5ÈÕ
 *      Author: admin
 */

#ifndef CDD_ETHCOMM_ZVT_ASWCOM_H_
#define CDD_ETHCOMM_ZVT_ASWCOM_H_

#include "Zvt_Types.h"
#include "Rte_Asw_Swc.h"


#define TCP_CONNECT_TIMES        12u



extern zvt_pt_ipmode Zvt_PtGetIPMode(void);
extern uint16 Zvt_PtReadReceipt(uint16 cmd);
extern uint8 Zvt_PtReadErrID(uint16 cmd);


extern uint8 Asw_ZvtDispatch0622PreAuthRequest(void);
extern uint8 Asw_ZvtDispatchUserStopRequest(void);
extern uint8 Asw_ZvtDispatch0623ReversalRequest(void);
extern uint8 Asw_ZvtDispatch06C0MifareRequest(void);

extern uint8 Zvt_MoneyFloat32Convert2Uint8Bcd(const float32* InputData, uint8* OutputData);

extern void Zvt_100msTask(void);
extern void Zvt_AswCom_WriteRte(void);
extern void Zvt_AswCom_ReadAsw(void);

#endif /* CDD_ETHCOMM_ZVT_ASWCOM_H_ */
