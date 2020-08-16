


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
#include "rba_FeeFs1_Cbk.h"
#include "Fls.h"
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
  //  #error "AUTOSAR major version undefined or mismatched"
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
/* FEE_PRV_DEBUGGING */
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_LLCompBlkInFlash(): Verify block checksums
 *
 * This function can be used to verify block checksums using block
 * header information. It can be called in the following situations:
 * - due to a write order in order to verify the already available
 *   copy in the flash
 * - after a write order in order to verify the programming result
 *
 * Hint: The compare will also work if the data is stored over
 *       sector boundaries.
 *
 * \param    HeaderInfo_ptr:        Pointer to the block header info
 * \param    Data_pcu8:             Pointer to the data to be compared
 * \return
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Difference detected
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCompBlkInFlash(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pcst,
                                                      P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E; /* Function return */
    VAR(uint16, AUTOMATIC) xNumBytes_u16  = 0;              /* Number of bytes */
    VAR(uint8, AUTOMATIC)  xLogSectIdx_u8 = 0;              /* Logical sector index */
    VAR(uint8, AUTOMATIC)  xPhySectIdx_u8 = 0;              /* Physical sector index */
    VAR(uint8, AUTOMATIC)  xPhyWrSectIdx_u8 = 0;            /* Physical sector index of the write address */
	VAR(uint16, AUTOMATIC) xCmpLen_u16;

	/* Switch over the state machine */
	switch(Fee_RdWrOrder_st.Fee_LLCompBlk)
	{
		/* Init state */
		case FEE_LL_CMP_BLK_INIT_E:
		{
			/* Depending on the page size, the header needs more than 1 page and there might be free space for
			 * data behind the header --> compare also data */
			Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = FEE_FREE_BYTES_AFTER_HEADER;

			/* Set next state */
			Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_HEADER_E;
		}
		/* No break to save time */

		/* Compare the complete block header (+ 2 data bytes if possible) against the page buffer */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_CMP_HEADER_E:
		{
			/* Reset the compare result */
			Fee_GlobInfoWrBlock_st.CompareResult_u8 = 0xFF;

			/* Get the block header start address */
			Fee_RdWrOrder_st.xCmpAddress = HeaderInfo_pcst->AdrBlkHeader_u32;

			xCmpLen_u16 = FEE_BLOCK_OVERHEAD + HeaderInfo_pcst->BlkLength_u16;

			if (xCmpLen_u16 > (FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN))
			{
			    xCmpLen_u16 = FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN;
			}

			/* Set the compare order */
			/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
			if (Fls_Compare(Fee_RdWrOrder_st.xCmpAddress,
							(uint8*)Fee_PageBytePtr_cpu8,
							xCmpLen_u16) != E_OK)
			{
				/* An error occured due to wrong parameters or a busy/not init state of the Fls */
				xRetVal_en = FEE_ABORTED_E;
			}
			else
			{
				/* The order was accepted and will be processed in the Fls driver */
				Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_WAIT_HEADER_E;

				/* Increment the compare address (if increment is behind the sector end address, the address will be set to
				 * the sector end address */
				Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xCmpAddress, xCmpLen_u16, TRUE);
			}
		}
		break;

		/* Wait for the compare to finish */
		case FEE_LL_CMP_WAIT_HEADER_E:
		{
			/* The next state (FEE_LL_CMP_DATA_SEC_A_E) will be set by the Fee_JobEndNotification () or
			 * Fee_JobErrorNotification() function automatically (in both cases verify the compare result
			 * inside the next case) */

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

        /* Check for an overlap of the compare address */
        case FEE_LL_CMP_CHECK_OVERLAP_E:
        {
            /* Set the next state */
            Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_DATA_SEC_A_E;

            /* Check if there are more bytes to be read. */
            if(Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 < HeaderInfo_pcst->BlkLength_u16)
            {
                /* Some more bytes are left. check if the next bytes are over sector boundary and handle boundary conditions*/
                /* Get the physical sector index of the current compare address */
                xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xCmpAddress);

                /* If there is only the block header inside the active sector, the Fee_RdWrOrder_st.xCmpAddress has to be set to the
                 * beginning of the next logical sector. */
                if(Fee_RdWrOrder_st.xCmpAddress >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
                {
                    /* The corresponding data is located in the next logical sector */
                    xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1);

                    /* Check if switching from last to first sector requires an overflow */
                    if(xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                    {
                        /* Abort, the block cannot continue in the logical sector 0 */
                        xRetVal_en = FEE_ERROR_E;
                    }
                    else
                    {
                        /* Before switching to next sector, check if next sector is programmed with data and if there are more data to be read. */
                        if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                           (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                        {
                            /* Get the new physical sector index */
                            xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                            /* Set the new start address of the compare */
                            Fee_RdWrOrder_st.xCmpAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;
                        }
                        else
                        {
                            /* Abort, the block check as next sector is still not programmed with data. */
                            xRetVal_en = FEE_ERROR_E;
                            break;
                        }
                    }
                }
            }
            else
            {
                /* There wont be any more reads in the next sector as all bytes are read.
                   Its important that the driver continues with the next step and checks if the data matches. */
            }

        }
        /* No break to save time */

		/* Check the header compare result and compare the data */
        /* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_CMP_DATA_SEC_A_E:
		{
			/* Check the header compare result */
			if (Fee_GlobInfoWrBlock_st.CompareResult_u8 > 0)
			{
				/* The compare failed, leave this function with an error */
				xRetVal_en = FEE_ERROR_E;
			}
			else
			{
				/* The compare is OK, check if there is more data than what has already been checked
				 * inside the block header (additional data pages) */
				if (HeaderInfo_pcst->BlkLength_u16 > Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16)
				{
					/* Get the number of bytes to check */
					xNumBytes_u16 = (uint16)(HeaderInfo_pcst->BlkLength_u16 -
											 Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16);

					/* Check if all the data is located within the same sector and reset the amount of bytes to compare
					 * in the next step, if necessary */
					if (Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_COMPARING) < xNumBytes_u16)
					{
						/* Restrict number of bytes */
						xNumBytes_u16 = (uint16)Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_COMPARING);
					}

					/* Set the compare order */
					if(Fls_Compare(Fee_RdWrOrder_st.xCmpAddress,
								   &Data_pcu8[Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16],
								   xNumBytes_u16) != E_OK)
					{
						/* An error occured due to wrong parameters or a busy/not init state of the Fls */
						xRetVal_en = FEE_ABORTED_E;
					}
					else
					{
						/* The order was accepted and will be processed in the Fls driver */
						Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_WAIT_DATA_SEC_A_E;

						/* Increment the compare address (if increment is behind the sector end address, the address will be set to
						 * the sector end address */
						Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xCmpAddress, xNumBytes_u16, TRUE);

						/* Increase the amount of already checked bytes */
						Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = (uint16)(Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 +
																				 xNumBytes_u16);
					}
				}
				else
				{
					/* All data was stored inside the block header
					 * --> compare successfully finished */

					/* Update the cache with the last header address */
					Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16, HeaderInfo_pcst->AdrBlkHeader_u32);

					/* Set return value */
					xRetVal_en = FEE_ORDER_FINISHED_E;
				}
			}
		}
		break;

		/* Wait for the compare to be finished */
		case FEE_LL_CMP_WAIT_DATA_SEC_A_E:
		{
			/* The next state (FEE_LL_CMP_FINISHED_E) will be set by the Fee_JobEndNotification () or
			 * Fee_JobErrorNotification() function automatically (in both cases verify the compare result
			 * inside the next case) */

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

		/* Verify the data compare result and reset the state machine */
		case FEE_LL_CMP_FINISHED_E:
		{
			/* Verify the data compare result */
			if(Fee_GlobInfoWrBlock_st.CompareResult_u8 > 0)
			{
				/* The compare failed, return an error */
				xRetVal_en = FEE_ERROR_E;
			}
			else
			{
                /* Get the physical sector index of the compare address */
                xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xCmpAddress);

                /* Get the physical sector index of the write address */
                xPhyWrSectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

                /* The compare address is already incremented with the number of bytes from the previous compare order
                 * -> if the compare address is now behind the write address the block is not written completely! */
                if ((Fee_RdWrOrder_st.xCmpAddress > Fee_RdWrOrder_st.xWrAddress) &&
                    (xPhySectIdx_u8 == xPhyWrSectIdx_u8))
                {
                    /* Abort */
                    xRetVal_en = FEE_ERROR_E;
                }
                else
                {
                    /* Check if there are bytes within the next sector that have to be compared
                     * (the Fee_LLWriteBlock function calls the compare already if one sector is filled up
                     * and continues the programming afterwards. Nevertheless check this here.) */
                    if(Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 < HeaderInfo_pcst->BlkLength_u16)
                    {
                        /* Increment the logical sector index */
                        xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1);

                        /* Check if switching from last to first sector requires an overflow */
                        if(xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                        {
                            /* Abort, the block cannot continue in the logical sector 0 */
                            xRetVal_en = FEE_ERROR_E;
                        }
                        else
                        {
           					/* Before switching to next sector, check if sector is programmed with data. */
							if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
							   (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
							{
								/* Get the physical sector index */
								xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

								/* Set the new start address of the new sector */
								Fee_RdWrOrder_st.xCmpAddress   = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

								/* Set the next state to go on with the data compare */
								Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_DATA_SEC_A_E;
							}
							else
							{
								/* Abort, the block check as next sector is still not programmed with data. */
								xRetVal_en = FEE_ERROR_E;
							}
						}
                    }
                    else
                    {
                        /* Update the cache with the last header address */
                        Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16, HeaderInfo_pcst->AdrBlkHeader_u32);

                        /* All bytes have been compared without any difference, return success */
                        xRetVal_en = FEE_ORDER_FINISHED_E;
                    }
                }
			}
		}
		break;

		/* This state should never be reached */
		default:
		{
			/* Return an error */
			xRetVal_en = FEE_ABORTED_E;
		}
		break;
	}


    /* Check if a reset of the state machine is necessary */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset the state machine */
        Fee_RdWrOrder_st.Fee_LLCompBlk = FEE_LL_CMP_BLK_INIT_E;
    }

    return (xRetVal_en);
}


/**
 *********************************************************************
 * Fee_LLCopyPageBuff2Marker(): Extract the block header data
 *
 * This function extracts the block header data out of the page
 * buffer.
 *
 * Hint: Marker structure:
 *       {
 *          uint16  xPattern;
 *          uint8   xIdent;
 *          uint8   xContent[3];
 *          uint16  xChecksum;
 *       }Fee_MarkerProp_t;
 *
 * \param    Marker_pst:        Pointer to the block header that was
 *                                  found in the flash.
 * \param    PageBuf_pcu8:      Pointer to the page buffer
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLCopyPageBuff2Marker(P2VAR(Fee_MarkerProp_t, AUTOMATIC, FEE_APPL_DATA) Marker_pst,
                                               P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8)
{
    /* 0xCAFE <- [0]: CA, [1]: FE */
    Marker_pst->xPattern     = ((uint16)(((uint16)(PageBuf_pcu8[0])) << 8u) | (uint16)PageBuf_pcu8[1]);
    Marker_pst->xIdent       = PageBuf_pcu8[2];

    /* 0x02   <- [3]:  0, [4]:  0, [5]: 2 */
    Marker_pst->xContent[0]  = PageBuf_pcu8[3];
    Marker_pst->xContent[1]  = PageBuf_pcu8[4];
    Marker_pst->xContent[2]  = PageBuf_pcu8[5];

    /* 0xFA33 <- [6]: FA, [7]: 33 */
    Marker_pst->xChecksum    = ((uint16)(((uint16)(PageBuf_pcu8[6])) << 8u) | (uint16)PageBuf_pcu8[7]);

}


/**
 *********************************************************************
 * Fee_LLPrepMarkerBufWithMarkerData(): Prepare the marker buffer with
 *                                      block the header data
 *
 * This function prepares the marker buffer with the marker data
 * for writing this data to the flash. This is done to ensure the
 * same data interpretation within the complete Fee driver.
 *
 * Hint: Marker structure:
 *       {
 *          uint16  xPattern;
 *          uint8   xIdent;
 *          uint8   xContent[3];
 *          uint16  xChecksum;
 *       }
 *
 * \param    Marker_pcst:  Pointer to the marker structure
 * \param    Data_pu8:     Pointer to the marker buffer that will
 *                         be used to write the data into the flash
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLPrepMarkerBufWithMarkerData(P2CONST(Fee_MarkerProp_t, AUTOMATIC, FEE_APPL_DATA) Marker_pcst,
                                                       P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) MarkerBuf_pu8)
{
    /* 0xCAFE <- [0]: CA, [1]: FE */
    MarkerBuf_pu8[0] = (uint8)(Marker_pcst->xPattern >> 8u);
    MarkerBuf_pu8[1] = (uint8)Marker_pcst->xPattern;

    MarkerBuf_pu8[2] = Marker_pcst->xIdent;

    /* 0x02 <- [0]: 0, [1]: 0, [2]: 2 */
    MarkerBuf_pu8[3] = Marker_pcst->xContent[0];
    MarkerBuf_pu8[4] = Marker_pcst->xContent[1];
    MarkerBuf_pu8[5] = Marker_pcst->xContent[2];

    /* 0xABCD <- [0]: AB, [1]: CD */
    MarkerBuf_pu8[6] = (uint8)(Marker_pcst->xChecksum >> 8u);
    MarkerBuf_pu8[7] = (uint8)Marker_pcst->xChecksum;
}


