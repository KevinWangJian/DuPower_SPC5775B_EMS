/*
 * File: EBCR_Cal.h
 *
 * Code generated for Simulink model 'EBCR'.
 *
 * Company                        : DP
 * Author                         : Kris Lee
 * Model version                  : 'EV31A-M1.05'
 * Simulink Coder version         : 8.9 (R2015b) 13-Aug-2015
 * C/C++ source code generated on : Mon Jun 08 14:21:32 2020
 */

#ifndef RTW_HEADER_EBCR_Cal_h_
#define RTW_HEADER_EBCR_Cal_h_
#include "rtwtypes.h"

/* Exported data declaration */
extern volatile boolean_T CbEBCR_BMSABMUSP2VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSABMUSP3VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSABMUSP4VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSABMUSP5VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACelConsistencyWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACelConsistencyWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSACellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellOvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellOvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSACellQuantityOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes1OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes2OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes3OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes4OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes5OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellTempMes6OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellUvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACellUvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSAChargeCurrentMaxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAChrgVoltMaxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSACurRechrgEnergyStorSysIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSADTCFailureTypeByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSADTCHighByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSADTCLowByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAFaultAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAFaultChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAFaultLevelOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHCUPwrCtrlOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHCUPwrCtrlOvr_flg;
extern volatile boolean_T CbEBCR_BMSAHVBCPLngTrmChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVBCPShrtTrmChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVBDPShrtTrmDischrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVBatSOCOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVCurrAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVCurrChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVILWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVILWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSAHVIsoValueOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVIsoWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVShutdownReqOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHVShutdownReqOvr_flg;
extern volatile boolean_T CbEBCR_BMSAHVSysStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHeatMagCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHeatModeSelOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHeatSetTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHeatVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAHwVersionOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAISODetStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAISONegResOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAISONegVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAISOPosVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMainNegCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMainPosCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxBatTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxBatWaterTmpOutOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxCellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxCellTempNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxCellVoltNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxClVltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMaxTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes1CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes1CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSAMes1CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes2CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes2CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSAMes2CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes3CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMes3CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSAMes3CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMesCellTempNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMesCellVoltNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinBatTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinBatWaterTmpInOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinCellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinCellTempNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinCellVoltNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinClVltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAMinTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPACK1RelayWaringOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPack1RechrgNegStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPack1RechrgPosStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackBalanceTypeOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackCurrentOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackCurrentStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackCurrentStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPackCurrentVldOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackCurrentVldOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPackManufactureOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackOCWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackOCWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPackOvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackOvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPackProductionDateDayOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackProductionDateMonthOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackProductionDateYearOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackSNOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackUvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackUvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPackVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackVoltVldOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPackVoltVldOvr_flg;
extern volatile boolean_T CbEBCR_BMSAPeakSOPAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPeakSOPChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPreChrgCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPreChrgHVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPwrBatPackMismatchWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAPwrBatPackMismatchWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSARealSOCOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCode1OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCode2OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCode3OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCode4OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCodeIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysCodeLengthOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARechrgEnergyStorSysNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSARestEnergyOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOCFastChrgWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOCFastChrgWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSASOCHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOCHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSASOCLowWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOEOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOHOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOPAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOPChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASOPosResOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASwVersionOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASysStatAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSASysStatChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSATempDiffWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSATempDiffWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSATempHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSATempHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSATempProbeQuantifyOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSATotalBatCapOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAVoltHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSAVoltHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBBMUSP2VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBBMUSP3VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBBMUSP4VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBBMUSP5VoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCelConsistencyWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCelConsistencyWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBCellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellOvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellOvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBCellQuantityOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes1OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes2OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes3OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes4OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes5OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellTempMes6OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellUvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCellUvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBChargeCurrentMaxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBChrgVoltMaxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBCurRechrgEnergyStorSysIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBDTCFailureTypeByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBDTCHighByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBDTCLowByteOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBFaultAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBFaultChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBFaultLevelOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHCUPwrCtrlOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHCUPwrCtrlOvr_flg;
extern volatile boolean_T CbEBCR_BMSBHVBCPLngTrmChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVBCPShrtTrmChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVBDPShrtTrmDischrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVBatSOCOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVCurrAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVCurrChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVILWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVILWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBHVIsoValueOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVIsoWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVShutdownReqOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHVShutdownReqOvr_flg;
extern volatile boolean_T CbEBCR_BMSBHVSysStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHeatMagCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHeatModeSelOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHeatSetTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHeatVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBHwVersionOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBISODetStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBISONegResOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBISONegVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBISOPosVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMainNegCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMainPosCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxBatTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxBatWaterTmpOutOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxCellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxCellTempNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxCellVoltNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxClVltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMaxTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes1CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes1CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSBMes1CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes2CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes2CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSBMes2CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes3CellBalStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMes3CellBalStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSBMes3CellVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMesCellTempNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMesCellVoltNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinBatTmpOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinBatWaterTmpInOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinCellBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinCellTempNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinCellVoltNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinClVltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBMinTempBatNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPACK1RelayWaringOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPack1RechrgNegStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPack1RechrgPosStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackBalanceTypeOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackCurrentOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackCurrentStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackCurrentStatOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPackCurrentVldOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackCurrentVldOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPackManufactureOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackNumIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackOCWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackOCWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPackOvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackOvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPackProductionDateDayOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackProductionDateMonthOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackProductionDateYearOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackSNOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackUvWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackUvWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPackVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackVoltVldOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPackVoltVldOvr_flg;
extern volatile boolean_T CbEBCR_BMSBPeakSOPAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPeakSOPChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPreChrgCntStatOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPreChrgHVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPwrBatPackMismatchWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBPwrBatPackMismatchWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBRealSOCOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCode1OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCode2OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCode3OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCode4OvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCodeIdxOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysCodeLengthOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRechrgEnergyStorSysNumbOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBRestEnergyOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOCFastChrgWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOCFastChrgWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBSOCHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOCHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBSOCLowWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOEOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOHOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOPAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOPChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSOPosResOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSwVersionOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSysStatAliveCntOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBSysStatChkSumOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBTempDiffWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBTempDiffWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBTempHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBTempHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_BMSBTempProbeQuantifyOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBTotalBatCapOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBVoltHighWarningOvrSwt_flg;
extern volatile boolean_T CbEBCR_BMSBVoltHighWarningOvr_flg;
extern volatile boolean_T CbEBCR_PackALongDisChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_PackAOutVoltOvrSwt_flg;
extern volatile boolean_T CbEBCR_PackBLongDisChrgPwrOvrSwt_flg;
extern volatile boolean_T CbEBCR_PackBOutVoltOvrSwt_flg;
extern volatile real32_T CcEBCR_BMSABMUSP2VoltOvr_V;
extern volatile real32_T CcEBCR_BMSABMUSP3VoltOvr_V;
extern volatile real32_T CcEBCR_BMSABMUSP4VoltOvr_V;
extern volatile real32_T CcEBCR_BMSABMUSP5VoltOvr_V;
extern volatile uint8_T CcEBCR_BMSACellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSACellQuantityOvr_numb;
extern volatile uint8_T CcEBCR_BMSACellTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSACellTempMes1Ovr_C;
extern volatile real32_T CcEBCR_BMSACellTempMes2Ovr_C;
extern volatile real32_T CcEBCR_BMSACellTempMes3Ovr_C;
extern volatile real32_T CcEBCR_BMSACellTempMes4Ovr_C;
extern volatile real32_T CcEBCR_BMSACellTempMes5Ovr_C;
extern volatile real32_T CcEBCR_BMSACellTempMes6Ovr_C;
extern volatile real32_T CcEBCR_BMSAChargeCurrentMaxOvr_A;
extern volatile real32_T CcEBCR_BMSAChrgVoltMaxOvr_V;
extern volatile uint8_T CcEBCR_BMSACurRechrgEnergyStorSysIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSADTCFailureTypeByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSADTCHighByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSADTCLowByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSAFaultAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSAFaultChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSAHVBCPLngTrmChrgPwrOvr_kW;
extern volatile real32_T CcEBCR_BMSAHVBCPShrtTrmChrgPwrOvr_kW;
extern volatile real32_T CcEBCR_BMSAHVBDPShrtTrmDischrgPwrOvr_kW;
extern volatile uint8_T CcEBCR_BMSAHVBatSOCOvr_pct;
extern volatile uint8_T CcEBCR_BMSAHVCurrAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSAHVCurrChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSAHVIsoValueOvr_kOhm;
extern volatile real32_T CcEBCR_BMSAHeatSetTmpOvr_C;
extern volatile real32_T CcEBCR_BMSAHeatVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSAHwVersionOvr_numb;
extern volatile real32_T CcEBCR_BMSAISONegResOvr_kOhm;
extern volatile real32_T CcEBCR_BMSAISONegVoltOvr_V;
extern volatile real32_T CcEBCR_BMSAISOPosVoltOvr_V;
extern volatile real32_T CcEBCR_BMSAMaxBatTmpOvr_C;
extern volatile real32_T CcEBCR_BMSAMaxBatWaterTmpOutOvr_C;
extern volatile uint8_T CcEBCR_BMSAMaxCellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSAMaxCellTempNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSAMaxCellVoltNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSAMaxClVltOvr_mV;
extern volatile uint8_T CcEBCR_BMSAMaxTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSAMes1CellVoltOvr_mV;
extern volatile real32_T CcEBCR_BMSAMes2CellVoltOvr_mV;
extern volatile real32_T CcEBCR_BMSAMes3CellVoltOvr_mV;
extern volatile uint8_T CcEBCR_BMSAMesCellTempNumIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSAMesCellVoltNumIdxOvr_numb;
extern volatile real32_T CcEBCR_BMSAMinBatTmpOvr_C;
extern volatile real32_T CcEBCR_BMSAMinBatWaterTmpInOvr_C;
extern volatile uint8_T CcEBCR_BMSAMinCellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSAMinCellTempNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSAMinCellVoltNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSAMinClVltOvr_mV;
extern volatile uint8_T CcEBCR_BMSAMinTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSAPackCurrentOvr_A;
extern volatile uint8_T CcEBCR_BMSAPackNumIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSAPackNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSAPackProductionDateDayOvr_numb;
extern volatile uint8_T CcEBCR_BMSAPackProductionDateMonthOvr_numb;
extern volatile uint8_T CcEBCR_BMSAPackProductionDateYearOvr_numb;
extern volatile uint32_T CcEBCR_BMSAPackSNOvr_numb;
extern volatile real32_T CcEBCR_BMSAPackVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSAPeakSOPAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSAPeakSOPChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSAPreChrgHVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSARealSOCOvr_pct;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCode1Ovr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCode2Ovr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCode3Ovr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCode4Ovr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCodeIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysCodeLengthOvr_numb;
extern volatile uint8_T CcEBCR_BMSARechrgEnergyStorSysNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSARestEnergyOvr_kwH;
extern volatile real32_T CcEBCR_BMSASOEOvr_kWh;
extern volatile uint8_T CcEBCR_BMSASOHOvr_pct;
extern volatile uint8_T CcEBCR_BMSASOPAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSASOPChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSASOPosResOvr_kOhm;
extern volatile uint8_T CcEBCR_BMSASwVersionOvr_numb;
extern volatile uint8_T CcEBCR_BMSASysStatAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSASysStatChkSumOvr_numb;
extern volatile uint8_T CcEBCR_BMSATempProbeQuantifyOvr_numb;
extern volatile real32_T CcEBCR_BMSATotalBatCapOvr_Ah;
extern volatile real32_T CcEBCR_BMSBBMUSP2VoltOvr_V;
extern volatile real32_T CcEBCR_BMSBBMUSP3VoltOvr_V;
extern volatile real32_T CcEBCR_BMSBBMUSP4VoltOvr_V;
extern volatile real32_T CcEBCR_BMSBBMUSP5VoltOvr_V;
extern volatile uint8_T CcEBCR_BMSBCellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBCellQuantityOvr_numb;
extern volatile uint8_T CcEBCR_BMSBCellTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBCellTempMes1Ovr_C;
extern volatile real32_T CcEBCR_BMSBCellTempMes2Ovr_C;
extern volatile real32_T CcEBCR_BMSBCellTempMes3Ovr_C;
extern volatile real32_T CcEBCR_BMSBCellTempMes4Ovr_C;
extern volatile real32_T CcEBCR_BMSBCellTempMes5Ovr_C;
extern volatile real32_T CcEBCR_BMSBCellTempMes6Ovr_C;
extern volatile real32_T CcEBCR_BMSBChargeCurrentMaxOvr_A;
extern volatile real32_T CcEBCR_BMSBChrgVoltMaxOvr_V;
extern volatile uint8_T CcEBCR_BMSBCurRechrgEnergyStorSysIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSBDTCFailureTypeByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSBDTCHighByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSBDTCLowByteOvr_numb;
extern volatile uint8_T CcEBCR_BMSBFaultAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSBFaultChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSBHVBCPLngTrmChrgPwrOvr_kW;
extern volatile real32_T CcEBCR_BMSBHVBCPShrtTrmChrgPwrOvr_kW;
extern volatile real32_T CcEBCR_BMSBHVBDPShrtTrmDischrgPwrOvr_kW;
extern volatile uint8_T CcEBCR_BMSBHVBatSOCOvr_pct;
extern volatile uint8_T CcEBCR_BMSBHVCurrAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSBHVCurrChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSBHVIsoValueOvr_kOhm;
extern volatile real32_T CcEBCR_BMSBHeatSetTmpOvr_C;
extern volatile real32_T CcEBCR_BMSBHeatVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSBHwVersionOvr_numb;
extern volatile real32_T CcEBCR_BMSBISONegResOvr_kOhm;
extern volatile real32_T CcEBCR_BMSBISONegVoltOvr_V;
extern volatile real32_T CcEBCR_BMSBISOPosVoltOvr_V;
extern volatile real32_T CcEBCR_BMSBMaxBatTmpOvr_C;
extern volatile real32_T CcEBCR_BMSBMaxBatWaterTmpOutOvr_C;
extern volatile uint8_T CcEBCR_BMSBMaxCellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBMaxCellTempNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBMaxCellVoltNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBMaxClVltOvr_mV;
extern volatile uint8_T CcEBCR_BMSBMaxTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBMes1CellVoltOvr_mV;
extern volatile real32_T CcEBCR_BMSBMes2CellVoltOvr_mV;
extern volatile real32_T CcEBCR_BMSBMes3CellVoltOvr_mV;
extern volatile uint8_T CcEBCR_BMSBMesCellTempNumIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSBMesCellVoltNumIdxOvr_numb;
extern volatile real32_T CcEBCR_BMSBMinBatTmpOvr_C;
extern volatile real32_T CcEBCR_BMSBMinBatWaterTmpInOvr_C;
extern volatile uint8_T CcEBCR_BMSBMinCellBatNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBMinCellTempNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBMinCellVoltNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBMinClVltOvr_mV;
extern volatile uint8_T CcEBCR_BMSBMinTempBatNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBPackCurrentOvr_A;
extern volatile uint8_T CcEBCR_BMSBPackNumIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSBPackNumbOvr_numb;
extern volatile uint8_T CcEBCR_BMSBPackProductionDateDayOvr_numb;
extern volatile uint8_T CcEBCR_BMSBPackProductionDateMonthOvr_numb;
extern volatile uint8_T CcEBCR_BMSBPackProductionDateYearOvr_numb;
extern volatile uint32_T CcEBCR_BMSBPackSNOvr_numb;
extern volatile real32_T CcEBCR_BMSBPackVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSBPeakSOPAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSBPeakSOPChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSBPreChrgHVoltOvr_V;
extern volatile uint8_T CcEBCR_BMSBRealSOCOvr_pct;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCode1Ovr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCode2Ovr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCode3Ovr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCode4Ovr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCodeIdxOvr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysCodeLengthOvr_numb;
extern volatile uint8_T CcEBCR_BMSBRechrgEnergyStorSysNumbOvr_numb;
extern volatile real32_T CcEBCR_BMSBRestEnergyOvr_kwH;
extern volatile real32_T CcEBCR_BMSBSOEOvr_kWh;
extern volatile uint8_T CcEBCR_BMSBSOHOvr_pct;
extern volatile uint8_T CcEBCR_BMSBSOPAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSBSOPChkSumOvr_numb;
extern volatile real32_T CcEBCR_BMSBSOPosResOvr_kOhm;
extern volatile uint8_T CcEBCR_BMSBSwVersionOvr_numb;
extern volatile uint8_T CcEBCR_BMSBSysStatAliveCntOvr_numb;
extern volatile uint8_T CcEBCR_BMSBSysStatChkSumOvr_numb;
extern volatile uint8_T CcEBCR_BMSBTempProbeQuantifyOvr_numb;
extern volatile real32_T CcEBCR_BMSBTotalBatCapOvr_Ah;
extern volatile real32_T CcEBCR_PackALongDisChrgPwrOvr_kw;
extern volatile real32_T CcEBCR_PackAOutVoltOvr_V;
extern volatile real32_T CcEBCR_PackBLongDisChrgPwrOvr_kw;
extern volatile real32_T CcEBCR_PackBOutVoltOvr_V;
extern volatile uint8_T CeEBCR_BMSAFaultLevelOvr_enum;
extern volatile uint8_T CeEBCR_BMSAHVIsoWarningOvr_enum;
extern volatile uint8_T CeEBCR_BMSAHVSysStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAHeatMagCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAHeatModeSelOvr_enum;
extern volatile uint8_T CeEBCR_BMSAISODetStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAMainNegCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAMainPosCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPACK1RelayWaringOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPack1RechrgNegStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPack1RechrgPosStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPackBalanceTypeOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPackManufactureOvr_enum;
extern volatile uint8_T CeEBCR_BMSAPreChrgCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSASOCLowWarningOvr_enum;
extern volatile uint8_T CeEBCR_BMSBFaultLevelOvr_enum;
extern volatile uint8_T CeEBCR_BMSBHVIsoWarningOvr_enum;
extern volatile uint8_T CeEBCR_BMSBHVSysStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBHeatMagCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBHeatModeSelOvr_enum;
extern volatile uint8_T CeEBCR_BMSBISODetStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBMainNegCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBMainPosCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPACK1RelayWaringOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPack1RechrgNegStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPack1RechrgPosStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPackBalanceTypeOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPackManufactureOvr_enum;
extern volatile uint8_T CeEBCR_BMSBPreChrgCntStatOvr_enum;
extern volatile uint8_T CeEBCR_BMSBSOCLowWarningOvr_enum;

#endif                                 /* RTW_HEADER_EBCR_Cal_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
