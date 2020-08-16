/*
 * File: EETM.h
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

#ifndef RTW_HEADER_EETM_h_
#define RTW_HEADER_EETM_h_
#include <stddef.h>
#ifndef EETM_COMMON_INCLUDES_
# define EETM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EETM_COMMON_INCLUDES_ */

#include "EETM_types.h"

/* Includes for objects with custom storage classes. */
#include "EETM_Cal.h"
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
  real32_T oGcEETM_SetTemp_C;          /* '<S3>/EETM_10ms' */
  uint8_T oGeEETM_HeatMode_enum;       /* '<S3>/EETM_10ms' */
} B_EETM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c1_EETM;           /* '<S3>/EETM_10ms' */
  uint8_T is_c1_EETM;                  /* '<S3>/EETM_10ms' */
} DW_EETM_T;

/* Real-time Model Data Structure */
struct tag_RTM_EETM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EETM_T EETM_B;

/* Block states (auto storage) */
extern DW_EETM_T EETM_DW;

/* Model entry point functions */
extern void EETM_initialize(void);

/* Exported entry point functions */
extern void EETM_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EETM_T *const EETM_M;

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
 * '<Root>' : 'EETM'
 * '<S1>'   : 'EETM/EETM'
 * '<S2>'   : 'EETM/EETM/EACB_10ms_Sys'
 * '<S3>'   : 'EETM/EETM/EACB_10ms_Sys/EETM_10ms_Sys'
 * '<S4>'   : 'EETM/EETM/EACB_10ms_Sys/EETM_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S5>'   : 'EETM/EETM/EACB_10ms_Sys/EETM_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum2'
 * '<S6>'   : 'EETM/EETM/EACB_10ms_Sys/EETM_10ms_Sys/EETM_10ms'
 */

/*-
 * Requirements for '<Root>': EETM
 */
#endif                                 /* RTW_HEADER_EETM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
