
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"

#include "EthTrcv.h"

#include "EthIf_Prv.h"

#include "EthSM.h"
#include "EthSM_Cbk.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/

#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                 VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_Down( VAR( uint8,             AUTOMATIC )             lEthIfCtrlIdx_u8,
                                                                    VAR( uint8,             AUTOMATIC )             lTrcvIdx_u8,
                                                                    VAR( Eth_ModeType,      AUTOMATIC )             lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_WaitActive( VAR( uint8,             AUTOMATIC )       lEthIfCtrlIdx_u8,
                                                                          VAR( uint8,             AUTOMATIC )       lTrcvIdx_u8,
                                                                          VAR( Eth_ModeType,      AUTOMATIC )       lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_WaitDown( VAR( uint8,             AUTOMATIC )         lEthIfCtrlIdx_u8,
                                                                        VAR( uint8,             AUTOMATIC )         lTrcvIdx_u8,
                                                                        VAR( Eth_ModeType,      AUTOMATIC )         lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_Active( VAR( uint8,             AUTOMATIC )           lEthIfCtrlIdx_u8,
                                                                      VAR( uint8,             AUTOMATIC )           lTrcvIdx_u8,
                                                                      VAR( Eth_ModeType,      AUTOMATIC )           lCtrlReqMode_en  );

#endif

#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )

static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_Control_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                           VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  );
#endif

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_LinkInfo_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                            VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_PGlinkInfo_Transfrm_WaitDown( VAR( uint8,           AUTOMATIC )       lEthIfCtrlIdx_u8,
                                                                        VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  );

static FUNC( void, RBA_ETHIF_CODE ) EthIf_PGlinkInfo_Transfrm_Active( VAR( uint8,           AUTOMATIC )       lEthIfCtrlIdx_u8,
                                                                      VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  );

#endif

#if( ETHIF_SWITCH_CONFIGURED == STD_ON )

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Switch_StateTransitions( VAR ( uint8,           AUTOMATIC )               lEthIfCtrlIdx_u8,
                                                                   VAR( Eth_ModeType,     AUTOMATIC )               lCtrlReqMode_en);
#endif

static FUNC( void, RBA_ETHIF_CODE ) EthIf_No_Ref_StateTransitions( VAR ( uint8,           AUTOMATIC )               lEthIfCtrlIdx_u8,
                                                                   VAR( Eth_ModeType,     AUTOMATIC )               lCtrlReqMode_en);



/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_MainFunctionState(), to check trigger transitions of mode state change for EthIf controllers
 * referencing a transceiver/ Switch/EthIfSwitchPortGroups
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
 ***************************************************************************************************
 */
FUNC( void, RBA_ETHSM_CODE ) EthIf_Prv_Trigger_StateTransitions( void )
{
    /* Local variables declaration */
    uint8                                       lEthIfCtrlIdx_u8;
    EthIf_Trcv_Swt_PortGrp_RefType_ten          lEthIf_Trcv_Swt_PortGrp_RefType_en;
    Eth_ModeType                                lCtrlReqMode_en;

    /* Loop through all EthIf Ctrls */
    for( lEthIfCtrlIdx_u8 = 0; (lEthIfCtrlIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ) ; lEthIfCtrlIdx_u8++ )
    {
        /* Fetch the reference type for the particular EthIf Ctrl */
        lEthIf_Trcv_Swt_PortGrp_RefType_en = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvSwtPortGrp_RefType_en;

        /* Fetch the mode requested for the EthIfCtrl */
        lCtrlReqMode_en = EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlReqMode_pa[lEthIfCtrlIdx_u8];

        /* Depending on the particular reference type call the particular state transition APIs */
        switch( lEthIf_Trcv_Swt_PortGrp_RefType_en )
        {
            case ETHIF_TRCV:
            {
#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )
                /* Reference type is a transceiver */
                EthIf_Trcv_StateTransitions( lEthIfCtrlIdx_u8, lCtrlReqMode_en );
#endif
            }
            break;

            case ETHIF_PORTGRP_CTRL:
            {
#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )
                /* Reference type is a EthIfSwitchPortGroup of semantic ETHIF_SWITCH_PORT_GROUP_CONTROL */
                EthIf_PrtGrp_Control_StateTransitions( lEthIfCtrlIdx_u8, lCtrlReqMode_en );
#endif
            }
            break;

            case ETHIF_PORTGRP_LINKINFO:
            {
#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
                /* Reference type is a EthIfSwitchPortGroup of semantic ETHIF_SWITCH_PORT_GROUP_LINK_INFO */
                EthIf_PrtGrp_LinkInfo_StateTransitions( lEthIfCtrlIdx_u8, lCtrlReqMode_en );
#endif
            }
            break;

            case ETHIF_SWITCH:
            {
#if( ETHIF_SWITCH_CONFIGURED == STD_ON )
                /* Reference type is a Switch */
                EthIf_Switch_StateTransitions( lEthIfCtrlIdx_u8, lCtrlReqMode_en );
#endif
            }
            break;

            case ETHIF_NO_REF:
            {
                /* EthIfCtrl has no reference */
                EthIf_No_Ref_StateTransitions( lEthIfCtrlIdx_u8, lCtrlReqMode_en );
            }
            break;

            default:
                /* Do Nothing */
            break;
        }
    }
}

#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )

/**
 *********************************************************************************************************************************
 * \module description
 * Called by EthIf_Prv_Trigger_StateTransitions(), to trigger all possible state transitions for EthIfCtrl refering a transceiver.
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 *********************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_StateTransitions( VAR ( uint8,           AUTOMATIC )     lEthIfCtrlIdx_u8,
                                                                VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    EthIf_EthIfCtrlStateType_ten            lEthIfCtrl_State_en;
    uint8                                   lTrcvIdx_u8;

    lEthIfCtrl_State_en = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en;

    lTrcvIdx_u8 = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvIdx_cu8;

    switch( lEthIfCtrl_State_en )
    {
        case ETHIF_ETHIFCTRL_STATE_DOWN:
        {
            /* Transition from ETHIF_ETHIFCTRL_STATE_DOWN to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE/ETHIF_ETHIFCTRL_STATE_ACTIVE */
            EthIf_Trcv_Transfrm_State_Down( lEthIfCtrlIdx_u8,
                                            lTrcvIdx_u8,
                                            lCtrlReqMode_en );
        }
        break;

        case ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE:
        {
            /* Transition from ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE to all available states */
            EthIf_Trcv_Transfrm_State_WaitActive( lEthIfCtrlIdx_u8,
                                                  lTrcvIdx_u8,
                                                  lCtrlReqMode_en );
        }
        break;

        case ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN:
        {
            /* Transition from ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN to ETHIF_ETHIFCTRL_STATE_DOWN/ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
            EthIf_Trcv_Transfrm_State_WaitDown( lEthIfCtrlIdx_u8,
                                                lTrcvIdx_u8,
                                                lCtrlReqMode_en );
        }
        break;

        case ETHIF_ETHIFCTRL_STATE_ACTIVE:
        {
            /* Transition from ETHIF_ETHIFCTRL_STATE_ACTIVE to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN/ETHIF_ETHIFCTRL_STATE_DOWN */
            EthIf_Trcv_Transfrm_State_Active( lEthIfCtrlIdx_u8,
                                              lTrcvIdx_u8,
                                              lCtrlReqMode_en );
        }
        break;

        default:
            /* Do Nothing */
        break;
    }

    return;
}

