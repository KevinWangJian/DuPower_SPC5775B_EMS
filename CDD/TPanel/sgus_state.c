#include "sgus_state.h"
#include "sgus_api.h"
#include "Rte_Asw_Swc.h"
#include "ASW_RTE.h"
#include "Rte_IoHwAb.h"
#include "sgus_io.h"
#include "Eep.h"

#define SGUS_STATE_TASK_PEROID  500

static volatile sgus_parser_t   SGUS_Parser;
static volatile sigupdatefunc_t SGUS_SignalUpdate;
static volatile sgus_signal_t   SGUS_Signal;


static volatile sgus_usertype_t SGUS_UserType[2] = {UserType_Null, UserType_Null}; //0 for Null, 1 for RFID, 2 for CreditCard, 3 for QRCode, 4 for password;
static volatile uint8_t SGUS_CardNumBackup[2][32]; //Backup CardNum to determine 
static volatile float SGUS_Patch_WH_Energy_Start[2];

const static uint8_t SuperUserName[7] = "123456";
const static uint8_t SuperPassWord[7] = "666666";

struct
{
    uint8_t  SerialNumber[32];
    uint8_t  NetworkState;
    uint8_t  CurrentPlug;
    uint16_t TimoutCount;
    uint8_t  ButtonBack;
    uint8_t  ButtonConfirm;
    uint8_t  ButtonHomepage;
    uint8_t  ButtonTest;
}Data_Global;

struct
{
    uint8_t ButtonStop_PlugA;
    uint8_t ButtonStop_PlugB;
    uint8_t ButtonBase_PlugA;
    uint8_t ButtonBase_PlugB;
    uint8_t ButtonLangSel;
    uint8_t MarkedWord_PlugA;
    uint8_t MarkedWord_PlugB;

    sgus_plugstate_t PlugState_PlugA;
    sgus_plugstate_t PlugState_PlugB;
    uint16_t RemainingTime_PlugA;
    uint16_t RemainingTime_PlugB;
    uint8_t SOCGreen_PlugA;
    uint8_t SOCGreen_PlugB;
    uint8_t SOCRed_PlugA;
    uint8_t SOCRed_PlugB;
    uint32_t ChargePrice;
}Data_Homepage;

struct
{
	uint8_t LangEnum;
}Data_LangSel;

struct
{
    uint8_t UserName[32];
    uint8_t PassWord[32];
}Data_Login;

struct
{
	uint8_t PaymentMethod;
}Data_PaymentMethod;

struct
{
	uint8_t QRCode[256];
}Data_QRCode;

struct
{
    uint8_t ButtonAutoFull;
    uint8_t ButtonMoney;
    uint8_t ButtonTime;
    uint8_t ButtonEnergy;
}Data_ModSel;

struct
{
	uint16_t ValueMoney;
	uint16_t ValueTime;
	uint16_t ValueEnergy;
}Data_ChargeValue;

struct
{
    uint32_t Current;
    uint32_t Voltage;
    uint32_t Energy;
    uint32_t ChargingTime;
    uint32_t RemaingTime;
    uint32_t Cost;
    uint32_t Power;
    uint8_t ButtonStopCharge;
    sgus_plugstate_t PlugState;
    
    uint8_t SOCGreen;
    uint8_t SOCRed;
    uint8_t ChargingGIF;
}Data_WorkInfo;

struct
{
    uint8_t RFIDSta;
}Data_WaitRFID;

struct
{
    uint8_t RFIDCardNum[32];
    uint8_t RFIDCardBalance[32];
    uint8_t RFIDCardPoint[32];
}Data_RFIDInfo;


struct
{
    uint8_t RFIDFaultReason;
}Data_RFIDFault;



struct
{
    uint8_t PassWord[32];
}Data_Logout;




struct
{
    uint32_t ENERGY;
    uint32_t Cost;
    uint32_t ChargedTime;
    uint32_t StopTime;
    uint8_t  TransactionNum[32];
    uint8_t  StopReason[32];
    uint32_t StartSOC;
    uint32_t StopSOC;
    uint32_t ChargeProgress;
    uint8_t  UserInfo[32];
    uint32_t Balance;
}Data_StopInfo;

struct
{
    uint8_t PassWord[32];
}Data_SysConfigLogin;

struct
{
    uint8_t ButtonSysConfig;
    uint8_t ButtonInfoCheck;
    uint8_t ButtonChargeRecord;
    uint8_t ButtonFaultRecord;
}Data_InfoManage;

struct
{
    uint8_t ButtonPagePowerOffSelect;
    uint8_t ButtonPageInputControl;
    uint8_t ButtonAreaSet;
    uint8_t ButtonPasswordReset;
}Data_SysConfig;

struct
{
	uint8_t ButtonPageSafePowerOff;
	uint8_t ButtonPageUserPowerOff;
}Data_PowerOffSelect;


struct
{
    uint8_t StateHighVoltage;
    uint8_t ButtonSafePowerOff;
}Data_SafePowerOff;

struct
{
	uint8_t IconUserPowerOff;
	uint8_t ButtonUserPowerOff;
}Data_UserPowerOff;

struct
{
    uint8_t InputControlEnum;
}Data_InputControl;

void SGUS_StateInit(void);



void SGUS_StateHomepageInit(void);
void SGUS_StateLangSelectInit(void);
void SGUS_StatePlugUnconnectInit(void);
void SGUS_StateVIPLoginInit(void);
void SGUS_StateVIPLogoutInit(void);
void SGUS_StatePaymentMethodInit(void);
void SGUS_StateCardLoginInit(void);
void SGUS_StateStartCardAuthInit(void);
void SGUS_StateCardAuthFailInit(void);
void SGUS_StateQRLoginInit(void);
void SGUS_StateChargeModSelInit(void);
void SGUS_StateChargeMoneyInit(void);
void SGUS_StateChargeTimeInit(void);
void SGUS_StateChargeEnergyInit(void);
void SGUS_StateStartChargeInit(void);
void SGUS_StateStartErrInit(void);
void SGUS_StateWorkInfoInit(void);
void SGUS_StateCardLogoutInit(void);
void SGUS_StateStopCardAuthInit(void);
void SGUS_StateStopChargeInit(void);
void SGUS_StateStopInfoInit(void);
void SGUS_StateSysManagerLoginInit(void);
void SGUS_StateSystermManagerInit(void);
void SGUS_StatePowerOffSelectInit(void);
void SGUS_StateSafePowerOffInit(void);
void SGUS_StateUserPowerOffInit(void);
void SGUS_StateStationInputControlInit(void);
void SGUS_StateSysConfigSuccessInit(void);
void SGUS_StateSysConfigFailueInit(void);

void SGUS_StateHomepageUpdate(void);
void SGUS_StateLangSelectUpdate(void);
void SGUS_StatePlugUnconnectUpdate(void);
void SGUS_StateVIPLoginUpdate(void);
void SGUS_StateVIPLogoutUpdate(void);
void SGUS_StatePaymentMethodUpdate(void);
void SGUS_StateCardLoginUpdate(void);
void SGUS_StateStartCardAuthUpdate(void);
void SGUS_StateCardAuthFailUpdate(void);
void SGUS_StateQRLoginUpdate(void);
void SGUS_StateChargeModSelUpdate(void);
void SGUS_StateChargeMoneyUpdate(void);
void SGUS_StateChargeTimeUpdate(void);
void SGUS_StateChargeEnergyUpdate(void);
void SGUS_StateStartChargeUpdate(void);
void SGUS_StateStartErrUpdate(void);
void SGUS_StateWorkInfoUpdate(void);
void SGUS_StateCardLogoutUpdate(void);
void SGUS_StateStopCardAuthUpdate(void);
void SGUS_StateStopChargeUpdate(void);
void SGUS_StateStopInfoUpdate(void);
void SGUS_StateSysManagerLoginUpdate(void);
void SGUS_StateSystermManagerUpdate(void);
void SGUS_StatePowerOffSelectUpdate(void);
void SGUS_StateSafePowerOffUpdate(void);
void SGUS_StateUserPowerOffUpdate(void);
void SGUS_StateStationInputControlUpdate(void);
void SGUS_StateSysConfigSuccessUpdate(void);
void SGUS_StateSysConfigFailueUpdate(void);



void SGUS_StateHomepage(parser_t *me, signal_t sig);
void SGUS_StateLangSelect(parser_t *me, signal_t sig);
void SGUS_StatePlugUnconnect(parser_t * me, signal_t sig);
void SGUS_StateVIPLogin(parser_t * me, signal_t sig);
void SGUS_StateVIPLogout(parser_t * me, signal_t sig);
void SGUS_StatePaymentMethod(parser_t * me, signal_t sig);
void SGUS_StateCardLogin(parser_t * me, signal_t sig);
void SGUS_StateStartCardAuth(parser_t *me, signal_t sig);
void SGUS_StateCardAuthFail(parser_t * me, signal_t sig);
void SGUS_StateQRLogin(parser_t * me, signal_t sig);
void SGUS_StateChargeModSel(parser_t * me, signal_t sig);
void SGUS_StateChargeMoney(parser_t * me, signal_t sig);
void SGUS_StateChargeTime(parser_t * me, signal_t sig);
void SGUS_StateChargeEnergy(parser_t * me, signal_t sig);
void SGUS_StateStartCharge(parser_t * me, signal_t sig);
void SGUS_StateStartErr(parser_t * me, signal_t sig);
void SGUS_StateWorkInfo(parser_t *me, signal_t sig);
void SGUS_StateCardLogout(parser_t * me, signal_t sig);
void SGUS_StateStopCardAuth(parser_t * me, signal_t sig);
void SGUS_StateStopCharge(parser_t * me, signal_t sig);
void SGUS_StateStopInfo(parser_t * me, signal_t sig);
void SGUS_StateSysManagerLogin(parser_t * me, signal_t sig);
void SGUS_StateSystermManager(parser_t * me, signal_t sig);
void SGUS_StatePowerOffSelect(parser_t * me, signal_t sig);
void SGUS_StateSafePowerOff(parser_t * me, signal_t sig);
void SGUS_StateUserPowerOff(parser_t * me, signal_t sig);
void SGUS_StateStationInputControl(parser_t * me, signal_t sig);
void SGUS_StateSysConfigSuccess(parser_t * me, signal_t sig);
void SGUS_StateSysConfigFailue(parser_t * me, signal_t sig);



void SGUS_StateSetTimeoutValue(uint8_t value_s);
void SGUS_StateTimeoutProcess(void);
void SGUS_StateButtonTestProcess(void);
void SGUS_StatePageCheckProcess(sgus_pageindex_t page);
void SGUS_StateCloudProcess(void);




void SGUS_StateInit(void)
{
    uint8_t tmp;
    
    SGUS_GetButtonStop_PlugA(&tmp);
    SGUS_GetButtonStop_PlugB(&tmp);
    SGUS_GetButtonBase_PlugA(&tmp);
    SGUS_GetButtonBase_PlugB(&tmp);
    SGUS_GetButtonLangSelect(&tmp);

    
    SGUS_SetPlugState_PlugA(SGUS_PlugStateIdle);
    SGUS_SetPlugState_PlugB(SGUS_PlugStateIdle);
    
    SGUS_SetSOCGreen_PlugA(SGUS_SOC_NONE);
    SGUS_SetSOCGreen_PlugB(SGUS_SOC_NONE);
    SGUS_SetSOCRed_PlugA(SGUS_SOC_NONE);
    SGUS_SetSOCRed_PlugB(SGUS_SOC_NONE);
    
    SGUS_SetSerialNum(SGUS_SERIAL_NUM);
    SGUS_SetCurrentPage(SGUS_Page_Homepage);
    SGUS_Parser.currentstate = SGUS_STA_HOMEPAGE;
    SGUS_SignalUpdate = SGUS_StateHomepageUpdate;
    TRAN(&SGUS_Parser, SGUS_StateHomepage);
};





