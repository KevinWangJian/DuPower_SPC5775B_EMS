


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: Com / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/

#ifndef COM_PBCFG_H
#define COM_PBCFG_H

/*  START: Local #defines  */

#define COM_NUM_RX_SIGNALS        1445u
#define COM_NUM_TX_SIGNALS        1565u
#define COM_NUM_TX_IPDU         107u
#define COM_NUM_RX_IPDU         149u
#define COM_NUM_GWSRC_SIGNALS  0u
#define COM_NUM_GWSRC_GRPSIGNALS  0u
#define COM_NUM_GWSRC_IPDUS     0u
#define COM_NUM_GRPSIG_NOGW     0u

#ifdef COM_F_ONEEVERYN
#define COM_NUM_OF_SIG_GRPSIG_WITH_ONE_EVERY_N 0u
#endif /* #ifdef COM_F_ONEEVERYN */




#define COM_UPDATE_MAX      0xFFFF   /* max ipdu size */


#ifdef COM_RxIPduDeferredProcessing
    /* Buffer to hold data for deferred signal processing */
    #define COM_MAX_DEFERRED_IPDUBUFF_SIZE 64
#endif /* #ifdef COM_RxIPduDeferredProcessing */


/* START: I-PDU Buffers */
/* ComIPdu*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_18F82B62h_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180102F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180702F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_ConntSts_Rx_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180102F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180702F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_ConntSts_Rx_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180202F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180302F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180402F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180502F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180602F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180802F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180202F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180302F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180402F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180502F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180602F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180802F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC2_Confirm_Status_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC_Confirm_Status_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180902F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180A02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180B02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180C02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180D02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180E02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x180F02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181002F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181102F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181202F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181302F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181402F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181502F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181602F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181702F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181802F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181902F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181A02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_0x181D02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180902F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180A02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180B02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180C02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180D02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180E02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x180F02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181002F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181102F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181202F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181302F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181402F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181502F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181602F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181702F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181802F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181902F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181A02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_0x181D02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_CML_1805FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_Res_0x181E02F1_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_IpduBuf_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1[];

        extern VAR(uint8,COM_VAR) Com_IpduBuf_EthernetPdu_Tx_EthernetPhysicalChannel_Tx[];



/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

#ifdef COM_TXDOUBLEBUFFER

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_18F82B62h_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180102F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180702F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_ConntSts_Rx_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180102F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180702F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_ConntSts_Rx_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180202F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180302F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180402F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180502F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180602F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180802F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180202F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180302F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180402F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180502F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180602F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180802F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_Confirm_Status_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_Confirm_Status_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180902F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180A02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180B02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180C02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180D02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180E02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x180F02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181002F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181102F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181202F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181302F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181402F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181502F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181602F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181702F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181802F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181902F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181A02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_0x181D02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180902F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180A02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180B02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180C02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180D02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180E02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x180F02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181002F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181102F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181202F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181302F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181402F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181502F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181602F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181702F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181802F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181902F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181A02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_0x181D02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_CML_1805FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_Res_0x181E02F1_Can_Network_CANNODE_5[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3[] ;
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1[] ;

        extern VAR(uint8,COM_VAR) Com_LocalBuf_EthernetPdu_Tx_EthernetPhysicalChannel_Tx[] ;



/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
#endif

/* LocalBuffer for Rx Ipdus */

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX10[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX11[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX2[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX8[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Confirm_MUX9[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_SafeCertif_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC2_EOLTester_Serial_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX10[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX11[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX2[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX8[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Confirm_MUX9[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_SafeCertif_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_AFC_EOLTester_Serial_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_Cell_18042701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_ConntSts_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_DTC_18AA2701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_DetCell_18052701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_DetTemp_18062701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_Fault_18072701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_HV2_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_HV_18022701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_ISO_18162701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_Info_18082701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_PackInfo_18142701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_PeskSOP_18172701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_SystPara_18012701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_SystStat_18122701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS2_Temp_18152701h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_Cell_18042701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_ConntSts_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_DTC_18AA2701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_DetCell_18052701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_DetTemp_18062701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_Fault_18072701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_HV2_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_HV_18022701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_ISO_18162701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_Info_18082701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_LongSOP_18032701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_PackInfo_18142701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_PeskSOP_18172701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_SystPara_18012701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_SystStat_18122701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_BMS_Temp_18152701h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_CCS_1819FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_CSTCEM_181DFAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_ConntSts_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_DTC_18AAFAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_HV_1802FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_ISO_1820FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_Sample_1803FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VIN_1816FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBCL_1817FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBCP1_1812FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBCP2_1813FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBCS_1818FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBHM_1811FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBRM1_1814FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBRM2_1815FAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBSD_181BFAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBSM_181AFAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU2_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_CCS_1819FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_CSTCEM_181DFAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_ConntSts_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_DTC_18AAFAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_HV_1802FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_ISO_1820FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_Sample_1803FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VIN_1816FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBCL_1817FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBCP1_1812FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBCP2_1813FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBCS_1818FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBHM_1811FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBRM1_1814FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBRM2_1815FAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBSD_181BFAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBSM_181AFAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_CCU_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame10_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame11_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame1_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame2_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame3_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame4_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame5_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame6_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame7_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame8_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDCModuleFrame9_Rx_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDC_1_18F8622Bh_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDC_2_18F8622Ch_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDC_3_18F8622Dh_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDC_Msg1_18FF50E5h_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_DCDC_Msg2_18FF51E5h_Can_Network_CANNODE_4[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_HCU2_Syst_18220145h_Can_Network_CANNODE_3[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_HCU_Syst_18220145h_Can_Network_CANNODE_1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1801F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1802F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1803F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1804F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1805F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1806F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1807F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1808F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x1809F102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180AF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180BF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180CF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180DF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180EF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x180FF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX2_0x18FFF102_Can_Network_CANNODE_6[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1801F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1802F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1803F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1804F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1805F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1806F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1807F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1808F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x1809F102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180AF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180BF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180CF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180DF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180EF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x180FF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_TBOX_0x18FFF102_Can_Network_CANNODE_5[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_Tester2_18FFFA01h_MUX1[];
        extern VAR(uint8,COM_VAR) Com_LocalBuf_Tester_18FFFA01h_MUX1[];

        extern VAR(uint8,COM_VAR) Com_LocalBuf_EthernetPdu_Rx_EthernetPhysicalChannel_Rx[];


/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
/* END: I-PDU Buffers */



/*Start: Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
extern VAR(uint8,COM_VAR) Com_SigType_u8[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
/*End: Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/*Start: Signal Buffer -----> uint16/sint16*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint16 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
extern VAR(uint16,COM_VAR) Com_SigType_u16[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint16 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
/*End: Signal Buffer -----> uint16/sint16*/

/*Start: Signal Buffer -----> uint32/sint32*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint32 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR) Com_SigType_u32[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint32 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
/*End: Signal Buffer -----> uint32/sint32*/

/*Start: Signal Buffer -----> uint64/sint64*/
#ifdef COM_RXSIG_INT64

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint64 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
extern VAR(uint64,COM_VAR) Com_SigType_u64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint64 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
#endif
/*End: Signal Buffer -----> uint64/sint64*/


#ifdef COM_RXSIG_FLOAT64SUPP

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(float64,COM_VAR) Com_SigType_f64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif /* #ifdef COM_RXSIG_FLOAT64SUPP */




#ifdef COM_RX_SIGNALGROUP

/*Start: Rx Group Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

extern VAR(uint8,COM_VAR) Com_RxGrpSigType_u8[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

/*End: Rx Group Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/*Start: Rx Group Signal Buffer -----> uint16/sint16*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint16 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
extern VAR(uint16,COM_VAR) Com_RxGrpSigType_u16[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint16 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
/*End:Rx Group Signal Buffer -----> uint16/sint16*/

/*Start: Rx Group Signal Buffer -----> uint32/sint32*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint32 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR) Com_RxGrpSigType_u32[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint32 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
/*End: Rx Group Signal Buffer -----> uint32/sint32*/

/*Start: Rx Group Signal Buffer -----> uint64/sint64*/
#ifdef COM_RXGRPSIG_INT64

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint64 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
extern VAR(uint64,COM_VAR) Com_RxGrpSigType_u64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint64 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
#endif
/*End: Rx Group Signal Buffer -----> uint64/sint64*/


#ifdef COM_RXGRPSIG_FLOAT64SUPP

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(float64,COM_VAR) Com_RxGrpSigType_f64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif /* #ifdef COM_RXGRPSIG_FLOAT64SUPP */


/*Start:Rx Group Signal second Buffer -----> uint8/sint8/boolean/uint8[n]*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

extern VAR(uint8,COM_VAR) Com_SecondRxGrpSigType_u8[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"

/*End: Rx Group Signal second Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/*Start: Rx Group Signal second Signal Buffer -----> uint16/sint16*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint16 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
extern VAR(uint16,COM_VAR) Com_SecondRxGrpSigType_u16[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint16 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
/*End: Rx Group Signal second Signal Buffer -----> uint16/sint16*/

/*Start: Rx Group Signal second Signal Buffer -----> uint32/sint32*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint32 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR) Com_SecondRxGrpSigType_u32[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint32 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
/*End: Rx Group Signal second Signal Buffer -----> uint32/sint32*/

/*Start: Rx Group Signal second Signal Buffer -----> uint64/sint64*/
#ifdef COM_RXGRPSIG_INT64

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint64 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
extern VAR(uint64,COM_VAR) Com_SecondRxGrpSigType_u64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint64 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
#endif
/*End: Rx Group Signal second Signal Buffer -----> uint64/sint64*/


#ifdef COM_RXGRPSIG_FLOAT64SUPP

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(float64,COM_VAR) Com_SecondRxGrpSigType_f64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
#endif /* #ifdef COM_RXGRPSIG_FLOAT64SUPP */


#endif /* #ifdef COM_RX_SIGNALGROUP*/

#ifdef COM_TX_SIGNALGROUP

/*Start: Tx group Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint8 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
extern VAR(uint8,COM_VAR) Com_TxGrpSigType_u8[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint8 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "Com_MemMap.h"
/*End: Tx group Signal Buffer -----> uint8/sint8/boolean/uint8[n]*/

/*Start: Tx group Signal Buffer -----> uint16/sint16*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint16 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
extern VAR(uint16,COM_VAR) Com_TxGrpSigType_u16[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint16 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_16
#include "Com_MemMap.h"
/*End: Tx group  Signal Buffer -----> uint16/sint16*/

/*Start: Tx group Signal Buffer -----> uint32/sint32*/

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint32 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR) Com_TxGrpSigType_u32[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint32 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
/*End: Tx group Signal Buffer -----> uint32/sint32*/

/*Start: Tx group Signal Buffer -----> uint64/sint64*/
#ifdef COM_TXGRPSIG_INT64

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint64 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
extern VAR(uint64,COM_VAR) Com_TxGrpSigType_u64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint64 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_64
#include "Com_MemMap.h"
#endif
/*End: Tx group Signal Buffer -----> uint64/sint64*/


#ifdef COM_TXGRPSIG_FLOAT64SUPP
/*Start: Tx group Signal Buffer -----> float64 */

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(float64,COM_VAR) Com_TxGrpSigType_f64[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
/*End: Tx group Signal Buffer -----> float64 */
#endif /* #ifdef COM_TXGRPSIG_FLOAT64SUPP */
#endif /* #ifdef COM_TX_SIGNALGROUP */

#ifdef COM_RxSigUpdateTimeout
#endif /* #ifdef COM_RxSigUpdateTimeout */

#ifdef COM_RxSigGrpUpdateTimeout
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */

#endif   /* COM_PBCFG_H */
