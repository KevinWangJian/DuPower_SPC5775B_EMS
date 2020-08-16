/*
 * File: EDCC_Cal.h
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:05:01 2020
 */

#ifndef RTW_HEADER_EDCC_Cal_h_
#define RTW_HEADER_EDCC_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile real32_T CaEDCC_DCDCAInVoltPwrTable_kw[10];/* InVoltPwr-Table */
extern volatile real32_T CaEDCC_DCDCAInVoltTable_V[10];/* InVolt-Table */
extern volatile real32_T CaEDCC_DCDCAOutVoltPwrTable_kw[8];/* OutVoltPwr-Table */
extern volatile real32_T CaEDCC_DCDCAOutVoltTable_V[8];/* OutVolt-Table */
extern volatile real32_T CaEDCC_DCDCATempPwrTable_kw[3];/* TempPwr-Table */
extern volatile real32_T CaEDCC_DCDCAWaterTemp_C[3];/* Temp-Table */
extern volatile real32_T CaEDCC_DCDCBInVoltPwrTable_kw[10];/* InVoltPwr-Table */
extern volatile real32_T CaEDCC_DCDCBInVoltTable_V[10];/* InVolt-Table */
extern volatile real32_T CaEDCC_DCDCBOutVoltPwrTable_kw[8];/* OutVoltPwr-Table */
extern volatile real32_T CaEDCC_DCDCBOutVoltTable_V[8];/* OutVolt-Table */
extern volatile real32_T CaEDCC_DCDCBTempPwrTable_kw[3];/* TempPwr-Table */
extern volatile real32_T CaEDCC_DCDCBWaterTemp_C[3];/* Temp-Table */
extern volatile boolean_T CbEDCC_DCDCAOutCurrReqOvrSwt_flg;/* GcEDCC_DCDCAOutCurrReq_A��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCAOutVoltReqOvrSwt_flg;/* GcEDCC_DCDCAOutVoltReq_V��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCAPwrCmdOvrSwt_flg;/* GbEDCC_DCDCAPwrCmd_flg��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCAPwrCmdOvr_flg;/* GbEDCC_DCDCAPwrCmd_flg��Ӧ��OverWriteֵ */
extern volatile boolean_T CbEDCC_DCDCARunModeOvrSwt_flg;/* GeEDCC_DCDCARunMode_enum��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCAVoltBuildFltOvrSwt_flg;/* GbEDCC_DCDCAVoltBuildFlt_flg��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCAVoltBuildFltOvr_flg;/* GbEDCC_DCDCAVoltBuildFlt_flg��Ӧ��OverWriteֵ */
extern volatile boolean_T CbEDCC_DCDCBOutCurrReqOvrSwt_flg;/* GcEDCC_DCDCBOutCurrReq_A��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCBOutVoltReqOvrSwt_flg;/* GcEDCC_DCDCBOutVoltReq_V��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCBPwrCmdOvrSwt_flg;/* GbEDCC_DCDCBPwrCmd_flg��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCBPwrCmdOvr_flg;/* GbEDCC_DCDCBPwrCmd_flg��Ӧ��OverWriteֵ */
extern volatile boolean_T CbEDCC_DCDCBRunModeOvrSwt_flg;/* GeEDCC_DCDCBRunMode_enum��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCBVoltBuildFltOvrSwt_flg;/* GbEDCC_DCDCBVoltBuildFlt_flg��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEDCC_DCDCBVoltBuildFltOvr_flg;/* GbEDCC_DCDCBVoltBuildFlt_flg��Ӧ��OverWriteֵ */
extern volatile uint16_T CcEDCC_AOffToStdbDelayT_ms;/* DCDCA����״̬offline��standby Delayʱ�� */
extern volatile uint16_T CcEDCC_AStdbToOffDelayT_ms;/* DCDCA����״̬standby��offline Delayʱ�� */
extern volatile uint8_T CcEDCC_AllowDCDCAWorkFltLvl_numb;/* ����DCDCA�����Ĺ��ϵȼ� */
extern volatile uint8_T CcEDCC_AllowDCDCBWorkFltLvl_numb;/* ����DCDCB�����Ĺ��ϵȼ� */
extern volatile uint16_T CcEDCC_BOffToStdbDelayT_ms;/* DCDCB����״̬offline��standby Delayʱ�� */
extern volatile uint16_T CcEDCC_BStdbToOffDelayT_ms;/* DCDCB����״̬standby��offline Delayʱ�� */
extern volatile uint8_T CcEDCC_DCDCACalCurr_A;/* DC/DCA�궨���� */
extern volatile real32_T CcEDCC_DCDCAConvRatio_R;/* DC/DCAת��ϵ�� */
extern volatile real32_T CcEDCC_DCDCAOutCurrReqOvr_A;/* GcEDCC_DCDCAOutCurrReq_A��Ӧ��OverWriteֵ */
extern volatile real32_T CcEDCC_DCDCAOutVoltReqOvr_V;/* GcEDCC_DCDCAOutVoltReq_V��Ӧ��OverWriteֵ */
extern volatile uint8_T CcEDCC_DCDCAPwrOffDelayT_ms;/* DCDCA�ػ�&#xA0;Delay&#xA0;ʱ�� */
extern volatile uint8_T CcEDCC_DCDCAPwrOnDelayT_ms;/* DCDCA����&#xA0;Delay&#xA0;ʱ�� */
extern volatile uint8_T CcEDCC_DCDCASum_numb;/* DC/DCA���� */
extern volatile real32_T CcEDCC_DCDCAUnloadVolt_V;/* DC/DCAй�ŵ�ѹ */
extern volatile uint16_T CcEDCC_DCDCAVoltBuildDelayT_ms;/* DCDCA��ѹ����Delayʱ�� */
extern volatile real32_T CcEDCC_DCDCAVoltRatio_R;/* DC/DCA��ѹϵ�� */
extern volatile uint8_T CcEDCC_DCDCBCalCurr_A;/* DC/DCB�궨���� */
extern volatile real32_T CcEDCC_DCDCBConvRatio_R;/* DC/DCBת��ϵ�� */
extern volatile real32_T CcEDCC_DCDCBOutCurrReqOvr_A;/* GcEDCC_DCDCBOutCurrReq_A��Ӧ��OverWriteֵ */
extern volatile real32_T CcEDCC_DCDCBOutVoltReqOvr_V;/* GcEDCC_DCDCBOutVoltReq_V��Ӧ��OverWriteֵ */
extern volatile uint8_T CcEDCC_DCDCBPwrOffDelayT_ms;/* DCDCB�ػ�&#xA0;Delay&#xA0;ʱ�� */
extern volatile uint8_T CcEDCC_DCDCBPwrOnDelayT_ms;/* DCDCB�ػ�&#xA0;Delay&#xA0;ʱ�� */
extern volatile uint8_T CcEDCC_DCDCBSum_numb;/* DC/DCB���� */
extern volatile real32_T CcEDCC_DCDCBUnloadVolt_V;/* DC/DCBй�ŵ�ѹ */
extern volatile uint16_T CcEDCC_DCDCBVoltBuildDelayT_ms;/* DCDCB��ѹ����Delayʱ�� */
extern volatile real32_T CcEDCC_DCDCBVoltRatio_R;/* DC/DCB��ѹϵ�� */
extern volatile real32_T CcEDCC_Ratio1000_R;
extern volatile uint8_T CeEDCC_DCDCARunModeOvr_enum;/* GeEDCC_DCDCARunMode_enum��Ӧ��OverWriteֵ */
extern volatile uint8_T CeEDCC_DCDCBRunModeOvr_enum;/* GeEDCC_DCDCBRunMode_enum��Ӧ��OverWriteֵ */

#endif                                 /* RTW_HEADER_EDCC_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