void SGUS_StateHomepageInit(void)
{
	uint8_t  ccu1state;
	uint8_t  ccu2state;
	uint8_t  ccu1_cc1state;
	uint8_t  ccu2_cc1state;
	uint8_t  socA;
	uint8_t  socB;
	uint16_t remaintimeA;
	uint16_t remaintimeB;

	sgus_plugstate_t plugstate_plugA;
	sgus_plugstate_t plugstate_plugB;

    uint8_t tmp;

    //Clear input signal to avoid Wrong State
//    SGUS_GetButtonStop_PlugA(&tmp);
//    SGUS_GetButtonStop_PlugB(&tmp);
    SGUS_GetButtonBase_PlugA(&tmp);
    SGUS_GetButtonBase_PlugB(&tmp);
    SGUS_GetButtonLangSelect(&tmp);


    Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_NONE);
	Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_NONE);

    Rte_Write_TouchPanel_LeftCCUStartCheck_flg(0);
	Rte_Write_TouchPanel_RightCCUStartCheck_flg(0);

    Rte_Write_TouchPanel_LeftCCUStopCheck_flg(0);
	Rte_Write_TouchPanel_RightCCUStopCheck_flg(0);

    Rte_Write_TouchPanel_UserStopCCU1Chg_flg(0);
    Rte_Write_TouchPanel_UserStopCCU2Chg_flg(0);

    Rte_Write_TouchPanel_LeftVIPChrgCheckSuccess_flg(0);
    Rte_Write_TouchPanel_RightVIPChrgCheckSuccess_flg(0);
    
    Rte_Write_TouchPanel_LeftVIPChrgStopSuccess_flg(0);
    Rte_Write_TouchPanel_RightVIPChrgStopSuccess_flg(0);


    //update value from bsw
    ccu1state     = get_GeECCR_CCU1CCUSTATE_enum();
	ccu1_cc1state = get_GeECCR_CCU1CCUCC1STATE_enum();

	ccu2state     = get_GeECCR_CCU2CCUSTATE_enum();
	ccu2_cc1state = get_GeECCR_CCU2CCUCC1STATE_enum();

	remaintimeA   = get_GcECCR_CCU1BCSSPN3079TimeRemain_min();
	remaintimeB   = get_GcECCR_CCU2BCSSPN3079TimeRemain_min();

	socA          = get_GcECCR_CCU1BCSSPN3078SOC_Pct();
	socB          = get_GcECCR_CCU2BCSSPN3078SOC_Pct();

	//update variables in Page Homepage
	//PlugA
	if(SGUS_CCU_STATE_STANDBY == ccu1state)
	{
		plugstate_plugA = SGUS_PlugStateIdle;

		if(SGUS_CCU_CC1_STATE_CONNECT == ccu1_cc1state)
		{
			plugstate_plugA = SGUS_PlugStateConnect;
		}
	}
	else if(SGUS_CCU_STATE_CHARGING == ccu1state)
	{
		plugstate_plugA = SGUS_PlugStateCharging;
	}
	else if(SGUS_CCU_STATE_STOPCHARGE == ccu1state || SGUS_CCU_STATE_POWERDOWN == ccu1state)
	{
		plugstate_plugA = SGUS_PlugStateComplete;
	}
	else if(SGUS_CCU_STATE_FAULT == ccu1state)
	{
		plugstate_plugA = SGUS_PlugStateFault;
	}
	else
	{
		plugstate_plugA = SGUS_PlugStateIdle;
	}

	SGUS_SetPlugState_PlugA(plugstate_plugA);

	//Clear Normal(green) or Error(red) SOC Value if needed
	if(SGUS_PlugStateIdle == plugstate_plugA ||\
	   SGUS_PlugStateConnect == plugstate_plugA)
	{
			SGUS_SetSOCGreen_PlugA(SGUS_SOC_NONE);
			SGUS_SetSOCRed_PlugA(SGUS_SOC_NONE);
	}
	else
	{
		if(SGUS_PlugStateFault == plugstate_plugA)
		{
				SGUS_SetSOCGreen_PlugA(SGUS_SOC_NONE);
		}
		else
		{
				SGUS_SetSOCRed_PlugA(SGUS_SOC_NONE);
		}
	}

	//Update SOC and Remaintime if needed
	switch(plugstate_plugA)
	{
		case SGUS_PlugStateCharging :
			SGUS_SetRemainingTime_PlugA(remaintimeA);
		case SGUS_PlugStateComplete :
			SGUS_SetSOCGreen_PlugA(socA);
			break;
		case SGUS_PlugStateFault :
			SGUS_SetSOCRed_PlugA(socA);
			break;
		default :
			break;
	}


	//PlugB
	if(SGUS_CCU_STATE_STANDBY == ccu2state)
	{
		plugstate_plugB = SGUS_PlugStateIdle;

		if(SGUS_CCU_CC1_STATE_CONNECT == ccu2_cc1state)
		{
			plugstate_plugB = SGUS_PlugStateConnect;
		}
	}
	else if(SGUS_CCU_STATE_CHARGING == ccu2state)
	{
		plugstate_plugB = SGUS_PlugStateCharging;
	}
	else if(SGUS_CCU_STATE_STOPCHARGE == ccu2state || SGUS_CCU_STATE_POWERDOWN == ccu2state)
	{
		plugstate_plugB = SGUS_PlugStateComplete;
	}
	else if(SGUS_CCU_STATE_FAULT == ccu2state)
	{
		plugstate_plugB = SGUS_PlugStateIdle;
	}
	else
	{
//		plugstate_plugB = SGUS_PlugStateFault;
	}

	SGUS_SetPlugState_PlugB(plugstate_plugB);

	if(SGUS_PlugStateIdle == plugstate_plugB ||\
	   SGUS_PlugStateConnect == plugstate_plugB)
	{
		SGUS_SetSOCGreen_PlugB(SGUS_SOC_NONE);
		SGUS_SetSOCRed_PlugB(SGUS_SOC_NONE);
	}
	else
	{
		if(SGUS_PlugStateFault == plugstate_plugB)
		{
			SGUS_SetSOCGreen_PlugB(SGUS_SOC_NONE);
		}
		else
		{
			SGUS_SetSOCRed_PlugB(SGUS_SOC_NONE);
		}
	}

	switch(plugstate_plugB)
	{
		case SGUS_PlugStateCharging :
			SGUS_SetRemainingTime_PlugB(remaintimeB);
		case SGUS_PlugStateComplete :
			SGUS_SetSOCGreen_PlugB(socB);
			break;
		case SGUS_PlugStateFault :
			SGUS_SetSOCRed_PlugB(socB);
			break;
		default :
			break;
	}

    //Change to Homepage
    SGUS_SetCurrentPage(SGUS_Page_Homepage); 
}

void SGUS_StateHomepageUpdate(void)
{
    static sgus_plugstate_t plugstate_plugA = SGUS_PlugStateIdle;
    static sgus_plugstate_t plugstate_plugB = SGUS_PlugStateIdle;
    static uint8_t currentplug = 0xFF;
    
    uint8_t  ccu1state;
    uint8_t  ccu2state;
    uint8_t  ccu1_cc1state;
    uint8_t  ccu2_cc1state;
    uint8_t  socA;
    uint8_t  socB;
    uint16_t remaintimeA;
    uint16_t remaintimeB;


    SGUS_StatePageCheckProcess(SGUS_Page_Homepage);

    SGUS_GetPlugState_PlugA(&Data_Homepage.PlugState_PlugA);
    SGUS_GetPlugState_PlugB(&Data_Homepage.PlugState_PlugB);

    SGUS_GetRemainingTime_PlugA(&Data_Homepage.RemainingTime_PlugA);
    SGUS_GetRemainingTime_PlugB(&Data_Homepage.RemainingTime_PlugB);

    SGUS_GetSOCGreen_PlugA(&Data_Homepage.SOCGreen_PlugA);
    SGUS_GetSOCGreen_PlugB(&Data_Homepage.SOCGreen_PlugB);

    SGUS_GetSOCRed_PlugA(&Data_Homepage.SOCRed_PlugA);
    SGUS_GetSOCRed_PlugB(&Data_Homepage.SOCRed_PlugB);

    SGUS_GetButtonBase_PlugA(&Data_Homepage.ButtonBase_PlugA);
    SGUS_GetButtonBase_PlugB(&Data_Homepage.ButtonBase_PlugB);

//    SGUS_GetButtonStop_PlugA(&Data_Homepage.ButtonStop_PlugA);
//    SGUS_GetButtonStop_PlugB(&Data_Homepage.ButtonStop_PlugB);
    
    SGUS_GetButtonLangSelect(&Data_Homepage.ButtonLangSel);
    
    ccu1state     = get_GeECCR_CCU1CCUSTATE_enum();
    ccu1_cc1state = get_GeECCR_CCU1CCUCC1STATE_enum();

    ccu2state     = get_GeECCR_CCU2CCUSTATE_enum();
    ccu2_cc1state = get_GeECCR_CCU2CCUCC1STATE_enum();

    remaintimeA   = get_GcECCR_CCU1BCSSPN3079TimeRemain_min();
    remaintimeB   = get_GcECCR_CCU2BCSSPN3079TimeRemain_min();

    socA          = get_GcECCR_CCU1BCSSPN3078SOC_Pct();
    socB          = get_GcECCR_CCU2BCSSPN3078SOC_Pct();
    
    //Check CCU and CCU_CC1 State to determine Charger State
    if(SGUS_CCU_STATE_STANDBY == ccu1state)
    {
        plugstate_plugA = SGUS_PlugStateIdle;

        if(SGUS_CCU_CC1_STATE_CONNECT == ccu1_cc1state)
        {
            plugstate_plugA = SGUS_PlugStateConnect;
        }
    }
    else if(SGUS_CCU_STATE_CHARGING == ccu1state)
    {
        plugstate_plugA = SGUS_PlugStateCharging;
    }
    else if(SGUS_CCU_STATE_STOPCHARGE == ccu1state || SGUS_CCU_STATE_POWERDOWN == ccu1state)
    {
        plugstate_plugA = SGUS_PlugStateComplete;
    }
    else if(SGUS_CCU_STATE_FAULT == ccu1state)
    {
        plugstate_plugA = SGUS_PlugStateFault;
    }
    else
    {
    	plugstate_plugA = SGUS_PlugStateIdle;
    }

    //Update screen state if needed
    if(plugstate_plugA != Data_Homepage.PlugState_PlugA)
    {
        SGUS_SetPlugState_PlugA(plugstate_plugA);
    }

    //Clear Normal(green) or Error(red) SOC Value if needed
    if(SGUS_PlugStateIdle == plugstate_plugA ||\
       SGUS_PlugStateConnect == plugstate_plugA)
    {
        if(SGUS_SOC_NONE != Data_Homepage.SOCGreen_PlugA)
        {
            SGUS_SetSOCGreen_PlugA(SGUS_SOC_NONE);
        }
        if(SGUS_SOC_NONE != Data_Homepage.SOCRed_PlugA)
        {
            SGUS_SetSOCRed_PlugA(SGUS_SOC_NONE);
        }
    }
    else
    {
        if(SGUS_PlugStateFault == plugstate_plugA)
        {
            if(SGUS_SOC_NONE != Data_Homepage.SOCGreen_PlugA) //Fault Mode show err,clear nor
            {
                SGUS_SetSOCGreen_PlugA(SGUS_SOC_NONE);
            }
        }
        else
        {
            if(SGUS_SOC_NONE != Data_Homepage.SOCRed_PlugA)//other mode show nor,clear err;
            {
                SGUS_SetSOCRed_PlugA(SGUS_SOC_NONE);

            }
        }
    }

    //Update SOC and Remaintime if needed
    switch(plugstate_plugA)
    {
        case SGUS_PlugStateCharging :
            if(remaintimeA != Data_Homepage.RemainingTime_PlugA)
            {
                SGUS_SetRemainingTime_PlugA(remaintimeA);
            }
        case SGUS_PlugStateComplete :
            if(socA != Data_Homepage.SOCGreen_PlugA)
            {
                SGUS_SetSOCGreen_PlugA(socA);
            }
            break;
        case SGUS_PlugStateFault :
            if(socA != Data_Homepage.SOCRed_PlugA)
            {
                SGUS_SetSOCRed_PlugA(socA);
            }
            break;
        default :
        	break;
    }



    //CCU2 is same as CCU1
    if(SGUS_CCU_STATE_STANDBY == ccu2state)
    {
        plugstate_plugB = SGUS_PlugStateIdle;
        
        if(SGUS_CCU_CC1_STATE_CONNECT == ccu2_cc1state)
        {
            plugstate_plugB = SGUS_PlugStateConnect;
        }
    }
    else if(SGUS_CCU_STATE_CHARGING == ccu2state)
    {
        plugstate_plugB = SGUS_PlugStateCharging;
    }
    else if(SGUS_CCU_STATE_STOPCHARGE == ccu2state || SGUS_CCU_STATE_POWERDOWN == ccu2state)
    {
        plugstate_plugB = SGUS_PlugStateComplete;
    }
    else if(SGUS_CCU_STATE_FAULT == ccu2state)
    {
        plugstate_plugB = SGUS_PlugStateFault;
    }
    else
    {
    	plugstate_plugB = SGUS_PlugStateIdle;
    }

    if(plugstate_plugB != Data_Homepage.PlugState_PlugB)
    {
        SGUS_SetPlugState_PlugB(plugstate_plugB);
    }

    if(SGUS_PlugStateIdle == plugstate_plugB ||\
       SGUS_PlugStateConnect == plugstate_plugB)
    {
        if(SGUS_SOC_NONE != Data_Homepage.SOCGreen_PlugB)
        {
            SGUS_SetSOCGreen_PlugB(SGUS_SOC_NONE);
        }
        if(SGUS_SOC_NONE != Data_Homepage.SOCRed_PlugB)
        {
            SGUS_SetSOCRed_PlugB(SGUS_SOC_NONE);
        }
    }
    else
    {
        if(SGUS_PlugStateFault == plugstate_plugB)
        {
            if(SGUS_SOC_NONE != Data_Homepage.SOCGreen_PlugB)
            {
                SGUS_SetSOCGreen_PlugB(SGUS_SOC_NONE);
            }
        }
        else
        {
            if(SGUS_SOC_NONE != Data_Homepage.SOCRed_PlugB)
            {
                SGUS_SetSOCRed_PlugB(SGUS_SOC_NONE);
            }
        }
    }

    switch(plugstate_plugB)
    {
        case SGUS_PlugStateCharging :
            if(remaintimeB != Data_Homepage.RemainingTime_PlugB)
            {
                    SGUS_SetRemainingTime_PlugB(remaintimeB);
            }
        case SGUS_PlugStateComplete :
            if(socB != Data_Homepage.SOCGreen_PlugB)
            {
                    SGUS_SetSOCGreen_PlugB(socB);
            }
            break;
        case SGUS_PlugStateFault :
            if(socB != Data_Homepage.SOCRed_PlugB)
            {
                    SGUS_SetSOCRed_PlugB(socB);
            }
            break;
        default :
        	break;
    }


    //Sig in Standby to Update 
    SGUS_Signal = SGUS_SIG_DEFAULT;
    
    if(TRUE == Data_Homepage.ButtonBase_PlugA)
    {
        SGUS_Signal = SGUS_SIG_BUTTONA;
        Data_Global.CurrentPlug = 0;
    }
    else if(TRUE == Data_Homepage.ButtonBase_PlugB)
    {
        SGUS_Signal = SGUS_SIG_BUTTONB;
        Data_Global.CurrentPlug = 1;
    }
    else if(TRUE == Data_Homepage.ButtonStop_PlugA)
    {
        if(SGUS_CCU_STATE_CHARGING == ccu1state)
        {
            SGUS_Signal = SGUS_SIG_STOPCHARGE;
            Data_Global.CurrentPlug = 0;
        }
    }
    else if(TRUE == Data_Homepage.ButtonStop_PlugB)
    {
        if(SGUS_CCU_STATE_CHARGING == ccu2state)
        {
            SGUS_Signal = SGUS_SIG_STOPCHARGE;
            Data_Global.CurrentPlug = 1;
        }
    }
    else if(TRUE == Data_Homepage.ButtonLangSel)
    {
    	SGUS_Signal = SGUS_SIG_LANGSEL;
    }
    else
    {
        SGUS_StateButtonTestProcess();
    }
    
    //Update Current Charger to Control if needed
	if(currentplug != Data_Global.CurrentPlug)
	{
		currentplug = Data_Global.CurrentPlug;
		SGUS_SetCurrentPlug(Data_Global.CurrentPlug);

	}
}