/**
 ***************************************************************************************************************************
 * \module description
 * Called by EthIf_Trcv_StateTrnsitions(), to trigger all possible state transitions from state ETHIF_ETHIFCTRL_STATE_DOWN.
 *
 * Parameter In:
 * \param lEthIfTrcv_Config_pst      : Transceiver configuration structure referred by the EthIfCtrl
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_Down( VAR( uint8,                           AUTOMATIC )               lEthIfCtrlIdx_u8,
                                                                    VAR( uint8,                           AUTOMATIC )               lTrcvIdx_u8,
                                                                    VAR( Eth_ModeType,                    AUTOMATIC )               lCtrlReqMode_en  )
{
    /* Local variables declaration */
    boolean            lTerminateLoop_b;
    Std_ReturnType     lStdRetType_en;
    uint16             lEthIfCtrlLoopIdx_u8;

    /* Initialize local variable */
    lTerminateLoop_b = FALSE;
    lStdRetType_en   = E_NOT_OK;

    /* If the requested controller mode is Active and transceiver error is not set */
    if(( lCtrlReqMode_en == ETH_MODE_ACTIVE ) &&
       ( FALSE == EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[lEthIfCtrlIdx_u8] ))
    {
        /* Initialize the physical controller referred by the EthIf Ctrl */
        lStdRetType_en = EthIf_Prv_ControllerInit( lEthIfCtrlIdx_u8 );

       if( E_OK == lStdRetType_en )
       {/* Initialize EthIfTrcv referred by the EthIf Ctrl. */
         lStdRetType_en = EthIf_Prv_TransceiverInit( lTrcvIdx_u8 );
       }

       /* After initialization is successful */
       if( E_OK == lStdRetType_en )
       { /* Set EthIfTrcv to ACTIVE */
         /* Check for EthIf Ctrls with physical Trcv Idx same as the requested physical Trcv Idx, */
         /* whether transceiver mode active has already been requested */
            for( lEthIfCtrlLoopIdx_u8 = 0;
                 ( ( lEthIfCtrlLoopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ) && ( lTerminateLoop_b == FALSE ) );
                 lEthIfCtrlLoopIdx_u8++ )
            {
                if(( lEthIfCtrlLoopIdx_u8 != lEthIfCtrlIdx_u8 ) &&
                      ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlLoopIdx_u8].TrcvIdx_cu8 == lTrcvIdx_u8 ))
                {
                    /* If the requested physical Trcv is already gone up, don't try to make Trcv up */
                    switch(  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlLoopIdx_u8].EthIfCtrlState_en )
                    {
                        case ( ETHIF_ETHIFCTRL_STATE_DOWN ):
                        {
                           /* State is down. EthTrcv_SetTransciverMode(ACTIVE) shall be called */
                        }
                        break;

                        case ( ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN ):
                        {
                            /* State is requested for down for the physical Trcv. */

                            lTerminateLoop_b = TRUE;
                        }
                        break;

                        case ( ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE ):
                        {
                            /* Update EthIf Trcv state to ETHIF_TRCV_STATE_WAIT_TRCV_ACTIVE */
                            ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE;

                            lTerminateLoop_b = TRUE;
                        }
                        break;

                        case ( ETHIF_ETHIFCTRL_STATE_ACTIVE ):
                        {
                            lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8, ETH_MODE_ACTIVE );

                            if( E_OK == lStdRetType_en )
                            {
                             EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                                       ETH_MODE_ACTIVE  );

                                /* Update EthIf Trcv state to ETHIF_TRCV_STATE_WAIT_TRCV_LINK and call EthSM_TrcvModeIndication */
                                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_ACTIVE;
                            }

                            lTerminateLoop_b = TRUE;
                        }
                        break;

                        default:
                            /* Do Nothing */
                        break;
                    }
                }
            }

            if( FALSE == lTerminateLoop_b )
            {
                /* Make the Trcv up*/
                lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                             ETHTRCV_MODE_ACTIVE );

                /* Update EthIf Trcv state to ETHIF_TRCV_STATE_WAIT_TRCV_ACTIVE */
                if( E_OK == lStdRetType_en )
                {
                    ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE;
                }
            }
        }/* if( E_OK == lStdRetType_en ) */
    }/* if( lCtrlReqMode_en == ETH_MODE_ACTIVE ) */
}

