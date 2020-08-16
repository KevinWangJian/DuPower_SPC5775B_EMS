/*
 * File: EACM.h
 *
 * Code generated for Simulink model 'EACM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 18:44:55 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EACM_h_
#define RTW_HEADER_EACM_h_
#include <stddef.h>
#ifndef EACM_COMMON_INCLUDES_
# define EACM_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* EACM_COMMON_INCLUDES_ */

#include "EACM_types.h"

/* Includes for objects with custom storage classes. */
#include "EACM_Cal.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S21>/Timer' */
typedef struct {
  real_T Output;                       /* '<S21>/Timer' */
} B_Timer_EACM_T;

/* Block states (auto storage) for system '<S21>/Timer' */
typedef struct {
  uint8_T is_active_c4_EACM;           /* '<S21>/Timer' */
  uint8_T is_c4_EACM;                  /* '<S21>/Timer' */
  uint8_T is_Output;                   /* '<S21>/Timer' */
  uint8_T temporalCounter_i1;          /* '<S21>/Timer' */
} DW_Timer_EACM_T;

/* Block signals for system '<S21>/Trigger_Rising1' */
typedef struct {
  boolean_T LogicalOperator;           /* '<S27>/Logical Operator' */
} B_Trigger_Rising1_EACM_T;

/* Block states (auto storage) for system '<S21>/Trigger_Rising1' */
typedef struct {
  uint8_T StateName;                   /* '<S29>/Unit Delay1' */
  boolean_T StateName_g;               /* '<S29>/Unit Delay' */
} DW_Trigger_Rising1_EACM_T;

/* Block signals for system '<S15>/Start_Stop' */
typedef struct {
  boolean_T StartFlg;                  /* '<S15>/Start_Stop' */
} B_Start_Stop_EACM_T;

/* Block states (auto storage) for system '<S15>/Start_Stop' */
typedef struct {
  uint8_T is_active_c10_EACM;          /* '<S15>/Start_Stop' */
  uint8_T is_c10_EACM;                 /* '<S15>/Start_Stop' */
  uint8_T is_Enable;                   /* '<S15>/Start_Stop' */
  boolean_T StopCheck_prev;            /* '<S15>/Start_Stop' */
  boolean_T StopCheck_start;           /* '<S15>/Start_Stop' */
  boolean_T Start_Check_prev;          /* '<S15>/Start_Stop' */
  boolean_T Start_Check_start;         /* '<S15>/Start_Stop' */
} DW_Start_Stop_EACM_T;

