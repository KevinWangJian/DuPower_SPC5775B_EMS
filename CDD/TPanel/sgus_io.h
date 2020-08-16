
#ifndef SGUS_IO_H_
#define SGUS_IO_H_

#include "sgus_api.h"

#define SGUS_INIT     0
#define SGUS_WORK     1
#define SGUS_BUSERR   2
#define SGUS_FAULT    3


#define SGUS_CCU_CC1_STATE_NOTCONNECT  0
#define SGUS_CCU_CC1_STATE_HALFCONNECT 1
#define SGUS_CCU_CC1_STATE_CONNECT     2



#define SGUS_CCU_STATE_NOTREADY   0
#define SGUS_CCU_STATE_STANDBY    1
#define SGUS_CCU_STATE_ISODETECT  2
#define SGUS_CCU_STATE_PRECHARGE  3
#define SGUS_CCU_STATE_CHARGING   4
#define SGUS_CCU_STATE_STOPCHARGE 5
#define SGUS_CCU_STATE_FAULT      6
#define SGUS_CCU_STATE_POWERDOWN  7

#define SGUS_SERIAL_NUM           "Du_Power_Test"

#define SGUS_CCV_CHARGE_TYPE_NONE 0
#define SGUS_CCV_CHARGE_TYPE_CC   1
#define SGUS_CCV_CHARGE_TYPE_RFID 2
#define SGUS_CCV_CHARGE_TYPE_APP  3
#define SGUS_CCV_CHARGE_TYPE_QR   4


#define SGUS_CCU_CHARGE_MODE_TIME     1
#define SGUS_CCU_CHARGE_MODE_ENERGY   2
#define SGUS_CCU_CHARGE_MODE_MONEY    3
#define SGUS_CCU_CHARGE_MODE_AUTOFULL 4

#define AFC_100_AH_CN             1
#define AFC_200_LH_CN             2
#define AFC_200_LH_EU             3
#define AFC_200_AH_CN             4

#define SGUS_TEST_SN_NUMBER       AFC_200_AH_CN

#if (AFC_100_AH_CN == SGUS_TEST_SN_NUMBER)   //AFC-100-AH-CN

#define SGUS_TEST_QRCODE_LEFT    "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21LHE0220011101"
#define SGUS_TEST_QRCODE_RIGHT   "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21LHE0220011102"

#elif (AFC_200_LH_CN == SGUS_TEST_SN_NUMBER) //AFC-200-LH-CN

#define SGUS_TEST_QRCODE_LEFT    "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21AHC0220011201"
#define SGUS_TEST_QRCODE_RIGHT   "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21AHC0220011202"

#elif (AFC_200_LH_EU == SGUS_TEST_SN_NUMBER) //AFC-200-LH-EU

#define SGUS_TEST_QRCODE_LEFT    "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21AHC0220011301"
#define SGUS_TEST_QRCODE_RIGHT   "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=A21AHC0220011302"

#elif (AFC_200_AH_CN == SGUS_TEST_SN_NUMBER) //AFC-200-AH-CN

#define SGUS_TEST_QRCODE_LEFT    "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=21AHC02001100401"
#define SGUS_TEST_QRCODE_RIGHT   "http://www.admin.du-power.com/pages/outer/buffer/buffer?gunCode=21AHC02001100402"

#endif


typedef enum
{
	UserType_Null,
    UserType_RFID,
	UserType_CreditCard,
	UserType_QRCode,
    UserType_VIP,
    UserType_VIN
}sgus_usertype_t;


typedef struct
{
	char flgname[14];
	uint16_t value;
}SGUS_StationInputCtl_eeprom;

void SGUS_IO_Store_InputControl(uint8_t * inputcontrol);
#endif

