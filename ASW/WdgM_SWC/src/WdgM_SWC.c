/* *****************************************************************************
 * BEGIN: Banner
 *-----------------------------------------------------------------------------
 *                                 ETAS GmbH
 *                      D-70469 Stuttgart, Borsigstr. 14
 *-----------------------------------------------------------------------------
 *    Administrative Information (automatically filled in by ISOLAR)         
 *-----------------------------------------------------------------------------
 * Name: Code-Frame generation feature
 * Description:
 * Version: 9.3
 *-----------------------------------------------------------------------------
 * END: Banner
 ******************************************************************************

 * Project : ETAS_AR_BSW3P1
 * Component: /WdgM_SWC/WdgM_SWC
 * Runnable : All Runnables in SwComponent
 *****************************************************************************
 * Tool Version: ISOLAR-A V 9.0
 * Author: Zhang Yawei
 * Date : ������ ���� 28 19:40:40 2018
 ****************************************************************************/

#include "Rte_WdgM_SWC.h"

/*PROTECTED REGION ID(FileHeaderUserDefinedIncludes :WdgMSwc_CheckpointReached_Bsw_20ms) ENABLED START */
/* Start of user defined includes  - Do not remove this comment */
/* End of user defined includes - Do not remove this comment */
/*PROTECTED REGION END */

/*PROTECTED REGION ID(FileHeaderUserDefinedConstants :WdgMSwc_CheckpointReached_Bsw_20ms) ENABLED START */
/* Start of user defined constant definitions - Do not remove this comment */
/* End of user defined constant definitions - Do not remove this comment */
/*PROTECTED REGION END */

/*PROTECTED REGION ID(FileHeaderUserDefinedVariables :WdgMSwc_CheckpointReached_Bsw_20ms) ENABLED START */
/* Start of user variable defintions - Do not remove this comment  */

#define EN_TEST (0x5A5AU)

uint32 wgd_task_asw_5ms_disable;
uint32 wgd_task_bsw_5ms_disable;
uint32 wgd_task_bsw_10ms_disable;
uint32 wgd_task_bsw_20ms_disable;
uint32 wgd_task_bsw_50ms_disable;
uint32 wgd_task_bsw_100ms_disable;
uint32 wgd_task_bsw_1000ms_disable;

/* End of user variable defintions - Do not remove this comment  */
/*PROTECTED REGION END */
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_20ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID1 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_20ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
	if (wgd_task_bsw_20ms_disable == TRUE)
	{
	    return;
	}
	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_20ms_CheckpointReached(CheckpointID1);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_20ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_1000ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID2 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_1000ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_bsw_1000ms_disable == EN_TEST)
    {
        return;
    }

	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_1000ms_CheckpointReached(CheckpointID2);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_1000ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_5ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID3 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_5ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_bsw_5ms_disable == EN_TEST)
    {
        return;
    }
	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_5ms_CheckpointReached(CheckpointID3);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_5ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_50ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID4 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_50ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_bsw_50ms_disable == EN_TEST)
    {
        return;
    }

	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_50ms_CheckpointReached(CheckpointID4);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_50ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Asw_5ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID5 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Asw_5ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_asw_5ms_disable == EN_TEST)
    {
        return;
    }

	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Asw_5ms_CheckpointReached(CheckpointID5);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Asw_5ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_10ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID6 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_10ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_bsw_10ms_disable == EN_TEST)
    {
        return;
    }

	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_10ms_CheckpointReached(CheckpointID6);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_10ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
#define WdgM_SWC_START_SEC_CODE                   
#include "WdgM_SWC_MemMap.h"
FUNC (void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_100ms // return value & FctID 
(
		void
)
{

	WdgM_CheckpointIdType CheckpointID7 = 0;
	Std_ReturnType syncCall1;

	/* Local Data Declaration */

	/*PROTECTED REGION ID(UserVariables :WdgMSwc_CheckpointReached_Bsw_100ms) ENABLED START */
	/* Start of user variable defintions - Do not remove this comment  */
    if (wgd_task_bsw_100ms_disable == EN_TEST)
    {
        return;
    }

	/* End of user variable defintions - Do not remove this comment  */
	/*PROTECTED REGION END */
//	Std_ReturnType retValue = RTE_E_OK;
	/*  -------------------------------------- Data Read -----------------------------------------  */

	/*  -------------------------------------- Server Call Point  --------------------------------  */

	syncCall1 = Rte_Call_RPort_AliveSupervision_Bsw_100ms_CheckpointReached(CheckpointID7);

	/*  -------------------------------------- CDATA ---------------------------------------------  */

	/*  -------------------------------------- Data Write ----------------------------------------  */

	/*  -------------------------------------- Trigger Interface ---------------------------------  */

	/*  -------------------------------------- Mode Management -----------------------------------  */

	/*  -------------------------------------- Port Handling -------------------------------------  */

	/*  -------------------------------------- Exclusive Area ------------------------------------  */

	/*  -------------------------------------- Multiple Instantiation ----------------------------  */

	/*PROTECTED REGION ID(User Logic :WdgMSwc_CheckpointReached_Bsw_100ms) ENABLED START */
	/* Start of user code - Do not remove this comment */
	/* End of user code - Do not remove this comment */
	/*PROTECTED REGION END */

}

#define WdgM_SWC_STOP_SEC_CODE                       
#include "WdgM_SWC_MemMap.h"
