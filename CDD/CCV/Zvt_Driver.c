/*
 * Zvt_Driver.c
 *
 *  Created on: 2019濠德板�楁慨鐑藉磿閹达箑绠柨鐕傛嫹12闂傚倷绀�?幖顐︽偋閻愬搫绠柨鐕傛�?30闂傚倷绀�?幖顐�?窗濞戙垹绠柨鐕傛嫹
 *      Author: admin
 */


#include "Zvt_Driver.h"
#include "Eth.h"



volatile uint8 zvtClientConfigFlag = FALSE;
volatile uint8 ptConfigFlag = FALSE;
volatile uint8 zvtClientRunFlag = FALSE;
volatile uint8 ptRunFlag = FALSE;

volatile zvt_cardtype cardTypeFlag = 0u;

extern zvt_writerte_t Zvt_WriteRte;
extern zvt_readasw_t Zvt_ReadAsw;
extern zvt_readasw_t Zvt_ReadAsw_Pre;

extern zvt_pt_ipmode IpModeFlag;

extern ccv_configdata_t			PtConfigData;
extern ccv_ptconfig_factory0813_t PtConfig0813FactoryData;
extern ccv_ptconfig_user0813_t    PtConfig0813UserData;
extern ccv_ptconfig_0693_t		  PtInit0693Data;
extern ccv_ptconfig_0670emv_t     PtDiag0670EmvData;


extern zvt_preauthdata_t 			CCV_PreAuthData;
extern zvt_partialreversaldata_t 	CCV_PartReverData;
extern zvt_credituserstopdata_t 	UserStopCreditData;
extern zvt_mifaredata_t            CCV_MifareData;


extern zvt_pt_errcode_t  PtErrCode;
 zvt_preauth_fsm 	 PreAuth_Fsm;
extern zvt_pt_errcode_t  PtErrCode;
extern volatile zvt_wrcomtest_t 	 ZvtCom_Write;
extern volatile zvt_rdcomtest_t   ZvtCom_Read;

 zvt_ptconfig_factory0600_t 	PtConfigFactory0600Data;
 zvt_ptconfig_factory0813_t 	PtConfigFactory0813Data;
 zvt_ptconfig_user0813_t    	PtConfigUser0813Data;
 zvt_ptconfig_user0693_t		PtConfigUser0693Data;
 zvt_ptconfig_user0670emv_t 	PtConfigUser0670emvData;



/**** global signal from EMS to PT ***/

zvt_ptconfig_t stPtCfgData;
zvt_transmitdata2pt_t stSendData2PT;


zvt_pt_init_statemachine_t PtInitState;
zvt_pt_cmdflag_t  PtCmdFlag;
zvt_pt_receiptnumber_t PtReceiptNo;

uint8 Rfid_UID_Number[10u] = {0u};


/**** global signal from PT to EMS ***/

zvt_extractdata_cmd_t extractCmd040fData;
zvt_extractdata_cmd_t extractCmd040fStdData;
zvt_extractdata_cmd_t extractCmd040fExtData;

zvt_extractdata_cmd_t debug_extractCmd040fExtData;


volatile zvt_extractdata_cmd_t extractCmd04ffStdData;
volatile zvt_extractdata_cmd_t extractCmd04ffExtData;

volatile zvt_extractdata_cmd_t extractCmd060fStdData;
volatile zvt_extractdata_cmd_t extractCmd060fExtData;


/***************************************************/
uint8 zvtSocketRxFrame[1500];

TcpIp_SocketIdType zvtSocketIdex;
uint16 zvtSocketRxFrameSize;
uint8 zvtSignalFrPt_Arr[TCP_PAYLOAD_MAX_LENGTH] = {0};
uint8 zvtSignalFrPt_Arr_Temp[TCP_PAYLOAD_MAX_LENGTH] = {0};
uint8 formatStdExtFlag = NonZvtFormat;
uint8 stdApduTotalLength;
uint16 extApduTotalLength;

/*	cmd 040f	*/
uint8 ui8StdFormatCmd040f_ByteCount;
uint8 ui8StdFormatCmd040f_PollCount;
uint8 ui8StdFormatCmd040f_PollCountTemp;
uint8 ui8ExtFormatCmd040f_PollCount;
uint8 ui8ExtFormatCmd040f_PollCountTemp;
uint16 ui16ExtFormatCmd040f_ByteCount;

uint16 Cmd040fGiveSIDto0622_Loop;
uint16 Cmd040fGiveSIDto06C0_Loop;


uint8 cmd040FSocketRxFrame[1000];


uint16 cmd040FrxLength;
volatile uint16 cmd040FrxDtaBlockLength;



/*	cmd 04ff	*/
uint8 ui8StdFormatCmd04ff_ByteCount;
uint8 ui8StdFormatCmd04ff_PollCount;

uint8 ui8ExtFormatCmd04ff_PollCount;
uint16 ui16ExtFormatCmd04ff_ByteCount;
uint8 cmd04FFSocketRxFrame[1000];

uint16 cmd04ffRxLength;
volatile uint16 cmd04ffRxDtaBlockLength;

zvt_cmd04ff_stdformat_t  cmd04ffPayload;

/*	cmd 060f	*/
uint8 ui8StdFormatCmd060f_PollCount;
uint8 ui8StdFormatCmd060f_ByteCount;
uint8 ui8ExtFormatCmd060f_PollCount;
uint16 ui16ExtFormatCmd060f_ByteCount;
uint8 cmd060FSocketRxFrame[1000];

uint16 cmd060fRxLength;
volatile uint16 cmd060fRxDtaBlockLength;

/*	cmd 061e	*/
uint8 ui8StdFormatCmd061e_ByteCount;
uint8 ui8StdFormatCmd061e_PollCount;

uint8 ui8ExtFormatCmd061e_PollCount;
uint16 ui16ExtFormatCmd061e_ByteCount;
uint8 cmd061ESocketRxFrame[1000];

uint16 cmd061eRxLength;
volatile uint16 cmd061eRxDtaBlockLength;

zvt_cmd061e_stdformat_t  cmd061ePayload;


/*cmd 06D3*/
uint8 cmd06D3SocketRxFrame[6];

/*cmd 8000*/
uint8 cmd8000SocketRxFrame[3];

/*cmd 8400*/
uint8 cmd8400SocketRxFrame[6];


volatile uint8 BitmapVarL_TotalLen_Std;
volatile uint16 BitmapVarL_TotalLen_Ext;

zvt_debugflag_t debugFlagList;

uint8 debugBitmap06BreakFlag = 0u;


uint8 ptInitDebugFlag1 = 0u;
uint8 ptInitDebugFlag2 = 0u;
uint8 ptInitDebugFlag3 = 0u;
uint8 ptInitDebugFlag4 = 0u;
uint8 ptInitDebugFlag5 = 0u;

uint8 debugZvtFlag = 0u;



uint16 zvtRealRxLength;
zvt_erridflag zvtResultCodeFlag;
volatile zvt_erridflag zvt060fResultCodeFlag = 0xFF;


uint32 ui32_Counter5 = 0u;
uint32 ui32_Counter6 = 0u;
uint32 ui32_Counter7 = 0u;
uint32 ui32_Counter8 = 0u;


uint8 dp_i;
Std_ReturnType dp_ret;
BufReq_ReturnType dp_ethRet;
Eth_FrameType dp_frameTypeARP;

uint8 dp_bufIdx;
uint8 *dp_bufIdxPtr = &dp_bufIdx;
uint8 arpSnifferCount;
zvt_arpsniffer arpSnifferFlag;

/*default MAC frame is an ARP message saying "Who has 192.168.10.2? Tell 192.168.10.1"*/
Eth_DataType dp_txMacFrame[ARP_LENGTH_FRAME] = {
    										0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,	/*[0]  Destination Address*/
    										0x66,0x55,0x44,0x33,0x22,0x11,	/*[6]  Source Address(config in tresos)*/
    										0x08,0x06,				  		/*[12] Frametype_ARP*/
    										0x00,0x01,				 		/*[14] ETH, hardware type*/
											0x08,0x00,						/*[16] IP, protocol type*/
											0x06,							/*[18] protocol size*/
											0x04,							/*[19] hardware size*/

											0x00,0x01,						/*[20] Opcode, request =1, reply=2*/
											0x66,0x55,0x44,0x33,0x22,0x11,	/*[22] sender's MAC*/
//	    										0xe4,0xb9,0x7a,0x52,0x98,0xf1,	/*[22] sender's MAC*/
											0xc0,0xa8, 0x0a,0x01,			/*[28] sender's IP*/
											0x00,0x00,0x00,0x00,0x00,0x00,	/*[32] targeter's MAC*/
    										0xc0,0xa8,0x0a,0xFA				/*[38] targeter's IP*/
                                        };

Eth_DataType *dp_txBufPtr;
Eth_DataType **dp_txBufPtrPtr = &dp_txBufPtr;
uint16_t dp_lenByte = LENGTH_PAYLOAD;
uint16_t *dp_lenBytePtr = &dp_lenByte;



zvt_transmitdata2pt_t    zvtTx2PtData;

/* ******************************************************
 * Command Sets
 * ******************************************************/
