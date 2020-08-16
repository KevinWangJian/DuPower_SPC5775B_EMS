

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */
#include "Ea.h"

/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#if (EA_PRESENT == 1)
#include "Ea_Cfg_SchM.h"
#include "Ea_Prv.h"
#include "Crc.h"

/*
 *********************************************************************
 * Global Variables
 *********************************************************************
 */
#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
boolean Ea_Rb_MigAndWrConflict_b;                   /* Active if write or during migration of the same block */
boolean Ea_Rb_isDataCrcZero_b;						/* TRUE: Data crc value for the block is zero */
boolean Ea_Rb_isData1CrcZero_b;						/* TRUE: Data crc value for the redundent block copy1 is zero */
boolean Ea_Rb_isData2CrcZero_b;						/* TRUE: Data crc value for the redundent block copy2 is zero */
boolean Ea_Rb_isLastDataValid_b;					/* TRUE: Eeprom Data Valid. Applicable only for user write request */
/* Ea can be stopped by CCAS adapter, in order to Write/Read/Erase median directly without Ea */
#if (EA_RB_ADDONS_CCAS != FALSE)
boolean Ea_Rb_stRequestStopMode_b;                  /* TRUE: Stop mode has been requested by CCAS add on */
#endif
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"
uint8 Ea_Rb_stInit_u8;      /* Status of Ea initialization */
uint8 Ea_Rb_stCancel_u8;    /* Status of cancel request */
/* Temporary buffer to store the data read from EEPROM.
 * These data will be compared with the contents of write buffer,
 * before starting to write */
