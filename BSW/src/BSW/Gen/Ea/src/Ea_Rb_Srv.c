

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */
#include "Ea.h"

#if (EA_PRESENT == 1)
/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Ea_Cfg_SchM.h"
#include "Ea_Prv.h"
#include "Crc.h"

#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
/* Check if migration header changed */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
boolean Ea_Rb_isMigHeaderDiff_b;
#endif
boolean Ea_Rb_MigClipUpdate_b;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"
    uint32 Ea_Rb_BlockData_CS_u32;
#define EA_STOP_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
Eep_AddressType Ea_Rb_BlockOffset_uo;
Eep_AddressType Ea_Rb_BlankStart_uo;     /* Blank area start address of survival blocks */
Eep_AddressType Ea_Rb_BlankLen_uo;       /* Blank area length of survival blocks */
static Ea_Rb_Order_tst Ea_Rb_OrderLoc_st;
static Ea_Rb_BlockHeader_tst Ea_Rb_BlockHeaderLoc_st;
static Ea_Rb_MigOrder_tst Ea_Rb_MigOrderLoc_st;
static Ea_Rb_SurvivalBlockOffset_tst Ea_Rb_Offset_st;
Ea_Rb_MigClipDetails_tst Ea_Rb_MigClipDetails_st;
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
Ea_Rb_SurvBlksHandling_tst Ea_Rb_SurvBlksHandling_st;
#endif
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"