uint8 cmd0101RFU[ZVT_CTRL_FIELD_LEN] 				= {0x01,0x01};
uint8 cmd0401SetDateTimeECR[ZVT_CTRL_FIELD_LEN] 	= {0x04,0x01};						/*PT to the ECR*/
uint8 cmd040DInputRequest[ZVT_CTRL_FIELD_LEN] 		= {0x04,0x0D};						/*PT to the ECR*/
uint8 cmd040EMenuRequest[ZVT_CTRL_FIELD_LEN] 		= {0x04,0x0E};						/*PT to the ECR*/
uint8 cmd040FStatusInformation[ZVT_CTRL_FIELD_LEN] 	= {0x04,0x0F};						/*PT to the ECR*/
uint8 cmd04FFIntermediateStatusInformation[ZVT_CTRL_FIELD_LEN] = {0x04,0xFF};			/*PT to the ECR*/
uint8 cmd0501StatusEnquiry[ZVT_CTRL_FIELD_LEN] 		= {0x05,0x01};
uint8 cmd05FFRFU[ZVT_CTRL_FIELD_LEN] 				= {0x05,0xFF};
uint8 cmd0600Registration[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x00};
uint8 cmd0601Authorisation[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x01};
uint8 cmd0602Log_Off[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x02};
uint8 cmd0603AccountBalanceRequest[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x03};
uint8 cmd0604ActivateCard[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x04};
uint8 cmd0605Procurement[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x05};
uint8 cmd0609PrepaidTop_Up[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x09};
uint8 cmd060ATaxFree[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x0A};
uint8 cmd060BRFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x0B};
uint8 cmd060CTip[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x0C};
uint8 cmd060DMenuSelectionWithGraphicDisplay[ZVT_CTRL_FIELD_LEN] = {0x06,0x0D};
uint8 cmd060FCompletion[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x0F};						/*PT to the ECR*/
uint8 cmd0610SendTurnoverTotals[ZVT_CTRL_FIELD_LEN] = {0x06,0x10};
uint8 cmd0611RFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x11};
uint8 cmd0612PrintTurnoverReceipts[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x12};
uint8 cmd0618ResetTerminal[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x18};
uint8 cmd061APrintSystemConfiguration[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x1A};
uint8 cmd061BSet_ResetTerminalID[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x1B};
uint8 cmd061EAbort[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x1E};						/*PT to the ECR*/
uint8 cmd0620RepeatReceipt[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x20};
uint8 cmd0621TelephonicAuthorisation[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x21};
uint8 cmd0622PreAuthorisationReservation[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x22};
uint8 cmd0623PartialReversalPreAuthorisation_BookingReservation[ZVT_CTRL_FIELD_LEN] = {0x06,0x23};
uint8 cmd0624BookTotal[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x24};
uint8 cmd0625PreAuthorisationReversal[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x25};
uint8 cmd0626ReversalExternalTransaction[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x26};
uint8 cmd0630Reversal[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x30};
uint8 cmd0631Refund[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x31};
uint8 cmd0650EndOfDay[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x50};
uint8 cmd0651SendOfflineTransactions[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x51};
uint8 cmd0670Diagnosis[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x70};
uint8 cmd0679Selftest[ZVT_CTRL_FIELD_LEN] 			= {0x06,0x79};
uint8 cmd0682RFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x82};
uint8 cmd0685DisplayText[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x85};
uint8 cmd0686DisplayTextNumericalInput[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x86};
uint8 cmd0687PINVerification[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x87};
uint8 cmd0688DisplayTextFunctionKeyInput[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x88};
uint8 cmd0690RFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0x90};
uint8 cmd0691SetDateTime[ZVT_CTRL_FIELD_LEN] 		= {0x06,0x91};
uint8 cmd0693Initialisation[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x93};
uint8 cmd0695ChangePassword[ZVT_CTRL_FIELD_LEN] 	= {0x06,0x95};
uint8 cmd06B0Abort[ZVT_CTRL_FIELD_LEN] 				= {0x06,0xB0};
uint8 cmd06C0ReadCard[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC0};
uint8 cmd06C1Reserved[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC1};
uint8 cmd06C2Reserved[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC2};
uint8 cmd06C3Reserved[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC3};
uint8 cmd06C4Reserved[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC4};
uint8 cmd06C5CloseCardSession[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xC5};
uint8 cmd06C6SendAPDUs[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xC6};
uint8 cmd06CERFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0xCE};
uint8 cmd06D1PrintLine[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xD1};				/*PT to the ECR*/
uint8 cmd06D3PrintTextBlock[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xD3};				/*PT to the ECR*/
uint8 cmd06D4RFU[ZVT_CTRL_FIELD_LEN] 				= {0x06,0xD4};
uint8 cmd06D8DialUp[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xD8};				/*PT to the ECR*/
uint8 cmd06D9TransmitDataDialUp[ZVT_CTRL_FIELD_LEN] = {0x06,0xD9};				/*PT to the ECR*/
uint8 cmd06DAReceiveDataDialUp[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xDA};				/*PT to the ECR*/
uint8 cmd06DBHangUp[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xDB};				/*PT to the ECR*/
uint8 cmd06DDTransparentMode[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xDD};				/*PT to the ECR*/
uint8 cmd06E0DisplayText[ZVT_CTRL_FIELD_LEN] 		= {0x06,0xE0};
uint8 cmd06E1DisplayTextFunctionKeyInput[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xE1};
uint8 cmd06E2DisplayTextNumericalInput[ZVT_CTRL_FIELD_LEN] 		= {0x06,0xE2};
uint8 cmd06E3PINVerificationCustomerCard[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xE3};
uint8 cmd06E4BlockedListQuery2ECR[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xE4};	/*PT to the ECR*/
uint8 cmd06E5MACCalculation[ZVT_CTRL_FIELD_LEN] 	= {0x06,0xE5};
uint8 cmd06E6CardPollAuthorization[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xE6};
uint8 cmd06E8ReferenceNumberBMP60[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xE8};
uint8 cmd06E9ReferenceNumberBMP58[ZVT_CTRL_FIELD_LEN] 			= {0x06,0xE9};
uint8 cmd06F0DisplayImage[ZVT_CTRL_FIELD_LEN] 		= {0x06,0xF0};
uint8 cmd0801ActivateServiceMode[ZVT_CTRL_FIELD_LEN] 			= {0x08,0x01};
uint8 cmd0802SwitchProtocol[ZVT_CTRL_FIELD_LEN] 	= {0x08,0x02};
uint8 cmd0810SoftwareUpdate[ZVT_CTRL_FIELD_LEN] 	= {0x08,0x10};
uint8 cmd0811ReadFile[ZVT_CTRL_FIELD_LEN] 			= {0x08,0x11};
uint8 cmd0812DeleteFile[ZVT_CTRL_FIELD_LEN] 		= {0x08,0x12};
uint8 cmd0813ChangeConfiguration[ZVT_CTRL_FIELD_LEN]= {0x08,0x13};
uint8 cmd0814WriteFile[ZVT_CTRL_FIELD_LEN] 			= {0x08,0x14};
uint8 cmd0820StartOPTAction[ZVT_CTRL_FIELD_LEN] 	= {0x08,0x20};
uint8 cmd0821SetOPTPointinTime[ZVT_CTRL_FIELD_LEN] 				= {0x08,0x21};
uint8 cmd0822OPTPreInitialisation[ZVT_CTRL_FIELD_LEN] 			= {0x08,0x22};
uint8 cmd0823OutputOPTData[ZVT_CTRL_FIELD_LEN] 		= {0x08,0x23};
uint8 cmd0824OPTOutofOrder[ZVT_CTRL_FIELD_LEN] 		= {0x08,0x24};
uint8 cmd0830SelectLanguage[ZVT_CTRL_FIELD_LEN] 	= {0x08,0x30};
uint8 cmd0840ChangeBaudrate[ZVT_CTRL_FIELD_LEN] 	= {0x08,0x40};
uint8 cmd0850ActivateCardReader[ZVT_CTRL_FIELD_LEN] = {0x08,0x50};
uint8 cmd0FxxReservedProprietaryExtensions[ZVT_CTRL_FIELD_LEN] 	= {0x0F,0x00};			/*****/
uint8 cmd0FCAChipActivator[ZVT_CTRL_FIELD_LEN] 		= {0x0F,0xCA};
uint8 cmd8000PositiveAcknowledgement[ZVT_CTRL_FIELD_LEN] 		= {0x80,0x00};
uint8 cmd8400PositiveAcknowledgement[ZVT_CTRL_FIELD_LEN] 		= {0x84,0x00};
uint8 cmd84xxNegativeAcknowledgement[ZVT_CTRL_FIELD_LEN] 		= {0x84,0x00};
uint8 cmd849CRepeatStatusinfo[ZVT_CTRL_FIELD_LEN] 				= {0x84,0x9C};			/*****/






uint8 debugFlag_ReceiptNoMatch;


uint8 ReceiptData_PreAuth[2u] = {0u};
uint8 ReceiptData_Reversal[2u] = {0u};



uint8 debugWaitFor040f_Flag1 = 0u;
uint8 debugWaitFor040f_Flag2 = 0u;
uint8 debugWaitFor040f_Resp_OK_Flag = 0u;



zvt_switch_fsm FsmSwitchVar;
uint32 FsmWaitTime = 200u;

/* ******************************************************
 * Signal from ZVT to PT
 * ******************************************************/



/*
@brief
@details
@para
@return
@note
*/

static void lPtConfigDataConverter_TID(const uint8* InputData_4B, uint8* OutputData_8B)
{
	uint8 InputArray[4u] = {0u};
	uint8 OutputArray[8u] = {0u};

	memcpy(InputArray, InputData_4B, 4u);

	OutputArray[0u] = (InputArray[0u] / 10u) + 0x30u;
	OutputArray[1u] = (InputArray[0u] % 10u) + 0x30u;

	OutputArray[2u] = (InputArray[1u] / 10u) + 0x30u;
	OutputArray[3u] = (InputArray[1u] % 10u) + 0x30u;

	OutputArray[4u] = (InputArray[2u] / 10u) + 0x30u;
	OutputArray[5u] = (InputArray[2u] % 10u) + 0x30u;

	OutputArray[6u] = (InputArray[3u] / 10u) + 0x30u;
	OutputArray[7u] = (InputArray[3u] % 10u) + 0x30u;

	memcpy(OutputData_8B, OutputArray, 8u);
}

/*
@brief
@details
@para
@return
@note
*/
static void lPtConfigDataConverter_IP_Netmask_Gateway(uint8* InputData_4B, uint8* OutputData_15B)
{
	uint8 InputArray[4u] = {0u};
	uint8 OutputArray[15u] = {0u};

	memcpy(InputArray, InputData_4B, 4u);

	OutputArray[0u] = (InputArray[0u] / 100u) + 0x30u;           /*bai wei*/
	OutputArray[1u] = ((InputArray[0u] % 100u) / 10u) + 0x30u;   /*shi*/
	OutputArray[2u] = (InputArray[0u] % 10u) + 0x30u;			 /*ge*/

	OutputArray[3u] = 0x2E;										 /* . */

	OutputArray[4u] = (InputArray[1u] / 100u) + 0x30u;           /*bai*/
	OutputArray[5u] = ((InputArray[1u] % 100u) / 10u) + 0x30u;   /*shi*/
	OutputArray[6u] = (InputArray[1u] % 10u) + 0x30u;			 /*ge*/

	OutputArray[7u] = 0x2E;										 /* . */

	OutputArray[8u] = (InputArray[2u] / 100u) + 0x30u;           /*bai*/
	OutputArray[9u] = ((InputArray[2u] % 100u) / 10u) + 0x30u;   /*shi*/
	OutputArray[10u] = (InputArray[2u] % 10u) + 0x30u;			 /*ge*/

	OutputArray[11u] = 0x2E;									 /* . */

	OutputArray[12u] = (InputArray[3u] / 100u) + 0x30u;          /*bai*/
	OutputArray[13u] = ((InputArray[3u] % 100u) / 10u) + 0x30u;  /*shi*/
	OutputArray[14u] = (InputArray[3u] % 10u) + 0x30u;			 /*ge*/

	memcpy(OutputData_15B, OutputArray, 15u);

}


/*
@brief
@details
@para
@return
@note
*/

static uint8 lPtconfigDataConverter_Netmask(uint8* InputData, uint8* OutputData)
{


}

/*
@brief
@details
@para
@return
@note
*/

static uint8 lPtconfigDataConverter_Gateway(uint8* InputData, uint8* OutputData)
{


}


/*******************************************************************************************************
 *
 	 LLVAR
The field always begins with 闂佺偨鍎插Δ绌y闂佺偨鍎婚幏锟� whereby xy positions follow.
e.g.
F1 F2 01 23 45 67 89 01 23 45 67 89 01 23 (F1 F2 states that the following 12 bytes belong to this field)
F0 F3 01 23 45 (F0 F3 means 3 following bytes)


 	 LLLVAR
The field always begins with 闂佺偨鍎插Δ绌yFz闂佺偨鍎婚幏锟� whereby xyz positions follow.
e.g.
F0 F1 F2 01 23 45 67 89 01 23 45 67 89 01 23 (F0 F1 F2 states that the following 12 bytes belong to this field)
F0 F0 F3 01 23 45 (F0 F0 F3 means 3 following bytes)
 *
 * ******************************************************************************************************/
static uint8 lZvt_LLVAR2L_GetTotalLength_Std(uint8* LenF0, uint8* LenF1)
{
	return (((*LenF0&(0x0f))*10u) + (*LenF1&(0x0f)) + LLVAR_HEAD_LEN);
}

static uint8 lZvt_LLLVAR3L_GetTotalLength_Std(uint8* LenF0, uint8* LenF1, uint8* LenF2)
{
	return ( ((*LenF0&(0x0f))*100u) + ((*LenF1&(0x0f))*10u) + (*LenF2&(0x0f))  + LLLVAR_HEAD_LEN);
}

static uint16 lZvt_LLVAR2L_GetTotalLength_Ext(uint8* LenF0, uint8* LenF1)
{
	return (  (uint16)(  ((*LenF0&(0x0f))*10u) + (*LenF1&(0x0f)) ) + LLVAR_HEAD_LEN );
}


static uint16 lZvt_LLLVAR3L_GetTotalLength_Ext(uint8* LenF0, uint8* LenF1, uint8* LenF2)
{
	return ( (uint16)((*LenF0&(0x0f))*100u) + (uint16)((*LenF1&(0x0f))*10u) + (uint16)(*LenF2&(0x0f))  + LLLVAR_HEAD_LEN);
}





