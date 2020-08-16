




 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: Com / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#ifndef COM_CBK_H
#define COM_CBK_H

#define COMCallback(CALLBACKROUTINENAME) FUNC(void,COM_CODE)(CALLBACKROUTINENAME)(void)

/************* Com Notification in Tx side ************************/


/* Start: ComNotification for Signals */


#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS2_relayNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS2_relayPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS1_relayNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS1_relayPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CrossrelayPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC2_CrossrelayNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC2_CrossrelayPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC1_CrossrelayNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CrossrelayNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC1_CrossrelayPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS2_relayNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS2_relayPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS1_relayNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TMS_PS1_relayPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CrossrelayPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC2_CrossrelayNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC2_CrossrelayPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC1_CrossrelayNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CrossrelayNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC1_CrossrelayPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/* End: ComNotification for Signals */


/* Start: ComNotification for Signals Groups */


/* End: ComNotification for Signals Groups */

/* Start : IPDU notification for TX IPDUs */


/* End : IPDU notification for TX IPDUs */

/******************************************************************/


/************* Com Notification in Rx side ************************/


/* Start: ComNotification for Signals */


#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh2_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOLTester_SetConfirm_Type_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCV_SetID6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LEM_SetADD6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACWh1_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC_PowerSetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC1_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ACDC2_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh1_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCWh2_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PowerSetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PowerNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PowerSetAdd_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_Number(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_SetSN1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_SetSN2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_SetSN3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPACDC_SetSN4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_Number(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_SetSN1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_SetSN2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_SetSN3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LPDCDC_SetSN4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData0(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EOLTesterData5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaskData(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CRCdata(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOL_Poject_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_Tester_Serial(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_LED_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AD_Speaker_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AD_FAN_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CoolingFAN_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_WIFI_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOL_ACDC_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOL_DCDC_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOL_ISOFaultdete_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AFC_EOL_HCUTest_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxClVlt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxCellVoltNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMaxCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinClVlt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinCellVoltNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMinCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack1_RechrNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack1_RechrPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCHighByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCLowByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCFailureTypeByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MesCellVoltNumIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes1CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes1CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes2CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes2CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes3CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes3CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MesCellTempNumIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes5_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes6_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_Fault_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVIsoWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVILWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCLowWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TempDiffWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TempHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackOvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackUvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellOvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellUvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCFastChgWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PwrBatPackMismatchWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCelConsistencyWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSVolHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackOCWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK1_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK2_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK3_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK4_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RestEnergy_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_Fault_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP5Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP4Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP3Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP2Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PreChrgHVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinBatWaterTmpIn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxBatWaterTmpOut_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_HVCurr_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackVoltVld_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackCurrentVld_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackCurrent_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_HVCurr_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_PosVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_NegVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_PosRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_NegRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CurRechgEnergyStorSysIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCodeLength_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCodeIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSSwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSHwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SOP_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBatSOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBCP_LngTrmChrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBDP_LngTrmDischrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SOP_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_number_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_number_index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_Current_Status_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_SerialNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Year_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Month_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Day_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_PeakSOP_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBCP_ShrtTrmChrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBDP_ShrtTrmDischrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_PeakSOP_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellQuantity_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RealSOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSTempProbeQuantity_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVIsoValue_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOH_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TotalBatteryCap_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SysStat_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatMagCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVSystemStatus_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSFaultLevel_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_IsoDetStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVShutdownReq_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargeVoltMax_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerCtrl_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatModeSelect_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MainPosCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MainNegCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PreChrgCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargeCurrentMax_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_Manufacture_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_BalanceType_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SysStat_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinBatTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinCellTempNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxBatTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxCellTempNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMaxTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMinTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatSetTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxClVlt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxCellVoltNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMaxCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinClVlt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinCellVoltNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMinCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack1_RechrNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack1_RechrPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSDTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MesCellVoltNumIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes1CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes1CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes2CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes2CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes3CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Mes3CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MesCellTempNumIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellTempMes6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_Fault_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVIsoWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVILWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCLowWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TempDiffWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TempHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackOvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackUvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellOvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CellUvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOCFastChgWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PwrBatPackMismatchWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCelConsistencyWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSVolHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackOCWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK1_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK2_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK3_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSPACK4_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RestEnergy(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_Fault_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP5Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP4Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP3Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMU_SP2Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PreChrgHVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinBatWaterTmpIn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxBatWaterTmpOut(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_HVCurr_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackVoltVld(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackCurrentVld(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PackCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_HVCurr_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_PosVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_NegVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_PosRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_ISO_NegRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CurRechgEnergyStorSysIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCodeLength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCodeIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RechgEnergyStorSysCode4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSSwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSHwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SOP_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBatSOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBCP_LngTrmChrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBDP_LngTrmDischrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SOP_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_number(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_number_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_Current_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_SerialNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Year(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Month(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_ProductionDate_Day(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_PeakSOP_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBCP_ShrtTrmChrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVBDP_ShrtTrmDischrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_PeakSOP_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSCellQuantity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RealSOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSTempProbeQuantity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVIsoValue(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOH(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_SOE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TotalBatteryCap(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatMagCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVSystemStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSFaultLevel(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_IsoDetStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HVShutdownReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargeVoltMax(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerCtrl(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatModeSelect(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MainPosCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MainNegCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_PreChrgCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargeCurrentMax(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_Manufacture(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Pack_BalanceType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMS_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinBatTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MinCellTempNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxBatTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_MaxCellTempNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMaxTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BMSMinTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HeatSetTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3081_U_Out_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3082_I_Out_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3083_Time_Charged_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_Auto_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Rea_Manual_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_Fault_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_T_CHG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_CHGCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_T_Inter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_Deliver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_3522_Stop_Fault_EmerStop_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_Other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_3523_Stop_Fault_Mismatch_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3523_Stop_Fault_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3921_Timeout_BRM_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3922_Timeout_BCP_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3923_Timeout_BRO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3924_Timeout_BCS_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3925_Timeout_BCL_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3926_Timeout_BST_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3927_Timeout_BSD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_CrossNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_CrossPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_DirectNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_DirectPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCHighByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCLowByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCFailureTypeByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Shunt_Current_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_Relay_OutVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_Relay_intVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_FuseVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_PosVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_NegVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_PosRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_NegRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_TEMP1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_TEMP2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_position_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Pyroswitch_CMD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_SysStat_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_FUSE1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_TEMP2_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_TEMP1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_CC1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_K1K3_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_K2K4_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ELOCK_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_CAR_CONNECTSTATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_FaultSevtyStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_12V_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_24V_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISOCheckFinish_flg_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUSwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUHwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_SysStat_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num5_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num6_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num7_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3072_U_Req_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3073_I_Req_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3078_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3074_ChgMode_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2816_Ucell_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2817_I_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2818_kWh_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2819_U_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2820_T_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2821_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2822_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3075_U_Mea_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3076_I_Mea_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3077_Ucell_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3077_Ucell_Max_Grp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3079_Time_Remain_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CHM_SPN2600_Comm_Ver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BHM_SPN2601_Ubat_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2566_Bat_Type_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2567_Cap_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2568_U_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2565_Comm_Ver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2569_BatFactory_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2570_PackSN_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3601_SOC_Final_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3602_Ucell_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3603_Ucell_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3604_T_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3605_T_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3085_Ucell_Max_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3086_T_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3087_T_Max_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3088_T_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3089_T_Min_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3090_Ucell_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3091_SOC_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3092_I_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3093_T_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3094_Iso_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3095_OutConnector_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3096_Chg_Enable_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_Ucell_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_StopReason_CHGStop_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_Iso_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_OutCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_StopFault_BCUcompo_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_ChgCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_T_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_HVRelay_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_CC2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_Other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3513_Stop_Fault_I_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3513_Stop_Fault_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3901TimeoutSPN2560_0x00_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3902TimeoutSPN2560_0xAA_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3903_Timeout_CTS_CML_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3904_Timeout_CRO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3905_Timeout_CCS_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3906_Timeout_CST_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3907_Timeout_CSD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3081_U_Out(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3082_I_Out(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCS_SPN3083_Time_Charged(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_Auto(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_Manual(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_Fault(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3521_Stop_Reason_BMSStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_T_CHG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_CHGCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_T_Inter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_Deliver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_EmerStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3522_Stop_Fault_Other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3523_Stop_Fault_Mismatch(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CST_SPN3523_Stop_Fault_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3921_Timeout_BRM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3922_Timeout_BCP(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3923_Timeout_BRO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3924_Timeout_BCS(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3925_Timeout_BCL(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3926_Timeout_BST(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_SPN3927_Timeout_BSD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CEM_other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_CrossNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_CrossPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_DirectNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU1_DirectPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUDTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Shunt_Current(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_Relay_OutVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_Relay_intVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_HV_FuseVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_PosVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_NegVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_PosRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_NegRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_TEMP1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_TEMP2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_position(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Pyroswitch_CMD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_FUSE1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISO_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_TEMP2_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_GUN_TEMP1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_CC1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_K1K3_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_K2K4_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ELOCK_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_CAR_CONNECTSTATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_FaultSevtyStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_12V_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_24V_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_ISOCheckFinish_flg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUSwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCUHwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CCU_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_VIN_Num7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3072_U_Req(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3073_I_Req(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3078_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCL_SPN3074_ChgMode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2816_Ucell_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2817_I_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2818_kWh_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2819_U_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2820_T_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2821_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCP_SPN2822_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3075_U_Mea(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3076_I_Mea(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3077_Ucell_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3077_Ucell_Max_Grp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BCS_SPN3079_Time_Remain(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_CHM_SPN2600_Comm_Ver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BHM_SPN2601_Ubat_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2566_Bat_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2567_Cap_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2568_U_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2565_Comm_Ver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2569_BatFactory(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BRM_SPN2570_PackSN(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3601_SOC_Final(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3602_Ucell_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3603_Ucell_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3604_T_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSD_SPN3605_T_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3085_Ucell_Max_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3086_T_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3087_T_Max_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3088_T_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3089_T_Min_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3090_Ucell_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3091_SOC_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3092_I_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3093_T_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3094_Iso_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3095_OutConnector_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BSM_SPN3096_Chg_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_Ucell(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3511_Stop_Reason_CHGStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_Iso(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_OutCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_BCUcompo(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_ChgCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_T(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_HVRelay(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_CC2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3512_Stop_Fault_Other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3513_Stop_Fault_I(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BST_SPN3513_Stop_Fault_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3901_Timeout_SPN2560_0x00(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3902_Timeout_SPN2560_0xAA(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3903_Timeout_CTS_CML(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3904_Timeout_CRO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3905_Timeout_CCS(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3906_Timeout_CST(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_SPN3907_Timeout_CSD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_BEM_other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal10_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal11_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal1_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal2_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal3_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal4_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal5_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal6_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal7_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal8_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCModuleSignal9_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCPFC_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCInput_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_AirTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCOutput_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultCode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCOutTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCOutput_Current(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCIntTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultHistory2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultHistory4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultHistory5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultHistory1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFaultHistory3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCRunDays(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCRunHours(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCSoftVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_RES5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFautOutputCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFautOutputVltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFautTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDCFautInputVltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputVolt_0(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputCurr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputOV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputUV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_SecondOT(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_InputFault(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PowerState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PrimStatus_Res1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PrimStatus_Res2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_IntputVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_InputOV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_InputUV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_InputVoltMismatch(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_InputBusVoltStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_PrimaryOT(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_SecondStatus_Res1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_SecondStatus_Res2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_SecondStatus_Res3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_Second_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_OutputPower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_DCDC_Prim_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUWaterTmpIn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUWaterTmpOut_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUSystemMode_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerReq_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUFaultStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUFaultSevtyStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerDemand_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUEnvTemp_A_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUWaterTmpIn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUWaterTmpOut(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUSystemMode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUFaultStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUFaultSevtyStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUPowerDemand(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_HCUEnvTemp_A(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_AccStrate_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_Tariff_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_Tariff_Starttime(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_Tariff_duration(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_Tariff_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Order_Tariff_value(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_AccStrate_ServiceFee(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Calibration_3D_result(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Calibration_3D_resultM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Serve_Stop_Charge_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_CCU_IndexM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_AFC_Out_cap_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_Battery_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Start_Charge_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Stop_Fill_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Start_Fill_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd1M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd2M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd3M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd4M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd5M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd6M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd7M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd8M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_Version_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppResetTypeEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_GetFirmwareStatusReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_cancelReservationReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_lockConnectorReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_unlockConnectorReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_cancelReservationReq_CCUIDM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_bootNotificationConf_CCUIDM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_OcppAvailabilityTypeEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteUpdateM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_DisplaycmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Adver_dis_updatecmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_HeaterSetM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Serve_Stop_Charge_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_CCU_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_AFC_Out_capacity_info(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_Battery_information(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Start_Charge_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Stop_Fill_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_Serve_Start_Fill_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_Control_Cmd8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Query_Version_information(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppResetTypeEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_GetFirmwareStatusReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_cancelReservationReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_lockConnectorReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_unlockConnectorReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_cancelReservationReq_CCUID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_bootNotificationConf_CCUID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_OcppAvailabilityTypeEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteUpdate(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Displaycmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Adver_dis_updatecmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_HeaterSet(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Year(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Month(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Day(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Hour(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Minute(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOXTimer_Second(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_network_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Ethernet_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_GPS_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_BLE_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Wlan_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_CHG_Loc_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_CRM_SPN2562_CHG_Loc(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_UserID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Serial_Num(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Card_Balance(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Auth_Results(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_CCUIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EMS_AccStrate_Num(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EMS_Date_Updated_Year(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EMS_Date_Updated_Month(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EMS_Date_Updated_Day(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargeModeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_ChargemodeValue(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_StartChargeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_StopChargeCode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_ChargeModeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_ChargeTime(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_ChargeCost(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_ChargePower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Auth_Mode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Card_Num1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Card_Num2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Card_Num3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Card_Num4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Card_Num5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_PaymentEnumType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod02(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType02(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_startPeriod16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_duration16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppPhysicalValueType16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_SetChargingProfileReq_Id(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_RemoteStartId9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcode14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_QRcodelength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TDF_3D_Acceleration_X(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TDF_3D_Acceleration_Y(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TDF_3D_Acceleration_Z(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_UseCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_IDlength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_ID16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Passwordlength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_WIFI_Password16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_CCU_Set_IndexM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU1_OcppAvailabEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU2_OcppAvailabEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_StandardConfigKeyEM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_blinkRepeatM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_lightIntensityM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxVoltageTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxCurrentTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxPowerTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_ElevationM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUminVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUminCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxPowerM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_get_StandardConfigKeyEM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppMeasurandEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_measurandArraySizeM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_numberOfConnectorsM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_resetRetriesM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU1_chargePointStatuM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU2_chargePointStatuM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_expiryDateM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_chargingSchePeriodSizeM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_EMS_MaxACVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_EMS_MaxACCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_HeatSet_TempM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_CCU_Set_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU1_OcppAvailabilityEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU2_OcppAvailabilityEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_StandardConfigKeyEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_blinkRepeat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_lightIntensity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxVoltageTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxCurrentTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_maxPowerTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_Elevation(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUminVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUminCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_CCUmaxPower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_get_StandardConfigKeyEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppMeasurandEnum1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppMeasurandEnum2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppMeasurandEnum3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_OcppMeasurandEnum4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_measurandArraySize(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_numberOfConnectors(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_T_resetRetries(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU1_chargePointStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_CCU2_chargePointStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_expiryDate(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_chargingSchePeriodArraySize(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_EMS_MaxACVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_Set_EMS_MaxACCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TBOX_HeatSet_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Crash_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Crash_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_Rollover_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_Crash_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_DTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_DTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_TFD_TBOX_DTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"


