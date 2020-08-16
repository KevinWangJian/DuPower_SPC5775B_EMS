


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

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_HLReadBlock(): Read back block data
 *
 * This function copies the block data of a request block index
 * to a user buffer.
 *
 * \param    none
 *
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:       Order is still pending
 * \retval   FEE_BLOCK_INVALIDATED_E:   The requested block is invalidated
 *                                      (data irrelevant)
 * \retval   FEE_ERROR_E:               No valid data available
 * \retval   FEE_ABORTED_E:             Order was aborted due to a wrong
 *                                      FLS compare function call or an
 *                                      internal error occured
 * \retval   FEE_FINISHED_E:            The block was copied successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLReadBlock(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal = FEE_ORDER_PENDING_E;     /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xtmpRetVal;                        /* Internal function return */
    static uint32 xAdrLastBlkHeader_u32 = FEE_MAXUINT32;                /* Block header end address used for the search */
    static boolean xSearchRetry_b = FALSE;                              /* First try indicator for finding a block */

    VAR(uint16,AUTOMATIC) Offset = 0;                   /* Offset for data tranfer from flash to the user buffer */
    VAR(uint16,AUTOMATIC) Length = 0;                   /* Length for data tranfer from flash to the user buffer */
    P2VAR(uint8,AUTOMATIC, FEE_APPL_DATA) DataPtr;      /* Data pointer for the transfer from flash to the user buffer */


    /* Loop over the read state machine */
	switch(Fee_RdWrOrder_st.Fee_HLRdBlock)
	{
		case FEE_HL_RDWR_BLK_INIT_E:
		{
			/* Extract the required information from the configuration table */
			Fee_GlobInfoLastRdHeader_st.FeeIndex_u16  =
					Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].BlockPersistentId_u16;
			/* This length is set below and taken out of the flash (header information) */
			Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
					Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
			Fee_GlobInfoLastRdHeader_st.BlkStatus_u8  =
					(uint8)(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & 0xFFu);

			Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32   = FEE_NULL;
			Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32       = 0;
			Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16       = 0;

			/* Set next state */
			Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_SEARCH_BLK_HDR_E;
		}
		/* No break to save time */

		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_HL_SEARCH_BLK_HDR_E:
		{
			/* Search for the latest valid block header with the given FeeIdx.
			 * The start address for the search can be set with the variable xAdrLastBlkHeader_u32. */
			xtmpRetVal = Fee_LLSearchSpecifiedBlkHeader(Fee_OrderFifo_st[Fee_idxActQueue_u8].FeeIdx_u16,  /* FeeIdx */
														&xAdrLastBlkHeader_u32,                 /* End address for the search */
														&Fee_GlobInfoLastRdHeader_st,              /* Result structure */
														xSearchRetry_b);                        /* Indicate first try */

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

				/* A valid blockheader was found */
				case FEE_ORDER_FINISHED_E:
				{
					/* Calculate block checksum in flash to check if the block is valid */
					Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_CHECK_BLK_CS_E;

					/* Store the header address. If the block checksum is wrong, searching of an old copy will be
					 * done until this address if the last valid header block is reached! */
					xAdrLastBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;
				}
				break;

				/* No valid header page was found within the complete flash (all sectors have been checked) */
				case FEE_ERROR_E:
				{
					/* The cache was already invalidated inside the function Fee_LLSearchSpecifiedBlkHeader */

					/* Return error */
					xRetVal = FEE_ERROR_E;
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
				case FEE_BLOCK_INVALIDATED_E:
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
		}
		break;

		/* A valid header was found, evaluate the block content */
		case FEE_HL_CHECK_BLK_CS_E:
		{
			/* Calculate the checksum */
			xtmpRetVal = Fee_LLCalcBlkCrcInFlash(&Fee_GlobInfoLastRdHeader_st);

			/* Evaluate the result */
			switch (xtmpRetVal)
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
					/* Data was read successfully from the flash.
					 * The cache was updated inside the function */

					/* Check whether the block is invalidated in the flash */
					if((Fee_GlobInfoLastRdHeader_st.BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) > 0)
					{
						/* Leave this function (block CRC is irrelevant) */
						xRetVal = FEE_BLOCK_INVALIDATED_E;
					}
					else
					{
						/* Copy the data to the user buffer */
						Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_RD_DATA_FROM_BLK_E;
					}
				}
				break;

				/* The checksum is invalid (block CRC is incorrect) or a read error occured */
				case FEE_ERROR_E:
				{
					/* If this is a forced read order, copy the data even if block CRC is not valid
					 * or the data was not readable */
					if (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_FORCED_READ_ORDER)
					{
						/* Copy the data to the user buffer */
						Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_RD_DATA_FROM_BLK_E;
					}
					else
					{
						/* Search for an older copy (last header address was already set in the last state) */
						Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_SEARCH_BLK_HDR_E;

						/* Workaround Overstamp invalid header to reduce init time */
						#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
						if(E_NOT_OK != Fls_Write(Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32, Fee_hdrBuffer_au8, FEE_PAGE_LEN))
						{
							Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_RD_WAIT_FOR_FLS_E;
						}
						else
						{
						}
						#endif
						/* END Workaround Overstamp invalid header to reduce init time */

						/* A reset of the cache in order to be safe against
						 * any kinds of interruptions for the following search
						 * (e.g. Fee_Cancel) was done inside the function already */

						/* Indicate a retry */
						xSearchRetry_b = TRUE;
					}
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
					xRetVal = FEE_ABORTED_E;
				}
				break;
			}
		}
		break;

		/* Workaround Overstamp invalid header to reduce init time */
		#if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))

		/* Wait for the flash to finish the overwrite of an invalid header */
		case FEE_HL_RD_WAIT_FOR_FLS_E:
		{
			if(Fls_GetJobResult() != MEMIF_JOB_PENDING)
			{
				Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_SEARCH_BLK_HDR_E;
			}
		}
		break;

		#endif
		/* END Workaround Overstamp invalid header to reduce init time */

		/* Copy the data to the user buffer */
		case FEE_HL_RD_DATA_FROM_BLK_E:
		{
			/* Copy user pointer and block info to Fee internal variables
			 * Hint: the data was first read back during the CRC check internally.
			 *       The user buffers should only be filled in case the data is
			 *       valid (excluding the forced read). */
			DataPtr = Fee_OrderFifo_st[Fee_idxActQueue_u8].DataBufferPtr_pu8;
			Offset  = Fee_OrderFifo_st[Fee_idxActQueue_u8].Offset_u16;

			/* Copy the original length */
			Length = Fee_OrderFifo_st[Fee_idxActQueue_u8].Length_u16;

			/* The cache was set already after verifying the block CRC */
			/* The order is finished --> no temporary return value is necessary */
			xRetVal = Fee_LLCopyData2Buffer(&Fee_GlobInfoLastRdHeader_st, DataPtr, Offset, Length);
		}
		break;

		/* These states cannot be reached */
		case FEE_HL_COMP_BLK_E:
		case FEE_HL_WR_BLK_E:
		default:
		{
			/* Abort this function with an error return */
			xRetVal = FEE_ABORTED_E;
		}
		break;
	}

    /* Evaluate the result of the function returns */
    if (xRetVal != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_HLRdBlock = FEE_HL_RDWR_BLK_INIT_E;

        /* Reset the end address of the search */
        xAdrLastBlkHeader_u32 = FEE_MAXUINT32;

        /* Reset start search indicator */
        xSearchRetry_b = FALSE;
    }

    return (xRetVal);
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
