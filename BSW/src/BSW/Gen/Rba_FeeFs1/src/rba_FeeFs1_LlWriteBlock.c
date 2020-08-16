


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
#include "Fls.h"
#include "Crc.h"
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
   // #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
   // #error "AUTOSAR minor version undefined or mismatched"
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)

#if(FEE_ROBUST_PROG_ACTIVE != FALSE)
/* Ifx robust programming */
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_IfxRobustProgramming_t Fee_IfxRobustProgramming_s;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
#endif


/**
 *********************************************************************
 * Fee_LLWriteBlock(): Write a block into a sector
 *
 * This function is used to write a block into the memory media. The
 * data is being programmed and verified afterwards automatically. In
 * case a sector erase is necessary, this operation is also performed.
 * The marker handling is done automatically in case an ERASED,
 * USED or FULL marker has to be written.
 *
 * \param    Info_ptr:  Pointer to the block header info
 * \param    Data_pcu8: Pointer the data to be compared
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Difference detected after the
 *                                  programming sequence
 * \retval   FEE_SECTORFULL_E:      The write order cannot be executed
 *                                  because the HSR threshold will be
 *                                  exceeded
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLWriteBlock(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Info_ptr,
                                                  P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en         = FEE_ORDER_PENDING_E;
    VAR(Fee_stRetVal_ten, AUTOMATIC) xCompareRetVal_en  = FEE_ORDER_PENDING_E;
    VAR(Fee_stRetVal_ten, AUTOMATIC) xWrMarkerRetVal_en;
    VAR(Fee_stRetVal_ten, AUTOMATIC) xErSectorRetVal_en;

    VAR(uint16, AUTOMATIC)           xNumBytes_u16      = 0;
    VAR(uint16, AUTOMATIC)           xTempNumBytes_u16  = 0;
    VAR(uint32, AUTOMATIC)           xNumFreeBytes_u32  = 0;
    VAR(uint8, AUTOMATIC)            xCnt_u8            = 0;
    VAR(uint16, AUTOMATIC)           xCnt_u16           = 0;
    VAR(uint8, AUTOMATIC)            xPhySectIdx_u8     = 0;
    VAR(uint8, AUTOMATIC)            xLogSectIdx_u8     = 0;

    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    VAR(uint8, AUTOMATIC)       i_u8                    = 0;
    VAR(uint16, AUTOMATIC)      xNumBytesCutOff_u16     = 0;
    VAR(uint8, AUTOMATIC)       xCrcOffset_u8           = 0;
    VAR(uint8, AUTOMATIC)       xNumCrcBytes_u8         = 0;
    VAR(uint32, AUTOMATIC)      xBlkCrc32Tmp_u32        = 0;
	VAR(uint8, AUTOMATIC)       xTempPadding            = 0;
    static uint32               xBlkCrc32Result_u32     = 0;
    static uint8                xNumCrcBytesDone_u8     = 0;
    #endif

    static uint32 cntProgrammedBytes_u32 = 0;
    uint32 tmpAddr_u32;

    /* Switch over the state machine for writing a block */
    switch(Fee_RdWrOrder_st.Fee_LLWrBlock_en)
    {
        /* Init state */
        case FEE_LL_WR_BLK_INIT_E:
        {
            /* Reset state machines */
            Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en  = FEE_LL_WR_BLK_INIT_E;
            Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_BLK_INIT_E;

            /* Reset the page buffer to make sure no wrong data remains inside */
            Fee_SrvMemSet8((uint8*)&Fee_DataBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_LL_DATABUFFSIZE);

            /* Get the logical sector index */
            xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress)];

            #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
            /* Get the start value for the CRC calculation and reset the considered Crc bytes */
            xBlkCrc32Result_u32 = Fee_DataByteStartCrc_u32;
            #endif

            cntProgrammedBytes_u32 = 0;

            #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            /* Initalise the address for 2nd header page to indicate that 2nd header page is not yet programmed. */
            Fee_RdWrOrder_st.xHdPg2Address = FEE_NULL;
            #endif

            /* Check the current sector state */
            switch(Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en)
            {
                /* Current sector is used */
                case FEE_SECTOR_USED_E:
                {
                    /* Go on with writing of the NoFallback marker */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_SIZECHECK_HSR_E;
                }
                break;

                /* Sector state is undefined */
                case FEE_SECTOR_STATE_UNDEF_E:
                case FEE_SECTOR_REQUEST2ERASE_E:
                {
                    /* This state cannot be reached (unless the sectors did not get the chance
                     * to be erased in the background after the production) */

                    /* Erase this sector */
                    Fee_LLSetEraseSector(xLogSectIdx_u8);

                    /* Write the ERASED marker */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_ERASE_SECTOR_E;

                    /* Go back to the init state */
                    Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_BLK_INIT_E;
                }
                break;

                /* Sector state is full */
                case FEE_SECTOR_FULL_E:
                {
                    /* The next sector has to be used for the current write order. The USED marker has
                     * to be written before */

                    /* Increment the logical sector */
                    xLogSectIdx_u8++;

                    /* Check if the last sector is reached */
                    if(xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                    {
                        /* Error case: all sectors are full (this assumption is guaranteed by the logical
                         *             sector order mechanism)
                         * --> erase the most current sector in order to get the chance to keep data
                         *     that is never written (which will be located in the oldest FULL sector).
                         *
                         * Hint: This is a backup solution since the hard sector reorganization will
                         *       run first which erases one sector already. */

                        /* Restrict the logical sector index to the maximum */
                        xLogSectIdx_u8 = FEE_NUM_FLASH_BANKS - 1;

                        /* Get the physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Get the start address for write accesses */
                        Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                        /* Mark the sector to be erased */
                        Fee_LLSetEraseSector(xLogSectIdx_u8);

                        /* Set the next state */
                        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_ERASE_SECTOR_E;

                        /* Come back to the write USED marker state as soon as erasing is finished */
                        Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;

                        /* Come back to the write of the NoFallback marker state after the USED marker is written */
                        Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_SIZECHECK_HSR_E;

                        /* Invalidate the complete cache */
                        for(xCnt_u16=0; xCnt_u16<FEE_NUM_BLOCKS; xCnt_u16++)
                        {
                            /* Invalidate the corresponding cache address */
                            Fee_LLInvalidateAddressInCache(Fee_BlockProperties_st[xCnt_u16].BlockPersistentId_u16);
                        }

                        /* Invalidate the complete cache status */
                        for(xCnt_u8=0; xCnt_u8<FEE_NUM_FLASH_BANKS; xCnt_u8++)
                        {
                            /* Invalidate the corresponding physical sector */
                            Fee_LLEraseCacheStForSect(xCnt_u8);
                        }
                    }
                    else
                    {
                        /* It is possible that the next logical sector is not erased yet!
                         * In this case, the sector has to be erased first
                         * Hint: it is actually not possible that the next sector after an active FULL sector
                         *       is in the FULL state (error case)
                         *       --> erase the most current FULL sector */

                        /* Get the new physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Get the new start address */
                        Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                        /* Verify the sector state */
                        if(Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_ERASED_E)
                        {
                            /* The new logical sector is already erased*/

                            /* Set the next state */
                            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;

                            /* Come back to the write of the NoFallback marker state after the USED marker is written */
                            Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_SIZECHECK_HSR_E;
                        }
                        else
                        {
                            /* The new logical sector has to be erased first */

                            /* Mark the sector to be erased */
                            Fee_LLSetEraseSector(xLogSectIdx_u8);

                            /* Set the next state */
                            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_ERASE_SECTOR_E;

                            /* Come back to the write USED marker state as soon as erasing is finished */
                            Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;

                            /* Come back to the write of the NoFallback marker state after the USED marker is written */
                            Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_SIZECHECK_HSR_E;
                        }
                    }
                }
                break;

                /* Sector was erased before */
                case FEE_SECTOR_ERASED_E:
                {
                    /* State can be reached if the flash was erased before */

                    /* Write the USED marker next */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;

                    /* Come back to the write of the NoFallback marker state after the USED marker is written */
                    Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_SIZECHECK_HSR_E;
                }
                break;

                /* Default states */
                case FEE_SECTOR_CONSIDERED_E:
                default:
                {
                    /* States should never be reached */
                    xRetVal_en = FEE_ABORTED_E;
                }
                break;
            }
        }
        break;


        // for the first copy written whithin this stateflow, check whether
        // there is enough space to the HSR for all blocks to be written.
        case FEE_LL_WR_SIZECHECK_HSR_E:
        {
            uint32 neededSpace_u32;

            // Is it the first execution cycle?
            if(Fee_GlobInfoWrBlock_st.cntCopies_u8 == FEE_CNT_FIRST_COPY)
            {
                uint16 dataLen_u16 , blockPropIdx_u16;
                boolean noFbActive_b , doubleSecActive_b;

                // calculate the space needed to check against the HSR threshold
                dataLen_u16 = Info_ptr->BlkLength_u16;// if invalidate order, block length is replaced with 0

                blockPropIdx_u16 = Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16;

                doubleSecActive_b = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_SEC_LEVEL_MSK) > 0u;

                #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                    noFbActive_b  = (Fee_BlockProperties_st[blockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u;
                #else
                    noFbActive_b = FALSE;
                #endif



                neededSpace_u32 = Fee_SrvCalcSpaceNeededForWrite(dataLen_u16 , doubleSecActive_b , noFbActive_b);

                if(Fee_LLCheckReorganizationNeed(FEE_REQUIRED_FREE_SPACE_BEFORE_HARD_SR, (uint16) neededSpace_u32)
                        == FEE_SECTORFULL_E )
                {
                    /* There is not enough free space left, this is probably a retry because user orders which
                     * will exceed the threshold will be blocked in the upper layer already
                     * --> Abort the write order, perform a hard sector reorganization and retry
                     * the whole write process after the Reorg*/
                    xRetVal_en = FEE_SECTORFULL_E;

                }

            }
            else
            {
                // A LLWrite loop to write a second copy for a 2sec block
                // --> Don't execute the check
            }


            // If the NoFallback feature is active, go to the specific handler.
            // Otherwise continue the actual write
            // If the decision was taken to execute the HSR, the state is going to be reset to Init
            // at the end of the function.
            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_BLANKCHECK_NOFB_WR_E;
            #else
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
            #endif


        }break;





