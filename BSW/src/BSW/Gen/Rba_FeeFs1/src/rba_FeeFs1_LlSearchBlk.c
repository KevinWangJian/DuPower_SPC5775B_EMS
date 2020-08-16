


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
#include "Fls_Types.h"
#include "Fee.h"
#include "rba_FeeFs1_Prv.h"
#include "Fls.h"
#include "rba_FeeFs1_SyncRead.h"
#if (FEE_SIMULATION_ACTIVE != FALSE)
#include "rba_FlsIfx.h"
#endif

#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    //#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
   // #error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Crc.h"
#if (!defined(CRC_AR_RELEASE_MAJOR_VERSION) || (CRC_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CRC_AR_RELEASE_MINOR_VERSION) || ((CRC_AR_RELEASE_MINOR_VERSION != 0) && (CRC_AR_RELEASE_MINOR_VERSION != 2)))
    #error "AUTOSAR minor version undefined or mismatched"
#endif

#if (FEE_PRV_DEBUGGING != FALSE)
#include "Mcu.h"
#include "Eep.h"
/* FEE_PRV_DEBUGGING */
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_LLSearchSpecifiedBlkHeader(): Search for a specific block header
 *                                   within all sector
 *
 * This function searches for a specific block header within all
 * sectors.
 *
 * \param    FeeIdx_u16:            Fee block index to search
 * \param    LastHdrAddr_ptr:       Address pointer for the last header address
 * \param    GlobBlkHdr_ptr:        Pointer for the block header content
 *                                  that will be found
 * \param    SearchRetry_b:         Retry of search
 * \return
 * \retval   FEE_ERROR_E:           The block does not exist in the flash
 * \retval   FEE_ABORTED_E:         The cache access did not work (another block
 *                                  or no block index was referenced)
 *                                  The function needs to be called again.
 * \retval   FEE_ORDER_FINISHED_E:  Order is finished with success
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchSpecifiedBlkHeader(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                                P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) LastHdrAddr_ptr,
                                                                P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) GlobBlkHdr_ptr,
                                                                VAR(boolean, AUTOMATIC) SearchRetry_b)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal    = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xtmpRetVal = FEE_ORDER_PENDING_E;  /* Temp return */

    VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) xTmpBlkHdr_st;         /* Temporary block header */
    VAR(uint8, AUTOMATIC)   xLogSecIdx_u8;                              /* Index of the logical sector */
	VAR(boolean, AUTOMATIC) xContinueSearch_b = FALSE;                  /* Seach indicator */
    VAR(uint32, AUTOMATIC)  xTmpAddr_u32 = FEE_CACHE_INIT_VALUE;        /* Temp variable */
    VAR(boolean, AUTOMATIC) xForcePageBufReload_b = FALSE;              /* Force no reload of the page buffer */

    static uint8 xPhySecIdx_u8  = FEE_NO_SEC_IDX_FOUND;                 /* Index of the active sector */
    static uint8 xSearchType_u8 = FEE_USE_MANUAL_ACCESS;                /* Search type (Cached / manual) */

    #if (FEE_PRV_DEBUGGING != FALSE)
    if(Eep_stMain == EEP_FIRSTINIT_INI)
    {
        Fee_Prv_stModuleTest_st.Fee_SearchSpecificBlockHeaderNum_u32++;
    }
    #endif


	/* Switch over state machine */
	switch (Fee_RdWrOrder_st.Fee_LLSearchBlkHdr_en)
	{
		/* Init state */
		case FEE_LL_SEARCHBLK_INIT_E:
		{
			/* Check if this is the first try to find a valid block */
			if((SearchRetry_b == FALSE) ||
			   (*LastHdrAddr_ptr == FEE_MAXUINT32))
			{
				/* Detect the most current sector because this is no retry due to
				 * an invalid block checksum. */
				xPhySecIdx_u8 = Fee_GetMostCurrentSectorIdx();
			}
			else
			{
				/* Get the corresponding sector index of the current read sector
				 * (this might be a retry within the most current or an elder sector) */
				xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);
			}

			/* Cache is not available for unknown blocks during the "afterburner" run
			 * which will be visible by a return of FEE_CACHE_INIT_VALUE. */
			if((Fee_Prv_stReorg_u8 != FEE_PRV_ST_REORG_AFTERB_RUNNING) &&
			   (SearchRetry_b == FALSE))
			{
				/* Try to get a valid address via cache */
				xTmpAddr_u32 = Fee_LLGetAddressFromCache(FeeIdx_u16);
			}

			/* Evaluate the cache content */
			if((xTmpAddr_u32 != FEE_CACHE_INIT_VALUE) &&
			   (xTmpAddr_u32 != FEE_CACHE_TMP_INVALID_VALUE))
			{
			    /* Cache can be used */
			    xSearchType_u8 = FEE_USE_CACHED_ACCESS;

			    /* Copy cache address */
			    Fee_RdWrOrder_st.xRdAddress = xTmpAddr_u32;
			}
			else
			{
			    /* Start the manual search from the beginning of the sector */
			    Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecStartAddress(xPhySecIdx_u8);

				/* A manual search is necessary */
				xSearchType_u8 = FEE_USE_MANUAL_ACCESS;
			}

			/* This pattern is used to detect if at least 1 time a valid header was copied */
			GlobBlkHdr_ptr->FeeIndex_u16 = FEE_MAXUINT16;

			/* Force a reload of the page buffer because the init state is only passed for
			 * new block read orders */
			xForcePageBufReload_b = TRUE;

			/* Set next state */
			Fee_RdWrOrder_st.Fee_LLSearchBlkHdr_en = FEE_LL_SEARCHBLK_BLK_HEADER_E;
		}
		/* No break to save time */

		/* Search any block header beginning at Fee_RdWrOrder_st.xRdAddress (manual search without cache) */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_SEARCHBLK_BLK_HEADER_E:
		{
			/* Search for the next block header. If cached access is used, the address for the header is already
			 * in the cache. If the manual search is used, the start address for the search can be changed
			 * via Fee_RdWrOrder_st.xRdAddress.
			 *
			 * The cache will always contain the latest version of the block. If this block is corrupt,
			 * the calling function comes back with the LastHdrAddr_ptr as the upper limit of the search.
			 * The area before this address has to be checked now in order to find elder versions of this
			 * block inside any of the sectors.
			 *
			 * During the initialization (and shutdown), the most current sector has already been checked via
			 * Fee_LLFindNextEmptyPage and the cache has been build up. All available blocks within the most
			 * current USED sector are available via cache from this moment onwards. Therefor this sector
			 * can be skipped for the subsequent read orders during the initialization if no cache entry
			 * is available.
			 * */

			/* Check if the current sector has to be used for the search. This is indicated by the
			 * update status array for the cache. In case the respective sector has already been checked,
			 * all found blocks out of the configuration are already in the cache).
			 * Searches can be skipped in case there is no cache entry available and the sector has
			 * been checked already and no older version is necessary to be detected. */
		    /* MR12 RULE 13.5 VIOLATION: Search must be continued when any of the multiple conditions are failed. */
		    if((Fee_LLGetCacheUpdateStForSect(xPhySecIdx_u8) == FEE_CACHE_UPD_COMP_FOR_SECT) &&
			   (xSearchType_u8 == FEE_USE_MANUAL_ACCESS) &&
			   (SearchRetry_b == FALSE) &&
			   (Fee_LLGetAddressFromCache(FeeIdx_u16) != FEE_CACHE_TMP_INVALID_VALUE) &&
			   (Fee_Prv_stReorg_u8 != FEE_PRV_ST_REORG_AFTERB_RUNNING))
			{
				/* Skip the search within the current sector and check if other sectors
				 * might be used for the search */
				xtmpRetVal = FEE_SEARCH_ABORTED_E;
			}
			else
			{
				/* Search the next block header */
				xtmpRetVal = Fee_LLSearchNextBlkHeader(&xTmpBlkHdr_st, xSearchType_u8, FEE_NO_CACHE_UPDATE, xForcePageBufReload_b, 0);
			}

            /* Switch function return */
            switch(xtmpRetVal)
            {
                /* Order is still pending */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                    ;
                }
                break;

				/* One valid header was found */
				case FEE_ORDER_FINISHED_E:
				{

					/* Check if the correct block index was found */
                    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
                    if((xTmpBlkHdr_st.FeeIndex_u16 == FeeIdx_u16) &&
                       ((Fee_RdWrOrder_st.Fee_LLSecReorg_en == FEE_LL_REORG_SEARCH_BLK_E) || /* sector change is active and no entry in the Fee_OrderFifo_st exists */
                    /* Search for an unknown block without cache. */
                    #if(((FEE_RB_ACT_SURVIVAL_EVAL != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_REORG == FALSE)) || ((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)))
 					    (Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en == FEE_LL_SEARCHUNKNBLK_SPEC_BLK_HEADER_E) || /* sector change is active and no entry in the Fee_OrderFifo_st exists */
                    #endif
 					    /* MR12 RULE 9.1 VIOLATION: The variable xTmpBlkHdr_st.BlkLength_u16 cannot be unset */
 						(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16 == xTmpBlkHdr_st.BlkLength_u16) ||
						(Fee_OrderFifo_st[Fee_idxActQueue_u8].Length_u16 == 0) || (xTmpBlkHdr_st.BlkLength_u16 == 0) ||
						(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16 == (xTmpBlkHdr_st.BlkLength_u16 + 4))))
					{
						/* Check if this is a retry due to an invalid latest copy and if the address of the
						 * newer, invalid block is already reached. There is no need to differ between a
						 * first try and a later try */
						/* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						if(*LastHdrAddr_ptr > xTmpBlkHdr_st.AdrBlkHeader_u32)
						{
							/* LastHdrAddr has the init value or an older copy was found
							 * --> search for newer copies inside the same sector */

							/* Save the block info */
							/* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->AdrBlkHeader_u32 = xTmpBlkHdr_st.AdrBlkHeader_u32;
						    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->BlkLength_u16    = xTmpBlkHdr_st.BlkLength_u16;
						    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->BlkStatus_u8     = xTmpBlkHdr_st.BlkStatus_u8;
						    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->FeeIndex_u16     = xTmpBlkHdr_st.FeeIndex_u16;
						    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->BlkCrc32_u32     = xTmpBlkHdr_st.BlkCrc32_u32;
						    /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
						    GlobBlkHdr_ptr->HdrCrc16_u16     = xTmpBlkHdr_st.HdrCrc16_u16;

						    /* Check if the search can be finished (the cache always contains the latest copy) */
						    if(xSearchType_u8 == FEE_USE_CACHED_ACCESS)
						    {
						        /* Block was found (latest copy), do not search until the sector end is reached */
						        xRetVal = FEE_ORDER_FINISHED_E;
						    }
						    else
						    {
						        /* Update the read address to the last found block header */
						        Fee_RdWrOrder_st.xRdAddress = xTmpBlkHdr_st.AdrBlkHeader_u32;

						        /* Increment the read address page wise ("safety mode") and search for the next
						         * block header until the complete sector is checked
						         * --> search for all copies of the block in order to find the latest one */
						        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);
						    }
						}
						else
						{
							/* The end address (former invalid block) is reached
							 * --> Check if at least one header was found before */

							if(GlobBlkHdr_ptr->FeeIndex_u16 != FEE_MAXUINT16)
							{
								/* The latest valid copy was found */
								xRetVal = FEE_ORDER_FINISHED_E;
							}
							else
							{
								/* There was no valid header found in the address space before the last invalid block
								 * --> Valid block is not within the current sector
								 * --> Search within older sectors if possible */

								/* Get the corresponding sector index of the sector that has been
								 * used for the search */
								xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

								/* Get the corresponding logical sector index */
								xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

								/* Reset the search indicator */
								xContinueSearch_b = FALSE;

								/* Check if there are more logical sectors available (0 is the lowest possible value)
								 * and if one of these sectors is either in the state FULL or USED */
								if(xLogSecIdx_u8 > 0)
								{
								    do
								    {
								        /* Decrement the logical sector */
								        xLogSecIdx_u8--;

								        /* Check for relevant sector states */
								        if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
								           (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
								        {
								            /* Go on with the previous sector */
								            xContinueSearch_b = TRUE;

								            /* Get respective physical sector index */
								            xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

								            /* This sector has to be checked, starting at the beginning */
								            Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32;

								            /* Set back the LastHrAddr_ptr because the new sector might have new adress ranges */
								            *LastHdrAddr_ptr = FEE_MAXUINT32;

											/* Make sure the manual search will be started in the next sector */
											xSearchType_u8 = FEE_USE_MANUAL_ACCESS;

											/* The next search will start in the previous sector and will continue until the
											 * end of this sector is reached */
								        }
									}
									while((xLogSecIdx_u8 > 0) && (xContinueSearch_b == FALSE));
								}

								/* Check if all relevant sectors have been checked already */
								if(xContinueSearch_b == FALSE)
								{
									/* All relevant sectors have been checked, block header cannot be found,
									 * invalidate the cache */
									Fee_LLInvalidateAddressInCache(FeeIdx_u16);

									/* Set the return value */
									xRetVal = FEE_ERROR_E;
								}
                            }
						}
					}
					else
					{
						/* Another block was found */
						/* *********************** */

						/* Evaluate the search type */
						if(xSearchType_u8 == FEE_USE_CACHED_ACCESS)
						{
							/* The address inside the cache was not correct or the data inside
							 * the header is corrupt.
							 * The manual search will be started automatically (no valid cache entry available). */

							/* Mark the cache for the activation of the manual search instead of avoiding
							 * this during the sector reorganization */
							Fee_LLUpdateAddressInCache(xTmpBlkHdr_st.FeeIndex_u16,
													   FEE_CACHE_TMP_INVALID_VALUE);

							/* Set return value */
							xRetVal = FEE_ABORTED_E;
						}
						else
						{
							/* Get the block address from the cache */
							xTmpAddr_u32 = Fee_LLGetAddressFromCache(xTmpBlkHdr_st.FeeIndex_u16);

							/* Check if a cache entry is already available and the search will be
							 * continued until the end of a sector (*LastHdrAddr_ptr == FEE_MAXUINT32).
							 * Not for retries after finding a block with a corrupted block checksum.
							 * Hint: the block checksum is not verified */
							if(((xTmpAddr_u32 == FEE_CACHE_INIT_VALUE) ||
								(xTmpAddr_u32 == FEE_CACHE_TMP_INVALID_VALUE)) &&
								(*LastHdrAddr_ptr == FEE_MAXUINT32))
							{
								/* There is no valid entry available, update the cache */
							    Fee_LLUpdateAddressInCache(xTmpBlkHdr_st.FeeIndex_u16,
							                               /* MR12 RULE 9.1 VIOLATION: Due to the return type, the variable cannot be unset */
                                                           xTmpBlkHdr_st.AdrBlkHeader_u32);
                            }
                            else
                            {
                                /* A cache entry already exists, an update might be possible */

								/* Get the corresponding sector index */
								xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

								/* Check if the address is within the same sector because
								 * later versions will always be located behind old copies and if
								 * the search will be continued until the end of the sector
								 * (a retry after a defect block CRC was found is indicated via
								 *  *LastHdrAddr_ptr != FEE_MAXUINT32 := upper limit for the search)*/
								if((xTmpAddr_u32 >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
								   (xTmpAddr_u32 <  Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32) &&
								   (*LastHdrAddr_ptr == FEE_MAXUINT32))
								{
									/* Overwrite the cache entry with a later block version */
									Fee_LLUpdateAddressInCache(xTmpBlkHdr_st.FeeIndex_u16,
															   xTmpBlkHdr_st.AdrBlkHeader_u32);
								}
							}

							/* Update the read address to the last found block header */
							Fee_RdWrOrder_st.xRdAddress = xTmpBlkHdr_st.AdrBlkHeader_u32;

							/* Increment the read address page wise ("safety mode") and search for the next
							 * block header until the end of the sector is reached */
							Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);
						}
					}
				}
				break;

				/* The requested header was not found in the sector that was used for the search */
				case FEE_SECTORFULL_E:
				case FEE_SEARCH_ABORTED_E:
				{

					/* Get the corresponding sector index of the sector that has been
					 * used for the search */
					xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

					/* Mark the respective sector as checked for building up the cache during
					 * the initialization phase of the driver or if it is manual search
					 * (during the manual search the cache is updated on "its" way to the
					 *  end of the sector) */
					if(xSearchType_u8 == FEE_USE_MANUAL_ACCESS)
					{
						/* Update the cache status array for the current sector */
						Fee_LLUpdateCacheStForSect(xPhySecIdx_u8);
					}

					/* Check if at least one header was found before */
					if(GlobBlkHdr_ptr->FeeIndex_u16 != FEE_MAXUINT16)
					{
						/* The end of the sector is reached and the latest copy was found */
						xRetVal = FEE_ORDER_FINISHED_E;
					}
					else
					{
						/* Check if another sector might be used to continue with the search */

						/* Get the corresponding logical sector index */
						xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];
						/* Reset the search indicator */
						xContinueSearch_b = FALSE;

						/* Check if there are more logical sectors available (0 is the lowest possible value)
						 * and if one of these sectors is either in the state FULL or USED */
						if(xLogSecIdx_u8 > 0)
						{
							do
							{
                                /* Decrement the logical sector */
                                xLogSecIdx_u8--;

                                /* Check for relevant sector states */
                                if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                                   (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                                {
                                    /* Go on with the previous sector */
                                    xContinueSearch_b = TRUE;

                                    /* Get respective physical sector index */
                                    xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

                                    /* This sector has to be checked, starting at the beginning */
                                    Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32;

                                    /* Set back the LastHrAddr_ptr because the new sector might have new address ranges */
                                    *LastHdrAddr_ptr = FEE_MAXUINT32;

                                    /* Make sure the manual search will be started in the next sector */
									xSearchType_u8 = FEE_USE_MANUAL_ACCESS;

									/* The next search will start in the previous sector and will continue until the
									 * end of this sector is reached */
                                }
							}
							while((xLogSecIdx_u8 > 0) && (xContinueSearch_b == FALSE));
						}

						/* Check if all relevant sectors have been checked already */
						if(xContinueSearch_b == FALSE)
						{
							/* All relevant sectors have been checked, block header cannot be found,
							 * invalidate the cache */
							Fee_LLInvalidateAddressInCache(FeeIdx_u16);

							/* Set the return value */
							xRetVal = FEE_ERROR_E;
						}
					}
				}
				break;

				/* Cache access did not show any result */
				case FEE_ERROR_E:
					/* Mark the cache for the activation of the manual search instead of avoiding
					 * this during the sector reorganization */
					Fee_LLUpdateAddressInCache(FeeIdx_u16,
											   FEE_CACHE_TMP_INVALID_VALUE);

					/* Return with an error to be called again with the manual search */
					xRetVal = FEE_ABORTED_E;
				break;

				/* Error cases */
				case FEE_ABORTED_E:
				default:
				{
					/* States should never be reached,
					 * invalidate the cache entry */
					Fee_LLUpdateAddressInCache(FeeIdx_u16,
										   	   FEE_CACHE_TMP_INVALID_VALUE);

					/* Set the return value */
					xRetVal = FEE_ERROR_E;
				}
				break;
			}
		}
		break;

		/* Default case */
		default:
		{
			/* States should never be reached,
			 * mark the cache for the activation of the manual search */
			Fee_LLUpdateAddressInCache(FeeIdx_u16,
									   FEE_CACHE_TMP_INVALID_VALUE);

			/* Set the return value */
			xRetVal = FEE_ERROR_E;
		}
		break;
	}


    /* Check for necessary resets */
    if(xRetVal != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_LLSearchBlkHdr_en = FEE_LL_SEARCHBLK_INIT_E;

        /* Reset physical sector index */
        xPhySecIdx_u8 = FEE_NO_SEC_IDX_FOUND;

        /* Reset search type */
        xSearchType_u8 = FEE_USE_MANUAL_ACCESS;
    }

    return (xRetVal);
}


