/*
 * File: EHVS.h
 *
 * Code generated for Simulink model 'EHVS'.
 *
 * Company                        : DP
 * Author                         : wxf
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 28 09:28:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EHVS_h_
#define RTW_HEADER_EHVS_h_
#include <stddef.h>
#ifndef EHVS_COMMON_INCLUDES_
# define EHVS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EHVS_COMMON_INCLUDES_ */

#include "EHVS_types.h"

/* Includes for objects with custom storage classes. */
#include "EHVS_Const.h"
#include "EHVS_Cal.h"
#include "EHVS_Var.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeEHVS_HVSState_enum;        /* '<S3>/EMSHighVoltSupply' */
} B_EHVS_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S32>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_e;   /* '<S22>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_o;   /* '<S17>/FixPt Unit Delay1' */
  uint8_T StateName;                   /* '<S3>/Unit Delay' */
  uint8_T StateName_k;                 /* '<S11>/Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S32>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_g;    /* '<S22>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_a;    /* '<S17>/FixPt Unit Delay2' */
  boolean_T StateName_h;               /* '<S10>/Unit Delay' */
  boolean_T StateName_b;               /* '<S9>/Unit Delay' */
  boolean_T StateName_n[2];            /* '<S31>/Unit Delay1' */
  boolean_T StateName_j[4];            /* '<S11>/Unit Delay' */
  uint8_T is_active_c4_EHVS;           /* '<S3>/EMSHighVoltSupply' */
  uint8_T is_c4_EHVS;                  /* '<S3>/EMSHighVoltSupply' */
  boolean_T OfflineWork_MODE;          /* '<S8>/OfflineWork' */
  boolean_T LineBWork_MODE;            /* '<S7>/LineBWork' */
  boolean_T LineAWork_MODE;            /* '<S6>/LineAWork' */
} DW_EHVS_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S10>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S10>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S10>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S10>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S10>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S10>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S10>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7;   /* '<S10>/Data Type Conversion7' */
  const uint8_T DataTypeConversion_g;  /* '<S9>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_b; /* '<S9>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_c; /* '<S9>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_b; /* '<S9>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_g; /* '<S9>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_p; /* '<S9>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_h; /* '<S9>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_b; /* '<S9>/Data Type Conversion7' */
  const uint8_T DataTypeConversion1_h; /* '<S11>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_a; /* '<S11>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_i; /* '<S11>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_c; /* '<S11>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_k; /* '<S11>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_c; /* '<S11>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_k; /* '<S11>/Data Type Conversion7' */
  const uint8_T DataTypeConversion1_a; /* '<S31>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_f; /* '<S31>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_f; /* '<S31>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_o;  /* '<S12>/Data Type Conversion' */
  const uint8_T DataTypeConversion_gt; /* '<S8>/Data Type Conversion' */
  const uint8_T DataTypeConversion_l;  /* '<S24>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_bv;/* '<S24>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_i; /* '<S24>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_bs;/* '<S24>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_j;  /* '<S25>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_o; /* '<S25>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_fo;/* '<S25>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_m; /* '<S25>/Data Type Conversion3' */
  const uint8_T DataTypeConversion_n;  /* '<S7>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_p; /* '<S19>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_g; /* '<S19>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_m;  /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_hr;/* '<S14>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_d; /* '<S14>/Data Type Conversion2' */
} ConstB_EHVS_T;

/* Real-time Model Data Structure */
struct tag_RTM_EHVS_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EHVS_T EHVS_B;

/* Block states (auto storage) */
extern DW_EHVS_T EHVS_DW;
extern const ConstB_EHVS_T EHVS_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EHVS_initialize(void);

/* Exported entry point functions */
extern void EHVS_10ms(void);

/* Real-time Model object */
extern RT_MODEL_EHVS_T *const EHVS_M;

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
 * '<Root>' : 'EHVS'
 * '<S1>'   : 'EHVS/EHVS_All'
 * '<S2>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys'
 * '<S3>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms'
 * '<S4>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/EACC_GeEACC_ACDCARunMode_enum'
 * '<S5>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/EMSHighVoltSupply'
 * '<S6>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA'
 * '<S7>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB'
 * '<S8>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/Offline'
 * '<S9>'   : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/PackALowPowerSupply'
 * '<S10>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/PackBLowPowerSupply'
 * '<S11>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl'
 * '<S12>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/SLVS'
 * '<S13>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA/LineAWork'
 * '<S14>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA/LineAWork/LineAReadyToChangeState'
 * '<S15>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA/LineAWork/LineAToSLVS'
 * '<S16>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA/LineAWork/LineAReadyToChangeState/Delay'
 * '<S17>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineA/LineAWork/LineAReadyToChangeState/Delay/Unit Delay Resettable'
 * '<S18>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB/LineBWork'
 * '<S19>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB/LineBWork/LineBReadyToChangeState'
 * '<S20>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB/LineBWork/LineBToSLVS'
 * '<S21>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB/LineBWork/LineBReadyToChangeState/Delay'
 * '<S22>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/LineB/LineBWork/LineBReadyToChangeState/Delay/Unit Delay Resettable'
 * '<S23>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/Offline/OfflineWork'
 * '<S24>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/Offline/OfflineWork/OfflineToLineA'
 * '<S25>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/Offline/OfflineWork/OfflineToLineB'
 * '<S26>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/Delay'
 * '<S27>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/EACC_GeEACC_ACDCARunMode_enum'
 * '<S28>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/EACC_GeEACC_ACDCARunMode_enum1'
 * '<S29>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S30>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/EACC_GeEACC_ACDCARunMode_enum3'
 * '<S31>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/Subsystem'
 * '<S32>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/Delay/Unit Delay Resettable'
 * '<S33>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/Subsystem/EACC_GeEACC_ACDCARunMode_enum'
 * '<S34>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/RelayCtrl/Subsystem/EACC_GeEACC_ACDCARunMode_enum1'
 * '<S35>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/SLVS/SLVSWork'
 * '<S36>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/SLVS/SLVSWork/SLVSToLineA'
 * '<S37>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/SLVS/SLVSWork/SLVSToLineB'
 * '<S38>'  : 'EHVS/EHVS_All/EHVS_10ms_Sys/EMSHighVoltSupply_10ms/SLVS/SLVSWork/SLVSToOffline'
 */

/*-
 * Requirements for '<Root>': EHVS
 */
#endif                                 /* RTW_HEADER_EHVS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
