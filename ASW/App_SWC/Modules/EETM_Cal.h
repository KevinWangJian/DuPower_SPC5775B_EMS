/*
 * File: EETM_Cal.h
 *
 * Code generated for Simulink model 'EETM'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 23 17:19:25 2020
 */

#ifndef RTW_HEADER_EETM_Cal_h_
#define RTW_HEADER_EETM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEETM_HeatModeOvrSwt_flg;/* ETM HeatMode */
extern volatile boolean_T CbEETM_SetTempOvrSwt_flg;/* 目标温度 */
extern volatile real32_T CcEETM_SetTempOvr_C;/* 目标温度 */
extern volatile uint8_T CeEETM_HeatModeOvr_enum;/* ETM HeatMode:
                                                   0:NotReady(Init)
                                                   1:OffLine
                                                   2:Standby
                                                   3:SelfCirculation
                                                   4:Cold
                                                   5:Heat */

#endif                                 /* RTW_HEADER_EETM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