void SGUS_State4ButtonBase_PlugA(parser_t *me)
{
    switch(Data_Homepage.PlugState_PlugA)
    {
    /*
        case SGUS_PlugStateIdle :
        	TRAN_EE(me, SGUS_StatePlugUnconnect);
        	break;
        	*/
        case SGUS_PlugStateConnect :
            TRAN_EE(me, SGUS_StatePaymentMethod);
            break;
        case SGUS_PlugStateCharging :
        	if(UserType_RFID == SGUS_UserType[0] || UserType_CreditCard == SGUS_UserType[0])
        	 {
				TRAN_EE(me, SGUS_StateWorkInfo);
			}
        	break;
        case SGUS_PlugStateComplete :
            if(UserType_RFID == SGUS_UserType[0] || UserType_CreditCard == SGUS_UserType[0])
            {
                TRAN_EE(me, SGUS_StateCardLogout);
            }
            else if(UserType_VIP == SGUS_UserType[0])
            {
                TRAN_EE(me, SGUS_StateVIPLogout);
            }
            break;
        /*
        case SGUS_PlugStateComplete :

            ccustate = get_GeECCR_CCU1CCUSTATE_enum();

            if(SGUS_CCU_STATE_POWERDOWN == ccustate)
            {
                TRAN_EE(me, SGUS_StateWorkInfo);
            }
            break;
        */
        /*
        case SGUS_ChargerStateFault :
            TRAN_EE(me, SGUS_StateFaultInfo);
            break;
        */
        default :
            break;
    }
}

void SGUS_State4ButtonBase_PlugB(parser_t *me)
{
    switch(Data_Homepage.PlugState_PlugB)
    {
    /*
        case SGUS_PlugStateIdle :
        	TRAN_EE(me, SGUS_StatePlugUnconnect);
        	break;
        	*/
        case SGUS_PlugStateConnect :
            TRAN_EE(me, SGUS_StatePaymentMethod);
            break;
        case SGUS_PlugStateCharging :
        case SGUS_PlugStateComplete :
            if(UserType_RFID == SGUS_UserType[1] || UserType_CreditCard == SGUS_UserType[1])
            {
                TRAN_EE(me, SGUS_StateCardLogout);
            }
            else if(UserType_VIP == SGUS_UserType[1])
            {
                TRAN_EE(me, SGUS_StateVIPLogout);
            }
            break;
        /*
        case SGUS_PlugStateComplete :
            #if defined(SGUS_STATE_DEBUG) && (1 == SGUS_STATE_DEBUG)
            ccustate = GeECCR_CCU2CCUSTATE_enum_debug;
            #else
            ccustate = get_GeECCR_CCU2CCUSTATE_enum();
            #endif
            if(SGUS_CCU_STATE_POWERDOWN == ccustate)
            {
                TRAN_EE(me, SGUS_StateWorkInfo);
            }
            break;
        */
        /*
        case SGUS_ChargerStateFault :
            TRAN_EE(me, SGUS_StateFaultInfo);
            break;
        */    
        default :
            break;
    }
}

void SGUS_StateHomepage(parser_t *me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateHomepageInit();
            SGUS_SignalUpdate = SGUS_StateHomepageUpdate;
            me->currentstate = SGUS_STA_HOMEPAGE;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_HOMEPAGE;
            break;
        case SGUS_SIG_BUTTONA :
            SGUS_State4ButtonBase_PlugA(me);
            break;
        case SGUS_SIG_BUTTONB :
            SGUS_State4ButtonBase_PlugB(me);
            break;
#if 0 //Don't need anymore
        case SGUS_SIG_STOPCHARGE :
            if(UserType_RFID == SGUS_UserType[Data_Global.CurrentPlug] || UserType_CreditCard == SGUS_UserType[Data_Global.CurrentPlug])
            {
                TRAN_EE(me, SGUS_StateCardLogout);
            }
            else if(UserType_VIP == SGUS_UserType[Data_Global.CurrentPlug])
            {
                TRAN_EE(me, SGUS_StateVIPLogout);
            }
            break;
#endif
        case SGUS_SIG_TEST :
            TRAN_EE(me, SGUS_StatePowerOffSelect);
            break;
        case SGUS_SIG_LANGSEL :
        	TRAN_EE(me, SGUS_StateLangSelect);
        	break;
        default :
            break;
    }
};


void SGUS_StateLangSelectInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonLangEnum(&tmp);
	SGUS_GetButtonBack(&tmp);
	SGUS_SetCurrentPage(SGUS_Page_LangSelect);
}

void SGUS_StateLangSelectUpdate(void)
{
	SGUS_StatePageCheckProcess(SGUS_Page_LangSelect);
	SGUS_GetButtonBack(&Data_Global.ButtonBack);
	SGUS_GetButtonLangEnum(&Data_LangSel.LangEnum);

	SGUS_Signal = SGUS_SIG_DEFAULT;
	if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
	else if(1 == Data_LangSel.LangEnum)
	{
		SGUS_SetLangEnum(SGUS_LANG_CN);
		SGUS_Signal = SGUS_SIG_LANG_CN;
	}
	else if(2 == Data_LangSel.LangEnum)
	{
		SGUS_SetLangEnum(SGUS_LANG_EN);
		SGUS_Signal = SGUS_SIG_LANG_EN;
	}
}

void SGUS_StateLangSelect(parser_t *me, signal_t sig)
{
	 switch(sig)
	    {
	        case SGUS_SIG_ENTRY :
	        	SGUS_StateLangSelectInit();
	            SGUS_SignalUpdate = SGUS_StateLangSelectUpdate;
	            me->currentstate = SGUS_STA_LANGSEL;
	            break;
	        case SGUS_SIG_EXIT :
	            me->prestate = SGUS_STA_LANGSEL;
	            break;
	        case SGUS_SIG_BACK :
	        case SGUS_SIG_LANG_CN :
	        case SGUS_SIG_LANG_EN :
	        	TRAN_EE(me, SGUS_StateHomepage);
	        	break;
	        default :
	        	break;
	    }
}


void SGUS_StatePlugUnconnectInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonHomePage(&tmp);
    SGUS_StateSetTimeoutValue(60);
    SGUS_SetCurrentPage(SGUS_Page_PlugUnconnect);
}

void SGUS_StatePlugUnconnectUpdate(void)
{
    uint8_t ccu1_cc1state;
    uint8_t ccu2_cc1state;

    SGUS_StatePageCheckProcess(SGUS_Page_PlugUnconnect);

    ccu1_cc1state = get_GeECCR_CCU1CCUCC1STATE_enum();
    ccu2_cc1state = get_GeECCR_CCU2CCUCC1STATE_enum();

    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    SGUS_Signal = SGUS_SIG_DEFAULT;
    SGUS_StateTimeoutProcess();
    if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
    else
    {
		if(0 == Data_Global.CurrentPlug)
		{
			if(SGUS_CCU_CC1_STATE_CONNECT == ccu1_cc1state)
			{
				SGUS_Signal = SGUS_SIG_PLUGCONNECT;
			}
		}
		else if(1 == Data_Global.CurrentPlug)
		{
			if(SGUS_CCU_CC1_STATE_CONNECT == ccu2_cc1state)
			{
				SGUS_Signal = SGUS_SIG_PLUGCONNECT;
			}
		}
    }
}

void SGUS_StatePlugUnconnect(parser_t * me, signal_t sig)
{
	switch(sig)
	{
		case SGUS_SIG_ENTRY :
			SGUS_StatePlugUnconnectInit();
			SGUS_SignalUpdate = SGUS_StatePlugUnconnectUpdate;
			me->currentstate = SGUS_STA_PLUGUNCONNECT;
			break;
		case SGUS_SIG_EXIT :
			me->prestate = SGUS_STA_PLUGUNCONNECT;
			break;
		case SGUS_SIG_PLUGCONNECT :
			TRAN_EE(me, SGUS_StatePaymentMethod);
			break;
		case SGUS_SIG_HOMEPAGE :
		case SGUS_SIG_TIMOUT :
			TRAN_EE(me, SGUS_StateHomepage);
			break;
		default :
			break;
	}
}


void SGUS_StateVIPLoginInit(void)
{
    uint8_t i;
    uint8_t tmp;

    for(i = 0; i < 32; i++)
    {
        Data_Login.UserName[i] = '\0';
        Data_Login.PassWord[i] = '\0';
    }
    SGUS_SetLoginUserName(&Data_Login.UserName[0]);
    SGUS_SetLoginPassWord(&Data_Login.PassWord[0]);

    Rte_Write_TouchPanel_LeftVIPChrgCheckSuccess_flg(0);
    Rte_Write_TouchPanel_RightVIPChrgCheckSuccess_flg(0);

    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonConfirm(&tmp);

    SGUS_StateSetTimeoutValue(120);

    SGUS_UserType[Data_Global.CurrentPlug] = UserType_VIP;
    SGUS_SetCurrentPage(SGUS_Page_UserLogin);
}


void SGUS_StateVIPLoginUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_UserLogin);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);

    SGUS_GetLoginUserName(Data_Login.UserName);
    SGUS_GetLoginPassWord(Data_Login.PassWord);

    SGUS_Signal = SGUS_SIG_DEFAULT;
    SGUS_StateTimeoutProcess();
    if(Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
}


