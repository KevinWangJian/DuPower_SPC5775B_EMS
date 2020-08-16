

#ifndef ETHSM_H_
#define ETHSM_H_

#include "ComStack_Types.h"
#include "EthSM_Cfg.h"
#ifdef ETHSM_CONFIGURED

/* Vendor Id */
#define ETHSM_VENDOR_ID  						6U

/* Module Id */
#define ETHSM_MODULE_ID							143U

/* EthSM instance Id */
#define ETHSM_INSTANCE_ID						0U

/* SOFTWARE VERSION INFORMATION */
#define ETHSM_SW_MAJOR_VERSION  				4U
#define ETHSM_SW_MINOR_VERSION  				0U
#define ETHSM_SW_PATCH_VERSION  				0U


/* AUTOSAR Version Info */
#define ETHSM_AR_RELEASE_MAJOR_VERSION 	 		4
#define ETHSM_AR_RELEASE_MINOR_VERSION  		2
#define ETHSM_AR_RELEASE_REVISION_VERSION 		2

/* START: Include Part  */
#include "EthSM_Types.h"
#include "EthIf_Types.h"

#include "ComM.h"
#if (!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != ETHSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != ETHSM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "EthTrcv.h"
#if (!defined(ETHTRCV_AR_RELEASE_MAJOR_VERSION) || (ETHTRCV_AR_RELEASE_MAJOR_VERSION != ETHSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHTRCV_AR_RELEASE_MINOR_VERSION) || (ETHTRCV_AR_RELEASE_MINOR_VERSION != ETHSM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "TcpIp_EthSM.h"
/* END: Include Part   */

#define ETHSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthSM_MemMap.h"

/* Global variable declaration */
extern VAR( EthSM_NetworkModeStateType, AUTOMATIC )                EthSM_NetState_aen[ETHSM_NUM_OF_ETHIFCTRL];       /* EthSM network current status per EthIfCtrlIdx                                           */
extern VAR( ComM_ModeType,              AUTOMATIC )                EthSM_ComMReqMode_au8[ETHSM_NUM_OF_ETHIFCTRL];    /* ComM mode request stored per EthIfCtrlIdx                                               */
extern VAR( Eth_ModeType,              AUTOMATIC )                 EthSM_EthIfCtrlMode_aen[ETHSM_NUM_OF_ETHIFCTRL];       /* Ctrl mode provided by EthSM_CtrlModeIndication() and is stored per EthIfCtrlIdx         */
extern VAR( EthTrcv_LinkStateType,      AUTOMATIC )                EthSM_TrcvLinkState_aen[ETHSM_NUM_OF_ETHIFCTRL];  /* Trcv link status provided by EthSM_TrcvLinkStateChg() and is stored per EthIfCtrlIdx    */
extern VAR( TcpIp_StateType,            AUTOMATIC )                EthSM_TcpIpState_aen[ETHSM_NUM_OF_ETHIFCTRL];     /* TcpIpCtrl status provided by EthSM_TcpIpModeIndication() and is stored per EthIfCtrlIdx */
extern VAR( boolean,                    AUTOMATIC )                EthSM_HwError_ab[ETHSM_NUM_OF_ETHIFCTRL];         /* Stores unexpected hardware mode DOWN indication and is stored per EthIfCtrl.           */

#define ETHSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthSM_MemMap.h"

#define ETHSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthSM_MemMap.h"

extern P2CONST( EthSM_ConfigType, AUTOMATIC, AUTOMATIC )                EthSM_EthChnlPtr_pco;

#define ETHSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthSM_MemMap.h"

#define ETHSM_START_SEC_CODE
#include "EthSM_MemMap.h"

/* Function declaration */
FUNC(void, RBA_ETHSM_CODE) EthSM_Init ( void );

FUNC(void,RBA_ETHSM_CODE) EthSM_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, AUTOMATIC) versioninfo);

FUNC(Std_ReturnType, RBA_ETHSM_CODE) EthSM_RequestComMode ( VAR(NetworkHandleType, AUTOMATIC) NetworkHandle, VAR(ComM_ModeType, AUTOMATIC) ComM_Mode );

FUNC(Std_ReturnType, RBA_ETHSM_CODE) EthSM_GetCurrentComMode (VAR(NetworkHandleType, AUTOMATIC) NetworkHandle, P2VAR(ComM_ModeType, AUTOMATIC, AUTOMATIC) ComM_ModePtr);

/*
 ***************************************************************************************************
 * Scheduled
 ***************************************************************************************************
 */

FUNC(void, RBA_ETHSM_CODE) EthSM_MainFunction(void);
#define ETHSM_STOP_SEC_CODE
#include "EthSM_MemMap.h"

#endif /* ETHSM_CONFIGURED */

#endif /* ETHSM_H_ */
