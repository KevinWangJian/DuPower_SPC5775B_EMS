#include "NvM.h"
#include "Rte_NvM_Type.h"
//#include "Fls.h"
#include "WdgIf.h"
#include "common.h"
NvM_RequestResultType ReadAllStatus = NVM_REQ_PENDING;
void Nvm_TestMultiBlockCallback(uint8 ServiceId, NvM_RequestResultType JobResult)
{
	if(ServiceId==NVM_SERVICE_ID_READ_ALL)
	{
		ReadAllStatus = JobResult;
	}
}


uint16 ReadAllcounter, WriteAllcounter,WriteAllcounter2;
void IC_BswM_NvM_ReadAll ( void )
{
	NvM_Rb_StatusType status_NvM;
	MemIf_StatusType stMemIf_en;

	ReadAllcounter=0;
	NvM_ReadAll();

#ifndef _GREENHILLS_C_RH850_
	/*
	 * gives sometime to perform ReadAll command
	 */
//	WdgIf_SetTriggerCondition(0, 2000);
#endif

#ifdef _GNU_C_TRICORE_
	/* disable detection and report of timeout for FLS */
	Fls_ControlTimeoutDet(0);
#endif
	do
	{
		NvM_MainFunction();
		MemIf_Rb_MainFunction();

		NvM_Rb_GetStatus(&status_NvM);
		stMemIf_en = MemIf_Rb_GetStatus();

		ReadAllcounter++;
	} while ( (status_NvM == NVM_RB_STATUS_BUSY ) || (stMemIf_en == MEMIF_BUSY));
#ifdef _GNU_C_TRICORE_
	/* enable detection and report of timeout for FLS */
	Fls_ControlTimeoutDet(1);
#endif
}


void IC_BswM_NvM_WriteAll ( void )
{
	NvM_Rb_StatusType status_NvM;
	MemIf_StatusType stMemIf_en;
	MemIf_StatusType FlsMemIf_en;
	WriteAllcounter=0;
	NvM_WriteAll();
	do
	{
		NvM_MainFunction();
		MemIf_Rb_MainFunction();
		NvM_Rb_GetStatus(&status_NvM);
		stMemIf_en = MemIf_Rb_GetStatus();
		WriteAllcounter++;
	} while ( (status_NvM == NVM_RB_STATUS_BUSY ) || (stMemIf_en == MEMIF_BUSY));

	/*
	 * Here RTE scheduling is stopped, so WdgM won't be triggered anymore.
	 * we need to prevent the Wdg from reseting the CPU.
	 * WDG_SLOW_MODE so Wdg increases the hardware timeout period
	 */
#ifndef _GREENHILLS_C_RH850_
	//WdgIf_SetMode(0, WDGIF_SLOW_MODE);
#endif

#if 0
	/*
	 * gives sometime to perform WriteAll command
	 */
	WdgIf_SetTriggerCondition(0, 2000);
#ifdef _GNU_C_TRICORE_
	/* disable detection and report of timeout for FLS */
	Fls_ControlTimeoutDet(0);
#endif
	do
	{
		NvM_MainFunction();
		MemIf_Rb_MainFunction();

		NvM_Rb_GetStatus(&status_NvM);
		stMemIf_en = MemIf_Rb_GetStatus();

		WriteAllcounter++;
	} while ( (status_NvM == NVM_RB_STATUS_BUSY ) || (stMemIf_en == MEMIF_BUSY));


	/* in case of page swap is required a second loop to complete the
	 * write of the updated block after the page swap
	 */

	NvM_WriteAll();

	do
	{
		NvM_MainFunction();
		MemIf_Rb_MainFunction();

		NvM_Rb_GetStatus(&status_NvM);
		stMemIf_en = MemIf_Rb_GetStatus();

		WriteAllcounter2++;
	} while ( (status_NvM == NVM_RB_STATUS_BUSY ) || (stMemIf_en == MEMIF_BUSY));

#ifdef _GNU_C_TRICORE_
	/* enable detection and report of timeout for FLS */
	Fls_ControlTimeoutDet(1);
#endif
#endif
}
