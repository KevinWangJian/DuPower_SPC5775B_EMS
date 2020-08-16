

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
#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
uint16 Ea_Rb_MigFoundBlkNr_u16;      /* The current block number which should be placed to the right address */
uint16 Ea_Rb_MigNumBytesTmp_u16;       /* Number of bytes to be read during block validation in init */
uint16	Ea_Rb_MigScanSize_u16;						/* Number of bytes already scanned */
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"
uint32 Ea_Rb_MigLayoutEnd_u32;
uint32 Ea_Rb_MigBlockData_CS_u32;      /* Checksum for init time block validation - used for second appearence of same ID */
#define EA_STOP_SEC_VAR_CLEARED_32
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
Ea_Rb_MigOrder_tst Ea_Rb_MigOrder_st;
Ea_Rb_BlockHeader_tst Ea_Rb_MigBlockHeader_st;      /* Block header information of the order block */
Ea_Rb_MigHeader_tst Ea_Rb_MigHeader_st;             /* Layout migration header information of all EEPROM */
Ea_Rb_MigSecondBlkValid_tst Ea_Rb_MigSecondBlkValid_st;  /* Temporary structure to validate the second found block */
Ea_Rb_BlockHeader_tst Ea_Rb_MigBlockHeaderTemp_st;	/* Block header information to read the multiple instance for same ID */
Eep_AddressType Ea_Rb_MigScanAddr_uo;               /* Start address for current scanning in 256byte buffer */

/* The layout on EEPROM has unknown block number, but we should keep only the blocks, which also in new layout exist.
 * So only these block will be stored in Ea_BlockProperties_onEep[], and this array has maximal EA_NUM_BLOCKS block
 * elements. */
