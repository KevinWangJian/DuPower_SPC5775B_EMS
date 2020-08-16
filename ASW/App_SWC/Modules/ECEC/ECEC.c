/*
 * File: ECEC.c
 *
 * Code generated for Simulink model 'ECEC'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 15:32:52 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECEC.h"
#include "ECEC_private.h"

/* Named constants for Chart: '<S3>/ECEC_CCU1_10ms' */
#define ECEC_IN_CHARGE_COMPLETE        ((uint8_T)1U)
#define ECEC_IN_CREDIT_CARD            ((uint8_T)1U)
#define ECEC_IN_DISABLE                ((uint8_T)1U)
#define ECEC_IN_ELECTRICITY_CALCULATION ((uint8_T)1U)
#define ECEC_IN_ENABLE                 ((uint8_T)2U)
#define ECEC_IN_IN_CHARGING            ((uint8_T)2U)
#define ECEC_IN_JUDGE_CARD_TYPE        ((uint8_T)2U)
#define ECEC_IN_NO_ACTIVE_CHILD        ((uint8_T)0U)
#define ECEC_IN_RFID_CARD              ((uint8_T)3U)
#define ECEC_IN_START_CHARGE           ((uint8_T)2U)
#define IN_WITHOUT_RMB_CAUSE_CHARGE_OVE ((uint8_T)3U)

/* Block signals (auto storage) */
B_ECEC_T ECEC_B;

/* Block states (auto storage) */
DW_ECEC_T ECEC_DW;

/* Real-time model */
RT_MODEL_ECEC_T ECEC_M_;
RT_MODEL_ECEC_T *const ECEC_M = &ECEC_M_;

/* Forward declaration for local functions */
static void ECEC_ElectricityCalculation(void);
static void ECEC_CrdtCrdMaxChargeEnergy(void);
static void ECEC_ElectricityCalculation_g(void);
static void ECEC_CrdtCrdMaxChargeEnergy_m(void);

/* Function for Chart: '<S3>/ECEC_CCU1_10ms' */
static void ECEC_ElectricityCalculation(void)
{
  if ((int32_T)Enum_EACMCCU1MCVCardType_CrdtCrd ==
      get_GeEACM_CCU1MCVCardType_enum()) {
    ECEC_B.oGcECEC_CCU1ElectricityRate_rmb = ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH
      * get_GcEACM_ChrgFee_rmb();
  }

  if ((get_GcEACM_PrePayment_rmb() <= ECEC_B.oGcECEC_CCU1ElectricityRate_rmb) &&
      ((int32_T)Enum_EACMCCU1MCVCardType_CrdtCrd ==
       get_GeEACM_CCU1MCVCardType_enum())) {
    ECEC_B.oGcECEC_CCU1ElectricityRate_rmb = get_GcEACM_PrePayment_rmb();
  }
}

/* Function for Chart: '<S3>/ECEC_CCU1_10ms' */
static void ECEC_CrdtCrdMaxChargeEnergy(void)
{
  if ((int32_T)Enum_EACMCCU1MCVCardType_CrdtCrd ==
      get_GeEACM_CCU1MCVCardType_enum()) {
    ECEC_DW.LcECEC_CCU1MaxChargeEnergy_kwH = get_GcEACM_PrePayment_rmb() /
      get_GcEACM_ChrgFee_rmb();
  }
}

/* Function for Chart: '<S3>/ECEC_CCU2_10ms' */
static void ECEC_ElectricityCalculation_g(void)
{
  if ((int32_T)Enum_EACMCCU2MCVCardType_CrdtCrd ==
      get_GeEACM_CCU2MCVCardType_enum()) {
    ECEC_B.oGcECEC_CCU2ElectricityRate_rmb = ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH
      * get_GcEACM_ChrgFee_rmb();
  }

  if ((get_GcEACM_PrePayment_rmb() <= ECEC_B.oGcECEC_CCU2ElectricityRate_rmb) &&
      ((int32_T)Enum_EACMCCU2MCVCardType_CrdtCrd ==
       get_GeEACM_CCU2MCVCardType_enum())) {
    ECEC_B.oGcECEC_CCU2ElectricityRate_rmb = get_GcEACM_PrePayment_rmb();
  }
}

