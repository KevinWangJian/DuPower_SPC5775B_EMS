
#ifndef SGUS_API_H_
#define SGUS_API_H_

#include "sgus_basic.h"

#define QUEUE_SIZE  40
#define QUEUE_TYPE_REG   0
#define QUEUE_TYPE_VAR   1


#define SGUS_SOC_NONE             200

#define SGUS_PAYMENTMETHOD_QR_EU    1
#define SGUS_PAYMENTMETHOD_RFID_EU  2
#define SGUS_PAYMENTMETHOD_CC_EU    3
#define SGUS_PAYMENTMETHOD_QR_CN    4
#define SGUS_PAYMENTMETHOD_RFID_CN  5
#define SGUS_PAYMENTMETHOD_CC_CN    6

#define SGUS_CARDICON_RFID          0
#define SGUS_CARDICON_CREDITCARD    1

typedef struct
{
    uint8_t type[QUEUE_SIZE];    //reg or var
    uint8_t queues[QUEUE_SIZE];  //fifo to save regindex or varindex
    uint8_t length[QUEUE_SIZE];  //reg or var length

    uint8_t head;
    uint8_t tail;
    uint8_t count;
}sgus_txqueue_t;


#define SGUS_SERIALNUM_MAX    32

typedef uint8_t sgus_version_t;

typedef struct
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t week;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
}sgus_rtc_t;

typedef enum
{
    SGUS_NetworkOff,
    SGUS_NetworkOn_Low,
    SGUS_NetworkOn_High
}sgus_networkstate_t;

typedef enum
{
	SGUS_PlugStateIdle = 1,
    SGUS_PlugStateConnect,
    SGUS_PlugStateCharging,
    SGUS_PlugStateComplete,
    SGUS_PlugStateFault
}sgus_plugstate_t;


extern uint8_t SGUS_EnableCRC_Flag;
//void SGUS_SetTxQueue(uint8_t indextype, uint8_t indexvalue, uint8_t length);
void SGUS_GetTxQueue(uint8_t *indextype, uint8_t *indexvalue, uint8_t *length, uint8_t *valid);

uint8_t SGUS_ApiInit(uint8_t recoverflg);

uint8_t SGUS_SetCurrentPage(sgus_pageindex_t pageindex);
uint8_t SGUS_GetCurrentPage(sgus_pageindex_t * pageindex);

uint8_t SGUS_GetRunTime(uint32_t * runtime);

uint8_t SGUS_SetSerialNum(uint8_t * buffer);
uint8_t SGUS_GetSerialNum(uint8_t * buffer);

uint8_t SGUS_SetNetworkState(sgus_networkstate_t state);
uint8_t SGUS_GetNetworkState(sgus_networkstate_t * state);

uint8_t SGUS_SetCurrentPlug(uint8_t plug);
uint8_t SGUS_GetCurrentPlug(uint8_t *plug);

uint8_t SGUS_SetTimOut(uint16_t value);

uint8_t SGUS_GetButtonBack(uint8_t *button);

uint8_t SGUS_GetButtonConfirm(uint8_t *button);

uint8_t SGUS_GetButtonSysInfo(uint8_t * button);

uint8_t SGUS_GetButtonHomePage(uint8_t *button);

uint8_t SGUS_GetButtonStopCharge(uint8_t * button);

uint8_t SGUS_GetButtonTest(uint8_t * button);

uint8_t SGUS_GetButtonStop_PlugA(uint8_t * button);

uint8_t SGUS_GetButtonStop_PlugB(uint8_t * button);

uint8_t SGUS_GetButtonBase_PlugA(uint8_t * button);

uint8_t SGUS_GetButtonBase_PlugB(uint8_t * button);

uint8_t SGUS_GetButtonLangSelect(uint8_t * button);

uint8_t SGUS_SetMarkedWord_PlugA(uint8_t markedword);
uint8_t SGUS_GetMarkedWord_PlugA(uint8_t * markedword);

uint8_t SGUS_SetMarkedWord_PlugB(uint8_t markedword);
uint8_t SGUS_GetMarkedWord_PlugB(uint8_t * markedword);

