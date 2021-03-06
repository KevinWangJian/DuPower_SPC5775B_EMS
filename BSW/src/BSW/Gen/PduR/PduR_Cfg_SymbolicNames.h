

 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/

#ifndef PDUR_CFG_SYMBOLICNAMES_H
#define PDUR_CFG_SYMBOLICNAMES_H

/* Note: Module variant generation is done here, specifically to make below macros available on the inclusion of 
 * PduR_memmap.h header file by other modules without PduR_Cfg.h inclusion */


#define PDUR_VARIANT_PRE_COMPILE    (0)

#define PDUR_VARIANT_POSTBUILD_LOADABLE    (1)

#if !defined(PDUR_CONFIGURATION_VARIANT)
#define PDUR_CONFIGURATION_VARIANT    PDUR_VARIANT_PRE_COMPILE
#endif /* PDUR_CONFIGURATION_VARIANT */




/* For PduRRoutingTable: Symbolic Name reference are generated for Tx Paths and Rx paths
For TxPaths:
PduRConf_PduRSrcPdu_<shortname of PduRSrcPdu> will be used by module which gives PduR_<UpperLayer>Transmit request e.g Com,Dcm,Up-Cdd
PduRConf_PduRDestPdu_<shortname of PduRDestPdu> will be used by module which gives PduR_<LowerLayer>TxConfirmation callback e.g CanIf,CanTp,Low-Cdd

For RxPaths:
PduRConf_PduRSrcPdu_<shortname of PduRSrcPdu> will be used by module which gives PduR_<LowerLayer>RxIndication callback e.g CanIf,CanTp,Low-Cdd */

#define PduRConf_PduRSrcPdu_AFC2_Confirm_Status_Can_Network_CANNODE_3_Com2PduR    0
#define PduRConf_PduRDestPdu_AFC2_Confirm_Status_Can_Network_CANNODE_3_PduR2CanIf  0

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX10_IpduM2PduR    0

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX11_IpduM2PduR    1

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX1_IpduM2PduR    2

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX2_IpduM2PduR    3

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX3_IpduM2PduR    4

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX4_IpduM2PduR    5

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX5_IpduM2PduR    6

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX6_IpduM2PduR    7

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX8_IpduM2PduR    8

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_MUX9_IpduM2PduR    9

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_3_CanIf2PduR    0

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_SafeCertif_Can_Network_CANNODE_3_CanIf2PduR    1

#define PduRConf_PduRSrcPdu_AFC2_EOLTester_Serial_Can_Network_CANNODE_3_CanIf2PduR    2

#define PduRConf_PduRSrcPdu_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3_Com2PduR    1
#define PduRConf_PduRDestPdu_AFC2_SafeCertif_Confirm_Can_Network_CANNODE_3_PduR2CanIf  1

#define PduRConf_PduRSrcPdu_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3_Com2PduR    2
#define PduRConf_PduRDestPdu_AFC2_TBOX_CCU2_Sys_Can_Network_CANNODE_3_PduR2CanIf  2

#define PduRConf_PduRSrcPdu_AFC_Confirm_Status_Can_Network_CANNODE_1_Com2PduR    3
#define PduRConf_PduRDestPdu_AFC_Confirm_Status_Can_Network_CANNODE_1_PduR2CanIf  3

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX10_IpduM2PduR    10

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX11_IpduM2PduR    11

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX1_IpduM2PduR    12

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX2_IpduM2PduR    13

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX3_IpduM2PduR    14

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX4_IpduM2PduR    15

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX5_IpduM2PduR    16

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX6_IpduM2PduR    17

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX8_IpduM2PduR    18

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_MUX9_IpduM2PduR    19

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Confirm_Multiplexed_IPDU_Can_Network_CANNODE_1_CanIf2PduR    3

#define PduRConf_PduRSrcPdu_AFC_EOLTester_SafeCertif_Can_Network_CANNODE_1_CanIf2PduR    4

#define PduRConf_PduRSrcPdu_AFC_EOLTester_Serial_Can_Network_CANNODE_1_CanIf2PduR    5

#define PduRConf_PduRSrcPdu_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1_Com2PduR    4
#define PduRConf_PduRDestPdu_AFC_SafeCertif_Confirm_Can_Network_CANNODE_1_PduR2CanIf  4

#define PduRConf_PduRSrcPdu_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1_Com2PduR    5
#define PduRConf_PduRDestPdu_AFC_TBOX_CCU2_Sys_Can_Network_CANNODE_1_PduR2CanIf  5

#define PduRConf_PduRSrcPdu_BMS2_Cell_18042701h_Can_Network_CANNODE_3_CanIf2PduR    6

#define PduRConf_PduRSrcPdu_BMS2_ConntSts_Can_Network_CANNODE_3_CanIf2PduR    7

#define PduRConf_PduRSrcPdu_BMS2_DTC_18AA2701h_Can_Network_CANNODE_3_CanIf2PduR    8

#define PduRConf_PduRSrcPdu_BMS2_DetCell_18052701h_Can_Network_CANNODE_3_CanIf2PduR    9

#define PduRConf_PduRSrcPdu_BMS2_DetTemp_18062701h_Can_Network_CANNODE_3_CanIf2PduR    10

#define PduRConf_PduRSrcPdu_BMS2_Fault_18072701h_Can_Network_CANNODE_3_CanIf2PduR    11

#define PduRConf_PduRSrcPdu_BMS2_HV2_Can_Network_CANNODE_3_CanIf2PduR    12

#define PduRConf_PduRSrcPdu_BMS2_HV_18022701h_Can_Network_CANNODE_3_CanIf2PduR    13

#define PduRConf_PduRSrcPdu_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3_CanIf2PduR    14

#define PduRConf_PduRSrcPdu_BMS2_ISO_18162701h_Can_Network_CANNODE_3_CanIf2PduR    15

#define PduRConf_PduRSrcPdu_BMS2_Info_18082701h_Can_Network_CANNODE_3_CanIf2PduR    16

#define PduRConf_PduRSrcPdu_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3_CanIf2PduR    17

