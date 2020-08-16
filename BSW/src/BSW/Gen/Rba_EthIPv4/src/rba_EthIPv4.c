
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )
#include "rba_EthIPv4.h"

#include "TcpIp_Prv.h"
#include "rba_EthIPv4_Prv.h"

#if ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON )
#include "rba_EthIcmp.h"
#endif

/* DET version check */
#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* ( TCPIP_DEV_ERROR_DETECT != STD_OFF ) */

/*
 ***************************************************************************************************
 * Global Variables
 ***************************************************************************************************
 */

#define RBA_ETHIPV4_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

/* Pointer - will be initialized in the Init Function */
CONSTP2CONST( rba_EthIPv4_CtrlCfg_tst, AUTOMATIC, AUTOMATIC ) * rba_EthIPv4_CtrlCfg_pcpcst = NULL_PTR;

#define RBA_ETHIPV4_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

/********************************************************************************************************************/
/* rba_EthIPv4_Init()           This function Initializes the rba_EthIPv4 module                                    */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* CurrConfig_pco               Configuration data structure for rba_EthIPv4 module                                 */
/*                                                                                                                  */
/* Return type :                void                                                                                */
/********************************************************************************************************************/
#define RBA_ETHIPV4_START_SEC_CODE
#include "rba_EthIPv4_MemMap.h"
FUNC( void, RBA_ETHIPV4_CODE ) rba_EthIPv4_Init (
                                        P2CONST( rba_EthIPv4_Config_to, AUTOMATIC, AUTOMATIC ) CurrConfig_pco )
{
#if ( ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) || ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) )
    VAR( uint8,  AUTOMATIC )         lCtrlLoopIdx_u8;
    VAR( uint16, AUTOMATIC )         lLoopIdx_u16;
#endif

    /* Report DET if TcpIp_CurrConfig_pco is not initialized */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == TcpIp_CurrConfig_pco ),                                  \
                                           RBA_ETHIPV4_E_INIT_API_ID, RBA_ETHIPV4_E_INIT_FAILED )

    /* Report DET if CurrConfig_pco does not contain a valid configuration */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( ( CurrConfig_pco != ( TcpIp_CurrConfig_pco->EthIPv4Config_pco) ),      \
                                           RBA_ETHIPV4_E_INIT_API_ID, RBA_ETHIPV4_E_INV_ARG )

    /* Initialize configuration structure */
    rba_EthIPv4_CtrlCfg_pcpcst = CurrConfig_pco->IPv4CtrlCfg_pco;

#if ( ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) || ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) )
    /* Loop through IPv4 controllers configured */
    for(lCtrlLoopIdx_u8 = 0; lCtrlLoopIdx_u8 < TCPIP_NUMETHIFCTRL; lCtrlLoopIdx_u8++)
    {
        /* If the EthIfCtrl referenced by loop index is an IPv4 controller */
        if(rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8] != NULL_PTR)
        {
        #if ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON )  /* If fragmentation is configured for any of the controller */
            /* If the fragmentation is enabled for the controller initialize length member of zeroth element of the fragmentation table to buffer size and free buffer position to zero */
            if(NULL_PTR != rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBuf_cpu8)
            {
                rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufTbl_cpst[0].FreeBufPos_u32 = 0U;
                rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufTbl_cpst[0].FreeBufLength_u32 = rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufSize_cu32;

                /* Initialize remaining element of the fragmentation table to zero */
                for(lLoopIdx_u16 = 1; lLoopIdx_u16 < rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufTblSize_cu16; lLoopIdx_u16++)
                {
                    rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufTbl_cpst[lLoopIdx_u16].FreeBufPos_u32 = 0U;
                    rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->TxFragBufTbl_cpst[lLoopIdx_u16].FreeBufLength_u32 = 0U;
                }
            }
        #endif   /* #if ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) */

        #if( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON )   /* If reassembly is configured for any of the controller */
           if(NULL_PTR != rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->ReassemblyBufDescriptor_cpst)
           {
               /* Initialize reassembly pending timeout value (TimerCurrentValue_u32) to zero for all configured reassembly buffers. */
               for(lLoopIdx_u16 = 0; lLoopIdx_u16 < rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->ReassemblyBufCnt_cu8; lLoopIdx_u16++)
               {
                   rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->ReassemblyBufDescriptor_cpst[lLoopIdx_u16].TimerCurrentValue_u32 = 0;
               }
           }
        #endif   /* #if( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) */
        }
    }