/**
 *********************************************************************
 * Fee_LLCopyPageBuff2HeaderMid(): Extract the rest up to the CRC 32
 *                                 of the block header data
 *
 * This function extracts block status, the Fee index and length from
 * the block header data out of the page buffer.
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    BlkHdr_pst:    Pointer to the block header that was
 *                          found in the flash.
 * \param    PageBuf_pcu8:  Pointer to the page buffer
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLCopyPageBuff2HeaderMid(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                  P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8)
{
    BlkHdr_pst->BlkStatus_u8    = PageBuf_pcu8[3];

    /* 0xD2E9 <- [4]: D2, [5]: E9 */
    BlkHdr_pst->FeeIndex_u16    = ((uint16)(((uint16)(PageBuf_pcu8[4])) << 8u)  | (uint16)(PageBuf_pcu8[5]));

    /* 0x0008 <- [6]: 00, [7]: 08 */
    BlkHdr_pst->BlkLength_u16   = ((uint16)(((uint16)(PageBuf_pcu8[6])) << 8u)  | (uint16)(PageBuf_pcu8[7]));

    /* 0xABCD <- [8]: AB, [9]: CD */
    BlkHdr_pst->HdrCrc16_u16    = ((uint16)(((uint16)(PageBuf_pcu8[8])) << 8u)  | (uint16)(PageBuf_pcu8[9]));
}


/**
 *********************************************************************
 * Fee_LLCopyPageBuff2HeaderEnd(): Extract the CRC 32 out
 *                                 of the block header data
 *
 * This function extracts CRC32 out of the block header data.
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    BlkHdr_pst:    Pointer to the block header that was
 *                          found in the flash.
 * \param    PageBuf_pcu8:  Pointer to the page buffer
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLCopyPageBuff2HeaderEnd(P2VAR(Fee_BlkHeader_tst, AUTOMATIC, FEE_APPL_DATA) BlkHdr_pst,
                                                  P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) PageBuf_pcu8)
{
    BlkHdr_pst->BlkCrc32_u32    = (uint32)((((uint32)(PageBuf_pcu8[10])) << 24u) |
                                           (((uint32)(PageBuf_pcu8[11])) << 16u) |
                                           (((uint32)(PageBuf_pcu8[12])) << 8u)  |
                                           (((uint32)(PageBuf_pcu8[13]))));
}


/**
 *********************************************************************
 * Fee_LLPrepPageBufWithHdrData(): Prepare the page buffer with block
 *                                 header data
 *
 * This function prepares the page buffer with block header data
 * for writing this data to the flash.
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    HeaderInfo_pst:   Pointer to the block header structure
 *                             that needs to be written into the flash
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLPrepPageBufWithHdrDataStart(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pst)
{
    VAR(uint16, AUTOMATIC) xPageCrc_u16 = 0;

    /* Reset the already considered bytes */
    Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 = 0;

    /* 0xA53C96 -> [0]: A5, [1]: 3C, [2]: 96 */
    Fee_PageBytePtr_cpu8[0] = (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_0;
    Fee_PageBytePtr_cpu8[1] = (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_1;
    Fee_PageBytePtr_cpu8[2] = (uint8)FEE_BLK_HEADER_PREAMBEL_BYTE_2;

    Fee_PageBytePtr_cpu8[3] = HeaderInfo_pst->BlkStatus_u8;

    /* MSByte: 0xD2E9 -> D2 */
    Fee_PageBytePtr_cpu8[4] = (uint8)(HeaderInfo_pst->FeeIndex_u16 >> 8u);
    /* LSByte:        -> E9*/
    Fee_PageBytePtr_cpu8[5] = (uint8)((HeaderInfo_pst->FeeIndex_u16) & 0xFFu);

    /* MSByte: 0x08   -> 00 */
    Fee_PageBytePtr_cpu8[6] = (uint8)(HeaderInfo_pst->BlkLength_u16 >> 8u);
    /* LSByte:        -> 08 */
    Fee_PageBytePtr_cpu8[7] = (uint8)((HeaderInfo_pst->BlkLength_u16) & 0xFFu);

    /* Calculate the CRC over an 8 byte data array */
    xPageCrc_u16 = Crc_CalculateCRC16((uint8*)&Fee_PageBytePtr_cpu8[0],
                                          (uint32)(FEE_BLK_HEADER_SIZE-6u),
                                          (uint16)FEE_MARKER_PATTERN,
                                           FALSE);

    Fee_PageBytePtr_cpu8[8] = (uint8)(xPageCrc_u16 >> 8u);
    Fee_PageBytePtr_cpu8[9] = (uint8)(xPageCrc_u16  & 0xFFu);

    /* Save the header Crc (this is necessary for calculating the block checksum in case no
     * block has been found so far) */
    HeaderInfo_pst->HdrCrc16_u16 = xPageCrc_u16;
}


/**
 *********************************************************************
 * Fee_LLPrepPageBufWithHdrDataEnd(): Prepare the page buffer with block
 *                                    header data
 *
 * This function prepares the page buffer with block header data
 * for writing this data to the flash.
 *
 * Hint: Block header structure:
 *       {
 *          uint8   Preamble_au8[3];
 *          uint8   BlkStatus_u8;
 *          uint16  FeeIndex_u16;
 *          uint16  BlkLength_u16;
 *          uint16  HdrCrc16_u16;
 *          uint32  BlkCrc32_u32;
 *       }Fee_BlkHeader_tst;
 *
 * \param    HeaderInfo_pst:   Pointer to the block header structure
 *                             that needs to be written into the flash
 * \param    Data_pcu8:        Pointer to the user data
 * \param    BlkCrc32_u32:     Block checksum
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(void, FEE_CODE) Fee_LLPrepPageBufWithHdrDataEnd(P2VAR(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pst,
                                                  	 P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Data_pcu8,
                                                  	 VAR(uint32, AUTOMATIC) BlkCrc32_u32)
{
    VAR(uint16, AUTOMATIC) xNumBytes_u16 = 0;
    VAR(uint16, AUTOMATIC) i = 0;

    /* Reset the already considered bytes */
    Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 = 0;

    /* Add the block CRC to the page buffer */
    Fee_PageBytePtr_cpu8[10] = (uint8) (BlkCrc32_u32 >> 24u);
    Fee_PageBytePtr_cpu8[11] = (uint8) (BlkCrc32_u32 >> 16u);
    Fee_PageBytePtr_cpu8[12] = (uint8) (BlkCrc32_u32 >> 8u);
    Fee_PageBytePtr_cpu8[13] = (uint8)  BlkCrc32_u32; // Would be a shift by 0

    /* Save the block CRC for the verification after writing */
    HeaderInfo_pst->BlkCrc32_u32 = BlkCrc32_u32;

    /* Depending on the page size the header needs more than 1 page and there might be free space for
     * data behind the header
     * --> copy also data */
    if((HeaderInfo_pst->BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) > 0)
    {
        /* Reset the data length to the number of free bytes after the header data
         * within the same page (length != 0 for filling up the rest of the page
         * with a defined value) */
        xNumBytes_u16 = FEE_FREE_BYTES_AFTER_HEADER;
    }
    else
    {
        /* Set the block length for filling up the header pages */
        xNumBytes_u16 = HeaderInfo_pst->BlkLength_u16;
    }

    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    /* Check for an activated block robustness feature */
    if((((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                                          (uint16)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint16)FEE_FLAG_ROBUST_ATTR_BP) > 0) &&
        ((HeaderInfo_pst->BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) == 0))
    {
        /* Set the block length for filling up the header pages */
        xNumBytes_u16 -= FEE_SIZE_OF_BLOCK_CS;
    }
    #endif

    if(xNumBytes_u16 > FEE_FREE_BYTES_AFTER_HEADER)
    {
        /* Restrict the number of bytes */
        xNumBytes_u16 = FEE_FREE_BYTES_AFTER_HEADER;
    }

    /* Copy the number of data bytes behind the block header until the last page of the
     * block header is filled up */
    for(i=0; i<xNumBytes_u16; i++)
    {
        /* Differ between invalidation and other orders */
        if((HeaderInfo_pst->BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) > 0)
        {
            /* Copy the erase pattern only */
            Fee_PageBytePtr_cpu8[FEE_BLK_HEADER_SIZE+i] = 0;
        }
        else
        {
            /* Copy the data bytes to the buffer which is used for writing the header */
            Fee_PageBytePtr_cpu8[FEE_BLK_HEADER_SIZE+i] = Data_pcu8[i];

            /* Increment amount of data that has already been considered for writing
             * (only for Non - invalidation orders because block length was overwritten
             * with zero otherwise) */
            Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16++;
        }
    }

    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    /* Check if the robustness checksum start value must be calculated */
    if(((Fee_BlockProperties_st[Fee_OrderFifo_st[Fee_idxActQueue_u8].BlockPropIdx_u16].Flags_u16 &
                                            (uint16)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint16)FEE_FLAG_ROBUST_ATTR_BP) > 0)
    {
        /* Save the start value for the robustness checksum
         * Hint: Only the data bytes within the header are regarded to far.
         *       The robustness checksum is calculated in small pieces using an internal
         *       buffer. The calculation can be done at any time as soon as the user data
         *       has been transfered. */
        Fee_DataByteStartCrc_u32 = Crc_CalculateCRC32(&Fee_PageBytePtr_cpu8[FEE_BLK_HEADER_SIZE],
                                                      (uint32)xNumBytes_u16,
                                                      (((uint32)HeaderInfo_pst->HdrCrc16_u16) ^ FEE_MAXUINT32),
                                                      FALSE);
    }
    #endif
}