#if((FEE_RB_ACT_SURVIVAL_EVAL != FALSE) || (FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE))
/* Search for an unknown block without cache. */
#if (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0)
/**
 *********************************************************************
 * Fee_LLSearchUnknownBlkHeader(): Search for an unknown block header
 *                                 within all sector. Search is without cache.
 *
 * This function searches for an unknown block header within all
 * sectors and returns the latest valid copy of this block.
 *
 * \param    StartHdrAddr_ptr:      Start address for the search
 * \param    LastHdrAddr_ptr:       Address pointer for the last header address
 * \param    GlobBlkHdr_ptr:        Pointer for the block header content
 *                                  that will be found
 * \param    SearchRetry_ptr:       Retry of search
 * \return
 * \return   FEE_PENDING_E:         Search is still ongoing
 * \retval   FEE_ERROR_E:           No unknown block exists in the
 *                                  eldest FULL sector
 * \retval   FEE_ORDER_FINISHED_E:  Order is finished with success
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchUnknownBlkHeader(P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) StartHdrAddr_ptr,
                                                              P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) LastHdrAddr_ptr,
                                                              P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) GlobBlkHdr_ptr,
                                                              P2VAR(boolean, AUTOMATIC, FEE_APPL_DATA) SearchRetry_ptr)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal    = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xtmpRetVal = FEE_ORDER_PENDING_E;  /* Temp return */

    VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) xTmpNxtBlkHdr_st;      /* Temporary block header */

    VAR(boolean, AUTOMATIC) xForcePageBufReload_b = FALSE;              /* Force no reload of the page buffer */
    VAR(uint16, AUTOMATIC)  xDummyCacheIdx_u16 = 0;                     /* Cache index dummy */
    VAR(uint8, AUTOMATIC)   xPhySecIdx_u8  = FEE_NO_SEC_IDX_FOUND;      /* Index of the active sector */
    static uint16           xFeeIdx_u16 = FEE_MAXUINT16;                /* Block index */


    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over state machine */
        switch (Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en)
        {
            /* Init state */
            case FEE_LL_SEARCHUNKNBLK_INIT_E:
            {
                /* Force a reload of the page buffer because the init state is only passed for
                 * new block read orders */
                xForcePageBufReload_b = TRUE;

                /* Check for a retry because of an invalid block checksum */
                if(*SearchRetry_ptr == FALSE)
                {
                    /* Reset the next block index */
                    xFeeIdx_u16 = FEE_MAXUINT16;

                    /* Copy the start address for the search */
                    Fee_RdWrOrder_st.xRdAddress = *StartHdrAddr_ptr;

                    /* Set next state */
                    Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_UNKN_BLK_HEADER_E;
                }
                else
                {
                    /* Return to the specified header search because this is a retry */
                    Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_SPEC_BLK_HEADER_E;

                    /* Get the corresponding sector index of the current read sector
                     * (this might be a retry within the most current or an elder sector) */
                    xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

                    /* Start the manual search from the beginning of the sector */
                    Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecStartAddress(xPhySecIdx_u8);

                    break;
                }
            }
            /* No break to save time */

            /* Search any block header beginning at Fee_RdWrOrder_st.xRdAddress (manual search without cache) */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_SEARCHUNKNBLK_UNKN_BLK_HEADER_E:
            {
                /* Search for the next block header. The start address for the search can be changed
                 * via Fee_RdWrOrder_st.xRdAddress.
                 * */

                /* Search the next block header */
                xtmpRetVal = Fee_LLSearchNextBlkHeader(&xTmpNxtBlkHdr_st, FEE_USE_MANUAL_ACCESS, FEE_NO_CACHE_UPDATE, xForcePageBufReload_b, 0);

                /* Switch function return */
                switch(xtmpRetVal)
                {
                    /* Order is still pending */
                    case FEE_ORDER_PENDING_E:
                    {
                        /* Just wait */
                        ;
                    }
                    break;

                    /* One valid unknown block header was found (within the oldest FULL sector) */
                    case FEE_ORDER_FINISHED_E:
                    {
                        /* Reset the forced reload for the initialization (init value will remain
                         * true in case the polling mode is active) */
                        xForcePageBufReload_b = FALSE;

                        /* Check if the found block index is within the configuration or not */
                        if(Fee_SrvBinarySearchInBlockProp(xTmpNxtBlkHdr_st.FeeIndex_u16, &xDummyCacheIdx_u16) == FALSE)
                        {
                            /* Check if this block has to be transfered. This is the case if:
                             * Block is not in the layout (afterburner is running) AND
                             *      - Survival flag is TRUE (config setting must be taken out of the DFlash) OR
                             *      - FEE_RB_ACT_UNKNOWN_BLOCK_REORG == TRUE (valid for all blocks) */
                            if(((xTmpNxtBlkHdr_st.BlkStatus_u8 & (uint8)FEE_FLAG_SURV_ATTR_MSK) > 0u) ||
                               (FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE))
                            {
                                /* The first copy of an unknown block index was found,
                                 * identify the latest valid version of this block in the next step */

                                /* Update the read address to the last found block header */
                                Fee_RdWrOrder_st.xRdAddress = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;

                                /* Increment the read address page wise ("safety mode") and search for the next
                                 * block header until the complete sector is checked
                                 * --> search for all copies of the block in order to find the latest one */
                                Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);

                                /* Save the block info */
                                GlobBlkHdr_ptr->AdrBlkHeader_u32 = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;
                                GlobBlkHdr_ptr->BlkLength_u16    = xTmpNxtBlkHdr_st.BlkLength_u16;
                                GlobBlkHdr_ptr->BlkStatus_u8     = xTmpNxtBlkHdr_st.BlkStatus_u8;
                                GlobBlkHdr_ptr->FeeIndex_u16     = xTmpNxtBlkHdr_st.FeeIndex_u16;
                                GlobBlkHdr_ptr->BlkCrc32_u32     = xTmpNxtBlkHdr_st.BlkCrc32_u32;
                                GlobBlkHdr_ptr->HdrCrc16_u16     = xTmpNxtBlkHdr_st.HdrCrc16_u16;

                                /* Copy the block index for the search */
                                xFeeIdx_u16 = GlobBlkHdr_ptr->FeeIndex_u16;

                                /* Set the next state to find the latest valid block version inside
                                 * all sectors */
                                Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_SPEC_BLK_HEADER_E;
                            }
                            else
                            {
                                /* The found unknown block need not be transffered
                                 * --> Go on with the search */

                                /* Update the read address to the last found block header */
                                Fee_RdWrOrder_st.xRdAddress = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;

                                /* Increment the read address page wise ("safety mode") and search for the next
                                 * block header until the complete sector is checked
                                 * --> search for all copies of the block in order to find the latest one */
                                Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);
                            }
                        }
                        else
                        {
                            /* The found block is within the layout and not relevant for this search
                             * --> Go on with the search */

                            /* Update the read address to the last found block header */
                            Fee_RdWrOrder_st.xRdAddress = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;

                            /* Increment the read address page wise ("safety mode") and search for the next
                             * block header until the complete sector is checked
                             * --> search for all copies of the block in order to find the latest one */
                            Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);
                        }

                        /* Save the address as start value for the next run for finding the next
                         * unknown block index */
                        *StartHdrAddr_ptr = Fee_RdWrOrder_st.xRdAddress;
                    }
                    break;

                    /* The sector end address is reached */
                    case FEE_SECTORFULL_E:
                    case FEE_SEARCH_ABORTED_E:
                    {
                        /* The end address for the search is set inside the calling function */

                        /* Function can be finished */
                        xRetVal = FEE_SECTORFULL_E;
                    }
                    break;

                    /* Error cases */
                    case FEE_ABORTED_E:
                    case FEE_ERROR_E:
                    default:
                    {
                        /* States should never be reached */
                        xRetVal = FEE_ERROR_E;
                    }
                    break;
                }
            }
            break;

            /* Search the next specific block header */
            case FEE_LL_SEARCHUNKNBLK_SPEC_BLK_HEADER_E:
                /* Search for the next block header with the given FeeIdx.
                 * The start address for the search can be set with the variable xAdrLastBlkHeader_u32. */
                xtmpRetVal = Fee_LLSearchSpecifiedBlkHeader(xFeeIdx_u16,        /* FeeIdx */
                                                            LastHdrAddr_ptr,    /* End address for the search */
                                                            GlobBlkHdr_ptr,     /* Result structure */
                                                            *SearchRetry_ptr);     /* Indicate first try or not */

                /* Evaluate the search result */
                switch(xtmpRetVal)
                {
                    /* Order not finished yet */
                    case FEE_ORDER_PENDING_E:
                    {
                        /* Just wait */
                        ;
                    }
                    break;

                    /* The latest valid block header was found (maybe the one that
                     * was found before in the oldest FULL sector) */
                    case FEE_ORDER_FINISHED_E:
                    {
                        /* Finish function */
                        xRetVal = FEE_ORDER_FINISHED_E;
                    }
                    break;

                    /* No valid header page was found within the complete flash (all sectors have been checked
                     * until the end address LastHdrAddr_ptr has been reached) */
                    case FEE_ERROR_E:
                    {
                        /* Set the read address to the end address of the search and reset the end address */
                        Fee_RdWrOrder_st.xRdAddress = *LastHdrAddr_ptr;
                        *LastHdrAddr_ptr = FEE_MAXUINT32;

                        /* Increment the read address page wise ("safety mode") and search for the next
                         * block header until the complete sector is checked
                         * --> search for all copies of the block in order to find the latest one */
                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);

                        /* Reset the retry indicator (normally done by calling function) */
                        *SearchRetry_ptr = FALSE;

                        /* Go on with the search */
                        Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_INIT_E;

                        /* Do not set the error return but keep on searching. Otherwise the
                         * unkown block reorganization will be finished without reaching the
                         * end of the sector. */
                    }
                    break;

                    /* These cases should never be reached (cannot be returned by Fee_LLSearchSpecifiedBlkHeader).
                     * FEE_ERROR_E and FEE_ABORTED_E cannot be reached because cache is not used and the block
                     * which is searched will be there at least once in the oldest FULL sector */
                    case FEE_BLOCK_INVALIDATED_E:
                    case FEE_ABORTED_E:
                    case FEE_NUM_RET_VAL_E:
                    case FEE_ERASE_SECTOR_E:
                    case FEE_SECTORCHANGE_E:
                    case FEE_SECTORFULL_E:
                    default:
                    {
                        /* Return an error */
                        xRetVal = FEE_ABORTED_E;
                    }
                    break;
                }
            break;

            /* Default case */
            default:
            {
                /* State should never be reached */
                xRetVal = FEE_ERROR_E;
            }
            break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal == FEE_ORDER_PENDING_E));

    /* Check for necessary resets */
    if(xRetVal != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_LLSearchUnknBlkHdr_en = FEE_LL_SEARCHUNKNBLK_INIT_E;
    }

    return (xRetVal);
}
#else
/**
 *********************************************************************************************************
 * Fee_BuildUpCacheUnknownBlk(): Build up the cache for unkown blocks over the oldest sector.
 *
 * This function builds up the cache for the unknown blocks that are present in the oldest sector.
 * The block checksum and data checksum are both considered while building the cahce.
 * The function continues to scan the remaining sectors for finding the latest copy of the unknown blocks.
 * The function is designed to be called when cyclic tasks are running.
 *
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Order is pending
 * \retval   FEE_ABORTED_E:         Order was aborted
 * \retval   FEE_SECTORFULL_E:      The end address of the sector
 *                                  was reached
 * \seealso
 * \usedresources
 *********************************************************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCacheUnknownBlk(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal    = FEE_ORDER_PENDING_E;  /* Function return value */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xtmpRetVal = FEE_ORDER_PENDING_E;  /* To hold return values of the functions Fee_LLCalcBlkCrcInFlash and Fee_LLSearchNextBlkHeader */
    VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) xTmpNxtBlkHdr_st;      /* To hold the details of the unkown block header */
    VAR(uint16,  AUTOMATIC) i;   										/* For loop Variable */
    VAR(uint16,  AUTOMATIC) xDummyCacheIdx_u16 = 0;                     /* Dummy cache index for the function Fee_SrvBinarySearchInBlockProp */
    VAR(uint8,   AUTOMATIC) xPhySecIdx_u8;      						/* Index of the physical sector */
    VAR(uint8,   AUTOMATIC) xLogSecIdx_u8;                              /* Index of the logical sector */
    VAR(boolean, AUTOMATIC) xContinueSearch_b = FALSE;                  /* Flag to indicate if search needs to be continued in other sector or not */
    VAR(boolean, AUTOMATIC) xForcePageBufReload_b = FALSE;              /* Force no reload of the page buffer */
    VAR(boolean, AUTOMATIC)	xOldUnknonwBlk;								/* Flag to indicate if the unknown block is new or old */

    /* Switch over state machine */
    switch (Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en)
    {
        /* Init state */
        case FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_INIT_E:
        {
            /* Initialise cache */
            for (i=0;i<FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE;i++)
            {
                Fee_UnknownBlkCache_Addr_au32[i]    = FEE_CACHE_INIT_VALUE;	/* Block header address */
                Fee_UnknownBlkCache_FeeIndex_u16[i] = 0;  				    /* Fee index */
            }

            /* Clear the count of number of unknown blocks */
            Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 = 0;

			/* Set to next state to build up the cache */
            Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_READ_E;

            /* Force a reload of the page buffer because the init state is only passed for new block read orders */
            xForcePageBufReload_b = TRUE;

            /* Copy the start address for the search, start address is from the last scanned address, if the address is within the range. */
            if ((Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 >= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                (Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 <=  Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
            {
                Fee_RdWrOrder_st.xRdAddress = Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32;
            }
            else
            {
                /* The cache is not built up yet, start from the top of the oldest sector. */
                Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32;
                Fee_RdWrOrder_st.xRdAddress = Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32;
            }
        }
        //break;

        /* MR12 RULE 16.3 VIOLATION: Time critical position, skip break for faster processing */
        case FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_READ_E:
        {
            /* Search the next block header */
            xtmpRetVal = Fee_LLSearchNextBlkHeader(&xTmpNxtBlkHdr_st, FEE_USE_MANUAL_ACCESS, FEE_NO_CACHE_UPDATE, xForcePageBufReload_b, 0);

            /* Switch function return */
            switch(xtmpRetVal)
            {
                /* Order is still pending */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                    ;
                }
                break;

                /* One valid header was found */
                case FEE_ORDER_FINISHED_E:
                {
                    /* Reset the forced reload for the initialization (init value will remain
                     * true in case the polling mode is active) */
                    xForcePageBufReload_b = FALSE;

                    /* Check if the found block index is within the configuration or not */
                    if(Fee_SrvBinarySearchInBlockProp(xTmpNxtBlkHdr_st.FeeIndex_u16, &xDummyCacheIdx_u16) == FALSE)
                    {
                        /* The first copy of an unknown block index was found, validate if Data CRC is ok */

                        /* Update the read address to the last found block header */
                        Fee_RdWrOrder_st.xRdAddress = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;

                        /* Increment the read address page wise ("safety mode") and search for the next
                         * block header until the complete sector is checked
                         * --> search for all copies of the block in order to find the latest one */
                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);

                        /* Update the address till where the sector is scanned till:
                         * 1. The unknown block cache is full and a new unknown block is found or
                         * 2. Till end of oldest sector is reached.
                         */
                        if ((Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 < FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE) &&
                            (Fee_RdWrOrder_st.xRdAddress >= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                            (Fee_RdWrOrder_st.xRdAddress <= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
                        {
                            Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = Fee_RdWrOrder_st.xRdAddress;
                        }
                        else
                        {
                            /* Cache for unknown block cant be built further.
                             * Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 should hold the last address till where the cahce was built.
                             * Hence, do nothing here.  */
                        }

                        /* Save the block info */
                        Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;
                        Fee_GlobInfoLastRdHeader_st.BlkLength_u16    = xTmpNxtBlkHdr_st.BlkLength_u16;
                        Fee_GlobInfoLastRdHeader_st.BlkStatus_u8     = xTmpNxtBlkHdr_st.BlkStatus_u8;
                        Fee_GlobInfoLastRdHeader_st.FeeIndex_u16     = xTmpNxtBlkHdr_st.FeeIndex_u16;
                        Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32     = xTmpNxtBlkHdr_st.BlkCrc32_u32;
                        Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16     = xTmpNxtBlkHdr_st.HdrCrc16_u16;

						/* Go to next state to validate the Data CRC for this copy */
                        Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_VALIDATEDATA_E;
                    }
                    else
                    {
                        /* The found block is a known block and not relevant for this search
                         * --> Go on with the search */

                        /* Update the read address to the last found block header */
                        Fee_RdWrOrder_st.xRdAddress = xTmpNxtBlkHdr_st.AdrBlkHeader_u32;

                        /* Increment the read address page wise ("safety mode") and search for the next
                         * block header until the complete sector is checked
                         * --> search for all copies of the block in order to find the latest one */
                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);

                        /* Update the address till where the sector is scanned till:
                         * 1. The unknown block cache is full and a new unknown block is found or
                         * 2. Till end of oldest sector is reached.
                         */
                        if ((Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 < FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE) &&
                            (Fee_RdWrOrder_st.xRdAddress >= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                            (Fee_RdWrOrder_st.xRdAddress <= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
                        {
                            Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = Fee_RdWrOrder_st.xRdAddress;
                        }
                        else
                        {
                            /* Cache for unknown block cant be built further.
                             * Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 should hold the last address till where the cahce was built.
                             * Hence, do nothing here.  */
                        }
                    }
                }
                break;

                /* The sector end address is reached */
                case FEE_SECTORFULL_E:
                {
                    /* Update the address till where the sector is scanned till:
                     * 1. The unknown block cache is full and a new unknown block is found or
                     * 2. Till end of oldest sector is reached.
                     */
                    if ((Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 < FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE) &&
                        (Fee_RdWrOrder_st.xRdAddress >= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                        (Fee_RdWrOrder_st.xRdAddress <= Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
                    {
                        Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 = Fee_RdWrOrder_st.xRdAddress;
                    }
                    else
                    {
                        /* Cache for unknown block cant be built further.
                         * Fee_RdWrOrder_st.Fee_UnknownBlkCacheAdd_u32 should hold the last address till where the cahce was built.
                         * Hence, do nothing here.  */
                    }

                    /* Continue scanning the other sectors as PLC must be built over all the sectors */
                    /* Get the corresponding physical sector index of the sector that has been used for the search */
                    xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

                    /* Get the corresponding logical sector index */
                    xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

                    /* Reset the search indicator */
                    xContinueSearch_b = FALSE;

                    /* Check if there are more logical sectors available (Fee_NumFlashBanksUsed_u8 is the biggest possible value)
                     * and if one of these sectors is either in the state FULL or USED */
                    do
                    {
                        /* Decrement the logical sector */
                        xLogSecIdx_u8++;

						/* Check for overflow */
						if(xLogSecIdx_u8 < Fee_NumFlashBanksUsed_u8)
						{
                            /* Check for relevant sector states */
                            if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                               (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                            {
                                /* Go on with the next sector */
                                xContinueSearch_b = TRUE;

                                /* Get respective physical sector index */
                                xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

                                /* This sector has to be checked, starting at the beginning */
                                Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32;

                                /* The next search will start in the next sector and will continue until the most active sector is reached */
                           }
						}
						else
						{
							/* End of the sectors have been reached, the loop must be exited now. Do nothing. */
						}
                    }
                    while((xLogSecIdx_u8 < Fee_NumFlashBanksUsed_u8) && (xContinueSearch_b == FALSE));

                    /* Check if all relevant sectors have been checked already */
                    if(xContinueSearch_b == FALSE)
                    {
                        /* All relevant sectors have been checked and cache building is complete. */
                        /* Set the return value */
                        xRetVal = FEE_ORDER_FINISHED_E;
                    }
                }
                break;

                /* Error cases */
                case FEE_SEARCH_ABORTED_E:
                case FEE_ABORTED_E:
                case FEE_ERROR_E:
                default:
                {
                    /* States should never be reached */
                    xRetVal = FEE_ERROR_E;
                }
                break;
            }
        }
        break;

        case FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_VALIDATEDATA_E:
        {
            /* Call to validate if the data CRC is valid */
            xtmpRetVal = Fee_LLCalcBlkCrcInFlash(&Fee_GlobInfoLastRdHeader_st);

            /* Update cache if the CRC is valid */
            /* Switch function return */
            switch(xtmpRetVal)
            {
                /* Order is still pending */
                case FEE_ORDER_PENDING_E:
                {
                    /* Just wait */
                    ;
                }
                break;

                /* One valid header was found */
                case FEE_ORDER_FINISHED_E:
                {
                    /* A unknown block with valid header and valid data is found, store the contents in the cache. */
                    /* Clear the flag to check if this unknown block is already found earlier or not. */
                    xOldUnknonwBlk = FALSE;

                    /* Check if this unknown block was found earlier.
                     * It is suffient to do the check till Fee_UnknownBlkCacheIdx_u16, as this will hold the index till which the cache is filled. */
                    for(i=0; i<Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16; i++)
                    {
                        if (Fee_UnknownBlkCache_FeeIndex_u16[i] == Fee_GlobInfoLastRdHeader_st.FeeIndex_u16)
                        {
                            /* Block was already found earlier, stop the search and set the flag for updating cache. */
                            xOldUnknonwBlk = TRUE;
                            /* Store the index and address, the location to store is there in variable i */
                            Fee_UnknownBlkCache_Addr_au32[i]   = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;	/* Store block header address */

							/* Update of the Fee index is not required as the Fee index is already known now and only the address is being updated now */
                            break;
                        }
                        else
                        {
                            /* Continue the search for the remaning entries in cache. */
                        }
                    }

                    /* If cache is not yet updated, then, update in next available space in cache.
                     * Also, consider only the unknown blocks of the oldest sector only. */
                    if ((xOldUnknonwBlk == FALSE) && (Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16 < FEE_RB_ACT_UNKNOWN_BLK_CACHE_ARRAY_SIZE) &&
                        (Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 < Fee_FlashProp_st[Fee_LLSectorOrder_st[0].xPhySecIdx_u8].Fee_LogEndAddress_u32))
                    {
                        /* This is a new unknown block found, store at the next available location in the cache. */
                        Fee_UnknownBlkCache_Addr_au32[Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16]   = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;            /* Block header address */
                        Fee_UnknownBlkCache_FeeIndex_u16[Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16]     = Fee_GlobInfoLastRdHeader_st.FeeIndex_u16;  /* Fee index */

                        /* Increment the index to next location in cache */
                        Fee_RdWrOrder_st.Fee_UnknownBlkCacheIdx_u16++;
                    }
                    else
                    {
                        /* This place is reached only when:
                         *  1. The cache for unknown block is full i.e., there are more unknown blocks and its details cant be remembered or
                         *  2. All the unknown blocks of the oldest sector are scanned.
                         * In the first case, cache must be build for the remaining area of the sector after all the current blocks are transfered.
                         * In the second case, no more cache building is required. */
                    }

                    /* Continue with the search for the next unknown block and cache build up. */
                    Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_READ_E;

                }
                break;

                /* Found unknown block copy was invalid, skip this copy and continue the search. */
                case FEE_ERROR_E:
                {
                    Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_READ_E;
                }
                break;

                /* Error cases */
                case FEE_SECTORFULL_E:
                case FEE_SEARCH_ABORTED_E:
                case FEE_ABORTED_E:
                default:
                {
                    /* States should never be reached */
                    xRetVal = FEE_ERROR_E;
                }
                break;
            }/* End of switch case of Fee_LLCalcBlkCrcInFlash */
        }
        break;
        default:
        {
            break;
        }
    }/*End of switch case */

    /* Check if the search was aborted or the sector is full */
    if (xRetVal != FEE_ORDER_PENDING_E)
    {
        /* No valid block header found yet, reset the state machine */
        Fee_RdWrOrder_st.Fee_LLBuildUpCacheUnknownBlk_en = FEE_LL_BLD_UP_CACHE_UNKOWN_BLK_INIT_E;
    }

    return(xRetVal);

}
#endif /* End of (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE == 0) */
#endif /* End of ((FEE_RB_ACT_SURVIVAL_EVAL != FALSE) || (FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE)) */

/**
 *********************************************************************
 * Fee_LLSearchNextBlkHeader(): Search for the next block header
 *                              within one sector
 *
 * This function searches for the next block header within one sector.
 * Therefore the internal page buffer Fee_llPageBuf_au32 is used. If only the
 * erase pattern is found within the page buffer, the rest of the
 * sector is assumed to be empty. The function searches not until the
 * very end of the respective sector.
 *
 * \param    Fee_GlobInfoLastRdHeader_ptr: Pointer to headers structure
 * \param    CachedAccess_boolean:    TRUE:   Cached access
 *                                    FALSE:  "Manual search"
 * \param    FastCacheUpdate_boolean: TRUE:   Update cache if an index
 *                                            is found
 *                                    FALSE:  Do not update the cache
 * \param    xForcePageBufReload_b:   TRUE:   The page buffer will be
 *                                            reloaded
 *                                    FALSE:  The page buffer will only
 *                                            be reloaded if necessary
 *
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Order is pending
 * \retval   FEE_ABORTED_E:         Order was aborted
 * \retval   FEE_SECTORFULL_E:      The end of the sector is reached
 * \retval   FEE_ERROR_E:           Cached access did not work or
 *                                  the default state was reached
 * \retval   FEE_ORDER_FINISHED_E:  Order is finished
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLSearchNextBlkHeader(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_ptr,
                                                           VAR(uint8, AUTOMATIC) CachedAccess_u8,
                                                           VAR(uint8, AUTOMATIC) FastCacheUpdate_u8,
                                                           VAR(boolean, AUTOMATIC) xForcePageBufReload_b,
														   VAR(uint32, AUTOMATIC) strAddrHdrSearch)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal = FEE_ORDER_PENDING_E;     /* Function return */

    #if ((FEE_HEADER_RECHECK_ACTIVE != FALSE) || (FEE_NO_FALLBACK_ACTIVE != FALSE))
    /* In case NoFallback is activated the last block header has to be stored until the NoFallback marker is evaluated */
    static Fee_BlkHeader_tst xCurrBlkHeader_st;                         /* Block header structure */
    static uint32 xBlkHeaderAdr_u32;                                    /* Address of the last block header */
    #else
    VAR(Fee_BlkHeader_tst, AUTOMATIC) xCurrBlkHeader_st;                /* Block header structure */
    #endif

    VAR(uint8, AUTOMATIC)           xPhySecIdx_u8;                      /* Physical sector index */
    VAR(uint8, AUTOMATIC)           xPhyWrSecIdx_u8;                    /* Physical sector index for the next write request */
    VAR(uint16, AUTOMATIC)          i_u16 = 0;                          /* Loop counter */
    VAR(uint16, AUTOMATIC)          xCalcCrc_u16 = 0;                   /* Block header CRC */
    VAR(uint32, AUTOMATIC)          xLoopInRamCounter_u32 = 0;          /* Loop counter */
    static uint16                   xNumBytes2Read_u16 = 0;             /* Bytes to read via Fls_Read */
    static boolean xPageBufReloaded_b = TRUE;                           /* Reloaded page buffer */
    static uint8 xCntRetry_u8 = FEE_MAX_RD_WR_COMP_RETRIES;             /* Retries for read */
    static uint8 xLoopReduction_u8 = 0;									/* Loop reduction counter */

    #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
    uint8 local_loop_u8;                                                /* Loop variable for checking page contents */
    uint32* Fee_PageBytePtr_pu32;                                       /* Temp pointer to read contents of page buffer. */
    #endif

    #if (FEE_PRV_DEBUGGING != FALSE)
    uint32 xTimeStart_u32 = 0;

    if(Eep_stMain == EEP_FIRSTINIT_INI)
    {
        Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderNum_u32++;
    }
    #endif
    if (strAddrHdrSearch != 0uL)
    {
        Fee_RdWrOrder_st.xRdAddress = strAddrHdrSearch;
    }
    /* Loop if function state is pending */
    do
    {
        /* Switch over state machine */
        switch(Fee_RdWrOrder_st.Fee_LLRdState_en)
        {
            /* Init state */
            case FEE_LL_INIT_READ_E:
            {
                /* Get index of the physical sector belonging to a read request */
                xPhySecIdx_u8   = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

                /* Get index of the physical sector belonging to a write request */
                xPhyWrSecIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

                /* Check if the user address is outside the active (logical) sector or behind the next
                 * write address (per definition the flash is empty behind the next write address if
                 * writing and reading is done in the same sector) */
                if((Fee_RdWrOrder_st.xRdAddress >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32 ) ||
                   ((Fee_RdWrOrder_st.xRdAddress >= Fee_RdWrOrder_st.xWrAddress) &&
                    (xPhySecIdx_u8 == xPhyWrSecIdx_u8)))
                {
                    /* Check if the read address is behind the active sector */
                    if(Fee_RdWrOrder_st.xRdAddress >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32)
                    {
                        /* Reset the address */
                        Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32;
                    }

                    /* Sector is full */
                    xRetVal = FEE_SECTORFULL_E;

                    /* Leave loop */
                    break;
                }

                /* Check if a reload via Fls is necessary or not */
                /* MR12 RULE 13.5 VIOLATION: Reload of buffer is required only when multiple conditions are not satisifed. */
                if((xForcePageBufReload_b == FALSE) &&
                   (Fee_RdWrOrder_st.AdrHdSearchStart_u32 != FEE_MAXUINT32) &&
                   (Fee_RdWrOrder_st.xRdAddress < ((Fee_RdWrOrder_st.AdrHdSearchStart_u32 + (uint32)FEE_LL_PAGEBUFFSIZE) - (uint32)xLoopReduction_u8)) &&
                   (Fee_RdWrOrder_st.xRdAddress >= Fee_RdWrOrder_st.AdrHdSearchStart_u32) &&
                   (xPhySecIdx_u8 == Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.AdrHdSearchStart_u32)))
                {
                    /* Reload is NOT necessary, indicate a still valid page buffer */
                    xPageBufReloaded_b = FALSE;

                    /* Evaluate the rest of the page buffer content */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_FINISHED_E;

                    /* Break in order to jump over the Fls_Read state */
                    break;
                }
                else
                {
                    /* Indicate a necessary reload */
                    xPageBufReloaded_b = TRUE;

                    /* Reset the start address for the search */
                    Fee_RdWrOrder_st.AdrHdSearchStart_u32 = Fee_RdWrOrder_st.xRdAddress;


                    /* Check for the necessity of a cached access */
                    if(CachedAccess_u8 == (uint8)FEE_USE_CACHED_ACCESS)
                    {
                        /* Cached access is possible, only read the necessary amount of data */
                        xNumBytes2Read_u16 = FEE_BLK_HEADER_SIZE;
                    }
                    else
                    {
                        /* Set default value for the number of bytes to read */
                        xNumBytes2Read_u16 = FEE_LL_PAGEBUFFSIZE;

                        /* 1. Check if the current sector has enough free pages left to fill the internal page buffer completely */
                        if((Fee_RdWrOrder_st.xRdAddress + (uint32)FEE_LL_PAGEBUFFSIZE) > Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32)
                        {
                           /* Reduce the number of bytes to read */
                           xNumBytes2Read_u16 = (uint16)((Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32 + 1u)-
                                                         Fee_RdWrOrder_st.xRdAddress);
                        }

                        /* 2. Check if reading of a complete page buffer exceeds the current write address */
                        if(((Fee_RdWrOrder_st.xRdAddress + (uint32)FEE_LL_PAGEBUFFSIZE) >= Fee_RdWrOrder_st.xWrAddress) &&
                           (xPhySecIdx_u8 == xPhyWrSecIdx_u8))
                        {
                           /* Reduce the number of bytes to read */
                           xNumBytes2Read_u16 = (uint16)(Fee_RdWrOrder_st.xWrAddress - Fee_RdWrOrder_st.xRdAddress);
                        }
                    }

                    /* Set next state in order to fill the page buffer with data from the flash */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_PAGE_E;
                }
            }
            /* No break to save time */

            /* Read a page */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_READ_PAGE_E:
            {
                /* Read the data from either the logical sector start address or the last known DFlash position of
                 * the requested block */
                if(Fls_Read(Fee_RdWrOrder_st.xRdAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xNumBytes2Read_u16) != E_NOT_OK)
                {
                    /* Set next state */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_WAIT_READ_PAGE_E;
                }
                else
                {
                    /* Fls did not accept the order due to wrong parameters or an internal busy state.
                     * Reset the state machine */
                    xRetVal = FEE_ABORTED_E;
                }
            }
            break;

            /* Wait for the read order to be finished */
            case FEE_LL_WAIT_READ_PAGE_E:
            {
                /* The next state will be set by the Fee_JobEndNotification () or
                 * Fee_JobErrorNotification() function automatically */

                /* Call the Fls main function manually */
                Fls_MainFunction();

                #if (STD_ON == FEE_POLLING_MODE)
                /* Use the FLS polling mechanism in order to reach the next state */
                Fee_CheckFlsJobResult();
                #endif
            }
            break;

            /* Error reaction for read error */
            case FEE_LL_READ_ERROR_E:
                /* Reset the complete read buffer */
                Fee_SrvMemSet8((uint8*)&Fee_PageBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, (uint32)FEE_LL_PAGEBUFFSIZE);

                /* Verify retry possibility */
                if(xCntRetry_u8 > 0u)
                {
                    /* Decrement retry possibilities */
                    xCntRetry_u8--;

                    /* Try again to call the Fls and perform the read procedure */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_PAGE_E;
                }
                else
                {
                    /* Reading failed somewhere in between the currently read flash area
                     * --> Cached access:    regular behaviour (switch over to manual read)
                     * --> Noncached access: Increment read address and repeat reading afterwards */
                    if(CachedAccess_u8 == FEE_USE_CACHED_ACCESS)
                    {
                        /* Error handling must be done by upper layer
                         * --> Current entry will be marked as temp invalid in the cache and a
                         *     manual search will be triggered starting at the beginning of the current
                         *     read sector */
                        xRetVal = FEE_ERROR_E;
                    }
                    else
                    {
                        /* Force a reload and start searching within the next area
                         * --> the formerly read flash area will not be used anymore,
                         *     data might get lost (no influence on cache and cache status) */
                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, xNumBytes2Read_u16, TRUE);

                        /* Reset state machine */
                        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                    }
                }
            break;

            /* Evaluate the content of the page buffer */
            case FEE_LL_READ_FINISHED_E:
            {
                /*
                 * Header overview:
                 *  +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
                 *  |            Preamble            |Blk Status|       FeeIndex      |     Block length    |     Header CRC16    |
                 *  +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
                 *  Preamble   : 0xA53C96 fix pattern
                 *  Blk Status : Contains information like security level, etc.
                 *  FeeIndex   : Block index
                 *  Block length: Block length without the header length
                 *  Header CRC16: CRC16 checksum over Preamble, Blk Status, Fee Index and Block length.
                 *                The start value is FEE_MARKER_PATTERN (0xCAFE)
                 *
                 *  Hint: A block header will always start at the beginning of a page.
                 */

                /* Check if a complete new page buffer was loaded */
                if(xPageBufReloaded_b == FALSE)
                {
                    /* Go on with the search within the same page buffer at the corresponding offset */
                    i_u16 = (uint16)((Fee_RdWrOrder_st.xRdAddress - Fee_RdWrOrder_st.AdrHdSearchStart_u32) / (uint32)FEE_PAGE_LEN);
                }
                else
                {
                    /* Reset the loop counter start value*/
                    i_u16 = 0u;

                    #if (FEE_PRV_DEBUGGING != FALSE)
                    Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderNumReload_u32++;
                    #endif
                }

                /* Set the loop counter end value to the temp value */
                xLoopInRamCounter_u32 = xNumBytes2Read_u16;

                /* Check for the page alignment of the loop counter */
                while((xLoopInRamCounter_u32 % (uint32)FEE_PAGE_LEN) != 0u)
                {
                    /* Increment address */
                    xLoopInRamCounter_u32++;
                }

                /* Copy the preamble out of the last 8 Bytes of the buffer */
                if(xLoopInRamCounter_u32 >= (uint32)FEE_LL_PAGEBUFFSIZE)
                {
                	/* Copy the preamble out of the last 8 Bytes of the buffer */
					Fee_LLCopyPageBuff2HeaderStart(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[xLoopInRamCounter_u32 - 8uL]);

					/* Check if the end of the buffer contains a preamble */
					if ((xCurrBlkHeader_st.Preamble_au8[2] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_2) &&
						(xCurrBlkHeader_st.Preamble_au8[1] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_1) &&
						(xCurrBlkHeader_st.Preamble_au8[0] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_0))
					{
						/* Set the loop reduction counter to the smallest supported page size. Otherwise only the first
						 * half out of the block header might be available inside the page buffer. */
						xLoopReduction_u8 = (uint8)FEE_BKL_HEADER_REDUCTION;
					}
                }

                /* Reduce the upper limit of the loop */
                xLoopInRamCounter_u32 -= xLoopReduction_u8;
                xLoopInRamCounter_u32 /= (uint32)FEE_PAGE_LEN;

                #if (FEE_PRV_DEBUGGING != FALSE)
                xTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
                #endif

                /* Loop over all pages inside the page buffer
                 * Hints:
                 * - a complete block header must be evaluated which are 14 bytes
                 *   (--> the upper limit for the search varies depending on the page size
                 *        in order to access only the buffer area)
                 * - also possible for the cached access, because the header information
                 *   will be located within the first two bytes */
                for(; i_u16 < xLoopInRamCounter_u32; i_u16++)
                {
                    /* Extract the preamble out of the page buffer and copy it to the block structure */
                    Fee_LLCopyPageBuff2HeaderStart(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[(i_u16 * (uint16)FEE_PAGE_LEN)]);

                    /* Compare the preamble of the block header byte - wise */
                    if ((xCurrBlkHeader_st.Preamble_au8[2] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_2) &&
                        (xCurrBlkHeader_st.Preamble_au8[1] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_1) &&
                        (xCurrBlkHeader_st.Preamble_au8[0] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_0))
                    {

                        /* For controllers with no Cache init, the last programmed page is identified here during the Next Free page identification.
                         * Set the last programmed address after the complete header. */
                        #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
                        if (Fee_stMain == FEE_POLLING_MODE_E)
                        {
                            Fee_RdWrOrder_st.LastProgrammedAddress_u32 = (uint32)(Fee_RdWrOrder_st.AdrHdSearchStart_u32 + (uint32)(i_u16 * (uint16)FEE_PAGE_LEN));
                        }
                        else
                        {
                            /* Software is running in Normal mode. it is not required to identify the last programmed page. */
                        }
                        #endif

                        /* Set the loop reduction counter to the smallest supported page size. Otherwise only the first
                         * half out of the block header might be available inside the page buffer. */
						xLoopReduction_u8 = (uint8)FEE_BKL_HEADER_REDUCTION;

						/* Extract the rest up to the Crc32 out of the page buffer and copy it to the block structure */
                        Fee_LLCopyPageBuff2HeaderMid(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[(i_u16 * (uint16)FEE_PAGE_LEN)]);

                        /* Read BIT7 and check if the block shall be considered or not.
						 * If this bit is set the block was written in plant and must be ignored from application. */
                        if((xCurrBlkHeader_st.BlkStatus_u8 & FEE_MASK_BIT7) == 0u)
						{
                            /* Check the block header CRC */
                            xCalcCrc_u16 = Crc_CalculateCRC16((uint8*)&Fee_PageBytePtr_cpu8[(i_u16 * (uint16)FEE_PAGE_LEN)],
                                                              (uint32)(FEE_BLK_HEADER_SIZE - 6u),
                                                              (uint16)FEE_MARKER_PATTERN,
                                                              FALSE);

                            /* Check the header consistency */
                            if(xCalcCrc_u16 == xCurrBlkHeader_st.HdrCrc16_u16)
                            {
                                /* This is a valid header. Nevertheless it is possible that this order was not finished correct
                                 * or that the block checksum is wrong. */

                                /* Extract the rest out of the page buffer and copy it to the block structure */
                                Fee_LLCopyPageBuff2HeaderEnd(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[(i_u16 * (uint16)FEE_PAGE_LEN)]);

                                /* Store the block header's start address to the global info structure */
                                Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32 = (uint32)(Fee_RdWrOrder_st.AdrHdSearchStart_u32 +
                                                                                          (uint32)(i_u16 * (uint16)FEE_PAGE_LEN));
                                Fee_GlobInfoLastRdHeader_ptr->FeeIndex_u16     = xCurrBlkHeader_st.FeeIndex_u16;
                                Fee_GlobInfoLastRdHeader_ptr->BlkStatus_u8     = xCurrBlkHeader_st.BlkStatus_u8;
                                Fee_GlobInfoLastRdHeader_ptr->BlkLength_u16    = xCurrBlkHeader_st.BlkLength_u16;
                                Fee_GlobInfoLastRdHeader_ptr->HdrCrc16_u16     = xCurrBlkHeader_st.HdrCrc16_u16;
                                Fee_GlobInfoLastRdHeader_ptr->BlkCrc32_u32     = xCurrBlkHeader_st.BlkCrc32_u32;

                                /* Check for an an init run because the special cache update without the evaluation
                                 * of the data checksum will be done in order to fasten up the system */
                                if(FastCacheUpdate_u8 == (uint8)FEE_UPDATE_CACHE_IN_INIT)
                                {
                                    /* Update the cache with the current header address */
                                    Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_ptr->FeeIndex_u16,
                                                               Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32);
                                }

                                /* Finish the order */
                                xRetVal = FEE_ORDER_FINISHED_E;

                                /* Finish the loop */
                                break;
                            }
						}
                    }
                    else
                    {
                        /* For controllers with no Cache init, the last programmed page is identified here during the Next Free page identification.
                         * Check if the page is blank or programmed by comparing against the erase pattern. */
                        #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
                        if (Fee_stMain == FEE_POLLING_MODE_E)
                        {
                            /* For faster operation, use 32 bytes compare. */
                            Fee_PageBytePtr_pu32 = (uint32*)Fee_PageBytePtr_cpu8;
                            local_loop_u8 = (i_u16 * (uint16)FEE_PAGE_LEN)/4u;
                            if((Fee_PageBytePtr_pu32[local_loop_u8] != FEE_ERASE_PATTERN_U32) ||
                               (Fee_PageBytePtr_pu32[(local_loop_u8 + 1u)] != FEE_ERASE_PATTERN_U32))
                            {
                                /* Page is not blank. Store the address of the page as last programmed page. */
                                Fee_RdWrOrder_st.LastProgrammedAddress_u32 = (uint32)(Fee_RdWrOrder_st.AdrHdSearchStart_u32 + (uint32)(i_u16 * (uint16)FEE_PAGE_LEN));
                            }
                            else
                            {
                                /* Page is blank. Continue to identify the last programmed page. */
                            }
                        }
                        else
                        {
                            /* Software is running in Normal mode. it is not required to identify the last programmed page. */
                        }
                        #endif

                        /* Page contains no block header (missing preamble)
                         * --> search within the next page that has already been loaded
                         *     or leave the loop in case this was a cached access */
                        if(CachedAccess_u8 == (uint8)FEE_USE_CACHED_ACCESS)
                        {
                            /* MR12 RULE 15.4 VIOLATION: Save time */
                            break;
                        }
                    }
                }


                #if (FEE_PRV_DEBUGGING != FALSE)
                Fee_Prv_stModuleTest_st.Fee_SearchNextBlockHeaderLoopRamDiff_u32 +=
                        MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) - xTimeStart_u32);
                #endif


                /* Check whether a valid block header has been found or not */
                if (xRetVal != FEE_ORDER_FINISHED_E)
                {
                    /* A complete page buffer (or a some pages only in case of a cached access)
                     * contain(s) no valid block header. The start address
                     * for this search was either the sector beginning or a pointer out of
                     * the last valid block header (or the address out of the cache). */

                    /* No abortion, go on until the end of the sector is reached unless it
                     * was a cached access */
                    if(CachedAccess_u8 == (uint8)FEE_USE_MANUAL_ACCESS)
                    {
                        /* No valid block header was found, increment address for next search. */

                        /* Set the read address for the next page buffer reload by the Fls right
                         * behind the end of the last loaded address area -1 page
                         * (The last page of the buffer was not evaluated because only complete
                         *  block headers can be checked (14 bytes)
                         *  --> do not skip this page but force a check).
                         * Ensure page alignment and keep the address within the current sector
                         * If the end of the sector is reached, the function will restrict the
                         * read address to the sector end address which will lead to a sector
                         * full return in the init read state */

                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress,
                                                   (uint16)(((Fee_RdWrOrder_st.AdrHdSearchStart_u32 +
                                                              (uint32)FEE_LL_PAGEBUFFSIZE) -
                                                             Fee_RdWrOrder_st.xRdAddress) -
                                                            (uint32)xLoopReduction_u8),
                                                   TRUE);

                        /* Reset state machine */
                        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                    }
                    else
                    {
                        /* Cache address is not correct */
                        xRetVal = FEE_ERROR_E;
                    }
                }
                #if (FEE_HEADER_RECHECK_ACTIVE != FALSE)
                /* The NoFallback feature can be activated only if header recheck is activated */
                else
                {
                    /* If the function is called during init additional checks are skipped */
                    if (FastCacheUpdate_u8 != (uint8)FEE_UPDATE_CACHE_IN_INIT)
                    {
                        #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                        /* A valid block header has been found
                         * --> check if the block is configured as NoFallback */
                        if ((Fee_GlobInfoLastRdHeader_ptr->BlkStatus_u8 & (uint8)FEE_FLAG_NOFALLBACK_MSK) > 0)
                        {
                            /* The block shall be considered only if the NoFallback marker is not written
                             * -> perform a blank check over the NoFallback marker area */
                            Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_NOFALLBACK_MARKER_CHECK_E;
                        }
                        else
                        #endif
                        {
                            Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_RECHECK_HEADER_E;
                        }

                        /* Store the block header's start address separately since it is not part of the local structure */
                        xBlkHeaderAdr_u32 = Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32;

                        /* The order is finished only if the NoFallback marker has been checked */
                        xRetVal = FEE_ORDER_PENDING_E;
                    }
                }
                #endif
            }
            break;

            #if (FEE_HEADER_RECHECK_ACTIVE != FALSE)
            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            case FEE_LL_NOFALLBACK_MARKER_CHECK_E:
            {
                /* Call the blank check function */
                if (Fls_Rb_BlankCheck(xBlkHeaderAdr_u32 - FEE_PAGE_LEN, NULL_PTR, FEE_PAGE_LEN) != E_NOT_OK)
                {
                    /* Set the next state */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_NOFALLBACK_MARKER_CHECK_WAIT_E;
                }
                else
                {
                    /* Fls did not accept the order due to wrong parameters or an internal busy state.
                     * Reset the state machine */
                    xRetVal = FEE_ABORTED_E;
                }
            }
            break;
            /* FEE_NO_FALLBACK_ACTIVE != FALSE */
            #endif

            case FEE_LL_RECHECK_HEADER_E:
            {
                /* Call the blank check function */
                if (Fls_Rb_BlankCheck(xBlkHeaderAdr_u32 + ((FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN) - FEE_PHY_PAGE_LEN),
                                      NULL_PTR,
                                      FEE_PHY_PAGE_LEN) != E_NOT_OK)
                {
                    /* Set the next state */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_RECHECK_HEADER_WAIT_E;
                }
                else
                {
                    /* Fls did not accept the order due to wrong parameters or an internal busy state.
                     * Reset the state machine */
                    xRetVal = FEE_ABORTED_E;
                }
            }
            break;

            /* Wait for the blank check to be finished */
            case FEE_LL_RECHECK_HEADER_WAIT_E:
            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            case FEE_LL_NOFALLBACK_MARKER_CHECK_WAIT_E:
            #endif
            {
                /* The next state will be set by the Fee_JobEndNotification() or Fee_JobErrorNotification() function automatically */

                /* Check whether the OS is currently running or not */
                if (Fee_stMain == FEE_POLLING_MODE_E)
                {
                    /* Call the Fls main function manually */
                    Fls_MainFunction();
                }

                #if (STD_ON == FEE_POLLING_MODE)
                /* Use the FLS polling mechanism in order to reach the next state */
                Fee_CheckFlsJobResult();
                #endif
            }
            break;

            /* Reading of the block is allowed since
             * - the NoFallback marker for NoFallback blocks is not programmed
             * - the block header is fully programmed */
            case FEE_LL_RECHECK_HEADER_FINISHED_E:
            {
                /* Store the block header information to the global info structure */
                Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32 = xBlkHeaderAdr_u32;
                Fee_GlobInfoLastRdHeader_ptr->FeeIndex_u16     = xCurrBlkHeader_st.FeeIndex_u16;
                Fee_GlobInfoLastRdHeader_ptr->BlkStatus_u8     = xCurrBlkHeader_st.BlkStatus_u8;
                Fee_GlobInfoLastRdHeader_ptr->BlkLength_u16    = xCurrBlkHeader_st.BlkLength_u16;
                Fee_GlobInfoLastRdHeader_ptr->HdrCrc16_u16     = xCurrBlkHeader_st.HdrCrc16_u16;
                Fee_GlobInfoLastRdHeader_ptr->BlkCrc32_u32     = xCurrBlkHeader_st.BlkCrc32_u32;

                /* Finish the order */
                xRetVal = FEE_ORDER_FINISHED_E;
            }
            break;

            /* If the NoFallback marker area is not blank reading of the block is not allowed */
            case FEE_LL_RECHECK_HEADER_FAILED_E:
            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            case FEE_LL_NOFALLBACK_MARKER_CHECK_FAILED_E:
            #endif
            {
                if (CachedAccess_u8 == (uint8)FEE_USE_MANUAL_ACCESS)
                {
                    /* Update the read address to the last found block header */
                    Fee_RdWrOrder_st.xRdAddress = xBlkHeaderAdr_u32;

                    /* Increment the read address page wise ("safety mode") and search for the next
                     * block header until the end of the page buffer */
                    Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, FEE_PAGE_LEN, TRUE);

                    /* Reset the state machine and continue the search */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                }
                else
                {
                    /* Cache address is not correct */
                    xRetVal = FEE_ERROR_E;
                }
            }
            break;
            /* FEE_HEADER_RECHECK_ACTIVE != FALSE */
            #endif

            /* Default case should never be reached */
            default:
            {
                /* Set error state */
                xRetVal = FEE_ERROR_E;

                /* No valid block header found yet, reset the state machine */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
            }
            break;
        }
    }
    while((xRetVal == FEE_ORDER_PENDING_E) && (Fee_stMain == FEE_POLLING_MODE_E));

    /* Check if the search was aborted or the sector is full */
    if (xRetVal != FEE_ORDER_PENDING_E)
    {
        /* No valid block header found yet, reset the state machine */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;

        /* Reset the loop reduction counter */
        xLoopReduction_u8 = 0u;

        /* Reset retry counter */
        xCntRetry_u8 = (uint8)FEE_MAX_RD_WR_COMP_RETRIES;
    }

    return(xRetVal);
}


/**
 *********************************************************************
 * Fee_LLGetSecStartAddress(): Return sector start address
 *
 * This function returns the start address of the requested sector.
 *
 * Hint: It might be necessary to return the address of the first
 *       block header within the requested sector in the future.
 *       In this case this address might be read out of a new sector
 *       header.
 *
 * \param    xPhySectorIdx_u8:  Active sector index
 * \return
 * \retval   0...4294967295:    Start address of the first page
 *                              of the active sector
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_LLGetSecStartAddress(VAR(uint8, AUTOMATIC) xPhySectorIdx_u8)
{
    /* Access flash property table */
    return(Fee_FlashProp_st[xPhySectorIdx_u8].Fee_LogStartAddress_u32);
}


