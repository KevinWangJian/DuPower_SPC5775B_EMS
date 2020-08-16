/*
 * File: ETIM_Cal.c
 *
 * Code generated for Simulink model 'ETIM'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 14 16:18:34 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ETIM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbETIM_OCPPCCU1StateOvrSwt_flg = 0;/* 目标温度 */
volatile boolean_T CbETIM_OCPPCCU2StateOvrSwt_flg = 0;/* 目标温度 */
volatile uint8_T CeETIM_OCPPCCU1StateOvr_enum = 0U;/* CCU1状态
                                                      0:unavailable
                                                      1:available
                                                      2:preparing
                                                      3:charging
                                                      4:finishing
                                                      5:fault */
volatile uint8_T CeETIM_OCPPCCU2StateOvr_enum = 0U;/* CCU2状态
                                                      0:unavailable
                                                      1:available
                                                      2:preparing
                                                      3:charging
                                                      4:finishing
                                                      5:fault */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
