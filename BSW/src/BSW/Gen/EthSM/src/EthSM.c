
#include "EthSM.h"

#ifdef ETHSM_CONFIGURED

#include "EthIf.h"
#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != ETHSM_AR_RELEASE_MAJOR_VERSION))
#error "EthIf AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != ETHSM_AR_RELEASE_MINOR_VERSION))
#error "EthIf AUTOSAR minor version undefined or mismatched"
#endif

#include "BswM_EthSM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != ETHSM_AR_RELEASE_MAJOR_VERSION))
#error "BswM AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != ETHSM_AR_RELEASE_MINOR_VERSION))
#error "BswM AUTOSAR minor version undefined or mismatched"
#endif

#include "EthSM_PbCfg.h"
#include "EthSM_Prv.h"

/* DET version check */
#if (ETHSM_DEV_ERROR_DETECT == STD_ON)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != ETHSM_AR_RELEASE_MAJOR_VERSION))
#error " DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != ETHSM_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* (ETHSM_DEV_ERROR_DETECT == STD_ON) */

#define ETHSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthSM_MemMap.h"

/*
***************************************************************************************************
* Global variable declaration
***************************************************************************************************
*/

/* EthSM status variables. Status are stored on EthIfCtrlIdx based*/
VAR( EthSM_NetworkModeStateType, AUTOMATIC )                EthSM_NetState_aen[ETHSM_NUM_OF_ETHIFCTRL];       /* EthSM network current status per EthIfCtrlIdx                                           */
VAR( ComM_ModeType,              AUTOMATIC )                EthSM_ComMReqMode_au8[ETHSM_NUM_OF_ETHIFCTRL];    /* ComM mode request stored per EthIfCtrlIdx                                               */
VAR( Eth_ModeType,               AUTOMATIC )                EthSM_EthIfCtrlMode_aen[ETHSM_NUM_OF_ETHIFCTRL];  /* EthIfCtrl mode provided by EthSM_CtrlModeIndication() and is stored per EthIfCtrlIdx    */
VAR( EthTrcv_LinkStateType,      AUTOMATIC )                EthSM_TrcvLinkState_aen[ETHSM_NUM_OF_ETHIFCTRL];  /* Trcv link status provided by EthSM_TrcvLinkStateChg() and is stored per EthIfCtrlIdx    */
VAR( TcpIp_StateType,            AUTOMATIC )                EthSM_TcpIpState_aen[ETHSM_NUM_OF_ETHIFCTRL];     /* TcpIpCtrl status provided by EthSM_TcpIpModeIndication() and is stored per EthIfCtrlIdx */
VAR( boolean,                    AUTOMATIC )                EthSM_HwError_ab[ETHSM_NUM_OF_ETHIFCTRL];         /* Stores unexpected hardware mode DOWN indication and is stored per EthIfCtrl.           */


#define ETHSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthSM_MemMap.h"

#define ETHSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthSM_MemMap.h"

P2CONST( EthSM_ConfigType, AUTOMATIC, AUTOMATIC )    EthSM_EthChnlPtr_pco    = NULL_PTR;

#define ETHSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthSM_MemMap.h"

