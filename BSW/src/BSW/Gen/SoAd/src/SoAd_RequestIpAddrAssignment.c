

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
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

#if ( (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
static FUNC( void, SOAD_CODE ) SoAd_RequestIpAddrAssignmentDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo, \
                                                                   VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )  Type_en , \
                                                                   P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST )  LocalIpAddr_cpst );
#endif /* (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ************************************************************************************************************************************************************
 * \Function Name : SoAd_RequestIpAddrAssignment()
 *
 * \Function description
 *  By this API service the local IP address assignment which shall be used for the socket connection specified by
 *  SoConIdx is initiated.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index specifying the socket connection for which the IP address shall be set.
 *
 * \param   TcpIp_IpAddrAssignmentType
 * \arg     Type - type of IP address assignment which shall be initiated.
 *
 * \param   const TcpIp_SockAddrType*
 * \arg     LocalIpAddrPtr - pointer to structure containing the IP address which shall be assigned to the
 *          EthIf controller indirectly specified via SoConIdx.
 *           Note:This parameter is only use in case parameter Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC.
 *
 * \param   uint8
 * \arg     Netmask - Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation
 *           Note: This parameter is only used in case the parameter Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC.
 *
 * \param   const TcpIp_SockAddrType*
 * \arg     DefaultRouterPtr - Pointer to structure containing the IP address of the default router (gateway)
 *          which shall be assigned..
 *           Note: This parameter is only used in case the parameter Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC,
 *                 can be set to NULL_PTR otherwise.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK: The request has been accepted
 *          E_NOT_OK: The request has not been accepted
 *
 *
 *
 *****************************************************************************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_RequestIpAddrAssignment( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId , \
                                                                VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )  Type , \
                                                                P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST )  LocalIpAddrPtr, \
                                                                VAR(uint8, AUTOMATIC) Netmask, \
                                                                P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST ) DefaultRouterPtr)
{
#if (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF)
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)          lFunctionRetVal_u8;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_RequestIpAddrAssignmentDetChk(SoConId, Type, LocalIpAddrPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* Get static socket Group configuration pointers */
        lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].soConGrpId_uo]);

        /* Call the TcpIp module function with local address index associated with the given socket Id */
        lFunctionRetVal_u8 = TcpIp_RequestIpAddrAssignment(lSoAdStaticSoConGrpConfig_cpst->soConGrpLocalAddressIdx_u8, Type, LocalIpAddrPtr, Netmask, DefaultRouterPtr );
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);

#else
    (void)SoConId;
    (void)Type;
    (void)LocalIpAddrPtr;

    return(E_NOT_OK);
#endif /* SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF */
}

#if ( (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_RequestIpAddrAssignmentDetChk()
 *
 * \function description
 * This function is called from SoAd_RequestIpAddrAssignment to handle the DET error for function arguments.
 * It covers SWS_SoAd_00613 & SWS_SoAd_00617 requirements
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection for which the IP address shall be set.
 *
 * \param   TcpIp_IpAddrAssignmentType
 * \arg     Type_en - type of IP address assignment which shall be initiated.
 *
 * \param   const TcpIp_SockAddrType*
 * \arg     LocalIpAddrPtr_cpst - pointer to structure containing the IP address which shall be assigned to the
 *          EthIf controller indirectly specified via SoConIdx.
 *           Note:This parameter is only use in case parameter Type is set to TCPIP_IPADDR_ASSIGNMENT_STATIC.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***********************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_RequestIpAddrAssignmentDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo, \
                                                                   VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )  Type_en , \
                                                                   P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST )  LocalIpAddr_cpst )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_REQUEST_IPADDR_ASSIGNMENT_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( (SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ), SOAD_REQUEST_IPADDR_ASSIGNMENT_API_ID, SOAD_E_INV_ARG )

    /* Check whether LocalIpAddr and connection domain are equal when assignment type is TCPIP_IPADDR_ASSIGNMENT_STATIC */
    SOAD_DET_REPORT_ERROR( ( (Type_en == TCPIP_IPADDR_ASSIGNMENT_STATIC) && ( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].domain_en) != LocalIpAddr_cpst->domain) ), SOAD_REQUEST_IPADDR_ASSIGNMENT_API_ID, SOAD_E_INV_ARG )
}
#endif /* (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
