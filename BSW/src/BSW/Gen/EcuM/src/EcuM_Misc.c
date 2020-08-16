

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/

#include "EcuM.h" /*BSW_HeaderInc_002*/



#include "EcuM_Cfg_SchM.h"

/*Extern module Headers*/
#if(ECUM_DEV_ERROR_DETECT == STD_ON)/*Det included when Det is enabled in EcuM*/
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif/*ECUM_DEV_ERROR_DETECT*/

/*EcuM Private headers*/
#include "EcuM_Prv.h"
/***********************************************************************************
 Function name	:   void EcuM_GetVersionInfo( Std_VersionInfoType* versioninfo)
 Description	:   Returns the version information of this module
 Parameter in	:   None
 Parameter out	:   versioninfo
 return			:	None
 ************************************************************************************/
#if(ECUM_VERSION_INFO_API	==	STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
FUNC( void, ECUM_CODE ) EcuM_GetVersionInfo ( P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo )
{

    /* Checking whether the pointer passed is a NULL pointer */
    if ( versioninfo == NULL_PTR )
    {
#if ( ECUM_DEV_ERROR_DETECT==STD_ON )
        /*DET if the passed parameter is a NULL pointer*/
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GETVERINFO_APIID, ECUM_E_NULL_POINTER );
#endif  /*ECUM_DEV_ERROR_DETECT*/
    }
    else
    {
        versioninfo->vendorID           =   ECUM_VENDOR_ID;
        versioninfo->moduleID           =   ECUM_MODULE_ID;
        versioninfo->sw_major_version   =   ECUM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version   =   ECUM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version   =   ECUM_SW_PATCH_VERSION;
    }

    return;
}


#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
#endif//ECUM_VERSION_INFO_API
