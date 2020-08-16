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
volatile boolean_T LbEACC_ACDCAOfflineToStandby_flg;/* ACDCA从Offline跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCAPrechrgToRun_flg;/* ACDCA从Prechrg跳转至Run标志 */
volatile boolean_T LbEACC_ACDCAPrechrgToStandby_flg;/* ACDCA从Prechrg跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCARunToStandby_flg;/* ACDCA从Run跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCAStandbyToOffline_flg;/* ACDCA从Standby跳转至Offline标志 */
volatile boolean_T LbEACC_ACDCAStandbyToPrechrg_flg;/* ACDCA从Standby跳转至Prechrg标志 */
volatile boolean_T LbEACC_ACDCAWork_flg;
volatile boolean_T LbEACC_ACDCBOfflineToStandby_flg;/* ACDCB从Offline跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCBPrechrgToRun_flg;/* ACDCB从Prechrg跳转至Run标志 */
volatile boolean_T LbEACC_ACDCBPrechrgToStandby_flg;/* ACDCB从Prechrg跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCBRunToStandby_flg;/* ACDCB从Run跳转至Standby标志 */
volatile boolean_T LbEACC_ACDCBStandbyToOffline_flg;/* ACDCB从Standby跳转至Offline标志 */
volatile boolean_T LbEACC_ACDCBStandbyToPrechrg_flg;/* ACDCB从Standby跳转至Prechrg标志 */
volatile boolean_T LbEACC_ACDCBWork_flg;
volatile real32_T LcEACC_ACDCACurrX_A;
volatile real32_T LcEACC_ACDCAMaxCurr_A;/* ACDCA最大电流 */
volatile real32_T LcEACC_ACDCAMaxPwr_kw;/* ACDCA最大功率 */
volatile real32_T LcEACC_ACDCAScreenInputPwr_kw;/* ACDC屏幕输入功率 */
volatile real32_T LcEACC_ACDCATempFltPwr_kw;/* ACDCA水温故障功率 */
volatile real32_T LcEACC_ACDCATempPwr_kw;/* ACDCA水温查表功率 */
volatile real32_T LcEACC_ACDCBCurrX_A;
volatile real32_T LcEACC_ACDCBMaxCurr_A;/* ACDCB最大电流 */
volatile real32_T LcEACC_ACDCBMaxPwr_kw;/* ACDCB最大功率 */
volatile real32_T LcEACC_ACDCBScreenInputPwr_kw;/* ACDC屏幕输入功率 */
volatile real32_T LcEACC_ACDCBTempFltPwr_kw;/* ACDCB水温故障功率 */
volatile real32_T LcEACC_ACDCBTempPwr_kw;/* ACDCB水温查表功率 */
volatile real32_T LcEACC_PrechrgACDCAOutVoltReq_V;/* ACDCA在Perchrg模式下请求电压 */
volatile real32_T LcEACC_PrechrgACDCBOutVoltReq_V;/* ACDCB在Perchrg模式下请求电压 */
volatile real32_T LcEACC_RunACDCAOutVoltReq_V;/* ACDCA在Run模式下请求电压 */
volatile real32_T LcEACC_RunACDCBOutVoltReq_V;/* ACDCB在Run模式下请求电压 */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
