
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"
#include "EthIf_Prv.h"

#include "EthTrcv.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
/**
 ***************************************************************************************************
 * \module description
 * ETHIF034: Enables / disables the indexed controller
 * \par Service ID 0x03, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx   Index of the Ethernet controller within the context of the Ethernet Interface
 * \param CtrlMode   ETHCTRL_MODE_DOWN: disable the controller ETHCTRL_MODE_ACTIVE: enable the controller
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: controller mode could not be changed}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_SetControllerMode(   VAR( uint8,         AUTOMATIC )     CtrlIdx,
                                                                VAR( Eth_ModeType,  AUTOMATIC )     CtrlMode   )
{
    /* Local variables declaration */
    Std_ReturnType    lResult_en;

    /* Initialise local variables */
    lResult_en      = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_SETCONTROLLERMODE,    \
                                ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ),    \
                                    ETHIF_SID_ETHIF_SETCONTROLLERMODE,                                                  \
                                    ETHIF_E_INV_CTRL_IDX, E_NOT_OK)

    /* Store the request, which will be processed in the next main function */
    EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlReqMode_pa[CtrlIdx] = CtrlMode;

    /* Check if the reference of the EthIfCtrl is a transceiver */
    if(ETHIF_TRCV == (EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].TrcvSwtPortGrp_RefType_en ))
    {
        /* Clear the transceiver error flag for the EthIfCtrl */
        EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[CtrlIdx] = FALSE;
    }

    lResult_en = E_OK;

    return lResult_en;
}

/**
 ***************************************************************************************************
 * \module description
 *  Initialises the indexed controller
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx  Index of the Ethernet controller within the context of the Ethernet Interface
 *
 * \return  Std_ReturnType { E_OK: success; E_NOT_OK: controller could not be initialised }
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_ControllerInit(  VAR( uint8, AUTOMATIC )     CtrlIdx )
{
    /* Local variables declaration */
    Std_ReturnType    lResult_en;
    uint8             lEthCtrlIdx_u8;

    /* Initialise local variables */
    lResult_en      = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_PRV_CONTROLLERINIT,    \
                                ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* If requested EthCtrl is already in ETHIF_ETHCTRL_STATE_INIT or ETHIF_ETHCTRL_STATE_ACTIVE no need to call driver API. Return with E_OK */
    lResult_en = E_OK;

    /* Get EthCtrlIdx configured for the requested EthIfCtrl  */
   lEthCtrlIdx_u8 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    if (ETHIF_ETHCTRLSTATE_UNINIT == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] ) )
    {
        /* From AUTOSAR 4.2.2 the controllers are initialized by Eth_Init */
        lResult_en = E_OK;

        /* If driver API returns E_OK set EthCtrl state in EthIf to ETHIF_ETHCTRLSTATE_INIT */
        if( E_OK == lResult_en )
        {
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] ) = ETHIF_ETHCTRLSTATE_INIT ;
        }
    }

    return lResult_en;
}


#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )

/**
 ***************************************************************************************************
 * \module description
 * Initialises the indexed transceiver
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param TrcvIdx    Index of the physical transceiver
 *
 *
 * \return  Std_ReturnType {E_OK: success;E_NOT_OK: transceiver could not be initialized}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_TransceiverInit( VAR( uint8, AUTOMATIC )     TrcvIdx )

{
    /* Local variables declaration */
    Std_ReturnType    lResult_en;

    /* Initialise local variables */
    lResult_en = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_PRV_TRANSCEIVERINIT,  \
                                    ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: TrcvIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( TrcvIdx + 1 )  > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfTrcv_cu8 ),       \
                                  ETHIF_SID_ETHIF_PRV_TRANSCEIVERINIT,                                                 \
                                  ETHIF_E_INV_TRCV_IDX, E_NOT_OK )

    /* Check if transceiver initialization is already called */
    if ( 0 != ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->TrcvInitFlg_pa[TrcvIdx] ) )
    {
        return E_OK;
    }
    else
    {
        /* From AUTOSAR 4.2.2 the Ethernet transceivers are initialized by Eth_Init */
        lResult_en = E_OK;

        if( E_OK == lResult_en )
        {   /* Set transceiver initialization flag once lower layer function is successfully called */
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->TrcvInitFlg_pa[TrcvIdx] ) = 1;
        }
    }

    return lResult_en;
}

#endif /* #if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON ) */

