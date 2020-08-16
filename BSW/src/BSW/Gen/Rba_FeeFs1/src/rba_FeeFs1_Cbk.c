


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
#include "rba_FeeFs1_Cbk.h"
#include "rba_FeeFs1_Prv.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_JobEndNotification(): Service for reporting a successful end
 *                           of an asynchronous operation.
 *
 * This function reports a successful end of an asynchronous
 * operation (FEE095). The function call has to be configured in the
 * Fls module in order to be called automatically whenever an
 * asynchronous operation was finished. Alternatively the
 * Fls_GetJobResult() functionality can be used depending on
 * "FEE_POLLING_MODE".
 *
 * Hint:
 * Deviation from the AR SWS:
 * - Whether a read or write operation is finished cannot be detected
 *   within this function (function call can be interrupt level).
 *   A finished block will be detected in the Fee_MainFunction.
 *   --> FEE052 and FEE142 is realized there
 * - FEE052: The function Fee_JobEndNotification shall perform any
 *   necessary block management operations and subsequently call
 *   the job end notification routine of the upper layer module if
 *   configured.
 * - FEE142: If the job result is currently MEMIF_JOB_PENDING, the
 *   function Fee_JobEndNotification shall set the job result to
 *   MEMIF_JOB_OK, else it shall leave the job result untouched.
 *
 * Note:
 * The function Fee_JobEndNotification shall be callable on
 * interrupt level.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#if (STD_OFF == FEE_POLLING_MODE)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_JobEndNotification(void)
#else
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_SwitchJobEndNotification(void)
#endif
{
    /* Switch the read state machine */
    if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_WAIT_READ_PAGE_E)
    {
        /* Fls_Read was finished with success */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_FINISHED_E;
    }
    else
    {
        /* Fasten up most common use case */

        /* Switch the read state machine */
        if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_BLANK_CHECK_WAIT_E)
        {
            /* Fls_Rb_BlankCheck was finished with success */
            Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_BLANK_CHECK_E;
        }

        /* Switch the blank check state machine */
        if(Fee_RdWrOrder_st.Fee_LLBlankCheckState_en == FEE_LL_WAIT_PERFORM_BLANK_CHECK_E)
        {
            /* Blank check was finished with success */
            Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_BLANK_CHECK_FINISHED_E;
        }

        /* Switch the sector detection state machine */
#if (defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH))
        if(Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en == FEE_LL_FINDEMPTYPGE_WAIT_E)
        {
            /* Chunk is blank */
            Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_RESULT_BLANK_E;
        }
#endif

        /* Switch the state machine of the function Fee_LLWriteMarker */
        if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_BLK_CHK_WAIT_E)
        {
            /* Fls_BlankCheck was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_FINISHED_E;
        }

        /* Switch the state machine of the function Fee_LLWriteMarker */
        if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_WRITE_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_VERIFY_E;
        }

        /* Switch the state machine of the function Fee_LLWriteMarker */
        if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_VERIFY_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_VERIFY_FINISHED_E;
        }

#if (FEE_HEADER_RECHECK_ACTIVE != FALSE)
        /* Switch state machine of the function Fee_LLSearchNextBlkHeader */
        if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_RECHECK_HEADER_WAIT_E)
        {
            /* Fls_Rb_BlankCheck was finished with success */
            Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_RECHECK_HEADER_FAILED_E;
        }

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        /* Switch state machine of the function Fee_LLSearchNextBlkHeader */
        if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_NOFALLBACK_MARKER_CHECK_WAIT_E)
        {
            /* Fls_Rb_BlankCheck was finished with success */
            Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_RECHECK_HEADER_E;
        }

        /* Switch state machine of the function Fee_LLWriteBlock */
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WRITE_NOFB_MARKER_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_E;
        }

        /* Switch state machine of the function Fee_LLWriteBlock */
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_FILL_SECTOR_END_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEHEADER_E;
        }

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_FILL_SECTOR_END_E)
        {
            /* Go back to the init state to continue the order */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E;
        }

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_WRITE_NOFB_MARKER_E)
        {
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_READ_E;
        }
