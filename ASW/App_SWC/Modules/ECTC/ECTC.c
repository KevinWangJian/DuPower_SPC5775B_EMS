/*
 * File: ECTC.c
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

/* Named constants for Chart: '<S9>/BCChrgCtrAMode' */
#define ECTC_IN_Offline                ((uint8_T)1U)
#define ECTC_IN_Online                 ((uint8_T)2U)
#define ECTC_IN_Prechrg                ((uint8_T)3U)
#define ECTC_IN_Preshut                ((uint8_T)4U)
#define ECTC_IN_Shutdown               ((uint8_T)5U)

/* Block signals (auto storage) */
B_ECTC_T ECTC_B;

/* Block states (auto storage) */
DW_ECTC_T ECTC_DW;

/* Real-time model */
RT_MODEL_ECTC_T ECTC_M_;
RT_MODEL_ECTC_T *const ECTC_M = &ECTC_M_;

/*
 * Initial conditions for atomic system:
 *    '<S25>/DebounceStartZero'
 *    '<S25>/DebounceStartZero1'
 *    '<S26>/DebounceStartZero'
 *    '<S194>/DebounceStartZero'
 *    '<S194>/DebounceStartZero1'
 *    '<S195>/DebounceStartZero'
 *    '<S260>/DebounceStartZero'
 *    '<S261>/DebounceStartZero'
 *    '<S329>/DebounceStartZero'
 *    '<S330>/DebounceStartZero'
 *    ...
 */
