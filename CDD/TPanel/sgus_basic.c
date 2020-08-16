

#include "sgus_def.h"
#include "eSCI.h"


/****************************************************************
*Data_Type      SOF     LENGTH     CMD      DATA_FLOW     CRC16 *
*Data_Length     2        1         1           N           2   *
*Comment                                                        *
****************************************************************/

volatile uint8_t SGUS_EnableCRCFlag = TRUE;
volatile uint8_t SGUS_LangEnum = SGUS_LANG_CN;


static uint8_t SGUS_SendBuffer[SGUS_BUFFER_SIZE];           //SendBuffer
static uint8_t SGUS_RecvBuffer[SGUS_BUFFER_SIZE];           //ReceiveBuffer

static sgus_regdata_t SGUS_TxRegData;
static sgus_regdata_t SGUS_RxRegData;

static sgus_vardata_t SGUS_TxVarData;
static sgus_vardata_t SGUS_RxVarData;



//sgus_reginfo_t
static const sgus_reginfo_t SGUS_REG[] =
{
//   Reg_Index                  Reg_Addr     Reg_Size    RegReadWriteType
    {SGUS_Reg_Version,            0x00,         1,       SGUS_REG_READABLE,                        &SGUS_TxRegData.version,            &SGUS_RxRegData.version,},
    {SGUS_Reg_LedLm,              0x01,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.ledlm,              &SGUS_RxRegData.ledlm,},
    {SGUS_Reg_BzTime,             0x02,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.bztime,             &SGUS_RxRegData.bztime,},
    {SGUS_Reg_PicIndex,           0x03,         2,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.picindex[0],        &SGUS_RxRegData.picindex[0],},
    {SGUS_Reg_TPFlag,             0x05,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tpflag,             &SGUS_RxRegData.tpflag,},
    {SGUS_Reg_TPStatus,           0x06,         1,       SGUS_REG_READABLE,                        &SGUS_TxRegData.tpstatus,           &SGUS_RxRegData.tpstatus,},
    {SGUS_Reg_TPPosition,         0x07,         4,       SGUS_REG_READABLE,                        &SGUS_TxRegData.tpposition[0],      &SGUS_RxRegData.tpposition[0],},
    {SGUS_Reg_TPCEnable,          0x0B,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tpcenable,          &SGUS_RxRegData.tpcenable,},
    {SGUS_Reg_RunTime,            0x0C,         4,       SGUS_REG_READABLE,                        &SGUS_TxRegData.runtime[0],         &SGUS_RxRegData.runtime[0],},
    {SGUS_Reg_TFConfig,           0x10,         13,      SGUS_REG_READABLE,                        &SGUS_TxRegData.tfconfig[0],        &SGUS_RxRegData.tfconfig[0],},
    {SGUS_Reg_TFConfig_R0,        0x10,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r0,        &SGUS_RxRegData.tfconfig_r0,},
    {SGUS_Reg_TFConfig_R1,        0x11,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r1,        &SGUS_RxRegData.tfconfig_r1,},
    {SGUS_Reg_TFConfig_R2,        0x12,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r2,        &SGUS_RxRegData.tfconfig_r2,},
    {SGUS_Reg_TFConfig_R3,        0x13,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r3,        &SGUS_RxRegData.tfconfig_r3,},
    {SGUS_Reg_TFConfig_R5,        0x15,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r5,        &SGUS_RxRegData.tfconfig_r5,},
    {SGUS_Reg_TFConfig_R6,        0x16,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r6,        &SGUS_RxRegData.tfconfig_r6,},
    {SGUS_Reg_TFConfig_R7,        0x17,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r7,        &SGUS_RxRegData.tfconfig_r7,},
    {SGUS_Reg_TFConfig_R8,        0x18,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r8,        &SGUS_RxRegData.tfconfig_r8,},
    {SGUS_Reg_TFConfig_R9,        0x19,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_r9,        &SGUS_RxRegData.tfconfig_r9,},
    {SGUS_Reg_TFConfig_RA,        0x1A,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_ra,        &SGUS_RxRegData.tfconfig_ra,},
    {SGUS_Reg_TFConfig_RC,        0x1C,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.tfconfig_rc,        &SGUS_RxRegData.tfconfig_rc,},
    {SGUS_Reg_TFConfigEnable,     0x1D,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.tfconfigenable,     &SGUS_RxRegData.tfconfigenable,},
    {SGUS_Reg_LedLmNow,           0x1E,         1,       SGUS_REG_READABLE,                        &SGUS_TxRegData.ledlmnow,           &SGUS_RxRegData.ledlmnow,},
    {SGUS_Reg_RtcComAdj,          0x1F,         8,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.rtccomadj[0],       &SGUS_RxRegData.rtccomadj[0],},
    {SGUS_Reg_RtcNow,             0x20,         7,       SGUS_REG_READABLE,                        &SGUS_TxRegData.rtcnow[0],          &SGUS_RxRegData.rtcnow[0],},
    {SGUS_Reg_FontEnLibOP,        0x40,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.fontenlibop,        &SGUS_RxRegData.fontenlibop,},
    {SGUS_Reg_FontLibOPMode,      0x41,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.fontlibopmode,      &SGUS_RxRegData.fontlibopmode,},
    {SGUS_Reg_FontLibID,          0x42,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.fontlibid,          &SGUS_RxRegData.fontlibid,},
    {SGUS_Reg_FontLiaAddress,     0x43,         3,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.fontliaaddress[0],  &SGUS_RxRegData.fontliaaddress[0],},
    {SGUS_Reg_FontVP,             0x46,         2,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.fontvp[0],          &SGUS_RxRegData.fontvp[0],},
    {SGUS_Reg_FontOPLength,       0x48,         2,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.fontoplength[0],    &SGUS_RxRegData.fontoplength[0],},
    {SGUS_Reg_Timer0,             0x4A,         2,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.timer0[0],          &SGUS_RxRegData.timer0[0],},
    {SGUS_Reg_Timer1,             0x4C,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.timer1,             &SGUS_RxRegData.timer1,},
    {SGUS_Reg_Timer2,             0x4D,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.timer2,             &SGUS_RxRegData.timer2,},
    {SGUS_Reg_Timer3,             0x4E,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.timer3,             &SGUS_RxRegData.timer3,},
    {SGUS_Reg_KeyCode,            0x4F,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.keycode,            &SGUS_RxRegData.keycode,},
    {SGUS_Reg_PlayMusic,          0x50,         3,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.playmusic[0],       &SGUS_RxRegData.playmusic[0],},
    {SGUS_Reg_VolumeAdj,          0x53,         2,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.volumeadj[0],       &SGUS_RxRegData.volumeadj[0],},
    {SGUS_Reg_VarEnDBLOP,         0x56,         1,       SGUS_REG_READABLE | SGUS_REG_WRITEABLE,   &SGUS_TxRegData.varendblop,         &SGUS_RxRegData.varendblop,},
    {SGUS_Reg_VarOPMode,          0x57,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.varopmode,          &SGUS_RxRegData.varopmode,},
    {SGUS_Reg_VarDBLAddress,      0x58,         4,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.vardbladdress[0],   &SGUS_RxRegData.vardbladdress[0],},
    {SGUS_Reg_VarVP,              0x5C,         2,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.varvp[0],           &SGUS_RxRegData.varvp[0],},
    {SGUS_Reg_VarOPLength,        0x5E,         2,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.varoplength[0],     &SGUS_RxRegData.varoplength[0],},
    {SGUS_Reg_TPCalTrigger,       0xEA,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.tpcaltrigger,       &SGUS_RxRegData.tpcaltrigger,},
    {SGUS_Reg_TrendlineClear,     0xEB,         1,       SGUS_REG_WRITEABLE,                       &SGUS_TxRegData.trendlineclear,  &SGUS_RxRegData.trendlineclear,},
};