/*
@brief
@details	Analysis cmd 040F IntermediateStatusInformation
@para
@return
*/
static uint8 lZvt_Analysis_cmd040FStatusInformationRx(uint16 rxLength, uint8* rxBuff)
{
//	uint8 zvt_retvalue;


	if(0u == rxLength)
	{
		return ZVT_RET_N_OK;
	}

	cmd040FrxLength = rxLength;
	ui8StdFormatCmd040f_ByteCount = 0u;
	ui8StdFormatCmd040f_PollCount = 0u;


	memcpy(cmd040FSocketRxFrame, rxBuff, rxLength);

	if(cmd040FSocketRxFrame[2u] < ZVT_EXT_FORMAT_FLAG)					/*Stand Format*/
	{
		stdApduTotalLength = 0u;
		extractCmd040fStdData.formatStdExtFlag = StdZvtFormat;
		stdApduTotalLength = cmd040FrxLength - 3u;

	}
	else if(ZVT_EXT_FORMAT_FLAG == cmd040FSocketRxFrame[2u])			/*Extended Format*/
	{
		extApduTotalLength = 0u;
		extractCmd040fExtData.formatStdExtFlag = ExtZvtFormat;
		extApduTotalLength = cmd040FrxLength - 5u;

	}
	else
	{;}
	/***********************************************************************************************************************/
	/**************************************Extended Apdu Format*************************************************************/
	/***********************************************************************************************************************/

	if(ExtZvtFormat == extractCmd040fExtData.formatStdExtFlag)
	{

		{
			ui16ExtFormatCmd040f_ByteCount = 5u;

			do
			{
				if(ui16ExtFormatCmd040f_ByteCount < extApduTotalLength)
				{
					if(Bitmap27_ResultCode_2B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						if((TRUE == Zvt_ReadAsw.AGunStart_flg)\
						 ||(TRUE == Zvt_ReadAsw.BGunStart_flg))
						{
							CCV_PreAuthData.ErrCode = cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1];
						}

						if((TRUE == Zvt_ReadAsw.AGunStop_flg)\
						 ||(TRUE == Zvt_ReadAsw.BGunStop_flg))
						{
							UserStopCreditData.ErrCode = cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1];
						}

						if((TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)\
						 ||(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg))

						{
							CCV_PartReverData.ErrCode = cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1];
						}

						ui16ExtFormatCmd040f_ByteCount += 2u;
					}
				}


				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)					/* [5]	*/
				{
					if(Bitmap29_TID_5B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.TerminalID0x29_5B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1], 4u);

						ui16ExtFormatCmd040f_ByteCount+= 5u;							/* 9 */
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap04_AmounMinorCurrencyUnits_7B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.Amount0x04_7B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1], 6u);
						ui16ExtFormatCmd040f_ByteCount+= 7u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0B_TraceNumber_4B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.Tracenumber0x0B_4B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1], 3u);
						ui16ExtFormatCmd040f_ByteCount+= 4u;
					}
				}


				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0C_TimeBCD_4B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.TimeBCD0x0c_4B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 3u);

						ui16ExtFormatCmd040f_ByteCount+= 4u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0D_DateBCD_3B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.DateBCD0x0d_3B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);

						ui16ExtFormatCmd040f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0E_ExpiryDateBCD_3B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.ExpiryDateBCD0x0e_3B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);

						ui16ExtFormatCmd040f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap17_CardSequenceNumberBCD_3B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.CardSequenceNumberBCD0x17_3B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);

						ui16ExtFormatCmd040f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap19_StatusBytePaymentTypeCardType_Bin_2B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.StatusBytePaymentTypeCardType0x19_2B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 1u);

						ui16ExtFormatCmd040f_ByteCount+= 2u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2A_VU_Number_ASCII_16B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.VU_Number0x2a_16B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 15u);

						ui16ExtFormatCmd040f_ByteCount+= 16u;
					}
				}


				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap37_ReceiptNumberReversal_4B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.ReceiptNumberReversal0x37_4B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 3u);

						ui16ExtFormatCmd040f_ByteCount+= 4u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap49_network_provider_card_type_ID_3B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						ui16ExtFormatCmd040f_ByteCount += 3u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap87_ReceiptNumber_3B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(extractCmd040fExtData.Receiptnumber0x87_3B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);
//						memcpy(debug_extractCmd040fExtData.Receiptnumber0x87_3B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);

						/**----------------------------------------------------------------------------------------------------------**/

						if(Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)
						{
							if((StartPreAuth == Zvt_ReadAsw.AGunStart_flg)\
								||(StartPreAuth == Zvt_ReadAsw.BGunStart_flg))
							{
								memcpy(CCV_PreAuthData.getCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);
								CCV_PreAuthData.getReceiptNo = TRUE;
							}

						}



						if((StartPartialReversal == Zvt_ReadAsw.AGunStop_flg)\
							||(StartPartialReversal == Zvt_ReadAsw.BGunStop_flg))
						{
							memcpy(UserStopCreditData.rxCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);
						}


						if(ReversalSend0623_OK == CCV_PartReverData.ReversalStep)
						{
							if((StartPartialReversal == Zvt_ReadAsw.CCU1_AutoFinish_flg)\
								||(StartPartialReversal == Zvt_ReadAsw.CCU2_AutoFinish_flg))
							{
								memcpy(CCV_PartReverData.rxCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 2u);
							}
						}


					/**----------------------------------------------------------------------------------------------------------------**/
						ui16ExtFormatCmd040f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap8A_CardType_Bin_2B == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
//						memcpy(&extractCmd040fExtData.CardType_Bin0x8a_2B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], 1u);

						ui16ExtFormatCmd040f_ByteCount+= 2u;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap8B_CardName_LL_Var == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 2u]);

//						memcpy(extractCmd040fExtData.CardName_LL_Var0x8b_11B, &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1], (BitmapVarL_TotalLen_Ext - 1u) );

						ui16ExtFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap22_LL_Var_PAN_EF_ID_BCD == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u]);

						ui16ExtFormatCmd040f_ByteCount+= BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap23_LL_Var_Track_2_data == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u]);

						ui16ExtFormatCmd040f_ByteCount+= BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap24_LLL_Var_Track_3_data == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u],\
																					&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 3u]);

						ui16ExtFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2D_LL_Var_Track_1_data == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u]);

						ui16ExtFormatCmd040f_ByteCount+= BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2E_LLL_Var_Synchronous_Chip_Data == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u],\
																					&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 3u]);

						ui16ExtFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap3C_LLL_Var_Additional_Data == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u],\
																					&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 3u]);

						ui16ExtFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{
					if(Bitmap60_LLL_Var_Individual_totals == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 1u],\
														 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 2u],\
																					&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount+ 3u]);

						ui16ExtFormatCmd040f_ByteCount+= BitmapVarL_TotalLen_Ext;
					}
				}


				/*the last bitmap in the commands*/
				if(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength)
				{

					if(Bitmap06_TLVContainer == cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount])
					{
						/**--------------------------------------------------------------------------------------------------------------------------**/
								if(0u == debugFlagList.debugFlag3)
								{
									if((extApduTotalLength + 6u) > ui16ExtFormatCmd040f_ByteCount)
									{
											if((Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)\
											 ||(Waitfor_0622SID == CCV_PreAuthData.PreAuthStep))
											{
												memcpy(CCV_PreAuthData.Bitmap06Get141F_Backup,\
														&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1],\
														(extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u));

												CCV_PreAuthData.Bitmap06Length = extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u;  		/*shift*/
												break;
											}

											else if(Arrived_UserSID == UserStopCreditData.UserStopStep)
											{
												memcpy(UserStopCreditData.Bitmap06Get141F_Backup,\
														&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1],\
														(extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u));

												UserStopCreditData.Bitmap06Length = extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u;  		/*shift*/
												break;
											}

											else if((MifareSend06C0_OK == CCV_MifareData.MifareCardStep)\
												  ||(Waitfor_RfidUID == UserStopCreditData.UserStopStep))
											{
												memcpy(CCV_MifareData.Bitmap06Get4C0A_Backup,\
														&cmd040FSocketRxFrame[ui16ExtFormatCmd040f_ByteCount + 1],\
														(extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u));

												CCV_MifareData.Bitmap06Length = extApduTotalLength - ui16ExtFormatCmd040f_ByteCount + 6u;  		/*shift*/
												break;
											}

											else
											{
												break;
											}
									}
									else
									{
										break;
									}
								}

						/**--------------------------------------------------------------------------------------------------------------------------**/
						if(3u == debugFlagList.debugFlag3)
						{
							if((Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)\
							 ||(Waitfor_0622SID == CCV_PreAuthData.PreAuthStep))
							{
								if((5 + extApduTotalLength - 39u) > 0u)
								{
									for(Cmd040fGiveSIDto0622_Loop =5 +  extApduTotalLength - 40u;\
									Cmd040fGiveSIDto0622_Loop > ui16ExtFormatCmd040f_ByteCount;\
									Cmd040fGiveSIDto0622_Loop--)
									{
										if((0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 1u])\
										 &&(0x14 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 2u])\
										 &&(0x20 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 3u])\
										 &&(0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 36u])\
										 &&(0x15 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 37u]))
										{
											memcpy(CCV_PreAuthData.SID_0x1F14_32B, &cmd040FSocketRxFrame[Cmd040fGiveSIDto0622_Loop + ui16ExtFormatCmd040f_ByteCount + 4], PT_SID_LEN );
											CCV_PreAuthData.getSID = TRUE;

											break;
										}
									}

								}

							}

						}

						/**--------------------------------------------------------------------------------------------------------------------------**/
						if(5u == debugFlagList.debugFlag3)
						{
							if((Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)\
							 ||(Waitfor_0622SID == CCV_PreAuthData.PreAuthStep))
							{
								if((extApduTotalLength - 40u) > ui16ExtFormatCmd040f_ByteCount)
								{
									for(Cmd040fGiveSIDto0622_Loop = 0u;\
									Cmd040fGiveSIDto0622_Loop < (extApduTotalLength - 34u);\
									Cmd040fGiveSIDto0622_Loop++)
									{
										if((0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 1u])\
										 &&(0x14 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 2u])\
										 &&(0x20 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 3u])\
										 &&(0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 36u])\
										 &&(0x15 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 37u]))
										{
											memcpy(CCV_PreAuthData.SID_0x1F14_32B, &cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + 4], PT_SID_LEN );
											CCV_PreAuthData.getSID = TRUE;

											break;
										}
									}

								}
								else
								{	break;	}

							}

						}
						/**--------------------------------------------------------------------------------------------------------------------------**/
						if(5u == debugFlagList.debugFlag15)
						{
							if(Arrived_UserSID == UserStopCreditData.UserStopStep)
							{
								if((extApduTotalLength - 40u) > ui16ExtFormatCmd040f_ByteCount)
								{
									for(Cmd040fGiveSIDto06C0_Loop = 0u;\
									    Cmd040fGiveSIDto06C0_Loop < (extApduTotalLength - ui16ExtFormatCmd040f_ByteCount -40u);\
									    Cmd040fGiveSIDto06C0_Loop++)
									{
										if((0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 1u])\
										 &&(0x14 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 2u])\
										 &&(0x20 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 3u])\
										 &&(0x1F == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 36u])\
										 &&(0x15 == cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 37u]))
										{
											memcpy(UserStopCreditData.SID_0x1F14_32B, &cmd040FSocketRxFrame[Cmd040fGiveSIDto06C0_Loop + ui16ExtFormatCmd040f_ByteCount + 4], PT_SID_LEN );
											UserStopCreditData.getSID = TRUE;

											break;
										}
									}

								}
								else
								{	break;	}

							}

						}


						/**--------------------------------------------------------------------------------------------------------------------------**/

						{	break;	}
					}
				}

				ui8ExtFormatCmd040f_PollCount++;
				/*In case of receiving Error Frame*/
				if(ui8ExtFormatCmd040f_PollCount >= CMDTAG_POLL_MAX_TIMES)
				{
					ui8ExtFormatCmd040f_PollCountTemp = ui8ExtFormatCmd040f_PollCount;
					ui8ExtFormatCmd040f_PollCount = 0u;
					break;
				}

			  }while(ui16ExtFormatCmd040f_ByteCount< extApduTotalLength);

			memset(cmd040FSocketRxFrame, 0u, 1000u);


		}


	}
	/***********************************************************************************************************************/
	/******************************************Stand Apdu Format************************************************************/
	/***********************************************************************************************************************/
	if(StdZvtFormat == extractCmd040fStdData.formatStdExtFlag)
	{
//			formatStdExtFlag = NonZvtFormat;

			/** APDU data**/

		ui8StdFormatCmd040f_ByteCount = 3u;

		do
		{
			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap27_ResultCode_2B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(&extractCmd040fStdData.Resultcode0x27_2B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 1u);

//					if(UserSend0623_OK == UserStopCreditData.UserStopStep)
					{
						if((TRUE == Zvt_ReadAsw.AGunStop_flg)\
						 ||(TRUE == Zvt_ReadAsw.BGunStop_flg))
						{
							UserStopCreditData.ErrCode = cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1];
						}
					}

//					if(ReversalSend0623_OK == CCV_PartReverData.ReversalStep)
					{
						if((TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)\
						 ||(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg))

						{
							CCV_PartReverData.ErrCode = cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1];
						}
					}

					ui8StdFormatCmd040f_ByteCount += 2u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap29_TID_5B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.TerminalID0x29_5B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 4u);

					ui8StdFormatCmd040f_ByteCount += 5u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap04_AmounMinorCurrencyUnits_7B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.Amount0x04_7B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 6u);
					ui8StdFormatCmd040f_ByteCount += 7u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap0B_TraceNumber_4B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.Tracenumber0x0B_4B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 3u);
					ui8StdFormatCmd040f_ByteCount += 4u;
				}
			}



			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap0C_TimeBCD_4B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.TimeBCD0x0c_4B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 3u);

					ui8StdFormatCmd040f_ByteCount += 4u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap0D_DateBCD_3B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.DateBCD0x0d_3B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);

					ui8StdFormatCmd040f_ByteCount += 3u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap0E_ExpiryDateBCD_3B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.ExpiryDateBCD0x0e_3B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);

					ui8StdFormatCmd040f_ByteCount += 3u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap17_CardSequenceNumberBCD_3B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.CardSequenceNumberBCD0x17_3B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);

					ui8StdFormatCmd040f_ByteCount += 3u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap19_StatusBytePaymentTypeCardType_Bin_2B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.StatusBytePaymentTypeCardType0x19_2B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 1u);

					ui8StdFormatCmd040f_ByteCount += 2u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap2A_VU_Number_ASCII_16B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.VU_Number0x2a_16B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 15u);

					ui8StdFormatCmd040f_ByteCount += 16u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap37_ReceiptNumberReversal_4B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					ui8StdFormatCmd040f_ByteCount += 4u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap49_network_provider_card_type_ID_3B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					ui8StdFormatCmd040f_ByteCount += 3u;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap87_ReceiptNumber_3B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(extractCmd040fStdData.Receiptnumber0x87_3B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);

					if(Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)
					{
						if((StartPreAuth == Zvt_ReadAsw.AGunStart_flg)\
							||(StartPreAuth == Zvt_ReadAsw.BGunStart_flg))
						{
							memcpy(CCV_PreAuthData.getCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);
							CCV_PreAuthData.getReceiptNo = TRUE;
						}
					}

