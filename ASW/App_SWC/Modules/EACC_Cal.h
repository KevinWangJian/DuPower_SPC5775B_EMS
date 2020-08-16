/*
 * File: EACC_Cal.h
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 13:26:06 2020
 */

#ifndef RTW_HEADER_EACC_Cal_h_
#define RTW_HEADER_EACC_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile real32_T CaEACC_ACDCATempPwrTable_kw[7];/* Pwr-Table */
extern volatile real32_T CaEACC_ACDCAWaterTemp_C[7];/* Temp-Table */
extern volatile real32_T CaEACC_ACDCBTempPwrTable_kw[7];/* Pwr-Table */
extern volatile real32_T CaEACC_ACDCBWaterTemp_C[7];/* Temp-Table */
extern volatile boolean_T CbEACC_ACDCAOutCurrReqOvrSwt_flg;/* GcEACC_ACDCAOutCurrReq_AӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCAOutVoltReqOvrSwt_flg;/* GcEACC_ACDCAOutVoltReq_VӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCAPwrCmdOvrSwt_flg;/* GbEACC_ACDCAPwrCmd_flgӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCAPwrCmdOvr_flg;/* GbEACC_ACDCAPwrCmd_flg��Ӧ��OverWriteֵ */
extern volatile boolean_T CbEACC_ACDCARunModeOvrSwt_flg;/* GeEACC_ACDCARunMode_enum��Ӧ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCBOutCurrReqOvrSwt_flg;/* GcEACC_ACDCBOutCurrReq_AӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCBOutVoltReqOvrSwt_flg;/* GcEACC_ACDCBOutVoltReq_VӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCBPwrCmdOvrSwt_flg;/* GbEACC_ACDCBPwrCmd_flgӦ��OverWrite��־ */
extern volatile boolean_T CbEACC_ACDCBPwrCmdOvr_flg;/* GbEACC_ACDCBPwrCmd_flg��Ӧ��OverWriteֵ */
extern volatile boolean_T CbEACC_ACDCBRunModeOvrSwt_flg;/* GeEACC_ACDCBRunMode_enumӦ��OverWrite��־ */
extern volatile uint8_T CcEACC_ACDCACalCurr_A;/* AC/DCA�궨���� */
extern volatile real32_T CcEACC_ACDCACurrRatio_R;/* AC/DCA�궨����ϵ�� */
extern volatile real32_T CcEACC_ACDCAOutCurrReqOvr_A;/* GcEACC_ACDCAOutCurrReq_A��Ӧ��OverWriteֵ */
extern volatile real32_T CcEACC_ACDCAOutVoltReqOvr_V;/* GcEACC_ACDCAOutVoltReq_V��Ӧ��OverWriteֵ */
extern volatile uint8_T CcEACC_ACDCAPwrOffDelayT_ms;/* AC/DCA�ػ�&#xA0;Delayʱ�� */
extern volatile uint8_T CcEACC_ACDCAPwrOnDelayT_ms;/* AC/DCA����&#xA0;Delayʱ�� */
extern volatile uint8_T CcEACC_ACDCASum_numb;/* AC/DCA���� */
extern volatile uint8_T CcEACC_ACDCBCalCurr_A;/* AC/DCB�궨���� */
extern volatile real32_T CcEACC_ACDCBCurrRatio_R;/* AC/DCB�궨����ϵ�� */
extern volatile real32_T CcEACC_ACDCBOutCurrReqOvr_A;/* GcEACC_ACDCBOutCurrReq_A��Ӧ��OverWriteֵ */
extern volatile real32_T CcEACC_ACDCBOutVoltReqOvr_V;/* GcEACC_ACDCBOutVoltReq_V��Ӧ��OverWriteֵ */
extern volatile uint8_T CcEACC_ACDCBSum_numb;/* AC/DCB���� */
extern volatile uint16_T CcEACC_AOffToStdbDelayT_ms;/* ACDCA����״̬offline��standby Delayʱ�� */
extern volatile uint8_T CcEACC_APChrgToStdbDelayT_ms;/* ACDCA����״̬PreChrg��standby Delayʱ�� */
extern volatile uint16_T CcEACC_AStdbToOffDelayT_ms;/* ACDCA����״̬standby��offline Delayʱ�� */
extern volatile uint8_T CcEACC_AllowACDCAWorkFltLvl_numb;/* ����ACDCA�����Ĺ��ϵȼ� */
extern volatile uint8_T CcEACC_AllowACDCBWorkFltLvl_numb;/* ����ACDCB�����Ĺ��ϵȼ� */
extern volatile uint16_T CcEACC_BOffToStdbDelayT_ms;/* ACDCB����״̬offline��standby Delayʱ�� */
extern volatile uint8_T CcEACC_BPChrgToStdbDelayT_ms;/* ACDCB����״̬PreChrg��standby Delayʱ�� */
extern volatile uint16_T CcEACC_BStdbToOffDelayT_ms;/* ACDCB����״̬standby��offline Delayʱ�� */
extern volatile real32_T CcEACC_Ratio1000_R;
extern volatile uint8_T CeEACC_ACDCARunModeOvr_enum;/* GeEACC_ACDCARunMode_enum��Ӧ��OverWriteֵ */
extern volatile uint8_T CeEACC_ACDCBRunModeOvr_enum;/* GeEACC_ACDCBRunMode_enum��Ӧ��OverWriteֵ */

#endif                                 /* RTW_HEADER_EACC_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
