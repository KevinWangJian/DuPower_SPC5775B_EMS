#include "Diag_SWC.h"
#include "Rte_Type.h"
#include "Rte_Asw_SWC.h"
#include "Rte_Dem_Type.h"
#include "Rte_Asw_SWC_Type.h"
#include "Eep.h"
#include "Rte_IoHwAb.h"
#include "SchM_BswM_Type.h"
#include "Rte_IoHwAb.h"
#include "Uds_Srv.h"
Std_ReturnType GlobalSnapshot_ACDC1Status_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D147_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_ACDC2Status_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D148_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_ACDCCtrCmd_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D101_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_ACDCOUTCheckIN_V(uint8* Buffer)
{
	uint32 ACDCOUTCheckIN_V=0;
	Rte_Read_SnapShot_D146_Val_Data(&ACDCOUTCheckIN_V);
	Buffer[0] = (ACDCOUTCheckIN_V>>24)&0xff;
	Buffer[1] = (ACDCOUTCheckIN_V>>16)&0xff;
	Buffer[2] = (ACDCOUTCheckIN_V>>8)&0xff;
	Buffer[3] = ACDCOUTCheckIN_V&0xff;
    return E_OK;
}
Std_ReturnType GlobalSnapshot_BCM_BothConnectState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D151_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_BCM_ConnectState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D152_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_BMSHVCtrCmd_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D103_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_CB3CheckIN_V(uint8* Buffer)
{
	Rte_Read_SnapShot_D141_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_CB5AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D128_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_CB6AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D129_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_CCU1_CCUState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D105_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_CCU2_CCUState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D106_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_DCDCCtrCmd_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D102_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_DoorConntAUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D130_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_EACB_ACChargeBatteryState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D153_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_EDC2_BatteryDisCharge2State_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D154_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_EMGSTOPAUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D131_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_EMSState_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D100_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_FUSE3RelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D140_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_FVC1CB1RelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D126_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_FVC2CB2RelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D132_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_HVNISOMeanAD_V(uint8* Buffer)
{
	uint32 HVNISOMeanAD_V=0;
	Rte_Read_SnapShot_D142_Val_Data(&HVNISOMeanAD_V);
	Buffer[0] = (HVNISOMeanAD_V>>24)&0xff;
	Buffer[1] = (HVNISOMeanAD_V>>16)&0xff;
	Buffer[2] = (HVNISOMeanAD_V>>8)&0xff;
	Buffer[3] = HVNISOMeanAD_V&0xff;
    return E_OK;
}
Std_ReturnType GlobalSnapshot_HVPISOMeanAD_V(uint8* Buffer)
{
	uint32 HVPISOMeanAD_V=0;
	Rte_Read_SnapShot_D143_Val_Data(&HVPISOMeanAD_V);
	Buffer[0] = (HVPISOMeanAD_V>>24)&0xff;
	Buffer[1] = (HVPISOMeanAD_V>>16)&0xff;
	Buffer[2] = (HVPISOMeanAD_V>>8)&0xff;
	Buffer[3] = HVPISOMeanAD_V&0xff;
    return E_OK;
}
Std_ReturnType GlobalSnapshot_HVSystemStatus_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D104_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K11K12AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D133_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K13RelayCheckIN_V(uint8* Buffer)
{
	uint32 K13RelayCheckIN_V=0;
	Rte_Read_SnapShot_D145_Val_Data(&K13RelayCheckIN_V);
	Buffer[0] = (K13RelayCheckIN_V>>24)&0xff;
	Buffer[1] = (K13RelayCheckIN_V>>16)&0xff;
	Buffer[2] = (K13RelayCheckIN_V>>8)&0xff;
	Buffer[3] = K13RelayCheckIN_V&0xff;
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K15RelayCheckIN_V(uint8* Buffer)
{
	uint32 K15RelayCheckIN_V=0;
	Rte_Read_SnapShot_D144_Val_Data(&K15RelayCheckIN_V);
	Buffer[0] = (K15RelayCheckIN_V>>24)&0xff;
	Buffer[1] = (K15RelayCheckIN_V>>16)&0xff;
	Buffer[2] = (K15RelayCheckIN_V>>8)&0xff;
	Buffer[3] = K15RelayCheckIN_V&0xff;
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K5K6AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D134_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K7K8AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D135_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_K9K10AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D136_Val_Data(Buffer);
    return E_OK;
}

Std_ReturnType GlobalSnapshot_KM1AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D137_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_KM2AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D138_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_LeftDCDCStatus_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D149_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MainNegCntStat_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D108_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MainPosCntStat_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D109_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MaxCellTemp_C(uint8* Buffer)
{
	uint16 MaxCellTemp_C=0;
	Rte_Read_SnapShot_D119_Val_Data(&MaxCellTemp_C);
	Buffer[0] = MaxCellTemp_C>>8;
	Buffer[1] = MaxCellTemp_C&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_MaxCellTemp_Numb(uint8* Buffer)
{
	Rte_Read_SnapShot_D120_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MaxClVlt_Numb(uint8* Buffer)
{
	Rte_Read_SnapShot_D116_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MaxClVlt_mV(uint8* Buffer)
{
	uint16 MaxClVlt_mV=0;
	Rte_Read_SnapShot_D115_Val_Data(&MaxClVlt_mV);
	Buffer[0] = MaxClVlt_mV>>8;
	Buffer[1] = MaxClVlt_mV&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_MinCellTemp_C(uint8* Buffer)
{
	uint16 MinCellTemp_C=0;
	Rte_Read_SnapShot_D121_Val_Data(&MinCellTemp_C);
	Buffer[0] = MinCellTemp_C>>8;
	Buffer[1] = MinCellTemp_C&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_MinCellTemp_Numb(uint8* Buffer)
{
	Rte_Read_SnapShot_D122_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MinClVlt_Numb(uint8* Buffer)
{
	Rte_Read_SnapShot_D118_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_MinClVlt_mV(uint8* Buffer)
{
	uint16 MinClVlt_mV=0;
	Rte_Read_SnapShot_D117_Val_Data(&MinClVlt_mV);
	Buffer[0] = MinClVlt_mV>>8;
	Buffer[1] = MinClVlt_mV&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_PackCurrentVld_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D111_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_PackCurrent_A(uint8* Buffer)
{
	uint16 PackCurrent_A=0;
	Rte_Read_SnapShot_D110_Val_Data(&PackCurrent_A);
	Buffer[0] = PackCurrent_A>>8;
	Buffer[1] = PackCurrent_A&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_PackVoltVld_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D113_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_PackVolt_V(uint8* Buffer)
{
	uint16 PackVolt_V=0;
	Rte_Read_SnapShot_D112_Val_Data(&PackVolt_V);
	Buffer[0] = PackVolt_V>>8;
	Buffer[1] = PackVolt_V&0xff;
	return E_OK;
}
Std_ReturnType GlobalSnapshot_QF1AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D123_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_QF2AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D124_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_QF3AUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D125_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_RealSOC_pct(uint8* Buffer)
{
	Rte_Read_SnapShot_D114_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_RightDCDCStatus_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D150_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_SmokeAlarmAUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D127_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_SupplyVoltage(uint8* Buffer)
{

    return E_OK;
}
Std_ReturnType GlobalSnapshot_TBOXStatus_enum(uint8* Buffer)
{
	Rte_Read_SnapShot_D107_Val_Data(Buffer);
    return E_OK;
}
Std_ReturnType GlobalSnapshot_WaterLevelAUXRelayStatus_flg(uint8* Buffer)
{
	Rte_Read_SnapShot_D139_Val_Data(Buffer);
    return E_OK;
}


FUNC (void, Dcm_SWC_CODE) RE_JumpToOEMBootloader // return value & FctID
(
		void
)
{

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :RE_JumpToOEMBootloader) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	Uds_JumpToBootloader();

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :RE_JumpToOEMBootloader) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}
FUNC (void, Dcm_SWC_CODE) SwcDcmEcuHardReset_func // return value & FctID
(
		void
)
{

	Std_ReturnType syncCall1;
	Std_ReturnType retWrite2;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :SwcDcmEcuHardReset_func) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

   syncCall1 = Rte_Call_RPort_EcuM_ShutdownTarget_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, ECUM_RESET_MCU);


	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */
	retWrite2 = Rte_Write_PPort_BswMArbitration_BswM_MRP_SwcModeRequest_VDP_uint16(RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_POST_RUN);

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :SwcDcmEcuHardReset_func) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

FUNC (void, Dcm_SWC_CODE) SwcDcmEcuSoftReset_func // return value & FctID
(
		void
)
{

	Std_ReturnType syncCall1;
	Std_ReturnType retWrite2;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :SwcDcmEcuSoftReset_func) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

    syncCall1 = Rte_Call_RPort_EcuM_ShutdownTarget_SelectShutdownTarget(ECUM_SHUTDOWN_TARGET_RESET, ECUM_RESET_MCU);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */
	retWrite2 = Rte_Write_PPort_BswMArbitration_BswM_MRP_SwcModeRequest_VDP_uint16(RTE_MODE_MDG_ECUM_STATE_ECUM_STATE_POST_RUN);

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :SwcDcmEcuSoftReset_func) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}
