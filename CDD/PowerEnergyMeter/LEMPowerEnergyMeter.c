#include <stdio.h>
#include <stdarg.h>


#include "LEMPowerEnergyMeter.h"
#include "StdRegMacros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"
#include "Mcal.h"
#include "Rte_Asw_Swc.h"
#include "Rte_IoHwAb.h"





/*LEM*/



typedef struct
{
    uint8_t rub_LEMWH_ConnectOK[2];
    float rul_LEMWHImportEnergy[2];
    float rul_LEMWHVoltage[2];
    float rul_LEMWHCurrent[2];
    uint8_t rub_suLinkStatusIsOk[2];
    uint8_t rub_sendChangeIPOk[2];
}LEM_WH_Data;


LEM_WH_Data rub_LEM_WH_Data;



TcpIp_SocketIdType LEMSocketIdex;
uint8 LEMSocketRxFrame[1000];
uint16 LEMSocketRxFrameSize;


LEMWH_arpsniffer LEMWHarpSnifferFlag;


TcpIp_SocketIdType LEMWHSocketIdex_Test;
TcpIp_SockAddrInetType LEMWHSocketRxIdex;


//TcpIp_SockAddrInetType LEMRemoteAddressWH1  = {TCPIP_AF_INET, 0xc0a8012a, 80};
//TcpIp_SockAddrInetType LEMRemoteAddressWH2  = {TCPIP_AF_INET, 0xc0a8012b, 80};

TcpIp_SockAddrInetType LEMRemoteAddressWH1  = {TCPIP_AF_INET, 0xc0a80014, 50007};		/*192.168.0.20*/
TcpIp_SockAddrInetType LEMRemoteAddressWH2  = {TCPIP_AF_INET, 0xc0a80028, 50008};      /*192.168.0.40*/
TcpIp_SockAddrInetType LEMRemoteDefaultAddressWH  = {TCPIP_AF_INET, 0xc0a80102, 80};		/*192.168.1.2*/
//TcpIp_SockAddrInetType LEMRemoteAddressWH2  = {TCPIP_AF_INET, 0xc0a80103, 80};		/*192.168.1.3*/


uint8 LEMWHSocketRxFrame_Test[1500];
uint16 LEMWHSocketRxFrameSize_Test;

uint16 rul_LEMWHSockIdx = 0;

uint8 rub_LEM_TEST_SEND;
uint8 rub_LEM_TEST_SEND1;
uint8 rub_LEM_TEST_SEND2;
uint8 rub_LEM_TEST_SENDStatus;
uint8 rub_LEM_TEST_SENDStatus1;
uint8 rub_LEM_TEST_SENDStatus2;
uint8 rub_LEM_TEST_SENDReturn1;
uint8 rub_LEM_TEST_SENDReturn2;
uint8 rub_LEM_TEST_SENDChangeIP1;
uint8 rub_LEM_TEST_SENDChangeIP2;

uint8 rub_LEM_SendStatus[2] = 0;
uint8 rub_LEM_Sendlivemeasure[2] = 0;


uint8 LEMWHdebugFlag1 = 0u;
uint8 LEMWHdebugFlag2 = 0u;
uint8 LEMWHdebugFlag3 = 0u;

uint8 rub_LEMWH_retvalhandleData = 0u;
uint8 rub_LeftLEMWH_retvalhandleData = 0u;
uint8 rub_RightLEMWH_retvalhandleData = 0u;


uint8 rub_LEMWH_retvalue = 0u;
uint8 rub_LEMWH_retcnt = 0u;

uint8 rub_LEMWH_DCIndex = 0;
uint8 rub_LEMWH_DCCounter;
uint8 rub_LEMWHSocketWHRx[2][1500];
uint8 rub_LEMWHSocketWHRx_handle[1500];


uint8 rub_LEMWHSocketWHRx_Test[1500] =  {'>','G','E','T','/','v','1','/','l','i','v','e','l','e','a','s','u','r','e'
		,' ','H','T','T','P','/','1','.','1'
		,'>','H','o','s','t',':','1','9','2','.','1','6','8','.','7','.','2','.'
		,'>','U','s','e','r','-','A','g','e','n','t',':','i','n','s','o','m','n','i','a','/','7','.','0','.','6'
		,'A','c','c','e','p','t',':','*','/','*'
		,'{','"','v','o','l','t','a','g','e','"',':','7','8','6','.','2','4','5',','
		,'"','c','u','r','r','e','n','t','g','e','n','t','"',':','4','6','1','.','1','5','2',','
		,'"','p','o','w','e','r','"',':','5','0','0',','
		,'"','t','e','m','p','e','r','a','t','u','r','e','H',':','7','0',','
		,'"','t','e','m','p','e','r','a','t','u','r','e','L',':','6','0',','
		,'"','e','n','e','r','g','e','n','y','I','m','p','o','r','t','T','o','t','a','l','"',':','8','7','6','8','9','5','.','1','3','4',','
		,'"','e','n','e','r','g','e','n','y','E','x','p','o','r','t','T','o','t','a','l','"',':','9','4','0','.','0','0','0',',','}'};