/**
 *********************************************************************
 * Fee_LLCopyData2Buffer(): Read out the block data
 *
 * This function copies the block data without the header information
 * to a buffer given by the user. Offset and length are considered.
 * Offsets != zero are not supported.
 *
 * \param    Fee_GlobInfoLastRdHeader_pcst: Pointer to the latest valid
 *                                  block header content of the block
 *                                  to read
 * \param    DataPtr_pu8:           Pointer to store the requested data
 * \param    DataOffset_u16:        Data offset within the block
 * \param    DataLength_u16:        Data length
 *
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  Fls function call or a busy Fls
 * \retval   FEE_ERROR_E:           A read or write error occured
 * \retval   FEE_ORDER_FINISHED_E:  The block was copied successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCopyData2Buffer(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_pcst,
                                                       P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataPtr_pu8,
                                                       VAR(uint16, FEE_VAR) DataOffset_u16,
                                                       VAR(uint16, FEE_VAR) DataLength_u16)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;     /* Function return */
    VAR(uint32, FEE_VAR) xNumBytesToSectEnd_u32 = 0;        /* Amount of bytes to the end of the sector */
    VAR(uint16, FEE_VAR) xNumBytesOfsConsid_u16 = 0;        /* Amount of bytes that are not relevant */
    VAR(uint8, FEE_VAR)  xLogSectIdx_u8         = 0;        /* Logical sector index */
    VAR(uint8, FEE_VAR)  xCntSect_u8            = 1;        /* Sector counter */
    VAR(uint8, FEE_VAR)  xPhySectIdx_u8         = 0;        /* Physical sector index */
    VAR(boolean, FEE_VAR) xStartAdrFound_b      = FALSE;    /* Indicator for exiting the search loop */


	/* Switch over state machine */
	switch (Fee_RdWrOrder_st.Fee_LLCopyBlk_en)
	{
		/* Init state */
		case FEE_LL_CPY_BLK_INIT_E:
		{
			/* Reset the amount of bytes that have already been considered for the transfer */
			Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 = 0;

			/* Identify the sector with the first relevant user data to copy and the amount of
			 * bytes that have to be copied in the first run */

			/* Set the data start address with offset = 0 */
			Fee_RdWrOrder_st.xRdAddress = (uint32)(Fee_GlobInfoLastRdHeader_pcst->AdrBlkHeader_u32 +
												  (uint32)FEE_BLK_HEADER_SIZE);

			/* Get the current physical sector index */
			xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

			/* Get the corresponding logical sector index */
			xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8]);

			/* Consider the offset for the header sector */
			if((uint32)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
					Fee_RdWrOrder_st.xRdAddress) <= DataOffset_u16)
			{
				/* The start address for the read is not within the header sector
				 * --> check any following sectors */
				do
				{
					/* Calculate the amount of bytes that are not necessary inside the previous sector */
					xNumBytesOfsConsid_u16 += (uint16)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
							Fee_RdWrOrder_st.xRdAddress);

					/* Increment the logical sector */
					xLogSectIdx_u8++;

					/* Sector overflow not necessary because the checksum verification was done before.
					 * This would have failed in case s.th. was wrong with the sector order. */

					/* Get the new physical sector index */
					xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

					/* Increment the amount of checked sectors */
					xCntSect_u8++;

					/* Check if the data start address is within the next sector */
					if((((uint32)(Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
								  Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32)) >
						 (uint32)(DataOffset_u16 - xNumBytesOfsConsid_u16))
					{
						/* The start address was found within this sector */

						/* Set the read start address */
						Fee_RdWrOrder_st.xRdAddress = (uint32)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32 +
															   DataOffset_u16) -
															   xNumBytesOfsConsid_u16);

						/* End loop */
						xStartAdrFound_b = TRUE;
					}
					else
					{
						/* The start address is still not found because of the offset */

						/* Reset read address to the current sector for next run */
						Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

					}
				}
				while((xStartAdrFound_b == FALSE) ||
					  (xCntSect_u8 >= FEE_NUM_FLASH_BANKS));
			}
			else
			{
				/* The start address is within the header sector */
				/* The offset can be added without causing an sector overflow */
				Fee_RdWrOrder_st.xRdAddress += DataOffset_u16;
			}

			/* Calculate amount of bytes to the sector end for first read out */
			xNumBytesToSectEnd_u32 = (uint32)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
					Fee_RdWrOrder_st.xRdAddress);

			/* Check if the amount of bytes to read needs to be restricted (sector overflow) */
			if(xNumBytesToSectEnd_u32 < DataLength_u16)
			{
				/* Restrict the amount of bytes to read */
				Fee_GlobInfoWrBlock_st.Bytes2Read_u16 = (uint16)xNumBytesToSectEnd_u32;
			}
			else
			{
				/* The complete data can be read out in one step */
				Fee_GlobInfoWrBlock_st.Bytes2Read_u16 = DataLength_u16;
			}

			/* Set the state */
			Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLOCK_START_E;
		}
		/* No break to save time */

		/* Read out the data */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_CPY_BLOCK_START_E:
		{
			#if (FEE_PRV_DEBUGGING != FALSE)
			Fee_Prv_stModuleTest_st.Fee_DataReadStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);

			Fee_Prv_stModuleTest_st.Fee_DataReadNumBytes_u32 += Fee_GlobInfoWrBlock_st.Bytes2Read_u16;
			#endif

			/* Call the Fls interface */
			if(Fls_Read(Fee_RdWrOrder_st.xRdAddress,
						&DataPtr_pu8[Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16],
						Fee_GlobInfoWrBlock_st.Bytes2Read_u16) != E_NOT_OK)
			{
				/* Read order was accepted, set the next state */
				Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLOCK_WAIT_E;

				/* Increment the amount of already considered data bytes */
				Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 = (uint16)((Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 +
																		Fee_GlobInfoWrBlock_st.Bytes2Read_u16));

				/* Increment the read address for the next Fls access (overflow is checked automatically) */
				Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xRdAddress, Fee_GlobInfoWrBlock_st.Bytes2Read_u16, TRUE);
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
		case FEE_LL_CPY_BLOCK_WAIT_E:
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

		/* Wait for the read order to be finished */
		case FEE_LL_CPY_BLOCK_ERROR_E:
		{
			/* Verify retry possibility */
			if(Fee_RdWrRetries_u8 > 0)
			{
				/* Decrement retry possibilities */
				Fee_RdWrRetries_u8--;

				/* Restart the state machine in order to start all over again */
				Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLK_INIT_E;
			}
			else
			{
				/* Return error, because maximum amount of retries is reached */
				xRetVal_en = FEE_ERROR_E;
			}
		}
		break;

		/* Finish the function or the data transfer */
		case FEE_LL_CPY_BLOCK_FINISHED_E:
		{
			#if (FEE_PRV_DEBUGGING != FALSE)
			Fee_Prv_stModuleTest_st.Fee_DataReadEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

			Fee_Prv_stModuleTest_st.Fee_DataReadDiff_u32 = MCU_RB_TIM0TICKS_TO_MS(
					Fee_Prv_stModuleTest_st.Fee_DataReadEnd_u32 -
					Fee_Prv_stModuleTest_st.Fee_DataReadStart_u32);
			#endif

			/* Check if the data transfer is complete */
			if(Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16 == DataLength_u16)
			{
				/* All data was read  out */
				xRetVal_en = FEE_ORDER_FINISHED_E;
			}
			else
			{
				/* There are still some data bytes left to be transfered
				 * --> switch to the next logical sector and read out more data */

				/* Get the current physical sector index */
				xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xRdAddress);

				/* Get the corresponding logical sector index and increment it */
				xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1u);

				/* Sector overflow not necessary because the checksum verification was done before.
				 * This would have failed in case s.th. was wrong with the sector order. */

				/* Get the new physical sector index */
				xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

				/* Set the start address for the read command (it will always be sector aligned
				 * because read orders can be performed until the end of the sector) */
				Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

				/* Check if the amount of bytes to read needs to be restricted (sector overflow) */
				if((uint16)(DataLength_u16 - Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16) >=
				   (uint32)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
							 Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32))
				{
					/* Read back one complete sector first */
					Fee_GlobInfoWrBlock_st.Bytes2Read_u16 = (uint16)((Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32 + 1u) -
																	  Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32);
				}
				else
				{
					/* Read back the complete rest of the data */
					Fee_GlobInfoWrBlock_st.Bytes2Read_u16 = (uint16)(DataLength_u16 -
																	 Fee_GlobInfoWrBlock_st.BytesAlrdyConsid_u16);
				}

				/* Restart the data transfer */
				Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLOCK_START_E;
			}
		}
		break;

		default:
			/* Return error */
			xRetVal_en = FEE_ERROR_E;
		break;
	}


    /* Check if the function is finished */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset the state machine */
        Fee_RdWrOrder_st.Fee_LLCopyBlk_en = FEE_LL_CPY_BLK_INIT_E;
        /* Retries for write/read and verify after failed compare */
        Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;
    }

    return (xRetVal_en);
}


/**
 *********************************************************************
 * Fee_LLCpyBlkFromFls2Fls(): Copy a block during the sector reorg
 *
 * This function copies a block during the sector reorganization
 * from one sector to another one.
 *
 * \param    Fee_GlobInfoLastRdHeader_pcst:  Pointer to the latest valid
 *                                  block header content of the block
 *                                  to copy
 *			 Fee_WriteTwice_b: For redundant blocks, if both copies must be written or only copy.
 *							  TRUE -> Both copies to be written
 *							  FALSE -> Only copy to be written (to avoid complex handling of invalidation for No fall back blocks)
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         A "sector overflow" occured, the
 *                                  USED sector was erased
 * \retval   FEE_ERROR_E:           A read, write or compare error occured or
 *                                  the order was aborted due to a
 *                                  wrong function call or a busy Fls
 * \retval   FEE_ORDER_FINISHED_E:  The block was copied successfully
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCpyBlkFromFls2Fls(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) Fee_GlobInfoLastRdHeader_pcst, boolean Fee_WriteTwice_b)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(uint8, AUTOMATIC) xPhySectIdx_u8;                           	/* Physical sector index */
    VAR(uint8, AUTOMATIC) xLogSectIdx_u8;	                            /* Logical sector index */
    VAR(uint32, AUTOMATIC) xNumBytes_u32;                       	    /* Calculated number of bytes (different usage) */
    static uint32 xHeaderAddr_u32 = FEE_MAXUINT32;                      /* Block header address */
    static boolean xSectOverflow_b = FALSE;                             /* Sector overflow indicator */
    VAR(Fee_stRetVal_ten, AUTOMATIC) xWrMarkerRetVal_en;                /* Return value for writing markers */
    VAR(uint16, AUTOMATIC) xCnt_u16;                                	/* Block and sector number counter */
    static uint8 xCntRetry_u8 = FEE_MAX_RD_WR_COMP_RETRIES;             /* Retries for write/read and verify after failed compare */
    VAR(uint16, AUTOMATIC) xConfigPropTableIdx_u16;                     /* Configuration properties table index */
	VAR (Fee_stRetVal_ten, AUTOMATIC) xRetValErase_en;
	static uint32 cntProgrammedBytes_u32;
	uint32 tmpAddr_u32;
	uint8* tmpAdd_pu8;

    /* Switch over state machine */
    switch (Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en)
    {
        /* Init state */
        case FEE_LL_CPY_FLS2FLS_INIT_E:
        {
            /* Reset amount of already copied bytes */
            Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 = 0;

            /* Copy the block header address */
            Fee_LLSecReorgStruct_st.xRdAddress_u32 = Fee_GlobInfoLastRdHeader_pcst->AdrBlkHeader_u32;

            /* Reset the sector overflow indicator */
            xSectOverflow_b = FALSE;

			cntProgrammedBytes_u32 = 0;

            /* Set the next state (could be changed in case of a NoFallback block) */
            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en  = FEE_LL_CPY_FLS2FLS_READ_E;

            /* Get the sector index of the write sector */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);
            xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8]);

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            /* Initalise the address for 2nd header page and the flag to indicate that first data pages is not yet programmed. */
            Fee_RdWrOrder_st.xHdPg2Address = FEE_NULL;
			Fee_LLSecReorgStruct_st.xFirstDataPgPgm_u8 = FEE_FIRSTDATAPAGE_NOTPROGRAMMED;
