/*
 * File: EACM_Cal.c
 *
 * Code generated for Simulink model 'EACM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 18:44:55 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EACM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEACM_AGunStartCheckForCardOvrSwt_flg = 0;
volatile boolean_T CbEACM_AGunStartCheckForCardOvr_flg = 0;/* A枪向CCV发送鉴权请求
                                                              0:无; 1:开始 */
volatile boolean_T CbEACM_AGunUserStopForCardOvrSwt_flg = 0;
volatile boolean_T CbEACM_AGunUserStopForCardOvr_flg = 0;/* A枪向CCV发送停止鉴权请求
                                                            0:无; 1:开始 */
volatile boolean_T CbEACM_BGunStartCheckForCardOvrSwt_flg = 0;
volatile boolean_T CbEACM_BGunStartCheckForCardOvr_flg = 0;/* B枪向CCV发送鉴权请求
                                                              0:无; 1:开始 */
volatile boolean_T CbEACM_BGunUserStopForCardOvrSwt_flg = 0;
volatile boolean_T CbEACM_BGunUserStopForCardOvr_flg = 0;/* B枪向CCV发送停止鉴权请求
                                                            0:无; 1:开始 */
volatile boolean_T CbEACM_CCU1MCVCardTypeOvrSwt_flg = 0;
volatile boolean_T CbEACM_CCU1TFDAuthReqOvrSwt_flg = 0;
volatile boolean_T CbEACM_CCU1TFDAuthReqOvr_flg = 0;/* 向TBOX发送鉴权请求 */
volatile boolean_T CbEACM_CCU2MCVCardTypeOvrSwt_flg = 0;
volatile boolean_T CbEACM_CCU2TFDAuthReqOvrSwt_flg = 0;
volatile boolean_T CbEACM_CCU2TFDAuthReqOvr_flg = 0;/* 向TBOX发送鉴权请求 */
volatile boolean_T CbEACM_ChrgFeeOvrSwt_flg = 0;
volatile boolean_T CbEACM_LeftCheckSuccessOvrSwt_flg = 0;
volatile boolean_T CbEACM_LeftCheckSuccessOvr_flg = 0;/* 向CHM发送充电请求 */
volatile boolean_T CbEACM_LeftStaRFIDCardUIDOvrSwt_flg = 0;
volatile boolean_T CbEACM_LeftStopChargeSuccessOvrSwt_flg = 0;
volatile boolean_T CbEACM_LeftStopChargeSuccessOvr_flg = 0;/* 向CHM发送停止充电请求 */
volatile boolean_T CbEACM_PrePaymentOvrSwt_flg = 0;
volatile boolean_T CbEACM_RightCheckSuccessOvrSwt_flg = 0;
volatile boolean_T CbEACM_RightCheckSuccessOvr_flg = 0;/* 向CHM发送充电请求 */
volatile boolean_T CbEACM_RightStaRFIDCardUIDOvrSwt_flg = 0;
volatile boolean_T CbEACM_RightStopChargeSuccessOvrSwt_flg = 0;
volatile boolean_T CbEACM_RightStopChargeSuccessOvr_flg = 0;/* 向CHM发送停止充电请求 */
volatile real32_T CcEACM_ChrgFeeOvr_rmb = 0.0F;/* 费率 */
volatile uint8_T CcEACM_LeftStaRFIDCardUIDOvr_numb = 0U;/* 左枪RFID卡UID号 */
volatile real32_T CcEACM_PrePaymentOvr_rmb = 0.0F;/* 预扣费 */
volatile uint8_T CcEACM_RightStaRFIDCardUIDOvr_numb = 0U;/* 右枪RFID卡UID号 */
volatile uint8_T CeEACM_CCU1MCVCardTypeOvr_enum = 0U;/* 左枪鉴权方式
                                                        0:无; 1:信用卡;
                                                        2:RFID卡;  */
volatile uint8_T CeEACM_CCU2MCVCardTypeOvr_enum = 0U;/* 右枪鉴权方式
                                                        0:无; 1:信用卡;
                                                        2:RFID卡;  */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
