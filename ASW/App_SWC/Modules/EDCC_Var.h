/*
 * File: EDCC_Var.h
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:05:01 2020
 */

#ifndef RTW_HEADER_EDCC_Var_h_
#define RTW_HEADER_EDCC_Var_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T LbEDCC_DCDCAOfflineToStandby_flg;/* DCDCA从Offline跳转至Standby标志 */
extern volatile boolean_T LbEDCC_DCDCARunToStandby_flg;/* DCDCA从Run跳转至Standby标志 */
extern volatile boolean_T LbEDCC_DCDCAStandbyToOffline_flg;/* DCDCA从Standby跳转至Offline标志 */
extern volatile boolean_T LbEDCC_DCDCAStandbyToRun_flg;/* DCDCA从Standby跳转至Run标志 */
extern volatile boolean_T LbEDCC_DCDCBOfflineToStandby_flg;/* DCDCB从Offline跳转至Standby标志 */
extern volatile boolean_T LbEDCC_DCDCBRunToStandby_flg;/* DCDCB从Run跳转至Standby标志 */
extern volatile boolean_T LbEDCC_DCDCBStandbyToOffline_flg;/* DCDCB从Standby跳转至Offline标志 */
extern volatile boolean_T LbEDCC_DCDCBStandbyToRun_flg;/* DCDCB从Standby跳转至Run标志 */
extern volatile real32_T LcEDCC_DCDCACurrX_A;
extern volatile real32_T LcEDCC_DCDCACurrY_A;
extern volatile real32_T LcEDCC_DCDCAMaxCurr_A;/* DCDCA最大电流 */
extern volatile real32_T LcEDCC_DCDCAMaxPwr_kw;/* DCDCA最大功率 */
extern volatile real32_T LcEDCC_DCDCATablePwr_kw;/* DCDCA查表功率 */
extern volatile real32_T LcEDCC_DCDCBCurrX_A;
extern volatile real32_T LcEDCC_DCDCBCurrY_A;
extern volatile real32_T LcEDCC_DCDCBMaxCurr_A;/* DCDCB最大电流 */
extern volatile real32_T LcEDCC_DCDCBMaxPwr_kw;/* DCDCB最大功率 */
extern volatile real32_T LcEDCC_DCDCBTablePwr_kw;/* DCDCB查表功率 */
extern volatile real32_T LcEDCC_PackAConvDCDCAMaxCurr_A;/* PackA转换成DCDCA最大电流 */
extern volatile real32_T LcEDCC_PackBConvDCDCBMaxCurr_A;/* PackB转换成DCDCB最大电流 */
extern volatile real32_T kw1;
extern volatile real32_T kw2;
extern volatile real32_T kw3;

#endif                                 /* RTW_HEADER_EDCC_Var_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
