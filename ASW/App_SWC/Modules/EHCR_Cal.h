/*
 * File: EHCR_Cal.h
 *
 * Code generated for Simulink model 'EHCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 14:52:44 2020
 */

#ifndef RTW_HEADER_EHCR_Cal_h_
#define RTW_HEADER_EHCR_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEHCR_HCUCntStatOvrSwt_flg;/* 热管理继电器状态 */
extern volatile boolean_T CbEHCR_HCUCntStatOvr_flg;/* 热管理继电器状态 */
extern volatile boolean_T CbEHCR_HCUFaultSevtyStatOvrSwt_flg;/* 热管理系统故障等级 */
extern volatile boolean_T CbEHCR_HCUFaultStaOvrSwt_flg;/* 热管理系统故障 */
extern volatile boolean_T CbEHCR_HCUPowerReqOvrSwt_flg;/* 热管理上下电请求 */
extern volatile boolean_T CbEHCR_HCUPowerReqOvr_flg;/* 热管理上下电请求 */
extern volatile boolean_T CbEHCR_HCUSystemModeOvrSwt_flg;/* 热管理工作模式反馈 */
extern volatile boolean_T CbEHCR_HCUWaterTmpOutOvrSwt_flg;/* 热管理机组出水口温度 */
extern volatile boolean_T CbHCR_HCUWaterTmpInOvrSwt_flg;/* 热管理机组进水口温度 */
extern volatile boolean_T CcEHCR_HCUEnvTempAOvrSwt_flg;/* 整机环境温度 */
extern volatile real32_T CcEHCR_HCUEnvTempAOvr_C;/* 整机环境温度 */
extern volatile boolean_T CcEHCR_HCUPowerDemandOvrSwt_flg;/* 热管理需求功率 */
extern volatile real32_T CcEHCR_HCUPowerDemandOvr_Kw;/* 热管理需求功率 */
extern volatile real32_T CcEHCR_HCUWaterTmpInOvr_C;/* 热管理机组进水口温度 */
extern volatile real32_T CcEHCR_HCUWaterTmpOutOvr_C;/* 热管理机组出水口温度 */
extern volatile uint8_T CeEHCR_HCUFaultSevtyStatOvr_enum;/* 热管理系统故障等级 */
extern volatile uint8_T CeEHCR_HCUFaultStatOvr_enum;/* 热管理系统故障 */
extern volatile uint8_T CeEHCR_HCUSystemModeOvr_enum;/* 热管理工作模式反馈 */

#endif                                 /* RTW_HEADER_EHCR_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