uint8 Ea_Rb_dDataBuf_u8[EA_DATA_BUFFER_SIZE];
#define EA_STOP_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
uint16              Ea_Rb_numBytesTmp_u16;              /* Global temporary number of bytes to be read/write*/
static uint16       Ea_Rb_lenTmp_u16;                   /* Temporary length for robustness checksum calculation */
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"
uint32 Ea_Rb_BlockData1_CS_u32;
uint32 Ea_Rb_BlockData2_CS_u32;
#define EA_STOP_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
/* Static variables only for robustness checksum calculation */
static Eep_AddressType      Ea_Rb_adTmp;                    /* Temporary start address for robustness checksum calculation */
MemIf_JobResultType         Ea_JobResult;                   /* Result of Ea jobs */
Ea_Rb_Order_tst             Ea_Rb_Order_st;                 /* EA order structure */
Ea_Rb_BlockHeader_tst       Ea_Rb_BlockHeader_st;           /* Block header information of the order block */
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"
Ea_Rb_stReturn_ten          Ea_Rb_LastCheckResult_en = EA_RB_ST_INIT_E;
static const uint8 *        Ea_Rb_WrBuf_pcu = NULL_PTR;
#define EA_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/**
 *********************************************************************
 * Ea_MainFunction(): Main function of the EA
 *
 * This function performs the processing of the EEPROM read, write
 * erase jobs.
 * When a job has been initiated, the environment of EA module
 * shall call this function cyclically until the job is finished.
 *
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_MainFunction(void)
{
    Std_ReturnType          stResult_u8     = E_OK;
    Ea_Rb_stReturn_ten      stRet_en        = EA_RB_ST_INIT_E;
    Ea_Rb_stReturn_ten      stRetSub_en     = EA_RB_ST_INIT_E;      /* Ea function return type */
    MemIf_JobResultType     stJobResultOfEep_en;                    /* Result of Eep jobs */
    uint16                  tmp_u16;
    Eep_AddressType         offset;

	/* Check if Ea has been initialised */
    (void)Ea_Rb_CheckInit(EA_SID_INIT);

    /* Check for an asynchronous cancel request */
    if(Ea_Rb_stCancel_u8 == EA_RB_ST_CANCEL_REQUESTED)
    {
        /* Cancel the ongoing job in Eep */
        Eep_Cancel();

        /* Reset cancel request */
        Ea_Rb_stCancel_u8 = EA_RB_ST_CANCEL_NOT_REQUESTED;
    }


    stJobResultOfEep_en = Eep_GetJobResult();

	/* Ea_Rb_MainFunctionOrderCheck() : Check whether this open order is independent of last Executed Eep_JobResult status
	 *  For more details on Ea_Rb_MainFunctionOrderCheck function refer Errata5113 */
	if(stJobResultOfEep_en == MEMIF_JOB_PENDING)
    {
        /* Wait */
		/* Always first we should check whether Eep job result is MEMIF_JOB_PENDING before checking for open order and processing the open order. *
		 * The reason is during migration we accept user request and also in background we do migration that means before processing 			  *
		 * a Ea open order the Eep may be processing some request, so in that case Eep will not accept the request we will get a DET Error.       */
    }
	/* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    else if((stJobResultOfEep_en == MEMIF_JOB_OK) || (Ea_Rb_MainFunctionOrderCheck() == TRUE))
    {
		/* Check for open orders */
        switch(Ea_Rb_Order_st.OrderType_en)
        {
            #if (EA_RB_ADDONS_CCAS != FALSE)
            /* Stop mode */
            case EA_RB_STOPMODE_E:
            {
                /* Stop mode, do nothing */
            }
            break;
            #endif

            case EA_RB_NO_ORDER_E:
    #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
    #else
                /* Do nothing, wait for orders; if migration hasn't finished, call migration */
                if(Ea_Rb_MigRunning_b && (Ea_Rb_stInit_u8 == EA_RB_ST_INIT_DONE))
                {
                    /* Call migration run function */
                    Ea_Rb_Migration();
                }
    #endif
    #if (EA_RB_ADDONS_CCAS != FALSE)
                /* Check for a stop mode request */
                if (Ea_Rb_stRequestStopMode_b == EA_RB_REQUEST_STOP_MODE)
                {
                    /* Activate the stop mode due to a user request from the CC-AS adapter
                     * --> no other orders should be executed any more */
                    Ea_Rb_Order_st.OrderType_en = EA_RB_STOPMODE_E;
                }
    #endif

                break;
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
			case EA_RB_WRITE_ORDER_WAIT_E:
				/* Check if the Handling of Survival blocks is completed */
				if(Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingOver_b != TRUE)
				{
					/* Handling of Survival Blocks not yet completed, so call Migration function which performs this process */
					Ea_Rb_Migration();
				}
				else
				{
					/* Handling of Survival Blocks is completed.*/
				    /* Update the start address of the order in case of new survival block */
				    if(Ea_Rb_isNewSurvBlkToBeWritten_b == TRUE)
				    {
				        /* Update the start address */
				        Ea_Rb_Order_st.adStart_uo = Ea_BlockProperties_onEep[Ea_Rb_NewSurvBlkIndex_u16].BlkStartAddr;
						/* Reset the variable that checks if a new survival block is to be written */
						Ea_Rb_isNewSurvBlkToBeWritten_b = FALSE;
				    }
					else if(Ea_Rb_SurvBlkHandlingAndWrConflict_b == TRUE)
				    {
				        /* Update the start address */
				        Ea_Rb_Order_st.adStart_uo = Ea_BlockProperties_onEep[Ea_Rb_SurvBlkHandlingAndWrConflictIndex_u16].BlkStartAddr;
						/* Reset the variable that checks for a conflict between write and Survival Block Handling */
						Ea_Rb_SurvBlkHandlingAndWrConflict_b = FALSE;
				    }
					else
					{
						/* Such case does not occur */
					}
				    /* Proceed to the Write Order */
					Ea_Rb_Order_st.OrderType_en = EA_RB_WRITE_ORDER_E;
				}

			break;
#endif
            case EA_RB_WRITE_ORDER_E:

                /* Calculate the data checksum only for no-invalidate write order */
                if((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) <= 0)
                {
                    /* Calculate the block data checksum at first, get ready for comparing */
                    Ea_Rb_BlockHeader_st.BlockData_CS_u32    = Crc_CalculateCRC32(Ea_Rb_Order_st.Buffer_un.Write_pcu8,
                                                                                        Ea_Rb_BlockHeader_st.BlockLen_u16,
                                                                                        (((uint32)Ea_Rb_BlockHeader_st.BlockID_u16)^EA_CRC_XOR_VALUE32),
                                                                                        FALSE);
                }

            /* MR12 RULE 16.3 VIOLATION: No break necessary */
            case EA_RB_MAINTAIN_ORDER_E:
                /* If the block to be written is the same one which is being relocated during migration
                 * Set the flag to cancel the current migration order
                 * Because the old address before migration order has been assigned for current write order */
                if(Ea_Rb_MigRunning_b && (Ea_Rb_Order_st.numID_u16 == Ea_Rb_MigOrder_st.numID_u16))
                {
                    /* Set conflict flag */
                    Ea_Rb_MigAndWrConflict_b = TRUE;
                }

            /* MR12 RULE 16.3 VIOLATION: No break necessary */
            case EA_RB_READ_ORDER_E:
            /* Do nothing, start read data check directly */

            case EA_RB_CHECK_DATA_VALID_E:

                /* Start the order to check block validity, call this function at first time to settle the check order */
				/* we are doing retry for Ea_Rb_CheckBlockValid function in some places, but in some places we  are not doing retry. 	*
				 * The reason is retry is not mandatory its a optional where ever it is easy to implement we have done retry, In 		*
				 * other places it's difficult to implement 																			*/
                if(Ea_Rb_CheckBlockValid(Ea_Rb_Order_st.adStart_uo, &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, TRUE) == EA_RB_ST_OK_E)
                {
                    /* Order accepted */
                    Ea_Rb_Order_st.numRepOrder_u8 = 0;
                    stRet_en = EA_RB_ST_PENDING_E;
                    Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_WAIT_E;
                }
                else
                {
                    /* Order not accepted: repeat */
                    stRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_CHECK_DATA_VALID_E);
                }

                break;

            case EA_RB_CHECK_DATA_VALID_WAIT_E:

                /* Call check block valid function continuously till check finished */
                stRetSub_en = Ea_Rb_CheckBlockValid(Ea_Rb_Order_st.adStart_uo, &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, FALSE);

                /* Evaluate the result of block valid check */
                stRet_en = Ea_Rb_BlockEvaluation(stRetSub_en);

                break;

            case EA_RB_SEARCH_ORDER_E:

                /* Call search survival block cyclic */
                offset = Ea_Rb_SearchBlock(0, 0, FALSE);

                if(offset == 0u)
                {
                    stRet_en = EA_RB_ST_PENDING_E;
                    Ea_Rb_Order_st.OrderType_en = EA_RB_SEARCH_ORDER_E;
                }
                else if(offset == EA_MAXUINT32)
                {
                    stRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }
                else
                {
                    /* Block offset found */
                    /* MR12 RULE 2.2 VIOLATION : The value "EEP_BASE_ADDRESS" is based on configuration, hence this operation needs to be performed */
                    Ea_Rb_Order_st.adStart_uo = EEP_BASE_ADDRESS + offset;
                    Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_E;

                    /* Block found: reset the survival block marker */
                    Ea_Rb_Order_st.isSurvivalBlk_b = FALSE;

                    /* Search the correct block number in properties */
                    tmp_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_Order_st.numID_u16);

                    /* Update the found information in on EEPROM properties */
                    Ea_BlockProperties_onEep[tmp_u16].BlkStartAddr = Ea_Rb_Order_st.adStart_uo;
                    Ea_BlockProperties_onEep[tmp_u16].NvMIdx       = Ea_Rb_Order_st.numID_u16;
                }

                break;

             case EA_RB_END_READ_ORDER_E:

                 stRet_en = EA_RB_ST_OK_E;
                 Ea_JobResult = MEMIF_JOB_OK;

                 break;

             case EA_RB_START_WRITE_ORDER_E:
                 /* Start to write block header */
                 stRet_en = Ea_Rb_StartToWrite();
                 break;

            case EA_RB_COMPARE_HEADER_ORDER_E:

                /* Compare block header if written correctly */
                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                stResult_u8 = Eep_Compare(Ea_Rb_Order_st.adStart_uo,
                                          (const uint8 *)&Ea_Rb_BlockHeader_st,
                                          EA_BLK_HEADER_SIZE);
                if(stResult_u8 == E_OK)
                {
                    stRet_en = EA_RB_ST_PENDING_E;

                    if(Ea_Rb_Order_st.isWriteHeaderOnly_b)
                    {
                        if(((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0) || ((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_ROBUST_CRC_FLAG) > 0))
                        {
                            /* For invalidate block */
                            stRet_en = EA_RB_ST_PENDING_E;
                            Ea_Rb_Order_st.OrderType_en = EA_RB_END_WRITE_ORDER_E;
                        }
                        else
                        {
                            Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_DATA_ORDER_E;
                            Ea_Rb_Order_st.isWriteHeaderOnly_b = FALSE;
                        }
                    }
                    else
                    {
                        Ea_Rb_Order_st.OrderType_en = EA_RB_WRITE_DATA_ORDER_E;

                        if((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_ROBUST_CRC_FLAG) > 0)
                        {
                            /* Ready to write the data: initialization*/
                            /* Mark the data write start address */
                            Ea_Rb_adTmp         = Ea_Rb_Order_st.adStart_uo + EA_BLK_HEADER_SIZE;
                            Ea_Rb_WrBuf_pcu     = Ea_Rb_Order_st.Buffer_un.Write_pcu8;
                            Ea_Rb_lenTmp_u16    = Ea_Rb_Order_st.numBytes_u16;
                            Ea_Rb_BlockData1_CS_u32 = Ea_Rb_BlockHeader_st.BlockID_u16;
                            /* Reflect the start value for next CRC32 calculate */
                            Ea_Rb_BlockData1_CS_u32 ^= EA_CRC_XOR_VALUE32;
                        }
                    }
                }
                else
                {
                    stRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }

                break;

            /* Process write data order */
            case EA_RB_WRITE_DATA_ORDER_E:

                /* Robustness checksum active: the data should be stored in buffer at first, and calculate the checksum for each transfer*/
                if((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_ROBUST_CRC_FLAG) > 0)
                {
                    /* Check the number of bytes that have to be written */
                    if(Ea_Rb_lenTmp_u16 <= 0u)
                    {
                        /* After writing, the data CRC32 should be equal to the original one --> Blocks with Robustness Checksum */
                        if(Ea_Rb_BlockData1_CS_u32 == Ea_Rb_BlockHeader_st.BlockData_CS_u32)
                        {
                            /* No comparing happened for fast mode */
                            if(Eep_Mode == MEMIF_MODE_FAST)
                            {
                                stRet_en = EA_RB_ST_PENDING_E;
                                Ea_Rb_Order_st.OrderType_en         = EA_RB_END_WRITE_ORDER_E;
                            }
                            else
                            {
                                stRet_en = EA_RB_ST_PENDING_E;
                                Ea_Rb_Order_st.OrderType_en         = EA_RB_COMPARE_DATA_ORDER_E;
                            }

                            Ea_Rb_Order_st.isCheckAfterWrite_b      = FALSE;
                        }
                        else
                        {
                            /* Wrong CRC in header: data has been changed during writing */
                            Ea_Rb_BlockHeader_st.BlockData_CS_u32   = Ea_Rb_BlockData1_CS_u32;
                            Ea_Rb_Order_st.isWriteHeaderOnly_b      = TRUE;
                            stRet_en                                = Ea_Rb_StartToWrite();
                            Ea_Rb_Order_st.isCheckAfterWrite_b      = TRUE;
                        }
                    }
                    else
                    {
                        /* Robustness CRC flag set: calculate CRC for part of the data */
                        if(Ea_Rb_lenTmp_u16 > EA_DATA_BUFFER_SIZE)
                        {
                            Ea_Rb_numBytesTmp_u16 = EA_DATA_BUFFER_SIZE;
                        }
                        else
                        {
                            Ea_Rb_numBytesTmp_u16 = Ea_Rb_lenTmp_u16;
                        }

                        /* Load the data to temporary buffer */
                        for(tmp_u16=0; tmp_u16<Ea_Rb_numBytesTmp_u16; tmp_u16++)
                        {
                            Ea_Rb_dDataBuf_u8[tmp_u16] = *(Ea_Rb_WrBuf_pcu + tmp_u16);
                        }

                        /* Write the block data */
                        stResult_u8 = EA_EEP_WRITE(Ea_Rb_adTmp, &Ea_Rb_dDataBuf_u8[0], Ea_Rb_numBytesTmp_u16);

                        if(stResult_u8 == E_OK)
                        {
                            /* Check the CRC_32 of data block */
                            Ea_Rb_BlockData1_CS_u32 = Crc_CalculateCRC32(&Ea_Rb_dDataBuf_u8[0],
                                                                                 Ea_Rb_numBytesTmp_u16,
                                                                                 Ea_Rb_BlockData1_CS_u32,
                                                                                 FALSE);
                           /* Set new values for relevant variables */
                            Ea_Rb_WrBuf_pcu             += Ea_Rb_numBytesTmp_u16;
                            Ea_Rb_adTmp                 += Ea_Rb_numBytesTmp_u16;
                            Ea_Rb_lenTmp_u16            -= Ea_Rb_numBytesTmp_u16;

                            stRet_en = EA_RB_ST_PENDING_E;
                            Ea_Rb_Order_st.OrderType_en = EA_RB_WRITE_DATA_ORDER_E;
                        }
                        else
                        {
                            stRet_en = EA_RB_ST_ERROR_E;
                            Ea_JobResult = MEMIF_JOB_FAILED;
                        }
                    }
                }
                else
                {
                    /* Write the block data */
                    stResult_u8 = EA_EEP_WRITE((Ea_Rb_Order_st.adStart_uo + EA_BLK_HEADER_SIZE),
                                                Ea_Rb_Order_st.Buffer_un.Write_pcu8,
                                                Ea_Rb_Order_st.numBytes_u16);
                    if(stResult_u8 == E_OK)
                    {
                        /* No comparing happened for fast mode */
                        if(Eep_Mode == MEMIF_MODE_FAST)
                        {
                            stRet_en = EA_RB_ST_PENDING_E;
                            Ea_Rb_Order_st.OrderType_en	= EA_RB_END_WRITE_ORDER_E;
                        }
                        else
                        {
                            stRet_en = EA_RB_ST_PENDING_E;
                            Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_DATA_ORDER_E;
                        }
                    }
                    else
                    {
                        stRet_en = EA_RB_ST_ERROR_E;
                        Ea_JobResult = MEMIF_JOB_FAILED;
                    }
                }

                break;

            case EA_RB_COMPARE_DATA_ORDER_E:

                /* Check the written block data are equal to data buffer */
                stResult_u8 = Eep_Compare((Ea_Rb_Order_st.adStart_uo + EA_BLK_HEADER_SIZE),
                                           Ea_Rb_Order_st.Buffer_un.Write_pcu8,
                                           Ea_Rb_Order_st.numBytes_u16);
                if(stResult_u8 == E_OK)
                {
                    stRet_en = EA_RB_ST_PENDING_E;
                    Ea_Rb_Order_st.OrderType_en = EA_RB_END_WRITE_ORDER_E;
                }
                else
                {
                    stRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }

                break;

            case EA_RB_END_WRITE_ORDER_E:

                if(Ea_Rb_Order_st.isSecLevelCurr_b)
                {
                    /* Check another copy of block if further written should be done */
                    stRet_en = Ea_Rb_CheckAnotherCopy();

                    /* reset current security level to finish the second writing */
                    Ea_Rb_Order_st.isSecLevelCurr_b = FALSE;
                }
                else
                {
                    if(Ea_Rb_Order_st.isCheckAfterWrite_b)
                    {
                        if(Ea_Rb_CheckBlockValid(Ea_Rb_Order_st.adStart_uo, &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, TRUE) == EA_RB_ST_OK_E)
                        {
                            /* The data buffer can be changed, don't compare with buffer, only check the writing successfully  */
                            /* Start the order to check block validity */
                            stRet_en = EA_RB_ST_PENDING_E;
                            Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_WAIT_E;
                        }
                    }
                    else
                    {
                        stRet_en = EA_RB_ST_OK_E;
                        Ea_JobResult = MEMIF_JOB_OK;
                    }

                    /* In case the migration is running, the block flag should be updated */
                    if(Ea_Rb_MigRunning_b)
                    {
                        tmp_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_Order_st.numID_u16);

                        if((tmp_u16 < EA_NUM_BLOCKS)
                            && (Ea_BlockProperties_onEep[tmp_u16].Flags != Ea_Rb_BlockHeader_st.BlockFlags_u8))
                        {
                            if((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0)
                            {
                                Ea_BlockProperties_onEep[tmp_u16].Flags |= (uint8)EA_INVALID_FLAG;
                            }
                            else
                            {
                                Ea_BlockProperties_onEep[tmp_u16].Flags &= (uint8)(~(uint8)EA_INVALID_FLAG);
                            }

                            break;
                        }
                    }
                }

                break;

            case EA_RB_MAINTAIN_MOVING_WAIT_E:

                stRet_en = Ea_Rb_MaintainMoveBlock();
                if(stRet_en == EA_RB_ST_OK_E)
                {
                    stRet_en = EA_RB_ST_OK_E;
                    Ea_JobResult = MEMIF_JOB_OK;
                }
                else if(stRet_en == EA_RB_ST_PENDING_E)
                {
                    /* Do nothing, wait here till order finished */
                }
                else
                {
                    stRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }

                break;

            case EA_RB_ERASE_ORDER_E:

                /* Execute erase function */
                stResult_u8 = Eep_Erase(Ea_Rb_Order_st.adStart_uo, Ea_Rb_Order_st.BlockLenAligned_uo);
                if(stResult_u8 == E_OK)
                {
                    stRet_en = EA_RB_ST_PENDING_E;
                    Ea_Rb_Order_st.OrderType_en = EA_RB_END_ERASE_ORDER_E;
                }
                else
                {
                    stRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }

                break;

            case EA_RB_END_ERASE_ORDER_E:

                stRet_en = EA_RB_ST_OK_E;
                Ea_JobResult = MEMIF_JOB_OK;

                break;

            /* Default state */
            default:
                Ea_Rb_ResetStatus();
                break;
        }
    }
    else
    {
         stRet_en = EA_RB_ST_ERROR_E;
         Ea_JobResult = MEMIF_JOB_FAILED;
    }

    Ea_Rb_JobFinished(stRet_en);
}