void SGUS_State4VIPLoginCheck(parser_t * me)
{
    uint8_t i;
    uint8_t result = FALSE;
    for(i = 0; i < 6; i++)
    {
        if(Data_Login.UserName[i] != SuperUserName[i])
        {
            break;
        }
    }

    if(6 == i && 0xFF ==Data_Login.UserName[i])
    {
        result = TRUE;
    }


    if(TRUE == result)
    {

        for(i = 0; i < 6; i++)
        {
            if(Data_Login.PassWord[i] != SuperPassWord[i])
            {
                break;
            }
        }
        if(6 == i && 0xFF ==Data_Login.PassWord[i])
        {
            result = TRUE;
        }
        else
        {
            result = FALSE;
        }
    }

    if(TRUE == result)
    {
        if(0 == Data_Global.CurrentPlug)
        {
            Rte_Write_TouchPanel_LeftVIPChrgCheckSuccess_flg(1);
        }
        else
        {
            Rte_Write_TouchPanel_RightVIPChrgCheckSuccess_flg(1);
        }
		TRAN_EE(me, SGUS_StateStartCharge);
    }
    else
    {
        TRAN_EE(me, SGUS_StateHomepage);
    }
}




void SGUS_StateVIPLogin(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateVIPLoginInit();
            SGUS_SignalUpdate = SGUS_StateVIPLoginUpdate;
            me->currentstate = SGUS_STA_USERLOGIN;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_USERLOGIN;
            break;
        case SGUS_SIG_BACK :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_CONFIRM :
            SGUS_State4VIPLoginCheck(me);
            break;
        default :
            break;
    }
}

void SGUS_StateVIPLogoutInit(void)
{
    uint8_t i;
    uint8_t tmp;
    for(i = 0; i < 32; i++)
    {

        Data_Logout.PassWord[i] = '\0';
    }
    SGUS_SetLogoutPassWord(&Data_Logout.PassWord[0]);

    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonConfirm(&tmp);

    SGUS_StateSetTimeoutValue(90);

    //Rte_Write_TouchPanel_LeftVIPChrgStopSuccess_flg(0);
    //Rte_Write_TouchPanel_RightVIPChrgStopSuccess_flg(0);

    SGUS_SetCurrentPage(SGUS_Page_UserLogout);
}


void SGUS_StateVIPLogoutUpdate(void)
{

    SGUS_StatePageCheckProcess(SGUS_Page_UserLogout);
    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);

    SGUS_GetLogoutPassWord(Data_Logout.PassWord);

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    if(Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
}


void SGUS_State4VIPLogoutCheck(parser_t * me)
{
    uint8_t result = FALSE;
    uint8_t i;
    uint8_t ccustate;
    for(i = 0; i < 6; i++)
    {
        if(Data_Logout.PassWord[i] != SuperPassWord[i])
        {
            break;
        }
    }
    if(6 == i && 0xFF ==Data_Logout.PassWord[i])
    {
        result = TRUE;
    }

    if(TRUE == result)
    {
        ccustate = (0 == Data_Global.CurrentPlug) ? get_GeECCR_CCU1CCUSTATE_enum() : get_GeECCR_CCU1CCUSTATE_enum();
        if(4 == ccustate)
        {
            TRAN_EE(me, SGUS_StateWorkInfo);
        }
        else if(5 == ccustate || 7 == ccustate)
        {   
            TRAN_EE(me, SGUS_StateStopCharge);
        }
    }
    else
    {
        TRAN_EE(me, SGUS_StateHomepage);
    }
}

void SGUS_StateVIPLogout(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateVIPLogoutInit();
            SGUS_SignalUpdate = SGUS_StateVIPLogoutUpdate;
            me->currentstate = SGUS_STA_USERLOGOUT;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_USERLOGOUT;
            break;
        case SGUS_SIG_BACK :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_CONFIRM :
            SGUS_State4VIPLogoutCheck(me);
            break;
        default :
            break;
    }
}

void SGUS_StatePaymentMethodInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonPaymentMethod(&tmp);
	SGUS_GetButtonBack(&tmp);
	SGUS_GetButtonTest(&tmp);

	Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_NONE);
	Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_NONE);

    if(0 == Data_Global.CurrentPlug)
	{
		Rte_Write_TouchPanel_LeftCCUStartCheck_flg(0);
	}
	else
	{
		Rte_Write_TouchPanel_RightCCUStartCheck_flg(0);
	}

	SGUS_StateSetTimeoutValue(30);

	SGUS_SetCurrentPage(SGUS_Page_PaymentMethod);
}

void SGUS_StatePaymentMethodUpdate(void)
{
	SGUS_StatePageCheckProcess(SGUS_Page_PaymentMethod);

	SGUS_GetButtonPaymentMethod(&Data_PaymentMethod.PaymentMethod);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

	SGUS_Signal =SGUS_SIG_DEFAULT;
    
    SGUS_StateButtonTestProcess();
    SGUS_StateTimeoutProcess();

	if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
	else if(0 != Data_PaymentMethod.PaymentMethod)
	{
		if(SGUS_PAYMENTMETHOD_QR_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_QR_CN == Data_PaymentMethod.PaymentMethod)
		{
			SGUS_Signal = SGUS_SIG_PAYMENTQRCODE;
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_QR);
			}
			else
			{
				Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_QR);
			}
		}
		else if(SGUS_PAYMENTMETHOD_RFID_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_RFID_CN == Data_PaymentMethod.PaymentMethod)
		{
			SGUS_Signal = SGUS_SIG_PAYMENTCARD;
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_RFID);
			}
			else
			{
				Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_RFID);
			}
		}
		else if(SGUS_PAYMENTMETHOD_CC_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_CC_CN == Data_PaymentMethod.PaymentMethod)
		{
			SGUS_Signal = SGUS_SIG_PAYMENTCARD;
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_CC);
			}
			else
			{
				Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_CC);
			}
		}
	}
}

void SGUS_StatePaymentMethod(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StatePaymentMethodInit();
            SGUS_SignalUpdate = SGUS_StatePaymentMethodUpdate;
            me->currentstate = SGUS_STA_PAYMENTMETHOD;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_PAYMENTMETHOD;
            break;
        case SGUS_SIG_HOMEPAGE :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_TEST :
        	TRAN_EE(me, SGUS_StateVIPLogin);
        	break;
        case SGUS_SIG_PAYMENTCARD :
        	TRAN_EE(me, SGUS_StateCardLogin);
        	break;
        case SGUS_SIG_PAYMENTQRCODE :
        	TRAN_EE(me, SGUS_StateQRLogin);
        	break;
        default :
        	break;
    }
}

void SGUS_StateCardLoginInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonBack(&tmp);
	SGUS_GetButtonHomePage(&tmp);
	SGUS_StateSetTimeoutValue(30);

	if(SGUS_PAYMENTMETHOD_RFID_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_RFID_CN == Data_PaymentMethod.PaymentMethod)
	{
		SGUS_UserType[Data_Global.CurrentPlug] = UserType_RFID;
	}
	else if(SGUS_PAYMENTMETHOD_CC_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_CC_CN == Data_PaymentMethod.PaymentMethod)
	{
		SGUS_UserType[Data_Global.CurrentPlug] = UserType_CreditCard;
	}
    
    if(0 == Data_Global.CurrentPlug)
	{
		Rte_Write_TouchPanel_LeftCCUStartCheck_flg(1);
	}
	else
	{
		Rte_Write_TouchPanel_RightCCUStartCheck_flg(1);
	}
    
	SGUS_SetCurrentPage(SGUS_Page_CardLogin);
}

void SGUS_StateCardLoginUpdate(void)
{
	uint8_t cardicon;
	SGUS_StatePageCheckProcess(SGUS_Page_CardLogin);

	SGUS_GetButtonBack(&Data_Global.ButtonBack);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

	SGUS_GetCardTypeIcon(&cardicon);

	if(SGUS_PAYMENTMETHOD_RFID_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_RFID_CN == Data_PaymentMethod.PaymentMethod)
	{
		if(SGUS_CARDICON_RFID != cardicon)
		{
			SGUS_SetCardTypeIcon(SGUS_CARDICON_RFID);
		}
	}
	else if(SGUS_PAYMENTMETHOD_CC_EU == Data_PaymentMethod.PaymentMethod || SGUS_PAYMENTMETHOD_CC_CN == Data_PaymentMethod.PaymentMethod)
	{
		if(SGUS_CARDICON_CREDITCARD != cardicon)
		{
			SGUS_SetCardTypeIcon(SGUS_CARDICON_CREDITCARD);
		}
	}

	SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();

	if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
	else if(TRUE == get_GbEBSW_CarPass_flg())
	{
		SGUS_Signal = SGUS_SIG_CARDAUTH;
	}
}

void SGUS_StateCardLogin(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateCardLoginInit();
            SGUS_SignalUpdate = SGUS_StateCardLoginUpdate;
            me->currentstate = SGUS_STA_CARDLOGIN;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CARDLOGIN;
            break;
        case SGUS_SIG_CARDAUTH :
        	TRAN_EE(me, SGUS_StateStartCardAuth);
        	break;
        case SGUS_SIG_BACK :
        	TRAN_EE(me, SGUS_StatePaymentMethod);
        	break;
        case SGUS_SIG_HOMEPAGE :
        case SGUS_SIG_TIMOUT :
        	TRAN_EE(me, SGUS_StateHomepage);
			break;
        default :
        	break;
    }
}

void SGUS_StateStartCardAuthInit(void)
{
    SGUS_StateSetTimeoutValue(60);

    //SGUS_SetCurrentPage(SGUS_Page_InfoConfirming);
    SGUS_SetCurrentPage(SGUS_Page_StartCharge);
}

void SGUS_StateStartCardAuthUpdate(void)
{
    //SGUS_StatePageCheckProcess(SGUS_Page_InfoConfirming);
	SGUS_SetCurrentPage(SGUS_Page_StartCharge);

    SGUS_Signal = SGUS_SIG_CLOUD_START;

    if(0 == Data_Global.CurrentPlug)
    {
        Rte_Write_TouchPanel_LeftVIPChrgCheckSuccess_flg(1);
    }
    else
    {
        Rte_Write_TouchPanel_RightVIPChrgCheckSuccess_flg(1);
    }
//    SGUS_StateCloudProcess();
    SGUS_StateTimeoutProcess();
}


void SGUS_StateStartCardAuth(parser_t *me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateStartCardAuthInit();
            SGUS_SignalUpdate = SGUS_StateStartCardAuthUpdate;
            me->currentstate = SGUS_STA_CARDAUTH;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CARDAUTH;
            break;
        case SGUS_SIG_CLOUD_START :
			TRAN_EE(me, SGUS_StateStartCharge);
            break;
        case SGUS_SIG_TIMOUT :
        	TRAN_EE(me, SGUS_StateHomepage);
        	break;
        default :
            break;
    }
}

void SGUS_StateCardAuthFailInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonConfirm(&tmp);
    SGUS_GetButtonHomePage(&tmp);
    SGUS_StateSetTimeoutValue(10);
    SGUS_SetCurrentPage(SGUS_Page_InfoConfirmFail);
}

void SGUS_StateCardAuthFailUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_InfoConfirmFail);

    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    
    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
}
void SGUS_StateCardAuthFail(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateCardAuthFailInit();
            SGUS_SignalUpdate = SGUS_StateCardAuthFailUpdate;
            me->currentstate = SGUS_STA_CARDAUTHFAIL;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CARDAUTHFAIL;
            break;
        case SGUS_SIG_CONFIRM :
        	TRAN_EE(me, SGUS_StateCardLogin);
        	break;
        case SGUS_SIG_HOMEPAGE :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        default :
            break;
    }
}

void SGUS_StateQRLoginInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonBack(&tmp);
	SGUS_GetButtonHomePage(&tmp);
	if(0 == Data_Global.CurrentPlug)
	{
		SGUS_SetQRCode(SGUS_TEST_QRCODE_LEFT);
	}
	else
	{
		SGUS_SetQRCode(SGUS_TEST_QRCODE_RIGHT);
	}
	SGUS_StateSetTimeoutValue(60);
	SGUS_SetCurrentPage(SGUS_Page_QRCodeLogin);
}

void SGUS_StateQRLoginUpdate(void)
{
	SGUS_StatePageCheckProcess(SGUS_Page_QRCodeLogin);

	SGUS_GetButtonBack(&Data_Global.ButtonBack);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

	SGUS_Signal = SGUS_SIG_DEFAULT;
    SGUS_StateCloudProcess();
    SGUS_StateTimeoutProcess();
	if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
}

void SGUS_StateQRLogin(parser_t * me, signal_t sig)
{
	 switch(sig)
	{
		case SGUS_SIG_ENTRY :
			SGUS_StateQRLoginInit();
			SGUS_SignalUpdate = SGUS_StateQRLoginUpdate;
			me->currentstate = SGUS_STA_QRLOGIN;
			break;
		case SGUS_SIG_EXIT :
			me->prestate = SGUS_STA_QRLOGIN;
			break;
		case SGUS_SIG_CLOUD_START :
			TRAN_EE(me, SGUS_StateChargeModSel);
			break;
		case SGUS_SIG_BACK :
			TRAN_EE(me, SGUS_StatePaymentMethod);
			break;
		case SGUS_SIG_HOMEPAGE :
		case SGUS_SIG_TIMOUT :
			TRAN_EE(me, SGUS_StateHomepage);
			break;
		default :
			break;
	}

}

