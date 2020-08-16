

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* definition of PDU info structure of DCM */
VAR(PduInfoType,DCM_VAR) Dcm_DsldPduInfo_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DsldResetCopyRxDataStatus : Function to reset CopyRxData status of all other dataRxPduId_u8 except
 * 									that dataRxPduId_u8 which has been passed as parameter
 * \param           dataRxPduId_u8 (in):  PDU Id for which CopyRxData status should not be reset
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void, DCM_CODE) Dcm_DsldResetCopyRxDataStatus ( VAR(PduIdType,AUTOMATIC) dataRxPduId_u8 )
{
	VAR(PduIdType,AUTOMATIC) dataPdu_u8;

	for ( dataPdu_u8 = 0 ; dataPdu_u8 < DCM_CFG_NUM_RX_PDUID ; dataPdu_u8++ )
	{
	    /*Check if the CopyRxData status is set and dataRxPduId_u8 which has been not passed as parameter */
		if ( ( dataPdu_u8 != dataRxPduId_u8 ) && (Dcm_DslDsdRxPduArray_ast[dataPdu_u8].Dcm_DsldCopyRxData_b != FALSE ) )
		{
		    /*Reset the CopyRxData status to false*/
			Dcm_DslDsdRxPduArray_ast[dataPdu_u8].Dcm_DsldCopyRxData_b = FALSE;
		}
	}
}

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_DsldPremptionHandling_u8 : Function to do the protocol preemption handling
 * \param           adrArrivedProt_pcst (in):  Pointer to protocol table (for newly arrived request)
 *                  nrTpSduLength_u16 (in) : Length of the request.
 *                  dataRxpduId_u8     (in) : Rx PDU id of arrived request.
 *
 * \retval          BufReq_ReturnType : same as above function
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(BufReq_ReturnType, DCM_CODE) Dcm_DsldPremptionHandling_u8
                                                    (
                                                            P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst,
                                                            VAR(PduLengthType,AUTOMATIC) nrTpSduLength_u16,
                                                            VAR(PduIdType,AUTOMATIC) dataRxpduId_u8
                                                     )

