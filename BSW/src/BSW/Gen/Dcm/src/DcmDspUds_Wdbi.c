

#include "DcmDspUds_Wdbi_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Wdbi_Priv.h"

/* Global varibale declaration */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspWDBIStates_ten,DCM_VAR) Dcm_stDspStateWDBI_en;   /* WDBI state */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stDspWdbiOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (boolean,DCM_VAR) Dcm_flgNvmWritePending_b;          /* variable to hold the NVM write status*/
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxwdbiDidIndexType;    /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint16,DCM_VAR)  s_dataDID_u16; /*Store the DID value sent from the tester */
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

 /***************************************************************************************************
 * Dcm_Dcm_WDBIInit : Initialisaton function for Write Data By Identifier (0x2E) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_Dcm_WDBIInit (void)
{
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8;
    VAR(Std_ReturnType,AUTOMATIC)   dataRetWriteFunc_u8;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)||   \
        (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF))
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
#endif
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
    P2CONST(Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidRangeConfig;
#endif
    ptrWriteFnc=NULL_PTR;
    dataNegResCode_u8 = 0x0;
    dataRetWriteFunc_u8=0x00;

    /* Check if there are any pending operations and if the did is a range did or not */

    if((Dcm_stDspWdbiOpStatus_u8 == DCM_PENDING) && (s_Dcm_idxwdbiDidIndexType.dataRange_b== FALSE))
    {
#if((DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)||   \
        (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF))
        ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
        ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        if(ptrSigConfig->idxDcmDspControlInfo_u16 > 0)
        {
            ptrWriteFnc   = ptrControlSigConfig->adrWriteFnc_cpv;
            /* If the DID use the Asynchronous operations */
            if((ptrWriteFnc != NULL_PTR)&& ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                ))
            {
#if(DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)
                /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                if(ptrDidConfig->dataFixedLength_b != FALSE)
                {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                    /* Call function to cancel the pending condition check operation for a DID */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetWriteFunc_u8 = (*(WdbiFnc4_pfct)(ptrWriteFnc))(NULL_PTR,DCM_CANCEL,&dataNegResCode_u8);
#endif
                }
                else
                {
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                    /* Call function to cancel the pending condition check operation for a DID */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetWriteFunc_u8 = (*(WdbiFnc3_pfct)(ptrWriteFnc))(NULL_PTR,0x0,DCM_CANCEL,&dataNegResCode_u8);
#endif
                }
                (void)dataNegResCode_u8;
                (void)dataRetWriteFunc_u8;
#endif
            }
#if(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)
            /*Check if write function is not NULL and use post is asynchronous*/
            else if ((ptrWriteFnc != NULL_PTR)&& (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
            {
                /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                if(ptrDidConfig->dataFixedLength_b != FALSE)
                {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                    /* Call function to cancel the pending condition check operation for a DID */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetWriteFunc_u8 = (*(WdbiFnc21_pfct)(ptrWriteFnc))(NULL_PTR,DCM_CANCEL,&dataNegResCode_u8);
#endif
                }
                else
                {
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                    /* Call function to cancel the pending condition check operation for a DID */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetWriteFunc_u8 = (*(WdbiFnc20_pfct)(ptrWriteFnc))(NULL_PTR,0x0,DCM_CANCEL,&dataNegResCode_u8);
#endif
                }
                (void)dataNegResCode_u8;
                (void)dataRetWriteFunc_u8;
            }
#endif
            else
            {
                /* Do nothing. Added to avoid MISRA warning */
            }
        }
#endif
#if ((DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
        if(ptrSigConfig->usePort_u8 == USE_BLOCK_ID)
        {
            /* Locking the unlocked block */
            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
        }
#endif
#endif
    }
    else
    {
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
        ptrDidRangeConfig=&Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
        ptrWriteFnc      = ptrDidRangeConfig->adrWriteFnc_pfct;
        /*Check if pointer to write function is not NULL and if the did is a range did or not */
        if ((ptrWriteFnc != NULL_PTR) && (s_Dcm_idxwdbiDidIndexType.dataRange_b!=FALSE))
        {
            /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
            if(ptrDidRangeConfig->nrRangeUsePort_b != FALSE)
            {
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                dataRetWriteFunc_u8 = (*(WriteFncRange1_pfct)(ptrWriteFnc))(0x0,NULL_PTR,DCM_CANCEL,0x0,&dataNegResCode_u8);
            }
            else
            {
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                dataRetWriteFunc_u8 = (*(WriteFncRange2_pfct)(ptrWriteFnc))(0x0,NULL_PTR,DCM_CANCEL,0x0,&dataNegResCode_u8);
            }
        }
#endif
    }
    /* Initialize the state of WDBI to IDLE */
    Dcm_stDspStateWDBI_en = DCM_DSP_WDBI_IDLE;
    /* Reset the Signal index to 0 */
    Dcm_DidSignalIdx_u16 = 0x0;
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
    /*Update the flag Dcm_flgNvmWritePending_b is to FALSE*/
    Dcm_flgNvmWritePending_b = FALSE;
