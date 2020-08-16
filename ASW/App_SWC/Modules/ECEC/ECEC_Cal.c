/*
 * File: ECEC_Cal.c
 *
 * Code generated for Simulink model 'ECEC'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 15:32:52 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECEC_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECEC_ACWhAfterChgEnergyOvrSwt_flg = 0;
volatile boolean_T CbECEC_ACWhBeforeChgEnergyOvrSwt_flg = 0;
volatile boolean_T CbECEC_ACWhChargeEnergyOvrSwt_flg = 0;
volatile boolean_T CbECEC_ACWhComFaultOvrSwt_flg = 0;
volatile boolean_T CbECEC_ACWhComFaultOvr_flg = 0;
volatile boolean_T CbECEC_CCU1ChargeEnergyOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU1ChargeOverOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU1ChargeOverOvr_flg = 0;
volatile boolean_T CbECEC_CCU1ChargeStatusOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU1ElectricityCalFinishOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU1ElectricityCalFinishOvr_flg = 0;
volatile boolean_T CbECEC_CCU1ElectricityRateOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU2ChargeEnergyOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU2ChargeOverOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU2ChargeOverOvr_flg = 0;
volatile boolean_T CbECEC_CCU2ChargeStatusOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU2ElectricityCalFinishOvrSwt_flg = 0;
volatile boolean_T CbECEC_CCU2ElectricityCalFinishOvr_flg = 0;
volatile boolean_T CbECEC_CCU2ElectricityRateOvrSwt_flg = 0;
volatile real32_T CcECEC_ACWhAfterChgEnergyOvr_kwH = 0.0F;
volatile real32_T CcECEC_ACWhBeforeChgEnergyOvr_kwH = 0.0F;
volatile real32_T CcECEC_ACWhChargeEnergyOvr_kwH = 0.0F;
volatile real32_T CcECEC_CCU1ChargeEnergyOvr_kwH = 0.0F;
volatile real32_T CcECEC_CCU1ElectricityRateOvr_rmb = 0.0F;
volatile real32_T CcECEC_CCU2ChargeEnergyOvr_kwH = 0.0F;
volatile real32_T CcECEC_CCU2ElectricityRateOvr_rmb = 0.0F;
volatile uint8_T CeECEC_CCU1ChargeStatusOvr_enum = 0U;
volatile uint8_T CeECEC_CCU2ChargeStatusOvr_enum = 0U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
