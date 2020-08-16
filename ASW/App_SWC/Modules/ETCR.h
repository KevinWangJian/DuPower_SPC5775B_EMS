/*
 * File: ETCR.h
 *
 * Code generated for Simulink model 'ETCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:37:39 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ETCR_h_
#define RTW_HEADER_ETCR_h_
#include <stddef.h>
#ifndef ETCR_COMMON_INCLUDES_
# define ETCR_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ETCR_COMMON_INCLUDES_ */

#include "ETCR_types.h"

/* Includes for objects with custom storage classes. */
#include "ETCR_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T FixPtUnitDelay1_DSTATE;     /* '<S9>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S9>/FixPt Unit Delay2' */
  boolean_T StateName;                 /* '<S3>/Unit Delay' */
} DW_ETCR_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const real32_T DataTypeConversion;   /* '<S3>/Data Type Conversion' */
  const real32_T DataTypeConversion1;  /* '<S3>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_i; /* '<S4>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S4>/Data Type Conversion2' */
  const uint8_T DataTypeConversion20;  /* '<S4>/Data Type Conversion20' */
  const uint8_T DataTypeConversion22;  /* '<S4>/Data Type Conversion22' */
  const uint8_T DataTypeConversion20_a;/* '<S5>/Data Type Conversion20' */
  const uint8_T DataTypeConversion22_g;/* '<S5>/Data Type Conversion22' */
} ConstB_ETCR_T;

/* Real-time Model Data Structure */
struct tag_RTM_ETCR_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_ETCR_T ETCR_DW;
extern const ConstB_ETCR_T ETCR_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ETCR_initialize(void);

/* Exported entry point functions */
extern void ETCR_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ETCR_T *const ETCR_M;

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
 * '<Root>' : 'ETCR'
 * '<S1>'   : 'ETCR/Subsystem1'
 * '<S2>'   : 'ETCR/Subsystem1/ETCR'
 * '<S3>'   : 'ETCR/Subsystem1/ETCR/Msg_0X1802F102Updata'
 * '<S4>'   : 'ETCR/Subsystem1/ETCR/StaChg'
 * '<S5>'   : 'ETCR/Subsystem1/ETCR/StpChg'
 * '<S6>'   : 'ETCR/Subsystem1/ETCR/Subsystem2'
 * '<S7>'   : 'ETCR/Subsystem1/ETCR/Msg_0X1802F102Updata/Delay'
 * '<S8>'   : 'ETCR/Subsystem1/ETCR/Msg_0X1802F102Updata/Subsystem'
 * '<S9>'   : 'ETCR/Subsystem1/ETCR/Msg_0X1802F102Updata/Delay/Unit Delay Resettable'
 * '<S10>'  : 'ETCR/Subsystem1/ETCR/Msg_0X1802F102Updata/Subsystem/OverWrite_CbETCR_0x1802F102UpdataOvr_flg'
 * '<S11>'  : 'ETCR/Subsystem1/ETCR/StaChg/OverWrite_CbETCR_LeftServeStpChgCmdOvr_flg'
 * '<S12>'  : 'ETCR/Subsystem1/ETCR/StaChg/OverWrite_CbETCR_RightServeStpChgCmdOvr_flg'
 * '<S13>'  : 'ETCR/Subsystem1/ETCR/StpChg/OverWrite_CbETCR_LeftServeStpChgCmdOvr_flg'
 * '<S14>'  : 'ETCR/Subsystem1/ETCR/StpChg/OverWrite_CbETCR_RightServeStpChgCmdOvr_flg'
 * '<S15>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_CeCAN5_TFDAuthResults_enum'
 * '<S16>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_CeCAN5_TFDAuthResults_enum1'
 * '<S17>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_CeCAN5_TFDAuthResults_enum2'
 * '<S18>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerDay_numb'
 * '<S19>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerHour_numb'
 * '<S20>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerInvalid_flg'
 * '<S21>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerMinute_numb'
 * '<S22>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerMonth_numb'
 * '<S23>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerSecond_numb'
 * '<S24>'  : 'ETCR/Subsystem1/ETCR/Subsystem2/OW_GcCAN5_TFDTBOXTimerYear_numb'
 */

/*-
 * Requirements for '<Root>': ETCR
 */
#endif                                 /* RTW_HEADER_ETCR_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
