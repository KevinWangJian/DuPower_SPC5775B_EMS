/*
 * File: EHCR_Cal.c
 *
 * Code generated for Simulink model 'EHCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 14:52:44 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EHCR_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEHCR_HCUCntStatOvrSwt_flg = 0;/* 热管理继电器状态 */
volatile boolean_T CbEHCR_HCUCntStatOvr_flg = 0;/* 热管理继电器状态 */
volatile boolean_T CbEHCR_HCUFaultSevtyStatOvrSwt_flg = 0;/* 热管理系统故障等级 */
volatile boolean_T CbEHCR_HCUFaultStaOvrSwt_flg = 0;/* 热管理系统故障 */
volatile boolean_T CbEHCR_HCUPowerReqOvrSwt_flg = 0;/* 热管理上下电请求 */
volatile boolean_T CbEHCR_HCUPowerReqOvr_flg = 0;/* 热管理上下电请求 */
volatile boolean_T CbEHCR_HCUSystemModeOvrSwt_flg = 0;/* 热管理工作模式反馈 */
volatile boolean_T CbEHCR_HCUWaterTmpOutOvrSwt_flg = 0;/* 热管理机组出水口温度 */
volatile boolean_T CbHCR_HCUWaterTmpInOvrSwt_flg = 0;/* 热管理机组进水口温度 */
volatile boolean_T CcEHCR_HCUEnvTempAOvrSwt_flg = 0;/* 整机环境温度 */
volatile real32_T CcEHCR_HCUEnvTempAOvr_C = 0.0F;/* 整机环境温度 */
volatile boolean_T CcEHCR_HCUPowerDemandOvrSwt_flg = 0;/* 热管理需求功率 */
volatile real32_T CcEHCR_HCUPowerDemandOvr_Kw = 0.0F;/* 热管理需求功率 */
volatile real32_T CcEHCR_HCUWaterTmpInOvr_C = 0.0F;/* 热管理机组进水口温度 */
volatile real32_T CcEHCR_HCUWaterTmpOutOvr_C = 0.0F;/* 热管理机组出水口温度 */
volatile uint8_T CeEHCR_HCUFaultSevtyStatOvr_enum = 0U;/* 热管理系统故障等级 */
volatile uint8_T CeEHCR_HCUFaultStatOvr_enum = 0U;/* 热管理系统故障 */
volatile uint8_T CeEHCR_HCUSystemModeOvr_enum = 0U;/* 热管理工作模式反馈 */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
