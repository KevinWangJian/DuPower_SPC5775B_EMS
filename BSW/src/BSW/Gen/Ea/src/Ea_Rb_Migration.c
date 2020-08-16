

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
#if (EA_DEV_ERROR_DETECT != FALSE)
    #include "Det.h"
#endif
#include "Ea_Prv.h"
#include "Crc.h"

/*
 *********************************************************************
 * Global Variables
 *********************************************************************
 */
#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
static boolean isClipResetReqd_b = FALSE;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"
uint8 Ea_Rb_dMigDataBuf_u8[EA_RB_MIG_BUFFER_SIZE];
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
uint8 Ea_Rb_MigrationStaus_u8;		/* Global variable to hold the Migration status */
#endif
#define EA_STOP_SEC_VAR_CLEARED_8
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
uint16 Ea_Rb_MigCurNr_u16;      /* The current block number which should be placed to the right address */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
uint16 Ea_Rb_MigEraseBlkNr_u16;
#endif
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
uint16 Ea_Rb_MigBlkNrToMove_u16;
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_INIT_32
#include "Ea_MemMap.h"
uint32 Ea_Rb_MigClipSrtAdr_u32  = EEP_TOTAL_SIZE;
uint32 Ea_Rb_MigClipBaseSrtAdr_u32;
uint32 Ea_Rb_MigClipBackUpSrtAdr_u32 = EEP_TOTAL_SIZE;
#define EA_STOP_SEC_VAR_INIT_32
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
    /* The layout on EEPROM has unknown block number, but we should keep only the blocks, which also in new layout exist.
     * So only these block will be stored in Ea_BlockProperties_onEep[], and this array has maximal EA_NUM_BLOCKS block
     * elements. */
    Ea_Rb_SurvivalBlockOffset_tst Ea_Rb_OffsetArr_st[EA_NUM_SURVIVAL_BLOCKS];
 #endif
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
Eep_AddressType Ea_Rb_MigEraseBuffer_uo[EA_RB_MIG_ERASE_BUFFER_SIZE];
 #endif
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"

/* Definitions of all static functions */
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
static boolean Ea_Rb_MigCheckUsrDataWritten(Eep_AddressType EraseHeaderStartAddr_uo);
#endif


/**
 *********************************************************************
 * Ea_Rb_Migration(): check migration needed --> yes, start the migration
 *
 * This function reads reserved EEPROM part, compares the migration marker
 * with EA_MIGRATION_MARKER. If different detected, starts the migration
 * here, changes the layout to Ea_BlockProperties in EEPROM.
 *
 * \return   Order acceptance status
 * \retval   E_OK:      Migration was successful
 * \retval   E_NOT_OK:  Migration failed
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_Migration(void)
{
 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
    boolean stBlkFound_b = FALSE;
    uint16 tmpCnt2_u16 = 0;
	uint16 tmpCnt1_u16 = 0;
 #endif
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en;
    MemIf_JobResultType stJobResultOfEep_en;
#if (EA_PRV_DEBUGGING != FALSE)
    uint32 xIniTimeEnd_u32;
#endif
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
	Eep_AddressType tmpEraseHeaderAddr_uo;
#endif

    /* Conflict between write oder and migration order (same block):
     * This label should be set in Ea_Mainfunction */
    if(Ea_Rb_MigAndWrConflict_b)
    {
        /* Reset this migration order to avoid missing written data
         * But keep the current block number which should be migrated
		 * Also update the Clipstart address to the previous value before conflict */

        Ea_Rb_MigOrder_st.MigOrderType_en   = EA_RB_MIG_RUNNING_E;
        Ea_Rb_MigOrder_st.adReadStart_uo    = 0;
        Ea_Rb_MigOrder_st.adWriteStart_uo   = 0;
        Ea_Rb_MigOrder_st.numBytes_uo       = 0;
        Ea_Rb_MigOrder_st.BlockData_CS_u32  = 0;
        Ea_Rb_MigOrder_st.stCurBlockVersion_u16  = 0;
        Ea_Rb_MigOrder_st.numAlignedBytes_uo = 0;
		/* Reset clipboard address only if transfer of data was from layout to clipboard */
		if(isClipResetReqd_b == TRUE)
		{
			/* Reset the boolean value as it is no longer required */
			isClipResetReqd_b = FALSE;
			/* Reset the Clip area start address to the value before the start of the migration operation from old layout to clipboard */
			Ea_Rb_MigClipSrtAdr_u32 = Ea_Rb_MigClipBackUpSrtAdr_u32;
        }
		Ea_Rb_MigOrder_st.isSecLevelCurr_b  = FALSE;
        Ea_Rb_MigOrder_st.isCopyWritten_b   = FALSE;
        Ea_Rb_MigOrder_st.isSecLevelCurr_b  = FALSE;
        Ea_Rb_MigOrder_st.isMoveToEepEnd_b  = FALSE;
        Ea_Rb_MigOrder_st.isToBeErase_b     = FALSE;

        /* Reset conflict flag */
        Ea_Rb_MigAndWrConflict_b = FALSE;
    }

    /* Get current job result of Eep */
    stJobResultOfEep_en = Eep_GetJobResult();

    /* Check if the Eep job finished */
	/* Ea_Rb_MigrationOrderCheck(): Check whether this Migration order is independent of last Executed Eep_JobResult status */
    if(stJobResultOfEep_en == MEMIF_JOB_PENDING)
    {
        /* Do nothing, just wait */
    }
	/* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
	else if((stJobResultOfEep_en == MEMIF_JOB_OK) ||(Ea_Rb_MigrationOrderCheck() == TRUE))
    {
        switch(Ea_Rb_MigOrder_st.MigOrderType_en)
        {
#if(EA_NUM_SURVIVAL_BLOCKS > 0)


			case EA_RB_MIG_SURVBLK_HANDLING_E:
			    Ea_Rb_MigSurvBlkHandling();
			break;

			case EA_RB_MIG_SURVBLK_HANDLING_ERROR_E:
                /* Set Migration Order as EA_RB_MIG_ERROR_E to stop Survival Block Handling and Migration operation */
				/* This will set the Migration status variable as EA_RB_MIGRATION_ERROR */                
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
            break;

