/*
 * File: ECMM_Cal.c
 *
 * Code generated for Simulink model 'ECMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed May 20 17:27:26 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECMM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECMM_ChrgCtrAModeOvrSwt_flg = 0;/* GeECMM_ChrgCtrAMode_enum������Ӧ��OverWrite��־ */
volatile boolean_T CbECMM_ChrgCtrBModeOvrSwt_flg = 0;/* GeECMM_ChrgCtrBMode_enum������Ӧ��OverWrite��־ */
volatile uint8_T CcECMM_ABCChrgToIdleDelayT_ms = 20U;/* ������״̬A BothCrossChrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_ACChrgToIdleDelayT_ms = 20U;/* ������״̬A CrossChrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_AChrgToIdleDelayT_ms = 20U;/* ������״̬A Chrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_AIdleToBCChrgDelayT_ms = 200U;/* ������״̬A Idle��תBothCrossChrg delayʱ�� */
volatile uint8_T CcECMM_AIdleToCChrgDelayT_ms = 200U;/* ������״̬A Idle��תCrossChrg delayʱ�� */
volatile uint8_T CcECMM_AIdleToChrgDelayT_ms = 200U;/* ������״̬A Idle��תChrg delayʱ�� */
volatile uint8_T CcECMM_AIdleToOfflineDelayT_ms = 200U;/* ������״̬A Idle��תoffline delayʱ�� */
volatile uint8_T CcECMM_AIdleToReChrgDelayT_ms = 200U;/* ������״̬A Idle��תReChrg delayʱ�� */
volatile uint8_T CcECMM_AOfflineToIdleDelayT_ms = 200U;/* ������״̬A offline��תIdle delayʱ�� */
volatile uint8_T CcECMM_AReChrgToIdleDelayT_ms = 20U;/* ������״̬A ReChrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_BBCChrgToIdleDelayT_ms = 20U;/* ������״̬B BothCrossChrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_BCChrgToIdleDelayT_ms = 20U;/* ������״̬B CrossChrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_BChrgToIdleDelayT_ms = 20U;/* ������״̬B Chrg��תIdle delayʱ�� */
volatile uint8_T CcECMM_BIdleToBCChrgDelayT_ms = 200U;/* ������״̬B Idle��תBothCrossChrg delayʱ�� */
volatile uint8_T CcECMM_BIdleToCChrgDelayT_ms = 200U;/* ������״̬B Idle��תCrossChrg delayʱ�� */
volatile uint8_T CcECMM_BIdleToChrgDelayT_ms = 200U;/* ������״̬B Idle��תChrg delayʱ�� */
volatile uint8_T CcECMM_BIdleToOfflineDelayT_ms = 200U;/* ������״̬B Idle��תoffline delayʱ�� */
volatile uint8_T CcECMM_BIdleToReChrgDelayT_ms = 200U;/* ������״̬B Idle��תReChrg delayʱ�� */
volatile uint8_T CcECMM_BOfflineToIdleDelayT_ms = 200U;/* ������״̬B offline��תIdle delayʱ�� */
volatile uint8_T CcECMM_BReChrgToIdleDelayT_ms = 20U;/* ������״̬B ReChrg��תIdle delayʱ�� */
volatile uint8_T CeECMM_ChrgCtrAModeOvr_enum = 0U;/* GeECMM_ChrgCtrAMode_enum������Ӧ��OverWriteֵ */
volatile uint8_T CeECMM_ChrgCtrBModeOvr_enum = 0U;/* GeECMM_ChrgCtrBMode_enum������Ӧ��OverWriteֵ */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
