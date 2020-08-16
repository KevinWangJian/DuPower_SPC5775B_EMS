

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/**************************************************************************************************
 Function name    : Com_GetConfigurationId
 Syntax           : uint32 Com_GetConfigurationId(void)
 Description      : Service provides the configuration ID
 Parameter        : void
 Return value     : Configuration ID
**************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint32, COM_CODE) Com_GetConfigurationId(void)
{
    /* Start: Det */

    COM_REPORT_ERROR2((Com_Uninit_Flag == COM_UNINIT), COMServiceId_GetConfigurationId, COM_E_UNINIT)

    /* End: Det */

    return COM_GET_CONFIGURATION_ID;  /* Provides the unique identifier of the configuration */
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

