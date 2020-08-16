/*
 * File: EACT_Cal.h
 *
 * Code generated for Simulink model 'EACT'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 15 14:12:21 2020
 */

#ifndef RTW_HEADER_EACT_Cal_h_
#define RTW_HEADER_EACT_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvrSwt_flg;/* KA4控制指令：
                                                                0：断开；1：闭合 */
extern volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvr_flg;/* KA4控制指令：
                                                             0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ACCtrCmdOvrSwt_flg;/* 交流继电器（KA2）控制指令：
                                                       0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ACCtrCmdOvr_flg;/* 交流继电器（KA2）控制指令：
                                                    0：断开；1：闭合 */
extern volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvrSwt_flg;/* KA1控制指令：
                                                               0：断开；1：闭合 */
extern volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvr_flg;/* KA1控制指令：
                                                            0：断开；1：闭合 */
extern volatile boolean_T CbEACT_AdvPowCtrCmdOvrSwt_flg;/* KA3控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_AdvPowCtrCmdOvr_flg;/* KA3控制指令：
                                                        0：断开；1：闭合 */
extern volatile boolean_T CbEACT_BCChrgNegCtrCmdOvrSwt_flg;/* BothCross继电器负极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_BCChrgNegCtrCmdOvr_flg;/* BothCross继电器负极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_BCChrgPosCtrCmdOvrSwt_flg;/* BothCross继电器正极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_BCChrgPosCtrCmdOvr_flg;/* BothCross继电器正极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgANegCtrCmdOvrSwt_flg;/* A枪ACDC跨接继电器负极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgANegCtrCmdOvr_flg;/* A枪ACDC跨接继电器负极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgAPosCtrCmdOvrSwt_flg;/* A枪ACDC跨接继电器正极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgAPosCtrCmdOvr_flg;/* A枪ACDC跨接继电器正极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgBNegCtrCmdOvrSwt_flg;/* B枪ACDC跨接继电器负极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgBNegCtrCmdOvr_flg;/* B枪ACDC跨接继电器负极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgBPosCtrCmdOvrSwt_flg;/* B枪ACDC跨接继电器正极控制指令：
                                                              0：断开；1：闭合 */
extern volatile boolean_T CbEACT_CChrgBPosCtrCmdOvr_flg;/* B枪ACDC跨接继电器正极控制指令：
                                                           0：断开；1：闭合 */
extern volatile boolean_T CbEACT_KA5CtrCmdOvrSwt_flg;/* KA5控制指令：
                                                        0：断开；1：闭合 */
extern volatile boolean_T CbEACT_KA5CtrCmdOvr_flg;/* KA5控制指令：
                                                     0：断开；1：闭合 */
extern volatile boolean_T CbEACT_PACKAToHVSNCtrOvrSwt_flg;/* PACKA到HVS N级继电器
                                                             0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKAToHVSNCtrOvr_flg;/* PACKA到HVS N级继电器
                                                          0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKAToHVSPCtrOvrSwt_flg;/* PACKA到HVS P级继电器
                                                             0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKAToHVSPCtrOvr_flg;/* PACKA到HVS P级继电器
                                                          0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKBToHVSNCtrOvrSwt_flg;/* PACKB到HVS N级继电器
                                                             0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKBToHVSNCtrOvr_flg;/* PACKB到HVS N级继电器
                                                          0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKBToHVSPCtrOvrSwt_flg;/* PACKB到HVS P级继电器
                                                             0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_PACKBToHVSPCtrOvr_flg;/* PACKB到HVS P级继电器
                                                          0:断开; 1:吸合 */
extern volatile boolean_T CbEACT_ReChrgANegCtrCmdOvrSwt_flg;/* A枪补能继电器负极控制指令：
                                                               0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgANegCtrCmdOvr_flg;/* A枪补能继电器负极控制指令：
                                                            0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvrSwt_flg;/* A枪补能继电器正极控制指令：
                                                               0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvr_flg;/* A枪补能继电器正极控制指令：
                                                            0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvrSwt_flg;/* B枪补能继电器负极控制指令：
                                                               0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvr_flg;/* B枪补能继电器负极控制指令：
                                                            0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvrSwt_flg;/* B枪补能继电器正极控制指令：
                                                               0：断开；1：闭合 */
extern volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvr_flg;/* B枪补能继电器正极控制指令：
                                                            0：断开；1：闭合 */
extern volatile uint16_T CcEACT_DelayTime3000_ms;
extern volatile uint32_T CcEACT_DelayTime3_min;
extern volatile uint16_T CcEACT_DelayTime50_ms;

#endif                                 /* RTW_HEADER_EACT_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