/* FEE_NO_FALLBACK_ACTIVE != FALSE */
#endif
/* FEE_HEADER_RECHECK_ACTIVE != FALSE */
#endif

        /* Switch state machine of the function Fee_LLWriteBlock */
#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_BLANKCHECK_NOFB_WR_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_NOFB_MARKER_E;
        }
#endif //(FEE_NO_FALLBACK_ACTIVE != FALSE)

        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WRITEHEADER_WAIT_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFYHEADER_E;
        }

        /* Switch state machine of the function Fee_LLWriteBlock */
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_VERIFYHEADER_WAIT_E)
        {
            /* Fls_Compare was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITEDATA_SEC_A_E;
        }

        /* Switch the state machine of the function Fee_LLWriteBlock */
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WAIT_WRITEDATA_SEC_A_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFY_BLK_E;
        }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Switch the state machine of the function Fee_LLWriteBlock */
        if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WAIT_WRITEHDRPG2_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFY_BLK_E;
        }
#endif

#if(FEE_RB_MAINTAIN != FALSE)
        /* Switch the state machine of the function Fee_HlMaintainBlock */
        if(Fee_RdWrOrder_st.Fee_HLMtBlock_en == FEE_HL_READ_BLK_HDR_WAIT_E)
        {
            /* Fls_Read was finished with success, check the read block header */
            Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_CHECK_BLK_HDR_E;
        }
#endif

        /* Switch the state machine of the function Fee_LLCompBlkInFlash */
        if(Fee_RdWrOrder_st.Fee_LLCompBlk == FEE_LL_CMP_WAIT_HEADER_E)
        {
            /* Fls_Compare was finished with success */
            /* Check if there was no call of the Fee_JobErrorNotification
             * function before (the compare state is still 0xFF) */
            if(Fee_GlobInfoWrBlock_st.CompareResult_u8 == 0xFF)
            {
                /* Reset the compare result */
                Fee_GlobInfoWrBlock_st.CompareResult_u8 = 0;
            }

            /* Set next state */
            Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_CHECK_OVERLAP_E;
        }

        if(Fee_RdWrOrder_st.Fee_LLCompBlk == FEE_LL_CMP_WAIT_DATA_SEC_A_E)
        {
            /* Fls_Compare was finished with success */
            /* Check if there was no call of the Fee_JobErrorNotification
             * function before (the compare state is still 0xFF) */
            if(Fee_GlobInfoWrBlock_st.CompareResult_u8 == 0xFF)
            {
                /* Reset the compare result */
                Fee_GlobInfoWrBlock_st.CompareResult_u8 = 0;
            }

            /* Set next state */
            Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_FINISHED_E;
        }

        /* Switch state machine of the function Fee_LLCalcBlkCrcInFlash */
        if(Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en == FEE_LL_CRC_RD_PAGE_WAIT_E)
        {
            /* Fls_Read was finished with success */
            Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_CHECK_OVERLAP_E;
        }

        #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
        /* Switch state machine of the function Fee_LLCalcBlkCrcInFlash */
        if(Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en == FEE_LL_CRC_RD_ROB_PAGE_WAIT_E)
        {
            /* Fls_Read was finished with success */
            Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_CHECK_OVERLAP_ROB_E;
        }
        #endif

        /* Switch state machine of the function Fee_LLEraseSector */
        if(Fee_LLEraseOrder_st.EraseState_en == FEE_ERASESEC_DO_E)
        {
            /* In case of suspend it might be necessary to switch a read or write
             * state machine instead of switching the erase state machine */

            /* Hint: an erase during a write or reorg is not regarded because
             *       this case is not common at all. It will be changed by
             *       moving the internal erase sequences to the very
             *       upper level (main function). */
            #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
            if(Fee_Prv_stSuspendActiv_b == FALSE)
            #endif
            {
                /* Fls_Erase was finished with success */
                Fee_LLEraseOrder_st.EraseState_en = FEE_ERASESEC_WRITE_MARKER_E;
            }
        }

        /* Switch state machine of the function Fee_LLCopyData2Buffer */
        if(Fee_RdWrOrder_st.Fee_LLCopyBlk_en == FEE_LL_CPY_BLOCK_WAIT_E)
        {
            /* Fls_Read was finished with success */
            Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLOCK_FINISHED_E;
        }

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_READ_E)
        {
            /* Fls_Read was finished with success */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            /* Check if header page or data needs to be programmed. */
            if(Fee_RdWrOrder_st.xHdPg2Address == FEE_NULL)
            {
                /* Program the header page 1. */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_E;
            }
            else
#endif
            {
                /* Program the data pages. */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_E;
            }
        }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_WRITE_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_E;
        }
