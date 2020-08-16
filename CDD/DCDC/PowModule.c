#include "PowModule.h"
#include "typedefs.h"
#include "stdio.h"
#include "Platform_Types.h"
#include "Rte_Asw_Swc.h"
#include "ASW_RTE.h"
#include "ComAb.h"
#include "Can.h"

//#define DCDC_CHARGETOCAR_SWITCH 1
//AFC本机项目类型：
//0：默认为LH - EU
//1：AH -  EU
//2: AH - CN
//3. 小电量
//F：DeBug模式（用做调试）

enum_Version GeEBSW_AFCProductType_enum_1 = LH_EU;
uint8 PM_DCDCStatus[SIDE_NUM];
uint8 PM_CQC_DCDCStatus[ADRESS_NUMBER];

uint8 GbEBSW_ACDCVoltandDCDCVoltequal_enum = 0;
uint8 PM_VERSION = 0;
uint8_t SideStart[SIDE_NUM] = { 0,6,9,10 };
uint8_t SideEnd[SIDE_NUM] = { 5,8,9,10 };
uint8_t SideLength[SIDE_NUM] = { 2,2 ,1,1 };
uint8 FirstByte_GetData = 0x03;
uint8 FirstByte_SetData = 0x03;
uint8 DCDC_Rated_Current = 27;
uint8 DC_SINGLE_MODULE_LIMIT = 100;
uint8 AC_SINGLE_MODULE_LIMIT = 50;
uint8  Active_Num = 13;
uint8 dcdc_init_flag = 1;

#ifndef WorkModule
uint8_t debugdata[8];
uint8_t debug_switch;
#endif
//发送
uint8_t PM_SendData[ADRESS_NUMBER][8];
uint8_t PM_NormalInfo_flg[ADRESS_NUMBER];
//接收
uint8_t PM_RecError[ADRESS_NUMBER][Reg_MaxValue] = { 0, };  //返回报文状态是否为f0
uint8_t RecErrorCount[ADRESS_NUMBER][Reg_MaxValue] = { 0, };
float PM_RecVolt[ADRESS_NUMBER] = { 0 };
float PM_RecCurrent[ADRESS_NUMBER] = { 0 };
uint16_t PM_DCDCInputVoltByAdress[ADRESS_NUMBER];
uint32_t PM_Module_Alarm[ADRESS_NUMBER] = { 0 };  //设备告警信息记录，需对照协议来解析
uint16_t PM_DCDCTemperature_T[ADRESS_NUMBER] = {0};
float PM_In_liq_T[ADRESS_NUMBER];
float PM_Out_liq_T[ADRESS_NUMBER];
uint8_t PM_RecFlag[ADRESS_NUMBER] = { 0, };
uint8_t PM_DCDCTimeOut_flg[ADRESS_NUMBER];
uint16_t PM_DCDCOnline_flg[SIDE_NUM] = { 0,0,0,0 };
uint8_t PM_Online_flg[ADRESS_NUMBER];

static uint8 dcdc_clock_cnt[DCDC_SEND_NUM] = {3,3,3,2,2,2,1,1,1,1};
static uint8 dcdc_index = 0;

typedef struct
{
	register_enu RegName;
	uint16_t RegNum;
}PM_Reg_Struct;


PM_Reg_Struct PM_Reg_Stru_Array[] =
{
	{Get_Float_OutPutVoltage,0x0001},
	{Get_Float_OutPutCurrent,0x0002},
	{Get_Float_InputDCVoltage,0x0005},
	{Get_Float_In_liq_T,0x0006},
	{Get_Float_Out_liq_T,0x0007},
	{Get_Float_EnvirTemp,0x000B},
	{Get_Float_InputAPhaseVoltage,0x000C},
	{Get_Float_InputCPhaseVoltage,0x000D},
	{Get_Float_InputCPhaseVoltage,0x000E},
	{Get_Int_Alarm,0x0040},
	{Get_Int_Alarm2,0x0041},
	{Set_Int_Elevation,0x0017},
	{Set_Int_OutputCurrent,0x001B},
	{Set_Int_Group,0x001E},
	{Set_Int_AddressMode,0x001F},
	{Set_Float_OutPutVoltage,0x0021},
	{Set_Float_LimitCurrent,0x0022},
	{Set_Float_LimitVoltage,0x0023},
	{Set_Int_OnOff,0x0030},
	{Set_Int_VoltageReset,0x0031},
	{Set_Int_VolProtectRelated,0x003E},
	{Set_Int_ShortReset,0x0044},
	{Set_Int_InputMode,0x0046}
};

const uint8 PM_Ver_Adress_Rte[VERSION_NUM][ADRESS_NUMBER] =
{
		{1,2,3,14,15,16,17,18,19,20,21}, //VERSION_CN
		{1,2,3,4,5,6,7,8,9,10,11,12,13},  //VERSION_EU
		{1,7,8,9,10,11},  //VERSION_100D
		{1,2,3,4,5,6},  //VERSION_FT
		{0,0,0,0,0,0,0,0,0,0,0}, //CN_YFY
		{22,23,24,25,26,27}  //VERSION_100D_YL

};
const uint8_t PM_Init_Group_Num[VERSION_NUM][ADRESS_NUMBER] =
{
		{1,1,1,2,3,4,5,5,5,6,6,0,0},  //VERSION_CN
		{1,1,1,1,1,2,3,3,3,3,3,4,4},  //VERSION_EU
		{1,2,3,4,5,6,0,0,0,0,0,0,0},  //VERSION_100D
		{1,1,2,2,3,3,0,0,0,0,0,0,0},  //VERSION_FT
		{1,1,1,2,3,4,5,5,5,6,6,0,0},  //VERSION_CN_YFY
		{1,2,3,4,5,6,0,0,0,0,0,0,0},  //VERSION_100D_YL
};
//状态机输入变量
typedef struct
{
	float dcdc_req_V[SIDE_NUM];
	float dcdc_req_I[SIDE_NUM];
	uint32 dcdc_req_onoff[SIDE_NUM];
	float dcdc_config_I[SIDE_NUM];

}PM_Input_Struct;
PM_Input_Struct PM_WorkInput;

