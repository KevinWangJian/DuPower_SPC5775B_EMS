/*
 * File: ECMM.c
 *
 * Code generated for Simulink model 'ECMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed May 20 17:27:26 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECMM.h"
#include "ECMM_private.h"

/* Named constants for Chart: '<S4>/ChrgCtrAMode' */
#define ECMM_IN_BCChrg                 ((uint8_T)1U)
#define ECMM_IN_CChrg                  ((uint8_T)2U)
#define ECMM_IN_Chrg                   ((uint8_T)3U)
#define ECMM_IN_Idle                   ((uint8_T)4U)
#define ECMM_IN_Offline                ((uint8_T)5U)
#define ECMM_IN_ReChrg                 ((uint8_T)6U)

/* Block signals (auto storage) */
B_ECMM_T ECMM_B;

/* Block states (auto storage) */
DW_ECMM_T ECMM_DW;

/* Real-time model */
RT_MODEL_ECMM_T ECMM_M_;
RT_MODEL_ECMM_T *const ECMM_M = &ECMM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECMMA_20ms_at_outport_1' */
void ECMMA_20ms(void)
{
  uint8_T rtb_GeECMM_ChrgCtrAMode_enum;
  boolean_T rtb_LogicalOperator_n;
  uint8_T rtb_Init_f4;
  uint8_T tmp;
  rtb_GeECMM_ChrgCtrAMode_enum = ECMM_DW.StateName_m;
  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_d0o) {
    if (!ECMM_DW.BCChrgWork_MODE_m) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_l = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_o = 0U;
      ECMM_DW.BCChrgWork_MODE_m = true;
    }

    rtb_LogicalOperator_n = (get_GbECHM_GunAStopChrg_flg() != ((boolean_T)
      ASWTYPE_TRUE));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_l != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_o;
    }

    LbECMM_ChrgCtrABCChrgToIdle_flg = (rtb_Init_f4 >=
      CcECMM_ABCChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_o = 0U;
    } else {
      if (LbECMM_ChrgCtrABCChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_o = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_l = 0U;
  } else {
    if (ECMM_DW.BCChrgWork_MODE_m) {
      LbECMM_ChrgCtrABCChrgToIdle_flg = false;
      ECMM_DW.BCChrgWork_MODE_m = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_fo) {
    if (!ECMM_DW.CChrgWork_MODE_o) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_e2 = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_dy = 0U;
      ECMM_DW.CChrgWork_MODE_o = true;
    }

    rtb_LogicalOperator_n = (get_GbECHM_GunAStopChrg_flg() != ((boolean_T)
      ASWTYPE_TRUE));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_e2 != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_dy;
    }

    LbECMM_ChrgCtrACChrgToIdle_flg = (rtb_Init_f4 >=
      CcECMM_ACChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_dy = 0U;
    } else {
      if (LbECMM_ChrgCtrACChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_dy = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_e2 = 0U;
  } else {
    if (ECMM_DW.CChrgWork_MODE_o) {
      LbECMM_ChrgCtrACChrgToIdle_flg = false;
      ECMM_DW.CChrgWork_MODE_o = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_kr) {
    if (!ECMM_DW.ChrgWork_MODE_a) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_k5 = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_j4 = 0U;
      ECMM_DW.ChrgWork_MODE_a = true;
    }

    rtb_LogicalOperator_n = !((get_GbECHM_GunAStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE)) || (get_GeEAMM_ACDCAWorkMode_enum() ==
                         ECMM_ConstB.DataTypeConversion_d3));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_k5 != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_j4;
    }

    LbECMM_ChrgCtrAChrgToIdle_flg = (rtb_Init_f4 >= CcECMM_AChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_j4 = 0U;
    } else {
      if (LbECMM_ChrgCtrAChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_j4 = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_k5 = 0U;
  } else {
    if (ECMM_DW.ChrgWork_MODE_a) {
      LbECMM_ChrgCtrAChrgToIdle_flg = false;
      ECMM_DW.ChrgWork_MODE_a = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_k) {
    if (!ECMM_DW.IdleWork_MODE_c) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_j = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_m = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_kg = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_e = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_b = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_pa = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_e = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_h = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_io = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_dd = 0U;
      ECMM_DW.IdleWork_MODE_c = true;
    }

    rtb_LogicalOperator_n = !((get_GeEAMM_ACDCAWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion_o) && (get_GeEAMM_ACDCBWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion1_k));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_j != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_m;
    }

    LbECMM_ChrgCtrAIdleToBCChrg_flg = (rtb_Init_f4 >=
      CcECMM_AIdleToBCChrgDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_m = 0U;
    } else {
      if (LbECMM_ChrgCtrAIdleToBCChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_m = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_j = 0U;
    rtb_LogicalOperator_n = !((get_GeEAMM_ACDCAWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion_b) && (get_GeEAMM_ACDCBWorkMode_enum() !=
      ECMM_ConstB.DataTypeConversion1_c));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_kg != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_e;
    }

    LbECMM_ChrgCtrAIdleToCChrg_flg = (rtb_Init_f4 >=
      CcECMM_AIdleToCChrgDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_e = 0U;
    } else {
      if (LbECMM_ChrgCtrAIdleToCChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_e = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_kg = 0U;
    rtb_LogicalOperator_n = !((get_GbECHM_GunAStartChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE)) && (get_GeEAMM_ACDCAWorkMode_enum() !=
                         ECMM_ConstB.DataTypeConversion_cr));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_b != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_pa;
    }

    LbECMM_ChrgCtrAIdleToChrg_flg = (rtb_Init_f4 >= CcECMM_AIdleToChrgDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_pa = 0U;
    } else {
      if (LbECMM_ChrgCtrAIdleToChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_pa = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_b = 0U;
    rtb_LogicalOperator_n = !(get_GeEBCR_BMSAMainPosCntStat_enum() ==
      ((boolean_T)ASWTYPE_FALSE));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_e != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_h;
    }

    LbECMM_ChrgCtrAIdleToOffline_flg = (rtb_Init_f4 >=
      CcECMM_AIdleToOfflineDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_h = 0U;
    } else {
      if (LbECMM_ChrgCtrAIdleToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_h = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_e = 0U;
    rtb_LogicalOperator_n = !(get_GeEAMM_ACDCAWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion_is);
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_io != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_dd;
    }

    LbECMM_ChrgCtrAIdleToReChrg_flg = (rtb_Init_f4 >=
      CcECMM_AIdleToReChrgDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_dd = 0U;
    } else {
      if (LbECMM_ChrgCtrAIdleToReChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_dd = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_io = 0U;
  } else {
    if (ECMM_DW.IdleWork_MODE_c) {
      LbECMM_ChrgCtrAIdleToOffline_flg = false;
      LbECMM_ChrgCtrAIdleToChrg_flg = false;
      LbECMM_ChrgCtrAIdleToReChrg_flg = false;
      LbECMM_ChrgCtrAIdleToCChrg_flg = false;
      LbECMM_ChrgCtrAIdleToBCChrg_flg = false;
      ECMM_DW.IdleWork_MODE_c = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_g) {
    if (!ECMM_DW.OfflineWork_MODE_i) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_km = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_bu = 0U;
      ECMM_DW.OfflineWork_MODE_i = true;
    }

    rtb_LogicalOperator_n = !((get_GeEBCR_BMSAMainPosCntStat_enum() ==
      ECMM_ConstB.DataTypeConversion_f) && (get_GeEBCR_BMSAMainNegCntStat_enum()
      == ECMM_ConstB.DataTypeConversion1_l));
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_km != 0)) {
      rtb_Init_f4 = 0U;
    } else {
      rtb_Init_f4 = ECMM_DW.FixPtUnitDelay1_DSTATE_bu;
    }

    LbECMM_ChrgCtrAOfflineToIdle_flg = (rtb_Init_f4 >=
      CcECMM_AOfflineToIdleDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_bu = 0U;
    } else {
      if (LbECMM_ChrgCtrAOfflineToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_bu = (uint8_T)((uint32_T)tmp + rtb_Init_f4);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_km = 0U;
  } else {
    if (ECMM_DW.OfflineWork_MODE_i) {
      LbECMM_ChrgCtrAOfflineToIdle_flg = false;
      ECMM_DW.OfflineWork_MODE_i = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrAMode_enum == ECMM_ConstB.DataTypeConversion_d0) {
    if (!ECMM_DW.ReChrgWork_MODE_p) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_c = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_bc = 0U;
      ECMM_DW.ReChrgWork_MODE_p = true;
    }

    rtb_LogicalOperator_n = !(get_GeEAMM_ACDCAWorkMode_enum() !=
      ECMM_ConstB.DataTypeConversion_dx);
    if (rtb_LogicalOperator_n || (ECMM_DW.FixPtUnitDelay2_DSTATE_c != 0)) {
      rtb_GeECMM_ChrgCtrAMode_enum = 0U;
    } else {
      rtb_GeECMM_ChrgCtrAMode_enum = ECMM_DW.FixPtUnitDelay1_DSTATE_bc;
    }

    LbECMM_ChrgCtrAReChrgToIdle_flg = (rtb_GeECMM_ChrgCtrAMode_enum >=
      CcECMM_AReChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_n) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_bc = 0U;
    } else {
      if (LbECMM_ChrgCtrAReChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_bc = (uint8_T)((uint32_T)tmp +
        rtb_GeECMM_ChrgCtrAMode_enum);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_c = 0U;
  } else {
    if (ECMM_DW.ReChrgWork_MODE_p) {
      LbECMM_ChrgCtrAReChrgToIdle_flg = false;
      ECMM_DW.ReChrgWork_MODE_p = false;
    }
  }

  if (ECMM_DW.is_active_c4_ECMM == 0U) {
    ECMM_DW.is_active_c4_ECMM = 1U;
    ECMM_DW.is_c4_ECMM = ECMM_IN_Offline;
    ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Offline;
  } else {
    switch (ECMM_DW.is_c4_ECMM) {
     case ECMM_IN_BCChrg:
      if (LbECMM_ChrgCtrABCChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Idle;
      }
      break;

     case ECMM_IN_CChrg:
      if (LbECMM_ChrgCtrACChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Idle;
      }
      break;

     case ECMM_IN_Chrg:
      if (LbECMM_ChrgCtrAChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Idle;
      }
      break;

     case ECMM_IN_Idle:
      if (LbECMM_ChrgCtrAIdleToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Offline;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Offline;
      } else if (LbECMM_ChrgCtrAIdleToChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Chrg;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Chrg;
      } else if (LbECMM_ChrgCtrAIdleToReChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_ReChrg;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_ReChrg;
      } else if (LbECMM_ChrgCtrAIdleToCChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_CChrg;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_CChrg;
      } else {
        if (LbECMM_ChrgCtrAIdleToBCChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECMM_DW.is_c4_ECMM = ECMM_IN_BCChrg;
          ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)
            Enum_ECMMChrgCtrAMode_BCChrg;
        }
      }
      break;

     case ECMM_IN_Offline:
      if (LbECMM_ChrgCtrAOfflineToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Idle;
      }
      break;

     default:
      if (LbECMM_ChrgCtrAReChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c4_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrAMode_enum = (uint8_T)Enum_ECMMChrgCtrAMode_Idle;
      }
      break;
    }
  }

  if (CbECMM_ChrgCtrAModeOvrSwt_flg) {
    set_GeECMM_ChrgCtrAMode_enum(CeECMM_ChrgCtrAModeOvr_enum);
  } else {
    set_GeECMM_ChrgCtrAMode_enum(ECMM_B.GeECMM_ChrgCtrAMode_enum);
  }

  ECMM_DW.StateName_m = get_GeECMM_ChrgCtrAMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECMMB_20ms_at_outport_1' */
void ECMMB_20ms(void)
{
  uint8_T rtb_GeECMM_ChrgCtrBMode_enum;
  boolean_T rtb_LogicalOperator_mr;
  uint8_T rtb_Init_dn;
  uint8_T tmp;
  rtb_GeECMM_ChrgCtrBMode_enum = ECMM_DW.StateName;
  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion_e) {
    if (!ECMM_DW.BCChrgWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_mx = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_jb = 0U;
      ECMM_DW.BCChrgWork_MODE = true;
    }

    rtb_LogicalOperator_mr = (get_GbECHM_GunBStopChrg_flg() != ((boolean_T)
      ASWTYPE_TRUE));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_mx != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_jb;
    }

    LbECMM_ChrgCtrBBCChrgToIdle_flg = (rtb_Init_dn >=
      CcECMM_BBCChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_jb = 0U;
    } else {
      if (LbECMM_ChrgCtrBBCChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_jb = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_mx = 0U;
  } else {
    if (ECMM_DW.BCChrgWork_MODE) {
      LbECMM_ChrgCtrBBCChrgToIdle_flg = false;
      ECMM_DW.BCChrgWork_MODE = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion_jf) {
    if (!ECMM_DW.CChrgWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_o = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_pe = 0U;
      ECMM_DW.CChrgWork_MODE = true;
    }

    rtb_LogicalOperator_mr = (get_GbECHM_GunBStopChrg_flg() != ((boolean_T)
      ASWTYPE_TRUE));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_o != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_pe;
    }

    LbECMM_ChrgCtrBCChrgToIdle_flg = (rtb_Init_dn >=
      CcECMM_BCChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_pe = 0U;
    } else {
      if (LbECMM_ChrgCtrBCChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_pe = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_o = 0U;
  } else {
    if (ECMM_DW.CChrgWork_MODE) {
      LbECMM_ChrgCtrBCChrgToIdle_flg = false;
      ECMM_DW.CChrgWork_MODE = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion_l) {
    if (!ECMM_DW.ChrgWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_mk = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_p = 0U;
      ECMM_DW.ChrgWork_MODE = true;
    }

    rtb_LogicalOperator_mr = !((get_GbECHM_GunBStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE)) || (get_GeEAMM_ACDCBWorkMode_enum() ==
                         ECMM_ConstB.DataTypeConversion_m));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_mk != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_p;
    }

    LbECMM_ChrgCtrBChrgToIdle_flg = (rtb_Init_dn >= CcECMM_BChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_p = 0U;
    } else {
      if (LbECMM_ChrgCtrBChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_p = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_mk = 0U;
  } else {
    if (ECMM_DW.ChrgWork_MODE) {
      LbECMM_ChrgCtrBChrgToIdle_flg = false;
      ECMM_DW.ChrgWork_MODE = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion_ib) {
    if (!ECMM_DW.IdleWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_ia = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_d = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_d = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_j = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_m = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_li = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_n = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_b = 0U;
      ECMM_DW.FixPtUnitDelay2_DSTATE_i = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_l = 0U;
      ECMM_DW.IdleWork_MODE = true;
    }

    rtb_LogicalOperator_mr = !((get_GeEAMM_ACDCBWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion1_g) && (get_GeEAMM_ACDCAWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion_n));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_ia != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_d;
    }

    LbECMM_ChrgCtrBIdleToBCChrg_flg = (rtb_Init_dn >=
      CcECMM_BIdleToBCChrgDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_d = 0U;
    } else {
      if (LbECMM_ChrgCtrBIdleToBCChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_d = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_ia = 0U;
    rtb_LogicalOperator_mr = !((get_GeEAMM_ACDCBWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion1_p) && (get_GeEAMM_ACDCAWorkMode_enum() !=
      ECMM_ConstB.DataTypeConversion_c));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_d != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_j;
    }

    LbECMM_ChrgCtrBIdleToCChrg_flg = (rtb_Init_dn >=
      CcECMM_BIdleToCChrgDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_j = 0U;
    } else {
      if (LbECMM_ChrgCtrBIdleToCChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_j = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_d = 0U;
    rtb_LogicalOperator_mr = !((get_GbECHM_GunBStartChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE)) && (get_GeEAMM_ACDCBWorkMode_enum() !=
                         ECMM_ConstB.DataTypeConversion_ci));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_m != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_li;
    }

    LbECMM_ChrgCtrBIdleToChrg_flg = (rtb_Init_dn >= CcECMM_BIdleToChrgDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_li = 0U;
    } else {
      if (LbECMM_ChrgCtrBIdleToChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_li = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_m = 0U;
    rtb_LogicalOperator_mr = !(get_GeEBCR_BMSBMainNegCntStat_enum() ==
      ((boolean_T)ASWTYPE_FALSE));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_n != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_b;
    }

    LbECMM_ChrgCtrBIdleToOffline_flg = (rtb_Init_dn >=
      CcECMM_BIdleToOfflineDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_b = 0U;
    } else {
      if (LbECMM_ChrgCtrBIdleToOffline_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_b = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_n = 0U;
    rtb_LogicalOperator_mr = !(get_GeEAMM_ACDCBWorkMode_enum() ==
      ECMM_ConstB.DataTypeConversion_d);
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_i != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_l;
    }

    LbECMM_ChrgCtrBIdleToReChrg_flg = (rtb_Init_dn >=
      CcECMM_BIdleToReChrgDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_l = 0U;
    } else {
      if (LbECMM_ChrgCtrBIdleToReChrg_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_l = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_i = 0U;
  } else {
    if (ECMM_DW.IdleWork_MODE) {
      LbECMM_ChrgCtrBIdleToOffline_flg = false;
      LbECMM_ChrgCtrBIdleToChrg_flg = false;
      LbECMM_ChrgCtrBIdleToReChrg_flg = false;
      LbECMM_ChrgCtrBIdleToCChrg_flg = false;
      LbECMM_ChrgCtrBIdleToBCChrg_flg = false;
      ECMM_DW.IdleWork_MODE = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion_i) {
    if (!ECMM_DW.OfflineWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE_k = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE_c = 0U;
      ECMM_DW.OfflineWork_MODE = true;
    }

    rtb_LogicalOperator_mr = !((get_GeEBCR_BMSBMainPosCntStat_enum() ==
      ECMM_ConstB.DataTypeConversion_a) && (get_GeEBCR_BMSBMainNegCntStat_enum()
      == ECMM_ConstB.DataTypeConversion1));
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE_k != 0)) {
      rtb_Init_dn = 0U;
    } else {
      rtb_Init_dn = ECMM_DW.FixPtUnitDelay1_DSTATE_c;
    }

    LbECMM_ChrgCtrBOfflineToIdle_flg = (rtb_Init_dn >=
      CcECMM_BOfflineToIdleDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE_c = 0U;
    } else {
      if (LbECMM_ChrgCtrBOfflineToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE_c = (uint8_T)((uint32_T)tmp + rtb_Init_dn);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE_k = 0U;
  } else {
    if (ECMM_DW.OfflineWork_MODE) {
      LbECMM_ChrgCtrBOfflineToIdle_flg = false;
      ECMM_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeECMM_ChrgCtrBMode_enum == ECMM_ConstB.DataTypeConversion) {
    if (!ECMM_DW.ReChrgWork_MODE) {
      ECMM_DW.FixPtUnitDelay2_DSTATE = 1U;
      ECMM_DW.FixPtUnitDelay1_DSTATE = 0U;
      ECMM_DW.ReChrgWork_MODE = true;
    }

    rtb_LogicalOperator_mr = !(get_GeEAMM_ACDCBWorkMode_enum() !=
      ECMM_ConstB.DataTypeConversion_j);
    if (rtb_LogicalOperator_mr || (ECMM_DW.FixPtUnitDelay2_DSTATE != 0)) {
      rtb_GeECMM_ChrgCtrBMode_enum = 0U;
    } else {
      rtb_GeECMM_ChrgCtrBMode_enum = ECMM_DW.FixPtUnitDelay1_DSTATE;
    }

    LbECMM_ChrgCtrBReChrgToIdle_flg = (rtb_GeECMM_ChrgCtrBMode_enum >=
      CcECMM_BReChrgToIdleDelayT_ms);
    if (rtb_LogicalOperator_mr) {
      ECMM_DW.FixPtUnitDelay1_DSTATE = 0U;
    } else {
      if (LbECMM_ChrgCtrBReChrgToIdle_flg) {
        tmp = 0U;
      } else {
        tmp = ECMM_RUNTIME_MS;
      }

      ECMM_DW.FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp +
        rtb_GeECMM_ChrgCtrBMode_enum);
    }

    ECMM_DW.FixPtUnitDelay2_DSTATE = 0U;
  } else {
    if (ECMM_DW.ReChrgWork_MODE) {
      LbECMM_ChrgCtrBReChrgToIdle_flg = false;
      ECMM_DW.ReChrgWork_MODE = false;
    }
  }

  if (ECMM_DW.is_active_c3_ECMM == 0U) {
    ECMM_DW.is_active_c3_ECMM = 1U;
    ECMM_DW.is_c3_ECMM = ECMM_IN_Offline;
    ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Offline;
  } else {
    switch (ECMM_DW.is_c3_ECMM) {
     case ECMM_IN_BCChrg:
      if (LbECMM_ChrgCtrBBCChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Idle;
      }
      break;

     case ECMM_IN_CChrg:
      if (LbECMM_ChrgCtrBCChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Idle;
      }
      break;

     case ECMM_IN_Chrg:
      if (LbECMM_ChrgCtrBChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Idle;
      }
      break;

     case ECMM_IN_Idle:
      if (LbECMM_ChrgCtrBIdleToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Offline;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Offline;
      } else if (LbECMM_ChrgCtrBIdleToChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Chrg;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Chrg;
      } else if (LbECMM_ChrgCtrBIdleToReChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_ReChrg;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_ReChrg;
      } else if (LbECMM_ChrgCtrBIdleToCChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_CChrg;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_CChrg;
      } else {
        if (LbECMM_ChrgCtrBIdleToBCChrg_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECMM_DW.is_c3_ECMM = ECMM_IN_BCChrg;
          ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)
            Enum_ECMMChrgCtrBMode_BCChrg;
        }
      }
      break;

     case ECMM_IN_Offline:
      if (LbECMM_ChrgCtrBOfflineToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Idle;
      }
      break;

     default:
      if (LbECMM_ChrgCtrBReChrgToIdle_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECMM_DW.is_c3_ECMM = ECMM_IN_Idle;
        ECMM_B.GeECMM_ChrgCtrBMode_enum = (uint8_T)Enum_ECMMChrgCtrBMode_Idle;
      }
      break;
    }
  }

  if (CbECMM_ChrgCtrBModeOvrSwt_flg) {
    set_GeECMM_ChrgCtrBMode_enum(CeECMM_ChrgCtrBModeOvr_enum);
  } else {
    set_GeECMM_ChrgCtrBMode_enum(ECMM_B.GeECMM_ChrgCtrBMode_enum);
  }

  ECMM_DW.StateName = get_GeECMM_ChrgCtrBMode_enum();
}

/* Model initialize function */
void ECMM_initialize(void)
{
  ECMM_DW.FixPtUnitDelay2_DSTATE_l = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_e2 = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_k5 = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_j = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_kg = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_b = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_e = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_io = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_km = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_c = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_mx = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_o = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_mk = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_ia = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_d = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_m = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_n = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_i = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE_k = 1U;
  ECMM_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
