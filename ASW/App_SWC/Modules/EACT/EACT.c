/*
 * File: EACT.c
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

#include "EACT.h"
#include "EACT_private.h"

/* Block signals (auto storage) */
B_EACT_T EACT_B;

/* Block states (auto storage) */
DW_EACT_T EACT_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_EACT_T EACT_U;

/* Real-time model */
RT_MODEL_EACT_T EACT_M_;
RT_MODEL_EACT_T *const EACT_M = &EACT_M_;

/*
 * Output and update for atomic system:
 *    '<S4>/DebounceStartZero'
 *    '<S4>/DebounceStartZero1'
 *    '<S4>/DebounceStartZero2'
 *    '<S60>/DebounceStartZero'
 *    '<S60>/DebounceStartZero1'
 *    '<S61>/DebounceStartZero'
 *    '<S61>/DebounceStartZero1'
 *    '<S62>/DebounceStartZero'
 *    '<S62>/DebounceStartZero1'
 *    '<S63>/DebounceStartZero'
 *    ...
 */
void EACT_DebounceStartZero(boolean_T rtu_Signal, uint16_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_EACT_T *localB,
  DW_DebounceStartZero_EACT_T *localDW)
{
  boolean_T rtb_RelationalOperator_p2;
  boolean_T rtb_RelationalOperator_de;
  uint32_T rtb_Switch2_dl;
  uint32_T rtb_Switch2_kh;
  if (localDW->StateName_a) {
    rtb_Switch2_dl = 0U;
  } else {
    rtb_Switch2_dl = localDW->StateName_i;
  }

  if (rtu_Signal) {
    rtb_Switch2_dl += rtu_FaultStep;
  } else if (rtb_Switch2_dl >= rtu_FaultStep) {
    rtb_Switch2_dl -= rtu_FaultStep;
  } else {
    rtb_Switch2_dl = 0U;
  }

  rtb_RelationalOperator_p2 = (rtb_Switch2_dl > rtu_Hearl2Fault);
  if (localDW->StateName_n) {
    rtb_Switch2_kh = 0U;
  } else {
    rtb_Switch2_kh = localDW->StateName_ir;
  }

  if (!rtu_Signal) {
    rtb_Switch2_kh += rtu_FaultStep;
  } else if (rtb_Switch2_kh >= rtu_FaultStep) {
    rtb_Switch2_kh -= rtu_FaultStep;
  } else {
    rtb_Switch2_kh = 0U;
  }

  rtb_RelationalOperator_de = (rtb_Switch2_kh > rtu_Hearl2Fault);
  if (localB->Switch == 0.0F) {
    if (rtb_RelationalOperator_p2) {
      localB->Switch = 1.0F;
    } else {
      localB->Switch = 0.0F;
    }
  } else {
    if (rtb_RelationalOperator_de) {
      localB->Switch = 0.0F;
    }
  }

  localDW->StateName_a = rtb_RelationalOperator_p2;
  localDW->StateName_i = rtb_Switch2_dl;
  localDW->StateName_n = rtb_RelationalOperator_de;
  localDW->StateName_ir = rtb_Switch2_kh;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EACT_10ms_at_outport_1' */
void EACT_10ms(void)
{
  boolean_T rtb_RelationalOperator1_d;
  uint16_T rtb_Init;
  real32_T rtb_Switch;
  boolean_T rtb_Switch_ap;
  boolean_T rtb_Merge8;
  boolean_T rtb_Switch_k;
  boolean_T rtb_Merge2;
  boolean_T rtb_Switch_iv;
  boolean_T rtb_Merge6;
  boolean_T rtb_Switch_dd;
  boolean_T rtb_GbEHVS_PACKAToHVSPCtr_flg;
  boolean_T rtb_Switch_dh;
  boolean_T rtb_Merge12;
  boolean_T rtb_Switch_d;
  boolean_T rtb_Merge;
  boolean_T rtb_Switch_l;
  boolean_T rtb_Merge4;
  uint32_T rtb_Switch2;
  uint32_T rtb_Switch2_i;
  uint8_T rtb_Merge8_0;
  EACT_DebounceStartZero((get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GeEBCR_BMSAHVSysStat_enum() == (int32_T)
                       Enum_EBCRHVSystemStatus_Standby) &&
    (get_GeEBCR_BMSBHVSysStat_enum() == (int32_T)Enum_EBCRHVSystemStatus_Standby),
    CcEACT_DelayTime3000_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero,
    &EACT_DW.DebounceStartZero);
  rtb_RelationalOperator1_d = (get_GbEMSM_24VSelfCheckSuccess_flg() ==
    ((boolean_T)ASWTYPE_FALSE));
  if (!get_GbEMSM_12VSelfCheckSuccess_flg()) {
    EACT_DebounceStartZero((EACT_DW.StateName_o == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_l,
      &EACT_DW.DebounceStartZero_l);
    EACT_DebounceStartZero((EACT_DW.StateName_o == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_cr,
      &EACT_DW.DebounceStartZero1_cr);
    if (EACT_B.DebounceStartZero_l.Switch != 0.0F) {
      rtb_Switch_ap = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_cr.Switch != 0.0F) {
      rtb_Switch_ap = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_ap = EACT_DW.StateName_k;
    }

    EACT_DebounceStartZero((EACT_DW.StateName_cu == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_g,
      &EACT_DW.DebounceStartZero_g);
    EACT_DebounceStartZero((EACT_DW.StateName_cu == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_a,
      &EACT_DW.DebounceStartZero1_a);
    if (EACT_B.DebounceStartZero_g.Switch != 0.0F) {
      rtb_Switch_k = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_a.Switch != 0.0F) {
      rtb_Switch_k = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_k = EACT_DW.StateName_l;
    }

    EACT_DebounceStartZero((EACT_DW.StateName_a == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_lb,
      &EACT_DW.DebounceStartZero_lb);
    EACT_DebounceStartZero((EACT_DW.StateName_a == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_p,
      &EACT_DW.DebounceStartZero1_p);
    if (EACT_B.DebounceStartZero_lb.Switch != 0.0F) {
      rtb_Switch_iv = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_p.Switch != 0.0F) {
      rtb_Switch_iv = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_iv = EACT_DW.StateName_hy;
    }

    rtb_Merge8 = rtb_Switch_ap;
    rtb_Merge2 = rtb_Switch_k;
    rtb_Merge6 = rtb_Switch_iv;
    EACT_DebounceStartZero((EACT_DW.StateName_j == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_ea,
      &EACT_DW.DebounceStartZero_ea);
    EACT_DebounceStartZero((EACT_DW.StateName_j == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_m,
      &EACT_DW.DebounceStartZero1_m);
    if (EACT_B.DebounceStartZero_ea.Switch != 0.0F) {
      rtb_Switch_dd = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_m.Switch != 0.0F) {
      rtb_Switch_dd = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_dd = EACT_DW.StateName_fx;
    }

    rtb_GbEHVS_PACKAToHVSPCtr_flg = rtb_Switch_dd;
    EACT_DebounceStartZero((EACT_DW.StateName_l3 == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_jo,
      &EACT_DW.DebounceStartZero_jo);
    EACT_DebounceStartZero((EACT_DW.StateName_l3 == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_c0,
      &EACT_DW.DebounceStartZero1_c0);
    if (EACT_B.DebounceStartZero_jo.Switch != 0.0F) {
      rtb_Switch_dh = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_c0.Switch != 0.0F) {
      rtb_Switch_dh = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_dh = EACT_DW.StateName_h0;
    }

    rtb_Merge12 = rtb_Switch_dh;
    EACT_DebounceStartZero(get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)
      ASWTYPE_TRUE), CcEACT_DelayTime50_ms, EACT_RUNTIME_MS,
      &EACT_B.DebounceStartZero_h, &EACT_DW.DebounceStartZero_h);
    EACT_DebounceStartZero((get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)
      ASWTYPE_FALSE)) && (EACT_DW.StateName_a2 == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_j,
      &EACT_DW.DebounceStartZero1_j);
    if (EACT_B.DebounceStartZero_h.Switch != 0.0F) {
      rtb_Switch_d = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_j.Switch != 0.0F) {
      rtb_Switch_d = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_d = EACT_DW.StateName_n;
    }

    rtb_Merge = rtb_Switch_d;
    EACT_DebounceStartZero((EACT_DW.StateName_gl == ((boolean_T)ASWTYPE_TRUE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_a,
      &EACT_DW.DebounceStartZero_a);
    EACT_DebounceStartZero((EACT_DW.StateName_gl == ((boolean_T)ASWTYPE_FALSE)) &&
      (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
      CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_e,
      &EACT_DW.DebounceStartZero1_e);
    if (EACT_B.DebounceStartZero_a.Switch != 0.0F) {
      rtb_Switch_l = ((boolean_T)ASWTYPE_TRUE);
    } else if (EACT_B.DebounceStartZero1_e.Switch != 0.0F) {
      rtb_Switch_l = ((boolean_T)ASWTYPE_FALSE);
    } else {
      rtb_Switch_l = EACT_DW.StateName_m;
    }

    rtb_Merge4 = rtb_Switch_l;
    EACT_DW.StateName_o = rtb_Switch_iv;
    EACT_DW.StateName_k = rtb_Switch_ap;
    EACT_DW.StateName_cu = rtb_Switch_d;
    EACT_DW.StateName_l = rtb_Switch_k;
    EACT_DW.StateName_a = rtb_Switch_l;
    EACT_DW.StateName_hy = rtb_Switch_iv;
    EACT_DW.StateName_j = rtb_Switch_ap;
    EACT_DW.StateName_fx = rtb_Switch_dd;
    EACT_DW.StateName_l3 = rtb_Switch_dd;
    EACT_DW.StateName_h0 = rtb_Switch_dh;
    EACT_DW.StateName_a2 = rtb_Switch_dh;
    EACT_DW.StateName_n = rtb_Switch_d;
    EACT_DW.StateName_gl = rtb_Switch_k;
    EACT_DW.StateName_m = rtb_Switch_l;
  } else {
    rtb_Merge = get_GbECTC_ReChrgAPCtrCmd_flg();
    rtb_Switch_d = get_GbECTC_ReChrgANCtrCmd_flg();
    rtb_Merge2 = get_GbECTC_CChrgAPCtrCmd_flg();
    rtb_Switch_k = get_GbECTC_CChrgANCtrCmd_flg();
    rtb_Merge4 = get_GbECTC_ReChrgBPCtrCmd_flg();
    rtb_Switch_l = get_GbECTC_ReChrgBNCtrCmd_flg();
    rtb_Merge6 = get_GbECTC_CChrgBPCtrCmd_flg();
    rtb_Switch_iv = get_GbECTC_CChrgBNCtrCmd_flg();
    rtb_Merge8 = get_GbECTC_BCChrgPCtrCmd_flg();
    rtb_Switch_ap = get_GbECTC_BCChrgNCtrCmd_flg();
    rtb_GbEHVS_PACKAToHVSPCtr_flg = get_GbEHVS_PACKAToHVSPCtr_flg();
    rtb_Switch_dd = get_GbEHVS_PACKAToHVSNCtr_flg();
    rtb_Merge12 = get_GbEHVS_PACKBToHVSPCtr_flg();
    rtb_Switch_dh = get_GbEHVS_PACKBToHVSNCtr_flg();
  }

  if (CbEACT_BCChrgNegCtrCmdOvrSwt_flg) {
    set_GbEACT_BCChrgNegCtrCmd_flg(CbEACT_BCChrgNegCtrCmdOvr_flg);
  } else {
    set_GbEACT_BCChrgNegCtrCmd_flg(rtb_Switch_ap);
  }

  if (CbEACT_BCChrgPosCtrCmdOvrSwt_flg) {
    set_GbEACT_BCChrgPosCtrCmd_flg(CbEACT_BCChrgPosCtrCmdOvr_flg);
  } else {
    set_GbEACT_BCChrgPosCtrCmd_flg(rtb_Merge8);
  }

  if (CbEACT_CChrgANegCtrCmdOvrSwt_flg) {
    set_GbEACT_CChrgANegCtrCmd_flg(CbEACT_CChrgANegCtrCmdOvr_flg);
  } else {
    set_GbEACT_CChrgANegCtrCmd_flg(rtb_Switch_k);
  }

  if (CbEACT_CChrgAPosCtrCmdOvrSwt_flg) {
    set_GbEACT_CChrgAPosCtrCmd_flg(CbEACT_CChrgAPosCtrCmdOvr_flg);
  } else {
    set_GbEACT_CChrgAPosCtrCmd_flg(rtb_Merge2);
  }

  if (CbEACT_CChrgBNegCtrCmdOvrSwt_flg) {
    set_GbEACT_CChrgBNegCtrCmd_flg(CbEACT_CChrgBNegCtrCmdOvr_flg);
  } else {
    set_GbEACT_CChrgBNegCtrCmd_flg(rtb_Switch_iv);
  }

  if (CbEACT_CChrgBPosCtrCmdOvrSwt_flg) {
    set_GbEACT_CChrgBPosCtrCmd_flg(CbEACT_CChrgBPosCtrCmdOvr_flg);
  } else {
    set_GbEACT_CChrgBPosCtrCmd_flg(rtb_Merge6);
  }

  if (CbEACT_PACKAToHVSNCtrOvrSwt_flg) {
    set_GbEACT_PACKAToHVSNCtr_flg(CbEACT_PACKAToHVSNCtrOvr_flg);
  } else {
    set_GbEACT_PACKAToHVSNCtr_flg(rtb_Switch_dd);
  }

  if (CbEACT_PACKAToHVSPCtrOvrSwt_flg) {
    set_GbEACT_PACKAToHVSPCtr_flg(CbEACT_PACKAToHVSPCtrOvr_flg);
  } else {
    set_GbEACT_PACKAToHVSPCtr_flg(rtb_GbEHVS_PACKAToHVSPCtr_flg);
  }

  if (CbEACT_PACKBToHVSNCtrOvrSwt_flg) {
    set_GbEACT_PACKBToHVSNCtr_flg(CbEACT_PACKBToHVSNCtrOvr_flg);
  } else {
    set_GbEACT_PACKBToHVSNCtr_flg(rtb_Switch_dh);
  }

  if (CbEACT_PACKBToHVSPCtrOvrSwt_flg) {
    set_GbEACT_PACKBToHVSPCtr_flg(CbEACT_PACKBToHVSPCtrOvr_flg);
  } else {
    set_GbEACT_PACKBToHVSPCtr_flg(rtb_Merge12);
  }

  if (CbEACT_ReChrgANegCtrCmdOvrSwt_flg) {
    set_GbEACT_ReChrgANegCtrCmd_flg(CbEACT_ReChrgANegCtrCmdOvr_flg);
  } else {
    set_GbEACT_ReChrgANegCtrCmd_flg(rtb_Switch_d);
  }

  if (CbEACT_ReChrgAPosCtrCmdOvrSwt_flg) {
    set_GbEACT_ReChrgAPosCtrCmd_flg(CbEACT_ReChrgAPosCtrCmdOvr_flg);
  } else {
    set_GbEACT_ReChrgAPosCtrCmd_flg(rtb_Merge);
  }

  if (CbEACT_ReChrgBNegCtrCmdOvrSwt_flg) {
    set_GbEACT_ReChrgBNegCtrCmd_flg(CbEACT_ReChrgBNegCtrCmdOvr_flg);
  } else {
    set_GbEACT_ReChrgBNegCtrCmd_flg(rtb_Switch_l);
  }

  if (CbEACT_ReChrgBPosCtrCmdOvrSwt_flg) {
    set_GbEACT_ReChrgBPosCtrCmd_flg(CbEACT_ReChrgBPosCtrCmdOvr_flg);
  } else {
    set_GbEACT_ReChrgBPosCtrCmd_flg(rtb_Merge4);
  }

  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
    (get_GbEACT_PACKBToHVSPCtr_flg() == ((boolean_T)ASWTYPE_TRUE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1,
    &EACT_DW.DebounceStartZero1);
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)) &&
    (get_GbEACT_PACKBToHVSPCtr_flg() == ((boolean_T)ASWTYPE_FALSE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero2,
    &EACT_DW.DebounceStartZero2);
  if (EACT_B.DebounceStartZero1.Switch != 0.0F) {
    rtb_Merge = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACT_B.DebounceStartZero2.Switch != 0.0F) {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
  } else if (EACT_B.DebounceStartZero.Switch != 0.0F) {
    rtb_Merge = ((boolean_T)ASWTYPE_FALSE);
  } else if ((get_GbEBSW_T645ThreePhaseOnline_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
               ASWTYPE_TRUE))) {
    rtb_Merge = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Merge = EACT_DW.StateName_h;
  }

  if (CbEACT_ACCtrCmdOvrSwt_flg) {
    set_GbEACT_ACCtrCmd_flg(CbEACT_ACCtrCmdOvr_flg);
  } else {
    set_GbEACT_ACCtrCmd_flg(rtb_Merge);
  }

  rtb_RelationalOperator1_d = (get_GbEMSM_24VSelfCheckSuccess_flg() ==
    ((boolean_T)ASWTYPE_FALSE));
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
    (get_GbEACT_ACCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_k,
    &EACT_DW.DebounceStartZero1_k);
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)) &&
    (get_GbEACT_ACCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero2_i,
    &EACT_DW.DebounceStartZero2_i);
  EACT_DebounceStartZero(get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE), CcEACT_DelayTime50_ms, EACT_RUNTIME_MS,
    &EACT_B.DebounceStartZero3, &EACT_DW.DebounceStartZero3);
  if (EACT_B.DebounceStartZero1_k.Switch != 0.0F) {
    rtb_Merge2 = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACT_B.DebounceStartZero2_i.Switch != 0.0F) {
    rtb_Merge2 = ((boolean_T)ASWTYPE_FALSE);
  } else if (EACT_B.DebounceStartZero3.Switch != 0.0F) {
    rtb_Merge2 = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Merge2 = EACT_DW.StateName_er;
  }

  if (CbEACT_AdvCoolFanCtrCmdOvrSwt_flg) {
    set_GbEACT_AdvCoolFanCtrCmd_flg(CbEACT_AdvCoolFanCtrCmdOvr_flg);
  } else {
    set_GbEACT_AdvCoolFanCtrCmd_flg(rtb_Merge2);
  }

  rtb_RelationalOperator1_d = (get_GbEMSM_24VSelfCheckSuccess_flg() ==
    ((boolean_T)ASWTYPE_FALSE));
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
    (get_GbEACT_AdvCoolFanCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero_j,
    &EACT_DW.DebounceStartZero_j);
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)) &&
    (get_GbEACT_AdvCoolFanCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_c,
    &EACT_DW.DebounceStartZero1_c);
  EACT_DebounceStartZero((get_GbEACT_AdvCoolFanCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcEACT_DelayTime50_ms, EACT_RUNTIME_MS,
    &EACT_B.DebounceStartZero2_a, &EACT_DW.DebounceStartZero2_a);
  if (EACT_B.DebounceStartZero_j.Switch != 0.0F) {
    rtb_Merge4 = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACT_B.DebounceStartZero1_c.Switch != 0.0F) {
    rtb_Merge4 = ((boolean_T)ASWTYPE_FALSE);
  } else if (EACT_B.DebounceStartZero2_a.Switch != 0.0F) {
    rtb_Merge4 = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Merge4 = EACT_DW.StateName_f;
  }

  if (CbEACT_AdvPowCtrCmdOvrSwt_flg) {
    set_GbEACT_AdvPowCtrCmd_flg(CbEACT_AdvPowCtrCmdOvr_flg);
  } else {
    set_GbEACT_AdvPowCtrCmd_flg(rtb_Merge4);
  }

  rtb_RelationalOperator1_d = (get_GbEMSM_24VSelfCheckSuccess_flg() ==
    ((boolean_T)ASWTYPE_FALSE));
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)) &&
    (get_GbEACT_AdvPowCtrCmd_flg() == ((boolean_T)ASWTYPE_FALSE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero1_cd,
    &EACT_DW.DebounceStartZero1_cd);
  EACT_DebounceStartZero((get_GbEACT_AdvPowCtrCmd_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)), CcEACT_DelayTime50_ms, EACT_RUNTIME_MS,
    &EACT_B.DebounceStartZero2_ag, &EACT_DW.DebounceStartZero2_ag);
  EACT_DebounceStartZero(rtb_RelationalOperator1_d &&
    (get_GbEMSM_SelfCheckCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
    (get_GbEACT_AdvPowCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)),
    CcEACT_DelayTime50_ms, EACT_RUNTIME_MS, &EACT_B.DebounceStartZero3_a,
    &EACT_DW.DebounceStartZero3_a);
  if (EACT_B.DebounceStartZero3_a.Switch != 0.0F) {
    rtb_RelationalOperator1_d = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACT_B.DebounceStartZero1_cd.Switch != 0.0F) {
    rtb_RelationalOperator1_d = ((boolean_T)ASWTYPE_FALSE);
  } else if ((get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
             && (EACT_U.GbECRH_CrashEnable_flg == ((boolean_T)ASWTYPE_TRUE))) {
    rtb_RelationalOperator1_d = ((boolean_T)ASWTYPE_FALSE);
  } else if (EACT_B.DebounceStartZero2_ag.Switch != 0.0F) {
    rtb_RelationalOperator1_d = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_RelationalOperator1_d = EACT_DW.StateName_c;
  }

  if (CbEACT_KA5CtrCmdOvrSwt_flg) {
    set_GbEACT_KA5CtrCmd_flg(CbEACT_KA5CtrCmdOvr_flg);
  } else {
    set_GbEACT_KA5CtrCmd_flg(rtb_RelationalOperator1_d);
  }

  rtb_Merge8 = ((get_GeEBIM_BMSAHVCtrCmd_enum() == EACT_OFF) &&
                (get_GeEBIM_BMSBHVCtrCmd_enum() == EACT_OFF) &&
                (get_GbEBIM_PackAAllowedReChrg_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbEBIM_PackBAllowedReChrg_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbEBIM_PackANotAllowedDisCharge_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEBIM_PackBNotAllowedDisCharge_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
    ASWTYPE_FALSE)));
  if (EACT_DW.StateName_erl) {
    rtb_Switch2 = 0U;
  } else {
    rtb_Switch2 = EACT_DW.StateName_d;
  }

  if (rtb_Merge8) {
    rtb_Switch2 += EACT_RUNTIME_MS;
  } else if (rtb_Switch2 >= EACT_RUNTIME_MS) {
    rtb_Switch2 -= EACT_RUNTIME_MS;
  } else {
    rtb_Switch2 = 0U;
  }

  rtb_Merge6 = (rtb_Switch2 > CcEACT_DelayTime3_min);
  if (EACT_DW.StateName_em) {
    rtb_Switch2_i = 0U;
  } else {
    rtb_Switch2_i = EACT_DW.StateName_e;
  }

  if (!rtb_Merge8) {
    rtb_Switch2_i += EACT_RUNTIME_MS;
  } else if (rtb_Switch2_i >= EACT_RUNTIME_MS) {
    rtb_Switch2_i -= EACT_RUNTIME_MS;
  } else {
    rtb_Switch2_i = 0U;
  }

  rtb_Merge8 = (rtb_Switch2_i > CcEACT_DelayTime3_min);
  if (EACT_DW.StateName == 0.0F) {
    if (rtb_Merge6) {
      rtb_Switch = 1.0F;
    } else {
      rtb_Switch = EACT_DW.StateName;
    }
  } else if (rtb_Merge8) {
    rtb_Switch = 0.0F;
  } else {
    rtb_Switch = EACT_DW.StateName;
  }

  EACT_DW.StateName = rtb_Switch;
  EACT_DW.StateName_erl = rtb_Merge6;
  EACT_DW.StateName_d = rtb_Switch2;
  EACT_DW.StateName_em = rtb_Merge8;
  EACT_DW.StateName_e = rtb_Switch2_i;
  rtb_Merge6 = !((boolean_T)ASWTYPE_TRUE);
  if (rtb_Merge6 || (EACT_DW.FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init = 0U;
  } else {
    rtb_Init = EACT_DW.FixPtUnitDelay1_DSTATE;
  }

  rtb_Merge8 = (rtb_Init >= CcEACT_DelayTime3000_ms);
  if (rtb_Merge6) {
    EACT_DW.FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (rtb_Merge8) {
      rtb_Merge8_0 = 0U;
    } else {
      rtb_Merge8_0 = EACT_RUNTIME_MS;
    }

    EACT_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)rtb_Merge8_0 +
      rtb_Init);
  }

  EACT_DW.FixPtUnitDelay2_DSTATE = 0U;
  if (rtb_Switch != 0.0F) {
    rtb_Merge6 = ((boolean_T)ASWTYPE_FALSE);
  } else if (rtb_Merge8) {
    rtb_Merge6 = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Merge6 = EACT_DW.StateName_g;
  }

  if (CbEACT_12VPyhSuplyCtrCmdOvrSwt_flg) {
    set_GbEACT_12VPyhSuplyCtrCmd_flg(CbEACT_12VPyhSuplyCtrCmdOvr_flg);
  } else {
    set_GbEACT_12VPyhSuplyCtrCmd_flg(rtb_Merge6);
  }

  EACT_DW.StateName_h = rtb_Merge;
  EACT_DW.StateName_er = rtb_Merge2;
  EACT_DW.StateName_f = rtb_Merge4;
  EACT_DW.StateName_c = rtb_RelationalOperator1_d;
  EACT_DW.StateName_g = rtb_Merge6;
}

/* Model initialize function */
void EACT_initialize(void)
{
  EACT_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
