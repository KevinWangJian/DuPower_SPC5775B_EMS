/*
 * File: EHCS.c
 *
 * Code generated for Simulink model 'EHCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 16:01:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EHCS.h"
#include "EHCS_private.h"

/* Block signals (auto storage) */
B_EHCS_T EHCS_B;

/* Real-time model */
RT_MODEL_EHCS_T EHCS_M_;
RT_MODEL_EHCS_T *const EHCS_M = &EHCS_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EHCS_10ms_at_outport_1' */
void EHCS_10ms(void)
{
  real32_T u0;
  if (CbEHCS_BMSMaxBatTmpOvrSwt_flg) {
    set_GcEHCS_BMSMaxBatTmp_C(CcEHCS_BMSMaxBatTmpOvr_C);
  } else {
    if ((get_GcEBCR_BMSAMaxBatTmp_C() >= get_GcEBCR_BMSBMaxBatTmp_C()) ||
        rtIsNaNF(get_GcEBCR_BMSBMaxBatTmp_C())) {
      u0 = get_GcEBCR_BMSAMaxBatTmp_C();
    } else {
      u0 = get_GcEBCR_BMSBMaxBatTmp_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_BMSMaxBatTmp_C((uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)-(int8_T)
      (uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (CbEHCS_BMSMaxBatWaterTmpOutOvrSwt_flg) {
    set_GcEHCS_BMSMaxBatWaterTmpOut_C(CcEHCS_BMSMaxBatWaterTmpOutOvr_C);
  } else {
    if ((get_GcEBCR_BMSAMaxBatWaterTmpOut_C() >=
         get_GcEBCR_BMSBMaxBatWaterTmpOut_C()) || rtIsNaNF
        (get_GcEBCR_BMSBMaxBatWaterTmpOut_C())) {
      u0 = get_GcEBCR_BMSAMaxBatWaterTmpOut_C();
    } else {
      u0 = get_GcEBCR_BMSBMaxBatWaterTmpOut_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_BMSMaxBatWaterTmpOut_C((uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (CbEHCS_BMSMinBatTmpOvrSwt_flg) {
    set_GcEHCS_BMSMinBatTmp_C(CcEHCS_BMSMinBatTmpOvr_C);
  } else {
    if ((get_GcEBCR_BMSAMinBatTmp_C() <= get_GcEBCR_BMSBMinBatTmp_C()) ||
        rtIsNaNF(get_GcEBCR_BMSBMinBatTmp_C())) {
      u0 = get_GcEBCR_BMSAMinBatTmp_C();
    } else {
      u0 = get_GcEBCR_BMSBMinBatTmp_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_BMSMinBatTmp_C((uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)-(int8_T)
      (uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (CbEHCS_BMSMinBatWaterTmpInOvrSwt_flg) {
    set_GcEHCS_BMSMinBatWaterTmpIn_C(CcEHCS_BMSMinBatWaterTmpInOvr_C);
  } else {
    if ((get_GcEBCR_BMSAMinBatWaterTmpIn_C() <=
         get_GcEBCR_BMSBMinBatWaterTmpIn_C()) || rtIsNaNF
        (get_GcEBCR_BMSBMinBatWaterTmpIn_C())) {
      u0 = get_GcEBCR_BMSAMinBatWaterTmpIn_C();
    } else {
      u0 = get_GcEBCR_BMSBMinBatWaterTmpIn_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_BMSMinBatWaterTmpIn_C((uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)
      -(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (((int32_T)Enum_EETMHeatMode_Standby == get_GeEETM_HeatMode_enum()) ||
      ((int32_T)Enum_EETMHeatMode_OffLine == get_GeEETM_HeatMode_enum()) ||
      ((int32_T)Enum_EETMHeatMode_NotReady == get_GeEETM_HeatMode_enum())) {
    EHCS_B.oGcEHCS_EMSHeatModeSelect_enum = Enum_EHCSEMSHeatModeSelect_Standby;
  } else if ((int32_T)Enum_EETMHeatMode_SelfCirculation ==
             get_GeEETM_HeatMode_enum()) {
    EHCS_B.oGcEHCS_EMSHeatModeSelect_enum = Enum_EHCSEMSHeatModeSelect_SelfLoop;
  } else if ((int32_T)Enum_EETMHeatMode_Cold == get_GeEETM_HeatMode_enum()) {
    EHCS_B.oGcEHCS_EMSHeatModeSelect_enum = Enum_EHCSEMSHeatModeSelect_PackCold;
  } else {
    if ((int32_T)Enum_EETMHeatMode_Heat == get_GeEETM_HeatMode_enum()) {
      EHCS_B.oGcEHCS_EMSHeatModeSelect_enum =
        Enum_EHCSEMSHeatModeSelect_PackHeat;
    }
  }

  if (CbEHCS_EMSHeatModeSelectOvrSwt_flg) {
    set_GcEHCS_EMSHeatModeSelect_enum(CeEHCS_EMSHeatModeSelectOvr_enum);
  } else {
    set_GcEHCS_EMSHeatModeSelect_enum((uint8_T)
      EHCS_B.oGcEHCS_EMSHeatModeSelect_enum);
  }

  if (CbEHCS_EMSHeatSetTmpOvrSwt_flg) {
    set_GcEHCS_EMSHeatSetTmp_C(CcEHCS_EMSHeatSetTmpOvr_C);
  } else {
    u0 = (real32_T)floor(get_GcEETM_SetTemp_C() + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_EMSHeatSetTmp_C((uint8_T)(u0 < 0.0F ? (int32_T)(uint8_T)-(int8_T)
      (uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (CbEHCS_EMSMaxPowerModelWaterTmpOutOvrSwt_flg) {
    set_GcEHCS_EMSMaxPowerModelWaterTmpOut_C
      (CcEHCS_EMSMaxPowerModelWaterTmpOutOvr_C);
  } else {
    if ((get_GcEBSW_ACDCAOutWaterTemp_C() >= get_GcEBSW_DCDCAOutWaterTemp_C()) ||
        rtIsNaNF(get_GcEBSW_DCDCAOutWaterTemp_C())) {
      u0 = get_GcEBSW_ACDCAOutWaterTemp_C();
    } else {
      u0 = get_GcEBSW_DCDCAOutWaterTemp_C();
    }

    if (!((u0 >= get_GcEBSW_ACDCBOutWaterTemp_C()) || rtIsNaNF
          (get_GcEBSW_ACDCBOutWaterTemp_C()))) {
      u0 = get_GcEBSW_ACDCBOutWaterTemp_C();
    }

    if (!((u0 >= get_GcEBSW_DCDCBOutWaterTemp_C()) || rtIsNaNF
          (get_GcEBSW_DCDCBOutWaterTemp_C()))) {
      u0 = get_GcEBSW_DCDCBOutWaterTemp_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_EMSMaxPowerModelWaterTmpOut_C((uint8_T)(u0 < 0.0F ? (int32_T)
      (uint8_T)-(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  if (CbEHCS_EMSMinPowerModelWaterTmpInOvrSwt_flg) {
    set_GcEHCS_EMSMinPowerModelWaterTmpIn_C
      (CcEHCS_EMSMinPowerModelWaterTmpInOvr_C);
  } else {
    if ((get_GcEBSW_ACDCAOutWaterTemp_C() <= get_GcEBSW_DCDCAOutWaterTemp_C()) ||
        rtIsNaNF(get_GcEBSW_DCDCAOutWaterTemp_C())) {
      u0 = get_GcEBSW_ACDCAOutWaterTemp_C();
    } else {
      u0 = get_GcEBSW_DCDCAOutWaterTemp_C();
    }

    if (!((u0 <= get_GcEBSW_ACDCBOutWaterTemp_C()) || rtIsNaNF
          (get_GcEBSW_ACDCBOutWaterTemp_C()))) {
      u0 = get_GcEBSW_ACDCBOutWaterTemp_C();
    }

    if (!((u0 <= get_GcEBSW_DCDCBOutWaterTemp_C()) || rtIsNaNF
          (get_GcEBSW_DCDCBOutWaterTemp_C()))) {
      u0 = get_GcEBSW_DCDCBOutWaterTemp_C();
    }

    u0 = (real32_T)floor(u0 + 40.0F);
    if (rtIsNaNF(u0) || rtIsInfF(u0)) {
      u0 = 0.0F;
    } else {
      u0 = (real32_T)fmod(u0, 256.0F);
    }

    set_GcEHCS_EMSMinPowerModelWaterTmpIn_C((uint8_T)(u0 < 0.0F ? (int32_T)
      (uint8_T)-(int8_T)(uint8_T)-u0 : (int32_T)(uint8_T)u0));
  }

  set_GcEHCS_EMSHeatExchangeSelect_numb(0U);
}

/* Model initialize function */
void EHCS_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  set_GcEHCS_BMSMaxBatTmp_C(40U);
  set_GcEHCS_BMSMaxBatWaterTmpOut_C(40U);
  set_GcEHCS_BMSMinBatTmp_C(40U);
  set_GcEHCS_BMSMinBatWaterTmpIn_C(40U);
  set_GcEHCS_EMSHeatSetTmp_C(40U);
  set_GcEHCS_EMSMaxPowerModelWaterTmpOut_C(40U);
  set_GcEHCS_EMSMinPowerModelWaterTmpIn_C(40U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