#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        case FEE_LL_WR_BLANKCHECK_NOFB_WR_E:
        {
           if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
            {
                /* Check if an old copy of the block is existing and also configured as NoFallback */
                if ((Info_ptr->AdrBlkHeader_u32 != FEE_MAXUINT32) && (Fee_Rb_NoFallback_LastBlockCfg_b != FALSE))
                {
                    // Execute a blankcheck on the NoFB marker address before writing to prevent a uCSafetyFault on Renesas if the addess is non-blank

                    if( Fls_Rb_BlankCheck( (Info_ptr->AdrBlkHeader_u32 - FEE_PAGE_LEN) , NULL_PTR , FEE_PAGE_LEN)!= E_OK)
                    {
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    else
                    {
                        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_BLANKCHECK_NOFB_WR_WAIT_E;
                    }
                }
                else
                {
                    // block is NoFallback, but no old copy was found
                    //or the old copy wasn't configured as NoFallback
                    //--> NoFB Marker Write is forbidden
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_E;
                }
            }
            else
            {
                /* The block is not configured as NoFallback
                 * -> go on with writing the header immediately */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
            }

        }break;



        /* Write the NoFallback marker */
        case FEE_LL_WR_WRITE_NOFB_MARKER_E:
        {

            /* Check the NoFallback configuration for the current write order */
            if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
            {
                /* Check if an old copy of the block is existing and also configured as NoFallback */
                if ((Info_ptr->AdrBlkHeader_u32 != FEE_MAXUINT32) && (Fee_Rb_NoFallback_LastBlockCfg_b != FALSE))
                {
                    /* Write the NoFallback marker to invalidate the old copy before writing any new copy */
                    if (Fls_Write(Info_ptr->AdrBlkHeader_u32 - FEE_PAGE_LEN, Fee_NoFallbackMarkerPattern, FEE_PAGE_LEN) != E_NOT_OK)
                    {
                        /* Wait for the over programming to finish */
                        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_NOFB_MARKER_WAIT_E;
                    }
                    else
                    {
                        /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                        xRetVal_en = FEE_ABORTED_E;
                    }
                }
                else
                {
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_E;
                }
            }
            else
            {
                /* The block is not configured as NoFallback
                 * -> go on with writing the header immediately */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
            }
        }
        break;


        /* The next sector will be used for writing in case the NoFallback marker and the block header does't fit
         * into the current sector. To avoid GhostHeaders the last 2 Pages are written. */
        case FEE_LL_WR_FILL_SECTOR_END_E:
        {
            /* Calculate number of bytes necessary to store the block header only */
            xNumBytes_u16 = FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN;

            /* Get the current physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Check if the sector is already filled up */
            if ((((Fee_RdWrOrder_st.xWrAddress + FEE_PAGE_LEN + xNumBytes_u16) - 1u) > Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32) &&
                (Fee_RdWrOrder_st.xWrAddress != Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32))
            {
                /* Fill the sector end with the NoFallback marker pattern */
                if (Fls_Write(Fee_RdWrOrder_st.xWrAddress,
                              Fee_NoFallbackMarkerPattern,
                              (Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 - Fee_RdWrOrder_st.xWrAddress) + 1u) != E_NOT_OK)
                {
                    /* Since there is not enough space to write the NoFallback marker and the block header
                     * -> the write address is set to the end of the logical sector to switch to the next sector */
                    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32;

                    /* Wait for the over programming to finish */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_WAIT_E;
                }
                else
                {
                    /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                    xRetVal_en = FEE_ABORTED_E;
                }
            }
            else
            {
                /* The NoFallback marker and the block header fits into the current sector */

                /* Write the block header */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
            }
        }
        break;

        /* Errors during write occured */
        case FEE_LL_WR_FILL_SECTOR_END_ERROR_E:
        case FEE_LL_WR_WRITE_NOFB_MARKER_ERROR_E:
        {
            /* Return error */
            xRetVal_en = FEE_ERROR_E;
        }
        break;

#endif //(FEE_NO_FALLBACK_ACTIVE != FALSE)

        /* Write the block header */
        case FEE_LL_WR_WRITEHEADER_E:
        {
            /* Calculate number of bytes necessary to store the block header only */
            xNumBytes_u16 = FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN;


            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            /* Check the NoFallback configuration for the current write order */
            if ((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 & FEE_FLAG_NOFALLBACK_MSK) > 0u)
            {
                /* Increment the write address with the size of the NoFallback marker
                 * -> It is always insured that the current write address remains in the current sector */
                Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress, FEE_PAGE_LEN, TRUE);
            }
            #endif


            #if (STD_OFF != FEE_SET_MODE_SUPPORTED)
            /* Check for a FastMode order */
            if(Fls_Mode == MEMIF_MODE_FAST)
            {
                /* Align the address to 16 bytes but only if it is not already aligned */
                if ((Fee_RdWrOrder_st.xWrAddress % FEE_FASTMODE_ALIGNMENT) != 0u)
                {
                    /* Get the current physical sector index before aligning the write address
                     * -> Necessary in case the alignment leads to an overflow! */
                    xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

                    /* Align the write address */
                    Fee_RdWrOrder_st.xWrAddress &= (~((uint32)FEE_FASTMODE_ALIGNMENT - 1uL));
                    Fee_RdWrOrder_st.xWrAddress += FEE_FASTMODE_ALIGNMENT;

                    /* Overflow handling
                     * -> If the write address is after the alignment behind the logical end address,
                     *    the write address is set to the end of the logical sector */
                    if (Fee_RdWrOrder_st.xWrAddress >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
                    {
                        Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32;
                    }
                }
            }
            /* #if (STD_OFF != FEE_SET_MODE_SUPPORTED) */
            #endif


            /* 1st check: Check if the complete block header fits in the active sector */
            if(Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING) >= xNumBytes_u16)
            {

                #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
                /* For blocks > 2 pages, header will be written in 2 parts. */
                if ((Info_ptr->BlkLength_u16 + FEE_BLOCK_OVERHEAD) > (FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN))
                {
                    /* Block header must be stored in 2 steps. */
                    /* Store the address where 2nd header page must be programmed. */
                    Fee_RdWrOrder_st.xHdPg2Address = Fee_RdWrOrder_st.xWrAddress + FEE_PAGE_LEN;

                    /* Copy the 2nd page information to an internal buffer. */
                    Fee_SrvMemCopy8(Fee_hdr2Buffer_au8,(Fee_PageBytePtr_cpu8+FEE_PAGE_LEN),FEE_PAGE_LEN);

                    /* Only one page must be programmed. */
                    xTempNumBytes_u16 = FEE_PAGE_LEN;
                }
                else
                {
                    /* Block data fits into the header itself. Complete block can be written in 1 step itself. */
                    xTempNumBytes_u16 = xNumBytes_u16;

                    /* Set the xHdPg2Address = FEE_MAXUINT32 to indicate that the 2nd header page is also programmed. */
                    Fee_RdWrOrder_st.xHdPg2Address = FEE_MAXUINT32;
                }
                #else
                    xTempNumBytes_u16 = xNumBytes_u16;
                #endif
                /* Write the header and some data bytes */
                if(Fls_Write(Fee_RdWrOrder_st.xWrAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xTempNumBytes_u16) != E_NOT_OK)
                {
                    cntProgrammedBytes_u32 += xNumBytes_u16;

                    /* Save the address for the block header (will be used for the checksum verification in the flash) */
                    Info_ptr->AdrBlkHeader_u32 = Fee_RdWrOrder_st.xWrAddress;

                    /* Mark the cache entry in order to be safe against write interruptions */
                    Fee_LLUpdateAddressInCache(Info_ptr->FeeIndex_u16, FEE_CACHE_TMP_INVALID_VALUE);

                    /* Increment the write address (if increment is behind the sector end address, the address will be set to
                     * the sector end address) */
                    Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress, xNumBytes_u16, TRUE);

                    /* Wait for the write order to be finished */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_WAIT_E;
                }
                else
                {
                    /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                    xRetVal_en = FEE_ABORTED_E;
                }

            }
            else
            {
                /* There are not enough bytes free to store at least the complete header (the block header should
                 * not be splitted over several sectors!) */

                /* The FULL marker has to be written first */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_FULL_MARKER_E;

                /* Come back to the write header state after the FULL marker is written */
                Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
            }
        }
        break;

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        //Wait for the end of the blankcheck before writing a NoFB marker
        case FEE_LL_WR_BLANKCHECK_NOFB_WR_WAIT_E:
        /* Wait for the end of the programming */
        case FEE_LL_WR_WRITE_NOFB_MARKER_WAIT_E:
        /* Wait for the over programming to finish */
        case FEE_LL_WR_FILL_SECTOR_END_WAIT_E:
