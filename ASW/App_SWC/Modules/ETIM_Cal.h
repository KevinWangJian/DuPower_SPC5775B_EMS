/*
 * File: ETIM_Cal.h
 *
 * Code generated for Simulink model 'ETIM'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 14 16:18:34 2020
 */

#ifndef RTW_HEADER_ETIM_Cal_h_
#define RTW_HEADER_ETIM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbETIM_OCPPCCU1StateOvrSwt_flg;/* 目标温度 */
extern volatile boolean_T CbETIM_OCPPCCU2StateOvrSwt_flg;/* 目标温度 */
extern volatile uint8_T CeETIM_OCPPCCU1StateOvr_enum;/* CCU1状态
                                                        0:unavailable
                                                        1:available
                                                        2:preparing
                                                        3:charging
                                                        4:finishing
                                                        5:fault */
extern volatile uint8_T CeETIM_OCPPCCU2StateOvr_enum;/* CCU2状态
                                                        0:unavailable
                                                        1:available
                                                        2:preparing
                                                        3:charging
                                                        4:finishing
                                                        5:fault */

#endif                                 /* RTW_HEADER_ETIM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
