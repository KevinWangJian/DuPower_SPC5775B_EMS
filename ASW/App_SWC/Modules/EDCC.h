/*
 * File: EDCC.h
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:05:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EDCC_h_
#define RTW_HEADER_EDCC_h_
#include <math.h>
#include <stddef.h>
#ifndef EDCC_COMMON_INCLUDES_
# define EDCC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EDCC_COMMON_INCLUDES_ */

#include "EDCC_types.h"

/* Includes for objects with custom storage classes. */
#include "EDCC_Const.h"
#include "EDCC_Cal.h"
#include "EDCC_Var.h"
#include "look1_iflf_binlxpw.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S19>/Delay' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S21>/Relational Operator' */
} B_Delay_EDCC_T;

/* Block states (auto storage) for system '<S19>/Delay' */
typedef struct {
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S22>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S22>/FixPt Unit Delay2' */
} DW_Delay_EDCC_T;

/* Block signals for system '<S10>/Delay' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S36>/Relational Operator' */
} B_Delay_EDCC_c_T;

/* Block states (auto storage) for system '<S10>/Delay' */
typedef struct {
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S39>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S39>/FixPt Unit Delay1' */
} DW_Delay_EDCC_o_T;

/* Block signals for system '<S10>/Delay1' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S37>/Relational Operator' */
} B_Delay1_EDCC_T;