/* End: ComNotification for Signals */


/* Start: ComNotification for Signals Groups */



/* End: ComNotification for Signals Groups */


/* Start: ComNotification for Rx IPdus */


/* End: ComNotification for Rx IPdus */


/******************************************************************/

/************* Com Error Notification in Tx side ************************/


/* Start: ComErrorNotification For Ipdu's */



/* End: ComErrorNotification for Ipdu's */


/* Start: ComErrorNotification for Signals */



/* End: ComErrorNotification for Signals */


/* Start: ComErrorNotification for Signals Groups */


/* End: ComErrorNotification for Signals Groups */


/******************************************************************/

/************* Com Timeout Notification in Tx side ************************/


/* Start: ComTimeoutNotification for Signals */



/* End: ComTimeoutNotification for Signals */


/* Start: ComTimeoutNotification for Signals Groups */


/* End: ComTimeoutNotification for Signals Groups */

/******************************************************************/

/************* Com Notification in Rx side ************************/


/* Start: ComTimeoutNotification for Signals */


#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh2_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOLTester_SetConfirm_Type_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCV_SetID6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LEM_SetADD6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACWh1_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACDC_PowerSetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACDC1_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ACDC2_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh1_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCWh2_SetAdd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PowerSetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PowerNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PowerSetAdd_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PowerSetAdd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_Number(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_SetSN1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_SetSN2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_SetSN3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPACDC_SetSN4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_SetAdd_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_Number(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_SetSN1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_SetSN2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_SetSN3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LPDCDC_SetSN4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData0(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EOLTesterData5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaskData(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CRCdata(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOL_Poject_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_Tester_Serial(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_LED_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AD_Speaker_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AD_FAN_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CoolingFAN_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_WIFI_TestCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOL_ACDC_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOL_DCDC_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOL_ISOFaultdete_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AFC_EOL_HCUTest_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxClVlt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxCellVoltNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMaxCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinClVlt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinCellVoltNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMinCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack1_RechrNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack1_RechrPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCHighByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCLowByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCFailureTypeByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MesCellVoltNumIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes1CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes1CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes2CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes2CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes3CellBalState_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes3CellVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MesCellTempNumIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes5_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes6_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_Fault_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVIsoWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVILWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCLowWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TempDiffWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TempHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackOvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackUvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellOvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellUvWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCFastChgWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PwrBatPackMismatchWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCelConsistencyWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSVolHighWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackOCWarning_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK1_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK2_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK3_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK4_RelayWaring_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RestEnergy_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_Fault_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP5Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP4Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP3Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP2Volt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PreChrgHVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinBatWaterTmpIn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxBatWaterTmpOut_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_HVCurr_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackVoltVld_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackCurrentVld_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackCurrent_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_HVCurr_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_PosVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_NegVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_PosRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_NegRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CurRechgEnergyStorSysIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCodeLength_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCodeIndex_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSSwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSHwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SOP_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBatSOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBCP_LngTrmChrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBDP_LngTrmDischrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SOP_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_number_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_number_index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_Current_Status_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_SerialNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_ProductionDate_Year_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_ProductionDate_Month_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_ProductionDate_Day_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_PeakSOP_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBCP_ShrtTrmChrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBDP_ShrtTrmDischrgPwr_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_PeakSOP_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellQuantity_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RealSOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSTempProbeQuantity_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVIsoValue_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOH_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TotalBatteryCap_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SysStat_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatMagCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVSystemStatus_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSFaultLevel_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_IsoDetStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVShutdownReq_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargeVoltMax_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerCtrl_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatModeSelect_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MainPosCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MainNegCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PreChrgCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargeCurrentMax_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_Manufacture_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_BalanceType_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SysStat_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinBatTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinCellTempNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxBatTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxCellTempNumb_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMaxTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMinTempBatteryNumber_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatSetTmp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxClVlt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxCellVoltNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMaxCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinClVlt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinCellVoltNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMinCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack1_RechrNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack1_RechrPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSDTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MesCellVoltNumIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes1CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes1CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes2CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes2CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes3CellBalState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Mes3CellVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MesCellTempNumIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellTempMes6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_Fault_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVIsoWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVILWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCLowWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TempDiffWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TempHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackOvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackUvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellOvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CellUvWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOCFastChgWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PwrBatPackMismatchWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCelConsistencyWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSVolHighWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackOCWarning(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK1_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK2_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK3_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSPACK4_RelayWaring(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RestEnergy(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_Fault_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP5Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP4Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP3Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMU_SP2Volt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PreChrgHVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinBatWaterTmpIn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxBatWaterTmpOut(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackVoltVld(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackCurrentVld(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PackCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_HVCurr_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_PosVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_NegVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_PosRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_ISO_NegRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CurRechgEnergyStorSysIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCodeLength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCodeIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RechgEnergyStorSysCode4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSSwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSHwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBatSOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBCP_LngTrmChrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBDP_LngTrmDischrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_PeakSOP_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBCP_ShrtTrmChrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVBDP_ShrtTrmDischrgPwr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_PeakSOP_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSCellQuantity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RealSOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSTempProbeQuantity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVIsoValue(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOH(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_SOE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TotalBatteryCap(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatMagCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVSystemStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSFaultLevel(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_IsoDetStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HVShutdownReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargeVoltMax(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerCtrl(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatModeSelect(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MainPosCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MainNegCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_PreChrgCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargeCurrentMax(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_Manufacture(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Pack_BalanceType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMS_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinBatTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MinCellTempNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxBatTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_MaxCellTempNumb(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMaxTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BMSMinTempBatteryNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HeatSetTmp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3081_U_Out_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3082_I_Out_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3083_Time_Charged_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Reason_Auto_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Rea_Manual_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_T_CHG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_CHGCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_T_Inter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_Deliver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_3522_Stop_Fault_EmerStop_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_Other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_3523_Stop_Fault_Mismatch_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3523_Stop_Fault_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3921_Timeout_BRM_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3922_Timeout_BCP_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3923_Timeout_BRO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3924_Timeout_BCS_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3925_Timeout_BCL_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3926_Timeout_BST_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3927_Timeout_BSD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_CrossNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_CrossPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_DirectNeg_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_DirectPos_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCHighByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCLowByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCFailureTypeByte_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_Relay_OutVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_Relay_intVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_FuseVLTG_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_PosVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_NegVolt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_PosRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_NegRes_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_TEMP1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_TEMP2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_position_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_Pyroswitch_CMD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_SysStat_AliveCounter_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_FUSE1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_TEMP2_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_TEMP1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_CC1_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_K1K3_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_K2K4_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ELOCK_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_CAR_CONNECTSTATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_FaultSevtyStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_12V_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_24V_STATE_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISOCheckFinish_flg_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUSwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUHwVersion_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_SysStat_CheckSum_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num1_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num3_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num4_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num5_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num6_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num7_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3072_U_Req_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3073_I_Req_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3078_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3074_ChgMode_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2817_I_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2818_kWh_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2819_U_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2820_T_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2821_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2822_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3075_U_Mea_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3076_I_Mea_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3077_Ucell_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3077_Ucell_Max_Grp_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3079_Time_Remain_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CHM_SPN2600_Comm_Ver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BHM_SPN2601_Ubat_Max_Permit_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2566_Bat_Type_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2567_Cap_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2568_U_Nom_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2565_Comm_Ver_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2569_BatFactory_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2570_PackSN_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3601_SOC_Final_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3602_Ucell_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3603_Ucell_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3604_T_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3605_T_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3085_Ucell_Max_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3086_T_Max_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3087_T_Max_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3088_T_Min_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3089_T_Min_Index_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3090_Ucell_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3091_SOC_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3092_I_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3093_T_Warn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3094_Iso_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3095_OutConnector_State_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3096_Chg_Enable_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_SOC_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_Ucell_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_StopReason_CHGStop_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_Iso_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_OutCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_StopFault_BCUcompo_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_ChgCnnt_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_T_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_HVRelay_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_CC2_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_Other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3513_Stop_Fault_U_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3901TimeoutSPN2560_0x00_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3902TimeoutSPN2560_0xAA_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3903_Timeout_CTS_CML_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3904_Timeout_CRO_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3905_Timeout_CCS_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3906_Timeout_CST_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3907_Timeout_CSD_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_other_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3081_U_Out(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3082_I_Out(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCS_SPN3083_Time_Charged(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Reason_Auto(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Reason_Manual(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Reason_Fault(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3521_Stop_Reason_BMSStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_T_CHG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_CHGCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_T_Inter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_Deliver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_EmerStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3522_Stop_Fault_Other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3523_Stop_Fault_Mismatch(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CST_SPN3523_Stop_Fault_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3921_Timeout_BRM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3922_Timeout_BCP(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3923_Timeout_BRO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3924_Timeout_BCS(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3925_Timeout_BCL(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3926_Timeout_BST(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_SPN3927_Timeout_BSD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CEM_other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_CrossNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_CrossPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_DirectNeg_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU1_DirectPos_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUDTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_Shunt_Current(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_Relay_OutVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_Relay_intVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_HV_FuseVLTG(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_PosVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_NegVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_PosRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_NegRes(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_TEMP1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_TEMP2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_position(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_Pyroswitch_CMD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_FUSE1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISO_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_TEMP2_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_GUN_TEMP1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_CC1_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_K1K3_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_K2K4_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ELOCK_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_CAR_CONNECTSTATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_FaultSevtyStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_12V_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_24V_STATE(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_ISOCheckFinish_flg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUSwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCUHwVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CCU_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_VIN_Num7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3072_U_Req(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3073_I_Req(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3078_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCL_SPN3074_ChgMode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2816_Ucell_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2817_I_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2818_kWh_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2819_U_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2820_T_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2821_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCP_SPN2822_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3075_U_Mea(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3076_I_Mea(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3077_Ucell_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3077_Ucell_Max_Grp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BCS_SPN3079_Time_Remain(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_CHM_SPN2600_Comm_Ver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BHM_SPN2601_Ubat_Max_Permit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2566_Bat_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2567_Cap_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2568_U_Nom(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2565_Comm_Ver(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2569_BatFactory(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BRM_SPN2570_PackSN(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3601_SOC_Final(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3602_Ucell_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3603_Ucell_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3604_T_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSD_SPN3605_T_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3085_Ucell_Max_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3086_T_Max(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3087_T_Max_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3088_T_Min(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3089_T_Min_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3090_Ucell_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3091_SOC_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3092_I_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3093_T_Warn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3094_Iso_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3095_OutConnector_State(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BSM_SPN3096_Chg_Enable(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_SOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_Ucell(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3511_Stop_Reason_CHGStop(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_Iso(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_OutCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_BCUcompo(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_ChgCnnt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_T(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_HVRelay(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_CC2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3512_Stop_Fault_Other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3513_Stop_Fault_I(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BST_SPN3513_Stop_Fault_U(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3901_Timeout_SPN2560_0x00(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3902_Timeout_SPN2560_0xAA(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3903_Timeout_CTS_CML(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3904_Timeout_CRO(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3905_Timeout_CCS(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3906_Timeout_CST(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_SPN3907_Timeout_CSD(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_BEM_other(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal10_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal11_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal1_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal2_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal3_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal4_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal5_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal6_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal7_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal8_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCModuleSignal9_Rx_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCPFC_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCInput_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_AirTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCOutput_Vltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultCode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCOutTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCOutput_Current(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCIntTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultHistory2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultHistory4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultHistory5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultNumber(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultHistory1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFaultHistory3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCRunDays(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCRunHours(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCSoftVersion(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_RES5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFautOutputCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFautOutputVltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFautTemp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDCFautInputVltg(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputVolt_0(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputCurr(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputOV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputUV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_SecondOT(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputOC(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_InputFault(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PowerState(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PrimStatus_Res1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PrimStatus_Res2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_IntputVolt(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_InputOV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_InputUV(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_InputVoltMismatch(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_InputBusVoltStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_PrimaryOT(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_SecondStatus_Res1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_SecondStatus_Res2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_SecondStatus_Res3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_Second_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_OutputPower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_DCDC_Prim_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUWaterTmpIn_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUWaterTmpOut_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUSystemMode_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerReq_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUCntStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUFaultStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUFaultSevtyStat_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerDemand_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUEnvTemp_A_2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUWaterTmpIn(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUWaterTmpOut(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUSystemMode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUCntStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUFaultStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUFaultSevtyStat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUPowerDemand(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_HCUEnvTemp_A(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_AccStrate_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_Tariff_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_Tariff_Starttime(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_Tariff_duration(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_Tariff_Type(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Order_Tariff_value(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_AccStrate_ServiceFee(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Calibration_3D_result(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Calibration_3D_resultM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Serve_Stop_Charge_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_CCU_IndexM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_AFC_Out_cap_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_Battery_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Start_Charge_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Stop_Fill_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Start_Fill_CmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd1M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd2M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd3M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd4M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd5M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd6M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd7M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd8M(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_Version_infoM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppResetTypeEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_GetFirmwareStatusReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_cancelReservationReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_lockConnectorReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_unlockConnectorReqM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_cancelReservationReq_CCUIDM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_bootNotificationConf_CCUIDM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_OcppAvailabilityTypeEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteUpdateM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_DisplaycmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Adver_dis_updatecmdM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_HeaterSetM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Serve_Stop_Charge_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_CCU_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_AFC_Out_capacity_info(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_Battery_information(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Start_Charge_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Stop_Fill_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_Serve_Start_Fill_Cmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_Control_Cmd8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Query_Version_information(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppResetTypeEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_GetFirmwareStatusReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_cancelReservationReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_lockConnectorReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_unlockConnectorReq(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_cancelReservationReq_CCUID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_bootNotificationConf_CCUID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_OcppAvailabilityTypeEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteUpdate(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Displaycmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Adver_dis_updatecmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_HeaterSet(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Year(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Month(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Day(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Hour(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Minute(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOXTimer_Second(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_network_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_SysStat_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Ethernet_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_GPS_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_BLE_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Wlan_Signal_Quality(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_SysStat_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_CHG_Loc_Invalid(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_CRM_SPN2562_CHG_Loc(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_UserID(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Serial_Num(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Card_Balance(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Auth_Results(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_CCUIndex(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EMS_AccStrate_Num(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EMS_Date_Updated_Year(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EMS_Date_Updated_Month(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_EMS_Date_Updated_Day(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargeModeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_ChargemodeValue(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_StartChargeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_StopChargeCode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_ChargeModeType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_ChargeTime(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_ChargeCost(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_ChargePower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Auth_Mode(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Card_Num1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Card_Num2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Card_Num3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Card_Num4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Card_Num5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_PaymentEnumType(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType01(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod02(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType02(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType03(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType04(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType05(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType06(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType07(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType08(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType09(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_startPeriod16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_duration16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppPhysicalValueType16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_SetChargingProfileReq_Id(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_RemoteStartId9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode_index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcode14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_QRcodelength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TDF_3D_Acceleration_X(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TDF_3D_Acceleration_Y(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TDF_3D_Acceleration_Z(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_UseCmd(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_IDlength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_ID16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Passwordlength(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password6(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password7(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password8(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password9(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password10(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password11(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password12(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password13(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password14(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password15(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_WIFI_Password16(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_CCU_Set_IndexM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU1_OcppAvailabEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU2_OcppAvailabEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_StandardConfigKeyEM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_blinkRepeatM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_lightIntensityM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxVoltageTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxCurrentTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxPowerTotalM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_ElevationM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUminVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUminCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxPowerM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_get_StandardConfigKeyEM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppMeasurandEnumM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_measurandArraySizeM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_numberOfConnectorsM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_resetRetriesM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU1_chargePointStatuM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU2_chargePointStatuM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_expiryDateM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_chargingSchePeriodSizeM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_EMS_MaxACVoltageM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_EMS_MaxACCurrentM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_HeatSet_TempM(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_CCU_Set_Index(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU1_OcppAvailabilityEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU2_OcppAvailabilityEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_StandardConfigKeyEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_blinkRepeat(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_lightIntensity(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxVoltageTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxCurrentTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_maxPowerTotal(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_Elevation(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUminVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUminCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_CCUmaxPower(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_get_StandardConfigKeyEnum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppMeasurandEnum1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppMeasurandEnum2(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppMeasurandEnum3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_OcppMeasurandEnum4(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_measurandArraySize(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_numberOfConnectors(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_T_resetRetries(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU1_chargePointStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_CCU2_chargePointStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_expiryDate(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_chargingSchePeriodArraySize(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_EMS_MaxACVoltage(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_Set_EMS_MaxACCurrent(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TBOX_HeatSet_Temp(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Crash_AliveCounter(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Crash_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_Rollover_Status(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_Crash_CheckSum(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_DTCHighByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_DTCLowByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbkTOut_TFD_TBOX_DTCFailureTypeByte(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"


