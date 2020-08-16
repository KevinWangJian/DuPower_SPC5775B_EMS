/*
 * File: EDCC_Cal.c
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 20:19:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EDCC_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile real32_T CaEDCC_DCDCAInVoltPwrTable_kw[10] = { 0.0F, 0.0F, 12.0F, 55.0F,
  55.0F, 60.0F, 60.0F, 6.0F, 3.0F, 0.0F } ;/* InVoltPwr-Table */
 
volatile real32_T CaEDCC_DCDCAInVoltTable_V[10] = { 0.0F, 249.9F, 250.0F, 450.0F,
  490.0F, 500.0F, 800.0F, 860.0F, 900.0F, 900.1F } ;/* InVolt-Table */
 
volatile real32_T CaEDCC_DCDCAOutVoltPwrTable_kw[8] = { 0.0F, 0.0F, 19.5F, 60.0F,
  60.0F, 6.0F, 2.0F, 0.0F } ;          /* OutVoltPwr-Table */
 
volatile real32_T CaEDCC_DCDCAOutVoltTable_V[8] = { 0.0F, 149.9F, 150.0F, 460.0F,
  800.0F, 860.0F, 920.0F, 920.1F } ;   /* OutVolt-Table */
 
volatile real32_T CaEDCC_DCDCATempPwrTable_kw[3] = { 60.0F, 60.0F, 0.0F } ;/* TempPwr-Table */
 
volatile real32_T CaEDCC_DCDCAWaterTemp_C[3] = { -20.0F, 40.0F, 50.0F } ;/* Temp-Table */
 
volatile real32_T CaEDCC_DCDCBInVoltPwrTable_kw[10] = { 0.0F, 0.0F, 12.0F, 55.0F,
  55.0F, 60.0F, 60.0F, 6.0F, 3.0F, 0.0F } ;/* InVoltPwr-Table */
 
volatile real32_T CaEDCC_DCDCBInVoltTable_V[10] = { 0.0F, 249.9F, 250.0F, 450.0F,
  490.0F, 500.0F, 800.0F, 860.0F, 900.0F, 900.1F } ;/* InVolt-Table */
 
volatile real32_T CaEDCC_DCDCBOutVoltPwrTable_kw[8] = { 0.0F, 0.0F, 19.5F, 60.0F,
  60.0F, 6.0F, 2.0F, 0.0F } ;          /* OutVoltPwr-Table */
 
volatile real32_T CaEDCC_DCDCBOutVoltTable_V[8] = { 0.0F, 149.9F, 150.0F, 460.0F,
  800.0F, 860.0F, 920.0F, 920.1F } ;   /* OutVolt-Table */
 
volatile real32_T CaEDCC_DCDCBTempPwrTable_kw[3] = { 60.0F, 60.0F, 0.0F } ;/* TempPwr-Table */
 
volatile real32_T CaEDCC_DCDCBWaterTemp_C[3] = { -20.0F, 40.0F, 50.0F } ;/* Temp-Table */
 