static const sgus_varinfo_t SGUS_VAR[] =
{
//   Var_Index               Var_Addr    Var_Size   Var_Type
    {SGUS_Var_SerialNum,          0x0110,       32,      SGUS_VAR_STATE, &SGUS_TxVarData.serialnum[0],        &SGUS_RxVarData.serialnum[0],},
    {SGUS_Var_NetworkState,           0x0120,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.networkstate[0],         &SGUS_RxVarData.networkstate[0],},
    {SGUS_Var_CurrentPlug,     0x0121,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.currentplug[0],   &SGUS_RxVarData.currentplug[0],},
    {SGUS_Var_TimeCountDown,      0x0122,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.timecountdown[0],    &SGUS_RxVarData.timecountdown[0],},
    {SGUS_Var_ButtonBack,         0x0130,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonback[0],       &SGUS_RxVarData.buttonback[0]},
    {SGUS_Var_ButtonConfirm,        0x0131,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonconfirm[0],      &SGUS_RxVarData.buttonconfirm[0],},
    {SGUS_Var_ButtonSysInfo,      0x0132,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonsysinfo[0],    &SGUS_RxVarData.buttonsysinfo[0],},
    {SGUS_Var_ButtonHomePage,     0x0133,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonhomepage[0],   &SGUS_RxVarData.buttonhomepage[0],},
    {SGUS_Var_ButtonStopCharge,   0x0134,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonstopcharge[0], &SGUS_RxVarData.buttonstopcharge[0],},
    {SGUS_Var_ButtonTest,         0x0135,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttontest[0],       &SGUS_RxVarData.buttontest[0],},
        
    {SGUS_Var_ButtonStop_PlugA,  0x0200,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonstop_pluga[0],    &SGUS_RxVarData.buttonstop_pluga[0],},
    {SGUS_Var_ButtonStop_PlugB,  0x0201,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonstop_plugb[0],    &SGUS_RxVarData.buttonstop_plugb[0],},
    {SGUS_Var_ButtonBase_PlugA,     0x0202,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonbase_pluga[0],       &SGUS_RxVarData.buttonbase_pluga[0],},
    {SGUS_Var_ButtonBase_PlugB,     0x0203,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonbase_plugb[0],       &SGUS_RxVarData.buttonbase_plugb[0],},
    {SGUS_Var_ButtonLangSelect,      0x0204,       2,        SGUS_VAR_EVENT, &SGUS_TxVarData.buttonlangsel[0],       &SGUS_RxVarData.buttonlangsel[0],},
	{SGUS_Var_MarkedWords_PlugA,      0x0205,       2,        SGUS_VAR_EVENT, &SGUS_TxVarData.markedword_pluga[0],       &SGUS_RxVarData.markedword_pluga[0],},
	{SGUS_Var_MarkedWords_PlugB,      0x0206,       2,        SGUS_VAR_EVENT, &SGUS_TxVarData.markedword_plugb[0],       &SGUS_RxVarData.markedword_plugb[0],},

	{SGUS_Var_DynState_PlugA,  0x0207,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.dynstate_pluga[0],       &SGUS_RxVarData.dynstate_pluga[0],},
    {SGUS_Var_StaticState_PlugA,  0x0209,       2,        SGUS_VAR_STATE, &SGUS_TxVarData.staticstate_pluga[0],       &SGUS_RxVarData.staticstate_pluga[0],},
    {SGUS_Var_DynState_PlugB,  0x020A,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.dynstate_plugb[0],       &SGUS_RxVarData.dynstate_plugb[0],},
    {SGUS_Var_StaticState_PlugB,  0x020C,       2,        SGUS_VAR_STATE, &SGUS_TxVarData.staticstate_plugb[0],       &SGUS_RxVarData.staticstate_plugb[0],},
    {SGUS_Var_RemainingTime_PlugA,   0x020D,       2,        SGUS_VAR_STATE, &SGUS_TxVarData.remainingtime_pluga[0],       &SGUS_RxVarData.remainingtime_pluga[0],},
    {SGUS_Var_RemainingTime_PlugB,   0x020E,       2,        SGUS_VAR_STATE, &SGUS_TxVarData.remainingtime_plugb[0],       &SGUS_RxVarData.remainingtime_plugb[0],},
    {SGUS_Var_WorkInfoSOCGreen_PlugA,     0x020F,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.socgreen_pluga[0],       &SGUS_RxVarData.socgreen_pluga[0],},
    {SGUS_Var_WorkInfoSOCGreen_PlugB,     0x0211,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.socgreen_plugb[0],       &SGUS_RxVarData.socgreen_plugb[0],},
    {SGUS_Var_WorkInfoSOCRed_PlugA,     0x0213,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.socred_pluga[0],       &SGUS_RxVarData.socred_pluga[0],},
    {SGUS_Var_WorkInfoSOCRed_PlugB,     0x0215,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.socred_plugb[0],       &SGUS_RxVarData.socred_plugb[0],},
	{SGUS_Var_ChargePrice,              0x0217,       4,        SGUS_VAR_STATE, &SGUS_TxVarData.chargeprice[0],        &SGUS_RxVarData.chargeprice[0],},

    {SGUS_Var_LoginUserName,        0x0250,       32,      SGUS_VAR_STATE, &SGUS_TxVarData.loginusername[0],    &SGUS_RxVarData.loginusername[0],},
    {SGUS_Var_LoginPassWord,        0x0260,       32,      SGUS_VAR_STATE, &SGUS_TxVarData.loginpassword[0],    &SGUS_RxVarData.loginpassword[0],},

	{SGUS_Var_Payment_Method,        0x0300,       2,      SGUS_VAR_EVENT, &SGUS_TxVarData.payment_method[0],    &SGUS_RxVarData.payment_method[0],},

	{SGUS_Var_QRCode,       0x0320,               480,      SGUS_VAR_STATE, &SGUS_TxVarData.qrcode[0],    &SGUS_RxVarData.qrcode[0],},

    {SGUS_Var_ChargeModAutoFull,  0x0500,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonmodautofull[0], &SGUS_RxVarData.buttonmodautofull[0],},
    {SGUS_Var_ChargeModMoney,     0x0501,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonmodmoney[0], &SGUS_RxVarData.buttonmodmoney[0],},
    {SGUS_Var_ChargeModTime,      0x0502,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonmodtime[0], &SGUS_RxVarData.buttonmodtime[0],},
    {SGUS_Var_ChargeModEnergy,     0x0503,       2,       SGUS_VAR_EVENT, &SGUS_TxVarData.buttonmodenergy[0], &SGUS_RxVarData.buttonmodenergy[0],},

    {SGUS_Var_ChargeMoneyValue,   0x0600,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.valuemodmoney[0], &SGUS_RxVarData.valuemodmoney[0],},
    {SGUS_Var_ChargeTimeValue,    0x0610,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.valuemodtime[0], &SGUS_RxVarData.valuemodtime[0],},
    {SGUS_Var_ChargeEnergyValue,   0x0620,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.valuemodenergy[0], &SGUS_RxVarData.valuemodenergy[0],},


    {SGUS_Var_InfoConfirmFailCode, 0x0700,  32,      SGUS_VAR_STATE, &SGUS_TxVarData.infoconfirmfailcode[0], &SGUS_RxVarData.infoconfirmfailcode[0],},


    {SGUS_Var_RFIDCardNum,        0x0720,       32,      SGUS_VAR_STATE, &SGUS_TxVarData.rfidcardnum[0],      &SGUS_RxVarData.rfidcardnum[0],},
    {SGUS_Var_RFIDCardBalance,        0x0730,       4,      SGUS_VAR_STATE, &SGUS_TxVarData.rfidcardbalance[0],      &SGUS_RxVarData.rfidcardbalance[0],},
    {SGUS_Var_RFIDCardPoint,        0x0732,       4,      SGUS_VAR_STATE, &SGUS_TxVarData.rfidcardpoint[0],      &SGUS_RxVarData.rfidcardpoint[0],},

    {SGUS_Var_ChargeStartFailueCode, 0x0750,      32,     SGUS_VAR_STATE, &SGUS_TxVarData.chargestartfailcode[0],      &SGUS_RxVarData.chargestartfailcode[0],},

	{SGUS_Var_CardIcon,     0x0770,               2,      SGUS_VAR_STATE, &SGUS_TxVarData.cardicon[0],    &SGUS_RxVarData.cardicon[0],},



    //Page Sys Info Charge
    {SGUS_Var_WorkInfoCurrent,        0X0800,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfocurrent[0],      &SGUS_RxVarData.workinfocurrent[0],},
    {SGUS_Var_WorkInfoVoltage,        0X0802,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfovoltate[0],      &SGUS_RxVarData.workinfovoltate[0],},
    {SGUS_Var_WorkInfoEnergy,        0X0804,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfoenergy[0],      &SGUS_RxVarData.workinfoenergy[0],},
    {SGUS_Var_WorkInfoChargingTime,     0X0806,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfochargingtime[0],    &SGUS_RxVarData.workinfochargingtime[0],},
    {SGUS_Var_WorkInfoCost,    0X0808,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfocost[0],  &SGUS_RxVarData.workinfocost[0],},
    {SGUS_Var_WorkInfoRemainingTime,     0X080A,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinforemainingtime[0],    &SGUS_RxVarData.workinforemainingtime[0],},
    {SGUS_Var_WorkInfoPlugDynState,     0X080C,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfoplugdynstate[0],    &SGUS_RxVarData.workinfoplugdynstate[0],},
    {SGUS_Var_WorkInfoPlugStaticState,     0X080E,       2,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfoplugstaticstate[0],    &SGUS_RxVarData.workinfoplugstaticstate[0],},
    {SGUS_Var_WorkInfoChargingGIF,               0X080F,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfocharginggif[0],    &SGUS_RxVarData.workinfocharginggif[0],},
    {SGUS_Var_WorkInfoSOCGreen,            0X0811,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfosocgreen[0],    &SGUS_RxVarData.workinfosocgreen[0],},
    {SGUS_Var_WorkInfoSOCRed,            0X0813,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfosocred[0],    &SGUS_RxVarData.workinfosocred[0],},
	{SGUS_Var_WorkInfoPower,            0X0815,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.workinfopower[0],    &SGUS_RxVarData.workinfopower[0],},



    {SGUS_Var_LogoutPassWord,     0x0960,       32,      SGUS_VAR_STATE, &SGUS_TxVarData.logoutpassword[0], &SGUS_RxVarData.logoutpassword[0],},
    
    {SGUS_Var_StopInfoEnergy,    0X09A0,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfoenergy[0],    &SGUS_RxVarData.stopinfoenergy[0],},
    {SGUS_Var_StopInfoCost,    0X09A2,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfocost[0],    &SGUS_RxVarData.stopinfocost[0],},
    {SGUS_Var_StopInfoChargedTime,    0X09A4,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfochargedtime[0],    &SGUS_RxVarData.stopinfochargedtime[0],},
    {SGUS_Var_StopInfoStopTime,    0X09A6,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfochargeendtime[0],    &SGUS_RxVarData.stopinfochargeendtime[0],},
    {SGUS_Var_StopInfoTransactionNum,    0X09A8,       32,       SGUS_VAR_STATE, &SGUS_TxVarData.stopInfotransactionnum[0],    &SGUS_RxVarData.stopInfotransactionnum[0],},
    {SGUS_Var_StopInfoStopReason,    0X09B8,       32,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfostopreason[0],    &SGUS_RxVarData.stopinfostopreason[0],},
    {SGUS_Var_StopInfoStartSOC,    0X09C8,      4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfostartsoc[0],    &SGUS_RxVarData.stopinfostartsoc[0],},
    {SGUS_Var_StopInfoStopSOC,    0X09CA,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfostopsoc[0],    &SGUS_RxVarData.stopinfostopsoc[0],},
    {SGUS_Var_InfoChargeProcess,    0X09CC,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.endinfochargeprocess[0],    &SGUS_RxVarData.endinfochargeprocess[0],},
    {SGUS_Var_StopInfoCardInfo,    0X09CE,       32,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfocardinfo[0],    &SGUS_RxVarData.stopinfocardinfo[0],},
    {SGUS_Var_StopInfoCardBalance,    0X09DE,       4,       SGUS_VAR_STATE, &SGUS_TxVarData.stopinfobalance[0],    &SGUS_RxVarData.stopinfobalance[0],},

    {SGUS_Var_SysLoginPassWord,     0x0B12,     32,  SGUS_VAR_STATE, &SGUS_TxVarData.sysconfigpassword[0], &SGUS_RxVarData.sysconfigpassword[0],},

	{SGUS_Var_ButtonPageSysConfig,  0x0C10,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagesysconfig[0], &SGUS_RxVarData.buttonpagesysconfig[0],},
	{SGUS_Var_ButtonPageInfoInquiry,  0x0C11,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageinfoinquiry[0], &SGUS_RxVarData.buttonpageinfoinquiry[0],},
	{SGUS_Var_ButtonPageChargeRecord,  0x0C12,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagechargerecord[0], &SGUS_RxVarData.buttonpagechargerecord[0],},
	{SGUS_Var_ButtonPageFaultRecord,  0x0C13,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagefaultrecord[0], &SGUS_RxVarData.buttonpagefaultrecord[0],},
	{SGUS_Var_ButtonPagerInputControl,  0x0C14,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageinputcontrol[0], &SGUS_RxVarData.buttonpageinputcontrol[0],},
	{SGUS_Var_ButtonPagePowerOffSelect,  0x0C15,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagepoweroffsel[0], &SGUS_RxVarData.buttonpagepoweroffsel[0],},

	{SGUS_Var_ButtonPageElectricityMeterConfig,  0x0D10,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageelectricitymeterconfig[0], &SGUS_RxVarData.buttonpageelectricitymeterconfig[0],},
	{SGUS_Var_ButtonPageAuxPowerConfig,  0x0D11,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageauxpowerconfig[0], &SGUS_RxVarData.buttonpageauxpowerconfig[0],},
	{SGUS_Var_ButtonPagePowerModuleConfig,  0x0D12,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagepowermoduleconfig[0], &SGUS_RxVarData.buttonpagepowermoduleconfig[0],},
	{SGUS_Var_ButtonPagePileTest,  0x0D13,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagepiletest[0], &SGUS_RxVarData.buttonpagepiletest[0],},
	{SGUS_Var_ButtonPageServerAddrConfig,  0x0D14,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageserveraddrconfig[0], &SGUS_RxVarData.buttonpageserveraddrconfig[0],},
	{SGUS_Var_ButtonPageQRCodeConfig,  0x0D15,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageqrcodeconfig[0], &SGUS_RxVarData.buttonpageqrcodeconfig[0],},
	{SGUS_Var_ButtonPageAreaSet,  0x0D16,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageareaset[0], &SGUS_RxVarData.buttonpageareaset[0],},
	{SGUS_Var_ButtonPagePasswordRest,  0x0D17,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagepasswordreset[0], &SGUS_RxVarData.buttonpagepasswordreset[0],},

	{SGUS_Var_StateHighVoltage,  0x0D50,     2,   SGUS_VAR_STATE, &SGUS_TxVarData.statehighvoltate[0], &SGUS_RxVarData.statehighvoltate[0],},
	{SGUS_Var_ButtonSafePowerOff,  0x0D51,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonsafepoweroff[0], &SGUS_RxVarData.buttonsafepoweroff[0],},

	{SGUS_Var_InputControl,  0x0E10,     2,   SGUS_VAR_STATE, &SGUS_TxVarData.inputcontrol[0], &SGUS_RxVarData.inputcontrol[0],},

	{SGUS_VAR_ButtonAUX12V,  0x10D0,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonaux12v[0], &SGUS_RxVarData.buttonaux12v[0],},
	{SGUS_VAR_ButtonAUX24V,  0x10D1,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonaux24v[0], &SGUS_RxVarData.buttonaux24v[0],},


	{SGUS_Var_ButtonUserPowerOff,  0x1310,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonuserpoweroff[0], &SGUS_RxVarData.buttonuserpoweroff[0],},
	{SGUS_Var_IconUserPowerOff,  0x1310,     2,   SGUS_VAR_STATE, &SGUS_TxVarData.iconuserpoweroff[0], &SGUS_RxVarData.iconuserpoweroff[0],},

	{SGUS_Var_ButtonPageSafePowerOff,  0x1350,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpagesafepoweroff[0], &SGUS_RxVarData.buttonpagesafepoweroff[0],},
	{SGUS_Var_ButtonPageUserPowerOff,  0x1351,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonpageuserpoweroff[0], &SGUS_RxVarData.buttonpageuserpoweroff[0],},

	{SGUS_Var_ButtonLanguageEnum,      0x1400,     2,   SGUS_VAR_EVENT, &SGUS_TxVarData.buttonlang_enum[0], &SGUS_RxVarData.buttonlang_enum[0],},
};


