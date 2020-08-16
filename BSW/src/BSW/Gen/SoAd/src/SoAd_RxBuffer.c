

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#include "rba_BswSrv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

#ifdef SOAD_DEBUG_AND_TEST
#include "TestSoAdApplication.h"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
static FUNC( void, SOAD_CODE )  SoAd_ExecuteTpProcessingAfterCopy       ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo,
                                                                          VAR( uint16, AUTOMATIC )                  CopiedLengthToUl_u16 );

static FUNC( void, SOAD_CODE )  SoAd_DispatchNextTpPduFromRxBuffer      ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo,
                                                                          VAR( boolean, AUTOMATIC )                 TerminationRequested_b );

static FUNC( void, SOAD_CODE )  SoAd_DiscardActualTpPduFromRxBuffer     ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo,
                                                                          VAR( uint32, AUTOMATIC )                  RemainingLenToTransfer_u32 );

static FUNC( void, SOAD_CODE )  SoAd_ReorganiseRxBuffer                 ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo );
#endif

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"


/*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

/*********************************************************************************************************************************/
/** SoAd_ResetRxBuffer()    - This function reset all the fields of the SoAd Rx buffer                                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( void, SOAD_CODE ) SoAd_ResetRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* --------------------------------------------- */
    /* Reset all fields                              */
    /* --------------------------------------------- */

    /* Buffer pointer */
    lSoAdDynRxBuff_pst->RxNxtFree_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
    lSoAdDynRxBuff_pst->RxNxtData_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);

    /* Rx Pdu desc */
    lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.PduDataLength_u32 = 0U;
    lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.RxPduId_uo = 0U;
#if (SOAD_TP_PRESENT != STD_OFF)
    lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = 0U;
#endif

    /* Current size */
    lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 = 0U;
#if (SOAD_TP_PRESENT != STD_OFF)
    lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 = 0U;
#endif
    lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 = 0U;

    /* Flags */
    lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b = FALSE;
    lSoAdDynRxBuff_pst->HeaderFragReceptionInProgress_b = FALSE;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_GetRxBufLnrFreeLen()   - Get the linear free length in the SoAd Rx buffer                                              **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - uint16                                                                                        **/
/**                                 Linear free length available at end of bufferr                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( uint16, SOAD_CODE ) SoAd_GetRxBufLnrFreeLen( VAR( SoAd_SoConIdType, AUTOMATIC ) StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)          lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                        lLnrFreeLen_u16;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* If Rx buffer is configured */
    if( lSoAdDynRxBuff_pst != NULL_PTR )
    {
        /* Compute the linear free length */
        lLnrFreeLen_u16 = ( lSoAdDynRxBuff_pst->TotalRxBuffSize_cu16 - (uint16)(lSoAdDynRxBuff_pst->RxNxtFree_pu8 - lSoAdDynRxBuff_pst->RxBuffStrt_cpu8) );
    }

    /* If Rx buffer is not configured */
    else
    {
        lLnrFreeLen_u16 = 0U;
    }

    return lLnrFreeLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_AddFragmentedHeaderInRxBuffer()    - This function add a fragment of Pdu header in the SoAd Rx buffer                  **/