volatile boolean_T CbEDCC_DCDCAOutCurrReqOvrSwt_flg = 0;/* GcEDCC_DCDCAOutCurrReq_A��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCAOutVoltReqOvrSwt_flg = 0;/* GcEDCC_DCDCAOutVoltReq_V��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCAPwrCmdOvrSwt_flg = 0;/* GbEDCC_DCDCAPwrCmd_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCAPwrCmdOvr_flg = 0;/* GbEDCC_DCDCAPwrCmd_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbEDCC_DCDCARunModeOvrSwt_flg = 0;/* GeEDCC_DCDCARunMode_enum��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCAVoltBuildFltOvrSwt_flg = 0;/* GbEDCC_DCDCAVoltBuildFlt_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCAVoltBuildFltOvr_flg = 0;/* GbEDCC_DCDCAVoltBuildFlt_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbEDCC_DCDCBOutCurrReqOvrSwt_flg = 0;/* GcEDCC_DCDCBOutCurrReq_A��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCBOutVoltReqOvrSwt_flg = 0;/* GcEDCC_DCDCBOutVoltReq_V��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCBPwrCmdOvrSwt_flg = 0;/* GbEDCC_DCDCBPwrCmd_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCBPwrCmdOvr_flg = 0;/* GbEDCC_DCDCBPwrCmd_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbEDCC_DCDCBRunModeOvrSwt_flg = 0;/* GeEDCC_DCDCBRunMode_enum��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCBVoltBuildFltOvrSwt_flg = 0;/* GbEDCC_DCDCBVoltBuildFlt_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEDCC_DCDCBVoltBuildFltOvr_flg = 0;/* GbEDCC_DCDCBVoltBuildFlt_flg��Ӧ��OverWriteֵ */
volatile uint16_T CcEDCC_AOffToStdbDelayT_ms = 6000U;/* DCDCA����״̬offline��standby Delayʱ�� */
volatile uint16_T CcEDCC_AStdbToOffDelayT_ms = 500U;/* DCDCA����״̬standby��offline Delayʱ�� */
volatile uint8_T CcEDCC_AllowDCDCAWorkFltLvl_numb = 2U;/* ����DCDCA�����Ĺ��ϵȼ� */
volatile uint8_T CcEDCC_AllowDCDCBWorkFltLvl_numb = 2U;/* ����DCDCB�����Ĺ��ϵȼ� */
volatile uint16_T CcEDCC_BOffToStdbDelayT_ms = 6000U;/* DCDCB����״̬offline��standby Delayʱ�� */
volatile uint16_T CcEDCC_BStdbToOffDelayT_ms = 500U;/* DCDCB����״̬standby��offline Delayʱ�� */
volatile uint8_T CcEDCC_DCDCACalCurr_A = 122U;/* DC/DCA�궨���� */
volatile real32_T CcEDCC_DCDCAConvRatio_R = 1.0F;/* DC/DCAת��ϵ�� */
volatile real32_T CcEDCC_DCDCAOutCurrReqOvr_A = 0.0F;/* GcEDCC_DCDCAOutCurrReq_A��Ӧ��OverWriteֵ */
volatile real32_T CcEDCC_DCDCAOutVoltReqOvr_V = 0.0F;/* GcEDCC_DCDCAOutVoltReq_V��Ӧ��OverWriteֵ */
volatile uint8_T CcEDCC_DCDCAPwrOffDelayT_ms = 60U;/* DCDCA�ػ�&#xA0;Delay&#xA0;ʱ�� */
volatile uint8_T CcEDCC_DCDCAPwrOnDelayT_ms = 60U;/* DCDCA����&#xA0;Delay&#xA0;ʱ�� */
volatile uint8_T CcEDCC_DCDCASum_numb = 2U;/* DC/DCA���� */
volatile real32_T CcEDCC_DCDCAUnloadVolt_V = 60.0F;/* DC/DCAй�ŵ�ѹ */
volatile uint16_T CcEDCC_DCDCAVoltBuildDelayT_ms = 20000U;/* DCDCA��ѹ����Delayʱ�� */
volatile real32_T CcEDCC_DCDCAVoltRatio_R = 1.0F;/* DC/DCA��ѹϵ�� */
volatile uint8_T CcEDCC_DCDCBCalCurr_A = 122U;/* DC/DCB�궨���� */
volatile real32_T CcEDCC_DCDCBConvRatio_R = 1.0F;/* DC/DCBת��ϵ�� */
volatile real32_T CcEDCC_DCDCBOutCurrReqOvr_A = 0.0F;/* GcEDCC_DCDCBOutCurrReq_A��Ӧ��OverWriteֵ */
volatile real32_T CcEDCC_DCDCBOutVoltReqOvr_V = 0.0F;/* GcEDCC_DCDCBOutVoltReq_V��Ӧ��OverWriteֵ */
volatile uint8_T CcEDCC_DCDCBPwrOffDelayT_ms = 60U;/* DCDCB�ػ�&#xA0;Delay&#xA0;ʱ�� */
volatile uint8_T CcEDCC_DCDCBPwrOnDelayT_ms = 60U;/* DCDCB�ػ�&#xA0;Delay&#xA0;ʱ�� */
volatile uint8_T CcEDCC_DCDCBSum_numb = 2U;/* DC/DCB���� */
volatile real32_T CcEDCC_DCDCBUnloadVolt_V = 60.0F;/* DC/DCBй�ŵ�ѹ */
volatile uint16_T CcEDCC_DCDCBVoltBuildDelayT_ms = 20000U;/* DCDCB��ѹ����Delayʱ�� */
volatile real32_T CcEDCC_DCDCBVoltRatio_R = 1.0F;/* DC/DCB��ѹϵ�� */
volatile real32_T CcEDCC_Ratio1000_R = 1000.0F;
volatile uint8_T CeEDCC_DCDCARunModeOvr_enum = 0U;/* GeEDCC_DCDCARunMode_enum��Ӧ��OverWriteֵ */
volatile uint8_T CeEDCC_DCDCBRunModeOvr_enum = 0U;/* GeEDCC_DCDCBRunMode_enum��Ӧ��OverWriteֵ */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
