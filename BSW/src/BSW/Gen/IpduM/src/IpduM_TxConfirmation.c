
#include "PduR_IpduM.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "IpduM.h"
#include "IpduM_Priv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Ipdum_TxConfirmation
 Syntax           : void Ipdum_TxConfirmation (PduIdType TxPduId)
 Description      : This is the AUTOSAR callback to indicate successful transmission.
 Parameter        : TxPduId : PduId of transmitted MPdu
 Return value     : None.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_TxConfirmation (
                                                VAR(PduIdType, AUTOMATIC) PdumTxPduId
                                            )
                                            {

    /* Start: Det */
    /* Return Type: void */
    IPDUM_REPORT_ERROR((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_TxConfirmation, IPDUM_E_UNINIT)
    /* End: Det */

    /*Process for regular Pdus*/
    if(PdumTxPduId < IPDUM_NUM_TX_MPDUS)
    {
#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)
        /* pointer to RAM data */
        P2VAR(IpduM_TxRamType, AUTOMATIC, IPDUM_APPL_DATA) TxRamPtr;

        boolean TxConfirm;

        /**** End Of Declarations ****/

        /* Get the DynPart PduId */
        TxRamPtr = &IpduM_TxRamData[PdumTxPduId];
        TxConfirm = FALSE;
        /* Checking for state*/
        if(TxRamPtr->TxState == IPDUM_TX_REQUESTED)
        {
            TxRamPtr->TxState = IPDUM_TX_READY;
            TxConfirm = TRUE;
        }
        /* IpduM Transmit not requested */
        else
        {
            /* Check for timeout value and trigger mode*/
            if(
                    (IpduM_TxMPduTable[PdumTxPduId].TxConfirmTimeout == 0u) ||
                    (IpduM_TxMPduTable[PdumTxPduId].TxTriggMode == IPDUM_NONE)
            )
            {
                TxConfirm = TRUE;
            }
        }

        if(TxConfirm != FALSE)
        {
            /* Check for dynamic part support*/
            if (TxRamPtr->DynPartPduId != IPDUM_INVALID_INDEX)
            {
                /* Send a dynamic part transmit confiramtion to upper layer*/
                IPDUM_UPL_TXCONFIRMATION(TxRamPtr->DynPartPduId);
                TxRamPtr->DynPartPduId = IPDUM_INVALID_INDEX;
            }
            /* Check for static part support*/
            if (TxRamPtr->StaticPartPduId != IPDUM_INVALID_INDEX)
            {
                /* Send a static part transmit confiramtion to upper layer*/
                IPDUM_UPL_TXCONFIRMATION(TxRamPtr->StaticPartPduId);
                TxRamPtr->StaticPartPduId = IPDUM_INVALID_INDEX;
            }
        }
#endif
    }
    /*Below code will execute only for contained Tx pdu*/
    else if((PdumTxPduId >= IPDUM_NUM_TX_MPDUS) && (PdumTxPduId < IPDUM_TOTAL_NUM_TX_MPDUS))
    {
#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)
        {
            /* Pointer to Container(Cr) Tx table*/
            P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrPtr_pst;

            P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContainedPduConstPtr_pst;

            /*Pointer to Tx ContainerPduDynamicType table*/
            P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrRAMptr_pst;

            /*Variable to hold the Container Pdu Id*/
            PduIdType TxContainerPduId;
            P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) HeaderAddr;
            uint8 HeaderSize_u8;
            uint32 HeaderId;
            uint32 Index_u32;
            uint32 ContainedtableIndex_u32;
            uint32 Dlc;
            Index_u32 = 0 ;
            TxContainerPduId = PdumTxPduId - IPDUM_NUM_TX_MPDUS;

            TxCntnrPtr_pst = &IpduM_TxContainerPdu[TxContainerPduId];

            HeaderSize_u8 = TxCntnrPtr_pst->HeaderSize;
            /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
            TxCntnrRAMptr_pst = &IpduM_TxContainerPduDynData[TxContainerPduId];

            /*If TxConf timer is set to 0 or not configured for this container then ignore the Tx Confirmation*/
            if((TxCntnrRAMptr_pst->TxConfPtr != NULL_PTR) && (TxCntnrRAMptr_pst->TxConfRAMTicks != 0))
            {
                /*loop till valid data is present in the container*/
                while(Index_u32 < IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrRAMptr_pst->TxConfPtr,
                        TxCntnrPtr_pst->TxContainerPduLen))
                {
                    HeaderAddr = TxCntnrRAMptr_pst->TxConfPtr + Index_u32;
                    HeaderId = IpduM_ReadIdFromHeader(HeaderSize_u8,HeaderAddr);
                    Dlc = IpduM_ReadDlcFromHeader(HeaderSize_u8,HeaderAddr);
                    /*loop thru all the contained Pdu's*/
                    for(ContainedtableIndex_u32 = 0; ContainedtableIndex_u32 < IPDUM_NUM_CONTAINED_TX_PDUS; ContainedtableIndex_u32++)
                    {
                        TxContainedPduConstPtr_pst = &IpduM_TxContainedPdu[ContainedtableIndex_u32];
                        /*Check if header Id matches with the Pdu header If present in contained table.*/
                        if(HeaderId == TxContainedPduConstPtr_pst->PduHeaderId)
                        {
                            /* Check if the corresponding TxContainedPdu expects TxConfirmation */
                            if(TxContainedPduConstPtr_pst->TxPduConfirmation != FALSE)
                            {
                                IPDUM_UPL_TXCONFIRMATION(TxContainedPduConstPtr_pst->TxConfirmationTargetPduId);
                                /* After finding a corresponding HeaderId in a containedPdu, break for this loop and continue processing for other contained Pdu's */
                                break;
                            }
                        }
                    }

                    Index_u32 = (Index_u32 + HeaderSize_u8 + Dlc);
                }
                /*Flush this container instance data. I,e set the byte(Container Sdu len) to 0 */
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrRAMptr_pst->TxConfPtr,TxCntnrPtr_pst->TxContainerPduLen) = 0;
                /*Set Tx confirmation pointer to NULL_PTR*/
                TxCntnrRAMptr_pst->TxConfPtr = NULL_PTR;
                /*Set Tx confirmation RAM Ticks to 0*/
                TxCntnrRAMptr_pst->TxConfRAMTicks = 0;
            }
            else
            {

                /*Ignore the Tx confirmation*/
            }
        }
#endif /*#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)*/
    }
    else
    {
        IPDUM_REPORT_ERROR((PdumTxPduId >= IPDUM_TOTAL_NUM_TX_MPDUS), IPDUMServiceId_TxConfirmation, IPDUM_E_PARAM)
    }

}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

