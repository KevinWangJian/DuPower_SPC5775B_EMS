/*
 * File: EMSM.c
 *
 * Code generated for Simulink model 'EMSM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 14:32:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EMSM.h"
#include "EMSM_private.h"

/* Block signals (auto storage) */
B_EMSM_T EMSM_B;

/* Block states (auto storage) */
DW_EMSM_T EMSM_DW;

/* Real-time model */
RT_MODEL_EMSM_T EMSM_M_;
RT_MODEL_EMSM_T *const EMSM_M = &EMSM_M_;

/*
 * Output and update for atomic system:
 *    '<S43>/DebounceStartZero'
 *    '<S6>/DebounceStartZero'
 *    '<S6>/DebounceStartZero1'
 */
void EMSM_DebounceStartZero(boolean_T rtu_Signal, uint32_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_EMSM_T *localB,
  DW_DebounceStartZero_EMSM_T *localDW)
{
  boolean_T rtb_RelationalOperator_nj;
  boolean_T rtb_RelationalOperator_d;
  uint32_T rtb_Switch2_b;
  uint32_T rtb_Switch2_ld;
  if (localDW->StateName_jv) {
    rtb_Switch2_b = 0U;
  } else {
    rtb_Switch2_b = localDW->StateName_j;
  }

  if (rtu_Signal) {
    rtb_Switch2_b += rtu_FaultStep;
  } else if (rtb_Switch2_b >= rtu_FaultStep) {
    rtb_Switch2_b -= rtu_FaultStep;
  } else {
    rtb_Switch2_b = 0U;
  }

  rtb_RelationalOperator_nj = (rtb_Switch2_b > rtu_Hearl2Fault);
  if (localDW->StateName_n) {
    rtb_Switch2_ld = 0U;
  } else {
    rtb_Switch2_ld = localDW->StateName_c;
  }

  if (!rtu_Signal) {
    rtb_Switch2_ld += rtu_FaultStep;
  } else if (rtb_Switch2_ld >= rtu_FaultStep) {
    rtb_Switch2_ld -= rtu_FaultStep;
  } else {
    rtb_Switch2_ld = 0U;
  }

  rtb_RelationalOperator_d = (rtb_Switch2_ld > rtu_Hearl2Fault);
  if (localB->Switch == 0.0F) {
    if (rtb_RelationalOperator_nj) {
      localB->Switch = 1.0F;
    } else {
      localB->Switch = 0.0F;
    }
  } else {
    if (rtb_RelationalOperator_d) {
      localB->Switch = 0.0F;
    }
  }

  localDW->StateName_jv = rtb_RelationalOperator_nj;
  localDW->StateName_j = rtb_Switch2_b;
  localDW->StateName_n = rtb_RelationalOperator_d;
  localDW->StateName_c = rtb_Switch2_ld;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EMSM_10ms_at_outport_1' */
void EMSM_10ms(void)
{
  boolean_T rtb_RelationalOperator_ab;
  boolean_T rtb_LogicalOperator1_f;
  boolean_T rtb_LogicalOperator_ok;
  boolean_T rtb_Switch_fs;
  boolean_T rtb_RelationalOperator_l;
  boolean_T rtb_LogicalOperator1_kk;
  boolean_T rtb_LogicalOperator_ku;
  uint16_T rtb_Init_h;
  boolean_T rtb_RelationalOperator_j;
  boolean_T rtb_RelationalOperator_n;
  uint32_T rtb_Switch2_i;
  uint32_T rtb_Switch2_o;
  boolean_T rtb_Switch_fz;
  uint8_T rtb_RelationalOperator_h;
  rtb_LogicalOperator_ku = !((boolean_T)ASWTYPE_TRUE);
  if (rtb_LogicalOperator_ku || (EMSM_DW.FixPtUnitDelay2_DSTATE_n != 0)) {
    rtb_Init_h = 0U;
  } else {
    rtb_Init_h = EMSM_DW.FixPtUnitDelay1_DSTATE_a;
  }

  rtb_RelationalOperator_ab = (rtb_Init_h >= CcEMSM_DelayTime2000_ms);
  if (rtb_LogicalOperator_ku) {
    EMSM_DW.FixPtUnitDelay1_DSTATE_a = 0U;
  } else {
    if (rtb_RelationalOperator_ab) {
      rtb_RelationalOperator_h = 0U;
    } else {
      rtb_RelationalOperator_h = EMSM_RUNTIME_MS;
    }

    EMSM_DW.FixPtUnitDelay1_DSTATE_a = (uint16_T)((uint32_T)
      rtb_RelationalOperator_h + rtb_Init_h);
  }

  EMSM_DW.FixPtUnitDelay2_DSTATE_n = 0U;
  rtb_LogicalOperator_ku = (((get_GbEBSW_BSWInitFinish_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && rtb_RelationalOperator_ab && (get_GbEDEC_FunFlt_flg() ==
    ((boolean_T)ASWTYPE_FALSE))) || EMSM_DW.StateName_o);
  if (CbEMSM_EMSCheckSuccessOvrSwt_flg) {
    set_GbEMSM_EMSCheckSuccess_flg(CbEMSM_EMSCheckSuccessOvr_flg);
  } else {
    set_GbEMSM_EMSCheckSuccess_flg(rtb_LogicalOperator_ku);
  }

  rtb_RelationalOperator_ab = (((get_GbEMSM_EMSCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GeEBCR_BMSAHVSysStat_enum() ==
                       EMSM_ConstB.DataTypeConversion_m) &&
    (get_GeEBCR_BMSBHVSysStat_enum() == EMSM_ConstB.DataTypeConversion1_j) &&
    ((get_GeECCR_CCU1CCUSTATE_enum() == EMSM_ConstB.DataTypeConversion2_l) ||
     (get_GeECCR_CCU2CCUSTATE_enum() == EMSM_ConstB.DataTypeConversion3_a)) &&
    (get_GeEBSW_TPSTATE_enum() == EMSM_ConstB.DataTypeConversion4)) ||
    EMSM_DW.StateName_i);
  if (CbEMSM_ECUCheckSuccessOvrSwt_flg) {
    set_GbEMSM_ECUCheckSuccess_flg(CbEMSM_ECUCheckSuccessOvr_flg);
  } else {
    set_GbEMSM_ECUCheckSuccess_flg(rtb_RelationalOperator_ab);
  }

  rtb_LogicalOperator1_f = ((EMSM_DW.StateName != 0.0F) || EMSM_DW.StateName_c);
  rtb_LogicalOperator_ok = ((get_GbEMSM_ECUCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEDEC_FunFlt_flg() == ((boolean_T)ASWTYPE_FALSE)) &&
    (rtb_LogicalOperator1_f == ((boolean_T)ASWTYPE_TRUE)));
  if (EMSM_DW.StateName_gd) {
    rtb_Switch2_i = 0U;
  } else {
    rtb_Switch2_i = EMSM_DW.StateName_d;
  }

  if (rtb_LogicalOperator_ok) {
    rtb_Switch2_i += EMSM_RUNTIME_MS;
  } else if (rtb_Switch2_i >= EMSM_RUNTIME_MS) {
    rtb_Switch2_i -= EMSM_RUNTIME_MS;
  } else {
    rtb_Switch2_i = 0U;
  }

  rtb_RelationalOperator_j = (rtb_Switch2_i > CcEMSM_DelayTime5000_ms);
  if (EMSM_DW.StateName_dg) {
    rtb_Switch2_o = 0U;
  } else {
    rtb_Switch2_o = EMSM_DW.StateName_k;
  }

  if (!rtb_LogicalOperator_ok) {
    rtb_Switch2_o += EMSM_RUNTIME_MS;
  } else if (rtb_Switch2_o >= EMSM_RUNTIME_MS) {
    rtb_Switch2_o -= EMSM_RUNTIME_MS;
  } else {
    rtb_Switch2_o = 0U;
  }

  rtb_LogicalOperator_ok = (rtb_Switch2_o > CcEMSM_DelayTime5000_ms);
  if (!EMSM_DW.StateName_kb) {
    if (rtb_RelationalOperator_j) {
      rtb_Switch_fs = true;
    } else {
      rtb_Switch_fs = EMSM_DW.StateName_kb;
    }
  } else if (rtb_LogicalOperator_ok) {
    rtb_Switch_fs = false;
  } else {
    rtb_Switch_fs = EMSM_DW.StateName_kb;
  }

  EMSM_DW.StateName_kb = rtb_Switch_fs;
  EMSM_DW.StateName_gd = rtb_RelationalOperator_j;
  EMSM_DW.StateName_d = rtb_Switch2_i;
  EMSM_DW.StateName_dg = rtb_LogicalOperator_ok;
  EMSM_DW.StateName_k = rtb_Switch2_o;
  rtb_RelationalOperator_j = (rtb_Switch_fs || EMSM_DW.StateName_gr);
  if (CbEMSM_12VSelfCheckSuccessOvrSwt_flg) {
    set_GbEMSM_12VSelfCheckSuccess_flg(CbEMSM_12VSelfCheckSuccessOvr_flg);
  } else {
    set_GbEMSM_12VSelfCheckSuccess_flg(rtb_RelationalOperator_j);
  }

  rtb_LogicalOperator_ok = (EMSM_DW.StateName_or || EMSM_DW.StateName_k3);
  EMSM_DebounceStartZero((get_GbEMSM_ECUCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (rtb_LogicalOperator_ok == ((boolean_T)ASWTYPE_TRUE)) &&
    (rtb_LogicalOperator1_f == ((boolean_T)ASWTYPE_FALSE)),
    CcEMSM_DelayTime5000_ms, EMSM_RUNTIME_MS, &EMSM_B.DebounceStartZero_e,
    &EMSM_DW.DebounceStartZero_e);
  rtb_Switch_fs = !((boolean_T)ASWTYPE_TRUE);
  if (rtb_Switch_fs || (EMSM_DW.FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Switch2_i = 0U;
  } else {
    rtb_Switch2_i = EMSM_DW.FixPtUnitDelay1_DSTATE;
  }

  rtb_RelationalOperator_l = (rtb_Switch2_i >= CcEMSM_DelayTime5000_ms);
  if (rtb_Switch_fs) {
    EMSM_DW.FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (rtb_RelationalOperator_l) {
      rtb_RelationalOperator_h = 0U;
    } else {
      rtb_RelationalOperator_h = EMSM_RUNTIME_MS;
    }

    EMSM_DW.FixPtUnitDelay1_DSTATE = rtb_RelationalOperator_h + rtb_Switch2_i;
  }

  EMSM_DW.FixPtUnitDelay2_DSTATE = 0U;
  rtb_Switch_fs = ((get_GbEMSM_ECUCheckSuccess_flg() == ((boolean_T)ASWTYPE_TRUE))
                   && (get_GeEBCR_BMSAMainPosCntStat_enum() ==
                       EMSM_ConstB.DataTypeConversion_g) &&
                   (get_GeEBCR_BMSAMainNegCntStat_enum() ==
                    EMSM_ConstB.DataTypeConversion1_i) &&
                   (get_GeEBCR_BMSBMainPosCntStat_enum() ==
                    EMSM_ConstB.DataTypeConversion2_a) &&
                   (get_GeEBCR_BMSBMainNegCntStat_enum() ==
                    EMSM_ConstB.DataTypeConversion3_g) &&
                   (get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && rtb_RelationalOperator_l && (rtb_LogicalOperator_ok ==
    ((boolean_T)ASWTYPE_FALSE)));
  if (EMSM_B.DebounceStartZero_e.Switch != 0.0F) {
    rtb_RelationalOperator_l = ((boolean_T)ASWTYPE_FALSE);
  } else if (rtb_Switch_fs) {
    rtb_RelationalOperator_l = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_RelationalOperator_l = EMSM_DW.StateName_jl;
  }

  if (CbEMSM_SelfCheckCtrCmdOvrSwt_flg) {
    set_GbEMSM_SelfCheckCtrCmd_flg(CbEMSM_SelfCheckCtrCmdOvr_flg);
  } else {
    set_GbEMSM_SelfCheckCtrCmd_flg(rtb_RelationalOperator_l);
  }

  rtb_LogicalOperator1_kk = ((get_GbEBSW_Door1CONAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GbEBSW_Door2CONAuxIn_flg() == ((boolean_T)
    ASWTYPE_FALSE)));
  if (EMSM_DW.StateName_e) {
    rtb_Switch2_i = 0U;
  } else {
    rtb_Switch2_i = EMSM_DW.StateName_g;
  }

  if (rtb_LogicalOperator1_kk) {
    rtb_Switch2_i += EMSM_RUNTIME_MS;
  } else if (rtb_Switch2_i >= EMSM_RUNTIME_MS) {
    rtb_Switch2_i -= EMSM_RUNTIME_MS;
  } else {
    rtb_Switch2_i = 0U;
  }

  rtb_RelationalOperator_n = (rtb_Switch2_i > CcEMSM_DelayTime2000_ms);
  if (EMSM_DW.StateName_m) {
    rtb_Switch2_o = 0U;
  } else {
    rtb_Switch2_o = EMSM_DW.StateName_f;
  }

  if (!rtb_LogicalOperator1_kk) {
    rtb_Switch2_o += EMSM_RUNTIME_MS;
  } else if (rtb_Switch2_o >= EMSM_RUNTIME_MS) {
    rtb_Switch2_o -= EMSM_RUNTIME_MS;
  } else {
    rtb_Switch2_o = 0U;
  }

  rtb_LogicalOperator1_kk = (rtb_Switch2_o > CcEMSM_DelayTime2000_ms);
  if (!EMSM_DW.StateName_h) {
    if (rtb_RelationalOperator_n) {
      rtb_Switch_fz = true;
    } else {
      rtb_Switch_fz = EMSM_DW.StateName_h;
    }
  } else if (rtb_LogicalOperator1_kk) {
    rtb_Switch_fz = false;
  } else {
    rtb_Switch_fz = EMSM_DW.StateName_h;
  }

  EMSM_DW.StateName_h = rtb_Switch_fz;
  EMSM_DW.StateName_e = rtb_RelationalOperator_n;
  EMSM_DW.StateName_g = rtb_Switch2_i;
  EMSM_DW.StateName_m = rtb_LogicalOperator1_kk;
  EMSM_DW.StateName_f = rtb_Switch2_o;
  if (CbEMSM_SafeCheckSuccessOvrSwt_flg) {
    set_GbEMSM_SafeCheckSuccess_flg(CbEMSM_SafeCheckSuccessOvr_flg);
  } else {
    set_GbEMSM_SafeCheckSuccess_flg(rtb_Switch_fz);
  }

  EMSM_DW.StateName_o = rtb_LogicalOperator_ku;
  EMSM_DW.StateName_i = rtb_RelationalOperator_ab;
  EMSM_DW.StateName = EMSM_B.DebounceStartZero_e.Switch;
  EMSM_DW.StateName_c = rtb_LogicalOperator1_f;
  EMSM_DW.StateName_gr = rtb_RelationalOperator_j;
  EMSM_DW.StateName_or = rtb_Switch_fs;
  EMSM_DW.StateName_k3 = rtb_LogicalOperator_ok;
  EMSM_DW.StateName_jl = rtb_RelationalOperator_l;
  if (CbEMSM_24VSelfCheckSuccessOvrSwt_flg) {
    rtb_LogicalOperator_ku = CbEMSM_24VSelfCheckSuccessOvr_flg;
  } else {
    rtb_LogicalOperator_ku = ((get_GbEMSM_12VSelfCheckSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEEPM_Power24VFaultLevel_enum() ==
      EMSM_ConstB.DataTypeConversion) && (get_GeEHCR_HCUSystemMode_enum() ==
      EMSM_ConstB.DataTypeConversion1) && ((get_GeEBCR_BMSAHVSysStat_enum() ==
      EMSM_ConstB.DataTypeConversion2) || (get_GeEBCR_BMSBHVSysStat_enum() ==
      EMSM_ConstB.DataTypeConversion3)));
  }

  set_GbEMSM_24VSelfCheckSuccess_flg((rtb_LogicalOperator_ku ||
    EMSM_DW.StateName_j));
  EMSM_DebounceStartZero((get_GbEMSM_12VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_FALSE)) || (get_GbEMSM_24VSelfCheckSuccess_flg() == ((boolean_T)
    ASWTYPE_FALSE)), CcEMSM_DelayTime30_min, EMSM_RUNTIME_MS,
    &EMSM_B.DebounceStartZero, &EMSM_DW.DebounceStartZero);
  EMSM_DebounceStartZero(get_GbEBSW_KA4AuxIn_flg() == ((boolean_T)ASWTYPE_FALSE),
    CcEMSM_DelayTime60000_ms, EMSM_RUNTIME_MS, &EMSM_B.DebounceStartZero1,
    &EMSM_DW.DebounceStartZero1);
  if (CbEMSM_SleepModeEnableOvrSwt_flg) {
    set_GbEMSM_SleepModeEnable_flg(CbEMSM_SleepModeEnableOvr_flg);
  } else {
    set_GbEMSM_SleepModeEnable_flg(((EMSM_B.DebounceStartZero.Switch != 0.0F) ||
      (EMSM_B.DebounceStartZero1.Switch != 0.0F)));
  }

  EMSM_DW.StateName_j = get_GbEMSM_24VSelfCheckSuccess_flg();
}

/* Model initialize function */
void EMSM_initialize(void)
{
  EMSM_DW.FixPtUnitDelay2_DSTATE_n = 1U;
  EMSM_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
