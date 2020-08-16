


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
#include "Fee_Cfg_SchM.h"
#include "rba_FeeFs1_Prv.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_HLPlaceOrder(): Place a user order to the order FIFO
 *
 * This function checks the user request and saves the order to the
 * FEE order FIFO.
 *
 * \param    Blocknumber_u16:   Auto generated block index that is
 *                              used by the Fee interfaces
 *           Offset_u16:        Data offset
 *           DataBufferPtr_pu8: Data pointer
 *           Length_16:         Data length (necessary only for read
 *                              orders)
 *           Mode_en:           Read / Write / Invalidation order type
 * \return   Function success
 * \retval   E_OK:              Order was successfully placed
 * \retval   E_NOT_OK:          Order was not placed because the
 *                              respective order queue entry is
 *                              not empty
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Std_ReturnType, FEE_CODE) Fee_HLPlaceOrder(VAR(uint16, AUTOMATIC) Blocknumber_u16,
                                                VAR(uint16, AUTOMATIC) Offset_u16,
                                                P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr_pu8,
                                                VAR(uint16, AUTOMATIC) Length_16,
                                                VAR(Fee_HlMode_ten, AUTOMATIC) Mode_en)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_NOT_OK;  /* Function return */
    VAR(uint16, AUTOMATIC) xJobType_u16;                /* Fee job type */
    VAR(uint16, AUTOMATIC) xJobPrio_u16;                /* Fee job priority */
    VAR(uint8, AUTOMATIC)  xSecLevel_u8;                /* Fee Security Level */

    /* Check if the requested block index can be found */
    if(Blocknumber_u16 < FEE_NUM_BLOCKS)
    {
        /* Disable interrupts */
        SchM_Enter_Fee_Order();

        /* Get the configured type of this block */
        xJobType_u16 = (uint16)((Fee_BlockProperties_st[Blocknumber_u16].Flags_u16 & FEE_FLAG_JOBTYPE_MSK) >> FEE_FLAG_JOBTYPE_BP);

        /* Check if the respective queue position is free and if the order is
         * currently allowed to be placed */
        if(Fee_SrvGetFifoMode(xJobType_u16) == FEE_NO_ORDER)
        {

			/* Set the job result state to pending */
			Fee_JobResult[xJobType_u16] = MEMIF_JOB_PENDING;

            /* Extract the job priority out of the configuration */
            xJobPrio_u16 = (uint16)((Fee_BlockProperties_st[Blocknumber_u16].Flags_u16 & FEE_FLAG_JOBPRIO_MSK) >> FEE_FLAG_JOBPRIO_BP);

            /* Save the priority to the order entry */
            /* MR12 RULE 10.5 VIOLATION: Job priority is defined as enum for modular design and easy to read. */
            Fee_OrderFifo_st[xJobType_u16].Prio_en = (Fee_HlPriority_ten)xJobPrio_u16;

            /* Extract the security level out of the configuration and convert it from internal to a user config type
             * --> easy to use */
            // Shift of the block propertie's flags is not necessary here, because the offset is 0
            xSecLevel_u8 = FEE_INT_TO_USER_STORAGE_TYPE((uint8)((Fee_BlockProperties_st[Blocknumber_u16].Flags_u16 &
                                                                    FEE_FLAG_SEC_LEVEL_MSK)));

            /* Save the security level to the order entry */
            Fee_OrderFifo_st[xJobType_u16].SecLevel_u8 = xSecLevel_u8;

            /* Copy the corresponding Fee/block properties info */
            Fee_OrderFifo_st[xJobType_u16].FeeIdx_u16        = Fee_BlockProperties_st[Blocknumber_u16].BlockPersistentId_u16;
            Fee_OrderFifo_st[xJobType_u16].BlockPropIdx_u16  = Blocknumber_u16;

            /* Copy the original user buffer pointer */
            Fee_OrderFifo_st[xJobType_u16].DataBufferPtr_pu8 = DataBufferPtr_pu8;

            /* Check the order type */
            if(Mode_en == FEE_READ_ORDER)
            {
                /* For read orders the user length is necessary, copy the original value */
                Fee_OrderFifo_st[xJobType_u16].Length_u16 = Length_16;
            }
            else
            {
                /* For write or invalidation orders the configured length can be
                 * extracted out of the configuration */
                Fee_OrderFifo_st[xJobType_u16].Length_u16 = Fee_BlockProperties_st[Blocknumber_u16].Length_u16;
            }

            /* Save the user offset and the order type (via function call to prevent from compiler optimization
             * and to ensure the correct order) */
            Fee_OrderFifo_st[xJobType_u16].Offset_u16  = Offset_u16;
            Fee_SrvSetFifoMode(Mode_en, xJobType_u16);

            /* Set the return status */
            xRetVal = E_OK;
        }
        else
        {
            /* Order entry is not empty, return an error */
            xRetVal = E_NOT_OK;
        }

        /* Enable interrupts */
        SchM_Exit_Fee_Order();
    }

    return (xRetVal);
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_PRESENT == 1 */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