//					if((UserSend0623_OK == UserStopCreditData.UserStopStep)\
//					 ||(UserSend0623_N_OK == UserStopCreditData.UserStopStep))
					{
						if((StartPartialReversal == Zvt_ReadAsw.AGunStop_flg)\
							||(StartPartialReversal == Zvt_ReadAsw.BGunStop_flg))
						{
							memcpy(UserStopCreditData.rxCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);
						}
					}

					if(ReversalSend0623_OK == CCV_PartReverData.ReversalStep)
					{
						if((StartPartialReversal == Zvt_ReadAsw.CCU1_AutoFinish_flg)\
							||(StartPartialReversal == Zvt_ReadAsw.CCU2_AutoFinish_flg))
						{
							memcpy(CCV_PartReverData.rxCmd040fReceiptNumber0x87, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 2u);
						}
					}

					ui8StdFormatCmd040f_ByteCount += 3u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap8A_CardType_Bin_2B == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{
//					memcpy(&extractCmd040fStdData.CardType_Bin0x8a_2B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], 1u);

					ui8StdFormatCmd040f_ByteCount +=2u;

				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{

				if(Bitmap8B_CardName_LL_Var == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLVAR2L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u]);

//					memcpy(extractCmd040fStdData.CardName_LL_Var0x8b_11B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1], (BitmapVarL_TotalLen_Std - 1u));

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap22_LL_Var_PAN_EF_ID_BCD == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLVAR2L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap23_LL_Var_Track_2_data == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLVAR2L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap24_LLL_Var_Track_3_data == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLLVAR3L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u],\
																				&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 3u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap2D_LL_Var_Track_1_data == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLVAR2L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	   &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap2E_LLL_Var_Synchronous_Chip_Data == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLLVAR3L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u],\
																				&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 3u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap3C_LLL_Var_Additional_Data == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLLVAR3L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 	 	 	 	 	 	 	&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u],\
																				&cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 3u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}


			if(ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)
			{
				if(Bitmap60_LLL_Var_Individual_totals == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					BitmapVarL_TotalLen_Std = lZvt_LLLVAR3L_GetTotalLength_Std( &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u],\
													 &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 2u],\
													 &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 3u]);

					ui8StdFormatCmd040f_ByteCount += BitmapVarL_TotalLen_Std;
				}
			}

			/*the last bitmap in the commands*/
			if(ui8StdFormatCmd040f_ByteCount< extApduTotalLength)
			{
				if(Bitmap06_TLVContainer == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount])
				{

					ui8StdFormatCmd040f_ByteCount+= cmd060FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 1u];

					{
						if(PrimitiveTag_UID_0x4c == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 4u])
						{
//							memcpy(extractCmd040fStdData.SID_0x1F14_32B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 6], PT_SID_LEN );

						}
						/**----------------------------------------------------------------------------------------------**/

						if(	PrimitiveTag_UID_0x4c == cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 4u])
						{
							if(PreAuthorize_OK == CCV_PreAuthData.PreAuthStep)
							{
								memcpy(CCV_PreAuthData.SID_0x1F14_32B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 6], PT_SID_LEN );
								CCV_PreAuthData.getSID = TRUE;
							}

							if(Arrived_UserSID == UserStopCreditData.UserStopStep)
							{
								memcpy(UserStopCreditData.SID_0x1F14_32B, &cmd040FSocketRxFrame[ui8StdFormatCmd040f_ByteCount + 6], PT_SID_LEN );
								UserStopCreditData.getSID = TRUE;
							}
						}

						/**----------------------------------------------------------------------------------------------**/

						break;
					}
				}

			}


			ui8StdFormatCmd040f_PollCount++;
			/*In case of receiving Error Frame*/
			if(ui8StdFormatCmd040f_PollCount >= CMDTAG_POLL_MAX_TIMES)
			{
				ui8StdFormatCmd040f_PollCountTemp = ui8StdFormatCmd040f_PollCount;
				ui8StdFormatCmd040f_PollCount = 0u;
				break;
			}

		  }while((ui8StdFormatCmd040f_ByteCount < stdApduTotalLength)||(ui8StdFormatCmd040f_PollCount <= CMD040F_POLL_MAX_TIMES));

		memset(cmd040FSocketRxFrame, 0u, 1000u);



	}

	return(ZVT_RET_OK);
}

/*
@brief
@details	Analysis cmd 04FF IntermediateStatusInformation,	page125/199
@para
@return
*/
static uint8 lZvt_Analysis_cmd04FFIntermediateStatusInformationRx(uint16 rxLength, uint8* rxBuff)
{
	uint8 zvt_retvalue;

	if(0u == rxLength)
	{
		return ZVT_RET_N_OK;
	}

	cmd04ffRxLength = rxLength;
	ui8StdFormatCmd04ff_ByteCount = 0u;
	ui8StdFormatCmd04ff_PollCount = 0u;


	memcpy(cmd04FFSocketRxFrame, rxBuff, rxLength);

	if(cmd04FFSocketRxFrame[2u] < ZVT_EXT_FORMAT_FLAG)					/*Stand Format*/
	{
		stdApduTotalLength = 0u;
		cmd04ffRxDtaBlockLength = cmd04FFSocketRxFrame[2u];
		formatStdExtFlag = StdZvtFormat;
		stdApduTotalLength = cmd04ffRxDtaBlockLength + ZVT_HEAD_LEN_STD;

	}
	else if(ZVT_EXT_FORMAT_FLAG == cmd04FFSocketRxFrame[2u])			/*Extended Format*/
	{
		extApduTotalLength = 0u;
		cmd04ffRxDtaBlockLength = ((uint16)cmd04FFSocketRxFrame[3u]) + (((uint16)cmd04FFSocketRxFrame[4u]) << 8u);
		formatStdExtFlag = ExtZvtFormat;
		extApduTotalLength = cmd04ffRxDtaBlockLength + ZVT_HEAD_LEN_EXT;

	}
	else
	{;}

	/***********************************************************************************************************************/
	/******************************************Stand Apdu Format************************************************************/
	/***********************************************************************************************************************/
	if(StdZvtFormat == formatStdExtFlag)
	{
		cmd04ffPayload.cmd04ff_intermediate_status 	= cmd04FFSocketRxFrame[3u];
		cmd04ffPayload.cmd04ff_timeout 				= cmd04FFSocketRxFrame[4u];

		ui8StdFormatCmd04ff_ByteCount				= 5u;


		if(Please_wait0x17 == cmd04ffPayload.cmd04ff_intermediate_status)
		{

		}


		if(PT_Detected_Customer_Card_Insertion0x68 == cmd04ffPayload.cmd04ff_intermediate_status)
		{

		}


		if(Approved_Please_fill_up0x1b == cmd04ffPayload.cmd04ff_intermediate_status)
		{
			/*Maximalbetrag*/

		}

		do{
			if(Bitmap06_TLVContainer == cmd04FFSocketRxFrame[ui8StdFormatCmd04ff_ByteCount])
			{
				if(ui8StdFormatCmd04ff_ByteCount< stdApduTotalLength)
				{
					ui8StdFormatCmd04ff_ByteCount+= cmd04FFSocketRxFrame[ui8StdFormatCmd04ff_ByteCount + 1u];

					{
						break;
					}

				}

			}


			ui8StdFormatCmd04ff_PollCount++;
			/*In case of receiving Error Frame*/
			if(ui8StdFormatCmd04ff_PollCount >= CMDTAG_POLL_MAX_TIMES)
			{
				break;
			}

		}while(ui8StdFormatCmd04ff_ByteCount< stdApduTotalLength);

	}





	/***********************************************************************************************************************/
	/**************************************Extended Apdu Format*************************************************************/
	/***********************************************************************************************************************/

	if(ExtZvtFormat == formatStdExtFlag)
	{
		cmd04ffPayload.cmd04ff_intermediate_status 	= cmd04FFSocketRxFrame[5u];
		cmd04ffPayload.cmd04ff_timeout 				= cmd04FFSocketRxFrame[6u];
		ui16ExtFormatCmd04ff_ByteCount				= 7u;

		if(Approved_Please_fill_up0x1b == cmd04ffPayload.cmd04ff_intermediate_status)
		{
			/*Maximalbetrag*/

		}

		do{
			if(Bitmap06_TLVContainer == cmd04FFSocketRxFrame[ui16ExtFormatCmd04ff_ByteCount])
			{
				if(ui16ExtFormatCmd04ff_ByteCount< extApduTotalLength)
				{
					ui16ExtFormatCmd04ff_ByteCount+= cmd04FFSocketRxFrame[ui16ExtFormatCmd04ff_ByteCount + 1u];

					{
						break;
					}

				}

			}

			ui8ExtFormatCmd04ff_PollCount++;
			/*In case of receiving Error Frame*/
			if(ui8ExtFormatCmd04ff_PollCount >= CMDTAG_POLL_MAX_TIMES)
			{
				break;
			}

		}while(ui16ExtFormatCmd04ff_ByteCount< extApduTotalLength);


	}


	return(ZVT_RET_OK);
}


