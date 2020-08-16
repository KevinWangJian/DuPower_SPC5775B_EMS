/*
 * File: ECCS_Cal.c
 *
 * Code generated for Simulink model 'ECCS'.
 *
 * Company                        : DP
 * Author                         : 19952702426
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Tue Jun 09 12:03:04 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Freescale->32-bit PowerPC
 * Code generation objective: MISRA C:2012 guidelines
 * Validation result: Not run
 */
 
#include "rtwtypes.h"
#include "ECCS_types.h"
 
#pragma section DATA ".cal_data"
/* Exported data definition */
volatile boolean_T CbECCS_CCU1ACDC1CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDC1CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDC1StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDC2CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDC2CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDC2StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDCCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDCCurrtPowerOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDCInputOverVoltOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ACDCInputOverVoltOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ACDCInputUnderVoltOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ACDCInputUnderVoltOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ACDCOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDCPowerCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ACDCPowerCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ACDCindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACDCinputLossPhaseOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ACDCinputLossPhaseOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ACWhCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACWhCurrtEnergeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACWhMeterCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ACWhMeterCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ACWhOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ACWhindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ADCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1ADCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1ADFANStatusOvrSwt_flg = 0;/* ״̬
                                                           0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU1ADFANStatusOvr_flg = 0U;/* ״̬
                                                       0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU1ADmicrophoneStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU1ADmicrophoneStatusOvr_flg = 0U;/* ״̬
                                                              0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU1AFCProjectTypeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1AFCSysModeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1AntithunderwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1AntithunderwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1AuxPwrCtrlOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1BMSCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1BMSCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CCU1CrossNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU1CrossNegFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU1CrossPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU1CrossPosFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU1DirectNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU1DirectNegFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU1DirectPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU1DirectPosFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU2CrossNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU2CrossNegFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU2CrossPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU2CrossPosFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU2DirectNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU2DirectNegFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCU2DirectPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU1CCU2DirectPosFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU1CCUCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1CCUCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CCUISONegMosCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1CCUISONegMosCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CCUISOPosMosCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1CCUISOPosMosCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CCUIsoDetAllowOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1CCUIsoDetAllowOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CCUUnlockCmdOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1CMLSPN2824UMaxOutOvrSwt_flg = 0;/* AFC��������ѹֵ */
volatile boolean_T CbECCS_CCU1CMLSPN2825UMinOutOvrSwt_flg = 0;/* AFC������С��ѹֵ */
volatile boolean_T CbECCS_CCU1CMLSPN2826IMaxOutOvrSwt_flg = 0;/* AFC����������ֵ */
volatile boolean_T CbECCS_CCU1CMLSPN2827IMinOutOvrSwt_flg = 0;/* AFC����������ֵ */
volatile boolean_T CbECCS_CCU1CRMSPN2561CHGIndexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1CRMSPN2562CHGLocOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1CardCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1CardCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1CellTmpTargetOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ChargeModeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1ConntCB5AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntCB5AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntCB6AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntCB6AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntCrashStatusOvrSwt_flg = 0;/* ״̬
                                                                0:reserved 1:reserved
                                                                2:normal  3:error */
volatile boolean_T CbECCS_CCU1ConntDoorConntAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntDoorConntAUXStatusOvr_flg = 0U;/* ״̬
                                                                   0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntEMGSTOPAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                     0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntEMGSTOPAUXStatusOvr_flg = 0U;/* ״̬
                                                                 0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntFUSE3StatusOvrSwt_flg = 0;/* ״̬
                                                                0:normal 1:open */
volatile uint8_T CbECCS_CCU1ConntFUSE3StatusOvr_flg = 0U;/* ״̬
                                                            0:normal 1:open */
volatile boolean_T CbECCS_CCU1ConntFVC1CB1StatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntFVC1CB1StatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntFVC2CB2StatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntFVC2CB2StatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntK11K12AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                    0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntK11K12AUXStatusOvr_flg = 0U;/* ״̬
                                                                0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntK13RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU1ConntK14RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU1ConntK14RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU1ConntK15RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU1ConntK15RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU1ConntK16RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU1ConntK16RealyStatusOvr_flg = 0U;/* ״̬
                                                               0:Open 1:Close
                                                               2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU1ConntK5K6AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntK5K6AUXStatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntK7K8AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntK7K8AUXStatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntK9K10AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntK9K10AUXStatusOvr_flg = 0U;/* ״̬
                                                               0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntKM1AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntKM1AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntKM2AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntKM2AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntQF1AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntQF1AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntQF2AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntQF2AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntQF3AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntQF3AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntRolloverStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:reserved 1:reserved
                                                                   2:normal  3:error */