typedef struct
{
	uint8_t dcdc_can_error[ADRESS_NUMBER];
	uint8_t dcdc_rec_error[ADRESS_NUMBER];
	uint8_t dcdc_pwr_error[3];
	uint8_t dcdc_BHM_Vlt_error[2];
	uint8_t dcdc_BCP_Vlt_error[2];
	uint8_t dcdc_BCL_Vlt_error[2];
	uint8_t dcdc_PackVolt_v_error;
	uint8_t dcdc_req_curt_error[ADRESS_NUMBER];
	uint8_t dcdc_out_volt_error[ADRESS_NUMBER];
	uint8_t dcdc_out_curt_error[ADRESS_NUMBER];
	uint8_t dcdc_set_volt_error[ADRESS_NUMBER];
	uint8_t dcdc_set_curt_error[ADRESS_NUMBER];
	uint8_t dcdc_set_onoff_error[ADRESS_NUMBER];
}str_error_code;
str_error_code Error_Code;

//输出变量
uint16_t PM_DCDCINVolt_V[SIDE_NUM];
uint8_t PM_DCDCINVoltVld_flg[SIDE_NUM];
uint8_t PM_DCDCOUTVoltVld_flg[SIDE_NUM];

uint16_t PM_DCDCOutputVolt_V[15] = {0};
uint16_t PM_DCDCCurrent_A[15 ]= {0};
uint16_t PM_ACDCOutputVolt_V[2] = {0};
uint16_t PM_ACDCCurrent_A[2] = {0};

//故障码新增变量
uint8 errcode_curt_flag[SIDE_NUM];
//文件内声明
void SendIntDataByAdress(uint8_t adress_par, uint8 first_par,register_enu reg_par, uint32_t number_par);
void SendFloatDataByAdress(uint8_t adress_par,uint8 first_par, register_enu reg_par, float number_par);
void dcdc_main();

#ifndef WorkModule
void PM_debug_data_rec(uint32 id,uint8* data)
{
	if(id == PM_DEBUG_REC_ID)
	{
		debug_switch = 1;
		debugdata[0] = data[0];
		debugdata[1] = data[1];
		debugdata[2] = data[2];
		debugdata[3] = data[3];
		debugdata[4] = data[4];
		debugdata[5] = data[5];
		debugdata[6] = data[6];
		debugdata[7] = data[7];
	}
}
void PM_debug_interface()
{
	uint32 debug_test = 0;
	if(debug_switch == 1)
	{
		debug_switch = 0;
		switch(debugdata[0])
		{
			case 0:  //电压
				debug_test = (debugdata[4] <<24) +
													(debugdata[5] <<16) +
													(debugdata[6] <<8) +
													(debugdata[7] <<0);
				break;
			case 1:  //电流
				debug_test = (debugdata[4] <<24) +
						(debugdata[5] <<16) +
						(debugdata[6] <<8) +
						(debugdata[7] <<0);

				break;

				break;

		}
	}
}
#endif
void Version_Control()
{

#ifdef WorkModule
	//GeEBSW_AFCProductType_enum_1 = get_GeEBSW_AFCProductType_enum();
	GeEBSW_AFCProductType_enum_1 = 0;
#endif
	switch(GeEBSW_AFCProductType_enum_1)
	{
		case LH_EU:
			PM_VERSION = VERSION_FT;
			break;
		case AH_EU:
			PM_VERSION = VERSION_EU;
			break;
		case AH_CN:
			PM_VERSION = VERSION_CN;
			break;
		case D100:
			PM_VERSION = VERSION_100D;
			break;
		case YFY_CN:
			PM_VERSION = VERSION_CN_YFY;
			break;
		case D100_YL:
			PM_VERSION = VERSION_100D_YL;
			break;

	}
	if(PM_VERSION == VERSION_CN)
	{
		SideStart[0] = 0;
		SideStart[1] = 6;
		SideStart[2] = 9;
		SideStart[3] = 10;

		SideEnd[0] = 5;
		SideEnd[1] = 8;
		SideEnd[2] = 9;
		SideEnd[3] = 10;

		SideLength[0] = 6;
		SideLength[1] = 3;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0002;
		PM_Reg_Stru_Array[Get_Float_In_liq_T].RegNum =  0xffff;
		PM_Reg_Stru_Array[Get_Float_Out_liq_T].RegNum =  0xffff;
		FirstByte_GetData = 0x10;
		DCDC_Rated_Current = 27;
		DC_SINGLE_MODULE_LIMIT = 50;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 11;
	}
	else if(PM_VERSION == VERSION_EU)
	{
		SideStart[0] = 0;
		SideStart[1] = 6;
		SideStart[2] = 11;
		SideStart[3] = 12;

		SideEnd[0] = 5;
		SideEnd[1] = 10;
		SideEnd[2] = 11;
		SideEnd[3] = 12;

		SideLength[0] = 6;
		SideLength[1] = 5;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0002;
		PM_Reg_Stru_Array[Get_Float_In_liq_T].RegNum =  0xffff;
		PM_Reg_Stru_Array[Get_Float_Out_liq_T].RegNum =  0xffff;
		FirstByte_GetData = 0x10;
		DCDC_Rated_Current = 27;
		DC_SINGLE_MODULE_LIMIT = 50;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 13;
	}
	else if(PM_VERSION == VERSION_100D)
	{
		SideStart[0] = 0;
		SideStart[1] = 2;
		SideStart[2] = 4;
		SideStart[3] = 5;

		SideEnd[0] = 1;
		SideEnd[1] = 3;
		SideEnd[2] = 4;
		SideEnd[3] = 5;

		SideLength[0] = 2;
		SideLength[1] = 2;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0007;
		PM_Reg_Stru_Array[Get_Float_In_liq_T].RegNum =  0xffff;
		PM_Reg_Stru_Array[Get_Float_Out_liq_T].RegNum =  0xffff;
		FirstByte_GetData = 0x03;
		DCDC_Rated_Current = 26;
		DC_SINGLE_MODULE_LIMIT = 50;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 6;
	}
	else if(PM_VERSION == VERSION_FT)
	{
		SideStart[0] = 0;
		SideStart[1] = 2;
		SideStart[2] = 4;
		SideStart[3] = 5;

		SideEnd[0] = 1;
		SideEnd[1] = 3;
		SideEnd[2] = 4;
		SideEnd[3] = 5;

		SideLength[0] = 2;
		SideLength[1] = 2;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0002;
		FirstByte_GetData = 0x10;
		DCDC_Rated_Current = 1;
		DC_SINGLE_MODULE_LIMIT = 100;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 6;
	}
	else if(PM_VERSION == VERSION_CN_YFY)
	{
		SideStart[0] = 0;
		SideStart[1] = 6;
		SideStart[2] = 9;
		SideStart[3] = 10;

		SideEnd[0] = 5;
		SideEnd[1] = 8;
		SideEnd[2] = 9;
		SideEnd[3] = 10;

		SideLength[0] = 6;
		SideLength[1] = 3;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0007;
		PM_Reg_Stru_Array[Get_Float_In_liq_T].RegNum =  0xffff;
		PM_Reg_Stru_Array[Get_Float_Out_liq_T].RegNum =  0xffff;
		FirstByte_GetData = 0x03;
		DCDC_Rated_Current = 26;
		DC_SINGLE_MODULE_LIMIT = 50;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 11;
	}
	else if(PM_VERSION == VERSION_100D_YL)
	{
		SideStart[0] = 0;
		SideStart[1] = 2;
		SideStart[2] = 4;
		SideStart[3] = 5;

		SideEnd[0] = 1;
		SideEnd[1] = 3;
		SideEnd[2] = 4;
		SideEnd[3] = 5;

		SideLength[0] = 2;
		SideLength[1] = 2;
		SideLength[2] = 1;
		SideLength[3] = 1;

		PM_Reg_Stru_Array[Get_Float_OutPutCurrent].RegNum =  0x0002;
		PM_Reg_Stru_Array[Get_Float_In_liq_T].RegNum =  0xffff;
		PM_Reg_Stru_Array[Get_Float_Out_liq_T].RegNum =  0xffff;
		FirstByte_GetData = 0x10;
		DCDC_Rated_Current = 27;
		DC_SINGLE_MODULE_LIMIT = 50;
		AC_SINGLE_MODULE_LIMIT = 50;
		Active_Num = 6;
	}
}
void ClearRecError(uint8_t side_par, register_enu reg_par)
{
	uint8_t i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		PM_RecError[i][reg_par] = 1; //如果有一台设备返回异常，则记录结果为异常
	}
}