#endif
			case EA_RB_MIG_RUNNING_E:

                /* Check if the Eep job finished */
				#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
				 /* Erase the block headers, which is not needed for the new layout */
				if(Ea_Rb_MigEraseBlkNr_u16 > 0)
				{
					tmpEraseHeaderAddr_uo = Ea_Rb_MigEraseBuffer_uo[Ea_Rb_MigEraseBlkNr_u16 - 1u];
					
					if(Ea_Rb_MigCheckUsrDataWritten(tmpEraseHeaderAddr_uo) != TRUE)
					{

						if(Eep_Erase(tmpEraseHeaderAddr_uo, EA_BLK_HEADER_SIZE) == E_OK)
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
							Ea_Rb_MigEraseBlkNr_u16 = Ea_Rb_MigEraseBlkNr_u16 - 1u;
						}
						else
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
						}
					}
					else
					{
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
						Ea_Rb_MigEraseBlkNr_u16 = Ea_Rb_MigEraseBlkNr_u16 - 1u;
					}

				}
                else
				#endif
				{
					if(Ea_Rb_MigCurNr_u16 > 0)
					{
						/* Reset block ID */
						Ea_Rb_MigOrder_st.numID_u16 = (uint16)EA_INIT_BLK_ID;

						/* Check the current block are already in the right address */
						if(Ea_Rb_CheckBlkInRightAddr(Ea_Rb_MigCurNr_u16))
						{
							/* This block locates in right address on EEPROM, do nothing for this block
							 * Check the next one or
							 * Start to finish the migration because it is already the last block to be migrated */
							Ea_Rb_MigCheckCurrBlkNr();
						}
						else
						{
							/* This block doesn't locate in right address on EEPROM: check next step */
							Ea_Rb_MigCheckCurrBlkToBeMoved();
						}
					}
				}
                break;

            /* This check is only for SL2 block to recognize if both copy valid */
            case EA_RB_MIG_CHECK_DATA_E:

                stRetSub_en = Ea_Rb_CheckBlockValid(Ea_Rb_MigOrder_st.adReadStart_uo, &Ea_Rb_MigBlockHeader_st, EA_RB_MIGRATION_E, FALSE);

                switch(stRetSub_en)
                {
                    case EA_RB_ST_OK_E:
                        if(Ea_Rb_MigOrder_st.isSecLevelCurr_b)
                        {
                            /* Update checksum of first copy */
                            Ea_Rb_BlockData1_CS_u32 = Ea_Rb_BlockData_CS_u32;

							/* This line is for special case data CRC is zero, During validating second copy we need first copy status info */
							Ea_Rb_isData1CrcZero_b = Ea_Rb_isDataCrcZero_b;

                            /* Reset flag */
                            Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;

                            Ea_Rb_MigOrder_st.stCurBlockVersion_u16 = Ea_Rb_MigBlockHeader_st.BlockVersion_u16;

                            Ea_Rb_MigOrder_st.adReadStart_uo += (Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16) + EA_BLK_HEADER_SIZE);

                            stRetSub_en = Ea_Rb_CheckBlockValid(Ea_Rb_MigOrder_st.adReadStart_uo, &Ea_Rb_MigBlockHeader_st, EA_RB_MIGRATION_E, TRUE);

                            if(stRetSub_en ==  EA_RB_ST_OK_E)
                            {
                                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECK_DATA_E;
                            }
                            else
                            {
                                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                            }
                        }
                        else
                        {
                            /* Update checksum of second copy */
                            Ea_Rb_BlockData2_CS_u32 = Ea_Rb_BlockData_CS_u32;

							Ea_Rb_isData2CrcZero_b = Ea_Rb_isDataCrcZero_b;  /* This flag value is not needed any more clear the flag */

                            /* Calculate the aligned address */
                            Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                            /* Data checksum of 2.copy valid?
                             * -- yes: 2.copy is the current valid copy, because if the 1.copy has higher or same version and valid data,
                             *         the 2.copy data checksum will not be calculated
                             * -- no: 1.copy is the current one        */
                            if((Ea_Rb_BlockData2_CS_u32 > 0u) || (Ea_Rb_isData2CrcZero_b != FALSE))
                            {
                                /* 2.copy has higher version and valid data, delete the 1.copy */
                                Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen   = Ea_Rb_MigOrder_st.numAlignedBytes_uo + EA_BLK_HEADER_SIZE;
                                Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr
                                                                                        + Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen;
                                /* Delete */
                                stRet_u8 = Eep_Erase((Ea_Rb_MigOrder_st.adReadStart_uo-Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen), EA_BLK_HEADER_SIZE);
                            }
                            else
                            {
                                /* 1.copy has higher version and valid data, delete the 2.copy */
                                Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen = Ea_Rb_MigOrder_st.numAlignedBytes_uo + EA_BLK_HEADER_SIZE;
                                Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkEndAddr = (Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr
                                                                                            + Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen)
                                                                                            -1u;
                                /* Delete */
                                stRet_u8 = Eep_Erase(Ea_Rb_MigOrder_st.adReadStart_uo, EA_BLK_HEADER_SIZE);
                            }

                            if(stRet_u8 == E_OK)
                            {
                                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
								Ea_Rb_isDataCrcZero_b = FALSE;
								Ea_Rb_isData1CrcZero_b = FALSE;
								Ea_Rb_isData2CrcZero_b = FALSE;
                            }
                            else
                            {
                                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                            }
                        }
                        break;

                    default:
                        /* Default state, no action required */
                        break;
                }

                break;

            case EA_RB_MIG_WRITE_BLKHDR_E:
                /* Load the block properties to block header */
                Ea_Rb_LoadBlkHdrFromProperties((Ea_Rb_MigCurNr_u16-1), (Ea_Rb_BlockHeader_tst *)&Ea_Rb_MigBlockHeader_st);

                /* This block on old layout was invalidated, it should not been changed in new layout */
                if((Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_INVALID_FLAG) > 0)
                {
                    /* Only invalid flag will be taken in new layout */
                    Ea_Rb_MigBlockHeader_st.BlockFlags_u8 |= (uint8)EA_INVALID_FLAG;
                }

                /* Reset flag value in old layout to avoid next flag compare difference */
                Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Flags = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags;

                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                Ea_Rb_MigBlockHeader_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8 *)&Ea_Rb_MigBlockHeader_st, (EA_BLK_HEADER_SIZE-6u), (uint16)EA_MARKER_PATTERN, FALSE);

                /* Flag changed: overwrite the block header with new flag and checksum */
                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                stRet_u8 = EA_EEP_WRITE(Ea_Rb_MigOrder_st.adWriteStart_uo, (uint8 *)&Ea_Rb_MigBlockHeader_st, EA_BLK_HEADER_SIZE);

                if(stRet_u8 == E_OK)
                {
                    /* Reset flag change marker */
                    Ea_Rb_MigOrder_st.isFlagChanged_b = FALSE;

                    /* Set next step to EA_RB_MIG_RUNNING_E */
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }

                break;

            case EA_RB_MIG_START_HDR_E:
                if(Ea_Rb_MigOrder_st.isSecLevelCurr_b)
                {
                    /* Set the write address at first, it should be set extra because for the second copy of SL2 blocks, it isn't same as the block start address */
                    Ea_Rb_MigOrder_st.adWriteStart_uo += (Ea_Rb_CalcAlignedLen(Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Length) + EA_BLK_HEADER_SIZE);

                    /* New block: write block header only */
                    Ea_Rb_WriteBlockHeader((Ea_Rb_MigCurNr_u16-1), &Ea_Rb_MigBlockHeader_st);
                    Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;
                }
                else
                {
                    /* Block data moving finished */
                    /* Update new layout address: here no need to call function Ea_Rb_MigUpdateBlockEntry:
                     * because it's new block, and it was not in old layout and
                     * Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1] is always free for the entries */
                    Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].NvMIdx         = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].NvMIdx;
                    Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Flags          = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags;
                    Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Length         = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Length;
                    Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen     = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkRealLen;

                    if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
                    {
                        /* Survival Block Handling is done before the start of Migration. So this part of code is not attained. To be removed in the future. */
                    }
                    else
                    {
                        Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr   = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;
                        Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkEndAddr     = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkEndAddr;
                    }

                    Ea_Rb_MigCheckCurrBlkNr();
                }

                break;

            case EA_RB_MIG_MOVING_WAIT_E:

                stRetSub_en = Ea_Rb_MigMoveBlock(NULL_PTR, FALSE);

                if(stRetSub_en == EA_RB_ST_OK_E)
                {
                    /* The current moving to end of EEPROM finished */
                    if(Ea_Rb_MigOrder_st.isMoveToEepEnd_b)
                    {
                        /* For survival blocks, no address changes for clip board */
                        if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
                        {
                            /* Survival Block Handling is done before the start of Migration. So this part of code is not attained. To be removed in the future. */
                        }
                        else
                        {
                            /* If this is a block moving as backup at the end of EEPROM */
                            Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkStartAddr   = Ea_Rb_MigOrder_st.adWriteStart_uo;

                            Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkEndAddr = (Ea_Rb_MigOrder_st.adWriteStart_uo + Ea_Rb_MigOrder_st.numBytes_uo) - 1u;
                            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
                        }
                    }
                    else
                    {
                        /* Update new clip board start address */
                        if((Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkEndAddr == (Ea_Rb_MigClipSrtAdr_u32 - 1u))
                            && (Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkEndAddr > Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr))
                        {
                            /* Disable interrupts */
							SchM_Enter_Ea_Order();

							Ea_Rb_MigClipSrtAdr_u32 -= Ea_Rb_MigOrder_st.numBytes_uo;

							/* Enable interrupts */
							SchM_Exit_Ea_Order();
                        }

                        if(Ea_Rb_MigOrder_st.isSecLevelCurr_b)
                        {
                            Ea_Rb_MigOrder_st.numBytes_uo = Ea_Rb_MigOrder_st.numBytes_uo*2u;

                            /* Reset Security level flag */
                            Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;
                        }

                        Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr = Ea_Rb_MigOrder_st.adWriteStart_uo;
                        Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkEndAddr   = (Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr
                                                                                        + Ea_Rb_MigOrder_st.numBytes_uo)
                                                                                        - 1u;
                        Ea_Rb_MigCheckCurrBlkNr();
                    }
                }
                else if(stRetSub_en == EA_RB_ST_PENDING_E)
                {
                    /* Do nothing, wait here till order finished */
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }

                break;

 #if(EA_NUM_SURVIVAL_BLOCKS > 0)
            case EA_RB_MIG_FINISH_CHECK_1_E:

                stBlkFound_b = FALSE;

                /* Load all survival block offsets and update the entries in reserved block */
                for(tmpCnt1_u16=0; tmpCnt1_u16<EA_NUM_BLOCKS;tmpCnt1_u16++)
                {
                    if((Ea_BlockProperties[tmpCnt1_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
                    {
                        /* Survival blocks found */
                        stBlkFound_b = TRUE;

                        /* Load persistent ID for found survival block */
                        Ea_Rb_OffsetArr_st[tmpCnt2_u16].SurvivalBlockID_u16 = Ea_BlockProperties_onEep[tmpCnt1_u16].NvMIdx;

                        /* Load Offset to EEPROM end for this found survival block */
                        Ea_Rb_OffsetArr_st[tmpCnt2_u16].BlockOffset_uo      = Ea_BlockProperties_onEep[tmpCnt1_u16].BlkStartAddr;

                        /* Increment array index */
                        tmpCnt2_u16++;
                    }
                }

                if(stBlkFound_b)
                {
                    /* Update reserved block for the survival blocks */
                    /* Get ready to read next block header */
                    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                    stRet_u8 = EA_EEP_WRITE((Ea_BlockProperties_onEep[EA_NUM_BLOCKS-1u].BlkStartAddr + EA_BLK_HEADER_SIZE),
                                                (const uint8 *)&Ea_Rb_OffsetArr_st[0],
                                                Ea_BlockProperties_onEep[EA_NUM_BLOCKS-1u].Length);

                    if(stRet_u8 == E_OK)
                    {
                        /* Only to write the valid layout header */
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_FINISH_CHECK_2_E;
                    }
                    else
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                    }
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETE_BASECLIP_E;
                }

            break;

        case EA_RB_MIG_FINISH_CHECK_2_E:

            Ea_Rb_LoadBlkHdrFromProperties((EA_NUM_BLOCKS-1u), &Ea_Rb_MigBlockHeader_st);
            Ea_Rb_MigBlockHeader_st.BlockVersion_u16 = 1;

            /* Calculate the checksum of offset array */
            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            Ea_Rb_MigBlockHeader_st.BlockData_CS_u32    = Crc_CalculateCRC32((const uint8 *)&Ea_Rb_OffsetArr_st[0],
                                                                                Ea_Rb_MigBlockHeader_st.BlockLen_u16,
                                                                                (((uint32)Ea_Rb_MigBlockHeader_st.BlockID_u16)^EA_CRC_XOR_VALUE32),
                                                                                FALSE);

            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            Ea_Rb_MigBlockHeader_st.BlockHeader_CS_u16  = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigBlockHeader_st, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);

            /* Write block header only */
            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            stRet_u8 = EA_EEP_WRITE(Ea_BlockProperties_onEep[EA_NUM_BLOCKS-1u].BlkStartAddr, (const uint8 *)&Ea_Rb_MigBlockHeader_st, EA_BLK_HEADER_SIZE);

            if(stRet_u8 == E_OK)
            {
                /* Only to write the valid layout header */
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETE_BASECLIP_E;
            }
            else
            {
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
            }

            break;
#endif

        case EA_RB_MIG_DELETE_BASECLIP_E:

            stRet_u8 = Eep_Erase((EEP_BASE_ADDRESS + EA_RB_MIGCLIP_ADDR_OFFSET),EA_MIGCLIP_DETAILS_SIZE);
            if(stRet_u8 == E_OK)
            {
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_FINISH_CHECK_3_E;
            }
            else
            {
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
            }

        break;

        case EA_RB_MIG_FINISH_CHECK_3_E:

            Ea_Rb_WriteMigHeader(&Ea_Rb_MigHeader_st);

            break;

        case EA_RB_MIG_WRITE_MIGHDR_E:

            /* Get ready to read next block header */
            /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            stRet_u8 = EA_EEP_WRITE((EEP_BASE_ADDRESS + EEP_LAYOUT_HEADER_SIZE),
                                        (const uint8 *)&Ea_Rb_MigHeader_st,
                                        EEP_LAYOUT_HEADER_SIZE);

            if(stRet_u8 == E_OK)
            {
                /* Only to write the valid layout header */
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETING_E;
            }
            else
            {
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
            }

            break;

        case EA_RB_MIG_DELETING_E:

            /* Get ready to delete the used area */

            /* Delete only if old layout greater than the new one */
            if(Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr < Ea_Rb_MigLayoutEnd_u32)
            {
                Ea_Rb_MigOrder_st.adReadStart_uo = Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr + 1u;

                 stRet_u8 = Eep_Erase(Ea_Rb_MigOrder_st.adReadStart_uo, (Eep_LengthType)(Ea_Rb_MigLayoutEnd_u32-Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkEndAddr));

                if(stRet_u8 == E_OK)
                {
                    /* Only to write the valid layout header */
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_END_MIGRATION_E;
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }
            }
            else
            {
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_END_MIGRATION_E;
            }

            break;

        case EA_RB_MIG_ERROR_E:
            /* Stop the migration */
            Ea_Rb_MigStop();

            /* Call error report */
            Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATION, EA_E_RB_MIGRATION_FAILED);

            break;

        case EA_RB_MIG_NOT_POSSIBLE_E:
            /* Stop the migration */
            Ea_Rb_MigStop();

            /* Call error report */
            Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATION, EA_E_RB_MIGRATION_NOT_POSSIBLE);

            break;

        case EA_RB_END_MIGRATION_E:

            #if (EA_PRV_DEBUGGING != FALSE)
            xIniTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

            Ea_Prv_stModuleTest_st.Ea_MigrationTimeDiff_u32 =
                    MCU_RB_TIM0TICKS_TO_US(xIniTimeEnd_u32 - Ea_Prv_stModuleTest_st.Ea_MigrationTimeStart_u32);
            #endif

            /* Stop migration */
            Ea_Rb_MigStop();

			#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
			if(Ea_Rb_MigrationStaus_u8 == EA_RB_MIGRATION_RUNNING)
			{
				Ea_Rb_MigrationStaus_u8 = EA_RB_MIGRATION_FINISHED;
			}
			#endif

            break;

        default:
            /* Unknown state: stop migration */
            Ea_Rb_MigStop();

            /* Call error report */
            Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATION, EA_E_RB_MIGRATION_FAILED);

            break;
        }
    }
    else
    {
        /* If Eep Job failed or inconsistent */

        /* Stop migration */
        Ea_Rb_MigStop();

        /* Call error report */
        Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATION, EA_E_RB_MIGRATION_FAILED);
    }

}


