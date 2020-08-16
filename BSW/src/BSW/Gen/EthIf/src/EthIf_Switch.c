
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"

#if ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))
#include "EthSwt.h"
#endif

#include "EthIf_Prv.h"

#define ETHIF_START_SEC_VAR_CLEARED_32
#include "EthIf_MemMap.h"

/* Global variable for EthIf Switch Ports active timer */
VAR( uint32,  AUTOMATIC )                            EthIf_PortActiveTime_u32 = 0UL;

#define ETHIF_STOP_SEC_VAR_CLEARED_32
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/* EthIf_SwitchPortGroupRequestMode() - Request a mode for the EthIfSwtPortGroup.                                   */
/*                                      The call shall be forwarded to EthSwt by calling EthSwt_SetSwitchPortMode,  */
/*                                      for all EthSwtPorts referenced by the port group.                           */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* PortGroupIdx       - Index of the port group within the context of the Ethernet Interface                        */
/* PortMode - ETHTRCV_MODE_DOWN:   disable the port group                                                           */
/*            ETHTRCV_MODE_ACTIVE: enable the port group                                                            */
/*                                                                                                                  */
/* Output Parameters :   none                                                                                       */
/*                                                                                                                  */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - Request processed successfully                                                   */
/*                          E_NOT_OK - Request NOT processed successfully                                           */
/*                                                                                                                  */
/********************************************************************************************************************/

FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_SwitchPortGroupRequestMode( EthIf_SwitchPortGroupIdxType PortGroupIdx,
                                                                       EthTrcv_ModeType             PortMode )
{
#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

    /* Local variable declaration */
    Std_ReturnType                          lStdRetType_en;
    EthIf_Swt_PortGrpConfig_tst*            lEthIf_PortGrp_pst;
    uint8                                   lloopIdx_u8;

    /* Initialise local variable */
    lStdRetType_en   = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_SWITCHPORTGROUPREQUESTMODE,
                                     ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: PortGroupIdx is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( PortGroupIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfSwtPortGrps_cu8 ), ETHIF_SID_ETHIF_SWITCHPORTGROUPREQUESTMODE,
                                  ETHIF_E_INV_PORT_GROUP_IDX, E_NOT_OK )

    /* Fetch the Switch PortGroup structure for the corresponding PortGroupIdx */
    lEthIf_PortGrp_pst = &(EthIf_CfgPtr_pco->EthIfPrtGrpConfig_pst[PortGroupIdx]);

    /* Report DET : Development Error: PortGroupIdx addresses a port group referenced by an EthIfController */
    ETHIF_REPORT_ERROR_RET_VALUE( ( lEthIf_PortGrp_pst->semantic_en != ETHIF_PORTGRP_UNREFERENCED ), ETHIF_SID_ETHIF_SWITCHPORTGROUPREQUESTMODE,
                                    ETHIF_E_INV_PORT_GROUP_IDX, E_NOT_OK )

    /* Loop through the configured standalone PortGroups and store the request for the PortGroupIdx */
    for( lloopIdx_u8 = 0; lloopIdx_u8 < EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfStdAlone_PrtGrps_cu8; lloopIdx_u8++ )
    {
        if( EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lloopIdx_u8].PortGrpIdx_u8 == PortGroupIdx )
        {
            EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lloopIdx_u8].Standalone_PG_ReqMode_en = PortMode;

            lStdRetType_en = E_OK;

            break;
        }
    }

    return lStdRetType_en;

#else /* ( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON ) */
    (void)PortGroupIdx;
    (void)PortMode;
    return E_NOT_OK;
#endif

}

/*****************************************************************************************************/
/* \module description                                                                              */
/* Request to start all configured ports
 * \par Service ID 0x07, Synchronous, Non Reentrant
 *
 * Parameter In:       none
 * Parameter InOut:    none
 *
 * Parameter Out:      none
 *
 * \return  Std_ReturnType
 *
 ***************************************************************************************************
 */

FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_StartAllPorts( void )
{
#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

    /* Local variable declaration */
    uint8   lStdRetType_en;

    /* Initialise local variable */
    lStdRetType_en = E_NOT_OK;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_STARTALLPORTS,
                                     ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Check whether the EthIfPortStartupActiveTime is zero. If not, EthIf_StartAllPorts() was called previously. */
    /* Continue only if the timer is zero */
    if( EthIf_PortActiveTime_u32 == 0U )
    {
        /* Start the timer with the configured value for all the ports. */
        EthIf_PortActiveTime_u32 = ETHIF_PORT_STARTUP_ACTIVE_TIME;

        lStdRetType_en = E_OK;
    }
    else
    {
        /* If the timer is non-zero, it means EthIf_StartAllPorts was called previously */
        /* Timer is not reset, reset is done in EthIf_MainFunctionState() after timer expires */
    }

    return lStdRetType_en;

#else /* ( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON ) */
    return E_NOT_OK;
#endif
}

#if ( ETHIF_SWITCH_CONFIGURED == STD_ON )

/**
 ***************************************************************************************************
 * \module description
 *  Called by EthIf_Prv_SetSwitchPortMode to enable/disable all the ports of a switch

 *
 * Parameter In:
 * \param EthSwtConfig_pst   Switch configuration structure for which the mode has been requested.
 * \param EthIfCtrlIdx_u8    Specifies the EthIfCtrlIdx the switch is referring to.
 * \param TrcvMode   ETHCTRL_MODE_DOWN: disable the switch ETHCTRL_MODE_ACTIVE: enable the switch.
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: switch mode could not be changed}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortMode( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )   EthSwtConfig_pst,
                                                                  VAR( uint8,                     AUTOMATIC )              EthIfCtrlIdx_u8,
                                                                  VAR( EthTrcv_ModeType,          AUTOMATIC )              TrcvMode   )
{
    /* Local variables declaration */
    uint8                              lloopIdx_u8;
    uint8                              lhostportIdx_u8;
    Std_ReturnType                     lResult_en;
    EthIf_EthSwt_PortStateType_tst*    lSwitchPorts_State_pst;
    uint8                              lEthIfCtrlLoopIdx_u8;
    boolean                            lHostPort_Active_b;
    boolean                            lStandardPort_Active_b;

    /* Initialize local variable */
    lResult_en              = E_NOT_OK;
    lHostPort_Active_b      = FALSE;
    lStandardPort_Active_b  = FALSE;

    /* Fetch the host port index */
    lhostportIdx_u8 = EthSwtConfig_pst->HostPortIdx_cu8;

    /*  Fetch the hardware ports structure */
    lSwitchPorts_State_pst = EthSwtConfig_pst->EthIf_SwtPort_past;

    /* If requested mode is ACTIVE */
    if( TrcvMode == ETHTRCV_MODE_ACTIVE )
    {
        /* Check if the host port has already been activated by a previous call */
        if( lSwitchPorts_State_pst[lhostportIdx_u8].IsPortActive_b == FALSE )
        {
            /* Set the port mode to active */
            lResult_en = EthSwt_SetSwitchPortMode ( EthSwtConfig_pst->EthSwtIdx_cu8,
                                                    lhostportIdx_u8,
                                                    ETHTRCV_MODE_ACTIVE );

            /* If activation of the host port is successful */
            if( lResult_en == E_OK )
            {
                /* Set the port status to active */
                lSwitchPorts_State_pst[lhostportIdx_u8].IsPortActive_b = TRUE;

                /* Clear portoffdelay timer as it is not used by switch */
                lSwitchPorts_State_pst[lhostportIdx_u8].PortOffDelay_u32 = 0UL;

                /* Set a flag to indicate host port is active */
                lHostPort_Active_b = TRUE;
            }
        }
        else
        {
            /* Clear portoffdelay timer as it is not used by switch */
            lSwitchPorts_State_pst[lhostportIdx_u8].PortOffDelay_u32 = 0UL;

            /* Set a flag to indicate host port is active */
            lHostPort_Active_b = TRUE;
        }

        /* Next set the non-host ports to active */
        for( lloopIdx_u8 = 0; (( lloopIdx_u8 <= EthSwtConfig_pst->LastPortIdx_cu8 ) && ( lHostPort_Active_b != FALSE )) ; lloopIdx_u8++ )
        {
            if(( lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8 != lhostportIdx_u8 ) &&
               ( lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8 != 0xFFU ))
            {
                /* Call Set Switch ports to active if not called previously */
                /* First check for states of each port and proceed with setting the ports to active */
                if( lSwitchPorts_State_pst[lloopIdx_u8].IsPortActive_b == FALSE )
                {
                    /* Set the port mode to active */
                    lResult_en = EthSwt_SetSwitchPortMode ( EthSwtConfig_pst->EthSwtIdx_cu8,
                                                            lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8,
                                                            TrcvMode );

                    /* If setting of the ports is successful, then set active flag to true */
                    if( lResult_en == E_OK )
                    {
                        /* Set the port status to active */
                        lSwitchPorts_State_pst[lloopIdx_u8].IsPortActive_b = TRUE;

                        /* Clear portoffdelay timer as it is not used by switch */
                        lSwitchPorts_State_pst[lloopIdx_u8].PortOffDelay_u32 = 0UL;

                        /* Set a flag, indicating a standard port is activated. */
                        lStandardPort_Active_b = TRUE;
                    }
                }
                else
                {
                    /* Clear portoffdelay timer as it is not used by switch */
                    lSwitchPorts_State_pst[lloopIdx_u8].PortOffDelay_u32 = 0UL;

                    /* Set a flag, indicating a standard port is activated. */
                    lStandardPort_Active_b = TRUE;
                }
            }
        }

        /* If host port and atleast one standard port is active, set return value to E_OK */
        if((lHostPort_Active_b != FALSE ) && ( lStandardPort_Active_b != FALSE ))
        {
            lResult_en = E_OK;
        }
    }
    /* If the requested mode is DOWN */
    else if( ETHTRCV_MODE_DOWN == TrcvMode )
    {
        lSwitchPorts_State_pst = EthSwtConfig_pst->EthIf_SwtPort_past;

        /* Check if any other EthIfCtrl is referring a switch and the mode is ACTIVE */
        for( lEthIfCtrlLoopIdx_u8 = 0; lEthIfCtrlLoopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ); lEthIfCtrlLoopIdx_u8++ )
        {
            /* If yes, break from the loop */
            if(( ETHIF_SWITCH == (EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlLoopIdx_u8].TrcvSwtPortGrp_RefType_en )) &&
               ( EthIfCtrlIdx_u8 != lEthIfCtrlLoopIdx_u8 ) &&
               ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lEthIfCtrlLoopIdx_u8] == ETH_MODE_ACTIVE ))
            {
                break;
            }
        }

        /* If no other EthIfCtrl is referring the switch proceed to set the ports of the switch to down */
        if( lEthIfCtrlLoopIdx_u8 == EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 )
        {
            /* First set the non-host ports to down */
            for( lloopIdx_u8 = 0; lloopIdx_u8 <= EthSwtConfig_pst->LastPortIdx_cu8; lloopIdx_u8++ )
            {
                /* Check if the port is active */
                if((( lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8 ) != lhostportIdx_u8 ) &&
                    ( lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8 != 0xFFU ) &&
                    ( lSwitchPorts_State_pst[lloopIdx_u8].IsPortActive_b != FALSE ))
                 {
                     /* set the port to down */
                     lResult_en = EthSwt_SetSwitchPortMode ( EthSwtConfig_pst->EthSwtIdx_cu8,
                                                             lSwitchPorts_State_pst[lloopIdx_u8].PortIdx_cu8,
                                                             ETHTRCV_MODE_DOWN );

                     if( lResult_en == E_OK )
                     {
                         /* Set the port active status to false */
                         lSwitchPorts_State_pst[lloopIdx_u8].IsPortActive_b = FALSE;
                     }
                     else
                     {
                         /* Set a flag, if setting of a standard port to down failed */
                         lStandardPort_Active_b = TRUE;
                     }
                 }
             }

            /* Initialize return value to E_NOT_OK */
            lResult_en = E_NOT_OK;

            /* If all standard ports are successfully set to down */
            if( lStandardPort_Active_b == FALSE )
            {
                /* Set the host port after all the non-host ports are set to down */
                lResult_en = EthSwt_SetSwitchPortMode ( EthSwtConfig_pst->EthSwtIdx_cu8,
                                                        lhostportIdx_u8,
                                                        ETHTRCV_MODE_DOWN );

                if( lResult_en == E_OK )
                {
                    /* Set the port active status to false */
                    lSwitchPorts_State_pst[lhostportIdx_u8].IsPortActive_b = FALSE;
                }
            }
        }
        else
        {
            /* Set return value to E_OK, since other EthIfCtrl referring the switch is active */
            lResult_en = E_OK;
        }
    }
    else
    {
        /* Do Nothing */
    }

    return lResult_en;
}
#endif /* #if ( ETHIF_SWITCH_CONFIGURED == STD_ON )  */

