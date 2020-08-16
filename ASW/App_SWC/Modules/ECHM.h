/*
 * File: ECHM.h
 *
 * Code generated for Simulink model 'ECHM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:07:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECHM_h_
#define RTW_HEADER_ECHM_h_
#include <stddef.h>
#ifndef ECHM_COMMON_INCLUDES_
# define ECHM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ECHM_COMMON_INCLUDES_ */

#include "ECHM_types.h"

/* Includes for objects with custom storage classes. */
#include "ECHM_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  boolean_T Delay_DSTATE;              /* '<S5>/Delay' */
  boolean_T Delay_DSTATE_c;            /* '<S4>/Delay' */
} DW_ECHM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion1;   /* '<S11>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S11>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S11>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S11>/Data Type Conversion4' */
} ConstB_ECHM_T;

/* Real-time Model Data Structure */
struct tag_RTM_ECHM_T {
  const char_T * volatile errorStatus;
};

/* Block states (auto storage) */
extern DW_ECHM_T ECHM_DW;
extern const ConstB_ECHM_T ECHM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ECHM_initialize(void);

/* Exported entry point functions */
extern void ECHM_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ECHM_T *const ECHM_M;

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
 * '<Root>' : 'ECHM'
 * '<S1>'   : 'ECHM/ECHM_Model'
 * '<S2>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms'
 * '<S3>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms'
 * '<S4>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/AGunChgControl'
 * '<S5>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/BGunChgControl'
 * '<S6>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/AGunChgControl/AGunStartChg'
 * '<S7>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/AGunChgControl/AGunStopChg'
 * '<S8>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/AGunChgControl/AGunStartChg/OverWrite_CbECHM_GunAStartChrgOvr_flg'
 * '<S9>'   : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/AGunChgControl/AGunStopChg/OverWrite_CbECHM_GunAStopChrgOvr_flg'
 * '<S10>'  : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/BGunChgControl/AGunStartChg'
 * '<S11>'  : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/BGunChgControl/AGunStopChg'
 * '<S12>'  : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/BGunChgControl/AGunStartChg/OverWrite_CbECHM_GunBStartChrgOvr_flg'
 * '<S13>'  : 'ECHM/ECHM_Model/ECHM_Model_10ms/ECHM_Model_10ms/BGunChgControl/AGunStopChg/OverWrite_CbECHM_GunBStopChrgOvr_flg'
 */

/*-
 * Requirements for '<Root>': ECHM
 */
#endif                                 /* RTW_HEADER_ECHM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
