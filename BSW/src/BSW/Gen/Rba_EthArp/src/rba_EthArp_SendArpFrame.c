

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )
#include "rba_EthArp.h"

#include "EthIf.h"
#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - TcpIp and EthIf"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - TcpIp and EthIf"
#endif

#include "rba_EthArp_Prv.h"

/*************************************************************************************************/
/* rba_EthArp_SendArpFrame() -                                                                   */
/* Function called to send ARP Frame (REPLY / REQUEST / PROBE)                                   */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8         - index of the Ethernet controller                                       */
/*  lIndexTable_u16     - index of the entry in the ARP Table                                    */
/*  lDestIPv4Addr_u32   - IP address of the host to which the frame must be sent                 */
/*  lDestEthAddr_au8    - MAC address of the host to which the frame must be sent                */
/*  lTypeFrame_u8       - Type of frame to send : Reply / Request / Probe                        */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetValStdType_en - Request Sent E_OK or E_NOT_OK                                            */
/*                                                                                               */
/*************************************************************************************************/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
FUNC( Std_ReturnType,   RBA_ETHARP_CODE )   rba_EthArp_SendArpFrame         (
                                                                VAR( uint8,                AUTOMATIC )      lCtrlIdx_u8,
                                                                VAR( uint16,               AUTOMATIC )      lIndexTable_u16,
                                                                VAR( uint32,               AUTOMATIC )      lDestIPv4Addr_u32,
                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )      lDestEthAddr_au8,
                                                                VAR( uint8,                AUTOMATIC )      lTypeFrame_u8)
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                    lBufPtr;
    VAR( rba_EthArp_Hdr_tst, AUTOMATIC )                    lEthArp_st;

    VAR( uint32, AUTOMATIC )                lSrcIPv4Addr_u32;
    VAR( uint32, AUTOMATIC )                lNetMask_u32;
    VAR( uint16, AUTOMATIC )                lLength_u16;
    VAR( uint16, AUTOMATIC )                lFrameType_u16;
    VAR( uint8, AUTOMATIC )             	lTableLoop_u8;
    VAR( uint8, AUTOMATIC )             	lLoop_u8;
    VAR( uint8, AUTOMATIC )             	lSrcEthAddr_au8[RBA_ETHARP_HWADDR_LENGTH];
    VAR( uint8, AUTOMATIC )             	lDestEthAddr_EthHdr_au8[RBA_ETHARP_HWADDR_LENGTH];
    VAR( uint8, AUTOMATIC )             	lBufIdx_u8;
    VAR( uint8, AUTOMATIC )             	lPriority_u8;
    VAR( Std_ReturnType, AUTOMATIC )        lRetValStdType_en;
    VAR( BufReq_ReturnType, AUTOMATIC )     lRetVal_TxBufReq_en;
    VAR( TcpIp_StateType, AUTOMATIC )       lTcpIpEthIfCtrlSt_en;

    /* Local variable initialization */
    lRetValStdType_en   = E_NOT_OK;
    lRetVal_TxBufReq_en = BUFREQ_E_NOT_OK;
    lPriority_u8        = 0;
    lSrcIPv4Addr_u32    = 0;
    lBufIdx_u8          = 0;
    lLength_u16         = RBA_ETHARP_HDR_LENGTH;    /* Required buffer length */
    lFrameType_u16      = ETHIF_FRAMETYP_ARP;
    lBufPtr             = NULL_PTR;
    lArpSubCfg_pco      = NULL_PTR;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_SEND_ARPFRAME_API_ID,   \
                                           RBA_ETHARP_E_NOTINIT, E_NOT_OK )

    /* Report DET if lIndexTable_u16 is invalid  */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lIndexTable_u16 >= ( rba_EthArp_ConfigPtr_pco->TableSizeMax_u16) ),    \
                                           RBA_ETHARP_E_SEND_ARPFRAME_API_ID, RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    for (lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++)
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if(lArpSubCfg_pco->EthIfCtrIdx_cu8 == lCtrlIdx_u8)
        {
            /* Get the state of the EthIf Controller */
            lTcpIpEthIfCtrlSt_en = TcpIp_GetEthIfCtrlState(lCtrlIdx_u8);

            /* If the EthIf Controller State is ONLINE or STARTUP */
            if(( TCPIP_STATE_ONLINE == lTcpIpEthIfCtrlSt_en ) || ( TCPIP_STATE_STARTUP == lTcpIpEthIfCtrlSt_en ))
            {
                if((lTypeFrame_u8 == RBA_ETHARP_ARP_REPLY_FRAME) || (lTypeFrame_u8 == RBA_ETHARP_ARP_REQUEST_FRAME))
                {
                    /* Report DET if lDestEthAddr_au8 is a Null Pointer */
                    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lDestEthAddr_au8 ), RBA_ETHARP_E_SEND_ARPFRAME_API_ID,     \
                                                            RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

                    /* Get the source/host IPv4 address based on socket handle id from configuration table */
                    lRetValStdType_en = TcpIp_GetIPv4AddrFrmCtrlIdx( lCtrlIdx_u8, &lSrcIPv4Addr_u32, &lNetMask_u32 );
                }
                else
                {
                    /* Don't need if ARP PROBE Frame */
                	lRetValStdType_en = E_OK;
                }

                if(E_OK ==lRetValStdType_en)
                {
                	/* Get the statically configured frame priority (TcpIpIpFramePrioDefault) */
                	lPriority_u8 = lArpSubCfg_pco->TcpIpCtrlFramePrio_cu8;

                    /* Call the EthIf_ProvideTxBuffer() to allocate memory for the data to be transmitted */
                    lRetVal_TxBufReq_en = EthIf_ProvideTxBuffer(lCtrlIdx_u8,
                                                                lFrameType_u16,
                                                                lPriority_u8,
                                                                &lBufIdx_u8,
                                                                &lBufPtr,
                                                                &lLength_u16 );
                }
            }

            /* If the CtrlIdx Table has been found */
            break;
        }
    } /* End of for Table loop */

    if ( BUFREQ_OK == lRetVal_TxBufReq_en )
    {
        /* Get the source Ethernet address based on the controller index */
        EthIf_GetPhysAddr( lCtrlIdx_u8, (uint8 *)&lSrcEthAddr_au8[0] );

        lLength_u16 = RBA_ETHARP_HDR_LENGTH;

        /**** ARP HEADER FRAME ****/
        ( lEthArp_st.hwType_u16 )   = RBA_ETHARP_ETH_HW_TYPE;
        ( lEthArp_st.protoType_u16 )= ETHIF_FRAMETYP_IPv4;
        ( lEthArp_st.hwAddrLen_u8 ) = RBA_ETHARP_HWADDR_LENGTH;
        ( lEthArp_st.protoLen_u8 )  = RBA_ETHARP_IPADDR_LENGTH;

        switch(lTypeFrame_u8)
        {
            /* If entry have to send an ARP REPLY */
            case RBA_ETHARP_ARP_REPLY_FRAME :
            {
                /* Update the destination and source IP address in the corresponding locations */
                ( lEthArp_st.srcIpAddr_u32 )  = lSrcIPv4Addr_u32;
                ( lEthArp_st.destIpAddr_u32 ) = lDestIPv4Addr_u32;

                /* Update the type of operation (Request Or Reply )*/
                ( lEthArp_st.arpOpCode_u16 ) = RBA_ETHARP_ARP_REPLY;

                /* Update the destination and source address in the corresponding locations */
                for ( lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++ )
                {
                    /* ETH HEADER FRAME
                     * Destination MAC Address */
                    lDestEthAddr_EthHdr_au8[lLoop_u8] = (uint8) lDestEthAddr_au8[lLoop_u8] ;

                    /* ARP HEADER FRAME */
                    ( lEthArp_st.destHwAddr_au8[lLoop_u8] ) = (uint8) lDestEthAddr_au8[lLoop_u8];
                    ( lEthArp_st.srcHwAddr_au8[lLoop_u8] )  = (uint8) lSrcEthAddr_au8[lLoop_u8];
                }
            }
            break;

            /* If entry have to send an ARP REQUEST */
            case RBA_ETHARP_ARP_REQUEST_FRAME :
            {
                /* Update the destination and source IP address in the corresponding locations */
                ( lEthArp_st.srcIpAddr_u32 )  = lSrcIPv4Addr_u32;
                ( lEthArp_st.destIpAddr_u32 ) = lDestIPv4Addr_u32;

                /* Update the type of operation (Request Or Reply )*/
                ( lEthArp_st.arpOpCode_u16  ) = RBA_ETHARP_ARP_REQUEST;

                /* Update the destination and source address in the corresponding locations */
                for ( lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++ )
                {
                    /* ETH HEADER FRAME
                     * MAC Address of the dest  : FF.FF.FF.FF.FF.FF = Broadcast */
                    lDestEthAddr_EthHdr_au8[lLoop_u8]       = 0xFF ;
                    /* ARP HEADER FRAME
                     * MAC Address of the dest not known : 00.00.00.00.00.00 */
                    ( lEthArp_st.destHwAddr_au8[lLoop_u8] ) = (uint8) 0x00;
                    ( lEthArp_st.srcHwAddr_au8[lLoop_u8] )  = (uint8) lSrcEthAddr_au8[lLoop_u8];
                }

            }
            break;

            /*
             * If entry have to send an ARP PROBE
             * Equivalent to an ARP REQUEST with Src IP address = 0.0.0.0
             */
            case RBA_ETHARP_ARP_PROBE_FRAME :
            {
                /* Update the destination and source IP address in the corresponding locations */
                ( lEthArp_st.srcIpAddr_u32 )  = (uint32) 0x00;
                ( lEthArp_st.destIpAddr_u32 ) = lDestIPv4Addr_u32;

                /* Update the type of operation (Request Or Reply )*/
                ( lEthArp_st.arpOpCode_u16 ) = RBA_ETHARP_ARP_REQUEST;

                /* Update the destination and source address in the corresponding locations */
                for ( lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++ )
                {
                    /* ETH HEADER FRAME
                     * MAC Address of the dest  : FF.FF.FF.FF.FF.FF = Broadcast */
                    lDestEthAddr_EthHdr_au8[lLoop_u8] = 0xFF ;

                    /* ARP HEADER FRAME
                     * MAC Address of the dest not known : 00.00.00.00.00.00 */
                    ( lEthArp_st.destHwAddr_au8[lLoop_u8] ) = (uint8) 0x00;
                    ( lEthArp_st.srcHwAddr_au8[lLoop_u8] )  = (uint8) lSrcEthAddr_au8[lLoop_u8];
                }
             }
            break;

            default :
            {
                /* Nothing to do */
            }
            break;
        }

        /* Copy data from the ARP header in the Tx buffer */
        rba_EthArp_HeaderToBuffer( &lEthArp_st, &lBufPtr[0]);

        /* Call the transmit function after all the payload and header pointers are updated in the Tx descriptor tables */
        lRetValStdType_en = EthIf_Transmit(  lCtrlIdx_u8,
                                             lBufIdx_u8,
                                             lFrameType_u16,
                                             FALSE,                    /* TcpIp shall always call EthIf_Transmit() with parameter TxConfirmation set to FALSE. */
                                             lLength_u16,
                                             (uint8 *)&(lDestEthAddr_EthHdr_au8[0]));

        /* If the Arp Request Frame is successfully sent update Arp table */
        if( ( RBA_ETHARP_ARP_REQUEST_FRAME == lTypeFrame_u8 ) &&
            ( E_OK == lRetValStdType_en ) )
        {
            /* Store the IP Address with MAC addr null and ReplyPending status */
            rba_EthArp_UpdateArpTableEntry( &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                                            lCtrlIdx_u8,
                                            RBA_ETHARP_RPLY_PENDING,
                                            lDestIPv4Addr_u32,
                                            &lDestEthAddr_au8[0],
                                            TCPIP_IPADDR_ASSIGNMENT_INVALID );
        }

    }
    else
    {
    	lRetValStdType_en = E_NOT_OK;
    }

    /* Report DET if value of lCtrlIdx_u8 is not valid and return E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),    \
    		                               RBA_ETHARP_E_SEND_ARPFRAME_API_ID, RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    return lRetValStdType_en;
}

/*************************************************************************************************/
/* rba_EthArp_SendArpGratuitousFrame() -                                                         */
/* Function called to send ARP Gratuitous Frame ( GRATUITOUS )                                   */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lCtrlIdx_u8         - index of the Ethernet controller                                       */
/*  lSrcIPv4Addr_u32    - Source IP to use to fill the ARP header Frame                          */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetValStdType_en - Frame Sent E_OK or E_NOT_OK                                              */
/*                                                                                               */
/*************************************************************************************************/
FUNC( Std_ReturnType,   RBA_ETHARP_CODE )   rba_EthArp_SendArpGratuitousFrame   (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                VAR( uint32, AUTOMATIC )        lSrcIPv4Addr_u32)
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC )         lArpSubCfg_pco;
    VAR( rba_EthArp_Hdr_tst,                     AUTOMATIC )         lEthArp_st;
    VAR( uint16,                                 AUTOMATIC )         lLength_u16;
    VAR( uint8,                                  AUTOMATIC )         lTableLoop_u8;
    VAR( uint8,                                  AUTOMATIC )         lLoop_u8;
    VAR( uint8,                                  AUTOMATIC )         lSrcEthAddr[RBA_ETHARP_HWADDR_LENGTH];
    VAR( uint8,                                  AUTOMATIC )         lDestEthAddr_EthHdr_au8[RBA_ETHARP_HWADDR_LENGTH];
    VAR( uint8,                                  AUTOMATIC )         lBufIdx_u8;
    VAR( uint8,                                  AUTOMATIC )         lPriority_u8;
    P2VAR( uint8,                     AUTOMATIC, AUTOMATIC )         lBufPtr;
    VAR( Std_ReturnType,                         AUTOMATIC )         lRetValStdType_en;
    VAR( BufReq_ReturnType,                      AUTOMATIC )         lRetVal_TxBufReq_en;
    VAR( TcpIp_StateType,                        AUTOMATIC )         lTcpIpEthIfCtrlSt_en;

    /* Local variable initialization */
    lRetValStdType_en         = E_NOT_OK;
    lRetVal_TxBufReq_en = BUFREQ_E_NOT_OK;
    lPriority_u8        = 0;
    lLength_u16         = RBA_ETHARP_HDR_LENGTH;    /* Required buffer length */
    lBufIdx_u8          = 0;
    lBufPtr             = NULL_PTR;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_SEND_ARP_GRATUITOUSFRAME_API_ID,   \
                                           RBA_ETHARP_E_NOTINIT, E_NOT_OK )

    /* Go through the Table */
    for(lTableLoop_u8 = 0; ( lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ); lTableLoop_u8++ )
    {
        /* Local Copy of the ARP SubConfig Structure */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if( lCtrlIdx_u8 == lArpSubCfg_pco->EthIfCtrIdx_cu8 )
        {
            /*Get the state of the EthIf Controller*/
            lTcpIpEthIfCtrlSt_en = TcpIp_GetEthIfCtrlState(lCtrlIdx_u8);

            /* If the EthIf Controller State is ONLINE or STARTUP */
            if(( TCPIP_STATE_ONLINE == lTcpIpEthIfCtrlSt_en ) || ( TCPIP_STATE_STARTUP == lTcpIpEthIfCtrlSt_en ))
            {
            	/* Get the statically configured frame priority (TcpIpIpFramePrioDefault) */
            	lPriority_u8 = lArpSubCfg_pco->TcpIpCtrlFramePrio_cu8;

                /* Call the EthIf_ProvideTxBuffer() to allocate memory for the data to be transmitted */
                lRetVal_TxBufReq_en = EthIf_ProvideTxBuffer(
                                                        lCtrlIdx_u8,
                                                        ETHIF_FRAMETYP_ARP,
                                                        lPriority_u8,
                                                        &lBufIdx_u8,
                                                        &lBufPtr,
                                                        &lLength_u16 );
            }

            /* CtrlIdx have been found => Break the loop */
            break;
        }
    }

    if ( BUFREQ_OK == lRetVal_TxBufReq_en )
    {
        /* Get the source Ethernet address based on the controller index */
        EthIf_GetPhysAddr( lCtrlIdx_u8, (uint8 *)&lSrcEthAddr[0] );

        lLength_u16 = RBA_ETHARP_HDR_LENGTH;

        /* ARP HEADER FRAME */
        ( lEthArp_st.hwType_u16 )   = RBA_ETHARP_ETH_HW_TYPE;
        ( lEthArp_st.protoType_u16 )= ETHIF_FRAMETYP_IPv4;
        ( lEthArp_st.hwAddrLen_u8 ) = RBA_ETHARP_HWADDR_LENGTH ;
        ( lEthArp_st.protoLen_u8 )  = RBA_ETHARP_IPADDR_LENGTH;

        /*
         * Update the destination and source IP address in the corresponding locations
         * For an ARP Gratuitous Frame, the target and the source addr are the same :
         * the sender address
         */
        ( lEthArp_st.srcIpAddr_u32 )  = lSrcIPv4Addr_u32;
        ( lEthArp_st.destIpAddr_u32 ) = ( lEthArp_st.srcIpAddr_u32 );

        /* Update the type of operation ( Request )*/
        ( lEthArp_st.arpOpCode_u16 )  = RBA_ETHARP_ARP_REQUEST;

        /* Update the destination and source address in the corresponding locations */
        for ( lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++ )
        {
            /* ETH HEADER FRAME
             * MAC Address of the dest  : FF.FF.FF.FF.FF.FF = Broadcast */
            lDestEthAddr_EthHdr_au8[lLoop_u8] = 0xFF ;

            /* ARP HEADER FRAME
             * MAC Address of the dest not known : 00.00.00.00.00.00 */
            ( lEthArp_st.destHwAddr_au8[lLoop_u8] )  = (uint8) 0x00;
            ( lEthArp_st.srcHwAddr_au8[lLoop_u8] )   = (uint8) lSrcEthAddr[lLoop_u8];
        }

        /* Copy data from the ARP header in the Tx buffer */
        rba_EthArp_HeaderToBuffer( &lEthArp_st, &lBufPtr[0]);

        lRetValStdType_en = EthIf_Transmit(
                                lCtrlIdx_u8,
                                lBufIdx_u8,
                                ETHIF_FRAMETYP_ARP,
                                FALSE,                    /* TcpIp shall always call EthIf_Transmit() with parameter TxConfirmation set to FALSE. */
                                lLength_u16,
                                (uint8 *)&(lDestEthAddr_EthHdr_au8[0]));
     }

    /* Report DET if value of lCtrlIdx_u8 is not valid and return E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ), RBA_ETHARP_E_SEND_ARP_GRATUITOUSFRAME_API_ID,   \
    		                               RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    return lRetValStdType_en;
}
#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

