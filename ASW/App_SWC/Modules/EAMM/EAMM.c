/*
 * File: EAMM.c
 *
 * Code generated for Simulink model 'EAMM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 21 14:33:07 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EAMM.h"
#include "EAMM_private.h"

/* Named constants for Chart: '<S4>/ACDCAWorkMode' */
#define EAMM_IN_GunA                   ((uint8_T)1U)
#define EAMM_IN_GunB                   ((uint8_T)2U)
#define EAMM_IN_Offline                ((uint8_T)3U)
#define EAMM_IN_PackA                  ((uint8_T)4U)

/* Named constants for Chart: '<S21>/ACDCBWorkMode' */
#define EAMM_IN_PackB                  ((uint8_T)4U)

/* Block signals (auto storage) */
B_EAMM_T EAMM_B;

/* Block states (auto storage) */
DW_EAMM_T EAMM_DW;

/* Real-time model */
RT_MODEL_EAMM_T EAMM_M_;
RT_MODEL_EAMM_T *const EAMM_M = &EAMM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EAMMA_20ms_at_outport_1' */
void EAMMA_20ms(void)
{
  uint8_T rtb_GeEAMM_ACDCAWorkMode_enum;
  rtb_GeEAMM_ACDCAWorkMode_enum = EAMM_DW.StateName_m;
  if (rtb_GeEAMM_ACDCAWorkMode_enum == EAMM_ConstB.DataTypeConversion_g) {
    if (!EAMM_DW.OfflineWork_MODE_i) {
      EAMM_DW.OfflineWork_MODE_i = true;
    }

    LbEAMM_ACDCAOfflineToGunA_flg = ((get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcECCR_GunAMaxPwr_kw() >
      CcEAMM_GunAMaxPwrLowLimit_kw) && (get_GeEACC_ACDCARunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_f) && (get_GcECCR_GunBMaxPwr_kw() <
      CcEAMM_GunBMaxPwrUpLimit_kw));
    LbEAMM_ACDCAOfflineToGunB_flg = ((get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEACC_ACDCARunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_a) && (get_GcECCR_GunBMaxPwr_kw() >
      CcEAMM_GunBMaxPwrUpLimit_kw));
    LbEAMM_ACDCAOfflineToPackA_flg = ((get_GbEBIM_PackAAllowedReChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEACC_ACDCARunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_i) && (get_GcECCR_GunBMaxPwr_kw() <
      CcEAMM_GunBMaxPwrUpLimit_kw));
  } else {
    if (EAMM_DW.OfflineWork_MODE_i) {
      LbEAMM_ACDCAOfflineToGunA_flg = false;
      LbEAMM_ACDCAOfflineToGunB_flg = false;
      LbEAMM_ACDCAOfflineToPackA_flg = false;
      EAMM_DW.OfflineWork_MODE_i = false;
    }
  }

  if (rtb_GeEAMM_ACDCAWorkMode_enum == EAMM_ConstB.DataTypeConversion_mq) {
    if (!EAMM_DW.GunAWork_MODE_p) {
      EAMM_DW.GunAWork_MODE_p = true;
    }

    LbEAMM_ACDCAGunAToOffline_flg = ((get_GeEACC_ACDCARunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_o5) || (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EAMM_DW.GunAWork_MODE_p) {
      LbEAMM_ACDCAGunAToOffline_flg = false;
      EAMM_DW.GunAWork_MODE_p = false;
    }
  }

  if (rtb_GeEAMM_ACDCAWorkMode_enum == EAMM_ConstB.DataTypeConversion_om) {
    if (!EAMM_DW.GunBWork_MODE_g) {
      EAMM_DW.GunBWork_MODE_g = true;
    }

    LbEAMM_ACDCAGunBToOffline_flg = ((get_GeEACC_ACDCARunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_h) || (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EAMM_DW.GunBWork_MODE_g) {
      LbEAMM_ACDCAGunBToOffline_flg = false;
      EAMM_DW.GunBWork_MODE_g = false;
    }
  }

  if (rtb_GeEAMM_ACDCAWorkMode_enum == EAMM_ConstB.DataTypeConversion_dd) {
    if (!EAMM_DW.PackAWork_MODE) {
      EAMM_DW.PackAWork_MODE = true;
    }

    LbEAMM_ACDCAPackAToOffline_flg = ((get_GeEACC_ACDCARunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_c) || (get_GbEBIM_PackAAllowedReChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) || (get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || ((get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcECCR_GunBMaxPwr_kw() >
      CcEAMM_GunBMaxPwrUpLimit_kw)));
  } else {
    if (EAMM_DW.PackAWork_MODE) {
      LbEAMM_ACDCAPackAToOffline_flg = false;
      EAMM_DW.PackAWork_MODE = false;
    }
  }

  if (EAMM_DW.is_active_c4_EAMM == 0U) {
    EAMM_DW.is_active_c4_EAMM = 1U;
    EAMM_DW.is_c4_EAMM = EAMM_IN_Offline;
    EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)Enum_EAMMACDCAWorkMode_Offline;
  } else {
    switch (EAMM_DW.is_c4_EAMM) {
     case EAMM_IN_GunA:
      if (LbEAMM_ACDCAGunAToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c4_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)
          Enum_EAMMACDCAWorkMode_Offline;
      }
      break;

     case EAMM_IN_GunB:
      if (LbEAMM_ACDCAGunBToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c4_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)
          Enum_EAMMACDCAWorkMode_Offline;
      }
      break;

     case EAMM_IN_Offline:
      if (LbEAMM_ACDCAOfflineToGunA_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c4_EAMM = EAMM_IN_GunA;
        EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)Enum_EAMMACDCAWorkMode_GunA;
      } else if (LbEAMM_ACDCAOfflineToGunB_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c4_EAMM = EAMM_IN_GunB;
        EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)Enum_EAMMACDCAWorkMode_GunB;
      } else {
        if (LbEAMM_ACDCAOfflineToPackA_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EAMM_DW.is_c4_EAMM = EAMM_IN_PackA;
          EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)
            Enum_EAMMACDCAWorkMode_PackA;
        }
      }
      break;

     default:
      if (LbEAMM_ACDCAPackAToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c4_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCAWorkMode_enum = (uint8_T)
          Enum_EAMMACDCAWorkMode_Offline;
      }
      break;
    }
  }

  if (CbEAMM_ACDCAWorkModeOvrSwt_flg) {
    set_GeEAMM_ACDCAWorkMode_enum(CeEAMM_ACDCAWorkModeOvr_enum);
  } else {
    set_GeEAMM_ACDCAWorkMode_enum(EAMM_B.GeEAMM_ACDCAWorkMode_enum);
  }

  EAMM_DW.StateName_m = get_GeEAMM_ACDCAWorkMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EAMMB_20ms_at_outport_1' */