volatile boolean_T CbECCS_CCU1ConntSmokeAlarmAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntSmokeAlarmAUXStatusOvr_flg = 0U;/* ״̬
                                                                    0:normal 1:error */
volatile boolean_T CbECCS_CCU1ConntWaterLevelAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU1ConntWaterLevelAUXStatusOvr_flg = 0U;/* ״̬
                                                                    0:normal 1:error */
volatile boolean_T CbECCS_CCU1CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC10StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC11StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC12StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC13StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC14StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC15StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC1StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC2StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC3StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC4StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC5StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC6StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC7StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC8StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDC9StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCCurrtPowerOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCInputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCPowerCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1DCDCPowerCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1DCDCT24VStatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDCindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCDT24CommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1DCDT24CommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1DCWhCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCWhCurrtEnergeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCWhMeterCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1DCWhMeterCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1DCWhOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1DCWhindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSACDCVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSCCUCrossCntCommandOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1EMSCCUCrossCntCommandOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1EMSCCUDirectCntCommandOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1EMSCCUDirectCntCommandOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1EMSChargeAllowOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSDTCFailureTypeByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSDTCHighByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSDTCLowByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSFltlevelOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSHVIsoWarningOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSHwVersionOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSK15FUSEVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSK15K16VoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSPowerOffCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1EMSPowerOffCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1EMSSetTimerDayOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerHourOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerMinuteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerMonthOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerSecondOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerYearOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSetTimerenbleOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSwVersionOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSysStatAliveCounterOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSSysStatCheckSumOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSToCCUindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1EMSToCHGIndexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1FAN1StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU1FAN1StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU1FAN2StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU1FAN2StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU1FAN3StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU1FAN3StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU1HeatInputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1InputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1LED1StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED1StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LED2StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED2StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LED3StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED3StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LED4StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED4StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LED5StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED5StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LED6StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU1LED6StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU1LowBatteryVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1SupplyPwrwarningOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1TBOXCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1TBOXCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU1TMSPS1relayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1TMSPS1relayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1TMSPS2relayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1TMSPS2relayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU1TouchCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU1TouchCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACDC1CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDC1CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDC1StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDC2CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDC2CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDC2StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDCCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDCCurrtPowerOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDCInputOverVoltOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ACDCInputOverVoltOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACDCInputUnderVoltOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ACDCInputUnderVoltOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACDCOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDCPowerCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ACDCPowerCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACDCindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACDCinputLossPhaseOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ACDCinputLossPhaseOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACWhCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACWhCurrtEnergeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACWhMeterCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ACWhMeterCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ACWhOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ACWhindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ADCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2ADCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2ADFANStatusOvrSwt_flg = 0;/* ״̬
                                                           0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU2ADFANStatusOvr_flg = 0U;/* ״̬
                                                       0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU2ADmicrophoneStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU2ADmicrophoneStatusOvr_flg = 0U;/* ״̬
                                                              0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU2AFCProjectTypeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2AFCSysModeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2AntithunderwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2AntithunderwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2AuxPwrCtrlOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2BMSCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2BMSCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CCU1CrossNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU1CrossNegFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU1CrossPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU1CrossPosFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU1DirectNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU1DirectNegFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU1DirectPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU1DirectPosFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU2CrossNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU2CrossNegFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU2CrossPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                              1 "Close"
                                                              2 "Can Not Open "
                                                              3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU2CrossPosFBOvr_enum = 0U;/* 0 "Open"
                                                           1 "Close"
                                                           2 "Can Not Open "
                                                           3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU2DirectNegFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU2DirectNegFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCU2DirectPosFBOvrSwt_flg = 0;/* 0 "Open"
                                                               1 "Close"
                                                               2 "Can Not Open "
                                                               3 "Can Not Close" */
volatile uint8_T CbECCS_CCU2CCU2DirectPosFBOvr_enum = 0U;/* 0 "Open"
                                                            1 "Close"
                                                            2 "Can Not Open "
                                                            3 "Can Not Close" */
