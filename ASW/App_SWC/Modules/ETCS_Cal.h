/*
 * File: ETCS_Cal.h
 *
 * Code generated for Simulink model 'ETCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:52:51 2020
 */

#ifndef RTW_HEADER_ETCS_Cal_h_
#define RTW_HEADER_ETCS_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbETCS_TFDAuthRequestOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCCU1OcppReasonEnumOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCCU1OpChrPointStatusEnumOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCCU2OcppReasonEnumOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCCU2OpChrPointStatusEnumOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCCUIndexOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardLengOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum1OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum2OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum3OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum4OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum5OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum6OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum7OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardNum8OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDCardbalanceOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDDCWhEnergeOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDDCWhindexOvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber1OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber2OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber3OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber4OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber5OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber6OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEACmeterSerialNumber7OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber1OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber2OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber3OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber4OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber5OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber6OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEDCmeterSerialNumber7OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEmeterType1OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEmeterType2OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDEmeterType3OvrSwt_flg;
extern volatile boolean_T CbETCS_TFDPasswordOvrSwt_flg;
extern volatile uint8_T CcETCS_TFDAuthRequestOvr_numb;/* 初始值为1（可标定） */
extern volatile uint8_T CcETCS_TFDAuthRequest_numb;/* 初始值为1（可标定） */
extern volatile uint8_T CcETCS_TFDCCUIndexOvr_numb;/* 1:左枪鉴权请求 2：右枪鉴权请求 */
extern volatile uint8_T CcETCS_TFDCardLengOvr_numb;/* 初始值为8（可标定） */
extern volatile uint8_T CcETCS_TFDCardLeng_numb;/* 初始值为8（可标定） */
extern volatile uint8_T CcETCS_TFDCardNum1Ovr_numb;/* RFID卡UID号1 */
extern volatile uint8_T CcETCS_TFDCardNum2Ovr_numb;/* RFID卡UID号2 */
extern volatile uint8_T CcETCS_TFDCardNum3Ovr_numb;/* RFID卡UID号3 */
extern volatile uint8_T CcETCS_TFDCardNum4Ovr_numb;/* RFID卡UID号4 */
extern volatile uint8_T CcETCS_TFDCardNum5Ovr_numb;/* RFID卡UID号5 */
extern volatile uint8_T CcETCS_TFDCardNum6Ovr_numb;/* RFID卡UID号6 */
extern volatile uint8_T CcETCS_TFDCardNum7Ovr_numb;/* RFID卡UID号7 */
extern volatile uint8_T CcETCS_TFDCardNum8Ovr_numb;/* RFID卡UID号8 */
extern volatile uint32_T CcETCS_TFDCardbalanceOvr_rmb;/* 预扣费 */
extern volatile uint32_T CcETCS_TFDDCWhEnergeOvr_Wh;/* 电表值 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber1Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber2Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber3Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber4Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber5Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber6Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEACmeterSerialNumber7Ovr_numb;/* CCU1 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber1Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber2Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber3Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber4Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber5Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber6Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEDCmeterSerialNumber7Ovr_numb;/* CCU2 LEM电表串号 */
extern volatile uint32_T CcETCS_TFDEmeterType1Ovr_numb;/* "LEM_" */
extern volatile uint32_T CcETCS_TFDEmeterType2Ovr_numb;/* "DCBM" */
extern volatile uint32_T CcETCS_TFDEmeterType3Ovr_numb;/* " v1" */
extern volatile uint32_T CcETCS_TFDPasswordOvr_rmb;/* remap信号，费率 */
extern volatile uint8_T CeETCS_TFDCCU1OcppReasonEnumOvr_enum;/* CCU1停止原因 */
extern volatile uint8_T CeETCS_TFDCCU1OpChrPointStatusEnumOvr_enum;/* CCU1工作状态 */
extern volatile uint8_T CeETCS_TFDCCU2OcppReasonEnumOvr_enum;/* CCU2停止原因 */
extern volatile uint8_T CeETCS_TFDCCU2OpChrPointStatusEnumOvr_enum;/* CCU2工作状态 */
extern volatile uint8_T CeETCS_TFDDCWhindexOvr_enum;/* 枪编号 */

#endif                                 /* RTW_HEADER_ETCS_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
