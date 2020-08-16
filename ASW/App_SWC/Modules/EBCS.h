/*
 * File: EBCS.h
 *
 * Code generated for Simulink model 'EBCS'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 16 09:46:28 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EBCS_h_
#define RTW_HEADER_EBCS_h_
#include <stddef.h>
#ifndef EBCS_COMMON_INCLUDES_
# define EBCS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EBCS_COMMON_INCLUDES_ */

#include "EBCS_types.h"

/* Includes for objects with custom storage classes. */
#include "EBCS_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Invariant block signals (auto storage) */
typedef struct {
  const boolean_T DataTypeConversion3; /* '<S3>/Data Type Conversion3' */
  const boolean_T DataTypeConversion2; /* '<S3>/Data Type Conversion2' */
  const boolean_T DataTypeConversion9; /* '<S3>/Data Type Conversion9' */
  const boolean_T DataTypeConversion3_b;/* '<S4>/Data Type Conversion3' */
  const boolean_T DataTypeConversion2_m;/* '<S4>/Data Type Conversion2' */
  const boolean_T DataTypeConversion10;/* '<S4>/Data Type Conversion10' */
} ConstB_EBCS_T;

/* Real-time Model Data Structure */
struct tag_RTM_EBCS_T {
  const char_T * volatile errorStatus;
};

extern const ConstB_EBCS_T EBCS_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EBCS_initialize(void);

/* Exported entry point functions */
extern void EBCS_BMS_EMS_SysStat_1801FAF1_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EBCS_T *const EBCS_M;

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
 * '<Root>' : 'EBCS'
 * '<S1>'   : 'EBCS/EBCS'
 * '<S2>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1'
 * '<S3>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1'
 * '<S4>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1'
 * '<S5>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite4'
 * '<S6>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite6'
 * '<S7>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb'
 * '<S8>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb2'
 * '<S9>'   : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb3'
 * '<S10>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSA_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb5'
 * '<S11>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite4'
 * '<S12>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite6'
 * '<S13>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb'
 * '<S14>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb2'
 * '<S15>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb3'
 * '<S16>'  : 'EBCS/EBCS/BMS_EMS_SysStat_1801FAF1/BMSB_EMS_SysStat_1801FAF1/OverWrite_CcEBCS_DTCHighByteOvr_numb5'
 */

/*-
 * Requirements for '<Root>': EBCS
 */
#endif                                 /* RTW_HEADER_EBCS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