//float rul_LEMWHImportEnergy[2];
uint8 rub_LEMWHImportEnergy_asl[15];
uint32 rul_LEMWHImportEnergy_temp;
unsigned char rub_LEMWHImportEnergy_val[15];


//float rul_LEMWHVoltage[2];
uint8 rub_LEMWHVoltage_asl[15];
uint32 rul_LEMWHVoltage_temp;
unsigned char rub_LEMWHVoltage_val[15];

//float rul_LEMWHCurrent[2];
uint8 rub_LEMWHCurrent_asl[15];
uint32 rul_LEMWHCurrent_temp;
unsigned char rub_LEMWHCurrent_val[15];

uint16 rul_iLength;

//uint8_t rub_LEMWH_ConnectOK[2];
uint8_t rub_LEMWH_DisconnectTime[2];

uint8 rub_LEMWSendWHIndex = 0u;


extern  uint8 LEMWHSocketRxFrame[1500];
extern  uint16 LEMWHSocketRxFrameSize;

uint8 LEMWHSignalFrPt_Arr[TCP_PAYLOAD_MAX_LENGTH] = {0};
/*LEM*/





static void LEMWH_ReceiveCurrent(unsigned char lub_index);
static void LEMWH_ReceiveEnergy(unsigned char lub_index);
static void LEMWH_ReceiveVoltage(unsigned char lub_index);
static uint8 LEMWH_ReceiveDataHandle(unsigned char lub_index);
static void LEMWH_Send_Livemeasure(unsigned char lub_index);
static void WH_LEMWH_HandleTASK_10ms(void);
static void WH_LEMWH_HandleTASK_100ms(void);
static uint8 LEMWH_ReceiveStatusHandle(unsigned char lub_index);
static void LEMWH_Send_status(unsigned char lub_index);
static uint8 LEMWH_ReceiveChangeIPHandle(unsigned char lub_index);
static void LEMWH_Send_ChangeIP(unsigned char lub_index);



/*uint8 rem_LEMWH1_getfunction_Data[] = {'>','G','E','T','/','v','1','l','e','g','a','l',' ','H','T','T','P','1','.','1'
			,'>','H','o','s','t',':','1','9','2','.','1','6','8','.','1','.','2'
			,'>','U','s','e','r','-','A','g','e','n','t',':','i','n','s','o','m','n','i','a','/','7','.','0','.','6'
			,'A','c','c','e','p','t',':','*','/','*'
			,'C','o','n','t','e','n','t','-','L','e','n','g','t','h',':','1','6','3',0x0D,0x0A,0x0D,0x0A
			,'{','}'
};*/

uint8 rem_LEMWH_getstatus_Data[] = {0x47,0x45,0x54,0x20,0x2F,0x76,0x31,0x2F,0x73,0x74,0x61,0x74,0x75,0x73,0x20,0x48
		,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x0D,0x0A,0x0D,0x0A
			};


uint8 rem_LEMWH1_getfunction_Data[] = {0x47,0x45,0x54,0x20,0x2F,0x76,0x31,0x2F,0x6C,0x69,0x76,0x65,0x6D,0x65,0x61,0x73
		,0x75,0x72,0x65,0x20,0x48,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x0D,0x0A,0x0D,0x0A,0x7B,0x7D
			};

uint8 rem_LEMWH2_getfunction_Data[] = {0x47,0x45,0x54,0x20,0x2F,0x76,0x31,0x2F,0x6C,0x69,0x76,0x65,0x6D,0x65,0x61,0x73
		,0x75,0x72,0x65,0x20,0x48,0x54,0x54,0x50,0x2F,0x31,0x2E,0x31,0x0D,0x0A,0x0D,0x0A,0x7B,0x7D
			};



uint8 rem_LEMWH1_SetfunctionChangeIP_Data[] = {'P','U','T',' ','/','v','1','/','s','e','t','t','i','n','g','s',' ','H','T','T','P','/','1','.','1',0x0D,0x0A
			,'C','o','n','t','e','n','t','-','L','e','n','g','t','h',':',' ','2','4','1'
			,0x0D,0x0A,0x0D,0x0A,'{',0x0D,0x0A,'"','i','p','A','d','d','r','e','s','s','"',':','"','1','9','2','.','1','6','8','.','1','.','2','0','"',0x0D,0x0A,'}'
};

uint8 rem_LEMWH2_SetfunctionChangeIP_Data[] = {'P','U','T',' ','/','v','1','/','s','e','t','t','i','n','g','s',' ','H','T','T','P','/','1','.','1',0x0D,0x0A
		,'C','o','n','t','e','n','t','-','L','e','n','g','t','h',':',' ','2','4','1'
		,0x0D,0x0A,0x0D,0x0A,'{',0x0D,0x0A,'"','i','p','A','d','d','r','e','s','s','"',':','"','1','9','2','.','1','6','8','.','1','.','4','0','"',0x0D,0x0A,'}'
};




void WH_LEMWH_TASK_100ms(void)
{
//    if(get_GeEBSW_AFCProductType_enum() == 0)
    {
	    WH_LEMWH_HandleTASK_100ms();
    }
//    else
//    {}

}