static const sgus_pageinfo_t SGUS_PAGE[] =
{
    {SGUS_Page_Startup,          0x0000,     SGUS_Var_Null,              SGUS_Var_Null},
    {SGUS_Page_Homepage,          0x0005,     SGUS_Var_ButtonStop_PlugA,     SGUS_Var_ChargePrice},
    
    {SGUS_Page_UserLogin,        0x0009,     SGUS_Var_LoginUserName,     SGUS_Var_LoginPassWord},
    {SGUS_Page_PaymentMethod,    0x000A,     SGUS_Var_Payment_Method,    SGUS_Var_Payment_Method},
    {SGUS_Page_ChargeModeSel,    0x000B,     SGUS_Var_ChargeModAutoFull, SGUS_Var_ChargeModEnergy}, 
    {SGUS_Page_ModeMoney,        0x000C,     SGUS_Var_ChargeMoneyValue,  SGUS_Var_ChargeMoneyValue},
    {SGUS_Page_ModeTime,         0x000D,     SGUS_Var_ChargeTimeValue,   SGUS_Var_ChargeTimeValue},
    {SGUS_Page_ModeEnergy,        0x000E,     SGUS_Var_ChargeEnergyValue,    SGUS_Var_ChargeEnergyValue},
    {SGUS_Page_InfoConfirming,   0x0010,     SGUS_Var_Null,              SGUS_Var_Null},
    {SGUS_Page_InfoConfirmFail,  0x0011,     SGUS_Var_InfoConfirmFailCode, SGUS_Var_InfoConfirmFailCode},
    {SGUS_Page_InfoConfirmSucceed, 0x0012,   SGUS_Var_RFIDCardNum,              SGUS_Var_RFIDCardPoint},
    {SGUS_Page_StartCharge,      0x0013,     SGUS_Var_Null,              SGUS_Var_Null},
    {SGUS_Page_StartChargeErr,   0x0014,     SGUS_Var_ChargeStartFailueCode,              SGUS_Var_ChargeStartFailueCode},
	{SGUS_Page_PlugUnconnect,   0x0015,      SGUS_Var_Null,              SGUS_Var_Null},
	{SGUS_Page_PlugUnmatched,   0x0016,      SGUS_Var_Null,              SGUS_Var_Null},
	{SGUS_Page_CardLogin,   0x0018,      SGUS_Var_CardIcon,              SGUS_Var_CardIcon},
	{SGUS_Page_QRCodeLogin,   0x0018,    SGUS_Var_QRCode,              SGUS_Var_QRCode},

    {SGUS_Page_WorkInfo,         0x0019,     SGUS_Var_WorkInfoCurrent,       SGUS_Var_WorkInfoPower},
    {SGUS_Page_CardLogout,         0x001E,     SGUS_Var_Null,              SGUS_Var_Null},
    {SGUS_Page_UserLogout,       0x0020,     SGUS_Var_LogoutPassWord,    SGUS_Var_LogoutPassWord},

    {SGUS_Page_StopInfoCard,         0x0023,     SGUS_Var_Null,              SGUS_Var_Null},
	{SGUS_Page_StopInfoQRCode,         0x0024,     SGUS_Var_StopInfoEnergy,              SGUS_Var_InfoChargeProcess},

    {SGUS_Page_SysConfigPassWord,        0x0027,     SGUS_Var_SysLoginPassWord,  SGUS_Var_SysLoginPassWord},
	{SGUS_Page_SysManager,        0x0028,     SGUS_Var_ButtonPageSysConfig,  SGUS_Var_ButtonPagePowerOffSelect},
    {SGUS_Page_SysConfig,        0x0029,     SGUS_Var_ButtonPageElectricityMeterConfig,  SGUS_Var_ButtonPagePasswordRest},
    {SGUS_Page_SafePowerOff,    0x002A,     SGUS_Var_StateHighVoltage, SGUS_Var_ButtonSafePowerOff},
    {SGUS_Page_InputControl, 0x002B,  SGUS_Var_InputControl, SGUS_Var_InputControl},
    {SGUS_Page_AreaSet, 0x002C,  SGUS_Var_Null, SGUS_Var_Null},
    {SGUS_Page_PasswordReset, 0x002D,  SGUS_Var_Null, SGUS_Var_Null},

    {SGUS_Page_SysConfigSuccess, 0x002E,  SGUS_Var_Null, SGUS_Var_Null},
    {SGUS_Page_SysConfigFailue, 0x002F,  SGUS_Var_Null, SGUS_Var_Null},


	{SGUS_Page_AuxPowerConfig, 0x0039,  SGUS_VAR_ButtonAUX12V, SGUS_VAR_ButtonAUX24V},

	{SGUS_Page_UserPowerOff, 0x003E,  SGUS_Var_ButtonUserPowerOff, SGUS_Var_IconUserPowerOff},

	{SGUS_Page_PowerOffSelect, 0x0040,  SGUS_Var_ButtonPageSafePowerOff, SGUS_Var_ButtonPageUserPowerOff},

	{SGUS_Page_LangSelect,     0x0042,  SGUS_Var_ButtonLanguageEnum, SGUS_Var_ButtonLanguageEnum},
};