#define PduRConf_PduRSrcPdu_BMS2_PackInfo_18142701h_Can_Network_CANNODE_3_CanIf2PduR    18

#define PduRConf_PduRSrcPdu_BMS2_PeskSOP_18172701h_Can_Network_CANNODE_3_CanIf2PduR    19

#define PduRConf_PduRSrcPdu_BMS2_SystPara_18012701h_Can_Network_CANNODE_3_CanIf2PduR    20

#define PduRConf_PduRSrcPdu_BMS2_SystStat_18122701h_Can_Network_CANNODE_3_CanIf2PduR    21

#define PduRConf_PduRSrcPdu_BMS2_Temp_18152701h_Can_Network_CANNODE_3_CanIf2PduR    22

#define PduRConf_PduRSrcPdu_BMS_Cell_18042701h_Can_Network_CANNODE_1_CanIf2PduR    23

#define PduRConf_PduRSrcPdu_BMS_ConntSts_Can_Network_CANNODE_1_CanIf2PduR    24

#define PduRConf_PduRSrcPdu_BMS_DTC_18AA2701h_Can_Network_CANNODE_1_CanIf2PduR    25

#define PduRConf_PduRSrcPdu_BMS_DetCell_18052701h_Can_Network_CANNODE_1_CanIf2PduR    26

#define PduRConf_PduRSrcPdu_BMS_DetTemp_18062701h_Can_Network_CANNODE_1_CanIf2PduR    27

#define PduRConf_PduRSrcPdu_BMS_Fault_18072701h_Can_Network_CANNODE_1_CanIf2PduR    28

#define PduRConf_PduRSrcPdu_BMS_HV2_Can_Network_CANNODE_1_CanIf2PduR    29

#define PduRConf_PduRSrcPdu_BMS_HV_18022701h_Can_Network_CANNODE_1_CanIf2PduR    30

#define PduRConf_PduRSrcPdu_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1_CanIf2PduR    31

#define PduRConf_PduRSrcPdu_BMS_ISO_18162701h_Can_Network_CANNODE_1_CanIf2PduR    32

#define PduRConf_PduRSrcPdu_BMS_Info_18082701h_Can_Network_CANNODE_1_CanIf2PduR    33

#define PduRConf_PduRSrcPdu_BMS_LongSOP_18032701h_Can_Network_CANNODE_1_CanIf2PduR    34

#define PduRConf_PduRSrcPdu_BMS_PackInfo_18142701h_Can_Network_CANNODE_1_CanIf2PduR    35

#define PduRConf_PduRSrcPdu_BMS_PeskSOP_18172701h_Can_Network_CANNODE_1_CanIf2PduR    36

#define PduRConf_PduRSrcPdu_BMS_SystPara_18012701h_Can_Network_CANNODE_1_CanIf2PduR    37

#define PduRConf_PduRSrcPdu_BMS_SystStat_18122701h_Can_Network_CANNODE_1_CanIf2PduR    38

#define PduRConf_PduRSrcPdu_BMS_Temp_18152701h_Can_Network_CANNODE_1_CanIf2PduR    39

#define PduRConf_PduRSrcPdu_CCU2_CCS_1819FAF2h_Can_Network_CANNODE_3_CanIf2PduR    40

#define PduRConf_PduRSrcPdu_CCU2_CSTCEM_181DFAF2h_Can_Network_CANNODE_3_CanIf2PduR    41

#define PduRConf_PduRSrcPdu_CCU2_ConntSts_Can_Network_CANNODE_3_CanIf2PduR    42

#define PduRConf_PduRSrcPdu_CCU2_DTC_18AAFAF2h_Can_Network_CANNODE_3_CanIf2PduR    43

#define PduRConf_PduRSrcPdu_CCU2_HV_1802FAF2h_Can_Network_CANNODE_3_CanIf2PduR    44

#define PduRConf_PduRSrcPdu_CCU2_ISO_1820FAF2h_Can_Network_CANNODE_3_CanIf2PduR    45

#define PduRConf_PduRSrcPdu_CCU2_Sample_1803FAF2h_Can_Network_CANNODE_3_CanIf2PduR    46

#define PduRConf_PduRSrcPdu_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3_CanIf2PduR    47

#define PduRConf_PduRSrcPdu_CCU2_VIN_1816FAF2h_Can_Network_CANNODE_3_CanIf2PduR    48

#define PduRConf_PduRSrcPdu_CCU2_VechBCL_1817FAF2h_Can_Network_CANNODE_3_CanIf2PduR    49

#define PduRConf_PduRSrcPdu_CCU2_VechBCP1_1812FAF2h_Can_Network_CANNODE_3_CanIf2PduR    50

#define PduRConf_PduRSrcPdu_CCU2_VechBCP2_1813FAF2h_Can_Network_CANNODE_3_CanIf2PduR    51

#define PduRConf_PduRSrcPdu_CCU2_VechBCS_1818FAF2h_Can_Network_CANNODE_3_CanIf2PduR    52

#define PduRConf_PduRSrcPdu_CCU2_VechBHM_1811FAF2h_Can_Network_CANNODE_3_CanIf2PduR    53

#define PduRConf_PduRSrcPdu_CCU2_VechBRM1_1814FAF2h_Can_Network_CANNODE_3_CanIf2PduR    54

#define PduRConf_PduRSrcPdu_CCU2_VechBRM2_1815FAF2h_Can_Network_CANNODE_3_CanIf2PduR    55

#define PduRConf_PduRSrcPdu_CCU2_VechBSD_181BFAF2h_Can_Network_CANNODE_3_CanIf2PduR    56

#define PduRConf_PduRSrcPdu_CCU2_VechBSM_181AFAF2h_Can_Network_CANNODE_3_CanIf2PduR    57

#define PduRConf_PduRSrcPdu_CCU2_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_3_CanIf2PduR    58

#define PduRConf_PduRSrcPdu_CCU_CCS_1819FAF2h_Can_Network_CANNODE_1_CanIf2PduR    59

#define PduRConf_PduRSrcPdu_CCU_CSTCEM_181DFAF2h_Can_Network_CANNODE_1_CanIf2PduR    60

