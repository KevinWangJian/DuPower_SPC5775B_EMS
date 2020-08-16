/*
 * File: EACT_Cal.h
 *
 * Code generated for Simulink model 'EACT'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EMS-1.0'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 15 14:12:21 2020
 */

#ifndef RTW_HEADER_EACT_Cal_h_
#define RTW_HEADER_EACT_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvrSwt_flg;/* KA4����ָ�
                                                                0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_12VPyhSuplyCtrCmdOvr_flg;/* KA4����ָ�
                                                             0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ACCtrCmdOvrSwt_flg;/* �����̵�����KA2������ָ�
                                                       0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ACCtrCmdOvr_flg;/* �����̵�����KA2������ָ�
                                                    0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvrSwt_flg;/* KA1����ָ�
                                                               0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_AdvCoolFanCtrCmdOvr_flg;/* KA1����ָ�
                                                            0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_AdvPowCtrCmdOvrSwt_flg;/* KA3����ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_AdvPowCtrCmdOvr_flg;/* KA3����ָ�
                                                        0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_BCChrgNegCtrCmdOvrSwt_flg;/* BothCross�̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_BCChrgNegCtrCmdOvr_flg;/* BothCross�̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_BCChrgPosCtrCmdOvrSwt_flg;/* BothCross�̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_BCChrgPosCtrCmdOvr_flg;/* BothCross�̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgANegCtrCmdOvrSwt_flg;/* AǹACDC��Ӽ̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgANegCtrCmdOvr_flg;/* AǹACDC��Ӽ̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgAPosCtrCmdOvrSwt_flg;/* AǹACDC��Ӽ̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgAPosCtrCmdOvr_flg;/* AǹACDC��Ӽ̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgBNegCtrCmdOvrSwt_flg;/* BǹACDC��Ӽ̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgBNegCtrCmdOvr_flg;/* BǹACDC��Ӽ̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgBPosCtrCmdOvrSwt_flg;/* BǹACDC��Ӽ̵�����������ָ�
                                                              0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_CChrgBPosCtrCmdOvr_flg;/* BǹACDC��Ӽ̵�����������ָ�
                                                           0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_KA5CtrCmdOvrSwt_flg;/* KA5����ָ�
                                                        0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_KA5CtrCmdOvr_flg;/* KA5����ָ�
                                                     0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_PACKAToHVSNCtrOvrSwt_flg;/* PACKA��HVS N���̵���
                                                             0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKAToHVSNCtrOvr_flg;/* PACKA��HVS N���̵���
                                                          0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKAToHVSPCtrOvrSwt_flg;/* PACKA��HVS P���̵���
                                                             0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKAToHVSPCtrOvr_flg;/* PACKA��HVS P���̵���
                                                          0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKBToHVSNCtrOvrSwt_flg;/* PACKB��HVS N���̵���
                                                             0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKBToHVSNCtrOvr_flg;/* PACKB��HVS N���̵���
                                                          0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKBToHVSPCtrOvrSwt_flg;/* PACKB��HVS P���̵���
                                                             0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_PACKBToHVSPCtrOvr_flg;/* PACKB��HVS P���̵���
                                                          0:�Ͽ�; 1:���� */
extern volatile boolean_T CbEACT_ReChrgANegCtrCmdOvrSwt_flg;/* Aǹ���̵ܼ�����������ָ�
                                                               0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgANegCtrCmdOvr_flg;/* Aǹ���̵ܼ�����������ָ�
                                                            0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvrSwt_flg;/* Aǹ���̵ܼ�����������ָ�
                                                               0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgAPosCtrCmdOvr_flg;/* Aǹ���̵ܼ�����������ָ�
                                                            0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvrSwt_flg;/* Bǹ���̵ܼ�����������ָ�
                                                               0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgBNegCtrCmdOvr_flg;/* Bǹ���̵ܼ�����������ָ�
                                                            0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvrSwt_flg;/* Bǹ���̵ܼ�����������ָ�
                                                               0���Ͽ���1���պ� */
extern volatile boolean_T CbEACT_ReChrgBPosCtrCmdOvr_flg;/* Bǹ���̵ܼ�����������ָ�
                                                            0���Ͽ���1���պ� */
extern volatile uint16_T CcEACT_DelayTime3000_ms;
extern volatile uint32_T CcEACT_DelayTime3_min;
extern volatile uint16_T CcEACT_DelayTime50_ms;

#endif                                 /* RTW_HEADER_EACT_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