#endif

            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            /* Check if the block has a NoFallback configuration
             * -> independent of the actual layout */
            if ((Fee_GlobInfoLastRdHeader_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_NOFALLBACK_MSK) > 0)
            {
                /* 1. Step:
                 * Check if the NoFallback marker and the block header fits into the current logical sector */

                /* Calculate number of bytes necessary to store the block header only */
                xNumBytes_u32 = FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN;

                /* Check if the sector is already filled up */
                if ((((Fee_RdWrOrder_st.xWrAddress + FEE_PAGE_LEN + xNumBytes_u32) - 1u) > Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32) &&
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
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_FILL_SECTOR_END_E;
                    }
                    else
                    {
                        /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                        xRetVal_en = FEE_ABORTED_E;
                    }

                    /* Do not continue this state due to an error of Fls or to fill up the sector end */
                    break;
                }

                /* 2. Step:
                 * In case the function is called for block maintenance during shutdown or a write order possibly
                 * existing copies needs to be invalidated (only for double storage blocks).
                 * This is only necessary in 2 cases:
                 *      1. The second copy of an old version is available
                 *          -> This is the case if the write of a new version gets interrupted
                 *      2. After copying the only existing version */
                // the security level bit has the offset 0 --> No shift required
                if ((Fee_Rb_MaintainRun_b != FALSE) &&
                    ((Fee_GlobInfoLastRdHeader_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_SEC_LEVEL_MSK) == FEE_BLK_INT_DOUBLE_STORAGE))
                {
                    if ((Fee_Rb_InvalidateOldCopy_b != FALSE) || (Fee_LLSecReorgStruct_st.xCntCopies_u8 > 0))
                    {
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en  = FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_E;
                    }
                }
            }
            /* #if (FEE_NO_FALLBACK_ACTIVE != FALSE) */
            #endif


            if((Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING) < (FEE_PAGES_USED_BY_BLK_HEADER * FEE_PAGE_LEN)) ||
               (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en != FEE_SECTOR_USED_E))
            {
                /* Get the sector index of the sector that will be used for writing
                 * the block header
                 * --> this address will be used to update the cache
                 *
                 * Currently possible sector states are:
                 * - USED (with not enough space left)
                 * - ERASED/REQ2ERASE
                 * - UNDEF
                 * - FULL */

                /* Verify the sector state in case the FULL marker has not been written yet
                 * (for e.g. due to resets or in case the sector overlap is caused by the
                 *  sector reorganization itself) */
                if(Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en != FEE_SECTOR_FULL_E)
                {
                    /* Write the FULL marker next */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E;
                }
                else
                {
                    /* Go on in the next sector */
                    xLogSectIdx_u8++;

                    /* Check if switching from last to first sector requires an overflow */
                    if(xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                    {
                        /* Error case: all sectors are full (this assumption is guaranteed by the logical
                         *             sector order mechanism)
                         * --> erase the most current sector in order to get the chance to keep data
                         *     that is never written (which will be located in the oldest FULL sector). */

                        /* Reset the logical sector index */
                        xLogSectIdx_u8 = FEE_NUM_FLASH_BANKS - 1u;

                        /* Get the new physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Physical sector index and write address are still OK, mark the sector to be erased */
                        Fee_LLSetEraseSector(xLogSectIdx_u8);

                        /* Set the sector overflow indicator
                         * (--> restart the reorganization after the USED marker has been written) */
                        xSectOverflow_b = TRUE;

                        /* Set erase state */
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E;
                    }
                    else
                    {
                        /* It is possible that this logical sector is not erased yet!
                         * In this case, the sector has to be erased first
                         * Hint: it is actually not possible that the next sector after an active FULL sector
                         *       is in the FULL state (error case)
                         *       --> erase the most current FULL sector
                         *
                         * Currently possible sector states are:
						 * - ERASED/REQ2ERASE
						 * - UNDEF */

                        /* Get the new physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Verify the sector state */
                        if(Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_ERASED_E)
                        {
                            /* The new logical sector is already erased */

                            /* Write the used marker */
                            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_USED_MARKER_E;
                        }
                        else
                        {
                            /* The new logical sector has to be erased first
                             * Possible sector states:
                             * - REQ2ERASE
                             * - UNDEF */

                            /* Mark the sector to be erased */
                            Fee_LLSetEraseSector(xLogSectIdx_u8);

                            /* Set erase state */
                            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E;
                        }
                    }

                    /* Set the address for writing the next block */
                    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;
                }
            }
        }
        break;

        #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        case FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_E:
        {
            if ((Fee_Rb_InvalidateOldCopy_b != FALSE) && (Fee_LLSecReorgStruct_st.xCntCopies_u8 == 0))
            {
                /* Invalidate the old copy first */
                tmpAddr_u32 = Fee_GlobInfoLastRdHeader_st.AdrBlkHeader_u32;
            }
            else
            {
                /* There is only one existing copy or the old copy is already invalidated */
                tmpAddr_u32 = Fee_GlobInfoLastRdHeader_pcst->AdrBlkHeader_u32;
            }

            /* Decrement the address for the NoFallback marker in front of the block */
            tmpAddr_u32 -= FEE_PAGE_LEN;

            /* Write the NoFallback marker to invalidate the old copy before writing any new copy */
            if (Fls_Write(tmpAddr_u32, Fee_NoFallbackMarkerPattern, FEE_PAGE_LEN) != E_NOT_OK)
            {
                /* Wait for the over programming to finish */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_WRITE_NOFB_MARKER_E;
            }
            else
            {
                /* Return an error due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }
        }
        break;
        #endif

        /* Read out the complete block (header and data) and finish the function if possible */
        case FEE_LL_CPY_FLS2FLS_READ_E:
        {
            /* Check if reading of data is necessary */
            if(Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 < (Fee_GlobInfoLastRdHeader_pcst->BlkLength_u16 +
                                                                   (uint16)FEE_BLK_HEADER_SIZE))
            {
                /* There are still bytes left to be read out */
                Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 = (uint16)((Fee_GlobInfoLastRdHeader_pcst->BlkLength_u16 +
                                                                            (uint16)FEE_BLK_HEADER_SIZE) -
                                                                            Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16);

                /* Ensure the correct alignment */
                /* MR12 RULE 14.2 VIOLATION: The variable is updated and used within the same function itself. */
                while((Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 % FEE_PAGE_LEN) != 0u)
                {
                    Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16++;
                }

                /* Note: The following combinations for the read and write data are possible:
                 *       - The block is greater than the page buffer and must be written in several steps
                 *       - The target sector has not enough space to store the complete block
                 *          -> data cannot be written in one step
                 *       - Original block is stored in the logical sector[0] and [1]
                 *          -> source data cannot be read in one step */

                /* Check if the block size is bigger than the page buffer size */
                if(Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 > FEE_LL_PAGEBUFFSIZE)
                {
                    /* Restrict the bytes to read (it will take several steps to read out this block) */
                    Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 = FEE_LL_PAGEBUFFSIZE;
                }

                /* Check if there are enough free bytes in the target sector for this block */
                xNumBytes_u32 = Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_WRITING);

                #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
                /* In case of a NoFallback block and only before writing the block header
                 * -> restrict the number of free bytes in the target sector due to the NoFallback marker
                 * -> the write address gets incremented right before writing the block header */
                if ((Fee_GlobInfoLastRdHeader_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_NOFALLBACK_MSK) > 0)
                {
                    /* Ensure that at least 1 Page is available in the target sector */
                    if ((Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 == 0) &&
                        (xNumBytes_u32 != 0uL))
                    {
                        xNumBytes_u32 -= FEE_PAGE_LEN;
                    }
                }
                #endif

                if(Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 > xNumBytes_u32)
                {
                    /* Restrict the number of bytes to read/write (it will take several steps) */
                    Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 = (uint16)xNumBytes_u32;
                }

                /* Check if the target sector is already full */
                if(xNumBytes_u32 == 0uL)
                {
                    /* Write the FULL_MARKER and the USED MARKER first */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E;
                }
                else
                {
                    /* There is at least some space left in the target sector */

                    /* Check the number of bytes until the sector end in the read sector is reached */
                    xNumBytes_u32 = Fee_CalculateNumOfFreeBytesInCurSector(Fee_LLSecReorgStruct_st.xRdAddress_u32);

                    if(Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 > xNumBytes_u32)
                    {
                        /* Restrict the amount of bytes to read
                         * --> Amount of bytes == Amount of bytes to write */
                        Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 = (uint16)xNumBytes_u32;
                    }

                    /* Read out the data (or part of it, or the header) */
                    if(Fls_Read(Fee_LLSecReorgStruct_st.xRdAddress_u32,
                                (uint8*)&Fee_PageBytePtr_cpu8[0],
                                Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16) != E_NOT_OK)
                    {
                        /* Set the next state to wait for the read order to be finished */
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_READ_E;

                        /* Increment amount of bytes that have already been considered */
                        Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 = (uint16)(Fee_LLSecReorgStruct_st.xNumBytesAlrdyCopied_u16 +
                                                                                    Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16);

                        /* Increment the read address for the next Fls_Read call */
                        Fee_IncAddressInsideSector(&Fee_LLSecReorgStruct_st.xRdAddress_u32,
                                                   Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16,
                                                   TRUE);
                    }
                    else
                    {
                        /* Fls did not accept the order due to wrong parameters or an internal busy state.
                         * Invalidate the cache entry */
                        Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                                   FEE_CACHE_TMP_INVALID_VALUE);

                        /* Reset the state machine (and the upper one) */
                        xRetVal_en = FEE_ABORTED_E;
                    }
                }
            }
            else
            {

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
                /* Check if 2nd header page is programmed. xHdPg2Address is set to FEE_MAXUINT32 after the header page 2 programming is initiated. */
	            if(Fee_RdWrOrder_st.xHdPg2Address != FEE_MAXUINT32)
                {
                    /* 2nd header page is yet to be programmed. */
                    /* Switch to state to program the 2nd header page. */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_E;
				}
                else
#endif
				{
				    /* Check if a second copy needs to be transfered (take the info out
                     * of the PFlash, not the DFlash if possible) */

                    /* Check if the index can be found */
                    if(Fee_SrvBinarySearchInBlockProp(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16, &xConfigPropTableIdx_u16) != FALSE)
                    {
                        /* Take the info out of the config */
                        // the security level bit has the offset 0 --> No shift required
                        if(((Fee_BlockProperties_st[xConfigPropTableIdx_u16].Flags_u16 &
                                                        FEE_FLAG_SEC_LEVEL_MSK) ==
                                                            FEE_BLK_INT_DOUBLE_STORAGE) &&
                             (Fee_LLSecReorgStruct_st.xCntCopies_u8 == 0) && (TRUE == Fee_WriteTwice_b))
                        {
                            /* Write the same data a second time (1st valid copy of the block will be copied twice) */
                            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E;
                            Fee_LLSecReorgStruct_st.xCntCopies_u8++;
                        }
                        else
                        {
                            /* Function is finished */
                            xRetVal_en = FEE_ORDER_FINISHED_E;
                        }
                    }
                    else
                    {
                        /* In case the "afterburner" is running, the available info for unknown blocks is only
                         * available inside the DFlash */
                        if(((Fee_GlobInfoLastRdHeader_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_SEC_LEVEL_MSK) ==
                                FEE_BLK_INT_DOUBLE_STORAGE) &&
                             (Fee_LLSecReorgStruct_st.xCntCopies_u8 == 0) && (TRUE == Fee_WriteTwice_b))
                        {
                            /* Write the same data a second time (1st valid copy of the block will be copied twice) */
                            Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E;
                            Fee_LLSecReorgStruct_st.xCntCopies_u8++;
                        }
                        else
                        {
                            /* Function is finished */
                            xRetVal_en = FEE_ORDER_FINISHED_E;
                        }
                    }

                    /* At least one copy was transfered correctly, update the cache with the current header address */
                    Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                               xHeaderAddr_u32);
                }
            }
        }
        break;

#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        /* Wait for the invalidation or filling up the sector to be finished */
        case FEE_LL_CPY_FLS2FLS_WAIT_FILL_SECTOR_END_E:
        case FEE_LL_CPY_FLS2FLS_WAIT_WRITE_NOFB_MARKER_E:
#endif
        /* Wait for the read order to be finished */
        case FEE_LL_CPY_FLS2FLS_WAIT_READ_E:
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Wait for the write order to be finished */
        case FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_WRITE_E:
        case FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_WRITE_E:
#endif
        case FEE_LL_CPY_FLS2FLS_WAIT_WRITE_E:
        /* Wait for the verification to finish */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        case FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_VERIFY_E:
        case FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_VERIFY_E:
#endif

        case FEE_LL_CPY_FLS2FLS_WAIT_VERIFY_E:
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

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Write the header page 1 into the new sector */
        case FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_E:
        {
            #if (FEE_NO_FALLBACK_ACTIVE != FALSE)
            /* Check if the block has a NoFallback configuration */
            if ((Fee_GlobInfoLastRdHeader_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_NOFALLBACK_MSK) > 0)
            {
                /* Increment the write address with the size of the NoFallback marker */
                Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress, FEE_PAGE_LEN, TRUE);
            }
            #endif

            /* The data was read, write the header page 1 into the new sector */
            if (Fls_Write(Fee_RdWrOrder_st.xWrAddress,
                          (uint8*)&Fee_PageBytePtr_cpu8[0],
                          FEE_PAGE_LEN) != E_NOT_OK)
            {
                /* Save the header address for the cache update */
                xHeaderAddr_u32 = Fee_RdWrOrder_st.xWrAddress;

                /* Store the address where the header page 2 must be programmed. */
                Fee_RdWrOrder_st.xHdPg2Address = Fee_RdWrOrder_st.xWrAddress + FEE_PAGE_LEN;

                /* Copy the header page 2 contents into a buffer. */
                Fee_SrvMemCopy8(Fee_hdr2Buffer_au8, (Fee_PageBytePtr_cpu8 + FEE_PAGE_LEN), FEE_PAGE_LEN);

                /* Reduce the number of bytes to be programmed if there is data also to be programmed. */
                Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16 -= FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER;

                /* Even though only one header page is programmed, count that both header pages are programmed.
				 * The 2nd header page is left blank and will be programmed after all data pages are written. */
				cntProgrammedBytes_u32 += FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER;

                /* Set the next state in order to wait until the write order is finished */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_WRITE_E;

                /* Prepare the compare address */
                Fee_RdWrOrder_st.xCmpAddress = Fee_RdWrOrder_st.xWrAddress;

                /* Next, data pages will be written. Increment the write address to point to data page. */
                Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress,
                                           (FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER),
                                           TRUE);
            }
            else
            {
                /* Fls did not accept the order due to wrong parameters or an internal busy state.
                 * Invalidate the cache entry */
                Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                           FEE_CACHE_TMP_INVALID_VALUE);

                /* Reset the state machine (and the upper one) */
                xRetVal_en = FEE_ABORTED_E;
            }
        }
        break;
