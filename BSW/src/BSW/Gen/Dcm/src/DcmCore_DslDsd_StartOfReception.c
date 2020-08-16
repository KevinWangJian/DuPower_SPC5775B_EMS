

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DslDsdRxPduArray_tst,DCM_VAR)Dcm_DslDsdRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean , DCM_VAR)Dcm_Prv_IsFuncTPOnOtherConnection_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Variable if set to TRUE denotes active Rx on OBD_ON_CAN during Rx Pdu sharing use case*/
VAR (boolean,DCM_VAR) Dcm_DsldObdReqIndn_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/* FC_VariationPoint_END */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *********************************************************************************************************************
 * Dcm_DslDsd_CheckForFuncTpr : This call-back function is invoked to check if request received is a Concurrent
 *                              Tester Present (Functional 3E 80) or not
 *
 * \param           DcmRxPduId (in): Pdu Id corresponding to the received Pdu
 *                  info       (in): PduInfo structure
 *                  TpSduLength (in): Total message length of the request to be received
 *
 * \retval         boolean:
 *                  TRUE : Request received is a Concurrent Tester Present (Functional 3E 80)
 *                  FALSE: Request received is not a Concurrent Tester Present (Functional 3E 80)
 *
 *
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */
static FUNC(boolean,DCM_CODE) Dcm_DslDsd_CheckForFuncTpr( VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
        VAR(PduLengthType, AUTOMATIC) TpSduLength);
static FUNC(boolean,DCM_CODE) Dcm_DslDsd_CheckForFuncTpr( VAR(PduIdType, AUTOMATIC) DcmRxPduId,
        P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
        VAR(PduLengthType, AUTOMATIC) TpSduLength)
{
    VAR(boolean, AUTOMATIC) retVal_b;
    /*Reset the return value to false*/
    retVal_b = FALSE;

   if(info !=NULL_PTR)
   {
       if((DcmRxPduId          >= DCM_INDEX_FUNC_RX_PDUID)                     &&    \
               (TpSduLength         == DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH)   &&    \
               (info->SduDataPtr[0] == DCM_DSLD_PARALLEL_TPR_BYTE1)            &&    \
               (info->SduDataPtr[1] == DCM_DSLD_PARALLEL_TPR_BYTE2))
       {
           /*Set the return value to true*/
           retVal_b = TRUE;
       }
   }

    return(retVal_b);
}

/* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
/**
 *********************************************************************************************************************
 * Dcm_IsSharedRxPdu : Used to chk if the received PDU is Shared or not
 *
 *
 * \param           DcmRxPduId (inout): Pdu Id corresponding to the received Pdu
 *                  info       (inout): PduInfo structure
 *                  RxBufferSizePtr (inout): Used for DLC length check in case of shared Rx PDU
 *                  dataIsshared_b (out) : If this parameter is set to true, it indicates the Rx PDU is shared
 *                                         and received over functional OBD, if not the request  received is over UDS
 *
 * \retval         boolean:
 *                  E_OK        : Return type is relevant only for shared RX PDU, if E_OK shared Rx PDU received is valid
 *                  E_NOT_OK    : Return type is relevant only for shared RX PDU, if E_NOT_OK shared Rx PDU received is not valid
 *
 *
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_IsSharedRxPdu
            (
                P2VAR(PduIdType, AUTOMATIC, DCM_APPL_DATA) DcmRxPduId,
                /* MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const' */
                P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
                P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) dataIsshared_b
            )
{
    /*local variables to hold connection ID and FLAG status*/
    VAR(Std_ReturnType, AUTOMATIC) dataSharedPdu;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(uint8,AUTOMATIC) dataConnectionId_u8;

    dataSharedPdu=E_NOT_OK;
    /*Indicate its a shared PDU*/
    *dataIsshared_b=FALSE;

    /* Check if the Rx Pdu is in the valid range AND Received Rx Pdu is shared AND
    Data length of request is 8 for OBD AND SID is in the OBD SID range 0x1 - 0xA */
    if((*DcmRxPduId < (DCM_CFG_NUM_RX_PDUID-1u)) && (*DcmRxPduId == DCM_CFG_SHARED_RX_PDUID)    &&          \
       ((info->SduDataPtr[0] > 0x0) && (info->SduDataPtr[0] < 0xB)))
    {
        /*Indicate its a shared PDU*/
        *dataIsshared_b=TRUE;
        /* Find the Connection on which request was received */
        dataConnectionId_u8 = Dcm_DsldRxTable_pcu8[DCM_CFG_NUM_RX_PDUID-1u];

        /* Find the Protocol of the received Rx pdu id */
        idxProtocol_u8 = Dcm_DsldConnTable_pcst[dataConnectionId_u8].protocol_num_u8;

        /*check whether request was received for DCM_OBD_ON_CAN OR DCM_OBD_ON_FLEX protocol*/
        if((Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8  == DCM_OBD_ON_CAN)         ||    \
                (Dcm_DsldProtocol_pcst[idxProtocol_u8].protocolid_u8  == DCM_OBD_ON_FLEXRAY))
        {
            /* Assign the last RxPdu for further processing as the
           generated code use the last Rx Pdu for OBD_ON_CAN */
            *DcmRxPduId = (DCM_CFG_NUM_RX_PDUID-1u);
            dataSharedPdu=E_OK;
        }
    }

    return dataSharedPdu;
}
#endif
/* FC_VariationPoint_END */