static const uint16_t SGUS_CRC16_L[] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140,
    0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741,
    0x0500, 0xC5C1, 0xC481, 0x0440
};
static const uint16_t SGUS_CRC16_H[] =
{
    0x0000, 0xCC01, 0xD801, 0x1400,
    0xF001, 0x3C00, 0x2800, 0xE401,
    0xA001, 0x6C00, 0x7800, 0xB401,
    0x5000, 0x9C01, 0x8801, 0x4400
};
/******************************************************************************
 * Name:    CRC16/MODBUS       x16+x15+x2+1
 * Poly:    0x8005
 * Init:    0xFFFF
 * Refin:   True
 * Refout:  True
 * Xorout:  0x0000
 * Note:
 *****************************************************************************/
static uint16_t SGUS_CRC16(uint8_t *Buffer, uint32_t Length)
{
    uint16_t CRCValue;
    uint8_t Dat;

    CRCValue = 0xFFFF;

    while(Length--)
    {
        Dat = *Buffer++;
        Dat ^= CRCValue;
        CRCValue >>= 8;
        CRCValue ^= SGUS_CRC16_L[Dat & 0x0F];
        CRCValue ^= SGUS_CRC16_H[(Dat>>4) & 0x0F];
    }

    return CRCValue;
}

sgus_error_t SGUS_WriteReg(sgus_regindex_t regindex, uint8_t length)
{
	sgus_error_t ret = SGUS_E_OK;

    uint8_t position = 0;
    
    uint8_t sendcnt = 0;

    uint16_t crcvalue;

	uint8_t i;

    for(i = 0; i < NumofRegIndex; i++)
    {
        if(SGUS_REG[i].regindex == regindex)
        {
            position = i;
            break;
        }
    }
    if(NumofRegIndex == i)
    {
        ret = SGUS_E_OTHER_ERR;
        return ret;
    }

    if(SGUS_REG_WRITEABLE != (SGUS_REG[position].regtype & SGUS_REG_WRITEABLE))
    {
        ret = SGUS_E_REG_RO;
        return ret;
    }
    
    SGUS_SendBuffer[sendcnt++] = (SGUS_START_OF_FRAME>>8) & 0xFF;
	SGUS_SendBuffer[sendcnt++] = SGUS_START_OF_FRAME & 0xFF;
	SGUS_SendBuffer[sendcnt++] = length + 2;
	SGUS_SendBuffer[sendcnt++] = SGUS_CMD_WRITE_REG;
	SGUS_SendBuffer[sendcnt++] = SGUS_REG[position].regaddr;

	for(i = 0; i < length; i++)
	{
        SGUS_SendBuffer[sendcnt++] = SGUS_REG[position].regtxdata[i];
	}


	if(TRUE == SGUS_EnableCRCFlag)
	{
		crcvalue = SGUS_CRC16(&SGUS_SendBuffer[3], SGUS_SendBuffer[2]);
		SGUS_SendBuffer[sendcnt++] = crcvalue & 0xFF;
		SGUS_SendBuffer[sendcnt++] = (crcvalue>>8) & 0xFF;
		SGUS_SendBuffer[2] += 2;
	}

	if(ESCIComm_SendDataBuff(ESCI_A, SGUS_SendBuffer, sendcnt))
	{
		ret = SGUS_E_OTHER_ERR;
	}
	return ret;
}


