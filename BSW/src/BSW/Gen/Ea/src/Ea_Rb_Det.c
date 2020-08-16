

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
 #if (EA_DEV_ERROR_DETECT != FALSE)
    #include "Det.h"
 #endif
#include "Ea_Prv.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
/**
 *********************************************************************
 * Ea_Rb_CheckInit()
 *
 * \param   ApiId_u8       : ID of API service in which error is detected
 * \param   Ea_ModuleIdx_u8: Ea module index
 * \return  status of check
 * \retval  E_OK    : status OK
 * \retval  E_NOT_OK: status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
Std_ReturnType Ea_Rb_CheckInit(uint8 ApiId_u8)
{
    Std_ReturnType stRetLoc_en = E_OK;

    /* Check init status */
    if(Ea_Rb_stInit_u8 == EA_RB_ST_INIT_NOT_DONE)
    {
 #if(EA_DEV_ERROR_DETECT != FALSE)
        /* Report error to DET */
        (void)Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, ApiId_u8, EA_E_NOT_INITIALIZED);
 #else
        /* cast of unused parameter for removing MISRA warning */
        (void)ApiId_u8;
 #endif

        stRetLoc_en = E_NOT_OK;
    }

    return stRetLoc_en;
}

/**
 *********************************************************************
 * Ea_Rb_CheckBlkNr()
 *
 * \param   ApiId_u8        : ID of API service in which error is detected
 * \param   Ea_ModuleIdx_u8: Ea module index
 * \return  status of check
 * \retval  E_OK    : status OK
 * \retval  E_NOT_OK: status not OK
 * \seealso
 * \usedresources
 *********************************************************************
 */
Std_ReturnType Ea_Rb_CheckBlkNr(uint8 ApiId_u8, uint16 BlockNumber_u16)
{
    Std_ReturnType stRetLoc_en = E_OK;

    /* Verify user length */
    if(BlockNumber_u16 > (EA_NUM_BLOCKS-1u))
    {
 #if(EA_DEV_ERROR_DETECT != FALSE)
        /* Report error to DET */
        (void)Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, ApiId_u8, EA_E_INVALID_BLOCK_NO);
 #else
        /* cast of unused parameter for removing MISRA warning */
        (void)ApiId_u8;
 #endif

        stRetLoc_en = E_NOT_OK;
    }

    return stRetLoc_en;
}

/**
 *********************************************************************
 * Ea_Rb_CheckMigrationErr()
 *
 * \param   ApiId_u8:   ID of API service in which error is detected
 * \param   ErrTyp_u8:  ID of Error type
 * \return
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_Rb_CheckMigrationErr(uint8 ApiId_u8, uint8 ErrTyp_u8)
{
 #if(EA_DEV_ERROR_DETECT != FALSE)
   /* Report error to DET about unsuccessful migration */
   (void)Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, ApiId_u8, ErrTyp_u8);
 #else
   (void)ApiId_u8;
 #endif
	
	#if(EA_RB_ACT_UNKNOWN_BLOCK_MIG != TRUE)
		Ea_Rb_MigrationStaus_u8 = EA_RB_MIGRATION_ERROR;
	#endif
	
	
    /* Callback function from user for the error handling */
    if(Ea_Prv_Common_cst.Ea_Rb_ErrorHandling_CallBack_pfct != NULL_PTR)
    {
        (*Ea_Prv_Common_cst.Ea_Rb_ErrorHandling_CallBack_pfct)((uint8)ErrTyp_u8);
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

