

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "SoAd.h"

#ifdef SOAD_CONFIGURED
#include "Det.h"

#include "SoAd_Prv.h"
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

#if ((SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF))
static FUNC( void, SOAD_CODE ) SoAd_DisableRoutingDetChk( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo );
#endif /* (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF) */

/**
 **********************************************************************************************************************
 * \Function Name : SoAd_DisableRouting()
 *
 * \Function description
 *  Disables routing of a group of PDUs in the SoAd related to the RoutingGroup specified by parameter id.
 *
 *  Parameters (in):
 * \param   SoAd_RoutingGroupIdType
 * \arg     id - Id of the soad routing group, for which the routing should be disabled
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
 **********************************************************************************************************************
 */
/* As the message transmission/reception to/from a remote node shall be stopped by two switches.
 * one is, related socket can be made to OFFLINE.
 * Second is, routing group linked with that pdu route dest can be disabled by upper layer.
 * This function allows to disable the routing group, which can stop tx and rx pdus linked with this routing group  even though its socket is ONLINE*/
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_DisableRouting( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  id )
{
#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    /* Local pointer to store the SoAd_RoutingGroupSoConStructMap_tst array for given index*/
    P2CONST(SoAd_RoutingGroupSoConStructMap_tst, AUTOMATIC, AUTOMATIC)  lSoAdRoutingGroupSoConStructMap_cpst;

    /* Variable to hold the return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lFunctionRetVal_u8;

    /* Loop through for NumofSocket Mapping to RG Id */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxSoCon_uo ;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_DisableRoutingDetChk(id);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables that are declared above */
        /* copy the global array address to local pointer for given index */
        lSoAdRoutingGroupSoConStructMap_cpst = &(SoAd_CurrConfig_cpst->SoAd_RoutingGroupSoConStructMap_cpst[id]);

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00721] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /*** For RoutingGroups that are referenced by a SoAdPduRouteDest that refers to a SocketConnectionGroup SoAd  ***/
        /*** shall maintain independent states for each SocketConnection that is part of the referenced               ***/
        /*** SocketConnectionGroup and handle them as if they were separate RoutingGroups.                            ***/
        /****************************************************************************************************************/

        /* Loop for each SoConId's whcih are mapped to given Routing Group Id */
        for(lIdxSoCon_uo = 0;
                lIdxSoCon_uo < lSoAdRoutingGroupSoConStructMap_cpst->numOfSoConIdMapped_uo;
                lIdxSoCon_uo++)
        {
            /* Disable the routing group by updating its value in Dynamic table,
             * Once the routing group is disabled, there shall be no Tx/Rx for the PDUs linked with this routing group */
            lSoAdRoutingGroupSoConStructMap_cpst->routingGrpSoConMap_pst[lIdxSoCon_uo].rg_status_b = FALSE;
            lFunctionRetVal_u8 = E_OK;
        }

    }/*End of If condition: Check SoAd Module should be Initialized */

    /* Return lFunctionRetVal_u8 */
    return(lFunctionRetVal_u8);
#else
    (void)id;
    return(E_NOT_OK);
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

}


#if ((SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF))
/**
 **********************************************************************************************************************
 * \Function Name : SoAd_DisableRoutingDetChk()
 *
 * \function description
 * This function is called from SoAd_DisableRouting to handle the DET error for function arguments.
 * It covers SWS_SoAd_00627 & SWS_SoAd_00626 requirements
 *
 *  Parameters (in):
 * \param   SoAd_RoutingGroupIdType
 * \arg     RgId_uo - Id of the soad routing group, for which the routing should be disabled
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 **********************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_DisableRoutingDetChk( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )  RgId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_DISABLE_ROUTING_API_ID, SOAD_E_NOTINIT )

    /* Check whether id is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noRoutingGrps_cuo <= RgId_uo ), SOAD_DISABLE_ROUTING_API_ID, SOAD_E_INV_ARG )

}
#endif /* (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && (SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
