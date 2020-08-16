/*
 * File: ETCS_Cal.c
 *
 * Code generated for Simulink model 'ETCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:52:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ETCS_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbETCS_TFDAuthRequestOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCCU1OcppReasonEnumOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCCU1OpChrPointStatusEnumOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCCU2OcppReasonEnumOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCCU2OpChrPointStatusEnumOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCCUIndexOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardLengOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum1OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum2OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum3OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum4OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum5OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum6OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum7OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardNum8OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDCardbalanceOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDDCWhEnergeOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDDCWhindexOvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber1OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber2OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber3OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber4OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber5OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber6OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEACmeterSerialNumber7OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber1OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber2OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber3OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber4OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber5OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber6OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEDCmeterSerialNumber7OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEmeterType1OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEmeterType2OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDEmeterType3OvrSwt_flg = 0;
volatile boolean_T CbETCS_TFDPasswordOvrSwt_flg = 0;
volatile uint8_T CcETCS_TFDAuthRequestOvr_numb = 0U;/* 初始值为1（可标定） */
volatile uint8_T CcETCS_TFDAuthRequest_numb = 1U;/* 初始值为1（可标定） */
volatile uint8_T CcETCS_TFDCCUIndexOvr_numb = 0U;/* 1:左枪鉴权请求 2：右枪鉴权请求 */
volatile uint8_T CcETCS_TFDCardLengOvr_numb = 0U;/* 初始值为8（可标定） */
volatile uint8_T CcETCS_TFDCardLeng_numb = 8U;/* 初始值为8（可标定） */
volatile uint8_T CcETCS_TFDCardNum1Ovr_numb = 0U;/* RFID卡UID号1 */
volatile uint8_T CcETCS_TFDCardNum2Ovr_numb = 0U;/* RFID卡UID号2 */
volatile uint8_T CcETCS_TFDCardNum3Ovr_numb = 0U;/* RFID卡UID号3 */
volatile uint8_T CcETCS_TFDCardNum4Ovr_numb = 0U;/* RFID卡UID号4 */
volatile uint8_T CcETCS_TFDCardNum5Ovr_numb = 0U;/* RFID卡UID号5 */
volatile uint8_T CcETCS_TFDCardNum6Ovr_numb = 0U;/* RFID卡UID号6 */
volatile uint8_T CcETCS_TFDCardNum7Ovr_numb = 0U;/* RFID卡UID号7 */
volatile uint8_T CcETCS_TFDCardNum8Ovr_numb = 0U;/* RFID卡UID号8 */
volatile uint32_T CcETCS_TFDCardbalanceOvr_rmb = 0U;/* 预扣费 */
volatile uint32_T CcETCS_TFDDCWhEnergeOvr_Wh = 0U;/* 电表值 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber1Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber2Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber3Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber4Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber5Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber6Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber7Ovr_numb = 0U;/* CCU1 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber1Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber2Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber3Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber4Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber5Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber6Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber7Ovr_numb = 0U;/* CCU2 LEM电表串号 */
volatile uint32_T CcETCS_TFDEmeterType1Ovr_numb = 0U;/* "LEM_" */
volatile uint32_T CcETCS_TFDEmeterType2Ovr_numb = 0U;/* "DCBM" */
volatile uint32_T CcETCS_TFDEmeterType3Ovr_numb = 0U;/* " v1" */
volatile uint32_T CcETCS_TFDPasswordOvr_rmb = 0U;/* remap信号，费率 */
volatile uint8_T CeETCS_TFDCCU1OcppReasonEnumOvr_enum = 0U;/* CCU1停止原因 */
volatile uint8_T CeETCS_TFDCCU1OpChrPointStatusEnumOvr_enum = 0U;/* CCU1工作状态 */
volatile uint8_T CeETCS_TFDCCU2OcppReasonEnumOvr_enum = 0U;/* CCU2停止原因 */
volatile uint8_T CeETCS_TFDCCU2OpChrPointStatusEnumOvr_enum = 0U;/* CCU2工作状态 */
volatile uint8_T CeETCS_TFDDCWhindexOvr_enum = 0U;/* 枪编号 */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