uint8_t GetSideByAdress(uint8_t adress_par)
{
	uint8_t side_par = 0;

	for(side_par = 0;side_par < SIDE_NUM;side_par++)
	{
		if((adress_par >= SideStart[side_par]) && (adress_par <= SideEnd[side_par]))
		{
			return side_par;
		}
	}
}
//将一个浮点数转换成4字节数
uint32_t FloatToInt(float float_par)
{
	uint32_t value = 0;
	//memcpy_s(&value, 4, &float_par, sizeof(float));
	unsigned int value1 = 0;
	float* temp1 = (&float_par);

	value1 = (int)temp1;
	value = *((unsigned int*)value1);

	return value;
}

float IntToFloat(unsigned int int_par)
{
	float value = 0;
	int value1 = 0;
	unsigned int* temp1 = (&int_par);

	value1 = (int)temp1;
	value = *((float*)value1);

	return value;

}

register_enu GetRegNameByNum(uint16_t reg_num_par)
{
	uint8_t i = 0;
	for (i = 0; i < Reg_MaxValue; i++)
	{
		if (PM_Reg_Stru_Array[i].RegNum == reg_num_par)
		{
			return PM_Reg_Stru_Array[i].RegName;
		}
	}
	return i;
}

uint16_t GetRegNumByName(register_enu reg_name_par)
{
	uint8_t i = 0;
	uint16_t value_return = 0;

	for (i = 0; i < Reg_MaxValue; i++)
	{
		if (PM_Reg_Stru_Array[i].RegName == reg_name_par)
		{
			value_return = PM_Reg_Stru_Array[i].RegNum;
		}
	}
	return value_return;
}

void SetRecFlag(uint8_t adress_par)
{
	PM_RecFlag[adress_par] = 1;
}
//Online超时检测
uint8_t CheckOnline(uint8_t side_par)
{
	uint8_t boolonline = 1;  //整组是否在线标志
	uint8_t i = 0;

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		if (PM_DCDCTimeOut_flg[i] == 1)
		{
			boolonline = 0;  //当有任意一台设备离线时，则判定整租离线
			break;
		}
	}
	return boolonline;
}
//在TIMEOUT为false时，该函数值有效
uint8_t RecState(uint8_t side_par, register_enu reg_par)
{
	uint8_t value_return = 0;
	int i = 0;
	if (PM_DCDCOnline_flg[side_par] == 0)
	{
		return 1;  //超时，则直接返回异常
	}

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		value_return |= PM_RecError[i][reg_par];  //如果有一台设备返回异常，则记录结果为异常
	}
	return value_return;
}

void SetNormalFlag(uint8_t side_par)
{
	uint8_t i = 0;

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		PM_NormalInfo_flg[i] = 1;
	}
}

void ClearNormalFlag(uint8_t side_par)
{
	uint8_t i = 0;

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		PM_NormalInfo_flg[i] = 0;
	}
}

void test_send_fun(uint8_t adress_par)
{
	static uint8 life_fra = 0;
	uint8_t data[8];

	if(life_fra < 255)
	{
		life_fra++;
	}
	else
	{
		life_fra = 0;
	}
	data[0] = life_fra;
//	data[1] = PM_DCDCStatus[0];
//	data[2] = PM_DCDCStatus[1];
//	data[3] = PM_DCDCStatus[2];
//	data[4] = PM_DCDCStatus[3];
//	data[5] = ((test_send_cnt[adress_par][1] >> 0)& 0xff);
//	data[6] = ((test_send_cnt[adress_par][2] >> 8)& 0xff);
//	data[7] = ((test_send_cnt[adress_par][2] >> 0)& 0xff);

	DCDCMessage_CanSend(0x774,data);
}
void dcdc_msg_fun10ms()
{
	static uint8_t name_count = 0;
	uint8_t adress_par = 0;
	uint8_t side_par = 0;
	static uint8_t test_tmr_cnt = 0;
	static uint8_t test_adress_cnt = 0;

#ifndef WorkModule
	PM_debug_interface();
	// test task
	if(test_tmr_cnt < 9)
	{
		test_tmr_cnt++;
	}
	else
	{
		test_tmr_cnt = 0;
		if(test_adress_cnt < (ADRESS_NUMBER-1))
		{
			test_adress_cnt ++;
		}
		else
		{
			test_adress_cnt = 0;
		}
		test_send_fun(test_adress_cnt);
	}
#endif
	//按地址遍历任务
	for(adress_par = 0;adress_par < ADRESS_NUMBER;adress_par++)
	{
		//更新timeout值
		PM_DCDCTimeOut_flg[adress_par] = (!PM_Online_flg[adress_par]);
		//
		if (RecErrorCount[adress_par][name_count] > REC_ERROR_TIMEOUT_TIME)
		{
			PM_RecError[adress_par][name_count] = 1;
		}
		else
		{
			RecErrorCount[adress_par][name_count]++;
		}

		//接收报文
		if (PM_RecFlag[adress_par] == 1)
		{
			RecManage(adress_par);
			PM_RecFlag[adress_par] = 0;
		}
	}
	//按分组遍历任务
	for(side_par = 0;side_par < SIDE_NUM;side_par++)
	{
		PM_DCDCOnline_flg[side_par] = CheckOnline(side_par);
	}
	if(name_count < Reg_MaxValue)
	{
		name_count++;
	}
	else
	{
		name_count = 0;
	}
}

