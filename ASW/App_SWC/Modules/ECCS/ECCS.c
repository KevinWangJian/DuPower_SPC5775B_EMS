/*
 * File: ECCS.c
 *
 * Code generated for Simulink model 'ECCS'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Sat May 09 15:30:08 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "ECCS.h"
#include "ECCS_private.h"

/* Block states (auto storage) */
DW_ECCS_T ECCS_DW;

/* External inputs (root inport signals with auto storage) */
ExtU_ECCS_T ECCS_U;

/* External outputs (root outports fed by signals with auto storage) */
ExtY_ECCS_T ECCS_Y;

/* Real-time model */
RT_MODEL_ECCS_T ECCS_M_;
RT_MODEL_ECCS_T *const ECCS_M = &ECCS_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_1801FAF1h_20ms_at_outport_1' */
void ECCS_1801FAF1h_20ms(void)
{
  boolean_T rtb_RelationalOperator2;
  boolean_T rtb_RelationalOperator7;
  boolean_T rtb_Switch_p;
  boolean_T rtb_Switch2;
  if (CbECCS_CCU1EMSSysStatAliveCounterOvrSwt_flg) {
    set_GcECCS_CCU1EMSSysStatAliveCounter_numb
      (CcECCS_CCU1EMSSysStatAliveCounterOvr_numb);
  } else {
    set_GcECCS_CCU1EMSSysStatAliveCounter_numb(ECCS_ConstB.DataTypeConversion_j);
  }

  if (CbECCS_CCU2EMSSysStatAliveCounterOvrSwt_flg) {
    set_GcECCS_CCU2EMSSysStatAliveCounter_numb
      (CcECCS_CCU2EMSSysStatAliveCounterOvr_numb);
  } else {
    set_GcECCS_CCU2EMSSysStatAliveCounter_numb(ECCS_ConstB.DataTypeConversion_j);
  }

  if (CbECCS_CCU1EMSCCUDirectCntCommandOvrSwt_flg) {
    set_GbECCS_CCU1EMSCCUDirectCntCommand_flg
      (CbECCS_CCU1EMSCCUDirectCntCommandOvr_flg);
  } else {
    set_GbECCS_CCU1EMSCCUDirectCntCommand_flg(ECCS_ConstB.DataTypeConversion1_m);
  }

  if (CbECCS_CCU2EMSCCUDirectCntCommandOvrSwt_flg) {
    set_GbECCS_CCU2EMSCCUDirectCntCommand_flg
      (CbECCS_CCU2EMSCCUDirectCntCommandOvr_flg);
  } else {
    set_GbECCS_CCU2EMSCCUDirectCntCommand_flg(ECCS_ConstB.DataTypeConversion1_m);
  }

  if (CbECCS_CCU1EMSCCUCrossCntCommandOvrSwt_flg) {
    set_GbECCS_CCU1EMSCCUCrossCntCommand_flg
      (CbECCS_CCU1EMSCCUCrossCntCommandOvr_flg);
  } else {
    set_GbECCS_CCU1EMSCCUCrossCntCommand_flg(ECCS_ConstB.DataTypeConversion10_e);
  }

  if (CbECCS_CCU2EMSCCUCrossCntCommandOvrSwt_flg) {
    set_GbECCS_CCU2EMSCCUCrossCntCommand_flg
      (CbECCS_CCU2EMSCCUCrossCntCommandOvr_flg);
  } else {
    set_GbECCS_CCU2EMSCCUCrossCntCommand_flg(ECCS_ConstB.DataTypeConversion10_e);
  }

  if (CbECCS_CCU1EMSChargeAllowOvrSwt_flg) {
    set_GeECCS_CCU1EMSChargeAllow_enum(CeECCS_CCU1EMSChargeAllowOvr_enum);
  } else {
    set_GeECCS_CCU1EMSChargeAllow_enum(0U);
  }

  if (CbECCS_CCU2EMSChargeAllowOvrSwt_flg) {
    set_GeECCS_CCU2EMSChargeAllow_enum(CeECCS_CCU2EMSChargeAllowOvr_enum);
  } else {
    set_GeECCS_CCU2EMSChargeAllow_enum(0U);
  }

  if (CbECCS_CCU1CCUUnlockCmdOvrSwt_flg) {
    set_GeECCS_CCU1CCUUnlockCmd_enum(CeECCS_CCU1CCUUnlockCmdOvr_enum);
  } else {
    set_GeECCS_CCU1CCUUnlockCmd_enum(ECCS_ConstB.DataTypeConversion5_h);
  }

  if (CbECCS_CCU2CCUUnlockCmdOvrSwt_flg) {
    set_GeECCS_CCU2CCUUnlockCmd_enum(CeECCS_CCU2CCUUnlockCmdOvr_enum);
  } else {
    set_GeECCS_CCU2CCUUnlockCmd_enum(ECCS_ConstB.DataTypeConversion5_h);
  }

  if (CbECCS_CCU1CCUIsoDetAllowOvrSwt_flg) {
    set_GbECCS_CCU1CCUIsoDetAllow_flg(CbECCS_CCU1CCUIsoDetAllowOvr_flg);
  } else {
    set_GbECCS_CCU1CCUIsoDetAllow_flg((uint8_T)(get_GbEISO_CCU1StartISOEn_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  }

  if (CbECCS_CCU2CCUIsoDetAllowOvrSwt_flg) {
    set_GbECCS_CCU2CCUIsoDetAllow_flg(CbECCS_CCU2CCUIsoDetAllowOvr_flg);
  } else {
    set_GbECCS_CCU2CCUIsoDetAllow_flg((uint8_T)(get_GbEISO_CCU2StartISOEn_flg() ==
      ((boolean_T)ASWTYPE_TRUE)));
  }

  if (CbECCS_CCU1CCUISONegMosCmdOvrSwt_flg) {
    set_GbECCS_CCU1CCUISONegMosCmd_flg(CbECCS_CCU1CCUISONegMosCmdOvr_flg);
  } else {
    set_GbECCS_CCU1CCUISONegMosCmd_flg(ECCS_ConstB.DataTypeConversion6_oa);
  }

  if (CbECCS_CCU2CCUISONegMosCmdOvrSwt_flg) {
    set_GbECCS_CCU2CCUISONegMosCmd_flg(CbECCS_CCU2CCUISONegMosCmdOvr_flg);
  } else {
    set_GbECCS_CCU2CCUISONegMosCmd_flg(ECCS_ConstB.DataTypeConversion6_oa);
  }

  if (CbECCS_CCU1CCUISOPosMosCmdOvrSwt_flg) {
    set_GbECCS_CCU1CCUISOPosMosCmd_flg(CbECCS_CCU1CCUISOPosMosCmdOvr_flg);
  } else {
    set_GbECCS_CCU1CCUISOPosMosCmd_flg(ECCS_ConstB.DataTypeConversion11_f);
  }

  if (CbECCS_CCU2CCUISOPosMosCmdOvrSwt_flg) {
    set_GbECCS_CCU2CCUISOPosMosCmd_flg(CbECCS_CCU2CCUISOPosMosCmdOvr_flg);
  } else {
    set_GbECCS_CCU2CCUISOPosMosCmd_flg(ECCS_ConstB.DataTypeConversion11_f);
  }

  if (CbECCS_CCU1ChargeModeOvrSwt_flg) {
    set_GeECCS_CCU1ChargeMode_enum(CeECCS_CCU1ChargeModeOvr_enum);
  } else {
    set_GeECCS_CCU1ChargeMode_enum(ECCS_ConstB.DataTypeConversion12_a);
  }

  if (CbECCS_CCU2ChargeModeOvrSwt_flg) {
    set_GeECCS_CCU2ChargeMode_enum(CeECCS_CCU2ChargeModeOvr_enum);
  } else {
    set_GeECCS_CCU2ChargeMode_enum(ECCS_ConstB.DataTypeConversion12_a);
  }

  if (CbECCS_CCU1AFCSysModeOvrSwt_flg) {
    set_GeECCS_CCU1AFCSysMode_enum(CeECCS_CCU1AFCSysModeOvr_enum);
  } else {
    set_GeECCS_CCU1AFCSysMode_enum(ECCS_ConstB.DataTypeConversion13_m);
  }

  if (CbECCS_CCU2AFCSysModeOvrSwt_flg) {
    set_GeECCS_CCU2AFCSysMode_enum(CeECCS_CCU2AFCSysModeOvr_enum);
  } else {
    set_GeECCS_CCU2AFCSysMode_enum(ECCS_ConstB.DataTypeConversion13_m);
  }

  if (CbECCS_CCU1EMSPowerOffCmdOvrSwt_flg) {
    set_GbECCS_CCU1EMSPowerOffCmd_flg(CbECCS_CCU1EMSPowerOffCmdOvr_flg);
  } else {
    set_GbECCS_CCU1EMSPowerOffCmd_flg(ECCS_ConstB.DataTypeConversion7_oq);
  }

  if (CbECCS_CCU2EMSPowerOffCmdOvrSwt_flg) {
    set_GbECCS_CCU2EMSPowerOffCmd_flg(CbECCS_CCU2EMSPowerOffCmdOvr_flg);
  } else {
    set_GbECCS_CCU2EMSPowerOffCmd_flg(ECCS_ConstB.DataTypeConversion7_oq);
  }

  if (CbECCS_CCU1EMSFltlevelOvrSwt_flg) {
    set_GeECCS_CCU1EMSFltlevel_enum(CeECCS_CCU1EMSFltlevelOvr_enum);
  } else {
    set_GeECCS_CCU1EMSFltlevel_enum(ECCS_ConstB.DataTypeConversion14_n);
  }

  if (CbECCS_CCU2EMSFltlevelOvrSwt_flg) {
    set_GeECCS_CCU2EMSFltlevel_enum(CeECCS_CCU2EMSFltlevelOvr_enum);
  } else {
    set_GeECCS_CCU2EMSFltlevel_enum(ECCS_ConstB.DataTypeConversion14_n);
  }

  rtb_RelationalOperator2 = (get_GbECHM_GunAStopChrg_flg() == ((boolean_T)
    ASWTYPE_TRUE));
  if ((get_GbECHM_GunAStartChrg_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
      (ECCS_DW.StateName_ov == ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch_p = ((boolean_T)ASWTYPE_TRUE);
  } else if ((rtb_RelationalOperator2 == ((boolean_T)ASWTYPE_TRUE)) &&
             (ECCS_DW.StateName_h == ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch_p = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch_p = ECCS_DW.StateName_c;
  }

  if (CbECCS_CCU1AuxPwrCtrlOvrSwt_flg) {
    set_GeECCS_CCU1AuxPwrCtrl_enum(CeECCS_CCU1AuxPwrCtrlOvr_enum);
  } else {
    set_GeECCS_CCU1AuxPwrCtrl_enum((uint8_T)rtb_Switch_p);
  }

  rtb_RelationalOperator7 = (get_GbECHM_GunBStopChrg_flg() == ((boolean_T)
    ASWTYPE_TRUE));
  if ((get_GbECHM_GunBStartChrg_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
      (ECCS_DW.StateName_m == ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch2 = ((boolean_T)ASWTYPE_TRUE);
  } else if ((rtb_RelationalOperator7 == ((boolean_T)ASWTYPE_TRUE)) &&
             (ECCS_DW.StateName_i == ((boolean_T)ASWTYPE_FALSE))) {
    rtb_Switch2 = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_Switch2 = ECCS_DW.StateName_j;
  }

  if (CbECCS_CCU2AuxPwrCtrlOvrSwt_flg) {
    set_GeECCS_CCU2AuxPwrCtrl_enum(CeECCS_CCU2AuxPwrCtrlOvr_enum);
  } else {
    set_GeECCS_CCU2AuxPwrCtrl_enum((uint8_T)rtb_Switch2);
  }

  if (CbECCS_CCU1AFCProjectTypeOvrSwt_flg) {
    set_GeECCS_CCU1AFCProjectType_enum(CeECCS_CCU1AFCProjectTypeOvr_enum);
  } else {
    set_GeECCS_CCU1AFCProjectType_enum(ECCS_ConstB.DataTypeConversion15_o);
  }

  if (CbECCS_CCU2AFCProjectTypeOvrSwt_flg) {
    set_GeECCS_CCU2AFCProjectType_enum(CeECCS_CCU2AFCProjectTypeOvr_enum);
  } else {
    set_GeECCS_CCU2AFCProjectType_enum(ECCS_ConstB.DataTypeConversion15_o);
  }

  if (CbECCS_CCU1CellTmpTargetOvrSwt_flg) {
    set_GcECCS_CCU1CellTmpTarget_C(CcECCS_CCU1CellTmpTargetOvr_C);
  } else {
    set_GcECCS_CCU1CellTmpTarget_C(ECCS_ConstB.DataTypeConversion8_a);
  }

  if (CbECCS_CCU2CellTmpTargetOvrSwt_flg) {
    set_GcECCS_CCU2CellTmpTarget_C(CcECCS_CCU2CellTmpTargetOvr_C);
  } else {
    set_GcECCS_CCU2CellTmpTarget_C(ECCS_ConstB.DataTypeConversion8_a);
  }

  if (CbECCS_CCU1EMSSysStatCheckSumOvrSwt_flg) {
    set_GcECCS_CCU1EMSSysStatCheckSum_numb(CcECCS_CCU1EMSSysStatCheckSumOvr_numb);
  } else {
    set_GcECCS_CCU1EMSSysStatCheckSum_numb(ECCS_ConstB.DataTypeConversion9_p);
  }

  if (CbECCS_CCU2EMSSysStatCheckSumOvrSwt_flg) {
    set_GcECCS_CCU2EMSSysStatCheckSum_numb(CcECCS_CCU2EMSSysStatCheckSumOvr_numb);
  } else {
    set_GcECCS_CCU2EMSSysStatCheckSum_numb(ECCS_ConstB.DataTypeConversion9_p);
  }

  ECCS_Y.GbECCS_CCU1BMSIsoDetAllow_flg = 0.0F;
  ECCS_Y.GbECCS_CCU2BMSIsoDetAllow_flg = 0.0F;
  ECCS_Y.GbECCS_CCU1BMSISOPosMosCmd_flg = 0.0F;
  ECCS_Y.GbECCS_CCU2BMSISOPosMosCmd_flg = 0.0F;
  ECCS_Y.GbECCS_CCU1BMSISONegMosCmd_flg = 0.0F;
  ECCS_Y.GbECCS_CCU2BMSISONegMosCmd_flg = 0.0F;
  ECCS_DW.StateName_ov = get_GbECHM_GunAStartChrg_flg();
  ECCS_DW.StateName_h = rtb_RelationalOperator2;
  ECCS_DW.StateName_c = rtb_Switch_p;
  ECCS_DW.StateName_m = get_GbECHM_GunBStartChrg_flg();
  ECCS_DW.StateName_i = rtb_RelationalOperator7;
  ECCS_DW.StateName_j = rtb_Switch2;
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_1807FAF1h_100ms_at_outport_1' */
void ECCS_1807FAF1h_100ms(void)
{
  uint8_T rtb_DataTypeConversion_c;
  if (CbECCS_CCU1ConntQF1AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntQF1AUXStatus_flg(CbECCS_CCU1ConntQF1AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntQF1AUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseAcAuxIn_flg());
  }

  if (CbECCS_CCU2ConntQF1AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntQF1AUXStatus_flg(CbECCS_CCU2ConntQF1AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntQF1AUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseAcAuxIn_flg());
  }

  if (CbECCS_CCU1ConntQF2AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntQF2AUXStatus_flg(CbECCS_CCU1ConntQF2AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntQF2AUXStatus_flg((uint8_T)get_GbEBSW_QF2AuxIn_flg());
  }

  if (CbECCS_CCU2ConntQF2AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntQF2AUXStatus_flg(CbECCS_CCU2ConntQF2AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntQF2AUXStatus_flg((uint8_T)get_GbEBSW_QF2AuxIn_flg());
  }

  if (CbECCS_CCU1ConntQF3AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntQF3AUXStatus_flg(CbECCS_CCU1ConntQF3AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntQF3AUXStatus_flg((uint8_T)
      get_GbEBSW_AdvCoolFanCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ConntQF3AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntQF3AUXStatus_flg(CbECCS_CCU2ConntQF3AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntQF3AUXStatus_flg((uint8_T)
      get_GbEBSW_AdvCoolFanCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ConntFVC1CB1StatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntFVC1CB1Status_flg(CbECCS_CCU1ConntFVC1CB1StatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntFVC1CB1Status_flg((uint8_T)
      get_GbEBSW_ThreePhraseCB1AuxIn_flg());
  }

  if (CbECCS_CCU2ConntFVC1CB1StatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntFVC1CB1Status_flg(CbECCS_CCU2ConntFVC1CB1StatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntFVC1CB1Status_flg((uint8_T)
      get_GbEBSW_ThreePhraseCB1AuxIn_flg());
  }

  if (CbECCS_CCU1ConntSmokeAlarmAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntSmokeAlarmAUXStatus_flg
      (CbECCS_CCU1ConntSmokeAlarmAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntSmokeAlarmAUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseFVC1AuxIn_flg());
  }

  if (CbECCS_CCU2ConntSmokeAlarmAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntSmokeAlarmAUXStatus_flg
      (CbECCS_CCU2ConntSmokeAlarmAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntSmokeAlarmAUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseFVC1AuxIn_flg());
  }

  if (CbECCS_CCU1ConntCB5AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntCB5AUXStatus_flg(CbECCS_CCU1ConntCB5AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntCB5AUXStatus_flg((uint8_T)get_GbEBSW_BCChrgPCtrAuxIn_flg
      ());
  }

  if (CbECCS_CCU2ConntCB5AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntCB5AUXStatus_flg(CbECCS_CCU2ConntCB5AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntCB5AUXStatus_flg((uint8_T)get_GbEBSW_BCChrgPCtrAuxIn_flg
      ());
  }

  if (CbECCS_CCU1ConntCB6AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntCB6AUXStatus_flg(CbECCS_CCU1ConntCB6AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntCB6AUXStatus_flg((uint8_T)get_GbEBSW_CB6AuxIn_flg());
  }

  if (CbECCS_CCU2ConntCB6AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntCB6AUXStatus_flg(CbECCS_CCU2ConntCB6AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntCB6AUXStatus_flg((uint8_T)get_GbEBSW_CB6AuxIn_flg());
  }

  if (get_GbEBSW_Door1CONAuxIn_flg()) {
    rtb_DataTypeConversion_c = ((boolean_T)ASWTYPE_FALSE);
  } else {
    rtb_DataTypeConversion_c = ((boolean_T)ASWTYPE_TRUE);
  }

  if (CbECCS_CCU1ConntDoorConntAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntDoorConntAUXStatus_flg
      (CbECCS_CCU1ConntDoorConntAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntDoorConntAUXStatus_flg(rtb_DataTypeConversion_c);
  }

  if (CbECCS_CCU2ConntDoorConntAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntDoorConntAUXStatus_flg
      (CbECCS_CCU2ConntDoorConntAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntDoorConntAUXStatus_flg(rtb_DataTypeConversion_c);
  }

  if (CbECCS_CCU1ConntEMGSTOPAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntEMGSTOPAUXStatus_flg
      (CbECCS_CCU1ConntEMGSTOPAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntEMGSTOPAUXStatus_flg((uint8_T)
      get_GbEBSW_EMGStopAuxIn_flg());
  }

  if (CbECCS_CCU2ConntEMGSTOPAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntEMGSTOPAUXStatus_flg
      (CbECCS_CCU2ConntEMGSTOPAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntEMGSTOPAUXStatus_flg((uint8_T)
      get_GbEBSW_EMGStopAuxIn_flg());
  }

  if (CbECCS_CCU1ConntFVC2CB2StatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntFVC2CB2Status_flg(CbECCS_CCU1ConntFVC2CB2StatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntFVC2CB2Status_flg((uint8_T)get_GbEBSW_ADFVC2CB2AuxIn_flg
      ());
  }

  if (CbECCS_CCU2ConntFVC2CB2StatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntFVC2CB2Status_flg(CbECCS_CCU2ConntFVC2CB2StatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntFVC2CB2Status_flg((uint8_T)get_GbEBSW_ADFVC2CB2AuxIn_flg
      ());
  }

  if (CbECCS_CCU1ConntK11K12AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK11K12AUXStatus_flg
      (CbECCS_CCU1ConntK11K12AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntK11K12AUXStatus_flg((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ConntK11K12AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK11K12AUXStatus_flg
      (CbECCS_CCU2ConntK11K12AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntK11K12AUXStatus_flg((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ConntK5K6AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK5K6AUXStatus_flg(CbECCS_CCU1ConntK5K6AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntK5K6AUXStatus_flg((uint8_T)
      get_GbEBSW_CChrgAPCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ConntK5K6AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK5K6AUXStatus_flg(CbECCS_CCU2ConntK5K6AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntK5K6AUXStatus_flg((uint8_T)
      get_GbEBSW_CChrgAPCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ConntK7K8AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK7K8AUXStatus_flg(CbECCS_CCU1ConntK7K8AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntK7K8AUXStatus_flg((uint8_T)
      get_GbEBSW_CChrgBPCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ConntK7K8AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK7K8AUXStatus_flg(CbECCS_CCU2ConntK7K8AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntK7K8AUXStatus_flg((uint8_T)
      get_GbEBSW_CChrgBPCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ConntK9K10AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK9K10AUXStatus_flg(CbECCS_CCU1ConntK9K10AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntK9K10AUXStatus_flg((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ConntK9K10AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK9K10AUXStatus_flg(CbECCS_CCU2ConntK9K10AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntK9K10AUXStatus_flg((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ConntKM1AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntKM1AUXStatus_flg(CbECCS_CCU1ConntKM1AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntKM1AUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseRechargeAuxIn_flg());
  }

  if (CbECCS_CCU2ConntKM1AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntKM1AUXStatus_flg(CbECCS_CCU2ConntKM1AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntKM1AUXStatus_flg((uint8_T)
      get_GbEBSW_ThreePhraseRechargeAuxIn_flg());
  }

  if (CbECCS_CCU1ConntKM2AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntKM2AUXStatus_flg(CbECCS_CCU1ConntKM2AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntKM2AUXStatus_flg((uint8_T)get_GbEBSW_Door2CONAuxIn_flg());
  }

  if (CbECCS_CCU2ConntKM2AUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntKM2AUXStatus_flg(CbECCS_CCU2ConntKM2AUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntKM2AUXStatus_flg((uint8_T)get_GbEBSW_Door2CONAuxIn_flg());
  }

  if (CbECCS_CCU1ConntCrashStatusOvrSwt_flg) {
    set_GeECCS_CCU1ConntCrashStatus_enum(CeECCS_CCU1ConntCrashStatusOvr_enum);
  } else {
    set_GeECCS_CCU1ConntCrashStatus_enum(ECCS_ConstB.DataTypeConversion1_p);
  }

  if (CbECCS_CCU2ConntCrashStatusOvrSwt_flg) {
    set_GeECCS_CCU2ConntCrashStatus_enum(CeECCS_CCU2ConntCrashStatusOvr_enum);
  } else {
    set_GeECCS_CCU2ConntCrashStatus_enum(ECCS_ConstB.DataTypeConversion1_p);
  }

  if (CbECCS_CCU1ConntRolloverStatusOvrSwt_flg) {
    set_GeECCS_CCU1ConntRolloverStatus_enum
      (CeECCS_CCU1ConntRolloverStatusOvr_enum);
  } else {
    set_GeECCS_CCU1ConntRolloverStatus_enum(ECCS_ConstB.DataTypeConversion2_hr);
  }

  if (CbECCS_CCU2ConntRolloverStatusOvrSwt_flg) {
    set_GeECCS_CCU2ConntRolloverStatus_enum
      (CeECCS_CCU2ConntRolloverStatusOvr_enum);
  } else {
    set_GeECCS_CCU2ConntRolloverStatus_enum(ECCS_ConstB.DataTypeConversion2_hr);
  }

  if (CbECCS_CCU1ConntFUSE3StatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntFUSE3Status_flg(CbECCS_CCU1ConntFUSE3StatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntFUSE3Status_flg(ECCS_ConstB.DataTypeConversion3_if);
  }

  if (CbECCS_CCU2ConntFUSE3StatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntFUSE3Status_flg(CbECCS_CCU2ConntFUSE3StatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntFUSE3Status_flg(ECCS_ConstB.DataTypeConversion3_if);
  }

  if (CbECCS_CCU1ConntWaterLevelAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntWaterLevelAUXStatus_flg
      (CbECCS_CCU1ConntWaterLevelAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntWaterLevelAUXStatus_flg((uint8_T)
      get_GbEBSW_WaterTSAuxIn_flg());
  }

  if (CbECCS_CCU2ConntWaterLevelAUXStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntWaterLevelAUXStatus_flg
      (CbECCS_CCU2ConntWaterLevelAUXStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntWaterLevelAUXStatus_flg((uint8_T)
      get_GbEBSW_WaterTSAuxIn_flg());
  }

  if (CbECCS_CCU1ConntK13RealyStatusOvrSwt_flg) {
    set_GeECCS_CCU1ConntK13RealyStatus_enum
      (CeECCS_CCU1ConntK13RealyStatusOvr_enum);
  } else {
    set_GeECCS_CCU1ConntK13RealyStatus_enum(ECCS_ConstB.DataTypeConversion27);
  }

  if (CbECCS_CCU2ConntK13RealyStatusOvrSwt_flg) {
    set_GeECCS_CCU2ConntK13RealyStatus_enum
      (CeECCS_CCU2ConntK13RealyStatusOvr_enum);
  } else {
    set_GeECCS_CCU2ConntK13RealyStatus_enum(ECCS_ConstB.DataTypeConversion27);
  }

  if (CbECCS_CCU1ConntK14RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK14RealyStatus_enum
      (CbECCS_CCU1ConntK14RealyStatusOvr_enum);
  } else {
    set_GbECCS_CCU1ConntK14RealyStatus_enum(ECCS_ConstB.DataTypeConversion4_mn);
  }

  if (CbECCS_CCU2ConntK14RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK14RealyStatus_enum
      (CbECCS_CCU2ConntK14RealyStatusOvr_enum);
  } else {
    set_GbECCS_CCU2ConntK14RealyStatus_enum(ECCS_ConstB.DataTypeConversion4_mn);
  }

  if (CbECCS_CCU1ConntK15RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK15RealyStatus_enum
      (CbECCS_CCU1ConntK15RealyStatusOvr_enum);
  } else {
    set_GbECCS_CCU1ConntK15RealyStatus_enum(ECCS_ConstB.DataTypeConversion5_cv);
  }

  if (CbECCS_CCU2ConntK15RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK15RealyStatus_enum
      (CbECCS_CCU2ConntK15RealyStatusOvr_enum);
  } else {
    set_GbECCS_CCU2ConntK15RealyStatus_enum(ECCS_ConstB.DataTypeConversion5_cv);
  }

  if (CbECCS_CCU1ConntK16RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU1ConntK16RealyStatus_flg(CbECCS_CCU1ConntK16RealyStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ConntK16RealyStatus_flg(ECCS_ConstB.DataTypeConversion6_o);
  }

  if (CbECCS_CCU2ConntK16RealyStatusOvrSwt_flg) {
    set_GbECCS_CCU2ConntK16RealyStatus_flg(CbECCS_CCU2ConntK16RealyStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ConntK16RealyStatus_flg(ECCS_ConstB.DataTypeConversion6_o);
  }

  if (CbECCS_CCU1LED1StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED1Status_enum(CbECCS_CCU1LED1StatusOvr_enum);
  } else {
    set_GbECCS_CCU1LED1Status_enum(ECCS_ConstB.DataTypeConversion7_j);
  }

  if (CbECCS_CCU2LED1StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED1Status_enum(CbECCS_CCU2LED1StatusOvr_enum);
  } else {
    set_GbECCS_CCU2LED1Status_enum(ECCS_ConstB.DataTypeConversion7_j);
  }

  if (CbECCS_CCU1LED2StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED2Status_enum(CbECCS_CCU1LED2StatusOvr_enum);
  } else {
    set_GbECCS_CCU1LED2Status_enum(ECCS_ConstB.DataTypeConversion8_i);
  }

  if (CbECCS_CCU2LED2StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED2Status_enum(CbECCS_CCU2LED2StatusOvr_enum);
  } else {
    set_GbECCS_CCU2LED2Status_enum(ECCS_ConstB.DataTypeConversion8_i);
  }

  if (CbECCS_CCU1LED3StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED3Status_enum(CbECCS_CCU1LED3StatusOvr_enum);
  } else {
    set_GbECCS_CCU1LED3Status_enum(ECCS_ConstB.DataTypeConversion9_h);
  }

  if (CbECCS_CCU2LED3StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED3Status_enum(CbECCS_CCU2LED3StatusOvr_enum);
  } else {
    set_GbECCS_CCU2LED3Status_enum(ECCS_ConstB.DataTypeConversion9_h);
  }

  if (CbECCS_CCU1LED4StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED4Status_enum(CbECCS_CCU1LED4StatusOvr_enum);
  } else {
    set_GbECCS_CCU1LED4Status_enum(ECCS_ConstB.DataTypeConversion10_k);
  }

  if (CbECCS_CCU2LED4StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED4Status_enum(CbECCS_CCU2LED4StatusOvr_enum);
  } else {
    set_GbECCS_CCU2LED4Status_enum(ECCS_ConstB.DataTypeConversion10_k);
  }

  if (CbECCS_CCU1LED5StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED5Status_flg(CbECCS_CCU1LED5StatusOvr_flg);
  } else {
    set_GbECCS_CCU1LED5Status_flg(ECCS_ConstB.DataTypeConversion11_n);
  }

  if (CbECCS_CCU2LED5StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED5Status_flg(CbECCS_CCU2LED5StatusOvr_flg);
  } else {
    set_GbECCS_CCU2LED5Status_flg(ECCS_ConstB.DataTypeConversion11_n);
  }

  if (CbECCS_CCU1LED6StatusOvrSwt_flg) {
    set_GbECCS_CCU1LED6Status_flg(CbECCS_CCU1LED6StatusOvr_flg);
  } else {
    set_GbECCS_CCU1LED6Status_flg(ECCS_ConstB.DataTypeConversion12_c);
  }

  if (CbECCS_CCU2LED6StatusOvrSwt_flg) {
    set_GbECCS_CCU2LED6Status_flg(CbECCS_CCU2LED6StatusOvr_flg);
  } else {
    set_GbECCS_CCU2LED6Status_flg(ECCS_ConstB.DataTypeConversion12_c);
  }

  if (CbECCS_CCU1ADmicrophoneStatusOvrSwt_flg) {
    set_GbECCS_CCU1ADmicrophoneStatus_flg(CbECCS_CCU1ADmicrophoneStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ADmicrophoneStatus_flg(ECCS_ConstB.DataTypeConversion13_k);
  }

  if (CbECCS_CCU2ADmicrophoneStatusOvrSwt_flg) {
    set_GbECCS_CCU2ADmicrophoneStatus_flg(CbECCS_CCU2ADmicrophoneStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ADmicrophoneStatus_flg(ECCS_ConstB.DataTypeConversion13_k);
  }

  if (CbECCS_CCU1ADFANStatusOvrSwt_flg) {
    set_GbECCS_CCU1ADFANStatus_flg(CbECCS_CCU1ADFANStatusOvr_flg);
  } else {
    set_GbECCS_CCU1ADFANStatus_flg(ECCS_ConstB.DataTypeConversion14_b);
  }

  if (CbECCS_CCU2ADFANStatusOvrSwt_flg) {
    set_GbECCS_CCU2ADFANStatus_flg(CbECCS_CCU2ADFANStatusOvr_flg);
  } else {
    set_GbECCS_CCU2ADFANStatus_flg(ECCS_ConstB.DataTypeConversion14_b);
  }

  if (CbECCS_CCU1FAN1StatusOvrSwt_flg) {
    set_GbECCS_CCU1FAN1Status_flg(CbECCS_CCU1FAN1StatusOvr_flg);
  } else {
    set_GbECCS_CCU1FAN1Status_flg(ECCS_ConstB.DataTypeConversion15_j);
  }

  if (CbECCS_CCU2FAN1StatusOvrSwt_flg) {
    set_GbECCS_CCU2FAN1Status_flg(CbECCS_CCU2FAN1StatusOvr_flg);
  } else {
    set_GbECCS_CCU2FAN1Status_flg(ECCS_ConstB.DataTypeConversion15_j);
  }

  if (CbECCS_CCU1FAN2StatusOvrSwt_flg) {
    set_GbECCS_CCU1FAN2Status_flg(CbECCS_CCU1FAN2StatusOvr_flg);
  } else {
    set_GbECCS_CCU1FAN2Status_flg(ECCS_ConstB.DataTypeConversion16_b);
  }

  if (CbECCS_CCU2FAN2StatusOvrSwt_flg) {
    set_GbECCS_CCU2FAN2Status_flg(CbECCS_CCU2FAN2StatusOvr_flg);
  } else {
    set_GbECCS_CCU2FAN2Status_flg(ECCS_ConstB.DataTypeConversion16_b);
  }

  if (CbECCS_CCU1FAN3StatusOvrSwt_flg) {
    set_GbECCS_CCU1FAN3Status_flg(CbECCS_CCU1FAN3StatusOvr_flg);
  } else {
    set_GbECCS_CCU1FAN3Status_flg(ECCS_ConstB.DataTypeConversion17);
  }

  if (CbECCS_CCU2FAN3StatusOvrSwt_flg) {
    set_GbECCS_CCU2FAN3Status_flg(CbECCS_CCU2FAN3StatusOvr_flg);
  } else {
    set_GbECCS_CCU2FAN3Status_flg(ECCS_ConstB.DataTypeConversion17);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_ACWh_1804FAF1h_1000ms_at_outport_1' */
void ECCS_EMS_ACWh_1804FAF1h_1000ms(void)
{
  uint32_T tmp;
  uint16_T rtb_DataTypeConversion2_p_0;
  real32_T tmp_0;
  if (CbECCS_CCU1ACWhindexOvrSwt_flg) {
    set_GeECCS_CCU1ACWhindex_enum(CeECCS_CCU1ACWhindexOvr_enum);
  } else {
    set_GeECCS_CCU1ACWhindex_enum(ECCS_ConstB.DataTypeConversion1_d);
  }

  if (CbECCS_CCU2ACWhindexOvrSwt_flg) {
    set_GeECCS_CCU2ACWhindex_enum(CeECCS_CCU2ACWhindexOvr_enum);
  } else {
    set_GeECCS_CCU2ACWhindex_enum(ECCS_ConstB.DataTypeConversion1_d);
  }

  tmp_0 = get_GcEBSW_ThreePhaseEnergy_kwH() / 0.1F;
  if (tmp_0 < 65536.0F) {
    if (tmp_0 >= 0.0F) {
      rtb_DataTypeConversion2_p_0 = (uint16_T)tmp_0;
    } else {
      rtb_DataTypeConversion2_p_0 = 0U;
    }
  } else {
    rtb_DataTypeConversion2_p_0 = MAX_uint16_T;
  }

  if (CbECCS_CCU1ACWhCurrtEnergeOvrSwt_flg) {
    set_GcECCS_CCU1ACWhCurrtEnerge_Kwh(CcECCS_CCU1ACWhCurrtEnergeOvr_Kwh);
  } else {
    set_GcECCS_CCU1ACWhCurrtEnerge_Kwh(rtb_DataTypeConversion2_p_0);
  }

  if (CbECCS_CCU2ACWhCurrtEnergeOvrSwt_flg) {
    set_GcECCS_CCU2ACWhCurrtEnerge_Kwh(CcECCS_CCU2ACWhCurrtEnergeOvr_Kwh);
  } else {
    set_GcECCS_CCU2ACWhCurrtEnerge_Kwh(rtb_DataTypeConversion2_p_0);
  }

  if (CbECCS_CCU1ACWhOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU1ACWhOutputVolt_V(CcECCS_CCU1ACWhOutputVoltOvr_V);
  } else {
    tmp = get_GcEBSW_ThreePhaseACWhOutputVolt_V() * 10U;
    if (tmp > 65535U) {
      tmp = 65535U;
    }

    set_GcECCS_CCU1ACWhOutputVolt_V((uint16_T)tmp);
  }

  if (CbECCS_CCU2ACWhOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU2ACWhOutputVolt_V(CcECCS_CCU2ACWhOutputVoltOvr_V);
  } else {
    tmp = get_GcEBSW_ThreePhaseACWhOutputVolt_V() * 10U;
    if (tmp > 65535U) {
      tmp = 65535U;
    }

    set_GcECCS_CCU2ACWhOutputVolt_V((uint16_T)tmp);
  }

  if (CbECCS_CCU1ACWhCurrentOvrSwt_flg) {
    set_GcECCS_CCU1ACWhCurrent_A(CcECCS_CCU1ACWhCurrentOvr_A);
  } else {
    tmp = get_GcEBSW_ThreePhaseACWhCurrent_A() * 5U + 2000U;
    if (tmp > 32767U) {
      set_GcECCS_CCU1ACWhCurrent_A(MAX_uint16_T);
    } else {
      set_GcECCS_CCU1ACWhCurrent_A((uint16_T)((int32_T)tmp << 1));
    }
  }

  if (CbECCS_CCU2ACWhCurrentOvrSwt_flg) {
    set_GcECCS_CCU2ACWhCurrent_A(CcECCS_CCU2ACWhCurrentOvr_A);
  } else {
    tmp = get_GcEBSW_ThreePhaseACWhCurrent_A() * 5U + 2000U;
    if (tmp > 32767U) {
      set_GcECCS_CCU2ACWhCurrent_A(MAX_uint16_T);
    } else {
      set_GcECCS_CCU2ACWhCurrent_A((uint16_T)((int32_T)tmp << 1));
    }
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_CML_1805FAF1h_1000ms_at_outport_1' */
void ECCS_EMS_CML_1805FAF1h_1000ms(void)
{
  if (CbECCS_CCU1CMLSPN2827IMinOutOvrSwt_flg) {
    set_GcECCS_CCU1CMLSPN2827IMinOut_A(CcECCS_CCU1CMLSPN2827IMinOutOvr_A);
  } else {
    set_GcECCS_CCU1CMLSPN2827IMinOut_A(ECCS_ConstB.DataTypeConversion22);
  }

  if (CbECCS_CCU2CMLSPN2827IMinOutOvrSwt_flg) {
    set_GcECCS_CCU2CMLSPN2827IMinOut_A(CcECCS_CCU2CMLSPN2827IMinOutOvr_A);
  } else {
    set_GcECCS_CCU2CMLSPN2827IMinOut_A(ECCS_ConstB.DataTypeConversion22);
  }

  if (CbECCS_CCU1CMLSPN2826IMaxOutOvrSwt_flg) {
    set_GcECCS_CCU1CMLSPN2826IMaxOut_A(CcECCS_CCU1CMLSPN2826IMaxOutOvr_A);
  } else {
    set_GcECCS_CCU1CMLSPN2826IMaxOut_A(ECCS_ConstB.DataTypeConversion5);
  }

  if (CbECCS_CCU2CMLSPN2826IMaxOutOvrSwt_flg) {
    set_GcECCS_CCU2CMLSPN2826IMaxOut_A(CcECCS_CCU2CMLSPN2826IMaxOutOvr_A);
  } else {
    set_GcECCS_CCU2CMLSPN2826IMaxOut_A(ECCS_ConstB.DataTypeConversion5);
  }

  if (CbECCS_CCU1CMLSPN2825UMinOutOvrSwt_flg) {
    set_GcECCS_CCU1CMLSPN2825UMinOut_V(CcECCS_CCU1CMLSPN2825UMinOutOvr_V);
  } else {
    set_GcECCS_CCU1CMLSPN2825UMinOut_V(ECCS_ConstB.DataTypeConversion4_m);
  }

  if (CbECCS_CCU2CMLSPN2825UMinOutOvrSwt_flg) {
    set_GcECCS_CCU2CMLSPN2825UMinOut_V(CcECCS_CCU2CMLSPN2825UMinOutOvr_V);
  } else {
    set_GcECCS_CCU2CMLSPN2825UMinOut_V(ECCS_ConstB.DataTypeConversion4_m);
  }

  if (CbECCS_CCU1CMLSPN2824UMaxOutOvrSwt_flg) {
    set_GcECCS_CCU1CMLSPN2824UMaxOut_V(CcECCS_CCU1CMLSPN2824UMaxOutOvr_V);
  } else {
    set_GcECCS_CCU1CMLSPN2824UMaxOut_V(ECCS_ConstB.DataTypeConversion1_j);
  }

  if (CbECCS_CCU2CMLSPN2824UMaxOutOvrSwt_flg) {
    set_GcECCS_CCU2CMLSPN2824UMaxOut_V(CcECCS_CCU2CMLSPN2824UMaxOutOvr_V);
  } else {
    set_GcECCS_CCU2CMLSPN2824UMaxOut_V(ECCS_ConstB.DataTypeConversion1_j);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_ConntSts_1815FAF1h_500ms_at_outport_1' */
void ECCS_EMS_ConntSts_1815FAF1h_500ms(void)
{
  if (CbECCS_CCU1ACDC1CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU1ACDC1CrossrelayNegState_enum
      (CeECCS_CCU1ACDC1CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC1CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_CChrgANCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ACDC1CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU1ACDC1CrossrelayPosState_enum
      (CeECCS_CCU1ACDC1CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC1CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_CChrgAPCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ACDC1CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU2ACDC1CrossrelayNegState_enum
      (CeECCS_CCU2ACDC1CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC1CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_CChrgANCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ACDC1CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU2ACDC1CrossrelayPosState_enum
      (CeECCS_CCU2ACDC1CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC1CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_CChrgAPCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ACDC2CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU1ACDC2CrossrelayNegState_enum
      (CeECCS_CCU1ACDC2CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC2CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_CChrgBNCtrAuxIn_flg());
  }

  if (CbECCS_CCU1ACDC2CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU1ACDC2CrossrelayPosState_enum
      (CeECCS_CCU1ACDC2CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC2CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_CChrgBPCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ACDC2CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU2ACDC2CrossrelayNegState_enum
      (CeECCS_CCU2ACDC2CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC2CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_CChrgBNCtrAuxIn_flg());
  }

  if (CbECCS_CCU2ACDC2CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU2ACDC2CrossrelayPosState_enum
      (CeECCS_CCU2ACDC2CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC2CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_CChrgBPCtrAuxIn_flg());
  }

  if (CbECCS_CCU1CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU1CrossrelayNegState_enum(CeECCS_CCU1CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU1CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_BCChrgNCtrAuxIn_flg());
  }

  if (CbECCS_CCU1CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU1CrossrelayPosState_enum(CeECCS_CCU1CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU1CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_BCChrgPCtrAuxIn_flg());
  }

  if (CbECCS_CCU2CrossrelayNegStateOvrSwt_flg) {
    set_GeECCS_CCU2CrossrelayNegState_enum(CeECCS_CCU2CrossrelayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU2CrossrelayNegState_enum((uint8_T)
      get_GbEBSW_BCChrgNCtrAuxIn_flg());
  }

  if (CbECCS_CCU2CrossrelayPosStateOvrSwt_flg) {
    set_GeECCS_CCU2CrossrelayPosState_enum(CeECCS_CCU2CrossrelayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU2CrossrelayPosState_enum((uint8_T)
      get_GbEBSW_BCChrgPCtrAuxIn_flg());
  }

  if (CbECCS_CCU1TMSPS1relayNegStateOvrSwt_flg) {
    set_GeECCS_CCU1TMSPS1relayNegState_enum
      (CeECCS_CCU1TMSPS1relayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU1TMSPS1relayNegState_enum((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU1TMSPS1relayPosStateOvrSwt_flg) {
    set_GeECCS_CCU1TMSPS1relayPosState_enum
      (CeECCS_CCU1TMSPS1relayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU1TMSPS1relayPosState_enum((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2TMSPS1relayNegStateOvrSwt_flg) {
    set_GeECCS_CCU2TMSPS1relayNegState_enum
      (CeECCS_CCU2TMSPS1relayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU2TMSPS1relayNegState_enum((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2TMSPS1relayPosStateOvrSwt_flg) {
    set_GeECCS_CCU2TMSPS1relayPosState_enum
      (CeECCS_CCU2TMSPS1relayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU2TMSPS1relayPosState_enum((uint8_T)
      get_GbEBSW_PACKAToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU1TMSPS2relayNegStateOvrSwt_flg) {
    set_GeECCS_CCU1TMSPS2relayNegState_enum
      (CeECCS_CCU1TMSPS2relayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU1TMSPS2relayNegState_enum((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU1TMSPS2relayPosStateOvrSwt_flg) {
    set_GeECCS_CCU1TMSPS2relayPosState_enum
      (CeECCS_CCU1TMSPS2relayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU1TMSPS2relayPosState_enum((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2TMSPS2relayNegStateOvrSwt_flg) {
    set_GeECCS_CCU2TMSPS2relayNegState_enum
      (CeECCS_CCU2TMSPS2relayNegStateOvr_enum);
  } else {
    set_GeECCS_CCU2TMSPS2relayNegState_enum((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }

  if (CbECCS_CCU2TMSPS2relayPosStateOvrSwt_flg) {
    set_GeECCS_CCU2TMSPS2relayPosState_enum
      (CeECCS_CCU2TMSPS2relayPosStateOvr_enum);
  } else {
    set_GeECCS_CCU2TMSPS2relayPosState_enum((uint8_T)
      get_GbEBSW_PACKBToHVCtrAuxIn_flg());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_ConntSts_1821FAF1h_50ms_at_outport_1' */
void ECCS_EMS_ConntSts_1821FAF1h_50ms(void)
{
  if (CbECCS_CCU1CCU1DirectPosFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU1DirectPosFB_enum(CbECCS_CCU1CCU1DirectPosFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU1DirectPosFB_enum(ECCS_ConstB.DataTypeConversion_ac);
  }

  if (CbECCS_CCU2CCU1DirectPosFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU1DirectPosFB_enum(CbECCS_CCU2CCU1DirectPosFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU1DirectPosFB_enum(ECCS_ConstB.DataTypeConversion_ac);
  }

  if (CbECCS_CCU1CCU1DirectNegFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU1DirectNegFB_enum(CbECCS_CCU1CCU1DirectNegFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU1DirectNegFB_enum(ECCS_ConstB.DataTypeConversion1_ki);
  }

  if (CbECCS_CCU2CCU1DirectNegFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU1DirectNegFB_enum(CbECCS_CCU2CCU1DirectNegFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU1DirectNegFB_enum(ECCS_ConstB.DataTypeConversion1_ki);
  }

  if (CbECCS_CCU1CCU1CrossPosFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU1CrossPosFB_enum(CbECCS_CCU1CCU1CrossPosFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU1CrossPosFB_enum(ECCS_ConstB.DataTypeConversion2_i);
  }

  if (CbECCS_CCU2CCU1CrossPosFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU1CrossPosFB_enum(CbECCS_CCU2CCU1CrossPosFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU1CrossPosFB_enum(ECCS_ConstB.DataTypeConversion2_i);
  }

  if (CbECCS_CCU1CCU1CrossNegFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU1CrossNegFB_enum(CbECCS_CCU1CCU1CrossNegFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU1CrossNegFB_enum(ECCS_ConstB.DataTypeConversion3_m);
  }

  if (CbECCS_CCU2CCU1CrossNegFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU1CrossNegFB_enum(CbECCS_CCU2CCU1CrossNegFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU1CrossNegFB_enum(ECCS_ConstB.DataTypeConversion3_m);
  }

  if (CbECCS_CCU1CCU2DirectPosFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU2DirectPosFB_enum(CbECCS_CCU1CCU2DirectPosFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU2DirectPosFB_enum(ECCS_ConstB.DataTypeConversion4_a);
  }

  if (CbECCS_CCU2CCU2DirectPosFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU2DirectPosFB_enum(CbECCS_CCU2CCU2DirectPosFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU2DirectPosFB_enum(ECCS_ConstB.DataTypeConversion4_a);
  }

  if (CbECCS_CCU1CCU2DirectNegFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU2DirectNegFB_enum(CbECCS_CCU1CCU2DirectNegFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU2DirectNegFB_enum(ECCS_ConstB.DataTypeConversion5_ai);
  }

  if (CbECCS_CCU2CCU2DirectNegFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU2DirectNegFB_enum(CbECCS_CCU2CCU2DirectNegFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU2DirectNegFB_enum(ECCS_ConstB.DataTypeConversion5_ai);
  }

  if (CbECCS_CCU1CCU2CrossPosFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU2CrossPosFB_enum(CbECCS_CCU1CCU2CrossPosFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU2CrossPosFB_enum(ECCS_ConstB.DataTypeConversion6_m);
  }

  if (CbECCS_CCU2CCU2CrossPosFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU2CrossPosFB_enum(CbECCS_CCU2CCU2CrossPosFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU2CrossPosFB_enum(ECCS_ConstB.DataTypeConversion6_m);
  }

  if (CbECCS_CCU1CCU2CrossNegFBOvrSwt_flg) {
    set_GbECCS_CCU1CCU2CrossNegFB_enum(CbECCS_CCU1CCU2CrossNegFBOvr_enum);
  } else {
    set_GbECCS_CCU1CCU2CrossNegFB_enum(ECCS_ConstB.DataTypeConversion7_o);
  }

  if (CbECCS_CCU2CCU2CrossNegFBOvrSwt_flg) {
    set_GbECCS_CCU2CCU2CrossNegFB_enum(CbECCS_CCU2CCU2CrossNegFBOvr_enum);
  } else {
    set_GbECCS_CCU2CCU2CrossNegFB_enum(ECCS_ConstB.DataTypeConversion7_o);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_DCDC_1812FAF1h_250ms_at_outport_1' */
void ECCS_EMS_DCDC_1812FAF1h_250ms(void)
{
  int32_T rtb_Add_fz;
  int32_T rtb_Add_o;
  uint16_T rtb_Divide_h;
  uint8_T rtb_DataTypeConversion5_e_0;
  uint32_T tmp;
  uint16_T rtb_DataTypeConversion_n_0;
  if (CbECCS_CCU1EMSToCCUindexOvrSwt_flg) {
    set_GeECCS_CCU1EMSToCCUindex_enum(CeECCS_CCU1EMSToCCUindexOvr_enum);
  } else {
    set_GeECCS_CCU1EMSToCCUindex_enum(ECCS_ConstB.DataTypeConversion7_p);
  }

  if (CbECCS_CCU2EMSToCCUindexOvrSwt_flg) {
    set_GeECCS_CCU2EMSToCCUindex_enum(CeECCS_CCU2EMSToCCUindexOvr_enum);
  } else {
    set_GeECCS_CCU2EMSToCCUindex_enum(ECCS_ConstB.DataTypeConversion8_o);
  }

  rtb_Add_fz = ECCS_DW.StateName_p + 1;
  tmp = get_GcEBSW_DCDCCurrent_A( rtb_Add_fz - 1 ) * 5U + 2000U;
  if (tmp > 32767U) {
    rtb_DataTypeConversion_n_0 = MAX_uint16_T;
  } else {
    rtb_DataTypeConversion_n_0 = (uint16_T)((int32_T)tmp << 1);
  }

  rtb_Add_o = ECCS_DW.StateName_o + 1;
  tmp = get_GcEBSW_DCDCOutputVolt_V( rtb_Add_o - 1 ) * 10U;
  if (tmp > 65535U) {
    tmp = 65535U;
  }

  if (rtb_Add_fz < 256) {
    rtb_DataTypeConversion5_e_0 = (uint8_T)rtb_Add_fz;
  } else {
    rtb_DataTypeConversion5_e_0 = MAX_uint8_T;
  }

  rtb_Divide_h = (uint16_T)(((int32_T)(rtb_DataTypeConversion_n_0 * 52429U >> 19)
    + -400) * ((uint16_T)tmp * 52429U >> 19));
  if (CbECCS_CCU1DCDCCurrentOvrSwt_flg) {
    set_GcECCS_CCU1DCDCCurrent_A(CcECCS_CCU1DCDCCurrentOvr_A);
  } else {
    set_GcECCS_CCU1DCDCCurrent_A(rtb_DataTypeConversion_n_0);
  }

  if (CbECCS_CCU1DCDCCurrtPowerOvrSwt_flg) {
    set_GcECCS_CCU1DCDCCurrtPower_Kw(CcECCS_CCU1DCDCCurrtPowerOvr_Kw);
  } else {
    set_GcECCS_CCU1DCDCCurrtPower_Kw(rtb_Divide_h);
  }

  if (CbECCS_CCU1DCDCOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU1DCDCOutputVolt_V(CcECCS_CCU1DCDCOutputVoltOvr_V);
  } else {
    set_GcECCS_CCU1DCDCOutputVolt_V((uint16_T)tmp);
  }

  if (CbECCS_CCU2DCDCCurrentOvrSwt_flg) {
    set_GcECCS_CCU2DCDCCurrent_A(CcECCS_CCU2DCDCCurrentOvr_A);
  } else {
    set_GcECCS_CCU2DCDCCurrent_A(rtb_DataTypeConversion_n_0);
  }

  if (CbECCS_CCU2DCDCCurrtPowerOvrSwt_flg) {
    set_GcECCS_CCU2DCDCCurrtPower_Kw(CcECCS_CCU2DCDCCurrtPowerOvr_Kw);
  } else {
    set_GcECCS_CCU2DCDCCurrtPower_Kw(rtb_Divide_h);
  }

  if (CbECCS_CCU2DCDCOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU2DCDCOutputVolt_V(CcECCS_CCU2DCDCOutputVoltOvr_V);
  } else {
    set_GcECCS_CCU2DCDCOutputVolt_V((uint16_T)tmp);
  }

  if (CbECCS_CCU1DCDCindexOvrSwt_flg) {
    set_GeECCS_CCU1DCDCindex_enum(CeECCS_CCU1DCDCindexOvr_enum);
  } else {
    set_GeECCS_CCU1DCDCindex_enum(rtb_DataTypeConversion5_e_0);
  }

  if (CbECCS_CCU2DCDCindexOvrSwt_flg) {
    set_GeECCS_CCU2DCDCindex_enum(CeECCS_CCU2DCDCindexOvr_enum);
  } else {
    set_GeECCS_CCU2DCDCindex_enum(rtb_DataTypeConversion5_e_0);
  }

  if (rtb_Add_fz >= 4) {
    ECCS_DW.StateName_p = 0U;
  } else {
    ECCS_DW.StateName_p = (uint16_T)(int32_T)fmod(rtb_Add_fz, 65536.0);
  }

  if (rtb_Add_o >= 4) {
    ECCS_DW.StateName_o = 0U;
  } else {
    ECCS_DW.StateName_o = (uint16_T)(int32_T)fmod(rtb_Add_o, 65536.0);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_DCWh_1803FAF1h_250ms_at_outport_1' */
void ECCS_EMS_DCWh_1803FAF1h_250ms(void)
{
  real32_T rtb_Add_m;
  real32_T tmp;
  uint32_T tmp_0;
  rtb_Add_m = ECCS_DW.StateName + ECCS_ConstB.DataTypeConversion1;
  if (CbECCS_CCU1DCWhindexOvrSwt_flg) {
    set_GeECCS_CCU1DCWhindex_enum(CeECCS_CCU1DCWhindexOvr_enum);
  } else if (rtb_Add_m < 256.0F) {
    if (rtb_Add_m >= 0.0F) {
      set_GeECCS_CCU1DCWhindex_enum((uint8_T)rtb_Add_m);
    } else {
      set_GeECCS_CCU1DCWhindex_enum(0U);
    }
  } else {
    set_GeECCS_CCU1DCWhindex_enum(MAX_uint8_T);
  }

  if (CbECCS_CCU2DCWhindexOvrSwt_flg) {
    set_GeECCS_CCU2DCWhindex_enum(CeECCS_CCU2DCWhindexOvr_enum);
  } else if (rtb_Add_m < 256.0F) {
    if (rtb_Add_m >= 0.0F) {
      set_GeECCS_CCU2DCWhindex_enum((uint8_T)rtb_Add_m);
    } else {
      set_GeECCS_CCU2DCWhindex_enum(0U);
    }
  } else {
    set_GeECCS_CCU2DCWhindex_enum(MAX_uint8_T);
  }

  if (CbECCS_CCU1DCWhCurrentOvrSwt_flg) {
    set_GcECCS_CCU1DCWhCurrent_A(CcECCS_CCU1DCWhCurrentOvr_A);
  } else {
    tmp_0 = get_GcEBSW_LeftDCWhCurrent_A() * 5U + 2000U;
    if (tmp_0 > 32767U) {
      set_GcECCS_CCU1DCWhCurrent_A(MAX_uint16_T);
    } else {
      set_GcECCS_CCU1DCWhCurrent_A((uint16_T)((int32_T)tmp_0 << 1));
    }
  }

  if (CbECCS_CCU2DCWhCurrentOvrSwt_flg) {
    set_GcECCS_CCU2DCWhCurrent_A(CcECCS_CCU2DCWhCurrentOvr_A);
  } else {
    tmp_0 = get_GcEBSW_RightDCWhCurrent_A() * 5U + 2000U;
    if (tmp_0 > 32767U) {
      set_GcECCS_CCU2DCWhCurrent_A(MAX_uint16_T);
    } else {
      set_GcECCS_CCU2DCWhCurrent_A((uint16_T)((int32_T)tmp_0 << 1));
    }
  }

  if (CbECCS_CCU1DCWhCurrtEnergeOvrSwt_flg) {
    set_GcECCS_CCU1DCWhCurrtEnerge_Kwh(CcECCS_CCU1DCWhCurrtEnergeOvr_Kwh);
  } else {
    tmp = get_GcEBSW_LeftDCWhCurrtEnerge_kwH() / 0.1F;
    if (tmp < 65536.0F) {
      if (tmp >= 0.0F) {
        set_GcECCS_CCU1DCWhCurrtEnerge_Kwh((uint16_T)tmp);
      } else {
        set_GcECCS_CCU1DCWhCurrtEnerge_Kwh(0U);
      }
    } else {
      set_GcECCS_CCU1DCWhCurrtEnerge_Kwh(MAX_uint16_T);
    }
  }

  if (CbECCS_CCU2DCWhCurrtEnergeOvrSwt_flg) {
    set_GcECCS_CCU2DCWhCurrtEnerge_Kwh(CcECCS_CCU2DCWhCurrtEnergeOvr_Kwh);
  } else {
    tmp = get_GcEBSW_RightDCWhCurrtEnerge_kwH() / 0.1F;
    if (tmp < 65536.0F) {
      if (tmp >= 0.0F) {
        set_GcECCS_CCU2DCWhCurrtEnerge_Kwh((uint16_T)tmp);
      } else {
        set_GcECCS_CCU2DCWhCurrtEnerge_Kwh(0U);
      }
    } else {
      set_GcECCS_CCU2DCWhCurrtEnerge_Kwh(MAX_uint16_T);
    }
  }

  if (CbECCS_CCU1DCWhOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU1DCWhOutputVolt_V(CcECCS_CCU1DCWhOutputVoltOvr_V);
  } else {
    tmp_0 = get_GcEBSW_LeftDCWhInputVolt_V() * 10U;
    if (tmp_0 > 65535U) {
      tmp_0 = 65535U;
    }

    set_GcECCS_CCU1DCWhOutputVolt_V((uint16_T)tmp_0);
  }

  if (CbECCS_CCU2DCWhOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU2DCWhOutputVolt_V(CcECCS_CCU2DCWhOutputVoltOvr_V);
  } else {
    tmp_0 = get_GcEBSW_RightDCWhInputVolt_V() * 10U;
    if (tmp_0 > 65535U) {
      tmp_0 = 65535U;
    }

    set_GcECCS_CCU2DCWhOutputVolt_V((uint16_T)tmp_0);
  }

  if (rtb_Add_m >= ECCS_ConstB.DataTypeConversion2) {
    ECCS_DW.StateName = ECCS_ConstB.DataTypeConversion;
  } else {
    ECCS_DW.StateName = rtb_Add_m;
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_DCWh_1813FAF1h_1000ms_at_outport_1' */
void ECCS_EMS_DCWh_1813FAF1h_1000ms(void)
{
  int32_T rtb_Add;
  int32_T rtb_Add_b;
  uint16_T rtb_DataTypeConversion2;
  uint16_T rtb_DataTypeConversion1_g;
  uint16_T rtb_DataTypeConversion3;
  real32_T tmp;
  int32_T tmp_0;
  rtb_Add = ECCS_DW.StateName_d + 1;
  rtb_DataTypeConversion1_g = (uint16_T)(real32_T)fmod((real32_T)floor
    (((real32_T)get_GcEBSW_ACDCCurrent_A( rtb_Add - 1 ) + 400.0F) / 0.1F),
    65536.0F);
  rtb_Add_b = ECCS_DW.StateName_b + 1;
  tmp_0 = (int32_T)fmod(rtb_Add_b, 256.0);
  rtb_DataTypeConversion3 = (uint16_T)(real32_T)fmod((real32_T)floor((real32_T)
    get_GcEBSW_ACDCOutputVolt_V( rtb_Add_b - 1 ) / 0.1F), 65536.0F);
  tmp = (real32_T)floor(((real32_T)rtb_DataTypeConversion1_g * 0.1F - 400.0F) *
                        ((real32_T)rtb_DataTypeConversion3 * 0.1F) /
                        ECCS_ConstB.DataTypeConversion7);
  if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
    tmp = 0.0F;
  } else {
    tmp = (real32_T)fmod(tmp, 65536.0F);
  }

  rtb_DataTypeConversion2 = (uint16_T)(tmp < 0.0F ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  if (CbECCS_CCU1ACDCCurrentOvrSwt_flg) {
    set_GcECCS_CCU1ACDCCurrent_A(CcECCS_CCU1ACDCCurrentOvr_A);
  } else {
    set_GcECCS_CCU1ACDCCurrent_A(rtb_DataTypeConversion1_g);
  }

  if (CbECCS_CCU1ACDCCurrtPowerOvrSwt_flg) {
    set_GcECCS_CCU1ACDCCurrtPower_Kw(CcECCS_CCU1ACDCCurrtPowerOvr_Kw);
  } else {
    set_GcECCS_CCU1ACDCCurrtPower_Kw(rtb_DataTypeConversion2);
  }

  if (CbECCS_CCU1ACDCOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU1ACDCOutputVolt_V(CcECCS_CCU1ACDCOutputVoltOvr_V);
  } else {
    set_GcECCS_CCU1ACDCOutputVolt_V(rtb_DataTypeConversion3);
  }

  if (CbECCS_CCU2ACDCCurrentOvrSwt_flg) {
    set_GcECCS_CCU2ACDCCurrent_A(CcECCS_CCU2ACDCCurrentOvr_A);
  } else {
    set_GcECCS_CCU2ACDCCurrent_A(rtb_DataTypeConversion1_g);
  }

  if (CbECCS_CCU2ACDCCurrtPowerOvrSwt_flg) {
    set_GcECCS_CCU2ACDCCurrtPower_Kw(CcECCS_CCU2ACDCCurrtPowerOvr_Kw);
  } else {
    set_GcECCS_CCU2ACDCCurrtPower_Kw(rtb_DataTypeConversion2);
  }

  if (CbECCS_CCU2ACDCOutputVoltOvrSwt_flg) {
    set_GcECCS_CCU2ACDCOutputVolt_V(CcECCS_CCU2ACDCOutputVoltOvr_V);
  } else {
    set_GcECCS_CCU2ACDCOutputVolt_V(rtb_DataTypeConversion3);
  }

  if (CbECCS_CCU1ACDCindexOvrSwt_flg) {
    set_GeECCS_CCU1ACDCindex_enum(CeECCS_CCU1ACDCindexOvr_enum);
  } else {
    set_GeECCS_CCU1ACDCindex_enum((uint8_T)tmp_0);
  }

  if (CbECCS_CCU2ACDCindexOvrSwt_flg) {
    set_GeECCS_CCU2ACDCindex_enum(CeECCS_CCU2ACDCindexOvr_enum);
  } else {
    set_GeECCS_CCU2ACDCindex_enum((uint8_T)tmp_0);
  }

  if (rtb_Add >= 2) {
    ECCS_DW.StateName_d = 0U;
  } else {
    ECCS_DW.StateName_d = 1U;
  }

  if (rtb_Add_b >= 2) {
    ECCS_DW.StateName_b = 0U;
  } else {
    ECCS_DW.StateName_b = 1U;
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_DTC_18AAFAF1h_200ms_at_outport_1' */
void ECCS_EMS_DTC_18AAFAF1h_200ms(void)
{
  if (CbECCS_CCU1EMSDTCHighByteOvrSwt_flg) {
    set_GcECCS_CCU1EMSDTCHighByte_numb(CcECCS_CCU1EMSDTCHighByteOvr_numb);
  } else {
    set_GcECCS_CCU1EMSDTCHighByte_numb(get_GcEDEC_DTCHighByte_numb());
  }

  if (CbECCS_CCU2EMSDTCHighByteOvrSwt_flg) {
    set_GcECCS_CCU2EMSDTCHighByte_numb(CcECCS_CCU2EMSDTCHighByteOvr_numb);
  } else {
    set_GcECCS_CCU2EMSDTCHighByte_numb(get_GcEDEC_DTCHighByte_numb());
  }

  if (CbECCS_CCU1EMSDTCLowByteOvrSwt_flg) {
    set_GcECCS_CCU1EMSDTCLowByte_numb(CcECCS_CCU1EMSDTCLowByteOvr_numb);
  } else {
    set_GcECCS_CCU1EMSDTCLowByte_numb(get_GcEDEC_DTCLowByte_numb());
  }

  if (CbECCS_CCU2EMSDTCLowByteOvrSwt_flg) {
    set_GcECCS_CCU2EMSDTCLowByte_numb(CcECCS_CCU2EMSDTCLowByteOvr_numb);
  } else {
    set_GcECCS_CCU2EMSDTCLowByte_numb(get_GcEDEC_DTCLowByte_numb());
  }

  if (CbECCS_CCU1EMSDTCFailureTypeByteOvrSwt_flg) {
    set_GcECCS_CCU1EMSDTCFailureTypeByte_numb
      (CcECCS_CCU1EMSDTCFailureTypeByteOvr_numb);
  } else {
    set_GcECCS_CCU1EMSDTCFailureTypeByte_numb(get_GcEDEC_DTCFailureType_numb());
  }

  if (CbECCS_CCU2EMSDTCFailureTypeByteOvrSwt_flg) {
    set_GcECCS_CCU2EMSDTCFailureTypeByte_numb
      (CcECCS_CCU2EMSDTCFailureTypeByteOvr_numb);
  } else {
    set_GcECCS_CCU2EMSDTCFailureTypeByte_numb(get_GcEDEC_DTCFailureType_numb());
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_HV1_1810FAF1h_100ms_at_outport_1' */
void ECCS_EMS_HV1_1810FAF1h_100ms(void)
{
  uint16_T rtb_DataTypeConversion6_j;
  real32_T tmp;
  if (CbECCS_CCU1EMSACDCVoltOvrSwt_flg) {
    set_GcECCS_CCU1EMSACDCVolt_V(CcECCS_CCU1EMSACDCVoltOvr_V);
  } else {
    set_GcECCS_CCU1EMSACDCVolt_V(ECCS_ConstB.DataTypeConversion_a);
  }

  if (CbECCS_CCU2EMSACDCVoltOvrSwt_flg) {
    set_GcECCS_CCU2EMSACDCVolt_V(CcECCS_CCU2EMSACDCVoltOvr_V);
  } else {
    set_GcECCS_CCU2EMSACDCVolt_V(ECCS_ConstB.DataTypeConversion1_gw);
  }

  if (CbECCS_CCU1EMSK15FUSEVoltOvrSwt_flg) {
    set_GcECCS_CCU1EMSK15FUSEVolt_V(CcECCS_CCU1EMSK15FUSEVoltOvr_V);
  } else {
    set_GcECCS_CCU1EMSK15FUSEVolt_V(ECCS_ConstB.DataTypeConversion2_o);
  }

  if (CbECCS_CCU2EMSK15FUSEVoltOvrSwt_flg) {
    set_GcECCS_CCU2EMSK15FUSEVolt_V(CcECCS_CCU2EMSK15FUSEVoltOvr_V);
  } else {
    set_GcECCS_CCU2EMSK15FUSEVolt_V(ECCS_ConstB.DataTypeConversion3_p);
  }

  if (CbECCS_CCU1EMSK15K16VoltOvrSwt_flg) {
    set_GcECCS_CCU1EMSK15K16Volt_V(CcECCS_CCU1EMSK15K16VoltOvr_V);
  } else {
    set_GcECCS_CCU1EMSK15K16Volt_V(ECCS_ConstB.DataTypeConversion4);
  }

  if (CbECCS_CCU2EMSK15K16VoltOvrSwt_flg) {
    set_GcECCS_CCU2EMSK15K16Volt_V(CcECCS_CCU2EMSK15K16VoltOvr_V);
  } else {
    set_GcECCS_CCU2EMSK15K16Volt_V(ECCS_ConstB.DataTypeConversion5_d);
  }

  tmp = (real32_T)floor(get_GcEBSW_BackupBatOutVolt_V() / 0.1F);
  if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
    tmp = 0.0F;
  } else {
    tmp = (real32_T)fmod(tmp, 65536.0F);
  }

  rtb_DataTypeConversion6_j = (uint16_T)(tmp < 0.0F ? (int32_T)(uint16_T)
    -(int16_T)(uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  if (CbECCS_CCU1LowBatteryVoltOvrSwt_flg) {
    set_GcECCS_CCU1LowBatteryVolt_V(CcECCS_CCU1LowBatteryVoltOvr_V);
  } else {
    set_GcECCS_CCU1LowBatteryVolt_V(rtb_DataTypeConversion6_j);
  }

  if (CbECCS_CCU2LowBatteryVoltOvrSwt_flg) {
    set_GcECCS_CCU2LowBatteryVolt_V(CcECCS_CCU2LowBatteryVoltOvr_V);
  } else {
    set_GcECCS_CCU2LowBatteryVolt_V(rtb_DataTypeConversion6_j);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_HV2_1811FAF1h_100ms_at_outport_1' */
void ECCS_EMS_HV2_1811FAF1h_100ms(void)
{
  uint16_T rtb_DataTypeConversion2;
  real32_T tmp;
  if (CbECCS_CCU1DCDCInputVoltOvrSwt_flg) {
    set_GcECCS_CCU1DCDCInputVolt_V(CcECCS_CCU1DCDCInputVoltOvr_V);
  } else {
    set_GcECCS_CCU1DCDCInputVolt_V(ECCS_ConstB.DataTypeConversion_e);
  }

  if (CbECCS_CCU2DCDCInputVoltOvrSwt_flg) {
    set_GcECCS_CCU2DCDCInputVolt_V(CcECCS_CCU2DCDCInputVoltOvr_V);
  } else {
    set_GcECCS_CCU2DCDCInputVolt_V(ECCS_ConstB.DataTypeConversion_e);
  }

  if (CbECCS_CCU1InputVoltOvrSwt_flg) {
    set_GcECCS_CCU1InputVolt_V(CcECCS_CCU1InputVoltOvr_V);
  } else {
    set_GcECCS_CCU1InputVolt_V(ECCS_ConstB.DataTypeConversion1_g);
  }

  if (CbECCS_CCU2InputVoltOvrSwt_flg) {
    set_GcECCS_CCU2InputVolt_V(CcECCS_CCU2InputVoltOvr_V);
  } else {
    set_GcECCS_CCU2InputVolt_V(ECCS_ConstB.DataTypeConversion1_g);
  }

  tmp = (real32_T)floor(get_GcEBSW_HeatVolt_V() / 0.1F);
  if (rtIsNaNF(tmp) || rtIsInfF(tmp)) {
    tmp = 0.0F;
  } else {
    tmp = (real32_T)fmod(tmp, 65536.0F);
  }

  rtb_DataTypeConversion2 = (uint16_T)(tmp < 0.0F ? (int32_T)(uint16_T)-(int16_T)
    (uint16_T)-tmp : (int32_T)(uint16_T)tmp);
  if (CbECCS_CCU1HeatInputVoltOvrSwt_flg) {
    set_GcECCS_CCU1HeatInputVolt_V(CcECCS_CCU1HeatInputVoltOvr_V);
  } else {
    set_GcECCS_CCU1HeatInputVolt_V(rtb_DataTypeConversion2);
  }

  if (CbECCS_CCU2HeatInputVoltOvrSwt_flg) {
    set_GcECCS_CCU2HeatInputVolt_V(CcECCS_CCU2HeatInputVoltOvr_V);
  } else {
    set_GcECCS_CCU2HeatInputVolt_V(rtb_DataTypeConversion2);
  }

  if (CbECCS_CCU1EMSSwVersionOvrSwt_flg) {
    set_GcECCS_CCU1EMSSwVersion_numb(CcECCS_CCU1EMSSwVersionOvr_numb);
  } else {
    set_GcECCS_CCU1EMSSwVersion_numb(ECCS_ConstB.DataTypeConversion3_o);
  }

  if (CbECCS_CCU2EMSSwVersionOvrSwt_flg) {
    set_GcECCS_CCU2EMSSwVersion_numb(CcECCS_CCU2EMSSwVersionOvr_numb);
  } else {
    set_GcECCS_CCU2EMSSwVersion_numb(ECCS_ConstB.DataTypeConversion3_o);
  }

  if (CbECCS_CCU1EMSHwVersionOvrSwt_flg) {
    set_GcECCS_CCU1EMSHwVersion_numb(CcECCS_CCU1EMSHwVersionOvr_numb);
  } else {
    set_GcECCS_CCU1EMSHwVersion_numb(ECCS_ConstB.DataTypeConversion4_i);
  }

  if (CbECCS_CCU2EMSHwVersionOvrSwt_flg) {
    set_GcECCS_CCU2EMSHwVersion_numb(CcECCS_CCU2EMSHwVersionOvr_numb);
  } else {
    set_GcECCS_CCU2EMSHwVersion_numb(ECCS_ConstB.DataTypeConversion4_i);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_PosLog_1806FAF1h_250ms_at_outport_1' */
void ECCS_EMS_PosLog_1806FAF1h_250ms(void)
{
  if (CbECCS_CCU1EMSToCHGIndexOvrSwt_flg) {
    set_GeECCS_CCU1EMSToCHGIndex_enum(CeECCS_CCU1EMSToCHGIndexOvr_enum);
  } else {
    set_GeECCS_CCU1EMSToCHGIndex_enum(ECCS_ConstB.DataTypeConversion1_b);
  }

  if (CbECCS_CCU2EMSToCHGIndexOvrSwt_flg) {
    set_GeECCS_CCU2EMSToCHGIndex_enum(CeECCS_CCU2EMSToCHGIndexOvr_enum);
  } else {
    set_GeECCS_CCU2EMSToCHGIndex_enum(ECCS_ConstB.DataTypeConversion1_b);
  }

  if (CbECCS_CCU1CRMSPN2561CHGIndexOvrSwt_flg) {
    set_GeECCS_CCU1CRMSPN2561CHGIndex_enum(CeECCS_CCU1CRMSPN2561CHGIndexOvr_enum);
  } else {
    set_GeECCS_CCU1CRMSPN2561CHGIndex_enum(ECCS_ConstB.DataTypeConversion2_h);
  }

  if (CbECCS_CCU2CRMSPN2561CHGIndexOvrSwt_flg) {
    set_GeECCS_CCU2CRMSPN2561CHGIndex_enum(CeECCS_CCU2CRMSPN2561CHGIndexOvr_enum);
  } else {
    set_GeECCS_CCU2CRMSPN2561CHGIndex_enum(ECCS_ConstB.DataTypeConversion2_h);
  }

  if (CbECCS_CCU1CRMSPN2562CHGLocOvrSwt_flg) {
    set_GeECCS_CCU1CRMSPN2562CHGLoc_enum(CeECCS_CCU1CRMSPN2562CHGLocOvr_enum);
  } else {
    set_GeECCS_CCU1CRMSPN2562CHGLoc_enum(ECCS_ConstB.DataTypeConversion3);
  }

  if (CbECCS_CCU2CRMSPN2562CHGLocOvrSwt_flg) {
    set_GeECCS_CCU2CRMSPN2562CHGLoc_enum(CeECCS_CCU2CRMSPN2562CHGLocOvr_enum);
  } else {
    set_GeECCS_CCU2CRMSPN2562CHGLoc_enum(ECCS_ConstB.DataTypeConversion3);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_PowerModul_1802FAF1h_250ms_at_outport_1' */
void ECCS_EMS_PowerModul_1802FAF1h_250ms(void)
{
  if (CbECCS_CCU1ACDC1StatusOvrSwt_flg) {
    set_GeECCS_CCU1ACDC1Status_enum(CeECCS_CCU1ACDC1StatusOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC1Status_enum(get_GeEBSW_ACDC1Status_enum());
  }

  if (CbECCS_CCU2ACDC1StatusOvrSwt_flg) {
    set_GeECCS_CCU2ACDC1Status_enum(CeECCS_CCU2ACDC1StatusOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC1Status_enum(get_GeEBSW_ACDC1Status_enum());
  }

  if (CbECCS_CCU1ACDC2StatusOvrSwt_flg) {
    set_GeECCS_CCU1ACDC2Status_enum(CeECCS_CCU1ACDC2StatusOvr_enum);
  } else {
    set_GeECCS_CCU1ACDC2Status_enum(get_GeEBSW_ACDC2Status_enum());
  }

  if (CbECCS_CCU2ACDC2StatusOvrSwt_flg) {
    set_GeECCS_CCU2ACDC2Status_enum(CeECCS_CCU2ACDC2StatusOvr_enum);
  } else {
    set_GeECCS_CCU2ACDC2Status_enum(get_GeEBSW_ACDC2Status_enum());
  }

  if (CbECCS_CCU1DCDC1StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC1Status_enum(CeECCS_CCU1DCDC1StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC1Status_enum(get_GeEBSW_LeftDCDCStatus_enum());
  }

  if (CbECCS_CCU2DCDC1StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC1Status_enum(CeECCS_CCU2DCDC1StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC1Status_enum(get_GeEBSW_LeftDCDCStatus_enum());
  }

  if (CbECCS_CCU1DCDC2StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC2Status_enum(CeECCS_CCU1DCDC2StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC2Status_enum(get_GeEBSW_RightDCDCStatus_enum());
  }

  if (CbECCS_CCU2DCDC2StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC2Status_enum(CeECCS_CCU2DCDC2StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC2Status_enum(get_GeEBSW_RightDCDCStatus_enum());
  }

  if (CbECCS_CCU1DCDC3StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC3Status_enum(CeECCS_CCU1DCDC3StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC3Status_enum(get_GeEBSW_DCDC3Status_enum());
  }

  if (CbECCS_CCU2DCDC3StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC3Status_enum(CeECCS_CCU2DCDC3StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC3Status_enum(get_GeEBSW_DCDC3Status_enum());
  }

  if (CbECCS_CCU1DCDC4StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC4Status_enum(CeECCS_CCU1DCDC4StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC4Status_enum(get_GeEBSW_DCDC4Status_enum());
  }

  if (CbECCS_CCU2DCDC4StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC4Status_enum(CeECCS_CCU2DCDC4StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC4Status_enum(get_GeEBSW_DCDC4Status_enum());
  }

  if (CbECCS_CCU1DCDC5StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC5Status_enum(CeECCS_CCU1DCDC5StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC5Status_enum(get_GeEBSW_DCDC5Status_enum());
  }

  if (CbECCS_CCU2DCDC5StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC5Status_enum(CeECCS_CCU2DCDC5StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC5Status_enum(get_GeEBSW_DCDC5Status_enum());
  }

  if (CbECCS_CCU1DCDC6StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC6Status_enum(CeECCS_CCU1DCDC6StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC6Status_enum(get_GeEBSW_DCDC6Status_enum());
  }

  if (CbECCS_CCU2DCDC6StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC6Status_enum(CeECCS_CCU2DCDC6StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC6Status_enum(get_GeEBSW_DCDC6Status_enum());
  }

  if (CbECCS_CCU1DCDC7StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC7Status_enum(CeECCS_CCU1DCDC7StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC7Status_enum(get_GeEBSW_DCDC7Status_enum());
  }

  if (CbECCS_CCU2DCDC7StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC7Status_enum(CeECCS_CCU2DCDC7StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC7Status_enum(get_GeEBSW_DCDC7Status_enum());
  }

  if (CbECCS_CCU1DCDC8StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC8Status_enum(CeECCS_CCU1DCDC8StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC8Status_enum(get_GeEBSW_DCDC8Status_enum());
  }

  if (CbECCS_CCU2DCDC8StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC8Status_enum(CeECCS_CCU2DCDC8StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC8Status_enum(get_GeEBSW_DCDC8Status_enum());
  }

  if (CbECCS_CCU1DCDC9StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC9Status_enum(CeECCS_CCU1DCDC9StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC9Status_enum(get_GeEBSW_DCDC9Status_enum());
  }

  if (CbECCS_CCU2DCDC9StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC9Status_enum(CeECCS_CCU2DCDC9StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC9Status_enum(get_GeEBSW_DCDC9Status_enum());
  }

  if (CbECCS_CCU1DCDC10StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC10Status_enum(CeECCS_CCU1DCDC10StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC10Status_enum(get_GeEBSW_DCDC10Status_enum());
  }

  if (CbECCS_CCU2DCDC10StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC10Status_enum(CeECCS_CCU2DCDC10StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC10Status_enum(get_GeEBSW_DCDC10Status_enum());
  }

  if (CbECCS_CCU1DCDC11StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC11Status_enum(CeECCS_CCU1DCDC11StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC11Status_enum(get_GeEBSW_DCDC11Status_enum());
  }

  if (CbECCS_CCU2DCDC11StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC11Status_enum(CeECCS_CCU2DCDC11StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC11Status_enum(get_GeEBSW_DCDC11Status_enum());
  }

  if (CbECCS_CCU1DCDC12StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC12Status_enum(CeECCS_CCU1DCDC12StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC12Status_enum(get_GeEBSW_DCDC12Status_enum());
  }

  if (CbECCS_CCU2DCDC12StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC12Status_enum(CeECCS_CCU2DCDC12StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC12Status_enum(get_GeEBSW_DCDC12Status_enum());
  }

  if (CbECCS_CCU1DCDC13StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC13Status_enum(CeECCS_CCU1DCDC13StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC13Status_enum(get_GeEBSW_DCDC13Status_enum());
  }

  if (CbECCS_CCU2DCDC13StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC13Status_enum(CeECCS_CCU2DCDC13StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC13Status_enum(get_GeEBSW_DCDC13Status_enum());
  }

  if (CbECCS_CCU1DCDC14StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC14Status_enum(CeECCS_CCU1DCDC14StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC14Status_enum(get_GeEBSW_DCDC14Status_enum());
  }

  if (CbECCS_CCU2DCDC14StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC14Status_enum(CeECCS_CCU2DCDC14StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC14Status_enum(get_GeEBSW_DCDC14Status_enum());
  }

  if (CbECCS_CCU1DCDC15StatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDC15Status_enum(CeECCS_CCU1DCDC15StatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDC15Status_enum(get_GeEBSW_DCDC15Status_enum());
  }

  if (CbECCS_CCU2DCDC15StatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDC15Status_enum(CeECCS_CCU2DCDC15StatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDC15Status_enum(get_GeEBSW_DCDC15Status_enum());
  }

  if (CbECCS_CCU1DCDCT24VStatusOvrSwt_flg) {
    set_GeECCS_CCU1DCDCT24VStatus_enum(CeECCS_CCU1DCDCT24VStatusOvr_enum);
  } else {
    set_GeECCS_CCU1DCDCT24VStatus_enum(ECCS_U.GeEDCM_SmallDCDCStatus_enum);
  }

  if (CbECCS_CCU2DCDCT24VStatusOvrSwt_flg) {
    set_GeECCS_CCU2DCDCT24VStatus_enum(CeECCS_CCU2DCDCT24VStatusOvr_enum);
  } else {
    set_GeECCS_CCU2DCDCT24VStatus_enum(ECCS_U.GeEDCM_SmallDCDCStatus_enum);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_Timer_1809FAF1h_1000ms_at_outport_1' */
void ECCS_EMS_Timer_1809FAF1h_1000ms(void)
{
  if (CbECCS_CCU1EMSSetTimerenbleOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerenble_flg(CcECCS_CCU1EMSSetTimerenbleOvr_flg);
  } else {
    set_GcECCS_CCU1EMSSetTimerenble_flg(ECCS_ConstB.DataTypeConversion_l);
  }

  if (CbECCS_CCU2EMSSetTimerenbleOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerenble_flg(CcECCS_CCU2EMSSetTimerenbleOvr_flg);
  } else {
    set_GcECCS_CCU2EMSSetTimerenble_flg(ECCS_ConstB.DataTypeConversion_l);
  }

  if (CbECCS_CCU1EMSSetTimerYearOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerYear_Y(CcECCS_CCU1EMSSetTimerYearOvr_Y);
  } else {
    set_GcECCS_CCU1EMSSetTimerYear_Y(ECCS_ConstB.DataTypeConversion1_ju);
  }

  if (CbECCS_CCU2EMSSetTimerYearOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerYear_Y(CcECCS_CCU2EMSSetTimerYearOvr_Y);
  } else {
    set_GcECCS_CCU2EMSSetTimerYear_Y(ECCS_ConstB.DataTypeConversion1_ju);
  }

  if (CbECCS_CCU1EMSSetTimerMonthOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerMonth_M(CcECCS_CCU1EMSSetTimerMonthOvr_M);
  } else {
    set_GcECCS_CCU1EMSSetTimerMonth_M(ECCS_ConstB.DataTypeConversion2_l);
  }

  if (CbECCS_CCU2EMSSetTimerMonthOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerMonth_M(CcECCS_CCU2EMSSetTimerMonthOvr_M);
  } else {
    set_GcECCS_CCU2EMSSetTimerMonth_M(ECCS_ConstB.DataTypeConversion2_l);
  }

  if (CbECCS_CCU1EMSSetTimerDayOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerDay_D(CcECCS_CCU1EMSSetTimerDayOvr_D);
  } else {
    set_GcECCS_CCU1EMSSetTimerDay_D(ECCS_ConstB.DataTypeConversion3_j);
  }

  if (CbECCS_CCU2EMSSetTimerDayOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerDay_D(CcECCS_CCU2EMSSetTimerDayOvr_D);
  } else {
    set_GcECCS_CCU2EMSSetTimerDay_D(ECCS_ConstB.DataTypeConversion3_j);
  }

  if (CbECCS_CCU1EMSSetTimerHourOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerHour_H(CcECCS_CCU1EMSSetTimerHourOvr_H);
  } else {
    set_GcECCS_CCU1EMSSetTimerHour_H(ECCS_ConstB.DataTypeConversion4_c);
  }

  if (CbECCS_CCU2EMSSetTimerHourOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerHour_H(CcECCS_CCU2EMSSetTimerHourOvr_H);
  } else {
    set_GcECCS_CCU2EMSSetTimerHour_H(ECCS_ConstB.DataTypeConversion4_c);
  }

  if (CbECCS_CCU1EMSSetTimerMinuteOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerMinute_Min(CcECCS_CCU1EMSSetTimerMinuteOvr_Min);
  } else {
    set_GcECCS_CCU1EMSSetTimerMinute_Min(ECCS_ConstB.DataTypeConversion5_a);
  }

  if (CbECCS_CCU2EMSSetTimerMinuteOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerMinute_Min(CcECCS_CCU2EMSSetTimerMinuteOvr_Min);
  } else {
    set_GcECCS_CCU2EMSSetTimerMinute_Min(ECCS_ConstB.DataTypeConversion5_a);
  }

  if (CbECCS_CCU1EMSSetTimerSecondOvrSwt_flg) {
    set_GcECCS_CCU1EMSSetTimerSecond_S(CcECCS_CCU1EMSSetTimerSecondOvr_S);
  } else {
    set_GcECCS_CCU1EMSSetTimerSecond_S(ECCS_ConstB.DataTypeConversion6_n);
  }

  if (CbECCS_CCU2EMSSetTimerSecondOvrSwt_flg) {
    set_GcECCS_CCU2EMSSetTimerSecond_S(CcECCS_CCU2EMSSetTimerSecondOvr_S);
  } else {
    set_GcECCS_CCU2EMSSetTimerSecond_S(ECCS_ConstB.DataTypeConversion6_n);
  }
}

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_ECCS_EMS_Warning_1808FAF1h_100ms_at_outport_1' */
void ECCS_EMS_Warning_1808FAF1h_100ms(void)
{
  if (CbECCS_CCU1EMSHVIsoWarningOvrSwt_flg) {
    set_GeECCS_CCU1EMSHVIsoWarning_enum(CeECCS_CCU1EMSHVIsoWarningOvr_enum);
  } else {
    set_GeECCS_CCU1EMSHVIsoWarning_enum(ECCS_ConstB.DataTypeConversion_f);
  }

  if (CbECCS_CCU2EMSHVIsoWarningOvrSwt_flg) {
    set_GeECCS_CCU2EMSHVIsoWarning_enum(CeECCS_CCU2EMSHVIsoWarningOvr_enum);
  } else {
    set_GeECCS_CCU2EMSHVIsoWarning_enum(ECCS_ConstB.DataTypeConversion_f);
  }

  if (CbECCS_CCU1ACDCInputOverVoltOvrSwt_flg) {
    set_GbECCS_CCU1ACDCInputOverVolt_flg(CbECCS_CCU1ACDCInputOverVoltOvr_flg);
  } else {
    set_GbECCS_CCU1ACDCInputOverVolt_flg(ECCS_ConstB.DataTypeConversion1_k);
  }

  if (CbECCS_CCU2ACDCInputOverVoltOvrSwt_flg) {
    set_GbECCS_CCU2ACDCInputOverVolt_flg(CbECCS_CCU2ACDCInputOverVoltOvr_flg);
  } else {
    set_GbECCS_CCU2ACDCInputOverVolt_flg(ECCS_ConstB.DataTypeConversion1_k);
  }

  if (CbECCS_CCU1ACDCInputUnderVoltOvrSwt_flg) {
    set_GbECCS_CCU1ACDCInputUnderVolt_flg(CbECCS_CCU1ACDCInputUnderVoltOvr_flg);
  } else {
    set_GbECCS_CCU1ACDCInputUnderVolt_flg(ECCS_ConstB.DataTypeConversion2_n);
  }

  if (CbECCS_CCU2ACDCInputUnderVoltOvrSwt_flg) {
    set_GbECCS_CCU2ACDCInputUnderVolt_flg(CbECCS_CCU2ACDCInputUnderVoltOvr_flg);
  } else {
    set_GbECCS_CCU2ACDCInputUnderVolt_flg(ECCS_ConstB.DataTypeConversion2_n);
  }

  if (CbECCS_CCU1ACDCinputLossPhaseOvrSwt_flg) {
    set_GbECCS_CCU1ACDCinputLossPhase_flg(CbECCS_CCU1ACDCinputLossPhaseOvr_flg);
  } else {
    set_GbECCS_CCU1ACDCinputLossPhase_flg(ECCS_ConstB.DataTypeConversion3_i);
  }

  if (CbECCS_CCU2ACDCinputLossPhaseOvrSwt_flg) {
    set_GbECCS_CCU2ACDCinputLossPhase_flg(CbECCS_CCU2ACDCinputLossPhaseOvr_flg);
  } else {
    set_GbECCS_CCU2ACDCinputLossPhase_flg(ECCS_ConstB.DataTypeConversion3_i);
  }

  if (CbECCS_CCU1SupplyPwrwarningOvrSwt_flg) {
    set_GeECCS_CCU1SupplyPwrwarning_enum(CeECCS_CCU1SupplyPwrwarningOvr_enum);
  } else {
    set_GeECCS_CCU1SupplyPwrwarning_enum(ECCS_ConstB.DataTypeConversion4_p);
  }

  if (CbECCS_CCU2SupplyPwrwarningOvrSwt_flg) {
    set_GeECCS_CCU2SupplyPwrwarning_enum(CeECCS_CCU2SupplyPwrwarningOvr_enum);
  } else {
    set_GeECCS_CCU2SupplyPwrwarning_enum(ECCS_ConstB.DataTypeConversion4_p);
  }

  if (CbECCS_CCU1ACDCPowerCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1ACDCPowerCommwarning_flg
      (CbECCS_CCU1ACDCPowerCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1ACDCPowerCommwarning_flg(ECCS_ConstB.DataTypeConversion5_c);
  }

  if (CbECCS_CCU2ACDCPowerCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2ACDCPowerCommwarning_flg
      (CbECCS_CCU2ACDCPowerCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2ACDCPowerCommwarning_flg(ECCS_ConstB.DataTypeConversion5_c);
  }

  if (CbECCS_CCU1DCDCPowerCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1DCDCPowerCommwarning_flg
      (CbECCS_CCU1DCDCPowerCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1DCDCPowerCommwarning_flg(ECCS_ConstB.DataTypeConversion6);
  }

  if (CbECCS_CCU2DCDCPowerCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2DCDCPowerCommwarning_flg
      (CbECCS_CCU2DCDCPowerCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2DCDCPowerCommwarning_flg(ECCS_ConstB.DataTypeConversion6);
  }

  if (CbECCS_CCU1DCDT24CommwarningOvrSwt_flg) {
    set_GbECCS_CCU1DCDT24Commwarning_flg(CbECCS_CCU1DCDT24CommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1DCDT24Commwarning_flg(ECCS_ConstB.DataTypeConversion7_l);
  }

  if (CbECCS_CCU2DCDT24CommwarningOvrSwt_flg) {
    set_GbECCS_CCU2DCDT24Commwarning_flg(CbECCS_CCU2DCDT24CommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2DCDT24Commwarning_flg(ECCS_ConstB.DataTypeConversion7_l);
  }

  if (CbECCS_CCU1ACWhMeterCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1ACWhMeterCommwarning_flg
      (CbECCS_CCU1ACWhMeterCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1ACWhMeterCommwarning_flg(ECCS_ConstB.DataTypeConversion8);
  }

  if (CbECCS_CCU2ACWhMeterCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2ACWhMeterCommwarning_flg
      (CbECCS_CCU2ACWhMeterCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2ACWhMeterCommwarning_flg(ECCS_ConstB.DataTypeConversion8);
  }

  if (CbECCS_CCU1DCWhMeterCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1DCWhMeterCommwarning_flg
      (CbECCS_CCU1DCWhMeterCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1DCWhMeterCommwarning_flg(ECCS_ConstB.DataTypeConversion9);
  }

  if (CbECCS_CCU2DCWhMeterCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2DCWhMeterCommwarning_flg
      (CbECCS_CCU2DCWhMeterCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2DCWhMeterCommwarning_flg(ECCS_ConstB.DataTypeConversion9);
  }

  if (CbECCS_CCU1TouchCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1TouchCommwarning_flg(CbECCS_CCU1TouchCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1TouchCommwarning_flg(ECCS_ConstB.DataTypeConversion10);
  }

  if (CbECCS_CCU2TouchCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2TouchCommwarning_flg(CbECCS_CCU2TouchCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2TouchCommwarning_flg(ECCS_ConstB.DataTypeConversion10);
  }

  if (CbECCS_CCU1ADCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1ADCommwarning_flg(CbECCS_CCU1ADCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1ADCommwarning_flg(ECCS_ConstB.DataTypeConversion11);
  }

  if (CbECCS_CCU2ADCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2ADCommwarning_flg(CbECCS_CCU2ADCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2ADCommwarning_flg(ECCS_ConstB.DataTypeConversion11);
  }

  if (CbECCS_CCU1CardCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1CardCommwarning_flg(CbECCS_CCU1CardCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1CardCommwarning_flg(ECCS_ConstB.DataTypeConversion12);
  }

  if (CbECCS_CCU2CardCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2CardCommwarning_flg(CbECCS_CCU2CardCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2CardCommwarning_flg(ECCS_ConstB.DataTypeConversion12);
  }

  if (CbECCS_CCU1BMSCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1BMSCommwarning_flg(CbECCS_CCU1BMSCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1BMSCommwarning_flg(ECCS_ConstB.DataTypeConversion13);
  }

  if (CbECCS_CCU2BMSCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2BMSCommwarning_flg(CbECCS_CCU2BMSCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2BMSCommwarning_flg(ECCS_ConstB.DataTypeConversion13);
  }

  if (CbECCS_CCU1TBOXCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1TBOXCommwarning_flg(CbECCS_CCU1TBOXCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1TBOXCommwarning_flg(ECCS_ConstB.DataTypeConversion14);
  }

  if (CbECCS_CCU2TBOXCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2TBOXCommwarning_flg(CbECCS_CCU2TBOXCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2TBOXCommwarning_flg(ECCS_ConstB.DataTypeConversion14);
  }

  if (CbECCS_CCU1CCUCommwarningOvrSwt_flg) {
    set_GbECCS_CCU1CCUCommwarning_flg(CbECCS_CCU1CCUCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU1CCUCommwarning_flg(ECCS_ConstB.DataTypeConversion15);
  }

  if (CbECCS_CCU2CCUCommwarningOvrSwt_flg) {
    set_GbECCS_CCU2CCUCommwarning_flg(CbECCS_CCU2CCUCommwarningOvr_flg);
  } else {
    set_GbECCS_CCU2CCUCommwarning_flg(ECCS_ConstB.DataTypeConversion15);
  }

  if (CbECCS_CCU1AntithunderwarningOvrSwt_flg) {
    set_GbECCS_CCU1Antithunderwarning_flg(CbECCS_CCU1AntithunderwarningOvr_flg);
  } else {
    set_GbECCS_CCU1Antithunderwarning_flg(ECCS_ConstB.DataTypeConversion16);
  }

  if (CbECCS_CCU2AntithunderwarningOvrSwt_flg) {
    set_GbECCS_CCU2Antithunderwarning_flg(CbECCS_CCU2AntithunderwarningOvr_flg);
  } else {
    set_GbECCS_CCU2Antithunderwarning_flg(ECCS_ConstB.DataTypeConversion16);
  }
}

/* Model initialize function */
void ECCS_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));
  set_GcECCS_CCU1ACDCCurrent_A(4000U);
  set_GcECCS_CCU2ACDCCurrent_A(4000U);
  set_GcECCS_CCU1ACWhCurrent_A(4000U);
  set_GcECCS_CCU2ACWhCurrent_A(4000U);
  set_GcECCS_CCU1CMLSPN2827IMinOut_A(4000U);
  set_GcECCS_CCU2CMLSPN2827IMinOut_A(4000U);
  set_GcECCS_CCU1CMLSPN2826IMaxOut_A(4000U);
  set_GcECCS_CCU2CMLSPN2826IMaxOut_A(4000U);
  set_GcECCS_CCU1DCDCCurrent_A(4000U);
  set_GcECCS_CCU2DCDCCurrent_A(4000U);
  set_GcECCS_CCU1DCWhCurrent_A(4000U);
  set_GcECCS_CCU2DCWhCurrent_A(4000U);
  set_GcECCS_CCU1CellTmpTarget_C(40U);
  set_GcECCS_CCU2CellTmpTarget_C(40U);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
