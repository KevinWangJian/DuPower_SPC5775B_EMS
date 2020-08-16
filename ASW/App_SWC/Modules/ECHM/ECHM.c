/*
 * File: ECHM.c
 *
 * Code generated for Simulink model 'ECHM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:07:51 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECHM.h"
#include "ECHM_private.h"

/* Block states (auto storage) */
DW_ECHM_T ECHM_DW;

/* Real-time model */
RT_MODEL_ECHM_T ECHM_M_;
RT_MODEL_ECHM_T *const ECHM_M = &ECHM_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECHM_10ms_at_outport_1' */
void ECHM_10ms(void)
{
  Enum_ECCRCCU1State rtb_DataTypeConversion2_n;
  Enum_ECCRCCU2State rtb_DataTypeConversion2_l;
  if (CbECHM_GunAStartChrgOvrSwt_flg) {
    set_GbECHM_GunAStartChrg_flg(CbECHM_GunAStartChrgOvr_flg);
  } else {
    rtb_DataTypeConversion2_n = (Enum_ECCRCCU1State)get_GeECCR_CCU1CCUSTATE_enum
      ();
    set_GbECHM_GunAStartChrg_flg(((get_GeECMM_ChrgCtrAMode_enum() != (int32_T)
      Enum_ECMMChrgCtrAMode_Offline) && (get_GbEACM_LeftCheckSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcEBCR_BMSARealSOC_pct() >=
      CcEBCR_BMSSOC30_pct) && (get_GeECCR_CCU1CCUCC1STATE_enum() == (int32_T)
      Enum_ECCRCCU1CCUCC1State_FullConnect) && ((rtb_DataTypeConversion2_n !=
      Enum_ECCRCCU1State_StopChg) && (rtb_DataTypeConversion2_n !=
      Enum_ECCRCCU1State_ChgFault) && (rtb_DataTypeConversion2_n !=
      Enum_ECCRCCU1State_Powerdown)) && (get_GbEDEC_GunAAllowedChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECHM_DW.Delay_DSTATE_c == ((boolean_T)
      ASWTYPE_FALSE))));
  }

  if (CbECHM_GunAStopChrgOvrSwt_flg) {
    set_GbECHM_GunAStopChrg_flg(CbECHM_GunAStopChrgOvr_flg);
  } else {
    rtb_DataTypeConversion2_n = (Enum_ECCRCCU1State)get_GeECCR_CCU1CCUSTATE_enum
      ();
    set_GbECHM_GunAStopChrg_flg(((get_GbEACM_LeftStopChargeSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GbECEC_CCU1ChargeOver_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GeECCR_CCU1CCUCC1STATE_enum() !=
      (int32_T)Enum_ECCRCCU1CCUCC1State_FullConnect) ||
      (get_GbEBSW_UserForceStopPACKA_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      ((rtb_DataTypeConversion2_n == Enum_ECCRCCU1State_StopChg) ||
       (rtb_DataTypeConversion2_n == Enum_ECCRCCU1State_ChgFault) ||
       (rtb_DataTypeConversion2_n == Enum_ECCRCCU1State_Powerdown)) ||
      (get_ECCR_CCU1BST181CFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      (get_ECCR_CCU1CST181DFAF2hUpdate_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      (get_GbEDEC_GunAAllowedChrg_flg() == ((boolean_T)ASWTYPE_FALSE)) ||
      (get_GbEBIM_PackANotAllowedDisCharge_flg() == ((boolean_T)ASWTYPE_TRUE)) ||
      (get_GcEBCR_BMSARealSOC_pct() <= CcEBCR_BMSASOC15_pct)));
  }

  ECHM_DW.Delay_DSTATE_c = get_GbECHM_GunAStopChrg_flg();
  if (CbECHM_GunBStartChrgOvrSwt_flg) {
    set_GbECHM_GunBStartChrg_flg(CbECHM_GunBStartChrgOvr_flg);
  } else {
    rtb_DataTypeConversion2_l = (Enum_ECCRCCU2State)get_GeECCR_CCU2CCUSTATE_enum
      ();
    set_GbECHM_GunBStartChrg_flg(((get_GeECMM_ChrgCtrBMode_enum() != (int32_T)
      Enum_ECMMChrgCtrAMode_Offline) && (get_GbEACM_RightCheckSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (get_GcEBCR_BMSBRealSOC_pct() >=
      CcEBCR_BMSSOC30_pct) && (get_GeECCR_CCU2CCUCC1STATE_enum() == (int32_T)
      Enum_ECCRCCU2CCUCC1State_FullConnect) && ((rtb_DataTypeConversion2_l !=
      Enum_ECCRCCU2State_StopChg) && (rtb_DataTypeConversion2_l !=
      Enum_ECCRCCU2State_ChgFault) && (rtb_DataTypeConversion2_l !=
      Enum_ECCRCCU2State_Powerdown)) && (get_GbEDEC_GunBAllowedChrg_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) && (ECHM_DW.Delay_DSTATE == ((boolean_T)
      ASWTYPE_FALSE))));
  }

  if (CbECHM_GunBStopChrgOvrSwt_flg) {
    set_GbECHM_GunBStopChrg_flg(CbECHM_GunBStopChrgOvr_flg);
  } else {
    set_GbECHM_GunBStopChrg_flg(((get_GbEACM_RightStopChargeSuccess_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GbECEC_CCU2ChargeOver_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GeECCR_CCU2CCUCC1STATE_enum() !=
      ECHM_ConstB.DataTypeConversion1) || (get_GbEBSW_UserForceStopPACKB_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || ((get_GeECCR_CCU2CCUSTATE_enum() ==
      ECHM_ConstB.DataTypeConversion2) || (get_GeECCR_CCU2CCUSTATE_enum() ==
      ECHM_ConstB.DataTypeConversion3) || (get_GeECCR_CCU2CCUSTATE_enum() ==
      ECHM_ConstB.DataTypeConversion4)) || (get_ECCR_CCU2BST181CFAF2hUpdate_flg()
      == ((boolean_T)ASWTYPE_TRUE)) || (get_ECCR_CCU2CST181DFAF2hUpdate_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GbEDEC_GunBAllowedChrg_flg() ==
      ((boolean_T)ASWTYPE_FALSE)) || (get_GbEBIM_PackBNotAllowedDisCharge_flg() ==
      ((boolean_T)ASWTYPE_TRUE)) || (get_GcEBCR_BMSBRealSOC_pct() <=
      CcEBCR_BMSBSOC15_pct)));
  }

  ECHM_DW.Delay_DSTATE = get_GbECHM_GunBStopChrg_flg();
}

/* Model initialize function */
void ECHM_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
