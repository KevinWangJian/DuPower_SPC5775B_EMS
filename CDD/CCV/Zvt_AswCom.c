/*
 * Zvt_AswCom.c
 *
 *  Created on: 2020Äê3ÔÂ5ÈÕ
 *      Author: admin
 */

#include "EthComm.h"
#include "Zvt_Driver.h"
#include "Zvt_HalfCom.h"
#include "Zvt_AswCom.h"
#include "ASW_RTE.h"
zvt_pt_errcode_t  PtErrCode;

zvt_debugcounter_t debugCounterList;

zvt_writerte_t Zvt_WriteRte;
zvt_readasw_t Zvt_ReadAsw;

uint8 ZVT_CarIDValue[10u];
uint8 ZVT_CarSIDValue[32u];


typedef parser_t zvtconfig_parser_t;

volatile zvt_wrcomtest_t ZvtCom_Write;
volatile zvt_rdcomtest_t ZvtCom_Read;

extern TcpIp_SockAddrInetType User_LocalAddress;
extern TcpIp_SockAddrInetType User_RouterAddress;
extern TcpIp_SockAddrInetType User_RemoteAddress;

extern zvt_pt_init_statemachine_t PtInitState;
extern zvt_cmd04ff_stdformat_t  cmd04ffPayload;
extern zvt_pt_ipmode IpModeFlag;
extern zvt_pt_ipmode PrevIpModeFlag;
extern zvt_debugflag_t debugFlagList;
extern zvt_pt_receiptnumber_t PtReceiptNo;

extern unsigned char GbEACM_AGunStartCheckForCard_flg;
extern unsigned char GbEACM_BGunStartCheckForCard_flg;
extern unsigned char GbEACM_AGunUserStopForCard_flg;
extern unsigned char GbEACM_BGunUserStopForCard_flg;
extern unsigned char GbEACM_AGunNonUserStopForCard_flg;
extern unsigned char GbEACM_BGunNonUserStopForCard_flg;

extern uint8 Bitmap06GetSIDProcess_0622(void);
extern uint8 Bitmap06GetSIDProcess_06C0(void);

extern uint8 Bitmap06GetSIDProcessPlusplus_06C0(void);
extern uint8 Bitmap06GetSIDProcessPlusplus_0622(void);

