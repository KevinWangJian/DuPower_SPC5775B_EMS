/*
 * main.c
 *
 *  Created on: Aug 9, 2018
 *      Author: CIX2SGH
 */

#include "Os.h"
#include "Pll.h"
#include "Pit.h"

 #include "Mcu.h"
 #include "Mcu_Cfg.h"

 #include "McuFunc.h"

#include "Mcl.h"
#include "CDD_Mcl_Cfg.h"

 #include "Port.h"
 #include "Port_Cfg.h"

 #include "Gpt.h"
 #include "Gpt_Cfg.h"
 #include "EcuM.h"

#if 0
/* Initalize PIT channel 0 for desired SYSCLK counts*/
#define PIT0_TIMEOUT	100000	//1MS

static void Init_Target(void)
{
	//Init_SystemClock();
	PIT0_Init(100000);
}
#endif


#pragma section DATA ".AppProgramValid"
uint8_t APPPRO_VALID[8] = {0x5A, 0x5A, 0x5A, 0x5A, 0xA5, 0xA5, 0xA5, 0xA5};
#pragma section DATA



int main(void)
{
	//Init_Target();

	Os_InitializeVectorTable();

	EcuM_Init();

//	StartOS(OSDEFAULTAPPMODE);

	return 0;
}