uint8_t SGUS_SetPlugState_PlugA(sgus_plugstate_t state);
uint8_t SGUS_GetPlugState_PlugA(sgus_plugstate_t * state);

uint8_t SGUS_SetPlugState_PlugB(sgus_plugstate_t state);
uint8_t SGUS_GetPlugState_PlugB(sgus_plugstate_t *state);

uint8_t SGUS_SetRemainingTime_PlugA(uint16_t     lefttime);
uint8_t SGUS_GetRemainingTime_PlugA(uint16_t   * lefttime);

uint8_t SGUS_SetRemainingTime_PlugB(uint16_t     lefttime);
uint8_t SGUS_GetRemainingTime_PlugB(uint16_t     *  lefttime);

uint8_t SGUS_SetSOCGreen_PlugA(uint8_t   soc);
uint8_t SGUS_GetSOCGreen_PlugA(uint8_t * soc);

uint8_t SGUS_SetSOCGreen_PlugB(uint8_t   soc);
uint8_t SGUS_GetSOCGreen_PlugB(uint8_t * soc);

uint8_t SGUS_SetSOCRed_PlugA(uint8_t   soc);
uint8_t SGUS_GetSOCRed_PlugA(uint8_t * soc);

uint8_t SGUS_SetSOCRed_PlugB(uint8_t   soc);
uint8_t SGUS_GetSOCRed_PlugB(uint8_t * soc);

uint8_t SGUS_SetChargePrice(uint32_t price);
uint8_t SGUS_GetChargePrice(uint32_t * price);

uint8_t SGUS_GetButtonLangEnum(uint8_t *button);
uint8_t SGUS_SetLangEnum(uint8_t value);
uint8_t SGUS_GetLangEnum(void);

uint8_t SGUS_SetLoginUserName(uint8_t *buffer);
uint8_t SGUS_GetLoginUserName(uint8_t * buffer);

uint8_t SGUS_SetLoginPassWord(uint8_t *buffer);
uint8_t SGUS_GetLoginPassWord(uint8_t * buffer);

uint8_t SGUS_GetButtonPaymentMethod(uint8_t * button);

uint8_t SGUS_SetQRCode(uint8_t * data);

uint8_t SGUS_GetButtonAutoFull(uint8_t * button);

uint8_t SGUS_GetButtonMoney(uint8_t * button);

uint8_t SGUS_GetButtonTime(uint8_t * button);

uint8_t SGUS_GetButtonEnergy(uint8_t * button);

uint8_t SGUS_SetChargeMoneyValue(uint16_t value);
uint8_t SGUS_GetChargeMoneyValue(uint16_t *value);

uint8_t SGUS_SetChargeTimeValue(uint16_t value);
uint8_t SGUS_GetChargeTimeValue(uint16_t *value);

uint8_t SGUS_SetChargeEnergyValue(uint16_t value);
uint8_t SGUS_GetChargeEnergyValue(uint16_t *value);

uint8_t SGUS_SetAuthCheckFailCode(uint8_t * failcode);

uint8_t SGUS_SetRFIDCardNum(uint8_t *buffer);

uint8_t SGUS_SetRFIDCardBalance(uint32_t balance);

uint8_t SGUS_SetRFIDCardPoint(uint32_t point);

uint8_t SGUS_SetChargeFailCode(uint8_t *buffer);

uint8_t SGUS_SetCardTypeIcon(uint8_t icon);
uint8_t SGUS_GetCardTypeIcon(uint8_t * icon);

uint8_t SGUS_SetWorkInfoCurrent(uint32_t data);
uint8_t SGUS_GetWorkInfoCurrent(uint32_t *data);

uint8_t SGUS_SetWorkInfoVoltage(uint32_t data);
uint8_t SGUS_GetWorkInfoVoltage(uint32_t *data);

uint8_t SGUS_SetWorkInfoEnergy(uint32_t data);
uint8_t SGUS_GetWorkInfoEnergy(uint32_t *data);

uint8_t SGUS_SetWorkInfoChargingTime(uint32_t data);
uint8_t SGUS_GetWorkInfoChargingTime(uint32_t *data);

uint8_t SGUS_SetWorkInfoRemainingTime(uint32_t data);
uint8_t SGUS_GetWorkInfoRemainingTime(uint32_t *data);