Ea_BlockPropertiesType Ea_BlockProperties_onEep[EA_NUM_BLOCKS];
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
boolean Ea_Rb_MigScanflag_b;
boolean Ea_Rb_MigVirginEepromFlag_b;
boolean Ea_Rb_MigNotPossibleFlag_b;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/**
 *********************************************************************
 * Ea_Rb_MigrationInit(): read all blocks and check if migration needed
 *
 * This function reads reserved EEPROM part, compares the migration marker
 * with EA_MIGRATION_MARKER. If different detected, starts to read all
 * relevant blocks which exist in EEPROM.
 *
 * \return   Order acceptance status
 * \retval   E_OK:      Migration was successful
 * \retval   E_NOT_OK:  Migration failed
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_MigrationInit(void)
{
    boolean isHeaderCRCValid_b = FALSE;
	boolean tmpMigNotPossible_b = FALSE;
    uint16 tmpCRC16_u16 = 0;
	uint16 clipTmpCRC16_u16 = 0;
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en;
    MemIf_JobResultType stJobResultOfEep_en;
#if (EA_PRV_DEBUGGING != FALSE)
    uint32 xIniTimeEnd_u32;
#endif

    /* Get current job result of Eep */
    stJobResultOfEep_en = Eep_GetJobResult();

    /* Check if the Eep job finished */
	/* Ea_Rb_MigrationInitOrderCheck(): Check whether this Migration order is independent of last Executed Eep_JobResult status */
	if(stJobResultOfEep_en == MEMIF_JOB_PENDING)
    {
        /* Do nothing, just wait */
    }
	/* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    else if((stJobResultOfEep_en == MEMIF_JOB_OK)||(Ea_Rb_MigrationInitOrderCheck() == TRUE))
    {
        switch(Ea_Rb_MigOrder_st.MigOrderType_en)
        {
            case EA_RB_NO_MIGRATION_E:
                if(Ea_Rb_MigChecked_b)
                {
                    /* Migration necessity has been checked */
                    /* Stop migration */
                    Ea_Rb_MigStop();

                    Ea_Rb_MigInit_b    = FALSE;
                }
                else
                {
                    /* Migration necessity has not been checked: start to read migration header */
                    /* Read reserved part of EEPROM */

                    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                    stRet_u8 = EA_EEP_READ(EEP_BASE_ADDRESS, (uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);
                    if(stRet_u8 == E_OK)
                    {
                        #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_BASECLIP_READ_E;
						#else
							Ea_Rb_MigOrder_st.adReadStart_uo = EA_EEP_START_OFFSET;
	               			Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECKMARKER_E;
						#endif
                    }
                    else
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                    }
                }
                break;

			case EA_RB_MIG_BASECLIP_READ_E:
				/* Read Stored Value of Initial ClipBoard Address only if Temporary Marker is set */
				if((Ea_Rb_MigHeader_st.MigMarker_u32 == (uint32)EA_MIGRATION_MARKER_TEMP))
				{
					/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                    stRet_u8 = EA_EEP_READ((EEP_BASE_ADDRESS + EA_RB_MIGCLIP_ADDR_OFFSET), (uint8 *)&Ea_Rb_MigClipDetails_st, EA_MIGCLIP_DETAILS_SIZE);
	                if(stRet_u8 == E_OK)
	                {
	                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_BASECLIP_READ_WAIT_E;
	                }
	                else
	                {
	                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
	                }
				}
				else
				{
					Ea_Rb_MigOrder_st.adReadStart_uo = EA_EEP_START_OFFSET;
	                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECKMARKER_E;
				}

			break;
			case EA_RB_MIG_BASECLIP_READ_WAIT_E:
				/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
            	clipTmpCRC16_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigClipDetails_st, EA_BASE_MIGCLIP_ADDR_SIZE, EA_MARKER_PATTERN, FALSE);

				/* CRC of Clipdetails should be validated only 1. CRC corrupted, 2. Marker corrupted. (Sometimes corruption of Marker and address might result in Same CRC) */
				if((clipTmpCRC16_u16 != Ea_Rb_MigClipDetails_st.MigClipBaseAddr_CS_u16)||(Ea_Rb_MigClipDetails_st.MigClipMarker_u16 != (uint16)EA_BASE_CLIP_MARKER))
				{
					if(Ea_Rb_MigHeader_st.MigEndAddr_u32 == (Eep_Rb_RealSize_u32-1u))
					{
					    /* If the Clip details stored is corrupted then only one cycle of Clip board area usage is possible as otherwise it can cause data corruption */
					    tmpMigNotPossible_b = TRUE;
					}
					else
					{
					    /* This is application to Boot mode so corruption of CRC need not be analyzed also set Mig clip update as TRUE then only write of Clipdetails possible */
                        Ea_Rb_MigClipUpdate_b = TRUE;
                    }
				}
				else
				{
					/* Added for MISRA */
				}

				Ea_Rb_MigOrder_st.adReadStart_uo = EA_EEP_START_OFFSET;
                Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECKMARKER_E;
			/* MR12 RULE 16.3 VIOLATION: Removing break statement will improve run time efficiency */
			case EA_RB_MIG_CHECKMARKER_E:

                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                tmpCRC16_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_MigHeader_st, (EA_BLK_HEADER_SIZE-2u), EA_MARKER_PATTERN, FALSE);

                if(tmpCRC16_u16 == Ea_Rb_MigHeader_st.MigHeader_CS_u16)
                {
                    /* Set migration header checked flag */
                    Ea_Rb_MigChecked_b = TRUE;

					if(tmpMigNotPossible_b != FALSE)
					{
						/* If the Clip details stored is corrupted then only one cycle of Clip board area usage is possible as otherwise it can cause data corruption */
						Ea_Rb_MigNotPossibleFlag_b = TRUE;
						tmpMigNotPossible_b = FALSE;
					}

                    /* Load layout end position of EEPROM */
                    if(Ea_Rb_MigHeader_st.MigEndAddr_u32 <= EEP_BASE_ADDRESS)
                    {
                        /* Layout end address for block searching, set to maximal */
                        Ea_Rb_MigHeader_st.MigEndAddr_u32   = Eep_Rb_RealSize_u32 - 1u;

                        /* Layout end address for old layout, set to minimal */
                        Ea_Rb_MigLayoutEnd_u32  = (uint32)EA_EEP_START_OFFSET - 1u;
                    }
                    else
                    {
                        /* In case of unsuccessful migration with layout end  = max: reload */
                        if(Ea_Rb_MigHeader_st.MigEndAddr_u32 >= (Eep_Rb_RealSize_u32 - 1u))
                        {
                            Ea_Rb_MigLayoutEnd_u32  = (uint32)EA_EEP_START_OFFSET - 1u;
                        }
                        else
                        {
                            /* Update layout end address */
                            Ea_Rb_MigLayoutEnd_u32  = Ea_Rb_MigHeader_st.MigEndAddr_u32;
                        }
                    }

                    if(Ea_Rb_MigHeader_st.MigMarker_u32 == (uint32)EA_MIGRATION_MARKER)
                    {
                        /* Same Layout, no migration needed */
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_NO_MIGRATION_E;
						#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
						/* Migration is not applicable for boot mode */
						Ea_Rb_MigrationStaus_u8 = EA_RB_MIGRATION_NOTNEEDED;
						#endif
                    }
                    else
                    {
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG == FALSE)
                        /* In case wrong permanent area start address: initialize it with EEPROM real size */
                        if((Ea_Rb_MigHeader_st.MigPerStartAddr_u32 > Eep_Rb_RealSize_u32)
                                || (Ea_Rb_MigHeader_st.MigPerStartAddr_u32 < Ea_Rb_MigHeader_st.MigEndAddr_u32))
                        {
                            Ea_Rb_MigHeader_st.MigPerStartAddr_u32  = Eep_Rb_RealSize_u32;
                        }
#endif
                        /* Start migration, read all block header at first */
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_LOAD_BLKHDR_E;

                        /* Get ready to read next block header */
                        /* Load next free start address */
                        Ea_Rb_MigOrder_st.adReadStart_uo = (uint32)EA_EEP_START_OFFSET;

                        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                        stRet_u8 = EA_EEP_READ(Ea_Rb_MigOrder_st.adReadStart_uo, (uint8 *)&Ea_Rb_dMigDataBuf_u8[0], EA_RB_MIG_BUFFER_SIZE);

                        if(stRet_u8 == E_OK)
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
                }
                else
                {
                    /* Checksum of layout migration header invalid --> Read the second copy */

                    if(!Ea_Rb_MigChecked_b)
                    {
                        /* Read reserved part of EEPROM */
                        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                        stRet_u8 = EA_EEP_READ((EEP_BASE_ADDRESS + EEP_LAYOUT_HEADER_SIZE), (uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);
                        if(stRet_u8 == E_OK)
                        {
							#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
								Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_BASECLIP_READ_E;
							#else
								Ea_Rb_MigOrder_st.adReadStart_uo = EA_EEP_START_OFFSET;
								Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECKMARKER_E;
							#endif
                            /* This is the read of second migration header: No more check necessary */
                            Ea_Rb_MigChecked_b = TRUE;
                        }
                        else
                        {
                            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                        }
                    }
                    else
                    {
                        /* Both block header invalid: search it manually
                         * and the end of layout unknown --> Set the end of layout
                         * to the maximal address of EEPROM */

						/* Set the Virgin Eeprom Flag as True as this is virgin Eeprom Case */
						Ea_Rb_MigVirginEepromFlag_b = TRUE;

						/* Layout end address for old layout, set to minimal */
                        Ea_Rb_MigLayoutEnd_u32  = (uint32)EA_EEP_START_OFFSET - 1u;

                        /* Reset all parameters because of the invalid migration header */
                        Ea_Rb_MigOrder_st.adReadStart_uo        = EA_EEP_START_OFFSET;
                        Ea_Rb_MigHeader_st.MigStartOff_u16      = EA_EEP_START_OFFSET;
                        Ea_Rb_MigHeader_st.MigEndAddr_u32       = Eep_Rb_RealSize_u32-1u;
                        Ea_Rb_MigHeader_st.MigPerStartAddr_u32  = Eep_Rb_RealSize_u32;
                        Ea_Rb_MigHeader_st.MigMarker_u32        = EA_MIGRATION_MARKER_TEMP;

                        #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
                            Ea_Rb_isMigHeaderDiff_b = TRUE;
                        #endif

                        /* Get ready to read next block header */
                        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                        stRet_u8 = EA_EEP_READ(Ea_Rb_MigOrder_st.adReadStart_uo, (uint8 *)&Ea_Rb_dMigDataBuf_u8[0], EA_RB_MIG_BUFFER_SIZE);

                        if(stRet_u8 == E_OK)
                        {
                            /* Start migration, read all block header at first */
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
                }

                break;

            case EA_RB_MIG_LOAD_BLKHDR_E:
                /* Start the migration:*/
				if(Ea_Rb_MigScanflag_b != FALSE)
				{
					/* Copy the header info from buffer to Mig block header structure. */
					Ea_Rb_CopyMigBlockHeader();
					Ea_Rb_MigScanflag_b = FALSE;
				}

                /* Load the read block header to its own buffer
                 * Load the header CRC valid status in global variable for the first result */
                isHeaderCRCValid_b = Ea_Rb_HeaderCheck((const Ea_Rb_BlockHeader_tst*)&Ea_Rb_MigBlockHeader_st);

                if(isHeaderCRCValid_b)
                {
                    /* This is redundant block, check if it is the 2.copy after the first valid one:
                     * -- Same persistent ID  */
                    if((Ea_Rb_MigOrder_st.isSecLevelCurr_b)
                            && (Ea_Rb_MigFoundBlkNr_u16 > 0)
                            && (Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].NvMIdx == Ea_Rb_MigBlockHeader_st.BlockID_u16)
                            && (Ea_Rb_MigOrder_st.adReadStart_uo == (Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkEndAddr + 1u)))
                    {
                        /* Reset SL2 flag */
                        Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;

                        /* Calculate the aligned address */
                        Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                        /* Update real length */
                        Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkRealLen = (Ea_Rb_MigOrder_st.numAlignedBytes_uo + EA_BLK_HEADER_SIZE)*2u;

                        /* If only one copy version, load the end address */
                        Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkEndAddr  = (Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkStartAddr
                                                                                        + (Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkRealLen
                                                                                        - 1u));
                        /* Load next free start address */
                        Ea_Rb_MigOrder_st.adReadStart_uo = (Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].BlkEndAddr + 1u);

                        /* The layout end reached after next reading? */
                        Ea_Rb_MigStartCheck();
                    }
                    else
                    {
                        /* Case for
                         * -- non-redundant blocks or
                         * -- redundant block but first valid block header */

                        /* Block header valid: check block status (know/unknow, survival/not survival) */
                        Ea_Rb_CheckFirstFoundBlk(Ea_Rb_MigBlockHeader_st.BlockID_u16);
                    }
                }
                else
                {
                    /* The current block header invalid */
                    Ea_Rb_MigOrder_st.adReadStart_uo += 4u;

                    /* Check other preambel in this block header, start search address+4bytes, with length EA_BLK_HEADER_SIZE-4u */
                    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                    Ea_Rb_MigOrder_st.adReadStart_uo += Ea_Rb_FindPreambelInHdr(((const uint8*)&Ea_Rb_MigBlockHeader_st + 4u), (EA_BLK_HEADER_SIZE-4u));

                    /* The layout end reached after next reading? */
                    Ea_Rb_MigStartCheck();
                }
                 /* -- read all block header at first
                 * -- store the block information to Ea_BlockProperties_onEep for the further compare */

                break;

            case EA_RB_MIG_CHECK_DATA_E:

                stRetSub_en = Ea_Rb_CheckBlockValid(Ea_Rb_MigOrder_st.adReadStart_uo, &Ea_Rb_MigBlockHeader_st, EA_RB_MIGRATION_E, FALSE);

                Ea_Rb_MigBlockEvaluation(stRetSub_en);

                break;

			case EA_RB_MIG_CHECKVALID_COPY_E:
				/* Check the valid block between first and second appearence of same ID */
				Ea_Rb_MigCheckSecondFoundBlkValid();

				break;

            case EA_RB_MIG_DELETING_E:

                Ea_Rb_MigOrder_st.isSecLevelCurr_b = FALSE;

				/* Read next block header with respect to the migration marker to reduce init timing */
				if((Ea_Rb_MigHeader_st.MigMarker_u32 != (uint32)EA_MIGRATION_MARKER_TEMP))
				{
					/* Read the next block header */
					Ea_Rb_MigOrder_st.adReadStart_uo += (Ea_Rb_MigOrder_st.numAlignedBytes_uo
                                                 + EA_BLK_HEADER_SIZE);
				}
				else
				{
					/* Read the next 16 bytes rather than going for the next block header */
					/* This change is made to make sure no existing block is lost during scanning */
					Ea_Rb_MigOrder_st.adReadStart_uo += EA_BLK_HEADER_SIZE;
				}

                /* The layout end reached after next reading? */
                Ea_Rb_MigStartCheck();

                break;

     #if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
            case EA_RB_MIG_WRITE_BLKHDR_E:

                    /* The layout end reached after next reading? */
                    Ea_Rb_MigStartCheck();

                break;
     #endif
			case EA_RB_MIG_BASECLIP_WRITE_WAIT_E:


				/* Get ready to migration, change the layout end address to recognize migration is running */
                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                stRet_u8 = EA_EEP_WRITE(EEP_BASE_ADDRESS, (const uint8 *)&Ea_Rb_MigHeader_st, EEP_LAYOUT_HEADER_SIZE);
                if(stRet_u8 == E_OK)
                {
                    /* switch to run migration */
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_WRITE_MIGHDR_TEMP_E;
                }
				else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }


			break;

            case EA_RB_MIG_WRITE_MIGHDR_TEMP_E:

                /* Get ready to read next block header */
                /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
                stRet_u8 = EA_EEP_WRITE((EEP_BASE_ADDRESS + EEP_LAYOUT_HEADER_SIZE),
                                            (const uint8 *)&Ea_Rb_MigHeader_st,
                                            EEP_LAYOUT_HEADER_SIZE);

                if(stRet_u8 == E_OK)
                {
                    #if (EA_PRV_DEBUGGING != FALSE)
                    xIniTimeEnd_u32 = Mcu_Rb_GetSysTimePart(TIM0);

                    Ea_Prv_stModuleTest_st.Ea_DataReadDiff_u32 =
                            MCU_RB_TIM0TICKS_TO_US(xIniTimeEnd_u32 - Ea_Prv_stModuleTest_st.Ea_MigrationTimeStart_u32);
                    #endif
            #if((EA_NUM_SURVIVAL_BLOCKS > 0)&&(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE))
                    /* Set the default value of variable which checks if Survival blocks are to be handled as False */
                    Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingOver_b = FALSE;
                    /* Set the Initial state as EA_RB_MIG_SURVBLK_HANDLING_INIT_E */
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_SURVBLK_HANDLING_INIT_E;
            #else
                    /* Ready for migration */
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
            #endif
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }

                break;

            case EA_RB_MIG_ERROR_E:
                /* Stop the migration init */
                Ea_Rb_MigInit_b = FALSE;

                /* Call error report */
                Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATIONINIT, EA_E_RB_MIGRATION_FAILED);

                break;

            case EA_RB_MIG_NOT_POSSIBLE_E:
                /* Stop the migration init*/
                Ea_Rb_MigInit_b = FALSE;

                /* Call error report */
                Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATIONINIT, EA_E_RB_MIGRATION_NOT_POSSIBLE);

                break;

            case EA_RB_MIG_RUNNING_E:

                /* Reset the migration initialization flag */
                Ea_Rb_MigInit_b = FALSE;

                break;
        #if(EA_NUM_SURVIVAL_BLOCKS > 0)
            case EA_RB_MIG_SURVBLK_HANDLING_INIT_E:

                Ea_Rb_MigSurvBlkHandlingInit();

                break;

            case EA_RB_MIG_SURVBLK_HANDLING_ERROR_E:
                /* Stop the migration init*/
                Ea_Rb_MigInit_b = FALSE;
                /* Set Migration running as FALSE to stop Survival Block Handling and Migration operation */
                Ea_Rb_MigStop();

			break;

        #endif

            default:
                Ea_Rb_MigInit_b     = FALSE;
                /* Stop migration */
                Ea_Rb_MigStop();

                /* Call error report */
                Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATION, EA_E_RB_MIGRATION_FAILED);

                break;
        }
    }
    else
    {
        /* Stop the migration init */
        Ea_Rb_MigInit_b = FALSE;

        /* Call error report */
        Ea_Rb_CheckMigrationErr(EA_SID_RB_MIGRATIONINIT, EA_E_RB_MIGRATION_FAILED);
    }

    return;
}

