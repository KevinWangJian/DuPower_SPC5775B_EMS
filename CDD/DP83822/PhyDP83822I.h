/*
 * PhyDP83822I.h
 *
 *  Created on: 2019Äê10ÔÂ23ÈÕ
 *      Author: admin
 */

#ifndef USERS_PHYDP83822I_H_
#define USERS_PHYDP83822I_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"
#include "Reg_eSys.h"
#include "StdRegMacros.h"
#include "Dio_Cfg.h"
#include "Dio.h"


#define USE_MCAL											(1U)

#define ETH_DP83822_TRANS_TEST_ENABLE						(0U)

#define ETH_100BASETX_TRANSMIT_TEST_ENABLE					(1U)

#define ETH_PHY_CHIP_RESET_ENABLE							(1U)

#define ETH_DP83822_PHY_CHIP_NUM							(2U)

/* DP83822HF Device PHY address */
#define DP83822HF_PHY_1_ADDRESS								(0x01U)
#define DP83822HF_PHY_2_ADDRESS								(0x02U)

#define PHY_DP83822HF_RESET_1_LOW()							Dio_WriteChannel(DioConf_DioChannel_DP83822HF_1_RESET, STD_LOW)
#define PHY_DP83822HF_RESET_1_HIGH()						Dio_WriteChannel(DioConf_DioChannel_DP83822HF_1_RESET, STD_HIGH)

#define PHY_DP83822HF_RESET_2_LOW()							Dio_WriteChannel(DioConf_DioChannel_DP83822HF_2_RESET, STD_LOW)
#define PHY_DP83822HF_RESET_2_HIGH()						Dio_WriteChannel(DioConf_DioChannel_DP83822HF_2_RESET, STD_HIGH)


/* Register definition. */
#define DP83822HF_BMCR_REG									(0x0000)
#define DP83822HF_BMCR_REG_Reset_Mask						((uint16_t)1 << 15)
#define DP83822HF_BMCR_REG_MiiLoopback_Mask					((uint16_t)1 << 14)
#define DP83822HF_BMCR_REG_SpeedSel_Mask					((uint16_t)1 << 13)
#define DP83822HF_BMCR_REG_AutoNegotiationEnable_Mask		((uint16_t)1 << 12)
#define DP83822HF_BMCR_REG_IEEEPowerDown_Mask				((uint16_t)1 << 11)
#define DP83822HF_BMCR_REG_Isolate_Mask						((uint16_t)1 << 10)
#define DP83822HF_BMCR_REG_RestartAutoNeg_Mask				((uint16_t)1 << 9)
#define DP83822HF_BMCR_REG_DuplexMode_Mask					((uint16_t)1 << 8)
#define DP83822HF_BMCR_REG_Collision_Mask					((uint16_t)1 << 7)

#define DP83822HF_BMSR_REG									(0x0001)
#define DP83822HF_BMSR_REG_100Base_T4_Mask					((uint16_t)1 << 15)
#define DP83822HF_BMSR_REG_100Base_TX_FullDuplex_Mask		((uint16_t)1 << 14)
#define DP83822HF_BMSR_REG_100Base_TX_HalfDuplex_Mask		((uint16_t)1 << 13)
#define DP83822HF_BMSR_REG_10Base_Te_FullDuplex_Mask		((uint16_t)1 << 12)
#define DP83822HF_BMSR_REG_10Base_Te_HalfDuplex_Mask		((uint16_t)1 << 11)
#define DP83822HF_BMSR_REG_SMI_PreambleSuppression_Mask		((uint16_t)1 << 6)
#define DP83822HF_BMSR_REG_AutoNegoComplete_Mask			((uint16_t)1 << 5)
#define DP83822HF_BMSR_REG_RemoteFault_Mask					((uint16_t)1 << 4)
#define DP83822HF_BMSR_REG_AutoNegoAbility_Mask				((uint16_t)1 << 3)
#define DP83822HF_BMSR_REG_LinkStatus_Mask					((uint16_t)1 << 2)
#define DP83822HF_BMSR_REG_JabberDetect_Mask				((uint16_t)1 << 1)
#define DP83822HF_BMSR_REG_ExtendedCapability_Mask			((uint16_t)1 << 0)

#define DP83822HF_PHY_ID1_REG								(0x0002)
#define DP83833HF_PHY_ID1_REG_UniqueIdHigh_Mask				((uint16_t)0xffff << 0)

#define DP83822HF_PHY_ID2_REG								(0x0003)
#define DP83822HF_PHY_ID2_REG_UniqueIdLow_Mask				((uint16_t)0x3F << 10)
#define DP83822HF_PHY_ID2_REG_ModelNum_Mask					((uint16_t)0x3F << 4)
#define DP83822HF_PHY_ID2_REG_RevisionNum_Mask				((uint16_t)0xF << 0)

