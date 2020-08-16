



 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: Com / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#include "Com_Priv.h"
#include "Com_Cbk.h"
#include "PduR_Com.h"


/* START : Tx IPDU notification functions */
#ifdef COM_TxIPduNotification
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Tx Notification callback function for IPDU : EMS2_ConntSts_Rx_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_TxNotify_EMS2_ConntSts_Rx_Can_Network_CANNODE_3(void)
{
//    Rte_COMCbk_TMS_PS2_relayNeg_State_2();
//
//    Rte_COMCbk_TMS_PS2_relayPos_State_2();
//
//    Rte_COMCbk_TMS_PS1_relayNeg_State_2();
//
//    Rte_COMCbk_TMS_PS1_relayPos_State_2();
//
//    Rte_COMCbk_CrossrelayPos_State_2();
//
//    Rte_COMCbk_ACDC2_CrossrelayNeg_State_2();
//
//    Rte_COMCbk_ACDC2_CrossrelayPos_State_2();
//
//    Rte_COMCbk_ACDC1_CrossrelayNeg_State_2();
//
//    Rte_COMCbk_CrossrelayNeg_State_2();
//
//    Rte_COMCbk_ACDC1_CrossrelayPos_State_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Tx Notification callback function for IPDU : EMS_ConntSts_Rx_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_TxNotify_EMS_ConntSts_Rx_Can_Network_CANNODE_1(void)
{
//    Rte_COMCbk_TMS_PS2_relayNeg_State();
//
//    Rte_COMCbk_TMS_PS2_relayPos_State();
//
//    Rte_COMCbk_TMS_PS1_relayNeg_State();
//
//    Rte_COMCbk_TMS_PS1_relayPos_State();
//
//    Rte_COMCbk_CrossrelayPos_State();
//
//    Rte_COMCbk_ACDC2_CrossrelayNeg_State();
//
//    Rte_COMCbk_ACDC2_CrossrelayPos_State();
//
//    Rte_COMCbk_ACDC1_CrossrelayNeg_State();
//
//    Rte_COMCbk_CrossrelayNeg_State();
//
//    Rte_COMCbk_ACDC1_CrossrelayPos_State();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_TxIPduNotification */
/* END : Tx IPDU notification functions */
/* START : Tx IPDU error notification functions */
/* END : Tx IPDU error notification functions */
/* START : Tx IPDU timeout  notification functions */
#ifdef COM_TxIPduTimeOutNotify
#endif /* #ifdef COM_TxIPduTimeOutNotify */
/* END : Tx IPDU timeout  notification functions */


/* START : Rx IPDU timeout  notification functions */
#ifdef COM_RxIPduTimeoutNotify
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Cell_18042701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Cell_18042701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_Cell_18042701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_MaxClVlt_2();
//
//    Rte_COMCbkTOut_MaxCellVoltNumb_2();
//
//    Rte_COMCbkTOut_BMSMaxCellBatteryNumber_2();
//
//    Rte_COMCbkTOut_MinClVlt_2();
//
//    Rte_COMCbkTOut_MinCellVoltNumb_2();
//
//    Rte_COMCbkTOut_BMSMinCellBatteryNumber_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_ConntSts_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_ConntSts_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_ConntSts_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_Pack1_RechrNeg_State_2();
//
//    Rte_COMCbkTOut_Pack1_RechrPos_State_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Fault_18072701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Fault_18072701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_Fault_18072701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMS_Fault_AliveCounter_2();
//
//    Rte_COMCbkTOut_HVIsoWarning_2();
//
//    Rte_COMCbkTOut_HVILWarning_2();
//
//    Rte_COMCbkTOut_SOCLowWarning_2();
//
//    Rte_COMCbkTOut_TempDiffWarning_2();
//
//    Rte_COMCbkTOut_TempHighWarning_2();
//
//    Rte_COMCbkTOut_PackOvWarning_2();
//
//    Rte_COMCbkTOut_PackUvWarning_2();
//
//    Rte_COMCbkTOut_CellOvWarning_2();
//
//    Rte_COMCbkTOut_CellUvWarning_2();
//
//    Rte_COMCbkTOut_SOCHighWarning_2();
//
//    Rte_COMCbkTOut_SOCFastChgWarning_2();
//
//    Rte_COMCbkTOut_PwrBatPackMismatchWarning_2();
//
//    Rte_COMCbkTOut_BMSCelConsistencyWarning_2();
//
//    Rte_COMCbkTOut_BMSVolHighWarning_2();
//
//    Rte_COMCbkTOut_PackOCWarning_2();
//
//    Rte_COMCbkTOut_BMSPACK1_RelayWaring_2();
//
//    Rte_COMCbkTOut_BMSPACK2_RelayWaring_2();
//
//    Rte_COMCbkTOut_BMSPACK3_RelayWaring_2();
//
//    Rte_COMCbkTOut_BMSPACK4_RelayWaring_2();
//
//    Rte_COMCbkTOut_RestEnergy_2();
//
//    Rte_COMCbkTOut_BMS_Fault_CheckSum_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_HV2_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_HV2_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_HV2_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMU_SP5Volt_2();
//
//    Rte_COMCbkTOut_BMU_SP4Volt_2();
//
//    Rte_COMCbkTOut_BMU_SP3Volt_2();
//
//    Rte_COMCbkTOut_BMU_SP2Volt_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMS_HVCurr_AliveCounter_2();
//
//    Rte_COMCbkTOut_PackVoltVld_2();
//
//    Rte_COMCbkTOut_PackVolt_2();
//
//    Rte_COMCbkTOut_PackCurrentVld_2();
//
//    Rte_COMCbkTOut_PackCurrent_2();
//
//    Rte_COMCbkTOut_BMS_HVCurr_CheckSum_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_LongSOP_18032701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMS_SOP_AliveCounter_2();
//
//    Rte_COMCbkTOut_HVBatSOC_2();
//
//    Rte_COMCbkTOut_HVBCP_LngTrmChrgPwr_2();
//
//    Rte_COMCbkTOut_HVBDP_LngTrmDischrgPwr_2();
//
//    Rte_COMCbkTOut_BMS_SOP_CheckSum_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_SystPara_18012701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_SystPara_18012701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_SystPara_18012701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMSCellQuantity_2();
//
//    Rte_COMCbkTOut_RealSOC_2();
//
//    Rte_COMCbkTOut_BMSTempProbeQuantity_2();
//
//    Rte_COMCbkTOut_HVIsoValue_2();
//
//    Rte_COMCbkTOut_SOH_2();
//
//    Rte_COMCbkTOut_SOE_2();
//
//    Rte_COMCbkTOut_TotalBatteryCap_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_SystStat_18122701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_SystStat_18122701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_SystStat_18122701h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_BMS_SysStat_AliveCounter_2();
//
//    Rte_COMCbkTOut_HeatMagCntStat_2();
//
//    Rte_COMCbkTOut_HVSystemStatus_2();
//
//    Rte_COMCbkTOut_BMSFaultLevel_2();
//
//    Rte_COMCbkTOut_IsoDetStat_2();
//
//    Rte_COMCbkTOut_HVShutdownReq_2();
//
//    Rte_COMCbkTOut_ChargeVoltMax_2();
//
//    Rte_COMCbkTOut_HCUPowerCtrl_2();
//
//    Rte_COMCbkTOut_HeatModeSelect_2();
//
//    Rte_COMCbkTOut_MainPosCntStat_2();
//
//    Rte_COMCbkTOut_MainNegCntStat_2();
//
//    Rte_COMCbkTOut_PreChrgCntStat_2();
//
//    Rte_COMCbkTOut_ChargeCurrentMax_2();
//
//    Rte_COMCbkTOut_Pack_Manufacture_2();
//
//    Rte_COMCbkTOut_Pack_BalanceType_2();
//
//    Rte_COMCbkTOut_BMS_SysStat_CheckSum_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Temp_18152701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Temp_18152701h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_BMS2_Temp_18152701h_Can_Network_CANNODE_3();
//
//    Rte_COMCbkTOut_MinBatTmp_2();
//
//    Rte_COMCbkTOut_MinCellTempNumb_2();
//
//    Rte_COMCbkTOut_MaxBatTmp_2();
//
//    Rte_COMCbkTOut_MaxCellTempNumb_2();
//
//    Rte_COMCbkTOut_BMSMaxTempBatteryNumber_2();
//
//    Rte_COMCbkTOut_BMSMinTempBatteryNumber_2();
//
//    Rte_COMCbkTOut_HeatSetTmp_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Cell_18042701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Cell_18042701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_Cell_18042701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_MaxClVlt();
//
//    Rte_COMCbkTOut_MaxCellVoltNumb();
//
//    Rte_COMCbkTOut_BMSMaxCellBatteryNumber();
//
//    Rte_COMCbkTOut_MinClVlt();
//
//    Rte_COMCbkTOut_MinCellVoltNumb();
//
//    Rte_COMCbkTOut_BMSMinCellBatteryNumber();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_ConntSts_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_ConntSts_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_ConntSts_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_Pack1_RechrNeg_State();
//
//    Rte_COMCbkTOut_Pack1_RechrPos_State();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Fault_18072701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Fault_18072701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_Fault_18072701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_BMS_Fault_AliveCounter();
//
//    Rte_COMCbkTOut_HVIsoWarning();
//
//    Rte_COMCbkTOut_HVILWarning();
//
//    Rte_COMCbkTOut_SOCLowWarning();
//
//    Rte_COMCbkTOut_TempDiffWarning();
//
//    Rte_COMCbkTOut_TempHighWarning();
//
//    Rte_COMCbkTOut_PackOvWarning();
//
//    Rte_COMCbkTOut_PackUvWarning();
//
//    Rte_COMCbkTOut_CellOvWarning();
//
//    Rte_COMCbkTOut_CellUvWarning();
//
//    Rte_COMCbkTOut_SOCHighWarning();
//
//    Rte_COMCbkTOut_SOCFastChgWarning();
//
//    Rte_COMCbkTOut_PwrBatPackMismatchWarning();
//
//    Rte_COMCbkTOut_BMSCelConsistencyWarning();
//
//    Rte_COMCbkTOut_BMSVolHighWarning();
//
//    Rte_COMCbkTOut_PackOCWarning();
//
//    Rte_COMCbkTOut_BMSPACK1_RelayWaring();
//
//    Rte_COMCbkTOut_BMSPACK2_RelayWaring();
//
//    Rte_COMCbkTOut_BMSPACK3_RelayWaring();
//
//    Rte_COMCbkTOut_BMSPACK4_RelayWaring();
//
//    Rte_COMCbkTOut_RestEnergy();
//
//    Rte_COMCbkTOut_BMS_Fault_CheckSum();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV2_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV2_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_HV2_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_BMU_SP5Volt();
//
//    Rte_COMCbkTOut_BMU_SP4Volt();
//
//    Rte_COMCbkTOut_BMU_SP3Volt();
//
//    Rte_COMCbkTOut_BMU_SP2Volt();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV_18022701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV_18022701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_HV_18022701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_PreChrgHVolt();
//
//    Rte_COMCbkTOut_HeatVolt();
//
//    Rte_COMCbkTOut_MinBatWaterTmpIn();
//
//    Rte_COMCbkTOut_MaxBatWaterTmpOut();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV_Curr_18102701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_PackVoltVld();
//
//    Rte_COMCbkTOut_PackVolt();
//
//    Rte_COMCbkTOut_PackCurrentVld();
//
//    Rte_COMCbkTOut_PackCurrent();
//
//    Rte_COMCbkTOut_BMS_HVCurr_CheckSum();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_LongSOP_18032701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_LongSOP_18032701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_LongSOP_18032701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_HVBatSOC();
//
//    Rte_COMCbkTOut_HVBCP_LngTrmChrgPwr();
//
//    Rte_COMCbkTOut_HVBDP_LngTrmDischrgPwr();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_SystPara_18012701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_SystPara_18012701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_SystPara_18012701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_BMSCellQuantity();
//
//    Rte_COMCbkTOut_RealSOC();
//
//    Rte_COMCbkTOut_BMSTempProbeQuantity();
//
//    Rte_COMCbkTOut_HVIsoValue();
//
//    Rte_COMCbkTOut_SOH();
//
//    Rte_COMCbkTOut_SOE();
//
//    Rte_COMCbkTOut_TotalBatteryCap();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_SystStat_18122701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_SystStat_18122701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_SystStat_18122701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_BMS_SysStat_AliveCounter();
//
//    Rte_COMCbkTOut_HeatMagCntStat();
//
//    Rte_COMCbkTOut_HVSystemStatus();
//
//    Rte_COMCbkTOut_BMSFaultLevel();
//
//    Rte_COMCbkTOut_IsoDetStat();
//
//    Rte_COMCbkTOut_HVShutdownReq();
//
//    Rte_COMCbkTOut_ChargeVoltMax();
//
//    Rte_COMCbkTOut_HCUPowerCtrl();
//
//    Rte_COMCbkTOut_HeatModeSelect();
//
//    Rte_COMCbkTOut_MainPosCntStat();
//
//    Rte_COMCbkTOut_MainNegCntStat();
//
//    Rte_COMCbkTOut_PreChrgCntStat();
//
//    Rte_COMCbkTOut_ChargeCurrentMax();
//
//    Rte_COMCbkTOut_Pack_Manufacture();
//
//    Rte_COMCbkTOut_Pack_BalanceType();
//
//    Rte_COMCbkTOut_BMS_SysStat_CheckSum();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Temp_18152701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Temp_18152701h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_BMS_Temp_18152701h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_MinBatTmp();
//
//    Rte_COMCbkTOut_MinCellTempNumb();
//
//    Rte_COMCbkTOut_MaxBatTmp();
//
//    Rte_COMCbkTOut_MaxCellTempNumb();
//
//    Rte_COMCbkTOut_BMSMaxTempBatteryNumber();
//
//    Rte_COMCbkTOut_BMSMinTempBatteryNumber();
//
//    Rte_COMCbkTOut_HeatSetTmp();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3();
//
//    Rte_COMCbkTOut_CCU_GUN_position_2();
//
//    Rte_COMCbkTOut_CCU_Pyroswitch_CMD_2();
//
//    Rte_COMCbkTOut_CCU_SysStat_AliveCounter_2();
//
//    Rte_COMCbkTOut_CCU_STATE_2();
//
//    Rte_COMCbkTOut_CCU_FUSE1_STATE_2();
//
//    Rte_COMCbkTOut_CCU_ISO_STATE_2();
//
//    Rte_COMCbkTOut_CCU_GUN_TEMP2_STATE_2();
//
//    Rte_COMCbkTOut_CCU_GUN_TEMP1_STATE_2();
//
//    Rte_COMCbkTOut_CCU_CC1_STATE_2();
//
//    Rte_COMCbkTOut_CCU_K1K3_STATE_2();
//
//    Rte_COMCbkTOut_CCU_K2K4_STATE_2();
//
//    Rte_COMCbkTOut_CCU_ELOCK_STATE_2();
//
//    Rte_COMCbkTOut_CCU_CAR_CONNECTSTATE_2();
//
//    Rte_COMCbkTOut_CCU_FaultSevtyStat_2();
//
//    Rte_COMCbkTOut_CCU_12V_STATE_2();
//
//    Rte_COMCbkTOut_CCU_24V_STATE_2();
//
//    Rte_COMCbkTOut_CCU_Index_2();
//
//    Rte_COMCbkTOut_CCU_ISOCheckFinish_flg_2();
//
//    Rte_COMCbkTOut_CCUSwVersion_2();
//
//    Rte_COMCbkTOut_CCUHwVersion_2();
//
//    Rte_COMCbkTOut_CCU_SysStat_CheckSum_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_CCU_GUN_position();
//
//    Rte_COMCbkTOut_CCU_Pyroswitch_CMD();
//
//    Rte_COMCbkTOut_CCU_SysStat_AliveCounter();
//
//    Rte_COMCbkTOut_CCU_STATE();
//
//    Rte_COMCbkTOut_CCU_FUSE1_STATE();
//
//    Rte_COMCbkTOut_CCU_ISO_STATE();
//
//    Rte_COMCbkTOut_CCU_GUN_TEMP2_STATE();
//
//    Rte_COMCbkTOut_CCU_GUN_TEMP1_STATE();
//
//    Rte_COMCbkTOut_CCU_CC1_STATE();
//
//    Rte_COMCbkTOut_CCU_K1K3_STATE();
//
//    Rte_COMCbkTOut_CCU_K2K4_STATE();
//
//    Rte_COMCbkTOut_CCU_ELOCK_STATE();
//
//    Rte_COMCbkTOut_CCU_CAR_CONNECTSTATE();
//
//    Rte_COMCbkTOut_CCU_FaultSevtyStat();
//
//    Rte_COMCbkTOut_CCU_12V_STATE();
//
//    Rte_COMCbkTOut_CCU_24V_STATE();
//
//    Rte_COMCbkTOut_CCU_Index();
//
//    Rte_COMCbkTOut_CCU_ISOCheckFinish_flg();
//
//    Rte_COMCbkTOut_CCUSwVersion();
//
//    Rte_COMCbkTOut_CCUHwVersion();
//
//    Rte_COMCbkTOut_CCU_SysStat_CheckSum();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : HCU2_Syst_18220145h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_HCU2_Syst_18220145h_Can_Network_CANNODE_3(void)
{
    Com_RxTOCbk_HCU2_Syst_18220145h_Can_Network_CANNODE_3();

//    Rte_COMCbkTOut_HCUWaterTmpIn_2();
//
//    Rte_COMCbkTOut_HCUWaterTmpOut_2();
//
//    Rte_COMCbkTOut_HCUSystemMode_2();
//
//    Rte_COMCbkTOut_HCUPowerReq_2();
//
//    Rte_COMCbkTOut_HCUCntStat_2();
//
//    Rte_COMCbkTOut_HCUFaultStat_2();
//
//    Rte_COMCbkTOut_HCUFaultSevtyStat_2();
//
//    Rte_COMCbkTOut_HCUPowerDemand_2();
//
//    Rte_COMCbkTOut_HCUEnvTemp_A_2();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : HCU_Syst_18220145h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_HCU_Syst_18220145h_Can_Network_CANNODE_1(void)
{
    Com_RxTOCbk_HCU_Syst_18220145h_Can_Network_CANNODE_1();

//    Rte_COMCbkTOut_HCUWaterTmpIn();
//
//    Rte_COMCbkTOut_HCUWaterTmpOut();
//
//    Rte_COMCbkTOut_HCUSystemMode();
//
//    Rte_COMCbkTOut_HCUPowerReq();
//
//    Rte_COMCbkTOut_HCUCntStat();
//
//    Rte_COMCbkTOut_HCUFaultStat();
//
//    Rte_COMCbkTOut_HCUFaultSevtyStat();
//
//    Rte_COMCbkTOut_HCUPowerDemand();
//
//    Rte_COMCbkTOut_HCUEnvTemp_A();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : TBOX_0x1803F102_Can_Network_CANNODE_5 */
FUNC(void,COM_CODE) Com_RxTONotify_TBOX_0x1803F102_Can_Network_CANNODE_5(void)
{
    Com_RxTOCbk_TBOX_0x1803F102_Can_Network_CANNODE_5();

//    Rte_COMCbkTOut_TFD_TBOXTimer_Invalid();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Year();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Month();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Day();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Hour();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Minute();
//
//    Rte_COMCbkTOut_TFD_TBOXTimer_Second();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : TBOX_0x1804F102_Can_Network_CANNODE_5 */
FUNC(void,COM_CODE) Com_RxTONotify_TBOX_0x1804F102_Can_Network_CANNODE_5(void)
{
    Com_RxTOCbk_TBOX_0x1804F102_Can_Network_CANNODE_5();

//    Rte_COMCbkTOut_TFD_TBOX_network_Status();
//
//    Rte_COMCbkTOut_TFD_SysStat_AliveCounter();
//
//    Rte_COMCbkTOut_TFD_Ethernet_Signal_Quality();
//
//    Rte_COMCbkTOut_TFD_GPS_Signal_Quality();
//
//    Rte_COMCbkTOut_TFD_WIFI_Signal_Quality();
//
//    Rte_COMCbkTOut_TFD_BLE_Signal_Quality();
//
//    Rte_COMCbkTOut_TFD_Wlan_Signal_Quality();
//
//    Rte_COMCbkTOut_TFD_TBOX_Status();
//
//    Rte_COMCbkTOut_TFD_SysStat_CheckSum();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* #ifdef COM_RxIPduTimeoutNotify */

/* END : Rx IPDU timeout  notification functions */

/* START: TMS NONE Details  */

#define COM_START_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"
CONST(Com_TransModeInfo, COM_CONST) Com_NONE_TransModeInfo =
{
    0, /* TimePeriodFact */
    0, /* TimeOffsetFact */

    0, /* RepetitionPeriodFact */
    0,  /* NumRepetitions */

#ifdef COM_MIXEDPHASESHIFT
    COM_TXMODE_NONE, /* Mode */
    COM_FALSE   /* MixedPhaseShift status */
#else

    COM_TXMODE_NONE /* Mode */

#endif /* #ifdef COM_MIXEDPHASESHIFT */

};
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "Com_MemMap.h"

/* END: TMS NONE Details  */






#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"
VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector;

VAR(Com_IpduGroupVector, COM_VAR) Com_IpduGrpVector_DM;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Com_MemMap.h"