/**
 *********************************************************************
 * Ea_Rb_CheckFirstFoundBlk()
 *
 *This function checks the first found block on EEPROM, if:
 *** it has been read in old layout?
 *** it is configured in new layout? If yes, with same length?
 *** it is a permanent block in permanent area?
 *
 * \param   PersistentID_u16: found block persistent ID
 * \return  void
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
void Ea_Rb_CheckFirstFoundBlk(uint16 PersistentID_u16)
{
    /* Initialize status of found block for this persistent ID */
    boolean stBlkFound_b = FALSE;
    uint16 locFoundBlkNr_u16;
	Std_ReturnType stRet_u8 = E_OK;

    /* Search this Persistent ID in known layout on EEPROM (old layout) */
    locFoundBlkNr_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties_onEep[0], PersistentID_u16);

    if(locFoundBlkNr_u16 < EA_NUM_BLOCKS)
    {
        /* This block exists in old layout more than once */
		/* Check the second appearence block length is same as Ea_BlockProperties ID length */

		if((Ea_Rb_MigSecondBlkValid_st.BlockLen_u16 == Ea_Rb_MigBlockHeader_st.BlockLen_u16) &&
			(Ea_Rb_MigSecondBlkValid_st.BlockID_u16 == Ea_Rb_MigBlockHeader_st.BlockID_u16) &&
			(Ea_Rb_MigSecondBlkValid_st.BlockLen_u16 != 0u) && (Ea_Rb_MigSecondBlkValid_st.BlockID_u16 != 0u))
		{
			/*	This condition should be reached only for below special case:   							*
			*	Redundent block with 2 copies present in both Clipboard and also inside layout.    			*
			*	1. Block version info of block which is present inside layout is same as block         		*
			*	version info of Clipboard first copy and 													*
			*	2. Clipboard second copy is having higher version.											*
			*	we are skipping this inorder to save the Ea Init Time										*/


			/* if backup persistent ID and backup length is matching then skip reading this block */
			Ea_Rb_MigOrder_st.adReadStart_uo +=  EA_BLK_HEADER_SIZE;

			/* The layout end reached after next reading? */
			Ea_Rb_MigStartCheck();

		}
		else if(Ea_BlockProperties[locFoundBlkNr_u16].Length == Ea_Rb_MigBlockHeader_st.BlockLen_u16)
		{
			Ea_Rb_MigSecondBlkValid_st.adStart_uo =  Ea_BlockProperties_onEep[locFoundBlkNr_u16].BlkStartAddr;
			Ea_Rb_MigSecondBlkValid_st.numBytes_u16 = Ea_BlockProperties_onEep[locFoundBlkNr_u16].Length;
			/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
			stRet_u8 = EA_EEP_READ(Ea_Rb_MigSecondBlkValid_st.adStart_uo, (uint8 *)&Ea_Rb_MigBlockHeaderTemp_st, EA_BLK_HEADER_SIZE);
			if(stRet_u8 == E_OK)
			{
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECKVALID_COPY_E;
				Ea_Rb_MigSecondBlkValid_st.OrderType_en   = EA_RB_MIG_BLOCK_VERSION_COMPARE_E;
			}
			else
			{
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
			}
		}
		else
		{
			/* Second found block has different length */
		   Ea_Rb_MigOrder_st.adReadStart_uo +=  EA_BLK_HEADER_SIZE;

			/* The layout end reached after next reading? */
		   Ea_Rb_MigStartCheck();
		}

		Ea_Rb_MigSecondBlkValid_st.BlockLen_u16 = 0;  /* Clear the backup length */
		Ea_Rb_MigSecondBlkValid_st.BlockID_u16 = 0;  /* Clear the backup persistent ID */
    }
    else
    {
        /* If it's the only block in old layout till now, then search in new layout:
         * -- If it's found in new layout, then load all information in the properties structure
         * -- If it doesn't appear in new layout, just ignore it and start to the next header reading */

        /* Search this Persistent ID in given layout from block configuration (new layout) */
        Ea_Rb_MigFoundBlkNr_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], PersistentID_u16);

        /* This found block exists in new layout */
        if(Ea_Rb_MigFoundBlkNr_u16 < EA_NUM_BLOCKS)
        {
            #if(EA_DEV_ERROR_DETECT != FALSE)
			/* Block exists in new layout but different length, different Survival Attribute or different security level throw DET */
			/* Exempt the Reserved Block ID from the DET check as per request of Productline */
			/* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
			if((PersistentID_u16 != EA_RESERVED_BLK_ID) && ((Ea_BlockProperties[Ea_Rb_MigFoundBlkNr_u16].Length != Ea_Rb_MigBlockHeader_st.BlockLen_u16)||
			((Ea_BlockProperties[Ea_Rb_MigFoundBlkNr_u16].Flags & EA_SECURITY_LEVEL_FLAG) != (Ea_Rb_MigBlockHeader_st.BlockFlags_u8 & EA_SECURITY_LEVEL_FLAG))||
			((Ea_BlockProperties[Ea_Rb_MigFoundBlkNr_u16].Flags & EA_SURVIVAL_FLAG) != (Ea_Rb_MigBlockHeader_st.BlockFlags_u8 & EA_SURVIVAL_FLAG))))
			{
			    /* Report error to DET about block length mismatch */
                (void)Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, EA_SID_RB_MIGRATIONINIT, EA_E_RB_BLOCK_LENGTH_MISMATCH);
			}
			#endif
			/* If found block in new layout: Check the block length */
            if(Ea_BlockProperties[Ea_Rb_MigFoundBlkNr_u16].Length == Ea_Rb_MigBlockHeader_st.BlockLen_u16)
            {
                /* Block found in new layout */
                stBlkFound_b = TRUE;

                /* Store the block start address at first */
                Ea_Rb_MigOrder_st.adWriteStart_uo = Ea_Rb_MigOrder_st.adReadStart_uo;

                /* Update block properties in onEep array */
                Ea_Rb_LoadBlkProperties(Ea_Rb_MigFoundBlkNr_u16, (Ea_Rb_BlockHeader_tst const *)&Ea_Rb_MigBlockHeader_st);

                /* Update old layout end address (excl. survival blocks)*/
                if((Ea_Rb_MigLayoutEnd_u32 < (Ea_Rb_MigOrder_st.adReadStart_uo - 1u))
                    && ((Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].Flags & (uint8)EA_SURVIVAL_FLAG) <= 0))
                {
                    Ea_Rb_MigLayoutEnd_u32 = Ea_Rb_MigOrder_st.adReadStart_uo - 1u;
                }

                /* The layout end reached after next reading? */
                Ea_Rb_MigStartCheck();
            }
        }

        if(!stBlkFound_b)
        {
            /* This block doesn't exist in new layout, check if it's a survival block?
             * -- Yes: block in new layout with same persistent ID found?
             *      -- Yes: delete it because of different length
             *      -- No: check if it has been stored in permanent area?
             *              -- Yes: an unknown survival block, let it stay and go further
             *              -- No: check validate, move it to permanent area
             * -- No:  it will be erased and overwritten if needed */
#if((EA_RB_ACT_SURVIVAL_EVAL != FALSE) || (EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE))
            if(((Ea_Rb_MigBlockHeader_st.BlockFlags_u8 & (uint8)EA_SURVIVAL_FLAG) > 0u) && (Ea_Rb_MigFoundBlkNr_u16 == EA_NUM_BLOCKS))
            {
                if(Ea_Rb_MigOrder_st.adReadStart_uo >= Ea_Rb_MigHeader_st.MigPerStartAddr_u32)
                {
                    /* An unknown survival block found in permanent area: ignore and search */
                    /* Calculate the aligned address */
                    Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                    Ea_Rb_MigOrder_st.adReadStart_uo += (Ea_Rb_MigOrder_st.numAlignedBytes_uo + EA_BLK_HEADER_SIZE);

                    /* The layout end reached after next reading? */
                    Ea_Rb_MigStartCheck();
                }
                else
                {
                    /* An unknown survival block found not in permanent area */

                    /* Get ready to read the data to check the CRC32 */

                    /* Store the block start address at first */
                    Ea_Rb_MigOrder_st.adWriteStart_uo = Ea_Rb_MigOrder_st.adReadStart_uo;

                    Ea_Rb_MigOrder_st.BlockData_CS_u32 = Ea_Rb_MigBlockHeader_st.BlockID_u16;
                    Ea_Rb_MigOrder_st.numBytes_uo = Ea_Rb_MigBlockHeader_st.BlockLen_u16;

                    /* Set block version to zero, it's used only for block version compare */
                    Ea_Rb_MigBlockHeader_st.BlockVersion_u16 = 0;

                    if(Ea_Rb_CheckBlockValid(Ea_Rb_MigOrder_st.adReadStart_uo, &Ea_Rb_MigBlockHeader_st, EA_RB_MIGRATION_E, TRUE) ==  EA_RB_ST_OK_E)
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_CHECK_DATA_E;
                    }
                    else
                    {
                        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                    }
                }
            }
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
            else if (Ea_Rb_MigFoundBlkNr_u16 == EA_NUM_BLOCKS)
            {
                /* An unknown block (not a survival block) found: ignore and search */
                /* Calculate the aligned address */
                Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                Ea_Rb_MigOrder_st.adReadStart_uo += (Ea_Rb_MigOrder_st.numAlignedBytes_uo + EA_BLK_HEADER_SIZE);

                /* Update old layout end address (excl. survival blocks)*/
                if(Ea_Rb_MigLayoutEnd_u32 <(Ea_Rb_MigOrder_st.adReadStart_uo - 1u))
                {
                    Ea_Rb_MigLayoutEnd_u32 = Ea_Rb_MigOrder_st.adReadStart_uo - 1u;
                }

                /* The layout end reached after next reading? */
                Ea_Rb_MigStartCheck();
            }
