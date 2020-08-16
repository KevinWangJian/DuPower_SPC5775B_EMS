/*
 * File: EACT_Cal.c
 *
 * Code generated for Simulink model 'EACT'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 15 14:12:21 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EACT_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvrSwt_flg = 0;/* KA4控制指令：
                                                             0：断开；1：闭合 */
volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvr_flg = 0;/* KA4控制指令：
                                                          0：断开；1：闭合 */
volatile boolean_T CbEACT_ACCtrCmdOvrSwt_flg = 0;/* 交流继电器（KA2）控制指令：
                                                    0：断开；1：闭合 */
volatile boolean_T CbEACT_ACCtrCmdOvr_flg = 0;/* 交流继电器（KA2）控制指令：
                                                 0：断开；1：闭合 */
volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvrSwt_flg = 0;/* KA1控制指令：
                                                            0：断开；1：闭合 */
volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvr_flg = 0;/* KA1控制指令：
                                                         0：断开；1：闭合 */
volatile boolean_T CbEACT_AdvPowCtrCmdOvrSwt_flg = 0;/* KA3控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_AdvPowCtrCmdOvr_flg = 0;/* KA3控制指令：
                                                     0：断开；1：闭合 */
volatile boolean_T CbEACT_BCChrgNegCtrCmdOvrSwt_flg = 0;/* BothCross继电器负极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_BCChrgNegCtrCmdOvr_flg = 0;/* BothCross继电器负极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_BCChrgPosCtrCmdOvrSwt_flg = 0;/* BothCross继电器正极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_BCChrgPosCtrCmdOvr_flg = 0;/* BothCross继电器正极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgANegCtrCmdOvrSwt_flg = 0;/* A枪ACDC跨接继电器负极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgANegCtrCmdOvr_flg = 0;/* A枪ACDC跨接继电器负极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgAPosCtrCmdOvrSwt_flg = 0;/* A枪ACDC跨接继电器正极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgAPosCtrCmdOvr_flg = 0;/* A枪ACDC跨接继电器正极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgBNegCtrCmdOvrSwt_flg = 0;/* B枪ACDC跨接继电器负极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgBNegCtrCmdOvr_flg = 0;/* B枪ACDC跨接继电器负极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgBPosCtrCmdOvrSwt_flg = 0;/* B枪ACDC跨接继电器正极控制指令：
                                                           0：断开；1：闭合 */
volatile boolean_T CbEACT_CChrgBPosCtrCmdOvr_flg = 0;/* B枪ACDC跨接继电器正极控制指令：
                                                        0：断开；1：闭合 */
volatile boolean_T CbEACT_KA5CtrCmdOvrSwt_flg = 0;/* KA5控制指令：
                                                     0：断开；1：闭合 */
volatile boolean_T CbEACT_KA5CtrCmdOvr_flg = 0;/* KA5控制指令：
                                                  0：断开；1：闭合 */
volatile boolean_T CbEACT_PACKAToHVSNCtrOvrSwt_flg = 0;/* PACKA到HVS N级继电器
                                                          0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKAToHVSNCtrOvr_flg = 0;/* PACKA到HVS N级继电器
                                                       0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKAToHVSPCtrOvrSwt_flg = 0;/* PACKA到HVS P级继电器
                                                          0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKAToHVSPCtrOvr_flg = 0;/* PACKA到HVS P级继电器
                                                       0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKBToHVSNCtrOvrSwt_flg = 0;/* PACKB到HVS N级继电器
                                                          0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKBToHVSNCtrOvr_flg = 0;/* PACKB到HVS N级继电器
                                                       0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKBToHVSPCtrOvrSwt_flg = 0;/* PACKB到HVS P级继电器
                                                          0:断开; 1:吸合 */
volatile boolean_T CbEACT_PACKBToHVSPCtrOvr_flg = 0;/* PACKB到HVS P级继电器
                                                       0:断开; 1:吸合 */
volatile boolean_T CbEACT_ReChrgANegCtrCmdOvrSwt_flg = 0;/* A枪补能继电器负极控制指令：
                                                            0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgANegCtrCmdOvr_flg = 0;/* A枪补能继电器负极控制指令：
                                                         0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvrSwt_flg = 0;/* A枪补能继电器正极控制指令：
                                                            0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvr_flg = 0;/* A枪补能继电器正极控制指令：
                                                         0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvrSwt_flg = 0;/* B枪补能继电器负极控制指令：
                                                            0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvr_flg = 0;/* B枪补能继电器负极控制指令：
                                                         0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvrSwt_flg = 0;/* B枪补能继电器正极控制指令：
                                                            0：断开；1：闭合 */
volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvr_flg = 0;/* B枪补能继电器正极控制指令：
                                                         0：断开；1：闭合 */
volatile uint16_T CcEACT_DelayTime3000_ms = 3000U;
volatile uint32_T CcEACT_DelayTime3_min = 180000U;
volatile uint16_T CcEACT_DelayTime50_ms = 50U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