#define PduRConf_PduRSrcPdu_CCU_ConntSts_Can_Network_CANNODE_1_CanIf2PduR    61

#define PduRConf_PduRSrcPdu_CCU_DTC_18AAFAF2h_Can_Network_CANNODE_1_CanIf2PduR    62

#define PduRConf_PduRSrcPdu_CCU_HV_1802FAF2h_Can_Network_CANNODE_1_CanIf2PduR    63

#define PduRConf_PduRSrcPdu_CCU_ISO_1820FAF2h_Can_Network_CANNODE_1_CanIf2PduR    64

#define PduRConf_PduRSrcPdu_CCU_Sample_1803FAF2h_Can_Network_CANNODE_1_CanIf2PduR    65

#define PduRConf_PduRSrcPdu_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1_CanIf2PduR    66

#define PduRConf_PduRSrcPdu_CCU_VIN_1816FAF2h_Can_Network_CANNODE_1_CanIf2PduR    67

#define PduRConf_PduRSrcPdu_CCU_VechBCL_1817FAF2h_Can_Network_CANNODE_1_CanIf2PduR    68

#define PduRConf_PduRSrcPdu_CCU_VechBCP1_1812FAF2h_Can_Network_CANNODE_1_CanIf2PduR    69

#define PduRConf_PduRSrcPdu_CCU_VechBCP2_1813FAF2h_Can_Network_CANNODE_1_CanIf2PduR    70

#define PduRConf_PduRSrcPdu_CCU_VechBCS_1818FAF2h_Can_Network_CANNODE_1_CanIf2PduR    71

#define PduRConf_PduRSrcPdu_CCU_VechBHM_1811FAF2h_Can_Network_CANNODE_1_CanIf2PduR    72

#define PduRConf_PduRSrcPdu_CCU_VechBRM1_1814FAF2h_Can_Network_CANNODE_1_CanIf2PduR    73

#define PduRConf_PduRSrcPdu_CCU_VechBRM2_1815FAF2h_Can_Network_CANNODE_1_CanIf2PduR    74

#define PduRConf_PduRSrcPdu_CCU_VechBSD_181BFAF2h_Can_Network_CANNODE_1_CanIf2PduR    75

#define PduRConf_PduRSrcPdu_CCU_VechBSM_181AFAF2h_Can_Network_CANNODE_1_CanIf2PduR    76

#define PduRConf_PduRSrcPdu_CCU_VechBSTBEM_181CFAF2h_Can_Network_CANNODE_1_CanIf2PduR    77

#define PduRConf_PduRSrcPdu_DCDCModuleFrame10_Rx_Can_Network_CANNODE_4_CanIf2PduR    78

#define PduRConf_PduRSrcPdu_DCDCModuleFrame11_Rx_Can_Network_CANNODE_4_CanIf2PduR    79

#define PduRConf_PduRSrcPdu_DCDCModuleFrame1_Rx_Can_Network_CANNODE_4_CanIf2PduR    80

#define PduRConf_PduRSrcPdu_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4_Com2PduR    6
#define PduRConf_PduRDestPdu_DCDCModuleFrame1_Tx_Can_Network_CANNODE_4_PduR2CanIf  6

#define PduRConf_PduRSrcPdu_DCDCModuleFrame2_Rx_Can_Network_CANNODE_4_CanIf2PduR    81

#define PduRConf_PduRSrcPdu_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4_Com2PduR    7
#define PduRConf_PduRDestPdu_DCDCModuleFrame2_Tx_Can_Network_CANNODE_4_PduR2CanIf  7

#define PduRConf_PduRSrcPdu_DCDCModuleFrame3_Rx_Can_Network_CANNODE_4_CanIf2PduR    82

#define PduRConf_PduRSrcPdu_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4_Com2PduR    8
#define PduRConf_PduRDestPdu_DCDCModuleFrame3_Tx_Can_Network_CANNODE_4_PduR2CanIf  8

#define PduRConf_PduRSrcPdu_DCDCModuleFrame4_Rx_Can_Network_CANNODE_4_CanIf2PduR    83

#define PduRConf_PduRSrcPdu_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4_Com2PduR    9
#define PduRConf_PduRDestPdu_DCDCModuleFrame4_Tx_Can_Network_CANNODE_4_PduR2CanIf  9

#define PduRConf_PduRSrcPdu_DCDCModuleFrame5_Rx_Can_Network_CANNODE_4_CanIf2PduR    84

#define PduRConf_PduRSrcPdu_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4_Com2PduR    10
#define PduRConf_PduRDestPdu_DCDCModuleFrame5_Tx_Can_Network_CANNODE_4_PduR2CanIf  10

#define PduRConf_PduRSrcPdu_DCDCModuleFrame6_Rx_Can_Network_CANNODE_4_CanIf2PduR    85

#define PduRConf_PduRSrcPdu_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4_Com2PduR    11
#define PduRConf_PduRDestPdu_DCDCModuleFrame6_Tx_Can_Network_CANNODE_4_PduR2CanIf  11

#define PduRConf_PduRSrcPdu_DCDCModuleFrame7_Rx_Can_Network_CANNODE_4_CanIf2PduR    86

#define PduRConf_PduRSrcPdu_DCDCModuleFrame8_Rx_Can_Network_CANNODE_4_CanIf2PduR    87

#define PduRConf_PduRSrcPdu_DCDCModuleFrame9_Rx_Can_Network_CANNODE_4_CanIf2PduR    88

#define PduRConf_PduRSrcPdu_DCDC_1_18F8622Bh_Can_Network_CANNODE_4_CanIf2PduR    89

#define PduRConf_PduRSrcPdu_DCDC_2_18F8622Ch_Can_Network_CANNODE_4_CanIf2PduR    90

#define PduRConf_PduRSrcPdu_DCDC_3_18F8622Dh_Can_Network_CANNODE_4_CanIf2PduR    91

#define PduRConf_PduRSrcPdu_DCDC_Msg1_18FF50E5h_Can_Network_CANNODE_4_CanIf2PduR    92