void SGUS_StateChargeModSelInit(void)
{
    uint8_t tmp;

    SGUS_GetButtonAutoFull(&tmp);
    SGUS_GetButtonMoney(&tmp);
    SGUS_GetButtonTime(&tmp);
    SGUS_GetButtonEnergy(&tmp);

    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonHomePage(&tmp);

    SGUS_StateSetTimeoutValue(30);

    SGUS_SetCurrentPage(SGUS_Page_ChargeModeSel);
}

void SGUS_StateChargeModSelUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_ChargeModeSel);

    SGUS_GetButtonAutoFull(&Data_ModSel.ButtonAutoFull);
    SGUS_GetButtonMoney(&Data_ModSel.ButtonMoney);
    SGUS_GetButtonTime(&Data_ModSel.ButtonTime);
    SGUS_GetButtonEnergy(&Data_ModSel.ButtonEnergy);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);


    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    if(TRUE == Data_ModSel.ButtonAutoFull)
    {
        SGUS_Signal = SGUS_SIG_MODAUTOFULL;
    }
    else if(TRUE == Data_ModSel.ButtonMoney)
    {
    	if(0 == Data_Global.CurrentPlug)
		{
			Rte_Write_TouchPanel_CCU1ChargeType_enum(3);
		}
		else if(1 == Data_Global.CurrentPlug)
		{
			Rte_Write_TouchPanel_CCU2ChargeType_enum(3);
		}
        SGUS_Signal = SGUS_SIG_MODMONEY;
    }
    else if(TRUE == Data_ModSel.ButtonTime)
    {

        SGUS_Signal = SGUS_SIG_MODTIME;
    }
    else if(TRUE == Data_ModSel.ButtonEnergy)
    {
    	if(0 == Data_Global.CurrentPlug)
		{
			Rte_Write_TouchPanel_CCU1ChargeType_enum(2);
		}
		else if(1 == Data_Global.CurrentPlug)
		{
			Rte_Write_TouchPanel_CCU2ChargeType_enum(2);
		}
        SGUS_Signal = SGUS_SIG_MODENERGY;
    }
    else if(TRUE == Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
}

void SGUS_StateChargeModSel(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateChargeModSelInit();
            SGUS_SignalUpdate = SGUS_StateChargeModSelUpdate;
            me->currentstate = SGUS_STA_CHARGEMODSEL;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CHARGEMODSEL;
            break;
        case SGUS_SIG_TIMOUT :
        case SGUS_SIG_MODAUTOFULL :
        	if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1ChargeType_enum(SGUS_CCU_CHARGE_MODE_AUTOFULL);
			}
			else if(1 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU2ChargeType_enum(SGUS_CCU_CHARGE_MODE_AUTOFULL);
			}
        	TRAN_EE(me, SGUS_StateStartCharge);
            break;
        case SGUS_SIG_MODENERGY :
        	TRAN_EE(me, SGUS_StateChargeEnergy);
            break;
        case SGUS_SIG_MODMONEY :
        	TRAN_EE(me, SGUS_StateChargeMoney);
            break;
        case SGUS_SIG_MODTIME :
        	TRAN_EE(me, SGUS_StateChargeTime);
            break;
        case SGUS_SIG_BACK :
            TRAN_EE(me, SGUS_StatePaymentMethod);
            break;
        case SGUS_SIG_HOMEPAGE :
        	TRAN_EE(me, SGUS_StateHomepage);
			break;
        default :
            break;
    }

}

void SGUS_StateChargeMoneyInit(void)
{
	uint8_t tmp;
	SGUS_SetChargeMoneyValue(0);

	SGUS_GetButtonConfirm(&tmp);
	SGUS_GetButtonHomePage(&tmp);
	SGUS_GetButtonBack(&tmp);

	SGUS_SetCurrentPage(SGUS_Page_ModeMoney);
}

void SGUS_StateChargeMoneyUpdate(void)
{
	uint16_t valuemoeny;

	SGUS_StatePageCheckProcess(SGUS_Page_ModeMoney);

	SGUS_GetChargeMoneyValue(&valuemoeny);

	SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);
	SGUS_GetButtonBack(&Data_Global.ButtonBack);

	SGUS_Signal = SGUS_SIG_DEFAULT;
	if(TRUE == Data_Global.ButtonConfirm)
	{
		if(0 != valuemoeny)
		{
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1PreChargeRate_rmb(valuemoeny);
				Rte_Write_TouchPanel_CCU1ChargeType_enum(SGUS_CCU_CHARGE_MODE_MONEY);
			}
			else if(1 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU2PreChargeRate_rmb(valuemoeny);
				Rte_Write_TouchPanel_CCU2ChargeType_enum(SGUS_CCU_CHARGE_MODE_MONEY);
			}
			SGUS_Signal = SGUS_SIG_CONFIRM;
		}
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
	else if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
}

void SGUS_StateChargeMoney(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateChargeModSelInit();
            SGUS_SignalUpdate = SGUS_StateChargeMoneyUpdate;
            me->currentstate = SGUS_STA_CHARGEMODMOENY;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CHARGEMODMOENY;
            break;
        case SGUS_SIG_CONFIRM :
        	TRAN_EE(me, SGUS_StateStartCharge);
        	break;
        case SGUS_SIG_HOMEPAGE :
        	TRAN_EE(me, SGUS_StateHomepage);
        	break;
        case SGUS_SIG_BACK :
        	TRAN_EE(me, SGUS_StateChargeModSel);
        	break;
        default :
        	break;
    }
}

void SGUS_StateChargeTimeInit(void)
{
	uint8_t tmp;
	SGUS_SetChargeTimeValue(0);

	SGUS_GetButtonConfirm(&tmp);
	SGUS_GetButtonHomePage(&tmp);
	SGUS_GetButtonBack(&tmp);

	SGUS_SetCurrentPage(SGUS_Page_ModeTime);
}

void SGUS_StateChargeTimeUpdate(void)
{
	uint16_t valuetime;

	SGUS_StatePageCheckProcess(SGUS_Page_ModeTime);

	SGUS_GetChargeMoneyValue(&valuetime);

	SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);
	SGUS_GetButtonBack(&Data_Global.ButtonBack);

	SGUS_Signal = SGUS_SIG_DEFAULT;
	if(TRUE == Data_Global.ButtonConfirm)
	{
		if(0 != valuetime)
		{
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1PreChargeTime_S(valuetime*60);
				Rte_Write_TouchPanel_CCU1ChargeType_enum(SGUS_CCU_CHARGE_MODE_TIME);
			}
			else if(1 == Data_Global.CurrentPlug)
			{
				//Rte_Write_TouchPanel_CCU2PreChargeTime_S(valuetime*60);
				Rte_Write_TouchPanel_CCU2ChargeType_enum(SGUS_CCU_CHARGE_MODE_TIME);
			}
			SGUS_Signal = SGUS_SIG_CONFIRM;
		}
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
	else if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
}

void SGUS_StateChargeTime(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateChargeModSelInit();
            SGUS_SignalUpdate = SGUS_StateChargeTimeUpdate;
            me->currentstate = SGUS_STA_CHARGEMODTIME;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CHARGEMODTIME;
            break;
        case SGUS_SIG_CONFIRM :
			TRAN_EE(me, SGUS_StateStartCharge);
			break;
		case SGUS_SIG_HOMEPAGE :
			TRAN_EE(me, SGUS_StateHomepage);
			break;
		case SGUS_SIG_BACK :
			TRAN_EE(me, SGUS_StateChargeModSel);
			break;
        default :
        	break;
    }
}

void SGUS_StateChargeEnergyInit(void)
{
	uint8_t tmp;
	SGUS_SetChargeEnergyValue(0);
	SGUS_GetButtonConfirm(&tmp);
	SGUS_GetButtonHomePage(&tmp);
	SGUS_GetButtonBack(&tmp);

	SGUS_SetCurrentPage(SGUS_Page_ModeEnergy);
}

void SGUS_StateChargeEnergyUpdate(void)
{
	uint16_t valueenergy;

	SGUS_StatePageCheckProcess(SGUS_Page_ModeEnergy);

	SGUS_GetChargeEnergyValue(&valueenergy);
	SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);
	SGUS_GetButtonBack(&Data_Global.ButtonBack);

	SGUS_Signal = SGUS_SIG_DEFAULT;
	if(TRUE == Data_Global.ButtonConfirm)
	{
		if(0 != valueenergy)
		{
			if(0 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU1PreChargeEnergy_kwH(valueenergy);
				Rte_Write_TouchPanel_CCU1ChargeType_enum(SGUS_CCU_CHARGE_MODE_ENERGY);
			}
			else if(1 == Data_Global.CurrentPlug)
			{
				Rte_Write_TouchPanel_CCU2PreChargeEnergy_kwH(valueenergy);
				Rte_Write_TouchPanel_CCU2ChargeType_enum(SGUS_CCU_CHARGE_MODE_ENERGY);
			}
			SGUS_Signal = SGUS_SIG_CONFIRM;
		}
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
	else if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
}

void SGUS_StateChargeEnergy(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateChargeModSelInit();
            SGUS_SignalUpdate = SGUS_StateChargeEnergyUpdate;
            me->currentstate = SGUS_STA_CHARGEMODENERGY;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CHARGEMODENERGY;
            break;
        case SGUS_SIG_CONFIRM :
			TRAN_EE(me, SGUS_StateStartCharge);
			break;
		case SGUS_SIG_HOMEPAGE :
			TRAN_EE(me, SGUS_StateHomepage);
			break;
		case SGUS_SIG_BACK :
			TRAN_EE(me, SGUS_StateChargeModSel);
			break;
        default :
        	break;
    }
}

void SGUS_StateStartChargeInit(void)
{
	SGUS_StateSetTimeoutValue(60);
    SGUS_SetCurrentPage(SGUS_Page_StartCharge);
}

void SGUS_StateStartChargeUpdate(void)
{
    uint8_t ccustate;

    SGUS_StatePageCheckProcess(SGUS_Page_StartCharge);

    ccustate = (0 == Data_Global.CurrentPlug) ? get_GeECCR_CCU1CCUSTATE_enum() : get_GeECCR_CCU2CCUSTATE_enum();


    SGUS_Signal = SGUS_SIG_DEFAULT;
    SGUS_StateTimeoutProcess();
    if(SGUS_CCU_STATE_STANDBY != ccustate)
    {
        SGUS_Signal = SGUS_SIG_DEFAULT;
    	if(SGUS_CCU_STATE_CHARGING == ccustate)
    	{
    		SGUS_Signal = SGUS_SIG_STARTSUCCEED;
    	}
    	else if(SGUS_CCU_STATE_STOPCHARGE == ccustate ||\
    	        SGUS_CCU_STATE_FAULT == ccustate ||\
    	        SGUS_CCU_STATE_POWERDOWN == ccustate)
		{
			SGUS_Signal = SGUS_SIG_STARTERR;
		}
    }
}


void SGUS_StateStartCharge(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateStartChargeInit();
            SGUS_SignalUpdate = SGUS_StateStartChargeUpdate;
            me->currentstate = SGUS_STA_STARTCHARGE;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_STARTCHARGE;
            break;
        case SGUS_SIG_STARTSUCCEED :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_STARTERR :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateStartErr);
            break;
        default :
            break;
    }
}

void SGUS_StateStartErrInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonConfirm(&tmp);
    SGUS_GetButtonHomePage(&tmp);
    SGUS_StateSetTimeoutValue(20);
    SGUS_SetCurrentPage(SGUS_Page_StartChargeErr);
}

void SGUS_StateStartErrUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_StartChargeErr);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
}

void SGUS_StateStartErr(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateStartErrInit();
            SGUS_SignalUpdate = SGUS_StateStartErrUpdate;
            me->currentstate = SGUS_STA_STARTCHARGERR;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_STARTCHARGERR;
            break;
        case SGUS_SIG_CONFIRM :
        case SGUS_SIG_HOMEPAGE :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        default :
            break;
    }
}


