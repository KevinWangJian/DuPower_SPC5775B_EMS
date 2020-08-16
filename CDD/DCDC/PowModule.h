#ifndef POWMODULE_H_
#define POWMODULE_H_
#include "typedefs.h"
#include "Platform_Types.h"

#define WorkModule    //0Ϊ����ģʽ��1Ϊ����ģʽ

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
//0:��������
//1��ŷ������
//2��С����Ӣ��Դ
//3�����ذ�
#define ADRESS_NUMBER 13
#define DCDC_NUM 11
#define GROUP_NUM 3
#define SIDE_NUM 4
#define ReadRegNum 11  //Ŀǰ��ʹ�õĶ�ȡ�Ĵ�����Ŀ
#define ZERO_VOLTAGE 150  //��ѹ���
#define ZERO_CURRENT 1  //�������
#define ZERO_CURRENT1 0.075  //�������
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
#define SEND_PERIOD 10  //��λΪ10ms
#define SEND_REG_NUM 12

#define SINGLE_GUN_LIMIT 200  //��ǹ�����������ֵ
#define ACDC_MAX_CURRENT 100

#define PM_DEBUG_REC_ID 0x98F8622D

//�����Ӷ�ȡ�Ĵ�����ʱ����һͬ����ReadRegNum
typedef enum /*register_enu*/
{
	Get_Float_OutPutVoltage,  //�������ѹ
	Get_Float_OutPutCurrent,  //���������
	Get_Float_InputDCVoltage,  //��ֱ�������ѹ
	Get_Float_In_liq_T,
	Get_Float_Out_liq_T,
	Get_Float_EnvirTemp,  //�������¶�
	Get_Float_InputAPhaseVoltage,  //��A�������ѹ
	Get_Float_InputBPhaseVoltage,  //��B�������ѹ
	Get_Float_InputCPhaseVoltage,  //��C�������ѹ
	Get_Int_Alarm,
	Get_Int_Alarm2,
	Set_Int_Elevation,  //��������ֵ
	Set_Int_OutputCurrent,  //�������
	Set_Int_Group,  //���
	Set_Int_AddressMode,  //��ַ���䷽ʽ
	Set_Float_OutPutVoltage,  //�����ѹ
	Set_Float_LimitCurrent,  //������
	Set_Float_LimitVoltage,  //��ѹ��
	Set_Int_OnOff,  //����
	Set_Int_VoltageReset,  //��ѹ��λ
	Set_Int_VolProtectRelated,  //����ģ�������ѹ���������Ƿ�����
	Set_Int_ShortReset,  //��·��λ
	Set_Int_InputMode,  //����ģʽ
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
//����
extern uint8_t PM_SendData[ADRESS_NUMBER][8];
extern uint8_t PM_NormalInfo_flg[ADRESS_NUMBER];
//����
extern uint8_t PM_RecError[ADRESS_NUMBER][Reg_MaxValue];  //���ر���״̬�Ƿ�Ϊf0
extern uint8_t RecErrorCount[ADRESS_NUMBER][Reg_MaxValue];
extern float PM_RecVolt[ADRESS_NUMBER];
extern float PM_RecCurrent[ADRESS_NUMBER];
extern uint16_t PM_DCDCInputVoltByAdress[ADRESS_NUMBER];
extern uint32_t PM_Module_Alarm[ADRESS_NUMBER];  //�豸�澯��Ϣ��¼�������Э��������
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


