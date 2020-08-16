/*
 * File: EDCC.c
 *
 * Code generated for Simulink model 'EDCC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 14:05:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EDCC.h"
#include "EDCC_private.h"

/* Named constants for Chart: '<S4>/DCDCARunMode' */
#define EDCC_IN_Offline                ((uint8_T)1U)
#define EDCC_IN_Run                    ((uint8_T)2U)
#define EDCC_IN_Standby                ((uint8_T)3U)

/* Block signals (auto storage) */
B_EDCC_T EDCC_B;

/* Block states (auto storage) */
DW_EDCC_T EDCC_DW;

/* Real-time model */
RT_MODEL_EDCC_T EDCC_M_;
RT_MODEL_EDCC_T *const EDCC_M = &EDCC_M_;

/*
 * Initial conditions for atomic system:
 *    '<S19>/Delay'
 *    '<S56>/Delay'
 */
void EDCC_Delay_Init(DW_Delay_EDCC_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
  localDW->FixPtUnitDelay1_DSTATE = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S19>/Delay'
 *    '<S56>/Delay'
 */
void EDCC_Delay(boolean_T rtu_Enable, uint16_T rtu_TimeThrld, B_Delay_EDCC_T
                *localB, DW_Delay_EDCC_T *localDW)
{
  boolean_T rtb_LogicalOperator_f;
  uint16_T rtb_Init_i;
  uint8_T tmp;
  rtb_LogicalOperator_f = !rtu_Enable;
  if (rtb_LogicalOperator_f || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_i = 0U;
  } else {
    rtb_Init_i = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_i >= rtu_TimeThrld);
  if (rtb_LogicalOperator_f) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = EDCC_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_i);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/*
 * Initial conditions for atomic system:
 *    '<S10>/Delay'
 *    '<S47>/Delay'
 */
void EDCC_Delay_g_Init(DW_Delay_EDCC_o_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S10>/Delay'
 *    '<S47>/Delay'
 */
void EDCC_Delay_h(boolean_T rtu_Enable, uint8_T rtu_TimeThrld, B_Delay_EDCC_c_T *
                  localB, DW_Delay_EDCC_o_T *localDW)
{
  boolean_T rtb_LogicalOperator_o;
  uint8_T rtb_Init_l;
  uint8_T tmp;
  rtb_LogicalOperator_o = !rtu_Enable;
  if (rtb_LogicalOperator_o || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_l = 0U;
  } else {
    rtb_Init_l = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_l >= rtu_TimeThrld);
  if (rtb_LogicalOperator_o) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = EDCC_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp + rtb_Init_l);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/*
 * Initial conditions for atomic system:
 *    '<S10>/Delay1'
 *    '<S47>/Delay1'
 */
void EDCC_Delay1_Init(DW_Delay1_EDCC_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S10>/Delay1'
 *    '<S47>/Delay1'
 */
void EDCC_Delay1(boolean_T rtu_Enable, uint8_T rtu_TimeThrld, B_Delay1_EDCC_T
                 *localB, DW_Delay1_EDCC_T *localDW)
{
  boolean_T rtb_LogicalOperator_j;
  uint8_T rtb_Init_e;
  uint8_T tmp;
  rtb_LogicalOperator_j = !rtu_Enable;
  if (rtb_LogicalOperator_j || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_e = 0U;
  } else {
    rtb_Init_e = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_e >= rtu_TimeThrld);
  if (rtb_LogicalOperator_j) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = EDCC_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp + rtb_Init_e);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EDCCA_20ms_at_outport_1' */
void EDCCA_20ms(void)
{
  real32_T rtb_Abs;
  uint8_T rtb_GeEDCC_DCDCARunMode_enum;
  boolean_T rtb_LogicalOperator_h;
  uint16_T rtb_Init_n;
  uint8_T tmp;
  rtb_GeEDCC_DCDCARunMode_enum = EDCC_DW.StateName_g;
  if (rtb_GeEDCC_DCDCARunMode_enum == EDCC_ConstB.DataTypeConversion_i) {
    if (!EDCC_DW.OfflineWork_MODE_l) {
      EDCC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
      EDCC_DW.FixPtUnitDelay1_DSTATE_m = 0U;
      EDCC_DW.OfflineWork_MODE_l = true;
    }

    rtb_LogicalOperator_h = !((get_GeEBCR_BMSAMainPosCntStat_enum() ==
      EDCC_ConstB.DataTypeConversion_n) && (get_GeEBCR_BMSAMainNegCntStat_enum()
      == EDCC_ConstB.DataTypeConversion1_m3) && (get_GbEBSW_DCDCATimeOut_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GeEBSW_DCDCAFltLvl_enum() <
      CcEDCC_AllowDCDCAWorkFltLvl_numb));
    if (rtb_LogicalOperator_h || (EDCC_DW.FixPtUnitDelay2_DSTATE_n != 0)) {
      rtb_Init_n = 0U;
    } else {
      rtb_Init_n = EDCC_DW.FixPtUnitDelay1_DSTATE_m;
    }

    LbEDCC_DCDCAOfflineToStandby_flg = (rtb_Init_n >= CcEDCC_AOffToStdbDelayT_ms);
    if (rtb_LogicalOperator_h) {
      EDCC_DW.FixPtUnitDelay1_DSTATE_m = 0U;
    } else {
      if (LbEDCC_DCDCAOfflineToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EDCC_RUNTIME_MS;
      }

      EDCC_DW.FixPtUnitDelay1_DSTATE_m = (uint16_T)((uint32_T)tmp + rtb_Init_n);
    }

    EDCC_DW.FixPtUnitDelay2_DSTATE_n = 0U;
  } else {
    if (EDCC_DW.OfflineWork_MODE_l) {
      LbEDCC_DCDCAOfflineToStandby_flg = false;
      EDCC_DW.OfflineWork_MODE_l = false;
    }
  }

  if (rtb_GeEDCC_DCDCARunMode_enum == EDCC_ConstB.DataTypeConversion_h) {
    if (!EDCC_DW.RunWork_MODE_g) {
      EDCC_Delay_Init(&EDCC_DW.Delay_j);
      EDCC_DW.RunWork_MODE_g = true;
    }

    EDCC_Delay(((get_GcEBSW_DCDCAOutVolt_V() < get_GcECIM_GunAExpOutputVolt_V() *
                 CcEDCC_DCDCAVoltRatio_R) && (get_GeECIM_GunAIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion_fk)) || ((get_GcEBSW_DCDCAOutVolt_V() >
      CcEDCC_DCDCAUnloadVolt_V) && (get_GeECIM_GunAIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion1_o)) || ((get_GcEBSW_DCDCAOutVolt_V() <
      (real32_T)get_GeECIM_GunAIntactMode_enum() * CcEDCC_DCDCAConvRatio_R) &&
                (get_GeECIM_GunAIntactMode_enum() ==
                 EDCC_ConstB.DataTypeConversion2_o)),
               CcEDCC_DCDCAVoltBuildDelayT_ms, &EDCC_B.Delay_j, &EDCC_DW.Delay_j);
    LbEDCC_DCDCARunToStandby_flg = ((EDCC_B.Delay_j.RelationalOperator ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EDCC_DW.RunWork_MODE_g) {
      LbEDCC_DCDCARunToStandby_flg = false;
      EDCC_DW.RunWork_MODE_g = false;
    }
  }

  if (rtb_GeEDCC_DCDCARunMode_enum == EDCC_ConstB.DataTypeConversion_f) {
    if (!EDCC_DW.StandbyWork_MODE_c) {
      EDCC_DW.FixPtUnitDelay2_DSTATE_cb = 1U;
      EDCC_DW.FixPtUnitDelay1_DSTATE_o = 0U;
      EDCC_DW.StandbyWork_MODE_c = true;
    }

    rtb_LogicalOperator_h = !((get_GeEBCR_BMSAMainPosCntStat_enum() ==
      ((boolean_T)ASWTYPE_FALSE)) || (get_GbEBSW_DCDCATimeOut_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GeEBSW_DCDCAFltLvl_enum() >=
      CcEDCC_AllowDCDCAWorkFltLvl_numb));
    if (rtb_LogicalOperator_h || (EDCC_DW.FixPtUnitDelay2_DSTATE_cb != 0)) {
      rtb_Init_n = 0U;
    } else {
      rtb_Init_n = EDCC_DW.FixPtUnitDelay1_DSTATE_o;
    }

    LbEDCC_DCDCAStandbyToOffline_flg = (rtb_Init_n >= CcEDCC_AStdbToOffDelayT_ms);
    if (rtb_LogicalOperator_h) {
      EDCC_DW.FixPtUnitDelay1_DSTATE_o = 0U;
    } else {
      if (LbEDCC_DCDCAStandbyToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = EDCC_RUNTIME_MS;
      }

      EDCC_DW.FixPtUnitDelay1_DSTATE_o = (uint16_T)((uint32_T)tmp + rtb_Init_n);
    }

    EDCC_DW.FixPtUnitDelay2_DSTATE_cb = 0U;
    LbEDCC_DCDCAStandbyToRun_flg = (get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    if (EDCC_DW.StandbyWork_MODE_c) {
      LbEDCC_DCDCAStandbyToOffline_flg = false;
      EDCC_DW.StandbyWork_MODE_c = false;
    }
  }

  kw1 = look1_iflf_binlxpw(get_GcEBSW_DCDCAWaterTemp_C(), ((real32_T *)
    &(CaEDCC_DCDCAWaterTemp_C[0])), ((real32_T *)&(CaEDCC_DCDCATempPwrTable_kw[0])),
    2U);
  kw2 = look1_iflf_binlxpw(get_GcEBSW_DCDCAInVolt_V(), ((real32_T *)
    &(CaEDCC_DCDCAInVoltTable_V[0])), ((real32_T *)
    &(CaEDCC_DCDCAInVoltPwrTable_kw[0])), 9U);
  kw3 = look1_iflf_binlxpw(get_GcEBSW_DCDCAOutVolt_V(), ((real32_T *)
    &(CaEDCC_DCDCAOutVoltTable_V[0])), ((real32_T *)
    &(CaEDCC_DCDCAOutVoltPwrTable_kw[0])), 7U);
  if ((kw1 <= kw2) || rtIsNaNF(kw2)) {
    rtb_Abs = kw1;
  } else {
    rtb_Abs = kw2;
  }

  if ((rtb_Abs <= kw3) || rtIsNaNF(kw3)) {
    LcEDCC_DCDCATablePwr_kw = rtb_Abs;
  } else {
    LcEDCC_DCDCATablePwr_kw = kw3;
  }

  if (get_GeEBSW_DCDCAFltLvl_enum() == EDCC_ConstB.DataTypeConversion_jy) {
    LcEDCC_DCDCAMaxPwr_kw = LcEDCC_DCDCATablePwr_kw;
  } else if (get_GeEBSW_DCDCAFltLvl_enum() == EDCC_ConstB.DataTypeConversion1_aa)
  {
    LcEDCC_DCDCAMaxPwr_kw = LcEDCC_DCDCATablePwr_kw / (real32_T)EDCC_Two_NUMB;
  } else if (get_GeEBSW_DCDCAFltLvl_enum() >= EDCC_ConstB.DataTypeConversion2_h)
  {
    LcEDCC_DCDCAMaxPwr_kw = EDCC_Zero_NUMB;
  } else {
    LcEDCC_DCDCAMaxPwr_kw = EDCC_DW.StateName_c;
  }

  rtb_Abs = LcEDCC_DCDCAMaxPwr_kw * CcEDCC_Ratio1000_R /
    get_GcEBSW_DCDCAOutVolt_V();
  if (!(rtb_Abs <= CcEDCC_DCDCACalCurr_A)) {
    rtb_Abs = CcEDCC_DCDCACalCurr_A;
  }

  LcEDCC_DCDCAMaxCurr_A = rtb_Abs * CcEDCC_DCDCAVoltRatio_R * (real32_T)
    CcEDCC_DCDCASum_numb;
  if (get_GeECIM_GunAIntactMode_enum() == EDCC_ConstB.DataTypeConversion1_m) {
    LcEDCC_PackAConvDCDCAMaxCurr_A = (real32_T)get_GcEBCR_PackALongDisChrgPwr_kw
      () * CcEDCC_Ratio1000_R / get_GcEBSW_DCDCAOutVolt_V() *
      CcEDCC_DCDCAConvRatio_R;
  } else {
    LcEDCC_PackAConvDCDCAMaxCurr_A = EDCC_Zero_NUMB;
  }

  rtb_Abs = (real32_T)get_GcECCR_CCU1BCLSPN3073IReq_A() -
    get_GcEACC_ACDCAOutCurrReq_A();
  if (rtb_Abs >= EDCC_ZERODOTONE_NUMB) {
    LcEDCC_DCDCACurrX_A = rtb_Abs;
  } else {
    LcEDCC_DCDCACurrX_A = EDCC_ZERODOTONE_NUMB;
  }

  rtb_Abs = LcEDCC_DCDCACurrX_A - get_GcEACC_ACDCBOutCurrReq_A();
  if (rtb_Abs >= EDCC_ZERODOTONE_NUMB) {
    LcEDCC_DCDCACurrY_A = rtb_Abs;
  } else {
    LcEDCC_DCDCACurrY_A = EDCC_ZERODOTONE_NUMB;
  }

  if (CbEDCC_DCDCAOutCurrReqOvrSwt_flg) {
    set_GcEDCC_DCDCAOutCurrReq_A(CcEDCC_DCDCAOutCurrReqOvr_A);
  } else {
    rtb_LogicalOperator_h = ((get_GeECIM_GunAIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion1_az) || (get_GeECIM_GunAIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion2_l));
    if (rtb_LogicalOperator_h && (rtb_GeEDCC_DCDCARunMode_enum ==
         EDCC_ConstB.DataTypeConversion3_j)) {
      rtb_Abs = EDCC_One_NUMB;
    } else if ((!rtb_LogicalOperator_h) && (rtb_GeEDCC_DCDCARunMode_enum ==
                EDCC_ConstB.DataTypeConversion8_l)) {
      if (get_GeECMM_ChrgCtrAMode_enum() == EDCC_ConstB.DataTypeConversion9_m) {
        if ((LcEDCC_DCDCAMaxCurr_A <= LcEDCC_PackAConvDCDCAMaxCurr_A) ||
            rtIsNaNF(LcEDCC_PackAConvDCDCAMaxCurr_A)) {
          rtb_Abs = LcEDCC_DCDCAMaxCurr_A;
        } else {
          rtb_Abs = LcEDCC_PackAConvDCDCAMaxCurr_A;
        }

        if (!(rtb_Abs <= get_GcECCR_CCU1BCLSPN3073IReq_A())) {
          rtb_Abs = get_GcECCR_CCU1BCLSPN3073IReq_A();
        }
      } else if (get_GeECMM_ChrgCtrAMode_enum() ==
                 EDCC_ConstB.DataTypeConversion11_p) {
        if ((LcEDCC_DCDCACurrX_A <= LcEDCC_DCDCAMaxCurr_A) || rtIsNaNF
            (LcEDCC_DCDCAMaxCurr_A)) {
          rtb_Abs = LcEDCC_DCDCACurrX_A;
        } else {
          rtb_Abs = LcEDCC_DCDCAMaxCurr_A;
        }

        if (!((rtb_Abs <= LcEDCC_PackAConvDCDCAMaxCurr_A) || rtIsNaNF
              (LcEDCC_PackAConvDCDCAMaxCurr_A))) {
          rtb_Abs = LcEDCC_PackAConvDCDCAMaxCurr_A;
        }
      } else if (get_GeECMM_ChrgCtrAMode_enum() ==
                 EDCC_ConstB.DataTypeConversion13_i) {
        if ((LcEDCC_DCDCACurrY_A <= LcEDCC_DCDCAMaxCurr_A) || rtIsNaNF
            (LcEDCC_DCDCAMaxCurr_A)) {
          rtb_Abs = LcEDCC_DCDCACurrY_A;
        } else {
          rtb_Abs = LcEDCC_DCDCAMaxCurr_A;
        }

        if (!((rtb_Abs <= LcEDCC_PackAConvDCDCAMaxCurr_A) || rtIsNaNF
              (LcEDCC_PackAConvDCDCAMaxCurr_A))) {
          rtb_Abs = LcEDCC_PackAConvDCDCAMaxCurr_A;
        }
      } else {
        rtb_Abs = EDCC_Zero_NUMB;
      }
    } else {
      rtb_Abs = EDCC_Zero_NUMB;
    }

    set_GcEDCC_DCDCAOutCurrReq_A(rtb_Abs);
  }

  if (CbEDCC_DCDCAOutVoltReqOvrSwt_flg) {
    set_GcEDCC_DCDCAOutVoltReq_V(CcEDCC_DCDCAOutVoltReqOvr_V);
  } else if (rtb_GeEDCC_DCDCARunMode_enum == EDCC_ConstB.DataTypeConversion8_h)
  {
    set_GcEDCC_DCDCAOutVoltReq_V(get_GcECIM_GunAExpOutputVolt_V());
  } else {
    set_GcEDCC_DCDCAOutVoltReq_V(EDCC_Zero_NUMB);
  }

  EDCC_Delay_h(get_GcEDCC_DCDCAOutVoltReq_V() >= EDCC_ZERODOTONE_NUMB,
               CcEDCC_DCDCAPwrOnDelayT_ms, &EDCC_B.Delay, &EDCC_DW.Delay);
  EDCC_Delay1(((real32_T)fabs(get_GcEDCC_DCDCAOutVoltReq_V()) <
               EDCC_ZERODOTONE_NUMB) && ((real32_T)fabs
    (get_GcEDCC_DCDCAOutCurrReq_A()) < EDCC_ZERODOTONE_NUMB),
              CcEDCC_DCDCAPwrOffDelayT_ms, &EDCC_B.Delay1, &EDCC_DW.Delay1);
  if (EDCC_B.Delay.RelationalOperator) {
    rtb_LogicalOperator_h = ((boolean_T)ASWTYPE_TRUE);
  } else if (EDCC_B.Delay1.RelationalOperator) {
    rtb_LogicalOperator_h = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_LogicalOperator_h = EDCC_DW.StateName_c5;
  }

  if (CbEDCC_DCDCAPwrCmdOvrSwt_flg) {
    set_GbEDCC_DCDCAPwrCmd_flg(CbEDCC_DCDCAPwrCmdOvr_flg);
  } else {
    set_GbEDCC_DCDCAPwrCmd_flg(rtb_LogicalOperator_h);
  }

  if (EDCC_DW.is_active_c4_EDCC == 0U) {
    EDCC_DW.is_active_c4_EDCC = 1U;
    EDCC_DW.is_c4_EDCC = EDCC_IN_Offline;
    EDCC_B.GeEDCC_DCDCARunMode_enum = (uint8_T)Enum_EDCCDCDCARunMode_Offline;
  } else {
    switch (EDCC_DW.is_c4_EDCC) {
     case EDCC_IN_Offline:
      if (LbEDCC_DCDCAOfflineToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c4_EDCC = EDCC_IN_Standby;
        EDCC_B.GeEDCC_DCDCARunMode_enum = (uint8_T)Enum_EDCCDCDCARunMode_Standby;
      }
      break;

     case EDCC_IN_Run:
      if (LbEDCC_DCDCARunToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c4_EDCC = EDCC_IN_Standby;
        EDCC_B.GeEDCC_DCDCARunMode_enum = (uint8_T)Enum_EDCCDCDCARunMode_Standby;
      }
      break;

     default:
      if (LbEDCC_DCDCAStandbyToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c4_EDCC = EDCC_IN_Offline;
        EDCC_B.GeEDCC_DCDCARunMode_enum = (uint8_T)Enum_EDCCDCDCARunMode_Offline;
      } else {
        if (LbEDCC_DCDCAStandbyToRun_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EDCC_DW.is_c4_EDCC = EDCC_IN_Run;
          EDCC_B.GeEDCC_DCDCARunMode_enum = (uint8_T)Enum_EDCCDCDCARunMode_Run;
        }
      }
      break;
    }
  }

  if (CbEDCC_DCDCARunModeOvrSwt_flg) {
    set_GeEDCC_DCDCARunMode_enum(CeEDCC_DCDCARunModeOvr_enum);
  } else {
    set_GeEDCC_DCDCARunMode_enum(EDCC_B.GeEDCC_DCDCARunMode_enum);
  }

  if (CbEDCC_DCDCAVoltBuildFltOvrSwt_flg) {
    set_GbEDCC_DCDCAVoltBuildFlt_flg(CbEDCC_DCDCAVoltBuildFltOvr_flg);
  } else {
    set_GbEDCC_DCDCAVoltBuildFlt_flg(EDCC_B.Delay_j.RelationalOperator);
  }

  EDCC_DW.StateName_g = get_GeEDCC_DCDCARunMode_enum();
  EDCC_DW.StateName_c = LcEDCC_DCDCAMaxPwr_kw;
  EDCC_DW.StateName_c5 = rtb_LogicalOperator_h;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EDCCB_20ms_at_outport_1' */
void EDCCB_20ms(void)
{
  real32_T rtb_Abs;
  real32_T rtb_Abs1_j;
  uint8_T rtb_GeEDCC_DCDCBRunMode_enum;
  boolean_T rtb_LogicalOperator_c;
  uint16_T rtb_Init_l;
  real32_T rtb_uDLookupTable;
  uint8_T tmp;
  rtb_GeEDCC_DCDCBRunMode_enum = EDCC_DW.StateName_i;
  if (rtb_GeEDCC_DCDCBRunMode_enum == EDCC_ConstB.DataTypeConversion_cg) {
    if (!EDCC_DW.OfflineWork_MODE) {
      EDCC_DW.FixPtUnitDelay2_DSTATE_c = 1U;
      EDCC_DW.FixPtUnitDelay1_DSTATE_p = 0U;
      EDCC_DW.OfflineWork_MODE = true;
    }

    rtb_LogicalOperator_c = !((get_GeEBCR_BMSBMainNegCntStat_enum() ==
      EDCC_ConstB.DataTypeConversion_m) && (get_GeEBCR_BMSBMainNegCntStat_enum()
      == EDCC_ConstB.DataTypeConversion1_a) && (get_GbEBSW_DCDCBTimeOut_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GeEBSW_DCDCBFltLvl_enum() <
      CcEDCC_AllowDCDCBWorkFltLvl_numb));
    if (rtb_LogicalOperator_c || (EDCC_DW.FixPtUnitDelay2_DSTATE_c != 0)) {
      rtb_Init_l = 0U;
    } else {
      rtb_Init_l = EDCC_DW.FixPtUnitDelay1_DSTATE_p;
    }

    LbEDCC_DCDCBOfflineToStandby_flg = (rtb_Init_l >= CcEDCC_BOffToStdbDelayT_ms);
    if (rtb_LogicalOperator_c) {
      EDCC_DW.FixPtUnitDelay1_DSTATE_p = 0U;
    } else {
      if (LbEDCC_DCDCBOfflineToStandby_flg) {
        tmp = 0U;
      } else {
        tmp = EDCC_RUNTIME_MS;
      }

      EDCC_DW.FixPtUnitDelay1_DSTATE_p = (uint16_T)((uint32_T)tmp + rtb_Init_l);
    }

    EDCC_DW.FixPtUnitDelay2_DSTATE_c = 0U;
  } else {
    if (EDCC_DW.OfflineWork_MODE) {
      LbEDCC_DCDCBOfflineToStandby_flg = false;
      EDCC_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeEDCC_DCDCBRunMode_enum == EDCC_ConstB.DataTypeConversion_c) {
    if (!EDCC_DW.RunWork_MODE) {
      EDCC_Delay_Init(&EDCC_DW.Delay_l);
      EDCC_DW.RunWork_MODE = true;
    }

    EDCC_Delay(((get_GcEBSW_DCDCBOutVolt_V() < get_GcECIM_GunBExpOutputVolt_V() *
                 CcEDCC_DCDCBVoltRatio_R) && (get_GeECIM_GunBIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion_b)) || ((get_GcEBSW_DCDCBOutVolt_V() >
      CcEDCC_DCDCBUnloadVolt_V) && (get_GeECIM_GunBIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion1_j)) || ((get_GcEBSW_DCDCBOutVolt_V() <
      get_GcECIM_GunBExpOutputVolt_V() * CcEDCC_DCDCBVoltRatio_R) &&
                (get_GeECIM_GunBIntactMode_enum() ==
                 EDCC_ConstB.DataTypeConversion2_f)),
               CcEDCC_DCDCBVoltBuildDelayT_ms, &EDCC_B.Delay_l, &EDCC_DW.Delay_l);
    LbEDCC_DCDCBRunToStandby_flg = ((EDCC_B.Delay_l.RelationalOperator ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EDCC_DW.RunWork_MODE) {
      LbEDCC_DCDCBRunToStandby_flg = false;
      EDCC_DW.RunWork_MODE = false;
    }
  }

  if (rtb_GeEDCC_DCDCBRunMode_enum == EDCC_ConstB.DataTypeConversion_j) {
    if (!EDCC_DW.StandbyWork_MODE) {
      EDCC_DW.FixPtUnitDelay2_DSTATE = 1U;
      EDCC_DW.FixPtUnitDelay1_DSTATE = 0U;
      EDCC_DW.StandbyWork_MODE = true;
    }

    rtb_LogicalOperator_c = !((get_GeEBCR_BMSBMainNegCntStat_enum() ==
      ((boolean_T)ASWTYPE_FALSE)) || (get_GbEBSW_DCDCBTimeOut_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GeEBSW_DCDCBFltLvl_enum() >=
      CcEDCC_AllowDCDCBWorkFltLvl_numb));
    if (rtb_LogicalOperator_c || (EDCC_DW.FixPtUnitDelay2_DSTATE != 0)) {
      rtb_Init_l = 0U;
    } else {
      rtb_Init_l = EDCC_DW.FixPtUnitDelay1_DSTATE;
    }

    LbEDCC_DCDCBStandbyToOffline_flg = (rtb_Init_l >= CcEDCC_BStdbToOffDelayT_ms);
    if (rtb_LogicalOperator_c) {
      EDCC_DW.FixPtUnitDelay1_DSTATE = 0U;
    } else {
      if (LbEDCC_DCDCBStandbyToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = EDCC_RUNTIME_MS;
      }

      EDCC_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_l);
    }

    EDCC_DW.FixPtUnitDelay2_DSTATE = 0U;
    LbEDCC_DCDCBStandbyToRun_flg = (get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    if (EDCC_DW.StandbyWork_MODE) {
      LbEDCC_DCDCBStandbyToOffline_flg = false;
      EDCC_DW.StandbyWork_MODE = false;
    }
  }

  rtb_uDLookupTable = look1_iflf_binlxpw(get_GcEBSW_DCDCBWaterTemp_C(),
    ((real32_T *)&(CaEDCC_DCDCBWaterTemp_C[0])), ((real32_T *)
    &(CaEDCC_DCDCBTempPwrTable_kw[0])), 2U);
  rtb_Abs1_j = look1_iflf_binlxpw(get_GcEBSW_DCDCBInVolt_V(), ((real32_T *)
    &(CaEDCC_DCDCBInVoltTable_V[0])), ((real32_T *)
    &(CaEDCC_DCDCBInVoltPwrTable_kw[0])), 9U);
  rtb_Abs = look1_iflf_binlxpw(get_GcEBSW_DCDCBOutVolt_V(), ((real32_T *)
    &(CaEDCC_DCDCBOutVoltTable_V[0])), ((real32_T *)
    &(CaEDCC_DCDCBOutVoltPwrTable_kw[0])), 7U);
  if ((rtb_uDLookupTable <= rtb_Abs1_j) || rtIsNaNF(rtb_Abs1_j)) {
    rtb_Abs1_j = rtb_uDLookupTable;
  }

  if ((rtb_Abs1_j <= rtb_Abs) || rtIsNaNF(rtb_Abs)) {
    LcEDCC_DCDCBTablePwr_kw = rtb_Abs1_j;
  } else {
    LcEDCC_DCDCBTablePwr_kw = rtb_Abs;
  }

  if (get_GeEBSW_DCDCBFltLvl_enum() == EDCC_ConstB.DataTypeConversion) {
    LcEDCC_DCDCBMaxPwr_kw = LcEDCC_DCDCBTablePwr_kw;
  } else if (get_GeEBSW_DCDCBFltLvl_enum() == EDCC_ConstB.DataTypeConversion1) {
    LcEDCC_DCDCBMaxPwr_kw = LcEDCC_DCDCBTablePwr_kw / (real32_T)EDCC_Two_NUMB;
  } else if (get_GeEBSW_DCDCBFltLvl_enum() >= EDCC_ConstB.DataTypeConversion2) {
    LcEDCC_DCDCBMaxPwr_kw = EDCC_Zero_NUMB;
  } else {
    LcEDCC_DCDCBMaxPwr_kw = EDCC_DW.StateName;
  }

  rtb_uDLookupTable = LcEDCC_DCDCBMaxPwr_kw * CcEDCC_Ratio1000_R /
    get_GcEBSW_DCDCBOutVolt_V();
  if (!(rtb_uDLookupTable <= CcEDCC_DCDCBCalCurr_A)) {
    rtb_uDLookupTable = CcEDCC_DCDCBCalCurr_A;
  }

  LcEDCC_DCDCBMaxCurr_A = rtb_uDLookupTable * CcEDCC_DCDCBVoltRatio_R *
    (real32_T)CcEDCC_DCDCBSum_numb;
  if (get_GeECIM_GunBIntactMode_enum() == EDCC_ConstB.DataTypeConversion1_e) {
    LcEDCC_PackBConvDCDCBMaxCurr_A = (real32_T)get_GcEBCR_PackBLongDisChrgPwr_kw
      () * CcEDCC_Ratio1000_R / get_GcEBSW_DCDCBOutVolt_V() *
      CcEDCC_DCDCBConvRatio_R;
  } else {
    LcEDCC_PackBConvDCDCBMaxCurr_A = EDCC_Zero_NUMB;
  }

  rtb_Abs = (real32_T)get_GcECCR_CCU2BCLSPN3073IReq_A() -
    get_GcEACC_ACDCBOutCurrReq_A();
  if (rtb_Abs >= EDCC_ZERODOTONE_NUMB) {
    LcEDCC_DCDCBCurrX_A = rtb_Abs;
  } else {
    LcEDCC_DCDCBCurrX_A = EDCC_ZERODOTONE_NUMB;
  }

  rtb_Abs = LcEDCC_DCDCBCurrX_A - get_GcEACC_ACDCAOutCurrReq_A();
  if (rtb_Abs >= EDCC_ZERODOTONE_NUMB) {
    LcEDCC_DCDCBCurrY_A = rtb_Abs;
  } else {
    LcEDCC_DCDCBCurrY_A = EDCC_ZERODOTONE_NUMB;
  }

  if (CbEDCC_DCDCBOutCurrReqOvrSwt_flg) {
    set_GcEDCC_DCDCBOutCurrReq_A(CcEDCC_DCDCBOutCurrReqOvr_A);
  } else {
    rtb_LogicalOperator_c = ((get_GeECIM_GunBIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion2_e) || (get_GeECIM_GunBIntactMode_enum() ==
      EDCC_ConstB.DataTypeConversion3));
    if (rtb_LogicalOperator_c && (rtb_GeEDCC_DCDCBRunMode_enum ==
         EDCC_ConstB.DataTypeConversion4)) {
      rtb_uDLookupTable = EDCC_One_NUMB;
    } else if ((!rtb_LogicalOperator_c) && (rtb_GeEDCC_DCDCBRunMode_enum ==
                EDCC_ConstB.DataTypeConversion5)) {
      if (get_GeECMM_ChrgCtrBMode_enum() == EDCC_ConstB.DataTypeConversion9) {
        if ((LcEDCC_DCDCBMaxCurr_A <= LcEDCC_PackBConvDCDCBMaxCurr_A) ||
            rtIsNaNF(LcEDCC_PackBConvDCDCBMaxCurr_A)) {
          rtb_uDLookupTable = LcEDCC_DCDCBMaxCurr_A;
        } else {
          rtb_uDLookupTable = LcEDCC_PackBConvDCDCBMaxCurr_A;
        }

        if (!(rtb_uDLookupTable <= get_GcECCR_CCU2BCLSPN3073IReq_A())) {
          rtb_uDLookupTable = get_GcECCR_CCU2BCLSPN3073IReq_A();
        }
      } else if (get_GeECMM_ChrgCtrBMode_enum() ==
                 EDCC_ConstB.DataTypeConversion11) {
        if ((LcEDCC_DCDCBCurrX_A <= LcEDCC_DCDCBMaxCurr_A) || rtIsNaNF
            (LcEDCC_DCDCBMaxCurr_A)) {
          rtb_uDLookupTable = LcEDCC_DCDCBCurrX_A;
        } else {
          rtb_uDLookupTable = LcEDCC_DCDCBMaxCurr_A;
        }

        if (!((rtb_uDLookupTable <= LcEDCC_PackBConvDCDCBMaxCurr_A) || rtIsNaNF
              (LcEDCC_PackBConvDCDCBMaxCurr_A))) {
          rtb_uDLookupTable = LcEDCC_PackBConvDCDCBMaxCurr_A;
        }
      } else if (get_GeECMM_ChrgCtrBMode_enum() ==
                 EDCC_ConstB.DataTypeConversion13) {
        if ((LcEDCC_DCDCBCurrY_A <= LcEDCC_DCDCBMaxCurr_A) || rtIsNaNF
            (LcEDCC_DCDCBMaxCurr_A)) {
          rtb_uDLookupTable = LcEDCC_DCDCBCurrY_A;
        } else {
          rtb_uDLookupTable = LcEDCC_DCDCBMaxCurr_A;
        }

        if (!((rtb_uDLookupTable <= LcEDCC_PackBConvDCDCBMaxCurr_A) || rtIsNaNF
              (LcEDCC_PackBConvDCDCBMaxCurr_A))) {
          rtb_uDLookupTable = LcEDCC_PackBConvDCDCBMaxCurr_A;
        }
      } else {
        rtb_uDLookupTable = EDCC_Zero_NUMB;
      }
    } else {
      rtb_uDLookupTable = EDCC_Zero_NUMB;
    }

    set_GcEDCC_DCDCBOutCurrReq_A(rtb_uDLookupTable);
  }

  if (CbEDCC_DCDCBOutVoltReqOvrSwt_flg) {
    set_GcEDCC_DCDCBOutVoltReq_V(CcEDCC_DCDCBOutVoltReqOvr_V);
  } else if (rtb_GeEDCC_DCDCBRunMode_enum == EDCC_ConstB.DataTypeConversion8) {
    set_GcEDCC_DCDCBOutVoltReq_V(get_GcECIM_GunBExpOutputVolt_V());
  } else {
    set_GcEDCC_DCDCBOutVoltReq_V(EDCC_Zero_NUMB);
  }

  EDCC_Delay_h(get_GcEDCC_DCDCBOutVoltReq_V() >= EDCC_ZERODOTONE_NUMB,
               CcEDCC_DCDCBPwrOnDelayT_ms, &EDCC_B.Delay_jd, &EDCC_DW.Delay_jd);
  EDCC_Delay1(((real32_T)fabs(get_GcEDCC_DCDCBOutVoltReq_V()) <
               EDCC_ZERODOTONE_NUMB) && ((real32_T)fabs
    (get_GcEDCC_DCDCBOutCurrReq_A()) < EDCC_ZERODOTONE_NUMB),
              CcEDCC_DCDCBPwrOffDelayT_ms, &EDCC_B.Delay1_d, &EDCC_DW.Delay1_d);
  if (EDCC_B.Delay_jd.RelationalOperator) {
    rtb_LogicalOperator_c = ((boolean_T)ASWTYPE_TRUE);
  } else if (EDCC_B.Delay1_d.RelationalOperator) {
    rtb_LogicalOperator_c = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_LogicalOperator_c = EDCC_DW.StateName_p;
  }

  if (CbEDCC_DCDCBPwrCmdOvrSwt_flg) {
    set_GbEDCC_DCDCBPwrCmd_flg(CbEDCC_DCDCBPwrCmdOvr_flg);
  } else {
    set_GbEDCC_DCDCBPwrCmd_flg(rtb_LogicalOperator_c);
  }

  if (EDCC_DW.is_active_c2_EDCC == 0U) {
    EDCC_DW.is_active_c2_EDCC = 1U;
    EDCC_DW.is_c2_EDCC = EDCC_IN_Offline;
    EDCC_B.GeEDCC_DCDCBRunMode_enum = (uint8_T)Enum_EDCCDCDCBRunMode_Offline;
  } else {
    switch (EDCC_DW.is_c2_EDCC) {
     case EDCC_IN_Offline:
      if (LbEDCC_DCDCBOfflineToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c2_EDCC = EDCC_IN_Standby;
        EDCC_B.GeEDCC_DCDCBRunMode_enum = (uint8_T)Enum_EDCCDCDCBRunMode_Standby;
      }
      break;

     case EDCC_IN_Run:
      if (LbEDCC_DCDCBRunToStandby_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c2_EDCC = EDCC_IN_Standby;
        EDCC_B.GeEDCC_DCDCBRunMode_enum = (uint8_T)Enum_EDCCDCDCBRunMode_Standby;
      }
      break;

     default:
      if (LbEDCC_DCDCBStandbyToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EDCC_DW.is_c2_EDCC = EDCC_IN_Offline;
        EDCC_B.GeEDCC_DCDCBRunMode_enum = (uint8_T)Enum_EDCCDCDCBRunMode_Offline;
      } else {
        if (LbEDCC_DCDCBStandbyToRun_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EDCC_DW.is_c2_EDCC = EDCC_IN_Run;
          EDCC_B.GeEDCC_DCDCBRunMode_enum = (uint8_T)Enum_EDCCDCDCBRunMode_Run;
        }
      }
      break;
    }
  }

  if (CbEDCC_DCDCBRunModeOvrSwt_flg) {
    set_GeEDCC_DCDCBRunMode_enum(CeEDCC_DCDCBRunModeOvr_enum);
  } else {
    set_GeEDCC_DCDCBRunMode_enum(EDCC_B.GeEDCC_DCDCBRunMode_enum);
  }

  if (CbEDCC_DCDCBVoltBuildFltOvrSwt_flg) {
    set_GbEDCC_DCDCBVoltBuildFlt_flg(CbEDCC_DCDCBVoltBuildFltOvr_flg);
  } else {
    set_GbEDCC_DCDCBVoltBuildFlt_flg(EDCC_B.Delay_l.RelationalOperator);
  }

  EDCC_DW.StateName_i = get_GeEDCC_DCDCBRunMode_enum();
  EDCC_DW.StateName = LcEDCC_DCDCBMaxPwr_kw;
  EDCC_DW.StateName_p = rtb_LogicalOperator_c;
}

/* Model initialize function */
void EDCC_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  EDCC_DW.FixPtUnitDelay2_DSTATE_n = 1U;
  EDCC_Delay_Init(&EDCC_DW.Delay_j);
  EDCC_DW.FixPtUnitDelay2_DSTATE_cb = 1U;
  EDCC_DW.FixPtUnitDelay2_DSTATE_c = 1U;
  EDCC_Delay_Init(&EDCC_DW.Delay_l);
  EDCC_DW.FixPtUnitDelay2_DSTATE = 1U;
  EDCC_Delay_g_Init(&EDCC_DW.Delay);
  EDCC_Delay1_Init(&EDCC_DW.Delay1);
  EDCC_Delay_g_Init(&EDCC_DW.Delay_jd);
  EDCC_Delay1_Init(&EDCC_DW.Delay1_d);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
