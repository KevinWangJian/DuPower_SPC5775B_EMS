/*
 * File: ETCS.h
 *
 * Code generated for Simulink model 'ETCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:52:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ETCS_h_
#define RTW_HEADER_ETCS_h_
#include <math.h>
#include <stddef.h>
#ifndef ETCS_COMMON_INCLUDES_
# define ETCS_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* ETCS_COMMON_INCLUDES_ */

#include "ETCS_types.h"

/* Includes for objects with custom storage classes. */
#include "ETCS_Cal.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<S19>/hold3tick' */
typedef struct {
  boolean_T out;                       /* '<S19>/hold3tick' */
} B_hold3tick_ETCS_T;

/* Block states (auto storage) for system '<S19>/hold3tick' */
typedef struct {
  uint8_T is_active_c2_ETCS;           /* '<S19>/hold3tick' */
  uint8_T is_c2_ETCS;                  /* '<S19>/hold3tick' */
  uint8_T temporalCounter_i1;          /* '<S19>/hold3tick' */
  boolean_T ipt_prev;                  /* '<S19>/hold3tick' */
  boolean_T ipt_start;                 /* '<S19>/hold3tick' */
} DW_hold3tick_ETCS_T;

/* Block signals for system '<S7>/HoldEnable3tick' */
typedef struct {
  boolean_T out;                       /* '<S7>/HoldEnable3tick' */
} B_HoldEnable3tick_ETCS_T;

/* Block states (auto storage) for system '<S7>/HoldEnable3tick' */
typedef struct {
  uint8_T is_active_c5_ETCS;           /* '<S7>/HoldEnable3tick' */
  uint8_T is_c5_ETCS;                  /* '<S7>/HoldEnable3tick' */
  uint8_T temporalCounter_i1;          /* '<S7>/HoldEnable3tick' */
} DW_HoldEnable3tick_ETCS_T;

/* Block signals (auto storage) */
typedef struct {
  B_HoldEnable3tick_ETCS_T sf_hold3tick_d;/* '<S8>/hold3tick' */
  B_HoldEnable3tick_ETCS_T sf_HoldEnable3tick;/* '<S7>/HoldEnable3tick' */
  B_hold3tick_ETCS_T sf_hold3tick_i;   /* '<S33>/hold3tick' */
  B_hold3tick_ETCS_T sf_hold3tick;     /* '<S19>/hold3tick' */
} B_ETCS_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T Memory_PreviousInput;        /* '<S16>/Memory' */
  DW_HoldEnable3tick_ETCS_T sf_hold3tick_d;/* '<S8>/hold3tick' */
  DW_HoldEnable3tick_ETCS_T sf_HoldEnable3tick;/* '<S7>/HoldEnable3tick' */
  DW_hold3tick_ETCS_T sf_hold3tick_i;  /* '<S33>/hold3tick' */
  DW_hold3tick_ETCS_T sf_hold3tick;    /* '<S19>/hold3tick' */
} DW_ETCS_T;

/* Real-time Model Data Structure */
struct tag_RTM_ETCS_T {
  const char_T * volatile errorStatus;
};

/* Block signals (auto storage) */
extern B_ETCS_T ETCS_B;

/* Block states (auto storage) */
extern DW_ETCS_T ETCS_DW;

/* Model entry point functions */
extern void ETCS_initialize(void);

/* Exported entry point functions */
extern void ETCS_180102F1Send1_500ms(void);
extern void ETCS_180102F1Send2_500ms(void);
extern void ETCS_180502F1Send3_1000ms(void);
extern void ETCS_181602F1Send1_1000ms(void);
extern void ETCS_181602F1Send2_1000ms(void);
extern void ETCS_181902F1Send1_1000ms(void);
extern void ETCS_181902F1Send2_1000ms(void);
extern void ETCS_181A02F1Send_1000ms(void);