#endif
    /* Reset the OpStatus */
    Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxwdbiDidIndexType);        /*This function is invoked to reset all the elements of DID index structure to its default value*/

    (void)dataRetWriteFunc_u8;

    (void)dataNegResCode_u8;

    (void)ptrWriteFnc;
}

/**
 **************************************************************************************************
 * Dcm_DcmWriteDataByIdentifier : Write Data By Identifier (0x2E) Service
 * WDBI service is used to write the Data record for the Data Identifier (DID)
 * sent in the request by the tester
 *
 * \param           pMsgContext: Pointer to message structure
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmWriteDataByIdentifier (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
                                                            P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (uint32,AUTOMATIC) dataSessionMask_u32;               /* Variable to hold the configured sessions value */
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Pointer to extended configuration */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
    P2CONST(Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidRangeConfig;
#endif
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrWriteFnc;
#if(DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF)
    VAR (uint32, AUTOMATIC) dataSignal_u32;                 /* Local variable for uint32 signal */
    VAR (uint16, AUTOMATIC) nrElements_u16;             /* Number of elements in the signal */
    VAR (uint16, AUTOMATIC) idxLoop_u16;                    /* counter to loop the array of signals */
#endif
#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint32, AUTOMATIC) dataSignal_s32;                 /* Local variable for sint32 signal */
#endif
#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)
    VAR (uint16, AUTOMATIC) dataSignal_u16;                 /* Local variable for uint16 signal */
#endif
#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint16, AUTOMATIC) dataSignal_s16;                 /* Local variable for sint16 signal */
#endif
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)
    VAR (uint8,  AUTOMATIC) dataSignal_u8;                  /* Local variable for uint8 signal */
#endif
#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint8,  AUTOMATIC) dataSignal_s8;                  /* Local variable for sint8 signal */
#endif
#if(DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
    VAR (boolean,AUTOMATIC) dataSignal_b;                   /* Local variable for boolean signal */
#endif
    /* Local variable for sint16 signal */
    VAR(uint16,AUTOMATIC)  nrLenDataRec_u16;              /* Variable to store the length of data record */
    VAR(uint16,AUTOMATIC)  idxDidSignal_u16;
    VAR(Std_ReturnType,AUTOMATIC)   dataRetGetDID_u8;      /* Variable to store the return from Binary Search function */
    VAR(Std_ReturnType,AUTOMATIC)   dataRetWriteFunc_u8;       /* Return from DcmDspConditionCheckWriteFunc */
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
    VAR(Std_ReturnType, AUTOMATIC) dataNvmWriteBlockRetVal_u8;/*Return value for Nvm_WriteBlock*/
    VAR(Std_ReturnType, AUTOMATIC) dataNvmGetErrorRetVal_u8;/*Return value for NvM_GetErrorStatus*/
    VAR(NvM_RequestResultType, AUTOMATIC) dataRequestResult_u8;
#endif
    VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8;/*Return value for Nvm_WriteBlock*/
    VAR(Dcm_SupportRet_t,AUTOMATIC) dataRetWriteSupport_en;    /* Return from Dcm_GetSupportOfIndex */
    VAR (uint16,  AUTOMATIC) posnDidSignal_u16;             /* Local variable for the signal position of did in terms of byte numbers*/

    /* Initilaization of local variables */
    dataSessionMask_u32  = 0x0;
    *dataNegRespCode_u8 = 0x0;
    dataRetWriteFunc_u8 = E_OK;
    dataRetWriteSupport_en = DCM_SUPPORT_OK;
    dataRetVal_u8=E_NOT_OK;
