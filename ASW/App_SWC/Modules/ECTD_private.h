/*
 * File: ECTD_private.h
 *
 * Code generated for Simulink model 'ECTD'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 10:58:24 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#ifndef RTW_HEADER_ECTD_private_h_
#define RTW_HEADER_ECTD_private_h_
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

extern void ECTD_DebounceStartZero(boolean_T rtu_Signal, uint16_T
  rtu_Hearl2Fault, uint8_T rtu_FaultStep, B_DebounceStartZero_ECTD_T *localB,
  DW_DebounceStartZero_ECTD_T *localDW);
extern void ECTD_DebounceStartZero_p(boolean_T rtu_Signal, uint16_T
  rtu_Hearl2Fault, uint8_T rtu_FaultStep, B_DebounceStartZero_ECTD_c_T *localB,
  DW_DebounceStartZero_ECTD_m_T *localDW);

#endif                                 /* RTW_HEADER_ECTD_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
