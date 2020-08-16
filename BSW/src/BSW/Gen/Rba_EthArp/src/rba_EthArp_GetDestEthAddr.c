

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )
#include "rba_EthArp.h"

#include "rba_EthArp_Prv.h"

/*************************************************************************************************/
/* rba_EthArp_GetDestEthAddr() - Returns the destination Ethernet address associate to the       */
/*      IP address. An ARP request should be sent out, if no destination Ethernet address entry  */
/*      is found in the ARP table for the destination IPv4 address.                              */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8     - Controller index used to transmit the Ethernet frame                       */
/*  lDestIpAddr_u32  - Destination IPv4 address                                                  */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  lDestEthAddr_au8 - Pointer to return the destination Ethernet address                        */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetVal_en      - Destination Ethernet Address OK or NOT_OK                                  */
/*                                                                                               */
/*************************************************************************************************/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
FUNC( TcpIp_ReturnType,     RBA_ETHARP_CODE )   rba_EthArp_GetDestEthAddr       (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                VAR( uint32, AUTOMATIC )        lDestIpAddr_u32,
                                                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )    lDestEthAddr_au8 )
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
    VAR( uint16, AUTOMATIC )                                lIndexTable_u16;
    VAR( uint8, AUTOMATIC )                             lLoop_u8;
    VAR( uint8, AUTOMATIC )                             lTableLoop_u8;
    VAR( TcpIp_ReturnType, AUTOMATIC )                      lRetVal_en;
    VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC ) lIpAddrInArpTable_en;
    VAR( Std_ReturnType, AUTOMATIC )                    lStdRetVal_en;

    /* Local variable Initialization */
    lRetVal_en  = TCPIP_E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_GET_DEST_ETHADDR_API_ID,   \
                                             RBA_ETHARP_E_NOTINIT, TCPIP_E_NOT_OK )

    /* Report DET if lDestEthAddr_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lDestEthAddr_au8 ), RBA_ETHARP_E_GET_DEST_ETHADDR_API_ID,      \
                                             RBA_ETHARP_E_NULL_PTR, TCPIP_E_NOT_OK )

    for (lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++)
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if(lArpSubCfg_pco->EthIfCtrIdx_cu8 == lCtrlIdx_u8)
        {
            /* Check in the ARP Table if the IP Address is known */
        	lStdRetVal_en = rba_EthArp_CheckIpTableEntry( lArpSubCfg_pco,
                                                          (uint16 *) &lIndexTable_u16,
                                                          lDestIpAddr_u32,
                                                          &lIpAddrInArpTable_en );

            if( lStdRetVal_en == E_OK )
            {
                /* If IP in ARP Table */
                if( ( RBA_ETHARP_ENTRY_USED == lIpAddrInArpTable_en ) || ( RBA_ETHARP_RPLY_TO_BE_SENT == lIpAddrInArpTable_en ) )
                {
                    /* Get the MAC Address in the ARP Table */
                    rba_EthArp_GetEthAddrInTableEntry( &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16], ( uint8 *) &lDestEthAddr_au8[0]);
                    lRetVal_en = TCPIP_OK;
                }
                /*If the Entry is a conflict IP - Do not return the MAC address*/
                else if (RBA_ETHARP_CONFLICT_DETECTED == lIpAddrInArpTable_en)
                {
                    lRetVal_en = TCPIP_E_NOT_OK;
                }
                /* If IP in ARP Table but MAC Address undefined */
                else if(RBA_ETHARP_FREE_ENTRY != lIpAddrInArpTable_en)
                {
                    /* Return MAC Address null */
                    for (lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
                    {
                        lDestEthAddr_au8[lLoop_u8] =  0x00;
                    }

                    lRetVal_en = TCPIP_E_ARP_CACHE_MISS;
                }
                /* If IP Address not found */
                else
                {
                    /* Return MAC Address null */
                    for (lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
                    {
                        lDestEthAddr_au8[lLoop_u8] =  0x00;
                    }

                    /* Get an entry available to store the new IP */
                    lStdRetVal_en =   rba_EthArp_GetUsableEntry( lArpSubCfg_pco,
                                                                 &lIndexTable_u16 );

                    if ( lStdRetVal_en == E_OK )
                    {
                        /* Store the IP Address with MAC addr null and ReqToBeSend status */
                        rba_EthArp_UpdateArpTableEntry(
                                            &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                                            lCtrlIdx_u8,
                                            RBA_ETHARP_REQ_TO_BE_SENT,
                                            lDestIpAddr_u32,
                                            &lDestEthAddr_au8[0],
                                            TCPIP_IPADDR_ASSIGNMENT_INVALID);


                        /* By setting the state of the entry as RBA_ETHARP_REQ_TO_BE_SENT
                         * the ARP Request frame will be sent in the next MainFunction */

                        /* MAC Address not available => Return ARP_CACHE_MISS */
                        lRetVal_en = TCPIP_E_ARP_CACHE_MISS;
                    }
                }
        	}

            /* break the loop */
            break;
        }
    } /* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid and return TCPIP_E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ), RBA_ETHARP_E_GET_DEST_ETHADDR_API_ID,   \
    		                               RBA_ETHARP_E_INV_ARG, TCPIP_E_NOT_OK )

    return lRetVal_en;
}

#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

