

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

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_GetLocalAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                   SoConId_uo ,\
                                                        P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  LocalAddrPtr_cpst );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ********************************************************************************************************************************************
 * \Function Name : SoAd_GetLocalAddr()
 *
 * \Function description
 *  Obtains the local address (IP address and port) actually used for the SoAd socket connection specified by SoConIdx,
 *   the netmask and default router.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index representing the SoAd socket connection for which the actual local IP address
 *                          shall be obtained.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):
 * \param   TcpIp_SockAddrType*
 * \arg     LocalAddrPtr - Pointer to struct where the IP address of the default router (gateway) is stored
 *                           (struct member port is not used and of arbitrary value).
 * \param   uint8*
 * \arg     NetmaskPtr - Pointer to memory where Network mask of IPv4 address or address prefix of IPv6 address in CIDR Notation is stored.
 * \param   TcpIp_SockAddrType*
 * \arg     DefaultRouterPtr - Pointer to a struct where the local address (IP address and port) is stored.
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK: The request has been accepted
 *          E_NOT_OK: The request has not been accepted
 *
 *
 *************************************************************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_GetLocalAddr( VAR( SoAd_SoConIdType, AUTOMATIC )                 SoConId ,\
                                                     P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  LocalAddrPtr,\
                                                     P2VAR( uint8, AUTOMATIC, AUTOMATIC )               NetmaskPtr,\
                                                     P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  DefaultRouterPtr)
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lFunctionRetVal_u8;

    /* Variable to store the return value of the internal functions */
    VAR(Std_ReturnType, AUTOMATIC)                                      lRetVal_u8;

    /* variable to store the dynamic socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

	/* Variable to store the port for dynamic socket */
    VAR(uint16, AUTOMATIC)                                  			lDyncSocPort_u16;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_GetLocalAddrDetChk(SoConId, (const TcpIp_SockAddrType*)LocalAddrPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables that are declared above */
        /* Get static socket Group configuration pointers */
        lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].soConGrpId_uo]);

        /* call tcp ip layer to get the ip address */
        lRetVal_u8 = TcpIp_GetIpAddr( lSoAdStaticSoConGrpConfig_cpst->soConGrpLocalAddressIdx_u8, LocalAddrPtr, NetmaskPtr, DefaultRouterPtr);

        /* Condition check: The function call to TcpIp layer should be successful */
        if( E_OK == lRetVal_u8 )
        {
            /* Initialize the return value with default E_NOT_OK and other local variables */
            /* Get the index of the dynamic soc table */
            lIdxDynSocket_uo            = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].SoAd_Prv_idxDynSocTable_puo);

			lDyncSocPort_u16 = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].soConDynLocalPort_u16;

            /* Condition check:
             * 1. Dynamic socket index is valid
             * 2. Configured local port should be valid
             */

            /* we can assume that remote address has been updated for this SoAd either
             * with configed Remote address or from appropriate UL */
            if( ( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo ) && \
                ( SOAD_DEFAULT_PORT != lDyncSocPort_u16 ) )
            {
                /* Load the port value from the configured value*/
				/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
				SOAD_SET_PORT_TO_SOCK_ADDR(LocalAddrPtr, lDyncSocPort_u16)

                lFunctionRetVal_u8 = E_OK;
            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ********************************************************************************************************************************
 * \Function Name : SoAd_GetLocalAddrDetChk()
 *
 * \function description
 * This function is called from SoAd_GetLocalAddr to handle the DET error for function arguments.
 * It covers SWS_SoAd_00621 & SWS_SoAd_00620 requirements
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index representing the SoAd socket connection for which the actual local IP address
 *                          shall be obtained.
 * \param   const TcpIp_SockAddrType*
 * \arg     LocalAddrPtr_cpst - Pointer to struct where the IP address of the default router (gateway) is stored
 *                           (struct member port is not used and of arbitrary value).
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 *********************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_GetLocalAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                   SoConId_uo ,\
                                                        P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  LocalAddrPtr_cpst )
{
    /* LocalAddrPtr_cpst can store the local address. */
    VAR(boolean, AUTOMATIC)  lCanStoreLocalAddr_b;

    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_GET_LOCAL_ADDR_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ), SOAD_GET_LOCAL_ADDR_API_ID, SOAD_E_INV_ARG )

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == LocalAddrPtr_cpst ), SOAD_GET_LOCAL_ADDR_API_ID, SOAD_E_PARAM_POINTER )

	if( SoAd_DetErrFlag_u8 == E_NOT_OK )
	{
		/* Check whether LocalAddrPtr_cpst can store the local address */
		lCanStoreLocalAddr_b = SOAD_SOCK_ADDR_CAN_STORE_CON_ADDR(LocalAddrPtr_cpst, SoConId_uo);
		SOAD_DET_REPORT_ERROR( !lCanStoreLocalAddr_b, SOAD_GET_LOCAL_ADDR_API_ID, SOAD_E_INV_ARG )
	}
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
