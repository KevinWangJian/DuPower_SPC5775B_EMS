


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
   // #error "AUTOSAR minor version undefined or mismatched"
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
#define FEE_START_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"
static uint16 Fee_LastErasedMarker_u16[FEE_NUM_FLASH_BANKS_AVAILABLE];
#define FEE_STOP_SEC_VAR_CLEARED_16
#include "Fee_MemMap.h"

/**
 *********************************************************************
 * Fee_LLDetectActiveSector(): Detect the active sector
 *
 * This function is used to detect the currently active sector.
 * If more than 2 sectors are available, the function is responsible
 * for putting the blocks in a logical order with the eldest data
 * sector at position zero.
 *
 * \param    none
 * \return   Physical index of the active sector
 * \retval   0...254    Physical sector index
 * \retval   255        No sector found
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(uint8, FEE_CODE) Fee_LLDetectActiveSector(void)
{
    /* MR12 RULE 8.5 VIOLATION: This is no function declaration but a variable only with an external linkage*/
    VAR(Fee_stSecDet_tst, AUTOMATIC) Fee_stSecDet_st[FEE_NUM_FLASH_BANKS_AVAILABLE];
    VAR(Fee_LLSectorOrder_tst, AUTOMATIC) TmpSectorOrder_st[FEE_NUM_FLASH_BANKS_AVAILABLE];
    VAR(uint8, AUTOMATIC)  xCurrSect_u8 = 0;        /* Sector loop counter */
    VAR(uint8, AUTOMATIC)  xCntFlashBank_u8 = 0;    /* Loop counter */
    VAR(uint8, AUTOMATIC)  cnt_u8 = 0;              /* Inner loop counter */
    VAR(uint32, AUTOMATIC) SectCntMin_u32 = 0;      /* Lowest sector change counter */
    VAR(uint8,  AUTOMATIC) xActiveSec_u8 = FEE_NO_SEC_IDX_FOUND;  /* Function return */
    VAR(uint8,  AUTOMATIC) xPhySecIdx_u8;  			/* Physical sector index */
    VAR(uint8,  AUTOMATIC) xLogSecIdx_u8;			/* Logical sector index */
    VAR(uint8, AUTOMATIC)  xRepeatSortLoop_u8;

    /* Collect all sector header information */
    Fee_LLSearchSectors(&Fee_stSecDet_st[0]);

    /* Sectors should be handled in the following order
     *
     *   +-----------------+             #   old data
     *   | full, SCcnt=X   |             #
     *   | full, SCcnt=X+1 |             #
     *   | full, SCcnt=X+2 |           #####
     *   +-----------------+            ###
     *   | used, SCcnt=X+3 |             #   new data
     *   +-----------------+
     *   | erased          |                 erased sector, ready to be used
     *   +-----------------+
     *
     *   +-----------------+             Sector has no marker and is in an undefined state. Before using this sector it
     *   | undefined       |             has to be erased.
     *   +-----------------+
     *
     *   -> Result of Step 2
     */

    /* STEP1: Save the sector states prioritized to the temp structure */
    /* *************************************************************** */
    /* Loop over all configured sectors and search for the available markers */
    for(xCurrSect_u8=0; xCurrSect_u8<FEE_NUM_FLASH_BANKS; xCurrSect_u8++)
    {
        TmpSectorOrder_st[xCurrSect_u8].SecChngCnt_u32 = Fee_stSecDet_st[xCurrSect_u8].SecChngCnt_u32;
        TmpSectorOrder_st[xCurrSect_u8].xPhySecIdx_u8  = xCurrSect_u8;

        /* Check for an erase request first */
        if(Fee_stSecDet_st[xCurrSect_u8].ctEraseReq_u8 > 0)
        {
            /* Sector is requested to be erased */
            TmpSectorOrder_st[xCurrSect_u8].SecState_en    = FEE_SECTOR_REQUEST2ERASE_E;
            TmpSectorOrder_st[xCurrSect_u8].SecChngCnt_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
        }
        else
        {
            /* Check for a full marker */
            if(Fee_stSecDet_st[xCurrSect_u8].ctFullMarker_u8 > 0)
            {
                /* The currently evaluated sector is full */
                TmpSectorOrder_st[xCurrSect_u8].SecState_en = FEE_SECTOR_FULL_E;
            }
            else
            {
                /* Check for a used marker */
                if(Fee_stSecDet_st[xCurrSect_u8].ctUsedMarker_u8 > 0)
                {
                    /* The currently evaluated sector is used */
                    TmpSectorOrder_st[xCurrSect_u8].SecState_en = FEE_SECTOR_USED_E;
                }
                else
                {
                    /* Check for an erased marker */
                    if (Fee_stSecDet_st[xCurrSect_u8].ctErasedMarker_u8 > 0)
                    {
                        /* if only a CLONE Marker without USED or START marker is present in the sector header, a cloning
                         * procedure was interrupted. In this case it could be possible that the new, or the old sector
                         * is the besster choice. Decision was that we will erase the clone sector again.
                         */
                        if (Fee_stSecDet_st[xCurrSect_u8].ctCloneMarker_u8 > 0){
                            /* The currently evaluated sector is still in an erased state */
                            TmpSectorOrder_st[xCurrSect_u8].SecState_en    = FEE_SECTOR_STATE_UNDEF_E;
                            TmpSectorOrder_st[xCurrSect_u8].SecChngCnt_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
                        }else{
                            /* The currently evaluated sector is still in an erased state */
                            TmpSectorOrder_st[xCurrSect_u8].SecState_en = FEE_SECTOR_ERASED_E;
                        }
                    }
                    else
                    {
                        /* The currently evaluated sector is in an undefined state */
                        TmpSectorOrder_st[xCurrSect_u8].SecState_en    = FEE_SECTOR_STATE_UNDEF_E;
                        TmpSectorOrder_st[xCurrSect_u8].SecChngCnt_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
                    }
                }
            }
        }
    }

    /* STEP2: Sort all sectors using the sector change counter as the criteria for
     *        the topicality and save it to the global structure */
    /* ********************************************************* */

    /* Set start value (min) */
    SectCntMin_u32 = FEE_SEC_CHANGE_CNT_UNDEF;

    /* Loop over all configured flash banks */
    for(xCntFlashBank_u8=0; xCntFlashBank_u8<FEE_NUM_FLASH_BANKS; xCntFlashBank_u8++)
    {
        /* Reset sector change counter */
        Fee_LLSectorOrder_st[xCntFlashBank_u8].SecChngCnt_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
		xCurrSect_u8 = 0xFF;
        /* Inner loop over all configured flash banks */
        for(cnt_u8=0; cnt_u8<FEE_NUM_FLASH_BANKS; cnt_u8++)
        {
            /* Search for the highest sector change counter within the sector headers */
            /* MR12 RULE 9.1 VIOLATION: Array is filled in the previous loop */
            if((SectCntMin_u32 >= TmpSectorOrder_st[cnt_u8].SecChngCnt_u32) &&
               (TmpSectorOrder_st[cnt_u8].SecState_en != FEE_SECTOR_CONSIDERED_E) &&
			   (TmpSectorOrder_st[cnt_u8].SecChngCnt_u32 != FEE_SEC_CHANGE_CNT_UNDEF))
            {
                /* Save the sector index with the lowest sector change counter */
                SectCntMin_u32 = TmpSectorOrder_st[cnt_u8].SecChngCnt_u32;
                xCurrSect_u8 = cnt_u8;
            }
        }
		if (xCurrSect_u8 == 0xFF){
			/* no block found till now --> loop not necessary */
			for(cnt_u8=0; cnt_u8<FEE_NUM_FLASH_BANKS; cnt_u8++)
			{
				/* Search for ERASED or UNDEF sectors and put them to behind all other sectors */
				if((SectCntMin_u32 == FEE_SEC_CHANGE_CNT_UNDEF) &&
				   (TmpSectorOrder_st[cnt_u8].SecState_en != FEE_SECTOR_CONSIDERED_E))
				{
					/* Save the sector index with the lowest sector change counter */
					xCurrSect_u8 = cnt_u8;
					break;
				}
			}
		}
        /* Copy the header data of the sector with the smallest sector change counter value which was not considered yet */
        Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8   = TmpSectorOrder_st[xCurrSect_u8].xPhySecIdx_u8;
        Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en     = TmpSectorOrder_st[xCurrSect_u8].SecState_en;
        Fee_LLSectorOrder_st[xCntFlashBank_u8].SecChngCnt_u32  = TmpSectorOrder_st[xCurrSect_u8].SecChngCnt_u32;

        /* Get sector change counter */
        if ((Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en != FEE_SECTOR_STATE_UNDEF_E) &&
            (Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en != FEE_SECTOR_REQUEST2ERASE_E))
        {
            /* Save sector change counter for currently active sector */
            Fee_SecChngCnt_u32 = Fee_LLSectorOrder_st[xCntFlashBank_u8].SecChngCnt_u32;
        }

        /* Save index of the current sector to the array Ram table in order to allow fast access to the
         * sector property configuration table in the flash. */
        Fee_idxLLSectorOrder_au8[Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8] = xCntFlashBank_u8;

        /* Mark this sector as already considered and reset the minimum sector change counter for the next loop run */
        TmpSectorOrder_st[xCurrSect_u8].SecState_en = FEE_SECTOR_CONSIDERED_E;
        SectCntMin_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
    }
    /* Workaround or robustness for the Kammerer/Daimler problem in the CB. If there is data programmed in a sector, but there is no USED
     * marker in the sector header, data was overprogrammed by the FEE. For this case it is not critical to mark the ERASED sector as USED.
     * To be consistent in RAM and FLASH, the marker will be written directly into the DFLASH. */
    for(xCntFlashBank_u8=1; xCntFlashBank_u8<FEE_NUM_FLASH_BANKS; xCntFlashBank_u8++)
    {
        xPhySecIdx_u8 = Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8;
        if ((Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_ERASED_E) &&
            (Fee_LLSectorOrder_st[xCntFlashBank_u8-1].SecState_en == FEE_SECTOR_FULL_E))
        {
			while(Fee_LLWriteMarker(xPhySecIdx_u8, FEE_USED_MARKER_ID_E) == FEE_ORDER_PENDING_E){
			    Fls_MainFunction();
			}
        }
	}
    /* STEP3:   Check all ERASED sectors, if they are empty.
                if one erased sector found which has still some data on it -->
                keep this sector as used sector */
    /* **************************************************************************************** */
    Fee_CheckErasedSectorEmpty();

    /* STEP4: Detect the most current sector index and save it to the return value */
    /* *************************************************************************** */
    /* Get the index */
    xActiveSec_u8 = Fee_GetMostCurrentSectorIdx();

    /* update start-address of first blockheader in USED sector. This address will only be used in function Fee_LLFindEmptyPage to find
     * first page which is not programmed. */
    Fee_RdWrOrder_st.xStartAddrNextSector_u32 = Fee_stSecDet_st[xActiveSec_u8].xStartAddr_u32;

    /* STEP5: Check if there are UNDEFINED / ERASED / REQ2ERASED sectors in between USED or FULL sectors */
    /* ************************************************************************************************* */
    /* Loop over all configured flash banks */
	do
	{
		xRepeatSortLoop_u8 = 0;
		for(xCntFlashBank_u8=1; xCntFlashBank_u8<FEE_NUM_FLASH_BANKS; xCntFlashBank_u8++)
		{
			/* Check the consistency of the sector states */
			if(((Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_USED_E) ||
				(Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_FULL_E)) &&
				(Fee_LLSectorOrder_st[xCntFlashBank_u8-1].SecState_en != FEE_SECTOR_USED_E) &&
				(Fee_LLSectorOrder_st[xCntFlashBank_u8-1].SecState_en != FEE_SECTOR_FULL_E))
			{
				/* Save the physical sector index temporarily */
				xPhySecIdx_u8 = Fee_LLSectorOrder_st[xCntFlashBank_u8-1].xPhySecIdx_u8;

				xLogSecIdx_u8=xCntFlashBank_u8;
				do
				{
					/* Reorganize the sector order */
					Fee_LLSectorOrder_st[xLogSecIdx_u8-1] = Fee_LLSectorOrder_st[xLogSecIdx_u8];

					/* Reorganize the array Ram table */
					Fee_idxLLSectorOrder_au8[Fee_LLSectorOrder_st[xLogSecIdx_u8-1].xPhySecIdx_u8] = xLogSecIdx_u8-1;
					xLogSecIdx_u8++;
				}while(xLogSecIdx_u8<FEE_NUM_FLASH_BANKS);

				/* Update the state information of the last sector in the ring */
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].SecState_en     = FEE_SECTOR_REQUEST2ERASE_E;
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].xPhySecIdx_u8   = xPhySecIdx_u8;
				Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS-1].SecChngCnt_u32  = FEE_SEC_CHANGE_CNT_UNDEF;
				Fee_idxLLSectorOrder_au8[xPhySecIdx_u8] = FEE_NUM_FLASH_BANKS-1;
				xRepeatSortLoop_u8 = 1;
			}
		}
	}
	while(xRepeatSortLoop_u8 != 0);

    /* Return the index of the most current sector */
    return (xActiveSec_u8);
}