#define ETHSM_START_SEC_CODE
#include "EthSM_MemMap.h"
/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Offline(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                             VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8 );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_SubstateOfflineWaitCtrlModeActive(    VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                                         VAR( Eth_ModeType,            AUTOMATIC ) lEthSM_EthIfCtrlMode_en,
                                                                                         VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                                                         P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitTrcvLink(  VAR( uint8,                 AUTOMATIC ) lCtrlIdx_u8,
                                                                  VAR( uint8,                 AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                                  VAR( EthTrcv_LinkStateType, AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                                  P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitOnline(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                                VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                                VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                                P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Online(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                            VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                            VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                            VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                            P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Onhold(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                            VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                            VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                            VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                            P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitOffline( VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                                P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb );

/**
 ***************************************************************************************************
 * \module description
 * ETHSM00043: This function initialize the EthSM.
 * \par Service ID 0x07, Synchronous, Non Reentrant
 *
 * Parameters In:
 * \param None
 *
 *  Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC( void, RBA_ETHSM_CODE ) EthSM_Init( void )
{
    VAR( uint8, AUTOMATIC )   lCtrlIdx_u8;

    /* Initialize global variables */
    for( lCtrlIdx_u8 = 0; lCtrlIdx_u8 < ETHSM_NUM_OF_ETHIFCTRL; lCtrlIdx_u8++ )
    {
        EthSM_NetState_aen[lCtrlIdx_u8]      = ETHSM_STATE_OFFLINE;
        EthSM_ComMReqMode_au8[lCtrlIdx_u8]   = COMM_NO_COMMUNICATION;
        EthSM_EthIfCtrlMode_aen[lCtrlIdx_u8] = ETH_MODE_DOWN;
        EthSM_TrcvLinkState_aen[lCtrlIdx_u8] = ETHTRCV_LINK_STATE_DOWN;
        EthSM_TcpIpState_aen[lCtrlIdx_u8]    = TCPIP_STATE_OFFLINE;
        EthSM_HwError_ab[lCtrlIdx_u8]        = FALSE;
    }

    EthSM_EthChnlPtr_pco = ( &( EthSM_NetConfig[0] ) );
}

/**
 ***************************************************************************************************
 * \module description
 * ETHSM00046: This service puts out the version information of this module.
 * \par Service ID 0x02, Synchronous, Reentrant
 *
 * Parameters In:
 * \param None
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param versioninfo : Pointer where to put out the version information.
 *
 * \return  None
 *
 ***************************************************************************************************
 */
#if(ETHSM_VERSIONINFO_API == STD_ON)
FUNC( void, RBA_ETHSM_CODE ) EthSM_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, AUTOMATIC ) versioninfo )
{
    /* Report DET if versioninfo is a Null Pointer */
    ETHSM_REPORT_ERROR_RET_VOID( ( NULL_PTR == versioninfo ), ETHSM_SID_ETHSM_GETVERSIONINFO, ETHSM_E_PARAM_POINTER )

    versioninfo->vendorID            = ETHSM_VENDOR_ID;
    versioninfo->moduleID            = ETHSM_MODULE_ID;
    versioninfo->sw_major_version    = ETHSM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version    = ETHSM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version    = ETHSM_SW_PATCH_VERSION;
}
#endif


/**
 ***************************************************************************************************
 * \module description
 * ETHSM00050: Handles the communication mode and sets the Ethernet network active or passive.
 * \par Service ID 0x05, Asynchronous, Non Reentrant
 *
 * Parameters In:
 * \param NetworkHandle : Handle of destinated communication network for request
 * \param ComM_Mode     : Requested communication mode
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  Std_ReturnType {E_OK: Service accepted; E_NOT_OK: Service denied}
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, RBA_ETHSM_CODE ) EthSM_RequestComMode(    VAR( NetworkHandleType, AUTOMATIC )     NetworkHandle,
                                                                VAR( ComM_ModeType, AUTOMATIC )         ComM_Mode )
{
    VAR( uint8, AUTOMATIC )   lCtrlIdx_u8;

    /* Report DET error if module is not initialized */
    ETHSM_REPORT_ERROR_RET_VALUE( ( NULL_PTR == EthSM_EthChnlPtr_pco ),                \
                                  ETHSM_SID_ETHSM_REQUESTCOMMODE, ETHSM_E_UNINIT, E_NOT_OK )

    /* Report DET error if ComM Mode is invalid */
    ETHSM_REPORT_ERROR_RET_VALUE( ( ( ComM_Mode != COMM_NO_COMMUNICATION ) &&         \
                                  ( ComM_Mode != COMM_FULL_COMMUNICATION ) &&         \
                                  ( ComM_Mode != COMM_SILENT_COMMUNICATION ) ),       \
                                 ETHSM_SID_ETHSM_REQUESTCOMMODE,                      \
                                 ETHSM_E_INVALID_NETWORK_MODE, E_NOT_OK )

     /* Loop through EthSM configuration structure and get the EthIfCtrlIdx corresponding to the ComM channel Id. (EthSM structure array is sorted according to EthIfCTrlIdx )  */
     for(lCtrlIdx_u8 = 0; lCtrlIdx_u8 < ETHSM_NUM_OF_ETHIFCTRL; lCtrlIdx_u8++)
     {
         if(EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 == NetworkHandle)
         {
             break;
         }
     }

    /* Report DET error if ComM channel Id is invalid */
    ETHSM_REPORT_ERROR_RET_VALUE( (ETHSM_NUM_OF_ETHIFCTRL == lCtrlIdx_u8),  \
                                  ETHSM_SID_ETHSM_REQUESTCOMMODE,                     \
                                  ETHSM_E_INVALID_NETWORK_HANDLE, E_NOT_OK )

    /* EthSM shall store the request only if requested ComM mode is COMM_FULL_COMMUNICATION or COMM_NO_COMMUNICATION */
    /* If ComM requests for COMM_SILENT_COMMUNICATION, EthSM shall return E_OK                                       */
    if( ( COMM_FULL_COMMUNICATION == ComM_Mode) ||
        ( COMM_NO_COMMUNICATION == ComM_Mode ) )
    {
        EthSM_ComMReqMode_au8[lCtrlIdx_u8] = ComM_Mode;
    }

    return E_OK;
}

/**
 ***************************************************************************************************
 * \module description
 * ETHSM00055: This service shall put out the current communication mode of a Ethernet network.
 * \par Service ID 0x04, Asynchronous, Non Reentrant
 *
 * Parameter In:
 * \param NetworkHandle : Network handle whose current communication mode shall be put out
 *
 * Parameters InOut:
 * \param None
 *
 * Parameter Out:
 * \param ComM_ModePtr  : Pointer where to put out the current communication mode
 *
 * \return  Std_ReturnType {E_OK: Service accepted; E_NOT_OK: Service denied}
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, RBA_ETHSM_CODE ) EthSM_GetCurrentComMode( VAR( NetworkHandleType, AUTOMATIC )             NetworkHandle,
                                                                P2VAR( ComM_ModeType, AUTOMATIC, AUTOMATIC )    ComM_ModePtr )
{
    VAR( uint8,                      AUTOMATIC )   lCtrlIdx_u8;

    /* Report DET : Development Error: Module not initialized */
    ETHSM_REPORT_ERROR_RET_VALUE( ( NULL_PTR == EthSM_EthChnlPtr_pco ),                         \
                                  ETHSM_SID_ETHSM_GETCURRENTCOMMODE, ETHSM_E_UNINIT, E_NOT_OK )

    /* Report DET : Development Error: Invalid Pointer */
    ETHSM_REPORT_ERROR_RET_VALUE( ( NULL_PTR == ComM_ModePtr ),                                       \
                                  ETHSM_SID_ETHSM_GETCURRENTCOMMODE, ETHSM_E_PARAM_POINTER, E_NOT_OK )

    /* Loop through EthSM configuration structure and get the EthIfCtrlIdx corresponding to the ComM channel Id. (EthSM structure array is sorted according to EthIfCTrlIdx )  */
    for(lCtrlIdx_u8 = 0; lCtrlIdx_u8 < ETHSM_NUM_OF_ETHIFCTRL; lCtrlIdx_u8++)
    {
        if(EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 == NetworkHandle)
        {
            break;
        }
    }

    /* Report DET : Development Error: Invalid Network Handle */
    ETHSM_REPORT_ERROR_RET_VALUE( ( ETHSM_NUM_OF_ETHIFCTRL == lCtrlIdx_u8 ),                  \
                                  ETHSM_SID_ETHSM_GETCURRENTCOMMODE, ETHSM_E_INVALID_NETWORK_HANDLE, E_NOT_OK )

    switch( EthSM_NetState_aen[lCtrlIdx_u8] )
    {
        case ETHSM_STATE_ONLINE:
        case ETHSM_STATE_ONHOLD:
        case ETHSM_STATE_WAIT_OFFLINE:
        {
            ( * ComM_ModePtr ) = COMM_FULL_COMMUNICATION;
        }
        break;

        case ETHSM_STATE_OFFLINE:
        case ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE:
        case ETHSM_STATE_WAIT_TRCVLINK:
        {
            ( * ComM_ModePtr ) = COMM_NO_COMMUNICATION;
        }
        break;

        case ETHSM_STATE_WAIT_ONLINE:
        {   /* In state WAIT_ONLINE, FULL_COM indication is given if one of the network users is CDD. */
            /* If more than one network user is present, then it is guaranteed that at least one is CDD */
            if(( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_CDD ) ||
               ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 > 1U ) )
            {
                ( * ComM_ModePtr ) = COMM_FULL_COMMUNICATION;
            }
            else
            {
                ( * ComM_ModePtr ) = COMM_NO_COMMUNICATION;
            }
        }
        break;

        default:
        { /* Do nothing */
        }
        break;
    }

    return E_OK;
}


/**
 ***************************************************************************************************
 * \module description
 * ETHSM00035: Cyclic Main Function which is called from the Scheduler.
 * \par Service ID 0x01 , Synchronous, Non Reentrant
 *
 * Parameters In:
 * \param None
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  None
 *
 ***************************************************************************************************
 */

/* HIS METRIC v(G), CALLS VIOLATION IN EthSM_MainFunction: This API contains switch-case and function call for every EthSM state and is not possible to avoid these HIS in-compliances.*/
FUNC( void, RBA_ETHSM_CODE )  EthSM_MainFunction( void )
{
    /* Local variable declaration */
     VAR( boolean,                    AUTOMATIC )       lEthSM_StateChgPossible_b;
     VAR( ComM_ModeType,              AUTOMATIC )       lEthSM_ComMReqMode_u8;
     VAR( Eth_ModeType,               AUTOMATIC )       lEthSM_CtrlMode_en;
     VAR( EthTrcv_LinkStateType,      AUTOMATIC )       lEthSM_TrcvLinkState_en;
     VAR( TcpIp_StateType,            AUTOMATIC )       lEthSM_TcpIpState_en;
     VAR( uint8,                      AUTOMATIC )       lCtrlIdx_u8;

     /* Initialize local variables */
     lEthSM_StateChgPossible_b   = FALSE;

     /* Report DET : Development Error: Module not initialized */
    ETHSM_REPORT_ERROR_RET_VOID( ( NULL_PTR == EthSM_EthChnlPtr_pco ), \
                                   ETHSM_SID_ETHSM_MAINFUNCTION, ETHSM_E_UNINIT )

   /* Loop through all EthIfCtrls */
   for( lCtrlIdx_u8 = 0; lCtrlIdx_u8 < ETHSM_NUM_OF_ETHIFCTRL; lCtrlIdx_u8++)
   {
       /* Locally store requested state/Call back status, to have data consistency during reentrancy  */
       lEthSM_TrcvLinkState_en        = EthSM_TrcvLinkState_aen[lCtrlIdx_u8];
       lEthSM_TcpIpState_en           = EthSM_TcpIpState_aen[lCtrlIdx_u8];
       lEthSM_CtrlMode_en             = EthSM_EthIfCtrlMode_aen[lCtrlIdx_u8];

       /* EthSM_CtrlModeIndication(ETHCTRL_MODE_DOWN) is expected only at ETHSM_STATE_OFFLINE. */
       /* At any other EthSM state it means error in the hardware and EthSM network shall be brought back to ETHSM_STATE_OFFLINE */
       if( FALSE == EthSM_HwError_ab[lCtrlIdx_u8] )
       {
           /* If no error is reported, proceed with ComM requested mode */
           lEthSM_ComMReqMode_u8 = EthSM_ComMReqMode_au8[lCtrlIdx_u8];
       }
       else
       {
           /* Set the requested state to NO_COM */
           lEthSM_ComMReqMode_u8 = COMM_NO_COMMUNICATION;
       }

       /* lEthSM_StateChgPossible_b will be set to TRUE on state transition if there is a possibility of another state transition to happen, within current EthSM main function.  */
        do{
            /*  Clear lEthSM_StateChgPossible_b on each loop */
            lEthSM_StateChgPossible_b = FALSE;

            switch( EthSM_NetState_aen[lCtrlIdx_u8] )
            {
                /* Transition from ETHSM_STATE_OFFLINE to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE */
                case ETHSM_STATE_OFFLINE:
                {
                    EthSM_TransFrm_Offline( lCtrlIdx_u8,
                                            lEthSM_ComMReqMode_u8 );
                }
                break;

                /* Transition from ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE to ETHSM_STATE_WAIT_TRCVLINK/ETHSM_STATE_OFFLINE */
                case ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE:
                {
                    EthSM_TransFrm_SubstateOfflineWaitCtrlModeActive(   lCtrlIdx_u8,
                                                                        lEthSM_CtrlMode_en,
                                                                        lEthSM_ComMReqMode_u8,
                                                                        &lEthSM_StateChgPossible_b );
                }
                break;

                /* Transition from ETHSM_STATE_WAIT_TRCVLINK to ETHSM_STATE_WAIT_ONLINE/ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE */
                case ETHSM_STATE_WAIT_TRCVLINK:
                {
                    EthSM_TransFrm_WaitTrcvLink( lCtrlIdx_u8,
                                                 lEthSM_ComMReqMode_u8,
                                                 lEthSM_TrcvLinkState_en,
                                                 &lEthSM_StateChgPossible_b );
                }
                break;

                /* Transition from ETHSM_STATE_WAIT_ONLINE to ETHSM_STATE_ONLINE/ETHSM_STATE_WAIT_TRCVLINK/ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE */
                case ETHSM_STATE_WAIT_ONLINE:
                {
                    EthSM_TransFrm_WaitOnline( lCtrlIdx_u8,
                                               lEthSM_ComMReqMode_u8,
                                               lEthSM_TrcvLinkState_en,
                                               lEthSM_TcpIpState_en,
                                               &lEthSM_StateChgPossible_b );
                }
                break;

                /* Transition from ETHSM_STATE_ONLINE to ETHSM_STATE_ONHOLD/ETHSM_STATE_WAIT_ONLINE/ETHSM_STATE_WAIT_OFFLINE */
                case ETHSM_STATE_ONLINE:
                {
                    EthSM_TransFrm_Online( lCtrlIdx_u8,
                                           lEthSM_ComMReqMode_u8,
                                           lEthSM_TrcvLinkState_en,
                                           lEthSM_TcpIpState_en,
                                           &lEthSM_StateChgPossible_b );
                }
                break;

                /* Transition from ETHSM_STATE_ONHOLD to ETHSM_STATE_ONLINE/ETHSM_STATE_WAIT_TRCVLINK/ETHSM_STATE_WAIT_OFFLINE */
                case ETHSM_STATE_ONHOLD:
                {
                    EthSM_TransFrm_Onhold(  lCtrlIdx_u8,
                                            lEthSM_ComMReqMode_u8,
                                            lEthSM_TrcvLinkState_en,
                                            lEthSM_TcpIpState_en,
                                            &lEthSM_StateChgPossible_b );
                }
                break;

                /* Transition from ETHSM_STATE_WAIT_OFFLINE to ETHSM_STATE_OFFLINE */
                case ETHSM_STATE_WAIT_OFFLINE:
                {
                    EthSM_TransFrm_WaitOffline( lCtrlIdx_u8,
                                                lEthSM_TcpIpState_en,
                                                &lEthSM_StateChgPossible_b );
                }
                break;

                default:
                { /* Do nothing */
                }
                break;
            }
        }while( FALSE != lEthSM_StateChgPossible_b );
    }
}


/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_OFFLINE
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Offline(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                             VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8 )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,             AUTOMATIC )       lStdRetType_en;

    /*Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* Check whether FULL_COM is requested */
    if( COMM_FULL_COMMUNICATION == lEthSM_ComMReqMode_u8 )
    {
        /* Set EthIfCtrl to ACTIVE */
        lStdRetType_en = EthIf_SetControllerMode( lCtrlIdx_u8,
                                                  ETH_MODE_ACTIVE );

        if( E_OK == lStdRetType_en )
        {
            /* Update the network state */
            EthSM_NetState_aen[lCtrlIdx_u8]  = ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE;
        }
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_EthIfCtrlMode_en    : EthIfCtrl Mode as indicated by EthSM_CtrlModeIndication() for the current network
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 *
 * \return  None
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_SubstateOfflineWaitCtrlModeActive(    VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                                         VAR( Eth_ModeType,            AUTOMATIC ) lEthSM_EthIfCtrlMode_en,
                                                                                         VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                                                         P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,                  AUTOMATIC )       lStdRetType_en;

    /* Transition from ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE to ETHSM_STATE_OFFLINE, if hardware error has occured. */
    if( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION )
    {
        /*Initialize local variable */
        lStdRetType_en = E_OK;

        /* If current EthIfCtrlMode is ETH_MODE_ACTIVE and NO_COM was received, set the EthIfCtrl mode to DOWN */
        if( lEthSM_EthIfCtrlMode_en == ETH_MODE_ACTIVE )
        {
            /* Set EthIfCtrl to DOWN */
            lStdRetType_en = EthIf_SetControllerMode( lCtrlIdx_u8,
                                                      ETH_MODE_DOWN );
        }

        if( lStdRetType_en == E_OK )
        {
            /* Update network state */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_OFFLINE;

            /* Set the status variables to initial value */
            EthSM_EthIfCtrlMode_aen[lCtrlIdx_u8] = ETH_MODE_DOWN;
            EthSM_TrcvLinkState_aen[lCtrlIdx_u8] = ETHTRCV_LINK_STATE_DOWN;
            EthSM_TcpIpState_aen[lCtrlIdx_u8]    = TCPIP_STATE_OFFLINE;

            /* In case of HW error another state transition from ETHSM_STATE_OFFLINE back to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE  */
            /* is possible within current EthSM main function */
            if( FALSE != EthSM_HwError_ab[lCtrlIdx_u8] )
            {
                *lEthSM_StateChgPossible_pb = TRUE;

                /* Clear the hardware error flag */
				EthSM_HwError_ab[lCtrlIdx_u8] = FALSE;
            }
        }
    }
    else if( ETH_MODE_ACTIVE == lEthSM_EthIfCtrlMode_en )
    {
        /* Update network state */
        EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_TRCVLINK;

        /* Inform BswM about the current state */
        BswM_EthSM_CurrentState(  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                  ETHSM_STATE_WAIT_TRCVLINK );

        /* Another state transition from ETHSM_STATE_WAIT_TRCVLINK to ETHSM_STATE_WAIT_ONLINE  */
        /* is possible within current EthSM main function */
        *lEthSM_StateChgPossible_pb = TRUE;
    }
    else
    {
        /* Do nothing */
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_WAIT_TRCVLINK
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 * \param lEthSM_TrcvLinkState_en    : Link state as indicated by EthSM_TrcvLinkStateChg() for the current network
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 * Parameters Out:
 * \param None
 *
 *
 * \return  None
 *
 ***************************************************************************************************
 */
/* HIS METRIC LEVEL VIOLATION IN EthSM_TransFrm_WaitTrcvLink: This function will have different state transitions based on different set of conditions and is not possible to avoid this HIS in-compliance .*/
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitTrcvLink(  VAR( uint8,                 AUTOMATIC )   lCtrlIdx_u8,
                                                                  VAR( uint8,                 AUTOMATIC )   lEthSM_ComMReqMode_u8,
                                                                  VAR( EthTrcv_LinkStateType, AUTOMATIC )   lEthSM_TrcvLinkState_en,
                                                                  P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,                  AUTOMATIC )       lStdRetType_en;
    VAR( uint8,                           AUTOMATIC )       lLoopIdx_u8;
    VAR( ComM_ModeType,                   AUTOMATIC )       lComMCurrMode_en;

    /*Initialize local variable */
    lStdRetType_en    = E_NOT_OK;
    lComMCurrMode_en  = COMM_NO_COMMUNICATION;

    /* If the case is ( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION )  and ( lEthSM_TrcvLinkState_en == ETHTRCV_LINK_STATE_ACTIVE. ),                                                 */
    /* condition ( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION ) carries higher priority, as there will be direct transition                                                   */
    /* ETHSM_STATE_WAIT_TRCVLINK  -> ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE instead of ETHSM_STATE_WAIT_TRCVLINK -> ETHSM_STATE_WAIT_ONLINE -> ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE */

    /* Transition from ETHSM_STATE_WAIT_TRCVLINK to ETHSM_STATE_OFFLINE */
    if ( COMM_NO_COMMUNICATION == lEthSM_ComMReqMode_u8 )
    {
        /* If the EthIfCtrl has reported unexpected DOWN state EthSM network shall be brought back to ETHSM_STATE_OFFLINE */
        /* Hence another state change to ETHSM_STATE_OFFLINE is possible within current EthSM_MainFunction() */
        if( FALSE != EthSM_HwError_ab[lCtrlIdx_u8] )
        {
            *lEthSM_StateChgPossible_pb = TRUE;

            lStdRetType_en = E_OK;
        }
        else
        {
            /* Set EthIfCtrl to DOWN */
            lStdRetType_en = EthIf_SetControllerMode( lCtrlIdx_u8,
                                                      ETH_MODE_DOWN );
        }

        if(E_OK == lStdRetType_en)
        {
            /* Inform BswM about EthSM state change */
            BswM_EthSM_CurrentState (  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                       ETHSM_STATE_OFFLINE );

            /* Update State network state */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_OFFLINE;

            /* Clear the hardware error flag */
			EthSM_HwError_ab[lCtrlIdx_u8] = FALSE;
        }
    }
    /* Transition from ETHSM_STATE_WAIT_TRCVLINK to ETHSM_STATE_WAIT_ONLINE */
    else if(ETHTRCV_LINK_STATE_ACTIVE == lEthSM_TrcvLinkState_en )
    {   /* Loop through all network users for the EthSM network */
        for( lLoopIdx_u8 = 0; lLoopIdx_u8 < ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 ); lLoopIdx_u8++ )
        {
            /* Initialize lStdRetType_en to E_OK. */
            lStdRetType_en = E_OK;

            if( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[lLoopIdx_u8].NetworkUser_en == ETHSM_USER_TCPIP )
            {
                /* Request TcpIp State ONLINE, if network user is TcpIp */
                lStdRetType_en = TcpIp_RequestComMode(  lCtrlIdx_u8,
                                                        TCPIP_STATE_ONLINE);

                /* Break from the loop as only one TcpIp user is possible for an EthSM network. */
                break;
            }
        }

        if( E_OK == lStdRetType_en )
        {
            /* If one of the network user is CDD, then ComM is indicated with FULL_COM */
            if(( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_CDD ) ||
               ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 > 1U ))
            {
                /* Communicate current state to ComM */
                lComMCurrMode_en = COMM_FULL_COMMUNICATION;

                ComM_BusSM_ModeIndication(  ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                              &lComMCurrMode_en );
            }

            /* Inform BswM about the current state */
            BswM_EthSM_CurrentState (   EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                        ETHSM_STATE_WAIT_ONLINE );

            /* Update State network state */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_ONLINE;
        }
    }
    else
    {  /* Do nothing */
    }
}