#endif   /* #if ( ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) || ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) ) */
}



/********************************************************************************************************************/
/* rba_EthIPv4_MainFunction() - This function decrements reassembly timer by value corresponding to                 */
/*                              TCPIP_MAIN_FUNCTIONPERIOD_MS releases the reassembly resources and triggers         */
/*                              transmission of ICMP Time Exceeded message upon timeout.                            */
/*                                                                                                                  */
/* Input Parameters :  void                                                                                         */
/*                                                                                                                  */
/* Return type :       void                                                                                         */
/********************************************************************************************************************/
#if ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON )
FUNC( void, TCPIP_CODE ) rba_EthIPv4_MainFunction( void )
{
    /* Local variable declaration */
    P2VAR( rba_EthIPv4_ReassemblyBufDescriptor_tst, AUTOMATIC, AUTOMATIC )         lReassemblyBufDescriptor_pst;
    VAR( uint8,                                                AUTOMATIC )         lCtrlLoopIdx_u8;
    VAR( uint8,                                                AUTOMATIC )         lReassemblyBufLoopIdx_u8;

#if ( TCPIP_ICMP_ENABLED == STD_ON )
    VAR( TcpIp_LocalAddrIdType,                                AUTOMATIC )         lLocalAddrId_u8;
    VAR( uint32,                                               AUTOMATIC )         lNetMask_u32;
    VAR( uint32,                                               AUTOMATIC )         lLocalIp_u32;
    VAR( Std_ReturnType,                                       AUTOMATIC )         lStdRetVal_en;
    VAR( uint16,                                               AUTOMATIC )         lIcmpFrameLength_u16;
    VAR( TcpIp_SockAddrInetType,                               AUTOMATIC )         lRemoteAddr_st;

    /* Initialize local variables */
    lLocalIp_u32    = 0;
    lLocalAddrId_u8 = 0xFFU;
#endif


    /* Report DET if rba_EthIPv4 module is uninitialised */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == rba_EthIPv4_CtrlCfg_pcpcst ), RBA_ETHIPV4_E_MAIN_FUNCTION_API_ID, RBA_ETHIPV4_E_NOTINIT )

    /* Loop through all the IPv4 controllers configured */
    for(lCtrlLoopIdx_u8 = 0; lCtrlLoopIdx_u8 < TCPIP_NUMETHIFCTRL; lCtrlLoopIdx_u8++)
    {
        /* Check if the EthIfCtrl referred by loop index is an IPv4 controller */
        if(NULL_PTR != rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8])
        {
            /* Loop through all the reassembly buffers configured for the controller */
            for(lReassemblyBufLoopIdx_u8 = 0; lReassemblyBufLoopIdx_u8 < rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->ReassemblyBufCnt_cu8; lReassemblyBufLoopIdx_u8++)
            {
                lReassemblyBufDescriptor_pst = ( rba_EthIPv4_CtrlCfg_pcpcst[lCtrlLoopIdx_u8]->ReassemblyBufDescriptor_cpst + lReassemblyBufLoopIdx_u8 );

                /* Check if the reassembly is active for this buffer */
                if(0U != lReassemblyBufDescriptor_pst->TimerCurrentValue_u32)
                {
                    /* Decrement time out tick by 1 (Here each tick corresponds to TcpIp main function period ) */
                    lReassemblyBufDescriptor_pst->TimerCurrentValue_u32--;

                    /* If the reassembly timer expires */
                    if(0U == lReassemblyBufDescriptor_pst->TimerCurrentValue_u32)
                    {
#if ( TCPIP_ICMP_ENABLED == STD_ON )

                        /* Get Unicast IP and Netmask assigned to the EthIfCtrl on which frame was received */
                        lStdRetVal_en = TcpIp_GetIPv4AddrFrmCtrlIdx(    lCtrlLoopIdx_u8,
                                                                        &lLocalIp_u32,
                                                                        &lNetMask_u32 );


                       if( (0U != lReassemblyBufDescriptor_pst->FirstHolePos_u16) &&         /* Check if first fragment is received. ICMP Time Exceeded message shall be sent only if the first eight bytes of IPv4 payload is received */
                           (lLocalIp_u32 == lReassemblyBufDescriptor_pst->DstIp_u32) &&      /* ICMP frame shall be sent only if the destination IP is unicast. */
                           (E_OK == lStdRetVal_en) )
                       {
                           lStdRetVal_en = TcpIp_GetLocalAddrIdForRxFrame( lCtrlLoopIdx_u8,
                                                                           lLocalIp_u32,
                                                                           &lLocalAddrId_u8 );
                       }
                       else
                       {
                           lStdRetVal_en = E_NOT_OK;
                       }

                       /* Trigger ICMP Time Exceeded message. */
                       if(E_OK == lStdRetVal_en)
                       {
                           /* The ICMP message shall contain IPv4 header + First eight octets of the received frame  */
                           lIcmpFrameLength_u16 = ( ( (lReassemblyBufDescriptor_pst->IcmpTimeExceededPayload_au8[RBA_ETHIPV4_IPV4VER_HDRLEN_TOS_UB]) & 0x0fU ) * 4U) + 8U;

                           /* Get remote IP information from buffer descriptor */
                           lRemoteAddr_st.addr[0] = lReassemblyBufDescriptor_pst->SrcIp_u32;

                           lStdRetVal_en = rba_EthIcmp_Transmit ( lLocalAddrId_u8,
                                                                  &lRemoteAddr_st,
                                                                  0,                                           /* TTL = 0 indicates default value will be used */
                                                                  (uint8) RBA_ETHICMP_TIME_EXCEED_E,
                                                                  (uint8)RBA_ETHICMP_TIME_EXCEED_FRAG_E,
                                                                  lIcmpFrameLength_u16,
                                                                  (lReassemblyBufDescriptor_pst->IcmpTimeExceededPayload_au8) );
                       }
#endif    /*( TCPIP_ICMP_ENABLED == STD_ON ) */

                       /* Clear total payload length to zero. */
                       lReassemblyBufDescriptor_pst->TotalPalyloadLen_u16 = 0U;
                    }
                }
            }
        }
    }
    return;
}
#endif  /* ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) */