#endif

        /* Write the data into the new sector */
        case FEE_LL_CPY_FLS2FLS_WRITE_E:
        {
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            /* The data was read from old sector, now write it into the new sector. */
            /* Check if the buffer contains header information. This is indicated:
			 * 1. If so far only header was programmed (indicated by cntProgrammedBytes_u32) and
			 * 2. This was a first read of the buffer (indicated by flag xFirstDataPgPgm_u8) */
            if((cntProgrammedBytes_u32 == (FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER)) &&
			   (Fee_LLSecReorgStruct_st.xFirstDataPgPgm_u8 == FEE_FIRSTDATAPAGE_NOTPROGRAMMED))
            {
                /* Ignore the first 2 pages of the page buffer as it contains header which is already programmed. */
                 tmpAdd_pu8 = (uint8*)&Fee_PageBytePtr_cpu8[0] + (FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER);
            }
            else
            {
                 /* Buffer contains only data.*/
				 tmpAdd_pu8 = (uint8*)&Fee_PageBytePtr_cpu8[0];
                 Fee_LLSecReorgStruct_st.xFirstDataPgPgm_u8 = FEE_FIRSTDATAPAGE_PROGRAMMED;
            }
#else
            tmpAdd_pu8 = (uint8*)&Fee_PageBytePtr_cpu8[0];
#endif
            if (Fls_Write(Fee_RdWrOrder_st.xWrAddress,
                          tmpAdd_pu8,
                          Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16) != E_NOT_OK)
            {
                 cntProgrammedBytes_u32 += Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16;

                 /* Set the next state in order to wait until the write order is finished */
                 Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_WRITE_E;

                 /* Prepare the compare address */
                 Fee_RdWrOrder_st.xCmpAddress = Fee_RdWrOrder_st.xWrAddress;

                 /* Increment the write address for the next call */
                 Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xWrAddress,
                                             Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16,
                                             TRUE);
             }
             else
             {
                 /* Fls did not accept the order due to wrong parameters or an internal busy state.
                  * Invalidate the cache entry */
                 Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                            FEE_CACHE_TMP_INVALID_VALUE);

                 /* Reset the state machine (and the upper one) */
                 xRetVal_en = FEE_ABORTED_E;
              }
        }
        break;

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Write the header page 2 */
        case FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_E:
        {
            /* The data was read, write the header page 1 into the new sector */
            if (Fls_Write(Fee_RdWrOrder_st.xHdPg2Address,
                          (uint8*)&Fee_hdr2Buffer_au8[0],
                          FEE_PAGE_LEN) != E_NOT_OK)
            {
                /* Prepare the compare address */
                Fee_RdWrOrder_st.xCmpAddress = Fee_RdWrOrder_st.xHdPg2Address;

                /* Clear the address to FEE_MAXUINT32 to indicate that the 2nd header page is programmed. */
                Fee_RdWrOrder_st.xHdPg2Address = FEE_MAXUINT32;

                /* Set the next state in order to wait until the write order is finished */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_WRITE_E;
            }
            else
            {
                /* Fls did not accept the order due to wrong parameters or an internal busy state.
                 * Invalidate the cache entry */
                Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                           FEE_CACHE_TMP_INVALID_VALUE);

                /* Reset the state machine (and the upper one) */
                xRetVal_en = FEE_ABORTED_E;
            }
        }
        break;
#endif

#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        /* Compare the programmed header */
        case FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_E:
        case FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_E:
		{
			/* Check which header page was programmed.*/
            if (Fee_RdWrOrder_st.xHdPg2Address != FEE_MAXUINT32)
			{
				/* Header page 1 was programmed, check against the first page of the header. */
				tmpAdd_pu8 = (uint8*)&Fee_PageBytePtr_cpu8[0];
			}
			else
			{
				/* Header page 2 was programmed, check against the second page of the header. */
				tmpAdd_pu8 = (uint8*)&Fee_hdr2Buffer_au8[0];
			}

            /* Set compare order */
            if (Fls_Compare(Fee_RdWrOrder_st.xCmpAddress,
                            tmpAdd_pu8,
                            FEE_PAGE_LEN) != E_OK)
            {
                /* An error occured due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }
            else
            {
                /* Set the next state to wait for the verification order to finish */
                if (Fee_RdWrOrder_st.xHdPg2Address != FEE_MAXUINT32)
                {
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_HDRPG1_VERIFY_E;
                }
                else
                {
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_HDRPG2_VERIFY_E;
                }
            }
        }
		break;
#endif

        /* Compare the programmed data */
        case FEE_LL_CPY_FLS2FLS_VERIFY_E:
        {
            /* Extract the buffer address from where the data must be programmed. */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
            if(Fee_LLSecReorgStruct_st.xFirstDataPgPgm_u8 == FEE_FIRSTDATAPAGE_NOTPROGRAMMED)
            {
                /* This is the first data byte programming.
                 * Ignore the first 2 pages of the page buffer as it contains header which is already programmed. */
                tmpAdd_pu8 = Fee_PageBytePtr_cpu8 + (FEE_PAGE_LEN*FEE_PAGES_USED_BY_BLK_HEADER);
            }
            else
#endif
            {
                tmpAdd_pu8 = (uint8*)&Fee_PageBytePtr_cpu8[0];
            }

            /* Set compare order */
            if (Fls_Compare(Fee_RdWrOrder_st.xCmpAddress,
                            tmpAdd_pu8,
                            Fee_LLSecReorgStruct_st.xNumBytesLeftToRdWr_u16) != E_OK)
            {
                /* An error occured due to wrong parameters or a busy/not init state of the Fls */
                xRetVal_en = FEE_ABORTED_E;
            }
            else
            {
                /* Set the next state to wait for the verification order to finish */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WAIT_VERIFY_E;
            }
        }
		break;

        /* Write verification error */
#if (FEE_NO_FALLBACK_ACTIVE != FALSE)
        case FEE_LL_CPY_FLS2FLS_FILL_SECTOR_END_ERROR_E:
        case FEE_LL_CPY_FLS2FLS_WRITE_NOFB_MARKER_ERROR_E:
#endif
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)	/* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        case FEE_LL_CPY_FLS2FLS_HDRPG1_WRITE_ERROR_E:
        case FEE_LL_CPY_FLS2FLS_HDRPG2_WRITE_ERROR_E:
#endif
        case FEE_LL_CPY_FLS2FLS_WRITE_ERROR_E:
        {
#if(FEE_ROBUST_PROG_ACTIVE != FALSE)
            /* check if the robust handling for IFX flashes is necessary */
            if (Fls_Rb_GetRobustProgStatus(&Fee_IfxRobustProgramming_s.xStartAddress,  &Fee_IfxRobustProgramming_s.DataBuffer, &Fee_IfxRobustProgramming_s.numBytes) == E_NOT_OK)
            {
                /* Fls_Write was finished without success */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ROBUST_IFX_HANDLING_E;
                break;
            }
            else
            {
                /* its not a IFX robustness error. Retry the operation. */
            }
#endif
        }
        /* No break required as retry must be triggered. */

        /* MR12 RULE 16.3 VIOLATION: Check for retry */
#if (FEE_PAGES_USED_BY_BLK_HEADER == 2u)    /* Robust block programming states (Hdpg1 -> Data -> Hdpg2 write) */
        case FEE_LL_CPY_FLS2FLS_HDRPG1_VERIFY_ERROR_E:
        case FEE_LL_CPY_FLS2FLS_HDRPG2_VERIFY_ERROR_E:
#endif
        case FEE_LL_CPY_FLS2FLS_READ_ERROR_E:
        case FEE_LL_CPY_FLS2FLS_VERIFY_ERROR_E:
        {
            /* Verify retry possibility */
            if(xCntRetry_u8 > 0)
            {
                /* Decrement retry possibilities */
                xCntRetry_u8--;

                /* Restart the state machine in order to start all over again with
                 * copying the current block to the new sector */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E;
            }
            else
            {
                /* Invalidate the cache entry */
                Fee_LLUpdateAddressInCache(Fee_GlobInfoLastRdHeader_pcst->FeeIndex_u16,
                                           FEE_CACHE_TMP_INVALID_VALUE);

                /* Return error, because maximum amount of retries is reached */
                xRetVal_en = FEE_ERROR_E;
            }
        }
        break;

        /* Data transfer is finished, check a possible address overflow */
        case FEE_LL_CPY_FLS2FLS_CHECK_ADR_OVERFLOW_E:
        {
            /* Data was now read and written successfully. A possible address overflow for the read and
             * write addresses must be handled and the possibility that the write sector is now full */

            /* Get the physical sector index for the next READ order */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_LLSecReorgStruct_st.xRdAddress_u32);

            /* Check if the end of the read sector was reached */
            if(Fee_LLSecReorgStruct_st.xRdAddress_u32 >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
            {
                /* Switch to next sector and read out the rest of the data, if necessary */

                /* Get logical sector index and increment it */
                xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1u);

                /* Overflow handling not necessary */

                /* Get the new physical sector index */
                xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                /* Get the new sector start address */
                Fee_LLSecReorgStruct_st.xRdAddress_u32 = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;
            }

            /* Get the physical sector index for the next WRITE order */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Check if the end of the write sector was reached */
            if(Fee_RdWrOrder_st.xWrAddress >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
            {
                /* The sector is full, write the FULL marker */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E;
            }
            else
            {
                /* Go on with reading the rest of the data, function will be finished automatically,
                 * if there is no data left */
                Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_READ_E;
            }
        }
        break;

        /* Write the FULL marker */
        case FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E:
        {
            /* Get the physical sector index of the FULL sector */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the FULL marker */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_FULL_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /*
                 * Writing of "FULL" marker was finished
                 * -----------------------------------
                 * --> Set Fee_RdWrOrder_st.xWrAddress to the first empty page in next logical sector
                 * --> Write the USED marker in the next logical sector
                 */

                /* Get the current logical sector index */
            	xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];

                /* Increment the logical sector index */
                xLogSectIdx_u8 += 1u;

                /* Check if switching from last to first sector requires an overflow */
                if (xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                {
                    /* Reset the logical sector index */
                    xLogSectIdx_u8 = FEE_NUM_FLASH_BANKS-1u;
                }

                /* Get the new physical sector index */
                xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                /* Erase the new logical sector if necessary  */
                if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_STATE_UNDEF_E) ||
                   (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_REQUEST2ERASE_E))
                {
                    /* Mark this sector */
                    Fee_LLSetEraseSector(xLogSectIdx_u8);

                    /* Save new write address */
                    Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                    /* Set erase state */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E;
                }
                else
                {
                    /* New logical sector might already be erased which is OK,
                     * but check for a "sector overflow" */
                    if(Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_ERASED_E)
                    {
                        /* Set the new write address */
                        Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                        /* Write the USED marker next */
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_USED_MARKER_E;
                    }
                    else
                    {
                        /* Prevent the driver from overwriting already used flash areas by erasing
                         * this sector in case of sector states "FULL" or "USED" (information might get lost)
                         * --> erase the formerly "USED" sector, not the oldest "FULL" sector */

                        /* Get the old physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Mark the latest sector */
                        Fee_LLSetEraseSector(xLogSectIdx_u8);

                        /* Save new write address  */
                        Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                        /* Set the sector overflow indicator */
                        xSectOverflow_b = TRUE;

                        /* Set erase state */
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E;
                    }
                }
            }
        }
        break;

        /* Erase the sector that will be used as a new USED sector */
        case FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E:
        {
            /* Check the erase sector result */
            /* MR12 RULE 10.3 VIOLATION: Not critical warning. (Changing the data type is not hex neutral for JDP) */
            xRetValErase_en = Fee_LLEraseSector();

            /* MR12 RULE 10.4 VIOLATION: Not critical warning. (Changing the data type is not hex neutral for JDP)  */
            if(xRetValErase_en != FEE_ORDER_PENDING_E)
            {
                /* If erase order was successfull, then set state to write used marker */
                /* in error case erase is restarted again.                             */
                /* MR12 RULE 10.4 VIOLATION: Not critical warning. (Changing the data type is not hex neutral for JDP)  */
                if (xRetValErase_en == FEE_ORDER_FINISHED_E)
                {
                    /* Sector erase is done. New write address was already set before */

                    /* Error reaction for unsuccessfull ERASED marker write order not necessary
                     * --> RAM structure will be set and used for writing the USED marker
                     *     procedure as long as the Fee_Init is not passed again.
                     * --> If init is passed, the sector detection will recognize this sector as
                     *     undefined and execute an erase automatically. */

                    /* Check if a sector overflow has happened */
                    if(xSectOverflow_b != FALSE)
                    {
                        /* Invalidate the complete cache */
                        for(xCnt_u16=0; xCnt_u16<FEE_NUM_BLOCKS; xCnt_u16++)
                        {
                            /* Invalidate the corresponding cache address */
                            Fee_LLInvalidateAddressInCache(Fee_BlockProperties_st[xCnt_u16].BlockPersistentId_u16);
                        }

                        /* Invalidate the complete cache status */
                        for(xCnt_u16=0; xCnt_u16<FEE_NUM_FLASH_BANKS; xCnt_u16++)
                        {
                            /* Invalidate the corresponding physical sector */
                            Fee_LLEraseCacheStForSect((uint8)xCnt_u16);
                        }

                        /* If robust sector flow feature is activated, then skip writing of the used marker as this will be used later. */
                        #if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ROBUST_SECT_OVERFLOW_E;
                        break;
                        #endif
                    }

                    /* Write the USED marker next */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_USED_MARKER_E;
                }
            }

        }
        break;

        /* Write the USED marker to the new sector */
        case FEE_LL_CPY_FLS2FLS_WRITE_USED_MARKER_E:
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
                 * was already set in the the previous state (FEE_LL_CPY_FLS2FLS_WRITE_FULL_MARKER_E) */

                /* Verify whether it was possible to write the USED marker or not */
                if(xWrMarkerRetVal_en == FEE_ORDER_FINISHED_E)
                {
                    /* Check for a sector overflow . But if Robust sector overflow is enabled, the control will not come here after erase
                     * but go directly to the robust sector flow state. Hence, below check is required only when robust feature is not active. */
                    #if ! (defined (FEE_PRV_ROBUST_SECT_OVERFLOW))
                    if(xSectOverflow_b != FALSE)
                    {
                        /* Due to a "sector overflow" the USED sector was erased instead of
                         * the oldest FULL sector, return an abortion of the copy process */
                        xRetVal_en = FEE_ABORTED_E;
                    }
                    else
                    #endif
                    {
                        /* Write Marker with the start-Address as Payload. This marker is more or less the double storage
						 * of the USED Marker and contains the Address of the first  blockheader */
                        tmpAddr_u32 = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;

                        if (cntProgrammedBytes_u32 > 0uL)
                        {
                            /* Calculate how many bytes have to be written in the "new" sector */
                            tmpAddr_u32 += (Fee_GlobInfoLastRdHeader_pcst->BlkLength_u16 + (uint16)FEE_BLK_HEADER_SIZE) - cntProgrammedBytes_u32;

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
                        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_WRITE_START_MARKER_E;
                    }
                }
                else
                {
                    /* The marker section is full/not readable/writeable or the Fls order was not accepted.
                     * --> The complete sector has to be erased again. Otherwise there might be
                     *     data getting lost in the future! */

                    /* Get corresponding logical sector */
                    xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];

                    /* Mark this sector */
                    Fee_LLSetEraseSector(xLogSectIdx_u8);

                    /* Set erase state */
                    Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E;
                }
            }
        }
        break;

       case FEE_LL_CPY_FLS2FLS_WRITE_START_MARKER_E:
       {
            /* Get the new physical sector index */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the USED marker */
            xWrMarkerRetVal_en = Fee_LLWriteMarker(xPhySectIdx_u8, FEE_START_MARKER_ID_E);

            /* Check the write USED marker result */
            if(xWrMarkerRetVal_en != FEE_ORDER_PENDING_E)
            {
				/* Go on with the block transfer in case it is necessary. Otherwise
				 * the function will be finished automatically. */
				Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_READ_E;
            }
        }
       break;

        #if(FEE_ROBUST_PROG_ACTIVE != FALSE)
		case FEE_LL_CPY_FLS2FLS_ROBUST_IFX_HANDLING_E:
		{
            /* Get the new physical sector index */
			xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

			/* Get corresponding logical sector */
			xLogSectIdx_u8 = Fee_idxLLSectorOrder_au8[xPhySectIdx_u8];

			if (Fee_RobIfxHandling(xLogSectIdx_u8) != FEE_ORDER_PENDING_E){
				xRetVal_en = FEE_ERROR_E;
			}
		}break;
        #endif

        #if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
		case FEE_LL_CPY_FLS2FLS_ROBUST_SECT_OVERFLOW_E:
		{
		    if (Fee_LlRobustSectorOverflow() != FEE_ORDER_PENDING_E)
		    {
		        /* Return error to start a retry of complete sector reorganisation. */
                xRetVal_en = FEE_ERROR_E;
		    }
		}break;
        #endif

        /* Default case should never be reached */
        default:
            /* Return error */
            xRetVal_en = FEE_ERROR_E;
        break;
    }

    /* Check if the function is finished (with or without success) */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        Fee_RdWrOrder_st.Fee_LLCpyBlkFls2Fls_en = FEE_LL_CPY_FLS2FLS_INIT_E;

        /* These are additional resets (cannot be reset in the init state) */
        Fee_LLSecReorgStruct_st.xCntCopies_u8 = 0;
        xCntRetry_u8 = FEE_MAX_RD_WR_COMP_RETRIES;
    }

    return (xRetVal_en);
}