void WH_LEMWH_HandleTASK_100ms(void)
{
    uint8 lub_get_live_status;
	LEMWH_PtMainFunctionTx();

	if(1 == rub_LeftLEMWH_retvalhandleData)
	{
      // rub_LEMWH_ConnectOK[0] = 1;
	//   lub_get_live_status  = LEMWH_ReceiveDataHandle(0);

	  if(rub_LEM_Sendlivemeasure[0] == 1)
	  {
	      lub_get_live_status  = LEMWH_ReceiveDataHandle(0);
	      rub_LEM_Sendlivemeasure[0] = 0;
	  }
	  else
	  {}

	   if(rub_LEM_SendStatus[0] == 1)
	   {
		   LEMWH_ReceiveStatusHandle(0);
		   rub_LEM_SendStatus[0] = 0;
	   }
	   else
	   {}
	   memset(rub_LEMWHSocketWHRx_handle, 0, rul_iLength);
	   rul_iLength = 0;

       rub_LeftLEMWH_retvalhandleData = 0;

	}
	else if(1 == rub_RightLEMWH_retvalhandleData)
	{
     //  rub_LEMWH_ConnectOK[1] = 1;

		  if(rub_LEM_Sendlivemeasure[1] == 1)
		  {
		      lub_get_live_status  = LEMWH_ReceiveDataHandle(1);
		      rub_LEM_Sendlivemeasure[1] = 0;
		  }
		  else
		  {}

		   if(rub_LEM_SendStatus[1] == 1)
		   {
			   LEMWH_ReceiveStatusHandle(1);
			   rub_LEM_SendStatus[1] = 0;
		   }
		   else
		   {}
       memset(rub_LEMWHSocketWHRx_handle, 0, rul_iLength);
	   rul_iLength = 0;
        rub_RightLEMWH_retvalhandleData = 0;
	}
	else
	{}
//		LEMWH_ReceiveChangeIPHandle(1);



	Rte_Write_T645Value_WH1DCDCEMOnline_flg(rub_LEM_WH_Data.rub_LEMWH_ConnectOK[0]);
	Rte_Write_T645Value_WH2DCDCEMOnline_flg(rub_LEM_WH_Data.rub_LEMWH_ConnectOK[1]);

	Rte_Write_T645Value_LeftDCWhCurrtEnerge_kwH(rub_LEM_WH_Data.rul_LEMWHImportEnergy[0]);
	Rte_Write_T645Value_RightDCWhCurrtEnerge_kwH(rub_LEM_WH_Data.rul_LEMWHImportEnergy[1]);

	Rte_Write_T645Value_LeftDCWhCurrent_A(rub_LEM_WH_Data.rul_LEMWHCurrent[0]);
	Rte_Write_T645Value_RightDCWhCurrent_A(rub_LEM_WH_Data.rul_LEMWHCurrent[1]);
	Rte_Write_T645Value_LeftDCWhInputVolt_V(rub_LEM_WH_Data.rul_LEMWHVoltage[0]);
	Rte_Write_T645Value_RightDCWhInputVolt_V(rub_LEM_WH_Data.rul_LEMWHVoltage[1]);



	WH_LEMWH_Reset_WHOnline();
}


void WH_LEMWH_TASK_10ms(void)
{
//    if(get_GeEBSW_AFCProductType_enum() == 0)
    {
	    WH_LEMWH_HandleTASK_10ms();
    }
//    else
//    {}
}



void WH_LEMWH_HandleTASK_10ms(void)
{

	LEMWH_Receive2Pt(&LEMSocketRxFrame, &LEMSocketRxFrameSize);
}



/*LEM*/
/*
uint8 LEMWH_Transmit2Pt(TcpIp_PortType LEMWHLocalPort, TcpIp_SockAddrInetType pRemoteAddrPtr, uint8* pLEMWHTxDatabuf, uint16 LEMWHTxLength)
{
	uint8 LEMWH_retvalue;


	LEMWH_retvalue = Ethernet_TcpClient_Send(LEMWHLocalPort, &pRemoteAddrPtr, pLEMWHTxDatabuf, LEMWHTxLength);
	if(LEMWH_retvalue == 0u)
	{
		return(LEMWH_RET_OK);
	}
	else
	{
		return(LEMWH_RET_N_OK);
	}

}
*/