/* Block signals (auto storage) */
typedef struct {
  uint8_T Check;                       /* '<S62>/Check' */
  uint8_T Check_f;                     /* '<S24>/Check' */
  boolean_T GbEACM_RightCheckSuccess_flg;/* '<S60>/Chart' */
  boolean_T StartCalTmFlg;             /* '<S71>/Timer_Count_30Sec' */
  boolean_T TmOutFlg;                  /* '<S71>/Timer_Count_30Sec' */
  boolean_T Check_b;                   /* '<S63>/Check' */
  boolean_T GbEACM_LeftCheckSuccess_flg;/* '<S20>/Chart' */
  boolean_T StartCalTmFlg_e;           /* '<S31>/Timer_Count_30Sec' */
  boolean_T TmOutFlg_d;                /* '<S31>/Timer_Count_30Sec' */
  boolean_T Check_l;                   /* '<S23>/Check' */
  B_Trigger_Rising1_EACM_T Trigger_Rising1_g;/* '<S79>/Trigger_Rising1' */
  B_Timer_EACM_T sf_Timer_j;           /* '<S79>/Timer' */
  B_Start_Stop_EACM_T sf_Start_Stop_p; /* '<S55>/Start_Stop' */
  B_Trigger_Rising1_EACM_T Trigger_Rising2_i;/* '<S61>/Trigger_Rising2' */
  B_Trigger_Rising1_EACM_T Trigger_Rising1_a;/* '<S61>/Trigger_Rising1' */
  B_Timer_EACM_T sf_Timer_o0;          /* '<S61>/Timer' */
  B_Trigger_Rising1_EACM_T Trigger_Rising1_d;/* '<S39>/Trigger_Rising1' */
  B_Timer_EACM_T sf_Timer_o;           /* '<S39>/Timer' */
  B_Start_Stop_EACM_T sf_Start_Stop;   /* '<S15>/Start_Stop' */
  B_Trigger_Rising1_EACM_T Trigger_Rising2;/* '<S21>/Trigger_Rising2' */
  B_Trigger_Rising1_EACM_T Trigger_Rising1;/* '<S21>/Trigger_Rising1' */
  B_Timer_EACM_T sf_Timer;             /* '<S21>/Timer' */
} B_EACM_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S71>/Timer_Count_30Sec' */
  uint16_T temporalCounter_i1_a;       /* '<S31>/Timer_Count_30Sec' */
  boolean_T StateName;                 /* '<S38>/Unit Delay' */
  boolean_T StateName_d;               /* '<S39>/Unit Delay' */
  boolean_T StateName_e;               /* '<S61>/Unit Delay' */
  boolean_T StateName_o;               /* '<S78>/Unit Delay' */
  boolean_T StateName_dz;              /* '<S79>/Unit Delay' */
  uint8_T is_active_c1_EACM;           /* '<S60>/Chart' */
  uint8_T is_c1_EACM;                  /* '<S60>/Chart' */
  uint8_T is_active_c12_EACM;          /* '<S71>/Timer_Count_30Sec' */
  uint8_T is_c12_EACM;                 /* '<S71>/Timer_Count_30Sec' */
  uint8_T is_ENABLE_p;                 /* '<S71>/Timer_Count_30Sec' */
  uint8_T is_active_c3_EACM;           /* '<S20>/Chart' */
  uint8_T is_c3_EACM;                  /* '<S20>/Chart' */
  uint8_T is_active_c9_EACM;           /* '<S31>/Timer_Count_30Sec' */
  uint8_T is_c9_EACM;                  /* '<S31>/Timer_Count_30Sec' */
  uint8_T is_ENABLE_b;                 /* '<S31>/Timer_Count_30Sec' */
  boolean_T Memory_PreviousInput;      /* '<S21>/Memory' */
  boolean_T GbEBSW_CarPass_flg_start;  /* '<S71>/Timer_Count_30Sec' */
  boolean_T GbEBSW_CarPass_flg_start_f;/* '<S31>/Timer_Count_30Sec' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising1_g;/* '<S79>/Trigger_Rising1' */
  DW_Timer_EACM_T sf_Timer_j;          /* '<S79>/Timer' */
  DW_Start_Stop_EACM_T sf_Start_Stop_p;/* '<S55>/Start_Stop' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising2_i;/* '<S61>/Trigger_Rising2' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising1_a;/* '<S61>/Trigger_Rising1' */
  DW_Timer_EACM_T sf_Timer_o0;         /* '<S61>/Timer' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising1_d;/* '<S39>/Trigger_Rising1' */
  DW_Timer_EACM_T sf_Timer_o;          /* '<S39>/Timer' */
  DW_Start_Stop_EACM_T sf_Start_Stop;  /* '<S15>/Start_Stop' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising2;/* '<S21>/Trigger_Rising2' */
  DW_Trigger_Rising1_EACM_T Trigger_Rising1;/* '<S21>/Trigger_Rising1' */
  DW_Timer_EACM_T sf_Timer;            /* '<S21>/Timer' */
} DW_EACM_T;

/* Invariant block signals (auto storage) */
typedef struct {
  const uint8_T DataTypeConversion1;   /* '<S21>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2;   /* '<S31>/Data Type Conversion2' */
  const uint8_T DataTypeConversion1_f; /* '<S31>/Data Type Conversion1' */
  const uint8_T DataTypeConversion;    /* '<S31>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_e; /* '<S38>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_n;  /* '<S16>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_n; /* '<S39>/Data Type Conversion1' */
  const uint8_T DataTypeConversion1_fu;/* '<S61>/Data Type Conversion1' */
  const uint8_T DataTypeConversion2_h; /* '<S71>/Data Type Conversion2' */
  const uint8_T DataTypeConversion1_p; /* '<S71>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_p;  /* '<S71>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_h; /* '<S78>/Data Type Conversion1' */
  const uint8_T DataTypeConversion_k;  /* '<S56>/Data Type Conversion' */
  const uint8_T DataTypeConversion1_d; /* '<S79>/Data Type Conversion1' */
} ConstB_EACM_T;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  boolean_T GbEBSW_EMGStopAuxIn_flg;   /* '<Root>/GbEBSW_EMGStopAuxIn_flg' */
} ExtU_EACM_T;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  uint8_T GcEACM_LeftStaRFIDCardUID_numb[8];/* '<Root>/GcEACM_LeftStaRFIDCardUID_numb' */
  uint8_T GcEACM_RightStaRFIDCardUID_numb[8];/* '<Root>/GcEACM_RightStaRFIDCardUID_numb' */
} ExtY_EACM_T;

/* Real-time Model Data Structure */
struct tag_RTM_EACM_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_EACM_T EACM_B;

/* Block states (auto storage) */
extern DW_EACM_T EACM_DW;

/* External inputs (root inport signals with auto storage) */
extern ExtU_EACM_T EACM_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExtY_EACM_T EACM_Y;
extern const ConstB_EACM_T EACM_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void EACM_initialize(void);

