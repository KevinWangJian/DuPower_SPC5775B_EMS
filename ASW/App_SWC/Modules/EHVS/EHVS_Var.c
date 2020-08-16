/*
 * File: EHVS_Var.c
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

/* Exported data definition */
volatile boolean_T LbEHVS_LineAReadyToChangeState_flg;/* A支路状态跳转准备完成标志 */
volatile boolean_T LbEHVS_LineAToSLVS_flg;/* HVS从LineA跳转至SLVS标志 */
volatile boolean_T LbEHVS_LineBReadyToChangeState_flg;/* B支路状态跳转准备完成标志 */
volatile boolean_T LbEHVS_LineBToSLVS_flg;/* HVS从LineB跳转至SLVS标志 */
volatile boolean_T LbEHVS_OfflineToLineA_flg;/* HVS从Offline跳转至LineA标志 */
volatile boolean_T LbEHVS_OfflineToLineB_flg;/* HVS从Offline跳转至LineB标志 */
volatile boolean_T LbEHVS_PackACondOne_flg;/* PackA低压供电标志条件一 */
volatile boolean_T LbEHVS_PackACondThree_flg;/* PackA低压供电标志条件三 */
volatile boolean_T LbEHVS_PackACondTwo_flg;/* PackA低压供电标志条件二 */
volatile boolean_T LbEHVS_PackALowPowerSupply_flg;/* PackA低压供电标志 */
volatile boolean_T LbEHVS_PackBCondOne_flg;/* PackB低压供电标志条件一 */
volatile boolean_T LbEHVS_PackBCondThree_flg;/* PackB低压供电标志条件三 */
volatile boolean_T LbEHVS_PackBCondTwo_flg;/* PackB低压供电标志条件二 */
volatile boolean_T LbEHVS_PackBLowPowerSupply_flg;/* PackB低压供电标志 */
volatile boolean_T LbEHVS_SLVSToLineA_flg;/* HVS从SLVS跳转至LineA标志 */
volatile boolean_T LbEHVS_SLVSToLineB_flg;/* HVS从SLVS跳转至LineB标志 */
volatile boolean_T LbEHVS_SLVSToOffline_flg;/* HVS从SLVS跳转至Offline标志 */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