/*
@brief
@details	Analysis cmd 060F	Completion
@para
@return
*/
static uint8 lZvt_Analysis_cmd060FCompletionRx(uint16 rxLength, uint8* rxBuff)
{

//	uint8 zvt_retvalue;

	if(0u == rxLength)
	{
		return ZVT_RET_N_OK;
	}

	cmd060fRxLength = rxLength;
	ui8StdFormatCmd060f_ByteCount = 0u;
	ui8StdFormatCmd060f_PollCount = 0u;


	memcpy(cmd060FSocketRxFrame, rxBuff, rxLength);

	if(cmd060FSocketRxFrame[2u] < ZVT_EXT_FORMAT_FLAG)					/*Stand Format*/
	{
		stdApduTotalLength = 0u;
		cmd060fRxDtaBlockLength = cmd060FSocketRxFrame[2u];
		formatStdExtFlag = StdZvtFormat;
		stdApduTotalLength = cmd060fRxDtaBlockLength + ZVT_HEAD_LEN_STD;

	}
	else if(ZVT_EXT_FORMAT_FLAG == cmd060FSocketRxFrame[2u])			/*Extended Format*/
	{
		extApduTotalLength = 0u;
		cmd060fRxDtaBlockLength = ((uint16)cmd060FSocketRxFrame[3u]) + (((uint16)cmd060FSocketRxFrame[4u]) << 8u);
		formatStdExtFlag = ExtZvtFormat;
		extApduTotalLength = cmd060fRxDtaBlockLength + ZVT_HEAD_LEN_EXT;

	}
	else
	{;}


	/***********************************************************************************************************************/
	/**************************************Extended Apdu Format*************************************************************/
	/***********************************************************************************************************************/

	if(ExtZvtFormat == formatStdExtFlag)
	{
		{
			ui16ExtFormatCmd060f_ByteCount = 5u;

			do
			{

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap27_ResultCode_2B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{
						extractCmd060fExtData.Resultcode0x27_2B = cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1];
						PtErrCode.PtCmd060fErrCode = cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1];

						ui16ExtFormatCmd060f_ByteCount += 2u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap29_TID_5B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{
						memcpy(extractCmd060fExtData.TerminalID0x29_5B, &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1], 4u);

						/**--------------------------------------------------------------------------------------------------------------------**/
						if(Cmd060fArrived_OK == PtConfigFactory0813Data.Factory0813_Waitfor060f)
						{
							memcpy(PtConfigFactory0813Data.Factory0813_getCmd060fTID, &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1], 4u);
						}

						if(Cmd060fArrived_OK == PtConfigUser0813Data.User0813_Waitfor060f)
						{
							memcpy(PtConfigUser0813Data.User0813_getCmd060fTID, &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1], 4u);
						}

						if((WaitforTID == PtConfig0813FactoryData.Factory0813Step)&&(Factory0813 == PtConfigData.ConfigStep))
						{
							memcpy(PtConfig0813FactoryData.Factory0813_getCmd060fTID, &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1], 4u);
						}

						if((2u == PtConfig0813UserData.User0813Step)&&(User0813 == PtConfigData.ConfigStep))
						{
							memcpy(PtConfig0813UserData.User0813_getCmd060fTID, &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1], 4u);
						}

						/**--------------------------------------------------------------------------------------------------------------------**/
						ui16ExtFormatCmd060f_ByteCount+= 5u;							/* 9 */
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap04_AmounMinorCurrencyUnits_7B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 7u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0B_TraceNumber_4B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 4u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0C_TimeBCD_4B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 4u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0D_DateBCD_3B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap0E_ExpiryDateBCD_3B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 3u;
					}

				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap17_CardSequenceNumberBCD_3B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 3u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap19_StatusBytePaymentTypeCardType_Bin_2B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 2u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2A_VU_Number_ASCII_16B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 16u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap37_ReceiptNumberReversal_4B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 4u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap49_network_provider_card_type_ID_3B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount += 3u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap87_ReceiptNumber_3B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 3u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap8A_CardType_Bin_2B == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= 2u;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap8B_CardName_LL_Var == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
										{
											BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
																			 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u]);


											ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
										}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap22_LL_Var_PAN_EF_ID_BCD == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u]);
						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap23_LL_Var_Track_2_data == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u]);
						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap24_LLL_Var_Track_3_data == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 3u]);
						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2D_LL_Var_Track_1_data == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u]);

						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap2E_LLL_Var_Synchronous_Chip_Data == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 3u]);
						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap3C_LLL_Var_Additional_Data == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 3u]);
						ui16ExtFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{

				}

				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap60_LLL_Var_Individual_totals == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Ext = lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 1u],\
														 &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 2u],\
														 &cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount+ 3u]);

						ui16ExtFormatCmd060f_ByteCount+= BitmapVarL_TotalLen_Ext;
					}
				}

				/*the last bitmap in the commands*/
				if(ui16ExtFormatCmd060f_ByteCount< extApduTotalLength)
				{
					if(Bitmap06_TLVContainer == cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount])
					{

						ui16ExtFormatCmd060f_ByteCount+= cmd060FSocketRxFrame[ui16ExtFormatCmd060f_ByteCount + 1u];

						{
							break;
						}
					}

				}

				ui8ExtFormatCmd060f_PollCount++;
				/*In case of receiving Error Frame*/
				if(ui8ExtFormatCmd060f_PollCount >= CMD060F_POLL_MAX_TIMES)
				{
					break;
				}

			 }while(ui16ExtFormatCmd060f_ByteCount < extApduTotalLength);


		}

	}


	/***********************************************************************************************************************/
	/******************************************Stand Apdu Format************************************************************/
	/***********************************************************************************************************************/
	if(StdZvtFormat == formatStdExtFlag)
	{
		{
			ui8StdFormatCmd060f_ByteCount = 3u;

			do
			{
				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap27_ResultCode_2B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{
						extractCmd060fStdData.Resultcode0x27_2B = cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1];
						PtErrCode.PtCmd060fErrCode = cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1];

						ui8StdFormatCmd060f_ByteCount += 2u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap29_TID_5B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{
						memcpy(extractCmd060fStdData.TerminalID0x29_5B, &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1], 4u);

						/**--------------------------------------------------------------------------------------------------------------------**/
						if(Cmd060fArrived_OK == PtConfigFactory0813Data.Factory0813_Waitfor060f)
						{
							memcpy(PtConfigFactory0813Data.Factory0813_getCmd060fTID, &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1], 4u);

						}

						if(Cmd060fArrived_OK == PtConfigUser0813Data.User0813_Waitfor060f)
						{
							memcpy(PtConfigUser0813Data.User0813_getCmd060fTID, &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1], 4u);
						}

						if((WaitforTID == PtConfig0813FactoryData.Factory0813Step)&&(Factory0813 == PtConfigData.ConfigStep))
						{
							memcpy(PtConfig0813FactoryData.Factory0813_getCmd060fTID, &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1], 4u);

						}

						if((2u == PtConfig0813UserData.User0813Step)&&(User0813 == PtConfigData.ConfigStep))
						{
							memcpy(PtConfig0813UserData.User0813_getCmd060fTID, &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1], 4u);
						}

						/**--------------------------------------------------------------------------------------------------------------------**/
						ui8StdFormatCmd060f_ByteCount+= 5u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap04_AmounMinorCurrencyUnits_7B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 7u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap0B_TraceNumber_4B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 4u;
					}
				}


				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap0C_TimeBCD_4B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 4u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap0D_DateBCD_3B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 3u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap0E_ExpiryDateBCD_3B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 3u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap17_CardSequenceNumberBCD_3B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 3u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap19_StatusBytePaymentTypeCardType_Bin_2B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 2u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap2A_VU_Number_ASCII_16B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 16u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap37_ReceiptNumberReversal_4B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 4u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap49_network_provider_card_type_ID_3B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount += 3u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap87_ReceiptNumber_3B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 3u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap8A_CardType_Bin_2B == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= 2u;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap8B_CardName_LL_Var == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
										{

											BitmapVarL_TotalLen_Std= lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
																			 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u]);
											ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
										}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap22_LL_Var_PAN_EF_ID_BCD == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap23_LL_Var_Track_2_data == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap24_LLL_Var_Track_3_data == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 3u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap2D_LL_Var_Track_1_data == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLVAR2L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	   &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap2E_LLL_Var_Synchronous_Chip_Data == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 3u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap3C_LLL_Var_Additional_Data == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std= lZvt_LLLVAR3L_GetTotalLength_Ext( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u],\
														 	 	 	 	 	 	 	&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 2u],\
																					&cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 3u]);
						ui8StdFormatCmd060f_ByteCount += BitmapVarL_TotalLen_Ext;
					}
				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{

				}

				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap60_LLL_Var_Individual_totals == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						BitmapVarL_TotalLen_Std = lZvt_LLLVAR3L_GetTotalLength_Std( &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 1u],\
														 &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 2u],\
														 &cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount+ 3u]);

						ui8StdFormatCmd060f_ByteCount+= BitmapVarL_TotalLen_Std;
					}
				}

				/*the last bitmap in the commands*/
				if(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength)
				{
					if(Bitmap06_TLVContainer == cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount])
					{

						ui8StdFormatCmd060f_ByteCount+= cmd060FSocketRxFrame[ui8StdFormatCmd060f_ByteCount + 1u];

						{
							break;
						}
					}

				}

				ui8StdFormatCmd060f_PollCount++;
				/*In case of receiving Error Frame*/
				if(ui8StdFormatCmd060f_PollCount >= CMD060F_POLL_MAX_TIMES)
				{
					break;
				}

			 }while(ui8StdFormatCmd060f_ByteCount< stdApduTotalLength);

		}

	}


	return(ZVT_RET_OK);
}


/*
@brief
@details	Analysis cmd 061E IntermediateStatusInformation,	page122/199
@para
@return
*/
static uint8 lZvt_Analysis_cmd061EAbortRx(uint16 rxLength, uint8* rxBuff)
{


//	uint8 zvt_retvalue;

	if(0u == rxLength)
	{
		return ZVT_RET_N_OK;
	}


	cmd061eRxLength = rxLength;
	ui8StdFormatCmd061e_ByteCount = 0u;
	ui8StdFormatCmd061e_PollCount = 0u;


	memcpy(cmd061ESocketRxFrame, rxBuff, rxLength);

	if(cmd061ESocketRxFrame[2u] < ZVT_EXT_FORMAT_FLAG)					/*Stand Format*/
	{
		stdApduTotalLength = 0u;
		cmd061eRxDtaBlockLength = cmd061ESocketRxFrame[2u];
		formatStdExtFlag = StdZvtFormat;
		stdApduTotalLength = cmd061eRxDtaBlockLength + ZVT_HEAD_LEN_STD;

	}
	else if(ZVT_EXT_FORMAT_FLAG == cmd061ESocketRxFrame[2u])				/*Extended Format*/
	{
		extApduTotalLength = 0u;
		cmd061eRxDtaBlockLength = ((uint16)cmd061ESocketRxFrame[3u]) + (((uint16)cmd061ESocketRxFrame[4u]) << 8u);
		formatStdExtFlag = ExtZvtFormat;
		extApduTotalLength = cmd061eRxDtaBlockLength + ZVT_HEAD_LEN_EXT;

	}
	else
	{;}

	/***********************************************************************************************************************/
	/******************************************Stand Apdu Format************************************************************/
	/***********************************************************************************************************************/
	if(StdZvtFormat == formatStdExtFlag)
	{
		cmd061ePayload.cmd061e_Result_Code 	= cmd061ESocketRxFrame[3u];
		PtErrCode.PtCmd061eErrCode = cmd061ESocketRxFrame[3u];

		/**---------------------------------------------------------------------------------------------------------**/

		if((1u == PtInit0693Data.Init0693Step)\
		 &&(User0693 == PtConfigData.ConfigStep))
		{
			PtInit0693Data.Init0693Get061eErrCode = cmd061ESocketRxFrame[3u];
		}

		if((1u == PtDiag0670EmvData.Diag0670EmvStep)\
		 &&(User0670emv == PtConfigData.ConfigStep))
		{
			PtDiag0670EmvData.Diag0670EmvGet061eErrCode = cmd061ESocketRxFrame[3u];
		}


		/**---------------------------------------------------------------------------------------------------------**/

		ui8StdFormatCmd061e_ByteCount				= 4u;

		if(reversal_not_possible_0xB5 == cmd061ePayload.cmd061e_Result_Code)
		{

		}

		if(error_pre_authorisation_0xB8 == cmd061ePayload.cmd061e_Result_Code)
		{
			/*Maximalbetrag*/

		}

		do{
			if(Bitmap06_TLVContainer == cmd061ESocketRxFrame[ui8StdFormatCmd061e_ByteCount])
			{
				if(ui8StdFormatCmd061e_ByteCount< stdApduTotalLength)
				{
					ui8StdFormatCmd061e_ByteCount+= cmd061ESocketRxFrame[ui8StdFormatCmd061e_ByteCount + 1u];

					{
						break;
					}

				}

			}


			ui8StdFormatCmd061e_PollCount++;
			/*In case of receiving Error Frame*/
			if(ui8StdFormatCmd061e_PollCount >= CMDTAG_POLL_MAX_TIMES)
			{
				break;
			}

		}while(ui8StdFormatCmd061e_ByteCount< stdApduTotalLength);

	}





	/***********************************************************************************************************************/
	/**************************************Extended Apdu Format*************************************************************/
	/***********************************************************************************************************************/

	if(ExtZvtFormat == formatStdExtFlag)
	{
		cmd061ePayload.cmd061e_Result_Code 	= cmd061ESocketRxFrame[5u];
		PtErrCode.PtCmd061eErrCode = cmd061ESocketRxFrame[5u];

		ui16ExtFormatCmd061e_ByteCount				= 6u;

		if(reversal_not_possible_0xB5 == cmd061ePayload.cmd061e_Result_Code)
		{

			ZvtCom_Write.CCU1_Set0623SettleAccount_flg = FALSE;

		}

		if(error_pre_authorisation_0xB8 == cmd061ePayload.cmd061e_Result_Code)
		{
			/*Maximalbetrag*/
			ZvtCom_Write.CCU1_Set0622PreAut_flg = FALSE;

		}

		do{
			if(Bitmap06_TLVContainer == cmd061ESocketRxFrame[ui16ExtFormatCmd061e_ByteCount])
			{
				if(ui16ExtFormatCmd061e_ByteCount< extApduTotalLength)
				{
					ui16ExtFormatCmd061e_ByteCount+= cmd061ESocketRxFrame[ui16ExtFormatCmd061e_ByteCount + 1u];

					{
						break;
					}

				}

			}

			ui8ExtFormatCmd061e_PollCount++;
			/*In case of receiving Error Frame*/
			if(ui8ExtFormatCmd061e_PollCount >= CMDTAG_POLL_MAX_TIMES)
			{
				break;
			}

		}while(ui16ExtFormatCmd061e_ByteCount< extApduTotalLength);


	}


	return(ZVT_RET_OK);
}