/**
 ***********************************************************************************************************************
 * Fee_SectorOverflow(): Handles the sector overflow situation during sector reorganisation.
 * This function is called only when there is not enough space to transfer all the old data to new sector during sector
 * reorganisation (this situation may arrise due to continous resets and sector being fully occupied).
 *
 * The design is different for Renasas controllers and all other controllers for following reasons:
 * 1. No Fall back feature leaves a page blank before the header. During the copy operation this page must be left blank.
 *    This means that a bulk programming is not possible. Page must be first checked if its blank, then transfered.
 * 2. It is not possible to give the source address as Flash area when placing write request, the data must be first
 *    read out in internal buffer and then this buffer must be given for programming. Junk data might be written if
 *    the flash address is given as source address (hardware doesnt allow read from one flash area when flash operation
 *    is going on).
 * Hence, for Renasas controllers, the design is to erase the sectors after the HSR (sectors are small and 64bytes).
 *
 * For all other controllers, this function copies data till HSR in the last but one sector information to next sector.
 *
 * \param    none:
 *
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E    : Operation is ongoing
 * \retval   FEE_ABORTED_E          : Order was aborted due to incorrect parameters for FLS function.
 * \retval   FEE_ERROR_E            :
 * \retval   FEE_ORDER_FINISHED_E   : Sector rearrangement is completed. Sector reorg can now be retried.
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
#if defined (FEE_PRV_ROBUST_SECT_OVERFLOW)
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LlRobustSectorOverflow(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC)    xRetVal_en      = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(Fee_stRetVal_ten, AUTOMATIC)    xTmpRetVal_en   = FEE_ORDER_PENDING_E;  /* Temporary return value of llErase Function */
    VAR(uint8,   AUTOMATIC)             xLogSecIdx_u8;                          /* Index of the logical sector */
    VAR(uint8,   AUTOMATIC)             xPhySectIdx_u8;                         /* Index of the physical sector */
    static VAR(Fls_LengthType, FEE_VAR) xDataSize_uo;                           /* Size of data to be copied. */
    static VAR(Fls_LengthType, FEE_VAR) xCntPgmSize_uo;                         /* Amount of bytes copied in one step. */

    switch (Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en)
    {
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_INIT_E:
        {
            /* Data must be copied from last but one sector, compute the start address of this sector. */
            xLogSecIdx_u8 = FEE_NUM_FLASH_BANKS_AVAILABLE - 2u;

            /* Get the physical sector index of the Last but one sector. */
            xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

            /* Update Read address to start of the last but one sector (skip the sector header area). */
            Fee_RdWrOrder_st.xRdAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_PhysStartAddress_u32 + FEE_SEC_HEADER_SIZE;

            /* Last sector is the sector that will be currently worked upon. */
            xLogSecIdx_u8 = FEE_NUM_FLASH_BANKS_AVAILABLE - 1u;

            /* Get the physical sector index of the Last sector */
            xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

            /* Update Write address to start of the last sector (skip the sector header area). */
            Fee_RdWrOrder_st.xWrAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_PhysStartAddress_u32 + FEE_SEC_HEADER_SIZE;

            /* Compute the amount of bytes to be copied (from top of the sector till HSR) */
            xDataSize_uo = (((FEE_PHYS_SEC_END0 + 1u) - FEE_PHYS_SEC_START0)*2u) - FEE_REQUIRED_FREE_SPACE_BEFORE_HARD_SR;

            /* Round it to the nearest page size. */
            while ((xDataSize_uo % FEE_PAGE_LEN) != 0u)
            {
                xDataSize_uo++;
            }

            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_CM_E;
        }
        /* No break to save time */

        /* MR12 RULE 16.3 VIOLATION: Time critical position */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_CM_E:
        {
            xPhySectIdx_u8 = Fee_LLSectorOrder_st[FEE_NUM_FLASH_BANKS_AVAILABLE - 1u].xPhySecIdx_u8;

            /* Write the CLONE_START marker */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_CLONE_START_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /* in the sector header, there is the information available, that a clone procedure has started. Now it
                 * is allowed to write data in this sector. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_PREPARE_E;
            }
        }
        break;

        case FEE_LL_ROBUST_SECTOR_OVERFLOW_PREPARE_E:
        {
            /* For Renesas the entire operation is done one page at a time, as blank pages maybe there due to no fall back feature and these pages must be left blank in the new sector as well. */
            #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
            xCntPgmSize_uo = FEE_PAGE_LEN;

            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_E;
            #else
            /* At maximum FEE_LL_PAGEBUFFSIZE bytes can be read in one step. */
            if (xDataSize_uo > FEE_LL_PAGEBUFFSIZE)
            {
                xCntPgmSize_uo = FEE_LL_PAGEBUFFSIZE;
            }
            else
            {
                xCntPgmSize_uo = xDataSize_uo;
            }

            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_E;
            #endif

        }
        /* No break to save time */

        /* For Renesas controllers, first check if the page is blank or not before transfering the information. */
        /* MR12 RULE 16.3 VIOLATION: Time critical position */
        #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_E:
        {
            if (Fls_Rb_BlankCheck(Fee_RdWrOrder_st.xRdAddress, NULL_PTR, xCntPgmSize_uo) != E_NOT_OK)
            {
                /* Blank check order accepted, go to wait state. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_WAIT_E;
            }
            else
            {
                xRetVal_en = FEE_ABORTED_E;
            }
        }break;
        #endif

        /* Page is not blank and has data, read this data to transfer it to new sector. */
        /* MR12 RULE 16.3 VIOLATION: Time critical position */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_E:
        {
            if (Fls_Read(Fee_RdWrOrder_st.xRdAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xCntPgmSize_uo) != E_NOT_OK)
            {
                /* Read request accepted, go to wait state. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_WAIT_E;
            }
            else
            {
                xRetVal_en = FEE_ABORTED_E;
            }
        }break;

        /* Tranfer the data to new sector. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_E:
        {
            if (Fls_Write(Fee_RdWrOrder_st.xWrAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xCntPgmSize_uo) != E_NOT_OK)
            {
                /* Write request accepted, go to wait state. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_WAIT_E;
            }
            else
            {
                xRetVal_en = FEE_ABORTED_E;
            }
        }break;

        /* Verify if the data copy was correct. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_E:
        {
            if (Fls_Compare(Fee_RdWrOrder_st.xWrAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xCntPgmSize_uo) != E_NOT_OK)
            {
                /* Compare request accepted, go to wait state. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_WAIT_E;
            }
            else
            {
                xRetVal_en = FEE_ABORTED_E;
            }
        }break;

        /* Wait for the order to be finished */
        #if ( defined(RBA_FLSRH850P1xC_FLASH) || defined(RBA_FLSV850R1x_FLASH) )
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_BLANK_CHK_WAIT_E:
        #endif

        case FEE_LL_ROBUST_SECTOR_OVERFLOW_READ_PAGE_WAIT_E:
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_COPY_DATA_WAIT_E:
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_DATA_WAIT_E:
        {
            /* switching state from WAIT --> DONE/ERROR will be done in
             * Fee_JobEndNotification and Fee_JobErrorNotification */

            /* Check whether the OS is currently running or not */
            if(Fee_stMain == FEE_POLLING_MODE_E)
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

        /* Page transfer was successful, check if there are more bytes to be transfered. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_VERIFY_SUCCESS_E:
        {
            /* Data transfer was successful, increment the read and write addresses and decrement the amount of bytes transfered.
             * There is no need to handle the sector overflow situation, as this will never occur in this function. */
            Fee_RdWrOrder_st.xWrAddress += xCntPgmSize_uo;
            Fee_RdWrOrder_st.xRdAddress += xCntPgmSize_uo;
            xDataSize_uo -= xCntPgmSize_uo;

            /* Check if all bytes are transfered. */
            if (xDataSize_uo != 0u)
            {
                /* Some more data yet to be transfered, continue with the transfer of data. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_PREPARE_E;
            }
            else
            {
                /* Data transfer is complete. Go to next state to write used marker. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_UM_E;
            }
        }
        break;

        /* All information is transfered to new sector, mark this sector to be used and then swap the sector order. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_WR_UM_E:
        {
            /* Get the physical sector index of the FULL sector */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* Write the CLONE_START marker */
            if(Fee_LLWriteMarker(xPhySectIdx_u8, FEE_USED_MARKER_ID_E) != FEE_ORDER_PENDING_E)
            {
                /* In the sector header, there is the information available, that a clone procedure has started. Now it
                 * is allowed to write data in this sector. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_SORT_SECT_E;
            }
        }
        break;

        /* Swap the sector order. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_SORT_SECT_E:
        {
            /* Cache invalidation is not requried as this is already done in the state FEE_LL_CPY_FLS2FLS_ERASE_SECTOR_E of Fee_LLCpyBlkFls2Fls().*/

            /* Put the old sector at the end of the sector list and mark the sector with request to erase marker.
             * In this error case only the last 2 sectors have to be swapped. */
            /* Back up the information for last but one sector. */
            xLogSecIdx_u8 = FEE_NUM_FLASH_BANKS_AVAILABLE - 2u;
            xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8;

            /* Reorganize the sector order */
            Fee_LLSectorOrder_st[xLogSecIdx_u8] = Fee_LLSectorOrder_st[xLogSecIdx_u8 + 1u];
            /* Reorganize the array Ram table */
            Fee_idxLLSectorOrder_au8[Fee_LLSectorOrder_st[xLogSecIdx_u8].xPhySecIdx_u8] = xLogSecIdx_u8;

            /* Update the state information of the last sector in the ring with the data of the sector with the wordline failure. */
            Fee_LLSectorOrder_st[xLogSecIdx_u8 + 1u].xPhySecIdx_u8   = xPhySectIdx_u8;
            Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] = xLogSecIdx_u8 + 1u;

            /* mark the last sector as ready to erase */
            Fee_LLSetEraseSector(FEE_NUM_FLASH_BANKS-1);

            xRetVal_en = FEE_ORDER_FINISHED_E;
        }
        break;

        /* Error state for all kinds of error (read error, blank check error, write error, blank check error and erase error.
         * In all these error case, the safest thing to do is retry the complete operation, starting with an erase of the latest sector. */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E:
        {
            /* Prepare the erase request for the last sector. */
            xLogSecIdx_u8 = FEE_NUM_FLASH_BANKS_AVAILABLE - 1u;

            Fee_LLSetEraseSector(xLogSecIdx_u8);

            Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_ERASE_E;
        }
        /* No break to save time */

        /* MR12 RULE 16.3 VIOLATION: Time critical position */
        case FEE_LL_ROBUST_SECTOR_OVERFLOW_ERASE_E:
        {
            xTmpRetVal_en = Fee_LLEraseSector();
            if(xTmpRetVal_en == FEE_ORDER_PENDING_E)
            {
                /* Erase is ongoing. do nothing till it is completed. */
            }
            else if(xTmpRetVal_en == FEE_ORDER_FINISHED_E)
            {
                /* Erase is completed successfully, re-start the transfer operation from beginnning. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_INIT_E;
            }
            else
            {
                /* Erase was not successful, retry the erase operation. */
                Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_ERROR_E;
            }
        }
        break;

        default:
            /* Return with error */
            xRetVal_en = FEE_ERROR_E;
        break;
    }

    /* Check if order was finished with or without success */
    if (xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset state machine */
        Fee_RdWrOrder_st.Fee_LLRobustSectOverflow_en = FEE_LL_ROBUST_SECTOR_OVERFLOW_INIT_E;
    }

    return (xRetVal_en);
}
#endif
/**
 *********************************************************************
 * Fee_LLCalcBlkCrcInFlash(): Calculate the block checksum
 *
 * This function calculates the block checksum in the flash.
 *
 * \param    HeaderInfo_pcst:        Pointer to the block header that was
 *                                  found in the flash.
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           The checksum is wrong or a read
 *                                  error occured
 * \retval   FEE_ORDER_FINISHED_E:  The checksum is correct (either
 *                                  standard or rob checksum)
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLCalcBlkCrcInFlash(P2CONST(Fee_GlobInfoLastRdHeader_tst, AUTOMATIC, FEE_APPL_DATA) HeaderInfo_pcst)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal_en = FEE_ORDER_PENDING_E;  /* Function return */
    VAR(uint8, AUTOMATIC) xPhySectIdx_u8 = 0;                           /* Physical sector index */
    VAR(uint8, AUTOMATIC) xPhyWrSectIdx_u8 = 0;                         /* Physical sector index of the write address */
    VAR(uint8, AUTOMATIC) xLogSectIdx_u8 = 0;                           /* Logical sector index */
    VAR(uint16, AUTOMATIC) xDataBlkLength_u16  = 0;                     /* Temporary data length */
    static uint16 xNumBytes_u16 = 0;                                    /* Amount of data bytes to use for the calculation */
    static uint32 xBlkCrc32_u32 = 0;                                    /* Block CRC */
    static uint16 xConfigPropTableIdx_u16 = 0;                          /* Respective block properties index */
    static boolean xFirstCRCRunDone_b = FALSE;                          /* Indication for the first CRC run */

    #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
    VAR(uint8, AUTOMATIC) i_u8 = 0;                                     /* Loop counter */
    VAR(uint32, AUTOMATIC) xNumBytesLeft_32 = 0;                        /* Number of bytes left for the current sector */
    static uint32 xBlkRobCrc32_u32 = 0;                                 /* Robustness block CRC */
    #endif


	/* Switch over the state machine */
	switch (Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en)
	{
		/* Init state */
		case FEE_LL_CRC_BLK_INIT_E:
		{
			/* Get the block header address */
			Fee_RdWrOrder_st.xCrcAddress = HeaderInfo_pcst->AdrBlkHeader_u32;

			/* Reset variables */
			xBlkCrc32_u32      = 0;
            xFirstCRCRunDone_b = FALSE;
			Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = 0;

            #if(FEE_FAST_CACHE_INIT_ACTIVE != FALSE)
            (void)Fee_SrvBinarySearchInBlockPropFast(HeaderInfo_pcst->FeeIndex_u16, &xConfigPropTableIdx_u16);
            #else
            /* Get the current block properties index in case a sector reorganization is running
             * (no order queue entry available) */
            (void)Fee_SrvBinarySearchInBlockProp(HeaderInfo_pcst->FeeIndex_u16, &xConfigPropTableIdx_u16);
            #endif

            /* Identify the correct number of bytes */
            if(HeaderInfo_pcst->BlkLength_u16 > FEE_LL_PAGEBUFFSIZE)
            {
                /* Restrict the number of bytes */
                xNumBytes_u16 = FEE_LL_PAGEBUFFSIZE;
            }
            else
            {
                /* The block length can be used unrestricted */
                xNumBytes_u16 = HeaderInfo_pcst->BlkLength_u16;
            }

            /* Reset the page buffer to make sure no wrong data remains inside */
            Fee_SrvMemSet8((uint8*)&Fee_PageBytePtr_cpu8[0], (uint8)FEE_ERASE_PATTERN, xNumBytes_u16);

            /* Set next state */
            Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en  = FEE_LL_CRC_RD_HD_PAGE_E;
		}
		/* No break to save time */

		/* Read the header page */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_LL_CRC_RD_HD_PAGE_E:
		{
			/* Get the number of data bytes */
			xNumBytes_u16 = HeaderInfo_pcst->BlkLength_u16;

			/* Check for the robustness configuration of this block */
			if((((HeaderInfo_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint8)FEE_FLAG_ROBUST_ATTR_BP) > 0) &&
				((HeaderInfo_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) == 0))
			{
				/* Adapt the block length for checking the regular checksum first */
				xNumBytes_u16 -= FEE_SIZE_OF_BLOCK_CS;
			}

			if(xNumBytes_u16 > FEE_FREE_BYTES_AFTER_HEADER)
			{
				/* During the header page read routine only some data bytes are located
				 * behind the header within the same page */
				xNumBytes_u16 = FEE_FREE_BYTES_AFTER_HEADER;
			}

			/* Read back the block header pages (no need for an overflow check since the header will
			 * always be located within one sector only) */
			if(Fls_Read(Fee_RdWrOrder_st.xCrcAddress,
			            (uint8*)&Fee_PageBytePtr_cpu8[0],
			            (FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER)) != E_NOT_OK)
			{
				/* Set the next state */
				Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_PAGE_WAIT_E;

				/* Increment the read address for the next Fls access (overflow is checked automatically) */
				Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xCrcAddress, (FEE_PAGE_LEN * FEE_PAGES_USED_BY_BLK_HEADER), TRUE);
			}
			else
			{
				/* Abort the function due to invalid Fls parameters or a busy Fls */
				xRetVal_en = FEE_ABORTED_E;
			}
		}
		break;

		/* Wait for the read function to be finished */
		case FEE_LL_CRC_RD_PAGE_WAIT_E:
#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
		case FEE_LL_CRC_RD_ROB_PAGE_WAIT_E:
#endif
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

		/* Read error case */
		case FEE_LL_CRC_RD_ERROR_E:
		{
			/* Verify retry possibility */
			if(Fee_RdWrRetries_u8 > 0)
			{
				/* Decrement retry possibilities */
				Fee_RdWrRetries_u8--;

				/* No matter when the read error happened (for reading the header
				 * or the data), restart from the beginning */
				Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_BLK_INIT_E;
			}
			else
			{
				/* The maximum amount of retries was reached. Do not invalidate the
				 * cache since the root cause for the read failure is not clear */
				Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16,
										   FEE_CACHE_TMP_INVALID_VALUE);

				/* Return error
				 * --> Sector reorganization: Search for older copies
				 * --> Read blocks: Search for older copies (independent from
				 *     forced read / normal read) */
				xRetVal_en = FEE_ERROR_E;
			}
		}
		break;

        /* Check for an overlap of the CRC address */
		case FEE_LL_CRC_CHECK_OVERLAP_E:
#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
		case FEE_LL_CRC_CHECK_OVERLAP_ROB_E:
#endif
		{
		    /* Set the next state */
#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
		    if(Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en == FEE_LL_CRC_CHECK_OVERLAP_ROB_E)
		    {
	            Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_ROB_PAGE_E;
	            xDataBlkLength_u16 = FEE_SIZE_OF_BLOCK_CS;
		    }
		    else
#endif
		    {
		        Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_PAGE_E;
		        xDataBlkLength_u16 = HeaderInfo_pcst->BlkLength_u16;
		    }

            /* Get the physical sector index of the CRC address */
            xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xCrcAddress);

            /* Get the physical sector index of the write address */
            xPhyWrSectIdx_u8 = Fee_GetPhysSectorByAddress(Fee_RdWrOrder_st.xWrAddress);

            /* The CRC address is already incremented with the number of bytes from the previous read order
             * -> if the CRC address is now behind the write address the block is not written completely! */
            if ((Fee_RdWrOrder_st.xCrcAddress > Fee_RdWrOrder_st.xWrAddress) &&
                (xPhySectIdx_u8 == xPhyWrSectIdx_u8))
            {
                /* Abort */
                xRetVal_en = FEE_ERROR_E;
            }

            /* Check if there are still bytes left to be checked */
            if((Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 + xNumBytes_u16) < xDataBlkLength_u16)
            {
                /* Check if the address behind the current block header is located at the very
                 * end of the current sector */
                if(Fee_RdWrOrder_st.xCrcAddress >= Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogEndAddress_u32)
                {
                    /* The corresponding data is located in the next logical sector */
                    xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] + 1);

                    /* Check if switching from last to first sector requires an overflow */
                    if (xLogSectIdx_u8 >= FEE_NUM_FLASH_BANKS)
                    {
                        /* Abort, the block cannot continue in the logical sector 0 */
                        xRetVal_en = FEE_ERROR_E;
                    }
                    else
                    {
                        /* Before switching to next sector, check if next sector is programmed with data and if there are more data to be read. */
                        if((Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_USED_E) ||
                           (Fee_LLSectorOrder_st[xLogSectIdx_u8].SecState_en == FEE_SECTOR_FULL_E))
                        {
                            /* Get the new physical sector index */
                            xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                            /* Set the new start address */
                            Fee_RdWrOrder_st.xCrcAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32;
                        }
                        else
                        {
							/* Abort, the block check as next sector is still not programmed with data. */
							xRetVal_en = FEE_ERROR_E;
						}
					}
                }
            }
            else
            {
                /* There wont be any more reads in the next sector as all bytes are read.
                   Its important that the driver continues with the next step and checks if the checksum matches. */
            }
		}
		break;

		/* Calculate the block checksums */
		case FEE_LL_CRC_RD_PAGE_E:
		{
			/* Check if this is a normal data page or not */
			if (xFirstCRCRunDone_b == FALSE)
			{
				/* This is the first time that this function is called
				 * --> block header information + data bytes are available in the page buffer
				 * --> get the start value for the data CRC */

				/* Calculate the checksum beginning with the data bytes position (the page buffer contains some
				 * data bytes which are not protected by the header checksum but by the block checksum only) */
				xBlkCrc32_u32 = Crc_CalculateCRC32((uint8*)&Fee_PageBytePtr_cpu8[FEE_BLK_HEADER_SIZE],
													(uint32)xNumBytes_u16,
													(((uint32)HeaderInfo_pcst->HdrCrc16_u16) ^ FEE_MAXUINT32),
													FALSE);

				/* Indicate that the first CRC run has been performed already */
				xFirstCRCRunDone_b = TRUE;
			}
			else
			{
				/* This is a normal data page
				 * --> only data bytes are available in the page buffer */

				/* XOR for the start value is necessary if the calculation is done over multiple steps
				 * and done by the CRC routine itself (AR40 Rev2) */

				/* Calculate the checksum over the complete page buffer */
				xBlkCrc32_u32 = Crc_CalculateCRC32((uint8*)&Fee_PageBytePtr_cpu8[0],
												   (uint32)xNumBytes_u16,
													xBlkCrc32_u32,
													FALSE);
			}

			/* Increment the amount of bytes that have already been considered */
			Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = (uint16)(Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 +
																	 xNumBytes_u16);

			#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
			/* Check for the robustness configuration of this block */
			if((((HeaderInfo_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint8)FEE_FLAG_ROBUST_ATTR_BP) > 0) &&
			   ((HeaderInfo_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_INVALID_MSK) == 0))
			{
				/* Adapt the block length for checking the regular checksum first */
				xDataBlkLength_u16 = HeaderInfo_pcst->BlkLength_u16 - FEE_SIZE_OF_BLOCK_CS;
			}
			else
			#endif
			{
				/* The regular length can be taken */
				xDataBlkLength_u16 = HeaderInfo_pcst->BlkLength_u16;
			}

			/* Check if there are still bytes left to be checked */
			if (Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 < xDataBlkLength_u16)
			{
				/* Calculate the number of bytes which need to be read next */
				xNumBytes_u16 = (uint16)(xDataBlkLength_u16 -
										 Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16);

				/* Check for a buffer overflow */
				if (xNumBytes_u16 > FEE_LL_CRC_CALC_RESTRICTION)
				{
					/* Restrict the number of bytes to read */
					xNumBytes_u16 = FEE_LL_CRC_CALC_RESTRICTION;
				}

				/* Check if the current sector has enough bytes left */
				if(Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_CRC_CALC) < xNumBytes_u16)
				{
					/* Restrict the number of bytes to read */
					xNumBytes_u16 = (uint16)(Fee_CalculateNumOfFreeBytesInCurSector(FEE_LL_SECTOR_USED_FOR_CRC_CALC));
				}

				/* Read the data bytes */
				if(Fls_Read(Fee_RdWrOrder_st.xCrcAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xNumBytes_u16) != E_NOT_OK)
				{
					/* Set the next state */
					Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_PAGE_WAIT_E;

					/* Increment the read address for the next Fls access (overflow is checked automatically) */
					Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xCrcAddress, xNumBytes_u16, FALSE);
				}
				else
				{
					/* Abort the function due to invalid Fls parameters or a busy Fls */
					xRetVal_en = FEE_ABORTED_E;
				}
			}
			else
			{
				/* Reading of this block is finished, verify the data checksum */
				if(xBlkCrc32_u32 == HeaderInfo_pcst->BlkCrc32_u32)
				{
					/* Update the address in the cache (the function will not change any
					 * entries in case an unknown block is checked during an
					 * "afterburner" run in the reorganization) */
					Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16,
											   HeaderInfo_pcst->AdrBlkHeader_u32);


					/* The calculated checksum is equal compared to the checksum in the block header */
					xRetVal_en = FEE_ORDER_FINISHED_E;
				}
				else
				{
					/* The calculated checksum is different compared to the checksum in the block header */

					#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
					/* Check for the availability of the robustness checksum */
					if(((HeaderInfo_pcst->BlkStatus_u8 & (uint8)FEE_FLAG_ROBUST_ATTR_MSK) >> (uint8)FEE_FLAG_ROBUST_ATTR_BP) > 0)
					{
						/* Read out the robustness checksum next */
						Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_ROB_PAGE_E;

						/* Reset variables */
						xNumBytes_u16 = 0;
						Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = 0;
					}
					else
					#endif
					{
						/* Check the necessity of marking the cache invalid temporarily.
						 * This is necessary in all cases (standard read and sector reorg for known blocks)
						 * besides a forced read action. An update of the cache for unknown blocks during the
						 * sector reorganization does not effect the cache. */
						if((Fee_Rb_WorkingState_en == FEE_RB_READ_MODE_E) &&
						   (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_FORCED_READ_ORDER))
						{
							/* Do not mark the cache as temporary invalid for not loosing the block
							 * during a reorganization after an interruption */
							;
						}
						else
						{
							/* Update the cache */
							Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16,
													   FEE_CACHE_TMP_INVALID_VALUE);
						}

						/* Set return value */
						xRetVal_en = FEE_ERROR_E;
					}
				}
			}
		}
		break;

		#if(FEE_ROB_FEATURE_ACTIVE != FALSE)
		/* Retry with the robustness checksum */
		case FEE_LL_CRC_RD_ROB_PAGE_E:
		{
			/* Only read out the robustness checksum now and compare it */

			/* Check if this is the first call of this function */
			if (xNumBytes_u16 != 0)
			{
				/* This is the second time that this function is called
				 * --> The first part of the robustness checksum was located in a different sector */

				/* Loop over the CRC bytes (size is already restricted to the number of CS bytes) */
				for(i_u8=0; i_u8<xNumBytes_u16; i_u8++)
				{
					/* Shift the robustness crc result */
					xBlkRobCrc32_u32 |= ((uint32)(((uint32)(Fee_PageBytePtr_cpu8[i_u8])) << (24 -
														((i_u8 + Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16)*8))));
				}
			}

			/* Increment the amount of bytes that have already been considered */
			Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 = (uint16)(Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 +
																	 xNumBytes_u16);

			/* Check if there are still bytes left to be checked */
			if (Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 < FEE_SIZE_OF_BLOCK_CS)
			{
				/* Calculate the number of bytes which need to be read next */
				xNumBytes_u16 = (uint16)(FEE_SIZE_OF_BLOCK_CS - Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16);

				/* Check if the current sector has enough bytes left, get the corresponding physical sector
				 * of the Crc address */
				xPhySectIdx_u8 = Fee_GetPhysSectorByAddress(FEE_LL_SECTOR_USED_FOR_CRC_CALC);

				/* Calculate the number of bytes until the sector end address is reached */
				xNumBytesLeft_32 = (Fee_FlashProp_st[xPhySectIdx_u8].Fee_PhysEndAddress_u32 + 1u) -
																		FEE_LL_SECTOR_USED_FOR_CRC_CALC;

				/* Check if the current sector has enough bytes left */
				if(xNumBytesLeft_32 < xNumBytes_u16)
				{
					/* Restrict the number of bytes to read */
					xNumBytes_u16 = (uint16)xNumBytesLeft_32;
				}

				/* Check if xCrcAddress must be corrected for the boundary condition when the first byte of the checksum is the last byte of the sector.
				 * Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 == 0 is required to be checked, so that this operation is performed only once when reading the first byte of the CRC. */
				if ((Fee_RdWrOrder_st.xCrcAddress == Fee_FlashProp_st[xPhySectIdx_u8].Fee_LogStartAddress_u32) &&
				    (Fee_GlobInfoWrBlock_st.BytesAlrdyCompared_u16 == 0u))
				{
				    /* Differentiate between the siutation when all 4 CRC bytes are present in the last page or only 3 bytes. */
				    if(((HeaderInfo_pcst->BlkLength_u16 - FEE_FREE_BYTES_AFTER_HEADER) % FEE_PAGE_LEN) == 3u)
				    {
				        /* Read only the last byte from the sector first. */
				        xLogSectIdx_u8 = (uint8)(Fee_idxLLSectorOrder_au8[xPhySectIdx_u8] - 1u);

				        /* Get the new physical sector index */
                        xPhySectIdx_u8 = Fee_LLSectorOrder_st[xLogSectIdx_u8].xPhySecIdx_u8;

                        /* Set the new start address */
                        Fee_RdWrOrder_st.xCrcAddress = Fee_FlashProp_st[xPhySectIdx_u8].Fee_PhysEndAddress_u32;

                        xNumBytes_u16 = 1u;
				    }
				}

				/* Read the checksum */
				if(Fls_Read(Fee_RdWrOrder_st.xCrcAddress, (uint8*)&Fee_PageBytePtr_cpu8[0], xNumBytes_u16) != E_NOT_OK)
				{
					/* Set the next state */
					Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_RD_ROB_PAGE_WAIT_E;

					/* Increment the read address for the next Fls access (overflow is checked automatically) */
					Fee_IncAddressInsideSector(&Fee_RdWrOrder_st.xCrcAddress, xNumBytes_u16, FALSE);
				}
				else
				{
					/* Abort the function due to invalid Fls parameters or a busy Fls */
					xRetVal_en = FEE_ABORTED_E;
				}
			}
			else
			{
				/* Reading is finished, compare the checksums */
				if(xBlkRobCrc32_u32 == xBlkCrc32_u32)
				{
					/* Update the address in the cache (the function will not change any
					 * entries in case an unknown block is checked during an
					 * "afterburner" run in the reorganization) */
					Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16,
											   HeaderInfo_pcst->AdrBlkHeader_u32);


					/* The calculated checksum is equal compared to the checksum in the block header */
					xRetVal_en = FEE_ORDER_FINISHED_E;
				}
				else
				{
					/* Check the necessity of marking the cache as temporary invalid.
					 * This is necessary in all cases (standard read and sector reorg for known blocks)
					 * besides a forced read action. An update of the cache for unkown blocks during the
					 * sector reorganization does not effect the cache. */
					if((Fee_Rb_WorkingState_en == FEE_RB_READ_MODE_E) &&
					   (Fee_OrderFifo_st[Fee_idxActQueue_u8].Mode_en == FEE_FORCED_READ_ORDER))
					{
						/* Do not mark the cache as temporary invalid for not loosing the block
						 * during a reorganization after an interruption */
						;
					}
					else
					{
						/* Update the cache */
						Fee_LLUpdateAddressInCache(HeaderInfo_pcst->FeeIndex_u16,
												   FEE_CACHE_TMP_INVALID_VALUE);
					}

					/* Set return value */
					xRetVal_en = FEE_ERROR_E;
				}
			}
		}
		break;
		/* FEE_ROB_FEATURE_ACTIVE != FALSE */
		#endif

		/* Default state should never be reached */
		default:
		{
			/* Check if this is a "standard" reorganization case */
			if(Fee_Prv_stReorg_u8 == FEE_PRV_ST_REORG_STANDARD_RUNNING)
			{
				/* Invalidate the cache entry (this is important for the
				 * sector reorganization. The cache should never point into an
				 * erased sector. This block will be skipped anyhow and
				 * the eldest FULL sector will be erased afterwards) */
				Fee_LLInvalidateAddressInCache(HeaderInfo_pcst->FeeIndex_u16);
			}

			/* Set return value (wrong Fls access and default is the
			 * same return for this function) */
			xRetVal_en = FEE_ABORTED_E;
		}
		break;
	}

    /* Check the function return */
    if(xRetVal_en != FEE_ORDER_PENDING_E)
    {
        /* Reset the state machine */
        Fee_RdWrOrder_st.Fee_LLCalcCrcBlk_en = FEE_LL_CRC_BLK_INIT_E;

        /* Retries for reading the header and the data */
        Fee_RdWrRetries_u8 = FEE_MAX_RD_WR_COMP_RETRIES;

        #if(FEE_ROB_FEATURE_ACTIVE != FALSE)
        /* Init the robustness checksum */
        xBlkRobCrc32_u32 = 0;
        #endif

        /* Init the array index */
        xConfigPropTableIdx_u16 = 0;
    }

    return (xRetVal_en);
}