sgus_error_t SGUS_ReadRegRequest(sgus_regindex_t regindex, uint8_t length)
{
	sgus_error_t ret = SGUS_E_OK;

    uint8_t position = 0;
    
    uint8_t sendcnt = 0;

    uint16_t crcvalue;

	uint8_t i;

    for(i = 0; i < NumofRegIndex; i++)
    {
        if(SGUS_REG[i].regindex == regindex)
        {
            position = i;
            break;
        }
    }
    if(NumofRegIndex == i)
    {
        ret = SGUS_E_OTHER_ERR;
        return ret;
    }

    if(SGUS_REG_READABLE != (SGUS_REG[position].regtype & SGUS_REG_READABLE))
    {
        ret = SGUS_E_REG_WO;
        return ret;
    }
    
	SGUS_SendBuffer[sendcnt++] = (SGUS_START_OF_FRAME>>8) & 0xFF;
	SGUS_SendBuffer[sendcnt++] = SGUS_START_OF_FRAME & 0xFF;
	SGUS_SendBuffer[sendcnt++] = 3;
	SGUS_SendBuffer[sendcnt++] = SGUS_CMD_READ_REG;
	SGUS_SendBuffer[sendcnt++] = SGUS_REG[position].regaddr;
	SGUS_SendBuffer[sendcnt++] = length;
	if(TRUE == SGUS_EnableCRCFlag)
	{
		crcvalue = SGUS_CRC16(&SGUS_SendBuffer[3], SGUS_SendBuffer[2]);
		SGUS_SendBuffer[sendcnt++] = crcvalue & 0xFF;
        SGUS_SendBuffer[sendcnt++] = (crcvalue>>8) & 0xFF;
        SGUS_SendBuffer[2] += 2;
	}
    
    if(ESCIComm_SendDataBuff(ESCI_A, SGUS_SendBuffer, sendcnt))
    {
        ret = SGUS_E_OTHER_ERR;
    }

	return ret;
}


