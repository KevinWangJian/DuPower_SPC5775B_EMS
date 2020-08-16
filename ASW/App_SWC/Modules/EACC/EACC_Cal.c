/*
 * File: EACC_Cal.c
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 13:26:06 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EACC_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile real32_T CaEACC_ACDCATempPwrTable_kw[7] = { 0.0F, 0.0F, 20.0F, 20.0F,
  10.0F, 0.0F, 0.0F } ;                /* Pwr-Table */
 
volatile real32_T CaEACC_ACDCAWaterTemp_C[7] = { -50.0F, -21.0F, -20.0F, 39.0F,
  40.0F, 50.0F, 80.0F } ;              /* Temp-Table */
 
volatile real32_T CaEACC_ACDCBTempPwrTable_kw[7] = { 0.0F, 0.0F, 20.0F, 20.0F,
  10.0F, 0.0F, 0.0F } ;                /* Pwr-Table */
 
volatile real32_T CaEACC_ACDCBWaterTemp_C[7] = { -50.0F, -21.0F, -20.0F, 39.0F,
  40.0F, 50.0F, 80.0F } ;              /* Temp-Table */
 
volatile boolean_T CbEACC_ACDCAOutCurrReqOvrSwt_flg = 0;/* GcEACC_ACDCAOutCurrReq_A应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCAOutVoltReqOvrSwt_flg = 0;/* GcEACC_ACDCAOutVoltReq_V应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCAPwrCmdOvrSwt_flg = 0;/* GbEACC_ACDCAPwrCmd_flg应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCAPwrCmdOvr_flg = 0;/* GbEACC_ACDCAPwrCmd_flg对应的OverWrite值 */
volatile boolean_T CbEACC_ACDCARunModeOvrSwt_flg = 0;/* GeEACC_ACDCARunMode_enum对应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCBOutCurrReqOvrSwt_flg = 0;/* GcEACC_ACDCBOutCurrReq_A应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCBOutVoltReqOvrSwt_flg = 0;/* GcEACC_ACDCBOutVoltReq_V应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCBPwrCmdOvrSwt_flg = 0;/* GbEACC_ACDCBPwrCmd_flg应的OverWrite标志 */
volatile boolean_T CbEACC_ACDCBPwrCmdOvr_flg = 0;/* GbEACC_ACDCBPwrCmd_flg对应的OverWrite值 */
volatile boolean_T CbEACC_ACDCBRunModeOvrSwt_flg = 0;/* GeEACC_ACDCBRunMode_enum应的OverWrite标志 */
volatile uint8_T CcEACC_ACDCACalCurr_A = 50U;/* AC/DCA标定电流 */
volatile real32_T CcEACC_ACDCACurrRatio_R = 1.0F;/* AC/DCA标定电流系数 */
volatile real32_T CcEACC_ACDCAOutCurrReqOvr_A = 0.0F;/* GcEACC_ACDCAOutCurrReq_A对应的OverWrite值 */
volatile real32_T CcEACC_ACDCAOutVoltReqOvr_V = 0.0F;/* GcEACC_ACDCAOutVoltReq_V对应的OverWrite值 */
volatile uint8_T CcEACC_ACDCAPwrOffDelayT_ms = 60U;/* AC/DCA关机&#xA0;Delay时间 */
volatile uint8_T CcEACC_ACDCAPwrOnDelayT_ms = 60U;/* AC/DCA开机&#xA0;Delay时间 */
volatile uint8_T CcEACC_ACDCASum_numb = 1U;/* AC/DCA数量 */
volatile uint8_T CcEACC_ACDCBCalCurr_A = 50U;/* AC/DCB标定电流 */
volatile real32_T CcEACC_ACDCBCurrRatio_R = 1.0F;/* AC/DCB标定电流系数 */
volatile real32_T CcEACC_ACDCBOutCurrReqOvr_A = 0.0F;/* GcEACC_ACDCBOutCurrReq_A对应的OverWrite值 */
volatile real32_T CcEACC_ACDCBOutVoltReqOvr_V = 0.0F;/* GcEACC_ACDCBOutVoltReq_V对应的OverWrite值 */
volatile uint8_T CcEACC_ACDCBSum_numb = 1U;/* AC/DCB数量 */
volatile uint16_T CcEACC_AOffToStdbDelayT_ms = 6000U;/* ACDCA工作状态offline跳standby Delay时间 */
volatile uint8_T CcEACC_APChrgToStdbDelayT_ms = 60U;/* ACDCA工作状态PreChrg跳standby Delay时间 */
volatile uint16_T CcEACC_AStdbToOffDelayT_ms = 1000U;/* ACDCA工作状态standby跳offline Delay时间 */
volatile uint8_T CcEACC_AllowACDCAWorkFltLvl_numb = 2U;/* 允许ACDCA工作的故障等级 */
volatile uint8_T CcEACC_AllowACDCBWorkFltLvl_numb = 2U;/* 允许ACDCB工作的故障等级 */
volatile uint16_T CcEACC_BOffToStdbDelayT_ms = 6000U;/* ACDCB工作状态offline跳standby Delay时间 */
volatile uint8_T CcEACC_BPChrgToStdbDelayT_ms = 60U;/* ACDCB工作状态PreChrg跳standby Delay时间 */
volatile uint16_T CcEACC_BStdbToOffDelayT_ms = 1000U;/* ACDCB工作状态standby跳offline Delay时间 */
volatile real32_T CcEACC_Ratio1000_R = 1000.0F;
volatile uint8_T CeEACC_ACDCARunModeOvr_enum = 0U;/* GeEACC_ACDCARunMode_enum对应的OverWrite值 */
volatile uint8_T CeEACC_ACDCBRunModeOvr_enum = 0U;/* GeEACC_ACDCBRunMode_enum对应的OverWrite值 */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
