/*
 * File: ECHM_Cal.c
 *
 * Code generated for Simulink model 'ECHM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:07:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECHM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECHM_GunAStartChrgOvrSwt_flg = 0;/* A枪开启充电指令
                                                         0:不开启; 1:开启 */
volatile boolean_T CbECHM_GunAStartChrgOvr_flg = 0;/* A枪开启充电指令
                                                      0:不开启; 1:开启 */
volatile boolean_T CbECHM_GunAStopChrgOvrSwt_flg = 0;/* A枪停止充电指令
                                                        0:不停止; 1:停止 */
volatile boolean_T CbECHM_GunAStopChrgOvr_flg = 0;/* A枪停止充电指令
                                                     0:不停止; 1:停止 */
volatile boolean_T CbECHM_GunBStartChrgOvrSwt_flg = 0;/* B枪开启充电指令
                                                         0:不开启; 1:开启 */
volatile boolean_T CbECHM_GunBStartChrgOvr_flg = 0;/* B枪开启充电指令
                                                      0:不开启; 1:开启 */
volatile boolean_T CbECHM_GunBStopChrgOvrSwt_flg = 0;/* B枪停止充电指令
                                                        0:不停止; 1:停止 */
volatile boolean_T CbECHM_GunBStopChrgOvr_flg = 0;/* B枪停止充电指令
                                                     0:不停止; 1:停止 */
volatile uint8_T CcEBCR_BMSASOC15_pct = 15U;
volatile uint8_T CcEBCR_BMSBSOC15_pct = 15U;
volatile uint8_T CcEBCR_BMSSOC30_pct = 30U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
