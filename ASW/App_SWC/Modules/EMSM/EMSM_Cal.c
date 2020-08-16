/*
 * File: EMSM_Cal.c
 *
 * Code generated for Simulink model 'EMSM'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 14:32:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "EMSM_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbEMSM_12VSelfCheckSuccessOvrSwt_flg = 0;/* 12V�Լ�ɹ���־λ
                                                               0��δ�ɹ�;1���ɹ� */
volatile boolean_T CbEMSM_12VSelfCheckSuccessOvr_flg = 0;/* 12V�Լ�ɹ���־λ
                                                            0��δ�ɹ�;1���ɹ� */
volatile boolean_T CbEMSM_24VSelfCheckSuccessOvrSwt_flg = 0;/* �Լ���Ƽ̵���ָ��
                                                               0���̵����Ͽ�;1���̵����պ� */
volatile boolean_T CbEMSM_24VSelfCheckSuccessOvr_flg = 0;/* �Լ���Ƽ̵���ָ��
                                                            0���̵����Ͽ�;1���̵����պ� */
volatile boolean_T CbEMSM_ECUCheckSuccessOvrSwt_flg = 0;/* AFC��ʼ���ɹ���־λ
                                                           0:δ�ɹ�; 1:�ɹ� */
volatile boolean_T CbEMSM_ECUCheckSuccessOvr_flg = 0;/* AFC��ʼ���ɹ���־λ
                                                        0:δ�ɹ�; 1:�ɹ� */
volatile boolean_T CbEMSM_EMSCheckSuccessOvrSwt_flg = 0;/* EMS��ʼ���ɹ���־λ
                                                           0:δ�ɹ�; 1:�ɹ� */
volatile boolean_T CbEMSM_EMSCheckSuccessOvr_flg = 0;/* EMS��ʼ���ɹ���־λ
                                                        0:δ�ɹ�; 1:�ɹ� */
volatile boolean_T CbEMSM_SafeCheckSuccessOvrSwt_flg = 0;/* ��ȫ�ż��ɹ���־λ
                                                            0��δ�ɹ�;1���ɹ� */
volatile boolean_T CbEMSM_SafeCheckSuccessOvr_flg = 0;/* ��ȫ�ż��ɹ���־λ
                                                         0��δ�ɹ�;1���ɹ� */
volatile boolean_T CbEMSM_SelfCheckCtrCmdOvrSwt_flg = 0;/* �Լ���Ƽ̵���ָ��
                                                           0���̵����Ͽ�;1���̵����պ� */
volatile boolean_T CbEMSM_SelfCheckCtrCmdOvr_flg = 0;/* �Լ���Ƽ̵���ָ��
                                                        0���̵����Ͽ�;1���̵����պ� */
volatile boolean_T CbEMSM_SleepModeEnableOvrSwt_flg = 0;/* ��������ģʽ��־λ
                                                           0��δ����;1������ */
volatile boolean_T CbEMSM_SleepModeEnableOvr_flg = 0;/* ��������ģʽ��־λ
                                                        0��δ����;1������ */
volatile uint16_T CcEMSM_DelayTime2000_ms = 2000U;
volatile uint32_T CcEMSM_DelayTime30_min = 1800000U;
volatile uint32_T CcEMSM_DelayTime5000_ms = 5000U;
volatile uint32_T CcEMSM_DelayTime60000_ms = 60000U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
