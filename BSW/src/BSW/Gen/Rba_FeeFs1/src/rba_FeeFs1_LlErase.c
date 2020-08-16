


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
#include "Fls.h"
#include "Fls_Types.h"
#if (!defined(FLS_AR_RELEASE_MAJOR_VERSION) || (FLS_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
   // #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FLS_AR_RELEASE_MINOR_VERSION) || ((FLS_AR_RELEASE_MINOR_VERSION != 0) && (FLS_AR_RELEASE_MINOR_VERSION != 2)))
   // #error "AUTOSAR minor version undefined or mismatched"
#endif

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if (FEE_PRESENT == 1)
/**
 *********************************************************************
 * Fee_LLSetEraseSector(): Set sector index of erase order
 *
 * This function sets the sector index of the global erase order
 * to the respective index value of the logical sector
 *
 * \param    EraseLogIdx:   Logical sector index
 * \return
 * \retval   none
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_LLSetEraseSector(VAR(uint8, AUTOMATIC) EraseLogIdx)
{
	Fee_LLEraseOrder_st.xPhySectorIdx_u8 = Fee_LLSectorOrder_st[EraseLogIdx].xPhySecIdx_u8;

	Fee_LLSectorOrder_st[EraseLogIdx].SecState_en 		= FEE_SECTOR_REQUEST2ERASE_E;
	Fee_LLSectorOrder_st[EraseLogIdx].SecChngCnt_u32  	= FEE_SEC_CHANGE_CNT_UNDEF;
}


/**
 *********************************************************************
 * Fee_LLEraseSector(): Erase the selected sector
 *
 * This function erases the formerly selected sector.
 *
 * \param    none
 * \return   Function result
 * \retval   FEE_ORDER_PENDING_E:   Order is still pending
 * \retval   FEE_ABORTED_E:         Order was aborted due to a wrong
 *                                  FLS compare function call
 * \retval   FEE_ERROR_E:           Writing of the erase marker is
 *                                  not possible
 * \retval   FEE_ORDER_FINISHED_E:  Order finished successfully
 *                                  (including write operation for the
 *                                   ERASE marker)
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Fee_stRetVal_ten, FEE_CODE) Fee_LLEraseSector(void)
{
    VAR(Fee_stRetVal_ten, AUTOMATIC) xRetVal = FEE_ORDER_PENDING_E;
    VAR(Fls_AddressType, FEE_VAR)    xAdStart_uo;
    VAR(Fls_LengthType, FEE_VAR)     xSecSize_uo;
    VAR(uint16, FEE_VAR)             xCacheIdx_u16;

    #if (FEE_PRV_DEBUG_MONITOR != FALSE)
    VAR(uint32, FEE_VAR)             stDBM_u32 = 0;
    #endif


	/* Switch over state machine */
	switch(Fee_LLEraseOrder_st.EraseState_en)
	{
		/* Idle state */
		case FEE_ERASESEC_IDLE_E:
		{
			;
		}
		/* No break to save time */

		/* Check if any cache entry points to the sector which should be erased */
		case FEE_ERASESEC_CHECK_CACHE_E:
		{
			for (xCacheIdx_u16 = 0; xCacheIdx_u16 < FEE_NUM_BLOCKS; xCacheIdx_u16++)
			{
				if ((Fee_Cache_au32[xCacheIdx_u16] >= Fee_FlashProp_st[Fee_LLEraseOrder_st.xPhySectorIdx_u8].Fee_PhysStartAddress_u32) &&
					(Fee_Cache_au32[xCacheIdx_u16] <= Fee_FlashProp_st[Fee_LLEraseOrder_st.xPhySectorIdx_u8].Fee_PhysEndAddress_u32))
				{
                    /* Set the Cache to FEE_CACHE_TMP_INVALID_VALUE for all blocks that are in the sector which gets erased */
				    Fee_Cache_au32[xCacheIdx_u16] = FEE_CACHE_TMP_INVALID_VALUE;

                    #if (FEE_PRV_DEBUG_MONITOR != FALSE)
					/* Set status for Debug monitor */
					stDBM_u32 = 0x1;
					xRetVal = FEE_ERROR_E;
                    #endif
				}
			}

			/* Set next state */
			Fee_LLEraseOrder_st.EraseState_en = FEE_ERASESEC_START_E;
		}
        /* No break to save time */

		/* Start the erase procedure */
		/* MR12 RULE 16.3 VIOLATION: Time critical position */
		case FEE_ERASESEC_START_E:
		{
			/* Check if the sector index is valid */
			if(Fee_LLEraseOrder_st.xPhySectorIdx_u8 != FEE_NO_SECTOR_TO_ERASE)
			{
				xAdStart_uo   = Fee_FlashProp_st[Fee_LLEraseOrder_st.xPhySectorIdx_u8].Fee_PhysStartAddress_u32;

				xSecSize_uo  = (Fee_FlashProp_st[Fee_LLEraseOrder_st.xPhySectorIdx_u8].Fee_PhysEndAddress_u32 + 1u) -
								Fee_FlashProp_st[Fee_LLEraseOrder_st.xPhySectorIdx_u8].Fee_PhysStartAddress_u32;

				/* Erase the respective sector */
				if(Fls_Erase(xAdStart_uo, xSecSize_uo) == E_OK)
				{
					/* Set next state */
					Fee_LLEraseOrder_st.EraseState_en = FEE_ERASESEC_DO_E;
				}
				else
				{
					/* Order was denied due to wrong parameters or an already busy Fls */
					xRetVal = FEE_ABORTED_E;
				}

				/* Erase the cache status for any block within this sector
				 * --> not necessary */

				#if (FEE_PRV_DEBUGGING != FALSE)
				Fee_Prv_stModuleTest_st.Fee_EraseTimeStart_u32 =
						MCU_RB_TIM0TICKS_TO_MS(Mcu_Rb_GetSysTimePart(TIM0));
				#endif
			}
			else
			{
				/* No sector currently selected for an erase operation */
				xRetVal = FEE_ABORTED_E;
			}
		}
		break;

		/* Wait for the order to be finished */
		case FEE_ERASESEC_DO_E:
		{
			/* switching state from FEE_ERASESEC_DO --> FEE_ERASESEC_END will be done in
			 * Fee_JobEndNotification and Fee_JobErrorNotification */

			/* Check whether the OS is currently running or not */
			if(Fee_stMain == FEE_POLLING_MODE_E)
			{
				/* Call the Fls main function manually */
				Fls_MainFunction();
			}

			#if (STD_ON == FEE_POLLING_MODE)
			/* Use the FLS polling mechanism in order to reach the next state */
			Fee_CheckFlsJobResult();
			#endif
		}
		break;

		/* Write the sector ERASED marker */
		case FEE_ERASESEC_WRITE_MARKER_E:
		{
			xRetVal = Fee_LLWriteMarker(Fee_LLEraseOrder_st.xPhySectorIdx_u8, FEE_ERASED_MARKER_ID_E);

			/* Error reaction not necessary
			 * --> RAM structure will be set and used for the identification of the next
			 *     sector can be used as long as the Fee_Init is not passed again.
			 * --> If init is passed, the sector might get erased again */
		}
		break;

		/* Error case */
		case FEE_ERASESEC_ERROR_E:
		default:
			/* Return with error */
			xRetVal = FEE_ERROR_E;
		break;
	}


    /* Check if order was finished with or without success */
    if (xRetVal != FEE_ORDER_PENDING_E)
    {
        #if (FEE_PRV_DEBUG_MONITOR != FALSE)
        /* Report Debug monitor */
        if (stDBM_u32 > 0)
        {
            Fee_DBM_RepError(Fee_LLEraseOrder_st.xPhySectorIdx_u8, FEE_DBM_ERROR_ERASE_FCT_E, stDBM_u32);
            stDBM_u32 = 0;
        }
        #endif

        /* Reset state machine */
        Fee_LLEraseOrder_st.EraseState_en = FEE_ERASESEC_IDLE_E;

        /* Mark sector state */
        Fee_LLEraseOrder_st.xPhySectorIdx_u8  = FEE_NO_SECTOR_TO_ERASE;

        #if (FEE_PRV_DEBUGGING != FALSE)
                Fee_Prv_stModuleTest_st.Fee_EraseTimeEnd_u32 =
                        MCU_RB_TIM0TICKS_TO_MS(Mcu_Rb_GetSysTimePart(TIM0));

        Fee_Prv_stModuleTest_st.Fee_EraseTimeDiff_u32 =
                                Fee_Prv_stModuleTest_st.Fee_EraseTimeEnd_u32 -
                                Fee_Prv_stModuleTest_st.Fee_EraseTimeStart_u32;

        if(Fee_Prv_stModuleTest_st.Fee_EraseTimeDiffMax_u32 <
           Fee_Prv_stModuleTest_st.Fee_EraseTimeDiff_u32)
        {
            Fee_Prv_stModuleTest_st.Fee_EraseTimeDiffMax_u32 =
            Fee_Prv_stModuleTest_st.Fee_EraseTimeDiff_u32;
        }
        #endif
    }

    return (xRetVal);
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_PRESENT */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
