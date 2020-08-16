
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"
#if (!defined(ETH_AR_RELEASE_MAJOR_VERSION) || (ETH_AR_RELEASE_MAJOR_VERSION != ETHIF_AR_RELEASE_MAJOR_VERSION))
#error "Eth AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETH_AR_RELEASE_MINOR_VERSION) || ((ETH_AR_RELEASE_MINOR_VERSION != ETHIF_AR_RELEASE_MINOR_VERSION) && (ETH_AR_RELEASE_MINOR_VERSION != 0)))
#error "Eth AUTOSAR minor version undefined or mismatched"
#endif

#include "EthTrcv.h"
#if (!defined(ETHTRCV_AR_RELEASE_MAJOR_VERSION) || (ETHTRCV_AR_RELEASE_MAJOR_VERSION != ETHIF_AR_RELEASE_MAJOR_VERSION))
#error "EthTrcv AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHTRCV_AR_RELEASE_MINOR_VERSION) || (ETHTRCV_AR_RELEASE_MINOR_VERSION != ETHIF_AR_RELEASE_MINOR_VERSION))
#error "EthTrcv AUTOSAR minor version undefined or mismatched"
#endif

#if ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))
#include "EthSwt.h"
#endif

#if ( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
#include "BswM_EthIf.h"
#endif

#include "EthIf_Prv.h"

/* DET version check */
#if (ETHIF_DEV_ERROR_DETECT == STD_ON)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != ETHIF_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != ETHIF_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* (ETHIF_DEV_ERROR_DETECT == STD_ON) */

#include "EthSM.h"
#include "EthSM_Cbk.h"
#if (!defined(ETHSM_AR_RELEASE_MAJOR_VERSION) || (ETHSM_AR_RELEASE_MAJOR_VERSION != ETHIF_AR_RELEASE_MAJOR_VERSION))
#error "EthSM AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHSM_AR_RELEASE_MINOR_VERSION) || (ETHSM_AR_RELEASE_MINOR_VERSION != ETHIF_AR_RELEASE_MINOR_VERSION))
#error "EthSM AUTOSAR minor version undefined or mismatched"
#endif

#define ETHIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"
/* EthIf_Init API call status flag */
VAR( EthIf_StateType, AUTOMATIC )                            EthIf_InitStatus_en = ETHCTRL_STATE_UNINIT;

/* EthIf configuration pointer */
P2CONST( EthIf_ConfigType, AUTOMATIC, AUTOMATIC )            EthIf_CfgPtr_pco    = NULL_PTR;

#define ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/

static FUNC( void, RBA_ETHIF_CODE ) EthIf_CtrlLinkStatus_Check( void );

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_Standalone_LinkTransitions( void );
#endif

#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_LinkTransitions( VAR ( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8  );
#endif

#if ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))

static FUNC( void, RBA_ETHIF_CODE ) EthIf_Getlinkstate( VAR( uint8,           AUTOMATIC )                         EthSwtIdx_cu8,
                                                        VAR( uint8,           AUTOMATIC )                         HostPortIdx_cu8,
                                                        VAR( uint8,           AUTOMATIC )                         nrOfPorts_cu8,
                                                        P2CONST( uint8,       AUTOMATIC, AUTOMATIC )              ReferredPorts_pcu8,
                                                        P2VAR( EthTrcv_LinkStateType,  AUTOMATIC, AUTOMATIC )     linkstate );
#endif

/**
 ***************************************************************************************************
 * \module description
 * ETHIF024: Initialises the Ethernet Interface
 * \par Service ID 0x01, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CfgPtr   Points to the implementation specific structure
 *
 * \return  None
 *
 ***************************************************************************************************
 */

