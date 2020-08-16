/*
 * File: ECMM_Cal.c
 *
 * Code generated for Simulink model 'ECMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed May 20 17:27:26 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECMM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECMM_ChrgCtrAModeOvrSwt_flg = 0;/* GeECMM_ChrgCtrAMode_enum变量对应的OverWrite标志 */
volatile boolean_T CbECMM_ChrgCtrBModeOvrSwt_flg = 0;/* GeECMM_ChrgCtrBMode_enum变量对应的OverWrite标志 */
volatile uint8_T CcECMM_ABCChrgToIdleDelayT_ms = 20U;/* 充电控制状态A BothCrossChrg跳转Idle delay时间 */
volatile uint8_T CcECMM_ACChrgToIdleDelayT_ms = 20U;/* 充电控制状态A CrossChrg跳转Idle delay时间 */
volatile uint8_T CcECMM_AChrgToIdleDelayT_ms = 20U;/* 充电控制状态A Chrg跳转Idle delay时间 */
volatile uint8_T CcECMM_AIdleToBCChrgDelayT_ms = 200U;/* 充电控制状态A Idle跳转BothCrossChrg delay时间 */
volatile uint8_T CcECMM_AIdleToCChrgDelayT_ms = 200U;/* 充电控制状态A Idle跳转CrossChrg delay时间 */
volatile uint8_T CcECMM_AIdleToChrgDelayT_ms = 200U;/* 充电控制状态A Idle跳转Chrg delay时间 */
volatile uint8_T CcECMM_AIdleToOfflineDelayT_ms = 200U;/* 充电控制状态A Idle跳转offline delay时间 */
volatile uint8_T CcECMM_AIdleToReChrgDelayT_ms = 200U;/* 充电控制状态A Idle跳转ReChrg delay时间 */
volatile uint8_T CcECMM_AOfflineToIdleDelayT_ms = 200U;/* 充电控制状态A offline跳转Idle delay时间 */
volatile uint8_T CcECMM_AReChrgToIdleDelayT_ms = 20U;/* 充电控制状态A ReChrg跳转Idle delay时间 */
volatile uint8_T CcECMM_BBCChrgToIdleDelayT_ms = 20U;/* 充电控制状态B BothCrossChrg跳转Idle delay时间 */
volatile uint8_T CcECMM_BCChrgToIdleDelayT_ms = 20U;/* 充电控制状态B CrossChrg跳转Idle delay时间 */
volatile uint8_T CcECMM_BChrgToIdleDelayT_ms = 20U;/* 充电控制状态B Chrg跳转Idle delay时间 */
volatile uint8_T CcECMM_BIdleToBCChrgDelayT_ms = 200U;/* 充电控制状态B Idle跳转BothCrossChrg delay时间 */
volatile uint8_T CcECMM_BIdleToCChrgDelayT_ms = 200U;/* 充电控制状态B Idle跳转CrossChrg delay时间 */
volatile uint8_T CcECMM_BIdleToChrgDelayT_ms = 200U;/* 充电控制状态B Idle跳转Chrg delay时间 */
volatile uint8_T CcECMM_BIdleToOfflineDelayT_ms = 200U;/* 充电控制状态B Idle跳转offline delay时间 */
volatile uint8_T CcECMM_BIdleToReChrgDelayT_ms = 200U;/* 充电控制状态B Idle跳转ReChrg delay时间 */
volatile uint8_T CcECMM_BOfflineToIdleDelayT_ms = 200U;/* 充电控制状态B offline跳转Idle delay时间 */
volatile uint8_T CcECMM_BReChrgToIdleDelayT_ms = 20U;/* 充电控制状态B ReChrg跳转Idle delay时间 */
volatile uint8_T CeECMM_ChrgCtrAModeOvr_enum = 0U;/* GeECMM_ChrgCtrAMode_enum变量对应的OverWrite值 */
volatile uint8_T CeECMM_ChrgCtrBModeOvr_enum = 0U;/* GeECMM_ChrgCtrBMode_enum变量对应的OverWrite值 */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