/* Exported entry point functions */
extern void EACM_20ms(void);

/* Real-time Model object */
extern RT_MODEL_EACM_T *const EACM_M;

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
 * '<Root>' : 'EACM'
 * '<S1>'   : 'EACM/EACM '
 * '<S2>'   : 'EACM/EACM /EACB_20ms_Sys'
 * '<S3>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys'
 * '<S4>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys'
 * '<S5>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite'
 * '<S6>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite1'
 * '<S7>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite2'
 * '<S8>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite3'
 * '<S9>'   : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite4'
 * '<S10>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite5'
 * '<S11>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite6'
 * '<S12>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite7'
 * '<S13>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/OverWrite8'
 * '<S14>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge'
 * '<S15>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Check'
 * '<S16>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Check1'
 * '<S17>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge'
 * '<S18>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck'
 * '<S19>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/InterAction_TBox '
 * '<S20>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Start_ChargeReq'
 * '<S21>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check '
 * '<S22>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Credit_Card'
 * '<S23>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /HoldL_CardType'
 * '<S24>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /HoldL_CardType1'
 * '<S25>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /NoCredit_Card'
 * '<S26>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Timer'
 * '<S27>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Trigger_Rising1'
 * '<S28>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Trigger_Rising2'
 * '<S29>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Trigger_Rising1/Unit Delay External IC'
 * '<S30>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check /Trigger_Rising2/Unit Delay External IC'
 * '<S31>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/InterAction_TBox /Card_ResponseTBox'
 * '<S32>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/InterAction_TBox /Card_ResponseTBox/Timer_Count_30Sec'
 * '<S33>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Start_ChargeReq/CCU1ReqPowerFalseCheck'
 * '<S34>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Start_ChargeReq/CCU1ReqPowerTrueCheck'
 * '<S35>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Charge/Start_ChargeReq/Chart'
 * '<S36>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Start_Check/Start_Stop'
 * '<S37>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck'
 * '<S38>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Req_PowerStop '
 * '<S39>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card '
 * '<S40>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card /Credit_Card'
 * '<S41>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card /NOCredit_Card'
 * '<S42>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card /Timer'
 * '<S43>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card /Trigger_Rising1'
 * '<S44>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU1_20ms_Sys/Stop_Charge/Card_StopCheck/Credit_Card /Trigger_Rising1/Unit Delay External IC'
 * '<S45>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OW_GbEBSW_RightCCUStartCheck_flg'
 * '<S46>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OW_GbETCR_LeftServeStaChgCmd_flg'
 * '<S47>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite1'
 * '<S48>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite2'
 * '<S49>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite4'
 * '<S50>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite5'
 * '<S51>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite6'
 * '<S52>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite7'
 * '<S53>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/OverWrite8'
 * '<S54>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge'
 * '<S55>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Check'
 * '<S56>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Check1'
 * '<S57>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge'
 * '<S58>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck'
 * '<S59>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/InterAction_TBox '
 * '<S60>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Start_ChargeReq'
 * '<S61>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check'
 * '<S62>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/HoldR_CardType'
 * '<S63>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/HoldR_CardType_flag'
 * '<S64>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/No_Card_PaymentFee'
 * '<S65>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Payment_Fee '
 * '<S66>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Timer'
 * '<S67>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Trigger_Rising1'
 * '<S68>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Trigger_Rising2'
 * '<S69>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Trigger_Rising1/Unit Delay External IC'
 * '<S70>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Card_StartCheck/Card_Check/Trigger_Rising2/Unit Delay External IC'
 * '<S71>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/InterAction_TBox /Card_ResponseTBox'
 * '<S72>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/InterAction_TBox /Card_ResponseTBox/Timer_Count_30Sec'
 * '<S73>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Start_ChargeReq/CCU1ReqPowerFalseCheck'
 * '<S74>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Start_ChargeReq/CCU1ReqPowerTrueCheck'
 * '<S75>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Charge/Start_ChargeReq/Chart'
 * '<S76>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Start_Check/Start_Stop'
 * '<S77>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck'
 * '<S78>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Req_PowerStop '
 * '<S79>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck '
 * '<S80>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck /Credit_Card'
 * '<S81>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck /NOCredit_Card'
 * '<S82>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck /Timer'
 * '<S83>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck /Trigger_Rising1'
 * '<S84>'  : 'EACM/EACM /EACB_20ms_Sys/EACM_CCU2_20ms_Sys/Stop_Charge/Card_StopCheck/Card_StopCheck /Trigger_Rising1/Unit Delay External IC'
 */

/*-
 * Requirements for '<Root>': EACM
 */
#endif                                 /* RTW_HEADER_EACM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
