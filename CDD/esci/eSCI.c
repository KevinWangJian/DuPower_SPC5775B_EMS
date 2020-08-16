
#include <stdio.h>
#include <stdarg.h>

#include "eSCI.h"
#include "StdRegMacros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"
#include "Mcal.h"
#include "Dio.h"
#include "Dio_Cfg.h"

#include "CDD_Mcl.h"
#include "Reg_eSys_Dma.h"

#if ESCI_A_FIFO_EN == 1
ISR(ESCI_A0_ISR);
#endif

#if ESCI_B_FIFO_EN == 1
ISR(ESCI_B1_ISR);
#endif

#if ESCI_C_FIFO_EN == 1
ISR(ESCI_C2_ISR);
#endif

#if ESCI_D_FIFO_EN == 1
ISR(ESCI_D3_ISR);
#endif

#if ESCI_E_FIFO_EN == 1
ISR(ESCI_E4_ISR);
#endif

#if ESCI_F_FIFO_EN == 1
ISR(ESCI_F5_ISR);
#endif



#if ESCI_A_FIFO_EN == 1
	static uint8_t eSCI_A_CommTxBuf[ESCI_A_TX_BUF_SIZE];
	static uint8_t eSCI_A_CommRxBuf[ESCI_A_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_A_CommFifo;
#endif

#if ESCI_B_FIFO_EN == 1
	static uint8_t eSCI_B_CommTxBuf[ESCI_B_TX_BUF_SIZE];
	static uint8_t eSCI_B_CommRxBuf[ESCI_B_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_B_CommFifo;
#endif

#if ESCI_C_FIFO_EN == 1
	static uint8_t eSCI_C_CommTxBuf[ESCI_C_TX_BUF_SIZE];
	static uint8_t eSCI_C_CommRxBuf[ESCI_C_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_C_CommFifo;
#endif

#if ESCI_D_FIFO_EN == 1
	static uint8_t eSCI_D_CommTxBuf[ESCI_D_TX_BUF_SIZE];
	static uint8_t eSCI_D_CommRxBuf[ESCI_D_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_D_CommFifo;
#endif

#if ESCI_E_FIFO_EN == 1
	static uint8_t eSCI_E_CommTxBuf[ESCI_E_TX_BUF_SIZE];
	static uint8_t eSCI_E_CommRxBuf[ESCI_E_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_E_CommFifo;
#endif

#if ESCI_F_FIFO_EN == 1
	static uint8_t eSCI_F_CommTxBuf[ESCI_F_TX_BUF_SIZE];
	static uint8_t eSCI_F_CommRxBuf[ESCI_F_RX_BUF_SIZE];
	static ESCI_FIFO_TypeDef eSCI_F_CommFifo;
#endif


/*
@brief
@details
@para
@return
*/
void Rs485Delay(uint32_t count)
{
    /* Disable interrupts*/
//	SuspendAllInterrupts();

	while (count--);

	/* Enable interrupts */
//	ResumeAllInterrupts();
}

/*
@brief
@details
@para
@return
*/
void ESCIComm_B_Transmit_Enable(void)
{
	Dio_WriteChannel(DioConf_DioChannel_MCU_eSCI_B_EN, STD_HIGH);

//	Rs485Delay(1000);
}

/*
@brief
@details
@para
@return
*/
void ESCIComm_B_Receive_Enable(void)
{
	Dio_WriteChannel(DioConf_DioChannel_MCU_eSCI_B_EN, STD_LOW);
}


/*
@brief
@details
@para
@return
*/
void ESCIComm_C_Transmit_Enable(void)
{
	Dio_WriteChannel(DioConf_DioChannel_MCU_eSCI_C_EN, STD_HIGH);

//	Rs485Delay(1000);
}

/*
@brief
@details
@para
@return
*/
void ESCIComm_C_Receive_Enable(void)
{
	Dio_WriteChannel(DioConf_DioChannel_MCU_eSCI_C_EN, STD_LOW);
}


/*
@brief      
@details    
@para
@return     
*/
void ESCIComm_FIFO_Init(ESCIPort_TypeDef eSCInum)
{
    switch(eSCInum)
    {
        case ESCI_A :
#if ESCI_A_FIFO_EN == 1
	eSCI_A_CommFifo.eSCIPort 	= ESCI_A;
	eSCI_A_CommFifo.pTxBuf 		= eSCI_A_CommTxBuf;
	eSCI_A_CommFifo.pRxBuf 		= eSCI_A_CommRxBuf;
	eSCI_A_CommFifo.usTxBufSize = ESCI_A_TX_BUF_SIZE;
	eSCI_A_CommFifo.usRxBufSize = ESCI_A_RX_BUF_SIZE;
	eSCI_A_CommFifo.usTxWrite  	= 0;
	eSCI_A_CommFifo.usTxRead   	= 0;
	eSCI_A_CommFifo.usTxCount  	= 0;
	eSCI_A_CommFifo.usRxWrite  	= 0;
	eSCI_A_CommFifo.usRxRead   	= 0;
	eSCI_A_CommFifo.usRxCount  	= 0;

	eSCI_A_CommFifo.usRxORCount = 0;

	eSCI_A_CommFifo.TxReady = 1;

    eSCI_A_CommFifo.DMATransive = 1;
	eSCI_A_CommFifo.TxTimeoutCnt = 0;
	eSCI_A_CommFifo.RxTimeoutCnt = 0;
	eSCI_A_CommFifo.TxTimeoutThreshold = 150;
	eSCI_A_CommFifo.RxTimeoutThreshold = 300;
	eSCI_A_CommFifo.SendBefore 	= NULL;
	eSCI_A_CommFifo.SendOver   	= NULL;
	eSCI_A_CommFifo.ReceiveNewDataNotification = NULL;
#endif
    break;
    case ESCI_B :
#if ESCI_B_FIFO_EN == 1
	eSCI_B_CommFifo.eSCIPort 	= ESCI_B;
	eSCI_B_CommFifo.pTxBuf 		= eSCI_B_CommTxBuf;
	eSCI_B_CommFifo.pRxBuf 		= eSCI_B_CommRxBuf;
	eSCI_B_CommFifo.usTxBufSize = ESCI_B_TX_BUF_SIZE;
	eSCI_B_CommFifo.usRxBufSize = ESCI_B_RX_BUF_SIZE;
	eSCI_B_CommFifo.usTxWrite  	= 0;
	eSCI_B_CommFifo.usTxRead   	= 0;
	eSCI_B_CommFifo.usTxCount  	= 0;
	eSCI_B_CommFifo.usRxWrite  	= 0;
	eSCI_B_CommFifo.usRxRead   	= 0;
	eSCI_B_CommFifo.usRxCount  	= 0;

	eSCI_B_CommFifo.usRxORCount = 0;

	eSCI_B_CommFifo.TxReady = 1;

    eSCI_B_CommFifo.DMATransive = 1;
	eSCI_B_CommFifo.TxTimeoutCnt = 0;
	eSCI_B_CommFifo.RxTimeoutCnt = 0;
	eSCI_B_CommFifo.TxTimeoutThreshold = 1000;
	eSCI_B_CommFifo.RxTimeoutThreshold = 2000;
	eSCI_B_CommFifo.SendBefore 	= ESCIComm_B_Transmit_Enable;
	eSCI_B_CommFifo.SendOver   	= ESCIComm_B_Receive_Enable;
	eSCI_B_CommFifo.ReceiveNewDataNotification = NULL;
#endif
        break;
    case ESCI_C :
#if ESCI_C_FIFO_EN == 1
	eSCI_C_CommFifo.eSCIPort 	= ESCI_C;
	eSCI_C_CommFifo.pTxBuf 		= eSCI_C_CommTxBuf;
	eSCI_C_CommFifo.pRxBuf 		= eSCI_C_CommRxBuf;
	eSCI_C_CommFifo.usTxBufSize = ESCI_C_TX_BUF_SIZE;
	eSCI_C_CommFifo.usRxBufSize = ESCI_C_RX_BUF_SIZE;
	eSCI_C_CommFifo.usTxWrite  	= 0;
	eSCI_C_CommFifo.usTxRead   	= 0;
	eSCI_C_CommFifo.usTxCount  	= 0;
	eSCI_C_CommFifo.usRxWrite  	= 0;
	eSCI_C_CommFifo.usRxRead   	= 0;
	eSCI_C_CommFifo.usRxCount  	= 0;

	eSCI_C_CommFifo.usRxORCount = 0;

	eSCI_C_CommFifo.TxReady = 1;

    eSCI_C_CommFifo.DMATransive = 0;
	eSCI_C_CommFifo.TxTimeoutCnt = 0;
	eSCI_C_CommFifo.RxTimeoutCnt = 0;
	eSCI_C_CommFifo.TxTimeoutThreshold = 1000;
	eSCI_C_CommFifo.RxTimeoutThreshold = 2000;
	eSCI_C_CommFifo.SendBefore 	= ESCIComm_C_Transmit_Enable;
	eSCI_C_CommFifo.SendOver   	= ESCIComm_C_Receive_Enable;
	eSCI_C_CommFifo.ReceiveNewDataNotification = NULL;
#endif
        break;
    case ESCI_D :
#if ESCI_D_FIFO_EN == 1
	eSCI_D_CommFifo.eSCIPort 	= ESCI_D;
	eSCI_D_CommFifo.pTxBuf 		= eSCI_D_CommTxBuf;
	eSCI_D_CommFifo.pRxBuf 		= eSCI_D_CommRxBuf;
	eSCI_D_CommFifo.usTxBufSize = ESCI_D_TX_BUF_SIZE;
	eSCI_D_CommFifo.usRxBufSize = ESCI_D_RX_BUF_SIZE;
	eSCI_D_CommFifo.usTxWrite  	= 0;
	eSCI_D_CommFifo.usTxRead   	= 0;
	eSCI_D_CommFifo.usTxCount  	= 0;
	eSCI_D_CommFifo.usRxWrite  	= 0;
	eSCI_D_CommFifo.usRxRead   	= 0;
	eSCI_D_CommFifo.usRxCount  	= 0;

	eSCI_D_CommFifo.usRxORCount = 0;

	eSCI_D_CommFifo.TxReady = 0;

    eSCI_D_CommFifo.DMATransive = 0;
	eSCI_D_CommFifo.TxTimeoutCnt = 0;
	eSCI_D_CommFifo.RxTimeoutCnt = 0;
	eSCI_D_CommFifo.TxTimeoutThreshold = 1000;
	eSCI_D_CommFifo.RxTimeoutThreshold = 2000;
	eSCI_D_CommFifo.SendBefore 	= NULL;
	eSCI_D_CommFifo.SendOver   	= NULL;
	eSCI_D_CommFifo.ReceiveNewDataNotification = NULL;
#endif
        break;
    case ESCI_E :
#if ESCI_E_FIFO_EN == 1
	eSCI_E_CommFifo.eSCIPort 	= ESCI_E;
	eSCI_E_CommFifo.pTxBuf 		= eSCI_E_CommTxBuf;
	eSCI_E_CommFifo.pRxBuf 		= eSCI_E_CommRxBuf;
	eSCI_E_CommFifo.usTxBufSize = ESCI_E_TX_BUF_SIZE;
	eSCI_E_CommFifo.usRxBufSize = ESCI_E_RX_BUF_SIZE;
	eSCI_E_CommFifo.usTxWrite  	= 0;
	eSCI_E_CommFifo.usTxRead   	= 0;
	eSCI_E_CommFifo.usTxCount  	= 0;
	eSCI_E_CommFifo.usRxWrite  	= 0;
	eSCI_E_CommFifo.usRxRead   	= 0;
	eSCI_E_CommFifo.usRxCount  	= 0;

	eSCI_E_CommFifo.usRxORCount = 0;

	eSCI_E_CommFifo.TxReady = 0;

    eSCI_E_CommFifo.DMATransive = 0;
	eSCI_E_CommFifo.TxTimeoutCnt = 0;
	eSCI_E_CommFifo.RxTimeoutCnt = 0;
	eSCI_E_CommFifo.TxTimeoutThreshold = 1000;
	eSCI_E_CommFifo.RxTimeoutThreshold = 2000;
	eSCI_E_CommFifo.SendBefore 	= NULL;
	eSCI_E_CommFifo.SendOver   	= NULL;
	eSCI_E_CommFifo.ReceiveNewDataNotification = NULL;
#endif
        break;
    case ESCI_F :
#if ESCI_F_FIFO_EN == 1
	eSCI_F_CommFifo.eSCIPort 	= ESCI_F;
	eSCI_F_CommFifo.pTxBuf 		= eSCI_F_CommTxBuf;
	eSCI_F_CommFifo.pRxBuf 		= eSCI_F_CommRxBuf;
	eSCI_F_CommFifo.usTxBufSize = ESCI_F_TX_BUF_SIZE;
	eSCI_F_CommFifo.usRxBufSize = ESCI_F_RX_BUF_SIZE;
	eSCI_F_CommFifo.usTxWrite  	= 0;
	eSCI_F_CommFifo.usTxRead   	= 0;
	eSCI_F_CommFifo.usTxCount  	= 0;
	eSCI_F_CommFifo.usRxWrite  	= 0;
	eSCI_F_CommFifo.usRxRead   	= 0;
	eSCI_F_CommFifo.usRxCount  	= 0;

	eSCI_F_CommFifo.usRxORCount = 0;

	eSCI_F_CommFifo.TxReady = 1;

    eSCI_F_CommFifo.DMATransive = 0;
	eSCI_F_CommFifo.TxTimeoutCnt = 0;
	eSCI_F_CommFifo.RxTimeoutCnt = 0;
	eSCI_F_CommFifo.TxTimeoutThreshold = 1000;
	eSCI_F_CommFifo.RxTimeoutThreshold = 2000;
	eSCI_F_CommFifo.SendBefore 	= NULL;
	eSCI_F_CommFifo.SendOver   	= NULL;
	eSCI_F_CommFifo.ReceiveNewDataNotification = NULL;
#endif
        break;
    default :
        break;
    }
}


/*
@brief      
@details    
@para
@return     
*/
void ESCIComm_ClearTxFIFO(ESCI_FIFO_TypeDef* pESCIfifo) 
{
	pESCIfifo->usTxWrite = 0;
	pESCIfifo->usTxRead  = 0;
	pESCIfifo->usTxCount = 0;
    pESCIfifo->TxTimeoutCnt = 0;
    pESCIfifo->TxReady   = 1;
}


/*
@brief      
@details    
@para
@return     
*/
void ESCIComm_ClearRxFIFO(ESCI_FIFO_TypeDef* pESCIfifo) 
{
    /*
	pESCIfifo->usRxWrite = 0;
	pESCIfifo->usRxRead  = 0;
	pESCIfifo->usRxCount = 0;
	*/
    pESCIfifo->RxTimeoutCnt = 0;
}


/*
@brief      
@details    
@para
@return     
*/



static ESCI_ReturnType ESCI_SendData(ESCI_FIFO_TypeDef* pFifo, uint8_t* pTxBuf, uint16_t txLength) 
{
	uint16_t i;
	volatile uint16_t usCount = pFifo->usTxCount;
	ESCI_ReturnType retVal = ESCI_OK;

	SuspendAllInterrupts();
	for (i = 0; i < txLength; i++) 
	{
		if(usCount >= pFifo->usTxBufSize)
		{
			retVal = ESCI_TIMEOUT_ERROR;
			return (retVal);
		}

		pFifo->pTxBuf[pFifo->usTxWrite] = pTxBuf[i];

		if (++pFifo->usTxWrite >= pFifo->usTxBufSize) 
		{
			pFifo->usTxWrite = 0;
		}

		pFifo->usTxCount++;
		
	}
	

	if(1 == pFifo->TxReady)
	{
		ResumeAllInterrupts();
		if (pFifo->SendBefore)
		{
			pFifo->SendBefore();
		}
        ESCI_ClearITFlag(pFifo->eSCIPort, ESCI_TIE_IT);
		ESCI_ITConfig(pFifo->eSCIPort, ESCI_TIE_IT, 1);
		ESCI_WriteData(pFifo->eSCIPort, pFifo->pTxBuf[pFifo->usTxRead]);
		pFifo->usTxRead++;
		pFifo->usTxCount--;
		
		pFifo->TxReady = 0;
	}
	else
	{
		ResumeAllInterrupts();
	}
	return (retVal);
}

static ESCI_ReturnType ESCI_SendData_DMA(ESCI_FIFO_TypeDef* pFifo, uint8_t* pTxBuf, uint16_t txLength)
{
	uint16_t i;
	ESCI_ReturnType retVal = ESCI_OK;

	if(pFifo->usTxWrite + txLength >= pFifo->usTxBufSize || pFifo->usTxCount + txLength >= pFifo->usTxBufSize)
	{
		retVal = ESCI_TIMEOUT_ERROR;
		return (retVal);
	}
    SuspendAllInterrupts();
	for (i = 0; i < txLength; i++)
	{
		pFifo->pTxBuf[pFifo->usTxWrite] = pTxBuf[i];
		pFifo->usTxWrite++;
		pFifo->usTxCount++;
	}
	
	if(1 == pFifo->TxReady)
	{
		ResumeAllInterrupts();
		if (pFifo->SendBefore)
		{
			pFifo->SendBefore();
		}
		ESCI_WriteData_DMA(pFifo->eSCIPort, &pFifo->pTxBuf[pFifo->usTxRead], pFifo->usTxCount);
		pFifo->usTxRead += pFifo->usTxCount;
		pFifo->usTxCount = 0;

		pFifo->TxReady = 0;
	}
	else
	{
		ResumeAllInterrupts();
	}
	return retVal;
}

/*
@brief      
@details    
@para
@return     
*/
static ESCI_FIFO_TypeDef* Get_ESCICommFifo(ESCIPort_TypeDef eSCINum) 
{
	ESCI_FIFO_TypeDef *pFifo = NULL;
	
	switch (eSCINum) 
	{
	#if ESCI_A_FIFO_EN == 1
		case ESCI_A: pFifo = &eSCI_A_CommFifo; break;
	#endif
		
	#if ESCI_B_FIFO_EN == 1
		case ESCI_B: pFifo = &eSCI_B_CommFifo; break;
	#endif
	
	#if ESCI_C_FIFO_EN == 1
		case ESCI_C: pFifo = &eSCI_C_CommFifo; break;
	#endif

	#if ESCI_D_FIFO_EN == 1
		case ESCI_D: pFifo = &eSCI_D_CommFifo; break;
	#endif

	#if ESCI_E_FIFO_EN == 1
		case ESCI_E: pFifo = &eSCI_E_CommFifo; break;
	#endif

	#if ESCI_F_FIFO_EN == 1
		case ESCI_F: pFifo = &eSCI_F_CommFifo; break;
	#endif
	
		default:break;
	}

	return (pFifo);
}


/*
@brief      
@details    
@para
@return     
*/
StatusType ESCIComm_SendDataBuff(ESCIPort_TypeDef eSCINum, uint8_t* pTxBuff, uint16_t len) 
{
	ESCI_FIFO_TypeDef *pESCIFifo;

	pESCIFifo = Get_ESCICommFifo(eSCINum);

	if (pESCIFifo->SendBefore)
	{
		pESCIFifo->SendBefore();
	}

	if(ESCI_A == pESCIFifo->eSCIPort || ESCI_B == pESCIFifo->eSCIPort)
	{
		if(ESCI_OK == ESCI_SendData_DMA(pESCIFifo, pTxBuff, len))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if (ESCI_SendData(pESCIFifo, pTxBuff, len) == ESCI_OK)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
}


/*
@brief      
@details    
@para
@return     
*/
StatusType ESCIComm_ReceiveDataBuff(ESCIPort_TypeDef eSCINum, uint8_t* pRxData, uint16_t* pLen) 
{
	ESCI_FIFO_TypeDef *pESCIFifo;
	uint16_t i, usCount;

	pESCIFifo = Get_ESCICommFifo(eSCINum);

	/* Disable interrupts */
	SuspendAllInterrupts();

	usCount = pESCIFifo->usRxCount;

	/* Enable interrupts */
	ResumeAllInterrupts();

	if (usCount == 0) 
	{
        *pLen = 0;
		return (0);
	}
	else 
	{
		for (i = 0; i < usCount; i++) 
		{
			pRxData[i] = pESCIFifo->pRxBuf[pESCIFifo->usRxRead];
			pESCIFifo->pRxBuf[pESCIFifo->usRxRead] = 0;

			/* Disable interrupts */
			SuspendAllInterrupts();

			if (++pESCIFifo->usRxRead >= pESCIFifo->usRxBufSize) 
			{
				pESCIFifo->usRxRead = 0;
			}

			pESCIFifo->usRxCount--;

			/* Enable interrupts */
			ResumeAllInterrupts();
		}
		*pLen = usCount;

		return (1);
	}
}


/*
@brief      
@details    
@para
@return     
*/
void ESCIComm_Init(void)
{
	ESCI_InitTypeDef eSCI_Init;

	eSCI_Init.Baudrate 		 = 115200;
	eSCI_Init.RXDMAEn_Status = 1;
	eSCI_Init.TXDMAEn_Status = 1;
	eSCI_Init.TIE_Status     = 0;
	eSCI_Init.TCIE_Status    = 1;
	eSCI_Init.RIE_Status     = 0;
	eSCI_Init.ILIE_Status    = 1;
	eSCI_Init.ORIE_Status    = 0;
	eSCI_Init.FrameFormats   = Data8Bits_NoneParity_1StopBit;
	ESCI_Init(ESCI_A, &eSCI_Init);


	eSCI_Init.Baudrate 		 = 2400;
	eSCI_Init.RXDMAEn_Status = 1;
	eSCI_Init.TXDMAEn_Status = 1;
	eSCI_Init.TIE_Status     = 0;
	eSCI_Init.TCIE_Status    = 1;
	eSCI_Init.RIE_Status     = 0;
	eSCI_Init.ILIE_Status    = 1;
	eSCI_Init.ORIE_Status    = 0;
	eSCI_Init.FrameFormats   = Data8Bits_EvenParity_1StopBit;
	ESCI_Init(ESCI_B, &eSCI_Init);


	eSCI_Init.Baudrate 		 = 2400;
	eSCI_Init.RXDMAEn_Status = 0;
	eSCI_Init.TXDMAEn_Status = 0;
	eSCI_Init.TIE_Status     = 1;
	eSCI_Init.TCIE_Status    = 1;
	eSCI_Init.RIE_Status     = 1;
	eSCI_Init.ILIE_Status    = 0;
	eSCI_Init.ORIE_Status    = 1;
	eSCI_Init.FrameFormats   = Data8Bits_EvenParity_1StopBit;
	ESCI_Init(ESCI_C, &eSCI_Init);


	eSCI_Init.Baudrate 		 = 115200;
	eSCI_Init.RXDMAEn_Status = 0;
	eSCI_Init.TXDMAEn_Status = 0;
	eSCI_Init.TIE_Status     = 1;
	eSCI_Init.TCIE_Status    = 1;
	eSCI_Init.RIE_Status     = 1;
	eSCI_Init.ILIE_Status    = 0;
	eSCI_Init.ORIE_Status    = 1;
	eSCI_Init.FrameFormats   = Data8Bits_NoneParity_1StopBit;
	ESCI_Init(ESCI_F, &eSCI_Init);

	ESCIComm_FIFO_Init(ESCI_A);
    ESCIComm_FIFO_Init(ESCI_B);
    ESCIComm_FIFO_Init(ESCI_C);
    ESCIComm_FIFO_Init(ESCI_F);

	ESCI_ReceiveInit_DMA(ESCI_A, eSCI_A_CommFifo.pRxBuf, eSCI_A_CommFifo.usRxBufSize);
	ESCI_ReceiveInit_DMA(ESCI_B, eSCI_B_CommFifo.pRxBuf, eSCI_B_CommFifo.usRxBufSize);
}


/*
@brief
@details
@para
@return
*/
ESCI_ReturnType ESCI_Init(ESCIPort_TypeDef eSCInum, const ESCI_InitTypeDef* pESCInit) 
{
	uint32_t SBR_REG;
	uint16_t regVal;
	volatile float baudratefactor;
#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (ESCI_PARAMETER_ERROR);
	if (pESCInit == NULL)return (ESCI_PARAMETER_ERROR);
#endif

	/* Set SCI mode */
	REG_WRITE16(ESCI_LCR1_ADDR32((uint8_t)eSCInum), 0x0UL);

	/* ERR flag not affected by overrun,frame error,parity error detection. */
	REG_WRITE16(ESCI_CR3_ADDR32((uint8_t)eSCInum), 0x0UL);

	/* Calculate communication baudrate and write the register. */
	baudratefactor =( (float)ESCI_CLK / 16UL / (pESCInit->Baudrate)) + 0.5;
	SBR_REG = (uint32_t)baudratefactor;
	REG_WRITE16(ESCI_BRR_ADDR32((uint8_t)eSCInum), SBR_REG);

	/* Read CR2 register and configure eSCI module with DMA control. */
	regVal = REG_READ16(ESCI_CR2_ADDR32((uint8_t)eSCInum));
	if (pESCInit->RXDMAEn_Status) 
	{
		regVal |= ESCI_CR2_RXDMA_MASK_U16;
	}
	else 
	{
		regVal &= ~ESCI_CR2_RXDMA_MASK_U16;
	}

	if (pESCInit->TXDMAEn_Status) 
	{
		regVal |= ESCI_CR2_TXDMA_MASK_U16;
	}
	else 
	{
		regVal &= ~ESCI_CR2_TXDMA_MASK_U16;
	}

	if(pESCInit->ORIE_Status)
	{
		ESCI_ClearITFlag(eSCInum, ESCI_ORIE_IT);
		regVal |= ESCI_CR2_ORIE_MASK_U16;
	}
	else
	{
		regVal &= ~ESCI_CR2_ORIE_MASK_U16;
	}

	REG_WRITE16(ESCI_CR2_ADDR32((uint8_t)eSCInum), regVal);

	/* Clear transmit complete interrupt flag and receive data register full interrupt flag. */
	regVal = 0;
	regVal |= (ESCI_IFSR1_TC_MASK_U16 | ESCI_IFSR1_RDRF_MASK_U16);
	REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), regVal);

	/* Read CR1 register and configure eSCI module with interrupt enable control status value. */
	regVal = REG_READ16(ESCI_CR1_ADDR32((uint8_t)eSCInum));

	if (pESCInit->FrameFormats == Data8Bits_NoneParity_1StopBit)
	{
		regVal &= ~ESCI_CR1_M_MASK_U16;
		regVal &= ~ESCI_CR1_WAKE_MASK_U16;
		regVal &= ~ESCI_CR1_PE_MASK_U16;
		regVal &= ~ESCI_CR1_PT_MASK_U16;
	}
	else if (pESCInit->FrameFormats == Data8Bits_EvenParity_1StopBit)
	{
		regVal |=  ESCI_CR1_M_MASK_U16;
		regVal &= ~ESCI_CR1_WAKE_MASK_U16;
		regVal |=  ESCI_CR1_PE_MASK_U16;
		regVal &= ~ESCI_CR1_PT_MASK_U16;
	}
	else if (pESCInit->FrameFormats == Data8Bits_OddParity_1StopBit)
	{
		regVal |=  ESCI_CR1_M_MASK_U16;
		regVal &= ~ESCI_CR1_WAKE_MASK_U16;
		regVal |=  ESCI_CR1_PE_MASK_U16;
		regVal |=  ESCI_CR1_PT_MASK_U16;
	}
	else
	{
		return (ESCI_PARAMETER_ERROR);
	}

	regVal &= ~(ESCI_CR1_LOOPS_MASK_U16 | ESCI_CR1_RSRC_MASK_U16);
	regVal &= ~ESCI_CR1_TIE_MASK_U16;


	if (pESCInit->TIE_Status)
	{
		ESCI_ClearITFlag(eSCInum, ESCI_TIE_IT);
		regVal |= ESCI_CR1_TIE_MASK_U16;
	}
	else
	{
		regVal &= ~ESCI_CR1_TIE_MASK_U16;
	}


	if (pESCInit->TCIE_Status) 
	{
		ESCI_ClearITFlag(eSCInum, ESCI_TCIE_IT);
		regVal |= ESCI_CR1_TCIE_MASK_U16;
	}
	else 
	{
		regVal &= ~ESCI_CR1_TCIE_MASK_U16;
	}


	if (pESCInit->RIE_Status) 
	{
		ESCI_ClearITFlag(eSCInum, ESCI_RIE_IT);
		regVal |= ESCI_CR1_RIE_MASK_U16;
	}
	else 
	{
		regVal &= ~ESCI_CR1_RIE_MASK_U16;
	}


	if(pESCInit->ILIE_Status)
	{
		ESCI_ClearITFlag(eSCInum, ESCI_ILIE_IT);
		regVal |= ESCI_CR1_ILIE_MASK_U16;
	}
	else
	{
		regVal &= ~ESCI_CR1_ILIE_MASK_U16;
	}

	regVal |= (ESCI_CR1_TE_MASK_U16 | ESCI_CR1_RE_MASK_U16);
	
	REG_WRITE16(ESCI_CR1_ADDR32((uint8_t)eSCInum), regVal);
	
	return (ESCI_OK);
}


/*
@brief      
@details    
@para
@return     
*/
ESCI_ReturnType ESCI_ITConfig(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType, StatusType newState) 
{
	uint16_t regVal;

#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (ESCI_PARAMETER_ERROR);
	if ((ItType > ESCI_ORIE_IT) || (ItType < ESCI_TIE_IT))return (ESCI_PARAMETER_ERROR);
#endif

	switch (ItType) 
	{
		case ESCI_TIE_IT: {
			regVal = REG_READ16(ESCI_CR1_ADDR32((uint8_t)eSCInum));
			(newState != 0)?(regVal |= ESCI_CR1_TIE_MASK_U16):(regVal &= ~ESCI_CR1_TIE_MASK_U16);
			REG_WRITE16(ESCI_CR1_ADDR32((uint8_t)eSCInum), regVal);
		}break;

		case ESCI_TCIE_IT: {
			regVal = REG_READ16(ESCI_CR1_ADDR32((uint8_t)eSCInum));
			(newState != 0)?(regVal |= ESCI_CR1_TCIE_MASK_U16):(regVal &= ~ESCI_CR1_TCIE_MASK_U16);
			REG_WRITE16(ESCI_CR1_ADDR32((uint8_t)eSCInum), regVal);
		}break;

		case ESCI_RIE_IT: {
			regVal = REG_READ16(ESCI_CR1_ADDR32((uint8_t)eSCInum));
			(newState != 0)?(regVal |= ESCI_CR1_RIE_MASK_U16):(regVal &= ~ESCI_CR1_RIE_MASK_U16);
			REG_WRITE16(ESCI_CR1_ADDR32((uint8_t)eSCInum), regVal);
		}break;
		case ESCI_ORIE_IT: {
			regVal = REG_READ16(ESCI_CR2_ADDR32((uint8_t)eSCInum));
			(newState != 0)?(regVal |= ESCI_CR2_ORIE_MASK_U16):(regVal &= ~ESCI_CR2_ORIE_MASK_U16);
			REG_WRITE16(ESCI_CR2_ADDR32((uint8_t)eSCInum), regVal);
		}break;

		default:break;
	}



	return (ESCI_OK);
}


/*
@brief      
@details    
@para
@return     
*/
StatusType ESCI_GetITFlag(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType) 
{
	StatusType retVal = 0;
	volatile uint16_t regVal;

#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (retVal);
	if ((ItType > ESCI_ORIE_IT) || (ItType < ESCI_TIE_IT))return (retVal);
#endif

	regVal = REG_READ16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum));
	
	switch (ItType) 
	{
		case ESCI_TIE_IT: {
			(regVal & ESCI_IFSR1_TDRE_MASK_U16)?(retVal = 1):(retVal = 0);
		}break;

		case ESCI_TCIE_IT: {
			(regVal & ESCI_IFSR1_TC_MASK_U16)?(retVal = 1):(retVal = 0);
		}break;

		case ESCI_RIE_IT: {
			(regVal & ESCI_IFSR1_RDRF_MASK_U16)?(retVal = 1):(retVal = 0);
		}break;
		case ESCI_ILIE_IT: {
			(regVal & ESCI_IFSR1_IDLE_MASK_U16)?(retVal = 1):(retVal = 0);
		}break;
		case ESCI_ORIE_IT:{
			(regVal & ESCI_IFSR1_OR_MASK_U16)?(retVal = 1):(retVal = 0);
		}break;

		default:break;
	}

	return (retVal);
}


/*
@brief      
@details    
@para
@return     
*/
ESCI_ReturnType ESCI_ClearITFlag(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType) 
{
#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (ESCI_PARAMETER_ERROR);
	if ((ItType > ESCI_ORIE_IT) || (ItType < ESCI_TIE_IT))return (ESCI_PARAMETER_ERROR);
#endif

	switch (ItType)
	{
		case ESCI_TIE_IT: {
			REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), ESCI_IFSR1_TDRE_MASK_U16);
		}break;

		case ESCI_TCIE_IT: {
			REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), ESCI_IFSR1_TC_MASK_U16);
		}break;

		case ESCI_RIE_IT: {
			REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), ESCI_IFSR1_RDRF_MASK_U16);
		}break;

		case ESCI_ILIE_IT: {
			REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), ESCI_IFSR1_IDLE_MASK_U16);
		}break;

		case ESCI_ORIE_IT: {
			REG_WRITE16(ESCI_IFSR1_ADDR32((uint8_t)eSCInum), ESCI_IFSR1_OR_MASK_U16);
		}break;

		default:break;
	}

	return (ESCI_OK);
}