#if(DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
    /*Update the variable dataSignal_b value to FALSE*/
    dataSignal_b   = FALSE;
#endif


    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dcm_WDBIInit();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    {
        /* WDBI State Machine */
        if(Dcm_stDspStateWDBI_en == DCM_DSP_WDBI_IDLE)
        {
            /* Check for the minimum request length equal to 0x03 bytes as 2 byte DID
            and at least one byte of data record is mandatory in WDBI request */
            if(pMsgContext->reqDataLen >= DCM_DSP_WDBI_MINREQLEN)
            {
                /* Extract the DID information from the request buffer and store in Global variable to later use */
                s_dataDID_u16 = (uint16)((uint16)((uint16)((uint16)pMsgContext->reqData[0])<< (uint16)8u) | ((uint16)pMsgContext->reqData[0x1]));
                /* Check if the DID sent from tester is configured in Server s_Dcm_idxwdbiDidIndexType.idxIndex_u16 */
                dataRetGetDID_u8 = Dcm_GetIndexOfDID(s_dataDID_u16, &s_Dcm_idxwdbiDidIndexType);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                /*Check if Requested DID is configured and if the did is a range did or not */
                if ((dataRetGetDID_u8 == E_OK)&& (s_Dcm_idxwdbiDidIndexType.dataRange_b==FALSE))
                {
                    /* Check if the DID is supported in current variant */
                    if(*Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR)
                    {
                        if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].idxDIDSupportedFnc_u16]))(s_dataDID_u16)!=E_OK)
                        {
                            dataRetGetDID_u8 = E_NOT_OK;
                        }
                    }
                }
