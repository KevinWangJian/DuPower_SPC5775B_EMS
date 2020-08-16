

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

#include "rba_EthArp.h"
#include "rba_EthArp_Cbk.h"

#include "rba_EthArp_Prv.h"

#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"

/*
****************************************************************************************************
*                                   Prototype static Functions
****************************************************************************************************
*/
LOCAL_INLINE FUNC( Std_ReturnType,   RBA_ETHARP_CODE )   rba_EthArp_ProcessReceivedFrm( VAR( uint8, AUTOMATIC ) lCtrlIdx_u8,
                                                                                        VAR( rba_EthArp_Hdr_tst, AUTOMATIC )  lArpHdr_st,
                                                                                        P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco );

/*
****************************************************************************************************
****************************************************************************************************
*/



/*************************************************************************************************/
/* rba_EthArp_RxIndication() - Function called if an ARP Frame have been received.               */
/* Rx process defined in the RFC826 - Packet Reception                                           */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8     - EthIf controller index                                                     */
/*  lRxDataPtr  - ARP payload pointer.                                                       */
/*  lRxDataLen_u16  - Number of data bytes received                                              */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetVal_en      - E_OK the ARP Frame received has been parsed.                               */
/*                  - E_NOT_OK  the ARP Frame received has not been parsed.                      */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

FUNC( Std_ReturnType,   RBA_ETHARP_CODE )   rba_EthArp_RxIndication         (
                                                                VAR( uint8, AUTOMATIC )     lCtrlIdx_u8,
                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )      lRxDataPtr,
                                                                VAR( uint16, AUTOMATIC )    lRxDataLen_u16  )
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
    VAR( rba_EthArp_Hdr_tst, AUTOMATIC )                     lArpHdr_st;

    VAR( uint8, AUTOMATIC )                                 lTableLoop_u8;
    VAR( Std_ReturnType, AUTOMATIC )                        lRetVal_tu8;
    VAR( TcpIp_StateType, AUTOMATIC )                       lTcpIpEthIfCtrlSt_en;

    /* Local variable initialization */
    lRetVal_tu8             = E_NOT_OK;


    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_RXINDICATION_API_ID,   \
                                          RBA_ETHARP_E_NOTINIT, E_NOT_OK )

    /* Report DET if lRxDataPtr is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lRxDataPtr ), RBA_ETHARP_E_RXINDICATION_API_ID,           \
                                          RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    for (lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++)
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if(lArpSubCfg_pco->EthIfCtrIdx_cu8 == lCtrlIdx_u8)
        {
            /*Get the state of the EthIf Controller*/
            lTcpIpEthIfCtrlSt_en = TcpIp_GetEthIfCtrlState(lCtrlIdx_u8);

            /* If the EthIf Controller State is ONLINE or STARTUP */
            if(( TCPIP_STATE_ONLINE == lTcpIpEthIfCtrlSt_en ) || ( TCPIP_STATE_STARTUP == lTcpIpEthIfCtrlSt_en ))
            {
                /* Check the length of the frame received */
                if ( lRxDataLen_u16 >= RBA_ETHARP_HDR_LENGTH )
                {
                    /* Identify the ARP header
                     * Copy the data from the buffer in the ARP Header Structure */
                    rba_EthArp_BufferToHeader( &lArpHdr_st, lRxDataPtr );

                    /****************************/
                    /* Process ARP Frame Received */
                    /****************************/
                    lRetVal_tu8 = rba_EthArp_ProcessReceivedFrm(lCtrlIdx_u8, lArpHdr_st, lArpSubCfg_pco);

                }
                else
                {   /* Wrong Length of Frame */
                    /* Report DET if value of lRxDataLen_u16 is invalid */
                    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lRxDataLen_u16 < RBA_ETHARP_HDR_LENGTH ), RBA_ETHARP_E_RXINDICATION_API_ID,   \
                                                          RBA_ETHARP_E_INV_ARG, E_NOT_OK )
                }
            }
            else
            {
                /* EthIf Controller State is OFFLINE */
                lRetVal_tu8 = E_NOT_OK;
            }


            /* CtrlIdx Found : Break the loop */
            break;
        }
    } /* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid and return TCPIP_E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),     \
    		                               RBA_ETHARP_E_RXINDICATION_API_ID, RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    return lRetVal_tu8;
}


/*************************************************************************************************/
/* rba_EthArp_ProcessReceivedFrm() - Function called to process the Received ARP Frame           */
/* Rx process defined in the RFC826 - Packet Reception                                           */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8     - EthIf controller index                                                     */
/*  lArpHdr_st      - ARP header structure to hold the received frame values.                    */
/*  lArpSubCfg_pco  - Sub Configuration data of the ARP module.                                  */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetVal_en      - E_OK the ARP Frame received has been Processed.                            */
/*                  - E_NOT_OK  the ARP Frame received has not been Processed.                   */
/*                                                                                               */
/*                                                                                               */
/*************************************************************************************************/