void SGUS_StateWorkInfoInit(void)
{
    uint8_t tmp;
    float current;
	float voltage;
	uint32_t energy;
	float power;

	uint32_t moneycost = 0;
	uint16_t timecharged;
	uint16_t lefttime;
	uint8_t  soc;
	uint8_t ccustate = 0;

	uint8_t plugstate;

    SGUS_GetButtonHomePage(&tmp);
    SGUS_GetButtonStopCharge(&tmp);

    if(0 == Data_Global.CurrentPlug)
	{
		ccustate    = get_GeECCR_CCU1CCUSTATE_enum();
		current     = get_GcECCR_CCU1CCSSPN3082IOut_A();
		voltage     = get_GcECCR_CCU1CCSSPN3081UOut_V();
		energy      = (get_GcEBSW_LeftDCWhCurrtEnerge_kwH() - SGUS_Patch_WH_Energy_Start[0]) * 100;
		soc         = get_GcECCR_CCU1BCSSPN3078SOC_Pct();
		timecharged = get_GcECCR_CCU1CCSSPN3083TimeCharged_Min();
		lefttime    = get_GcECCR_CCU1BCSSPN3079TimeRemain_min();
	}
	else
	{
		ccustate = get_GeECCR_CCU2CCUSTATE_enum();
		current = get_GcECCR_CCU2CCSSPN3082IOut_A();
		voltage = get_GcECCR_CCU2CCSSPN3081UOut_V();
		energy = (get_GcEBSW_RightDCWhCurrtEnerge_kwH() - SGUS_Patch_WH_Energy_Start[1]) * 100;
		soc = get_GcECCR_CCU2BCSSPN3078SOC_Pct();
		timecharged = get_GcECCR_CCU2CCSSPN3083TimeCharged_Min();
		lefttime = get_GcECCR_CCU2BCSSPN3079TimeRemain_min();
	}

    if(SGUS_CCU_STATE_CHARGING == ccustate)
	{
		plugstate = SGUS_PlugStateCharging;
	}
	else if(SGUS_CCU_STATE_STOPCHARGE == ccustate || SGUS_CCU_STATE_POWERDOWN == ccustate)
	{
		plugstate = SGUS_PlugStateComplete;
	}
	else if(SGUS_CCU_STATE_FAULT == ccustate)
	{
		plugstate = SGUS_PlugStateFault;
	}

    SGUS_SetPlugState(plugstate);

    if(SGUS_PlugStateCharging == plugstate)
	{
		SGUS_SetChargingGIF(1);
	}
	else
	{
		SGUS_SetChargingGIF(0);
	}
	if(SGUS_PlugStateFault == plugstate)
	{
		SGUS_SetSOCGreen(SGUS_SOC_NONE);
		SGUS_SetSOCRed(soc);
	}
	else
	{
		SGUS_SetSOCRed(SGUS_SOC_NONE);
		SGUS_SetSOCGreen(soc);
	}


	SGUS_SetWorkInfoCurrent(current*10);

	SGUS_SetWorkInfoVoltage(voltage*10);


	energy *= 100;
	SGUS_SetWorkInfoEnergy(energy);

	SGUS_SetWorkInfoChargingTime(timecharged);

	SGUS_SetWorkInfoRemainingTime(lefttime);

	SGUS_SetWorkInfoCost(moneycost);

	power = current * voltage / 1000;

	SGUS_SetWorkInfoPower(power*100);

    SGUS_SetCurrentPage(SGUS_Page_WorkInfo);
}

void SGUS_StateWorkInfoUpdate(void)
{
    static uint8_t plugstate = 0xFF;

    uint16_t current;
    float    current_tmp;
    uint16_t voltage;
    float    voltage_tmp;
    uint32_t energy;
    uint32_t power;

    uint32_t moneycost = 0;
    uint16_t timecharged;
    uint16_t lefttime;
    uint8_t  soc;
    uint8_t ccustate = 0;

    SGUS_StatePageCheckProcess(SGUS_Page_WorkInfo);
    SGUS_GetPlugState(&Data_WorkInfo.PlugState);
    SGUS_GetSOCGreen(&Data_WorkInfo.SOCGreen);
    SGUS_GetSOCRed(&Data_WorkInfo.SOCRed);
    SGUS_GetChargingGIF(&Data_WorkInfo.ChargingGIF);

    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);
    SGUS_GetButtonStopCharge(&Data_WorkInfo.ButtonStopCharge);
    
    if(0 == Data_Global.CurrentPlug)
    {
        ccustate    = get_GeECCR_CCU1CCUSTATE_enum();
        #if 0
        current     = get_GcECCR_CCU1CCSSPN3082IOut_A();
        #else
        current_tmp     = get_GcECCR_CCU1CCSSPN3082IOut_A();
        #endif
        voltage_tmp     = get_GcECCR_CCU1CCSSPN3081UOut_V();
        energy      = (get_GcEBSW_LeftDCWhCurrtEnerge_kwH() - SGUS_Patch_WH_Energy_Start[0]) * 100;
        soc         = get_GcECCR_CCU1BCSSPN3078SOC_Pct();
        timecharged = get_GcECCR_CCU1CCSSPN3083TimeCharged_Min();
        lefttime    = get_GcECCR_CCU1BCSSPN3079TimeRemain_min();
    }
    else
    {
        ccustate = get_GeECCR_CCU2CCUSTATE_enum();
        #if 0
        current = get_GcECCR_CCU2CCSSPN3082IOut_A();
        #else
        current_tmp  = get_GcECCR_CCU1CCSSPN3082IOut_A();
        #endif
        voltage_tmp = get_GcECCR_CCU2CCSSPN3081UOut_V();
        energy = (get_GcEBSW_RightDCWhCurrtEnerge_kwH() - SGUS_Patch_WH_Energy_Start[1]) * 100;
        soc = get_GcECCR_CCU2BCSSPN3078SOC_Pct();
        timecharged = get_GcECCR_CCU2CCSSPN3083TimeCharged_Min();
        lefttime = get_GcECCR_CCU2BCSSPN3079TimeRemain_min();
    }
    if(SGUS_CCU_STATE_CHARGING == ccustate)
    {
        plugstate = SGUS_PlugStateCharging;
    }
    else if(SGUS_CCU_STATE_STOPCHARGE == ccustate || SGUS_CCU_STATE_POWERDOWN == ccustate)
    {
        plugstate = SGUS_PlugStateComplete;
    }
    else if(SGUS_CCU_STATE_FAULT == ccustate)
    {
        plugstate = SGUS_PlugStateFault;
    }


    
    if(plugstate != Data_WorkInfo.PlugState)
    {
        SGUS_SetPlugState(plugstate);
    }

    if(SGUS_PlugStateCharging == Data_WorkInfo.PlugState)
    {
        
        if(0 == Data_WorkInfo.ChargingGIF)
        {
        	SGUS_GetChargingGIF(1);
        }
    }
    else
    {
        if(1 == Data_WorkInfo.ChargingGIF)
        {
        	SGUS_GetChargingGIF(0);
        }
    }
    if(SGUS_PlugStateFault == Data_WorkInfo.PlugState)
    {
        if(200 != Data_WorkInfo.SOCGreen)
        {
            SGUS_SetSOCGreen(SGUS_SOC_NONE);
        }
        if(soc != Data_WorkInfo.SOCRed)
        {
            SGUS_SetSOCRed(soc);
        }
    }
    else
    {
        if(200 != Data_WorkInfo.SOCRed)
        {
            SGUS_SetSOCRed(SGUS_SOC_NONE);
        }
        if(soc != Data_WorkInfo.SOCGreen)
        {
            SGUS_SetSOCGreen(soc);
        }

    }

    #if 0
    if(current >4000)
    {
        current -= 4000;
    }
    else if(current > 0)
    {
        current = 4000 - current;
    }
    #else
    current = (uint16_t)((current_tmp+0.05) * 10);
    #endif
    SGUS_GetWorkInfoCurrent(&Data_WorkInfo.Current);
    if(current != Data_WorkInfo.Current) //Update Current Info
    {
        SGUS_SetWorkInfoCurrent(current);
    }

    voltage = (uint16_t)((voltage_tmp+0.05) * 10);
    SGUS_GetWorkInfoVoltage(&Data_WorkInfo.Voltage);
    if(voltage != Data_WorkInfo.Voltage) //Update Voltage Info
    {
        SGUS_SetWorkInfoVoltage(voltage);
    }

    
    energy *= 100;
    SGUS_GetWorkInfoEnergy(&Data_WorkInfo.Energy);
    if(energy != Data_WorkInfo.Energy)
    {
        SGUS_SetWorkInfoEnergy(energy);
    }
    
    SGUS_GetWorkInfoChargingTime(&Data_WorkInfo.ChargingTime);
    if(timecharged != Data_WorkInfo.ChargingTime)
    {
        SGUS_SetWorkInfoChargingTime(timecharged);
    }    
    
    SGUS_GetWorkInfoRemainingTime(&Data_WorkInfo.RemaingTime);
    if(lefttime != Data_WorkInfo.RemaingTime)
    {
        SGUS_SetWorkInfoRemainingTime(lefttime);
    }    

    SGUS_GetWorkInfoCost(&Data_WorkInfo.Cost);
    if(moneycost != Data_WorkInfo.Cost)
    {
        SGUS_SetWorkInfoCost(moneycost);
    }
    power = current * voltage;
    SGUS_GetWorkInfoPower(&Data_WorkInfo.Power);
    if(power != Data_WorkInfo.Power)
    {
    	SGUS_SetWorkInfoPower(power);
    }

    SGUS_Signal = SGUS_SIG_DEFAULT;
    
    if(TRUE == Data_Global.ButtonHomepage)
    {
        SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
    else if(TRUE == Data_WorkInfo.ButtonStopCharge)
    {
        if(UserType_RFID == SGUS_UserType[Data_Global.CurrentPlug] || UserType_CreditCard == SGUS_UserType[Data_Global.CurrentPlug])
        {
            if(0 == Data_Global.CurrentPlug)
            {
                Rte_Write_TouchPanel_LeftVIPChrgStopSuccess_flg(1);
            }
            else
            {
                Rte_Write_TouchPanel_RightVIPChrgStopSuccess_flg(1);
            }
        }
        else if(UserType_VIP == SGUS_UserType[Data_Global.CurrentPlug])
        {
            if(0 == Data_Global.CurrentPlug)
            {
                Rte_Write_TouchPanel_LeftVIPChrgStopSuccess_flg(1);
            }
            else
            {
                Rte_Write_TouchPanel_RightVIPChrgStopSuccess_flg(1);
            }
        }
        SGUS_Signal = SGUS_SIG_STOPCHARGE;
    }
}

void SGUS_StateWorkInfo(parser_t *me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateWorkInfoInit();
            SGUS_SignalUpdate = SGUS_StateWorkInfoUpdate;
            me->currentstate = SGUS_STA_WORKINFO;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_WORKINFO;
            break;
        case SGUS_SIG_HOMEPAGE :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_STOPCHARGE :
            TRAN_EE(me, SGUS_StateStopCharge);

            break;
        default :
            break;
    }
}

void SGUS_StateCardLogoutInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonBack(&tmp);
	SGUS_StateSetTimeoutValue(60);
    
	if(0 == Data_Global.CurrentPlug)
	{
		
        if(UserType_RFID == SGUS_UserType[0])
        {
            Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_RFID);
        }
        else if(UserType_CreditCard == SGUS_UserType[0])
        {
            Rte_Write_TouchPanel_CCU1CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_CC);
        }
        Rte_Write_TouchPanel_LeftCCUStopCheck_flg(1);
	}
	else
	{
		
        if(UserType_RFID == SGUS_UserType[1])
        {
            Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_RFID);
        }
        else if(UserType_CreditCard == SGUS_UserType[1])
        {
            Rte_Write_TouchPanel_CCU2CCVChargeType_enum(SGUS_CCV_CHARGE_TYPE_CC);
        }
        Rte_Write_TouchPanel_RightCCUStopCheck_flg(1);
	}

	SGUS_SetCurrentPage(SGUS_Page_CardLogout);
}

void SGUS_StateCardLogoutUpdate(void)
{
	SGUS_StatePageCheckProcess(SGUS_Page_CardLogout);

	SGUS_GetButtonBack(&Data_Global.ButtonBack);

	SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
	if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
	else if(TRUE == get_GbEBSW_CarPass_flg())
	{
		SGUS_Signal = SGUS_SIG_CARDAUTH;
	}
}

void SGUS_StateCardLogout(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateCardLogoutInit();
            SGUS_SignalUpdate = SGUS_StateCardLogoutUpdate;
            me->currentstate = SGUS_STA_CARDLOGOUT;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CARDLOGOUT;
            break;
        case SGUS_SIG_CARDAUTH :
        	TRAN_EE(me, SGUS_StateStopCardAuth);
        	break;
        case SGUS_SIG_BACK :
        case SGUS_SIG_TIMOUT :
        	TRAN_EE(me, SGUS_StateHomepage);
        	break;
        default :
        	break;
    }
}

