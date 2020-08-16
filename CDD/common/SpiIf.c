#include "SpiIf.h"
#include "Dio.h"
#include "Spi.h"
#include "common.h"

#define RETURN_ON_ERROR(rType)\
	do { if (rType != E_OK) {return rType;} } while(FALSE)

#define WAIT_AFERX_TIEMOUT	(15U)

//static Std_ReturnType SpiIf_SyncWaitAfeRx(void);
static Std_ReturnType SpiIf_SyncWaitAfeRx(uint32 rxLen);

uint8 afe_RxData[75];
uint8 RxIdxIn=0;
Std_ReturnType SpiIf_TransmitHv(uint16 txData, uint16 *rxData)
{

	Std_ReturnType rType = E_OK;
//	uint16 txdata_u16 = txData;

	rType = Spi_WriteIB(SpiConf_SpiChannel_HvChannel, &txData);

	if (rType == E_OK)
	{
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_HvCommand);
		if (rType == E_OK)
		{
			rType = Spi_ReadIB(SpiConf_SpiChannel_HvChannel, rxData);
		}
	}

	return rType;

}

Std_ReturnType SpiIf_TransmitSbc(uint16 txData, uint32 *rxData)
{

	Std_ReturnType rType = E_OK;
	uint8 txdata_arr[2] = {0};
	uint8 rxdata_arr[4] = {0};

	txdata_arr[0] = (uint8)(txData >>8 & 0xFF);
	txdata_arr[1] = (uint8)txData;

	rType = Spi_WriteIB(SpiConf_SpiChannel_SbcChannel, txdata_arr);
	if (rType == E_OK)
	{
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_SbcCommand);
		if (rType == E_OK)
		{
			rType = Spi_ReadIB(SpiConf_SpiChannel_SbcChannel, rxdata_arr);
		}
	}

	*rxData = (uint32)(rxdata_arr[0] << 8 | rxdata_arr[1]);

	return rType;

}


Std_ReturnType SpiIf_TransmitEepReadData(uint8 *ins, uint32 insLen, uint8 *data, uint32 dataLen)
{
	Std_ReturnType rType = E_OK;

	rType = Spi_SetupEB(SpiConf_SpiChannel_RomChannel_Instruction, ins, NULL_PTR, insLen);
	RETURN_ON_ERROR(rType);

	rType = Spi_SetupEB(SpiConf_SpiChannel_RomChannel_Data, NULL_PTR, data, dataLen);
		RETURN_ON_ERROR(rType);

	if (rType == E_OK)
	{
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_RomDataCommand);
	}

	return rType;
}


Std_ReturnType SpiIf_TransmitEepWriteData(uint8 *ins, uint32 insLen, uint8 *data, uint32 dataLen)
{
	Std_ReturnType rType = E_OK;

	rType = Spi_SetupEB(SpiConf_SpiChannel_RomChannel_Instruction, ins, NULL_PTR, insLen);
	RETURN_ON_ERROR(rType);

	rType = Spi_SetupEB(SpiConf_SpiChannel_RomChannel_Data, data, NULL_PTR, dataLen);
		RETURN_ON_ERROR(rType);

	if (rType == E_OK)
	{
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_RomDataCommand);
	}

	return rType;
}

Std_ReturnType SpiIf_TransmitEepRegister(uint8 *txData, uint8 *rxData, uint32 len)
{
	Std_ReturnType rType = E_OK;

	rType = Spi_SetupEB(SpiConf_SpiChannel_RomChannel_Instruction, txData, rxData, len);
	if (rType == E_OK)
	{
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_RomOpCommand);
	}

	return rType;
}


Std_ReturnType SpiIf_TransmitRtc(uint8 *txData, uint8 *rxData, uint32 len)
{

	Std_ReturnType rType = E_OK;

	rType = Spi_SetupEB(SpiConf_SpiChannel_RtcChannel, txData, rxData, len);
	if (rType == E_OK)
	{
		Dio_WriteChannel(DioConf_DioChannel_MCU_DSPI_C_PCA21125_CS, STD_HIGH);
		rType = Spi_SyncTransmit(SpiConf_SpiSequence_RtcCommand);
	    Dio_WriteChannel(DioConf_DioChannel_MCU_DSPI_C_PCA21125_CS, STD_LOW);
	}

	return rType;

}

Std_ReturnType SpiIf_TransmitAfe(uint8 *txData, uint32 txLen, uint8 *rxData, uint32 rxLen)
{}

//static Std_ReturnType SpiIf_SyncWaitAfeRx(void)
static Std_ReturnType SpiIf_SyncWaitAfeRx(uint32 rxLen)
{}

Std_ReturnType SpiIf_TransmitTJA1145(uint8 *txData, uint8 *rxData, uint32 len)
{}