FUNC( void, RBA_ETHIF_CODE ) EthIf_Init( P2CONST( EthIf_ConfigType,AUTOMATIC, AUTOMATIC ) CfgPtr )
{
    /* Local Variable declaration */
    uint8     lLoopCntr_u8;

    /* Initialize state to Uninit */
    EthIf_InitStatus_en  = ETHCTRL_STATE_UNINIT;

    /* Initialize global configuration pointer to null pointer */
    EthIf_CfgPtr_pco = NULL_PTR;

#if ( ETHIF_CFG_CONFIGURATION_VARIANT != ETHIF_CFG_VARIANT_PRE_COMPILE )

#if ( ETHIF_DEV_ERROR_DETECT  == STD_ON )

    boolean lCfgValid_b = FALSE;

    /* Loop through all EthIf config sets to check whether CfgPtr is a valid configuration */
    for( lLoopCntr_u8 = 0; lLoopCntr_u8 < ETHIF_NUM_CONFIGSETS; lLoopCntr_u8++ )
    {
        if ( ( &EthIf_ConfigSet[lLoopCntr_u8] ) == CfgPtr ) /* EthIf_Config_aco is the post build data set */
        {
            lCfgValid_b = TRUE;
            break;
        }
    }

    /* Report DET: Development Error: CfgPtr is an invalid configuration */
    ETHIF_REPORT_ERROR_RET_VOID( ( FALSE == lCfgValid_b ), ETHIF_SID_ETHIF_INIT, ETHIF_E_INIT_FAILED )

#endif /* #if (ETHIF_DEV_ERROR_DETECT  == STD_ON) */

    EthIf_CfgPtr_pco = CfgPtr;

#else
    /* Report DET if CfgPtr is not NULL_PTR */
    ETHIF_REPORT_ERROR_RET_VOID( ( NULL_PTR != CfgPtr ), ETHIF_SID_ETHIF_INIT, ETHIF_E_INIT_FAILED )

    /* If the variant is pre-compile (NULL_PTR is passed as input parameter), */
    /* intialize global configuration pointer with default configuration. */
    EthIf_CfgPtr_pco = &EthIf_ConfigSet[0];

    /* Ignore passed parameter. */
    (void)CfgPtr;

#endif

    /* Initialise EthInitFlag to 0 for EthDrv controllers */
    for( lLoopCntr_u8 = 0; ( lLoopCntr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthCtrl_cu8 ) ); lLoopCntr_u8++ )
    {
        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lLoopCntr_u8] )   = ETHIF_ETHCTRLSTATE_UNINIT;
    }

#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )
    /* Initialise all EthTrcv flags to 0 and transceiver indicated mode to ETHTRCV_MODE_DOWN */
    for( lLoopCntr_u8 = 0; ( lLoopCntr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfTrcv_cu8 ) ); lLoopCntr_u8++ )
    {
        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->TrcvInitFlg_pa[lLoopCntr_u8] )  = 0;

        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->Trcv_IndicatedMode_en[lLoopCntr_u8] )  = ETHTRCV_MODE_DOWN;
    }
#endif

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
    /* Initialize the state, link and requested mode of all configured standalone PortGroups */
    for( lLoopCntr_u8 = 0; ( lLoopCntr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfStdAlone_PrtGrps_cu8) ); lLoopCntr_u8++ )
    {
        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lLoopCntr_u8].Standalone_PG_State_en ) = ETHIF_STANDALONE_PG_MODE_DOWN;

        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lLoopCntr_u8].Standalone_PG_LinkStatus_en ) = ETHIF_STANDALONE_PG_LINKSTATE_DOWN;

        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->StandalonePG_Type_pst[lLoopCntr_u8].Standalone_PG_ReqMode_en ) = ETHTRCV_MODE_DOWN;
    }
#endif

#if (( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))
    /* Initialize the switch init state for all configured EthSwtes */
    for( lLoopCntr_u8 = 0; ( lLoopCntr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthSwtes_cu8) ); lLoopCntr_u8++ )
    {
        ( EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lLoopCntr_u8].EthIfSwt_State_en ) = ETHIF_ETHSWTSTATE_UNINIT;
    }