volatile boolean_T CbECCS_CCU2CCUCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2CCUCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CCUISONegMosCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2CCUISONegMosCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CCUISOPosMosCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2CCUISOPosMosCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CCUIsoDetAllowOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2CCUIsoDetAllowOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CCUUnlockCmdOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2CMLSPN2824UMaxOutOvrSwt_flg = 0;/* AFC��������ѹֵ */
volatile boolean_T CbECCS_CCU2CMLSPN2825UMinOutOvrSwt_flg = 0;/* AFC������С��ѹֵ */
volatile boolean_T CbECCS_CCU2CMLSPN2826IMaxOutOvrSwt_flg = 0;/* AFC����������ֵ */
volatile boolean_T CbECCS_CCU2CMLSPN2827IMinOutOvrSwt_flg = 0;/* AFC����������ֵ */
volatile boolean_T CbECCS_CCU2CRMSPN2561CHGIndexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2CRMSPN2562CHGLocOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2CardCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2CardCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2CellTmpTargetOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ChargeModeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2ConntCB5AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntCB5AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntCB6AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntCB6AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntCrashStatusOvrSwt_flg = 0;/* ״̬
                                                                0:reserved 1:reserved
                                                                2:normal  3:error */
volatile boolean_T CbECCS_CCU2ConntDoorConntAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntDoorConntAUXStatusOvr_flg = 0U;/* ״̬
                                                                   0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntEMGSTOPAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                     0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntEMGSTOPAUXStatusOvr_flg = 0U;/* ״̬
                                                                 0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntFUSE3StatusOvrSwt_flg = 0;/* ״̬
                                                                0:normal 1:open */
volatile uint8_T CbECCS_CCU2ConntFUSE3StatusOvr_flg = 0U;/* ״̬
                                                            0:normal 1:open */
volatile boolean_T CbECCS_CCU2ConntFVC1CB1StatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntFVC1CB1StatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntFVC2CB2StatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntFVC2CB2StatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntK11K12AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                    0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntK11K12AUXStatusOvr_flg = 0U;/* ״̬
                                                                0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntK13RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU2ConntK14RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU2ConntK14RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU2ConntK15RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU2ConntK15RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU2ConntK16RealyStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:Open 1:Close
                                                                   2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CbECCS_CCU2ConntK16RealyStatusOvr_flg = 0U;/* ״̬
                                                               0:Open 1:Close
                                                               2:AbnormalClose 3:AbnormalOpen */
volatile boolean_T CbECCS_CCU2ConntK5K6AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntK5K6AUXStatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntK7K8AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                  0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntK7K8AUXStatusOvr_flg = 0U;/* ״̬
                                                              0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntK9K10AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntK9K10AUXStatusOvr_flg = 0U;/* ״̬
                                                               0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntKM1AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntKM1AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntKM2AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntKM2AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntQF1AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntQF1AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntQF2AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntQF2AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntQF3AUXStatusOvrSwt_flg = 0;/* ״̬
                                                                 0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntQF3AUXStatusOvr_flg = 0U;/* ״̬
                                                             0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntRolloverStatusOvrSwt_flg = 0;/* ״̬
                                                                   0:reserved 1:reserved
                                                                   2:normal  3:error */
volatile boolean_T CbECCS_CCU2ConntSmokeAlarmAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntSmokeAlarmAUXStatusOvr_flg = 0U;/* ״̬
                                                                    0:normal 1:error */
volatile boolean_T CbECCS_CCU2ConntWaterLevelAUXStatusOvrSwt_flg = 0;/* ״̬
                                                                      0:normal 1:error */
volatile uint8_T CbECCS_CCU2ConntWaterLevelAUXStatusOvr_flg = 0U;/* ״̬
                                                                    0:normal 1:error */
volatile boolean_T CbECCS_CCU2CrossrelayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2CrossrelayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC10StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC11StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC12StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC13StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC14StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC15StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC1StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC2StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC3StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC4StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC5StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC6StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC7StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC8StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDC9StatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCCurrtPowerOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCInputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCPowerCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2DCDCPowerCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2DCDCT24VStatusOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDCindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCDT24CommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2DCDT24CommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2DCWhCurrentOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCWhCurrtEnergeOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCWhMeterCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2DCWhMeterCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2DCWhOutputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2DCWhindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSACDCVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSCCUCrossCntCommandOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2EMSCCUCrossCntCommandOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2EMSCCUDirectCntCommandOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2EMSCCUDirectCntCommandOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2EMSChargeAllowOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSDTCFailureTypeByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSDTCHighByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSDTCLowByteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSFltlevelOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSHVIsoWarningOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSHwVersionOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSK15FUSEVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSK15K16VoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSPowerOffCmdOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2EMSPowerOffCmdOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2EMSSetTimerDayOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerHourOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerMinuteOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerMonthOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerSecondOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerYearOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSetTimerenbleOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSwVersionOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSysStatAliveCounterOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSSysStatCheckSumOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSToCCUindexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2EMSToCHGIndexOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2FAN1StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU2FAN1StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU2FAN2StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU2FAN2StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU2FAN3StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:Run 2:error */
volatile uint8_T CbECCS_CCU2FAN3StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:Run 2:error */
volatile boolean_T CbECCS_CCU2HeatInputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2InputVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2LED1StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED1StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LED2StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED2StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LED3StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED3StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LED4StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED4StatusOvr_enum = 0U;/* ״̬
                                                       0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LED5StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED5StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LED6StatusOvrSwt_flg = 0;/* ״̬
                                                          0:off 1:on 2:error */