void SGUS_StateStopCardAuthInit(void)
{
    SGUS_StateSetTimeoutValue(60);

    SGUS_SetCurrentPage(SGUS_Page_InfoConfirming);
}

void SGUS_StateStopCardAuthUpdate(void)
{
    uint8_t i;
    
    SGUS_StatePageCheckProcess(SGUS_Page_InfoConfirming);
    
	SGUS_Signal = SGUS_SIG_DEFAULT;
    SGUS_StateTimeoutProcess();
	if(UserType_CreditCard == SGUS_UserType[Data_Global.CurrentPlug])
	{
		SGUS_Signal = SGUS_SIG_CC_OK;
	}
    else if(UserType_RFID == SGUS_UserType[Data_Global.CurrentPlug])
    {
        SGUS_Signal = SGUS_SIG_AUTH_OK;
    }
}


    

void SGUS_StateStopCardAuth(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateStopCardAuthInit();
            SGUS_SignalUpdate = SGUS_StateStopCardAuthUpdate;
            me->currentstate = SGUS_STA_CARDAUTH;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_CARDAUTH;
            break;
        case SGUS_SIG_CC_OK :
        case SGUS_SIG_AUTH_OK :
            TRAN_EE(me, SGUS_StateStopCharge);
            break;
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        default :
            break;
    }
}


void SGUS_StateStopChargeInit(void)
{
	SGUS_StateSetTimeoutValue(120);
   //SGUS_SetCurrentPage(Page_StopCharge);
}

void SGUS_StateStopChargeUpdate(void)
{
    uint8_t ccustate;
    uint8_t elecFinish_flg;

    ccustate = (0 == Data_Global.CurrentPlug) ? get_GeECCR_CCU1CCUSTATE_enum() : get_GeECCR_CCU2CCUSTATE_enum();
    elecFinish_flg = (0 == Data_Global.CurrentPlug) ? get_GbECEC_CCU1ElectricityCalFinish_flg() : get_GbECEC_CCU2ElectricityCalFinish_flg();

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    if(UserType_VIP == SGUS_UserType[Data_Global.CurrentPlug])
    {
        elecFinish_flg = TRUE;
    }
    
    if(SGUS_CCU_STATE_CHARGING != ccustate && TRUE == elecFinish_flg)
    {
    	SGUS_Signal = SGUS_SIG_STOPSUCCEED;
    }
}
void SGUS_StateStopCharge(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateStopChargeInit();
            SGUS_SignalUpdate = SGUS_StateStopChargeUpdate;
            me->currentstate = SGUS_STA_STOPCHARGE;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_STOPCHARGE;
            break;
        case SGUS_SIG_STOPSUCCEED :
            TRAN_EE(me, SGUS_StateStopInfo);
            break;
        case SGUS_SIG_TIMOUT :
        	TRAN_EE(me, SGUS_StateHomepage);
        	break;
        default :
            break;
    }
}

void SGUS_StateStopInfoInit(void)
{
    uint32_t tmp;
    uint8_t buf[32];
    uint8_t i;
    SGUS_GetButtonConfirm((uint8_t*)&(tmp));
    SGUS_GetButtonHomePage((uint8_t*)&(tmp));

    if(0 == Data_Global.CurrentPlug)
    {
        tmp = get_GcECCR_CCU1BCPSPN2821SOC_Pct();
    }
    else
    {
        tmp = get_GcECCR_CCU2BCPSPN2821SOC_Pct();
    }
    SGUS_SetStopInfoStartSOC(tmp/10);
    
    if(0 == Data_Global.CurrentPlug)
    {
        tmp = get_GcECCR_CCU1BCSSPN3078SOC_Pct();
    }
    else
    {
        tmp = get_GcECCR_CCU2BCSSPN3078SOC_Pct();
    }
    SGUS_SetStopInfoStopSOC(tmp);
    if(0 == Data_Global.CurrentPlug)
    {
        tmp = get_GcECCR_CCU1CCSSPN3083TimeCharged_Min();
    }
    else
    {
        tmp = get_GcECCR_CCU2CCSSPN3083TimeCharged_Min();
    }
    SGUS_SetStopInfoChargedTime(tmp);
    for(i = 0; i < 8; i++)
    {
        buf[i] = i + '0';
    }
    buf[i] = '\0';
    SGUS_SetStopInfoTransactionNum(buf);
    for(i = 0; i < 8; i++)
    {
        buf[2*i] = (SGUS_CardNumBackup[Data_Global.CurrentPlug][i]>>4) + '0';
        buf[2*i+1] = (SGUS_CardNumBackup[Data_Global.CurrentPlug][i] & 0xF) + '0';
    }
    SGUS_SetStopInfoCardInfo(buf);

    SGUS_StateSetTimeoutValue(60);

    SGUS_SetCurrentPage(SGUS_Page_StopInfoCard);
}
void SGUS_StateStopInfoUpdate(void)
{

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StatePageCheckProcess(SGUS_Page_StopInfoCard);
    
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
        SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
    else
    {
    	SGUS_StateTimeoutProcess();
    }

}
void SGUS_StateStopInfo(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateStopInfoInit();
            SGUS_SignalUpdate = SGUS_StateStopInfoUpdate;
            me->currentstate = SGUS_STA_STOPINFO;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_STOPINFO;
            break;
        case SGUS_SIG_HOMEPAGE :
        case SGUS_SIG_CONFIRM :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        default :
            break;
    }
}


void SGUS_StateSysManagerLoginInit(void)
{
    uint8_t i;
    uint8_t tmp;
    for(i = 0; i < 32; i++)
    {

        Data_SysConfigLogin.PassWord[i] = '\0';
    }
    SGUS_SetSysConfigPassWord(&Data_SysConfigLogin.PassWord[0]);

    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonConfirm(&tmp);

    SGUS_StateSetTimeoutValue(90);

    SGUS_SetCurrentPage(SGUS_Page_SysConfigPassWord);
}

void SGUS_StateSysManagerLoginUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_SysConfigPassWord);
    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);


    SGUS_GetSysConfigPassWord(Data_SysConfigLogin.PassWord);

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    
    if(Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }    
}


const uint8_t SysconfigPassword[] = "123456";
void SGUS_StateSysManagerLoginCheck(parser_t * me)
{
    uint8_t result = FALSE;
    uint8_t i;
    for(i = 0; i < 6; i++)
    {
        if(Data_SysConfigLogin.PassWord[i] != SysconfigPassword[i])
        {
            break;
        }
    }
    if(6 == i)
    {
        result = TRUE;
    }

    if(TRUE == result)
    {
        TRAN_EE(me, SGUS_StateSystermManager);
    }
    else
    {
        TRAN_EE(me, SGUS_StateHomepage);
    }
}

void SGUS_StateSysManagerLogin(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateSysManagerLoginInit();
            SGUS_SignalUpdate = SGUS_StateSysManagerLoginUpdate;
            me->currentstate = SGUS_STA_SYSMANAGERLOGIN;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_SYSMANAGERLOGIN;
            break;
        case SGUS_SIG_BACK :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_CONFIRM :
            SGUS_StateSysManagerLoginCheck(me);
            break;
        default :
            break;
    }
}


void SGUS_StateSystermManagerInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonHomePage(&tmp);

    SGUS_GetButtonPageSysConfig(&tmp);
    SGUS_GetButtonPageInfoInquiry(&tmp);

    SGUS_GetButtonPageChargeRecord(&tmp);
    SGUS_GetButtonPageFaultRecord(&tmp);
    SGUS_GetButtonPageInputControl(&tmp);
    SGUS_GetButtonPagePowerOffSelect(&tmp);

    SGUS_SetCurrentPage(SGUS_Page_SysManager);
}

void SGUS_StateSystermManagerUpdate(void)
{
    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StatePageCheckProcess(SGUS_Page_SysManager);

    SGUS_GetButtonPagePowerOffSelect(&Data_SysConfig.ButtonPagePowerOffSelect);
    SGUS_GetButtonPageInputControl(&Data_SysConfig.ButtonPageInputControl);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    if(TRUE == Data_SysConfig.ButtonPagePowerOffSelect)
    {
        SGUS_Signal = SGUS_SIG_POWEROFFSELECT_PAGE;
    }
    else if(TRUE == Data_SysConfig.ButtonPageInputControl)
    {
        SGUS_Signal = SGUS_SIG_INPUTCONTROL_PAGE;
    }
    else if(TRUE == Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
        
}
void SGUS_StateSystermManager(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateSystermManagerInit();
            SGUS_SignalUpdate = SGUS_StateSystermManagerUpdate;
            me->currentstate = SGUS_STA_SYSMANAGER;
            break;
        case SGUS_SIG_EXIT :
            me->prestate = SGUS_STA_SYSMANAGER;
            break;
        case SGUS_SIG_BACK :
        case SGUS_SIG_HOMEPAGE :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        case SGUS_SIG_POWEROFFSELECT_PAGE :
            TRAN_EE(me, SGUS_StatePowerOffSelect);
            break;
        case SGUS_SIG_INPUTCONTROL_PAGE :
            TRAN_EE(me, SGUS_StateStationInputControl);
            break;
        default :
            break;
    }
}

void SGUS_StatePowerOffSelectInit(void)
{
	uint8_t tmp;
	SGUS_GetButtonPageSafePowerOff(&tmp);
	SGUS_GetButtonPageUserPowerOff(&tmp);

	SGUS_GetButtonBack(&tmp);
	SGUS_GetButtonHomePage(&tmp);

	SGUS_SetCurrentPage(SGUS_Page_PowerOffSelect);
}

void SGUS_StatePowerOffSelectUpdate(void)
{
	SGUS_StatePageCheckProcess(SGUS_Page_PowerOffSelect);

	SGUS_GetButtonPageSafePowerOff(&Data_PowerOffSelect.ButtonPageSafePowerOff);
	SGUS_GetButtonPageUserPowerOff(&Data_PowerOffSelect.ButtonPageUserPowerOff);

	SGUS_GetButtonBack(&Data_Global.ButtonBack);
	SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    if(TRUE == Data_PowerOffSelect.ButtonPageSafePowerOff)
	{
		Rte_Write_TouchPanel_SafetyPowerdownCmd_flg(1);
	}
	else if(TRUE == Data_PowerOffSelect.ButtonPageUserPowerOff)
	{
		Rte_Write_TouchPanel_UserChargingeStop_flg(1);
	}
	SGUS_Signal = SGUS_SIG_DEFAULT;

	if(TRUE == Data_Global.ButtonBack)
	{
		SGUS_Signal = SGUS_SIG_BACK;
	}
	else if(TRUE == Data_Global.ButtonHomepage)
	{
		SGUS_Signal = SGUS_SIG_HOMEPAGE;
	}
}

void SGUS_StatePowerOffSelect(parser_t * me, signal_t sig)
{
	switch(sig)
	{
		case SGUS_SIG_ENTRY :
			SGUS_StatePowerOffSelectInit();
			SGUS_SignalUpdate = SGUS_StatePowerOffSelectUpdate;
			me->currentstate = SGUS_STA_POWEROFFSELECT;
			break;
		case SGUS_SIG_EXIT :
			me->prestate = SGUS_STA_POWEROFFSELECT;
			break;
        /*
		case SGUS_SIG_SAFEPOWEROFF_PAGE :
			TRAN_EE(me, SGUS_StateSafePowerOff);
			break;
		case SGUS_SIG_USERPOWEROFF_PAGE :
			TRAN_EE(me, SGUS_StateUserPowerOff);
			break;
			*/
		case SGUS_SIG_BACK :
			TRAN_EE(me, SGUS_StateSystermManager);
			break;
		case SGUS_SIG_HOMEPAGE :
			TRAN_EE(me, SGUS_StateHomepage);
			break;
		default :
			break;
	}
}






uint8_t tmp_get_HighVoltageState_flg(void)
{
    uint8_t rtn = 0;
    if(1)
    {
        rtn = 1;
    }

    return rtn;
}

void SGUS_StateSafePowerOffInit(void)
{
    uint8_t tmp;
    tmp = tmp_get_HighVoltageState_flg();
    SGUS_SetHighVoltageState(tmp);
    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonHomePage(&tmp);
    SGUS_GetButtonSafePowerOff(&tmp);
    SGUS_SetCurrentPage(SGUS_Page_SafePowerOff);
}

