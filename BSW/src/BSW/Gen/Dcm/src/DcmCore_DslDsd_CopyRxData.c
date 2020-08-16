

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *********************************************************************************************************************
 * Dcm_CopyRxData : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * Dcm once upon reception of each segment. Within this call, the received data is copied from the receive TP buffer
 * to the DCM receive buffer.
 *
 * \param           DcmRxPduId: Address of global variable Passed by the appl
 *					PduInfoPtr:  Pointer to a PduInfoType which indicates the number of bytes to be copied (SduLength) and the location of the source data (SduDataPtr).
 *					RxBufferSizePtr: Remaining free place in receive buffer after completion of this call.
 *
 * \retval          BufReq_ReturnType:
 *
 *
 *
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */
/*  Cannot change from pointer to variable to pointer to constant as the API is defined so in the DCM SWS AR4.0 Rev 2 */
FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData
(
	VAR(PduIdType, AUTOMATIC) DcmRxPduId,
	/* MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const' */
	P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
)
{
	VAR(BufReq_ReturnType,AUTOMATIC) dataReturnValue_en;

	/* Initialise the return value */
	dataReturnValue_en = BUFREQ_E_NOT_OK;


	if (DcmRxPduId<DCM_CFG_NUM_RX_PDUID)
	{
	  if ((PduInfoPtr != NULL_PTR) && (RxBufferSizePtr!=NULL_PTR))
      {
	      /* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
if ( PduInfoPtr->SduDataPtr != NULL_PTR )
{
		/* Shared RX PduId should always be functional - So extra check is not necessary */
		/* Check if the received SID is in the OBD SID range 0x1-0x10 */
		/* RxPdu should range is limited as one PduId is shared */
        /*Check if obd request indication flag is set to True*/
		if((DcmRxPduId < (DCM_CFG_NUM_RX_PDUID-1u)) && (DcmRxPduId == DCM_CFG_SHARED_RX_PDUID) &&
			(((PduInfoPtr->SduDataPtr[0] > 0x0u) && (PduInfoPtr->SduDataPtr[0] < 0xBu))&&(Dcm_DsldObdReqIndn_b!=FALSE)))
		{
			/* Assign the last RxPdu for further processing as the
			   generated code use the last Rx Pdu for OBD_ON_CAN */
			DcmRxPduId = (DCM_CFG_NUM_RX_PDUID-1u);
		}
}
#endif
	/* FC_VariationPoint_END */
		if ( PduInfoPtr->SduLength != 0u )
		{
			if ( PduInfoPtr->SduDataPtr != NULL_PTR )
			{
			    /*Check if the Dcm_DsldCopyRxData is set to True*/
				if ( Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b != FALSE)
				{
					if ( PduInfoPtr->SduLength <= Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength )
					{
					   /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
					    DCM_MEMCOPY(Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduDataPtr, PduInfoPtr->SduDataPtr,PduInfoPtr->SduLength);
						Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduDataPtr += PduInfoPtr->SduLength;
						Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength = (uint16)((uint16)Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength -(uint16)PduInfoPtr->SduLength);
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
#if(DCM_BUFQUEUE_ENABLED !=DCM_CFG_OFF)
						if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE)
						{
							(void)DcmAppl_CopyRxData(DcmRxPduId,PduInfoPtr->SduLength);
						}
#else
                        (void)DcmAppl_CopyRxData(DcmRxPduId,PduInfoPtr->SduLength);
#endif
#endif
						/* Update remaining buffer size info to underlying TP layer */
						*(RxBufferSizePtr) = Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength;

						/* Set dataReturnValue_en as BUFREQ_OK as copy is successfully done */
						dataReturnValue_en = BUFREQ_OK;
					}
					else
					{
						/* SduDataLength passed in this call of Dcm_CopyRxData is more than the remaining bytes which Dcm
						 * is expecting, thus this call of Dcm_CopyRxData should be rejected, dataReturnValue_en is already set
						 * accordingly */
						/* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW " to DET module if the DET module is enabled */
						DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_INTERFACE_BUFFER_OVERFLOW )
					}
				}
				else
				{
					/* If the CopyRxData call is for Functional TP received on the same/different connection as the first request under processing */
				    /*Check if the Functional TP received is on same conection and set to True*/
					if(FALSE != Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b)
					{
						dataReturnValue_en = BUFREQ_OK;
					}
					/*Check if the nrc21 flag, transmission for the same Rx Pdu is set to True*/
					else if (Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8)].nrc21_b != FALSE)
					{
						/* If the channel is on full communication */
						if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8))
						{
							/* This is probably the case of pseudo copy, thus set the dataReturnValue_en as BUFREQ_OK without any copy operation if the channel is in full_comm mode*/
							dataReturnValue_en = BUFREQ_OK;
						}
						else
						{
							/* This is probably the case of pseudo copy, thus set the dataReturnValue_en as BUFREQ_E_NOT_OK if the channel is not in full_comm mode*/
							/*dataReturnValue_en is already set accordingly.*/
							dataReturnValue_en = BUFREQ_E_NOT_OK;
						}

					}
					else
					{
						dataReturnValue_en = BUFREQ_E_NOT_OK;

					}
				}
                /* Written in Dcm_Init, Dcm_CopyRxData, Dcm_TpRxIndication, Dcm_StartOfReception and Dcm_TpTxConfirmation
                 * Read in Dcm_CopyRxData, Dcm_CopyTxData, Dcm_TpRxIndication, Dcm_StartOfReception and Dcm_TpTxConfirmation
                 * There is a possibility that Rx is active on the RxPduId on which Dcm is waiting for the Tx completion.
                 * Ex: NRC21 transmission for the same Rx Pdu where the states are not changed. Hence the access to this
                 * variable needs to be locked. */

				/* The very first Dcm_CopyRxData call after Dcm_StartOfReception on that RxPduId shall have SId still 0xFFFF, if that is the case take a back-up of SId info, which may be needed
				 * SId needs to be stored irrespective of the existing state of Dcm_DsldCopyRxData_b as it is quite possible that during the reception, a higher priority protocol may interrupt
				 * forcing NRC-21 to be sent on this RxPduId later */
                SchM_Enter_Dcm_Global_NoNest();
                /*Check if the RxPduId shall have SId still 0xFFFF and Functional TP received flag is set to False */
				if ((Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 == 0xFFFFu) && (Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b == FALSE))
				{
					Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 = (uint8)PduInfoPtr->SduDataPtr[0];
				}

				SchM_Exit_Dcm_Global_NoNest();
			}
			else
			{
				/* SduDataPtr cannot be NULL_PTR when SduLength is not equal to zero, thus this call of
				Dcm_CopyRxData should be rejected, dataReturnValue_en is already set accordingly */
				/* Report development error "DCM_E_PARAM_POINTER " to DET module if the DET module is enabled */
				DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER )
			}
		}
		else
		{
			/* SduLength is called with value zero, thus Dcm needs to update to the underlying TP on the no. of
			remaining bytes left */
		    /*Check if Dcm_DsldCopyRxData flag is supported and set to True*/
			if ( Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b != FALSE)
			{
				*(RxBufferSizePtr) = Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength;
			}
			else
			{
				/* Simulating reception without copying, thus update to TP that Buffer is available for any length. The available Rx buffer is updated in this case. */
				*(RxBufferSizePtr) = (PduLengthType) (Dcm_DsldProtocol_pcst[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8].rx_buffer_size_u32) ;
			}
			dataReturnValue_en = BUFREQ_OK;
		}
	}
	  else
	  {
	         //Set DET Error NULL_PTR
	         DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_PARAM_POINTER )
	  }
	}
	else
    {
	   //Set DET Error Range Exceed
	   DCM_DET_ERROR(DCM_COPYRXDATA_ID , DCM_E_DCMRXPDUID_RANGE_EXCEED )
    }
	return (dataReturnValue_en);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