/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_WAIT_ONLINE
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 * \param lEthSM_TrcvLinkState_en    : Link state as indicated by EthSM_TrcvLinkStateChg() for the current network
 * \param lEthSM_TcpIpState_en       : TcpIp Mode as indicated by EthSM_TcpIpModeIndication() for the current network
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 * \return  None
 *
 ***************************************************************************************************
 */
/* HIS METRIC v(G), LEVEL VIOLATION IN EthSM_TransFrm_WaitOnline: This function will have different state transitions based on different set of conditions and is not possible to avoid these HIS in-compliances .*/
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitOnline(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                                VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                                VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                                P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,             AUTOMATIC )       lStdRetType_en;
    VAR( ComM_ModeType,              AUTOMATIC )       lComMCurrMode_en;
    VAR( uint8,                      AUTOMATIC )       lLoopIdx_u8;

    /*Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* In case multiple conditions are met for the transition, conditions shall be prioritized.       */
    /* Priority to be followed is:                                                                    */
    /* ( lEthSM_TcpIpState_en == TCPIP_STATE_ONLINE )                                                 */
    /* ( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION  )                                            */
    /* ( lEthSM_TrcvLinkState_en == ETHTRCV_LINK_STATE_DOWN )                                         */


    /* Transition from ETHSM_STATE_WAIT_ONLINE to ETHSM_STATE_ONLINE */
    if( TCPIP_STATE_ONLINE == lEthSM_TcpIpState_en )
    {
        /* Inform BswM about the current state */
        BswM_EthSM_CurrentState(   EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                   ETHSM_STATE_ONLINE );

        /* If network user of the network is only TCPIP then ComM is indicated with FULL_COM */
        if( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 == 1U )
        {
            /* Communicate current state to ComM */
            lComMCurrMode_en = COMM_FULL_COMMUNICATION;

            ComM_BusSM_ModeIndication( ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                         &lComMCurrMode_en );
        }
        else
        {   /* ComM is already notified with mode COMM_FULL_COMMUNICATION if CDD is also the user of the network */
        }

        /* Update state of corresponding network to ETHSM_STATE_ONLINE */
        EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_ONLINE;

        /* Another state transition ETHSM_STATE_ONLINE to ETHSM_STATE_WAIT_OFFLINE/ETHSM_STATE_ONHOLD is possible within current EthSM main function, */
        /* if EthSM has already received function calls EthSM_TrcvLinkStateChg( DOWN )/EthSM_RequestComMode(OFFLINE) */
        *lEthSM_StateChgPossible_pb = TRUE;
    }
    /* Transition from ETHSM_STATE_WAIT_ONLINE to ETHSM_STATE_OFFLINE */
    else if( COMM_NO_COMMUNICATION == lEthSM_ComMReqMode_u8 )
    {
        /* Reason for calling EthIf_SetControllerMode() before TcpIp_RequestComMode(): */
        /* There is possibility of EthIf_SetControllerMode() returning E_NOT_OK, where as TcpIp_RequestComMode() will never return E_NOT_OK unless parameters is invalid */\
        lStdRetType_en = E_OK;

        /* If the EthIfCtrl has not reported unexpected DOWN state, set EthIfCtrl mode to DOWN */
        if( FALSE == EthSM_HwError_ab[lCtrlIdx_u8] )
        {
            /* Set EthIfCtrl to DOWN */
            lStdRetType_en = EthIf_SetControllerMode( lCtrlIdx_u8,
                                                      ETH_MODE_DOWN );
        }

        /* Request TcpIp to release IP address */
        if( E_OK == lStdRetType_en )
        {
            /* Loop through all network users for the EthSM network */
            for( lLoopIdx_u8 = 0; lLoopIdx_u8 < ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 ); lLoopIdx_u8++ )
            {
                if( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[lLoopIdx_u8].NetworkUser_en == ETHSM_USER_TCPIP )
                {
                    lStdRetType_en = TcpIp_RequestComMode( lCtrlIdx_u8,
                                                           TCPIP_STATE_OFFLINE );

                    /* Break from the loop as only one TcpIp user is possible for an EthSM network. */
                    break;
                }
            }
        }

        if( E_OK == lStdRetType_en )
        {
            /* If one of the network user is CDD, then ComM is indicated with NO_COM */
            if(( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_CDD ) ||
               ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 > 1U ))
            {
                /* Communicate current state to ComM */
                lComMCurrMode_en = COMM_NO_COMMUNICATION;

                ComM_BusSM_ModeIndication(  ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                              &lComMCurrMode_en );
            }

            /* Inform BswM about EthSM state change */
            BswM_EthSM_CurrentState (  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                       ETHSM_STATE_OFFLINE );

            /* Update State of the EthSM network */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_OFFLINE;

            /* In case of HW error another state transition from ETHSM_STATE_OFFLINE to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE  */
            /* is possible within current EthSM main function */
            if( FALSE != EthSM_HwError_ab[lCtrlIdx_u8] )
            {
                *lEthSM_StateChgPossible_pb = TRUE;

                /* Clear the hardware error flag */
				EthSM_HwError_ab[lCtrlIdx_u8] = FALSE;
            }
        }
    }

    /* Transition from ETHSM_STATE_WAIT_ONLINE to ETHSM_STATE_WAIT_TRCVLINK */
    else if( ETHTRCV_LINK_STATE_DOWN == lEthSM_TrcvLinkState_en )
    {
        /* Initialize lStdRetType_en to E_OK. As User_TrcvLinkStateChg() API has no return value lStdRetType_en is decided by TcpIp only */
        lStdRetType_en = E_OK;

        /* Loop through all network users for the EthSM network */
        for( lLoopIdx_u8 = 0; lLoopIdx_u8 < ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 ); lLoopIdx_u8++ )
        {
            if( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[lLoopIdx_u8].NetworkUser_en == ETHSM_USER_TCPIP )
            {
                /* Request TcpIp State TCPIP_STATE_OFFLINE, if network user is TcpIp */
                lStdRetType_en = TcpIp_RequestComMode(  lCtrlIdx_u8,
                                                        TCPIP_STATE_OFFLINE );

                /* Break from the loop as only one TcpIp user is possible for an EthSM network. */
                break;
            }
        }

        if ( E_OK == lStdRetType_en )
        {
            /* If one of the network user is CDD, then ComM is indicated with NO_COM */
            if(( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_CDD ) ||
               ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 > 1U ))
            {
                /* Communicate current state to ComM */
                lComMCurrMode_en = COMM_NO_COMMUNICATION;

                ComM_BusSM_ModeIndication(  ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                              &lComMCurrMode_en );
            }

            /* Inform BswM about the current state */
            BswM_EthSM_CurrentState(  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                      ETHSM_STATE_WAIT_TRCVLINK );

            /* Update State of the EthSM network */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_TRCVLINK;
        }
    }
    else
    { /* Do nothing */
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_ONLINE
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 * \param lEthSM_TrcvLinkState_en    : Link state as indicated by EthSM_TrcvLinkStateChg() for the current network
 * \param lEthSM_TcpIpState_en       : TcpIp Mode as indicated by EthSM_TcpIpModeIndication() for the current network
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 * \return  None
 *
 ***************************************************************************************************
 */
/* HIS METRIC LEVEL VIOLATION IN EthSM_TransFrm_Online: This function will have different state transitions based on different set of conditions and is not possible to avoid this HIS in-compliance .*/
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Online(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                            VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                            VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                            VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                            P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,             AUTOMATIC )       lStdRetType_en;
    VAR( ComM_ModeType,              AUTOMATIC )       lComMCurrMode_en;

    /*Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* In case multiple conditions are met for the transition, conditions shall be prioritized.        */
    /* Priority to be followed is:                                                                     */
    /* ( lEthSM_TcpIpState_en == TCPIP_STATE_OFFLINE )                                                 */
    /* ( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION )                                              */
    /* ( lEthSM_TrcvLinkState_en == ETHTRCV_LINK_STATE_DOWN )                                          */


    /* Transition from ETHSM_STATE_ONLINE to ETHSM_STATE_WAIT_ONLINE */
    if( TCPIP_STATE_OFFLINE == lEthSM_TcpIpState_en )
    {
        /* Inform BswM about the current state */
        BswM_EthSM_CurrentState(    EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                    ETHSM_STATE_WAIT_ONLINE );

        /* If network user of the network is only TCPIP then ComM is indicated with NO_COM */
        if(( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NetworkUserConfig_pcst[0].NetworkUser_en == ETHSM_USER_TCPIP ) &&
           ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].NumOfNetworkUsers_u8 == 1U ) )
        {
            /* Communicate current state to ComM */
            lComMCurrMode_en = COMM_NO_COMMUNICATION;

            ComM_BusSM_ModeIndication(  ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                          &lComMCurrMode_en );
        }

        /* Update state of corresponding network to ETHSM_STATE_WAIT_ONLINE */
        EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_ONLINE;

        /* Another state transition from ETHSM_STATE_WAIT_ONLINE to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE/ETHSM_STATE_WAIT_TRCVLINK is possible within  */
        /*current EthSM main function if EthSM is has already received function call EthSM_RequestComMode(NO_COM)/EthSM_TrcvLinkStateChg(ETHTRCV_LINK_STATE_DOWN) */
        *lEthSM_StateChgPossible_pb = TRUE;

    }
    /* Transition from ETHSM_STATE_ONLINE to ETHSM_STATE_WAIT_OFFLINE */
    else if( COMM_NO_COMMUNICATION == lEthSM_ComMReqMode_u8 )
    {
        /* Request TcpIp to release IP address */
        lStdRetType_en = TcpIp_RequestComMode( lCtrlIdx_u8,
                                               TCPIP_STATE_OFFLINE);

        if( E_OK == lStdRetType_en )
        {
            /* Inform BswM about EthSM state change */
            BswM_EthSM_CurrentState (  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                       ETHSM_STATE_WAIT_OFFLINE );

            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_OFFLINE;
        }
    }
    /* Transition from ETHSM_STATE_ONLINE to ETHSM_STATE_ONHOLD */
    else if(  ETHTRCV_LINK_STATE_DOWN == lEthSM_TrcvLinkState_en  )
    {
        /* Request TcpIp State ONHOLD */
        lStdRetType_en = TcpIp_RequestComMode(  lCtrlIdx_u8,
                                                TCPIP_STATE_ONHOLD );

        if( E_OK == lStdRetType_en)
        {
            /* Inform BswM about the current state */
            BswM_EthSM_CurrentState(    EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                        ETHSM_STATE_ONHOLD );

            /* Update State of EthSM network */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_ONHOLD;
        }
    }
    else
    { /* Do nothing */
    }
}

