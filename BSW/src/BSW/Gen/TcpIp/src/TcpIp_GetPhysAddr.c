

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED
#include "EthIf.h"
#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched - EthIf and TcpIp"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - EthIf and TcpIp"
#endif

#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/* TcpIp_GetPhysAddr()  - Obtains the physical source address used by the EthIf controller implicitly specified via */
/*                      LocalAddrId                                                                                 */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId     - Local address identifier implicitly specifying the EthIf controller for which the physical    */
/*                      address shall be obtained.                                                                  */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  PhysAddrPtr     - Pointer to the memory where the physical source address (MAC address) in network byte         */
/*                      order is stored.                                                                            */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request was not successful,                                                 */
/*                                  e.g. no unique Ctrl specified via IpAddrId.                                     */
/*                                                                                                                  */
/********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_GetPhysAddr(  VAR( TcpIp_LocalAddrIdType, AUTOMATIC )     LocalAddrId,
                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        PhysAddrPtr )
{
    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_GET_PHYSADDR_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),  \
    		                          TCPIP_E_GET_PHYSADDR_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if PhysAddrPtr is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == PhysAddrPtr ), TCPIP_E_GET_PHYSADDR_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

    EthIf_GetPhysAddr(  ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId].EthIfCtrlRef_u8 ),
                        PhysAddrPtr );

    return ( E_OK );
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

