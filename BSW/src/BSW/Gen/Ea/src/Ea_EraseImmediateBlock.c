

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */

/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Ea.h"

#if (EA_PRESENT == 1)

#include "Ea_Cfg_SchM.h"
#include "Ea_Prv.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/* *********************************************************************************************************************
 * Req:                 EA093
 *
 * Service name:        Ea_EraseImmediateBlock
 * Syntax:
 *                      Std_ReturnType Ea_EraseImmediateBlock(uint16 BlockNumber)
 * Service ID[hex]:     0x01
 * Sync/Async:          Synchronous
 * Reentrancy:          Non Reentrant
 * Return value:        Std_ReturnType: E_OK --> requirement accepted; E_NOT_OK --> not accepted
 * Description:         Service to call the Eep_Erase function of the underlying EEP driver.
 * ****************************************************************************************************************** */
Std_ReturnType Ea_EraseImmediateBlock(uint16 BlockNumber)
{
    Std_ReturnType retVal = E_NOT_OK;

    /* Check user parameters and Ea readiness */

    /* [EA136]: If development error detection for the module Ea is enabled: the function Ea_EraseImmediateBlock
     * shall check that the module has been initialized. If this check fails, the function Ea_EraseImmediateBlock
     * shall raise the development error EA_E_NOT_INITIALIZED and return E_NOT_OK to the caller without performing
     * the requested function.
     *
     * [EA152]: If development error detection for the module EA is enabled: the function Ea_EraseImmediateBlock
     * shall check whether the given block number is valid (i.e. inside the configured range). If this check fails,
     * the function Ea_InvalidateBlock shall raise the development error EA_E_INVALID_BLOCK_NO and return E_NOT_OK
     * to the caller without performing the requested function. */

    /* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    if((Ea_Rb_CheckInit(EA_SID_ERASE) != E_OK) ||
           (Ea_Rb_CheckBlkNr(EA_SID_ERASE, BlockNumber) != E_OK)
    #if((EA_NUM_SURVIVAL_BLOCKS > 0)&&(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE))
           ||(Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingError_b == TRUE)
    #endif
           )
    {
        retVal = E_NOT_OK;
    }
    /* [EA162]:
     * If a erase is rejected by the function Ea_EraseImmediateBlock, i.e. requirements EA136
     * or EA152 apply, the function Ea_EraseImmediateBlock shall not change the current module status or job result. */
    else
    {
        /* Disable interrupts */
        SchM_Enter_Ea_Order();

        /* Check the queue availability immediately with interrupts being locked */
        if(Ea_Rb_Order_st.OrderType_en == EA_RB_NO_ORDER_E)
        {
	        /* This block doesn't exist in old layout: block inconsistent */
	        if((Ea_Rb_MigRunning_b) && ((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr == 0u)
	           || (Ea_BlockProperties_onEep[BlockNumber].NvMIdx != Ea_BlockProperties[BlockNumber].NvMIdx)))
	        {
	            /* Set job result directly */
	            Ea_JobResult = MEMIF_JOB_OK;
	        }
	        else
	        {
	            /* Set main status to busy independent from other users */
	            Ea_GlobModuleState_st = MEMIF_BUSY;

	            /* Set Ea job result */
	            Ea_JobResult = MEMIF_JOB_PENDING;

	            /* Initiate erase job */
	            Ea_Rb_Order_st.OrderType_en = EA_RB_ERASE_ORDER_E;
			}

            /* Order has been assigned */
            retVal = E_OK;
        }

        /* Enable interrupts */
        SchM_Exit_Ea_Order();

        /* If this order has been accepted, parameter assignment */
        if((Ea_Rb_Order_st.OrderType_en == EA_RB_ERASE_ORDER_E) && (retVal == E_OK))
        {
            /* Save user parameters and reset necessary order structure elements */
            Ea_Rb_Order_st.numBytes_u16         = Ea_BlockProperties[BlockNumber].Length;
            Ea_Rb_Order_st.isActivBlkCurr_b     = FALSE;
            Ea_Rb_Order_st.numID_u16            = Ea_BlockProperties[BlockNumber].NvMIdx;

            if(Ea_Rb_MigRunning_b)
            {
                /* Migration is running, this block exists in old layout? */
                if((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr != 0u)
                        && (Ea_BlockProperties_onEep[BlockNumber].NvMIdx == Ea_BlockProperties[BlockNumber].NvMIdx))
                {
                    /* During migration running, get the address from the on EEPROM properties
                     * and no difference between survival blocks and non-survival blocks */
                    Ea_Rb_Order_st.isSurvivalBlk_b  = FALSE;
                    Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr;
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
                    /* Reset the survival block flag */
                    Ea_Rb_Order_st.isSurvivalBlk_b  = FALSE;

                    /* Set the start address of current block */
                    Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties[BlockNumber].BlkStartAddr;
                }
            }

            Ea_Rb_Order_st.BlockLenAligned_uo  = Ea_Rb_CalcAlignedLen(Ea_BlockProperties[BlockNumber].Length) + EA_BLK_HEADER_SIZE;

            /* Set security level flag */
            if((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0)
            {
                Ea_Rb_Order_st.isSecLevelCurr_b     = TRUE;
                Ea_Rb_Order_st.BlockLenAligned_uo  *= 2u;
            }
            else
            {
                Ea_Rb_Order_st.isSecLevelCurr_b     = FALSE;
            }

            /* Only for debugging purposes */
            #if (EA_PRV_DEBUGGING == TRUE)
            Ea_Prv_stModuleTest_st.Ea_WriteTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
            /* EA_PRV_DEBUGGING */
            #endif
        }
    }

    return retVal;
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

