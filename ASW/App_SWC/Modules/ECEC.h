/*
 * File: ECEC.h
 *
 * Code generated for Simulink model 'ECEC'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 15:32:52 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECEC_h_
#define RTW_HEADER_ECEC_h_
#include <stddef.h>
#ifndef ECEC_COMMON_INCLUDES_
# define ECEC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ECEC_COMMON_INCLUDES_ */

#include "ECEC_types.h"

/* Includes for objects with custom storage classes. */
#include "ECEC_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T In1;                        /* '<S21>/In1' */
  real32_T oGcECEC_CCU2ElectricityRate_rmb;/* '<S3>/ECEC_CCU2_10ms' */
  real32_T oGcECEC_CCU2ChargeEnergy_kwH;/* '<S3>/ECEC_CCU2_10ms' */
  real32_T oGcECEC_CCU1ElectricityRate_rmb;/* '<S3>/ECEC_CCU1_10ms' */
  real32_T oGcECEC_CCU1ChargeEnergy_kwH;/* '<S3>/ECEC_CCU1_10ms' */
  uint8_T oGeECEC_CCU2ChargeStatus_enum;/* '<S3>/ECEC_CCU2_10ms' */
  uint8_T oGeECEC_CCU1ChargeStatus_enum;/* '<S3>/ECEC_CCU1_10ms' */
  boolean_T oGbECEC_CCU2ElectricityCalFinis;/* '<S3>/ECEC_CCU2_10ms' */
  boolean_T oGbECEC_CCU2ChargeOver_flg;/* '<S3>/ECEC_CCU2_10ms' */
  boolean_T oGbECEC_CCU1ElectricityCalFinis;/* '<S3>/ECEC_CCU1_10ms' */
  boolean_T oGbECEC_CCU1ChargeOver_flg;/* '<S3>/ECEC_CCU1_10ms' */
} B_ECEC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T LcECEC_CCU2StrChargeEnergy_kwH;/* '<S3>/ECEC_CCU2_10ms' */
  real32_T LcECEC_CCU2MaxChargeEnergy_kwH;/* '<S3>/ECEC_CCU2_10ms' */
  real32_T LcECEC_CCU1StrChargeEnergy_kwH;/* '<S3>/ECEC_CCU1_10ms' */
  real32_T LcECEC_CCU1MaxChargeEnergy_kwH;/* '<S3>/ECEC_CCU1_10ms' */
  uint8_T StateName;                   /* '<S22>/Unit Delay1' */
  boolean_T StateName_j;               /* '<S22>/Unit Delay' */
  uint8_T is_active_c2_ECEC;           /* '<S3>/ECEC_CCU2_10ms' */
  uint8_T is_c2_ECEC;                  /* '<S3>/ECEC_CCU2_10ms' */
  uint8_T is_ENABLE;                   /* '<S3>/ECEC_CCU2_10ms' */
  uint8_T is_IN_CHARGING;              /* '<S3>/ECEC_CCU2_10ms' */
  uint8_T is_CHARGE_COMPLETE;          /* '<S3>/ECEC_CCU2_10ms' */
  uint8_T iGeECCR_CCU2CCUState_enum_start;/* '<S3>/ECEC_CCU2_10ms' */
  uint8_T is_active_c1_ECEC;           /* '<S3>/ECEC_CCU1_10ms' */
  uint8_T is_c1_ECEC;                  /* '<S3>/ECEC_CCU1_10ms' */
  uint8_T is_ENABLE_m;                 /* '<S3>/ECEC_CCU1_10ms' */
  uint8_T is_IN_CHARGING_c;            /* '<S3>/ECEC_CCU1_10ms' */
  uint8_T is_CHARGE_COMPLETE_k;        /* '<S3>/ECEC_CCU1_10ms' */
  uint8_T iGeECCR_CCU1CCUState_enum_start;/* '<S3>/ECEC_CCU1_10ms' */
} DW_ECEC_T;

/* Real-time Model Data Structure */
struct tag_RTM_ECEC_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ECEC_T ECEC_B;

/* Block states (auto storage) */
extern DW_ECEC_T ECEC_DW;

/* Model entry point functions */
extern void ECEC_initialize(void);

/* Exported entry point functions */
extern void ECEC_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ECEC_T *const ECEC_M;

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
 * '<Root>' : 'ECEC'
 * '<S1>'   : 'ECEC/ECEC'
 * '<S2>'   : 'ECEC/ECEC/EACB_10ms_Sys'
 * '<S3>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys'
 * '<S4>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECEC_CCU1_10ms'
 * '<S5>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECEC_CCU2_10ms'
 * '<S6>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum1'
 * '<S7>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum10'
 * '<S8>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum11'
 * '<S9>'   : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum12'
 * '<S10>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum13'
 * '<S11>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum14'
 * '<S12>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum2'
 * '<S13>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum3'
 * '<S14>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum4'
 * '<S15>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum5'
 * '<S16>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum6'
 * '<S17>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum7'
 * '<S18>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum8'
 * '<S19>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/ECTC_GeECTC_ACChgBatState_enum9'
 * '<S20>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/Trigger_Rising'
 * '<S21>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/Triggered Subsystem'
 * '<S22>'  : 'ECEC/ECEC/EACB_10ms_Sys/ECEC_10ms_Sys/Trigger_Rising/Unit Delay External IC'
 */

/*-
 * Requirements for '<Root>': ECEC
 */
#endif                                 /* RTW_HEADER_ECEC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
