

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )
#include "rba_EthArp.h"

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif
#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#include "rba_EthArp_Prv.h"


/*************************************************************************************************/
/* rba_EthArp_IpConflictDetection() - Function called by rba_EthArp_RxIndication()               */
/* This function is called to check the Ip received in the frame and to detect if there is       */
/* no conflict between Ip address.                                                               */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8             - index of the Ethernet controller                                   */
/*  lRxSrcIpAddress_u32     - Source IP Address received from the ARP Frame                      */
/*  lRxDstIpAddress_u32     - Dest  IP Address received from the ARP Frame                       */
/*  lRxSrcEthAddress_au8    - MAC Address received from the ARP Frame                            */
/*  lTypeOfFrame_u16        - Type of Frame for which the conflict process is executed           */
/*                                                                                               */
/* return - Std_ReturnType  lRetVal_tu8                                                          */
/*      E_OK : an IP Conflict has been detected.                                                 */
/*      E_NOT_OK : No IP Conflict has been detected.                                             */
/*                                                                                               */
/*************************************************************************************************/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
FUNC( Std_ReturnType,   RBA_ETHARP_CODE ) rba_EthArp_IpConflictDetection    ( VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                                      VAR( uint32, AUTOMATIC )                      lRxSrcIpAddress_u32,
                                                                                      VAR( uint32, AUTOMATIC )                      lRxDstIpAddress_u32,
                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )        lRxSrcEthAddress_au8,
                                                                                      VAR( uint16, AUTOMATIC )                      lTypeOfFrame_u16)
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;

    VAR( uint32, AUTOMATIC )                            lCurrentIpAddr_u32;
    VAR( uint32, AUTOMATIC )                            lIpAddrToVerify_u32;
    VAR( uint8, AUTOMATIC )                             lTableLoop_u8;
    VAR( boolean, AUTOMATIC )                           lIpAddrInAutoIpRange_b;
    VAR( TcpIp_IpAddrStateType, AUTOMATIC )             lIpAddrStateType_en;
    VAR( rba_EthArp_EthAddrMatch_ten, AUTOMATIC )       lEthAddrMatch_en;

    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_tu8;
    VAR( Std_ReturnType, AUTOMATIC )                    lRetFctVal_tu8;
    VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )        lAssignMeth_en;

#if( TCPIP_IP_ADDR_CONFLICT_DETECTION_IP_FRAMES == STD_ON )
    VAR( uint16, AUTOMATIC )                            lIndexTable_u16;
    VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC ) lIpAddrInArpTable_en;
#endif

    /* Initialization */
    lCurrentIpAddr_u32              = 0;
    lIpAddrToVerify_u32             = 0;
    lIpAddrInAutoIpRange_b          = FALSE;
    lRetVal_tu8                     = E_NOT_OK;
    lRetFctVal_tu8                  = E_NOT_OK;
    lEthAddrMatch_en                = RBA_ETHARP_ETHADDR_NO_MATCH;
    lIpAddrStateType_en             = TCPIP_IPADDR_STATE_UNASSIGNED;

#if ( ( TCPIP_IP_ADDR_CONFLICT_DETECTION_IP_FRAMES == STD_OFF ) &&                  \
      ( ( RBA_ETHARP_MAC_ADDRS_CHECKS == STD_OFF ) ||                               \
        ( TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES == STD_OFF) ) )
    (void)lRxSrcEthAddress_au8;