#endif

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_WRITE_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_VERIFY_E;
        }


#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_WRITE_E)
        {
            /* Fls_Write was finished with success */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_E;
        }

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_VERIFY_E)
        {
            /* Fls_Compare was finished with success */
            /* Set to next state to program data if there is some more data bytes that can be programmed, else read the data first. */
            if (Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 != 0)
            {
                /* There is some more data that was read and can be transfered, go directly to state FEE_LL_CPY_FLS2FLS_WRITE_E to transfer this data. */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_E;
            }
            else
            {
                /* There is no data read out, read the data first. */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_CHECK_ADR_OVERFLOW_E;

                Fee_LLSecReorgStruct_st.xFirstDataPgPgm_u8 = FEE_FIRSTDATAPAGE_PROGRAMMED;
            }
        }
#endif

        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_VERIFY_E)
        {
            /* Fls_Compare was finished with success */
            /* Set next state */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_CHECK_ADR_OVERFLOW_E;
        }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
        if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_VERIFY_E)
        {
            /* Fls_Compare was finished with success */
            /* Set next state to exit the function (or to start programming of second copy) */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_READ_E;
        }
#endif

#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
    #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) ) /* For Renesas controllers */
        /* Switch state machine of the function Fee_LlRobustSectorOverflow */
        if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_WAIT_E)
        {
            /* Page is blank, skip transfer of this page and go back to read next page.  */
            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_SUCCESS_E;
        }
    #endif

        /* Switch state machine of the function Fee_LlRobustSectorOverflow */
        if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_WAIT_E)
        {
            /* Page was read successfully, program this to new sector.  */
            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_E;
        }

        /* Switch state machine of the function Fee_LlRobustSectorOverflow */
        if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_WAIT_E)
        {
            /* Page was programmed successfully, verify the same.  */
            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_E;
        }

        /* Switch state machine of the function Fee_LlRobustSectorOverflow */
        if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_WAIT_E)
        {
            /* Verification was successfull, check if there is more bytes left to transfer.  */
            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_SUCCESS_E;
        }
