
#ifndef SGUS_TYPE_H_
#define SGUS_TYPE_H_

#include "typedefs.h"


#ifndef TRUE
#define TRUE                           1
#endif

#ifndef FALSE
#define FALSE                          0
#endif

#define SGUS_START_OF_FRAME            0x5AA5

#define SGUS_CMD_WRITE_REG             0x80
#define SGUS_CMD_READ_REG              0x81
#define SGUS_CMD_WRITE_VAR             0x82
#define SGUS_CMD_READ_VAR              0x83
#define SGUS_CMD_WRITE_CURVE           0x84

#define SGUS_BUFFER_SIZE               256



#define SGUS_REG_READABLE              1
#define SGUS_REG_WRITEABLE             2

#define SGUS_VAR_EVENT                 0    //Event varialbe, read or write has no meaning , only valid when witget trigered, auto inform user;
#define SGUS_VAR_STATE                 1    //State variable, controlled and changed by user, or changed by touch, read by user;

#define SGUS_PAGE_OFFSET               200
#define SGUS_VAR_OFFSET                0X2000

#define SGUS_LANG_CN                   0
#define SGUS_LANG_EN                   1

typedef enum
{
    SGUS_E_OK = 0,
    SGUS_E_LEN_ERR,
    SGUS_E_REG_RO,
    SGUS_E_REG_WO,
    SGUS_E_TIMEOUT,
    SGUS_E_CRC_ERR,
    SGUS_E_OTHER_ERR
}sgus_error_t;

typedef enum
{
	SGUS_Reg_Version = 0,
	SGUS_Reg_LedLm,
	SGUS_Reg_BzTime,
	SGUS_Reg_PicIndex,
	SGUS_Reg_TPFlag,
	SGUS_Reg_TPStatus,
	SGUS_Reg_TPPosition,
	SGUS_Reg_TPCEnable,
	SGUS_Reg_RunTime,
	SGUS_Reg_TFConfig,
	SGUS_Reg_TFConfig_R0,
	SGUS_Reg_TFConfig_R1,
	SGUS_Reg_TFConfig_R2,
	SGUS_Reg_TFConfig_R3,
	SGUS_Reg_TFConfig_R5,
	SGUS_Reg_TFConfig_R6,
	SGUS_Reg_TFConfig_R7,
	SGUS_Reg_TFConfig_R8,
	SGUS_Reg_TFConfig_R9,
	SGUS_Reg_TFConfig_RA,
	SGUS_Reg_TFConfig_RC,
	SGUS_Reg_TFConfigEnable,
	SGUS_Reg_LedLmNow,
	SGUS_Reg_RtcComAdj,
	SGUS_Reg_RtcNow,
	SGUS_Reg_FontEnLibOP,
	SGUS_Reg_FontLibOPMode,
	SGUS_Reg_FontLibID,
	SGUS_Reg_FontLiaAddress,
	SGUS_Reg_FontVP,
	SGUS_Reg_FontOPLength,
	SGUS_Reg_Timer0,
	SGUS_Reg_Timer1,
	SGUS_Reg_Timer2,
	SGUS_Reg_Timer3,
	SGUS_Reg_KeyCode,
	SGUS_Reg_PlayMusic,
	SGUS_Reg_VolumeAdj,
	SGUS_Reg_VarEnDBLOP,
	SGUS_Reg_VarOPMode,
	SGUS_Reg_VarDBLAddress,
	SGUS_Reg_VarVP,
	SGUS_Reg_VarOPLength,
	SGUS_Reg_TPCalTrigger,
	SGUS_Reg_TrendlineClear,
	NumofRegIndex,
	SGUS_Reg_Null
}sgus_regindex_t;