/**
 *********************************************************************
 * Fee_LLSearchSectors(): Read all sector headers
 *
 * This function reads the sector headers of all configured sectors
 * and stores its sector change counters which can be found within
 * the marker content. This information is the base for finding
 * the currently active sector by the function
 * Fee_Rb_LLDetecActiveSector.
 *
 * Hint: It is not allowed to call this function if the scheduling
 * is currently running (e.g. outside the intialization or shutdown
 * phase).
 *
 * \param    Fee_stSecDet_ps:   Pointer to an array of marker
 *                              structures
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_LLSearchSectors(P2VAR(Fee_stSecDet_tst, AUTOMATIC, FEE_APPL_DATA) Fee_stSecDet_ps)
{
    VAR(Fee_MarkerProp_t, AUTOMATIC)    xRdMarker;                  /* Marker structure */
    VAR(uint32, AUTOMATIC)              xTmpMarkerContent_u32;      /* Marker content */
    VAR(uint8, AUTOMATIC)               xCurrSect_u8 = 0;           /* Current sector index */
    VAR(uint16, AUTOMATIC)              xCalc_crc_u16;              /* CRC16 variable */
    VAR(sint8, AUTOMATIC)				xMarkerIdx_s8 = -1;			/* Marker index */
    VAR(uint32, AUTOMATIC)				xAdrBlnkChk_u32 = FEE_NULL;	/* Blank check address */

    /* Set the number of Retries */
    Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

    /* Loop over all sectors */
    while (xCurrSect_u8<FEE_NUM_FLASH_BANKS)
    {
        /* Read state machine */
        switch(Fee_RdWrOrder_st.Fee_LLRdState_en)
        {
            /* Init state */
            case FEE_LL_INIT_READ_E:
            {
                /* Initialize sector info array */
                Fee_stSecDet_ps[xCurrSect_u8].ctErasedMarker_u8    = 0;
                Fee_stSecDet_ps[xCurrSect_u8].ctUsedMarker_u8      = 0;
                Fee_stSecDet_ps[xCurrSect_u8].ctFullMarker_u8      = 0;
                Fee_stSecDet_ps[xCurrSect_u8].ctEraseReq_u8        = 0;
                Fee_stSecDet_ps[xCurrSect_u8].ctCloneMarker_u8     = 0;
                Fee_stSecDet_ps[xCurrSect_u8].SecChngCnt_u32       = FEE_SEC_CHANGE_CNT_UNDEF;
				Fee_stSecDet_ps[xCurrSect_u8].xStartAddr_u32       = FEE_MAXUINT32;
                /* Initialize global array for accessing sectors in the correct order */
                Fee_LLSectorOrder_st[xCurrSect_u8].SecChngCnt_u32 = FEE_SEC_CHANGE_CNT_UNDEF;
                Fee_LLSectorOrder_st[xCurrSect_u8].xPhySecIdx_u8  = 0;
                Fee_LLSectorOrder_st[xCurrSect_u8].SecState_en    = FEE_SECTOR_STATE_UNDEF_E;

                /* Reset buffer */
                Fee_SrvMemSet8((uint8*)&Fee_MarkerBufBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN , FEE_SEC_HEADER_SIZE);

                /* Set next state */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_BLANK_CHECK_E;

                /* Initialize last erased marker for this sector */
                Fee_LastErasedMarker_u16[xCurrSect_u8]  = 0;

                /* Initialize the marker index */
                xMarkerIdx_s8 = -1;

                /* Init the start address */
                xAdrBlnkChk_u32 = Fee_FlashProp_st[xCurrSect_u8].Fee_PhysStartAddress_u32 - FEE_PAGE_LEN;
            }
            /* No break to save time */

            /* Perform a blank check */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_BLANK_CHECK_E:
            {
            	/* Increment the marker index */
            	xMarkerIdx_s8++;

            	/* Check if the end of the marker section is already reached */
            	if(xMarkerIdx_s8 <= FEE_NUM_MARKER_IN_HEADER)
            	{
                    /* Calculate the blank check address for the next marker (markers will start only at a free page) */
                    xAdrBlnkChk_u32 += FEE_PAGE_LEN;

                    /* Call the blank check function
                     * -> for devices in witch the FEE_PHY_PAGE_LEN is smaller than FEE_MARKER_SIZE the second part of the marker needs to be checked! */

                    /* MR12 RULE 2.2 VIOLATION: Checks the last phys. header page. If phys. size equals logical,
                          this leads to checking with Offset 0*/
                    if(Fls_Rb_BlankCheck(xAdrBlnkChk_u32 + (FEE_PAGE_LEN - FEE_PHY_PAGE_LEN),
                                         NULL_PTR,
                                         FEE_PHY_PAGE_LEN) != E_NOT_OK)
					{
						/* Set the next state */
						Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_BLANK_CHECK_WAIT_E;
					}
					else
					{
						/* Error handling due to wrong user parameters or a currently active FLS
                         * -> Try again with the next sector*/
						Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
						xCurrSect_u8++;
					}
            	}
            	else
            	{
            		/* Go on with the next sector */
            		Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
					xCurrSect_u8++;
            	}
            }
            break;

            /* Wait for the blank check to be finished */
            case FEE_LL_BLANK_CHECK_WAIT_E:
			{
				/* The next state will be set by the Fee_JobEndNotification () or
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
			}
			break;

            /* Call read order for the sector header area */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_READ_PAGE_E:
            {
                /* Read the one sector marker only */
                if(Fls_Read(xAdrBlnkChk_u32,
                           (uint8*)&Fee_MarkerBufBytePtr_cpu8[0],
                           (FEE_MARKER_SIZE)) != E_NOT_OK)
                {
                    /* Set next state */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_WAIT_READ_PAGE_E;
                }
                else
                {
                    /* Error handling due to wrong user parameters or a currently active FLS
                     * -> Try again with the next sector */
                    Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                    xCurrSect_u8++;

                    /* Set the number of Retries for the next sector */
                    Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;
                }
            }
            break;

            /* Wait until the read order has finished */
            case FEE_LL_WAIT_READ_PAGE_E:
            {
                /* The next state will be set by the Fee_JobEndNotification () or
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
            }
            break;

            /* Evaluate the content of the markers */
            case FEE_LL_READ_FINISHED_E:
            {
				/* Copy the content of the marker buffer to a read buffer and extract the
                 * organizational data from the raw data */
				Fee_LLCopyPageBuff2Marker(&xRdMarker, &Fee_MarkerBufBytePtr_cpu8[0]);

				/* Evaluate the marker pattern */
				if (xRdMarker.xPattern == FEE_MARKER_PATTERN)
				{
					/* Calculate checksum over one marker */
					/* MR12 RULE 11.3 VIOLATION: Variable must be changeable */
					xCalc_crc_u16 = Crc_CalculateCRC16((const uint8*)&xRdMarker,
													   (uint32)(FEE_MARKER_SIZE-FEE_MARKER_CS_SIZE),
													   (uint16)FEE_MARKER_PATTERN,
														FALSE);

                    /* Compare the marker checksums */
                    if (xCalc_crc_u16 == xRdMarker.xChecksum)
                    {
                        /* Extract the marker content byte - wise */
                        xTmpMarkerContent_u32  = (uint32)(((uint32)(xRdMarker.xContent[0])) << 16u);
                        xTmpMarkerContent_u32 |= (uint32)(((uint32)(xRdMarker.xContent[1])) << 8u);
                        xTmpMarkerContent_u32 |= (uint32)(xRdMarker.xContent[2]);

                        /* Request2Erase and Start-Marker do not have the sector change counter as payload. Because payload of Request2Erase Marker
                         * is always 0, no special handling is required. */
                        switch (xRdMarker.xIdent)
                        {
                            case (uint8)FEE_ERASED_MARKER_ID_E:
                            case (uint8)FEE_USED_MARKER_ID_E:
                            case (uint8)FEE_FULL_MARKER_ID_E:
                            {
                                if ((Fee_stSecDet_ps[xCurrSect_u8].SecChngCnt_u32 <= xTmpMarkerContent_u32) || (Fee_stSecDet_ps[xCurrSect_u8].SecChngCnt_u32 == FEE_MAXUINT32))
                                {
                                    /* Save the current sector change counter (available within nearly all markers). Normaly all markers should have the same
                                     * sector change counter. If there are different once available, ensure to take the highest one. */
                                    Fee_stSecDet_ps[xCurrSect_u8].SecChngCnt_u32 = xTmpMarkerContent_u32;
                                }
                            }break;

                            case (uint8)FEE_START_MARKER_ID_E:
                            {
                                /* Save the current sector change counter. In the START marker, only the 3 low-bytes of the address are stored. The start address
                                 * of the logical sector was used to initialize ...xStartAddr_u32. To get the absolut address, it is necessary to "merge" the
                                 * logical start-address of the sector with the relative address in the sector. In case of sector-size > 2^24 = 16,7MByte, this
                                 * mechanisms will not work anymore. */
                                Fee_stSecDet_ps[xCurrSect_u8].xStartAddr_u32  = (Fee_FlashProp_st[xCurrSect_u8].Fee_LogStartAddress_u32 & 0xFF000000uL);
                                Fee_stSecDet_ps[xCurrSect_u8].xStartAddr_u32 |= xTmpMarkerContent_u32;
                            }break;

                            case (uint8)FEE_ERASE_REQUEST_ID_E:
                            case (uint8)FEE_CLONE_START_MARKER_ID_E:
                            default:
                            {
                                /* marker has no content, or the content is not used in the moment */
                            }break;
                        }

                        /* Check for the different marker IDs */
                        switch(xRdMarker.xIdent)
                        {
                            /* Erase marker ID was found */
                            case (uint8)FEE_ERASED_MARKER_ID_E:
                                /* Increment the amount of its availability */
                                Fee_stSecDet_ps[xCurrSect_u8].ctErasedMarker_u8++;

                                /* Save the last erased marker position within the sector header in order to check
                                 * the subsequent position for a damaged USED marker */
                                /* MR12 DIR 4.1 VIOLATION: Only the start value is negative, it cannot be negative here */
								Fee_LastErasedMarker_u16[xCurrSect_u8]  = (uint16)xMarkerIdx_s8;
							break;

							/* Used marker ID was found */
						    case (uint8)FEE_START_MARKER_ID_E:
							case (uint8)FEE_USED_MARKER_ID_E:
								/* Increment the amount of its availability */
								Fee_stSecDet_ps[xCurrSect_u8].ctUsedMarker_u8++;
							break;

							/* Full marker ID was found */
							case (uint8)FEE_FULL_MARKER_ID_E:
								/* Increment the amount of its availability */
								Fee_stSecDet_ps[xCurrSect_u8].ctFullMarker_u8++;
                            break;

                            /* Erase request marker ID was found */
                            case (uint8)FEE_ERASE_REQUEST_ID_E:
                                /* Increment the amount of its availability */
                                Fee_stSecDet_ps[xCurrSect_u8].ctEraseReq_u8++;
                            break;

                            /* Clone Marker for IFX-Robust programming algorithm found */
                            case (uint8)FEE_CLONE_START_MARKER_ID_E:
                                /* Increment the amount of its availability */
                                Fee_stSecDet_ps[xCurrSect_u8].ctCloneMarker_u8++;
                            break;

                            /* This state should never be reached */
                            default:
                                /* Error handling due to a wrong marker ID with valid checksum
                                 * -> Try again with the next sector (done already at end of case) */
                                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                            break;
                           }
                    }
                    else
                    {
                        /* Error handling due to an invalid marker (wrong checksum)
                         * -> Search until the end of the marker region */
                        ;
                    }
                }
                else
                {
                    /* No marker was found (wrong or no pattern)
                     * -> Search until the end of the marker region */
                    ;
                }

                /* Prepare state machine to run again for the next marker inside the same sector */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_BLANK_CHECK_E;
            }
            break;

            /* Error reaction for read error */
            case FEE_LL_READ_ERROR_E:
                /* Reset the respective array and either read out the same sector again or
                 * the next one depending on the retry possiblity */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;

                /* Verify retry possibility */
                if(Fee_RdWrRetries_u8 > 0)
                {
                    /* Decrement retry possibilities */
                    Fee_RdWrRetries_u8--;
                }
                else
                {
                    /* Skip the current sector and try to read out the next one if possible */
                    xCurrSect_u8++;

                    /* Set the number of Retries for the next sector */
                    Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;
                }
            break;

            default:
            {
                /* Prepare state machine to run again for the next sector */
                Fee_RdWrOrder_st.Fee_LLRdState_en = FEE_LL_INIT_READ_E;
                xCurrSect_u8++;

                /* Set the number of Retries for the next sector */
                Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;
            }
            break;
        }
    }
}


/**
 *********************************************************************
 * Fee_LLFindEmptyPage(): Find first empty page
 *
 * This function searches the first free page in the sector
 * with the most current data if its sector state is USED.
 *
 * Hint: this function can only be called inside the initialization
 *       phase of the ECU (scheduling should be disabled).
 *
 * \param    PhySectIdxUsedSect_u8: Physical sector index to use for the search
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Function has to be called again
 * \retval   FEE_ABORTED_E:         Function was aborted (wrong sector
 *                                  state or wrong Fls parameters)
 * \retval   FEE_ORDER_FINISHED_E:  Function successfully finished
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLFindEmptyPage(uint8 PhySectIdxUsedSect_u8)
{

#if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )

    /*
     * For FLSRH850 flash the provided blank check mechanism is used.
     * First the whole used sector is checked in big chunks to roughly identify the last written space.
     * Then the last big block which is not fully blank is checked in small steps to accurately
     * find the new write address.
     */

    /*
     * s  = size of a sector
     * b1 = big step size
     * b2 = small step size
     *
     * t1 = basic costs for triggering one blank check
     * t2 = costs for blank check per byte
     *
     * Duration of a blank check with big and small steps on the whole sector:
     *
     * f(s, b1, b2) = (s/b1)*t1 + s*t2 + (b1/b2)*t1 + b1*t2
     *
     * This time should be as small as possible, therefore we can leave out s*t2 since we cannot influence it
     *
     * f(s, b1, b2) = (s/b1 + b1/b2)*t1 + b1*t2
     *
     * Following values were APPROXIMATELY measured:
     *
     * t1 = 70    us
     * t2 = 0.625 us
     *
     * f(s, b1, b2) = (s/b1 + b1/b2)*70 + b1*0.625
     *
     * The second summand should be much smaller than the first summand so we can leave it out
     * and also remove the constant factor 70 since it is just a linear change
     *
     * f(s, b1, b2) = s/b1 + b1/b2
     *
     * s  is fixed to sector size
     * b2 must be a page length
     * so the only factor we can vary is b1
     *
     * Since the first summand doubles if b1 doubles and the second summand halves if b1 halves
     * the smallest value is achieved if:
     *
     * s/b1 = b1/b2 =>
     * b1   = sqrt(s * b2)
     *
     * of course this is not exact but an approximation
     * for the first try this code is optimized for s = 8192 and b2 = 16
     * b1 = sqrt(8192 * 16) = 362
     * to make sure the big step is always bigger than the small step we express the big step in small steps
     * b1 = 362/b2 = 362/16 = 22.65 => Round to power of 2 => 16
     */

    /* Big and small steps */
    CONST(uint32, AUTOMATIC) smallStep_cu32 = FEE_PAGE_LEN;
    CONST(uint32, AUTOMATIC) bigStep_cu32   = smallStep_cu32 * 16uL;

    static VAR(uint32,  AUTOMATIC) adrCurr_u32  = 0;    /* Current address which is investigated            */
    static VAR(uint32,  AUTOMATIC) adrWrite_u32 = 0;    /* New read/write address                           */
    static VAR(uint32,  AUTOMATIC) adrEnd_u32   = 0;    /* End address - either sector end or big block end */
    static VAR(uint32,  AUTOMATIC) stepSize_u32 = 0;    /* Small or big step size                           */

    VAR(uint32,             AUTOMATIC) checkChunk_u32   = 0;                    /* Amount of data for the blank check   */
    VAR(Fee_stRetVal_ten,   AUTOMATIC) xRetVal_en       = FEE_ORDER_PENDING_E;  /* Return value                         */

    /* Run through the whole sector */
    do
    {
        /* Empty page state machine in case it is not used in polling mode */
        switch(Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en)
        {
            /* Initialize static variables for the check */
            case FEE_LL_FINDEMPTYPGE_INIT_E:
            {
                adrCurr_u32                                     = Fee_LLGetSecStartAddress(PhySectIdxUsedSect_u8);
                adrWrite_u32                                    = adrCurr_u32;
                adrEnd_u32                                      = Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8);
                stepSize_u32                                    = bigStep_cu32;
                Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en    = FEE_LL_FINDEMPTYPGE_CHECK_E;
            }
            break;

            /* Start a blank check for one chunk */
            case FEE_LL_FINDEMPTYPGE_CHECK_E:
            {
                /* Is the end of the big block / sector reached */
                if(adrCurr_u32 >= adrEnd_u32)
                {
                    /* Small step size, so it is the end of the big block */
                    if(stepSize_u32 == smallStep_cu32)
                    {
                        /* Adjust write address to page borders */
                        adrWrite_u32 += (FEE_PAGE_LEN - (adrWrite_u32 % FEE_PAGE_LEN)) % FEE_PAGE_LEN;

                        xRetVal_en = FEE_ORDER_FINISHED_E;
                    }
                    /* Big step size, so it is the end of the sector */
                    else
                    {
                        /* Set the currently investigated address pointer to the begin of the last big blank block */
                        if(bigStep_cu32 > (adrWrite_u32 - Fee_LLGetSecStartAddress(PhySectIdxUsedSect_u8)))
                        {
                            adrCurr_u32 = Fee_LLGetSecStartAddress(PhySectIdxUsedSect_u8);
                        }
                        else
                        {
                            adrCurr_u32 = adrWrite_u32 - bigStep_cu32;
                        }

                        /* Switch to small step size */
                        stepSize_u32 = smallStep_cu32;
                    }

                    /*
                     * If sector is completely full set the write address to the end of the sector.
                     * This way it is ensured that during next startup a sector change is triggered.
                     */
                    if(adrWrite_u32 > Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8))
                    {
                        adrWrite_u32 = Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8);
                    }

                    /*
                     * BigStepSize:     Set the end address to the end of the last big blank block
                     *                  Use the limitiation to the sector end of the write address above
                     * SmallStepSize:   No effect since state machine is aborted anyway
                     */
                    adrEnd_u32 = adrWrite_u32;
                }
                else
                {
                    /* Chop chunk which should be checked in case the end of the sector is reached */
                    checkChunk_u32 = stepSize_u32;
                    if( (adrCurr_u32 + stepSize_u32) > adrEnd_u32 )
                    {
                        checkChunk_u32 = (adrEnd_u32 - adrCurr_u32) + 1uL;
                    }

                    /* Delegate blank check to flash driver */
                    if(Fls_Rb_BlankCheck(adrCurr_u32, NULL_PTR, checkChunk_u32) != E_NOT_OK)
                    {
                        adrCurr_u32 += checkChunk_u32;
                        Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_WAIT_E;
                    }
                    else
                    {
                        xRetVal_en = FEE_ABORTED_E;
                    }
                }
            }
            break;

            /*
             * Wait until blank check finished
             * In case of polling mode poll the status of the flash driver
             * Otherwise the state transission is triggered by a callback
             */
            case FEE_LL_FINDEMPTYPGE_WAIT_E:
            {
                Fls_MainFunction();

                #if (STD_ON == FEE_POLLING_MODE)
                Fee_CheckFlsJobResult();
                #endif
            }
            break;

            /* Last checked block is blank */
            case FEE_LL_FINDEMPTYPGE_RESULT_BLANK_E:
            {
                Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_CHECK_E;
            }
            break;

            /* Last checked block is not blank */
            case FEE_LL_FINDEMPTYPGE_RESULT_NOT_BLANK_E:
            {
                /* Set the read/write address to the end of the not blank block */
                adrWrite_u32                                 = adrCurr_u32;
                Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINDEMPTYPGE_CHECK_E;
            }
            break;

            default:
            {
                /* Should never occur */
                xRetVal_en = FEE_ABORTED_E;
            }
            break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal_en == FEE_ORDER_PENDING_E));

    /* Finished */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Set read and write address and reset state machine */
        Fee_RdWrOrder_st.xRdAddress                     = adrWrite_u32;
        Fee_RdWrOrder_st.xWrAddress                     = adrWrite_u32;
        Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en    = FEE_LL_FINDEMPTYPGE_INIT_E;
    }

    return(xRetVal_en);

