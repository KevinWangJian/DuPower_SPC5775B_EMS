
#include "rba_BswSrv.h"
#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *********************************************************************************************************************
 * Dcm_CopyTxData : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * Dcm once upon reception of each segment. Within this call, the received data is copied from the receive TP buffer
 * to the DCM receive buffer.
 *
 * \param           DcmRxPduId: Address of global variable Passed by the appl
 *					PduInfoPtr:
 *					RetryInfoPtr:
 *					TxDataCntPtr:
 *
 * \retval          BufReq_ReturnType:
 *
 *
 *
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData
(
	VAR(PduIdType, AUTOMATIC) DcmTxPduId,
	P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
	/* MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const'*/
	P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr
)
{
    VAR(BufReq_ReturnType,AUTOMATIC) dataReturnType_en;
    P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) adrDataPtr_pst;
    VAR(PduLengthType, AUTOMATIC) idxLengthIndex_u16;
#if((DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    VAR(uint8, AUTOMATIC) idxIndex_u8;
#endif

#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROE_QUEUE_ENABLED != DCM_CFG_OFF))
    VAR(Dcm_DsldstRoeQueueState_ten,AUTOMATIC) stRoeQueueState_st;
    VAR(PduIdType,AUTOMATIC) dataRoeRxPduId_u8; /* Local variable to store ROE RxPdu */
#endif
    dataReturnType_en = BUFREQ_E_NOT_OK;
    idxLengthIndex_u16 = DCM_CFG_NUM_RX_PDUID;
    adrDataPtr_pst = NULL_PTR;

	if(PduInfoPtr != NULL_PTR)
	{
	  if ( DcmTxPduId < DCM_NUM_TX_PDUID )
	  {

    	if(Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] == Dcm_DsldGlobal_st.dataActiveTxPduId_u8)
    	{
            /* Write operations in DSL state machine, Paged buffer handling, ROE, RDPI handling etc in MainFunction and Interrupt context
               When this API is invoked from TP (interrupt) there are chances that the Dsl state is changes in MainFunction context
               Hence locking is necessary */
            SchM_Enter_Dcm_Global_NoNest();
    		if((Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_CONFIRMATION)||
    				(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED))
    		{
    			/* Sending of the wait pend, general reject and normal response */
    			adrDataPtr_pst = &Dcm_DsldPduInfo_st;
    			dataReturnType_en = BUFREQ_OK;
    		}
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    		else if(Dcm_DsldGlobal_st.stDslState_en == DSL_DATA_READY)
    		{
    		    if (PduInfoPtr->SduLength <= (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32)
    		    {
    		        /* Update data in PDU structure */
    		        Dcm_DsldPduInfo_st.SduDataPtr = & Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0];
    		        Dcm_DsldPduInfo_st.SduLength  = (PduLengthType)Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32;
    		        /* Now service is given the filled page. Give buffer to lower layer to transmit */
    		        adrDataPtr_pst = &Dcm_DsldPduInfo_st;
    		        /* Change the DSL to wait for next Dcm_provideTxbuffer  call */
    		        Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_PAGE_TXCONFIRM;
    		        dataReturnType_en = BUFREQ_OK;
    		    }
    		    else
    		    {
    		        /* To send DET error when first Dcm_TpCopyTxData fails for the paged buffer in the first page when the TP requests Dcm to copy payload where the length indicated to copy is greater than the available Dcm response length. */
    		        dataReturnType_en = BUFREQ_E_NOT_OK;
    		        DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_INVALID_LENGTH )
    		    }
    		}
    		else if (Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_DATA)
    		{
    			/* Service is filling the data into the page hence DCM is unable to give buffer  */
    			dataReturnType_en = BUFREQ_E_BUSY;
    		}
    		else if (Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_PAGE_TXCONFIRM)
    		{
				/* Check if the page can be given to the service for filling */
    			if ((Dcm_DsldPduInfo_st.SduLength == 0u ) && ((RetryInfoPtr==NULL_PTR )|| (RetryInfoPtr->TpDataState == TP_DATACONF)))
    			{
    				/* Current page transmission is over. Give the page back to service to fill next page */
    				Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_DATA;
    				dataReturnType_en = BUFREQ_E_BUSY;
    			}
    		    else
    		    {
    		        if ((Dcm_DsldPduInfo_st.SduLength < PduInfoPtr->SduLength ) && (Dcm_DsldGlobal_st.flgPagedBufferTxOn_b))
    				{
    		    /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMSET takes void pointer as input and object type pointer is converted to void pointer*/
    				DCM_MEMSET(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE,Dcm_DsldPduInfo_st.SduLength);
    			    /* copy the  reaming bytes to Start page address */
    			 /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
    			    DCM_MEMCOPY(& Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0], Dcm_DsldPduInfo_st.SduDataPtr, Dcm_DsldPduInfo_st.SduLength);
    			    Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_DATA;
    			    dataReturnType_en = BUFREQ_E_BUSY;
    				}
    		        else
    		        {
    			     /* Current page transmission is not yet over. To copy the requested data */
    			     adrDataPtr_pst = &Dcm_DsldPduInfo_st;
    			     dataReturnType_en = BUFREQ_OK;
    		        }
    		    }
    		}
