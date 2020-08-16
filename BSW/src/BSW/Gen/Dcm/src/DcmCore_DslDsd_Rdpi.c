

#include "DcmCore_DslDsd_Inf.h"
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_PeriodicInfoType_tst,DCM_CODE) Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER];  /* Periodic scheduler array */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,       DCM_VAR)      Dcm_NumOfActivePeriodicId_u8;            /* Variable to store the number of active identifiers in the periodic scheduler */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxDidIndexType_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean,DCM_VAR) s_isTxPduIdBusy_b =  FALSE;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* RDPI2 message context table */
VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Rdpi2MesContext_st;
/* response type */
VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Rdpi2ResponseType_en;
/* RDPI2 info structure */
VAR(PduInfoType,DCM_VAR) Dcm_DsldRdpi2pduinfo_ast[DCM_CFG_NUM_RDPITYPE2_TXPDU];
/* RDPI2 TYPE2 TxPduid index*/
static VAR(uint8,DCM_VAR) s_idxRdpi2TxPduId_u8;
/* Pointer to RDPI info structure */
P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRdpi2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



/**
**************************************************************************************************
* Dcm_RdpiPriorityInversion :  DCM function to perofrm the Priority Inversion for RDPI service
* \param  idxSchedulerIndexLoop_u16    :   Index of the scheduler for which Dcm_RdpiPriorityInversion has to be performed
*
* \retval          None
*
* \seealso
* \usedresources
**************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_RdpiPriorityInversion(VAR(uint16,AUTOMATIC) idxSchedulerIndexLoop_u16)
{
    VAR(uint16,AUTOMATIC) idxIndex_u16 = 0u;
    VAR(Dcm_PeriodicInfoType_tst,DCM_CODE) Temp_PeriodicInfo_st;
    /*copy the values associated with the scheduled PDID into Temporary variables */
    Temp_PeriodicInfo_st.cntrTime_u32         = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32;
    Temp_PeriodicInfo_st.dataId_u16           = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataId_u16;
    Temp_PeriodicInfo_st.idxPeriodicId_u16    = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].idxPeriodicId_u16;
    Temp_PeriodicInfo_st.dataOverflowValue_en = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataOverflowValue_en;
    Temp_PeriodicInfo_st.dataRange_b          = Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataRange_b;

    /*Perform Priority Inversion for the scheduled PDID*/
    for(idxIndex_u16 = idxSchedulerIndexLoop_u16 ; idxIndex_u16 < (DCM_CFG_MAX_DID_SCHEDULER-1u) ; idxIndex_u16++)
    {
        /*Shift the PDID present in the RDPI scheduler up by one */
        Dcm_PeriodicInfo_st[idxIndex_u16].cntrTime_u32         = Dcm_PeriodicInfo_st[idxIndex_u16+1].cntrTime_u32;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataId_u16           = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataId_u16;
        Dcm_PeriodicInfo_st[idxIndex_u16].idxPeriodicId_u16    = Dcm_PeriodicInfo_st[idxIndex_u16+1].idxPeriodicId_u16;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataOverflowValue_en = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataOverflowValue_en;
        Dcm_PeriodicInfo_st[idxIndex_u16].dataRange_b          = Dcm_PeriodicInfo_st[idxIndex_u16+1].dataRange_b;
    }

        /*Place the scheduled PDID at the end of the RDPI scheduler */
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].cntrTime_u32         = Temp_PeriodicInfo_st.cntrTime_u32;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataId_u16           = Temp_PeriodicInfo_st.dataId_u16;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].idxPeriodicId_u16    = Temp_PeriodicInfo_st.idxPeriodicId_u16;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataOverflowValue_en = Temp_PeriodicInfo_st.dataOverflowValue_en;
        Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER-1u].dataRange_b          = Temp_PeriodicInfo_st.dataRange_b;
}