#define PduRConf_PduRSrcPdu_DCDC_Msg2_18FF51E5h_Can_Network_CANNODE_4_CanIf2PduR    93

#define PduRConf_PduRSrcPdu_EMS2_0x180102F1_Can_Network_CANNODE_6_Com2PduR    12
#define PduRConf_PduRDestPdu_EMS2_0x180102F1_Can_Network_CANNODE_6_PduR2CanIf  12

#define PduRConf_PduRSrcPdu_EMS2_0x180202F1_Can_Network_CANNODE_6_Com2PduR    13
#define PduRConf_PduRDestPdu_EMS2_0x180202F1_Can_Network_CANNODE_6_PduR2CanIf  13

#define PduRConf_PduRSrcPdu_EMS2_0x180302F1_Can_Network_CANNODE_6_Com2PduR    14
#define PduRConf_PduRDestPdu_EMS2_0x180302F1_Can_Network_CANNODE_6_PduR2CanIf  14

#define PduRConf_PduRSrcPdu_EMS2_0x180402F1_Can_Network_CANNODE_6_Com2PduR    15
#define PduRConf_PduRDestPdu_EMS2_0x180402F1_Can_Network_CANNODE_6_PduR2CanIf  15

#define PduRConf_PduRSrcPdu_EMS2_0x180502F1_Can_Network_CANNODE_6_Com2PduR    16
#define PduRConf_PduRDestPdu_EMS2_0x180502F1_Can_Network_CANNODE_6_PduR2CanIf  16

#define PduRConf_PduRSrcPdu_EMS2_0x180602F1_Can_Network_CANNODE_6_Com2PduR    17
#define PduRConf_PduRDestPdu_EMS2_0x180602F1_Can_Network_CANNODE_6_PduR2CanIf  17

#define PduRConf_PduRSrcPdu_EMS2_0x180702F1_Can_Network_CANNODE_6_Com2PduR    18
#define PduRConf_PduRDestPdu_EMS2_0x180702F1_Can_Network_CANNODE_6_PduR2CanIf  18

#define PduRConf_PduRSrcPdu_EMS2_0x180802F1_Can_Network_CANNODE_6_Com2PduR    19
#define PduRConf_PduRDestPdu_EMS2_0x180802F1_Can_Network_CANNODE_6_PduR2CanIf  19

#define PduRConf_PduRSrcPdu_EMS2_0x180902F1_Can_Network_CANNODE_6_Com2PduR    20
#define PduRConf_PduRDestPdu_EMS2_0x180902F1_Can_Network_CANNODE_6_PduR2CanIf  20

#define PduRConf_PduRSrcPdu_EMS2_0x180A02F1_Can_Network_CANNODE_6_Com2PduR    21
#define PduRConf_PduRDestPdu_EMS2_0x180A02F1_Can_Network_CANNODE_6_PduR2CanIf  21

#define PduRConf_PduRSrcPdu_EMS2_0x180B02F1_Can_Network_CANNODE_6_Com2PduR    22
#define PduRConf_PduRDestPdu_EMS2_0x180B02F1_Can_Network_CANNODE_6_PduR2CanIf  22

#define PduRConf_PduRSrcPdu_EMS2_0x180C02F1_Can_Network_CANNODE_6_Com2PduR    23
#define PduRConf_PduRDestPdu_EMS2_0x180C02F1_Can_Network_CANNODE_6_PduR2CanIf  23

#define PduRConf_PduRSrcPdu_EMS2_0x180D02F1_Can_Network_CANNODE_6_Com2PduR    24
#define PduRConf_PduRDestPdu_EMS2_0x180D02F1_Can_Network_CANNODE_6_PduR2CanIf  24

#define PduRConf_PduRSrcPdu_EMS2_0x180E02F1_Can_Network_CANNODE_6_Com2PduR    25
#define PduRConf_PduRDestPdu_EMS2_0x180E02F1_Can_Network_CANNODE_6_PduR2CanIf  25

#define PduRConf_PduRSrcPdu_EMS2_0x180F02F1_Can_Network_CANNODE_6_Com2PduR    26
#define PduRConf_PduRDestPdu_EMS2_0x180F02F1_Can_Network_CANNODE_6_PduR2CanIf  26

#define PduRConf_PduRSrcPdu_EMS2_0x181002F1_Can_Network_CANNODE_6_Com2PduR    27
#define PduRConf_PduRDestPdu_EMS2_0x181002F1_Can_Network_CANNODE_6_PduR2CanIf  27

#define PduRConf_PduRSrcPdu_EMS2_0x181102F1_Can_Network_CANNODE_6_Com2PduR    28
#define PduRConf_PduRDestPdu_EMS2_0x181102F1_Can_Network_CANNODE_6_PduR2CanIf  28

#define PduRConf_PduRSrcPdu_EMS2_0x181202F1_Can_Network_CANNODE_6_Com2PduR    29
#define PduRConf_PduRDestPdu_EMS2_0x181202F1_Can_Network_CANNODE_6_PduR2CanIf  29

#define PduRConf_PduRSrcPdu_EMS2_0x181302F1_Can_Network_CANNODE_6_Com2PduR    30
#define PduRConf_PduRDestPdu_EMS2_0x181302F1_Can_Network_CANNODE_6_PduR2CanIf  30

#define PduRConf_PduRSrcPdu_EMS2_0x181402F1_Can_Network_CANNODE_6_Com2PduR    31
#define PduRConf_PduRDestPdu_EMS2_0x181402F1_Can_Network_CANNODE_6_PduR2CanIf  31

#define PduRConf_PduRSrcPdu_EMS2_0x181502F1_Can_Network_CANNODE_6_Com2PduR    32
#define PduRConf_PduRDestPdu_EMS2_0x181502F1_Can_Network_CANNODE_6_PduR2CanIf  32

#define PduRConf_PduRSrcPdu_EMS2_0x181602F1_Can_Network_CANNODE_6_Com2PduR    33
#define PduRConf_PduRDestPdu_EMS2_0x181602F1_Can_Network_CANNODE_6_PduR2CanIf  33

