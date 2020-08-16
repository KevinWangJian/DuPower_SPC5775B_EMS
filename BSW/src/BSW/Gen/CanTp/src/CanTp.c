

#include "CanTp.h" /* TRACE[SWS_CanTp_00221] */
#include "CanTp_Cbk.h"
#include "CanTp_Prv.h" /* TRACE[SWS_CanTp_00156] Indirect inclusion CanTp_Cfg.h[through CanTp.h] SchM_CanTp.h Det.h */

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"
/* TRACE[SWS_CanTp_00253][SWS_CanTp_00168]TRACE[SWS_CanTp_00161] Defined as global variable available for debugging */
uint8 CanTp_MainState;

#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

#if(CANTP_VERSION_INFO_API == STD_ON)
/***********************************************************************************************************************
 Function name    : CanTp_GetVersionInfo
 Syntax           : CanTp_GetVersionInfo(versioninfo)
 Description      : TRACE[SWS_CanTp_00210] This function returns the version information of the CanTp module.
 Parameter        : Std_VersionInfoType* versioninfo
 Return value     : None
***********************************************************************************************************************/
void CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo)
{   /* TRACE[SWS_CanTp_00031][SWS_CanTp_00319] */
    if(versioninfo == NULL_PTR)
    {
        CanTp_Prv_ReportRunTimeError(CANTP_GETVERSIONINFO, CANTP_E_PARAM_POINTER);
    }
    else
    { /* TRACE[SWS_CanTp_00267] */
        versioninfo->vendorID            = CANTP_VENDOR_ID;
        versioninfo->moduleID            = CANTP_MODULE_ID;
        versioninfo->sw_major_version    = CANTP_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version    = CANTP_SW_MINOR_VERSION;
        versioninfo->sw_patch_version    = CANTP_SW_PATCH_VERSION;
    }
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_Init
 Syntax           : CanTp_Init(CfgPtr)
 Description      : TRACE[SWS_CanTp_00208] This function initializes the CanTp module.
 Parameter        : const CanTp_ConfigType*
 Return value     : None
***********************************************************************************************************************/
void CanTp_Init(const CanTp_ConfigType *CfgPtr)
{
    CanTp_MainState = CANTP_OFF; /* TRACE[SWS_CanTp_00027] */

    #if(CANTP_VARIANT == CANTP_PRE_COMPILE)
    CanTp_CfgPtr = &CanTp_Config;
    (void)CfgPtr;
	#else
    CanTp_CfgPtr = CfgPtr; /* TRACE[SWS_CanTp_00169] */

    if(CfgPtr == NULL_PTR)
    {
        CanTp_Prv_ReportRunTimeError(CANTP_INIT, CANTP_E_PARAM_POINTER);
    }
    #if((CANTP_DEV_ERROR_DETECT == CANTP_ON) && (CANTP_VARIANT == CANTP_POST_BUILD_SELECTABLE))
    else if(CanTp_Prv_PbCfgCheck(CfgPtr) != E_OK)
    {
        CanTp_Prv_ReportError(CANTP_INIT, CANTP_E_INIT_FAILED);
    }
    #endif
    else
    #endif
    {   /* TRACE[SWS_CanTp_00030][SWS_CanTp_00111][SWS_CanTp_00273] */
        CanTp_Prv_RxParamInit(); /* This is required for Change Parameter Api usecase.  */
        CanTp_Prv_QInit(); /* Burst Mode initialization  */
        /* Initialize all the channels to Idle  */
		CanTp_Prv_ArrayInit(&CanTp_SubState[0], CanTp_CfgPtr->NumberOfChannels, CANTP_IDLE);
        CanTp_Prv_ArrayInit(&CanTp_TxConfirmationChannel[0], CanTp_CfgPtr->NumberOfTxPdus, CANTP_INVALID_CHANNEL);

		CanTp_MainState = CANTP_ON; /* TRACE[SWS_CanTp_00027][SWS_CanTp_00170] */
    }
}

#if(CANTP_CANTPLITE_SUPPORT != STD_ON)
/***********************************************************************************************************************
 Function name    : CanTp_Shutdown
 Syntax           : CanTp_Shutdown()
 Description      : TRACE[SWS_CanTp_00211] This function is called to shutdown the CanTp module.
 Parameter        : None
 Return value     : None
***********************************************************************************************************************/
void CanTp_Shutdown(void)
{
    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_MainState != CANTP_ON)
    { /* TRACE[SWS_CanTp_00031] */
        CanTp_Prv_ReportError(CANTP_SHUTDOWN, CANTP_E_UNINIT);
    }
    else
    #endif
    { /* TRACE[SWS_CanTp_00010][SWS_CanTp_00202][SWS_CanTp_00200] */
        CanTp_MainState = CANTP_OFF;
        CanTp_Prv_RxParamInit();
        CanTp_Prv_QInit(); /* DeInitialize the Burst Q */
        /* Initialize all the channels to Idle state. */
        CanTp_Prv_ArrayInit(&CanTp_SubState[0], CanTp_CfgPtr->NumberOfChannels, CANTP_IDLE);
        CanTp_Prv_ArrayInit(&CanTp_TxConfirmationChannel[0], CanTp_CfgPtr->NumberOfTxPdus, CANTP_INVALID_CHANNEL);
        CanTp_CfgPtr = NULL_PTR;
    }
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_MainFunction
 Syntax           : CanTp_MainFunction()
 Description      : TRACE[SWS_CanTp_00213][SWS_CanTp_00164] CanTp scheduled functions which is called by the
                    BSW sheduler in a cyclic interval defined by the configuration parameter CanTp_MainFunctionPeriod.
                    Carries out all the routine job w.r.t. Timeout handling functionality of the CanTp when the OS is
                    running.
 Parameter        : None
 Return value     : None
***********************************************************************************************************************/
void CanTp_MainFunction(void)
{
    CanTp_ChannelIdType ChannelId;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_MainState != CANTP_ON)
    {/* TRACE[SWS_CanTp_00031] */
        CanTp_Prv_ReportError(CANTP_MAINFUNCTION, CANTP_E_UNINIT);
    }
    else
    #endif
    {
        #if(CANTP_TX_BURST_MODE == CANTP_ON)
        if(CanTp_Prv_GetFromQ(&ChannelId) == E_OK)
        {   /* This Action was put in queue either in TxConfirmaton or RxIndication. */
            CanTp_Prv_ExecuteState(ChannelId);
        }
        else
        #endif
        {   /* Execute the states of all the non-burst channels. */
            for(ChannelId = 0; ChannelId < CanTp_CfgPtr->NumberOfChannels; ChannelId++)
            {
                CanTp_Prv_ExecuteState(ChannelId);
            }

            CanTp_IncrementCounter();
        }
    }
}