uint8 LEMWH_Receive2Pt(uint8* pLEMWHRxBuf, uint16* LEMWHRxLength)
{

	uint8 LEMWH_retvalue;
	uint8 iIndex;
	uint16 iLength;
	uint8 ireturn_val;

	 if(0 == Ethernet_LeftLEM_GetRxData(pLEMWHRxBuf, LEMWHRxLength))
	 {
        iLength = *LEMWHRxLength;
	    rul_iLength = *LEMWHRxLength;
        if(rul_iLength<500)
        {
            memcpy(rub_LEMWHSocketWHRx_handle, pLEMWHRxBuf, rul_iLength);
            rub_LeftLEMWH_retvalhandleData = 1;
        }
		 

//	     LEMWH_ReceiveCurrent(1);
//		 LEMWH_ReceiveEnergy(1);
//		 LEMWH_ReceiveVoltage(1);
	 }
	 else if(0 == Ethernet_RightLEM_GetRxData(pLEMWHRxBuf, LEMWHRxLength))
    {
        iLength = *LEMWHRxLength;
        rul_iLength = *LEMWHRxLength;
        if(rul_iLength<500)
        {
            memcpy(rub_LEMWHSocketWHRx_handle, pLEMWHRxBuf, rul_iLength);
            rub_RightLEMWH_retvalhandleData = 1;
        }
    }
	return(ireturn_val);

}




uint8 LEMWH_PtMainFunctionTx(void)
{


//	LEMWH_Send_ChangeIP(1);

	switch(rub_LEMWH_DCCounter)
	{
	   case 0:
	   {
		   LEMWH_Send_Livemeasure(0);
		   break;
	   }
	   case 1:
	   {
		   LEMWH_Send_Livemeasure(0);
		   break;
	   }
	   case 2:
	   {

		   break;
	   }
	   case 3:
	   {

		   break;
	   }
	   case 4:
	   {
		   LEMWH_Send_status(0);
		   break;
	   }
	   case 5:
	   {
		   LEMWH_Send_status(1);
		   break;
	   }
	   case 6:
	   {

		   break;
	   }
	   case 7:
	   {

		   break;
	   }
	   case 8:
	   {
		   LEMWH_Send_Livemeasure(1);
		   break;
	   }
	   case 9:
	   {
		   LEMWH_Send_Livemeasure(1);
		   break;
	   }
	   case 10:
	   {

		   break;
	   }
	   case 11:
	   {

		   break;
	   }
	   case 12:
	   {
		   LEMWH_Send_status(1);
		   break;
	   }
	   case 13:
	   {
		   LEMWH_Send_status(1);
		   break;
	   }


	}


//	LEMWH_Send_Livemeasure(rub_LEMWH_DCIndex);
//	LEMWH_Send_status(rub_LEMWH_DCIndex);


	if(rub_LEMWH_DCCounter == 15)
	{
		rub_LEMWH_DCCounter = 0;
		rub_LEMWH_DCIndex = !rub_LEMWH_DCIndex;
	}
	else
	{
		rub_LEMWH_DCCounter++;
	}


	return(LEMWH_RET_OK);
}


