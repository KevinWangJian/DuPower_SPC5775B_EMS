/*
 * File: EMSM_Cal.h
 *
 * Code generated for Simulink model 'EMSM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 14:32:04 2020
 */

#ifndef RTW_HEADER_EMSM_Cal_h_
#define RTW_HEADER_EMSM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEMSM_12VSelfCheckSuccessOvrSwt_flg;/* 12V自检成功标志位
                                                                  0：未成功;1：成功 */
extern volatile boolean_T CbEMSM_12VSelfCheckSuccessOvr_flg;/* 12V自检成功标志位
                                                               0：未成功;1：成功 */
extern volatile boolean_T CbEMSM_24VSelfCheckSuccessOvrSwt_flg;/* 自检控制继电器指令
                                                                  0：继电器断开;1：继电器闭合 */
extern volatile boolean_T CbEMSM_24VSelfCheckSuccessOvr_flg;/* 自检控制继电器指令
                                                               0：继电器断开;1：继电器闭合 */
extern volatile boolean_T CbEMSM_ECUCheckSuccessOvrSwt_flg;/* AFC初始化成功标志位
                                                              0:未成功; 1:成功 */
extern volatile boolean_T CbEMSM_ECUCheckSuccessOvr_flg;/* AFC初始化成功标志位
                                                           0:未成功; 1:成功 */
extern volatile boolean_T CbEMSM_EMSCheckSuccessOvrSwt_flg;/* EMS初始化成功标志位
                                                              0:未成功; 1:成功 */
extern volatile boolean_T CbEMSM_EMSCheckSuccessOvr_flg;/* EMS初始化成功标志位
                                                           0:未成功; 1:成功 */
extern volatile boolean_T CbEMSM_SafeCheckSuccessOvrSwt_flg;/* 安全门检测成功标志位
                                                               0：未成功;1：成功 */
extern volatile boolean_T CbEMSM_SafeCheckSuccessOvr_flg;/* 安全门检测成功标志位
                                                            0：未成功;1：成功 */
extern volatile boolean_T CbEMSM_SelfCheckCtrCmdOvrSwt_flg;/* 自检控制继电器指令
                                                              0：继电器断开;1：继电器闭合 */
extern volatile boolean_T CbEMSM_SelfCheckCtrCmdOvr_flg;/* 自检控制继电器指令
                                                           0：继电器断开;1：继电器闭合 */
extern volatile boolean_T CbEMSM_SleepModeEnableOvrSwt_flg;/* 进入休眠模式标志位
                                                              0：未休眠;1：休眠 */
extern volatile boolean_T CbEMSM_SleepModeEnableOvr_flg;/* 进入休眠模式标志位
                                                           0：未休眠;1：休眠 */
extern volatile uint16_T CcEMSM_DelayTime2000_ms;
extern volatile uint32_T CcEMSM_DelayTime30_min;
extern volatile uint32_T CcEMSM_DelayTime5000_ms;
extern volatile uint32_T CcEMSM_DelayTime60000_ms;

#endif                                 /* RTW_HEADER_EMSM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