/**                                         This function is for HEADER ENABLED only                                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** SrcPtr_cpu8                             - Pointer to the source pointer containing the Pdu header fragment                  **/
/** SrcLen_u16                              - Total length of bytes present in source buffer                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedLength_pu8                        - Copied length in the SoAd rx buffer                                               **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: Fragment has been saved in buffer                                         **/
/**                                             E_NOT_OK: Fragment cannot be been saved in buffer                               **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_AddFragmentedHeaderInRxBuffer(   VAR( SoAd_SoConIdType, AUTOMATIC )          StaticSocketId_uo,
                                                                        P2CONST( uint8, AUTOMATIC, AUTOMATIC )      SrcPtr_cpu8,
                                                                        VAR( uint16, AUTOMATIC )                    SrcLen_u16,
                                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        CopiedLength_pu8 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                    lLinearFreeLen_u16;
    VAR( uint8, AUTOMATIC )                                     lLengthToCopy_u8;
    VAR( Std_ReturnType, AUTOMATIC )                            lFunctionRetVal_en;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* If there is no data fragmentation in progress */
    /* (it is not possible to store fragment of header if there is already data fragmentation) */
    if( lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b == FALSE )
    {
        /* ---------------------------- */
        /* Compute length to copy       */
        /* ---------------------------- */
        if( (uint8)(SrcLen_u16) > (SOAD_PDUHDR_SIZE - lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8) )
        {
            lLengthToCopy_u8 = ( SOAD_PDUHDR_SIZE - lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 );
        }
        else
        {
            lLengthToCopy_u8 = (uint8)( SrcLen_u16 );
        }

        /* ---------------------------- */
        /* Check space                  */
        /* ---------------------------- */

        /* Get linear free length */
        lLinearFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );

        /* Check if there is enough space and the total length of the fragmented header in buffer is not greater than the Pdu header length */
        if( lLinearFreeLen_u16 >= (uint16)(lLengthToCopy_u8) )
        {
            /* ---------------------------- */
            /* Copy header in the Rx Buffer */
            /* ---------------------------- */

            /* Copy the fragment of header */
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( lSoAdDynRxBuff_pst->RxNxtFree_pu8, SrcPtr_cpu8, lLengthToCopy_u8 );

            /* Move the NxtFree pointer by the length given in argument of the function */
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 += lLengthToCopy_u8;

            /* Increment the size of the fragmented header size stored in the Rx Buffer */
            lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 += lLengthToCopy_u8;

            /* Set the out argument of the function */
            *CopiedLength_pu8 = lLengthToCopy_u8;

            /* ----------------------------- */
            /* Update frag in progress       */
            /* ----------------------------- */

            /* If header is not complete */
            if( lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 < SOAD_PDUHDR_SIZE )
            {
                /* Fragmented header is in progress as a fragment has been added in the SoAd Rx buffer and header is not complete yet */
                lSoAdDynRxBuff_pst->HeaderFragReceptionInProgress_b = TRUE;
            }
            else
            {
                /* Fragmented header is no more in progress */
                /* (complete header is now received) */
                lSoAdDynRxBuff_pst->HeaderFragReceptionInProgress_b = FALSE;
            }

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }

        /* No space available */
        else
        {
            /* Report DET error as per [SWS_SoAd_00693]*/
            SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_GetFragmentedHeaderFromRxBuffer()      - Extract pointer to the Pdu header stored in the SoAd buffer                   **/
/**                                             This function is for HEADER ENABLED only                                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                           - SoAd static socket index                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                         None                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** PduHeaderPointer_ppu8                       - Pointer to linear memory location containing the assembled Pdu header         **/
/**                                                                                                                             **/
/** Return value:                               None                                                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( void, SOAD_CODE ) SoAd_GetFragmentedHeaderFromRxBuffer(   VAR( SoAd_SoConIdType, AUTOMATIC )      StaticSocketId_uo,
                                                                P2VAR( uint8*, AUTOMATIC, AUTOMATIC )   PduHeaderPointer_ppu8 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;
    P2VAR(uint8, SOAD_VAR, SOAD_VAR)                            lHeaderPointer_pu8;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Compute pointer */
    lHeaderPointer_pu8 = ( lSoAdDynRxBuff_pst->RxNxtFree_pu8 - lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 );

    /* Set in out argument */
    *PduHeaderPointer_ppu8 = lHeaderPointer_pu8;

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ClearFragmentedHeaderFromRxBuffer() - Clear the fragments of Pdu header stored in the SoAd buffer                      **/
/**                                          This function is for HEADER ENABLED only                                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                        - SoAd static socket index                                                         **/
/**                                                                                                                             **/
/** Parameters (inout):                      None                                                                               **/
/**                                                                                                                             **/
/** Parameters (out):                        None                                                                               **/
/**                                                                                                                             **/
/** Return value:                            None                                                                               **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( void, SOAD_CODE ) SoAd_ClearFragmentedHeaderFromRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC ) StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* If there is header fragments present in the buffer */
    /* (length shall be checked because it is possible to have header fragmentation in progress to FALSE with some fragments in the buffer in case all the fragments have been received) */
    if( lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 > 0U )
    {
        /* -------------------------------------- */
        /* Clear header fragments from Rx buffer  */
        /* -------------------------------------- */

        /* Move back the TxWndNxtFree pointer */
        lSoAdDynRxBuff_pst->RxNxtFree_pu8 -= lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8;

        /* Reset the fragmented header size to 0 */
        lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 = 0U;

        /* Fragmented header no more in progress */
        lSoAdDynRxBuff_pst->HeaderFragReceptionInProgress_b = FALSE;
    }

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_StartFragmentedDataInRxBuffer()    - Start the reception of fragmented Pdu data                                        **/
/**                                         This function is for HEADER ENABLED only                                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** RxPduDesc_cpst                          - Pointer to the Rx Pdu description of the Pdu which is fragmented                  **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** HeaderSavedInBuff_pb                    - Flag indicating if SoAd header has been saved in buffer or not                   **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: Fragmented data reception is started successfully                         **/
/**                                             E_NOT_OK: Fragmented data reception cannot be successfully                      **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_StartFragmentedDataInRxBuffer(   VAR( SoAd_SoConIdType, AUTOMATIC )                   StaticSocketId_uo,
                                                                        P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC )  RxPduDesc_cpst,
                                                                        P2VAR( boolean, AUTOMATIC, AUTOMATIC )               HeaderSavedInBuff_pb )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                    lLinearFreeLen_u16;
    VAR( Std_ReturnType, AUTOMATIC )                            lFunctionRetVal_en;
    VAR( boolean, AUTOMATIC )                                   lErrorFlag_b;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Set the error flag to false */
    lErrorFlag_b = FALSE;

    /* Initialize the header saved in buff flag to FALSE in out argument of the function */
    (*HeaderSavedInBuff_pb) = FALSE;

    /* If there is no fragmentation in progress */
    if( (lSoAdDynRxBuff_pst->HeaderFragReceptionInProgress_b == FALSE) &&
        (lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b == FALSE) )
    {
#if (SOAD_TP_PRESENT != STD_OFF)
        /* --------------------------------- */
        /* Copy header for fragmented TP Pdu */
        /* --------------------------------- */

        /* If we start a fragmented TP Pdu in Rx buffer and there is already a TP transfer from Rx buffer to UL */
        /* (In that case, it is needed to saved The Pdu header in SoAd Rx buffer) */
        /* (The Pdu cannot be processed for the moment because there is already a TP data in progress from Rx buffer to UL) */
        if( (SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_cpst->RxPduId_uo].rxUpperLayerType_en == SOAD_TP)   &&
            (lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > 0U) )
        {
            /* ---------------------------- */
            /* Check space                  */
            /* ---------------------------- */

            /* Get linear free length */
            lLinearFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );

            /* Check if there is enough space and the total length of the fragmented header in buffer is not greater than the Pdu header length */
            if( lLinearFreeLen_u16 >= SOAD_PDUHDR_SIZE )
            {
                /* ---------------------------- */
                /* Copy Pdu header              */
                /* ---------------------------- */

                /* Copy header in buffer */
                /* (header must be copied in SoAd Rx buffer when a TP Pdu is already present in the buffer and we receive a new fragmented TP Pdu) */
                SoAd_InsertPduHdrToBuffer(  SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_cpst->RxPduId_uo].rxPduHeaderId_u32,
                                            RxPduDesc_cpst->PduDataLength_u32,
                                            lSoAdDynRxBuff_pst->RxNxtFree_pu8 );

                /* Move the NxtFree pointer by the length given in argument of the function */
                lSoAdDynRxBuff_pst->RxNxtFree_pu8 += SOAD_PDUHDR_SIZE;

                /* Increment the size of TP data size stored in the Rx Buffer */
                lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 += SOAD_PDUHDR_SIZE;

                /* Initialize the header saved in buff flag to TRUE in out argument of the function */
                (*HeaderSavedInBuff_pb) = TRUE;
            }

            /* No space available */
            else
            {
                /* Report DET error as per [SWS_SoAd_00693]*/
                SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
                lErrorFlag_b = TRUE;
            }
        }