#endif

    /* Initialise the EthIfCtrlMode and EthIfCtrlReqMode to ETH_MODE_DOWN */
    for( lLoopCntr_u8 = 0; ( lLoopCntr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ); lLoopCntr_u8++ )
    {
        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[lLoopCntr_u8] )    = ETH_MODE_DOWN;

        ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlReqMode_pa[lLoopCntr_u8] ) = ETH_MODE_DOWN;

        ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lLoopCntr_u8].EthIfCtrlState_en ) = ETHIF_ETHIFCTRL_STATE_DOWN;

        ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lLoopCntr_u8].EthIfCtrl_LinkState_en ) = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;

        /* Check if transceivers are configured, by checking for NULL_PTR */
        if( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa != NULL_PTR )
        {
            /* Initialize Trcv error to FALSE */
            ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrl_TrcvError_pa[lLoopCntr_u8] ) = FALSE;
        }
    }

    EthIf_InitStatus_en  = ETHCTRL_STATE_INIT;
	#if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )
		EthIf_Prv_ResetPhysAddrFilterReferences();
	#endif
}

/**
 ***************************************************************************************************
 * \module description
 * ETHIF082: Returns the version information of this module
 * \par Service ID 0x0b, Synchronous, Non Reentrant
 *
 * Parameter Out:
 * \param VersionInfoPtr    Version information of this module
 *
 * \return  None
 *
 ***************************************************************************************************
 */
#if(ETHIF_VERSIONINFO_API == STD_ON)

FUNC( void, RBA_ETHIF_CODE ) EthIf_GetVersionInfo(  P2VAR(Std_VersionInfoType,AUTOMATIC, AUTOMATIC) VersionInfoPtr )
{

    /* Report DET : Development Error for Invalid Configuration Pointer */
    ETHIF_REPORT_ERROR_RET_VOID( ( VersionInfoPtr == NULL_PTR ), ETHIF_SID_ETHIF_GETVERSIONINFO, ETHIF_E_PARAM_POINTER)

    VersionInfoPtr->vendorID            = ETHIF_VENDOR_ID;
    VersionInfoPtr->moduleID            = ETHIF_MODULE_ID;
    VersionInfoPtr->sw_major_version    = ETHIF_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version    = ETHIF_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version    = ETHIF_SW_PATCH_VERSION;

}
#endif

/*
***************************************************************************************************
* Scheduled
***************************************************************************************************
*/

/**
***************************************************************************************************
* \module description
* ETHIF097: The function checks for new received frames and issues transmission confirmations in polling mode.
* It checks also for transceiver state changes.
* \par Service ID 0x20, FIXED_CYCLIC
*
* \return
*
***************************************************************************************************
*/
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionRx( void )
{
#if (ETHIF_ENABLE_RX_INTERRUPT  != STD_ON)

    Eth_RxStatusType   lRxStatus_en;
    uint8              lEthCtrlNr_u8;
    uint16             lRxIndicationIteration_u16;

    /* Initialise local variables */
    lRxStatus_en               = ETH_NOT_RECEIVED;
    lEthCtrlNr_u8              = 0;
    lRxIndicationIteration_u16 = 0;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_MAINFUNCTIONRX, ETHIF_E_NOT_INITIALIZED)

    /* Trigger reception of all frames from given controller */
    for( lEthCtrlNr_u8 = 0; lEthCtrlNr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthCtrl_cu8 ); lEthCtrlNr_u8++ )
    {
        /* Call Eth_Receive() only if EthCtrl is set to ETHIF_ETHCTRLSTATE_ACTIVE */
        if ( ETHIF_ETHCTRLSTATE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlNr_u8] ) )
        {
            lRxStatus_en = ETH_RECEIVED_MORE_DATA_AVAILABLE;

            /* Receive frames as per configuration parameter EthIfRxIndicationIterations or until there are no more frames to receive whichever is earliest */
            for( lRxIndicationIteration_u16 = 0;
                 ( ( lRxIndicationIteration_u16 < ETHIF_RX_INDICATION_ITERATIONS ) && ( ETH_RECEIVED_MORE_DATA_AVAILABLE == lRxStatus_en ) ) ;
                 lRxIndicationIteration_u16++)
            {
                Eth_Receive( lEthCtrlNr_u8,
                             &lRxStatus_en );
            }
        }
    }
#endif
}

