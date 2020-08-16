
#ifndef ESCI_H
#define ESCI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>

#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"

/* esci driver version: V1.0.1 */
#define ESCI_DRIVER_VER		(101)


/* ESCI module input clock frequency definition.(This clock source is PER_CLK.) */
#define ESCI_CLK	(40000000.0)

#define ESCI_A_FIFO_EN	(1)
#define ESCI_B_FIFO_EN	(1)
#define ESCI_C_FIFO_EN	(1)
#define ESCI_D_FIFO_EN	(0)
#define ESCI_E_FIFO_EN	(0)
#define ESCI_F_FIFO_EN	(1)


#if ESCI_A_FIFO_EN == 1
	#define ESCI_A_TX_BUF_SIZE	(2*256)
	#define ESCI_A_RX_BUF_SIZE	(2*256)
#endif

#if ESCI_B_FIFO_EN == 1
	#define ESCI_B_TX_BUF_SIZE	(1*256)
	#define ESCI_B_RX_BUF_SIZE	(1*256)
#endif

#if ESCI_C_FIFO_EN == 1
	#define ESCI_C_TX_BUF_SIZE	(1*256)
	#define ESCI_C_RX_BUF_SIZE	(1*256)
#endif

#if ESCI_D_FIFO_EN == 1
	#define ESCI_D_TX_BUF_SIZE	(1*256)
	#define ESCI_D_RX_BUF_SIZE	(1*256)
#endif

#if ESCI_E_FIFO_EN == 1
	#define ESCI_E_TX_BUF_SIZE	(1*256)
	#define	ESCI_E_RX_BUF_SIZE	(1*256)
#endif

#if ESCI_F_FIFO_EN == 1
	#define ESCI_F_TX_BUF_SIZE	(1*256)
	#define ESCI_F_RX_BUF_SIZE	(1*256)
#endif


#define PARAMETERS_MONITOR_EN	(1)


typedef enum
{
	ESCI_OK = 0,
	ESCI_PARAMETER_ERROR,
	ESCI_TIMEOUT_ERROR
}ESCI_ReturnType;

typedef enum
{
	ESCI_A = 0,
	ESCI_B = 1,
	ESCI_C = 2,
	ESCI_D = 3,
	ESCI_E = 4,
	ESCI_F = 5
}ESCIPort_TypeDef;

typedef enum
{
	ESCI_TIE_IT = 0,				/* Transmitter interrupt. 	*/
	ESCI_TCIE_IT = 1,				/* Transmission complete interrupt. */
	ESCI_RIE_IT = 2,					/* Receiver full interrupt. */
	ESCI_ILIE_IT = 3,                /* Idle line interrupt */
	ESCI_ORIE_IT = 4              /* OverRun  interrupt. */
}ESCI_IT_TypeDef;


typedef enum
{
	Data8Bits_NoneParity_1StopBit = 0,
	Data8Bits_EvenParity_1StopBit,
	Data8Bits_OddParity_1StopBit
}ESCI_DataFrameFormatsTypeDef;


typedef struct
{
	uint32_t   Baudrate;						/* ESCI communication baud rate. */
	StatusType TIE_Status;
	StatusType TCIE_Status;						/* Transmit complete interrupt enable control status. */
	StatusType RIE_Status;						/* Receive data register full interrupt enable control status. */
	StatusType ILIE_Status;
	StatusType ORIE_Status;                    /* OverRun interrupt enable control status. */
	StatusType RXDMAEn_Status;					/* Receive DMA enable control status.  */
	StatusType TXDMAEn_Status;					/* Transmit DMA enable control status. */
	ESCI_DataFrameFormatsTypeDef FrameFormats;	/* ESCI transmit frame formats. */
}ESCI_InitTypeDef;


typedef struct
{
	ESCIPort_TypeDef eSCIPort;
	uint8_t *pTxBuf;
	uint8_t *pRxBuf;
	uint16_t usTxBufSize;
	uint16_t usRxBufSize;

	volatile uint16_t usTxWrite;
	volatile uint16_t usTxRead;
	volatile uint16_t usTxCount;
	volatile uint16_t usRxWrite;
	volatile uint16_t usRxRead;
	volatile uint16_t usRxCount;
	volatile uint16_t usRxORCount;
	volatile uint8_t  TxReady;

    volatile uint8_t  DMATransive;
    volatile uint16_t TxTimeoutCnt;
    volatile uint16_t TxTimeoutThreshold;
    volatile uint16_t RxTimeoutCnt;
    volatile uint16_t RxTimeoutThreshold;
	void (*SendBefore)(void);
	void (*SendOver)(void);
	void (*ReceiveNewDataNotification)(void);
}ESCI_FIFO_TypeDef;


void ESCIComm_FIFO_Init(ESCIPort_TypeDef eSCInum);
void ESCIComm_ClearTxFIFO(ESCI_FIFO_TypeDef* pESCIfifo);
void ESCIComm_ClearRxFIFO(ESCI_FIFO_TypeDef* pESCIfifo);
StatusType ESCIComm_SendDataBuff(ESCIPort_TypeDef eSCINum, uint8_t* pTxBuff, uint16_t len);
StatusType ESCIComm_ReceiveDataBuff(ESCIPort_TypeDef eSCINum, uint8_t* pRxData, uint16_t* pLen);

extern void ESCIComm_Init(void);
ESCI_ReturnType ESCI_Init(ESCIPort_TypeDef eSCInum, const ESCI_InitTypeDef* pESCInit);
ESCI_ReturnType ESCI_ITConfig(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType, StatusType newState);
StatusType ESCI_GetITFlag(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType);
ESCI_ReturnType ESCI_ClearITFlag(ESCIPort_TypeDef eSCInum, ESCI_IT_TypeDef ItType);
ESCI_ReturnType ESCI_WriteData(ESCIPort_TypeDef eSCInum, uint16_t txData);
void ESCI_WriteData_DMA(ESCIPort_TypeDef eSCINum, uint8_t * buf, uint16_t length);
uint16_t ESCI_ReadData(ESCIPort_TypeDef eSCInum);
void ESCI_ReadData_DMA(ESCIPort_TypeDef eSCInum, uint8_t *buf, uint16_t * length);
void ESCI_ReceiveInit_DMA(ESCIPort_TypeDef eSCINum, uint8_t * buf, uint16_t length);

void ESCI_Task_10ms(void);

#ifdef __cplusplus
}
#endif

#endif
