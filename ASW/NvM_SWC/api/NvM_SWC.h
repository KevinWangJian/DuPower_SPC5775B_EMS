/*
 * NvM_SWC.h
 *
 *  Created on: Jan 16, 2017
 *      Author: OX81HC
 */

#ifndef NvM_SWC_H_
#define NvM_SWC_H_
typedef enum NvM_Test_t{
	SWC_ZERO = 0,
	ASW_WRITE_BLOCK_1024,
	ASW_READ_BLOCK_1024,
	ASW_WRITE_REDUNDANT_BLOCK_1024,
	ASW_READ_REDUNDANT_BLOCK_1024,
	ASW_WRITE_ALL_BLKS_REQ,
	ASW_CORRUPT_ONE_BLOCK_OF_REDUNDANT_BLOCK_1024_1,
	ASW_CORRUPT_ONE_BLOCK_OF_REDUNDANT_BLOCK_1024_2,
	ASW_CORRUPT_TWO_BLOCK_OF_REDUNDANT_BLOCK_1024,
	ASW_CHECK_DATA_IN_EEP,
	ASW_EEPROM_CE,
	ASW_CORRUPT_BLOCK_OF_NATIVE_BLOCK_1024,
	UT_WRITE,
	UT_READ,
	UT_ERASE
}NvM_Test_t;

typedef enum request_result_t{
	REQUEST_OK,
	REQUEST_NOT_OK,
	REQUEST_PENDING,
	NOT_REQUEST
}request_result_t;

typedef enum Flash_Erase_t{
	NOT_ERASE = 0,
	ERASE_BANK0,
	ERASE_BANK1,
	EEPROM_CE
}Flash_Erase_t;

typedef enum NvM_SwcIModifyNvBlock_State_t{
	MDF_NONE,
	MDF_INIT_STATE,
	MDF_ERASE_BANK,
	MDF_MODIFY_DATA,
	MDF_UPDATE_DATA,
	MDF_UPDATE_MANANGMENT_INFO
}MDF_State_t;

typedef enum NvM_SwcIModifyBothNvBlock_State_t{
	MODIFY_BOTH_NV_BLOCK_NONE,
	MODIFY_READ_BLOCK,
	MODIFY_BACKUP_BLOCK
}MDF_Both_State_t;

/*Test data*/
extern uint8 TEST_DATA_NVM_NATIVE_1024[1024];
extern uint8 TEST_DATA_NVM_REDUNDANT_1024[1024];
extern uint8 TEST_DATA_NVM_NATIVE_512[512];
extern uint32 NVData_Test;
/*Internal test functions*/
//#define NvM_SWC_START_SEC_CODE
//#include "NvM_SWC_MemMap.h"
void UpdatePIMWithValue(uint8 *dst, uint32 length, uint8 Value) ;
//#define NvM_SWC_STOP_SEC_CODE
//#include "NvM_SWC_MemMap.h"

//#define NvM_SWC_START_SEC_CODE
//#include "NvM_SWC_MemMap.h"
//void WriteAll_ImmediateBlock (void);
//#define NvM_SWC_STOP_SEC_CODE
//#include "NvM_SWC_MemMap.h"
//
//#define NvM_SWC_START_SEC_CODE
//#include "NvM_SWC_MemMap.h"
//void ReadAll_ImmediateBlock (void);
//#define NvM_SWC_STOP_SEC_CODE
//#include "NvM_SWC_MemMap.h"
//
//#define NvM_SWC_START_SEC_CODE
//#include "NvM_SWC_MemMap.h"
//void NvM_Swc_EEP(void);
//#define NvM_SWC_STOP_SEC_CODE
//#include "NvM_SWC_MemMap.h"

#endif /* NvM_SWC_H_ */