/********************************************************************************************************************/
/* rba_EthIPv4_ChkIPv4AddrType() - Return the IPv4 destination address type -  Unicast / Broadcast / Multicast      */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  DestIpAddr_u32      - Destination IPv4 address type                                                             */
/*  SrcIpAddr_u32       - Source IPv4 address type                                                              */
/*  NetMask_u32         - NetMask of the LocalAddr Index                                                            */
/*                                                                                                                  */
/* Return                                                                                                           */
/*  TcpIp_AddressType   - Unicast OR Multicast OR Broadcast                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( TcpIp_AddressType, RBA_ETHIPV4_CODE ) rba_EthIPv4_ChkIPv4AddrType(    VAR( uint32, AUTOMATIC )    DestIpAddr_u32,
                                                                            VAR( uint32, AUTOMATIC )    SrcIpAddr_u32,
                                                                            VAR( uint32, AUTOMATIC )    NetMask_u32 )
{
    VAR( TcpIp_AddressType, AUTOMATIC )         lRetAddrType_en;

    /* Check for DET errors */
    /* Report DET if rba_EthIPv4 module is uninitialised */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == rba_EthIPv4_CtrlCfg_pcpcst ), RBA_ETHIPV4_E_CHK_IPV4ADDR_TYPE_API_ID,    \
                                            RBA_ETHIPV4_E_NOTINIT, TCPIP_NONE )

    /* Check whether the destination IPv4 address is in the Multicast address range - 224.0.0.0 to 239.255.255.255 */
     if (   ( DestIpAddr_u32 <= RBA_ETHIPV4_MULTICASTADDR_MAX ) &&
            ( DestIpAddr_u32 >= RBA_ETHIPV4_MULTICASTADDR_MIN ) )
     {  /* Set return value to multicast */
        lRetAddrType_en = TCPIP_MULTICAST;
     }
     /* Check whether the destination IP is broadcast address */
     /* Check for direct broadcast shall be done only if destination Ip and source Ip are within the same subnet */
     /* If the DestIpAddr_u32 is a directed broadcast to the subnet to which the local host is not directly attached, */
     /* the frame shall be treated as Unicast and shall be forwarded to the default router. */
     else if( ( ( ( DestIpAddr_u32 & NetMask_u32 ) == ( SrcIpAddr_u32 & NetMask_u32 ) ) &&
                ( DestIpAddr_u32 == ( DestIpAddr_u32 | ( ~ NetMask_u32 ) ) ) ) ||
              ( TCPIP_IPADDR_BROADCAST == DestIpAddr_u32 ) ||
              ( TCPIP_AUTOIP_BROADCAST == DestIpAddr_u32 ) )
     {  /* Set return value to broadcast */
        lRetAddrType_en = TCPIP_BROADCAST;
     }
     else
     {  /* Set return value to unicast */
        lRetAddrType_en = TCPIP_UNICAST;
     }

    return ( lRetAddrType_en );
}