/**
 *********************************************************************
 * Ea_Rb_ResetStatus(): Reset all the status
 *
 * This function resets all the processing variables back. After this
 * function call the order structure shows no order is active
 * currently.
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_ResetStatus(void)
{
    #if (EA_PRV_DEBUGGING != FALSE)
    if (Ea_Rb_Order_st.RequestOrder_en == EA_RB_READ_E)
    {
        Ea_Prv_stModuleTest_st.Ea_ReadTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

        Ea_Prv_stModuleTest_st.Ea_ReadTimeDiff_u32 = MCU_RB_TIM0TICKS_TO_US(
                                                    Ea_Prv_stModuleTest_st.Ea_ReadTimeEnd_u32 -
                                                    Ea_Prv_stModuleTest_st.Ea_ReadTimeStart_u32);
    }
    else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
    {
        Ea_Prv_stModuleTest_st.Ea_WriteTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

        Ea_Prv_stModuleTest_st.Ea_WriteTimeDiff_u32 = MCU_RB_TIM0TICKS_TO_US(
                                                    Ea_Prv_stModuleTest_st.Ea_WriteTimeEnd_u32 -
                                                    Ea_Prv_stModuleTest_st.Ea_WriteTimeStart_u32);
    }
    else
    {
        /* No action required if requested order is other than READ or WRITE */
    }
    #endif

    /* Reset all internal processing variables */
    Ea_Rb_Order_st.adStart_uo               = 0;
    Ea_Rb_Order_st.numBytes_u16             = 0;
    Ea_Rb_Order_st.Buffer_un.Read_pu8       = NULL_PTR;
    Ea_Rb_Order_st.Buffer_un.Write_pcu8     = NULL_PTR;
    Ea_Rb_Order_st.OrderType_en             = EA_RB_NO_ORDER_E;
    Ea_Rb_Order_st.RequestOrder_en          = EA_RB_NO_REQUEST_E;
    Ea_Rb_Order_st.isDataNotEqual_b         = TRUE;
    Ea_Rb_Order_st.isActivBlkCurr_b         = FALSE;
    Ea_Rb_Order_st.isSecLevelCurr_b         = FALSE;
    Ea_Rb_Order_st.isWriteHeaderOnly_b      = FALSE;
    Ea_Rb_Order_st.isSurvivalBlk_b          = FALSE;
    Ea_Rb_Order_st.isCheckAfterWrite_b      = FALSE;
    Ea_Rb_Order_st.stCurBlockVersion_u16    = 0;
	Ea_Rb_Order_st.numRepOrder_u8 = 0;

    /* Persistent ID with EA_INIT_BLK_ID initialized */
    Ea_Rb_Order_st.numID_u16 = (uint16)EA_INIT_BLK_ID;

    Ea_Rb_BlockHeader_st.BlockLen_u16       = 0;
    Ea_Rb_BlockHeader_st.BlockVersion_u16   = 0;
    Ea_Rb_BlockHeader_st.BlockFlags_u8      = 0;
    Ea_Rb_BlockHeader_st.BlockID_u16        = 0;

    Ea_Rb_BlockData_CS_u32  = 0;
    Ea_Rb_BlockData1_CS_u32 = 0;
    Ea_Rb_BlockData2_CS_u32 = 0;

	Ea_Rb_isDataCrcZero_b  = FALSE;
	Ea_Rb_isData1CrcZero_b = FALSE;
	Ea_Rb_isData2CrcZero_b = FALSE;
	Ea_Rb_isLastDataValid_b = FALSE;

}

/**
 *********************************************************************
 * Ea_Rb_JobFinished(): Write one or more complete eep pages
 *
 * This function is always called at the end of every main function
 * call. It detects cancel request and finishes the current order if
 * order status is to EA_RB_ST_OK_E (finished) or EA_RB_ST_ERROR_E
 * (error occurred).
 *
 * \param    stRetEnd_en:     internal return order status
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_JobFinished(Ea_Rb_stReturn_ten stRetEnd_en)
{
    if((stRetEnd_en == EA_RB_ST_OK_E)||(stRetEnd_en == EA_RB_ST_ERROR_E))
    {
        /* Ea_JobResult has been set to the right result accordingly, not only ok or error */
        /* Disable interrupts */
        SchM_Enter_Ea_Order();

        /* Reset ea main state (in case of a cancellation it is already set to idle) */
        Ea_GlobModuleState_st = MEMIF_IDLE;

        /* Enable interrupts */
        SchM_Exit_Ea_Order();

        /* Reset all the internal parameters */
        Ea_Rb_ResetStatus();
    }
}