/**
 **************************************************************************************************
 * Dcm_DsldPeriodicSchedulerIni :  DCM function to initialise the periodic scheduler
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldPeriodicSchedulerIni(void)
{
	VAR(uint16,AUTOMATIC) idxIndex_u16;
	for(idxIndex_u16=0;idxIndex_u16<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u16++)
	{
		Dcm_PeriodicInfo_st[idxIndex_u16].dataId_u16=0x00;
		Dcm_PeriodicInfo_st[idxIndex_u16].idxPeriodicId_u16=0x00;
		Dcm_PeriodicInfo_st[idxIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
		Dcm_PeriodicInfo_st[idxIndex_u16].cntrTime_u32=0x00;
		/*Initialize that the did range is not valid*/
		Dcm_PeriodicInfo_st[idxIndex_u16].dataRange_b = FALSE;

	}
	Dcm_NumOfActivePeriodicId_u8 = 0x00;
	Dcm_PeriodicSchedulerRunning_b=FALSE;
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
	s_idxRdpi2TxPduId_u8=0;
#endif
	Dcm_ResetDIDIndexstruct(&s_Dcm_idxDidIndexType_st);		/*This function is invoked to reset all the elements of DID index structure to its default value*/
}


/**
**************************************************************************************************
* Dcm_InitializeRdpiParameters :  DCM function to obtain the data of the DID and pass it on to lower layers
*                          for transmission
* \param           dataLength_u32    :   length of the DID
*                  dataSchedulerLoop_u16 : Index of the PID in periodic scheduler table
* \retval          STD_ReturnType      :    E_OK if transmission was successful
*
* \seealso
* \usedresources
**************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_SetRdpicounter(VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16);
static FUNC(void,DCM_CODE) Dcm_SetRdpicounter(VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16)
{

    if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en==DCM_RDPI_SLOW_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_SLOWRATE;
     }
     else if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en==DCM_RDPI_MEDIUM_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_MEDIUMRATE;
     }
     else if(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataOverflowValue_en== DCM_RDPI_FAST_RATE)
     {
         Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].cntrTime_u32=DCM_CFG_PERIODICTX_FASTRATE;
     }
     else
     {
        /*Nothing to be done here*/
     }
}

/**
**************************************************************************************************
* Dcm_InitializeRdpiParameters :  DCM function to obtain the data of the DID and pass it on to lower layers
*                          for transmission
* \param           dataLength_u32    :   length of the DID
*                  dataSchedulerLoop_u16 : Index of the PID in periodic scheduler table
* \retval          STD_ReturnType      :    E_OK if transmission was successful
*
* \seealso
* \usedresources
**************************************************************************************************
*/
/*MR12 RULE 8.13 VIOLATION: The object addressed by the pointer parameter 'idxRdpiType2_pu8' is not modified and so the pointer could be of type 'pointer to const'. MISRA C:2012 Rule-8.13  */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_InitializeRdpiParameters(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpiType2_pu8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_InitializeRdpiParameters(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpiType2_pu8)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    VAR (Std_ReturnType,   AUTOMATIC) idxIndex_u8;
    idxIndex_u8=0;
#endif
    dataCondChkRetVal_u8=E_NOT_OK;

#if(DCM_CFG_RDPITYPE2_ENABLED == DCM_CFG_OFF)
    (void)idxRdpiType2_pu8;

    if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&&(Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE))
    {
        Dcm_DsldRoeRdpi_pcst = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs;
        /* Get the active Tx buffer pointer for periodic transmissions */
        Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = Dcm_DsldRoeRdpi_pcst->txbuffer_ptr;
        /* Get the Max possible response length possible */
        Dcm_DsldMsgContext_st.resMaxDataLen = Dcm_DsldRoeRdpi_pcst->txbuffer_length_u32 - 0x01u;
        /* Get the transmission buffer pointer */
        Dcm_DsldMsgContext_st.resData = &(Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[3]);
        /* Is suppressed positive bit is always set to FALSE */

        Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse = FALSE;
        /*Dcm is free*/
        dataCondChkRetVal_u8=E_OK;
        s_isTxPduIdBusy_b = FALSE;
    }
    else
    {   /*Dcm is busy*/
        dataCondChkRetVal_u8=E_NOT_OK;
        s_isTxPduIdBusy_b = TRUE;
    }
