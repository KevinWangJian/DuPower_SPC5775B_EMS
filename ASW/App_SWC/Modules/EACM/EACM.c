/*
 * File: EACM.c
 *
 * Code generated for Simulink model 'EACM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 18:44:55 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EACM.h"
#include "EACM_private.h"

/* Named constants for Chart: '<S21>/Timer' */
#define EACM_IN_A                      ((uint8_T)1U)
#define EACM_IN_B                      ((uint8_T)2U)
#define EACM_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define EACM_IN_Output                 ((uint8_T)1U)
#define EACM_IN_Timer                  ((uint8_T)2U)

/* Named constants for Chart: '<S15>/Start_Stop' */
#define EACM_IN_Default                ((uint8_T)1U)
#define EACM_IN_Enable                 ((uint8_T)2U)
#define EACM_IN_START                  ((uint8_T)1U)
#define EACM_IN_STOP                   ((uint8_T)2U)

/* Named constants for Chart: '<S31>/Timer_Count_30Sec' */
#define EACM_IN_B1                     ((uint8_T)2U)
#define EACM_IN_B_g                    ((uint8_T)1U)
#define EACM_IN_DISABLE                ((uint8_T)1U)
#define EACM_IN_ENABLE                 ((uint8_T)2U)
#define EACM_IN_NO_ACTIVE_CHILD_m      ((uint8_T)0U)

/* Block signals (auto storage) */
B_EACM_T EACM_B;

/* Block states (auto storage) */
DW_EACM_T EACM_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_EACM_T EACM_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_EACM_T EACM_Y;

/* Real-time model */
RT_MODEL_EACM_T EACM_M_;
RT_MODEL_EACM_T *const EACM_M = &EACM_M_;

/*
 * Output and update for atomic system:
 *    '<S21>/Timer'
 *    '<S39>/Timer'
 *    '<S61>/Timer'
 *    '<S79>/Timer'
 */
void EACM_Timer(boolean_T rtu_Timing, B_Timer_EACM_T *localB, DW_Timer_EACM_T
                *localDW)
{
  if (localDW->temporalCounter_i1 < 63U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c4_EACM == 0U) {
    localDW->is_active_c4_EACM = 1U;
    localDW->is_c4_EACM = EACM_IN_Timer;
    localB->Output = 0.0;
  } else if (localDW->is_c4_EACM == EACM_IN_Output) {
    if (!rtu_Timing) {
      localDW->is_Output = EACM_IN_NO_ACTIVE_CHILD;
      localDW->is_c4_EACM = EACM_IN_Timer;
      localB->Output = 0.0;
    } else {
      if ((localDW->is_Output == EACM_IN_A) && (localDW->temporalCounter_i1 >=
           50)) {
        localDW->is_Output = EACM_IN_B;
        localB->Output = 1.0;
      }
    }
  } else {
    if (rtu_Timing) {
      localDW->is_c4_EACM = EACM_IN_Output;
      localDW->is_Output = EACM_IN_A;
      localDW->temporalCounter_i1 = 0U;
    }
  }
}

/*
 * Initial conditions for atomic system:
 *    '<S21>/Trigger_Rising1'
 *    '<S21>/Trigger_Rising2'
 *    '<S39>/Trigger_Rising1'
 *    '<S61>/Trigger_Rising1'
 *    '<S61>/Trigger_Rising2'
 *    '<S79>/Trigger_Rising1'
 */
void EACM_Trigger_Rising1_Init(DW_Trigger_Rising1_EACM_T *localDW)
{
  localDW->StateName = 1U;
}

/*
 * Output and update for atomic system:
 *    '<S21>/Trigger_Rising1'
 *    '<S21>/Trigger_Rising2'
 *    '<S39>/Trigger_Rising1'
 *    '<S61>/Trigger_Rising1'
 *    '<S61>/Trigger_Rising2'
 *    '<S79>/Trigger_Rising1'
 */
void EACM_Trigger_Rising1(boolean_T rtu_In, B_Trigger_Rising1_EACM_T *localB,
  DW_Trigger_Rising1_EACM_T *localDW)
{
  boolean_T rtb_Init;
  if (localDW->StateName != 0) {
    rtb_Init = rtu_In;
  } else {
    rtb_Init = localDW->StateName_g;
  }

  localDW->StateName = 0U;
  localDW->StateName_g = rtu_In;
  localB->LogicalOperator = (rtu_In && (!rtb_Init));
}

/*
 * Output and update for atomic system:
 *    '<S15>/Start_Stop'
 *    '<S55>/Start_Stop'
 */