/**
 *********************************************************************
 * Ea_Rb_CheckAnotherCopy():
 *
 * This function is called only for redundant blocks (security level 2)
 * It checks whether the another copy of redundant block has been checked,
 * written or read. If yes, the processing of another copy will be started.
 *
 *
 * \param    none
 * \retval   stRetEnd_en:     internal return order status
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_CheckAnotherCopy(void)
{
    Ea_Rb_stReturn_ten stRetLoc_en;

    if(Ea_Rb_Order_st.isActivBlkCurr_b)
    {
        /* Second block write is done, need to go back to start address of first block */
        Ea_Rb_Order_st.adStart_uo -= Ea_Rb_Order_st.BlockLenAligned_uo;
        Ea_Rb_Order_st.isActivBlkCurr_b = FALSE;

        /* If the valid block with higher version has different data with write buffer */
        /* All data should be overwritten, so set the number of bytes to be written to block length */
        if(Ea_Rb_Order_st.isDataNotEqual_b)
        {
            if((Ea_Rb_BlockHeader_st.BlockData_CS_u32 == Ea_Rb_BlockData1_CS_u32)&&(Ea_Rb_BlockData1_CS_u32!=0u))
            {
                /* The higher version has the same data like write buffer, no version update done */
               Ea_Rb_Order_st.isDataNotEqual_b      = FALSE;
               Ea_Rb_Order_st.isWriteHeaderOnly_b   = TRUE;
            }
            else
            {
                Ea_Rb_Order_st.numBytes_u16         = Ea_Rb_BlockHeader_st.BlockLen_u16;
                Ea_Rb_Order_st.isDataNotEqual_b     = TRUE;
                Ea_Rb_Order_st.isWriteHeaderOnly_b  = FALSE;
            }

            /* Start to write block header */
            stRetLoc_en = Ea_Rb_StartToWrite();
        }
        else
        {
            stRetLoc_en = EA_RB_ST_PENDING_E;
            Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_DATA_ORDER_E;
        }
    }
    else
    {
        /* first block version has been written, no need to edit start address, just follow */
        Ea_Rb_Order_st.adStart_uo += Ea_Rb_Order_st.BlockLenAligned_uo;
        Ea_Rb_Order_st.isActivBlkCurr_b = TRUE;

        /* If the valid block with higher version has different data with write buffer */
        /* All data should be overwritten, so set the number of bytes to be written to block length */
        if(Ea_Rb_Order_st.isDataNotEqual_b)
        {
            /* If another block has the same data like write buffer, no need to write */
            if((Ea_Rb_BlockHeader_st.BlockData_CS_u32 == Ea_Rb_BlockData2_CS_u32)&&(Ea_Rb_BlockData2_CS_u32 != 0u))
            {
                /* The higher version has the same data like write buffer, no version update done */
                Ea_Rb_Order_st.isWriteHeaderOnly_b = TRUE;
            }
            else
            {
                Ea_Rb_Order_st.numBytes_u16         = Ea_Rb_BlockHeader_st.BlockLen_u16;
                Ea_Rb_Order_st.isDataNotEqual_b     = TRUE;
                Ea_Rb_Order_st.isWriteHeaderOnly_b  = FALSE;
            }

            /* Start to write block header */
            stRetLoc_en = Ea_Rb_StartToWrite();
        }
        else
        {
            stRetLoc_en = EA_RB_ST_PENDING_E;
            Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_DATA_ORDER_E;
        }
    }

    return stRetLoc_en;
}

/**
 *********************************************************************
 * Ea_Rb_StartToRead():
 *
 * This function starts a EEPROM read order.
 *
 * \param    CrcToBeChecked: CRC checksum to be checked
 * \return
 * \retval   Ea_Rb_stReturn_ten: result of calling read order
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_StartToRead(uint32 CrcToBeChecked)
{
    Ea_Rb_stReturn_ten stMainRet_en = EA_RB_ST_PENDING_E;
    uint16 tmp_u16;

    /* If block length is smaller than EA_DATA_BUFFER_SIZE, the data can be read directly from this buffer */
    if(Ea_Rb_Order_st.numBytes_u16 < EA_DATA_BUFFER_SIZE)
    {
        /* Calculate the block data checksum at first, get ready for comparing */
        Ea_Rb_BlockData_CS_u32 = Crc_CalculateCRC32(&Ea_Rb_dDataBuf_u8[0],
                                            Ea_Rb_BlockHeader_st.BlockLen_u16,
                                            (((uint32)Ea_Rb_BlockHeader_st.BlockID_u16)^EA_CRC_XOR_VALUE32),
                                            FALSE);

        if(Ea_Rb_BlockData_CS_u32 == CrcToBeChecked)
        {
            for(tmp_u16 = 0; tmp_u16 < Ea_Rb_Order_st.numBytes_u16; tmp_u16++)
            {
                Ea_Rb_Order_st.Buffer_un.Read_pu8[tmp_u16] = Ea_Rb_dDataBuf_u8[tmp_u16];
            }

            stMainRet_en = EA_RB_ST_OK_E;
            Ea_JobResult = MEMIF_JOB_OK;
        }
        else
        {
            /* Read direct from EEPROM */
            stMainRet_en = Ea_Rb_StartToReadFromEep(Ea_Rb_Order_st.adStart_uo + EA_BLK_HEADER_SIZE,
                                            Ea_Rb_Order_st.Buffer_un.Read_pu8,
                                            Ea_Rb_Order_st.numBytes_u16);
        }
    }
    else
    {
        stMainRet_en = Ea_Rb_StartToReadFromEep(Ea_Rb_Order_st.adStart_uo + EA_BLK_HEADER_SIZE,
                                        Ea_Rb_Order_st.Buffer_un.Read_pu8,
                                        Ea_Rb_Order_st.numBytes_u16);
    }

    return stMainRet_en;
}

/**
 *********************************************************************
 * Ea_Rb_StartToReadFromEep():
 *
 * This function starts to read data from the given address. *
 *
 * \param    EepromAddress: start address
 * \param    DataBufferPtr: pointer of data buffer, where the data
 *                          can be stored
 * \param    Length:        the length to be read
 * \retval   stRetLoc_en:   internal return order status
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_StartToReadFromEep(Eep_AddressType EepromAddress, uint8* DataBufferPtr, Eep_LengthType Length)
{
    Ea_Rb_stReturn_ten stRetLoc_en = EA_RB_ST_INIT_E;
    Std_ReturnType stResultLoc_u8;

    if(Ea_Rb_Order_st.stCurBlockVersion_u16 == 0)
    {
        stRetLoc_en = EA_RB_ST_ERROR_E;
        Ea_JobResult = MEMIF_BLOCK_INCONSISTENT;
    }
    else
    {
        /* Read block data */
        stResultLoc_u8 = EA_EEP_READ(EepromAddress, DataBufferPtr, Length);

        if(stResultLoc_u8 == E_OK)
        {
            Ea_Rb_Order_st.numRepOrder_u8 = 0;

            /* Set next step */
            stRetLoc_en = EA_RB_ST_PENDING_E;
            Ea_Rb_Order_st.OrderType_en = EA_RB_END_READ_ORDER_E;
        }
        else
        {
            /* Order not accepted: repeat */
            stRetLoc_en = Ea_Rb_CheckRetryOrderNr(EA_RB_CHECK_DATA_VALID_WAIT_E);
        }
    }

    return stRetLoc_en;
}

/**
 *********************************************************************
 * Ea_Rb_HeaderCheck(): Block header check
 *
 * This function checks the block header of given pointer if it starts
 * with right preampel and ends with right checksum.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
boolean Ea_Rb_HeaderCheck(const Ea_Rb_BlockHeader_tst* TargetHeader)
{
    boolean isCRCValid_b = FALSE;

    if((TargetHeader->BlockPattern_u8[0] == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_0)
            &&(TargetHeader->BlockPattern_u8[1] == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_1)
            &&(TargetHeader->BlockPattern_u8[2] == (uint8)EA_BLK_HEADER_PREAMBEL_BYTE_2))
    {
        /* Calculate CRC16 of source header */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        if((TargetHeader->BlockHeader_CS_u16) == Crc_CalculateCRC16((const uint8 *)TargetHeader, (EA_BLK_HEADER_SIZE-6u), (uint16)EA_MARKER_PATTERN, FALSE))
        {
            isCRCValid_b = TRUE;
        }
    }

    return isCRCValid_b;
}

