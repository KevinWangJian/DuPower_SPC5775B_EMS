/*
 * File: EHCR.c
 *
 * Code generated for Simulink model 'EHCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 18 14:52:44 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "EHCR.h"
#include "EHCR_private.h"

/* Real-time model */
RT_MODEL_EHCR_T EHCR_M_;
RT_MODEL_EHCR_T *const EHCR_M = &EHCR_M_;

/* Output function for RootInportFunctionCallGenerator: '<Root>/RootFcnCall_InsertedFor_EHCR_10ms_at_outport_1' */
void EHCR_10ms(void)
{
  if (CbHCR_HCUWaterTmpInOvrSwt_flg) {
    set_GcEHCR_HCUWaterTmpIn_C(CcEHCR_HCUWaterTmpInOvr_C);
  } else {
    set_GcEHCR_HCUWaterTmpIn_C((real32_T)get_GcCAN1_HCUWaterTmpIn_C() - 40.0F);
  }

  if (CbEHCR_HCUWaterTmpOutOvrSwt_flg) {
    set_GcEHCR_HCUWaterTmpOut_C(CcEHCR_HCUWaterTmpOutOvr_C);
  } else {
    set_GcEHCR_HCUWaterTmpOut_C((real32_T)get_GcCAN1_HCUWaterTmpOut_C() - 40.0F);
  }

  if (CbEHCR_HCUSystemModeOvrSwt_flg) {
    set_GeEHCR_HCUSystemMode_enum(CeEHCR_HCUSystemModeOvr_enum);
  } else {
    set_GeEHCR_HCUSystemMode_enum(get_GeCAN1_HCUSystemMode_enum());
  }

  if (CbEHCR_HCUPowerReqOvrSwt_flg) {
    set_GbEHCR_HCUPowerReq_flg(CbEHCR_HCUPowerReqOvr_flg);
  } else {
    set_GbEHCR_HCUPowerReq_flg(get_GbCAN1_HCUPowerReq_flg());
  }

  if (CbEHCR_HCUCntStatOvrSwt_flg) {
    set_GbEHCR_HCUCntStat_flg(CbEHCR_HCUCntStatOvr_flg);
  } else {
    set_GbEHCR_HCUCntStat_flg(get_GbCAN1_HCUCntStat_flg());
  }

  if (CbEHCR_HCUFaultStaOvrSwt_flg) {
    set_GeEHCR_HCUFaultStat_enum(CeEHCR_HCUFaultStatOvr_enum);
  } else {
    set_GeEHCR_HCUFaultStat_enum(get_GeCAN1_HCUFaultStat_enum());
  }

  if (CbEHCR_HCUFaultSevtyStatOvrSwt_flg) {
    set_GeEHCR_HCUFaultSevtyStat_enum(CeEHCR_HCUFaultSevtyStatOvr_enum);
  } else {
    set_GeEHCR_HCUFaultSevtyStat_enum(get_GeCAN1_HCUFaultSevtyStat_enum());
  }

  if (CcEHCR_HCUPowerDemandOvrSwt_flg) {
    set_GcEHCR_HCUPowerDemand_Kw(CcEHCR_HCUPowerDemandOvr_Kw);
  } else {
    set_GcEHCR_HCUPowerDemand_Kw((real32_T)get_GcCAN1_HCUPowerDemand_Kw() * 0.1F);
  }

  if (CcEHCR_HCUEnvTempAOvrSwt_flg) {
    set_GcEHCR_HCUEnvTempA_C(CcEHCR_HCUEnvTempAOvr_C);
  } else {
    set_GcEHCR_HCUEnvTempA_C((real32_T)get_GcCAN1_HCUEnvTempA_C() - 40.0F);
  }
}

/* Model initialize function */
void EHCR_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
