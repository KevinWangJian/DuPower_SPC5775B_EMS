

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
static FUNC( void, SOAD_CODE ) SoAd_GetRemoteAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                   SoConId_uo,\
                                                         P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 *************************************************************************************************************************
 * \Function Name : SoAd_GetRemoteAddr()
 *
 * \Function description
 *  Retrieves the remote address (IP address and port) actually used for the SoAd socket connection specified by SoConId.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - Socket connection index representing the SoAd socket connection for which the actually specified
 *                    remote address shall be obtained.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):
 * \param   TcpIp_SockAddrType*
 * \arg     IpAddrPtr - Pointer to a struct where the retrieved remote address (IP address and port) is stored.
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK: The request was successful
 *          E_NOT_OK: The request was not successful
 *
 *
 ************************************************************************************************************************
 */
/* This function shall be called from upper layer of SoAd, if it receives a pdu via SoAd_Rxindication() and it is
 * interested to know from which remote node the message is received. Then upper layer shall call the below function */

FUNC( Std_ReturnType, SOAD_CODE ) SoAd_GetRemoteAddr( VAR( SoAd_SoConIdType, AUTOMATIC )                 SoConId ,\
                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  IpAddrPtr )
{
    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* variable to store the dynamic socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_GetRemoteAddrDetChk(SoConId, IpAddrPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the return value with default E_NOT_OK and other local variables */
        /* Get the index of the dynamic soc table */
        lIdxDynSocket_uo            = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].SoAd_Prv_idxDynSocTable_puo);

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00666] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** SoAd_GetRemoteAddr() shall immediately return E_NOT_OK if the remote address of the socket connection *******/
        /**                 specified by parameter SoConId is not set.                                               ****/
        /****************************************************************************************************************/

        /* If dynamic socket is valid means , we can assume that remote address has been updated for this SoAd either
         * with configed Remote address or from appropriate UL */
        if( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo)
        {
            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00664] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /* At SoAd_GetRemoteAddr() SoAd shall retrieve the remote address (IP address and port) actually used for *******/
            /*************************the socket connection specified by parameter SoConId. *********************************/
            /****************************************************************************************************************/

            /* copy the global array index address to local pointer for further processing */
            lSoAdDyncSocConfig_pst      =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_COPY_FROM_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_SOCK_ADDR(lSoAdDyncSocConfig_pst, IpAddrPtr)

            /* Return value shall be set to E_OK */
            lFunctionRetVal_u8  = E_OK;
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ************************************************************************************************************************
 * \Function Name : SoAd_GetRemoteAddrDetChk()
 *
 * \function description
 * This function is called from SoAd_GetRemoteAddr to handle the DET error for function arguments.
 * It covers SWS_SoAd_00659, SWS_SoAd_00660 & SWS_SoAd_00698 requirements
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index representing the SoAd socket connection for which the actually
 *                       specified remote address shall be obtained.
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddr_cpst - Pointer to a struct where the retrieved remote address (IP address and port) is stored.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_GetRemoteAddrDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )                       SoConId_uo,\
                                                         P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_GET_REMOTE_ADDR_API_ID, SOAD_E_NOTINIT )

    /* Check whether IpAddrPtr pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == RemoteAddr_cpst ), SOAD_GET_REMOTE_ADDR_API_ID, SOAD_E_PARAM_POINTER )

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00698] ****************************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /**  SoAd_GetRemoteAddr() shall refuse the request if the domain set in IpAddrPtr does not match the      *******/
    /** TcpIp_DomainType of the local address related to the socket connection identified by SoConId and return   ***/
    /** E_NOT_OK. If development error detection is enabled, the service SoAd_GetRemoteAddr() shall also raise    ***/
    /**                             the development error SOAD_E_INV_ARG                                          ***/
    /****************************************************************************************************************/

    /* Check whether SoConId is valid or not */
    SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ) || \
                             ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].domain_en != RemoteAddr_cpst->domain) ), \
                                SOAD_GET_REMOTE_ADDR_API_ID, SOAD_E_INV_ARG )
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
