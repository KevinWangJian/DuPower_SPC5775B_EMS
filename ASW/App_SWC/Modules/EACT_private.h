/*
 * File: EACT_private.h
 *
 * Code generated for Simulink model 'EACT'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 15 14:12:21 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_EACT_private_h_
#define RTW_HEADER_EACT_private_h_
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

extern void EACT_DebounceStartZero(boolean_T rtu_Signal, uint16_T
  rtu_Hearl2Fault, uint8_T rtu_FaultStep, B_DebounceStartZero_EACT_T *localB,
  DW_DebounceStartZero_EACT_T *localDW);

#endif                                 /* RTW_HEADER_EACT_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