/**
 *********************************************************************************************************************
 * Dcm_StartOfReception : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * start of reception (i.e. receiving a Single Frame or First Frame indication)
 *
 * \param           DcmRxPduId (in): Pdu Id corresponding to the received Pdu
 *                  TpSduLength (in): Total message length of the request to be received
 *                  RxBufferSizePtr (out): Dcm shall need to fill in the buffer capability while providing BUFREQ_OK
 *
 * \retval          BufReq_ReturnType:
 *                  BUFREQ_E_NOT_OK - Dcm does not intend to receive this request
 *                  BUFREQ_OK - Dcm can process this request, requesting CanTp/FrTp via PduR to trigger Dcm_CopyRxData
 *                  BUFREQ_E_OVFL - Available buffer with Dcm is less than requested buffer to receive this request
 *
 *
 * \seealso
 * \usedresources
 *********************************************************************************************************************
 */
/*MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter 'PduInfoPtr' is not modified and so the pointer could be of type 'pointer to const'. MISRA C:2012 Rule-8.13*/

FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception
        (
                VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                /* MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter '%s' is not modified and so the pointer could be of type 'pointer to const' */
                P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
                VAR(PduLengthType, AUTOMATIC) TpSduLength,
                P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
        )
{
    VAR(BufReq_ReturnType,AUTOMATIC) dataReturnValue_en;
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(uint8,AUTOMATIC) dataConnectionId_u8;
    P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrProtocolTable_pcst;
    /* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
    /* Local variable to handle the OBD request during Rx Pdu sharing use case */
    VAR(boolean,AUTOMATIC) dataIsShared_b;
    VAR(Std_ReturnType,AUTOMATIC) dataObdReqInd;
    /*Initialize the dataIsShared value to false */
    dataIsShared_b = FALSE;
    dataObdReqInd  = E_NOT_OK;
#endif

    /* FC_VariationPoint_END */

    /* Initialise the return value */
    dataReturnValue_en = BUFREQ_E_NOT_OK;
#if((DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)||(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF))
	if (info == NULL_PTR)
	{
		dataReturnValue_en = BUFREQ_E_NOT_OK;
	    DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_PARAM_POINTER );
	}
	else
