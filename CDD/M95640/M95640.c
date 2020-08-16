/*
 * M95640.c
 *
 *  Created on: Jun 29, 2018
 *      Author: CIX2SGH
 */

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "SpiIf.h"
#include "M95640.h"
#include "rba_BswSrv.h"
#include "Integration.h"
#include "Ea_Cfg.h"
#include "common.h"
#include "Std_Types.h"

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

typedef unsigned char boolean;

#define WREN 		0x06  //Write Enable command
#define WRDI 		0x04  //Write Disable command
#define RDSR 		0x05  //Read Status Register command
#define WRSR 		0x01  //Write Status Register command
#define READ 		0x03  //Read from Memory Array command
#define WRITE 		0x02  //Write to Memory Array command

#define PAGE_SIZE 	32U
#define BUFF_SIZE	2048U

#define memset 		rba_BswSrv_MemSet
#define memcmp 		rba_BswSrv_MemCompare

uint8 WriteEepm95640Flag = 0;		//M95640 write data to memory flag info


static void  Eepm95640_WriteEnable(void);
static void  Eepm95640_WriteDisable(void);
static void  Eepm95640_ProtectedSet(uint8 DataToWrite);
static uint8 Eepm95640_WriteStatus(uint8 DataToWrite);
static uint8 Eepm95640_ReadStatus(void);


static boolean Eepm95640_WaitIdle(void);
static uint8 Eepm95640_WriteStatus(uint8 DataToWrite);
static Std_ReturnType Eepm95640_WritePage(uint16_t WriteAddr, uint8 *pBuffer,
										  uint16_t NumToWrite);

static uint8 Eepm95640_Buffer[BUFF_SIZE];


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/************************************************************************************
*   Function Name:  Eepm95640_WriteEnable
*
*   Descriptions: set the write enable latch(WEL) bit of the status register
*
*
*   Parameters:     none
*
*   Return Value:   none
*
*************************************************************************************/
static void Eepm95640_WriteEnable(void)
{
	uint8 ins = WREN;

	SpiIf_TransmitEepRegister(&ins, NULL_PTR, 1);
}

/************************************************************************************
*   Function Name:  Eepm95640_WriteDisable
*
*   Descriptions: reset the write enable latch(WEL) bit of the status register
*
*
*   Parameters:     none
*
*   Return Value:   none
*
*************************************************************************************/
static void Eepm95640_WriteDisable(void)
{
	uint8 ins = WRDI;

	SpiIf_TransmitEepRegister(&ins, NULL_PTR, 1);
}

/************************************************************************************
 *	Function Name:	Eepm95640_ProtectedSet
 *
 *	Descriptions: Eepm95640 write status register
 *
 *
 *	Parameters: 	DataToWrite
 *					SPM_NONE	       0x00    //Software Protected (none)
					SPM_UPPER_QUARTER  0x04    //Software Protected (Upper quarter  1800h - 1FFFh(M95640))
					SPM_UPPER_HALF     0x08    //Software Protected (Upper half     1000h - 1FFFh(M95640))
					SPM_WHOLE_MEMORY   0x0C    //Software Protected (Whole memory   0000h - 1FFFh(M95640))

					HPM_NONE	       0x80    //Hardware Protected (none)
					HPM_UPPER_QUARTER  0x84    //Hardware Protected (Upper quarter  1800h - 1FFFh(M95640))
					HPM_UPPER_HALF     0x88    //Hardware Protected (Upper half     1000h - 1FFFh(M95640))
					HPM_WHOLE_MEMORY   0x8C    //Hardware Protected (Whole memory   0000h - 1FFFh(M95640))
 *
 *	Return Value:	none
 *
 *************************************************************************************/
static void Eepm95640_ProtectedSet(uint8 DataToWrite)
{
	uint8 status = 0;

	status = Eepm95640_WriteStatus(DataToWrite);
}