#endif

        /* If no error occured */
        if( lErrorFlag_b == FALSE )
        {
            /* ---------------------------- */
            /* Save current Pdu desc        */
            /* ---------------------------- */
            lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.PduDataLength_u32 = RxPduDesc_cpst->PduDataLength_u32;
            lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.RxPduId_uo = RxPduDesc_cpst->RxPduId_uo;

            /* Fragmented data is now in progress */
            lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b = TRUE;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_AddFragmentedDataInRxBuffer()      - This function add a fragment of Pdu data in the SoAd Rx buffer                    **/
/**                                         This function is for HEADER ENABLED only                                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** SrcPtr_cpu8                             - Pointer to the source pointer containing the Pdu data fragment                    **/
/** SrcLen_u16                              - Total length of bytes present in source buffer                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: Fragment has been saved in buffer                                         **/
/**                                             E_NOT_OK: Fragment cannot be been saved in buffer                               **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_AddFragmentedDataInRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )          StaticSocketId_uo,
                                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )      SrcPtr_cpu8,
                                                                    VAR( uint16, AUTOMATIC )                    SrcLen_u16 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)              lSoAdDynRxBuff_pst;
    VAR( uint32, AUTOMATIC )                                            lRemainingPduDataLen_u32;
    VAR( uint16, AUTOMATIC )                                            lLinearFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLengthToCopy_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* If fragmented Pdu data reception is in progress */
    if( lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b == TRUE )
    {
        /* ------------------------------------------ */
        /* Compute remaining length of fragmented Pdu */
        /* ------------------------------------------ */

        /* Compute already received Pdu data length for the currently fragmented Pdu */
#if (SOAD_TP_PRESENT != STD_OFF)
        /* If the fragmented data are along with a current TP transfer from Rx buffer to UL */
        if( (lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16)) )
        {
            lRemainingPduDataLen_u32 = ( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 - (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16) );
        }
        else
#endif
        {
            lRemainingPduDataLen_u32 = ( lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.PduDataLength_u32 - lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 );
        }


        /* ---------------------------- */
        /* Compute length to copy       */
        /* ---------------------------- */
        if( (uint32)(SrcLen_u16) > lRemainingPduDataLen_u32 )
        {
            lLengthToCopy_u16 = (uint16)( lRemainingPduDataLen_u32 );
        }
        else
        {
            lLengthToCopy_u16 = SrcLen_u16;
        }


        /* ---------------------------- */
        /* Check space                  */
        /* ---------------------------- */

        /* Get linear free length */
        lLinearFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );

        /* Check if there is enough space and the total length of the fragmented header in buffer is not greater than the Pdu header length */
        if( lLinearFreeLen_u16 >= lLengthToCopy_u16 )
        {
            /* ----------------------------- */
            /* Copy data in the Rx Buffer    */
            /* ----------------------------- */

            /* Copy the fragment of data */
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( lSoAdDynRxBuff_pst->RxNxtFree_pu8, SrcPtr_cpu8, lLengthToCopy_u16 );

            /* Move the NxtFree pointer by the length of data */
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 += lLengthToCopy_u16;

            /* Increment the size of the fragmented data size stored in the Rx Buffer */
            lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 += lLengthToCopy_u16;

            /* Decrement the remaining length of the fragmented Pdu data */
            lRemainingPduDataLen_u32 -= lLengthToCopy_u16;


            /* ----------------------------- */
            /* Check for frag completion     */
            /* ----------------------------- */

            /* If Pdu data is now complete (means fragmentation is finished) */
            if( lRemainingPduDataLen_u32 == 0U )
            {
#if ( SOAD_TP_PRESENT != STD_OFF )
                /* If the fragmented data are for a TP Pdu */
                if( SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[ lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.RxPduId_uo].rxUpperLayerType_en == SOAD_TP )
                {
                    /* The completed fragmented data as now part of the Tp data in Rx buffer */
					/* (this transfer from fragmented data to TP data in the Rx buffer can be done only when the fragmentation is completed in order to be able to handle a call of ClearFragmentedDataFromRxBuffer in case of a fragmented extra TP Pdu. We should remember the size of fragmented data already received in order to do the fragments clearing for that use case.) */
                    lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 += lSoAdDynRxBuff_pst->DataFragCurrentSize_u16;
                    lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 = 0U;
                }
#endif

                /* Fragmented data is no more in progress */
                lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b = FALSE;
            }

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }

        /* No space available */
        else
        {
            /* Report DET error as per [SWS_SoAd_00693]*/
            SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_GetFragmentedDataFromRxBuffer()        - Get pointer to the Pdu data stored in the SoAd buffer                         **/
/**                                             This function is for HEADER ENABLED only                                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                           - SoAd static socket index                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                         None                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** PduHeaderPointer_ppu8                       - Pointer to linear memory location containing the assembled Pdu data           **/
/**                                                                                                                             **/
/** Return value:                               None                                                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( void, SOAD_CODE ) SoAd_GetFragmentedDataFromRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )      StaticSocketId_uo,
                                                            P2VAR( uint8*, AUTOMATIC, AUTOMATIC )   PduDataPointer_ppu8 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;
    P2VAR(uint8, SOAD_VAR, SOAD_VAR)                            lDataPointer_pu8;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Compute pointer */
    lDataPointer_pu8 = ( lSoAdDynRxBuff_pst->RxNxtFree_pu8 - lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 );

    /* Set in out argument */
    *PduDataPointer_ppu8 = lDataPointer_pu8;

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ClearFragmentedDataFromRxBuffer()  - Clear the fragments of Pdu data stored in the SoAd Rx buffer                      **/
/**                                          This function is for HEADER ENABLED only                                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):                      None                                                                               **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** RemainingPduDataLength_pu32             - Remaining Pdu data length that have not been processed / cleared yet              **/
/**                                                                                                                             **/
/** Return value:                           - uint16                                                                            **/
/**                                             Length of Pdu data cleared from buffer                                          **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
FUNC( uint16, SOAD_CODE ) SoAd_ClearFragmentedDataFromRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )      StaticSocketId_uo,
                                                                P2VAR( uint32, AUTOMATIC, AUTOMATIC )   RemainingPduDataLength_pu32 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)      lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                    lClearLen_u16;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Set clear length to 0 */
    lClearLen_u16 = 0U;

    /* If there is data fragmentation in progress or there is fragments present in the buffer */
    /* (it is possible to have data fragmentation in progress with no fragment in the buffer when only header has been received for the moment) */
    /* (it is possible to have data fragmentation in progress to FALSE with some fragments in the buffer in case all the fragments have been received) */
    if( (lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b == TRUE) || (lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 > 0U) )
    {
        /* --------------------------------------- */
        /* Clear Pdu data fragments from Rx buffer */
        /* --------------------------------------- */

        /* Increment clear length */
        lClearLen_u16 = (lSoAdDynRxBuff_pst->DataFragCurrentSize_u16);

        /* Set the remaining Pdu data length in out argument */
        (*RemainingPduDataLength_pu32) = ( lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.PduDataLength_u32 - (uint32)(lClearLen_u16) );

        /* Move back the TxWndNxtFree pointer */
        lSoAdDynRxBuff_pst->RxNxtFree_pu8 -= lSoAdDynRxBuff_pst->DataFragCurrentSize_u16;

        /* Reset the fragmented header size to 0 */
        lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 = 0U;

        /* Fragmented Pdu data no more in progress */
        lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b = FALSE;

#if ( SOAD_TP_PRESENT != STD_OFF )
        /* ------------------------------------ */
        /* Check for TP data clearing           */
        /* ------------------------------------ */

        /* If the cleared fragmented data are for a TP Pdu */
        if( (SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[ lSoAdDynRxBuff_pst->DataFragCurrentRxPduDesc_st.RxPduId_uo].rxUpperLayerType_en == SOAD_TP) )
        {
            /* ------------------------------------ */
            /* Fragments are with current TP Pdu    */
            /* ------------------------------------ */

            /* If the fragmented data are along with a current TP transfer from Rx buffer to UL */
            /* (It is also needed to clear the current TP reception) */
            if( (lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16) ) )
            {
                /* Increment clear length */
                lClearLen_u16 += lSoAdDynRxBuff_pst->TpDataCurrentSize_u16;

                /* Set the remaining Pdu data length in out argument */
                (*RemainingPduDataLength_pu32) = ( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 - (uint32)(lClearLen_u16) );

                /* Reset the SoAd Rx buffer to default state (no more data are present in the buffer because we remove the only one TP Pdu from Rx buffer) */
                lSoAdDynRxBuff_pst->RxNxtFree_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
                lSoAdDynRxBuff_pst->RxNxtData_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
                lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 = 0U;
                lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = 0U;
            }

            /* ------------------------------------ */
            /* Fragments are with extra TP Pdu      */
            /* ------------------------------------ */

            /* If the cleared fragmented data are along with an extra TP Pdu */
            /* (It is also needed to clear the header previously saved during the starting of fragmented data) */
            else
            {
                /* Increment clear length */
                lClearLen_u16 += SOAD_PDUHDR_SIZE;

                /* Move back the TxWndNxtFree pointer */
                lSoAdDynRxBuff_pst->RxNxtFree_pu8 -= SOAD_PDUHDR_SIZE;

                /* Reset the TP data current size */
                lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 -= SOAD_PDUHDR_SIZE;
            }
        }
#endif
    }

    return lClearLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_StartTpDataInRxBuffer()  - This function start Tp data reception in SoAd Rx buffer                                     **/
