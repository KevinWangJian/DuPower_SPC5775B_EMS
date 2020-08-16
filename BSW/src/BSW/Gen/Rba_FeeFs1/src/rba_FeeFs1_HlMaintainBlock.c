


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
#if(FEE_RB_MAINTAIN != FALSE)
/* Information regarding the last found block header */
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
/* MR12 RULE 8.5 VIOLATION: This variable needs to keep its value but it is not used outside of this file */
static Fee_GlobInfoLastRdHeader_tst Fee_GlobInfoLastRdHeaderMt_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_VAR_INIT_8
#include "Fee_MemMap.h"
/* MR12 RULE 8.5 VIOLATION: This variable needs to keep its value but it is not used outside of this file */
static boolean Fee_Rb_GlobSecurityLevelInfo_b = FALSE;
#define FEE_STOP_SEC_VAR_INIT_8
#include "Fee_MemMap.h"

/**
 *********************************************************************
 * Fee_HLMaintainBlock(): Maintain a redundant block
 *
 * This function is used to repair a redundant block if one of the
 * copies has corrupt data.
 *
 * The block is being searched in all the sectors due to the verification
 * whether a maintenance is necessary or not (one of the copes incorrect).
 * In this case, the correct copy will be moved to newest free FLASH space
 * and write it redundant again.
 *
 * \param    none
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Block write caused an error
 *                                  (3 retries failed)
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully or
 *                                  write order not necessary
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_HLMaintainBlock(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC)  xRetVal_en    = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC)  xTmpRetVal_en = FEE_ORDER_PENDING_E;  /* Temp return */
    VAR(Fee_BlkHeader_tst, AUTOMATIC) xTmpBlkHdr_st;
    static uint32  xAdrLastBlkHeader_u32            = FEE_MAXUINT32;        /* Block header address */
    static boolean xSearchRetry_b;                                          /* First try indicator for finding a block */
    uint16 xBlockLength_u16;
    uint16 xCalcCrc_u16;

    #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    uint8 xPhySectIdxFirstCopy_u8;
    uint8 xPhySectIdxSecondCopy_u8;
    #endif


    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over function state machine */
        switch (Fee_RdWrOrder_st.Fee_HLMtBlock_en)
        {
            /* Init state */
            case FEE_HL_RDWR_BLK_INIT_E:
            {
                /* Do not maintain single storage blocks */
                if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                        FEE_FLAG_SEC_LEVEL_MSK) == 0u)
                {
                    xRetVal_en = FEE_ORDER_FINISHED_E;
                    break;
                }

                /* Init last block header address */
                xAdrLastBlkHeader_u32 = FEE_MAXUINT32;

                /* Extract the required information from the configuration table */
                Fee_GlobInfoLastRdHeader_st.FeeIndex_u16  =
                        Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].BlockPersistentId_u16;
                Fee_GlobInfoLastRdHeader_st.BlkLength_u16 =
                        Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Length_u16;
                Fee_GlobInfoLastRdHeader_st.BlkStatus_u8  =
                        (uint8)(Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & (uint16)0x00FF);

                Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = FEE_NULL;
                Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32     = 0;
                Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16     = 0;

                /* Reset start search indicator */
                xSearchRetry_b = FALSE;

				/* Reset the redundant block flag */
				Fee_Rb_GlobSecurityLevelInfo_b = FALSE;

                #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
				/* Reset the flag to invalidate an old copy */
				Fee_Rb_InvalidateOldCopy_b = FALSE;

				/* Indicate Fee_LLCpyBlkFromFls2Fls that Maintain is running */
				Fee_Rb_MaintainRun_b = TRUE;
                #endif

                /* Set next state */
                Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_SEARCH_BLK_HDR_E;
            }
            /* No break to save time */

            /* Search for a block header */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_HL_SEARCH_BLK_HDR_E:
            {
                /* Search for the latest valid block header with the given FeeIdx.
                 * The end address for the search can be set with the variable xAdrLastBlkHeader_u32. */
                xTmpRetVal_en = Fee_LLSearchSpecifiedBlkHeader(Fee_OrderFifo_st[Fee_idxActQueue_u8].FeeIdx_u16,         /* FeeIdx */
                                                               &xAdrLastBlkHeader_u32,                                  /* End address for the search */
                                                               &Fee_GlobInfoLastRdHeader_st,                            /* Result structure */
                                                               xSearchRetry_b);                                         /* Indicate first try */

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
                        Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_CHECK_BLK_CS_E;
                    }
                    break;

                    case FEE_ERROR_E:
                    {
                        #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                        if (((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u) &&
                            (Fee_Rb_GlobSecurityLevelInfo_b != FALSE))
                        {
                            /* Only one valid block was found within the complete flash (all sectors have been checked)
                             * -> rewrite the block */
                            Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                        }
                        else
                        #endif
                        {
                            /* No valid header was found within the complete flash (all sectors have been checked) */
                            xRetVal_en = FEE_ERROR_E;
                        }
                    }
                    break;

                    /* The cache is corrupt */
                    case FEE_ABORTED_E:
                    {
                        /* The wrong index was found using the cache. The respective entry was already
                         * marked for a manual search during the sector reorganization.
                         * --> "Manual search" will start automatically in order to find other copies */

                        /* Indicate retry */
                        xSearchRetry_b = TRUE;
                    }
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
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    break;
                }
            }
            break;

            /* A valid header was found, evaluate the block content */
            case FEE_HL_CHECK_BLK_CS_E:
            {
                /* Calculate the block CRC */
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
                        if (Fee_Rb_GlobSecurityLevelInfo_b == FALSE)
                        {
                            /* Store the found valid block header */
                            Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;
                            Fee_GlobInfoLastRdHeaderMt_st.BlkCrc32_u32     = Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32;
                            Fee_GlobInfoLastRdHeaderMt_st.BlkLength_u16    = Fee_GlobInfoLastRdHeader_st.BlkLength_u16;
                            Fee_GlobInfoLastRdHeaderMt_st.BlkStatus_u8     = Fee_GlobInfoLastRdHeader_st.BlkStatus_u8;
                            Fee_GlobInfoLastRdHeaderMt_st.FeeIndex_u16     = Fee_GlobInfoLastRdHeader_st.FeeIndex_u16;
                            Fee_GlobInfoLastRdHeaderMt_st.HdrCrc16_u16     = Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16;

                            /* Reset the block header info for further search */
                            Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32 = 0;

                            /* Set the second search flag */
                            Fee_Rb_GlobSecurityLevelInfo_b = TRUE;

                            /* Load the limit address for next search: if the limit is not given with FEE_MAXUINT32,
                             * next search happens only on current sector */
                            xAdrLastBlkHeader_u32 = Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32;

                            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                            if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
                            {
                                /* Indicate a retry (necessary to search a second version of a NoFallback block) */
                                xSearchRetry_b = TRUE;

                                /* Search for a second copy or version of this block */
                                Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_SEARCH_BLK_HDR_E;
                            }
                            else
                            #endif
                            {
                                /* Temporary block length without alignment */
                                xBlockLength_u16 = Fee_GlobInfoLastRdHeaderMt_st.BlkLength_u16 + FEE_BLOCK_OVERHEAD;

                                /* Alignment with FEE_PAGE_LEN */
                                while ((xBlockLength_u16 % (uint16)FEE_PAGE_LEN) != 0)
                                {
                                    xBlockLength_u16++;
                                }

                                /* Calculate the possible start address of next copy */
                                xAdrLastBlkHeader_u32 -= xBlockLength_u16;

                                /* Check if this address on the same sector of the found block or not */
                                if (xAdrLastBlkHeader_u32 < Fee_LLGetSecStartAddress(Fee_GetPhysSectorByAddress(Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32)))
                                {
                                    /* The next copy does not exist in this sector, rewrite this block directly */
                                    Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                                }
                                else
                                {
                                    /* Start to read block header in calculated address */
                                    if (Fls_Read(xAdrLastBlkHeader_u32, (uint8*)&Fee_PageBytePtr_cpu8[0], FEE_BLOCK_OVERHEAD) != E_NOT_OK)
                                    {
                                        /* Set next state */
                                        Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_READ_BLK_HDR_WAIT_E;

                                        /* Update the next header address */
                                        Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32 = xAdrLastBlkHeader_u32;
                                    }
                                    else
                                    {
                                        /* Fls did not accept the order due to wrong parameters or an internal busy state.
                                         * Reset the state machine */
                                        xRetVal_en = FEE_ABORTED_E;
                                    }
                                }
                            }
                        }
                        else
                        {
                            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                            if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
                            {
                                /* Get the sector index of both copies */
                                xPhySectIdxFirstCopy_u8 = Fee_GetPhysSectorByAddress(Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32);
                                xPhySectIdxSecondCopy_u8 = Fee_GetPhysSectorByAddress(Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32);

                                /* In case the function is called during shutdown the block has to be restored and a
                                 * possibly available old copy destroyed!
                                 * -> Check if the block CRC of both copies are equal
                                 * -> Check if the second copy starts in the same sector */
                                if ((Fee_GlobInfoLastRdHeaderMt_st.BlkCrc32_u32 != Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32) ||
                                    (xPhySectIdxFirstCopy_u8 != xPhySectIdxSecondCopy_u8))
                                {
                                    /* The old copy needs to be invalidated first! */
                                    Fee_Rb_InvalidateOldCopy_b = TRUE;

                                    Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                                }
                                else
                                {
                                    /* The cache was updated with the address of the second valid version of the block
                                     * -> restore the cache with the address of the latest copy */
                                    Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeaderMt_st.FeeIndex_u16,
                                                               Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32);

                                    /* The block CRC of the second copy has been checked already and is equal to the first copy
                                     * -> no repair needed */
                                    xRetVal_en = FEE_ORDER_FINISHED_E;
                                }
                            }
                            else
                            #endif
                            {
                                /* The cache was updated with the address of the second valid version of the block
                                 * -> restore the cache with the address of the latest copy */
                                Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeaderMt_st.FeeIndex_u16,
                                                           Fee_GlobInfoLastRdHeaderMt_st.AdrBlkHeader_u32);

                                /* The block CRC of the second copy has been checked already and is equal to the first copy
                                 * -> no repair needed */
                                xRetVal_en = FEE_ORDER_FINISHED_E;
                            }
                        }
                    }
                    break;

                    /* The checksum is invalid (block CRC is incorrect) or a read error occurred */
                    case FEE_ERROR_E:
                    {
                        /* Error during CRC detected:
                         * -> For the 1. copy: search further
                         * -> For the 2. copy: repair it with the found block */

                        if(Fee_Rb_GlobSecurityLevelInfo_b == FALSE)
                        {
                            /* Indicate a retry */
                            xSearchRetry_b = TRUE;

                            xAdrLastBlkHeader_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;

                            /* Search for an older copy (last header address was already set in the last state) */
                            Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_SEARCH_BLK_HDR_E;
                        }
                        else
                        {
                            /* Start to repair */
                            Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
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
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    break;
                }
            }
            break;

            /* Search for a block header */
            case FEE_HL_READ_BLK_HDR_WAIT_E:
            {
                /* The next state will be set by the Fee_JobEndNotification() or
                 * Fee_JobErrorNotification() function automatically (the verification of the data will be done
                 * in one step after the data was read) */

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

            case FEE_HL_CHECK_BLK_HDR_E:
            {
                /* Compare the preamble of the block header byte - wise */
                if ((Fee_PageBytePtr_cpu8[2] == FEE_BLK_HEADER_PREAMBEL_BYTE_2) &&
                    (Fee_PageBytePtr_cpu8[1] == FEE_BLK_HEADER_PREAMBEL_BYTE_1) &&
                    (Fee_PageBytePtr_cpu8[0] == FEE_BLK_HEADER_PREAMBEL_BYTE_0))
                {
                    /* Extract the rest up to the Crc32 out of the page buffer and copy it to the block structure */
                    Fee_LLCopyPageBuff2HeaderMid(&xTmpBlkHdr_st, &Fee_PageBytePtr_cpu8[0]);

                    /* Check the block header CRC */
                    xCalcCrc_u16 = Crc_CalculateCRC16((uint8*)&Fee_PageBytePtr_cpu8[0],
                                                      (uint32)(FEE_BLK_HEADER_SIZE - 6u),
                                                      (uint16)FEE_MARKER_PATTERN,
                                                      FALSE);

                   /* Check the header consistency and persistent ID */
                   if ((xCalcCrc_u16 == xTmpBlkHdr_st.HdrCrc16_u16) &&
                       (xTmpBlkHdr_st.FeeIndex_u16 == Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].BlockPersistentId_u16))
                   {
                      /* This is a valid header. Nevertheless it is possible that this order was not finished correct
                       * or that the block checksum is wrong. */

                      /* Extract the rest out of the page buffer and copy it to the block structure */
                      Fee_LLCopyPageBuff2HeaderEnd(&xTmpBlkHdr_st, &Fee_PageBytePtr_cpu8[0]);

                      /* Load the valid block header info to global header structure */
                      Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32  = xTmpBlkHdr_st.BlkCrc32_u32;
                      Fee_GlobInfoLastRdHeader_st.BlkLength_u16 = xTmpBlkHdr_st.BlkLength_u16;
                      Fee_GlobInfoLastRdHeader_st.BlkStatus_u8  = xTmpBlkHdr_st.BlkStatus_u8;
                      Fee_GlobInfoLastRdHeader_st.FeeIndex_u16  = xTmpBlkHdr_st.FeeIndex_u16;
                      Fee_GlobInfoLastRdHeader_st.HdrCrc16_u16  = xTmpBlkHdr_st.HdrCrc16_u16;

                      /* Compare the block data checksum at first for both copies */
                      if (Fee_GlobInfoLastRdHeaderMt_st.BlkCrc32_u32 == Fee_GlobInfoLastRdHeader_st.BlkCrc32_u32)
                      {
                          /* Calculate block checksum in flash to check if the block is valid */
                          Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_CHECK_BLK_CS_E;
                      }
                      else
                      {
                          /* Different data checksum --> Start to repair directly */
                          Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                      }
                   }
                   else
                   {
                       /* 2. copy header corrupt --> Start to repair */
                       Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                   }
                }
                else
                {
                    /* 2. copy header not found --> Start to repair */
                    Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
                }
            }
            break;

            /* Write a block into the latest sector twice */
            case FEE_HL_WR_BLK_E:
            {
                /* Copy the block from the old sector (Fee_GlobInfoLastRdHeader_st->AdrBlkHeader_u32) to the
                 * new sector (Fee_RdWrOrder_st.xWrAddress). If the security level is greater than 1, the
                 * same block (latest valid copy) is copied twice automatically. */
                xTmpRetVal_en = Fee_LLCpyBlkFromFls2Fls(&Fee_GlobInfoLastRdHeaderMt_st, TRUE);

                /* Evaluate the function return */
                switch (xTmpRetVal_en)
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
                        xRetVal_en = FEE_ORDER_FINISHED_E;
                    }
                    break;

                    /* An error occurred during the read, write or verify sequence
                     * (3 retries for read, write or verify failed in case the orders
                     *  have been accepted by the Fls before)*/
                    case FEE_ERROR_E:
                    {
                        xRetVal_en = FEE_ERROR_E;
                    }

                    break;

                    /* The reorganization was aborted and the USED sector was erased */
                    case FEE_ABORTED_E:
                    {
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    break;

                    /* These states should never be reached (cannot be returned by Fee_LLCpyBlkFromFls2Fls) */
                    case FEE_ERASE_SECTOR_E:
                    case FEE_SECTORCHANGE_E:
                    case FEE_SECTORFULL_E:
                    case FEE_BLOCK_INVALIDATED_E:
                    case FEE_NUM_RET_VAL_E:
                    default:
                    {
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
    }
    while ((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal_en == FEE_ORDER_PENDING_E));

    /* Reset state machine if necessary */
    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_RDWR_BLK_INIT_E;

        /* Reset the end address of the search */
        xAdrLastBlkHeader_u32 = FEE_MAXUINT32;

        #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        /* Reset the Maintain indication flag for Fee_LLCpyBlkFromFls2Fls */
        Fee_Rb_MaintainRun_b = FALSE;
        #endif
    }

    return (xRetVal_en);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_RB_MAINTAIN != FALSE */
#endif
/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
