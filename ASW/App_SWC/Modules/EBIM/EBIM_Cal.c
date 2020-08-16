/*
 * File: EBIM_Cal.c
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EBIM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEBIM_BMSAHVCtrCmdOvrSwt_flg = 0;/* BMS A继电器闭合指令的overwrite标定开关 */
volatile boolean_T CbEBIM_BMSBHVCtrCmdOvrSwt_flg = 0;/* BMS B继电器闭合指令的overwrite标定开关 */
volatile boolean_T CbEBIM_PackAAllowedReChrgOvrSwt_flg = 0;/* PackA允许补能
                                                              0：不允许补能
                                                              1：允许补能 */
volatile boolean_T CbEBIM_PackAAllowedReChrgOvr_flg = 0;/* PackA允许补能
                                                           0：不允许补能
                                                           1：允许补能 */
volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvrSwt_flg = 0;/* PackA不允许放电标志
                                                                    0：Reserve
                                                                    1：不允许放电 */
volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvr_flg = 0;/* PackA不允许放电标志
                                                                 0：Reserve
                                                                 1：不允许放电 */
volatile boolean_T CbEBIM_PackAOutCurrReqOvrSwt_flg = 0;/* PackA请求输出电流 */
volatile boolean_T CbEBIM_PackAOutVoltReqOvrSwt_flg = 0;/* PackA请求输出电压 */
volatile boolean_T CbEBIM_PackBAllowedReChrgOvrSwt_flg = 0;/* PackA允许补能
                                                              0：不允许补能
                                                              1：允许补能 */
volatile boolean_T CbEBIM_PackBAllowedReChrgOvr_flg = 0;/* PackA允许补能
                                                           0：不允许补能
                                                           1：允许补能 */
volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvrSwt_flg = 0;/* PackA不允许放电标志
                                                                    0：Reserve
                                                                    1：不允许放电 */
volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvr_flg = 0;/* PackA不允许放电标志
                                                                 0：Reserve
                                                                 1：不允许放电 */
volatile boolean_T CbEBIM_PackBOutCurrReqOvrSwt_flg = 0;/* PackA请求输出电流 */
volatile boolean_T CbEBIM_PackBOutVoltReqOvrSwt_flg = 0;/* PackA请求输出电压 */
volatile uint8_T CcEBIM_BMSASOC10_pct = 10U;/* BIM模块PACKA强制下电SOC阈值 */
volatile uint8_T CcEBIM_BMSBSOC10_pct = 10U;/* BIM模块PACKB强制下电SOC阈值 */
volatile real32_T CcEBIM_PackAOutCurrReqOvr_A = 0.0F;/* PackA请求输出电流 */
volatile real32_T CcEBIM_PackAOutVoltReqOvr_V = 0.0F;/* PackA请求输出电压 */
volatile real32_T CcEBIM_PackBOutCurrReqOvr_A = 0.0F;/* PackA请求输出电流 */
volatile real32_T CcEBIM_PackBOutVoltReqOvr_V = 0.0F;/* PackA请求输出电压 */
volatile uint8_T CeEBIM_BMSAHVCtrCmdOvr_enum = 1U;/* BMS A继电器闭合指令的overwrite标定值
                                                     0:res
                                                     1:闭合
                                                     2:断开 */
volatile uint8_T CeEBIM_BMSBHVCtrCmdOvr_enum = 1U;/* BMS B继电器闭合指令的overwrite标定值
                                                     0:res
                                                     1:闭合
                                                     2:断开 */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