sgus_error_t SGUS_ReadReg_Async(uint8_t *data, uint8_t * passflg)
{
    uint8_t datalen;
    uint8_t cmd;
    uint8_t regaddr;
    uint8_t position = 0;
    uint16_t crcvalue;
    uint8_t i;

    cmd = data[3];
    if(SGUS_CMD_READ_REG != cmd)     //if the data is not reg data return
    {
        return SGUS_E_OTHER_ERR;
    }

    if(TRUE == SGUS_EnableCRCFlag)
    {
    	data[2] -= 2;
        crcvalue = (data[data[2]+4]<<8) | data[data[2]+3];
        if(crcvalue != SGUS_CRC16(&data[3], data[2]))
        {
            return SGUS_E_CRC_ERR;
        }
    }
    
    regaddr = data[4];
    for(i = 0; i < NumofRegIndex; i++)
    {
        if(SGUS_REG[i].regaddr == regaddr)
        {
            position = i;
            break;
        }
    }
    if(NumofRegIndex == i)
    {
        return SGUS_E_OTHER_ERR;
    }
    datalen = data[5];
    for(i = 0; i < datalen; i++) //copy reg data to regdatabuffer
    {
        SGUS_REG[position].regrxdata[i] = data[6+i];
    }
    
    *passflg = TRUE;
    return SGUS_E_OK;
}