/**
***************************************************************************************************
* \module description
* ETHIF113: The function issues transmission confirmations in polling mode. It checks also for transceiver state changes.
* \par Service ID 0x21, FIXED_CYCLIC
*
* \return
*
***************************************************************************************************
*/
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionTx( void )
{
#if ( ETHIF_ENABLE_TX_INTERRUPT  != STD_ON )
    uint8  lEthCtrlNr_u8;
#endif

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_MAINFUNCTIONTX, ETHIF_E_NOT_INITIALIZED )

#if ( ETHIF_ENABLE_TX_INTERRUPT  != STD_ON )
    /* Call TxConfirmation Once for each EthCtrl */
    for( lEthCtrlNr_u8 = 0; lEthCtrlNr_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthCtrl_cu8 ); lEthCtrlNr_u8++ )
    {   /* Call Eth_TxConfirmation() only if EthCtrl is set to ETHIF_ETHCTRLSTATE_ACTIVE */
        if ( ETHIF_ETHCTRLSTATE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthCtrlState_pa[lEthCtrlNr_u8] ) )
        {
            Eth_TxConfirmation( lEthCtrlNr_u8 );
        }
    }
#endif
}

/********************************************************************************************************************/
/* EthIf_MainFunctionState() - The function is polling the link state of the used communication hardware            */
/* (Ethernet transceiver, Ethernet switch ports).                                                                   */
/*                                                                                                                  */
/* Input Parameters :   none                                                                                        */
/*                                                                                                                  */
/* Return  :  none                                                                                                  */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionState( void )
{

    /* local variable declaration */
    static uint8                     EthIf_MainFuncCntr_u8   = 0;      /* Transceiver link state check Main Function Scheduling counter */

#if(ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
    uint8                            lSwitchIdx_u8;
    uint8                            lloopIdx_u8;
    EthIf_EthSwt_PortStateType_tst*  lEthIfSwitch_PortState_pst;
#endif

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_MAINFUNCTIONSTATE, ETHIF_E_NOT_INITIALIZED )

#if(ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
    /* check for Port Off delay timer */
    /* Loop through all the EthSwtes */
    for( lSwitchIdx_u8 = 0; lSwitchIdx_u8 < EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthSwtes_cu8; lSwitchIdx_u8++ )
    {
        /* Fetch the individual hardware ports structure */
        lEthIfSwitch_PortState_pst = EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lSwitchIdx_u8].EthIf_SwtPort_past;

        /* Loop through all the configured SwitchPorts */
        for( lloopIdx_u8 = 0; lloopIdx_u8 <= EthIf_CfgPtr_pco->EthIfSwtConfig_pst[lSwitchIdx_u8].LastPortIdx_cu8; lloopIdx_u8++ )
        {
            /* Check whether the port off delay timer has been started */
            if(( lEthIfSwitch_PortState_pst[lloopIdx_u8].PortIdx_cu8 != 0xFFU ) &&
               ( lEthIfSwitch_PortState_pst[lloopIdx_u8].ActiveCnt_u8 == 0U ) &&
               ( lEthIfSwitch_PortState_pst[lloopIdx_u8].PortOffDelay_u32 > 0U ) &&
               ( lEthIfSwitch_PortState_pst[lloopIdx_u8].PortOffDelay_u32 < ETHIF_PORT_SWITCHOFF_DELAY ))
            {
                /* If the timer has been started, but not timed out, increment the timer */
                lEthIfSwitch_PortState_pst[lloopIdx_u8].PortOffDelay_u32 += ETHIF_MAINFUNCTION_STATE_PERIOD;
            }
        }
    }

    /* Call API to trigger state transitions of standalone EthIf SwitchPortGroups */
    EthIf_Prv_StandalonePG_StateTransitions();

    /* Check if Port active timer has been started */
    if( EthIf_PortActiveTime_u32 > 0U )
    {
        /* Decrement the PortActiveTime if the timer has been started and not reached to zero */
        EthIf_PortActiveTime_u32--;
    }
