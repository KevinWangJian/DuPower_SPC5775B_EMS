

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */
#include "Ea.h"

#if (EA_PRESENT == 1)
/*
 *********************************************************************
 * Includes
 *********************************************************************
 */

#include "Ea_Prv.h"

#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
boolean Ea_Rb_MigChecked_b;
boolean Ea_Rb_MigRunning_b;
boolean Ea_Rb_MigInit_b;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"
MemIf_StatusType          Ea_GlobModuleState_st = MEMIF_UNINIT; /* Global module state */
#define EA_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
    #if (EA_PRV_DEBUGGING != FALSE)
    Ea_Prv_stModuleTest_tst Ea_Prv_stModuleTest_st;
    #endif
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

/**
 *********************************************************************
 * Ea_Init(): Init function of the EA
 *
 * This function initializes the EEPROM abstraction module. It must be called
 * once before the module is used.
 *
 * \param    None
 * \return   None
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
void Ea_Init(void)
{
    uint16 cnt_i;
	/* initialization */

    #if (EA_PRV_DEBUGGING != FALSE)
    uint32  xIniTimeEnd_u32;
    xIniTimeEnd_u32 = 0;

    /* Init max timings */
    Ea_Prv_stModuleTest_st.Ea_DataReadDiff_u32          = 0;
    Ea_Prv_stModuleTest_st.Ea_MigrationTimeStart_u32    = Mcu_Rb_GetSysTimePart(TIM0);
    #endif

	/* Reset Cancel request status */
	Ea_Rb_stCancel_u8 = EA_RB_ST_CANCEL_NOT_REQUESTED;

    /* Set Ea initial state */
    Ea_Rb_stInit_u8 = EA_RB_ST_INIT_RUNNING;
	
	#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
	Ea_Rb_MigrationStaus_u8 = EA_RB_MIGRATION_RUNNING;
	#endif

    /* Initialize the block version for all orders */
    Ea_Rb_BlockHeader_st.BlockVersion_u16 = 0;

    /* Initialize block properties on EEPROM, all the contents will be read during migration initialization */
    for(cnt_i=0; cnt_i<EA_NUM_BLOCKS;cnt_i++)
    {
        Ea_BlockProperties_onEep[cnt_i].BlkStartAddr    = 0;
        Ea_BlockProperties_onEep[cnt_i].BlkEndAddr      = 0;
        Ea_BlockProperties_onEep[cnt_i].BlkRealLen      = 0;
        Ea_BlockProperties_onEep[cnt_i].NvMIdx          = (uint16)EA_INIT_BLK_ID;
        Ea_BlockProperties_onEep[cnt_i].Length          = 0;
        Ea_BlockProperties_onEep[cnt_i].Flags           = 0;
    }

    /* [EA128]:
     * The function Ea_Init shall set the module state to MEMIF_IDLE and the job result to MEMIF_JOB_OK after
     * successful module initialization and before it returns to the caller. */

    /* Reset job result */
    Ea_JobResult = MEMIF_JOB_OK;

    /* Initialize necessary variables for migration */
    Ea_Rb_MigOrder_st.MigOrderType_en   = EA_RB_NO_MIGRATION_E;
    Ea_Rb_MigChecked_b  = FALSE;
    Ea_Rb_MigInit_b 	= TRUE;
	Ea_Rb_MigRunning_b 	= TRUE;

    /* Set the global status to MEMIF_BUSY_INTERNAL if Migration is running
        but the status can be changed due to external read/write order */
    Ea_GlobModuleState_st = MEMIF_BUSY_INTERNAL;

    Ea_Rb_MigCurNr_u16  = 0;
    Ea_Rb_MigClipSrtAdr_u32 = 0;
	Ea_Rb_MigClipBaseSrtAdr_u32 = 0;
	Ea_Rb_MigClipUpdate_b = FALSE;
	Ea_Rb_MigVirginEepromFlag_b = FALSE;
	Ea_Rb_MigNotPossibleFlag_b = FALSE;

    do
    {
        Ea_Rb_MigrationInit();
        Eep_MainFunction();
//        Spi_MainFunction_Handling();
    }while(Ea_Rb_MigInit_b);
	
	#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
	/* In bootmode Migration will not be done and Ea_Init will be exiting with MEMIF_BUSY_INTERNAL state.
	bootmode users said it's difficult to place any request if the Ea_GlobModuleState_st state is MEMIF_BUSY_INTERNAL
	so we are changing it to MEMIF_IDLE */
	if(Ea_GlobModuleState_st == MEMIF_BUSY_INTERNAL)
	{
		Ea_GlobModuleState_st = MEMIF_IDLE;
	}
	#endif
	
    #if (EA_PRV_DEBUGGING != FALSE)
    xIniTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

    Ea_Prv_stModuleTest_st.Ea_InitTimeDiff_u32 =
            MCU_RB_TIM0TICKS_TO_US(xIniTimeEnd_u32 - Ea_Prv_stModuleTest_st.Ea_MigrationTimeStart_u32);
    #endif
}

/**
 *********************************************************************
 * Ea_Rb_EndInit(): Allow background services of the module
 *
 * This function indicates the end of the system's init phase and
 * therefore allows the Ea to start migration if necessary.
 *
 * This function should be placed when the period of a necessary
 * fast start-up is finished, e.g. after calling NvM_ReadAll.
 * This function should also be called right after the Ea_Init()
 * function in case the system uses the initialization function
 * inside a power down service (e.g. Shutdown). Otherwise migration
 * will not be formed inside this system state anymore.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_EndInit(void)
{
    /* Set the init indicator to finished and allow for migration in
     * the background whenever the has no order active */
    Ea_Rb_stInit_u8 = EA_RB_ST_INIT_DONE;
}

#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* #if (EA_PRESENT == 1) */
#endif

 /*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
 </BASDKey>*/

