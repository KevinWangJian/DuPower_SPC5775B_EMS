

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR Ea
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
/**
 *********************************************************************
 * Ea_Read(): Read one or more complete EEPROM pages
 *
 * This function reads one or more complete EEPROM pages
 * depending on the user parameters. The job processing is done
 * within the module's main state and is called cyclically.
 * The result of the function indicates whether the order is accepted
 * or not.
 *
 * \param    BlockNumber:     	Number of logical block
 * \param    BlockOffset:  		Read address offset inside the block
 * \param    DataBufferPtr:     Pointer to data buffer
 * \param    Length:            Number of bytes to read
 * \return   Order acceptance status
 * \retval   E_OK:      Order was accepted
 * \retval   E_NOT_OK:  Order was not accepted
 * \seealso
 * \usedresources
 *********************************************************************
 */
Std_ReturnType Ea_Read(uint16 BlockNumber, uint16 BlockOffset, uint8* DataBufferPtr, uint16 Length)
{
    uint16 iLen_u16 = 0;
    Std_ReturnType retVal = E_NOT_OK;

    /* Check user parameters and ea readiness */
    /* [EA130]:
     * If development error detection for the module EA is enabled: the function Ea_Read
     * shall check that the module has been initialized. If this check fails, the function
     * Ea_Read shall raise the development error EA_E_NOT_INITIALIZED and return E_NOT_OK
     * to the caller without performing the requested function.
     *
     * [EA147]:
     * If development error detection for the module EA is enabled: the function Ea_Read
     * shall check whether the given block number is valid (i.e. inside the configured range).
     * If this check fails, the function Ea_Read shall raise the development error
     * EA_E_INVALID_BLOCK_NO and return E_NOT_OK to the caller without performing the requested
     * function. */

    /* MR12 RULE 13.5 VIOLATION : The right hand operand of this logical operator don't need to be called if the left hand operand is TRUE */
    if((Ea_Rb_CheckInit(EA_SID_READ) != E_OK) ||
           (Ea_Rb_CheckBlkNr(EA_SID_READ, BlockNumber) != E_OK)
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

        if((Ea_Rb_Order_st.OrderType_en == EA_RB_NO_ORDER_E) && (Length > 0))
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
                Ea_Rb_Order_st.OrderType_en     = EA_RB_READ_ORDER_E;
                Ea_Rb_Order_st.RequestOrder_en  = EA_RB_READ_E;
            }

            /* Order has been assigned */
            retVal = E_OK;
        }
        else
        {
           /* Check user parameters return E_NOT_OK if:
            * -- read length is NULL.*/
            retVal = E_NOT_OK;
        }

        /* Enable interrupts */
        SchM_Exit_Ea_Order();

        /* If this order has been accepted, parameter assignment */
        if((Ea_Rb_Order_st.OrderType_en == EA_RB_READ_ORDER_E) && (retVal == E_OK))
        {
            /* Save user parameters to current block header */
            /* Attention: Ea_Rb_BlockHeader_st.BlockVersion_u16 will be adapted first after reading valid block data */
            Ea_Rb_LoadBlkHdrFromProperties(BlockNumber, &Ea_Rb_BlockHeader_st);

            /* Load parameters to current order */
            Ea_Rb_Order_st.Buffer_un.Read_pu8       = DataBufferPtr;
            Ea_Rb_Order_st.numID_u16                = Ea_BlockProperties[BlockNumber].NvMIdx;

            if(Ea_Rb_MigRunning_b)
            {
                /* Migration is running, this block exists in old layout? */
                if((Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr != 0u)
                        && (Ea_BlockProperties_onEep[BlockNumber].NvMIdx == Ea_BlockProperties[BlockNumber].NvMIdx))
                {
                    /* During migration running, get the address from the on EEPROM properties
                     * and no difference between survival blocks and non-survival blocks */
                    Ea_Rb_Order_st.isSurvivalBlk_b  = FALSE;
                    Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr + BlockOffset;
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
                        Ea_Rb_Order_st.adStart_uo       = Ea_BlockProperties_onEep[BlockNumber].BlkStartAddr + BlockOffset;
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
                    Ea_Rb_Order_st.adStart_uo           = Ea_BlockProperties[BlockNumber].BlkStartAddr + BlockOffset;
                }
            }

            Ea_Rb_Order_st.BlockLenAligned_uo = Ea_Rb_CalcAlignedLen(Ea_BlockProperties[BlockNumber].Length) + EA_BLK_HEADER_SIZE;

            /* Set security level bit from block flag settings */
            if((Ea_BlockProperties[BlockNumber].Flags & (uint8)EA_SECURITY_LEVEL_FLAG) > 0u)
            {
                Ea_Rb_Order_st.isSecLevelCurr_b = TRUE;
            }
            else
            {
                Ea_Rb_Order_st.isSecLevelCurr_b = FALSE;
            }

            /* [EA_EEP100]: If the user data length is not equal to the configured data length during a read order,
             * the order should not be rejected but the smaller amount of bytes should be transferred instead and
             * the rest of the bytes should be filled up with zeros.
             * - RAM > EEPROM: Copy available EEPROM data to begin of target RAM and fill remaining RAM with a
             *   configurable default initialization value
             * - RAM < EEPROM: Copy available EEPROM data to begin of target RAM and cut exceeding data */
            if(Length > Ea_BlockProperties[BlockNumber].Length)
            {
                Ea_Rb_Order_st.numBytes_u16 = Ea_BlockProperties[BlockNumber].Length;

                for(iLen_u16=Length; iLen_u16>Ea_BlockProperties[BlockNumber].Length; iLen_u16--)
                {
                    DataBufferPtr[iLen_u16-1] = EEP_ERASE_VALUE;
                }
            }
            else
            {
                Ea_Rb_Order_st.numBytes_u16 = Length;
            }

            /* Only for debugging purposes */
            #if (EA_PRV_DEBUGGING == TRUE)
            Ea_Prv_stModuleTest_st.Ea_ReadTimeStart_u32 = Mcu_Rb_GetSysTimePart(TIM0);
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