/**
 ***************************************************************************************************
 * \module description
 * Enables / disables the indexed controller
 * \par Synchronous, Non Reentrant
 *
 * If ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT is ON (that is: physical address filtering is activated in the driver), then
 * 	it clears the physical address filters for the specified physical eth controller index before setting the controller to
 *  ETH_MODE_ACTIVE mode.
 *
 *
 * Parameter In:
 * \param CtrlIdx   Index of the Ethernet controller within the context of the Ethernet Interface
 * \param CtrlMode   ETHCTRL_MODE_DOWN: disable the controller ETHCTRL_MODE_ACTIVE: enable the controller
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: controller mode could not be changed}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetControllerMode(   VAR( uint8,         AUTOMATIC )     CtrlIdx,
                                                                    VAR( Eth_ModeType,  AUTOMATIC )     CtrlMode     )
{
    /* Local variables declaration */
    Std_ReturnType    lResult_en;
    uint8             lEthCtrlIdx_u8;
    uint8             lEthIfCtrlLoopIdx_u8;

    /* Initialise local variables */
    lResult_en      = E_NOT_OK;
    lEthCtrlIdx_u8  = 0xFF;
    lEthIfCtrlLoopIdx_u8     = 0;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_SETCONTROLLERMODE,    \
                                    ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ),    \
                                    ETHIF_SID_ETHIF_SETCONTROLLERMODE,                                                  \
                                    ETHIF_E_INV_CTRL_IDX, E_NOT_OK)

     /* Get EthCtrlIdx configured for the requested EthIfCtrl  */
    lEthCtrlIdx_u8 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    /* If EthIf_SetControllerMode() is called with ETH_MODE_DOWN */
    if( ETH_MODE_DOWN == CtrlMode )
    {
        /* If any of the EthIfCtrl (mapped to same EthCtrl) except the requested one is in state ETH_MODE_ACTIVE */
        /* call shall not be forwarded to driver API */
        for( lEthIfCtrlLoopIdx_u8 = 0; lEthIfCtrlLoopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ); lEthIfCtrlLoopIdx_u8++ )
        {
            if ( ( lEthCtrlIdx_u8  == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlLoopIdx_u8].idxEthCtrRef_cu8  ) ) &&  /* If any of the EthIfCtrl (mapped to same EthCtrl) */
                 ( CtrlIdx != lEthIfCtrlLoopIdx_u8  ) &&                                                                    /* except the requested one */
                 ( ETH_MODE_DOWN  != ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lEthIfCtrlLoopIdx_u8] ) ) )           /* is in state ETH_MODE_ACTIVE */
            {
                    /* Update the EThIfCtrl state to ETH_MODE_DOWN and return with E_OK */
                    ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] ) = ETH_MODE_DOWN;

                    return E_OK;
            }
        }

        /* If no other EthIfCtrl (mapped to same EthCtrl) except the requested one is in state ETH_MODE_ACTIVE */
        /* call driver API with ETH_MODE_DOWN */
        lResult_en = Eth_SetControllerMode( lEthCtrlIdx_u8,
                                            ETH_MODE_DOWN );

        if( E_OK == lResult_en )
        {
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] ) = ETHIF_ETHCTRLSTATE_UNINIT;
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] ) = ETH_MODE_DOWN;
        }
    }
    else    /* If EthIf_SetControllerMode() is called with ETH_MODE_ACTIVE */
    {
        /* Check the state EthCtrl in context of EthIf */
        switch( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] )
        {
            /* If the state of EthCtrl is ETHIF_ETHCTRLSTATE_INIT, it indicates EthIf_SetControllerMode( CtrlMode == ETH_MODE_ACTIVE ) is */
            /* not yet called to any of EthIfCtrl mapped to the current EthCtrl. And hence driver API needs to be called.  */
            case ETHIF_ETHCTRLSTATE_INIT:
        	{
				#if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )
					EthIf_Prv_ResetPhysAddrFilterReferencesForEthHwCtrlIdx(lEthCtrlIdx_u8);
				#endif

                lResult_en = Eth_SetControllerMode( lEthCtrlIdx_u8,
                                                    CtrlMode );

                if ( E_OK == lResult_en )
                {   /* Update the Data structure with state as Active */
                    ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] ) = ETH_MODE_ACTIVE;
                    EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] = ETHIF_ETHCTRLSTATE_ACTIVE;
                }
            }
            break;

            /* If the state of EthCtrl is ETHIF_ETHCTRLSTATE_ACTIVE, it indicates EthIf_SetControllerMode( CtrlMode == ETH_MODE_ACTIVE ) is */
            /* already successfully called at to least one of EthIfCtrl mapped to the current EthCtrl. And hence there is no need to call driver API  */
            case ETHIF_ETHCTRLSTATE_ACTIVE:
            {
                 ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] ) = ETH_MODE_ACTIVE;
                lResult_en = E_OK;
            }
            break;

            /* default state corresponds ETHIF_ETHCTRLSTATE_UNINIT */
            /* API shall return E_NOT_OK as EthIf_ControllerInit() needs to be called before calling EthIf_SetControllerMode( CtrlMode == ETH_MODE_ACTIVE ) */
            default:
            {
                lResult_en = E_NOT_OK;
            }
            break;
        }
    }

    return lResult_en;
}


