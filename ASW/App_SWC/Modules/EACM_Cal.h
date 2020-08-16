/*
 * File: EACM_Cal.h
 *
 * Code generated for Simulink model 'EACM'.
 *
 * Company                        : DP
 * Author                         : xudong.liang
 * Model version                  : 'EMS-M2.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jul 20 18:44:55 2020
 */

#ifndef RTW_HEADER_EACM_Cal_h_
#define RTW_HEADER_EACM_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEACM_AGunStartCheckForCardOvrSwt_flg;
extern volatile boolean_T CbEACM_AGunStartCheckForCardOvr_flg;/* Aǹ��CCV���ͼ�Ȩ����
                                                                 0:��; 1:��ʼ */
extern volatile boolean_T CbEACM_AGunUserStopForCardOvrSwt_flg;
extern volatile boolean_T CbEACM_AGunUserStopForCardOvr_flg;/* Aǹ��CCV����ֹͣ��Ȩ����
                                                               0:��; 1:��ʼ */
extern volatile boolean_T CbEACM_BGunStartCheckForCardOvrSwt_flg;
extern volatile boolean_T CbEACM_BGunStartCheckForCardOvr_flg;/* Bǹ��CCV���ͼ�Ȩ����
                                                                 0:��; 1:��ʼ */
extern volatile boolean_T CbEACM_BGunUserStopForCardOvrSwt_flg;
extern volatile boolean_T CbEACM_BGunUserStopForCardOvr_flg;/* Bǹ��CCV����ֹͣ��Ȩ����
                                                               0:��; 1:��ʼ */
extern volatile boolean_T CbEACM_CCU1MCVCardTypeOvrSwt_flg;
extern volatile boolean_T CbEACM_CCU1TFDAuthReqOvrSwt_flg;
extern volatile boolean_T CbEACM_CCU1TFDAuthReqOvr_flg;/* ��TBOX���ͼ�Ȩ���� */
extern volatile boolean_T CbEACM_CCU2MCVCardTypeOvrSwt_flg;
extern volatile boolean_T CbEACM_CCU2TFDAuthReqOvrSwt_flg;
extern volatile boolean_T CbEACM_CCU2TFDAuthReqOvr_flg;/* ��TBOX���ͼ�Ȩ���� */
extern volatile boolean_T CbEACM_ChrgFeeOvrSwt_flg;
extern volatile boolean_T CbEACM_LeftCheckSuccessOvrSwt_flg;
extern volatile boolean_T CbEACM_LeftCheckSuccessOvr_flg;/* ��CHM���ͳ������ */
extern volatile boolean_T CbEACM_LeftStaRFIDCardUIDOvrSwt_flg;
extern volatile boolean_T CbEACM_LeftStopChargeSuccessOvrSwt_flg;
extern volatile boolean_T CbEACM_LeftStopChargeSuccessOvr_flg;/* ��CHM����ֹͣ������� */
extern volatile boolean_T CbEACM_PrePaymentOvrSwt_flg;
extern volatile boolean_T CbEACM_RightCheckSuccessOvrSwt_flg;
extern volatile boolean_T CbEACM_RightCheckSuccessOvr_flg;/* ��CHM���ͳ������ */
extern volatile boolean_T CbEACM_RightStaRFIDCardUIDOvrSwt_flg;
extern volatile boolean_T CbEACM_RightStopChargeSuccessOvrSwt_flg;
extern volatile boolean_T CbEACM_RightStopChargeSuccessOvr_flg;/* ��CHM����ֹͣ������� */
extern volatile real32_T CcEACM_ChrgFeeOvr_rmb;/* ���� */
extern volatile uint8_T CcEACM_LeftStaRFIDCardUIDOvr_numb;/* ��ǹRFID��UID�� */
extern volatile real32_T CcEACM_PrePaymentOvr_rmb;/* Ԥ�۷� */
extern volatile uint8_T CcEACM_RightStaRFIDCardUIDOvr_numb;/* ��ǹRFID��UID�� */
extern volatile uint8_T CeEACM_CCU1MCVCardTypeOvr_enum;/* ��ǹ��Ȩ��ʽ
                                                          0:��; 1:���ÿ�;
                                                          2:RFID��;  */
extern volatile uint8_T CeEACM_CCU2MCVCardTypeOvr_enum;/* ��ǹ��Ȩ��ʽ
                                                          0:��; 1:���ÿ�;
                                                          2:RFID��;  */

#endif                                 /* RTW_HEADER_EACM_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
