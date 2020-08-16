/*
 * File: EISO.h
 *
 * Code generated for Simulink model 'EISO'.
 *
 * Company                        : DP
 * Author                         : Àîê»
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 16:42:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EISO_h_
#define RTW_HEADER_EISO_h_
#include <stddef.h>
#ifndef EISO_COMMON_INCLUDES_
# define EISO_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EISO_COMMON_INCLUDES_ */

#include "EISO_types.h"

/* Includes for objects with custom storage classes. */
#include "EISO_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S13>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_d;   /* '<S12>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_j;   /* '<S8>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_l;   /* '<S7>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S13>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_l;    /* '<S12>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_a;    /* '<S8>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_j;    /* '<S7>/FixPt Unit Delay2' */
} DW_EISO_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S9>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S9>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S9>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S9>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S9>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S9>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S9>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7;   /* '<S9>/Data Type Conversion7' */
  const uint8_T DataTypeConversion_g;  /* '<S4>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_l; /* '<S4>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S4>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_i; /* '<S4>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_g; /* '<S4>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_l; /* '<S4>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_d; /* '<S4>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_i; /* '<S4>/Data Type Conversion7' */
} ConstB_EISO_T;

/* Real-time Model Data Structure */
struct tag_RTM_EISO_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_EISO_T EISO_DW;
extern const ConstB_EISO_T EISO_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EISO_initialize(void);

/* Exported entry point functions */
extern void EISO_PACKA_10ms(void);
extern void EISO_PACKB_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EISO_T *const EISO_M;

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
 * '<Root>' : 'EISO'
 * '<S1>'   : 'EISO/EISO'
 * '<S2>'   : 'EISO/EISO/PACKA'
 * '<S3>'   : 'EISO/EISO/PACKB'
 * '<S4>'   : 'EISO/EISO/PACKA/PACKA_10ms'
 * '<S5>'   : 'EISO/EISO/PACKA/PACKA_10ms/Delay'
 * '<S6>'   : 'EISO/EISO/PACKA/PACKA_10ms/Delay2'
 * '<S7>'   : 'EISO/EISO/PACKA/PACKA_10ms/Delay/Unit Delay Resettable'
 * '<S8>'   : 'EISO/EISO/PACKA/PACKA_10ms/Delay2/Unit Delay Resettable'
 * '<S9>'   : 'EISO/EISO/PACKB/PACKB_10ms'
 * '<S10>'  : 'EISO/EISO/PACKB/PACKB_10ms/Delay1'
 * '<S11>'  : 'EISO/EISO/PACKB/PACKB_10ms/Delay3'
 * '<S12>'  : 'EISO/EISO/PACKB/PACKB_10ms/Delay1/Unit Delay Resettable'
 * '<S13>'  : 'EISO/EISO/PACKB/PACKB_10ms/Delay3/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': EISO
 */
#endif                                 /* RTW_HEADER_EISO_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