#endif

    		else
    		{
    			/* Paged buffer timeout happened or some other error, reset lower layer */
    			dataReturnType_en = BUFREQ_E_NOT_OK;
    		}
            SchM_Exit_Dcm_Global_NoNest();
    	}
#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROE_QUEUE_ENABLED == DCM_CFG_OFF))
    	else if(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].roetype2_txpdu_u8==Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId])
    	{
    		/* This call is for ROE type 2 response. Give the buffer */
    		dataReturnType_en = BUFREQ_OK;
    		adrDataPtr_pst = &Dcm_DsldRoe2PduInfo_st;
    	}
#endif

#if((DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    	else
    	{
    		/* Check if the API is called for RDPI type 2 transmission. If so find the TxPduId used for transmission */
			for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU;idxIndex_u8++)
			{
					if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txpduid_num_u8 == Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId])
					{
						/* Reset the status of the TxPduId */
						/* Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy= FALSE;*/
						dataReturnType_en = BUFREQ_OK;
			    		adrDataPtr_pst = &Dcm_DsldRdpi2pduinfo_ast[idxIndex_u8];
						break;
					}

			}
			if(idxIndex_u8==DCM_CFG_NUM_RDPITYPE2_TXPDU)
			{
	    		/* Update the general return_value which is possible from here */
	    		dataReturnType_en = BUFREQ_E_NOT_OK;

	    		/* Check if there are any Rx Pdu's which have updated SId i.e placed this Tx Pdu for sending NRC-21
	    		 * if that be the case then it is required to update response Buffer for NRC-21 */
	    		for ( idxLengthIndex_u16 = 0; idxLengthIndex_u16 < DCM_CFG_NUM_RX_PDUID ; idxLengthIndex_u16++ )
	    		{

                    VAR(uint16,AUTOMATIC) dcmDsldSid_u16;
                /* Multicore: No lock is necessary for Dcm_DsldSId_u16 as this is a read operation and is atomic
                 * Also as the new request cannot be received on the same RxPduId till the transmission is complete,
                 * there are no chances of parallel write and hence no locks.
                 */
                    dcmDsldSid_u16 = Dcm_DslDsdRxPduArray_ast[idxLengthIndex_u16].Dcm_DsldSId_u16;
                    /*Check if RxPduId is not having the SId equal to 0xFFFF and nrc21 flag for the transmission is set to True*/
                    if ( ( dcmDsldSid_u16 != 0xFFFFu ) && ( Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxLengthIndex_u16]].txpduid_num_u8 == Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] ) && ( Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxLengthIndex_u16]].protocol_num_u8)].nrc21_b != FALSE ))
	    			{
	    				/* Set Return Value to BUFREQ_OK */
	    				dataReturnType_en = BUFREQ_OK;

							if ( PduInfoPtr->SduLength != 0u )
							{
								/* Nesting of control structures (statements) exceeds 15 - program does not conform strictly to ISO:C90.- Control structure required for functionality implementation */
								if(PduInfoPtr->SduDataPtr != NULL_PTR)
								{
									*(PduInfoPtr->SduDataPtr) = 0x7F; /* Negative Response Indicator */

									PduInfoPtr->SduDataPtr++;
									*(PduInfoPtr->SduDataPtr) = (uint8)dcmDsldSid_u16; /* Service Id */

									PduInfoPtr->SduDataPtr++;
									*(PduInfoPtr->SduDataPtr) = 0x21; /* NRC-21 BusyRepeatRequest */

									/* Update to TP that there is no more data to fill */
									*(TxDataCntPtr) = 0;
								}
								else
								{
									dataReturnType_en = BUFREQ_E_NOT_OK;
									DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
								}
							}
							else
							{
								/* Update length as 3, 0x7F, SId and NRC-21 */
								*(TxDataCntPtr) = 3;
							}

							break;
						}
					}
				}
			}