/**                             This function is for HEADER ENABLED or DISABLED                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** RxPduDesc_cpst               - Pointer to the Rx Pdu description of the Pdu which is received                                **/
/** ForwardedDataLenToUl_u16    - Already forwarded data length to UL                                                           **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               None                                                                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
FUNC( void, SOAD_CODE ) SoAd_StartTpDataInRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )                      StaticSocketId_uo,
                                                    P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC )     RxPduDesc_cpst,
                                                    VAR( uint16, AUTOMATIC )                                ForwardedDataLenToUl_u16 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)              lSoAdDynRxBuff_pst;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* If there is no TP transfer from Rx buffer to UL */
    if( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 == 0U )
    {
        /* ------------------------------------ */
        /* Save remaining length to transfer    */
        /* ------------------------------------ */

        /* Compute remaining length to trasfer based on the already copied length to UL */
        lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = ( RxPduDesc_cpst->PduDataLength_u32 - (uint32)(ForwardedDataLenToUl_u16) );
    }

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_AddTpDataInRxBuffer()  - This function add some TP data in the SoAd Rx buffer (when UL does not have space)            **/
/**                             This function is for HEADER ENABLED or DISABLED                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** SrcPtr_cpu8                 - Pointer to the source pointer containing the TP Pdu data                                      **/
/** SrcLen_u16                  - Total length of bytes present in source buffer                                                **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Std_ReturnType                                                                                **/
/**                                 E_OK: Data has been saved in buffer                                                         **/
/**                                 E_NOT_OK: Data cannot be been saved in buffer                                               **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_AddTpDataInRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )              StaticSocketId_uo,
                                                            P2CONST( uint8, AUTOMATIC, AUTOMATIC )          SrcPtr_cpu8,
                                                            VAR( uint16, AUTOMATIC )                        SrcLen_u16 )
{
    /* Declare local variables */
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)              lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                            lLinearFreeLen_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* If there is a TP transfer from Rx buffer to UL */
    if( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > 0U )
    {
        /* ---------------------------- */
        /* Check space                  */
        /* ---------------------------- */

        /* Get linear free length */
        lLinearFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );

        /* Check if there is enough space and the total length of the fragmented header in buffer is not greater than the Pdu header length */
        if( lLinearFreeLen_u16 >= SrcLen_u16 )
        {
            /* ---------------------------- */
            /* Copy data                    */
            /* ---------------------------- */

            /* Copy TP data */
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( lSoAdDynRxBuff_pst->RxNxtFree_pu8, SrcPtr_cpu8, SrcLen_u16 );

            /* Move the NxtFree pointer by the copied length */
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 += SrcLen_u16;

            /* Increment the size of the fragmented data size stored in the Rx Buffer */
            lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 += SrcLen_u16;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }

        /* No space available */
        else
        {
            /* Report DET error as per [SWS_SoAd_00693]*/
            SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_AddExtraTpDataInRxBuffer() - This function add extra TP data in the SoAd Rx buffer when there is already TP reception  **/
/**                             This function is for HEADER ENABLED or DISABLED                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** RxPduDesc_cpst               - Pointer to the Rx Pdu description of the Pdu which is received                                **/
/** SrcPtr_cpu8                 - Pointer to the source pointer containing the TP Pdu data                                      **/
/** SrcLen_u16                  - Total length of bytes present in source buffer                                                **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Std_ReturnType                                                                                **/
/**                                 E_OK: Data has been saved in buffer                                                         **/
/**                                 E_NOT_OK: Data cannot be been saved in buffer                                               **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_AddExtraTpDataInRxBuffer(    VAR( SoAd_SoConIdType, AUTOMATIC )                      StaticSocketId_uo,
                                                                    P2CONST( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC )     RxPduDesc_cpst,
                                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )                  SrcPtr_cpu8,
                                                                    VAR( uint16, AUTOMATIC )                                SrcLen_u16 )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR)              lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                            lLinearFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLengthToCopy_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* If there is already a TP transfer from Rx buffer to UL */
    /* (adding of extra Tp Pdu in the Rx buffer is possible only if there is already a Tp data in progress in the buffer) */
    if( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > 0U )
    {
        /* ---------------------------- */
        /* Compute length to copy       */
        /* ---------------------------- */

        /* If header is enabled */
        if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE )
        {
            /* Length to copy shall also contain the size for the header */
            /* (Pdu header will be saved in the buffer along to the Pdu data because already a Pdu data reception is in progress) */
            lLengthToCopy_u16 = ( SOAD_PDUHDR_SIZE + SrcLen_u16 );
        }
        else
        {
            /* Only data need to be copied */
            lLengthToCopy_u16 = SrcLen_u16;
        }


        /* ---------------------------- */
        /* Check space                  */
        /* ---------------------------- */

        /* Get linear free length */
        lLinearFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );

        /* Check if there is enough space and the total length of the fragmented header in buffer is not greater than the Pdu header length */
        if( lLinearFreeLen_u16 >= lLengthToCopy_u16 )
        {
            /* ---------------------------- */
            /* Copy in Rx buffer            */
            /* ---------------------------- */

            /* If header is enabled */
            if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE )
            {
                /* Copy header before */
                SoAd_InsertPduHdrToBuffer(  SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_cpst->RxPduId_uo].rxPduHeaderId_u32,
                                            RxPduDesc_cpst->PduDataLength_u32,
                                            lSoAdDynRxBuff_pst->RxNxtFree_pu8 );

                /* Move the NxtFree pointer by the copied header length */
                lSoAdDynRxBuff_pst->RxNxtFree_pu8 += SOAD_PDUHDR_SIZE;
            }

            /* Copy TP data */
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( lSoAdDynRxBuff_pst->RxNxtFree_pu8, SrcPtr_cpu8, SrcLen_u16 );

            /* Move the NxtFree pointer by the copied TP data length */
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 += SrcLen_u16;

            /* Increment the size of the fragmented data size stored in the Rx Buffer */
            lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 += lLengthToCopy_u16;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }

        /* No space available */
        else
        {
            /* Report DET error as per [SWS_SoAd_00693]*/
            SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_CopyTpDataFromRxBufferToUl()   - This function execute the cyclic processing that consist of giving data to UL         **/
/**                                     This function is for HEADER ENABLED or DISABLED                                         **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                   - SoAd static socket index                                                              **/
/** TerminationRequested_b              - Flag indicating if the TP reception session shall be terminated (due to socket close) **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                   None                                                                                    **/
/**                                                                                                                             **/
/** Return value:                       None                                                                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
FUNC( void, SOAD_CODE ) SoAd_CopyTpDataFromRxBufferToUl( VAR( SoAd_SoConIdType, AUTOMATIC )     StaticSocketId_uo,
                                                         VAR( boolean, AUTOMATIC )              TerminationRequested_b )
{
    /* Declare local variables */
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )       lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, AUTOMATIC, AUTOMATIC)             lSoAdDyncSocConfig_pst;
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;
    VAR( PduInfoType, AUTOMATIC )                                       lPduInfo_st;
    VAR( SoAd_SoConIdType, AUTOMATIC )                                  lIdxDynSocket_uo;
    VAR( uint16, AUTOMATIC )                                            lAvailablePduDataLength_u16;
    VAR( PduLengthType, AUTOMATIC )                                     lDataLenUpperLayer_uo;
    VAR( BufReq_ReturnType, AUTOMATIC )                                 lBufferRetVal_en;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic socket configuration pointers */
    lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* --------------------------------------------- */
    /* While Rx data are available                   */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00569] */
    /* In the SoAd_Mainfunction() the SoAd shall process as specified below if the SoAd receive buffer contains TP data for a socket connection with PDU Header mode disabled: */
    /* (1) Query the available amount of data at the upper layer by calling the configurable callback function <Up>_[SoAd][Tp]CopyRxData() with PduInfoType.SduLength = 0. */

    /* [SWS_SoAd_00574] */
    /* In the SoAd_Mainfunction() the SoAd shall process as specified below if a TP reception is in progress for a socket connection with PDU Header mode enabled: */
    /* (1) Query the available amount of data at the upper layer by calling the configurable callback function <Up>_[SoAd][Tp]CopyRxData() with PduInfoType.SduLength = 0. */

    /* 1. If Rx and Tx are allowed on the socket connection */
    /* 2. If there is TP transfer from Rx buffer to UL */
    /* 3. If Tp reception is ongoing for header enabled or there is Tp data in the buffer for header disabled (according to [SWS_SoAd_00569] and [SWS_SoAd_00574]) */
    while( (lSoAdDyncSocConfig_pst->discardNewTxRxReq_b == FALSE)                                       &&
           (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->TpDataRemainingLenToTransfer_u32 > 0U)  &&
           (((SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE) && (lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 > 0U)) ||
            ((SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE) && (lSoAdDyncSocConfig_pst->tpReceptionOngoing_b == TRUE))) )
    {
        /* --------------------------------------------- */
        /* Query UL buffer size                          */
        /* --------------------------------------------- */

        /* Initialization of data length available at Upper layer to 0 */
        lDataLenUpperLayer_uo = 0;

        /* To get the available length from UL, call the CopyRxData function with SduLength set to 0 and SduDataPtr set to NULL */
        lPduInfo_st.SduDataPtr = NULL_PTR;
        lPduInfo_st.SduLength  = 0;

        /* RxCallback function to the Upper layer to get the available length */
        lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn ( \
                                    SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo, \
                                    (const PduInfoType*)&lPduInfo_st, \
                                    &lDataLenUpperLayer_uo );

        /* In case of success */
        if( lBufferRetVal_en == BUFREQ_OK )
        {
            /* Compute available Pdu data length that can be copied to UL */
            /* (according to available bytes in Rx buffer, fragmented data length is also counted because it is also possible to transfer fragments of a TP reception to UL) */
            lAvailablePduDataLength_u16 = ( (lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 <= (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16))? (uint16)(lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32) : (lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16) );

            /* --------------------------------------------- */
            /* Copy data to UL                               */
            /* --------------------------------------------- */

			/* [SWS_SoAd_00569] */
			/* In the SoAd_MainFunction() the SoAd shall process as specified below if the SoAd receive buffer contains TP data for a socket connection with PDU Header mode disabled: */
			/* (2) Copy all data belonging to this socket connection from the SoAd receive buffer which can be accepted by the upper layer module determined at (1) to the upper layer by calling <Up>_[SoAd][Tp]CopyRxData() */

			/* [SWS_SoAd_00574] */
			/* In the SoAd_Mainfunction() the SoAd shall process as specified below if a TP reception is in progress for a socket connection with PDU Header mode enabled: */
			/* (2) Copy all data belonging to this socket connection from the SoAd receive buffer which can be accepted by the upper layer module determined at (1) to the upper layer by calling <Up>_[SoAd][Tp]CopyRxData() */

            /* If there is available data in the SoAd Rx buffer and UL has space to accept some data */
            if( (lAvailablePduDataLength_u16 > 0U) && (lDataLenUpperLayer_uo > 0U) )
            {
                /* Initialize Pdu Info */
                lPduInfo_st.SduDataPtr = lSoAdDynRxBuff_pst->RxNxtData_pu8;
                lPduInfo_st.SduLength = (PduLengthType)( ((uint32)(lDataLenUpperLayer_uo) < (uint32)(lAvailablePduDataLength_u16))? (uint16)(lDataLenUpperLayer_uo) : (lAvailablePduDataLength_u16) );

                /* RxCallback function to the Upper layer to copy the data */
                lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn (
                                                SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo,
                                                &lPduInfo_st,
                                                &lDataLenUpperLayer_uo);

                /* If no error occured */
                if( lBufferRetVal_en == BUFREQ_OK )
                {
                    /* Execute processing after copy to Upper Layer */
                    SoAd_ExecuteTpProcessingAfterCopy(  StaticSocketId_uo,
                                                        (uint16)(lPduInfo_st.SduLength) );
                }
            }
            else
            {
                /* Break the copying of data from Rx buffer to UL */
                /* (we do not have data in Rx buffer for the moment or the UL does not have free space for the moment) */
                break;
            }
        }


        /* --------------------------------------------- */
        /* Handle error                                  */
        /* --------------------------------------------- */

        /* If header is disabled */
        if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE )
        {
            /* [SWS_SoAd_00570] */
            /* If <Up>_[SoAd][Tp]StartOfReception()or <Up>_[SoAd][Tp]CopyRxData() return with BUFREQ_E_NOT_OK for a socket connection with PDU Header mode disabled, SoAd shall */
            /* (a) disable further transmission or reception for this socket connection (i.e. new transmit requests shall be rejected with E_NOT_OK and received messages shall simply be discarded) and */
            /* (b) close the socket connection in the next SoAd_MainFunction(). */

            /* If we got BUFREQ_E_NOT_OK */
            if( lBufferRetVal_en == BUFREQ_E_NOT_OK )
            {
                /* Set the global variables to skip the further transmission and reception */
                /* (TP reception cannot continue and socket need to be close so stop to copying of the data to UL) */
                lSoAdDyncSocConfig_pst->discardNewTxRxReq_b = TRUE;

                /* As an error occurred, so request need to be taken to abort the socket connection */
                lSoAdDyncSocConfig_pst->socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD;
            }
        }

        /* If header is enabled */
        else
        {
            /* [SWS_SoAd_00573] */
            /* If <Up>_[SoAd][Tp]CopyRxData() does not return BUFREQ_OK for a socket connection with PDU Header mode enabled, */
            /* SoAd shall terminate the TP receive session, simply discard all data of the PDU and call <Up>_[SoAd][Tp]RxIndication() with E_NOT_OK */

            /* If we got someting different from BUFREQ_OK */
            if( lBufferRetVal_en != BUFREQ_OK )
            {
                /* Call the upper layer with notify reslut type E_NOT_OK */
                SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                                SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo,
                                                E_NOT_OK);

                /* Terminate the TP reception session */
                lSoAdDyncSocConfig_pst->tpReceptionOngoing_b = FALSE;
                lSoAdDyncSocConfig_pst->idxRxPduTable_uo = (PduIdType)0xFFFF;

                /* Discard actual Tp Pdu from SoAd Rx buffer */
                SoAd_DiscardActualTpPduFromRxBuffer( StaticSocketId_uo, lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 );
            }
        }


        /* --------------------------------------------- */
        /* Dispatch next Pdu                             */
        /* --------------------------------------------- */

        /* If we do not have Tp data to be transferred anymore, try to dispach */
        /* (the dispaching to the next Pdu shall be done only if we do not have TP transfer from Rx buffer to UL anymore) */
        if( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 == 0U )
        {
            /* call a function to dispacth to next Pdu */
            SoAd_DispatchNextTpPduFromRxBuffer( StaticSocketId_uo, TerminationRequested_b );
        }
    }

    /* --------------------------------------------- */
    /* Reorganize Rx buffer                          */
    /* --------------------------------------------- */

    /* Reorganise the Rx buffer to prevent hole at the beginning */
    SoAd_ReorganiseRxBuffer( StaticSocketId_uo );

    return;
}
#endif


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** SoAd_DispatchNextTpPduFromRxBuffer()    - This function execute the processing after some data have been copied to UL       **/
/**                                         This function is for HEADER ENABLED or DISABLED                                     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** CopiedLengthToUl_u16                    - Copied length to Upper Layer                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
static FUNC( void, SOAD_CODE ) SoAd_ExecuteTpProcessingAfterCopy(   VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,
                                                                    VAR( uint16, AUTOMATIC )            CopiedLengthToUl_u16 )
{
    /* Declare local variables */
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )       lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, AUTOMATIC, AUTOMATIC)             lSoAdDyncSocConfig_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic socket configuration pointers */
    lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* --------------------------------------------- */
    /* Update Rx buffer variables                    */
    /* --------------------------------------------- */

    /* Update SoAd Rx buffer variables */
    lSoAdDynRxBuff_pst->RxNxtData_pu8 += CopiedLengthToUl_u16;
    lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 -= ( (CopiedLengthToUl_u16 > lSoAdDynRxBuff_pst->TpDataCurrentSize_u16)? (CopiedLengthToUl_u16 - lSoAdDynRxBuff_pst->TpDataCurrentSize_u16) : (0U) );
    lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 -= ( (CopiedLengthToUl_u16 > lSoAdDynRxBuff_pst->TpDataCurrentSize_u16)? (lSoAdDynRxBuff_pst->TpDataCurrentSize_u16) : (CopiedLengthToUl_u16) );
    lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 -= (uint32)( CopiedLengthToUl_u16 );

