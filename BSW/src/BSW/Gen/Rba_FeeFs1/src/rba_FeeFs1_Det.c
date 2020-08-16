


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

#if(STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
/* FEE_DEV_ERROR_DETECT == STD_ON*/
#endif
/* Version check deactivated due to incompatabality with CC-AS (AR3.1)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
*/


/**
 *********************************************************************
 * Fee_CheckModuleSt(): Check the module status
 *
 * This functions checks for the module to be in the idle state.
 * If this is not the case, an error is reported to the DET
 * module.
 *
 * Hint: The module status MEMIF_BUSY_INTERNAL is not checked due to
 *       the multi - user concept (Eep_Adapt / NvM / Internal orders).
 *
 * \param   ApiId_u8 : ID of API service in which error is detected
 * \return  status of check
 * \retval  E_OK     : status OK
 * \retval  E_NOT_OK : status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(Std_ReturnType, FEE_CODE) Fee_CheckModuleSt(VAR(uint8, AUTOMATIC) ApiId_u8)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_OK;      /* Function return */

    /* Check whether the current FEE status is MEMIF_BUSY or MEMIF_BUSY_INTERNAL
	 * (only for the Fee_SetMode function because all other user APIs can
	 *  handle several users at the same time, e.g. NvM and adapter jobs) */
    if(ApiId_u8 == FEE_SID_SETMODE)
    {
        /* Check whether the current FEE status is MEMIF_BUSY or not */
        if(Fee_GlobModuleState_st == MEMIF_BUSY)
        {
            #if(STD_ON == FEE_DEV_ERROR_DETECT)
            /* Report error to DET */
            /* MR12 RULE 17.7 VIOLATION: Return value is not required */
            (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_BUSY);
            #else
            (void)ApiId_u8;
            #endif

            /* Return with an error */
            xRetVal = E_NOT_OK;
        }

        /* Check whether the current FEE status is MEMIF_BUSY_INTERNAL or not */
        if(Fee_GlobModuleState_st == MEMIF_BUSY_INTERNAL)
        {
                #if(STD_ON == FEE_DEV_ERROR_DETECT)
            /* Report error to DET */
            /* MR12 RULE 17.7 VIOLATION: Return value is not required */
            (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_BUSY_INTERNAL);
            #else
            (void)ApiId_u8;
            #endif

            /* Return with an error */
            xRetVal = E_NOT_OK;
        }
    }

    /* Check whether the current FEE status is MEMIF_UNINIT */
    if(Fee_GlobModuleState_st == MEMIF_UNINIT)
    {
        #if(STD_ON == FEE_DEV_ERROR_DETECT)
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_UNINIT);
        #else
        (void)ApiId_u8;
        #endif

        /* Return with an error */
        xRetVal = E_NOT_OK;
    }


	/* Return result of check */
	return (xRetVal);
}


/**
 *********************************************************************
 * Fee_CheckBlockCfg(): Check if the given block number is valid
 *
 * This functions checks if the given user block number is valid.  The
 * block number refers to the auto generated block index that is used
 * by the Fee interfaces.
 *
 * \param   ApiId_u8 : ID of API service in which error is detected
 * \return  status of check
 * \retval  E_OK     : status OK
 * \retval  E_NOT_OK : status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlockCfg(VAR(uint8, AUTOMATIC)  ApiId_u8,
                                                 VAR(uint16, AUTOMATIC) BlockNum_u16)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_OK;  /* Function return */

	/* Check if the requested block index can be found */
    if(BlockNum_u16 >= FEE_NUM_BLOCKS)
    {
        #if(STD_ON == FEE_DEV_ERROR_DETECT)
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_INVALID_BLOCK_NO);
        #else
        (void)ApiId_u8;
        #endif

        /* Block number is valid, set return value */
        xRetVal = E_NOT_OK;
    }

    /* Return result */
    return (xRetVal);
}


/**
 *********************************************************************
 * Fee_CheckAdrPtr(): Check the user's data buffer pointer
 *
 * \param   ApiId_u8          : ID of API service in which error is detected
 * \param   DataBufferPtr_pcu8: Constant pointer to target address
 * \return  Status of check
 * \retval  E_OK    : status OK
 * \retval  E_NOT_OK: status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Std_ReturnType, FEE_CODE) Fee_CheckAdrPtr(VAR(uint8, AUTOMATIC) ApiId_u8,
                                               P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr_pcu8)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_OK;      /* Function return */

    /* Check whether the given data buffer pointer is a NULL pointer */
    if(DataBufferPtr_pcu8 == NULL_PTR)
    {
        #if(STD_ON == FEE_DEV_ERROR_DETECT)
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_INVALID_DATA_PTR);
        #else
        (void)ApiId_u8;
        #endif

        /* Return an error */
        xRetVal = E_NOT_OK;
    }

    /* Return function result */
    return(xRetVal);
}


/**
 *********************************************************************
 * Fee_CheckBlkOfs(): Check the user's block offset
 *
 * \param   ApiId_u8         : ID of API service in which error is detected
 * \param   BlockNum_u16     : Block number
 * \param   BlockOfs_u16     : Block offset
 * \return  Status of check
 * \retval  E_OK    : status OK
 * \retval  E_NOT_OK: status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlkOfs(VAR(uint8, AUTOMATIC) ApiId_u8,
                                               VAR(uint16, AUTOMATIC) BlockNum_u16,
                                               VAR(uint16, AUTOMATIC) BlockOfs_u16)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_OK;  /* Function return */

    /* Check if the requested block index is valid */
    if(BlockNum_u16 >= FEE_NUM_BLOCKS)
    {
        /* Block index is invalid, allow the check of the block offset */
        xRetVal = E_NOT_OK;
    }
    else
    {
        /* Check whether the given block offset is valid */
        if(BlockOfs_u16 >= Fee_BlockProperties_st[BlockNum_u16].Length_u16)
        {
            #if(STD_ON == FEE_DEV_ERROR_DETECT)
            /* Report error to DET */
            /* MR12 RULE 17.7 VIOLATION: Return value is not required */
            (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_INVALID_BLOCK_OFS);
            #else
            (void)ApiId_u8;
            #endif

            /* Return an error */
            xRetVal = E_NOT_OK;
        }
    }

    /* Return function result */
    return(xRetVal);
}


/**
 *********************************************************************
 * Fee_CheckBlkLen(): Check the user's block length
 *
 * \param   ApiId_u8         : ID of API service in which error is detected
 * \param   BlockNum_u16     : Block number
 * \param   BlockOfs_u16     : Block offset
 * \param   BlockLen_u16     : Block length
 * \return  Status of check
 * \retval  E_OK    : status OK
 * \retval  E_NOT_OK: status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
FUNC(Std_ReturnType, FEE_CODE) Fee_CheckBlkLen(VAR(uint8, AUTOMATIC) ApiId_u8,
                                               VAR(uint16, AUTOMATIC) BlockNum_u16,
                                               VAR(uint16, AUTOMATIC) BlockOfs_u16,
                                               VAR(uint16, AUTOMATIC) BlockLen_u16)
{
    VAR(Std_ReturnType, AUTOMATIC) xRetVal = E_OK;      /* Function return */

    /* Check if the requested block index is valid */
    if(BlockNum_u16 >= FEE_NUM_BLOCKS)
    {
        /* Block index is invalid, allow the check of the block offset */
        xRetVal = E_NOT_OK;
    }
    else
    {
        /* Check whether the given block length is valid */
        if((BlockLen_u16 + BlockOfs_u16) > Fee_BlockProperties_st[BlockNum_u16].Length_u16)
        {
            #if(STD_ON == FEE_DEV_ERROR_DETECT)
            /* Report error to DET */
            /* MR12 RULE 17.7 VIOLATION: Return value is not required */
            (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId_u8, FEE_E_INVALID_BLOCK_LEN);
            #else
            (void)ApiId_u8;
            #endif

            /* Return an error */
            xRetVal = E_NOT_OK;
        }
    }

    /* Return function result */
    return(xRetVal);
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif


/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
