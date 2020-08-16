/*
 * File: EACC.c
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 14 21:17:16 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EACC.h"
#include "EACC_private.h"

/* Named constants for Chart: '<S4>/ACDCARunMode' */
#define EACC_IN_Offline                ((uint8_T)1U)
#define EACC_IN_Prechrg                ((uint8_T)2U)
#define EACC_IN_Run                    ((uint8_T)3U)
#define EACC_IN_Standby                ((uint8_T)4U)

/* Block signals (auto storage) */
B_EACC_T EACC_B;

/* Block states (auto storage) */
DW_EACC_T EACC_DW;

/* Real-time model */
RT_MODEL_EACC_T EACC_M_;
RT_MODEL_EACC_T *const EACC_M = &EACC_M_;

/*
 * Initial conditions for atomic system:
 *    '<S7>/Delay'
 *    '<S49>/Delay'
 */
void EACC_Delay_Init(DW_Delay_EACC_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S7>/Delay'
 *    '<S49>/Delay'
 */
void EACC_Delay(boolean_T rtu_Enable, uint8_T rtu_TimeThrld, B_Delay_EACC_T
                *localB, DW_Delay_EACC_T *localDW)
{
  boolean_T rtb_LogicalOperator_k;
  uint8_T rtb_Init_c;
  uint8_T tmp;
  rtb_LogicalOperator_k = !rtu_Enable;
  if (rtb_LogicalOperator_k || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_c = 0U;
  } else {
    rtb_Init_c = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_c >= rtu_TimeThrld);
  if (rtb_LogicalOperator_k) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = EACC_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp + rtb_Init_c);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/*
 * Initial conditions for atomic system:
 *    '<S7>/Delay1'
 *    '<S49>/Delay1'
 */
void EACC_Delay1_Init(DW_Delay1_EACC_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S7>/Delay1'
 *    '<S49>/Delay1'
 */
void EACC_Delay1(boolean_T rtu_Enable, uint8_T rtu_TimeThrld, B_Delay1_EACC_T
                 *localB, DW_Delay1_EACC_T *localDW)
{
  boolean_T rtb_LogicalOperator_o;
  uint8_T rtb_Init_m;
  uint8_T tmp;
  rtb_LogicalOperator_o = !rtu_Enable;
  if (rtb_LogicalOperator_o || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_m = 0U;
  } else {
    rtb_Init_m = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_m >= rtu_TimeThrld);
  if (rtb_LogicalOperator_o) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = EACC_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp + rtb_Init_m);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EACCA_20ms_at_outport_1' */
void EACCA_20ms(void)
{
  uint8_T rtb_GeEACC_ACDCARunMode_enum;
  boolean_T rtb_Switch8_c;
  boolean_T rtb_LogicalOperator_k;
  uint16_T rtb_Init_n;
  uint8_T rtb_Init_a;
  real32_T rtb_Switch6_j;
  uint8_T tmp;
  LcEACC_ACDCATempPwr_kw = look1_iflf_binlxpw(get_GcEBSW_ACDCAWaterTemp_C(),
    ((real32_T *)&(CaEACC_ACDCAWaterTemp_C[0])), ((real32_T *)
    &(CaEACC_ACDCATempPwrTable_kw[0])), 6U);
  if (get_GeEBSW_ACDCAFltLvl_enum() == EACC_ConstB.DataTypeConversion_ib) {
    LcEACC_ACDCATempFltPwr_kw = LcEACC_ACDCATempPwr_kw;
  } else if (get_GeEBSW_ACDCAFltLvl_enum() == EACC_ConstB.DataTypeConversion1_f)
  {
    LcEACC_ACDCATempFltPwr_kw = LcEACC_ACDCATempPwr_kw / (real32_T)EACC_Two_NUMB;
  } else if (get_GeEBSW_ACDCAFltLvl_enum() >= EACC_ConstB.DataTypeConversion2_i)
  {
    LcEACC_ACDCATempFltPwr_kw = EACC_Zero_NUMB;
  } else {
    LcEACC_ACDCATempFltPwr_kw = EACC_DW.StateName_f;
  }

  if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion3_c) {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_11_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion4_p)
  {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_33p_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion5_b)
  {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_7_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion6_e)
  {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_20_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion7_o)
  {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_40_kw;
  } else {
    LcEACC_ACDCAScreenInputPwr_kw = EACC_DW.StateName_h;
  }

  if ((LcEACC_ACDCATempFltPwr_kw <= LcEACC_ACDCAScreenInputPwr_kw) || rtIsNaNF
      (LcEACC_ACDCAScreenInputPwr_kw)) {
    LcEACC_ACDCAMaxPwr_kw = LcEACC_ACDCATempFltPwr_kw;
  } else {
    LcEACC_ACDCAMaxPwr_kw = LcEACC_ACDCAScreenInputPwr_kw;
  }

  rtb_Switch6_j = LcEACC_ACDCAMaxPwr_kw * CcEACC_Ratio1000_R /
    get_GcEBSW_ACDCAOutVolt_V();
  if (!(rtb_Switch6_j <= CcEACC_ACDCACalCurr_A)) {
    rtb_Switch6_j = CcEACC_ACDCACalCurr_A;
  }

  LcEACC_ACDCAMaxCurr_A = rtb_Switch6_j * CcEACC_ACDCACurrRatio_R * (real32_T)
    CcEACC_ACDCASum_numb;
  rtb_Switch6_j = get_GcECCR_CCU2BCLSPN3073IReq_A() -
    get_GcEACC_ACDCBOutCurrReq_A();
  if (rtb_Switch6_j >= EACC_ZERODOTONE_NUMB) {
    LcEACC_ACDCACurrX_A = rtb_Switch6_j;
  } else {
    LcEACC_ACDCACurrX_A = EACC_ZERODOTONE_NUMB;
  }

  rtb_GeEACC_ACDCARunMode_enum = EACC_DW.StateName_m;
  if (CbEACC_ACDCAOutCurrReqOvrSwt_flg) {
    set_GcEACC_ACDCAOutCurrReq_A(CcEACC_ACDCAOutCurrReqOvr_A);
  } else if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion8_g)
  {
    if (get_GeEAMM_ACDCAWorkMode_enum() == EACC_ConstB.DataTypeConversion9_b) {
      if ((LcEACC_ACDCAMaxCurr_A <= get_GcECCR_CCU1BCLSPN3073IReq_A()) ||
          rtIsNaNF(get_GcECCR_CCU1BCLSPN3073IReq_A())) {
        set_GcEACC_ACDCAOutCurrReq_A(LcEACC_ACDCAMaxCurr_A);
      } else {
        set_GcEACC_ACDCAOutCurrReq_A(get_GcECCR_CCU1BCLSPN3073IReq_A());
      }
    } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
               EACC_ConstB.DataTypeConversion11_j) {
      if ((LcEACC_ACDCACurrX_A <= LcEACC_ACDCAMaxCurr_A) || rtIsNaNF
          (LcEACC_ACDCAMaxCurr_A)) {
        set_GcEACC_ACDCAOutCurrReq_A(LcEACC_ACDCACurrX_A);
      } else {
        set_GcEACC_ACDCAOutCurrReq_A(LcEACC_ACDCAMaxCurr_A);
      }
    } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
               EACC_ConstB.DataTypeConversion13_d) {
      if ((LcEACC_ACDCAMaxCurr_A <= get_GcEBIM_PackAOutCurrReq_A()) || rtIsNaNF
          (get_GcEBIM_PackAOutCurrReq_A())) {
        set_GcEACC_ACDCAOutCurrReq_A(LcEACC_ACDCAMaxCurr_A);
      } else {
        set_GcEACC_ACDCAOutCurrReq_A(get_GcEBIM_PackAOutCurrReq_A());
      }
    } else {
      set_GcEACC_ACDCAOutCurrReq_A(EACC_Zero_NUMB);
    }
  } else if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion1_p)
  {
    set_GcEACC_ACDCAOutCurrReq_A(EACC_One_NUMB);
  } else {
    set_GcEACC_ACDCAOutCurrReq_A(EACC_Zero_NUMB);
  }

  if (get_GeEAMM_ACDCAWorkMode_enum() == EACC_ConstB.DataTypeConversion1_e) {
    if ((get_GcEDCC_DCDCAOutVoltReq_V() <= get_GcEBSW_DCDCAOutVolt_V()) ||
        rtIsNaNF(get_GcEBSW_DCDCAOutVolt_V())) {
      LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEDCC_DCDCAOutVoltReq_V();
    } else {
      LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEBSW_DCDCAOutVolt_V();
    }
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion3_b) {
    if ((get_GcEDCC_DCDCBOutVoltReq_V() <= get_GcEBSW_DCDCBOutVolt_V()) ||
        rtIsNaNF(get_GcEBSW_DCDCBOutVolt_V())) {
      LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEDCC_DCDCBOutVoltReq_V();
    } else {
      LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEBSW_DCDCBOutVolt_V();
    }
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion5_nv) {
    LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEBCR_PackAOutVolt_V();
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion7_i) {
    LcEACC_PrechrgACDCAOutVoltReq_V = get_GcEBCR_PackBOutVolt_V();
  } else {
    LcEACC_PrechrgACDCAOutVoltReq_V = EACC_Zero_NUMB;
  }

  if (get_GeEAMM_ACDCAWorkMode_enum() == EACC_ConstB.DataTypeConversion9_e) {
    LcEACC_RunACDCAOutVoltReq_V = get_GcEDCC_DCDCAOutVoltReq_V();
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion11_g) {
    LcEACC_RunACDCAOutVoltReq_V = get_GcEDCC_DCDCBOutVoltReq_V();
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion13_m) {
    LcEACC_RunACDCAOutVoltReq_V = get_GcEBIM_PackAOutVoltReq_V();
  } else if (get_GeEAMM_ACDCAWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion15_e) {
    LcEACC_RunACDCAOutVoltReq_V = get_GcEBIM_PackBOutVoltReq_V();
  } else {
    LcEACC_RunACDCAOutVoltReq_V = EACC_Zero_NUMB;
  }

  if (CbEACC_ACDCAOutVoltReqOvrSwt_flg) {
    set_GcEACC_ACDCAOutVoltReq_V(CcEACC_ACDCAOutVoltReqOvr_V);
  } else if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion_l) {
    set_GcEACC_ACDCAOutVoltReq_V(LcEACC_PrechrgACDCAOutVoltReq_V);
  } else if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion8_f)
  {
    set_GcEACC_ACDCAOutVoltReq_V(LcEACC_RunACDCAOutVoltReq_V);
  } else {
    set_GcEACC_ACDCAOutVoltReq_V(EACC_Zero_NUMB);
  }

  EACC_Delay(get_GcEACC_ACDCAOutVoltReq_V() >= EACC_ZERODOTONE_NUMB,
             CcEACC_ACDCAPwrOnDelayT_ms, &EACC_B.Delay, &EACC_DW.Delay);
  EACC_Delay1(((real32_T)fabs(get_GcEACC_ACDCAOutVoltReq_V()) <
               EACC_ZERODOTONE_NUMB) && ((real32_T)fabs
    (get_GcEACC_ACDCAOutCurrReq_A()) < EACC_ZERODOTONE_NUMB),
              CcEACC_ACDCAPwrOffDelayT_ms, &EACC_B.Delay1, &EACC_DW.Delay1);
  if (EACC_B.Delay.RelationalOperator) {
    rtb_Switch8_c = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACC_B.Delay1.RelationalOperator) {
    rtb_Switch8_c = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch8_c = EACC_DW.StateName_a0;
  }

  if (CbEACC_ACDCAPwrCmdOvrSwt_flg) {
    set_GbEACC_ACDCAPwrCmd_flg(CbEACC_ACDCAPwrCmdOvr_flg);
  } else {
    set_GbEACC_ACDCAPwrCmd_flg(rtb_Switch8_c);
  }

  LbEACC_ACDCAWork_flg = ((get_GbEBSW_T645ThreePhaseOnline_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEBSW_ACDCATimeOut_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GeEBSW_ACDCAFltLvl_enum() <
                        CcEACC_AllowACDCAWorkFltLvl_numb));
  if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion_g) {
    if (!EACC_DW.OfflineWork_MODE_i) {
      EACC_DW.FixPtUnitDelay2_DSTATE_d = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE_i = 0U;
      EACC_DW.OfflineWork_MODE_i = true;
    }

    rtb_LogicalOperator_k = (LbEACC_ACDCAWork_flg != ((boolean_T)ASWTYPE_TRUE));
    if (rtb_LogicalOperator_k || (EACC_DW.FixPtUnitDelay2_DSTATE_d != 0)) {
      rtb_Init_n = 0U;
    } else {
      rtb_Init_n = EACC_DW.FixPtUnitDelay1_DSTATE_i;
    }

    LbEACC_ACDCAOfflineToStandby_flg = (rtb_Init_n >= CcEACC_AOffToStdbDelayT_ms);
    if (rtb_LogicalOperator_k) {
      EACC_DW.FixPtUnitDelay1_DSTATE_i = 0U;
    } else {
      if (LbEACC_ACDCAOfflineToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE_i = (uint16_T)((uint32_T)tmp + rtb_Init_n);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE_d = 0U;
  } else {
    if (EACC_DW.OfflineWork_MODE_i) {
      LbEACC_ACDCAOfflineToStandby_flg = false;
      EACC_DW.OfflineWork_MODE_i = false;
    }
  }

  if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion_mq) {
    if (!EACC_DW.StandbyWork_MODE_f) {
      EACC_DW.FixPtUnitDelay2_DSTATE_p = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE_b = 0U;
      EACC_DW.StandbyWork_MODE_f = true;
    }

    rtb_LogicalOperator_k = (LbEACC_ACDCAWork_flg != ((boolean_T)ASWTYPE_FALSE));
    if (rtb_LogicalOperator_k || (EACC_DW.FixPtUnitDelay2_DSTATE_p != 0)) {
      rtb_Init_n = 0U;
    } else {
      rtb_Init_n = EACC_DW.FixPtUnitDelay1_DSTATE_b;
    }

    LbEACC_ACDCAStandbyToOffline_flg = (rtb_Init_n >= CcEACC_AStdbToOffDelayT_ms);
    if (rtb_LogicalOperator_k) {
      EACC_DW.FixPtUnitDelay1_DSTATE_b = 0U;
    } else {
      if (LbEACC_ACDCAStandbyToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE_b = (uint16_T)((uint32_T)tmp + rtb_Init_n);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE_p = 0U;
    LbEACC_ACDCAStandbyToPrechrg_flg = ((get_GeEAMM_ACDCAWorkMode_enum() !=
      EACC_ConstB.DataTypeConversion_fg) && (LbEACC_ACDCAWork_flg == ((boolean_T)
      ASWTYPE_TRUE)));
  } else {
    if (EACC_DW.StandbyWork_MODE_f) {
      LbEACC_ACDCAStandbyToOffline_flg = false;
      EACC_DW.StandbyWork_MODE_f = false;
    }
  }

  if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion_om) {
    if (!EACC_DW.PrechrgWork_MODE_g) {
      EACC_DW.FixPtUnitDelay2_DSTATE_e = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE_gn = 0U;
      EACC_DW.PrechrgWork_MODE_g = true;
    }

    rtb_LogicalOperator_k = !((get_GeEAMM_ACDCAWorkMode_enum() ==
      EACC_ConstB.DataTypeConversion_i3) || (LbEACC_ACDCAWork_flg == ((boolean_T)
      ASWTYPE_FALSE)));
    if (rtb_LogicalOperator_k || (EACC_DW.FixPtUnitDelay2_DSTATE_e != 0)) {
      rtb_Init_a = 0U;
    } else {
      rtb_Init_a = EACC_DW.FixPtUnitDelay1_DSTATE_gn;
    }

    LbEACC_ACDCAPrechrgToStandby_flg = (rtb_Init_a >=
      CcEACC_APChrgToStdbDelayT_ms);
    if (rtb_LogicalOperator_k) {
      EACC_DW.FixPtUnitDelay1_DSTATE_gn = 0U;
    } else {
      if (LbEACC_ACDCAPrechrgToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE_gn = (uint8_T)((uint32_T)tmp + rtb_Init_a);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE_e = 0U;
    LbEACC_ACDCAPrechrgToRun_flg = (((get_GeECMM_ChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion_cf) && (get_GeECTC_ReChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion1_nd)) || ((get_GeECMM_ChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion2_e) && (get_GeECTC_CChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion3_d)) || ((get_GeECMM_ChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion4_c) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion5_n)) || ((get_GeECMM_ChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion6_p) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion7_jp)));
  } else {
    if (EACC_DW.PrechrgWork_MODE_g) {
      EACC_DW.PrechrgWork_MODE_g = false;
    }
  }

  if (rtb_GeEACC_ACDCARunMode_enum == EACC_ConstB.DataTypeConversion_dd) {
    if (!EACC_DW.RunWork_MODE_f) {
      EACC_DW.RunWork_MODE_f = true;
    }

    LbEACC_ACDCARunToStandby_flg = ((get_GeEAMM_ACDCAWorkMode_enum() ==
      EACC_ConstB.DataTypeConversion_b) || (LbEACC_ACDCAWork_flg == ((boolean_T)
      ASWTYPE_FALSE)));
  } else {
    if (EACC_DW.RunWork_MODE_f) {
      LbEACC_ACDCARunToStandby_flg = false;
      EACC_DW.RunWork_MODE_f = false;
    }
  }

  if (EACC_DW.is_active_c4_EACC == 0U) {
    EACC_DW.is_active_c4_EACC = 1U;
    EACC_DW.is_c4_EACC = EACC_IN_Offline;
    EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Offline;
  } else {
    switch (EACC_DW.is_c4_EACC) {
     case EACC_IN_Offline:
      if (LbEACC_ACDCAOfflineToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c4_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Standby;
      }
      break;

     case EACC_IN_Prechrg:
      if (LbEACC_ACDCAPrechrgToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c4_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Standby;
      } else {
        if (LbEACC_ACDCAPrechrgToRun_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EACC_DW.is_c4_EACC = EACC_IN_Run;
          EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Run;
        }
      }
      break;

     case EACC_IN_Run:
      if (LbEACC_ACDCARunToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c4_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Standby;
      }
      break;

     default:
      if (LbEACC_ACDCAStandbyToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c4_EACC = EACC_IN_Offline;
        EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)Enum_EACCACDCARunMode_Offline;
      } else {
        if (LbEACC_ACDCAStandbyToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EACC_DW.is_c4_EACC = EACC_IN_Prechrg;
          EACC_B.GeEACC_ACDCARunMode_enum = (uint8_T)
            Enum_EACCACDCARunMode_Prechrg;
        }
      }
      break;
    }
  }

  if (CbEACC_ACDCARunModeOvrSwt_flg) {
    set_GeEACC_ACDCARunMode_enum(CeEACC_ACDCARunModeOvr_enum);
  } else {
    set_GeEACC_ACDCARunMode_enum(EACC_B.GeEACC_ACDCARunMode_enum);
  }

  EACC_DW.StateName_f = LcEACC_ACDCATempFltPwr_kw;
  EACC_DW.StateName_h = LcEACC_ACDCAScreenInputPwr_kw;
  EACC_DW.StateName_m = get_GeEACC_ACDCARunMode_enum();
  EACC_DW.StateName_a0 = rtb_Switch8_c;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EACCB_20ms_at_outport_1' */
void EACCB_20ms(void)
{
  uint8_T rtb_GeEACC_ACDCBRunMode_enum;
  boolean_T rtb_Switch8_m;
  boolean_T rtb_LogicalOperator_m;
  uint16_T rtb_Init_h;
  uint8_T rtb_Init_f;
  real32_T rtb_Switch6;
  uint8_T tmp;
  LbEACC_ACDCBWork_flg = ((get_GbEBSW_T645ThreePhaseOnline_flg() == ((boolean_T)
    ASWTYPE_TRUE)) && (get_GbEBSW_ACDCBTimeOut_flg() == ((boolean_T)
    ASWTYPE_FALSE)) && (get_GeEBSW_ACDCBFltLvl_enum() <
                        CcEACC_AllowACDCBWorkFltLvl_numb));
  LcEACC_ACDCBTempPwr_kw = look1_iflf_binlxpw(get_GcEBSW_ACDCBWaterTemp_C(),
    ((real32_T *)&(CaEACC_ACDCBWaterTemp_C[0])), ((real32_T *)
    &(CaEACC_ACDCBTempPwrTable_kw[0])), 6U);
  if (get_GeEBSW_ACDCBFltLvl_enum() == EACC_ConstB.DataTypeConversion) {
    LcEACC_ACDCBTempFltPwr_kw = LcEACC_ACDCBTempPwr_kw;
  } else if (get_GeEBSW_ACDCBFltLvl_enum() == EACC_ConstB.DataTypeConversion1) {
    LcEACC_ACDCBTempFltPwr_kw = LcEACC_ACDCBTempPwr_kw / (real32_T)EACC_Two_NUMB;
  } else if (get_GeEBSW_ACDCBFltLvl_enum() >= EACC_ConstB.DataTypeConversion2) {
    LcEACC_ACDCBTempFltPwr_kw = EACC_Zero_NUMB;
  } else {
    LcEACC_ACDCBTempFltPwr_kw = EACC_DW.StateName;
  }

  if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion3) {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_11_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion4) {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_33p_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion5) {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_7_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion6) {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_20_kw;
  } else if (get_GcEBSW_ACDCMaxPwr_enum() == EACC_ConstB.DataTypeConversion7) {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_40_kw;
  } else {
    LcEACC_ACDCBScreenInputPwr_kw = EACC_DW.StateName_c;
  }

  if ((LcEACC_ACDCBTempFltPwr_kw <= LcEACC_ACDCBScreenInputPwr_kw) || rtIsNaNF
      (LcEACC_ACDCBScreenInputPwr_kw)) {
    LcEACC_ACDCBMaxPwr_kw = LcEACC_ACDCBTempFltPwr_kw;
  } else {
    LcEACC_ACDCBMaxPwr_kw = LcEACC_ACDCBScreenInputPwr_kw;
  }

  rtb_Switch6 = LcEACC_ACDCBMaxPwr_kw * CcEACC_Ratio1000_R /
    get_GcEBSW_ACDCBOutVolt_V();
  if (!(rtb_Switch6 <= CcEACC_ACDCBCalCurr_A)) {
    rtb_Switch6 = CcEACC_ACDCBCalCurr_A;
  }

  LcEACC_ACDCBMaxCurr_A = rtb_Switch6 * CcEACC_ACDCBCurrRatio_R * (real32_T)
    CcEACC_ACDCBSum_numb;
  rtb_Switch6 = get_GcECCR_CCU1BCLSPN3073IReq_A() - get_GcEACC_ACDCAOutCurrReq_A
    ();
  if (rtb_Switch6 >= EACC_ZERODOTONE_NUMB) {
    LcEACC_ACDCBCurrX_A = rtb_Switch6;
  } else {
    LcEACC_ACDCBCurrX_A = EACC_ZERODOTONE_NUMB;
  }

  rtb_GeEACC_ACDCBRunMode_enum = EACC_DW.StateName_a;
  if (CbEACC_ACDCBOutCurrReqOvrSwt_flg) {
    set_GcEACC_ACDCBOutCurrReq_A(CcEACC_ACDCBOutCurrReqOvr_A);
  } else if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion8) {
    if (get_GeEAMM_ACDCBWorkMode_enum() == EACC_ConstB.DataTypeConversion9) {
      if ((LcEACC_ACDCBMaxCurr_A <= get_GcECCR_CCU2BCLSPN3073IReq_A()) ||
          rtIsNaNF(get_GcECCR_CCU2BCLSPN3073IReq_A())) {
        set_GcEACC_ACDCBOutCurrReq_A(LcEACC_ACDCBMaxCurr_A);
      } else {
        set_GcEACC_ACDCBOutCurrReq_A(get_GcECCR_CCU2BCLSPN3073IReq_A());
      }
    } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
               EACC_ConstB.DataTypeConversion11) {
      if ((LcEACC_ACDCBCurrX_A <= LcEACC_ACDCBMaxCurr_A) || rtIsNaNF
          (LcEACC_ACDCBMaxCurr_A)) {
        set_GcEACC_ACDCBOutCurrReq_A(LcEACC_ACDCBCurrX_A);
      } else {
        set_GcEACC_ACDCBOutCurrReq_A(LcEACC_ACDCBMaxCurr_A);
      }
    } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
               EACC_ConstB.DataTypeConversion13) {
      if ((LcEACC_ACDCBMaxCurr_A <= get_GcEBIM_PackBOutCurrReq_A()) || rtIsNaNF
          (get_GcEBIM_PackBOutCurrReq_A())) {
        set_GcEACC_ACDCBOutCurrReq_A(LcEACC_ACDCBMaxCurr_A);
      } else {
        set_GcEACC_ACDCBOutCurrReq_A(get_GcEBIM_PackBOutCurrReq_A());
      }
    } else {
      set_GcEACC_ACDCBOutCurrReq_A(EACC_Zero_NUMB);
    }
  } else if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion1_n)
  {
    set_GcEACC_ACDCBOutCurrReq_A(EACC_One_NUMB);
  } else {
    set_GcEACC_ACDCBOutCurrReq_A(EACC_Zero_NUMB);
  }

  if (get_GeEAMM_ACDCBWorkMode_enum() == EACC_ConstB.DataTypeConversion1_m) {
    if ((get_GcEDCC_DCDCAOutVoltReq_V() <= get_GcEBSW_DCDCAOutVolt_V()) ||
        rtIsNaNF(get_GcEBSW_DCDCAOutVolt_V())) {
      LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEDCC_DCDCAOutVoltReq_V();
    } else {
      LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEBSW_DCDCAOutVolt_V();
    }
  } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion3_o) {
    if ((get_GcEDCC_DCDCBOutVoltReq_V() <= get_GcEBSW_DCDCBOutVolt_V()) ||
        rtIsNaNF(get_GcEBSW_DCDCBOutVolt_V())) {
      LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEDCC_DCDCBOutVoltReq_V();
    } else {
      LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEBSW_DCDCBOutVolt_V();
    }
  } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion5_k) {
    LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEBCR_PackAOutVolt_V();
  } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion7_j) {
    LcEACC_PrechrgACDCBOutVoltReq_V = get_GcEBCR_PackBOutVolt_V();
  } else {
    LcEACC_PrechrgACDCBOutVoltReq_V = EACC_Zero_NUMB;
  }

  if (get_GeEAMM_ACDCBWorkMode_enum() == EACC_ConstB.DataTypeConversion9_p) {
    LcEACC_RunACDCBOutVoltReq_V = get_GcEDCC_DCDCAOutVoltReq_V();
  } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion11_m) {
    LcEACC_RunACDCBOutVoltReq_V = get_GcEDCC_DCDCBOutVoltReq_V();
  } else if (get_GeEAMM_ACDCBWorkMode_enum() ==
             EACC_ConstB.DataTypeConversion13_e) {
    LcEACC_RunACDCBOutVoltReq_V = get_GcEBIM_PackAOutVoltReq_V();
  } else if (get_GeEAMM_ACDCBWorkMode_enum() == EACC_ConstB.DataTypeConversion15)
  {
    LcEACC_RunACDCBOutVoltReq_V = get_GcEBIM_PackBOutVoltReq_V();
  } else {
    LcEACC_RunACDCBOutVoltReq_V = EACC_Zero_NUMB;
  }

  if (CbEACC_ACDCBOutVoltReqOvrSwt_flg) {
    set_GcEACC_ACDCBOutVoltReq_V(CcEACC_ACDCBOutVoltReqOvr_V);
  } else if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion_p5)
  {
    set_GcEACC_ACDCBOutVoltReq_V(LcEACC_PrechrgACDCBOutVoltReq_V);
  } else if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion8_k)
  {
    set_GcEACC_ACDCBOutVoltReq_V(LcEACC_RunACDCBOutVoltReq_V);
  } else {
    set_GcEACC_ACDCBOutVoltReq_V(EACC_Zero_NUMB);
  }

  EACC_Delay(get_GcEACC_ACDCBOutVoltReq_V() >= EACC_ZERODOTONE_NUMB,
             CcEACC_ACDCAPwrOnDelayT_ms, &EACC_B.Delay_d, &EACC_DW.Delay_d);
  EACC_Delay1(((real32_T)fabs(get_GcEACC_ACDCBOutVoltReq_V()) <
               EACC_ZERODOTONE_NUMB) && ((real32_T)fabs
    (get_GcEACC_ACDCBOutCurrReq_A()) < EACC_ZERODOTONE_NUMB),
              CcEACC_ACDCAPwrOffDelayT_ms, &EACC_B.Delay1_p, &EACC_DW.Delay1_p);
  if (EACC_B.Delay_d.RelationalOperator) {
    rtb_Switch8_m = ((boolean_T)ASWTYPE_TRUE);
  } else if (EACC_B.Delay1_p.RelationalOperator) {
    rtb_Switch8_m = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch8_m = EACC_DW.StateName_hu;
  }

  if (CbEACC_ACDCBPwrCmdOvrSwt_flg) {
    set_GbEACC_ACDCBPwrCmd_flg(CbEACC_ACDCBPwrCmdOvr_flg);
  } else {
    set_GbEACC_ACDCBPwrCmd_flg(rtb_Switch8_m);
  }

  if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion_m) {
    if (!EACC_DW.OfflineWork_MODE) {
      EACC_DW.FixPtUnitDelay2_DSTATE_j = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE_f = 0U;
      EACC_DW.OfflineWork_MODE = true;
    }

    rtb_LogicalOperator_m = (LbEACC_ACDCBWork_flg != ((boolean_T)ASWTYPE_TRUE));
    if (rtb_LogicalOperator_m || (EACC_DW.FixPtUnitDelay2_DSTATE_j != 0)) {
      rtb_Init_h = 0U;
    } else {
      rtb_Init_h = EACC_DW.FixPtUnitDelay1_DSTATE_f;
    }

    LbEACC_ACDCBOfflineToStandby_flg = (rtb_Init_h >= CcEACC_BOffToStdbDelayT_ms);
    if (rtb_LogicalOperator_m) {
      EACC_DW.FixPtUnitDelay1_DSTATE_f = 0U;
    } else {
      if (LbEACC_ACDCBOfflineToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE_f = (uint16_T)((uint32_T)tmp + rtb_Init_h);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE_j = 0U;
  } else {
    if (EACC_DW.OfflineWork_MODE) {
      LbEACC_ACDCBOfflineToStandby_flg = false;
      EACC_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion_c) {
    if (!EACC_DW.StandbyWork_MODE) {
      EACC_DW.FixPtUnitDelay2_DSTATE = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE = 0U;
      EACC_DW.StandbyWork_MODE = true;
    }

    rtb_LogicalOperator_m = (LbEACC_ACDCBWork_flg != ((boolean_T)ASWTYPE_FALSE));
    if (rtb_LogicalOperator_m || (EACC_DW.FixPtUnitDelay2_DSTATE != 0)) {
      rtb_Init_h = 0U;
    } else {
      rtb_Init_h = EACC_DW.FixPtUnitDelay1_DSTATE;
    }

    LbEACC_ACDCBStandbyToOffline_flg = (rtb_Init_h >= CcEACC_BStdbToOffDelayT_ms);
    if (rtb_LogicalOperator_m) {
      EACC_DW.FixPtUnitDelay1_DSTATE = 0U;
    } else {
      if (LbEACC_ACDCBStandbyToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_h);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE = 0U;
    LbEACC_ACDCBStandbyToPrechrg_flg = ((LbEACC_ACDCBWork_flg == ((boolean_T)
      ASWTYPE_TRUE)) && (get_GeEAMM_ACDCBWorkMode_enum() !=
                         EACC_ConstB.DataTypeConversion_d));
  } else {
    if (EACC_DW.StandbyWork_MODE) {
      LbEACC_ACDCBStandbyToOffline_flg = false;
      EACC_DW.StandbyWork_MODE = false;
    }
  }

  if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion_p) {
    if (!EACC_DW.PrechrgWork_MODE) {
      EACC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
      EACC_DW.FixPtUnitDelay1_DSTATE_g = 0U;
      EACC_DW.PrechrgWork_MODE = true;
    }

    rtb_LogicalOperator_m = !((get_GeEAMM_ACDCBWorkMode_enum() ==
      EACC_ConstB.DataTypeConversion_f) || (LbEACC_ACDCBWork_flg == ((boolean_T)
      ASWTYPE_FALSE)));
    if (rtb_LogicalOperator_m || (EACC_DW.FixPtUnitDelay2_DSTATE_n != 0)) {
      rtb_Init_f = 0U;
    } else {
      rtb_Init_f = EACC_DW.FixPtUnitDelay1_DSTATE_g;
    }

    LbEACC_ACDCBPrechrgToStandby_flg = (rtb_Init_f >=
      CcEACC_BPChrgToStdbDelayT_ms);
    if (rtb_LogicalOperator_m) {
      EACC_DW.FixPtUnitDelay1_DSTATE_g = 0U;
    } else {
      if (LbEACC_ACDCBPrechrgToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EACC_RUNTIME_MS;
      }

      EACC_DW.FixPtUnitDelay1_DSTATE_g = (uint8_T)((uint32_T)tmp + rtb_Init_f);
    }

    EACC_DW.FixPtUnitDelay2_DSTATE_n = 0U;
    LbEACC_ACDCBPrechrgToRun_flg = (((get_GeECMM_ChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion_o) && (get_GeECTC_ReChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion1_b)) || ((get_GeECMM_ChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion2_h) && (get_GeECTC_CChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion3_p)) || ((get_GeECMM_ChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion4_f) && (get_GeECTC_BCChrgCtrBMode_enum() ==
      EACC_ConstB.DataTypeConversion5_e)) || ((get_GeECMM_ChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion6_l) && (get_GeECTC_BCChrgCtrAMode_enum() ==
      EACC_ConstB.DataTypeConversion7_n)));
  } else {
    if (EACC_DW.PrechrgWork_MODE) {
      EACC_DW.PrechrgWork_MODE = false;
    }
  }

  if (rtb_GeEACC_ACDCBRunMode_enum == EACC_ConstB.DataTypeConversion_h) {
    if (!EACC_DW.RunWork_MODE) {
      EACC_DW.RunWork_MODE = true;
    }

    LbEACC_ACDCBRunToStandby_flg = ((get_GeEAMM_ACDCBWorkMode_enum() ==
      EACC_ConstB.DataTypeConversion_i) || (LbEACC_ACDCBWork_flg == ((boolean_T)
      ASWTYPE_FALSE)));
  } else {
    if (EACC_DW.RunWork_MODE) {
      LbEACC_ACDCBRunToStandby_flg = false;
      EACC_DW.RunWork_MODE = false;
    }
  }

  if (EACC_DW.is_active_c3_EACC == 0U) {
    EACC_DW.is_active_c3_EACC = 1U;
    EACC_DW.is_c3_EACC = EACC_IN_Offline;
    EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Offline;
  } else {
    switch (EACC_DW.is_c3_EACC) {
     case EACC_IN_Offline:
      if (LbEACC_ACDCBOfflineToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c3_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Standby;
      }
      break;

     case EACC_IN_Prechrg:
      if (LbEACC_ACDCBPrechrgToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c3_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Standby;
      } else {
        if (LbEACC_ACDCBPrechrgToRun_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EACC_DW.is_c3_EACC = EACC_IN_Run;
          EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Run;
        }
      }
      break;

     case EACC_IN_Run:
      if (LbEACC_ACDCBRunToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c3_EACC = EACC_IN_Standby;
        EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Standby;
      }
      break;

     default:
      if (LbEACC_ACDCBStandbyToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EACC_DW.is_c3_EACC = EACC_IN_Offline;
        EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)Enum_EACCACDCBRunMode_Offline;
      } else {
        if (LbEACC_ACDCBStandbyToPrechrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EACC_DW.is_c3_EACC = EACC_IN_Prechrg;
          EACC_B.GeEACC_ACDCBRunMode_enum = (uint8_T)
            Enum_EACCACDCBRunMode_Prechrg;
        }
      }
      break;
    }
  }

  if (CbEACC_ACDCBRunModeOvrSwt_flg) {
    set_GeEACC_ACDCBRunMode_enum(CeEACC_ACDCBRunModeOvr_enum);
  } else {
    set_GeEACC_ACDCBRunMode_enum(EACC_B.GeEACC_ACDCBRunMode_enum);
  }

  EACC_DW.StateName = LcEACC_ACDCBTempFltPwr_kw;
  EACC_DW.StateName_c = LcEACC_ACDCBScreenInputPwr_kw;
  EACC_DW.StateName_a = get_GeEACC_ACDCBRunMode_enum();
  EACC_DW.StateName_hu = rtb_Switch8_m;
}

/* Model initialize function */
void EACC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  EACC_DW.FixPtUnitDelay2_DSTATE_d = 1U;
  EACC_DW.FixPtUnitDelay2_DSTATE_p = 1U;
  EACC_DW.FixPtUnitDelay2_DSTATE_e = 1U;
  EACC_DW.FixPtUnitDelay2_DSTATE_j = 1U;
  EACC_DW.FixPtUnitDelay2_DSTATE = 1U;
  EACC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
  EACC_Delay_Init(&EACC_DW.Delay);
  EACC_Delay1_Init(&EACC_DW.Delay1);
  EACC_Delay_Init(&EACC_DW.Delay_d);
  EACC_Delay1_Init(&EACC_DW.Delay1_p);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
