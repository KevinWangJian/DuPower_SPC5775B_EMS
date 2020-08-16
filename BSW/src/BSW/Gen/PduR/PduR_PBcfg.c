

 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#include "PduR_PBcfg.h"
#include "PduR_UpIf.h"

#include "PduR_LoIfTT.h"

#include "PduR_LoIf.h"
#include "PduR_LoTp.h"

#include "PduR_UpTp.h"

#include "PduR_Mc.h"
#include "PduR_Gw.h"


#include "PduR_Gw_Cfg.h"
/* Generating PbCfg_c::PduR_UpIfToLo_PBcfg_c::upIf_To_Lo */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
#define PduR_comToLo   NULL_PTR
#else
static CONST(PduR_RT_UpToLo,PDUR_CONST ) PduR_comToLo[] = {
    { CanIfConf_CanIfTxPduCfg_AFC2_Confirm_Status_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC2_Confirm_Status_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_AFC_Confirm_Status_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC_Confirm_Status_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC_SafeCertif_Confirm_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame1_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame2_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame3_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame4_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame5_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*DCDCModuleFrame6_Tx_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180102F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180102F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180202F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180202F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180302F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180302F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180402F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180402F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180502F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180502F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180602F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180602F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180702F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180702F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180802F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180802F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180902F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180902F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180A02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180A02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180B02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180B02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180C02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180C02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180D02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180D02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180E02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180E02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x180F02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x180F02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181002F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181002F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181102F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181102F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181202F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181202F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181302F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181302F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181402F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181402F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181502F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181502F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181602F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181602F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181702F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181702F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181802F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181802F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181902F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181902F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181A02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181A02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_0x181D02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_0x181D02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_CML_1805FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_ConntSts_Rx_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_ConntSts_Rx_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_Res_0x181E02F1_Can_Network_CANNODE_6_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180102F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180102F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180202F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180202F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180302F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180302F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180402F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180402F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180502F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180502F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180602F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180602F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180702F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180702F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180802F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180802F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180902F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180902F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180A02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180A02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180B02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180B02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180C02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180C02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180D02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180D02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180E02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180E02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x180F02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x180F02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181002F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181002F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181102F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181102F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181202F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181202F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181302F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181302F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181402F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181402F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181502F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181502F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181602F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181602F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181702F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181702F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181802F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181802F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181902F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181902F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181A02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181A02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_0x181D02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_0x181D02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_18F82B62h_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_18F82B62h_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_CML_1805FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_CML_1805FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_ConntSts_Rx_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_ConntSts_Rx_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_Connt_1807FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_HCU_1814FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_HV1_1810FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_HV2_1811FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_Msg_1806E5F4h_Can_Network_CANNODE_4_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_Res_0x181E02F1_Can_Network_CANNODE_5 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_Res_0x181E02F1_Can_Network_CANNODE_5_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_Timer_1809FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*EMS_Warning_1808FAF1h_Can_Network_CANNODE_1_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3_Com2PduR*/
    { CanIfConf_CanIfTxPduCfg_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1 , (PduR_loTransmitFP)PduR_RF_CanIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit },    /*TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1_Com2PduR*/
    { SoAdConf_SoAdPduRoute_PduTriggering_TX_EthernetPhysicalChannel , (PduR_loTransmitFP)PduR_RF_SoAdIf_Transmit, (PduR_loCancelTransmitFP)PduR_IH_CancelTransmit }    /*EthernetPdu_Tx_Com2PduR*/


};
#endif /* PDUR_CONFIG_SINGLE_IFTX_LO */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


/* Generating PbCfg_c::PduR_UpTpToLo_PBcfg_c::upTp_To_Lo */


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_DcmToLo NULL_PTR
#else
static CONST(PduR_RT_UpToLo,PDUR_CONST ) PduR_DcmToLo[] = {
    { CanTpConf_CanTpTxNSdu_CanTpTxNSdu, (PduR_loTransmitFP)PduR_RF_CanTp_Transmit, (PduR_loCancelTransmitFP)PduR_RF_CanTp_CancelTransmit }    /*EMS_DiagResp_0x18DAFAF1h_Can_Network_CANNODE_2_Phys_Dcm2PduR*/

};
#endif /* PDUR_CONFIG_SINGLE_IFTX_LO */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

/* Generating PbCfg_c::PduR_LoIfRxToUp_PBcfg_c::loIfRx_To_Up */
    
        

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_CanIfRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoIfRxToUp, PDUR_CONST ) PduR_CanIfRxToUp[] = {        
    { IpduMConf_IpduMRxIndication_AFC2_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_3_PduR2IpduM, (PduR_upIfRxIndicationFP) PduR_RF_IpduM_RxIndication },   /*AFC2_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_SafeCertif_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_SafeCertif_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Serial_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Serial_Can_Network_CANNODE_3_CanIf2PduR*/        
    { IpduMConf_IpduMRxIndication_AFC_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_1_PduR2IpduM, (PduR_upIfRxIndicationFP) PduR_RF_IpduM_RxIndication },   /*AFC_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_SafeCertif_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_SafeCertif_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Serial_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Serial_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_Cell_18042701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_Cell_18042701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_ConntSts_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_ConntSts_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_DTC_18AA2701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_DTC_18AA2701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_DetCell_18052701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_DetCell_18052701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_DetTemp_18062701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_DetTemp_18062701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_Fault_18072701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_Fault_18072701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_HV2_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_HV2_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_HV_18022701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_HV_18022701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_ISO_18162701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_ISO_18162701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_Info_18082701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_Info_18082701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_LongSOP_18032701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_PackInfo_18142701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_PackInfo_18142701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_PeskSOP_18172701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_PeskSOP_18172701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_SystPara_18012701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_SystPara_18012701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_SystStat_18122701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_SystStat_18122701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS2_Temp_18152701h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS2_Temp_18152701h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_Cell_18042701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_Cell_18042701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_ConntSts_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_ConntSts_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_DTC_18AA2701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_DTC_18AA2701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_DetCell_18052701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_DetCell_18052701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_DetTemp_18062701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_DetTemp_18062701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_Fault_18072701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_Fault_18072701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_HV2_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_HV2_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_HV_18022701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_HV_18022701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_HV_Curr_18102701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_ISO_18162701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_ISO_18162701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_Info_18082701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_Info_18082701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_LongSOP_18032701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_LongSOP_18032701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_PackInfo_18142701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_PackInfo_18142701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_PeskSOP_18172701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_PeskSOP_18172701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_SystPara_18012701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_SystPara_18012701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_SystStat_18122701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_SystStat_18122701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_BMS_Temp_18152701h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*BMS_Temp_18152701h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_CCS_1819FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_CCS_1819FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_CSTCEM_181DFAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_CSTCEM_181DFAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_ConntSts_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_ConntSts_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_DTC_18AAFAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_DTC_18AAFAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_HV_1802FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_HV_1802FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_ISO_1820FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_ISO_1820FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_Sample_1803FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_Sample_1803FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VIN_1816FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VIN_1816FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBCL_1817FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBCL_1817FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBCP1_1812FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBCP1_1812FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBCP2_1813FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBCP2_1813FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBCS_1818FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBCS_1818FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBHM_1811FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBHM_1811FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBRM1_1814FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBRM1_1814FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBRM2_1815FAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBRM2_1815FAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBSD_181BFAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBSD_181BFAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBSM_181AFAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBSM_181AFAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU2_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU2_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_CCS_1819FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_CCS_1819FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_CSTCEM_181DFAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_CSTCEM_181DFAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_ConntSts_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_ConntSts_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_DTC_18AAFAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_DTC_18AAFAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_HV_1802FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_HV_1802FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_ISO_1820FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_ISO_1820FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_Sample_1803FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_Sample_1803FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VIN_1816FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VIN_1816FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBCL_1817FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBCL_1817FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBCP1_1812FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBCP1_1812FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBCP2_1813FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBCP2_1813FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBCS_1818FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBCS_1818FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBHM_1811FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBHM_1811FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBRM1_1814FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBRM1_1814FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBRM2_1815FAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBRM2_1815FAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBSD_181BFAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBSD_181BFAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBSM_181AFAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBSM_181AFAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_CCU_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*CCU_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame10_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame10_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame11_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame11_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame1_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame1_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame2_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame2_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame3_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame3_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame4_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame4_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame5_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame5_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame6_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame6_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame7_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame7_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame8_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame8_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDCModuleFrame9_Rx_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDCModuleFrame9_Rx_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDC_1_18F8622Bh_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDC_1_18F8622Bh_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDC_2_18F8622Ch_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDC_2_18F8622Ch_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDC_3_18F8622Dh_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDC_3_18F8622Dh_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDC_Msg1_18FF50E5h_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDC_Msg1_18FF50E5h_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_DCDC_Msg2_18FF51E5h_Can_Network_CANNODE_4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*DCDC_Msg2_18FF51E5h_Can_Network_CANNODE_4_CanIf2PduR*/        
    { ComConf_ComIPdu_HCU2_Syst_18220145h_Can_Network_CANNODE_3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*HCU2_Syst_18220145h_Can_Network_CANNODE_3_CanIf2PduR*/        
    { ComConf_ComIPdu_HCU_Syst_18220145h_Can_Network_CANNODE_1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*HCU_Syst_18220145h_Can_Network_CANNODE_1_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1801F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1801F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1802F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1802F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1803F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1803F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1804F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1804F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1805F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1805F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1806F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1806F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1807F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1807F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1808F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1808F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x1809F102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x1809F102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180AF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180AF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180BF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180BF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180CF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180CF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180DF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180DF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180EF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180EF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x180FF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x180FF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX2_0x18FFF102_Can_Network_CANNODE_6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX2_0x18FFF102_Can_Network_CANNODE_6_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1801F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1801F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1802F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1802F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1803F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1803F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1804F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1804F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1805F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1805F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1806F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1806F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1807F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1807F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1808F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1808F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x1809F102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x1809F102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180AF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180AF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180BF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180BF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180CF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180CF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180DF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180DF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180EF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180EF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x180FF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x180FF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { ComConf_ComIPdu_TBOX_0x18FFF102_Can_Network_CANNODE_5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*TBOX_0x18FFF102_Can_Network_CANNODE_5_CanIf2PduR*/        
    { IpduMConf_IpduMRxIndication_Tester2_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_3_PduR2IpduM, (PduR_upIfRxIndicationFP) PduR_RF_IpduM_RxIndication },   /*Tester2_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_3_CanIf2PduR*/        
    { IpduMConf_IpduMRxIndication_Tester_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_1_PduR2IpduM, (PduR_upIfRxIndicationFP) PduR_RF_IpduM_RxIndication }    /*Tester_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_1_CanIf2PduR*/
 };
#endif  /* PDUR_CONFIG_SINGLE_IFRX */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


        

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_IpduMRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoIfRxToUp, PDUR_CONST ) PduR_IpduMRxToUp[] = {        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX10, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX10_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX11, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX11_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX1_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX2, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX2_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX3_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX4_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX5_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX6_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX8, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX8_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC2_EOLTester_Confirm_MUX9, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC2_EOLTester_Confirm_MUX9_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX10, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX10_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX11, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX11_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX1_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX2, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX2_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX3, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX3_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX4, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX4_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX5, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX5_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX6, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX6_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX8, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX8_IpduM2PduR*/        
    { ComConf_ComIPdu_AFC_EOLTester_Confirm_MUX9, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*AFC_EOLTester_Confirm_MUX9_IpduM2PduR*/        
    { ComConf_ComIPdu_Tester2_18FFFA01h_MUX1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication },   /*Tester2_18FFFA01h_MUX1_IpduM2PduR*/        
    { ComConf_ComIPdu_Tester_18FFFA01h_MUX1, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication }    /*Tester_18FFFA01h_MUX1_IpduM2PduR*/
 };
#endif  /* PDUR_CONFIG_SINGLE_IFRX */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


        
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_SoAdIfRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoIfRxToUp, PDUR_CONST ) PduR_SoAdIfRxToUp[] = {        
    { ComConf_ComIPdu_EthernetPdu_Rx_EthernetPhysicalChannel_Rx, (PduR_upIfRxIndicationFP) PduR_RF_Com_RxIndication }    /*EthernetPdu_Rx_SoAd2PduR*/
 };
#endif  /* PDUR_CONFIG_SINGLE_IFRX */
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
    
/* Generating PbCfg_c::PduR_LoIfDTxToUp_PBcfg_c::loIf_DTxToUp */
    
        

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP )
#define PduR_CanIfTxToUp NULL_PTR
#else

static CONST(PduR_RT_LoIfTxToUp, PDUR_CONST ) PduR_CanIfTxToUp [] = { 
{ ComConf_ComIPdu_AFC2_Confirm_Status_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 0  SrcPdu: AFC2_Confirm_Status_Can_Network_CANNODE_3_Com2PduR  DestPdu: AFC2_Confirm_Status_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 1  SrcPdu: AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3_Com2PduR  DestPdu: AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 2  SrcPdu: AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3_Com2PduR  DestPdu: AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_AFC_Confirm_Status_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 3  SrcPdu: AFC_Confirm_Status_Can_Network_CANNODE_1_Com2PduR  DestPdu: AFC_Confirm_Status_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 4  SrcPdu: AFC_SafeCertif_Confirm_Can_Network_CANNODE_1_Com2PduR  DestPdu: AFC_SafeCertif_Confirm_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 5  SrcPdu: AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1_Com2PduR  DestPdu: AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 6  SrcPdu: DCDCModuleFrame1_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame1_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 7  SrcPdu: DCDCModuleFrame2_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame2_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 8  SrcPdu: DCDCModuleFrame3_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame3_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 9  SrcPdu: DCDCModuleFrame4_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame4_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 10  SrcPdu: DCDCModuleFrame5_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame5_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 11  SrcPdu: DCDCModuleFrame6_Tx_Can_Network_CANNODE_4_Com2PduR  DestPdu: DCDCModuleFrame6_Tx_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180102F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 12  SrcPdu: EMS2_0x180102F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180102F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180202F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 13  SrcPdu: EMS2_0x180202F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180202F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180302F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 14  SrcPdu: EMS2_0x180302F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180302F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180402F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 15  SrcPdu: EMS2_0x180402F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180402F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180502F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 16  SrcPdu: EMS2_0x180502F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180502F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180602F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 17  SrcPdu: EMS2_0x180602F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180602F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180702F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 18  SrcPdu: EMS2_0x180702F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180702F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180802F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 19  SrcPdu: EMS2_0x180802F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180802F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180902F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 20  SrcPdu: EMS2_0x180902F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180902F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180A02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 21  SrcPdu: EMS2_0x180A02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180A02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180B02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 22  SrcPdu: EMS2_0x180B02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180B02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180C02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 23  SrcPdu: EMS2_0x180C02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180C02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180D02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 24  SrcPdu: EMS2_0x180D02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180D02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180E02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 25  SrcPdu: EMS2_0x180E02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180E02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x180F02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 26  SrcPdu: EMS2_0x180F02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x180F02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181002F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 27  SrcPdu: EMS2_0x181002F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181002F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181102F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 28  SrcPdu: EMS2_0x181102F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181102F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181202F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 29  SrcPdu: EMS2_0x181202F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181202F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181302F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 30  SrcPdu: EMS2_0x181302F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181302F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181402F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 31  SrcPdu: EMS2_0x181402F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181402F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181502F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 32  SrcPdu: EMS2_0x181502F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181502F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181602F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 33  SrcPdu: EMS2_0x181602F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181602F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181702F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 34  SrcPdu: EMS2_0x181702F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181702F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181802F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 35  SrcPdu: EMS2_0x181802F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181802F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181902F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 36  SrcPdu: EMS2_0x181902F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181902F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181A02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 37  SrcPdu: EMS2_0x181A02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181A02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_0x181D02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 38  SrcPdu: EMS2_0x181D02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_0x181D02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 39  SrcPdu: EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 40  SrcPdu: EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 41  SrcPdu: EMS2_CML_1805FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_CML_1805FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 42  SrcPdu: EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_ConntSts_Rx_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 43  SrcPdu: EMS2_ConntSts_Rx_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_ConntSts_Rx_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 44  SrcPdu: EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 45  SrcPdu: EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 46  SrcPdu: EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 47  SrcPdu: EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 48  SrcPdu: EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 49  SrcPdu: EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 50  SrcPdu: EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 51  SrcPdu: EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 52  SrcPdu: EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 53  SrcPdu: EMS2_Res_0x181E02F1_Can_Network_CANNODE_6_Com2PduR  DestPdu: EMS2_Res_0x181E02F1_Can_Network_CANNODE_6_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 54  SrcPdu: EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 55  SrcPdu: EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 56  SrcPdu: EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3_Com2PduR  DestPdu: EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180102F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 57  SrcPdu: EMS_0x180102F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180102F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180202F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 58  SrcPdu: EMS_0x180202F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180202F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180302F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 59  SrcPdu: EMS_0x180302F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180302F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180402F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 60  SrcPdu: EMS_0x180402F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180402F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180502F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 61  SrcPdu: EMS_0x180502F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180502F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180602F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 62  SrcPdu: EMS_0x180602F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180602F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180702F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 63  SrcPdu: EMS_0x180702F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180702F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180802F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 64  SrcPdu: EMS_0x180802F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180802F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180902F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 65  SrcPdu: EMS_0x180902F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180902F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180A02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 66  SrcPdu: EMS_0x180A02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180A02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180B02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 67  SrcPdu: EMS_0x180B02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180B02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180C02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 68  SrcPdu: EMS_0x180C02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180C02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180D02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 69  SrcPdu: EMS_0x180D02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180D02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180E02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 70  SrcPdu: EMS_0x180E02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180E02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x180F02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 71  SrcPdu: EMS_0x180F02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x180F02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181002F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 72  SrcPdu: EMS_0x181002F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181002F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181102F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 73  SrcPdu: EMS_0x181102F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181102F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181202F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 74  SrcPdu: EMS_0x181202F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181202F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181302F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 75  SrcPdu: EMS_0x181302F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181302F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181402F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 76  SrcPdu: EMS_0x181402F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181402F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181502F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 77  SrcPdu: EMS_0x181502F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181502F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181602F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 78  SrcPdu: EMS_0x181602F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181602F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181702F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 79  SrcPdu: EMS_0x181702F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181702F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181802F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 80  SrcPdu: EMS_0x181802F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181802F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181902F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 81  SrcPdu: EMS_0x181902F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181902F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181A02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 82  SrcPdu: EMS_0x181A02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181A02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_0x181D02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 83  SrcPdu: EMS_0x181D02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_0x181D02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_18F82B62h_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 84  SrcPdu: EMS_18F82B62h_Can_Network_CANNODE_4_Com2PduR  DestPdu: EMS_18F82B62h_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 85  SrcPdu: EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 86  SrcPdu: EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_CML_1805FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 87  SrcPdu: EMS_CML_1805FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_CML_1805FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 88  SrcPdu: EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_ConntSts_Rx_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 89  SrcPdu: EMS_ConntSts_Rx_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_ConntSts_Rx_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 90  SrcPdu: EMS_Connt_1807FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_Connt_1807FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 91  SrcPdu: EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 92  SrcPdu: EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 93  SrcPdu: EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 94  SrcPdu: EMS_HCU_1814FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_HCU_1814FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 95  SrcPdu: EMS_HV1_1810FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_HV1_1810FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 96  SrcPdu: EMS_HV2_1811FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_HV2_1811FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 97  SrcPdu: EMS_Msg_1806E5F4h_Can_Network_CANNODE_4_Com2PduR  DestPdu: EMS_Msg_1806E5F4h_Can_Network_CANNODE_4_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 98  SrcPdu: EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 99  SrcPdu: EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_Res_0x181E02F1_Can_Network_CANNODE_5 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 100  SrcPdu: EMS_Res_0x181E02F1_Can_Network_CANNODE_5_Com2PduR  DestPdu: EMS_Res_0x181E02F1_Can_Network_CANNODE_5_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 101  SrcPdu: EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 102  SrcPdu: EMS_Timer_1809FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_Timer_1809FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 103  SrcPdu: EMS_Warning_1808FAF1h_Can_Network_CANNODE_1_Com2PduR  DestPdu: EMS_Warning_1808FAF1h_Can_Network_CANNODE_1_PduR2CanIf*/
{ ComConf_ComIPdu_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation} ,   /* Index: 104  SrcPdu: TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3_Com2PduR  DestPdu: TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3_PduR2CanIf*/
{ ComConf_ComIPdu_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1 , (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation}     /* Index: 105  SrcPdu: TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1_Com2PduR  DestPdu: TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1_PduR2CanIf*/
};
#endif  /* PDUR_CONFIG_SINGLE_IFTX_UP */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

        
    
/* Generating PbCfg_c::PduR_LoIfTTxToUp_PBcfg_c::loIf_TTxToUp */
    

        
    
/* Generating PbCfg_c::PduR_LoTpRxToUp_PBcfg_c::loTpRx_To_Up */

        

/* ------------------------------------------------------------------------ */
/* Begin section for constants */


#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP )
#define PduR_SoAdIfTxToUp NULL_PTR
#else
static CONST(PduR_RT_LoTtIfTxToUp, PDUR_CONST ) PduR_SoAdIfTxToUp [] = {
{ComConf_ComIPdu_EthernetPdu_Tx_EthernetPhysicalChannel_Tx,(PduR_upIfTriggerTxFP) PduR_RF_Com_TriggerTransmit, (PduR_upIfTxConfirmationFP) PduR_RF_Com_TxConfirmation }    /* Index: 0  SrcPdu: EthernetPdu_Tx_Com2PduR  DestPdu: EthernetPdu_Tx_PduR2SoAd*/
};
#endif  /* PDUR_CONFIG_SINGLE_IFTX_UP */
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined ( PDUR_CONFIG_SINGLE_TPRX )
#define PduR_CanTpRxToUp   NULL_PTR
#else
static CONST( PduR_RT_LoTpRxToUp, PDUR_CONST ) PduR_CanTpRxToUp[] = {
    {DcmConf_DcmDslProtocolRx_Tester_DiagFunReq_0x18DBFFFAh_Can_Network_CANNODE_2_Func_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication },   /*Tester_DiagFunReq_0x18DBFFFAh_Can_Network_CANNODE_2_Func_CanTp2PduR*/
    {DcmConf_DcmDslProtocolRx_Tester_DiagPhyReq_0x18DAF1FAh_Can_Network_CANNODE_2_Phys_PduR2Dcm, (PduR_upTpStartOfReceptionFP) PduR_RF_Dcm_StartOfReception,(PduR_upTpProvideRxBufFP) PduR_RF_Dcm_CopyRxData,(PduR_upTpRxIndicationFP) PduR_RF_Dcm_TpRxIndication }    /*Tester_DiagPhyReq_0x18DAF1FAh_Can_Network_CANNODE_2_Phys_CanTp2PduR*/
};
#endif  /* PDUR_CONFIG_SINGLE_TPRX */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


        
    
/* Generating PbCfg_c::PduR_LoTpTxToUp_PBcfg_c::loTpTx_To_Up */
    
        

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
#if defined(PDUR_CONFIG_SINGLE_TPTX_UP )
#define PduR_CanTpTxToUp NULL_PTR
#else
static CONST(PduR_RT_LoTpTxToUp, PDUR_CONST ) PduR_CanTpTxToUp [] = {  
    { DcmConf_DcmDslProtocolTx_EMS_DiagResp_0x18DAFAF1h_Can_Network_CANNODE_2_Phys_Dcm2PduR, (PduR_upTpProvideTxBufFP) PduR_RF_Dcm_CopyTxData,(PduR_upTpTxConfirmationFP) PduR_RF_Dcm_TpTxConfirmation }    /*Index: 0 EMS_DiagResp_0x18DAFAF1h_Can_Network_CANNODE_2_Phys_Dcm2PduR*/
};
#endif  /* PDUR_CONFIG_SINGLE_TPTX_UP */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


        
    
/* Generating PbCfg_c::PduR_Mc_ComToLo_PBcfg_c::mcComToLow */
/* Generating PbCfg_c::PduR_Mc_DcmToLo_PBcfg_c::mcDcmToLow */
/* Generating PbCfg_c::PduR_Mc_IpduMToLo_PBcfg_c::MC_IpduMUp_Lo */
/* Generating PbCfg_c::PduR_Mc_TpTxToUp_PBcfg_c::xpandMcTpTxToUp */
/* Generating PbCfg_c::PduR_Cdd_PBcfg_c::Xpand_Cdd_body */
/* Generating PbCfg_c::PduR_Mc_GwToLo_PBcfg_c::DisplayPduR_mcGwToLo */
/* Generating PbCfg_c::PduR_GwIfTx_PBcfg_c::display_GwIfTx */
/* Generating PbCfg_c::PduR_GwIf_PBcfg_c::display_GwIf */
/* Generating PbCfg_c::PduR_Gw_IfBuf_PBcfg_c::PduR_gw_Buf_If_structure */
/* Generating PbCfg_c::PduR_Rpg_PBcfg_c::display_PduR_RPG*/


#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

static CONST (PduR_RPGInfoType, PDUR_CONST) PduR_RPGInfo[] = {

    {
     NULL_PTR,
     PDUR_RPGID_NULL,
     0
    },   /* PDUR_RPGID_NULL */

    
};

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"
/* Routing enable disbale flag to control routing. */
CONST(boolean, PDUR_CONST) PduR_RPG_EnRouting[] =
{
  TRUE, /*PDUR_RPGID_NULL*/
  
};

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"


#endif /* #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0) */


/* Generating PbCfg_c::PduR_Gw_TpBuf_PBcfg_c::PduR_gw_Buf_TP_structure*/

    /* Generating PbCfg_c::PduR_GwTp_PBcfg_c::display_GwTp */
    /* Generating PbCfg_c::PduR_PbConfigType_PBcfg_c::PduR_BswLoCfg */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_LoTpConfig, PDUR_CONST ) PduR_LoTpCfg[] = {
  {
    PduR_CanTpRxToUp,       /* CanTp */
    PduR_CanTpTxToUp,       /* CanTp */
    2,        /* CanTp RxToUp Number Of Entries*/
    1     /* CanTp TxToUp Number Of Entries*/
    }
  };

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_LoIfDConfig, PDUR_CONST ) PduR_LoIfDCfg[] = {
  {
    PduR_CanIfRxToUp,       /* CanIf */
    PduR_CanIfTxToUp,       /* CanIf */
    130,        /* CanIf RxToUp NrEntries*/
    106      /* CanIf TxToUp NrEntries*/
    }
  };

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_LoIfTTConfig, PDUR_CONST ) PduR_LoIfTTCfg[] = {
  {
    PduR_IpduMRxToUp,       /* IpduM */
    NULL_PTR,       /* IpduM */
    22,        /* IpduM RxToUp NrEntries*/
    0   /* IpduM */
      },
  {
    PduR_SoAdIfRxToUp,       /* SoAdIf */
    PduR_SoAdIfTxToUp,       /* SoAdIf */
    1,        /* SoAdIf RxToUp NrEntries*/
    1      /* SoAdIf TxToUp NrEntries*/
    }
  };

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
/* Generating PbCfg_c::PduR_PbConfigType_PBcfg_c::PduR_BswUpCfg */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_UpConfig, PDUR_CONST ) PduR_UpTpCfg[] = {
  {
    PduR_DcmToLo,     /* Dcm */
    NULL_PTR,       /* mcDcmToLo */
    1      /* Dcm */
    }
  };

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
static CONST( PduR_UpConfig, PDUR_CONST ) PduR_UpIfCfg[] = {
  {
    PduR_comToLo,     /* Com */
    NULL_PTR,       /* mcComToLo */
    106      /* Com */
    },
  {
    NULL_PTR,       /* IpduM */
    NULL_PTR,       /* mcIpduMToLo */
    0   /* IpduM */
    }
  };

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
/* Generating PbCfg_c::PduR_Cdd_PBcfg_c::PduR_CddCfg */
/* Generating PbCfg_c::PduR_PbConfigType_PBcfg_c::PduR_BswUpToLoRxCfg */


    


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

