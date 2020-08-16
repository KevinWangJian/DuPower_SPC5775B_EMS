/*
 * File: EACC.h
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 13:26:06 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EACC_h_
#define RTW_HEADER_EACC_h_
#include <math.h>
#include <stddef.h>
#ifndef EACC_COMMON_INCLUDES_
# define EACC_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EACC_COMMON_INCLUDES_ */

#include "EACC_types.h"

/* Includes for objects with custom storage classes. */
#include "EACC_Const.h"
#include "EACC_Cal.h"
#include "EACC_Var.h"
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

/* Block signals for system '<S7>/Delay' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S24>/Relational Operator' */
} B_Delay_EACC_T;

/* Block states (auto storage) for system '<S7>/Delay' */
typedef struct {
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S27>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S27>/FixPt Unit Delay1' */
} DW_Delay_EACC_T;

/* Block signals for system '<S7>/Delay1' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S25>/Relational Operator' */
} B_Delay1_EACC_T;

/* Block states (auto storage) for system '<S7>/Delay1' */
typedef struct {
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S28>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S28>/FixPt Unit Delay1' */
} DW_Delay1_EACC_T;

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeEACC_ACDCBRunMode_enum;    /* '<S45>/ACDCBRunMode' */
  uint8_T GeEACC_ACDCARunMode_enum;    /* '<S4>/ACDCARunMode' */
  B_Delay1_EACC_T Delay1_p;            /* '<S49>/Delay1' */
  B_Delay_EACC_T Delay_d;              /* '<S49>/Delay' */
  B_Delay1_EACC_T Delay1;              /* '<S7>/Delay1' */
  B_Delay_EACC_T Delay;                /* '<S7>/Delay' */
} B_EACC_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T StateName;                  /* '<S60>/Unit Delay1' */
  real32_T StateName_c;                /* '<S51>/Unit Delay2' */
  real32_T StateName_f;                /* '<S19>/Unit Delay1' */
  real32_T StateName_h;                /* '<S10>/Unit Delay2' */
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S85>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_f;   /* '<S73>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_b;   /* '<S44>/FixPt Unit Delay1' */
  uint16_T FixPtUnitDelay1_DSTATE_i;   /* '<S32>/FixPt Unit Delay1' */
  uint8_T StateName_a;                 /* '<S45>/Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S85>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_n;    /* '<S78>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_g;    /* '<S78>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_j;    /* '<S73>/FixPt Unit Delay2' */
  uint8_T StateName_m;                 /* '<S4>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_p;    /* '<S44>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay2_DSTATE_e;    /* '<S37>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_gn;   /* '<S37>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_d;    /* '<S32>/FixPt Unit Delay2' */
  boolean_T StateName_hu;              /* '<S49>/Unit Delay2' */
  boolean_T StateName_a0;              /* '<S7>/Unit Delay2' */
  uint8_T is_active_c3_EACC;           /* '<S45>/ACDCBRunMode' */
  uint8_T is_c3_EACC;                  /* '<S45>/ACDCBRunMode' */
  uint8_T is_active_c4_EACC;           /* '<S4>/ACDCARunMode' */
  uint8_T is_c4_EACC;                  /* '<S4>/ACDCARunMode' */
  boolean_T StandbyWork_MODE;          /* '<S55>/StandbyWork' */
  boolean_T RunWork_MODE;              /* '<S54>/RunWork' */
  boolean_T PrechrgWork_MODE;          /* '<S53>/PrechrgWork' */
  boolean_T OfflineWork_MODE;          /* '<S52>/OfflineWork' */
  boolean_T StandbyWork_MODE_f;        /* '<S14>/StandbyWork' */
  boolean_T RunWork_MODE_f;            /* '<S13>/RunWork' */
  boolean_T PrechrgWork_MODE_g;        /* '<S12>/PrechrgWork' */
  boolean_T OfflineWork_MODE_i;        /* '<S11>/OfflineWork' */
  DW_Delay1_EACC_T Delay1_p;           /* '<S49>/Delay1' */
  DW_Delay_EACC_T Delay_d;             /* '<S49>/Delay' */
  DW_Delay1_EACC_T Delay1;             /* '<S7>/Delay1' */
  DW_Delay_EACC_T Delay;               /* '<S7>/Delay' */
} DW_EACC_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S60>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S60>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S60>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S51>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S51>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5;   /* '<S51>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6;   /* '<S51>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7;   /* '<S51>/Data Type Conversion7' */
  const uint8_T DataTypeConversion1_n; /* '<S47>/Data Type Conversion1' */
  const uint8_T DataTypeConversion11;  /* '<S47>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13;  /* '<S47>/Data Type Conversion13' */
  const uint8_T DataTypeConversion8;   /* '<S47>/Data Type Conversion8' */
  const uint8_T DataTypeConversion9;   /* '<S47>/Data Type Conversion9' */
  const uint8_T DataTypeConversion_c;  /* '<S55>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d;  /* '<S83>/Data Type Conversion' */
  const uint8_T DataTypeConversion_h;  /* '<S54>/Data Type Conversion' */
  const uint8_T DataTypeConversion_i;  /* '<S80>/Data Type Conversion' */
  const uint8_T DataTypeConversion_p;  /* '<S53>/Data Type Conversion' */
  const uint8_T DataTypeConversion_f;  /* '<S76>/Data Type Conversion' */
  const uint8_T DataTypeConversion_o;  /* '<S75>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_b; /* '<S75>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S75>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_p; /* '<S75>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_f; /* '<S75>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_e; /* '<S75>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_l; /* '<S75>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_n; /* '<S75>/Data Type Conversion7' */
  const uint8_T DataTypeConversion_m;  /* '<S52>/Data Type Conversion' */
  const uint8_T DataTypeConversion_p5; /* '<S48>/Data Type Conversion' */
  const uint8_T DataTypeConversion8_k; /* '<S48>/Data Type Conversion8' */
  const uint8_T DataTypeConversion1_m; /* '<S63>/Data Type Conversion1' */
  const uint8_T DataTypeConversion3_o; /* '<S63>/Data Type Conversion3' */
  const uint8_T DataTypeConversion5_k; /* '<S63>/Data Type Conversion5' */
  const uint8_T DataTypeConversion7_j; /* '<S63>/Data Type Conversion7' */
  const uint8_T DataTypeConversion9_p; /* '<S64>/Data Type Conversion9' */
  const uint8_T DataTypeConversion11_m;/* '<S64>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13_e;/* '<S64>/Data Type Conversion13' */
  const uint8_T DataTypeConversion15;  /* '<S64>/Data Type Conversion15' */
  const uint8_T DataTypeConversion_ib; /* '<S19>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_f; /* '<S19>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_i; /* '<S19>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_c; /* '<S10>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_p; /* '<S10>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_b; /* '<S10>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_e; /* '<S10>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_o; /* '<S10>/Data Type Conversion7' */
  const uint8_T DataTypeConversion1_p; /* '<S5>/Data Type Conversion1' */
  const uint8_T DataTypeConversion11_j;/* '<S5>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13_d;/* '<S5>/Data Type Conversion13' */
  const uint8_T DataTypeConversion8_g; /* '<S5>/Data Type Conversion8' */
  const uint8_T DataTypeConversion9_b; /* '<S5>/Data Type Conversion9' */
  const uint8_T DataTypeConversion_mq; /* '<S14>/Data Type Conversion' */
  const uint8_T DataTypeConversion_fg; /* '<S42>/Data Type Conversion' */
  const uint8_T DataTypeConversion_dd; /* '<S13>/Data Type Conversion' */
  const uint8_T DataTypeConversion_b;  /* '<S39>/Data Type Conversion' */
  const uint8_T DataTypeConversion_om; /* '<S12>/Data Type Conversion' */
  const uint8_T DataTypeConversion_i3; /* '<S35>/Data Type Conversion' */
  const uint8_T DataTypeConversion_cf; /* '<S34>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_nd;/* '<S34>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_e; /* '<S34>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_d; /* '<S34>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_c; /* '<S34>/Data Type Conversion4' */
  const uint8_T DataTypeConversion5_n; /* '<S34>/Data Type Conversion5' */
  const uint8_T DataTypeConversion6_p; /* '<S34>/Data Type Conversion6' */
  const uint8_T DataTypeConversion7_jp;/* '<S34>/Data Type Conversion7' */
  const uint8_T DataTypeConversion_g;  /* '<S11>/Data Type Conversion' */
  const uint8_T DataTypeConversion_l;  /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion8_f; /* '<S6>/Data Type Conversion8' */
  const uint8_T DataTypeConversion1_e; /* '<S22>/Data Type Conversion1' */
  const uint8_T DataTypeConversion3_b; /* '<S22>/Data Type Conversion3' */
  const uint8_T DataTypeConversion5_nv;/* '<S22>/Data Type Conversion5' */
  const uint8_T DataTypeConversion7_i; /* '<S22>/Data Type Conversion7' */
  const uint8_T DataTypeConversion9_e; /* '<S23>/Data Type Conversion9' */
  const uint8_T DataTypeConversion11_g;/* '<S23>/Data Type Conversion11' */
  const uint8_T DataTypeConversion13_m;/* '<S23>/Data Type Conversion13' */
  const uint8_T DataTypeConversion15_e;/* '<S23>/Data Type Conversion15' */
} ConstB_EACC_T;