/*
@brief      
@details    
@para
@return     
*/
ESCI_ReturnType ESCI_WriteData(ESCIPort_TypeDef eSCInum, uint16_t txData) 
{
	ESCI_FIFO_TypeDef * pFifo;
#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (ESCI_PARAMETER_ERROR);
#endif
	pFifo = Get_ESCICommFifo(eSCInum);
	if (pFifo->SendBefore)
	{
		pFifo->SendBefore();
	}
	REG_WRITE16(ESCI_SDR_ADDR32((uint8_t)eSCInum), txData);

	return (ESCI_OK);
}

void ESCI_WriteData_DMA(ESCIPort_TypeDef eSCINum, uint8_t * buf, uint16_t length)
{
	uint8_t DMA_Channel;
	uint32_t regData;
	if(ESCI_A == eSCINum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_18;
	}
	else if(ESCI_B == eSCINum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_34;
	}
	else
	{
		return;
	}

	//Disable Request Register Low
	REG_WRITE8(DMA_CERQ_ADDR32(0), DMA_Channel);

	//Control Register
	REG_WRITE32(DMA_CR_ADDR32(0), 0x0000E400);		//CR[EMLM] = 0	/	Disabled Minor Loop Mapping  /  TCDn.word2 is defined as a 32-bit NBYTES field.

	//DAM.TCDn.SADDR
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_1ST_WORD_OFFSET_U32, (uint32)buf);

	//DMA.TCDn.ATTR
	//DAM.TCDn.SOFF
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_2ND_WORD_OFFSET_U32, 0x00000001);

	//(DMA_TCDn.NBYTES.MLNO、	DMA_TCDn.NBYTES. MLOFFNO、	DMA_TCDn.NBYTES. MLOFFYES)
	//DMA_TCDn.NBYTES.MLNO	/	Minor Byte Transfer Count
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_3RD_WORD_OFFSET_U32, 0x00000001);

	//(DMA.TCDn.CITER.ELINKNO、	DMA.TCDn.CITER_ELINKYES)	DMA.TCDn.CITER.ELINKNO	/	TCDn_CITER[ELINK] is cleared
	//DAM_TCDn_DOFF
	regData = length<<16;
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_6TH_WORD_OFFSET_U32, regData);		//0x5A - 90

	//(DMA.TCDn。SLAST)
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_4TH_WORD_OFFSET_U32, 0);

	//DAM.TCDn.DADDR
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_5TH_WORD_OFFSET_U32, (uint32)(ESCI_SDR_ADDR32(eSCINum) + 1));

	//(DMA_TCDn.BITER.ELINKNO、	DMA_TCDn.BITER.ELINKYES)	DMA_TCDn.BITER.ELINKNO	/	TCDn_BITER[ELINK] bit is cleared
	//DMA_TCDn.CSR
	////DREQ		The channel¨s ERQ {H,L} bit is cleared when the major loop is complete.
	///INTMAJOR		The end-of-major loop interrupt is enabled.
	regData = 0x8 | (length << 16);
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_8TH_WORD_OFFSET_U32, regData);

	//Enable Request Register Low
	REG_WRITE8(DMA_SERQ_ADDR32(0), DMA_Channel);
}