static void LEMWH_Send_Livemeasure(unsigned char lub_index)
{
	uint8 LEMWH_retvalue;


    if(rub_LEM_TEST_SEND == 0)
    {
	    if(lub_index == 0)
	    {
    	 // LEMWH_retvalue = LEMWH_Transmit2Pt(LEMWH_REMOTE_PORT,LEMRemoteAddressWH1, rem_LEMWH1_getfunction_Data, sizeof(rem_LEMWH1_getfunction_Data)/sizeof(uint8));

	    	if(rub_LEM_TEST_SEND1 == 0)
	    	{
	    		rub_LEM_TEST_SENDReturn1 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT1, &LEFT_LEM_RemoteAddress, rem_LEMWH1_getfunction_Data, sizeof(rem_LEMWH1_getfunction_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 0;
	    		rub_LEM_Sendlivemeasure[lub_index] = 1;
	    	}
	    	else
	    	{}
	    }
	    else if(lub_index == 1)
	    {
    	 // LEMWH_retvalue = LEMWH_Transmit2Pt(LEMWH_REMOTE_PORT,LEMRemoteAddressWH2, rem_LEMWH2_getfunction_Data, sizeof(rem_LEMWH2_getfunction_Data)/sizeof(uint8));
	    	if(rub_LEM_TEST_SEND2 == 0)
	    	{
	    		rub_LEM_TEST_SENDReturn2 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT2, &RIGHT_LEM_RemoteAddess, rem_LEMWH2_getfunction_Data, sizeof(rem_LEMWH2_getfunction_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 0;
	    		rub_LEM_Sendlivemeasure[lub_index] = 1;
	    	}
	    	else
	    	{}
	    }
	    else
	    {}
	}
    else{}

}


static void LEMWH_Send_status(unsigned char lub_index)
{
	uint8 LEMWH_retvalue;


    if(rub_LEM_TEST_SENDStatus == 0)
    {
	    if(lub_index == 0)
	    {
       	    if(rub_LEM_TEST_SENDStatus1 == 0)
	    	{
	    		rub_LEM_TEST_SENDReturn1 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT1, &LEFT_LEM_RemoteAddress, rem_LEMWH_getstatus_Data, sizeof(rem_LEMWH_getstatus_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 1;
	    		rub_LEM_Sendlivemeasure[lub_index] = 0;
	    	}
	    	else
	    	{}
	    }
	    else if(lub_index == 1)
	    {

	    	if(rub_LEM_TEST_SENDStatus2 == 0)
	    	{
	    		rub_LEM_TEST_SENDReturn2 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT2, &RIGHT_LEM_RemoteAddess, rem_LEMWH_getstatus_Data, sizeof(rem_LEMWH_getstatus_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 1;
	    		rub_LEM_Sendlivemeasure[lub_index] = 0;
	    	}
	    	else
	    	{}
	    }
	    else
	    {}
	}
    else{}

}




static void LEMWH_Send_ChangeIP(unsigned char lub_index)
{
	uint8 LEMWH_retvalue;


    if(rub_LEM_TEST_SENDChangeIP1 == 0)
    {
	    if(lub_index == 0)
	    {
       	    if(rub_LEM_TEST_SENDStatus1 == 1)
	    	{
	    		rub_LEM_TEST_SENDReturn1 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT1, &LEMRemoteDefaultAddressWH, rem_LEMWH1_SetfunctionChangeIP_Data, sizeof(rem_LEMWH1_SetfunctionChangeIP_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 0;
	    		rub_LEM_Sendlivemeasure[lub_index] = 0;
	    	}
	    	else
	    	{}
	    }
	    else if(lub_index == 1)
	    {

	    	if(rub_LEM_TEST_SENDChangeIP1 == 0)
	    	{
	    		rub_LEM_TEST_SENDReturn2 =  Ethernet_TcpClient_Send(LEMWH_REMOTE_PORT2, &LEMRemoteDefaultAddressWH, rem_LEMWH2_SetfunctionChangeIP_Data, sizeof(rem_LEMWH2_SetfunctionChangeIP_Data)/sizeof(uint8));
	    		rub_LEM_SendStatus[lub_index] = 0;
	    		rub_LEM_Sendlivemeasure[lub_index] = 0;
	    	}
	    	else
	    	{}
	    }
	    else
	    {}
	}
    else{}

}


static void WH_LEMWH_Reset_WHOnline(void)
{



	if(rub_LEMWH_DisconnectTime[0]>200)
	{
		rub_LEMWH_DisconnectTime[0] =200;
		rub_LEM_WH_Data.rub_LEMWH_ConnectOK[0] = 0;
		rub_LEM_WH_Data.rub_suLinkStatusIsOk[0] = 0;
		rub_LEM_WH_Data.rul_LEMWHImportEnergy[0] = 0;
		rub_LEM_WH_Data.rul_LEMWHVoltage[0] = 0;
		rub_LEM_WH_Data.rul_LEMWHCurrent[0] = 0;
	}
	else
	{
		rub_LEMWH_DisconnectTime[0]++;
	}

	if(rub_LEMWH_DisconnectTime[1]>200)
	{
		rub_LEMWH_DisconnectTime[1] = 200;
		rub_LEM_WH_Data.rub_LEMWH_ConnectOK[1] = 0;
		rub_LEM_WH_Data.rub_suLinkStatusIsOk[1] = 0;
		rub_LEM_WH_Data.rul_LEMWHImportEnergy[1] = 0;
		rub_LEM_WH_Data.rul_LEMWHVoltage[1] = 0;
		rub_LEM_WH_Data.rul_LEMWHCurrent[1] = 0;
	}
	else
	{
		rub_LEMWH_DisconnectTime[1]++;
	}

}





static uint8 LEMWH_ReceiveDataHandle(unsigned char lub_index)
{

	uint8 LEMWH_retvalue;
	uint8 iIndex;
	uint8 iLEM_Index;
	uint16 iLength;
	uint8 ireturn_val=0;

	//memset(rub_LEMWHImportEnergy_val, 0, 15);

	//	 for(iIndex = 0;iIndex<rul_iLength;iIndex++)
	  //   for(iIndex = 0;iIndex<170;iIndex++)
	     for(iIndex = 0;iIndex<rul_iLength;iIndex++)
		 {
	    	 if(rub_LEMWHSocketWHRx_handle[0] != 'H')
	    	 {
	    		 break;
	    	 }
	    	 else
	    	 {}

	    	 if(rub_LEMWHSocketWHRx_handle[iIndex] == ':')
			 {

				 if((rub_LEMWHSocketWHRx_handle[iIndex-2] == 'e')&&(rub_LEMWHSocketWHRx_handle[iIndex-3] == 'g'))
				 {
					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
						 rub_LEMWHVoltage_asl[iLEM_Index] = rub_LEMWHSocketWHRx_handle[iIndex+1+iLEM_Index];
					 }
					 LEMWH_ReceiveVoltage(lub_index);
					 rub_LEM_WH_Data.rub_LEMWH_ConnectOK[lub_index] = 1;
					 rub_LEMWH_DisconnectTime[lub_index] = 0;
					 ireturn_val = 1;

				 }
				 else
				 {}
				 if((rub_LEMWHSocketWHRx_handle[iIndex-2] == 't')&&(rub_LEMWHSocketWHRx_handle[iIndex-3] == 'n'))
				 {
					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
						 rub_LEMWHCurrent_asl[iLEM_Index] = rub_LEMWHSocketWHRx_handle[iIndex+1+iLEM_Index];
					 }
					 LEMWH_ReceiveCurrent(lub_index);
					 rub_LEM_WH_Data.rub_LEMWH_ConnectOK[lub_index] = 1;
					 rub_LEMWH_DisconnectTime[lub_index] = 0;
					 ireturn_val = 1;
				 }
				 else
				 {}
				 if((rub_LEMWHSocketWHRx_handle[iIndex-2] == 'l')&&(rub_LEMWHSocketWHRx_handle[iIndex-3] == 'a')&&(rub_LEMWHSocketWHRx_handle[iIndex-11] == 'm')&&(rub_LEMWHSocketWHRx_handle[iIndex-12] == 'I'))
				 {
					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
						 rub_LEMWHImportEnergy_asl[iLEM_Index] = rub_LEMWHSocketWHRx_handle[iIndex+1+iLEM_Index];
					 }
					 LEMWH_ReceiveEnergy(lub_index);
					 rub_LEM_WH_Data.rub_LEMWH_ConnectOK[lub_index] = 1;
					 rub_LEMWH_DisconnectTime[lub_index] = 0;
					 ireturn_val = 1;
					 break;
				 }
				 else
				 {}
			 }
			 else
			 {}
		 }

     return ireturn_val;
}



static void LEMWH_ReceiveEnergy(unsigned char lub_index)
{

	uint8 iLEM_Index;


	//LEMWH_retvalue = Ethernet_TcpIp_Receive(LEMWHSockIdx, pLEMWHRxBuf, LEMWHRxLength);

	                  memset(rub_LEMWHImportEnergy_val, 0, 15);

					 //LEM_retest = rub_LEMWHSocketWHRx_handle[iIndex+1]-'0';


					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
					 	if(rub_LEMWHImportEnergy_asl[iLEM_Index] == '.')
					 	{
					 		rub_LEMWHImportEnergy_val[0] = rub_LEMWHImportEnergy_asl[iLEM_Index+3]-'0';
					 		rub_LEMWHImportEnergy_val[1] = rub_LEMWHImportEnergy_asl[iLEM_Index+2]-'0';
					 		rub_LEMWHImportEnergy_val[2] = rub_LEMWHImportEnergy_asl[iLEM_Index+1]-'0';

					 		switch(iLEM_Index)
					 		{
					 		    case 1:
								{
								   rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
								   break;
								}
					 		    case 2:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									break;
								}
					 		    case 3:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									break;
								}
					 		    case 4:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									rub_LEMWHImportEnergy_val[6] = rub_LEMWHImportEnergy_asl[iLEM_Index-4]-'0';
									break;
								}
					 		    case 5:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									rub_LEMWHImportEnergy_val[6] = rub_LEMWHImportEnergy_asl[iLEM_Index-4]-'0';
									rub_LEMWHImportEnergy_val[7] = rub_LEMWHImportEnergy_asl[iLEM_Index-5]-'0';
									break;
								}
					 		    case 6:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									rub_LEMWHImportEnergy_val[6] = rub_LEMWHImportEnergy_asl[iLEM_Index-4]-'0';
									rub_LEMWHImportEnergy_val[7] = rub_LEMWHImportEnergy_asl[iLEM_Index-5]-'0';
									rub_LEMWHImportEnergy_val[8] = rub_LEMWHImportEnergy_asl[iLEM_Index-6]-'0';
									break;
								}
					 		    case 7:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									rub_LEMWHImportEnergy_val[6] = rub_LEMWHImportEnergy_asl[iLEM_Index-4]-'0';
									rub_LEMWHImportEnergy_val[7] = rub_LEMWHImportEnergy_asl[iLEM_Index-5]-'0';
									rub_LEMWHImportEnergy_val[8] = rub_LEMWHImportEnergy_asl[iLEM_Index-6]-'0';
									rub_LEMWHImportEnergy_val[9] = rub_LEMWHImportEnergy_asl[iLEM_Index-7]-'0';
									break;
								}
					 		    case 8:
								{
									rub_LEMWHImportEnergy_val[3] = rub_LEMWHImportEnergy_asl[iLEM_Index-1]-'0';
									rub_LEMWHImportEnergy_val[4] = rub_LEMWHImportEnergy_asl[iLEM_Index-2]-'0';
									rub_LEMWHImportEnergy_val[5] = rub_LEMWHImportEnergy_asl[iLEM_Index-3]-'0';
									rub_LEMWHImportEnergy_val[6] = rub_LEMWHImportEnergy_asl[iLEM_Index-4]-'0';
									rub_LEMWHImportEnergy_val[7] = rub_LEMWHImportEnergy_asl[iLEM_Index-5]-'0';
									rub_LEMWHImportEnergy_val[8] = rub_LEMWHImportEnergy_asl[iLEM_Index-6]-'0';
									rub_LEMWHImportEnergy_val[9] = rub_LEMWHImportEnergy_asl[iLEM_Index-7]-'0';
									rub_LEMWHImportEnergy_val[10] = rub_LEMWHImportEnergy_asl[iLEM_Index-8]-'0';
									break;
								}
					 		    default:
					 		    	break;
					 		}
					 		break;
					 	}
					 	else
					 	{}
					 }



					 rul_LEMWHImportEnergy_temp = (rub_LEMWHImportEnergy_val[0]+rub_LEMWHImportEnergy_val[1]*10+rub_LEMWHImportEnergy_val[2]*100
							 +rub_LEMWHImportEnergy_val[3]*1000+rub_LEMWHImportEnergy_val[4]*10000+rub_LEMWHImportEnergy_val[5]*100000
							 +rub_LEMWHImportEnergy_val[6]*1000000+rub_LEMWHImportEnergy_val[7]*10000000+rub_LEMWHImportEnergy_val[8]*100000000
							 +rub_LEMWHImportEnergy_val[9]*1000000000+rub_LEMWHImportEnergy_val[10]*10000000000);
					 rub_LEM_WH_Data.rul_LEMWHImportEnergy[lub_index] = rul_LEMWHImportEnergy_temp*0.001;






}