#else

    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en     = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xTmpRetVal_en  = FEE_ORDER_PENDING_E;  /* Function temp return */
    VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC) xBlkHdrTmp_st;             /* Temporary block header */

    #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
	static uint32 xRdAddrStrt_u32;
	VAR(uint8, AUTOMATIC) xCacheUpdateType_u8       = FEE_UPDATE_CACHE_IN_INIT; /* Init value */
	#endif

    /* Loop if polling mode is active and function state is pending */
    do
    {
        /* Switch over state machine */
        switch(Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en)
        {
            /* Identify the start address */
            case FEE_LL_FIND_CURRENT_SECTOR_E:
            {
                /* Reset temporary block header */
                xBlkHdrTmp_st.FeeIndex_u16 = FEE_MAXUINT16;

               /* Set the read address to the begining of the sector for which cache must be built up. */
               Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecStartAddress(PhySectIdxUsedSect_u8);

               /* Reset the start address for the search */
               #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
               xRdAddrStrt_u32 = Fee_RdWrOrder_st.xRdAddress;
               #endif

               Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FIND_LAST_HEADER_E;
            }
            /* Search for the block header in the active sector */
            /* MR12 RULE 16.3 VIOLATION: Time critical position */
            case FEE_LL_FIND_LAST_HEADER_E:
            {
                #if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
                /* Search for the highest address within the sectors using the cache entries */
                xTmpRetVal_en = Fee_SearchLastBlkHeader(&xBlkHdrTmp_st);
                #else
                /* Search for the next block header without cache usage (FEE_MAXUINT16).
                 * This function will be called until the end of the sector is reached. */
                xTmpRetVal_en = Fee_LLSearchNextBlkHeader(&xBlkHdrTmp_st, FEE_USE_MANUAL_ACCESS, xCacheUpdateType_u8, FALSE, xRdAddrStrt_u32);
                #endif

                /* Evaluate return value */
                switch(xTmpRetVal_en)
                {
                    /* Order is still pending */
                    case FEE_ORDER_PENDING_E:
                    {
                        /* Do nothing */
                        ;
                    }
                    break;

                    /* Order is finished */
                    case FEE_ORDER_FINISHED_E:
                    #if(FEE_FAST_CACHE_INIT_ACTIVE == FALSE)
                    {
                        /* A valid block header was found. Set address for next free page or block header.
                         * Hint: increment the address via "page mode" (a reload of a complete page buffer
                         *       is only necessary if the new read address has not been loaded before) */
						Fee_RdWrOrder_st.xRdAddress = (uint32)(xBlkHdrTmp_st.AdrBlkHeader_u32 + FEE_PAGE_LEN);

                        /* Ensure page alignment */
						/* MR12 RULE 14.2 VIOLATION: The variable is updated and used within the same function itself. */
						while((Fee_RdWrOrder_st.xRdAddress % FEE_PAGE_LEN) != 0u)
                        {
                            /* Increment next read address */
                            Fee_RdWrOrder_st.xRdAddress++;
                        }
                        xRdAddrStrt_u32 = Fee_RdWrOrder_st.xRdAddress;

                        /* Come back to this state because the next empty page has to be found
                         * and not the next block header. */
                    }
                    break;

                    /* The end of the active sector is reached. No valid page header was found within a certain
                     * amount of pages or until the end of the sector. There might be a valid page header available
                     * within the searched sector that was found before. */
                    case FEE_SECTORFULL_E:
                    #endif
                    {
                        /* Check if a valid block header was found */
                        if (xBlkHdrTmp_st.FeeIndex_u16 != FEE_MAXUINT16)
                        {
                            /* At least one valid block header was found in the active sector. */
							/* Set next free page behind the last found block (overlap in USED sectors not possible) */
							Fee_RdWrOrder_st.xRdAddress = (uint32)(xBlkHdrTmp_st.AdrBlkHeader_u32 + (uint32)FEE_BLK_HEADER_SIZE + xBlkHdrTmp_st.BlkLength_u16);

							/* Reading will always start on a page boundary */
							/* MR12 RULE 14.2 VIOLATION: The variable is updated and used within the same function itself. */
							while ((Fee_RdWrOrder_st.xRdAddress % FEE_PAGE_LEN) != 0u)
							{
								Fee_RdWrOrder_st.xRdAddress++;
							}

							/* Check for overlapping block */
							if (Fee_RdWrOrder_st.xRdAddress > Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8))
							{
								Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8);
							}
                        }
                        else
                        {
                            /* No valid block header was found in the active sector
                             * --> check if other FULL sectors contain a valid header in order to
                             *     be able to locate the next empty page (programmed erase pattern
                             *     might not be detected otherwise) */
							if (Fee_RdWrOrder_st.xStartAddrNextSector_u32 != FEE_MAXUINT32)
							{
								/* A START-Marker was found --> use this address as read-address */
								 Fee_RdWrOrder_st.xRdAddress = Fee_RdWrOrder_st.xStartAddrNextSector_u32;
							}
							else
							{
								/* No START-Marker was found --> Maybe this sector was never programmed except inside the sector header */
								Fee_RdWrOrder_st.xRdAddress = Fee_LLGetSecStartAddress(PhySectIdxUsedSect_u8);
							}

                        }

                        /* Perform a blank check */
                        Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FINISHED_E;
                    }
                    break;

                    /* Order was aborted due to a wrong Fls access or due to the
                     * sector state (do not search within not USED sectors) */
                    #if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
                    case FEE_SECTORFULL_E:
                    #endif
                    case FEE_ABORTED_E:
                    case FEE_ERROR_E:
                    case FEE_SEARCH_ABORTED_E:
                    default:
                    {
                        /* Leave the loop */
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    break;
                }
            }
            break;

			/* Check for the erase pattern  */
            case FEE_LL_FINISHED_E:
            {
                /* Set the sector start address for the next write address because the read
                 * address points to the first empty page or the end of the sector. */
                Fee_RdWrOrder_st.xWrAddress = Fee_RdWrOrder_st.xRdAddress;

                /* Check if this value is more then the last programmed address found during cache build up, if no correct the next free page address. */
                if (Fee_RdWrOrder_st.xWrAddress < (Fee_RdWrOrder_st.LastProgrammedAddress_u32+FEE_PAGE_LEN))
                {
                    Fee_RdWrOrder_st.xWrAddress = Fee_RdWrOrder_st.LastProgrammedAddress_u32+FEE_PAGE_LEN;

                    /* Check for overlapping block */
                    if (Fee_RdWrOrder_st.xWrAddress > Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8))
                    {
                        Fee_RdWrOrder_st.xWrAddress = Fee_LLGetSecEndAddress(PhySectIdxUsedSect_u8);
                    }
                    else
                    {
                        /* Block is not overlapping to another sector. Nothing required to be done. */
                    }

                    Fee_RdWrOrder_st.xRdAddress = Fee_RdWrOrder_st.xWrAddress;
                }

                /* Set return value */
                xRetVal_en = FEE_ORDER_FINISHED_E;
            }
            break;

            /* Default case should never be reached */
            default:
            {
                /* Return with error */
                xRetVal_en = FEE_ABORTED_E;
            }
            break;
        }
    }
    while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal_en == FEE_ORDER_PENDING_E));

    /* Check if the internal state machine needs to be reset */
    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Ensure reset of the state machine */
        Fee_RdWrOrder_st.Fee_LLFindEmptyPageState_en = FEE_LL_FIND_CURRENT_SECTOR_E;
    }

    return(xRetVal_en);

