/*
 * Dcm_Stub.c
 *
 *  Created on: Apr 28, 2018
 *      Author: ZBO4SGH
 */

#include "Std_Types.h"
#include "Rte_Type.h"
#include "Eep.h"
#include "Rte_IoHwAb.h"
#include "Dcm_SWC.h"
#include "Rte_Asw_Swc.h"
#include "NVM.h"
#include "Uds_Srv.h"
#include "NvM_SWC.h"

#pragma section DATA ".cal_data"
const uint8 F1A1_EcuCalibrationSoftwareNumber[6]={'D',0x00,0x00,0x00,0x00,0x02};                       //D0000000002
#pragma section DATA

const uint8 F183_EcuBootSwRefNumber[10]="EV31AB002R";     //EV31AB002R
const uint8 F18A_SystemSupplierIdentifier[6]={'P',0x01,0x31,0x70,0x00,0x00};                           //P01164                                  //
const uint8 F191_ECUHardwareNumber[6]={'D',0x00,0x00,0x00,0x00,0x01};                                  //B6907210000
const uint8 F191_SupplierEcuHwRefNumber[12]="EMS0A0000P10";   //BMSBH01AH0        //EMS0E0000P00
const uint8 F194_SupplierEcuSwRefNumber[12]="EMS0A001R010";   //EV31AH04S4BR190   //EMS0E000R000
const uint8 F1A0_EcuApplicationSoftwareNumber[6]={'D',0x00,0x00,0x00,0x00,0x02};                        //N0000000001
const uint8 F1A2_EcuNetReferenceNumber[6]={'D',0x00,0x00,0x00,0x00,0x03};                               //N0000000003

NVM_DIDDATA NVM_DidData={0};

 uint8 Test_DcmSeed[4] = {
    0x11, 0x22, 0x33, 0x44  /*seed for LEV1 */
} ;
 uint8 Test_DcmKey[4] = {
    0x10, 0x20, 0x30, 0x40  /*key for LEV2 */
} ;

//test
uint32 Test_UDS_Key=0;

Std_ReturnType retValue = RTE_E_INVALID;

extern uint8 DiagData1[512];

void Str_MemoryCopy(uint8 *ptr_d, uint8 *ptr_s, uint32 size)
{
	 uint32 i;

	 for (i=0; i<size; i++)
	 {
		*ptr_d++ = *ptr_s++;
	 }
}


void UDS_NVM_CopyDIDToRam(void)
{
	Rte_Call_DiagDataBlock1_ReadBlock(&DiagData1);
	Str_MemoryCopy((uint8_t*)(&NVM_DidData),(uint8_t*)DiagData1, sizeof(NVM_DidData));
}

void UDS_NVM_StoreDIDToFee(void)
{
	Str_MemoryCopy((uint8_t*)DiagData1,(uint8_t*)(&NVM_DidData),sizeof(NVM_DidData));
	Rte_Call_DiagDataBlock1_WriteBlock(DiagData1);
}



FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L1_GetSeed(
	VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,
	VAR(uint8,AUTOMATIC) Seedlen_u8,
	VAR(uint8,AUTOMATIC) AccDataRecsize_u8,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,
	VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{

	Test_DcmSeed[0] = rand()%255;
	Test_DcmSeed[1] = rand()%255;
	Test_DcmSeed[2] = rand()%255;
	Test_DcmSeed[3] = rand()%255;

	Seed[0] = Test_DcmSeed[0];
	Seed[1] = Test_DcmSeed[1];
	Seed[2] = Test_DcmSeed[2];
	Seed[3] = Test_DcmSeed[3];
	return E_OK;

}

/***Seca dcmDspSecurityCompareKeyFnc functions with Useport  USE_ASYNCH_FNC ***/
FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L1_CompareKey(
	VAR(uint8,AUTOMATIC) KeyLen,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,
	VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{

	uint32 Seed = (uint32)(((uint32)Test_DcmSeed[0]<<(uint8)24)|((uint32)Test_DcmSeed[1]<<(uint8)16)|((uint32)Test_DcmSeed[2]<<(uint8)8)|((uint32)Test_DcmSeed[3]));
	uint32 ReturnKey= Seed_2_Key_L1(Seed,SECURITY_LEVEL1);
	Test_DcmKey[0] = (uint8) ((ReturnKey >> (uint8)24) & (uint32)0x000000FFu);
	Test_DcmKey[1] = (uint8) ((ReturnKey >> (uint8)16) & (uint32)0x000000FF);
	Test_DcmKey[2] = (uint8) ((ReturnKey >> (uint8)8) & (uint32)0x000000FF);
	Test_DcmKey[3] = (uint8) (ReturnKey & (uint32)0x000000FF);
	if((Key[0] == Test_DcmKey[0])&&(Key[1] == Test_DcmKey[1])&&(Key[2] == Test_DcmKey[2])&&(Key[3] == Test_DcmKey[3]))
	{
		retValue = E_OK;
	}
	else
	{
		*ErrorCode=0x35;
		retValue = E_NOT_OK;
	}

	return retValue;
}


FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L2_GetSeed(
	VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,
	VAR(uint8,AUTOMATIC) Seedlen_u8,
	VAR(uint8,AUTOMATIC) AccDataRecsize_u8,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,
	VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{

	Test_DcmSeed[0] = rand()%255;
	Test_DcmSeed[1] = rand()%255;
	Test_DcmSeed[2] = rand()%255;
	Test_DcmSeed[3] = rand()%255;

	Seed[0] = Test_DcmSeed[0];
	Seed[1] = Test_DcmSeed[1];
	Seed[2] = Test_DcmSeed[2];
	Seed[3] = Test_DcmSeed[3];

	return E_OK;
}

FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L2_CompareKey(
	VAR(uint8,AUTOMATIC) KeyLen,
	P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,
	VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{

	uint32 Seed = (uint32)(((uint32)Test_DcmSeed[0]<<(uint8)24)|((uint32)Test_DcmSeed[1]<<(uint8)16)|((uint32)Test_DcmSeed[2]<<(uint8)8)|((uint32)Test_DcmSeed[3]));
	uint32 ReturnKey= Seed_2_Key_L1(Seed,SECURITY_LEVEL2);
	Test_DcmKey[0] = (uint8) ((ReturnKey >> (uint8)24) & (uint32)0x000000FFu);
	Test_DcmKey[1] = (uint8) ((ReturnKey >> (uint8)16) & (uint32)0x000000FF);
	Test_DcmKey[2] = (uint8) ((ReturnKey >> (uint8)8) & (uint32)0x000000FF);
	Test_DcmKey[3] = (uint8) (ReturnKey & (uint32)0x000000FF);
	if((Key[0] == Test_DcmKey[0])&&(Key[1] == Test_DcmKey[1])&&(Key[2] == Test_DcmKey[2])&&(Key[3] == Test_DcmKey[3]))
	{
		retValue = E_OK;
	}
	else
	{
		*ErrorCode=0x35;
		retValue = E_NOT_OK;
	}
	return retValue;

}

 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F186 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
 {
	 *Data = Dcm_DidServices_F186_ReadData();
 	 return E_OK;
 }

 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_0101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}


FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F183 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F187 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F18B (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F18C (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F191 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	Str_MemoryCopy(Data,&F191_SupplierEcuHwRefNumber[0],12);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F194 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	Str_MemoryCopy(Data,&F194_SupplierEcuSwRefNumber[0],12);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A1 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A2 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.ChargeGunNumber_F1A2[0],32);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A3 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.AFCManufactureDate_F1A3[0],3);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A4 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.AFCSerialNumber_F1A4[0],10);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A5 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A6 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C001 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.AFCFeatureInformation_C001[0],10);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C002 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.WaltMeterAddress_C002[0],24);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C003 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.DCDCAddressOfYonglian_C003[0],30);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C004 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{

	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.VIN_F190[0],18);

	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.DCDCAddressOfFuTe_C004[0],8);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C005 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.CCVID_C005[0],6);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C006(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C007 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.AFCOperatorCode_C007[0],9);
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C008 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C009 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C010 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C011 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C012 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D102 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D103 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D104 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D105 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D106 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D110 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D112 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D114 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D117 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D118 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D119 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D120 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E100 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E102 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E103 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E104 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D107 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D108 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D109 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D111 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D113 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}

FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D115 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D116 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D121 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D122 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D123 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}



/***Extern declarations for XXX_ReadData of type USE_DATA_SYNCH_FNC ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_Read_Fnc (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F190 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data)
{
	UDS_NVM_CopyDIDToRam();
	Str_MemoryCopy(Data,&NVM_DidData.VIN_F190[0],18);
	return E_OK;
}






/***Extern declarations for XXX_WriteData of type USE_DATA_ASYNCH_FNC  and of fixed length ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F187 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F18B (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F18C (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F191 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A2 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	//Uds_Send_NegResp(0x22, 0x78);

	Str_MemoryCopy(&NVM_DidData.ChargeGunNumber_F1A2[0],Data,32);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A3 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	//Uds_Send_NegResp(0x22, 0x78);

	Str_MemoryCopy(&NVM_DidData.AFCManufactureDate_F1A3[0],Data,3);
	UDS_NVM_StoreDIDToFee();

	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A4 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.AFCSerialNumber_F1A4[0],Data,10);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A5 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A6 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C001 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.AFCFeatureInformation_C001[0],Data,10);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C002 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.WaltMeterAddress_C002[0],Data,24);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C003 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.DCDCAddressOfYonglian_C003[0],Data,30);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C004 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.DCDCAddressOfFuTe_C004[0],Data,8);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C005 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.CCVID_C005[0],Data,6);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C006 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C007 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	Str_MemoryCopy(&NVM_DidData.AFCOperatorCode_C007[0],Data,9);
	UDS_NVM_StoreDIDToFee();
	return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C008 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C009 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C010 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C011 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C012 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}


FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F190 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	//Uds_Send_NegResp(0x22, 0x78);

	Str_MemoryCopy(&NVM_DidData.VIN_F190[0],Data,18);
	UDS_NVM_StoreDIDToFee();

	return E_OK;
}



/***Extern declarations for XXX_FreezeCurrentStateFnc of type USE_DATA_ASYNCH_FNC ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_FreezeCurrentState_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}

/***Extern declarations for XXX_FreezeCurrentStateFnc of type USE_DATA_SYNCH_FNC ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}

/***Extern declarations for XXX_ResetToDefaultFnc of type USE_DATA_ASYNCH_FNC ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ResetToDefault_Fnc (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}

/***Extern declarations for XXX_ResetToDefaultFnc of type USE_DATA_SYNCH_FNC ***/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}

/***Extern declarations for ReturnControlToEcuFnc.Only Synchronous API is used irrespective of UsePort Configuration to USE_DATA_SYNCH_FNC or USE_DATA_ASYNCH_FNC **/
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}


/***Extern declarations for ShortTermAdjustmentFnc of type USE_DATA_ASYNCH_FNC  for Fixed LENGTH with no control mask or internal control mask handling***/

/***Extern declarations for ShortTermAdjustmentFnc of type USE_DATA_ASYNCH_FNC  for variable LENGTH with no control mask or internal control mask handling***/




FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	 return E_OK;
}




/***Routine control Appl functions***/



/*** Extern declaration for DcmDspStartRoutine_4AF0 ***/
 FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspStartRoutine_4AF0(
VAR(uint8, AUTOMATIC) dataIn1,
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
                         P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut1,
                          P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode)
{
	 return E_OK;
}



 uint32 Seed_2_Key_L1(uint32 in_seed,uint8 SecurityLevel_Index)
 {
 	uint32 key = 0;

 	uint32 MASK=0;
 	uint8 i;

 	if(1==SecurityLevel_Index)
 	{
 		MASK = 0x6D696D69;
 	}else if(2==SecurityLevel_Index)
 	{
 		MASK = 0x696E696E;
 	}else{

 	}


 	if (in_seed !=0 )
 	{
 		for (i=0; i<35; i++)
 		{
 			if (in_seed & 0x80000000)
 			{
 				in_seed = in_seed <<1;
 				in_seed = in_seed^MASK;
 			}
 			else
 			{
 				in_seed = in_seed << 1;
 			}
 		}
 		key = in_seed;
 	}
 	return key;
 }





