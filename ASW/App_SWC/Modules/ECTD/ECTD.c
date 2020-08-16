/*
 * File: ECTD.c
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

#include "ECTD.h"
#include "ECTD_private.h"

/* Block signals (auto storage) */
B_ECTD_T ECTD_B;

/* Block states (auto storage) */
DW_ECTD_T ECTD_DW;

/* Real-time model */
RT_MODEL_ECTD_T ECTD_M_;
RT_MODEL_ECTD_T *const ECTD_M = &ECTD_M_;

/*
 * Output and update for atomic system:
 *    '<S13>/DebounceStartZero'
 *    '<S14>/DebounceStartZero'
 *    '<S38>/DebounceStartZero'
 *    '<S39>/DebounceStartZero'
 *    '<S63>/DebounceStartZero'
 *    '<S64>/DebounceStartZero'
 *    '<S88>/DebounceStartZero'
 *    '<S89>/DebounceStartZero'
 *    '<S118>/DebounceStartZero'
 *    '<S119>/DebounceStartZero'
 *    ...
 */
void ECTD_DebounceStartZero(boolean_T rtu_Signal, uint16_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_ECTD_T *localB,
  DW_DebounceStartZero_ECTD_T *localDW)
{
  boolean_T rtb_RelationalOperator_m4;
  boolean_T rtb_RelationalOperator_dw;
  uint32_T rtb_Switch2_b1;
  uint32_T rtb_Switch2_e;
  if (localDW->StateName_os) {
    rtb_Switch2_b1 = 0U;
  } else {
    rtb_Switch2_b1 = localDW->StateName_g;
  }

  if (rtu_Signal) {
    rtb_Switch2_b1 += rtu_FaultStep;
  } else if (rtb_Switch2_b1 >= rtu_FaultStep) {
    rtb_Switch2_b1 -= rtu_FaultStep;
  } else {
    rtb_Switch2_b1 = 0U;
  }

  rtb_RelationalOperator_m4 = (rtb_Switch2_b1 > rtu_Hearl2Fault);
  if (localDW->StateName_f) {
    rtb_Switch2_e = 0U;
  } else {
    rtb_Switch2_e = localDW->StateName_o;
  }

  if (!rtu_Signal) {
    rtb_Switch2_e += rtu_FaultStep;
  } else if (rtb_Switch2_e >= rtu_FaultStep) {
    rtb_Switch2_e -= rtu_FaultStep;
  } else {
    rtb_Switch2_e = 0U;
  }

  rtb_RelationalOperator_dw = (rtb_Switch2_e > rtu_Hearl2Fault);
  if (localB->Switch == 0.0F) {
    if (rtb_RelationalOperator_m4) {
      localB->Switch = 1.0F;
    } else {
      localB->Switch = 0.0F;
    }
  } else {
    if (rtb_RelationalOperator_dw) {
      localB->Switch = 0.0F;
    }
  }

  localDW->StateName_os = rtb_RelationalOperator_m4;
  localDW->StateName_g = rtb_Switch2_b1;
  localDW->StateName_f = rtb_RelationalOperator_dw;
  localDW->StateName_o = rtb_Switch2_e;
}

/*
 * Output and update for atomic system:
 *    '<S6>/DebounceStartZero'
 *    '<S6>/DebounceStartZero1'
 *    '<S6>/DebounceStartZero2'
 *    '<S6>/DebounceStartZero3'
 *    '<S6>/DebounceStartZero4'
 *    '<S6>/DebounceStartZero5'
 *    '<S6>/DebounceStartZero6'
 *    '<S6>/DebounceStartZero7'
 *    '<S6>/DebounceStartZero8'
 *    '<S6>/DebounceStartZero9'
 */