#define PduRConf_PduRSrcPdu_EMS2_0x181702F1_Can_Network_CANNODE_6_Com2PduR    34
#define PduRConf_PduRDestPdu_EMS2_0x181702F1_Can_Network_CANNODE_6_PduR2CanIf  34

#define PduRConf_PduRSrcPdu_EMS2_0x181802F1_Can_Network_CANNODE_6_Com2PduR    35
#define PduRConf_PduRDestPdu_EMS2_0x181802F1_Can_Network_CANNODE_6_PduR2CanIf  35

#define PduRConf_PduRSrcPdu_EMS2_0x181902F1_Can_Network_CANNODE_6_Com2PduR    36
#define PduRConf_PduRDestPdu_EMS2_0x181902F1_Can_Network_CANNODE_6_PduR2CanIf  36

#define PduRConf_PduRSrcPdu_EMS2_0x181A02F1_Can_Network_CANNODE_6_Com2PduR    37
#define PduRConf_PduRDestPdu_EMS2_0x181A02F1_Can_Network_CANNODE_6_PduR2CanIf  37

#define PduRConf_PduRSrcPdu_EMS2_0x181D02F1_Can_Network_CANNODE_6_Com2PduR    38
#define PduRConf_PduRDestPdu_EMS2_0x181D02F1_Can_Network_CANNODE_6_PduR2CanIf  38

#define PduRConf_PduRSrcPdu_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3_Com2PduR    39
#define PduRConf_PduRDestPdu_EMS2_ACDC_1813FAF1h_Can_Network_CANNODE_3_PduR2CanIf  39

#define PduRConf_PduRSrcPdu_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3_Com2PduR    40
#define PduRConf_PduRDestPdu_EMS2_ACWh_1804FAF1h_Can_Network_CANNODE_3_PduR2CanIf  40

#define PduRConf_PduRSrcPdu_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3_Com2PduR    41
#define PduRConf_PduRDestPdu_EMS2_CML_1805FAF1h_Can_Network_CANNODE_3_PduR2CanIf  41

#define PduRConf_PduRSrcPdu_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3_Com2PduR    42
#define PduRConf_PduRDestPdu_EMS2_ConntSts_1821FAF1h_Can_Network_CANNODE_3_PduR2CanIf  42

#define PduRConf_PduRSrcPdu_EMS2_ConntSts_Rx_Can_Network_CANNODE_3_Com2PduR    43
#define PduRConf_PduRDestPdu_EMS2_ConntSts_Rx_Can_Network_CANNODE_3_PduR2CanIf  43

#define PduRConf_PduRSrcPdu_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3_Com2PduR    44
#define PduRConf_PduRDestPdu_EMS2_Connt_1807FAF1h_Can_Network_CANNODE_3_PduR2CanIf  44

#define PduRConf_PduRSrcPdu_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3_Com2PduR    45
#define PduRConf_PduRDestPdu_EMS2_DCDC_1812FAF1h_Can_Network_CANNODE_3_PduR2CanIf  45

#define PduRConf_PduRSrcPdu_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3_Com2PduR    46
#define PduRConf_PduRDestPdu_EMS2_DCWh_1803FAF1h_Can_Network_CANNODE_3_PduR2CanIf  46

#define PduRConf_PduRSrcPdu_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3_Com2PduR    47
#define PduRConf_PduRDestPdu_EMS2_DTC_18AAFAF1h_Can_Network_CANNODE_3_PduR2CanIf  47

#define PduRConf_PduRSrcPdu_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3_Com2PduR    48
#define PduRConf_PduRDestPdu_EMS2_HCU_1814FAF1h_Can_Network_CANNODE_3_PduR2CanIf  48

#define PduRConf_PduRSrcPdu_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3_Com2PduR    49
#define PduRConf_PduRDestPdu_EMS2_HV1_1810FAF1h_Can_Network_CANNODE_3_PduR2CanIf  49

#define PduRConf_PduRSrcPdu_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3_Com2PduR    50
#define PduRConf_PduRDestPdu_EMS2_HV2_1811FAF1h_Can_Network_CANNODE_3_PduR2CanIf  50

#define PduRConf_PduRSrcPdu_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3_Com2PduR    51
#define PduRConf_PduRDestPdu_EMS2_PosLog_1806FAF1h_Can_Network_CANNODE_3_PduR2CanIf  51

#define PduRConf_PduRSrcPdu_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3_Com2PduR    52
#define PduRConf_PduRDestPdu_EMS2_PowerModul_1802FAF1h_Can_Network_CANNODE_3_PduR2CanIf  52

#define PduRConf_PduRSrcPdu_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6_Com2PduR    53
#define PduRConf_PduRDestPdu_EMS2_Res_0x181E02F1_Can_Network_CANNODE_6_PduR2CanIf  53

#define PduRConf_PduRSrcPdu_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3_Com2PduR    54
#define PduRConf_PduRDestPdu_EMS2_SystStat_1801FAF1h_Can_Network_CANNODE_3_PduR2CanIf  54

#define PduRConf_PduRSrcPdu_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3_Com2PduR    55
#define PduRConf_PduRDestPdu_EMS2_Timer_1809FAF1h_Can_Network_CANNODE_3_PduR2CanIf  55

#define PduRConf_PduRSrcPdu_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3_Com2PduR    56
#define PduRConf_PduRDestPdu_EMS2_Warning_1808FAF1h_Can_Network_CANNODE_3_PduR2CanIf  56

#define PduRConf_PduRSrcPdu_EMS_0x180102F1_Can_Network_CANNODE_5_Com2PduR    57
#define PduRConf_PduRDestPdu_EMS_0x180102F1_Can_Network_CANNODE_5_PduR2CanIf  57

#define PduRConf_PduRSrcPdu_EMS_0x180202F1_Can_Network_CANNODE_5_Com2PduR    58
#define PduRConf_PduRDestPdu_EMS_0x180202F1_Can_Network_CANNODE_5_PduR2CanIf  58

#define PduRConf_PduRSrcPdu_EMS_0x180302F1_Can_Network_CANNODE_5_Com2PduR    59
#define PduRConf_PduRDestPdu_EMS_0x180302F1_Can_Network_CANNODE_5_PduR2CanIf  59