/* End: ComTimeoutNotification for Signals */


/* Start: ComTimeoutNotification for Signals Groups */


/* End: ComTimeoutNotification for Signals Groups */


/******************************************************************/

/************* Com Invalid Notification for Rx************************/


/* Start: ComInvalidNotification for Signals */



/* End: ComInvalidNotification for Signals */


/* Start: ComInvalidNotification for Signals Groups */

/* End: ComInvalidNotification for Signals Groups */



/******************************************************************/

/************* Com Ipdu Callouts ************************/




#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX10(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX11(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX2(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX8(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Confirm_MUX9(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_SafeCertif_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC2_EOLTester_Serial_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX10(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX11(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX2(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX8(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Confirm_MUX9(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_SafeCertif_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_AFC_EOLTester_Serial_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_Cell_18042701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_ConntSts_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_DTC_18AA2701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_DetCell_18052701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_DetTemp_18062701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_Fault_18072701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_HV2_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_HV_18022701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_ISO_18162701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_Info_18082701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_PackInfo_18142701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_PeskSOP_18172701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_SystPara_18012701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_SystStat_18122701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS2_Temp_18152701h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_Cell_18042701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_ConntSts_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_DTC_18AA2701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_DetCell_18052701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_DetTemp_18062701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_Fault_18072701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_HV2_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_HV_18022701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_ISO_18162701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_Info_18082701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_LongSOP_18032701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_PackInfo_18142701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_PeskSOP_18172701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_SystPara_18012701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_SystStat_18122701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_BMS_Temp_18152701h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_CCS_1819FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_CSTCEM_181DFAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_ConntSts_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_DTC_18AAFAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_HV_1802FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_ISO_1820FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_Sample_1803FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VIN_1816FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBCL_1817FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBCP1_1812FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBCP2_1813FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBCS_1818FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBHM_1811FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBRM1_1814FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBRM2_1815FAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBSD_181BFAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBSM_181AFAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU2_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_CCS_1819FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_CSTCEM_181DFAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_ConntSts_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_DTC_18AAFAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_HV_1802FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_ISO_1820FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_Sample_1803FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VIN_1816FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBCL_1817FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBCP1_1812FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBCP2_1813FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBCS_1818FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBHM_1811FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBRM1_1814FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBRM2_1815FAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBSD_181BFAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBSM_181AFAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_CCU_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame10_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame11_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame1_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame2_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame3_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame4_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame5_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame6_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame7_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame8_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDCModuleFrame9_Rx_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDC_1_18F8622Bh_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDC_2_18F8622Ch_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDC_3_18F8622Dh_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDC_Msg1_18FF50E5h_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_DCDC_Msg2_18FF51E5h_Can_Network_CANNODE_4(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_HCU2_Syst_18220145h_Can_Network_CANNODE_3(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_HCU_Syst_18220145h_Can_Network_CANNODE_1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1801F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1802F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1803F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1804F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1805F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1806F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1807F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1808F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x1809F102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180AF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180BF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180CF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180DF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180EF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x180FF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX2_0x18FFF102_Can_Network_CANNODE_6(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1801F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1802F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1803F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1804F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1805F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1806F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1807F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1808F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x1809F102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180AF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180BF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180CF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180DF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180EF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x180FF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_TBOX_0x18FFF102_Can_Network_CANNODE_5(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_Tester2_18FFFA01h_MUX1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_RxCbk_Tester_18FFFA01h_MUX1(VAR(PduIdType, AUTOMATIC) id, P2CONST(uint8, AUTOMATIC, COM_APPL_CONST) ptr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"



/******************************************************************/

/*************Error Notification for Rx Ipdus *****************/

/* Start: ComErrorNotification For Ipdu's */


#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_Cell_18042701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_ConntSts_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_Fault_18072701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_HV2_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_SystPara_18012701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_SystStat_18122701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS2_Temp_18152701h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_Cell_18042701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_ConntSts_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_Fault_18072701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_HV2_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_HV_18022701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_LongSOP_18032701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_SystPara_18012701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_SystStat_18122701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_BMS_Temp_18152701h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_HCU2_Syst_18220145h_Can_Network_CANNODE_3(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_HCU_Syst_18220145h_Can_Network_CANNODE_1(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_TBOX_0x1803F102_Can_Network_CANNODE_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_RxTOCbk_TBOX_0x1804F102_Can_Network_CANNODE_5(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"


#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Rte_COMCbk_EthernetPdu_Rx_EthernetPhysicalChannel_null_ETH_Rx(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/******************************************************************/

#endif /* COM_CBK_H */