/**
 *********************************************************************
 * Ea_Rb_MigCheckCurrBlkToBeMoved():
 *
 * This function checks if the address area for current block is free.
 * If not, the occupied block will be moved to clipboard
 * If yes, write or move this block to right address (only block header
 * written for first write of this block)
 *
 * \param   void
 * \return  void
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_MigCheckCurrBlkToBeMoved(void)
{
    /* Check the last block addressed in target area, where this new block will be relocated.
     * It returns the first block number, which should be moved to clip board */
    Ea_Rb_MigBlkNrToMove_u16 = Ea_Rb_MigCheckFreeAdr(Ea_Rb_MigCurNr_u16);

    /* Target address used by another block: moving necessary */
    if(Ea_Rb_MigBlkNrToMove_u16 > 0)
    {
        /* Set block ID */
        Ea_Rb_MigOrder_st.numID_u16 = Ea_BlockProperties[Ea_Rb_MigBlkNrToMove_u16-1].NvMIdx;

        /* Set read start address */
        Ea_Rb_MigOrder_st.adReadStart_uo    = Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkStartAddr;

        /* In case SL2-->SL1 */
        if(Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkRealLen == (Ea_BlockProperties[Ea_Rb_MigBlkNrToMove_u16-1].BlkRealLen*2u))
        {
            Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkRealLen = Ea_BlockProperties[Ea_Rb_MigBlkNrToMove_u16-1].BlkRealLen;
        }

        /* Set move data length */
        Ea_Rb_MigOrder_st.numBytes_uo       = Ea_BlockProperties_onEep[Ea_Rb_MigBlkNrToMove_u16-1].BlkRealLen;

		/* Check if space available in the clipboard for migration */
		if(Ea_Rb_MigClipAddrCheckSpace(Ea_Rb_MigCurNr_u16, (uint16)Ea_Rb_MigOrder_st.numBytes_uo) == TRUE)
		{
			/* Disable interrupts */
			SchM_Enter_Ea_Order();

			/* Set write address: target address */
			Ea_Rb_MigOrder_st.adWriteStart_uo   = Ea_Rb_MigClipSrtAdr_u32;

			/* Update the back up of Clip Start Address */
			Ea_Rb_MigClipBackUpSrtAdr_u32 = Ea_Rb_MigClipSrtAdr_u32;

			/* Update the new clip board start address */
			Ea_Rb_MigClipSrtAdr_u32 += Ea_Rb_MigOrder_st.numBytes_uo;

			/* Set isClipResetReqd_b to TRUE as if there is a write request immediately for same block Ea should know so that clip area could be reused */
			isClipResetReqd_b = TRUE;

			/* Enable interrupts */
			SchM_Exit_Ea_Order();

			/* Set moving parameters for last block to clip board start address */
			Ea_Rb_MigOrder_st.isSecLevelCurr_b  = FALSE;
			Ea_Rb_MigOrder_st.isCopyWritten_b   = TRUE;
			Ea_Rb_MigOrder_st.isMoveToEepEnd_b  = TRUE;
			Ea_Rb_MigOrder_st.isToBeErase_b     = TRUE;

			/* Start to move block */
			if(Ea_Rb_MigMoveBlock((const Ea_Rb_MigOrder_tst *)&Ea_Rb_MigOrder_st, TRUE) == EA_RB_ST_OK_E)
			{
				Ea_Rb_MigOrder_st.MigOrderType_en   = EA_RB_MIG_MOVING_WAIT_E;
			}
			else
			{
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
			}
		}
		else
		{
			Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_NOT_POSSIBLE_E;
		}
	}
    else
    {
        /* No block found to be moved */
        /* The target address is free, load the current migration block there */

        /* Set block ID */
        Ea_Rb_MigOrder_st.numID_u16 = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].NvMIdx;

        /* Current block exist in old layout: relocation needed */
        if(Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].NvMIdx == Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].NvMIdx)
        {
            /* Check the flag changes at first */
            if(Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Flags != Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags)
            {
                /* Set flag changed label */
                Ea_Rb_MigOrder_st.isFlagChanged_b   = TRUE;

                /* Case 1: SL2--> SL1 */
                if((((Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
                        && ((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) <= 0))
                    && (Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen == (Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkRealLen*2u)))
                {
                    /* Choose one block with higher version and valid data, delete another copy */

                    /* Get ready to read the data to check the CRC32, block header both valid, so if data is valid should be checked */

                    /* Store the block start address at first */
                    Ea_Rb_MigOrder_st.adReadStart_uo    = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;
                    Ea_Rb_MigOrder_st.adWriteStart_uo   = Ea_Rb_MigOrder_st.adReadStart_uo;

                    Ea_Rb_MigOrder_st.BlockData_CS_u32  = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].NvMIdx;
                    Ea_Rb_MigOrder_st.numBytes_uo       = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Length;
                    Ea_Rb_MigOrder_st.isSecLevelCurr_b  = TRUE;

                    Ea_Rb_MigBlockHeader_st.BlockID_u16  = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].NvMIdx;
                    Ea_Rb_MigBlockHeader_st.BlockLen_u16 = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].Length;

                    /* Set block version to zero, it's used only for block version compare */
                    Ea_Rb_MigBlockHeader_st.BlockVersion_u16 = 0;

                    /* Start to check block data valid */
                    if(Ea_Rb_CheckBlockValid(Ea_Rb_MigOrder_st.adReadStart_uo, &Ea_Rb_MigBlockHeader_st, EA_RB_MIGRATION_E, TRUE) == EA_RB_ST_OK_E)
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECK_DATA_E;
                    }
                    else
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                    }
                }
                else
                {
                    /* Any other cases: SL1-->SL2, No-Survival <--> Survival: overwrite the block header at first */

                    /* Get ready to read the block header */
                    Ea_Rb_MigOrder_st.adReadStart_uo    = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;
                    Ea_Rb_MigOrder_st.adWriteStart_uo   = Ea_Rb_MigOrder_st.adReadStart_uo;

                    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                    if(EA_EEP_READ(Ea_Rb_MigOrder_st.adReadStart_uo, (uint8 *)&Ea_Rb_MigBlockHeader_st, EA_BLK_HEADER_SIZE) == E_OK)
                    {
                        /* Next step to overwrite the old block header with new flag value */
                        Ea_Rb_MigOrder_st.MigOrderType_en   = EA_RB_MIG_WRITE_BLKHDR_E;
                    }
                    else
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                    }
                }
            }
            else
            {
                /* In case of block flag not changed */
                /* Set read start address */
                Ea_Rb_MigOrder_st.adReadStart_uo    = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;

                /* Set move data length */
                if(Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen == (Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkRealLen*2u))
                {
                    Ea_Rb_MigOrder_st.numBytes_uo   = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkRealLen;
                }
                else
                {
                    Ea_Rb_MigOrder_st.numBytes_uo   = Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen;
                }

                /* For survival block there are no fix address, it should be located in permanent area */
                if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0 )
                {
                    /* Survival Block Handling is done before the start of Migration. So this part of code is not attained. To be removed in the future. */
                }
                else
                {
                    /* Set write address: target address */
                    Ea_Rb_MigOrder_st.adWriteStart_uo   = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;

                    Ea_Rb_MigStartToMoveBlock();
                }
            }
        }
        else
        {
            /* This block is a new block, no data in old layout: write default block header with NO_DATA */

            /* Set the write address at first, it should be set extra because for the second copy of SL2 blocks,
             * because in that case it isn't same as the block start address */

            if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SURVIVAL_FLAG) > 0 )
            {
                /* Survival block are already handled before Migration. So no operation is performed here */
            }
            else
            {
                Ea_Rb_MigOrder_st.adWriteStart_uo = Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkStartAddr;
            }

            if((Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
            {
                Ea_Rb_MigOrder_st.isSecLevelCurr_b = TRUE;
            }
            else
            {
                Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;
            }

            /* New block: write block header only */
            Ea_Rb_WriteBlockHeader((Ea_Rb_MigCurNr_u16-1), &Ea_Rb_MigBlockHeader_st);
        }
    }
}