void ECTC_DebounceStartZero_Init(DW_DebounceStartZero_ECTC_T *localDW)
{
  localDW->StateName_h = false;
  localDW->StateName_e = false;
  localDW->StateName = 0U;
  localDW->StateName_m = false;
  localDW->StateName_f = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S25>/DebounceStartZero'
 *    '<S25>/DebounceStartZero1'
 *    '<S26>/DebounceStartZero'
 *    '<S194>/DebounceStartZero'
 *    '<S194>/DebounceStartZero1'
 *    '<S195>/DebounceStartZero'
 *    '<S260>/DebounceStartZero'
 *    '<S261>/DebounceStartZero'
 *    '<S329>/DebounceStartZero'
 *    '<S330>/DebounceStartZero'
 *    ...
 */
void ECTC_DebounceStartZero(boolean_T rtu_Signal, uint16_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_ECTC_T *localB,
  DW_DebounceStartZero_ECTC_T *localDW)
{
  boolean_T rtb_RelationalOperator_io;
  boolean_T rtb_RelationalOperator_nn;
  uint32_T rtb_Switch2;
  uint32_T rtb_Switch2_bw;
  if (localDW->StateName_e) {
    rtb_Switch2 = 0U;
  } else {
    rtb_Switch2 = localDW->StateName;
  }

  if (rtu_Signal) {
    rtb_Switch2 += rtu_FaultStep;
  } else if (rtb_Switch2 >= rtu_FaultStep) {
    rtb_Switch2 -= rtu_FaultStep;
  } else {
    rtb_Switch2 = 0U;
  }

  rtb_RelationalOperator_io = (rtb_Switch2 > rtu_Hearl2Fault);
  if (localDW->StateName_m) {
    rtb_Switch2_bw = 0U;
  } else {
    rtb_Switch2_bw = localDW->StateName_f;
  }

  if (!rtu_Signal) {
    rtb_Switch2_bw += rtu_FaultStep;
  } else if (rtb_Switch2_bw >= rtu_FaultStep) {
    rtb_Switch2_bw -= rtu_FaultStep;
  } else {
    rtb_Switch2_bw = 0U;
  }

  rtb_RelationalOperator_nn = (rtb_Switch2_bw > rtu_Hearl2Fault);
  if (!localDW->StateName_h) {
    if (rtb_RelationalOperator_io) {
      localB->Switch = true;
    } else {
      localB->Switch = localDW->StateName_h;
    }
  } else if (rtb_RelationalOperator_nn) {
    localB->Switch = false;
  } else {
    localB->Switch = localDW->StateName_h;
  }

  localDW->StateName_h = localB->Switch;
  localDW->StateName_e = rtb_RelationalOperator_io;
  localDW->StateName = rtb_Switch2;
  localDW->StateName_m = rtb_RelationalOperator_nn;
  localDW->StateName_f = rtb_Switch2_bw;
}

/*
 * Initial conditions for atomic system:
 *    '<S61>/DebounceStartZero'
 *    '<S62>/DebounceStartZero'
 *    '<S63>/DebounceStartZero'
 *    '<S64>/DebounceStartZero'
 *    '<S138>/DebounceStartZero'
 *    '<S139>/DebounceStartZero'
 *    '<S140>/DebounceStartZero'
 *    '<S141>/DebounceStartZero'
 *    '<S285>/DebounceStartZero'
 *    '<S286>/DebounceStartZero'
 *    ...
 */
void ECTC_DebounceStartZero_e_Init(DW_DebounceStartZero_ECTC_n_T *localDW)
{
  localDW->StateName = 0.0F;
  localDW->StateName_g = false;
  localDW->StateName_e = 0U;
  localDW->StateName_h = false;
  localDW->StateName_c = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S61>/DebounceStartZero'
 *    '<S62>/DebounceStartZero'
 *    '<S63>/DebounceStartZero'
 *    '<S64>/DebounceStartZero'
 *    '<S138>/DebounceStartZero'
 *    '<S139>/DebounceStartZero'
 *    '<S140>/DebounceStartZero'
 *    '<S141>/DebounceStartZero'
 *    '<S285>/DebounceStartZero'
 *    '<S286>/DebounceStartZero'
 *    ...
 */
void ECTC_DebounceStartZero_f(boolean_T rtu_Signal, uint16_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero_ECTC_m_T *localB,
  DW_DebounceStartZero_ECTC_n_T *localDW)
{
  boolean_T rtb_RelationalOperator_ly;
  boolean_T rtb_RelationalOperator_dm;
  uint32_T rtb_Switch2;
  uint32_T rtb_Switch2_n;
  if (localDW->StateName_g) {
    rtb_Switch2 = 0U;
  } else {
    rtb_Switch2 = localDW->StateName_e;
  }

  if (rtu_Signal) {
    rtb_Switch2 += rtu_FaultStep;
  } else if (rtb_Switch2 >= rtu_FaultStep) {
    rtb_Switch2 -= rtu_FaultStep;
  } else {
    rtb_Switch2 = 0U;
  }

  rtb_RelationalOperator_ly = (rtb_Switch2 > rtu_Hearl2Fault);
  if (localDW->StateName_h) {
    rtb_Switch2_n = 0U;
  } else {
    rtb_Switch2_n = localDW->StateName_c;
  }

  if (!rtu_Signal) {
    rtb_Switch2_n += rtu_FaultStep;
  } else if (rtb_Switch2_n >= rtu_FaultStep) {
    rtb_Switch2_n -= rtu_FaultStep;
  } else {
    rtb_Switch2_n = 0U;
  }

  rtb_RelationalOperator_dm = (rtb_Switch2_n > rtu_Hearl2Fault);
  if (localDW->StateName == 0.0F) {
    if (rtb_RelationalOperator_ly) {
      localB->Switch = 1.0F;
    } else {
      localB->Switch = localDW->StateName;
    }
  } else if (rtb_RelationalOperator_dm) {
    localB->Switch = 0.0F;
  } else {
    localB->Switch = localDW->StateName;
  }

  localDW->StateName = localB->Switch;
  localDW->StateName_g = rtb_RelationalOperator_ly;
  localDW->StateName_e = rtb_Switch2;
  localDW->StateName_h = rtb_RelationalOperator_dm;
  localDW->StateName_c = rtb_Switch2_n;
}

/*
 * Initial conditions for atomic system:
 *    '<S112>/DebounceStartZero1'
 *    '<S230>/DebounceStartZero1'
 */
void ECTC_DebounceStartZero1_Init(DW_DebounceStartZero1_ECTC_T *localDW)
{
  localDW->StateName_l = false;
  localDW->StateName_i = false;
  localDW->StateName = 0U;
  localDW->StateName_n = false;
  localDW->StateName_h = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S112>/DebounceStartZero1'
 *    '<S230>/DebounceStartZero1'
 */
void ECTC_DebounceStartZero1(boolean_T rtu_Signal, uint8_T rtu_Hearl2Fault,
  uint8_T rtu_FaultStep, B_DebounceStartZero1_ECTC_T *localB,
  DW_DebounceStartZero1_ECTC_T *localDW)
{
  boolean_T rtb_RelationalOperator_fb;
  boolean_T rtb_RelationalOperator_hpd;
  uint32_T rtb_Switch2;
  uint32_T rtb_Switch2_p;
  if (localDW->StateName_i) {
    rtb_Switch2 = 0U;
  } else {
    rtb_Switch2 = localDW->StateName;
  }

  if (rtu_Signal) {
    rtb_Switch2 += rtu_FaultStep;
  } else if (rtb_Switch2 >= rtu_FaultStep) {
    rtb_Switch2 -= rtu_FaultStep;
  } else {
    rtb_Switch2 = 0U;
  }

  rtb_RelationalOperator_fb = (rtb_Switch2 > rtu_Hearl2Fault);
  if (localDW->StateName_n) {
    rtb_Switch2_p = 0U;
  } else {
    rtb_Switch2_p = localDW->StateName_h;
  }

  if (!rtu_Signal) {
    rtb_Switch2_p += rtu_FaultStep;
  } else if (rtb_Switch2_p >= rtu_FaultStep) {
    rtb_Switch2_p -= rtu_FaultStep;
  } else {
    rtb_Switch2_p = 0U;
  }

  rtb_RelationalOperator_hpd = (rtb_Switch2_p > rtu_Hearl2Fault);
  if (!localDW->StateName_l) {
    if (rtb_RelationalOperator_fb) {
      localB->Switch = true;
    } else {
      localB->Switch = localDW->StateName_l;
    }
  } else if (rtb_RelationalOperator_hpd) {
    localB->Switch = false;
  } else {
    localB->Switch = localDW->StateName_l;
  }

  localDW->StateName_l = localB->Switch;
  localDW->StateName_i = rtb_RelationalOperator_fb;
  localDW->StateName = rtb_Switch2;
  localDW->StateName_n = rtb_RelationalOperator_hpd;
  localDW->StateName_h = rtb_Switch2_p;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_BCChrgA_20ms_at_outport_1' */
void ECTC_BCChrgA_20ms(void)
{
  uint8_T rtb_GeECTC_BCChrgCtrAMode_enum;
  boolean_T rtb_LogicalOperator_io;
  uint16_T rtb_Init_ai;
  uint8_T tmp;
  rtb_GeECTC_BCChrgCtrAMode_enum = ECTC_DW.StateName_i2;
  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_oo) {
    if (!ECTC_DW.PrechrgWork_MODE_pf) {
      ECTC_DW.StateName_ib = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_f);
      ECTC_DW.StateName_ax = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_p);
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_g);
      ECTC_DW.StateName_jt = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_e);
      ECTC_DW.StateName_nc = false;
      ECTC_DW.PrechrgWork_MODE_pf = true;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCBOutVolt_V() > CcECTC_ACDCMinVolt_V) &&
      get_GbECTD_CChrgAPCtrFilSta_flg() && get_GbECTD_CChrgANCtrFilSta_flg() &&
      ECTC_DW.StateName_ib, CcECTC_BCChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_f, &ECTC_DW.DebounceStartZero_f);
    if (ECTC_B.DebounceStartZero_f.Switch != 0.0F) {
      LbECTC_BCChrgAPCtrCmdPrec_flg = ((boolean_T)ASWTYPE_TRUE);
    } else {
      LbECTC_BCChrgAPCtrCmdPrec_flg = ECTC_DW.StateName_ax;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V) &&
      ECTC_DW.StateName_ib && get_GbECTD_CChrgAPCtrFilSta_flg() &&
      get_GbECTD_CChrgANCtrFilSta_flg(), CcECTC_PreChrgTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_p, &ECTC_DW.DebounceStartZero_p);
    if (ECTC_B.DebounceStartZero_p.Switch != 0.0F) {
      ECTC_B.LbECTC_BCChrgAPreChrgTimeOutFlt = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.LbECTC_BCChrgAPreChrgTimeOutFlt = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCAOutVolt_V() > CcECTC_ACDCMinVolt_V),
      CcECTC_CChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_g,
      &ECTC_DW.DebounceStartZero_g);
    if (ECTC_B.DebounceStartZero_g.Switch != 0.0F) {
      LbECTC_CChrgABCPCtrCmdPrec_flg = ((boolean_T)ASWTYPE_TRUE);
    } else {
      LbECTC_CChrgABCPCtrCmdPrec_flg = ECTC_DW.StateName_jt;
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_e,
      &ECTC_DW.DebounceStartZero_e);
    if (ECTC_B.DebounceStartZero_e.Switch != 0.0F) {
      ECTC_B.Switch_fc = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_fc = ((boolean_T)ASWTYPE_FALSE);
    }

    LbECTC_BCChrgCtrAPrechrgToOffline_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_h);
    LbECTC_BCChrgCtrAPrechrgToOnline_flg = ((get_GbECTD_CChrgAPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_CChrgANCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_BCChrgPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_BCChrgNCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_ib == ((boolean_T)
      ASWTYPE_TRUE)) && (ECTC_DW.StateName_nc == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_ib = LbECTC_CChrgABCPCtrCmdPrec_flg;
    ECTC_DW.StateName_ax = LbECTC_BCChrgAPCtrCmdPrec_flg;
    ECTC_DW.StateName_jt = LbECTC_CChrgABCPCtrCmdPrec_flg;
    ECTC_DW.StateName_nc = LbECTC_BCChrgAPCtrCmdPrec_flg;
  } else {
    if (ECTC_DW.PrechrgWork_MODE_pf) {
      LbECTC_BCChrgCtrAPrechrgToOffline_flg = false;
      LbECTC_BCChrgCtrAPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE_pf = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_gj) {
    if (!ECTC_DW.ShutdownWork_MODE_bv) {
      ECTC_DebounceStartZero1_Init(&ECTC_DW.DebounceStartZero1_a);
      ECTC_DW.FixPtUnitDelay2_DSTATE_ek = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_d = 0U;
      ECTC_DW.ShutdownWork_MODE_bv = true;
    }

    ECTC_B.Constant3_j = ((boolean_T)ASWTYPE_FALSE);
    ECTC_DebounceStartZero1(((boolean_T)ASWTYPE_FALSE), ECTC_RUNTIME_MS,
      CcECTC_DebounceTime100_ms, &ECTC_B.DebounceStartZero1_a,
      &ECTC_DW.DebounceStartZero1_a);
    rtb_LogicalOperator_io = !((!ECTC_B.Constant3_j) &&
      (!ECTC_B.DebounceStartZero1_a.Switch));
    if (rtb_LogicalOperator_io || (ECTC_DW.FixPtUnitDelay2_DSTATE_ek != 0)) {
      rtb_Init_ai = 0U;
    } else {
      rtb_Init_ai = ECTC_DW.FixPtUnitDelay1_DSTATE_d;
    }

    LbECTC_BCChrgCtrAShutdownToOffline_flg = (rtb_Init_ai >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_io) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_d = 0U;
    } else {
      if (LbECTC_BCChrgCtrAShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_d = (uint16_T)((uint32_T)tmp + rtb_Init_ai);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_ek = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE_bv) {
      LbECTC_BCChrgCtrAShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE_bv = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_jc) {
    ECTC_B.Switch_n = LbECTC_BCChrgAPCtrCmdPrec_flg;
  } else if (rtb_GeECTC_BCChrgCtrAMode_enum ==
             ECTC_ConstB.DataTypeConversion1_bj) {
    ECTC_B.Switch_n = ECTC_B.Constant3_j;
  } else {
    ECTC_B.Switch_n = ECTC_DW.Delay_DSTATE_o;
  }

  ECTC_DW.Delay_DSTATE_o = ECTC_B.Switch_n;
  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_cx) {
    if (!ECTC_DW.OfflineWork_MODE_h) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_fc = 0U;
      ECTC_DW.OfflineWork_MODE_h = true;
    }

    rtb_LogicalOperator_io = !((get_GeECMM_ChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion_oj) && (get_GeECTC_ReChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_k) && (get_GeECTC_ReChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion4_n) && (get_GeECTC_CChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2_l) && (get_GeECTC_CChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3_i) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion5_e));
    if (rtb_LogicalOperator_io || (ECTC_DW.FixPtUnitDelay2_DSTATE_n != 0)) {
      rtb_Init_ai = 0U;
    } else {
      rtb_Init_ai = ECTC_DW.FixPtUnitDelay1_DSTATE_fc;
    }

    LbECTC_BCChrgCtrAOfflineToPrechrg_flg = (rtb_Init_ai >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_io) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_fc = 0U;
    } else {
      if (LbECTC_BCChrgCtrAOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_fc = (uint16_T)((uint32_T)tmp + rtb_Init_ai);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_n = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE_h) {
      LbECTC_BCChrgCtrAOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE_h = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_as) {
    if (!ECTC_DW.OnlineWork_MODE_k) {
      ECTC_DW.OnlineWork_MODE_k = true;
    }

    LbECTC_BCChrgCtrAOnlineToPreshut_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_c4);
  } else {
    if (ECTC_DW.OnlineWork_MODE_k) {
      LbECTC_BCChrgCtrAOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE_k = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_az) {
    if (!ECTC_DW.PreshutWork_MODE_h) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero1);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_o);
      ECTC_DW.StateName_b = false;
      ECTC_DW.StateName_aj = false;
      ECTC_DW.PreshutWork_MODE_h = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero, &ECTC_DW.DebounceStartZero);
    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero1, &ECTC_DW.DebounceStartZero1);
    ECTC_DebounceStartZero((get_GcEBSW_ACDCAOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A) && (get_GcEBSW_ACDCBOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A), CcECTC_PreshutToShutdownDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_o, &ECTC_DW.DebounceStartZero_o);
    LbECTC_BCChrgCtrAPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_o.Switch ||
      (ECTC_DW.StateName_b == ((boolean_T)ASWTYPE_TRUE)) ||
      (ECTC_DW.StateName_aj == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_b = ECTC_B.DebounceStartZero1.Switch;
    ECTC_DW.StateName_aj = ECTC_B.DebounceStartZero.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE_h) {
      LbECTC_BCChrgCtrAPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE_h = false;
    }
  }

  if (ECTC_DW.is_active_c3_ECTC == 0U) {
    ECTC_DW.is_active_c3_ECTC = 1U;
    ECTC_DW.is_c3_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)Enum_ECTCBCChrgCtrAMode_Offline;
  } else {
    switch (ECTC_DW.is_c3_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_BCChrgCtrAOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c3_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrAMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_BCChrgCtrAOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c3_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrAMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_BCChrgCtrAPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c3_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrAMode_Offline;
      } else {
        if (LbECTC_BCChrgCtrAPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c3_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
            Enum_ECTCBCChrgCtrAMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_BCChrgCtrAPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c3_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrAMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_BCChrgCtrAShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c3_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_BCChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrAMode_Offline;
      }
      break;
    }
  }

  if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_j) {
    ECTC_B.Switch_ex = LbECTC_CChrgABCPCtrCmdPrec_flg;
  } else if (rtb_GeECTC_BCChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion1_j)
  {
    ECTC_B.Switch_ex = ECTC_B.DebounceStartZero1_a.Switch;
  } else {
    ECTC_B.Switch_ex = ECTC_DW.Delay_DSTATE_av;
  }

  ECTC_DW.Delay_DSTATE_av = ECTC_B.Switch_ex;
  if (CbECTC_BCChrgCtrAModeOvrSwt_flg) {
    set_GeECTC_BCChrgCtrAMode_enum(CeECTC_BCChrgCtrAModeOvr_enum);
  } else {
    set_GeECTC_BCChrgCtrAMode_enum(ECTC_B.GeECTC_BCChrgCtrAMode_enum);
  }

  ECTC_DW.StateName_i2 = get_GeECTC_BCChrgCtrAMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_BCChrgB_20ms_at_outport_1' */