/*
@brief
@details	Analysis cmd	06D3	PrintTextBlock
@para
@return
*/
static uint8 lZvt_Analysis_cmd06D3PrintTextBlockRx(void)
{
	uint8 zvt_retvalue;


	return(ZVT_RET_OK);
}


/*
@brief
@details	Analysis cmd	8000	PositiveAcknowledgement
@para
@return
*/
static uint8 lZvt_Analysis_cmd8000PositiveAcknowledgementRx(uint8* rxBuff)
{

	memcpy(cmd8000SocketRxFrame, rxBuff, 3u);

	if(0u == cmd8000SocketRxFrame[2u])
	{
		PtInitState.PtResp0800Flag = PtRespCmd0800_OK;

		PtCmdFlag.PtResp8000Flag = PtRespCmd8000_OK;

	}
	else
	{
		PtInitState.PtResp0800Flag = PtRespCmd0800_N_OK;

		PtCmdFlag.PtResp8000Flag = PtRespCmd8000_N_OK;
	}

		return(no_error);
}


/*
@brief
@details	Analysis cmd	8400	PositiveAcknowledgement
@para
@return
*/
static uint8 lZvt_Analysis_cmd8400PositiveAcknowledgementRx(uint16 rxLength, uint8* rxBuff)
{

	memcpy(cmd8400SocketRxFrame, rxBuff, rxLength);

	PtErrCode.PtCmd8400ErrCode = cmd8400SocketRxFrame[2u];

	if(0u == cmd8400SocketRxFrame[2u])
	{
		PtCmdFlag.PtResp8400Flag = PtRespCmd8400_OK;
	}
	else
	{
		PtCmdFlag.PtResp8400Flag = PtRespCmd8400_N_OK;
	}

	return(no_error);
}

