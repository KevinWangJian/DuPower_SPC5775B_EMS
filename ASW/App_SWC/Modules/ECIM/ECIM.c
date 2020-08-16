/*
 * File: ECIM.c
 *
 * Code generated for Simulink model 'ECIM'.
 *
 * Company                        : DP
 * Author                         : wxf
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jun 17 11:08:54 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECIM.h"
#include "ECIM_private.h"

/* Named constants for Chart: '<S4>/GunAIntactMode' */
#define ECIM_IN_BCL                    ((uint8_T)1U)
#define ECIM_IN_BCP                    ((uint8_T)2U)
#define ECIM_IN_ISO                    ((uint8_T)3U)
#define ECIM_IN_Offline                ((uint8_T)4U)
#define ECIM_IN_Unload                 ((uint8_T)5U)

/* Block signals (auto storage) */
B_ECIM_T ECIM_B;

/* Block states (auto storage) */
DW_ECIM_T ECIM_DW;

/* Real-time model */
RT_MODEL_ECIM_T ECIM_M_;
RT_MODEL_ECIM_T *const ECIM_M = &ECIM_M_;

/*
 * Initial conditions for atomic system:
 *    '<S7>/Delay'
 *    '<S37>/Delay'
 */
void ECIM_Delay_Init(DW_Delay_ECIM_T *localDW)
{
  localDW->FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S7>/Delay'
 *    '<S37>/Delay'
 */
void ECIM_Delay(boolean_T rtu_Enable, uint16_T rtu_TimeThrld, B_Delay_ECIM_T
                *localB, DW_Delay_ECIM_T *localDW)
{
  boolean_T rtb_LogicalOperator_j;
  uint16_T rtb_Init_by;
  uint8_T tmp;
  rtb_LogicalOperator_j = !rtu_Enable;
  if (rtb_LogicalOperator_j || (localDW->FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init_by = 0U;
  } else {
    rtb_Init_by = localDW->FixPtUnitDelay1_DSTATE;
  }

  localB->RelationalOperator = (rtb_Init_by >= rtu_TimeThrld);
  if (rtb_LogicalOperator_j) {
    localDW->FixPtUnitDelay1_DSTATE = 0U;
  } else {
    if (localB->RelationalOperator) {
      tmp = 0U;
    } else {
      tmp = ECIM_RUNTIME_MS;
    }

    localDW->FixPtUnitDelay1_DSTATE = (uint16_T)((uint32_T)tmp + rtb_Init_by);
  }

  localDW->FixPtUnitDelay2_DSTATE = 0U;
}

/*
 * Output and update for atomic system:
 *    '<S7>/DiffValue'
 *    '<S37>/DiffValue'
 */
void ECIM_DiffValue(real32_T rtu_Signal1, real32_T rtu_Signal2,
                    B_DiffValue_ECIM_T *localB)
{
  if (rtu_Signal1 >= rtu_Signal2) {
    localB->Switch = rtu_Signal1 - rtu_Signal2;
  } else {
    localB->Switch = rtu_Signal2 - rtu_Signal1;
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECIMA_10ms_at_outport_1' */
void ECIMA_10ms(void)
{
  uint8_T rtb_GeECIM_GunAIntactMode_enum;
  boolean_T rtb_LogicalOperator_c;
  uint8_T tmp;
  rtb_GeECIM_GunAIntactMode_enum = ECIM_DW.StateName_m;
  if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_db) {
    if (!ECIM_DW.BCLWork_MODE_g) {
      ECIM_DW.BCLWork_MODE_g = true;
    }

    LbECIM_GunABCLToOffline_flg = (get_GbECHM_GunAStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
  } else {
    if (ECIM_DW.BCLWork_MODE_g) {
      LbECIM_GunABCLToOffline_flg = false;
      ECIM_DW.BCLWork_MODE_g = false;
    }
  }

  if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_n) {
    if (!ECIM_DW.BCPWork_MODE_j) {
      ECIM_DW.BCPWork_MODE_j = true;
    }

    LbECIM_GunABCPToOffline_flg = (get_GbECHM_GunAStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
    LbECIM_GunABCPToBCL_flg = (get_GcECCR_CCU1BCLSPN3072UReq_V() >=
      CcECIM_GunABCPToBCLDebVolt_V);
  } else {
    if (ECIM_DW.BCPWork_MODE_j) {
      LbECIM_GunABCPToOffline_flg = false;
      ECIM_DW.BCPWork_MODE_j = false;
    }
  }

  ECIM_DiffValue(get_GcECCR_CCU1BCPSPN2822U_V(), get_GcEBSW_DCDCAOutVolt_V(),
                 &ECIM_B.DiffValue);
  ECIM_Delay((rtb_GeECIM_GunAIntactMode_enum ==
              ECIM_ConstB.DataTypeConversion4_a) && (ECIM_B.DiffValue.Switch <
              CcECIM_GunAMaxOutputVoltDiff_V), CcECIM_GunAEMSReadyDebTime_ms,
             &ECIM_B.Delay, &ECIM_DW.Delay);
  if (CbECIM_GunAEMSAlreadyOvrSwt_flg) {
    set_GbECIM_GunAEMSAlready_flg(CbECIM_GunAEMSAlreadyOvr_flg);
  } else {
    set_GbECIM_GunAEMSAlready_flg(ECIM_B.Delay.RelationalOperator);
  }

  if (CbECIM_GunAExpOutputVoltOvrSwt_flg) {
    set_GcECIM_GunAExpOutputVolt_V(CcECIM_GunAExpOutputVoltOvr_V);
  } else if ((rtb_GeECIM_GunAIntactMode_enum ==
              ECIM_ConstB.DataTypeConversion1_e) ||
             (rtb_GeECIM_GunAIntactMode_enum ==
              ECIM_ConstB.DataTypeConversion3_f)) {
    set_GcECIM_GunAExpOutputVolt_V(ECIM_CONST0_NUMB);
  } else if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion2_i)
  {
    set_GcECIM_GunAExpOutputVolt_V(get_GcECCR_CCU1BHMSPN2601UbatMaxPermit_V());
  } else if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion4_n)
  {
    set_GcECIM_GunAExpOutputVolt_V(get_GcECCR_CCU1BCPSPN2822U_V());
  } else if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_j)
  {
    set_GcECIM_GunAExpOutputVolt_V(get_GcECCR_CCU1BCLSPN3072UReq_V());
  } else {
    set_GcECIM_GunAExpOutputVolt_V(ECIM_DW.StateName_n);
  }

  ECIM_DW.StateName_n = get_GcECIM_GunAExpOutputVolt_V();
  if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_mq) {
    if (!ECIM_DW.ISOWork_MODE_n) {
      ECIM_DW.ISOWork_MODE_n = true;
    }

    LbECIM_GunAISOToOffline_flg = (get_GbECHM_GunAStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
    LbECIM_GunAISOToUnload_flg = (get_GbECCR_CCU1CCUISOCheckFinish_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    if (ECIM_DW.ISOWork_MODE_n) {
      LbECIM_GunAISOToOffline_flg = false;
      ECIM_DW.ISOWork_MODE_n = false;
    }
  }

  if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_gt) {
    if (!ECIM_DW.OfflineWork_MODE_i) {
      ECIM_DW.OfflineWork_MODE_i = true;
    }

    LbECIM_GunAOfflineToISO_flg = ((get_GcECCR_CCU1BHMSPN2601UbatMaxPermit_V() >=
      CcECIM_GunAOfflineToISODebVolt_V) && (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GbECHM_GunAStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (ECIM_DW.OfflineWork_MODE_i) {
      LbECIM_GunAOfflineToISO_flg = false;
      ECIM_DW.OfflineWork_MODE_i = false;
    }
  }

  if (rtb_GeECIM_GunAIntactMode_enum == ECIM_ConstB.DataTypeConversion_d) {
    if (!ECIM_DW.UnloadWork_MODE_b) {
      ECIM_DW.FixPtUnitDelay2_DSTATE_c = 1U;
      ECIM_DW.FixPtUnitDelay1_DSTATE_f = 0U;
      ECIM_DW.UnloadWork_MODE_b = true;
    }

    LbECIM_GunAUnloadToOffline_flg = (get_GbECHM_GunAStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
    rtb_LogicalOperator_c = !((get_GcEBSW_DCDCAOutVolt_V() <
      CcECIM_GunAUnloadToBCPDebVolt_V) && (get_GcECCR_CCU1BCPSPN2822U_V() >=
      CcECIM_Volt200_V));
    if (rtb_LogicalOperator_c || (ECIM_DW.FixPtUnitDelay2_DSTATE_c != 0)) {
      rtb_GeECIM_GunAIntactMode_enum = 0U;
    } else {
      rtb_GeECIM_GunAIntactMode_enum = ECIM_DW.FixPtUnitDelay1_DSTATE_f;
    }

    LbECIM_GunAUnloadToBCP_flg = (rtb_GeECIM_GunAIntactMode_enum >=
      CcECIM_GunAUnloadToBCPDebTime_ms);
    if (rtb_LogicalOperator_c) {
      ECIM_DW.FixPtUnitDelay1_DSTATE_f = 0U;
    } else {
      if (LbECIM_GunAUnloadToBCP_flg) {
        tmp = 0U;
      } else {
        tmp = ECIM_RUNTIME_MS;
      }

      ECIM_DW.FixPtUnitDelay1_DSTATE_f = (uint8_T)((uint32_T)tmp +
        rtb_GeECIM_GunAIntactMode_enum);
    }

    ECIM_DW.FixPtUnitDelay2_DSTATE_c = 0U;
  } else {
    if (ECIM_DW.UnloadWork_MODE_b) {
      LbECIM_GunAUnloadToOffline_flg = false;
      ECIM_DW.UnloadWork_MODE_b = false;
    }
  }

  if (ECIM_DW.is_active_c4_ECIM == 0U) {
    ECIM_DW.is_active_c4_ECIM = 1U;
    ECIM_DW.is_c4_ECIM = ECIM_IN_Offline;
    ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)Enum_ECIMGunAIntactMode_Offline;
  } else {
    switch (ECIM_DW.is_c4_ECIM) {
     case ECIM_IN_BCL:
      if (LbECIM_GunABCLToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c4_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      }
      break;

     case ECIM_IN_BCP:
      if (LbECIM_GunABCPToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c4_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunABCPToBCL_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c4_ECIM = ECIM_IN_BCL;
          ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
            Enum_ECIMGunAIntactMode_BCL;
        }
      }
      break;

     case ECIM_IN_ISO:
      if (LbECIM_GunAISOToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c4_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunAISOToUnload_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c4_ECIM = ECIM_IN_Unload;
          ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
            Enum_ECIMGunAIntactMode_Unload;
        }
      }
      break;

     case ECIM_IN_Offline:
      if (LbECIM_GunAOfflineToISO_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c4_ECIM = ECIM_IN_ISO;
        ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)Enum_ECIMGunAIntactMode_ISO;
      }
      break;

     default:
      if (LbECIM_GunAUnloadToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c4_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunAUnloadToBCP_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c4_ECIM = ECIM_IN_BCP;
          ECIM_B.GeECIM_GunAIntactMode_enum = (uint8_T)
            Enum_ECIMGunAIntactMode_BCP;
        }
      }
      break;
    }
  }

  if (CbECIM_GunAIntactModeOvrSwt_flg) {
    set_GeECIM_GunAIntactMode_enum(CeECIM_GunAIntactModeOvr_enum);
  } else {
    set_GeECIM_GunAIntactMode_enum(ECIM_B.GeECIM_GunAIntactMode_enum);
  }

  ECIM_DW.StateName_m = get_GeECIM_GunAIntactMode_enum();
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECIMB_10ms_at_outport_1' */
void ECIMB_10ms(void)
{
  uint8_T rtb_GeECIM_GunBIntactMode_enum;
  boolean_T rtb_LogicalOperator;
  uint8_T tmp;
  rtb_GeECIM_GunBIntactMode_enum = ECIM_DW.StateName_g;
  if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion_eb) {
    if (!ECIM_DW.BCLWork_MODE) {
      ECIM_DW.BCLWork_MODE = true;
    }

    LbECIM_GunBBCLToOffline_flg = (get_GbECHM_GunBStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
  } else {
    if (ECIM_DW.BCLWork_MODE) {
      LbECIM_GunBBCLToOffline_flg = false;
      ECIM_DW.BCLWork_MODE = false;
    }
  }

  if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion_g) {
    if (!ECIM_DW.BCPWork_MODE) {
      ECIM_DW.BCPWork_MODE = true;
    }

    LbECIM_GunBBCPToOffline_flg = (get_GbECHM_GunBStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
    LbECIM_GunBBCPToBCL_flg = (get_GcECCR_CCU2BCLSPN3072UReq_V() >=
      CcECIM_GunBBCPToBCLDebVolt_V);
  } else {
    if (ECIM_DW.BCPWork_MODE) {
      LbECIM_GunBBCPToOffline_flg = false;
      ECIM_DW.BCPWork_MODE = false;
    }
  }

  ECIM_DiffValue(get_GcECCR_CCU2BCPSPN2822U_V(), get_GcEBSW_DCDCBOutVolt_V(),
                 &ECIM_B.DiffValue_h);
  ECIM_Delay((rtb_GeECIM_GunBIntactMode_enum ==
              ECIM_ConstB.DataTypeConversion4_c) && (ECIM_B.DiffValue_h.Switch <
              CcECIM_GunBMaxOutputVoltDiff_V), CcECIM_GunBEMSReadyDebTime_ms,
             &ECIM_B.Delay_b, &ECIM_DW.Delay_b);
  if (CbECIM_GunBEMSAlreadyOvrSwt_flg) {
    set_GbECIM_GunBEMSAlready_flg(CbECIM_GunBEMSAlreadyOvr_flg);
  } else {
    set_GbECIM_GunBEMSAlready_flg(ECIM_B.Delay_b.RelationalOperator);
  }

  if (CbECIM_GunBExpOutputVoltOvrSwt_flg) {
    set_GcECIM_GunBExpOutputVolt_V(CcECIM_GunBExpOutputVoltOvr_V);
  } else if ((rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion1)
             || (rtb_GeECIM_GunBIntactMode_enum ==
                 ECIM_ConstB.DataTypeConversion3)) {
    set_GcECIM_GunBExpOutputVolt_V(ECIM_CONST0_NUMB);
  } else if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion2)
  {
    set_GcECIM_GunBExpOutputVolt_V(get_GcECCR_CCU2BHMSPN2601UbatMaxPermit_V());
  } else if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion4)
  {
    set_GcECIM_GunBExpOutputVolt_V(get_GcECCR_CCU2BCPSPN2822U_V());
  } else if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion_b)
  {
    set_GcECIM_GunBExpOutputVolt_V(get_GcECCR_CCU2BCLSPN3072UReq_V());
  } else {
    set_GcECIM_GunBExpOutputVolt_V(ECIM_DW.StateName);
  }

  ECIM_DW.StateName = get_GcECIM_GunBExpOutputVolt_V();
  if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion_m) {
    if (!ECIM_DW.ISOWork_MODE) {
      ECIM_DW.ISOWork_MODE = true;
    }

    LbECIM_GunBISOToOffline_flg = (get_GbECHM_GunBStopChrg_flg() == ((boolean_T)
      ASWTYPE_TRUE));
    LbECIM_GunBISOToUnload_flg = (get_GbECCR_CCU2CCUISOCheckFinish_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    if (ECIM_DW.ISOWork_MODE) {
      LbECIM_GunBISOToOffline_flg = false;
      ECIM_DW.ISOWork_MODE = false;
    }
  }

  if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion_e) {
    if (!ECIM_DW.OfflineWork_MODE) {
      ECIM_DW.OfflineWork_MODE = true;
    }

    LbECIM_GunBOfflineToISO_flg = ((get_GcECCR_CCU2BHMSPN2601UbatMaxPermit_V() >=
      CcECIM_GunBOfflineToISODebVolt_V) && (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) && (get_GbECHM_GunBStartChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  } else {
    if (ECIM_DW.OfflineWork_MODE) {
      LbECIM_GunBOfflineToISO_flg = false;
      ECIM_DW.OfflineWork_MODE = false;
    }
  }

  if (rtb_GeECIM_GunBIntactMode_enum == ECIM_ConstB.DataTypeConversion) {
    if (!ECIM_DW.UnloadWork_MODE) {
      ECIM_DW.FixPtUnitDelay2_DSTATE = 1U;
      ECIM_DW.FixPtUnitDelay1_DSTATE = 0U;
      ECIM_DW.UnloadWork_MODE = true;
    }

    LbECIM_GunBUnloadToOffline_flg = (get_GbECHM_GunBStopChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE));
    rtb_LogicalOperator = !((get_GcEBSW_DCDCBOutVolt_V() <
      CcECIM_GunBUnloadToBCPDebVolt_V) && (get_GcECCR_CCU2BCPSPN2822U_V() >=
      CcECIM_Volt200_V));
    if (rtb_LogicalOperator || (ECIM_DW.FixPtUnitDelay2_DSTATE != 0)) {
      rtb_GeECIM_GunBIntactMode_enum = 0U;
    } else {
      rtb_GeECIM_GunBIntactMode_enum = ECIM_DW.FixPtUnitDelay1_DSTATE;
    }

    LbECIM_GunBUnloadToBCP_flg = (rtb_GeECIM_GunBIntactMode_enum >=
      CcECIM_GunBUnloadToBCPDebTime_ms);
    if (rtb_LogicalOperator) {
      ECIM_DW.FixPtUnitDelay1_DSTATE = 0U;
    } else {
      if (LbECIM_GunBUnloadToBCP_flg) {
        tmp = 0U;
      } else {
        tmp = ECIM_RUNTIME_MS;
      }

      ECIM_DW.FixPtUnitDelay1_DSTATE = (uint8_T)((uint32_T)tmp +
        rtb_GeECIM_GunBIntactMode_enum);
    }

    ECIM_DW.FixPtUnitDelay2_DSTATE = 0U;
  } else {
    if (ECIM_DW.UnloadWork_MODE) {
      LbECIM_GunBUnloadToOffline_flg = false;
      ECIM_DW.UnloadWork_MODE = false;
    }
  }

  if (ECIM_DW.is_active_c3_ECIM == 0U) {
    ECIM_DW.is_active_c3_ECIM = 1U;
    ECIM_DW.is_c3_ECIM = ECIM_IN_Offline;
    ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)Enum_ECIMGunAIntactMode_Offline;
  } else {
    switch (ECIM_DW.is_c3_ECIM) {
     case ECIM_IN_BCL:
      if (LbECIM_GunBBCLToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c3_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      }
      break;

     case ECIM_IN_BCP:
      if (LbECIM_GunBBCPToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c3_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunBBCPToBCL_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c3_ECIM = ECIM_IN_BCL;
          ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
            Enum_ECIMGunBIntactMode_BCL;
        }
      }
      break;

     case ECIM_IN_ISO:
      if (LbECIM_GunBISOToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c3_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunBISOToUnload_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c3_ECIM = ECIM_IN_Unload;
          ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
            Enum_ECIMGunBIntactMode_Unload;
        }
      }
      break;

     case ECIM_IN_Offline:
      if (LbECIM_GunBOfflineToISO_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c3_ECIM = ECIM_IN_ISO;
        ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)Enum_ECIMGunBIntactMode_ISO;
      }
      break;

     default:
      if (LbECIM_GunBUnloadToOffline_flg == ((boolean_T)ASWTYPE_TRUE)) {
        ECIM_DW.is_c3_ECIM = ECIM_IN_Offline;
        ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
          Enum_ECIMGunAIntactMode_Offline;
      } else {
        if (LbECIM_GunBUnloadToBCP_flg == ((boolean_T)ASWTYPE_TRUE)) {
          ECIM_DW.is_c3_ECIM = ECIM_IN_BCP;
          ECIM_B.GeECIM_GunBIntactMode_enum = (uint8_T)
            Enum_ECIMGunBIntactMode_BCP;
        }
      }
      break;
    }
  }

  if (CbECIM_GunBIntactModeOvrSwt_flg) {
    set_GeECIM_GunBIntactMode_enum(CeECIM_GunBIntactModeOvr_enum);
  } else {
    set_GeECIM_GunBIntactMode_enum(ECIM_B.GeECIM_GunBIntactMode_enum);
  }

  ECIM_DW.StateName_g = get_GeECIM_GunBIntactMode_enum();
}

/* Model initialize function */
void ECIM_initialize(void)
{
  ECIM_DW.FixPtUnitDelay2_DSTATE_c = 1U;
  ECIM_DW.FixPtUnitDelay2_DSTATE = 1U;
  ECIM_Delay_Init(&ECIM_DW.Delay);
  ECIM_Delay_Init(&ECIM_DW.Delay_b);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