void ECTC_BCChrgB_20ms(void)
{
  uint8_T rtb_GeECTC_BCChrgCtrBMode_enum;
  boolean_T rtb_LogicalOperator_nn;
  uint16_T rtb_Init_g4;
  uint8_T tmp;
  rtb_GeECTC_BCChrgCtrBMode_enum = ECTC_DW.StateName_k;
  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_ko) {
    if (!ECTC_DW.PrechrgWork_MODE_o) {
      ECTC_DW.StateName_ha = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_pv);
      ECTC_DW.StateName_l = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_n);
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_l);
      ECTC_DW.StateName_jm = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_f4);
      ECTC_DW.StateName_n = false;
      ECTC_DW.PrechrgWork_MODE_o = true;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCAOutVolt_V() > CcECTC_ACDCMinVolt_V) &&
      get_GbECTD_CChrgBPCtrFilSta_flg() && get_GbECTD_CChrgBNCtrFilSta_flg() &&
      ECTC_DW.StateName_ha, CcECTC_BCChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_pv, &ECTC_DW.DebounceStartZero_pv);
    if (ECTC_B.DebounceStartZero_pv.Switch != 0.0F) {
      ECTC_B.Switch_j = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_j = ECTC_DW.StateName_l;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V) &&
      ECTC_DW.StateName_ha && get_GbECTD_CChrgBPCtrFilSta_flg() &&
      get_GbECTD_CChrgBNCtrFilSta_flg(), CcECTC_PreChrgTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_n, &ECTC_DW.DebounceStartZero_n);
    if (ECTC_B.DebounceStartZero_n.Switch != 0.0F) {
      ECTC_B.Switch_hy = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_hy = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCBOutVolt_V() > CcECTC_ACDCMinVolt_V),
      CcECTC_CChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_l,
      &ECTC_DW.DebounceStartZero_l);
    if (ECTC_B.DebounceStartZero_l.Switch != 0.0F) {
      ECTC_B.Switch_a = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_a = ECTC_DW.StateName_jm;
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_f4, &ECTC_DW.DebounceStartZero_f4);
    if (ECTC_B.DebounceStartZero_f4.Switch != 0.0F) {
      ECTC_B.Switch_af = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_af = ((boolean_T)ASWTYPE_FALSE);
    }

    LbECTC_BCChrgCtrBPrechrgToOffline_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_n);
    LbECTC_BCChrgCtrBPrechrgToOnline_flg = ((get_GbECTD_CChrgBPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_CChrgBNCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_BCChrgPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_BCChrgNCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_ha == ((boolean_T)
      ASWTYPE_TRUE)) && (ECTC_DW.StateName_n == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_ha = ECTC_B.Switch_a;
    ECTC_DW.StateName_l = ECTC_B.Switch_j;
    ECTC_DW.StateName_jm = ECTC_B.Switch_a;
    ECTC_DW.StateName_n = ECTC_B.Switch_j;
  } else {
    if (ECTC_DW.PrechrgWork_MODE_o) {
      LbECTC_BCChrgCtrBPrechrgToOffline_flg = false;
      LbECTC_BCChrgCtrBPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE_o = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_hk) {
    if (!ECTC_DW.ShutdownWork_MODE_bd) {
      ECTC_DebounceStartZero1_Init(&ECTC_DW.DebounceStartZero1_g);
      ECTC_DW.FixPtUnitDelay2_DSTATE_mk = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_c = 0U;
      ECTC_DW.ShutdownWork_MODE_bd = true;
    }

    ECTC_B.Constant3_l = ((boolean_T)ASWTYPE_FALSE);
    ECTC_DebounceStartZero1(((boolean_T)ASWTYPE_FALSE), ECTC_RUNTIME_MS,
      CcECTC_DebounceTime100_ms, &ECTC_B.DebounceStartZero1_g,
      &ECTC_DW.DebounceStartZero1_g);
    rtb_LogicalOperator_nn = !((!ECTC_B.Constant3_l) &&
      (!ECTC_B.DebounceStartZero1_g.Switch));
    if (rtb_LogicalOperator_nn || (ECTC_DW.FixPtUnitDelay2_DSTATE_mk != 0)) {
      rtb_Init_g4 = 0U;
    } else {
      rtb_Init_g4 = ECTC_DW.FixPtUnitDelay1_DSTATE_c;
    }

    LbECTC_BCChrgCtrBShutdownToOffline_flg = (rtb_Init_g4 >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_nn) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_c = 0U;
    } else {
      if (LbECTC_BCChrgCtrBShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_c = (uint16_T)((uint32_T)tmp + rtb_Init_g4);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_mk = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE_bd) {
      LbECTC_BCChrgCtrBShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE_bd = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_p) {
    ECTC_B.Switch_k = ECTC_B.Switch_j;
  } else if (rtb_GeECTC_BCChrgCtrBMode_enum ==
             ECTC_ConstB.DataTypeConversion1_di) {
    ECTC_B.Switch_k = ECTC_B.Constant3_l;
  } else {
    ECTC_B.Switch_k = ECTC_DW.Delay_DSTATE_p;
  }

  ECTC_DW.Delay_DSTATE_p = ECTC_B.Switch_k;
  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_fd) {
    if (!ECTC_DW.OfflineWork_MODE_b) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_e = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_i = 0U;
      ECTC_DW.OfflineWork_MODE_b = true;
    }

    rtb_LogicalOperator_nn = !((get_GeECMM_ChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion_ou) && (get_GeECTC_ReChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_g) && (get_GeECTC_ReChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion4) && (get_GeECTC_CChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2_a) && (get_GeECTC_CChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3_a) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion5));
    if (rtb_LogicalOperator_nn || (ECTC_DW.FixPtUnitDelay2_DSTATE_e != 0)) {
      rtb_Init_g4 = 0U;
    } else {
      rtb_Init_g4 = ECTC_DW.FixPtUnitDelay1_DSTATE_i;
    }

    LbECTC_BCChrgCtrBOfflineToPrechrg_flg = (rtb_Init_g4 >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_nn) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_i = 0U;
    } else {
      if (LbECTC_BCChrgCtrBOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_i = (uint16_T)((uint32_T)tmp + rtb_Init_g4);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_e = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE_b) {
      LbECTC_BCChrgCtrBOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE_b = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_os) {
    if (!ECTC_DW.OnlineWork_MODE_d) {
      ECTC_DW.OnlineWork_MODE_d = true;
    }

    LbECTC_BCChrgCtrBOnlineToPreshut_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_dm);
  } else {
    if (ECTC_DW.OnlineWork_MODE_d) {
      LbECTC_BCChrgCtrBOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE_d = false;
    }
  }

  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_bz) {
    if (!ECTC_DW.PreshutWork_MODE_j) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_p3);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero1_h);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_a);
      ECTC_DW.StateName_o = false;
      ECTC_DW.StateName_mi = false;
      ECTC_DW.PreshutWork_MODE_j = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_p3,
      &ECTC_DW.DebounceStartZero_p3);
    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero1_h,
      &ECTC_DW.DebounceStartZero1_h);
    ECTC_DebounceStartZero((get_GcEBSW_ACDCAOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A) && (get_GcEBSW_ACDCBOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A), CcECTC_PreshutToShutdownDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_a, &ECTC_DW.DebounceStartZero_a);
    LbECTC_BCChrgCtrBPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_a.Switch ||
      (ECTC_DW.StateName_o == ((boolean_T)ASWTYPE_TRUE)) ||
      (ECTC_DW.StateName_mi == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_o = ECTC_B.DebounceStartZero1_h.Switch;
    ECTC_DW.StateName_mi = ECTC_B.DebounceStartZero_p3.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE_j) {
      LbECTC_BCChrgCtrBPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE_j = false;
    }
  }

  if (ECTC_DW.is_active_c6_ECTC == 0U) {
    ECTC_DW.is_active_c6_ECTC = 1U;
    ECTC_DW.is_c6_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)Enum_ECTCBCChrgCtrBMode_Offline;
  } else {
    switch (ECTC_DW.is_c6_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_BCChrgCtrBOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c6_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrBMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_BCChrgCtrBOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c6_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrBMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_BCChrgCtrBPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c6_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrBMode_Offline;
      } else {
        if (LbECTC_BCChrgCtrBPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c6_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
            Enum_ECTCBCChrgCtrBMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_BCChrgCtrBPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c6_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrBMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_BCChrgCtrBShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c6_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_BCChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCBCChrgCtrBMode_Offline;
      }
      break;
    }
  }

  if (rtb_GeECTC_BCChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_oh) {
    ECTC_B.Switch_f = ECTC_B.Switch_a;
  } else if (rtb_GeECTC_BCChrgCtrBMode_enum ==
             ECTC_ConstB.DataTypeConversion1_ay) {
    ECTC_B.Switch_f = ECTC_B.DebounceStartZero1_g.Switch;
  } else {
    ECTC_B.Switch_f = ECTC_DW.Delay_DSTATE_an;
  }

  ECTC_DW.Delay_DSTATE_an = ECTC_B.Switch_f;
  if (CbECTC_BCChrgCtrBModeOvrSwt_flg) {
    set_GeECTC_BCChrgCtrBMode_enum(CeECTC_BCChrgCtrBModeOvr_enum);
  } else {
    set_GeECTC_BCChrgCtrBMode_enum(ECTC_B.GeECTC_BCChrgCtrBMode_enum);
  }

  ECTC_DW.StateName_k = get_GeECTC_BCChrgCtrBMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_CChrgA_20ms_at_outport_1' */
