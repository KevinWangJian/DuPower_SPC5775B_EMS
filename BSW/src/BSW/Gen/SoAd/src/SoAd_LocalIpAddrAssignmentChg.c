

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "SoAd.h"
#include "SoAd_Cbk.h"

#ifdef SOAD_CONFIGURED
#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Prototype for Static functions: Start
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_LocalIpAddrAssignmentChgDetChk( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  IpAddrId_u8 );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_LocalIpAddrAssignmentChg()
 *
 * \Function description
 *  SoAd_LocalIpAssignmentChg() gets called by the TCP/IP stack if an IP address assignment changes.
 *
 *  Parameters (in):
 * \param   TcpIp_LocalAddrIdType
 * \arg     IpAddrId - IP address Identifier, representing an IP address specified in the TcpIp module configuration
 * \param   TcpIp_IpAddrStateType
 * \arg     State - state of IP address assignment
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 *
 ***********************************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_LocalIpAddrAssignmentChg( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  IpAddrId ,\
                                                       VAR( TcpIp_IpAddrStateType, AUTOMATIC )  State )
{
    /* Index for looping across static sockets*/
    VAR(SoAd_SoConIdType, AUTOMATIC)            lIdxSoCon_uo ;

    /* Index to store the localaddressId */
    VAR(TcpIp_LocalAddrIdType, AUTOMATIC)       lLocalAddressId_u8;

    /* Local pointer to store the static SoCon array one by one */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC) lSoAdStaticSocConfig_cpst;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_LocalIpAddrAssignmentChgDetChk(IpAddrId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* store the status of the local address Id in the table*/
        SoAd_LocalAddrIdx_State_aen[IpAddrId] = State ;

        /* loop through all the sockets for the processing */
        for (lIdxSoCon_uo=0; lIdxSoCon_uo<SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo; lIdxSoCon_uo++)
        {
            /* copy the static socket config array to local pointer for further processing */
            lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxSoCon_uo]);

            /* Get the local address Id of this socket connection */
            lLocalAddressId_u8 = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpLocalAddressIdx_u8 ;

             /* condition to check the local address Id belongs to this socket connection */
            if(lLocalAddressId_u8  == IpAddrId )
            {
                /* Condition check: mode change notification is enabled and call back should be  configured in upper layer */
                /*1 socket supports 1 upper layer. Multiple upper layers per socket is not supported.*/
                if( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].ipAddrAssgnChgNotify_b != FALSE )&& \
                    ( NULL_PTR != SoAd_CurrConfig_cpst->SoAd_LocalIpAddrAsgnChgCbk_cpst[lSoAdStaticSocConfig_cpst->idxLocalIpAddrChgCbk_u8].soAdLocalIpAddrAsgnChgCbk_pfn ) )
                {
                    /* call the upper layer to notify about Local Address assignment change */
                    SoAd_CurrConfig_cpst->SoAd_LocalIpAddrAsgnChgCbk_cpst[lSoAdStaticSocConfig_cpst->idxLocalIpAddrChgCbk_u8].soAdLocalIpAddrAsgnChgCbk_pfn(\
                                                                                    lSoAdStaticSocConfig_cpst->soConId_uo, State);
                }/* End for : Condition check for mode change notification is enabled*/

            }
        }/* for (lIdxSoCon_uo=0; lIdxSoCon_uo<SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo; lIdxSoCon_uo++) */
    }/*End of If condition: Check SoAd Module should be Initialized */
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_LocalIpAddrAssignmentChgDetChk()
 *
 * \function description
 * This function is called from SoAd_LocalIpAddrAssignmentChg to handle the DET error for function arguments.
 * It covers SWS_SoAd_00279 & SWS_SoAd_00280 requirements
 *
 *  Parameters (in):
 * \param   TcpIp_LocalAddrIdType
 * \arg     IpAddrId_u8 - IP address Identifier, representing an IP address specified in the TcpIp module configuration
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***********************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_LocalIpAddrAssignmentChgDetChk( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  IpAddrId_u8 )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_LOCAL_IPADDR_ASSIGNMENT_CHG_API_ID, SOAD_E_NOTINIT )

    /* Check whether IpAddrId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SOAD_MAX_TCPIP_LOCALADDRIDX <= IpAddrId_u8 ), SOAD_LOCAL_IPADDR_ASSIGNMENT_CHG_API_ID, SOAD_E_INV_ARG)

}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