#else
    (void)idxRdpiType2_pu8;
    Dcm_DsldRdpi2_pcst = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs;
    /* Fill the default response type */
    Dcm_Rdpi2ResponseType_en = DCM_DSLD_POS_RESPONSE;
    /* Response length (filled by the service) */
    Dcm_Rdpi2MesContext_st.resDataLen = 0x0u;
    /* Fill the addressing mode as physical  */
    Dcm_Rdpi2MesContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
    for( idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU;idxIndex_u8++)
    {
        /*Check if the Roe type isTxPduId is set to the value false*/
        if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy==FALSE)
        {
            Dcm_Rdpi2MesContext_st.resData = &Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txbuffer_ptr[0];
            break;
        }
    }
    /*Check if any TXPDU is available, if not wait for the next time slice*/
    if(idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU)
    {
        /* Fill the maximum possible response length */
        Dcm_Rdpi2MesContext_st.resMaxDataLen = Dcm_DsldRdpi2_pcst->txbuffer_length_u32 - 1uL;
        /* This is ROE requested service */
        Dcm_Rdpi2MesContext_st.msgAddInfo.sourceofRequest = DCM_RDPI_SOURCE;
        /* Is suppressed positive bit is always FALSE */

        Dcm_Rdpi2MesContext_st.msgAddInfo.suppressPosResponse = FALSE;
        /*Update the index of TxPdu to be used by the Dcm_FrameRdpiresponse()*/
        *idxRdpiType2_pu8=idxIndex_u8;
        s_idxRdpi2TxPduId_u8=idxIndex_u8;
        /*TXPDUID is available*/
        dataCondChkRetVal_u8=E_OK;
        s_isTxPduIdBusy_b = FALSE;
    }
    else
    {
        dataCondChkRetVal_u8=E_NOT_OK;
        s_isTxPduIdBusy_b = TRUE;
    }
#endif
    return dataCondChkRetVal_u8;
}

#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
/**
**************************************************************************************************
* Dcm_GetRdpiType2Index :  DCM function to obtain the data of the DID and pass it on to lower layers
*                          for transmission
* \param           dataLength_u32    :   length of the DID
*                  dataSchedulerLoop_u16 : Index of the PID in periodic scheduler table
* \retval          STD_ReturnType      :    E_OK if transmission was successful
*
* \seealso
* \usedresources
**************************************************************************************************
*/

FUNC(void,DCM_CODE) Dcm_GetRdpiType2Index(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpi2TxPduId_u8)
{
    *idxRdpi2TxPduId_u8=s_idxRdpi2TxPduId_u8;
}
#endif

