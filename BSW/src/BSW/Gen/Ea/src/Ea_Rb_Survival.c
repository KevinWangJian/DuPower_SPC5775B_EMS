
#include "Ea.h"

#if (EA_PRESENT == 1)
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
#include "Ea_Prv.h"
#include "Eep.h"
#include "Crc.h"

/*
 *********************************************************************
 * Global Variables
 *********************************************************************
 */
#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
static boolean isSecondDataWriteOngoing_b = FALSE;
static boolean isSecondCopyErase_b = FALSE;
static boolean isDoubleSecurityInOldLayout_b = FALSE;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
uint16 Ea_Rb_SurvBlksIndex_u16 = 0;
uint16 Ea_Rb_SurvBlksIndexBackUp_u16 = 0;
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
static Ea_Rb_BlockHeader_tst Ea_Rb_SurvBlockHeader_st;
static Ea_Rb_BlockHeader_tst Ea_Rb_SurvBlockHeaderCopy_st;
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"


#define EA_START_SEC_CODE
#include "Ea_MemMap.h"

/* Definitions of all static functions */
static Ea_Rb_stReturn_ten Ea_Rb_MigNewSurvBlksHandling(void);
static Ea_Rb_stReturn_ten Ea_Rb_MigNonSurv_ToSurvBlksHandling(void);
static Ea_Rb_stReturn_ten Ea_Rb_MigSingle_ToDoubleSurvBlksHandling(void);
static Ea_Rb_stReturn_ten Ea_Rb_MigDouble_ToSingleSurvBlksHandling(void);
static void Ea_Rb_MigCheckStatus_SurvBlkHandling(Ea_Rb_stReturn_ten stSurvBlkHandlingLoc_en);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadData(void);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadHeader(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadHeaderCopy(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteData(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteHeader(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteHeaderCopy(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_Erase(uint16 blkIndex_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHeaderHandling(uint16 blockNum_u16);
static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkDataHandling(uint16 blockNum_u16);
static void Ea_Rb_MigSurvBlkHandling_ResetInternalVariables(void);

/* Start of the Function area */


/**
 *********************************************************************
 * Ea_Rb_MigSurvBlkHandlingInit(): Search for Survival Blocks to be handled
 *
 * This function checks the Eep cache built during Init phase and looks
 * for new Survival Blocks that have been added or any existing Survival
 * blocks whose properties(Security level,Survival attribute) have been
 * modified.
 *
 * \param 	 none
 * \return   none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */

void Ea_Rb_MigSurvBlkHandlingInit(void)
{
    uint16 tmpCnt3_u16 = 0;

    /* Set to init State for next operation */
    Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_INIT_E;

    for(tmpCnt3_u16 = 0; tmpCnt3_u16 < EA_NUM_BLOCKS; tmpCnt3_u16++)
    {
        /* Check for Newly configured Survival Blocks */
        if((Ea_BlockProperties_onEep[tmpCnt3_u16].NvMIdx == 0)&&((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0))
        {
            /* A new Survival Block Found. Load it to the array */
            Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16]=tmpCnt3_u16;
            /* Update the reason why it was loaded to the array */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16]=EA_RB_FLAG_NEW_SURVBLK_E;
            /* Increment the Survival Blocks Handling Counter */
            Ea_Rb_SurvBlksIndex_u16 = Ea_Rb_SurvBlksIndex_u16+1;
        }
        /* Check for a block changed from Non-Survival to Survival */
        else if(((Ea_BlockProperties_onEep[tmpCnt3_u16].NvMIdx == Ea_BlockProperties[tmpCnt3_u16].NvMIdx)
                 &&((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)
                 &&((Ea_BlockProperties_onEep[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) == 0)))
        {
            /* A new Survival Block Found. Load it to the array */
            Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16]=tmpCnt3_u16;
            /* Update the reason why it was loaded to the array */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16]=EA_RB_FLAG_TO_SURVIVAL_E;
            /* Increment the Survival Blocks Handling Counter */
            Ea_Rb_SurvBlksIndex_u16 = Ea_Rb_SurvBlksIndex_u16+1;
        }
        /* Check for a Survival block changed from Single to Double Security*/
        else if(((Ea_BlockProperties_onEep[tmpCnt3_u16].NvMIdx == Ea_BlockProperties[tmpCnt3_u16].NvMIdx)&&(((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0) && ((Ea_BlockProperties_onEep[tmpCnt3_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) == 0)))
                    &&(((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)&&(((Ea_BlockProperties_onEep[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0))))
        {
            /* A new Survival Block Found. Load it to the array */
            Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16]=tmpCnt3_u16;
            /* Update the reason why it was loaded to the array */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16]=EA_RB_FLAG_SL1_TO_SL2_E;
            /* Increment the Survival Blocks Handling Counter */
            Ea_Rb_SurvBlksIndex_u16 = Ea_Rb_SurvBlksIndex_u16+1;
        }
        /* Check for a Survival Block changed from Double Security to Single Security */
        else if(((Ea_BlockProperties_onEep[tmpCnt3_u16].NvMIdx == Ea_BlockProperties[tmpCnt3_u16].NvMIdx)&&(((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) == 0) && ((Ea_BlockProperties_onEep[tmpCnt3_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)))
                    &&(((Ea_BlockProperties[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0)&&(((Ea_BlockProperties_onEep[tmpCnt3_u16].Flags & (uint8)EA_SURVIVAL_FLAG) > 0))))
        {
            /* A new Survival Block Found. Load it to the array */
            Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16]=tmpCnt3_u16;
            /* Update the reason why it was loaded to the array */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16]=EA_RB_FLAG_SL2_TO_SL1_E;
            /* Increment the Survival Blocks Handling Counter */
            Ea_Rb_SurvBlksIndex_u16 = Ea_Rb_SurvBlksIndex_u16+1;
        }
        else
        {
            /* Added for MISRA */
        }
    }
    if(Ea_Rb_SurvBlksIndex_u16 == 0)
    {
        /* Since No Survival Block needs to be handled/ All Survival Blocks already handled start the Migration process */
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
        /* Set the variable which denotes whether Survival Block handling is over as TRUE to start allowing Write/Invalidate requests for new blocks to be processed */
        Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingOver_b = TRUE;
    }
    else
    {
        /* Set Initial value to false to start Handling of Survival Blocks */
        Ea_Rb_SurvBlksHandling_st.isNextSurvBlkHandlingPossible_b = FALSE;
		/* Reset the migration initialization flag */
		Ea_Rb_MigInit_b = FALSE;
        /* Update the variable to be used as backup */
        Ea_Rb_SurvBlksIndexBackUp_u16 = Ea_Rb_SurvBlksIndex_u16;
		/* Set the state to handle the Survival Blocks as no Non-Survival Blocks need to be deleted */
		Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_SURVBLK_HANDLING_E;
	}
}

/**
 *********************************************************************
 * Ea_Rb_MigSurvBlkHandling(): Handles the new/modified SUrvival Blocks
 *
 * This function handles the new/modified Survival blocks identified
 * in the Ea_Rb_MigSurvBlkHandlingInit Function. After the handling them
 * it allows migration operation to start and write/invalidate
 * requests which results in occupancy of clipboard to be processed.
 *
 * \param 	 none
 * \return   none
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */

void Ea_Rb_MigSurvBlkHandling(void)
{
    Ea_Rb_stReturn_ten stSurvBlkHandling_en;

    if(Ea_Rb_SurvBlksHandling_st.isNextSurvBlkHandlingPossible_b == TRUE)
    {
        Ea_Rb_SurvBlksIndex_u16 = Ea_Rb_SurvBlksIndex_u16-1;
        if(Ea_Rb_SurvBlksIndex_u16 == 0)
        {
            /* Set the variable which denotes whether Survival Block handling is over as TRUE to start allowing Write/Invalidate requests for new blocks to be processed */
            Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingOver_b = TRUE;
            /* All Blocks are handled Start Migration operation */
            Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_RUNNING_E;
        }
        else
        {
            /* Next Survival Block Should be handled. */
            Ea_Rb_SurvBlksHandling_st.isNextSurvBlkHandlingPossible_b = FALSE;
		}
    }
    else
    {
        /* Update the Persistent Id of the next block that is being handled */
        Ea_Rb_SurvBlkHandled_u16 = Ea_BlockProperties[Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1]].NvMIdx;

        /* A New Survival Block should be handled */
        if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_NEW_SURVBLK_E)
        {
            /* Call the Function which does the handling of new Survival Blocks */
            stSurvBlkHandling_en = Ea_Rb_MigNewSurvBlksHandling();
            /* Check the return value of the Function */
            Ea_Rb_MigCheckStatus_SurvBlkHandling(stSurvBlkHandling_en);
        }
        /* A Non-Survival to Survival Block should be handled */
        else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_TO_SURVIVAL_E)
        {
            /* Call the Function which does the handling of Non-Survival to Survival Blocks */
            stSurvBlkHandling_en = Ea_Rb_MigNonSurv_ToSurvBlksHandling();
            /* Check the return value of the Function */
            Ea_Rb_MigCheckStatus_SurvBlkHandling(stSurvBlkHandling_en);
        }
        /* A Single Security Survival Block to Double Security Survival Block should be handled */
        else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL1_TO_SL2_E)
        {
            /* Call the Function which does the handling of Single Security Survival Block to Double Security Survival Block */
            stSurvBlkHandling_en = Ea_Rb_MigSingle_ToDoubleSurvBlksHandling();
            /* Check the return value of the Function */
            Ea_Rb_MigCheckStatus_SurvBlkHandling(stSurvBlkHandling_en);
        }
        /* A Double Security Survival Block to Single Security Survival Block should be handled */
        else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL2_TO_SL1_E)
        {
            /* Call the Function which does the handling of Double Security Survival Block to Single Security Survival Block */
            stSurvBlkHandling_en = Ea_Rb_MigDouble_ToSingleSurvBlksHandling();
            /* Check the return value of the Function */
            Ea_Rb_MigCheckStatus_SurvBlkHandling(stSurvBlkHandling_en);
        }
        else
        {
            /* Such state is not proccessed or allowed so go to the next block */
            Ea_Rb_SurvBlksHandling_st.isNextSurvBlkHandlingPossible_b = TRUE;
        }
    }
}

/**
 ******************************************************************************
 * Ea_Rb_MigCheckStatus_SurvBlkHandling(): check status of Survival block Handling
 *
 * This function checks the status of the every Survival Block handling
 * functions called for different scenarios of Survival Block handling(SL1->SL2,
 * SL2->SL1, NonSurvival->Survival, New Survival Block Addition)
 *
 * \param 	 return status of any of the Survival Block handling functions.
 * \return   None
 * \retval   None
 * \seealso
 * \usedresources
 ******************************************************************************
 */

static void Ea_Rb_MigCheckStatus_SurvBlkHandling(Ea_Rb_stReturn_ten stSurvBlkHandlingLoc_en)
{
    uint16 blkNum_u16;
    /* Load the Ea Block number to be handled to the local variable */
    blkNum_u16 = Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1];
    /* If the status is EA_RB_ST_OK_E then the handling is complete */
    if(stSurvBlkHandlingLoc_en == EA_RB_ST_OK_E)
    {
        /* Update the Permanent start Address for the following conditions: 1. New Survival Block  2. SL1->SL2 for a Survival Block  3. Non-Survival to Survival */
        if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_NEW_SURVBLK_E)
           ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL1_TO_SL2_E)
           ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_TO_SURVIVAL_E))
        {
            /* Update Permanent Area start address to start address of the last written block */
            Ea_Rb_MigHeader_st.MigPerStartAddr_u32 = Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr;
        }
        /* Set to init State for next operation */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_INIT_E;
        /* One Block Handling is complete Go to the next block */
        Ea_Rb_SurvBlksHandling_st.isNextSurvBlkHandlingPossible_b = TRUE;
    }
    else if(stSurvBlkHandlingLoc_en == EA_RB_ST_PENDING_E)
    {
        /* Block Handling is still ongoing please wait */
    }
    else
    {
        /* Some error, so call Error status in Migration as no new status for Survival Block Handling is present */
        Ea_Rb_MigOrder_st.MigOrderType_en = EA_RB_MIG_SURVBLK_HANDLING_ERROR_E;
        /* Set an Error Status to indicate error while handling of Survival Blocks */
        Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingError_b = TRUE;
    }
}

