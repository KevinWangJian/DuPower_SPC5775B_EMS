

#ifndef RBA_ETHARP_H
#define RBA_ETHARP_H

/*
****************************************************************************************************
*                                   Includes
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

/* Vendor Id */
#define RBA_ETHARP_VENDOR_ID                    6U

/* rba_EthArp module Id */
#define RBA_ETHARP_MODULE_ID                    255U

/* rba_EthArp instance Id */
#define RBA_ETHARP_INSTANCE_ID                  171U


/* SOFTWARE VERSION INFORMATION */
#define RBA_ETHARP_SW_MAJOR_VERSION                 4U
#define RBA_ETHARP_SW_MINOR_VERSION                 0U
#define RBA_ETHARP_SW_PATCH_VERSION                 0U
/*End: Common Published information*/

/*********************************************/
/* ARP code - Define Value                   */
/*********************************************/

/* Type of ARP Frame to send */
#define RBA_ETHARP_ARP_PROBE_FRAME              2U

/*
****************************************************************************************************
*                                   Prototypes
****************************************************************************************************
*/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
extern FUNC( void,              RBA_ETHARP_CODE )   rba_EthArp_Init (
                                                        P2CONST( rba_EthArp_Config_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_Config_cst );

extern FUNC( void,              RBA_ETHARP_CODE )   rba_EthArp_MainFunction         ( void );

extern FUNC( TcpIp_ReturnType,  RBA_ETHARP_CODE )   rba_EthArp_GetDestEthAddr       (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                VAR( uint32, AUTOMATIC )        lDestIpAddr_u32,
                                                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )    lDestEthAddr_au8 );

extern FUNC( TcpIp_ReturnType,  RBA_ETHARP_CODE )   rba_EthArp_UpdateArpTable       (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )      lSrcEthAddr_au8,
                                                                VAR( uint32, AUTOMATIC )    lSrcIpAddr_u32 );

extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE )   rba_EthArp_SendArpFrame         (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                VAR( uint16, AUTOMATIC )        lIndexTable_u16,
                                                                VAR( uint32, AUTOMATIC )    lDestIPv4Addr_u32,
                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )      lDestEthAddr_au8,
                                                                VAR( uint8, AUTOMATIC )         lTypeFrame_u8);

extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE )   rba_EthArp_SendArpGratuitousFrame   (
                                                                VAR( uint8, AUTOMATIC )     lCtrlIdx_u8,
                                                                VAR( uint32, AUTOMATIC )        lSrcIPv4Addr_u32);

extern FUNC( Std_ReturnType, RBA_ETHARP_CODE )rba_EthArp_ReadArpTable (
                                                                VAR(        uint8,      AUTOMATIC ) EthIfCtrlIdx_u8,
                                                                CONSTP2VAR( uint8,      AUTOMATIC, AUTOMATIC )   ArpTable_cpu8,
                                                                CONSTP2VAR( uint16,     AUTOMATIC, AUTOMATIC )   NumberEntries_cpu16 );

extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE ) rba_EthArp_IpConflictDetection    ( VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                                      VAR( uint32, AUTOMATIC )                      lRxSrcIpAddress_u32,
                                                                                      VAR( uint32, AUTOMATIC )                      lRxDstIpAddress_u32,
                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )        lRxSrcEthAddress_au8,
                                                                                      VAR( uint16, AUTOMATIC )                      lTypeOfFrame_u16);

extern FUNC( void ,           RBA_ETHARP_CODE )     rba_EthArp_CleanArpTable        (
                                                                VAR( uint8, AUTOMATIC ) EthIfCtrlIdxCurr_u8 );

extern FUNC( Std_ReturnType ,            RBA_ETHARP_CODE ) rba_EthArp_GetArpTablesize (   P2VAR( uint16, AUTOMATIC, AUTOMATIC ) lArpTableSize_pu16 );

#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"
#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */
#endif /* RBA_ETHARP_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/

