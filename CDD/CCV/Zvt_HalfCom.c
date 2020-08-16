#include "Zvt_HalfCom.h"
#include "ASW_RTE.h"

volatile uint8_t CCV_UID[2][16]; //Save UID from Mifare Card
volatile uint8_t CCV_SID[2][32]; //Save SID Num with 06 C0 CMD, for UserStop
volatile uint8_t CCV_CardType_Bak[2]; // 0 for CreditCard 1 for Mifare Card;

volatile uint8_t tmp_ASW_Config_Request = 0;
volatile uint8_t tmp_ASW_CC_Request = 0;
volatile uint8_t tmp_ASW_Mifare_Request = 0;
volatile uint8_t tmp_ASW_UserStop_Request = 0;
volatile uint8_t tmp_ASW_CC_Reversal_Request = 0;

static volatile ccv_parser_t 		CCV_Parser;
static volatile ccv_signal_t 		CCV_Signal;
static volatile ccv_sigupdatefunc_t CCV_SignalUpdate;

ccv_ptconfig_factory0813_t    	PtConfig0813FactoryData;
ccv_ptconfig_user0813_t    		PtConfig0813UserData;
ccv_ptconfig_0693_t				PtInit0693Data;
ccv_ptconfig_0670emv_t          PtDiag0670EmvData;

ccv_configdata_t			PtConfigData;
zvt_credituserstopdata_t 	UserStopCreditData;
zvt_preauthdata_t 			CCV_PreAuthData;
zvt_partialreversaldata_t 	CCV_PartReverData;
zvt_mifaredata_t            CCV_MifareData;


zvt_ptconfig_t stPtCfgData;

extern zvt_writerte_t Zvt_WriteRte;
extern zvt_readasw_t Zvt_ReadAsw;

extern zvt_pt_ipmode IpModeFlag;
extern zvt_cmd04ff_stdformat_t  cmd04ffPayload;
extern zvt_debugflag_t debugFlagList;


extern volatile zvt_wrcomtest_t ZvtCom_Write;
extern volatile zvt_rdcomtest_t ZvtCom_Read;

extern TcpIp_SockAddrInetType User_LocalAddress;
extern TcpIp_SockAddrInetType User_RouterAddress;
extern TcpIp_SockAddrInetType User_RemoteAddress;


extern uint8 Zvt_MoneyFloat32Convert2Uint8Bcd(const float32* InputData, uint8* OutputData);

void CCV_StateIdleInit(void);
void CCV_StateCreditInit(void);
void CCV_StateMifareInit(void);
void CCV_StateUserStopInit(void);
void CCV_StateCreditReversalInit(void);
void CCV_StatePtConfigInit(void);


void CCV_StateIdleUpdate(void);
void CCV_StateCreditUpdate(void);
void CCV_StateMifareUpdate(void);
void CCV_StateUserStopUpdate(void);
void CCV_StateCreditReversalUpdate(void);
void CCV_StatePtConfigUpdate(void);


void CCV_StateIdle(parser_t *me, signal_t sig);
void CCV_StateCredit(parser_t *me, signal_t sig);
void CCV_StateMifare(parser_t *me, signal_t sig);
void CCV_StateUserStop(parser_t *me, signal_t sig);
void CCV_StateCreditReversal(parser_t *me, signal_t sig);
void CCV_StatePtConfig(parser_t *me, signal_t sig);

extern zvt_pt_ipmode Zvt_PtGetIPMode(void);
extern uint8 Asw_ZvtDispatch0622PreAuthRequest(void);
extern uint8 Asw_ZvtDispatch06C0CreditStopRequest(void);
extern uint8 Asw_ZvtDispatch0623ReversalRequest(void);
extern uint8 Asw_ZvtDispatch06C0MifareRequest(void);

extern uint16 lZvt_2Uint8bcdMergeToUint16(uint8* data);
extern void lPartialReversal_SendCmd04ffAck(void);
extern void lPtConfig0813_SendAckCmd(void);
extern uint8 Zvt_PtAbort06B0(void);
extern void lSendCmd04ffAck(void);
extern void lPreAuthorized_SendCmd04ffAck(void);

/*
@brief
@details
@para
@return
@note    InputData = ZvtCom_Read.PtCfg_IpAddr, OutputData = User_LocalAddress.addr
*/
void lAswTcpDataConverter_UserIP(const uint8* InputData, uint32* OutputData)
{
	uint8 InputArray[4u] = {0u};
	uint32 OutputDataTemp;

	memcpy(InputArray, InputData, 4u);

	OutputDataTemp = ((uint32)InputArray[3u]) + \
					 (((uint32)InputArray[2u]) << 8u ) + \
		             (((uint32)InputArray[1u]) << 16u ) + \
					 (((uint32)InputArray[0u]) << 24u );

	*OutputData = OutputDataTemp;
}