#endif
	{
		if(DcmRxPduId<DCM_CFG_NUM_RX_PDUID)
		{
				/*If Dcm is initialise and request is accept*/
				if((Dcm_isInitialised_b!=FALSE) && (Dcm_acceptRequests_b !=FALSE))
				{
					/* FC_VariationPoint_START */
	#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
					/*Check if the received PDU is Shared between OBD and Physical functional IDs*/
					dataObdReqInd=Dcm_IsSharedRxPdu(&DcmRxPduId,info,&dataIsShared_b);

					if(((dataIsShared_b!=FALSE) && (dataObdReqInd==E_OK))||(dataIsShared_b==FALSE))
	#endif
						/* FC_VariationPoint_END */
					{
						/* Find the Connection on which request was received */
						dataConnectionId_u8 = Dcm_DsldRxTable_pcu8[DcmRxPduId];

						/* Find the Protocol of the received Rx pdu id */
						idxProtocol_u8 = Dcm_DsldConnTable_pcst[dataConnectionId_u8].protocol_num_u8;

						/* Get the pointer of protocol table */
						adrProtocolTable_pcst = &Dcm_DsldProtocol_pcst[idxProtocol_u8];

						/* Check the ComM state is No communication mode, range of Rx pdu id and check if protocol is available in current configuration */
						if((DCM_CHKNOCOMM_MODE(Dcm_DsldConnTable_pcst[dataConnectionId_u8].channel_idx_u8)) && (DcmRxPduId < DCM_CFG_NUM_RX_PDUID)
	#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
								&&
								(((adrProtocolTable_pcst->Config_Mask) & (Dcm_ActiveConfiguration_u8)) != 0)
	#endif
						)
						{
							/* Initialise both CopyRxData and SId for this Rx Pdu Id which is received */

							Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b = FALSE;
							/* Multicore: Locks are not needed here as the SID value is per RxPduId and there cannot be parallel Rx/Tx for this RxPduId */
							/* No lock is necessary for Dcm_DsldSId_u16 as this is a write operation and is atomic
							 * Also as the new request cannot be received on the same RxPduId till the transmission is complete,
							 * there are no chances of parallel write and hence no locks.
							 */
							Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldSId_u16 = 0xFFFF;
							/* Check if the TpSduLength is zero or not*/
							if(TpSduLength!=0u)
							{
								/* Check for Permission from Application to process/reject this request */
								if (DcmAppl_DcmGetRxPermission(adrProtocolTable_pcst->protocolid_u8,DcmRxPduId,info,TpSduLength) == E_OK)
								{
									Dcm_Prv_IsFuncTPOnOtherConnection_b = FALSE;
									/*check whether current request is FuncTP and it is arrived on connection other than current connection */
									if( (FALSE!=Dcm_DslDsd_CheckForFuncTpr(DcmRxPduId,info,TpSduLength)) && (Dcm_DsldGlobal_st.nrActiveConn_u8 != dataConnectionId_u8) )
									{
										Dcm_Prv_IsFuncTPOnOtherConnection_b = TRUE;
									}
									/* If Dcm is currently waiting for request and if either active session is DEFAULT_SESSION or if the
									received request is from the active connection, Buffer can be provided without any further checks */
									if(((Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX)
											||(Dcm_DsldGlobal_st.nrActiveConn_u8 == dataConnectionId_u8)))
									{
										/* Check the size of rx buffer against request length*/
										if((uint32)TpSduLength <= Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32 )
										{
											VAR (boolean, AUTOMATIC) processReq_b;
											/*initialize the process request flag to false*/
											processReq_b = FALSE;
											/* Interrupt locks added to protect updation of the state variables in case of new request is being processed */
											SchM_Enter_Dcm_Global_NoNest();



											if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION) && (TRUE != Dcm_Prv_IsFuncTPOnOtherConnection_b)
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
													&&      \
													((Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL_RECEIVING) && (Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL))
	#endif
													)
											{

													/* DSL is ready for accept the request */
													Dcm_DsldGlobal_st.stDslState_en = DSL_RECEIVING;

													/* if request comes on other protocol in default session start the new protocol again */
													if(Dcm_DsldGlobal_st.idxCurrentProtocol_u8 != idxProtocol_u8)
													{
														/*Communication protocl active status is set to false*/
														Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
													}
													/* store the rx pdu id and request length and channel id*/
													Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
													Dcm_DsldGlobal_st.nrActiveConn_u8      = dataConnectionId_u8;
													/* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
													   there is no parallel writing due to DSL state machine handling */
													Dcm_DsldGlobal_st.dataActiveRxPduId_u8   = DcmRxPduId;
													Dcm_DsldGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].txpduid_num_u8;
													Dcm_DsldGlobal_st.dataRequestLength_u16  = TpSduLength;
													/*Initialize the CopyRxData value to true*/
													Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b = TRUE;

													dataReturnValue_en = BUFREQ_OK;
											}
											else
											{
												/*Set the process request flag value to true*/
												processReq_b = TRUE;
											}
											SchM_Exit_Dcm_Global_NoNest();
											/*Check if process request flag is set to false*/
											if(processReq_b==FALSE)
											{
												Dcm_DsldResetCopyRxDataStatus(DcmRxPduId);
											}
											else
											{
												/* Check if the new request is a Functional Tester Present request */
												if(FALSE!=Dcm_DslDsd_CheckForFuncTpr(DcmRxPduId,info,TpSduLength))
												{
													/* If the Functional TP request is on the active or different connection */

													Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b = TRUE;
													dataReturnValue_en = BUFREQ_OK;
												}

	#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
											/* If ROE or RDPI is enabled and protocol preemption is enabled,
									If ROE/RDPI event is active call the function for ROE handling */
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
													/* Multicore: No lock needed here as Dsl state is an atomic operation */
													/* DSL state machine handling ensures that there is no data consistency issues */
												else if((Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)&&
														(Dcm_DsldProtocol_pcst[idxProtocol_u8].premption_level_u8 ==
																Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].premption_level_u8))
												{
													/* Check for high priority request on persistent ROE*/
													dataReturnValue_en = Dcm_DsldPersistentRoeHandling_en(adrProtocolTable_pcst,TpSduLength,DcmRxPduId);
													/*Check if data return value is 0x01 and NRC-21 protocol is received and rejected during pre-emption assertion*/
													if ( ( dataReturnValue_en == BUFREQ_E_NOT_OK ) && ( Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE ) )
													{
														/* Set the dataReturnValue_en as BUFREQ_OK in order to know the SID which is required to send NRC21,
														 * Dcm has decided to ignore this lower priority request as high priority ROE is under processing */
														dataReturnValue_en = BUFREQ_OK;
													}
												}
												/* If ROE or RDPI is enabled and protocol preemption is disabled,
										If ROE/RDPI event is active when new request is received, restart S3 Timer and reject new request */
	#else
												/* Multicore: No lock needed here as Dsl state is an atomic operation */
												/* DSL state machine handling ensures that there is no data consistency issues
												 * Once the DSL state is set to DSL_ROETYPE1_RECIEVED state, no parallel update possible */
												else if((Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)&&
														(Dcm_DsldGlobal_st.nrActiveConn_u8 == dataConnectionId_u8))
												{
													/* ROE type1 request under processing and tester request comes. Reset S3 timer */
													Dcm_StartS3MaxMonitoring();
													/* But the request is still ignored as the dataReturnValue_en is not altered yet */
													/*If NRC-21 protocol is received and rejected during pre-emption assertion*/
													if(Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE )
													{
														dataReturnValue_en = BUFREQ_OK;
													}
													else
													{
														/* Ignore the request */
														dataReturnValue_en = BUFREQ_E_NOT_OK;
													}
												}
	#endif
	#endif
												else
												{
													if(Dcm_DsldGlobal_st.nrActiveConn_u8 != dataConnectionId_u8)
													{
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
														/* If the request is received on the same connection then the request can be ignored
												   and even NRC 0x21 should not be triggered. This case occurs when a request is received
												   on active connection on different Rx Pdu */

														/* Check for high priority request */
														dataReturnValue_en = Dcm_DsldPremptionHandling_u8(adrProtocolTable_pcst,TpSduLength,DcmRxPduId);

	#else
														/* dataReturnValue_en for this use-case is already updated at the top of this function */
														/* If the active protocol is different from current protocol and NRC 21 is supported */

														if(Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE )
														{
															dataReturnValue_en = BUFREQ_OK;
														}
														else
														{
															/* Ignore the request */
															dataReturnValue_en = BUFREQ_E_NOT_OK;
														}
	#endif
													}
												}
											}

										}
										else
										{
											/* Dcm buffer is not sufficient to receive the received request */
											dataReturnValue_en = BUFREQ_E_OVFL;
										}
									}
									else
									{
										/* Received connection isn't the active connection and also active session isn't the default, hence
										this is the classic case of applying the "complex" protocol preemption logic */

										/* The below code snippet is reached if Functional TP request comes in non default session and not on the active connection */
										/* If the request is a Functional TP request and Busy Repeat request feature is enabled for the protocol */
										if(FALSE!=Dcm_DslDsd_CheckForFuncTpr(DcmRxPduId,info,TpSduLength))
										{
											/* Set the variable to TRUE to indicate a Func TP request received in parallel to another request */

											Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldFuncTp_b = TRUE;
											dataReturnValue_en = BUFREQ_OK;
										}
										else
										{
	#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
											/* Handle protocol preemption in non default session */
											dataReturnValue_en = Dcm_DsldPremptionHandling_u8(adrProtocolTable_pcst,TpSduLength,DcmRxPduId);
	#else
											/* If NRC-21 protocol is received and rejected during pre-emption assertion*/
											if(Dcm_DsldProtocol_pcst[idxProtocol_u8].nrc21_b != FALSE )
											{
												dataReturnValue_en = BUFREQ_OK;
											}
											else
											{
												/* Ignore the request */
												dataReturnValue_en = BUFREQ_E_NOT_OK;
											}
	#endif
										}
									}

									if(NULL_PTR!=RxBufferSizePtr)
									{
										if(dataReturnValue_en == BUFREQ_OK)
										{
											/* At this stage of the execution if dataReturnValue_en is BUFREQ_OK, then Dcm has decided to process this
									request. As Dcm needs to always receive the request in full, update Buffer capability as requested */
											*(RxBufferSizePtr) = (uint16)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
											/*If the CopyRxData value is supported*/
											if (Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b != FALSE )
											{
												/* Store the length of the total to be received request into Rx Pdu Info struct,
										and the same shall be decremented with every call of Dcm_CopyRxData */
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength = TpSduLength;
													/* Store the corresponding protocol buffer pointer in case of normal protocol */
	#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].adrBufferPtr_pu8 = Dcm_ProvideFreeBuffer(idxProtocol_u8,FALSE);
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduDataPtr = Dcm_DslDsdRxPduArray_ast[DcmRxPduId].adrBufferPtr_pu8;
	#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
												(void)DcmAppl_StartOfReception(info->SduDataPtr[0],DcmRxPduId,TpSduLength,(uint32)(Dcm_DslDsdRxPduArray_ast[DcmRxPduId].adrBufferPtr_pu8));
	#endif
	#else
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduDataPtr = adrProtocolTable_pcst->rx_buffer1_pa;
	#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
												(void)DcmAppl_StartOfReception(info->SduDataPtr[0],DcmRxPduId,TpSduLength,(uint32)(adrProtocolTable_pcst->rx_buffer1_pa));
	#endif
	#endif
											}
											/* FC_VariationPoint_START */
	#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
											/* If the request processed is a request on OBD_ON_CAN */

											if((dataIsShared_b==TRUE)&&(dataObdReqInd==E_OK))
											{   /* Set the variable to denote that Rx on protocol OBD_ON_CAN is active */

												Dcm_DsldObdReqIndn_b = TRUE;
											}
	#endif
											/* FC_VariationPoint_END */
										}
	#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
										/* Dcm will not queue second request untill first request is fully received (Until positive Dcm_TpRxIndication for the first request is received) */
										else if((dataReturnValue_en!=BUFREQ_E_OVFL) && (Dcm_DsldGlobal_st.nrActiveConn_u8 == dataConnectionId_u8) && (Dcm_DsldGlobal_st.stDslState_en != DSL_RECEIVING))
										{
											SchM_Enter_Dcm_Global_NoNest();
											/* Beginning of Queuing */
											if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE)
											{
												/* copy the buffer address into the queue buffer pointer */
												Dcm_QueueStructure_st.adrBufferPtr_pu8 = Dcm_ProvideFreeBuffer(idxProtocol_u8,TRUE);
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduDataPtr = Dcm_QueueStructure_st.adrBufferPtr_pu8;
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldRxPduBuffer_st.SduLength = TpSduLength;
												Dcm_DslDsdRxPduArray_ast[DcmRxPduId].Dcm_DsldCopyRxData_b = TRUE;
												/* Application should not be called for copying the data while being queuing the request */
												Dcm_QueueStructure_st.dataQueueReqLength_u16 = TpSduLength;
												Dcm_QueueStructure_st.dataQueueRxPduId_u8 = DcmRxPduId;
												*(RxBufferSizePtr) = (uint16)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
												/* set the flag to indicate that the first buffer is busy */
												/* To indicate that the Queueing of the next request on the same connection has started on buffer 0*/
												Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_RUNNING;
												dataReturnValue_en = BUFREQ_OK;
											}
											else
											{
												/* return not ok as both the buffers in Dcm are occupied */
												dataReturnValue_en = BUFREQ_E_NOT_OK;
											}
											SchM_Exit_Dcm_Global_NoNest();
										}
	#endif
										else
										{
											/* dummy else */
										}
								}
								else
								{
									dataReturnValue_en = BUFREQ_E_NOT_OK;
									//Set DET Error NULL_PTR
									DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_PARAM_POINTER )
								}
							}
							else
							{
								/* Request is not accepted by Application, dataReturnValue_en is already set to the required value */
							}
						}
							else
							{
								if(NULL_PTR!=RxBufferSizePtr)
								{
									/* If the SduLength is zero in the request, then the entire available Rx buffer size shall be returned. */
									*(RxBufferSizePtr) = (uint16)(Dcm_DsldProtocol_pcst[idxProtocol_u8].rx_buffer_size_u32);
									dataReturnValue_en = BUFREQ_OK;
								}
								else
								{
									dataReturnValue_en = BUFREQ_E_NOT_OK;
									//Set DET Error NULL_PTR
									DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID , DCM_E_PARAM_POINTER )
								}
							}
						}
						else
						{
							/* Either RxPdu is out of range, or Dcm is not in the state to accept this request, dataReturnValue_en is already initialised to the required value */
						}
					}
				}
				else
				{
					/* Dcm is not initialised.DataReturnValue_en is already initialised to the required value */
				}
		}
		else
		{           //Set DET Error Range Exceed
				DCM_DET_ERROR(DCM_STARTOFRECEPTION_ID ,  DCM_E_DCMRXPDUID_RANGE_EXCEED )
		}
	}	
    return (dataReturnValue_en);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