{
    /* Local variable for return value */
    VAR(BufReq_ReturnType,AUTOMATIC) dataReturnValue_en;
    /* Local variable for connection index */
    VAR(uint8,AUTOMATIC) dataConnectionId_u8;
    /* Local variable for protocol index  */
    VAR(uint8,AUTOMATIC) idxProtocol_u8;

    /* Check the size of the buffer */
    if((uint32)nrTpSduLength_u16 <= adrArrivedProt_pcst->rx_buffer_size_u32)
    {
        /* Check if already high priority protocol request is under reception or not */
        if(Dcm_DsldGlobal_st.dataNewRxPduId_u8 == 0xff)
        {
        	/* Set return value as BUFREQ_OK */
        	dataReturnValue_en = BUFREQ_OK;

            if(adrArrivedProt_pcst->premption_level_u8 <
                          Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].premption_level_u8)

            {
                /* Store the Rx PDU id, request length and ready to receive buffer */
                /* dataRxPduId_u8 of new request should be stored*/
                Dcm_DsldGlobal_st.dataNewRxPduId_u8 = dataRxpduId_u8;
                Dcm_DsldGlobal_st.dataNewdataRequestLength_u16  = nrTpSduLength_u16;
                /*Update the pre-emption state to DSL_STOP_PROTOCOL_RECEIVING, the same state will be moved to
                 * DSL_STOP_PROTOCOL when the request is fully received i.e., on a positive RxIndication*/
                Dcm_DsldGlobal_st.stDslPreemptionState_en=DSL_STOP_PROTOCOL_RECEIVING;
                /*Set the CopyRxData data status to true*/
                Dcm_DslDsdRxPduArray_ast[dataRxpduId_u8].Dcm_DsldCopyRxData_b  = TRUE;
                Dcm_DsldResetCopyRxDataStatus(dataRxpduId_u8);
            }
            else
            {
            	/* Lower priority protocol received, dataReturnValue_en is already set accordingly to
            	 * receive SID to send NRC21, in case NRC21 need not be triggered for this protocol
            	 * it is required to reset the return value back to BUFREQ_E_NOT_OK */

            	if ( adrArrivedProt_pcst->nrc21_b == FALSE )
            	{
            		dataReturnValue_en = BUFREQ_E_NOT_OK;
            	}
            }
        }
        else
        {
            /* High priority request under reception   */
            /* Connection on which request is received */
            dataConnectionId_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataNewRxPduId_u8];

            /* protocol of the received Rx PDU id */
            idxProtocol_u8 = Dcm_DsldConnTable_pcst[dataConnectionId_u8].protocol_num_u8;

            /* Set return value as BUFREQ_OK */
            dataReturnValue_en = BUFREQ_OK;

            /* Check arrived request has higher priority than already preempting protocol */
            if(adrArrivedProt_pcst->premption_level_u8 < Dcm_DsldProtocol_pcst[idxProtocol_u8].premption_level_u8)
            {
                /* Store the Rx PDU Id, request length and ready to receive buffer */
                Dcm_DsldGlobal_st.dataNewRxPduId_u8 = dataRxpduId_u8;
                Dcm_DsldGlobal_st.dataNewdataRequestLength_u16  = nrTpSduLength_u16;
                /*Update the pre-emption state to DSL_STOP_PROTOCOL_RECEIVING, the same state will be moved to
                 * DSL_STOP_PROTOCOL when the request is fully received i.e., on a positive RxIndication*/
                Dcm_DsldGlobal_st.stDslPreemptionState_en=DSL_STOP_PROTOCOL_RECEIVING;
                /*Initialize the CopyRxData status to the value true */
                Dcm_DslDsdRxPduArray_ast[dataRxpduId_u8].Dcm_DsldCopyRxData_b  = TRUE;
                Dcm_DsldResetCopyRxDataStatus(dataRxpduId_u8);
            }
            else
            {
            	/* Lower priority protocol received, dataReturnValue_en is already set accordingly to
            	 * receive SID to send NRC21, in case NRC21 need not be triggered for this protocol
            	 * it is required to reset the return value back to BUFREQ_E_NOT_OK */

            	if ( adrArrivedProt_pcst->nrc21_b == FALSE )
            	{
                	dataReturnValue_en = BUFREQ_E_NOT_OK;
            	}
            }
        }
    }
    else
    {
        /* buffer is not big enough, ignore the request */
        dataReturnValue_en = BUFREQ_E_OVFL;
    }

    return(dataReturnValue_en);
}


