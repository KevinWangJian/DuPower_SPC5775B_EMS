/*
 * Os_Callbacks.c
 *
 *  Created on: Jun 2, 2018
 *      Author: CIX2SGH
 */

#include "Os.h"
#include "IoAb.h"

#define OS_START_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.h"
FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Error)
{
}
#define OS_STOP_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.h"
FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void)
{
}
#define OS_STOP_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.h"
FUNC(boolean, OS_OS_CBK_IDLE_CODE) Os_Cbk_Idle(void)
{
	return TRUE;
}
#define OS_STOP_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.h"
FUNC(void, OS_OS_CBK_INSHUTDOWN_CODE) Os_Cbk_InShutdown(void)
{
	Sys_Force_Shutdown();		//20180920-20:54  zyw
}
#define OS_STOP_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.h"

#define OS_START_SEC_CODE_LIB
#include "Os_MemMap.h"
void Os_Cat1_Wrapper_OS_Default_IRQHandler(void)
{
	//Sys_Shutdown();
}
#define OS_STOP_SEC_CODE_LIB
#include "Os_MemMap.h"