/*
@brief      
@details    
@para
@return     
*/
uint16_t ESCI_ReadData(ESCIPort_TypeDef eSCInum) 
{
	uint16_t retData = 0;

#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_F) || (eSCInum < ESCI_A))return (retData);
#endif

	retData = REG_READ16(ESCI_SDR_ADDR32((uint8_t)eSCInum));

	return (retData);
}

void  ESCI_ReadData_DMA(ESCIPort_TypeDef eSCInum, uint8_t *buf, uint16_t * length)
{
	ESCI_FIFO_TypeDef* pESCIFifo;
	volatile uint32_t Offset1, Offset2;
	uint8_t DMA_Channel = 0;

#if PARAMETERS_MONITOR_EN == 1
	if ((eSCInum > ESCI_B) || (eSCInum < ESCI_A))
	{
		*length = 0;
		return;
	}
#endif
	if(ESCI_A == eSCInum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_19;
	}
	else if(ESCI_B == eSCInum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_35;
	}
	pESCIFifo = Get_ESCICommFifo(eSCInum);

	Offset1 = REG_READ32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_5TH_WORD_OFFSET_U32) - (uint32)pESCIFifo->pRxBuf;
	Offset2 = (uint32_t)buf - (uint32_t)pESCIFifo->pRxBuf;
	if(Offset1 < Offset2)
	{
		*length = pESCIFifo->usRxBufSize - Offset2 + Offset1;
	}
	else
	{
		*length = Offset1 - Offset2;
	}
}

