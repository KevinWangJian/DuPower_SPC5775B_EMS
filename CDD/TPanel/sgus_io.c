
#include "sgus_io.h"
#include "Rte_Asw_Swc.h"

extern uint8 gaucNVData1[];



typedef struct
{
    uint8_t InputControl[16];
}sgus_nvmdata_t;

sgus_nvmdata_t SGUS_NVMData;

void SGUS_NVM_CopyDataToRam(void)
{
	Rte_Call_RPort_NVDataBlock1_ReadBlock(&gaucNVData1);
	memcpy((uint8_t*)(&SGUS_NVMData),(uint8_t*)gaucNVData1, sizeof(sgus_nvmdata_t));
}

void SGUS_NVM_StoreDataToFlash(void)
{
	memcpy((uint8_t*)gaucNVData1,(uint8_t*)(&SGUS_NVMData),sizeof(sgus_nvmdata_t));
	Rte_Call_RPort_NVDataBlock1_WriteBlock(gaucNVData1);
}



void SGUS_IO_Store_InputControl(uint8_t * inputcontrol)
{
    uint8_t i;
    for(i = 0; i < 16; i++)
    {
        SGUS_NVMData.InputControl[i] = inputcontrol[i];
    }
    SGUS_NVM_StoreDataToFlash();
}


void SGUS_IO_Read_InputControl(uint8_t * inputcontrol)
{
    uint8_t i;
    SGUS_NVM_CopyDataToRam();
    for(i = 0; i < 16; i++)
    {
	    inputcontrol[i] = SGUS_NVMData.InputControl[i];
    }
}