/**
 *********************************************************************
 * Ea_Rb_CheckBlockValid()
 *
 * This function checks the block with start address if block header and
 * block data both valid.
 *
 * \param   adStart: start address of block, which to be checked
 * \param   hdrFromOrder_st: block header information from the order side
 * \param   isFirstCall_b: first function call or not:
 *          TRUE: first call, set the check order from parameter
 *          FALSE: not the first call, continue the check cyclically
 * \return  status of check
 * \retval  stRet: result of check
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_CheckBlockValid(uint32 adStart, Ea_Rb_BlockHeader_tst* hdrFromOrder_st, Ea_Rb_Request_ten RequestOrder_en, boolean isFirstCall_b)
{
    Ea_Rb_stReturn_ten stRet            = EA_RB_ST_INIT_E;
    Std_ReturnType stRetLoc_u8          = E_NOT_OK;
    MemIf_JobResultType stJobResult_en  = MEMIF_JOB_OK;
    boolean stDataToBeChecked_b         = TRUE;
    boolean isHeaderCRCValidLoc_b       = FALSE;
	/* TRUE: Difference found between write buffer and existing eeprom data for the block*/
	static boolean s_isDataDiffFound_b	= FALSE;
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    uint8* ptrSurvivalOff               = (uint8*)&Ea_Rb_Offset_st;
	/* Compare the Write data with existing Eeprom data. Used only for write request */
	static const uint8*        s_dataWrBufComp_pcu8 = NULL_PTR;
    uint8 num_u8;
    uint16 num_u16;
	uint16 index_u16;

    if(isFirstCall_b)
    {
        Ea_Rb_OrderLoc_st.adStart_uo = adStart;
		s_isDataDiffFound_b		= FALSE;	/* clear the Flag while starting a new request	*/



        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, (uint8 *)&Ea_Rb_BlockHeaderLoc_st, EA_BLK_HEADER_SIZE);

        if(stRetLoc_u8 == E_OK)
        {
            /* Init */
            Ea_Rb_BlockData_CS_u32 	= 0;
			/* Clear the Flag while starting a new request													 *
			 * This clearing is needed because checkblockvalid is called for both user request and Migration */
			Ea_Rb_isDataCrcZero_b 	= FALSE;
			Ea_Rb_BlockOffset_uo 	= 0;
            Ea_Rb_OrderLoc_st.OrderType_en      = EA_RB_READ_HEADER_E;
            Ea_Rb_OrderLoc_st.RequestOrder_en   = RequestOrder_en;
            Ea_Rb_OrderLoc_st.numID_u16         = hdrFromOrder_st->BlockID_u16;
            stRet = EA_RB_ST_OK_E;
        }
        else
        {
            stRet = EA_RB_ST_ERROR_E;
        }
    }
    else
    {
        switch(Ea_Rb_OrderLoc_st.OrderType_en)
        {
            case EA_RB_READ_HEADER_E:
                /* Get current job result of Eep */
                stJobResult_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stJobResult_en == MEMIF_JOB_OK)
                {
                    /* Successful header read */

                    /* Check the header CRC valid status */
                    isHeaderCRCValidLoc_b = Ea_Rb_HeaderCheck((const Ea_Rb_BlockHeader_tst*)&Ea_Rb_BlockHeaderLoc_st);

                    /* Check:
                     * -- Block header valid;
                     * -- By block processing, the read block persistent ID should be equal to ordered persistent ID;
                     * -- In case of migration block valid check: ordered persistent ID should be zero;
                     * -- In case of survival block searching, read reserved block (Persistent ID: 0xFFFF) at first;
                     * */
                    if(isHeaderCRCValidLoc_b
                            && ((Ea_Rb_BlockHeaderLoc_st.BlockID_u16 == hdrFromOrder_st->BlockID_u16)
                                    || (Ea_Rb_OrderLoc_st.numID_u16 == 0)
                                    || (Ea_Rb_BlockHeaderLoc_st.BlockID_u16 == (uint16)EA_RESERVED_BLK_ID)))
                    {
                        if((Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32 == 0u) && (Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16 == 0u))
                        {
                            /* No need to check data */
                            stDataToBeChecked_b = FALSE;

                            /* Don't need to set the block version because the current one is zero:
                             * -- If redundant block, 1. copy has higher version: keep it
                             * -- If redundant block, 1. copy has version 0: keep it
                             * -- If no redundant block, block version has been initialized to zero: keep it */
                            hdrFromOrder_st->BlockVersion_u16 = 0;

                            /* Version=0: this block has never been written, return with EA_RB_ST_OK_E */
                            Ea_Rb_BlockData_CS_u32 = 0;
							Ea_Rb_isDataCrcZero_b 	= FALSE;
                            stRet = EA_RB_ST_OK_E;
                        }

                        if(Ea_Rb_BlockHeaderLoc_st.BlockID_u16 == (uint16)EA_RESERVED_BLK_ID)
                        {
                            /* Search the block */
                            stDataToBeChecked_b = TRUE;
                        }
                        else
                        {
                            /* Check redundant block: SL2 */
                            if((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
                            {
                                Ea_Rb_OrderLoc_st.isSecLevelCurr_b = TRUE;

                                if((hdrFromOrder_st->BlockVersion_u16 > Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16)
									&& ((Ea_Rb_BlockData1_CS_u32 > 0u)||(Ea_Rb_isData1CrcZero_b != FALSE)||(Ea_Rb_isLastDataValid_b != FALSE)))
                                {
                                    /* No need to check data */
                                    stDataToBeChecked_b = FALSE;
                                    Ea_Rb_BlockData_CS_u32 = 0;
									Ea_Rb_isDataCrcZero_b 	= FALSE;
									Ea_Rb_isLastDataValid_b = FALSE;  /* Clear the flag.This flag info is not needed further */
                                    stRet = EA_RB_ST_OK_E;
                                }
                                else if((hdrFromOrder_st->BlockVersion_u16 == Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16)
									&& ((Ea_Rb_BlockData1_CS_u32 > 0u)||(Ea_Rb_isData1CrcZero_b != FALSE)||(Ea_Rb_isLastDataValid_b != FALSE)))
                                {
									Ea_Rb_isLastDataValid_b = FALSE;  /* Clear the flag.This flag info is not needed further */

                                    /* For maintain request: the second copy should be checked even the first copy is the current valid one */
                                    if((Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_MAINTAIN_E) || (Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_WRITE_E))
                                    {
                                        /* The second copy data should be checked even if
                                         * -- the first copy has the same version number and
                                         * -- the first copy with data valid */

                                        /* Check if this is an invalidate order */
                                        if((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0)
                                        {
                                            /* To invalidate the block: no need to check block data */
                                            stDataToBeChecked_b = FALSE;

                                            Ea_Rb_BlockData_CS_u32 = Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32;

                                            stRet = EA_RB_ST_INVALIDATED_E;
                                        }
                                        else
                                        {
                                            stDataToBeChecked_b = FALSE;
                                            Ea_Rb_BlockData_CS_u32 = 0;
											Ea_Rb_isDataCrcZero_b 	= FALSE;
                                            stRet = EA_RB_ST_OK_E;
                                        }
                                    }
                                    else
                                    {
                                        /* Higher version available: no need to check this block data for read order */
                                        stDataToBeChecked_b = FALSE;
                                        Ea_Rb_BlockData_CS_u32 = 0;
										Ea_Rb_isDataCrcZero_b 	= FALSE;
                                        stRet = EA_RB_ST_OK_E;
                                    }
                                }
                                else
                                {
                                    /* Check if this is an invalidate order */
                                    if((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0)
                                    {
                                        hdrFromOrder_st->BlockVersion_u16 = Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16;

                                        /* To invalidate the block: no need to check block data */
                                        stDataToBeChecked_b = FALSE;

                                        Ea_Rb_BlockData_CS_u32 = Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32;

                                        stRet = EA_RB_ST_INVALIDATED_E;
                                    }
                                }
                            }
                            else
                            {
                                Ea_Rb_OrderLoc_st.isSecLevelCurr_b = FALSE;

                                /* Check if this is an invalidated block */
                                if((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0)
                                {
                                    hdrFromOrder_st->BlockVersion_u16 = Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16;

                                    Ea_Rb_BlockData_CS_u32 = Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32;

                                    /* To invalidate the block: no need to check block data */
                                    stDataToBeChecked_b = FALSE;

                                    stRet = EA_RB_ST_INVALIDATED_E;
                                }
                                else
                                {
                                    /* In case write the different data */
                                    if((Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_WRITE_E) && (Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32 != hdrFromOrder_st->BlockData_CS_u32))
                                    {
                                        /* No-Redundant block writing: no need to read data if checksum difference detected between them */

                                        hdrFromOrder_st->BlockVersion_u16 = Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16;

                                        Ea_Rb_BlockData_CS_u32 = 0;
										Ea_Rb_isDataCrcZero_b 	= FALSE;
                                        stDataToBeChecked_b = FALSE;
                                        stRet = EA_RB_ST_OK_E;
                                    }
                                }
                            }
                        }

                        /* Start to check the data */
                        if(stDataToBeChecked_b)
                        {
                            hdrFromOrder_st->BlockVersion_u16 = Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16;

                            /* Header valid --> Start to read data and calculate the CRC32 */
                            Ea_Rb_OrderLoc_st.adStart_uo    += EA_BLK_HEADER_SIZE;
                            Ea_Rb_OrderLoc_st.numBytes_u16   = Ea_Rb_BlockHeaderLoc_st.BlockLen_u16;
                            Ea_Rb_BlockData_CS_u32          = Ea_Rb_BlockHeaderLoc_st.BlockID_u16;
							s_dataWrBufComp_pcu8             = Ea_Rb_Order_st.Buffer_un.Write_pcu8;

                            if(Ea_Rb_OrderLoc_st.numBytes_u16 < EA_DATA_BUFFER_SIZE)
                            {
                                Ea_Rb_numBytesTmp_u16 = Ea_Rb_OrderLoc_st.numBytes_u16;
                            }
                            else
                            {
                                Ea_Rb_numBytesTmp_u16 = EA_DATA_BUFFER_SIZE;
                            }

                            stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, &Ea_Rb_dDataBuf_u8[0], Ea_Rb_numBytesTmp_u16);

                            if(stRetLoc_u8 == E_OK)
                            {
                                Ea_Rb_OrderLoc_st.OrderType_en = EA_RB_READ_ORDER_E;
                                stRet = EA_RB_ST_PENDING_E;
                            }
                            else
                            {
                                stRet = EA_RB_ST_ERROR_E;
                            }
                        }
                    }
                    else
                    {
                        /* No valid header, rest block version */
                        hdrFromOrder_st->BlockVersion_u16 = 0;

                        Ea_Rb_BlockData_CS_u32 = 0;
						Ea_Rb_isDataCrcZero_b 	= FALSE;

						if(Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_WRITE_E)
						{	/* This check is needed if 2nd copy header is invalid to clear the previous status */
							/* This applicable only for write request */
							Ea_Rb_isLastDataValid_b = FALSE;
						}

                        if(isHeaderCRCValidLoc_b && (Ea_Rb_BlockHeaderLoc_st.BlockID_u16 != hdrFromOrder_st->BlockID_u16))
                        {
                            stRet = EA_RB_ST_WRONG_ID_E;
                        }
                        else
                        {
                            stRet = EA_RB_ST_OK_E;
                        }
                    }
                }
                else if(stJobResult_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                    stRet = EA_RB_ST_PENDING_E;
                }
                else
                {
                    stRet = EA_RB_ST_ERROR_E;
                }

                break;

            case EA_RB_READ_ORDER_E:
                /* Get current job result of Eep */
                stJobResult_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stJobResult_en == MEMIF_JOB_OK)
                {
                    /* Set default return value */
                    stRet = EA_RB_ST_PENDING_E;

                    /* Disable interrupts */
                    SchM_Enter_Ea_Order();

                    /* Reserved block, find the survival block in read data */
                    if((Ea_Rb_BlockHeaderLoc_st.BlockID_u16 == (uint16)EA_RESERVED_BLK_ID)
                            && (hdrFromOrder_st->BlockID_u16 != 0)
                            && (Ea_Rb_BlockOffset_uo == 0u))
                    {
                        /* Transfer the read data to survival block offset */
                        for(num_u16=0; ((num_u16 + (uint8)sizeof(Ea_Rb_SurvivalBlockOffset_tst))<=Ea_Rb_numBytesTmp_u16); num_u16+=(uint8)sizeof(Ea_Rb_SurvivalBlockOffset_tst))
                        {
                            /* Copy the data to survival offset structure, real useful data only 6 Bytes */
                            for(num_u8=0; num_u8<((uint8)sizeof(Ea_Rb_SurvivalBlockOffset_tst)-2); num_u8++)
                            {
                                *(ptrSurvivalOff+num_u8) = Ea_Rb_dDataBuf_u8[num_u16+num_u8];
                            }

                            /* Looking for the survival block */
                            if(Ea_Rb_Offset_st.SurvivalBlockID_u16 == Ea_Rb_OrderLoc_st.numID_u16)
                            {
                                /* Found: set the global label for offset */
                                Ea_Rb_BlockOffset_uo  = Ea_Rb_Offset_st.BlockOffset_uo;
                                break;
                            }
                        }
                    }

                    /* Enable interrupts */
                    SchM_Exit_Ea_Order();

                    /* Order length is equal to block length, no data has been read:
                     * it is the first time to calculate the CRC, initialize it only once here */
                    if(Ea_Rb_OrderLoc_st.numBytes_u16 == Ea_Rb_BlockHeaderLoc_st.BlockLen_u16)
                    {
                        /* Initialize block data checksum with persistent ID */
                        Ea_Rb_BlockData_CS_u32 = (uint32)Ea_Rb_BlockHeaderLoc_st.BlockID_u16;

                        /* Reflect the start value for next CRC32 calculate */
                        Ea_Rb_BlockData_CS_u32 ^= EA_CRC_XOR_VALUE32;
                    }

					/* Compare the user write data buffer with existing Eeprom data due to CRC algorithm limitation : Reference Err5321 */
					/* if  difference found, set the flag, the user data should be written to the Eeprom */
					/* Persistent ID should not be 0x0 or 0xFFFF for user Request */
					if ((Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_WRITE_E) && (Ea_Rb_BlockHeaderLoc_st.BlockID_u16 != (uint16)EA_RESERVED_BLK_ID) && (hdrFromOrder_st->BlockID_u16 != 0u) && (s_dataWrBufComp_pcu8 != NULL_PTR))
					{
						for (index_u16 = 0; ((index_u16 < Ea_Rb_numBytesTmp_u16) && (s_isDataDiffFound_b != TRUE)) ; index_u16++)
						{
							if((*(s_dataWrBufComp_pcu8 + index_u16)) != Ea_Rb_dDataBuf_u8[index_u16])
							{
							    s_isDataDiffFound_b = TRUE;
							}
						}

						s_dataWrBufComp_pcu8            += Ea_Rb_numBytesTmp_u16;
					}

                    /* Check the CRC_32 of data block */
                    Ea_Rb_BlockData_CS_u32 = Crc_CalculateCRC32(&Ea_Rb_dDataBuf_u8[0],
                                                                         Ea_Rb_numBytesTmp_u16,
                                                                         Ea_Rb_BlockData_CS_u32,
                                                                         FALSE);

                    /* Update actual start address and rest length */
                    Ea_Rb_OrderLoc_st.numBytes_u16  -= Ea_Rb_numBytesTmp_u16;
                    Ea_Rb_OrderLoc_st.adStart_uo    += Ea_Rb_numBytesTmp_u16;

                    if(Ea_Rb_OrderLoc_st.numBytes_u16 == 0u)
                    {
						if(Ea_Rb_BlockData_CS_u32 == Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32)
                        {
							/* Ea module is not working properly when the CRC for the user data is zero.       	    *
							 * For more details refer Errata5405, so we are setting special flag for CRC0 case 	    */
							if(Ea_Rb_BlockHeaderLoc_st.BlockData_CS_u32 == 0u)
							{
								Ea_Rb_isDataCrcZero_b = TRUE;
							}
                            /* For maintain request: no need to change the status bit if the first copy is the valid one (with same or higher copy) */
                            if((Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_MAINTAIN_E) && ((Ea_Rb_BlockData_CS_u32 > 0u)||(Ea_Rb_isDataCrcZero_b != FALSE)))
                            {
                                /* block header and data both valid */
                                stRet = EA_RB_ST_OK_E;
                            }
                            else
                            {
                                /* Update current block header including version */
                                hdrFromOrder_st->BlockVersion_u16 = Ea_Rb_BlockHeaderLoc_st.BlockVersion_u16;

								/* The below conditional check is applicable only for user write request */
                                if (s_isDataDiffFound_b != FALSE)
								{
									Ea_Rb_BlockData_CS_u32  = 0;		/* This indicates user data and Eeprom content are not same block write is needed  */
									/* Ea_Rb_isLastDataValid_b flag is needed for redundent block to decide which version should be written first   *
									 * This flag is applicable only for write request																*/
									if((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
									{
										Ea_Rb_isLastDataValid_b = TRUE;
									}

									s_isDataDiffFound_b = FALSE;
								}

                                /* block header and data both valid */
                                stRet = EA_RB_ST_OK_E;
                            }
                        }
                        else
                        {
                            /* Update current block data checksum with 0 because of invalid data */
                            Ea_Rb_BlockData_CS_u32      = 0;

							if((Ea_Rb_OrderLoc_st.RequestOrder_en == EA_RB_WRITE_E)&&((Ea_Rb_BlockHeaderLoc_st.BlockFlags_u8 & (uint8)EA_SECURITY_LEVEL_FLAG) > 0))
							{	/* This check is needed if 2nd copy data is invalid to clear the previous status */
								Ea_Rb_isLastDataValid_b = FALSE;
							}

                            stRet = EA_RB_ST_OK_E;
                        }
                    }
                    else
                    {
                        /* Check the rest block length to be read */
                        if(Ea_Rb_OrderLoc_st.numBytes_u16 < EA_DATA_BUFFER_SIZE)
                        {
                            Ea_Rb_numBytesTmp_u16 = Ea_Rb_OrderLoc_st.numBytes_u16;
                        }
                        else
                        {
                            Ea_Rb_numBytesTmp_u16 = EA_DATA_BUFFER_SIZE;
                        }

                        /* Read the next buffer size data */
                        stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo,
                                                  &Ea_Rb_dDataBuf_u8[0],
                                                  Ea_Rb_numBytesTmp_u16);

                        if(stRetLoc_u8 == E_OK)
                        {
                            stRet = EA_RB_ST_PENDING_E;
                        }
                        else
                        {
                            Ea_JobResult = MEMIF_JOB_FAILED;
                            stRet = EA_RB_ST_ERROR_E;
                        }
                    }
                }
                else if(stJobResult_en == MEMIF_JOB_PENDING)
                {
                    stRet = EA_RB_ST_PENDING_E;
                }
                else
                {
                    Ea_JobResult = MEMIF_JOB_FAILED;
                    stRet = EA_RB_ST_ERROR_E;
                }
                break;

            default:
                /* Default state, no action required */
                break;
        }
    }

    return stRet;
}

/**
 *********************************************************************
 * Ea_Rb_MigMoveBlock()
 *
 * This function moves one block from current read address to write address.
 * All the data will be compared after every movement. At the end the source
 * block can be deleted after order requirement
 *
 * \param   MigOrder_pst: pointer for current order
 * \param   isFirstCall_b: first function call or not:
 *          TRUE: first call, set the check order from parameter
 *          FALSE: not the first call, continue the moving cyclically
 * \return  status of check
 * \retval  stRet: result of moving
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_MigMoveBlock(const Ea_Rb_MigOrder_tst * MigOrder_pst, boolean bFirstCall)
{
    Ea_Rb_stReturn_ten stRetLoc = EA_RB_ST_PENDING_E;
    MemIf_JobResultType stEepJobResultLoc_en;
    Std_ReturnType stRetSub;

    if(bFirstCall)
    {
        /* Check all needed parameters available */
        if((MigOrder_pst->adReadStart_uo != 0u) && (MigOrder_pst->adWriteStart_uo != 0u) && (MigOrder_pst->numBytes_uo!= 0u))
        {
            /* Load the global order to local order which is reserved only for this moving */
            Ea_Rb_MigOrderLoc_st.adReadStart_uo     = MigOrder_pst->adReadStart_uo;
            Ea_Rb_MigOrderLoc_st.adWriteStart_uo    = MigOrder_pst->adWriteStart_uo;
            Ea_Rb_MigOrderLoc_st.numBytes_uo        = MigOrder_pst->numBytes_uo;
            Ea_Rb_MigOrderLoc_st.isToBeErase_b      = MigOrder_pst->isToBeErase_b;
            Ea_Rb_MigOrderLoc_st.isMoveToEepEnd_b   = MigOrder_pst->isMoveToEepEnd_b;
            Ea_Rb_MigOrderLoc_st.isSecLevelCurr_b   = MigOrder_pst->isSecLevelCurr_b;

            /* In case of erasing source block: start address and block length should be stored at first*/
            if(Ea_Rb_MigOrderLoc_st.isToBeErase_b)
            {
                Ea_Rb_MigOrderLoc_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigOrderLoc_st.numBytes_uo);
            }

            /* Start to read the data to buffer, check to be moved data size with buffer size */
            if(Ea_Rb_MigOrderLoc_st.numBytes_uo >= EA_DATA_BUFFER_SIZE)
            {
                Ea_Rb_MigOrderLoc_st.numTrsBytes_uo = EA_DATA_BUFFER_SIZE;
            }
            else
            {
                Ea_Rb_MigOrderLoc_st.numTrsBytes_uo = Ea_Rb_MigOrderLoc_st.numBytes_uo;
            }

            /* Read the first block data */
            stRetSub = EA_EEP_READ(Ea_Rb_MigOrderLoc_st.adReadStart_uo,
                                      &Ea_Rb_dMigDataBuf_u8[0],
                                      Ea_Rb_MigOrderLoc_st.numTrsBytes_uo);

            if(stRetSub == E_OK)
            {
                /* Block exists in Eeprom, the data should be moved */
                Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_WRITE_E;

                stRetLoc = EA_RB_ST_OK_E;
            }
            else
            {
                stRetLoc = EA_RB_ST_ERROR_E;
            }
        }
        else
        {
            stRetLoc = EA_RB_ST_ERROR_E;
        }
    }
    else
    {
        switch(Ea_Rb_MigOrderLoc_st.MigOrderType_en)
        {
            case EA_RB_MIG_MOVING_READ_E:
                /* In this step, only data moving, header writing is finished */
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* Detect if data to be written */
                    if(Ea_Rb_MigOrderLoc_st.numBytes_uo > 0u)
                    {
                        if(Ea_Rb_MigOrderLoc_st.numBytes_uo >= EA_DATA_BUFFER_SIZE)
                        {
                            Ea_Rb_MigOrderLoc_st.numTrsBytes_uo = EA_DATA_BUFFER_SIZE;
                        }
                        else
                        {
                            Ea_Rb_MigOrderLoc_st.numTrsBytes_uo = Ea_Rb_MigOrderLoc_st.numBytes_uo;
                        }

                        /* Read the first block data */
                        stRetSub = EA_EEP_READ(Ea_Rb_MigOrderLoc_st.adReadStart_uo,
                                                  &Ea_Rb_dMigDataBuf_u8[0],
                                                  Ea_Rb_MigOrderLoc_st.numTrsBytes_uo);

                        if(stRetSub == E_OK)
                        {
                            /* Block exists in Eeprom, the data should be moved */
                            Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_WRITE_E;
                        }
                        else
                        {
                            stRetLoc = EA_RB_ST_ERROR_E;
                        }
                    }
                    else
                    {
                        /* In case of erasing the source block */
                        if(Ea_Rb_MigOrderLoc_st.isToBeErase_b)
                        {
                            Ea_Rb_MigOrderLoc_st.adReadStart_uo -= Ea_Rb_MigOrderLoc_st.numAlignedBytes_uo;

                            /* Erase the source block */
                            stRetSub = Eep_Erase(Ea_Rb_MigOrderLoc_st.adReadStart_uo, Ea_Rb_MigOrderLoc_st.numAlignedBytes_uo);

                            if(stRetSub == E_OK)
                            {
                                Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_DELETE_E;
                            }
                            else
                            {
                                stRetLoc = EA_RB_ST_ERROR_E;
                            }
                        }
                        else
                        {
                            stRetLoc = EA_RB_ST_OK_E;
                        }
                    }
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    stRetLoc = EA_RB_ST_ERROR_E;
                }
                break;

            case EA_RB_MIG_MOVING_WRITE_E:
                /* In this step, only data moving, header writing is finished */
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* Write block data to the right address */
                    stRetSub = EA_EEP_WRITE(Ea_Rb_MigOrderLoc_st.adWriteStart_uo,
                                              (const uint8*)&Ea_Rb_dMigDataBuf_u8[0],
                                              Ea_Rb_MigOrderLoc_st.numTrsBytes_uo);
                    if(stRetSub == E_OK)
                    {
                        /* Compare the copied the data, check if they are equal */
                        Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_COMPARE_E;
                    }
                    else
                    {
                        stRetLoc = EA_RB_ST_ERROR_E;
                    }
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    stRetLoc = EA_RB_ST_ERROR_E;
                }
                break;

            case EA_RB_MIG_MOVING_COMPARE_E:
                /* In this step, only data moving, header writing is finished */
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* Write block data to the right address */
                    stRetSub = Eep_Compare(Ea_Rb_MigOrderLoc_st.adWriteStart_uo,
                                              (const uint8*)&Ea_Rb_dMigDataBuf_u8[0],
                                              Ea_Rb_MigOrderLoc_st.numTrsBytes_uo);
                    if(stRetSub == E_OK)
                    {
                        /* Wait until the compare is finished, check if they are equal */
                        Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_WAIT_E;
                    }
                    else
                    {
                        stRetLoc = EA_RB_ST_ERROR_E;
                    }
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    stRetLoc = EA_RB_ST_ERROR_E;
                }
                break;

            case EA_RB_MIG_MOVING_WAIT_E:
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* In case of SL2 moving, check if it's moving to clip board:
                     * yes: no need to move the second copy version
                     * no: move it twice to the right address */
                    if(Ea_Rb_MigOrderLoc_st.isSecLevelCurr_b && !Ea_Rb_MigOrderLoc_st.isMoveToEepEnd_b)
                    {
                        if(!Ea_Rb_MigOrderLoc_st.isCopyWritten_b)
                        {
                            Ea_Rb_MigOrderLoc_st.adWriteStart_uo    += Ea_Rb_MigOrderLoc_st.numAlignedBytes_uo;
                            Ea_Rb_MigOrderLoc_st.isCopyWritten_b    = TRUE;

                            /* Write the second copy again */
                            Ea_Rb_MigOrderLoc_st.MigOrderType_en    = EA_RB_MIG_MOVING_WRITE_E;
                        }
                        else
                        {
                            Ea_Rb_MigOrderLoc_st.isCopyWritten_b    = FALSE;

                            Ea_Rb_MigOrderLoc_st.adWriteStart_uo    -= Ea_Rb_MigOrderLoc_st.numAlignedBytes_uo;

                            /* After reading, load new read address */
                            Ea_Rb_MigOrderLoc_st.adReadStart_uo     += Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;

                            Ea_Rb_MigOrderLoc_st.adWriteStart_uo    += Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;
                            Ea_Rb_MigOrderLoc_st.numBytes_uo        -= Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;

                            /* Block exists in Eeprom, the data should be moved */
                            Ea_Rb_MigOrderLoc_st.MigOrderType_en    = EA_RB_MIG_MOVING_READ_E;
                        }
                    }
                    else
                    {
                        /* After reading, load new read address */
                        Ea_Rb_MigOrderLoc_st.adReadStart_uo     += Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;

                        Ea_Rb_MigOrderLoc_st.adWriteStart_uo += Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;
                        Ea_Rb_MigOrderLoc_st.numBytes_uo -= Ea_Rb_MigOrderLoc_st.numTrsBytes_uo;

                        /* Block exists in Eeprom, the data should be moved */
                        Ea_Rb_MigOrderLoc_st.MigOrderType_en = EA_RB_MIG_MOVING_READ_E;
                    }
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */

                }
                else if(stEepJobResultLoc_en == MEMIF_BLOCK_INCONSISTENT)
                {
                    /* Data not equal: copy it again */
                    /* Wrong data copied, the data should be moved again */
                    Ea_Rb_MigOrderLoc_st.MigOrderType_en    = EA_RB_MIG_MOVING_READ_E;
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    stRetLoc = EA_RB_ST_ERROR_E;
                }
                break;

            case EA_RB_MIG_MOVING_DELETE_E:
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    stRetLoc = EA_RB_ST_OK_E;
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    stRetLoc = EA_RB_ST_ERROR_E;
                }
                break;

            default:
                stRetLoc = EA_RB_ST_ERROR_E;
                break;
        }
    }
    return stRetLoc;
}