#define PduRConf_PduRSrcPdu_EMS_0x180402F1_Can_Network_CANNODE_5_Com2PduR    60
#define PduRConf_PduRDestPdu_EMS_0x180402F1_Can_Network_CANNODE_5_PduR2CanIf  60

#define PduRConf_PduRSrcPdu_EMS_0x180502F1_Can_Network_CANNODE_5_Com2PduR    61
#define PduRConf_PduRDestPdu_EMS_0x180502F1_Can_Network_CANNODE_5_PduR2CanIf  61

#define PduRConf_PduRSrcPdu_EMS_0x180602F1_Can_Network_CANNODE_5_Com2PduR    62
#define PduRConf_PduRDestPdu_EMS_0x180602F1_Can_Network_CANNODE_5_PduR2CanIf  62

#define PduRConf_PduRSrcPdu_EMS_0x180702F1_Can_Network_CANNODE_5_Com2PduR    63
#define PduRConf_PduRDestPdu_EMS_0x180702F1_Can_Network_CANNODE_5_PduR2CanIf  63

#define PduRConf_PduRSrcPdu_EMS_0x180802F1_Can_Network_CANNODE_5_Com2PduR    64
#define PduRConf_PduRDestPdu_EMS_0x180802F1_Can_Network_CANNODE_5_PduR2CanIf  64

#define PduRConf_PduRSrcPdu_EMS_0x180902F1_Can_Network_CANNODE_5_Com2PduR    65
#define PduRConf_PduRDestPdu_EMS_0x180902F1_Can_Network_CANNODE_5_PduR2CanIf  65

#define PduRConf_PduRSrcPdu_EMS_0x180A02F1_Can_Network_CANNODE_5_Com2PduR    66
#define PduRConf_PduRDestPdu_EMS_0x180A02F1_Can_Network_CANNODE_5_PduR2CanIf  66

#define PduRConf_PduRSrcPdu_EMS_0x180B02F1_Can_Network_CANNODE_5_Com2PduR    67
#define PduRConf_PduRDestPdu_EMS_0x180B02F1_Can_Network_CANNODE_5_PduR2CanIf  67

#define PduRConf_PduRSrcPdu_EMS_0x180C02F1_Can_Network_CANNODE_5_Com2PduR    68
#define PduRConf_PduRDestPdu_EMS_0x180C02F1_Can_Network_CANNODE_5_PduR2CanIf  68

#define PduRConf_PduRSrcPdu_EMS_0x180D02F1_Can_Network_CANNODE_5_Com2PduR    69
#define PduRConf_PduRDestPdu_EMS_0x180D02F1_Can_Network_CANNODE_5_PduR2CanIf  69

#define PduRConf_PduRSrcPdu_EMS_0x180E02F1_Can_Network_CANNODE_5_Com2PduR    70
#define PduRConf_PduRDestPdu_EMS_0x180E02F1_Can_Network_CANNODE_5_PduR2CanIf  70

#define PduRConf_PduRSrcPdu_EMS_0x180F02F1_Can_Network_CANNODE_5_Com2PduR    71
#define PduRConf_PduRDestPdu_EMS_0x180F02F1_Can_Network_CANNODE_5_PduR2CanIf  71

#define PduRConf_PduRSrcPdu_EMS_0x181002F1_Can_Network_CANNODE_5_Com2PduR    72
#define PduRConf_PduRDestPdu_EMS_0x181002F1_Can_Network_CANNODE_5_PduR2CanIf  72

#define PduRConf_PduRSrcPdu_EMS_0x181102F1_Can_Network_CANNODE_5_Com2PduR    73
#define PduRConf_PduRDestPdu_EMS_0x181102F1_Can_Network_CANNODE_5_PduR2CanIf  73

#define PduRConf_PduRSrcPdu_EMS_0x181202F1_Can_Network_CANNODE_5_Com2PduR    74
#define PduRConf_PduRDestPdu_EMS_0x181202F1_Can_Network_CANNODE_5_PduR2CanIf  74

#define PduRConf_PduRSrcPdu_EMS_0x181302F1_Can_Network_CANNODE_5_Com2PduR    75
#define PduRConf_PduRDestPdu_EMS_0x181302F1_Can_Network_CANNODE_5_PduR2CanIf  75

#define PduRConf_PduRSrcPdu_EMS_0x181402F1_Can_Network_CANNODE_5_Com2PduR    76
#define PduRConf_PduRDestPdu_EMS_0x181402F1_Can_Network_CANNODE_5_PduR2CanIf  76

#define PduRConf_PduRSrcPdu_EMS_0x181502F1_Can_Network_CANNODE_5_Com2PduR    77
#define PduRConf_PduRDestPdu_EMS_0x181502F1_Can_Network_CANNODE_5_PduR2CanIf  77

#define PduRConf_PduRSrcPdu_EMS_0x181602F1_Can_Network_CANNODE_5_Com2PduR    78
#define PduRConf_PduRDestPdu_EMS_0x181602F1_Can_Network_CANNODE_5_PduR2CanIf  78

#define PduRConf_PduRSrcPdu_EMS_0x181702F1_Can_Network_CANNODE_5_Com2PduR    79
#define PduRConf_PduRDestPdu_EMS_0x181702F1_Can_Network_CANNODE_5_PduR2CanIf  79

#define PduRConf_PduRSrcPdu_EMS_0x181802F1_Can_Network_CANNODE_5_Com2PduR    80
#define PduRConf_PduRDestPdu_EMS_0x181802F1_Can_Network_CANNODE_5_PduR2CanIf  80

#define PduRConf_PduRSrcPdu_EMS_0x181902F1_Can_Network_CANNODE_5_Com2PduR    81
#define PduRConf_PduRDestPdu_EMS_0x181902F1_Can_Network_CANNODE_5_PduR2CanIf  81

#define PduRConf_PduRSrcPdu_EMS_0x181A02F1_Can_Network_CANNODE_5_Com2PduR    82
#define PduRConf_PduRDestPdu_EMS_0x181A02F1_Can_Network_CANNODE_5_PduR2CanIf  82