#if (SOAD_TCP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Confirm TCP reception (UL data)               */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00564] */
    /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
    /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

    /* Check if upper layer type is TCP */
    if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP )
    {
        /* The reception of socket data is confirmed to the TCP/IP stack */
        (void)TcpIp_TcpReceived( lSoAdDyncSocConfig_pst->socketHandleTcpIp_uo,
                                 CopiedLengthToUl_u16 );
    }
#endif

    /* --------------------------------------------- */
    /* Check if complete Pdu is forwarded            */
    /* --------------------------------------------- */

    /* If complete Pdu has been forwarded */
    if( lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 == 0U )
    {
        /* If header is enabled */
        if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE )
        {
            /* [SWS_SoAd_00574] */
            /* In the SoAd_Mainfunction() the SoAd shall process as specified below if a TP reception is in progress for a socket connection with PDU Header mode enabled: */
            /* (3) call <Up>_[SoAd][Tp]RxIndication() if the complete PDU has been forwarded to the upper layer [...] */

            /* Call the upper layer with notify reslut type E_OK */
            SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                            SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo,
                                            E_OK);

            /* Terminate the TP reception session */
            lSoAdDyncSocConfig_pst->tpReceptionOngoing_b = FALSE;
            lSoAdDyncSocConfig_pst->idxRxPduTable_uo = (PduIdType)0xFFFF;
        }
    }

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_DispatchNextTpPduFromRxBuffer()    - This function dispatch the next Tp pdu from SoAd Rx buffer if any                 **/
/**                                         This function is for HEADER ENABLED or DISABLED                                     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** TerminationRequested_b              - Flag indicating if the TP reception session shall be terminated (due to socket close) **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
static FUNC( void, SOAD_CODE ) SoAd_DispatchNextTpPduFromRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )   StaticSocketId_uo,
                                                                   VAR( boolean, AUTOMATIC )            TerminationRequested_b )
{
    /* Declare local variables */
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )       lSoAdStaticSocConfig_cpst;
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;
    VAR( BufReq_ReturnType, AUTOMATIC )                                 lBufferRetVal_en;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    VAR(PduIdType, AUTOMATIC)                                           lIdxRxPdu_uo;
    VAR( uint32, AUTOMATIC )                                            lPduHeaderId_u32;
    VAR( uint32, AUTOMATIC )                                            lPduDataLength_u32;
    VAR( PduLengthType, AUTOMATIC )                                     lDataLenUpperLayer_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* --------------------------------------------- */
    /* Header disabled                               */
    /* --------------------------------------------- */
    if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE )
    {
        /* Reload the Pdu remaining length to transfer from Rx buffer to UL */
        /* (Pdu id is always the same in case header is disabled so nothing more need to be done) */
        lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = lSoAdDynRxBuff_pst->TpDataCurrentSize_u16;
    }

    /* --------------------------------------------- */
    /* Header enabled                                */
    /* --------------------------------------------- */
    else
    {
        /* [SWS_SoAd_00574] */
        /* In the SoAd_Mainfunction() the SoAd shall process as specified below if a TP reception is in progress for a socket connection with PDU Header mode enabled: */
        /* (3) [...] dispatch the next TP-PDU (if any) */

        /* Try to dispach next Pdu while there is still some Tp data in Rx buffer and the dispatching is not requested to be terminated  */
        while( (lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 > 0U) && (TerminationRequested_b == FALSE) )
        {
            /* --------------------------------------------- */
            /* Extract header                                */
            /* --------------------------------------------- */

            /* Header is always saved in the SoAd Rx buffer as TP data when header is enabled */

            /* Reading Pdu Id from Ethernet header which shall be used for de-multiplexing and finding out Pdu owner*/
            /*converting the data from Big Endian to controller specific Endianness*/
            lPduHeaderId_u32 = (lSoAdDynRxBuff_pst->RxNxtData_pu8[3]) | (((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[2])<<8U) |
                              (((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[1])<<16U) |(((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[0])<<24U);

            /* Reading Pdu length from Ethernet header which shall be used for finding out Pdu length*/
            /*converting the data from Big Endian to controller specific Endianness*/
            lPduDataLength_u32 = (lSoAdDynRxBuff_pst->RxNxtData_pu8[7]) | (((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[6])<<8U) |
                                 (((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[5])<<16U) | (((uint32)lSoAdDynRxBuff_pst->RxNxtData_pu8[4])<<24U);

            /* Update SoAd Rx buffer variables */
            lSoAdDynRxBuff_pst->RxNxtData_pu8 += SOAD_PDUHDR_SIZE;
            lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 -= SOAD_PDUHDR_SIZE;

#if (SOAD_TCP_PRESENT != STD_OFF)
            /* --------------------------------------------- */
            /* Confirm TCP reception (header)                */
            /* --------------------------------------------- */

            /* [SWS_SoAd_00564] */
            /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
            /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

            /* Check if upper layer type is TCP */
            if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP )
            {
                /* The reception of socket data is confirmed to the TCP/IP stack */
                (void)TcpIp_TcpReceived( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                         SOAD_PDUHDR_SIZE );
            }
#endif

            /* --------------------------------------------- */
            /* Select Rx socket route                        */
            /* --------------------------------------------- */

            /* Get the socket route according to the received Pdu header Id */
            lRetVal_en = SoAd_SelectRxSocketRoute(  StaticSocketId_uo,
                                                    lPduHeaderId_u32,
                                                    TRUE,
                                                    &lIdxRxPdu_uo );

            /* In case a valid socket route has been found */
            if( lRetVal_en == E_OK )
            {
                /* --------------------------------------------- */
                /* Call StartOfReception                         */
                /* --------------------------------------------- */

                /* Step (a) of [SWS_SoAd_00571] */
                /* (a) After reception of a complete PDU Header, call <Up>_[SoAd][Tp]StartOfReception() of the related upper layer module with RxPduId set to the ID specified by */
                /*     the upper layer module for the PDU referenced by SoAdRxPduRef, set TpSduLength to the length specified in the PDU Header, and set PduInfoType.SduDataPtr and */
                /*     PduInfoType.SduLength to provide already received PDU data to the upper layer. */

                /* Initialization of data length available at Upper layer to 0 */
                lDataLenUpperLayer_uo = 0;

                /* Start of reception function to the Upper layer */
                lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_StartOfReceptionCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lIdxRxPdu_uo].idxTpStartReceptionCbk_u8].StartOfReception_pfn (
                                            SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lIdxRxPdu_uo].ulRxPduId_uo,
                                            NULL_PTR,
                                            0U,
                                            &lDataLenUpperLayer_uo );

                /* In case of success */
                if( lBufferRetVal_en == BUFREQ_OK )
                {
                    /* TP reception is now ongoing */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b = TRUE;
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxRxPduTable_uo = lIdxRxPdu_uo;

                    /* Save the remaining length to transfer from Rx buffer to UL */
                    lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = lPduDataLength_u32;

                    /* Break the loop as the current Tp Pdu reception is now started successfully */
                    break;
                }

                /* In case of error */
                else
                {
                    /* Discard the Pdu from the SoAd Rx buffer */
                    SoAd_DiscardActualTpPduFromRxBuffer( StaticSocketId_uo, lPduDataLength_u32 );
                }

            }
            /* In case of error */
            else
            {
                /* Discard the Pdu from the SoAd Rx buffer */
                SoAd_DiscardActualTpPduFromRxBuffer( StaticSocketId_uo, lPduDataLength_u32 );
            }
        }
    }

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_DiscardActualTpPduFromRxBuffer()    - This function discard the current Tp Pdu from the SoAd Rx buffer                 **/
/**                                         This function is for HEADER ENABLED                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** TotalPduDataLength_u32                  - Total Pdu data length of the Pdu that need to be discarded                        **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
static FUNC( void, SOAD_CODE ) SoAd_DiscardActualTpPduFromRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,
                                                                    VAR( uint32, AUTOMATIC )            RemainingLenToTransfer_u32 )
{
    /* Declare local variables */
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )       lSoAdStaticSocConfig_cpst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                            lAvailableTpPduDataLength_u16;
    VAR( uint16, AUTOMATIC )                                            lDiscardedLength_u16;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* Initialize the discarded length to 0 */
    lDiscardedLength_u16 = 0U;

    /* ------------------------------------- */
    /* Clear fragmented data from Rx buffer  */
    /* ------------------------------------- */

    /* If there are fragmentation along with the current Tp Pdu reception in SoAd Rx buffer */
    if( (lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b == TRUE)    &&
        (lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 > (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16)) )
    {
        /* Increment discarded length */
        lDiscardedLength_u16 = lSoAdDynRxBuff_pst->DataFragCurrentSize_u16;

        /* Update Rx buffer variables */
        lSoAdDynRxBuff_pst->RxNxtFree_pu8 -= lSoAdDynRxBuff_pst->DataFragCurrentSize_u16;
        lSoAdDynRxBuff_pst->DataFragCurrentSize_u16 = 0U;

        /* Fragmented Pdu data no more in progress */
        lSoAdDynRxBuff_pst->DataFragReceptionInProgress_b = FALSE;
    }


    /* ------------------------------------- */
    /* Clear Tp data from Rx buffer          */
    /* ------------------------------------- */

    /* Compute available TP Pdu data length in the buffer */
    lAvailableTpPduDataLength_u16 = ( ((RemainingLenToTransfer_u32 - (uint32)(lDiscardedLength_u16)) < (uint32)(lSoAdDynRxBuff_pst->TpDataCurrentSize_u16))? (uint16)(RemainingLenToTransfer_u32 - (uint32)(lDiscardedLength_u16)) : (lSoAdDynRxBuff_pst->TpDataCurrentSize_u16) );

    /* Increment discarded length */
    lDiscardedLength_u16 += lAvailableTpPduDataLength_u16;

    /* Update Rx buffer variables */
    lSoAdDynRxBuff_pst->RxNxtData_pu8 += lAvailableTpPduDataLength_u16;
    lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 -= lAvailableTpPduDataLength_u16;


    /* ------------------------------------- */
    /* Clear current TP transfer             */
    /* ------------------------------------- */

    /* Set the remaining length to transfer tofrom Rx buffer to UL to 0 because actual TP Pdu is discarded */
    lSoAdDynRxBuff_pst->TpDataRemainingLenToTransfer_u32 = 0U;