typedef enum
{
    SGUS_Var_SerialNum,
    SGUS_Var_NetworkState,
    SGUS_Var_CurrentPlug,
    SGUS_Var_TimeCountDown,
    SGUS_Var_ButtonBack,
    SGUS_Var_ButtonConfirm,
    SGUS_Var_ButtonSysInfo,
    SGUS_Var_ButtonHomePage,
    SGUS_Var_ButtonStopCharge,
    SGUS_Var_ButtonTest,

    //Page SysHomepage
    SGUS_Var_ButtonStop_PlugA,
    SGUS_Var_ButtonStop_PlugB,
    SGUS_Var_ButtonBase_PlugA,
    SGUS_Var_ButtonBase_PlugB,
    SGUS_Var_ButtonLangSelect,
    SGUS_Var_MarkedWords_PlugA,
	SGUS_Var_MarkedWords_PlugB,
    SGUS_Var_DynState_PlugA,
    SGUS_Var_StaticState_PlugA,
    SGUS_Var_DynState_PlugB,
    SGUS_Var_StaticState_PlugB,
    SGUS_Var_RemainingTime_PlugA,
    SGUS_Var_RemainingTime_PlugB,
    SGUS_Var_WorkInfoSOCGreen_PlugA,
    SGUS_Var_WorkInfoSOCGreen_PlugB,
    SGUS_Var_WorkInfoSOCRed_PlugA,
    SGUS_Var_WorkInfoSOCRed_PlugB,
	SGUS_Var_ChargePrice,
    
    //Page User Login
    SGUS_Var_LoginUserName,
    SGUS_Var_LoginPassWord,

	//Page Payment Method
	SGUS_Var_Payment_Method,

	//Page QRCode
	SGUS_Var_QRCode,

    //Page Charge Mode Select
    SGUS_Var_ChargeModAutoFull,
    SGUS_Var_ChargeModMoney,
    SGUS_Var_ChargeModTime,
    SGUS_Var_ChargeModEnergy,

    //Page Charge Modd Money
    SGUS_Var_ChargeMoneyValue,
    //Page Charge Mode Time
    SGUS_Var_ChargeTimeValue,
    //Page Charge Mode Cap
    SGUS_Var_ChargeEnergyValue,

    //Page_CardInfoCheckFailue
    SGUS_Var_InfoConfirmFailCode,

    //Page_CardInfoCheckSuccess
    SGUS_Var_RFIDCardNum,
    SGUS_Var_RFIDCardBalance,
    SGUS_Var_RFIDCardPoint,

    //Page_ChargeStartFailue
    SGUS_Var_ChargeStartFailueCode,

	//Page_RFID/CC_Notice
	SGUS_Var_CardIcon,


    
    //Page SysInfo
    SGUS_Var_WorkInfoCurrent,
    SGUS_Var_WorkInfoVoltage,
    SGUS_Var_WorkInfoEnergy,
    SGUS_Var_WorkInfoChargingTime,
    SGUS_Var_WorkInfoCost,
    SGUS_Var_WorkInfoRemainingTime,
    SGUS_Var_WorkInfoPlugDynState,
    SGUS_Var_WorkInfoPlugStaticState,
    SGUS_Var_WorkInfoChargingGIF,
    SGUS_Var_WorkInfoSOCGreen,
    SGUS_Var_WorkInfoSOCRed,
	SGUS_Var_WorkInfoPower,

    

    //Page Stop Charge
    SGUS_Var_LogoutPassWord,

	//PageCardStopChargeInfo
	SGUS_Var_StopInfoEnergy,
	SGUS_Var_StopInfoCost,
	SGUS_Var_StopInfoChargedTime,
	SGUS_Var_StopInfoStopTime,
	SGUS_Var_StopInfoTransactionNum,
	SGUS_Var_StopInfoStopReason,
	SGUS_Var_StopInfoStartSOC,
	SGUS_Var_StopInfoStopSOC,
	SGUS_Var_InfoChargeProcess,
	SGUS_Var_StopInfoCardInfo,
	SGUS_Var_StopInfoCardBalance,

    //Page Systerm Config Login
    SGUS_Var_SysLoginPassWord,

    //Page Systerm Manage
	SGUS_Var_ButtonPageSysConfig,
	SGUS_Var_ButtonPageInfoInquiry,
	SGUS_Var_ButtonPageChargeRecord,
	SGUS_Var_ButtonPageFaultRecord,
	SGUS_Var_ButtonPagerInputControl,
	SGUS_Var_ButtonPagePowerOffSelect,

	//Page Systerm Config
	SGUS_Var_ButtonPageElectricityMeterConfig,
	SGUS_Var_ButtonPageAuxPowerConfig,
	SGUS_Var_ButtonPagePowerModuleConfig,
	SGUS_Var_ButtonPagePileTest,
	SGUS_Var_ButtonPageServerAddrConfig,
	SGUS_Var_ButtonPageQRCodeConfig,
	SGUS_Var_ButtonPageAreaSet,
	SGUS_Var_ButtonPagePasswordRest,

    //Page Sage Powerdown
    SGUS_Var_StateHighVoltage,
    SGUS_Var_ButtonSafePowerOff,

    //Page Charger Input Control
    SGUS_Var_InputControl,

    //Page Area Set

    //Page PasswordReset

	//Page AuxPowerSet
	SGUS_VAR_ButtonAUX12V,
	SGUS_VAR_ButtonAUX24V,

	//Page UserPowerOff Page
	SGUS_Var_ButtonUserPowerOff,
	SGUS_Var_IconUserPowerOff,

	//Page PowerOff Select
	SGUS_Var_ButtonPageSafePowerOff,
	SGUS_Var_ButtonPageUserPowerOff,

	//Page Language Select
	SGUS_Var_ButtonLanguageEnum,
    
    NumofVarIndex,
    SGUS_Var_Null
}sgus_varindex_t;