/**
 *********************************************************************
 * Ea_Rb_BlockEvaluation(): Main function of the EA
 *
 * This function checks the returned result of Ea_Rb_CheckBlockValid(),
 * and analyses block status on EEPROM especially with redundant blocks.
 *
 * \param    stRetLoc_en: result of Ea_Rb_CheckBlockValid()
 * \return
 * \retval   stMainRet_en: result of block evaluation
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_BlockEvaluation(Ea_Rb_stReturn_ten   stRetLoc_en)
{
    Ea_Rb_stReturn_ten stMainRet_en = EA_RB_ST_INIT_E;
    uint16 tmp_u16;
    Eep_AddressType         offset;

    switch(stRetLoc_en)
    {
        case EA_RB_ST_WRONG_ID_E:
        case EA_RB_ST_OK_E:
            /* For robustness checksum block: after writing the block will be checked if valid
             * instead of comparing
             * -- if block ok: write successfully
             * -- if block not ok: write failed */
            if(Ea_Rb_Order_st.isCheckAfterWrite_b)
            {
                stMainRet_en = EA_RB_ST_OK_E;
                Ea_JobResult = MEMIF_JOB_OK;
            }
            else if(Ea_Rb_Order_st.isSurvivalBlk_b)
            {
                /*For survival block searching */

				/* 	Ea_Rb_isDataCrcZero_b check is added Considering the scenarion the reserved	    *
				 *	block(0xFFFF) data CRC value is zero. If this check is not added we will do 	*
				 *	an unneccessary search in the else part 										*/
                if(((Ea_Rb_BlockData_CS_u32 > 0u)||(Ea_Rb_isDataCrcZero_b != FALSE)) && (Ea_Rb_BlockOffset_uo != 0u))
                {
                    /* For survival block: offset found, load this address to the new read address */
                    /* MR12 RULE 2.2 VIOLATION : The value "EEP_BASE_ADDRESS" is based on configuration, hence this operation needs to be performed */
                    Ea_Rb_Order_st.adStart_uo = EEP_BASE_ADDRESS + Ea_Rb_BlockOffset_uo;

                    /* Find the right block array number for this found survival block persistent ID */
                    tmp_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_Order_st.numID_u16);

                    /* Load the block properties */
                    Ea_BlockProperties_onEep[tmp_u16].BlkStartAddr = Ea_Rb_Order_st.adStart_uo;
                    Ea_BlockProperties_onEep[tmp_u16].NvMIdx       = Ea_Rb_Order_st.numID_u16;

                    /* Start to check survival block data, which to be read in the order */
                    if(Ea_Rb_CheckBlockValid(Ea_Rb_Order_st.adStart_uo, &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, TRUE) == EA_RB_ST_OK_E)
                    {
                        /* Block found: reset the survival block marker */
                        Ea_Rb_Order_st.isSurvivalBlk_b = FALSE;

                        stMainRet_en = EA_RB_ST_PENDING_E;
                        Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_WAIT_E;;
                    }
                    else
                    {
                        stMainRet_en = EA_RB_ST_ERROR_E;
                        Ea_JobResult = MEMIF_JOB_FAILED;
                    }
                }
                else
                {
                    /* if block offset not found, call a search function to find this block in the permanent area */
                    if((Ea_Rb_MigHeader_st.MigPerStartAddr_u32 != 0u) && (Ea_Rb_MigHeader_st.MigPerStartAddr_u32 != Eep_Rb_RealSize_u32))
                    {
                        offset = Ea_Rb_SearchBlock(Ea_Rb_MigHeader_st.MigPerStartAddr_u32, Ea_Rb_Order_st.numID_u16, TRUE);
                    }
                    else
                    {
                        offset = Ea_Rb_SearchBlock(EEP_BASE_ADDRESS, Ea_Rb_Order_st.numID_u16, TRUE);
                    }

                    if(offset == (Eep_AddressType)0)
                    {
                        stMainRet_en = EA_RB_ST_PENDING_E;
                        Ea_Rb_Order_st.OrderType_en = EA_RB_SEARCH_ORDER_E;
                    }
                    else
                    {
                        stMainRet_en = EA_RB_ST_ERROR_E;
                        Ea_JobResult = MEMIF_JOB_FAILED;
                    }
                }
            }
            else
            {
                if(Ea_Rb_Order_st.isSecLevelCurr_b)
                {
                    /* Call evaluation function for redundant blocks */
                    stMainRet_en = Ea_Rb_RedundantBlockEvaluation(stRetLoc_en);
                }
                else
                {
                    /* Call evaluation function for no redundant blocks */
                    stMainRet_en = Ea_Rb_SingleBlockEvaluation();
                }
            }
            break;

    case EA_RB_ST_INVALIDATED_E:
                /* It is an invalidate order? */
                if((!Ea_Rb_Order_st.isSecLevelCurr_b) && ((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0u))
                {
                    /* Invalidate one invalidated block: do nothing */
                    stMainRet_en        = EA_RB_ST_OK_E;
                    Ea_JobResult    = MEMIF_JOB_OK;
                }
                else
                {
                    if((Ea_Rb_Order_st.isSecLevelCurr_b) && (!Ea_Rb_Order_st.isActivBlkCurr_b))
                    {
                        /* Redundant block:
                         * -- current checked block is the first copy
                         * -- check the second copy of block if valid data with higher version available */
                        if(Ea_Rb_Order_st.stCurBlockVersion_u16 < Ea_Rb_BlockHeader_st.BlockVersion_u16)
                        {
                            Ea_Rb_Order_st.stCurBlockVersion_u16 = Ea_Rb_BlockHeader_st.BlockVersion_u16;
                        }

                        /* Update checksum of first copy */
                        Ea_Rb_BlockData1_CS_u32 = Ea_Rb_BlockData_CS_u32;

                        /* Store check block valid result of the first copy */
                        Ea_Rb_LastCheckResult_en = EA_RB_ST_INVALIDATED_E;

                        /* Set to current block at 2.copy */
                        Ea_Rb_Order_st.isActivBlkCurr_b = TRUE;

                        /* Start the order to check another block copy validity */
                        if(Ea_Rb_CheckBlockValid((Ea_Rb_Order_st.adStart_uo + Ea_Rb_Order_st.BlockLenAligned_uo), &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, TRUE) == EA_RB_ST_OK_E)
                        {
                            Ea_Rb_Order_st.numRepOrder_u8 = 0;
                            Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_WAIT_E;
                        }
                        else
                        {
                            /* Order not accepted: repeat */
                            stMainRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_CHECK_DATA_VALID_E);
                        }
                    }
                    else
                    {
                        Ea_Rb_Order_st.isActivBlkCurr_b = FALSE;
                        Ea_Rb_Order_st.isDataNotEqual_b = TRUE;
                        Ea_Rb_BlockData2_CS_u32 = Ea_Rb_BlockData_CS_u32;

                        if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_READ_E)
                        {
                            /* If invalid block, set read order to MEMIF_BLOCK_INVALID */
                            stMainRet_en = EA_RB_ST_OK_E;
                            Ea_JobResult = MEMIF_BLOCK_INVALID;
                        }
                        else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
                        {
                            /* If invalid block, write directly */
                            if(Ea_Rb_Order_st.stCurBlockVersion_u16 < Ea_Rb_BlockHeader_st.BlockVersion_u16)
                            {
                                Ea_Rb_Order_st.stCurBlockVersion_u16 = Ea_Rb_BlockHeader_st.BlockVersion_u16;
                            }

                            /* Start to write block header */
                            stMainRet_en = Ea_Rb_StartToWrite();
                        }
                        else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_MAINTAIN_E)
                        {
                           /* (Ea_Rb_isData1CrcZero_b != TRUE) check reason -->
                            *   1.If data of both copy is invalid then it will check Ea_Rb_isData1CrcZero_b value       *
                            * and returns MEMIF_JOB_OK without moving the block.In Maintain there is a design           *
                            * limitation it will not detect the dataset difference if CRC of both copy are same.        *
                            *   2. For Maintain order if 1st copy is    having higher block version then we will not    *
                            * read the second copyin this case Ea_Rb_BlockData2_CS_u32 will be set to zero, But         *
                            * consider if 1st copy data CRC is zero                                                     */

                            if((Ea_Rb_BlockData1_CS_u32 == Ea_Rb_BlockData2_CS_u32)&&(Ea_Rb_isData2CrcZero_b != TRUE))
                            {
                                /* Checksum the same --> no need to maintain the block */
                                stMainRet_en = EA_RB_ST_OK_E;
                                Ea_JobResult = MEMIF_JOB_OK;
                            }
                            else
                            {
                                /* For maintain redundant block request: 2.copy --> 1.copy only header */

                                Ea_Rb_BlockMaintenance_st.WriteAddr_uo = Ea_Rb_Order_st.adStart_uo;     /* Store 1st copy start Address */

                                /* Store 2nd copy start Address */
                                Ea_Rb_BlockMaintenance_st.ReadAddr_uo =  Ea_Rb_Order_st.adStart_uo + Ea_Rb_Order_st.BlockLenAligned_uo;
                                Ea_Rb_BlockMaintenance_st.numBytes_u32 = EA_BLK_HEADER_SIZE;    /* Block is in invalidated state Only header will be copied */

                                Ea_Rb_Order_st.OrderType_en = EA_RB_MAINTAIN_MOVING_WAIT_E;

                                stMainRet_en = EA_RB_ST_PENDING_E;
                            }
                        }
                        else
                        {
                            /* Do nothing, only to avoid MISRA Warning */
                        }
                    }
                }
                break;

        case EA_RB_ST_PENDING_E:
            /* Do nothing, just wait */
            stMainRet_en = EA_RB_ST_PENDING_E;
            break;

        default:
            stMainRet_en = EA_RB_ST_ERROR_E;
            Ea_JobResult = MEMIF_JOB_FAILED;
            break;
    }

    return stMainRet_en;
}

