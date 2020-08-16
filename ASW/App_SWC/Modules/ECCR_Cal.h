/*
 * File: ECCR_Cal.h
 *
 * Code generated for Simulink model 'ECCR'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 08 15:47:51 2020
 */

#ifndef RTW_HEADER_ECCR_Cal_h_
#define RTW_HEADER_ECCR_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbECCR_CCU1BCL1817FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCLSPN3072UReqOvrSwt_flg;/* ��ѹ���� */
extern volatile boolean_T CbECCR_CCU1BCLSPN3073IReqOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCLSPN3074ChgModeOvrSwt_flg;/* ���ģʽ */
extern volatile boolean_T CbECCR_CCU1BCP1812FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCP1813FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCPSPN2816UcellMaxPermitOvrSwt_flg;/* ���嶯����������������ѹ */
extern volatile boolean_T CbECCR_CCU1BCPSPN2817IMaxPermitOvrSwt_flg;/* ������������ */
extern volatile boolean_T CbECCR_CCU1BCPSPN2818kWhNomOvrSwt_flg;/* �������ر�������� */
extern volatile boolean_T CbECCR_CCU1BCPSPN2819UMaxPermitOvrSwt_flg;/* ����������ܵ�ѹ */
extern volatile boolean_T CbECCR_CCU1BCPSPN2820TMaxPermitOvrSwt_flg;/* ��������������¶� */
extern volatile boolean_T CbECCR_CCU1BCPSPN2821SOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCPSPN2822UOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCS1818FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3075UMeaOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3076IMeaOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3077UcellMaxGrpOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3077UcellMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3078SOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BCSSPN3079TimeRemainOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3901TimeoutSPN25600x00OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3902TimeoutSPN25600xAAOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3903TimeoutCTSCMLOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3904TimeoutCROOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3905TimeoutCCSOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3906TimeoutCSTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMSPN3907TimeoutCSDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BEMotherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BHM1811FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BHMSPN2601UbatMaxPermitOvrSwt_flg;/* ������������ߵ�ѹ�����ھ�Ե��⣩ */
extern volatile boolean_T CbECCR_CCU1BRM1814FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BRM1815FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BRMSPN2565CommVerOvrSwt_flg;/* ����ͨѶЭ��汾 */
extern volatile boolean_T CbECCR_CCU1BRMSPN2566BatTypeOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BRMSPN2567CapNomOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BRMSPN2568UNomOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BRMSPN2569BatFactoryOvrSwt_flg;/* ��������������ƣ�4λASCII�� */
extern volatile boolean_T CbECCR_CCU1BRMSPN2570PackSNOvrSwt_flg;/* ���ģ���ţ������Զ��壩 */
extern volatile boolean_T CbECCR_CCU1BSD181BFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSDSPN3601SOCFinalOvrSwt_flg;/* ��ֹ�ɵ�״̬SOC */
extern volatile boolean_T CbECCR_CCU1BSDSPN3602UcellMinOvrSwt_flg;/* �������ص�����͵�ѹ */
extern volatile boolean_T CbECCR_CCU1BSDSPN3603UcellMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSDSPN3604TMinOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSDSPN3605TMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSM181AFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3085UcellMaxIndexOvrSwt_flg;/* ��ߵ��嶯�����ص�ѹ���ڱ�� */
extern volatile boolean_T CbECCR_CCU1BSMSPN3086TMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3087TMaxIndexOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3088TMinOvrSwt_flg;/* ��Ͷ��������¶� */
extern volatile boolean_T CbECCR_CCU1BSMSPN3089TMinIndexOvrSwt_flg;/* ��Ͷ��������¶ȼ����� */
extern volatile boolean_T CbECCR_CCU1BSMSPN3090UcellWarnOvrSwt_flg;/* ���嶯�����ص�ѹ */
extern volatile boolean_T CbECCR_CCU1BSMSPN3091SOCWarnOvrSwt_flg;/* �����������غɵ�״̬SOC */
extern volatile boolean_T CbECCR_CCU1BSMSPN3092IWarnOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3093TWarnOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3094IsoStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3095OutConnectorStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSMSPN3096ChgEnableOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BST181CFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3511StopReasonCHGStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3511StopReasonSOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3511StopReasonUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3511StopReasonUcellOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultBCUcompoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultCC2OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultChgCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultHVRelayOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultIsoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultOutCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3512StopFaultTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3513StopFaultIOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1BSTSPN3513StopFaultUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCS1819FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCSSPN3081UOutOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCSSPN3082IOutOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCSSPN3083TimeChargedOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCU12VSTATEOvrSwt_flg;/* CCU22V״̬ */
extern volatile boolean_T CbECCR_CCU1CCU24VSTATEOvrSwt_flg;/* CCU24V״̬ */
extern volatile boolean_T CbECCR_CCU1CCUCARCONNECTSTATEOvrSwt_flg;/* �����Ƿ񷴽� */
extern volatile boolean_T CbECCR_CCU1CCUCC1STATEOvrSwt_flg;/* CC1״̬ */
extern volatile boolean_T CbECCR_CCU1CCUDTCFailureTypeByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUDTCHighByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUDTCLowByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUGUNTEMP1STATEOvrSwt_flg;/* ǹ�¶�2״̬ */
extern volatile boolean_T CbECCR_CCU1CCUGUNTEMP2STATEOvrSwt_flg;/* ǹ�¶�1״̬ */
extern volatile boolean_T CbECCR_CCU1CCUGUNpositionOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUHVFuseVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUHVRelayOutVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUHVRelayintVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUHwVersionOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1CCUHwVersionOvr_numb;
extern volatile boolean_T CbECCR_CCU1CCUISOCheckFinishOvrSwt_flg;/* CCU ISO���״̬ */
extern volatile uint8_T CbECCR_CCU1CCUISOCheckFinishOvr_flg;/* CCU ISO���״̬ */
extern volatile boolean_T CbECCR_CCU1CCUISONegVoltOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUISOOvrSwt_flg;/* CCU��Ե��� */
extern volatile boolean_T CbECCR_CCU1CCUISOPosVoltOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUISOSTATEOvrSwt_flg;/* CCU��Ե���״̬ */
extern volatile boolean_T CbECCR_CCU1CCUIndexOvrSwt_flg;/* CCU��� */
extern volatile boolean_T CbECCR_CCU1CCUK1K3STATEOvrSwt_flg;/* K1�̵���״̬(K3) */
extern volatile boolean_T CbECCR_CCU1CCUK2K4STATEOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUPyroswitchCMDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUSTATEOvrSwt_flg;/* CCU����״̬ */
extern volatile boolean_T CbECCR_CCU1CCUShuntCurrentOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUSwVersionOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1CCUSwVersionOvr_numb;
extern volatile boolean_T CbECCR_CCU1CCUSysStatAliveCounterOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CCUSysStatCheckSumOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1CCUSysStatCheckSumOvr_numb;
extern volatile boolean_T CbECCR_CCU1CCUTEMP1OvrSwt_flg;/* ǹ���¶Ȳɼ�1 */
extern volatile boolean_T CbECCR_CCU1CCUTEMP2OvrSwt_flg;/* ǹ���¶Ȳɼ�2 */
extern volatile boolean_T CbECCR_CCU1CEMOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3921TimeoutBRMOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3922TimeoutBCPOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3923TimeoutBROOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3924TimeoutBCSOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3925TimeoutBCLOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3926TimeoutBSTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CEMSPN3927TimeoutBSDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CHMSPN2600CommVerOvrSwt_flg;/* ׮��ͨѶЭ��汾 */
extern volatile boolean_T CbECCR_CCU1CST181DFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3521StopReasonAutoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3521StopReasonBMSStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3521StopReasonFaultOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3521StopReasonManualOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultCHGCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultDeliverOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultEmerStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultTCHGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3522StopFaultTInterOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3523StopFaultMismatchOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CSTSPN3523StopFaultUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1ChgBCLOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1ChgBCLOvr_flg;
extern volatile boolean_T CbECCR_CCU1ChgBCPOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1ChgBCPOvr_flg;
extern volatile boolean_T CbECCR_CCU1ChgBHMOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1ChgBHMOvr_flg;
extern volatile boolean_T CbECCR_CCU1ChgBSTOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU1ChgBSTOvr_flg;
extern volatile boolean_T CbECCR_CCU1CrossNegStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1CrossPosStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1DTC18AAFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1DirectNegStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1DirectPosStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1ELOCKSTATEOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1FUSE1STATEOvrSwt_flg;/* ����˿״̬ */
extern volatile boolean_T CbECCR_CCU1FaultSevtyStatOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1HV1802FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1ISO1820FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1Sample1803FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VIN1816FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum1OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum2OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum3OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum4OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum5OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum6OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNum7OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU1VINNumIndexOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCL1817FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCLSPN3072UReqOvrSwt_flg;/* ��ѹ���� */
extern volatile boolean_T CbECCR_CCU2BCLSPN3073IReqOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCLSPN3074ChgModeOvrSwt_flg;/* ���ģʽ */
extern volatile boolean_T CbECCR_CCU2BCP1812FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCP1813FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCPSPN2816UcellMaxPermitOvrSwt_flg;/* ���嶯����������������ѹ */
extern volatile boolean_T CbECCR_CCU2BCPSPN2817IMaxPermitOvrSwt_flg;/* ������������ */
extern volatile boolean_T CbECCR_CCU2BCPSPN2818kWhNomOvrSwt_flg;/* �������ر�������� */
extern volatile boolean_T CbECCR_CCU2BCPSPN2819UMaxPermitOvrSwt_flg;/* ����������ܵ�ѹ */
extern volatile boolean_T CbECCR_CCU2BCPSPN2820TMaxPermitOvrSwt_flg;/* ��������������¶� */
extern volatile boolean_T CbECCR_CCU2BCPSPN2821SOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCPSPN2822UOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCS1818FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3075UMeaOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3076IMeaOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3077UcellMaxGrpOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3077UcellMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3078SOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BCSSPN3079TimeRemainOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3901TimeoutSPN25600x00OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3902TimeoutSPN25600xAAOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3903TimeoutCTSCMLOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3904TimeoutCROOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3905TimeoutCCSOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3906TimeoutCSTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMSPN3907TimeoutCSDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BEMotherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BHM1811FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BHMSPN2601UbatMaxPermitOvrSwt_flg;/* ������������ߵ�ѹ�����ھ�Ե��⣩ */
extern volatile boolean_T CbECCR_CCU2BRM1814FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BRM1815FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BRMSPN2565CommVerOvrSwt_flg;/* ����ͨѶЭ��汾 */
extern volatile boolean_T CbECCR_CCU2BRMSPN2566BatTypeOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BRMSPN2567CapNomOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BRMSPN2568UNomOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BRMSPN2569BatFactoryOvrSwt_flg;/* ��������������ƣ�4λASCII�� */
extern volatile boolean_T CbECCR_CCU2BRMSPN2570PackSNOvrSwt_flg;/* ���ģ���ţ������Զ��壩 */
extern volatile boolean_T CbECCR_CCU2BSD181BFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSDSPN3601SOCFinalOvrSwt_flg;/* ��ֹ�ɵ�״̬SOC */
extern volatile boolean_T CbECCR_CCU2BSDSPN3602UcellMinOvrSwt_flg;/* �������ص�����͵�ѹ */
extern volatile boolean_T CbECCR_CCU2BSDSPN3603UcellMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSDSPN3604TMinOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSDSPN3605TMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSM181AFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3085UcellMaxIndexOvrSwt_flg;/* ��ߵ��嶯�����ص�ѹ���ڱ�� */
extern volatile boolean_T CbECCR_CCU2BSMSPN3086TMaxOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3087TMaxIndexOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3088TMinOvrSwt_flg;/* ��Ͷ��������¶� */
extern volatile boolean_T CbECCR_CCU2BSMSPN3089TMinIndexOvrSwt_flg;/* ��Ͷ��������¶ȼ����� */
extern volatile boolean_T CbECCR_CCU2BSMSPN3090UcellWarnOvrSwt_flg;/* ���嶯�����ص�ѹ */
extern volatile boolean_T CbECCR_CCU2BSMSPN3091SOCWarnOvrSwt_flg;/* �����������غɵ�״̬SOC */
extern volatile boolean_T CbECCR_CCU2BSMSPN3092IWarnOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3093TWarnOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3094IsoStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3095OutConnectorStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSMSPN3096ChgEnableOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BST181CFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3511StopReasonCHGStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3511StopReasonSOCOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3511StopReasonUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3511StopReasonUcellOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultBCUcompoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultCC2OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultChgCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultHVRelayOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultIsoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultOutCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3512StopFaultTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3513StopFaultIOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2BSTSPN3513StopFaultUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCS1819FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCSSPN3081UOutOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCSSPN3082IOutOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCSSPN3083TimeChargedOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCU22VSTATEOvrSwt_flg;/* CCU22V״̬ */
extern volatile boolean_T CbECCR_CCU2CCU24VSTATEOvrSwt_flg;/* CCU24V״̬ */
extern volatile boolean_T CbECCR_CCU2CCUCARCONNECTSTATEOvrSwt_flg;/* �����Ƿ񷴽� */
extern volatile boolean_T CbECCR_CCU2CCUCC1STATEOvrSwt_flg;/* CC1״̬ */
extern volatile boolean_T CbECCR_CCU2CCUDTCFailureTypeByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUDTCHighByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUDTCLowByteOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUGUNTEMP1STATEOvrSwt_flg;/* ǹ�¶�2״̬ */
extern volatile boolean_T CbECCR_CCU2CCUGUNTEMP2STATEOvrSwt_flg;/* ǹ�¶�1״̬ */
extern volatile boolean_T CbECCR_CCU2CCUGUNpositionOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUHVFuseVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUHVRelayOutVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUHVRelayintVLTGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUHwVersionOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2CCUHwVersionOvr_numb;
extern volatile boolean_T CbECCR_CCU2CCUISOCheckFinishOvrSwt_flg;/* CCU ISO���״̬ */
extern volatile uint8_T CbECCR_CCU2CCUISOCheckFinishOvr_flg;/* CCU ISO���״̬ */
extern volatile boolean_T CbECCR_CCU2CCUISONegVoltOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUISOOvrSwt_flg;/* CCU��Ե��� */
extern volatile boolean_T CbECCR_CCU2CCUISOPosVoltOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUISOSTATEOvrSwt_flg;/* CCU��Ե���״̬ */
extern volatile boolean_T CbECCR_CCU2CCUIndexOvrSwt_flg;/* CCU��� */
extern volatile boolean_T CbECCR_CCU2CCUK1K3STATEOvrSwt_flg;/* K1�̵���״̬(K3) */
extern volatile boolean_T CbECCR_CCU2CCUK2K4STATEOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUPyroswitchCMDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUSTATEOvrSwt_flg;/* CCU����״̬ */
extern volatile boolean_T CbECCR_CCU2CCUShuntCurrentOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUSwVersionOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2CCUSwVersionOvr_numb;
extern volatile boolean_T CbECCR_CCU2CCUSysStatAliveCounterOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CCUSysStatCheckSumOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2CCUSysStatCheckSumOvr_numb;
extern volatile boolean_T CbECCR_CCU2CCUTEMP1OvrSwt_flg;/* ǹ���¶Ȳɼ�1 */
extern volatile boolean_T CbECCR_CCU2CCUTEMP2OvrSwt_flg;/* ǹ���¶Ȳɼ�2 */
extern volatile boolean_T CbECCR_CCU2CEMOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3921TimeoutBRMOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3922TimeoutBCPOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3923TimeoutBROOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3924TimeoutBCSOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3925TimeoutBCLOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3926TimeoutBSTOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CEMSPN3927TimeoutBSDOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CHMSPN2600CommVerOvrSwt_flg;/* ׮��ͨѶЭ��汾 */
extern volatile boolean_T CbECCR_CCU2CST181DFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3521StopReasonAutoOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3521StopReasonBMSStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3521StopReasonFaultOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3521StopReasonManualOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultCHGCnntOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultDeliverOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultEmerStopOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultOtherOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultTCHGOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3522StopFaultTInterOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3523StopFaultMismatchOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CSTSPN3523StopFaultUOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2ChgBCLOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2ChgBCLOvr_flg;
extern volatile boolean_T CbECCR_CCU2ChgBCPOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2ChgBCPOvr_flg;
extern volatile boolean_T CbECCR_CCU2ChgBHMOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2ChgBHMOvr_flg;
extern volatile boolean_T CbECCR_CCU2ChgBSTOvrSwt_flg;
extern volatile uint8_T CbECCR_CCU2ChgBSTOvr_flg;
extern volatile boolean_T CbECCR_CCU2CrossNegStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2CrossPosStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2DTC18AAFAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2DirectNegStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2DirectPosStateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2ELOCKSTATEOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2FUSE1STATEOvrSwt_flg;/* ����˿״̬ */
extern volatile boolean_T CbECCR_CCU2FaultSevtyStatOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2HV1802FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2ISO1820FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2Sample1803FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VIN1816FAF2hUpdateOvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum1OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum2OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum3OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum4OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum5OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum6OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNum7OvrSwt_flg;
extern volatile boolean_T CbECCR_CCU2VINNumIndexOvrSwt_flg;
extern volatile boolean_T CbECCR_GunAMaxPwrOvrSwt_flg;
extern volatile boolean_T CcECCR_CCU1BCL1817FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU1BCLSPN3072UReqOvr_V;/* ��ѹ���� */
extern volatile real32_T CcECCR_CCU1BCLSPN3073IReqOvr_A;
extern volatile uint8_T CcECCR_CCU1BCLSPN3074ChgModeOvr_enum;/* ���ģʽ */
extern volatile boolean_T CcECCR_CCU1BCP1812FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU1BCP1813FAF2hUpdateOvr_flg;
extern volatile uint16_T CcECCR_CCU1BCPSPN2816UcellMaxPermitOvr_V;/* ���嶯����������������ѹ */
extern volatile real32_T CcECCR_CCU1BCPSPN2817IMaxPermitOvr_A;/* ������������ */
extern volatile real32_T CcECCR_CCU1BCPSPN2818kWhNomOvr_Kwh;/* �������ر�������� */
extern volatile real32_T CcECCR_CCU1BCPSPN2819UMaxPermitOvr_V;/* ����������ܵ�ѹ */
extern volatile real32_T CcECCR_CCU1BCPSPN2820TMaxPermitOvr_C;/* ��������������¶� */
extern volatile real32_T CcECCR_CCU1BCPSPN2821SOCOvr_Pct;
extern volatile real32_T CcECCR_CCU1BCPSPN2822UOvr_V;
extern volatile boolean_T CcECCR_CCU1BCS1818FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU1BCSSPN3075UMeaOvr_V;
extern volatile real32_T CcECCR_CCU1BCSSPN3076IMeaOvr_A;
extern volatile uint16_T CcECCR_CCU1BCSSPN3077UcellMaxOvr_V;
extern volatile uint8_T CcECCR_CCU1BCSSPN3078SOCOvr_Pct;
extern volatile uint16_T CcECCR_CCU1BCSSPN3079TimeRemainOvr_min;
extern volatile uint8_T CcECCR_CCU1BEMSPN3901TimeoutSPN25600x00Ovr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3902TimeoutSPN25600xAAOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3903TimeoutCTSCMLOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3904TimeoutCROOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3905TimeoutCCSOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3906TimeoutCSTOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMSPN3907TimeoutCSDOvr_enum;
extern volatile uint8_T CcECCR_CCU1BEMotherOvr_enum;
extern volatile boolean_T CcECCR_CCU1BHM1811FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU1BHMSPN2601UbatMaxPermitOvr_V;/* ������������ߵ�ѹ�����ھ�Ե��⣩ */
extern volatile boolean_T CcECCR_CCU1BRM1814FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU1BRM1815FAF2hUpdateOvr_flg;
extern volatile uint32_T CcECCR_CCU1BRMSPN2565CommVerOvr_numb;/* ����ͨѶЭ��汾 */
extern volatile real32_T CcECCR_CCU1BRMSPN2567CapNomOvr_Ah;
extern volatile real32_T CcECCR_CCU1BRMSPN2568UNomOvr_V;
extern volatile uint32_T CcECCR_CCU1BRMSPN2569BatFactoryOvr_numb;/* ��������������ƣ�4λASCII�� */
extern volatile uint32_T CcECCR_CCU1BRMSPN2570PackSNOvr_numb;/* ���ģ���ţ������Զ��壩 */
extern volatile boolean_T CcECCR_CCU1BSD181BFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU1BSDSPN3601SOCFinalOvr_Pct;/* ��ֹ�ɵ�״̬SOC */
extern volatile uint16_T CcECCR_CCU1BSDSPN3602UcellMinOvr_V;/* �������ص�����͵�ѹ */
extern volatile uint16_T CcECCR_CCU1BSDSPN3603UcellMaxOvr_V;
extern volatile real32_T CcECCR_CCU1BSDSPN3604TMinOvr_C;
extern volatile real32_T CcECCR_CCU1BSDSPN3605TMaxOvr_C;
extern volatile boolean_T CcECCR_CCU1BSM181AFAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU1BSMSPN3086TMaxOvr_C;
extern volatile real32_T CcECCR_CCU1BSMSPN3088TMinOvr_C;/* ��Ͷ��������¶� */
extern volatile uint8_T CcECCR_CCU1BSMSPN3089TMinIndexOvr_enum;/* ��Ͷ��������¶ȼ����� */
extern volatile boolean_T CcECCR_CCU1BST181CFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU1BSTSPN3511StopReasonCHGStopOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3511StopReasonSOCOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3511StopReasonUOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3511StopReasonUcellOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultBCUcompoOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultCC2Ovr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultChgCnntOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultHVRelayOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultIsoOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultOtherOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultOutCnntOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3512StopFaultTOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3513StopFaultIOvr_enum;
extern volatile uint8_T CcECCR_CCU1BSTSPN3513StopFaultUOvr_enum;
extern volatile boolean_T CcECCR_CCU1CCS1819FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU1CCSSPN3081UOutOvr_V;
extern volatile real32_T CcECCR_CCU1CCSSPN3082IOutOvr_A;
extern volatile uint16_T CcECCR_CCU1CCSSPN3083TimeChargedOvr_Min;
extern volatile uint8_T CcECCR_CCU1CCUDTCFailureTypeByteOvr_numb;
extern volatile uint8_T CcECCR_CCU1CCUDTCHighByteOvr_numb;
extern volatile uint8_T CcECCR_CCU1CCUDTCLowByteOvr_numb;
extern volatile uint8_T CcECCR_CCU1CCUGUNTEMP1STATEOvr_enum;/* ǹ�¶�2״̬ */
extern volatile uint8_T CcECCR_CCU1CCUGUNTEMP2STATEOvr_enum;/* ǹ�¶�1״̬ */
extern volatile real32_T CcECCR_CCU1CCUHVFuseVLTGOvr_V;
extern volatile real32_T CcECCR_CCU1CCUHVRelayOutVLTGOvr_V;
extern volatile real32_T CcECCR_CCU1CCUHVRelayintVLTGOvr_V;
extern volatile uint16_T CcECCR_CCU1CCUISONegVoltOvr_Kohm;
extern volatile real32_T CcECCR_CCU1CCUISONegVoltOvr_V;
extern volatile uint16_T CcECCR_CCU1CCUISOOvr_Kohm;/* CCU��Ե��� */
extern volatile uint16_T CcECCR_CCU1CCUISOPosVoltOvr_Kohm;
extern volatile real32_T CcECCR_CCU1CCUISOPosVoltOvr_V;
extern volatile real32_T CcECCR_CCU1CCUShuntCurrentOvr_A;
extern volatile uint8_T CcECCR_CCU1CCUSysStatAliveCounterOvr_numb;
extern volatile real32_T CcECCR_CCU1CCUTEMP1Ovr_C;/* ǹ���¶Ȳɼ�1 */
extern volatile real32_T CcECCR_CCU1CCUTEMP2Ovr_C;/* ǹ���¶Ȳɼ�2 */
extern volatile uint32_T CcECCR_CCU1CHMSPN2600CommVerOvr_numb;/* ׮��ͨѶЭ��汾 */
extern volatile boolean_T CcECCR_CCU1CST181DFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU1CrossNegStateOvr_enum;
extern volatile uint8_T CcECCR_CCU1CrossPosStateOvr_enum;
extern volatile boolean_T CcECCR_CCU1DTC18AAFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU1DirectNegStateOvr_enum;
extern volatile uint8_T CcECCR_CCU1DirectPosStateOvr_enum;
extern volatile uint8_T CcECCR_CCU1ELOCKSTATEOvr_enum;
extern volatile boolean_T CcECCR_CCU1HV1802FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU1ISO1820FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU1Sample1803FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU1VIN1816FAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU1VINNum1Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum2Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum3Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum4Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum5Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum6Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNum7Ovr_numb;
extern volatile uint8_T CcECCR_CCU1VINNumIndexOvr_numb;
extern volatile boolean_T CcECCR_CCU2BCL1817FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU2BCLSPN3072UReqOvr_V;/* ��ѹ���� */
extern volatile real32_T CcECCR_CCU2BCLSPN3073IReqOvr_A;
extern volatile uint8_T CcECCR_CCU2BCLSPN3074ChgModeOvr_enum;/* ���ģʽ */
extern volatile boolean_T CcECCR_CCU2BCP1812FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU2BCP1813FAF2hUpdateOvr_flg;
extern volatile uint16_T CcECCR_CCU2BCPSPN2816UcellMaxPermitOvr_V;/* ���嶯����������������ѹ */
extern volatile real32_T CcECCR_CCU2BCPSPN2817IMaxPermitOvr_A;/* ������������ */
extern volatile real32_T CcECCR_CCU2BCPSPN2818kWhNomOvr_Kwh;/* �������ر�������� */
extern volatile real32_T CcECCR_CCU2BCPSPN2819UMaxPermitOvr_V;/* ����������ܵ�ѹ */
extern volatile real32_T CcECCR_CCU2BCPSPN2820TMaxPermitOvr_C;/* ��������������¶� */
extern volatile real32_T CcECCR_CCU2BCPSPN2821SOCOvr_Pct;
extern volatile real32_T CcECCR_CCU2BCPSPN2822UOvr_V;
extern volatile boolean_T CcECCR_CCU2BCS1818FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU2BCSSPN3075UMeaOvr_V;
extern volatile real32_T CcECCR_CCU2BCSSPN3076IMeaOvr_A;
extern volatile uint16_T CcECCR_CCU2BCSSPN3077UcellMaxOvr_V;
extern volatile uint8_T CcECCR_CCU2BCSSPN3078SOCOvr_Pct;
extern volatile uint16_T CcECCR_CCU2BCSSPN3079TimeRemainOvr_min;
extern volatile uint8_T CcECCR_CCU2BEMSPN3901TimeoutSPN25600x00Ovr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3902TimeoutSPN25600xAAOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3903TimeoutCTSCMLOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3904TimeoutCROOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3905TimeoutCCSOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3906TimeoutCSTOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMSPN3907TimeoutCSDOvr_enum;
extern volatile uint8_T CcECCR_CCU2BEMotherOvr_enum;
extern volatile boolean_T CcECCR_CCU2BHM1811FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU2BHMSPN2601UbatMaxPermitOvr_V;/* ������������ߵ�ѹ�����ھ�Ե��⣩ */
extern volatile boolean_T CcECCR_CCU2BRM1814FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU2BRM1815FAF2hUpdateOvr_flg;
extern volatile uint32_T CcECCR_CCU2BRMSPN2565CommVerOvr_numb;/* ����ͨѶЭ��汾 */
extern volatile real32_T CcECCR_CCU2BRMSPN2567CapNomOvr_Ah;
extern volatile real32_T CcECCR_CCU2BRMSPN2568UNomOvr_V;
extern volatile uint32_T CcECCR_CCU2BRMSPN2569BatFactoryOvr_numb;/* ��������������ƣ�4λASCII�� */
extern volatile uint32_T CcECCR_CCU2BRMSPN2570PackSNOvr_numb;/* ���ģ���ţ������Զ��壩 */
extern volatile boolean_T CcECCR_CCU2BSD181BFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU2BSDSPN3601SOCFinalOvr_Pct;/* ��ֹ�ɵ�״̬SOC */
extern volatile uint16_T CcECCR_CCU2BSDSPN3602UcellMinOvr_V;/* �������ص�����͵�ѹ */
extern volatile uint16_T CcECCR_CCU2BSDSPN3603UcellMaxOvr_V;
extern volatile real32_T CcECCR_CCU2BSDSPN3604TMinOvr_C;
extern volatile real32_T CcECCR_CCU2BSDSPN3605TMaxOvr_C;
extern volatile boolean_T CcECCR_CCU2BSM181AFAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU2BSMSPN3086TMaxOvr_C;
extern volatile real32_T CcECCR_CCU2BSMSPN3088TMinOvr_C;/* ��Ͷ��������¶� */
extern volatile uint8_T CcECCR_CCU2BSMSPN3089TMinIndexOvr_enum;/* ��Ͷ��������¶ȼ����� */
extern volatile boolean_T CcECCR_CCU2BST181CFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU2BSTSPN3511StopReasonCHGStopOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3511StopReasonSOCOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3511StopReasonUOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3511StopReasonUcellOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultBCUcompoOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultCC2Ovr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultChgCnntOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultHVRelayOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultIsoOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultOtherOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultOutCnntOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3512StopFaultTOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3513StopFaultIOvr_enum;
extern volatile uint8_T CcECCR_CCU2BSTSPN3513StopFaultUOvr_enum;
extern volatile boolean_T CcECCR_CCU2CCS1819FAF2hUpdateOvr_flg;
extern volatile real32_T CcECCR_CCU2CCSSPN3081UOutOvr_V;
extern volatile real32_T CcECCR_CCU2CCSSPN3082IOutOvr_A;
extern volatile uint16_T CcECCR_CCU2CCSSPN3083TimeChargedOvr_Min;
extern volatile uint8_T CcECCR_CCU2CCUDTCFailureTypeByteOvr_numb;
extern volatile uint8_T CcECCR_CCU2CCUDTCHighByteOvr_numb;
extern volatile uint8_T CcECCR_CCU2CCUDTCLowByteOvr_numb;
extern volatile uint8_T CcECCR_CCU2CCUGUNTEMP1STATEOvr_enum;/* ǹ�¶�2״̬ */
extern volatile uint8_T CcECCR_CCU2CCUGUNTEMP2STATEOvr_enum;/* ǹ�¶�1״̬ */
extern volatile real32_T CcECCR_CCU2CCUHVFuseVLTGOvr_V;
extern volatile real32_T CcECCR_CCU2CCUHVRelayOutVLTGOvr_V;
extern volatile real32_T CcECCR_CCU2CCUHVRelayintVLTGOvr_V;
extern volatile uint16_T CcECCR_CCU2CCUISONegVoltOvr_Kohm;
extern volatile real32_T CcECCR_CCU2CCUISONegVoltOvr_V;
extern volatile uint16_T CcECCR_CCU2CCUISOOvr_Kohm;/* CCU��Ե��� */
extern volatile uint16_T CcECCR_CCU2CCUISOPosVoltOvr_Kohm;
extern volatile real32_T CcECCR_CCU2CCUISOPosVoltOvr_V;
extern volatile real32_T CcECCR_CCU2CCUShuntCurrentOvr_A;
extern volatile uint8_T CcECCR_CCU2CCUSysStatAliveCounterOvr_numb;
extern volatile real32_T CcECCR_CCU2CCUTEMP1Ovr_C;/* ǹ���¶Ȳɼ�1 */
extern volatile real32_T CcECCR_CCU2CCUTEMP2Ovr_C;/* ǹ���¶Ȳɼ�2 */
extern volatile uint32_T CcECCR_CCU2CHMSPN2600CommVerOvr_numb;/* ׮��ͨѶЭ��汾 */
extern volatile boolean_T CcECCR_CCU2CST181DFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU2CrossNegStateOvr_enum;
extern volatile uint8_T CcECCR_CCU2CrossPosStateOvr_enum;
extern volatile boolean_T CcECCR_CCU2DTC18AAFAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU2DirectNegStateOvr_enum;
extern volatile uint8_T CcECCR_CCU2DirectPosStateOvr_enum;
extern volatile uint8_T CcECCR_CCU2ELOCKSTATEOvr_enum;
extern volatile boolean_T CcECCR_CCU2HV1802FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU2ISO1820FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU2Sample1803FAF2hUpdateOvr_flg;
extern volatile boolean_T CcECCR_CCU2VIN1816FAF2hUpdateOvr_flg;
extern volatile uint8_T CcECCR_CCU2VINNum1Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum2Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum3Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum4Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum5Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum6Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNum7Ovr_numb;
extern volatile uint8_T CcECCR_CCU2VINNumIndexOvr_numb;
extern volatile real32_T CcECCR_GunAMaxPwrOvr_kw;
extern volatile uint8_T CeECCR_CCU1BCSSPN3077UcellMaxGrpOvr_enum;
extern volatile uint8_T CeECCR_CCU1BRMSPN2566BatTypeOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3085UcellMaxIndexOvr_enum;/* ��ߵ��嶯�����ص�ѹ���ڱ�� */
extern volatile uint8_T CeECCR_CCU1BSMSPN3087TMaxIndexOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3090UcellWarnOvr_enum;/* ���嶯�����ص�ѹ */
extern volatile uint8_T CeECCR_CCU1BSMSPN3091SOCWarnOvr_enum;/* �����������غɵ�״̬SOC */
extern volatile uint8_T CeECCR_CCU1BSMSPN3092IWarnOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3093TWarnOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3094IsoStateOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3095OutConnectorStateOvr_enum;
extern volatile uint8_T CeECCR_CCU1BSMSPN3096ChgEnableOvr_enum;
extern volatile uint8_T CeECCR_CCU1CCU12VSTATEOvr_enum;/* CCU22V״̬ */
extern volatile uint8_T CeECCR_CCU1CCU24VSTATEOvr_enum;/* CCU24V״̬ */
extern volatile uint8_T CeECCR_CCU1CCUCARCONNECTSTATEOvr_enum;/* �����Ƿ񷴽� */
extern volatile uint8_T CeECCR_CCU1CCUCC1STATEOvr_enum;/* CC1״̬ */
extern volatile uint8_T CeECCR_CCU1CCUGUNpositionOvr_enum;
extern volatile uint8_T CeECCR_CCU1CCUISOSTATEOvr_enum;/* CCU��Ե���״̬ */
extern volatile uint8_T CeECCR_CCU1CCUIndexOvr_enum;/* CCU��� */
extern volatile uint8_T CeECCR_CCU1CCUK1K3STATEOvr_enum;/* K1�̵���״̬(K3) */
extern volatile uint8_T CeECCR_CCU1CCUK2K4STATEOvr_enum;
extern volatile uint8_T CeECCR_CCU1CCUPyroswitchCMDOvr_enum;
extern volatile uint8_T CeECCR_CCU1CCUSTATEOvr_enum;/* CCU����״̬ */
extern volatile uint8_T CeECCR_CCU1CEMOtherOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3921TimeoutBRMOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3922TimeoutBCPOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3923TimeoutBROOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3924TimeoutBCSOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3925TimeoutBCLOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3926TimeoutBSTOvr_enum;
extern volatile uint8_T CeECCR_CCU1CEMSPN3927TimeoutBSDOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3521StopReasonAutoOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3521StopReasonBMSStopOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3521StopReasonFaultOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3521StopReasonManualOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultCHGCnntOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultDeliverOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultEmerStopOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultOtherOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultTCHGOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3522StopFaultTInterOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3523StopFaultMismatchOvr_enum;
extern volatile uint8_T CeECCR_CCU1CSTSPN3523StopFaultUOvr_enum;
extern volatile uint8_T CeECCR_CCU1FUSE1STATEOvr_enum;/* ����˿״̬ */
extern volatile uint8_T CeECCR_CCU1FaultSevtyStatOvr_enum;
extern volatile uint8_T CeECCR_CCU2BCSSPN3077UcellMaxGrpOvr_enum;
extern volatile uint8_T CeECCR_CCU2BRMSPN2566BatTypeOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3085UcellMaxIndexOvr_enum;/* ��ߵ��嶯�����ص�ѹ���ڱ�� */
extern volatile uint8_T CeECCR_CCU2BSMSPN3087TMaxIndexOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3090UcellWarnOvr_enum;/* ���嶯�����ص�ѹ */
extern volatile uint8_T CeECCR_CCU2BSMSPN3091SOCWarnOvr_enum;/* �����������غɵ�״̬SOC */
extern volatile uint8_T CeECCR_CCU2BSMSPN3092IWarnOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3093TWarnOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3094IsoStateOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3095OutConnectorStateOvr_enum;
extern volatile uint8_T CeECCR_CCU2BSMSPN3096ChgEnableOvr_enum;
extern volatile uint8_T CeECCR_CCU2CCU22VSTATEOvr_enum;/* CCU22V״̬ */
extern volatile uint8_T CeECCR_CCU2CCU24VSTATEOvr_enum;/* CCU24V״̬ */
extern volatile uint8_T CeECCR_CCU2CCUCARCONNECTSTATEOvr_enum;/* �����Ƿ񷴽� */
extern volatile uint8_T CeECCR_CCU2CCUCC1STATEOvr_enum;/* CC1״̬ */
extern volatile uint8_T CeECCR_CCU2CCUGUNpositionOvr_enum;
extern volatile uint8_T CeECCR_CCU2CCUISOSTATEOvr_enum;/* CCU��Ե���״̬ */
extern volatile uint8_T CeECCR_CCU2CCUIndexOvr_enum;/* CCU��� */
extern volatile uint8_T CeECCR_CCU2CCUK1K3STATEOvr_enum;/* K1�̵���״̬(K3) */
extern volatile uint8_T CeECCR_CCU2CCUK2K4STATEOvr_enum;
extern volatile uint8_T CeECCR_CCU2CCUPyroswitchCMDOvr_enum;
extern volatile uint8_T CeECCR_CCU2CCUSTATEOvr_enum;/* CCU����״̬ */
extern volatile uint8_T CeECCR_CCU2CEMOtherOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3921TimeoutBRMOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3922TimeoutBCPOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3923TimeoutBROOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3924TimeoutBCSOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3925TimeoutBCLOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3926TimeoutBSTOvr_enum;
extern volatile uint8_T CeECCR_CCU2CEMSPN3927TimeoutBSDOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3521StopReasonAutoOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3521StopReasonBMSStopOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3521StopReasonFaultOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3521StopReasonManualOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultCHGCnntOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultDeliverOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultEmerStopOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultOtherOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultTCHGOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3522StopFaultTInterOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3523StopFaultMismatchOvr_enum;
extern volatile uint8_T CeECCR_CCU2CSTSPN3523StopFaultUOvr_enum;
extern volatile uint8_T CeECCR_CCU2FUSE1STATEOvr_enum;/* ����˿״̬ */
extern volatile uint8_T CeECCR_CCU2FaultSevtyStatOvr_enum;
extern volatile boolean_T GbECCR_GunBMaxPwrOvrSwt_flg;
extern volatile real32_T GcECCR_GunBMaxPwrOvr_kw;

#endif                                 /* RTW_HEADER_ECCR_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
