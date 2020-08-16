/*
 * File: ETCR_Cal.h
 *
 * Code generated for Simulink model 'ETCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:37:39 2020
 */

#ifndef RTW_HEADER_ETCR_Cal_h_
#define RTW_HEADER_ETCR_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbETCR_0x1802F102UpdataOvrSwt_flg;
extern volatile boolean_T CbETCR_0x1802F102UpdataOvr_flg;
extern volatile boolean_T CbETCR_LeftServeStaChgCmdOvrSwt_flg;
extern volatile boolean_T CbETCR_LeftServeStaChgCmdOvr_flg;/* 左枪允许充电 */
extern volatile boolean_T CbETCR_LeftServeStpChgCmdOvrSwt_flg;
extern volatile boolean_T CbETCR_LeftServeStpChgCmdOvr_flg;/* 左枪停止充电 */
extern volatile boolean_T CbETCR_RightServeStaChgCmdOvrSwt_flg;
extern volatile boolean_T CbETCR_RightServeStaChgCmdOvr_flg;/* 右枪允许充电 */
extern volatile boolean_T CbETCR_RightServeStpChgCmdOvrSwt_flg;
extern volatile boolean_T CbETCR_RightServeStpChgCmdOvr_flg;/* 右枪停止充电 */
extern volatile boolean_T CbETCR_TBOXCCU1OcppAvailabilityEnumOvrSwt_flg;
extern volatile boolean_T CbETCR_TBOXCCU2OcppAvailabilityEnumOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDAuthResultsOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerDayOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerHourOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerInvalidOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerMinuteOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerMonthOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerSecondOvrSwt_flg;
extern volatile boolean_T CbETCR_TFDTBOXTimerYearOvrSwt_flg;
extern volatile uint8_T CcETCR_TFDTBOXTimerDayOvr_numb;/* TBOX下发时间 日 */
extern volatile uint8_T CcETCR_TFDTBOXTimerHourOvr_numb;/* TBOX下发时间 时 */
extern volatile boolean_T CcETCR_TFDTBOXTimerInvalidOvr_flg;/* TBOX下发时间有效性 */
extern volatile uint8_T CcETCR_TFDTBOXTimerMinuteOvr_numb;/* TBOX下发时间 分 */
extern volatile uint8_T CcETCR_TFDTBOXTimerMonthOvr_numb;/* TBOX下发时间 月 */
extern volatile uint8_T CcETCR_TFDTBOXTimerSecondOvr_numb;/* TBOX下发时间 秒 */
extern volatile uint16_T CcETCR_TFDTBOXTimerYearOvr_numb;/* TBOX下发时间 年 */
extern volatile uint8_T CeETCR_TBOXCCU1OcppAvailabilityEnumOvr_enum;/* 云端下发CCU1可用状态 */
extern volatile uint8_T CeETCR_TBOXCCU2OcppAvailabilityEnumOvr_enum;/* 云端下发CCU2可用状态 */
extern volatile uint8_T CeETCR_TFDAuthResultsOvr_enum;/* 鉴权结果 */

#endif                                 /* RTW_HEADER_ETCR_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
