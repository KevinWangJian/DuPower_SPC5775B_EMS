/*
 * File: ECTC_data.c
 *
 * Code generated for Simulink model 'ECTC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 17:33:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECTC.h"
#include "ECTC_private.h"

/* Invariant block signals (auto storage) */
const ConstB_ECTC_T ECTC_ConstB = {
  2U
  ,                                    /* '<S493>/Data Type Conversion' */
  3U
  ,                                    /* '<S494>/Data Type Conversion' */
  4U
  ,                                    /* '<S496>/Data Type Conversion' */
  1U
  ,                                    /* '<S495>/Data Type Conversion' */
  3U
  ,                                    /* '<S528>/Data Type Conversion1' */
  3U
  ,                                    /* '<S501>/Data Type Conversion1' */
  1U
  ,                                    /* '<S492>/Data Type Conversion' */
  4U
  ,                                    /* '<S492>/Data Type Conversion1' */
  0U
  ,                                    /* '<S491>/Data Type Conversion' */
  3U
  ,                                    /* '<S498>/Data Type Conversion' */
  0U
  ,                                    /* '<S498>/Data Type Conversion1' */
  0U
  ,                                    /* '<S498>/Data Type Conversion2' */
  0U
  ,                                    /* '<S498>/Data Type Conversion3' */
  2U
  ,                                    /* '<S424>/Data Type Conversion' */
  3U
  ,                                    /* '<S425>/Data Type Conversion' */
  4U
  ,                                    /* '<S427>/Data Type Conversion' */
  1U
  ,                                    /* '<S426>/Data Type Conversion' */
  3U
  ,                                    /* '<S459>/Data Type Conversion1' */
  3U
  ,                                    /* '<S432>/Data Type Conversion1' */
  1U
  ,                                    /* '<S423>/Data Type Conversion' */
  4U
  ,                                    /* '<S423>/Data Type Conversion1' */
  0U
  ,                                    /* '<S422>/Data Type Conversion' */
  3U
  ,                                    /* '<S429>/Data Type Conversion' */
  0U
  ,                                    /* '<S429>/Data Type Conversion1' */
  0U
  ,                                    /* '<S429>/Data Type Conversion2' */
  0U
  ,                                    /* '<S429>/Data Type Conversion3' */
  2U
  ,                                    /* '<S318>/Data Type Conversion' */
  3U
  ,                                    /* '<S319>/Data Type Conversion' */
  4U
  ,                                    /* '<S321>/Data Type Conversion' */
  1U
  ,                                    /* '<S320>/Data Type Conversion' */
  4U
  ,                                    /* '<S356>/Data Type Conversion1' */
  4U
  ,                                    /* '<S327>/Data Type Conversion1' */
  1U
  ,                                    /* '<S317>/Data Type Conversion' */
  4U
  ,                                    /* '<S317>/Data Type Conversion1' */
  0U
  ,                                    /* '<S316>/Data Type Conversion' */
  4U
  ,                                    /* '<S324>/Data Type Conversion' */
  0U
  ,                                    /* '<S324>/Data Type Conversion1' */
  0U
  ,                                    /* '<S324>/Data Type Conversion2' */
  0U
  ,                                    /* '<S324>/Data Type Conversion3' */
  2U
  ,                                    /* '<S249>/Data Type Conversion' */
  3U
  ,                                    /* '<S250>/Data Type Conversion' */
  4U
  ,                                    /* '<S252>/Data Type Conversion' */
  1U
  ,                                    /* '<S251>/Data Type Conversion' */
  4U
  ,                                    /* '<S287>/Data Type Conversion1' */
  4U
  ,                                    /* '<S258>/Data Type Conversion1' */
  1U
  ,                                    /* '<S248>/Data Type Conversion' */
  4U
  ,                                    /* '<S248>/Data Type Conversion1' */
  0U
  ,                                    /* '<S247>/Data Type Conversion' */
  4U
  ,                                    /* '<S255>/Data Type Conversion' */
  0U
  ,                                    /* '<S255>/Data Type Conversion1' */
  0U
  ,                                    /* '<S255>/Data Type Conversion2' */
  0U
  ,                                    /* '<S255>/Data Type Conversion3' */
  4U
  ,                                    /* '<S135>/Data Type Conversion' */
  2U
  ,                                    /* '<S132>/Data Type Conversion' */
  3U
  ,                                    /* '<S133>/Data Type Conversion' */
  1U
  ,                                    /* '<S134>/Data Type Conversion' */
  4U
  ,                                    /* '<S134>/Data Type Conversion1' */
  5U
  ,                                    /* '<S192>/Data Type Conversion1' */
  0U
  ,                                    /* '<S131>/Data Type Conversion' */
  5U
  ,                                    /* '<S189>/Data Type Conversion' */
  0U
  ,                                    /* '<S189>/Data Type Conversion1' */
  0U
  ,                                    /* '<S189>/Data Type Conversion2' */
  0U
  ,                                    /* '<S189>/Data Type Conversion3' */
  0U
  ,                                    /* '<S189>/Data Type Conversion4' */
  0U
  ,                                    /* '<S189>/Data Type Conversion5' */
  1U
  ,                                    /* '<S129>/Data Type Conversion' */
  5U
  ,                                    /* '<S142>/Data Type Conversion1' */
  1U
  ,                                    /* '<S128>/Data Type Conversion' */
  4U
  ,                                    /* '<S128>/Data Type Conversion1' */
  4U
  ,                                    /* '<S17>/Data Type Conversion' */
  2U
  ,                                    /* '<S13>/Data Type Conversion' */
  3U
  ,                                    /* '<S14>/Data Type Conversion' */
  1U
  ,                                    /* '<S16>/Data Type Conversion' */
  4U
  ,                                    /* '<S16>/Data Type Conversion1' */
  1U
  ,                                    /* '<S15>/Data Type Conversion' */
  5U
  ,                                    /* '<S65>/Data Type Conversion1' */
  5U
  ,                                    /* '<S23>/Data Type Conversion1' */
  0U
  ,                                    /* '<S12>/Data Type Conversion' */
  5U
  ,                                    /* '<S20>/Data Type Conversion' */
  0U
  ,                                    /* '<S20>/Data Type Conversion1' */
  0U
  ,                                    /* '<S20>/Data Type Conversion2' */
  0U
  ,                                    /* '<S20>/Data Type Conversion3' */
  0U
  ,                                    /* '<S20>/Data Type Conversion4' */
  0U
  ,                                    /* '<S20>/Data Type Conversion5' */
  1U
  ,                                    /* '<S10>/Data Type Conversion' */
  4U
  /* '<S10>/Data Type Conversion1' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
