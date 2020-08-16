/*
 * File: ETCR.c
 *
 * Code generated for Simulink model 'ETCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:37:39 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ETCR.h"
#include "ETCR_private.h"

/* Block states (auto storage) */
DW_ETCR_T ETCR_DW;

/* Real-time model */
RT_MODEL_ETCR_T ETCR_M_;
RT_MODEL_ETCR_T *const ETCR_M = &ETCR_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETCR_10ms_at_outport_1' */
void ETCR_10ms(void)
{
  boolean_T rtb_RelationalOperator_n;
  boolean_T rtb_LogicalOperator_c;
  real32_T rtb_Init;
  real32_T rtb_RelationalOperator_h;
  rtb_LogicalOperator_c = !ETCR_DW.StateName;
  if (rtb_LogicalOperator_c || (ETCR_DW.FixPtUnitDelay2_DSTATE != 0)) {
    rtb_Init = 0.0F;
  } else {
    rtb_Init = ETCR_DW.FixPtUnitDelay1_DSTATE;
  }

  rtb_RelationalOperator_n = (rtb_Init >= ETCR_ConstB.DataTypeConversion1);
  if (rtb_LogicalOperator_c) {
    ETCR_DW.FixPtUnitDelay1_DSTATE = 0.0F;
  } else {
    if (rtb_RelationalOperator_n) {
      rtb_RelationalOperator_h = 0.0F;
    } else {
      rtb_RelationalOperator_h = ETCR_ConstB.DataTypeConversion;
    }

    ETCR_DW.FixPtUnitDelay1_DSTATE = rtb_RelationalOperator_h + rtb_Init;
  }

  ETCR_DW.FixPtUnitDelay2_DSTATE = 0U;
  if (rtb_RelationalOperator_n) {
    if (CbETCR_0x1802F102UpdataOvrSwt_flg) {
      set_GbETCR_0x1802F102Updata_flg(CbETCR_0x1802F102UpdataOvr_flg);
    } else {
      set_GbETCR_0x1802F102Updata_flg(((boolean_T)ASWTYPE_FALSE));
    }
  }

  if (get_GbETCR_0x1802F102Updata_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_LogicalOperator_c = (get_GeCAN5_ServeStartChargeCmd_enum() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    rtb_LogicalOperator_c = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbETCR_LeftServeStaChgCmdOvrSwt_flg) {
    set_GbETCR_LeftServeStaChgCmd_flg(CbETCR_LeftServeStaChgCmdOvr_flg);
  } else if (!((get_GeECCR_CCU1CCUSTATE_enum() ==
                ETCR_ConstB.DataTypeConversion20) ||
               (get_GeECCR_CCU1CCUSTATE_enum() ==
                ETCR_ConstB.DataTypeConversion1_i))) {
    set_GbETCR_LeftServeStaChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  } else if (rtb_LogicalOperator_c && (get_GcCAN5_TFDTBOXCCUIndex_enum() ==
              ((boolean_T)ASWTYPE_TRUE))) {
    set_GbETCR_LeftServeStaChgCmd_flg(((boolean_T)ASWTYPE_TRUE));
  } else {
    set_GbETCR_LeftServeStaChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  }

  if (CbETCR_RightServeStaChgCmdOvrSwt_flg) {
    set_GbETCR_RightServeStaChgCmd_flg(CbETCR_RightServeStaChgCmdOvr_flg);
  } else if (!((get_GeECCR_CCU2CCUSTATE_enum() ==
                ETCR_ConstB.DataTypeConversion22) ||
               (get_GeECCR_CCU2CCUSTATE_enum() ==
                ETCR_ConstB.DataTypeConversion2))) {
    set_GbETCR_RightServeStaChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  } else if (rtb_LogicalOperator_c && (get_GcCAN5_TFDTBOXCCUIndex_enum() == 2))
  {
    set_GbETCR_RightServeStaChgCmd_flg(((boolean_T)ASWTYPE_TRUE));
  } else {
    set_GbETCR_RightServeStaChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  }

  if (get_GbETCR_0x1802F102Updata_flg() == ((boolean_T)ASWTYPE_TRUE)) {
    rtb_LogicalOperator_c = (get_GeCAN5_TFDServeStopChargeCmd_enum() ==
      ((boolean_T)ASWTYPE_TRUE));
  } else {
    rtb_LogicalOperator_c = ((boolean_T)ASWTYPE_FALSE);
  }

  if (CbETCR_LeftServeStpChgCmdOvrSwt_flg) {
    set_GbETCR_LeftServeStpChgCmd_flg(CbETCR_LeftServeStpChgCmdOvr_flg);
  } else if (get_GeECCR_CCU1CCUSTATE_enum() ==
             ETCR_ConstB.DataTypeConversion20_a) {
    set_GbETCR_LeftServeStpChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  } else if (rtb_LogicalOperator_c && (get_GcCAN5_TFDTBOXCCUIndex_enum() ==
              ((boolean_T)ASWTYPE_TRUE))) {
    set_GbETCR_LeftServeStpChgCmd_flg(((boolean_T)ASWTYPE_TRUE));
  } else {
    set_GbETCR_LeftServeStpChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  }

  if (CbETCR_RightServeStpChgCmdOvrSwt_flg) {
    set_GbETCR_RightServeStpChgCmd_flg(CbETCR_RightServeStpChgCmdOvr_flg);
  } else if (get_GeECCR_CCU2CCUSTATE_enum() ==
             ETCR_ConstB.DataTypeConversion22_g) {
    set_GbETCR_RightServeStpChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  } else if (rtb_LogicalOperator_c && (get_GcCAN5_TFDTBOXCCUIndex_enum() == 2))
  {
    set_GbETCR_RightServeStpChgCmd_flg(((boolean_T)ASWTYPE_TRUE));
  } else {
    set_GbETCR_RightServeStpChgCmd_flg(((boolean_T)ASWTYPE_FALSE));
  }

  if (CbETCR_TFDTBOXTimerInvalidOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerInvalid_flg(CcETCR_TFDTBOXTimerInvalidOvr_flg);
  } else {
    set_GcETCR_TFDTBOXTimerInvalid_flg(get_GcCAN5_TFDTBOXTimerInvalid_flg());
  }

  if (CbETCR_TFDTBOXTimerYearOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerYear_numb(CcETCR_TFDTBOXTimerYearOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerYear_numb(get_GcCAN5_TFDTBOXTimerYear_numb());
  }

  if (CbETCR_TFDTBOXTimerMonthOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerMonth_numb(CcETCR_TFDTBOXTimerMonthOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerMonth_numb(get_GcCAN5_TFDTBOXTimerMonth_numb());
  }

  if (CbETCR_TFDTBOXTimerDayOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerDay_numb(CcETCR_TFDTBOXTimerDayOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerDay_numb(get_GcCAN5_TFDTBOXTimerDay_numb());
  }

  if (CbETCR_TFDTBOXTimerHourOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerHour_numb(CcETCR_TFDTBOXTimerHourOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerHour_numb(get_GcCAN5_TFDTBOXTimerHour_numb());
  }

  if (CbETCR_TFDTBOXTimerMinuteOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerMinute_numb(CcETCR_TFDTBOXTimerMinuteOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerMinute_numb(get_GcCAN5_TFDTBOXTimerMinute_numb());
  }

  if (CbETCR_TFDTBOXTimerSecondOvrSwt_flg) {
    set_GcETCR_TFDTBOXTimerSecond_numb(CcETCR_TFDTBOXTimerSecondOvr_numb);
  } else {
    set_GcETCR_TFDTBOXTimerSecond_numb(get_GcCAN5_TFDTBOXTimerSecond_numb());
  }

  if (CbETCR_TFDAuthResultsOvrSwt_flg) {
    set_GeETCR_TFDAuthResults_enum(CeETCR_TFDAuthResultsOvr_enum);
  } else {
    set_GeETCR_TFDAuthResults_enum(get_GeCAN5_TFDAuthResults_enum());
  }

  if (CbETCR_TBOXCCU1OcppAvailabilityEnumOvrSwt_flg) {
    set_GeETCR_TBOXCCU1OcppAvailabilityEnum_enum
      (CeETCR_TBOXCCU1OcppAvailabilityEnumOvr_enum);
  } else {
    set_GeETCR_TBOXCCU1OcppAvailabilityEnum_enum
      (get_GeCAN5_TBOXCCU1OcppAvailabilityEnum_enum());
  }

  if (CbETCR_TBOXCCU2OcppAvailabilityEnumOvrSwt_flg) {
    set_GeETCR_TBOXCCU2OcppAvailabilityEnum_enum
      (CeETCR_TBOXCCU2OcppAvailabilityEnumOvr_enum);
  } else {
    set_GeETCR_TBOXCCU2OcppAvailabilityEnum_enum
      (get_GeCAN5_TBOXCCU2OcppAvailabilityEnum_enum());
  }

  ETCR_DW.StateName = get_GbETCR_0x1802F102Updata_flg();
}

/* Model initialize function */
void ETCR_initialize(void)
{
  ETCR_DW.FixPtUnitDelay2_DSTATE = 1U;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