#endif

}

/**
 *********************************************************************
 * Fee_CheckErasedSectorEmpty(): Check all erased sectors
 *
 * This function checks for all erased sectors if they are really erased.
 * The subsequent page after an ERASED marker will be checked, if not
 * blank, a USED marker will be written in the first blank page
 * afterwards.
 *
 * \param    none
 * \return   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 1505 VIOLATION: This function is used within the same file and has no external linkage */
FUNC(void, FEE_CODE) Fee_CheckErasedSectorEmpty(void)
{
    VAR(uint8, AUTOMATIC)  xCurrSect_u8 = 0;        /* Sector loop counter */
    VAR(uint8,  AUTOMATIC) xCurrSectPhys_u8 = 0;    /* Physical current sector number */
    VAR(uint32, AUTOMATIC) xPageAfterErased_u32  = 0;      /* Next page address after erased marker */
    VAR(Fee_stRetVal_ten,  AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;

    /* Inner loop over all configured flash banks */
    for(xCurrSect_u8=0; xCurrSect_u8<FEE_NUM_FLASH_BANKS; xCurrSect_u8++)
    {
        /* Check for all erased sectors, if they are really empty. If the flash cell of a USED marker is weakly programmed,
         * it might disappear after some some time. In this case, the current used sector has also only an ERASED marker
         * --> extra check to avoid data loss */

        /* If the sector header is full: no need to check this sector */
        if((Fee_LLSectorOrder_st[xCurrSect_u8].SecState_en == FEE_SECTOR_ERASED_E) &&
           (Fee_LastErasedMarker_u16[xCurrSectPhys_u8] < ((uint16)FEE_NUM_MARKER_IN_HEADER-1u)))
        {
            /* Store physical sector number */
            xCurrSectPhys_u8 = Fee_LLSectorOrder_st[xCurrSect_u8].xPhySecIdx_u8;

            /* Load blank check address after the ERASED marker */
            xPageAfterErased_u32 = Fee_FlashProp_st[xCurrSectPhys_u8].Fee_PhysStartAddress_u32 +
                    					((Fee_LastErasedMarker_u16[xCurrSectPhys_u8] + 1u) *
                    							(FEE_SEC_HEADER_SIZE/(uint16)FEE_NUM_MARKER_IN_HEADER));

            /* Set next state */
            Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_PERFORM_BLANK_CHECK_E;

            /* Init return value */
            xRetVal_en = FEE_ORDER_PENDING_E;

            /* Loop if polling mode is active and function state is pending */
            do
            {
                /* Switch over state machine */
                switch(Fee_RdWrOrder_st.Fee_LLBlankCheckState_en)
                {
                    /* Read the data */
                    case FEE_LL_PERFORM_BLANK_CHECK_E:
                    {
                        /* Call the blank check function
                         * Hint: xNumBytes2Read will always be smaller than the FEE_LL_PAGEUFFSIZE so the buffer can be used. */
                        if(Fls_Rb_BlankCheck(xPageAfterErased_u32, NULL_PTR, (uint32)(FEE_SEC_HEADER_SIZE/(uint16)FEE_NUM_MARKER_IN_HEADER)) != E_NOT_OK)
                        {
                            Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_WAIT_PERFORM_BLANK_CHECK_E;
                        }
                        else
                        {
                            /* Error handling due to wrong user data: check the next bytes */
                        }
                    }
                    break;

                    /* Wait until the read order is finished */
                    case FEE_LL_WAIT_PERFORM_BLANK_CHECK_E:
                    {
                        /* The next state will be set by the Fee_JobEndNotification () or
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
                    }
                    break;

                    /* Differences detected */
                    case FEE_LL_BLANK_CHECK_ERROR_E:
                    {
                        /* Differences to the erase pattern were detected, check the next address area */

                        /* Mark this sector as USED */
                        if(Fee_LLWriteMarker(xCurrSectPhys_u8, FEE_USED_MARKER_ID_E) != FEE_ORDER_PENDING_E)
                        {
                            /* Set return type */
                            xRetVal_en = FEE_ORDER_FINISHED_E;

                            /* Restart the state machine */
                            Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_INIT_BLANK_CHECK_E;
                        }
                    }
                    break;

                    /* Finish the state machine */
                    case FEE_LL_BLANK_CHECK_FINISHED_E:
                    {
                        /* No differences were detected, finish the function with the xRdAddress keeping
                         * its old value */
                        xRetVal_en = FEE_ORDER_FINISHED_E;

                        /* Restart the state machine */
                        Fee_RdWrOrder_st.Fee_LLBlankCheckState_en = FEE_LL_INIT_BLANK_CHECK_E;
                    }
                    break;

                    /* Default case should never be reached */
                    default:
                    {
                        /*If the statemachine is corrupted by any influence, keep the SW being stuck*/
                    }
                    break;
                }
            }
            while((Fee_stMain == FEE_POLLING_MODE_E) && (xRetVal_en == FEE_ORDER_PENDING_E));
        }
    }
}

/**
 *********************************************************************
 * Fee_GetMostCurrentSectorIdx(): Find most current sector
 *
 * This function searches for the sector with the most current
 * values and returns its index.
 *
 * \param    none
 * \return
 * \retval   0...254:   Index of physical sector
 * \retval   255:       No sector found
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint8, FEE_CODE) Fee_GetMostCurrentSectorIdx(void)
{
    VAR(uint8,AUTOMATIC) xCntFlashBank_u8;                       /* Loop counter */
    VAR(uint8,AUTOMATIC) xActiveSec_u8 = FEE_NO_SEC_IDX_FOUND;   /* Function return */
	VAR(uint8,AUTOMATIC) xFirstErasedSec_u8 = FEE_NO_SEC_IDX_FOUND;	/* Temporary function return */

    /* Explanation and hints
     * *********************
     *
     * Sector order is always:
     *
     *  +---------------+  (1) (2) (3) (4) (5)
     *  |     FULL      |   D   D   D   D   D
     *  |      #0       |   D   D   D   D   D
     *  |               |   D   D   D   D   D
     *  +---------------+   D   D   D   D   D
     *  |     FULL      |   D   D   D   D   D
     *  |      #1       |   D   D   D   D   D
     *  |               |   D   D   D   D   D
     *  +---------------+   D   D   D   D   D
     *  |     USED      |   D       D       D
     *  |      #2       |           D       D
     *  |               |           D       D
     *  +---------------+           D       D
     *  |    ERASED     |
     *  |      #3       |
     *  +---------------+
     *  |undef./ReqErase|
     *  |      #4       |
     *  +---------------+
     *
     *  Possible cases:
     *
     *  (1) Sector state == USED
     *      Data was written in the sector with state used but there is still free space
     *      available within the sector (normal case)
     *      ==> Read address points to the last header page in sector #2
     *          Write address points to the first page behind the block (usage of the block length for calculation of last page)
     *
     *  (2) Sector state == USED
     *      Data was not written in the sector due to a write interruption after writing the sector state
     *      ==> Read address points to the last block header in the previous sector (#1)
     *          Write address points to the first page behind the last blockheader  (#1)
     *
     *  (3) Sector state == USED
     *      Sector is completely filled, write interruption occured before writing the sector state (FULL)
     *      ==> Read address points to the last block header inside sector #2
     *          Write address points to the next sector. The Calculation is based on the length within the last blockheader (of sector #2)
     *
     *  (4) Sector state == FULL
     *      Same case as (2) - at least from data point of view. Interruption occurs directly after the sector
     *      state "FULL" was written
     *      ==> Read address see above
     *          Write address see above
     *
     *  (5) Sector state == FULL
     *      Same case as (3) - at least from data point of view. Interruption occurs directly after sector state
     *      "FULL" was written
     *      ==> Read  address see above
     *          Write address see above
     */

    /* Loop over all configured flash banks */
    for(xCntFlashBank_u8=0; xCntFlashBank_u8<FEE_NUM_FLASH_BANKS; xCntFlashBank_u8++)
    {
        /* Check if the current sector is in state FULL */
        if(Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_FULL_E)
        {
            /* This sector should be used to search for block headers if no other USED sector was found */
            xActiveSec_u8 = Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8;
        }

        /* Check if the current sector is in state USED */
        if(Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_USED_E)
        {
            /* This is the active sector, search for the first block header */
            xActiveSec_u8 = Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8;

            /* Hint: No break, otherwise the first FULL sector will be detected as first USED sector
             * in case a full sector containing a FULL marker was destroyed.
             * -> The last found USED sector should remain the active one !!! */
        }

        /* Check if the current sector is in state ERASED and no active sector has been found so far */
        if((Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_ERASED_E) &&
           (xActiveSec_u8 == FEE_NO_SEC_IDX_FOUND))
        {
			/* Check if this is the first ERASED sector */
			if(xFirstErasedSec_u8 == FEE_NO_SEC_IDX_FOUND)
			{
				/* Save this sector temporarily */
				xFirstErasedSec_u8 = xCntFlashBank_u8;
			}
        }

        /* If no sector with the state "USED" or "ERASED" was found during the sector detection (Fee_LLDetectActiveSector),
         * the logical sector 0 was marked to be erased already. */
        if(((Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_STATE_UNDEF_E) ||
            (Fee_LLSectorOrder_st[xCntFlashBank_u8].SecState_en == FEE_SECTOR_REQUEST2ERASE_E)) &&
            (xActiveSec_u8 == FEE_NO_SEC_IDX_FOUND) &&
			(xFirstErasedSec_u8 == FEE_NO_SEC_IDX_FOUND))
        {
            /* Mark the current sector to be the active one */
            xActiveSec_u8 = Fee_LLSectorOrder_st[xCntFlashBank_u8].xPhySecIdx_u8;
        }
    }

	/* Check if there are no USED or FULL sectors available but an erased sector was found,
	   take the first one as the new active sector */
	if((xActiveSec_u8 == FEE_NO_SEC_IDX_FOUND) && (xFirstErasedSec_u8 != FEE_NO_SEC_IDX_FOUND))
	{
		/* Take the first erased sector as the active one */
		xActiveSec_u8 = Fee_LLSectorOrder_st[xFirstErasedSec_u8].xPhySecIdx_u8;
	}

    /* Return the most current sector index */
    return (xActiveSec_u8);
}


/**
 *********************************************************************
 * Fee_IncAddressInsideSector(): Increment address page aligned
 *
 * This function returns the next page aligned address (+ user length)
 *
 * \param    Address_u32:   Physical user address
 * \param    numBytes_u16:  Number of bytes
 * \param    EnsurePageAlign_b: Ensure page alignment option
 * \return
 * \retval   none
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_IncAddressInsideSector(P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) Address_u32,
                                                VAR(uint16, FEE_VAR) numBytes_u16,
                                                VAR(boolean, FEE_VAR) EnsurePageAlign_b)
{
    /* Get physical sector index belonging to the user address */
    VAR(uint8, AUTOMATIC) xActSector_u8 = Fee_GetPhysSectorByAddress(*Address_u32);

    /* Check for a valid sector index */
    if(xActSector_u8 != FEE_NO_SEC_IDX_FOUND)
    {
        if(EnsurePageAlign_b != FALSE)
        {
            /* Check for the page alignment */
            while((numBytes_u16 % FEE_PAGE_LEN) != 0u)
            {
                /* Increment address */
                numBytes_u16++;
            }
        }

        /* Set address to the beginning of the next page */
        *Address_u32 += numBytes_u16;

        /* Keep address inside of the current sector in case of an address overflow.
         * Otherwise Fee_GetPhysSectorByAddress will return only invalid values */
        if (*Address_u32 > Fee_FlashProp_st[xActSector_u8].Fee_LogEndAddress_u32)
        {
            *Address_u32 = Fee_FlashProp_st[xActSector_u8].Fee_LogEndAddress_u32;
        }
    }
}


