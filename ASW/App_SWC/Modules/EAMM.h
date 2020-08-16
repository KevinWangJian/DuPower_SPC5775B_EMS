/*
 * File: EAMM.h
 *
 * Code generated for Simulink model 'EAMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 14:33:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EAMM_h_
#define RTW_HEADER_EAMM_h_
#include <stddef.h>
#ifndef EAMM_COMMON_INCLUDES_
# define EAMM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EAMM_COMMON_INCLUDES_ */

#include "EAMM_types.h"

/* Includes for objects with custom storage classes. */
#include "EAMM_Cal.h"
#include "EAMM_Var.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  uint8_T GeEAMM_ACDCBWorkMode_enum;   /* '<S21>/ACDCBWorkMode' */
  uint8_T GeEAMM_ACDCAWorkMode_enum;   /* '<S4>/ACDCAWorkMode' */
} B_EAMM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T StateName;                   /* '<S21>/Unit Delay1' */
  uint8_T StateName_m;                 /* '<S4>/Unit Delay' */
  uint8_T is_active_c3_EAMM;           /* '<S21>/ACDCBWorkMode' */
  uint8_T is_c3_EAMM;                  /* '<S21>/ACDCBWorkMode' */
  uint8_T is_active_c4_EAMM;           /* '<S4>/ACDCAWorkMode' */
  uint8_T is_c4_EAMM;                  /* '<S4>/ACDCAWorkMode' */
  boolean_T PackBWork_MODE;            /* '<S26>/PackBWork' */
  boolean_T OfflineWork_MODE;          /* '<S25>/OfflineWork' */
  boolean_T GunBWork_MODE;             /* '<S24>/GunBWork' */
  boolean_T GunAWork_MODE;             /* '<S23>/GunAWork' */
  boolean_T PackAWork_MODE;            /* '<S9>/PackAWork' */
  boolean_T OfflineWork_MODE_i;        /* '<S8>/OfflineWork' */
  boolean_T GunBWork_MODE_g;           /* '<S7>/GunBWork' */
  boolean_T GunAWork_MODE_p;           /* '<S6>/GunAWork' */
} DW_EAMM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion;    /* '<S26>/Data Type Conversion' */
  const uint8_T DataTypeConversion_n;  /* '<S37>/Data Type Conversion' */
  const uint8_T DataTypeConversion_nl; /* '<S25>/Data Type Conversion' */
  const uint8_T DataTypeConversion_o;  /* '<S33>/Data Type Conversion' */
  const uint8_T DataTypeConversion_m;  /* '<S34>/Data Type Conversion' */
  const uint8_T DataTypeConversion_og; /* '<S35>/Data Type Conversion' */
  const uint8_T DataTypeConversion_ng; /* '<S24>/Data Type Conversion' */
  const uint8_T DataTypeConversion_p;  /* '<S31>/Data Type Conversion' */
  const uint8_T DataTypeConversion_d;  /* '<S23>/Data Type Conversion' */
  const uint8_T DataTypeConversion_b;  /* '<S29>/Data Type Conversion' */
  const uint8_T DataTypeConversion_dd; /* '<S9>/Data Type Conversion' */
  const uint8_T DataTypeConversion_c;  /* '<S20>/Data Type Conversion' */
  const uint8_T DataTypeConversion_g;  /* '<S8>/Data Type Conversion' */
  const uint8_T DataTypeConversion_f;  /* '<S16>/Data Type Conversion' */
  const uint8_T DataTypeConversion_a;  /* '<S17>/Data Type Conversion' */
  const uint8_T DataTypeConversion_i;  /* '<S18>/Data Type Conversion' */
  const uint8_T DataTypeConversion_om; /* '<S7>/Data Type Conversion' */
  const uint8_T DataTypeConversion_h;  /* '<S14>/Data Type Conversion' */
  const uint8_T DataTypeConversion_mq; /* '<S6>/Data Type Conversion' */
  const uint8_T DataTypeConversion_o5; /* '<S12>/Data Type Conversion' */
} ConstB_EAMM_T;

/* Real-time Model Data Structure */
struct tag_RTM_EAMM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EAMM_T EAMM_B;

/* Block states (auto storage) */
extern DW_EAMM_T EAMM_DW;
extern const ConstB_EAMM_T EAMM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EAMM_initialize(void);

/* Exported entry point functions */
extern void EAMMA_20ms(void);
extern void EAMMB_20ms(void);

/* Real-time Model object */
extern RT_MODEL_EAMM_T *const EAMM_M;

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
 * '<Root>' : 'EAMM'
 * '<S1>'   : 'EAMM/EAMM_All'
 * '<S2>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys'
 * '<S3>'   : 'EAMM/EAMM_All/EAMMB_20ms_Sys'
 * '<S4>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms'
 * '<S5>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/ACDCAWorkMode'
 * '<S6>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunA'
 * '<S7>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunB'
 * '<S8>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AOffline'
 * '<S9>'   : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/APackA'
 * '<S10>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/ECTC_GeECTC_BatDisChg2State_enum'
 * '<S11>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunA/GunAWork'
 * '<S12>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunA/GunAWork/GunAToOffline'
 * '<S13>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunB/GunBWork'
 * '<S14>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AGunB/GunBWork/GunBToOffline'
 * '<S15>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AOffline/OfflineWork'
 * '<S16>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AOffline/OfflineWork/OfflineToGunA'
 * '<S17>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AOffline/OfflineWork/OfflineToGunB'
 * '<S18>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/AOffline/OfflineWork/OfflineToPackA'
 * '<S19>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/APackA/PackAWork'
 * '<S20>'  : 'EAMM/EAMM_All/EAMMA_20ms_Sys/ACDCAModeManage_20ms/APackA/PackAWork/PackAToOffline'
 * '<S21>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms'
 * '<S22>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/ACDCBWorkMode'
 * '<S23>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunA'
 * '<S24>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunB'
 * '<S25>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BOffline'
 * '<S26>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BPackB'
 * '<S27>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/ECTC_GeECTC_BatDisChg2State_enum1'
 * '<S28>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunA/GunAWork'
 * '<S29>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunA/GunAWork/GunAToOffline'
 * '<S30>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunB/GunBWork'
 * '<S31>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BGunB/GunBWork/GunBToOffline'
 * '<S32>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BOffline/OfflineWork'
 * '<S33>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BOffline/OfflineWork/OfflineToGunA'
 * '<S34>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BOffline/OfflineWork/OfflineToGunB'
 * '<S35>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BOffline/OfflineWork/OfflineToPackB'
 * '<S36>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BPackB/PackBWork'
 * '<S37>'  : 'EAMM/EAMM_All/EAMMB_20ms_Sys/ACDCBModeManage_20ms/BPackB/PackBWork/PackBToOffline'
 */

/*-
 * Requirements for '<Root>': EAMM
 */
#endif                                 /* RTW_HEADER_EAMM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