/**
 ***************************************************************************************************
 * \module description
 *  API to check if any EthIfCtrl other than the input parameter CtrlIdx is active.
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx   Index of the Ethernet controller within the context of the Ethernet Interface
 * \param CtrlMode   ETHCTRL_MODE_DOWN: disable the controller ETHCTRL_MODE_ACTIVE: enable the controller
 *
 * \return  Std_ReturnType {E_OK: Other EthIfCtrl/s are active; E_NOT_OK: All EthIfCtrls are down }
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_EthIfCtrl_ActiveStatus( VAR( uint8,         AUTOMATIC )     CtrlIdx,
                                                                       VAR( Eth_ModeType,  AUTOMATIC )     CtrlMode )
{
    /* Local variables declaration */
    Std_ReturnType    lResult_en;
    uint8             lEthCtrlIdx_u8;
    uint8             lEthIfCtrlLoopIdx_u8;

    /* Initialise local variables */
    lResult_en            = E_NOT_OK;
    lEthCtrlIdx_u8        = 0xFF;
    lEthIfCtrlLoopIdx_u8  = 0;

     /* Get EthCtrlIdx configured for the requested EthIfCtrl  */
    lEthCtrlIdx_u8 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    /* If EthIf_SetControllerMode() is called with ETH_MODE_DOWN */
    if( ETH_MODE_DOWN == CtrlMode )
    {
        /* If any of the EthIfCtrl (mapped to same EthCtrl) except the requested one is in state ETH_MODE_ACTIVE */
        /* call shall not be forwarded to driver API */
        for( lEthIfCtrlLoopIdx_u8 = 0; lEthIfCtrlLoopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ); lEthIfCtrlLoopIdx_u8++ )
        {
            if ( ( lEthCtrlIdx_u8  == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlLoopIdx_u8].idxEthCtrRef_cu8  ) ) &&  /* If any of the EthIfCtrl (mapped to same EthCtrl) */
                 ( CtrlIdx != lEthIfCtrlLoopIdx_u8  ) &&                                                                    /* except the requested one */
                 ( ETH_MODE_DOWN  != ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lEthIfCtrlLoopIdx_u8] ) ) )           /* is in state ETH_MODE_ACTIVE */
            {
                lResult_en = E_OK;

                break;
            }
        }
    }

    return lResult_en;
}

/**
 ***************************************************************************************************
 * \module description
 * ETHIF039: Obtains the state of the indexed controller
 * \par Service ID 0x04, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 *
 * Parameter Out:
 * \param CtrlModePtr   {ETHCTRL_MODE_DOWN: the controller is disabled; ETHCTRL_MODE_ACTIVE: the controller is enabled}
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: controller could not be initialised}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_GetControllerMode(   VAR( uint8,             AUTOMATIC )             CtrlIdx,
                                                                P2VAR( Eth_ModeType,    AUTOMATIC, AUTOMATIC )  CtrlModePtr )
{
    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_GETCONTROLLERMODE,
                                    ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),      \
                                      ETHIF_SID_ETHIF_GETCONTROLLERMODE,                                              \
                                      ETHIF_E_INV_CTRL_IDX, E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == CtrlModePtr ), ETHIF_SID_ETHIF_GETCONTROLLERMODE, ETHIF_E_PARAM_POINTER, E_NOT_OK )

    /* Return the EthIfCtrlLinkState */
    ( *CtrlModePtr ) =  ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] );

    return E_OK;
}

#if( ETHIF_ENABLE_ETHIF_GET_VLANID == STD_ON )

/********************************************************************************************************************/
/*                                                                                                                  */
/* EthIf_GetVlanId()  - Returns the VLAN identifier of the requested Ethernet controller.                           */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* CtrlIdx           - Index of the Ethernet controller within the context of the Ethernet Interface.               */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/* VlanIdPtr        - Pointer to store the VLAN identifier (VID) of the Ethernet controller.                        */
/*                  - 0 if  the Ethernet controller represents no virtual network (VLAN).                           */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - success                                                                          */
/*                          E_NOT_OK - failure                                                                      */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  EthIf_GetVlanId( VAR( uint8, AUTOMATIC )                                 CtrlIdx,
                                                     P2VAR( uint16, AUTOMATIC, AUTOMATIC )                   VlanIdPtr )
{
    /* Local variable declaration */
    Std_ReturnType   lRetVal_en;

    /* Initialize local variables */
    lRetVal_en = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ),                             \
                                     ETHIF_SID_ETHIF_GETVLANID, ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),      \
                                      ETHIF_SID_ETHIF_GETVLANID,                                                      \
                                      ETHIF_E_INV_CTRL_IDX, E_NOT_OK )

    /* Report DET if VlanIdPtr is a Null Pointer */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == VlanIdPtr ), ETHIF_SID_ETHIF_GETVLANID,                      \
                                    ETHIF_E_PARAM_POINTER, E_NOT_OK )

    /* Fetch the corresponding Vlan Id for the EthIf CtrlIdx */
    ( *( uint16 * ) VlanIdPtr ) = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16 );

    /* If the CtrlIdx does not have a Vlan Id, then the value 0 is returned */
    if( *VlanIdPtr == 0xffffUL )
    {
        /* Zero is a valid VlanId incase of priority tagged frames. Hence 0 means either untagged or priority tagged frame */
        *VlanIdPtr = 0;
    }

    /* return E_OK */
    lRetVal_en = E_OK;

    return ( lRetVal_en );
}

#endif  /* #if(ETHIF_ENABLE_ETHIF_GET_VLANID == STD_ON) */

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