/**
 *********************************************************************************************************************************
 * \module description
 * Called by EthIf_Trcv_StateTransitions(), to trigger all possible state transitions from ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE.
 *
 * Parameter In:
 * \param lEthIfTrcv_Config_pst      : Transceiver configuration structure referred by the EthIfCtrl
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***********************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_WaitActive( VAR( uint8,                           AUTOMATIC )              lEthIfCtrlIdx_u8,
                                                                          VAR( uint8,                           AUTOMATIC )              lTrcvIdx_u8,
                                                                          VAR( Eth_ModeType,                    AUTOMATIC )              lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType    lStdRetType_en;
    uint16            lloopIdx_u8;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* If indicated mode of the physical transceiver is active */
    if( ETHTRCV_MODE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[lTrcvIdx_u8] ))
    {
        /* If requested EthIf controller mode is active */
        if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
        {
            /* Call EthIf_Prv_SetControllerMode with Eth mode ETH_MODE_ACTIVE */
            lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                          ETH_MODE_ACTIVE );

            if( E_OK == lStdRetType_en )
            {
                /* Indicate that the hardware mode is active to EthSM */
                EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                          ETH_MODE_ACTIVE  );

                /* Update EthIf Ctrl state to ETHIF_ETHIFCTRL_STATE_ACTIVE */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_ACTIVE;
            }
        }
        else if( lCtrlReqMode_en == ETH_MODE_DOWN )
        {
            /* Loop through all EthIf Ctrls mapped to the same physical Trcv, if they are in state ACTIVE or WAIT_TRCVMODE_ACTIVE */
            for( lloopIdx_u8 = 0; ( lloopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 )); lloopIdx_u8++ )
            {
                if(( lloopIdx_u8 != lEthIfCtrlIdx_u8 ) &&
                  (( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lloopIdx_u8].EthIfCtrlState_en == ETHIF_ETHIFCTRL_STATE_ACTIVE ) ||
                   ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lloopIdx_u8].EthIfCtrlState_en == ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE )))
                {
                    /* If yes, indicate that the hardware mode is active to EthSM */
                    EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                              ETH_MODE_DOWN  );

                    /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_DOWN */
                    ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;

                    break;
                }
            }

            /* If no other EthIf Ctrls are in active/wait_active state, set the physical trcv to down */
            if( lloopIdx_u8 == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) )
            {
                /* Make the Trcv down */
                lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                             ETHTRCV_MODE_DOWN );

                /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN */
                (  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
    else if(( ETHTRCV_MODE_DOWN == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[lTrcvIdx_u8] )) &&
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[lEthIfCtrlIdx_u8] != FALSE ))
    {
        /* Make the Trcv down, if the trcv indicated mode is down and there is a trcv error */
        lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                     ETHTRCV_MODE_DOWN );

        if( lStdRetType_en == E_OK )
        {
            /* Indicate that the hardware mode is down to EthSM */
            EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                      ETH_MODE_DOWN  );

            /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_DOWN */
            ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;
        }
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 *************************************************************************************************************************************
 * \module description
 * Called by EthIf_Trcv_StateTransitions(), to trigger all possible state transitions from state ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN
 *
 * Parameter In:
 * \param lEthIfTrcv_Config_pst      : Transceiver configuration structure referred by the EthIfCtrl
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_WaitDown( VAR( uint8,                           AUTOMATIC )              lEthIfCtrlIdx_u8,
                                                                        VAR( uint8,                           AUTOMATIC )              lTrcvIdx_u8,
                                                                        VAR( Eth_ModeType,                    AUTOMATIC )              lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType   lStdRetType_en;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* If indicated transceiver mode is down */
    if( ETHTRCV_MODE_DOWN == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[lTrcvIdx_u8] ) )
    {
        /* If the requested controller mode is down */
        if( lCtrlReqMode_en == ETH_MODE_DOWN )
        {
            /*  Call EthIf_Prv_SetControllerMode with Eth mode ETH_MODE_DOWN  */
            lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                          ETH_MODE_DOWN );

            if( E_OK == lStdRetType_en )
            {
                /* Indicate that the hardware mode is down to EthSM */
                EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                          ETH_MODE_DOWN  );

                /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_DOWN */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;

                if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) != ETHIF_ETHIFCTRL_LINKSTATE_DOWN )
                {
                    /* Give indication to EthSM that the virtual link state of the Trcv is also DOWN */
                    EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                            ETHTRCV_LINK_STATE_DOWN );

                    /* Update EthIf Trcv link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                    ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                }
            }
        }
        else if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
        {
            /* Make the physical transceiver active */
            lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                         ETHTRCV_MODE_ACTIVE );

            if( lStdRetType_en == E_OK )
            {
                /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en) = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }
}

