/*
 * File: EMSM.h
 *
 * Code generated for Simulink model 'EMSM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 14:32:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EMSM_h_
#define RTW_HEADER_EMSM_h_
#include <stddef.h>
#ifndef EMSM_COMMON_INCLUDES_
# define EMSM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EMSM_COMMON_INCLUDES_ */

#include "EMSM_types.h"

/* Includes for objects with custom storage classes. */
#include "EMSM_Const.h"
#include "EMSM_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S43>/DebounceStartZero' */
typedef struct {
  real32_T Switch;                     /* '<S46>/Switch' */
} B_DebounceStartZero_EMSM_T;

/* Block states (auto storage) for system '<S43>/DebounceStartZero' */
typedef struct {
  uint32_T StateName_j;                /* '<S48>/Unit Delay' */
  uint32_T StateName_c;                /* '<S49>/Unit Delay1' */
  boolean_T StateName_jv;              /* '<S48>/Unit Delay1' */
  boolean_T StateName_n;               /* '<S49>/Unit Delay2' */
} DW_DebounceStartZero_EMSM_T;

/* Block signals (auto storage) */
typedef struct {
  B_DebounceStartZero_EMSM_T DebounceStartZero1;/* '<S6>/DebounceStartZero1' */
  B_DebounceStartZero_EMSM_T DebounceStartZero;/* '<S6>/DebounceStartZero' */
  B_DebounceStartZero_EMSM_T DebounceStartZero_e;/* '<S43>/DebounceStartZero' */
} B_EMSM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T StateName;                  /* '<S43>/Unit Delay1' */
  uint32_T FixPtUnitDelay1_DSTATE;     /* '<S45>/FixPt Unit Delay1' */
  uint32_T StateName_g;                /* '<S32>/Unit Delay' */
  uint32_T StateName_f;                /* '<S33>/Unit Delay1' */
  uint32_T StateName_d;                /* '<S14>/Unit Delay' */
  uint32_T StateName_k;                /* '<S15>/Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_a;   /* '<S28>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S45>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_n;    /* '<S28>/FixPt Unit Delay2' */
  boolean_T StateName_j;               /* '<S5>/Unit Delay' */
  boolean_T StateName_o;               /* '<S24>/Unit Delay' */
  boolean_T StateName_i;               /* '<S23>/Unit Delay1' */
  boolean_T StateName_c;               /* '<S43>/Unit Delay' */
  boolean_T StateName_gr;              /* '<S7>/Unit Delay' */
  boolean_T StateName_or;              /* '<S42>/Unit Delay1' */
  boolean_T StateName_k3;              /* '<S42>/Unit Delay' */
  boolean_T StateName_jl;              /* '<S10>/Unit Delay' */
  boolean_T StateName_h;               /* '<S29>/Unit Delay' */
  boolean_T StateName_e;               /* '<S32>/Unit Delay1' */
  boolean_T StateName_m;               /* '<S33>/Unit Delay2' */
  boolean_T StateName_kb;              /* '<S11>/Unit Delay' */
  boolean_T StateName_gd;              /* '<S14>/Unit Delay1' */
  boolean_T StateName_dg;              /* '<S15>/Unit Delay2' */
  DW_DebounceStartZero_EMSM_T DebounceStartZero1;/* '<S6>/DebounceStartZero1' */
  DW_DebounceStartZero_EMSM_T DebounceStartZero;/* '<S6>/DebounceStartZero' */
  DW_DebounceStartZero_EMSM_T DebounceStartZero_e;/* '<S43>/DebounceStartZero' */
} DW_EMSM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S5>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S5>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S5>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S5>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_m;  /* '<S23>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_j; /* '<S23>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_l; /* '<S23>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_a; /* '<S23>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S23>/Data Type Conversion4' */
  const uint8_T DataTypeConversion_g;  /* '<S42>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_i; /* '<S42>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_a; /* '<S42>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_g; /* '<S42>/Data Type Conversion3' */
} ConstB_EMSM_T;

/* Real-time Model Data Structure */
struct tag_RTM_EMSM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EMSM_T EMSM_B;

/* Block states (auto storage) */
extern DW_EMSM_T EMSM_DW;
extern const ConstB_EMSM_T EMSM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EMSM_initialize(void);