/**
 *******************************************************************************
 * Ea_Rb_MigNewSurvBlksHandling(): Handles Newly added Survival Blocks
 *
 * This function writes the header for the new survival block and
 * also the copy of the header if the block is of double security.
 * It also updates the Eep Cache for that block.
 *
 * \param 	 None
 * \return   Processing status of New Survival Block Handling
 * \retval   EA_RB_ST_OK_E: Handling of New Survival Block was successful
 * \retval   EA_RB_ST_ERROR_E: Handling of New Survival Block was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigNewSurvBlksHandling(void)
{
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    uint16 blkNum_u16;

    /* Load the Ea Block number to be handled to the local variable */
    blkNum_u16 = Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1];

    /* Init State called only once per operation */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_INIT_E)
    {
        /* Set the state that starts the operation */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_E;
    }

    /* Since no data for new blocks only header information will be written */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_E)
    {
        /* Load the Eep Cache based on the config File */
        Ea_BlockProperties_onEep[blkNum_u16].NvMIdx = Ea_BlockProperties[blkNum_u16].NvMIdx;
        Ea_BlockProperties_onEep[blkNum_u16].Flags = Ea_BlockProperties[blkNum_u16].Flags;
        Ea_BlockProperties_onEep[blkNum_u16].BlkRealLen = Ea_BlockProperties[blkNum_u16].BlkRealLen;
        Ea_BlockProperties_onEep[blkNum_u16].Length = Ea_BlockProperties[blkNum_u16].Length;


        /* Update the Eep Cache's start address of the block using Permanent Area start address */
        Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr = Ea_Rb_MigHeader_st.MigPerStartAddr_u32 - Ea_BlockProperties_onEep[blkNum_u16].BlkRealLen;
        /* Update the Eep Cache after handling of Block */
        Ea_BlockProperties_onEep[blkNum_u16].BlkEndAddr   = (Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr + Ea_BlockProperties[blkNum_u16].BlkRealLen) - 1uL;

        /* Update Header Information */
        /* Update Block Pattern */
        Ea_Rb_SurvBlockHeader_st.BlockPattern_u8[0] = EA_BLK_HEADER_PREAMBEL_BYTE_0;
        Ea_Rb_SurvBlockHeader_st.BlockPattern_u8[1] = EA_BLK_HEADER_PREAMBEL_BYTE_1;
        Ea_Rb_SurvBlockHeader_st.BlockPattern_u8[2] = EA_BLK_HEADER_PREAMBEL_BYTE_2;

        /* Update Block Flag */
        Ea_Rb_SurvBlockHeader_st.BlockFlags_u8 = Ea_BlockProperties_onEep[blkNum_u16].Flags;

        /* Update Block ID */
        Ea_Rb_SurvBlockHeader_st.BlockID_u16 = Ea_BlockProperties_onEep[blkNum_u16].NvMIdx;

        /* Update Block Length */
        Ea_Rb_SurvBlockHeader_st.BlockLen_u16 = Ea_BlockProperties_onEep[blkNum_u16].Length;

        /* Update Block Version as 0 as no data is written */
        Ea_Rb_SurvBlockHeader_st.BlockVersion_u16 = 0;

        /* Update Block Data CRC as 0 as no data is written */
        Ea_Rb_SurvBlockHeader_st.BlockData_CS_u32 = 0;

        /* Calculate the BlockHeader CRC */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        Ea_Rb_SurvBlockHeader_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8*)&Ea_Rb_SurvBlockHeader_st, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);

        /* Give write request to the Driver(Eep) Layer */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
        stRet_u8 = EA_EEP_WRITE(Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr, (const uint8 *)&Ea_Rb_SurvBlockHeader_st, EA_BLK_HEADER_SIZE);

        /* Check the return status */
        if(stRet_u8 == E_OK)
        {
            /* Check if Survival Block is of Double security */
            if((Ea_BlockProperties_onEep[blkNum_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
            {
                /* The Survival Block is of Double security Write Header copy */
                Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_COPY_E;
            }
            else
            {
                /* Survival Block is Single security, so handling is complete process to next block */
                stRetSub_en = EA_RB_ST_OK_E;
            }
        }
        else
        {
            /* Request Not Accepted, so throw error */
            stRetSub_en = EA_RB_ST_ERROR_E;
        }
    }
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_COPY_E)
    {
        /* Give write request to the Driver(Eep) Layer */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
        stRet_u8 = EA_EEP_WRITE(((Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr)+((Ea_BlockProperties_onEep[blkNum_u16].BlkRealLen)/2u)), (const uint8 *)&Ea_Rb_SurvBlockHeader_st, EA_BLK_HEADER_SIZE);

        /* Check the return status */
        if(stRet_u8 == E_OK)
        {
            /* Survival Block handling is complete process to next block */
            stRetSub_en = EA_RB_ST_OK_E;
        }
        else
        {
            /* Request Not Accepted, so throw error */
            stRetSub_en = EA_RB_ST_ERROR_E;
        }
    }
    else
    {
        /* Such a state should not be handled by this Function */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 *******************************************************************************
 * Ea_Rb_MigNonSurv_ToSurvBlksHandling(): Handles Blocks changed from NonSurvival
 * 									   to Survival
 *
 * This function reads the header(s) of the existing block(Non-Survival) and
 * reads the data corresponding to the most recent and valid header and writes
 * it in the Permanent Area and also erases the header of the Non-Survival copy.
 *
 * \param 	 None
 * \return   Processing status of Non Survival -> Survival Block Handling
 * \retval   EA_RB_ST_OK_E:    Handling of Non Survival -> Survival Block was
 * 							   successful
 * \retval   EA_RB_ST_ERROR_E: Handling of Non Survival -> Survival Block
 * 							   was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigNonSurv_ToSurvBlksHandling(void)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    uint16 blkNum_u16;

    /* Load the Ea Block number to be handled to the local variable */
    blkNum_u16 = Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1];

    /* Init State called only once per operation */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_INIT_E)
    {
        /* Load Eep Cache properties to the Local structure */
        Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr;
        Ea_Rb_SurvBlksHandling_st.BlkLength_u16 = Ea_BlockProperties_onEep[blkNum_u16].Length;
        Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 = Ea_Rb_MigHeader_st.MigPerStartAddr_u32 - Ea_BlockProperties[blkNum_u16].BlkRealLen;
        /* Set the state that starts the operation */
        /* Always read the original copy First */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_HEADER_E;
    }
    /* Reading of original Header, Reading of Header copy, Writing of original Header, Writing of Header copy */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_COPY_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_COPY_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHeaderHandling(blkNum_u16);
    }

    /* Reading First Copy of Data, Reading Second Copy of Data, Writing First copy of Data, Writing Second copy of Data */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_DATA_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_DATA_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkDataHandling(blkNum_u16);
    }

    /* Erasing of Second copy if SL2->SL1/ Erasing of Non-Survival copy if change from Non-Survival to Survival */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_ERASE_COPY_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_Erase(blkNum_u16);
    }

    else
    {
        /* Such a Case not possible. So throw Error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ***************************************************************************************

 * 									   		Single Security(SL1) to Double Security(SL2)
 *
 * This function reads the header of the existing block(SL1) and
 * reads the data corresponding to the header and writes it in the
 * Permanent Area and also erases the header of the SL1 copy.
 *
 * \param 	 None
 * \return   Processing status of SL1 -> SL2 Survival Block Handling
 * \retval   EA_RB_ST_OK_E:    Handling of SL1 -> SL2 Survival Block was
 * 							   successful
 * \retval   EA_RB_ST_ERROR_E: Handling of SL1 -> SL2 Survival Block
 * 							   was unsuccessful
 * \seealso
 * \usedresources
 ****************************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSingle_ToDoubleSurvBlksHandling(void)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    uint16 blkNum_u16;

    /* Load the Ea Block number to be handled to the local variable */
    blkNum_u16 = Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1];

    /* Init State called only once per operation */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_INIT_E)
    {
        /* Load Eep Cache properties to the Local structure */
        Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr;
        Ea_Rb_SurvBlksHandling_st.BlkLength_u16 = Ea_BlockProperties_onEep[blkNum_u16].Length;
        Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 = Ea_Rb_MigHeader_st.MigPerStartAddr_u32 - Ea_BlockProperties[blkNum_u16].BlkRealLen;
        /* Set the state that starts the operation */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_HEADER_E;
    }

    /* Reading of original Header, Reading of Header copy, Writing of original Header, Writing of Header copy */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_COPY_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_COPY_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHeaderHandling(blkNum_u16);
    }

    /* Reading First Copy of Data, Reading Second Copy of Data, Writing First copy of Data, Writing Second copy of Data */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_DATA_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_DATA_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkDataHandling(blkNum_u16);
    }

    /* Erasing of Second copy if SL2->SL1/ Erasing of Non-Survival copy if change from Non-Survival to Survival */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_ERASE_COPY_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_Erase(blkNum_u16);
    }

    else
    {
        /* Such a Case not possible. So throw Error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ***************************************************************************************
 * Ea_Rb_MigDouble_ToSingleSurvBlksHandling(): Handles Survival Blocks changed from
 * 									   		Double Security(SL2) to Single Security(SL1)
 *
 * This function reads the headers of the existing block(SL2) and
 * reads the data corresponding to the last written valid header
 * and writes it in the Permanent Area and also erases both the headers
 * of the SL2 copy.
 *
 * \param 	 None
 * \return   Processing status of SL2 -> SL1 Survival Block Handling
 * \retval   EA_RB_ST_OK_E:    Handling of SL2 -> SL1 Survival Block was
 * 							   successful
 * \retval   EA_RB_ST_ERROR_E: Handling of SL2 -> SL1 Survival Block
 * 							   was unsuccessful
 * \seealso
 * \usedresources
 ****************************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigDouble_ToSingleSurvBlksHandling(void)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    uint16 blkNum_u16;

    /* Load the Ea Block number to be handled to the local variable */
    blkNum_u16 = Ea_Rb_SurvBlksHandling_st.SurvBlksToBeHandled[Ea_Rb_SurvBlksIndex_u16-1];

    /* Init State called only once per operation */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_INIT_E)
    {
        /* Load Eep Cache properties to the Local structure */
        Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr;
        Ea_Rb_SurvBlksHandling_st.BlkLength_u16 = Ea_BlockProperties_onEep[blkNum_u16].Length;
        Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 = Ea_BlockProperties_onEep[blkNum_u16].BlkStartAddr;
        /* Set the state that starts the operation */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_HEADER_E;
    }

    /* Reading of original Header, Reading of Header copy, Writing of original Header, Writing of Header copy */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_COPY_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_COPY_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHeaderHandling(blkNum_u16);
    }

    /* Reading First Copy of Data, Reading Second Copy of Data, Writing First copy of Data, Writing Second copy of Data */
    else if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_DATA_E)
            ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_DATA_E))
    {
        stRetSub_en = Ea_Rb_MigSurvBlkDataHandling(blkNum_u16);
    }

    /* Erasing of Second copy if SL2->SL1/ Erasing of Non-Survival copy if change from Non-Survival to Survival */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_ERASE_COPY_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_Erase(blkNum_u16);
    }

    else
    {
        /* Such a Case not possible. So throw Error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}


/* Start of the Functions depicting the State Machines */

/**
 *******************************************************************************
 * Ea_Rb_MigSurvBlkHandling_ReadHeader(): Reads header of existing Survival Block
 *
 * This function reads the header of an existing Survival Block which is
 * currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadHeader(uint16 blkIndex_u16)
{
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;

    /* Give read request to the Driver(Eep) Layer */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Read operation */
    stRet_u8 = EA_EEP_READ(Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32, (uint8 *)&Ea_Rb_SurvBlockHeader_st, EA_BLK_HEADER_SIZE);

    if((stRet_u8 == E_OK)&&((Ea_BlockProperties_onEep[blkIndex_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0))
    {
        /* Set the variable to denote two copies in old configuration */
		isDoubleSecurityInOldLayout_b = TRUE;
		/* Go to the analysis state as there are two copies */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_HEADER_COPY_E;
    }
    else if((stRet_u8 == E_OK)&&((Ea_BlockProperties_onEep[blkIndex_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) == 0))
    {
        /* Header read.. update ReadStartAddress to read Data */
        Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 += EA_BLK_HEADER_SIZE;
		/* Also Update the write start address as write starts immediately after read. No time then to change */
		Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 += EA_BLK_HEADER_SIZE;
        /* This block has only one header so go to data part. No analysis required */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_DATA_E;
    }
    else
    {
        /* Request Not Accepted, so throw error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 *******************************************************************************
 * Ea_Rb_MigSurvBlkHandling_ReadHeaderCopy(): Reads second copy of header of
 * 										   existing Survival Block
 *
 * This function reads the second copy of the header of an existing Survival
 * block which is currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadHeaderCopy(uint16 blkIndex_u16)
{
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;

    /* Give read request to the Driver(Eep) Layer */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Read operation */
    stRet_u8 = EA_EEP_READ(((Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32)+((Ea_BlockProperties_onEep[blkIndex_u16].BlkRealLen)/2u)), (uint8 *)&Ea_Rb_SurvBlockHeaderCopy_st, EA_BLK_HEADER_SIZE);
    if(stRet_u8 == E_OK)
    {
        if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL2_TO_SL1_E)
        {
            /* Block in New layout is of Single security. So proceed to Header writing state */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_E;
        }
        else
        {
            /* Header read.. update ReadStartAddress to read Data */
            Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 += EA_BLK_HEADER_SIZE;
            /* Also Update the write start address as write starts immediately after read. No time then to change */
            Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 += EA_BLK_HEADER_SIZE;
            /* This block has only one header so go to data part. No analysis required */
            Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_DATA_E;
        }
    }
    else
    {
        /* Request Not Accepted, so throw error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}


/**
 *******************************************************************************
 * Ea_Rb_MigSurvBlkHandling_ReadData(): Reads Data of existing Survival Block
 *
 * This function reads the data of an existing Survival Block which is
 * currently being handled.
 *
 * \param 	 None
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_ReadData(void)
{
    Std_ReturnType stRet_u8 = E_OK;
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;


    /* Read the Data and Write the Data Page wise */
    if(Ea_Rb_SurvBlksHandling_st.BlkLength_u16 >= (uint16)EA_RB_MIG_BUFFER_SIZE)
    {
        Ea_Rb_SurvBlksHandling_st.TransmitLen_u16 = (uint16)EA_RB_MIG_BUFFER_SIZE;
    }
    else
    {
        Ea_Rb_SurvBlksHandling_st.TransmitLen_u16 = Ea_Rb_SurvBlksHandling_st.BlkLength_u16;
    }

    /* Give Read request to read data of size less than or equal to the Buffer size */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Read operation */
    stRet_u8 = EA_EEP_READ(Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32, (uint8 *)&Ea_Rb_dMigDataBuf_u8, Ea_Rb_SurvBlksHandling_st.TransmitLen_u16);

    if(stRet_u8 == E_OK)
    {
        /* Request accepted.*/
        /* change to write state so that the data read will be written */
        Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_DATA_E;
    }
    else
    {
        /* Request Not Accepted, so throw error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}



/**
 *******************************************************************************
 * Ea_Rb_MigSurvBlkHandling_WriteData(): Writes Data to a changed Survival Block
 *
 * This function writes the data to a changed Survival Block which is
 * currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 *******************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteData(uint16 blkIndex_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    Std_ReturnType stRet_u8 = E_OK;
	Eep_LengthType tmpBlklengthAligned_uo;

    /* Give Write request to Write data read prior to this request */
    /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
    stRet_u8 = EA_EEP_WRITE(Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32, (const uint8 *)&Ea_Rb_dMigDataBuf_u8, Ea_Rb_SurvBlksHandling_st.TransmitLen_u16);

    if(stRet_u8 == E_OK)
    {
       /* Request accepted. */
       /* Update the Read and Write start address along with the length remaining to be transmitted */
	   
	   tmpBlklengthAligned_uo = Ea_Rb_CalcAlignedLen(Ea_Rb_SurvBlksHandling_st.TransmitLen_u16);
	   
       Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 += tmpBlklengthAligned_uo;
       Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 += tmpBlklengthAligned_uo;
       Ea_Rb_SurvBlksHandling_st.BlkLength_u16 -= Ea_Rb_SurvBlksHandling_st.TransmitLen_u16;

       /*Proceed to the next state based on the number bytes to be transmitted/ length remaining to be Written */
       if(Ea_Rb_SurvBlksHandling_st.BlkLength_u16 == 0)
       {
           if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL1_TO_SL2_E)
           {
               if(isSecondDataWriteOngoing_b == FALSE)
               {
                   /* Update the Read Start Address */
                   /* Set the read address to the start of first copy of data */
                   Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + EA_BLK_HEADER_SIZE;

                   /* Update Write Start Address */
                   Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 += EA_BLK_HEADER_SIZE;
                   /* Update the Block Length */
                   Ea_Rb_SurvBlksHandling_st.BlkLength_u16 = Ea_BlockProperties_onEep[blkIndex_u16].Length;
                   /* Update the variable which directs read data to original/copy */
                   isSecondDataWriteOngoing_b = TRUE;
                   /* Final Data should be of Double Security Go to the Data copy writing state */
                   Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_DATA_E;
               }
               else
               {
                   /* Reset the Variables */
                   isSecondDataWriteOngoing_b = FALSE;
                   /* Both Data Copies written now write the Header */
                   Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_E;
               }
           }
           else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_TO_SURVIVAL_E)
           {
               /* Check if the Block in new layout is single or double security */
               if(((Ea_BlockProperties[blkIndex_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)&&(isSecondDataWriteOngoing_b == FALSE))
               {
                   /* Update the Read Start Address */
                   if(isDoubleSecurityInOldLayout_b == TRUE)
                   {
                       /* Set the read address to the start of second copy of data */
                       Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = (Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + ((Ea_BlockProperties_onEep[blkIndex_u16].BlkRealLen)/2uL)) + EA_BLK_HEADER_SIZE;
				   }
                   else
                   {
                       /* Set the read address to the start of first copy of data */
                       Ea_Rb_SurvBlksHandling_st.ReadStartAdr_u32 = Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + EA_BLK_HEADER_SIZE;
                   }
                   /* Update Write Start Address */
                   Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 += EA_BLK_HEADER_SIZE;
                   /* Update the Block Length */
                   Ea_Rb_SurvBlksHandling_st.BlkLength_u16 = Ea_BlockProperties_onEep[blkIndex_u16].Length;
                   /* Update the variable which directs read data to original/copy */
                   isSecondDataWriteOngoing_b = TRUE;
                   /* Final Data should be of Double Security Go to the Data copy writing state */
                   Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_DATA_E;
               }
               else
               {
                  /* Reset the Variables */
                  isSecondDataWriteOngoing_b = FALSE;
                  /* Block is of Single security in the new layout. Proceed to Header writing state */
                  Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_E;
               }
           }
           else
           {
               /* Added for MISRA */
           }
       }
       else
       {
           /* Go to the Data reading state to read remaining data of the block */
           Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_READ_DATA_E;
       }
    }
    else
    {
       /* Request Not Accepted, so throw error */
       stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ********************************************************************************
 * Ea_Rb_MigSurvBlkHandling_WriteHeader(): Writes Header of a changed Survival Block
 *
 * This function writes the header of a changed Survival Block which is
 * currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 ********************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteHeader(uint16 blkIndex_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    Std_ReturnType stRet_u8 = E_OK;
    boolean writeSecondCopy_b = FALSE;

	if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] != EA_RB_FLAG_SL2_TO_SL1_E)
	{
        /* Update the Write start Address- Might have changed during handling */
        /* Update it to Permanent start Address minus the real length of the new block arrived at after Handling of the Block */
        Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32 = Ea_Rb_MigHeader_st.MigPerStartAddr_u32 - Ea_BlockProperties[blkIndex_u16].BlkRealLen;
	}

    /* Update the Structure from which header will be written */
	/* Update the flag of the Header */
	if(((Ea_BlockProperties[blkIndex_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG)) > 0)
	{
		/* Update the temporary variable */
		writeSecondCopy_b = TRUE;
		/* Block is double security so update the Flag */
		Ea_Rb_SurvBlockHeader_st.BlockFlags_u8 |= (uint8)EA_SECURITY_LEVEL_FLAG;
	}
	else
	{
		/* Block is single security so update the flag */
		Ea_Rb_SurvBlockHeader_st.BlockFlags_u8 &= ~((uint8)EA_SECURITY_LEVEL_FLAG);
	}


	/* Always update the Survival flag as this is Survival Block Handling */
	Ea_Rb_SurvBlockHeader_st.BlockFlags_u8 |= (uint8)EA_SURVIVAL_FLAG;
	/* Calculate and update the Header Crc since header properties are changed */
	/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
	Ea_Rb_SurvBlockHeader_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8 *)&Ea_Rb_SurvBlockHeader_st, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);

	/* Give Write request to Write Header read from original copy */
	/* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
	stRet_u8 = EA_EEP_WRITE(Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32, (const uint8 *)&Ea_Rb_SurvBlockHeader_st, EA_BLK_HEADER_SIZE);

	if(stRet_u8 == E_OK)
	{
		/* Write request Accepted */
		/* Check if Header copy required to be written */
		if(writeSecondCopy_b == TRUE)
		{
			/* Set the state to writing of Header copy */
			Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_WRITE_HEADER_COPY_E;
		}
		else
		{
			/* Reset all variable pertaining to writing of Survival Blocks */
			/* Set state to erase previous version of block present in another place */
			Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_ERASE_COPY_E;
		}
	}
	else
	{
		/* Request Not Accepted, so throw error */
		stRetSub_en = EA_RB_ST_ERROR_E;
	}


    return stRetSub_en;

}

/**
 ********************************************************************************
 * Ea_Rb_MigSurvBlkHandling_WriteHeaderCopy(): Writes Second copy of the Header of
 *											a changed Survival Block
 *
 * This function writes the Second copy of the Header of a changed Survival Block
 * which is currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 ********************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_WriteHeaderCopy(uint16 blkIndex_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    Std_ReturnType stRet_u8 = E_OK;

    if(isDoubleSecurityInOldLayout_b == TRUE)
    {
        /* Update the Structure from which header will be written */
        /* Update the flag of the Header */
        if(((Ea_BlockProperties[blkIndex_u16].Flags & (uint8)EA_SECURITY_LEVEL_FLAG)) > 0)
        {
            /* Block is double security so update the Flag */
            Ea_Rb_SurvBlockHeaderCopy_st.BlockFlags_u8 |= (uint8)EA_SECURITY_LEVEL_FLAG;
        }
        else
        {
            /* Block is single security so update the flag */
            Ea_Rb_SurvBlockHeaderCopy_st.BlockFlags_u8 &= ~((uint8)EA_SECURITY_LEVEL_FLAG);
        }

        /* Always update the Survival flag as this is Survival Block Handling */
        Ea_Rb_SurvBlockHeaderCopy_st.BlockFlags_u8 |= (uint8)EA_SURVIVAL_FLAG;
        /* Calculate and update the Header Crc since header properties are changed */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access */
        Ea_Rb_SurvBlockHeaderCopy_st.BlockHeader_CS_u16 = Crc_CalculateCRC16((uint8 *)&Ea_Rb_SurvBlockHeaderCopy_st, (EA_BLK_HEADER_SIZE-6u), EA_MARKER_PATTERN, FALSE);

        /* Give Write request to Write Header for second copy */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
        stRet_u8 = EA_EEP_WRITE(((Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32)+((Ea_BlockProperties[blkIndex_u16].BlkRealLen)/2u)), (const uint8 *)&Ea_Rb_SurvBlockHeaderCopy_st, EA_BLK_HEADER_SIZE);
    }
    else
    {
        /* Give Write request to Write Header for second copy */
        /* MR12 RULE 11.3 VIOLATION: Cast necessary for byte wise access as this is Write operation */
        stRet_u8 = EA_EEP_WRITE(((Ea_Rb_SurvBlksHandling_st.WriteStartAdr_u32)+((Ea_BlockProperties[blkIndex_u16].BlkRealLen)/2u)), (const uint8 *)&Ea_Rb_SurvBlockHeader_st, EA_BLK_HEADER_SIZE);
    }

	if(stRet_u8 == E_OK)
	{
		/* Write request Accepted */
		/* Reset all variable pertaining to writing of Survival Blocks */
		/* Set state to erase previous version of block present in another place */
		Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en = EA_RB_SURVBLK_ERASE_COPY_E;
	}
	else
    {
        /* Request Not Accepted, so throw error */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ********************************************************************************
 * Ea_Rb_MigSurvBlkHeaderHandling(): Function that routes Survival block handling
 *								  orders for header handling to the respective
 * 								  functions.
 *
 * This function takes care of Header handling part of Survival Block handling
 *
 * \param 	 blockNum_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 ********************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHeaderHandling(uint16 blockNum_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;

    /* Reading of original Header */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_ReadHeader(blockNum_u16);
    }

    /* Reading of Header copy */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_HEADER_COPY_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_ReadHeaderCopy(blockNum_u16);
    }

    /* Writing of original Header */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_WriteHeader(blockNum_u16);
    }

    /* Writing of Header copy */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_HEADER_COPY_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_WriteHeaderCopy(blockNum_u16);
    }

    /* This case not possible. If it occurs throw error */
    else
    {
        /* Throw Error as such a state should not come */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ********************************************************************************
 * Ea_Rb_MigSurvBlkDataHandling(): Function that routes Survival block handling
 *								orders for data handling to the respective
 * 								functions.
 *
 * This function takes care of Data handling part of Survival Block handling
 *
 * \param 	 blockNum_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 ********************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkDataHandling(uint16 blockNum_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;

    /* Reading Data of First Copy */
    if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_READ_DATA_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_ReadData();
    }

    /* Writing First copy of Data */
    else if(Ea_Rb_SurvBlksHandling_st.Ea_Rb_SurvBlkHandlingOrderType_en == EA_RB_SURVBLK_WRITE_DATA_E)
    {
        stRetSub_en = Ea_Rb_MigSurvBlkHandling_WriteData(blockNum_u16);
    }


    /* This case not possible. If it occurs throw error */
    else
    {
        /* Throw Error as such a state should not come */
        stRetSub_en = EA_RB_ST_ERROR_E;
    }

    return stRetSub_en;
}

