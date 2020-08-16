/*
 * File: EETM_Cal.c
 *
 * Code generated for Simulink model 'EETM'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 23 17:19:25 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EETM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEETM_HeatModeOvrSwt_flg = 0;/* ETM HeatMode */
volatile boolean_T CbEETM_SetTempOvrSwt_flg = 0;/* 目标温度 */
volatile real32_T CcEETM_SetTempOvr_C = 0.0F;/* 目标温度 */
volatile uint8_T CeEETM_HeatModeOvr_enum = 0U;/* ETM HeatMode:
                                                 0:NotReady(Init)
                                                 1:OffLine
                                                 2:Standby
                                                 3:SelfCirculation
                                                 4:Cold
                                                 5:Heat */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