void ECTC_CChrgA_20ms(void)
{
  uint8_T rtb_GeECTC_CChrgCtrAMode_enum;
  boolean_T rtb_LogicalOperator_o2;
  uint16_T rtb_Init_px;
  uint8_T tmp;
  rtb_GeECTC_CChrgCtrAMode_enum = ECTC_DW.StateName_d;
  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_co) {
    if (!ECTC_DW.OfflineWork_MODE_c) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_m = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_h = 0U;
      ECTC_DW.OfflineWork_MODE_c = true;
    }

    rtb_LogicalOperator_o2 = !((get_GeECMM_ChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion_ke) && (get_GeECTC_ReChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_mh) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2_d) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3_g));
    if (rtb_LogicalOperator_o2 || (ECTC_DW.FixPtUnitDelay2_DSTATE_m != 0)) {
      rtb_Init_px = 0U;
    } else {
      rtb_Init_px = ECTC_DW.FixPtUnitDelay1_DSTATE_h;
    }

    LbECTC_CChrgCtrAOfflineToPrechrg_flg = (rtb_Init_px >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_o2) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_h = 0U;
    } else {
      if (LbECTC_CChrgCtrAOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_h = (uint16_T)((uint32_T)tmp + rtb_Init_px);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_m = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE_c) {
      LbECTC_CChrgCtrAOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE_c = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_iv) {
    if (!ECTC_DW.PrechrgWork_MODE_i) {
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_d);
      ECTC_DW.StateName_iz = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_m);
      ECTC_DW.StateName_m = false;
      ECTC_DW.PrechrgWork_MODE_i = true;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCAOutVolt_V() > CcECTC_ACDCMinVolt_V),
      CcECTC_CChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_d,
      &ECTC_DW.DebounceStartZero_d);
    if (ECTC_B.DebounceStartZero_d.Switch != 0.0F) {
      ECTC_B.Switch_i = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_i = ECTC_DW.StateName_iz;
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBSW_DCDCAOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_m,
      &ECTC_DW.DebounceStartZero_m);
    if (ECTC_B.DebounceStartZero_m.Switch != 0.0F) {
      ECTC_B.Switch_e = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_e = ((boolean_T)ASWTYPE_FALSE);
    }

    LbECTC_CChrgCtrAPrechrgToOffline_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_cc);
    LbECTC_CChrgCtrAPrechrgToOnline_flg = ((get_GbECTD_CChrgAPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_CChrgANCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_m == ((boolean_T)
      ASWTYPE_TRUE)));
    ECTC_DW.StateName_iz = ECTC_B.Switch_i;
    ECTC_DW.StateName_m = ECTC_B.Switch_i;
  } else {
    if (ECTC_DW.PrechrgWork_MODE_i) {
      LbECTC_CChrgCtrAPrechrgToOffline_flg = false;
      LbECTC_CChrgCtrAPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE_i = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_ov) {
    if (!ECTC_DW.OnlineWork_MODE_c) {
      ECTC_DW.OnlineWork_MODE_c = true;
    }

    LbECTC_CChrgCtrAOnlineToPreshut_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_cl);
  } else {
    if (ECTC_DW.OnlineWork_MODE_c) {
      LbECTC_CChrgCtrAOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE_c = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_ep) {
    if (!ECTC_DW.PreshutWork_MODE_n) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_ln);
      ECTC_DW.StateName_fy = false;
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_k);
      ECTC_DW.PreshutWork_MODE_n = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A, CcECTC_PreshutToShutdownDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_ln, &ECTC_DW.DebounceStartZero_ln);
    LbECTC_CChrgCtrAPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_ln.Switch ||
      (ECTC_DW.StateName_fy == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_k, &ECTC_DW.DebounceStartZero_k);
    ECTC_DW.StateName_fy = ECTC_B.DebounceStartZero_k.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE_n) {
      LbECTC_CChrgCtrAPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE_n = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_i) {
    if (!ECTC_DW.ShutdownWork_MODE_b) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_k = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_l = 0U;
      ECTC_DW.ShutdownWork_MODE_b = true;
    }

    ECTC_B.Constant3_c = ((boolean_T)ASWTYPE_FALSE);
    rtb_LogicalOperator_o2 = !((boolean_T)ASWTYPE_TRUE);
    if (rtb_LogicalOperator_o2 || (ECTC_DW.FixPtUnitDelay2_DSTATE_k != 0)) {
      rtb_Init_px = 0U;
    } else {
      rtb_Init_px = ECTC_DW.FixPtUnitDelay1_DSTATE_l;
    }

    LbECTC_CChrgCtrAShutdownToOffline_flg = (rtb_Init_px >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_o2) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_l = 0U;
    } else {
      if (LbECTC_CChrgCtrAShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_l = (uint16_T)((uint32_T)tmp + rtb_Init_px);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_k = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE_b) {
      LbECTC_CChrgCtrAShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE_b = false;
    }
  }

  if (ECTC_DW.is_active_c1_ECTC == 0U) {
    ECTC_DW.is_active_c1_ECTC = 1U;
    ECTC_DW.is_c1_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)Enum_ECTCCChrgCtrAMode_Offline;
  } else {
    switch (ECTC_DW.is_c1_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_CChrgCtrAOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c1_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrAMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_CChrgCtrAOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c1_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrAMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_CChrgCtrAPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c1_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrAMode_Offline;
      } else {
        if (LbECTC_CChrgCtrAPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c1_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
            Enum_ECTCCChrgCtrAMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_CChrgCtrAPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c1_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrAMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_CChrgCtrAShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c1_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_CChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrAMode_Offline;
      }
      break;
    }
  }

  if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion_au) {
    ECTC_B.Switch_en = ECTC_B.Switch_i;
  } else if (rtb_GeECTC_CChrgCtrAMode_enum == ECTC_ConstB.DataTypeConversion1_pa)
  {
    ECTC_B.Switch_en = ECTC_B.Constant3_c;
  } else {
    ECTC_B.Switch_en = ECTC_DW.Delay_DSTATE_h;
  }

  ECTC_DW.Delay_DSTATE_h = ECTC_B.Switch_en;
  if (CbECTC_CChrgCtrAModeOvrSwt_flg) {
    set_GeECTC_CChrgCtrAMode_enum(CeECTC_CChrgCtrAModeOvr_enum);
  } else {
    set_GeECTC_CChrgCtrAMode_enum(ECTC_B.GeECTC_CChrgCtrAMode_enum);
  }

  ECTC_DW.StateName_d = get_GeECTC_CChrgCtrAMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_CChrgB_20ms_at_outport_1' */