/**
 *********************************************************************
 * Ea_Rb_MigCheckResult()
 *
 * This function compares all the blocks on current layout with configured
 * layout. Non-survival blocks should be identical to configured status.
 * Survival blocks should be in permanent area.
 *
 * \param   none
 * \return  the resuslt ok for identical feature
 * \retval  stRet: result of check
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
boolean Ea_Rb_MigCheckResult(void)
{
    uint16 cnt_i;
    boolean isRet_b = TRUE;

    /* check all blocks if Layout == configuration:
     * Any mismatch: start migration or migration unsuccessfully finished */
    for(cnt_i=0; cnt_i<EA_NUM_BLOCKS;cnt_i++)
    {
        /* For all non-survival blocks: all parameters should be identical
         * For all survival blocks extra checks needed */
        if((((Ea_BlockProperties[cnt_i].Flags & (uint8)EA_SURVIVAL_FLAG) == 0)
            && (!(((((Ea_BlockProperties_onEep[cnt_i].BlkStartAddr == Ea_BlockProperties[cnt_i].BlkStartAddr)
                &&(Ea_BlockProperties_onEep[cnt_i].BlkEndAddr   == Ea_BlockProperties[cnt_i].BlkEndAddr))
                &&(Ea_BlockProperties_onEep[cnt_i].NvMIdx       == Ea_BlockProperties[cnt_i].NvMIdx))
                &&(Ea_BlockProperties_onEep[cnt_i].Length       == Ea_BlockProperties[cnt_i].Length))
                &&(Ea_BlockProperties_onEep[cnt_i].Flags        == Ea_BlockProperties[cnt_i].Flags))))
           ||(((Ea_BlockProperties[cnt_i].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
               &&(!(((Ea_BlockProperties_onEep[cnt_i].NvMIdx         == Ea_BlockProperties[cnt_i].NvMIdx)
                   &&(Ea_BlockProperties_onEep[cnt_i].BlkStartAddr  >= Ea_Rb_MigHeader_st.MigPerStartAddr_u32))
                   &&(Ea_BlockProperties_onEep[cnt_i].BlkEndAddr     == ((Ea_BlockProperties_onEep[cnt_i].BlkStartAddr + Ea_BlockProperties[cnt_i].BlkRealLen) - 1u))))))
        {
            isRet_b = FALSE;
            break;
        }
    }

    return isRet_b;
}

/**
 *********************************************************************
 * Ea_Rb_SearchBlock()
 *
 * This function searches the survival block and return the address offset
 * of found blocks.
 *
 * \param   adStart:        start address to be searched
 * \param   numSearchID:    block persistent ID to be searched
 * \param   bFirstCall:     TRUE for first call of this function
 * \return  offset of found block
 * \seealso
 * \usedresources
 *********************************************************************
 */
Eep_AddressType Ea_Rb_SearchBlock(Eep_AddressType adStart, uint16 numSearchID, boolean bFirstCall)
{
    Eep_AddressType offset_uo = 0;
    uint16 cnt_i;
    boolean isHeaderCRCValidLoc_b = FALSE;
    Std_ReturnType stRetLoc_u8;
    MemIf_JobResultType stEepJobResultLoc_en;

    if(bFirstCall)
    {
        Ea_Rb_OrderLoc_st.adStart_uo    = adStart;
        Ea_Rb_OrderLoc_st.numID_u16     = numSearchID;

        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, &Ea_Rb_dMigDataBuf_u8[0], EA_BLK_HEADER_SIZE);

        if(stRetLoc_u8 == E_OK)
        {
            Ea_Rb_OrderLoc_st.OrderType_en  = EA_RB_READ_ORDER_E;
            Ea_Rb_BlankStart_uo = Ea_Rb_OrderLoc_st.adStart_uo;
            Ea_Rb_BlankLen_uo   = 0;
        }
        else
        {
            /* Error return value */
            offset_uo = EA_MAXUINT32;
        }
    }
    else
    {
        switch(Ea_Rb_OrderLoc_st.OrderType_en)
        {
            case EA_RB_READ_ORDER_E:
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* Find a preambel in read header */
                    cnt_i = Ea_Rb_FindPreambelInHdr((const uint8*)&Ea_Rb_dMigDataBuf_u8[0], EA_BLK_HEADER_SIZE);

                    if((Ea_Rb_OrderLoc_st.adStart_uo + cnt_i) < Eep_Rb_RealSize_u32)
                    {
                        /* Shift start address to the next possible block header */
                        Ea_Rb_OrderLoc_st.adStart_uo += cnt_i;
                    }
                    else
                    {
                        /* Not found, error return value */
                        offset_uo = EA_MAXUINT32;
                    }

                    if(cnt_i == EA_BLK_HEADER_SIZE)
                    {
                        /* No preambel found: read the next possible address */

                        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                        stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, &Ea_Rb_dMigDataBuf_u8[0], EA_BLK_HEADER_SIZE);

                        if(stRetLoc_u8 == E_OK)
                        {
                            Ea_Rb_OrderLoc_st.OrderType_en = EA_RB_READ_ORDER_E;
                        }
                        else
                        {
                            /* Error return value */
                            offset_uo = EA_MAXUINT32;
                        }
                    }
                    else
                    {
                        /* Preambel for block header found --> read this block header */

                        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                        stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, (uint8 *)&Ea_Rb_BlockHeaderLoc_st, EA_BLK_HEADER_SIZE);

                        if(stRetLoc_u8 == E_OK)
                        {
                            Ea_Rb_OrderLoc_st.OrderType_en = EA_RB_READ_HEADER_E;
                        }
                        else
                        {
                            /* Error return value */
                            offset_uo = EA_MAXUINT32;
                        }
                    }

                    Ea_Rb_BlankLen_uo = Ea_Rb_OrderLoc_st.adStart_uo - Ea_Rb_BlankStart_uo;
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    /* Error return value */
                    offset_uo = EA_MAXUINT32;
                }
                break;

            case EA_RB_READ_HEADER_E:
                /* Get current job result of Eep */
                stEepJobResultLoc_en = Eep_GetJobResult();

                /* Check if the Eep job finished */
                if(stEepJobResultLoc_en == MEMIF_JOB_OK)
                {
                    /* Check the header CRC valid status */
                    isHeaderCRCValidLoc_b = Ea_Rb_HeaderCheck((const Ea_Rb_BlockHeader_tst*)&Ea_Rb_BlockHeaderLoc_st);

                    if(!isHeaderCRCValidLoc_b)
                    {
                        /* It isn't an invalid block header: search forward */
                        /* Shift start address to the next possible block header */
                        if((Ea_Rb_OrderLoc_st.adStart_uo + EA_BLK_HEADER_SIZE) < Eep_Rb_RealSize_u32)
                        {
                            Ea_Rb_OrderLoc_st.adStart_uo += EA_BLK_HEADER_SIZE;

                            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                            stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, &Ea_Rb_dMigDataBuf_u8[0], EA_BLK_HEADER_SIZE);

                            if(stRetLoc_u8 == E_OK)
                            {
                                Ea_Rb_OrderLoc_st.OrderType_en  = EA_RB_READ_ORDER_E;
                            }
                            else
                            {
                                /* Error return value */
                                offset_uo = EA_MAXUINT32;
                            }
                        }
                        else
                        {
                            /* Not found, error return value */
                            offset_uo = EA_MAXUINT32;
                        }
                    }
                    else
                    {
                        /* It is a valid block header */
                        /* It is the searched block */
                        if(Ea_Rb_BlockHeaderLoc_st.BlockID_u16 == Ea_Rb_OrderLoc_st.numID_u16)
                        {
                            /* Block found, load the offset_uo */
                            /* MR12 RULE 2.2 VIOLATION : The value "EEP_BASE_ADDRESS" is based on configuration, hence this operation needs to be performed */
                            offset_uo = (Eep_AddressType)(Ea_Rb_OrderLoc_st.adStart_uo - EEP_BASE_ADDRESS);
                        }
                        else
                        {
                            /* Update next search address */
                            Ea_Rb_OrderLoc_st.adStart_uo += Ea_Rb_CalcAlignedLen(Ea_Rb_BlockHeaderLoc_st.BlockLen_u16) + EA_BLK_HEADER_SIZE;

                            /* Reset black start address */
                            Ea_Rb_BlankStart_uo = Ea_Rb_OrderLoc_st.adStart_uo;

                            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                            stRetLoc_u8 = EA_EEP_READ(Ea_Rb_OrderLoc_st.adStart_uo, &Ea_Rb_dMigDataBuf_u8[0], EA_BLK_HEADER_SIZE);

                            if(stRetLoc_u8 == E_OK)
                            {
                                Ea_Rb_OrderLoc_st.OrderType_en  = EA_RB_READ_ORDER_E;
                            }
                            else
                            {
                                /* Error return value */
                                offset_uo = EA_MAXUINT32;
                            }
                        }
                    }
                }
                else if(stEepJobResultLoc_en == MEMIF_JOB_PENDING)
                {
                    /* Do nothing, just wait */
                }
                else
                {
                    /* If Eep Job failed or inconsistent */
                    /* Error return value */
                    offset_uo = EA_MAXUINT32;
                }
                break;

            default:
                /* Default state, no action required */
                break;
        }
    }

    return offset_uo;
}

