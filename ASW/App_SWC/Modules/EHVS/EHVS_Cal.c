/*
 * File: EHVS_Cal.c
 *
 * Code generated for Simulink model 'EHVS'.
 *
 * Company                        : DP
 * Author                         : wxf
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 28 09:28:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EHVS_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEHVS_HVSStateOvrSwt_flg = 0;/* GeEHVS_HVSState_enum��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_PACKAToHVSNCtrOvrSwt_flg = 0;/* GbEHVS_PACKAToHVSNCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_PACKAToHVSNCtrOvr_flg = 0;/* GbEHVS_PACKAToHVSNCtr_flg��Ӧ��OverWrite���� */
volatile boolean_T CbEHVS_PACKAToHVSPCtrOvrSwt_flg = 0;/* GbEHVS_PACKAToHVSPCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_PACKAToHVSPCtrOvr_flg = 0;/* GbEHVS_PACKAToHVSPCtr_flg��Ӧ��OverWrite���� */
volatile boolean_T CbEHVS_PACKBToHVSNCtrOvrSwt_flg = 0;/* GbEHVS_PACKBToHVSNCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_PACKBToHVSNCtrOvr_flg = 0;/* GbEHVS_PACKBToHVSNCtr_flg��Ӧ��OverWrite���� */
volatile boolean_T CbEHVS_PACKBToHVSPCtrOvrSwt_flg = 0;/* GbEHVS_PACKBToHVSPCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_PACKBToHVSPCtrOvr_flg = 0;/* GbEHVS_PACKBToHVSPCtr_flg��Ӧ��OverWrite���� */
volatile boolean_T CbEHVS_SmallDCDCPowerCtrOvrSwt_flg = 0;/* GbEHVS_SmallDCDCPowerCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_SmallDCDCPowerCtrOvr_flg = 0;/* GbEHVS_SmallDCDCPowerCtr_flg��Ӧ��OverWrite���� */
volatile boolean_T CbEHVS_TMSPowerCtrOvrSwt_flg = 0;/* GbEHVS_TMSPowerCtr_flg��Ӧ��OverWrite��־ */
volatile boolean_T CbEHVS_TMSPowerCtrOvr_flg = 0;/* GbEHVS_TMSPowerCtr_flg��Ӧ��OverWrite���� */
volatile uint16_T CcEHVS_LineAChangeStateDebTime_ms = 5000U;/* LineA״̬��֧·A��ת׼����ɱ궨ʱ�� */
volatile uint16_T CcEHVS_LineBChangeStateDebTime_ms = 5000U;/* LineB״̬��֧·B��ת׼����ɱ궨ʱ�� */
volatile real32_T CcEHVS_PackAVoltFactor_numb = 0.5F;/* PackA��ѹ�궨ϵ�� */
volatile real32_T CcEHVS_PackBVoltFactor_numb = 0.5F;/* PackB��ѹ�궨ϵ�� */
volatile real32_T CcEHVS_PackSOC20Percent_pct = 20.0F;/* 20%SOCֵ */
volatile real32_T CcEHVS_PackSOC45Percent_pct = 45.0F;/* 45%SOCֵ */
volatile real32_T CcEHVS_PackSOCLowLimit_pct = 15.0F;/* PackSOC���� */
volatile uint16_T CcEHVS_RelayCtrOFFDebTime_ms = 1000U;/* TMS����ָ��ΪFALSE�궨ʱ�� */
volatile uint8_T CeEHVS_HVSStateOvr_enum = 0U;/* GeEHVS_HVSState_enum��Ӧ��OverWrite���� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