/**
 *********************************************************************
 * Fee_LLGetSecEndAddress(): Return sector end address
 *
 * This function returns the end address of the requested sector.
 *
 *
 * \param    xPhySectorIdx_u8:  Active sector index
 * \return
 * \retval   0...4294967295:    End address of the sector
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_LLGetSecEndAddress(VAR(uint8, AUTOMATIC) xPhySectorIdx_u8)
{
    /* Access flash property table */
    return(Fee_FlashProp_st[xPhySectorIdx_u8].Fee_LogEndAddress_u32);
}


/**
 *********************************************************************
 * Fee_LLGetAddressFromCache(): Find address in flash
 *
 * This functions returns the address of the corresponding block
 * header.
 *
 * \param    FeeIdx_u16:    Fee index (block persistent ID)
 * \return
 * \retval   addr_u32:      Address in flash if persistent ID is
 *                          configured
 * \retval   FEE_CACHE_INIT_VALUE: block is not configured
 * \retval   FEE_CACHE_TMP_INVALID_VALUE: block is configured but
 *                          address within cache is not valid
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_LLGetAddressFromCache(VAR(uint16, AUTOMATIC) FeeIdx_u16)
{
    VAR(uint16, AUTOMATIC) xCacheIdx_u16;                   /* Cache index */
    VAR(uint32, AUTOMATIC) addr_u32 = FEE_CACHE_INIT_VALUE; /* Return value */

    /* Check if the index can be found */
    if(Fee_SrvBinarySearchInBlockProp(FeeIdx_u16, &xCacheIdx_u16) != FALSE)
    {
        /* Set return value */
        addr_u32 = Fee_Cache_au32[xCacheIdx_u16];
    }

    /* Check if the cache entry is within any of the configured sectors */
    if(Fee_LLCheckAddressInCache(addr_u32) == FALSE)
    {
        /* Return the temp init value */
        addr_u32 = FEE_CACHE_TMP_INVALID_VALUE;
    }

    /* Return the block address */
    return (addr_u32);
}


