

#ifndef SOAD_H
#define SOAD_H


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComStack_Types.h"
#include "SoAd_Types.h"
#include "TcpIp_Types.h"
#include "SoAd_Cfg.h"

/**************************************************************************************************/
/*  Common Published Information                                                                  */
/**************************************************************************************************/

/* Vendor ID */
#define SOAD_VENDOR_ID  6u

/* Module ID */
#define SOAD_MODULE_ID                      56u

/* As of now, SoAd is supported only single instance, so SoAd Instance Id will be '0' in all the scenario */
#define SOAD_INSTANCE_ID                    0u

/* AUTOSAR SPECIFICATION VERSION */
#define SOAD_AR_RELEASE_MAJOR_VERSION       4u
#define SOAD_AR_RELEASE_MINOR_VERSION       2u
#define SOAD_AR_RELEASE_REVISION_VERSION    2u

/* SOFTWARE VERSION INFORMATION */
#define SOAD_SW_MAJOR_VERSION               4u
#define SOAD_SW_MINOR_VERSION               0u
#define SOAD_SW_PATCH_VERSION               0u

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */

/****************************************************************************************************************
**                                   Global Variable Declaration                                                **
****************************************************************************************************************/

#define SOAD_START_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"
extern CONST( SoAd_ConfigType, SOAD_CONST )      SoAd_ConfigSet[];
#define SOAD_STOP_SEC_CONST_UNSPECIFIED
#include "SoAd_MemMap.h"

/****************************************************************************************************************
**                                   Global Function Prototypes                                                **
****************************************************************************************************************/
#define SOAD_START_SEC_CODE_SLOW
#include "SoAd_MemMap.h"
extern FUNC( void, SOAD_CODE )                  SoAd_Init                           ( P2CONST( SoAd_ConfigType, AUTOMATIC, AUTOMATIC )          SoAdConfigPtr ) ;

#define SOAD_STOP_SEC_CODE_SLOW
#include "SoAd_MemMap.h"

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"
#if (SOAD_VERSION_INFO_API == STD_ON)
extern FUNC( void, SOAD_CODE )                  SoAd_GetVersionInfo                 ( P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_DATA)      versioninfo );
#endif

#if( SOAD_ECUC_RB_RTE_IN_USE == STD_OFF)
extern FUNC( void, SOAD_CODE )                  SoAd_MainFunction                   ( void );

#if ( SOAD_MAIN_FUNCTION_1MS_ENABLED  == STD_ON)
extern FUNC( void, SOAD_CODE )                  SoAd_MainFunction_1ms               ( void );
#endif
#endif

/* End of SOAD_MAIN_FUNCTION_1MS_ENABLED  == STD_ON  */

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_OpenSoCon                      ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_CloseSoCon                     ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId ,\
                                                                                      VAR( boolean, AUTOMATIC )                                 Abort );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_TpCancelTransmit               ( VAR( PduIdType, AUTOMATIC )                               PduId);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_TpCancelReceive                ( VAR( PduIdType, AUTOMATIC )                               PduId);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_GetSoConId                     ( VAR( PduIdType, AUTOMATIC )                               TxPduId ,\
                                                                                      P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )           SoConIdPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_IfTransmit                     ( VAR( PduIdType, AUTOMATIC )                               SoAdSrcPduId ,\
                                                                                      P2CONST( PduInfoType, AUTOMATIC, AUTOMATIC )              SoAdSrcPduInfoPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_IfRoutingGroupTransmit         ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_IfSpecificRoutingGroupTransmit ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id,
                                                                                      VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_TpTransmit                     ( VAR( PduIdType, AUTOMATIC )                               SoAdSrcPduId ,\
                                                                                      P2CONST( PduInfoType, AUTOMATIC, AUTOMATIC )              SoAdSrcPduInfoPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_SetRemoteAddr                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId ,\
                                                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         RemoteAddrPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_RequestIpAddrAssignment        ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId , \
                                                                                      VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )              Type , \
                                                                                      P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST )     LocalIpAddrPtr, \
                                                                                      VAR(uint8, AUTOMATIC)                                     Netmask, \
                                                                                      P2CONST( TcpIp_SockAddrType, SOAD_CONST, SOAD_CONST )     DefaultRouterPtr);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_GetPhysAddr                    ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId ,\
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      PhysAddrPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_GetRemoteAddr                  ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId ,\
                                                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         IpAddrPtr );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_GetLocalAddr                   ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId , \
                                                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         LocalAddrPtr, \
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      NetmaskPtr, \
                                                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         DefaultRouterPtr);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_ReleaseIpAddrAssignment        ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_EnableRouting                  ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_DisableRouting                 ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_EnableSpecificRouting          ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id, \
                                                                                      VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_DisableSpecificRouting         ( VAR( SoAd_RoutingGroupIdType, AUTOMATIC )                 id, \
                                                                                      VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId);

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_SetUniqueRemoteAddr            ( VAR  ( SoAd_SoConIdType, AUTOMATIC )                      SoConId, \
                                                                                      P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         RemoteAddrPtr, \
                                                                                      P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )           AssignedSoConIdPtr);

extern FUNC(Std_ReturnType, SOAD_CODE)          SoAd_ChangeParameter                ( VAR(SoAd_SoConIdType, AUTOMATIC)                          SoConId, \
                                                                                      VAR(SoAd_ParamIdType, AUTOMATIC)                          ParameterId, \
                                                                                      P2VAR(uint8, AUTOMATIC, AUTOMATIC)                        ParameterValuePtr);

extern FUNC(Std_ReturnType, SOAD_CODE )         SoAd_ReadDhcpHostNameOption         ( VAR( SoAd_SoConIdType, AUTOMATIC )                        SoConId, \
                                                                                      P2VAR ( uint8, AUTOMATIC, AUTOMATIC )                     length, \
                                                                                      P2VAR ( uint8, AUTOMATIC, AUTOMATIC )                     data );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_WriteDhcpHostNameOption        ( VAR ( SoAd_SoConIdType, AUTOMATIC )                       SoConId, \
                                                                                      VAR (uint8, AUTOMATIC )                                   length, \
                                                                                      P2CONST ( uint8, AUTOMATIC, AUTOMATIC )                   data );

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

/*** BSD Socket Interfaces supported by SoAd ****/


/****************************************************************************************************************
**                                   External Variables Declarations                                           **
****************************************************************************************************************/

#endif