/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_ONHOLD
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_ComMReqMode_u8      : Mode requested by ComM for the current network
 * \param lEthSM_TrcvLinkState_en    : Link state as indicated by EthSM_TrcvLinkStateChg() for the current network
 * \param lEthSM_TcpIpState_en       : TcpIp Mode as indicated by EthSM_TcpIpModeIndication() for the current network
 *
 * Parameters InOut:
 * \param None
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 * \return  None
 *
 ***************************************************************************************************
 */
/* HIS METRIC LEVEL VIOLATION IN EthSM_TransFrm_Onhold: This function will have different state transitions based on different set of conditions and is not possible to avoid this HIS in-compliance .*/
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_Onhold(  VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                            VAR( uint8,                   AUTOMATIC ) lEthSM_ComMReqMode_u8,
                                                            VAR( EthTrcv_LinkStateType,   AUTOMATIC ) lEthSM_TrcvLinkState_en,
                                                            VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                            P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,             AUTOMATIC )       lStdRetType_en;
    VAR( ComM_ModeType,              AUTOMATIC )       lComMCurrMode_en;

    /*Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    /* In case multiple conditions are met for the transition, conditions shall be prioritized.         */
    /* Priority to be followed is:                                                                      */
    /* ( lEthSM_TcpIpState_en == TCPIP_STATE_OFFLINE )                                                  */
    /* ( lEthSM_ComMReqMode_u8 == COMM_NO_COMMUNICATION )                                               */
    /* ( lEthSM_TrcvLinkState_en == ETHTRCV_LINK_STATE_ACTIVE )                                         */

    /* Transition from ETHSM_STATE_ONHOLD to ETHSM_STATE_WAIT_TRCVLINK */
    if( TCPIP_STATE_OFFLINE == lEthSM_TcpIpState_en )
    {
        /* Inform BswM about the current state */
        BswM_EthSM_CurrentState( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                 ETHSM_STATE_WAIT_TRCVLINK );

        /* Communicate current state to ComM */
        lComMCurrMode_en = COMM_NO_COMMUNICATION;
        ComM_BusSM_ModeIndication(  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ,
                                    &lComMCurrMode_en );

        /* Update state of corresponding network */
        EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_TRCVLINK;

        /* Another state transition ETHSM_STATE_WAIT_TRCVLINK to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE is possible within current EthSM main function if */
        /* EthSM is has already received function call EthSM_RequestComMode(NO_COM) */
        *lEthSM_StateChgPossible_pb = TRUE;

    }
    /* Transition from ETHSM_STATE_ONHOLD to ETHSM_STATE_WAIT_OFFLINE */
    else if( COMM_NO_COMMUNICATION == lEthSM_ComMReqMode_u8 )
    {
        lStdRetType_en = TcpIp_RequestComMode( lCtrlIdx_u8,
                                               TCPIP_STATE_OFFLINE );

        if( E_OK == lStdRetType_en )
        {
            /* Inform BswM about EthSM state change */
            BswM_EthSM_CurrentState (  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                       ETHSM_STATE_WAIT_OFFLINE );

            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_WAIT_OFFLINE;
        }
    }
    /* Transition from ETHSM_STATE_ONHOLD to ETHSM_STATE_ONLINE */
    else if( ETHTRCV_LINK_STATE_ACTIVE == lEthSM_TrcvLinkState_en )
    {
        /* Request TcpIp State ONLINE  */
        lStdRetType_en = TcpIp_RequestComMode(  lCtrlIdx_u8,
                                                TCPIP_STATE_ONLINE );

        if( E_OK == lStdRetType_en)
        {
            /* Inform BswM about the current state */
            BswM_EthSM_CurrentState(  EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                      ETHSM_STATE_ONLINE );

            /* Update State of the corresponding network */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_ONLINE;
        }
    }
    else
    { /* Do nothing */
    }
}