void SGUS_StateSafePowerOffUpdate(void)
{
    uint8_t hightvoltagestate;
    SGUS_Signal = SGUS_SIG_DEFAULT;
    
    SGUS_StatePageCheckProcess(SGUS_Page_SafePowerOff);

    hightvoltagestate = tmp_get_HighVoltageState_flg();
    SGUS_GetHighVoltageState(&Data_SafePowerOff.StateHighVoltage);
    SGUS_GetButtonSafePowerOff(&Data_SafePowerOff.ButtonSafePowerOff);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

    if(hightvoltagestate != Data_SafePowerOff.StateHighVoltage)
    {
        SGUS_SetHighVoltageState(hightvoltagestate);
    }

    if(1 == hightvoltagestate)
    {
        if(TRUE == Data_SafePowerOff.ButtonSafePowerOff)
        {
            Rte_Write_TouchPanel_SafetyPowerdownCmd_flg(1);
        }
    }
    else
    {
        Rte_Write_TouchPanel_SafetyPowerdownCmd_flg(0);
    }


    if(TRUE == Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
    
}

void SGUS_StateSafePowerOff(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateSafePowerOffInit();
            SGUS_SignalUpdate = SGUS_StateSafePowerOffUpdate;
            me->currentstate = SGUS_STA_SAFEPOWEROFF;
            break;
        case SGUS_SIG_EXIT :
            Rte_Write_TouchPanel_SafetyPowerdownCmd_flg(0);
            me->prestate = SGUS_STA_SAFEPOWEROFF;
            break;
        case SGUS_SIG_BACK :
        	TRAN_EE(me,SGUS_StatePowerOffSelect);
        	break;
        case SGUS_SIG_HOMEPAGE :
            TRAN_EE(me,SGUS_StateHomepage);
            break;
        default :
            break;
    }
}

void SGUS_StateUserPowerOffInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonPageUserPowerOff(&tmp);
    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonHomePage(&tmp);
    SGUS_SetCurrentPage(SGUS_Page_UserPowerOff);
}

void SGUS_StateUserPowerOffUpdate(void)
{
    uint8_t hightvoltagestate;


    SGUS_StatePageCheckProcess(SGUS_Page_UserPowerOff);

    SGUS_GetButtonSafePowerOff(&Data_UserPowerOff.ButtonUserPowerOff);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);

	if(TRUE == Data_UserPowerOff.ButtonUserPowerOff)
	{
		Rte_Write_TouchPanel_UserChargingeStop_flg(1);
	}


    SGUS_Signal = SGUS_SIG_DEFAULT;
    if(TRUE == Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }

}

void SGUS_StateUserPowerOff(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
        	SGUS_StateUserPowerOffInit();
            SGUS_SignalUpdate = SGUS_StateUserPowerOffUpdate;
            me->currentstate = SGUS_STA_USERPOWEROFF;
            break;
        case SGUS_SIG_EXIT :
        	Rte_Write_TouchPanel_UserChargingeStop_flg(0);
            me->prestate = SGUS_STA_USERPOWEROFF;
            break;
        case SGUS_SIG_BACK :
			TRAN_EE(me,SGUS_StatePowerOffSelect);
			break;
        case SGUS_SIG_HOMEPAGE :
            TRAN_EE(me,SGUS_StateHomepage);
            break;
        default :
            break;
    }
}


void SGUS_StateStationInputControlInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonBack(&tmp);
    SGUS_GetButtonConfirm(&tmp);
    SGUS_GetButtonHomePage(&tmp);
    Rte_Read_TouchPanel_StationInputCtl_enum(&tmp);
    SGUS_SetStationInput(tmp);
    SGUS_SetCurrentPage(SGUS_Page_InputControl);
}

void SGUS_StateStationInputControlUpdate(void)
{
    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StatePageCheckProcess(SGUS_Page_InputControl);

    SGUS_GetStationInput(&Data_InputControl.InputControlEnum);

    SGUS_GetButtonBack(&Data_Global.ButtonBack);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);
    SGUS_GetButtonHomePage(&Data_Global.ButtonHomepage);
    
    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
    else if(TRUE == Data_Global.ButtonBack)
    {
        SGUS_Signal = SGUS_SIG_BACK;
    }
    else if(TRUE == Data_Global.ButtonHomepage)
    {
    	SGUS_Signal = SGUS_SIG_HOMEPAGE;
    }
}

SGUS_StationInputCtl_eeprom inputcontroldata;
void SGUS_StateStationInputControl(parser_t * me, signal_t sig)
{
    SGUS_StationInputCtl_eeprom tmpinputcontrol;
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateStationInputControlInit();
            SGUS_SignalUpdate = SGUS_StateStationInputControlUpdate;
            me->currentstate = SGUS_STA_INPUTCONTROL;
            break;
        case SGUS_SIG_EXIT :

            me->prestate = SGUS_STA_INPUTCONTROL;
            break;
        case SGUS_SIG_CONFIRM :
        	memcpy(&inputcontroldata.flgname[0],"Inputflg",8);
        	inputcontroldata.value = Data_InputControl.InputControlEnum;
            SGUS_IO_Store_InputControl((uint8_t*)&inputcontroldata);
            SGUS_IO_Read_InputControl((uint8_t*)&tmpinputcontrol);
            if(0 == memcmp((void*)&inputcontroldata, (void*)&tmpinputcontrol, sizeof(SGUS_StationInputCtl_eeprom)))
            {
                Rte_Write_TouchPanel_StationInputCtl_enum(inputcontroldata.value);
                TRAN_EE(me,SGUS_StateSysConfigSuccess);
            }
            else
            {
                TRAN_EE(me,SGUS_StateSysConfigFailue);
            }
            break;
        case SGUS_SIG_BACK :
        	TRAN_EE(me, SGUS_StateSystermManager);
        	break;
        case SGUS_SIG_HOMEPAGE :
            TRAN_EE(me, SGUS_StateHomepage);
            break;
        default :
            break;
    }
}

void SGUS_StateSysConfigSuccessInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonConfirm(&tmp);
    SGUS_StateSetTimeoutValue(15);
    SGUS_SetCurrentPage(SGUS_Page_SysConfigSuccess);
}

void SGUS_StateSysConfigSuccessUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_SysConfigSuccess);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);

    SGUS_StateTimeoutProcess();
    SGUS_Signal = SGUS_SIG_DEFAULT;
    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
}

void SGUS_StateSysConfigSuccess(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateSysConfigSuccessInit();
            SGUS_SignalUpdate = SGUS_StateSysConfigSuccessUpdate;
            me->currentstate = SGUS_STA_SYSCONFIGSUCCESS;
            break;
        case SGUS_SIG_EXIT :

            me->prestate = SGUS_STA_SYSCONFIGSUCCESS;
            break;
        case SGUS_SIG_CONFIRM :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateSystermManager);
            break;
        default :
            break;
    }
}


void SGUS_StateSysConfigFailueInit(void)
{
    uint8_t tmp;
    SGUS_GetButtonConfirm(&tmp);
    SGUS_StateSetTimeoutValue(15);
    SGUS_SetCurrentPage(SGUS_Page_SysConfigFailue);
}

void SGUS_StateSysConfigFailueUpdate(void)
{
    SGUS_StatePageCheckProcess(SGUS_Page_SysConfigFailue);
    SGUS_GetButtonConfirm(&Data_Global.ButtonConfirm);

    SGUS_Signal = SGUS_SIG_DEFAULT;

    SGUS_StateTimeoutProcess();
    if(TRUE == Data_Global.ButtonConfirm)
    {
        SGUS_Signal = SGUS_SIG_CONFIRM;
    }
}

void SGUS_StateSysConfigFailue(parser_t * me, signal_t sig)
{
    switch(sig)
    {
        case SGUS_SIG_ENTRY :
            SGUS_StateSysConfigFailueInit();
            SGUS_SignalUpdate = SGUS_StateSysConfigFailueUpdate;
            me->currentstate = SGUS_STA_SYSCONFIGFAILUE;
            break;
        case SGUS_SIG_EXIT :

            me->prestate = SGUS_STA_SYSCONFIGFAILUE;
            break;
        case SGUS_SIG_CONFIRM :
        case SGUS_SIG_TIMOUT :
            TRAN_EE(me, SGUS_StateSystermManager);
            break;
        default :
            break;
    }
}

void SGUS_StateSetTimeoutValue(uint8_t value_s)
{
    Data_Global.TimoutCount = value_s*1000/SGUS_STATE_TASK_PEROID;
    SGUS_SetTimOut(value_s);
}
void SGUS_StateTimeoutProcess(void)
{
    if(0 != Data_Global.TimoutCount)
    {
        if(0 == Data_Global.TimoutCount%2)
        {
            SGUS_SetTimOut(Data_Global.TimoutCount/2);
        }
        Data_Global.TimoutCount--;
    }
    else
    {
        SGUS_Signal = SGUS_SIG_TIMOUT;
    }
}

void SGUS_StateButtonTestProcess(void)
{
    static uint8_t ButtonTCnt = 0;
    static uint8_t ButtonTTimoutCnt = 0;
    
    SGUS_GetButtonTest(&Data_Global.ButtonTest);

    //Test Button Need Press 6 times to trigger
    //Time between eath press must less than 1500ms
    if(TRUE == Data_Global.ButtonTest)
    {
        ButtonTCnt++;
        ButtonTTimoutCnt = 0;
    }
    else
    {
        ButtonTTimoutCnt++;
    }

    if(ButtonTTimoutCnt > 3)
    {
        ButtonTTimoutCnt = 0;
        ButtonTCnt = 0;
    }

    if(ButtonTCnt > 5)
    {
        ButtonTCnt = 0;
        SGUS_Signal = SGUS_SIG_TEST;
    }
}


void SGUS_StatePageCheckProcess(sgus_pageindex_t page)
{
    sgus_pageindex_t pagecur;
    SGUS_GetCurrentPage(&pagecur);
    if(pagecur != page)
    {
        SGUS_SetCurrentPage(page);
    }
}

static volatile uint8_t CloudDebugFlg = FALSE;
static volatile uint8_t AuthResultDebug_PlugA = 0;
static volatile uint8_t AuthResultDebug_PlugB = 0;

void SGUS_StateCloudProcess(void)
{
    uint8_t i;

	uint8_t startChargeCmd_plugA;
	uint8_t startChargeCmd_plugB;
	uint8_t stopChargeCmd_plugA;
	uint8_t stopChargeCmd_plugB;

	static uint8_t startChargeCmdPre_plugA = 0;
	static uint8_t startChargeCmdPre_plugB = 0;
	static uint8_t stopChargeCmdPre_plugA = 0;
	static uint8_t stopChargeCmdPre_plugB = 0;

	uint8_t ccuState_plugA;
	uint8_t ccuState_plugB;


	ccuState_plugA = get_GeECCR_CCU1CCUSTATE_enum();
	ccuState_plugB = get_GeECCR_CCU2CCUSTATE_enum();

	startChargeCmd_plugA = get_GbETCR_LeftServeStaChgCmd_flg();
	startChargeCmd_plugB = get_GbETCR_RightServeStaChgCmd_flg();

	stopChargeCmd_plugA = get_GbETCR_LeftServeStpChgCmd_flg();
	stopChargeCmd_plugB = get_GbETCR_RightServeStpChgCmd_flg();



	if(1 == startChargeCmd_plugA && 0 == startChargeCmdPre_plugA)
	{
		if(1 == ccuState_plugA)
		{
            SGUS_Signal = SGUS_SIG_CLOUD_START;
			Data_Global.CurrentPlug = 0;
			SGUS_SetCurrentPlug(0);
		}
	}
	else if(1 == stopChargeCmd_plugA && 0 == stopChargeCmdPre_plugA)
	{
		if(4 == ccuState_plugA)
		{
			SGUS_Signal = SGUS_SIG_CLOUD_STOP;
			Data_Global.CurrentPlug = 0;
			SGUS_SetCurrentPlug(0);
		}
	}

	if(1 == startChargeCmd_plugB && 0 == startChargeCmdPre_plugB)
	{
		if(1 == ccuState_plugB)
		{
            SGUS_Signal = SGUS_SIG_CLOUD_START;
			Data_Global.CurrentPlug= 1;
			SGUS_SetCurrentPlug(1);
		}
	}
	else if(1 == stopChargeCmd_plugB && 0 == stopChargeCmdPre_plugB)
	{
		if(4 == ccuState_plugB)
		{
			SGUS_Signal = SGUS_SIG_CLOUD_STOP;
			Data_Global.CurrentPlug = 1;
			SGUS_SetCurrentPlug(1);
		}
	}

	
	startChargeCmdPre_plugA = startChargeCmd_plugA;
	startChargeCmdPre_plugB = startChargeCmd_plugB;
	stopChargeCmdPre_plugA = stopChargeCmd_plugA;
	stopChargeCmdPre_plugB = stopChargeCmd_plugB;
}

void SGUS_State_Task(void)
{
    SGUS_SignalUpdate();
    FsmDispatch(&SGUS_Parser, SGUS_Signal);
}