#endif /*#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)*/

        #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
        /* robust Ifx Handling */
        if (Fee_RobIfxHdl == FEE_ROB_IFX_STORE_BUFFER_WAIT)
        {
            Fee_RobIfxHdl = FEE_ROB_IFX_COPY_DATA;
        }

        if (Fee_RobIfxHdl == FEE_ROB_IFX_STORE_COPY_WAIT)
        {
            Fee_RobIfxHdl = FEE_ROB_IFX_WRITE_USED_MARK_SECTOR;
        }
        #endif

        #if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0))
        /* Unknown block sector reorganisation with cache:
		 * Reading of header page of unknown block during sector change to extract the lenght and status flag. */
        if (Fee_RdWrOrder_st.Fee_LLSecReorg_en == FEE_LL_REORG_SEARCH_UNK_HDRBLK_WAIT_E)
        {
            Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_FINISHED_E;
        }
        #endif
    }
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/**
 *********************************************************************
 * Fee_JobEndNotification(): Service for reporting an unsuccessful end
 *                           of an asynchronous operation.
 *
 * This function reports an unsuccessful end of an asynchronous
 * operation (FEE096). The function call has to be configured in the
 * Fls module in order to be called automatically whenever an
 * asynchronous operation was finished. Alternatively the
 * Fls_GetJobResult() functionality can be used depending on
 * "FEE_POLLING_MODE".
 *
 * Hint:
 * Deviation from the AR SWS:
 * - Whether a read or write operation is finished cannot be detected
 *   within this function (function call can be interrupt level).
 *   A finished block will be detected in the Fee_MainFunction.
 *   --> FEE054 and FEE143 is realized there
 * - FEE054: The function Fee_JobErrorNotification shall perform any
 *   necessary block management operations and subsequently call
 *   the job end notification routine of the upper layer module if
 *   configured.
 * - FEE143: If the job result is currently MEMIF_JOB_PENDING, the
 *   function Fee_JobErrorNotification shall set the job result to
 *   MEMIF_JOB_OK, else it shall leave the job result untouched.
 *
 * Note:
 * The function Fee_JobErrorNotification shall be callable on
 * interrupt level.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#if (STD_OFF == FEE_POLLING_MODE)
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_JobErrorNotification(void)
#else
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_SwitchJobErrorNotification(void)
#endif
{
    /* Switch the read state machine */
    if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_WAIT_READ_PAGE_E)
    {
        /* Fls_Read was finished without success */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_ERROR_E;
    }

    /* Switch the read state machine */
    if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_BLANK_CHECK_WAIT_E)
    {
        /* Fls_Rb_BlankCheck was finished without success */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_READ_PAGE_E;
    }

    /* Switch the sector detection state machine */
#if (defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH))
    if(Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en == FEE_LL_FINDEMPTYPGE_WAIT_E)
    {
        /* Chunk is not blank */
        Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_RESULT_NOT_BLANK_E;
    }
#endif

    /* Switch the blank check state machine */
    if(Fee_RdWrOrder_st.Fee_LLBlankCheckState_en == FEE_LL_WAIT_PERFORM_BLANK_CHECK_E)
    {
        /* Blank check detected differences */
        Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_BLANK_CHECK_ERROR_E;
    }

    /* Switch the state machine of the function Fee_LLWriteMarker */
    if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_BLK_CHK_WAIT_E)
    {
        /* Fls_BlankCheck was finished without success */
        Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_ERROR_E;
    }

    /* Switch the state machine of the function Fee_LLWriteMarker */
    if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_WRITE_WAIT_E)
    {
        /* Fls_Write was finished without success */
        Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_WRITE_ERROR_E;
    }

    /* Switch the state machine of the function Fee_LLWriteMarker */
    if(Fee_RdWrOrder_st.Fee_LLWrMarker_en == FEE_LL_MARKER_VERIFY_WAIT_E)
    {
        /* Fls_Write was finished without success */
        Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_WRITE_ERROR_E;
    }

#if (FEE_HEADER_RECHECK_ACTIVE != FALSE)
    /* Switch state machine of the function Fee_LLSearchNextBlkHeader */
    if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_RECHECK_HEADER_WAIT_E)
    {
        /* Fls_Rb_BlankCheck was finished with success */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_RECHECK_HEADER_FINISHED_E;
    }

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    /* Switch the read state machine */
    if(Fee_RdWrOrder_st.Fee_LLRdState_en == FEE_LL_NOFALLBACK_MARKER_CHECK_WAIT_E)
    {
        /* Fls_Rb_BlankCheck was not finished with success */
        Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_NOFALLBACK_MARKER_CHECK_FAILED_E;
    }

    /* Switch state machine of the function Fee_LLWriteBlock */
    if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WRITE_NOFB_MARKER_WAIT_E)
    {
        /* Fls_Write was not finished with success */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_NOFB_MARKER_ERROR_E;
    }

    /* Switch state machine of the function Fee_LLWriteBlock */
    if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_FILL_SECTOR_END_WAIT_E)
    {
        /* Fls_Write was finished with success */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_ERROR_E;
    }

    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_FILL_SECTOR_END_E)
    {
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_FILL_SECTOR_END_ERROR_E;
    }

    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_WRITE_NOFB_MARKER_E)
    {
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_ERROR_E;
    }
