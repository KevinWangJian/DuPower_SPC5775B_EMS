

/*****************************************************************************************
 * Header Includes *
 *****************************************************************************************/
#include "BswM.h"
#include "BswM_Prv.h"

#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*****************************************************************************************
 * Definition of Global Functions *
 *****************************************************************************************/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name	: 	void BswM_Init( void )
* Description	: 	Initializes the BSW Mode Manager.
* Parameter  	: 	None
* Return value	: 	None
* Remarks		:
*****************************************************************************************/
FUNC (void, BSWM_CODE) BswM_Init
(
	P2CONST(BswM_ConfigType,AUTOMATIC,BSWM_APPL_CONST) ConfigPtr
)
{
    /* Declaration of local variables */
#if (defined(BSWM_NO_OF_AC_IPDUGROUPSWITCH) && (BSWM_NO_OF_AC_IPDUGROUPSWITCH > 0 ))
    VAR(uint8,AUTOMATIC)index_u8 = 0;
#endif /* ( BSWM_NO_OF_AC_IPDUGROUPSWITCH ) */
    VAR(uint8,AUTOMATIC) cntrLoop_u8 = 0;
    VAR(boolean,AUTOMATIC) isValidConfigPtr_b = FALSE;

    /* Check for NULL_PTR on the function parameter ConfigPtr */
    if(NULL_PTR == ConfigPtr)
    {
#if(BSWM_DEV_ERROR_DETECT != FALSE)
        Det_ReportError(BSWM_MODULE_ID,BSWM_INSTANCE_ID,BSWM_INIT_API_ID,BSWM_E_NULL_POINTER);
#endif /* ( BSWM_DEV_ERROR_DETECT == TRUE ) */
    }
    else
    {
        /* Check to verify ConfigPtr is a valid Post-build configuration structure provided by BswM */
        for(cntrLoop_u8 = 0; cntrLoop_u8 < BSWM_NO_OF_CONFIGSETS; cntrLoop_u8++)
        {
            if(ConfigPtr == BswM_Configurations_capcst[cntrLoop_u8])
            {
                /* If a vaild match is found, update the flag and break the loop*/
                isValidConfigPtr_b = TRUE;
                break;
            }
        }

        if(FALSE != isValidConfigPtr_b)
        {
            if((BSWM_MODULE_ID == ConfigPtr->dataVersionInfo_st.moduleID)
                    && (BSWM_VENDOR_ID == ConfigPtr->dataVersionInfo_st.vendorID)
                    && (BSWM_SW_MAJOR_VERSION == ConfigPtr->dataVersionInfo_st.sw_major_version)
                    && (BSWM_SW_MINOR_VERSION == ConfigPtr->dataVersionInfo_st.sw_minor_version))
            {
                /* Pre-compile and Post-build Version info matches. Proceed with BswM initialisation */

                /* Copy the pointer to post build structure */
                BswM_Prv_adrSelectedConfig_pcst = ConfigPtr;

                /* Function call to copy the initial mode values from the constant post build structure */
                BswM_Prv_CopyModeInitValues();

                /* Function call to copy the initial rule states from the constant post build structure */
                BswM_Prv_CopyRuleInitSates();

                /* Update the BswM Initialised flag as TRUE to intimate other APIs of BswM that the module is intialised */
                BswM_Prv_isModuleInitialised_b = TRUE;

#if (defined(BSWM_NO_OF_AC_IPDUGROUPSWITCH) && (BSWM_NO_OF_AC_IPDUGROUPSWITCH > 0 ))

                /* Initialize all PduGroupSwitch action global variables of the BSW Mode Manager */
                BswM_PduGrpSwt_b = FALSE;

                /*Initialize all PduGroupSwitch Vectors to all zeros */
                for (index_u8 = 0; index_u8 < (sizeof(BswM_IPduGrpVctr_ReinitTrue_au8)/sizeof(Com_IpduGroupVector)); index_u8++)
                {
                    BswM_IPduGrpVctr_ReinitTrue_au8[index_u8] = (uint8)0;
                }
                for (index_u8 = 0; index_u8 < (sizeof(BswM_IPduGrpVctr_ReinitAll_au8)/sizeof(Com_IpduGroupVector)); index_u8++)
                {
                    BswM_IPduGrpVctr_ReinitAll_au8[index_u8] = (uint8)0;
                }

#endif /* ( BSWM_NO_OF_AC_IPDUGROUPSWITCH ) */


            }
            else
            {
                /* Pre-compile and post-build version info are not matching. Intimate with a callout and skip BswM Initialisation*/
                BswM_Appl_IncompatibleGenerator();
            }
        }
        else
        {
            /* The ConfigPtr is invalid and return without BswM initialization. Report error if DET is enabled */
#if(BSWM_DEV_ERROR_DETECT != FALSE)
            Det_ReportError(BSWM_MODULE_ID,BSWM_INSTANCE_ID,BSWM_INIT_API_ID,BSWM_E_PARAM_CONFIG);
#endif /* ( BSWM_DEV_ERROR_DETECT == TRUE ) */
        }

    }
	return;
}