volatile uint8_T CbECCS_CCU2LED6StatusOvr_flg = 0U;/* ״̬
                                                      0:off 1:on 2:error */
volatile boolean_T CbECCS_CCU2LowBatteryVoltOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2SupplyPwrwarningOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2TBOXCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2TBOXCommwarningOvr_flg = 0U;
volatile boolean_T CbECCS_CCU2TMSPS1relayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2TMSPS1relayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2TMSPS2relayNegStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2TMSPS2relayPosStateOvrSwt_flg = 0;
volatile boolean_T CbECCS_CCU2TouchCommwarningOvrSwt_flg = 0;
volatile uint8_T CbECCS_CCU2TouchCommwarningOvr_flg = 0U;
volatile uint16_T CcECCS_CCU1ACDCCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU1ACDCCurrtPowerOvr_Kw = 0U;
volatile uint16_T CcECCS_CCU1ACDCOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1ACWhCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU1ACWhCurrtEnergeOvr_Kwh = 0U;
volatile uint16_T CcECCS_CCU1ACWhOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1CMLSPN2824UMaxOutOvr_V = 0U;/* AFC��������ѹֵ */
volatile uint16_T CcECCS_CCU1CMLSPN2825UMinOutOvr_V = 0U;/* AFC������С��ѹֵ */
volatile uint16_T CcECCS_CCU1CMLSPN2826IMaxOutOvr_A = 0U;/* AFC����������ֵ */
volatile uint16_T CcECCS_CCU1CMLSPN2827IMinOutOvr_A = 0U;/* AFC����������ֵ */
volatile uint8_T CcECCS_CCU1CellTmpTargetOvr_C = 40U;
volatile uint16_T CcECCS_CCU1DCDCCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU1DCDCCurrtPowerOvr_Kw = 0U;
volatile uint16_T CcECCS_CCU1DCDCInputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1DCDCOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1DCWhCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU1DCWhCurrtEnergeOvr_Kwh = 0U;
volatile uint16_T CcECCS_CCU1DCWhOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1EMSACDCVoltOvr_V = 0U;
volatile uint8_T CcECCS_CCU1EMSDTCFailureTypeByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU1EMSDTCHighByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU1EMSDTCLowByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU1EMSHwVersionOvr_numb = 0U;
volatile uint16_T CcECCS_CCU1EMSK15FUSEVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1EMSK15K16VoltOvr_V = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerDayOvr_D = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerHourOvr_H = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerMinuteOvr_Min = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerMonthOvr_M = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerSecondOvr_S = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerYearOvr_Y = 0U;
volatile uint8_T CcECCS_CCU1EMSSetTimerenbleOvr_flg = 0U;
volatile uint8_T CcECCS_CCU1EMSSwVersionOvr_numb = 0U;
volatile uint8_T CcECCS_CCU1EMSSysStatAliveCounterOvr_numb = 0U;
volatile uint8_T CcECCS_CCU1EMSSysStatCheckSumOvr_numb = 0U;
volatile uint16_T CcECCS_CCU1HeatInputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1InputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU1LowBatteryVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2ACDCCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU2ACDCCurrtPowerOvr_Kw = 0U;
volatile uint16_T CcECCS_CCU2ACDCOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2ACWhCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU2ACWhCurrtEnergeOvr_Kwh = 0U;
volatile uint16_T CcECCS_CCU2ACWhOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2CMLSPN2824UMaxOutOvr_V = 0U;/* AFC��������ѹֵ */
volatile uint16_T CcECCS_CCU2CMLSPN2825UMinOutOvr_V = 0U;/* AFC������С��ѹֵ */
volatile uint16_T CcECCS_CCU2CMLSPN2826IMaxOutOvr_A = 0U;/* AFC����������ֵ */
volatile uint16_T CcECCS_CCU2CMLSPN2827IMinOutOvr_A = 0U;/* AFC����������ֵ */
volatile uint8_T CcECCS_CCU2CellTmpTargetOvr_C = 40U;
volatile uint16_T CcECCS_CCU2DCDCCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU2DCDCCurrtPowerOvr_Kw = 0U;
volatile uint16_T CcECCS_CCU2DCDCInputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2DCDCOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2DCWhCurrentOvr_A = 4000U;
volatile uint16_T CcECCS_CCU2DCWhCurrtEnergeOvr_Kwh = 0U;
volatile uint16_T CcECCS_CCU2DCWhOutputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2EMSACDCVoltOvr_V = 0U;
volatile uint8_T CcECCS_CCU2EMSDTCFailureTypeByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU2EMSDTCHighByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU2EMSDTCLowByteOvr_numb = 0U;
volatile uint8_T CcECCS_CCU2EMSHwVersionOvr_numb = 0U;
volatile uint16_T CcECCS_CCU2EMSK15FUSEVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2EMSK15K16VoltOvr_V = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerDayOvr_D = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerHourOvr_H = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerMinuteOvr_Min = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerMonthOvr_M = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerSecondOvr_S = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerYearOvr_Y = 0U;
volatile uint8_T CcECCS_CCU2EMSSetTimerenbleOvr_flg = 0U;
volatile uint8_T CcECCS_CCU2EMSSwVersionOvr_numb = 0U;
volatile uint8_T CcECCS_CCU2EMSSysStatAliveCounterOvr_numb = 0U;
volatile uint8_T CcECCS_CCU2EMSSysStatCheckSumOvr_numb = 0U;
volatile uint16_T CcECCS_CCU2HeatInputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2InputVoltOvr_V = 0U;
volatile uint16_T CcECCS_CCU2LowBatteryVoltOvr_V = 0U;
volatile uint8_T CeECCS_CCU1ACDC1CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDC1CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDC1StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDC2CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDC2CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDC2StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACDCindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ACWhindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1AFCProjectTypeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1AFCSysModeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1AuxPwrCtrlOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1CCUUnlockCmdOvr_enum = 0U;
volatile uint32_T CeECCS_CCU1CRMSPN2561CHGIndexOvr_enum = 0U;
volatile uint32_T CeECCS_CCU1CRMSPN2562CHGLocOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ChargeModeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1ConntCrashStatusOvr_enum = 0U;/* ״̬
                                                             0:reserved 1:reserved
                                                             2:normal  3:error */