#define DP83822HF_ANAR_REG									(0x0004)
#define DP83822HF_ANAR_REG_NextPage_Mask					((uint16_t)1 << 15)
#define DP83822HF_ANAR_REG_RemoteFault_Mask					((uint16_t)1 << 13)

#define DP83822HF_ANLPAR_REG								(0x0005)
#define DP83822HF_ANLPAR_REG_100Base_T4_Mask				((uint16_t)1 << 9)

#define DP83822HF_ANER_REG									(0x0006)
#define DP83822HF_ANER_REG_ParallelDetectFault_Mask			((uint16_t)1 << 4)
#define DP83822HF_ANER_REG_LinkPartnerNextPageAble_Mask		((uint16_t)1 << 3)
#define DP83822HF_ANER_REG_LocalDevNextPageAble_Mask		((uint16_t)1 << 2)
#define DP83822HF_ANER_REG_PageReceived_Mask				((uint16_t)1 << 1)
#define DP83822HF_ANER_REG_LinkPartnerAutoNegoAble_Mask		((uint16_t)1 << 0)

#define DP83822HF_ANNPTR_REG								(0x0007)

#define DP83822HF_ANLNPTR_REG								(0x0008)

#define DP83822HF_CR1_REG									(0x0009)
#define DP83822HF_CR1_REG_RMII_EnhancedMode_Mask			((uint16_t)1 << 9)
#define DP83822HF_CR1_REG_TDRAutoRun_Mask					((uint16_t)1 << 8)
#define DP83822HF_CR1_REG_LinkLossRecovery_Mask				((uint16_t)1 << 7)
#define DP83822HF_CR1_REG_FastAutoMDIX_Mask					((uint16_t)1 << 6)
#define DP83822HF_CR1_REG_RobustAutoMDIX_Mask				((uint16_t)1 << 5)
#define DP83822HF_CR1_REG_FastAutoNegoEnable_Mask			((uint16_t)1 << 4)
#define DP83822HF_CR1_REG_FastAutoNegoSelect_Mask			((uint16_t)3 << 2)
#define DP83822HF_CR1_REG_FastRXDVDetection_Mask			((uint16_t)1 << 1)

#define DP83822HF_CR2_REG									(0x000A)
#define DP83822HF_CR2_REG_100Base_FX_Enable_Mask			((uint16_t)1 << 14)
#define DP83822HF_CR2_REG_FastLinkUpParallelDetect_Mask		((uint16_t)1 << 6)
#define DP83822HF_CR2_REG_ExtendFullDuplexAbility_Mask		((uint16_t)1 << 5)
#define DP83822HF_CR2_REG_EnhancedLedLink_Mask				((uint16_t)1 << 4)
#define DP83822HF_CR2_REG_IsolateMii_Mask					((uint16_t)1 << 3)
#define DP83822HF_CR2_REG_RX_ER_Mask						((uint16_t)1 << 2)
#define DP83822HF_CR2_REG_OddNibDetectDisable_Mask			((uint16_t)1 << 1)
#define DP83822HF_CR2_REG_RMII_RxClock_Mask					((uint16_t)1 << 0)

#define DP83822HF_CR3_REG									(0x000B)
#define DP83822HF_CR3_REG_DescramblerFastLinkDown_Mask		((uint16_t)1 << 10)
#define DP83822HF_CR3_REG_PolaritySwap_Mask					((uint16_t)1 << 6)
#define DP83822HF_CR3_REG_MDI_MDIX_Swap_Mask				((uint16_t)1 << 5)
#define DP83822HF_CR3_REG_FastLinkDownMode_Mask				((uint16_t)0xF << 0)

#define DP83822HF_REGCR_REG									(0x000D)
#define DP83822HF_REGCR_REG_ExtendCommand_Mask				((uint16_t)3 << 14)
#define DP83822HF_REGCR_REG_DEVAD_Mask						((uint16_t)0x1F << 0)

#define DP83822HF_ADDAR_REG									(0x000E)
#define DP83822HF_ADDAR_REG_Address_Data_Mask				((uint16_t)0xffff << 0)

#define DP83822HF_FLDS_REG									(0x000F)
#define DP83822HF_FLDS_REG_FastLinkDownSta_Mask				((uint16_t)0x1f << 4)

