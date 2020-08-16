/*
 * File: EHVS.c
 *
 * Code generated for Simulink model 'EHVS'.
 *
 * Company                        : DP
 * Author                         : wxf
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 28 09:28:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EHVS.h"
#include "EHVS_private.h"

/* Named constants for Chart: '<S3>/EMSHighVoltSupply' */
#define EHVS_IN_LineA                  ((uint8_T)1U)
#define EHVS_IN_LineB                  ((uint8_T)2U)
#define EHVS_IN_Offline                ((uint8_T)3U)
#define EHVS_IN_SLVS                   ((uint8_T)4U)

/* Block signals (auto storage) */
B_EHVS_T EHVS_B;

/* Block states (auto storage) */
DW_EHVS_T EHVS_DW;

/* Real-time model */
RT_MODEL_EHVS_T EHVS_M_;
RT_MODEL_EHVS_T *const EHVS_M = &EHVS_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EHVS_10ms_at_outport_1' */
void EHVS_10ms(void)
{
  uint8_T rtb_GeEHVS_HVSState_enum;
  boolean_T rtb_RelationalOperator_hw;
  boolean_T rtb_LogicalOperator_k;
  uint16_T rtb_Init_j;
  boolean_T rtb_Switch2_idx_0;
  boolean_T rtb_Switch2_idx_1;
  boolean_T rtb_Switch1_a_idx_2;
  boolean_T rtb_Switch1_a_idx_3;
  uint8_T rtb_RelationalOperator_k;
  rtb_GeEHVS_HVSState_enum = EHVS_DW.StateName;
  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion_gt) {
    if (!EHVS_DW.OfflineWork_MODE) {
      EHVS_DW.OfflineWork_MODE = true;
    }

    LbEHVS_OfflineToLineA_flg = ((get_GbEDEC_PackAAllowedDisChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcEBCR_BMSARealSOC_pct() >=
      get_GcEBCR_BMSBRealSOC_pct()) && (get_GbEMSM_12VSelfCheckSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEBCR_BMSAMainPosCntStat_enum() ==
      EHVS_ConstB.DataTypeConversion_l) && (get_GeEBCR_BMSAMainNegCntStat_enum()
      == EHVS_ConstB.DataTypeConversion1_bv) &&
      (get_GeEBCR_BMSBMainPosCntStat_enum() == EHVS_ConstB.DataTypeConversion2_i)
      && (get_GeEBCR_BMSBMainNegCntStat_enum() ==
          EHVS_ConstB.DataTypeConversion3_bs));
    LbEHVS_OfflineToLineB_flg = ((get_GbEDEC_PackBAllowedDisChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcEBCR_BMSARealSOC_pct() <
      get_GcEBCR_BMSBRealSOC_pct()) && (get_GbEMSM_12VSelfCheckSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEBCR_BMSAMainPosCntStat_enum() ==
      EHVS_ConstB.DataTypeConversion_j) && (get_GeEBCR_BMSAMainNegCntStat_enum()
      == EHVS_ConstB.DataTypeConversion1_o) &&
      (get_GeEBCR_BMSBMainPosCntStat_enum() ==
       EHVS_ConstB.DataTypeConversion2_fo) &&
      (get_GeEBCR_BMSBMainNegCntStat_enum() == EHVS_ConstB.DataTypeConversion3_m));
  } else {
    if (EHVS_DW.OfflineWork_MODE) {
      LbEHVS_OfflineToLineA_flg = false;
      EHVS_DW.OfflineWork_MODE = false;
    }
  }

  LbEHVS_PackBCondOne_flg = ((get_GeEACC_ACDCARunMode_enum() ==
    EHVS_ConstB.DataTypeConversion) && (get_GeEACC_ACDCBRunMode_enum() ==
    EHVS_ConstB.DataTypeConversion1) && (get_GcEBCR_BMSARealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct) && (get_GcEBCR_BMSBRealSOC_pct() >
    CcEHVS_PackSOC45Percent_pct));
  LbEHVS_PackBCondTwo_flg = ((get_GeEACC_ACDCARunMode_enum() ==
    EHVS_ConstB.DataTypeConversion2) && (get_GeEACC_ACDCBRunMode_enum() !=
    EHVS_ConstB.DataTypeConversion3) && (get_GcEBCR_BMSARealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct));
  LbEHVS_PackBCondThree_flg = ((get_GeEACC_ACDCARunMode_enum() !=
    EHVS_ConstB.DataTypeConversion4) && (get_GeEACC_ACDCBRunMode_enum() !=
    EHVS_ConstB.DataTypeConversion5) && (get_GcEBCR_BMSARealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct) && (get_GcEBCR_BMSBRealSOC_pct() >
    CcEHVS_PackSOC20Percent_pct));
  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion6) {
    LbEHVS_PackBLowPowerSupply_flg = (LbEHVS_PackBCondOne_flg ||
      LbEHVS_PackBCondTwo_flg || LbEHVS_PackBCondThree_flg);
  } else if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion7) {
    LbEHVS_PackBLowPowerSupply_flg = ((boolean_T)ASWTYPE_FALSE);
  } else {
    LbEHVS_PackBLowPowerSupply_flg = EHVS_DW.StateName_h;
  }

  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion_m) {
    if (!EHVS_DW.LineAWork_MODE) {
      EHVS_DW.FixPtUnitDelay2_DSTATE_a = 1U;
      EHVS_DW.FixPtUnitDelay1_DSTATE_o = 0U;
      EHVS_DW.LineAWork_MODE = true;
    }

    rtb_LogicalOperator_k = !((get_GeECCR_CCU1CCUCC1STATE_enum() ==
      EHVS_ConstB.DataTypeConversion1_hr) && (get_GeECCR_CCU2CCUCC1STATE_enum() ==
      EHVS_ConstB.DataTypeConversion2_d) && (LbEHVS_PackBLowPowerSupply_flg ==
      ((boolean_T)ASWTYPE_TRUE)));
    if (rtb_LogicalOperator_k || (EHVS_DW.FixPtUnitDelay2_DSTATE_a != 0)) {
      rtb_Init_j = 0U;
    } else {
      rtb_Init_j = EHVS_DW.FixPtUnitDelay1_DSTATE_o;
    }

    LbEHVS_LineAReadyToChangeState_flg = (rtb_Init_j >=
      CcEHVS_LineAChangeStateDebTime_ms);
    if (rtb_LogicalOperator_k) {
      EHVS_DW.FixPtUnitDelay1_DSTATE_o = 0U;
    } else {
      if (LbEHVS_LineAReadyToChangeState_flg) {
        rtb_RelationalOperator_k = 0U;
      } else {
        rtb_RelationalOperator_k = EHVS_RUNTIME_MS;
      }

      EHVS_DW.FixPtUnitDelay1_DSTATE_o = (uint16_T)((uint32_T)
        rtb_RelationalOperator_k + rtb_Init_j);
    }

    EHVS_DW.FixPtUnitDelay2_DSTATE_a = 0U;
    LbEHVS_LineAToSLVS_flg = ((LbEHVS_LineAReadyToChangeState_flg == ((boolean_T)
      ASWTYPE_TRUE)) || (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
      ASWTYPE_FALSE)) || (get_GbEBSW_UserForceStopPACKA_flg() == ((boolean_T)
      ASWTYPE_TRUE)));
  } else {
    if (EHVS_DW.LineAWork_MODE) {
      EHVS_DW.LineAWork_MODE = false;
    }
  }

  LbEHVS_PackACondOne_flg = ((get_GeEACC_ACDCARunMode_enum() ==
    EHVS_ConstB.DataTypeConversion_g) && (get_GeEACC_ACDCBRunMode_enum() ==
    EHVS_ConstB.DataTypeConversion1_b) && (get_GcEBCR_BMSARealSOC_pct() >
    CcEHVS_PackSOC45Percent_pct) && (get_GcEBCR_BMSBRealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct));
  LbEHVS_PackACondTwo_flg = ((get_GeEACC_ACDCARunMode_enum() !=
    EHVS_ConstB.DataTypeConversion2_c) && (get_GeEACC_ACDCBRunMode_enum() ==
    EHVS_ConstB.DataTypeConversion3_b) && (get_GcEBCR_BMSBRealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct));
  LbEHVS_PackACondThree_flg = ((get_GeEACC_ACDCARunMode_enum() !=
    EHVS_ConstB.DataTypeConversion4_g) && (get_GeEACC_ACDCBRunMode_enum() !=
    EHVS_ConstB.DataTypeConversion5_p) && (get_GcEBCR_BMSARealSOC_pct() >
    CcEHVS_PackSOC20Percent_pct) && (get_GcEBCR_BMSBRealSOC_pct() <
    CcEHVS_PackSOCLowLimit_pct));
  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion6_h) {
    LbEHVS_PackALowPowerSupply_flg = (LbEHVS_PackACondOne_flg ||
      LbEHVS_PackACondTwo_flg || LbEHVS_PackACondThree_flg);
  } else if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion7_b) {
    LbEHVS_PackALowPowerSupply_flg = ((boolean_T)ASWTYPE_FALSE);
  } else {
    LbEHVS_PackALowPowerSupply_flg = EHVS_DW.StateName_b;
  }

  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion_n) {
    if (!EHVS_DW.LineBWork_MODE) {
      EHVS_DW.FixPtUnitDelay2_DSTATE_g = 1U;
      EHVS_DW.FixPtUnitDelay1_DSTATE_e = 0U;
      EHVS_DW.LineBWork_MODE = true;
    }

    rtb_LogicalOperator_k = !((get_GeECCR_CCU1CCUCC1STATE_enum() ==
      EHVS_ConstB.DataTypeConversion1_p) && (get_GeECCR_CCU2CCUCC1STATE_enum() ==
      EHVS_ConstB.DataTypeConversion2_g) && (LbEHVS_PackALowPowerSupply_flg ==
      ((boolean_T)ASWTYPE_TRUE)));
    if (rtb_LogicalOperator_k || (EHVS_DW.FixPtUnitDelay2_DSTATE_g != 0)) {
      rtb_Init_j = 0U;
    } else {
      rtb_Init_j = EHVS_DW.FixPtUnitDelay1_DSTATE_e;
    }

    LbEHVS_LineBReadyToChangeState_flg = (rtb_Init_j >=
      CcEHVS_LineBChangeStateDebTime_ms);
    if (rtb_LogicalOperator_k) {
      EHVS_DW.FixPtUnitDelay1_DSTATE_e = 0U;
    } else {
      if (LbEHVS_LineBReadyToChangeState_flg) {
        rtb_RelationalOperator_k = 0U;
      } else {
        rtb_RelationalOperator_k = EHVS_RUNTIME_MS;
      }

      EHVS_DW.FixPtUnitDelay1_DSTATE_e = (uint16_T)((uint32_T)
        rtb_RelationalOperator_k + rtb_Init_j);
    }

    EHVS_DW.FixPtUnitDelay2_DSTATE_g = 0U;
    LbEHVS_LineBToSLVS_flg = ((LbEHVS_LineBReadyToChangeState_flg == ((boolean_T)
      ASWTYPE_TRUE)) || (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
      ASWTYPE_FALSE)) || (get_GbEBSW_UserForceStopPACKB_flg() == ((boolean_T)
      ASWTYPE_TRUE)));
  } else {
    if (EHVS_DW.LineBWork_MODE) {
      EHVS_DW.LineBWork_MODE = false;
    }
  }

  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion_o) {
    LbEHVS_SLVSToLineA_flg = ((get_GbECTD_PACKBToHVSPCtrCloseDiagFlt_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTD_PACKBToHVSNCtrCloseDiagFlt_flg()
      == ((boolean_T)ASWTYPE_FALSE)) && (LbEHVS_PackALowPowerSupply_flg ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbEBSW_UserForceStopPACKA_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GcEBSW_TMSMiddleHVVolt_V() <
      get_GcEBCR_BMSBPackVolt_V() * CcEHVS_PackBVoltFactor_numb));
    LbEHVS_SLVSToLineB_flg = ((get_GbECTD_PACKAToHVSPCtrCloseDiagFlt_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GbECTD_PACKAToHVSNCtrCloseDiagFlt_flg()
      == ((boolean_T)ASWTYPE_FALSE)) && (LbEHVS_PackBLowPowerSupply_flg ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbEBSW_UserForceStopPACKB_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GcEBSW_TMSMiddleHVVolt_V() <
      get_GcEBCR_BMSAPackVolt_V() * CcEHVS_PackAVoltFactor_numb));
    LbEHVS_SLVSToOffline_flg = (((get_GbEDEC_PackAAllowedDisChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GbEDEC_PackBAllowedDisChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE))) || ((get_GbEBSW_UserForceStopPACKA_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbEBSW_UserForceStopPACKB_flg() ==
      ((boolean_T)ASWTYPE_TRUE))));
  }

  if (EHVS_DW.is_active_c4_EHVS == 0U) {
    EHVS_DW.is_active_c4_EHVS = 1U;
    EHVS_DW.is_c4_EHVS = EHVS_IN_Offline;
    EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_Offline;
  } else {
    switch (EHVS_DW.is_c4_EHVS) {
     case EHVS_IN_LineA:
      if (LbEHVS_LineAToSLVS_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EHVS_DW.is_c4_EHVS = EHVS_IN_SLVS;
        EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_SLVS;
      }
      break;

     case EHVS_IN_LineB:
      if (LbEHVS_LineBToSLVS_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EHVS_DW.is_c4_EHVS = EHVS_IN_SLVS;
        EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_SLVS;
      }
      break;

     case EHVS_IN_Offline:
      if (LbEHVS_OfflineToLineA_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EHVS_DW.is_c4_EHVS = EHVS_IN_LineA;
        EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_LineA;
      } else {
        if (LbEHVS_OfflineToLineB_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EHVS_DW.is_c4_EHVS = EHVS_IN_LineB;
          EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_LineB;
        }
      }
      break;

     default:
      if (LbEHVS_SLVSToLineB_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EHVS_DW.is_c4_EHVS = EHVS_IN_LineB;
        EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_LineB;
      } else if (LbEHVS_SLVSToLineA_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EHVS_DW.is_c4_EHVS = EHVS_IN_LineA;
        EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_LineA;
      } else {
        if (LbEHVS_SLVSToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EHVS_DW.is_c4_EHVS = EHVS_IN_Offline;
          EHVS_B.GeEHVS_HVSState_enum = (uint8_T)Enum_EHVSHVSState_Offline;
        }
      }
      break;
    }
  }

  if (CbEHVS_HVSStateOvrSwt_flg) {
    set_GeEHVS_HVSState_enum(CeEHVS_HVSStateOvr_enum);
  } else {
    set_GeEHVS_HVSState_enum(EHVS_B.GeEHVS_HVSState_enum);
  }

  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion1_a) {
    rtb_Switch2_idx_0 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Switch2_idx_1 = ((boolean_T)ASWTYPE_FALSE);
  } else if ((rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion2_f) ||
             (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion3_f)) {
    rtb_Switch2_idx_0 = ((boolean_T)ASWTYPE_TRUE);
    rtb_Switch2_idx_1 = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Switch2_idx_0 = EHVS_DW.StateName_n[0];
    rtb_Switch2_idx_1 = EHVS_DW.StateName_n[1];
  }

  if (CbEHVS_TMSPowerCtrOvrSwt_flg) {
    set_GbEHVS_TMSPowerCtr_flg(CbEHVS_TMSPowerCtrOvr_flg);
  } else {
    set_GbEHVS_TMSPowerCtr_flg(rtb_Switch2_idx_0);
  }

  rtb_LogicalOperator_k = (get_GbEHVS_TMSPowerCtr_flg() != ((boolean_T)
    ASWTYPE_FALSE));
  if (rtb_LogicalOperator_k || (EHVS_DW.FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_j = 0U;
  } else {
    rtb_Init_j = EHVS_DW.FixPtUnitDelay1_DSTATE;
  }

  rtb_RelationalOperator_hw = (rtb_Init_j >= CcEHVS_RelayCtrOFFDebTime_ms);
  if (rtb_LogicalOperator_k) {
    EHVS_DW.FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (rtb_RelationalOperator_hw) {
      rtb_RelationalOperator_k = 0U;
    } else {
      rtb_RelationalOperator_k = EHVS_RUNTIME_MS;
    }

    EHVS_DW.FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)
      rtb_RelationalOperator_k + rtb_Init_j);
  }

  EHVS_DW.FixPtUnitDelay2_DSTATE = 0U;
  if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion6_c) {
    rtb_LogicalOperator_k = ((boolean_T)ASWTYPE_TRUE);
    rtb_RelationalOperator_hw = ((boolean_T)ASWTYPE_TRUE);
    rtb_Switch1_a_idx_2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Switch1_a_idx_3 = ((boolean_T)ASWTYPE_FALSE);
  } else if (rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion7_k) {
    rtb_LogicalOperator_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_RelationalOperator_hw = ((boolean_T)ASWTYPE_FALSE);
    rtb_Switch1_a_idx_2 = ((boolean_T)ASWTYPE_TRUE);
    rtb_Switch1_a_idx_3 = ((boolean_T)ASWTYPE_TRUE);
  } else if (((rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion1_h) &&
              (get_GeEHCR_HCUSystemMode_enum() ==
               EHVS_ConstB.DataTypeConversion2_a)) || ((EHVS_DW.StateName_k ==
               EHVS_ConstB.DataTypeConversion4_c) && (rtb_GeEHVS_HVSState_enum
               != EHVS_ConstB.DataTypeConversion5_k)) ||
             ((rtb_GeEHVS_HVSState_enum == EHVS_ConstB.DataTypeConversion3_i) &&
              rtb_RelationalOperator_hw)) {
    rtb_LogicalOperator_k = ((boolean_T)ASWTYPE_FALSE);
    rtb_RelationalOperator_hw = ((boolean_T)ASWTYPE_FALSE);
    rtb_Switch1_a_idx_2 = ((boolean_T)ASWTYPE_FALSE);
    rtb_Switch1_a_idx_3 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_LogicalOperator_k = EHVS_DW.StateName_j[0];
    rtb_RelationalOperator_hw = EHVS_DW.StateName_j[1];
    rtb_Switch1_a_idx_2 = EHVS_DW.StateName_j[2];
    rtb_Switch1_a_idx_3 = EHVS_DW.StateName_j[3];
  }

  if (CbEHVS_PACKAToHVSPCtrOvrSwt_flg) {
    set_GbEHVS_PACKAToHVSPCtr_flg(CbEHVS_PACKAToHVSPCtrOvr_flg);
  } else {
    set_GbEHVS_PACKAToHVSPCtr_flg(rtb_LogicalOperator_k);
  }

  if (CbEHVS_PACKAToHVSNCtrOvrSwt_flg) {
    set_GbEHVS_PACKAToHVSNCtr_flg(CbEHVS_PACKAToHVSNCtrOvr_flg);
  } else {
    set_GbEHVS_PACKAToHVSNCtr_flg(rtb_RelationalOperator_hw);
  }

  if (CbEHVS_PACKBToHVSPCtrOvrSwt_flg) {
    set_GbEHVS_PACKBToHVSPCtr_flg(CbEHVS_PACKBToHVSPCtrOvr_flg);
  } else {
    set_GbEHVS_PACKBToHVSPCtr_flg(rtb_Switch1_a_idx_2);
  }

  if (CbEHVS_PACKBToHVSNCtrOvrSwt_flg) {
    set_GbEHVS_PACKBToHVSNCtr_flg(CbEHVS_PACKBToHVSNCtrOvr_flg);
  } else {
    set_GbEHVS_PACKBToHVSNCtr_flg(rtb_Switch1_a_idx_3);
  }

  if (CbEHVS_SmallDCDCPowerCtrOvrSwt_flg) {
    set_GbEHVS_SmallDCDCPowerCtr_flg(CbEHVS_SmallDCDCPowerCtrOvr_flg);
  } else {
    set_GbEHVS_SmallDCDCPowerCtr_flg(rtb_Switch2_idx_1);
  }

  EHVS_DW.StateName = get_GeEHVS_HVSState_enum();
  EHVS_DW.StateName_h = LbEHVS_PackBLowPowerSupply_flg;
  EHVS_DW.StateName_b = LbEHVS_PackALowPowerSupply_flg;
  EHVS_DW.StateName_n[0] = rtb_Switch2_idx_0;
  EHVS_DW.StateName_n[1] = rtb_Switch2_idx_1;
  EHVS_DW.StateName_k = rtb_GeEHVS_HVSState_enum;
  EHVS_DW.StateName_j[0] = rtb_LogicalOperator_k;
  EHVS_DW.StateName_j[1] = rtb_RelationalOperator_hw;
  EHVS_DW.StateName_j[2] = rtb_Switch1_a_idx_2;
  EHVS_DW.StateName_j[3] = rtb_Switch1_a_idx_3;
}

/* Model initialize function */
void EHVS_initialize(void)
{
  EHVS_DW.FixPtUnitDelay2_DSTATE_a = 1U;
  EHVS_DW.FixPtUnitDelay2_DSTATE_g = 1U;
  EHVS_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