/*
@brief    check whether ip1 = ip2
@details
@para
@return
*/
uint8 Asw_ZvtCompareTwoIP(const uint8* pNewIpData, const uint8* pOldIpData)
{
	uint8 NewIpDataArray[4u] = {0u};
	uint8 OldIpDataArray[4u] = {0u};

	memcpy(NewIpDataArray, pNewIpData, 4u);
	memcpy(OldIpDataArray, pOldIpData, 4u);

	if((NewIpDataArray[0u] == OldIpDataArray[0u])\
	 &&(NewIpDataArray[1u] == OldIpDataArray[1u])\
	 &&(NewIpDataArray[2u] == OldIpDataArray[2u])\
	 &&(NewIpDataArray[3u] == OldIpDataArray[3u]))
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
*/
uint8 Zvt_MoneyFloat32Convert2Uint8Bcd(const float32* InputData, uint8* OutputData)
{
	uint8 BcdData0, BcdData1, BcdData2, BcdData3;

	uint8 OutputDataArray[2u] = {0u};
	uint16 u16InputDataTemp;
	float32 pInputDataTemp;

	pInputDataTemp = *InputData;
	u16InputDataTemp = (uint16)(pInputDataTemp*100);

	BcdData0 = (uint8)(u16InputDataTemp % 10u);        		/*ge*/
	BcdData1 = (uint8)((u16InputDataTemp % 100u) / 10u);	/*shi*/
	BcdData2 = (uint8)((u16InputDataTemp % 1000u) / 100u);	/*bai*/
	BcdData3 = (uint8)(u16InputDataTemp / 1000u);        	/*qian*/

	OutputDataArray[1u] = (BcdData1 << 4u) + BcdData0;
	OutputDataArray[0u] = (BcdData3 << 4u) + BcdData2;


	/*max = 2500 fen*/
	if(u16InputDataTemp <= 2500u)
	{
		memcpy(OutputData, OutputDataArray, sizeof(OutputDataArray)/sizeof(uint8));
		return TRUE;
	}
	else
	{
		return maximum_amount_exceeded_0xC3;
	}
}


/*
@brief
@details
@para
@return
@ e.g.  InputData[2u]={0x01, 0x65} -----> 0165
*/
void Zvt_ReceiptUint8BcdConvert2Uint16(const uint8*InputData, uint16* pOutputData)
{
	uint8 InputDataArrayTemp[2u] = {0u};
	uint16 TempData0, TempData1, TempData2, TempData3, OutputDataTemp;

	memcpy(InputDataArrayTemp, InputData, sizeof(InputData)/sizeof(uint8));

	TempData0 = (uint16)InputDataArrayTemp[0u];
	TempData1 = (uint16)InputDataArrayTemp[0u];

	TempData2 = (uint16)InputDataArrayTemp[1u];
	TempData3 = (uint16)InputDataArrayTemp[1u];


	OutputDataTemp = ((TempData0 >> 4u)*1000u)\
					 +((TempData1 & 0x000Fu)*100u)\
					 +((TempData2 >> 4u)*10u)\
					 +(TempData3 & 0x000Fu);

	*pOutputData = OutputDataTemp;
}


/*
@brief
@details
@para
@return
*/
zvt_pt_ipmode Zvt_PtGetIPMode(void)
{
	return (IpModeFlag);
}

/*
@brief
@details
@para
@return
*/
uint8 Asw_ZvtDispatch0622PreAuthRequest(void)
{
	uint8 ret = FALSE;
	if((CreditCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)&&(TRUE == Zvt_ReadAsw.AGunStart_flg))
	{
		Zvt_ReadAsw.CCU1_MCVCardType_enum_bak = CreditCard;
		ret = TRUE;
	}
	else if((CreditCard == Zvt_ReadAsw.CCU2_MCVCardType_enum)&&(TRUE == Zvt_ReadAsw.BGunStart_flg))
	{
		Zvt_ReadAsw.CCU2_MCVCardType_enum_bak = CreditCard;
		ret = TRUE;
	}
	return ret;
}


/*
@brief
@details
@para
@return
*/
uint8 Asw_ZvtDispatchUserStopRequest(void)
{
	uint8 ret = FALSE;
	if(((TRUE == Zvt_ReadAsw.AGunStop_flg)&&((CreditCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)||(RfidCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)))\
	 ||((TRUE == Zvt_ReadAsw.BGunStop_flg)&&((CreditCard == Zvt_ReadAsw.CCU2_MCVCardType_enum)||(RfidCard == Zvt_ReadAsw.CCU2_MCVCardType_enum))))
	{
		ret = TRUE;
	}

	return ret;
}

/*
@brief
@details
@para
@return
*/
uint8 Asw_ZvtDispatch0623ReversalRequest(void)
{
	uint8 ret = FALSE;
	if(((CreditCard == Zvt_ReadAsw.CCU1_MCVCardType_enum_bak)&&(TRUE == Zvt_ReadAsw.CCU1_AutoFinish_flg))\
	 ||((CreditCard == Zvt_ReadAsw.CCU2_MCVCardType_enum_bak)&&(TRUE == Zvt_ReadAsw.CCU2_AutoFinish_flg)))
	{
		ret = TRUE;
	}

	return ret;
}

/*
@brief
@details
@para
@return
*/
uint8 Asw_ZvtDispatch06C0MifareRequest(void)
{
	uint8 ret = FALSE;
	if((RfidCard == Zvt_ReadAsw.CCU1_MCVCardType_enum)&&(TRUE == Zvt_ReadAsw.AGunStart_flg))
	{
		Zvt_ReadAsw.CCU1_MCVCardType_enum_bak = RfidCard;
		ret = TRUE;
	}
	else if((RfidCard == Zvt_ReadAsw.CCU2_MCVCardType_enum)&&(TRUE == Zvt_ReadAsw.BGunStart_flg))
	{
		Zvt_ReadAsw.CCU2_MCVCardType_enum_bak = RfidCard;
		ret = TRUE;
	}

	return ret;
}


/*
@brief
@details
@para
@return
*/
uint8 Asw_ZvtDispatchConfigurationRequest(void)
{
	if(TRUE ==  ZvtCom_Read.PT_ConfigSwitch_flg)
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
@details   polled by 100ms_task
@para
@return
*/
uint8 Asw_ZvtMonitorIpConnection_100ms(void)
{

	if(0 != ZvtCom_Read.ChgUsr_IpAddr[0u])  													/*valid IP*/
	{
		if(TRUE != CompareSimilarIpData(ZvtCom_Read.ChgUsr_IpAddr, User_LocalAddress.addr))     /* if UserIP have been changed*/
		{

			PrevIpModeFlag = Factory_IpMode;


		}
	}


}



/*
@brief
@details
@para
@return
@note     called by Zvt_PtCheckTcpConnection()
*/
uint8 lZvt_PtFactoryMode_CheckTcpConnection(void)
{
	uint8 retvalue;

	if((TRUE == Asw_ZvtDispatchConfigurationRequest())\
	 &&(Factory_IpMode == IpModeFlag))
	{
		switch(PtInitState.CheckTcpConnectionStep)
		{
			case SendCmd0501:

				if(PtInitState.CheckTcpConnectionTimes <= TCP_CONNECT_TIMES)
				{
					retvalue = Zvt_Pt142IpStatusEnquiry0501();

					if(TRUE == retvalue)
					{
						PtInitState.CheckTcpConnectionStep = WaitAckFor0501;
						PtInitState.Counter_PtInit142Connect = 0u;

					}
					else
					{
						PtInitState.CheckTcpConnectionStep = SendCmd0501;
						PtInitState.Counter_PtInit142Connect = 0u;

						PtInitState.CheckTcpConnectionTimes++;
					}
				}
				else
				{
					PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
				}

				break;

			case WaitAckFor0501:

				if(PtInitState.CheckTcpConnectionTimes <= TCP_CONNECT_TIMES)
				{
					PtInitState.Counter_PtInit142Connect++;

					if(PtInitState.Counter_PtInit142Connect < 50u)   				/* within 5s a time*/
					{
						if((Service_Mode_0x1a == cmd04ffPayload.cmd04ff_intermediate_status)\
						 ||(PtRespCmd0800_OK == PtInitState.PtResp0800Flag))
						{
							cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
							PtInitState.PtResp0800Flag = PtRespCmd0800_N_OK;

							PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
							PtInitState.PtInit142Connect = PtInit_1_42_OK;

							PtInitState.CheckTcpConnectionTimes++;
						}
					}
					else
					{
						PtInitState.CheckTcpConnectionStep = SendCmd0501;
						PtInitState.Counter_PtInit142Connect = 0u;

						PtInitState.CheckTcpConnectionTimes++;
					}
				}
				else
				{
					PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
				}

				break;

			case CheckTcpConnnectionOver:
#if DEBUG_PHASE
				ZvtCom_Read.PT_ConfigSwitch_flg = FALSE;
#endif

				break;

			default:
				break;
		}
	}
	return(ZVT_RET_OK);
}



/*
@brief
@details
@para
@return
@note     called by Zvt_PtCheckTcpConnection()
*/
uint8 lZvt_PtUserMode_CheckTcpConnection(void)
{
	uint8 retvalue;

	if((TRUE == Asw_ZvtDispatchConfigurationRequest())\
	 &&(User_IpMode == IpModeFlag))
	{
		switch(PtInitState.CheckTcpConnectionStep)
		{
			case SendCmd0501:

				if(PtInitState.CheckTcpConnectionTimes <= TCP_CONNECT_TIMES)
				{
					retvalue = Zvt_PtUserIpStatusEnquiry0501();

					if(TRUE == retvalue)
					{
						PtInitState.CheckTcpConnectionStep = WaitAckFor0501;
						PtInitState.Counter_PtInit142Connect = 0u;

					}
					else
					{
						PtInitState.CheckTcpConnectionStep = SendCmd0501;
						PtInitState.Counter_PtInit142Connect = 0u;

						PtInitState.CheckTcpConnectionTimes++;

					}
				}
				else
				{
					PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
				}

				break;

			case WaitAckFor0501:

				if(PtInitState.CheckTcpConnectionTimes <= TCP_CONNECT_TIMES)
				{
					PtInitState.Counter_PtInit142Connect++;

					if(PtInitState.Counter_PtInit142Connect < 50u)   				/* within 5s a time*/
					{
						if((Service_Mode_0x1a == cmd04ffPayload.cmd04ff_intermediate_status)\
						 ||(PtRespCmd0800_OK == PtInitState.PtResp0800Flag))
						{
							cmd04ffPayload.cmd04ff_intermediate_status = 0xfe;
							PtInitState.PtResp0800Flag = PtRespCmd0800_N_OK;

							PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
							PtInitState.PtInit142Connect = PtInit_UserIP_OK;

							PtInitState.CheckTcpConnectionTimes++;
						}
					}
					else
					{
						PtInitState.CheckTcpConnectionStep = SendCmd0501;
						PtInitState.Counter_PtInit142Connect = 0u;

						PtInitState.CheckTcpConnectionTimes++;
					}
				}
				else
				{
					PtInitState.CheckTcpConnectionStep = CheckTcpConnnectionOver;
				}

				break;

			case CheckTcpConnnectionOver:

#if DEBUG_PHASE
				ZvtCom_Read.PT_ConfigSwitch_flg = FALSE;
#endif

				break;

			default:
				break;
		}
	}
	return(ZVT_RET_OK);

}



/*
@brief
@details
@para
@return
@note     called by Zvt_100msTask()
*/

uint8 Zvt_PtCheckTcpConnection(void)
{
	static uint32 ui32Counter;
	uint8 retvalue = FALSE;

	if((TRUE != Zvt_ReadAsw.AGunStart_flg)\
	 &&(TRUE != Zvt_ReadAsw.BGunStart_flg)\
	 &&(TRUE != Zvt_ReadAsw.AGunStop_flg)\
	 &&(TRUE != Zvt_ReadAsw.BGunStop_flg)\
	 &&(TRUE != Zvt_ReadAsw.CCU1_AutoFinish_flg)\
	 &&(TRUE != Zvt_ReadAsw.CCU2_AutoFinish_flg))
	{
		if(0u == (ui32Counter % 15u))			/*1.5s per time*/
		{
			if(User_IpMode == IpModeFlag)
			{
				retvalue = Zvt_PtTxPositiveAck8000();
			}

			if(Factory_IpMode == IpModeFlag)
			{
				retvalue = Zvt_PtTxFactoryPositiveAck8000();
			}
		}
		ui32Counter++;
	}
	else
	{
		ui32Counter = 0u;
	}

	return(retvalue);
}



/*
@brief
@details
@para
@return
*/
uint16 Zvt_PtReadReceipt(uint16 cmd)
{

	if(0x040f == cmd)
	{
		return (PtReceiptNo.PtCmd040fReceipt87No);
	}

	else if(0x060f == cmd)
	{
		return (PtReceiptNo.PtCmd060fReceipt87No);
	}

	else if(0x061e == cmd)
	{
		return (PtReceiptNo.PtCmd061eReceipt87No);
	}

	else if(0x06d3 == cmd)
	{
		return (PtReceiptNo.PtCmd06d3Receipt87No);
	}

}



/* ******************************************************
 * Signal from PT  to ZVT
 * ******************************************************/
/*
@brief
@details
@para
@return
*/

uint8 Zvt_PtReadErrID(uint16 cmd)
{
	if(0x040f == cmd)
	{
		return (PtErrCode.PtCmd040fErrCode);
	}

	else if(0x060f == cmd)
	{
		return (PtErrCode.PtCmd060fErrCode);
	}

	else if(0x061e == cmd)
	{
		return (PtErrCode.PtCmd061eErrCode);
	}

	else if(0x06d3 == cmd)
	{
		return (PtErrCode.PtCmd06d3ErrCode);
	}

	else if(0x8000 == cmd)
	{
		return (0u);
	}

	else if(0x8400 == cmd)
	{
		return (0u);
	}

	else
	{;}
}

/*
@brief
@details	polled by Zvt_100msTask()
@para
@return
*/

void Debug_Function_100ms(void)
{

	  if(1u == debugFlagList.debugFlag13)
	  {
		  Zvt_PtTxPositiveAck8400();

		  debugFlagList.counter1++;

		  if( debugFlagList.counter1 > 80u)  /*delay 8s*/
		  {
			  debugFlagList.debugFlag13 = 0u;
			  debugFlagList.counter1 = 0u;
		  }
	  }

	  if(5u == debugFlagList.debugFlag16)
	  {
		  Zvt_Pt142IpStatusEnquiry0501();

		  debugFlagList.counter2++;

		  if( debugFlagList.counter2 > 80)  /*delay 8s*/
		  {
			  debugFlagList.debugFlag16 = 0u;
			  debugFlagList.counter2 = 0u;
		  }
	  }

	  if(5u == debugFlagList.debugFlag13)
	  {
		  if(0u == (debugFlagList.counter2 % 8))    /*800ms  per time*/
		  {
			  Zvt_PtUserIpStatusEnquiry0501();
		  }

		  debugFlagList.counter2++;

		  if( debugFlagList.counter2 > 80)  /*delay 8s*/
		  {
			  debugFlagList.debugFlag13 = 0u;
			  debugFlagList.counter2 = 0u;
		  }
	  }

	  if(1u == debugFlagList.debugFlag14)	/*OK*/
	  {
		  if(TRUE == Bitmap06GetSIDProcess_0622())
		  {
			  debugFlagList.debugFlag14 = 0u;
		  }

	  }

	  if(3u == debugFlagList.debugFlag14)		/*OK*/
	  {
		  if(TRUE == Bitmap06GetSIDProcess_06C0())
		  {
			  debugFlagList.debugFlag14 = 0u;
		  }

	  }

	  if(3u == debugFlagList.debugFlag6)		/*OK*/
	  {
		  if(TRUE == Bitmap06GetSIDProcessPlusplus_06C0())
		  {
			  debugFlagList.debugFlag6 = 0u;
		  }

	  }

	  if(6u == debugFlagList.debugFlag6)		/*OK*/
	  {
		  if(TRUE == Bitmap06GetSIDProcessPlusplus_0622())
		  {
			  debugFlagList.debugFlag6 = 0u;
		  }

	  }

	  if(13u == debugFlagList.debugFlag13)
	  {

		  debugFlagList.counter3++;

		  if( debugFlagList.counter3 > 20u)  /*delay 2s*/
		  {
			  Zvt_PtReturnRemainingAmount0623(ZvtCom_Read.LeftCreditCardReceipt_numb, ZvtCom_Read.CCU1_RemainMoney_rmb);

			  debugFlagList.debugFlag13 = 0u;
			  debugFlagList.counter3 = 0u;
		  }
	  }

}

/*
@brief
@details	polled by BSW_OsTask_100ms()
@para
@return
*/

 void Asw_ZvtCopyAswData2Zvt(void)
{
	if(COM_ZVT_TEST_CONST == Zvt_ReadAsw.Zvt_ReadAsw_switch)
	{
		/*********0622SID*************/
		if(ZvtCom_Read.CCU1_ZVT0622PreAut_flg)
		{
			Zvt_ReceiptUint8BcdConvert2Uint16(ZvtCom_Write.CCU1_SetCCVCreditCardReceipt_numb, &Zvt_WriteRte.SetCCVCreditCardReceipt);
			memcpy(Zvt_WriteRte.SetCCVCreditCardSID_numb, ZvtCom_Write.CCU1_SetCCVCreditCardSID_numb, PT_SID_LEN);
		}
		if(ZvtCom_Read.CCU2_ZVT0622PreAut_flg)
		{
			Zvt_ReceiptUint8BcdConvert2Uint16(ZvtCom_Write.CCU2_SetCCVCreditCardReceipt_numb, &Zvt_WriteRte.SetCCVCreditCardReceipt);
			memcpy(Zvt_WriteRte.SetCCVCreditCardSID_numb, ZvtCom_Write.CCU2_SetCCVCreditCardSID_numb, PT_SID_LEN);
		}

		/*********06C0SID*************/


		/*********0623*************/


		/*********RFID,  06C0UID*************/
		if(ZvtCom_Read.CCU1_ZVT06C0CardUID_flg)
		{
			memcpy(Zvt_WriteRte.SetCCVRFIDCardUID_numb, ZvtCom_Write.CCU1_SetCCVRFIDCardUID_numb, 10u);
		}
		if(ZvtCom_Read.CCU2_ZVT06C0CardUID_flg)
		{
			memcpy(Zvt_WriteRte.SetCCVRFIDCardUID_numb, ZvtCom_Write.CCU2_SetCCVRFIDCardUID_numb, 10u);
		}


		/**********************************READ*************************************************************/
		/**********************************READ*************************************************************/
		ZvtCom_Read.CCU1_CardType_enum = Zvt_ReadAsw.CCU1_MCVCardType_enum;
		ZvtCom_Read.CCU2_CardType_enum = Zvt_ReadAsw.CCU2_MCVCardType_enum;

		if(0u == debugFlagList.debugFlag20)
		{
			ZvtCom_Read.CCU1_ZVT0622PreAut_flg = Zvt_ReadAsw.AGunStart_flg;
			ZvtCom_Read.CCU2_ZVT0622PreAut_flg = Zvt_ReadAsw.BGunStart_flg;

			ZvtCom_Read.CCU1_ZVT06C0CardSID_flg = Zvt_ReadAsw.AGunStop_flg;
			ZvtCom_Read.CCU2_ZVT06C0CardSID_flg = Zvt_ReadAsw.BGunStop_flg;

			ZvtCom_Read.CCU1_ZVT0623SettleAccount_flg = Zvt_ReadAsw.CCU1_AutoFinish_flg;
			ZvtCom_Read.CCU2_ZVT0623SettleAccount_flg = Zvt_ReadAsw.CCU2_AutoFinish_flg;
		}

		Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU1_PreMoney_rmb, ZvtCom_Read.CCU1_PreMoney_rmb);
		Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU2_PreMoney_rmb, ZvtCom_Read.CCU2_PreMoney_rmb);

		Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU1_RemainMoney_rmb, ZvtCom_Read.CCU1_RemainMoney_rmb);
		Zvt_MoneyFloat32Convert2Uint8Bcd(&Zvt_ReadAsw.CCU2_RemainMoney_rmb, ZvtCom_Read.CCU2_RemainMoney_rmb);

	}
}



