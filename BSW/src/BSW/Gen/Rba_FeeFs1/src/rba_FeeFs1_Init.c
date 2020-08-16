


/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Fee.h"
#include "rba_FeeFs1_Prv.h"

#if (FEE_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
//#include "TestCd_Fee.h"
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/*
 *********************************************************************
 * Global Variables
 *********************************************************************
 */
#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
/* This pointer is used for easy, byte - wise access to the marker buffer */
/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
CONSTP2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) Fee_MarkerBufBytePtr_cpu8 = (uint8*)Fee_llMarkerPageBuf_au32;
/* This pointer is used for easy, byte - wise access to the pagebuffer */
/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
CONSTP2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) Fee_DataBytePtr_cpu8 = (uint8*)Fee_llDataBuf_au32;
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
/* Array containing the sectors that have already been checked completely */
VAR(uint8, FEE_VAR)                     Fee_Prv_stInit_u8        = FEE_PRV_ST_INIT_RUNNING; /* Global init state */
VAR(uint8, FEE_VAR)                     Fee_Prv_stReorg_u8       = FEE_PRV_ST_REORG_IDLE; /* Global reorganization state */
VAR(uint8, FEE_VAR)                     Fee_NumFlashBanksUsed_u8 = FEE_NUM_FLASH_BANKS_AVAILABLE;
                                                                        /* Init number of sectors corresponding
                                                                           to HW availability */

#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_32
#include "Fee_MemMap.h"
VAR(uint32, AUTOMATIC)                  Fee_SecChngCnt_u32 = 0;             /* Fee sector change counter */
#define FEE_STOP_SEC_VAR_INIT_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
/* This pointer is used for easy, byte - wise access to the pagebuffer */
/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) Fee_PageBytePtr_cpu8;

/* Global structure containing states, etc. */
VAR(Fee_RdWrOrder_tst, AUTOMATIC) Fee_RdWrOrder_st;

/* Structure contains sector order (0 is eldest, valid sector) */
VAR(Fee_LLSectorOrder_tst, AUTOMATIC) Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS_AVAILABLE];

/* Information regarding the last block header that was read */
VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) Fee_GlobInfoLastRdHeader_st;
VAR(Fee_LLEraseOrderType_tst, AUTOMATIC)  Fee_LLEraseOrder_st;          /* Global sector erase structure */
VAR(Fee_OrderFifo_tst, AUTOMATIC)       Fee_OrderFifo_st[FEE_QUEUE_SIZE];  /* Fee order queue */
VAR(Fee_LLSecReorgStruct_tst, FEE_VAR)  Fee_LLSecReorgStruct_st;        /* Global sector reorganization structure */
VAR(Fee_GlobInfoWrBlock_tst, FEE_VAR)   Fee_GlobInfoWrBlock_st;         /* Global sector write structure */
VAR(MemIf_JobResultType, AUTOMATIC)     Fee_JobResult[FEE_QUEUE_SIZE];                  /* Fee job result */
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
/* Array containing the index of each sector in the RAM table (fast access) */
VAR(uint8, AUTOMATIC) Fee_idxLLSectorOrder_au8[FEE_NUM_FLASH_BANKS_AVAILABLE];

/* Array containing the sectors that have already been checked completely */
VAR(uint8,  FEE_CONST) Fee_CacheUpdCompForSect_au8[FEE_NUM_FLASH_BANKS_AVAILABLE];
VAR(uint8, FEE_VAR)                     Fee_idxActQueue_u8;             /* Fee queue index */
VAR(uint8, AUTOMATIC)                   Fee_RdWrRetries_u8;             /* Read and write retry amounts */
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"

/* Page buffer, used for reading FEE_LL_PAGEBUFFSIZE/FEE_PAGE_SIZE pages at once.
 * Because access is also done with a struct pointer, the buffer has to be aligned
 * on a 32bit address. */

