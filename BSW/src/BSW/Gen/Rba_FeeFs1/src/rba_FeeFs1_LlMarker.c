


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
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
   // #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
    //#error "AUTOSAR minor version undefined or mismatched"
#endif

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
 * Fee_LLWriteMarker(): Write a marker in the sector marker section
 *
 * This function writes one of the sector markers in the respective
 * sector header section. The marker pattern, marker ID,
 * sector change counter (if necessary) and the marker checksum are
 * written.
 * If there is not enough space in the marker section and the USED
 * marker needs to be written, the calling function should erase
 * this sector. Otherwise data might get lost.
 * If the there is enough space and the marker cannot be written
 * due to any HW issue, the function will retry the write access
 * automatically for FEE_MAX_RD_WR_COMP_RETRIES times.
 *
 * \param    PhySectIdx_u8:         Index of the physical sector
 * \param    MarkerID_u8:           Marker ID to write
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Marker not writable/readable or
 *                                  marker section is full
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLWriteMarker(VAR(uint8, AUTOMATIC) PhySectIdx_u8,
                                                   VAR(uint8, AUTOMATIC) MarkerID_u8)
{
    VAR(Fee_MarkerProp_t, AUTOMATIC) xWrMarker_st;                      /* Marker structure */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;  /* Function return value */
    VAR(uint32, AUTOMATIC) xSecChngCntTmp_u32 = 0;                      /* Temporary sector change counter */
    VAR(uint8, AUTOMATIC) xLogSectIdx_u8 = 0;                           /* Logical sector index */
    static uint32 xRdWr_Address_u32 = FEE_MAXUINT32;                    /* Read address for the blank check */

    #if (FEE_PRV_DEBUG_MONITOR != FALSE)
    VAR(uint16, FEE_VAR)             xCacheIdx_u16;
    VAR(uint32, FEE_VAR)             stDBM_u32 = 0;
    #endif

	/* Get the logical sector index */
	xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[PhySectIdx_u8];


	/* Switch over function state machine */
	switch (Fee_RdWrOrder_st.Fee_LLWrMarker_en)
	{
		/* Init state */
		case FEE_LL_MARKER_INIT_E:
		{
            #if (FEE_PRV_DEBUG_MONITOR != FALSE)
		    /* For ERASE_REQUEST marker, check the cache if block is still in this sector */
			if (MarkerID_u8 == FEE_ERASE_REQUEST_ID_E)
			{
				/* Check if any cache entry points to the sector which should be erased */
				for (xCacheIdx_u16 = 0; xCacheIdx_u16 < FEE_NUM_BLOCKS; xCacheIdx_u16++)
				{
					if ((Fee_Cache_au32[xCacheIdx_u16] >= Fee_FlashProp_st[PhySectIdx_u8].Fee_PhysStartAddress_u32) &&
						 (Fee_Cache_au32[xCacheIdx_u16] <= Fee_FlashProp_st[PhySectIdx_u8].Fee_PhysEndAddress_u32))
					{
						/* Set status for debug monitor */
						stDBM_u32 = 0x1;
						xRetVal_en = FEE_ERROR_E;
					}
				}
			}
            #endif

			/* Set next state */
			Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_E;

			/* Reset buffer */
			Fee_SrvMemSet8((uint8*)&Fee_MarkerBufBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_SEC_HEADER_SIZE);

			/* Set the start read address */
			xRdWr_Address_u32 = Fee_FlashProp_st[PhySectIdx_u8].Fee_PhysStartAddress_u32;
		}
		/* No break to save time */

		/* Perform a blank check over one page */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_MARKER_BLK_CHK_E:
		{
			/* Perform a blank check over the respective marker */
			if(Fls_Rb_BlankCheck(xRdWr_Address_u32, NULL_PTR, FEE_MARKER_SIZE) != E_NOT_OK)
			{
				/* Set the next state for finishing the blank check */
				Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_WAIT_E;
			}
			else
			{
				/* Return an error due to invalid parameters or a busy / not intialized Fls */
				xRetVal_en = FEE_ABORTED_E;
			}
		}
		break;

		/* Wait for the blank check order to be finished */
		case FEE_LL_MARKER_BLK_CHK_WAIT_E:
		{
			/* The next state (FEE_LL_MARKER_BLK_CHK_FINISHED_E or FEE_LL_MARKER_BLK_CHK_ERROR_E)
			 * will be set by the Fee_JobEndNotification() or Fee_JobErrorNotification() function
			 * automatically */

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

		/* Differences detected */
		case FEE_LL_MARKER_BLK_CHK_ERROR_E:
		{
			/* Check the next page / marker, increment the write address for the blank check */
			xRdWr_Address_u32 += FEE_PAGE_LEN;

			/* Ensure page alignment for blank check and write operation (following) */
			while((xRdWr_Address_u32 % FEE_PAGE_LEN) != 0u)
			{
				/* Increment address */
				xRdWr_Address_u32++;
			}

			/* Check for an overflow (at least enough space for one more marker must be available) */
			if(xRdWr_Address_u32 >
			  ((Fee_FlashProp_st[PhySectIdx_u8].Fee_PhysStartAddress_u32 + FEE_SEC_HEADER_SIZE) - FEE_MARKER_SIZE))
			{
				/* Return with an error */
				xRetVal_en = FEE_ERROR_E;
			}
			else
			{
				/* Reset buffer */
				Fee_SrvMemSet8((uint8*)&Fee_MarkerBufBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_SEC_HEADER_SIZE);

				/* Restart the state machine starting with a blank check */
				Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_E;
			}
		}
		break;

		/* Start write order of the marker */
		case FEE_LL_MARKER_BLK_CHK_FINISHED_E:
		{
			/* Prepare the marker to be written */
			xWrMarker_st.xPattern = FEE_MARKER_PATTERN;
			xWrMarker_st.xIdent   = MarkerID_u8;

			/* Verify whether enough space for another marker is left or not.
			 * Hint: Header section size is generated depending on the page length
			 *       and the marker size: FEE_NUM_MARKER_IN_HEADER * FEE_PAGE_LEN */
			if(xRdWr_Address_u32 >
			  ((Fee_FlashProp_st[PhySectIdx_u8].Fee_PhysStartAddress_u32 + FEE_SEC_HEADER_SIZE) - FEE_PAGE_LEN))
			{
				/* Return with an error */
				xRetVal_en = FEE_ERROR_E;
			}

			/* Check if the sector which will be used to store the marker has a valid
			 * sector change counter. If not, the highest available counter has to be
			 * searched and incremented within the other sectors.
			 *
			 * If the ERASED marker needs to be written, this search is also necessary,
			 * because this is the first marker to be written inside this sectors
			 * --> no other sector change counter is available inside this sector yet
			 */

			/* Check for an available sector change counter inside the requested sector */
			if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecChngCnt_u32 != FEE_SEC_CHANGE_CNT_UNDEF) &&
			   (MarkerID_u8 != FEE_ERASED_MARKER_ID_E) )
			{
				/* Save the available counter value */
				xSecChngCntTmp_u32 = Fee_LLSectorOrder_st[xLogSectIdx_u8].SecChngCnt_u32;
			}
			else
			{
				/* Increment the counter because every sector has to use different sector
				 * change counter values */
				if (Fee_RdWrRetries_u8 == FEE_MAX_RD_WR_COMP_RETRIES)
				{
					/* Increment sector change counter (highest one is detected during the sector detection) */
					Fee_SecChngCnt_u32++;
				}
                xSecChngCntTmp_u32 = Fee_SecChngCnt_u32;
				/* Save the new sector change counter value */
				Fee_LLSectorOrder_st[xLogSectIdx_u8].SecChngCnt_u32 = xSecChngCntTmp_u32;
			}

            if (MarkerID_u8 == FEE_START_MARKER_ID_E)
            {
                xSecChngCntTmp_u32 = Fee_RdWrOrder_st.xStartAddrNextSector_u32;
            }

            #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
            if (MarkerID_u8 == FEE_CLONE_START_MARKER_ID_E)
            {
                xSecChngCntTmp_u32 = Fee_IfxRobustProgramming_s.xStartAddress;
            }
            #endif

			/* Save the counter value to the content structure of the marker content. For the
			 * USED, FULL and ERASED marker it contains the sector change counter. The ERASE
			 * marker content is not used and will therefore be zero.
			 * Result of the shift operation: [2]CC, [1]BB, [0]AA: 0xAABBCC*/
			xWrMarker_st.xContent[0] = (uint8)(xSecChngCntTmp_u32 >> 16u);
			xWrMarker_st.xContent[1] = (uint8)(xSecChngCntTmp_u32 >> 8u);
			xWrMarker_st.xContent[2] = (uint8)(xSecChngCntTmp_u32);

			/* Calculate the new marker CRC and save it to the marker structure */
			/* MR12 RULE 11.3 VIOLATION: Variable must be changeable */
			xWrMarker_st.xChecksum  = Crc_CalculateCRC16((const uint8*)&xWrMarker_st,
														 (uint32)(FEE_MARKER_SIZE-FEE_MARKER_CS_SIZE),
														 (uint16)FEE_MARKER_PATTERN,
														  FALSE);

			/* Prepare marker buffer */
			Fee_LLPrepMarkerBufWithMarkerData(&xWrMarker_st, &Fee_MarkerBufBytePtr_cpu8[0]);

			/* Write the new marker into the flash */
			if(Fls_Write(xRdWr_Address_u32, (uint8*)&Fee_MarkerBufBytePtr_cpu8[0], FEE_MARKER_SIZE) != E_NOT_OK)
			{
				/* Set the next state to wait for the write order to be finished */
				Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_WRITE_WAIT_E;
			}
			else
			{
				/* Abort due to wrong parameters or the Fls being busy / not initialized */
				xRetVal_en = FEE_ABORTED_E;
			}
		}
		break;

		/* Wait for the write order to be finished */
		case FEE_LL_MARKER_WRITE_WAIT_E:
		{
			/* The next state (FEE_LL_MARKER_WRITE_FINISHED_E) will be set by the Fee_JobEndNotification() or
			 * Fee_JobErrorNotification() function automatically (the verification of the data will be done
			 * in one step after the data was written) */

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

		/* Read or write error */
		case FEE_LL_MARKER_WRITE_ERROR_E:
		{
			/* Verify retry possibility */
			if(Fee_RdWrRetries_u8 > 0)
			{
				/* Decrement retry possibilities */
				Fee_RdWrRetries_u8--;

				/* Increment the write address */
				xRdWr_Address_u32 += FEE_PAGE_LEN;

				/* Ensure page alignment */
				while((xRdWr_Address_u32 % FEE_PAGE_LEN) != 0u)
				{
					/* Increment address */
					xRdWr_Address_u32++;
				}

				/* Reset buffer */
				Fee_SrvMemSet8((uint8*)&Fee_MarkerBufBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, FEE_SEC_HEADER_SIZE);

				/* Restart the state machine starting with a blank check */
				Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_BLK_CHK_E;
			}
			else
			{
				/* Return error, because maximum amount of retries is reached */
				xRetVal_en = FEE_ERROR_E;
			}
		}
		break;

		/* Verify the written marker  */
		case FEE_LL_MARKER_VERIFY_E:
		{
			if(Fls_Compare(xRdWr_Address_u32, (uint8*)&Fee_MarkerBufBytePtr_cpu8[0], FEE_MARKER_SIZE) != E_NOT_OK)
			{
				/* Set the next state to wait for the write order to be finished */
				Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_VERIFY_WAIT_E;
			}
			else
			{
				/* Abort due to wrong parameters or the Fls being busy / not initialized */
				xRetVal_en = FEE_ABORTED_E;
			}
		}
		break;

		/* Verify the written marker  */
		case FEE_LL_MARKER_VERIFY_WAIT_E:
		{
			/* The next state (FEE_LL_MARKER_WRITE_FINISHED_E) will be set by the Fee_JobEndNotification() or
			 * Fee_JobErrorNotification() function automatically (the verification of the data will be done
			 * in one step after the data was written) */

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

		/* Marker was written with success */
		case FEE_LL_MARKER_VERIFY_FINISHED_E:
		{
			/* Return with success */
			xRetVal_en = FEE_ORDER_FINISHED_E;
		}
		break;

		/* Default state */
		default:
		{
			/* Return aborted */
			xRetVal_en = FEE_ABORTED_E;
		}
		break;
	}


    /* Verify a necessary reset of the state machine */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        #if (FEE_PRV_DEBUG_MONITOR != FALSE)
        /* Report Debug monitor */
        if (stDBM_u32 > 0)
        {
            Fee_DBM_RepError(PhySectIdx_u8, FEE_DBM_ERROR_LLMARKER_FCT_E, stDBM_u32);
            stDBM_u32 = 0;
        }
        #endif

		/* Update the new sector state (if necessary the sector change counter has been updated already before) */
		if ((MarkerID_u8 != FEE_START_MARKER_ID_E) && (MarkerID_u8 != FEE_CLONE_START_MARKER_ID_E))
		{
			/* if a START-Marker was written, the sector is still in the STATE USED. It is not allowed to write the
			 * START-Marker-ID on the sector state, because the sector didn't get a new STATE by writing START-Marker */
		    /* MR12 RULE 10.5 VIOLATION: Sector states are defined as enum for modular design and easy to read. */
		    Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en = (Fee_SectorState_ten)MarkerID_u8;
		}
		else
		{
			/* Start- and Clonse-Marker is nearly the same as the USED-Marker */
		    Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en = FEE_SECTOR_USED_E;
		}

        /* Init state machine */
        Fee_RdWrOrder_st.Fee_LLWrMarker_en = FEE_LL_MARKER_INIT_E;

        /* Retries for write */
        Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

        /* Reset start address for the blank check */
        xRdWr_Address_u32 = FEE_MAXUINT32;
    }

    return (xRetVal_en);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