/************************************************************************************
 *	Function Name:	Eepm95640_WriteStatus
 *
 *	Descriptions: Write new values to the status register
 only effect on SRWD(b7)茫鈧拷BP1(b3) and BP0(b2) of the Status Register
 b6, b5 and b4 are always read as 0
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
static uint8 Eepm95640_WriteStatus(uint8 DataToWrite)
{
	uint8 rxData[2] = {WRSR, 0};

	rxData[1] = DataToWrite;

	Eepm95640_WriteEnable(); //Set the write enable latch

	SpiIf_TransmitEepRegister(rxData, NULL_PTR, 2);

	return OK;
}

/************************************************************************************
 *	Function Name:	Eepm95640_ReadStatus
 *
 *	Descriptions: Eepm95640 read status register
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
static uint8 Eepm95640_ReadStatus(void)
{
	uint8 txData[2] = {RDSR, 0};
	uint8 status[2] = {0, 0};

	SpiIf_TransmitEepRegister(txData, status, 2);

	return status[1];
}

/************************************************************************************
 *	Function Name:	Eepm95640_WaitIdle
 *
 *	Descriptions: Wait Eepm95640 devices idle
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
static boolean Eepm95640_WaitIdle(void)
{
	uint8 status_d = Eepm95640_ReadStatus();
	uint16_t num_i = 0;

	while ((status_d & 0x01) && (num_i < WAIT_T)) 	//Wait until no write operation is in progress.
	{
		delay_us(10);
		status_d = Eepm95640_ReadStatus(); 			//Read status register value.
		num_i++;
	}

	return (num_i < WAIT_T);
}

///************************************************************************************
// *	Function Name:	Eepm95640_ResetBuff
// *
// *	Descriptions: Clear eeprom95640 write data buffer.
// *
// *
// *	Parameters: 	none
// *
// *	Return Value:	none
// *
// *************************************************************************************/
//static void Eepm95640_ResetBuff(void)
//{
//	memset(&Eepm95640_Buffer[0], EA_ERASE_PATTERN, BUFF_SIZE);
//}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief        The function initializes Eep module.
* @details      The function sets the internal module variables according to given
*               configuration set.
*
* @param[in]    pConfigPtr        Pointer to eeprom driver configuration set.
*
* @api
*
* @pre          @p pConfigPtr must not be @p NULL_PTR and the module status must not
*               be @p MEMIF_BUSY.
*
* @implements     Eep_Init_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
void Eepm95640_Init(void)
{
	uint8 status = 0;

	uint8 status_d = Eepm95640_ReadStatus();

	if((status_d & 0x01) == 0x00)	//Wait until no write operation is in progress.
	{
//		status = Eepm95640_WriteStatus(SPM_NONE);		//Software Protected (none)
		Eepm95640_ProtectedSet(SPM_NONE);		//Software Protected (none)
	}
}