#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
/* Page buffer, used for reading the sector header. It is possible that
 * a marker has to be written while processing an order with valid
 * data in pagebuffer --> easy solution: use extra buffer for marker handling */
/* MR12 RULE 1504 VIOLATION: This is no function declaration but a variable only with an external linkage */
VAR(uint32, AUTOMATIC) Fee_llMarkerPageBuf_au32[FEE_SEC_HEADER_SIZE / 4u];

/* This array should be located in the ProtRam, if a ProtRam is available */
VAR(uint32, FEE_CONST) Fee_Cache_au32[FEE_NUM_BLOCKS];
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_32_SECURED
#include "Fee_MemMap.h"
VAR(uint32, AUTOMATIC) Fee_llPageBuf_au32[(FEE_LL_PAGEBUFFSIZE / 4u) + 2u];
/* Data buffer used for writing data step by step into the flash */
/* MR12 RULE 1504 VIOLATION: This is no function declaration but a variable only with an external linkage */
VAR(uint32, AUTOMATIC) Fee_llDataBuf_au32[FEE_LL_DATABUFFSIZE / 4u];
#define FEE_STOP_SEC_VAR_CLEARED_32_SECURED
#include "Fee_MemMap.h"

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0))
/* Cache for unknown block sector reorganisation */
#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
VAR(uint32, AUTOMATIC) Fee_UnknownBlkCache_Addr_au32[FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE];   /* Address of unknown block. */
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"
VAR(uint16, AUTOMATIC) Fee_UnknownBlkCache_FeeIndex_u16[FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE]; /* Index of unknown block. */
#define FEE_STOP_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"
#endif

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
VAR(MemIf_StatusType, FEE_VAR)            Fee_GlobModuleState_st   = MEMIF_UNINIT; /* Global module state */
VAR(Fee_stMainType, AUTOMATIC)            Fee_stMain               = FEE_POLLING_MODE_E;                     /* Fee main state */
VAR(Fee_Rb_WorkingStateType_ten, FEE_VAR) Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;       /* Working state of Fee_MainFunction */
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
VAR(uint32, AUTOMATIC)                   Fee_DataByteStartCrc_u32;       /* Start value of the robustness checksum */
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
#endif

#if ((FEE_RB_MAINTAIN != FALSE) && (FEE_NO_FALLBACK_ACTIVE != FALSE))
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_WriteStateNoFb_ten Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_IDLE_E;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"
VAR(uint32, AUTOMATIC)                  Fee_Rb_NoFallback_RemAdr_u32;           /* Address of 2nd copy for double storage */
#define FEE_STOP_SEC_VAR_CLEARED_32
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
VAR(boolean, AUTOMATIC)                 Fee_Rb_NoFallback_LastBlockCfg_b;       /* NoFallback configuration of the last found block */
VAR(boolean, AUTOMATIC)                 Fee_Rb_InvalidateOldCopy_b;             /* Indication to invalidate an old copy */
VAR(boolean, AUTOMATIC)                 Fee_Rb_MaintainRun_b;                   /* Indicate that Maintain is running */
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"

#define FEE_START_SEC_CONST_8
#include "Fee_MemMap.h"
const uint8 Fee_NoFallbackMarkerPattern[FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN] =
{
        0xDE, 0xAD, 0xB1, 0x0C, 0xB1, 0x0C, 0xDE, 0xAD,
        0xDE, 0xAD, 0xB1, 0x0C, 0xB1, 0x0C, 0xDE, 0xAD
};
#define FEE_STOP_SEC_CONST_8
#include "Fee_MemMap.h"
#endif

#if (FEE_PRV_DEBUGGING != FALSE)
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
VAR(Fee_Prv_stModuleTest_tst, AUTOMATIC) Fee_Prv_stModuleTest_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

/* Buffer to hold 2nd header page contents. */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)
#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
VAR(uint8, AUTOMATIC) Fee_hdr2Buffer_au8[FEE_PAGE_LEN] = {0};
#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
#endif