#if (SOAD_TCP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Save remaining length to discard for Tcp      */
    /* --------------------------------------------- */

    /* If we are in case of Tcp, we need to remember how many byte still need to be discarded */
    /* (fragmentation can occur for Tcp but not Udp and if there is fragmentation the following fragments of the current Pdu to discard need to be discarded in following RxIndication) */
    if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP)   &&
        ((RemainingLenToTransfer_u32 - (uint32)(lDiscardedLength_u16)) > 0U) )
    {
        /* Save remaining length to be discarded in dynamic socket */
        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].rxTcpRemainingPduLengthToDicard_u32 = ( RemainingLenToTransfer_u32 - (uint32)(lDiscardedLength_u16) );
    }
#endif


#if (SOAD_TCP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Confirm TCP reception (discard)               */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00564] */
    /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
    /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

    /* Check if upper layer type is TCP */
    if(  SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP )
    {
        /* The reception of socket data is confirmed to the TCP/IP stack */
        (void)TcpIp_TcpReceived(    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                    lDiscardedLength_u16 );
    }
#endif

    return;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ReorganiseRxBuffer()   - This function copies the used part of the SoAd Rx buffer to the beginning to prevent hole     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               None                                                                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
static FUNC( void, SOAD_CODE ) SoAd_ReorganiseRxBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR( SoAd_DynRxBuffTableType_tst, SOAD_VAR, SOAD_VAR )            lSoAdDynRxBuff_pst;
    VAR( uint16, AUTOMATIC )                                            lTotalOccupiedSize_u16;
    VAR( uint16, AUTOMATIC )                                            lBufferIndex_u16;

    /* Get dynamic buffer table */
    lSoAdDynRxBuff_pst = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst;

    /* If the pointer to the starting of data in the buffer is different from the starting of the buffer */
    if( lSoAdDynRxBuff_pst->RxNxtData_pu8 != (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8) )
    {
        /* Compute total occupied size in buffer */
        lTotalOccupiedSize_u16 = ( lSoAdDynRxBuff_pst->TpDataCurrentSize_u16 + (lSoAdDynRxBuff_pst->HeaderFragCurrentSize_u8 + lSoAdDynRxBuff_pst->DataFragCurrentSize_u16) );

        /* If complete buffer is not empty */
        if( lTotalOccupiedSize_u16 != 0U )
        {
            /* Copy each byte one by one */
            for( lBufferIndex_u16 = 0U; lBufferIndex_u16 < lTotalOccupiedSize_u16;  lBufferIndex_u16++ )
            {
                lSoAdDynRxBuff_pst->RxBuffStrt_cpu8[lBufferIndex_u16] = lSoAdDynRxBuff_pst->RxNxtData_pu8[lBufferIndex_u16];
            }

            /* Move pointers */
            lSoAdDynRxBuff_pst->RxNxtData_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 = ( (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8) + lTotalOccupiedSize_u16 );
        }

        /* If the complete buffer is empty */
        else
        {
            /* Simply move the pointers back to the beginning */
            lSoAdDynRxBuff_pst->RxNxtData_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
            lSoAdDynRxBuff_pst->RxNxtFree_pu8 = (uint8*)(lSoAdDynRxBuff_pst->RxBuffStrt_cpu8);
        }
    }

    return;
}
#endif


#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
