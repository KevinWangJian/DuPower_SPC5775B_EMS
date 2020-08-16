/*
 * Switch_SJA1105.h
 *
 *  Created on: 2019Äê10ÔÂ23ÈÕ
 *      Author: admin
 */

#ifndef USERS_SWITCH_SJA1105_H_
#define USERS_SWITCH_SJA1105_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"
#include "Reg_eSys.h"
#include "StdRegMacros.h"
#include "Dio_Cfg.h"
#include "Dio.h"


#define  DRIVER_USE_MCAL						(1U)

#define  SWITCH_SJA1105_RESET_LOW()				Dio_WriteChannel(DioConf_DioChannel_SJA1105_RESET, STD_LOW)
#define  SWITCH_SJA1105_RESET_HIGH()			Dio_WriteChannel(DioConf_DioChannel_SJA1105_RESET, STD_HIGH)


/* Switch core device id definition. */
#define SJA1105PEL_CORE_EVICE_ID				(0xAF00030EU)
#define SJA1105QEL_CORE_DEVICE_ID				(0xAE00030EU)
#define SJA1105REL_CORE_DEVICE_ID				(0xAF00030EU)
#define SJA1105SEL_CORE_DEVICE_ID				(0xAE00030EU)

/* Switch PROD_ID register PART_NR definition. */
#define SJA1105PEL_PROD_ID_PARTNR				(0x9A84U)
#define SJA1105QEL_PROD_ID_PARTNR				(0x9A85U)
#define SJA1105REL_PROD_ID_PARTNR				(0x9A86U)
#define SJA1105SEL_PROD_ID_PARTNR				(0x9A87U)


#define DEVICE_ID_REG							(0x000000U)

#define DEVICE_CONFIGFLAG_REG					(0x000001U)
#define DEVICE_CONFIGFLAG_REG_CONFIGS_MASK		((uint32_t)1 << 31)
#define DEVICE_CONFIGFLAG_REG_CRCCHKL_MASK		((uint32_t)1 << 30)
#define DEVICE_CONFIGFLAG_REG_IDS_MASK			((uint32_t)1 << 29)
#define DEVICE_CONFIGFLAG_REG_CRCCHKG_MASK		((uint32_t)1 << 28)


#define RESET_CTRL_REG							(0x100440U)
#define RESET_CTRL_POR_RST_MASK					((uint32_t)1 << 1)
#define RESET_CTRL_COLD_RST_MASK				((uint32_t)1 << 2)
#define RESET_CTRL_WARM_RST_MASK				((uint32_t)1 << 3)

#define UNIT_DISABLE_REG_FOR_RGU				(0x1007FDU)


#define CFG_PAD_MII0_TX_REG						(0x100800U)
#define CFG_PAD_MII0_RX_REG						(0x100801U)

#define IDIV_0_C_REG							(0x10000BU)
#define IDIV_1_C_REG							(0x10000CU)


#define DEVICE_PROD_ID_REG						(0x100BC3U)
#define DEVICE_PROD_ID_REG_PART_NR_MASK			((uint32_t)0xFFFFU << 4)


typedef enum
{
	DEVICE_NONE = 0,
	DEVICE_SJA1105PEL,
	DEVICE_SJA1105QEL,
	DEVICE_SJA1105REL,
	DEVICE_SJA1105SEL
}SJA1105TypeDef;

typedef enum
{
	CONFIG_INVALID = 0,
	CONFIG_VALID
}SJA1105ConfigStatus;


typedef struct 
{
    uint8_t* pConfig0Ptr;
    uint16_t Config0Size;

    uint8_t* pConfig1Ptr;
    uint16_t Config1Size;

    uint8_t* pConfig2Ptr;
    uint16_t Config2Size;

    uint8_t* pConfig3Ptr;
    uint16_t Config3Size;
}SJA1105_StaticConfigPara_t;


extern SJA1105_StaticConfigPara_t Sja1105StaticConfigPa;


int  SJA1105_ResetChip(void);
int  SJA1105_ConfigureParamters(SJA1105_StaticConfigPara_t* pStaticConfig);
void SJA1105_Init(void);


#ifdef __cplusplus
}
#endif
#endif /* USERS_SWITCH_SJA1105_H_ */