#if ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )

/**
 ******************************************************************************************************************
 * \module description
 * Activates a EthIfSwitchPortGroup
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param EthSwtConfig_pst   Switch configuration structure from which the SwitchPortGroup has been derived.
 * \param EthIf_PortGrp_pst  EthIfSwitchPortGroup structure for which mode active has been requested.
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: PortGroup mode could not be changed}
 *
 ******************************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortGroupActive( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          EthSwtConfig_pst,
                                                                         P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   EthIf_PortGrp_pst )
{
    /* Local variables declaration */
    uint8                              lloopIdx_u8;
    Std_ReturnType                     lResult_en;
    boolean                            lActiveFlag_b;
    EthIf_EthSwt_PortStateType_tst*    lSwitchPorts_State_pst;

    /* Initialize local variable */
    lResult_en = E_NOT_OK;

    /*  Fetch the hardware ports structure */
    lSwitchPorts_State_pst = EthSwtConfig_pst->EthIf_SwtPort_past;

    /* First set the host port to ACTIVE */
    if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b == FALSE )
    {
        /* Set the port to active */
        lResult_en = EthSwt_SetSwitchPortMode ( EthIf_PortGrp_pst->EthSwtIdx_cu8,
                                                EthIf_PortGrp_pst->HostPortIdx_cu8,
                                                ETHTRCV_MODE_ACTIVE );

        /* If port activation was successful */
        if( lResult_en == E_OK )
        {
            /* Set the port active status to true */
            lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b = TRUE;
        }
    }
    else
    {
        /* Clear the port switch off delay timer, if it was previously started */
        lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 = 0UL;
    }

    /* Set all the ports in the port group */
    for( lloopIdx_u8 = 0; lloopIdx_u8 < EthIf_PortGrp_pst->nrOfPorts_cu8; lloopIdx_u8++ )
    {
        /* Check if the port is not activated */
        if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b == FALSE )
        {
            /* Set the port to active */
            lResult_en = EthSwt_SetSwitchPortMode ( EthIf_PortGrp_pst->EthSwtIdx_cu8,
                                                    EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8],
                                                    ETHTRCV_MODE_ACTIVE );

            if( lResult_en == E_OK )
            {
                /* Set the port active status to true */
                lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b = TRUE;
            }
        }
        else
        {
            /* Clear the port switch off delay timer, if it was previously started */
            lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortOffDelay_u32 = 0UL;
        }
    }

    /* Check if atleast the host port and one non-host port has been successfully activated */
    lActiveFlag_b = EthIf_Prv_CheckPrtGrp_ActiveStatus( EthIf_PortGrp_pst );

    /* If the PortGroup has been activated, increment the port active counter and return E_OK */
    if( lActiveFlag_b != FALSE )
    {
        /* Increment the host port active count */
        lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8++;

        for( lloopIdx_u8 = 0; lloopIdx_u8 < EthIf_PortGrp_pst->nrOfPorts_cu8; lloopIdx_u8++ )
        {
            /* Check if the port is activated */
            if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b != FALSE )
            {
                /* Increment the port active count */
                lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8++;
            }
        }

        lResult_en = E_OK;
    }
    else
    {
        /* Return E_NOT_OK if not activated successfully */
        lResult_en = E_NOT_OK;
    }

    return lResult_en;
}

