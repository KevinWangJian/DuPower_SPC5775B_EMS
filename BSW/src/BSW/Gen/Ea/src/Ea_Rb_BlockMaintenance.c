

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
#if (EA_DEV_ERROR_DETECT != FALSE)
    #include "Det.h"
#endif
#include "Ea_Prv.h"

#define EA_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"
Ea_Rb_BlockMaintenance_tst Ea_Rb_BlockMaintenance_st;		/* structure used for maintaining redundant block */
#define EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Ea_MemMap.h"

/**
 *********************************************************************
 * Ea_Rb_BlockMaintenance():
 *
 * [EA_EEP_RBA_04]
 *
 * Repair redundant copy of blocks with security level 2.
 *
 * This function maintains one redundant block to make sure one of the
 * corrupt data to be repaired. The job processing is done
 * within the module's main state and is called cyclically by the
 * system's background. The result of the function indicates
 * whether the order is accepted or not.
 *
 * \param    BlockNumber:     Target address
 * \return   Order acceptance status
 * \retval   E_OK:      Order was accepted
 * \retval   E_NOT_OK:  Order was not accepted
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
FUNC(Std_ReturnType, EA_CODE) Ea_Rb_BlockMaintenance(uint16 BlockNumber)
{
    Std_ReturnType retVal = E_NOT_OK;

    /* Check user parameters*/
    /* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    if((Ea_Rb_CheckInit(EA_SID_RB_MAINTENANCE) != E_OK) ||
           (Ea_Rb_CheckBlkNr(EA_SID_RB_MAINTENANCE, BlockNumber) != E_OK)
    #if((EA_NUM_SURVIVAL_BLOCKS > 0)&&(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE))
           ||(Ea_Rb_SurvBlksHandling_st.isSurvBlksHandlingError_b == TRUE)
    #endif
           )
    {
        retVal = E_NOT_OK;
    }
    else
    {
        /* Disable interrupts */
        SchM_Enter_Ea_Order();

        /* Check the queue availability immediately with interrupts being locked */
        if(Ea_Rb_Order_st.OrderType_en == EA_RB_NO_ORDER_E)
        {
            if ((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0u)
            {
                /* This block doesn't exist in old layout: block inconsistent */
                if((Ea_Rb_MigRunning_b) && ((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr == 0u)
                            || (Ea_BlockProperties_onEep[BlockNumber].NvMIdx != Ea_BlockProperties[BlockNumber].NvMIdx)))
                {
                    /* Set job result directly */
                    Ea_JobResult = MEMIF_BLOCK_INCONSISTENT;
                }
                else
                {
		            /* Set main status to busy independent from other users */
		            Ea_GlobModuleState_st = MEMIF_BUSY;

		            /* Set Ea job result */
		            Ea_JobResult = MEMIF_JOB_PENDING;

		            /* Set order type for the further progress in main function */
		            Ea_Rb_Order_st.OrderType_en     = EA_RB_MAINTAIN_ORDER_E;

		            /* Set request order to recognise the maintain job, unchanged during main function run */
		            Ea_Rb_Order_st.RequestOrder_en  = EA_RB_MAINTAIN_E;

		            /* Set security level bit from block flag settings */
		            Ea_Rb_Order_st.isSecLevelCurr_b = TRUE;
                }

                /* Order has been assigned */
                retVal = E_OK;
            }
        }

        /* Enable interrupts */
        SchM_Exit_Ea_Order();

        /* If this order has been accepted, parameter assignment */
        if((Ea_Rb_Order_st.OrderType_en == EA_RB_MAINTAIN_ORDER_E) && (retVal == E_OK))
        {
			/* Reset the Ea_Rb_BlockMaintenance internal structure content */
			Ea_Rb_BlockMaintenance_st.ReadAddr_uo = 0;
			Ea_Rb_BlockMaintenance_st.WriteAddr_uo = 0;
			Ea_Rb_BlockMaintenance_st.MaintainOrder_en = EA_RB_MAINTAIN_READ_E;
			Ea_Rb_BlockMaintenance_st.numBytes_u32 = 0;
			Ea_Rb_BlockMaintenance_st.numBytesTemp_u32 = 0;

            /* Save user parameters and reset necessary order structure elements */
            Ea_Rb_Order_st.Buffer_un.Write_pcu8 = NULL_PTR;
            Ea_Rb_Order_st.numBytes_u16         = Ea_BlockProperties[BlockNumber].Length;
            Ea_Rb_Order_st.isActivBlkCurr_b     = FALSE;
            Ea_Rb_Order_st.isDataNotEqual_b     = FALSE;
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
                    Ea_Rb_Order_st.isSurvivalBlk_b      = FALSE;
                    Ea_Rb_Order_st.adStart_uo           = Ea_BlockProperties[BlockNumber].BlkStartAddr;
                }
            }

            Ea_Rb_Order_st.BlockLenAligned_uo = Ea_Rb_CalcAlignedLen(Ea_BlockProperties[BlockNumber].Length) + EA_BLK_HEADER_SIZE;

            /* Set block header */
            Ea_Rb_LoadBlkHdrFromProperties(BlockNumber, &Ea_Rb_BlockHeader_st);

            /* Init block version with 0, will be updated after block check */
            Ea_Rb_BlockHeader_st.BlockVersion_u16   = 0;

            /* Calculate the block data checksum at first, get ready for comparing */
            Ea_Rb_BlockHeader_st.BlockData_CS_u32   = 0;

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