#endif

    /* Call API to trigger state transitions for all EthIf Controllers. */
    EthIf_Prv_Trigger_StateTransitions();

    /* Increment counter for link state monitoring */
    EthIf_MainFuncCntr_u8++;

    /* Check for the transceiver/Switch/Switch PortGroups link state is to be read or not */
    if ( EthIf_MainFuncCntr_u8 == ETHIF_TRCV_LINKSTATECHGMAIN_RELOAD )
    {
        /* Call API to poll for hardware link status for all EthIfControllers */
        EthIf_CtrlLinkStatus_Check();

#if(ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
        /* Trigger API for standalone port groups link status check */
        EthIf_PrtGrp_Standalone_LinkTransitions();
#endif

        /* Set EthIf_MFSchCntr to 0 */
        EthIf_MainFuncCntr_u8 = 0U;
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_MainFunctionState(), to check link status of transceiver/Switch/EthIf SwitchPortGroups
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
static FUNC( void, RBA_ETHIF_CODE ) EthIf_CtrlLinkStatus_Check( void )
{
    /* Local variables declaration */
    uint8                                       lEthIfCtrlIdx_u8;
    EthIf_Trcv_Swt_PortGrp_RefType_ten          lEthIf_Trcv_Swt_PortGrp_RefType_en;

#if ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))
    EthTrcv_LinkStateType                       linkstate_en;
#endif

#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )
    EthIf_Swt_PortGrpConfig_tst*                lEthIf_Swt_PortGrp_pst;
#endif

    /* Loop through all EthIf Ctrls */
   for( lEthIfCtrlIdx_u8 = 0; (lEthIfCtrlIdx_u8 < ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ) ; lEthIfCtrlIdx_u8++ )
   {
       /* Fetch the reference type of the EthIfController */
       lEthIf_Trcv_Swt_PortGrp_RefType_en =  EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvSwtPortGrp_RefType_en;

       /* Based on the reference call the particular link transition APIs */
       switch( lEthIf_Trcv_Swt_PortGrp_RefType_en )
       {
           /* If the reference is a transceiver */
           case ETHIF_TRCV:
           {
#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )
               /* Call the transceiver link status check  API */
               EthIf_Trcv_LinkTransitions( lEthIfCtrlIdx_u8 );
#endif
           }
           break;


           /* If the reference is a EthIfSwitchPortGroup of semantic Control or Link info */
           case ETHIF_PORTGRP_CTRL:
           case ETHIF_PORTGRP_LINKINFO:
           {
#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )
               /* Fetch the EthIf Portgroup structure of the EthIfCtrl */
               lEthIf_Swt_PortGrp_pst = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].SwtPortGrp_pst;

               /* Poll for link status if the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN or ETHIF_ETHIFCTRL_STATE_ACTIVE */
               if(( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en == ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN ) ||
                  ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en == ETHIF_ETHIFCTRL_STATE_ACTIVE ) )
               {
                   /* Call the Portgroup link status API check */
                   EthIf_Getlinkstate( lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8,
                                       lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8,
                                       lEthIf_Swt_PortGrp_pst->nrOfPorts_cu8,
                                       lEthIf_Swt_PortGrp_pst->RefPorts_cpu8,
                                       &linkstate_en );

                   if(( linkstate_en == ETHTRCV_LINK_STATE_DOWN ) &&
                      ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en == ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE ))
                   {
                       EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_DOWN );

                       /* Set the link status of the PortGroup to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                   }
                   else if(( linkstate_en == ETHTRCV_LINK_STATE_ACTIVE ) &&
                           ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en == ETHIF_ETHIFCTRL_LINKSTATE_DOWN ))
                   {
                       /* Indicate link state active to EthSM */
                       EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_ACTIVE );

                       /* The link status of the Port group is considered active if the host port and atleast one non-empty port link is active */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE;
                   }
                   else
                   {
                       /* Do Nothing */
                   }
               }
