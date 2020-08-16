/*
 * File: ECMM_Var.c
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

/* Exported data definition */
volatile boolean_T LbECMM_ChrgCtrABCChrgToIdle_flg;/* A支路从BCChrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrACChrgToIdle_flg;/* A支路从CChrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrAChrgToIdle_flg;/* A支路从Chrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrAIdleToBCChrg_flg;/* A支路从Idle跳转到BCChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrAIdleToCChrg_flg;/* A支路从Idle跳转到CChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrAIdleToChrg_flg;/* A支路从Idle跳转到Chrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrAIdleToOffline_flg;/* A支路从Idle跳转到Offline状态标志 */
volatile boolean_T LbECMM_ChrgCtrAIdleToReChrg_flg;/* A支路从Idle跳转到ReChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrAOfflineToIdle_flg;/* A支路从Offline跳转到Idel状态标志 */
volatile boolean_T LbECMM_ChrgCtrAReChrgToIdle_flg;/* A支路从ReChrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrBBCChrgToIdle_flg;/* B支路从BCChrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrBCChrgToIdle_flg;/* B支路从CChrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrBChrgToIdle_flg;/* B支路从Chrg跳转到Idle状态标志 */
volatile boolean_T LbECMM_ChrgCtrBIdleToBCChrg_flg;/* B支路从Idle跳转到BCChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrBIdleToCChrg_flg;/* B支路从Idle跳转到CChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrBIdleToChrg_flg;/* B支路从Idle跳转到Chrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrBIdleToOffline_flg;/* B支路从Idle跳转到Offline状态标志 */
volatile boolean_T LbECMM_ChrgCtrBIdleToReChrg_flg;/* B支路从Idle跳转到ReChrg状态标志 */
volatile boolean_T LbECMM_ChrgCtrBOfflineToIdle_flg;/* B支路从Offline跳转到Idel状态标志 */
volatile boolean_T LbECMM_ChrgCtrBReChrgToIdle_flg;/* B支路从ReChrg跳转到Idle状态标志 */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