/**
**************************************************************************************************
* Dcm_FrameRdpiresponse :  DCM function to obtain the data of the DID and pass it on to lower layers
*                          for transmission
* \param           dataLength_u32    :   length of the DID
*                  dataSchedulerLoop_u16 : Index of the PID in periodic scheduler table
* \retval          STD_ReturnType      :    E_OK if transmission was successful
*
* \seealso
* \usedresources
**************************************************************************************************
*/
static FUNC(Std_ReturnType,DCM_CODE) Dcm_FrameRdpiresponse(VAR(uint32, AUTOMATIC) dataLength_u32,VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_FrameRdpiresponse(VAR(uint32, AUTOMATIC) dataLength_u32,VAR(uint16, AUTOMATIC) dataSchedulerLoop_u16)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataReaddataRetVal_u8; /* Return value of Condition check API */
    VAR (uint8,   AUTOMATIC) idxRdpiType2_u8;
    idxRdpiType2_u8=0xFF;
    dataReaddataRetVal_u8=E_NOT_OK;

    dataReaddataRetVal_u8=Dcm_InitializeRdpiParameters(&idxRdpiType2_u8);

    if(E_OK==dataReaddataRetVal_u8)
    {
        /* Call the API to read data corresponding to the periodic identifier */
#if(DCM_CFG_RDPITYPE2_ENABLED == DCM_CFG_OFF)
        dataReaddataRetVal_u8 = Dcm_GetDIDData (&s_Dcm_idxDidIndexType_st,&Dcm_DsldMsgContext_st.resData[1]);
#else
        dataReaddataRetVal_u8 = Dcm_GetDIDData (&s_Dcm_idxDidIndexType_st,&Dcm_Rdpi2MesContext_st.resData[1]);
#endif
        /*Check if data read successfully or if applicationtion has set any NRC*/
        if(s_Dcm_idxDidIndexType_st.dataNegRespCode_u8==0x00)
        {
            /* If data was read successfully */
            if(E_OK==dataReaddataRetVal_u8)
            {
                /*  Data ready successfully, trigger the response*/
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
               /* Update the response length for the SID and the identifier */
               Dcm_Rdpi2MesContext_st.resDataLen=dataLength_u32+1uL;
               /* Update the periodic identifier in the transmission buffer */
               Dcm_Rdpi2MesContext_st.resData[0]=(uint8)(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataId_u16);
               /* Send the response */
               /*txpduid is blocked in the processiong done before Pdur_DcmTransmit is triggered*/
               Dcm_ProcessingDone(&Dcm_Rdpi2MesContext_st);

#else
               (void)dataSchedulerLoop_u16;
               /* Multicore: The write needs to be locked as there could be parallel Rx and ROE requests */
               SchM_Enter_Dcm_Global_NoNest();
               if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&&(Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE))
               {
                   #if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                   VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
                   stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
                   /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
                   if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
                   #endif
                   {
                       /* By moving the DSL state, ignore request from tester */
                       Dcm_DsldGlobal_st.stDslState_en = DSL_ROETYPE1_RECIEVED;
                   }
               }
               SchM_Exit_Dcm_Global_NoNest();

               /* Multicore: No lock needed here as Dsl state is an atomic operation
                * This is a read operation and when DSL is set to DSL_ROETYPE1_RECIEVED in the above lines of code
                * then only the request is accepted. So there is no chance of parallel write */
               if(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)
               {

                   /* Interrupt locks added to protect updation of Dsd state machine and variables in case of a new reception/processing of ROE event */
                   Dcm_DsldMsgContext_st.resData[0]=(uint8)(Dcm_PeriodicInfo_st[dataSchedulerLoop_u16].dataId_u16);
                   Dcm_DsldMsgContext_st.resDataLen=dataLength_u32+1u;
                   Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;
                   /* This is RDPI requested service */
                   Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_RDPI_SOURCE;
                   Dcm_DsldGlobal_st.dataSid_u8 = 0x2A;
                   Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_POS_RESPONSE;
                   /* Service found in table,Fill the message context structure with proper data */
                   Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;

                   /* Update the state variable to process the request */
                   Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                   Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE ;
                   /* Send the response */
                   Dcm_ProcessingDone(&Dcm_DsldMsgContext_st);
               }
#endif
               s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0; /*All the signals read correctly, therefore reset it to zero*/
               s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;    /*All the signals read correctly, therefore reset the signal data length to zero*/

            }
            else
            {
                s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0; /*All the signals read correctly, therefore reset it to zero*/
                s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;    /*All the signals read correctly, therefore reset the signal data length to zero*/
                dataReaddataRetVal_u8=E_NOT_OK;
            }
        }
        else
        {
            s_Dcm_idxDidIndexType_st.nrNumofSignalsRead_u16 = 0x0; /*All the signals read correctly, therefore reset it to zero*/
            s_Dcm_idxDidIndexType_st.dataSignalLengthInfo_u32 = 0x0;    /*All the signals read correctly, therefore reset the signal data length to zero*/
            dataReaddataRetVal_u8=E_NOT_OK;
        }
    }
    else
    {
        dataReaddataRetVal_u8=E_NOT_OK;
    }

    return dataReaddataRetVal_u8;
}