#endif
                /* Requested DID is configured */
                if(dataRetGetDID_u8 == E_OK)
                {
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
                    /*Check if the DID currently under process is a normal DID or range DID*/
                    if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
                    {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                        /* Check if the Write function is configured for all signals */
                        for(idxDidSignal_u16=0x0; idxDidSignal_u16 < Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].nrSig_u16; idxDidSignal_u16++)
                        {
                            if((Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].usePort_u8 != USE_BLOCK_ID))
                            {
                                /* Check if the DID sent from tester has Write Access */
                                if((Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessWrite_u32 >0x00u)   && (Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrDidSignalConfig_pcst[idxDidSignal_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrWriteFnc_cpv == NULL_PTR))
                                {
                                    break;
                                }
                            }
                        }
                        if(idxDidSignal_u16 == Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].nrSig_u16)
                        {   /* Move the state to next state */
                            Dcm_stDspStateWDBI_en = DCM_DSP_WDBI_VALDATALEN;
                        }
                        else
                        {   /*DID sent from tester has no Write Access - Set NRC Request Out Of Range */
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            /* Report development error "DCM_E_NO_WRITE_ACCESS " to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_WDBI_ID , DCM_E_NO_WRITE_ACCESS )
                        }
#endif
                    }
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
                    else
                    {
                        if(Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrWriteFnc_pfct != NULL_PTR)
                        {
                            /* Move the state to next state */
                            Dcm_stDspStateWDBI_en = DCM_DSP_WDBI_VALDATALEN;
                        }
                        else
                        {
                            /*DID sent from tester has no Write Access - Set NRC Request Out Of Range */
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            /* Report development error "DCM_E_NO_WRITE_ACCESS " to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_WDBI_ID , DCM_E_NO_WRITE_ACCESS )
                        }
                    }
#endif
                }
                else if(dataRetGetDID_u8 == DCM_E_PENDING)
                {
                    dataRetVal_u8=DCM_E_PENDING;
                    dataRetWriteFunc_u8=DCM_E_PENDING;
                }
                else
                {   /*DID sent from tester is incorrect - Set NRC Request Out Of Range */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
                    dataRetVal_u8=E_NOT_OK;
                }
            }
            else
            {
                /*Set NRC Request Length incorrect */
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                dataRetVal_u8=E_NOT_OK;
            }
        }

        if(Dcm_stDspStateWDBI_en == DCM_DSP_WDBI_VALDATALEN)
        {
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
            if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
            {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                adrExtendedConfig_pcst = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;
#endif
            }
            else
            {
                adrExtendedConfig_pcst = Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;
            }
#else
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
            adrExtendedConfig_pcst = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrExtendedConfig_pcst;
#endif
#endif
            /* Copy the session level for write configured */
            dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessWrite_u32;
            if (((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL))
            {
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
                /*Check if the did is a range did or not*/
                if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
                {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                    /* Copy the total valid length */
                    nrLenDataRec_u16 = (uint16)(Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataMaxDidLen_u16+2u);
                    /* Check for fixed length signals is  using ReadDataLengthFnc*/

                    if(Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataFixedLength_b != FALSE)
                    {
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                        /* Check for exact length */
                        if(pMsgContext->reqDataLen != nrLenDataRec_u16)
                        {   /*Set NRC Request Length incorrect */
                            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        }
#endif
                    }
                    else
                    {
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                        /* Check for length within max range */
                        if(pMsgContext->reqDataLen > nrLenDataRec_u16)
                        {   /*Set NRC Request Length incorrect */
                            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        }
                        else
                        {
                            /* For application to do the exact length check in case of varaible length signal */
                            if(DcmAppl_DcmCheckWDBIReqLen(s_dataDID_u16,(pMsgContext->reqDataLen-2u))!= E_OK)
                            {
                                /*Set NRC Request Length incorrect */
                                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                            }
                        }
#endif
                    }
#endif
                }
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
                else
                {
                    nrLenDataRec_u16 = (uint16)(Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataMaxDidLen_u16+2u);
                    if(pMsgContext->reqDataLen > nrLenDataRec_u16)
                    {   /*Set NRC Request Length incorrect */
                        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    }
                    else
                    {
                        /* For application to do the exact length check in case of varaible length signal */
                        if(DcmAppl_DcmCheckWDBIReqLen(s_dataDID_u16,(pMsgContext->reqDataLen-2u))!= E_OK)
                        {
                            /*Set NRC Request Length incorrect */
                            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        }
                    }
                }
#endif
            }
            else
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
            /* If Negative response is not set */
            if(*dataNegRespCode_u8 == 0)
            {   /* Move the state of WDBI to check for session and security access*/
                Dcm_stDspStateWDBI_en = DCM_DSP_WDBI_CHECKACCESS;
            }
        }
        if(Dcm_stDspStateWDBI_en == DCM_DSP_WDBI_CHECKACCESS)
        {   /* Call the function to see if there is a write support of the DID */
            dataRetWriteSupport_en = Dcm_GetSupportOfIndex(&s_Dcm_idxwdbiDidIndexType, DCM_SUPPORT_WRITE,dataNegRespCode_u8);
            /* If the conditions of writing is supported */
            if(dataRetWriteSupport_en == DCM_SUPPORT_OK)
            {   /* Move the state to Write the DID data record */
                Dcm_stDspStateWDBI_en = DCM_DSP_WDBI_WRITEDATAREC;
            }
            /* CONDITION_PENDING or SESSION_VIOLATED or SECURITY_VIOLATED or CONDITION_VIOLATED */
            else
            {   /* Nothing to do here as NRC will be set by Dcm_GetSupportOfIndex */
            }
        }

        if(Dcm_stDspStateWDBI_en == DCM_DSP_WDBI_WRITEDATAREC)
        {
            /* loop for all signals for this DID */
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
            /*Check if the did is a range did or not*/
            if(s_Dcm_idxwdbiDidIndexType.dataRange_b == FALSE)
#endif
            {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
                while((Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16) && (dataRetWriteFunc_u8 == E_OK))
                {
                    ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
                    /*Calculate the signal position of did in terms of byte numbers*/
                    posnDidSignal_u16 = (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16/8) +2);
                    /* Find the port configured for the Signal */
                    if(ptrSigConfig->idxDcmDspControlInfo_u16>0)
                    {
                        ptrWriteFnc = ptrControlSigConfig->adrWriteFnc_cpv;
                        /* Synchronous interface is used for writing */
                        if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) && (ptrWriteFnc != NULL_PTR))
                        {   /* Check if the signal is of fixed length */
#if(DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED != DCM_CFG_OFF)
                            /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                            if(ptrDidConfig->dataFixedLength_b != FALSE)
                            {   /* Call function to check if conditions are fulfilled to write the DID */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                                dataRetWriteFunc_u8 = (*(WdbiFnc2_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16], dataNegRespCode_u8);
#endif
                            }
                            else
                            {   /* Call function to check if conditions are fulfilled to write the DID */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                                dataRetWriteFunc_u8 = (*(WdbiFnc1_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16],(uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);
#endif
                            }
#endif
                        }
#if(DCM_CFG_DSP_WRITE_SYNCH_FNC_ENABLED != DCM_CFG_OFF)
                        else if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC )&& (ptrWriteFnc != NULL_PTR))
                        {
                            /* Check if the signal is of fixed length */

                            if(ptrSigConfig->dataFixedLength_b != FALSE)
                            {   /* Call function to check if conditions are fulfilled to write the DID */
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc19_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16], dataNegRespCode_u8);
#endif
                            }
                            else
                            {   /* Call function to check if conditions are fulfilled to write the DID */
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc18_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16],(uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);
#endif
                            }
                        }