#endif /* #if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ) */
           }
           break;

           /* If the reference is a switch */
           case ETHIF_SWITCH:
           {
#if( ETHIF_SWITCH_CONFIGURED == STD_ON )
               /* Poll the EthIfSwitch link status if the state of the EthIfSwitch is ETHIF_ETHIFCTRL_STATE_ACTIVE */
               if( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en == ETHIF_ETHIFCTRL_STATE_ACTIVE )
               {
                   /* Call the Portgroup link status API check */
                   EthIf_Getlinkstate( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthSwtIdx_cu8,
                                       EthIf_CfgPtr_pco->EthIfSwtConfig_pst[EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthSwtIdx_cu8].HostPortIdx_cu8,
                                       EthIf_CfgPtr_pco->EthIfSwtConfig_pst[EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthSwtIdx_cu8].nrOfStdPorts_cu8,
                                       EthIf_CfgPtr_pco->EthIfSwtConfig_pst[EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthSwtIdx_cu8].RefStdPorts_cpu8,
                                       &linkstate_en );

                   if(( linkstate_en == ETHTRCV_LINK_STATE_DOWN ) &&
                      ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en == ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE ))
                   {
                       EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_DOWN );

                       /* Set the link status of the EthIfCtrl to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                   }
                   else if(( linkstate_en == ETHTRCV_LINK_STATE_ACTIVE ) &&
                           ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en == ETHIF_ETHIFCTRL_LINKSTATE_DOWN ))
                   {
                       /* Indicate link state active to EthSM */
                       EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_ACTIVE );

                       /* The link status of the Port group is considered active if the host port and atleast one non-empty port link is active */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE;
                   }
                   else
                   {
                       /* Do Nothing */
                   }
               }
#endif /* #if( ETHIF_SWITCH_CONFIGURED == STD_ON ) */
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
 ***********************************************************************************************************************
 * \module description
 * Called by EthIf_CtrlLinkStatus_Check(), to trigger all possible link transitions for EthIfCtrl referring to a transceiver
 *
 * Parameter In:
 * \param lEthIfCtrlIdx_u8           : Index of EthIfCtrl for which state transitions needs to be triggered
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 *
 * \return  None
 *
 ***********************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Trcv_LinkTransitions( VAR( uint8,           AUTOMATIC )      lEthIfCtrlIdx_u8  )
{
    /* Local variables declaration */
    EthTrcv_LinkStateType                      lTrcvLinkState_en;
    Std_ReturnType                             lStdRetType_en;
    uint8                                      lTrcvIdx_u8;

    /* Initialise local variable */
    lStdRetType_en  = E_NOT_OK;
    lTrcvIdx_u8 = EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].TrcvIdx_cu8;

    /* Check the link status if the state of the EthIfCtrl is ETHIF_ETHIFCTRL_STATE_ACTIVE */
    if(( ETHIF_ETHIFCTRL_STATE_ACTIVE == ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrlState_en )))
    {
        /* Get the transceiver link status of the physical transceiver */
        lStdRetType_en = EthTrcv_GetLinkState( lTrcvIdx_u8,
                                               (&lTrcvLinkState_en ) );

       /* If the link status was read out successfully */
       if( lStdRetType_en == E_OK )
       {
           /* Check the link state of the EthIfCtrl */
           switch( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en )
           {
               /* If the link state is down */
               case ETHIF_ETHIFCTRL_LINKSTATE_DOWN:
               {
                   /* Call EthSM_TrcvlinkStateChg() API, if the state of EthIfCtrl is ETHIF_ETHIFCTRL_LINKSTATE_DOWN and link ACTIVE is returned */
                   if( ETHTRCV_LINK_STATE_ACTIVE == lTrcvLinkState_en )
                   {
                       EthSM_TrcvLinkStateChg( lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_ACTIVE );

                       /* Set the link state to ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE;
                   }
               }
               break;

               /* If the link state of EthIfCtrl is ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE */
               case ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE:
               {
                   /* Call EthSM_TrcvlinkStateChg() API, if the state of EthIfCtrl is ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE and link state is DOWN */
                   if (  ETHTRCV_LINK_STATE_DOWN == lTrcvLinkState_en )
                   {
                       EthSM_TrcvLinkStateChg(  lEthIfCtrlIdx_u8, ETHTRCV_LINK_STATE_DOWN );

                       /* Update EthIf Trcv state to ETHIF_ETHIFCTRL_LINKSTATE_DOWN */
                       EthIf_CfgPtr_pco->EthIfControllerConfig_pst[lEthIfCtrlIdx_u8].EthIfCtrl_LinkState_en = ETHIF_ETHIFCTRL_LINKSTATE_DOWN;
                   }
               }
               break;

               default:
                   /*Do Nothing */
               break;
           }
       }
    }
}
#endif

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )

/**
 ***************************************************************************************************
 * \module description
 * Called by EthIf_MainFunctionState(), to trigger all possible link transitions for EthIf SwitchPortGroups with no semantics
 *
 * Parameter In:
 * \param None
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
static FUNC( void, RBA_ETHIF_CODE ) EthIf_PrtGrp_Standalone_LinkTransitions( void )
{
    /* Local variables declaration */
    uint8                                       lloopIdx_u8;
    EthIf_Swt_PortGrpConfig_tst*                lEthIf_Swt_PortGrp_pst;
    uint8                                       lPortGrpIdx_u8;
    EthIf_Standalone_SwtPrtGrpStateType_ten*    lEthIfSwt_PortGrpState_pen;
    EthIf_LinkStateType*                        lEthIfSwt_PortGrpLink_pen;
    EthIf_StandalonePG_Type_tst*                lEthIf_StandalonePG_Type_pst;
    EthTrcv_LinkStateType                       linkstate_en;

    /* loop through all configured EthIfSwitchPortGroups */
    for( lPortGrpIdx_u8 = 0; ( lPortGrpIdx_u8 < EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfSwtPortGrps_cu8 );
         lPortGrpIdx_u8++ )
    {   /* If the PortGroup is standalone */
        if(EthIf_CfgPtr_pco->EthIfPrtGrpConfig_pst[lPortGrpIdx_u8].semantic_en == ETHIF_PORTGRP_UNREFERENCED )
        {
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

            /* Fetch the PG structure */
            lEthIf_Swt_PortGrp_pst = &(EthIf_CfgPtr_pco->EthIfPrtGrpConfig_pst[lPortGrpIdx_u8]);

            /* Fetch the state of the standalone PG */
            lEthIfSwt_PortGrpState_pen = &(lEthIf_StandalonePG_Type_pst->Standalone_PG_State_en);

            /* Fetch the link state of the standalone PG */
            lEthIfSwt_PortGrpLink_pen = &(lEthIf_StandalonePG_Type_pst->Standalone_PG_LinkStatus_en);

            /* Poll for link status if the state is Startup, active or waitdown */
            if(( *lEthIfSwt_PortGrpState_pen == ETHIF_STANDALONE_PG_MODE_STARTUP ) ||
               ( *lEthIfSwt_PortGrpState_pen == ETHIF_STANDALONE_PG_MODE_ACTIVE )  ||
               ( *lEthIfSwt_PortGrpState_pen == ETHIF_STANDALONE_PG_MODE_WAITDOWN ))
            {

                EthIf_Getlinkstate( lEthIf_Swt_PortGrp_pst->EthSwtIdx_cu8,
                                    lEthIf_Swt_PortGrp_pst->HostPortIdx_cu8,
                                    lEthIf_Swt_PortGrp_pst->nrOfPorts_cu8,
                                    lEthIf_Swt_PortGrp_pst->RefPorts_cpu8,
                                    &linkstate_en );

                if(( linkstate_en == ETHTRCV_LINK_STATE_DOWN ) &&
                   ( *lEthIfSwt_PortGrpLink_pen == ETHIF_STANDALONE_PG_LINKSTATE_ACTIVE ))
                {
                    /* Call BswM Link state info API */
                    BswM_EthIf_PortGroupLinkStateChg( lPortGrpIdx_u8, ETHTRCV_LINK_STATE_DOWN );

                    /* Set the state of the standalone PG to ETHIF_STANDALONE_PG_LINKSTATE_DOWN */
                    *lEthIfSwt_PortGrpLink_pen = ETHIF_STANDALONE_PG_LINKSTATE_DOWN;
                }
                else if(( linkstate_en == ETHTRCV_LINK_STATE_ACTIVE )  &&
                        (*lEthIfSwt_PortGrpLink_pen == ETHIF_STANDALONE_PG_LINKSTATE_DOWN))
                {
                    /* The link status of the Port group is considered active if the host port and atleast one non-empty port link is active */
                    *lEthIfSwt_PortGrpLink_pen = ETHIF_STANDALONE_PG_LINKSTATE_ACTIVE;

                    /* Call BswM Link state info API */
                    BswM_EthIf_PortGroupLinkStateChg( lPortGrpIdx_u8, ETHTRCV_LINK_STATE_ACTIVE );
                }
                else
                {
                    /* Do nothing */
                }
            }/* if(( *lEthIfSwt_PortGrpState_pen == ETHIF_STANDALONE_PG_MODE_STARTUP ) || */
        }
    }
}
#endif /* #if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON ) */