static void LEMWH_ReceiveVoltage(unsigned char lub_index)
{


	uint8 iLEM_Index;


	//LEMWH_retvalue = Ethernet_TcpIp_Receive(LEMWHSockIdx, pLEMWHRxBuf, LEMWHRxLength);

	                 memset(rub_LEMWHVoltage_val, 0, 15);
					 //LEM_retest = rub_LEMWHSocketWHRx_handle[iIndex+1]-'0';

					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
					 	if(rub_LEMWHVoltage_asl[iLEM_Index] == '.')
					 	{
					 		rub_LEMWHVoltage_val[0] = rub_LEMWHVoltage_asl[iLEM_Index+3]-'0';
					 		rub_LEMWHVoltage_val[1] = rub_LEMWHVoltage_asl[iLEM_Index+2]-'0';
					 		rub_LEMWHVoltage_val[2] = rub_LEMWHVoltage_asl[iLEM_Index+1]-'0';

					 		switch(iLEM_Index)
					 		{
					 		    case 1:
								{
								    rub_LEMWHVoltage_val[3] = rub_LEMWHVoltage_asl[iLEM_Index-1]-'0';
								    break;
								}
					 		    case 2:
								{
									rub_LEMWHVoltage_val[3] = rub_LEMWHVoltage_asl[iLEM_Index-1]-'0';
									rub_LEMWHVoltage_val[4] = rub_LEMWHVoltage_asl[iLEM_Index-2]-'0';
									break;
								}
					 		    case 3:
								{
									rub_LEMWHVoltage_val[3] = rub_LEMWHVoltage_asl[iLEM_Index-1]-'0';
									rub_LEMWHVoltage_val[4] = rub_LEMWHVoltage_asl[iLEM_Index-2]-'0';
									rub_LEMWHVoltage_val[5] = rub_LEMWHVoltage_asl[iLEM_Index-3]-'0';
									break;
								}
					 		    case 4:
								{
									rub_LEMWHVoltage_val[3] = rub_LEMWHVoltage_asl[iLEM_Index-1]-'0';
									rub_LEMWHVoltage_val[4] = rub_LEMWHVoltage_asl[iLEM_Index-2]-'0';
									rub_LEMWHVoltage_val[5] = rub_LEMWHVoltage_asl[iLEM_Index-3]-'0';
									rub_LEMWHVoltage_val[6] = rub_LEMWHVoltage_asl[iLEM_Index-4]-'0';
									break;
								}
					 		    default:
					 		    	break;
					 		}
					 		break;
					 	}
					 	else
					 	{}
					 }



					 rul_LEMWHVoltage_temp = (rub_LEMWHVoltage_val[0]+rub_LEMWHVoltage_val[1]*10+rub_LEMWHVoltage_val[2]*100
							 +rub_LEMWHVoltage_val[3]*1000+rub_LEMWHVoltage_val[4]*10000+rub_LEMWHVoltage_val[5]*100000
							 +rub_LEMWHVoltage_val[6]*1000000);
					 rub_LEM_WH_Data.rul_LEMWHVoltage[lub_index] = rul_LEMWHVoltage_temp*0.001;






}



