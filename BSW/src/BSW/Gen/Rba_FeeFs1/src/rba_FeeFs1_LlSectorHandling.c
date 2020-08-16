


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
/* FEE_PRV_DEBUGGING */
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)

#if (FEE_PRV_FREEBYTES_INDFLASH ==TRUE)
/* Added volatile to avoid compiler optimisation*/
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
static volatile Fee_FreeByte_thrshold_t Fee_FreeByte_thr_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
/* Information regarding the 2nd copy of the Redundant block header that was read */
static Fee_GlobInfoLastRdHeader_tst Fee_GlobInfoRedundantRdHeader_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

static Fee_stRetVal_ten Fee_LLRedundantCpyChk(Fee_GlobInfoLastRdHeader_tst * xFee_GlobInfoRedundantRdHeader_pst);

/**
 *********************************************************************
 * Fee_LLCheckReorganizationNeed(): Check the necessity of a sector
 *                                  reorganization
 *
 * This function checks if there is still enough space left in all
 * sectors. Also "empty" sectors are checked because they can also be
 * used. If a sector reorganization is necessary, SECTORFULL will
 * be returned.
 *
 * \param    Threshold_u32:         Amount of bytes must be available
 * \return   Function result
 * \retval   FEE_SECTORFULL_E:      A reorganization is necessary
 * \retval   FEE_ORDER_FINISHED_E:  A reorganization is not necessary
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
 FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCheckReorganizationNeed(VAR(uint32, AUTOMATIC) Threshold_u32,
                                                               VAR(uint16, AUTOMATIC) DataLength_u16)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_SECTORFULL_E;     /* Function return */
    VAR(uint8, AUTOMATIC) xLogSecIdx_u8;                                /* Logical sector index */
    VAR(uint8, AUTOMATIC) xPhySecIdx_u8;                                /* Physical sector index */
    VAR(uint32,AUTOMATIC) xNumFreeBytes_u32;                            /* Amount of free bytes in the current sector */

    /* Calculate the number of free bytes in currently used sector */
    xNumFreeBytes_u32 = Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING);

    /* Check if a reorganization is necessary (only the currently active sector
     * was regarded) */
    if((xNumFreeBytes_u32 > DataLength_u16) &&
      ((xNumFreeBytes_u32 - DataLength_u16) >= Threshold_u32))
    {
        /* The current sector contains more free space than required
         * --> No sector reorganization necessary */
        xRetVal_en = FEE_ORDER_FINISHED_E;
    }
    else
    {
        /* The active sector does not contain enough free space
         * --> check the other sectors */

        /* Get the current logical sector index (sector for current write accesses) */
        xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress)];

        /* Increment the index */
        xLogSecIdx_u8++;

        /* Check for a bank overflow */
        if(xLogSecIdx_u8<FEE_NUM_FLASH_BANKS)
        {
            /* Hint: The logical sector with index 0 is the sector with the eldest data. The logical sector with
             * the index xLogSecIdx_u8 is the write sector and therefor the latest one with the most current
             * data. All logical sectors with an index in between can be used for new data and can be considered
             * as empty. Even if they might be not be erased.
             */

            /* Loop over all configured banks */
            for(;xLogSecIdx_u8<(FEE_NUM_FLASH_BANKS); xLogSecIdx_u8++)
            {
                if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                   (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                {
                    /* The first FULL or USED sector behind the current active sector contains the eldest valid data.
                     * --> skip this sector because only empty sectors are relevant */
                    break;
                }
                else
                {
                    /* The sector state of the current sector is ERASED, ERASEREQUEST or UNDEF
                     * --> get the amount of free bytes in order to find out how many bytes are still available */

                    /* Get the new corresponding physical sector index */
                    xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

                    /* Add the new sector size to the amount of free bytes */
                    xNumFreeBytes_u32 += (Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32 + 1uL) -
                                          Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32;
                }
            }

            /* Now all free sectors were also considered */
            if ((xNumFreeBytes_u32 > DataLength_u16) &&
               ((xNumFreeBytes_u32 - DataLength_u16) >= Threshold_u32))
            {
                /* The current sector contains more free space than required
                 * --> No sector reorganization necessary */
                xRetVal_en = FEE_ORDER_FINISHED_E;
            }
        }
    }
#if (FEE_PRV_FREEBYTES_INDFLASH ==TRUE)
	/* The below part of the code is to calculate the free bytes available in the flash*/
	/* Calculate the number of free bytes in currently used sector */
    xNumFreeBytes_u32 = Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING);

	/* For calculating the number of bytes the remaing sectors i.e is in Erased stated should be considered */

	xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress)];
	/*incriment the sector index for next logical sector*/
	xLogSecIdx_u8++;
	/* Get the current logical sector index (sector for current write accesses) */
	for(;xLogSecIdx_u8<(FEE_NUM_FLASH_BANKS); xLogSecIdx_u8++)
    {
	     /* concider the sector which is only in erased state for the free byte calculation*/
	    if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_ERASED_E))
		{
      		/* Get the new corresponding physical sector index */
            xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;
            /* Add the new sector size to the amount of free bytes */
            xNumFreeBytes_u32 += (Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32 + 1) -
                                          Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32;
		}
	}
	/*load the values in the global varible*/
	Fee_FreeByte_thr_st.Fee_Totalfree_bytes=xNumFreeBytes_u32;
	Fee_FreeByte_thr_st.Fee_hardThreshold=FEE_REQUIRED_FREE_SPACE_BEFORE_HARD_SR;
	Fee_FreeByte_thr_st.Fee_softThershold=FEE_REQUIRED_FREE_SPACE_BEFORE_SOFT_SR;
#endif

    return (xRetVal_en);
}


