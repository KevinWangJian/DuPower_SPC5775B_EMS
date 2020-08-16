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
volatile uint8_T CcETCS_TFDAuthRequestOvr_numb = 0U;/* ��ʼֵΪ1���ɱ궨�� */
volatile uint8_T CcETCS_TFDAuthRequest_numb = 1U;/* ��ʼֵΪ1���ɱ궨�� */
volatile uint8_T CcETCS_TFDCCUIndexOvr_numb = 0U;/* 1:��ǹ��Ȩ���� 2����ǹ��Ȩ���� */
volatile uint8_T CcETCS_TFDCardLengOvr_numb = 0U;/* ��ʼֵΪ8���ɱ궨�� */
volatile uint8_T CcETCS_TFDCardLeng_numb = 8U;/* ��ʼֵΪ8���ɱ궨�� */
volatile uint8_T CcETCS_TFDCardNum1Ovr_numb = 0U;/* RFID��UID��1 */
volatile uint8_T CcETCS_TFDCardNum2Ovr_numb = 0U;/* RFID��UID��2 */
volatile uint8_T CcETCS_TFDCardNum3Ovr_numb = 0U;/* RFID��UID��3 */
volatile uint8_T CcETCS_TFDCardNum4Ovr_numb = 0U;/* RFID��UID��4 */
volatile uint8_T CcETCS_TFDCardNum5Ovr_numb = 0U;/* RFID��UID��5 */
volatile uint8_T CcETCS_TFDCardNum6Ovr_numb = 0U;/* RFID��UID��6 */
volatile uint8_T CcETCS_TFDCardNum7Ovr_numb = 0U;/* RFID��UID��7 */
volatile uint8_T CcETCS_TFDCardNum8Ovr_numb = 0U;/* RFID��UID��8 */
volatile uint32_T CcETCS_TFDCardbalanceOvr_rmb = 0U;/* Ԥ�۷� */
volatile uint32_T CcETCS_TFDDCWhEnergeOvr_Wh = 0U;/* ���ֵ */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber1Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber2Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber3Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber4Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber5Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber6Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEACmeterSerialNumber7Ovr_numb = 0U;/* CCU1 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber1Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber2Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber3Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber4Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber5Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber6Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEDCmeterSerialNumber7Ovr_numb = 0U;/* CCU2 LEM����� */
volatile uint32_T CcETCS_TFDEmeterType1Ovr_numb = 0U;/* "LEM_" */
volatile uint32_T CcETCS_TFDEmeterType2Ovr_numb = 0U;/* "DCBM" */
volatile uint32_T CcETCS_TFDEmeterType3Ovr_numb = 0U;/* " v1" */
volatile uint32_T CcETCS_TFDPasswordOvr_rmb = 0U;/* remap�źţ����� */
volatile uint8_T CeETCS_TFDCCU1OcppReasonEnumOvr_enum = 0U;/* CCU1ֹͣԭ�� */
volatile uint8_T CeETCS_TFDCCU1OpChrPointStatusEnumOvr_enum = 0U;/* CCU1����״̬ */
volatile uint8_T CeETCS_TFDCCU2OcppReasonEnumOvr_enum = 0U;/* CCU2ֹͣԭ�� */
volatile uint8_T CeETCS_TFDCCU2OpChrPointStatusEnumOvr_enum = 0U;/* CCU2����״̬ */
volatile uint8_T CeETCS_TFDDCWhindexOvr_enum = 0U;/* ǹ��� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
