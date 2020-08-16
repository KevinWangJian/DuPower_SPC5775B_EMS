/*
 * File: ECIM.h
 *
 * Code generated for Simulink model 'ECIM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jun 10 09:42:58 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECIM_h_
#define RTW_HEADER_ECIM_h_
#include <stddef.h>
#ifndef ECIM_COMMON_INCLUDES_
# define ECIM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ECIM_COMMON_INCLUDES_ */

#include "ECIM_types.h"

/* Includes for objects with custom storage classes. */
#include "ECIM_Const.h"
#include "ECIM_Cal.h"
#include "ECIM_Var.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S7>/Delay' */
typedef struct {
  boolean_T RelationalOperator;        /* '<S19>/Relational Operator' */
} B_Delay_ECIM_T;

/* Block states (auto storage) for system '<S7>/Delay' */
typedef struct {
  uint16_T FixPtUnitDelay1_DSTATE;     /* '<S22>/FixPt Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S22>/FixPt Unit Delay2' */
} DW_Delay_ECIM_T;

/* Block signals for system '<S7>/DiffValue' */
typedef struct {
  real32_T Switch;                     /* '<S20>/Switch' */
} B_DiffValue_ECIM_T;

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeECIM_GunBIntactMode_enum;  /* '<S34>/GunBIntactMode' */
  uint8_T GeECIM_GunAIntactMode_enum;  /* '<S4>/GunAIntactMode' */
  B_DiffValue_ECIM_T DiffValue_h;      /* '<S37>/DiffValue' */
  B_Delay_ECIM_T Delay_b;              /* '<S37>/Delay' */
  B_DiffValue_ECIM_T DiffValue;        /* '<S7>/DiffValue' */
  B_Delay_ECIM_T Delay;                /* '<S7>/Delay' */
} B_ECIM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T StateName;                  /* '<S38>/Unit Delay1' */
  real32_T StateName_n;                /* '<S8>/Unit Delay1' */
  uint8_T StateName_g;                 /* '<S34>/Unit Delay1' */
  uint8_T FixPtUnitDelay2_DSTATE;      /* '<S63>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE;      /* '<S63>/FixPt Unit Delay1' */
  uint8_T StateName_m;                 /* '<S4>/Unit Delay' */
  uint8_T FixPtUnitDelay2_DSTATE_c;    /* '<S33>/FixPt Unit Delay2' */
  uint8_T FixPtUnitDelay1_DSTATE_f;    /* '<S33>/FixPt Unit Delay1' */
  uint8_T is_active_c3_ECIM;           /* '<S34>/GunBIntactMode' */
  uint8_T is_c3_ECIM;                  /* '<S34>/GunBIntactMode' */
  uint8_T is_active_c4_ECIM;           /* '<S4>/GunAIntactMode' */
  uint8_T is_c4_ECIM;                  /* '<S4>/GunAIntactMode' */
  boolean_T UnloadWork_MODE;           /* '<S41>/UnloadWork' */
  boolean_T OfflineWork_MODE;          /* '<S40>/OfflineWork' */
  boolean_T ISOWork_MODE;              /* '<S39>/ISOWork' */
  boolean_T BCPWork_MODE;              /* '<S36>/BCPWork' */
  boolean_T BCLWork_MODE;              /* '<S35>/BCLWork' */
  boolean_T UnloadWork_MODE_b;         /* '<S11>/UnloadWork' */
  boolean_T OfflineWork_MODE_i;        /* '<S10>/OfflineWork' */
  boolean_T ISOWork_MODE_n;            /* '<S9>/ISOWork' */
  boolean_T BCPWork_MODE_j;            /* '<S6>/BCPWork' */
  boolean_T BCLWork_MODE_g;            /* '<S5>/BCLWork' */
  DW_Delay_ECIM_T Delay_b;             /* '<S37>/Delay' */
  DW_Delay_ECIM_T Delay;               /* '<S7>/Delay' */
} DW_ECIM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S41>/Data Type Conversion' */
  const uint8_T DataTypeConversion_e;  /* '<S40>/Data Type Conversion' */
  const uint8_T DataTypeConversion_m;  /* '<S39>/Data Type Conversion' */
  const uint8_T DataTypeConversion_b;  /* '<S38>/Data Type Conversion' */
  const uint8_T DataTypeConversion1;   /* '<S38>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S38>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3;   /* '<S38>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4;   /* '<S38>/Data Type Conversion4' */
  const uint8_T DataTypeConversion4_c; /* '<S37>/Data Type Conversion4' */
  const uint8_T DataTypeConversion_g;  /* '<S36>/Data Type Conversion' */
  const uint8_T DataTypeConversion_eb; /* '<S35>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d;  /* '<S11>/Data Type Conversion' */
  const uint8_T DataTypeConversion_gt; /* '<S10>/Data Type Conversion' */
  const uint8_T DataTypeConversion_mq; /* '<S9>/Data Type Conversion' */
  const uint8_T DataTypeConversion_j;  /* '<S8>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_e; /* '<S8>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_i; /* '<S8>/Data Type Conversion2' */
  const uint8_T DataTypeConversion3_f; /* '<S8>/Data Type Conversion3' */
  const uint8_T DataTypeConversion4_n; /* '<S8>/Data Type Conversion4' */
  const uint8_T DataTypeConversion4_a; /* '<S7>/Data Type Conversion4' */
  const uint8_T DataTypeConversion_n;  /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion_db; /* '<S5>/Data Type Conversion' */
} ConstB_ECIM_T;