volatile uint8_T CeECCS_CCU1ConntK13RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CeECCS_CCU1ConntRolloverStatusOvr_enum = 0U;/* ״̬
                                                                0:reserved 1:reserved
                                                                2:normal  3:error */
volatile uint8_T CeECCS_CCU1CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC10StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC11StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC12StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC13StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC14StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC15StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC1StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC2StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC3StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC4StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC5StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC6StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC7StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC8StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDC9StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDCT24VStatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCDCindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1DCWhindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1EMSChargeAllowOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1EMSFltlevelOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1EMSHVIsoWarningOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1EMSToCCUindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1EMSToCHGIndexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1SupplyPwrwarningOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1TMSPS1relayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1TMSPS1relayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1TMSPS2relayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU1TMSPS2relayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC1CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC1CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC1StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC2CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC2CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDC2StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACDCindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ACWhindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2AFCProjectTypeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2AFCSysModeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2AuxPwrCtrlOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2CCUUnlockCmdOvr_enum = 0U;
volatile uint32_T CeECCS_CCU2CRMSPN2561CHGIndexOvr_enum = 0U;
volatile uint32_T CeECCS_CCU2CRMSPN2562CHGLocOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ChargeModeOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2ConntCrashStatusOvr_enum = 0U;/* ״̬
                                                             0:reserved 1:reserved
                                                             2:normal  3:error */
volatile uint8_T CeECCS_CCU2ConntK13RealyStatusOvr_enum = 0U;/* ״̬
                                                                0:Open 1:Close
                                                                2:AbnormalClose 3:AbnormalOpen */
volatile uint8_T CeECCS_CCU2ConntRolloverStatusOvr_enum = 0U;/* ״̬
                                                                0:reserved 1:reserved
                                                                2:normal  3:error */
volatile uint8_T CeECCS_CCU2CrossrelayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2CrossrelayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC10StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC11StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC12StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC13StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC14StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC15StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC1StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC2StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC3StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC4StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC5StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC6StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC7StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC8StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDC9StatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDCT24VStatusOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCDCindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2DCWhindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2EMSChargeAllowOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2EMSFltlevelOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2EMSHVIsoWarningOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2EMSToCCUindexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2EMSToCHGIndexOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2SupplyPwrwarningOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2TMSPS1relayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2TMSPS1relayPosStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2TMSPS2relayNegStateOvr_enum = 0U;
volatile uint8_T CeECCS_CCU2TMSPS2relayPosStateOvr_enum = 0U;
#pragma section DATA
/*
 * File trailer for generated code.
 *
 * [EOF]
 */
