/*
 * File: EBIM.h
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EBIM_h_
#define RTW_HEADER_EBIM_h_
#include <stddef.h>
#ifndef EBIM_COMMON_INCLUDES_
# define EBIM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EBIM_COMMON_INCLUDES_ */

#include "EBIM_types.h"

/* Includes for objects with custom storage classes. */
#include "EBIM_Const.h"
#include "EBIM_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T StateName;                   /* '<S12>/Unit Delay' */
  uint8_T StateName_h;                 /* '<S13>/Unit Delay' */
  boolean_T StateName_l;               /* '<S8>/Unit Delay' */
  boolean_T StateName_e;               /* '<S9>/Unit Delay' */
} DW_EBIM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion2;   /* '<S12>/Data Type Conversion2' */
  const uint8_T DataTypeConversion2_g; /* '<S13>/Data Type Conversion2' */
} ConstB_EBIM_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  boolean_T GbEBSW_T645ThreePhaseOnline_flg;/* '<Root>/GbEBSW_T645ThreePhaseOnline_flg' */
} ExtU_EBIM_T;

/* Real-time Model Data Structure */
struct tag_RTM_EBIM_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_EBIM_T EBIM_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_EBIM_T EBIM_U;
extern const ConstB_EBIM_T EBIM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EBIM_initialize(void);

/* Exported entry point functions */
extern void EBIM_BMSInterMgt_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EBIM_T *const EBIM_M;

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
 * '<Root>' : 'EBIM'
 * '<S1>'   : 'EBIM/EBIM'
 * '<S2>'   : 'EBIM/EBIM/BMSInterMgt_10ms'
 * '<S3>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys'
 * '<S4>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackAllowedReCharge'
 * '<S5>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackCntCtr'
 * '<S6>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq'
 * '<S7>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/PackNotAllowedDisCharge'
 * '<S8>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackAllowedReCharge/BMSAPackAllowedReCharge'
 * '<S9>'   : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackAllowedReCharge/BMSBPackAllowedReCharge'
 * '<S10>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackAllowedReCharge/BMSAPackAllowedReCharge/OverWrite3'
 * '<S11>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackAllowedReCharge/BMSBPackAllowedReCharge/OverWrite3'
 * '<S12>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackCntCtr/BMSAPackCntCtr'
 * '<S13>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackCntCtr/BMSBPackCntCtr'
 * '<S14>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackCntCtr/BMSAPackCntCtr/OverWrite3'
 * '<S15>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackCntCtr/BMSBPackCntCtr/OverWrite3'
 * '<S16>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSAPackOutReq'
 * '<S17>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSBPackOutReq'
 * '<S18>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSAPackOutReq/OverWrite1'
 * '<S19>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSAPackOutReq/OverWrite3'
 * '<S20>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSBPackOutReq/OverWrite1'
 * '<S21>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/BMSPackOutReq/BMSBPackOutReq/OverWrite3'
 * '<S22>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/PackNotAllowedDisCharge/PackANotAllowedDisCharge'
 * '<S23>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/PackNotAllowedDisCharge/PackBNotAllowedDisCharge'
 * '<S24>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/PackNotAllowedDisCharge/PackANotAllowedDisCharge/OverWrite3'
 * '<S25>'  : 'EBIM/EBIM/BMSInterMgt_10ms/BMSInterMgt_10ms_sys/PackNotAllowedDisCharge/PackBNotAllowedDisCharge/OverWrite3'
 */

/*-
 * Requirements for '<Root>': EBIM
 */
#endif                                 /* RTW_HEADER_EBIM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
