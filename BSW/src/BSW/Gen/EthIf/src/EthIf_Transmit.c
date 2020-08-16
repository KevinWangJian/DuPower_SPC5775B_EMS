
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"
#include "EthIf_Prv.h"

/*****************************************************************************************************/
/* \module description                                                                              */
/* ETHIF067: Provides access to a transmit buffer of the specified Ethernet controller
 * \par Service ID 0x09, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx       Index of the Ethernet controller within the context of the Ethernet Interface
 * \param FrameType     Ethernet Frame Type (EtherType)
 * \param Priority      Priority value which shall be used for the 3-bit PCP field of the VLAN tag
 *
 * Parameter InOut:
 * \param LenBytePtr    in: desired length in bytes, out: granted length in bytes
 *                          EthIf expects pointer to buffer where the eth_header can be directly written to
 *
 * Parameter Out:
 * \param BufIdxPtr     Index to the granted buffer resource. To be used for subsequent requests
 * \param BufPtr        Pointer to the granted buffer
 *
 * \return  BufReq_ReturnType {BUFREQ_OK: success; BUFREQ_E_NOT_OK: development error detected; BUFREQ_E_BUSY: all buffers in use}
 *
 ***************************************************************************************************
 */
#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

FUNC(BufReq_ReturnType, RBA_ETHIF_CODE) EthIf_ProvideTxBuffer(  VAR( uint8,         AUTOMATIC )                                     CtrlIdx,
                                                                VAR( Eth_FrameType, AUTOMATIC )                                     FrameType,
                                                                VAR( uint8,         AUTOMATIC )                                     Priority,
                                                                P2VAR( uint8,       AUTOMATIC, AUTOMATIC )                          BufIdxPtr,
                                                                P2VAR(P2VAR(uint8,  AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC)    BufPtr,
                                                                P2VAR( uint16,      AUTOMATIC, AUTOMATIC )                          LenBytePtr )
{
    uint16                          lVlanId_u16;
    uint8                           lEthCtrlIdx_u8;
    BufReq_ReturnType               lRetValBufReqType_en;

    /* Initialise local variables */
    lRetValBufReqType_en    = BUFREQ_E_NOT_OK;
    lVlanId_u16             = 0xffff;
    lEthCtrlIdx_u8          = 0xFF;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_PROVIDETXBUFFER,
                                     ETHIF_E_NOT_INITIALIZED, BUFREQ_E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( (  CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),      \
                                       ETHIF_SID_ETHIF_PROVIDETXBUFFER,                                                \
                                       ETHIF_E_INV_CTRL_IDX, BUFREQ_E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == BufIdxPtr ), ETHIF_SID_ETHIF_PROVIDETXBUFFER, ETHIF_E_PARAM_POINTER, BUFREQ_E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == BufPtr ), ETHIF_SID_ETHIF_PROVIDETXBUFFER, ETHIF_E_PARAM_POINTER, BUFREQ_E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == LenBytePtr ), ETHIF_SID_ETHIF_PROVIDETXBUFFER, ETHIF_E_PARAM_POINTER, BUFREQ_E_NOT_OK )

    /* Report DET : Development Error: Frame priority parameter (Priority) is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( Priority > ETHIF_FRAMEPRIO_MAXVAL ), ETHIF_SID_ETHIF_PROVIDETXBUFFER, ETHIF_E_INV_PARAM, BUFREQ_E_NOT_OK )

    if( ETH_MODE_DOWN != EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] )  /* Check whether  EthIfCtrl state is ETH_MODE_ACTIVE                    */
    {
       /* If buffer length requested is greater than MTU, set buffer length to MTU configured and return with BUFREQ_E_OVFL */
        if( ( *LenBytePtr ) > ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].MtuSize_cu16 ) )
        {
            ( *LenBytePtr )      = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].MtuSize_cu16 );
            lRetValBufReqType_en = BUFREQ_E_OVFL;
        }

        /* If requested EthIfCtrl is Vlan configured, increase the buffer length by 4 */
        if( 0xffffU != ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16 ) )
        {
            ( *LenBytePtr ) = ( ( *LenBytePtr ) + ETHIF_VLANTAG_LENGTH );
        }

        if(BUFREQ_E_OVFL != lRetValBufReqType_en)
        {
            /* Get EthCtrlIdx mapped to requested EthIfCtrl */
             lEthCtrlIdx_u8 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

            /* Request buffer from Eth-driver */
            lRetValBufReqType_en = Eth_ProvideTxBuffer(  lEthCtrlIdx_u8,
                                                         BufIdxPtr,
                                                         BufPtr,
                                                         LenBytePtr );
        }
    }

    if( BUFREQ_OK == lRetValBufReqType_en )     /* EthDrv provided requested buffer length  */
    {
        /* Check if Vlan is configured for the requested EthIfCtrl */
        if( 0xffffU != ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16 ) )
        {
            /* Read out VLANid from the configuration */
            lVlanId_u16 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16 );

            /* Write PCP (Priority) to header --> upper 3 bits in ETHIF_VLANTAG_BYTE1 */
            ( *( ( *BufPtr ) + ETHIF_VLANTAG_BYTE1 ) ) = ( Priority << 5U );

            /* write VLANid into header */
            /* Don't overwrite upper 4 bits in ETHIF_VLANTAG_BYTE1 because they are PCP(priority of the VLAN frame) and CFI */
            ( *( ( *BufPtr ) + ETHIF_VLANTAG_BYTE1 ) ) = ( * ( ( * BufPtr ) + ETHIF_VLANTAG_BYTE1 ) ) | ( (uint8)( lVlanId_u16 >> 8U ) );
            ( *( ( *BufPtr ) + ETHIF_VLANTAG_BYTE2 ) ) = ( (uint8)( lVlanId_u16 & 0x00FFU ) );

            /* write EthType */
            ( *( ( *BufPtr ) + ETHIF_ETHTYPE_IN_VLAN_BYTE1 ) ) = ( (uint8)( FrameType >> 8U ) );
            ( *( ( *BufPtr ) + ETHIF_ETHTYPE_IN_VLAN_BYTE2 ) ) = ( (uint8)( FrameType & 0x00FFU ) );

            /* Shift pointer to the beginning of IP payload */
            ( *BufPtr)     = ( ( *BufPtr ) + ETHIF_VLANTAG_LENGTH );

            /* Update length byte pointer with the buffer length requested by upper layer */
            ( *LenBytePtr )= ( ( *LenBytePtr ) - ETHIF_VLANTAG_LENGTH );

        }

        /* If buffer length to be provided to upper layer is greater than MTU, set it to MTU configured */
        if( (*LenBytePtr) > ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].MtuSize_cu16 ) )
        {
            /* Update the buffer length to MTU + EthIf header length */
            (*LenBytePtr) = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].MtuSize_cu16 );
        }
    }
    else if( (BUFREQ_E_OVFL == lRetValBufReqType_en) &&                                    /* If Eth_ProvideTxBuffer() returned BUFREQ_E_OVFL and */
        (0xffffU != EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16) )    /* requested EthIfCtrl is Vlan configured              */
    {
        if( (*LenBytePtr) > ETHIF_VLANTAG_LENGTH )                                         /* Check whether the buffer length which EthDrv can provide is */
        {                                                                                  /* at least a byte more than the required for Vlan header       */
            (*LenBytePtr) = (*LenBytePtr) - ETHIF_VLANTAG_LENGTH;
        }
        else
        {
            (*LenBytePtr) = 0;
        }
    }
    else
    {
        /* Do Nothing */
    }

    return lRetValBufReqType_en;
}