typedef enum
{
    SGUS_Page_Startup,
    SGUS_Page_Homepage,

    SGUS_Page_UserLogin,
	SGUS_Page_PaymentMethod,
    SGUS_Page_ChargeModeSel,
    SGUS_Page_ModeMoney,
    SGUS_Page_ModeTime,
    SGUS_Page_ModeEnergy,
	SGUS_Page_InfoConfirming,
	SGUS_Page_InfoConfirmFail,
	SGUS_Page_InfoConfirmSucceed,
	SGUS_Page_StartCharge,
	SGUS_Page_StartChargeErr,
	SGUS_Page_PlugUnconnect,
	SGUS_Page_PlugUnmatched,
	SGUS_Page_CardLogin,
	SGUS_Page_QRCodeLogin,

    SGUS_Page_WorkInfo,

    SGUS_Page_CardLogout,

    SGUS_Page_UserLogout,

    SGUS_Page_StopInfoCard,
	SGUS_Page_StopInfoQRCode,

    SGUS_Page_SysConfigPassWord,
	SGUS_Page_SysManager,
	SGUS_Page_SysConfig,
	SGUS_Page_SafePowerOff,
	SGUS_Page_InputControl,
	SGUS_Page_AreaSet,
	SGUS_Page_PasswordReset,
	SGUS_Page_SysConfigSuccess,
	SGUS_Page_SysConfigFailue,
	SGUS_Page_AuxPowerConfig,
	SGUS_Page_UserPowerOff,
	SGUS_Page_PowerOffSelect,

	SGUS_Page_LangSelect,

    NumofPageIndex,
    SGUS_Page_Null
}sgus_pageindex_t;



#pragma pack (1)
typedef struct
{
    uint8_t version;
	uint8_t ledlm;
	uint8_t bztime;
	uint8_t picindex[2];
	uint8_t tpflag;
	uint8_t tpstatus;
	uint8_t tpposition[4];
	uint8_t tpcenable;
	uint8_t runtime[4];
    uint8_t tfconfig[13];
    uint8_t tfconfig_r0;
    uint8_t tfconfig_r1;
    uint8_t tfconfig_r2;
    uint8_t tfconfig_r3;
    uint8_t tfconfig_r5;
    uint8_t tfconfig_r6;
    uint8_t tfconfig_r7;
    uint8_t tfconfig_r8;
    uint8_t tfconfig_r9;
    uint8_t tfconfig_ra;
    uint8_t tfconfig_rc;
    uint8_t tfconfigenable;
    uint8_t ledlmnow;
    uint8_t rtccomadj[8];
    uint8_t rtcnow[7];
    uint8_t fontenlibop;
    uint8_t fontlibopmode;
    uint8_t fontlibid;
    uint8_t fontliaaddress[3];
    uint8_t fontvp[2];
    uint8_t fontoplength[2];
    uint8_t timer0[2];
    uint8_t timer1;
    uint8_t timer2;
    uint8_t timer3;
    uint8_t keycode;
    uint8_t playmusic[3];
    uint8_t volumeadj[2];
    uint8_t varendblop;
    uint8_t varopmode;
    uint8_t vardbladdress[4];
    uint8_t varvp[2];
    uint8_t varoplength[2];
    uint8_t tpcaltrigger;
    uint8_t trendlineclear;
}
sgus_regdata_t;