static void LEMWH_ReceiveCurrent(unsigned char lub_index)
{

	uint8 iLEM_Index;

	//LEMWH_retvalue = Ethernet_TcpIp_Receive(LEMWHSockIdx, pLEMWHRxBuf, LEMWHRxLength);

	                 memset(rub_LEMWHCurrent_val, 0, 15);

					 //LEM_retest = rub_LEMWHSocketWHRx_handle[iIndex+1]-'0';


					 for(iLEM_Index = 0;iLEM_Index<15;iLEM_Index++)
					 {
					 	if(rub_LEMWHCurrent_asl[iLEM_Index] == '.')
					 	{
					 		rub_LEMWHCurrent_val[0] = rub_LEMWHCurrent_asl[iLEM_Index+3]-'0';
					 		rub_LEMWHCurrent_val[1] = rub_LEMWHCurrent_asl[iLEM_Index+2]-'0';
					 		rub_LEMWHCurrent_val[2] = rub_LEMWHCurrent_asl[iLEM_Index+1]-'0';

					 		switch(iLEM_Index)
					 		{
					 		    case 1:
								{
								    rub_LEMWHCurrent_val[3] = rub_LEMWHCurrent_asl[iLEM_Index-1]-'0';
								    break;
								}
					 		    case 2:
								{
									rub_LEMWHCurrent_val[3] = rub_LEMWHCurrent_asl[iLEM_Index-1]-'0';
									rub_LEMWHCurrent_val[4] = rub_LEMWHCurrent_asl[iLEM_Index-2]-'0';
									break;
								}
					 		    case 3:
								{
									rub_LEMWHCurrent_val[3] = rub_LEMWHCurrent_asl[iLEM_Index-1]-'0';
									rub_LEMWHCurrent_val[4] = rub_LEMWHCurrent_asl[iLEM_Index-2]-'0';
									rub_LEMWHCurrent_val[5] = rub_LEMWHCurrent_asl[iLEM_Index-3]-'0';
									break;
								}
					 		    case 4:
								{
									rub_LEMWHCurrent_val[3] = rub_LEMWHCurrent_asl[iLEM_Index-1]-'0';
									rub_LEMWHCurrent_val[4] = rub_LEMWHCurrent_asl[iLEM_Index-2]-'0';
									rub_LEMWHCurrent_val[5] = rub_LEMWHCurrent_asl[iLEM_Index-3]-'0';
									rub_LEMWHCurrent_val[6] = rub_LEMWHCurrent_asl[iLEM_Index-4]-'0';
									break;
								}
					 		    default:
					 		    	break;
					 		}
					 		break;
					 	}
					 	else
					 	{}
					 }



					 rul_LEMWHCurrent_temp = (rub_LEMWHCurrent_val[0]+rub_LEMWHCurrent_val[1]*10+rub_LEMWHCurrent_val[2]*100
							 +rub_LEMWHCurrent_val[3]*1000+rub_LEMWHCurrent_val[4]*10000+rub_LEMWHCurrent_val[5]*100000
							 +rub_LEMWHCurrent_val[6]*1000000);
					 rub_LEM_WH_Data.rul_LEMWHCurrent[lub_index] = rul_LEMWHCurrent_temp*0.001;


}