/**
 ***************************************************************************************************
 * \module description
 * ETHIF075: Triggers transmission of a previously filled transmit buffer
 * \par Service ID 0x0a, Synchronous, Non Reentrant
 *
 * Parameter In:
 * \param CtrlIdx           Index of the Ethernet controller within the context of the Ethernet Interface
 * \param FrameType         Ethernet frame type
 * \param TxConfirmation    Activates transmission confirmation
 * \param PhysAddrPtr       Physical target address (MAC address) in network byte order
 *
 * Parameter InOut:
 * \param LenByte           Data length in byte
 *
 * Parameter Out:
 * \param BufIdx            Index of the buffer resource
 *
 * \return  Std_ReturnType {E_OK: success;E_NOT_OK: transmission failed}
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Transmit(    VAR( uint8,         AUTOMATIC )             CtrlIdx,
                                                        VAR( uint8,         AUTOMATIC )             BufIdx,
                                                        VAR( Eth_FrameType, AUTOMATIC )             FrameType,
                                                        VAR( boolean,       AUTOMATIC )             TxConfirmation,
                                                        VAR( uint16,        AUTOMATIC )             LenByte,
                                                        P2VAR( uint8,       AUTOMATIC, AUTOMATIC )  PhysAddrPtr )
{
    Std_ReturnType          lRetValStdType_en;
    Eth_FrameType           lFrameType_u16;
    uint8                   lEthCtrlIdx_u8;
    boolean                 lBufReleaseRequested_b;

    /* Initialise local variables */
    lRetValStdType_en   = E_NOT_OK;
    lEthCtrlIdx_u8      = 0xFF;
    lFrameType_u16      = FrameType;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_TRANSMIT,            \
    		                        ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),      \
                                      ETHIF_SID_ETHIF_TRANSMIT,                                                       \
                                      ETHIF_E_INV_CTRL_IDX, E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( NULL_PTR == PhysAddrPtr), ETHIF_SID_ETHIF_TRANSMIT, ETHIF_E_PARAM_POINTER, E_NOT_OK )

    /* Data length 0 indicates upper layer is trying to release the buffer */
    lBufReleaseRequested_b = (boolean)( ( 0 == LenByte ) ? TRUE: FALSE );

    if(  FALSE == lBufReleaseRequested_b )
    {
        if( ( ETH_MODE_ACTIVE == EthIf_CfgPtr_pco->EthIfCtrlState_pst->EthIfCtrlMode_pa[CtrlIdx] ) &&  /* Check whether  EthIfCtrl state is ETH_MODE_ACTIVE                     */
            ( LenByte <= ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].MtuSize_cu16 ) ) )     /* Check whether the data length is within the configured MTU            */
        {
            /* If VALN is configured for the requested EthIf controller increase the data length by 4 bytes */
            if( 0xffffU != ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].VlanId_cu16 ) )
            {
                LenByte = LenByte + ETHIF_VLANTAG_LENGTH ;
                lFrameType_u16 = ETHIF_FRAMETYP_VLAN;
            }
        }
        else
        {   /* If frame type is invalid or if data length greater than MTU or if controller state is not ETH_MODE_ACTIVE, release the buffer */
            lRetValStdType_en = E_NOT_OK;
            LenByte = 0;
        }
    }

    /* Get EthCtrlIdx configured to the requested EthIfCtrl */
    lEthCtrlIdx_u8 = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    lRetValStdType_en = Eth_Transmit( lEthCtrlIdx_u8,
                                       BufIdx,
                                       lFrameType_u16,
                                       TxConfirmation,
                                       LenByte,
                                       PhysAddrPtr );

    /* If upper layer didn't request for releasing buffer and if EthIf is releasing buffer */
    /* (Because of not meeting required condition for Tx), E_NOT_OK shall be returned to the upper layer */
    lRetValStdType_en = (Std_ReturnType)( ( (FALSE == lBufReleaseRequested_b) && (0 == LenByte) ) ? E_NOT_OK : lRetValStdType_en);

    return lRetValStdType_en;
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"
#endif /* ETHIF_CONFIGURED */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