CONST( PduR_RPTablesType, PDUR_CONST ) PduR_RoutingPathTables = {
    (P2CONST( PduR_loTransmitFuncType, AUTOMATIC, PDUR_CONST ))             PduR_loTransmitTable,
    (P2CONST( PduR_loCancelReceiveFuncType, AUTOMATIC,  PDUR_CONST))        PduR_loCancelRxTable,
    (P2CONST( PduR_loCancelTransmitFuncType, AUTOMATIC, PDUR_CONST ))       PduR_loCancelTransmitTable,
    (P2CONST( PduR_upIfRxIndicationFuncType, AUTOMATIC, PDUR_CONST ))       PduR_upIfRxIndicationTable,
    (P2CONST( PduR_upIfTxConfirmationFuncType, AUTOMATIC, PDUR_CONST ))     PduR_upIfTxConfirmationTable,
    (P2CONST( PduR_upTpCopyRxDataFuncType, AUTOMATIC, PDUR_CONST ))         PduR_upTpCopyRxDataTable,
    (P2CONST( PduR_upTpStartOfReceptionFuncType, AUTOMATIC, PDUR_CONST ))   PduR_upTpStartOfReceptionTable,
    (P2CONST( PduR_upTpRxIndicationFuncType, AUTOMATIC, PDUR_CONST ))       PduR_upTpRxIndicationTable,
    (P2CONST( PduR_upTpCopyTxDataFuncType, AUTOMATIC, PDUR_CONST ))         PduR_upTpCopyTxDataTable,
    (P2CONST( PduR_upTpTxConfirmationFuncType, AUTOMATIC, PDUR_CONST ))     PduR_upTpTxConfirmationTable,
    (P2CONST( PduR_upIfTriggerTxFuncType, AUTOMATIC, PDUR_CONST ))          PduR_upIfTriggerTxTable

};


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

    
/*
    These structures are generated by the code generator tool. Respective module's function names are generated
    only if it is present in the PduR_PbCfg.c file in any one of the entries.
*/