static uint8 LEMWH_ReceiveStatusHandle(unsigned char lub_index)
{

	uint8 LEMWH_retvalue;
	uint8 iIndex;
	uint8 iLEM_Index;
	uint16 iLength;
	uint8 ireturn_val=0;

		 for(iIndex = 0;iIndex<rul_iLength;iIndex++)
		 {

	    	 if(rub_LEMWHSocketWHRx_handle[0] != 'H')
	    	 {
	    		 break;
	    	 }
	    	 else
	    	 {}
			 if(rub_LEMWHSocketWHRx_handle[iIndex] == ':')
			 {

				 if((rub_LEMWHSocketWHRx_handle[iIndex-2] == 'k')&&(rub_LEMWHSocketWHRx_handle[iIndex-3] == 'O')&&(rub_LEMWHSocketWHRx_handle[iIndex-12] == 'k')&&(rub_LEMWHSocketWHRx_handle[iIndex-13] == 'n')&&(rub_LEMWHSocketWHRx_handle[iIndex-11] == 'S'))
				 {

					 if(rub_LEMWHSocketWHRx_handle[iIndex+1] == 't')
					 {
						 rub_LEM_WH_Data.rub_suLinkStatusIsOk[lub_index] = 1;
					 }
					 else if(rub_LEMWHSocketWHRx_handle[iIndex+1] == 'f')
					 {
						 rub_LEM_WH_Data.rub_suLinkStatusIsOk[lub_index] = 0;
					 }
					 else
					 {}
					 rub_LEMWH_retcnt = 0;
					 ireturn_val = 1;
					 break;
				 }
				 else
				 {}

			 }
			 else
			 {}
		 }

     return ireturn_val;
}






static uint8 LEMWH_ReceiveChangeIPHandle(unsigned char lub_index)
{

	uint8 LEMWH_retvalue;
	uint8 iIndex;
	uint8 iLEM_Index;
	uint16 iLength;
	uint8 ireturn_val=0;

		 for(iIndex = 0;iIndex<rul_iLength;iIndex++)
		 {
	    	 if(rub_LEMWHSocketWHRx_handle[0] != 'H')
	    	 {
	    		 break;
	    	 }
	    	 else
	    	 {}
			 if(rub_LEMWHSocketWHRx_handle[iIndex] == ':')
			 {

				 if((rub_LEMWHSocketWHRx_handle[iIndex-2] == 't')&&(rub_LEMWHSocketWHRx_handle[iIndex-3] == 'l'))
				 {

					 if(rub_LEMWHSocketWHRx_handle[iIndex+1] == '1')
					 {
						 rub_LEM_WH_Data.rub_sendChangeIPOk[lub_index] = 1;
					 }
					 else
					 {
						 rub_LEM_WH_Data.rub_sendChangeIPOk[lub_index] = 0;
					 }
					 ireturn_val = 1;
					 break;
				 }
				 else
				 {}

			 }
			 else
			 {}
		 }

     return ireturn_val;
}

/*LEM*/