/*
@brief      
@details    
@para
@return     
*/
static void ESCI_IRQ(ESCI_FIFO_TypeDef* pESCIFifo)
{
	if (ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_RIE_IT) != 0 || 0 != ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_ORIE_IT))
	{
		uint16_t rxdata;

		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_RIE_IT);
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_ORIE_IT);

		rxdata = ESCI_ReadData(pESCIFifo->eSCIPort);

		pESCIFifo->pRxBuf[pESCIFifo->usRxWrite] = (uint8_t)rxdata;

		if (++pESCIFifo->usRxWrite >= pESCIFifo->usRxBufSize)
		{
			pESCIFifo->usRxWrite = 0;
		}

		if (pESCIFifo->usRxCount < pESCIFifo->usRxBufSize)
		{
			pESCIFifo->usRxCount++;
		}
        pESCIFifo->RxTimeoutCnt = 0;
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_RIE_IT);
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_ORIE_IT);
	}

	if (0 != ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_TIE_IT) || 0 != ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT))
	{
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_TIE_IT);
		if(0 != pESCIFifo->usTxCount)
		{
			ESCI_WriteData(pESCIFifo->eSCIPort, pESCIFifo->pTxBuf[pESCIFifo->usTxRead]);

			if (++pESCIFifo->usTxRead >= pESCIFifo->usTxBufSize)
			{
				pESCIFifo->usTxRead = 0;
			}

			if(0 == --pESCIFifo->usTxCount)
			{
					ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT);
					ESCI_ITConfig(pESCIFifo->eSCIPort, ESCI_TCIE_IT, 1);
                ESCI_ITConfig(pESCIFifo->eSCIPort, ESCI_TIE_IT, 0);
			}
		}
		else
		{
			if(0 != ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT))
			{
				ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT);
				ESCI_ITConfig(pESCIFifo->eSCIPort, ESCI_TCIE_IT, 0);

				if (pESCIFifo->SendOver)
				{
					pESCIFifo->SendOver();
				}

				ESCIComm_ClearTxFIFO(pESCIFifo);
			}
		}
	}

	/* When exit the ISR,the following function must be called by user. */
	EXIT_INTERRUPT();
}

