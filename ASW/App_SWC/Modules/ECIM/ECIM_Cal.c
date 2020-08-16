/*
 * File: ECIM_Cal.c
 *
 * Code generated for Simulink model 'ECIM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jun 10 09:42:58 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECIM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECIM_GunAEMSAlreadyOvrSwt_flg = 0;/* GbECIM_GunAEMSAlready_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbECIM_GunAEMSAlreadyOvr_flg = 0;/* GbECIM_GunAEMSAlready_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbECIM_GunAExpOutputVoltOvrSwt_flg = 0;/* GcECIM_GunAExpOutputVolt_V��Ӧ��OverWrite��־ */
volatile boolean_T CbECIM_GunAIntactModeOvrSwt_flg = 0;/* GeECIM_GunAIntactMode_enum��Ӧ��OverWrite��־ */
volatile boolean_T CbECIM_GunBEMSAlreadyOvrSwt_flg = 0;/* GbECIM_GunBEMSAlready_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbECIM_GunBEMSAlreadyOvr_flg = 0;/* GbECIM_GunBEMSAlready_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbECIM_GunBExpOutputVoltOvrSwt_flg = 0;/* GcECIM_GunBExpOutputVolt_V��Ӧ��OverWrite��־ */
volatile boolean_T CbECIM_GunBIntactModeOvrSwt_flg = 0;/* GeECIM_GunBIntactMode_enum��Ӧ��OverWrite��־ */
volatile real32_T CcECIM_GunABCPToBCLDebVolt_V = 200.0F;
volatile uint16_T CcECIM_GunAEMSReadyDebTime_ms = 300U;/* ǹA׼�������궨ʱ�� */
volatile real32_T CcECIM_GunAExpOutputVoltOvr_V = 0.0F;/* GcECIM_GunAExpOutputVolt_V��Ӧ��OverWriteֵ */
volatile real32_T CcECIM_GunAMaxOutputVoltDiff_V = 20.0F;/* ǹA�����ѹƫ��궨ֵ */
volatile real32_T CcECIM_GunAOfflineToISODebVolt_V = 200.0F;
volatile uint8_T CcECIM_GunAUnloadToBCPDebTime_ms = 200U;
volatile real32_T CcECIM_GunAUnloadToBCPDebVolt_V = 150.0F;
volatile real32_T CcECIM_GunBBCPToBCLDebVolt_V = 200.0F;
volatile uint16_T CcECIM_GunBEMSReadyDebTime_ms = 300U;/* ǹB׼�������궨ʱ�� */
volatile real32_T CcECIM_GunBExpOutputVoltOvr_V = 0.0F;/* GcECIM_GunBExpOutputVolt_V��Ӧ��OverWriteֵ */
volatile real32_T CcECIM_GunBMaxOutputVoltDiff_V = 20.0F;/* ǹB�����ѹƫ��궨ֵ */
volatile real32_T CcECIM_GunBOfflineToISODebVolt_V = 200.0F;
volatile uint8_T CcECIM_GunBUnloadToBCPDebTime_ms = 200U;
volatile real32_T CcECIM_GunBUnloadToBCPDebVolt_V = 150.0F;
volatile real32_T CcECIM_Volt200_V = 200.0F;
volatile uint8_T CeECIM_GunAIntactModeOvr_enum = 0U;/* GeECIM_GunAIntactMode_enum��Ӧ��OverWriteֵ */
volatile uint8_T CeECIM_GunBIntactModeOvr_enum = 0U;/* GeECIM_GunBIntactMode_enum��Ӧ��OverWriteֵ */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