/**
 *********************************************************************
 * Ea_Rb_RedundantBlockEvaluation(): Main function of the EA
 *
 * This function checks the returned result of Ea_Rb_CheckBlockValid(),
 * and analyses block status on EEPROM especially with redundant blocks.
 *
 * \param    stRetLoc_en: result of Ea_Rb_CheckBlockValid()
 * \return
 * \retval   stMainRet_en: result of block evaluation
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_RedundantBlockEvaluation(Ea_Rb_stReturn_ten stRetSub_en)
{
    Ea_Rb_stReturn_ten stMainRet_en = EA_RB_ST_PENDING_E;
    uint16 tmp_u16;

    if(Ea_Rb_Order_st.stCurBlockVersion_u16 < Ea_Rb_BlockHeader_st.BlockVersion_u16)
    {
        Ea_Rb_Order_st.stCurBlockVersion_u16 = Ea_Rb_BlockHeader_st.BlockVersion_u16;

        if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
        {
            /* Check the higher version has the same data like write buffer? */
            /* For invalidate case, no write data buffer, so Ea_Rb_BlockHeader_st.BlockData_CS_u32 is always zero */
            if(((Ea_Rb_BlockData_CS_u32 == Ea_Rb_BlockHeader_st.BlockData_CS_u32) && (Ea_Rb_BlockData_CS_u32 != 0u)) && (Ea_Rb_BlockHeader_st.BlockVersion_u16 > 0u))
            {
                Ea_Rb_Order_st.isDataNotEqual_b = FALSE;
            }
            else
            {
                Ea_Rb_Order_st.isDataNotEqual_b = TRUE;
            }
        }
        else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_MAINTAIN_E)
        {
            /* For maintain redundant block: no calculated checksum to be compared */
            Ea_Rb_Order_st.isDataNotEqual_b = FALSE;
        }
        else
        {
            /* Do nothing, only to avoid MISRA Warning */
        }
    }

    /* Redundant blocks: check current checked block is the first copy or the second one */
    if(Ea_Rb_Order_st.isActivBlkCurr_b)
    {
        /* Only second copy is valid, check free space before */
        if((stRetSub_en == EA_RB_ST_WRONG_ID_E) && (Ea_Rb_BlankLen_uo >= Ea_Rb_Order_st.BlockLenAligned_uo))
        {
            Ea_Rb_BlockData2_CS_u32 = Ea_Rb_BlockData1_CS_u32;
            Ea_Rb_BlockData1_CS_u32 = 0;

            /* Search the correct block number in properties */
            tmp_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_Order_st.numID_u16);

            /* Update the found information in on EEPROM properties */
            Ea_BlockProperties_onEep[tmp_u16].BlkEndAddr   = Ea_Rb_Order_st.adStart_uo + Ea_Rb_Order_st.BlockLenAligned_uo;
            Ea_Rb_Order_st.adStart_uo -= Ea_Rb_Order_st.BlockLenAligned_uo;

            Ea_BlockProperties_onEep[tmp_u16].BlkStartAddr = Ea_Rb_Order_st.adStart_uo;
            Ea_BlockProperties_onEep[tmp_u16].NvMIdx       = Ea_Rb_Order_st.numID_u16;
            Ea_BlockProperties_onEep[tmp_u16].Length       = Ea_BlockProperties[tmp_u16].Length;
            Ea_BlockProperties_onEep[tmp_u16].Flags        = Ea_BlockProperties[tmp_u16].Flags;
        }
        else
        {
            /* Current checked block is the second copy -> both copy of redundant block has been checked
             * Start to write depending on which block has higher version and valid data
             * Both the same Header+data : take the first copy as the valid one */

            /* Update checksum of second copy */
            Ea_Rb_BlockData2_CS_u32 = Ea_Rb_BlockData_CS_u32;

			/*This is introduced for data CRC zero case */
			Ea_Rb_isData2CrcZero_b = Ea_Rb_isDataCrcZero_b;

        }
		/* Ea_Rb_BlockData2_CS_u32 is for normal case. Ea_Rb_isData2CrcZero_b is for data CRC zero case.
		   Ea_Rb_isLastDataValid_b this is to know whether previous Eeprom content is valid or not  */
        if(((Ea_Rb_BlockData2_CS_u32 > 0u)||(Ea_Rb_isData2CrcZero_b != FALSE )||(Ea_Rb_isLastDataValid_b != FALSE)) && (Ea_Rb_BlockHeader_st.BlockID_u16 == Ea_Rb_Order_st.numID_u16))
        {
			/* It is applicable only for user write request.Clear the flag.This flag info is not needed further */
			Ea_Rb_isLastDataValid_b = FALSE;
            /* The second copy is the valid one */
            if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_READ_E)
            {
                /* For read order, read the second copy directly */
                /* Jump to the second copy and read it */
                Ea_Rb_Order_st.adStart_uo += Ea_Rb_Order_st.BlockLenAligned_uo;

                /* Start to read this block */
                stMainRet_en = Ea_Rb_StartToRead(Ea_Rb_BlockData2_CS_u32);
            }
            else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
            {
                /* Write case: the second copy is the valid one -> overwrite the first copy as the first write address */
                Ea_Rb_Order_st.isActivBlkCurr_b = FALSE;

                if(Ea_Rb_Order_st.isDataNotEqual_b)
                {
					/* CRC0 is a special case for this always we write both data and header */
                    if((Ea_Rb_BlockData1_CS_u32 == Ea_Rb_BlockHeader_st.BlockData_CS_u32)&&(Ea_Rb_BlockData1_CS_u32 != 0u))
                    {
                        Ea_Rb_Order_st.isWriteHeaderOnly_b = TRUE;
                    }
                    else
                    {
                        /* Different data to be written, start the write progress */
                        Ea_Rb_Order_st.isWriteHeaderOnly_b = FALSE;
                    }
                }
                else
                {
                    Ea_Rb_Order_st.stCurBlockVersion_u16--;
                }

                /* Start to write block header */
                stMainRet_en = Ea_Rb_StartToWrite();
            }
            else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_MAINTAIN_E)
            {
                /* For maintain redundant block request: 2.copy --> 1.copy */
                Ea_Rb_BlockMaintenance_st.WriteAddr_uo   = Ea_Rb_Order_st.adStart_uo;  /* Store 1st copy start Address */
                Ea_Rb_BlockMaintenance_st.numBytes_u32    = Ea_Rb_Order_st.BlockLenAligned_uo;
                /* Store 2nd copy start Address */
				Ea_Rb_BlockMaintenance_st.ReadAddr_uo    = Ea_Rb_Order_st.adStart_uo + Ea_Rb_BlockMaintenance_st.numBytes_u32;
                Ea_Rb_Order_st.OrderType_en = EA_RB_MAINTAIN_MOVING_WAIT_E;
                stMainRet_en = EA_RB_ST_PENDING_E;
            }
            else
            {
                /* Do nothing, only to avoid MISRA Warning */
            }
        }
        else
        {
            /* The first copy is the valid one */
            if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_READ_E)
            {
                /* Turn back to the first copy and read it */
                if((Ea_Rb_LastCheckResult_en == EA_RB_ST_OK_E) && ((Ea_Rb_BlockData1_CS_u32 > 0u)||(Ea_Rb_isData1CrcZero_b != FALSE )))
                {
                    /* Start to read this block */
                    stMainRet_en = Ea_Rb_StartToRead(Ea_Rb_BlockData1_CS_u32);
                }
                else if((Ea_Rb_LastCheckResult_en == EA_RB_ST_OK_E) && (Ea_Rb_BlockData1_CS_u32 == 0u))
                {
                    stMainRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_BLOCK_INCONSISTENT;
                }
                else if(Ea_Rb_LastCheckResult_en == EA_RB_ST_INVALIDATED_E)
                {
                    /* If invalid block, set read order to MEMIF_BLOCK_INVALID */
                    stMainRet_en = EA_RB_ST_OK_E;
                    Ea_JobResult = MEMIF_BLOCK_INVALID;
                }
                else
                {
                    stMainRet_en = EA_RB_ST_ERROR_E;
                    Ea_JobResult = MEMIF_JOB_FAILED;
                }
            }
            else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
            {
                /* If write order: overwrite the second copy */
                Ea_Rb_Order_st.isActivBlkCurr_b = TRUE;

                if(Ea_Rb_Order_st.isDataNotEqual_b)
                {
                    if((Ea_Rb_BlockData2_CS_u32 == Ea_Rb_BlockHeader_st.BlockData_CS_u32)&&(Ea_Rb_BlockData2_CS_u32 != 0u))
                    {
                        Ea_Rb_Order_st.isWriteHeaderOnly_b = TRUE;
                    }
                    else
                    {
                        /* Different data to be written, start the write progress */
                        Ea_Rb_Order_st.isWriteHeaderOnly_b = FALSE;
                    }
                }
                else
                {
                    Ea_Rb_Order_st.stCurBlockVersion_u16--;
                }

                /* Jump to the second copy and write it */
                Ea_Rb_Order_st.adStart_uo += Ea_Rb_Order_st.BlockLenAligned_uo;

                /* No need to write the higher version block */
                stMainRet_en = Ea_Rb_StartToWrite();
            }
            else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_MAINTAIN_E)
            {
				/* (Ea_Rb_isData1CrcZero_b != TRUE) check reason -->
				 *	1.If data of both copy is invalid then it will check Ea_Rb_isData1CrcZero_b value    	*
				 * and returns MEMIF_JOB_OK without moving the block.In Maintain there is a design       	*
				 * limitation it will not detect the dataset difference if CRC of both copy are same. 		*
				 *  2. For Maintain order if 1st copy is	having higher block version then we will not 	*
				 * read the second copyin this case Ea_Rb_BlockData2_CS_u32 will be set to zero, But 		*
				 * consider if 1st copy data CRC is zero 													*/
                if((Ea_Rb_BlockData1_CS_u32 == Ea_Rb_BlockData2_CS_u32)&&(Ea_Rb_isData1CrcZero_b != TRUE))
                {
                    /* Checksum the same --> no need to maintain the block */
                    stMainRet_en = EA_RB_ST_OK_E;
                    Ea_JobResult = MEMIF_JOB_OK;
                }
                else
                {
                    /* For maintain redundant block request: 1.copy --> 2.copy */
                    Ea_Rb_BlockMaintenance_st.ReadAddr_uo	   = Ea_Rb_Order_st.adStart_uo; /* Store 1st copy start Address */
                    Ea_Rb_BlockMaintenance_st.numBytes_u32     = Ea_Rb_Order_st.BlockLenAligned_uo;
					/* Store 2nd copy start Address */
                    Ea_Rb_BlockMaintenance_st.WriteAddr_uo     = Ea_Rb_Order_st.adStart_uo + Ea_Rb_BlockMaintenance_st.numBytes_u32;
					Ea_Rb_Order_st.OrderType_en = EA_RB_MAINTAIN_MOVING_WAIT_E;
                    stMainRet_en = EA_RB_ST_PENDING_E;
                }
            }
            else
            {
                /* Do nothing, only to avoid MISRA Warning */
            }
        }
    }
    else
    {
        /* Redundant block:
         * -- current checked block is the first copy
         * -- check the second copy of block if valid data with higher version available */

        /* Update checksum of first copy */
        Ea_Rb_BlockData1_CS_u32 = Ea_Rb_BlockData_CS_u32;

		/*This is introduced for data CRC zero case */
		Ea_Rb_isData1CrcZero_b = Ea_Rb_isDataCrcZero_b;

        /* Store check block valid result of the first copy */
        Ea_Rb_LastCheckResult_en = EA_RB_ST_OK_E;

        /* Set to current block at 2.copy */
        Ea_Rb_Order_st.isActivBlkCurr_b = TRUE;

        /* Start the order to check another block copy validity */
        if(Ea_Rb_CheckBlockValid((Ea_Rb_Order_st.adStart_uo + Ea_Rb_Order_st.BlockLenAligned_uo), &Ea_Rb_BlockHeader_st, Ea_Rb_Order_st.RequestOrder_en, TRUE) == EA_RB_ST_OK_E)
        {
            Ea_Rb_Order_st.numRepOrder_u8 = 0;
            Ea_Rb_Order_st.OrderType_en = EA_RB_CHECK_DATA_VALID_WAIT_E;
        }
        else
        {
            /* Order not accepted: repeat */
            stMainRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_CHECK_DATA_VALID_E);
        }
    }

    return stMainRet_en;
}