#endif
            else
#endif
            {
                /* Block exists in new layout but different length:
                 * Delete the data no matter survival or not */

                /* Calculate the aligned address */
                Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                /* Delete */
				#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != FALSE)
					/* In BootMode the deletion will be happening in Init function */
					if(Eep_Erase(Ea_Rb_MigOrder_st.adReadStart_uo, EA_BLK_HEADER_SIZE) == E_OK)
					{
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETING_E;
					}
					else
					{
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
					}

				#else
					/* Application Mode */
					/* Application mode delete operation is moved to cyclic task */
					if(Ea_Rb_MigEraseBlkNr_u16 < EA_RB_MIG_ERASE_BUFFER_SIZE)
					{
						/* Store the block addresses to erase the block headers in cyclic task */						
						Ea_Rb_MigEraseBuffer_uo[Ea_Rb_MigEraseBlkNr_u16] = Ea_Rb_MigOrder_st.adReadStart_uo;
						
						Ea_Rb_MigEraseBlkNr_u16++;
						/* Setting the state to EA_RB_MIG_DELETING_E will not really erase the block herader here */
						/* Erasing the block headers done in cyclic task */
						Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETING_E;
					}
					else			
					{
						if(Eep_Erase(Ea_Rb_MigOrder_st.adReadStart_uo, EA_BLK_HEADER_SIZE) == E_OK)
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETING_E;
						}
						else
						{
							Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
						}
					}
				#endif
            }
        }
    }
}

