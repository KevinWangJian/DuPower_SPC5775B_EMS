/*
 * File: EAMM_Var.c
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

/* Exported data definition */
volatile boolean_T LbEAMM_ACDCAGunAToOffline_flg;/* ACDCA从GunA状态跳转至Offline状态标志 */
volatile boolean_T LbEAMM_ACDCAGunBToOffline_flg;/* ACDCA从GunB状态跳转至Offline状态标志 */
volatile boolean_T LbEAMM_ACDCAOfflineToGunA_flg;/* ACDCA从Offline状态跳转至GunA状态标志 */
volatile boolean_T LbEAMM_ACDCAOfflineToGunB_flg;/* ACDCA从Offline状态跳转至GunB状态标志 */
volatile boolean_T LbEAMM_ACDCAOfflineToPackA_flg;/* ACDCA从Offline状态跳转至PackA状态标志 */
volatile boolean_T LbEAMM_ACDCAPackAToOffline_flg;/* ACDCA从PackA状态跳转至Offline状态标志 */
volatile boolean_T LbEAMM_ACDCBGunAToOffline_flg;/* ACDCB从GunA状态跳转至Offline状态标志 */
volatile boolean_T LbEAMM_ACDCBGunBToOffline_flg;/* ACDCB从GunB状态跳转至Offline状态标志 */
volatile boolean_T LbEAMM_ACDCBOfflineToGunA_flg;/* ACDCB从Offline状态跳转至GunA状态标志 */
volatile boolean_T LbEAMM_ACDCBOfflineToGunB_flg;/* ACDCB从Offline状态跳转至GunB状态标志 */
volatile boolean_T LbEAMM_ACDCBOfflineToPackB_flg;/* ACDCB从Offline状态跳转至PackB状态标志 */
volatile boolean_T LbEAMM_ACDCBPackBToOffline_flg;/* ACDCB从PackB状态跳转至Offline状态标志 */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
