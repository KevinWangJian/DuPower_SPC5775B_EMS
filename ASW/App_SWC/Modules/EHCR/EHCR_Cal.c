/*
 * File: EHCR_Cal.c
 *
 * Code generated for Simulink model 'EHCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 14:52:44 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EHCR_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEHCR_HCUCntStatOvrSwt_flg = 0;/* �ȹ���̵���״̬ */
volatile boolean_T CbEHCR_HCUCntStatOvr_flg = 0;/* �ȹ���̵���״̬ */
volatile boolean_T CbEHCR_HCUFaultSevtyStatOvrSwt_flg = 0;/* �ȹ���ϵͳ���ϵȼ� */
volatile boolean_T CbEHCR_HCUFaultStaOvrSwt_flg = 0;/* �ȹ���ϵͳ���� */
volatile boolean_T CbEHCR_HCUPowerReqOvrSwt_flg = 0;/* �ȹ������µ����� */
volatile boolean_T CbEHCR_HCUPowerReqOvr_flg = 0;/* �ȹ������µ����� */
volatile boolean_T CbEHCR_HCUSystemModeOvrSwt_flg = 0;/* �ȹ�����ģʽ���� */
volatile boolean_T CbEHCR_HCUWaterTmpOutOvrSwt_flg = 0;/* �ȹ�������ˮ���¶� */
volatile boolean_T CbHCR_HCUWaterTmpInOvrSwt_flg = 0;/* �ȹ�������ˮ���¶� */
volatile boolean_T CcEHCR_HCUEnvTempAOvrSwt_flg = 0;/* ���������¶� */
volatile real32_T CcEHCR_HCUEnvTempAOvr_C = 0.0F;/* ���������¶� */
volatile boolean_T CcEHCR_HCUPowerDemandOvrSwt_flg = 0;/* �ȹ��������� */
volatile real32_T CcEHCR_HCUPowerDemandOvr_Kw = 0.0F;/* �ȹ��������� */
volatile real32_T CcEHCR_HCUWaterTmpInOvr_C = 0.0F;/* �ȹ�������ˮ���¶� */
volatile real32_T CcEHCR_HCUWaterTmpOutOvr_C = 0.0F;/* �ȹ�������ˮ���¶� */
volatile uint8_T CeEHCR_HCUFaultSevtyStatOvr_enum = 0U;/* �ȹ���ϵͳ���ϵȼ� */
volatile uint8_T CeEHCR_HCUFaultStatOvr_enum = 0U;/* �ȹ���ϵͳ���� */
volatile uint8_T CeEHCR_HCUSystemModeOvr_enum = 0U;/* �ȹ�����ģʽ���� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
