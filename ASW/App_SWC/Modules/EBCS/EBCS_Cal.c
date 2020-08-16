/*
 * File: EBCS_Cal.c
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
 
#include "rtwtypes.h"
#include "EBCS_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEBCS_BMSABMSCntctrReqOvrSwt_flg = 0;/* BMS高压接触器控制指令 */
volatile boolean_T CbEBCS_BMSABMSISONegMosCmdOvrSwt_flg = 0;/* BMS负极MOS指令 */
volatile boolean_T CbEBCS_BMSABMSISONegMosCmdOvr_flg = 0;/* BMS负极MOS指令 */
volatile boolean_T CbEBCS_BMSABMSISOPosMosCmdOvrSwt_flg = 0;/* BMS正极MOS指令 */
volatile boolean_T CbEBCS_BMSABMSISOPosMosCmdOvr_flg = 0;/* BMS正极MOS指令 */
volatile boolean_T CbEBCS_BMSABMSIsoDetAllowOvrSwt_flg = 0;/* BMS绝缘检测使能指令 */
volatile boolean_T CbEBCS_BMSABMSIsoDetAllowOvr_flg = 0;/* BMS绝缘检测使能指令 */
volatile boolean_T CbEBCS_BMSABattReqEOLISOdeteOvrSwt_flg = 0;/* 预留 */
volatile boolean_T CbEBCS_BMSABattReqEOLISOdeteOvr_flg = 0;/* 预留 */
volatile boolean_T CbEBCS_BMSAEMSRechargeCntctrReqOvrSwt_flg = 0;
volatile boolean_T CbEBCS_BMSBBMSCntctrReqOvrSwt_flg = 0;/* BMS高压接触器控制指令 */
volatile boolean_T CbEBCS_BMSBBMSISONegMosCmdOvrSwt_flg = 0;/* BMS负极MOS指令 */
volatile boolean_T CbEBCS_BMSBBMSISONegMosCmdOvr_flg = 0;/* BMS负极MOS指令 */
volatile boolean_T CbEBCS_BMSBBMSISOPosMosCmdOvrSwt_flg = 0;/* BMS正极MOS指令 */
volatile boolean_T CbEBCS_BMSBBMSISOPosMosCmdOvr_flg = 0;/* BMS正极MOS指令 */
volatile boolean_T CbEBCS_BMSBBMSIsoDetAllowOvrSwt_flg = 0;/* BMS绝缘检测使能指令 */
volatile boolean_T CbEBCS_BMSBBMSIsoDetAllowOvr_flg = 0;/* BMS绝缘检测使能指令 */
volatile boolean_T CbEBCS_BMSBBattReqEOLISOdeteOvrSwt_flg = 0;/* 预留 */
volatile boolean_T CbEBCS_BMSBBattReqEOLISOdeteOvr_flg = 0;/* 预留 */
volatile boolean_T CbEBCS_BMSBEMSRechargeCntctrReqOvrSwt_flg = 0;
volatile uint8_T CeEBCS_BMSABMSCntctrReqOvr_enum = 0U;/* BMS高压接触器控制指令 */
volatile uint8_T CeEBCS_BMSAEMSRechargeCntctrReqOvr_enum = 0U;
volatile uint8_T CeEBCS_BMSBBMSCntctrReqOvr_enum = 0U;/* BMS高压接触器控制指令 */
volatile uint8_T CeEBCS_BMSBEMSRechargeCntctrReqOvr_enum = 0U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
