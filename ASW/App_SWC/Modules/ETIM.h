/*
 * File: ETIM.h
 *
 * Code generated for Simulink model 'ETIM'.
 *
 * Company                        : DP
 * Author                         : 19455
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 15:30:23 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ETIM_h_
#define RTW_HEADER_ETIM_h_
#include <stddef.h>
#ifndef ETIM_COMMON_INCLUDES_
# define ETIM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ETIM_COMMON_INCLUDES_ */

#include "ETIM_types.h"

/* Includes for objects with custom storage classes. */
#include "ETIM_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  Enum_ETCRTBOXCCU1OcppAvailability In1;/* '<S9>/In1' */
  Enum_ETCRTBOXCCU1OcppAvailability In1_j;/* '<S7>/In1' */
} B_ETIM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  boolean_T UnitDelay2_DSTATE;         /* '<S3>/Unit Delay2' */
  boolean_T UnitDelay1_DSTATE;         /* '<S3>/Unit Delay1' */
  boolean_T UnitDelay2_DSTATE_e;       /* '<S4>/Unit Delay2' */
  boolean_T UnitDelay1_DSTATE_l;       /* '<S4>/Unit Delay1' */
} DW_ETIM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S3>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S3>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S3>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S3>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S3>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S3>/Data Type Conversion5' */
  const uint8_T DataTypeConversion_i;  /* '<S4>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_c; /* '<S4>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_j; /* '<S4>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_h; /* '<S4>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_c; /* '<S4>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_n; /* '<S4>/Data Type Conversion5' */
} ConstB_ETIM_T;

/* Real-time Model Data Structure */
struct tag_RTM_ETIM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ETIM_T ETIM_B;

/* Block states (auto storage) */
extern DW_ETIM_T ETIM_DW;
extern const ConstB_ETIM_T ETIM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ETIM_initialize(void);

/* Exported entry point functions */
extern void ETIM_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ETIM_T *const ETIM_M;

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
 * '<Root>' : 'ETIM'
 * '<S1>'   : 'ETIM/ETIM'
 * '<S2>'   : 'ETIM/ETIM/ETIM_10ms_Sys'
 * '<S3>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU1State_10ms_Sys'
 * '<S4>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU2State_10ms_Sys'
 * '<S5>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU2State_10ms_Sys1'
 * '<S6>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU1State_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S7>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU1State_10ms_Sys/Enabled Subsystem'
 * '<S8>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU2State_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S9>'   : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU2State_10ms_Sys/Enabled Subsystem'
 * '<S10>'  : 'ETIM/ETIM/ETIM_10ms_Sys/OCPPCCU2State_10ms_Sys1/ECTC_GeECTC_ACChgBatState_enum1'
 */

/*-
 * Requirements for '<Root>': ETIM
 */
#endif                                 /* RTW_HEADER_ETIM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