#endif
                        /* Asynchronous interface is used for writing */
#if(DCM_CFG_DSP_WRITE_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)
                        else if((ptrWriteFnc != NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                        ))
                        {
                            /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                            if(ptrSigConfig->dataFixedLength_b != FALSE)
                            {   /* Call function to check if conditions are fulfilled to write the DID */
#if(DCM_CFG_DSP_WRITE_FIXED_LENGTH != DCM_CFG_OFF)
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc4_pfct)(ptrWriteFnc))   (&pMsgContext->reqData[posnDidSignal_u16],Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
#endif
                            }
                            else
                            {   /* Call function to check if conditions are fulfilled to write the DID */
#if(DCM_CFG_DSP_WRITE_VARIABLE_LENGTH != DCM_CFG_OFF)
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc3_pfct)(ptrWriteFnc))   (&pMsgContext->reqData[posnDidSignal_u16],(uint16)(pMsgContext->reqDataLen-0x02u),Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
#endif
                            }
                        }
#endif
#if(DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF)
                        else if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrWriteFnc != NULL_PTR))
                        {
                            /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                            if(ptrSigConfig->dataFixedLength_b != FALSE)
                            {   /* Call function to check if conditions are fulfilled to write the DID */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc21_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16],Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
                            }
                            else
                            {   /* Call function to check if conditions are fulfilled to write the DID */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetWriteFunc_u8 = (*(WdbiFnc20_pfct)(ptrWriteFnc)) (&pMsgContext->reqData[posnDidSignal_u16],(uint16)(pMsgContext->reqDataLen-0x02u),Dcm_stDspWdbiOpStatus_u8,dataNegRespCode_u8);
                            }
                        }
