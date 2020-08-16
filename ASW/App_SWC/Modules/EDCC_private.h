/*
 * File: EDCC_private.h
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

#ifndef RTW_HEADER_EDCC_private_h_
#define RTW_HEADER_EDCC_private_h_
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

extern void EDCC_Delay_Init(DW_Delay_EDCC_T *localDW);
extern void EDCC_Delay(boolean_T rtu_Enable, uint16_T rtu_TimeThrld,
  B_Delay_EDCC_T *localB, DW_Delay_EDCC_T *localDW);
extern void EDCC_Delay_g_Init(DW_Delay_EDCC_o_T *localDW);
extern void EDCC_Delay_h(boolean_T rtu_Enable, uint8_T rtu_TimeThrld,
  B_Delay_EDCC_c_T *localB, DW_Delay_EDCC_o_T *localDW);
extern void EDCC_Delay1_Init(DW_Delay1_EDCC_T *localDW);
extern void EDCC_Delay1(boolean_T rtu_Enable, uint8_T rtu_TimeThrld,
  B_Delay1_EDCC_T *localB, DW_Delay1_EDCC_T *localDW);

#endif                                 /* RTW_HEADER_EDCC_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
