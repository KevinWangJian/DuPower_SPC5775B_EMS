/*
 * File: EDCC_Var.c
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:05:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "rtwtypes.h"
#include "EDCC_types.h"

/* Exported data definition */
volatile boolean_T LbEDCC_DCDCAOfflineToStandby_flg;/* DCDCA��Offline��ת��Standby��־ */
volatile boolean_T LbEDCC_DCDCARunToStandby_flg;/* DCDCA��Run��ת��Standby��־ */
volatile boolean_T LbEDCC_DCDCAStandbyToOffline_flg;/* DCDCA��Standby��ת��Offline��־ */
volatile boolean_T LbEDCC_DCDCAStandbyToRun_flg;/* DCDCA��Standby��ת��Run��־ */
volatile boolean_T LbEDCC_DCDCBOfflineToStandby_flg;/* DCDCB��Offline��ת��Standby��־ */
volatile boolean_T LbEDCC_DCDCBRunToStandby_flg;/* DCDCB��Run��ת��Standby��־ */
volatile boolean_T LbEDCC_DCDCBStandbyToOffline_flg;/* DCDCB��Standby��ת��Offline��־ */
volatile boolean_T LbEDCC_DCDCBStandbyToRun_flg;/* DCDCB��Standby��ת��Run��־ */
volatile real32_T LcEDCC_DCDCACurrX_A;
volatile real32_T LcEDCC_DCDCACurrY_A;
volatile real32_T LcEDCC_DCDCAMaxCurr_A;/* DCDCA������ */
volatile real32_T LcEDCC_DCDCAMaxPwr_kw;/* DCDCA����� */
volatile real32_T LcEDCC_DCDCATablePwr_kw;/* DCDCA����� */
volatile real32_T LcEDCC_DCDCBCurrX_A;
volatile real32_T LcEDCC_DCDCBCurrY_A;
volatile real32_T LcEDCC_DCDCBMaxCurr_A;/* DCDCB������ */
volatile real32_T LcEDCC_DCDCBMaxPwr_kw;/* DCDCB����� */
volatile real32_T LcEDCC_DCDCBTablePwr_kw;/* DCDCB����� */
volatile real32_T LcEDCC_PackAConvDCDCAMaxCurr_A;/* PackAת����DCDCA������ */
volatile real32_T LcEDCC_PackBConvDCDCBMaxCurr_A;/* PackBת����DCDCB������ */
volatile real32_T kw1;
volatile real32_T kw2;
volatile real32_T kw3;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
