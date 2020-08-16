/*
 * File: EAMM_Cal.c
 *
 * Code generated for Simulink model 'EAMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 14:33:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EAMM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEAMM_ACDCAWorkModeOvrSwt_flg = 0;/* GeEAMM_ACDCAWorkMode_enum������Ӧ��OvrWrite��־ */
volatile boolean_T CbEAMM_ACDCBWorkModeOvrSwt_flg = 0;/* GeEAMM_ACDCBWorkMode_enum������Ӧ��OvrWrite��־ */
volatile real32_T CcEAMM_GunAMaxPwrLowLimit_kw = 1.0F;/* ǹA��������� */
volatile real32_T CcEAMM_GunAMaxPwrUpLimit_kw = 120.0F;/* ǹA��������� */
volatile real32_T CcEAMM_GunBMaxPwrLowLimit_kw = 1.0F;/* ǹB��������� */
volatile real32_T CcEAMM_GunBMaxPwrUpLimit_kw = 120.0F;/* ǹB��������� */
volatile uint8_T CeEAMM_ACDCAWorkModeOvr_enum = 0U;/* GeEAMM_ACDCAWorkMode_enum������Ӧ��OvrWriteֵ */
volatile uint8_T CeEAMM_ACDCBWorkModeOvr_enum = 0U;/* GeEAMM_ACDCBWorkMode_enum������Ӧ��OvrWriteֵ */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