/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


CONST(PduR_loTransmitFuncType, PDUR_CONST) PduR_loTransmitTable[] =
{
    {&PduR_RF_CanIf_Transmit_Func},
    {&PduR_RF_CanTp_Transmit_Func},
    {&PduR_RF_SoAdIf_Transmit_Func}
};




CONST(PduR_loCancelReceiveFuncType, PDUR_CONST) PduR_loCancelRxTable[] =
{
    {NULL_PTR}
};




CONST(PduR_loCancelTransmitFuncType, PDUR_CONST) PduR_loCancelTransmitTable[] =
{
    {&PduR_IH_CancelTransmit_Func},
    {&PduR_RF_CanTp_CancelTransmit_Func}
};



CONST(PduR_upIfRxIndicationFuncType, PDUR_CONST) PduR_upIfRxIndicationTable[] =
{
    {&PduR_RF_Com_RxIndication_Func},
    {&PduR_RF_IpduM_RxIndication_Func}
};



CONST(PduR_upIfTxConfirmationFuncType, PDUR_CONST) PduR_upIfTxConfirmationTable[] =
{
    {&PduR_RF_Com_TxConfirmation_Func}
};



CONST(PduR_upIfTriggerTxFuncType, PDUR_CONST) PduR_upIfTriggerTxTable[] =
{
    {&PduR_RF_Com_TriggerTransmit_Func}
};