/**
 *********************************************************************
 * Ea_Rb_MigBlockEvaluation()
 *
 *This function evaluates block validity of check result
 * \param   stRetSub_en: block valid check result
 * \return  void
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
void Ea_Rb_MigBlockEvaluation(Ea_Rb_stReturn_ten stRetSub_en)
{
    uint16 tmpCnt1_u16;

    switch(stRetSub_en)
    {
        case EA_RB_ST_OK_E:

            if((Ea_Rb_BlockData_CS_u32 != 0u) || (Ea_Rb_isDataCrcZero_b != FALSE))
            {
                /* In case that this block doesn't exist in new layout, happened only with survival blocks
                 * which not included in new configuration layout.
                 * normal unknown block (non-survival block) will not run here (not necessary)   */
                if(Ea_Rb_MigFoundBlkNr_u16 == EA_NUM_BLOCKS)
                {
                    /* Reload the new permanent area start address */
                    

                    if((Ea_Rb_MigHeader_st.MigPerStartAddr_u32 > Ea_Rb_MigOrder_st.adReadStart_uo)
                            && (Ea_Rb_MigOrder_st.adReadStart_uo > Ea_Rb_MigClipSrtAdr_u32)
                            && ((Ea_Rb_MigBlockHeader_st.BlockFlags_u8 & (uint8)EA_SURVIVAL_FLAG) > 0))
                    {
                        Ea_Rb_MigHeader_st.MigPerStartAddr_u32 = Ea_Rb_MigOrder_st.adReadStart_uo;
                    }
                    else
                    {
                        

                    }

                    /* This valid block doesn't exist in new layout
                     * Do not remove the unknown survival block from permanent area
                     * Search further */
                    Ea_Rb_MigOrder_st.adReadStart_uo += (Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16) + EA_BLK_HEADER_SIZE);

                    /* Load the information to onEep array */
                    Ea_Rb_MigStartCheck();
                }
                else
                {
                    /* Any other cases:
                     * -- survival blocks and it exist in new layout
                     * -- normal blocks  and it exist in new layout      */

                    tmpCnt1_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_MigBlockHeader_st.BlockID_u16);

                    Ea_Rb_LoadBlkProperties(tmpCnt1_u16, (Ea_Rb_BlockHeader_tst const *)&Ea_Rb_MigBlockHeader_st);

                    /* No flag changes */
                    Ea_Rb_MigStartCheck();
                }
            }
            else
            {
                /* No valid checksum, block invalid: delete the content */
                /* Calculate the aligned address */
                Ea_Rb_MigOrder_st.numAlignedBytes_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_MigBlockHeader_st.BlockLen_u16);

                /* Reload the start address of this block */
                Ea_Rb_MigOrder_st.adReadStart_uo = Ea_Rb_MigOrder_st.adWriteStart_uo;

                /* Erase the unused block */
                if(Eep_Erase(Ea_Rb_MigOrder_st.adWriteStart_uo, EA_BLK_HEADER_SIZE) == E_OK)
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_DELETING_E;
                }
                else
                {
                    Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
                }
            }
            break;

        case EA_RB_ST_PENDING_E:
            /* Do nothing, just wait */
            break;

        case EA_RB_ST_INVALIDATED_E:
            /* Invalidated block: load this block information */

            tmpCnt1_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_MigBlockHeader_st.BlockID_u16);

            Ea_Rb_LoadBlkProperties(tmpCnt1_u16, (Ea_Rb_BlockHeader_tst const *)&Ea_Rb_MigBlockHeader_st);

            /* No flag changes */
            Ea_Rb_MigStartCheck();

            break;

        default:
            /* Default state, no action required */
            break;
    }
}