void ECTC_CChrgB_20ms(void)
{
  uint8_T rtb_GeECTC_CChrgCtrBMode_enum;
  boolean_T rtb_LogicalOperator_c;
  uint16_T rtb_Init_fh;
  uint8_T tmp;
  rtb_GeECTC_CChrgCtrBMode_enum = ECTC_DW.StateName_c;
  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_k) {
    if (!ECTC_DW.OfflineWork_MODE_e) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_hu = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_p = 0U;
      ECTC_DW.OfflineWork_MODE_e = true;
    }

    rtb_LogicalOperator_c = !((get_GeECMM_ChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion_cd) && (get_GeECTC_ReChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_i) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2_m) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3_o));
    if (rtb_LogicalOperator_c || (ECTC_DW.FixPtUnitDelay2_DSTATE_hu != 0)) {
      rtb_Init_fh = 0U;
    } else {
      rtb_Init_fh = ECTC_DW.FixPtUnitDelay1_DSTATE_p;
    }

    LbECTC_CChrgCtrBOfflineToPrechrg_flg = (rtb_Init_fh >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_c) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_p = 0U;
    } else {
      if (LbECTC_CChrgCtrBOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_p = (uint16_T)((uint32_T)tmp + rtb_Init_fh);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_hu = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE_e) {
      LbECTC_CChrgCtrBOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE_e = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_dy) {
    if (!ECTC_DW.PrechrgWork_MODE_g) {
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_on);
      ECTC_DW.StateName_cv = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_kb);
      ECTC_DW.StateName_h = false;
      ECTC_DW.PrechrgWork_MODE_g = true;
    }

    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) < CcECTC_ACDCANDDCDCVoltDif_V) &&
      (get_GcEBSW_ACDCBOutVolt_V() > CcECTC_ACDCMinVolt_V),
      CcECTC_CChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_on,
      &ECTC_DW.DebounceStartZero_on);
    if (ECTC_B.DebounceStartZero_on.Switch != 0.0F) {
      ECTC_B.Switch_o = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_o = ECTC_DW.StateName_cv;
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBSW_DCDCBOutVolt_V()) > CcECTC_ACDCANDDCDCVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_kb, &ECTC_DW.DebounceStartZero_kb);
    if (ECTC_B.DebounceStartZero_kb.Switch != 0.0F) {
      ECTC_B.Switch_p = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_p = ((boolean_T)ASWTYPE_FALSE);
    }

    LbECTC_CChrgCtrBPrechrgToOffline_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_b);
    LbECTC_CChrgCtrBPrechrgToOnline_flg = ((get_GbECTD_CChrgBPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_CChrgBNCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_h == ((boolean_T)
      ASWTYPE_TRUE)));
    ECTC_DW.StateName_cv = ECTC_B.Switch_o;
    ECTC_DW.StateName_h = ECTC_B.Switch_o;
  } else {
    if (ECTC_DW.PrechrgWork_MODE_g) {
      LbECTC_CChrgCtrBPrechrgToOffline_flg = false;
      LbECTC_CChrgCtrBPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE_g = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_cf) {
    if (!ECTC_DW.OnlineWork_MODE_b) {
      ECTC_DW.OnlineWork_MODE_b = true;
    }

    LbECTC_CChrgCtrBOnlineToPreshut_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_a);
  } else {
    if (ECTC_DW.OnlineWork_MODE_b) {
      LbECTC_CChrgCtrBOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE_b = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_c4) {
    if (!ECTC_DW.PreshutWork_MODE_l) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_pk);
      ECTC_DW.StateName_f2 = false;
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_i);
      ECTC_DW.PreshutWork_MODE_l = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A, CcECTC_PreshutToShutdownDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_pk, &ECTC_DW.DebounceStartZero_pk);
    LbECTC_CChrgCtrBPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_pk.Switch ||
      (ECTC_DW.StateName_f2 == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_i, &ECTC_DW.DebounceStartZero_i);
    ECTC_DW.StateName_f2 = ECTC_B.DebounceStartZero_i.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE_l) {
      LbECTC_CChrgCtrBPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE_l = false;
    }
  }

  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_lw) {
    if (!ECTC_DW.ShutdownWork_MODE_g) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_j = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_m = 0U;
      ECTC_DW.ShutdownWork_MODE_g = true;
    }

    ECTC_B.Constant3_f = ((boolean_T)ASWTYPE_FALSE);
    rtb_LogicalOperator_c = !((boolean_T)ASWTYPE_TRUE);
    if (rtb_LogicalOperator_c || (ECTC_DW.FixPtUnitDelay2_DSTATE_j != 0)) {
      rtb_Init_fh = 0U;
    } else {
      rtb_Init_fh = ECTC_DW.FixPtUnitDelay1_DSTATE_m;
    }

    LbECTC_CChrgCtrBShutdownToOffline_flg = (rtb_Init_fh >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_c) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_m = 0U;
    } else {
      if (LbECTC_CChrgCtrBShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_m = (uint16_T)((uint32_T)tmp + rtb_Init_fh);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_j = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE_g) {
      LbECTC_CChrgCtrBShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE_g = false;
    }
  }

  if (ECTC_DW.is_active_c5_ECTC == 0U) {
    ECTC_DW.is_active_c5_ECTC = 1U;
    ECTC_DW.is_c5_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)Enum_ECTCCChrgCtrBMode_Offline;
  } else {
    switch (ECTC_DW.is_c5_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_CChrgCtrBOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c5_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrBMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_CChrgCtrBOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c5_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrBMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_CChrgCtrBPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c5_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrBMode_Offline;
      } else {
        if (LbECTC_CChrgCtrBPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c5_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
            Enum_ECTCCChrgCtrBMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_CChrgCtrBPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c5_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrBMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_CChrgCtrBShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c5_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_CChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCCChrgCtrBMode_Offline;
      }
      break;
    }
  }

  if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_g5) {
    ECTC_B.Switch_g = ECTC_B.Switch_o;
  } else if (rtb_GeECTC_CChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion1_f)
  {
    ECTC_B.Switch_g = ECTC_B.Constant3_f;
  } else {
    ECTC_B.Switch_g = ECTC_DW.Delay_DSTATE_a;
  }

  ECTC_DW.Delay_DSTATE_a = ECTC_B.Switch_g;
  if (CbECTC_CChrgCtrBModeOvrSwt_flg) {
    set_GeECTC_CChrgCtrBMode_enum(CeECTC_CChrgCtrBModeOvr_enum);
  } else {
    set_GeECTC_CChrgCtrBMode_enum(ECTC_B.GeECTC_CChrgCtrBMode_enum);
  }

  ECTC_DW.StateName_c = get_GeECTC_CChrgCtrBMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_Fault_20ms_at_outport_1' */