void DCDCTimeTask100ms()
{
//	uint8_t adress_count = 0;
//	uint8_t side_count = 0;
//	uint8_t setgroup_count = 0;
//	static uint16_t time_cnt[SIDE_NUM] = {0};
//	static uint16_t acdcchargetocar_cnt[2]  = {0};
//
//	for (side_count = 0; side_count < SIDE_NUM; side_count++)
//	{
//		time_cnt[side_count]++;
//		if (time_cnt[side_count] > 10)
//		{
//			time_cnt[side_count] = 0;
//		}
//
//		if((time_cnt[side_count] == 0)
//		|| (time_cnt[side_count] == 3))
//		{
//			SetVoltBySide(side_count);
//		}
//		else if((time_cnt[side_count] == 1)
//			|| (time_cnt[side_count] == 4))
//		{
//			SetCurrentBySide(side_count);
//		}
//		else if((time_cnt[side_count] == 2)
//			|| (time_cnt[side_count] == 5))
//		{
//			SetOnoffBySide(side_count);
//		}
//		else if(time_cnt[side_count] == 6)
//		{
//			GetOutpurVoltBySide(side_count);
//		}
//		else if(time_cnt[side_count] == 7)
//		{
//			GetOutpurCurrentBySide(side_count);
//		}
//		else if(time_cnt[side_count] == 8)
//		{
//			GetInputVoltBySide(side_count);
//		}
//		else if(time_cnt[side_count] == 9)
//		{
//			GetEnvirTempBySide(side_count);
//		}
//		else if(time_cnt[side_count] == 10)
//		{
//			GetAlarmBySide(side_count);
//		}
//	}
	dcdc_main();
	dcdc_error_code_fun();
}

void RecManage(uint8_t adress_par)
{
	uint16_t reg_num = 0;
	uint32_t int_data = 0;
	uint8_t reg_name = 0;
	uint8_t side_par = 0;
	uint8 rte_num = 0;

	uint8_t Rx_1 = 0;
	uint8_t Rx_2 = 0;
	uint8_t Rx_3 = 0;
	uint8_t Rx_4 = 0;
	uint8_t Rx_5 = 0;
	uint8_t Rx_6 = 0;
	uint8_t Rx_7 = 0;
	uint8_t Rx_8 = 0;

	side_par = GetSideByAdress(adress_par);
	switch (PM_Ver_Adress_Rte[PM_VERSION][adress_par])
	{
	case 1:
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame1_Rx_DCDCModuleSignal1_Rx_8(&Rx_8);
		break;

	case 2:
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame2_Rx_DCDCModuleSignal2_Rx_8(&Rx_8);
		break;

	case 3:
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame3_Rx_DCDCModuleSignal3_Rx_8(&Rx_8);
		break;

	case 4:
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame4_Rx_DCDCModuleSignal4_Rx_8(&Rx_8);
		break;

	case 5:
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame5_Rx_DCDCModuleSignal5_Rx_8(&Rx_8);
		break;

	case 6:
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame6_Rx_DCDCModuleSignal6_Rx_8(&Rx_8);
		break;

	case 7:
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame7_Rx_DCDCModuleSignal7_Rx_8(&Rx_8);
		break;

	case 8:
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame8_Rx_DCDCModuleSignal8_Rx_8(&Rx_8);
		break;

	case 9:
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame9_Rx_DCDCModuleSignal9_Rx_8(&Rx_8);
		break;

	case 10:
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame10_Rx_DCDCModuleSignal10_Rx_8(&Rx_8);
		break;

	case 11:
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_1(&Rx_1);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_2(&Rx_2);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_3(&Rx_3);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_4(&Rx_4);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_5(&Rx_5);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_6(&Rx_6);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_7(&Rx_7);
		Rte_Read_DCDCModuleFrame11_Rx_DCDCModuleSignal11_Rx_8(&Rx_8);
		break;
	}
	if ((Rx_1 + Rx_2 + Rx_3 + Rx_4 + Rx_5 + Rx_6 + Rx_7 + Rx_8) == 0)
	{
		return;  //如果全为0，则报文无效
	}
	else
	{
		//Timeout清零
	}
	reg_num = (Rx_3 << 8) + Rx_4;
	reg_name = GetRegNameByNum(reg_num);

	//发送标志为1，才进行报文解析
	//if (PM_SendFlag[adress_par][reg_name] == 1)
	{
		if (Rx_2 != 0xF0)  //设置错误
		{
			PM_RecError[adress_par][reg_name] = 1;
			PM_RecError[adress_par][reg_name] = 0;
		}
		else
		{
			PM_RecError[adress_par][reg_name] = 0;
			int_data = ((Rx_5 << 24) + (Rx_6 << 16) + (Rx_7 << 8) + (Rx_8 << 0));
			switch (reg_name)
			{
				case Get_Float_OutPutVoltage:
					PM_RecVolt[adress_par] = IntToFloat(int_data);
					break;

				case Get_Float_OutPutCurrent:
					PM_RecCurrent[adress_par] = IntToFloat(int_data);
					break;

				case Get_Float_InputDCVoltage:
					PM_DCDCInputVoltByAdress[adress_par] = IntToFloat(int_data);
					break;

				case Get_Int_Alarm:
					PM_Module_Alarm[adress_par] = int_data;
					break;

				case Get_Float_EnvirTemp:
					PM_DCDCTemperature_T[adress_par] = IntToFloat(int_data);
					break;

				case Get_Float_In_liq_T:
					PM_In_liq_T[adress_par] = IntToFloat(int_data);
					break;

				case Get_Float_Out_liq_T:
					PM_Out_liq_T[adress_par] = IntToFloat(int_data);
					break;

				case Set_Int_Group:
					PM_RecError[adress_par][reg_name] = 0;
					RecErrorCount[adress_par][reg_name] = 0;
					break;

				case Set_Int_InputMode:
					PM_RecError[adress_par][reg_name] = 0;
					RecErrorCount[adress_par][reg_name] = 0;
					break;

				case Set_Float_OutPutVoltage:
					PM_RecError[adress_par][reg_name] = 0;
					RecErrorCount[adress_par][reg_name] = 0;
					break;

				case Set_Float_LimitCurrent:
					PM_RecError[adress_par][reg_name] = 0;
					RecErrorCount[adress_par][reg_name] = 0;

					break;

				case Set_Int_OnOff:
					PM_RecError[adress_par][reg_name] = 0;
					RecErrorCount[adress_par][reg_name] = 0;

					break;

			}
		}
	}
}
void SendIntDataByAdress(uint8_t adress_par, uint8 first_par,register_enu reg_par, uint32_t number_par)
{
	uint8_t data[8] = { 0,0,0,0,0,0,0,0 };
	uint8_t i = 0;
	uint16_t reg_value = 0;

	reg_value = PM_Reg_Stru_Array[reg_par].RegNum;

	data[0] = first_par;
	if((PM_VERSION == VERSION_CN_YFY) ||(PM_VERSION == VERSION_100D))
	{
		data[1] = 0xF0;
	}
	else
	{
		data[1] = 0x00;
	}
	data[2] = (uint8_t)((reg_value >> 8) & 0xff); //数据高位在前
	data[3] = (uint8_t)((reg_value >> 0) & 0xff);
	data[4] = (uint8_t)((number_par >> 24) & 0xff);
	data[5] = (uint8_t)((number_par >> 16) & 0xff);
	data[6] = (uint8_t)((number_par >> 8) & 0xff);
	data[7] = (uint8_t)((number_par >> 0) & 0xff);

	for (i = 0; i < 8; i++)
	{
		PM_SendData[adress_par - 1][i] = data[i];
	}
}
void SendFloatDataByAdress(uint8_t adress_par,uint8 first_par, register_enu reg_par, float number_par)
{
	uint32_t number = 0;
	number = FloatToInt(number_par);
	SendIntDataByAdress(adress_par, first_par,reg_par, number);
}