#if ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))

/**
 ***********************************************************************************************************************
 * \module description
 * EthIf_Getlinkstate: This API returns the link status of a EthIfSwitch/EthIfSwitchPortGroup as per link accumulation
 *
 * Parameter In:
 * \param EthSwtIdx_cu8           : Index of EthSwt
 * \param HostPortIdx_cu8         : Host port index of the Switch/SwitchPortGroup
 * \param nrOfPorts_cu8           : Number of ports the Switch/SwitchPortGroup
 * \param nrOfPorts_cu8           : Pointer to the standard ports of the Switch/SwitchPortGroup
 * Parameters InOut:
 * \param None
 *
 * Parameters Out: None
 * \param linkstate           : Link status of the Switch/SwitchPortGroup as per Link accumulation.
 * \return  None
 *
 ***********************************************************************************************************************
 */
static FUNC( void, RBA_ETHIF_CODE ) EthIf_Getlinkstate( VAR( uint8,           AUTOMATIC )                         EthSwtIdx_cu8,
                                                        VAR( uint8,           AUTOMATIC )                         HostPortIdx_cu8,
                                                        VAR( uint8,           AUTOMATIC )                         nrOfPorts_cu8,
                                                        P2CONST( uint8,       AUTOMATIC, AUTOMATIC )              ReferredPorts_pcu8,
                                                        P2VAR( EthTrcv_LinkStateType,  AUTOMATIC, AUTOMATIC )     linkstate )
{
    /* Local variables declaration */
    EthTrcv_LinkStateType                       lTrcvLinkState_en;
    Std_ReturnType                              lStdRetType_en;
    uint8                                       lloopIdx_u8;

    /* Get the link state of the host port */
    lStdRetType_en = EthSwt_GetLinkState( EthSwtIdx_cu8,
                                          HostPortIdx_cu8,
                                          &lTrcvLinkState_en );

    if( E_OK == lStdRetType_en )
    {   /* If link state of the host port is down/undefined, return the link status as down */
        if( lTrcvLinkState_en != ETHTRCV_LINK_STATE_ACTIVE )
        {
            *linkstate = ETHTRCV_LINK_STATE_DOWN;
        }
        else
        {   /* If host port is active */
            /* Check for other empty role ports status. If atleast one is in active state then the link status of the port group is ACTIVE */
            for( lloopIdx_u8 = 0; lloopIdx_u8 < nrOfPorts_cu8; lloopIdx_u8++ )
            {
                /* Get the link status of the port */
                lStdRetType_en = EthSwt_GetLinkState( EthSwtIdx_cu8,
                                                   ReferredPorts_pcu8[lloopIdx_u8],
                                                   &lTrcvLinkState_en );

                /* If the link state is active */
                if(( lStdRetType_en == E_OK ) && ( lTrcvLinkState_en == ETHTRCV_LINK_STATE_ACTIVE ))
                {
                    /* Return the link state as active if atleast host port and one standard port is up */
                    *linkstate = ETHTRCV_LINK_STATE_ACTIVE;

                    break;
                }
            }

            /* If host port is active, but no other ports are active, then the link status is down */
            if( lloopIdx_u8 == nrOfPorts_cu8 )
            {
                *linkstate = ETHTRCV_LINK_STATE_DOWN;
            }
        }
    }
}

#endif /* ( ( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )) */

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */
