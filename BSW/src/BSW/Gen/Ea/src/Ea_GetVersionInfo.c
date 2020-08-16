

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 4.0.2
 * \scope    INTERN
 **********************************************************************************************************************
 */

#include "Ea.h"
#if (EA_PRESENT == 1)
/*
 *********************************************************************
 * Includes
 *********************************************************************
 */

#if (EA_DEV_ERROR_DETECT != FALSE)
    #include "Det.h"
#endif
#include "Ea_Prv.h"

#define EA_START_SEC_CODE
#include "Ea_MemMap.h"
#if (EA_VERSION_INFO_API != FALSE)
/**
 *********************************************************************
 * Ea_GetVersionInfo(): Return version information
 *
 * This function returns general and SW version information
 *
 * \param   VersioninfoPtr: Pointer to where to store the version
 *                          information of this module.
 * \return  None
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
void Ea_GetVersionInfo(Std_VersionInfoType* VersioninfoPtr)
{
   if(VersioninfoPtr == NULL_PTR)
   {
#if(EA_DEV_ERROR_DETECT != FALSE)
       /* Report error to DET */
       (void)Det_ReportError(EA_MODULE_ID, EA_INSTANCE_ID, EA_SID_GETVERSIONINFO, EA_E_INCOMPATIBLE_VERSIONS);
/* EA_DEV_ERROR_DETECT == STD_ON */
#endif
   }
   else
   {
        VersioninfoPtr->vendorID            = EA_VENDOR_ID;
        VersioninfoPtr->moduleID            = EA_MODULE_ID;
        VersioninfoPtr->sw_major_version    = EA_SW_MAJOR_VERSION;
        VersioninfoPtr->sw_minor_version    = EA_SW_MINOR_VERSION;
        VersioninfoPtr->sw_patch_version    = EA_SW_PATCH_VERSION;
   }
}
/* EA_VERSION_INFO_API */
#endif
#define EA_STOP_SEC_CODE
#include "Ea_MemMap.h"
/* #if (EA_PRESENT == 1) */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

