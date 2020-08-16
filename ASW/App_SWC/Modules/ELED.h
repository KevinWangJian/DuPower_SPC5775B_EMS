/*
 * File: ELED.h
 *
 * Code generated for Simulink model 'ELED'.
 *
 * Company                        : DP
 * Author                         : Àîê»
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:59:41 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ELED_h_
#define RTW_HEADER_ELED_h_
#include <math.h>
#include <stddef.h>
#ifndef ELED_COMMON_INCLUDES_
# define ELED_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ELED_COMMON_INCLUDES_ */

#include "ELED_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Invariant block signals (auto storage) */
typedef struct {
  const real32_T DataTypeConversion10; /* '<S6>/Data Type Conversion10' */
  const real32_T DataTypeConversion8;  /* '<S6>/Data Type Conversion8' */
  const real32_T DataTypeConversion15; /* '<S6>/Data Type Conversion15' */
  const real32_T DataTypeConversion7;  /* '<S6>/Data Type Conversion7' */
  const real32_T DataTypeConversion10_p;/* '<S7>/Data Type Conversion10' */
  const real32_T DataTypeConversion8_b;/* '<S7>/Data Type Conversion8' */
  const real32_T DataTypeConversion15_f;/* '<S7>/Data Type Conversion15' */
  const real32_T DataTypeConversion7_l;/* '<S7>/Data Type Conversion7' */
  const uint8_T DataTypeConversion;    /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S6>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S6>/Data Type Conversion2' */
  const uint8_T DataTypeConversion12;  /* '<S6>/Data Type Conversion12' */
  const uint8_T DataTypeConversion13;  /* '<S6>/Data Type Conversion13' */
  const uint8_T DataTypeConversion14;  /* '<S6>/Data Type Conversion14' */
  const uint8_T DataTypeConversion3;   /* '<S6>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S6>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S6>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S6>/Data Type Conversion6' */
  const uint8_T DataTypeConversion9;   /* '<S6>/Data Type Conversion9' */
  const uint8_T DataTypeConversion_d;  /* '<S7>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_g; /* '<S7>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_g; /* '<S7>/Data Type Conversion2' */
  const uint8_T DataTypeConversion12_k;/* '<S7>/Data Type Conversion12' */
  const uint8_T DataTypeConversion13_h;/* '<S7>/Data Type Conversion13' */
  const uint8_T DataTypeConversion14_i;/* '<S7>/Data Type Conversion14' */
  const uint8_T DataTypeConversion3_i; /* '<S7>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_c; /* '<S7>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_d; /* '<S7>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_n; /* '<S7>/Data Type Conversion6' */
  const uint8_T DataTypeConversion9_g; /* '<S7>/Data Type Conversion9' */
} ConstB_ELED_T;

/* Real-time Model Data Structure */
struct tag_RTM_ELED_T {
  const char_T * volatile errorStatus;
};

extern const ConstB_ELED_T ELED_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ELED_initialize(void);

/* Exported entry point functions */
extern void ELED_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ELED_T *const ELED_M;

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
 * '<Root>' : 'ELED'
 * '<S1>'   : 'ELED/ELED_All'
 * '<S2>'   : 'ELED/ELED_All/ELED_10ms_Sys'
 * '<S3>'   : 'ELED/ELED_All/ELED_10ms_Sys/ELED10ms_R'
 * '<S4>'   : 'ELED/ELED_All/ELED_10ms_Sys/ELED10ms_R/PACKA'
 * '<S5>'   : 'ELED/ELED_All/ELED_10ms_Sys/ELED10ms_R/PACKAB'
 * '<S6>'   : 'ELED/ELED_All/ELED_10ms_Sys/ELED10ms_R/PACKA/PACKA_10ms'
 * '<S7>'   : 'ELED/ELED_All/ELED_10ms_Sys/ELED10ms_R/PACKAB/PACKA_10ms'
 */

/*-
 * Requirements for '<Root>': ELED
 */
#endif                                 /* RTW_HEADER_ELED_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