/**
 *********************************************************************
 * Fee_LLCheckHdAddressInCache(): Validate the cache address
 *
 * This functions checks if a header address is within any of the
 * configured flash sectors.
 *
 * \param    AdrInSector_u32:   Address to check
 * \return
 * \retval   TRUE:              Address is valid
 * \retval   FALSE:             Address is invalid
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(boolean, FEE_CODE) Fee_LLCheckAddressInCache(VAR(uint32, AUTOMATIC) AdrInSector_u32)
{
    VAR(boolean, AUTOMATIC) xRetVal_b = FALSE;      /* Default return value */
    VAR(uint8, AUTOMATIC)   xPhySecIdx_u8;          /* Loop counter */
    VAR(uint8, AUTOMATIC)   xLogSecIdx_u8;          /* Logical sector index */

    /* Check for the cache init value or the temp init value first */
    if((AdrInSector_u32 != FEE_CACHE_INIT_VALUE) &&
       (AdrInSector_u32 != FEE_CACHE_TMP_INVALID_VALUE))
    {
        /* Loop over all configured flash banks */
        for(xPhySecIdx_u8=0; xPhySecIdx_u8<FEE_NUM_FLASH_BANKS; xPhySecIdx_u8++)
        {
            uint32 secStartAddr_u32 , secEndAddr_u32;
            /* Check if the address is within one of the configured sectors.
             * Low check:   logical sector start address
             * Upper check: logical sector end address - block header size */

            secStartAddr_u32 = Fee_LLGetSecStartAddress(xPhySecIdx_u8);
            secEndAddr_u32   = Fee_LLGetSecEndAddress(xPhySecIdx_u8);

            /* MR12 RULE 13.5 VIOLATION: Both upper and lower boundary checks are required. */
            if((secStartAddr_u32 <= AdrInSector_u32) &&
               (((secEndAddr_u32 + 1uL) - (FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN)) >= AdrInSector_u32))
            {
                    /* Get the respective logical sector index */
                    xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

                    /* Cross check the sector state */
                    if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                       (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                    {
                        /* Address successfully verified */
                        xRetVal_b = TRUE;
                    }

                    /* Exit loop */
                    break;
               }
        }
    }
    else
    {
        /* Defined values are allowed */
        xRetVal_b = TRUE;
    }

    /* Function return */
    return (xRetVal_b);
}


