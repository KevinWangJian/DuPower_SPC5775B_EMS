/*
 * File: EHCS_Cal.c
 *
 * Code generated for Simulink model 'EHCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 16:01:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EHCS_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEHCS_BMSMaxBatTmpOvrSwt_flg = 0;/* BMS����о�¶� */
volatile boolean_T CbEHCS_BMSMaxBatWaterTmpOutOvrSwt_flg = 0;/* ��ذ���ˮ������¶� */
volatile boolean_T CbEHCS_BMSMinBatTmpOvrSwt_flg = 0;/* BMS��С��о�¶� */
volatile boolean_T CbEHCS_BMSMinBatWaterTmpInOvrSwt_flg = 0;/* ��ذ���ˮ������¶� */
volatile boolean_T CbEHCS_EMSHeatModeSelectOvrSwt_flg = 0;/* �ȹ���ģʽѡ�� */
volatile boolean_T CbEHCS_EMSHeatSetTmpOvrSwt_flg = 0;/* �ȹ����趨Ŀ���¶� */
volatile boolean_T CbEHCS_EMSMaxPowerModelWaterTmpOutOvrSwt_flg = 0;/* ����ģ���ˮ������¶� */
volatile boolean_T CbEHCS_EMSMinPowerModelWaterTmpInOvrSwt_flg = 0;/* ����ģ���ˮ������¶� */
volatile uint8_T CcEHCS_BMSMaxBatTmpOvr_C = 0U;/* BMS����о�¶� */
volatile uint8_T CcEHCS_BMSMaxBatWaterTmpOutOvr_C = 0U;/* ��ذ���ˮ������¶� */
volatile uint8_T CcEHCS_BMSMinBatTmpOvr_C = 0U;/* BMS��С��о�¶� */
volatile uint8_T CcEHCS_BMSMinBatWaterTmpInOvr_C = 0U;/* ��ذ���ˮ������¶� */
volatile uint8_T CcEHCS_EMSHeatSetTmpOvr_C = 0U;/* �ȹ����趨Ŀ���¶� */
volatile uint8_T CcEHCS_EMSMaxPowerModelWaterTmpOutOvr_C = 0U;/* ����ģ���ˮ������¶� */
volatile uint8_T CcEHCS_EMSMinPowerModelWaterTmpInOvr_C = 0U;/* ����ģ���ˮ������¶� */
volatile uint8_T CeEHCS_EMSHeatModeSelectOvr_enum = 0U;/* �ȹ���ģʽѡ�� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
