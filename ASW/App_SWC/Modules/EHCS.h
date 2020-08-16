/*
 * File: EHCS.h
 *
 * Code generated for Simulink model 'EHCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 16:01:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EHCS_h_
#define RTW_HEADER_EHCS_h_
#include <math.h>
#include <stddef.h>
#ifndef EHCS_COMMON_INCLUDES_
# define EHCS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EHCS_COMMON_INCLUDES_ */

#include "EHCS_types.h"

/* Includes for objects with custom storage classes. */
#include "EHCS_Cal.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  Enum_EHCSEMSHeatModeSelect oGcEHCS_EMSHeatModeSelect_enum;/* '<S3>/Chart' */
} B_EHCS_T;

/* Real-time Model Data Structure */
struct tag_RTM_EHCS_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EHCS_T EHCS_B;

/* Model entry point functions */
extern void EHCS_initialize(void);

/* Exported entry point functions */
extern void EHCS_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EHCS_T *const EHCS_M;

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
 * '<Root>' : 'EHCS'
 * '<S1>'   : 'EHCS/EHCS'
 * '<S2>'   : 'EHCS/EHCS/EHCS_10ms_Sys'
 * '<S3>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys'
 * '<S4>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/Chart'
 * '<S5>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S6>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum10'
 * '<S7>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum2'
 * '<S8>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum3'
 * '<S9>'   : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum4'
 * '<S10>'  : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum6'
 * '<S11>'  : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum7'
 * '<S12>'  : 'EHCS/EHCS/EHCS_10ms_Sys/EHCS_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum9'
 */

/*-
 * Requirements for '<Root>': EHCS
 */
#endif                                 /* RTW_HEADER_EHCS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