/**
 *********************************************************************
 * Ea_Rb_SingleBlockEvaluation():
 *
 * This function evaluates a single block.
 *
 * \param    void
 * \return
 * \retval   Ea_Rb_stReturn_ten: result of evaluation
 * \seealso
 * \usedresources
 *********************************************************************
 */

Ea_Rb_stReturn_ten Ea_Rb_SingleBlockEvaluation(void)
{
    Ea_Rb_stReturn_ten stMainRet_en = EA_RB_ST_PENDING_E;

    /* No redundant block */
    /* Load the new block version */
    Ea_Rb_Order_st.stCurBlockVersion_u16 = Ea_Rb_BlockHeader_st.BlockVersion_u16;

    /* No redundant block, read or write directly */
    if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_READ_E)
    {
        /* we should read and return the value to user only if the eeprom content is valid */
		if((Ea_Rb_BlockData_CS_u32 > 0u) || (Ea_Rb_isDataCrcZero_b != FALSE))
        {
            stMainRet_en = Ea_Rb_StartToRead(Ea_Rb_BlockData1_CS_u32);
        }
        else
        {
            stMainRet_en = EA_RB_ST_ERROR_E;
            Ea_JobResult = MEMIF_BLOCK_INCONSISTENT;
        }
    }
    else if(Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E)
    {
        /* Write block */

        /* Compare the checksum:
         * -- difference found or invalidate block order, write directly
         * -- no difference, the same data, no need to write the data again */
		 /* During invalidate request Ea_Rb_BlockData_CS_u32 will be zero so it will always
		    enter into if condition this is analysed in Ea_Rb_StartToWrite there is an additional
			check Invalidate request */
        if((Ea_Rb_Order_st.stCurBlockVersion_u16 == 0u)
                || ((Ea_Rb_BlockHeader_st.BlockData_CS_u32 != Ea_Rb_BlockData_CS_u32)||(Ea_Rb_BlockData_CS_u32 == 0u))
                || ((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0u))
        {
            /* If block header corrupt*/
            /* If the checksums are different --> different data should be written, don't need to compare data */
            Ea_Rb_Order_st.isDataNotEqual_b = TRUE;

            /* Start to write block header */
            stMainRet_en = Ea_Rb_StartToWrite();
        }
        else
        {
            /* Reset compare marker */
            Ea_Rb_Order_st.isDataNotEqual_b = FALSE;

            /* Checksum the same --> no need to write the data again */
            stMainRet_en = EA_RB_ST_OK_E;
            Ea_JobResult = MEMIF_JOB_OK;
        }
    }
    else
    {
        /* Do nothing, only to avoid MISRA Warning */
    }

    return stMainRet_en;
}

/**
 *********************************************************************
 * Ea_Rb_StartToWrite():
 *
 * This function starts a EEPROM write order.
 *
 * \param    void
 * \return
 * \retval   Ea_Rb_stReturn_ten: result of calling write order
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_StartToWrite(void)
{
    Ea_Rb_stReturn_ten stRet_en = EA_RB_ST_PENDING_E;

    /* The block checksum has to be calculated over the provided user buffer and the page CRC.
     * Therefore 2 steps are necessary:
     * - checksum over block header
     * - checksum over rest of data in user buffer
     * For further procedure no additional checksum calculation is necessary any more. */

    /* No increment has been done: increment the block version */
    if(Ea_Rb_Order_st.stCurBlockVersion_u16 >= Ea_Rb_BlockHeader_st.BlockVersion_u16)
    {
        


        /* Update the current block version and increment for this writing */
        Ea_Rb_BlockHeader_st.BlockVersion_u16 = Ea_Rb_Order_st.stCurBlockVersion_u16;

        /* Detect maximal block version */
        if(Ea_Rb_BlockHeader_st.BlockVersion_u16 < (uint16)EA_MAXUINT16)
        {
            /* Increase block version */
            Ea_Rb_BlockHeader_st.BlockVersion_u16++;
        }
        else
        {
            /* In case of version number overflow:
            start from version number 1, because zero means this block has never been written */
            Ea_Rb_BlockHeader_st.BlockVersion_u16 = EA_INIT_BLK_VERSION;
        }
    }

    /* Calculate CRC16 for block header */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    Ea_Rb_BlockHeader_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_BlockHeader_st, (EA_BLK_HEADER_SIZE-6u), (uint16)EA_MARKER_PATTERN, FALSE);

    /* If this is an invalid block */
    if((Ea_Rb_BlockHeader_st.BlockFlags_u8 & (uint8)EA_INVALID_FLAG) > 0)
    {
        /* No data valid --> Set data CRC32 = Header CRC16 */
        Ea_Rb_BlockHeader_st.BlockData_CS_u32 = Ea_Rb_BlockHeader_st.BlockHeader_CS_u16;

        /* Write block header only */
        Ea_Rb_Order_st.isWriteHeaderOnly_b = TRUE;
    }
	 else
	 {
	     /* In fast mode there is no CRC32 calculation for block data, because this step should be done in case EA_RB_WRITE_ORDER_E */
	     /* For redundant block: the CRC32 Calculation only once */
	     if((Eep_Mode == MEMIF_MODE_FAST) && (!Ea_Rb_Order_st.isActivBlkCurr_b))
	     {
	         /* Calculate the block data checksum at first, get ready for comparing */
	         Ea_Rb_BlockHeader_st.BlockData_CS_u32    = Crc_CalculateCRC32(Ea_Rb_Order_st.Buffer_un.Write_pcu8,
	                                                                             Ea_Rb_BlockHeader_st.BlockLen_u16,
	                                                                             (((uint32)Ea_Rb_BlockHeader_st.BlockID_u16)^EA_CRC_XOR_VALUE32),
	                                                                             FALSE);
	     }
	 }

    /* Write block header at first */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
    if(EA_EEP_WRITE(Ea_Rb_Order_st.adStart_uo, (const uint8 *)&Ea_Rb_BlockHeader_st, EA_BLK_HEADER_SIZE) == E_OK)
    {
         stRet_en = EA_RB_ST_PENDING_E;
         if(Eep_Mode == MEMIF_MODE_FAST)
         {
             if ((Ea_Rb_Order_st.RequestOrder_en == EA_RB_WRITE_E) && (Ea_Rb_Order_st.Buffer_un.Write_pcu8 == NULL_PTR))
             {
			 	/* We donot support invalidate in fast Mode if user calls invalidate in fast Mode 
				   the behaviour will be same like in Slow Mode  */
                 Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_HEADER_ORDER_E;
             }
             else
             {
                 Ea_Rb_Order_st.OrderType_en = EA_RB_WRITE_DATA_ORDER_E;
             }
         }
         else
         {
             Ea_Rb_Order_st.OrderType_en = EA_RB_COMPARE_HEADER_ORDER_E;
         }
     }
    else
    {
        stRet_en = EA_RB_ST_ERROR_E;
        Ea_JobResult = MEMIF_JOB_FAILED;
    }

    return stRet_en;
}