#endif
                        else
                        {   /* Sender Receiver interface is used for writing */
#if(DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF)
                            if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) && (ptrWriteFnc != NULL_PTR))
                            {
                                /* Check for the Type of the signal */
                                switch(ptrSigConfig->dataType_u8)
                                {
#if(DCM_CFG_DSP_WRITE_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_BOOLEAN: /* boolean signal */
                                    {
                                        /* Get the signal value from the request buffer */
                                        dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                        /* Check if the signal value if True/false */
                                        if(dataSignal_u32 != 0u)
                                        {
                                            /*Set the variable dataSignal_b to TRUE*/
                                            dataSignal_b = TRUE;
                                        }
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataRetWriteFunc_u8 = (*(WdbiFnc5_pfct)(ptrWriteFnc))(dataSignal_b);
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_UINT8_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT8:
                                    {   /* Check if the signal is array of UINT8 signals */
                                        if(ptrSigConfig->dataSize_u16 == 8)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* Extract uint8 value from uint32 */
                                            dataSignal_u8 = (uint8)dataSignal_u32;
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc6_pfct)(ptrWriteFnc))(dataSignal_u8);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of UINT8 signal */
                                            nrElements_u16 = (uint16)((uint32)(Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].dataSize_u16)/8u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16 +(uint16)(idxLoop_u16*8)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_au8[idxLoop_u16]=(uint8)dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc12_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_UINT16_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT16:
                                    {   /* Calculate the number of elements in the Array of UINT16 signal */
                                        if(ptrSigConfig->dataSize_u16 == 16)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* Extract uint16 value from uint32 */
                                            dataSignal_u16 = (uint16)dataSignal_u32;
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc7_pfct)(ptrWriteFnc))(dataSignal_u16);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of UINT16 signal */
                                            nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16 +(uint16)(idxLoop_u16*16)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_au16[idxLoop_u16]=(uint16)dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc13_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au16);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_UINT32_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_UINT32:
                                    {   /* Calculate the number of elements in the Array of UINT32 signal */
                                        if(ptrSigConfig->dataSize_u16 == 32)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc8_pfct)(ptrWriteFnc))(dataSignal_u32);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of UINT32 signal */
                                            nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_au32[idxLoop_u16]=dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc14_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_au32);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_SINT8_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT8:
                                    {   /* Check if the signal is array of SINT8 signals */
                                        if(ptrSigConfig->dataSize_u16 == 8)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* Extract sint8 value from uint32 */
                                            dataSignal_s8 = (sint8)dataSignal_u32;
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc9_pfct)(ptrWriteFnc))(dataSignal_s8);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of SINT8 signal */
                                            nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/8u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_as8[idxLoop_u16]=(sint8)dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc15_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as8);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_SINT16_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT16:
                                    {   /* Check if the signal is array of SINT16 signals */
                                        if(ptrSigConfig->dataSize_u16 == 16)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* Extract sint16 value from uint32 */
                                            dataSignal_s16 = (sint16)dataSignal_u32;
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc10_pfct)(ptrWriteFnc))(dataSignal_s16);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of SINT16 signal */
                                            nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_as16[idxLoop_u16]=(sint16)dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc16_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as16);
                                        }
                                        break;
                                    }
#endif
#if(DCM_CFG_DSP_WRITE_SINT32_SR_ENABLED != DCM_CFG_OFF)
                                    case DCM_SINT32:
                                    {   /* Check if the signal is array of SINT32 signals */
                                        if(ptrSigConfig->dataSize_u16 == 32)
                                        {   /* Get the signal value from the request buffer */
                                            dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                            /* Extract sint32 value from uint32 */
                                            dataSignal_s32 = (sint32)dataSignal_u32;
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc11_pfct)(ptrWriteFnc))(dataSignal_s32);
                                        }
                                        else
                                        {   /* Calculate the number of elements in the Array of SINT32 signal */
                                            nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);
                                            idxLoop_u16 = 0;
                                            do
                                            {   /* Get the signal value from the request buffer */
                                                dataSignal_u32 = Dcm_GetSignal_u32(ptrSigConfig->dataType_u8,(ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32)),&pMsgContext->reqData[0x02],ptrSigConfig->dataEndianness_u8);
                                                /* Copy the part of the signal to the local Signal array */
                                                Dcm_DspArraySignal_as32[idxLoop_u16]=(sint32)dataSignal_u32;
                                                idxLoop_u16++;
                                                /* loop for all the elements of the signal */
                                            }while((idxLoop_u16 < nrElements_u16));
                                            /* Call the configured callback to write the signal */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataRetWriteFunc_u8 = (*(WdbiFnc17_pfct)(ptrWriteFnc))(Dcm_DspArraySignal_as32);
                                        }
                                        break;
                                    }
#endif
                                    default:
                                    {   /* No operation */
                                        break;
                                    }
                                }
                            }