void ECTC_Fault_20ms(void)
{
  boolean_T rtb_LogicalOperator5;
  boolean_T rtb_LogicalOperator6;
  boolean_T rtb_LogicalOperator7;
  if (CbECTC_ACDCAOutCurrTimeOutFltOvrSwt_flg) {
    set_GbECTC_ACDCAOutCurrTimeOutFlt_flg(CbECTC_ACDCAOutCurrTimeOutFltOvr_flg);
  } else {
    set_GbECTC_ACDCAOutCurrTimeOutFlt_flg((ECTC_B.DebounceStartZero_mk.Switch ||
      ECTC_B.DebounceStartZero_k.Switch || ECTC_B.DebounceStartZero.Switch ||
      ECTC_B.DebounceStartZero_p3.Switch));
  }

  if (CbECTC_CChrgAPreChrgTimeOutFltOvrSwt_flg) {
    set_GbECTC_CChrgAPreChrgTimeOutFlt_flg(CbECTC_CChrgAPreChrgTimeOutFltOvr_flg);
  } else {
    set_GbECTC_CChrgAPreChrgTimeOutFlt_flg((ECTC_B.Switch_e || ECTC_B.Switch_fc));
  }

  if (CbECTC_BCChrgPreChrgTimeOutFltOvrSwt_flg) {
    set_GbECTC_BCChrgPreChrgTimeOutFlt_flg(CbECTC_BCChrgPreChrgTimeOutFltOvr_flg);
  } else {
    set_GbECTC_BCChrgPreChrgTimeOutFlt_flg
      ((ECTC_B.LbECTC_BCChrgAPreChrgTimeOutFlt || ECTC_B.Switch_hy));
  }

  if (CbECTC_ACDCBOutCurrTimeOutFltOvrSwt_flg) {
    set_GbECTC_ACDCBOutCurrTimeOutFlt_flg(CbECTC_ACDCBOutCurrTimeOutFltOvr_flg);
  } else {
    set_GbECTC_ACDCBOutCurrTimeOutFlt_flg((ECTC_B.DebounceStartZero1.Switch ||
      ECTC_B.DebounceStartZero_px.Switch || ECTC_B.DebounceStartZero_i.Switch ||
      ECTC_B.DebounceStartZero1_h.Switch));
  }

  if (CbECTC_CChrgBPreChrgTimeOutFltOvrSwt_flg) {
    set_GbECTC_CChrgBPreChrgTimeOutFlt_flg(CbECTC_CChrgBPreChrgTimeOutFltOvr_flg);
  } else {
    set_GbECTC_CChrgBPreChrgTimeOutFlt_flg((ECTC_B.Switch_p || ECTC_B.Switch_af));
  }

  if (CbECTC_ReChrgAPreChrgTimeOutFltOvrSwt_flg) {
    set_GbECTC_ReChrgAPreChrgTimeOutFlt_flg
      (CbECTC_ReChrgAPreChrgTimeOutFltOvr_flg);
  } else {
    set_GbECTC_ReChrgAPreChrgTimeOutFlt_flg(ECTC_B.Switch_b);
  }

  if (CbECTC_ReChrgBPreChrgTimeOutFltOvrSwt_flg) {
    set_GbECTC_ReChrgBPreChrgTimeOutFlt_flg
      (CbECTC_ReChrgBPreChrgTimeOutFltOvr_flg);
  } else {
    set_GbECTC_ReChrgBPreChrgTimeOutFlt_flg(ECTC_B.Switch_h);
  }

  rtb_LogicalOperator5 = (ECTC_B.Switch_en || ECTC_B.Switch_ex);
  if (CbECTC_ReChrgAANDCChrgACircuitFltOvrSwt_flg) {
    set_GbECTC_ReChrgAANDCChrgACircuitFlt_flg
      (CbECTC_ReChrgAANDCChrgACircuitFltOvr_flg);
  } else {
    set_GbECTC_ReChrgAANDCChrgACircuitFlt_flg((LbECTC_ReChrgAPCtrCmd_flg &&
      rtb_LogicalOperator5));
  }

  rtb_LogicalOperator6 = (ECTC_B.Switch_g || ECTC_B.Switch_f);
  if (CbECTC_ReChrgBANDCChrgBCircuitFltOvrSwt_flg) {
    set_GbECTC_ReChrgBANDCChrgBCircuitFlt_flg
      (CbECTC_ReChrgBANDCChrgBCircuitFltOvr_flg);
  } else {
    set_GbECTC_ReChrgBANDCChrgBCircuitFlt_flg((ECTC_B.Switch_c &&
      rtb_LogicalOperator6));
  }

  rtb_LogicalOperator7 = (ECTC_B.Switch_n || ECTC_B.Switch_k);
  if (CbECTC_ReChrgAANDBCChrgCircuitFltOvrSwt_flg) {
    set_GbECTC_ReChrgAANDBCChrgCircuitFlt_flg
      (CbECTC_ReChrgAANDBCChrgCircuitFltOvr_flg);
  } else {
    set_GbECTC_ReChrgAANDBCChrgCircuitFlt_flg((LbECTC_ReChrgAPCtrCmd_flg &&
      rtb_LogicalOperator7));
  }

  if (CbECTC_ReChrgBANDBCChrgCircuitFltOvrSwt_flg) {
    set_GbECTC_ReChrgBANDBCChrgCircuitFlt_flg
      (CbECTC_ReChrgBANDBCChrgCircuitFltOvr_flg);
  } else {
    set_GbECTC_ReChrgBANDBCChrgCircuitFlt_flg((ECTC_B.Switch_c &&
      rtb_LogicalOperator7));
  }

  if (CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvrSwt_flg) {
    set_GbECTC_CChrgAANDBCChrgANDCChrgBCircuitFlt_flg
      (CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvr_flg);
  } else {
    set_GbECTC_CChrgAANDBCChrgANDCChrgBCircuitFlt_flg((rtb_LogicalOperator5 &&
      rtb_LogicalOperator6 && rtb_LogicalOperator7));
  }

  if (get_GbECTC_ReChrgAANDBCChrgCircuitFlt_flg() ||
      get_GbECTC_ReChrgBANDBCChrgCircuitFlt_flg() ||
      get_GbECTC_CChrgAANDBCChrgANDCChrgBCircuitFlt_flg()) {
    rtb_LogicalOperator7 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECTC_BCChrgNCtrCmdOvrSwt_flg) {
    set_GbECTC_BCChrgNCtrCmd_flg(CbECTC_BCChrgNCtrCmdOvr_flg);
  } else {
    set_GbECTC_BCChrgNCtrCmd_flg(rtb_LogicalOperator7);
  }

  if (CbECTC_BCChrgPCtrCmdOvrSwt_flg) {
    set_GbECTC_BCChrgPCtrCmd_flg(CbECTC_BCChrgPCtrCmdOvr_flg);
  } else {
    set_GbECTC_BCChrgPCtrCmd_flg(rtb_LogicalOperator7);
  }

  if (get_GbECTC_ReChrgAANDCChrgACircuitFlt_flg() ||
      get_GbECTC_CChrgAANDBCChrgANDCChrgBCircuitFlt_flg()) {
    rtb_LogicalOperator5 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECTC_CChrgANCtrCmdOvrSwt_flg) {
    set_GbECTC_CChrgANCtrCmd_flg(CbECTC_CChrgANCtrCmdOvr_flg);
  } else {
    set_GbECTC_CChrgANCtrCmd_flg(rtb_LogicalOperator5);
  }

  if (CbECTC_CChrgAPCtrCmdOvrSwt_flg) {
    set_GbECTC_CChrgAPCtrCmd_flg(CbECTC_CChrgAPCtrCmdOvr_flg);
  } else {
    set_GbECTC_CChrgAPCtrCmd_flg(rtb_LogicalOperator5);
  }

  if (get_GbECTC_ReChrgBANDCChrgBCircuitFlt_flg() ||
      get_GbECTC_CChrgAANDBCChrgANDCChrgBCircuitFlt_flg()) {
    rtb_LogicalOperator6 = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbECTC_CChrgBNCtrCmdOvrSwt_flg) {
    set_GbECTC_CChrgBNCtrCmd_flg(CbECTC_CChrgBNCtrCmdOvr_flg);
  } else {
    set_GbECTC_CChrgBNCtrCmd_flg(rtb_LogicalOperator6);
  }

  if (CbECTC_CChrgBPCtrCmdOvrSwt_flg) {
    set_GbECTC_CChrgBPCtrCmd_flg(CbECTC_CChrgBPCtrCmdOvr_flg);
  } else {
    set_GbECTC_CChrgBPCtrCmd_flg(rtb_LogicalOperator6);
  }

  if (get_GbECTC_ReChrgAANDCChrgACircuitFlt_flg() ||
      get_GbECTC_ReChrgAANDBCChrgCircuitFlt_flg()) {
    rtb_LogicalOperator6 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_LogicalOperator6 = LbECTC_ReChrgAPCtrCmd_flg;
  }

  if (CbECTC_ReChrgANCtrCmdOvrSwt_flg) {
    set_GbECTC_ReChrgANCtrCmd_flg(CbECTC_ReChrgANCtrCmdOvr_flg);
  } else {
    set_GbECTC_ReChrgANCtrCmd_flg(rtb_LogicalOperator6);
  }

  if (CbECTC_ReChrgAPCtrCmdOvrSwt_flg) {
    set_GbECTC_ReChrgAPCtrCmd_flg(CbECTC_ReChrgAPCtrCmdOvr_flg);
  } else {
    set_GbECTC_ReChrgAPCtrCmd_flg(rtb_LogicalOperator6);
  }

  if (get_GbECTC_ReChrgBANDCChrgBCircuitFlt_flg() ||
      get_GbECTC_ReChrgBANDBCChrgCircuitFlt_flg()) {
    rtb_LogicalOperator6 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_LogicalOperator6 = ECTC_B.Switch_c;
  }

  if (CbECTC_ReChrgBNCtrCmdOvrSwt_flg) {
    set_GbECTC_ReChrgBNCtrCmd_flg(CbECTC_ReChrgBNCtrCmdOvr_flg);
  } else {
    set_GbECTC_ReChrgBNCtrCmd_flg(rtb_LogicalOperator6);
  }

  if (CbECTC_ReChrgBPCtrCmdOvrSwt_flg) {
    set_GbECTC_ReChrgBPCtrCmd_flg(CbECTC_ReChrgBPCtrCmdOvr_flg);
  } else {
    set_GbECTC_ReChrgBPCtrCmd_flg(rtb_LogicalOperator6);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_ReChrgA_20ms_at_outport_1' */
void ECTC_ReChrgA_20ms(void)
{
  boolean_T rtb_LogicalOperator_ag;
  uint16_T rtb_Init_b;
  uint8_T tmp;
  LbECTC_Flag1_flg = ECTC_DW.StateName_i;
  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_e) {
    if (!ECTC_DW.OfflineWork_MODE_n) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_ov = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_b = 0U;
      ECTC_DW.OfflineWork_MODE_n = true;
    }

    rtb_LogicalOperator_ag = !((get_GeECMM_ChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion_o) && (get_GeECTC_CChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_e) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2_i) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3_f));
    if (rtb_LogicalOperator_ag || (ECTC_DW.FixPtUnitDelay2_DSTATE_ov != 0)) {
      rtb_Init_b = 0U;
    } else {
      rtb_Init_b = ECTC_DW.FixPtUnitDelay1_DSTATE_b;
    }

    LbECTC_ReChrgCtrAOfflineToPrechrg_flg = (rtb_Init_b >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_ag) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_b = 0U;
    } else {
      if (LbECTC_ReChrgCtrAOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_b = (uint16_T)((uint32_T)tmp + rtb_Init_b);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_ov = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE_n) {
      LbECTC_ReChrgCtrAOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE_n = false;
    }
  }

  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_f) {
    if (!ECTC_DW.PrechrgWork_MODE_p) {
      ECTC_DW.StateName_f = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_k1);
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_h);
      ECTC_DW.PrechrgWork_MODE_p = true;
    }

    LbECTC_ReChrgCtrAPrechrgToOffline_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_d);
    LbECTC_ReChrgCtrAPrechrgToOnline_flg = ((get_GbECTD_ReChrgAPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_ReChrgANCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_f == ((boolean_T)
      ASWTYPE_TRUE)));
    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBCR_PackAOutVolt_V()) < CcECTC_ACDCANDPackVoltDif_V) &&
      (get_GcEBCR_PackAOutVolt_V() > CcECTC_SysMinVolt_V),
      CcECTC_ReChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_k1,
      &ECTC_DW.DebounceStartZero_k1);
    if (ECTC_B.DebounceStartZero_k1.Switch != 0.0F) {
      LbECTC_ReChrgAPCtrCmdPrec_flg = ((boolean_T)ASWTYPE_TRUE);
    } else {
      LbECTC_ReChrgAPCtrCmdPrec_flg = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCAOutVolt_V() -
      get_GcEBCR_PackAOutVolt_V()) > CcECTC_ACDCANDPackVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_h,
      &ECTC_DW.DebounceStartZero_h);
    if (ECTC_B.DebounceStartZero_h.Switch != 0.0F) {
      ECTC_B.Switch_b = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_b = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DW.StateName_f = LbECTC_ReChrgAPCtrCmdPrec_flg;
  } else {
    if (ECTC_DW.PrechrgWork_MODE_p) {
      LbECTC_ReChrgCtrAPrechrgToOffline_flg = false;
      LbECTC_ReChrgCtrAPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE_p = false;
    }
  }

  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_h) {
    if (!ECTC_DW.OnlineWork_MODE_o) {
      ECTC_DW.OnlineWork_MODE_o = true;
    }

    LbECTC_ReChrgCtrAOnlineToPreshut_flg = (get_GeECMM_ChrgCtrAMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_c2);
  } else {
    if (ECTC_DW.OnlineWork_MODE_o) {
      LbECTC_ReChrgCtrAOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE_o = false;
    }
  }

  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_c2) {
    if (!ECTC_DW.PreshutWork_MODE_i) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_mk);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_b);
      ECTC_DW.StateName_j = false;
      ECTC_DW.PreshutWork_MODE_i = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_mk,
      &ECTC_DW.DebounceStartZero_mk);
    ECTC_DebounceStartZero(get_GcEBSW_ACDCAOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A, CcECTC_PreshutToShutdownDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_b, &ECTC_DW.DebounceStartZero_b);
    LbECTC_ReChrgCtrAPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_b.Switch ||
      (ECTC_DW.StateName_j == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_j = ECTC_B.DebounceStartZero_mk.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE_i) {
      LbECTC_ReChrgCtrAPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE_i = false;
    }
  }

  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_g) {
    if (!ECTC_DW.ShutdownWork_MODE_h) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_h = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_g = 0U;
      ECTC_DW.ShutdownWork_MODE_h = true;
    }

    LbECTC_ReChrgAPCtrCmdShut_flg = ((boolean_T)ASWTYPE_FALSE);
    rtb_LogicalOperator_ag = !((boolean_T)ASWTYPE_TRUE);
    if (rtb_LogicalOperator_ag || (ECTC_DW.FixPtUnitDelay2_DSTATE_h != 0)) {
      rtb_Init_b = 0U;
    } else {
      rtb_Init_b = ECTC_DW.FixPtUnitDelay1_DSTATE_g;
    }

    LbECTC_ReChrgCtrAShutdownToOffline_flg = (rtb_Init_b >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_ag) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_g = 0U;
    } else {
      if (LbECTC_ReChrgCtrAShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_g = (uint16_T)((uint32_T)tmp + rtb_Init_b);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_h = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE_h) {
      LbECTC_ReChrgCtrAShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE_h = false;
    }
  }

  if (ECTC_DW.is_active_c2_ECTC == 0U) {
    ECTC_DW.is_active_c2_ECTC = 1U;
    ECTC_DW.is_c2_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)Enum_ECTCReChrgCtrAMode_Offline;
  } else {
    switch (ECTC_DW.is_c2_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_ReChrgCtrAOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c2_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrAMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_ReChrgCtrAOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c2_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrAMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_ReChrgCtrAPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c2_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrAMode_Offline;
      } else {
        if (LbECTC_ReChrgCtrAPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c2_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
            Enum_ECTCReChrgCtrAMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_ReChrgCtrAPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c2_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrAMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_ReChrgCtrAShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c2_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_ReChrgCtrAMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrAMode_Offline;
      }
      break;
    }
  }

  if (CbECTC_ReChrgCtrAModeOvrSwt_flg) {
    set_GeECTC_ReChrgCtrAMode_enum(CeECTC_ReChrgCtrAModeOvr_enum);
  } else {
    set_GeECTC_ReChrgCtrAMode_enum(ECTC_B.GeECTC_ReChrgCtrAMode_enum);
  }

  if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion_d) {
    LbECTC_ReChrgAPCtrCmd_flg = LbECTC_ReChrgAPCtrCmdPrec_flg;
  } else if (LbECTC_Flag1_flg == ECTC_ConstB.DataTypeConversion1_m) {
    LbECTC_ReChrgAPCtrCmd_flg = LbECTC_ReChrgAPCtrCmdShut_flg;
  } else {
    LbECTC_ReChrgAPCtrCmd_flg = ECTC_DW.StateName_a;
  }

  ECTC_DW.StateName_a = LbECTC_ReChrgAPCtrCmd_flg;
  ECTC_DW.StateName_i = get_GeECTC_ReChrgCtrAMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECTC_ReChrgB_20ms_at_outport_1' */
