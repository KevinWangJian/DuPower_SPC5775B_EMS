/*
 * File: EACC_Cal.h
 *
 * Code generated for Simulink model 'EACC'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jul 07 13:26:06 2020
 */

#ifndef RTW_HEADER_EACC_Cal_h_
#define RTW_HEADER_EACC_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile real32_T CaEACC_ACDCATempPwrTable_kw[7];/* Pwr-Table */
extern volatile real32_T CaEACC_ACDCAWaterTemp_C[7];/* Temp-Table */
extern volatile real32_T CaEACC_ACDCBTempPwrTable_kw[7];/* Pwr-Table */
extern volatile real32_T CaEACC_ACDCBWaterTemp_C[7];/* Temp-Table */
extern volatile boolean_T CbEACC_ACDCAOutCurrReqOvrSwt_flg;/* GcEACC_ACDCAOutCurrReq_A应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCAOutVoltReqOvrSwt_flg;/* GcEACC_ACDCAOutVoltReq_V应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCAPwrCmdOvrSwt_flg;/* GbEACC_ACDCAPwrCmd_flg应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCAPwrCmdOvr_flg;/* GbEACC_ACDCAPwrCmd_flg对应的OverWrite值 */
extern volatile boolean_T CbEACC_ACDCARunModeOvrSwt_flg;/* GeEACC_ACDCARunMode_enum对应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCBOutCurrReqOvrSwt_flg;/* GcEACC_ACDCBOutCurrReq_A应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCBOutVoltReqOvrSwt_flg;/* GcEACC_ACDCBOutVoltReq_V应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCBPwrCmdOvrSwt_flg;/* GbEACC_ACDCBPwrCmd_flg应的OverWrite标志 */
extern volatile boolean_T CbEACC_ACDCBPwrCmdOvr_flg;/* GbEACC_ACDCBPwrCmd_flg对应的OverWrite值 */
extern volatile boolean_T CbEACC_ACDCBRunModeOvrSwt_flg;/* GeEACC_ACDCBRunMode_enum应的OverWrite标志 */
extern volatile uint8_T CcEACC_ACDCACalCurr_A;/* AC/DCA标定电流 */
extern volatile real32_T CcEACC_ACDCACurrRatio_R;/* AC/DCA标定电流系数 */
extern volatile real32_T CcEACC_ACDCAOutCurrReqOvr_A;/* GcEACC_ACDCAOutCurrReq_A对应的OverWrite值 */
extern volatile real32_T CcEACC_ACDCAOutVoltReqOvr_V;/* GcEACC_ACDCAOutVoltReq_V对应的OverWrite值 */
extern volatile uint8_T CcEACC_ACDCAPwrOffDelayT_ms;/* AC/DCA关机&#xA0;Delay时间 */
extern volatile uint8_T CcEACC_ACDCAPwrOnDelayT_ms;/* AC/DCA开机&#xA0;Delay时间 */
extern volatile uint8_T CcEACC_ACDCASum_numb;/* AC/DCA数量 */
extern volatile uint8_T CcEACC_ACDCBCalCurr_A;/* AC/DCB标定电流 */
extern volatile real32_T CcEACC_ACDCBCurrRatio_R;/* AC/DCB标定电流系数 */
extern volatile real32_T CcEACC_ACDCBOutCurrReqOvr_A;/* GcEACC_ACDCBOutCurrReq_A对应的OverWrite值 */
extern volatile real32_T CcEACC_ACDCBOutVoltReqOvr_V;/* GcEACC_ACDCBOutVoltReq_V对应的OverWrite值 */
extern volatile uint8_T CcEACC_ACDCBSum_numb;/* AC/DCB数量 */
extern volatile uint16_T CcEACC_AOffToStdbDelayT_ms;/* ACDCA工作状态offline跳standby Delay时间 */
extern volatile uint8_T CcEACC_APChrgToStdbDelayT_ms;/* ACDCA工作状态PreChrg跳standby Delay时间 */
extern volatile uint16_T CcEACC_AStdbToOffDelayT_ms;/* ACDCA工作状态standby跳offline Delay时间 */
extern volatile uint8_T CcEACC_AllowACDCAWorkFltLvl_numb;/* 允许ACDCA工作的故障等级 */
extern volatile uint8_T CcEACC_AllowACDCBWorkFltLvl_numb;/* 允许ACDCB工作的故障等级 */
extern volatile uint16_T CcEACC_BOffToStdbDelayT_ms;/* ACDCB工作状态offline跳standby Delay时间 */
extern volatile uint8_T CcEACC_BPChrgToStdbDelayT_ms;/* ACDCB工作状态PreChrg跳standby Delay时间 */
extern volatile uint16_T CcEACC_BStdbToOffDelayT_ms;/* ACDCB工作状态standby跳offline Delay时间 */
extern volatile real32_T CcEACC_Ratio1000_R;
extern volatile uint8_T CeEACC_ACDCARunModeOvr_enum;/* GeEACC_ACDCARunMode_enum对应的OverWrite值 */
extern volatile uint8_T CeEACC_ACDCBRunModeOvr_enum;/* GeEACC_ACDCBRunMode_enum对应的OverWrite值 */

#endif                                 /* RTW_HEADER_EACC_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
