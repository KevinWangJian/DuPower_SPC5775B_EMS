/*
 * File: ECMM.h
 *
 * Code generated for Simulink model 'ECMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed May 20 17:27:26 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECMM_h_
#define RTW_HEADER_ECMM_h_
#include <stddef.h>
#ifndef ECMM_COMMON_INCLUDES_
# define ECMM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ECMM_COMMON_INCLUDES_ */

#include "ECMM_types.h"

/* Includes for objects with custom storage classes. */
#include "ECMM_Const.h"
#include "ECMM_Cal.h"
#include "ECMM_Var.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeECMM_ChrgCtrBMode_enum;    /* '<S49>/ChrgCtrBMode' */
  uint8_T GeECMM_ChrgCtrAMode_enum;    /* '<S4>/ChrgCtrAMode' */
} B_ECMM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T StateName;                   /* '<S49>/Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S93>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S93>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_k;    /* '<S89>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_c;    /* '<S89>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_i;    /* '<S85>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_l;    /* '<S85>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_n;    /* '<S83>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_b;    /* '<S83>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_m;    /* '<S81>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_li;   /* '<S81>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_d;    /* '<S79>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_j;    /* '<S79>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_ia;   /* '<S77>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_d;    /* '<S77>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_mk;   /* '<S69>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_p;    /* '<S69>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_o;    /* '<S65>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_pe;   /* '<S65>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_mx;   /* '<S61>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_jb;   /* '<S61>/FixPt Unit Delay1' */
  uint8_T StateName_m;                 /* '<S4>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_c;    /* '<S48>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_bc;   /* '<S48>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_km;   /* '<S44>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_bu;   /* '<S44>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_io;   /* '<S40>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_dd;   /* '<S40>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_e;    /* '<S38>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_h;    /* '<S38>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_b;    /* '<S36>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_pa;   /* '<S36>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_kg;   /* '<S34>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_e;    /* '<S34>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_j;    /* '<S32>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_m;    /* '<S32>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_k5;   /* '<S24>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_j4;   /* '<S24>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_e2;   /* '<S20>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_dy;   /* '<S20>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE_l;    /* '<S16>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_o;    /* '<S16>/FixPt Unit Delay1' */
  uint8_T is_active_c3_ECMM;           /* '<S49>/ChrgCtrBMode' */
  uint8_T is_c3_ECMM;                  /* '<S49>/ChrgCtrBMode' */
  uint8_T is_active_c4_ECMM;           /* '<S4>/ChrgCtrAMode' */
  uint8_T is_c4_ECMM;                  /* '<S4>/ChrgCtrAMode' */
  boolean_T ReChrgWork_MODE;           /* '<S55>/ReChrgWork' */
  boolean_T OfflineWork_MODE;          /* '<S54>/OfflineWork' */
  boolean_T IdleWork_MODE;             /* '<S53>/IdleWork' */
  boolean_T ChrgWork_MODE;             /* '<S52>/ChrgWork' */
  boolean_T CChrgWork_MODE;            /* '<S51>/CChrgWork' */
  boolean_T BCChrgWork_MODE;           /* '<S50>/BCChrgWork' */
  boolean_T ReChrgWork_MODE_p;         /* '<S10>/ReChrgWork' */
  boolean_T OfflineWork_MODE_i;        /* '<S9>/OfflineWork' */
  boolean_T IdleWork_MODE_c;           /* '<S8>/IdleWork' */
  boolean_T ChrgWork_MODE_a;           /* '<S7>/ChrgWork' */
  boolean_T CChrgWork_MODE_o;          /* '<S6>/CChrgWork' */
  boolean_T BCChrgWork_MODE_m;         /* '<S5>/BCChrgWork' */
} DW_ECMM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S55>/Data Type Conversion' */
  const uint8_T DataTypeConversion_j;  /* '<S91>/Data Type Conversion' */
  const uint8_T DataTypeConversion_i;  /* '<S54>/Data Type Conversion' */
  const uint8_T DataTypeConversion_a;  /* '<S87>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S87>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_ib; /* '<S53>/Data Type Conversion' */
  const uint8_T DataTypeConversion_n;  /* '<S71>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_g; /* '<S71>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_c;  /* '<S72>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_p; /* '<S72>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_ci; /* '<S73>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d;  /* '<S75>/Data Type Conversion' */
  const uint8_T DataTypeConversion_l;  /* '<S52>/Data Type Conversion' */
  const uint8_T DataTypeConversion_m;  /* '<S67>/Data Type Conversion' */
  const uint8_T DataTypeConversion_jf; /* '<S51>/Data Type Conversion' */
  const uint8_T DataTypeConversion_e;  /* '<S50>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d0; /* '<S10>/Data Type Conversion' */
  const uint8_T DataTypeConversion_dx; /* '<S46>/Data Type Conversion' */
  const uint8_T DataTypeConversion_g;  /* '<S9>/Data Type Conversion' */
  const uint8_T DataTypeConversion_f;  /* '<S42>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_l; /* '<S42>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_k;  /* '<S8>/Data Type Conversion' */
  const uint8_T DataTypeConversion_o;  /* '<S26>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_k; /* '<S26>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_b;  /* '<S27>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_c; /* '<S27>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_cr; /* '<S28>/Data Type Conversion' */
  const uint8_T DataTypeConversion_is; /* '<S30>/Data Type Conversion' */
  const uint8_T DataTypeConversion_kr; /* '<S7>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d3; /* '<S22>/Data Type Conversion' */
  const uint8_T DataTypeConversion_fo; /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d0o;/* '<S5>/Data Type Conversion' */
} ConstB_ECMM_T;