/**
 *********************************************************************************************************************************
 * \module description
 * Called by EthIf_Trcv_StateTransitions(), to trigger all possible state transitions for EthIfCtrl referring a transceiver.
 *
 * Parameter In:
 * \param lEthIfTrcv_Config_pst      : Transceiver configuration structure referred by the EthIfCtrl
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***********************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_Transfrm_State_Active( VAR( uint8,             AUTOMATIC )                            lEthIfCtrlIdx_u8,
                                                                      VAR( uint8,             AUTOMATIC )                            lTrcvIdx_u8,
                                                                      VAR( Eth_ModeType,      AUTOMATIC )                            lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType   lStdRetType_en;
    uint16           lloopIdx_u8;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* Make the Trcv down, if the trcv indicated mode is down and there is a trcv error */
    if(( ETHTRCV_MODE_DOWN == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[lTrcvIdx_u8] )) &&
       ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[lEthIfCtrlIdx_u8] != FALSE ))
    {
        lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                     ETHTRCV_MODE_DOWN );

        if( lStdRetType_en == E_OK )
        {
            /* Set the mode of the controller to down */
            lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                          ETH_MODE_DOWN );

            if( E_OK == lStdRetType_en )
            {
                /* Indicate that the hardware mode is down to EthSM */
                EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                          ETH_MODE_DOWN  );

                /* Update EthIf Trcv state to ETHIF_TRCV_STATE_DOWN */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;

                /* If the link state of the EthIfCtrl is still active */
                if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) == ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE )
                {
                    /* Give indication to EthSM that the virtual link state of the Trcv is also DOWN */
                    EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                            ETHTRCV_LINK_STATE_DOWN );

                    /* Update EthIf Trcv link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                    ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                }
            }
        }
    }
    else if( lCtrlReqMode_en == ETH_MODE_DOWN )
    {
        /* For EthIf Ctrls with physical Trcv Idx same as the requested physical Trcv Idx */
        for( lloopIdx_u8 = 0; lloopIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ); lloopIdx_u8++ )
        {
            if(( lloopIdx_u8 != lEthIfCtrlIdx_u8  ) &&
               ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lloopIdx_u8].TrcvIdx_cu8 == lTrcvIdx_u8 ))
            {
                /* If other than requested EthIf Trcv is in state ETHIF_ETHIFCTRL_STATE_ACTIVE/ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
                /* don't try to make Trcv down */
                if( ( ETHIF_ETHIFCTRL_STATE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lloopIdx_u8].EthIfCtrlState_en )) ||
                  ( ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lloopIdx_u8].EthIfCtrlState_en )))
                {
                    /* Set the mode of they controller to down */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                  ETH_MODE_DOWN );

                    if( E_OK == lStdRetType_en )
                    {
                        /* Indicate that the hardware mode is down to EthSM */
                        EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                                  ETH_MODE_DOWN  );

                        /* Update EthIf Trcv state to ETHIF_TRCV_STATE_DOWN */
                        (  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;

                        /* If the link state of the EthIfCtrl is still active */
                        if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) == ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE )
                        {
                            /* Give indication to EthSM that the virtual link state of the Trcv is also DOWN */
                            EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                                    ETHTRCV_LINK_STATE_DOWN );


                            /* Update EthIf Trcv link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                            ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en ) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                        }
                    }

                    /* return if other active EthIfCtrls are using the same transceiver. */
                    return;
                }
            }
        }

        /* Make the Trcv down, if no other EthIf Ctrls has requested for transceiver active */
        lStdRetType_en = EthTrcv_SetTransceiverMode( lTrcvIdx_u8,
                                                     ETHTRCV_MODE_DOWN );

        /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN */
        if( E_OK == lStdRetType_en )
        {
            /* Update the state to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN */
            ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN;
        }
    }
    else
    {
        /* Do nothing */
    }
}

