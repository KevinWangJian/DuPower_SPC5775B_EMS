/*
 * File: EHCR.h
 *
 * Code generated for Simulink model 'EHCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 14:52:44 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EHCR_h_
#define RTW_HEADER_EHCR_h_
#include <stddef.h>
#ifndef EHCR_COMMON_INCLUDES_
# define EHCR_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EHCR_COMMON_INCLUDES_ */

#include "EHCR_types.h"

/* Includes for objects with custom storage classes. */
#include "EHCR_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Real-time Model Data Structure */
struct tag_RTM_EHCR_T {
  const char_T * volatile errorStatus;
};

/* Model entry point functions */
extern void EHCR_initialize(void);

/* Exported entry point functions */
extern void EHCR_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EHCR_T *const EHCR_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'EHCR'
 * '<S1>'   : 'EHCR/EHCR'
 * '<S2>'   : 'EHCR/EHCR/EHCR_10ms_Sys'
 * '<S3>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys'
 * '<S4>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S5>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum2'
 * '<S6>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum3'
 * '<S7>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum4'
 * '<S8>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum5'
 * '<S9>'   : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum6'
 * '<S10>'  : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum7'
 * '<S11>'  : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum8'
 * '<S12>'  : 'EHCR/EHCR/EHCR_10ms_Sys/EHCR_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum9'
 */

/*-
 * Requirements for '<Root>': EHCR
 */
#endif                                 /* RTW_HEADER_EHCR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