void ECTC_ReChrgB_20ms(void)
{
  uint8_T rtb_GeECTC_ReChrgCtrBMode_enum;
  boolean_T rtb_LogicalOperator_ht;
  uint16_T rtb_Init_d;
  uint8_T tmp;
  rtb_GeECTC_ReChrgCtrBMode_enum = ECTC_DW.StateName;
  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_a) {
    if (!ECTC_DW.OfflineWork_MODE) {
      ECTC_DW.FixPtUnitDelay2_DSTATE_o = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE_f = 0U;
      ECTC_DW.OfflineWork_MODE = true;
    }

    rtb_LogicalOperator_ht = !((get_GeECMM_ChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion_ai) && (get_GeECTC_CChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion1_pe) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      ECTC_ConstB.DataTypeConversion2) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      ECTC_ConstB.DataTypeConversion3));
    if (rtb_LogicalOperator_ht || (ECTC_DW.FixPtUnitDelay2_DSTATE_o != 0)) {
      rtb_Init_d = 0U;
    } else {
      rtb_Init_d = ECTC_DW.FixPtUnitDelay1_DSTATE_f;
    }

    LbECTC_ReChrgCtrBOfflineToPrechrg_flg = (rtb_Init_d >=
      CcECTC_OfflineToPrechrgDelayT_ms);
    if (rtb_LogicalOperator_ht) {
      ECTC_DW.FixPtUnitDelay1_DSTATE_f = 0U;
    } else {
      if (LbECTC_ReChrgCtrBOfflineToPrechrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE_f = (uint16_T)((uint32_T)tmp + rtb_Init_d);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE_o = 0U;
  } else {
    if (ECTC_DW.OfflineWork_MODE) {
      LbECTC_ReChrgCtrBOfflineToPrechrg_flg = false;
      ECTC_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_b) {
    if (!ECTC_DW.PrechrgWork_MODE) {
      ECTC_DW.StateName_p = false;
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_pkl);
      ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_g4);
      ECTC_DW.PrechrgWork_MODE = true;
    }

    LbECTC_ReChrgCtrBPrechrgToOffline_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1);
    LbECTC_ReChrgCtrBPrechrgToOnline_flg = ((get_GbECTD_ReChrgBPCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECTD_ReChrgBNCtrFilSta_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECTC_DW.StateName_p == ((boolean_T)
      ASWTYPE_TRUE)));
    ECTC_DebounceStartZero_f(((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBCR_PackBOutVolt_V()) < CcECTC_ACDCANDPackVoltDif_V) &&
      (get_GcEBCR_PackBOutVolt_V() > CcECTC_SysMinVolt_V),
      CcECTC_ReChrgCtrCmdDebT_ms, ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_pkl,
      &ECTC_DW.DebounceStartZero_pkl);
    if (ECTC_B.DebounceStartZero_pkl.Switch != 0.0F) {
      ECTC_B.Switch = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DebounceStartZero_f((real32_T)fabs(get_GcEBSW_ACDCBOutVolt_V() -
      get_GcEBCR_PackBOutVolt_V()) > CcECTC_ACDCANDPackVoltDif_V,
      CcECTC_PreChrgTimeOutDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_g4, &ECTC_DW.DebounceStartZero_g4);
    if (ECTC_B.DebounceStartZero_g4.Switch != 0.0F) {
      ECTC_B.Switch_h = ((boolean_T)ASWTYPE_TRUE);
    } else {
      ECTC_B.Switch_h = ((boolean_T)ASWTYPE_FALSE);
    }

    ECTC_DW.StateName_p = ECTC_B.Switch;
  } else {
    if (ECTC_DW.PrechrgWork_MODE) {
      LbECTC_ReChrgCtrBPrechrgToOffline_flg = false;
      LbECTC_ReChrgCtrBPrechrgToOnline_flg = false;
      ECTC_DW.PrechrgWork_MODE = false;
    }
  }

  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion) {
    if (!ECTC_DW.OnlineWork_MODE) {
      ECTC_DW.OnlineWork_MODE = true;
    }

    LbECTC_ReChrgCtrBOnlineToPreshut_flg = (get_GeECMM_ChrgCtrBMode_enum() !=
      ECTC_ConstB.DataTypeConversion1_p);
  } else {
    if (ECTC_DW.OnlineWork_MODE) {
      LbECTC_ReChrgCtrBOnlineToPreshut_flg = false;
      ECTC_DW.OnlineWork_MODE = false;
    }
  }

  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_l) {
    if (!ECTC_DW.PreshutWork_MODE) {
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_px);
      ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_c);
      ECTC_DW.StateName_g = false;
      ECTC_DW.PreshutWork_MODE = true;
    }

    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() >
      CcECTC_ACDCTimeOutCurr_A, CcECTC_ACDCOutCurrTimeOutDebT_ms,
      ECTC_RUNTIME_MS, &ECTC_B.DebounceStartZero_px,
      &ECTC_DW.DebounceStartZero_px);
    ECTC_DebounceStartZero(get_GcEBSW_ACDCBOutCurr_A() <
      CcECTC_ACDCTimeOutCurr_A, CcECTC_PreshutToShutdownDebT_ms, ECTC_RUNTIME_MS,
      &ECTC_B.DebounceStartZero_c, &ECTC_DW.DebounceStartZero_c);
    LbECTC_ReChrgCtrBPreShutToShutdown_flg = (ECTC_B.DebounceStartZero_c.Switch ||
      (ECTC_DW.StateName_g == ((boolean_T)ASWTYPE_TRUE)));
    ECTC_DW.StateName_g = ECTC_B.DebounceStartZero_px.Switch;
  } else {
    if (ECTC_DW.PreshutWork_MODE) {
      LbECTC_ReChrgCtrBPreShutToShutdown_flg = false;
      ECTC_DW.PreshutWork_MODE = false;
    }
  }

  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_n) {
    if (!ECTC_DW.ShutdownWork_MODE) {
      ECTC_DW.FixPtUnitDelay2_DSTATE = 1U;
      ECTC_DW.FixPtUnitDelay1_DSTATE = 0U;
      ECTC_DW.ShutdownWork_MODE = true;
    }

    ECTC_B.Constant3 = ((boolean_T)ASWTYPE_FALSE);
    rtb_LogicalOperator_ht = !((boolean_T)ASWTYPE_TRUE);
    if (rtb_LogicalOperator_ht || (ECTC_DW.FixPtUnitDelay2_DSTATE != 0)) {
      rtb_Init_d = 0U;
    } else {
      rtb_Init_d = ECTC_DW.FixPtUnitDelay1_DSTATE;
    }

    LbECTC_ReChrgCtrBShutdownToOffline_flg = (rtb_Init_d >=
      CcECTC_ShutdownToOfflineDelayT_ms);
    if (rtb_LogicalOperator_ht) {
      ECTC_DW.FixPtUnitDelay1_DSTATE = 0U;
    } else {
      if (LbECTC_ReChrgCtrBShutdownToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECTC_RUNTIME_MS;
      }

      ECTC_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_d);
    }

    ECTC_DW.FixPtUnitDelay2_DSTATE = 0U;
  } else {
    if (ECTC_DW.ShutdownWork_MODE) {
      LbECTC_ReChrgCtrBShutdownToOffline_flg = false;
      ECTC_DW.ShutdownWork_MODE = false;
    }
  }

  if (ECTC_DW.is_active_c4_ECTC == 0U) {
    ECTC_DW.is_active_c4_ECTC = 1U;
    ECTC_DW.is_c4_ECTC = ECTC_IN_Offline;
    ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)Enum_ECTCReChrgCtrBMode_Offline;
  } else {
    switch (ECTC_DW.is_c4_ECTC) {
     case ECTC_IN_Offline:
      if (LbECTC_ReChrgCtrBOfflineToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c4_ECTC = ECTC_IN_Prechrg;
        ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrBMode_Prechrg;
      }
      break;

     case ECTC_IN_Online:
      if (LbECTC_ReChrgCtrBOnlineToPreshut_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c4_ECTC = ECTC_IN_Preshut;
        ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrBMode_Preshut;
      }
      break;

     case ECTC_IN_Prechrg:
      if (LbECTC_ReChrgCtrBPrechrgToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c4_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrBMode_Offline;
      } else {
        if (LbECTC_ReChrgCtrBPrechrgToOnline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECTC_DW.is_c4_ECTC = ECTC_IN_Online;
          ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
            Enum_ECTCReChrgCtrBMode_Online;
        }
      }
      break;

     case ECTC_IN_Preshut:
      if (LbECTC_ReChrgCtrBPreShutToShutdown_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c4_ECTC = ECTC_IN_Shutdown;
        ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrBMode_Shutdown;
      }
      break;

     default:
      if (LbECTC_ReChrgCtrBShutdownToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECTC_DW.is_c4_ECTC = ECTC_IN_Offline;
        ECTC_B.GeECTC_ReChrgCtrBMode_enum = (uint8_T)
          Enum_ECTCReChrgCtrBMode_Offline;
      }
      break;
    }
  }

  if (CbECTC_ReChrgCtrBModeOvrSwt_flg) {
    set_GeECTC_ReChrgCtrBMode_enum(CeECTC_ReChrgCtrBModeOvr_enum);
  } else {
    set_GeECTC_ReChrgCtrBMode_enum(ECTC_B.GeECTC_ReChrgCtrBMode_enum);
  }

  if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion_c) {
    ECTC_B.Switch_c = ECTC_B.Switch;
  } else if (rtb_GeECTC_ReChrgCtrBMode_enum == ECTC_ConstB.DataTypeConversion1_c)
  {
    ECTC_B.Switch_c = ECTC_B.Constant3;
  } else {
    ECTC_B.Switch_c = ECTC_DW.Delay_DSTATE;
  }

  ECTC_DW.Delay_DSTATE = ECTC_B.Switch_c;
  ECTC_DW.StateName = get_GeECTC_ReChrgCtrBMode_enum();
}