/**
 *********************************************************************************************************************
 * \module description
 * Deactivates a EthIfSwitchPortGroup
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param EthSwtConfig_pst   Switch configuration structure from which the SwitchPortGroup has been derived.
 * \param EthIf_PortGrp_pst  EthIfSwitchPortGroup structure for which mode down has been requested.
 *
 * \return  Std_ReturnType {E_OK: success; E_NOT_OK: PortGroup mode could not be changed}
 *
 *********************************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortGroupDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          EthSwtConfig_pst,
                                                                       P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   EthIf_PortGrp_pst )
{
    /* Local variables declaration */
    uint8                                   lloopIdx_u8;
    Std_ReturnType                          lResult_en;
    EthIf_EthSwt_PortStateType_tst*         lSwitchPorts_State_pst;
    boolean                                 lPortModeChange_Failed_b;

    /* Initialize local variable */
    lResult_en               = E_NOT_OK;
    lPortModeChange_Failed_b = FALSE;

    /* Fetch the hardware port structure. */
    lSwitchPorts_State_pst = EthSwtConfig_pst->EthIf_SwtPort_past;

    /* Set all the ports in the portgroup to DOWN. */
    for( lloopIdx_u8 = 0; lloopIdx_u8 < EthIf_PortGrp_pst->nrOfPorts_cu8; lloopIdx_u8++ )
    {
        /* Check if the port is active */
        if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b  != FALSE )
        {
            /* If the port group is active in only one PG, switch off the port */
            if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8 == 1U )
            {
                /* Set the port to down. */
                lResult_en = EthSwt_SetSwitchPortMode ( EthIf_PortGrp_pst->EthSwtIdx_cu8,
                                                        EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8],
                                                        ETHTRCV_MODE_DOWN );

                if( lResult_en == E_OK )
                {
                    /* If the port was successfully switched off, set the port active status to false */
                    lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b = FALSE;

                    /* Clear the active count */
                    lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8 = 0;
                }
                else
                {
                    /* Set a flag to indicate setting of a port to down failed. */
                    lPortModeChange_Failed_b = TRUE;
                }
            }
            else
            {
                /* Decrement the port active count */
                lSwitchPorts_State_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8--;
            }
        }
    }

    /* If there was no failure in setting of ports to down */
    if( lPortModeChange_Failed_b == FALSE )
    {
        /* Check if the host port is active */
        if(lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b != FALSE )
        {
            /* Check if the port is not used by any other PortGroups and Port Off delay timer is not started */
            if( lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 == 1U )
            {
                /* Set the port to down. */
                lResult_en = EthSwt_SetSwitchPortMode ( EthIf_PortGrp_pst->EthSwtIdx_cu8,
                                                        EthIf_PortGrp_pst->HostPortIdx_cu8,
                                                        ETHTRCV_MODE_DOWN );

                if( lResult_en == E_OK )
                {
                    /* If the port was successfully switched off, set the port active status to false */
                    lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b = FALSE;

                    /* Clear the active count */
                    lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 = 0;
                }
            }
            else
            {
                /* Decrement the active count */
                lSwitchPorts_State_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8--;

                /* Set return value to E_OK */
                lResult_en = E_OK;
            }
        }
        else
        {
            /* Set return value to E_OK */
            lResult_en = E_OK;
        }
    }
    else
    {
        /* Set return value to E_NOT_OK */
        lResult_en = E_NOT_OK;
    }


    return lResult_en;
}