#endif
                        }

                        if(dataRetWriteFunc_u8 != E_OK)
                        {
                            /*MR12 RULE 13.5 VIOLATION:Right hand operand of '&&' or '||' is an expression with possible side effects. MISRA C:2012 Rule-13.5*/
                            if (((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)) && (Dcm_IsInfrastructureErrorPresent_b(dataRetWriteFunc_u8) != FALSE))
                            {
#if((DCM_CFG_DSP_WRITE_ASYNCH_CS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SYNCH_CS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF))
                                /* General Reject is sent when there is Infrastructure error */
                                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                dataRetWriteFunc_u8 = DCM_INFRASTRUCTURE_ERROR;
#endif
                            }
                            break;
                        }
                        else
                        {
                            *dataNegRespCode_u8=0x00;
                        }
                    }
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                    else if((ptrSigConfig->usePort_u8 == USE_BLOCK_ID))
                    {
                        /*Check if the flag Dcm_flgNvmWritePending_b is set to FALSE*/
                        if(Dcm_flgNvmWritePending_b ==FALSE)
                        {

                            NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,FALSE);
                            /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as NvM_WriteBlock takes void pointer as input and object type pointer is converted to void pointer*/
                            dataNvmWriteBlockRetVal_u8=NvM_WriteBlock(ptrSigConfig->dataNvmBlockId_u16,&pMsgContext->reqData[posnDidSignal_u16]);
                            if(dataNvmWriteBlockRetVal_u8 != E_OK)
                            {
                                /* According to  ISO 14229-1;2013 - General Programming failure has to be returned in case of NvmWrite Failure */
                                *dataNegRespCode_u8 =DCM_E_GENERALPROGRAMMINGFAILURE;
                                /*Set the flag Dcm_flgNvmWritePending_b is to FALSE*/
                                Dcm_flgNvmWritePending_b=FALSE;
                                /* Locking the unlocked block */
                                NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
                            }
                            else
                            {
                                /*Set the flag Dcm_flgNvmWritePending_b to TRUE*/
                                Dcm_flgNvmWritePending_b=TRUE;
                                dataRetWriteFunc_u8 =DCM_E_PENDING;
                            }
                            /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                            break;
                        }
                        else
                        {
                            dataNvmGetErrorRetVal_u8= NvM_GetErrorStatus(ptrSigConfig->dataNvmBlockId_u16,&dataRequestResult_u8);
                            /*Set the flag Dcm_flgNvmWritePending_b to FALSE*/
                            Dcm_flgNvmWritePending_b = FALSE;
                            if(dataNvmGetErrorRetVal_u8 != E_OK)
                            {
                                /* According to  ISO 14229-1;2013 - General Programming failure has to be returned in case of NvmWrite Failure */
                                *dataNegRespCode_u8 =DCM_E_GENERALPROGRAMMINGFAILURE;
                                /* Locking the unlocked block */
                                NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
                                /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                                break;
                            }
                            else
                            {
                                if(dataRequestResult_u8 == NVM_REQ_PENDING)
                                {
                                    /*Set the flag Dcm_flgNvmWritePending_b to TRUE*/
                                    Dcm_flgNvmWritePending_b = TRUE;
                                    dataRetWriteFunc_u8 = DCM_E_PENDING;
                                }
                                else if(dataRequestResult_u8==NVM_REQ_OK)
                                {
                                    dataRetWriteFunc_u8 =E_OK;
                                }
                                else
                                {
                                    /* According to  ISO 14229-1;2013 - General Programming failure has to be returned in case of any Nvm Failure */
                                    *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
                                }
                            }
                            if((dataRequestResult_u8 != NVM_REQ_PENDING) && (dataNvmGetErrorRetVal_u8==E_OK))
                            {
                                /* Locking the unlocked block */
                                NvM_SetBlockLockStatus(ptrSigConfig->dataNvmBlockId_u16,TRUE);
                            }
                            if(dataRequestResult_u8!=NVM_REQ_OK)
                            {
                                /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                                break;
                            }

                        }
                    }
#endif
                    else
                    {

                    }
				Dcm_DidSignalIdx_u16++;	
                }

#endif
            }
