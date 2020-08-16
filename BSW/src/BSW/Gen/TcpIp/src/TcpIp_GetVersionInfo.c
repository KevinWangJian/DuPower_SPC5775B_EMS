

#include "TcpIp.h"

#ifdef TCPIP_CONFIGURED

#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/* TcpIp_GetVersionInfo() - TReturns the version information.                                                       */
/*                                                                                                                  */
/* Out Parameters :                                                                                                 */
/*      versioninfo     - Pointer to where to store the version information of this module.                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#if(TCPIP_VERSION_INFO_API == STD_ON)
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( void, TCPIP_CODE ) TcpIp_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, AUTOMATIC )   versioninfo )
{
    /* Report DET if PhysAddrPtr is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == versioninfo ), TCPIP_E_GET_VERSIONINFO_API_ID, TCPIP_E_NULL_PTR )

    versioninfo->vendorID            = TCPIP_VENDOR_ID;
    versioninfo->moduleID            = TCPIP_MODULE_ID;
    versioninfo->sw_major_version    = TCPIP_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version    = TCPIP_SW_MINOR_VERSION;
    versioninfo->sw_patch_version    = TCPIP_SW_PATCH_VERSION;

}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_VERSION_INFO_API */

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/