/**
 *********************************************************************
 * Fee_GetPhysSectorByAddress(): Get flash bank index
 *
 * This function searches for the physical sector index belonging
 * to the address passed by the user.
 *
 * \param    Address_u32:   Physical user address
 * \return
 * \retval   0...254:       Index of physical flash bank
 * \retval   255:           No configured bank was found which
 *                          matches to the user parameter
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint8, FEE_CODE) Fee_GetPhysSectorByAddress(VAR(uint32, AUTOMATIC) Address_u32)
{
    VAR(uint8, AUTOMATIC) cnt_u8;                          /* Loop counter */
    VAR(uint8, AUTOMATIC) xSec_u8 = FEE_NO_SEC_IDX_FOUND;  /* Function return */


    /* Loop over all configured flash banks */
    for (cnt_u8=0; cnt_u8<FEE_NUM_FLASH_BANKS; cnt_u8++)
    {
        /* Search only within the user area */
        if((Address_u32 >= Fee_FlashProp_st[cnt_u8].Fee_PhysStartAddress_u32) &&
           (Address_u32 <= Fee_FlashProp_st[cnt_u8].Fee_PhysEndAddress_u32))
        {
            /* Save the flash bank index */
            xSec_u8 = cnt_u8;

            /* Loop can be left */
            break;
        }
    }

    /* Return flash bank index */
    return(xSec_u8);
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