void ClearSendData()
{
	uint8_t i = 0;
	uint8_t adress_par;
	for(adress_par = 0;adress_par < ADRESS_NUMBER;adress_par++)
	{
		for (i = 0; i < 8; i++)
		{
			PM_SendData[adress_par][i] = 0;
		}
	}
}

void SetVoltBySide(uint8_t side_par)
{
	float temp_volt = (float)PM_WorkInput.dcdc_req_V[side_par];
	uint8_t i = 0;

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendFloatDataByAdress((i + 1), FirstByte_SetData ,Set_Float_OutPutVoltage, temp_volt);  //为整边设置电压
	}
}
void SetCurrentBySide(uint8_t side_par)
{
	float temp_volt = (float)PM_WorkInput.dcdc_config_I[side_par];
	int i = 0;

	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendFloatDataByAdress((i + 1), FirstByte_SetData ,Set_Float_LimitCurrent, temp_volt);  //为整边设置电流
	}
}
void SetOnoffBySide(uint8_t side_par)
{
	uint32 temp_volt = (float)PM_WorkInput.dcdc_req_onoff[side_par];
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_SetData ,Set_Int_OnOff, temp_volt);  //为整边设置开关机
	}
}
void GetOutputVoltBySide(uint8_t side_par)
{
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_GetData ,Get_Float_OutPutVoltage, 0);
	}
}
void GetOutputCurrentBySide(uint8_t side_par)
{
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_GetData ,Get_Float_OutPutCurrent, 0);
	}
}
void GetInputVoltBySide(uint8_t side_par)
{
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_GetData ,Get_Float_InputDCVoltage, 0);
	}
}
void GetEnvirTempBySide(uint8_t side_par)
{
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_GetData ,Get_Float_EnvirTemp, 0);
	}
}
void GetAlarmBySide(uint8_t side_par)
{
	int i = 0;
	for (i = SideStart[side_par]; i <= SideEnd[side_par]; i++)
	{
		SendIntDataByAdress((i + 1), FirstByte_GetData ,Get_Int_Alarm, 0);
	}
}