/**
 *********************************************************************
 * Fee_Init(): Initialize the module
 *
 * This function intializes the Fee and has to be called by
 * the operating system once during the Init phase.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
#if (FEE_AR42_API_COMPLIANCE == STD_ON)
/*MR12 RULE 8.13 VIOLATION: AR4.2 defines this function prototype with a non-constant pointer*/
FUNC(void, FEE_CODE) Fee_Init(Fee_ConfigType const * ConfigPtr)
#else
FUNC(void, FEE_CODE) Fee_Init(void)
#endif
{
    VAR(uint8,  AUTOMATIC) xPhySecIdx_u8;       /* Index of physical sector */
    VAR(uint8,  AUTOMATIC) xLogSecIdx_u8;       /* Index of logical sector */
	VAR(uint8,  AUTOMATIC) local_loop_u8;       /* Local loop variable */

    /* Workaround Overstamp invalid header to reduce init time */
    #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
    VAR(uint8, AUTOMATIC) a_u8 = 0;
    #endif
    /* END Workaround Overstamp invalid header to reduce init time */

    #if (FEE_PRV_DEBUGGING != FALSE)
    /* Init max timings */
    VAR(uint32, AUTOMATIC) xIniTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
    VAR(uint32, AUTOMATIC) xIniTimeEnd_u32 = 0;
    VAR(uint32, AUTOMATIC) xIniTimeCacheStart_u32 = 0;
    VAR(uint32, AUTOMATIC) xFindEmptyPageStart_u32 = 0;

    Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiffMax_u32    = 0;
    Fee_Prv_stModuleTest_st.Fee_EraseTimeDiffMax_u32    = 0;
    Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderNum_u32            = 0;
    Fee_Prv_stModuleTest_st.Fee_SearchSpecificBlockHeaderNum_u32        = 0;
    Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderNumReload_u32      = 0;
    Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderLoopRamDiff_u32    = 0;
    Fee_Prv_stModuleTest_st.Fee_DataReadNumBytes_u32    = 0;
    Fee_Prv_stModuleTest_st.Fee_DataReadDiff_u32        = 0;
    Fee_Prv_stModuleTest_st.Eep_InitTimeDiff_u32        = 0;
	Fee_Prv_stModuleTest_st.Fee_CacheInitTime_u32       = 0;
	Fee_Prv_stModuleTest_st.Fee_FindEmptyPageTime_u32   = 0;
	Fee_Prv_stModuleTest_st.Eep_EepRamIniDiff_u32       = 0;
    Fee_Prv_stModuleTest_st.Eep_EnvRamIniDiff_u32       = 0;
    Fee_Prv_stModuleTest_st.Eep_FirstIniDiff_u32        = 0;
    Fee_Prv_stModuleTest_st.Eep_MigrationIniDiff_u32    = 0;
    #endif

    // ignore AR4.2 Config Pointer because Postcompile configuration is not possible
#if (FEE_AR42_API_COMPLIANCE == STD_ON)
    if(ConfigPtr != NULL_PTR){}
#endif

    /* Workaround Overstamp invalid header to reduce init time */
    #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
    for(a_u8 = 0; a_u8 < FEE_PAGE_LEN; a_u8++)
    {
        Fee_hdrBuffer_au8[a_u8] = (uint8)(~FEE_ERASE_PATTERN);
    }
    #endif
    /* END Workaround Overstamp invalid header to reduce init time */

    /* Check if the amount of used sectors needs to be reset */
    if(Fee_LinkedFunctions_cst.Fee_ResetUsedSectors_pfn != NULL_PTR)
    {
        /* Overwrite the amount of used sectors */
        Fee_LinkedFunctions_cst.Fee_ResetUsedSectors_pfn();
    }

    /* Ensure proper 64 Bit alignment of the pointer */
    /* MISRA RULE 11.3 VIOLATION: cast of address required */
    Fee_PageBytePtr_cpu8 = (uint8*)(((uint32)(&Fee_llPageBuf_au32[0]) + 7u) & ~7uL);

    /* Reset the init indicator */
    Fee_Prv_stInit_u8 = FEE_PRV_ST_INIT_RUNNING;

    /* Init Fee internal sector change counter */
    Fee_SecChngCnt_u32 = 0;

    /* Indicate polling mode (no OS scheduling active) */
    Fee_stMain = FEE_POLLING_MODE_E;

    /* Reset job result */
	for (local_loop_u8=0;local_loop_u8<(uint8)FEE_QUEUE_SIZE;local_loop_u8++)
	{
		Fee_JobResult[local_loop_u8] = MEMIF_JOB_OK;
	}

    /* Init the Fee internal working state */
    Fee_Rb_WorkingState_en = FEE_RB_IDLE_E;

    #if ((FEE_RB_MAINTAIN != FALSE) && (FEE_NO_FALLBACK_ACTIVE != FALSE))
    /* Init the internal main write state machine */
    Fee_WriteStateNoFb_en = FEE_WRITE_NOFB_IDLE_E;

    /* Clear the Maintain indication flag */
    Fee_Rb_MaintainRun_b = FALSE;
    #endif

    /* Init Fee internal variables and state machines */
    Fee_InitVarAndState();

    /* Init the Fee cache and its status */
    Fee_InitCache();

    /* Clear the order fifo buffer */
    Fee_InitOrderFifoBuffer();

    /* Detect the most current and eldest sectors (physical and logical index) */
    xPhySecIdx_u8 = Fee_LLDetectActiveSector();

    xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

    #if (!defined(RBA_FLSRH850P1xC_FLASH) && !defined(RBA_FLSV850R1x_FLASH))
    #if (FEE_PRV_DEBUGGING != FALSE)
    xIniTimeCacheStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
    #endif

    #if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
    /* Build up the cache in the correct logical order for all relevant sectors */
    /* MR12 RULE 17.7 VIOLATION: Return value is not required */
    (void)Fee_BuildUpCacheForAllSect();
    #endif

    #if (FEE_PRV_DEBUGGING != FALSE)
    Fee_Prv_stModuleTest_st.Fee_CacheInitTime_u32 =
            MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) - xIniTimeCacheStart_u32);
    #endif
    #endif

    /* Search only within USED sectors for the first empty page */
    if(Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E)
    {

        #if (FEE_PRV_DEBUGGING != FALSE)
        xFindEmptyPageStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
        #endif

        /* Search empty page in most current sector */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Fee_LLFindEmptyPage(xPhySecIdx_u8);

        #if (FEE_PRV_DEBUGGING != FALSE)
        Fee_Prv_stModuleTest_st.Fee_FindEmptyPageTime_u32 = MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) - xFindEmptyPageStart_u32);
        #endif

        /* Update the respective sector index in the array for checked sectors */
        Fee_LLUpdateCacheStForSect(xPhySecIdx_u8);
    }
    else
    {
        /* Sector state is FULL, ERASED, UNDEF or REQUEST2ERASE */

        /* Check for the FULL state */
        if(Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E)
        {
            /* Set the read and write address to the sector end address */
            Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecEndAddress(xPhySecIdx_u8);
        }
        else
        {
            /* Sector state is REQUEST2ERASE, ERASED or UNDEF, mark this for the erase sequence */

            /* Set the read and write address to the sector start address */
            Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecStartAddress(xPhySecIdx_u8);
        }

        /* Take over the read address */
        Fee_RdWrOrder_st.xWrAddress = Fee_RdWrOrder_st.xRdAddress;
    }

    #if (defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH))
    #if (FEE_PRV_DEBUGGING != FALSE)
    xIniTimeCacheStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
    #endif

    /* Build up the cache in the correct logical order for all relevant sectors */
    /* MR12 RULE 17.7 VIOLATION: Return value is not required */
    (void)Fee_BuildUpCacheForAllSect();

    #if (FEE_PRV_DEBUGGING != FALSE)
    Fee_Prv_stModuleTest_st.Fee_CacheInitTime_u32 =
            MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) - xIniTimeCacheStart_u32);
    #endif
    #endif

    /* FEE168:
     * If initialization is finished within Fee_Init, the function Fee_Init shall set the module state from
     * MEMIF_BUSY_INTERNAL to MEMIF_IDLE once initialization has been successfully finished.
     *
     * Note: The FEE module s environment shall not call the function Fee_Init during a running operation of the FEE
     * module. */
    Fee_GlobModuleState_st = MEMIF_IDLE;

    /* Set the global main status to normal mode
     * --> internal or user orders are only processed if the Fee_MainFunction is called
     * by the user (e.g. via scheduling or MemIf) */
    Fee_stMain = FEE_NORMAL_MODE_E;

    /* Set normal mode for reading and writing (ensure maximum Fee speed) */

    #if (FEE_PRV_DEBUGGING != FALSE)
    xIniTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

    Fee_Prv_stModuleTest_st.Fee_InitTimeDiff_u32 =
            MCU_RB_TIM0TICKS_TO_US(xIniTimeEnd_u32 - xIniTimeStart_u32);

    Fee_Prv_stModuleTest_st.Fee_InitTimeDiff_u32 /= 1000u;
    #endif
}


