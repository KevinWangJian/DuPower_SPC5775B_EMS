/*
 * File: EBIM_Cal.c
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EBIM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEBIM_BMSAHVCtrCmdOvrSwt_flg = 0;/* BMS A�̵����պ�ָ���overwrite�궨���� */
volatile boolean_T CbEBIM_BMSBHVCtrCmdOvrSwt_flg = 0;/* BMS B�̵����պ�ָ���overwrite�궨���� */
volatile boolean_T CbEBIM_PackAAllowedReChrgOvrSwt_flg = 0;/* PackA������
                                                              0����������
                                                              1�������� */
volatile boolean_T CbEBIM_PackAAllowedReChrgOvr_flg = 0;/* PackA������
                                                           0����������
                                                           1�������� */
volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvrSwt_flg = 0;/* PackA������ŵ��־
                                                                    0��Reserve
                                                                    1��������ŵ� */
volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvr_flg = 0;/* PackA������ŵ��־
                                                                 0��Reserve
                                                                 1��������ŵ� */
volatile boolean_T CbEBIM_PackAOutCurrReqOvrSwt_flg = 0;/* PackA����������� */
volatile boolean_T CbEBIM_PackAOutVoltReqOvrSwt_flg = 0;/* PackA���������ѹ */
volatile boolean_T CbEBIM_PackBAllowedReChrgOvrSwt_flg = 0;/* PackA������
                                                              0����������
                                                              1�������� */
volatile boolean_T CbEBIM_PackBAllowedReChrgOvr_flg = 0;/* PackA������
                                                           0����������
                                                           1�������� */
volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvrSwt_flg = 0;/* PackA������ŵ��־
                                                                    0��Reserve
                                                                    1��������ŵ� */
volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvr_flg = 0;/* PackA������ŵ��־
                                                                 0��Reserve
                                                                 1��������ŵ� */
volatile boolean_T CbEBIM_PackBOutCurrReqOvrSwt_flg = 0;/* PackA����������� */
volatile boolean_T CbEBIM_PackBOutVoltReqOvrSwt_flg = 0;/* PackA���������ѹ */
volatile uint8_T CcEBIM_BMSASOC10_pct = 10U;/* BIMģ��PACKAǿ���µ�SOC��ֵ */
volatile uint8_T CcEBIM_BMSBSOC10_pct = 10U;/* BIMģ��PACKBǿ���µ�SOC��ֵ */
volatile real32_T CcEBIM_PackAOutCurrReqOvr_A = 0.0F;/* PackA����������� */
volatile real32_T CcEBIM_PackAOutVoltReqOvr_V = 0.0F;/* PackA���������ѹ */
volatile real32_T CcEBIM_PackBOutCurrReqOvr_A = 0.0F;/* PackA����������� */
volatile real32_T CcEBIM_PackBOutVoltReqOvr_V = 0.0F;/* PackA���������ѹ */
volatile uint8_T CeEBIM_BMSAHVCtrCmdOvr_enum = 1U;/* BMS A�̵����պ�ָ���overwrite�궨ֵ
                                                     0:res
                                                     1:�պ�
                                                     2:�Ͽ� */
volatile uint8_T CeEBIM_BMSBHVCtrCmdOvr_enum = 1U;/* BMS B�̵����պ�ָ���overwrite�궨ֵ
                                                     0:res
                                                     1:�պ�
                                                     2:�Ͽ� */
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