void SetVolt()
{
	uint8 side_par;
	uint8 adress_par;
	float temp_;

	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		side_par = GetSideByAdress(adress_par);
		temp_ = (float)PM_WorkInput.dcdc_req_V[side_par];
		SendFloatDataByAdress((adress_par + 1), FirstByte_SetData ,Set_Float_OutPutVoltage, temp_);  //为整边设置电压
	}
}
void SetCurrent()
{
	uint8 side_par;
	uint8 adress_par;
	float temp_;

	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		side_par = GetSideByAdress(adress_par);
		temp_ = (float)PM_WorkInput.dcdc_config_I[side_par];
		SendFloatDataByAdress((adress_par + 1), FirstByte_SetData ,Set_Float_LimitCurrent, temp_);  //为整边设置电压
	}
}
void SetOnoff()
{
	uint8 side_par;
	uint8 adress_par;
	uint32 temp_;

	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		side_par = GetSideByAdress(adress_par);
		temp_ = (float)PM_WorkInput.dcdc_req_onoff[side_par];
		SendIntDataByAdress((adress_par + 1), FirstByte_SetData ,Set_Int_OnOff, temp_);  //为整边设置电压
	}
}
void GetOutputVolt()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_OutPutVoltage, 0);
	}
}
void GetOutputCurrent()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_OutPutCurrent, 0);
	}
}
void GetInputVolt()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_InputDCVoltage, 0);
	}
}
void GetEnvirTemp()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_EnvirTemp, 0);
	}
}
void GetAlarm_dcdc()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Int_Alarm, 0);
	}
}
void Get_In_Liq_T()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_In_liq_T, 0);
	}
}
void Get_Out_Liq_T()
{
	int adress_par = 0;
	for (adress_par = 0; adress_par <= Active_Num; adress_par++)
	{
		SendIntDataByAdress((adress_par + 1), FirstByte_GetData ,Get_Float_Out_liq_T, 0);
	}
}
float DCDC_Get_Req_I(uint8 side_par)
{
	float input = 0;
	float value = 0;

	switch(side_par)
	{
		case 0:
			input = PM_WorkInput.dcdc_req_I[0];
			break;

		case 1:
			input = PM_WorkInput.dcdc_req_I[1];
				break;

		case 2:
			input = PM_WorkInput.dcdc_req_I[2];
				break;

		case 3:
			input = PM_WorkInput.dcdc_req_I[3];
				break;
	}
	value = input/DCDC_Rated_Current;
	value = value/SideLength[side_par];

	return value;

}
//接口转换
void InterfaceTrans()
{
	uint8_t count = 0;
	uint16_t _temp = 0;
	uint8 timeout_value = 0;
#ifdef WorkModule
	//外部输入变量转换
	PM_WorkInput.dcdc_req_V[0] = get_GcEDCC_DCDCAOutVoltReq_V();
	PM_WorkInput.dcdc_req_V[1] = get_GcEDCC_DCDCBOutVoltReq_V();
	PM_WorkInput.dcdc_req_V[2] = get_GcEACC_ACDCAOutVoltReq_V();
	PM_WorkInput.dcdc_req_V[3] = get_GcEACC_ACDCBOutVoltReq_V();

	PM_WorkInput.dcdc_req_I[0] = get_GcEDCC_DCDCAOutCurrReq_A();
	PM_WorkInput.dcdc_req_I[1] = get_GcEDCC_DCDCBOutCurrReq_A();
	PM_WorkInput.dcdc_req_I[2] = get_GcEACC_ACDCAOutCurrReq_A();
	PM_WorkInput.dcdc_req_I[3] = get_GcEACC_ACDCBOutCurrReq_A();


	PM_WorkInput.dcdc_req_onoff[0] = get_GbEDCC_DCDCAPwrCmd_flg()?DCDC_SWITCH_ON:DCDC_SWITCH_OFF;
	PM_WorkInput.dcdc_req_onoff[1] = get_GbEDCC_DCDCBPwrCmd_flg()?DCDC_SWITCH_ON:DCDC_SWITCH_OFF;
	PM_WorkInput.dcdc_req_onoff[2] = get_GbEACC_ACDCAPwrCmd_flg()?DCDC_SWITCH_ON:DCDC_SWITCH_OFF;
	PM_WorkInput.dcdc_req_onoff[3] = get_GbEACC_ACDCBPwrCmd_flg()?DCDC_SWITCH_ON:DCDC_SWITCH_OFF;

	PM_WorkInput.dcdc_config_I[0] = DCDC_Get_Req_I(0);
	PM_WorkInput.dcdc_config_I[1] = DCDC_Get_Req_I(1);
	PM_WorkInput.dcdc_config_I[2] = DCDC_Get_Req_I(2);
	PM_WorkInput.dcdc_config_I[3] = DCDC_Get_Req_I(3);
#else

#endif
	//输出变量
	for(count = 0;count < (Active_Num - 2);count++)
	{
		PM_DCDCOutputVolt_V[count] = PM_RecVolt[count];
		PM_DCDCCurrent_A[count] = (PM_RecCurrent[count] * 10);
	}
	PM_ACDCOutputVolt_V[0] = PM_RecVolt[Active_Num - 2];
	PM_ACDCOutputVolt_V[1] = PM_RecVolt[Active_Num - 1];

	PM_ACDCCurrent_A[0] = (PM_RecCurrent[Active_Num - 2] * 10);
	PM_ACDCCurrent_A[1] = (PM_RecCurrent[Active_Num - 1] * 10);

	//状态机输出量处理
	PM_DCDCINVolt_V[SIDE_LEFT] = PM_DCDCInputVoltByAdress[SideStart[SIDE_LEFT]];
	PM_DCDCINVolt_V[SIDE_RIGHT] = PM_DCDCInputVoltByAdress[SideStart[SIDE_RIGHT]];
	PM_DCDCINVolt_V[SIDE_ACDC1] = PM_DCDCInputVoltByAdress[SideStart[SIDE_ACDC1]];
	PM_DCDCINVolt_V[SIDE_ACDC2] = PM_DCDCInputVoltByAdress[SideStart[SIDE_ACDC2]];

	//输出变量

	//水冷温度
	Rte_Write_DCDC_DCDCAWaterTemp_C(PM_In_liq_T[SideStart[SIDE_LEFT]]);
	Rte_Write_DCDC_DCDCBWaterTemp_C(PM_In_liq_T[SideStart[SIDE_RIGHT]]);
	Rte_Write_ACDC_ACDCAWaterTemp_C(PM_In_liq_T[Active_Num - 2]);
	Rte_Write_ACDC_ACDCBWaterTemp_C(PM_In_liq_T[Active_Num - 1]);

	Rte_Write_DCDC_DCDCAOutWaterTemp_C(PM_Out_liq_T[SIDE_LEFT]);
	Rte_Write_DCDC_DCDCBOutWaterTemp_C(PM_Out_liq_T[SIDE_RIGHT]);
	Rte_Write_ACDC_ACDCAOutWaterTemp_C(PM_Out_liq_T[Active_Num - 2]);
	Rte_Write_ACDC_ACDCBOutWaterTemp_C(PM_Out_liq_T[Active_Num - 1]);

	//输出电压
	Rte_Write_DCDC_DCDCAOutVolt_V(PM_RecVolt[SideStart[SIDE_LEFT]]);
	Rte_Write_DCDC_DCDCBOutVolt_V(PM_RecVolt[SideStart[SIDE_RIGHT]]);
	Rte_Write_ACDC_ACDCAOutVolt_V(PM_RecVolt[Active_Num - 2]);
	Rte_Write_ACDC_ACDCBOutVolt_V(PM_RecVolt[Active_Num - 1]);

	//输出电流
	Rte_Write_ACDC_ACDCAOutCurr_A(PM_RecCurrent[Active_Num - 2]);
	Rte_Write_ACDC_ACDCBOutCurr_A(PM_RecCurrent[Active_Num - 1]);
	//输出电压、电流
	for(count = 0;count < 15;count++)
	{
		Rte_Write_DCDC_DCDCCurrent_A(PM_DCDCCurrent_A);
		Rte_Write_DCDC_DCDCOutputVolt_V(PM_DCDCOutputVolt_V);
	}
	Rte_Write_ACDC_ACDCOutputVolt_V(PM_ACDCOutputVolt_V);
	Rte_Write_ACDC_ACDCCurrent_A(PM_ACDCCurrent_A);

	//输入电压
	Rte_Write_DCDC_DCDCAInVolt_V(PM_DCDCINVolt_V[SIDE_LEFT]);
	Rte_Write_DCDC_DCDCBInVolt_V(PM_DCDCINVolt_V[SIDE_RIGHT]);
	//Timeout
	timeout_value = 0;
	for(count = SideStart[SIDE_LEFT];count < SideEnd[SIDE_LEFT];count++)
	{
		timeout_value |= PM_DCDCTimeOut_flg[count];
	}
	Rte_Write_CBK_DCDCATimeOut_flg(timeout_value);

	timeout_value = 0;
	for(count = SideStart[SIDE_RIGHT];count < SideEnd[SIDE_RIGHT];count++)
	{
		timeout_value |= PM_DCDCTimeOut_flg[count];
	}
	Rte_Write_CBK_DCDCBTimeOut_flg(timeout_value);

	Rte_Write_CBK_ACDCATimeOut_flg(PM_DCDCTimeOut_flg[Active_Num - 2]);
	Rte_Write_CBK_ACDCBTimeOut_flg(PM_DCDCTimeOut_flg[Active_Num - 1]);
}