/********************************************************************************************************************/
/* rba_EthIPv4_GetIPMulticastDestEthAddr() - Return the multicast Ethernet address for multicast IPv4 destination . */
/*                  address.                                                                                        */
/*                  Upper half of destination Ethernet address for multicast IP address is 01:00:5E. The lower half */
/*                  comes from the lower 23 bits of the multicast destination IP address. The 24th bit of the       */
/*                  destination MAC address is always set to 0 for multicast IP address.                            */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  DestMultiCastIpAddr_u32 - Destination multicast IPv4 address                                                    */
/*                                                                                                                  */
/* Output Parameters :                                                                                              */
/*  DestEthAddr_au8         - Destination multicast Ethernet/MAC address                                            */
/*                                                                                                                  */
/* Return                                                                                                           */
/*                      void                                                                                        */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, RBA_ETHIPV4_CODE )  rba_EthIPv4_GetIPMulticastDestEthAddr(
                                                       VAR( uint32, AUTOMATIC )                 DestMultiCastIpAddr_u32,
                                                       P2VAR( uint8, AUTOMATIC, AUTOMATIC )     DestEthAddr_pau8 )
{
    /* First half of destination Ethernet address for multicast IP address is 01:00:5E. The second half comes from  */
    /* the lower 23 bits of the multicast destination IP address. The 24th bit of the destination MAC address is    */
    /* always set to 0 for multicast IP address. */

    /* Check for DET errors */
    /* Report DET if rba_EthIPv4 module is uninitialised */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == rba_EthIPv4_CtrlCfg_pcpcst ), RBA_ETHIPV4_E_GET_IPMULTICAST_DESTETHADDR_API_ID,   \
                                           RBA_ETHIPV4_E_NOTINIT )

    /* Report DET if DestEthAddr_pau8 is a Null pointer */
    RBA_ETHIPV4_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == DestEthAddr_pau8 ), RBA_ETHIPV4_E_GET_IPMULTICAST_DESTETHADDR_API_ID,         \
                                           RBA_ETHIPV4_E_NULL_PTR )

    /* Upper 3 bytes of destination multicast Ethernet address for multicast IP address is 01:00:5E. */
    DestEthAddr_pau8[0] =  0x01U;
    DestEthAddr_pau8[1] =  0x00U;
    DestEthAddr_pau8[2] =  0x5EU;

    /* Third lowest byte (lower 7 bits only) of the destination multicast IP address, is the third byte */
    /*  (lower 7 bits only) of destination MAC address */
    DestEthAddr_pau8[3] = ( uint8 )( ( DestMultiCastIpAddr_u32 & 0x007F0000UL ) >> 16U );

    /* Second lowest byte of the destination multicast IP address, is the second byte of destination MAC address */
    DestEthAddr_pau8[4] = ( uint8 )( ( DestMultiCastIpAddr_u32 & 0x0000FF00UL ) >>  8U );

    /* Lowest byte of the destination multicast IP address, is the first byte of destination MAC address */
    DestEthAddr_pau8[5] = ( uint8 )(   DestMultiCastIpAddr_u32 & 0x000000FFUL );
    return;
}


#define RBA_ETHIPV4_STOP_SEC_CODE
#include "rba_EthIPv4_MemMap.h"

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */
