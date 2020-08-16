


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
#include "rba_FeeFs1_Prv.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_SrvBinarySearchInBlockProp(): Get the respective index out of
 *                                   the block properties table
 *
 * This function searches for the respective block properties table
 * index. In case unknown blocks are searched, the function will
 * return with a negative response.
 *
 * \param    FeeIdx_u16:    Fee index (persistent ID)
 * \param    CacheIdx_pu16: Pointer for the result
 * \return   Success of the function
 * \retval   FALSE: Corresponding index was not found
 * \retval   TRUE:  Corresponding index was found
 *
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(boolean, FEE_CODE) Fee_SrvBinarySearchInBlockProp(VAR(uint16, AUTOMATIC) FeeIdx_u16,
                                                       P2VAR(uint16, AUTOMATIC, FEE_APPL_DATA) CacheIdx_pu16)
{
    VAR(boolean, AUTOMATIC)  xFuncRet_b = FALSE;    /* Function return value */
    VAR(uint16, AUTOMATIC)  xMid_u16;               /* Mid index for the search */
    VAR(uint16, AUTOMATIC)  xLeft_u16 = 0;          /* Left index for the search */
    VAR(uint16, AUTOMATIC)  xRight_u16 = FEE_NUM_BLOCKS - 1u; /* Right index for the search */

    /* Loop until the value is found */
    do
    {
        /* Divide search area by two */
        xMid_u16 = (uint16)(xLeft_u16 + ((xRight_u16 - xLeft_u16) / 2));

        /* Check the cache content */
        if(Fee_BlockProperties_st[xMid_u16].BlockPersistentId_u16 == FeeIdx_u16)
        {
            /* Index was found, set return value */
            *CacheIdx_pu16 = xMid_u16;

            /* Return positive response */
            xFuncRet_b = TRUE;

            /* Leave the loop */
            return xFuncRet_b;
        }

        /* Check the current array index */
        if(Fee_BlockProperties_st[xMid_u16].BlockPersistentId_u16 > FeeIdx_u16)
        {
            /* Check if the lowest array position is reached */
            if(xMid_u16 != 0)
            {
                /* Reduce the right limit to the left */
                xRight_u16 = (uint16)(xMid_u16 - 1u);
            }
            else
            {
                /* Leave the loop with a negative response */
                return xFuncRet_b;
            }
        }
        else
        {
            /* Reduce the left limit to the right (upper limit is
             * safe because of the loop condition) */
            xLeft_u16 = (uint16)(xMid_u16 + 1u);
        }
    }
    while(xRight_u16 >= xLeft_u16);

    return xFuncRet_b;
}


/**
 *********************************************************************
 * Fee_Rb_GetSectChngCnt(): Return number of sector changes
 *
 * This function returns the number of sector changes (sector
 * reorganizations) which is represented by the sector change
 * counter of the current USED sector.
 *
 * \param   none
 * \return  xSecChngCnt_u32: Number of sector changes
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(uint32, FEE_CODE) Fee_Rb_GetSectChngCnt(void)
{
    VAR(uint32, AUTOMATIC)  xSecChngCnt_u32;        /* Function return value */

    /* Check if a division is possible */
    if(Fee_SecChngCnt_u32 >= FEE_NUM_FLASH_BANKS)
    {
        /* Calculate the amount of sector reorganizations */
        xSecChngCnt_u32 = (Fee_SecChngCnt_u32 - FEE_NUM_FLASH_BANKS);
    }
    else
    {
        /* No sector reorganization was necessary so far */
        xSecChngCnt_u32 = 0;
    }

    return(xSecChngCnt_u32);
}

/**
 **********************************************************************************************************************
 * Fee_Rb_DisableBackgroundOperation(): This function when called stops the execution of background operations i.e.,
 * Soft Sector Reorganisation and Sector Erase.
 * It does not suspend or stops the already ongoing background task but stops further background operations execution i.e.,
 * if a sector reorganisation operation has started and one job is currently being transfered then the current block
 * operation will be completed and next block will not be transfered. if an erase is ongoing, then it will wait for the
 * erase to be completed and next background operation will not be started.
 * Application requests of read, write, maintain, invalidate and others will be processed as usual without any delay.
 * HSR will also be processed without any delay.
 *
 * The interface is to be used only if there are some critical writes coming up and to delay background operations so that
 * the new requests are not disturbed or delayed by background requests.
 *
 * Background tasks could be resumed again by calling the API Fee_Rb_EnableBackgroundOperation().
 *
 * Please note, background operations can only be delayed till HSR is reached.
 *
 * \param   none
 * \return  none
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
FUNC(void, FEE_CODE) Fee_Rb_DisableBackgroundOperation(void)
{
    /* Stop the ongoing background operations. */
    Fee_Prv_stInit_u8 = FEE_PRV_ST_INIT_RUNNING;
}

/**
 **********************************************************************************************************************
 * Fee_Rb_EnableBackgroundOperation(): This function when called resumes the execution of background operations i.e.,
 * Soft Sector Reorganisation and Sector Erase if it was halted by Fee_Rb_DisableBackgroundOperation().
 *
 * \param   none
 * \return  none
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
FUNC(void, FEE_CODE) Fee_Rb_EnableBackgroundOperation(void)
{
    /* Resume the ongoing background operations. */
    Fee_Prv_stInit_u8 = FEE_PRV_ST_INIT_DONE;
}

/**
 ***************************************************************************************************
 * Fee_SrvMemSet8 - initialize memory with 8 Bit data
 *
 * Memory initialization routine. 8 Bit Pattern is written to the destination.
 *
 * \param   xDest_pu8       destination address
 * \param   xPattern_u32    fill pattern, only lower 8 bit used
 * \param   numBytes_u32    number of bytes to be initialized
 * \return
 * \seealso
 ***************************************************************************************************
 */
FUNC(void, FEE_CODE)  Fee_SrvMemSet8(P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) xDest_pu8,
                                     VAR(uint32, FEE_VAR) xPattern_u32,
                                     VAR(uint32, FEE_VAR) numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = (uint8)xPattern_u32;
        xDest_pu8++;
    }

    return;
}


/**
 ***************************************************************************************************
 * Fee_SrvMemCopy8 - copy non overlapping memory
 *
 * Memory copy routine. Source and destination must not overlap.
 *
 * \param   xDest_pu8       destination address
 * \param   xSrc_pcu8       source address
 * \param   numBytes_u32    number of bytes to be copied
 * \return
 * \seealso
 ***************************************************************************************************
 */
FUNC(void, FEE_CODE)  Fee_SrvMemCopy8(P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) xDest_pu8,
                                      P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) xSrc_pcu8,
                                      VAR(uint32, FEE_VAR) numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = *xSrc_pcu8;
        xDest_pu8++;
        xSrc_pcu8++;
    }

    return;
}


/**
 ***************************************************************************************************
 * Fee_SrvSetFifoMode - Set the internal order mode of the module
 *
 * This function changes the internal order mode within the order fifo of the module.
 * This is done inside a function in order to ensure the correct read and write order
 * in combination with other variables in case of compiler optimizations. Therefor
 * no common locks are necessary.
 *
 * \param   Mode_en         mode to be set
 * \param   xJobType_u16    index for order queue
 * \return
  * \seealso
 ***************************************************************************************************
 */
FUNC(void, FEE_CODE)  Fee_SrvSetFifoMode(VAR(Fee_HlMode_ten, AUTOMATIC) Mode_en,
                                         VAR(uint16, AUTOMATIC) xJobType_u16)
{
    /* Set the order mode and return */
    Fee_OrderFifo_st[xJobType_u16].Mode_en = Mode_en;

    return;
}


/**
 ***************************************************************************************************
 * Fee_SrvGetFifoMode - Get the internal order mode of the module
 *
 * This function returns the internal order mode of the respective position within the
 * order fifo of the module.
 * This is done inside a function in order to ensure the correct read and write order
 * in combination with other variables in case of compiler optimizations. Therefor
 * no common locks are necessary.
 *
 * \param   xJobType_u16    index for order queue
 * \return  current mode
 * \seealso
 ***************************************************************************************************
 */
FUNC(Fee_HlMode_ten, FEE_CODE)  Fee_SrvGetFifoMode(VAR(uint16, AUTOMATIC) xJobType_u16)
{
    /* Return the order mode of the respective array position */
    return Fee_OrderFifo_st[xJobType_u16].Mode_en;
}

#if (FEE_PRV_DEBUG_MONITOR != FALSE)
/**
 ***************************************************************************************************
 * Fee_DBM_RepError - Debug monitor function
 *
 * This function stores information for debug monitor.
 *
 * \param   FeeBlkIdx    Fee block index
 * \param   xError       Error ID
 * \param   xErrorInfo   Error info
 * \return  none
 * \seealso
 ***************************************************************************************************
 */
FUNC(void ,FEE_CODE) Fee_DBM_RepError(VAR(uint16,FEE_VAR) FeeBlkIdx, VAR(Fee_DebugMonitoringFct_ten,FEE_VAR) xError, VAR(uint8,FEE_VAR) xErrorInfo)
{
    Fee_DebugMonitoring.xErrorEntry[Fee_DebugMonitoring.idxNewEntry].FeeBlkIdx      = FeeBlkIdx;
    Fee_DebugMonitoring.xErrorEntry[Fee_DebugMonitoring.idxNewEntry].xError         = xError;
    Fee_DebugMonitoring.xErrorEntry[Fee_DebugMonitoring.idxNewEntry].xErrorInfo     = xErrorInfo;
    Fee_DebugMonitoring.xErrorEntry[Fee_DebugMonitoring.idxNewEntry].xSecChngCntVal = Fee_SecChngCnt_u32;
    Fee_DebugMonitoring.idxNewEntry++;

    if (Fee_DebugMonitoring.idxNewEntry >= FEE_DBM_ERROR_ENTRIES)
    {
        /* If debug monitor is full, overwrite the last entry */
        Fee_DebugMonitoring.idxNewEntry = FEE_DBM_ERROR_ENTRIES - 1;
        if (Fee_DebugMonitoring.ctBuffOverflow < 0xFF)
        {
            Fee_DebugMonitoring.ctBuffOverflow++;
        }

    }
}
#endif
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
