/*
 * File: EACM_Var.c
 *
 * Code generated for Simulink model 'EACM'.
 *
 * Company                        : DP
 * Author                         : Administrator
 * Model version                  : 'GL48-M1.0-C1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jun 11 10:32:11 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */

#include "rtwtypes.h"
#include "EACM_types.h"

/* Exported data definition */
volatile boolean_T LbEACM_APPCCU1StartCharg_flg;
volatile boolean_T LbEACM_APPCCU1StopChargNocmd_flg;
volatile boolean_T LbEACM_APPCCU1StopCharg_flg;
volatile boolean_T LbEACM_APPCCU1SwpOvr_flg;
volatile boolean_T LbEACM_APPCCU2StartCharg_flg;
volatile boolean_T LbEACM_APPCCU2StopChargNocmd_flg;
volatile boolean_T LbEACM_APPCCU2StopCharg_flg;
volatile boolean_T LbEACM_APPCCU2SwpOvr_flg;
volatile boolean_T LbEACM_CCU1CancelRdCard_flg;
volatile boolean_T LbEACM_CCU2CancelRdCard_flg;
volatile boolean_T LbEACM_CrdCCU1Check_flg;
volatile boolean_T LbEACM_CrdCCU1NoUserRdCard_flg;
volatile boolean_T LbEACM_CrdCCU1NoUserStpChg_flg;
volatile boolean_T LbEACM_CrdCCU1PreAut_flg;
volatile boolean_T LbEACM_CrdCCU1StaChg_flg;
volatile boolean_T LbEACM_CrdCCU1StaRdCarOvrTime_flg;
volatile boolean_T LbEACM_CrdCCU1UserRdCard_flg;
volatile boolean_T LbEACM_CrdCCU1UserStpRdCard_flg;
volatile boolean_T LbEACM_CrdCCU2Check_flg;
volatile boolean_T LbEACM_CrdCCU2NoUserRdCard_flg;
volatile boolean_T LbEACM_CrdCCU2NoUserStpChg_flg;
volatile boolean_T LbEACM_CrdCCU2PreAut_flg;
volatile boolean_T LbEACM_CrdCCU2StaChg_flg;
volatile boolean_T LbEACM_CrdCCU2StaRdCarOvrTime_flg;
volatile boolean_T LbEACM_CrdCCU2UserRdCard_flg;
volatile boolean_T LbEACM_CrdCCU2UserStpRdCard_flg;
volatile boolean_T LbEACM_RFCCU1AfterChgNoUserRdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU1AfterChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU1AfterChgStpRdCard_flg;
volatile boolean_T LbEACM_RFCCU1AfterChgUserAuthOvrTime_flg;
volatile boolean_T LbEACM_RFCCU1AfterChgUserRdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU1AuthFail_flg;
volatile boolean_T LbEACM_RFCCU1AuthOvrTime_flg;
volatile boolean_T LbEACM_RFCCU1Check_flg;
volatile boolean_T LbEACM_RFCCU1NoUserStpChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU1NoUserStpReq_flg;
volatile boolean_T LbEACM_RFCCU1RdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU1StaChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU1StaChgStpRdCard_flg;
volatile boolean_T LbEACM_RFCCU1StpChg_flg;
volatile boolean_T LbEACM_RFCCU2AfterChgNoUserRdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU2AfterChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU2AfterChgStpRdCard_flg;
volatile boolean_T LbEACM_RFCCU2AfterChgUserAuthOvrTime_flg;
volatile boolean_T LbEACM_RFCCU2AfterChgUserRdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU2AuthFail_flg;
volatile boolean_T LbEACM_RFCCU2AuthOvrTime_flg;
volatile boolean_T LbEACM_RFCCU2Check_flg;
volatile boolean_T LbEACM_RFCCU2NoUserStpChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU2NoUserStpReq_flg;
volatile boolean_T LbEACM_RFCCU2RdCardOvrTime_flg;
volatile boolean_T LbEACM_RFCCU2StaChgRdCard_flg;
volatile boolean_T LbEACM_RFCCU2StaChgStpRdCard_flg;
volatile boolean_T LbEACM_RFCCU2StpChg_flg;
volatile boolean_T LbEACM_VIPCCU1StartCharg_flg;
volatile boolean_T LbEACM_VIPCCU1StopChg_flg;
volatile boolean_T LbEACM_VIPCCU2StopChg_flg;
volatile boolean_T LbEACM_VIPLeftCheckSuccess_flg;
volatile boolean_T LbEACM_VIPLeftStopChargeSuccess_flg;
volatile boolean_T LbEACM_VIPRightCheckSuccess_flg;
volatile boolean_T LbEACM_VIPRightStopChargeSuccess_flg;
volatile uint8_T LeEACM_CCU1CCVChargeTypeStore_enum;
volatile uint8_T LeEACM_CCU2CCVChargeTypeStore_enum;

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