/* FEE_NO_FALLBACK_ACTIVE != FALSE */
#endif
/* FEE_HEADER_RECHECK_ACTIVE != FALSE */
#endif

    /* Switch state machine of the function Fee_LLWriteBlock */
    if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_VERIFYHEADER_WAIT_E)
    {
        /* Fls_Compare was finished without success */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_VERIFYHEADER_ERROR_E;
    }

#if(FEE_RB_MAINTAIN != FALSE)
    /* Switch the state machine of the function Fee_HlMaintainBlock */
    if(Fee_RdWrOrder_st.Fee_HLMtBlock_en == FEE_HL_READ_BLK_HDR_WAIT_E)
    {
        /* Fls_Read was finished without success, repair this block directly */
        Fee_RdWrOrder_st.Fee_HLMtBlock_en = FEE_HL_WR_BLK_E;
    }
#endif

    /* Switch state machine of the function Fee_LLCompBlkInFlash */
    if (Fee_RdWrOrder_st.Fee_LLCompBlk == FEE_LL_CMP_WAIT_HEADER_E)
    {
        /* Fls_Compare was finished without success */
        Fee_GlobInfoWrBlock_st.CompareResult_u8 = 1;

        /* Error behaviour is done after checking the compare result */
        Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_CHECK_OVERLAP_E;
    }

    /* Switch state machine of the function Fee_LLCompBlkInFlash */
    if (Fee_RdWrOrder_st.Fee_LLCompBlk == FEE_LL_CMP_WAIT_DATA_SEC_A_E)
    {
        /* Fls_Compare was finished without success */
        Fee_GlobInfoWrBlock_st.CompareResult_u8 = 1;

        /* Error behaviour is done after checking the compare result */
        Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_FINISHED_E;
    }

    /* Switch state machine of the function Fee_LLCalcBlkCrcInFlash */
    if(Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en == FEE_LL_CRC_RD_PAGE_WAIT_E)
    {
        /* Fls_Read was finished without success */
        Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_ERROR_E;
    }

    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    /* Switch state machine of the function Fee_LLCalcBlkCrcInFlash */
    if(Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en == FEE_LL_CRC_RD_ROB_PAGE_WAIT_E)
    {
        /* Fls_Read was finished without success */
        Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_ERROR_E;
    }
    #endif

    /* Switch state machine of function the Fee_LLEraseSector */
    if (Fee_LLEraseOrder_st.EraseState_en == FEE_ERASESEC_DO_E)
    {
        /* In case of suspend it might be necessary to switch a read or write
         * state machine instead of switching the erase state machine */

        /* Hint: an erase during a write or reorg is not regarded because
         *       this case is not common at all. It will be changed by
         *       moving the internal erase sequences to the very
         *       upper level (main function). */
        #if (FEE_RB_ACT_ERASE_SUSPENSION != FALSE)
        if(Fee_Prv_stSuspendActiv_b == FALSE)
        #endif
        {
            /* Fls_Erase was finished without success */
            Fee_LLEraseOrder_st.EraseState_en = FEE_ERASESEC_ERROR_E;
        }
    }

    /* Switch state machine of the function Fee_LLCopyData2Buffer */
    if(Fee_RdWrOrder_st.Fee_LLCopyBlk_en == FEE_LL_CPY_BLOCK_WAIT_E)
    {
        /* Fls_Read was finished without success */
        Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLOCK_ERROR_E;
    }

    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_READ_E)
    {
        /* Fls_Read was finished without success */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_READ_ERROR_E;
    }


    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_WRITE_E)
    {
        /* Fls_Write was finished without success */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_ERROR_E;
    }
