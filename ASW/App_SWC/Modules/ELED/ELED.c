/*
 * File: ELED.c
 *
 * Code generated for Simulink model 'ELED'.
 *
 * Company                        : DP
 * Author                         : Àîê»
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:59:41 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ELED.h"
#include "ELED_private.h"

/* Real-time model */
RT_MODEL_ELED_T ELED_M_;
RT_MODEL_ELED_T *const ELED_M = &ELED_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ELED_10ms _at_outport_1' */
void ELED_10ms(void)
{
  real32_T tmp;
  if (ELED_ConstB.DataTypeConversion == get_GeECMM_ChrgCtrAMode_enum()) {
    set_GbELED_GunARedLEDStateMode(ELED_ConstB.DataTypeConversion4);
  } else {
    set_GbELED_GunARedLEDStateMode(ELED_ConstB.DataTypeConversion5);
  }

  if (ELED_ConstB.DataTypeConversion1 == get_GeECMM_ChrgCtrAMode_enum()) {
    set_GbELED_GunABlueLEDStateMode(ELED_ConstB.DataTypeConversion6);
  } else if (ELED_ConstB.DataTypeConversion14 == get_GeECMM_ChrgCtrAMode_enum())
  {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion15);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunABlueLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  } else {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion7);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunABlueLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  }

  if ((ELED_ConstB.DataTypeConversion3 == get_GeECMM_ChrgCtrAMode_enum()) ||
      (ELED_ConstB.DataTypeConversion12 == get_GeECMM_ChrgCtrAMode_enum()) ||
      (ELED_ConstB.DataTypeConversion13 == get_GeECMM_ChrgCtrAMode_enum())) {
    set_GbELED_GunAGreenLEDStateMode(ELED_ConstB.DataTypeConversion9);
  } else if (ELED_ConstB.DataTypeConversion2 == get_GeECMM_ChrgCtrAMode_enum())
  {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion8);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunAGreenLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  } else {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion10);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunAGreenLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  }

  if (ELED_ConstB.DataTypeConversion_d == get_GeECMM_ChrgCtrBMode_enum()) {
    set_GbELED_GunBRedLEDStateMode(ELED_ConstB.DataTypeConversion4_c);
  } else {
    set_GbELED_GunBRedLEDStateMode(ELED_ConstB.DataTypeConversion5_d);
  }

  if (ELED_ConstB.DataTypeConversion1_g == get_GeECMM_ChrgCtrBMode_enum()) {
    set_GbELED_GunBBlueLEDStateMode(ELED_ConstB.DataTypeConversion6_n);
  } else if (ELED_ConstB.DataTypeConversion14_i == get_GeECMM_ChrgCtrBMode_enum())
  {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion15_f);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunBBlueLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  } else {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion7_l);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunBBlueLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  }

  if ((ELED_ConstB.DataTypeConversion3_i == get_GeECMM_ChrgCtrBMode_enum()) ||
      (ELED_ConstB.DataTypeConversion12_k == get_GeECMM_ChrgCtrBMode_enum()) ||
      (ELED_ConstB.DataTypeConversion13_h == get_GeECMM_ChrgCtrBMode_enum())) {
    set_GbELED_GunBGreenLEDStateMode(ELED_ConstB.DataTypeConversion9_g);
  } else if (ELED_ConstB.DataTypeConversion2_g == get_GeECMM_ChrgCtrBMode_enum())
  {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion8_b);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunBGreenLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  } else {
    tmp = (real32_T)floor(ELED_ConstB.DataTypeConversion10_p);
    if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
      tmp = 0.0F;
    } else {
      tmp = (real32_T)fmod(tmp, 256.0F);
    }

    set_GbELED_GunBGreenLEDStateMode((uint8_T)(tmp < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-tmp : (int32_T)(uint8_T)tmp));
  }
}

/* Model initialize function */
void ELED_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