/**
 *********************************************************************
 * Fee_LLUpdateCacheStForSect(): Indicate a physical sector as
 *                                checked (cache update complete)
 *
 * This function updates the respective physical sector as completed
 * with respect to the cache entries.
 *
 * \param    PhySecIdx_u8:  Physical sector index
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLUpdateCacheStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8)
{
    /* Update the array indicator for a completed cache update for one sector */
    Fee_CacheUpdCompForSect_au8[PhySecIdx_u8] = FEE_CACHE_UPD_COMP_FOR_SECT;
}

/**
 *********************************************************************
 * Fee_LLEraseCacheStForSect():  Erase checked indication for the
 *                               cache status
 *
 * This function erases the checked indication of the respective
 * physical sector.
 *
 * \param    PhySecIdx_u8:  Physical sector index
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLEraseCacheStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8)
{
    /* Update the array indicator for a completed cache update for one sector */
    Fee_CacheUpdCompForSect_au8[PhySecIdx_u8] = FEE_CACHE_UPD_NOT_COMP_FOR_SECT;
}


/**
 *********************************************************************
 * Fee_LLGetCacheUpdateStForAllSect(): Get the status summary of the
 *                                     cache updates of all sectors
 *
 * This function returns whether a all relevant sectors have been
 * used for updating the cache or not. Currently relevant are only
 * USED or FULL sectors.
 *
 * \param    none
 * \return   Cache update status
 * \retval   FEE_CACHE_UPD_COMP_FOR_ALL_SECT: All sectors have been
 *                                            checked
 * \retval   FEE_CACHE_UPD_NOT_COMP_FOR_SECT: At least one sector was
 *                                            not checked
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint8, FEE_CODE) Fee_LLGetCacheUpdateStForAllSect(void)
{
    VAR(uint8, AUTOMATIC)  xFuncRet_u8 = FEE_CACHE_UPD_COMP_FOR_ALL_SECT;
    VAR(uint8, AUTOMATIC)  xLogSecIdx_u8;               /* Logical sector index */
    VAR(uint8, AUTOMATIC)  xPhySecIdx_u8;               /* Physical sector index */

    /* Loop over all sectors */
    for(xPhySecIdx_u8=0; xPhySecIdx_u8<FEE_NUM_FLASH_BANKS; xPhySecIdx_u8++)
    {
        /* Get the corresponding logical sector index */
        xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

        /* Check if all relevant sectors have been checked so far */
        /* MR12 RULE 13.5 VIOLATION: Checking state of cache for the sector required only for sectors that are in USED or FULL state. */
        if(((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
            (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E)) &&
           (Fee_LLGetCacheUpdateStForSect(xPhySecIdx_u8) != FEE_CACHE_UPD_COMP_FOR_SECT))
        {
            xFuncRet_u8 = FEE_CACHE_UPD_NOT_COMP_FOR_SECT;
        }
    }

    return xFuncRet_u8;
}