/**
 ***************************************************************************************************
 * \module description
 * Called by EthSM_MainFunction(), to trigger all possible state transitions from ETHSM_STATE_WAIT_OFFLINE
 *
 * Parameter In:
 * \param lCtrlIdx_u8                : Index of EthIfCtrl for which state transitions needs to be triggered
 * \param lEthSM_TcpIpState_en       : TcpIp Mode as indicated by EthSM_TcpIpModeIndication() for the current network
 *
 * Parameters Out:
 * \param lEthSM_StateChgPossible_pb : will be set to TRUE on state transition if there is a possibility of another
 *                                     state transition to happen, within current EthSM main function.
 *
 * Parameters Out:
  * \param  None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
static FUNC( void, RBA_ETHSM_CODE ) EthSM_TransFrm_WaitOffline( VAR( uint8,                   AUTOMATIC ) lCtrlIdx_u8,
                                                                VAR( TcpIp_StateType,         AUTOMATIC ) lEthSM_TcpIpState_en,
                                                                P2VAR( boolean,    AUTOMATIC, AUTOMATIC ) lEthSM_StateChgPossible_pb )
{
    /* Local variable declaration */
    VAR( Std_ReturnType,             AUTOMATIC )       lStdRetType_en;
    VAR( ComM_ModeType,              AUTOMATIC )       lComMCurrMode_en;

    /*Initialize local variable */
    lStdRetType_en = E_NOT_OK;

    if(TCPIP_STATE_OFFLINE == lEthSM_TcpIpState_en)
    {
        /* If the EthIfCtrl has reported unexpected DOWN state EthSM network shall be brought back to ETHSM_STATE_OFFLINE. */
        /* Hence another state change from ETHSM_STATE_OFFLINE to ETHSM_SUBSTATE_OFFLINE_WAIT_CTRLMODE_ACTIVE is possible within current EthSM_MainFunction()*/
        if( FALSE != EthSM_HwError_ab[lCtrlIdx_u8] )
        {
            *lEthSM_StateChgPossible_pb = TRUE;

            lStdRetType_en = E_OK;
        }
        else
        {
            /* Set EthIfCtrl to DOWN */
            lStdRetType_en = EthIf_SetControllerMode( lCtrlIdx_u8,
                                                      ETH_MODE_DOWN );
        }

        if(E_OK == lStdRetType_en)
        {
            /* Inform BswM about the current state */
            BswM_EthSM_CurrentState(   EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8,
                                       ETHSM_STATE_OFFLINE );

            /* Communicate current state to ComM */
            lComMCurrMode_en = COMM_NO_COMMUNICATION;
            ComM_BusSM_ModeIndication(  ( EthSM_EthChnlPtr_pco[lCtrlIdx_u8].comMNetHandleId_u8 ),
                                        &lComMCurrMode_en );

            /* Update the state of EthSM network */
            EthSM_NetState_aen[lCtrlIdx_u8] = ETHSM_STATE_OFFLINE;

            /* Clear the hardware error flag */
            EthSM_HwError_ab[lCtrlIdx_u8] = FALSE;
        }
    }
}


#define ETHSM_STOP_SEC_CODE
#include "EthSM_MemMap.h"

#endif /* ETHSM_CONFIGURED */