/**
 *********************************************************************
 * Ea_Prv_SearchBlockInProp()
 *
 *This function searches the current block with given persistent ID in
 *given configuration properties.
 *
 * \param   stBlockProperties_apcst: search target block properties
 * \param   persistentID_u16:    current persistent ID to be searched
 * \return  if found: found block number in properties
 *          if not found: EA_NUM_BLOCKS
 * \seealso
 * \usedresources
 *********************************************************************
 */
uint16 Ea_Prv_SearchBlockInProp(Ea_BlockPropertiesType const* stBlockProperties_apcst, uint16 persistentID_u16)
{
    uint16 cnt_u16 = 0;

    /* Search the persistent ID in a known layout, find the block idex for it */
    for(cnt_u16 = 0; cnt_u16 < EA_NUM_BLOCKS; cnt_u16++)
    {
        /* Detected Block in the layout properties only if same block persistent ID */
        if(stBlockProperties_apcst[cnt_u16].NvMIdx == persistentID_u16)
        {
            break;
        }
    }

    return cnt_u16;
}

/**
 *********************************************************************
 * Ea_Rb_MigCheckCurrBlkNr():
 *
 * This function is called at the end of one block migration. Before it
 * gets ready for next block, the current block number should be checked
 * if the block number is still available:
 * yes: increment block number and continue the migration
 * no: migration finished
 *
 * \return   none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_MigCheckCurrBlkNr(void)
{
    /* Migrate the next block */
    if(Ea_Rb_MigCurNr_u16 > 0)
    {
        /* Decrement for next block to be migrated */
        Ea_Rb_MigCurNr_u16--;

        if(Ea_Rb_MigCurNr_u16 > 0)
        {
            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;

            if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
            {
                Ea_Rb_MigOrder_st.isSecLevelCurr_b = TRUE;
            }
            else
            {
                Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;
            }
        }
        else
        {
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
            /* Block compare and moving finished, update reserved block and layout header */
            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_FINISH_CHECK_1_E;
 #else
            /* Update layout header directly */
            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETE_BASECLIP_E;
 #endif
        }
    }
    else
    {
        /* Impossible to have block number with zero: error */
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
    }
}