/*****************************************************************************************
* Function name	: 	void BswM_Deinit( void )
* Description	: 	Deinitializes the BSW Mode Manager.
* Parameter  	: 	None
* Return value	: 	None
* Remarks		: 	After execution of this routine no mode processing shall
*          			be performed by BswM even if any mode requests
*          			are made or the BswM main function is called.
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Deinit
(
	void
)
{
    /* Update the module initialised flag as FALSE to stop further mode processing by BswM */
    BswM_Prv_isModuleInitialised_b = FALSE;
    return;
}


/***********************************************************************************
 Function name  :   void BswM_GetVersionInfo( Std_VersionInfoType* versionInfo)
 Description    :   Returns the version information of this module
 Parameter in   :   None
 Parameter out  :   versioninfo
 return         :   None
 ************************************************************************************/
#ifdef BSWM_VERSIONINFO_API
#if(BSWM_VERSIONINFO_API != FALSE)

FUNC(void, BSWM_CODE) BswM_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, BSWM_APPL_DATA) VersionInfo
)
{
    if ( VersionInfo == NULL_PTR)
    {
#if (BSWM_DEV_ERROR_DETECT != FALSE)
        /*DET if the passed parameter is a NULL pointer */
        (void)Det_ReportError( BSWM_MODULE_ID, BSWM_INSTANCE_ID, BSWM_GETVERINFO_API_ID, BSWM_E_NULL_POINTER );
#endif /* ( BSWM_DEV_ERROR_DETECT == TRUE ) */
    }
    else
    {
        /* Copy the version info to the address provided by the valid pointer */
        VersionInfo->vendorID       =   BSWM_VENDOR_ID;
        VersionInfo->moduleID       =   BSWM_MODULE_ID;
        VersionInfo->sw_major_version   =   BSWM_SW_MAJOR_VERSION;
        VersionInfo->sw_minor_version   =   BSWM_SW_MINOR_VERSION;
        VersionInfo->sw_patch_version   =   BSWM_SW_PATCH_VERSION;
    }
	return;
}

#endif /* ( BSWM_VERSIONINFO_API != FALSE ) */
#endif /*  BSWM_VERSIONINFO_API  */

/*****************************************************************************************
* Function name :
* Description   :
* Parameter     :
* Return value  :
* Remarks       :
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_MainFunction
(
   void
)
{

    if(FALSE == BswM_Prv_isModuleInitialised_b)
    {
        /*BswM is not initialised, return without any action*/
    }
    else
    {
        /* Module initialised proceed with processing of rules associated with deferred request */
        if(BSWM_PRV_ISNOREQSTINPROGRESS)
        {
            /* Update the Deferred Request in progress flag, So no mode request interrups the current execution */
            BswM_Prv_flgDeferredReqstProgress_b = TRUE;

            BswM_Prv_ProcessDeferredReqst();

            /* Process requests that interrupted the processing of the previous mode request */
            if (FALSE != BswM_Prv_isReqstDelayed_b)
            {
                BswM_Prv_ProcessDelayedReqst();
            }

            BswM_Prv_flgDeferredReqstProgress_b = FALSE;

        }
        else
        {
            /* Delay the deferred request processing */
            BswM_Prv_flgDelayDeferredReqst_b = TRUE;

        }

    }

	return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/**********************************************************************************************************************
 *
 **********************************************************************************************************************/