void EAMMB_20ms(void)
{
  uint8_T rtb_GeEAMM_ACDCBWorkMode_enum;
  rtb_GeEAMM_ACDCBWorkMode_enum = EAMM_DW.StateName;
  if (rtb_GeEAMM_ACDCBWorkMode_enum == EAMM_ConstB.DataTypeConversion_nl) {
    if (!EAMM_DW.OfflineWork_MODE) {
      EAMM_DW.OfflineWork_MODE = true;
    }

    LbEAMM_ACDCBOfflineToGunA_flg = ((get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEACC_ACDCBRunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_o) && (get_GcECCR_GunAMaxPwr_kw() >
      CcEAMM_GunAMaxPwrUpLimit_kw));
    LbEAMM_ACDCBOfflineToGunB_flg = ((get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcECCR_GunBMaxPwr_kw() >
      CcEAMM_GunBMaxPwrLowLimit_kw) && (get_GeEACC_ACDCBRunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_m) && (get_GcECCR_GunAMaxPwr_kw() <
      CcEAMM_GunAMaxPwrUpLimit_kw));
    LbEAMM_ACDCBOfflineToPackB_flg = ((get_GbEBIM_PackBAllowedReChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GeEACC_ACDCBRunMode_enum() !=
      EAMM_ConstB.DataTypeConversion_og) && (get_GcECCR_GunAMaxPwr_kw() <
      CcEAMM_GunAMaxPwrUpLimit_kw));
  } else {
    if (EAMM_DW.OfflineWork_MODE) {
      LbEAMM_ACDCBOfflineToGunB_flg = false;
      LbEAMM_ACDCBOfflineToGunA_flg = false;
      LbEAMM_ACDCBOfflineToPackB_flg = false;
      EAMM_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeEAMM_ACDCBWorkMode_enum == EAMM_ConstB.DataTypeConversion_ng) {
    if (!EAMM_DW.GunBWork_MODE) {
      EAMM_DW.GunBWork_MODE = true;
    }

    LbEAMM_ACDCBGunBToOffline_flg = ((get_GeEACC_ACDCBRunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_p) || (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EAMM_DW.GunBWork_MODE) {
      LbEAMM_ACDCBGunBToOffline_flg = false;
      EAMM_DW.GunBWork_MODE = false;
    }
  }

  if (rtb_GeEAMM_ACDCBWorkMode_enum == EAMM_ConstB.DataTypeConversion_d) {
    if (!EAMM_DW.GunAWork_MODE) {
      EAMM_DW.GunAWork_MODE = true;
    }

    LbEAMM_ACDCBGunAToOffline_flg = ((get_GeEACC_ACDCBRunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_b) || (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (EAMM_DW.GunAWork_MODE) {
      LbEAMM_ACDCBGunAToOffline_flg = false;
      EAMM_DW.GunAWork_MODE = false;
    }
  }

  if (rtb_GeEAMM_ACDCBWorkMode_enum == EAMM_ConstB.DataTypeConversion) {
    if (!EAMM_DW.PackBWork_MODE) {
      EAMM_DW.PackBWork_MODE = true;
    }

    LbEAMM_ACDCBPackBToOffline_flg = ((get_GeEACC_ACDCBRunMode_enum() ==
      EAMM_ConstB.DataTypeConversion_n) || (get_GbEBIM_PackBAllowedReChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) || (get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || ((get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcECCR_GunAMaxPwr_kw() >
      CcEAMM_GunAMaxPwrUpLimit_kw)));
  } else {
    if (EAMM_DW.PackBWork_MODE) {
      LbEAMM_ACDCBPackBToOffline_flg = false;
      EAMM_DW.PackBWork_MODE = false;
    }
  }

  if (EAMM_DW.is_active_c3_EAMM == 0U) {
    EAMM_DW.is_active_c3_EAMM = 1U;
    EAMM_DW.is_c3_EAMM = EAMM_IN_Offline;
    EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)Enum_EAMMACDCBWorkMode_Offline;
  } else {
    switch (EAMM_DW.is_c3_EAMM) {
     case EAMM_IN_GunA:
      if (LbEAMM_ACDCBGunAToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c3_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)
          Enum_EAMMACDCBWorkMode_Offline;
      }
      break;

     case EAMM_IN_GunB:
      if (LbEAMM_ACDCBGunBToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c3_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)
          Enum_EAMMACDCBWorkMode_Offline;
      }
      break;

     case EAMM_IN_Offline:
      if (LbEAMM_ACDCBOfflineToGunB_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c3_EAMM = EAMM_IN_GunB;
        EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)Enum_EAMMACDCBWorkMode_GunB;
      } else if (LbEAMM_ACDCBOfflineToGunA_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c3_EAMM = EAMM_IN_GunA;
        EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)Enum_EAMMACDCBWorkMode_GunA;
      } else {
        if (LbEAMM_ACDCBOfflineToPackB_flg == ((boolean_T)ASWTYPE_TRUE)) {
          EAMM_DW.is_c3_EAMM = EAMM_IN_PackB;
          EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)
            Enum_EAMMACDCBWorkMode_PackB;
        }
      }
      break;

     default:
      if (LbEAMM_ACDCBPackBToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        EAMM_DW.is_c3_EAMM = EAMM_IN_Offline;
        EAMM_B.GeEAMM_ACDCBWorkMode_enum = (uint8_T)
          Enum_EAMMACDCBWorkMode_Offline;
      }
      break;
    }
  }

  if (CbEAMM_ACDCBWorkModeOvrSwt_flg) {
    set_GeEAMM_ACDCBWorkMode_enum(CeEAMM_ACDCBWorkModeOvr_enum);
  } else {
    set_GeEAMM_ACDCBWorkMode_enum(EAMM_B.GeEAMM_ACDCBWorkMode_enum);
  }

  EAMM_DW.StateName = get_GeEAMM_ACDCBWorkMode_enum();
}

/* Model initialize function */
void EAMM_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