/**
 *********************************************************************
 * Fee_Rb_EndInit(): Allow background services of the module
 *
 * This function indicates the end of the system's init phase and
 * therefore allows the Fee to start erasing any sector if necessary.
 * Also Soft Sector reorganizations are only performed if this function
 * has been called before.
 * This function should be placed when the period of a necessary
 * fast start-up is finished, e.g. after the ECU is ready to accept
 * CAN messages.
 * This function should also be called right after the Fee_Init()
 * function in case the system uses the initialization function
 * inside a power down service (e.g. Shutdown). Otherwise erasing
 * and sector reorganizations will not be formed inside this system
 * state anymore.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_Rb_EndInit(void)
{
    /* Set the init indicator to finished and allow for erase sequences
     * or the soft sector reorganization in the background whenever
     * the Fee is in IDLE mode */
    Fee_Prv_stInit_u8 = FEE_PRV_ST_INIT_DONE;
}


/**
 *********************************************************************
 * Fee_InitVarAndState(): Initialize internal Fee state machines
 *                           and variables
 *
 * This function initializes the module s internal state machines
 * and variables.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_InitVarAndState(void)
{
    VAR(uint8, AUTOMATIC) i_u8;                                         /* loop counter */

    /* Init read / write addresses */
    Fee_RdWrOrder_st.xRdAddress           = FEE_NULL;
    Fee_RdWrOrder_st.xWrAddress           = FEE_NULL;
    Fee_RdWrOrder_st.xCmpAddress          = FEE_NULL;
    Fee_RdWrOrder_st.xCrcAddress          = FEE_NULL;
    Fee_RdWrOrder_st.xCpyAddress          = FEE_NULL;
    Fee_RdWrOrder_st.AdrHdSearchStart_u32 = FEE_MAXUINT32;

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    Fee_RdWrOrder_st.xHdPg2Address = FEE_NULL;
#endif