/**
 *********************************************************************
 * Ea_Rb_MigStartToMoveBlock():
 *
 * This function starts block moving.
 *
 * \param   void
 * \return  void
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
void Ea_Rb_MigStartToMoveBlock(void)
{
    /* Set moving parameters for last block to clip board start address */
    Ea_Rb_MigOrder_st.isSecLevelCurr_b  = FALSE;
    Ea_Rb_MigOrder_st.isMoveToEepEnd_b  = FALSE;
    Ea_Rb_MigOrder_st.isToBeErase_b     = TRUE;

    /* Check for redundant block if it is really redundant on EEPROM (old layout)*/
    if(Ea_BlockProperties[Ea_Rb_MigCurNr_u16-1].BlkRealLen == (Ea_BlockProperties_onEep[Ea_Rb_MigCurNr_u16-1].BlkRealLen*2u))
    {
        Ea_Rb_MigOrder_st.isSecLevelCurr_b  = TRUE;
        Ea_Rb_MigOrder_st.isCopyWritten_b   = TRUE;
    }
    else
    {
        Ea_Rb_MigOrder_st.isSecLevelCurr_b  = FALSE;
        Ea_Rb_MigOrder_st.isCopyWritten_b   = FALSE;
    }

    Ea_Rb_MigOrder_st.isCopyWritten_b   = FALSE;

    /* Start to move block */
    if(Ea_Rb_MigMoveBlock((const Ea_Rb_MigOrder_tst *)&Ea_Rb_MigOrder_st, TRUE) == EA_RB_ST_OK_E)
    {
        Ea_Rb_MigOrder_st.MigOrderType_en   = EA_RB_MIG_MOVING_WAIT_E;
    }
    else
    {
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
    }
}