static void ESCI_IRQ_DMA(ESCI_FIFO_TypeDef* pESCIFifo)
{

	if (ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_ILIE_IT) != 0)
	{
		uint16_t length;
		ESCI_ReadData_DMA(pESCIFifo->eSCIPort, &pESCIFifo->pRxBuf[pESCIFifo->usRxWrite], &length);
		pESCIFifo->usRxWrite += length;
		if(pESCIFifo->usRxBufSize <= pESCIFifo->usRxWrite)
		{
			pESCIFifo->usRxWrite -= pESCIFifo->usRxBufSize;
		}
		pESCIFifo->usRxCount += length;

        pESCIFifo->RxTimeoutCnt = 0;
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_ILIE_IT);
	}

	if (ESCI_GetITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT) != 0)
	{

			if (pESCIFifo->usTxCount == 0)
			{
				if (pESCIFifo->SendOver)
				{
					pESCIFifo->SendOver();
				}

				ESCIComm_ClearTxFIFO(pESCIFifo);
			}
			else
			{
				ESCI_WriteData_DMA(pESCIFifo->eSCIPort, &pESCIFifo->pTxBuf[pESCIFifo->usTxRead], pESCIFifo->usTxCount);
				pESCIFifo->usTxRead += pESCIFifo->usTxCount;
				pESCIFifo->usTxCount = 0;
            
		}
        pESCIFifo->TxTimeoutCnt = 0;
		ESCI_ClearITFlag(pESCIFifo->eSCIPort, ESCI_TCIE_IT);
	}

	/* When exit the ISR,the following function must be called by user. */
	EXIT_INTERRUPT();
}