void DCDCTimeTask10ms()
{
	uint8_t side_count = 0;
	uint8_t adress_count = 0;

	dcdc_init();
	InterfaceTrans();  //输入输出变量转换
	dcdc_msg_fun10ms();

	for (side_count = 0; side_count < SIDE_NUM; side_count++)
	{
		//更新在线标志
		PM_DCDCOnline_flg[side_count] = CheckOnline(side_count);
	}
}

//主任务
void dcdc_init()
{
	if(dcdc_init_flag ==1)
	{
		Version_Control();
		dcdc_init_flag = 0;
	}
}
void DCDCMessage_CanSend(uint32_t id, uint8_t * data)
{

	Can_PduType can_pdu;

	can_pdu.id = id;
	can_pdu.length = 8;
	can_pdu.sdu = data;
	can_pdu.swPduHandle = 1;
	switch(id)
	{
		case 0x829f3ff0 :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_1, &can_pdu);
		break;

		case 0x829601F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_2, &can_pdu);
		break;

		case 0x829602F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_3, &can_pdu);
		break;

		case 0x829603F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_4, &can_pdu);
		break;

		case 0x829604F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_5, &can_pdu);
		break;

		case 0x829605F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_6, &can_pdu);
		break;

		case 0x829606F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_7, &can_pdu);
		break;

		case 0x829607F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_8, &can_pdu);
		break;

		case 0x829608F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_1, &can_pdu);
		break;

		case 0x829609F0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_2, &can_pdu);
		break;

		case 0x82960aF0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_3, &can_pdu);
		break;

		case 0x82960bF0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_4, &can_pdu);
		break;

		case 0x82960cF0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_5, &can_pdu);
		break;

		case 0x82960dF0  :     //Tx12
 		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_6, &can_pdu);
		break;

		case 0x774  :     //Tx12
		(void)Can_Write(CanConf_CanHardwareObject_Can_Network_CANNODE_4_Tx_Ext_MailBox_7, &can_pdu);
		break;

		default :
		break;
	}
}