/* Real-time Model Data Structure */
struct tag_RTM_EACC_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EACC_T EACC_B;

/* Block states (auto storage) */
extern DW_EACC_T EACC_DW;
extern const ConstB_EACC_T EACC_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EACC_initialize(void);

/* Exported entry point functions */
extern void EACCA_20ms(void);
extern void EACCB_20ms(void);

/* Real-time Model object */
extern RT_MODEL_EACC_T *const EACC_M;

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
 * '<Root>' : 'EACC'
 * '<S1>'   : 'EACC/EACC_All'
 * '<S2>'   : 'EACC/EACC_All/EACCA_20ms_Sys'
 * '<S3>'   : 'EACC/EACC_All/EACCB_20ms_Sys'
 * '<S4>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms'
 * '<S5>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq'
 * '<S6>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutVoltReq'
 * '<S7>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd'
 * '<S8>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCARunMode'
 * '<S9>'   : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAWork'
 * '<S10>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCScreenInputPwr'
 * '<S11>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AOffline'
 * '<S12>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg'
 * '<S13>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ARun'
 * '<S14>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby'
 * '<S15>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/EACC_GeEACC_ACDCARunMode_enum'
 * '<S16>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq/ACDCAMaxCurr'
 * '<S17>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq/EACC_GcEACC_ACDCAOutCurrReq_A'
 * '<S18>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq/Subsystem'
 * '<S19>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq/ACDCAMaxCurr/ACDCAMaxPwr'
 * '<S20>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutCurrReq/ACDCAMaxCurr/ACDCATempPwr'
 * '<S21>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutVoltReq/EACC_GcEACC_ACDCAOutVoltReq_V'
 * '<S22>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutVoltReq/PrechrgACDCAOutVoltReq'
 * '<S23>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAOutVoltReq/RunACDCAOutVoltReq'
 * '<S24>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd/Delay'
 * '<S25>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd/Delay1'
 * '<S26>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd/EACC_GbEACC_ACDCAPwrOn_flg'
 * '<S27>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd/Delay/Unit Delay Resettable'
 * '<S28>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ACDCAPwrCmd/Delay1/Unit Delay Resettable'
 * '<S29>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AOffline/OfflineWork'
 * '<S30>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby'
 * '<S31>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby/Delay'
 * '<S32>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AOffline/OfflineWork/OfflineToStandby/Delay/Unit Delay Resettable'
 * '<S33>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg/PrechrgWork'
 * '<S34>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg/PrechrgWork/PrechrgToRun'
 * '<S35>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg/PrechrgWork/PrechrgToStandby'
 * '<S36>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg/PrechrgWork/PrechrgToStandby/Delay'
 * '<S37>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/APrechrg/PrechrgWork/PrechrgToStandby/Delay/Unit Delay Resettable'
 * '<S38>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ARun/RunWork'
 * '<S39>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/ARun/RunWork/RunToStandby'
 * '<S40>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby/StandbyWork'
 * '<S41>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline'
 * '<S42>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby/StandbyWork/StandbyToPrechrg'
 * '<S43>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline/Delay'
 * '<S44>'  : 'EACC/EACC_All/EACCA_20ms_Sys/ACDCCtrA_20ms/AStandby/StandbyWork/StandbyToOffline/Delay/Unit Delay Resettable'
 * '<S45>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms'
 * '<S46>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCAWork'
 * '<S47>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq'
 * '<S48>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutVoltReq'
 * '<S49>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd'
 * '<S50>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBRunMode'
 * '<S51>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCScreenInputPwr'
 * '<S52>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BOffline'
 * '<S53>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg'
 * '<S54>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BRun'
 * '<S55>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby'
 * '<S56>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/EACC_GeEACC_ACDCBRunMode_enum'
 * '<S57>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq/ACDCBMaxCurr'
 * '<S58>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq/EACC_GcEACC_ACDCBOutCurrReq_A'
 * '<S59>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq/Subsystem'
 * '<S60>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq/ACDCBMaxCurr/ACDCBMaxPwr'
 * '<S61>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutCurrReq/ACDCBMaxCurr/ACDCBTempPwr'
 * '<S62>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutVoltReq/EACC_GcEACC_ACDCBOutVoltReq_V'
 * '<S63>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutVoltReq/PrechrgACDCBOutVoltReq'
 * '<S64>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBOutVoltReq/RunACDCBOutVoltReq'
 * '<S65>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd/Delay'
 * '<S66>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd/Delay1'
 * '<S67>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd/EACC_GbEACC_ACDCBPwrOn_flg'
 * '<S68>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd/Delay/Unit Delay Resettable'
 * '<S69>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/ACDCBPwrCmd/Delay1/Unit Delay Resettable'
 * '<S70>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BOffline/OfflineWork'
 * '<S71>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby'
 * '<S72>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby/Delay'
 * '<S73>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BOffline/OfflineWork/OfflineToStandby/Delay/Unit Delay Resettable'
 * '<S74>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg/PrechrgWork'
 * '<S75>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg/PrechrgWork/PrechrgToRun'
 * '<S76>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg/PrechrgWork/PrechrgToStandby'
 * '<S77>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg/PrechrgWork/PrechrgToStandby/Delay'
 * '<S78>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BPrechrg/PrechrgWork/PrechrgToStandby/Delay/Unit Delay Resettable'
 * '<S79>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BRun/RunWork'
 * '<S80>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BRun/RunWork/RunToStandby'
 * '<S81>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby/StandbyWork'
 * '<S82>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline'
 * '<S83>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby/StandbyWork/StandbyToPrechrg'
 * '<S84>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline/Delay'
 * '<S85>'  : 'EACC/EACC_All/EACCB_20ms_Sys/ACDCCtrB_20ms/BStandby/StandbyWork/StandbyToOffline/Delay/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': EACC
 */
#endif                                 /* RTW_HEADER_EACC_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