/**
 *********************************************************************
 * Ea_Rb_MigCheckFreeAdr():
 *
 * This function checks if the address area for current block is free.
 * If not, return the first found overlap block number.
 * If yes, return block number zero.
 *
 * \param   currBlk_u16: current block number to be checked, if the address
 *                       area for this block are free or not.
 * \return  block number of first found block which is still on the need
 *          address
 * \retval  retVal_u16: block number
 * \seealso
 * \usedresources
 *********************************************************************
 */
uint16 Ea_Rb_MigCheckFreeAdr(uint16 currBlk_u16)
{
    uint16 i_cnt;
    uint16 retVal_u16 = 0;

    /* Load start address of target address area */
    Eep_AddressType srtAddr_u32 = Ea_BlockProperties[currBlk_u16-1].BlkStartAddr;

    /* Load end address of target address area */
    Eep_AddressType endAddr_u32 = Ea_BlockProperties[currBlk_u16-1].BlkEndAddr;

    if((srtAddr_u32 == 0u) && (endAddr_u32 == 0u))
    {
        /* No address generated for this block: survival block
         * No block should be moved, return 0 */
    }
    else
    {
        /* Loop all blocks, which haven't been migrated */
        for(i_cnt=Ea_Rb_MigCurNr_u16;i_cnt>0;i_cnt--)
        {
            /* Block found (should be moved away) if:
             * -- block start address locates in target address area or
             * -- block end address locates in target address area */
            if(((Ea_BlockProperties_onEep[i_cnt-1].BlkStartAddr >= srtAddr_u32) && (Ea_BlockProperties_onEep[i_cnt-1].BlkStartAddr <= endAddr_u32))
                || ((Ea_BlockProperties_onEep[i_cnt-1].BlkEndAddr >= srtAddr_u32) && (Ea_BlockProperties_onEep[i_cnt-1].BlkEndAddr <= endAddr_u32))
                || ((Ea_BlockProperties_onEep[i_cnt-1].BlkStartAddr <= srtAddr_u32) && (Ea_BlockProperties_onEep[i_cnt-1].BlkEndAddr >= endAddr_u32)))
            {
                retVal_u16 = i_cnt;
                break;
            }
        }
    }

    return retVal_u16;
}

/**
 *********************************************************************
 * Ea_Rb_CheckBlkInRightAddr():
 *
 * This function checks if the current block are already in the right address
 *
 * \param   currBlk_u16: current block number to be checked
 * \return  TRUE: this block is located on the right address
 *          FALSE: this block is not located on the right address, migration
 *                 needed
 * \retval  retVal_b: result of check
 * \seealso
 * \usedresources
 *********************************************************************
 */
