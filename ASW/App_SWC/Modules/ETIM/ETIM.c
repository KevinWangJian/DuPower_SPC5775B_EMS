/*
 * File: ETIM.c
 *
 * Code generated for Simulink model 'ETIM'.
 *
 * Company                        : DP
 * Author                         : 19455
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Wed Jul 15 15:30:23 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ETIM.h"
#include "ETIM_private.h"

/* Block signals (auto storage) */
B_ETIM_T ETIM_B;

/* Block states (auto storage) */
DW_ETIM_T ETIM_DW;

/* Real-time model */
RT_MODEL_ETIM_T ETIM_M_;
RT_MODEL_ETIM_T *const ETIM_M = &ETIM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ETIM_10ms_at_outport_1' */
void ETIM_10ms(void)
{
  Enum_ETCRTBOXCCU1OcppAvailability rtb_Switch7;
  Enum_ECCRCCU1State rtb_DataTypeConversion10_p;
  Enum_ECCRCCU1CCUCC1State rtb_DataTypeConversion7_l;
  if (ETIM_DW.UnitDelay2_DSTATE) {
    rtb_Switch7 = Enum_ETCRTBOXCCU1OcppAvailability_Avlbl;
  } else {
    rtb_Switch7 = (Enum_ETCRTBOXCCU1OcppAvailability)
      get_GeETCR_TBOXCCU1OcppAvailabilityEnum_enum();
  }

  if (rtb_Switch7 != Enum_ETCRTBOXCCU1OcppAvailability_Invalid) {
    ETIM_B.In1_j = rtb_Switch7;
  }

  if (CbETIM_OCPPCCU1StateOvrSwt_flg) {
    set_GeETIM_OCPPCCU1State_enum(CeETIM_OCPPCCU1StateOvr_enum);
  } else {
    rtb_DataTypeConversion10_p = (Enum_ECCRCCU1State)
      get_GeECCR_CCU1CCUSTATE_enum();
    if ((ETIM_B.In1_j == Enum_ETCRTBOXCCU1OcppAvailability_UnAvlbl) &&
        (rtb_DataTypeConversion10_p != Enum_ECCRCCU1State_ChgFault) &&
        (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_TRUE))) {
      set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion);
    } else {
      rtb_DataTypeConversion7_l = (Enum_ECCRCCU1CCUCC1State)
        get_GeECCR_CCU1CCUCC1STATE_enum();
      if ((ETIM_B.In1_j == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
          (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Standby) &&
          (rtb_DataTypeConversion7_l == Enum_ECCRCCU1CCUCC1State_NoConnect) &&
          (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion1);
      } else if ((ETIM_B.In1_j == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Standby) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect) &&
                 (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion2);
      } else if ((ETIM_B.In1_j == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Chging) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect)) {
        set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion3);
      } else if ((ETIM_B.In1_j == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_StopChg ||
                  rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Powerdown ) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect) &&
                 (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion4);
      } else if ((rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_ChgFault) ||
                 (get_GbEDEC_PackAAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_FALSE))) {
        set_GeETIM_OCPPCCU1State_enum(ETIM_ConstB.DataTypeConversion5);
      } else {
        set_GeETIM_OCPPCCU1State_enum(0U);
      }
    }
  }

  if (ETIM_DW.UnitDelay2_DSTATE_e) {
    rtb_Switch7 = Enum_ETCRTBOXCCU1OcppAvailability_Avlbl;
  } else {
    rtb_Switch7 = (Enum_ETCRTBOXCCU1OcppAvailability)
      get_GeETCR_TBOXCCU2OcppAvailabilityEnum_enum();
  }

  if (rtb_Switch7 != Enum_ETCRTBOXCCU1OcppAvailability_Invalid) {
    ETIM_B.In1 = rtb_Switch7;
  }

  if (CbETIM_OCPPCCU2StateOvrSwt_flg) {
    set_GeETIM_OCPPCCU2State_enum(CeETIM_OCPPCCU2StateOvr_enum);
  } else {
    rtb_DataTypeConversion10_p = (Enum_ECCRCCU1State)
      get_GeECCR_CCU2CCUSTATE_enum();
    if ((ETIM_B.In1 == Enum_ETCRTBOXCCU1OcppAvailability_UnAvlbl) &&
        (rtb_DataTypeConversion10_p != Enum_ECCRCCU1State_ChgFault) &&
        (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_TRUE))) {
      set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion_i);
    } else {
      rtb_DataTypeConversion7_l = (Enum_ECCRCCU1CCUCC1State)
        get_GeECCR_CCU2CCUCC1STATE_enum();
      if ((ETIM_B.In1 == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
          (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Standby) &&
          (rtb_DataTypeConversion7_l == Enum_ECCRCCU1CCUCC1State_NoConnect) &&
          (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion1_c);
      } else if ((ETIM_B.In1 == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Standby) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect) &&
                 (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion2_j);
      } else if ((ETIM_B.In1 == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Chging) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect)) {
        set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion3_h);
      } else if ((ETIM_B.In1 == Enum_ETCRTBOXCCU1OcppAvailability_Avlbl) &&
                 (rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_StopChg ||
                  rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_Powerdown) &&
                 (rtb_DataTypeConversion7_l ==
                  Enum_ECCRCCU1CCUCC1State_FullConnect) &&
                 (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_TRUE))) {
        set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion4_c);
      } else if ((rtb_DataTypeConversion10_p == Enum_ECCRCCU1State_ChgFault) ||
                 (get_GbEDEC_PackBAllowedDisChrg_flg() == ((boolean_T)
                   ASWTYPE_FALSE))) {
        set_GeETIM_OCPPCCU2State_enum(ETIM_ConstB.DataTypeConversion5_n);
      } else {
        set_GeETIM_OCPPCCU2State_enum(0U);
      }
    }
  }

  ETIM_DW.UnitDelay2_DSTATE = ETIM_DW.UnitDelay1_DSTATE;
  ETIM_DW.UnitDelay1_DSTATE = false;
  ETIM_DW.UnitDelay2_DSTATE_e = ETIM_DW.UnitDelay1_DSTATE_l;
  ETIM_DW.UnitDelay1_DSTATE_l = false;
}

/* Model initialize function */
void ETIM_initialize(void)
{
  ETIM_DW.UnitDelay2_DSTATE = true;
  ETIM_DW.UnitDelay1_DSTATE = true;
  ETIM_DW.UnitDelay2_DSTATE_e = true;
  ETIM_DW.UnitDelay1_DSTATE_l = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