#endif /* #if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON ) */

#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_Prv_Trigger_StateTransitions(),
 * to trigger all possible state transitions for EthIf SwitchPortGroups with semantic 'Control'
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
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
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_Control_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                          VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType                   lStdRetType_en;
    EthIf_Swt_PortGrpConfig_tst*     lEthIf_Swt_PortGrp_pst;
    EthIf_EthSwtConfig_tst*          lEthIf_SwtConfig_pst;

    lEthIf_Swt_PortGrp_pst = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].SwtPortGrp_pst;

    /* Fetch the switch structure for the corresponding switch index */
    lEthIf_SwtConfig_pst = &(EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8]);

    switch( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en )
    {
        /* If the state of the EthIf Ctrl is DOWN */
        case ETHIF_ETHIFCTRL_STATE_DOWN:
        {
            /* If requested EthIf controller mode is ACTIVE */
            if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
            {
                lStdRetType_en = EthIf_Prv_ControllerInit( lEthIfCtrlIdx_u8 );

                if( lEthIf_SwtConfig_pst->EthIfSwt_State_en == ETHIF_ETHSWTSTATE_UNINIT )
                {
                  /* Currently EthSwt_SwitchInit() API is not called form EthIf, it shall be called by integration code */

                    if( lStdRetType_en == E_OK )
                    {
                        /* If controller init was successful, set switch to init state */
                        lEthIf_SwtConfig_pst->EthIfSwt_State_en = ETHIF_ETHSWTSTATE_INIT;
                    }
                }

                if( lStdRetType_en == E_OK )
                {
                    /* Set the mode of the physical controller to ACTIVE, for the corresponding EthIf Ctrl */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                  ETH_MODE_ACTIVE );
                }

                if( E_OK == lStdRetType_en )
                {
                    /* Set the EthIfSwitchPortGroup to active */
                    lStdRetType_en =  EthIf_Prv_SetSwitchPortGroupActive( lEthIf_SwtConfig_pst,
                                                                          lEthIf_Swt_PortGrp_pst );
                }

                /* If setting of ports of the PortGroup is successful */
                if( lStdRetType_en == E_OK )
                {
                    /* Indicate the controller mode to EthSM */
                    EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                              ETH_MODE_ACTIVE );

                    /* Set the state of the EthIf Ctrl to ACTIVE */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_ACTIVE;

                }
            }
        }
        break;

        /* If the state of the EthIf Ctrl is Active */
        case ETHIF_ETHIFCTRL_STATE_ACTIVE:
        {
            /* If mode down has been requested */
            if( lCtrlReqMode_en == ETH_MODE_DOWN )
            {
                /* Set the EthIfSwitchPortGroup to down */
                lStdRetType_en =  EthIf_Prv_SetSwitchPortGroupDown( lEthIf_SwtConfig_pst,
                                                                    lEthIf_Swt_PortGrp_pst );

                if( E_OK == lStdRetType_en )
                {
                    /* Set the controller mode to down */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                  ETH_MODE_DOWN );
                }

                if( lStdRetType_en == E_OK )
                {
                    /* Indicate the EthIf controller mode to DOWN */
                    EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                              ETH_MODE_DOWN );

                    /* Set the state of the EthIf Ctrl to DOWN */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_DOWN;

                    if( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en != ETHIF_ETHIFCTRL_LINKSTATE_DOWN )
                    {
                        /* Give indication to EthSM that the virtual link state of the PG is also DOWN */
                        EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                                ETHTRCV_LINK_STATE_DOWN );

                        /* Update PG link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                        ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                    }
                }
            }
        }
        break;

        default:
            /* Do Nothing */
        break;
    }
}
#endif /* #if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ) */

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