sgus_error_t SGUS_WriteVar(sgus_varindex_t varindex, uint8_t length)
{
    sgus_error_t ret = SGUS_E_OK;

    uint8_t position = 0;
    
    uint8_t sendcnt = 0;
    uint16_t crcvalue;
    uint16_t varaddr_tmp;

	uint8_t i;

    for(i = 0; i < NumofVarIndex; i++)
    {
        if(SGUS_VAR[i].varindex == varindex)
        {
            position = i;
            break;
        }
    }
    if(NumofVarIndex == i)
    {
        ret = SGUS_E_OTHER_ERR;
        return ret;
    }

    varaddr_tmp = SGUS_VAR[position].varaddr + SGUS_VAR_OFFSET*SGUS_LangEnum;

    SGUS_SendBuffer[sendcnt++] = (SGUS_START_OF_FRAME>>8) & 0xFF; //sof high
	SGUS_SendBuffer[sendcnt++] = SGUS_START_OF_FRAME & 0xFF;      //sof low
    SGUS_SendBuffer[sendcnt++] = length + 3;                      //data to be send except crc
    SGUS_SendBuffer[sendcnt++] = SGUS_CMD_WRITE_VAR;             //write data cmd
    SGUS_SendBuffer[sendcnt++] = (varaddr_tmp >> 8) & 0xFF; //data address high
    SGUS_SendBuffer[sendcnt++] = varaddr_tmp & 0xFF;       //data address low

    for(i = 0; i < length; i++)
    {
        SGUS_SendBuffer[sendcnt++] = SGUS_VAR[position].vartxdata[i];                                //data to be write
    }
    if(TRUE == SGUS_EnableCRCFlag)
	{
		crcvalue = SGUS_CRC16(&SGUS_SendBuffer[3], SGUS_SendBuffer[2]);       //calc crc value
		SGUS_SendBuffer[sendcnt++] = crcvalue & 0xFF;                       //crc low
		SGUS_SendBuffer[sendcnt++] = (crcvalue>>8) & 0xFF;                  //crc high
		SGUS_SendBuffer[2] += 2;
	}

    if(ESCIComm_SendDataBuff(ESCI_A, SGUS_SendBuffer, sendcnt))
	{
	   ret = SGUS_E_OTHER_ERR;
	}
    return ret;
}



sgus_error_t SGUS_ReadVarRequest(sgus_varindex_t varindex, uint8_t length)
{
    sgus_error_t ret = SGUS_E_OK;

    uint8_t position = 0;
    uint8_t sendcnt = 0;
    uint8_t templength;
	uint16_t crcvalue;
	uint16_t varaddr_tmp;

	uint8_t i;

    templength = length;//(length + 1) / 2; //there are two bytes in one SGUS_address;

    for(i = 0; i < NumofVarIndex; i++)
    {
        if(SGUS_VAR[i].varindex == varindex)
        {
            position = i;
            break;
        }
    }
    if(NumofVarIndex == i)
    {
        ret = SGUS_E_OTHER_ERR;
        return ret;
    }
    
    varaddr_tmp = SGUS_VAR[position].varaddr + SGUS_VAR_OFFSET*SGUS_LangEnum;

    SGUS_SendBuffer[sendcnt++] = (SGUS_START_OF_FRAME>>8) & 0xFF;
	SGUS_SendBuffer[sendcnt++] = SGUS_START_OF_FRAME & 0xFF;
    SGUS_SendBuffer[sendcnt++] = 4;
    SGUS_SendBuffer[sendcnt++] = SGUS_CMD_READ_VAR;
    SGUS_SendBuffer[sendcnt++] = (varaddr_tmp >> 8) & 0xFF;
    SGUS_SendBuffer[sendcnt++] = varaddr_tmp & 0xFF;
    SGUS_SendBuffer[sendcnt++] = templength;
    if(TRUE == SGUS_EnableCRCFlag)
	{
		crcvalue = SGUS_CRC16(&SGUS_SendBuffer[3], SGUS_SendBuffer[2]);
        SGUS_SendBuffer[sendcnt++] = crcvalue & 0xFF;
		SGUS_SendBuffer[sendcnt++] = (crcvalue>>8) & 0xFF;
		SGUS_SendBuffer[2] += 2;
	}
    
    if(ESCIComm_SendDataBuff(ESCI_A, SGUS_SendBuffer, sendcnt))
    {
        ret = SGUS_E_OTHER_ERR;
    }

    return ret;
}