/* Block states (auto storage) for system '<S10>/Delay1' */
typedef struct {
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S40>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S40>/FixPt Unit Delay1' */
} DW_Delay1_EDCC_T;

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeEDCC_DCDCBRunMode_enum;    /* '<S41>/DCDCBRunMode' */
  uint8_T GeEDCC_DCDCARunMode_enum;    /* '<S4>/DCDCARunMode' */
  B_Delay1_EDCC_T Delay1_d;            /* '<S47>/Delay1' */
  B_Delay_EDCC_c_T Delay_jd;           /* '<S47>/Delay' */
  B_Delay_EDCC_T Delay_l;              /* '<S56>/Delay' */
  B_Delay1_EDCC_T Delay1;              /* '<S10>/Delay1' */
  B_Delay_EDCC_c_T Delay;              /* '<S10>/Delay' */
  B_Delay_EDCC_T Delay_j;              /* '<S19>/Delay' */
} B_EDCC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T StateName;                  /* '<S70>/Unit Delay1' */
  real32_T StateName_c;                /* '<S33>/Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S64>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_p;   /* '<S54>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_o;   /* '<S27>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_m;   /* '<S17>/FixPt Unit Delay1' */
  uint8_T StateName_i;                 /* '<S41>/Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S64>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_c;    /* '<S54>/FixPt Unit Delay2' */
  uint8_T StateName_g;                 /* '<S4>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_cb;   /* '<S27>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_n;    /* '<S17>/FixPt Unit Delay2' */
  boolean_T StateName_p;               /* '<S47>/Unit Delay2' */
  boolean_T StateName_c5;              /* '<S10>/Unit Delay2' */
  uint8_T is_active_c2_EDCC;           /* '<S41>/DCDCBRunMode' */
  uint8_T is_c2_EDCC;                  /* '<S41>/DCDCBRunMode' */
  uint8_T is_active_c4_EDCC;           /* '<S4>/DCDCARunMode' */
  uint8_T is_c4_EDCC;                  /* '<S4>/DCDCARunMode' */
  boolean_T StandbyWork_MODE;          /* '<S44>/StandbyWork' */
  boolean_T RunWork_MODE;              /* '<S43>/RunWork' */
  boolean_T OfflineWork_MODE;          /* '<S42>/OfflineWork' */
  boolean_T StandbyWork_MODE_c;        /* '<S7>/StandbyWork' */
  boolean_T RunWork_MODE_g;            /* '<S6>/RunWork' */
  boolean_T OfflineWork_MODE_l;        /* '<S5>/OfflineWork' */
  DW_Delay1_EDCC_T Delay1_d;           /* '<S47>/Delay1' */
  DW_Delay_EDCC_o_T Delay_jd;          /* '<S47>/Delay' */
  DW_Delay_EDCC_T Delay_l;             /* '<S56>/Delay' */
  DW_Delay1_EDCC_T Delay1;             /* '<S10>/Delay1' */
  DW_Delay_EDCC_o_T Delay;             /* '<S10>/Delay' */
  DW_Delay_EDCC_T Delay_j;             /* '<S19>/Delay' */
} DW_EDCC_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S70>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S70>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S70>/Data Type Conversion2' */
  const uint8_T DataTypeConversion11;  /* '<S45>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13;  /* '<S45>/Data Type Conversion13' */
  const uint8_T DataTypeConversion2_e; /* '<S45>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S45>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S45>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S45>/Data Type Conversion5' */
  const uint8_T DataTypeConversion9;   /* '<S45>/Data Type Conversion9' */
  const uint8_T DataTypeConversion1_e; /* '<S69>/Data Type Conversion1' */
  const uint8_T DataTypeConversion8;   /* '<S46>/Data Type Conversion8' */
  const uint8_T DataTypeConversion_j;  /* '<S44>/Data Type Conversion' */
  const uint8_T DataTypeConversion_c;  /* '<S43>/Data Type Conversion' */
  const uint8_T DataTypeConversion_b;  /* '<S56>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_j; /* '<S56>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_f; /* '<S56>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_cg; /* '<S42>/Data Type Conversion' */
  const uint8_T DataTypeConversion_m;  /* '<S52>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_a; /* '<S52>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_jy; /* '<S33>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_aa;/* '<S33>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S33>/Data Type Conversion2' */
  const uint8_T DataTypeConversion1_az;/* '<S8>/Data Type Conversion1' */
  const uint8_T DataTypeConversion11_p;/* '<S8>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13_i;/* '<S8>/Data Type Conversion13' */
  const uint8_T DataTypeConversion2_l; /* '<S8>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_j; /* '<S8>/Data Type Conversion3' */
  const uint8_T DataTypeConversion8_l; /* '<S8>/Data Type Conversion8' */
  const uint8_T DataTypeConversion9_m; /* '<S8>/Data Type Conversion9' */
  const uint8_T DataTypeConversion1_m; /* '<S32>/Data Type Conversion1' */
  const uint8_T DataTypeConversion8_h; /* '<S9>/Data Type Conversion8' */
  const uint8_T DataTypeConversion_f;  /* '<S7>/Data Type Conversion' */
  const uint8_T DataTypeConversion_h;  /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion_fk; /* '<S19>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_o; /* '<S19>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_o; /* '<S19>/Data Type Conversion2' */
  const uint8_T DataTypeConversion_i;  /* '<S5>/Data Type Conversion' */
  const uint8_T DataTypeConversion_n;  /* '<S15>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_m3;/* '<S15>/Data Type Conversion1' */
} ConstB_EDCC_T;

/* Real-time Model Data Structure */
struct tag_RTM_EDCC_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EDCC_T EDCC_B;

/* Block states (auto storage) */
extern DW_EDCC_T EDCC_DW;
extern const ConstB_EDCC_T EDCC_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EDCC_initialize(void);

/* Exported entry point functions */
extern void EDCCA_20ms(void);
extern void EDCCB_20ms(void);