#if ESCI_A_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_A0_ISR)
{
	ESCI_IRQ_DMA(&eSCI_A_CommFifo);
}
#endif


#if ESCI_B_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_B1_ISR)
{
	ESCI_IRQ_DMA(&eSCI_B_CommFifo);
}
#endif


#if ESCI_C_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_C2_ISR)
{
	ESCI_IRQ(&eSCI_C_CommFifo);	
}
#endif


#if ESCI_D_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_D3_ISR)
{
	ESCI_IRQ(&eSCI_D_CommFifo);
}
#endif


#if ESCI_E_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_E4_ISR)
{
	ESCI_IRQ(&eSCI_E_CommFifo);
}
#endif


#if ESCI_F_FIFO_EN == 1
/*
@brief      
@details    
@para
@return     
*/
ISR(ESCI_F5_ISR)
{
	ESCI_IRQ(&eSCI_F_CommFifo);	
}
#endif

void ESCI_Task_10ms(void)
{
	ESCIPort_TypeDef eSCINum;
	ESCI_FIFO_TypeDef* pESCIFifo;

    for(eSCINum = ESCI_A; eSCINum <= ESCI_F; eSCINum++)
		{
			pESCIFifo = Get_ESCICommFifo(eSCINum);
        if(NULL != pESCIFifo)
			{
			if(++pESCIFifo->TxTimeoutCnt > pESCIFifo->TxTimeoutThreshold)
			{
                if(0 == pESCIFifo->DMATransive)
                {
                ESCI_ITConfig(eSCINum, ESCI_TIE_IT, 0);
                ESCI_ITConfig(eSCINum, ESCI_TCIE_IT, 0);
                }
                ESCI_ClearITFlag(eSCINum, ESCI_TIE_IT);
				ESCI_ClearITFlag(eSCINum, ESCI_TCIE_IT);
				ESCIComm_ClearTxFIFO(pESCIFifo);
			}
			if(++pESCIFifo->RxTimeoutCnt > pESCIFifo->RxTimeoutThreshold)
			{
				ESCIComm_ClearRxFIFO(pESCIFifo);
				ESCI_ClearITFlag(eSCINum, ESCI_RIE_IT);

				ESCI_ClearITFlag(eSCINum, ESCI_ILIE_IT);
				ESCI_ClearITFlag(eSCINum, ESCI_ORIE_IT);
			}
		}
	}
}