/**
 *********************************************************************
 *  Ea_Rb_MigrationOrderCheck(): Check whether this Migration order
 *  is independent of last executed Eep_JobResult
 * \param    None
 * \return
 * \retval   TRUE - Don't require last Executed Eep_JobResult status
 *			 FALSE - Require last Executed Eep_JobResult status
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
boolean Ea_Rb_MigrationOrderCheck(void)
{
	boolean	xRetVal_b = FALSE;
	switch(Ea_Rb_MigOrder_st.MigOrderType_en)
	{
		case EA_RB_MIG_ERROR_E:
		case EA_RB_MIG_NOT_POSSIBLE_E:
			xRetVal_b = TRUE;			/* These states don't depends on last executed Eep_JobResult */
			break;

		/* Default state */
        default:
            /* Default state, no action required */
			break;
	}
	return xRetVal_b;
}

#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
/**
 *********************************************************************
 *  Ea_Rb_MigrationStatus(): Returns the Migration status to appliation layer.
 *  This is Not applicable to boot mode.
 * \param    None
 * \return	return Migration Status
 * \retval  EA_RB_MIGRATION_NOTNEEDED
 *			EA_RB_MIGRATION_RUNNING
 *			EA_RB_MIGRATION_FINISHED
 *			EA_RB_MIGRATION_ERROR
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
uint8 Ea_Rb_MigrationStatus(void)
{
	return(Ea_Rb_MigrationStaus_u8);
}

#endif

/**
 *********************************************************************
 *  Ea_Rb_MigClipAddrCheckSpace(): Updates Proper clip address.
 *  If there is no space returns False else Returns True.
 *  This is Not applicable to boot mode.
 * \param    CurrMigBlk_u16  	The current block for which migration
 *								operation is ongoing
 * \param	 NumBytes_u16		The Number of bytes of Migration/Write
 *								or Invalidate order request.
 * \return	return  ClipBoard space available or not.
 * \retval  TRUE	ClipBoard space was available and Clipboard Address
 *					is Updated.
 *			FALSE	ClipBoard is full cannot be reused anymore.
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */

boolean Ea_Rb_MigClipAddrCheckSpace(uint16 CurrMigBlk_u16, uint16 NumBytes_u16)
{
    boolean xRetVal_b = TRUE;
    boolean tmpMigNotPossibleFlag_b = FALSE;
    uint16 cnt_u16 = 0;
    uint32 tmpClipEndAdr_u32;
    tmpClipEndAdr_u32 = (Ea_Rb_MigClipSrtAdr_u32 + (uint32)NumBytes_u16) - 1uL;

    /* Check if the new Clip board address clashes with any of the Blocks already present in the Clip board due to external user requests*/
    for(cnt_u16=CurrMigBlk_u16; cnt_u16>0; cnt_u16--)
    {
        if((tmpClipEndAdr_u32 >= Ea_Rb_MigHeader_st.MigPerStartAddr_u32) || (tmpClipEndAdr_u32 > (Eep_Rb_RealSize_u32-1U)))
        {
            if((Ea_Rb_MigNotPossibleFlag_b == TRUE)||(tmpMigNotPossibleFlag_b == TRUE))
            {
                xRetVal_b = FALSE;
                break;
            }
            else
            {
                /* Disable interrupts */
				SchM_Enter_Ea_Order();

				Ea_Rb_MigClipSrtAdr_u32 = Ea_Rb_MigClipBaseSrtAdr_u32;

				/* Enable interrupts */
				SchM_Exit_Ea_Order();

                tmpClipEndAdr_u32 = (Ea_Rb_MigClipSrtAdr_u32 + (uint32)NumBytes_u16) - 1uL;
                tmpMigNotPossibleFlag_b = TRUE;
                /* MR12 RULE 14.2 VIOLATION: Loop control variable needed to be reset in order to do thorough checking */
                cnt_u16=CurrMigBlk_u16 + 1uL;   /* Since we are updating loop control value inside the for Loop. cnt_u16 value is incremented by One */
            }
        }
        else
        {
            if((Ea_BlockProperties_onEep[cnt_u16-1].BlkStartAddr >= Ea_Rb_MigClipBaseSrtAdr_u32)&&(Ea_BlockProperties_onEep[cnt_u16-1].BlkEndAddr < Ea_Rb_MigHeader_st.MigPerStartAddr_u32))
            {
                if(((Ea_BlockProperties_onEep[cnt_u16-1].BlkStartAddr >= Ea_Rb_MigClipSrtAdr_u32) && (Ea_BlockProperties_onEep[cnt_u16-1].BlkStartAddr <= (tmpClipEndAdr_u32)))
                || ((Ea_BlockProperties_onEep[cnt_u16-1].BlkEndAddr >= Ea_Rb_MigClipSrtAdr_u32) && (Ea_BlockProperties_onEep[cnt_u16-1].BlkEndAddr <= (tmpClipEndAdr_u32)))
                || ((Ea_BlockProperties_onEep[cnt_u16-1].BlkStartAddr <= Ea_Rb_MigClipSrtAdr_u32) && (Ea_BlockProperties_onEep[cnt_u16-1].BlkEndAddr >= (tmpClipEndAdr_u32))))
                {
                    /* Disable interrupts */
					SchM_Enter_Ea_Order();

					Ea_Rb_MigClipSrtAdr_u32 = Ea_BlockProperties_onEep[cnt_u16-1].BlkEndAddr + 1U;

					/* Enable interrupts */
					SchM_Exit_Ea_Order();

                    tmpClipEndAdr_u32 = (Ea_Rb_MigClipSrtAdr_u32 + (uint32)NumBytes_u16) - 1uL;
                    /* MR12 RULE 14.2 VIOLATION: Loop control variable needed to be reset in order to do thorough checking */
                    cnt_u16=CurrMigBlk_u16 + 1uL;  /* Since we are Setting loop control value inside the for Loop. cnt_u16 value is incremented by One */
                }
                else
                {
                    /* Added for MISRA */
                }
            }
            else
            {
                /* Added for MISRA */
            }
        }
    }

    return xRetVal_b;
}

