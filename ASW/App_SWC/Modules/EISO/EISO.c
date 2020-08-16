/*
 * File: EISO.c
 *
 * Code generated for Simulink model 'EISO'.
 *
 * Company                        : DP
 * Author                         : Àîê»
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 16:42:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EISO.h"
#include "EISO_private.h"

/* Block states (auto storage) */
DW_EISO_T EISO_DW;

/* Real-time model */
RT_MODEL_EISO_T EISO_M_;
RT_MODEL_EISO_T *const EISO_M = &EISO_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EISO_PACKA_10ms_at_outport_1' */
void EISO_PACKA_10ms(void)
{
  boolean_T rtb_LogicalOperator_kh;
  uint16_T rtb_Init_c;
  uint16_T tmp;
  if (get_GbEDEC_PackAAllowedReChrg_flg()) {
    rtb_LogicalOperator_kh = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_LogicalOperator_kh = ((boolean_T)ASWTYPE_FALSE);
  }

  rtb_LogicalOperator_kh = !((get_GeECMM_ChrgCtrAMode_enum() !=
    EISO_ConstB.DataTypeConversion_g) && ((get_GeECCR_CCU1CCUCC1STATE_enum() !=
    EISO_ConstB.DataTypeConversion1_l) && (get_GeECCR_CCU1CCUSTATE_enum() ==
    EISO_ConstB.DataTypeConversion2_h)) && rtb_LogicalOperator_kh);
  if (rtb_LogicalOperator_kh || (EISO_DW.FixPtUnitDelay2_DSTATE_j != 0)) {
    rtb_Init_c = 0U;
  } else {
    rtb_Init_c = EISO_DW.FixPtUnitDelay1_DSTATE_l;
  }

  set_GbEISO_BMS1StartISOEn_flg((rtb_Init_c >= CcEISO_DelayT_ms));
  if (rtb_LogicalOperator_kh) {
    EISO_DW.FixPtUnitDelay1_DSTATE_l = 0U;
  } else {
    if (get_GbEISO_BMS1StartISOEn_flg()) {
      tmp = 0U;
    } else {
      tmp = EISO_RUNTIME_MS;
    }

    EISO_DW.FixPtUnitDelay1_DSTATE_l = (uint16_T)((uint32_T)tmp + rtb_Init_c);
  }

  EISO_DW.FixPtUnitDelay2_DSTATE_j = 0U;
  if (get_GbEDEC_GunAAllowedChrg_flg()) {
    rtb_LogicalOperator_kh = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_LogicalOperator_kh = ((boolean_T)ASWTYPE_FALSE);
  }

  rtb_LogicalOperator_kh = !((get_GeECMM_ChrgCtrAMode_enum() !=
    EISO_ConstB.DataTypeConversion3_i) && ((get_GeECCR_CCU1CCUCC1STATE_enum() ==
    EISO_ConstB.DataTypeConversion4_g) && ((get_GeECCR_CCU1CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion7_i) && (get_GeECCR_CCU1CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion5_l) && (get_GeECCR_CCU1CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion6_d))) && rtb_LogicalOperator_kh);
  if (rtb_LogicalOperator_kh || (EISO_DW.FixPtUnitDelay2_DSTATE_a != 0)) {
    rtb_Init_c = 0U;
  } else {
    rtb_Init_c = EISO_DW.FixPtUnitDelay1_DSTATE_j;
  }

  set_GbEISO_CCU1StartISOEn_flg((rtb_Init_c >= CcEISO_DelayT_ms));
  if (rtb_LogicalOperator_kh) {
    EISO_DW.FixPtUnitDelay1_DSTATE_j = 0U;
  } else {
    if (get_GbEISO_CCU1StartISOEn_flg()) {
      tmp = 0U;
    } else {
      tmp = EISO_RUNTIME_MS;
    }

    EISO_DW.FixPtUnitDelay1_DSTATE_j = (uint16_T)((uint32_T)tmp + rtb_Init_c);
  }

  EISO_DW.FixPtUnitDelay2_DSTATE_a = 0U;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EISO_PACKB_10ms_at_outport_1' */
void EISO_PACKB_10ms(void)
{
  boolean_T rtb_LogicalOperator_m;
  uint16_T rtb_Init_g;
  uint16_T tmp;
  if (get_GbEDEC_PackBAllowedReChrg_flg()) {
    rtb_LogicalOperator_m = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_LogicalOperator_m = ((boolean_T)ASWTYPE_FALSE);
  }

  rtb_LogicalOperator_m = !((get_GeECMM_ChrgCtrBMode_enum() !=
    EISO_ConstB.DataTypeConversion1) && ((get_GeECCR_CCU2CCUCC1STATE_enum() !=
    EISO_ConstB.DataTypeConversion) && (get_GeECCR_CCU2CCUSTATE_enum() ==
    EISO_ConstB.DataTypeConversion2)) && rtb_LogicalOperator_m);
  if (rtb_LogicalOperator_m || (EISO_DW.FixPtUnitDelay2_DSTATE_l != 0)) {
    rtb_Init_g = 0U;
  } else {
    rtb_Init_g = EISO_DW.FixPtUnitDelay1_DSTATE_d;
  }

  set_GbEISO_BMS2StartISOEn_flg((rtb_Init_g >= CcEISO_DelayT_ms));
  if (rtb_LogicalOperator_m) {
    EISO_DW.FixPtUnitDelay1_DSTATE_d = 0U;
  } else {
    if (get_GbEISO_BMS2StartISOEn_flg()) {
      tmp = 0U;
    } else {
      tmp = EISO_RUNTIME_MS;
    }

    EISO_DW.FixPtUnitDelay1_DSTATE_d = (uint16_T)((uint32_T)tmp + rtb_Init_g);
  }

  EISO_DW.FixPtUnitDelay2_DSTATE_l = 0U;
  if (get_GbEDEC_GunBAllowedChrg_flg()) {
    rtb_LogicalOperator_m = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_LogicalOperator_m = ((boolean_T)ASWTYPE_FALSE);
  }

  rtb_LogicalOperator_m = !((get_GeECMM_ChrgCtrBMode_enum() !=
    EISO_ConstB.DataTypeConversion3) && ((get_GeECCR_CCU2CCUCC1STATE_enum() ==
    EISO_ConstB.DataTypeConversion4) && ((get_GeECCR_CCU2CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion5) && (get_GeECCR_CCU2CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion6) && (get_GeECCR_CCU2CCUSTATE_enum() !=
    EISO_ConstB.DataTypeConversion7))) && rtb_LogicalOperator_m);
  if (rtb_LogicalOperator_m || (EISO_DW.FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_g = 0U;
  } else {
    rtb_Init_g = EISO_DW.FixPtUnitDelay1_DSTATE;
  }

  set_GbEISO_CCU2StartISOEn_flg((rtb_Init_g >= CcEISO_DelayT_ms));
  if (rtb_LogicalOperator_m) {
    EISO_DW.FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (get_GbEISO_CCU2StartISOEn_flg()) {
      tmp = 0U;
    } else {
      tmp = EISO_RUNTIME_MS;
    }

    EISO_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_g);
  }

  EISO_DW.FixPtUnitDelay2_DSTATE = 0U;
}

/* Model initialize function */
void EISO_initialize(void)
{
  EISO_DW.FixPtUnitDelay2_DSTATE_j = 1U;
  EISO_DW.FixPtUnitDelay2_DSTATE_a = 1U;
  EISO_DW.FixPtUnitDelay2_DSTATE_l = 1U;
  EISO_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