/*
@brief
@details
@para
@return
@note    InputData = ZvtCom_Read.PtCfg_IpAddr, OutputData = User_LocalAddress.addr
*/
uint8 CompareSimilarIpData(const uint8* ZvtIpData, const uint32* EthIpData)
{
	uint8 ZvtIpDataArrayTemp[4u] = {0u};

	uint32 ZvtIpDataTemp = 0u;
	uint32 EthIpDataTemp = 0u;

	memcpy(ZvtIpDataArrayTemp, ZvtIpData, 4u);
	EthIpDataTemp = * EthIpData;

	ZvtIpDataTemp = ((uint32)ZvtIpDataArrayTemp[3u]) + \
					 (((uint32)ZvtIpDataArrayTemp[2u]) << 8u ) + \
		             (((uint32)ZvtIpDataArrayTemp[1u]) << 16u ) + \
					 (((uint32)ZvtIpDataArrayTemp[0u]) << 24u );

	if(ZvtIpDataTemp == EthIpDataTemp)
	{
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
@note    InputData = ZvtCom_Read.PtCfg_IpAddr, OutputData = User_LocalAddress.addr
*/

void Asw_ZvtChangeUserIP(void)
{

//	lAswTcpDataConverter_UserIP(ZvtCom_Read.PtCfg_IpAddr, User_LocalAddress.addr);

	lAswTcpDataConverter_UserIP(ZvtCom_Read.PtCfg_IpAddr, CCV_POS_RemoteAddress.addr);
//	lAswTcpDataConverter_UserIP(ZvtCom_Read.PtCfg_IpAddr, User_LocalAddress.addr);

}

/*
@brief
@details
@para
@return
@note
*/
uint8 lBitmap06Get06C0_UIDProcess(uint8 *data, uint16* length)
{
	uint16 Bitmap06Get4C0A_Len;
	uint16 Bitmap06Get4C0A_Loop;
	uint8  Bitmap06Get4C0A[800u];

	Bitmap06Get4C0A_Len = *length;
	if((Bitmap06Get4C0A_Len > 12u)\
	 &&(Bitmap06Get4C0A_Len <= 800u))
	{
		memcpy(Bitmap06Get4C0A, data, Bitmap06Get4C0A_Len);

		for(Bitmap06Get4C0A_Loop = 0u;\
		    Bitmap06Get4C0A_Loop < (Bitmap06Get4C0A_Len - 12u);\
		    Bitmap06Get4C0A_Loop++)
		{
			if((0x4C == Bitmap06Get4C0A[Bitmap06Get4C0A_Loop + 1u])\
			 &&(0x0A == Bitmap06Get4C0A[Bitmap06Get4C0A_Loop + 2u]))
			{

				{
					memcpy(CCV_MifareData.UID_0x4C0A_10B, &Bitmap06Get4C0A[Bitmap06Get4C0A_Loop + 3u], 10u );
					CCV_MifareData.getUID = TRUE;

					memset(Bitmap06Get4C0A, 0, 800);

					return TRUE;
					break;
				}
			}
		}
	}

	return FALSE;
}


/*
@brief
@details
@para
@return
@note
*/
uint8 lBitmap06Get06C0_SIDProcess(uint8 *data, uint16* length)
{
	uint16 Bitmap06Get141F_Len;
	uint16 Bitmap06Get141F_Loop;
	uint8  Bitmap06Get141F[800u];

	Bitmap06Get141F_Len = *length;
	if((Bitmap06Get141F_Len > 39u)\
	 &&(Bitmap06Get141F_Len <= 800u))
	{
		memcpy(Bitmap06Get141F, data, Bitmap06Get141F_Len);

		for(Bitmap06Get141F_Loop = 0u;\
		    Bitmap06Get141F_Loop < (Bitmap06Get141F_Len - 39u);\
		    Bitmap06Get141F_Loop++)
		{
			if((0x1F == Bitmap06Get141F[Bitmap06Get141F_Loop + 1u])\
			 &&(0x14 == Bitmap06Get141F[Bitmap06Get141F_Loop + 2u])\
			 &&(0x20 == Bitmap06Get141F[Bitmap06Get141F_Loop + 3u])\
			 &&(0x1F == Bitmap06Get141F[Bitmap06Get141F_Loop + 36u])\
			 &&(0x15 == Bitmap06Get141F[Bitmap06Get141F_Loop + 37u]))
			{
				if((Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)\
				 ||(Waitfor_0622SID == CCV_PreAuthData.PreAuthStep))
				{
					memcpy(CCV_PreAuthData.SID_0x1F14_32B, &Bitmap06Get141F[Bitmap06Get141F_Loop + 4u], PT_SID_LEN );
					CCV_PreAuthData.getSID = TRUE;

					memset(Bitmap06Get141F, 0, 800);

					return TRUE;
					break;
				}

				if(Arrived_UserSID == UserStopCreditData.UserStopStep)
				{
					memcpy(UserStopCreditData.SID_0x1F14_32B, &Bitmap06Get141F[Bitmap06Get141F_Loop + 4u], PT_SID_LEN );
					UserStopCreditData.getSID = TRUE;

					memset(Bitmap06Get141F, 0, 800);

					return TRUE;
					break;
				}

			}
		}

	}

	return FALSE;
}

/*
@brief
@details
@para
@return
@note
*/
uint8 lBitmap06Get0622SIDProcess(uint8 *data, uint16* length)
{
	uint16 Bitmap06Get141F_Len;
	uint16 Bitmap06Get141F_Loop;
	uint8  Bitmap06Get141F[800u];

	Bitmap06Get141F_Len = *length;

	if((Bitmap06Get141F_Len > 39u)\
	 &&(Bitmap06Get141F_Len <= 800u))
	{
		memcpy(Bitmap06Get141F, data, Bitmap06Get141F_Len);

		for(Bitmap06Get141F_Loop = (Bitmap06Get141F_Len - 39u);\
		    Bitmap06Get141F_Loop > 0u;\
		    Bitmap06Get141F_Loop--)
		{
			if((0x1F == Bitmap06Get141F[Bitmap06Get141F_Loop + 1u])\
			 &&(0x14 == Bitmap06Get141F[Bitmap06Get141F_Loop + 2u])\
			 &&(0x20 == Bitmap06Get141F[Bitmap06Get141F_Loop + 3u])\
			 &&(0x1F == Bitmap06Get141F[Bitmap06Get141F_Loop + 36u])\
			 &&(0x15 == Bitmap06Get141F[Bitmap06Get141F_Loop + 37u]))
			{
				if((Send0622Sid_OK == CCV_PreAuthData.PreAuthStep)\
				 ||(Waitfor_0622SID == CCV_PreAuthData.PreAuthStep))
				{
					memcpy(CCV_PreAuthData.SID_0x1F14_32B, &Bitmap06Get141F[Bitmap06Get141F_Loop + 4u], PT_SID_LEN );
					CCV_PreAuthData.getSID = TRUE;

					memset(Bitmap06Get141F, 0, 800u);

					return TRUE;
					break;
				}

				if(Arrived_UserSID == UserStopCreditData.UserStopStep)
				{
					memcpy(UserStopCreditData.SID_0x1F14_32B, &Bitmap06Get141F[Bitmap06Get141F_Loop + 4u], PT_SID_LEN );
					UserStopCreditData.getSID = TRUE;

					memset(Bitmap06Get141F, 0, 800u);

					return TRUE;
					break;
				}

			}
		}

	}

	return FALSE;
}

uint8 Bitmap06GetSIDProcess_0622(void)
{
	uint8 retvalue = 0u;


	retvalue = lBitmap06Get0622SIDProcess(CCV_PreAuthData.Bitmap06Get141F_Backup, &CCV_PreAuthData.Bitmap06Length);

	if(TRUE == retvalue)
	{
		memset(CCV_PreAuthData.Bitmap06Get141F_Backup, 0u, CCV_PreAuthData.Bitmap06Length);

	}

	return retvalue;

}

uint8 Bitmap06GetSIDProcess_06C0(void)
{
	uint8 retvalue;


	retvalue = lBitmap06Get0622SIDProcess(UserStopCreditData.Bitmap06Get141F_Backup, &UserStopCreditData.Bitmap06Length);
	if(TRUE == retvalue)
	{
		memset(UserStopCreditData.Bitmap06Get141F_Backup, 0u, UserStopCreditData.Bitmap06Length);

	}

	return retvalue;

}

/*
@brief
@details
@para
@return
@note     called by ()
*/
uint8 Bitmap06GetSIDProcessPlusplus_06C0(void)
{
	uint8 retvalue = 0u;


	retvalue = lBitmap06Get06C0_SIDProcess(&UserStopCreditData.Bitmap06Get141F_Backup[0u], &UserStopCreditData.Bitmap06Length);
	if(TRUE == retvalue)
	{
		memset(UserStopCreditData.Bitmap06Get141F_Backup, 0u, UserStopCreditData.Bitmap06Length);

	}

	return retvalue;
}


/*
@brief
@details
@para
@return
@note     called by ()
*/
uint8 Bitmap06GetSIDProcessPlusplus_0622(void)
{
	uint8 retvalue = 0u;


	retvalue = lBitmap06Get06C0_SIDProcess(CCV_PreAuthData.Bitmap06Get141F_Backup, &CCV_PreAuthData.Bitmap06Length);
	if(TRUE == retvalue)
	{
		memset(CCV_PreAuthData.Bitmap06Get141F_Backup, 0u, CCV_PreAuthData.Bitmap06Length);

	}

	return retvalue;
}



/*
@brief
@details
@para
@return
@note     called by ()
*/
uint8 Bitmap06Get_UIDProcess(void)
{
	uint8 retvalue = 0u;

	retvalue = lBitmap06Get06C0_UIDProcess(CCV_MifareData.Bitmap06Get4C0A_Backup, &CCV_MifareData.Bitmap06Length);
	if(TRUE == retvalue)
	{
		memset(CCV_MifareData.Bitmap06Get4C0A_Backup, 0u, CCV_MifareData.Bitmap06Length);
	}

	return retvalue;
}

/*
@brief
@details
@para
@return
*/

zvt_apdu_err_id Zvt_Uint32DivedTo4Uint8Bcd(uint32* u32_data, uint8* u8_data)
{
	uint8 u8ArrayBcd[4u] = { 0u };
	uint8 dataF4,dataF5,dataF6,dataF7;
	uint32 u32_data0;

	u32_data0 = *u32_data;

	if(u32_data0 > 2500u)
	{
		return maximum_amount_exceeded_0xC3;
	}
	else
	{
		memset(u8ArrayBcd, 0u, sizeof(u8ArrayBcd)/sizeof(uint8));

		dataF4 = (uint8)((u32_data0 % 10000) / (1000));		/*qian*/
		dataF5 = (uint8)((u32_data0 % 1000)/(100));			/*bai*/

		dataF6 = (uint8)(u32_data0 / (10));					/*shi*/
		dataF7 = (uint8)(u32_data0 % 10);					/*ge*/

		u8ArrayBcd[0u] = 0u;
		u8ArrayBcd[1u] = 0u;
		u8ArrayBcd[2u] = (dataF5 + (dataF4 << 4u));
		u8ArrayBcd[3u] = (dataF7 + (dataF6 << 4u));

		memcpy(u8_data, u8ArrayBcd, sizeof(u8ArrayBcd)/sizeof(uint8));

//		memcpy(u8ArrayBcd_temp, u8ArrayBcd, sizeof(u8ArrayBcd)/sizeof(uint8));

		return no_error;
	}
}


/*
@brief
@details
@para
@return
@note     called by PtPreAuthorizedProcessA()
*/

 void lPreAuthorized_SendCmd04ffAck(void)
{
	if((Insert_card0x0a == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(PT_Detected_Customer_Card_Insertion0x68 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Please_wait0x17 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Connecting_Dial_Up0xd2 == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
	}
	else if((Approved_Please_fill_up0x1b == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;

	}
	else if((Connecting_Dial_Up0xd2 == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;

	}
	else
	{;}
}


/*
@brief
@details
@para
@return
@note     called by Zvt_PtInitStateMachineProcess()
*/

void lSendCmd04ffAck(void)
{
	if((BeingProcessed_PleaseWait0x0e == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Please_wait0x17 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(PIN_try_limit_exceeded0x18 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Service_Mode_0x1a == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Connecting_Dial_Up0xd2 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Dial_up_connection_made0xd3 == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
	}
}


/*
@brief
@details
@para
@return
@note     called by
*/

 void lPtConfig0813_SendAckCmd(void)
{
	if((BeingProcessed_PleaseWait0x0e == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Please_wait0x17 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Service_Mode_0x1a == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Np_propriate_ZVT_status_code_matches_the_status0xff == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
	}
}


/*
@brief
@details
@para
@return
@note     called by PtPartialReversalProcessA()
*/

void lPartialReversal_SendCmd04ffAck(void)
{
	if((Please_wait0x17 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(PT_send_post_booking0x06 == cmd04ffPayload.cmd04ff_intermediate_status)\
		||(Connecting_Dial_Up0xd2 == cmd04ffPayload.cmd04ff_intermediate_status))
	{
		Zvt_PtTxPositiveAck8000();
		cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
	}
}


/*
@brief
@details
@para
@return 数据格式待定    2*uint8(BCD)  ---> uint16
@note
*/

uint16 lZvt_2Uint8bcdMergeToUint16(uint8* data)
{
	uint8 tempArray[2u] = {0u};
	uint16 ret;
	memcpy(tempArray, data, (sizeof(data))/(sizeof(uint8)));
			/*qian + bai + shi + ge*/
	ret = (((uint16)(tempArray[0] >> 4u))*1000)\
			+ (((uint16)(tempArray[0] & 0xF))*100)\
			+ (((uint16)(tempArray[1] >> 4u))*10)\
			+ ((uint16)(tempArray[1] & 0xF));

	return ret;
}

/*
@brief
@details
@para
@return
*/
uint8 CheckSecureIDisZero(uint8 *sid)
{
	uint8 retvalue = 0u;
	uint8 checksum = 0u;
	uint8 checkLoop = 0u;
	uint8 sidData[PT_SID_LEN] = {0u};


	memcpy(sidData, sid, PT_SID_LEN);

	for(checkLoop = 0u; checkLoop < PT_SID_LEN; checkLoop++)
	{
		if(TRUE == sidData[checkLoop])
		{
			++checksum;
		}
	}

	if(checksum >= PT_SID_LEN)			/*sidData[PT_SID_LEN] = {0u}*/
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}


/*
@brief
@details
@para
@return
*/
uint8 CheckRfidUIDisZero(uint8 *uid)
{
	uint8 retvalue = 0u;
	uint8 checksum = 0u;
	uint8 checkLoop = 0u;
	uint8 uidData[PT_UID_LEN] = {0u};


	memcpy(uidData, uid, PT_UID_LEN);

	for(checkLoop = 0u; checkLoop < PT_UID_LEN; checkLoop++)
	{
		if(TRUE == uidData[checkLoop])
		{
			++checksum;
		}
	}

	if(checksum >= PT_UID_LEN)			/*uidData[PT_UID_LEN] = {0u}*/
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}

/*
@brief
@details
@para
@return
*/
static uint8 lCompareCreditSID(uint8 *startData, uint8* endData)
{
	uint8 retvalue = TRUE;
	uint8 iLoop;
	uint8 matchStartData[PT_SID_LEN];
	uint8 matchEndData[PT_SID_LEN];

	memcpy(matchStartData, startData, PT_SID_LEN);
	memcpy(matchEndData, endData, PT_SID_LEN);

	for(iLoop = 0u; iLoop < PT_SID_LEN; iLoop++)
	{
		if(matchStartData[iLoop] != matchEndData[iLoop])
		{
			retvalue = FALSE;
			break;
		}
	}
	return retvalue;
}
/*
@brief
@details
@para
@return
*/
static uint8 lCompareRfidUID(uint8 *startData, uint8* endData)
{
	uint8 retvalue = TRUE;
	uint8 iLoop;
	uint8 matchStartData[PT_UID_LEN];
	uint8 matchEndData[PT_UID_LEN];

	memcpy(matchStartData, startData, PT_UID_LEN);
	memcpy(matchEndData, endData, PT_UID_LEN);

	for(iLoop = 0u; iLoop < PT_UID_LEN; iLoop++)
	{
		if(matchStartData[iLoop] != matchEndData[iLoop])
		{
			retvalue = FALSE;
			break;
		}
	}
	return retvalue;
}

/*
@brief
@details
@para
@return
*/
void CCV_StateInit(void)
{
    CCV_StateIdleInit();
    CCV_SignalUpdate = CCV_StateIdleUpdate;
    TRAN(&CCV_Parser, CCV_StateIdle);
}


/*
@brief
@details
@para
@return
*/
void CCV_StateIdleInit(void)
{
	//Abort
	//Carpass = FALSE;

	Zvt_WriteRte.ReadCardSuccess_flg = FALSE;
    Zvt_WriteRte.HandleReversalSuccess_flg = FALSE;
    
    Rte_Write_ZVT_CCU1CCVBillHandleOvr_flg(Zvt_WriteRte.HandleReversalSuccess_flg);
    Rte_Write_ZVT_CCU2CCVBillHandleOvr_flg(Zvt_WriteRte.HandleReversalSuccess_flg);
	Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);
    
	Zvt_PtAbort06B0();
}
/*
@brief
@details
@para
@return
*/
void CCV_StateIdleUpdate(void)
{
	debugFlagList.counter9++;
	if(0u == debugFlagList.debugFlag19)
	{
		Zvt_ReadAsw.CCU1_MCVCardType_enum = get_GeEACM_CCU1MCVCardType_enum();
		Zvt_ReadAsw.CCU2_MCVCardType_enum = get_GeEACM_CCU2MCVCardType_enum();

		Zvt_ReadAsw.AGunStart_flg = get_GbEACM_AGunStartCheckForCard_flg();
		Zvt_ReadAsw.BGunStart_flg = get_GbEACM_BGunStartCheckForCard_flg();

		Zvt_ReadAsw.AGunStop_flg = get_GbEACM_AGunUserStopForCard_flg();
		Zvt_ReadAsw.BGunStop_flg = get_GbEACM_BGunUserStopForCard_flg();

		Zvt_ReadAsw.CCU1_AutoFinish_flg = get_GbECEC_CCU1ElectricityCalFinish_flg();
		Zvt_ReadAsw.CCU2_AutoFinish_flg = get_GbECEC_CCU2ElectricityCalFinish_flg();
	}
    
	tmp_ASW_CC_Request = Asw_ZvtDispatch0622PreAuthRequest();

	tmp_ASW_UserStop_Request = Asw_ZvtDispatchUserStopRequest();

	tmp_ASW_CC_Reversal_Request = Asw_ZvtDispatch0623ReversalRequest();

	tmp_ASW_Mifare_Request = Asw_ZvtDispatch06C0MifareRequest();

    tmp_ASW_Config_Request = Asw_ZvtDispatchConfigurationRequest();


    CCV_Signal = CCV_SIG_DEFAULT;

    if(TRUE == tmp_ASW_Config_Request)
    {
        CCV_Signal = CCV_SIG_CONFIG;
    }
    else
    {
        if(User_IpMode == Zvt_PtGetIPMode())
        {
            if(TRUE == tmp_ASW_CC_Request)
            {
                CCV_Signal = CCV_SIG_CREDIT;
            }
            else if(TRUE == tmp_ASW_Mifare_Request)
            {
                CCV_Signal = CCV_SIG_MIFARE;
            }
            else if(TRUE == tmp_ASW_UserStop_Request)
            {
                CCV_Signal = CCV_SIG_USERSTOP;
            }
            else if(TRUE == tmp_ASW_CC_Reversal_Request)
            {
                CCV_Signal = CCV_SIG_CREDIT_REVERSAL;
            }
        }
        else if(Factory_IpMode == Zvt_PtGetIPMode())
        {
            CCV_Signal = CCV_SIG_CONFIG;
        }
    }

}


/*
@brief
@details
@para
@return
*/
void CCV_StateIdle(parser_t *me, signal_t sig)
{
	    switch(sig)
	    {
	    case CCV_SIG_ENTRY :
	        CCV_StateIdleInit();
	        CCV_SignalUpdate = CCV_StateIdleUpdate;
	        me->currentstate = SGUS_STA_IDLE;
	        break;
	    case CCV_SIG_EXIT :
	        me->prestate = SGUS_STA_IDLE;
	        break;
	    case CCV_SIG_CREDIT :
	        TRAN_EE(me, CCV_StateCredit);
	        break;
	    case CCV_SIG_MIFARE :
	        TRAN_EE(me, CCV_StateMifare);
	        break;
	    case CCV_SIG_USERSTOP :
	        TRAN_EE(me, CCV_StateUserStop);
	        break;
	    case CCV_SIG_CREDIT_REVERSAL :
	        TRAN_EE(me, CCV_StateCreditReversal);
	        break;
	    case CCV_SIG_CONFIG :
	        TRAN_EE(me, CCV_StatePtConfig);
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
void CCV_StateCreditInit(void)
{
    //Send 06 C0 for SID/UID
	/*先初始化各种标志位*/

	ZvtCom_Write.CCU1_Set0622PreAut_flg = FALSE;
	ZvtCom_Write.CCU2_Set0622PreAut_flg = FALSE;

	CCV_PreAuthData.PreAuthStep = Send0622Sid_N_OK;
	CCV_PreAuthData.ErrCode = PAY_DEFAULT_ERRID;

	CCV_PreAuthData.getSID = FALSE;
	CCV_PreAuthData.getReceiptNo = FALSE;

	CCV_PreAuthData.CounterStep1 = 0u;
	CCV_PreAuthData.CounterStep2 = 0u;
	CCV_PreAuthData.CounterStep3 = 0u;
	CCV_PreAuthData.CounterStep4 = 0u;

//	memset(&CCV_SID[0][0], 0u , 32u);  /*待定在解析函数中提取  CCU1*/
//	memset(&CCV_SID[1][0], 0u , 32u);  /*待定在解析函数中提取  CCU2*/

	memset(CCV_PreAuthData.SID_0x1F14_32B, 0u, 32u);  /*待定在解析函数中提取  CCU1*/
	memset(CCV_PreAuthData.getCmd040fReceiptNumber0x87, 0u, 2u);
	memset(ZVT_CarSIDValue, 0u , 32u);

    Zvt_ReadAsw.CCU1_PreMoney_rmb = get_GcEACM_PrePayment_rmb();
	Zvt_ReadAsw.CCU2_PreMoney_rmb = get_GcEACM_PrePayment_rmb();

	Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU1_PreMoney_rmb, ZvtCom_Read.CCU1_PreMoney_rmb);
	Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU2_PreMoney_rmb, ZvtCom_Read.CCU2_PreMoney_rmb);

}
/*
@brief
@details
@para
@return
*/
void CCV_StateCreditUpdate(void)
{
	uint8 retvalue = 0u;
	/*step 1,step 2....各种处理*/

 //   volatile uint8_t tmp_ASW_CC_Request = 0;
    //if TRUE == SID, Save SID and Send 06 22
    //if TRUE == 0622
    {
        //if succeed ,ZVT0623SettleAccount_flg = TRUE;
        //else
    }
	if(0u == debugFlagList.debugFlag19)
	{
	    Zvt_ReadAsw.AGunStart_flg = get_GbEACM_AGunStartCheckForCard_flg();
		Zvt_ReadAsw.BGunStart_flg = get_GbEACM_BGunStartCheckForCard_flg();
	}

    if(FALSE == Zvt_ReadAsw.AGunStart_flg && FALSE == Zvt_ReadAsw.BGunStart_flg)
    {
        tmp_ASW_CC_Request = FALSE;
    }
	

    switch(CCV_PreAuthData.PreAuthStep)
    {
		case Send0622Sid_N_OK:

			if(TRUE == Zvt_ReadAsw.AGunStart_flg)
			{
				if((0u != ZvtCom_Read.CCU1_PreMoney_rmb[0u])||(0u != ZvtCom_Read.CCU1_PreMoney_rmb[1u]))
				{
					retvalue = Zvt_PtPreAuthorized0622SID(&ZvtCom_Read.CCU1_PreMoney_rmb[0u]);

				}
				else
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = pre_authorisation_incorrect_or_amount_wrong_0xB7;
					CCV_PreAuthData.PreAuthStep = PreAuthorize_Over;
				}

			}
			else
			{
				CCV_PreAuthData.PreAuthStep = Send0622Sid_N_OK;
			}

			if(TRUE == Zvt_ReadAsw.BGunStart_flg)
			{
				if((0u != ZvtCom_Read.CCU2_PreMoney_rmb[0u])||(0u != ZvtCom_Read.CCU2_PreMoney_rmb[1u]))
				{
					retvalue = Zvt_PtPreAuthorized0622SID(&ZvtCom_Read.CCU2_PreMoney_rmb[0u]);

				}
				else
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = pre_authorisation_incorrect_or_amount_wrong_0xB7;
					CCV_PreAuthData.PreAuthStep = PreAuthorize_Over;
				}
			}
			else
			{
				CCV_PreAuthData.PreAuthStep = Send0622Sid_N_OK;
			}


			if(ZVT_RET_OK == retvalue)
			{
				CCV_PreAuthData.PreAuthStep = Send0622Sid_OK;
			}

			CCV_PreAuthData.CounterStep1++;

			break;

		case Send0622Sid_OK:


			if(TRUE == CCV_PreAuthData.getReceiptNo)
			{

				if((0u != CCV_PreAuthData.getCmd040fReceiptNumber0x87[0u])\
					||(0u != CCV_PreAuthData.getCmd040fReceiptNumber0x87[1u]))
				{
					Zvt_PtTxPositiveAck8000();

					if(TRUE == Zvt_ReadAsw.AGunStart_flg)
					{
						memcpy(ZvtCom_Write.CCU1_SetCCVCreditCardReceipt_numb,\
							   CCV_PreAuthData.getCmd040fReceiptNumber0x87,\
							   2u);

						memcpy(ZvtCom_Read.LeftCreditCardReceipt_numb,\
							   CCV_PreAuthData.getCmd040fReceiptNumber0x87,\
							   2u);

						Zvt_ReceiptUint8BcdConvert2Uint16(ZvtCom_Write.CCU1_SetCCVCreditCardReceipt_numb, &Zvt_WriteRte.SetCCVCreditCardReceipt);
						Rte_Write_ZVT_CarReceipt_Value(Zvt_WriteRte.SetCCVCreditCardReceipt);
					}

					if(TRUE == Zvt_ReadAsw.BGunStart_flg)
					{
						memcpy(ZvtCom_Write.CCU2_SetCCVCreditCardReceipt_numb,\
							   CCV_PreAuthData.getCmd040fReceiptNumber0x87,\
							   2u);

						memcpy(ZvtCom_Read.RightCreditCardReceipt_numb,\
							   CCV_PreAuthData.getCmd040fReceiptNumber0x87,\
							   2u);

						Zvt_ReceiptUint8BcdConvert2Uint16(ZvtCom_Write.CCU2_SetCCVCreditCardReceipt_numb, &Zvt_WriteRte.SetCCVCreditCardReceipt);
						Rte_Write_ZVT_CarReceipt_Value(Zvt_WriteRte.SetCCVCreditCardReceipt);
					}

					CCV_PreAuthData.PreAuthStep = Waitfor_0622SID;
					CCV_PreAuthData.getReceiptNo = FALSE;

				}
				else
				{
					CCV_PreAuthData.getReceiptNo = FALSE;
					CCV_PreAuthData.PreAuthStep = Send0622Sid_OK;		/*repeat again*/
				}
			}

			CCV_PreAuthData.CounterStep2++;
			if(CCV_PreAuthData.CounterStep2 > 1500u)	/*wait for 15s*/
			{
				CCV_PreAuthData.CounterStep2 = 0u;
				CCV_PreAuthData.PreAuthStep = PreAuthorize_OverTime;

				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}
			}

			break;
		case Waitfor_0622SID:

			Bitmap06GetSIDProcess_0622();

			if(TRUE == CCV_PreAuthData.getSID)
			{
				CCV_PreAuthData.PreAuthStep = PreAuthorize_OK;
			}
			else
			{
				CCV_PreAuthData.PreAuthStep = Waitfor_0622SID;
			}

			CCV_PreAuthData.CounterStep3++;
			if(CCV_PreAuthData.CounterStep3 > 1500u)	/*wait for 15s*/
			{
				CCV_PreAuthData.CounterStep3 = 0u;
				CCV_PreAuthData.PreAuthStep = PreAuthorize_OverTime;

				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}
			}

			break;

		case PreAuthorize_OK:


			if(TRUE == CCV_PreAuthData.getSID)
			{
				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					memcpy(ZvtCom_Read.LeftStartCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);
					memcpy(ZvtCom_Write.CCU1_SetCCVCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);

					memcpy(Zvt_WriteRte.SetCCVCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);
					memcpy(ZVT_CarSIDValue, Zvt_WriteRte.SetCCVCreditCardSID_numb, 32u);


					memset(CCV_PreAuthData.getCmd040fReceiptNumber0x87, 0u, 2u);
					memset(CCV_PreAuthData.SID_0x1F14_32B, 0u, PT_SID_LEN);

					ZvtCom_Write.CCU1_SetCCVFault_enum = no_error;
					ZvtCom_Write.CCU1_Set0622PreAut_flg = PreAuth_OK;

					Zvt_WriteRte.ReadCardSuccess_flg = TRUE;

					CCV_PreAuthData.getSID = FALSE;
					CCV_PreAuthData.PreAuthStep = PreAuthorize_Over;
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					memcpy(ZvtCom_Read.RightStartCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);
					memcpy(ZvtCom_Write.CCU2_SetCCVCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);

					memcpy(Zvt_WriteRte.SetCCVCreditCardSID_numb, CCV_PreAuthData.SID_0x1F14_32B, PT_SID_LEN);
					memcpy(ZVT_CarSIDValue, Zvt_WriteRte.SetCCVCreditCardSID_numb, 32u);

					memset(CCV_PreAuthData.getCmd040fReceiptNumber0x87, 0u, 2u);
					memset(CCV_PreAuthData.SID_0x1F14_32B, 0u, PT_SID_LEN);

					ZvtCom_Write.CCU2_SetCCVFault_enum = no_error;
					ZvtCom_Write.CCU2_Set0622PreAut_flg = PreAuth_OK;
					Zvt_WriteRte.ReadCardSuccess_flg = TRUE;

					CCV_PreAuthData.getSID = FALSE;
					CCV_PreAuthData.PreAuthStep = PreAuthorize_Over;
				}
                Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);
			}

			/*timeout*/
			CCV_PreAuthData.CounterStep4++;
			if(CCV_PreAuthData.CounterStep4 > 3000u)	/*wait for 30s*/
			{
				CCV_PreAuthData.CounterStep4 = 0u;
				CCV_PreAuthData.PreAuthStep = PreAuthorize_OverTime;

				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = CCV_PreAuthData.ErrCode;
				}
			}

			break;

		case PreAuthorize_Over:

			if(1u == debugFlagList.debugFlag20)
			{
				Zvt_ReadAsw.AGunStart_flg = FALSE;
				Zvt_ReadAsw.BGunStart_flg = FALSE;
			}
			break;

		case PreAuthorize_OverTime:

			if(1u == debugFlagList.debugFlag20)
			{
				Zvt_ReadAsw.AGunStart_flg = FALSE;
				Zvt_ReadAsw.BGunStart_flg = FALSE;
			}
			break;

		default :
			break;

    }

    /* tmp_ASW_CC_Request = Rte_Read_ZVT_CCU1_ZVT0622PreAut_flg(uint8 _temp)*/
    CCV_Signal = CCV_SIG_DEFAULT;
    if(FALSE == tmp_ASW_CC_Request)
    {
        CCV_Signal = CCV_SIG_BACK;
    }
}

/*
@brief
@details
@para
@return
*/
void CCV_StateCredit(parser_t *me, signal_t sig)
{
    switch(sig)
    {
    case CCV_SIG_ENTRY :
        CCV_StateCreditInit();
        CCV_SignalUpdate = CCV_StateCreditUpdate;
        me->currentstate = SGUS_STA_CREDIT;
        break;
    case CCV_SIG_EXIT :
        me->prestate = SGUS_STA_CREDIT;
        break;
    case CCV_SIG_BACK :
        TRAN_EE(me, CCV_StateIdle);
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
void CCV_StateUserStopInit(void)
{
    //Send 06 C0

	UserStopCreditData.TimeOutCounter = 0u;
	UserStopCreditData.TimeOutWaitAckCounter = 0u;
	UserStopCreditData.UserSend0623Counter = 0u;
	UserStopCreditData.TimeOutArrivedAckCounter = 0u;
	UserStopCreditData.WaitforTx0623Counter = 0u;
	UserStopCreditData.WaitforTx0623DefaultCounter = 1000u;
	UserStopCreditData.TimeOutDefaultCounter = 4500u;

	UserStopCreditData.TimeOutWaitUidCounter = 0u;
	UserStopCreditData.TimeOutArrivedUidCounter = 0u;
	UserStopCreditData.getSID = FALSE;
	UserStopCreditData.ErrCode = PAY_DEFAULT_ERRID;

	CCV_MifareData.getUID = FALSE;
	memset(UserStopCreditData.SID_0x1F14_32B, 0u, PT_SID_LEN);
	memset(UserStopCreditData.rxCmd040fReceiptNumber0x87, 0u ,2u);
	memset(CCV_MifareData.UID_0x4C0A_10B, 0u, PT_UID_LEN);

	ZvtCom_Write.CCU1_Set06C0CardSID_flg = FALSE;
	ZvtCom_Write.CCU2_Set06C0CardSID_flg = FALSE;
	ZvtCom_Write.CCU1_Set0623SettleAccount_flg = FALSE;
	ZvtCom_Write.CCU2_Set0623SettleAccount_flg = FALSE;

	ZvtCom_Write.CCU1_SetCCVFault_enum = PAY_DEFAULT_ERRID;
	ZvtCom_Write.CCU2_SetCCVFault_enum = PAY_DEFAULT_ERRID;

	if((CreditCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)\
	 ||(CreditCard == Zvt_ReadAsw.CCU2_MCVCardType_enum))
	{
		UserStopCreditData.UserStopStep = Waitfor_UserSID;
	}

	if((RfidCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)\
	 ||(RfidCard == Zvt_ReadAsw.CCU2_MCVCardType_enum))
	{
		UserStopCreditData.UserStopStep = UserSend06C0_RfidUID;
	}
}

/*
@brief
@details
@para
@return
*/
void CCV_StateUserStopUpdate(void)
{
	uint8 retvalue = 0u;

	//    volatile uint8_t tmp_ASW_UserStop_Request = 0;
    //if Succeed
    {
        //if SID Same as CCV_SID
    }
	if(0u == debugFlagList.debugFlag19)
	{
	    Zvt_ReadAsw.AGunStop_flg = get_GbEACM_AGunUserStopForCard_flg();
		Zvt_ReadAsw.BGunStop_flg = get_GbEACM_BGunUserStopForCard_flg();
	}

    if(FALSE == Zvt_ReadAsw.AGunStop_flg && FALSE == Zvt_ReadAsw.BGunStop_flg)
    {
        tmp_ASW_UserStop_Request = FALSE;
    }
            

    switch(UserStopCreditData.UserStopStep)
    {
    	/**************************Rfid Card************************/
    	case UserSend06C0_RfidUID:
			if(0u == (UserStopCreditData.TimeOutWaitUidCounter % 800u))  /*per 8s repeat one time*/
			{
				Zvt_PtReadCard06C0UID();
			}

			if(TRUE == Zvt_PtCheckReceive8000Ack())      				/*Transmit 06C0 successfully*/
			{
				UserStopCreditData.UserStopStep = Waitfor_RfidUID;
			}

			UserStopCreditData.TimeOutWaitUidCounter++;

			if(UserStopCreditData.TimeOutWaitUidCounter > 8000u)  /*80s*/
			{
				UserStopCreditData.TimeOutWaitUidCounter = 0u;
				Zvt_WriteRte.ReadCardSuccess_flg = FALSE;

				UserStopCreditData.UserStopStep = UserStop_Over;
			}

    		break;

    	case Waitfor_RfidUID:

			Bitmap06Get_UIDProcess();

			if(TRUE == CCV_MifareData.getUID)
			{
				Zvt_PtTxPositiveAck8000();

		    	retvalue = CheckRfidUIDisZero(&CCV_MifareData.UID_0x4C0A_10B[0u]);

				if(TRUE == retvalue)
				{
			    	CCV_MifareData.getUID = FALSE;
					Zvt_PtAbort06B0();
					UserStopCreditData.UserStopStep = Check_RfidUID;
				}
			}

			UserStopCreditData.TimeOutArrivedUidCounter++;

			if(UserStopCreditData.TimeOutArrivedUidCounter > 8000u)  /*80s*/
			{
				Zvt_PtAbort06B0();

				UserStopCreditData.TimeOutArrivedUidCounter = 0u;
				Zvt_WriteRte.ReadCardSuccess_flg = FALSE;

				UserStopCreditData.UserStopStep = UserStop_Over;
			}

    		break;

    	case Check_RfidUID:

			if(TRUE == Zvt_ReadAsw.AGunStop_flg)
			{
	        	retvalue = lCompareRfidUID(ZvtCom_Read.LeftRFIDCardUID_numb ,CCV_MifareData.UID_0x4C0A_10B);

				if(TRUE == retvalue)
				{
//					memcpy(ZVT_CarIDValue, CCV_MifareData.UID_0x4C0A_10B, 10u);

//					memset(ZvtCom_Read.LeftRFIDCardUID_numb, 0u, PT_UID_LEN);
//					memset(CCV_MifareData.UID_0x4C0A_10B, 0u, PT_UID_LEN);

					Zvt_WriteRte.ReadCardSuccess_flg = TRUE;

					UserStopCreditData.UserStopStep = UserStop_Over;
				}
			}

			if(TRUE == Zvt_ReadAsw.BGunStop_flg)
			{
	        	retvalue = lCompareRfidUID(ZvtCom_Read.RightRFIDCardUID_numb ,CCV_MifareData.UID_0x4C0A_10B);

				if(TRUE == retvalue)
				{
//					memcpy(ZVT_CarIDValue, CCV_MifareData.UID_0x4C0A_10B, 10u);

//					memset(ZvtCom_Read.RightRFIDCardUID_numb, 0u, PT_UID_LEN);
//					memset(CCV_MifareData.UID_0x4C0A_10B, 0u, PT_UID_LEN);

					Zvt_WriteRte.ReadCardSuccess_flg = TRUE;

					UserStopCreditData.UserStopStep = UserStop_Over;
				}
			}

    		break;

    		/**************************Credit Card************************/
        case Waitfor_UserSID:

			if(0u == (UserStopCreditData.TimeOutWaitAckCounter % 800u))  /*per 8s repeat one time*/
			{
				Zvt_PtReadCard06C0SID();
			}

			if(TRUE == Zvt_PtCheckReceive8000Ack())      				/*Transmit 06C0 successfully*/
			{
				UserStopCreditData.UserStopStep = Arrived_UserSID;
			}

			UserStopCreditData.TimeOutWaitAckCounter++;

			if(UserStopCreditData.TimeOutWaitAckCounter > 8000u)  /*80s*/
			{
				UserStopCreditData.TimeOutWaitAckCounter = 0u;
				UserStopCreditData.UserStopStep = UserStop_Over;
			}


			break;

        case Arrived_UserSID:


	    	Bitmap06GetSIDProcessPlusplus_06C0();


		    if(TRUE == UserStopCreditData.getSID)
			{
				Zvt_PtTxPositiveAck8000();

		    	retvalue = CheckSecureIDisZero(&UserStopCreditData.SID_0x1F14_32B[0u]);

				if((TRUE == retvalue)&&(TRUE == Zvt_ReadAsw.AGunStop_flg))
				{
			    	memcpy(&CCV_SID[0][0], UserStopCreditData.SID_0x1F14_32B, PT_SID_LEN);  /*待定在解析函数中提取  CCU1*/
			    	memcpy(ZvtCom_Read.LeftEndCreditCardSID_numb, UserStopCreditData.SID_0x1F14_32B, PT_SID_LEN);

			    	UserStopCreditData.getSID = FALSE;
					retvalue = Zvt_PtAbort06B0();

					if(ZVT_RET_OK == retvalue)
					{
						UserStopCreditData.UserStopStep = Check_UserSID;
				    	memset(UserStopCreditData.SID_0x1F14_32B, 0u, PT_SID_LEN);
					}

				}

				else if((TRUE == retvalue)&&(TRUE == Zvt_ReadAsw.BGunStop_flg))
				{
			    	memcpy(&CCV_SID[1][0], UserStopCreditData.SID_0x1F14_32B, PT_SID_LEN);  /*待定在解析函数中提取  CCU2*/
			    	memcpy(ZvtCom_Read.RightEndCreditCardSID_numb, UserStopCreditData.SID_0x1F14_32B, PT_SID_LEN);

			    	UserStopCreditData.getSID = FALSE;
					retvalue = Zvt_PtAbort06B0();

					if(ZVT_RET_OK == retvalue)
					{
						UserStopCreditData.UserStopStep = Check_UserSID;
				    	memset(UserStopCreditData.SID_0x1F14_32B, 0u, PT_SID_LEN);
					}
				}
			}

		    /*timeout*/
		    UserStopCreditData.TimeOutArrivedAckCounter++;
		    if(UserStopCreditData.TimeOutArrivedAckCounter > 8000u)  /*80s*/
			{
		    	UserStopCreditData.TimeOutArrivedAckCounter = 0u;
				UserStopCreditData.UserStopStep = UserStop_Over;
			}


		    break;

        case Check_UserSID:

			if(TRUE == Zvt_ReadAsw.AGunStop_flg)
			{
	        	retvalue = lCompareCreditSID(ZvtCom_Read.LeftStartCreditCardSID_numb ,ZvtCom_Read.LeftEndCreditCardSID_numb);

				if(TRUE == retvalue)
				{
					UserStopCreditData.UserStopStep = UserStop_Over;
                    Zvt_WriteRte.ReadCardSuccess_flg = TRUE;
				}

			}

			if(TRUE == Zvt_ReadAsw.BGunStop_flg)
			{
	        	retvalue = lCompareCreditSID(ZvtCom_Read.RightStartCreditCardSID_numb ,ZvtCom_Read.RightEndCreditCardSID_numb);

				if(TRUE == retvalue)
				{
					UserStopCreditData.UserStopStep = UserStop_Over;
                    Zvt_WriteRte.ReadCardSuccess_flg = TRUE;
				}

			}

        	break;

        case UserStop_Over:

    		if(1u == debugFlagList.debugFlag20)
    		{
				Zvt_ReadAsw.AGunStop_flg = FALSE;
				Zvt_ReadAsw.BGunStop_flg = FALSE;
    		}
            Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);
        	break;

        default:
        	break;

    }

    CCV_Signal = CCV_SIG_DEFAULT;
    if(FALSE == tmp_ASW_UserStop_Request)
    {
        CCV_Signal = CCV_SIG_BACK;
    }
}

/*
@brief
@details
@para
@return
*/
void CCV_StateUserStop(parser_t *me, signal_t sig)
{
    switch(sig)
    {
    case CCV_SIG_ENTRY :
        CCV_StateUserStopInit();
        CCV_SignalUpdate = CCV_StateUserStopUpdate;
        me->currentstate = SGUS_STA_USERSTOP;
        break;
    case CCV_SIG_EXIT :
        me->prestate = SGUS_STA_USERSTOP;
        break;
    case CCV_SIG_BACK :
        TRAN_EE(me, CCV_StateIdle);
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
void CCV_StateCreditReversalInit(void)
{
    //Send 06 23

	CCV_PartReverData.ErrCode = PAY_DEFAULT_ERRID;
	ZvtCom_Write.CCU1_SetCCVFault_enum = PAY_DEFAULT_ERRID;
	ZvtCom_Write.CCU2_SetCCVFault_enum = PAY_DEFAULT_ERRID;

	CCV_PartReverData.TimeOutWaitAckCounter = 0u;
	CCV_PartReverData.TimeOutCounter = 0u;
	CCV_PartReverData.TimeOutDefaultCounter = 6000u;  /*60s*/
	CCV_PartReverData.ReversalStep = ReversalSend0623_N_OK;

	memset(CCV_PartReverData.rxCmd040fReceiptNumber0x87, 0u, 2u);

	ZvtCom_Write.CCU1_Set0623SettleAccount_flg = FALSE;
	ZvtCom_Write.CCU2_Set0623SettleAccount_flg = FALSE;

    Zvt_ReadAsw.CCU1_RemainMoney_rmb = Zvt_ReadAsw.CCU1_PreMoney_rmb - get_GcECEC_CCU1ElectricityRate_rmb();
	Zvt_ReadAsw.CCU2_RemainMoney_rmb = Zvt_ReadAsw.CCU2_PreMoney_rmb - get_GcECEC_CCU2ElectricityRate_rmb();

	Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU1_RemainMoney_rmb, ZvtCom_Read.CCU1_RemainMoney_rmb);
	Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU2_RemainMoney_rmb, ZvtCom_Read.CCU2_RemainMoney_rmb);
}

/*
@brief
@details
@para
@return
*/
void CCV_StateCreditReversalUpdate(void)
{
	uint8 retvalue = 0u;
//    volatile uint8_t tmp_ASW_CC_Reversal_Request = 0;
	if(0u == debugFlagList.debugFlag19)
	{
	    Zvt_ReadAsw.CCU1_AutoFinish_flg = get_GbECEC_CCU1ElectricityCalFinish_flg();
	    Zvt_ReadAsw.CCU2_AutoFinish_flg = get_GbECEC_CCU2ElectricityCalFinish_flg();
	}

	if((FALSE == Zvt_ReadAsw.CCU1_AutoFinish_flg) &&\
       (FALSE == Zvt_ReadAsw.CCU2_AutoFinish_flg))
    {tmp_ASW_CC_Reversal_Request = FALSE;}

	switch(CCV_PartReverData.ReversalStep)
	{
		case ReversalSend0623_N_OK:

			debugFlagList.counter6++;

			if(CCV_PartReverData.TimeOutWaitAckCounter < 8000u)   /*80s*/
			{
				if(0u == (CCV_PartReverData.TimeOutWaitAckCounter % 800u))  /*per 8s repeat one time*/
				{
					if(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)
					{
						retvalue = Zvt_PtReturnRemainingAmount0623(ZvtCom_Read.LeftCreditCardReceipt_numb, ZvtCom_Read.CCU1_RemainMoney_rmb);
					}

					else if(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)
					{
						retvalue = Zvt_PtReturnRemainingAmount0623(ZvtCom_Read.RightCreditCardReceipt_numb, ZvtCom_Read.CCU2_RemainMoney_rmb);
					}
				}


				if(TRUE == Zvt_PtCheckReceive8000Ack())
				{
					CCV_PartReverData.ReversalStep = ReversalSend0623_OK;

					debugFlagList.counter6 = 0u;
				}
				else
				{
					CCV_PartReverData.ReversalStep = ReversalSend0623_N_OK;   /*repeat send 06 23 again*/
				}

				CCV_PartReverData.TimeOutWaitAckCounter++;
			}
			else
			{
				CCV_PartReverData.ReversalStep = ReversalStep_Over;
			}


			break;

		case ReversalSend0623_OK:

			lPartialReversal_SendCmd04ffAck();

			debugFlagList.counter5++;

			CCV_PartReverData.TimeOutCounter++;




			if((no_error == CCV_PartReverData.ErrCode))
			{
				if(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = CCV_PartReverData.ErrCode;

					ZvtCom_Write.CCU1_Set0623SettleAccount_flg = Reversal_OK;
					CCV_PartReverData.ReversalStep = ReversalStep_Over;
					Zvt_WriteRte.HandleReversalSuccess_flg = TRUE;
				}

				if(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = CCV_PartReverData.ErrCode;

					ZvtCom_Write.CCU2_Set0623SettleAccount_flg = Reversal_OK;
					CCV_PartReverData.ReversalStep = ReversalStep_Over;
				}

			}

			if((0 != CCV_PartReverData.rxCmd040fReceiptNumber0x87[0u])\
			 ||(0 != CCV_PartReverData.rxCmd040fReceiptNumber0x87[1u]))
			{
				if(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)
				{
					ZvtCom_Write.CCU1_Set0623SettleAccount_flg = Reversal_OK;
					Zvt_WriteRte.HandleReversalSuccess_flg = TRUE;

					CCV_PartReverData.ReversalStep = ReversalStep_Over;

				}

				if(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)
				{
					ZvtCom_Write.CCU2_Set0623SettleAccount_flg = Reversal_OK;

					CCV_PartReverData.ReversalStep = ReversalStep_Over;
					Zvt_WriteRte.HandleReversalSuccess_flg = TRUE;
				}
			}


			if(CCV_PartReverData.TimeOutCounter > CCV_PartReverData.TimeOutDefaultCounter)  /*60s*/
			{
				CCV_PartReverData.TimeOutCounter = 0u;
				CCV_PartReverData.ReversalStep = ReversalStep_Over;

				if(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = CCV_PartReverData.ErrCode;
				}

				if(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = CCV_PartReverData.ErrCode;
				}
			}


			break;

		case ReversalStep_Over:

			if(1u == debugFlagList.debugFlag20)
			{
				Zvt_ReadAsw.CCU1_AutoFinish_flg = FALSE;
				Zvt_ReadAsw.CCU2_AutoFinish_flg = FALSE;
			}
            if(TRUE == Zvt_WriteRte.HandleReversalSuccess_flg)
            {
                if(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg)
                {
                    Rte_Write_ZVT_CCU1CCVBillHandleOvr_flg(Zvt_WriteRte.HandleReversalSuccess_flg);
                }
                else if(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)
                {
                    Rte_Write_ZVT_CCU2CCVBillHandleOvr_flg(Zvt_WriteRte.HandleReversalSuccess_flg);
                }
            }

			break;

		default:

			break;

	}
    CCV_Signal = CCV_SIG_DEFAULT;

    if(FALSE == tmp_ASW_CC_Reversal_Request)
    {
        CCV_Signal = CCV_SIG_BACK;
    }
}

/*
@brief
@details
@para
@return
*/
void CCV_StateCreditReversal(parser_t *me, signal_t sig)
{
    switch(sig)
    {
    case CCV_SIG_ENTRY :
        CCV_StateCreditReversalInit();
        CCV_SignalUpdate = CCV_StateCreditReversalUpdate;
        me->currentstate = SGUS_STA_CREDITREVERSAL;
        break;
    case CCV_SIG_EXIT :
        me->prestate = SGUS_STA_CREDITREVERSAL;
        break;
    case CCV_SIG_BACK :
        TRAN_EE(me, CCV_StateIdle);
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
void CCV_StatePtConfigInit(void)
{
#if DEBUG_PHASE
				PtConfigData.ConfigStep = User0600;
#else
				PtConfigData.ConfigStep = Factory0600;
#endif

	if(0u == debugFlagList.debugFlag18)
	{
		PtConfigData.ConfigStep = User0600;
	}

	if(1u == debugFlagList.debugFlag18)
	{
		PtConfigData.ConfigStep = Factory0600;

		IpModeFlag = Factory_IpMode;
	}

	PtConfigData.Cfg0813Factory_Times = 0u;
	PtConfigData.Cfg0813User_Times = 0u;
	PtConfigData.Cfg0693_Times = 0u;
	PtConfigData.Cfg0670Emv_Times = 0u;

	PtConfig0813FactoryData.Factory0813Step = 0u;
	PtConfig0813UserData.User0813Step = 0u;
	PtInit0693Data.Init0693Step = 0u;
	PtDiag0670EmvData.Diag0670EmvStep = 0u;

	PtConfig0813FactoryData.Factory0813_DefaultCounter = 15000u;  		/*  Counter x 10ms = 150s*/
	PtConfig0813UserData.User0813_DefaultCounter = 15000u;  			/*150s*/
	PtConfig0813FactoryData.Factory0813CheckTID_DefaultCounter = 900u;  /*9s*/
	PtConfig0813UserData.User0813CheckTID_DefaultCounter = 900u;		/*9s*/
	PtConfig0813FactoryData.Factory0813CheckIP_DefaultCounter = 3000u;	/*30s*/

	PtInit0693Data.PtInitialisation0693_DefaultCounter = 4500u;    		/*Counter x 10ms = 45s*/
	PtDiag0670EmvData.Diag0670Emv_DefaultCounter = 4500u;    			/*45s*/

	memset(PtConfig0813FactoryData.Factory0813_getCmd060fTID, 0u ,4u);
	memset(PtConfig0813UserData.User0813_getCmd060fTID, 0u ,4u);

	PtInit0693Data.Init0693Get061eErrCode = Default_NullCode;
	PtDiag0670EmvData.Diag0670EmvGet061eErrCode =  Default_NullCode;

	memset(PtConfigData.Cfg0693_RecordErrID, 0u, PT_CFG_MAX_TIMES);
	memset(PtConfigData.Cfg0670Emv_RecordErrID, 0u, PT_CFG_MAX_TIMES);
}

/*
@brief
@details
@para
@return
*/
void CCV_StatePtConfigUpdate(void)
{
	uint8 retvalue = FALSE;

	switch(PtConfigData.ConfigStep)
	{
		case Factory0600:

			retvalue = Zvt_PtFactoryRegistration0600();
			if(TRUE == retvalue)
			{
				retvalue = FALSE;
				PtConfigData.ConfigStep = Factory0813;
			}

			break;

		case User0600:

			retvalue = Zvt_PtUserRegistration0600();
			if(TRUE == retvalue)
			{
				retvalue = FALSE;
				PtConfigData.ConfigStep = User0813;
			}

			break;

		case Factory0813:

				switch(PtConfig0813FactoryData.Factory0813Step)
				{
					case SendFactory0813:
						retvalue = Zvt_PtFactoryConfiguration0813(ZvtCom_Read.PtCfg_TidNo,\
																  ZvtCom_Read.PtCfg_IpAddr,\
																  ZvtCom_Read.PtCfg_IpNetmask,\
																  ZvtCom_Read.PtCfg_IpGateway);

						if(TRUE == retvalue)
						{
							retvalue = FALSE;
							PtConfig0813FactoryData.Factory0813Step = DelayFactory0813;
						}
						break;

					case DelayFactory0813:

						lPtConfig0813_SendAckCmd();
						PtConfig0813FactoryData.Factory0813_Counter++;

						if(PtConfig0813FactoryData.Factory0813_Counter > PtConfig0813FactoryData.Factory0813_DefaultCounter)			/*about 180s*/
						{
							lAswTcpDataConverter_UserIP(ZvtCom_Read.PtCfg_IpAddr, CCV_POS_RemoteAddress.addr);
							PtConfig0813FactoryData.Factory0813Step = CheckCennection;
							IpModeFlag = User_IpMode;
						}

						break;

					case CheckCennection:

						if( 0u == (PtConfig0813FactoryData.Factory0813CheckIP_Counter % 300u))		/*3s*/
						{
							Zvt_PtUserIpStatusEnquiry0501();
						}

						if(TRUE == Zvt_PtCheckReceive8000Ack())
						{
							retvalue = Zvt_PtUserRegistration0600();

							if(TRUE == retvalue)
							{
								retvalue = FALSE;
								PtConfig0813FactoryData.Factory0813CheckIP_Counter = 0u;
								PtConfig0813FactoryData.Factory0813Step = WaitforTID;

							}

						}

						/*timeout*/
						PtConfig0813FactoryData.Factory0813CheckIP_Counter++;

						if(PtConfigData.Cfg0813Factory_Times < PT_CFG_MAX_TIMES)
						{
							if(PtConfig0813FactoryData.Factory0813CheckIP_Counter > PtConfig0813FactoryData.Factory0813CheckIP_DefaultCounter)
							{
								PtConfig0813FactoryData.Factory0813CheckIP_Counter = 0u;
								PtConfigData.ConfigStep = Factory0600;
								PtConfig0813FactoryData.Factory0813Step = SendFactory0813;
								IpModeFlag = Factory_IpMode;
								PtConfigData.Cfg0813Factory_Times++;
							}
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_Factory0813Err;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}


						break;


					case WaitforTID:

						if((0u != PtConfig0813FactoryData.Factory0813_getCmd060fTID[0u])\
						 ||(0u != PtConfig0813FactoryData.Factory0813_getCmd060fTID[1u])\
						 ||(0u != PtConfig0813FactoryData.Factory0813_getCmd060fTID[2u])\
						 ||(0u != PtConfig0813FactoryData.Factory0813_getCmd060fTID[3u]))
						{
							PtConfig0813FactoryData.Factory0813CheckTID_Counter = 0u;
							PtConfig0813FactoryData.Factory0813Step = SendFactory0813;
							PtConfigData.ConfigStep = User0693;
							IpModeFlag = User_IpMode;
							PtConfigData.Cfg0813Factory_Times++;
						}

						PtConfig0813FactoryData.Factory0813CheckTID_Counter++;

						if(PtConfigData.Cfg0813Factory_Times < PT_CFG_MAX_TIMES)
						{
							if(PtConfig0813FactoryData.Factory0813CheckTID_Counter > PtConfig0813FactoryData.Factory0813CheckTID_DefaultCounter)
							{
								PtConfig0813FactoryData.Factory0813CheckTID_Counter = 0u;
								PtConfigData.ConfigStep = Factory0600;
								PtConfig0813FactoryData.Factory0813Step = SendFactory0813;
								IpModeFlag = Factory_IpMode;
								PtConfigData.Cfg0813Factory_Times++;

							}
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_Factory0813Err;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}


						break;

					default:
						break;
				}

			break;

		case User0813:

				switch(PtConfig0813UserData.User0813Step)
				{
					case 0:
						retvalue = Zvt_PtUserConfiguration0813(ZvtCom_Read.PtCfg_TidNo,\
															   ZvtCom_Read.PtCfg_IpAddr,\
															   ZvtCom_Read.PtCfg_IpNetmask,\
															   ZvtCom_Read.PtCfg_IpGateway);

						if(TRUE == retvalue)
						{
							PtConfig0813UserData.User0813Step = 1u;
						}
						break;

					case 1:

						lPtConfig0813_SendAckCmd();

						if(PtConfig0813UserData.User0813_Counter > PtConfig0813UserData.User0813_DefaultCounter)			/*about 180s*/
						{

							retvalue = Zvt_PtUserRegistration0600();     /*Check TID*/
							if(TRUE == retvalue)
							{
								retvalue = FALSE;
								PtConfig0813UserData.User0813_Counter = 0u;
								PtConfig0813UserData.User0813Step = 2u;
							}
						}

						PtConfig0813UserData.User0813_Counter++;

						break;

					case 2:

						if((0u != PtConfig0813UserData.User0813_getCmd060fTID[0u])\
						 ||(0u != PtConfig0813UserData.User0813_getCmd060fTID[1u])\
						 ||(0u != PtConfig0813UserData.User0813_getCmd060fTID[2u])\
						 ||(0u != PtConfig0813UserData.User0813_getCmd060fTID[3u]))
						{
							PtConfig0813UserData.User0813Step = 3u;
						}

						if(PtConfig0813UserData.User0813CheckTID_Counter > PtConfig0813UserData.User0813CheckTID_DefaultCounter)
						{
							PtConfig0813UserData.User0813CheckTID_Counter = 0u;
							PtConfig0813UserData.User0813Step = 4u;
						}

						PtConfig0813UserData.User0813CheckTID_Counter++;

						break;

					case 3:

						if(PtConfigData.Cfg0813User_Times < PT_CFG_MAX_TIMES)
						{
							PtConfigData.Cfg0813User_Times++;
							PtConfigData.ConfigStep = User0693;
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0813Err;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}

						break;

					case 4:

						if(PtConfigData.Cfg0813User_Times < PT_CFG_MAX_TIMES)
						{
							PtConfigData.Cfg0813User_Times++;
							PtConfigData.ConfigStep = User0813;
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0813Err;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}

						break;

					default:
						break;
				}

			break;

		case User0693:
			switch(PtInit0693Data.Init0693Step)
			{
				case 0:
					retvalue = Zvt_PtInitilisation0693();
					if(TRUE == retvalue)
					{
						PtInit0693Data.Init0693Step = 1u;
					}

					break;

				case 1:

					lSendCmd04ffAck();

					if(PtConfigData.Cfg0693_Times < PT_CFG_MAX_TIMES)
					{
						PtInit0693Data.PtInitialisation0693_Counter++;

						if(PtInit0693Data.PtInitialisation0693_Counter > PtInit0693Data.PtInitialisation0693_DefaultCounter)		/*about 45s*/
						{
							PtInit0693Data.PtInitialisation0693_Counter = 0u;

							PtInit0693Data.Init0693Step = 0u;
							PtConfigData.ConfigStep = User0670emv;
							PtConfigData.Cfg0693_Times++;
						}
					}
					else
					{
						ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0693Err;
						PtConfigData.ConfigStep = PtConfig_TimeOut;
					}


					if((no_error != PtInit0693Data.Init0693Get061eErrCode)\
					&& ((Default_NullCode != PtInit0693Data.Init0693Get061eErrCode)))
					{

						if(PtConfigData.Cfg0693_Times < PT_CFG_MAX_TIMES)
						{
							PtConfigData.Cfg0693_RecordErrID[PtConfigData.Cfg0693_Times] = PtInit0693Data.Init0693Get061eErrCode;
							PtInit0693Data.Init0693Get061eErrCode = Default_NullCode;

							PtInit0693Data.Init0693Step = 0u;
							PtInit0693Data.PtInitialisation0693_Counter = 0u;
							PtConfigData.ConfigStep = User0693;
							PtConfigData.Cfg0693_Times++;
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0693Err;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}
					}

					break;

				default:

					break;

			}

			break;

		case User0670emv:
				switch(PtDiag0670EmvData.Diag0670EmvStep)
				{
					case 0:

						retvalue = Zvt_PtEmvConfigurationDiagnosis0670_4();
						if(TRUE == retvalue)
						{
							PtDiag0670EmvData.Diag0670EmvStep = 1u;
						}

						break;

					case 1:

						lSendCmd04ffAck();

						if(PtConfigData.Cfg0670Emv_Times < PT_CFG_MAX_TIMES)
						{
							if(PtDiag0670EmvData.Diag0670Emv_Counter > PtDiag0670EmvData.Diag0670Emv_DefaultCounter)			/*about 45s*/
							{
								PtDiag0670EmvData.Diag0670Emv_Counter = 0u;

								PtDiag0670EmvData.Diag0670EmvStep = 0u;
								PtConfigData.ConfigStep = PtConfig_OK;
								PtConfigData.Cfg0670Emv_Times++;
							}

							PtDiag0670EmvData.Diag0670Emv_Counter++;
						}
						else
						{
							ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0670EmvErr;
							PtConfigData.ConfigStep = PtConfig_TimeOut;
						}

						/*If Get ErrorCode*/
						if((no_error != PtDiag0670EmvData.Diag0670EmvGet061eErrCode)\
						&&((Default_NullCode != PtDiag0670EmvData.Diag0670EmvGet061eErrCode)))
						{
							if(PtConfigData.Cfg0670Emv_Times < PT_CFG_MAX_TIMES)
							{
								PtConfigData.Cfg0693_RecordErrID[PtConfigData.Cfg0670Emv_Times] = PtDiag0670EmvData.Diag0670EmvGet061eErrCode;
								PtDiag0670EmvData.Diag0670EmvGet061eErrCode = Default_NullCode;
								PtDiag0670EmvData.Diag0670EmvStep = 0u;
								PtDiag0670EmvData.Diag0670Emv_Counter = 0u;
								PtConfigData.ConfigStep = User0693;
								PtConfigData.Cfg0670Emv_Times++;
							}
							else
							{
								ZvtCom_Write.SetCCVFault_enum_Watch = PtCfg_User0670EmvErr;
								PtConfigData.ConfigStep = PtConfig_TimeOut;
							}
						}

						break;

					default:
						break;
				}

			break;

			case PtConfig_OK:
#if DEBUG_PHASE
				ZvtCom_Read.PT_ConfigSwitch_flg = FALSE;
#endif
				break;

			case PtConfig_TimeOut:
#if DEBUG_PHASE
				ZvtCom_Read.PT_ConfigSwitch_flg = FALSE;
#endif
				break;

		default:
			break;

	}

    if(FALSE == Asw_ZvtDispatchConfigurationRequest())
    {
        CCV_Signal = CCV_SIG_BACK;
    }

}


/*
@brief
@details
@para
@return
*/
void CCV_StatePtConfig(parser_t *me, signal_t sig)
{
    switch(sig)
    {
    case CCV_SIG_ENTRY :
    	CCV_StatePtConfigInit();
        CCV_SignalUpdate = CCV_StatePtConfigUpdate;
        me->currentstate = SGUS_STA_PTCONFIG;
        break;
    case CCV_SIG_EXIT :
        me->prestate = SGUS_STA_PTCONFIG;
        break;
    case CCV_SIG_BACK :
        TRAN_EE(me, CCV_StateIdle);
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
void CCV_StateMifareInit(void)
{
    //Send 06 C0

	CCV_MifareData.TimeOutCounter = 0u;
	CCV_MifareData.Send06C0Counter = 0u;
	CCV_MifareData.MifareCardStep = MifareSend06C0_N_OK;
	memset(ZVT_CarIDValue, 0u, 10u);
	memset(CCV_MifareData.UID_0x4C0A_10B, 0u, 10u);

}

/*
@brief
@details
@para
@return
*/
void CCV_StateMifareUpdate(void)
{
	uint8 retvalue;
	uint8 i;
//    volatile uint8_t tmp_ASW_Mifare_Request = 0;
    //Wait UID
    //if Succeed
	if(0u == debugFlagList.debugFlag19)
	{
	    Zvt_ReadAsw.AGunStart_flg = get_GbEACM_AGunStartCheckForCard_flg();
		Zvt_ReadAsw.BGunStart_flg = get_GbEACM_BGunStartCheckForCard_flg();
	}

    CCV_Signal = CCV_SIG_DEFAULT;

    switch(CCV_MifareData.MifareCardStep)
    {
		case MifareSend06C0_N_OK:

			if(0u == (CCV_MifareData.Send06C0Counter % 600u))
			{
				Zvt_PtReadCard06C0UID();
			}

			if(TRUE == Zvt_PtCheckReceive8000Ack())
			{
				CCV_MifareData.MifareCardStep = MifareSend06C0_OK;
			}

			CCV_MifareData.Send06C0Counter++;
			if(CCV_MifareData.Send06C0Counter >= 3000)
			{
				CCV_MifareData.Send06C0Counter = 0u;
				CCV_MifareData.MifareCardStep = MifareStep_TimeOut;
				Zvt_WriteRte.ReadCardSuccess_flg = FALSE;

			}

			break;

		case MifareSend06C0_OK:

			Bitmap06Get_UIDProcess();

			if(TRUE == CCV_MifareData.getUID)
			{

				memcpy(ZVT_CarIDValue, CCV_MifareData.UID_0x4C0A_10B, 10u);

                for(i = 0; i < 7; i++)
                {
                    set_GcEBSW_CCVRFIDCardUID_numb(i, ZVT_CarIDValue[i+3]);
                }

				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					memcpy(ZvtCom_Read.LeftRFIDCardUID_numb, CCV_MifareData.UID_0x4C0A_10B, 10u);
					memcpy(ZVT_CarIDValue, CCV_MifareData.UID_0x4C0A_10B, 10u);
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					memcpy(ZvtCom_Read.RightRFIDCardUID_numb, CCV_MifareData.UID_0x4C0A_10B, 10u);
					memcpy(ZVT_CarIDValue, CCV_MifareData.UID_0x4C0A_10B, 10u);

				}

				retvalue = Zvt_PtAbort06B0();
				if(ZVT_RET_OK == retvalue)
				{
					CCV_MifareData.getUID = FALSE;
					Zvt_WriteRte.ReadCardSuccess_flg = TRUE;
					CCV_MifareData.MifareCardStep = MifareStep_Over;
				}
			}

			CCV_MifareData.TimeOutCounter++;
			if(CCV_MifareData.TimeOutCounter > 3000u)     /*wait for tapping MifareCard about 30s */
			{
				CCV_MifareData.TimeOutCounter = 0u;
				CCV_MifareData.MifareCardStep = MifareStep_TimeOut;
				Zvt_WriteRte.ReadCardSuccess_flg = FALSE;

				if(TRUE == Zvt_ReadAsw.AGunStart_flg)
				{
					ZvtCom_Write.CCU1_SetCCVFault_enum = abort_via_timeout_or_abort_key_0x6C;
				}

				if(TRUE == Zvt_ReadAsw.BGunStart_flg)
				{
					ZvtCom_Write.CCU2_SetCCVFault_enum = abort_via_timeout_or_abort_key_0x6C;
				}
			}

			break;

		case MifareStep_Over:

			if(1u == debugFlagList.debugFlag20)
			{
				Zvt_ReadAsw.AGunStart_flg = FALSE;
				Zvt_ReadAsw.BGunStart_flg = FALSE;
			}

			Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);
		    CCV_Signal = CCV_SIG_DEFAULT;

			break;

		case MifareStep_TimeOut:

			if(1u == debugFlagList.debugFlag20)
			{
				Zvt_ReadAsw.AGunStart_flg = FALSE;
				Zvt_ReadAsw.BGunStart_flg = FALSE;
			}

			Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);
		    CCV_Signal = CCV_SIG_DEFAULT;

			break;

		default:

			break;
    }

	tmp_ASW_Mifare_Request = Asw_ZvtDispatch06C0MifareRequest();

    if(FALSE == tmp_ASW_Mifare_Request)
    {
        CCV_Signal = CCV_SIG_BACK;
    }
}
/*
@brief
@details
@para
@return
*/
void CCV_StateMifare(parser_t *me, signal_t sig)
{
    switch(sig)
    {
    case CCV_SIG_ENTRY :
        CCV_StateMifareInit();
        CCV_SignalUpdate = CCV_StateMifareUpdate;
        me->currentstate = SGUS_STA_MIFARE;
        break;
    case CCV_SIG_EXIT :
        me->prestate = SGUS_STA_MIFARE;
        break;
    case CCV_SIG_BACK :
        TRAN_EE(me, CCV_StateIdle);
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
void StateTask(void)
{
    static uint8_t initonce = TRUE;

    if(TRUE == initonce)
    {
        CCV_StateInit();
        initonce = 0;
    }

    CCV_SignalUpdate();
    FsmDispatch(&CCV_Parser, CCV_Signal);
}