uint8_t SGUS_SetWorkInfoCost(uint32_t data);
uint8_t SGUS_GetWorkInfoCost(uint32_t *data);

uint8_t SGUS_SetPlugState(sgus_plugstate_t state);
uint8_t SGUS_GetPlugState(sgus_plugstate_t * state);

uint8_t SGUS_SetChargingGIF(uint8_t state);
uint8_t SGUS_GetChargingGIF(uint8_t * state);

uint8_t SGUS_SetSOCGreen(uint8_t   soc);
uint8_t SGUS_GetSOCGreen(uint8_t * soc);

uint8_t SGUS_SetSOCRed(uint8_t   soc);
uint8_t SGUS_GetSOCRed(uint8_t * soc);

uint8_t SGUS_SetWorkInfoPower(uint32_t power);
uint8_t SGUS_GetWorkInfoPower(uint32_t * power);

uint8_t SGUS_SetLogoutPassWord(uint8_t *buffer);
uint8_t SGUS_GetLogoutPassWord(uint8_t * buffer);

uint8_t SGUS_SetStopInfoEnergy(uint32_t energy);

uint8_t SGUS_SetStopInfoMoney(uint32_t money);

uint8_t SGUS_SetStopInfoChargedTime(uint32_t time);

uint8_t SGUS_SetStopInfoTransactionNum(uint8_t * number);

uint8_t SGUS_SetStopInfoStopReason(uint8_t * reson);

uint8_t SGUS_SetStopInfoStartSOC(uint32_t soc);

uint8_t SGUS_SetStopInfoStopSOC(uint32_t soc);

uint8_t SGUS_SetStopInfoCardInfo(uint8_t * id);

uint8_t SGUS_SetStopInfoCardBalance(uint32_t balance);

uint8_t SGUS_SetSysConfigPassWord(uint8_t *buffer);
uint8_t SGUS_GetSysConfigPassWord(uint8_t * buffer);

uint8_t SGUS_GetButtonPageSysConfig(uint8_t *button);

uint8_t SGUS_GetButtonPageInfoInquiry(uint8_t *button);

uint8_t SGUS_GetButtonPageChargeRecord(uint8_t *button);

uint8_t SGUS_GetButtonPageFaultRecord(uint8_t *button);

uint8_t SGUS_GetButtonPageInputControl(uint8_t *button);

uint8_t SGUS_GetButtonPagePowerOffSelect(uint8_t *button);

uint8_t SGUS_GetButtonPageElectricityMeterConfig(uint8_t *button);

uint8_t SGUS_GetButtonPageAuxPowerConfig(uint8_t *button);

uint8_t SGUS_GetButtonPagePowerModuleConfig(uint8_t *button);

uint8_t SGUS_GetButtonPagePileTest(uint8_t *button);

uint8_t SGUS_GetButtonPageServerAddrConfig(uint8_t *button);

uint8_t SGUS_GetButtonPageQRCodeConfig(uint8_t *button);

uint8_t SGUS_GetButtonPageAreaSet(uint8_t *button);

uint8_t SGUS_GetButtonPagePasswordReset(uint8_t *button);

uint8_t SGUS_SetHighVoltageState(uint8_t state);
uint8_t SGUS_GetHighVoltageState(uint8_t *state);

uint8_t SGUS_GetButtonSafePowerOff(uint8_t *button);

uint8_t SGUS_SetStationInput(uint8_t value);
uint8_t SGUS_GetStationInput(uint8_t *value);

uint8_t SGUS_GetButtonAux12V(uint8_t *button);

uint8_t SGUS_GetButtonAux24V(uint8_t *button);

uint8_t SGUS_GetButtonUserPowerOff(uint8_t *button);

uint8_t SGUS_SetUserPowerOffIcon(uint8_t icon);
uint8_t SGUS_GetUserPowerOffIcon(uint8_t *icon);

uint8_t SGUS_GetButtonPageSafePowerOff(uint8_t *button);

uint8_t SGUS_GetButtonPageUserPowerOff(uint8_t *button);


extern void SGUS_Task_10ms(void);







#endif


