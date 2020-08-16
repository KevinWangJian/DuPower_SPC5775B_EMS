/*
 * File: ECTC_Cal.h
 *
 * Code generated for Simulink model 'ECTC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 17:33:01 2020
 */

#ifndef RTW_HEADER_ECTC_Cal_h_
#define RTW_HEADER_ECTC_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbECTC_ACDCAOutCurrTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ACDCAOutCurrTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_ACDCBOutCurrTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ACDCBOutCurrTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_BCChrgCtrAModeOvrSwt_flg;
extern volatile boolean_T CbECTC_BCChrgCtrBModeOvrSwt_flg;
extern volatile boolean_T CbECTC_BCChrgNCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_BCChrgNCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_BCChrgPCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_BCChrgPCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_BCChrgPreChrgTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_BCChrgPreChrgTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgAANDBCChrgANDCChrgBCircuitFltOvr_flg;
extern volatile boolean_T CbECTC_CChrgANCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgANCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_CChrgAPCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgAPCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_CChrgAPreChrgTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgAPreChrgTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_CChrgBNCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgBNCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_CChrgBPCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgBPCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_CChrgBPreChrgTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgBPreChrgTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_CChrgCtrAModeOvrSwt_flg;
extern volatile boolean_T CbECTC_CChrgCtrBModeOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgAANDBCChrgCircuitFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgAANDBCChrgCircuitFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgAANDCChrgACircuitFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgAANDCChrgACircuitFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgANCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgANCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_ReChrgAPCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgAPCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_ReChrgAPreChrgTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgAPreChrgTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgBANDBCChrgCircuitFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgBANDBCChrgCircuitFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgBANDCChrgBCircuitFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgBANDCChrgBCircuitFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgBNCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgBNCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_ReChrgBPCtrCmdOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgBPCtrCmdOvr_flg;
extern volatile boolean_T CbECTC_ReChrgBPreChrgTimeOutFltOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgBPreChrgTimeOutFltOvr_flg;
extern volatile boolean_T CbECTC_ReChrgCtrAModeOvrSwt_flg;
extern volatile boolean_T CbECTC_ReChrgCtrBModeOvrSwt_flg;
extern volatile uint8_T CcECTC_ACDCANDDCDCVoltDif_V;
extern volatile uint8_T CcECTC_ACDCANDPackVoltDif_V;
extern volatile uint16_T CcECTC_ACDCMinVolt_V;
extern volatile uint16_T CcECTC_ACDCOutCurrTimeOutDebT_ms;/* 3000ms */
extern volatile uint8_T CcECTC_ACDCTimeOutCurr_A;
extern volatile uint16_T CcECTC_BCChrgCtrCmdDebT_ms;/* 300ms */
extern volatile uint16_T CcECTC_CChrgCtrCmdDebT_ms;/* 300ms */
extern volatile uint8_T CcECTC_DebounceTime100_ms;/* 100ms */
extern volatile uint16_T CcECTC_OfflineToPrechrgDelayT_ms;/* 300ms */
extern volatile uint16_T CcECTC_PreChrgTimeOutDebT_ms;/* 300ms */
extern volatile uint16_T CcECTC_PreshutToShutdownDebT_ms;/* 300ms */
extern volatile uint16_T CcECTC_ReChrgCtrCmdDebT_ms;/* 300ms */
extern volatile uint16_T CcECTC_ShutdownToOfflineDelayT_ms;/* 300ms */
extern volatile uint16_T CcECTC_SysMinVolt_V;
extern volatile uint8_T CeECTC_BCChrgCtrAModeOvr_enum;
extern volatile uint8_T CeECTC_BCChrgCtrBModeOvr_enum;
extern volatile uint8_T CeECTC_CChrgCtrAModeOvr_enum;
extern volatile uint8_T CeECTC_CChrgCtrBModeOvr_enum;
extern volatile uint8_T CeECTC_ReChrgCtrAModeOvr_enum;
extern volatile uint8_T CeECTC_ReChrgCtrBModeOvr_enum;

#endif                                 /* RTW_HEADER_ECTC_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