void ESCI_ReceiveInit_DMA(ESCIPort_TypeDef eSCINum, uint8_t * buf, uint16_t length)
{
	uint8_t DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_19;
	uint32_t regData;
	if(ESCI_A == eSCINum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_19;
	}
	else if(ESCI_B == eSCINum)
	{
		DMA_Channel = MCL_DMA_LOGICAL_CHANNEL_35;
	}

	//Disable Request Register Low
	REG_WRITE8(DMA_CERQ_ADDR32(0), DMA_Channel);

	//Control Register
	REG_WRITE32(DMA_CR_ADDR32(0), 0x0000E400);		//CR[EMLM] = 0	/	Disabled Minor Loop Mapping  /  TCDn.word2 is defined as a 32-bit NBYTES field.

	//DAM.TCDn.SADDR
	regData = (uint32)(ESCI_SDR_ADDR32(eSCINum) + 1);
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_1ST_WORD_OFFSET_U32, regData);

	//DMA.TCDn.ATTR
	//DAM.TCDn.SOFF
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_2ND_WORD_OFFSET_U32, 0x00000000);

	//(DMA_TCDn.NBYTES.MLNO、	DMA_TCDn.NBYTES. MLOFFNO、	DMA_TCDn.NBYTES. MLOFFYES)
	//DMA_TCDn.NBYTES.MLNO	/	Minor Byte Transfer Count
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_3RD_WORD_OFFSET_U32, 0x00000001);

	//(DMA.TCDn.CITER.ELINKNO、	DMA.TCDn.CITER_ELINKYES)	DMA.TCDn.CITER.ELINKNO	/	TCDn_CITER[ELINK] is cleared
	//DAM_TCDn_DOFF
	regData = 1 | (length <<16);
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_6TH_WORD_OFFSET_U32, regData);		//0x5A - 90

	//(DMA.TCDn。SLAST)
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_4TH_WORD_OFFSET_U32, 0);

	//DAM.TCDn.DADDR
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_5TH_WORD_OFFSET_U32, (uint32)buf);

	//DMA DLAST_SAG
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_7TH_WORD_OFFSET_U32, -length);
	//(DMA_TCDn.BITER.ELINKNO、	DMA_TCDn.BITER.ELINKYES)	DMA_TCDn.BITER.ELINKNO	/	TCDn_BITER[ELINK] bit is cleared
	//DMA_TCDn.CSR
	////The channel¨s ERQ {H,L} bit is cleared when the major loop is complete.
	///The end-of-major loop interrupt is enabled.
	regData =  length << 16;
	REG_WRITE32((uint32)(Mcl_DmaTcdType *)DMA_TCD((uint32)(DMA_Channel)) + DMA_TCD_8TH_WORD_OFFSET_U32, regData);

	//Enable Request Register Low
	REG_WRITE8(DMA_SERQ_ADDR32(0), DMA_Channel);
}