/************************************************************************************
 *	Function Name:	Eepm95640_Erase
 *
 *	Descriptions: Erase eeprom95640 memory.
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
Std_ReturnType Eepm95640_Erase(uint16_t address, uint16_t size)
{
#if 0
	Std_ReturnType ret = E_NOT_OK;
	uint16_t erase_idx;
	uint16_t num_pages;
	uint16_t remained_bytes;
	uint16_t str_address;

	str_address = address;
	num_pages = size / BUFF_SIZE;
	remained_bytes = size % BUFF_SIZE;

	Eepm95640_ResetBuff();

	for (erase_idx = 0; erase_idx < num_pages; erase_idx++)
	{
		ret = Eepm95640_Write(str_address, &Eepm95640_Buffer[0], BUFF_SIZE);

		if (ret != E_OK)
		{
			break;
		}
		else
		{
			str_address += BUFF_SIZE;
		}
	}

	if ((ret == E_OK) && (remained_bytes != 0u))
	{
		ret = Eepm95640_Write(str_address, &Eepm95640_Buffer[0], remained_bytes);
	}
#endif

	return E_OK;
}

/************************************************************************************
 *	Function Name:	m95640_Compare
 *
 *	Descriptions: m95640 memory.
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
Std_ReturnType m95640_Compare(uint16_t SourceAddress, uint8 *pTargetAddressPtr, uint16_t Length)
{
	Std_ReturnType ret;

	if (Length <= BUFF_SIZE)
	{
		ret = Eepm95640_Read(SourceAddress, &Eepm95640_Buffer[0], Length);

		if (ret == E_OK)
		{
			if (0 != memcmp(&Eepm95640_Buffer[0], pTargetAddressPtr, Length))
			{
				ret = E_NOT_OK;
			}
			else
			{
				ret = E_OK;
			}
		}
	}
	else
	{
		ret = E_NOT_OK;
	}

	return ret;
}

/************************************************************************************
 *	Function Name:	Eepm95640_Compare
 *
 *	Descriptions: Compares a eeprom memory area with an application data buffer.
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
Std_ReturnType Eepm95640_Compare(uint16_t SourceAddress, uint8 *pTargetAddressPtr, uint16_t Length)
{
	Std_ReturnType ret = E_OK;
	volatile uint16_t src_address;
	volatile uint8* dst_address;
	uint16_t page_idx;
	uint16_t num_pages;
	uint16_t remained_bytes;

	src_address = SourceAddress;
	dst_address = pTargetAddressPtr;
	num_pages = Length / BUFF_SIZE;
	remained_bytes = Length % BUFF_SIZE;

	for (page_idx = 0; page_idx < num_pages; page_idx++)
	{
		ret = m95640_Compare(src_address, dst_address, BUFF_SIZE);

		if (ret == E_NOT_OK)
		{
			break;
		}
		else
		{
			src_address += BUFF_SIZE;
			dst_address += BUFF_SIZE;
		}
	}

	if ((ret == E_OK) && (remained_bytes != 0))
	{
		ret = m95640_Compare(src_address, dst_address, remained_bytes);
	}

	return ret;
}

/************************************************************************************
 *	Function Name:	Eepm95640_WritePage
 *
 *	Descriptions:
 *
 *
 *	Return Value:	none
 *
 *************************************************************************************/
Std_ReturnType Eepm95640_WritePage(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite)
{
	Std_ReturnType ret;

	uint8 ins[] = {WRITE, 0, 0};
	ins[1] = WriteAddr >> 8;
	ins[2] = WriteAddr & 0xFF;

	Eepm95640_WriteEnable(); //Set the write enable latch

	ret = SpiIf_TransmitEepWriteData(ins, sizeof(ins), pBuffer, NumToWrite);

	return ret;
}

