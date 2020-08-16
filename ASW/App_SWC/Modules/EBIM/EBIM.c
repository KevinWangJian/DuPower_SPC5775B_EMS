/*
 * File: EBIM.c
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EBIM.h"
#include "EBIM_private.h"

/* Block states (auto storage) */
DW_EBIM_T EBIM_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_EBIM_T EBIM_U;

/* Real-time model */
RT_MODEL_EBIM_T EBIM_M_;
RT_MODEL_EBIM_T *const EBIM_M = &EBIM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBIM_BMSInterMgt_10ms_at_outport_1' */
void EBIM_BMSInterMgt_10ms(void)
{
  boolean_T rtb_Switch2_j;
  boolean_T rtb_Switch2_d;
  uint8_T rtb_Switch2;
  uint8_T rtb_Switch2_i;
  int32_T rtb_Switch;
  if ((get_GcEBCR_BMSARealSOC_pct() >= SOC_100) || (get_GbEBSW_UserForceStop_flg
       () == ((boolean_T)ASWTYPE_TRUE)) || (get_GbEDEC_PackAAllowedDisChrg_flg()
       == ((boolean_T)ASWTYPE_FALSE)) || (get_GbEDEC_PackAAllowedReChrg_flg() ==
       ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch2_j = ((boolean_T)ASWTYPE_FALSE);
  } else if ((get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (get_GcEBCR_BMSARealSOC_pct() < SOC_80)) {
    rtb_Switch2_j = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Switch2_j = EBIM_DW.StateName_l;
  }

  if (CbEBIM_PackAAllowedReChrgOvrSwt_flg) {
    set_GbEBIM_PackAAllowedReChrg_flg(CbEBIM_PackAAllowedReChrgOvr_flg);
  } else {
    set_GbEBIM_PackAAllowedReChrg_flg(rtb_Switch2_j);
  }

  if ((get_GcEBCR_BMSBRealSOC_pct() >= SOC_100) || (get_GbEBSW_UserForceStop_flg
       () == ((boolean_T)ASWTYPE_TRUE)) || (get_GbEDEC_PackBAllowedDisChrg_flg()
       == ((boolean_T)ASWTYPE_FALSE)) || (get_GbEDEC_PackBAllowedReChrg_flg() ==
       ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch2_d = ((boolean_T)ASWTYPE_FALSE);
  } else if ((get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (get_GcEBCR_BMSBRealSOC_pct() < SOC_80)) {
    rtb_Switch2_d = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Switch2_d = EBIM_DW.StateName_e;
  }

  if (CbEBIM_PackBAllowedReChrgOvrSwt_flg) {
    set_GbEBIM_PackBAllowedReChrg_flg(CbEBIM_PackBAllowedReChrgOvr_flg);
  } else {
    set_GbEBIM_PackBAllowedReChrg_flg(rtb_Switch2_d);
  }

  if ((get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_FALSE)) ||
      (get_GbEBSW_UserForceStop_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      (get_GeEBCR_BMSAHVSysStat_enum() == EBIM_ConstB.DataTypeConversion2) ||
      ((EBIM_U.GbEBSW_T645ThreePhaseOnline_flg == ((boolean_T)ASWTYPE_FALSE)) &&
       (get_GcEBCR_BMSARealSOC_pct() <= CcEBIM_BMSASOC10_pct))) {
    rtb_Switch2 = EBIM_OFF;
  } else if ((get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
               ASWTYPE_TRUE))) {
    rtb_Switch2 = EBIM_ON;
  } else {
    rtb_Switch2 = EBIM_DW.StateName;
  }

  if (CbEBIM_BMSAHVCtrCmdOvrSwt_flg) {
    set_GeEBIM_BMSAHVCtrCmd_enum(CeEBIM_BMSAHVCtrCmdOvr_enum);
  } else {
    set_GeEBIM_BMSAHVCtrCmd_enum(rtb_Switch2);
  }

  if ((get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_FALSE)) ||
      (get_GbEBSW_UserForceStop_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      (get_GeEBCR_BMSBHVSysStat_enum() == EBIM_ConstB.DataTypeConversion2_g) ||
      ((EBIM_U.GbEBSW_T645ThreePhaseOnline_flg == ((boolean_T)ASWTYPE_FALSE)) &&
       (get_GcEBCR_BMSBRealSOC_pct() <= CcEBIM_BMSBSOC10_pct))) {
    rtb_Switch2_i = EBIM_OFF;
  } else if ((get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
               ASWTYPE_TRUE))) {
    rtb_Switch2_i = EBIM_ON;
  } else {
    rtb_Switch2_i = EBIM_DW.StateName_h;
  }

  if (CbEBIM_BMSBHVCtrCmdOvrSwt_flg) {
    set_GeEBIM_BMSBHVCtrCmd_enum(CeEBIM_BMSBHVCtrCmdOvr_enum);
  } else {
    set_GeEBIM_BMSBHVCtrCmd_enum(rtb_Switch2_i);
  }

  if (CbEBIM_PackANotAllowedDisChargeOvrSwt_flg) {
    set_GbEBIM_PackANotAllowedDisCharge_flg
      (CbEBIM_PackANotAllowedDisChargeOvr_flg);
  } else {
    set_GbEBIM_PackANotAllowedDisCharge_flg((get_GcEBCR_BMSARealSOC_pct() <=
      SOC_10));
  }

  if (CbEBIM_PackBNotAllowedDisChargeOvrSwt_flg) {
    set_GbEBIM_PackBNotAllowedDisCharge_flg
      (CbEBIM_PackBNotAllowedDisChargeOvr_flg);
  } else {
    set_GbEBIM_PackBNotAllowedDisCharge_flg((get_GcEBCR_BMSBRealSOC_pct() <=
      SOC_10));
  }

  if (get_GbEBCR_BMSAPackVoltVld_flg()) {
    rtb_Switch = 700;
  } else {
    rtb_Switch = 150;
  }

  if (CbEBIM_PackAOutVoltReqOvrSwt_flg) {
    set_GcEBIM_PackAOutVoltReq_V(CcEBIM_PackAOutVoltReqOvr_V);
  } else {
    set_GcEBIM_PackAOutVoltReq_V((real32_T)rtb_Switch);
  }

  if (CbEBIM_PackAOutCurrReqOvrSwt_flg) {
    set_GcEBIM_PackAOutCurrReq_A(CcEBIM_PackAOutCurrReqOvr_A);
  } else {
    set_GcEBIM_PackAOutCurrReq_A((real32_T)(get_GcEBCR_BMSAHVBCPLngTrmChrgPwr_kW
      () / (real_T)rtb_Switch * 1000.0));
  }

  if (get_GbEBCR_BMSBPackVoltVld_flg()) {
    rtb_Switch = 700;
  } else {
    rtb_Switch = 150;
  }

  if (CbEBIM_PackBOutVoltReqOvrSwt_flg) {
    set_GcEBIM_PackBOutVoltReq_V(CcEBIM_PackBOutVoltReqOvr_V);
  } else {
    set_GcEBIM_PackBOutVoltReq_V((real32_T)rtb_Switch);
  }

  if (CbEBIM_PackBOutCurrReqOvrSwt_flg) {
    set_GcEBIM_PackBOutCurrReq_A(CcEBIM_PackBOutCurrReqOvr_A);
  } else {
    set_GcEBIM_PackBOutCurrReq_A((real32_T)(get_GcEBCR_BMSBHVBCPLngTrmChrgPwr_kW
      () / (real_T)rtb_Switch * 1000.0));
  }

  EBIM_DW.StateName_l = rtb_Switch2_j;
  EBIM_DW.StateName_e = rtb_Switch2_d;
  EBIM_DW.StateName = rtb_Switch2;
  EBIM_DW.StateName_h = rtb_Switch2_i;
}

/* Model initialize function */
void EBIM_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