#define PduRConf_PduRSrcPdu_EMS_0x181D02F1_Can_Network_CANNODE_5_Com2PduR    83
#define PduRConf_PduRDestPdu_EMS_0x181D02F1_Can_Network_CANNODE_5_PduR2CanIf  83

#define PduRConf_PduRSrcPdu_EMS_18F82B62h_Can_Network_CANNODE_4_Com2PduR    84
#define PduRConf_PduRDestPdu_EMS_18F82B62h_Can_Network_CANNODE_4_PduR2CanIf  84

#define PduRConf_PduRSrcPdu_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1_Com2PduR    85
#define PduRConf_PduRDestPdu_EMS_ACDC_1813FAF1h_Can_Network_CANNODE_1_PduR2CanIf  85

#define PduRConf_PduRSrcPdu_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1_Com2PduR    86
#define PduRConf_PduRDestPdu_EMS_ACWh_1804FAF1h_Can_Network_CANNODE_1_PduR2CanIf  86

#define PduRConf_PduRSrcPdu_EMS_CML_1805FAF1h_Can_Network_CANNODE_1_Com2PduR    87
#define PduRConf_PduRDestPdu_EMS_CML_1805FAF1h_Can_Network_CANNODE_1_PduR2CanIf  87

#define PduRConf_PduRSrcPdu_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1_Com2PduR    88
#define PduRConf_PduRDestPdu_EMS_ConntSts_1821FAF1h_Can_Network_CANNODE_1_PduR2CanIf  88

#define PduRConf_PduRSrcPdu_EMS_ConntSts_Rx_Can_Network_CANNODE_1_Com2PduR    89
#define PduRConf_PduRDestPdu_EMS_ConntSts_Rx_Can_Network_CANNODE_1_PduR2CanIf  89

#define PduRConf_PduRSrcPdu_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1_Com2PduR    90
#define PduRConf_PduRDestPdu_EMS_Connt_1807FAF1h_Can_Network_CANNODE_1_PduR2CanIf  90

#define PduRConf_PduRSrcPdu_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1_Com2PduR    91
#define PduRConf_PduRDestPdu_EMS_DCDC_1812FAF1h_Can_Network_CANNODE_1_PduR2CanIf  91

#define PduRConf_PduRSrcPdu_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1_Com2PduR    92
#define PduRConf_PduRDestPdu_EMS_DCWh_1803FAF1h_Can_Network_CANNODE_1_PduR2CanIf  92

#define PduRConf_PduRSrcPdu_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1_Com2PduR    93
#define PduRConf_PduRDestPdu_EMS_DTC_18AAFAF1h_Can_Network_CANNODE_1_PduR2CanIf  93

#define PduRConf_PduRSrcPdu_EMS_DiagResp_0x18DAFAF1h_Can_Network_CANNODE_2_Phys_Dcm2PduR    0
#define PduRConf_PduRDestPdu_EMS_DiagResp_0x18DAFAF1h_Can_Network_CANNODE_2_Phys_PduR2CanTp  0

#define PduRConf_PduRSrcPdu_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1_Com2PduR    94
#define PduRConf_PduRDestPdu_EMS_HCU_1814FAF1h_Can_Network_CANNODE_1_PduR2CanIf  94

#define PduRConf_PduRSrcPdu_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1_Com2PduR    95
#define PduRConf_PduRDestPdu_EMS_HV1_1810FAF1h_Can_Network_CANNODE_1_PduR2CanIf  95

#define PduRConf_PduRSrcPdu_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1_Com2PduR    96
#define PduRConf_PduRDestPdu_EMS_HV2_1811FAF1h_Can_Network_CANNODE_1_PduR2CanIf  96

#define PduRConf_PduRSrcPdu_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4_Com2PduR    97
#define PduRConf_PduRDestPdu_EMS_Msg_1806E5F4h_Can_Network_CANNODE_4_PduR2CanIf  97

#define PduRConf_PduRSrcPdu_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1_Com2PduR    98
#define PduRConf_PduRDestPdu_EMS_PosLog_1806FAF1h_Can_Network_CANNODE_1_PduR2CanIf  98

#define PduRConf_PduRSrcPdu_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1_Com2PduR    99
#define PduRConf_PduRDestPdu_EMS_PowerModul_1802FAF1h_Can_Network_CANNODE_1_PduR2CanIf  99

#define PduRConf_PduRSrcPdu_EMS_Res_0x181E02F1_Can_Network_CANNODE_5_Com2PduR    100
#define PduRConf_PduRDestPdu_EMS_Res_0x181E02F1_Can_Network_CANNODE_5_PduR2CanIf  100

#define PduRConf_PduRSrcPdu_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1_Com2PduR    101
#define PduRConf_PduRDestPdu_EMS_SystStat_1801FAF1h_Can_Network_CANNODE_1_PduR2CanIf  101

#define PduRConf_PduRSrcPdu_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1_Com2PduR    102
#define PduRConf_PduRDestPdu_EMS_Timer_1809FAF1h_Can_Network_CANNODE_1_PduR2CanIf  102

#define PduRConf_PduRSrcPdu_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1_Com2PduR    103
#define PduRConf_PduRDestPdu_EMS_Warning_1808FAF1h_Can_Network_CANNODE_1_PduR2CanIf  103

#define PduRConf_PduRSrcPdu_HCU2_Syst_18220145h_Can_Network_CANNODE_3_CanIf2PduR    94

#define PduRConf_PduRSrcPdu_HCU_Syst_18220145h_Can_Network_CANNODE_1_CanIf2PduR    95

#define PduRConf_PduRSrcPdu_TBOX2_0x1801F102_Can_Network_CANNODE_6_CanIf2PduR    96

#define PduRConf_PduRSrcPdu_TBOX2_0x1802F102_Can_Network_CANNODE_6_CanIf2PduR    97

#define PduRConf_PduRSrcPdu_TBOX2_0x1803F102_Can_Network_CANNODE_6_CanIf2PduR    98

#define PduRConf_PduRSrcPdu_TBOX2_0x1804F102_Can_Network_CANNODE_6_CanIf2PduR    99

