/*
 * File: ETCR_Cal.c
 *
 * Code generated for Simulink model 'ETCR'.
 *
 * Company                        : DP
 * Author                         : admin
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 13 19:37:39 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ETCR_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbETCR_0x1802F102UpdataOvrSwt_flg = 0;
volatile boolean_T CbETCR_0x1802F102UpdataOvr_flg = 0;
volatile boolean_T CbETCR_LeftServeStaChgCmdOvrSwt_flg = 0;
volatile boolean_T CbETCR_LeftServeStaChgCmdOvr_flg = 0;/* ��ǹ������ */
volatile boolean_T CbETCR_LeftServeStpChgCmdOvrSwt_flg = 0;
volatile boolean_T CbETCR_LeftServeStpChgCmdOvr_flg = 0;/* ��ǹֹͣ��� */
volatile boolean_T CbETCR_RightServeStaChgCmdOvrSwt_flg = 0;
volatile boolean_T CbETCR_RightServeStaChgCmdOvr_flg = 0;/* ��ǹ������ */
volatile boolean_T CbETCR_RightServeStpChgCmdOvrSwt_flg = 0;
volatile boolean_T CbETCR_RightServeStpChgCmdOvr_flg = 0;/* ��ǹֹͣ��� */
volatile boolean_T CbETCR_TBOXCCU1OcppAvailabilityEnumOvrSwt_flg = 0;
volatile boolean_T CbETCR_TBOXCCU2OcppAvailabilityEnumOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDAuthResultsOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerDayOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerHourOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerInvalidOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerMinuteOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerMonthOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerSecondOvrSwt_flg = 0;
volatile boolean_T CbETCR_TFDTBOXTimerYearOvrSwt_flg = 0;
volatile uint8_T CcETCR_TFDTBOXTimerDayOvr_numb = 0U;/* TBOX�·�ʱ�� �� */
volatile uint8_T CcETCR_TFDTBOXTimerHourOvr_numb = 0U;/* TBOX�·�ʱ�� ʱ */
volatile boolean_T CcETCR_TFDTBOXTimerInvalidOvr_flg = 0;/* TBOX�·�ʱ����Ч�� */
volatile uint8_T CcETCR_TFDTBOXTimerMinuteOvr_numb = 0U;/* TBOX�·�ʱ�� �� */
volatile uint8_T CcETCR_TFDTBOXTimerMonthOvr_numb = 0U;/* TBOX�·�ʱ�� �� */
volatile uint8_T CcETCR_TFDTBOXTimerSecondOvr_numb = 0U;/* TBOX�·�ʱ�� �� */
volatile uint16_T CcETCR_TFDTBOXTimerYearOvr_numb = 0U;/* TBOX�·�ʱ�� �� */
volatile uint8_T CeETCR_TBOXCCU1OcppAvailabilityEnumOvr_enum = 0U;/* �ƶ��·�CCU1����״̬ */
volatile uint8_T CeETCR_TBOXCCU2OcppAvailabilityEnumOvr_enum = 0U;/* �ƶ��·�CCU2����״̬ */
volatile uint8_T CeETCR_TFDAuthResultsOvr_enum = 0U;/* ��Ȩ��� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
