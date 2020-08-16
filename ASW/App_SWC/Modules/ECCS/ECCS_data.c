/*
 * File: ECCS_data.c
 *
 * Code generated for Simulink model 'ECCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Sat May 09 15:30:08 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECCS.h"
#include "ECCS_private.h"

/* Invariant block signals (auto storage) */
const ConstB_ECCS_T ECCS_ConstB = {
  1000.0F
  ,                                    /* '<S58>/Data Type Conversion7' */
  1.0F
  ,                                    /* '<S209>/Data Type Conversion1' */
  0.0F
  ,                                    /* '<S209>/Data Type Conversion' */
  2.0F
  ,                                    /* '<S209>/Data Type Conversion2' */
  4294967295U
  ,                                    /* '<S245>/Data Type Conversion2' */
  1677215U
  ,                                    /* '<S245>/Data Type Conversion3' */
  4000U
  ,                                    /* '<S77>/Data Type Conversion22' */
  6000U
  ,                                    /* '<S77>/Data Type Conversion5' */
  0U
  ,                                    /* '<S234>/Data Type Conversion' */
  0U
  ,                                    /* '<S234>/Data Type Conversion1' */
  0U
  ,                                    /* '<S225>/Data Type Conversion' */
  0U
  ,                                    /* '<S225>/Data Type Conversion1' */
  0U
  ,                                    /* '<S225>/Data Type Conversion2' */
  0U
  ,                                    /* '<S225>/Data Type Conversion3' */
  0U
  ,                                    /* '<S225>/Data Type Conversion4' */
  0U
  ,                                    /* '<S225>/Data Type Conversion5' */
  0U
  ,                                    /* '<S77>/Data Type Conversion4' */
  9200U
  ,                                    /* '<S77>/Data Type Conversion1' */
  0U
  ,                                    /* '<S304>/Data Type Conversion' */
  0U
  ,                                    /* '<S304>/Data Type Conversion1' */
  0U
  ,                                    /* '<S304>/Data Type Conversion2' */
  0U
  ,                                    /* '<S304>/Data Type Conversion3' */
  0U
  ,                                    /* '<S304>/Data Type Conversion4' */
  0U
  ,                                    /* '<S304>/Data Type Conversion5' */
  0U
  ,                                    /* '<S304>/Data Type Conversion6' */
  0U
  ,                                    /* '<S304>/Data Type Conversion7' */
  0U
  ,                                    /* '<S304>/Data Type Conversion8' */
  0U
  ,                                    /* '<S304>/Data Type Conversion9' */
  0U
  ,                                    /* '<S304>/Data Type Conversion10' */
  0U
  ,                                    /* '<S304>/Data Type Conversion11' */
  0U
  ,                                    /* '<S304>/Data Type Conversion12' */
  0U
  ,                                    /* '<S304>/Data Type Conversion13' */
  0U
  ,                                    /* '<S304>/Data Type Conversion14' */
  0U
  ,                                    /* '<S304>/Data Type Conversion15' */
  0U
  ,                                    /* '<S304>/Data Type Conversion16' */
  0U
  ,                                    /* '<S289>/Data Type Conversion' */
  0U
  ,                                    /* '<S289>/Data Type Conversion1' */
  0U
  ,                                    /* '<S289>/Data Type Conversion2' */
  0U
  ,                                    /* '<S289>/Data Type Conversion3' */
  0U
  ,                                    /* '<S289>/Data Type Conversion4' */
  0U
  ,                                    /* '<S289>/Data Type Conversion5' */
  0U
  ,                                    /* '<S289>/Data Type Conversion6' */
  2U
  ,                                    /* '<S245>/Data Type Conversion1' */
  10U
  ,                                    /* '<S234>/Data Type Conversion3' */
  10U
  ,                                    /* '<S234>/Data Type Conversion4' */
  1U
  ,                                    /* '<S195>/Data Type Conversion7' */
  1U
  ,                                    /* '<S195>/Data Type Conversion8' */
  0U
  ,                                    /* '<S107>/Data Type Conversion' */
  0U
  ,                                    /* '<S107>/Data Type Conversion1' */
  0U
  ,                                    /* '<S107>/Data Type Conversion2' */
  0U
  ,                                    /* '<S107>/Data Type Conversion3' */
  0U
  ,                                    /* '<S107>/Data Type Conversion4' */
  0U
  ,                                    /* '<S107>/Data Type Conversion5' */
  0U
  ,                                    /* '<S107>/Data Type Conversion6' */
  0U
  ,                                    /* '<S107>/Data Type Conversion7' */
  1U
  ,                                    /* '<S4>/Data Type Conversion1' */
  0U
  ,                                    /* '<S124>/Data Type Conversion1' */
  0U
  ,                                    /* '<S124>/Data Type Conversion2' */
  0U
  ,                                    /* '<S124>/Data Type Conversion3' */
  0U
  ,                                    /* '<S124>/Data Type Conversion27' */
  0U
  ,                                    /* '<S124>/Data Type Conversion4' */
  0U
  ,                                    /* '<S124>/Data Type Conversion5' */
  0U
  ,                                    /* '<S124>/Data Type Conversion6' */
  0U
  ,                                    /* '<S124>/Data Type Conversion7' */
  0U
  ,                                    /* '<S124>/Data Type Conversion8' */
  0U
  ,                                    /* '<S124>/Data Type Conversion9' */
  0U
  ,                                    /* '<S124>/Data Type Conversion10' */
  0U
  ,                                    /* '<S124>/Data Type Conversion11' */
  0U
  ,                                    /* '<S124>/Data Type Conversion12' */
  0U
  ,                                    /* '<S124>/Data Type Conversion13' */
  0U
  ,                                    /* '<S124>/Data Type Conversion14' */
  0U
  ,                                    /* '<S124>/Data Type Conversion15' */
  0U
  ,                                    /* '<S124>/Data Type Conversion16' */
  0U
  ,                                    /* '<S124>/Data Type Conversion17' */
  0U
  ,                                    /* '<S23>/Data Type Conversion' */
  0U
  ,                                    /* '<S23>/Data Type Conversion1' */
  0U
  ,                                    /* '<S23>/Data Type Conversion10' */
  0U
  ,                                    /* '<S23>/Data Type Conversion5' */
  0U
  ,                                    /* '<S24>/Data Type Conversion6' */
  0U
  ,                                    /* '<S24>/Data Type Conversion11' */
  0U
  ,                                    /* '<S24>/Data Type Conversion12' */
  0U
  ,                                    /* '<S24>/Data Type Conversion13' */
  0U
  ,                                    /* '<S24>/Data Type Conversion7' */
  0U
  ,                                    /* '<S24>/Data Type Conversion14' */
  0U
  ,                                    /* '<S25>/Data Type Conversion15' */
  0U
  ,                                    /* '<S25>/Data Type Conversion9' */
  40U
  /* '<S25>/Data Type Conversion8' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