LOCAL_INLINE FUNC( Std_ReturnType,   RBA_ETHARP_CODE )   rba_EthArp_ProcessReceivedFrm( VAR( uint8, AUTOMATIC ) lCtrlIdx_u8,
                                                                                        VAR( rba_EthArp_Hdr_tst, AUTOMATIC )  lArpHdr_st,
                                                                                        P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco )
{

    VAR( uint32, AUTOMATIC )                                lRxSrcIPv4Addr_u32;
    VAR( uint32, AUTOMATIC )                                lRxDstIPv4Addr_u32;
    VAR( uint32, AUTOMATIC )                                lMySrcIPv4Addr_u32;
    VAR( uint32, AUTOMATIC )                                lNetMask_u32;
    VAR( uint16, AUTOMATIC )                                lIndexTable_u16;
    VAR( boolean, AUTOMATIC )                               lMergeFlag_b;
    VAR( uint8, AUTOMATIC )                                 lLoop_u8;
    VAR( uint8, AUTOMATIC )                                 lRxSrcEthAddr_au8[RBA_ETHARP_HWADDR_LENGTH];
    VAR( Std_ReturnType, AUTOMATIC )                        lStdRetVTypeVal_tu8;
    VAR( Std_ReturnType, AUTOMATIC )                        lStdRetVal_CheckIP_tu8;
    VAR( Std_ReturnType, AUTOMATIC )                        lRetVal_tu8;
    VAR( Std_ReturnType, AUTOMATIC )                        lStdRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                        lFctRetVal_en;
    VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC )     lIpAddrInArpTable_en;

    lRetVal_tu8 = E_NOT_OK;
    lStdRetVal_CheckIP_tu8  = E_NOT_OK;
    lMergeFlag_b           = FALSE;
    lIndexTable_u16         = 0;

    /* Required by RFC 826 */
    if ( ( ( lArpHdr_st.hwType_u16 )    == RBA_ETHARP_ETH_HW_TYPE ) &&      /* Check the HW type                */
            ( ( lArpHdr_st.protoType_u16 ) == TCPIP_TYPE_IPV4 )        &&      /* Check the Protocol type          */
            ( ( lArpHdr_st.hwAddrLen_u8 )  == RBA_ETHARP_HWADDR_LENGTH)&&      /* Check the HW length (optionally) */
            ( ( lArpHdr_st.protoLen_u8 )   == RBA_ETHARP_IPADDR_LENGTH ))      /* Check the IP length (optionally) */
    {
        /************************************/
        /* Get info from ARP Frame Received */
        /************************************/

        /* Get IP Address from the ARP Frame Received */
        lRxSrcIPv4Addr_u32 = ( lArpHdr_st.srcIpAddr_u32 );
        lRxDstIPv4Addr_u32 = ( lArpHdr_st.destIpAddr_u32 );

        /* Get MAC Address from the ARP Frame Received */
        for (lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
        {
            lRxSrcEthAddr_au8[lLoop_u8] = ( lArpHdr_st.srcHwAddr_au8[lLoop_u8] );
        }

        /*********************************/
        /* IP Conflict Detection Process */
        /*********************************/
    #if(TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES == STD_ON)

        lStdRetVal_CheckIP_tu8 = rba_EthArp_IpConflictDetection(
                                                                lCtrlIdx_u8,
                                                                lRxSrcIPv4Addr_u32,
                                                                lRxDstIPv4Addr_u32,
                                                                &lRxSrcEthAddr_au8[0],
                                                                TCPIP_TYPE_ARP);

    #endif /* (TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES == STD_ON) */

        /* If no IP Conflict detected */
        if(E_NOT_OK == lStdRetVal_CheckIP_tu8)
        {
            /***********************************************/
            /* Check Parameter of the ARP Frame Received   */
            /***********************************************/

            /* Check if the IP Address received is already in the ARP Table */
            lFctRetVal_en = rba_EthArp_CheckIpTableEntry( lArpSubCfg_pco,
                                                            &lIndexTable_u16,
                                                            lRxSrcIPv4Addr_u32,
                                                            &lIpAddrInArpTable_en );

            if ( lFctRetVal_en == E_OK )
            {
                /* if the address is in the ARP Table => Update the entry with new value */
                if(RBA_ETHARP_FREE_ENTRY != lIpAddrInArpTable_en)
                {
                    /* Overwrite the entry with the IP/MAC Address */
                    rba_EthArp_UpdateArpTableEntry(
                                                    &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                                                    lCtrlIdx_u8,
                                                    RBA_ETHARP_ENTRY_USED,
                                                    lRxSrcIPv4Addr_u32,
                                                    &lRxSrcEthAddr_au8[0],
                                                    TCPIP_IPADDR_ASSIGNMENT_INVALID);

                    /* Entry already updates = TRUE */
                    lMergeFlag_b = TRUE;
                }

                /* Get the source/host IPv4 address based on socket handle id from configuration table */
                lStdRetVTypeVal_tu8 = TcpIp_GetIPv4AddrFrmCtrlIdx( lCtrlIdx_u8, &lMySrcIPv4Addr_u32, &lNetMask_u32 );

                /* If MyIpAddress have been returned */
                if( E_OK == lStdRetVTypeVal_tu8 )
                {
                    /* If IP address in ARP Frame == My IP address */
                    if ( lRxDstIPv4Addr_u32 == lMySrcIPv4Addr_u32 )
                    {
                        /* If entry not already updated */
                        if(FALSE == lMergeFlag_b)
                        {
                            /* Check entry available to store the new IP */
                            lStdRetVal_en =   rba_EthArp_GetUsableEntry( lArpSubCfg_pco,
                                    &lIndexTable_u16 );

                            if( lStdRetVal_en == E_OK )
                            {
                                /* Update new the entry with the IP/MAC Address */
                                rba_EthArp_UpdateArpTableEntry(
                                                                &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                                                                lCtrlIdx_u8,
                                                                RBA_ETHARP_ENTRY_USED,
                                                                lRxSrcIPv4Addr_u32,
                                                                &lRxSrcEthAddr_au8[0],
                                                                TCPIP_IPADDR_ASSIGNMENT_INVALID );
                            }
                        }

                        /* If ARP Frame request received => Send an ARP Reply */
                        if( RBA_ETHARP_ARP_REQUEST == ( lArpHdr_st.arpOpCode_u16 ) )
                        {
                            /* Update state of the entry */
                            lArpSubCfg_pco->ArpTable_past[lIndexTable_u16].procEntryState_en = RBA_ETHARP_RPLY_TO_BE_SENT;
                        }
                    }
                    else
                    {
                        /* Destination IP address in ARP Frame != My IP address */
                    }
                }
                else
                {
                    /*
                     * If MyIpAddress have not been returned by
                     * TcpIp_GetIPv4AddrFrmCtrlIdx()
                     */
                }
            }  /* lFctRetVal_en == E_OK */
        }
        else
        {
            /*
             * If IP conflict detected
             * Actions made in the function
             * rba_EthAutoIp_ArpReply()
             */
        }

        /* The ARP Frame received has been parsed */
        lRetVal_tu8 = E_OK;
    }

    return lRetVal_tu8;

}





#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */


