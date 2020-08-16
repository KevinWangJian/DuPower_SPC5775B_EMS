
#include "EthIf.h"

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

#ifdef ETHIF_CONFIGURED

#include "EthSwt.h"

#include "EthIf_Prv.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/

static FUNC( Std_ReturnType, RBA_ETHIF_CODE ) EthIf_Stop_NotReqPorts( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          lEthSwtConfig_pst,
                                                                      P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_State_ModeDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )        lEthSwtConfig_pst,
                                                                   P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst,
                                                                   P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_PG_State_active( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )        lEthSwtConfig_pst,
                                                                    P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst,
                                                                    P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_PG_State_WaitDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          lEthSwtConfig_pst,
                                                                      P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst,
                                                                      P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst );

/**
 *****************************************************************************************************************************
 * \module description
 * Called by EthIf_MainFunctionState(), to trigger all possible state transitions for EthIf SwitchPortGroups with no semantics
 *
 * Parameter In: None
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ******************************************************************************************************************************
 */
FUNC( void, RBA_ETHIF_CODE ) EthIf_Prv_StandalonePG_StateTransitions( void )
{
    /* Local variables declaration */
    Std_ReturnType                       lStdRetType_en;
    uint8                                lPortGrpIdx_u8;
    uint16                               lloopIdx_u8;
    EthIf_Swt_PortGrpConfig_tst*         lEthIf_Swt_PortGrp_pst;
    EthIf_EthSwtConfig_tst*              lEthSwtConfig_pst;
    EthIf_StandalonePG_Type_tst*         lEthIf_StandalonePG_Type_pst;

    /* Initialise local variable */
    lStdRetType_en                = E_NOT_OK;

    /* Loop through all configured port groups. */
    for ( lPortGrpIdx_u8 = 0; lPortGrpIdx_u8 < EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfSwtPortGrps_cu8; lPortGrpIdx_u8++ )
    {
        /* Initialize standalone port group structure to NULL_PTR */
        lEthIf_StandalonePG_Type_pst  = NULL_PTR;

        lEthIf_Swt_PortGrp_pst = &(EthIf_CfgPtr_pco->EthIfPrtGrpConfig_pst[lPortGrpIdx_u8]);

        /* If the EthIfSwitchPortGroup is a standalone port group */
        if( lEthIf_Swt_PortGrp_pst->semantic_en == ETHIF_PORTGRP_UNREFERENCED )
        {
            /* Fetch the switch config of the corresponding EthIfSwitchPortGroup */
            lEthSwtConfig_pst = &(EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8]);

            /* Fetch the Standalone PG requested mode structure */
            for( lloopIdx_u8 = 0; lloopIdx_u8 < EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfStdAlone_PrtGrps_cu8; lloopIdx_u8++ )
            {
                /* If the PortGrpIdx matches the PortGrpIdx in the structure, break from the loop */
                if( lPortGrpIdx_u8 == EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lloopIdx_u8].PortGrpIdx_u8 )
                {
                    lEthIf_StandalonePG_Type_pst = &(EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lloopIdx_u8]);
                    break;
                }
            }

            /* Check if lEthIf_StandalonePG_Type_pst is not NULL_PTR */
            if( lEthIf_StandalonePG_Type_pst != NULL_PTR )
            {
                /* Fetch the current state of the standalone EthIfSwitchPortGroup */
                switch( lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en )
                {
                    /* If the state is ETHIF_STANDALONE_PG_MODE_DOWN */
                    case ETHIF_STANDALONE_PG_MODE_DOWN:
                    {
                        EthIf_Transfrm_State_ModeDown( lEthSwtConfig_pst,
                                                       lEthIf_Swt_PortGrp_pst,
                                                       lEthIf_StandalonePG_Type_pst);
                    }
                    break;

                    /* If the state of the standalone portgroup is ETHIF_STANDALONE_PG_MODE_STARTUP */
                    /* The state is reached if the portgroup was triggered by EthIf_StartAllPorts() API */
                    case ETHIF_STANDALONE_PG_MODE_STARTUP:
                    {
                        /* Check if the Ports active time has expired */
                        if( EthIf_PortActiveTime_u32 == 0U )
                        {
                            /* If timer is expired, stop all the ports of EthIfSwitchPortGroup which are not requested for ACTIVE */
                            lStdRetType_en = EthIf_Stop_NotReqPorts( lEthSwtConfig_pst,
                                                                     lEthIf_Swt_PortGrp_pst );

                            if( lStdRetType_en == E_OK )
                            {
                                /* Set the state of the EthIfSwitchPortGroup to ETHIF_STANDALONE_PG_MODE_DOWN */
                                lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_DOWN;

                                /* Set the link status of the EthIfSwitchPortGroup to ETHIF_STANDALONE_PG_LINKSTATE_DOWN */
                                lEthIf_StandalonePG_Type_pst->Standalone_PG_LinkStatus_en = ETHIF_STANDALONE_PG_LINKSTATE_DOWN;
                            }
                        }
                        /* Check if the requested state of the standalone EthIfSwitchPortGroup is ETHTRCV_MODE_ACTIVE */
                        else if( lEthIf_StandalonePG_Type_pst->Standalone_PG_ReqMode_en == ETHTRCV_MODE_ACTIVE )
                        {
                            /* Change the state of the portgroup to ETHIF_STANDALONE_PG_MODE_ACTIVE */
                            lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_ACTIVE;
                        }
                        else
                        {
                            /* Do nothing */
                        }
                    }
                    break;

                    /* If the state is ETHIF_STANDALONE_PG_MODE_ACTIVE */
                    case ETHIF_STANDALONE_PG_MODE_ACTIVE:
                    {
                        /* If the requested port mode is DOWN */
                        if( lEthIf_StandalonePG_Type_pst->Standalone_PG_ReqMode_en == ETHTRCV_MODE_DOWN )
                        {
                            EthIf_Transfrm_PG_State_active( lEthSwtConfig_pst,
                                                            lEthIf_Swt_PortGrp_pst,
                                                            lEthIf_StandalonePG_Type_pst );
                        }
                    }

                    break;

                    case ETHIF_STANDALONE_PG_MODE_WAITDOWN:
                    {
                        EthIf_Transfrm_PG_State_WaitDown( lEthSwtConfig_pst,
                                                          lEthIf_Swt_PortGrp_pst,
                                                          lEthIf_StandalonePG_Type_pst );
                    }
                    break;

                    default:
                        /* Do Nothing */
                    break;
                }
            }
        } /* if( lEthIf_StandalonePG_Type_pst != NULL_PTR ) */
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_Prv_StandalonePG_StateTransitions(), to trigger all possible transitions from state ETHIF_STANDALONE_PG_MODE_DOWN
 *
 * Parameter In: None
 * \param lEthSwtConfig_pst              Switch configuration structure of which the EthIfSwitchPortGroup is derived.
 * \param lEthIf_Swt_PortGrp_pst         Standalone SwitchPortGroup whose ports have to be switched off.
 * \param lEthIf_StandalonePG_Type_pst   Holds the state, link and requested mode for the Standalone SwitchPortGroup.
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_State_ModeDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )        lEthSwtConfig_pst,
                                                                   P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst,
                                                                   P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst )
{
    /* Local variables declaration */
    Std_ReturnType       lStdRetType_en;

    /* Initialise local variable */
    lStdRetType_en             = E_NOT_OK;

    /* Check if the requested state of the Standalone EthIfSwitchPortGroup is ETHTRCV_MODE_ACTIVE. */
    if( lEthIf_StandalonePG_Type_pst->Standalone_PG_ReqMode_en == ETHTRCV_MODE_ACTIVE )
    {
        /* Set the ports of PortGroup to ACTIVE */
        lStdRetType_en = EthIf_Prv_SetSwitchPortGroupActive( lEthSwtConfig_pst,
                                                             lEthIf_Swt_PortGrp_pst );

        /* If setting of the PortGroup is successful, change state to Active */
        if( lStdRetType_en == E_OK )
        {
            /* Set the state of the Standalone portgroup to ETHIF_STANDALONE_PG_MODE_ACTIVE */
            lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_ACTIVE;
        }
    }/* If EthIf_StartAllPorts() was called (PortActiveTime was started) , then activate the PortGroup */
    else if( EthIf_PortActiveTime_u32 > 0U )
    {
        lStdRetType_en = EthIf_Prv_SetSwitchPortGroupActive( lEthSwtConfig_pst,
                                                             lEthIf_Swt_PortGrp_pst );

        if( lStdRetType_en == E_OK )
        {
            /* If activation was successful, set the state to the PG to ETHIF_STANDALONE_PG_MODE_STARTUP */
            lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_STARTUP;
        }
    }
    else
    {
        /* Do Nothing */
    }
}


/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_Prv_StandalonePG_StateTransitions(), to trigger all possible transitions from state ETHIF_STANDALONE_PG_MODE_ACTIVE
 *
 * Parameter In: None
 * \param lEthSwtConfig_pst              Switch configuration structure of which the EthIfSwitchPortGroup is derived.
 * \param lEthIf_Swt_PortGrp_pst         Standalone SwitchPortGroup whose ports have to be switched off.
 * \param lEthIf_StandalonePG_Type_pst   Holds the state, link and requested mode for the Standalone SwitchPortGroup.
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * Return  : none
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_PG_State_active( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )        lEthSwtConfig_pst,
                                                                    P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC ) lEthIf_Swt_PortGrp_pst,
                                                                    P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst )
{
    /* Local variables declaration */
    uint16                               lloopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*      lEthIfSwitch_PortState_pst;

    /* Fetch the individual port structure */
    lEthIfSwitch_PortState_pst = lEthSwtConfig_pst->EthIf_SwtPort_past;

    /* loop through all the ports of the PortGroup */
    for( lloopIdx_u8 = 0; lloopIdx_u8 < lEthIf_Swt_PortGrp_pst->nrOfPorts_cu8; lloopIdx_u8++ )
    {
        /* If the port is ACTIVE, check whether the port is part of any other EthIfSwitchPortGroup */
        if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b != FALSE )
        {
            /* check if the port is active in other portgroups */
            if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8 > 0U )
            {
                /* Decrement the port active count */
                lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8--;
            }

            /* If the port is not used by any other EthIfSwitchPortGroup, then the port is switched off after the Port off delay timer. */
            if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8 == 0U ) &&
               (( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortOffDelay_u32 == 0U )))
            {
                /*Start Port off delay timer, by incrementing by one main function period */
                lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortOffDelay_u32 += ETHIF_MAINFUNCTION_STATE_PERIOD;
            }
        }
        else
        {
            /* Port is already down */
        }
    }

    /* If the port is ACTIVE, check whether the port is part of any other EthIfSwitchPortGroup */
    if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b != FALSE )
    {
        /* check if the port is active in other portgroups */
        if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 > 0U )
        {
            /* Decrement the port active count */
            lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8--;
        }

        /* If the port is not used by any other EthIfSwitchPortGroup, then the port is switched off after the Port off delay timer. */
        if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 == 0U ) &&
           ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 == 0U ))
        {
            /*Start Port off delay timer, by incrementing by one main function period */
            lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 += ETHIF_MAINFUNCTION_STATE_PERIOD;
        }
    }
    else
    {
        /* Port is already down */
    }

    /* Set the PG state to wait down */
    lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_WAITDOWN;
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_Prv_StandalonePG_StateTransitions(), to trigger all possible transitions from state ETHIF_STANDALONE_PG_MODE_WAITDOWN
 *
 * Parameter In: None
 * \param lEthSwtConfig_pst              Switch configuration structure of which the EthIfSwitchPortGroup is derived.
 * \param lEthIf_Swt_PortGrp_pst         Standalone SwitchPortGroup whose ports have to be switched off.
 * \param lEthIf_StandalonePG_Type_pst   Holds the state, link and requested mode for the Standalone SwitchPortGroup.
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * Return  : None
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Transfrm_PG_State_WaitDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )        lEthSwtConfig_pst,
                                                                      P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC ) lEthIf_Swt_PortGrp_pst,
                                                                      P2VAR( EthIf_StandalonePG_Type_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_StandalonePG_Type_pst )

{
    /* Local variables declaration */
    Std_ReturnType                       lStdRetType_en;
    uint16                               lloopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*      lEthIfSwitch_PortState_pst;
    boolean                              lPortModeChangeFailed_b;
    boolean                              lPortDelayExpired_b;

    /* Initialise local variable */
    lStdRetType_en             = E_NOT_OK;
    lPortModeChangeFailed_b    = FALSE;
    lPortDelayExpired_b        = FALSE;

    /* Fetch the individual port structure */
    lEthIfSwitch_PortState_pst = lEthSwtConfig_pst->EthIf_SwtPort_past;

    /* loop through all the ports of the PortGroup */
    for(lloopIdx_u8 = 0; lloopIdx_u8 < lEthIf_Swt_PortGrp_pst->nrOfPorts_cu8; lloopIdx_u8++ )
    {
        /* Check whether the port off delay timer has been exceeded, and the port is still active */
        if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].ActiveCnt_u8 == 0U ) &&
           ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortOffDelay_u32 >= ETHIF_PORT_SWITCHOFF_DELAY ) &&
           ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b != FALSE ))
        {
            /* Set the PortGroup to DOWN */
            lStdRetType_en = EthSwt_SetSwitchPortMode ( lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8,
                                                        lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortIdx_cu8,
                                                        ETHTRCV_MODE_DOWN );

            /* Set flag to indicate, that 'PortOffDelay' for the port has expired */
            lPortDelayExpired_b = TRUE;

            /* If the switching off the port was successful */
            if( lStdRetType_en == E_OK )
            {
                /* Clear the Port delay timer */
                lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].PortOffDelay_u32 = 0UL;

                /* Set the Port Active flag to false */
                lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lloopIdx_u8]].IsPortActive_b   = FALSE;
            }
            else
            {
                /* Set flag to TRUE if deactivation failed */
                lPortModeChangeFailed_b = TRUE;
            }
        }
    }

    /* Check whether the port off delay timer has been exceeded, and the host port is still active */
    if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 == 0U ) &&
       ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 >= ETHIF_PORT_SWITCHOFF_DELAY ) &&
       ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b != FALSE ) &&
       ( FALSE == lPortModeChangeFailed_b ))
    {
        /* If there is a match in the host portIdx and no standard port has failed to deactivate */
        /* Set the PortGroup to DOWN */
        lStdRetType_en = EthSwt_SetSwitchPortMode ( lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8,
                                                    lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortIdx_cu8,
                                                    ETHTRCV_MODE_DOWN );

        /* Set flag to indicate, that 'PortOffDelay' for the port has expired */
        lPortDelayExpired_b = TRUE;

        /* If the switching off the port was successful */
        if( lStdRetType_en == E_OK )
        {
            lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 = 0UL;

            lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b   = FALSE;
        }
        else
        {
            /* Set flag to TRUE if deactivation failed */
            lPortModeChangeFailed_b = TRUE;
        }
    }

    /* If atleast for one port 'PortOffDelay' timer has reached, and setting of all timed out ports was successful */
    if(( FALSE != lPortDelayExpired_b ) && ( FALSE == lPortModeChangeFailed_b ))
    {
        /* If the portgroup is down set state to ETHIF_STANDALONE_PG_MODE_DOWN */
        lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en = ETHIF_STANDALONE_PG_MODE_DOWN;

        /* If the portgroup is down set link state to ETHIF_STANDALONE_PG_LINKSTATE_DOWN */
        lEthIf_StandalonePG_Type_pst->Standalone_PG_LinkStatus_en = ETHIF_STANDALONE_PG_LINKSTATE_DOWN;
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_Prv_StandalonePG_StateTransitions(), to switch off EthIfSwitchPortGroups not requested
 * for active within port active time.
 *
 * Parameter In: None
 * \param lEthSwtConfig_pst              Switch configuration structure of which the EthIfSwitchPortGroup is derived.
 * \param lEthIf_Swt_PortGrp_pst         Standalone SwitchPortGroup whose ports have to be switched off.
 * \param lEthIf_StandalonePG_Type_pst   Holds the state, link and requested mode for the Standalone SwitchPortGroup.
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * Return  :
 * Std_ReturnType       -   Result of operation
 *                          E_OK - Request processed successfully
 *                          E_NOT_OK - Request NOT processed successfully
 *
 ***************************************************************************************************
 */
static FUNC( Std_ReturnType, RBA_ETHIF_CODE ) EthIf_Stop_NotReqPorts( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          lEthSwtConfig_pst,
                                                                      P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   lEthIf_Swt_PortGrp_pst )
{
    /* Local variables declaration */
    Std_ReturnType                     lStdRetType_en;
    uint8                              lLoopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*    lEthIfSwitch_PortState_pst;
    boolean                            lSetPortModeFailed_b;

    /* Initialise local variable */
    lStdRetType_en  =      E_NOT_OK;
    lSetPortModeFailed_b = FALSE;

    /* Fetch the individual ports structure */
    lEthIfSwitch_PortState_pst = lEthSwtConfig_pst->EthIf_SwtPort_past;

    /* loop through all the ports of the PortGroup */
    for( lLoopIdx_u8 = 0; lLoopIdx_u8 < lEthIf_Swt_PortGrp_pst->nrOfPorts_cu8; lLoopIdx_u8++ )
    {
        /* If the port is ACTIVE, check whether the port is part of any other EthIfSwitchPortGroup */
        if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].IsPortActive_b != FALSE )
        {
            /* check if the port is active in other portgroups */
            if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].ActiveCnt_u8 > 0U )
            {
                /* Decrement the port active count */
                lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].ActiveCnt_u8--;
            }

            /* If the port is not used by any other EthIfSwitchPortGroup, then the port is switched off, if not initiated already */
            if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].ActiveCnt_u8 == 0U )  &&
               ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].PortOffDelay_u32 == 0U ))
            {

                /* Set the Port mode to DOWN */
                lStdRetType_en = EthSwt_SetSwitchPortMode ( lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8,
                                                            lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8],
                                                            ETHTRCV_MODE_DOWN );

                /* If the mode was successfully set to DOWN, set active flag to false */
                if( lStdRetType_en == E_OK )
                {
                    /* Set the port active status to false */
                    lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->RefPorts_cpu8[lLoopIdx_u8]].IsPortActive_b = FALSE;
                }
                else
                {
                    lSetPortModeFailed_b = TRUE;
                }
            }
        }
    }

    /* Set the host port to down only after the non-host ports are set to down */
    /* Check if the host port has already been activated by a previous call. */
    if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b != FALSE ) &&
       ( lSetPortModeFailed_b == FALSE ))
    {
        /* check if the port is active in other portgroups */
        if( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 > 0U )
        {
            /* Decrement the port active count */
            lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8--;
        }

        /* If the port is not used by any other EthIfSwitchPortGroup, then the port is switched off, if not initiated already */
        if(( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].ActiveCnt_u8 == 0U ) &&
           ( lEthIfSwitch_PortState_pst[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].PortOffDelay_u32 == 0U ))
        {
            /* Set the Port mode to DOWN */
            lStdRetType_en = EthSwt_SetSwitchPortMode ( lEthSwtConfig_pst->EthSwtIdx_cu8,
                                                        lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8,
                                                        ETHTRCV_MODE_DOWN );

            /* If de-activation of the host port is successful */
            if( lStdRetType_en == E_OK )
            {
                /* Set the port active status to false */
                lEthSwtConfig_pst->EthIf_SwtPort_past[lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8].IsPortActive_b = FALSE;
            }
            else
            {
                lSetPortModeFailed_b = TRUE;
            }
        }
    }

    /* Check if all the ports which are not requested for mode ACTIVE, are set to DOWN */
    if( lSetPortModeFailed_b == FALSE )
    {
        /* If successful, set the return value to E_OK */
        lStdRetType_en = E_OK;
    }
    else
    {
        /* If not successful, return E_NOT_OK */
        lStdRetType_en = E_NOT_OK;
    }

    return lStdRetType_en;
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

#endif /* #if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON ) */