#endif
        /* Write the block header */
        case FEE_LL_WR_WRITEHEADER_WAIT_E:
        /* Wait for the verification to end */
        case FEE_LL_WR_VERIFYHEADER_WAIT_E:
        /* Wait for the write order to be finished */
        case FEE_LL_WR_WAIT_WRITEDATA_SEC_A_E:
        /* Wait for the 2nd header page write order to be finished */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        case FEE_LL_WR_WAIT_WRITEHDRPG2_E:
#endif
        {
            /* The next state (FEE_LL_WR_WRITEDATA_SEC_A_E / FEE_LL_WR_VERIFYHEADER_ERROR_E) will be set by
             * the Fee_JobEndNotification() or Fee_JobErrorNotification() function automatically
             * (the verification of the data will be done * in one step after the data was written) */

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

        /* Verify the header */
        case FEE_LL_WR_VERIFYHEADER_E:
        {
            #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            /* Check if complete header must be verified or only first page. */
            if (Fee_RdWrOrder_st.xHdPg2Address != FEE_MAXUINT32)
            {
                /* One header page 1 was programmed. */
                xTempNumBytes_u16 = FEE_PAGE_LEN;
            }
            else
            #endif
            {
                /* Complete block was programmed in one step, 2 bytes block or invalidate request. */
                xTempNumBytes_u16 = FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER;
            }

            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            if (Fls_Compare(Info_ptr->AdrBlkHeader_u32,
                            (uint8*)Fee_PageBytePtr_cpu8,
                            xTempNumBytes_u16) != E_OK)
            {
                /* An error occured due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }
            else
            {
                /* Set the next state */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFYHEADER_WAIT_E;
            }
        }
        break;

        /* Verify or write error */
        case FEE_LL_WR_WRITE_ERROR_E:
        {
            #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
            /* check if the robust handling for IFX flashes is necessary */
            if (Fls_Rb_GetRobustProgStatus(&Fee_IfxRobustProgramming_s.xStartAddress,  &Fee_IfxRobustProgramming_s.DataBuffer, &Fee_IfxRobustProgramming_s.numBytes) == E_NOT_OK)
            {
                /* Fls_Write was finished with success */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEDATA_IFX_HANDLING_E;
            }
            else
            #endif
            {
                xRetVal_en = FEE_ERROR_E;
            }
        }
        break;



        case FEE_LL_WR_VERIFYHEADER_ERROR_E:
        {
           /* The current block header in the flash is invalid
            * --> execute write order again at the next write address (increment was
            *     done already by the number of programmed bytes)
            * --> Return an error */
           xRetVal_en = FEE_ERROR_E;
        }
        break;

        /* Prepare the data */
        case FEE_LL_WR_WRITEDATA_SEC_A_E:
        {
            /* Calculate the amount of bytes which are left (maybe the header pages already contain
             * all necessary data bytes) */
            xNumBytes_u16 = (uint16)(Info_ptr->BlkLength_u16 - Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16);

            /* Check if an additional write order is necessary */
            if (xNumBytes_u16 == 0)
            {
                /* Block header pages and the complete data has already been written, verify the content */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFY_BLK_E;
            }
            else
            {
                /* Calculate number of free bytes in the currently active sector */
                xNumFreeBytes_u32 = Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING);

                /* At least one page has to be free */
                if (xNumFreeBytes_u32 >= FEE_PAGE_LEN)
                {
                    /* Check if the complete data can be written to the active sector */
                    if(xNumFreeBytes_u32 < xNumBytes_u16)
                    {
                        /* Restrict number of bytes to the maximum for the currently active sector */
                        xNumBytes_u16 = (uint16)xNumFreeBytes_u32;
                    }

                    /* The complete data buffer can be used this time,
                     * check if the complete data fits into the internal data buffer */
                    if(FEE_LL_DATABUFFSIZE < xNumBytes_u16)
                    {
                        /* Restrict the number of bytes to the maximum size of the internal data buffer */
                        xNumBytes_u16 = FEE_LL_DATABUFFSIZE;
                    }

					if((xNumBytes_u16 % FEE_VIRTUAL_PAGE_SIZE) != 0U)
					{
						xTempPadding = FEE_VIRTUAL_PAGE_SIZE - (xNumBytes_u16 % FEE_VIRTUAL_PAGE_SIZE);
					}
                    /* Reset the page buffer to make sure no wrong data remains inside */
                    Fee_SrvMemSet8((uint8*)&Fee_DataBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, (xNumBytes_u16 + xTempPadding));

                    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
                    /* Increment the considered Crc bytes */
                    xNumCrcBytesDone_u8 = 0;

                    /* Get the number of cut off bytes */
                    xNumBytesCutOff_u16 = (uint16)((Info_ptr->BlkLength_u16 - Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16) - xNumBytes_u16);

                    /* Check for an activated robustness attribute */
                    if((((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                          (uint16)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint16)FEE_FLAG_ROBUST_ATTR_BP) > 0))
                    {
                        /* The robust feature is active for this block, check if this is the
                         * last complete data transfer */
                        if(((uint16)((Info_ptr->BlkLength_u16 -
                                      Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16) - xNumBytes_u16)) < FEE_SIZE_OF_BLOCK_CS)
                        {
                            /* The last transfer with data only has finished, now the checksum is at least part
                             * of the stream and must be considered */

                            /* Get the offset for the CRC transfer, e.g. 3 Bytes:
                             *
                             * xCrcOffset_u8:           0  1  2  3 |  1  2  3
                             * xNumBytes_u16:           4  3  2  1 |  3  2  1
                             * xBlkCrc32Result_u32:    5A C3 B8 76 | C3 B8 76
                             * Fee_DataBytePtr_cpu8[]: 76 B8 C3 5A | 76 B8 5A
                             *
                             * */
                            if((Info_ptr->BlkLength_u16 - Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16) > FEE_SIZE_OF_BLOCK_CS)
                            {
                                /* The first CRC byte has to be transfered */
                                xCrcOffset_u8 = 0;
                            }
                            else
                            {
                                /* Some CRC bytes have already been transfered */
                                xCrcOffset_u8 = (uint8)(FEE_SIZE_OF_BLOCK_CS -
                                                       (Info_ptr->BlkLength_u16 - Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16));
                            }

                            /* Get the number of CRC bytes to transfer this time */
                            if(xNumBytesCutOff_u16 > FEE_SIZE_OF_BLOCK_CS)
                            {
                                /* No CRC bytes can be transfered now, only the complete data fits into
                                 * the current sector or data buffer */
                                xNumCrcBytes_u8 = 0;
                            }
                            else
                            {
                                /* Some CRC bytes can be added now */
                                if((xNumBytesCutOff_u16 == 0) && (xNumBytes_u16 < FEE_SIZE_OF_BLOCK_CS))
                                {
                                    /* All the bytes to be transfered are CRC bytes and there is no limitation */
                                    xNumCrcBytes_u8 = (uint8)(xNumBytes_u16);
                                }
                                else
                                {
                                    /* The number of bytes to transfer is limited */
                                    xNumCrcBytes_u8 = (uint8)(FEE_SIZE_OF_BLOCK_CS - xNumBytesCutOff_u16);
                                }
                            }

                            /* Check if data bytes are left */
                            if(xNumBytes_u16 > xNumCrcBytes_u8)
                            {
                                /* Data bytes are left */
                                Fee_SrvMemCopy8((uint8*)&Fee_DataBytePtr_cpu8[0],
                                                &Data_pcu8[Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16],
                                                (xNumBytes_u16 - xNumCrcBytes_u8));

                                /* Calculate the CRC for the user data over the internal data buffer */
                                xBlkCrc32Tmp_u32 = Crc_CalculateCRC32(&Fee_DataBytePtr_cpu8[0],
                                                                     (uint32)(xNumBytes_u16 -
                                                                              xNumCrcBytes_u8),
                                                                     xBlkCrc32Result_u32,
                                                                     FALSE);

                                /* Save the final checksum */
                                xBlkCrc32Result_u32 = xBlkCrc32Tmp_u32;

                                /* Add data offset */
                                xNumCrcBytesDone_u8 = (uint8)(xNumBytes_u16 - xNumCrcBytes_u8);
                            }

                            /* Loop over the CRC bytes (amount of bytes to transfer is set by xNumBytes_u16) */
                            for(i_u8=0; i_u8<xNumCrcBytes_u8; i_u8++)
                            {
                                /* Prepare the data buffer with the robustness CRC */
                                Fee_DataBytePtr_cpu8[xNumCrcBytesDone_u8 + i_u8] =
                                                                  (uint8)((xBlkCrc32Result_u32 >> ((24 - (i_u8*8)) - (xCrcOffset_u8*8))) & 0xFFu);
                            }
                        }
                        else
                        {
                            /* Additional transfers might follow, continue with copying the data only */
                            Fee_SrvMemCopy8((uint8*)&Fee_DataBytePtr_cpu8[0],
                                            &Data_pcu8[Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16],
                                            xNumBytes_u16);

                            /* Calculate the CRC for the user data over the internal data buffer */
                            xBlkCrc32Tmp_u32 = Crc_CalculateCRC32(&Fee_DataBytePtr_cpu8[0],
                                                                 (uint32)xNumBytes_u16,
                                                                  xBlkCrc32Result_u32,
                                                                  FALSE);

                            /* Save the start value for the next call */
                            xBlkCrc32Result_u32 = xBlkCrc32Tmp_u32;
                        }
                    }
                    else
                    #endif
                    {
                        /* The robustness feature is inactive, continue with copying the data only */
                        Fee_SrvMemCopy8((uint8*)&Fee_DataBytePtr_cpu8[0],
                                        &Data_pcu8[Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16],
                                        xNumBytes_u16);
                    }

                    /* Write the data, rounding up to the nearest FEE_VIRTUAL_PAGE_SIZE */
                    if(Fls_Write(Fee_RdWrOrder_st.xWrAddress, &Fee_DataBytePtr_cpu8[0], (xNumBytes_u16 + xTempPadding)) != E_NOT_OK)
                    {
                        cntProgrammedBytes_u32 += xNumBytes_u16;

                        /* Update amount of already programmed data (will be used to calculate the rest in the next run) */
                        Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 = (uint16)(Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 +
                                                                               xNumBytes_u16);

                        /* Increment the write address (if increment is behind the sector end address, the address will be set to
                         * the sector end address */
                        Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress, xNumBytes_u16, TRUE);

                        /* Wait for the write order to be finished */
                        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WAIT_WRITEDATA_SEC_A_E;
                    }
                    else
                    {
                        /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                        xRetVal_en = FEE_ABORTED_E;
                    }
                }
                else
                {
                    /* The sector is full */

                    /* The FULL marker has to be written first */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_FULL_MARKER_E;

                    /* Come back to the write data state after the FULL marker is written */
                    Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_WRITEDATA_SEC_A_E;
                }
            }
        }
        break;

        /* Write the FULL marker */
        case FEE_LL_WR_WRITE_FULL_MARKER_E:
        {
            /* Get the physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the FULL marker to the respective sector */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_FULL_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /*
                 * Writing of "FULL" Marker was finished
                 * -----------------------------------
                 * --> Set Fee_RdWrOrder_st.xWrAddress to the first empty page in next logical sector
                 * --> Write the USED Marker in the next logical sector
                 */

                /* Get logical sector and increment it */
                xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1);

                /* Check if switching from last to first sector requires an overflow */
                if (xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                {
                    /* Reset the logical sector index */
                    xLogSectIdx_u8 = FEE_NUM_FLASH_BANKS-1;
                }

                /* Get the new physical sector index */
                xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                /* Erase the new logical sector if necessary  */
                if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_STATE_UNDEF_E) ||
                   (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_REQUEST2ERASE_E))
                {
                    /* Mark this sector */
                    Fee_LLSetEraseSector(xLogSectIdx_u8);

                    /* Save new write address  */
                    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                    /* Set erase state */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_ERASE_SECTOR_E;

                    /* Come back to the write USED marker state after the ERASED marker is written */
                    Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;
                }
                else
                {
                    /* New logical sector is already erased */

                    /* Set the new write address */
                    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                    /* Write the USED marker next */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;
                }
            }
        }
        break;

        /* Erase the sector */
        case FEE_LL_WR_ERASE_SECTOR_E:
        {
            /* Get the erase result */
            xErSectorRetVal_en = Fee_LLEraseSector();

            /* Check the erase sector result */
            if(xErSectorRetVal_en != FEE_ORDER_PENDING_E)
            {
                /* Sector erase is done. New write address was already set before */

                /* Verify the error return */
                if((xErSectorRetVal_en == FEE_ERROR_E) || (xErSectorRetVal_en == FEE_ABORTED_E))
                {
                    /* Return an error
                     * --> Write order will be finished unsuccessfully because the error reaction
                     *     cannot be finished */
                    xRetVal_en = FEE_ERROR_E;
                }
                else
                {
                    /* Get back the previous state */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en;
                }
            }
        }
        break;

        /* Write the USED marker */
        case FEE_LL_WR_WRITE_USED_MARKER_E:
        {
            /* Get the new physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Mark the cache status for this sector */
            Fee_LLUpdateCacheStForSect(xPhySectIdx_u8);

            /* Write the USED marker */
            xWrMarkerRetVal_en = Fee_LLWriteMarker(xPhySectIdx_u8, FEE_USED_MARKER_ID_E);

            /* Check the write USED marker result */
            if(xWrMarkerRetVal_en != FEE_ORDER_PENDING_E)
            {
                /* Setting the write address to the first empty page in the next logical sector
                 * was already set in the the previous state (FEE_LL_WR_WRITE_FULL_MARKER_E) */

                /* Verify whether it was possible to write the USED marker or not */
                if(xWrMarkerRetVal_en == FEE_ORDER_FINISHED_E)
                {
                    /* Write Marker with the start-Address as Payload. This marker is more or less the double storage
                     * of the USED Marker and contains the Address of the first  blockheader */
                    tmpAddr_u32 = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                    /* Calculate how many bytes have to be written in the "new" sector */
                    if (cntProgrammedBytes_u32 > 0uL)
                    {
                        /* Parts of the block are in the "old" (and hopefully FULL) sector.
                         * -> calculate number of bytes which will be stored from the current block into the "new" sector */
                        tmpAddr_u32 += (uint32)(FEE_BLOCK_OVERHEAD + Info_ptr->BlkLength_u16) - cntProgrammedBytes_u32;

                        /* Ensure correct page alignment */
                        while ((tmpAddr_u32 % FEE_PAGE_LEN) != 0u)
                        {
                            tmpAddr_u32++;
                        }

                        /* Check if the block is maybe greater then 1 sector and so the sector contains programmed pages, but no blockheader */
                        if (tmpAddr_u32 >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
                        {
                            tmpAddr_u32 = FEE_MAXUINT32;
                        }
                    }
                    else
                    {
                        /* First blockheader will be stored on the first page of the logic sector.
                         * -> No additional correction required */
                    }

                    Fee_RdWrOrder_st.xStartAddrNextSector_u32 = tmpAddr_u32;

                    /* Get back to the previous state */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_START_MARKER_E;
                }
                else
                {
                    /* The complete sector has to be erased again. Otherwise there might be
                     * data getting lost in the future! */

                    /* Get corresponding logical sector */
                    xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];

                    /* Mark this sector */
                    Fee_LLSetEraseSector(xLogSectIdx_u8);

                    /* Set erase state */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_ERASE_SECTOR_E;

                    /* Come back to the write USED marker state after the ERASED marker is written
                     * (Next state after the write USED marker state was already saved to
                     *  Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en in the former step)*/
                    Fee_RdWrOrder_st.Fee_LLNextEraseWrBlock_en = FEE_LL_WR_WRITE_USED_MARKER_E;
                }
            }
        }
        break;

        /* Write the START marker */
        case FEE_LL_WR_WRITE_START_MARKER_E:
        {
            /* Get the new physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the USED marker */
            xWrMarkerRetVal_en = Fee_LLWriteMarker(xPhySectIdx_u8, FEE_START_MARKER_ID_E);

            /* Check the write USED marker result */
            if(xWrMarkerRetVal_en != FEE_ORDER_PENDING_E)
            {
                /* Get back to the previous state */
                Fee_RdWrOrder_st.Fee_LLWrBlock_en = Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en;
            }
        }
        break;

        /* Verify the block data and header content */
        case FEE_LL_WR_VERIFY_BLK_E:
        {
            /* Check if the complete block was written first (blocks are always written with as much data as possible) */
            if(Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 < Fee_GlobInfoLastRdHeader_st.BlkLength_u16)
            {
                /* Check whether the last order filled up the sector already or not */
                if(Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING) == 0u)
                {
                    /* The current sector was filled up completely and there are still data bytes to
                     * program. Necessary steps:
                     * 1. write FULL marker
                     * 2. switch active write sector
                     * 3. write USED marker
                     * 4. write the rest of the data
                     */

                    /* Set the next state */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_FULL_MARKER_E;

                    /* Come back to the write data state after the FULL marker was written */
                    Fee_RdWrOrder_st.Fee_LLNextUsedWrBlock_en = FEE_LL_WR_WRITEDATA_SEC_A_E;
                }
                else
                {
                    /* Go on with the write order */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEDATA_SEC_A_E;
                }
            }
            else
            {
                #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
                /* Check if 2nd header page is programmed. */
                if (Fee_RdWrOrder_st.xHdPg2Address != FEE_MAXUINT32)
                {
                    /* First write the 2nd header page. */
                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHDRPG2_E;
                }
                else
                #endif
                {
                    /* Compare the complete programmed data including the block header */
                    xCompareRetVal_en = Fee_LLCalcBlkCrcInFlash(Info_ptr);

                    /* Check the busy state of the compare function */
                    if(xCompareRetVal_en != FEE_ORDER_PENDING_E)
                    {
                        /* Check the compare result */
                        if(xCompareRetVal_en == FEE_ORDER_FINISHED_E)
                        {
                            /* Block in flash is correct, verify the security level depending
                             * on the config out of the PFlash, not out of the DFlash */

                            /* Verify the security level out of the PFlash */
                            // Shift isn't required when accessing the security bit because it has the offset 0
                            if(((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                                    FEE_FLAG_SEC_LEVEL_MSK) == FEE_BLK_INT_DOUBLE_STORAGE) &&
                             (Fee_GlobInfoWrBlock_st.cntCopies_u8 == FEE_CNT_FIRST_COPY))
                            {
                                /* Reset state machine because there is still one copy to program */
                                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_BLK_INIT_E;

                                /* Increment the copy counter for the next check */
                                Fee_GlobInfoWrBlock_st.cntCopies_u8++;

                                #if(FEE_NO_FALLBACK_ACTIVE != FALSE)
                                /* Set the address of the second copy of this block to write the NoFallback marker */
                                Info_ptr->AdrBlkHeader_u32 = Fee_Rb_NoFallback_RemAdr_u32;
                                #endif

                                /* Reset the already considered bytes */
                                Fee_LLPrepPageBufWithHdrDataStart(Info_ptr);
                                Fee_LLPrepPageBufWithHdrDataEnd(Info_ptr, Data_pcu8, Info_ptr->BlkCrc32_u32);
                            }
                            else
                            {
                                /* All required copies were stored correctly */
                                xRetVal_en = FEE_ORDER_FINISHED_E;
                            }

                            /* The cache update was already done inside the compare function */
                        }
                        else
                        {
                            /* The current block in flash is invalid or the compare order was aborted
                             * --> execute write order again at the next write address (increment was
                             *     done already by the number of programmed bytes) */
                            /* Return error */
                            xRetVal_en = FEE_ERROR_E;

                            /* Workaround Overstamp invalid header to reduce init time */
                            #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
                            if(xCompareRetVal_en == FEE_ERROR_E)
                            {
                                if(E_NOT_OK != Fls_Write(Info_ptr->AdrBlkHeader_u32, Fee_hdrBuffer_au8, FEE_PAGE_LEN))
                                {
                                    Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WAIT_FOR_FLS_OVERPROGRAMMING_E;
                                    xRetVal_en                        = FEE_ORDER_PENDING_E;
                                }
                                else
                                {
                                }
                            }
                            #endif
                            /* END Workaround Overstamp invalid header to reduce init time */
                        }
                    }
                }
            }
        }
        break;

        /* Workaround Overstamp invalid header to reduce init time */
        #if (defined(RBA_FLSIFX_FLASH) || defined(RBA_FLSJDP_FLASH))
        case FEE_LL_WR_WAIT_FOR_FLS_OVERPROGRAMMING_E:
        {
            if(Fls_GetJobResult() != MEMIF_JOB_PENDING)
            {
                xRetVal_en = FEE_ERROR_E;
            }
        }
        break;
        #endif
        /* END Workaround Overstamp invalid header to reduce init time */

        #if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        case FEE_LL_WR_WRITEHDRPG2_E:
        {
            /* Trigger write for 2nd header page. */
            if(Fls_Write(Fee_RdWrOrder_st.xHdPg2Address, (uint8*)&Fee_hdr2Buffer_au8[0], FEE_PAGE_LEN) != E_NOT_OK)
            {
                /* Set the xHdPg2Address = FEE_MAXUINT32 to indicate that 2nd header page write is started */
                Fee_RdWrOrder_st.xHdPg2Address = FEE_MAXUINT32;

                Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WAIT_WRITEHDRPG2_E;
            }
            else
            {
                /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }
        }break;
        #endif

        #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
        case FEE_LL_WR_WRITEDATA_IFX_HANDLING_E:
        {
            /* Get the new physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Get corresponding logical sector */
            xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];

            if (Fee_RobIfxHandling(xLogSectIdx_u8) != FEE_ORDER_PENDING_E)
            {
                xRetVal_en = FEE_ERROR_E;
            }
        }
        break;
        #endif

        /* Default */
        default:
        {
            /* State should never be reached */
            xRetVal_en = FEE_ABORTED_E;
        }
        break;
    }


    /* Reset state machine if necessary */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Order was finished with or without error */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_BLK_INIT_E;

        /* This additional reset is necessary, because it cannot be reset in the initialization state */
        Fee_GlobInfoWrBlock_st.cntCopies_u8 = FEE_CNT_FIRST_COPY;
    }

    return (xRetVal_en);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