#if (DCM_CFG_DIDRANGE_EXTENSION!=DCM_CFG_OFF)
            else
            {
                ptrDidRangeConfig = &Dcm_DIDRangeConfig_cast[s_Dcm_idxwdbiDidIndexType.idxIndex_u16];
                ptrWriteFnc = ptrDidRangeConfig->adrWriteFnc_pfct;
                if(ptrWriteFnc != NULL_PTR)
                {
                    /*Check if Fixed length or obtainable using ReadDataLengthFnc*/
                    if(ptrDidRangeConfig->nrRangeUsePort_b != FALSE)
                    {
                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetWriteFunc_u8 = (*(WriteFncRange1_pfct)(ptrWriteFnc))(s_dataDID_u16,&pMsgContext->reqData[0x2],Dcm_stDspWdbiOpStatus_u8,(uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);
                        /* Check for infrastructure error  incase of case RTE use ports */

                        if((Dcm_IsInfrastructureErrorPresent_b(dataRetWriteFunc_u8) != FALSE) &&(ptrDidRangeConfig->nrRangeUsePort_b != FALSE))
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                            Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
                        }
                    }
                    else
                    {
                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetWriteFunc_u8 = (*(WriteFncRange2_pfct)(ptrWriteFnc))(s_dataDID_u16,&pMsgContext->reqData[0x2],Dcm_stDspWdbiOpStatus_u8,(uint16)(pMsgContext->reqDataLen-0x02u),dataNegRespCode_u8);
                    }
                }
            }
#endif
        }

        if( (dataRetWriteFunc_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00) )
        {   /* Frame the positive response by updating DID in response buffer */
            pMsgContext->resData[0] = pMsgContext->reqData[0];
            pMsgContext->resData[1] = pMsgContext->reqData[1];
            pMsgContext->resDataLen = 0x02;
            /* Reset the state of WDBI state machine to IDLE */
            Dcm_stDspStateWDBI_en  = DCM_DSP_WDBI_IDLE;
            Dcm_DidSignalIdx_u16 = 0x0;
            Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
            dataRetVal_u8=E_OK;
        }
        /* If the write Function needs more time for writing */
        else if((dataRetWriteFunc_u8 == DCM_E_PENDING) || (dataRetWriteSupport_en == DCM_SUPPORT_CONDITION_PENDING))
        {
            /* Remain in the same state, Write function will be called again in next cycle */
            Dcm_stDspWdbiOpStatus_u8 = DCM_PENDING;
            *dataNegRespCode_u8=0x00;
            dataRetVal_u8=DCM_E_PENDING;
        }
        else /* Return is E_NOT_OK */
        {   /*Set Negative response code to DCM_E_GENERALREJECT*/
            if(*dataNegRespCode_u8 == 0x00)
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }

            Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
            dataRetVal_u8=E_NOT_OK;
        }

        /* Check if Negative response is set */
        if(*dataNegRespCode_u8 != 0x0)
        {
            dataRetVal_u8=E_NOT_OK;
            /* Reset the state of WDBI state machine to IDLE */
            Dcm_stDspStateWDBI_en  = DCM_DSP_WDBI_IDLE;
            Dcm_DidSignalIdx_u16 = 0x0;
            Dcm_stDspWdbiOpStatus_u8 = DCM_INITIAL;
        }
    }
        return dataRetVal_u8;
}

/**
 *************************************************************************************************************************************************************
 * Dcm_GetActiveWDBIDid:
 *
 * This API returns the active DID being processed when WDBI service request is being processed. This function is called from the Dcm API Dcm_GetActiveDid
 *
 *
 * \param     uint16* dataDid_u16 : Parameter for updating of the DID under processing. The DID value returned is valid only if return value is E_OK.
 * \retval    Std_ReturnType : E_OK : The DID under processing is a normal DID.The parameter dataDid_u16 contains valid DID value in this case.
 *                             E_NOT_OK: The DID under processing is a range DID. The parameter dataDid_u16 contains invalid data in this case.
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveWDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8; /* Variable to store the return value */

    /* Initialisation of local variables  */
    dataRetVal_u8 = E_NOT_OK;

    /* Check if the DID currently under process is a normal DID */

    if(s_Dcm_idxwdbiDidIndexType.dataRange_b==FALSE)
    {
        /* Update the DID value currently under process */
        *dataDid_u16 = Dcm_DIDConfig[s_Dcm_idxwdbiDidIndexType.idxIndex_u16].dataDid_u16;
        /* Update the return value to E_OK */
        dataRetVal_u8 = E_OK;
    }
    else
    {
#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
        /* Update the DID value currently under process */
        *dataDid_u16 = s_Dcm_idxwdbiDidIndexType.dataRangeDid_16;
        /* Update the return value to E_OK */
        dataRetVal_u8 = E_OK;
#endif
    }
    return (dataRetVal_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
