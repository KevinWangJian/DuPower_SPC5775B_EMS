/*
 * PhyDP83822I.c
 *
 *  Created on: 2019Äê10ÔÂ23ÈÕ
 *      Author: admin
 */

#include "PhyDP83822I.h"
#include "Eth.h"
#include "EthComm.h"
#include "Eth_GeneralTypes.h"
#include "Std_Types.h"

#include "EthTrcv_Prv.h"
#include "EthTrcv.h"
#include "EthSM.h"
#include "EthIf_PbCfg.h"
#include "EthIf_Cbk.h"

#include "TcpIp_Cfg.h"
#include "TcpIp.h"
#include "TcpIp_PbCfg.h"
#include "TcpIp_Prv.h"


PHY_DP83822_ProTypeDef PHY_DP83822HF_Prop[ETH_DP83822_PHY_CHIP_NUM] = {0};


/*
@brief
@details
@para
@return
*/
static void CntDelay(uint32_t cnt)
{
	while (cnt--){;}
}

/*
@brief Write data to DP83822HF chip internal registers by SMI interface.
@para phyAddr, DP83822HF PHY address;
@para regAddr, internal register address;
@para WtData, the new write data;
@return 1,success; 0,failed;
*/
static int PHY_DP83822_SMIWriteRegData(const uint8_t phyAddr, const uint16_t regAddr, const uint16_t WtData)
{
	uint8_t MMD, ExtendRegCmd;
	uint16_t writeData, writeAddr;
	uint8_t dummyCount;
	Eth_ReturnType ret;

	if (regAddr <= 0x001FU)
	{
		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)regAddr, (uint16)WtData);

		if (ret != ETH_OK)
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (1);
		}
	}
	else if ((regAddr > 0x001FU) && (regAddr <= 0x04D1U))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x1FU;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)regAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01U;	/* Data command no post increment. */
				MMD = 0x1FU;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)WtData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else if ((regAddr >= 0x3000U) && (regAddr <= 0x3016U))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x03U;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			writeAddr = regAddr;
			writeAddr &= 0x0FFFU;

			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)writeAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01U;	/* Data command no post increment. */
				MMD = 0x03U;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)WtData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else if ((regAddr >= 0x703CU) && (regAddr <= 0x703DU))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x07U;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			writeAddr = regAddr;
			writeAddr &= 0x0FFFU;

			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)writeAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01U;	/* Data command no post increment. */
				MMD = 0x07U;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)WtData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else
	{
		dummyCount = 0;
		/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
		while (dummyCount < 3U)dummyCount++;
		return (0);
	}
}

/*
@brief Read data from DP83822HF chip internal registers by SMI interface.
@para phyAddr, DP83822HF PHY address;
@para regAddr, internal register address;
@para *pRdData, a pointer to the read-out register value;
@return 1,success; 0,failed;
*/
static int PHY_DP83822_SMIReadRegData(const uint8_t phyAddr, const uint16_t regAddr, uint16_t* pRdData)
{
	uint8_t MMD, ExtendRegCmd;
	uint16_t writeData, writeAddr;
	uint8_t dummyCount;
	Eth_ReturnType ret;

	if (regAddr <= 0x001FU)
	{
		ret = Eth_ReadMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)regAddr, (uint16 *)pRdData);

		if (ret == ETH_OK)
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (1);
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else if ((regAddr > 0x001FU) && (regAddr <= 0x04D1U))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x1FU;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)regAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01U;	/* Data command no post increment. */
				MMD = 0x1FU;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_ReadMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16 *)pRdData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else if ((regAddr >= 0x3000U) && (regAddr <= 0x3016U))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x03U;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			writeAddr = regAddr;
			writeAddr &= 0x0FFFU;

			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)writeAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01;	/* Data command no post increment. */
				MMD = 0x03;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_ReadMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16 *)pRdData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else if ((regAddr >= 0x703CU) && (regAddr <= 0x703DU))
	{
		ExtendRegCmd = 0x00U;	/* Address command */
		MMD = 0x07U;
		writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

		ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

		if (ret == ETH_OK)
		{
			writeAddr = regAddr;
			writeAddr &= 0x0FFFU;

			ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16)writeAddr);

			if (ret == ETH_OK)
			{
				ExtendRegCmd = 0x01U;	/* Data command no post increment. */
				MMD = 0x07U;
				writeData = ((uint16_t)ExtendRegCmd << 14) + MMD;

				ret = Eth_WriteMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_REGCR_REG, (uint16)writeData);

				if (ret == ETH_OK)
				{
					ret = Eth_ReadMii((uint8)CTRL_INDEX, (uint8)phyAddr, (uint8)DP83822HF_ADDAR_REG, (uint16 *)pRdData);

					if (ret == ETH_OK)
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (1);
					}
					else
					{
						dummyCount = 0;
						/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
						while (dummyCount < 3U)dummyCount++;
						return (0);
					}
				}
				else
				{
					dummyCount = 0;
					/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
					while (dummyCount < 3U)dummyCount++;
					return (0);
				}
			}
			else
			{
				dummyCount = 0;
				/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
				while (dummyCount < 3U)dummyCount++;
				return (0);
			}
		}
		else
		{
			dummyCount = 0;
			/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
			while (dummyCount < 3U)dummyCount++;
			return (0);
		}
	}
	else
	{
		dummyCount = 0;
		/* Execute several empty operation to enable system can set breakpoint here when in debug mode. */
		while (dummyCount < 3U)dummyCount++;
		return (0);
	}
}

