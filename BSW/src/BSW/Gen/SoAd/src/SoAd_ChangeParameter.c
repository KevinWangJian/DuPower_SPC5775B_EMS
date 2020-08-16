

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

#if (SOAD_CHANGEPARAMETER_ENABLED != STD_OFF)
LOCAL_INLINE FUNC( Std_ReturnType, SOAD_CODE ) SoAd_ConvertParamIdToTcpIpParamIdType( \
                                                    VAR(SoAd_ParamIdType, AUTOMATIC)    ParameterId_u8, \
                                                    P2VAR(TcpIp_ParamIdType, AUTOMATIC, AUTOMATIC)   TcpIpParameterId_pen);

#if (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF)
static FUNC( void, SOAD_CODE ) SoAd_ChangeParameterDetChk( VAR(SoAd_SoConIdType, AUTOMATIC) SoConId_uo,
                                                           VAR(SoAd_ParamIdType, AUTOMATIC) ParameterId_u8 );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#endif /* SOAD_CHANGEPARAMETER_ENABLED != STD_OFF */

/**
 **********************************************************************************************************************
 * \Function Name : SoAd_ChangeParameter()
 *
 * \Function description
 * This API can be requested to control the connection parameter either by SoAd or TcpIp.
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index specifying the socket connection which shall be closed
 * \param   SoAd_ParamIdType
 * \arg     ParameterId - Parameter which is requested by UL to get or set the values
 * \param   uint8*
 * \arg     ParameterValuePtr - Pointer to an address which contains the value for the corresponding ParameterId in
 *                              case of set request.
 *                              Else, this address will be filled by TcpIp module if its a Get request.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 *  Return value:
 * \retval  E_OK :      The request was successful
 *          E_NOT_OK:   The request was not successful
 *
 **********************************************************************************************************************
 */
/* MR12 RULE 8.13 VIOLATION: A pointer should point to a const-qualified type whenever possible. */
FUNC(Std_ReturnType, SOAD_CODE) SoAd_ChangeParameter( VAR(SoAd_SoConIdType, AUTOMATIC)   SoConId,
                                                      VAR(SoAd_ParamIdType, AUTOMATIC)   ParameterId,
                                                      P2VAR(uint8, AUTOMATIC, AUTOMATIC) ParameterValuePtr )
{
#if (SOAD_CHANGEPARAMETER_ENABLED != STD_OFF)

    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lFunctionRetVal_u8;

    /* Variable to store the internal function return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lRetVal_u8;

    /* Index to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* Variable to store the TcpIp socket Id */
    VAR(TcpIp_SocketIdType, AUTOMATIC)                                  lTcpIpSocketId_uo;

    VAR(TcpIp_ParamIdType, AUTOMATIC)                                   lTcpIpParameterId_en;

     /* Initialize the funtion return variable to E_NOT_OK */
     lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_ChangeParameterDetChk(SoConId, ParameterId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialization of Variables*/
        lTcpIpSocketId_uo            = (TcpIp_SocketIdType)0xFFFF;

        /* Get static socket configuration pointers */
        lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId]);

        /* Get the "dynamic socket connection index" from Static socket table */
        lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

        /* Condition check: the dynamic socket id should be valid  */
        if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
        {
            /*Check if the SoAd socket is in the right state*/
            if( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en >= SOAD_SOCON_TCPIP_ALLOCATED )
            {
                /* Get the TcpIp socket Id available in the dynamic table */
                lTcpIpSocketId_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo;

                /*Check if the TcpIp socket is valid, then call the TcpIp_ChangeParameter function*/
                if( lTcpIpSocketId_uo < SOAD_NUM_TCPIP_SOCKETS )
                {
                    lRetVal_u8 = SoAd_ConvertParamIdToTcpIpParamIdType(ParameterId, &lTcpIpParameterId_en);

                    lFunctionRetVal_u8 =  ( E_OK == lRetVal_u8 ) ? \
                            TcpIp_ChangeParameter(lTcpIpSocketId_uo,lTcpIpParameterId_en,ParameterValuePtr): \
                            E_NOT_OK;
                }
            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);

#else
    (void)SoConId;
    (void)ParameterId;
    (void)ParameterValuePtr;

    return(E_NOT_OK);

#endif /* SOAD_CHANGEPARAMETER_ENABLED != STD_OFF */
}

#if (SOAD_CHANGEPARAMETER_ENABLED != STD_OFF)
/**
 **************************************************************************************************************
 * \Function Name : SoAd_ConvertParamIdToTcpIpParamIdType()
 *
 * \function description
 * This function is called from SoAd_ChangeParameter to handle the DET error for function arguments.
 *
 * Parameters (in) :
 * \param   SoAd_ParamIdType
 * \arg     ParameterId_u8 - SoAd Parameter Id
 *
 * Parameters (inout): None
 * \param   TcpIp_ParamIdType
 * \arg     TcpIpParameterId_pen - TcpIp Parameter Id pointer in which TcpIp Param id would be copied
 *
 * Parameters (out):   None
 *
 * Return value:       None
 *
 *************************************************************************************************************
 */
LOCAL_INLINE FUNC( Std_ReturnType, SOAD_CODE ) SoAd_ConvertParamIdToTcpIpParamIdType( \
                                                    VAR(SoAd_ParamIdType, AUTOMATIC)    ParameterId_u8, \
                                                    P2VAR(TcpIp_ParamIdType, AUTOMATIC, AUTOMATIC)   TcpIpParameterId_pen)
{
    VAR(Std_ReturnType, AUTOMATIC)   lRetVal_u8;

    /* initialization of return variable to E_NOT_OK */
    lRetVal_u8 = E_OK;

    switch(ParameterId_u8)
    {
        case 0x00U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_RXWND_MAX;
            break;
        }

        case 0x01U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_FRAMEPRIO;
            break;
        }

        case 0x02U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_NAGLE;
            break;
        }

        case 0x03U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_KEEPALIVE;
            break;
        }

        case 0x04U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TTL;
            break;
        }

        case 0x05U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_KEEPALIVE_TIME;
            break;
        }

        case 0x06U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX;
            break;
        }

        case 0x07U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL;
            break;
        }

        case 0x80U:
        {
            (*TcpIpParameterId_pen) = TCPIP_PARAMID_VENDOR_SPECIFIC;
            break;
        }

        default:
            lRetVal_u8 = E_NOT_OK;
            break;
    }

    return (lRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 **************************************************************************************************************
 * \Function Name : SoAd_ChangeParameterDetChk()
 *
 * \function description
 * This function is called from SoAd_ChangeParameter to handle the DET error for function arguments.
 *
 * Parameters (in) :
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection which shall be closed
 * \param   SoAd_ParamIdType
 * \arg     ParameterId_u8 - Parameter which is requested by UL to get or set the values
 *
 * Parameters (inout): None
 *
 * Parameters (out):   None
 *
 * Return value:       None
 *
 *************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_ChangeParameterDetChk( VAR(SoAd_SoConIdType, AUTOMATIC) SoConId_uo,
                                                           VAR(SoAd_ParamIdType, AUTOMATIC) ParameterId_u8 )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
	 * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
	 * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
	 * for the same function.
	 */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_CHANGE_PARAMETER_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId & ParameterId are valid or not */
    SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ) || \
                             ( (SoAd_ParamIdType)TCPIP_PARAMID_TTL < ParameterId_u8 ) ), \
                            SOAD_CHANGE_PARAMETER_API_ID, SOAD_E_INV_ARG )

}
#endif /* (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF) */
#endif /* (SOAD_CHANGEPARAMETER_ENABLED != STD_OFF) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