/**
**************************************************************************************************
* Dcm_VerifyLengthRdpiType :  DCM function to verify if the length of the DID is within the Tx buffer limits
*
* \param           dataLength_u32    :   length of the DID
*
* \retval          None
* \seealso
* \usedresources
**************************************************************************************************
*/
static FUNC(Std_ReturnType,DCM_CODE) Dcm_VerifyLengthRdpiType(VAR(uint32,AUTOMATIC) dataLength_u32);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_VerifyLengthRdpiType(VAR(uint32,AUTOMATIC) dataLength_u32)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
    dataCondChkRetVal_u8=E_NOT_OK;

    /*Verify if the DID can be accomodated within the buffer available*/
    if((dataLength_u32+1uL)<=Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs->txbuffer_length_u32)
    {
        dataCondChkRetVal_u8=E_OK;
    }

    return dataCondChkRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_RdpiCheckPIDSupportConditions :  DCM function to monitor the session security and condition
 * check read function for the PID, if all checks are fine then the length of PID is obtained and
 * RDPI response frame function is invoked
 *
 * \param           idxPeriodicIndex_u16    :   Index of the DID in Dcm_DIDConfig[]
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiCheckPIDSupportConditions(VAR(uint16,AUTOMATIC) idxPeriodicIndex_u16);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiCheckPIDSupportConditions(VAR(uint16,AUTOMATIC) idxPeriodicIndex_u16)
{
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
    VAR (uint32,AUTOMATIC) dataSessionMask_u32;   /* Variable to hold the configured sessions value */
    VAR (uint32,AUTOMATIC) dataSecurityMask_u32;  /* Variable to hold the configured security value */
    VAR(uint32,                      AUTOMATIC) dataLength_u32;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Pointer to extended configuration */

    dataLength_u32=0x0;
    dataSessionMask_u32=0;
    dataSecurityMask_u32=0;
    /*initialize the file static DID structure variable with the index of DID in Dcm_DIDCOnfig*/
    s_Dcm_idxDidIndexType_st.idxIndex_u16 = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].idxPeriodicId_u16;
    s_Dcm_idxDidIndexType_st.dataRange_b = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataRange_b;
    dataCondChkRetVal_u8=E_NOT_OK;
    adrExtendedConfig_pcst=NULL_PTR;

    /*Is the DID range DID or not*/

    if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
    {
        adrExtendedConfig_pcst=Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
    }
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
    /*Control comes here for range DIDS*/
    else
    {
        s_Dcm_idxDidIndexType_st.dataRangeDid_16 = Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataId_u16;
        adrExtendedConfig_pcst=Dcm_DIDRangeConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
    }
#endif

    /*Obtain the session and security mask based on the type of DID*/
    /*MR12 RULE 9.1 VIOLATION: Using value of uninitialized automatic object 'adrExtendedConfig_pcst'. MISRA C:2012 Rule-9.1*/
    dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
    /*MR12 RULE 9.1 VIOLATION: Using value of uninitialized automatic object 'adrExtendedConfig_pcst'. MISRA C:2012 Rule-9.1*/
    dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;

    /* If the identifier is supported in the current session*/
    if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
    {
       /* If the identifier is supported in the current security level */
        if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
        {
            /*Check if condition read for the DID is fine*/
            dataCondChkRetVal_u8=Dcm_RdpiIsDidCondtionChkReadSupported(&s_Dcm_idxDidIndexType_st);
            if (dataCondChkRetVal_u8 == E_OK)
            {
               /*Obtain the length of the PDID*/
               if(E_OK==Dcm_GetLengthOfDIDIndex(s_Dcm_idxDidIndexType_st, &dataLength_u32,(uint16)(Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataId_u16|0xF200u)))
               {
                   /*Verify if the length of DID fits in within the buffer*/
                   if(E_OK==Dcm_VerifyLengthRdpiType(dataLength_u32))
                   {
                       /*All checks passed, frame the rdpi response*/
                       dataCondChkRetVal_u8=Dcm_FrameRdpiresponse(dataLength_u32,idxPeriodicIndex_u16);
                   }
                   else
                   {   /*Stop processing this ID length check has failed*/
                     Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                   }
               }
               else
               {   /*Stop processing this ID since some session or security or condition or readdata has failed*/
                 Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
               }
            }
            else
            {      /*Stop processing this ID condition check has failed*/
                Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
            }
        }
        else
        {   /*Stop processing this ID security check has failed*/
            Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
        }
    }
    else
    {   /*Stop processing this ID session check has failed*/
        Dcm_PeriodicInfo_st[idxPeriodicIndex_u16].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
    }

    return dataCondChkRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_RdpiMainFunction :  DCM function to monitor the periodic scheduler and for initiating the
 * periodic transmissions of the active periodic identifiers.
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_RdpiMainFunction(void)
{
    VAR(uint16, AUTOMATIC) idxSchedulerIndexLoop_u16 = 0u;
    VAR(uint16, AUTOMATIC) idxPriorityInversion_u16 = 0u;
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    VAR (Std_ReturnType,   AUTOMATIC) idxIndex_u8;
    idxIndex_u8=0;
#endif
    idxSchedulerIndexLoop_u16=0x0u;
    dataCondChkRetVal_u8=E_NOT_OK;

    if(Dcm_NumOfActivePeriodicId_u8>0u)
    {

#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
        /*Loop throught the scheduler and check if any of the IDs time slice has expired*/
        for( idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU;idxIndex_u8++)
        {
            /*MR12 RULE 10.4 VIOLATION: The is required for implementation*/
            if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy!=FALSE)
            {
                if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8!=0)
                {
                    /*Decrrement the timer and chck if time out has occured*/
                    Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8--;
                    /*Check if the timer has timedout*/
                    if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8==0)
                    {
                        /*Release the TxPDU since the confirmation has not yet come and timer has timedout*/
                        /*MR12 RULE VIOLATION: The is required for implementation*/
                        Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy=FALSE;
                        s_isTxPduIdBusy_b = FALSE;
                        /*Reload the counter, TXPDU is already released*/
                        Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8=DCM_CFG_RDPITYPE2FREETXPDUCOUNTER;
                    }
                }
            }
        }