//需求电压、电流、开关机信息只要发生变化，就会重置发送顺序
void dcdc_get_send_res()
{
	uint8 reset_flag = 0;
	uint8 cnt = 0;
	static float pre_volt[4] = {0};
	static float last_volt[4] = {0};
	static float pre_current[4] = {0};
	static float last_current[4] = {0};
	static uint8 pre_onoff[4] = {0};
	static uint8 last_onoff[4] = {0};

	for(cnt = 0;cnt < 4;cnt++)
	{
		if((pre_volt[cnt] != last_volt[cnt]) ||
				(pre_current[cnt] != last_current[cnt]) ||
				(pre_onoff[cnt] != last_onoff[cnt])
				)
		{
			reset_flag = 1;
		}
		else
		{

		}
	}

	if(1 == reset_flag)
	{
		dcdc_clock_reset();
		dcdc_index = 0;
	}


}
void dcdc_error_code_fun()
{
	static uint16 can_error_cnt[ADRESS_NUMBER];
	static uint16 rec_error_cnt[ADRESS_NUMBER];
	static uint16 pwr_error_cnt[3];
	static uint16 BHM_Vlt_error_cnt[2];
	static uint16 BCP_Vlt_error_cnt[2];
	static uint16 BCL_Vlt_error_cnt[2];
	static uint16 PackVolt_v_error_cnt;
	static uint16 req_curt_error_cnt[ADRESS_NUMBER];
	static uint16 out_volt_error_cnt[ADRESS_NUMBER];
	static uint16 out_curt_error_cnt[ADRESS_NUMBER];
	static uint16 set_volt_error_cnt[ADRESS_NUMBER];
	static uint16 set_curt_error_cnt[ADRESS_NUMBER];
	static uint16 set_onoff_error_cnt[ADRESS_NUMBER];

	uint8 adress_par = 0;
	uint8 side_par = 0;
	uint8 cnt = 0;

	for(adress_par = 0;adress_par < ADRESS_NUMBER;adress_par++)
	{
		side_par = GetSideByAdress(adress_par);
		//功率模块通讯异常

		//接收报文周期异常

		//功率模块需求电流异常
		if((((side_par < 2)&&(PM_WorkInput.dcdc_req_I[adress_par] > DC_SINGLE_MODULE_LIMIT))||((side_par >= 2)&&(PM_WorkInput.dcdc_req_I[adress_par] > AC_SINGLE_MODULE_LIMIT)))
				)
		{
			if(req_curt_error_cnt[adress_par] < 100)
			{
				req_curt_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_req_curt_error[adress_par] = 1;
			}

		}
		else
		{
			req_curt_error_cnt[adress_par] = 0;
			Error_Code.dcdc_req_curt_error[adress_par] = 0;
		}

		//输出电压异常
		if(((PM_RecVolt[adress_par] - PM_WorkInput.dcdc_req_V[side_par]) > 4))
		{
			if(out_volt_error_cnt[adress_par] < 10)
			{
				out_volt_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_out_volt_error[adress_par] = 1;
			}

		}
		else
		{
			out_volt_error_cnt[adress_par] = 0;
			Error_Code.dcdc_out_volt_error[adress_par] = 0;
		}
		//输出电流异常
		if(((PM_RecCurrent[adress_par] - PM_WorkInput.dcdc_req_I[adress_par]) > 1))
		{
			if(out_curt_error_cnt[adress_par] < 10)
			{
				out_curt_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_out_curt_error[adress_par] = 1;
			}

		}
		else
		{
			out_curt_error_cnt[adress_par] = 0;
			Error_Code.dcdc_out_curt_error[adress_par] = 0;
		}
		//设置电压失败
		if((PM_RecError[adress_par][Set_Float_OutPutVoltage] == 1))
		{
			if(set_volt_error_cnt[adress_par] < 20)
			{
				set_volt_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_set_volt_error[adress_par] = 1;
			}

		}
		else
		{
			set_volt_error_cnt[adress_par] = 0;
			Error_Code.dcdc_set_volt_error[adress_par] = 0;
		}
		//设置电流失败
		if((PM_RecError[adress_par][Set_Float_LimitCurrent] == 1))
		{
			if(set_curt_error_cnt[adress_par] < 20)
			{
				set_curt_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_set_curt_error[adress_par] = 1;
			}

		}
		else
		{
			set_curt_error_cnt[adress_par] = 0;
			Error_Code.dcdc_set_curt_error[adress_par] = 0;
		}
		//设置开关机失败
		if((PM_RecError[adress_par][Set_Int_OnOff] == 1))
		{
			if(set_onoff_error_cnt[adress_par] < 20)
			{
				set_onoff_error_cnt[adress_par]++;
			}
			else
			{
				Error_Code.dcdc_set_onoff_error[adress_par] = 1;
			}

		}
		else
		{
			set_onoff_error_cnt[adress_par] = 0;
			Error_Code.dcdc_set_onoff_error[adress_par] = 0;
		}
	}

//	for(side_par = 0;side_par < SIDE_NUM;side_par++)
//	{
//		//功率模块需求功率异常
//		if(side_par < 2)
//		{
//			//BHM_Vlt电压值异常
//			if(
//			    (PM_WorkInput.BHM_Vlt_flg[side_par] == 1) &&
//			    (PM_WorkInput.ISOCheckFinish_flg[side_par] == 0) &&
//			    (PM_WorkInput.BHM_Vlt[side_par] >750)
//					)
//			{
//				if(BHM_Vlt_error_cnt[side_par] < 10)
//				{
//					BHM_Vlt_error_cnt[side_par]++;
//				}
//				else
//				{
//					Error_Code.dcdc_BHM_Vlt_error[side_par] = 1;
//				}
//			}
//			else
//			{
//				BHM_Vlt_error_cnt[side_par] = 0;
//				Error_Code.dcdc_BHM_Vlt_error[side_par] = 0;
//			}
//			//BCP_Vlt电压值异常
//			if(
//			    (PM_WorkInput.BCPVlt_flg [side_par] == 1) &&
//			    (PM_WorkInput.ISOCheckFinish_flg[side_par] == 1) &&
//			    (PM_WorkInput.BCP_Vlt[side_par] >750)
//					)
//			{
//				if(BCP_Vlt_error_cnt[side_par] < 10)
//				{
//					BCP_Vlt_error_cnt[side_par]++;
//				}
//				else
//				{
//					Error_Code.dcdc_BCP_Vlt_error[side_par] = 1;
//				}
//			}
//			else
//			{
//				BCP_Vlt_error_cnt[side_par] = 0;
//				Error_Code.dcdc_BCP_Vlt_error[side_par] = 0;
//			}
//			//BCL_Vlt电压值异常
//			if(
//			    (PM_WorkInput.BCL_Vlt_flg[side_par] == 1) &&
//			    (PM_WorkInput.BCL_Vlt[side_par] >750)
//					)
//			{
//				if(BCL_Vlt_error_cnt[side_par] < 10)
//				{
//					BCL_Vlt_error_cnt[side_par]++;
//				}
//				else
//				{
//					Error_Code.dcdc_BCL_Vlt_error[side_par] = 1;
//				}
//			}
//			else
//			{
//				BCL_Vlt_error_cnt[side_par] = 0;
//				Error_Code.dcdc_BCL_Vlt_error[side_par] = 0;
//			}
//		}
//		//PackVolt_v电压值异常
//		if((PM_WorkInput.PackVoltVld_flg == 1) &&(PM_WorkInput.PackVolt_v >700))
//		{
//			if(PackVolt_v_error_cnt < 10)
//			{
//				PackVolt_v_error_cnt++;
//			}
//			else
//			{
//				Error_Code.dcdc_PackVolt_v_error = 1;
//			}
//		}
//		else
//		{
//			PackVolt_v_error_cnt = 0;
//			Error_Code.dcdc_PackVolt_v_error = 0;
//		}
//	}


	//

}

void dcdc_clock_reset()
{
	dcdc_clock_cnt[0] = 3;
	dcdc_clock_cnt[1] = 3;
	dcdc_clock_cnt[2] = 3;
	dcdc_clock_cnt[3] = 2;
	dcdc_clock_cnt[4] = 2;
	dcdc_clock_cnt[5] = 2;
	dcdc_clock_cnt[6] = 1;
	dcdc_clock_cnt[7] = 1;
	dcdc_clock_cnt[8] = 1;
	dcdc_clock_cnt[9] = 1;
}
void dcdc_main()
{
	uint8 i = 0;
	uint8 cnt_sum = 0;

	for(;dcdc_index < DCDC_SEND_NUM;dcdc_index++)
	{
		if(dcdc_clock_cnt[dcdc_index] > 0)
		{
			switch(dcdc_index)
				{
					case 0:
						SetVolt();
						break;

					case 1:
						SetCurrent();
						break;

					case 2:
						SetOnoff();
						break;

					case 3:
						GetOutputVolt();
						break;

					case 4:
						GetOutputCurrent();
						break;

					case 5:
						GetInputVolt();
						break;

					case 6:
						GetEnvirTemp();
						break;

					case 7:
						GetAlarm_dcdc();
						break;

					case 8:
						Get_In_Liq_T();
						break;

					case 9:
						Get_Out_Liq_T();
						break;
				}
			dcdc_clock_cnt[dcdc_index]--;
			dcdc_index++;
			break;
		}
		else
		{

		}
	}
	if(dcdc_index >= (DCDC_SEND_NUM-1))
	{
		dcdc_index = 0;
	}

	for(i = 0;i < DCDC_SEND_NUM;i++)
	{
		cnt_sum += dcdc_clock_cnt[i];
	}
	if(cnt_sum == 0)
	{
		dcdc_clock_reset();
	}

}