/**
 *********************************************************************
 *  Ea_Rb_CheckRetryOrderNr(): Check repeat order number exceed the max.
 *  number as defined in EA_RB_REPEAT_ORDER_MAX
 *
 * \param    RetryOrder_en The step to be repeated
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
Ea_Rb_stReturn_ten Ea_Rb_CheckRetryOrderNr(Ea_Rb_OrderType_ten RetryOrder_en)
{
    Ea_Rb_stReturn_ten stRetLoc_en;

    /* Order not accepted: repeat */
    if(Ea_Rb_Order_st.numRepOrder_u8 < (uint8)EA_REPEAT_ORDER_MAX)
    {
        Ea_Rb_Order_st.numRepOrder_u8++;
        stRetLoc_en = EA_RB_ST_PENDING_E;
        Ea_Rb_Order_st.OrderType_en = RetryOrder_en;
    }
    else
    {
        stRetLoc_en = EA_RB_ST_ERROR_E;
        Ea_JobResult = MEMIF_JOB_FAILED;
    }

    return stRetLoc_en;
}

/**
 *********************************************************************
 *  Ea_Rb_MainFunctionOrderCheck(): Check whether this open order
 *	is independent of last executed Eep_JobResult
 * \param    None
 * \return
 * \retval   TRUE - Don't require last Executed Eep_JobResult status
 *			 FALSE - Require last Executed Eep_JobResult status
 * \seealso
 * \usedresources
 *********************************************************************
 */
boolean Ea_Rb_MainFunctionOrderCheck(void)
{
	boolean	xRetVal_b = FALSE;
	switch(Ea_Rb_Order_st.OrderType_en)
	{
		#if (EA_RB_ADDONS_CCAS != FALSE)
		case EA_RB_STOPMODE_E:
		#endif
		case EA_RB_NO_ORDER_E:
		case EA_RB_WRITE_ORDER_E:
		case EA_RB_MAINTAIN_ORDER_E:
		case EA_RB_READ_ORDER_E:
		case EA_RB_ERASE_ORDER_E:
			xRetVal_b = TRUE;			/* These states don't need last executed Eep_JobResult */
			break;

        default:
            /* Default state */
			break;
	}
	return xRetVal_b;
}


/**
 ************************************************************************
 *  Ea_Rb_MaintainMoveBlock(): During Ea_Rb_BlockMaintenance operation
 *	this function moves the block from one location to other.Applicable
 *  only for redundent blocks.
 * \param    None
 * \return
 * \retval   EA_RB_ST_OK_E - Maintain Move Block is completed successfully
 *			 EA_RB_ST_PENDING_E - Maintain Move Block is Ongoing
 *			 EA_RB_ST_ERROR_E - Maintain Move Block is failed with Error
 * \seealso
 * \usedresources
 *************************************************************************
 */

Ea_Rb_stReturn_ten Ea_Rb_MaintainMoveBlock(void)
{
	Ea_Rb_stReturn_ten stRet_en = EA_RB_ST_PENDING_E;
	Std_ReturnType stRetLoc_u8  = E_NOT_OK;

	if((Ea_Rb_BlockMaintenance_st.ReadAddr_uo == 0u) ||(Ea_Rb_BlockMaintenance_st.WriteAddr_uo == 0u))
	{
		stRet_en = EA_RB_ST_ERROR_E;
	}
	else
	{
		switch(Ea_Rb_BlockMaintenance_st.MaintainOrder_en)
		{
			case EA_RB_MAINTAIN_READ_E:

			if(Ea_Rb_BlockMaintenance_st.numBytes_u32 < EA_DATA_BUFFER_SIZE)
			{
				Ea_Rb_BlockMaintenance_st.numBytesTemp_u32 = Ea_Rb_BlockMaintenance_st.numBytes_u32;
			}
			else
			{
				Ea_Rb_BlockMaintenance_st.numBytesTemp_u32 = EA_DATA_BUFFER_SIZE;
			}

			stRetLoc_u8 = EA_EEP_READ(Ea_Rb_BlockMaintenance_st.ReadAddr_uo, &Ea_Rb_dDataBuf_u8[0], Ea_Rb_BlockMaintenance_st.numBytesTemp_u32);

			if(stRetLoc_u8 == E_OK)
			{
				/* Set the state to EA_RB_MAINTAIN_WRITE_E to write the current read data */
				Ea_Rb_BlockMaintenance_st.MaintainOrder_en = EA_RB_MAINTAIN_WRITE_E;
				Ea_Rb_Order_st.numRepOrder_u8 = 0; /* Since order is accepted reset the repeat counter */
				stRet_en = EA_RB_ST_PENDING_E;
			}
			else
			{
				/* Order not accepted: repeat */
                stRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_MAINTAIN_MOVING_WAIT_E);
			}
			break;

			case EA_RB_MAINTAIN_WRITE_E:
			stRetLoc_u8 = EA_EEP_WRITE(Ea_Rb_BlockMaintenance_st.WriteAddr_uo, &Ea_Rb_dDataBuf_u8[0], Ea_Rb_BlockMaintenance_st.numBytesTemp_u32);
			if(stRetLoc_u8 == E_OK)
			{
				Ea_Rb_BlockMaintenance_st.MaintainOrder_en = EA_RB_MAINTAIN_COMPARE_E;
				Ea_Rb_Order_st.numRepOrder_u8 = 0; /* Since order is accepted reset the repeat counter */
				stRet_en = EA_RB_ST_PENDING_E;
			}
			else
			{
				/* Order not accepted: repeat */
                stRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_MAINTAIN_MOVING_WAIT_E);
			}
			break;

			case EA_RB_MAINTAIN_COMPARE_E:
			stRetLoc_u8 = Eep_Compare(Ea_Rb_BlockMaintenance_st.WriteAddr_uo, &Ea_Rb_dDataBuf_u8[0], Ea_Rb_BlockMaintenance_st.numBytesTemp_u32);

			if(stRetLoc_u8 == E_OK)
			{
				Ea_Rb_Order_st.numRepOrder_u8 = 0; /* Since order is accepted reset the repeat counter */

				/* Reduce the length of already moved data */
				Ea_Rb_BlockMaintenance_st.numBytes_u32 -= Ea_Rb_BlockMaintenance_st.numBytesTemp_u32;

				if(Ea_Rb_BlockMaintenance_st.numBytes_u32 == 0u)
				{
					Ea_Rb_BlockMaintenance_st.MaintainOrder_en = EA_RB_MAINTAIN_FINISH_E;
					stRet_en = EA_RB_ST_PENDING_E;
				}
				else
				{
					Ea_Rb_BlockMaintenance_st.MaintainOrder_en = EA_RB_MAINTAIN_READ_E;
					/* Set the values to read the next data */
					Ea_Rb_BlockMaintenance_st.ReadAddr_uo += Ea_Rb_BlockMaintenance_st.numBytesTemp_u32;
					/* Set the values to write the next data */
					Ea_Rb_BlockMaintenance_st.WriteAddr_uo += Ea_Rb_BlockMaintenance_st.numBytesTemp_u32;
					stRet_en = EA_RB_ST_PENDING_E;
				}
			}
			else
			{
				/* Order not accepted: repeat */
                stRet_en = Ea_Rb_CheckRetryOrderNr(EA_RB_MAINTAIN_MOVING_WAIT_E);
			}
			break;

			case EA_RB_MAINTAIN_FINISH_E:
				stRet_en = EA_RB_ST_OK_E;  /* Maintain operation is complete */
			break;

			/* Default state */
			default:
				stRet_en = 	EA_RB_ST_ERROR_E;
			break;
		}
	}
	return stRet_en;
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