/**
 *********************************************************************
 * Fee_LLUpdateAddressInCache(): Update the address within the cache
 *
 * This functions updates the address of the corresponding block
 * in the cache.
 *
 * \param    FeeIdx_u16:    Fee index (block persistent ID)
 * \param    Addr_u32:      Address in flash
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLUpdateAddressInCache(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                VAR(uint32, AUTOMATIC) Addr_u32)
{
    VAR(uint16, AUTOMATIC) xCacheIdx_u16;   /* Cache index */

    /* Check if the index can be found */
    if(Fee_SrvBinarySearchInBlockProp(FeeIdx_u16, &xCacheIdx_u16) != FALSE)
    {
        /* Update the address within the cache */
        Fee_Cache_au32[xCacheIdx_u16] = Addr_u32;
    }
}


/**
 *********************************************************************
 * Fee_LLGetCacheUpdateStForSect(): Get the status of the cache update
 *                                  of the respective sector
 *
 * This function returns whether a complete search through the
 * respective sector in combination with a cache update has already
 * been performed or not.
 *
 * \param    PhySecIdx_u8:  Physical sector index
 * \return   Cache update status for the physical sector
 * \retval   FEE_CACHE_UPD_COMP_FOR_SECT:     The respective sector was
 *                                            checked completely
 * \retval   FEE_CACHE_UPD_NOT_COMP_FOR_SECT: The respective sector was
 *                                            not completely checked
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(uint8, FEE_CODE) Fee_LLGetCacheUpdateStForSect(VAR(uint8, AUTOMATIC) PhySecIdx_u8)
{
    /* Return the status of the physical sector */
    return Fee_CacheUpdCompForSect_au8[PhySecIdx_u8];
}


/* Macro implementation for an invalidation of the cache can be found in Fee_Prv.h:
 * #define Fee_LLInvalidateAddressInCache(FEEIDX)   Fee_LLUpdateAddressInCache(FEEIDX, FEE_CACHE_INIT_VALUE) */