void ECTD_DebounceStartZero_p(boolean_T rtu_Signal, uint16_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_ECTD_c_T *localB,
  DW_DebounceStartZero_ECTD_m_T *localDW)
{
  boolean_T rtb_RelationalOperator_dv;
  boolean_T rtb_RelationalOperator_de;
  uint32_T rtb_Switch2_da;
  uint32_T rtb_Switch2_p;
  if (localDW->StateName_gk) {
    rtb_Switch2_da = 0U;
  } else {
    rtb_Switch2_da = localDW->StateName;
  }

  if (rtu_Signal) {
    rtb_Switch2_da += rtu_FaultStep;
  } else if (rtb_Switch2_da >= rtu_FaultStep) {
    rtb_Switch2_da -= rtu_FaultStep;
  } else {
    rtb_Switch2_da = 0U;
  }

  rtb_RelationalOperator_dv = (rtb_Switch2_da > rtu_Hearl2Fault);
  if (localDW->StateName_f) {
    rtb_Switch2_p = 0U;
  } else {
    rtb_Switch2_p = localDW->StateName_c;
  }

  if (!rtu_Signal) {
    rtb_Switch2_p += rtu_FaultStep;
  } else if (rtb_Switch2_p >= rtu_FaultStep) {
    rtb_Switch2_p -= rtu_FaultStep;
  } else {
    rtb_Switch2_p = 0U;
  }

  rtb_RelationalOperator_de = (rtb_Switch2_p > rtu_Hearl2Fault);
  if (!localB->Switch) {
    localB->Switch = rtb_RelationalOperator_dv;
  } else if (rtb_RelationalOperator_de) {
    localB->Switch = false;
  } else {
    localB->Switch = true;
  }

  localDW->StateName_gk = rtb_RelationalOperator_dv;
  localDW->StateName = rtb_Switch2_da;
  localDW->StateName_f = rtb_RelationalOperator_de;
  localDW->StateName_c = rtb_Switch2_p;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTD_20ms_at_outport_1' */
void ECTD_20ms(void)
{
  boolean_T rtb_Switch4;
  boolean_T rtb_Switch6;
  boolean_T rtb_Switch;
  boolean_T rtb_Switch2;
  boolean_T rtb_Switch3;
  boolean_T rtb_Switch7;
  boolean_T rtb_Switch4_n;
  boolean_T rtb_Switch1;
  boolean_T rtb_Switch4_h;
  boolean_T rtb_Switch6_pj;
  boolean_T rtb_Switch2_p;
  boolean_T rtb_Switch_ia;
  boolean_T rtb_Switch4_p;
  boolean_T rtb_Switch7_j;
  boolean_T rtb_Switch3_p;
  boolean_T rtb_Switch1_g;
  boolean_T rtb_Switch3_l;
  boolean_T rtb_Switch7_hk;
  boolean_T rtb_Switch4_my;
  boolean_T rtb_Switch1_pg;
  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgANCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero, &ECTD_DW.DebounceStartZero);
  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgANCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_l, &ECTD_DW.DebounceStartZero_l);
  if (ECTD_B.DebounceStartZero.Switch != 0.0F) {
    rtb_Switch4 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_l.Switch != 0.0F) {
    rtb_Switch4 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4 = ECTD_DW.Delay2_DSTATE;
  }

  if (CbECTD_ReChrgANCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgANCtrCloseDiagFlt_flg(CbECTD_ReChrgANCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgANCtrCloseDiagFlt_flg(rtb_Switch4);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgANCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_c, &ECTD_DW.DebounceStartZero_c);
  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgANCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_p, &ECTD_DW.DebounceStartZero_p);
  if (ECTD_B.DebounceStartZero_c.Switch != 0.0F) {
    rtb_Switch6 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_p.Switch != 0.0F) {
    rtb_Switch6 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch6 = ECTD_DW.Delay3_DSTATE;
  }

  if (CbECTD_ReChrgANCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgANCtrOpenDiagFlt_flg(CbECTD_ReChrgANCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgANCtrOpenDiagFlt_flg(rtb_Switch6);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgAPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_o, &ECTD_DW.DebounceStartZero_o);
  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgAPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_d, &ECTD_DW.DebounceStartZero_d);
  if (ECTD_B.DebounceStartZero_o.Switch != 0.0F) {
    rtb_Switch = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_d.Switch != 0.0F) {
    rtb_Switch = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch = ECTD_DW.Delay_DSTATE;
  }

  if (CbECTD_ReChrgAPCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgAPCtrCloseDiagFlt_flg(CbECTD_ReChrgAPCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgAPCtrCloseDiagFlt_flg(rtb_Switch);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgAPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_f, &ECTD_DW.DebounceStartZero_f);
  ECTD_DebounceStartZero((get_GeEBCR_BMSAPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgAPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_px, &ECTD_DW.DebounceStartZero_px);
  if (ECTD_B.DebounceStartZero_f.Switch != 0.0F) {
    rtb_Switch2 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_px.Switch != 0.0F) {
    rtb_Switch2 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch2 = ECTD_DW.Delay1_DSTATE;
  }

  if (CbECTD_ReChrgAPCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgAPCtrOpenDiagFlt_flg(CbECTD_ReChrgAPCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgAPCtrOpenDiagFlt_flg(rtb_Switch2);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgANCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgANCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_h, &ECTD_DW.DebounceStartZero_h);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgANCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgANCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_k, &ECTD_DW.DebounceStartZero_k);
  if (ECTD_B.DebounceStartZero_k.Switch != 0.0F) {
    rtb_Switch3 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_h.Switch != 0.0F) {
    rtb_Switch3 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch3 = ECTD_DW.Delay3_DSTATE_k;
  }

  if (CbECTD_CChrgANCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgANCtrCloseDiagFlt_flg(CbECTD_CChrgANCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgANCtrCloseDiagFlt_flg(rtb_Switch3);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgANCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgANCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_e, &ECTD_DW.DebounceStartZero_e);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgANCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgANCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_k3, &ECTD_DW.DebounceStartZero_k3);
  if (ECTD_B.DebounceStartZero_k3.Switch != 0.0F) {
    rtb_Switch7 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_e.Switch != 0.0F) {
    rtb_Switch7 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch7 = ECTD_DW.Delay4_DSTATE;
  }

  if (CbECTD_CChrgANCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgANCtrOpenDiagFlt_flg(CbECTD_CChrgANCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgANCtrOpenDiagFlt_flg(rtb_Switch7);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgAPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgAPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_a, &ECTD_DW.DebounceStartZero_a);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgAPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgAPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_i, &ECTD_DW.DebounceStartZero_i);
  if (ECTD_B.DebounceStartZero_i.Switch != 0.0F) {
    rtb_Switch4_n = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_a.Switch != 0.0F) {
    rtb_Switch4_n = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4_n = ECTD_DW.Delay2_DSTATE_i;
  }

  if (CbECTD_CChrgAPCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgAPCtrCloseDiagFlt_flg(CbECTD_CChrgAPCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgAPCtrCloseDiagFlt_flg(rtb_Switch4_n);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgAPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgAPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ox, &ECTD_DW.DebounceStartZero_ox);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgAPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgAPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_n, &ECTD_DW.DebounceStartZero_n);
  if (ECTD_B.DebounceStartZero_n.Switch != 0.0F) {
    rtb_Switch1 = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ox.Switch != 0.0F) {
    rtb_Switch1 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch1 = ECTD_DW.Delay1_DSTATE_o;
  }

  if (CbECTD_CChrgAPCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgAPCtrOpenDiagFlt_flg(CbECTD_CChrgAPCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgAPCtrOpenDiagFlt_flg(rtb_Switch1);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgBNCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_j, &ECTD_DW.DebounceStartZero_j);
  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgBNCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ft, &ECTD_DW.DebounceStartZero_ft);
  if (ECTD_B.DebounceStartZero_j.Switch != 0.0F) {
    rtb_Switch4_h = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ft.Switch != 0.0F) {
    rtb_Switch4_h = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4_h = ECTD_DW.Delay2_DSTATE_f;
  }

  if (CbECTD_ReChrgBNCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgBNCtrCloseDiagFlt_flg(CbECTD_ReChrgBNCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgBNCtrCloseDiagFlt_flg(rtb_Switch4_h);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgBNCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_i5, &ECTD_DW.DebounceStartZero_i5);
  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgNegStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgBNCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_m, &ECTD_DW.DebounceStartZero_m);
  if (ECTD_B.DebounceStartZero_i5.Switch != 0.0F) {
    rtb_Switch6_pj = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_m.Switch != 0.0F) {
    rtb_Switch6_pj = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch6_pj = ECTD_DW.Delay3_DSTATE_l;
  }

  if (CbECTD_ReChrgBNCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgBNCtrOpenDiagFlt_flg(CbECTD_ReChrgBNCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgBNCtrOpenDiagFlt_flg(rtb_Switch6_pj);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgBPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_oq, &ECTD_DW.DebounceStartZero_oq);
  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgBPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_m3, &ECTD_DW.DebounceStartZero_m3);
  if (ECTD_B.DebounceStartZero_oq.Switch != 0.0F) {
    rtb_Switch2_p = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_m3.Switch != 0.0F) {
    rtb_Switch2_p = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch2_p = ECTD_DW.Delay1_DSTATE_i;
  }

  if (CbECTD_ReChrgBPCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgBPCtrCloseDiagFlt_flg(CbECTD_ReChrgBPCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgBPCtrCloseDiagFlt_flg(rtb_Switch2_p);
  }

  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTC_ReChrgBPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ao, &ECTD_DW.DebounceStartZero_ao);
  ECTD_DebounceStartZero((get_GeEBCR_BMSBPack1RechrgPosStat_enum() ==
    ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTC_ReChrgBPCtrCmd_flg() ==
    ((boolean_T)ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_kt, &ECTD_DW.DebounceStartZero_kt);
  if (ECTD_B.DebounceStartZero_ao.Switch != 0.0F) {
    rtb_Switch_ia = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_kt.Switch != 0.0F) {
    rtb_Switch_ia = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch_ia = ECTD_DW.Delay_DSTATE_a;
  }

  if (CbECTD_ReChrgBPCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_ReChrgBPCtrOpenDiagFlt_flg(CbECTD_ReChrgBPCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_ReChrgBPCtrOpenDiagFlt_flg(rtb_Switch_ia);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgBNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgBNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_on, &ECTD_DW.DebounceStartZero_on);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgBNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgBNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_o4, &ECTD_DW.DebounceStartZero_o4);
  if (ECTD_B.DebounceStartZero_o4.Switch != 0.0F) {
    rtb_Switch4_p = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_on.Switch != 0.0F) {
    rtb_Switch4_p = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4_p = ECTD_DW.Delay2_DSTATE_fk;
  }

  if (CbECTD_CChrgBNCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgBNCtrCloseDiagFlt_flg(CbECTD_CChrgBNCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgBNCtrCloseDiagFlt_flg(rtb_Switch4_p);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgBNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgBNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ek, &ECTD_DW.DebounceStartZero_ek);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgBNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgBNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ju, &ECTD_DW.DebounceStartZero_ju);
  if (ECTD_B.DebounceStartZero_ju.Switch != 0.0F) {
    rtb_Switch7_j = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ek.Switch != 0.0F) {
    rtb_Switch7_j = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch7_j = ECTD_DW.Delay4_DSTATE_b;
  }

  if (CbECTD_CChrgBNCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgBNCtrOpenDiagFlt_flg(CbECTD_CChrgBNCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgBNCtrOpenDiagFlt_flg(rtb_Switch7_j);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgBPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgBPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_eo, &ECTD_DW.DebounceStartZero_eo);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgBPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgBPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_g, &ECTD_DW.DebounceStartZero_g);
  if (ECTD_B.DebounceStartZero_g.Switch != 0.0F) {
    rtb_Switch3_p = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_eo.Switch != 0.0F) {
    rtb_Switch3_p = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch3_p = ECTD_DW.Delay3_DSTATE_f;
  }

  if (CbECTD_CChrgBPCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgBPCtrCloseDiagFlt_flg(CbECTD_CChrgBPCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgBPCtrCloseDiagFlt_flg(rtb_Switch3_p);
  }

  ECTD_DebounceStartZero((get_GbEBSW_CChrgBPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_CChrgBPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ekz, &ECTD_DW.DebounceStartZero_ekz);
  ECTD_DebounceStartZero((get_GbEBSW_CChrgBPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_CChrgBPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_cl, &ECTD_DW.DebounceStartZero_cl);
  if (ECTD_B.DebounceStartZero_cl.Switch != 0.0F) {
    rtb_Switch1_g = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ekz.Switch != 0.0F) {
    rtb_Switch1_g = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch1_g = ECTD_DW.Delay1_DSTATE_d;
  }

  if (CbECTD_CChrgBPCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_CChrgBPCtrOpenDiagFlt_flg(CbECTD_CChrgBPCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_CChrgBPCtrOpenDiagFlt_flg(rtb_Switch1_g);
  }

  ECTD_DebounceStartZero((get_GbEBSW_BCChrgNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_BCChrgNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ir, &ECTD_DW.DebounceStartZero_ir);
  ECTD_DebounceStartZero((get_GbEBSW_BCChrgNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_BCChrgNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ns, &ECTD_DW.DebounceStartZero_ns);
  if (ECTD_B.DebounceStartZero_ns.Switch != 0.0F) {
    rtb_Switch3_l = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ir.Switch != 0.0F) {
    rtb_Switch3_l = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch3_l = ECTD_DW.Delay3_DSTATE_o;
  }

  if (CbECTD_BCChrgNCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_BCChrgNCtrCloseDiagFlt_flg(CbECTD_BCChrgNCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_BCChrgNCtrCloseDiagFlt_flg(rtb_Switch3_l);
  }

  ECTD_DebounceStartZero((get_GbEBSW_BCChrgNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_BCChrgNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_b, &ECTD_DW.DebounceStartZero_b);
  ECTD_DebounceStartZero((get_GbEBSW_BCChrgNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_BCChrgNCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ef, &ECTD_DW.DebounceStartZero_ef);
  if (ECTD_B.DebounceStartZero_ef.Switch != 0.0F) {
    rtb_Switch7_hk = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_b.Switch != 0.0F) {
    rtb_Switch7_hk = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch7_hk = ECTD_DW.Delay4_DSTATE_c;
  }

  if (CbECTD_BCChrgNCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_BCChrgNCtrOpenDiagFlt_flg(CbECTD_BCChrgNCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_BCChrgNCtrOpenDiagFlt_flg(rtb_Switch7_hk);
  }

  ECTD_DebounceStartZero((get_GbEBSW_BCChrgPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_BCChrgPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_aw, &ECTD_DW.DebounceStartZero_aw);
  ECTD_DebounceStartZero((get_GbEBSW_BCChrgPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_BCChrgPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_o4j, &ECTD_DW.DebounceStartZero_o4j);
  if (ECTD_B.DebounceStartZero_o4j.Switch != 0.0F) {
    rtb_Switch4_my = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_aw.Switch != 0.0F) {
    rtb_Switch4_my = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4_my = ECTD_DW.Delay2_DSTATE_fq;
  }

  if (CbECTD_BCChrgPCtrCloseDiagFltOvrSwt_flg) {
    set_GbECTD_BCChrgPCtrCloseDiagFlt_flg(CbECTD_BCChrgPCtrCloseDiagFltOvr_flg);
  } else {
    set_GbECTD_BCChrgPCtrCloseDiagFlt_flg(rtb_Switch4_my);
  }

  ECTD_DebounceStartZero((get_GbEBSW_BCChrgPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbECTC_BCChrgPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_ph, &ECTD_DW.DebounceStartZero_ph);
  ECTD_DebounceStartZero((get_GbEBSW_BCChrgPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbECTC_BCChrgPCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcECTD_DebounceTime300ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_es, &ECTD_DW.DebounceStartZero_es);
  if (ECTD_B.DebounceStartZero_es.Switch != 0.0F) {
    rtb_Switch1_pg = ((boolean_T)ASWTYPE_TRUE);
  } else if (ECTD_B.DebounceStartZero_ph.Switch != 0.0F) {
    rtb_Switch1_pg = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch1_pg = ECTD_DW.Delay1_DSTATE_df;
  }

  if (CbECTD_BCChrgPCtrOpenDiagFltOvrSwt_flg) {
    set_GbECTD_BCChrgPCtrOpenDiagFlt_flg(CbECTD_BCChrgPCtrOpenDiagFltOvr_flg);
  } else {
    set_GbECTD_BCChrgPCtrOpenDiagFlt_flg(rtb_Switch1_pg);
  }

  ECTD_DebounceStartZero_p(get_GeEBCR_BMSAPack1RechrgPosStat_enum() ==
    ECTD_ConstB.DataTypeConversion, CcECTD_DebounceTime60ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero_phs, &ECTD_DW.DebounceStartZero_phs);
  if (CbECTD_ReChrgAPCtrFilStaOvrSwt_flg) {
    set_GbECTD_ReChrgAPCtrFilSta_flg(CbECTD_ReChrgAPCtrFilStaOvr_flg);
  } else {
    set_GbECTD_ReChrgAPCtrFilSta_flg(ECTD_B.DebounceStartZero_phs.Switch);
  }

  ECTD_DebounceStartZero_p(get_GeEBCR_BMSAPack1RechrgNegStat_enum() ==
    ECTD_ConstB.DataTypeConversion1, CcECTD_DebounceTime60ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero1, &ECTD_DW.DebounceStartZero1);
  if (CbECTD_ReChrgANCtrFilStaOvrSwt_flg) {
    set_GbECTD_ReChrgANCtrFilSta_flg(CbECTD_ReChrgANCtrFilStaOvr_flg);
  } else {
    set_GbECTD_ReChrgANCtrFilSta_flg(ECTD_B.DebounceStartZero1.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_CChrgAPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero2, &ECTD_DW.DebounceStartZero2);
  if (CbECTD_CChrgAPCtrFilStaOvrSwt_flg) {
    set_GbECTD_CChrgAPCtrFilSta_flg(CbECTD_CChrgAPCtrFilStaOvr_flg);
  } else {
    set_GbECTD_CChrgAPCtrFilSta_flg(ECTD_B.DebounceStartZero2.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_CChrgANCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero3, &ECTD_DW.DebounceStartZero3);
  if (CbECTD_CChrgANCtrFilStaOvrSwt_flg) {
    set_GbECTD_CChrgANCtrFilSta_flg(CbECTD_CChrgANCtrFilStaOvr_flg);
  } else {
    set_GbECTD_CChrgANCtrFilSta_flg(ECTD_B.DebounceStartZero3.Switch);
  }

  ECTD_DebounceStartZero_p(get_GeEBCR_BMSBPack1RechrgPosStat_enum() ==
    ECTD_ConstB.DataTypeConversion2, CcECTD_DebounceTime60ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero4, &ECTD_DW.DebounceStartZero4);
  if (CbECTD_ReChrgBPCtrFilStaOvrSwt_flg) {
    set_GbECTD_ReChrgBPCtrFilSta_flg(CbECTD_ReChrgBPCtrFilStaOvr_flg);
  } else {
    set_GbECTD_ReChrgBPCtrFilSta_flg(ECTD_B.DebounceStartZero4.Switch);
  }

  ECTD_DebounceStartZero_p(get_GeEBCR_BMSBPack1RechrgNegStat_enum() ==
    ECTD_ConstB.DataTypeConversion3, CcECTD_DebounceTime60ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero5, &ECTD_DW.DebounceStartZero5);
  if (CbECTD_ReChrgBNCtrFilStaOvrSwt_flg) {
    set_GbECTD_ReChrgBNCtrFilSta_flg(CbECTD_ReChrgBNCtrFilStaOvr_flg);
  } else {
    set_GbECTD_ReChrgBNCtrFilSta_flg(ECTD_B.DebounceStartZero5.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_CChrgBPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero6, &ECTD_DW.DebounceStartZero6);
  if (CbECTD_CChrgBPCtrFilStaOvrSwt_flg) {
    set_GbECTD_CChrgBPCtrFilSta_flg(CbECTD_CChrgBPCtrFilStaOvr_flg);
  } else {
    set_GbECTD_CChrgBPCtrFilSta_flg(ECTD_B.DebounceStartZero6.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_CChrgBNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero7, &ECTD_DW.DebounceStartZero7);
  if (CbEECTD_CChrgBNCtrFilStaOvrSwt_flg) {
    set_GbECTD_CChrgBNCtrFilSta_flg(CbECTD_CChrgBNCtrFilStaOvr_flg);
  } else {
    set_GbECTD_CChrgBNCtrFilSta_flg(ECTD_B.DebounceStartZero7.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_BCChrgPCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero8, &ECTD_DW.DebounceStartZero8);
  if (CbECTD_BCChrgPCtrFilStaOvrSwt_flg) {
    set_GbECTD_BCChrgPCtrFilSta_flg(CbECTD_BCChrgPCtrFilStaOvr_flg);
  } else {
    set_GbECTD_BCChrgPCtrFilSta_flg(ECTD_B.DebounceStartZero8.Switch);
  }

  ECTD_DebounceStartZero_p(get_GbEBSW_BCChrgNCtrAuxIn_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcECTD_DebounceTime40ms_ms, ECTD_RUNTIME_MS,
    &ECTD_B.DebounceStartZero9, &ECTD_DW.DebounceStartZero9);
  if (CbECTD_BCChrgNCtrFilStaOvrSwt_flg) {
    set_GbECTD_BCChrgNCtrFilSta_flg(CbECTD_BCChrgNCtrFilStaOvr_flg);
  } else {
    set_GbECTD_BCChrgNCtrFilSta_flg(ECTD_B.DebounceStartZero9.Switch);
  }

  ECTD_DW.Delay2_DSTATE = rtb_Switch4;
  ECTD_DW.Delay3_DSTATE = rtb_Switch6;
  ECTD_DW.Delay_DSTATE = rtb_Switch;
  ECTD_DW.Delay1_DSTATE = rtb_Switch2;
  ECTD_DW.Delay3_DSTATE_k = rtb_Switch3;
  ECTD_DW.Delay4_DSTATE = rtb_Switch7;
  ECTD_DW.Delay2_DSTATE_i = rtb_Switch4_n;
  ECTD_DW.Delay1_DSTATE_o = rtb_Switch1;
  ECTD_DW.Delay2_DSTATE_f = rtb_Switch4_h;
  ECTD_DW.Delay3_DSTATE_l = rtb_Switch6_pj;
  ECTD_DW.Delay1_DSTATE_i = rtb_Switch2_p;
  ECTD_DW.Delay_DSTATE_a = rtb_Switch_ia;
  ECTD_DW.Delay2_DSTATE_fk = rtb_Switch4_p;
  ECTD_DW.Delay4_DSTATE_b = rtb_Switch7_j;
  ECTD_DW.Delay3_DSTATE_f = rtb_Switch3_p;
  ECTD_DW.Delay1_DSTATE_d = rtb_Switch1_g;
  ECTD_DW.Delay3_DSTATE_o = rtb_Switch3_l;
  ECTD_DW.Delay4_DSTATE_c = rtb_Switch7_hk;
  ECTD_DW.Delay2_DSTATE_fq = rtb_Switch4_my;
  ECTD_DW.Delay1_DSTATE_df = rtb_Switch1_pg;
}

/* Model initialize function */
void ECTD_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