#if(FEE_ROBUST_PROG_ACTIVE != FALSE)
#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
Fee_RobIfxHdl_e Fee_RobIfxHdl;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
/* MR12 RULE 8.5 VIOLATION: This variable needs to keep its value but it is not used outside of this file */
#define FEE_START_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"
uint8 Fee_RobMarkerBuff_au8[FEE_ROBMARKER_BUFF_SIZE];
#define FEE_STOP_SEC_VAR_CLEARED_8
#include "Fee_MemMap.h"

/**
 ***************************************************************************************************
 * Fee_RobIfxHandling(): Funktion to handle robust programming algorithm for Ifx DFLASHs
 *
 * In case of a wordline fail, this function is called and will do the following steps:
 * 1. check if the next logical sector is erased. If not, erase this sector.
 * 2. write the clone marker in the new sector. This marker indicates that there might be data
 *    in the sector, written by this algorithm
 * 3. copy the data of the defect wordline at the same location in the clone sector
 * 4. copy data 1:1 from the old sector to the new sector, starting after the sectorheader,
 *    stopping at the wordline which causes the defect
 * 5. writing the used marker in the sector
 * 6. sort the now old sector at the end of the logical list.
 *
 * \param    none
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS write function call
 * \retval   FEE_ERROR_E:           writing is still done in the last logical sector. Do not
 *                                  start the algotihm.
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully
 * \seealso
 * \usedresources
 ***************************************************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_RobIfxHandling(uint8 xActLogWrSect_u8)
{
    Fee_stRetVal_ten xRetVal_en = FEE_ORDER_PENDING_E;
    uint32 i;
    uint8 xLogSectIdx_u8;
    uint8 xPhySectIdx_u8;
    Fls_AddressType BaseAddress;
    uint32 tmpNumBytes2Clone_u32;
    uint32 xOffsetInSector_u32;
    uint8 xPhySecIdx_u8;

    switch (Fee_RobIfxHdl){
        case FEE_ROB_IFX_INIT:
        {
            /* in the statemashine of the robustness algorithmus for IFX programming, at least one marker has to be written. During this
             * write, max. the marker-section size will be overwritten in the Wordline-Buffer, again. To prevent loss of data, this buffer
             * has to be backuped before starting any marker or erase operation. */
            for (i=0;i<FEE_ROBMARKER_BUFF_SIZE;i++)
            {
                Fee_RobMarkerBuff_au8[i] = Fee_IfxRobustProgramming_s.DataBuffer[i];
            }
            /* check if the next sector is erased */
            /* Get the logical sector index */
            xLogSectIdx_u8 = xActLogWrSect_u8;

            xOffsetInSector_u32 = Fee_IfxRobustProgramming_s.xStartAddress - Fee_FlashProp_st[Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8].Fee_PhysStartAddress_u32;

            xLogSectIdx_u8++;

            if (xLogSectIdx_u8 < FEE_NUM_FLASH_BANKS)
            {
                /* We are not in the last sector --> it should be possible to start with the robust Ifx Flash handling */
                /* first, set write address to the logical start address of the next sector */
                Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8].Fee_PhysStartAddress_u32;

                /* calculate correct WriteAddress */
                Fee_RdWrOrder_st.xWrAddress += xOffsetInSector_u32;

                /* check if the first wordline is in the buffer. In this case it is necessary to start programming AFTER the sector header section */
                if (Fee_RdWrOrder_st.xWrAddress <= Fee_LLGetSecStartAddress(Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8))
                {
                    /* set write address to the beginn of the logical sector */
                    Fee_RdWrOrder_st.xWrAddress = Fee_LLGetSecStartAddress(Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8);

                    /* calculate now the offset in the buffer to ensure, that data has to be copied. Theoretically it could be happen that the error happens
                     * inside the sector header and so nothing could be stored ore copied! */
                    xOffsetInSector_u32 = Fee_RdWrOrder_st.xWrAddress - Fee_FlashProp_st[Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8].Fee_PhysStartAddress_u32;

                    if (xOffsetInSector_u32 >= Fee_IfxRobustProgramming_s.numBytes)
                    {
                        Fee_IfxRobustProgramming_s.numBytes = 0;
                    }else{
                        /* start copying of the buffer with the offset of the sector header */
                        /* MR12 RULE 10.3 VIOLATION: Masking is faster and more efficient */
                        Fee_IfxRobustProgramming_s.offInBuf_u16 = (uint16)(Fee_RdWrOrder_st.xWrAddress & FEE_MAXUINT16);

                        /* reduce number of byte that have to be programmed in the flash */
                        Fee_IfxRobustProgramming_s.numBytes -= Fee_IfxRobustProgramming_s.offInBuf_u16;
                    }
                }
                else
                {
                    Fee_IfxRobustProgramming_s.offInBuf_u16 = 0;
                }
                if (Fee_IfxRobustProgramming_s.numBytes > 0uL)
                {
                    /* now check if the next sector is still erased */
                    if (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en ==  FEE_SECTOR_ERASED_E)
                    {
                        /* the next logical sector is still erase --> mark this sector as clone sector */
                        Fee_RobIfxHdl = FEE_ROB_IFX_MARK_SECTOR;
                    }
                    else
                    {
                        /* the sector which should be used to clone the current sector is not erased yet --> erase this sector first */
                        Fee_LLSetEraseSector(xLogSectIdx_u8);
                        Fee_RobIfxHdl = FEE_ROB_IFX_ERASE_SECTOR;
                    }
                }
                else
                {
                    /* the wordline error happens while writing in the sector header --> now robust handling for this use case planned
                     * --> finish special handling */
                    Fee_RobIfxHdl = FEE_ROB_IFX_FINISHED;
                }

            }else{
                xRetVal_en = FEE_ERROR_E;
            }
        }break;

        case FEE_ROB_IFX_MARK_SECTOR:
        {
            /* Get the physical sector index of the FULL sector */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the CLONE_START marker */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_CLONE_START_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /* in the sector header, there is the information available, that a clone procedure has started. Now it
                 * is allowed to write data in this sector.
                 */
                Fee_RobIfxHdl = FEE_ROB_IFX_STORE_BUFFER;
            }
        }break;

        case FEE_ROB_IFX_STORE_BUFFER:
        {
            /* before writing the buffer, it was necessary to write at least one marker. Because the Fls-Driver will always backup the WordLine, it is
             * possible that the whole markersection in the buffer was overwritten. Because of this, the markersection size of the buffer was backuped
             * and has to be restored before writing this data, too. */
            for (i=0;i<FEE_ROBMARKER_BUFF_SIZE;i++)
            {
                (Fee_IfxRobustProgramming_s.DataBuffer[i]) = Fee_RobMarkerBuff_au8[i];
            }

            if(Fls_Write(Fee_RdWrOrder_st.xWrAddress, (uint8*)(&Fee_IfxRobustProgramming_s.DataBuffer[Fee_IfxRobustProgramming_s.offInBuf_u16]), Fee_IfxRobustProgramming_s.numBytes) != E_NOT_OK)
            {
                Fee_RdWrOrder_st.xWrAddress += Fee_IfxRobustProgramming_s.numBytes;
                /* Wait for the write order to be finished */
                Fee_RobIfxHdl = FEE_ROB_IFX_STORE_BUFFER_WAIT;
            }
            else
            {
                /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }

        }break;

        case FEE_ROB_IFX_STORE_BUFFER_WAIT:
        {
            /* The next state (FEE_ROB_IFX_COPY_DATA) will be set by the Fee_JobEndNotification() or
             * Fee_JobErrorNotification() function automatically */

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
        }break;

        case FEE_ROB_IFX_COPY_DATA:
        {
            /* if there is a offset in the data buffer, the first wordline had the error. In this case there is no data to copy --> go directly in the state
            * Write-Used-Marker */
            if (Fee_IfxRobustProgramming_s.offInBuf_u16 == 0)
            {
                /* in the state FEE_ROB_IFX_INIT the xLogSectIdx_u8 was incremented once and so the new sector was found. The current write
                * address could not belong to the logical oldest sector --> new calculation of the previous sector is possible */
                xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);
                xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];
                /* start-Address of copying data is the start-address of the logical sector */
                Fee_RdWrOrder_st.xWrAddress = Fee_LLGetSecStartAddress(xPhySectIdx_u8);

                /* switch back to the sector which was used bevore */
                xLogSectIdx_u8--;

                /* start-Address is the start of the logical sector which was used bevore */
                BaseAddress = Fee_LLGetSecStartAddress(Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8);

                /* start- and base-address are both in the old sector. The difference is the number of byte that have to be programmed */
                tmpNumBytes2Clone_u32 = Fee_IfxRobustProgramming_s.xStartAddress - BaseAddress;

                /* if the error happens while programming the first wordline, it is possible that no data could be copied. In this case go directly to writing the
                * used marker */
                /* Write the data. The Write-Address was set into the correct sector in the state FEE_ROB_IFX_INIT. */
                /* MISRA RULE 11.3 VIOLATION: Cast necessary and not critical */
                if(Fls_Write(Fee_RdWrOrder_st.xWrAddress, (uint8*)BaseAddress, tmpNumBytes2Clone_u32) != E_NOT_OK)
                {
                    /* add copied bytes to the write address */
                    Fee_RdWrOrder_st.xWrAddress += tmpNumBytes2Clone_u32;

                    /* add bytes in the clone buffer */
                    Fee_RdWrOrder_st.xWrAddress +=  Fee_IfxRobustProgramming_s.numBytes;

                    /* Wait for the write order to be finished */
                    Fee_RobIfxHdl = FEE_ROB_IFX_STORE_COPY_WAIT;
                }
                else
                {
                    /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                    xRetVal_en = FEE_ABORTED_E;
                }
            }
            else
            {
                Fee_RobIfxHdl = FEE_ROB_IFX_WRITE_USED_MARK_SECTOR;
            }
        }break;

        case FEE_ROB_IFX_STORE_COPY_WAIT:
        {
            /* The next state (FEE_ROB_IFX_COPY_DATA) will be set by the Fee_JobEndNotification() or
            * Fee_JobErrorNotification() function automatically */

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
        }break;

        case FEE_ROB_IFX_ERASE_SECTOR:
        {
            if(Fee_LLEraseSector() == FEE_ORDER_FINISHED_E)
            {
                /* the next logical sector is now erased --> mark this sector as clone sector */
                Fee_RobIfxHdl = FEE_ROB_IFX_MARK_SECTOR;
            }
        }break;

        case FEE_ROB_IFX_WRITE_USED_MARK_SECTOR:
        {
            /* Get the physical sector index of the FULL sector */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the CLONE_START marker */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_USED_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /* in the sector header, there is the information available, that a clone procedure has started. Now it
                 * is allowed to write data in this sector.
                 */
                Fee_RobIfxHdl = FEE_ROB_SORT_SECTOR;
            }
        }break;

        case FEE_ROB_SORT_SECTOR:
        {
            /* step1: invalidate complete cache */
            for (i=0;i<FEE_NUM_BLOCKS;i++)
            {
                Fee_Cache_au32[i] = FEE_CACHE_TMP_INVALID_VALUE;
            }

            /* step2: invalidate sector cache state */
            for (i=0;i<FEE_NUM_FLASH_BANKS_AVAILABLE;i++)
            {
                Fee_CacheUpdCompForSect_au8[i] = FEE_CACHE_UPD_NOT_COMP_FOR_SECT;
            }
            /* step3: now it is possible that the hard reorganisation has to be startet, because free space in flash was reduced by 1
             * sector. To prevent any replacement reaction, it is a great idea to put the old sector at the end of the sector list and
             * mark the sector with request to erase marker. */

            /* in the state FEE_ROB_IFX_INIT the xLogSectIdx_u8 was incremented once and so the new sector was found. The current write
             * address could not belong to the logical oldest sector --> new calculation of the previous sector is possible */
            xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress)];
            xPhySecIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8-1].xPhySecIdx_u8;

            /* Loop over all sectors and reorganize the sector order:
             * - The sector with the error in the wordl-line will be set to the last entry in the array
             * - the clone sector (and all following sectors) will be shifted by 1 entry
             *
             */
            for( ; xLogSectIdx_u8<FEE_NUM_FLASH_BANKS; xLogSectIdx_u8++)
            {
                /* Reorganize the sector order */
                Fee_LLSectorOrder_st[xLogSectIdx_u8-1] = Fee_LLSectorOrder_st[xLogSectIdx_u8];

                /* Reorganize the array Ram table */
                Fee_idxLLSectorOrder_au8[Fee_LLSectorOrder_st[xLogSectIdx_u8-1].xPhySecIdx_u8] = xLogSectIdx_u8-1;
            }

            /* Update the state information of the last sector in the ring with the data of the sector with the wordline failure. */
            Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].xPhySecIdx_u8   = xPhySecIdx_u8;
            Fee_idxLLSectorOrder_au8[xPhySecIdx_u8] = FEE_NUM_FLASH_BANKS-1;

            /* mark the last sector as ready to erase */
            Fee_LLSetEraseSector(FEE_NUM_FLASH_BANKS-1);

            Fee_RobIfxHdl = FEE_ROB_IFX_FINISHED;
        }
        break;

        case FEE_ROB_IFX_FINISHED:
        default:
        {
            xRetVal_en = FEE_ORDER_FINISHED_E;
        }
        break;
    }

    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        Fee_RobIfxHdl = FEE_ROB_IFX_INIT;
    }
    return(xRetVal_en);
}
/* FEE_ROBUST_PROG_ACTIVE */
#endif

#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
