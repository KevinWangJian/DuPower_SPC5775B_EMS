

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#if ( TCPIP_ARP_ENABLED == STD_ON )
#include "rba_EthArp.h"

#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/*                                                                                                                  */
/* TcpIp_ReadArpTable() - This API is used by the upper layer to read out the Arp table for the EthIfCrtl,          */
/*                        which is indirectly specified by the LocalAddrId.                                         */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* LocalAddrId          - IP address identifier EthIf controller  for which Arp table shall be returned.            */
/*                                                                                                                  */
/* InOut Parameters :                                                                                               */
/*NumberEntries_pu16    - Number of Arp table entries. As input parameter specifies the number of Arp table entries */
/*                       to be read (size of the provided buffer ArpTable_pu8 in entries).                          */
/*                      As output parameter NumberEntries_pu16 contains the number of the returned Arp table entries*/
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/* ArpTable_pu8         - Pointer to first element of array, which contains the ARP table per EthIfCtrl indirectly  */
/*                        specified by LocalAddrId.                                                                 */
/*                                                                                                                  */
/* Std_ReturnType       Result of operation                                                                         */
/*      E_OK            The request was successful, ArpTable_pu8 and NumberEntries_pu16 were successfully updated   */
/*                      and contain valid data.                                                                     */
/*      E_NOT_OK        The request was not successful.                                                             */
/*                                                                                                                  */
/********************************************************************************************************************/

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_ReadArpTable(
                                    VAR(        TcpIp_LocalAddrIdType,  AUTOMATIC )                 LocalAddrId_u8 ,
                                    CONSTP2VAR( uint8,                  AUTOMATIC, AUTOMATIC )      ArpTable_cpu8,
                                    CONSTP2VAR( uint16,                 AUTOMATIC, AUTOMATIC )      NumberEntries_cpu16 )
{
    VAR( Std_ReturnType,    AUTOMATIC )     lRetVal_en;

    /* Local variable initialisation */
    lRetVal_en  = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_READ_ARPTABLE_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ), TCPIP_E_READ_ARPTABLE_API_ID , TCPIP_E_INV_ARG, E_NOT_OK )
    
    /* Report DET if local address ID refers to an IPv6 address */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].IpDomainType_u32 != TCPIP_AF_INET ), TCPIP_E_READ_ARPTABLE_API_ID , TCPIP_E_INV_ARG, E_NOT_OK )

    /* Report DET if ArpTable_cpu8 is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == ArpTable_cpu8 ), TCPIP_E_READ_ARPTABLE_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if NumberEntries_cpu16 is a Null Pointer */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == NumberEntries_cpu16 ), TCPIP_E_READ_ARPTABLE_API_ID, TCPIP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if value at address of NumberEntries_pu16 is equal 0 */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( *NumberEntries_cpu16 ) == 0 ), TCPIP_E_READ_ARPTABLE_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    lRetVal_en = rba_EthArp_ReadArpTable( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco[LocalAddrId_u8].EthIfCtrlRef_u8,   /* Get EthIf controller index from localAddrId */
                                          ArpTable_cpu8,
                                          NumberEntries_cpu16 );

    return lRetVal_en;
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* ( TCPIP_ARP_ENABLED == STD_ON ) */

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