/*
@brief
@details	Analysis cmd	8000	PositiveAcknowledgement
@para
@return
*/
 uint8 Zvt_PtCheckReceive8000Ack(void)
 {
		if((0x80 == cmd8000SocketRxFrame[0])\
		 &&(0x00 == cmd8000SocketRxFrame[1])\
		 &&(0x00 == cmd8000SocketRxFrame[2]))
		{
			memset(cmd8000SocketRxFrame, 0u, 3u);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
 }


/*
@brief
@details
@para
@return
*/
uint8 Zvt_Pt142IpStatusEnquiry0501(void)
{
	uint8 zvt_retvalue;
	uint8 statusEnquiry_0501Data[] = {0x05, 0x01, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00};

	zvt_retvalue = Zvt_Transmit2Pt1_42(ZVT_REMOTE_PORT, statusEnquiry_0501Data, sizeof(statusEnquiry_0501Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtUserIpStatusEnquiry0501(void)
{
	uint8 zvt_retvalue;
	uint8 statusEnquiry_0501Data[] = {0x05, 0x01, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, statusEnquiry_0501Data, sizeof(statusEnquiry_0501Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details  Registration password, CC, list of commands
@para
@return
*/
uint8 Zvt_PtFactoryRegistration0600(void)
{
	uint8 zvt_retvalue;

	uint8 registration_0600Data[] ={0x06, 0x00, 0x3a, 0x01, 0x02, 0x03, 0x8e, 0x09, 0x78, 0x06, 0x32, 0x40, 0x02, 0xb0, 0x80, 0x26, 0x2c, 0x0a,\
								    0x02, 0x04, 0x0f, 0x0a, 0x02, 0x04, 0xff, 0x0a, 0x02, 0x06, 0x0f, 0x0a, 0x02, 0x06, 0x1e, 0x0a, 0x02, 0x06,\
								    0xd1, 0x0a, 0x02, 0x06, 0xd3, 0x0a,	0x02, 0x06, 0xd8, 0x0a, 0x02, 0x06, 0xd9, 0x0a, 0x02, 0x06, 0xda, 0x0a,\
								    0x02, 0x06, 0xdb, 0x0a, 0x02, 0x10, 0x10};

	zvt_retvalue = Zvt_Transmit2Pt1_42(ZVT_REMOTE_PORT, registration_0600Data, sizeof(registration_0600Data)/sizeof(uint8));

	return(zvt_retvalue);
}


/*
@brief
@details  Registration password, CC, list of commands
@para
@return
*/
uint8 Zvt_PtUserRegistration0600(void)
{
	uint8 zvt_retvalue;

	uint8 registration_0600Data[] ={0x06, 0x00, 0x3a, 0x01, 0x02, 0x03, 0x8e, 0x09, 0x78, 0x06, 0x32, 0x40, 0x02, 0xb0, 0x80, 0x26, 0x2c, 0x0a,\
								    0x02, 0x04, 0x0f, 0x0a, 0x02, 0x04, 0xff, 0x0a, 0x02, 0x06, 0x0f, 0x0a, 0x02, 0x06, 0x1e, 0x0a, 0x02, 0x06,\
								    0xd1, 0x0a, 0x02, 0x06, 0xd3, 0x0a,	0x02, 0x06, 0xd8, 0x0a, 0x02, 0x06, 0xd9, 0x0a, 0x02, 0x06, 0xda, 0x0a,\
								    0x02, 0x06, 0xdb, 0x0a, 0x02, 0x10, 0x10};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, registration_0600Data, sizeof(registration_0600Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para     uint8* PreAuthorizedMoney	 (zvtTx2PtData.preAuthorizedAmount[6u])
@return	  ZVT_RET_OK/ZVT_RET_N_OK
*/
uint8 Zvt_PtPreAuthorized0622(uint32* PreAuthorizedMoney)
{
	uint8 zvt_retvalue = 0u;
	uint8 preAuthorized_0622Data[] = {0x06, 0x22, 0x09,\
									  0x04, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, /* max 25. 00 EURO*/ \
									  0x19, 0x44								/*Payment-type*/ };

	if(NULL != *PreAuthorizedMoney)
	{
		memcpy(&preAuthorized_0622Data[8u], PreAuthorizedMoney, 2u);

		zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, preAuthorized_0622Data, sizeof(preAuthorized_0622Data)/sizeof(uint8));

		if (ZVT_RET_N_OK == zvt_retvalue)
	   {
		   memset(preAuthorized_0622Data, 0u, sizeof(preAuthorized_0622Data)/sizeof(uint8));
	   }
	}

	return(zvt_retvalue);
}

/*
@brief
@details
@para     uint8* PreAuthorizedMoney	 (zvtTx2PtData.preAuthorizedAmount[6u])
@return	  ZVT_RET_OK/ZVT_RET_N_OK
*/

uint8 Zvt_PtPreAuthorized0622SID(uint8* PreAuthorizedMoney)
{
	uint8 zvt_retvalue = 0u;
	uint8 preAuthorized_0622DataSid[] = {0x06, 0x22, 0x13,\
									  0x04, 0x00, 0x00, 0x00, 0x00, 0x25, 0x00, /* max 25. 00 EURO*/ \
									  0x19, 0x44,								/*Payment-type*/\
									  0x06, 0x08, \
									  0x1f, 0x15, 0x01, 0x82,	/*calculate Secure-ID with offline hash algorithm*/\
									  0x1f, 0x61, 0x01, 0x04	/*using Salt-Key no.4*/	};

		memcpy(&preAuthorized_0622DataSid[8u], PreAuthorizedMoney, 2u);

		zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, preAuthorized_0622DataSid, sizeof(preAuthorized_0622DataSid)/sizeof(uint8));

		if (ZVT_RET_N_OK == zvt_retvalue)
	   {
		   memset(preAuthorized_0622DataSid, 0u, sizeof(preAuthorized_0622DataSid)/sizeof(uint8));
	   }

	return(zvt_retvalue);
}


/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtReturnRemainingAmount0623(uint8*Receiptnumber, uint8* RemainingMoney)
{
	uint8 zvt_retvalue;
	uint8 remainAmount_0623Data[] = {0x06, 0x23, 0x0a,\
									0x87, 0x00, 0x06,/*Receipt-number*/\
									0x04, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00 };  /*default Remaining 18. 00 EURO*/

	if(NULL != *(uint16*)Receiptnumber)
	{
		memcpy(&remainAmount_0623Data[4u], Receiptnumber, 2u);
		memcpy(&remainAmount_0623Data[11u], RemainingMoney, 2u);

		zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, remainAmount_0623Data, sizeof(remainAmount_0623Data)/sizeof(uint8));

		if (ZVT_RET_N_OK == zvt_retvalue)
	   {
			memset(remainAmount_0623Data, 0u, sizeof(remainAmount_0623Data)/sizeof(uint8));
	   }
		return(zvt_retvalue);
	}
	else
	{
		return FALSE;
	}
}



/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtExtendedDiagnosis0670_2(void)
{
	uint8 zvt_retvalue;
	uint8 extDiag_0670Data[] = {0x06, 0x70, 0x05, 0x06, 0x03, 0x1b, 0x01, 0x02};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, extDiag_0670Data, sizeof(extDiag_0670Data)/sizeof(uint8));

	return(zvt_retvalue);

}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtConfigurationDiagnosis0670_3(void)
{
	uint8 zvt_retvalue;
	uint8 configDiag_0670Data[] = {0x06, 0x70, 0x05, 0x06, 0x03, 0x1b, 0x01, 0x03};


	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, configDiag_0670Data, sizeof(configDiag_0670Data)/sizeof(uint8));

	return(zvt_retvalue);
}



/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtEmvConfigurationDiagnosis0670_4(void)
{
	uint8 zvt_retvalue;
	uint8 emvConfigDiag_0670Data[] = {0x06, 0x70, 0x05, 0x06, 0x03, 0x1b, 0x01, 0x04};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, emvConfigDiag_0670Data, sizeof(emvConfigDiag_0670Data)/sizeof(uint8));

	return(zvt_retvalue);
}


/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtInitilisation0693(void)
{
	uint8 zvt_retvalue;
	uint8 ptInitilisation_0693Data[] = {0x06, 0x93, 0x03, 0x01, 0x02, 0x03};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, ptInitilisation_0693Data, sizeof(ptInitilisation_0693Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtAbort06B0(void)
{
	uint8 zvt_retvalue;
	uint8 ptAbort_06b0Data[] = {0x06, 0xb0, 0x00};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, ptAbort_06b0Data, sizeof(ptAbort_06b0Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtReadCard06C0UID(void)
{
	uint8 zvt_retvalue;
	uint8 ptReadCrad_06c0Data[] = {0x06, 0xC0, 0x0F, 0x00, 0x06, 0x0C, 0x1F, 0x15, 0x01, 0x40, 0x1F, 0x60, 0x01, 0x04, 0x1F, 0x61, 0x01, 0x00};
/*0x06, 0xC0, 0x0F, 0x00, 0x06, 0x0C, 0x1F, 0x15, 0x01, 0x40, 0x1F, 0x60, 0x01, 0x04, 0x1F, 0x61, 0x01, 0x00*/
	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, ptReadCrad_06c0Data, sizeof(ptReadCrad_06c0Data)/sizeof(uint8));
	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtReadCard06C0SID(void)
{
	uint8 zvt_retvalue;
	uint8 ptReadCrad_06c0DataSid[] = {0x06, 0xc0, 0x0f, 0x00, 0x06, 0x0c, \
									  0x1f, 0x15, 0x01, 0x82, /*calculate Secure-ID with offline hash algorithm*/\
									  0x1f, 0x60, 0x01, 0x04, /*allowed card technologies: only contactless cards*/\
									  0x1f, 0x61, 0x01, 0x04};/*聽using Salt-Key no.4*/

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, ptReadCrad_06c0DataSid, sizeof(ptReadCrad_06c0DataSid)/sizeof(uint8));

	return(zvt_retvalue);
}



/*
@brief
@details	send cmd	8000	PositiveAcknowledgement
@para
@return
*/
uint8 Zvt_PtTxPositiveAck8000(void)
{
	uint8 zvt_retvalue;

	uint8 positiveAck_8000Data[] = {0x80, 0x00, 0x00};
	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, positiveAck_8000Data, sizeof(positiveAck_8000Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details	send cmd	8000	PositiveAcknowledgement
@para
@return
*/
uint8 Zvt_PtTxFactoryPositiveAck8000(void)
{
	uint8 zvt_retvalue;

	uint8 positiveAck_8000Data[] = {0x80, 0x00, 0x00};
	zvt_retvalue = Zvt_Transmit2Pt1_42(ZVT_REMOTE_PORT, positiveAck_8000Data, sizeof(positiveAck_8000Data)/sizeof(uint8));

	return(zvt_retvalue);
}


/*
@brief
@details Configure  IP address闂傚倷绶氬褍螞閺冨牊鍤堥柟顓烆浐mask闂傚倷绶氬褍螞閺冨倻绠旈柕鍫熺eway闂傚倷绶氬褍螞閺冨倹灏庡┑鐙呮�? and TID
@para
@return
*/

/*
08 13 - command				[0]
4B - length of zvt command	[2]
06 - TLV container			[3]
49 - length of TLV container	[4]
2D - Tag 2D (<file> see ECR-Interface ZVT-Protocol PA00P015_13.xx)			[5]
47 - length of Tag 2D														[6]
1C - Tag 1C (<file-block> see ECR-Interface ZVT-Protocol PA00P015_13.xx)	[7]
45 - length of Tag 1C														[8]

CCV specific extension of ECR-Interface ZVT-Protocol PA00P015_13.xx ->
20 - Tag TLV_TAG_CCV_TERMINAL_INITIATION (Container der Konfigurationsparameter)	[9]
43 - length of Tag 20						[10]
01 - Tag TLV_TAG_CCV_TERMINAL_ID			[11]
08 - length of Tag 01						[12]
38 34 30 37 33 30 32 30 - Terminal ID		[13]
02 - Tag TLV_TAG_CCV_PU		[21]
01 - length of Tag 02		[22]
63 - PU Number des Payment Hosts	[23]
06 - Tag TLV_TAG_CCV_IP_DHCP_FLAG	[24]
01 - length of Tag 06				[25]
00 - DHCP off						[26]
03 - Tag TLV_TAG_CCV_IP_ADDRESS		[27]
0F - length of Tag 03				[28]
31 39 32 2E 31 36 38 2E 30 30 32 2E 31 30 30 - TCP/IP address terminal	[29]
04 - Tag TLV_TAG_CCV_IP_SUBNET_MASK	[37]
0F - length of Tag 04				[38]
32 35 35 2E 32 35 35 2E 32 35 35 2E 30 30 30 - Netmask terminal			[46]
05 TLV_TAG_CCV_IP_GATEWAY			[54]
0F - length of Tag 05				[55]
31 39 32 2E 31 36 38 2E 30 30 32 2E 30 30 31 - Gateway terminal		[63]

 * */
uint8 debugFlag_ChangeIP = 0u;
uint8 ptConfig_0813Data[] = {0x08 , 0x13 , 0x4B , 0x06 , 0x49 , 0x2D , 0x47 , 0x1C , 0x45 , 0x20 ,\
							0x43 , 0x01 , 0x08 , \
							0x34 , 0x34 , 0x32 , 0x32 , 0x30 , 0x30 , 0x37 ,0x31 , 	/*[13] TID = 44220071*/\
							0x02 , 0x01 , 0x63 , 0x06 , 0x01 , 0x00 , 0x03 , 0x0F ,\
							0x31 , 0x39 , 0x32 , 0x2E , 0x31 , 0x36 , 0x38 , 0x2E,	/*[29] IP = 192.168.0.71*/\
							0x30 , 0x30 , 0x30 , 0x2E , 0x30 , 0x37 , 0x31 , 		/*IP*/\
							0x04 , 0x0F , \
							0x32 , 0x35 , 0x35 , 0x2E ,	0x32 , 0x35 , 0x35 , 0x2E,	/*[46] Netmask*/\
							0x32 , 0x35 , 0x35 , 0x2E , 0x30 , 0x30 , 0x30,			/*Netmask*/\
							0x05 , 0x0F , \
							0x31 , 0x39 , 0x32 , 0x2E , 0x31 , 0x36 , 0x38 ,		/*[63] Gateway = 192.168.0.1*/\
							0x2E , 0x30 , 0x30 , 0x30 , 0x2E , 0x30 , 0x30 , 0x31	/*Gateway*/
						};

//uint8 ptConfig_0813Data[] = {0x08 , 0x13 , 0x4B , 0x06 , 0x40 , 0x2D , 0x3E , 0x1C , 0x3C , 0x20 ,\
//							0x3A , 0x01 , 0x08 , \
//							0x34 , 0x34 , 0x32 , 0x32 , 0x30 , 0x30 , 0x37 ,0x31 , 	/*[13] TID = 44220071*/\
//							0x02 , 0x01 , 0x63 , 0x03 , 0x0C ,\
//							0x31 , 0x39 , 0x32 , 0x2E , 0x31 , 0x36 , 0x38 , 0x2E,	/*[26] IP = 192.168.1.71*/\
//							0x30 , 0x30 , 0x31 , 0x2E , 0x30 , 0x37 , 0x31 , 		/*IP*/\
//							0x04 , 0x0F , \
//							0x32 , 0x35 , 0x35 , 0x2E ,	0x32 , 0x35 , 0x35 , 0x2E,	/*[46] Netmask*/\
//							0x32 , 0x35 , 0x35 , 0x2E , 0x30 , 0x30 , 0x30,			/*Netmask*/\
//							0x05 , 0x0F , \
//							0x31 , 0x39 , 0x32 , 0x2E , 0x31 , 0x36 , 0x38 ,		/*[63] Gateway = 192.168.1.1*/\
//							0x2E , 0x30 , 0x30 , 0x31 , 0x2E , 0x30 , 0x30 , 0x31	/*Gateway*/
//						};

uint8 Zvt_PtFactoryConfiguration0813(uint8* Tid_Ascii_8B,\
									 uint8* Ip_Ascii_15B,\
									 uint8* Netmask_Ascii_15B,\
									 uint8* Gateway_Ascii_15B)
{
	uint8 zvt_retvalue;
	/*static IP address=192.168.2.100, Netmask=255.255.255.0, Gateway=192.168.2.1, PU=99 and TID=84073020 */
	/*static IP address=192.168.1.88,  Netmask=255.255.255.0, Gateway=192.168.1.1, PU=99 and TID=44220073 */

	if(1u == debugFlag_ChangeIP)
	{
		memcpy(&ptConfig_0813Data[13u], Tid_Ascii_8B, 8u);
		memcpy(&ptConfig_0813Data[29u], Ip_Ascii_15B, 15u);
		memcpy(&ptConfig_0813Data[46u], Netmask_Ascii_15B, 15u);
		memcpy(&ptConfig_0813Data[63u], Gateway_Ascii_15B, 15u);
	}

	if(0u == debugFlag_ChangeIP)
	{
		lPtConfigDataConverter_TID(Tid_Ascii_8B, &ptConfig_0813Data[13u]);

		lPtConfigDataConverter_IP_Netmask_Gateway(Ip_Ascii_15B, &ptConfig_0813Data[29u]);
		lPtConfigDataConverter_IP_Netmask_Gateway(Netmask_Ascii_15B, &ptConfig_0813Data[46u]);
		lPtConfigDataConverter_IP_Netmask_Gateway(Gateway_Ascii_15B, &ptConfig_0813Data[63u]);
	}

	zvt_retvalue = Zvt_Transmit2Pt1_42(ZVT_REMOTE_PORT, ptConfig_0813Data, sizeof(ptConfig_0813Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
 uint8 Zvt_PtUserConfiguration0813(uint8* Tid_Ascii_8B,\
		 	 	 	 	 	 	   uint8* Ip_Ascii_15B,\
								   uint8* Netmask_Ascii_15B,\
								   uint8* Gateway_Ascii_15B)
{
	uint8 zvt_retvalue;
	/*static IP address=192.168.2.100, Netmask=255.255.255.0, Gateway=192.168.2.1, PU=99 and TID=84073020 */
	/*static IP address=192.168.1.88,  Netmask=255.255.255.0, Gateway=192.168.1.1, PU=99 and TID=44220073 */

	if(1u == debugFlag_ChangeIP)
	{
		memcpy(&ptConfig_0813Data[13u], Tid_Ascii_8B, 8u);
		memcpy(&ptConfig_0813Data[29u], Ip_Ascii_15B, 15u);
		memcpy(&ptConfig_0813Data[46u], Netmask_Ascii_15B, 15u);
		memcpy(&ptConfig_0813Data[63u], Gateway_Ascii_15B, 15u);
	}

	if(0u == debugFlag_ChangeIP)
	{
		lPtConfigDataConverter_TID(Tid_Ascii_8B, &ptConfig_0813Data[13u]);

		lPtConfigDataConverter_IP_Netmask_Gateway(Ip_Ascii_15B, &ptConfig_0813Data[29u]);
		lPtConfigDataConverter_IP_Netmask_Gateway(Netmask_Ascii_15B, &ptConfig_0813Data[46u]);
		lPtConfigDataConverter_IP_Netmask_Gateway(Gateway_Ascii_15B, &ptConfig_0813Data[63u]);
	}

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, ptConfig_0813Data, sizeof(ptConfig_0813Data)/sizeof(uint8));

	return(zvt_retvalue);
}



/*
@brief
@details	Change the language  type
@para
@return
*/
uint8 Zvt_PtChangeLanguage0830(zvt_languagetype* LanguageTpye)
{
	uint8 zvt_retvalue;

	uint8 txGermanBuff[4u] 	= {0x08, 0x30, 0x01, 0x0};
	uint8 txEnglishBuff[4u] = {0x08, 0x30, 0x01, 0x1};
	uint8 txFrenchBuff[4u] 	= {0x08, 0x30, 0x01, 0x2};
	uint8 txItalianBuff[4u] = {0x08, 0x30, 0x01, 0x3};

	switch(*LanguageTpye)
	{
		case German:
			zvt_retvalue = Zvt_Transmit2Pt(ZVT_LOCAL_PORT, &txGermanBuff[0u], ZVT_LANGUAGE_BUFF_LENGTH);
			break;

		case English:
			zvt_retvalue = Zvt_Transmit2Pt(ZVT_LOCAL_PORT, &txEnglishBuff[0u], ZVT_LANGUAGE_BUFF_LENGTH);
			break;

		case French:
			zvt_retvalue = Zvt_Transmit2Pt(ZVT_LOCAL_PORT, &txFrenchBuff[0u], ZVT_LANGUAGE_BUFF_LENGTH);
			break;

		case Italian:
			zvt_retvalue = Zvt_Transmit2Pt(ZVT_LOCAL_PORT, &txItalianBuff[0u], ZVT_LANGUAGE_BUFF_LENGTH);
			break;

		default:
			break;

	}

	return(zvt_retvalue);
}





/*
@brief
@details	send cmd	8400	PositiveAcknowledgement
@para
@return
*/
uint8 Zvt_PtTxPositiveAck8400(void)
{
	uint8 zvt_retvalue;
	uint8 positiveAck_8400Data[] = {0x84, 0x00, 0x00};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, positiveAck_8400Data, sizeof(positiveAck_8400Data)/sizeof(uint8));

	return(zvt_retvalue);
}



/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtReadCreditStatus(void)
{
	uint8 zvt_retvalue;
	uint8 creditStatusEnquiry_0501Data[] = {0x05, 0x01, 0x05, 0x00, 0x00, 0x00, 0x03, 0x03};
	TcpIp_SocketIdType   ptSocketId = 0u;

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, creditStatusEnquiry_0501Data, sizeof(creditStatusEnquiry_0501Data)/sizeof(uint8));


	return(ZVT_RET_OK);

}



/*
@brief
@details
@para
@return
*/
uint8  Zvt_PtReadRfidStatus(void)
{
	uint8 zvt_retvalue;
	uint8 rfidStatusEnquiry_0501Data[] = {0x05, 0x01, 0x05, 0x00, 0x00, 0x00, 0x03, 0x03};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, rfidStatusEnquiry_0501Data, sizeof(rfidStatusEnquiry_0501Data)/sizeof(uint8));

	return(zvt_retvalue);

}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_PtReadIntermediateStatus(void)
{
	return 0;
}




/*
@brief
@details
@para
@return
*/
uint8 Zvt_ReadRfidUID(void)
{
	uint8 zvt_retvalue;
	uint8 readCard_06C0Data[] = {0x06, 0xC0, 0x0F, 0x00, 0x06, 0x0C, 0x1F, 0x15, 0x01, 0x40, 0x1F, 0x60, 0x01, 0x04, 0x1F, 0x61, 0x01, 0x00};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, readCard_06C0Data, sizeof(readCard_06C0Data)/sizeof(uint8));

	return(zvt_retvalue);
}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_ReadCard(void)
{
	uint8 zvt_retvalue;
	uint8 readCard_06C0Data[] = {0x06, 0xC0, 0x05, 0x1E, 0x19, 0x50, 0xFC, 0x01};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, readCard_06C0Data, sizeof(readCard_06C0Data)/sizeof(uint8));

	return(zvt_retvalue);
}


/*
@brief
@details
@para
@return
*/
void Zvt_GetRfidUID(void)
{

	memcpy(Rfid_UID_Number, extractCmd040fExtData.UID_0x4c_2_10B, PT_SID_LEN);

}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_SetDateTime(uint16 date, uint16 time)
{
	uint8 zvt_retvalue;
	uint8 readCard_0670Data[] = {0x06, 0xC0, 0x05, 0x1E, 0x19, 0x50, 0xFC, 0x01};

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, readCard_0670Data, sizeof(readCard_0670Data)/sizeof(uint8));

	return(zvt_retvalue);
}


/*
@brief
@details
@para
@return
*/
uint8 Zvt_CheckSameCard(void)
{
	uint8 zvt_retvalue;
	uint8 readCard_0670Data[] = {0x06, 0xC0, 0x05, 0x1E, 0x19, 0x50, 0xFC, 0x01};

	/*	List of ZVT-card-type IDs	185/199*/
	if(extractCmd040fExtData.CardType_Bin0x8a_2B)
	{

	}

	zvt_retvalue = Zvt_Transmit2Pt(ZVT_REMOTE_PORT, readCard_0670Data, sizeof(readCard_0670Data)/sizeof(uint8));

	return(zvt_retvalue);
}



/*
@brief
@details
@para
@return
*/

uint8 Zvt_Transmit2Pt1_42(TcpIp_PortType zvtLocalPort, uint8* pZvtTxDatabuf, uint16 zvtTxLength)
{
	uint8 zvt_retvalue;

	zvt_retvalue = Ethernet_TcpClient_Send(zvtLocalPort, &Factory_RemoteAddress, pZvtTxDatabuf, zvtTxLength);

	return(zvt_retvalue);
}


/*
@brief
@details
@para
@return
*/
uint8 Zvt_Transmit2Pt(TcpIp_PortType zvtLocalPort, uint8* pZvtTxDatabuf, uint16 zvtTxLength)
{
	uint8 zvt_retvalue;

	zvt_retvalue = Ethernet_TcpClient_Send(zvtLocalPort, &CCV_POS_RemoteAddress, pZvtTxDatabuf, zvtTxLength);

	if(zvt_retvalue == 0u)
	{
        if(!(3 == zvtTxLength && 0x80 == pZvtTxDatabuf[0] && 0x00 == pZvtTxDatabuf[1]))
        {
            Zvt_PtCheckReceive8000Ack();
        }
        return(ZVT_RET_OK);    
	}
	else
	{
		return(ZVT_RET_N_OK);
	}

}


/*
@brief
@details
@para
@return
*/
uint8 Zvt_Receive2Pt(uint8* pZvtRxBuf, uint16* zvtRxLength)
{

	uint8 zvt_retvalue;
    zvt_retvalue = Ethernet_CCV_GetRxData(pZvtRxBuf, zvtRxLength);
	return (zvt_retvalue);

}

/*
@brief
@details
@para
@return
*/
uint8 Zvt_Receive2Pt1_42(uint8* pZvtRxBuf, uint16* zvtRxLength)
{

	uint8 zvt_retvalue;

	zvt_retvalue = Ethernet_CCV_GetRxData(&Factory_RemoteAddress, pZvtRxBuf, zvtRxLength);

	return (zvt_retvalue);

}


/*
@brief
@details  handle the procedure about the received signals
@para
@return
@note     poll in BSW_OsTask_10ms()
*/
uint8 Zvt_PtSortReceivedCommand(void)
{
	uint8 zvt_retvalue;
	volatile uint16 zvtSocketRxFrameSizeTemp;
	{
		if(0u == zvtSocketRxFrameSize)
		{
			return ZVT_RET_N_OK;
		}

			memcpy(zvtSignalFrPt_Arr, zvtSocketRxFrame, zvtSocketRxFrameSize);
			memcpy(zvtSignalFrPt_Arr_Temp, zvtSocketRxFrame, zvtSocketRxFrameSize);
			zvtSocketRxFrameSizeTemp = zvtSocketRxFrameSize;

			/*the first byte of control field*/
			if((0x01u == zvtSignalFrPt_Arr[0u])||(0x04u == zvtSignalFrPt_Arr[0u]) \
			  ||(0x05u == zvtSignalFrPt_Arr[0u])||(0x06u == zvtSignalFrPt_Arr[0u])\
			  ||(0x08u == zvtSignalFrPt_Arr[0u])||(0x0Fu == zvtSignalFrPt_Arr[0u])\
			  ||(0x80u == zvtSignalFrPt_Arr[0u])||(0x84u == zvtSignalFrPt_Arr[0u]))
			{
				if(zvtSignalFrPt_Arr[2u] < ZVT_EXT_FORMAT_FLAG)						/*Stand Format*/
				{
					zvtRealRxLength = zvtSignalFrPt_Arr[2u];
				}
				else
				{
					zvtRealRxLength = ((uint16)zvtSignalFrPt_Arr[3u]) + (((uint16)zvtSignalFrPt_Arr[4u]) << 8u);		/*Extended Format*/
				}

				{
					if((cmd0401SetDateTimeECR[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd0401SetDateTimeECR[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd040DInputRequest[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd040DInputRequest[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();

					}

					else if((cmd040EMenuRequest[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd040EMenuRequest[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd040FStatusInformation[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd040FStatusInformation[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd040FStatusInformationRx(zvtSocketRxFrameSizeTemp, &zvtSignalFrPt_Arr[0u]);

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd04FFIntermediateStatusInformation[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd04FFIntermediateStatusInformation[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd04FFIntermediateStatusInformationRx(zvtSocketRxFrameSizeTemp, &zvtSignalFrPt_Arr[0u]);

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd060FCompletion[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd060FCompletion[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd060FCompletionRx(zvtSocketRxFrameSizeTemp, &zvtSignalFrPt_Arr[0u]);

						Zvt_PtTxPositiveAck8000();

					}

					else if((cmd061EAbort[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd061EAbort[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd061EAbortRx(zvtSocketRxFrameSizeTemp, &zvtSignalFrPt_Arr[0u]);
						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06D1PrintLine[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06D1PrintLine[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06D3PrintTextBlock[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06D3PrintTextBlock[1u] == zvtSignalFrPt_Arr[1u]))
					{

						lZvt_Analysis_cmd06D3PrintTextBlockRx();
						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06D8DialUp[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06D8DialUp[1u] == zvtSignalFrPt_Arr[1u]))
					{
						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06D9TransmitDataDialUp[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06D9TransmitDataDialUp[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06DAReceiveDataDialUp[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06DAReceiveDataDialUp[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06DBHangUp[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06DBHangUp[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06DDTransparentMode[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06DDTransparentMode[1u] == zvtSignalFrPt_Arr[1u]))
					{
						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd06E4BlockedListQuery2ECR[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd06E4BlockedListQuery2ECR[1u] == zvtSignalFrPt_Arr[1u]))
					{

						Zvt_PtTxPositiveAck8000();
					}

					else if((cmd8000PositiveAcknowledgement[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd8000PositiveAcknowledgement[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd8000PositiveAcknowledgementRx(&zvtSignalFrPt_Arr[0u]);
						 if(9u == debugFlagList.debugFlag6)
						 {
								memset(&zvtSignalFrPt_Arr[0u], 0u, 3u);
						 }
							Zvt_PtTxPositiveAck8000();
					}

					else if((cmd8400PositiveAcknowledgement[0u] == zvtSignalFrPt_Arr[0u])\
						&& (cmd8400PositiveAcknowledgement[1u] == zvtSignalFrPt_Arr[1u]))
					{
						lZvt_Analysis_cmd8400PositiveAcknowledgementRx(zvtSocketRxFrameSizeTemp, &zvtSignalFrPt_Arr[0u]);
						Zvt_PtTxPositiveAck8000();

					}
					else
					{ ; }
				}

			}

			memset(&zvtSignalFrPt_Arr[3u], 0u, 8u);
			memset(zvtSocketRxFrame, 0u, zvtSocketRxFrameSize);
			zvtSocketRxFrameSize = 0u;

	}


	return(ZVT_RET_OK);
}


/*
@brief
@details	called by BSW_OsTask_10ms()
@para
@return
*/
void Zvt_10msTask(void)
{

	if(User_IpMode == IpModeFlag)
	{
		   Zvt_Receive2Pt(&zvtSocketRxFrame[0u], &zvtSocketRxFrameSize);
	}

	if(Factory_IpMode == IpModeFlag)
	{
		   Zvt_Receive2Pt1_42(&zvtSocketRxFrame[0u], &zvtSocketRxFrameSize);
	}

	{
		Zvt_PtSortReceivedCommand();
	}

	{
		StateTask();
	}

}

Std_ReturnType  Zvt_ArpSniffer(void)
{

	if(ZvtSniffer_Start == arpSnifferFlag)
	{
//		for(arpSnifferCount = 2u; arpSnifferCount < 255u; arpSnifferCount++)
		for(arpSnifferCount = 250u; arpSnifferCount < 255u; arpSnifferCount++)
		{
			dp_frameTypeARP = ((uint16_t)dp_txMacFrame[OFFSET_FRAMETYPE] << 8U) | dp_txMacFrame[OFFSET_FRAMETYPE + 1];

			dp_ethRet = Eth_ProvideTxBuffer(CTRL_IDX, dp_bufIdxPtr, dp_txBufPtrPtr, dp_lenBytePtr);
			if(dp_ethRet != BUFREQ_OK)
				return E_NOT_OK;

			/*If guaranteed memory is larger than requested memory, re-assign lenByte as requested value. Or return E_NOT_OK.*/
			if(*dp_lenBytePtr >= LENGTH_PAYLOAD)
				dp_lenByte = LENGTH_PAYLOAD;
			else
				return E_NOT_OK;

			/*Assign value to memory pointed by txBufPtr, whose value is assigned by txBufPtrPtr in Eth_ProvideTxBuffer.*/
			for(dp_i = 0u; dp_i < dp_lenByte; dp_i++)
			{
				*dp_txBufPtr = dp_txMacFrame[OFFSET_PAYLOAD + dp_i];
				dp_txBufPtr++;
			}

			dp_ret = Eth_Transmit(CTRL_IDX, dp_bufIdx, dp_frameTypeARP, TXCOMFIRMATION_OFF, dp_lenByte, dp_txMacFrame);


			if(dp_ret != E_OK)
				return E_NOT_OK;


			Eth_TxConfirmation(TXCOMFIRMATION_ON);							/*for polling only*/
			dp_txMacFrame[41u]++;
			if(0xff == dp_txMacFrame[41u])
			{
				dp_txMacFrame[41u] = 0xfa;
				break;
			}

			return E_OK;
		}
	}
	return(ZVT_RET_OK);

}