#define DP83822HF_PHYSTS_REG								(0x0010)
#define DP83822HF_PHYSTS_REG_MDI_MDIX_Mode_Mask				((uint16_t)1 << 14)
#define DP83822HF_PHYSTS_REG_ReceiveErr_Mask				((uint16_t)1 << 13)
#define DP83822HF_PHYSTS_REG_PolarityStatus_Mask			((uint16_t)1 << 12)
#define DP83822HF_PHYSTS_REG_AutoNegoStatus_Mask			((uint16_t)1 << 4)
#define DP83822HF_PHYSTS_REG_MIILoopbackStatus_Mask			((uint16_t)1 << 3)
#define DP83822HF_PHYSTS_REG_DuplexStatus_Mask				((uint16_t)1 << 2)
#define DP83822HF_PHYSTS_REG_SpeedStatus_Mask				((uint16_t)1 << 1)
#define DP83822HF_PHYSTS_REG_LinkStatus_Mask				((uint16_t)1 << 0)

#define DP83822HF_PHYSCR_REG								(0x0011)
#define DP83822HF_PHYSCR_REG_DisablePLL_Mask				((uint16_t)1 << 15)
#define DP83822HF_PHYSCR_REG_PowerSaveModeEnable_Mask		((uint16_t)1 << 14)
#define DP83822HF_PHYSCR_REG_PowerSaveMode_Mask				((uint16_t)3 << 12)
#define DP83822HF_PHYSCR_REG_LoopbackFifoDepth_Mask			((uint16_t)3 << 8)
#define DP83822HF_PHYSCR_REG_COL_FullDuplexEnable_Mask		((uint16_t)1 << 4)
#define DP83822HF_PHYSCR_REG_InterruptPolarity_Mask			((uint16_t)1 << 3)
#define DP83822HF_PHYSCR_REG_TestInterrupt_Mask				((uint16_t)1 << 2)
#define DP83822HF_PHYSCR_REG_InterruptEnable_Mask			((uint16_t)1 << 1)
#define DP83822HF_PHYSCR_REG_InterruptOutputEnable_Mask		((uint16_t)1 << 0)

#define DP83822HF_MISR1_REG									(0x0012)
#define DP83822HF_MISR1_REG_LinkQualityInt_Mask				((uint16_t)1 << 15)
#define DP83822HF_MISR1_REG_EnergyDetectInt_Mask			((uint16_t)1 << 14)
#define DP83822HF_MISR1_REG_LinkStatusChangeInt_Mask		((uint16_t)1 << 13)
#define DP83822HF_MISR1_REG_SpeedChangeInt_Mask				((uint16_t)1 << 12)
#define DP83822HF_MISR1_REG_DuplexModeChangeInt_Mask		((uint16_t)1 << 11)
#define DP83822HF_MISR1_REG_AutoNegoCompleteInt_Mask		((uint16_t)1 << 10)
#define DP83822HF_MISR1_REG_FalseCarrierCntHalfFulInt_Mask	((uint16_t)1 << 9)
#define DP83822HF_MISR1_REG_ReceiveErrCntHalfFullInt_Mask	((uint16_t)1 << 8)
#define DP83822HF_MISR1_REG_LinkQualityIntEnable_Mask		((uint16_t)1 << 7)
#define DP83822HF_MISR1_REG_EnergyDetectIntEnable_Mask		((uint16_t)1 << 6)
#define DP83822HF_MISR1_REG_LinkStatusChangeIntEnable_Mask	((uint16_t)1 << 5)
#define DP83822HF_MISR1_REG_SpeedChangeIntEnbale_Mask		((uint16_t)1 << 4)
#define DP83822HF_MISR1_REG_DuplexModeChangeIntEnable_Mask	((uint16_t)1 << 3)
#define DP83822HF_MISR1_REG_AutoNegoCompleteIntEnable_Mask	((uint16_t)1 << 2)
#define DP83822HF_MISR1_REG_FalseCarrierHfEnable_Mask		((uint16_t)1 << 1)
#define DP83822HF_MISR1_REG_ReceiveErrHfEnable_Mask			((uint16_t)1 << 0)

#define DP83822HF_MISR2_REG									(0x0013)

#define DP83822HF_FCSCR_REG									(0x0014)
#define DP83822HF_FCSCR_REG_FalseCarrierEvtCounter_Mask		((uint16_t)0xff << 0)

#define DP83822HF_RECR_REG									(0x0015)

#define DP83822HF_BISCR_REG									(0x0016)
#define DP83822HF_BISCR_REG_TransmitMIILoopback_Mask		((uint16_t)1 << 6)
#define DP83822HF_BISCR_REG_LoopbackMode_Mask				((uint16_t)0x1f << 0)

#define DP83822HF_RCSR_REG									(0x0017)