#if(CANTP_CHANGE_PARAMETER_API == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_ChangeParameter
 Syntax           : CanTp_ChangeParameter(id, parameter, value)
 Description      : TRACE[SWS_CanTp_00302][SWS_CanTp_00091]This service is used to change the current value of reception
                    parameters BS and STmin for a specified RxNSdu.
 Parameter        : PduIdType, TPParameterType, uint16
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
	CanTp_ChannelIdType ChannelId;
    Std_ReturnType RetVal = E_NOT_OK; /* TRACE[SWS_CanTp_00294][SWS_CanTp_00304] */

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
	if(CanTp_Prv_IsNoDevError(id, CANTP_CHANGEPARAMETER, CANTP_E_INVALID_RX_ID))
	#endif
	{   /* Runtime error check: returns error if wrong Parameter or wrong range of parameter values for STMin or BS. */
		if(CanTp_Prv_IsChangeParameterOk(parameter, value))
		{
            ChannelId = CanTp_Prv_GetRxChannelId(id);

            SchM_Enter_CanTp_EXCLUSIVE_AREA();

			if(CanTp_Prv_GetState(ChannelId) == CANTP_RECEPTION)
			{   /* TRACE[SWS_CanTp_00303] */
				CanTp_Prv_ReportRunTimeError(CANTP_CHANGEPARAMETER, CANTP_E_OPER_NOT_SUPPORTED);
			}
			else
			{   /* Made sure that value is within 0xFF in Det-CANTP_E_PARAM_CONFIG. So typecasting done here is okay. */
				CanTp_ParamPair[id].Param[(parameter == TP_STMIN) ? 0 : 1] = (uint8)value;
				RetVal=E_OK;
			}

            SchM_Exit_CanTp_EXCLUSIVE_AREA();
		}
	}

    return RetVal;
}
#endif

