/*
 * McuFunc.h
 *
 *  Created on: Jun 6, 2018
 *      Author: CIX2SGH
 */

#ifndef MCUFUNC_H
#define MCUFUNC_H

/* Include Files */
#include "IoAb.h"
#include "Mcu.h"
#include "Port.h"
#include "Gpt.h"
//#include "Wdg.h"
#include "Adc.h"
#include "Spi.h"
#include "Can.h"
#include "sbcif.h"
#include "Pwm.h"
#include "McanComm.h"
#include "Fls.h"

#include "Can_43_MCAN.h"


#include "Fls_Cfg.h"
#include "Integration.h"

/* Macro Definitions */

/* EcuM Initialization */
#define Mcu_Config	McuConfigPB_0
//#define Port_Config	PortConfigSet
#define Port_Config	PortConfigSet_0
//#define Gpt_Config	GptChannelConfigSet
#define Gpt_Config	GptChannelConfigSet_0
//#define Gpt_Config	GptChannelConfigSet_0 OsCounter
#define Wdg_Config	WdgSettingsConfig_Inner
#define Mcl_Config  MclConfigSet_0

/* BswM Initialization */
#define ADC_INIT()      Adc_Init(&AdcConfigSet_0)
#define PWM_INIT()      Pwm_Init(&PwmChannelConfigSet_0)
#define SPI_INIT()      Spi_Init(&SpiDriver)
#define SPI_CONFIG_TRANSMIT_MODE()  (Spi_SetAsyncMode(SPI_POLLING_MODE))
#define CAN_INIT()      Can_Init(&CanConfigSet)
#define SBC_INIT()      sbc_init()
#define MCAN_INIT()		McanComm_Init()

//#define SBC_RUN()           uja1076_run()
//#define SBC_PREP_SHUTDOWN() uja1076_PrepShutDown()
#define EA_INIT()       IC_EA_Init()
#define FEE_INIT()       IC_FEE_Init()
#define FLS_INIT()      Fls_Init(&FlsConfigSet_0)
//#define FLS_INIT()      Flash_Init();
#define AFE_INIT()      IC_Afe_Init()
#define CDD_INIT()      Cdd_Init()

/* Function Declaration */
extern void McuFunc_InitializeClock(void);

#endif /* MCUFUNC_H */