#endif
        /*Loop throught the scheduler and check if any of the IDs time slice has expired*/
        for (idxSchedulerIndexLoop_u16=0;idxSchedulerIndexLoop_u16<DCM_CFG_MAX_DID_SCHEDULER;idxSchedulerIndexLoop_u16++)
        {
            if (Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION)
            {
               /* Check if the identifier is ready for transmission*/
               if(Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32>0uL)
               {
                   /* Decrement the counter and see if the time slice is reached*/
                   Dcm_PeriodicInfo_st[idxSchedulerIndexLoop_u16].cntrTime_u32--;
               }
            }
        }

        if((DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8))&&(NULL_PTR != Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rdpi_info_pcs))
        {
            for (idxSchedulerIndexLoop_u16=0;idxSchedulerIndexLoop_u16<DCM_CFG_MAX_DID_SCHEDULER;idxSchedulerIndexLoop_u16++)
            {
                if ((Dcm_PeriodicInfo_st[idxPriorityInversion_u16].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION) && \
                        (Dcm_PeriodicInfo_st[idxPriorityInversion_u16].cntrTime_u32 == 0uL))
                {
                   dataCondChkRetVal_u8=Dcm_RdpiCheckPIDSupportConditions(idxPriorityInversion_u16);

                   /*If response was triggered successfully on the bus, reload the counters and perforrm priority Inversion*/
                   if((s_isTxPduIdBusy_b != TRUE) || (dataCondChkRetVal_u8 != E_NOT_OK))
                   {
                      Dcm_SetRdpicounter(idxPriorityInversion_u16);
                      Dcm_RdpiPriorityInversion(idxPriorityInversion_u16);
                   }
                }
                else
                {
                    /*increment the scheduler counter when cntrTime_u32 is not zero and dataOverflowValue_en is not DCM_RDPI_NO_TRANMISSION*/
                    idxPriorityInversion_u16++;
                }
            }
        }
    }
}

/*
***********************************************************************************************************
*  Dcm_DsldResetRDPI :TO Reset the state machine of RDPI type 1 or Type 2
                         Also reset of settings done for the active service table
*  \param         None
*  \retval        None
*  \seealso
*
***********************************************************************************************************/

FUNC(void,DCM_CODE) Dcm_DsldResetRDPI(void)
{

    /*Check if RDPI Type 1 periodic event is under processing when S3 timeout happens */
    /* Multicore: No lock needed here as Dsl state is an atomic operation and this API will be invoked to reset
     * the RDPI APIs, the check is only to see if DSL is processing ROE event. Parallel update to DSL state will
     * not affect the functionality */
    if ((Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED) &&
        (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE))
    {
        /* Set the RDPI timer variable to zero */
        Dcm_DsldGlobal_st.dataRoeRdpiTimeout_u32 = 0;

        Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].
                                ptr_service_table_pcs;

        /* reset the DCM states */
        /* Multicore: Only called upon session change. So when there is a request under processing, this API will not be called
         * This API in only triggered if there is session timeout / after receving DSC response confirmation / Dcm_ResetToDefaultSession API
         */
        Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;
        /* Multicore: No lock needed here as Dsl state is an atomic operation */
         /* DSL state machine handling ensures that there is no data consistency issues as when RDPI is active
          * DSL state will not be changed in parallel*/
        Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;

        /* Update the tx PDU id to a invalid value */
        /* This is added to avoid Tx confirmation for RDPI type1 which can come after
           resetting the state machine if RDPI Type 1 response is already triggered */
        Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = 0xFF;
    }
    Dcm_DsldPeriodicSchedulerIni();
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

