

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "TcpIp.h"
#include "Det.h"

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
static FUNC( void, SOAD_CODE ) SoAd_ReleaseIpAddrAssignmentDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo );
#endif /* (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ************************************************************************************************************************
 * \Function Name : SoAd_ReleaseIpAddrAssignment()
 *
 * \Function description
 *  By this API service the local IP address assignment which shall be released for the socket connection specified by
 *  SoConIdx.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index specifying the socket connection for which the IP address shall be released
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
 ************************************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_ReleaseIpAddrAssignment( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId )
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
    SoAd_ReleaseIpAddrAssignmentDetChk(SoConId);

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
        lFunctionRetVal_u8 = TcpIp_ReleaseIpAddrAssignment(lSoAdStaticSoConGrpConfig_cpst->soConGrpLocalAddressIdx_u8 );
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
#else
    (void)SoConId;

    return(E_NOT_OK);
#endif /* SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF */
}


#if ( (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_ReleaseIpAddrAssignmentDetChk()
 *
 * \function description
 * This function is called from SoAd_ReleaseIpAddrAssignment to handle the DET error for function arguments.
 * It covers SWS_SoAd_00618 & SWS_SoAd_00619 requirements
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection for which the IP address shall be released
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_ReleaseIpAddrAssignmentDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_RELEASE_IPADDR_ASSIGNMENT_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( (SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ), SOAD_RELEASE_IPADDR_ASSIGNMENT_API_ID, SOAD_E_INV_ARG )

}
#endif /* (SOAD_IPADDR_ASSIGNMENT_ENABLED != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