#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
/**
 *********************************************************************
 *  Ea_Rb_MigCheckUsrDataWritten(): Checks whether any user request is
 *  written in the given Address.
 * \param   EraseHeaderAddr_32
 * \return	return Ea_Rb_MigCheckUsrDataWritten Status
 * \retval  FALSE  - User Request is Not Written
 *			TRUE   - User Request is Written
 *			
 * \seealso
 * \usedresources
 *********************************************************************/

static boolean Ea_Rb_MigCheckUsrDataWritten(Eep_AddressType EraseHeaderStartAddr_uo)
{
	uint16 Block_No;
	boolean xRetVal_b = FALSE;
	Eep_AddressType tmpEraseHeaderEndAddr_uo = (EraseHeaderStartAddr_uo + EA_BLK_HEADER_SIZE) - 1u;
	
	for(Block_No=0;Block_No < EA_NUM_BLOCKS;Block_No++)
	{
		/* For the below check Interupt Enable/Disable is not needed because if the below check is interrupted and user request is placed in the same block number,
		In this case the Erase will be done this is not a problem since only request is accepted the data write is not yet happened. The data write will be happening 
		only after the Eep Header Erase operation is done */
		if( ((EraseHeaderStartAddr_uo >= Ea_BlockProperties_onEep[Block_No].BlkStartAddr)&&(EraseHeaderStartAddr_uo <= Ea_BlockProperties_onEep[Block_No].BlkEndAddr)) ||
			((tmpEraseHeaderEndAddr_uo >= Ea_BlockProperties_onEep[Block_No].BlkStartAddr)&&(tmpEraseHeaderEndAddr_uo <= Ea_BlockProperties_onEep[Block_No].BlkEndAddr)) )
		{
			xRetVal_b = TRUE;
			break;		/* User data is present in that address skip Erasing */
		}			

	}
	return xRetVal_b;
}
#endif		/* Ea_Rb_MigCheckUsrDataWritten function */

#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

