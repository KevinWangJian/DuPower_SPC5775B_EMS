/*
 * File: EBIM_Cal.h
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 */

#ifndef RTW_HEADER_EBIM_Cal_h_
#define RTW_HEADER_EBIM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEBIM_BMSAHVCtrCmdOvrSwt_flg;/* BMS A继电器闭合指令的overwrite标定开关 */
extern volatile boolean_T CbEBIM_BMSBHVCtrCmdOvrSwt_flg;/* BMS B继电器闭合指令的overwrite标定开关 */
extern volatile boolean_T CbEBIM_PackAAllowedReChrgOvrSwt_flg;/* PackA允许补能
                                                                 0：不允许补能
                                                                 1：允许补能 */
extern volatile boolean_T CbEBIM_PackAAllowedReChrgOvr_flg;/* PackA允许补能
                                                              0：不允许补能
                                                              1：允许补能 */
extern volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvrSwt_flg;/* PackA不允许放电标志
                                                                      0：Reserve
                                                                      1：不允许放电 */
extern volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvr_flg;/* PackA不允许放电标志
                                                                    0：Reserve
                                                                    1：不允许放电 */
extern volatile boolean_T CbEBIM_PackAOutCurrReqOvrSwt_flg;/* PackA请求输出电流 */
extern volatile boolean_T CbEBIM_PackAOutVoltReqOvrSwt_flg;/* PackA请求输出电压 */
extern volatile boolean_T CbEBIM_PackBAllowedReChrgOvrSwt_flg;/* PackA允许补能
                                                                 0：不允许补能
                                                                 1：允许补能 */
extern volatile boolean_T CbEBIM_PackBAllowedReChrgOvr_flg;/* PackA允许补能
                                                              0：不允许补能
                                                              1：允许补能 */
extern volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvrSwt_flg;/* PackA不允许放电标志
                                                                      0：Reserve
                                                                      1：不允许放电 */
extern volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvr_flg;/* PackA不允许放电标志
                                                                    0：Reserve
                                                                    1：不允许放电 */
extern volatile boolean_T CbEBIM_PackBOutCurrReqOvrSwt_flg;/* PackA请求输出电流 */
extern volatile boolean_T CbEBIM_PackBOutVoltReqOvrSwt_flg;/* PackA请求输出电压 */
extern volatile uint8_T CcEBIM_BMSASOC10_pct;/* BIM模块PACKA强制下电SOC阈值 */
extern volatile uint8_T CcEBIM_BMSBSOC10_pct;/* BIM模块PACKB强制下电SOC阈值 */
extern volatile real32_T CcEBIM_PackAOutCurrReqOvr_A;/* PackA请求输出电流 */
extern volatile real32_T CcEBIM_PackAOutVoltReqOvr_V;/* PackA请求输出电压 */
extern volatile real32_T CcEBIM_PackBOutCurrReqOvr_A;/* PackA请求输出电流 */
extern volatile real32_T CcEBIM_PackBOutVoltReqOvr_V;/* PackA请求输出电压 */
extern volatile uint8_T CeEBIM_BMSAHVCtrCmdOvr_enum;/* BMS A继电器闭合指令的overwrite标定值
                                                       0:res
                                                       1:闭合
                                                       2:断开 */
extern volatile uint8_T CeEBIM_BMSBHVCtrCmdOvr_enum;/* BMS B继电器闭合指令的overwrite标定值
                                                       0:res
                                                       1:闭合
                                                       2:断开 */

#endif                                 /* RTW_HEADER_EBIM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