#if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
/**
 *********************************************************************
 * Fee_BuildUpCache(): Build up the cache for the passed address area
 *
 * This function builds up the cache for the address area passed
 * by the user. The block checksum can be regarded if necessary.
 * The function can execute one sector without returning in case
 * this is necessary (e.g. during the ECU init).
 *
 * \param    StartAdr_u32:      Start address for the search
 * \param    EndAdr_u32:        End address for the search
 *
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Order is pending
 * \retval   FEE_ABORTED_E:         Order was aborted
 * \retval   FEE_SECTORFULL_E:      The end address of the sector
 *                                  was reached
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCache(VAR(uint32, AUTOMATIC) StartAdr_u32,
                                                  VAR(uint32, AUTOMATIC) EndAdr_u32)
{
    uint8 xLogSecIdx_u8;                        /* Index of logical sector */
    uint8 xPhySecIdx_u8;                        /* Index of physical sector */
    uint16 xCalcCrc_u16;                        /* Header checksum */
    Fee_BlkHeader_tst xCurrBlkHeader_st;        /* Block header structure */
    uint32 xRdAdr_u32;                          /* Address for reading */
    uint32 xRdAdrEnd_u32;                       /* End address for reading */
    uint16 xBlockPropIdx_u16;                   /* Block index */
    uint16 xCacheIdx_u16 = 0;                       /* Cache index */
    uint32 xAdrBlkHeaderTmp_u32;                /* Temporary block header address */
    uint32 xDataBuf_au32[(FEE_PAGES_USED_BY_BLK_HEADER*FEE_PAGE_LEN)/4u];    /* Data buffer */
    Fee_stRetVal_ten xRetVal = FEE_ORDER_PENDING_E;  /* Function return */
    #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) ) /* Local varaibles are used to save computation time. */
    uint8 xActivateLastPgmSearch_u8 = 0;        	/* Flag to indicate if searching of last programmed page must be done for the sector or not. */
    uint32 xLastProgrammedAddress_u32 = FEE_NULL; 	/* Local variable to store the address of the last programmeed page. */
    uint32 xLastValidHeader_u32 = FEE_NULL;     	/* Local variable to store the address of the last valid header. */
	#else
    uint32 const xHdrCutOff_cu32 = (FEE_PAGE_LEN * (FEE_PAGES_USED_BY_BLK_HEADER - 1u)); /* Possible cutoff before write address where no valid header can be located */
    #endif

    static uint32 xRdAdrContinue_u32;           /* Address to continue the reading */
    static uint32 xRdAdrEndContinue_u32;        /* End address for the search */

    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over state machine */
        switch (Fee_RdWrOrder_st.Fee_LLBuildUpCache_en)
        {
            /* Init state */
            case FEE_LL_BLD_UP_CACHE_INIT_E:
            {
                /* Get the corresponding sector indexes */
                xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(StartAdr_u32);
                xLogSecIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySecIdx_u8];

                /* Loop over all configured blocks */
                for(xBlockPropIdx_u16=0; xBlockPropIdx_u16<FEE_NUM_BLOCKS; xBlockPropIdx_u16++)
                {
                    /* Check the address range */
                    if((Fee_Cache_au32[xBlockPropIdx_u16] >= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogStartAddress_u32) &&
                       (Fee_Cache_au32[xBlockPropIdx_u16] <= Fee_FlashProp_st[xPhySecIdx_u8].Fee_LogEndAddress_u32))
                    {
                        /* Clean all cache entries referring to this sector */
                        Fee_LLInvalidateAddressInCache(xBlockPropIdx_u16);
                    }
                }

                /* Check if building up the cache is necessary */
                if((Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                   (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                {
                    /* Read out the data */
                    Fee_RdWrOrder_st.Fee_LLBuildUpCache_en = FEE_LL_BLD_UP_CACHE_READ_E;

                    /* Copy the user's start and end addresses */
                    xRdAdrContinue_u32      = StartAdr_u32;
                    xRdAdrEnd_u32           = xRdAdrContinue_u32;
                    xRdAdrEndContinue_u32   = xRdAdrEnd_u32;

                    /* Update the cache status for the current sector  */
                    Fee_LLUpdateCacheStForSect(xPhySecIdx_u8);

                    #if (FEE_PRV_DEBUGGING != FALSE)
                    Fee_Prv_stModuleTest_st.Fee_CacheCntSect_u8++;
                    Fee_Prv_stModuleTest_st.BuildUpCacheStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
                    #endif

                    #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
                    /* Initialise the flag and address variables. */
                    xActivateLastPgmSearch_u8 = 0;
    				xLastProgrammedAddress_u32 = FEE_NULL;
    				xLastValidHeader_u32 = FEE_NULL;

                    /* Check for last programmed page only for most active sector i.e., sector state = FEE_SECTOR_USED_E. */
                    if (Fee_LLSectorOrder_st[xLogSecIdx_u8].SecState_en == FEE_SECTOR_USED_E)
                    {
                        /* Set the flag to activate the check of last programmed page. */
                        xActivateLastPgmSearch_u8 = 1;
                    }
					else
					{
						/* Identification of last programmed header and page is required only for the lastest valid sector i.e., sector with USED state.
						 * Do nothing for all other sectors. */
					}
                    #endif
                }
                else
                {
                    /* Set return value */
                    xRetVal = FEE_ABORTED_E;

                    break;
                }
            }
            /* No break to save time */

            /* Read out data */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_BLD_UP_CACHE_READ_E:
            {
                /* Get the addresses for reading the data
                 * (use locals for faster access) */
                xRdAdr_u32      = xRdAdrContinue_u32;
                xRdAdrEnd_u32   = xRdAdrEndContinue_u32;

                /* Check if the end address for the search is already reached
                 * because of jumps after the checksum verification */
                if(xRdAdr_u32 >= Fee_LLGetSecEndAddress(Fee_GetPhysSectorByAddress(xRdAdr_u32)))
                {
                    /* Finish the order */
                    xRetVal = FEE_SECTORFULL_E;

                    break;
                }

                /* Set the end address for the search depending on the mode
                 * --> Use the fast mode during the init phase */
                if(Fee_Prv_stInit_u8 != FEE_PRV_ST_INIT_DONE)
                {
                    #if (defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH))
                    uint8 endAddrSector_u8 , wrAddrSector_u8;

                    endAddrSector_u8 = Fee_GetPhysSectorByAddress(EndAdr_u32);
                    wrAddrSector_u8  = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

                    /* Check if the users end address exceeds the current write address */
                    if((EndAdr_u32 >= Fee_RdWrOrder_st.xWrAddress) &&
                       (endAddrSector_u8 == wrAddrSector_u8))
                    {
                        if(Fee_RdWrOrder_st.xWrAddress <= (Fee_LLGetSecStartAddress(Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress)) + xHdrCutOff_cu32))
                        {
                            /*
                             * Two cases are possible:
                             * 1. Only the USED marker is available but no data!
                             * 2. Only a partial programmed header page is available
                             * In both the cases it cannot be a valid block which shall be put into the cache.
                             */
                            xRetVal = FEE_SECTORFULL_E;
                            break;
                        }
                        else
                        {
                            /*
                             * Write address before or equal to sector end - limit scan to write address
                             * Even if the last page before the write address contains a valid preamble it cannot be a valid header.
                             * At the very last part before the write address (xHdrCutOff) there can be no valid header anymore.
                             * Do not check this in order to avoid reading of erased area (see below do while abort condition).
                             */
                            xRdAdrEnd_u32 = (Fee_RdWrOrder_st.xWrAddress - xHdrCutOff_cu32);
                        }
                    }
                    else
                    #endif
                    {
                        /* Take over the users end address */
                        xRdAdrEnd_u32 = EndAdr_u32;
                    }
                }
                else
                {
                    /* Do the read out DataBuf size wise */

                    /* Check if an increase of the end address is necessary again */
                    if(xRdAdr_u32 == xRdAdrEnd_u32)
                    {
                        /* Reset the current loop end */
                        Fee_IncAddressInsideSector(&xRdAdrEnd_u32, FEE_LL_DATABUFFSIZE, TRUE);

                        /* Check if the user's end address is exceeded */
                        if(xRdAdrEnd_u32 > EndAdr_u32)
                        {
                            /* Restrict the end address */
                            xRdAdrEnd_u32 = EndAdr_u32;
                        }
                    }
                }

                /* Loop until the end address is reached */
                do
                {
                    /* Read out the preamble and the block status directly */
                    /* MISRA RULE 11.3 VIOLATION: Cast is necessary and not critical */
                    (void)Fee_Fls_SyncRead(xRdAdr_u32, (uint8*)&xDataBuf_au32[0], (Fls_LengthType)4U);


                    /*
                     * Header overview:
                     *  +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
                     *  |            Preamble            |Blk Status|       FeeIndex      |     Block length    |     Header CRC16    |
                     *  +----------+----------+----------+----------+----------+----------+----------+----------+----------+----------+
                     *  Preamble   : 0xA53C96 fix pattern
                     *  Blk Status : Contains information like security level, etc.
                     *  FeeIndex   : Block index
                     *  Block length: Block length without the header length
                     *  Header CRC16: CRC16 checksum over Preamble, Blk Status, Fee Index and Block length.
                     *                The start value is FEE_MARKER_PATTERN (0xCAFE)
                     *
                     *  Hint: A block header will always start at the beginning of a page.
                     */

                    /* Compare the preamble of the block header byte - wise */
                    /* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
                    if ((((Fee_BlkHeader_tst*)(&xDataBuf_au32[0]))->Preamble_au8[2] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_2) &&
                        /* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
                        (((Fee_BlkHeader_tst*)(&xDataBuf_au32[0]))->Preamble_au8[1] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_1) &&
                        /* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
                        (((Fee_BlkHeader_tst*)(&xDataBuf_au32[0]))->Preamble_au8[0] == (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_0))
                    {

                        /* Load the last programmed page for controllers other then R1x and P1x. */
                        #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
                        if (xActivateLastPgmSearch_u8 == 1)
                        {
                            xLastProgrammedAddress_u32 = xRdAdr_u32;
                        }
						else
						{
							/* Identification of last programmed header and page is required only for the lastest valid sector i.e., sector with USED state.
							 * Do nothing for all other sectors. */
						}
                        #endif

                        /* Save the start address for updating the cache */
                        xAdrBlkHeaderTmp_u32 = xRdAdr_u32;

                        /* Read out the block index and the block length */
                        Fee_IncAddressInsideSector(&xRdAdr_u32 , 4u , FALSE);

                        /* MISRA RULE 11.3 VIOLATION: Cast is necessary and not critical */
                        (void)Fee_Fls_SyncRead(xRdAdr_u32, (uint8*)&xDataBuf_au32[1], (Fls_LengthType)4U);


                        /* Read out the header CRC and parts of the block CRC */
                        Fee_IncAddressInsideSector(&xRdAdr_u32 , 4u , FALSE);

                        /* MISRA RULE 11.3 VIOLATION: Cast is necessary and not critical */
                        (void)Fee_Fls_SyncRead(xRdAdr_u32, (uint8*)&xDataBuf_au32[2], (Fls_LengthType)4U);

                        /* Read BIT7 and check if the block shall be considered or not.
                        * If this bit is set the block was written in plant and must be ignored from application. */

						/* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
						if((((Fee_BlkHeader_tst*)(&xDataBuf_au32[0]))->BlkStatus_u8 & FEE_MASK_BIT7) == 0u)
						{
						    /* Check the block header CRC */
						    /* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
						    xCalcCrc_u16 = Crc_CalculateCRC16((uint8*)&xDataBuf_au32[0],
                                                              (uint32)(FEE_BLK_HEADER_SIZE - 6u),
                                                              (uint16)FEE_MARKER_PATTERN,
                                                              FALSE);

                            /* Extract the header checksum out of the page buffer and copy it to the block structure */
                            /* MR12 RULE 11.3 VIOLATION: Cast is necessary and not critical */
                            Fee_LLCopyPageBuff2HeaderIdxAndCrc(&xCurrBlkHeader_st, (const uint8*) &xDataBuf_au32[0]);

                            /* Check the header consistency */
                            if (xCalcCrc_u16 == xCurrBlkHeader_st.HdrCrc16_u16)
                            {
                                /* Load the last valid header address (known or unknown block). */
                                #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
                                if (xActivateLastPgmSearch_u8 == 1)
                                {
                                    xLastValidHeader_u32 = xAdrBlkHeaderTmp_u32;
                                }
                                else
                                {
                                    /* Identification of last programmed header and page is required only for the lastest valid sector i.e., sector with USED state.
                                     * Do nothing for all sectors. */
                                }
                                #endif

                                /* Check if the index can be found */
                                if (Fee_SrvBinarySearchInBlockPropFast(xCurrBlkHeader_st.FeeIndex_u16,
                                        &xCacheIdx_u16) != FALSE)
                                {
                                    /* Update the address within the cache */
                                    Fee_Cache_au32[xCacheIdx_u16] = xAdrBlkHeaderTmp_u32;
                                }
                            }
                        }
                    }
                    else
                    {
                        /* Load the last programmed page for controllers other then R1x and P1x. */
                        #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
                        if (xActivateLastPgmSearch_u8 == 1)
                        {
                            /* Direct read from memory is time consuming. Hence, reuse the first 4 bytes information that was already read earlier. */
                            if (xDataBuf_au32[0] != FEE_ERASE_PATTERN_U32)
                            {
                                /* Copy the address to a local variable for faster execution. */
                                xLastProgrammedAddress_u32 = xRdAdr_u32;
                            }
                            else
                            {
                                /* Extract the next 4 bytes of the page. */

                                /* MISRA RULE 11.3 VIOLATION: Cast is necessary and not critical */
                                (void)Fee_Fls_SyncRead(xRdAdr_u32 + 4, (uint8*)&xDataBuf_au32[1], (Fls_LengthType)4U);

                                if (xDataBuf_au32[1] != FEE_ERASE_PATTERN_U32)
                                {
                                    /* Copy the address to a local variable for faster execution. */
                                    xLastProgrammedAddress_u32 = xRdAdr_u32;
                                }
                                else
                                {
                                    /* The page is blank. do nothing. */
                                }
                            }
                        }
                        else
                        {
                            /* Identification of last programmed header and page is required only for the lastest valid sector i.e., sector with USED state.
                             * Do nothing for all sectors. */
                        }
                        #endif

                        /* Just go on until the end address is reached,
                         * the next header can only start at the next page */
                        Fee_IncAddressInsideSector(&xRdAdr_u32 , FEE_PAGE_LEN , FALSE);

                    }
                } while (xRdAdr_u32 < xRdAdrEnd_u32);



                #if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
                if (xActivateLastPgmSearch_u8 == 1)
                {
                    Fee_RdWrOrder_st.LastProgrammedAddress_u32 = xLastProgrammedAddress_u32;
                    Fee_RdWrOrder_st.LastValidHdrAddress_u32 = xLastValidHeader_u32;
                }
                else
				{
					/* Identification of last programmed header and page is required only for the lastest valid sector i.e., sector with USED state.
					 * Do nothing for all sectors. */
		    	}
				#endif

                /* Save addresses for next call */
                xRdAdrContinue_u32      = xRdAdr_u32;
                xRdAdrEndContinue_u32   = xRdAdrEnd_u32;

                /* Check if the end address for the search is already reached */
                #if (defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH))
                if(xRdAdr_u32 >= xRdAdrEnd_u32)
                #else
                if(xRdAdrEnd_u32 >= EndAdr_u32)
                #endif
                {
                    /* Finish the order */
                    xRetVal = FEE_SECTORFULL_E;
                }
            }
            break;

            /* These states should never be reached */
            default:
            {
                /* Set error state */
                xRetVal = FEE_ERROR_E;
            }
            break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal == FEE_ORDER_PENDING_E) && (xRdAdrContinue_u32 < xRdAdrEndContinue_u32));

    #if (FEE_PRV_DEBUGGING != FALSE)
    Fee_Prv_stModuleTest_st.BuildUpCacheDiffRemainInside_u32 =
                        MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) -
                                               Fee_Prv_stModuleTest_st.BuildUpCacheStart_u32);

    /* Check for the maximum outside of the ECU init phase */
    if((Fee_Prv_stModuleTest_st.BuildUpCacheDiffRemainInside_u32 > Fee_Prv_stModuleTest_st.BuildUpCacheRemainInsideMax_u32) &&
       (Fee_stMain != FEE_POLLING_MODE_E))
    {
        Fee_Prv_stModuleTest_st.BuildUpCacheRemainInsideMax_u32 = Fee_Prv_stModuleTest_st.BuildUpCacheDiffRemainInside_u32;
    }
    #endif

    /* Check for necessary resets */
    if(xRetVal != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_LLBuildUpCache_en = FEE_LL_BLD_UP_CACHE_INIT_E;

        #if (FEE_PRV_DEBUGGING != FALSE)
        Fee_Prv_stModuleTest_st.BuildUpCacheDiff_u32 =
                            MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTimePart(TIM0) -
                                                   Fee_Prv_stModuleTest_st.BuildUpCacheStart_u32);

        /* Check for the maximum outside of the ECU init phase */
        if((Fee_Prv_stModuleTest_st.BuildUpCacheDiff_u32 > Fee_Prv_stModuleTest_st.BuildUpCacheMax_u32) &&
           (Fee_stMain != FEE_POLLING_MODE_E))
        {
            Fee_Prv_stModuleTest_st.BuildUpCacheMax_u32 = Fee_Prv_stModuleTest_st.BuildUpCacheDiff_u32;
        }
        #endif
    }

    return xRetVal;
}