/*
@brief Initialize DP83822 PHY chips.
@para None.
@para None.
@return 0, Failed; 1; Successfully;
*/
int PHY_DP83822_Init(void)
{
	int result;
	uint16_t WriteRegData;
	uint16_t RegRdData;
	uint32_t timeoutCnt;

	/* Hardware reset DP83822I chips. */
	PHY_DP83822HF_RESET_1_LOW();
	PHY_DP83822HF_RESET_2_LOW();
	CntDelay(500000);
	PHY_DP83822HF_RESET_1_HIGH();
	PHY_DP83822HF_RESET_2_HIGH();

	/********************** 1, Reset DP83822 PHY chips *******************/
	/* Reset PHY_1 chip. */
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_BMCR_REG, DP83822HF_BMCR_REG_Reset_Mask) == 0)
	{
		result = 0;
		return (result);
	}

	/* Wait reset sequence completely. */
	timeoutCnt = 0;
	while (((RegRdData & DP83822HF_BMCR_REG_Reset_Mask) != 0) && (timeoutCnt < 0x10000000U));
	{
		if (PHY_DP83822_SMIReadRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_BMCR_REG, &RegRdData) == 0)
		{
			result = 0;
			return (result);
		}
		timeoutCnt++;
	}
	if (timeoutCnt >= 0x10000000U)
	{
		result = 0;
		return (result);
	}

	/* Reset PHY_2 chip. */
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_BMCR_REG, DP83822HF_BMCR_REG_Reset_Mask) == 0)
	{
		result = 0;
		return (result);
	}

	/* Wait reset sequence completely. */
	timeoutCnt = 0;
	RegRdData  = 0;
	while (((RegRdData & DP83822HF_BMCR_REG_Reset_Mask) != 0) && (timeoutCnt < 0x10000000U));
	{
		if (PHY_DP83822_SMIReadRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_BMCR_REG, &RegRdData) == 0)
		{
			result = 0;
			return (result);
		}
		timeoutCnt++;
	}
	if (timeoutCnt >= 0x10000000U)
	{
		result = 0;
		return (result);
	}

	/********************** 2, Configure PHY work mode and speed *******************/
	WriteRegData = 0;
	/* MII normal operation, 100Mbps, Enable Auto_negotiation, Full-duplex mode. */
	WriteRegData |= (DP83822HF_BMCR_REG_SpeedSel_Mask | \
			         DP83822HF_BMCR_REG_AutoNegotiationEnable_Mask | \
					 DP83822HF_BMCR_REG_DuplexMode_Mask);

	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_BMCR_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_BMCR_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}

	/********************** 3, Configure PHY link loss recovery *******************/
	WriteRegData  = 0;
	/* Enable execution of TDR procedure, Enable Link loss recovery mechanism. */
	WriteRegData |= (DP83822HF_CR1_REG_TDRAutoRun_Mask | DP83822HF_CR1_REG_LinkLossRecovery_Mask);

	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_CR1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_CR1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}

	/********************** 4, Configure PHY LED1 light link on and blink when TX and RX activity *******************/
	WriteRegData = 0;
	/* LEDCFG1 Control: LED_1 LINK OK / BLINK on TX/RX Activity. */
	WriteRegData |= (DP83822HF_LEDCFG1_REG_LED1Contrl(0x8) | (DP83822HF_LEDCFG1_REG_LED3Contrl(0x5)) | (0x01));

	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_LEDCFG1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_LEDCFG1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}

	/********************** 5, Configure PHY LED1 light work as GPIO output mode *******************/
	WriteRegData  = 0;
	/* IOCTRL1 Control: LED_1 config to GPIO output.  */
	WriteRegData |= DP83822HF_IOCTRL1_REG_LED1GPIOCtrl(0x1);

	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_1_ADDRESS, DP83822HF_IOCTRL1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}
	if (PHY_DP83822_SMIWriteRegData(DP83822HF_PHY_2_ADDRESS, DP83822HF_IOCTRL1_REG, WriteRegData) == 0)
	{
		result = 0;
		return (result);
	}

	return (1);
}