/**
 ***************************************************************************************************
 * \module description
 * Checks whether a EthIfSwitchPortGroup has been successfully activated.
 * Criteria: Atleast one host port and one non-host port has been activated.
 * \par Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param EthIf_PortGrp_pst  EthIfSwitchPortGroup structure for which mode down has been requested.
 *
 * \return  boolean {TRUE: activated; FALSE: not activated}
 *
 ***************************************************************************************************
 */
FUNC(boolean, RBA_ETHIF_CODE) EthIf_Prv_CheckPrtGrp_ActiveStatus( P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   EthIf_PortGrp_pst )
{
    /* Local variables declaration */
    uint8                              lLoopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*    lEthIfSwitch_PortState_pst;
    boolean                            lActiveFlag_b;

    /* Initialize local variable */
    lActiveFlag_b = FALSE;

    /* Fetch the hardware port structure. */
    lEthIfSwitch_PortState_pst =  EthIf_CfgPtr_pco->EthIfSwtConfig_pst[EthIf_PortGrp_pst->EthSwtIdx_cu8].EthIf_SwtPort_past;

    /* If host port is active, set flag to true */
    if( lEthIfSwitch_PortState_pst[EthIf_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b != FALSE )
    {
        lActiveFlag_b = TRUE;
    }

    if( lActiveFlag_b != FALSE )
    {
        /* Initialize flag to false, so that it will be set if atleast one port is active */
        lActiveFlag_b = FALSE;

        /* Loop through all the ports of the port group */
        for( lLoopIdx_u8 = 0; lLoopIdx_u8 < EthIf_PortGrp_pst->nrOfPorts_cu8; lLoopIdx_u8++ )
        {
            /* Check if a non-host port is active */
            if( lEthIfSwitch_PortState_pst[EthIf_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].IsPortActive_b != FALSE )
            {
                /* Set the active flag to true, if atleast one port is active and break from the loop */
                lActiveFlag_b = TRUE;

                break;
            }
        }
    }

    return lActiveFlag_b;
}

#endif /* #if  ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ) */

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