#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
/**
 **************************************************************************************************
 * Dcm_DsldPersistentRoeHandling_en : Function to do the persistent ROE handling
 * \param           adrArrivedProt_pcst (in):  Pointer to protocol table (for newly arrived request)
 *                  nrTpSduLength_u16 (in) : Length of the request.
 *                  RxPduid     (in) : Rx PDU id of arrived request.
 *  If a high priority request is to be taken; and ROE events are invoked - there is a chance ROE would reject the
 * high priority protocols request. IS0 specifies ROE to work persistently as application demands. But when a higher
 * priority protocol preempts the ROE protocol. THe high priority protocols requests are not to be ignored.
 * \retval          BufReq_ReturnType : same as above function
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_DsldPersistentRoeHandling_en(
                                         P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst,
                                         VAR(PduLengthType,AUTOMATIC) nrTpSduLength_u16,
                                         VAR(PduIdType,AUTOMATIC) dataRxpduId_u8
                                                     )

{
    /* Local variable for return value */
    VAR(BufReq_ReturnType,AUTOMATIC) dataReturnVal_en;
    /* Local variable for Roe connection index */
    VAR(uint8,AUTOMATIC) dataRoeConnId_u8;
    /* Local variable for Roe protocol index  */
    VAR(uint8,AUTOMATIC) idxRoeProt_u8;
    /* Local variable for ROE dataRxPduId_u8  */
    VAR(PduIdType,AUTOMATIC) dataRoeRxPduId_u8;
    /* ROE protocol Table */
    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrRoeProtTable_pcst;

    /* The Active dataRxpduId_u8 when ROETYPE1 is active would be from the protocol where ROE was started*/
    /* This dataRxPduId_u8 can be used to calculate the protocol from where ROE was started */
    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
       there is no parallel writing due to DSL state machine handling */
    dataRoeRxPduId_u8 = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

    /* The connection on which the application invoked ROE */
    dataRoeConnId_u8 = Dcm_DsldRxTable_pcu8[dataRoeRxPduId_u8];

    /* Protocol of the ROE Rx pdu id */
    idxRoeProt_u8 = Dcm_DsldConnTable_pcst[dataRoeConnId_u8].protocol_num_u8;

    /* Get the pointer of ROE protocol table */
    adrRoeProtTable_pcst = &Dcm_DsldProtocol_pcst[idxRoeProt_u8];

    dataReturnVal_en = BUFREQ_E_NOT_OK;

    /* If the request has not arrived on the active protocol yet */
    if(Dcm_DsldGlobal_st.dataPassRxPduId_u8 == 0xff)
    {
        /* Check the size of the buffer */
        if((uint32)nrTpSduLength_u16 <= adrArrivedProt_pcst->rx_buffer_size_u32)
        {
            /* Check arrived request has higher priority */
            if(adrRoeProtTable_pcst->premption_level_u8 > adrArrivedProt_pcst->premption_level_u8)
            {
                /* case when the incoming request is from a same protocol which is active.*/
                /* ROE might stop the preemption*/
                /* this check is for the incoming requests protocol id with the active protocol */
                if(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8 ==
                 adrArrivedProt_pcst->protocolid_u8)
                {
                    /* Store the Rx pduid, request length and ready to receive buffer */
                    Dcm_DsldGlobal_st.dataPassRxPduId_u8 = dataRxpduId_u8;
                    Dcm_DsldGlobal_st.dataPassdataRequestLength_u16  = nrTpSduLength_u16;
                    /*Initialize the CopyRxData status to the value true*/
                    Dcm_DslDsdRxPduArray_ast[dataRxpduId_u8].Dcm_DsldCopyRxData_b = TRUE;
                    Dcm_DsldResetCopyRxDataStatus(dataRxpduId_u8);
                    dataReturnVal_en = BUFREQ_OK;

                    /* The Trasmit_s Dsl Next State is pushed to DSL_RECEIVING ,since if ROE TxConfirmation arrives */
                    /* before RxIndication for this provide Rx Buffer call; DCM has to wait for the RxIndication of */
                    /* current provide Rx Buffer call */

                    Dcm_DsldTransmit_st.stDslNextState_en = DSL_RECEIVING;
                }
            }
            else
            {
                 if(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8 ==
                  adrArrivedProt_pcst->protocolid_u8)
                 {
                     /* ROE type1 request under processing and tester request comes. Reset S3 timer */
                     Dcm_StartS3MaxMonitoring();
                 }
             /* But ignore the request */
             dataReturnVal_en = BUFREQ_E_NOT_OK;
            }

        }
        else
        {
            /* buffer is not big enough, ignore the request */
            dataReturnVal_en = BUFREQ_E_OVFL;
        }
    }
    return dataReturnVal_en;
}
#endif
#endif
 /*
***********************************************************************************************************
*  Dcm_TpRxIndication :This function is called by the lower layer (in general the PDU Router):
*  - with Result = E_OK after the complete DCM I-PDU has successfully been received, i.e. at the very
*    end of the segmented TP receive cycle or after receiving an unsegmented N-PDU.
*  - with Result = E_NOT_OK it is indicated that an error (e.g. timeout) has occurred during
*    the reception of the DCM I-PDU. This passes the receive buffer back to DCM and allows error handling.
*    It is undefined which part of the buffer contains valid data in this case, so the DCM shall not evaluate
*    that buffer. By calling this service only the DCM is allowed to access the buffer.
*
*  \param:   DcmRxPduId     ID of DCM I-PDU that has been received. Identifies the data that has been received.
*            Result         Result of the N-PDU reception:
*                           E_OK if the complete N-PDU has been received.
*                           E_NOT_OK if an error occurred during reception, used to enable
*                           unlocking of the receive buffer.
*  \retval   None
*  \seealso
*  \usedresources
***********************************************************************************************************/


