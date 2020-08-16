/*
 * File: ECTC_Cal.c
 *
 * Code generated for Simulink model 'ECTC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 17:33:01 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECTC_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECTC_ACDCAOutCurrTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ACDCAOutCurrTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_ACDCBOutCurrTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ACDCBOutCurrTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_BCChrgCtrAModeOvrSwt_flg = 0;
volatile boolean_T CbECTC_BCChrgCtrBModeOvrSwt_flg = 0;
volatile boolean_T CbECTC_BCChrgNCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_BCChrgNCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_BCChrgPCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_BCChrgPCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_BCChrgPreChrgTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_BCChrgPreChrgTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvr_flg = 0;
volatile boolean_T CbECTC_CChrgANCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgANCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_CChrgAPCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgAPCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_CChrgAPreChrgTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgAPreChrgTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_CChrgBNCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgBNCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_CChrgBPCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgBPCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_CChrgBPreChrgTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgBPreChrgTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_CChrgCtrAModeOvrSwt_flg = 0;
volatile boolean_T CbECTC_CChrgCtrBModeOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgAANDBCChrgCircuitFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgAANDBCChrgCircuitFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgAANDCChrgACircuitFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgAANDCChrgACircuitFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgANCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgANCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgAPCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgAPCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgAPreChrgTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgAPreChrgTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgBANDBCChrgCircuitFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgBANDBCChrgCircuitFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgBANDCChrgBCircuitFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgBANDCChrgBCircuitFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgBNCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgBNCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgBPCtrCmdOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgBPCtrCmdOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgBPreChrgTimeOutFltOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgBPreChrgTimeOutFltOvr_flg = 0;
volatile boolean_T CbECTC_ReChrgCtrAModeOvrSwt_flg = 0;
volatile boolean_T CbECTC_ReChrgCtrBModeOvrSwt_flg = 0;
volatile uint8_T CcECTC_ACDCANDDCDCVoltDif_V = 30U;
volatile uint8_T CcECTC_ACDCANDPackVoltDif_V = 30U;
volatile uint16_T CcECTC_ACDCMinVolt_V = 200U;
volatile uint16_T CcECTC_ACDCOutCurrTimeOutDebT_ms = 3000U;/* 3000ms */
volatile uint8_T CcECTC_ACDCTimeOutCurr_A = 5U;
volatile uint16_T CcECTC_BCChrgCtrCmdDebT_ms = 300U;/* 300ms */
volatile uint16_T CcECTC_CChrgCtrCmdDebT_ms = 300U;/* 300ms */
volatile uint8_T CcECTC_DebounceTime100_ms = 100U;/* 100ms */
volatile uint16_T CcECTC_OfflineToPrechrgDelayT_ms = 300U;/* 300ms */
volatile uint16_T CcECTC_PreChrgTimeOutDebT_ms = 10000U;/* 300ms */
volatile uint16_T CcECTC_PreshutToShutdownDebT_ms = 3000U;/* 300ms */
volatile uint16_T CcECTC_ReChrgCtrCmdDebT_ms = 300U;/* 300ms */
volatile uint16_T CcECTC_ShutdownToOfflineDelayT_ms = 100U;/* 300ms */
volatile uint16_T CcECTC_SysMinVolt_V = 300U;
volatile uint8_T CeECTC_BCChrgCtrAModeOvr_enum = 0U;
volatile uint8_T CeECTC_BCChrgCtrBModeOvr_enum = 0U;
volatile uint8_T CeECTC_CChrgCtrAModeOvr_enum = 0U;
volatile uint8_T CeECTC_CChrgCtrBModeOvr_enum = 0U;
volatile uint8_T CeECTC_ReChrgCtrAModeOvr_enum = 0U;
volatile uint8_T CeECTC_ReChrgCtrBModeOvr_enum = 0U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
