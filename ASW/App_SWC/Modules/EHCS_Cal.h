/*
 * File: EHCS_Cal.h
 *
 * Code generated for Simulink model 'EHCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 16:01:07 2020
 */

#ifndef RTW_HEADER_EHCS_Cal_h_
#define RTW_HEADER_EHCS_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEHCS_BMSMaxBatTmpOvrSwt_flg;/* BMS最大电芯温度 */
extern volatile boolean_T CbEHCS_BMSMaxBatWaterTmpOutOvrSwt_flg;/* 电池包出水口最高温度 */
extern volatile boolean_T CbEHCS_BMSMinBatTmpOvrSwt_flg;/* BMS最小电芯温度 */
extern volatile boolean_T CbEHCS_BMSMinBatWaterTmpInOvrSwt_flg;/* 电池包进水口最低温度 */
extern volatile boolean_T CbEHCS_EMSHeatModeSelectOvrSwt_flg;/* 热管理模式选择 */
extern volatile boolean_T CbEHCS_EMSHeatSetTmpOvrSwt_flg;/* 热管理设定目标温度 */
extern volatile boolean_T CbEHCS_EMSMaxPowerModelWaterTmpOutOvrSwt_flg;/* 功率模块出水口最高温度 */
extern volatile boolean_T CbEHCS_EMSMinPowerModelWaterTmpInOvrSwt_flg;/* 功率模块出水口最低温度 */
extern volatile uint8_T CcEHCS_BMSMaxBatTmpOvr_C;/* BMS最大电芯温度 */
extern volatile uint8_T CcEHCS_BMSMaxBatWaterTmpOutOvr_C;/* 电池包出水口最高温度 */
extern volatile uint8_T CcEHCS_BMSMinBatTmpOvr_C;/* BMS最小电芯温度 */
extern volatile uint8_T CcEHCS_BMSMinBatWaterTmpInOvr_C;/* 电池包进水口最低温度 */
extern volatile uint8_T CcEHCS_EMSHeatSetTmpOvr_C;/* 热管理设定目标温度 */
extern volatile uint8_T CcEHCS_EMSMaxPowerModelWaterTmpOutOvr_C;/* 功率模块出水口最高温度 */
extern volatile uint8_T CcEHCS_EMSMinPowerModelWaterTmpInOvr_C;/* 功率模块出水口最低温度 */
extern volatile uint8_T CeEHCS_EMSHeatModeSelectOvr_enum;/* 热管理模式选择 */

#endif                                 /* RTW_HEADER_EHCS_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