boolean Ea_Rb_CheckBlkInRightAddr(uint16 numBlk_u16)
{
    boolean retVal_b = FALSE;

    if((Ea_BlockProperties[numBlk_u16-1].NvMIdx == Ea_BlockProperties_onEep[numBlk_u16-1].NvMIdx)
            && (((Ea_BlockProperties[numBlk_u16-1].BlkStartAddr == Ea_BlockProperties_onEep[numBlk_u16-1].BlkStartAddr)
            && (Ea_BlockProperties[numBlk_u16-1].BlkEndAddr == Ea_BlockProperties_onEep[numBlk_u16-1].BlkEndAddr))
            || (((Ea_BlockProperties_onEep[numBlk_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
            && (Ea_BlockProperties_onEep[numBlk_u16-1].BlkStartAddr >= Ea_Rb_MigHeader_st.MigPerStartAddr_u32)))
            && (Ea_BlockProperties[numBlk_u16-1].Length == Ea_BlockProperties_onEep[numBlk_u16-1].Length)
            && (Ea_BlockProperties[numBlk_u16-1].Flags == Ea_BlockProperties_onEep[numBlk_u16-1].Flags))
    {
        retVal_b = TRUE;
    }

    return retVal_b;
}

/**
 *********************************************************************
 * Ea_Rb_LoadBlkProperties():
 *
 * This function loads all the properties of current block to onEep
 * array.
 *
 * \param   tmpCnt1_u16: current block number to be loaded
 * \param   tmpMigBlkHdr_st: header pointer of current block
 * \return  none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_LoadBlkProperties(uint16 tmpCnt1_u16, Ea_Rb_BlockHeader_tst const *tmpMigBlkHdr_st)
{
    /* Load all block properties to on EEPROM  property structure */
    Ea_BlockProperties_onEep[tmpCnt1_u16].NvMIdx        = tmpMigBlkHdr_st->BlockID_u16;
    Ea_BlockProperties_onEep[tmpCnt1_u16].Length        = tmpMigBlkHdr_st->BlockLen_u16;
    Ea_BlockProperties_onEep[tmpCnt1_u16].Flags         = tmpMigBlkHdr_st->BlockFlags_u8;
    Ea_BlockProperties_onEep[tmpCnt1_u16].BlkStartAddr  = Ea_Rb_MigOrder_st.adWriteStart_uo;

    /* Calculate the real length of this block */
    Ea_BlockProperties_onEep[tmpCnt1_u16].BlkRealLen = Ea_Rb_CalcAlignedLen(tmpMigBlkHdr_st->BlockLen_u16) + EA_BLK_HEADER_SIZE;

    /* If only one copy version, load the end address */
    Ea_BlockProperties_onEep[tmpCnt1_u16].BlkEndAddr    = ((Ea_BlockProperties_onEep[tmpCnt1_u16].BlkStartAddr
                                                                + Ea_BlockProperties_onEep[tmpCnt1_u16].BlkRealLen)
                                                                - 1u);

    /* Load next free start address */
    Ea_Rb_MigOrder_st.adReadStart_uo = (Ea_BlockProperties_onEep[tmpCnt1_u16].BlkEndAddr + 1u);

    if((tmpMigBlkHdr_st->BlockFlags_u8 & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
    {
        /* Set SL2 flag for next block check */
        Ea_Rb_MigOrder_st.isSecLevelCurr_b = TRUE;

        /* Store the version number of the first copy */
        Ea_Rb_MigOrder_st.stCurBlockVersion_u16 = tmpMigBlkHdr_st->BlockVersion_u16;
    }
    else
    {
        /*No redundant block */
        Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;
    }
}

/**
 *********************************************************************
 * Ea_Rb_LoadBlkHdrFromProperties():
 *
 * This function loads all the properties of current block from array.
 *
 * \param   tmpCnt1_u16: current block number to be loaded
 * \param   tmpMigBlkHdr_st: header pointer of current block
 * \return  none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_LoadBlkHdrFromProperties(uint16 BlockNumber, Ea_Rb_BlockHeader_tst *tmpBlkHdr_st)
{
    tmpBlkHdr_st->BlockPattern_u8[0] = (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_0;
    tmpBlkHdr_st->BlockPattern_u8[1] = (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_1;
    tmpBlkHdr_st->BlockPattern_u8[2] = (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_2;
    tmpBlkHdr_st->BlockID_u16        = Ea_BlockProperties[BlockNumber].NvMIdx;
    tmpBlkHdr_st->BlockFlags_u8      = Ea_BlockProperties[BlockNumber].Flags;
    tmpBlkHdr_st->BlockLen_u16       = Ea_BlockProperties[BlockNumber].Length;
}

/**
 *********************************************************************
 * Ea_Rb_CalcAlignedLen(): align the length
 *
 * This function checks if the input length can be divisible by four:
 * --yes: no changes, return the length back;
 * --no: the length will be aligned to the next number, which can be
 * divisible by four.
 *
 * \param    unalignedLen_u32:   length to be aligned
 * \return   aligned length
 * \seealso
 * \usedresources
 *********************************************************************
 */

uint32 Ea_Rb_CalcAlignedLen(uint32 unalignedLen_u32)
{
    uint32 alignedLen_u32 = 0;
    uint32 tmpLen_u32;

    tmpLen_u32 = unalignedLen_u32 % 4u;

    if(tmpLen_u32 > 0u)
    {
        alignedLen_u32 = ((unalignedLen_u32/4u) + 1u)*4u;
    }
    else
    {
        alignedLen_u32 = unalignedLen_u32;
    }

    return alignedLen_u32;
}

/**
 *********************************************************************
 * Ea_Rb_WriteBlockHeader(): start writing of block header
 *
 * This function reads reserved EEPROM part, compares the migration marker
 * with EA_MIGRATION_MARKER. If different detected, starts the migration
 * here, changes the layout to Ea_BlockProperties in Eeprom.
 *
 * \param    BlockNr:   block number to be written
 * \param    Target:   block header to be written
 * \return   none
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_WriteBlockHeader(uint16 BlockNr, Ea_Rb_BlockHeader_tst* Target)
{
    Std_ReturnType stRetLoc_u8;

    /* Block doesn't exist in EEPROM, new block: no data to be moved */
    /* Only block header will be written at first, because no data available in new layout */
    Ea_Rb_LoadBlkHdrFromProperties(BlockNr, Target);

    /* Set version to zero because of new block */
    Target->BlockVersion_u16 = 0;

    Ea_Rb_MigOrder_st.isMoveToEepEnd_b = FALSE;

    /* The block checksum has to be calculated over the provided user buffer and the page CRC.
     * Therefore 2 steps are necessary:
     * - checksum over block header
     * - checksum over rest of data in user buffer
     * For further procedure no additional checksum calculation is necessary anymore. */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    Target->BlockHeader_CS_u16  = Crc_CalculateCRC16((uint8*)Target, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);
    Target->BlockData_CS_u32    = 0;

    /* Write block header only */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    stRetLoc_u8 = EA_EEP_WRITE(Ea_Rb_MigOrder_st.adWriteStart_uo,
                              (const uint8 *)Target,
                              EA_BLK_HEADER_SIZE);

    if(stRetLoc_u8 == E_OK)
    {
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_START_HDR_E;
    }
    else
    {
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
    }
}

/**
 *********************************************************************
 * Ea_Rb_WriteMigHeader(): check migration needed --> yes, start the migration
 *
 * This function reads reserved EEPROM part, compares the migration marker
 * with EA_MIGRATION_MARKER. If different detected, starts the migration
 * here, changes the layout to Ea_BlockProperties in Eeprom.
 *
 * \param    SourceMigHeader: pointer of migration header to be written
 * \return   Order acceptance status
 * \retval   stRetLoc_u8: result of writing
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_WriteMigHeader(Ea_Rb_MigHeader_tst* SourceMigHeader)
{
    boolean stMig_b = TRUE;

    /* Check migration successfully? */
    stMig_b = Ea_Rb_MigCheckResult();

    if(stMig_b)
    {
        /* Successful migration, load new layout end address */
        SourceMigHeader->MigMarker_u32          = (uint32)EA_MIGRATION_MARKER;
        SourceMigHeader->MigEndAddr_u32         = (uint32)Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr;
        SourceMigHeader->MigStartOff_u16        = (uint16)EA_EEP_START_OFFSET;
    }
    else
    {
        /* Unsuccessful migration, load max address as new layout end address, so that no blocks missing
         * in next migration */
        SourceMigHeader->MigEndAddr_u32 = Eep_Rb_RealSize_u32-1u;
    }

    /* The block checksum has to be calculated over the provided user buffer and the page CRC.
     * Therefore 2 steps are necessary:
     * - checksum over block header
     * - checksum over rest of data in user buffer
     * For further procedure no additional checksum calculation is necessary anymore. */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    SourceMigHeader->MigHeader_CS_u16 = Crc_CalculateCRC16((uint8*)SourceMigHeader, (EEP_LAYOUT_HEADER_SIZE-2u), EA_MARKER_PATTERN, FALSE);

    /* Get ready to read next block header */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    if(EA_EEP_WRITE(EEP_BASE_ADDRESS, (const uint8*)SourceMigHeader, EEP_LAYOUT_HEADER_SIZE) == E_OK)
    {
        /* Only to write the valid layout header */
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_MIGHDR_E;
    }
    else
    {
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
    }
}

/**
 *********************************************************************
 * Ea_Rb_MigStartCheck(): check migration needed --> yes, start the migration
 *
 * This function checks if layout end of EEPROM reached. If
 * yes: detect the permanent area and search further until EEPORM end
 * no: reads the next data to search next valid block
 *
 * \return   none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_MigStartCheck(void)
{
    Std_ReturnType stRetLoc_u8;
    boolean isMigOk_b = TRUE;
    boolean isReadNext_b = FALSE;
    uint16  numBlk_u16 = 0;
 #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
 	Std_ReturnType stRet_u8;
 #endif

    Ea_Rb_MigOrder_st.isToBeErase_b = FALSE;

    /* All blocks (non permanent) in old layout detected */
    if(Ea_Rb_MigOrder_st.adReadStart_uo >= (Ea_Rb_MigHeader_st.MigEndAddr_u32-EA_BLK_HEADER_SIZE))
    {
        /* Permanent block area detected? */
        if((Ea_Rb_MigOrder_st.adReadStart_uo < Ea_Rb_MigHeader_st.MigPerStartAddr_u32)
            && (Ea_Rb_MigHeader_st.MigPerStartAddr_u32 < (Eep_Rb_RealSize_u32-EA_BLK_HEADER_SIZE)))
        {
            /* Not jet: set read start address to permanent block area start and read header */
            Ea_Rb_MigOrder_st.adReadStart_uo = Ea_Rb_MigHeader_st.MigPerStartAddr_u32;

            isReadNext_b = TRUE;
        }
        else
        {
            /* Eeprom size reached? */
            if((Ea_Rb_MigOrder_st.adReadStart_uo >= (Eep_Rb_RealSize_u32-EA_BLK_HEADER_SIZE))
                    || (Ea_Rb_MigHeader_st.MigPerStartAddr_u32 == Eep_Rb_RealSize_u32))
            {
                isMigOk_b = Ea_Rb_MigCheckResult();

                /* In the configured block array there are no address entries for the survival block in the permanent area
                 * so no need to detect the between address */
                if(Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr >= Ea_Rb_MigLayoutEnd_u32)
                {
                    Ea_Rb_MigClipSrtAdr_u32 = Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr + 1u;
                }
                else
                {
                    Ea_Rb_MigClipSrtAdr_u32 = Ea_Rb_MigLayoutEnd_u32 + 1u;
                }


                    if(!isMigOk_b)
                    {
                        /* Detect how many blocks are in permanent area */
                        for(numBlk_u16 = EA_NUM_BLOCKS; numBlk_u16 > 0 ; numBlk_u16--)
                        {
                            if((Ea_BlockProperties_onEep[numBlk_u16-1].NvMIdx != 0)
                                && ((Ea_BlockProperties_onEep[numBlk_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0))
                            {
                                if((Ea_Rb_MigHeader_st.MigPerStartAddr_u32 > Ea_BlockProperties_onEep[numBlk_u16-1].BlkStartAddr)
                                    && (Ea_BlockProperties_onEep[numBlk_u16-1].BlkStartAddr > Ea_Rb_MigClipSrtAdr_u32))
                                {
									/* Load the start address to the Permanent start address varibale present in Layout Header structure */
                                    Ea_Rb_MigHeader_st.MigPerStartAddr_u32 = Ea_BlockProperties_onEep[numBlk_u16-1].BlkStartAddr;
                                }
                            }
                        }

 #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)

                        /* Detect how many blocks are not present in layout */
                        for(numBlk_u16 = 0; (numBlk_u16 < EA_NUM_BLOCKS); numBlk_u16++)
                        {
                            /* For no-existing block: reserve the address area for temporary writing */
                            if(((Ea_BlockProperties_onEep[numBlk_u16].NvMIdx == 0u)
                                    && (Ea_BlockProperties_onEep[numBlk_u16].BlkStartAddr == 0u))
                                    && ((Ea_Rb_MigClipSrtAdr_u32 + Ea_BlockProperties[numBlk_u16].BlkRealLen) < Ea_Rb_MigHeader_st.MigPerStartAddr_u32))
                            {
                                /* No all blocks included in Layout, reload new migration marker */
                                Ea_Rb_MigHeader_st.MigMarker_u32 = (uint32)EA_MIGRATION_MARKER_TEMP;

                                /* Migration header changed, it should be written at layout begin */
                                Ea_Rb_isMigHeaderDiff_b = TRUE;

                                if((Ea_BlockProperties[numBlk_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
                                {
                                    /* Reserve the addresses in permanent area for unwritten survival blocks */
                                    Ea_Rb_MigHeader_st.MigPerStartAddr_u32 -= Ea_BlockProperties[numBlk_u16].BlkRealLen;

                                    Ea_BlockProperties_onEep[numBlk_u16].NvMIdx       = Ea_BlockProperties[numBlk_u16].NvMIdx;
                                    Ea_BlockProperties_onEep[numBlk_u16].BlkStartAddr = Ea_Rb_MigHeader_st.MigPerStartAddr_u32;
                                }
                                else
                                {
                                    Ea_BlockProperties_onEep[numBlk_u16].NvMIdx       = Ea_BlockProperties[numBlk_u16].NvMIdx;
                                    Ea_BlockProperties_onEep[numBlk_u16].BlkStartAddr = Ea_Rb_MigClipSrtAdr_u32;

                                    /* Reserve the addresses after migration layout end for unwritten non-survival blocks */
                                    Ea_Rb_MigClipSrtAdr_u32 += Ea_BlockProperties[numBlk_u16].BlkRealLen;
									Ea_Rb_MigLayoutEnd_u32 = Ea_Rb_MigClipSrtAdr_u32 - 1u;
									Ea_Rb_MigHeader_st.MigEndAddr_u32 = Ea_Rb_MigLayoutEnd_u32;
                                }

                                /* Load the block properties to block header */
                                Ea_Rb_LoadBlkHdrFromProperties(numBlk_u16, (Ea_Rb_BlockHeader_tst *)&Ea_Rb_MigBlockHeader_st);

                                Ea_Rb_MigBlockHeader_st.BlockVersion_u16 = 0;
                                Ea_Rb_MigBlockHeader_st.BlockData_CS_u32 = 0;
                                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                                Ea_Rb_MigBlockHeader_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8 *)&Ea_Rb_MigBlockHeader_st, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);

                                /* Flag changed: overwrite the block header with new flag and checksum */
                                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                                stRet_u8 = EA_EEP_WRITE(Ea_BlockProperties_onEep[numBlk_u16].BlkStartAddr, (uint8 *)&Ea_Rb_MigBlockHeader_st, EA_BLK_HEADER_SIZE);

                                if(stRet_u8 == E_OK)
                                {
                                    /* Set next step to EA_RB_MIG_WRITE_BLKHDR_E */
                                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_BLKHDR_E;
                                }
                                else
                                {
                                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                                }
                                break;
                            }
                        }

                        /* All blocks have been checked, update new migration header if changed */
                        if(numBlk_u16 == EA_NUM_BLOCKS)
                        {
                            /* No migration marker change and permanent area start address changes,
                               no need to write the migration header.
                               In case of EA_MIGRATION_MARKER_TEMP:
                               Layout end address keeps at EEPROM size -1, not possible to write blocks at clip board */
                            if(Ea_Rb_isMigHeaderDiff_b)
                            {
							    /* Update layout header: calculate the CRC16 for the header at first */
                                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                                Ea_Rb_MigHeader_st.MigHeader_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigHeader_st, (EA_BLK_HEADER_SIZE-2u), EA_MARKER_PATTERN, FALSE);

                                /* Get ready to migration, change the layout end address to recognize migration is running */
                                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                                stRetLoc_u8 = EA_EEP_WRITE(EEP_BASE_ADDRESS, (const uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);
                                if(stRetLoc_u8 == E_OK)
                                {
                                    /* switch to run migration */
                                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_MIGHDR_TEMP_E;

									/* Reset migration header difference flag */
                                    Ea_Rb_isMigHeaderDiff_b = FALSE;
                                }
                                else
                                {
                                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                                }
                            }
                            else
                            {
                                /* Jump to next status directly */
                                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
                            }
                        }
                        /* Else: Order type has been set in the for loop */
 #else
                        /* Now start migration */

                        /* Reset the current block number: important because by loading block header this variable is used for
                         * found block number in new layout
                         * Migration follows after: Ea_Rb_MigCurNr_u16 = EA_NUM_BLOCKS-->EA_NUM_BLOCKS-1-->EA_NUM_BLOCKS-2...-->1 */

                        /* Initialize the current migration block number from (EA_NUM_BLOCKS-1) to 0 */
                        Ea_Rb_MigCurNr_u16 = EA_NUM_BLOCKS;

                        /* To avoid any block lost the layout end address should be set to all Eeprom size */
                        Ea_Rb_MigHeader_st.MigEndAddr_u32 = (Eep_Rb_RealSize_u32-1u);

					/* Valid Migration Marker and Valid data present */
					if(Ea_Rb_MigHeader_st.MigMarker_u32 != (uint32)EA_MIGRATION_MARKER_TEMP)
					{
						Ea_Rb_MigClipUpdate_b = TRUE;
					}
					else
					{
						/* Added for MISRA */
					}

					if((Ea_Rb_MigClipUpdate_b == TRUE)||(Ea_Rb_MigVirginEepromFlag_b == TRUE))
					{
						/* Before Allocating of space for new Survival Blocks update the BaseClipAddress */
						Ea_Rb_MigClipDetails_st.MigClipBaseAddr_uo = Ea_Rb_MigClipSrtAdr_u32;

						/* Clear the Virgin Eeprom Flag as it is not required thereafter */
						Ea_Rb_MigVirginEepromFlag_b = FALSE;
					}


					/* Migration Marker should be set to temoprary one to show the migration is running, not finished successfully*/
					Ea_Rb_MigHeader_st.MigMarker_u32 = (uint32)EA_MIGRATION_MARKER_TEMP;

					/* Update layout header: calculate the CRC16 for the header at first */
					/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
					Ea_Rb_MigHeader_st.MigHeader_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigHeader_st, (EA_BLK_HEADER_SIZE-2u), EA_MARKER_PATTERN, FALSE);

					/* Initially calculated clip board address is stored for future usage after Clip Details write is completed */
					Ea_Rb_MigClipBaseSrtAdr_u32 = Ea_Rb_MigClipDetails_st.MigClipBaseAddr_uo;

					/* Detect migration limit, if less space than the biggest block size: migration not possible */
					if((Ea_Rb_MigClipBaseSrtAdr_u32 >= (Ea_Rb_MigHeader_st.MigPerStartAddr_u32-EA_BLK_SIZE_MAX))&&(Ea_Rb_MigClipUpdate_b == TRUE))
					{
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_NOT_POSSIBLE_E;
					}
					if((Ea_Rb_MigClipUpdate_b == TRUE)&&(Ea_Rb_MigOrder_st.MigOrderType_en != EA_RB_MIG_NOT_POSSIBLE_E))
					{
						/* Update the Clipdetails Marker to be written */
						Ea_Rb_MigClipDetails_st.MigClipMarker_u16 = (uint16)EA_BASE_CLIP_MARKER;
						/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
						Ea_Rb_MigClipDetails_st.MigClipBaseAddr_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigClipDetails_st, (EA_BASE_MIGCLIP_ADDR_SIZE), EA_MARKER_PATTERN, FALSE);
						/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
						stRetLoc_u8 = EA_EEP_WRITE((EEP_BASE_ADDRESS + EA_RB_MIGCLIP_ADDR_OFFSET),(const uint8 *)&Ea_Rb_MigClipDetails_st,EA_MIGCLIP_DETAILS_SIZE);
						if(stRetLoc_u8 == E_OK)
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_BASECLIP_WRITE_WAIT_E;
							Ea_Rb_MigClipUpdate_b = FALSE;  /* This flag info is not needed further */
						}
						else
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
						}
					}
					else if(Ea_Rb_MigOrder_st.MigOrderType_en == EA_RB_MIG_NOT_POSSIBLE_E)
					{
						/* Do nothing Here.. Go back to MigrationInit Function and process Migration Not Possible state */
					}
					else
					{
						/* Get ready to migration, change the layout end address to recognize migration is running */
						/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
						stRetLoc_u8 = EA_EEP_WRITE(EEP_BASE_ADDRESS, (const uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);
						if(stRetLoc_u8 == E_OK)
						{
							/* switch to run migration */
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_MIGHDR_TEMP_E;
						}
						else
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
						}
					}
 #endif
                }
				else
				{
 #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG == FALSE)
					/* In case of wrong migration marker but all blocks all right */
					if(Ea_Rb_MigHeader_st.MigMarker_u32 != (uint32)EA_MIGRATION_MARKER)
					{
						/* Load new migration marker */
						Ea_Rb_MigHeader_st.MigMarker_u32 = (uint32)EA_MIGRATION_MARKER;

						/* Update layout header: calculate the CRC16 for the header at first */
						/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
						Ea_Rb_MigHeader_st.MigHeader_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigHeader_st, (EA_BLK_HEADER_SIZE-2u), EA_MARKER_PATTERN, FALSE);

						/* Get ready to migration, change the layout end address to recognize migration is running */
						/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
						stRetLoc_u8 = EA_EEP_WRITE(EEP_BASE_ADDRESS, (const uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);

						if(stRetLoc_u8 == E_OK)
						{
							/* switch to run migration */
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_MIGHDR_TEMP_E;
						}
						else
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
						}
					}
                    else
 #endif
                    {
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
						/* Block compare and moving finished, update reserved block and layout header */
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_FINISH_CHECK_1_E;
 #else
						/* Update layout header directly */
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETE_BASECLIP_E;
 #endif
                    }
                }
            }
            else
            {
                /* Read address doesn't reach EEPROM end: continue to read the next one */
                isReadNext_b = TRUE;
            }
        }
    }
    else
    {
        /* Read address is not at the end of layout: continue to read the next one */
        isReadNext_b = TRUE;
    }

    if(isReadNext_b)
    {
        /* Read the next block */
		if((Ea_Rb_MigOrder_st.adReadStart_uo >= Ea_Rb_MigScanAddr_uo) &&(Ea_Rb_MigOrder_st.adReadStart_uo <= (Ea_Rb_MigScanAddr_uo + EA_RB_MIG_BUFFER_ALIGN_SIZE))&&(Ea_Rb_MigScanAddr_uo != 0uL))
		{
			Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_LOAD_BLKHDR_E;
			Ea_Rb_MigScanSize_u16 = (uint16)(Ea_Rb_MigOrder_st.adReadStart_uo - Ea_Rb_MigScanAddr_uo);
			Ea_Rb_MigScanflag_b = TRUE;
		}
		else if((Ea_Rb_MigOrder_st.adReadStart_uo + EA_RB_MIG_BUFFER_SIZE) < Eep_Rb_RealSize_u32)
		{
			stRetLoc_u8 = EA_EEP_READ(Ea_Rb_MigOrder_st.adReadStart_uo, (uint8 *)&Ea_Rb_dMigDataBuf_u8[0], EA_RB_MIG_BUFFER_SIZE);

			if(stRetLoc_u8 == E_OK)
			{
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_LOAD_BLKHDR_E;
				Ea_Rb_MigScanAddr_uo = Ea_Rb_MigOrder_st.adReadStart_uo;
				Ea_Rb_MigScanSize_u16 = 0;
				Ea_Rb_MigScanflag_b = TRUE;
			}
			else
			{
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
			}
		}
		else
		{
	        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        	stRetLoc_u8 = EA_EEP_READ(Ea_Rb_MigOrder_st.adReadStart_uo, (uint8 *)&Ea_Rb_MigBlockHeader_st, EA_BLK_HEADER_SIZE);

        	if(stRetLoc_u8 == E_OK)
        	{
            	Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_LOAD_BLKHDR_E;
        	}
        	else
        	{
            	Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
        	}
    	}
	}
}