/*
@brief
@details	polled by BSW_OsTask_100ms()
@para
@return
*/
void Zvt_100msTask(void)
{

	  {
		  Zvt_PtCheckTcpConnection();
	  }

	  if(0u == debugFlagList.debugFlag17)

	  {
		  Zvt_AswCom_WriteRte();
	  }

	  if(0u == debugFlagList.debugFlag10)

	  {
		  Zvt_AswCom_ReadAsw();
	  }

	  if(0u == debugFlagList.debugFlag11)
	  {
		  Asw_ZvtCopyAswData2Zvt();
	  }

	  {
		  Debug_Function_100ms();
	  }

}


/* send ASW*/
void  Zvt_AswCom_WriteRte(void)
{
	if(COM_ZVT_TEST_CONST == Zvt_ReadAsw.Zvt_ReadAsw_switch)
	{
		Rte_Write_ZVT_ZVTCarPass_flg(Zvt_WriteRte.ReadCardSuccess_flg);

		Rte_Write_ZVT_CarReceipt_Value(Zvt_WriteRte.SetCCVCreditCardReceipt);

		memcpy(ZVT_CarIDValue, Zvt_WriteRte.SetCCVRFIDCardUID_numb, 10u);
		memcpy(ZVT_CarSIDValue, Zvt_WriteRte.SetCCVCreditCardSID_numb, 32u);
	}
}



