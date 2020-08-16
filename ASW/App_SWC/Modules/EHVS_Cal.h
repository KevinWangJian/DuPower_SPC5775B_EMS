/*
 * File: EHVS_Cal.h
 *
 * Code generated for Simulink model 'EHVS'.
 *
 * Company                        : DP
 * Author                         : wxf
 * Model version                  : 'ES50A-M1.02-C1.02'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu May 28 09:28:01 2020
 */

#ifndef RTW_HEADER_EHVS_Cal_h_
#define RTW_HEADER_EHVS_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEHVS_HVSStateOvrSwt_flg;/* GeEHVS_HVSState_enum对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_PACKAToHVSNCtrOvrSwt_flg;/* GbEHVS_PACKAToHVSNCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_PACKAToHVSNCtrOvr_flg;/* GbEHVS_PACKAToHVSNCtr_flg对应的OverWrite变量 */
extern volatile boolean_T CbEHVS_PACKAToHVSPCtrOvrSwt_flg;/* GbEHVS_PACKAToHVSPCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_PACKAToHVSPCtrOvr_flg;/* GbEHVS_PACKAToHVSPCtr_flg对应的OverWrite变量 */
extern volatile boolean_T CbEHVS_PACKBToHVSNCtrOvrSwt_flg;/* GbEHVS_PACKBToHVSNCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_PACKBToHVSNCtrOvr_flg;/* GbEHVS_PACKBToHVSNCtr_flg对应的OverWrite变量 */
extern volatile boolean_T CbEHVS_PACKBToHVSPCtrOvrSwt_flg;/* GbEHVS_PACKBToHVSPCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_PACKBToHVSPCtrOvr_flg;/* GbEHVS_PACKBToHVSPCtr_flg对应的OverWrite变量 */
extern volatile boolean_T CbEHVS_SmallDCDCPowerCtrOvrSwt_flg;/* GbEHVS_SmallDCDCPowerCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_SmallDCDCPowerCtrOvr_flg;/* GbEHVS_SmallDCDCPowerCtr_flg对应的OverWrite变量 */
extern volatile boolean_T CbEHVS_TMSPowerCtrOvrSwt_flg;/* GbEHVS_TMSPowerCtr_flg对应的OverWrite标志 */
extern volatile boolean_T CbEHVS_TMSPowerCtrOvr_flg;/* GbEHVS_TMSPowerCtr_flg对应的OverWrite变量 */
extern volatile uint16_T CcEHVS_LineAChangeStateDebTime_ms;/* LineA状态下支路A跳转准备完成标定时间 */
extern volatile uint16_T CcEHVS_LineBChangeStateDebTime_ms;/* LineB状态下支路B跳转准备完成标定时间 */
extern volatile real32_T CcEHVS_PackAVoltFactor_numb;/* PackA电压标定系数 */
extern volatile real32_T CcEHVS_PackBVoltFactor_numb;/* PackB电压标定系数 */
extern volatile real32_T CcEHVS_PackSOC20Percent_pct;/* 20%SOC值 */
extern volatile real32_T CcEHVS_PackSOC45Percent_pct;/* 45%SOC值 */
extern volatile real32_T CcEHVS_PackSOCLowLimit_pct;/* PackSOC下限 */
extern volatile uint16_T CcEHVS_RelayCtrOFFDebTime_ms;/* TMS控制指令为FALSE标定时间 */
extern volatile uint8_T CeEHVS_HVSStateOvr_enum;/* GeEHVS_HVSState_enum对应的OverWrite变量 */

#endif                                 /* RTW_HEADER_EHVS_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
