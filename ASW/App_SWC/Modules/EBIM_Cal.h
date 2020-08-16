/*
 * File: EBIM_Cal.h
 *
 * Code generated for Simulink model 'EBIM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EV31A-M1.07'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Thu Jul 16 13:05:13 2020
 */

#ifndef RTW_HEADER_EBIM_Cal_h_
#define RTW_HEADER_EBIM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEBIM_BMSAHVCtrCmdOvrSwt_flg;/* BMS A�̵����պ�ָ���overwrite�궨���� */
extern volatile boolean_T CbEBIM_BMSBHVCtrCmdOvrSwt_flg;/* BMS B�̵����պ�ָ���overwrite�궨���� */
extern volatile boolean_T CbEBIM_PackAAllowedReChrgOvrSwt_flg;/* PackA������
                                                                 0����������
                                                                 1�������� */
extern volatile boolean_T CbEBIM_PackAAllowedReChrgOvr_flg;/* PackA������
                                                              0����������
                                                              1�������� */
extern volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvrSwt_flg;/* PackA������ŵ��־
                                                                      0��Reserve
                                                                      1��������ŵ� */
extern volatile boolean_T CbEBIM_PackANotAllowedDisChargeOvr_flg;/* PackA������ŵ��־
                                                                    0��Reserve
                                                                    1��������ŵ� */
extern volatile boolean_T CbEBIM_PackAOutCurrReqOvrSwt_flg;/* PackA����������� */
extern volatile boolean_T CbEBIM_PackAOutVoltReqOvrSwt_flg;/* PackA���������ѹ */
extern volatile boolean_T CbEBIM_PackBAllowedReChrgOvrSwt_flg;/* PackA������
                                                                 0����������
                                                                 1�������� */
extern volatile boolean_T CbEBIM_PackBAllowedReChrgOvr_flg;/* PackA������
                                                              0����������
                                                              1�������� */
extern volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvrSwt_flg;/* PackA������ŵ��־
                                                                      0��Reserve
                                                                      1��������ŵ� */
extern volatile boolean_T CbEBIM_PackBNotAllowedDisChargeOvr_flg;/* PackA������ŵ��־
                                                                    0��Reserve
                                                                    1��������ŵ� */
extern volatile boolean_T CbEBIM_PackBOutCurrReqOvrSwt_flg;/* PackA����������� */
extern volatile boolean_T CbEBIM_PackBOutVoltReqOvrSwt_flg;/* PackA���������ѹ */
extern volatile uint8_T CcEBIM_BMSASOC10_pct;/* BIMģ��PACKAǿ���µ�SOC��ֵ */
extern volatile uint8_T CcEBIM_BMSBSOC10_pct;/* BIMģ��PACKBǿ���µ�SOC��ֵ */
extern volatile real32_T CcEBIM_PackAOutCurrReqOvr_A;/* PackA����������� */
extern volatile real32_T CcEBIM_PackAOutVoltReqOvr_V;/* PackA���������ѹ */
extern volatile real32_T CcEBIM_PackBOutCurrReqOvr_A;/* PackA����������� */
extern volatile real32_T CcEBIM_PackBOutVoltReqOvr_V;/* PackA���������ѹ */
extern volatile uint8_T CeEBIM_BMSAHVCtrCmdOvr_enum;/* BMS A�̵����պ�ָ���overwrite�궨ֵ
                                                       0:res
                                                       1:�պ�
                                                       2:�Ͽ� */
extern volatile uint8_T CeEBIM_BMSBHVCtrCmdOvr_enum;/* BMS B�̵����պ�ָ���overwrite�궨ֵ
                                                       0:res
                                                       1:�պ�
                                                       2:�Ͽ� */

#endif                                 /* RTW_HEADER_EBIM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