void EACM_Start_Stop(boolean_T rtu_Start_Check, boolean_T rtu_StopCheck,
                     B_Start_Stop_EACM_T *localB, DW_Start_Stop_EACM_T *localDW)
{
  localDW->StopCheck_prev = localDW->StopCheck_start;
  localDW->StopCheck_start = rtu_StopCheck;
  localDW->Start_Check_prev = localDW->Start_Check_start;
  localDW->Start_Check_start = rtu_Start_Check;
  if (localDW->is_active_c10_EACM == 0U) {
    localDW->StopCheck_prev = rtu_StopCheck;
    localDW->Start_Check_prev = rtu_Start_Check;
    localDW->is_active_c10_EACM = 1U;
    localDW->is_c10_EACM = EACM_IN_Default;
    localB->StartFlg = false;
  } else if (localDW->is_c10_EACM == EACM_IN_Default) {
    if ((localDW->Start_Check_prev != localDW->Start_Check_start) &&
        localDW->Start_Check_start) {
      localDW->is_c10_EACM = EACM_IN_Enable;
      localDW->is_Enable = EACM_IN_START;
      localB->StartFlg = true;
    } else {
      if ((localDW->StopCheck_prev != localDW->StopCheck_start) &&
          localDW->StopCheck_start) {
        localDW->is_c10_EACM = EACM_IN_Enable;
        localDW->is_Enable = EACM_IN_STOP;
        localB->StartFlg = false;
      }
    }
  } else if (localDW->is_Enable == EACM_IN_START) {
    if ((localDW->StopCheck_prev != localDW->StopCheck_start) &&
        localDW->StopCheck_start) {
      localDW->is_Enable = EACM_IN_STOP;
      localB->StartFlg = false;
    }
  } else {
    if ((localDW->Start_Check_prev != localDW->Start_Check_start) &&
        localDW->Start_Check_start) {
      localDW->is_Enable = EACM_IN_START;
      localB->StartFlg = true;
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EACM_20ms_at_outport_1' */
void EACM_20ms(void)
{
  boolean_T rtb_GbEBSW_LeftCCUStartCheck_fl;
  uint8_T rtb_GeEBSW_CCU1CCVChargeType_en;
  Enum_EACMCCU1CCVChargeType rtb_DataTypeConversion;
  boolean_T rtb_Switch4_o;
  boolean_T rtb_GbEBSW_CarPass_flg_k;
  boolean_T rtb_GbEBSW_CarPass_flg;
  uint8_T rtb_GeEACM_CCU1MCVCardType_enum;
  boolean_T rtb_Switch3;
  boolean_T rtb_GbEACM_AGunStartCheckForCar;
  boolean_T rtb_GbETCR_LeftServeStaChgCmd_f;
  Enum_EACMCCU2CCVChargeType rtb_DataTypeConversion_g;
  boolean_T rtb_GbEACM_BGunStartCheckForCar;
  boolean_T rtb_GbETCR_RightServeStaChgCmd_;
  uint8_T rtb_GcEBSW_CCVRFIDCardUID_num_d[8];
  boolean_T GbEBSW_CarPass_flg_prev_c;
  boolean_T GbEBSW_CarPass_flg_prev;
  int32_T i;
  switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
   case 0:
    rtb_GbEBSW_LeftCCUStartCheck_fl = false;
    break;

   case 1:
    rtb_GbEBSW_LeftCCUStartCheck_fl = get_GbEBSW_LeftCCUStartCheck_flg();
    break;

   default:
    rtb_GbEBSW_LeftCCUStartCheck_fl = get_GbEBSW_LeftCCUStartCheck_flg();
    break;
  }

  EACM_Trigger_Rising1(rtb_GbEBSW_LeftCCUStartCheck_fl, &EACM_B.Trigger_Rising1,
                       &EACM_DW.Trigger_Rising1);
  switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
   case 0:
    rtb_GeEBSW_CCU1CCVChargeType_en = 0U;
    break;

   case 1:
    rtb_GeEBSW_CCU1CCVChargeType_en = get_GeEBSW_CCU1CCVChargeType_enum();
    break;

   default:
    rtb_GeEBSW_CCU1CCVChargeType_en = get_GeEBSW_CCU1CCVChargeType_enum();
    break;
  }

  rtb_DataTypeConversion = (Enum_EACMCCU1CCVChargeType)
    rtb_GeEBSW_CCU1CCVChargeType_en;
  switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
   case 0:
    rtb_GbEBSW_CarPass_flg_k = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;
  }

  EACM_Timer(rtb_GbEBSW_CarPass_flg_k == ((boolean_T)ASWTYPE_TRUE),
             &EACM_B.sf_Timer, &EACM_DW.sf_Timer);
  if (((rtb_GbEBSW_LeftCCUStartCheck_fl == ((boolean_T)ASWTYPE_FALSE)) &&
       (EACM_DW.Memory_PreviousInput == ((boolean_T)ASWTYPE_TRUE))) ||
      ((EACM_DW.Memory_PreviousInput == ((boolean_T)ASWTYPE_TRUE)) &&
       (EACM_B.sf_Timer.Output != 0.0))) {
    rtb_Switch4_o = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch4_o = EACM_DW.Memory_PreviousInput;
  }

  if (EACM_B.Trigger_Rising1.LogicalOperator &&
      ((Enum_EACMCCU1CCVChargeType_CreditCard == rtb_DataTypeConversion) ||
       (rtb_DataTypeConversion == Enum_EACMCCU1CCVChargeType_RFCard))) {
    rtb_Switch3 = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_Switch3 = rtb_Switch4_o;
  }

  if (CbEACM_AGunStartCheckForCardOvrSwt_flg) {
    set_GbEACM_AGunStartCheckForCard_flg(CbEACM_AGunStartCheckForCardOvr_flg);
  } else {
    set_GbEACM_AGunStartCheckForCard_flg(rtb_Switch3);
  }

  if (rtb_GeEBSW_CCU1CCVChargeType_en > 0) {
    EACM_B.Check_f = rtb_GeEBSW_CCU1CCVChargeType_en;
  }

  EACM_Trigger_Rising1(rtb_GbEBSW_LeftCCUStartCheck_fl, &EACM_B.Trigger_Rising2,
                       &EACM_DW.Trigger_Rising2);
  if (EACM_B.Trigger_Rising2.LogicalOperator) {
    EACM_B.Check_l = EACM_B.Trigger_Rising2.LogicalOperator;
  }

  if (EACM_B.Check_l) {
    rtb_GeEBSW_CCU1CCVChargeType_en = EACM_B.Check_f;
  } else {
    rtb_GeEBSW_CCU1CCVChargeType_en = EACM_ConstB.DataTypeConversion1;
  }

  switch (rtb_GeEBSW_CCU1CCVChargeType_en) {
   case 0:
    rtb_GbEBSW_CarPass_flg = false;
    rtb_GeEACM_CCU1MCVCardType_enum = 0U;
    rtb_GbEACM_AGunStartCheckForCar = false;
    rtb_GbETCR_LeftServeStaChgCmd_f = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg = get_GbEBSW_CarPass_flg();
    rtb_GeEACM_CCU1MCVCardType_enum = rtb_GeEBSW_CCU1CCVChargeType_en;
    rtb_GbEACM_AGunStartCheckForCar = rtb_Switch3;
    rtb_GbETCR_LeftServeStaChgCmd_f = get_GbETCR_LeftServeStaChgCmd_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg = get_GbEBSW_CarPass_flg();
    rtb_GeEACM_CCU1MCVCardType_enum = rtb_GeEBSW_CCU1CCVChargeType_en;
    rtb_GbEACM_AGunStartCheckForCar = rtb_Switch3;
    rtb_GbETCR_LeftServeStaChgCmd_f = get_GbETCR_LeftServeStaChgCmd_flg();
    break;
  }

  if (EACM_DW.temporalCounter_i1_a < 2047U) {
    EACM_DW.temporalCounter_i1_a++;
  }

  GbEBSW_CarPass_flg_prev_c = EACM_DW.GbEBSW_CarPass_flg_start_f;
  EACM_DW.GbEBSW_CarPass_flg_start_f = rtb_GbEBSW_CarPass_flg;
  if (EACM_DW.is_active_c9_EACM == 0U) {
    EACM_DW.is_active_c9_EACM = 1U;
    EACM_DW.is_c9_EACM = EACM_IN_DISABLE;
    EACM_B.StartCalTmFlg_e = false;
    EACM_B.TmOutFlg_d = false;
  } else if (EACM_DW.is_c9_EACM == EACM_IN_DISABLE) {
    if ((GbEBSW_CarPass_flg_prev_c != EACM_DW.GbEBSW_CarPass_flg_start_f) &&
        EACM_DW.GbEBSW_CarPass_flg_start_f && rtb_GbEACM_AGunStartCheckForCar &&
        (((int32_T)Enum_EACMCCU1CCVChargeType_CreditCard ==
          rtb_GeEACM_CCU1MCVCardType_enum) || ((int32_T)
          Enum_EACMCCU1CCVChargeType_RFCard == rtb_GeEACM_CCU1MCVCardType_enum)))
    {
      EACM_DW.is_c9_EACM = EACM_IN_ENABLE;
      EACM_DW.is_ENABLE_b = EACM_IN_B_g;
      EACM_DW.temporalCounter_i1_a = 0U;
      EACM_B.StartCalTmFlg_e = true;
    }
  } else if (((int32_T)Enum_EACMCCU1CCVChargeType_CreditCard !=
              rtb_GeEACM_CCU1MCVCardType_enum) && ((int32_T)
              Enum_EACMCCU1CCVChargeType_RFCard !=
              rtb_GeEACM_CCU1MCVCardType_enum)) {
    EACM_DW.is_ENABLE_b = EACM_IN_NO_ACTIVE_CHILD_m;
    EACM_DW.is_c9_EACM = EACM_IN_DISABLE;
    EACM_B.StartCalTmFlg_e = false;
    EACM_B.TmOutFlg_d = false;
  } else {
    if ((EACM_DW.is_ENABLE_b == EACM_IN_B_g) && ((EACM_DW.temporalCounter_i1_a >=
          1500) || rtb_GbETCR_LeftServeStaChgCmd_f)) {
      EACM_DW.is_ENABLE_b = EACM_IN_B1;
      EACM_B.TmOutFlg_d = true;
      EACM_B.StartCalTmFlg_e = false;
    }
  }

  if (CbEACM_CCU1TFDAuthReqOvrSwt_flg) {
    set_GbEACM_CCU1TFDAuthReq_flg(CbEACM_CCU1TFDAuthReqOvr_flg);
  } else if (EACM_B.StartCalTmFlg_e) {
    set_GbEACM_CCU1TFDAuthReq_flg(((boolean_T)ASWTYPE_TRUE));
  } else if (EACM_B.TmOutFlg_d) {
    set_GbEACM_CCU1TFDAuthReq_flg(((boolean_T)ASWTYPE_FALSE));
  } else if ((EACM_B.TmOutFlg_d == ((boolean_T)ASWTYPE_FALSE)) && (((boolean_T)
               ASWTYPE_FALSE) == EACM_B.StartCalTmFlg_e)) {
    set_GbEACM_CCU1TFDAuthReq_flg(((boolean_T)ASWTYPE_FALSE));
  } else {
    set_GbEACM_CCU1TFDAuthReq_flg(((boolean_T)ASWTYPE_TRUE));
  }

  if (CbEACM_LeftStaRFIDCardUIDOvrSwt_flg) {
    for (i = 0; i < 8; i++) {
      set_GcEACM_LeftStaRFIDCardUID_numb( i , CcEACM_LeftStaRFIDCardUIDOvr_numb);
    }
  } else {
    if (EACM_B.StartCalTmFlg_e) {
      switch (rtb_GeEBSW_CCU1CCVChargeType_en) {
       case 0:
        rtb_GcEBSW_CCVRFIDCardUID_num_d[0] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[1] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[2] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[3] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[4] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[5] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[6] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[7] = 0U;
        break;

       case 1:
        for (i = 0; i < 8; i++) {
          rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = get_GcEBSW_OCPPDefaultUID_numb( i
            );
        }
        break;

       default:
        for (i = 0; i < 8; i++) {
          rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = get_GcEBSW_CCVRFIDCardUID_numb( i
            );
        }
        break;
      }
    } else {
      for (i = 0; i < 8; i++) {
        rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = EACM_ConstB.DataTypeConversion;
      }
    }

    for (i = 0; i < 8; i++) {
      set_GcEACM_LeftStaRFIDCardUID_numb( i , rtb_GcEBSW_CCVRFIDCardUID_num_d[i]);
    }
  }

  rtb_GbEBSW_CarPass_flg_k = ((int32_T)Enum_GeECCR_CCU1CCUSTATE_Standby ==
    get_GeECCR_CCU1CCUSTATE_enum());
  rtb_GbEBSW_CarPass_flg = (((((boolean_T)ASWTYPE_TRUE) ==
    get_GbETCR_LeftServeStaChgCmd_flg()) && rtb_GbEBSW_CarPass_flg_k) ||
    ((((boolean_T)ASWTYPE_TRUE) == get_GbEBSW_LeftVIPChrgCheckSuccess_flg()) &&
     rtb_GbEBSW_CarPass_flg_k) || ((get_GbEDSM_EnterChargeControlMaunalCmd_flg()
    == ((boolean_T)ASWTYPE_TRUE)) &&
    (get_GbEDSM_DiagLeftChargeStartMaunalCmd_flg() == ((boolean_T)ASWTYPE_TRUE))
    && rtb_GbEBSW_CarPass_flg_k) ||
    ((get_GbEBSW_EnterCEChargeControlMaunalCmd_flg() == ((boolean_T)ASWTYPE_TRUE))
     && (get_GeECCR_CCU1CCUCC1STATE_enum() == (int32_T)
         Enum_GeECCR_CCU1CCUCC1STATE_Fully_Connected) &&
     rtb_GbEBSW_CarPass_flg_k));
  if ((get_GeECCR_CCU1CCUSTATE_enum() == (int32_T)
       Enum_GeECCR_CCU1CCUSTATE_PowerDown) || (((boolean_T)ASWTYPE_TRUE) ==
       get_GbEBSW_UserStopCCU1Chg_flg()) || (((boolean_T)ASWTYPE_TRUE) ==
       get_GbEBSW_LeftVIPChrgStopSuccess_flg()) ||
      (!(get_GeECCR_CCU1CCUCC1STATE_enum() == (int32_T)
         Enum_GeECCR_CCU1CCUCC1STATE_Fully_Connected)) || (((boolean_T)
        ASWTYPE_TRUE) == EACM_U.GbEBSW_EMGStopAuxIn_flg) || ((((boolean_T)
         ASWTYPE_TRUE) == get_GbEDSM_EnterChargeControlMaunalCmd_flg()) &&
       (((boolean_T)ASWTYPE_TRUE) == get_GbEDSM_DiagLeftChargeStopMaunalCmd_flg())))
  {
    rtb_GbEACM_AGunStartCheckForCar = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_GbEACM_AGunStartCheckForCar = ((boolean_T)ASWTYPE_FALSE);
  }

  if (EACM_DW.is_active_c3_EACM == 0U) {
    EACM_DW.is_active_c3_EACM = 1U;
    EACM_DW.is_c3_EACM = EACM_IN_DISABLE;
    EACM_B.GbEACM_LeftCheckSuccess_flg = false;
  } else if (EACM_DW.is_c3_EACM == EACM_IN_DISABLE) {
    if (rtb_GbEBSW_CarPass_flg && (!rtb_GbEACM_AGunStartCheckForCar)) {
      EACM_DW.is_c3_EACM = EACM_IN_ENABLE;
      EACM_B.GbEACM_LeftCheckSuccess_flg = true;
    }
  } else {
    if (rtb_GbEACM_AGunStartCheckForCar && (!rtb_GbEBSW_CarPass_flg)) {
      EACM_DW.is_c3_EACM = EACM_IN_DISABLE;
      EACM_B.GbEACM_LeftCheckSuccess_flg = false;
    }
  }

  if (CbEACM_LeftCheckSuccessOvrSwt_flg) {
    set_GbEACM_LeftCheckSuccess_flg(CbEACM_LeftCheckSuccessOvr_flg);
  } else {
    set_GbEACM_LeftCheckSuccess_flg(EACM_B.GbEACM_LeftCheckSuccess_flg);
  }

  rtb_GbEBSW_CarPass_flg = (get_GeECCR_CCU1CCUSTATE_enum() == (int32_T)
    Enum_GeECCR_CCU1CCUSTATE_Charge);
  if (((get_GbEBSW_UserStopCCU1Chg_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       rtb_GbEBSW_CarPass_flg) || ((get_GbETCR_LeftServeStpChgCmd_flg() ==
        ((boolean_T)ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg) ||
      ((get_GbEBSW_LeftVIPChrgStopSuccess_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       rtb_GbEBSW_CarPass_flg) || ((EACM_U.GbEBSW_EMGStopAuxIn_flg ==
        ((boolean_T)ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg) ||
      ((get_GbEDSM_EnterChargeControlMaunalCmd_flg() == ((boolean_T)ASWTYPE_TRUE))
       && (get_GbEDSM_DiagLeftChargeStopMaunalCmd_flg() == ((boolean_T)
         ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg)) {
    rtb_GbEBSW_CarPass_flg = ((boolean_T)ASWTYPE_TRUE);
  } else if (((((boolean_T)ASWTYPE_TRUE) != rtb_GbEBSW_CarPass_flg) ||
              (!(get_GeECCR_CCU1CCUCC1STATE_enum() ==
                 EACM_ConstB.DataTypeConversion1_e))) && (((boolean_T)
               ASWTYPE_TRUE) == EACM_DW.StateName)) {
    rtb_GbEBSW_CarPass_flg = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_GbEBSW_CarPass_flg = EACM_DW.StateName;
  }

  if (CbEACM_LeftStopChargeSuccessOvrSwt_flg) {
    set_GbEACM_LeftStopChargeSuccess_flg(CbEACM_LeftStopChargeSuccessOvr_flg);
  } else {
    set_GbEACM_LeftStopChargeSuccess_flg(rtb_GbEBSW_CarPass_flg);
  }

  EACM_Start_Stop(get_GbEBSW_LeftCCUStartCheck_flg(),
                  get_GbEBSW_LeftCCUStopCheck_flg(), &EACM_B.sf_Start_Stop,
                  &EACM_DW.sf_Start_Stop);
  switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
   case 0:
    rtb_GeEACM_CCU1MCVCardType_enum = 0U;
    rtb_GbEACM_AGunStartCheckForCar = false;
    break;

   case 1:
    rtb_GeEACM_CCU1MCVCardType_enum = get_GeEBSW_CCU1CCVChargeType_enum();
    rtb_GbEACM_AGunStartCheckForCar = get_GbEBSW_LeftCCUStopCheck_flg();
    break;

   default:
    rtb_GeEACM_CCU1MCVCardType_enum = get_GeEBSW_CCU1CCVChargeType_enum();
    rtb_GbEACM_AGunStartCheckForCar = get_GbEBSW_LeftCCUStopCheck_flg();
    break;
  }

  if (CbEACM_CCU1MCVCardTypeOvrSwt_flg) {
    set_GeEACM_CCU1MCVCardType_enum(CeEACM_CCU1MCVCardTypeOvr_enum);
  } else {
    if (EACM_B.sf_Start_Stop.StartFlg) {
      rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_TRUE);
    } else {
      rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_FALSE);
    }

    if (rtb_GbEBSW_CarPass_flg_k) {
      if (!EACM_B.TmOutFlg_d) {
        set_GeEACM_CCU1MCVCardType_enum(rtb_GeEBSW_CCU1CCVChargeType_en);
      } else {
        set_GeEACM_CCU1MCVCardType_enum(EACM_ConstB.DataTypeConversion_n);
      }
    } else if (rtb_GbEACM_AGunStartCheckForCar) {
      set_GeEACM_CCU1MCVCardType_enum(rtb_GeEACM_CCU1MCVCardType_enum);
    } else {
      set_GeEACM_CCU1MCVCardType_enum(EACM_ConstB.DataTypeConversion1_n);
    }
  }

  EACM_Trigger_Rising1(rtb_GbEACM_AGunStartCheckForCar,
                       &EACM_B.Trigger_Rising1_d, &EACM_DW.Trigger_Rising1_d);
  rtb_DataTypeConversion = (Enum_EACMCCU1CCVChargeType)
    rtb_GeEACM_CCU1MCVCardType_enum;
  switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
   case 0:
    rtb_GbEBSW_CarPass_flg_k = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;
  }

  EACM_Timer(rtb_GbEBSW_CarPass_flg_k == ((boolean_T)ASWTYPE_TRUE),
             &EACM_B.sf_Timer_o, &EACM_DW.sf_Timer_o);
  if (EACM_B.Trigger_Rising1_d.LogicalOperator &&
      ((Enum_EACMCCU1CCVChargeType_CreditCard == rtb_DataTypeConversion) ||
       (rtb_DataTypeConversion == Enum_EACMCCU1CCVChargeType_RFCard))) {
    rtb_GbEACM_AGunStartCheckForCar = ((boolean_T)ASWTYPE_TRUE);
  } else if (((rtb_GbEACM_AGunStartCheckForCar == ((boolean_T)ASWTYPE_FALSE)) &&
              (EACM_DW.StateName_d == ((boolean_T)ASWTYPE_TRUE))) ||
             ((EACM_DW.StateName_d == ((boolean_T)ASWTYPE_TRUE)) &&
              (EACM_B.sf_Timer_o.Output != 0.0))) {
    rtb_GbEACM_AGunStartCheckForCar = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_GbEACM_AGunStartCheckForCar = EACM_DW.StateName_d;
  }

  if (CbEACM_AGunUserStopForCardOvrSwt_flg) {
    set_GbEACM_AGunUserStopForCard_flg(CbEACM_AGunUserStopForCardOvr_flg);
  } else {
    set_GbEACM_AGunUserStopForCard_flg(rtb_GbEACM_AGunStartCheckForCar);
  }

  for (i = 0; i < 8; i++) {
    EACM_Y.GcEACM_LeftStaRFIDCardUID_numb[i] =
      get_GcEACM_LeftStaRFIDCardUID_numb( i );
  }

  switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
   case 0:
    rtb_GbETCR_LeftServeStaChgCmd_f = false;
    break;

   case 1:
    rtb_GbETCR_LeftServeStaChgCmd_f = get_GbEBSW_RightCCUStartCheck_flg();
    break;

   default:
    rtb_GbETCR_LeftServeStaChgCmd_f = get_GbEBSW_RightCCUStartCheck_flg();
    break;
  }

  EACM_Trigger_Rising1(rtb_GbETCR_LeftServeStaChgCmd_f,
                       &EACM_B.Trigger_Rising1_a, &EACM_DW.Trigger_Rising1_a);
  switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
   case 0:
    rtb_GeEBSW_CCU1CCVChargeType_en = 0U;
    break;

   case 1:
    rtb_GeEBSW_CCU1CCVChargeType_en = get_GeEBSW_CCU2CCVChargeType_enum();
    break;

   default:
    rtb_GeEBSW_CCU1CCVChargeType_en = get_GeEBSW_CCU2CCVChargeType_enum();
    break;
  }

  rtb_DataTypeConversion_g = (Enum_EACMCCU2CCVChargeType)
    rtb_GeEBSW_CCU1CCVChargeType_en;
  switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
   case 0:
    rtb_GbEBSW_CarPass_flg_k = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;
  }

  EACM_Timer(rtb_GbEBSW_CarPass_flg_k == ((boolean_T)ASWTYPE_TRUE),
             &EACM_B.sf_Timer_o0, &EACM_DW.sf_Timer_o0);
  if (EACM_B.Trigger_Rising1_a.LogicalOperator &&
      ((Enum_EACMCCU2CCVChargeType_CreditCard == rtb_DataTypeConversion_g) ||
       (rtb_DataTypeConversion_g == Enum_EACMCCU2CCVChargeType_RFCard))) {
    GbEBSW_CarPass_flg_prev_c = ((boolean_T)ASWTYPE_TRUE);
  } else if (((rtb_GbETCR_LeftServeStaChgCmd_f == ((boolean_T)ASWTYPE_FALSE)) &&
              (EACM_DW.StateName_e == ((boolean_T)ASWTYPE_TRUE))) ||
             ((EACM_DW.StateName_e == ((boolean_T)ASWTYPE_TRUE)) &&
              (EACM_B.sf_Timer_o0.Output != 0.0))) {
    GbEBSW_CarPass_flg_prev_c = ((boolean_T)ASWTYPE_FALSE);
  } else {
    GbEBSW_CarPass_flg_prev_c = EACM_DW.StateName_e;
  }

  if (CbEACM_BGunStartCheckForCardOvrSwt_flg) {
    set_GbEACM_BGunStartCheckForCard_flg(CbEACM_BGunStartCheckForCardOvr_flg);
  } else {
    set_GbEACM_BGunStartCheckForCard_flg(GbEBSW_CarPass_flg_prev_c);
  }

  if (rtb_GeEBSW_CCU1CCVChargeType_en > 0) {
    EACM_B.Check = rtb_GeEBSW_CCU1CCVChargeType_en;
  }

  EACM_Trigger_Rising1(rtb_GbETCR_LeftServeStaChgCmd_f,
                       &EACM_B.Trigger_Rising2_i, &EACM_DW.Trigger_Rising2_i);
  if (EACM_B.Trigger_Rising2_i.LogicalOperator) {
    EACM_B.Check_b = EACM_B.Trigger_Rising2_i.LogicalOperator;
  }

  if (EACM_B.Check_b) {
    rtb_GeEBSW_CCU1CCVChargeType_en = EACM_B.Check;
  } else {
    rtb_GeEBSW_CCU1CCVChargeType_en = EACM_ConstB.DataTypeConversion1_fu;
  }

  switch (rtb_GeEBSW_CCU1CCVChargeType_en) {
   case 0:
    rtb_GbEBSW_CarPass_flg_k = false;
    rtb_GeEACM_CCU1MCVCardType_enum = 0U;
    rtb_GbEACM_BGunStartCheckForCar = false;
    rtb_GbETCR_RightServeStaChgCmd_ = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    rtb_GeEACM_CCU1MCVCardType_enum = rtb_GeEBSW_CCU1CCVChargeType_en;
    rtb_GbEACM_BGunStartCheckForCar = GbEBSW_CarPass_flg_prev_c;
    rtb_GbETCR_RightServeStaChgCmd_ = get_GbETCR_RightServeStaChgCmd_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    rtb_GeEACM_CCU1MCVCardType_enum = rtb_GeEBSW_CCU1CCVChargeType_en;
    rtb_GbEACM_BGunStartCheckForCar = GbEBSW_CarPass_flg_prev_c;
    rtb_GbETCR_RightServeStaChgCmd_ = get_GbETCR_RightServeStaChgCmd_flg();
    break;
  }

  if (EACM_DW.temporalCounter_i1 < 2047U) {
    EACM_DW.temporalCounter_i1++;
  }

  GbEBSW_CarPass_flg_prev = EACM_DW.GbEBSW_CarPass_flg_start;
  EACM_DW.GbEBSW_CarPass_flg_start = rtb_GbEBSW_CarPass_flg_k;
  if (EACM_DW.is_active_c12_EACM == 0U) {
    EACM_DW.is_active_c12_EACM = 1U;
    EACM_DW.is_c12_EACM = EACM_IN_DISABLE;
    EACM_B.StartCalTmFlg = false;
    EACM_B.TmOutFlg = false;
  } else if (EACM_DW.is_c12_EACM == EACM_IN_DISABLE) {
    if ((GbEBSW_CarPass_flg_prev != EACM_DW.GbEBSW_CarPass_flg_start) &&
        EACM_DW.GbEBSW_CarPass_flg_start && rtb_GbEACM_BGunStartCheckForCar &&
        (((int32_T)Enum_EACMCCU2CCVChargeType_CreditCard ==
          rtb_GeEACM_CCU1MCVCardType_enum) || ((int32_T)
          Enum_EACMCCU2CCVChargeType_RFCard == rtb_GeEACM_CCU1MCVCardType_enum)))
    {
      EACM_DW.is_c12_EACM = EACM_IN_ENABLE;
      EACM_DW.is_ENABLE_p = EACM_IN_B_g;
      EACM_DW.temporalCounter_i1 = 0U;
      EACM_B.StartCalTmFlg = true;
    }
  } else if (((int32_T)Enum_EACMCCU2CCVChargeType_CreditCard !=
              rtb_GeEACM_CCU1MCVCardType_enum) && ((int32_T)
              Enum_EACMCCU2CCVChargeType_RFCard !=
              rtb_GeEACM_CCU1MCVCardType_enum)) {
    EACM_DW.is_ENABLE_p = EACM_IN_NO_ACTIVE_CHILD_m;
    EACM_DW.is_c12_EACM = EACM_IN_DISABLE;
    EACM_B.StartCalTmFlg = false;
    EACM_B.TmOutFlg = false;
  } else {
    if ((EACM_DW.is_ENABLE_p == EACM_IN_B_g) && ((EACM_DW.temporalCounter_i1 >=
          1500) || rtb_GbETCR_RightServeStaChgCmd_)) {
      EACM_DW.is_ENABLE_p = EACM_IN_B1;
      EACM_B.TmOutFlg = true;
      EACM_B.StartCalTmFlg = false;
    }
  }

  if (CbEACM_CCU2TFDAuthReqOvrSwt_flg) {
    set_GbEACM_CCU2TFDAuthReq_flg(CbEACM_CCU2TFDAuthReqOvr_flg);
  } else if (EACM_B.StartCalTmFlg) {
    set_GbEACM_CCU2TFDAuthReq_flg(((boolean_T)ASWTYPE_TRUE));
  } else if (EACM_B.TmOutFlg) {
    set_GbEACM_CCU2TFDAuthReq_flg(((boolean_T)ASWTYPE_FALSE));
  } else if ((EACM_B.TmOutFlg == ((boolean_T)ASWTYPE_FALSE)) && (((boolean_T)
               ASWTYPE_FALSE) == EACM_B.StartCalTmFlg)) {
    set_GbEACM_CCU2TFDAuthReq_flg(((boolean_T)ASWTYPE_FALSE));
  } else {
    set_GbEACM_CCU2TFDAuthReq_flg(((boolean_T)ASWTYPE_TRUE));
  }

  if (CbEACM_RightStaRFIDCardUIDOvrSwt_flg) {
    for (i = 0; i < 8; i++) {
      set_GcEACM_RightStaRFIDCardUID_numb( i ,
        CcEACM_RightStaRFIDCardUIDOvr_numb);
    }
  } else {
    if (EACM_B.StartCalTmFlg) {
      switch (rtb_GeEBSW_CCU1CCVChargeType_en) {
       case 0:
        rtb_GcEBSW_CCVRFIDCardUID_num_d[0] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[1] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[2] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[3] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[4] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[5] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[6] = 0U;
        rtb_GcEBSW_CCVRFIDCardUID_num_d[7] = 0U;
        break;

       case 1:
        for (i = 0; i < 8; i++) {
          rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = get_GcEBSW_OCPPDefaultUID_numb( i
            );
        }
        break;

       default:
        for (i = 0; i < 8; i++) {
          rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = get_GcEBSW_CCVRFIDCardUID_numb( i
            );
        }
        break;
      }
    } else {
      for (i = 0; i < 8; i++) {
        rtb_GcEBSW_CCVRFIDCardUID_num_d[i] = EACM_ConstB.DataTypeConversion_p;
      }
    }

    for (i = 0; i < 8; i++) {
      set_GcEACM_RightStaRFIDCardUID_numb( i , rtb_GcEBSW_CCVRFIDCardUID_num_d[i]);
    }
  }

  rtb_GbEBSW_CarPass_flg_k = ((int32_T)Enum_GeECCR_CCU1CCUSTATE_Standby ==
    get_GeECCR_CCU2CCUSTATE_enum());
  rtb_GbEBSW_CarPass_flg_k = (((((boolean_T)ASWTYPE_TRUE) ==
    get_GbETCR_RightServeStaChgCmd_flg()) && rtb_GbEBSW_CarPass_flg_k) ||
    ((((boolean_T)ASWTYPE_TRUE) == get_GbEBSW_RightVIPChrgCheckSuccess_flg()) &&
     rtb_GbEBSW_CarPass_flg_k) || ((((boolean_T)ASWTYPE_TRUE) ==
    get_GbEDSM_EnterChargeControlMaunalCmd_flg()) && (((boolean_T)ASWTYPE_TRUE) ==
    get_GbEDSM_DiagRightChargeStartMaunalCmd_flg()) && rtb_GbEBSW_CarPass_flg_k)
    || ((((boolean_T)ASWTYPE_TRUE) ==
         get_GbEBSW_EnterCEChargeControlMaunalCmd_flg()) && ((int32_T)
    Enum_GeECCR_CCU2CCUCC1STATE_Fully_Connected ==
    get_GeECCR_CCU2CCUCC1STATE_enum()) && rtb_GbEBSW_CarPass_flg_k));
  if ((get_GeECCR_CCU2CCUSTATE_enum() == (int32_T)
       Enum_GeECCR_CCU1CCUSTATE_PowerDown) || (((boolean_T)ASWTYPE_TRUE) ==
       get_GbEBSW_UserStopCCU2Chg_flg()) || (((boolean_T)ASWTYPE_TRUE) ==
       get_GbEBSW_RightVIPChrgStopSuccess_flg()) ||
      (!(get_GeECCR_CCU2CCUCC1STATE_enum() == (int32_T)
         Enum_GeECCR_CCU1CCUCC1STATE_Fully_Connected)) || (((boolean_T)
        ASWTYPE_TRUE) == EACM_U.GbEBSW_EMGStopAuxIn_flg) || ((((boolean_T)
         ASWTYPE_TRUE) == get_GbEDSM_EnterChargeControlMaunalCmd_flg()) &&
       (((boolean_T)ASWTYPE_TRUE) == get_GbEDSM_DiagRightChargeStopMaunalCmd_flg
        ()))) {
    rtb_GbEACM_BGunStartCheckForCar = ((boolean_T)ASWTYPE_TRUE);
  } else {
    rtb_GbEACM_BGunStartCheckForCar = ((boolean_T)ASWTYPE_FALSE);
  }

  if (EACM_DW.is_active_c1_EACM == 0U) {
    EACM_DW.is_active_c1_EACM = 1U;
    EACM_DW.is_c1_EACM = EACM_IN_DISABLE;
    EACM_B.GbEACM_RightCheckSuccess_flg = false;
  } else if (EACM_DW.is_c1_EACM == EACM_IN_DISABLE) {
    if (rtb_GbEBSW_CarPass_flg_k && (!rtb_GbEACM_BGunStartCheckForCar)) {
      EACM_DW.is_c1_EACM = EACM_IN_ENABLE;
      EACM_B.GbEACM_RightCheckSuccess_flg = true;
    }
  } else {
    if (rtb_GbEACM_BGunStartCheckForCar && (!rtb_GbEBSW_CarPass_flg_k)) {
      EACM_DW.is_c1_EACM = EACM_IN_DISABLE;
      EACM_B.GbEACM_RightCheckSuccess_flg = false;
    }
  }

  if (CbEACM_RightCheckSuccessOvrSwt_flg) {
    set_GbEACM_RightCheckSuccess_flg(CbEACM_RightCheckSuccessOvr_flg);
  } else {
    set_GbEACM_RightCheckSuccess_flg(EACM_B.GbEACM_RightCheckSuccess_flg);
  }

  rtb_GbEBSW_CarPass_flg_k = (get_GeECCR_CCU2CCUSTATE_enum() == (int32_T)
    Enum_GeECCR_CCU2CCUSTATE_Charge);
  if (((get_GbEBSW_UserStopCCU2Chg_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       rtb_GbEBSW_CarPass_flg_k) || ((get_GbETCR_RightServeStpChgCmd_flg() ==
        ((boolean_T)ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg_k) ||
      ((get_GbEBSW_RightVIPChrgStopSuccess_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       rtb_GbEBSW_CarPass_flg_k) || ((EACM_U.GbEBSW_EMGStopAuxIn_flg ==
        ((boolean_T)ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg_k) ||
      ((get_GbEDSM_EnterChargeControlMaunalCmd_flg() == ((boolean_T)ASWTYPE_TRUE))
       && (get_GbEDSM_DiagRightChargeStopMaunalCmd_flg() == ((boolean_T)
         ASWTYPE_TRUE)) && rtb_GbEBSW_CarPass_flg_k)) {
    rtb_GbEACM_BGunStartCheckForCar = ((boolean_T)ASWTYPE_TRUE);
  } else if (((((boolean_T)ASWTYPE_TRUE) != rtb_GbEBSW_CarPass_flg_k) ||
              (!(get_GeECCR_CCU2CCUCC1STATE_enum() ==
                 EACM_ConstB.DataTypeConversion1_h))) && (((boolean_T)
               ASWTYPE_TRUE) == EACM_DW.StateName_o)) {
    rtb_GbEACM_BGunStartCheckForCar = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_GbEACM_BGunStartCheckForCar = EACM_DW.StateName_o;
  }

  if (CbEACM_RightStopChargeSuccessOvrSwt_flg) {
    set_GbEACM_RightStopChargeSuccess_flg(CbEACM_RightStopChargeSuccessOvr_flg);
  } else {
    set_GbEACM_RightStopChargeSuccess_flg(rtb_GbEACM_BGunStartCheckForCar);
  }

  EACM_Start_Stop(get_GbEBSW_RightCCUStartCheck_flg(),
                  get_GbEBSW_RightCCUStopCheck_flg(), &EACM_B.sf_Start_Stop_p,
                  &EACM_DW.sf_Start_Stop_p);
  switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
   case 0:
    rtb_GeEACM_CCU1MCVCardType_enum = 0U;
    rtb_GbETCR_RightServeStaChgCmd_ = false;
    break;

   case 1:
    rtb_GeEACM_CCU1MCVCardType_enum = get_GeEBSW_CCU2CCVChargeType_enum();
    rtb_GbETCR_RightServeStaChgCmd_ = get_GbEBSW_RightCCUStopCheck_flg();
    break;

   default:
    rtb_GeEACM_CCU1MCVCardType_enum = get_GeEBSW_CCU2CCVChargeType_enum();
    rtb_GbETCR_RightServeStaChgCmd_ = get_GbEBSW_RightCCUStopCheck_flg();
    break;
  }

  if (CbEACM_CCU2MCVCardTypeOvrSwt_flg) {
    set_GeEACM_CCU2MCVCardType_enum(CeEACM_CCU2MCVCardTypeOvr_enum);
  } else {
    if (EACM_B.sf_Start_Stop_p.StartFlg) {
      rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_TRUE);
    } else {
      rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_FALSE);
    }

    if (rtb_GbEBSW_CarPass_flg_k) {
      if (!EACM_B.TmOutFlg) {
        set_GeEACM_CCU2MCVCardType_enum(rtb_GeEBSW_CCU1CCVChargeType_en);
      } else {
        set_GeEACM_CCU2MCVCardType_enum(EACM_ConstB.DataTypeConversion_k);
      }
    } else if (rtb_GbETCR_RightServeStaChgCmd_) {
      set_GeEACM_CCU2MCVCardType_enum(rtb_GeEACM_CCU1MCVCardType_enum);
    } else {
      set_GeEACM_CCU2MCVCardType_enum(EACM_ConstB.DataTypeConversion1_d);
    }
  }

  EACM_Trigger_Rising1(rtb_GbETCR_RightServeStaChgCmd_,
                       &EACM_B.Trigger_Rising1_g, &EACM_DW.Trigger_Rising1_g);
  rtb_DataTypeConversion_g = (Enum_EACMCCU2CCVChargeType)
    rtb_GeEACM_CCU1MCVCardType_enum;
  switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
   case 0:
    rtb_GbEBSW_CarPass_flg_k = false;
    break;

   case 1:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;

   default:
    rtb_GbEBSW_CarPass_flg_k = get_GbEBSW_CarPass_flg();
    break;
  }

  EACM_Timer(rtb_GbEBSW_CarPass_flg_k == ((boolean_T)ASWTYPE_TRUE),
             &EACM_B.sf_Timer_j, &EACM_DW.sf_Timer_j);
  if (EACM_B.Trigger_Rising1_g.LogicalOperator &&
      ((Enum_EACMCCU2CCVChargeType_CreditCard == rtb_DataTypeConversion_g) ||
       (rtb_DataTypeConversion_g == Enum_EACMCCU2CCVChargeType_RFCard))) {
    rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_TRUE);
  } else if (((rtb_GbETCR_RightServeStaChgCmd_ == ((boolean_T)ASWTYPE_FALSE)) &&
              (EACM_DW.StateName_dz == ((boolean_T)ASWTYPE_TRUE))) ||
             ((EACM_DW.StateName_dz == ((boolean_T)ASWTYPE_TRUE)) &&
              (EACM_B.sf_Timer_j.Output != 0.0))) {
    rtb_GbEBSW_CarPass_flg_k = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_GbEBSW_CarPass_flg_k = EACM_DW.StateName_dz;
  }

  if (CbEACM_BGunUserStopForCardOvrSwt_flg) {
    set_GbEACM_BGunUserStopForCard_flg(CbEACM_BGunUserStopForCardOvr_flg);
  } else {
    set_GbEACM_BGunUserStopForCard_flg(rtb_GbEBSW_CarPass_flg_k);
  }

  for (i = 0; i < 8; i++) {
    EACM_Y.GcEACM_RightStaRFIDCardUID_numb[i] =
      get_GcEACM_RightStaRFIDCardUID_numb( i );
  }

  if (get_GbEBSW_LeftCCUStartCheck_flg()) {
    if (CbEACM_PrePaymentOvrSwt_flg) {
      set_GcEACM_PrePayment_rmb(CcEACM_PrePaymentOvr_rmb);
    } else if (rtb_GbEBSW_LeftCCUStartCheck_fl) {
      switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
       case 0:
        set_GcEACM_PrePayment_rmb(0.0F);
        break;

       case 1:
        set_GcEACM_PrePayment_rmb(get_GcEBSW_OCPPPrePayment_rmb());
        break;

       default:
        set_GcEACM_PrePayment_rmb(0.0F);
        break;
      }
    } else {
      set_GcEACM_PrePayment_rmb(0.0F);
    }

    if (CbEACM_ChrgFeeOvrSwt_flg) {
      set_GcEACM_ChrgFee_rmb(CcEACM_ChrgFeeOvr_rmb);
    } else if (rtb_GbEBSW_LeftCCUStartCheck_fl) {
      switch (get_GeEBSW_CCU1CCVChargeType_enum()) {
       case 0:
        set_GcEACM_ChrgFee_rmb(0.0F);
        break;

       case 1:
        set_GcEACM_ChrgFee_rmb(get_GcEBSW_OCPPChrgFee_rmb());
        break;

       default:
        set_GcEACM_ChrgFee_rmb(get_GcEBSW_OCPPChrgFee_rmb());
        break;
      }
    } else {
      set_GcEACM_ChrgFee_rmb(0.0F);
    }
  } else {
    if (CbEACM_PrePaymentOvrSwt_flg) {
      set_GcEACM_PrePayment_rmb(CcEACM_PrePaymentOvr_rmb);
    } else if (rtb_GbETCR_LeftServeStaChgCmd_f) {
      switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
       case 0:
        set_GcEACM_PrePayment_rmb(0.0F);
        break;

       case 1:
        set_GcEACM_PrePayment_rmb(get_GcEBSW_OCPPPrePayment_rmb());
        break;

       default:
        set_GcEACM_PrePayment_rmb(0.0F);
        break;
      }
    } else {
      set_GcEACM_PrePayment_rmb(0.0F);
    }

    if (CbEACM_ChrgFeeOvrSwt_flg) {
      set_GcEACM_ChrgFee_rmb(CcEACM_ChrgFeeOvr_rmb);
    } else if (rtb_GbETCR_LeftServeStaChgCmd_f) {
      switch (get_GeEBSW_CCU2CCVChargeType_enum()) {
       case 0:
        set_GcEACM_ChrgFee_rmb(0.0F);
        break;

       case 1:
        set_GcEACM_ChrgFee_rmb(get_GcEBSW_OCPPChrgFee_rmb());
        break;

       default:
        set_GcEACM_ChrgFee_rmb(get_GcEBSW_OCPPChrgFee_rmb());
        break;
      }
    } else {
      set_GcEACM_ChrgFee_rmb(0.0F);
    }
  }

  if (rtb_Switch3 || rtb_Switch4_o) {
    EACM_DW.Memory_PreviousInput = ((boolean_T)ASWTYPE_TRUE);
  } else {
    EACM_DW.Memory_PreviousInput = ((boolean_T)ASWTYPE_FALSE);
  }

  EACM_DW.StateName = rtb_GbEBSW_CarPass_flg;
  EACM_DW.StateName_d = rtb_GbEACM_AGunStartCheckForCar;
  EACM_DW.StateName_e = GbEBSW_CarPass_flg_prev_c;
  EACM_DW.StateName_o = rtb_GbEACM_BGunStartCheckForCar;
  EACM_DW.StateName_dz = rtb_GbEBSW_CarPass_flg_k;
}

/* Model initialize function */
void EACM_initialize(void)
{
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising1);
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising2);
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising1_d);
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising1_a);
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising2_i);
  EACM_Trigger_Rising1_Init(&EACM_DW.Trigger_Rising1_g);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
