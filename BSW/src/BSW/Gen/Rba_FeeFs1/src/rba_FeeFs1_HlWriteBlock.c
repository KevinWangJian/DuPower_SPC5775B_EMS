


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
#include "Crc.h"
#if (!defined(CRC_AR_RELEASE_MAJOR_VERSION) || (CRC_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CRC_AR_RELEASE_MINOR_VERSION) || ((CRC_AR_RELEASE_MINOR_VERSION != 0) && (CRC_AR_RELEASE_MINOR_VERSION != 2)))
    #error "AUTOSAR minor version undefined or mismatched"
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_HLWriteBlock(): Write a block into a sector
 *
 * This function is used to write a block into the memory media or
 * to invalidate a block (write only the block header with a
 * block length of zero).
 *
 * The block is being searched in all the sectors due to the verification
 * whether a write is necessary or not (data identical and checksum
 * in the flash still correct). After a successfull write operation
 * the data is being compared automcatically.
 *
 * \param    none
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Block write caused an error
 *                                  (3 retries failed)
 * \retval   FEE_SECTORFULL_E:      The write order cannot be executed
 *                                  because the HSR threshold will be
 *                                  exceeded
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully or
 *                                  write order not necessary
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLWriteBlock(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xtmpRetVal_en;                     /* Temp return */
    VAR(uint16, AUTOMATIC)           xNumBytes_u16 = 0;                 /* Number of bytes */
    static uint32		             xAdrLastBlkHeader_u32; 			/* Block header address */
    static uint16  xBlkLength_u16;                						/* Block length */
    static uint32  xNumCrcBytesConsid_u16;                              /* Number of bytes which were already considered */
    static uint32  xBlkCrc_u32;                                         /* Block CRC value */
    static boolean xSearchRetry_b;                                      /* First try indicator for finding a block */


	/* Switch over function state machine */
	switch (Fee_RdWrOrder_st.Fee_HLWrBlock_en)
	{
		/* Init state */
		case FEE_HL_RDWR_BLK_INIT_E:
		{
			/* Init last block header address */
			xAdrLastBlkHeader_u32 = FEE_MAXUINT32;

			/* Extract the required information from the configuration table */
			Fee_GlobInfoLastRdHeader_st.FeeIndex_u16  =
					Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].BlockPersistentId_u16;
			Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
					Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
			Fee_GlobInfoLastRdHeader_st.BlkStatus_u8  =
					(uint8)(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & 0xFFu);

			Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32   = FEE_MAXUINT32;
			Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32       = 0;
			Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16       = 0;

			/* Init the block CRC and amount of Crc bytes that have already been considered */
			xBlkCrc_u32 = 0;
			xNumCrcBytesConsid_u16 = 0;
			xBlkLength_u16 = 0;

			/* Reset start search indicator */
			xSearchRetry_b = FALSE;

			#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
			/* Reset the fall back indicator */
			Fee_Rb_NoFallback_RemAdr_u32 = FEE_MAXUINT32;
			Fee_Rb_NoFallback_LastBlockCfg_b = FALSE;
			#endif

			/* Set next state */
			Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_SEARCH_BLK_HDR_E;
		}
		/* No break to save time */

		/* Search for a block header */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_HL_SEARCH_BLK_HDR_E:
		{
			/* Search next block header of FeeBlock with given FeeIdx_u16.
			 * Start address for the search can be set with variable xAdrLastBlkHeader_u32.
			 * If the sector should be read from the beginning, FEE_NULL has to be taken.
			 */
			/* Search for the latest valid block header within all sectors */
			xtmpRetVal_en = Fee_LLSearchSpecifiedBlkHeader(Fee_OrderFifo_st[Fee_idxActQueue_u8].FeeIdx_u16,   /* FeeIdx */
														   &xAdrLastBlkHeader_u32,                  /* End address for the search */
														   &Fee_GlobInfoLastRdHeader_st,               /* Result structure */
														   xSearchRetry_b);                         /* Indicate first try */
			/* Evaluate the search result */
			switch(xtmpRetVal_en)
			{
				/* Search is still pending */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

                    /* A block header was found in the DFlash */
                case FEE_ORDER_FINISHED_E:
                {
                    /* Possible cases:
                     * 1. block in data flash is invalid
                     * 2. block in data flash is identical to what the user wants to write
                     * 3. block in data flash is different
                     *
                     * Due to the fact that there is only block write access possible, it is not necessary
                     * to verify the block content in the data flash but the checksum only. If both
                     * checksums are identical, it is not necessary to write the block again.
                     * Also in case the block is already invalidated it is not necessary to execute
                     * an invalidation order again. */

                    /* Check if an invalidation order is active or the block was invalidated in
                     * the flash before */
                    if (((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8) FEE_FLAG_INVALID_MSK) > 0) ||
                             (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER))
                    {
                        /* Check if a write without a compare can be performed */
                        if (((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8) FEE_FLAG_INVALID_MSK) > 0) &&
                                 (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER))
                        {
                            /* A block which is already invalidated should not be invalidated
                             * again (redundant)
                             * --> leave the function */

                            /* Finish this function */
                            xRetVal_en = FEE_ORDER_FINISHED_E;

                            break;
                        }
                        else
                        {
                            /* The block was either invalidated before and now a regular write order
                             * is requested or this is an invalidation order for a block which was
                             * not invalidated before */

                            /* Due to a former invalidation, the block length was set to 0.
                             * Reset the block length */
                            Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
                                    Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
                        }
                    }
                    else
                    {
                        /* The block header was found and this is a regular write order of a non-invalidated block
                         * --> just calculate the checksum over the user data (state is set below) */
                        ;
                    }

                    /* Check if the current order is an invalidation order */
                    if (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER)
                    {
                        /* Set the corresponding flag in block status */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= (uint8) FEE_FLAG_INVALID_MSK;

                        /* Set the block length to zero (only save the block header, data is not necessary. Save flash) */
                        Fee_GlobInfoLastRdHeader_st.BlkLength_u16 = 0;
                    }
                    else
                    {
                        /* For write orders reset the invalidation bit */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 &= ~ FEE_FLAG_INVALID_MSK;
                    }


					#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                    /* In case of a Layout change (e.g. NoFallback is now set to TRUE for a specific block)
                     * -> remember the configuration of the found block to avoid a writing of the NoFallback marker */
                    if ((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_NOFALLBACK_MSK) > 0u)
                    {
                        /* An old copy of the block was found with NoFallback = TRUE
                         * -> This copy must be invalidated by writing the NoFallback marker */
                        Fee_Rb_NoFallback_LastBlockCfg_b = TRUE;
                    }
                    else
                    {
                        /* An old copy of the block was found with NoFallback = FALSE
                         * -> Prevent a write of the NoFallback marker since there is no area reserved for that block */
                        Fee_Rb_NoFallback_LastBlockCfg_b = FALSE;
                    }

                    /* Since the status flags are overwritten with the flags from the last found block (by Fee_LLSearchSpecifiedBlkHeader())
                     * --> reset the the NoFallback configuration according to the BlockProperties */
                    if((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
                    {
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= FEE_FLAG_NOFALLBACK_MSK;
                    }
                    else
                    {
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 &= (uint8)~FEE_FLAG_NOFALLBACK_MSK;
                    }
                    #endif

                    /* Initialize the page buffer */
                    Fee_SrvMemSet8((uint8*) &Fee_PageBytePtr_cpu8[0], (uint8) FEE_ERASE_PATTERN, FEE_LL_PAGEBUFFSIZE);

                    /* While searching the block, the flag was overwritten from DFLASH values. Restore the values for Security level, Survival and Robustness flags.
                     * Remaining flags are already handled correctly. */
                    if((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_SEC_LEVEL_MSK) > 0u)
                    {
                        /* Double security block, set bit 0. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= FEE_FLAG_SEC_LEVEL_MSK;
                    }
                    else
                    {
                        /* Single security block, clear bit 0. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 &= (uint8)~FEE_FLAG_SEC_LEVEL_MSK;
                    }

                    if((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_SURV_ATTR_MSK) > 0u)
                    {
                        /* Surivival feature enabled. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= FEE_FLAG_SURV_ATTR_MSK;
                    }
                    else
                    {
                        /* Survival feature disabled. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 &= (uint8)~FEE_FLAG_SURV_ATTR_MSK;
                    }

                    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
                    if((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & (uint16)FEE_FLAG_ROBUST_ATTR_MSK) > 0u)
                    {
                        /* Surivival feature enabled. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= (uint8)FEE_FLAG_ROBUST_ATTR_MSK;

                        if(FEE_INVALIDATE_ORDER != Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en)
                        {
                            /* It may happen that the read block in DFLASH block is 4 bytes lesser (because the block was previously disabled),
                             * restore the block lenght as per the actual length. */
                            Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
                                    Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
                        }

                    }
                    else
                    {
                        /* Survival feature disabled. */
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 &= (uint8)~(uint8)FEE_FLAG_ROBUST_ATTR_MSK;
                    }
                    #endif

                    /* Calculate the header CRC */
                    Fee_LLPrepPageBufWithHdrDataStart(&Fee_GlobInfoLastRdHeader_st);

                    /* Set the start value for the block CRC calculation */
                    xBlkCrc_u32 = ((uint32)Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16) ^ FEE_MAXUINT32;

                    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
                    /* Set the block length depending on the robustness configuration */
                    if ((((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                    		(uint16) FEE_FLAG_ROBUST_ATTR_MSK) >> (uint16) FEE_FLAG_ROBUST_ATTR_BP) > 0) &&
                    		((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8) FEE_FLAG_INVALID_MSK) == 0u))
                    {
                        /* Set the block length for the checksum calculation */
                        xBlkLength_u16 = Fee_GlobInfoLastRdHeader_st.BlkLength_u16 - FEE_SIZE_OF_BLOCK_CS;
                    }
                    else
                    #endif
                    {
                        /* Set the block length for the checksum calculation */
                        xBlkLength_u16 = Fee_GlobInfoLastRdHeader_st.BlkLength_u16;
                    }

                    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                    /* Check if the search for the first copy is necessary or not. This is the case if:
                     * - the NoFallback feature is active for this block and
                     * - the block is a double storage block and
                     * - the second copy has been found already */
                    // Shift of the block properties' flag SEC LEVEL is not necessary here, because the offset is 0
                    if (((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16
                            & FEE_FLAG_NOFALLBACK_MSK) > 0u)
                            && ((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8) FEE_FLAG_SEC_LEVEL_MSK)
                                    == FEE_BLK_INT_DOUBLE_STORAGE)
                            && (Fee_Rb_NoFallback_RemAdr_u32 == FEE_MAXUINT32))
                    {
                        /* Search for the first copy of this block */

                        /* Save the address of the 2nd copy */
                        Fee_Rb_NoFallback_RemAdr_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;

                        /* Save the upper limit for the search */
                        xAdrLastBlkHeader_u32 = Fee_Rb_NoFallback_RemAdr_u32;

                        /* Indicate a retry */
                        xSearchRetry_b = TRUE;
                    }
                    else
                    /* #if (FEE_NO_FALLBACK_ACTIVE != FALSE) */
                    #endif
                    {
                        /* NoFallback feature is deactivated for this block or
                         * both copies of a double storage block have been found already,
                         * go on with the block checksum calculation over the user data
                         */

                        /* Calculate the checksum over the user data */
                        Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_CALC_BLK_CS_E;
                    }
                }
                    break;

				/* The block doesn't exist in any of the sectors */
				case FEE_ERROR_E:
				{
					/* Block can be written immediately without any compare
					 * to the next free address in the active sector */

					/* Extract the required information from the configuration table */
					Fee_GlobInfoLastRdHeader_st.FeeIndex_u16  =
							Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].BlockPersistentId_u16;
					Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
							Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
					Fee_GlobInfoLastRdHeader_st.BlkStatus_u8  =
							(uint8)(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & 0xFFu);


					/*Enforce a rewrite of that block even for 2sec blocks with one copy present*/
					Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32     = 0;

					/*Reset the search result, which can be set at the first search for double security blocks*/
					/*This change prevents a double write at the same address in LLWrite NoFB marker writing*/
					Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = FEE_MAXUINT32;

					/* Check if the current order is an invalidation order */
					if(Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER)
					{
						/* Set the corresponding flag in block status */
						Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 |= (uint8)FEE_FLAG_INVALID_MSK;

						/* Set the block length to zero (save the block header only, data is not necessary) */
						Fee_GlobInfoLastRdHeader_st.BlkLength_u16 = 0;
					}

					/* Initialize the page buffer */
					Fee_SrvMemSet8((uint8*)&Fee_PageBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_LL_PAGEBUFFSIZE);

					/* Calculate the header CRC */
					Fee_LLPrepPageBufWithHdrDataStart(&Fee_GlobInfoLastRdHeader_st);

					/* Set the start value for the block CRC calculation */
					xBlkCrc_u32 = ((uint32)Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16) ^ FEE_MAXUINT32;

					#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
					/* Set the block length depending on the robustness configuration */
					if((((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
														(uint16)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint16)FEE_FLAG_ROBUST_ATTR_BP) > 0) &&
						((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) == 0u))
					{
						/* Set the block length for the checksum calculation */
						xBlkLength_u16 = Fee_GlobInfoLastRdHeader_st.BlkLength_u16 - FEE_SIZE_OF_BLOCK_CS;
					}
					else
					#endif
					{
						/* Set the block length for the checksum calculation */
						xBlkLength_u16 = Fee_GlobInfoLastRdHeader_st.BlkLength_u16;
					}

					/* Set next state to prepare the block checksum before writing the block */
					Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_CALC_BLK_CS_E;
				}
				break;

				/* The cache is corrupt */
				case FEE_ABORTED_E:
					/* Indicate retry */
					 xSearchRetry_b = TRUE;

					/* Search again manually (since the cache was marked for a manual search inside
					 * the Fee_LLSearchSpecificBlkHeader already,
					 * the search will be switched to the manual mode automatically. */
				break;


				/* Default states (can never be reached) */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_SECTORFULL_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_NUM_RET_VAL_E:
				default:
				{
					/* Return an error */
					xRetVal_en = FEE_ABORTED_E;
				}
				break;
			}
		}
		break;

		/* Calculate the user checksum */
		case FEE_HL_CALC_BLK_CS_E:
		{
			/* Get the number of bytes for this Crc calculation run */
			xNumBytes_u16 = (uint16)(xBlkLength_u16 - xNumCrcBytesConsid_u16);

			/* Check for a necessary restriction */
			if(xNumBytes_u16 > FEE_LL_CRC_CALC_RESTRICTION)
			{
				/* Restrict the amount of bytes that are used for calculation */
				xNumBytes_u16 = FEE_LL_CRC_CALC_RESTRICTION;
			}

			/* Check how many data bytes are left (relevant for write orders only) */
			if (xNumBytes_u16 > 0)
			{
				/* Calculate the block checksum step wise */
				xBlkCrc_u32 = Crc_CalculateCRC32((uint8*)&Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8[xNumCrcBytesConsid_u16],
												 (uint32)xNumBytes_u16,
												 xBlkCrc_u32,
												 FALSE);

				/* Increment the amount of already considered bytes */
				xNumCrcBytesConsid_u16 += xNumBytes_u16;
			}
			else
			{
				/* The checksum calculation is finished for Non - Invalidation orders. */

				/* Check if the current order is an invalidation order */
				if(Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_INVALIDATE_ORDER)
				{
					/* Due to a block length of zero the checksum calculation has to be done here */
					xBlkCrc_u32 = Crc_CalculateCRC32((uint8*)&Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8[0],
													 (uint32)xNumBytes_u16,
													 (((uint32)Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16) ^ FEE_MAXUINT32),
													  FALSE);
				}

				/* Check if the calculated checksum is equal to the checksum in the flash (out of the block header) */
				if((xBlkCrc_u32 == Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32) &&
				   (Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 != FEE_MAXUINT32))
				{
					/* Write sequence is not necessary
					 * Verify the block checksum in the block header in the flash to make sure that
					 * the former write was not aborted or that the flash is still OK */
					Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_CHECK_BLK_CS_E;
				}
				else
				{
					/* The block checksum in the flash is different to the calculated one
					 * --> write the data */
					Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_WR_BLK_E;
				}

				/* Prepare the page buffer independent from any subsequent write access to the flash
				 * (a compare order might result in a write order afterwards) */
				Fee_LLPrepPageBufWithHdrDataEnd(&Fee_GlobInfoLastRdHeader_st, &Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8[0], xBlkCrc_u32);
			}
		}
		break;

		/* Verify the block checksum in the flash */
		case FEE_HL_CHECK_BLK_CS_E:
		{
			/* Compare the user data + block header with the complete block and the block header in the flash */
			xtmpRetVal_en = Fee_LLCompBlkInFlash(&Fee_GlobInfoLastRdHeader_st,
												 &Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8[0]);

			/* Evaluate the function return */
			switch(xtmpRetVal_en)
			{
				/* Order is still pending */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

				/* Order is finished with success, the block is still OK in the flash */
				case FEE_ORDER_FINISHED_E:
				{
					/*  A refresh of the cache entry was already done inside the compare function
					 * (it might be overwritten due to a retry while searching the header) */

                    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
				    /* In case of NoFallback blocks
				     * - it doesn't matter which block is checked since Fee_HLMaintainBlock ensures that always two
				     *   copies are available
				     * - the 1. copy was checked and the Cache is pointing to that after comparing the data */
				    // Shift of the block propertie's flags is not necessary here, because the offset is 0
                    if(((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u) &&
                       ((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_SEC_LEVEL_MSK) == FEE_BLK_INT_DOUBLE_STORAGE) &&
                       (Fee_Rb_NoFallback_RemAdr_u32 != FEE_MAXUINT32))
                    {
                        /* Restore the Cache with the address of the latest copy */
                        Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_st.FeeIndex_u16, Fee_Rb_NoFallback_RemAdr_u32);
                    }
                    #endif

					/* Finish this function */
					xRetVal_en = FEE_ORDER_FINISHED_E;
				}
				break;

				/* The data in the flash is different compared to the user data */
				case FEE_ERROR_E:
				{
					/* Write the data again (a cache update is handled right before the Fls is accessed
					 * inside the function Fee_LLWriteBlock) */
					Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_WR_BLK_E;
				}
				break;

				/* Default, states cannot be reached */
				case FEE_ERASE_SECTOR_E:
				case FEE_SECTORCHANGE_E:
				case FEE_SECTORFULL_E:
				case FEE_ABORTED_E:
				case FEE_BLOCK_INVALIDATED_E:
				case FEE_NUM_RET_VAL_E:
				case FEE_SEARCH_ABORTED_E:
				default:
				{
					/* Return an error */
					xRetVal_en = FEE_ABORTED_E;
				}
				break;
			}
		}
		break;

		/* Write the complete block */
		case FEE_HL_WR_BLK_E:
		{
			/* Call the write interface */
			xtmpRetVal_en = Fee_LLWriteBlock(&Fee_GlobInfoLastRdHeader_st,
											 Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8);

			/* Evaluate the function return */
			switch(xtmpRetVal_en)
			{
				/* Order is still pending */
				case FEE_ORDER_PENDING_E:
				{
					/* Just wait */
					;
				}
				break;

				/* A write error occured */
				case FEE_ERROR_E:
				case FEE_ABORTED_E:
				{
					/* if the function Fee_LLWriteBlock() abort with error start the retry on this block, this will be done               */
					/* in case  of flash interface problems (FEE_ABORT_E) and in case if the fls driver returns with error (FEE_ERROR_E). */
					if(Fee_GlobInfoWrBlock_st.cntWriteRetry_u8 > 0)
					{
						/* Decrement retry possibilities */
						Fee_GlobInfoWrBlock_st.cntWriteRetry_u8--;

						/* Restart with the block */
						Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_RDWR_BLK_INIT_E;
					}
					else
					{
						xRetVal_en = FEE_ERROR_E;
					}

				}
				break;

				/* The write order exceeds the HSR */
				case FEE_SECTORFULL_E:
					/* Return the function return */
					xRetVal_en = xtmpRetVal_en;
				break;

				/* Error states */
				case FEE_ORDER_FINISHED_E:
				case FEE_SECTORCHANGE_E:
				{
					/* Return the function return (cache is already updated in the function Fee_LLWriteBlock) */
					xRetVal_en = xtmpRetVal_en;
				}
				break;

				/* Default, case should never be reached */
				default:
				{
					/* Return an error */
					xRetVal_en = FEE_ABORTED_E;
				}
				break;
			}
		}
		break;

		/* Cases are not reachable for the write function */
		case FEE_HL_RD_DATA_FROM_BLK_E:
		case FEE_HL_COMP_BLK_E:
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
        /* Init number of retries for this block */
        Fee_GlobInfoWrBlock_st.cntWriteRetry_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_HLWrBlock_en = FEE_HL_RDWR_BLK_INIT_E;
    }

    return (xRetVal_en);
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
