/*
 * File: EMSM_Cal.c
 *
 * Code generated for Simulink model 'EMSM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 14:32:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EMSM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEMSM_12VSelfCheckSuccessOvrSwt_flg = 0;/* 12V自检成功标志位
                                                               0：未成功;1：成功 */
volatile boolean_T CbEMSM_12VSelfCheckSuccessOvr_flg = 0;/* 12V自检成功标志位
                                                            0：未成功;1：成功 */
volatile boolean_T CbEMSM_24VSelfCheckSuccessOvrSwt_flg = 0;/* 自检控制继电器指令
                                                               0：继电器断开;1：继电器闭合 */
volatile boolean_T CbEMSM_24VSelfCheckSuccessOvr_flg = 0;/* 自检控制继电器指令
                                                            0：继电器断开;1：继电器闭合 */
volatile boolean_T CbEMSM_ECUCheckSuccessOvrSwt_flg = 0;/* AFC初始化成功标志位
                                                           0:未成功; 1:成功 */
volatile boolean_T CbEMSM_ECUCheckSuccessOvr_flg = 0;/* AFC初始化成功标志位
                                                        0:未成功; 1:成功 */
volatile boolean_T CbEMSM_EMSCheckSuccessOvrSwt_flg = 0;/* EMS初始化成功标志位
                                                           0:未成功; 1:成功 */
volatile boolean_T CbEMSM_EMSCheckSuccessOvr_flg = 0;/* EMS初始化成功标志位
                                                        0:未成功; 1:成功 */
volatile boolean_T CbEMSM_SafeCheckSuccessOvrSwt_flg = 0;/* 安全门检测成功标志位
                                                            0：未成功;1：成功 */
volatile boolean_T CbEMSM_SafeCheckSuccessOvr_flg = 0;/* 安全门检测成功标志位
                                                         0：未成功;1：成功 */
volatile boolean_T CbEMSM_SelfCheckCtrCmdOvrSwt_flg = 0;/* 自检控制继电器指令
                                                           0：继电器断开;1：继电器闭合 */
volatile boolean_T CbEMSM_SelfCheckCtrCmdOvr_flg = 0;/* 自检控制继电器指令
                                                        0：继电器断开;1：继电器闭合 */
volatile boolean_T CbEMSM_SleepModeEnableOvrSwt_flg = 0;/* 进入休眠模式标志位
                                                           0：未休眠;1：休眠 */
volatile boolean_T CbEMSM_SleepModeEnableOvr_flg = 0;/* 进入休眠模式标志位
                                                        0：未休眠;1：休眠 */
volatile uint16_T CcEMSM_DelayTime2000_ms = 2000U;
volatile uint32_T CcEMSM_DelayTime30_min = 1800000U;
volatile uint32_T CcEMSM_DelayTime5000_ms = 5000U;
volatile uint32_T CcEMSM_DelayTime60000_ms = 60000U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