/**
 ************************************************************************************************************************************************
 * \module description
 * Called by EthIf_Prv_Trigger_StateTransitions(), to trigger all possible state transitions for EthIf SwitchPortGroups with semantic 'Link-Info'
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_LinkInfo_StateTransitions( VAR( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                           VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType                       lStdRetType_en;
    EthIf_Swt_PortGrpConfig_tst*         lEthIf_Swt_PortGrp_pst;
    boolean                              lActiveFlag_b;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    lEthIf_Swt_PortGrp_pst =  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].SwtPortGrp_pst;

    switch( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en )
    {
        /* If the state of EthIf Ctrl is ETHIF_ETHIFCTRL_STATE_DOWN */
        case ETHIF_ETHIFCTRL_STATE_DOWN:
        {
            /* If the requested controller mode is ACTIVE */
            if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
            {
                /* Initialize the physical controller */
                lStdRetType_en = EthIf_Prv_ControllerInit( lEthIfCtrlIdx_u8 );

                /* If controller initialization was successful */
                if( lStdRetType_en == E_OK )
                {
                    /* Set the controller mode to ACTIVE */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                  ETH_MODE_ACTIVE );

                    /* Set the state of the EthIf Ctrl to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
                    /* The state is changed to ETHIF_ETHIFCTRL_STATE_ACTIVE when ports of the EthIfSwitchPortGroup is set to active by BswM */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE;
                }
            }
            else
            {
                /* Already down. Do nothing */
            }
        }
        break;

        /* If the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
        case ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE:
        {
            /* Check whether atleast host port and one non-host port is active */
            lActiveFlag_b = EthIf_Prv_CheckPrtGrp_ActiveStatus( lEthIf_Swt_PortGrp_pst );

            /* If the required ports are activated */
            if( lActiveFlag_b != FALSE )
            {
                /* Indicate the EthIf Ctrl mode as ACTIVE to EthSM */
                EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                          ETH_MODE_ACTIVE );

                /* Set the state of the EthIf Ctrl to ETHIF_ETHIFCTRL_STATE_ACTIVE */
                EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_ACTIVE;

                break;
            }

            /* if the requested controller mode is down */
            if( lCtrlReqMode_en == ETH_MODE_DOWN )
            {
                /* Set the controller to DOWN */
                lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                              ETH_MODE_DOWN );

                if( lStdRetType_en == E_OK )
                {
                    /* Set the state of the EthIf Ctrl to ETHIF_ETHIFCTRL_STATE_DOWN */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_DOWN;
                }
            }
            else
            {
                /* Do Nothing */
            }
        }
        break;

        /* If the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN */
        case ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN:
        {
            EthIf_PGlinkInfo_Transfrm_WaitDown( lEthIfCtrlIdx_u8,
                                                lCtrlReqMode_en );
        }
        break;

        /* If the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_ACTIVE */
        case ETHIF_ETHIFCTRL_STATE_ACTIVE:
        {
            EthIf_PGlinkInfo_Transfrm_Active( lEthIfCtrlIdx_u8,
                                              lCtrlReqMode_en );
        }
        break;

        default:
        /* Do Nothing */
        break;
    }
}

/**
 ************************************************************************************************************************************************
 * \module description
 * Called by EthIf_PrtGrp_LinkInfo_StateTransitions(), to trigger all possible state transitions for ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PGlinkInfo_Transfrm_WaitDown( VAR( uint8,           AUTOMATIC )       lEthIfCtrlIdx_u8,
                                                                        VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType                       lStdRetType_en;
    uint8                                lEthCtrlIdx_u8;
    uint16                               lloopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*      lEthIfSwitch_PortState_pst;
    EthIf_Swt_PortGrpConfig_tst*         lEthIf_Swt_PortGrp_pst;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    lEthIf_Swt_PortGrp_pst =  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].SwtPortGrp_pst;

    /* Fetch the individual ports structure */
    lEthIfSwitch_PortState_pst = EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].EthIf_SwtPort_past;

    /* Fetch the physical controller index */
    lEthCtrlIdx_u8  = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].idxEthCtrRef_cu8;

    /* If the requested controller mode is active */
    if(lCtrlReqMode_en == ETH_MODE_ACTIVE )
    {
        /* Set the state of the EthIf Ctrl to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE */
        EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE;

    } /* If the requested controller mode is down */
    else if( lCtrlReqMode_en == ETH_MODE_DOWN )
    {
        /* Check if all the ports of the switch related to the EthIf_SwitchPortGroup is down */
        for( lloopIdx_u8 = 0; lloopIdx_u8 <= EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].LastPortIdx_cu8; lloopIdx_u8++)
        {
            if(( lEthIfSwitch_PortState_pst[lloopIdx_u8].IsPortActive_b != FALSE ) &&
               ( lEthIfSwitch_PortState_pst[lloopIdx_u8].PortIdx_cu8 != 0xFFU ))
            {
               /* If atleast one port is active, do not set the physical controller to down */
               break;
            }
        }

        /* If all the ports of the switch is down, then set the physical controller to down */
        if( lloopIdx_u8 == ( EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].LastPortIdx_cu8+1 ) )
        {
            lStdRetType_en = Eth_SetControllerMode( lEthCtrlIdx_u8,
                                                    ETH_MODE_DOWN );

            if( lStdRetType_en == E_OK )
            {
                /* Update the state of the Eth controller to ETHIF_ETHCTRLSTATE_UNINIT */
                ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlIdx_u8] ) = ETHIF_ETHCTRLSTATE_UNINIT;

                /* Update the EThIfCtrl state to ETH_MODE_DOWN */
                ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lEthIfCtrlIdx_u8] ) = ETH_MODE_DOWN;

                /* Indicate that the mode of the EthIf Ctrl is Down */
                EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8, ETH_MODE_DOWN );

                /* Set the state of the EthIfSwitchPortGroup to ETHIF_ETHIFCTRL_STATE_DOWN */
                EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_DOWN;

                /* Update PG link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;

            }
        }
    }
    else
    {
        /* Do Nothing */
    }
}

/**
 ************************************************************************************************************************************************
 * \module description
 * Called by EthIf_PrtGrp_LinkInfo_StateTransitions(), to trigger all possible state transitions for ETHIF_ETHIFCTRL_STATE_ACTIVE
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***************************************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PGlinkInfo_Transfrm_Active( VAR( uint8,           AUTOMATIC )       lEthIfCtrlIdx_u8,
                                                                      VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType                       lStdRetType_en;
    uint16                               lloopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*      lEthIfSwitch_PortState_pst;
    EthIf_Swt_PortGrpConfig_tst*         lEthIf_Swt_PortGrp_pst;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    lEthIf_Swt_PortGrp_pst =  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].SwtPortGrp_pst;

    /* Fetch the individual ports structure */
    lEthIfSwitch_PortState_pst = EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].EthIf_SwtPort_past;

    /* If the requested controller mode is DOWN */
    if( lCtrlReqMode_en == ETH_MODE_DOWN )
    {
        /* Check if atleast one port of the switch is referred by other EthIfCtrls */
        for( lloopIdx_u8 = 0; lloopIdx_u8 <= EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].LastPortIdx_cu8; lloopIdx_u8++ )
        {
            if(( lEthIfSwitch_PortState_pst[lloopIdx_u8].ActiveCnt_u8 > 1U ) &&
               ( lEthIfSwitch_PortState_pst[lloopIdx_u8].PortIdx_cu8 != 0xFFU ))
            {
               break;
            }
        }

        /* Check if all the EthIfCtrls are requested for down mapped to the same physical controller */
        lStdRetType_en = EthIf_Prv_EthIfCtrl_ActiveStatus( lEthIfCtrlIdx_u8, ETH_MODE_DOWN );

        /* If no other EthIfCtrl is requested for active and all ports of the switch are not referred by any other EthIfCtrl */
        if(( lloopIdx_u8 == ( EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8].LastPortIdx_cu8+1 )) &&
           ( lStdRetType_en == E_NOT_OK ))
        {
            /* Set the SwitchPortGroup state to ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN */
            EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN;
        }
        else
        {
            /* If still atleast a port is active or if atleast one EthIfCtrl is not requested for down */
            /* Indicate the EthIf Ctrl mode as down to EthSM */
            EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8, ETH_MODE_DOWN );

            /* Set the state of the EthIfSwitchPortGroup mapped to the EthIf Ctrl to ETHIF_ETHIFCTRL_STATE_DOWN */
            EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_DOWN;

            /* If the link state of the Port Group is still active */
            if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en) == ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE )
            {
                /* Give indication to EthSM that the virtual link state of the PG is also DOWN */
                EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                        ETHTRCV_LINK_STATE_DOWN );

                /* Update PG link state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
            }
        }
    }
    else
    {
        /* Do Nothing */
    }
}

#endif /* #if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON ) */

#if( ETHIF_SWITCH_CONFIGURED == STD_ON )

