/*
 * File: EACC_Cal.c
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 13:26:06 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EACC_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile real32_T CaEACC_ACDCATempPwrTable_kw[7] = { 0.0F, 0.0F, 20.0F, 20.0F,
  10.0F, 0.0F, 0.0F } ;                /* Pwr-Table */
 
volatile real32_T CaEACC_ACDCAWaterTemp_C[7] = { -50.0F, -21.0F, -20.0F, 39.0F,
  40.0F, 50.0F, 80.0F } ;              /* Temp-Table */
 
volatile real32_T CaEACC_ACDCBTempPwrTable_kw[7] = { 0.0F, 0.0F, 20.0F, 20.0F,
  10.0F, 0.0F, 0.0F } ;                /* Pwr-Table */
 
volatile real32_T CaEACC_ACDCBWaterTemp_C[7] = { -50.0F, -21.0F, -20.0F, 39.0F,
  40.0F, 50.0F, 80.0F } ;              /* Temp-Table */
 
volatile boolean_T CbEACC_ACDCAOutCurrReqOvrSwt_flg = 0;/* GcEACC_ACDCAOutCurrReq_AӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCAOutVoltReqOvrSwt_flg = 0;/* GcEACC_ACDCAOutVoltReq_VӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCAPwrCmdOvrSwt_flg = 0;/* GbEACC_ACDCAPwrCmd_flgӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCAPwrCmdOvr_flg = 0;/* GbEACC_ACDCAPwrCmd_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbEACC_ACDCARunModeOvrSwt_flg = 0;/* GeEACC_ACDCARunMode_enum��Ӧ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCBOutCurrReqOvrSwt_flg = 0;/* GcEACC_ACDCBOutCurrReq_AӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCBOutVoltReqOvrSwt_flg = 0;/* GcEACC_ACDCBOutVoltReq_VӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCBPwrCmdOvrSwt_flg = 0;/* GbEACC_ACDCBPwrCmd_flgӦ��OverWrite��־ */
volatile boolean_T CbEACC_ACDCBPwrCmdOvr_flg = 0;/* GbEACC_ACDCBPwrCmd_flg��Ӧ��OverWriteֵ */
volatile boolean_T CbEACC_ACDCBRunModeOvrSwt_flg = 0;/* GeEACC_ACDCBRunMode_enumӦ��OverWrite��־ */
volatile uint8_T CcEACC_ACDCACalCurr_A = 50U;/* AC/DCA�궨���� */
volatile real32_T CcEACC_ACDCACurrRatio_R = 1.0F;/* AC/DCA�궨����ϵ�� */
volatile real32_T CcEACC_ACDCAOutCurrReqOvr_A = 0.0F;/* GcEACC_ACDCAOutCurrReq_A��Ӧ��OverWriteֵ */
volatile real32_T CcEACC_ACDCAOutVoltReqOvr_V = 0.0F;/* GcEACC_ACDCAOutVoltReq_V��Ӧ��OverWriteֵ */
volatile uint8_T CcEACC_ACDCAPwrOffDelayT_ms = 60U;/* AC/DCA�ػ�&#xA0;Delayʱ�� */
volatile uint8_T CcEACC_ACDCAPwrOnDelayT_ms = 60U;/* AC/DCA����&#xA0;Delayʱ�� */
volatile uint8_T CcEACC_ACDCASum_numb = 1U;/* AC/DCA���� */
volatile uint8_T CcEACC_ACDCBCalCurr_A = 50U;/* AC/DCB�궨���� */
volatile real32_T CcEACC_ACDCBCurrRatio_R = 1.0F;/* AC/DCB�궨����ϵ�� */
volatile real32_T CcEACC_ACDCBOutCurrReqOvr_A = 0.0F;/* GcEACC_ACDCBOutCurrReq_A��Ӧ��OverWriteֵ */
volatile real32_T CcEACC_ACDCBOutVoltReqOvr_V = 0.0F;/* GcEACC_ACDCBOutVoltReq_V��Ӧ��OverWriteֵ */
volatile uint8_T CcEACC_ACDCBSum_numb = 1U;/* AC/DCB���� */
volatile uint16_T CcEACC_AOffToStdbDelayT_ms = 6000U;/* ACDCA����״̬offline��standby Delayʱ�� */
volatile uint8_T CcEACC_APChrgToStdbDelayT_ms = 60U;/* ACDCA����״̬PreChrg��standby Delayʱ�� */
volatile uint16_T CcEACC_AStdbToOffDelayT_ms = 1000U;/* ACDCA����״̬standby��offline Delayʱ�� */
volatile uint8_T CcEACC_AllowACDCAWorkFltLvl_numb = 2U;/* ����ACDCA�����Ĺ��ϵȼ� */
volatile uint8_T CcEACC_AllowACDCBWorkFltLvl_numb = 2U;/* ����ACDCB�����Ĺ��ϵȼ� */
volatile uint16_T CcEACC_BOffToStdbDelayT_ms = 6000U;/* ACDCB����״̬offline��standby Delayʱ�� */
volatile uint8_T CcEACC_BPChrgToStdbDelayT_ms = 60U;/* ACDCB����״̬PreChrg��standby Delayʱ�� */
volatile uint16_T CcEACC_BStdbToOffDelayT_ms = 1000U;/* ACDCB����״̬standby��offline Delayʱ�� */
volatile real32_T CcEACC_Ratio1000_R = 1000.0F;
volatile uint8_T CeEACC_ACDCARunModeOvr_enum = 0U;/* GeEACC_ACDCARunMode_enum��Ӧ��OverWriteֵ */
volatile uint8_T CeEACC_ACDCBRunModeOvr_enum = 0U;/* GeEACC_ACDCBRunMode_enum��Ӧ��OverWriteֵ */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