/**
 *********************************************************************
 * Fee_CalculateNumOfFreeBytesInCurSector(): Calculate the amount of
 *              bytes until the end of the respective sector is reached
 *
 * This function calculates the amount of bytes until the respective
 * sector end address is reached depending on the user address.
 *
 * \param    DataEndAdr_u32:        Last data address within one sector
 *
 * \return   Function result
 * \retval   xNumFreeBytes_u32:     Number of free bytes until the
 *                                  sector end address
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_CalculateNumOfFreeBytesInCurSector(VAR(uint32, FEE_VAR) DataEndAdr_u32)
{
    VAR(uint8, AUTOMATIC)  xPhySecIdx_u8;               /* Physical sector index */
    VAR(uint32, AUTOMATIC) xNumFreeBytes_u32;           /* Amount of free bytes */

    /* Get the corresponding physical sector index */
    xPhySecIdx_u8 = Fee_GetPhysSectorByAddress(DataEndAdr_u32);

    /* Calculate the number of bytes until the sector end address is reached */
    xNumFreeBytes_u32 = (Fee_FlashProp_st[xPhySecIdx_u8].Fee_PhysEndAddress_u32 + 1u) - DataEndAdr_u32;

    /* Do only consider complete pages */
    if(xNumFreeBytes_u32 < FEE_PAGE_LEN)
    {
        /* Reset the amount of bytes because only complete pages can be written */
        xNumFreeBytes_u32 = 0;
    }

    return (xNumFreeBytes_u32);
}


/**
 *********************************************************************
 * Fee_CheckFlsJobResult(): Poll the Fls job result
 *
 * This function polls the Fls job result in case the callback
 * notifications are not used and the polling module's polling mode
 * is used instead.
 *
 * \param    none
 * \return   none
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
#if (STD_ON == FEE_POLLING_MODE)
FUNC(void, FEE_CODE) Fee_CheckFlsJobResult(void)
{
    VAR(MemIf_JobResultType, AUTOMATIC) FlsJobResult = MEMIF_JOB_PENDING;

    /* Get the job result of the last Fls order */
	FlsJobResult = Fls_GetJobResult();

	/* Check if the result is still pending or not */
	if(FlsJobResult != MEMIF_JOB_PENDING)
	{
        /* The last order was finished with or without success,
         * it is possible to check the result now */
        if(FlsJobResult == MEMIF_JOB_OK)
		{
            /* Job was finished without any errors, call the Fee internal
             * function to switch the respective state machine */
            Fee_SwitchJobEndNotification();
        }
		else
		{
            /* Job was finished with an error, call the Fee internal
             * function to switch the respective state machine */
            Fee_SwitchJobErrorNotification();
        }
    }
}

/* FEE_POLLING_MODE */
#endif

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