#if(CANTP_READ_PARAMETER_API == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_ReadParameter
 Syntax           : CanTp_ReadParameter(id, parameter, value)
 Description      : TRACE[SWS_CanTp_00323] This service is used to read the current value of reception parameters BS and
                    STmin for a specified N-SDU.
 Parameter        : PduIdType, TPParameterType, uint16
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16 *value)
{
    Std_ReturnType RetVal = E_NOT_OK; /* TRACE[SWS_CanTp_00294] */

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(id, CANTP_READPARAMETER, CANTP_E_INVALID_RX_ID))
	#endif
	{
		if(value == NULL_PTR)
        {
		    CanTp_Prv_ReportRunTimeError(CANTP_READPARAMETER, CANTP_E_PARAM_POINTER);
        }
        else if((parameter != TP_BS) && (parameter != TP_STMIN))
        { /* TRACE[SWS_CanTp_00324] */
            CanTp_Prv_ReportRunTimeError(CANTP_READPARAMETER, CANTP_E_PARAM_ID);
        }
        else
		{
			*value = CanTp_Prv_GetRxParam(id, parameter); /* Read configuration values from Flash/RAM.  */
			RetVal = E_OK;
		}
	}

    return(RetVal);
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_Transmit
 Syntax           : CanTp_Transmit(CanTpTxSduId, CanTpTxInfoPtr)
 Description      : TRACE[SWS_CanTp_00212][SWS_CanTp_00176] Asyncrounus Transmission request Api for upper layer module
                    I.e. PduR Module calls this Api for[Segmented: Multiframe][Unsegemented: Singleframe] type
                    tranmission request.
 Parameter        : PduIdType, PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType *CanTpTxInfoPtr)
{
    Std_ReturnType RetVal = E_NOT_OK; /* TRACE[SWS_CanTp_00294] */
    CanTp_TickType Value = 0;
    CanTp_TickType ElapsedValue;
	uint16 MaxLength;
    uint8 PciId;
    uint8 ErrorId;
	uint8 PayloadLength;
	uint8 TX_DL;
    const CanTp_TxSduType *Connection;
    CanTp_ChannelType *Channel;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(CanTpTxSduId, CANTP_TRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {
        Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
        Channel = CanTp_Channel + Connection->ChannelId;

		if(CanTpTxInfoPtr == NULL_PTR)
		{   /* TRACE[SWS_CanTp_00321] */
			ErrorId = CANTP_E_PARAM_POINTER;
		}
		else if(CanTpTxInfoPtr->SduLength == 0)
		{
			ErrorId = CANTP_E_COM;
		}
		else
		{
	        CanTp_Prv_TxPciInit(&PciId, CanTpTxSduId, CanTpTxInfoPtr);
			TX_DL = CanTp_Prv_GetTxDl(Connection); /* TRACE[SWS_CanTp_00354] */

			if(CanTp_Prv_GetBit(Connection->BitFields, CANTP_FUNCTIONAL))
			{
			    PayloadLength = TX_DL - 1 - CanTp_AddressSize[Connection->AddressFormatId];
				MaxLength = (PciId <= CANTP_NPCI_SFCANFD) ? (PayloadLength - 1) : PayloadLength;
			}
			else
			{
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
				MaxLength = (TX_DL > CANTP_DEFAULT_CAN_DL) ? CANTP_MAXFDFFDL : CANTP_MAXFFDL;
                #else
                MaxLength = CANTP_MAXFFDL;
                #endif
			}
            /* TRACE[SWS_CanTp_00093][SWS_CanTp_00231][SWS_CanTp_00232] */
			ErrorId = (CanTpTxInfoPtr->SduLength > MaxLength) ? CANTP_E_INVALID_TATYPE : CANTP_NO_ERROR;
		}

        if(ErrorId != CANTP_NO_ERROR)
        {
            CanTp_Prv_ReportRunTimeError(CANTP_TRANSMIT, ErrorId);
        }
        else
        {
            CanTp_GetElapsedValue(&Value, &ElapsedValue);

            SchM_Enter_CanTp_EXCLUSIVE_AREA();

            if(CanTp_Prv_GetState(Connection->ChannelId) == CANTP_IDLE)
            {    /* TRACE[SWS_CanTp_00206][SWS_CanTp_00287][SWS_CanTp_00288][SWS_CanTp_00123] Accept request for Tx in
                 IDLE state */
                Channel->ActiveSduId = CanTpTxSduId;
                Channel->PciId = PciId;
                Channel->SduLength = CanTpTxInfoPtr->SduLength;
                Channel->InitialTicks = Value; /* TRACE[SWS_CanTp_00167] */
                /* Invalid STmin to denote that 1st FC-CTS is not received, shall be set after rx of 1st FC-CTS */
                Channel->STminTicks = CANTP_INVALID_STMIN_TICKS;
                CanTp_SubState[Connection->ChannelId] = CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED;
                RetVal = E_OK;
            }

            SchM_Exit_CanTp_EXCLUSIVE_AREA();
        }
    }

    return(RetVal);
}

#if(CANTP_CANTPLITE_SUPPORT != CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_CancelTransmit
 Syntax           : CanTp_CancelTransmit(CanTpTxSduId)
 Description      : TRACE[SWS_CanTp_00246] This service primitive is used to cancel the transfer of a pending CAN N-SDU.
                    When the function returns, no transmission is in progress anymore with the given N-SDU identifier.
 Parameter        : CanTpTxSduId
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
    Std_ReturnType RetVal = E_NOT_OK; /* TRACE[SWS_CanTp_00294] */
    const CanTp_TxSduType *Connection;
    boolean TcDisabled;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(CanTpTxSduId, CANTP_CANCELTRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {
        Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
        TcDisabled = CanTp_Prv_GetBit(Connection->BitFields, CANTP_TC_DISABLED); /* TRACE[SWS_CanTp_00242] */

        SchM_Enter_CanTp_EXCLUSIVE_AREA();

        if((TcDisabled) || (CanTp_Prv_GetState(Connection->ChannelId) != CANTP_TRANSMISSION) ||
           (CanTpTxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId))
        {   /* TRACE[SWS_CanTp_00254] */
			CanTp_Prv_ReportRunTimeError(CANTP_CANCELTRANSMIT, CANTP_E_OPER_NOT_SUPPORTED);
        }
        else
        {
			/* TRACE[SWS_CanTp_00255] Cancellation is success. Report negatively to unlock previously occupied buffer */
			CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            /* TRACE[SWS_CanTp_00248][SWS_CanTp_00274][SWS_CanTp_00243] */
			if(CanTp_SubState[Connection->ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
			{
			    CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
			}
            /* TRACE[SWS_CanTp_00256] */
			CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
			RetVal = E_OK;
        }

        SchM_Exit_CanTp_EXCLUSIVE_AREA();
    }

    return (RetVal);
}

/***********************************************************************************************************************
 Function name    : CanTp_CancelReceive
 Syntax           : CanTp_CancelReceive(RxPduId)
 Description      : TRACE[SWS_CanTp_00257] This service primitive is used to cancel the transfer of a pending CAN N-SDU.
                    When the function returns, no reception is in progress anymore with the given N-SDU identifier.
 Parameter        : RxPduId
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
    uint8 PayLoadLength;
    Std_ReturnType RetVal = E_NOT_OK; /* TRACE[SWS_CanTp_00294] */
    const CanTp_RxSduType *Connection;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(CanTpRxSduId, CANTP_CANCELRECEIVE, CANTP_E_PARAM_ID)) /* TRACE[SWS_CanTp_00260] */
    #endif
    {
        Connection = CanTp_CfgPtr->RxSdu + CanTpRxSduId;

        SchM_Enter_CanTp_EXCLUSIVE_AREA();

        if((CanTp_Prv_GetState(Connection->ChannelId) != CANTP_RECEPTION) ||
           (CanTpRxSduId != CanTp_Channel[Connection->ChannelId].ActiveSduId))
        {   /* TRACE[SWS_CanTp_00260][SWS_CanTp_00262] */
            CanTp_Prv_ReportRunTimeError(CANTP_CANCELRECEIVE, CANTP_E_OPER_NOT_SUPPORTED);
        }
        else
        {
            PayLoadLength = CanTp_Prv_GetRxDl(Connection->ChannelId) -
                            CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;
            /* This case is true only when we have case other than Last CF or SF */
            if(CanTp_Channel[Connection->ChannelId].SduLengthRemaining > PayLoadLength) /* TRACE[SWS_CanTp_00262] */
            {
                /* TRACE[SWS_CanTp_00263] Cancellation is success. Report negatively to unlock occupied buffer */
                CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
                /* TRACE[SWS_CanTp_00248] */
                if(CanTp_SubState[Connection->ChannelId] == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION)
                {
                    CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
                }
                /* TRACE[SWS_CanTp_00261] */
                CanTp_SubState[Connection->ChannelId] = CANTP_IDLE;
                RetVal = E_OK;
            }
        }

        SchM_Exit_CanTp_EXCLUSIVE_AREA();
    }

    return (RetVal);
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_TxConfirmation
 Syntax           : CanTp_TxConfirmation(TxPduId)
 Description      : Indication of a transmit confirmation from a lower layer communication interface module. I.e.
                    CanIf Module calls this Api for [SF][FF][CF][FC] transmit confirmation.
                    TRACE[SWS_CanTp_00215][SWS_CanTp_00076][SWS_CanTp_00236]
 Parameter        : PduIdType
 Return value     : None
***********************************************************************************************************************/
void CanTp_TxConfirmation(PduIdType TxPduId)
{   /* TRACE[SWS_CanTp_00076] */
	CanTp_ChannelType *Channel;
	CanTp_ChannelIdType ChannelId;
	uint8 SubState;
    CanTp_TickType Value = 0;
	CanTp_TickType ElapsedValue;
    uint8 MaxCopyLength;
	const CanTp_TxSduType *TxConnection;

	#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
	if(CanTp_Prv_IsNoDevError(TxPduId, CANTP_TXCONFIRMATION, CANTP_E_INVALID_TX_ID))
	#endif
	{
	    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	    SchM_Enter_CanTp_EXCLUSIVE_AREA();

        ChannelId = CanTp_TxConfirmationChannel[TxPduId];
        Channel = CanTp_Channel + ((ChannelId < CanTp_CfgPtr->NumberOfChannels) ? ChannelId : 0);
        SubState = (ChannelId < CanTp_CfgPtr->NumberOfChannels) ? CanTp_SubState[ChannelId] : CANTP_IDLE;

		switch(SubState)
		{
		    case CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION:

                Channel->InitialTicks = Value;
                CanTp_Prv_FcTxConfirmation(ChannelId);
                CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL; /* TRACE[SWS_CanTp_00248] */
                break;

            case CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION:

                Channel->InitialTicks = Value;
                TxConnection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
                MaxCopyLength = CanTp_Prv_GetTxDl(TxConnection) -
                                CanTp_AddressSize[TxConnection->AddressFormatId] - CanTp_PciSize[Channel->PciId];
                Channel->SduLengthRemaining = (Channel->SduLengthRemaining < MaxCopyLength) ? 0 :
                                              (Channel->SduLengthRemaining - MaxCopyLength);

                if(Channel->PciId == CANTP_NPCI_CF)
                {
                    Channel->SN++;
                    Channel->SN &= CANTP_LOWERNIBBLE_MASK ;
                    Channel->BlockCfsRemaining--;
                }

                if(Channel->SduLengthRemaining == 0)
                {   /* TRACE[SWS_CanTp_00177][SWS_CanTp_00090][SWS_CanTp_00204] This is entered for SF or Last CF. */
                    CanTp_SubState[ChannelId] = CANTP_IDLE;
                    CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, TxConnection->PduRPduHandleId, E_OK);
                }
                else
                {
                    if(Channel->BlockCfsRemaining != 0)
                    {
                        CanTp_SubState[ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
                    }
                    else
                    {   /* If flowcontrol is disabled then move state to next level and update STMin/BS defaults. */
                        CanTp_Prv_PrepareFcRecieve(ChannelId);
                    }
                }
                /* TRACE[SWS_CanTp_00248][SWS_CanTp_00075] */
                CanTp_TxConfirmationChannel[TxPduId] = CANTP_INVALID_CHANNEL;
                break;

            default:    /* Wrong State */
                break;
		}

		SchM_Exit_CanTp_EXCLUSIVE_AREA();
		/* If burst mode is enabled then activate state function directly. */
		CanTp_Prv_BurstMainFunction(ChannelId, CANTP_TRIGGER_TX_CONFIRMATION);
	}
}

/***********************************************************************************************************************
 Function name    : CanTp_RxIndication
 Syntax           : CanTp_RxIndication(RxPduId, PduInfoPtr)
 Description      : Indication of a received I-PDU from a lower layer communication interface module. I.e. CanIf Module
                    calls this Api for [SF][FF][CF][FC] type frames. TRACE[SWS_CanTp_00214][SWS_CanTp_00078]
                    [SWS_CanTp_00235][SWS_CanTp_00057][SWS_CanTp_00290]
 Parameter        : PduIdType, PduInfoType
 Return value     : None
***********************************************************************************************************************/
void CanTp_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
	CanTp_RxContextType Context;
	uint8 ErrorId;

	Context.PduId = RxPduId;
    Context.FrameType = 0;
    Context.ChannelId = 0;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(RxPduId, CANTP_RXINDICATION, CANTP_E_INVALID_RX_ID))
	#endif
	{/* TRACE[SWS_CanTp_00238] Initialization check done in CanTp_Prv_IsNoDevError */
		if(PduInfoPtr == NULL_PTR)
		{   /* TRACE[SWS_CanTp_00322] */
		    CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_PARAM_POINTER);
		}
		else
		{
		    ErrorId = CanTp_Prv_GetRxContext(&Context, PduInfoPtr);

		    if(ErrorId != CANTP_NO_ERROR)
            {
                CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, ErrorId);
            }
            else if(CanTp_Prv_RxSduLengthCheck(&Context, PduInfoPtr) != E_OK)
            {
                CanTp_Prv_LengthError(&Context);
			}
			else
			{   /* Frame Processing based on Context updated in CanTp_Prv_GetRxContext and CanTp_Prv_RxSduLengthCheck */
                CanTp_Prv_ProcessFrame(&Context, PduInfoPtr);
                /* If burst mode is enabled then activate state function directly. */
                CanTp_Prv_BurstMainFunction(Context.ChannelId, CANTP_TRIGGER_RX_INDICATION);
            }
		}
	}
}