/* Function for Chart: '<S3>/ECEC_CCU2_10ms' */
static void ECEC_CrdtCrdMaxChargeEnergy_m(void)
{
  if ((int32_T)Enum_EACMCCU2MCVCardType_CrdtCrd ==
      get_GeEACM_CCU2MCVCardType_enum()) {
    ECEC_DW.LcECEC_CCU2MaxChargeEnergy_kwH = get_GcEACM_PrePayment_rmb() /
      get_GcEACM_ChrgFee_rmb();
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECEC_10ms_at_outport_1' */
void ECEC_10ms(void)
{
  real32_T rtb_Switch3;
  real32_T rtb_Switch1;
  boolean_T rtb_Init;
  uint8_T iGeECCR_CCU1CCUState_enum_prev;
  iGeECCR_CCU1CCUState_enum_prev = ECEC_DW.iGeECCR_CCU1CCUState_enum_start;
  ECEC_DW.iGeECCR_CCU1CCUState_enum_start = get_GeECCR_CCU1CCUSTATE_enum();
  if (ECEC_DW.is_active_c1_ECEC == 0U) {
    ECEC_DW.is_active_c1_ECEC = 1U;
    ECEC_DW.is_c1_ECEC = ECEC_IN_DISABLE;
    ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU1ChargeStatus_NoCharge;
    ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH = 0.0F;
    ECEC_DW.LcECEC_CCU1StrChargeEnergy_kwH = 0.0F;
    ECEC_B.oGbECEC_CCU1ElectricityCalFinis = false;
    ECEC_B.oGbECEC_CCU1ChargeOver_flg = false;
    ECEC_B.oGcECEC_CCU1ElectricityRate_rmb = 0.0F;
  } else if (ECEC_DW.is_c1_ECEC == ECEC_IN_DISABLE) {
    if (get_GbEBSW_WH1DCDCEMOnline_flg() && ((int32_T)
         Enum_ECCRCCU1CCUCC1State_FullConnect == get_GeECCR_CCU1CCUCC1STATE_enum
         ()) && ((iGeECCR_CCU1CCUState_enum_prev !=
                  ECEC_DW.iGeECCR_CCU1CCUState_enum_start) &&
                 (iGeECCR_CCU1CCUState_enum_prev == (int32_T)
                  Enum_ECCRCCU1State_PreChg)) && ((int32_T)
         Enum_ECCRCCU1State_Chging == get_GeECCR_CCU1CCUSTATE_enum())) {
      ECEC_DW.is_c1_ECEC = ECEC_IN_ENABLE;
      ECEC_DW.is_ENABLE_m = ECEC_IN_IN_CHARGING;
      ECEC_DW.is_IN_CHARGING_c = ECEC_IN_START_CHARGE;
      ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
        Enum_ECECCCU1ChargeStatus_Charging;
      ECEC_DW.LcECEC_CCU1StrChargeEnergy_kwH =
        get_GcEBSW_LeftDCWhCurrtEnerge_kwH();
      ECEC_CrdtCrdMaxChargeEnergy();
    } else {
      if ((iGeECCR_CCU1CCUState_enum_prev !=
           ECEC_DW.iGeECCR_CCU1CCUState_enum_start) &&
          (iGeECCR_CCU1CCUState_enum_prev == (int32_T)Enum_ECCRCCU1State_Chging)
          && (((int32_T)Enum_ECCRCCU1State_StopChg ==
               get_GeECCR_CCU1CCUSTATE_enum()) || ((int32_T)
            Enum_ECCRCCU1State_ChgFault == get_GeECCR_CCU1CCUSTATE_enum()) ||
              ((int32_T)Enum_ECCRCCU1State_Powerdown ==
               get_GeECCR_CCU1CCUSTATE_enum()))) {
        ECEC_DW.is_c1_ECEC = ECEC_IN_ENABLE;
        ECEC_DW.is_ENABLE_m = ECEC_IN_CHARGE_COMPLETE;
        ECEC_DW.is_CHARGE_COMPLETE_k = ECEC_IN_JUDGE_CARD_TYPE;
        ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
          Enum_ECECCCU1ChargeStatus_CompleCharge;
      }
    }
  } else if (((int32_T)Enum_ECCRCCU1State_NotReady ==
              get_GeECCR_CCU1CCUSTATE_enum()) || ((int32_T)
              Enum_ECCRCCU1State_Standby == get_GeECCR_CCU1CCUSTATE_enum()) ||
             ((int32_T)Enum_ECCRCCU1CCUCC1State_FullConnect !=
              get_GeECCR_CCU1CCUCC1STATE_enum())) {
    if (ECEC_DW.is_ENABLE_m == ECEC_IN_IN_CHARGING) {
      if (ECEC_DW.is_IN_CHARGING_c == IN_WITHOUT_RMB_CAUSE_CHARGE_OVE) {
        ECEC_B.oGbECEC_CCU1ChargeOver_flg = false;
        ECEC_DW.is_IN_CHARGING_c = ECEC_IN_NO_ACTIVE_CHILD;
      } else {
        ECEC_DW.is_IN_CHARGING_c = ECEC_IN_NO_ACTIVE_CHILD;
      }

      ECEC_DW.is_ENABLE_m = ECEC_IN_NO_ACTIVE_CHILD;
    } else {
      ECEC_DW.is_ENABLE_m = ECEC_IN_NO_ACTIVE_CHILD;
      ECEC_DW.is_CHARGE_COMPLETE_k = ECEC_IN_NO_ACTIVE_CHILD;
    }

    ECEC_DW.is_c1_ECEC = ECEC_IN_DISABLE;
    ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU1ChargeStatus_NoCharge;
    ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH = 0.0F;
    ECEC_DW.LcECEC_CCU1StrChargeEnergy_kwH = 0.0F;
    ECEC_B.oGbECEC_CCU1ElectricityCalFinis = false;
    ECEC_B.oGbECEC_CCU1ChargeOver_flg = false;
    ECEC_B.oGcECEC_CCU1ElectricityRate_rmb = 0.0F;
  } else if (ECEC_DW.is_ENABLE_m == ECEC_IN_CHARGE_COMPLETE) {
    if (ECEC_DW.is_CHARGE_COMPLETE_k == ECEC_IN_JUDGE_CARD_TYPE) {
      if ((int32_T)Enum_EACMCCU1MCVCardType_CrdtCrd ==
          get_GeEACM_CCU1MCVCardType_enum()) {
        ECEC_DW.is_CHARGE_COMPLETE_k = ECEC_IN_CREDIT_CARD;
        ECEC_B.oGbECEC_CCU1ElectricityCalFinis = true;
      } else {
        if (((int32_T)Enum_EACMCCU1MCVCardType_RFIDCrd ==
             get_GeEACM_CCU1MCVCardType_enum()) &&
            get_GcEBSW_OCPPCCU1CostVld_flg()) {
          ECEC_DW.is_CHARGE_COMPLETE_k = ECEC_IN_RFID_CARD;
          ECEC_B.oGbECEC_CCU1ElectricityCalFinis = true;
          ECEC_B.oGcECEC_CCU1ElectricityRate_rmb = get_GcEBSW_OCPPCCU1Cost_rmb();
        }
      }
    }
  } else if ((iGeECCR_CCU1CCUState_enum_prev !=
              ECEC_DW.iGeECCR_CCU1CCUState_enum_start) &&
             (iGeECCR_CCU1CCUState_enum_prev == (int32_T)
              Enum_ECCRCCU1State_Chging) && (((int32_T)
               Enum_ECCRCCU1State_StopChg == get_GeECCR_CCU1CCUSTATE_enum()) ||
              ((int32_T)Enum_ECCRCCU1State_ChgFault ==
               get_GeECCR_CCU1CCUSTATE_enum()) || ((int32_T)
               Enum_ECCRCCU1State_Powerdown == get_GeECCR_CCU1CCUSTATE_enum())))
  {
    if (ECEC_DW.is_IN_CHARGING_c == IN_WITHOUT_RMB_CAUSE_CHARGE_OVE) {
      ECEC_B.oGbECEC_CCU1ChargeOver_flg = false;
      ECEC_DW.is_IN_CHARGING_c = ECEC_IN_NO_ACTIVE_CHILD;
    } else {
      ECEC_DW.is_IN_CHARGING_c = ECEC_IN_NO_ACTIVE_CHILD;
    }

    ECEC_DW.is_ENABLE_m = ECEC_IN_CHARGE_COMPLETE;
    ECEC_DW.is_CHARGE_COMPLETE_k = ECEC_IN_JUDGE_CARD_TYPE;
    ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU1ChargeStatus_CompleCharge;
  } else {
    switch (ECEC_DW.is_IN_CHARGING_c) {
     case ECEC_IN_ELECTRICITY_CALCULATION:
      if (((int32_T)Enum_ECCRCCU1State_Chging == get_GeECCR_CCU1CCUSTATE_enum())
          && (ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH >=
              ECEC_DW.LcECEC_CCU1MaxChargeEnergy_kwH) && ((int32_T)
           Enum_EACMCCU1MCVCardType_CrdtCrd == get_GeEACM_CCU1MCVCardType_enum()))
      {
        ECEC_DW.is_IN_CHARGING_c = IN_WITHOUT_RMB_CAUSE_CHARGE_OVE;
        ECEC_B.oGbECEC_CCU1ChargeOver_flg = true;
        ECEC_ElectricityCalculation();
      } else {
        ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH = get_GcEBSW_LeftDCWhCurrtEnerge_kwH
          () - ECEC_DW.LcECEC_CCU1StrChargeEnergy_kwH;
        ECEC_ElectricityCalculation();
      }
      break;

     case ECEC_IN_START_CHARGE:
      if ((int32_T)Enum_ECCRCCU1State_Chging == get_GeECCR_CCU1CCUSTATE_enum())
      {
        ECEC_DW.is_IN_CHARGING_c = ECEC_IN_ELECTRICITY_CALCULATION;
        ECEC_B.oGeECEC_CCU1ChargeStatus_enum = (uint8_T)
          Enum_ECECCCU1ChargeStatus_Charging;
        ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH = get_GcEBSW_LeftDCWhCurrtEnerge_kwH
          () - ECEC_DW.LcECEC_CCU1StrChargeEnergy_kwH;
        ECEC_B.oGbECEC_CCU1ChargeOver_flg = false;
        ECEC_ElectricityCalculation();
      }
      break;
    }
  }

  iGeECCR_CCU1CCUState_enum_prev = ECEC_DW.iGeECCR_CCU2CCUState_enum_start;
  ECEC_DW.iGeECCR_CCU2CCUState_enum_start = get_GeECCR_CCU2CCUSTATE_enum();
  if (ECEC_DW.is_active_c2_ECEC == 0U) {
    ECEC_DW.is_active_c2_ECEC = 1U;
    ECEC_DW.is_c2_ECEC = ECEC_IN_DISABLE;
    ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU2ChargeStatus_NoCharge;
    ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH = 0.0F;
    ECEC_DW.LcECEC_CCU2StrChargeEnergy_kwH = 0.0F;
    ECEC_B.oGbECEC_CCU2ElectricityCalFinis = false;
    ECEC_B.oGbECEC_CCU2ChargeOver_flg = false;
    ECEC_B.oGcECEC_CCU2ElectricityRate_rmb = 0.0F;
  } else if (ECEC_DW.is_c2_ECEC == ECEC_IN_DISABLE) {
    if (get_GbEBSW_WH2DCDCEMOnline_flg() && ((int32_T)
         Enum_ECCRCCU2CCUCC1State_FullConnect == get_GeECCR_CCU2CCUCC1STATE_enum
         ()) && ((iGeECCR_CCU1CCUState_enum_prev !=
                  ECEC_DW.iGeECCR_CCU2CCUState_enum_start) &&
                 (iGeECCR_CCU1CCUState_enum_prev == (int32_T)
                  Enum_ECCRCCU2State_PreChg)) && ((int32_T)
         Enum_ECCRCCU2State_Chging == get_GeECCR_CCU2CCUSTATE_enum())) {
      ECEC_DW.is_c2_ECEC = ECEC_IN_ENABLE;
      ECEC_DW.is_ENABLE = ECEC_IN_IN_CHARGING;
      ECEC_DW.is_IN_CHARGING = ECEC_IN_START_CHARGE;
      ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
        Enum_ECECCCU2ChargeStatus_Charging;
      ECEC_DW.LcECEC_CCU2StrChargeEnergy_kwH =
        get_GcEBSW_RightDCWhCurrtEnerge_kwH();
      ECEC_CrdtCrdMaxChargeEnergy_m();
    } else {
      if ((iGeECCR_CCU1CCUState_enum_prev !=
           ECEC_DW.iGeECCR_CCU2CCUState_enum_start) &&
          (iGeECCR_CCU1CCUState_enum_prev == (int32_T)Enum_ECCRCCU2State_Chging)
          && (((int32_T)Enum_ECCRCCU2State_StopChg ==
               get_GeECCR_CCU2CCUSTATE_enum()) || ((int32_T)
            Enum_ECCRCCU2State_ChgFault == get_GeECCR_CCU2CCUSTATE_enum()) ||
              ((int32_T)Enum_ECCRCCU2State_Powerdown ==
               get_GeECCR_CCU2CCUSTATE_enum()))) {
        ECEC_DW.is_c2_ECEC = ECEC_IN_ENABLE;
        ECEC_DW.is_ENABLE = ECEC_IN_CHARGE_COMPLETE;
        ECEC_DW.is_CHARGE_COMPLETE = ECEC_IN_JUDGE_CARD_TYPE;
        ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
          Enum_ECECCCU2ChargeStatus_CompleCharge;
      }
    }
  } else if (((int32_T)Enum_ECCRCCU2State_NotReady ==
              get_GeECCR_CCU2CCUSTATE_enum()) || ((int32_T)
              Enum_ECCRCCU2State_Standby == get_GeECCR_CCU2CCUSTATE_enum()) ||
             ((int32_T)Enum_ECCRCCU2CCUCC1State_FullConnect !=
              get_GeECCR_CCU2CCUCC1STATE_enum())) {
    if (ECEC_DW.is_ENABLE == ECEC_IN_IN_CHARGING) {
      if (ECEC_DW.is_IN_CHARGING == IN_WITHOUT_RMB_CAUSE_CHARGE_OVE) {
        ECEC_B.oGbECEC_CCU2ChargeOver_flg = false;
        ECEC_DW.is_IN_CHARGING = ECEC_IN_NO_ACTIVE_CHILD;
      } else {
        ECEC_DW.is_IN_CHARGING = ECEC_IN_NO_ACTIVE_CHILD;
      }

      ECEC_DW.is_ENABLE = ECEC_IN_NO_ACTIVE_CHILD;
    } else {
      ECEC_DW.is_ENABLE = ECEC_IN_NO_ACTIVE_CHILD;
      ECEC_DW.is_CHARGE_COMPLETE = ECEC_IN_NO_ACTIVE_CHILD;
    }

    ECEC_DW.is_c2_ECEC = ECEC_IN_DISABLE;
    ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU2ChargeStatus_NoCharge;
    ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH = 0.0F;
    ECEC_DW.LcECEC_CCU2StrChargeEnergy_kwH = 0.0F;
    ECEC_B.oGbECEC_CCU2ElectricityCalFinis = false;
    ECEC_B.oGbECEC_CCU2ChargeOver_flg = false;
    ECEC_B.oGcECEC_CCU2ElectricityRate_rmb = 0.0F;
  } else if (ECEC_DW.is_ENABLE == ECEC_IN_CHARGE_COMPLETE) {
    if (ECEC_DW.is_CHARGE_COMPLETE == ECEC_IN_JUDGE_CARD_TYPE) {
      if ((int32_T)Enum_EACMCCU2MCVCardType_CrdtCrd ==
          get_GeEACM_CCU2MCVCardType_enum()) {
        ECEC_DW.is_CHARGE_COMPLETE = ECEC_IN_CREDIT_CARD;
        ECEC_B.oGbECEC_CCU2ElectricityCalFinis = true;
      } else {
        if (((int32_T)Enum_EACMCCU2MCVCardType_RFIDCrd ==
             get_GeEACM_CCU2MCVCardType_enum()) &&
            get_GcEBSW_OCPPCCU2CostVld_flg()) {
          ECEC_DW.is_CHARGE_COMPLETE = ECEC_IN_RFID_CARD;
          ECEC_B.oGbECEC_CCU2ElectricityCalFinis = true;
          ECEC_B.oGcECEC_CCU2ElectricityRate_rmb = get_GcEBSW_OCPPCCU2Cost_rmb();
        }
      }
    }
  } else if ((iGeECCR_CCU1CCUState_enum_prev !=
              ECEC_DW.iGeECCR_CCU2CCUState_enum_start) &&
             (iGeECCR_CCU1CCUState_enum_prev == (int32_T)
              Enum_ECCRCCU2State_Chging) && (((int32_T)
               Enum_ECCRCCU2State_StopChg == get_GeECCR_CCU2CCUSTATE_enum()) ||
              ((int32_T)Enum_ECCRCCU2State_ChgFault ==
               get_GeECCR_CCU2CCUSTATE_enum()) || ((int32_T)
               Enum_ECCRCCU2State_Powerdown == get_GeECCR_CCU2CCUSTATE_enum())))
  {
    if (ECEC_DW.is_IN_CHARGING == IN_WITHOUT_RMB_CAUSE_CHARGE_OVE) {
      ECEC_B.oGbECEC_CCU2ChargeOver_flg = false;
      ECEC_DW.is_IN_CHARGING = ECEC_IN_NO_ACTIVE_CHILD;
    } else {
      ECEC_DW.is_IN_CHARGING = ECEC_IN_NO_ACTIVE_CHILD;
    }

    ECEC_DW.is_ENABLE = ECEC_IN_CHARGE_COMPLETE;
    ECEC_DW.is_CHARGE_COMPLETE = ECEC_IN_JUDGE_CARD_TYPE;
    ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
      Enum_ECECCCU2ChargeStatus_CompleCharge;
  } else {
    switch (ECEC_DW.is_IN_CHARGING) {
     case ECEC_IN_ELECTRICITY_CALCULATION:
      if (((int32_T)Enum_ECCRCCU2State_Chging == get_GeECCR_CCU2CCUSTATE_enum())
          && (ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH >=
              ECEC_DW.LcECEC_CCU2MaxChargeEnergy_kwH) && ((int32_T)
           Enum_EACMCCU2MCVCardType_CrdtCrd == get_GeEACM_CCU2MCVCardType_enum()))
      {
        ECEC_DW.is_IN_CHARGING = IN_WITHOUT_RMB_CAUSE_CHARGE_OVE;
        ECEC_B.oGbECEC_CCU2ChargeOver_flg = true;
        ECEC_ElectricityCalculation_g();
      } else {
        ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH =
          get_GcEBSW_RightDCWhCurrtEnerge_kwH() -
          ECEC_DW.LcECEC_CCU2StrChargeEnergy_kwH;
        ECEC_ElectricityCalculation_g();
      }
      break;

     case ECEC_IN_START_CHARGE:
      if ((int32_T)Enum_ECCRCCU2State_Chging == get_GeECCR_CCU2CCUSTATE_enum())
      {
        ECEC_DW.is_IN_CHARGING = ECEC_IN_ELECTRICITY_CALCULATION;
        ECEC_B.oGeECEC_CCU2ChargeStatus_enum = (uint8_T)
          Enum_ECECCCU2ChargeStatus_Charging;
        ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH =
          get_GcEBSW_RightDCWhCurrtEnerge_kwH() -
          ECEC_DW.LcECEC_CCU2StrChargeEnergy_kwH;
        ECEC_B.oGbECEC_CCU2ChargeOver_flg = false;
        ECEC_ElectricityCalculation_g();
      }
      break;
    }
  }

  if (CbECEC_CCU1ChargeStatusOvrSwt_flg) {
    set_GeECEC_CCU1ChargeStatus_enum(CeECEC_CCU1ChargeStatusOvr_enum);
  } else {
    set_GeECEC_CCU1ChargeStatus_enum(ECEC_B.oGeECEC_CCU1ChargeStatus_enum);
  }

  if (CbECEC_CCU2ChargeOverOvrSwt_flg) {
    set_GbECEC_CCU2ChargeOver_flg(CbECEC_CCU2ChargeOverOvr_flg);
  } else {
    set_GbECEC_CCU2ChargeOver_flg(ECEC_B.oGbECEC_CCU2ChargeOver_flg);
  }

  if (CbECEC_CCU1ElectricityCalFinishOvrSwt_flg) {
    set_GbECEC_CCU1ElectricityCalFinish_flg
      (CbECEC_CCU1ElectricityCalFinishOvr_flg);
  } else {
    set_GbECEC_CCU1ElectricityCalFinish_flg
      (ECEC_B.oGbECEC_CCU1ElectricityCalFinis);
  }

  if (CbECEC_CCU1ElectricityRateOvrSwt_flg) {
    set_GcECEC_CCU1ElectricityRate_rmb(CcECEC_CCU1ElectricityRateOvr_rmb);
  } else {
    set_GcECEC_CCU1ElectricityRate_rmb(ECEC_B.oGcECEC_CCU1ElectricityRate_rmb);
  }

  if (CbECEC_CCU1ChargeEnergyOvrSwt_flg) {
    set_GcECEC_CCU1ChargeEnergy_kwH(CcECEC_CCU1ChargeEnergyOvr_kwH);
  } else {
    set_GcECEC_CCU1ChargeEnergy_kwH(ECEC_B.oGcECEC_CCU1ChargeEnergy_kwH);
  }

  if (CbECEC_CCU1ChargeOverOvrSwt_flg) {
    set_GbECEC_CCU1ChargeOver_flg(CbECEC_CCU1ChargeOverOvr_flg);
  } else {
    set_GbECEC_CCU1ChargeOver_flg(ECEC_B.oGbECEC_CCU1ChargeOver_flg);
  }

  if (CbECEC_CCU2ChargeStatusOvrSwt_flg) {
    set_GeECEC_CCU2ChargeStatus_enum(CeECEC_CCU2ChargeStatusOvr_enum);
  } else {
    set_GeECEC_CCU2ChargeStatus_enum(ECEC_B.oGeECEC_CCU2ChargeStatus_enum);
  }

  if (CbECEC_CCU2ElectricityCalFinishOvrSwt_flg) {
    set_GbECEC_CCU2ElectricityCalFinish_flg
      (CbECEC_CCU2ElectricityCalFinishOvr_flg);
  } else {
    set_GbECEC_CCU2ElectricityCalFinish_flg
      (ECEC_B.oGbECEC_CCU2ElectricityCalFinis);
  }

  if (CbECEC_CCU2ElectricityRateOvrSwt_flg) {
    set_GcECEC_CCU2ElectricityRate_rmb(CcECEC_CCU2ElectricityRateOvr_rmb);
  } else {
    set_GcECEC_CCU2ElectricityRate_rmb(ECEC_B.oGcECEC_CCU2ElectricityRate_rmb);
  }

  if (CbECEC_CCU2ChargeEnergyOvrSwt_flg) {
    set_GcECEC_CCU2ChargeEnergy_kwH(CcECEC_CCU2ChargeEnergyOvr_kwH);
  } else {
    set_GcECEC_CCU2ChargeEnergy_kwH(ECEC_B.oGcECEC_CCU2ChargeEnergy_kwH);
  }

  if (ECEC_DW.StateName != 0) {
    rtb_Init = get_GbEBSW_T645ThreePhaseOnline_flg();
  } else {
    rtb_Init = ECEC_DW.StateName_j;
  }

  ECEC_DW.StateName = 0U;
  ECEC_DW.StateName_j = get_GbEBSW_T645ThreePhaseOnline_flg();
  if (get_GbEBSW_T645ThreePhaseOnline_flg() && (!rtb_Init)) {
    ECEC_B.In1 = get_GcEBSW_ThreePhaseEnergy_kwH();
  }

  if (get_GbEBSW_T645ThreePhaseOnline_flg()) {
    rtb_Switch1 = ECEC_B.In1;
    rtb_Switch3 = get_GcEBSW_ThreePhaseEnergy_kwH();
  } else {
    rtb_Switch1 = 0.0F;
    rtb_Switch3 = 0.0F;
  }

  if (CbECEC_ACWhBeforeChgEnergyOvrSwt_flg) {
    set_GcECEC_ACWhBeforeChgEnergy_kwH(CcECEC_ACWhBeforeChgEnergyOvr_kwH);
  } else {
    set_GcECEC_ACWhBeforeChgEnergy_kwH(rtb_Switch1);
  }

  rtb_Init = (rtb_Switch1 > rtb_Switch3);
  if (CbECEC_ACWhChargeEnergyOvrSwt_flg) {
    set_GcECEC_ACWhChargeEnergy_kwH(CcECEC_ACWhChargeEnergyOvr_kwH);
  } else if (!rtb_Init) {
    set_GcECEC_ACWhChargeEnergy_kwH(rtb_Switch3 - rtb_Switch1);
  } else {
    set_GcECEC_ACWhChargeEnergy_kwH(0.0F);
  }

  if (CbECEC_ACWhComFaultOvrSwt_flg) {
    set_GbECEC_ACWhComFault_flg(CbECEC_ACWhComFaultOvr_flg);
  } else {
    set_GbECEC_ACWhComFault_flg((rtb_Init && get_GbEBSW_T645ThreePhaseOnline_flg
      ()));
  }

  if (CbECEC_ACWhAfterChgEnergyOvrSwt_flg) {
    set_GcECEC_ACWhAfterChgEnergy_kwH(CcECEC_ACWhAfterChgEnergyOvr_kwH);
  } else {
    set_GcECEC_ACWhAfterChgEnergy_kwH(rtb_Switch3);
  }
}

/* Model initialize function */
void ECEC_initialize(void)
{
  ECEC_DW.StateName = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
