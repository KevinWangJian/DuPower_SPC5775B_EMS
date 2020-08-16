/*
 * File: EBCR.c
 *
 * Code generated for Simulink model 'EBCR'.
 *
 * Company                        : DP
 * Author                         : Kris Lee
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 08 14:21:32 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EBCR.h"
#include "EBCR_private.h"

/* External outputs (root outports fed by signals with auto storage) */
ExtY_EBCR_T EBCR_Y;

/* Real-time model */
RT_MODEL_EBCR_T EBCR_M_;
RT_MODEL_EBCR_T *const EBCR_M = &EBCR_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_Cell_18042701_10ms_at_outport_1' */
void EBCR_BMS_Cell_18042701_10ms(void)
{
  if (CbEBCR_BMSAMaxClVltOvrSwt_flg) {
    set_GcEBCR_BMSAMaxClVlt_mV(CcEBCR_BMSAMaxClVltOvr_mV);
  } else {
    set_GcEBCR_BMSAMaxClVlt_mV((real32_T)get_GcCAN1_MaxClVlt_mV());
  }

  if (CbEBCR_BMSAMaxCellVoltNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMaxCellVoltNumb_numb(CcEBCR_BMSAMaxCellVoltNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMaxCellVoltNumb_numb(get_GcCAN1_MaxCellVoltNumb_numb());
  }

  if (CbEBCR_BMSAMaxCellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMaxCellBatNumb_numb(CcEBCR_BMSAMaxCellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMaxCellBatNumb_numb(get_GcCAN1_BMSMaxCellBatteryNumber_numb());
  }

  if (CbEBCR_BMSAMinClVltOvrSwt_flg) {
    set_GcEBCR_BMSAMinClVlt_mV(CcEBCR_BMSAMinClVltOvr_mV);
  } else {
    set_GcEBCR_BMSAMinClVlt_mV((real32_T)get_GcCAN1_MinClVlt_mV());
  }

  if (CbEBCR_BMSAMinCellVoltNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMinCellVoltNumb_numb(CcEBCR_BMSAMinCellVoltNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMinCellVoltNumb_numb(get_GcCAN1_MinCellVoltNumb_numb());
  }

  if (CbEBCR_BMSAMinCellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMinCellBatNumb_numb(CcEBCR_BMSAMinCellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMinCellBatNumb_numb(get_GcCAN1_BMSMinCellBatteryNumber_numb());
  }

  if (CbEBCR_BMSBMaxClVltOvrSwt_flg) {
    set_GcEBCR_BMSBMaxClVlt_mV(CcEBCR_BMSBMaxClVltOvr_mV);
  } else {
    set_GcEBCR_BMSBMaxClVlt_mV((real32_T)get_GcCAN3_MaxClVlt_mV());
  }

  if (CbEBCR_BMSBMaxCellVoltNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMaxCellVoltNumb_numb(CcEBCR_BMSBMaxCellVoltNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMaxCellVoltNumb_numb(get_GcCAN3_MaxCellVoltNumb_numb());
  }

  if (CbEBCR_BMSBMaxCellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMaxCellBatNumb_numb(CcEBCR_BMSBMaxCellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMaxCellBatNumb_numb(get_GcCAN3_BMSMaxCellBatteryNumber_numb());
  }

  if (CbEBCR_BMSBMinClVltOvrSwt_flg) {
    set_GcEBCR_BMSBMinClVlt_mV(CcEBCR_BMSBMinClVltOvr_mV);
  } else {
    set_GcEBCR_BMSBMinClVlt_mV((real32_T)get_GcCAN3_MinClVlt_mV());
  }

  if (CbEBCR_BMSBMinCellVoltNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMinCellVoltNumb_numb(CcEBCR_BMSBMinCellVoltNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMinCellVoltNumb_numb(get_GcCAN3_MinCellVoltNumb_numb());
  }

  if (CbEBCR_BMSBMinCellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMinCellBatNumb_numb(CcEBCR_BMSBMinCellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMinCellBatNumb_numb(get_GcCAN3_BMSMinCellBatteryNumber_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_ConntSts_18192701_10ms_at_outport_1' */
void EBCR_BMS_ConntSts_18192701_10ms(void)
{
  if (CbEBCR_BMSAPack1RechrgPosStatOvrSwt_flg) {
    set_GeEBCR_BMSAPack1RechrgPosStat_enum(CeEBCR_BMSAPack1RechrgPosStatOvr_enum);
  } else {
    set_GeEBCR_BMSAPack1RechrgPosStat_enum(get_GeCAN1_Pack1RechrPosState_enum());
  }

  if (CbEBCR_BMSAPack1RechrgNegStatOvrSwt_flg) {
    set_GeEBCR_BMSAPack1RechrgNegStat_enum(CeEBCR_BMSAPack1RechrgNegStatOvr_enum);
  } else {
    set_GeEBCR_BMSAPack1RechrgNegStat_enum(get_GeCAN1_Pack1RechrNegState_enum());
  }

  if (CbEBCR_BMSBPack1RechrgPosStatOvrSwt_flg) {
    set_GeEBCR_BMSBPack1RechrgPosStat_enum(CeEBCR_BMSBPack1RechrgPosStatOvr_enum);
  } else {
    set_GeEBCR_BMSBPack1RechrgPosStat_enum(get_GeCAN3_Pack1RechrPosState_enum());
  }

  if (CbEBCR_BMSBPack1RechrgNegStatOvrSwt_flg) {
    set_GeEBCR_BMSBPack1RechrgNegStat_enum(CeEBCR_BMSBPack1RechrgNegStatOvr_enum);
  } else {
    set_GeEBCR_BMSBPack1RechrgNegStat_enum(get_GeCAN3_Pack1RechrNegState_enum());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_DTC_18AA2701_10ms_at_outport_1' */
void EBCR_BMS_DTC_18AA2701_10ms(void)
{
  if (CbEBCR_BMSADTCHighByteOvrSwt_flg) {
    set_GcEBCR_BMSADTCHighByte_numb(CcEBCR_BMSADTCHighByteOvr_numb);
  } else {
    set_GcEBCR_BMSADTCHighByte_numb(get_GcCAN1_BMSDTCHighByte_numb());
  }

  if (CbEBCR_BMSADTCLowByteOvrSwt_flg) {
    set_GcEBCR_BMSADTCLowByte_numb(CcEBCR_BMSADTCLowByteOvr_numb);
  } else {
    set_GcEBCR_BMSADTCLowByte_numb(get_GcCAN1_BMSDTCLowByte_numb());
  }

  if (CbEBCR_BMSADTCFailureTypeByteOvrSwt_flg) {
    set_GcEBCR_BMSADTCFailureTypeByte_numb(CcEBCR_BMSADTCFailureTypeByteOvr_numb);
  } else {
    set_GcEBCR_BMSADTCFailureTypeByte_numb(get_GcCAN1_BMSDTCFailureTypeByte_numb
      ());
  }

  if (CbEBCR_BMSBDTCHighByteOvrSwt_flg) {
    set_GcEBCR_BMSBDTCHighByte_numb(CcEBCR_BMSBDTCHighByteOvr_numb);
  } else {
    set_GcEBCR_BMSBDTCHighByte_numb(get_GcCAN3_BMSDTCHighByte_numb());
  }

  if (CbEBCR_BMSBDTCLowByteOvrSwt_flg) {
    set_GcEBCR_BMSBDTCLowByte_numb(CcEBCR_BMSBDTCLowByteOvr_numb);
  } else {
    set_GcEBCR_BMSBDTCLowByte_numb(get_GcCAN3_BMSDTCLowByte_numb());
  }

  if (CbEBCR_BMSBDTCFailureTypeByteOvrSwt_flg) {
    set_GcEBCR_BMSBDTCFailureTypeByte_numb(CcEBCR_BMSBDTCFailureTypeByteOvr_numb);
  } else {
    set_GcEBCR_BMSBDTCFailureTypeByte_numb(get_GcCAN3_BMSDTCFailureTypeByte_numb
      ());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_DetCell_18042701_10ms_at_outport_1' */
void EBCR_BMS_DetCell_18042701_10ms(void)
{
  if (CbEBCR_BMSACellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSACellBatNumb_numb(CcEBCR_BMSACellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSACellBatNumb_numb(get_GcCAN1_BMSCellBatteryNumber_numb());
  }

  if (CbEBCR_BMSAMesCellVoltNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSAMesCellVoltNumIdx_numb(CcEBCR_BMSAMesCellVoltNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSAMesCellVoltNumIdx_numb(get_GcCAN1_MesCellVoltNumIndex_numb());
  }

  if (CbEBCR_BMSAMes1CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSAMes1CellBalStat_flg(CbEBCR_BMSAMes1CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSAMes1CellBalStat_flg(get_GbCAN1_Mes1CellBalState_flg());
  }

  if (CbEBCR_BMSAMes1CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSAMes1CellVolt_mV(CcEBCR_BMSAMes1CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSAMes1CellVolt_mV((real32_T)get_GcCAN1_Mes1CellVolt_mV());
  }

  if (CbEBCR_BMSAMes2CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSAMes2CellBalStat_flg(CbEBCR_BMSAMes2CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSAMes2CellBalStat_flg(get_GbCAN1_Mes2CellBalState_flg());
  }

  if (CbEBCR_BMSAMes2CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSAMes2CellVolt_mV(CcEBCR_BMSAMes2CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSAMes2CellVolt_mV((real32_T)get_GcCAN1_Mes2CellVolt_mV());
  }

  if (CbEBCR_BMSAMes3CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSAMes3CellBalStat_flg(CbEBCR_BMSAMes3CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSAMes3CellBalStat_flg(get_GbCAN1_Mes3CellBalState_flg());
  }

  if (CbEBCR_BMSAMes3CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSAMes3CellVolt_mV(CcEBCR_BMSAMes3CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSAMes3CellVolt_mV((real32_T)get_GcCAN1_Mes3CellVolt_mV());
  }

  if (CbEBCR_BMSBCellBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBCellBatNumb_numb(CcEBCR_BMSBCellBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBCellBatNumb_numb(get_GcCAN3_BMSCellBatteryNumber_numb());
  }

  if (CbEBCR_BMSBMesCellVoltNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSBMesCellVoltNumIdx_numb(CcEBCR_BMSBMesCellVoltNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSBMesCellVoltNumIdx_numb(get_GcCAN3_MesCellVoltNumIndex_numb());
  }

  if (CbEBCR_BMSBMes1CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSBMes1CellBalStat_flg(CbEBCR_BMSBMes1CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSBMes1CellBalStat_flg(get_GbCAN3_Mes1CellBalState_flg());
  }

  if (CbEBCR_BMSBMes1CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSBMes1CellVolt_mV(CcEBCR_BMSBMes1CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSBMes1CellVolt_mV((real32_T)get_GcCAN3_Mes1CellVolt_mV());
  }

  if (CbEBCR_BMSBMes2CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSBMes2CellBalStat_flg(CbEBCR_BMSBMes2CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSBMes2CellBalStat_flg(get_GbCAN3_Mes2CellBalState_flg());
  }

  if (CbEBCR_BMSBMes2CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSBMes2CellVolt_mV(CcEBCR_BMSBMes2CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSBMes2CellVolt_mV((real32_T)get_GcCAN3_Mes2CellVolt_mV());
  }

  if (CbEBCR_BMSBMes3CellBalStatOvrSwt_flg) {
    set_GbEBCR_BMSBMes3CellBalStat_flg(CbEBCR_BMSBMes3CellBalStatOvr_flg);
  } else {
    set_GbEBCR_BMSBMes3CellBalStat_flg(get_GbCAN3_Mes3CellBalState_flg());
  }

  if (CbEBCR_BMSBMes3CellVoltOvrSwt_flg) {
    set_GcEBCR_BMSBMes3CellVolt_mV(CcEBCR_BMSBMes3CellVoltOvr_mV);
  } else {
    set_GcEBCR_BMSBMes3CellVolt_mV((real32_T)get_GcCAN3_Mes3CellVolt_mV());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_DetTemp_18062701_10ms_at_outport_1' */
void EBCR_BMS_DetTemp_18062701_10ms(void)
{
  if (CbEBCR_BMSACellTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSACellTempBatNumb_numb(CcEBCR_BMSACellTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSACellTempBatNumb_numb(get_GcCAN1_BMSCellTempBatteryNumber_numb
      ());
  }

  if (CbEBCR_BMSAMesCellTempNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSAMesCellTempNumIdx_numb(CcEBCR_BMSAMesCellTempNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSAMesCellTempNumIdx_numb(get_GcCAN1_MesCellTempNumIndex_numb());
  }

  if (CbEBCR_BMSACellTempMes1OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes1_C(CcEBCR_BMSACellTempMes1Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes1_C((real32_T)get_GcCAN1_CellTempMes1_C() - 40.0F);
  }

  if (CbEBCR_BMSACellTempMes2OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes2_C(CcEBCR_BMSACellTempMes2Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes2_C((real32_T)get_GcCAN1_CellTempMes2_C() - 40.0F);
  }

  if (CbEBCR_BMSACellTempMes3OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes3_C(CcEBCR_BMSACellTempMes3Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes3_C((real32_T)get_GcCAN1_CellTempMes3_C() - 40.0F);
  }

  if (CbEBCR_BMSACellTempMes4OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes4_C(CcEBCR_BMSACellTempMes4Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes4_C((real32_T)get_GcCAN1_CellTempMes4_C() - 40.0F);
  }

  if (CbEBCR_BMSACellTempMes5OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes5_C(CcEBCR_BMSACellTempMes5Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes5_C((real32_T)get_GcCAN1_CellTempMes5_C() - 40.0F);
  }

  if (CbEBCR_BMSACellTempMes6OvrSwt_flg) {
    set_GcEBCR_BMSACellTempMes6_C(CcEBCR_BMSACellTempMes6Ovr_C);
  } else {
    set_GcEBCR_BMSACellTempMes6_C((real32_T)get_GcCAN1_CellTempMes6_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBCellTempBatNumb_numb(CcEBCR_BMSBCellTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBCellTempBatNumb_numb(get_GcCAN3_BMSCellTempBatteryNumber_numb
      ());
  }

  if (CbEBCR_BMSBMesCellTempNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSBMesCellTempNumIdx_numb(CcEBCR_BMSBMesCellTempNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSBMesCellTempNumIdx_numb(get_GcCAN3_MesCellTempNumIndex_numb());
  }

  if (CbEBCR_BMSBCellTempMes1OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes1_C(CcEBCR_BMSBCellTempMes1Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes1_C((real32_T)get_GcCAN3_CellTempMes1_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempMes2OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes2_C(CcEBCR_BMSBCellTempMes2Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes2_C((real32_T)get_GcCAN3_CellTempMes2_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempMes3OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes3_C(CcEBCR_BMSBCellTempMes3Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes3_C((real32_T)get_GcCAN3_CellTempMes3_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempMes4OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes4_C(CcEBCR_BMSBCellTempMes4Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes4_C((real32_T)get_GcCAN3_CellTempMes4_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempMes5OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes5_C(CcEBCR_BMSBCellTempMes5Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes5_C((real32_T)get_GcCAN3_CellTempMes5_C() - 40.0F);
  }

  if (CbEBCR_BMSBCellTempMes6OvrSwt_flg) {
    set_GcEBCR_BMSBCellTempMes6_C(CcEBCR_BMSBCellTempMes6Ovr_C);
  } else {
    set_GcEBCR_BMSBCellTempMes6_C((real32_T)get_GcCAN3_CellTempMes6_C() - 40.0F);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_Fault_18072701_10ms_at_outport_1' */
void EBCR_BMS_Fault_18072701_10ms(void)
{
  if (CbEBCR_BMSAFaultAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSAFaultAliveCnt_numb(CcEBCR_BMSAFaultAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSAFaultAliveCnt_numb(get_GcCAN1_BMSFaultAliveCounter_numb());
  }

  if (CbEBCR_BMSAHVIsoWarningOvrSwt_flg) {
    set_GeEBCR_BMSAHVIsoWarning_enum(CeEBCR_BMSAHVIsoWarningOvr_enum);
  } else {
    set_GeEBCR_BMSAHVIsoWarning_enum(get_GeCAN1_HVIsoWarning_enum());
  }

  if (CbEBCR_BMSAHVILWarningOvrSwt_flg) {
    set_GbEBCR_BMSAHVILWarning_flg(CbEBCR_BMSAHVILWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAHVILWarning_flg(get_GbCAN1_HVILWarning_flg());
  }

  if (CbEBCR_BMSASOCLowWarningOvrSwt_flg) {
    set_GeEBCR_BMSASOCLowWarning_enum(CeEBCR_BMSASOCLowWarningOvr_enum);
  } else {
    set_GeEBCR_BMSASOCLowWarning_enum(get_GeCAN1_SOCLowWarning_enum());
  }

  if (CbEBCR_BMSATempDiffWarningOvrSwt_flg) {
    set_GbEBCR_BMSATempDiffWarning_flg(CbEBCR_BMSATempDiffWarningOvr_flg);
  } else {
    set_GbEBCR_BMSATempDiffWarning_flg(get_GbCAN1_TempDiffWarning_flg());
  }

  if (CbEBCR_BMSATempHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSATempHighWarning_flg(CbEBCR_BMSATempHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSATempHighWarning_flg(get_GbCAN1_TempHighWarning_flg());
  }

  if (CbEBCR_BMSAPackOvWarningOvrSwt_flg) {
    set_GbEBCR_BMSAPackOvWarning_flg(CbEBCR_BMSAPackOvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAPackOvWarning_flg(get_GbCAN1_PackOvWarning_flg());
  }

  if (CbEBCR_BMSAPackUvWarningOvrSwt_flg) {
    set_GbEBCR_BMSAPackUvWarning_flg(CbEBCR_BMSAPackUvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAPackUvWarning_flg(get_GbCAN1_PackUvWarning_flg());
  }

  if (CbEBCR_BMSACellOvWarningOvrSwt_flg) {
    set_GbEBCR_BMSACellOvWarning_flg(CbEBCR_BMSACellOvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSACellOvWarning_flg(get_GbCAN1_CellOvWarning_flg());
  }

  if (CbEBCR_BMSACellUvWarningOvrSwt_flg) {
    set_GbEBCR_BMSACellUvWarning_flg(CbEBCR_BMSACellUvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSACellUvWarning_flg(get_GbCAN1_CellUvWarning_flg());
  }

  if (CbEBCR_BMSASOCHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSASOCHighWarning_flg(CbEBCR_BMSASOCHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSASOCHighWarning_flg(get_GbCAN1_SOCHighWarning_flg());
  }

  if (CbEBCR_BMSASOCFastChrgWarningOvrSwt_flg) {
    set_GbEBCR_BMSASOCFastChrgWarning_flg(CbEBCR_BMSASOCFastChrgWarningOvr_flg);
  } else {
    set_GbEBCR_BMSASOCFastChrgWarning_flg(get_GbCAN1_SOCFastChgWarning_flg());
  }

  if (CbEBCR_BMSAPwrBatPackMismatchWarningOvrSwt_flg) {
    set_GbEBCR_BMSAPwrBatPackMismatchWarning_flg
      (CbEBCR_BMSAPwrBatPackMismatchWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAPwrBatPackMismatchWarning_flg
      (get_GbCAN1_PwrBatPackMismatchWarning_flg());
  }

  if (CbEBCR_BMSACelConsistencyWarningOvrSwt_flg) {
    set_GbEBCR_BMSACelConsistencyWarning_flg
      (CbEBCR_BMSACelConsistencyWarningOvr_flg);
  } else {
    set_GbEBCR_BMSACelConsistencyWarning_flg
      (get_GbCAN1_BMSCelConsistencyWarning_flg());
  }

  if (CbEBCR_BMSAVoltHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSAVoltHighWarning_flg(CbEBCR_BMSAVoltHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAVoltHighWarning_flg(get_GbCAN1_BMSVolHighWarning_flg());
  }

  if (CbEBCR_BMSAPackOCWarningOvrSwt_flg) {
    set_GbEBCR_BMSAPackOCWarning_flg(CbEBCR_BMSAPackOCWarningOvr_flg);
  } else {
    set_GbEBCR_BMSAPackOCWarning_flg(get_GbCAN1_PackOCWarning_flg());
  }

  if (CbEBCR_BMSAPACK1RelayWaringOvrSwt_flg) {
    set_GeEBCR_BMSAPACK1RelayWaring_enum(CeEBCR_BMSAPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSAPACK2RelayWaring_enum(CeEBCR_BMSAPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSAPACK3RelayWaring_enum(CeEBCR_BMSAPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSAPACK4RelayWaring_enum(CeEBCR_BMSAPACK1RelayWaringOvr_enum);
  } else {
    set_GeEBCR_BMSAPACK1RelayWaring_enum(get_GeCAN1_BMSPACK1RelayWaring_enum());
    set_GeEBCR_BMSAPACK2RelayWaring_enum(get_GeCAN1_BMSPACK2RelayWaring_enum());
    set_GeEBCR_BMSAPACK3RelayWaring_enum(get_GeCAN1_BMSPACK3RelayWaring_enum());
    set_GeEBCR_BMSAPACK4RelayWaring_enum(get_GeCAN1_BMSPACK4RelayWaring_enum());
  }

  if (CbEBCR_BMSARestEnergyOvrSwt_flg) {
    set_GcEBCR_BMSARestEnergy_kwH(CcEBCR_BMSARestEnergyOvr_kwH);
  } else {
    set_GcEBCR_BMSARestEnergy_kwH((real32_T)get_GcCAN1_RestEnergy_kwH() * 0.01F);
  }

  if (CbEBCR_BMSAFaultChkSumOvrSwt_flg) {
    set_GcEBCR_BMSAFaultChkSum_numb(CcEBCR_BMSAFaultChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSAFaultChkSum_numb(get_GcCAN1_BMSFaultCheckSum_numb());
  }

  if (CbEBCR_BMSBFaultAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSBFaultAliveCnt_numb(CcEBCR_BMSBFaultAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSBFaultAliveCnt_numb(get_GcCAN3_BMSFaultAliveCounter_numb());
  }

  if (CbEBCR_BMSBHVIsoWarningOvrSwt_flg) {
    set_GeEBCR_BMSBHVIsoWarning_enum(CeEBCR_BMSBHVIsoWarningOvr_enum);
  } else {
    set_GeEBCR_BMSBHVIsoWarning_enum(get_GeCAN3_HVIsoWarning_enum());
  }

  if (CbEBCR_BMSBHVILWarningOvrSwt_flg) {
    set_GbEBCR_BMSBHVILWarning_flg(CbEBCR_BMSBHVILWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBHVILWarning_flg(get_GbCAN3_HVILWarning_flg());
  }

  if (CbEBCR_BMSBSOCLowWarningOvrSwt_flg) {
    set_GeEBCR_BMSBSOCLowWarning_enum(CeEBCR_BMSBSOCLowWarningOvr_enum);
  } else {
    set_GeEBCR_BMSBSOCLowWarning_enum(get_GeCAN3_SOCLowWarning_enum());
  }

  if (CbEBCR_BMSBTempDiffWarningOvrSwt_flg) {
    set_GbEBCR_BMSBTempDiffWarning_flg(CbEBCR_BMSBTempDiffWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBTempDiffWarning_flg(get_GbCAN3_TempDiffWarning_flg());
  }

  if (CbEBCR_BMSBTempHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSBTempHighWarning_flg(CbEBCR_BMSBTempHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBTempHighWarning_flg(get_GbCAN3_TempHighWarning_flg());
  }

  if (CbEBCR_BMSBPackOvWarningOvrSwt_flg) {
    set_GbEBCR_BMSBPackOvWarning_flg(CbEBCR_BMSBPackOvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBPackOvWarning_flg(get_GbCAN3_PackOvWarning_flg());
  }

  if (CbEBCR_BMSBPackUvWarningOvrSwt_flg) {
    set_GbEBCR_BMSBPackUvWarning_flg(CbEBCR_BMSBPackUvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBPackUvWarning_flg(get_GbCAN3_PackUvWarning_flg());
  }

  if (CbEBCR_BMSBCellOvWarningOvrSwt_flg) {
    set_GbEBCR_BMSBCellOvWarning_flg(CbEBCR_BMSBCellOvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBCellOvWarning_flg(get_GbCAN3_CellOvWarning_flg());
  }

  if (CbEBCR_BMSBCellUvWarningOvrSwt_flg) {
    set_GbEBCR_BMSBCellUvWarning_flg(CbEBCR_BMSBCellUvWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBCellUvWarning_flg(get_GbCAN3_CellUvWarning_flg());
  }

  if (CbEBCR_BMSBSOCHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSBSOCHighWarning_flg(CbEBCR_BMSBSOCHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBSOCHighWarning_flg(get_GbCAN3_SOCHighWarning_flg());
  }

  if (CbEBCR_BMSBSOCFastChrgWarningOvrSwt_flg) {
    set_GbEBCR_BMSBSOCFastChrgWarning_flg(CbEBCR_BMSBSOCFastChrgWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBSOCFastChrgWarning_flg(get_GbCAN3_SOCFastChgWarning_flg());
  }

  if (CbEBCR_BMSBPwrBatPackMismatchWarningOvrSwt_flg) {
    set_GbEBCR_BMSBPwrBatPackMismatchWarning_flg
      (CbEBCR_BMSBPwrBatPackMismatchWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBPwrBatPackMismatchWarning_flg
      (get_GbCAN3_PwrBatPackMismatchWarning_flg());
  }

  if (CbEBCR_BMSBCelConsistencyWarningOvrSwt_flg) {
    set_GbEBCR_BMSBCelConsistencyWarning_flg
      (CbEBCR_BMSBCelConsistencyWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBCelConsistencyWarning_flg
      (get_GbCAN3_BMSCelConsistencyWarning_flg());
  }

  if (CbEBCR_BMSBVoltHighWarningOvrSwt_flg) {
    set_GbEBCR_BMSBVoltHighWarning_flg(CbEBCR_BMSBVoltHighWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBVoltHighWarning_flg(get_GbCAN3_BMSVolHighWarning_flg());
  }

  if (CbEBCR_BMSBPackOCWarningOvrSwt_flg) {
    set_GbEBCR_BMSBPackOCWarning_flg(CbEBCR_BMSBPackOCWarningOvr_flg);
  } else {
    set_GbEBCR_BMSBPackOCWarning_flg(get_GbCAN3_PackOCWarning_flg());
  }

  if (CbEBCR_BMSBPACK1RelayWaringOvrSwt_flg) {
    set_GeEBCR_BMSBPACK1RelayWaring_enum(CeEBCR_BMSBPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSBPACK2RelayWaring_enum(CeEBCR_BMSBPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSBPACK3RelayWaring_enum(CeEBCR_BMSBPACK1RelayWaringOvr_enum);
    set_GeEBCR_BMSBPACK4RelayWaring_enum(CeEBCR_BMSBPACK1RelayWaringOvr_enum);
  } else {
    set_GeEBCR_BMSBPACK1RelayWaring_enum(get_GeCAN3_BMSPACK1RelayWaring_enum());
    set_GeEBCR_BMSBPACK2RelayWaring_enum(get_GeCAN3_BMSPACK2RelayWaring_enum());
    set_GeEBCR_BMSBPACK3RelayWaring_enum(get_GeCAN3_BMSPACK3RelayWaring_enum());
    set_GeEBCR_BMSBPACK4RelayWaring_enum(get_GeCAN3_BMSPACK4RelayWaring_enum());
  }

  if (CbEBCR_BMSBRestEnergyOvrSwt_flg) {
    set_GcEBCR_BMSBRestEnergy_kwH(CcEBCR_BMSBRestEnergyOvr_kwH);
  } else {
    set_GcEBCR_BMSBRestEnergy_kwH((real32_T)get_GcCAN3_RestEnergy_kwH() * 0.01F);
  }

  if (CbEBCR_BMSBFaultChkSumOvrSwt_flg) {
    set_GcEBCR_BMSBFaultChkSum_numb(CcEBCR_BMSBFaultChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSBFaultChkSum_numb(get_GcCAN3_BMSFaultCheckSum_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_HV2_18182071_10ms_at_outport_1' */
void EBCR_BMS_HV2_18182071_10ms(void)
{
  if (CbEBCR_BMSABMUSP2VoltOvrSwt_flg) {
    set_GcEBCR_BMSABMUSP2Volt_V(CcEBCR_BMSABMUSP2VoltOvr_V);
  } else {
    set_GcEBCR_BMSABMUSP2Volt_V((real32_T)get_GcCAN1_BMUSP2Volt_V());
  }

  if (CbEBCR_BMSABMUSP3VoltOvrSwt_flg) {
    set_GcEBCR_BMSABMUSP3Volt_V(CcEBCR_BMSABMUSP3VoltOvr_V);
  } else {
    set_GcEBCR_BMSABMUSP3Volt_V((real32_T)get_GcCAN1_BMUSP3Volt_V());
  }

  if (CbEBCR_BMSABMUSP4VoltOvrSwt_flg) {
    set_GcEBCR_BMSABMUSP4Volt_V(CcEBCR_BMSABMUSP4VoltOvr_V);
  } else {
    set_GcEBCR_BMSABMUSP4Volt_V((real32_T)get_GcCAN1_BMUSP4Volt_V());
  }

  if (CbEBCR_BMSABMUSP5VoltOvrSwt_flg) {
    set_GcEBCR_BMSABMUSP5Volt_V(CcEBCR_BMSABMUSP5VoltOvr_V);
  } else {
    set_GcEBCR_BMSABMUSP5Volt_V((real32_T)get_GcCAN1_BMUSP5Volt_V());
  }

  if (CbEBCR_BMSBBMUSP2VoltOvrSwt_flg) {
    set_GcEBCR_BMSBBMUSP2Volt_V(CcEBCR_BMSBBMUSP2VoltOvr_V);
  } else {
    set_GcEBCR_BMSBBMUSP2Volt_V((real32_T)get_GcCAN3_BMUSP2Volt_V());
  }

  if (CbEBCR_BMSBBMUSP3VoltOvrSwt_flg) {
    set_GcEBCR_BMSBBMUSP3Volt_V(CcEBCR_BMSBBMUSP3VoltOvr_V);
  } else {
    set_GcEBCR_BMSBBMUSP3Volt_V((real32_T)get_GcCAN3_BMUSP3Volt_V());
  }

  if (CbEBCR_BMSBBMUSP4VoltOvrSwt_flg) {
    set_GcEBCR_BMSBBMUSP4Volt_V(CcEBCR_BMSBBMUSP4VoltOvr_V);
  } else {
    set_GcEBCR_BMSBBMUSP4Volt_V((real32_T)get_GcCAN3_BMUSP4Volt_V());
  }

  if (CbEBCR_BMSBBMUSP5VoltOvrSwt_flg) {
    set_GcEBCR_BMSBBMUSP5Volt_V(CcEBCR_BMSBBMUSP5VoltOvr_V);
  } else {
    set_GcEBCR_BMSBBMUSP5Volt_V((real32_T)get_GcCAN3_BMUSP5Volt_V());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_HV_18022701_10ms_at_outport_1' */
void EBCR_BMS_HV_18022701_10ms(void)
{
  if (CbEBCR_BMSAPreChrgHVoltOvrSwt_flg) {
    set_GcEBCR_BMSAPreChrgHVolt_V(CcEBCR_BMSAPreChrgHVoltOvr_V);
  } else {
    set_GcEBCR_BMSAPreChrgHVolt_V((real32_T)get_GcCAN1_PreChrgHVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSAHeatVoltOvrSwt_flg) {
    set_GcEBCR_BMSAHeatVolt_V(CcEBCR_BMSAHeatVoltOvr_V);
  } else {
    set_GcEBCR_BMSAHeatVolt_V((real32_T)get_GcCAN1_HeatVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSAMinBatWaterTmpInOvrSwt_flg) {
    set_GcEBCR_BMSAMinBatWaterTmpIn_C(CcEBCR_BMSAMinBatWaterTmpInOvr_C);
  } else {
    set_GcEBCR_BMSAMinBatWaterTmpIn_C((real32_T)get_GcCAN1_MinBatWaterTmpIn_C()
      - 40.0F);
  }

  if (CbEBCR_BMSAMaxBatWaterTmpOutOvrSwt_flg) {
    set_GcEBCR_BMSAMaxBatWaterTmpOut_C(CcEBCR_BMSAMaxBatWaterTmpOutOvr_C);
  } else {
    set_GcEBCR_BMSAMaxBatWaterTmpOut_C((real32_T)get_GcCAN1_MaxBatWaterTmpOut_C()
      - 40.0F);
  }

  if (CbEBCR_BMSBPreChrgHVoltOvrSwt_flg) {
    set_GcEBCR_BMSBPreChrgHVolt_V(CcEBCR_BMSBPreChrgHVoltOvr_V);
  } else {
    set_GcEBCR_BMSBPreChrgHVolt_V((real32_T)get_GcCAN3_PreChrgHVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBHeatVoltOvrSwt_flg) {
    set_GcEBCR_BMSBHeatVolt_V(CcEBCR_BMSBHeatVoltOvr_V);
  } else {
    set_GcEBCR_BMSBHeatVolt_V((real32_T)get_GcCAN3_HeatVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBMinBatWaterTmpInOvrSwt_flg) {
    set_GcEBCR_BMSBMinBatWaterTmpIn_C(CcEBCR_BMSBMinBatWaterTmpInOvr_C);
  } else {
    set_GcEBCR_BMSBMinBatWaterTmpIn_C((real32_T)get_GcCAN3_MinBatWaterTmpIn_C()
      - 40.0F);
  }

  if (CbEBCR_BMSBMaxBatWaterTmpOutOvrSwt_flg) {
    set_GcEBCR_BMSBMaxBatWaterTmpOut_C(CcEBCR_BMSBMaxBatWaterTmpOutOvr_C);
  } else {
    set_GcEBCR_BMSBMaxBatWaterTmpOut_C((real32_T)get_GcCAN3_MaxBatWaterTmpOut_C()
      - 40.0F);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_HV_Curr_18102071_10ms_at_outport_1' */
void EBCR_BMS_HV_Curr_18102071_10ms(void)
{
  if (CbEBCR_BMSAHVCurrAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSAHVCurrAliveCnt_numb(CcEBCR_BMSAHVCurrAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSAHVCurrAliveCnt_numb(get_GcCAN1_BMSHVCurrAliveCounter_numb());
  }

  if (CbEBCR_BMSAPackVoltVldOvrSwt_flg) {
    set_GbEBCR_BMSAPackVoltVld_flg(CbEBCR_BMSAPackVoltVldOvr_flg);
  } else {
    set_GbEBCR_BMSAPackVoltVld_flg(get_GbCAN1_PackVoltVld_flg());
  }

  if (CbEBCR_PackAOutVoltOvrSwt_flg) {
    set_GcEBCR_PackAOutVolt_V(CcEBCR_PackAOutVoltOvr_V);
  } else {
    set_GcEBCR_PackAOutVolt_V((real32_T)get_GcCAN1_PackVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSAPackVoltOvrSwt_flg) {
    set_GcEBCR_BMSAPackVolt_V(CcEBCR_BMSAPackVoltOvr_V);
  } else {
    set_GcEBCR_BMSAPackVolt_V((real32_T)get_GcCAN1_PackVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSAPackCurrentVldOvrSwt_flg) {
    set_GbEBCR_BMSAPackCurrentVld_flg(CbEBCR_BMSAPackCurrentVldOvr_flg);
  } else {
    set_GbEBCR_BMSAPackCurrentVld_flg(get_GbCAN1_PackCurrentVld_flg());
  }

  if (CbEBCR_BMSAPackCurrentOvrSwt_flg) {
    set_GcEBCR_BMSAPackCurrent_A(CcEBCR_BMSAPackCurrentOvr_A);
  } else {
    set_GcEBCR_BMSAPackCurrent_A((real32_T)get_GcCAN1_PackCurrent_A() * 0.1F -
      400.0F);
  }

  if (CbEBCR_BMSAHVCurrChkSumOvrSwt_flg) {
    set_GcEBCR_BMSAHVCurrChkSum_numb(CcEBCR_BMSAHVCurrChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSAHVCurrChkSum_numb(get_GcCAN1_BMSHVCurrCheckSum_numb());
  }

  if (CbEBCR_BMSBHVCurrAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSBHVCurrAliveCnt_numb(CcEBCR_BMSBHVCurrAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSBHVCurrAliveCnt_numb(get_GcCAN3_BMSHVCurrAliveCounter_numb());
  }

  if (CbEBCR_BMSBPackVoltVldOvrSwt_flg) {
    set_GbEBCR_BMSBPackVoltVld_flg(CbEBCR_BMSBPackVoltVldOvr_flg);
  } else {
    set_GbEBCR_BMSBPackVoltVld_flg(get_GbCAN3_PackVoltVld_flg());
  }

  if (CbEBCR_PackBOutVoltOvrSwt_flg) {
    set_GcEBCR_PackBOutVolt_V(CcEBCR_PackBOutVoltOvr_V);
  } else {
    set_GcEBCR_PackBOutVolt_V((real32_T)get_GcCAN3_PackVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBPackVoltOvrSwt_flg) {
    set_GcEBCR_BMSBPackVolt_V(CcEBCR_BMSBPackVoltOvr_V);
  } else {
    set_GcEBCR_BMSBPackVolt_V((real32_T)get_GcCAN3_PackVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBPackCurrentVldOvrSwt_flg) {
    set_GbEBCR_BMSBPackCurrentVld_flg(CbEBCR_BMSBPackCurrentVldOvr_flg);
  } else {
    set_GbEBCR_BMSBPackCurrentVld_flg(get_GbCAN3_PackCurrentVld_flg());
  }

  if (CbEBCR_BMSBPackCurrentOvrSwt_flg) {
    set_GcEBCR_BMSBPackCurrent_A(CcEBCR_BMSBPackCurrentOvr_A);
  } else {
    set_GcEBCR_BMSBPackCurrent_A((real32_T)get_GcCAN3_PackCurrent_A() * 0.1F -
      400.0F);
  }

  if (CbEBCR_BMSBHVCurrChkSumOvrSwt_flg) {
    set_GcEBCR_BMSBHVCurrChkSum_numb(CcEBCR_BMSBHVCurrChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSBHVCurrChkSum_numb(get_GcCAN3_BMSHVCurrCheckSum_numb());
  }

  EBCR_Y.GcEBCR_PackBOutVolt_V = 0.0F;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_ISO_18162701_10ms_at_outport_1' */
void EBCR_BMS_ISO_18162701_10ms(void)
{
  if (CbEBCR_BMSAISOPosVoltOvrSwt_flg) {
    set_GcEBCR_BMSAISOPosVolt_V(CcEBCR_BMSAISOPosVoltOvr_V);
  } else {
    set_GcEBCR_BMSAISOPosVolt_V((real32_T)get_GcCAN1_BMSISOPosVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSAISONegVoltOvrSwt_flg) {
    set_GcEBCR_BMSAISONegVolt_V(CcEBCR_BMSAISONegVoltOvr_V);
  } else {
    set_GcEBCR_BMSAISONegVolt_V((real32_T)get_GcCAN1_BMSISONegVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSASOPosResOvrSwt_flg) {
    set_GcEBCR_BMSASOPosRes_kOhm(CcEBCR_BMSASOPosResOvr_kOhm);
  } else {
    set_GcEBCR_BMSASOPosRes_kOhm((real32_T)get_GcCAN1_BMSISOPosRes_kOhm());
  }

  if (CbEBCR_BMSAISONegResOvrSwt_flg) {
    set_GcEBCR_BMSAISONegRes_kOhm(CcEBCR_BMSAISONegResOvr_kOhm);
  } else {
    set_GcEBCR_BMSAISONegRes_kOhm((real32_T)get_GcCAN1_BMSISONegRes_kOhm());
  }

  if (CbEBCR_BMSBISOPosVoltOvrSwt_flg) {
    set_GcEBCR_BMSBISOPosVolt_V(CcEBCR_BMSBISOPosVoltOvr_V);
  } else {
    set_GcEBCR_BMSBISOPosVolt_V((real32_T)get_GcCAN3_BMSISOPosVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBISONegVoltOvrSwt_flg) {
    set_GcEBCR_BMSBISONegVolt_V(CcEBCR_BMSBISONegVoltOvr_V);
  } else {
    set_GcEBCR_BMSBISONegVolt_V((real32_T)get_GcCAN3_BMSISONegVolt_V() * 0.1F);
  }

  if (CbEBCR_BMSBSOPosResOvrSwt_flg) {
    set_GcEBCR_BMSBSOPosRes_kOhm(CcEBCR_BMSBSOPosResOvr_kOhm);
  } else {
    set_GcEBCR_BMSBSOPosRes_kOhm((real32_T)get_GcCAN3_BMSISOPosRes_kOhm());
  }

  if (CbEBCR_BMSBISONegResOvrSwt_flg) {
    set_GcEBCR_BMSBISONegRes_kOhm(CcEBCR_BMSBISONegResOvr_kOhm);
  } else {
    set_GcEBCR_BMSBISONegRes_kOhm((real32_T)get_GcCAN3_BMSISONegRes_kOhm());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_Info_18082701_10ms_at_outport_1' */
void EBCR_BMS_Info_18082701_10ms(void)
{
  if (CbEBCR_BMSARechrgEnergyStorSysNumbOvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysNumb_numb
      (CcEBCR_BMSARechrgEnergyStorSysNumbOvr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysNumb_numb
      (get_GcCAN1_RechgEnergyStorSysNumb_numb());
  }

  if (CbEBCR_BMSACurRechrgEnergyStorSysIdxOvrSwt_flg) {
    set_GcEBCR_BMSACurRechrgEnergyStorSysIdx_numb
      (CcEBCR_BMSACurRechrgEnergyStorSysIdxOvr_numb);
  } else {
    set_GcEBCR_BMSACurRechrgEnergyStorSysIdx_numb
      (get_GcCAN1_CurRechgEnergyStorSysIndex_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCodeLengthOvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCodeLength_numb
      (CcEBCR_BMSARechrgEnergyStorSysCodeLengthOvr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCodeLength_numb
      (get_GcCAN1_RechgEnergyStorSysCodeLength_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCodeIdxOvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCodeIdx_numb
      (CcEBCR_BMSARechrgEnergyStorSysCodeIdxOvr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCodeIdx_numb
      (get_GcCAN1_RechgEnergyStorSysCodeIndex_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCode1OvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCode1_numb
      (CcEBCR_BMSARechrgEnergyStorSysCode1Ovr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCode1_numb
      (get_GcCAN1_RechgEnergyStorSysCode1_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCode2OvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCode2_numb
      (CcEBCR_BMSARechrgEnergyStorSysCode2Ovr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCode2_numb
      (get_GcCAN1_RechgEnergyStorSysCode2_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCode3OvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCode3_numb
      (CcEBCR_BMSARechrgEnergyStorSysCode3Ovr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCode3_numb
      (get_GcCAN1_RechgEnergyStorSysCode3_numb());
  }

  if (CbEBCR_BMSARechrgEnergyStorSysCode4OvrSwt_flg) {
    set_GcEBCR_BMSARechrgEnergyStorSysCode4_numb
      (CcEBCR_BMSARechrgEnergyStorSysCode4Ovr_numb);
  } else {
    set_GcEBCR_BMSARechrgEnergyStorSysCode4_numb
      (get_GcCAN1_RechgEnergyStorSysCode4_numb());
  }

  if (CbEBCR_BMSASwVersionOvrSwt_flg) {
    set_GcEBCR_BMSASwVersion_numb(CcEBCR_BMSASwVersionOvr_numb);
  } else {
    set_GcEBCR_BMSASwVersion_numb(get_GcCAN1_BMSSwVersion_numb());
  }

  if (CbEBCR_BMSAHwVersionOvrSwt_flg) {
    set_GcEBCR_BMSAHwVersion_numb(CcEBCR_BMSAHwVersionOvr_numb);
  } else {
    set_GcEBCR_BMSAHwVersion_numb(get_GcCAN1_BMSHwVersion_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysNumbOvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysNumb_numb
      (CcEBCR_BMSBRechrgEnergyStorSysNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysNumb_numb
      (get_GcCAN3_RechgEnergyStorSysNumb_numb());
  }

  if (CbEBCR_BMSBCurRechrgEnergyStorSysIdxOvrSwt_flg) {
    set_GcEBCR_BMSBCurRechrgEnergyStorSysIdx_numb
      (CcEBCR_BMSBCurRechrgEnergyStorSysIdxOvr_numb);
  } else {
    set_GcEBCR_BMSBCurRechrgEnergyStorSysIdx_numb
      (get_GcCAN3_CurRechgEnergyStorSysIndex_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCodeLengthOvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCodeLength_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCodeLengthOvr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCodeLength_numb
      (get_GcCAN3_RechgEnergyStorSysCodeLength_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCodeIdxOvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCodeIdx_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCodeIdxOvr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCodeIdx_numb
      (get_GcCAN3_RechgEnergyStorSysCodeIndex_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCode1OvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode1_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCode1Ovr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode1_numb
      (get_GcCAN3_RechgEnergyStorSysCode1_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCode2OvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode2_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCode2Ovr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode2_numb
      (get_GcCAN3_RechgEnergyStorSysCode2_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCode3OvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode3_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCode3Ovr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode3_numb
      (get_GcCAN3_RechgEnergyStorSysCode3_numb());
  }

  if (CbEBCR_BMSBRechrgEnergyStorSysCode4OvrSwt_flg) {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode4_numb
      (CcEBCR_BMSBRechrgEnergyStorSysCode4Ovr_numb);
  } else {
    set_GcEBCR_BMSBRechrgEnergyStorSysCode4_numb
      (get_GcCAN3_RechgEnergyStorSysCode4_numb());
  }

  if (CbEBCR_BMSBSwVersionOvrSwt_flg) {
    set_GcEBCR_BMSBSwVersion_numb(CcEBCR_BMSBSwVersionOvr_numb);
  } else {
    set_GcEBCR_BMSBSwVersion_numb(get_GcCAN3_BMSSwVersion_numb());
  }

  if (CbEBCR_BMSBHwVersionOvrSwt_flg) {
    set_GcEBCR_BMSBHwVersion_numb(CcEBCR_BMSBHwVersionOvr_numb);
  } else {
    set_GcEBCR_BMSBHwVersion_numb(get_GcCAN3_BMSHwVersion_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_LongSOP_18032701_10ms_at_outport_1' */
void EBCR_BMS_LongSOP_18032701_10ms(void)
{
  if (CbEBCR_BMSASOPAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSASOPAliveCnt_numb(CcEBCR_BMSASOPAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSASOPAliveCnt_numb(get_GcCAN1_BMSSOPAliveCounter_numb());
  }

  if (CbEBCR_BMSAHVBatSOCOvrSwt_flg) {
    set_GcEBCR_BMSAHVBatSOC_pct(CcEBCR_BMSAHVBatSOCOvr_pct);
  } else {
    set_GcEBCR_BMSAHVBatSOC_pct(get_GcCAN1_HVBatSOC_pct());
  }

  if (CbEBCR_BMSAHVBCPLngTrmChrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSAHVBCPLngTrmChrgPwr_kW(CcEBCR_BMSAHVBCPLngTrmChrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSAHVBCPLngTrmChrgPwr_kW((real32_T)
      get_GcCAN1_HVBCPLngTrmChrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_PackALongDisChrgPwrOvrSwt_flg) {
    set_GcEBCR_PackALongDisChrgPwr_kw(CcEBCR_PackALongDisChrgPwrOvr_kw);
  } else {
    set_GcEBCR_PackALongDisChrgPwr_kw((real32_T)
      get_GcCAN1_HVBDPLngTrmDischrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSASOPChkSumOvrSwt_flg) {
    set_GcEBCR_BMSASOPChkSum_numb(CcEBCR_BMSASOPChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSASOPChkSum_numb(get_GcCAN1_BMSSOPCheckSum_numb());
  }

  if (CbEBCR_BMSBSOPAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSBSOPAliveCnt_numb(CcEBCR_BMSBSOPAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSBSOPAliveCnt_numb(get_GcCAN3_BMSSOPAliveCounter_numb());
  }

  if (CbEBCR_BMSBHVBatSOCOvrSwt_flg) {
    set_GcEBCR_BMSBHVBatSOC_pct(CcEBCR_BMSBHVBatSOCOvr_pct);
  } else {
    set_GcEBCR_BMSBHVBatSOC_pct(get_GcCAN3_HVBatSOC_pct());
  }

  if (CbEBCR_BMSBHVBCPLngTrmChrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSBHVBCPLngTrmChrgPwr_kW(CcEBCR_BMSBHVBCPLngTrmChrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSBHVBCPLngTrmChrgPwr_kW((real32_T)
      get_GcCAN3_HVBCPLngTrmChrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_PackBLongDisChrgPwrOvrSwt_flg) {
    set_GcEBCR_PackBLongDisChrgPwr_kw(CcEBCR_PackBLongDisChrgPwrOvr_kw);
  } else {
    set_GcEBCR_PackBLongDisChrgPwr_kw((real32_T)
      get_GcCAN3_HVBDPLngTrmDischrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSBSOPChkSumOvrSwt_flg) {
    set_GcEBCR_BMSBSOPChkSum_numb(CcEBCR_BMSBSOPChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSBSOPChkSum_numb(get_GcCAN3_BMSSOPCheckSum_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_PackInfo_18142701_10ms_at_outport_1' */
void EBCR_BMS_PackInfo_18142701_10ms(void)
{
  if (CbEBCR_BMSAPackNumbOvrSwt_flg) {
    set_GcEBCR_BMSAPackNumb_numb(CcEBCR_BMSAPackNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAPackNumb_numb(get_GcCAN1_Packnumber_numb());
  }

  if (CbEBCR_BMSAPackNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSAPackNumIdx_numb(CcEBCR_BMSAPackNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSAPackNumIdx_numb(get_GcCAN1_Packnumberindex_numb());
  }

  if (CbEBCR_BMSAPackCurrentStatOvrSwt_flg) {
    set_GbEBCR_BMSAPackCurrentStat_flg(CbEBCR_BMSAPackCurrentStatOvr_flg);
  } else {
    set_GbEBCR_BMSAPackCurrentStat_flg(get_GbCAN1_PackCurrentStatus_flg());
  }

  if (CbEBCR_BMSAPackSNOvrSwt_flg) {
    set_GcEBCR_BMSAPackSN_numb(CcEBCR_BMSAPackSNOvr_numb);
  } else {
    set_GcEBCR_BMSAPackSN_numb(get_GcCAN1_PackSerialNumber_numb());
  }

  if (CbEBCR_BMSAPackProductionDateYearOvrSwt_flg) {
    set_GcEBCR_BMSAPackProductionDateYear_numb
      (CcEBCR_BMSAPackProductionDateYearOvr_numb);
  } else {
    set_GcEBCR_BMSAPackProductionDateYear_numb
      (get_GcCAN1_PackProductionDateYear_numb());
  }

  if (CbEBCR_BMSAPackProductionDateMonthOvrSwt_flg) {
    set_GcEBCR_BMSAPackProductionDateMonth_numb
      (CcEBCR_BMSAPackProductionDateMonthOvr_numb);
  } else {
    set_GcEBCR_BMSAPackProductionDateMonth_numb
      (get_GcCAN1_PackProductionDateMonth_numb());
  }

  if (CbEBCR_BMSAPackProductionDateDayOvrSwt_flg) {
    set_GcEBCR_BMSAPackProductionDateDay_numb
      (CcEBCR_BMSAPackProductionDateDayOvr_numb);
  } else {
    set_GcEBCR_BMSAPackProductionDateDay_numb
      (get_GcCAN1_PackProductionDateDay_numb());
  }

  if (CbEBCR_BMSBPackNumbOvrSwt_flg) {
    set_GcEBCR_BMSBPackNumb_numb(CcEBCR_BMSBPackNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBPackNumb_numb(get_GcCAN3_Packnumber_numb());
  }

  if (CbEBCR_BMSBPackNumIdxOvrSwt_flg) {
    set_GcEBCR_BMSBPackNumIdx_numb(CcEBCR_BMSBPackNumIdxOvr_numb);
  } else {
    set_GcEBCR_BMSBPackNumIdx_numb(get_GcCAN3_Packnumberindex_numb());
  }

  if (CbEBCR_BMSBPackCurrentStatOvrSwt_flg) {
    set_GbEBCR_BMSBPackCurrentStat_flg(CbEBCR_BMSBPackCurrentStatOvr_flg);
  } else {
    set_GbEBCR_BMSBPackCurrentStat_flg(get_GbCAN3_PackCurrentStatus_flg());
  }

  if (CbEBCR_BMSBPackSNOvrSwt_flg) {
    set_GcEBCR_BMSBPackSN_numb(CcEBCR_BMSBPackSNOvr_numb);
  } else {
    set_GcEBCR_BMSBPackSN_numb(get_GcCAN3_PackSerialNumber_numb());
  }

  if (CbEBCR_BMSBPackProductionDateYearOvrSwt_flg) {
    set_GcEBCR_BMSBPackProductionDateYear_numb
      (CcEBCR_BMSBPackProductionDateYearOvr_numb);
  } else {
    set_GcEBCR_BMSBPackProductionDateYear_numb
      (get_GcCAN3_PackProductionDateYear_numb());
  }

  if (CbEBCR_BMSBPackProductionDateMonthOvrSwt_flg) {
    set_GcEBCR_BMSBPackProductionDateMonth_numb
      (CcEBCR_BMSBPackProductionDateMonthOvr_numb);
  } else {
    set_GcEBCR_BMSBPackProductionDateMonth_numb
      (get_GcCAN3_PackProductionDateMonth_numb());
  }

  if (CbEBCR_BMSBPackProductionDateDayOvrSwt_flg) {
    set_GcEBCR_BMSBPackProductionDateDay_numb
      (CcEBCR_BMSBPackProductionDateDayOvr_numb);
  } else {
    set_GcEBCR_BMSBPackProductionDateDay_numb
      (get_GcCAN3_PackProductionDateDay_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_PeakSOP_18172701_10ms_at_outport_1' */
void EBCR_BMS_PeakSOP_18172701_10ms(void)
{
  if (CbEBCR_BMSAPeakSOPAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSAPeakSOPAliveCnt_numb(CcEBCR_BMSAPeakSOPAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSAPeakSOPAliveCnt_numb(get_GcCAN1_BMSPeakSOPAliveCounter_numb());
  }

  if (CbEBCR_BMSAHVBCPShrtTrmChrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSAHVBCPShrtTrmChrgPwr_kW(CcEBCR_BMSAHVBCPShrtTrmChrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSAHVBCPShrtTrmChrgPwr_kW((real32_T)
      get_GcCAN1_HVBCPShrtTrmChrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSAHVBDPShrtTrmDischrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSAHVBDPShrtTrmDischrgPwr_kW
      (CcEBCR_BMSAHVBDPShrtTrmDischrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSAHVBDPShrtTrmDischrgPwr_kW((real32_T)
      get_GcCAN1_HVBDPShrtTrmDischrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSAPeakSOPChkSumOvrSwt_flg) {
    set_GcEBCR_BMSAPeakSOPChkSum_numb(CcEBCR_BMSAPeakSOPChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSAPeakSOPChkSum_numb(get_GcCAN1_BMSPeakSOPCheckSum_numb());
  }

  if (CbEBCR_BMSBPeakSOPAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSBPeakSOPAliveCnt_numb(CcEBCR_BMSBPeakSOPAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSBPeakSOPAliveCnt_numb(get_GcCAN3_BMSPeakSOPAliveCounter_numb());
  }

  if (CbEBCR_BMSBHVBCPShrtTrmChrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSBHVBCPShrtTrmChrgPwr_kW(CcEBCR_BMSBHVBCPShrtTrmChrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSBHVBCPShrtTrmChrgPwr_kW((real32_T)
      get_GcCAN3_HVBCPShrtTrmChrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSBHVBDPShrtTrmDischrgPwrOvrSwt_flg) {
    set_GcEBCR_BMSBHVBDPShrtTrmDischrgPwr_kW
      (CcEBCR_BMSBHVBDPShrtTrmDischrgPwrOvr_kW);
  } else {
    set_GcEBCR_BMSBHVBDPShrtTrmDischrgPwr_kW((real32_T)
      get_GcCAN3_HVBDPShrtTrmDischrgPwr_kW() * 0.1F);
  }

  if (CbEBCR_BMSBPeakSOPChkSumOvrSwt_flg) {
    set_GcEBCR_BMSBPeakSOPChkSum_numb(CcEBCR_BMSBPeakSOPChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSBPeakSOPChkSum_numb(get_GcCAN3_BMSPeakSOPCheckSum_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_SysPara_18012701_10ms_at_outport_1' */
void EBCR_BMS_SysPara_18012701_10ms(void)
{
  if (CbEBCR_BMSACellQuantityOvrSwt_flg) {
    set_GcEBCR_BMSACellQuantity_numb(CcEBCR_BMSACellQuantityOvr_numb);
  } else {
    set_GcEBCR_BMSACellQuantity_numb(get_GcCAN1_BMSCellQuantity_numb());
  }

  if (CbEBCR_BMSARealSOCOvrSwt_flg) {
    set_GcEBCR_BMSARealSOC_pct(CcEBCR_BMSARealSOCOvr_pct);
  } else {
    set_GcEBCR_BMSARealSOC_pct(get_GcCAN1_RealSOC_pct());
  }

  if (CbEBCR_BMSATempProbeQuantifyOvrSwt_flg) {
    set_GcEBCR_BMSATempProbeQuantify_numb(CcEBCR_BMSATempProbeQuantifyOvr_numb);
  } else {
    set_GcEBCR_BMSATempProbeQuantify_numb(get_GcCAN1_BMSTempProbeQuantity_numb());
  }

  if (CbEBCR_BMSAHVIsoValueOvrSwt_flg) {
    set_GcEBCR_BMSAHVIsoValue_kOhm(CcEBCR_BMSAHVIsoValueOvr_kOhm);
  } else {
    set_GcEBCR_BMSAHVIsoValue_kOhm((real32_T)get_GcCAN1_HVIsoValue_kOhm());
  }

  if (CbEBCR_BMSASOHOvrSwt_flg) {
    set_GcEBCR_BMSASOH_pct(CcEBCR_BMSASOHOvr_pct);
  } else {
    set_GcEBCR_BMSASOH_pct(get_GcCAN1_SOH_pct());
  }

  if (CbEBCR_BMSASOEOvrSwt_flg) {
    set_GcEBCR_BMSASOE_kWh(CcEBCR_BMSASOEOvr_kWh);
  } else {
    set_GcEBCR_BMSASOE_kWh((real32_T)get_GcCAN1_SOE_kWh());
  }

  if (CbEBCR_BMSATotalBatCapOvrSwt_flg) {
    set_GcEBCR_BMSATotalBatCap_Ah(CcEBCR_BMSATotalBatCapOvr_Ah);
  } else {
    set_GcEBCR_BMSATotalBatCap_Ah((real32_T)get_GcCAN1_TotalBatteryCap_Ah() *
      0.1F);
  }

  if (CbEBCR_BMSBCellQuantityOvrSwt_flg) {
    set_GcEBCR_BMSBCellQuantity_numb(CcEBCR_BMSBCellQuantityOvr_numb);
  } else {
    set_GcEBCR_BMSBCellQuantity_numb(get_GcCAN3_BMSCellQuantity_numb());
  }

  if (CbEBCR_BMSBRealSOCOvrSwt_flg) {
    set_GcEBCR_BMSBRealSOC_pct(CcEBCR_BMSBRealSOCOvr_pct);
  } else {
    set_GcEBCR_BMSBRealSOC_pct(get_GcCAN3_RealSOC_pct());
  }

  if (CbEBCR_BMSBTempProbeQuantifyOvrSwt_flg) {
    set_GcEBCR_BMSBTempProbeQuantify_numb(CcEBCR_BMSBTempProbeQuantifyOvr_numb);
  } else {
    set_GcEBCR_BMSBTempProbeQuantify_numb(get_GcCAN3_BMSTempProbeQuantity_numb());
  }

  if (CbEBCR_BMSBHVIsoValueOvrSwt_flg) {
    set_GcEBCR_BMSBHVIsoValue_kOhm(CcEBCR_BMSBHVIsoValueOvr_kOhm);
  } else {
    set_GcEBCR_BMSBHVIsoValue_kOhm((real32_T)get_GcCAN3_HVIsoValue_kOhm());
  }

  if (CbEBCR_BMSBSOHOvrSwt_flg) {
    set_GcEBCR_BMSBSOH_pct(CcEBCR_BMSBSOHOvr_pct);
  } else {
    set_GcEBCR_BMSBSOH_pct(get_GcCAN3_SOH_pct());
  }

  if (CbEBCR_BMSBSOEOvrSwt_flg) {
    set_GcEBCR_BMSBSOE_kWh(CcEBCR_BMSBSOEOvr_kWh);
  } else {
    set_GcEBCR_BMSBSOE_kWh((real32_T)get_GcCAN3_SOE_kWh());
  }

  if (CbEBCR_BMSBTotalBatCapOvrSwt_flg) {
    set_GcEBCR_BMSBTotalBatCap_Ah(CcEBCR_BMSBTotalBatCapOvr_Ah);
  } else {
    set_GcEBCR_BMSBTotalBatCap_Ah((real32_T)get_GcCAN3_TotalBatteryCap_Ah() *
      0.1F);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_SysStat_18122701_10ms_at_outport_1' */
void EBCR_BMS_SysStat_18122701_10ms(void)
{
  if (CbEBCR_BMSASysStatAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSASysStatAliveCnt_numb(CcEBCR_BMSASysStatAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSASysStatAliveCnt_numb(get_GcCAN1_BMSSysStatAliveCounter_numb());
  }

  if (CbEBCR_BMSAHeatMagCntStatOvrSwt_flg) {
    set_GeEBCR_BMSAHeatMagCntStat_enum(CeEBCR_BMSAHeatMagCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSAHeatMagCntStat_enum(get_GeCAN1_HeatMagCntStat_enum());
  }

  if (CbEBCR_BMSAHVSysStatOvrSwt_flg) {
    set_GeEBCR_BMSAHVSysStat_enum(CeEBCR_BMSAHVSysStatOvr_enum);
  } else {
    set_GeEBCR_BMSAHVSysStat_enum(get_GeCAN1_HVSystemStatus_enum());
  }

  if (CbEBCR_BMSAFaultLevelOvrSwt_flg) {
    set_GeEBCR_BMSAFaultLevel_enum(CeEBCR_BMSAFaultLevelOvr_enum);
  } else {
    set_GeEBCR_BMSAFaultLevel_enum(get_GeCAN1_BMSFaultLevel_enum());
  }

  if (CbEBCR_BMSAISODetStatOvrSwt_flg) {
    set_GeEBCR_BMSAISODetStat_enum(CeEBCR_BMSAISODetStatOvr_enum);
  } else {
    set_GeEBCR_BMSAISODetStat_enum(get_GeCAN1_IsoDetStat_enum());
  }

  if (CbEBCR_BMSAHVShutdownReqOvrSwt_flg) {
    set_GbEBCR_BMSAHVShutdownReq_flg(CbEBCR_BMSAHVShutdownReqOvr_flg);
  } else {
    set_GbEBCR_BMSAHVShutdownReq_flg(get_GbCAN1_HVShutdownReq_flg());
  }

  if (CbEBCR_BMSAChrgVoltMaxOvrSwt_flg) {
    set_GcEBCR_BMSAChrgVoltMax_V(CcEBCR_BMSAChrgVoltMaxOvr_V);
  } else {
    set_GcEBCR_BMSAChrgVoltMax_V((real32_T)get_GcCAN1_ChargeVoltMax_V());
  }

  if (CbEBCR_BMSAHCUPwrCtrlOvrSwt_flg) {
    set_GbEBCR_BMSAHCUPwrCtrl_flg(CbEBCR_BMSAHCUPwrCtrlOvr_flg);
  } else {
    set_GbEBCR_BMSAHCUPwrCtrl_flg(get_GbCAN1_HCUPowerCtrl_flg());
  }

  if (CbEBCR_BMSAHeatModeSelOvrSwt_flg) {
    set_GeEBCR_BMSAHeatModeSel_enum(CeEBCR_BMSAHeatModeSelOvr_enum);
  } else {
    set_GeEBCR_BMSAHeatModeSel_enum(get_GeCAN1_HeatModeSelect_enum());
  }

  if (CbEBCR_BMSAMainPosCntStatOvrSwt_flg) {
    set_GeEBCR_BMSAMainPosCntStat_enum(CeEBCR_BMSAMainPosCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSAMainPosCntStat_enum(get_GeCAN1_MainPosCntStat_enum());
  }

  if (CbEBCR_BMSAMainNegCntStatOvrSwt_flg) {
    set_GeEBCR_BMSAMainNegCntStat_enum(CeEBCR_BMSAMainNegCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSAMainNegCntStat_enum(get_GeCAN1_MainNegCntStat_enum());
  }

  if (CbEBCR_BMSAPreChrgCntStatOvrSwt_flg) {
    set_GeEBCR_BMSAPreChrgCntStat_enum(CeEBCR_BMSAPreChrgCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSAPreChrgCntStat_enum(get_GeCAN1_PreChrgCntStat_enum());
  }

  if (CbEBCR_BMSAChargeCurrentMaxOvrSwt_flg) {
    set_GcEBCR_BMSAChargeCurrentMax_A(CcEBCR_BMSAChargeCurrentMaxOvr_A);
  } else {
    set_GcEBCR_BMSAChargeCurrentMax_A((real32_T)get_GcCAN1_ChargeCurrentMax_A());
  }

  if (CbEBCR_BMSAPackManufactureOvrSwt_flg) {
    set_GeEBCR_BMSAPackManufacture_enum(CeEBCR_BMSAPackManufactureOvr_enum);
  } else {
    set_GeEBCR_BMSAPackManufacture_enum(get_GeCAN1_PackManufacture_enum());
  }

  if (CbEBCR_BMSAPackBalanceTypeOvrSwt_flg) {
    set_GeEBCR_BMSAPackBalanceType_enum(CeEBCR_BMSAPackBalanceTypeOvr_enum);
  } else {
    set_GeEBCR_BMSAPackBalanceType_enum(get_GeCAN1_PackBalanceType_enum());
  }

  if (CbEBCR_BMSASysStatChkSumOvrSwt_flg) {
    set_GcEBCR_BMSASysStatChkSum_numb(CcEBCR_BMSASysStatChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSASysStatChkSum_numb(get_GcCAN1_BMSSysStatCheckSum_numb());
  }

  if (CbEBCR_BMSBSysStatAliveCntOvrSwt_flg) {
    set_GcEBCR_BMSBSysStatAliveCnt_numb(CcEBCR_BMSBSysStatAliveCntOvr_numb);
  } else {
    set_GcEBCR_BMSBSysStatAliveCnt_numb(get_GcCAN3_BMSSysStatAliveCounter_numb());
  }

  if (CbEBCR_BMSBHeatMagCntStatOvrSwt_flg) {
    set_GeEBCR_BMSBHeatMagCntStat_enum(CeEBCR_BMSBHeatMagCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSBHeatMagCntStat_enum(get_GeCAN3_HeatMagCntStat_enum());
  }

  if (CbEBCR_BMSBHVSysStatOvrSwt_flg) {
    set_GeEBCR_BMSBHVSysStat_enum(CeEBCR_BMSBHVSysStatOvr_enum);
  } else {
    set_GeEBCR_BMSBHVSysStat_enum(get_GeCAN3_HVSystemStatus_enum());
  }

  if (CbEBCR_BMSBFaultLevelOvrSwt_flg) {
    set_GeEBCR_BMSBFaultLevel_enum(CeEBCR_BMSBFaultLevelOvr_enum);
  } else {
    set_GeEBCR_BMSBFaultLevel_enum(get_GeCAN3_BMSFaultLevel_enum());
  }

  if (CbEBCR_BMSBISODetStatOvrSwt_flg) {
    set_GeEBCR_BMSBISODetStat_enum(CeEBCR_BMSBISODetStatOvr_enum);
  } else {
    set_GeEBCR_BMSBISODetStat_enum(get_GeCAN3_IsoDetStat_enum());
  }

  if (CbEBCR_BMSBHVShutdownReqOvrSwt_flg) {
    set_GbEBCR_BMSBHVShutdownReq_flg(CbEBCR_BMSBHVShutdownReqOvr_flg);
  } else {
    set_GbEBCR_BMSBHVShutdownReq_flg(get_GbCAN3_HVShutdownReq_flg());
  }

  if (CbEBCR_BMSBChrgVoltMaxOvrSwt_flg) {
    set_GcEBCR_BMSBChrgVoltMax_V(CcEBCR_BMSBChrgVoltMaxOvr_V);
  } else {
    set_GcEBCR_BMSBChrgVoltMax_V((real32_T)get_GcCAN3_ChargeVoltMax_V());
  }

  if (CbEBCR_BMSBHCUPwrCtrlOvrSwt_flg) {
    set_GbEBCR_BMSBHCUPwrCtrl_flg(CbEBCR_BMSBHCUPwrCtrlOvr_flg);
  } else {
    set_GbEBCR_BMSBHCUPwrCtrl_flg(get_GbCAN3_HCUPowerCtrl_flg());
  }

  if (CbEBCR_BMSBHeatModeSelOvrSwt_flg) {
    set_GeEBCR_BMSBHeatModeSel_enum(CeEBCR_BMSBHeatModeSelOvr_enum);
  } else {
    set_GeEBCR_BMSBHeatModeSel_enum(get_GeCAN3_HeatModeSelect_enum());
  }

  if (CbEBCR_BMSBMainPosCntStatOvrSwt_flg) {
    set_GeEBCR_BMSBMainPosCntStat_enum(CeEBCR_BMSBMainPosCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSBMainPosCntStat_enum(get_GeCAN3_MainPosCntStat_enum());
  }

  if (CbEBCR_BMSBMainNegCntStatOvrSwt_flg) {
    set_GeEBCR_BMSBMainNegCntStat_enum(CeEBCR_BMSBMainNegCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSBMainNegCntStat_enum(get_GeCAN3_MainNegCntStat_enum());
  }

  if (CbEBCR_BMSBPreChrgCntStatOvrSwt_flg) {
    set_GeEBCR_BMSBPreChrgCntStat_enum(CeEBCR_BMSBPreChrgCntStatOvr_enum);
  } else {
    set_GeEBCR_BMSBPreChrgCntStat_enum(get_GeCAN3_PreChrgCntStat_enum());
  }

  if (CbEBCR_BMSBChargeCurrentMaxOvrSwt_flg) {
    set_GcEBCR_BMSBChargeCurrentMax_A(CcEBCR_BMSBChargeCurrentMaxOvr_A);
  } else {
    set_GcEBCR_BMSBChargeCurrentMax_A((real32_T)get_GcCAN3_ChargeCurrentMax_A());
  }

  if (CbEBCR_BMSBPackManufactureOvrSwt_flg) {
    set_GeEBCR_BMSBPackManufacture_enum(CeEBCR_BMSBPackManufactureOvr_enum);
  } else {
    set_GeEBCR_BMSBPackManufacture_enum(get_GeCAN3_PackManufacture_enum());
  }

  if (CbEBCR_BMSBPackBalanceTypeOvrSwt_flg) {
    set_GeEBCR_BMSBPackBalanceType_enum(CeEBCR_BMSBPackBalanceTypeOvr_enum);
  } else {
    set_GeEBCR_BMSBPackBalanceType_enum(get_GeCAN3_PackBalanceType_enum());
  }

  if (CbEBCR_BMSBSysStatChkSumOvrSwt_flg) {
    set_GcEBCR_BMSBSysStatChkSum_numb(CcEBCR_BMSBSysStatChkSumOvr_numb);
  } else {
    set_GcEBCR_BMSBSysStatChkSum_numb(get_GcCAN3_BMSSysStatCheckSum_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCR_BMS_Temp_18152701_10ms_at_outport_1' */
void EBCR_BMS_Temp_18152701_10ms(void)
{
  if (CbEBCR_BMSAMinBatTmpOvrSwt_flg) {
    set_GcEBCR_BMSAMinBatTmp_C(CcEBCR_BMSAMinBatTmpOvr_C);
  } else {
    set_GcEBCR_BMSAMinBatTmp_C((real32_T)get_GcCAN1_MinBatTmp_C() - 40.0F);
  }

  if (CbEBCR_BMSAMinCellTempNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMinCellTempNumb_numb(CcEBCR_BMSAMinCellTempNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMinCellTempNumb_numb(get_GcCAN1_MinCellTempNumb_numb());
  }

  if (CbEBCR_BMSAMaxBatTmpOvrSwt_flg) {
    set_GcEBCR_BMSAMaxBatTmp_C(CcEBCR_BMSAMaxBatTmpOvr_C);
  } else {
    set_GcEBCR_BMSAMaxBatTmp_C((real32_T)get_GcCAN1_MaxBatTmp_C() - 40.0F);
  }

  if (CbEBCR_BMSAMaxCellTempNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMaxCellTempNumb_numb(CcEBCR_BMSAMaxCellTempNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMaxCellTempNumb_numb(get_GcCAN1_MaxCellTempNumb_numb());
  }

  if (CbEBCR_BMSAMaxTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMaxTempBatNumb_numb(CcEBCR_BMSAMaxTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMaxTempBatNumb_numb(get_GcCAN1_BMSMaxTempBatteryNumber_numb());
  }

  if (CbEBCR_BMSAMinTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSAMinTempBatNumb_numb(CcEBCR_BMSAMinTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSAMinTempBatNumb_numb(get_GcCAN1_BMSMinTempBatteryNumber_numb());
  }

  if (CbEBCR_BMSAHeatSetTmpOvrSwt_flg) {
    set_GcEBCR_BMSAHeatSetTmp_C(CcEBCR_BMSAHeatSetTmpOvr_C);
  } else {
    set_GcEBCR_BMSAHeatSetTmp_C((real32_T)get_GcCAN1_HeatSetTmp_C() - 40.0F);
  }

  if (CbEBCR_BMSBMinBatTmpOvrSwt_flg) {
    set_GcEBCR_BMSBMinBatTmp_C(CcEBCR_BMSBMinBatTmpOvr_C);
  } else {
    set_GcEBCR_BMSBMinBatTmp_C((real32_T)get_GcCAN3_MinBatTmp_C() - 40.0F);
  }

  if (CbEBCR_BMSBMinCellTempNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMinCellTempNumb_numb(CcEBCR_BMSBMinCellTempNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMinCellTempNumb_numb(get_GcCAN3_MinCellTempNumb_numb());
  }

  if (CbEBCR_BMSBMaxBatTmpOvrSwt_flg) {
    set_GcEBCR_BMSBMaxBatTmp_C(CcEBCR_BMSBMaxBatTmpOvr_C);
  } else {
    set_GcEBCR_BMSBMaxBatTmp_C((real32_T)get_GcCAN3_MaxBatTmp_C() - 40.0F);
  }

  if (CbEBCR_BMSBMaxCellTempNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMaxCellTempNumb_numb(CcEBCR_BMSBMaxCellTempNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMaxCellTempNumb_numb(get_GcCAN3_MaxCellTempNumb_numb());
  }

  if (CbEBCR_BMSBMaxTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMaxTempBatNumb_numb(CcEBCR_BMSBMaxTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMaxTempBatNumb_numb(get_GcCAN3_BMSMaxTempBatteryNumber_numb());
  }

  if (CbEBCR_BMSBMinTempBatNumbOvrSwt_flg) {
    set_GcEBCR_BMSBMinTempBatNumb_numb(CcEBCR_BMSBMinTempBatNumbOvr_numb);
  } else {
    set_GcEBCR_BMSBMinTempBatNumb_numb(get_GcCAN3_BMSMinTempBatteryNumber_numb());
  }

  if (CbEBCR_BMSBHeatSetTmpOvrSwt_flg) {
    set_GcEBCR_BMSBHeatSetTmp_C(CcEBCR_BMSBHeatSetTmpOvr_C);
  } else {
    set_GcEBCR_BMSBHeatSetTmp_C((real32_T)get_GcCAN3_HeatSetTmp_C() - 40.0F);
  }
}

/* Model initialize function */
void EBCR_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