/**
 *******************************************************************************************************************************
 * \module description
 * Called by EthIf_Prv_Trigger_StateTransitions(), to trigger all possible state transitions for EthIfCtrl refering to EthIfSwitch
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 *******************************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Switch_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                  VAR( Eth_ModeType,     AUTOMATIC )      lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType             lStdRetType_en;
    EthIf_EthSwtConfig_tst*    lEthSwtConfig_pst;
    uint8                      lSwtIdx_u8;

    /* Initialize local variable */
    lStdRetType_en    = E_NOT_OK;
    lSwtIdx_u8        = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthSwtIdx_cu8;
    lEthSwtConfig_pst = &(EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lSwtIdx_u8]);

    /* Check the state of the EthIfCtrl referring the Switch */
    switch( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en )
    {
        /* If the state is ETHIF_ETHIFCTRL_STATE_DOWN */
        case ETHIF_ETHIFCTRL_STATE_DOWN:
        {   /* If the EthIfCtrl is requested for ACTIVE */
            if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
            {
                /* Initialize the physical controller mapped to the EthIf Ctrl */
                lStdRetType_en = EthIf_Prv_ControllerInit( lEthIfCtrlIdx_u8 );

                if( lEthSwtConfig_pst->EthIfSwt_State_en == ETHIF_ETHSWTSTATE_UNINIT )
                {
                    /* Call Switch init API */
                    /* Switch init not to be called for Leo Switch */
                    lEthSwtConfig_pst->EthIfSwt_State_en = ETHIF_ETHSWTSTATE_INIT;
                }

                /* If controller initialization was successful, set the controller mode to active */
                if( lStdRetType_en == E_OK )
                {
                    /* Set the controller mode to active */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                ETH_MODE_ACTIVE );
                }

                if( E_OK == lStdRetType_en )
                {
                    /* Set the ports of the switch to active */
                    lStdRetType_en =  EthIf_Prv_SetSwitchPortMode( lEthSwtConfig_pst,
                                                                   lEthIfCtrlIdx_u8,
                                                                   ETHTRCV_MODE_ACTIVE );
                }

                if( lStdRetType_en == E_OK )
                {
                    /* Indicate that the state of the EthIfCtrl as Active to EthSM */
                    EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                              ETH_MODE_ACTIVE  );

                    /* Set the state of the EthIfCtrl to Active */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_ACTIVE;
                }
            }
        }
        break;

        /* If the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_ACTIVE */
        case ETHIF_ETHIFCTRL_STATE_ACTIVE:
        {
            /* If the requested controller mode is DOWN */
            if( lCtrlReqMode_en == ETH_MODE_DOWN )
            {
                /* Set the switch ports to down */
                lStdRetType_en =  EthIf_Prv_SetSwitchPortMode( lEthSwtConfig_pst,
                                                               lEthIfCtrlIdx_u8,
                                                               ETHTRCV_MODE_DOWN );

                /* If the setting of ports is successful */
                if( lStdRetType_en == E_OK )
                {
                    /* Set the controller mode to DOWN */
                    lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                                  ETH_MODE_DOWN );
                }

                if( lStdRetType_en == E_OK )
                {
                    /* Indicate the EthIf Ctrl mode as down to EthSM */
                    EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8, ETH_MODE_DOWN );

                    /* Give indication to EthSM that the virtual link state of the PG is also DOWN */
                    EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                            ETHTRCV_LINK_STATE_DOWN );

                    /* Set the EthIfCtrl state to down */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en = ETHIF_ETHIFCTRL_STATE_DOWN;

                    /* Update the switch state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                    EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                }
            }
        }
        break;

        default:
            /* Do Nothing */
        break;
    }
}

#endif /* #if( ETHIF_SWITCH_CONFIGURED == STD_ON ) */

/**
 ******************************************************************************************************************************
 * \module description
 * Called by EthIf_Prv_Trigger_StateTransitions(), to trigger all possible state transitions for EthIfCtrl having no reference
 * to either Trcv/Switch/SwitchPortGroup.
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered.
 * \param lCtrlReqMode_en            : Ctrl Mode requested by EthIf for the current EthIfCtrl.
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
static FUNC( void, RBA_ETHIF_CODE ) EthIf_No_Ref_StateTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8,
                                                                   VAR ( Eth_ModeType,     AUTOMATIC )     lCtrlReqMode_en  )
{
    /* Local variables declaration */
    Std_ReturnType   lStdRetType_en;

    /* Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* If requested control mode is active */
    if( lCtrlReqMode_en == ETH_MODE_ACTIVE )
    {
        /* Request physical controller for initialization */
        lStdRetType_en = EthIf_Prv_ControllerInit( lEthIfCtrlIdx_u8 );

        if( lStdRetType_en == E_OK )
        {
         /* Request the controller mode to Active */
            lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                          ETH_MODE_ACTIVE );
        }

        if( lStdRetType_en == E_OK )
        {
            /* Indicate the controller mode to EthSM */
            EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                      ETH_MODE_ACTIVE );

            /* Indicate the link status as active to EthSM */
            EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                    ETHTRCV_LINK_STATE_ACTIVE );
        }
    }/* If the requested controller mode is down */
    else if( lCtrlReqMode_en == ETH_MODE_DOWN )
    {
        /* Set the controller mode to down */
        lStdRetType_en = EthIf_Prv_SetControllerMode( lEthIfCtrlIdx_u8,
                                                      ETH_MODE_DOWN );

        if( lStdRetType_en == E_OK )
        {
            /* If setting of mode down is successful, indicate mode to EthSM */
            EthSM_CtrlModeIndication( lEthIfCtrlIdx_u8,
                                      ETH_MODE_DOWN );

            /* Indicate the link state as down to EthSM */
            EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8,
                                    ETHTRCV_LINK_STATE_DOWN );
        }
    }
    else
    {
        /* Do Nothing */
    }
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif /* ETHIF_CONFIGURED */