/* Real-time Model object */
extern RT_MODEL_EDCC_T *const EDCC_M;

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
 * '<Root>' : 'EDCC'
 * '<S1>'   : 'EDCC/EDCC_All'
 * '<S2>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys'
 * '<S3>'   : 'EDCC/EDCC_All/EDCCB_20ms_Sys'
 * '<S4>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms'
 * '<S5>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AOffline'
 * '<S6>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun'
 * '<S7>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby'
 * '<S8>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq'
 * '<S9>'   : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutVoltReq'
 * '<S10>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd'
 * '<S11>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCARunMode'
 * '<S12>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/EACC_GeEACC_ACDCARunMode_enum'
 * '<S13>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/EACC_GeEACC_ACDCARunMode_enum1'
 * '<S14>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AOffline/OfflineWork'
 * '<S15>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby'
 * '<S16>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby/Delay'
 * '<S17>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby/Delay/Unit Delay Resettable'
 * '<S18>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun/RunWork'
 * '<S19>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun/RunWork/DCDCAVoltBuildFlt'
 * '<S20>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun/RunWork/RunToStandby'
 * '<S21>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun/RunWork/DCDCAVoltBuildFlt/Delay'
 * '<S22>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/ARun/RunWork/DCDCAVoltBuildFlt/Delay/Unit Delay Resettable'
 * '<S23>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby/StandbyWork'
 * '<S24>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline'
 * '<S25>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby/StandbyWork/StandbyToRun'
 * '<S26>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline/Delay'
 * '<S27>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline/Delay/Unit Delay Resettable'
 * '<S28>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/DCDCAMaxCurr'
 * '<S29>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/EACC_GcEACC_ACDCAOutCurrReq_A'
 * '<S30>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/Subsystem'
 * '<S31>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/Subsystem1'
 * '<S32>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/Subsystem2'
 * '<S33>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/DCDCAMaxCurr/DCDCAMaxPwr'
 * '<S34>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutCurrReq/DCDCAMaxCurr/DCDCATablePwr'
 * '<S35>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAOutVoltReq/EACC_GcEACC_ACDCAOutVoltReq_V'
 * '<S36>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd/Delay'
 * '<S37>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd/Delay1'
 * '<S38>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd/EACC_GbEACC_ACDCAPwrOn_flg'
 * '<S39>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd/Delay/Unit Delay Resettable'
 * '<S40>'  : 'EDCC/EDCC_All/EDCCA_20ms_Sys/DCDCCtrA_20ms/DCDCAPwrCmd/Delay1/Unit Delay Resettable'
 * '<S41>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms'
 * '<S42>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BOffline'
 * '<S43>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun'
 * '<S44>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby'
 * '<S45>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq'
 * '<S46>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutVoltReq'
 * '<S47>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd'
 * '<S48>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBRunMode'
 * '<S49>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S50>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/EACC_GeEACC_ACDCARunMode_enum3'
 * '<S51>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BOffline/OfflineWork'
 * '<S52>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby'
 * '<S53>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby/Delay'
 * '<S54>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby/Delay/Unit Delay Resettable'
 * '<S55>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun/RunWork'
 * '<S56>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun/RunWork/DCDCBVoltBuildFlt'
 * '<S57>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun/RunWork/RunToStandby'
 * '<S58>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun/RunWork/DCDCBVoltBuildFlt/Delay'
 * '<S59>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BRun/RunWork/DCDCBVoltBuildFlt/Delay/Unit Delay Resettable'
 * '<S60>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby/StandbyWork'
 * '<S61>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline'
 * '<S62>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby/StandbyWork/StandbyToRun'
 * '<S63>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline/Delay'
 * '<S64>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline/Delay/Unit Delay Resettable'
 * '<S65>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/DCDCBMaxCurr'
 * '<S66>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/EACC_GcEACC_ACDCAOutCurrReq_A'
 * '<S67>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/Subsystem'
 * '<S68>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/Subsystem1'
 * '<S69>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/Subsystem2'
 * '<S70>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/DCDCBMaxCurr/DCDCBMaxPwr'
 * '<S71>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutCurrReq/DCDCBMaxCurr/DCDCBTempPwr'
 * '<S72>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBOutVoltReq/EACC_GcEACC_ACDCAOutVoltReq_V'
 * '<S73>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd/Delay'
 * '<S74>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd/Delay1'
 * '<S75>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd/EACC_GbEACC_ACDCAPwrOn_flg'
 * '<S76>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd/Delay/Unit Delay Resettable'
 * '<S77>'  : 'EDCC/EDCC_All/EDCCB_20ms_Sys/DCDCCtrB_20ms/DCDCBPwrCmd/Delay1/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': EDCC
 */
#endif                                 /* RTW_HEADER_EDCC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