FUNC(void,DCM_CODE) Dcm_TpRxIndication (
                                        VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                        VAR(Std_ReturnType, AUTOMATIC) Result
                                     )
{
    VAR(Dcm_DsldDslStatesType_ten,AUTOMATIC) stDslState_en;
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRxBuffer_pu8;
    #if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) idxKwpTiming_u8;
    #endif
    /* Local variable for connection index */
    VAR(uint8,AUTOMATIC) dataConnectionId_u8;
    /* Local variable for protocol index  */
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(boolean,AUTOMATIC) isProcessRequest_b;
    VAR(PduLengthType,AUTOMATIC) dataRequestLength_u16;
    VAR(PduInfoType,AUTOMATIC) dataPduInfo_st;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(PduIdType,AUTOMATIC) dataActiveRxPduId_u8;
#endif
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldQueHandling_ten,AUTOMATIC) dataqueHandling_en;
#endif

    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */
    stDslState_en   = Dcm_DsldGlobal_st.stDslState_en;


   if ( DcmRxPduId < DCM_CFG_NUM_RX_PDUID)
   {
       /* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
    /*Check whether RxPduId is  equal to 6 and odb request indication is set to true*/
	if((DcmRxPduId < (DCM_CFG_NUM_RX_PDUID-1u)) && (DcmRxPduId == DCM_CFG_SHARED_RX_PDUID) && (Dcm_DsldObdReqIndn_b != FALSE))
	{
		/* Assign the last RxPdu for further processing as the generated code use the last Rx Pdu for OBD_ON_CAN */
		DcmRxPduId = (DCM_CFG_NUM_RX_PDUID-1u);
		/* Reset the variable which denotes the reception of OBD request */
		/*Initialize the odb request indication flag to false*/
		Dcm_DsldObdReqIndn_b = FALSE;
	}
#endif
	/* FC_VariationPoint_END */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    /* Multicore: lock needed here as queue state can be updated in parallel and in RxIndication we can be working on older queue state */
    SchM_Enter_Dcm_Global_NoNest();
    dataqueHandling_en=Dcm_QueueStructure_st.Dcm_QueHandling_en;
    SchM_Exit_Dcm_Global_NoNest();

    if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE)||(Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b!=FALSE))
    {
#endif
		/* Do not allow erroneous reception  */
		if(E_OK == Result)
		{
			/* Connection on which request is received */
			dataConnectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];

			/* protocol of the received Rx pdu id */
			idxProtocol_u8 = Dcm_DsldConnTable_pcst[dataConnectionId_u8].protocol_num_u8;
			/* take the local copy of Rx buffer pointer and DSL state variable */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
			adrRxBuffer_pu8 = (Dcm_DslDsdRxPduArray_ast[DcmRxPduId].adrBufferPtr_pu8);
#else
			adrRxBuffer_pu8 = Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer1_pa;
#endif

			if (Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].protocol_num_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
			{
				if (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX)
				{
					/* If the request is not a concurrent Functional TP request in parallel to a normal tester request, then request for a full communication mode */

					if((FALSE ==Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b) )
					{
							/* Get the request length in local variable */
							dataRequestLength_u16 = Dcm_DsldGlobal_st.dataRequestLength_u16;
							/* Check whether its not a functional tester present when the state machine is free*/
							if(!((adrRxBuffer_pu8[0] == DCM_DSLD_PARALLEL_TPR_BYTE1) && (adrRxBuffer_pu8[1] == DCM_DSLD_PARALLEL_TPR_BYTE2)&&(dataRequestLength_u16 == DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH) && (DcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID)))
							{
								/* Initialise the counter to zero, would be useful if ComM state is not already FULL-COMM */


    						/* Api to check whether ComM_Dcm_ActiveDiagnostic needs to be called or not*/
    						Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
    					}

    			}
    		}
    		else
    		{
    			/*Do nothing here*/
    		}
    	}
    	else
    	{
    		/* If the request is not a concurrent Functional TP request in parallel to a normal tester request, then request for a full communication mode */

    		if((FALSE == Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b) && (Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b == TRUE))
			{
				/* Initialise the counter to zero, would be useful if ComM state is not already FULL-COMM */

				/* Api to check whether ComM_Dcm_ActiveDiagnostic needs to be called or not*/
				Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId);
			}
    	}



    	/* Check if this positive indication is for "real" reception or "pseudo" reception */

    	if ( Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b == FALSE )
    	{
    		/* If the request is a functional TP request in parallel to an ongoing request being processed */

    		if(FALSE != Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b)
    		{
				/* Provide indication to application about functional tester present request */
				DcmAppl_DcmIndicationFuncTpr();
				/* S3 timer needs to be reset only if Dcm has finished processing first request and is currently free, i.e. S3 timer is running  */
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues
                 * When Function tester present is received the DSL state is referred only to reset S3 timer
                 * When there is a parallel update of DSL state machine still there is no functionality problems */
				if(((Dcm_DsldGlobal_st.stDslState_en==DSL_READY_FOR_RECEPTION) && (TRUE != Dcm_Prv_IsFuncTPOnOtherConnection_b)) || (Dcm_DsldGlobal_st.stDslState_en== DSL_ROETYPE1_RECIEVED))
				{
					Dcm_StartS3MaxMonitoring();
				}
				/* Reset the table indicating functional TP and table storing SID for NRC 0x21 */

				Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b = FALSE;
                /* Multicore: Locks are not needed here as this is a pseudo reception and the
                 * SID value stored for this RxPduId will not be accessed in Tx APIs parallely */
				Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 = 0xFFFF;
    		}
    		/* This indication is for the "pseudo" reception, check if NRC-21 needs to be triggered for this protocol */

    		else if ( Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE )
    		{
    			/* This is the indication of faking complete reception of the low-priority protocol, now trigger NRC-21 */
    			dataPduInfo_st.SduDataPtr = NULL_PTR;
    			dataPduInfo_st.SduLength = 3;
    			if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[dataConnectionId_u8].channel_idx_u8))
    			{
        			if(PduR_DcmTransmit(Dcm_DsldConnTable_pcst[dataConnectionId_u8].txpduid_num_u8, &dataPduInfo_st) != E_OK)
        			{
        				/* Reset the SID for the RX Pdu to 0xffff as this request will not be considered for processing */
                        /* Multicore: Locks are not needed here as the transmission is canceled by PduR and there cannot be a parallel Rx/Tx on this RxPduid */
                        /* Also this is a an atomic operation and hence no lock needed */
        	    		Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 = 0xFFFF;

						}
					}
					else
					{
						/*Nothing to be done*/
						/* Report development error "DCM_E_FULLCOMM_DISABLED " to DET module if the DET module is enabled */
						DCM_DET_ERROR(DCM_TPRXIND_ID , DCM_E_FULLCOMM_DISABLED )
					}
				}
				else
				{
					/* Do nothing */
				}
			}
			else
			{
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
				(void)DcmAppl_TpRxIndication(DcmRxPduId,Result);
#endif
				/* Reset the SID for the RX Pdu to 0xffff as this request will not be considered for processing */
				/* Multicore: Locks are not needed here as the request on this RxPduId is accepted for processing and in parallel no Rx/Tx can be active in parallel */
				/* Also this is a an atomic operation and hence no lock needed */
				Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 = 0xFFFF;

                /* Assign default value */

                isProcessRequest_b = TRUE;
				/* Get the request length in local variable */
				dataRequestLength_u16 = Dcm_DsldGlobal_st.dataRequestLength_u16;

			/* Since result is OK, Check for functional tester present request in buffer for UDS protocol */

			if((DcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID) && ((DCM_IS_KWPPROT_ACTIVE() == FALSE)&& (DCM_IS_KLINEPROT_ACTIVE()==FALSE)))
			{
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
				/* Update the request length if protocol is new protocol  */
				if(DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)
				{
					dataRequestLength_u16 = Dcm_DsldGlobal_st.dataNewdataRequestLength_u16;
				} /* if the rx pdu id is pass rx pdu id */
		#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
				else if(DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
				{
					dataRequestLength_u16 = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;

				}
		#endif
				else
				{
				/* Clearing MISRA warning */
				}
#endif

				/* Check the buffer content is 0x3e,0x80 and request length is 0x02 */
				if(((adrRxBuffer_pu8[0] == DCM_DSLD_PARALLEL_TPR_BYTE1) && (adrRxBuffer_pu8[1] == DCM_DSLD_PARALLEL_TPR_BYTE2)&&(dataRequestLength_u16 == DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH)))
				{
					/* Provide indication to application about functional tester present request */
					DcmAppl_DcmIndicationFuncTpr();
					/* Reset S3 timer only if request received is for running protocol else ignore */
					if(idxProtocol_u8 == Dcm_DsldGlobal_st.idxCurrentProtocol_u8)
					{
	#if(((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))&&(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF))
						if(DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
						{
                            /* Multicore: Code reaches here during protocol preemption and hence even if there are parallel modification
                              to this variable then there is no issues as a new request will start soon */
						    /* making sure the next state is not affected due to Provide Rx Buffer */
							Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
							/* Reseting the pass dataRxPduId_u8 */
							Dcm_DsldGlobal_st.dataPassRxPduId_u8 = 0xff;
                            /* Multicore: No lock needed here as Dsl state is an atomic operation */
                            /* DSL state machine handling ensures that there is no data consistency issues
                             * Once the DSL state is set to Receiving state, no parallel update possible*/
							if(Dcm_DsldGlobal_st.stDslState_en == DSL_RECEIVING)
							{
								Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;
								/* update the local variable with the proper state so that correct state will be updated in the global state variable before exiting from the function */
                                stDslState_en = DSL_READY_FOR_RECEPTION;

							}
							/* Request is tester present start S3 timer again */
							Dcm_StartS3MaxMonitoring();
						}
						else
	#endif
						{
							/* Request is tester present start S3 timer again */
							Dcm_StartS3MaxMonitoring();
							/* Ready for receiving the new request */
							stDslState_en = DSL_READY_FOR_RECEPTION;
						}
					}
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
					else
					{
						/* In case of parallel tester present. The nexRxPdudid has to be reset for two levels of*/
						/* protocol preemption */
						Dcm_DsldGlobal_st.dataNewRxPduId_u8 = 0xff;
					}
	#endif
					/* Ignore this request */

					isProcessRequest_b = FALSE;
				}
			}

			/* Take any physical and functional (except 3e 80) request */
			/*Check if teh Process Request is proceed*/
			if(isProcessRequest_b != FALSE)
			{
				/* DCM need to start P2 timer in Rx indication */
				/* If it is new UDS protocol then we need to start P2 timer with default P2 max  */
				/* If it is new KWP then we need to start P2 timer with P2 max from corresponding protocol */

	#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
			    /*If the Communication Protocol is Active */
				if((Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
		#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
				   && (DcmRxPduId != Dcm_DsldGlobal_st.dataNewRxPduId_u8)
		#endif
				)
				{
					/* Do nothing for consecutive requests */
				}
				else
				{
					/* Check if the new request has arrived on KWP protocol */
					if((Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8 & 0xF0u) == 0x80u)
					{
						/* Get the P2 max from default timing configuration structure  */
						/* This is required for the first request of KWP. For consecutive requests  "Dcm_DsldTimer_st.*/
						/* dataTimeoutP2max_u32" get updated in protocol activation and might be get modified by ATP service */
						idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;
                        /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                         * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */
						Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;
					}
					else
					{
						/* UDS is new protocol, Update P2 max */
                        /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                         * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */
						Dcm_DsldTimer_st.dataTimeoutP2max_u32 = DCM_CFG_DEFAULT_P2MAX_TIME;
					}
				}
	#else
		/* If protocol preemption is not enabled and KWP protocol is not present then only UDS protocol is present
		   So already the UDS P2 timing is updated during Initialization. As a result no need to load the time again */
		/* Also after transition from non default to default session, default P2 timer is loaded in Dcm_SetSesCtrlType API*/
		#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
				if(DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)
				{
					/* UDS is new protocol, Update P2 max */
                    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                     * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */
					Dcm_DsldTimer_st.dataTimeoutP2max_u32 = DCM_CFG_DEFAULT_P2MAX_TIME;
				}
		#endif
	#endif

	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
				if(DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)
				{
					/* Store the active tx pdu id number */
                    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                       there is no parallel writing due to DSL state machine handling */
					Dcm_DsldGlobal_st.dataOldtxPduId_u8 =
					Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;

					/* If ROE is under processing when this request was received, ROE has to be stopped*/
					/* Setting the Active TxPduId to invalid value */
					/*ROE is also active; stopping ROE transmission */
                    /* Multicore: Lock needed here to avoid reception of ROE/RDPI events when the DSL has already become free */
                    SchM_Enter_Dcm_Global_NoNest();
					Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = 0xff;
					Dcm_DsldGlobal_st.stDslPreemptionState_en = DSL_STOP_PROTOCOL;

                    /* Copy the old RxPdu to local variable for comparison */
                    dataActiveRxPduId_u8 = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

                    /* Update the active Rx and Tx pdu ids */
                    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                       there is no parallel writing due to DSL state machine handling */
                    Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
                    SchM_Exit_Dcm_Global_NoNest();

					/* Invoke ComM_Inactive Diagnosis  for the old protocol */
					if(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[DcmRxPduId]].channel_idx_u8].ComMChannelId != Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId)
					{
					ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[dataActiveRxPduId_u8]].channel_idx_u8].ComMChannelId);
					}

					/* make new rx pdu id invalid */
					Dcm_DsldGlobal_st.dataNewRxPduId_u8 = 0xff;
					#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
					/* make pass rx pdu id invalid */
					Dcm_DsldGlobal_st.dataPassRxPduId_u8 = 0xff;
					#endif
					/* Start P2 timer */
                    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                     * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */

					DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
								  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[idxProtocol_u8].dataP2TmrAdjust),
								   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
				}
				#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
				else if(DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
				{
					/* Store the active tx pdu id number */
                    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                       there is no parallel writing due to DSL state machine handling */
					Dcm_DsldGlobal_st.dataOldtxPduId_u8 =
					Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;
                    /* Multicore: No lock needed here as Dsl state is an atomic operation */
                    /* DSL state machine handling ensures that there is no data consistency issues */
                    /* ROE tx confirmation has not yet come; ROE is in processing. Stop Roe by moving */
                    /* Active tx pdu id to a invalid value 0xFF ; and setting the Dsl next state to DSL_STOP_ROE */
                    /* Multicore: Lock needed here to avoid reception of ROE/RDPI events when the DSL has already become free */
                    SchM_Enter_Dcm_Global_NoNest();
					if(Dcm_DsldGlobal_st.stDslState_en == DSL_RECEIVING)
					{
						stDslState_en = DSL_REQUEST_RECEIVED;
						/* Update the active Rx Pdu Id and the request length*/
						Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
						Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
						/* Reset the Pass rx pdu id variable */
						Dcm_DsldGlobal_st.dataPassRxPduId_u8 = 0xff;

					}
					else
					{
						/* ROE tx confirmation has not yet come; ROE is in processing. Stop Roe by moving */
						/* Active tx pdu id to a invalid value 0xFF ; and setting the Dsl next state to DSL_STOP_ROE */
						Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = 0xff;
						Dcm_DsldGlobal_st.stDslPreemptionState_en = DSL_STOP_ROE;
						Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;
						/* Update the active Rx Pdu Id */
                        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                           there is no parallel writing due to DSL state machine handling */
						Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
						Dcm_DsldGlobal_st.dataPassRxPduId_u8 = 0xff;

						/* After Stopping ROE , the Active service table has to be restored from the old Service Table */
						/* Change the service table to originally active table */
						if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
						{
							Dcm_DsldGlobal_st.datActiveSrvtable_u8  = Dcm_DsldGlobal_st.dataOldSrvtable_u8;
						}
						Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

					}
                    /* Multicore: Lock needed here to avoid reception of ROE/RDPI events when the DSL has already become free */
                    SchM_Exit_Dcm_Global_NoNest();
					/* Start P2 timer */

					DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
								  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
								   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
				}
				#endif
				else
				{
					/* If this call is for running protocol and there is no ROE event which is currently active
					on the arrived protocol, process the arrived request else stop the running protocol */
                    /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                       there is no parallel writing due to DSL state machine handling */
					if(DcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
					{
						stDslState_en = DSL_REQUEST_RECEIVED;
						/* Start P2 timer */
	                    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
	                     * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */

						DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
									  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
									   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
					}
				}
	#else
				/* If this call is for running protocol and there is no ROE event which is currently active
				on the arrived protocol, process the arrived request else stop the running protocol */
                /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                   there is no parallel writing due to DSL state machine handling */
				if(DcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
				{
							/* updating the buffer pointer with the address which has the request to be processed. This buffer is used for further processing of the request.  */
	#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
							Dcm_DsldGlobal_st.adrBufferPtr_pu8 = Dcm_DslDsdRxPduArray_ast[DcmRxPduId].adrBufferPtr_pu8;
	#endif
						stDslState_en = DSL_REQUEST_RECEIVED;
						/* Start P2 timer */
						/* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
                     * where P2, P3 and P2Star is involved, this is case where only P2max_u32 is being accessed */

					DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
								  (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
								   Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
				}
	#endif
			}
    	}

    }
		else
		{
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
			/* Negative Rx indication is received */
			if ( Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b!= FALSE )
			{
				(void)DcmAppl_TpRxIndication(DcmRxPduId,Result);
			}
#endif

			/* Reset both Sid and Concurrent Tester Present flag for this Rx Pdu Id  */

			Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b  = FALSE;
        /* Multicore: Locks are not needed here as the request on this RxPduId is not accepted for processing and in parallel no Rx/Tx can be active in parallel */
        /* Also this is a an atomic operation and hence no lock needed */
		Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16   = 0xFFFF;

        /* check this indication came for receiving request or discarded request in provide_rxbuffer() */
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
           there is no parallel writing due to DSL state machine handling */
        if((Dcm_DsldGlobal_st.dataActiveRxPduId_u8 == DcmRxPduId) && (stDslState_en == DSL_RECEIVING))
        {
            /* error found discard the request, reset DSL state */
            stDslState_en = DSL_READY_FOR_RECEPTION;

            /* restart S3 timer */
            Dcm_StartS3MaxMonitoring();
        }


#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        /* Error full reception of high priority protocol. Ignore the new Rx pdu id */
        if(DcmRxPduId == Dcm_DsldGlobal_st.dataNewRxPduId_u8)
        {
            Dcm_DsldGlobal_st.dataNewRxPduId_u8 = 0xff;
            /*Update the pre-emption state to default state, since the request is not fully received,
             *  no pre-emption can occur now because request is not fully revceived*/
            Dcm_DsldGlobal_st.stDslPreemptionState_en=DSL_READY_FOR_RECEPTION;
        }
    #if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        /* Error full reception of high priority request. Ignore the pass Rx pdu id */
        if(DcmRxPduId == Dcm_DsldGlobal_st.dataPassRxPduId_u8)
        {
            Dcm_DsldGlobal_st.dataPassRxPduId_u8 = 0xff;

            /* error found discard the request, reset DSL state */
            stDslState_en = DSL_READY_FOR_RECEPTION;
            /* If ROE TxConfirmation has come; then the DSL state would be changes to RECEIVING.. */
            /* In case of Discarded RxIndication; The DSL next State has to be reset back to READY FOR RECEPTION */
            if(stDslState_en != DSL_RECEIVING)
            {
                Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
            }

            /* restart S3 timer */
            Dcm_StartS3MaxMonitoring();
        }
    #endif
#endif
    }
    /* reload the DSL state variable */
    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */

    Dcm_DsldGlobal_st.stDslState_en = stDslState_en;

	#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    }
    /* if the Rx indication is for the queued request */
    else
    {
    	SchM_Enter_Dcm_Global_NoNest();
		if((Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_RUNNING)&&(Dcm_DsldGlobal_st.stDslState_en!=DSL_READY_FOR_RECEPTION))
		{
			if(E_OK != Result)
			{
				/* Connection on which request is received */
				dataConnectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];
				/* protocol of the received Rx pdu id */
				idxProtocol_u8 = Dcm_DsldConnTable_pcst[dataConnectionId_u8].protocol_num_u8;
				/* to switch the buffer back as the Rx indication is negative */
				(void)Dcm_ProvideFreeBuffer(idxProtocol_u8,TRUE);
				Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
			}
			else
			{
				Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_COMPLETED;
				/* queing of the second request is completed */
			}
		}
        SchM_Exit_Dcm_Global_NoNest();
    }
#endif

    }

    else
    {
        // Set Det Error
        DCM_DET_ERROR( DCM_TPRXINDICATION_ID ,DCM_E_DCMRXPDUID_RANGE_EXCEED)
    }

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

