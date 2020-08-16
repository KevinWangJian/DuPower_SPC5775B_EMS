
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#include "EthIf.h"

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#include "TcpIp_Prv.h"

#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched - EthIf and TcpIp"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - EthIf and TcpIp"
#endif

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
/*
***************************************************************************************************
* Static function declaration
***************************************************************************************************
*/

static FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_ReleaseStaticIPAddr( CONST( TcpIp_LocalAddrIdType, AUTOMATIC )  LocalAddrId );


/********************************************************************************************************************/
/* TcpIp_ReleaseIpAddrAssignment() - This API service the local IP address assignment for the IP address specified  */
/*                          by LocalAddrId shall be released.                                                       */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrId     - IP address index specifying the IP address for which an assignment shall  be initiated.   */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request has not been accepted.                                              */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_ReleaseIpAddrAssignment(
                                                    CONST( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( Std_ReturnType,                          AUTOMATIC )   lStdRetType_en;
    VAR( uint8,                                   AUTOMATIC )   lAddrAssgntMethIdx_u8;

    /* Initialise local variables */
    lStdRetType_en          = E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_RELEASE_IP_ADDRASSIGNMENT_API_ID, \
                                      TCPIP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),      \
                                      TCPIP_E_RELEASE_IP_ADDRASSIGNMENT_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Update the pointer to LocalAddrId structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId );

    /* Loop through all address assignment methods configured for the LocalAddrId and stop the assignment methods */
    for(lAddrAssgntMethIdx_u8 = 0; lAddrAssgntMethIdx_u8 < lLocalAddrConfig_pcst->NumAddrAsgnment_u8; lAddrAssgntMethIdx_u8++ )
    {
        if( (TCPIP_MANUAL == lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentTrig_en) ||
            (TCPIP_STATE_OFFLINE == TcpIp_EthIfCtrlReqSt_aen[lLocalAddrConfig_pcst->EthIfCtrlRef_u8]) )
        {

            switch(lLocalAddrConfig_pcst->AddrAsgnment_pcst[lAddrAssgntMethIdx_u8].AddrAsgnmentMeth_en)
            {
                case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
                case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP:
                {
					#if (TCPIP_AUTOIP_ENABLED == STD_ON)
                    lStdRetType_en = rba_EthAutoIp_Stop( LocalAddrId );
                    #endif
                }
                break;

                case TCPIP_IPADDR_ASSIGNMENT_DHCP:
                {
					#if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
                    lStdRetType_en = rba_EthDHCP_Stop( LocalAddrId );
                    #endif
                }
                break;

                case TCPIP_IPADDR_ASSIGNMENT_STATIC:
                {
                    lStdRetType_en = TcpIp_ReleaseStaticIPAddr( LocalAddrId );
                }
                break;

                default:
                { /* Do nothing */
                }
                break;
            }

            /* Clear IP assignment pending request bit */
            if(E_OK == lStdRetType_en)
            {
                lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->ReqAddrAssgnMeth_u8 &=  (uint8)( ~(uint8)(1U << lAddrAssgntMethIdx_u8) );
            }
            else
            {
                break;     /* If releasing of any of the assignments return E_NOT_OK, terminate the release operation and inform upper layer */
            }
        }
    }

    return( lStdRetType_en );
}


/********************************************************************************************************************/
/* TcpIp_ReleaseStaticIPAddr() -By this API the static local IP address specified by LocalAddrId shall be released. */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*      LocalAddrId     - IP address index specifying the IP address for which the static IP address is released.   */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/* Std_ReturnType       -   Result of operation                                                                     */
/*                          E_OK - Request processed successfully                                                   */
/*                          E_NOT_OK - Request NOT processed successfully                                           */
/*                                                                                                                  */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_ReleaseStaticIPAddr(
                                                        CONST( TcpIp_LocalAddrIdType, AUTOMATIC )   LocalAddrId )
{
    /* Local variables declaration */
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;
    VAR( Std_ReturnType,                          AUTOMATIC )   lStdRetType_en;

    /* If the assignment method is pointing to STATIC and STATIC IP is not assigned API shall not return E_NOT_OK   */
    lStdRetType_en = E_OK;

    /* Update the pointer to LocalAddrId structure */
    lLocalAddrConfig_pcst = ( TcpIp_CurrConfig_pco->EthLocalAddrConfig_paco + LocalAddrId );

    if ( TCPIP_IPADDR_ASSIGNMENT_STATIC == lLocalAddrConfig_pcst->CurrAsgnedAddr_pst->CurrAsgnedAddrMeth_en )
    {
        /* Check whether the LocalAddress is multicast */
        if( TCPIP_MULTICAST == lLocalAddrConfig_pcst->IpAddressType_en )
        {
            lStdRetType_en = TcpIp_UpdateMulticastPhysFilter(lLocalAddrConfig_pcst, REMOVE_FROM_FILTER);
        }

        /* Reset the structure members, inform SoAd and EthSM about release of IP */
        if( E_OK == lStdRetType_en )
        {
            TcpIp_LocalIpAddrAssignmentChg( LocalAddrId,
                                            TCPIP_IPADDR_STATE_UNASSIGNED,
                                            NULL_PTR,                          /* Parameter of type TcpIp_IPvAddrParamType_tst is irrelevant for this use case */
                                            TCPIP_IPADDR_ASSIGNMENT_STATIC,
                                            lLocalAddrConfig_pcst->IpDomainType_u32);
        }
    }

    return lStdRetType_en;
}

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