/**
 *********************************************************************
 * Fee_LLSectorReorganization(): Reorganization function
 *
 * This function performs a sector reorganization. Therefore the eldest
 * sector is checked and blocks which are only located there are
 * written again into the latest sector.
 *
 * Attention: the cache has to be built up completely before
 *            entering the reorganization!
 *
 * \param    SectReorgInterSt_pb:   Will be set to TRUE by the function
 *                                  if the transfer of the next block is
 *                                  currently being prepared (interruptable)
 *                                  Will be set to FALSE by the function
 *                                  in any other cases
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ERROR_E:           An internal error occured
 * \retval   FEE_ORDER_FINISHED_E:  Reorganization finished successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSectorReorganization(P2VAR(boolean, AUTOMATIC, FEE_APPL_DATA) SectReorgInterSt_pb)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en     = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xTmpRetVal_en  = FEE_ORDER_PENDING_E;  /* Temp return */
    VAR(uint8, AUTOMATIC) xLogSecIdx_u8;                                    /* Logical sector index */
    VAR(uint8, AUTOMATIC) xPhySecIdx_u8;                                    /* Physical sector index */
    VAR(uint32, AUTOMATIC)xTmpAddr_u32 = FEE_CACHE_INIT_VALUE;              /* Temporary block address */
    VAR(uint8, AUTOMATIC) xStCache_u8   = 0;                                /* Cache status */
    VAR(boolean, AUTOMATIC) xSectReorgInterSt_b = FALSE;                    /* Interruptability of the reorg */

    static uint32 xAdrBlkHeader_u32;                                        /* Block header address */
    static boolean xSearchRetry_b;                                          /* First try indicator for finding a block */
    static uint16 xBlkIdx_u16;                                              /* Block index */
    static boolean xFee_WriteTwice_b;                                        /* Variable to indicate if block must be written once or twice during Fls2Fls copy operaiton. */

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
    static uint32 xAdrBlkHdAfterbStart_u32;                                 /* "Afterburner" start address */

    /* Search for an unknown block with cache. */
 #if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0)
    static uint16 xUnknownBlkCacheIdx_u16 = FEE_MAXUINT16;                  /* Index for accessing unknown block cache */
    VAR(Fee_BlkHeader_tst, AUTOMATIC) xCurrBlkHeader_st;                    /* Block header structure to extract the header details of unknown block */
 #endif /* (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0) */
#endif /* ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE)) */


    /* Sector reorganization cannot be interrupted by default */
    *SectReorgInterSt_pb = FALSE;

    /* Hints:
     *
     * The driver knows several logical sectors. The eldest one has index 0, the latest one has index X and
     * all sectors between FEE_NUM_FLASH_BANKS and X are currently not used. During the reorganization it
     * is only necessary to check the data within the eldest sector because only this sector will be erased
     * afterwards.
     *
     * Sector order:
     *
     *  +---------------+
     *  |     FULL      |
     *  |      #0 (0)   | <==== Eldest data
     *  |               |
     *  +---------------+   The sector (standard) reorganization is done in the following steps:
     *  |     FULL      |   - Read 1 byte in a block
     *  |      #1       |   - Check if the block header is located in the eldest sector (logical sector 0)
     *  |               |   - If yes, write the block again
     *  +---------------+   - Otherwise search for the next block
     *  |     USED      |
     *  |      #2 (X)   |   The "afterburner" is done in the following steps:
     *  |               |   - Check the eldest sector for blocks which are only located there
     *  +---------------+   - Copy these blocks to the USED sector
     *  |    ERASED     |
     *  |      #3       |
     *  +---------------+
     *  |undef./ReqErase|
     *  |      #4       |
     *  +---------------+ */


	/* Switch over the state machine */
	switch(Fee_RdWrOrder_st.Fee_LLSecReorg_en)
	{
		/* Init state */
		case FEE_LL_REORG_INIT_E:
		{
			/* Set the internal sector reorganization state */
			Fee_Prv_stReorg_u8 = FEE_PRV_ST_REORG_STANDARD_RUNNING;

			/* Reset block index and retry indicator */
			xBlkIdx_u16 = FEE_MAXUINT16;
			xSearchRetry_b = FALSE;

			#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
			/* Get the start address for the "afterburner" */
			xAdrBlkHdAfterbStart_u32 = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32;

			/* Search for an unknown block with cache: Initialise the variables. */
            #if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0)
            xUnknownBlkCacheIdx_u16 = FEE_MAXUINT16;    /* set to -1 */
            Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32;
            #endif
			#endif

			/* Set the next state */
			Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;

			#if (FEE_PRV_DEBUGGING != FALSE)
			Fee_Prv_stModuleTest_st.Fee_ReorgTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM2);
			Fee_Prv_stModuleTest_st.Fee_ReorgCntStart_u32 = 0;
			#endif

			if ((Fee_RdWrOrder_st.xWrAddress>=Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
			    (Fee_RdWrOrder_st.xWrAddress<=Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32)){
	            /* - If the Hard-Reorg-Treshold is in the oldest sector, the Wr-Address could be in the oldest sector, too.
	             * - It is not allowed to start writing/copying of blocks in the oldest sector, because the oldest sector will
	             *   be erased after the sector-reorganisation.
	             * - For this special case, it is necessary to set the write address in the next logical sector.
	             * - Because the if condition is only true if the write address is in the logical[0] sector, the write address has
	             *   to be set at the end of logical[0] sector.
	             **/
			    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32;
			}
		}
		/* No break to save time */

		/* Prepare the next block search */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_REORG_PREP_SEARCH_BLK_E:
		{
			/* This state is only passed after the first function call or for the
			 * first try of finding any of the configured blocks (not if the checksum
			 * of a found block is invalid) */

			/* Increment the block counter in order to find the next block for the transfer */
			xBlkIdx_u16++;

		    /* Initialize block header for redundant block of last read order */
		    Fee_GlobInfoRedundantRdHeader_st.AdrBlkHeader_u32 = FEE_NULL;            /* Block header address */
		    Fee_GlobInfoRedundantRdHeader_st.BlkLength_u16    = 0;                   /* Block length */
		    Fee_GlobInfoRedundantRdHeader_st.BlkStatus_u8     = 0;                   /* Block status */
		    Fee_GlobInfoRedundantRdHeader_st.FeeIndex_u16     = 0;                   /* Fee index */
		    Fee_GlobInfoRedundantRdHeader_st.HdrCrc16_u16     = 0,                   /* Crc16 checksum (block header) */
		    Fee_GlobInfoRedundantRdHeader_st.BlkCrc32_u32     = 0;                   /* Crc32 checksum (block data) */

            /* Default both the copies must be transfered for double security block. */
            xFee_WriteTwice_b = TRUE;

			/* Loop over all configured blocks */
			if (xBlkIdx_u16 >= FEE_NUM_BLOCKS)
			{
				/* All blocks from the layout have been checked now
				 * --> start and execute the "afterburner" for unknown blocks
				 * --> the sector reorganization was finished from block copy point of view
				 * --> the sector arrays and the sector markers have to be updated
				 */

				#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
				/* Check if the oldest FULL sector has been checked completely or not */
				if(xAdrBlkHdAfterbStart_u32 <
				   Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32)
				{
				    /* Search for an unknown block with cache: increment to the next index of the cache. */
                    #if(FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0)
				    xUnknownBlkCacheIdx_u16++;
                    #endif

		            /* Set the internal sector reorganization state */
					Fee_Prv_stReorg_u8 = FEE_PRV_ST_REORG_AFTERB_RUNNING;

					/* Reset the address of the last found block header address for the current block index
					 * (indicate first try for every single block) */
					xAdrBlkHeader_u32 = FEE_MAXUINT32;

					/* Indicate a first try for this block */
					xSearchRetry_b = FALSE;

					/* Start or continue with the search of an unknown block in the oldest FULL sector */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_BLK_E;

					/* Leave this state to reach the finish state in the next call */
					break;
				}
				#endif

				/* Finish the sector reorganization (standard reorganization and the afterburner are finished) */
				Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_FINISHED_E;

				/* Leave this state to reach the finish state in the next call */
				break;
			}

			/* Check if this block has a valid cache entry */
			xTmpAddr_u32 = Fee_LLGetAddressFromCache(Fee_BlockProperties_st[xBlkIdx_u16].BlockPersistentId_u16);

			/* Repeat the check */
			xStCache_u8 = Fee_LLGetCacheUpdateStForAllSect();

			/* Evaluate the cache content and check if all sectors have been checked at least
			 * once until now. Otherwise the cache might not be complete (e.g. sector change in shutdown).
			 * --> Skip the block only in case:
			 *     - all sectors have been checked completely (xStCache_u8 == Complete) and
			 *     - the address out of the cache == FEE_CACHE_INIT_VALUE */
			if((xTmpAddr_u32 != FEE_CACHE_INIT_VALUE) ||
			   (xStCache_u8 == FEE_CACHE_UPD_NOT_COMP_FOR_SECT))
			{
				/* Block is currently (potentially) in the flash, it has to be read out in order to check
				 * its validity and copy it, if necessary (cache entry is re-checked) */

				/* Reset the address of the last found block header address for the current block index
				 * (indicate first try) */
				xAdrBlkHeader_u32 = FEE_MAXUINT32;

				/* Indicate a first try for this block */
				xSearchRetry_b = FALSE;

			    /* Set the next state */
				Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_BLK_E;
			}
			else
			{
				/* Block is currently not in the flash, go on with the next one out of
				 * the configuration */

				/* Do not enter the next state but come here again */
				break;
			}
		}
		/* No break to save time */

		/* Search for a specific block */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_REORG_SEARCH_BLK_E:
		{
			/* Find the latest version of the current block */
			xTmpRetVal_en = Fee_LLSearchSpecifiedBlkHeader(Fee_BlockProperties_st[xBlkIdx_u16].BlockPersistentId_u16,  /* FeeIdx */
														   &xAdrBlkHeader_u32,                         /* End address for the search */
														   &Fee_GlobInfoLastRdHeader_st,                  /* Result structure */
														   xSearchRetry_b);                            /* Indicate first try / retry after a
																										  corrupted checksum of the latest
																										  block version */
			/* Switch over the function return */
			switch (xTmpRetVal_en)
			{
				/* Order not finished yet */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

				/* A valid block header was found */
				case FEE_ORDER_FINISHED_E:
				{
					/* The latest copy with a correct block header of this block was found.
					 * --> Verify the block checksum in order to make sure this is also the latest valid block */

					/* Save the current block header address. If the checksum is incorrect, the function
					 * Fee_LLSearchSpecifiedBlkHeader will try to find older versions only until this
					 * address is reached
					 */
					xAdrBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;

					/* Update the cache (in case of retries due to a former invalid block header search,
					 * the cache should be up to date). Cannot be done inside the function itself, because
					 * this would make the special manual search marker in the cache obsolete which
					 * prevents from invalid cache entries due to write interruptions. Moreover the cache will
					 * be updated for read and write orders only when the block CS is valid. */
					if(xSearchRetry_b != FALSE)
					{
						Fee_LLUpdateAddressInCache(Fee_BlockProperties_st[xBlkIdx_u16].BlockPersistentId_u16,
												   Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32);
					}

					/* Set corresponding state */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_CHECK_BLOCK_CS_E;
				}
				break;

				/* No valid header page was found within the complete flash (all sectors have been checked) */
				case FEE_ERROR_E:
				{
					/* The cache was already invalidated inside the function Fee_LLSearchSpecifiedBlkHeader */

					/* The block is not in the flash and can therefor be skipped, search the next block */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
				}
				break;

				/* The cache is corrupt */
				case FEE_ABORTED_E:
					/* The wrong index was found using the cache. The respective entry was already
					 * marked for a manual search during the sector reorganization.
					 * --> "Manual search" will start automatically in order to find other copies */

					/* Indicate retry */
					xSearchRetry_b = TRUE;
				break;

				/* These cases should never be reached (cannot be returned by Fee_LLSearchSpecifiedBlkHeader) */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_SECTORFULL_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_NUM_RET_VAL_E:
				default:
				{
					/* Mark the block as temporary not available */
					Fee_LLUpdateAddressInCache(Fee_BlockProperties_st[xBlkIdx_u16].BlockPersistentId_u16,
											   FEE_CACHE_TMP_INVALID_VALUE);

					/* Something went wrong, restart from the beginning */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;
				}
				break;
			}
		}
		break;

		/* Evaluate the block checksum */
		case FEE_LL_REORG_CHECK_BLOCK_CS_E:
		{
			/* Read out the complete block and calculate the checksum */
			xTmpRetVal_en = Fee_LLCalcBlkCrcInFlash(&Fee_GlobInfoLastRdHeader_st);

			/* Evaluate the result */
			switch (xTmpRetVal_en)
			{
				/* Order is still pending */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
				}
				break;

				/* Order is finished with success (block CRC is correct) */
				case FEE_ORDER_FINISHED_E:
				{
					/* Get the corresponding physical sector of the eldest logical sector (sector state FULL) */
					xPhySecIdx_u8 = Fee_LLSectorOrder_st[0].xPhySecIdx_u8;

					/* Check if this header was found within the address range of the logical sector 0 */
					if((Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
					   (Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32  < (Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32)))
					{
						/* The latest valid copy of this block is located in the eldest logical sector
						 * --> block might be considered for the reorganization */

						/* Check if this block has to be transfered. This is the case if:
						 * 1. Block is in the layout (standard reorg is active) OR
						 * 2. Block is not in the layout (afterburner is running) AND
						 *      - Survival flag is TRUE (config setting must be taken out of the DFlash) OR
						 *      - FEE_RB_ACT_UNKNOWN_BLOCK_REORG == TRUE (valid for all blocks) */
						if((Fee_Prv_stReorg_u8 == FEE_PRV_ST_REORG_STANDARD_RUNNING) ||
						   ((Fee_Prv_stReorg_u8 == FEE_PRV_ST_REORG_AFTERB_RUNNING) &&
						   (((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_SURV_ATTR_MSK) > 0u) ||
							 (FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE))))
						{
							/* WRITE this block */
							Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_WRITE_BLOCK_E;
						}
						else
						{
							/* Indicate a possible interruption of the sector reorganization */
							xSectReorgInterSt_b = TRUE;

							/* Search for the next block */
							Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
						}
					}
					else
					{
						/* The latest valid copy of this block is not located within the eldest logical sector. */

						/* Perform an additional check for redundant block, to ensure that the 2nd copy is also available outside oldest sector. */
                        if((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_SEC_LEVEL_MSK) != FEE_BLK_INT_DOUBLE_STORAGE)
					    {
					        /* This is a single security block, no more handling required. */
					        /* Indicate a possible interruption of the sector reorganization */
					        xSectReorgInterSt_b = TRUE;

							/* Search for the next block */
					        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
                        }
					    else
					    {
					        /* Search the Redundant copy. */
					        /* Set values in global structure for search. */
					        Fee_GlobInfoRedundantRdHeader_st = Fee_GlobInfoLastRdHeader_st;

					        /* Go to the state to check availability of 2nd copy. */
					        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_REDUNDANT_BLK_CHK_E;
					    }
					}
				}
				break;

				/* The block checksum is incorrect */
				case FEE_ERROR_E:
				{
				    /* Search for an unknown block without cache. */
                    #if(((FEE_RB_ACT_SURVIVAL_EVAL != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_REORG == FALSE)) || ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)))
					/* Check if the "afterburner" is currently active */
					if(Fee_Prv_stReorg_u8 == FEE_PRV_ST_REORG_AFTERB_RUNNING)
					{
						uint8 startSectorAfterburner_u8 , currScannedSector_u8;
					    /* Save the current header address */
						xAdrBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;

						/* Search for later copies of this block (search must be done from
						 * the top to the bottom of the sector for unknown blocks) only
						 * in case the block is still behind the current start address
						 * for unknown blocks */
						startSectorAfterburner_u8  = Fee_GetPhysSectorByAddress(xAdrBlkHdAfterbStart_u32);
						currScannedSector_u8       = Fee_GetPhysSectorByAddress(xAdrBlkHeader_u32);

						/* MR12 RULE 13.5 VIOLATION: Both checks of absolute address and address belonging to same physical sectors is required. */
						if((xAdrBlkHdAfterbStart_u32 >= xAdrBlkHeader_u32) &&
						   (startSectorAfterburner_u8 == currScannedSector_u8))
						{
							/* Go on with the search, because no valid block copy for this persistent ID was found */
							Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_BLK_E;
						}
						else
						{
							/* Retry */
							Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_BLK_E;
							xSearchRetry_b = TRUE;
						}
					}
					else
					#endif
					{
						/* Search for older copies of this block */
						Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_BLK_E;

						/* Workaround Overstamp invalid header to reduce init time */
						#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
						if(E_NOT_OK != Fls_Write(Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32, Fee_hdrBuffer_au8, FEE_PAGE_LEN))
						{
							Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_WAIT_FOR_FLS_E;
						}
						else
						{
						}
						#endif
						/* END Workaround Overstamp invalid header to reduce init time */

						/* A reset of the cache in order to be safe against
						 * any kind of interruptions for the following search
						 * (e.g. Fee_Cancel) was done inside the function already */

						/* Indicate a retry */
						xSearchRetry_b = TRUE;
					}
				}
				break;

				/* These states should never be reached (cannot be returned by Fee_LLCalcBlkCrcInFlash) */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_SECTORFULL_E:
				case FEE_ABORTED_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_NUM_RET_VAL_E:
				default:
				{
					/* The cache was already invalidated inside the function in case of
					 * a standard sector reorganization (no "afterburner"). */

					/* Something went wrong, restart from the beginning */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;
				}
				break;
			}
		}
		break;

		/* Workaround Overstamp invalid header to reduce init time */
		#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))

		/* Wait for the flash to finish the overwrite of an invalid header */
		case FEE_LL_REORG_WAIT_FOR_FLS_E:
		{
			if(Fls_GetJobResult() != MEMIF_JOB_PENDING)
			{
				Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_BLK_E;
			}
		}
		break;

		#endif
		/* END Workaround Overstamp invalid header to reduce init time */

		/* Check if 2nd copy of Redundant block is present in oldest sector or not. */
		case FEE_LL_REORG_REDUNDANT_BLK_CHK_E:
		{
		    xTmpRetVal_en = Fee_LLRedundantCpyChk(&Fee_GlobInfoRedundantRdHeader_st);

            /* Evaluate the function return */
            switch(xTmpRetVal_en)
            {
                /* Order not finished yet */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                    ;
                }
                break;

                /* All copies of the respective block were copied and verified */
                case FEE_ORDER_FINISHED_E:
                {
                    /* Check if 2nd copy is present in the oldest sector. */
                    /* Get the corresponding physical sector of the eldest logical sector (sector state FULL) */
                    xPhySecIdx_u8 = Fee_LLSectorOrder_st[0].xPhySecIdx_u8;

                    /* Check if this header was found within the address range of the logical sector 0 */
                    if((Fee_GlobInfoRedundantRdHeader_st.AdrBlkHeader_u32 >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                       (Fee_GlobInfoRedundantRdHeader_st.AdrBlkHeader_u32  < Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32))
                    {
                        /* Redundant copy exists in the oldest sector. Write the block once. */
                        xFee_WriteTwice_b = FALSE;

						/* Restore the contents of the latest copy to be transfered. */
						Fee_GlobInfoLastRdHeader_st = Fee_GlobInfoRedundantRdHeader_st;

                        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_WRITE_BLOCK_E;
                    }
                    else
                    {
                        /* Redundant copy is present outside the oldest sector, so no more writes required.
                         * Continue with reorg with next block. */
  						/* Indicate a possible interruption of the sector reorganization */
						xSectReorgInterSt_b = TRUE;

						Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
                    }
                }
                break;

                /* An error occured during the search -> there is no second copy. Transfer the copy once. */
                case FEE_ERROR_E:
                {
                    xFee_WriteTwice_b = FALSE;

                    /* Restore the contents of the latest copy to be transfered. */
                    Fee_GlobInfoLastRdHeader_st = Fee_GlobInfoRedundantRdHeader_st;

                    Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_WRITE_BLOCK_E;
                }
                break;

                case FEE_ABORTED_E:
                case FEE_ERASE_SECTOR_E:
                case FEE_SECTORCHANGE_E:
                case FEE_SECTORFULL_E:
                case FEE_BLOCK_INVALIDATED_E:
                case FEE_NUM_RET_VAL_E:
                default:
                {
                    /* Something went wrong, restart from the beginning */
                    Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;
                }
                break;
			}
        }
		break;

		/* Write a block into the latest sector */
		case FEE_LL_REORG_WRITE_BLOCK_E:
		{
			/* Copy the block from the old sector (Fee_GlobInfoLastRdHeader_st->AdrBlkHeader_u32) to the
			 * new sector (Fee_RdWrOrder_st.xWrAddress). If the security level is greater than 1, the
			 * same block (latest valid copy) is copied twice when xFee_WriteTwice_b is set to TRUE. */
			xTmpRetVal_en = Fee_LLCpyBlkFromFls2Fls(&Fee_GlobInfoLastRdHeader_st, xFee_WriteTwice_b);

			/* Evaluate the function return */
			switch(xTmpRetVal_en)
			{
				/* Order not finished yet */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

				/* All copies of the respective block were copied and verified */
				case FEE_ORDER_FINISHED_E:
				{
					/* Indicate a possible interruption of the sector reorganization */
					xSectReorgInterSt_b = TRUE;

					/* Go on with the next block (cache was already updated inside the
					 * function Fee_LLCpyBlkFromFls2Fls, because only the low level
					 * part of the driver has the possibility of a respective reaction
					 * in case of multiple block storages) */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
				}
				break;

				/* An error occured during the read, write or verify sequence */
				case FEE_ERROR_E:
					/* (3 retries for read, write or verify failed in case the orders
					 *  have been accepted by the Fls before)*/
				/* The reorganization was aborted and the USED sector was erased */
				case FEE_ABORTED_E:
					/* Restart the sector reorganization from the beginning using an
					 * erased sector (the cache was already invalidated for all blocks
					 * within the erased sector as well as the the cache status)
					 * Hint: This dead lock preventive action is only effective if
					 *       the size of all blocks that need to be transfered into
					 *       this sector is smaller than the respective sector size */
				/* These states should never be reached (cannot be returned by Fee_LLCpyBlkFromFls2Fls) */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_SECTORFULL_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_NUM_RET_VAL_E:
				default:
				{
					/* Something went wrong, restart from the beginning */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;
				}
				break;
			}
		}
		break;

#if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) || (FEE_RB_ACT_SURVIVAL_EVAL != FALSE))
		/* Search for an unknown block without cache. */
 #if (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)
		case FEE_LL_REORG_SEARCH_UNK_BLK_E:
		{
			/* Search the latest valid copy of the next unknown block header index */
			xTmpRetVal_en = Fee_LLSearchUnknownBlkHeader(&xAdrBlkHdAfterbStart_u32, /* Start address for the search */
														 &xAdrBlkHeader_u32,        /* End address for the search */
														 &Fee_GlobInfoLastRdHeader_st, /* Result structure */
														 &xSearchRetry_b);          /* Indicate first try / retry after a
																					   corrupted checksum of the latest
																					   block version */

			/* Switch over the function return */
			switch (xTmpRetVal_en)
			{
				/* Order not finished yet */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

				/* A valid block header was found */
				case FEE_ORDER_FINISHED_E:
				{
					/* The latest copy with a correct block header of this block was found.
					 * --> Verify the block checksum in order to make sure this is also the latest valid block */

					/* Save the current block header address. If the checksum is incorrect, the function
					 * Fee_LLSearchNextUnknownBlkHeader will try to find older versions only until this
					 * address is reached (end address for the search)
					 */
					xAdrBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;

					/* Set corresponding state */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_CHECK_BLOCK_CS_E;
				}
				break;

				/* No valid unknown header page was found within the eldest FULL sector */
				case FEE_ERROR_E:
				/* The sector end is reached without finding another relevant index */
				case FEE_SECTORFULL_E:
					/* Set the end address for the search */
					xAdrBlkHdAfterbStart_u32 = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32;

					/* Finish the "afterburner" in the next step (the end address of the sector is
					 * set inside the function Fee_LLSearchUnknownBlkHeader) */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
				break;

				/* These cases should never be reached (cannot be returned by Fee_LLSearchSpecifiedBlkHeader) */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_ABORTED_E:
				case FEE_NUM_RET_VAL_E:
				default:
				{
					/* Increment the address to go on with the search of the next block */
					Fee_IncAddressInsideSector(&xAdrBlkHdAfterbStart_u32, FEE_PAGE_LEN, TRUE);

					/* Something went wrong, restart from the beginning */
					Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;
				}
				break;
			}
		}
		break;
 #else /* Search for an unknown block with cache. */
		case FEE_LL_REORG_SEARCH_UNK_BLK_E:
		{
		    /* Check if there are entries in cache. */
		    if(xUnknownBlkCacheIdx_u16 < Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16)
		   {
	            /* The unknown block details is present in the cache.
	             * Also, the cache address points to a valid header and valid data.
	             * Scan the cache and transfer all the blocks that have address within the oldest sector. */
	           /* Read the unknown block header to extract the block properties details. */
		           /* Extract header details for read */
		           Fee_RdWrOrder_st.xRdAddress = Fee_UnknownBlkCache_Addr_au32[xUnknownBlkCacheIdx_u16];

		           if (Fls_Read(Fee_RdWrOrder_st.xRdAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], (FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN)) != E_NOT_OK)
		           {
		               /* Read request is accepted, go to wait state to check the order status */
		               Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_HDRBLK_WAIT_E;
		           }
		           else
		           {
		               /* This error can come only for wrong parameter, development errors */
		               xRetVal_en = FEE_ERROR_E;
		           }
	       }
		   else
		   {
		       /* All unknown blocks present in the cache has been transfered. Check if there is more area to be scanned in the oldest sector.
		        * if yes, build the cache over the remaining area.*/
		       if(Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 < Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32)
               {
		           /* Cache has to be built for remaining area of the sector */
		           Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_CACHEBUILDUP_UNK_BLK_E;

		           /* Clear the index */
		           xUnknownBlkCacheIdx_u16 = 0;
		       }
		       else
		       {
		           /* The oldest sector has been scanned and all unknown blocks are transfered. End the sector change operation */
		           /* Set the end address for the search */
		           xAdrBlkHdAfterbStart_u32 = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32;

		           /* Finish the "afterburner" in the next step (the end address of the sector is set inside the function Fee_LLSearchUnknownBlkHeader) */
		           Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_PREP_SEARCH_BLK_E;
		       }
		   }
		}
		break;

		/* Build cache for unkown block */
		case FEE_LL_REORG_CACHEBUILDUP_UNK_BLK_E:
		{
		    if(Fee_BuildUpCacheUnknownBlk() != FEE_ORDER_PENDING_E)
		    {
		        /* Cache build up is complete. Switch to FEE_LL_REORG_SEARCH_UNK_BLK_E state and transfer the blocks.*/
		        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_BLK_E;
		    }
		    else
		    {
		        /* Cache building is ongoing. Do nothing, wait till complete cache is built */
		    }
		}break;

		/* Wait state for the header read order of unknown block */
		case FEE_LL_REORG_SEARCH_UNK_HDRBLK_WAIT_E:
		{
            /* The next state will be set by the Fee_JobEndNotification () or
             * Fee_JobErrorNotification() function automatically */

            /* Call the Fls main function manually */
            Fls_MainFunction();

            #if (STD_ON == FEE_POLLING_MODE)
            /* Use the FLS polling mechanism in order to reach the next state */
            Fee_CheckFlsJobResult();
            #endif
		}break;

        /* Error while reading the header */
        case FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_ERROR_E:
        {
            /* Ideally, this state cant be reached, since the header was validated during cache build up.
             * It may come here due to hardware error or CACHE corruption. Retry again starting from FEE_LL_REORG_SEARCH_UNK_BLK_E. */
            Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_BLK_E;
        }break;

        /* Header read successful */
        case FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_FINISHED_E:
        {
            /* Prepare header details for transfer */
            /* Read address and Fee index can be taken from the cache */
            Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = Fee_UnknownBlkCache_Addr_au32[xUnknownBlkCacheIdx_u16];            /* Block header address */
            Fee_GlobInfoLastRdHeader_st.FeeIndex_u16     = Fee_UnknownBlkCache_FeeIndex_u16[xUnknownBlkCacheIdx_u16];  /* Fee index */

            /* Extract the other information of the header */
            Fee_LLCopyPageBuff2HeaderMid(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[0]);
            Fee_LLCopyPageBuff2HeaderEnd(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[0]);

            Fee_GlobInfoLastRdHeader_st.BlkLength_u16    = xCurrBlkHeader_st.BlkLength_u16; /* Block length */
            Fee_GlobInfoLastRdHeader_st.BlkStatus_u8     = xCurrBlkHeader_st.BlkStatus_u8;  /* Block status */
            Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16     = xCurrBlkHeader_st.HdrCrc16_u16,  /* Crc16 checksum (block header) */
            Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32     = xCurrBlkHeader_st.BlkCrc32_u32;  /* Crc32 checksum (block data) */

            /* Check if the latest copy of the unkown block is in the oldest sector (logical sector 0). */
            if((Fee_UnknownBlkCache_Addr_au32[xUnknownBlkCacheIdx_u16] >= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
               (Fee_UnknownBlkCache_Addr_au32[xUnknownBlkCacheIdx_u16]  < Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
            {
                /* Latest copy is present in the oldest sector, transfer the block (redundant blocks will be transfered twice as xFee_WriteTwice_b is set to TRUE in init state). */
                Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_WRITE_BLOCK_E;
            }
            else
            {
                /* The latest copy of the unknown block is present outside the oldest sector. */
                /* Perform an additional check for redundant block, to ensure that the 2nd copy is also available outside oldest sector. */
                if((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_SEC_LEVEL_MSK) != FEE_BLK_INT_DOUBLE_STORAGE)
                {
                    /* This is a single security block, no more handling required. */
                    xUnknownBlkCacheIdx_u16++;

                    /* Return to state FEE_LL_REORG_SEARCH_UNK_BLK_E to check if futher entries in cache are available. */
                    Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_BLK_E;
                }
                else
                {
                    /* Set values in global structure for search. */
					Fee_GlobInfoRedundantRdHeader_st = Fee_GlobInfoLastRdHeader_st;

					/* Go to the state to check availability of 2nd copy. */
                    Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_REDUNDANT_BLK_CHK_E;
                }
            }
        }break;
#endif /* End of (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0) */
#endif /* End of ((FEE_RB_ACT_SURVIVAL_EVAL != FALSE) || (FEE_RB_ACT_UNKNOWN_BLOCK_REORG == FALSE)) */
		/* Function finished */
		case FEE_LL_REORG_FINISHED_E:
		{
			/* The sector reorganization is almost finished. The following steps have to be done:
			 * - Write the "ERASE REQUEST" marker into the sector that needs to get erased
			 * - Reorganize the sector order structure
			 */

			/* Get the physical sector index of the eldest logical sector */
			xPhySecIdx_u8 = Fee_LLSectorOrder_st[0].xPhySecIdx_u8;

			/* Write the erase request marker */
			if(Fee_LLWriteMarker(xPhySecIdx_u8, FEE_ERASE_REQUEST_ID_E) != FEE_ORDER_PENDING_E)
			{
				/* Error reaction not necessary (no free space available in the marker section
				 * or read or write error in the marker section)
				 * --> RAM structure will be set and used for the detection of a necessary erase
				 *     procedure as long as the Fee_Init is not passed again.
				 * --> If init is passed, the sector detection will recognize this sector as
				 *     the oldest one and execute an erase because the threshold for the sector
				 *     reorganization is passed automatically. */

				/* Loop over all sectors and reorganize the sector order:
				 * - The previous 1st sector is now the eldest one (the logical index 0)
				 * - The previous 2nd sector is now the 1st sector, ...
				 */
				for(xLogSecIdx_u8=0; xLogSecIdx_u8<(FEE_NUM_FLASH_BANKS-1); xLogSecIdx_u8++)
				{
					/* Reorganize the sector order */
					Fee_LLSectorOrder_st[xLogSecIdx_u8] = Fee_LLSectorOrder_st[xLogSecIdx_u8+1];

					/* Reorganize the array Ram table */
					Fee_idxLLSectorOrder_au8[Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8] = xLogSecIdx_u8;
				}

				/* Update the state information of the last sector in the ring */
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].SecState_en     = FEE_SECTOR_REQUEST2ERASE_E;
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].xPhySecIdx_u8   = xPhySecIdx_u8;
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].SecChngCnt_u32  = FEE_SEC_CHANGE_CNT_UNDEF;

				Fee_idxLLSectorOrder_au8[xPhySecIdx_u8] = FEE_NUM_FLASH_BANKS-1;

				/* Sector reorganization is completely finished */
				xRetVal_en = FEE_ORDER_FINISHED_E;
			}

			/* Hint: forcing an erase sequence immediately in case the erase request marker cannot be
			 *       written might lead to an erase sequence in the shutdown phase
			 *       --> restarting the sector reorganization in the next driving cycle is better
			 *           (which will be done automatically in case the eldest sector is not erased) */

		}
		break;

		/* This state should never be reached */
		default:
		{
			/* Set the error return */
			xRetVal_en = FEE_ERROR_E;
		}
		break;
	}


    /* Take over the local value for the interruptability of the sector reorganization */
    *SectReorgInterSt_pb = xSectReorgInterSt_b;

    /* Evaluate the result of the function returns */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Set the internal sector reorganization state */
        Fee_Prv_stReorg_u8 = FEE_PRV_ST_REORG_IDLE;

        /* Reset the state machine */
        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_INIT_E;

        /* Reset start search indicator */
        xSearchRetry_b = FALSE;

        #if (FEE_PRV_DEBUGGING != FALSE)
        Fee_Prv_stModuleTest_st.Fee_ReorgTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM2);

        /* MISRA RULE 10.8 VIOLATION: Below type cast is ok as this is only for testing purpose to measure the time. */
        Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiff_u32 = (uint32)MCU_RB_TIM2TICKS_TO_MS(
                Fee_Prv_stModuleTest_st.Fee_ReorgTimeEnd_u32 -
                Fee_Prv_stModuleTest_st.Fee_ReorgTimeStart_u32);

        if(Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiff_u32 >
           Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiffMax_u32)
        {
            Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiffMax_u32 =
                    Fee_Prv_stModuleTest_st.Fee_ReorgTimeDiff_u32;
        }

        /* Update max time for sector reorg */
        if (Fee_Prv_stModuleTest_st.Fee_ReorgCntStart_u32 > Fee_Prv_stModuleTest_st.Fee_ReorgCntDiffMax_u32)
        {
            Fee_Prv_stModuleTest_st.Fee_ReorgCntDiffMax_u32 = Fee_Prv_stModuleTest_st.Fee_ReorgCntStart_u32;
        }
        #endif
    }
    #if (FEE_PRV_DEBUGGING != FALSE)
    else
    {
        /* Increment the count call counter */
        Fee_Prv_stModuleTest_st.Fee_ReorgCntStart_u32++;
    }
    #endif

    return (xRetVal_en);
}