#else
    /* Report DET if lRxSrcEthAddress_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lRxSrcEthAddress_au8 ), RBA_ETHARP_E_IPCONFLICT_DETECTION_API_ID,     \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK )
#endif

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_IPCONFLICT_DETECTION_API_ID,   \
                                           RBA_ETHARP_E_NOTINIT, E_NOT_OK )

    for(lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++)
    {
        /* Local Copy of the ARP SubConfig Structure */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if(lCtrlIdx_u8 == lArpSubCfg_pco->EthIfCtrIdx_cu8)
        {
            /**********************************/
            /* Perform the Conflict Detection */

            switch ( lTypeOfFrame_u16 )
            {
                #if(TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES == STD_ON)
                case TCPIP_TYPE_ARP :
                {
                    /* Detect if the ARP Frame is an ARP PROBE Frame (SrcIp == 0) */
                    if(lRxSrcIpAddress_u32 == 0UL)
                    {   /* ARP PROBE : Take the DestIp of the ARP Frame for the checking step */
                        lIpAddrToVerify_u32 = lRxDstIpAddress_u32;
                    }
                    else
                    {   /* ARP Take the SrcIp of the ARP Frame for the checking step */
                        lIpAddrToVerify_u32 = lRxSrcIpAddress_u32;
                    }

                    /* Check whether the IP address of the remote node is in the AutoIp address range */
                    if(( TCPIP_AUTOIP_RANGE_START <= lIpAddrToVerify_u32 ) && ( lIpAddrToVerify_u32 <= TCPIP_AUTOIP_RANGE_END ))
                    {
                        /* Indicate that the IP Address is in the AutoIp range */
                        lIpAddrInAutoIpRange_b = TRUE;

                        #if (TCPIP_AUTOIP_ENABLED == STD_ON)
                        /* Set the assignment method to AUTOIP (Link Local addressing) */
                        lAssignMeth_en = TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL;

                        /* Get IP Address from the AutoIP Table */
                        lRetFctVal_tu8 = rba_EthAutoIp_GetIpAddress (lCtrlIdx_u8, &lCurrentIpAddr_u32, &lIpAddrStateType_en);

                        #else
                        lRetFctVal_tu8 = E_NOT_OK;
                        #endif
                    }
                    else
                    {
                        /* Indicate that the IP Address is NOT in the AutoIp range */
                        lIpAddrInAutoIpRange_b = FALSE;

                        #if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
                        /* Set the assignment method to DHCP */
                        lAssignMeth_en = TCPIP_IPADDR_ASSIGNMENT_DHCP;

                        /* Get IP Address from the DHCP Table */
                        lRetFctVal_tu8 = rba_EthDHCP_GetIpAddress (lCtrlIdx_u8, &lCurrentIpAddr_u32, &lIpAddrStateType_en);

                        #else
                        lRetFctVal_tu8 = E_NOT_OK;
                        #endif
                    }

                    #if (RBA_ETHARP_MAC_ADDRS_CHECKS==STD_ON)
                    lEthAddrMatch_en = rba_EthArp_ChkMACAddrMatch(lCtrlIdx_u8,lRxSrcEthAddress_au8);
                    #endif

                    if( lRetFctVal_tu8 == E_OK )
                    {

                            if (lIpAddrStateType_en == TCPIP_IPADDR_STATE_UNASSIGNED )
                            {
                                /* RFC 3927 Section 2.2.1.
                                 * From the beginning to after the ANNOUNCE_WAIT seconds we have a conflict if :
                                 * ARP Frames       : (ip.src == lCurrentIpAddr_u32) OR
                                 * ARP Probe frames : ((ip.dest == lCurrentIpAddr_u32) && (hw.src != lMyEthAddr_au8) && (ip.src == 0)) */
                                if( ( lIpAddrToVerify_u32 == lCurrentIpAddr_u32) && (RBA_ETHARP_ETHADDR_MATCH != lEthAddrMatch_en) )
                                {
                                    /* Update ARP table if IP conflict is detected */
                                    rba_EthArp_UpdateConflictTblEntry( lCtrlIdx_u8,
                                                                       lAssignMeth_en,
                                                                       lIpAddrToVerify_u32,
                                                                       &lRxSrcEthAddress_au8[0] );

                                    /* conflict detected */
                                    lRetVal_tu8 = E_OK;
                                }
                                else
                                {   /* else no conflict */
                                    lRetVal_tu8 = E_NOT_OK;
                                }
                            }


                            else if (lIpAddrStateType_en == TCPIP_IPADDR_STATE_ASSIGNED )
                            {
                                /*  RFC 3927 Section 2.5.
                                 * In any state we have a conflict if : ip.src == lCurrentIpAddr_u32 && hw.src != lMyEthAddr_au8 */
                                if( ( lRxSrcIpAddress_u32 == lCurrentIpAddr_u32 ) && ( RBA_ETHARP_ETHADDR_NO_MATCH == lEthAddrMatch_en ))
                                {
                                    /* Update ARP table if IP conflict is detected */
                                    rba_EthArp_UpdateConflictTblEntry( lCtrlIdx_u8,
                                                                       lAssignMeth_en,
                                                                       lIpAddrToVerify_u32,
                                                                       &lRxSrcEthAddress_au8[0] );

                                    /* conflict detected */
                                    lRetVal_tu8 = E_OK;
                                }
                                else
                                {   /* else no conflict */
                                    lRetVal_tu8 = E_NOT_OK;
                                }
                            }
                            else
                            {
                                /*Do nothing */
                            }


                    }

                    /**********************************/
                    /* CONFLICT DETECTION STATIC PART */
                    /**********************************/

                    /* If IP conflict not yet detected AND IP is not present in AutoIp range AND
                     * ( nothing has been returned by DHCP or AutoIP GetIpAddress API (process stopped or COMP not available)
                     *   OR If (IP Returned) AND (DHCP IP Assignment State not Assigned (INIT or UNASSIGNED)))  */
                    if( ( FALSE == lIpAddrInAutoIpRange_b )  &&
                        ( lRetVal_tu8 == E_NOT_OK ) &&
                        ( ( lRetFctVal_tu8 == E_NOT_OK ) ||
                          ( ( lRetFctVal_tu8 == E_OK )  && ( lIpAddrStateType_en != TCPIP_IPADDR_STATE_ASSIGNED ) ) ) )

                    {   /* Call API to detect IP conflict with assignment method TCPIP_STATIC */
                        lRetVal_tu8 = rba_EthArp_ConflictDet_CurrAsgndIP( lCtrlIdx_u8,
                                                                          TCPIP_IPADDR_ASSIGNMENT_STATIC,
                                                                          lRxSrcIpAddress_u32,
                                                                          &lRxSrcEthAddress_au8[0] );
                    }
                    else
                    {
                        /* The case have been already covered previously */
                    }
                }
            break;
            #endif /* (TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES == STD_ON) */

            #if(TCPIP_IP_ADDR_CONFLICT_DETECTION_IP_FRAMES == STD_ON)

                case TCPIP_TYPE_IPV4 :
                {
                    /* Get the IP address assignment type from the TCPIP */
                    lRetVal_tu8 = TcpIp_GetIPAddrAsgnMethFrmCrtlIdx( lArpSubCfg_pco->EthIfCtrIdx_cu8, &lAssignMeth_en );

                    if ( E_OK == lRetVal_tu8 )
                    {
                        /* Call API to detect IP conflict for currently assigned IP address */
                        lRetVal_tu8 = rba_EthArp_ConflictDet_CurrAsgndIP( lCtrlIdx_u8,
                                                                          lAssignMeth_en,
                                                                          lRxSrcIpAddress_u32,
                                                                          &lRxSrcEthAddress_au8[0] );
                    }
                }
                break;

            #endif /* (TCPIP_IP_ADDR_CONFLICT_DETECTION_IP_FRAMES == STD_ON) */

                default :
                {
                    /* Nothing to do */
                }
                break;

            }

            /* The ARP Table matched to the CtrlIdx has been found : break the loop */
            break;
        }
    } /* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid and return TCPIP_E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),       \
                                           RBA_ETHARP_E_IPCONFLICT_DETECTION_API_ID, RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    return lRetVal_tu8;
}

#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