/* Real-time Model Data Structure */
struct tag_RTM_ECIM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ECIM_T ECIM_B;

/* Block states (auto storage) */
extern DW_ECIM_T ECIM_DW;
extern const ConstB_ECIM_T ECIM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void ECIM_initialize(void);

/* Exported entry point functions */
extern void ECIMA_10ms(void);
extern void ECIMB_10ms(void);

/* Real-time Model object */
extern RT_MODEL_ECIM_T *const ECIM_M;

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
 * '<Root>' : 'ECIM'
 * '<S1>'   : 'ECIM/ECIM_All'
 * '<S2>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys'
 * '<S3>'   : 'ECIM/ECIM_All/ECIMB_10ms_Sys'
 * '<S4>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms'
 * '<S5>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCL'
 * '<S6>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCP'
 * '<S7>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AEMSAlready'
 * '<S8>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AExpOutputVolt'
 * '<S9>'   : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AISO'
 * '<S10>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AOffline'
 * '<S11>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload'
 * '<S12>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/EACC_GeEACC_ACDCARunMode_enum'
 * '<S13>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/GunAIntactMode'
 * '<S14>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCL/BCLWork'
 * '<S15>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCL/BCLWork/BCLToOffline'
 * '<S16>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCP/BCPWork'
 * '<S17>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCP/BCPWork/BCPToBCL'
 * '<S18>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/ABCP/BCPWork/BCPToOffline'
 * '<S19>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AEMSAlready/Delay'
 * '<S20>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AEMSAlready/DiffValue'
 * '<S21>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AEMSAlready/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S22>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AEMSAlready/Delay/Unit Delay Resettable'
 * '<S23>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AExpOutputVolt/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S24>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AISO/ISOWork'
 * '<S25>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AISO/ISOWork/ISOToOffline'
 * '<S26>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AISO/ISOWork/ISOToUnload'
 * '<S27>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AOffline/OfflineWork'
 * '<S28>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AOffline/OfflineWork/OfflineToISO'
 * '<S29>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload/UnloadWork'
 * '<S30>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload/UnloadWork/UnloadToBCP'
 * '<S31>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload/UnloadWork/UnloadToOffline'
 * '<S32>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload/UnloadWork/UnloadToBCP/Delay'
 * '<S33>'  : 'ECIM/ECIM_All/ECIMA_10ms_Sys/EMSCCUAIntactMan_10ms/AUnload/UnloadWork/UnloadToBCP/Delay/Unit Delay Resettable'
 * '<S34>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms'
 * '<S35>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCL'
 * '<S36>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCP'
 * '<S37>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BEMSAlready'
 * '<S38>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BExpOutputVolt'
 * '<S39>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BISO'
 * '<S40>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BOffline'
 * '<S41>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload'
 * '<S42>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S43>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/GunBIntactMode'
 * '<S44>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCL/BCLWork'
 * '<S45>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCL/BCLWork/BCLToOffline'
 * '<S46>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCP/BCPWork'
 * '<S47>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCP/BCPWork/BCPToBCL'
 * '<S48>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BBCP/BCPWork/BCPToOffline'
 * '<S49>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BEMSAlready/Delay'
 * '<S50>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BEMSAlready/DiffValue'
 * '<S51>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BEMSAlready/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S52>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BEMSAlready/Delay/Unit Delay Resettable'
 * '<S53>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BExpOutputVolt/EACC_GeEACC_ACDCARunMode_enum2'
 * '<S54>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BISO/ISOWork'
 * '<S55>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BISO/ISOWork/ISOToOffline'
 * '<S56>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BISO/ISOWork/ISOToUnload'
 * '<S57>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BOffline/OfflineWork'
 * '<S58>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BOffline/OfflineWork/OfflineToISO'
 * '<S59>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload/UnloadWork'
 * '<S60>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload/UnloadWork/UnloadToBCP'
 * '<S61>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload/UnloadWork/UnloadToOffline'
 * '<S62>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload/UnloadWork/UnloadToBCP/Delay'
 * '<S63>'  : 'ECIM/ECIM_All/ECIMB_10ms_Sys/EMSCCUBIntactMan_10ms/BUnload/UnloadWork/UnloadToBCP/Delay/Unit Delay Resettable'
 */

/*-
 * Requirements for '<Root>': ECIM
 */
#endif                                 /* RTW_HEADER_ECIM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