#if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
    Fee_RdWrOrder_st.LastProgrammedAddress_u32 = FEE_NULL;
    Fee_RdWrOrder_st.LastValidHdrAddress_u32 = FEE_NULL;
#endif

    /* Init state machines of different Fee functions */
    Fee_RdWrOrder_st.Fee_LLSecReorg_en    = FEE_LL_REORG_INIT_E;         /* Fee_LLSectorReorganization */
    Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en = FEE_LL_REDUNDANT_CPY_CHK_INIT_E;    /* Fee_LLRedundantCpyChk */
    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E; /* Fee_LLCpyBlkFromFls2Fls */
    Fee_RdWrOrder_st.Fee_HLWrBlock_en     = FEE_HL_RDWR_BLK_INIT_E;      /* Fee_HLWriteBlock */
    Fee_RdWrOrder_st.Fee_LLWrBlock_en     = FEE_LL_WR_BLK_INIT_E;        /* Fee_LLWriteBlock */
    Fee_RdWrOrder_st.Fee_HLRdBlock        = FEE_HL_RDWR_BLK_INIT_E;      /* Fee_HLReadBlock */
    Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en  = FEE_LL_WR_BLK_INIT_E;   /* Next state after USED-Marker in function
                                                                            Fee_LLWriteBlock */
    Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_BLK_INIT_E;   /* Next state after ERASED-Marker in function
                                                                            Fee_LLWriteBlock */
    Fee_RdWrOrder_st.Fee_LLCompBlk        = FEE_LL_CMP_BLK_INIT_E;       /* Fee_LLCompBlkInFlash */
    Fee_RdWrOrder_st.Fee_LLCopyBlk_en     = FEE_LL_CPY_BLK_INIT_E;       /* Fee_LLCopyData2Buffer */
    Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en  = FEE_LL_CRC_BLK_INIT_E;       /* Fee_LLCalcBlkCrcInFlash */
    Fee_RdWrOrder_st.Fee_LLWrMarker_en    = FEE_LL_MARKER_INIT_E;        /* Fee_LLWriteMarker */
    Fee_RdWrOrder_st.Fee_LLRdState_en     = FEE_LL_INIT_READ_E;          /* Fee_LLSearchSectors / Fee_LLSearchNextBlkHeader */
    Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_INIT_BLANK_CHECK_E;/* Fee_LLCheckErasePattern */
    #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
    Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_INIT_E;   /* Fee_LLFindEmptyPage */
    #else
    Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FIND_CURRENT_SECTOR_E; /* Fee_LLFindEmptyPage */
    #endif
    Fee_RdWrOrder_st.Fee_LLSearchBlkHdr_en = FEE_LL_SEARCHBLK_INIT_E;    /* Fee_LLSearchSpecifiedBlkHeader */
    #if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
    /* Search for an unknown block without cache. */
	#if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)
	Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_INIT_E;    /* Fee_LLSearchUnknownBlkHeader */
	#else
	/* Search of an unknown block using cache */
	Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_INIT_E; /*Fee_BuildUpCacheUnknownBlk */
    Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = FEE_MAXUINT32;
	Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 = 0;
	#endif
	#endif
    #if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
    Fee_RdWrOrder_st.Fee_LLBuildUpCache_en = FEE_LL_BLD_UP_CACHE_INIT_E;                 /* Fee_BuildUpCache */
    Fee_RdWrOrder_st.Fee_LLBuildUpCacheAllSect_en = FEE_LL_BLD_UP_CACHE_ALL_SECT_INIT_E; /* Fee_BuildUpCacheForAllSect */
    #endif

    /* Initialize variables for the erase function */
    Fee_LLEraseOrder_st.EraseState_en    = FEE_ERASESEC_IDLE_E;
    Fee_LLEraseOrder_st.xPhySectorIdx_u8 = FEE_NO_SECTOR_TO_ERASE;

    /* Initialize block header of last read order */
    Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = FEE_NULL;            /* Block header address */
    Fee_GlobInfoLastRdHeader_st.BlkLength_u16    = 0;                   /* Block length */
    Fee_GlobInfoLastRdHeader_st.BlkStatus_u8     = 0;                   /* Block status */
    Fee_GlobInfoLastRdHeader_st.FeeIndex_u16     = 0;                   /* Fee index */
    Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16     = 0,                   /* Crc16 checksum (block header) */
    Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32     = 0;                   /* Crc32 checksum (block data) */

    /* Initialize write block information */
    Fee_GlobInfoWrBlock_st.cntCopies_u8       = FEE_CNT_FIRST_COPY;     /* Retry counter to count number of stored copies */
    Fee_GlobInfoWrBlock_st.cntWriteRetry_u8   = FEE_MAX_RD_WR_COMP_RETRIES;
                                                                        /* Retry counter in case of write errors */
    Fee_GlobInfoWrBlock_st.Bytes2Read_u16     = 0;                      /* Used during sector change to save number
                                                                           of bytes to be read / written */
    Fee_GlobInfoWrBlock_st.CompareResult_u8       = 0;                  /* Result of data compare after writing */
    Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16   = 0;                  /* Data offset in used data */
    Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = 0;                  /* Number of bytes already compared */

    /* Initialization of reorganization information */
    Fee_LLSecReorgStruct_st.xCntCopies_u8            = 0;               /* Count number of copied copies of a block */
    Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 = 0;               /* Count number of copied bytes */
    Fee_LLSecReorgStruct_st.xRdAddress_u32           = FEE_NULL;        /* Read address */
    Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16  = 0;               /* Number of bytes which are handled in next
                                                                           read or write */

    /* Reset queue index */
    Fee_idxActQueue_u8 = (uint8)FEE_QUEUE_SIZE;

	/* Reset retry counter */
	Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

    /* Init sector order array */
   for (i_u8=0; i_u8<FEE_NUM_FLASH_BANKS_AVAILABLE; i_u8++)
   {
       /* Reset all elements inside the strucutre to a defined value */
       Fee_LLSectorOrder_st[i_u8].SecState_en       = FEE_SECTOR_STATE_UNDEF_E;
       Fee_LLSectorOrder_st[i_u8].SecChngCnt_u32    = FEE_SEC_CHANGE_CNT_UNDEF;
       Fee_LLSectorOrder_st[i_u8].xPhySecIdx_u8     = 0xFF;

       /* Reset the physical sector index for all entries */
       Fee_idxLLSectorOrder_au8[i_u8] = 0;
   }
}