/**
 ********************************************************************************
 * Ea_Rb_MigSurvBlkHandling_Erase(): Erases old copy of the Header of a changed
 *								  Survival Block
 *
 * This function Erases old copy of the Header of a changed Survival Block
 * which is currently being handled.
 *
 * \param 	 blkIndex_u16	Ea ID of Survival Block for which Handling is ongoing.
 * \return   Processing status of overall Survival Block Handling operation
 * \retval   EA_RB_ST_PENDING_E: Handling of the Survival Block is pending
 * \retval   EA_RB_ST_ERROR_E: Handling of the Survival Block was unsuccessful
 * \seealso
 * \usedresources
 ********************************************************************************
 */

static Ea_Rb_stReturn_ten Ea_Rb_MigSurvBlkHandling_Erase(uint16 blkIndex_u16)
{
    Ea_Rb_stReturn_ten stRetSub_en = EA_RB_ST_PENDING_E;
    Std_ReturnType stRet_u8 = E_OK;
    Eep_AddressType tmpEraseAddress_u32;
	Eep_LengthType tmpBlklengthAligned_uo;

    /* Check which Flag change has occured */
    if((Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_TO_SURVIVAL_E)
        ||(Ea_Rb_SurvBlksHandling_st.Ea_Rb_MigFlagChanges_aen[Ea_Rb_SurvBlksIndex_u16-1] == EA_RB_FLAG_SL1_TO_SL2_E))
    {
        /*Check if Double security --> Happens only for Non-Survival to Survival case */
		if((isDoubleSecurityInOldLayout_b == TRUE)&&(isSecondCopyErase_b == FALSE))
		{
			/* Update the Temporary erase address variable */
			tmpEraseAddress_u32 = Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr;
			/* Set a variable indicating another write is required. */
			isSecondCopyErase_b = TRUE;
			/* Give the Erase request */
			stRet_u8 = Eep_Erase(tmpEraseAddress_u32,EA_BLK_HEADER_SIZE);
		}
		else if((isDoubleSecurityInOldLayout_b == TRUE)&&(isSecondCopyErase_b == TRUE))
		{
			tmpBlklengthAligned_uo = Ea_Rb_CalcAlignedLen(Ea_BlockProperties_onEep[blkIndex_u16].Length);
			/* Update the temporary Address variable to erase second copy */
			tmpEraseAddress_u32 = (Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + (uint32)tmpBlklengthAligned_uo) + (uint32)EA_BLK_HEADER_SIZE;
			/* Reset the variable indicating another variable is required */
			isSecondCopyErase_b = FALSE;
			/* Give Erase Request */
			stRet_u8 = Eep_Erase(tmpEraseAddress_u32,EA_BLK_HEADER_SIZE);
		}
		else
		{
			/* Update the Temporary erase address variable */
			tmpEraseAddress_u32 = Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr;
			/* Give the Erase request */
			stRet_u8 = Eep_Erase(tmpEraseAddress_u32,EA_BLK_HEADER_SIZE);
		}

        if((stRet_u8 == E_OK)&&(isSecondCopyErase_b == FALSE))
        {
            /* Erase Request is accepted */
            /* Update the Eep cache */
			Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr = Ea_Rb_MigHeader_st.MigPerStartAddr_u32 - Ea_BlockProperties[blkIndex_u16].BlkRealLen;
			Ea_BlockProperties_onEep[blkIndex_u16].BlkEndAddr = (Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + Ea_BlockProperties[blkIndex_u16].BlkRealLen) - 1u;
			Ea_BlockProperties_onEep[blkIndex_u16].BlkRealLen = Ea_BlockProperties[blkIndex_u16].BlkRealLen;
			Ea_BlockProperties_onEep[blkIndex_u16].Flags = Ea_BlockProperties[blkIndex_u16].Flags;

			/* Reset Internal Variables */
			Ea_Rb_MigSurvBlkHandling_ResetInternalVariables();

            /* Set Return as Success as all operation related to handling of this survival block is completed */
			stRetSub_en = EA_RB_ST_OK_E;
        }
        else if(stRet_u8 != E_OK)
        {
            /* Request Not Accepted, so throw error */
            stRetSub_en = EA_RB_ST_ERROR_E;
        }
		else
		{
			/* Do not perform any operation.. Allow to continue */
		}
    }
    else
    {
		tmpBlklengthAligned_uo = Ea_Rb_CalcAlignedLen(Ea_BlockProperties_onEep[blkIndex_u16].Length);
        /* Update the Temporary erase address variable */
        tmpEraseAddress_u32 = (Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + (uint32)tmpBlklengthAligned_uo) + (uint32)EA_BLK_HEADER_SIZE;
        /* Give the Erase request */
        stRet_u8 = Eep_Erase(tmpEraseAddress_u32,EA_BLK_HEADER_SIZE);

        if(stRet_u8 == E_OK)
        {
            /* Erase Request is accepted */
            /* Update the Eep cache and Permanent Start Address */
            /* Since no change in Permanent Area start address - update the Flag and Blk End,Start Address variable of Eep Cache */
            Ea_BlockProperties_onEep[blkIndex_u16].Flags = Ea_BlockProperties[blkIndex_u16].Flags;
            /* No update of start address is required */
            Ea_BlockProperties_onEep[blkIndex_u16].BlkEndAddr = (Ea_BlockProperties_onEep[blkIndex_u16].BlkStartAddr + Ea_BlockProperties[blkIndex_u16].BlkRealLen) - 1u;
            Ea_BlockProperties_onEep[blkIndex_u16].BlkRealLen = Ea_BlockProperties[blkIndex_u16].BlkRealLen;

			/* Reset Internal Variables */
			Ea_Rb_MigSurvBlkHandling_ResetInternalVariables();

            /* Set Return as Success as all operation related to handling of this survival block is completed */
            stRetSub_en = EA_RB_ST_OK_E;

        }
        else
        {
            /* Request Not Accepted, so throw error */
            stRetSub_en = EA_RB_ST_ERROR_E;
        }
    }

    return stRetSub_en;
}

/**
 *********************************************************************
 * Ea_Rb_MigSurvBlkHandling_ResetInternalVariables(): Resets all Internal
 *  											   variables
 *
 * This function resets all internally declared variables so that next
 * Survival block can be processed
 *
 * \param   void
 * \return  void
 * \seealso
 * \usedresources
 *********************************************************************
 */

static void Ea_Rb_MigSurvBlkHandling_ResetInternalVariables(void)
{
	/* Reset all the variables used while Handling of one Survival Block */
	isSecondDataWriteOngoing_b = FALSE;
	isSecondCopyErase_b = FALSE;
	isDoubleSecurityInOldLayout_b = FALSE;
}



#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
#endif
/* #if(EA_NUM_SURVIVAL_BLOCKS > 0) */
#endif
/* #if (EA_PRESENT == 1) */
/*<BASDKey>
**********************************************************************************************************************
* $History___:
*
* AR40.7.11.0; 2     08.06.2017 SRG8COB
*   Update to set initial state at start
*
* AR40.7.11.0; 1     06.06.2017 SRG8COB
*   Review Corrections
*
* AR40.7.11.0; 0     02.06.2017 SRG8COB
*
*
* $
**********************************************************************************************************************
</BASDKey>*/

