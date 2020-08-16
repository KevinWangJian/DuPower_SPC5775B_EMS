

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
#if (EA_DEV_ERROR_DETECT != FALSE)
    #include "Det.h"
#endif
#include "Ea_Prv.h"

#define EA_START_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"
boolean Ea_Rb_isNewSurvBlkToBeWritten_b = FALSE;        /* TRUE: Write request for a new Survival block is given by user */
boolean Ea_Rb_SurvBlkHandlingAndWrConflict_b = FALSE;
#define EA_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Ea_MemMap.h"

#define EA_START_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
#if(EA_NUM_SURVIVAL_BLOCKS > 0)
uint16 Ea_Rb_NewSurvBlkIndex_u16;        /* Index of the new survival block for which write/invalidate request has been given */
#endif
uint16 Ea_Rb_SurvBlkHandled_u16;         /* Persistent Id of the block which is being handled */
uint16 Ea_Rb_SurvBlkHandlingAndWrConflictIndex_u16 = 0;
#define EA_STOP_SEC_VAR_CLEARED_16
#include "Ea_MemMap.h"
/**
 *********************************************************************
 * Ea_InvalidateBlock():
 *
 * Service name:        Ea_InvalidateBlock
 * This function invalidates one block
 * Service ID[hex]:     0x07
 * Sync/Async:          Asynchronous
 * Reentrancy:          Non Reentrant
 * Parameters (in):     BlockNumber:  block number
 * Parameters (inout):  None
 * Parameters (out):    None
 * Return value:        None
 * Description:         Service to call the Ea_InvalidateBlock function of the Eeprom driver.
 * ****************************************************************************************************************** */