#define PduRConf_PduRSrcPdu_TBOX2_0x1805F102_Can_Network_CANNODE_6_CanIf2PduR    100

#define PduRConf_PduRSrcPdu_TBOX2_0x1806F102_Can_Network_CANNODE_6_CanIf2PduR    101

#define PduRConf_PduRSrcPdu_TBOX2_0x1807F102_Can_Network_CANNODE_6_CanIf2PduR    102

#define PduRConf_PduRSrcPdu_TBOX2_0x1808F102_Can_Network_CANNODE_6_CanIf2PduR    103

#define PduRConf_PduRSrcPdu_TBOX2_0x1809F102_Can_Network_CANNODE_6_CanIf2PduR    104

#define PduRConf_PduRSrcPdu_TBOX2_0x180AF102_Can_Network_CANNODE_6_CanIf2PduR    105

#define PduRConf_PduRSrcPdu_TBOX2_0x180BF102_Can_Network_CANNODE_6_CanIf2PduR    106

#define PduRConf_PduRSrcPdu_TBOX2_0x180CF102_Can_Network_CANNODE_6_CanIf2PduR    107

#define PduRConf_PduRSrcPdu_TBOX2_0x180DF102_Can_Network_CANNODE_6_CanIf2PduR    108

#define PduRConf_PduRSrcPdu_TBOX2_0x180EF102_Can_Network_CANNODE_6_CanIf2PduR    109

#define PduRConf_PduRSrcPdu_TBOX2_0x180FF102_Can_Network_CANNODE_6_CanIf2PduR    110

#define PduRConf_PduRSrcPdu_TBOX2_0x18FFF102_Can_Network_CANNODE_6_CanIf2PduR    111

#define PduRConf_PduRSrcPdu_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3_Com2PduR    104
#define PduRConf_PduRDestPdu_TBOX2_DTC_0x18AAF8F1_Can_Network_CANNODE_3_PduR2CanIf  104

#define PduRConf_PduRSrcPdu_TBOX_0x1801F102_Can_Network_CANNODE_5_CanIf2PduR    112

#define PduRConf_PduRSrcPdu_TBOX_0x1802F102_Can_Network_CANNODE_5_CanIf2PduR    113

#define PduRConf_PduRSrcPdu_TBOX_0x1803F102_Can_Network_CANNODE_5_CanIf2PduR    114

#define PduRConf_PduRSrcPdu_TBOX_0x1804F102_Can_Network_CANNODE_5_CanIf2PduR    115

#define PduRConf_PduRSrcPdu_TBOX_0x1805F102_Can_Network_CANNODE_5_CanIf2PduR    116

#define PduRConf_PduRSrcPdu_TBOX_0x1806F102_Can_Network_CANNODE_5_CanIf2PduR    117

#define PduRConf_PduRSrcPdu_TBOX_0x1807F102_Can_Network_CANNODE_5_CanIf2PduR    118

#define PduRConf_PduRSrcPdu_TBOX_0x1808F102_Can_Network_CANNODE_5_CanIf2PduR    119

#define PduRConf_PduRSrcPdu_TBOX_0x1809F102_Can_Network_CANNODE_5_CanIf2PduR    120

#define PduRConf_PduRSrcPdu_TBOX_0x180AF102_Can_Network_CANNODE_5_CanIf2PduR    121

#define PduRConf_PduRSrcPdu_TBOX_0x180BF102_Can_Network_CANNODE_5_CanIf2PduR    122

#define PduRConf_PduRSrcPdu_TBOX_0x180CF102_Can_Network_CANNODE_5_CanIf2PduR    123

#define PduRConf_PduRSrcPdu_TBOX_0x180DF102_Can_Network_CANNODE_5_CanIf2PduR    124

#define PduRConf_PduRSrcPdu_TBOX_0x180EF102_Can_Network_CANNODE_5_CanIf2PduR    125

#define PduRConf_PduRSrcPdu_TBOX_0x180FF102_Can_Network_CANNODE_5_CanIf2PduR    126

#define PduRConf_PduRSrcPdu_TBOX_0x18FFF102_Can_Network_CANNODE_5_CanIf2PduR    127

#define PduRConf_PduRSrcPdu_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1_Com2PduR    105
#define PduRConf_PduRDestPdu_TBOX_DTC_0x18AAF8F1_Can_Network_CANNODE_1_PduR2CanIf  105

#define PduRConf_PduRSrcPdu_Tester2_18FFFA01h_MUX1_IpduM2PduR    20

#define PduRConf_PduRSrcPdu_Tester2_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_3_CanIf2PduR    128

#define PduRConf_PduRSrcPdu_Tester_18FFFA01h_MUX1_IpduM2PduR    21

#define PduRConf_PduRSrcPdu_Tester_18FFFA01h_Multiplexed_IPDU_Can_Network_CANNODE_1_CanIf2PduR    129

#define PduRConf_PduRSrcPdu_Tester_DiagFunReq_0x18DBFFFAh_Can_Network_CANNODE_2_Func_CanTp2PduR    0
#define PduRConf_PduRDestPdu_Tester_DiagFunReq_0x18DBFFFAh_Can_Network_CANNODE_2_Func_PduR2Dcm  0

#define PduRConf_PduRSrcPdu_Tester_DiagPhyReq_0x18DAF1FAh_Can_Network_CANNODE_2_Phys_CanTp2PduR    1
#define PduRConf_PduRDestPdu_Tester_DiagPhyReq_0x18DAF1FAh_Can_Network_CANNODE_2_Phys_PduR2Dcm  1


#define PduRConf_PduRSrcPdu_EthernetPdu_Rx_SoAd2Com_Src    0
#define PduRConf_PduRDestPdu_EthernetPdu_Rx_SoAd2Com_Dest  0

#define PduRConf_PduRSrcPdu_EthernetPdu_Tx_Com2PduR_Src    106
#define PduRConf_PduRDestPdu_EthernetPdu_Tx_PduR2SoAd_Dest  0



#endif /* PDUR_CFG_SYMBOLICNAMES_H */