/**
 *********************************************************************
 * Ea_Rb_FindPreambelInHdr(): Find the preambel in read data
 *
 * This function searches a preambel for block header in given buffer
 *
 * \param    SearchStart_Ptr:   start address of data buffer
 * \param    Len_u16:   length to be checked
 * \return   cnt_u16:   fould preambel position,
 *                      if it es equal to Len_u16: not found
 * \seealso
 * \usedresources
 *********************************************************************
 */

uint16 Ea_Rb_FindPreambelInHdr(const uint8* SearchStart_Ptr, uint16 Len_u16)
{
    boolean stBlkFound_b = FALSE;
    uint16 cnt_u16;

    /* Search in this header if any HEADER_PREAMBEL found in every 4 Bytes */
    for(cnt_u16=0; (cnt_u16+2u)<Len_u16; cnt_u16+=4u)
    {
        if((*(SearchStart_Ptr + cnt_u16) == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_0)
         &&(*(SearchStart_Ptr + cnt_u16 + 1u) == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_1)
         &&(*(SearchStart_Ptr + cnt_u16 + 2u) == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_2))
        {
            /* Next header found !!!! */
            stBlkFound_b = TRUE;
            break;
        }
    }

    /* In case no block header found in this data area*/
    if(!stBlkFound_b)
    {
        /* return max. length to be checked */
        cnt_u16 = Len_u16;
    }

    return cnt_u16;
}

/**
 *********************************************************************
 *  Ea_Rb_MigStop():
 *
 *  This function stops the migration and set the status to MEMIF_IDLE
 *
 * \param    void
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_MigStop(void)
{
    Ea_Rb_MigRunning_b = FALSE;

    if(Ea_GlobModuleState_st == MEMIF_BUSY_INTERNAL)
    {
        Ea_GlobModuleState_st = MEMIF_IDLE;
    }
}

#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"

/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