/* Exported entry point functions */
extern void EMSM_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EMSM_T *const EMSM_M;

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
 * '<Root>' : 'EMSM'
 * '<S1>'   : 'EMSM/EMSM_Model'
 * '<S2>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms'
 * '<S3>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms'
 * '<S4>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck'
 * '<S5>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/24VSelfCheck'
 * '<S6>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode'
 * '<S7>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess'
 * '<S8>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork'
 * '<S9>'   : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck'
 * '<S10>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd'
 * '<S11>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero'
 * '<S12>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/OverWrite_CbEMSM_12VSelfCheckSuccessOvr_flg'
 * '<S13>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/Compare To Zero'
 * '<S14>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/FaultProcess'
 * '<S15>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/HealProcess'
 * '<S16>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/FaultProcess/Decrease'
 * '<S17>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/FaultProcess/Increase'
 * '<S18>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S19>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S20>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/HealProcess/Decrease'
 * '<S21>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/HealProcess/Increase'
 * '<S22>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/12VSelfCheckSuccess/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S23>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/ECUCheckSuccess'
 * '<S24>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/EMSCheckSuccess'
 * '<S25>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/ECUCheckSuccess/OverWrite_CbEMSM_ECUCheckSuccessOvr_flg'
 * '<S26>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/EMSCheckSuccess/Delay'
 * '<S27>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/EMSCheckSuccess/OverWrite_CbEMSM_EMSCheckSuccessOvr_flg'
 * '<S28>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/ECUSelfCheckWork/EMSCheckSuccess/Delay/Unit Delay Resettable'
 * '<S29>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero'
 * '<S30>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/OverWrite_CbEMSM_SafeCheckSuccessOvr_flg'
 * '<S31>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/Compare To Zero'
 * '<S32>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/FaultProcess'
 * '<S33>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/HealProcess'
 * '<S34>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/FaultProcess/Decrease'
 * '<S35>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/FaultProcess/Increase'
 * '<S36>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S37>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S38>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/HealProcess/Decrease'
 * '<S39>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/HealProcess/Increase'
 * '<S40>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SafetyStateCheck/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S41>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/OverWrite_CbEMSM_SelfCheckCtrCmdOvr_flg'
 * '<S42>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrCloseCmd'
 * '<S43>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd'
 * '<S44>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrCloseCmd/Delay'
 * '<S45>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrCloseCmd/Delay/Unit Delay Resettable'
 * '<S46>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero'
 * '<S47>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/Compare To Zero'
 * '<S48>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/FaultProcess'
 * '<S49>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/HealProcess'
 * '<S50>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/FaultProcess/Decrease'
 * '<S51>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/FaultProcess/Increase'
 * '<S52>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S53>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S54>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/HealProcess/Decrease'
 * '<S55>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/HealProcess/Increase'
 * '<S56>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/12VSelfCheck/SelfCtrCmd/SelfCtrOpenCmd/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S57>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/24VSelfCheck/OverWrite_CbEMSM_24VSelfCheckSuccessOvr_flg'
 * '<S58>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero'
 * '<S59>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1'
 * '<S60>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/OverWrite_CbEMSM_SleepModeEnableOvr_flg'
 * '<S61>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/Compare To Zero'
 * '<S62>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/FaultProcess'
 * '<S63>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/HealProcess'
 * '<S64>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/FaultProcess/Decrease'
 * '<S65>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/FaultProcess/Increase'
 * '<S66>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/FaultProcess/Decrease/Nomal'
 * '<S67>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/HealProcess/Compare To Zero'
 * '<S68>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/HealProcess/Decrease'
 * '<S69>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/HealProcess/Increase'
 * '<S70>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero/HealProcess/Decrease/Nomal'
 * '<S71>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/Compare To Zero'
 * '<S72>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/FaultProcess'
 * '<S73>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/HealProcess'
 * '<S74>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/FaultProcess/Decrease'
 * '<S75>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/FaultProcess/Increase'
 * '<S76>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/FaultProcess/Decrease/Nomal'
 * '<S77>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/HealProcess/Compare To Zero'
 * '<S78>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/HealProcess/Decrease'
 * '<S79>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/HealProcess/Increase'
 * '<S80>'  : 'EMSM/EMSM_Model/EMSM_Model_10ms/EMSM_Model_10ms/SleepMode/DebounceStartZero1/HealProcess/Decrease/Nomal'
 */

/*-
 * Requirements for '<Root>': EMSM
 */
#endif                                 /* RTW_HEADER_EMSM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