#define DP83822HF_LEDCR_REG									(0x0018)
#define DP83822HF_LEDCR_REG_BlinkRate_Mask					((uint16_t)3 << 9)
#define DP83822HF_LEDCR_REG_LED0Palarity_Mask				((uint16_t)1 << 7)
#define DP83822HF_LEDCR_REG_DriveLED0_Mask					((uint16_t)1 << 4)
#define DP83822HF_LEDCR_REG_LED0_ON_OFF_Mask				((uint16_t)1 << 1)

#define DP83822HF_PHYCR_REG									(0x0019)
#define DP83822HF_PHYCR_REG_MIILinkStatus_Mask				((uint16_t)1 << 11)
#define DP83822HF_PHYCR_REG_BypassLEDStretching_Mask		((uint16_t)1 << 7)
#define DP83822HF_PHYCR_REG_LEDConfiguration_Mask			((uint16_t)1 << 5)
#define DP83822HF_PHYCR_REG_PHYADDRESS_Mask					((uint16_t)0x1f << 0)

#define DP83822HF_10BTSCR_REG								(0x001A)

#define DP83822HF_BICSR1_REG								(0x001B)

#define DP83822HF_BICSR2_REG								(0x001C)

#define DP83822HF_CDCR_REG									(0x001E)

#define DP83822HF_PHYRCR_REG								(0x001F)
#define DP83822HF_PHYRCR_REG_SoftwareReset_Mask				((uint16_t)1 << 15)
#define DP83822HF_PHYRCR_REG_DigitalRestart_Mask			((uint16_t)1 << 14)

/********************************************************************************************/
#define DP83822HF_LEDCFG1_REG								(0x0460)
#define DP83822HF_LEDCFG1_REG_LED1Contrl_Mask				((uint16_t)0xf << 8)
#define DP83822HF_LEDCFG1_REG_LED1Contrl(x)					((uint16_t)x << 8)
#define DP83822HF_LEDCFG1_REG_LED3Contrl(x)					((uint16_t)x << 4)
#define DP83822HF_LEDCFG1_REG_LED3Contrl_Mask				((uint16_t)0xf << 4)

#define DP83822HF_IOCTRL_REG								(0x0461)
#define DP83822HF_IOCTRL_REG_LED1GPIO1Ctrl_Mask				((uint16_t)7 << 0)

#define DP83822HF_IOCTRL1_REG								(0x0462)
#define DP83822HF_IOCTRL1_REG_LED1GPIOCtrl(x)				((uint16_t)x << 0)

#define DP83822HF_LEDCFG2_REG								(0x0469)
#define DP83822HF_LEDCFG2_REG_LED1Palarity_Mask				((uint16_t)1 << 10)
#define DP83822HF_LEDCFG2_REG_LED1ForceValue_Mask			((uint16_t)1 << 9)
#define DP83822HF_LEDCFG2_REG_LED1ForceEnable_Mask			((uint16_t)1 << 8)
#define DP83822HF_LEDCFG2_REG_LED3Palarity_Mask				((uint16_t)1 << 6)
#define DP83822HF_LEDCFG2_REG_LED3ForceValue_Mask			((uint16_t)1 << 5)
#define DP83822HF_LEDCFG2_REG_LED3ForceEnable_Mask			((uint16_t)1 << 4)


typedef enum
{
	Link_Not_Established = 0,
	Valid_Link_Established = 1
}PhyLinkState;

typedef enum
{
	AutoNegotiation_Not_Complete = 0,
	AutoNegotiation_Complete = 1
}PhyAutoNegotiationState;

typedef enum
{
	HalfDuplexMode = 0,
	FullDuplexMode = 1
}PhyDuplexModeState;

typedef enum
{
	Speed_100MbpsMode = 0,
	Speed_10MbpsMode = 1
}PhySpeedModeState;

typedef enum
{
	NoActive_100BaseTxFullDuplexLink = 0,
	Active_100BaseTxFullDuplexLink = 1
}PhyMIILinkState;


typedef struct
{
	uint8_t 				PhyAddress;
	PhyLinkState 			PhyLinkStatus;
	PhyAutoNegotiationState AutoNegotiationCompleteStatus;
	PhyDuplexModeState 		DuplexStatus;
	PhySpeedModeState 		SpeedStatus;
	PhyMIILinkState 		MiiLinkStatus;
}PHY_DP83822_ProTypeDef;


extern PHY_DP83822_ProTypeDef PHY_DP83822HF_Prop[ETH_DP83822_PHY_CHIP_NUM];


int PHY_DP83822_Init(void);
void PHY_DP83822_MainFunction(void);


#ifdef __cplusplus
}
#endif
#endif /* USERS_PHYDP83822I_H_ */