/**
 *********************************************************************
 * Fee_InitCache(): Initialize the cache
 *
 * This function initializes the module s cache and the cache status.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_InitCache(void)
{
    VAR(uint16, AUTOMATIC) i_u16;               /* loop counter */

    /* Loop over all configured blocks */
    for (i_u16=0; i_u16<FEE_NUM_BLOCKS; i_u16++)
    {
        /* Init all cache entries */
        Fee_Cache_au32[i_u16] = FEE_CACHE_INIT_VALUE;
    }

    /* Loop over all configured flash banks */
    for (i_u16=0; i_u16<FEE_NUM_FLASH_BANKS_AVAILABLE; i_u16++)
    {
        /* Clear marker for all sectors */
        Fee_CacheUpdCompForSect_au8[i_u16] = FEE_CACHE_UPD_NOT_COMP_FOR_SECT;
    }
}


/**
 *********************************************************************
 * Fee_InitOrderFifoBuffer(): Initialize the Fee interal order fifo
 *                            buffer
 *
 * This function initializes the module s order fifo buffer.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_InitOrderFifoBuffer(void)
{
    VAR(uint16, AUTOMATIC) i_u16;               /* loop counter */

    /* Clear order fifo buffer */
    for (i_u16=0; i_u16<(uint8)FEE_QUEUE_SIZE; i_u16++)
    {
        Fee_OrderFifo_st[i_u16].DataBufferPtr_pu8  = NULL_PTR;
        Fee_OrderFifo_st[i_u16].FeeIdx_u16         = 0x0000;
        Fee_OrderFifo_st[i_u16].Length_u16         = 0;
        Fee_OrderFifo_st[i_u16].Mode_en            = FEE_NO_ORDER;
        Fee_OrderFifo_st[i_u16].SecLevel_u8        = 0;
    }
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif
/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