sgus_error_t SGUS_ReadVar_Async(uint8_t *data, uint8_t * passflg) //Auto Receive Data when variable changed
{
    uint8_t datalen;
    uint8_t cmd;
    uint8_t position = 0;
    uint16_t varaddr;
    uint16_t crcvalue;
    uint8_t i;

    cmd = data[3];
    if(SGUS_CMD_READ_VAR != cmd)     //if the data is not reg data return
    {
        return SGUS_E_OTHER_ERR;
    }

    if(TRUE == SGUS_EnableCRCFlag)
    {
    	data[2] -= 2;
        crcvalue = (data[data[2]+4]<<8) | data[data[2]+3];
        if(crcvalue != SGUS_CRC16(&data[3], data[2]))
        {
            return SGUS_E_CRC_ERR;
        }
    }
    
    varaddr = (data[4]<<8) | (data[5]);

    varaddr -= SGUS_VAR_OFFSET*SGUS_LangEnum;

    for(i = 0; i < NumofVarIndex; i++)
    {
        if(SGUS_VAR[i].varaddr == varaddr)
        {
            position = i;
            break;
        }
    }

    if(NumofVarIndex == i)
    {
        return SGUS_E_OTHER_ERR;
    }
    
    datalen = data[6];// * 2;
    for(i = 0; i < datalen; i++) //copy reg data to regdatabuffer
    {
        SGUS_VAR[position].varrxdata[i] = data[7+i];
    }
    *passflg = TRUE;
    return SGUS_E_OK;
}

volatile uint32_t SGUS_FrameLose_Cnt = 0;

void SGUS_Recieve_Task(void)
{
	uint16_t recvlen = 0;
	uint8_t *pdata = SGUS_RecvBuffer;
	uint8_t passflg;
	uint16_t i;
	ESCIComm_ReceiveDataBuff(ESCI_A, SGUS_RecvBuffer, &recvlen);



	if(0 != recvlen )
	{
		if(0x5A != pdata[0] || 0xA5 != pdata[1])
		{
			SGUS_FrameLose_Cnt++;
		}
		for(i = 0; i < recvlen; i++)
		{
			if(0x5A == pdata[i] && 0xA5 == pdata[i+1])
			{
				pdata[i] = 0x5A;
				pdata[i+1] = 0xA5;
				passflg = FALSE;
				SGUS_ReadReg_Async(&pdata[i], &passflg);
				SGUS_ReadVar_Async(&pdata[i], &passflg);
				if(FALSE == passflg)
				{
					SGUS_FrameLose_Cnt++;
				}
			}
		}
	}
}

void SGUS_ISRCallback(void)
{
    uint16_t recvlen = 0;
    static uint8_t totallen = 0;
    static uint8_t expectlen = 0;
    static uint8_t backupbyte = 0xFF;
    uint8_t i;
    ESCIComm_ReceiveDataBuff(ESCI_A, SGUS_RecvBuffer+totallen, &recvlen);
    totallen += recvlen;
#if 0
    if(totallen > 1)
    {
        if(0x5A != SGUS_RecvBuffer[0] || 0xA5 != SGUS_RecvBuffer[1])
        {
            for(i = 1; i < totallen; i++)
            {
                SGUS_RecvBuffer[i-1] = SGUS_RecvBuffer[i];
            }
            totallen -= 1;
        }

        if(0x5A == SGUS_RecvBuffer[totallen-2] && 0xA5 == SGUS_RecvBuffer[totallen-1])
        {
            SGUS_RecvBuffer[0] = 0x5A;
            SGUS_RecvBuffer[1] = 0xA5;
            totallen = 2;
        }
    }

    if(totallen > 2)
    {
        expectlen = SGUS_RecvBuffer[2];
        if(TRUE == SGUS_EnableCRCFlag)
        {
            expectlen += 2;
        }
    }

    if(totallen >= expectlen + 3)
    {
        backupbyte = SGUS_RecvBuffer[totallen-1];
        SGUS_ReadReg_Async(SGUS_RecvBuffer);
        SGUS_ReadVar_Async(SGUS_RecvBuffer);
        totallen = 0;
        expectlen = 0;
    }

#else
    if(totallen > 1)
    {
    	if(totallen > 2)//if lost more than two bytes£¬we can check it out
		{
			if(0x5A == SGUS_RecvBuffer[totallen-2] && 0xA5 == SGUS_RecvBuffer[totallen-1])
			{
				SGUS_RecvBuffer[0] = 0x5A;
				SGUS_RecvBuffer[1] = 0xA5;
				backupbyte = 0xFF;
				totallen = 2;
				SGUS_FrameLose_Cnt++;
			}
    	}

        if(0x5A == SGUS_RecvBuffer[0] && 0xA5 == SGUS_RecvBuffer[1])
        {
            if(totallen > 2)
            {
                expectlen = SGUS_RecvBuffer[2];
                if(TRUE == SGUS_EnableCRCFlag)
                {
                    expectlen += 2;
                }
            }
            if(totallen >= expectlen + 3)
            {
                backupbyte = SGUS_RecvBuffer[totallen-1];
                SGUS_ReadReg_Async(SGUS_RecvBuffer);
                SGUS_ReadVar_Async(SGUS_RecvBuffer);
                totallen = 0;
                expectlen = 0;
            }
        }
        else
        {
            if(0xA5 == SGUS_RecvBuffer[0] && 0x5A ==backupbyte) //if Lost Onebyte, we can recoverit
            {
                SGUS_RecvBuffer[2] = SGUS_RecvBuffer[1];
                SGUS_RecvBuffer[0] = 0x5A;
                SGUS_RecvBuffer[1] = 0xA5;
                backupbyte = 0xFF;
                totallen = 3;
                SGUS_FrameLose_Cnt++;
            }
        }
    }
#endif
}


const sgus_reginfo_t * SGUS_GetRegInfo(void)
{
    return &SGUS_REG[0];
}

const sgus_varinfo_t * SGUS_GetVarInfo(void)
{
    return &SGUS_VAR[0];
}


const sgus_pageinfo_t * SGUS_GetPageInfo(void)
{
    return &SGUS_PAGE[0];
}


sgus_regdata_t * SGUS_GetTxRegData(void)
{
    return &SGUS_TxRegData;
}

sgus_regdata_t * SGUS_GetRxRegData(void)
{
    return &SGUS_RxRegData;
}

sgus_vardata_t * SGUS_GetTxVarData(void)
{
    return &SGUS_TxVarData;
}


sgus_vardata_t * SGUS_GetRxVarData(void)
{
    return &SGUS_RxVarData;
}