#else
    	else
    	{
    		/* Update the general return_value which is possible from here */
    		dataReturnType_en = BUFREQ_E_NOT_OK;

    		/* Check if there are any Rx Pdu's which have updated SId i.e placed this Tx Pdu for sending NRC-21
    		 * if that be the case then it is required to update response Buffer for NRC-21 */
    		for ( idxLengthIndex_u16 = 0; idxLengthIndex_u16 < DCM_CFG_NUM_RX_PDUID ; idxLengthIndex_u16++ )
    		{
                VAR(uint16,AUTOMATIC) dcmDsldSid_u16;
                /* Multicore: No lock is necessary for Dcm_DsldSId_u16 as this is a read operation and is atomic
                 * Also as the new request cannot be received on the same RxPduId till the transmission is complete,
                 * there are no chances of parallel write and hence no locks.
                 */
                dcmDsldSid_u16 = Dcm_DslDsdRxPduArray_ast[idxLengthIndex_u16].Dcm_DsldSId_u16;
                /*Check if RxPduId is not having the SId equal to 0xFFFF and nrc21 flag for the transmission is set to True*/
    			if ( ( dcmDsldSid_u16 != 0xFFFFu ) && ( Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxLengthIndex_u16]].txpduid_num_u8 == Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] ) && ( Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxLengthIndex_u16]].protocol_num_u8)].nrc21_b != FALSE ))
    			{
    				/* Set Return Value to BUFREQ_OK */
    				dataReturnType_en = BUFREQ_OK;

						if ( PduInfoPtr->SduLength != 0u )
						{
							if(PduInfoPtr->SduDataPtr != NULL_PTR)
							{
								*(PduInfoPtr->SduDataPtr) = 0x7F; /* Negative Response Indicator */

								PduInfoPtr->SduDataPtr++;
								*(PduInfoPtr->SduDataPtr) = (uint8)dcmDsldSid_u16; /* Service Id */

								PduInfoPtr->SduDataPtr++;
								*(PduInfoPtr->SduDataPtr) = 0x21; /* NRC-21 BusyRepeatRequest */


								/* Update to TP that there is no more data to fill */
								*(TxDataCntPtr) = 0;
							}
							else
							{
								dataReturnType_en = BUFREQ_E_NOT_OK;
								DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
							}
						}
						else
						{
							/* Update length as 3, 0x7F, SId and NRC-21 */
							*(TxDataCntPtr) = 3;
						}

						break;
					}
				}
			}
#endif
    	/* This snippet of code does the copying to TP's Transmit Buffer for normal Tx msgs */
    	if ( (dataReturnType_en == BUFREQ_OK) && (idxLengthIndex_u16 == DCM_CFG_NUM_RX_PDUID))
    	{
				if(adrDataPtr_pst != NULL_PTR)
				{
    		if ( PduInfoPtr->SduLength != 0u )
    		{
				/* If Retry is requested by lower layer */
				if((RetryInfoPtr!=NULL_PTR) && (RetryInfoPtr->TpDataState==TP_DATARETRY))
				{
					/* Check if the Retry count is valid */
							if((RetryInfoPtr->TxTpDataCnt> 0u ) && (PduInfoPtr->SduDataPtr != NULL_PTR))
					{
						/* Update DataPtr with the offset count transmitted by lower layer */

						adrDataPtr_pst->SduDataPtr = adrDataPtr_pst->SduDataPtr - RetryInfoPtr->TxTpDataCnt;

						/* Update the remaining length to be transmitted to include the number of bytes to be transmitted again as requested by lower layer */
						adrDataPtr_pst->SduLength = adrDataPtr_pst->SduLength + RetryInfoPtr->TxTpDataCnt;
					}
					/* If retry count is 0x00 */
					else
					{
						dataReturnType_en = BUFREQ_E_NOT_OK;
					}
				}


						if ((PduInfoPtr->SduLength <= adrDataPtr_pst->SduLength) && (dataReturnType_en == BUFREQ_OK))
						{
							if(PduInfoPtr->SduDataPtr != NULL_PTR)
							{
								/* If the requested Tx buffer is less than the available Tx buffer, copy the data */
							   /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
			    				DCM_MEMCOPY(PduInfoPtr->SduDataPtr, adrDataPtr_pst->SduDataPtr, PduInfoPtr->SduLength);

								/* Update adrDataPtr_pst for remaining length and buffer pointer update */

								adrDataPtr_pst->SduDataPtr = adrDataPtr_pst->SduDataPtr + PduInfoPtr->SduLength;
								adrDataPtr_pst->SduLength = (uint16)((uint16)adrDataPtr_pst->SduLength - (uint16)PduInfoPtr->SduLength);
								/* Update remaining Length Information to TP layer */
								*(TxDataCntPtr) = adrDataPtr_pst->SduLength;
							}
							else
							{
								dataReturnType_en = BUFREQ_E_NOT_OK;
								DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )

							}
						}
						else
						{
							dataReturnType_en = BUFREQ_E_NOT_OK;
						}

					}
					else
					{
						/* Here there is no data to be copied, just to provide the available buffer size */
						*(TxDataCntPtr) = adrDataPtr_pst->SduLength;
					}
				}
			}
		}
	  else
	  {
		    DCM_DET_ERROR(DCM_COPYTXDATA_ID ,DCM_E_DCMTXPDUID_RANGE_EXCEED)
	  }
	}
	else
	{
		DCM_DET_ERROR(DCM_COPYTXDATA_ID , DCM_E_PARAM_POINTER )
	}
	return(dataReturnType_en);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