/* Model initialize function */
void ECTC_initialize(void)
{
  ECTC_DW.FixPtUnitDelay2_DSTATE_ov = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_k1);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_h);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_mk);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_b);
  LbECTC_ReChrgAPCtrCmdShut_flg = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DW.FixPtUnitDelay2_DSTATE_h = 1U;
  ECTC_DW.FixPtUnitDelay2_DSTATE_m = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_d);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_m);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_ln);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_k);
  ECTC_B.Constant3_c = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DW.FixPtUnitDelay2_DSTATE_k = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_f);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_p);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_g);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_e);
  ECTC_B.Constant3_j = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DebounceStartZero1_Init(&ECTC_DW.DebounceStartZero1_a);
  ECTC_DW.FixPtUnitDelay2_DSTATE_ek = 1U;
  ECTC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero1);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_o);
  ECTC_DW.FixPtUnitDelay2_DSTATE_o = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_pkl);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_g4);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_px);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_c);
  ECTC_B.Constant3 = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DW.FixPtUnitDelay2_DSTATE = 1U;
  ECTC_DW.FixPtUnitDelay2_DSTATE_hu = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_on);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_kb);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_pk);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_i);
  ECTC_B.Constant3_f = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DW.FixPtUnitDelay2_DSTATE_j = 1U;
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_pv);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_n);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_l);
  ECTC_DebounceStartZero_e_Init(&ECTC_DW.DebounceStartZero_f4);
  ECTC_B.Constant3_l = ((boolean_T)ASWTYPE_FALSE);
  ECTC_DebounceStartZero1_Init(&ECTC_DW.DebounceStartZero1_g);
  ECTC_DW.FixPtUnitDelay2_DSTATE_mk = 1U;
  ECTC_DW.FixPtUnitDelay2_DSTATE_e = 1U;
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_p3);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero1_h);
  ECTC_DebounceStartZero_Init(&ECTC_DW.DebounceStartZero_a);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