/**
 *********************************************************************
 *  Ea_Rb_MigrationInitOrderCheck(): Check whether this Migration order
 *	is independent of last executed Eep_JobResult
 * \param    None
 * \return
 * \retval   TRUE - Don't require last Executed Eep_JobResult status
 *			 FALSE - Require last Executed Eep_JobResult status
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
boolean Ea_Rb_MigrationInitOrderCheck(void)
{
	boolean	xRetVal_b = FALSE;
	switch(Ea_Rb_MigOrder_st.MigOrderType_en)
	{
		case EA_RB_NO_MIGRATION_E:
		case EA_RB_MIG_ERROR_E:
		case EA_RB_MIG_NOT_POSSIBLE_E:
			xRetVal_b = TRUE;			/* These states don't need last executed Eep_JobResult */
			break;

        default:
            /* Default state, no action required */
			break;
	}
	return xRetVal_b;
}

/**
 *********************************************************************
 * Ea_Rb_CopyMigBlockHeader(): Block header Copy
 * This function is to copy the header info from buffer to block header structure.
 *
 * \param    none
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
/* MR12 RULE 8.7 VIOLATION: For future use this is declared as extern */
void Ea_Rb_CopyMigBlockHeader(void)
{
    uint8 tmp_u8;
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
	uint8* TargetHeader = (uint8*)&Ea_Rb_MigBlockHeader_st;

	if(Ea_Rb_MigScanSize_u16 < EA_RB_MIG_BUFFER_SIZE)
	{
		for(tmp_u8 = 0; tmp_u8 < EA_BLK_HEADER_SIZE;tmp_u8++)
		{
			TargetHeader[tmp_u8] = Ea_Rb_dMigDataBuf_u8[Ea_Rb_MigScanSize_u16 + tmp_u8];
		}
	}
}

