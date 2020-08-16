#ifndef POWMODULE_H_
#define POWMODULE_H_
#include "typedefs.h"
#include "Platform_Types.h"

#define WorkModule    //0为工作模式，1为调试模式

#define SIDE_LEFT 0
#define SIDE_RIGHT 1
#define SIDE_ACDC1 2
#define SIDE_ACDC2 3

#define VERSION_CN 0
#define VERSION_EU 1
#define VERSION_100D 2
#define VERSION_FT 3
#define VERSION_CN_YFY 4
#define VERSION_100D_YL 5

#define DCDC_SEND_NUM 10
#define VERSION_NUM 6
//0:国版永联
//1：欧版永联
//2：小电量英飞源
//3：富特版
#define ADRESS_NUMBER 13
#define DCDC_NUM 11
#define GROUP_NUM 3
#define SIDE_NUM 4
#define ReadRegNum 11  //目前已使用的读取寄存器数目
#define ZERO_VOLTAGE 150  //电压零点
#define ZERO_CURRENT 1  //电流零点
#define ZERO_CURRENT1 0.075  //电流零点
#define STANDBY_VALUE 200
#define IDLE_VALUE 200
#define RUN_VALUE 100

#define ACDC_Volt_Out2Baty 5
#define DCDC_Volt_Out2Baty 5
#define ACDC_Volt_OutInRun 700
#define DCDC_Volt_OutInRun 700
#define VOLT_CHANGE_TIME 2000
#define VOLT_CHANGE_VALUE 5
#define VOLT_HIGH_TIME 100
#define VoltDevi 100

#define INPUT_MODE_AC 1  
#define INPUT_MODE_DC 2
#define DCDC_SWITCH_ON  0x00000000
#define DCDC_SWITCH_OFF 0x00010000

#define REC_ERROR_TIMEOUT_TIME 100
#define SEND_PERIOD 10  //单位为10ms
#define SEND_REG_NUM 12

#define SINGLE_GUN_LIMIT 200  //单枪输出电流限制值
#define ACDC_MAX_CURRENT 100

#define PM_DEBUG_REC_ID 0x98F8622D

//当增加读取寄存器号时，需一同更改ReadRegNum
typedef enum /*register_enu*/
{
	Get_Float_OutPutVoltage,  //读输出电压
	Get_Float_OutPutCurrent,  //读输出电流
	Get_Float_InputDCVoltage,  //读直流输入电压
	Get_Float_In_liq_T,
	Get_Float_Out_liq_T,
	Get_Float_EnvirTemp,  //读环境温度
	Get_Float_InputAPhaseVoltage,  //读A相输入电压
	Get_Float_InputBPhaseVoltage,  //读B相输入电压
	Get_Float_InputCPhaseVoltage,  //读C相输入电压
	Get_Int_Alarm,
	Get_Int_Alarm2,
	Set_Int_Elevation,  //工作海拔值
	Set_Int_OutputCurrent,  //输出电流
	Set_Int_Group,  //组号
	Set_Int_AddressMode,  //地址分配方式
	Set_Float_OutPutVoltage,  //输出电压
	Set_Float_LimitCurrent,  //限流点
	Set_Float_LimitVoltage,  //限压点
	Set_Int_OnOff,  //开关
	Set_Int_VoltageReset,  //过压复位
	Set_Int_VolProtectRelated,  //设置模块输出过压保护关联是否允许
	Set_Int_ShortReset,  //短路复位
	Set_Int_InputMode,  //输入模式
	Reg_MaxValue
}register_enu;

typedef enum
{
	LH_EU,
	AH_EU,
	AH_CN,
	D100,
	YFY_CN,
	D100_YL
}enum_Version;
void InterfaceTrans();
void RecManage(uint8_t adress_par);
extern void DCDCTimeTask10ms();
//发送
extern uint8_t PM_SendData[ADRESS_NUMBER][8];
extern uint8_t PM_NormalInfo_flg[ADRESS_NUMBER];
//接收
extern uint8_t PM_RecError[ADRESS_NUMBER][Reg_MaxValue];  //返回报文状态是否为f0
extern uint8_t RecErrorCount[ADRESS_NUMBER][Reg_MaxValue];
extern float PM_RecVolt[ADRESS_NUMBER];
extern float PM_RecCurrent[ADRESS_NUMBER];
extern uint16_t PM_DCDCInputVoltByAdress[ADRESS_NUMBER];
extern uint32_t PM_Module_Alarm[ADRESS_NUMBER];  //设备告警信息记录，需对照协议来解析
extern uint16_t PM_DCDCTemperature_T[ADRESS_NUMBER];
extern uint8_t PM_RecFlag[ADRESS_NUMBER];
extern uint8_t PM_DCDCTimeOut_flg[ADRESS_NUMBER];
extern uint16_t PM_DCDCOnline_flg[SIDE_NUM];
extern uint8_t SideStart[SIDE_NUM];
extern uint8_t SideEnd[SIDE_NUM];
extern uint8_t SideLength[SIDE_NUM];

extern uint8 PM_DCDCStatus[SIDE_NUM];
extern uint8 PM_CQC_DCDCStatus[ADRESS_NUMBER];

extern uint8_t RecState(uint8_t side_par, register_enu reg_par);
extern void SetNormalFlag(uint8_t side_par);
extern void ClearNormalFlag(uint8_t side_par);
extern void dcdc_msg_fun10ms();
extern void DCDCTimeTask100ms();

extern void SetVoltBySide(uint8_t side_par);
extern void SetCurrentBySide(uint8_t side_par);
extern void SetOnoffBySide(uint8_t side_par);
extern void GetOutpurVoltBySide(uint8_t side_par);
extern void SetRecFlag(uint8_t adress_par);
extern void DCDCMessage_CanSend(uint32_t id, uint8_t * data);
extern uint8_t debugdata[8];
extern uint8_t debug_switch;
extern uint8  Active_Num;
extern uint8 PM_VERSION;
extern uint16_t PM_DCDCOutputVolt_V[15] = {0};
extern uint16_t PM_DCDCCurrent_A[15 ]= {0};
extern uint16_t PM_ACDCOutputVolt_V[2] = {0};
extern uint16_t PM_ACDCCurrent_A[2] = {0};
extern uint8 GbEBSW_ACDCVoltandDCDCVoltequal_enum;
#ifndef WorkModule
extern void PM_debug_data_rec(uint32 id,uint8* data);
extern enum_Version GeEBSW_AFCProductType_enum_1;
#endif
extern float get_GcEDCC_DCDCAOutVoltReq_V();
extern float get_GcEDCC_DCDCBOutVoltReq_V();
extern float get_GcEACC_ACDCAOutVoltReq_V();
extern float get_GcEACC_ACDCBOutVoltReq_V();

extern float get_GcEDCC_DCDCAOutCurrReq_A();
extern float get_GcEDCC_DCDCBOutCurrReq_A();
extern float get_GcEACC_ACDCAOutCurrReq_A();
extern float get_GcEACC_ACDCAOutCurrReq_A();

unsigned char get_GbEDCC_DCDCAPwrCmd_flg(void);
unsigned char get_GbEDCC_DCDCBPwrCmd_flg(void);
unsigned char get_GbEACC_ACDCAPwrCmd_flg(void);
unsigned char get_GbEACC_ACDCBPwrCmd_flg(void);
uint8_t TouchPanel_StationInputCtl_enum;
#endif