/* Real-time Model object */
extern RT_MODEL_ETCS_T *const ETCS_M;

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
 * '<Root>' : 'ETCS'
 * '<S1>'   : 'ETCS/ETCS_10MS'
 * '<S2>'   : 'ETCS/ETCS_10MS/CAN180102F1Send2_500ms_Sys '
 * '<S3>'   : 'ETCS/ETCS_10MS/CAN180102F1Send_500ms_Sys'
 * '<S4>'   : 'ETCS/ETCS_10MS/CAN180502F1Send3_1000ms_Sys'
 * '<S5>'   : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys'
 * '<S6>'   : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys'
 * '<S7>'   : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys'
 * '<S8>'   : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys'
 * '<S9>'   : 'ETCS/ETCS_10MS/CAN181A02F1Send_1000ms'
 * '<S10>'  : 'ETCS/ETCS_10MS/CAN180102F1Send2_500ms_Sys /CAN180102F1Send2_500ms_Sys'
 * '<S11>'  : 'ETCS/ETCS_10MS/CAN180102F1Send2_500ms_Sys /CAN180102F1Send2_500ms_Sys/OW_GeETCS_TFDCCU1OpChrPointStatusEnum_enum1'
 * '<S12>'  : 'ETCS/ETCS_10MS/CAN180102F1Send2_500ms_Sys /CAN180102F1Send2_500ms_Sys/OW_GeETCS_TFDCCU2OpChrPointStatusEnum_enum1'
 * '<S13>'  : 'ETCS/ETCS_10MS/CAN180102F1Send_500ms_Sys/CAN180102F1Send_500ms_Sys'
 * '<S14>'  : 'ETCS/ETCS_10MS/CAN180102F1Send_500ms_Sys/CAN180102F1Send_500ms_Sys/OW_GeETCS_TFDCCU1OcppReasonEnum_enum1'
 * '<S15>'  : 'ETCS/ETCS_10MS/CAN180102F1Send_500ms_Sys/CAN180102F1Send_500ms_Sys/OW_GeETCS_TFDCCU2OcppReasonEnum_enum1'
 * '<S16>'  : 'ETCS/ETCS_10MS/CAN180502F1Send3_1000ms_Sys/CAN180502F1Send3_1000ms_Sys'
 * '<S17>'  : 'ETCS/ETCS_10MS/CAN180502F1Send3_1000ms_Sys/CAN180502F1Send3_1000ms_Sys/OW_GcETCS_TFDDCWhEnerge_Wh'
 * '<S18>'  : 'ETCS/ETCS_10MS/CAN180502F1Send3_1000ms_Sys/CAN180502F1Send3_1000ms_Sys/OW_GeETCS_TFDDCWhindex_enum'
 * '<S19>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys'
 * '<S20>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem'
 * '<S21>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/hold3tick'
 * '<S22>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcEACM_LeftStaRFIDCardUID_numb1'
 * '<S23>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcEACM_LeftStaRFIDCardUID_numb2'
 * '<S24>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcEACM_LeftStaRFIDCardUID_numb3'
 * '<S25>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum1_numb'
 * '<S26>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum2_numb'
 * '<S27>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum3_numb'
 * '<S28>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum4_numb'
 * '<S29>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum5_numb'
 * '<S30>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum6_numb'
 * '<S31>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum7_numb'
 * '<S32>'  : 'ETCS/ETCS_10MS/CAN181602F1Send1_1000ms_Sys/CAN181602F1Send1_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardNum8_numb'
 * '<S33>'  : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys/CAN181602F1Send2_1000ms_Sys'
 * '<S34>'  : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys/CAN181602F1Send2_1000ms_Sys/Subsystem'
 * '<S35>'  : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys/CAN181602F1Send2_1000ms_Sys/hold3tick'
 * '<S36>'  : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys/CAN181602F1Send2_1000ms_Sys/Subsystem/OW_GcETCS_TFDCardbalance_rmb1'
 * '<S37>'  : 'ETCS/ETCS_10MS/CAN181602F1Send2_1000ms_Sys/CAN181602F1Send2_1000ms_Sys/Subsystem/OW_GcETCS_TFDPassword_rmb1'
 * '<S38>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys'
 * '<S39>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/HoldEnable3tick'
 * '<S40>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GbEACM_CCU1TFDAuthReq_flg'
 * '<S41>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GbEACM_CCU2TFDAuthReq_flg'
 * '<S42>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GcEACM_ChrgFee_rmb'
 * '<S43>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GcEACM_PrePayment_rmb'
 * '<S44>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GcEACM_RightStaRFIDCardUID_numb'
 * '<S45>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GcEBSW_LeftDCWhCurrtEnerge_kwH'
 * '<S46>'  : 'ETCS/ETCS_10MS/CAN181902F1Send1_1000ms_Sys/CAN181902F1Send1_1000ms_Sys/OW_GcEBSW_RightDCWhCurrtEnerge_kwH'
 * '<S47>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys'
 * '<S48>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/hold3tick'
 * '<S49>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GcECCR_CCU1BSTSPN3511StopReasonCHGStop_enum'
 * '<S50>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GcECCR_CCU2BSTSPN3511StopReasonCHGStop_enum'
 * '<S51>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GcETCS_TFDEDCmeterSerialNumber5_numb'
 * '<S52>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GcETCS_TFDEDCmeterSerialNumber6_numb'
 * '<S53>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GcETCS_TFDEDCmeterSerialNumber7_numb'
 * '<S54>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GeECCR_CCU1CCUSTATE_enum'
 * '<S55>'  : 'ETCS/ETCS_10MS/CAN181902F1Send2_1000ms_Sys/CAN181902F1Send2_1000ms_Sys/OW_GeECCR_CCU2CCUSTATE_enum'
 * '<S56>'  : 'ETCS/ETCS_10MS/CAN181A02F1Send_1000ms/Subsystem'
 * '<S57>'  : 'ETCS/ETCS_10MS/CAN181A02F1Send_1000ms/Subsystem/OW_GcEACM_LeftStaRFIDCardUID_numb'
 * '<S58>'  : 'ETCS/ETCS_10MS/CAN181A02F1Send_1000ms/Subsystem/OW_GcEBSW_CCU1LEMMeterID_numb'
 * '<S59>'  : 'ETCS/ETCS_10MS/CAN181A02F1Send_1000ms/Subsystem/OW_GcEBSW_CCU2LEMMeterID_numb'
 */

/*-
 * Requirements for '<Root>': ETCS
 */
#endif                                 /* RTW_HEADER_ETCS_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