/*
@brief Polling current DP83822 PHY link status,speed information and other properties.
@details This func should be called by user's APP program to polling DP83822 PHY status periodically.
@para None.
@return None.
*/
void PHY_DP83822_MainFunction(void)
{
	uint16_t RegRdData;
	uint8_t index;
	int result;
	uint8_t PHY_BASEADDR = DP83822HF_PHY_1_ADDRESS;

	for (index = 0; index < ETH_DP83822_PHY_CHIP_NUM; index++)
	{
		result = PHY_DP83822_SMIReadRegData((PHY_BASEADDR + index), DP83822HF_BMSR_REG, &RegRdData);

		if (result == 1)
		{
			PHY_DP83822HF_Prop[index].PhyLinkStatus = (PhyLinkState)((RegRdData & DP83822HF_BMSR_REG_LinkStatus_Mask) >> 2);
			PHY_DP83822HF_Prop[index].AutoNegotiationCompleteStatus = (PhyAutoNegotiationState)((RegRdData & DP83822HF_BMSR_REG_AutoNegoComplete_Mask) >> 5);
		}
		else
		{
			PHY_DP83822HF_Prop[index].PhyLinkStatus = 0;
			PHY_DP83822HF_Prop[index].AutoNegotiationCompleteStatus = 0;
		}

		result = PHY_DP83822_SMIReadRegData((PHY_BASEADDR + index), DP83822HF_PHYSTS_REG, &RegRdData);

		if (result == 1)
		{
			PHY_DP83822HF_Prop[index].DuplexStatus = (PhyDuplexModeState)((RegRdData & DP83822HF_PHYSTS_REG_DuplexStatus_Mask) >> 2);
			PHY_DP83822HF_Prop[index].SpeedStatus = (PhySpeedModeState)((RegRdData & DP83822HF_PHYSTS_REG_SpeedStatus_Mask) >> 1);
		}
		else
		{
			PHY_DP83822HF_Prop[index].DuplexStatus = 0;
			PHY_DP83822HF_Prop[index].SpeedStatus = 0;
		}

		result = PHY_DP83822_SMIReadRegData((PHY_BASEADDR + index), DP83822HF_PHYCR_REG, &RegRdData);

		if (result == 1)
		{
			PHY_DP83822HF_Prop[index].MiiLinkStatus = (PhyMIILinkState)((RegRdData & DP83822HF_PHYCR_REG_MIILinkStatus_Mask) >> 11);
			PHY_DP83822HF_Prop[index].PhyAddress = (uint8_t)((RegRdData & DP83822HF_PHYCR_REG_PHYADDRESS_Mask) >> 0);
		}
		else
		{
			PHY_DP83822HF_Prop[index].MiiLinkStatus = 0;
			PHY_DP83822HF_Prop[index].PhyAddress = 0;
		}
	}
}