/* receive ASW*/
void Zvt_AswCom_ReadAsw(void)
{
//	if(COM_ZVT_TEST_CONST == Zvt_ReadAsw.Zvt_ReadAsw_switch)
//	{
//		/*from Tpanel*/
//
//
//		/*from ASW*/
//
//		Zvt_ReadAsw.CCU1_MCVCardType_enum = get_GeEBSW_CCU1CCVChargeType_enum();
//		Zvt_ReadAsw.CCU2_MCVCardType_enum = get_GeEBSW_CCU2CCVChargeType_enum();
//
//		Zvt_ReadAsw.AGunStart_flg = get_GbEACM_AGunStartCheckForCard_flg();
//		Zvt_ReadAsw.BGunStart_flg = get_GbEACM_BGunStartCheckForCard_flg();
//
//		Zvt_ReadAsw.AGunStop_flg = get_GbEACM_AGunUserStopForCard_flg();
//		Zvt_ReadAsw.BGunStop_flg = get_GbEACM_BGunUserStopForCard_flg();
//
////		Zvt_ReadAsw.CCU1_AutoFinish_flg = get_GbECEC_CCU1ElectricityCalFinish_flg();
////		Zvt_ReadAsw.CCU2_AutoFinish_flg = get_GbECEC_CCU2ElectricityCalFinish_flg();
//
//		Zvt_ReadAsw.CCU1_PreMoney_rmb = get_GcEACM_CCU1PreMoney_rmb();
//		Zvt_ReadAsw.CCU2_PreMoney_rmb = get_GcEACM_CCU2PreMoney_rmb();
//
//		Zvt_ReadAsw.CCU1_RemainMoney_rmb = get_GcEACM_CCU1RemainMoney_rmb();
//		Zvt_ReadAsw.CCU2_RemainMoney_rmb = get_GcEACM_CCU2RemainMoney_rmb();
//	}
}