#endif


    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_WRITE_E)
    {
        /* Fls_Write was finished without success */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_ERROR_E;
    }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_WRITE_E)
    {
        /* Fls_Write was finished without success */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_ERROR_E;
    }

    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_VERIFY_E)
    {
        /* Fls_Compare was finished without success */
        /* Set error case */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_ERROR_E;
    }
#endif

    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_VERIFY_E)
    {
        /* Fls_Compare was finished without success */
        /* Set error case */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_VERIFY_ERROR_E;
    }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    /* Switch state machine of the function Fee_LLCpyBlkFromFls2Fls */
    if(Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en == FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_VERIFY_E)
    {
        /* Fls_Compare was finished without success */
        /* Set error case */
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_ERROR_E;
    }
#endif

#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
#if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) ) /* For Renesas controllers */
    /* Switch state machine of the function Fee_LlRobustSectorOverflow */
    if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_WAIT_E)
    {
        /* Page is not blank, the page must be transfered to new sector, first read the page into internal buffer.  */
        Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_E;
    }
#endif

    /* Switch state machine of the function Fee_LlRobustSectorOverflow */
    if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_WAIT_E)
    {
        /* Page was read failed, retry with erase.  */
        Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E;
    }

    /* Switch state machine of the function Fee_LlRobustSectorOverflow */
    if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_WAIT_E)
    {
        /* Page programming failed, retry starting with erase.  */
        Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E;
    }

    /* Switch state machine of the function Fee_LlRobustSectorOverflow */
    if(Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en == FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_WAIT_E)
    {
        /* Verification failed, retry starting with erase. */
        Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E;
    }
#endif   /*#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)*/

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
    if (Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_BLANKCHECK_NOFB_WR_WAIT_E)
    {
        // If NoFB Address is not blank, overstep the writing of the marker
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_FILL_SECTOR_END_E;
    }
#endif //(FEE_NO_FALLBACK_ACTIVE != FALSE)

    /* Switch state machine of the function Fee_LLWriteBlock */

    if((Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WRITEHEADER_WAIT_E) || (Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WAIT_WRITEDATA_SEC_A_E))
    {
        /* Fls_Write failed, return error */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_ERROR_E;
    }

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)   /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
    if(Fee_RdWrOrder_st.Fee_LLWrBlock_en == FEE_LL_WR_WAIT_WRITEHDRPG2_E)
    {
        /* Fls_Write failed, return error */
        Fee_RdWrOrder_st.Fee_LLWrBlock_en = FEE_LL_WR_WRITE_ERROR_E;
    }
#endif

    #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
    if (Fee_RobIfxHdl == FEE_ROB_IFX_STORE_BUFFER_WAIT)
    {
        Fee_RobIfxHdl = FEE_ROB_IFX_COPY_DATA;
    }

    if (Fee_RobIfxHdl == FEE_ROB_IFX_STORE_COPY_WAIT)
    {
        Fee_RobIfxHdl = FEE_ROB_IFX_WRITE_USED_MARK_SECTOR;
    }
    #endif

    #if((FEE_RB_ACT_UNKNOWN_BLOCK_REORG != FALSE) && (FEE_RB_ACT_UNKNOWN_BLOCK_CACHE_SIZE != 0))
    /* Unknown block sector reorganisation with cache:
     * Reading of header page of unknown block during sector change to extract the lenght and status flag. */
    if (Fee_RdWrOrder_st.Fee_LLSecReorg_en == FEE_LL_REORG_SEARCH_UNK_HDRBLK_WAIT_E)
    {
        Fee_RdWrOrder_st.Fee_LLSecReorg_en = FEE_LL_REORG_SEARCH_UNK_HDRBLK_READ_ERROR_E;
    }
    #endif

    #if (STD_OFF == FEE_POLLING_MODE)
    /* Switch the read or write state machine (no special case within this function) */
    Fee_JobEndNotification();
    #else
    /* Switch the read or write state machine (no special cases within this function) */
    Fee_SwitchJobEndNotification();
    #endif
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