/**
 *********************************************************************
 * Fee_BuildUpCacheForAllSect(): Build up the cache for all
 *                               available sectors
 *
 * This function builds up the cache for all sectors that are
 * configured.
 * The function can execute one sector without returning in case
 * this is necessary (e.g. during the ECU init) or verify
 * the block checksum.
 *
 * \param    none
 *
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Order is pending
 * \retval   FEE_ORDER_FINISHED_E:  Order is finished
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_BuildUpCacheForAllSect(void)
{
    Fee_stRetVal_ten xtmpRetVal;                        /* Function return */
    Fee_stRetVal_ten xRetVal = FEE_ORDER_PENDING_E;     /* Function return */
    static uint8 xLogSecIdxForCache_u8;                 /* Index of logical sector */

    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over state machine */
        switch (Fee_RdWrOrder_st.Fee_LLBuildUpCacheAllSect_en)
        {
            /* Init case */
            case FEE_LL_BLD_UP_CACHE_ALL_SECT_INIT_E:
            {
                /* Init the sector index */
                xLogSecIdxForCache_u8 = 0;

                /* Set next state */
                Fee_RdWrOrder_st.Fee_LLBuildUpCacheAllSect_en = FEE_LL_BLD_UP_CACHE_ALL_SECT_DO_E;
            }
            /* No break to save time */

            /* Build up the cache */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_BLD_UP_CACHE_ALL_SECT_DO_E:
            {
                /* Build up the cache */
                xtmpRetVal = Fee_BuildUpCache(Fee_FlashProp_st[Fee_LLSectorOrder_st[xLogSecIdxForCache_u8].xPhySecIdx_u8].Fee_LogStartAddress_u32,
                                              Fee_FlashProp_st[Fee_LLSectorOrder_st[xLogSecIdxForCache_u8].xPhySecIdx_u8].Fee_LogEndAddress_u32);

                   /* Check the function return */
                if(xtmpRetVal != FEE_ORDER_PENDING_E)
                {
                    /* Check if all relevant sectors have been checked so far */
                    xLogSecIdxForCache_u8++;
                    if(xLogSecIdxForCache_u8 >= (Fee_NumFlashBanksUsed_u8))
                    {
                        /* Finish the function */
                        xRetVal = FEE_ORDER_FINISHED_E;
                    }
                }
            }
            break;

            /* This case should never be reached */
            default:
                /* Finish the function, the return type is currently not
                 * evaluated (only called in Ini) */
                xRetVal = FEE_ORDER_FINISHED_E;
            break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal == FEE_ORDER_PENDING_E));

    /* Check the function state */
    if(xRetVal != FEE_ORDER_PENDING_E)
    {
        /* Reset the state machine */
        Fee_RdWrOrder_st.Fee_LLBuildUpCacheAllSect_en = FEE_LL_BLD_UP_CACHE_ALL_SECT_INIT_E;
    }

    return xRetVal;
}

#if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
/**
 *********************************************************************
 * Fee_SearchLastBlkHeader(): Return the latest valid block
 *                            header address within one sector
 *
 * This function returns the latest valid block header address out of
 * the Fee_RdWrOrder_st.xRdAddress sector which can be found in the cache.
 * This read address can point somewhere into a sector.
 *
 * \param    none
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Function is still pending
 * \retval   FEE_ERROR_E:           An error occurred
 * \retval   FEE_ABORTED_E:         Order was aborted
 * \retval   FEE_ORDER_FINISHED_E:  Function is finished
  * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_SearchLastBlkHeader(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_ptr)
{
    Fee_BlkHeader_tst xCurrBlkHeader_st;                            /* Block header structure */
    Fee_stRetVal_ten xRetVal_en  = FEE_ORDER_PENDING_E;             /* Function return */

    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over the state machine */
        switch (Fee_RdWrOrder_st.Fee_LLRdState_en)
        {
            /* Init state */
            case FEE_LL_INIT_READ_E:
            {
                /* Init the user parameter */
                Fee_GlobInfoLastRdHeader_ptr->FeeIndex_u16      = FEE_MAXUINT16;
                Fee_GlobInfoLastRdHeader_ptr->BlkCrc32_u32      = 0;
                Fee_GlobInfoLastRdHeader_ptr->HdrCrc16_u16      = 0;
                Fee_GlobInfoLastRdHeader_ptr->BlkStatus_u8      = 0;
                Fee_GlobInfoLastRdHeader_ptr->BlkLength_u16     = 0;

                /* Retries for read */
                Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

                /* Pick the last address information from the variable which was updated during Cache init. this is required to handle unknown blocks.
                 * There is no details of unknown blocks in cache. */
                Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32 = Fee_RdWrOrder_st.LastValidHdrAddress_u32;

                /* Check if a block header was found */
                if(Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32 != FEE_NULL)
                {
                    /* Copy the header address */
                    Fee_RdWrOrder_st.xRdAddress = Fee_GlobInfoLastRdHeader_ptr->AdrBlkHeader_u32;

                    /* Read out the length of the corresponding block */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_PAGE_E;
                }
                else
                {
                    /* No block header was found, return finished immediately */
                    xRetVal_en = FEE_ORDER_FINISHED_E;
                    break;
                }
            }
            /* No break to save time */
            /* Read out the header */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_READ_PAGE_E:
			{
                /* Read out the header only */
                if(Fls_Read(Fee_RdWrOrder_st.xRdAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], FEE_BLK_HEADER_SIZE) != E_NOT_OK)
                {
                    /* Set the next states:
                     * The block checksum has to be checked since the cache might have been build up during without a checksum
                     * verification (e.g. during the init) */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_WAIT_READ_PAGE_E;
                }
                else
                {
                    /* Fls did not accept the order due to wrong parameters or an internal busy state.
                     * Reset the state machine */
                    xRetVal_en = FEE_ABORTED_E;
                }
            }
			break;

            /* Wait for the read order to be finished */
            case FEE_LL_WAIT_READ_PAGE_E:
            {
			    /* The next state will be set by the Fee_JobEndNotification () or
                 * Fee_JobErrorNotification() function automatically */

                /* Call the Fls main function manually */
                Fls_MainFunction();

                #if (STD_ON == FEE_POLLING_MODE)
                /* Use the FLS polling mechanism in order to reach the next state */
                Fee_CheckFlsJobResult();
                #endif
            }
			break;

            /* Error reaction for read error */
            case FEE_LL_READ_ERROR_E:
            {
			    /* Reset the complete read buffer */
                Fee_SrvMemSet8((uint8*)&Fee_PageBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_LL_PAGEBUFFSIZE);

                /* Verify retry possibility */
                if(Fee_RdWrRetries_u8 > 0)
                {
                    /* Decrement retry possibilities */
                    Fee_RdWrRetries_u8--;

                    /* Try again to call the Fls and perform the read procedure */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_PAGE_E;
                }
                else
                {
                    /* Return error */
                    xRetVal_en = FEE_ERROR_E;
                }
            }
			break;

            /* Evaluate the block header */
            case FEE_LL_READ_FINISHED_E:
            {
			    /* Extract the block length and the block index out of the flash
                 *
                 * Hint: This function is used in the init phase of the Fee and therefore
                 *       the block checksum is not relevant. Only valid headers are
                 *       added to the cache and therefore it can be regarded as valid */
                Fee_LLCopyPageBuff2HeaderMid(&xCurrBlkHeader_st, &Fee_PageBytePtr_cpu8[0]);

                /* Copy the relevant info to the global structure */
                Fee_GlobInfoLastRdHeader_ptr->FeeIndex_u16  = xCurrBlkHeader_st.FeeIndex_u16;
                Fee_GlobInfoLastRdHeader_ptr->BlkLength_u16 = xCurrBlkHeader_st.BlkLength_u16;

                /* Set return value */
                xRetVal_en = FEE_ORDER_FINISHED_E;
            }
			break;

            /* Default state should never be reached */
            default:
            {
			    /* Set error state */
                xRetVal_en = FEE_ERROR_E;

                /* Reset the state machine */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
            }
			break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal_en == FEE_ORDER_PENDING_E));

    /* Check if the search was aborted or the sector is full */
    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Init the state machine */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
    }

    /* Return function state */
    return xRetVal_en;
}
/* if !( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )*/
#endif
/* FEE_FAST_CACHE_INIT_ACTIVE != FALSE */
#endif


/**
 *********************************************************************
 * Fee_SearchHighestCacheEntry(): Return the highest cache address
 *                                for the corresponding sector within
 *                                a certain boundary.
 *
 * This function returns the highest cache address for a certain
 * sector within given boundaries.
 *
 * \param    UpperBoundary_u32:		Upper boundary
 * \param	 SectIdx_u8:			Corresponding sector index
 * \return
 * \retval   xAddress_u32:			Corresponding address
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_SearchHighestCacheEntry(VAR(uint32,FEE_VAR) UpperBoundary_u32, VAR(uint8, FEE_VAR) SectIdx_u8)
{
	uint32 xAddress_u32 		= FEE_NULL;				/* Function return */
	uint32 i_u32 = 0;									/* Loop counter */
	uint32 xSectStartAdr_u32 	= Fee_FlashProp_st[SectIdx_u8].Fee_LogStartAddress_u32;
	uint32 xSectEndAdr_u32 		= Fee_FlashProp_st[SectIdx_u8].Fee_LogEndAddress_u32;

	/* Get the highest value out of the cache */
	for(i_u32=0; i_u32<FEE_NUM_BLOCKS;i_u32++)
	{
		/* Check if the current cache entry to be regarded for the search*/
		if((Fee_Cache_au32[i_u32] >= xSectStartAdr_u32) &&
		   (Fee_Cache_au32[i_u32]  < xSectEndAdr_u32) &&
		   (Fee_Cache_au32[i_u32] != FEE_CACHE_INIT_VALUE) &&
		   (Fee_Cache_au32[i_u32] != FEE_CACHE_TMP_INVALID_VALUE) &&
		   (Fee_Cache_au32[i_u32] > xAddress_u32) &&
		   (Fee_Cache_au32[i_u32] < UpperBoundary_u32))
		{
			/* Save the current address */
			xAddress_u32 = Fee_Cache_au32[i_u32];
		}
	}

	/* Check for the init value */
	if(xAddress_u32 == FEE_NULL)
	{
		/* Reset the return to the upper boundary */
		xAddress_u32 = UpperBoundary_u32;
	}

	return xAddress_u32;
}

FUNC(void, FEE_CODE) Fee_InvalidateCacheByAddress(VAR(uint32,FEE_VAR) xAddress_u32)
{
	uint32 i_u32 = 0;									/* Loop counter */

	/* Get the highest value out of the cache */
	for(i_u32=0; i_u32<FEE_NUM_BLOCKS;i_u32++)
	{
		/* Check if the current cache entry to be regarded for the search*/
		if(Fee_Cache_au32[i_u32] == xAddress_u32)
		{
			Fee_Cache_au32[i_u32] = FEE_CACHE_TMP_INVALID_VALUE;
		}
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