/**
 *********************************************************************
 * Fee_LLRedundantCpyChk():
 *
 * This function searches the 2nd copy of redundnat block (both unknown and known blocks).
 * It checks for both header and data validity.
 *
 * Attention: the search is without cache!
 *
 * \param    xFee_GlobInfoRedundantRdHeader_pst: Details of the block that must searched.
 *                                  The address of the valid block is returned in xFee_GlobInfoRedundantRdHeader_pst.AdrBlkHeader_u32
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ERROR_E:           An internal error occured
 * \retval   FEE_ORDER_FINISHED_E:  Block search finished successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
static Fee_stRetVal_ten Fee_LLRedundantCpyChk(Fee_GlobInfoLastRdHeader_tst * xFee_GlobInfoRedundantRdHeader_pst)
{
    Fee_stRetVal_ten    xRetVal_en              = FEE_ORDER_PENDING_E;  /* Function return */
    Fee_stRetVal_ten    xTmpRetVal_en           = FEE_ORDER_PENDING_E;  /* Return value from called functions */
    static uint16       xFeeIndex_u16;                                  /* Fee index which is required to be searched. */
    static uint32       xAdrLastBlkHeader_u32;                          /* Address for limit the search */
    static uint32       xAdrFirstBlkHeader_u32;                         /* Address of the first copy, required to restore cache contents at the end. */

    switch (Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en)
    {
        /* Init state */
        case FEE_LL_REDUNDANT_CPY_CHK_INIT_E:
        {
            /* Copy the Fee index into local static variable that must be searched again. */
            xFeeIndex_u16 = xFee_GlobInfoRedundantRdHeader_pst->FeeIndex_u16;

            /* Copy the address of the first copy to restore the cache contents later. */
            xAdrFirstBlkHeader_u32 = xFee_GlobInfoRedundantRdHeader_pst->AdrBlkHeader_u32;

            /* Limit the address for search. */
            xAdrLastBlkHeader_u32 = xFee_GlobInfoRedundantRdHeader_pst->AdrBlkHeader_u32;

            /* Go to next state to search the header. */
            Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en = FEE_LL_REDUNDANT_CPY_CHK_SEARCH_HDR_E;
        }
        break;

        /* Search header of redundant copy */
        case FEE_LL_REDUNDANT_CPY_CHK_SEARCH_HDR_E:
        {
            /* Search for the redundant block header with the given FeeIdx.
             * The end address for the search is set with the variable xAdrLastBlkHeader_u32. */
            xTmpRetVal_en = Fee_LLSearchSpecifiedBlkHeader(xFeeIndex_u16,                               /* FeeIdx */
                                                           &xAdrLastBlkHeader_u32,                      /* End address for the search */
                                                           xFee_GlobInfoRedundantRdHeader_pst,           /* Result structure */
                                                           TRUE);                                       /* Indicate always a retry */

            /* Evaluate the search result */
            switch (xTmpRetVal_en)
            {
                /* Order not finished yet */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                    ;
                }
                break;

                /* A valid block header was found */
                case FEE_ORDER_FINISHED_E:
                {
                    /* Calculate block checksum in flash to check if the block is valid */
                    Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en = FEE_LL_REDUNDANT_CPY_CHK_BLK_CS_E;
                }
                break;

                case FEE_ERROR_E:
                {
                    /* No valid header was found within the complete flash (all sectors have been checked)
                     * Return ERROR and this will trigger write of the block. */
                    /* The fee index was updated to 0xFFFF as no copy was found, restore it to the correct value. */
                    xFee_GlobInfoRedundantRdHeader_pst->FeeIndex_u16 = xFeeIndex_u16;

                    xRetVal_en = FEE_ERROR_E;
                }
                break;

                /* These cases should never be reached here (cannot be returned by Fee_LLSearchSpecifiedBlkHeader) */
                case FEE_ABORTED_E:
                case FEE_BLOCK_INVALIDATED_E:
                case FEE_NUM_RET_VAL_E:
                case FEE_ERASE_SECTOR_E:
                case FEE_SECTORCHANGE_E:
                case FEE_SECTORFULL_E:
                default:
                {
                    /* The fee index was updated to 0xFFFF as no copy was found, restore it to the correct value. */
                    xFee_GlobInfoRedundantRdHeader_pst->FeeIndex_u16 = xFeeIndex_u16;

                    /* Return an error */
                    xRetVal_en = FEE_ABORTED_E;
                }
                break;
            }
        }
        break;

        /* Validate data CRC of redundant copy */
        case FEE_LL_REDUNDANT_CPY_CHK_BLK_CS_E:
        {
            /* Calculate the block CRC */
            xTmpRetVal_en = Fee_LLCalcBlkCrcInFlash(xFee_GlobInfoRedundantRdHeader_pst);

            /* Evaluate the result */
            switch (xTmpRetVal_en)
            {
                /* Order is still pending */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                }
                break;

                /* Order is finished with success (block CRC is correct) */
                case FEE_ORDER_FINISHED_E:
                {
                    /* Redundant copy was found, return success to upper layer. */
                    xRetVal_en = FEE_ORDER_FINISHED_E;
                }
                break;

                /* The checksum is invalid (block CRC is incorrect) or a read error occurred */
                case FEE_ERROR_E:
                {
                    /* Error during CRC detected -> search further */
                    /* Limit the address to search to avoid revalidating the same block again. */
                    xAdrLastBlkHeader_u32 = xFee_GlobInfoRedundantRdHeader_pst->AdrBlkHeader_u32;

                    /* Search for an older copy */
                    Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en = FEE_LL_REDUNDANT_CPY_CHK_SEARCH_HDR_E;
                }
                break;

                /* These states should never be reached (cannot be returned by Fee_LLCalcBlkCrcInFlash) */
                case FEE_BLOCK_INVALIDATED_E:
                case FEE_NUM_RET_VAL_E:
                case FEE_ERASE_SECTOR_E:
                case FEE_SECTORCHANGE_E:
                case FEE_SECTORFULL_E:
                case FEE_ABORTED_E:
                default:
                {
                    /* Return an error */
                    xRetVal_en = FEE_ABORTED_E;
                }
                break;
            }
        }
        break;

        default:
        {
            /* Return an error */
            xRetVal_en = FEE_ABORTED_E;
        }
        break;
    }

    /* Reset state machine if necessary */
    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_LLRedundantCpyChk_en = FEE_LL_REDUNDANT_CPY_CHK_INIT_E;

        /* The cache could have been updated with the address of the second valid version or invalidated if block was not found.
         * As safety, restore the cache with the address of the latest copy */
        Fee_LLUpdateAddressInCache(xFeeIndex_u16, xAdrFirstBlkHeader_u32);
    }

    return (xRetVal_en);
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_PRESENT */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