CONST(PduR_upTpCopyRxDataFuncType, PDUR_CONST) PduR_upTpCopyRxDataTable[] =
{
    {&PduR_RF_Dcm_CopyRxData_Func}
};



CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[] =
{
    {&PduR_RF_Dcm_StartOfReception_Func}
};



CONST(PduR_upTpRxIndicationFuncType, PDUR_CONST) PduR_upTpRxIndicationTable[] =
{
    {&PduR_RF_Dcm_TpRxIndication_Func}
};




CONST(PduR_upTpCopyTxDataFuncType, PDUR_CONST) PduR_upTpCopyTxDataTable[] =
{
    {&PduR_RF_Dcm_CopyTxData_Func}
};



CONST(PduR_upTpTxConfirmationFuncType, PDUR_CONST) PduR_upTpTxConfirmationTable[] =
{
    {&PduR_RF_Dcm_TpTxConfirmation_Func}
};






/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
/* Generating PbCfg_c::PduR_PbConfigType_PBcfg_c::pdur_PBConfigType */

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
CONST( PduR_PBConfigType, PDUR_CONST ) PduR_GlobalPBConfig = {
  (P2CONST( PduR_CddConfig, AUTOMATIC, PDUR_CONST )) NULL_PTR,                /* PduR_CddCfg */
     (P2CONST( PduR_LoTpConfig, AUTOMATIC, PDUR_CONST )) PduR_LoTpCfg,           /* Pointer to lowerlayer Tp config structure */
     (P2CONST( PduR_LoIfDConfig, AUTOMATIC, PDUR_CONST )) PduR_LoIfDCfg,         /* Pointer to Direct lowerlayer If config structure */
     (P2CONST( PduR_LoIfTTConfig, AUTOMATIC, PDUR_CONST )) PduR_LoIfTTCfg,       /* Pointer to TT lowerlayer If config structure */
     (P2CONST( PduR_UpConfig, AUTOMATIC, PDUR_CONST )) PduR_UpIfCfg,             /* Pointer to Upperlayer If config structure */
     (P2CONST( PduR_UpConfig, AUTOMATIC, PDUR_CONST )) PduR_UpTpCfg,             /* Pointer to Upperlayer Tp config structure */
     (P2CONST( PduR_MT_UpToLo, AUTOMATIC, PDUR_CONST )) NULL_PTR,                /* mcGwToLo */
     (P2CONST( PduR_MT_LoIfTxToUp, AUTOMATIC, PDUR_CONST )) NULL_PTR,            /* McIfRx */
     (P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST )) NULL_PTR,            /* McTpTx */
     (P2VAR(   PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR )) NULL_PTR,              /* PduR_msTpTxToUp*/
     (P2CONST( PduR_GT_IfTx, AUTOMATIC, PDUR_CONST )) NULL_PTR,                  /* gwIfTx */
     (P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST )) NULL_PTR,                    /* gwIf        */
     (P2CONST( PduR_GT_Tp, AUTOMATIC, PDUR_CONST )) NULL_PTR,                    /* GwTp */
     (P2CONST( PduR_RPTablesType, AUTOMATIC, PDUR_CONST )) &PduR_RoutingPathTables, /* PduR_RoutingPathTables */
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
    (P2CONST(PduR_GwTp_SessionListType, AUTOMATIC, PDUR_CONST )) NULL_PTR, /*PduR_TpSession_Dynamic*/
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
     (P2CONST(PduR_UpIfTxConf_Config, AUTOMATIC, PDUR_CONST)) PduR_UpIfTxConf_ConfigList,
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
     (P2CONST (PduR_RPGInfoType, AUTOMATIC, PDUR_CONST))        PduR_RPGInfo,        /* RoutingPathGroup ConfigInfo */
     (P2CONST (boolean, AUTOMATIC, PDUR_CONST))   PduR_RPG_EnRouting,  /* RoutingControl StatusInfo */
     (P2VAR  (boolean , TYPEDEF , PDUR_VAR))  PduR_RPG_Status,        /*RAM status for each RPG*/
     (PduR_RoutingPathGroupIdType)                              0,        /* Number of RPGs.*/
#endif
     (P2CONST (PduR_UpTpToLoTpRxConfig, TYPEDEF, PDUR_CONST)) NULL_PTR,          /* Pointer to PduR_UpTpToLoTpRxConfig structure for supporting Cancel Receive API */
0,                  /* PDUR_CONFIGURATION_ID */
0, /*Total no of Gw Tp Routing Path*/
0, /*Total no of Gw If Routing path*/
     (PduIdType) 0       /* McTpTx */
};

/* ------------------------------------------------------------------------ */
/* Begin section for constants */

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"







#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_ConfigType, PDUR_CONST) PduR_Config = {
    NULL_PTR,    /* Void pointer initialised with null pointer as PduR_Config will not be used in case of PDUR_VARIANT_PRE_COMPILE */
    NULL_PTR
};

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


