/*
 * File: EACC_Var.c
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Sun Jul 19 15:50:17 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "rtwtypes.h"
#include "EACC_types.h"

/* Exported data definition */
volatile boolean_T LbEACC_ACDCAOfflineToStandby_flg;/* ACDCA��Offline��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCAPrechrgToRun_flg;/* ACDCA��Prechrg��ת��Run��־ */
volatile boolean_T LbEACC_ACDCAPrechrgToStandby_flg;/* ACDCA��Prechrg��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCARunToStandby_flg;/* ACDCA��Run��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCAStandbyToOffline_flg;/* ACDCA��Standby��ת��Offline��־ */
volatile boolean_T LbEACC_ACDCAStandbyToPrechrg_flg;/* ACDCA��Standby��ת��Prechrg��־ */
volatile boolean_T LbEACC_ACDCAWork_flg;
volatile boolean_T LbEACC_ACDCBOfflineToStandby_flg;/* ACDCB��Offline��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCBPrechrgToRun_flg;/* ACDCB��Prechrg��ת��Run��־ */
volatile boolean_T LbEACC_ACDCBPrechrgToStandby_flg;/* ACDCB��Prechrg��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCBRunToStandby_flg;/* ACDCB��Run��ת��Standby��־ */
volatile boolean_T LbEACC_ACDCBStandbyToOffline_flg;/* ACDCB��Standby��ת��Offline��־ */
volatile boolean_T LbEACC_ACDCBStandbyToPrechrg_flg;/* ACDCB��Standby��ת��Prechrg��־ */
volatile boolean_T LbEACC_ACDCBWork_flg;
volatile real32_T LcEACC_ACDCACurrX_A;
volatile real32_T LcEACC_ACDCAMaxCurr_A;/* ACDCA������ */
volatile real32_T LcEACC_ACDCAMaxPwr_kw;/* ACDCA����� */
volatile real32_T LcEACC_ACDCAScreenInputPwr_kw;/* ACDC��Ļ���빦�� */
volatile real32_T LcEACC_ACDCATempFltPwr_kw;/* ACDCAˮ�¹��Ϲ��� */
volatile real32_T LcEACC_ACDCATempPwr_kw;/* ACDCAˮ�²���� */
volatile real32_T LcEACC_ACDCBCurrX_A;
volatile real32_T LcEACC_ACDCBMaxCurr_A;/* ACDCB������ */
volatile real32_T LcEACC_ACDCBMaxPwr_kw;/* ACDCB����� */
volatile real32_T LcEACC_ACDCBScreenInputPwr_kw;/* ACDC��Ļ���빦�� */
volatile real32_T LcEACC_ACDCBTempFltPwr_kw;/* ACDCBˮ�¹��Ϲ��� */
volatile real32_T LcEACC_ACDCBTempPwr_kw;/* ACDCBˮ�²���� */
volatile real32_T LcEACC_PrechrgACDCAOutVoltReq_V;/* ACDCA��Perchrgģʽ�������ѹ */
volatile real32_T LcEACC_PrechrgACDCBOutVoltReq_V;/* ACDCB��Perchrgģʽ�������ѹ */
volatile real32_T LcEACC_RunACDCAOutVoltReq_V;/* ACDCA��Runģʽ�������ѹ */
volatile real32_T LcEACC_RunACDCBOutVoltReq_V;/* ACDCB��Runģʽ�������ѹ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