/* Real-time Model Data Structure */
struct tag_RTM_ECMM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ECMM_T ECMM_B;

/* Block states (auto storage) */
extern DW_ECMM_T ECMM_DW;
extern const ConstB_ECMM_T ECMM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ECMM_initialize(void);

/* Exported entry point functions */
extern void ECMMA_20ms(void);
extern void ECMMB_20ms(void);

/* Real-time Model object */
extern RT_MODEL_ECMM_T *const ECMM_M;

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
 * '<Root>' : 'ECMM'
 * '<S1>'   : 'ECMM/ECMM_All'
 * '<S2>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys'
 * '<S3>'   : 'ECMM/ECMM_All/ECMMB_20ms_Sys'
 * '<S4>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms'
 * '<S5>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ABCChrg'
 * '<S6>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ACChrg'
 * '<S7>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AChrg'
 * '<S8>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle'
 * '<S9>'   : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AOffline'
 * '<S10>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AReChrg'
 * '<S11>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ChrgCtrAMode'
 * '<S12>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S13>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ABCChrg/BCChrgWork'
 * '<S14>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ABCChrg/BCChrgWork/BCChrgToIdle'
 * '<S15>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ABCChrg/BCChrgWork/BCChrgToIdle/Delay'
 * '<S16>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ABCChrg/BCChrgWork/BCChrgToIdle/Delay/Unit Delay Resettable'
 * '<S17>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ACChrg/CChrgWork'
 * '<S18>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ACChrg/CChrgWork/CChrgToIdle'
 * '<S19>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ACChrg/CChrgWork/CChrgToIdle/Delay'
 * '<S20>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/ACChrg/CChrgWork/CChrgToIdle/Delay/Unit Delay Resettable'
 * '<S21>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AChrg/ChrgWork'
 * '<S22>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AChrg/ChrgWork/ChrgToIdle'
 * '<S23>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AChrg/ChrgWork/ChrgToIdle/Delay'
 * '<S24>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AChrg/ChrgWork/ChrgToIdle/Delay/Unit Delay Resettable'
 * '<S25>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork'
 * '<S26>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToBCChrg'
 * '<S27>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToCChrg'
 * '<S28>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToChrg'
 * '<S29>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToOffline'
 * '<S30>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToReChrg'
 * '<S31>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToBCChrg/Delay'
 * '<S32>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToBCChrg/Delay/Unit Delay Resettable'
 * '<S33>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToCChrg/Delay'
 * '<S34>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToCChrg/Delay/Unit Delay Resettable'
 * '<S35>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToChrg/Delay'
 * '<S36>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToChrg/Delay/Unit Delay Resettable'
 * '<S37>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToOffline/Delay'
 * '<S38>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToOffline/Delay/Unit Delay Resettable'
 * '<S39>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToReChrg/Delay'
 * '<S40>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AIdle/IdleWork/IdleToReChrg/Delay/Unit Delay Resettable'
 * '<S41>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AOffline/OfflineWork'
 * '<S42>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AOffline/OfflineWork/OfflineToIdel'
 * '<S43>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AOffline/OfflineWork/OfflineToIdel/Delay'
 * '<S44>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AOffline/OfflineWork/OfflineToIdel/Delay/Unit Delay Resettable'
 * '<S45>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AReChrg/ReChrgWork'
 * '<S46>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AReChrg/ReChrgWork/ReChrgToIdle'
 * '<S47>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AReChrg/ReChrgWork/ReChrgToIdle/Delay'
 * '<S48>'  : 'ECMM/ECMM_All/ECMMA_20ms_Sys/ChrgModeManageA_20ms/AReChrg/ReChrgWork/ReChrgToIdle/Delay/Unit Delay Resettable'
 * '<S49>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms'
 * '<S50>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BBCChrg'
 * '<S51>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BCChrg'
 * '<S52>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BChrg'
 * '<S53>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle'
 * '<S54>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BOffline'
 * '<S55>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BReChrg'
 * '<S56>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/ChrgCtrBMode'
 * '<S57>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S58>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BBCChrg/BCChrgWork'
 * '<S59>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BBCChrg/BCChrgWork/BCChrgToIdle'
 * '<S60>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BBCChrg/BCChrgWork/BCChrgToIdle/Delay'
 * '<S61>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BBCChrg/BCChrgWork/BCChrgToIdle/Delay/Unit Delay Resettable'
 * '<S62>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BCChrg/CChrgWork'
 * '<S63>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BCChrg/CChrgWork/CChrgToIdle'
 * '<S64>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BCChrg/CChrgWork/CChrgToIdle/Delay'
 * '<S65>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BCChrg/CChrgWork/CChrgToIdle/Delay/Unit Delay Resettable'
 * '<S66>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BChrg/ChrgWork'
 * '<S67>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BChrg/ChrgWork/ChrgToIdle'
 * '<S68>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BChrg/ChrgWork/ChrgToIdle/Delay'
 * '<S69>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BChrg/ChrgWork/ChrgToIdle/Delay/Unit Delay Resettable'
 * '<S70>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork'
 * '<S71>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToBCChrg'
 * '<S72>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToCChrg'
 * '<S73>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToChrg'
 * '<S74>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToOffline'
 * '<S75>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToReChrg'
 * '<S76>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToBCChrg/Delay'
 * '<S77>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToBCChrg/Delay/Unit Delay Resettable'
 * '<S78>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToCChrg/Delay'
 * '<S79>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToCChrg/Delay/Unit Delay Resettable'
 * '<S80>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToChrg/Delay'
 * '<S81>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToChrg/Delay/Unit Delay Resettable'
 * '<S82>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToOffline/Delay'
 * '<S83>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToOffline/Delay/Unit Delay Resettable'
 * '<S84>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToReChrg/Delay'
 * '<S85>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BIdle/IdleWork/IdleToReChrg/Delay/Unit Delay Resettable'
 * '<S86>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BOffline/OfflineWork'
 * '<S87>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BOffline/OfflineWork/OfflineToIdel'
 * '<S88>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BOffline/OfflineWork/OfflineToIdel/Delay'
 * '<S89>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BOffline/OfflineWork/OfflineToIdel/Delay/Unit Delay Resettable'
 * '<S90>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BReChrg/ReChrgWork'
 * '<S91>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BReChrg/ReChrgWork/ReChrgToIdle'
 * '<S92>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BReChrg/ReChrgWork/ReChrgToIdle/Delay'
 * '<S93>'  : 'ECMM/ECMM_All/ECMMB_20ms_Sys/ChrgModeManageB_20ms/BReChrg/ReChrgWork/ReChrgToIdle/Delay/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': ECMM
 */
#endif                                 /* RTW_HEADER_ECMM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
