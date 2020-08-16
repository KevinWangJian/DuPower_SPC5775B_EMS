/*
 * File: EBCS.c
 *
 * Code generated for Simulink model 'EBCS'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 16 09:46:28 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EBCS.h"
#include "EBCS_private.h"

/* Real-time model */
RT_MODEL_EBCS_T EBCS_M_;
RT_MODEL_EBCS_T *const EBCS_M = &EBCS_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EBCS_BMS_EMS_SysStat_1801FAF1_10ms_at_outport_1' */
void EBCS_BMS_EMS_SysStat_1801FAF1_10ms(void)
{
  if (CbEBCS_BMSAEMSRechargeCntctrReqOvrSwt_flg) {
    set_GeEBCS_BMSAEMSRechargeCntctrReq_enum
      (CeEBCS_BMSAEMSRechargeCntctrReqOvr_enum);
  } else {
    set_GeEBCS_BMSAEMSRechargeCntctrReq_enum((uint8_T)
      ((get_GbEACT_ReChrgAPosCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       (get_GbEACT_ReChrgANegCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE))));
  }

  if (CbEBCS_BMSABMSIsoDetAllowOvrSwt_flg) {
    set_GbEBCS_BMSABMSIsoDetAllow_flg(CbEBCS_BMSABMSIsoDetAllowOvr_flg);
  } else {
    set_GbEBCS_BMSABMSIsoDetAllow_flg(get_GbEISO_BMS1StartISOEn_flg());
  }

  if (CbEBCS_BMSABMSISOPosMosCmdOvrSwt_flg) {
    set_GbEBCS_BMSABMSISOPosMosCmd_flg(CbEBCS_BMSABMSISOPosMosCmdOvr_flg);
  } else {
    set_GbEBCS_BMSABMSISOPosMosCmd_flg(EBCS_ConstB.DataTypeConversion3);
  }

  if (CbEBCS_BMSABMSISONegMosCmdOvrSwt_flg) {
    set_GbEBCS_BMSABMSISONegMosCmd_flg(CbEBCS_BMSABMSISONegMosCmdOvr_flg);
  } else {
    set_GbEBCS_BMSABMSISONegMosCmd_flg(EBCS_ConstB.DataTypeConversion2);
  }

  if (CbEBCS_BMSABMSCntctrReqOvrSwt_flg) {
    set_GeEBCS_BMSABMSCntctrReq_enum(CeEBCS_BMSABMSCntctrReqOvr_enum);
  } else {
    set_GeEBCS_BMSABMSCntctrReq_enum(get_GeEBIM_BMSAHVCtrCmd_enum());
  }

  if (CbEBCS_BMSABattReqEOLISOdeteOvrSwt_flg) {
    set_GbEBCS_BMSABattReqEOLISOdete_flg(CbEBCS_BMSABattReqEOLISOdeteOvr_flg);
  } else {
    set_GbEBCS_BMSABattReqEOLISOdete_flg(EBCS_ConstB.DataTypeConversion9);
  }

  if (CbEBCS_BMSBEMSRechargeCntctrReqOvrSwt_flg) {
    set_GeEBCS_BMSBEMSRechargeCntctrReq_enum
      (CeEBCS_BMSBEMSRechargeCntctrReqOvr_enum);
  } else {
    set_GeEBCS_BMSBEMSRechargeCntctrReq_enum((uint8_T)
      ((get_GbEACT_ReChrgBPosCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE)) &&
       (get_GbEACT_ReChrgBNegCtrCmd_flg() == ((boolean_T)ASWTYPE_TRUE))));
  }

  if (CbEBCS_BMSBBMSIsoDetAllowOvrSwt_flg) {
    set_GbEBCS_BMSBBMSIsoDetAllow_flg(CbEBCS_BMSBBMSIsoDetAllowOvr_flg);
  } else {
    set_GbEBCS_BMSBBMSIsoDetAllow_flg(get_GbEISO_BMS2StartISOEn_flg());
  }

  if (CbEBCS_BMSBBMSISOPosMosCmdOvrSwt_flg) {
    set_GbEBCS_BMSBBMSISOPosMosCmd_flg(CbEBCS_BMSBBMSISOPosMosCmdOvr_flg);
  } else {
    set_GbEBCS_BMSBBMSISOPosMosCmd_flg(EBCS_ConstB.DataTypeConversion3_b);
  }

  if (CbEBCS_BMSBBMSISONegMosCmdOvrSwt_flg) {
    set_GbEBCS_BMSBBMSISONegMosCmd_flg(CbEBCS_BMSBBMSISONegMosCmdOvr_flg);
  } else {
    set_GbEBCS_BMSBBMSISONegMosCmd_flg(EBCS_ConstB.DataTypeConversion2_m);
  }

  if (CbEBCS_BMSBBMSCntctrReqOvrSwt_flg) {
    set_GeEBCS_BMSBBMSCntctrReq_enum(CeEBCS_BMSBBMSCntctrReqOvr_enum);
  } else {
    set_GeEBCS_BMSBBMSCntctrReq_enum(get_GeEBIM_BMSBHVCtrCmd_enum());
  }

  if (CbEBCS_BMSBBattReqEOLISOdeteOvrSwt_flg) {
    set_GbEBCS_BMSBBattReqEOLISOdete_flg(CbEBCS_BMSBBattReqEOLISOdeteOvr_flg);
  } else {
    set_GbEBCS_BMSBBattReqEOLISOdete_flg(EBCS_ConstB.DataTypeConversion10);
  }
}

/* Model initialize function */
void EBCS_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