typedef struct
{
    uint8_t serialnum[32];
    uint8_t networkstate[2];
    uint8_t currentplug[2];
    uint8_t timecountdown[2];
    uint8_t buttonback[2];
    uint8_t buttonconfirm[2];
    uint8_t buttonsysinfo[2];
    uint8_t buttonhomepage[2];
    uint8_t buttonstopcharge[2];
    uint8_t buttontest[2];
    
    uint8_t buttonstop_pluga[2];
    uint8_t buttonstop_plugb[2];
    uint8_t buttonbase_pluga[2];
    uint8_t buttonbase_plugb[2];
    uint8_t buttonlangsel[2];
    uint8_t markedword_pluga[2];
    uint8_t markedword_plugb[2];
    uint8_t dynstate_pluga[4];
    uint8_t staticstate_pluga[2];
    uint8_t dynstate_plugb[4];
    uint8_t staticstate_plugb[2];
    uint8_t remainingtime_pluga[2];
    uint8_t remainingtime_plugb[2];
    uint8_t socgreen_pluga[4];
    uint8_t socgreen_plugb[4];
    uint8_t socred_pluga[4];
    uint8_t socred_plugb[4];
    uint8_t chargeprice[4];

    uint8_t loginusername[32];
    uint8_t loginpassword[32];

    uint8_t payment_method[2];

    uint8_t qrcode[480];

    uint8_t buttonmodautofull[2];
    uint8_t buttonmodmoney[2];
    uint8_t buttonmodtime[2];
    uint8_t buttonmodenergy[2];


    uint8_t valuemodmoney[2];
    uint8_t valuemodtime[2];
    uint8_t valuemodenergy[2];

    uint8_t infoconfirmfailcode[32];

    uint8_t rfidcardnum[32];
    uint8_t rfidcardbalance[4];
    uint8_t rfidcardpoint[4];

    uint8_t chargestartfailcode[32];
    
    uint8_t cardicon[2];


    
    uint8_t workinfocurrent[4];
    uint8_t workinfovoltate[4];
    uint8_t workinfoenergy[4];
    uint8_t workinfochargingtime[4];
    uint8_t workinfocost[4];
    uint8_t workinforemainingtime[4];
    uint8_t workinfoplugdynstate[4];
    uint8_t workinfoplugstaticstate[2];
    uint8_t workinfocharginggif[4];
    uint8_t workinfosocgreen[4];
    uint8_t workinfosocred[4];
    uint8_t workinfopower[4];

    uint8_t logoutpassword[32];

    uint8_t stopinfoenergy[4];
    uint8_t stopinfocost[4];
    uint8_t stopinfochargedtime[4];
    uint8_t stopinfochargeendtime[4];
    uint8_t stopInfotransactionnum[32];
    uint8_t stopinfostopreason[32];
    uint8_t stopinfostartsoc[4];
    uint8_t stopinfostopsoc[4];
    uint8_t endinfochargeprocess[4];
    uint8_t stopinfocardinfo[32];
    uint8_t stopinfobalance[4];



    uint8_t sysconfigpassword[32];

    uint8_t buttonpagesysconfig[2];
    uint8_t buttonpageinfoinquiry[2];
    uint8_t buttonpagechargerecord[2];
    uint8_t buttonpagefaultrecord[2];
    uint8_t buttonpageinputcontrol[2];
    uint8_t buttonpagepoweroffsel[2];

    uint8_t buttonpageelectricitymeterconfig[2];
    uint8_t buttonpageauxpowerconfig[2];
    uint8_t buttonpagepowermoduleconfig[2];
    uint8_t buttonpagepiletest[2];
    uint8_t buttonpageserveraddrconfig[2];
    uint8_t buttonpageqrcodeconfig[2];
    uint8_t buttonpageareaset[2];
    uint8_t buttonpagepasswordreset[2];

    uint8_t statehighvoltate[2];
    uint8_t buttonsafepoweroff[2];

    uint8_t inputcontrol[2];

    uint8_t buttonaux12v[2];
    uint8_t buttonaux24v[2];

    uint8_t buttonuserpoweroff[2];
    uint8_t iconuserpoweroff[2];

    uint8_t buttonpagesafepoweroff[2];
    uint8_t buttonpageuserpoweroff[2];

    uint8_t buttonlang_enum[2];
}sgus_vardata_t;
#pragma pack ()




typedef struct
{
	sgus_regindex_t regindex;
	uint8_t regaddr;
	uint8_t regsize;
	uint8_t regtype;
    uint8_t *regtxdata;
    uint8_t *regrxdata;
}sgus_reginfo_t;

typedef struct
{
    sgus_varindex_t varindex;
    uint16_t varaddr;
    uint8_t varsize;
    uint8_t vartype;
    uint8_t *vartxdata;
    uint8_t *varrxdata;
}sgus_varinfo_t;

typedef struct
{
    sgus_pageindex_t pageindex;
    uint16_t pageaddr;
    sgus_varindex_t  varstartindex;
    sgus_varindex_t  varstopindex;
}sgus_pageinfo_t;
#endif