/**
 *********************************************************************
 * Ea_Rb_MigCheckSecondFoundBlkValid():select the valid block b/w two copies.
 *
 * This function checks the block validation between the first and
 * second found copies. If the block versions are same, read the first
 * copy for CRC32 validation. else consider higher version copy as
 * valid block.
 *
 * \return   none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */

void Ea_Rb_MigCheckSecondFoundBlkValid(void)
{
	Std_ReturnType stRet_u8 = E_OK;

	switch(Ea_Rb_MigSecondBlkValid_st.OrderType_en)
	{
		case EA_RB_MIG_BLOCK_VERSION_COMPARE_E:
		/* Check the block versions are same? */
		/* Yes:  Read the data of first copy to check CRC32 validation */
		/* No :  update the higher version as the valid block */

		if(Ea_Rb_MigBlockHeader_st.BlockVersion_u16 == Ea_Rb_MigBlockHeaderTemp_st.BlockVersion_u16)
			{
				if(Ea_Rb_MigSecondBlkValid_st.numBytes_u16 < EA_DATA_BUFFER_SIZE)
				{
					Ea_Rb_MigNumBytesTmp_u16 = Ea_Rb_MigSecondBlkValid_st.numBytes_u16;
				}
				else
				{
					Ea_Rb_MigNumBytesTmp_u16 = EA_DATA_BUFFER_SIZE;
				}

				/* Read the data of first copy */
				Ea_Rb_MigSecondBlkValid_st.adStart_uo    += EA_BLK_HEADER_SIZE;
				stRet_u8 = EA_EEP_READ(Ea_Rb_MigSecondBlkValid_st.adStart_uo, &Ea_Rb_dMigDataBuf_u8[0], Ea_Rb_MigNumBytesTmp_u16);

				if(stRet_u8 == E_OK)
				{
					Ea_Rb_MigSecondBlkValid_st.OrderType_en = EA_RB_MIG_READ_DATA_TO_VALIDATE_E;
				}
				else
				{
					Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
				}
			}

				/* Check second found copy is higher version than first copy */
		else if(Ea_Rb_MigBlockHeader_st.BlockVersion_u16 > Ea_Rb_MigBlockHeaderTemp_st.BlockVersion_u16)
			{
				Ea_Rb_MigFoundBlkNr_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_MigBlockHeaderTemp_st.BlockID_u16);
				/* Store the block start address at first */
				Ea_Rb_MigOrder_st.adWriteStart_uo = Ea_Rb_MigOrder_st.adReadStart_uo;

				/* Update the second found block properties in onEep array */
				Ea_Rb_LoadBlkProperties(Ea_Rb_MigFoundBlkNr_u16, (Ea_Rb_BlockHeader_tst const *)&Ea_Rb_MigBlockHeader_st);

				/* Update old layout end address (excl. survival blocks)*/
				if((Ea_Rb_MigLayoutEnd_u32 < (Ea_Rb_MigOrder_st.adReadStart_uo - 1u))
					&& ((Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].Flags & (uint8)EA_SURVIVAL_FLAG) <= 0))
				{
					Ea_Rb_MigLayoutEnd_u32 = Ea_Rb_MigOrder_st.adReadStart_uo - 1u;
				}

				/* The layout end reached after next reading? */
				Ea_Rb_MigStartCheck();
			}
		else
			{
				/* Second found block version is lesser than On Eep structure version info */
				/* Keep the first instance properties of the same ID in onEep array */
				Ea_Rb_MigOrder_st.adReadStart_uo += EA_BLK_HEADER_SIZE;

				/* The layout end reached after next reading? */
				Ea_Rb_MigStartCheck();
			}

		break;

		case EA_RB_MIG_READ_DATA_TO_VALIDATE_E:

			/* Order length is equal to block length, no data has been read:
			 * it is the first time to calculate the CRC, initialize it only once here */
			if(Ea_Rb_MigSecondBlkValid_st.numBytes_u16 == Ea_Rb_MigBlockHeaderTemp_st.BlockLen_u16)
			{
				/* Initialize block data checksum with persistent ID */
				Ea_Rb_MigBlockData_CS_u32 = (uint32)Ea_Rb_MigBlockHeaderTemp_st.BlockID_u16;

				/* Reflect the start value for next CRC32 calculate */
				Ea_Rb_MigBlockData_CS_u32 ^= EA_CRC_XOR_VALUE32;
			}

			   /* Check the CRC_32 of data block */
			Ea_Rb_MigBlockData_CS_u32 = Crc_CalculateCRC32(&Ea_Rb_dMigDataBuf_u8[0],
																 Ea_Rb_MigNumBytesTmp_u16,
																 Ea_Rb_MigBlockData_CS_u32,
																 FALSE);
			/* Update actual start address and rest length */
			Ea_Rb_MigSecondBlkValid_st.numBytes_u16  -= Ea_Rb_MigNumBytesTmp_u16;
			Ea_Rb_MigSecondBlkValid_st.adStart_uo    += Ea_Rb_MigNumBytesTmp_u16;

            if(Ea_Rb_MigSecondBlkValid_st.numBytes_u16 == 0u)
            {
				if(Ea_Rb_MigBlockData_CS_u32 == Ea_Rb_MigBlockHeaderTemp_st.BlockData_CS_u32)
                {
					if((Ea_Rb_MigBlockHeader_st.BlockFlags_u8 & (uint8)EA_SECURITY_LEVEL_FLAG) > 0u)
					{
						Ea_Rb_MigSecondBlkValid_st.BlockID_u16 = Ea_Rb_MigBlockHeader_st.BlockID_u16;  	/* Take backup of current block Persistent ID */
						Ea_Rb_MigSecondBlkValid_st.BlockLen_u16 = Ea_Rb_MigBlockHeader_st.BlockLen_u16;	/* Take backup of current block length */
					}
					/* First copy is valid, keep the first instance properties of the same ID in onEep array */
					Ea_Rb_MigOrder_st.adReadStart_uo += EA_BLK_HEADER_SIZE;

					/* The layout end reached after next reading? */
					Ea_Rb_MigStartCheck();
				}
				else
				{
					Ea_Rb_MigFoundBlkNr_u16 = Ea_Prv_SearchBlockInProp((Ea_BlockPropertiesType const*)&Ea_BlockProperties[0], Ea_Rb_MigBlockHeaderTemp_st.BlockID_u16);

					/* First copy is invalid update the second copy */
					/* Store the block start address at first */
					Ea_Rb_MigOrder_st.adWriteStart_uo = Ea_Rb_MigOrder_st.adReadStart_uo;

					/* Update the second found block properties in onEep array */
					Ea_Rb_LoadBlkProperties(Ea_Rb_MigFoundBlkNr_u16, (Ea_Rb_BlockHeader_tst const *)&Ea_Rb_MigBlockHeader_st);

					/* Update old layout end address (excl. survival blocks)*/
					if((Ea_Rb_MigLayoutEnd_u32 < (Ea_Rb_MigOrder_st.adReadStart_uo - 1u))
						&& ((Ea_BlockProperties_onEep[Ea_Rb_MigFoundBlkNr_u16].Flags & (uint8)EA_SURVIVAL_FLAG) <= 0))
					{
						Ea_Rb_MigLayoutEnd_u32 = Ea_Rb_MigOrder_st.adReadStart_uo - 1u;
					}

					/* The layout end reached after next reading? */
					Ea_Rb_MigStartCheck();
				}
			}
			else
			{
				/* Check the rest block length to be read */
				if(Ea_Rb_MigSecondBlkValid_st.numBytes_u16 < EA_DATA_BUFFER_SIZE)
				{
					Ea_Rb_MigNumBytesTmp_u16 = Ea_Rb_MigSecondBlkValid_st.numBytes_u16;
				}
				else
				{
					Ea_Rb_MigNumBytesTmp_u16 = EA_DATA_BUFFER_SIZE;
				}

				/* Read the next buffer size data */
				stRet_u8 = EA_EEP_READ(Ea_Rb_MigSecondBlkValid_st.adStart_uo,
										  &Ea_Rb_dMigDataBuf_u8[0],
										  Ea_Rb_MigNumBytesTmp_u16);

				if(stRet_u8 == E_OK)
				{
					Ea_Rb_MigSecondBlkValid_st.OrderType_en = EA_RB_MIG_READ_DATA_TO_VALIDATE_E;
				}
				else
				{
					Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
				}
			}
		break;

		/* Default state */
		default:
				Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_ERROR_E;
		break;

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

