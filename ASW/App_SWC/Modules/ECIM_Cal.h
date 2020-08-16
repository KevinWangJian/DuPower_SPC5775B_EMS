/*
 * File: ECIM_Cal.h
 *
 * Code generated for Simulink model 'ECIM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jun 10 09:42:58 2020
 */

#ifndef RTW_HEADER_ECIM_Cal_h_
#define RTW_HEADER_ECIM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbECIM_GunAEMSAlreadyOvrSwt_flg;/* GbECIM_GunAEMSAlready_flg对应的OverWrite标志 */
extern volatile boolean_T CbECIM_GunAEMSAlreadyOvr_flg;/* GbECIM_GunAEMSAlready_flg对应的OverWrite值 */
extern volatile boolean_T CbECIM_GunAExpOutputVoltOvrSwt_flg;/* GcECIM_GunAExpOutputVolt_V对应的OverWrite标志 */
extern volatile boolean_T CbECIM_GunAIntactModeOvrSwt_flg;/* GeECIM_GunAIntactMode_enum对应的OverWrite标志 */
extern volatile boolean_T CbECIM_GunBEMSAlreadyOvrSwt_flg;/* GbECIM_GunBEMSAlready_flg对应的OverWrite标志 */
extern volatile boolean_T CbECIM_GunBEMSAlreadyOvr_flg;/* GbECIM_GunBEMSAlready_flg对应的OverWrite值 */
extern volatile boolean_T CbECIM_GunBExpOutputVoltOvrSwt_flg;/* GcECIM_GunBExpOutputVolt_V对应的OverWrite标志 */
extern volatile boolean_T CbECIM_GunBIntactModeOvrSwt_flg;/* GeECIM_GunBIntactMode_enum对应的OverWrite标志 */
extern volatile real32_T CcECIM_GunABCPToBCLDebVolt_V;
extern volatile uint16_T CcECIM_GunAEMSReadyDebTime_ms;/* 枪A准备就绪标定时间 */
extern volatile real32_T CcECIM_GunAExpOutputVoltOvr_V;/* GcECIM_GunAExpOutputVolt_V对应的OverWrite值 */
extern volatile real32_T CcECIM_GunAMaxOutputVoltDiff_V;/* 枪A输出电压偏差标定值 */
extern volatile real32_T CcECIM_GunAOfflineToISODebVolt_V;
extern volatile uint8_T CcECIM_GunAUnloadToBCPDebTime_ms;
extern volatile real32_T CcECIM_GunAUnloadToBCPDebVolt_V;
extern volatile real32_T CcECIM_GunBBCPToBCLDebVolt_V;
extern volatile uint16_T CcECIM_GunBEMSReadyDebTime_ms;/* 枪B准备就绪标定时间 */
extern volatile real32_T CcECIM_GunBExpOutputVoltOvr_V;/* GcECIM_GunBExpOutputVolt_V对应的OverWrite值 */
extern volatile real32_T CcECIM_GunBMaxOutputVoltDiff_V;/* 枪B输出电压偏差标定值 */
extern volatile real32_T CcECIM_GunBOfflineToISODebVolt_V;
extern volatile uint8_T CcECIM_GunBUnloadToBCPDebTime_ms;
extern volatile real32_T CcECIM_GunBUnloadToBCPDebVolt_V;
extern volatile real32_T CcECIM_Volt200_V;
extern volatile uint8_T CeECIM_GunAIntactModeOvr_enum;/* GeECIM_GunAIntactMode_enum对应的OverWrite值 */
extern volatile uint8_T CeECIM_GunBIntactModeOvr_enum;/* GeECIM_GunBIntactMode_enum对应的OverWrite值 */

#endif                                 /* RTW_HEADER_ECIM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