#if(CANTP_TRIGGER_TRANSMIT_API == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_TriggerTransmit
 Syntax           : CanTp_TriggerTransmit(TxPduId, PduInfoPtr)
 Description      : Can Driver calls this Api for the data to be transmitted correponding to the request in
                    CanIf_Transmit.
 Parameter        : PduIdType, PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
Std_ReturnType CanTp_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr)
{
    Std_ReturnType Status = E_NOT_OK; /* TRACE[SWS_CanTp_00294] */
    CanTp_ChannelIdType ChannelId;
    uint8 TX_DL = CANTP_DEFAULT_CAN_DL;

    #if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
    if(CanTp_Prv_IsNoDevError(TxPduId, CANTP_TRIGGERTRANSMIT, CANTP_E_INVALID_TX_ID))
    #endif
    {   /* TRACE[SWS_CanTp_00238] Initialization check done in CanTp_Prv_IsNoDevError */
        if(PduInfoPtr == NULL_PTR)
        {
            CanTp_Prv_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_PARAM_POINTER);
        }
        else
        {  /* Take the ChannelId locked for TxConfirmation even in TriggerTransmit. */
            ChannelId = CanTp_TxConfirmationChannel[TxPduId];

            SchM_Enter_CanTp_EXCLUSIVE_AREA();
            if(ChannelId < CanTp_CfgPtr->NumberOfChannels)
            {
                TX_DL = (CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION) ?
                        CanTp_Prv_GetTxDl(CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId) : TX_DL;

                if((PduInfoPtr->SduLength < TX_DL) || (PduInfoPtr->SduDataPtr == NULL_PTR))
                {
                    CanTp_Prv_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_PARAM_POINTER);
                }
                else
                {   /* TRACE[SWS_CanTp_00298] */
                    Status = CanTp_Prv_CreateFrame(ChannelId, PduInfoPtr);
                }
            }
            SchM_Exit_CanTp_EXCLUSIVE_AREA();
        }
    }

    return Status;
}
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"