/**
* @brief            Write one or more complete eeprom pages to the eeprom device.
* @details          Starts a write job asynchronously. The actual job is performed by
*                   Eep_MainFunction.
*
* @param[in]        TargetAddress        Target address in eeprom memory.
* @param[in]        SourceAddressPtr     Pointer to source data buffer.
* @param[in]        Length               Number of bytes to write.
*
* @return           Std_ReturnType
* @retval           E_OK                 Write command has been accepted.
* @retval           E_NOT_OK             Write command has not been accepted.
*
* @api
*
* @pre              The module has to be initialized and not busy.
*
* @implements       Eep_Write_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
Std_ReturnType Eepm95640_Write(uint16_t WriteAddr, uint8 *pBuffer, uint16_t NumToWrite, uint16_t *written)
{
	Std_ReturnType ret;
	uint8 PageCurOff;
	uint8 PageRmByte;
//	uint16 WritePageNum = 0;
	uint8* pBufferPtr;

	pBufferPtr = pBuffer;
	PageCurOff = WriteAddr % PAGE_SIZE;
	PageRmByte = PAGE_SIZE - PageCurOff;

	if (PageRmByte > NumToWrite)
	{
	    PageRmByte = NumToWrite;
	}

	*written = 0;

	ret = Eepm95640_WritePage(WriteAddr, pBuffer, PageRmByte);

	if (ret == E_OK)
	{
	    *written = PageRmByte;
	}

#if 0
	if (PageRmByte < NumToWrite)
	{
		ret = Eepm95640_WritePage(WriteAddr, pBufferPtr, PageRmByte);

		if (ret == E_OK)
		{
			WriteAddr += PageRmByte;
			NumToWrite -= PageRmByte;

			pBufferPtr += PageRmByte;

			WritePageNum = NumToWrite / PAGE_SIZE;
			PageRmByte = NumToWrite % PAGE_SIZE;
			while (WritePageNum--)
			{
				ret = Eepm95640_WritePage(WriteAddr, pBufferPtr, PAGE_SIZE);

				if (ret == E_OK)
				{
					WriteAddr += PAGE_SIZE;
					pBufferPtr += PAGE_SIZE;
				}
				else
				{
					break;
				}
			}
			if ((ret == E_OK) && (PageRmByte))
			{
				ret = Eepm95640_WritePage(WriteAddr, pBufferPtr, PageRmByte);
			}
		}
	}
	else
	{
		ret = Eepm95640_WritePage(WriteAddr, pBuffer, NumToWrite);
	}
#endif

	return ret;
}

/**
* @brief            Reads from eeprom memory.
* @details          Starts a read job asynchronously. The actual job is performed by
*                   @p Eep_MainFunction.
*
* @param[in]        SourceAddress        Source address in eeprom memory.
* @param[in]        Length               Number of bytes to read.
* @param[out]       TargetAddressPtr    Pointer to target data buffer.
*
* @return           MemIf_JobResultType
* @retval           MEMIF_JOB_OK              Successfully completed job.
* @retval           MEMIF_JOB_FAILED          Not successfully completed job.
* @retval           MEMIF_JOB_PENDING         Still pending job (not yet completed).
* @retval           MEMIF_JOB_CANCELED        Job has been canceled.
* @retval           MEMIF_BLOCK_INCONSISTENT  Inconsistent block requested, it may
*                                             contains corrupted data.
* @retval           MEMIF_BLOCK_INVALID       Invalid block requested.
*
* @api
*
* @pre            The module has to be initialized and not busy.
* @post
*
* @implements       Eep_Read_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
Std_ReturnType Eepm95640_Read(uint16_t ReadAddr, uint8 *pBuffer, uint16_t NumToRead)
{
	Std_ReturnType ret;
	uint8 ins[] = {READ, 0, 0};
	ins[1] = ReadAddr >> 8;
	ins[2] = ReadAddr & 0xFF;

	if (Eepm95640_WaitIdle())
	{
		ret = SpiIf_TransmitEepReadData(ins, sizeof(ins), pBuffer, NumToRead);
	}
	else
	{
		ret = E_NOT_OK;
	}

	return ret;
}

/**
* @brief            Performs actual eeprom read, write, erase and compare jobs.
* @details          Bytes number processed per cycle depends by job type (erase, write, read, compare)
*                   current EEP module's operating mode (normal, fast)
*                   and write, erase Mode of Execution (sync, async).
*
* @api
*
* @pre              The module has to be initialized.
*
*
* @implements       Eep_MainFunction_Activity
*
* @note             This function have to be called ciclically by the Basic Software Module;
*                   it will do nothing if there aren't pending job.
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
void Eepm95640_MainFunction(void)
{
#if 0
	static uint16 addr_n = Eepm95640BeginAddress;
	static uint16 data_n = 0;
	uint8 status = 0;

	Std_ReturnType ret = E_NOT_OK;

	uint8 status_d = 0;

	if(WriteEepm95640Flag)
	{
		status_d = Eepm95640_ReadStatus();

		if((status_d & 0x01) == 0x00)	//Eepm95640
		{
			memset(Eepm95640_Buffer[data_n], addr_n & 0xFF, PageByte);
			ret = Eep_Write(addr_n, Eepm95640_Buffer[data_n], PageByte);
			addr_n += 32;
			data_n += 32;

			ret = E_OK;

			if(data_n < BUFF_SIZE)
			{
				WriteEepm95640Flag = 0x01;
			}
			else
			{
				WriteEepm95640Flag = 0x00;
			}
		}
	}
#endif
}

/************************************************************************************
 *	Function Name:	Eepm95640_IsInWriting
 *
 *	Descriptions: Read eeprom95640 device status.
 *
 *
 *	Parameters: 	none
 *
 *	Return Value:	none
 *
 *************************************************************************************/
boolean Eepm95640_IsInWriting(void)
{
    uint8_t status;

    status = Eepm95640_ReadStatus();

    return (status & 0x01);
}






