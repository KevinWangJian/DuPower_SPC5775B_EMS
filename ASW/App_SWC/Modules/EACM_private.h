/*
 * File: EACM_private.h
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

#ifndef RTW_HEADER_EACM_private_h_
#define RTW_HEADER_EACM_private_h_
#include "rtwtypes.h"

/* Includes for objects with custom storage classes. */
#include "ASW_RTE.h"
#include "Global_Define.h"

/*
 * Generate compile time checks that imported macros for parameters
 * with storage class "ImportedDefine" are defined
 */
#ifndef ASWTYPE_FALSE
#error The variable for the parameter "ASWTYPE_FALSE" is not defined
#endif

#ifndef ASWTYPE_TRUE
#error The variable for the parameter "ASWTYPE_TRUE" is not defined
#endif

extern void EACM_Timer(boolean_T rtu_Timing, B_Timer_EACM_T *localB,
  DW_Timer_EACM_T *localDW);
extern void EACM_Trigger_Rising1_Init(DW_Trigger_Rising1_EACM_T *localDW);
extern void EACM_Trigger_Rising1(boolean_T rtu_In, B_Trigger_Rising1_EACM_T
  *localB, DW_Trigger_Rising1_EACM_T *localDW);
extern void EACM_Start_Stop(boolean_T rtu_Start_Check, boolean_T rtu_StopCheck,
  B_Start_Stop_EACM_T *localB, DW_Start_Stop_EACM_T *localDW);

#endif                                 /* RTW_HEADER_EACM_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