#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
Std_ReturnType Ea_InvalidateBlock(uint16 BlockNumber)
{
    Std_ReturnType retVal = E_NOT_OK;
    uint16 tmpBlkNum_u16  = 0;
#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG == TRUE)
	uint32 tmpClipEndAdr_u32 = 0;
#endif

    /* Check the EA module status and the user's block number */

    /* [EA135]: If development error detection for the module Ea is enabled: the function Ea_InvalidateBlock
     * shall check that the module has been initialized. If this check fails, the function Ea_InvalidateBlock
     * shall raise the development error EA_E_NOT_INITIALIZED and return E_NOT_OK to the caller without performing
     * the requested function.
     *
     * [EA149]: If development error detection for the module EA is enabled: the function Ea_InvalidateBlock
     * shall check whether the given block number is valid (i.e. inside the configured range). If this check fails,
     * the function Ea_InvalidateBlock shall raise the development error EA_E_INVALID_BLOCK_NO and return E_NOT_OK
     * to the caller without performing the requested function. */

    /* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    if((Ea_Rb_CheckInit(EA_SID_INVALIDATEBLOCK) != E_OK) ||
       (Ea_Rb_CheckBlkNr(EA_SID_INVALIDATEBLOCK, BlockNumber) != E_OK)
#if((EA_NUM_SURVIVAL_BLOCKS > 0)&&(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE))
       ||(Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingError_b == TRUE)
#endif
       )
    {
        /* Return with an error */
        retVal = E_NOT_OK;
    }
    /* [EA161]:
     * If a block invalidation request is rejected by the function Ea_InvalidateBlock, i.e. requirements EA135
     * or EA149 apply, the function Ea_InvalidateBlock shall not change the current module status or job result. */
    else
    {
        /* Disable interrupts */
        SchM_Enter_Ea_Order();

        /* Check the queue availability immediately with interrupts being locked */
        if(Ea_Rb_Order_st.OrderType_en == EA_RB_NO_ORDER_E)
        {
            /* Set main status to busy independent from other users */
            Ea_GlobModuleState_st = MEMIF_BUSY;

            /* Set Ea job result */
            Ea_JobResult = MEMIF_JOB_PENDING;

            /* Set order type for the further progress in main function */
            Ea_Rb_Order_st.OrderType_en     = EA_RB_WRITE_ORDER_E;

            /* Set order type for the further progress in main function */
            /* Invalidate: only write the change header, no need to write any data. */
            /* So here just start a normal write order with Ea_Rb_Order_st.numBytes_u16 = 0 */
            Ea_Rb_Order_st.RequestOrder_en = EA_RB_WRITE_E;

            /* Default return value if write order is set */
            retVal = E_OK;
        }

        /* Enable interrupts */
        SchM_Exit_Ea_Order();

        /* If this order has been accepted, parameter assignment */
        if((Ea_Rb_Order_st.OrderType_en == EA_RB_WRITE_ORDER_E) && (retVal == E_OK))
        {
            /* Save user parameters and reset necessary order structure elements */

            Ea_Rb_Order_st.numBytes_u16         = 0;
            Ea_Rb_Order_st.Buffer_un.Write_pcu8 = NULL_PTR;
            Ea_Rb_Order_st.isDataNotEqual_b     = TRUE;
            Ea_Rb_Order_st.numID_u16            = Ea_BlockProperties[BlockNumber].NvMIdx;

            /* Set security level bit from block flag settings */
            if((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0u)
            {
                Ea_Rb_Order_st.isSecLevelCurr_b = TRUE;
            }
            else
            {
                Ea_Rb_Order_st.isSecLevelCurr_b = FALSE;
            }

            Ea_Rb_Order_st.BlockLenAligned_uo = Ea_Rb_CalcAlignedLen(Ea_BlockProperties[BlockNumber].Length) + EA_BLK_HEADER_SIZE;

            if(Ea_Rb_MigRunning_b)
            {
                /* During migration running, get the address from the on EEPROM properties
                 * and no difference between survival blocks and non-survival blocks */
                Ea_Rb_Order_st.isSurvivalBlk_b  = FALSE;

                /* Check if this block exists in old layout */
                if((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr != 0u)
                        && (Ea_BlockProperties_onEep[BlockNumber].NvMIdx == Ea_BlockProperties[BlockNumber].NvMIdx))
                {
                    /* This block exists in old layout: overwrite the data if any differences */
                    Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr;

                    /* Check SL2 blocks, if there are really two copies available in old layout */
                    if(Ea_Rb_Order_st.isSecLevelCurr_b)
                    {
                        if(Ea_BlockProperties_onEep[BlockNumber].BlkRealLen == Ea_Rb_Order_st.BlockLenAligned_uo)
                        {
                            /* Only one copy available, write only once
                             * (in case security level changes between old and new layouts) */
                            Ea_Rb_Order_st.isSecLevelCurr_b = FALSE;
                        }
                    }

                    /* Check if this block is currently handled by Survival block handling operation */
                    if(Ea_Rb_Order_st.numID_u16 == Ea_Rb_SurvBlkHandled_u16)
                    {
                        Ea_Rb_SurvBlkHandlingAndWrConflict_b = TRUE;
                    }
					
					if(Ea_Rb_SurvBlkHandlingAndWrConflict_b == TRUE)
					{
						/* Load the Ea Block Number value */
						Ea_Rb_SurvBlkHandlingAndWrConflictIndex_u16 = BlockNumber;

						/* Set order type for the further progress in main function */
						Ea_Rb_Order_st.OrderType_en     = EA_RB_WRITE_ORDER_WAIT_E;
					}
                }
                else
                {
                    /* This block doesn't exist in old layout:
                     * Check the target address area for this block is free? */
                    tmpBlkNum_u16 = Ea_Rb_MigCheckFreeAdr(BlockNumber+1);

                    if((tmpBlkNum_u16 > 0) || (Ea_BlockProperties[BlockNumber].BlkStartAddr == 0u))
                    {
						if((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SURVIVAL_FLAG) > 0u)
						{
							/* Disable interrupts */
							SchM_Enter_Ea_Order();
				#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
                            /* Set the flag to denote that a new survival block is to be written */
                            Ea_Rb_isNewSurvBlkToBeWritten_b = TRUE;
				#else
                            /* Calculate the new valid permanent area start address */
                            Ea_Rb_MigHeader_st.MigPerStartAddr_u32 -= Ea_BlockProperties[BlockNumber].BlkRealLen;

                            /* Write this block in permanent area directly */
							Ea_Rb_Order_st.adStart_uo   = Ea_Rb_MigHeader_st.MigPerStartAddr_u32;

				#endif
							/* Enable interrupts */
							SchM_Exit_Ea_Order();

						}
						else
						{
							/* Target address used by another block */
							#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
								if(Ea_Rb_MigClipAddrCheckSpace(Ea_Rb_MigCurNr_u16, (uint16)Ea_BlockProperties[BlockNumber].BlkRealLen) == TRUE)
								{
									/* Disable interrupts */
									SchM_Enter_Ea_Order();

									/* Update Start Address of the Write Operation */
									Ea_Rb_Order_st.adStart_uo   = Ea_Rb_MigClipSrtAdr_u32;

									/* Update the clip board start address */
									Ea_Rb_MigClipSrtAdr_u32     += Ea_BlockProperties[BlockNumber].BlkRealLen;

									/* Enable interrupts */
									SchM_Exit_Ea_Order();
								}
								else
								{
									/* Disable interrupts */
									SchM_Enter_Ea_Order();

                            /* Permanent area reached: no place to be written */
                            /* Return value if write order is set */
                            retVal = E_NOT_OK;

                            /* Reset order */
                            /* Set main status to busy independent from other users */
                            Ea_GlobModuleState_st = MEMIF_IDLE;

                            /* Set Ea job result */
                            Ea_JobResult = MEMIF_JOB_OK;

                            Ea_Rb_Order_st.RequestOrder_en  = EA_RB_NO_REQUEST_E;

                            /* Set order type for the further progress in main function */
                            Ea_Rb_Order_st.OrderType_en     = EA_RB_NO_ORDER_E;

									/* Enable interrupts */
									SchM_Exit_Ea_Order();
								}
							#else
								/* Calculate the possible clip board end address */
								tmpClipEndAdr_u32 = Ea_Rb_MigClipSrtAdr_u32 + Ea_BlockProperties[BlockNumber].BlkRealLen;

								/* Check if enough place in clip board to be written*/
								if(tmpClipEndAdr_u32 >= Ea_Rb_MigHeader_st.MigPerStartAddr_u32)
								{
									/* Permanent area reached: no place to be written */
									/* Disable interrupts */
									SchM_Enter_Ea_Order();

									/* Permanent area reached: no place to be written */
									/* Return value if write order is set */
									retVal = E_NOT_OK;

									/* Reset order */
									/* Set main status to busy independent from other users */
									Ea_GlobModuleState_st = MEMIF_IDLE;

									/* Set Ea job result */
									Ea_JobResult = MEMIF_JOB_OK;

									Ea_Rb_Order_st.RequestOrder_en  = EA_RB_NO_REQUEST_E;

									/* Set order type for the further progress in main function */
									Ea_Rb_Order_st.OrderType_en     = EA_RB_NO_ORDER_E;

									/* Enable interrupts */
									SchM_Exit_Ea_Order();
								}
								else
								{
									/* No free place: write the data temporary at beginning of clip board */
									Ea_Rb_Order_st.adStart_uo   = Ea_Rb_MigClipSrtAdr_u32;

									/* Update the clip board start address */
									Ea_Rb_MigClipSrtAdr_u32     += Ea_BlockProperties[BlockNumber].BlkRealLen;
								}
							#endif
						}
					}
                    else
                    {
                        /* Target address area free and non-survival block*/
                        Ea_Rb_Order_st.adStart_uo   = Ea_BlockProperties[BlockNumber].BlkStartAddr;
                    }
#if((EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)&&(EA_NUM_SURVIVAL_BLOCKS > 0))
					if(Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingOver_b != TRUE)
                    {
                        /* New Requirement: Survival Block Handling has not been completed yet so accept invalidate requests for new blocks but dont process them */
                        /* Disable interrupts */
                        SchM_Enter_Ea_Order();

                        if(Ea_Rb_isNewSurvBlkToBeWritten_b == TRUE)
                        {
                            /* Load the Ea Block Number value */
                            Ea_Rb_NewSurvBlkIndex_u16 = BlockNumber;

                            /* Set order type for the further progress in main function */
                            Ea_Rb_Order_st.OrderType_en     = EA_RB_WRITE_ORDER_WAIT_E;
                        }

                        /* Enable interrupts */
                        SchM_Exit_Ea_Order();
					}
#endif
                    if(retVal == E_OK)
                    {
                        /* Update the layout entry of this block */
                        Ea_BlockProperties_onEep[BlockNumber].NvMIdx        = Ea_BlockProperties[BlockNumber].NvMIdx;
                        Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr  = Ea_Rb_Order_st.adStart_uo;
                        Ea_BlockProperties_onEep[BlockNumber].BlkRealLen    = Ea_BlockProperties[BlockNumber].BlkRealLen;
                        Ea_BlockProperties_onEep[BlockNumber].BlkEndAddr    = (Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr
                                                                                + Ea_BlockProperties_onEep[BlockNumber].BlkRealLen)
                                                                                - 1u;
                        Ea_BlockProperties_onEep[BlockNumber].Length        = Ea_BlockProperties[BlockNumber].Length;
                        Ea_BlockProperties_onEep[BlockNumber].Flags         = Ea_BlockProperties[BlockNumber].Flags;
                    }
                }
            }
            else
            {
                /* Check if survival block? */
                if((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SURVIVAL_FLAG) > 0u)
                {
                    /* If this block info has been filled in the Ea_BlockProperties_onEep entries: read directly */

                    if((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr != 0u)
                            && (Ea_BlockProperties_onEep[BlockNumber].NvMIdx == Ea_BlockProperties[BlockNumber].NvMIdx))
                    {
                        Ea_Rb_Order_st.isSurvivalBlk_b  = FALSE;
                        Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr;
                    }
                    else
                    {
                        Ea_Rb_Order_st.isSurvivalBlk_b  = TRUE;

                        /* For survival block, there are no addresses in normal layout.
                         * It should be searched in reserved block to find out the address offset to permanent area.
                         * So the start address should be set to the reserved block */
                        Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties[EA_NUM_BLOCKS-1u].BlkStartAddr;
                    }
                }
                else
                {
                    Ea_Rb_Order_st.isSurvivalBlk_b      = FALSE;
                    Ea_Rb_Order_st.adStart_uo           = Ea_BlockProperties[BlockNumber].BlkStartAddr;
                }
            }

            if(retVal == E_OK)
            {
                /* Set block header */
                Ea_Rb_LoadBlkHdrFromProperties(BlockNumber, &Ea_Rb_BlockHeader_st);

                /* Change flag to invalidated: there is no invalidate order. All invalidate order has been implemented to write order,
                 * this flag is the only difference to write order */
                Ea_Rb_BlockHeader_st.BlockFlags_u8       = Ea_Rb_BlockHeader_st.BlockFlags_u8 | (uint8)EA_INVALID_FLAG;

                /* Initialize block version with 0, will be updated after block check */
                Ea_Rb_BlockHeader_st.BlockVersion_u16    = 0;

                /* Calculate the block data checksum at first, get ready for comparing */
                Ea_Rb_BlockHeader_st.BlockData_CS_u32    = 0;
            }
        }
    }

    return retVal;
}
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

