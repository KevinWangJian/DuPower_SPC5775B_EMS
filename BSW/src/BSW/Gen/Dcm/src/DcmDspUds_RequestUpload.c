

#include "DcmDspUds_RequestUpload_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_RequestUpload_Priv.h"
/* Global varibale declaration */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspRequestUploadStates_ten,DCM_VAR) Dcm_stDspStateRequestUpload_en;   /* RequestUpload state */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint32,            DCM_VAR) Dcm_dataMemoryAddress_u32; /*Variable to store the memory address requested by the tester*/
static VAR(uint32,            DCM_VAR) Dcm_dataMemoryLength_u32;  /*Variable to store the memory length requested by the tester*/
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR (uint8,  DCM_VAR) Dcm_dataMemdatasize_u8;                /* Variable for storing the length of memory size */

static VAR (uint8,  DCM_VAR) Dcm_dataMemaddrsize_u8;                /* Variable for storing the memory address size*/
static VAR (uint8,  DCM_VAR) Dcm_dataFormatIdentifier_u8;           /* Variable for storing the dataFormatIdentifier in tester request */
static VAR(uint8,   DCM_VAR) s_dataCompressionMethod_u8;                 /* Variable to store the compression method in tester request */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRequestUploadOpstatus_u8; /* Variable to store the RequestUpload opstatus*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_RequestUpload_Ini : Initialisation function for RequestUpload  (0x35) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_Dsp_RequestUpload_Ini (void)
{
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8; /* Variable to store Negative response code */
    VAR(uint32,AUTOMATIC)  dataBlockLength_u32;                    /* Variable to store the block length returned by application */

    /* Cancel in the operation in case Opstatus is DCM_PENDING */
    if(Dcm_stRequestUploadOpstatus_u8 == DCM_PENDING)
    {
        /* Call the DcmAppl API to do the cancellation with Opstatus as DCM_CANCEL */
        (void)DcmAppl_Dcm_ProcessRequestUpload(DCM_CANCEL,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)dataBlockLength_u32;
    }
    /* Reset of opstatus , RequestUpload state machine and upload status*/
    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
    Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_IDLE;
    Dcm_DspDeactivateRequestUploadDownloadPermission();
}


/**
 **************************************************************************************************
 * Dcm_GetIndexOfRequestUploadMemory_u8 : Function to check if the memory address is supported and
 * memprySize is within the supported range
 *
 * \param[in]           dataMemAddr_u32 :MemoryAddress where data is to be read
 * \param[in]           nrMemLength_u32 : Length of data to be read
 * \param[out]          idxIndex_u16    :Index of the memory range in which memoryAddress lies
 *
 * \retval          Std_ReturnType E_OK : If the memory range is supported and memory size is valid
 *                                 DCM_E_REQUEST_NOT_ACCEPTED :If the memory range is not supported or memory size is invalid
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfRequestUploadMemory_u8(VAR   (uint32,AUTOMATIC) dataMemAddr_u32,
                                                                           VAR   (uint32,AUTOMATIC) nrMemLength_u32,
                                                                           P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16);
static FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfRequestUploadMemory_u8(VAR   (uint32,AUTOMATIC) dataMemAddr_u32,
                                                                           VAR   (uint32,AUTOMATIC) nrMemLength_u32,
                                                                           P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16)
{

    VAR (uint16,         AUTOMATIC) dataSize_u16;
    VAR (uint16,         AUTOMATIC) idxLoop_u16;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;
    /* Calculate the size of the RequestUpload Structure generated */
    dataSize_u16 = Dcm_RequestUploadCalculateTableSize_u16();

    if(0u != nrMemLength_u32)
    {
        /* Loop through the memoryRanges configured to see if the memoryAddress and memorySize is supported */
         for(idxLoop_u16 = 0;idxLoop_u16<dataSize_u16;idxLoop_u16++)
        {
             if((dataMemAddr_u32 >= Dcm_RequestUploadConfig_cast[idxLoop_u16].dataRequestUploadMemoryRangeLow_u32) && ((dataMemAddr_u32 + (nrMemLength_u32-1u))<=(Dcm_RequestUploadConfig_cast[idxLoop_u16].dataRequestUploadMemoryRangeHigh_u32)))
             {
                 *idxIndex_u16 = idxLoop_u16;
                 dataRetVal_u8 = E_OK;
                 Dcm_DataTransfer_st.dataMemoryIdentifier_u8 = Dcm_RequestUploadConfig_cast[idxLoop_u16].dataMemoryValue_u8;
                 break;
             }
        }
    }
     return (dataRetVal_u8);
}



/**
 **************************************************************************************************
 * Dcm_DcmRequestUpload : Function to implement RequestUpload Service (0x35) according to Autosar
 * specifications.
 *
 * \param           pMsgContext: Pointer to message structure
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmRequestUpload (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint8,AUTOMATIC) dataEncryptionMethod_u8;                  /* Variable to store the encryption method in tester request  */
    VAR(Std_ReturnType,AUTOMATIC)  dataretVal_u8 = E_NOT_OK;       /* Variable to store the returnType from DcmAppl API          */
    VAR(uint16,AUTOMATIC) idxIndex_u16 = 0u;                            /* Variable to store the index of memory range                */
    VAR(uint32,AUTOMATIC)  dataBlockLength_u32;                    /* Variable to store the block length returned by application */

    /* Initialize the error code to 0x00 */
    *dataNegRespCode_u8 =0x00;
    dataBlockLength_u32=0x00;
	s_dataCompressionMethod_u8 = 0x00;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_RequestUpload_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataretVal_u8 = E_OK;
    }
    else
    {
        /* If statemachine is in IDLE state */
        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_IDLE)
        {
            /* Minimum Length check */
            if(pMsgContext->reqDataLen >= DCM_DSP_REQUESTUPLOAD_MINREQLEN)
            {
                /* Extract the DataFormatIdentifier from the tester request */
                Dcm_dataFormatIdentifier_u8 = pMsgContext->reqData[0];
                /* Extract the encryption method from the lower nibble of dataFormatIdentifier present in the first byte after SID  */
                dataEncryptionMethod_u8 = (Dcm_dataFormatIdentifier_u8& (0xFu));
                /* Extract the compression method from the higher nibble of dataFormatIdentifier present in the first byte after SID  */
                s_dataCompressionMethod_u8 = (uint8)((Dcm_dataFormatIdentifier_u8 & (0xF0u))>>4u);

                /* Call the DcmAppl API to check if the compression and encryption method passed in the dataFormatIdentifier is valid */
                dataretVal_u8 = DcmAppl_CheckEncryptionCompressionMethod (0x35,s_dataCompressionMethod_u8,dataEncryptionMethod_u8);
                /* If the function returns E_OK and also the memoryAddress size and memoryData size is atleast 1 byte and less than or equal to 4 bytes */
                if(dataretVal_u8==E_OK)
                {
                    /* Extract the MemoryAddess size  from the lower nibble of addressAndLengthFormatIdentifier present in the second byte after SID  */
                    Dcm_dataMemaddrsize_u8 = ((pMsgContext->reqData[1])& (0xFu));
                    /* Extract the size of the data from the higher nibble of addressAndLengthFormatIdentifier present in the second byte after SID  */
                    Dcm_dataMemdatasize_u8 = (uint8)(((pMsgContext->reqData[1])& (0xF0u))>>4u);

                    if ((0u!=Dcm_dataMemaddrsize_u8)&&(0u!=Dcm_dataMemdatasize_u8)&&(Dcm_dataMemdatasize_u8 <=4u)&&(Dcm_dataMemaddrsize_u8<=4u))
                    {
                        /*Total Length Check, 1 added is for the address length field format identifier field*/
                    if(pMsgContext->reqDataLen == (Dcm_dataMemaddrsize_u8 + Dcm_dataMemdatasize_u8 + 2u))
                    {
                        /*Calculate the Memory address to write requested by the tester*/
                        Dcm_GetMemoryInfo(Dcm_dataMemaddrsize_u8,&(pMsgContext->reqData[2]),&Dcm_dataMemoryAddress_u32);
                        /*Calculate the memory size requested by the tester*/
                        Dcm_GetMemoryInfo(Dcm_dataMemdatasize_u8,&(pMsgContext->reqData[Dcm_dataMemaddrsize_u8+2]),&Dcm_dataMemoryLength_u32);
                        /* Check if the Memory Address sent from tester is configured in the Server and memorySize is within the configured range */
                        dataretVal_u8 = Dcm_GetIndexOfRequestUploadMemory_u8(Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&idxIndex_u16);
                        /* If the memoryAddress is within the limits */
                        if(E_OK == dataretVal_u8)
                        {
                            /* Check if the Read is allowed in the active security level*/
                            if ((Dcm_DsldGetActiveSecurityMask_u32 () &  Dcm_RequestUploadConfig_cast[idxIndex_u16].dataAllowedSec_u32) != 0x0uL)
                            {
#if( DCM_CFG_DSP_REQUESTUPLOAD_SEQUENCECHECK_ENABLED !=DCM_CFG_OFF)
                               /* Check if RequestUpload is already active */

                                if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE) || (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
                                {
                                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                                }
                                /* Set NRC if request upload is already active */
                                else
#endif
                                {
                                    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
                                    Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_GETBLOCKNUM;
                                }
                            }
                            /* Set NRC if security access is denied to read the memory range */
                            else
                            {
                                *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                            }
                        }
                        /*Set NRC 0x31 Memory address is not configured or it is outside the boundaries of lower and upper limits configured */
                        else
                        {
                              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    else
                    {
                        /*Set NRC 0x31 Total Length check has failed */
                        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                        }
                    }
                    else
                    {
                        /*Incorrect addressLengthFormatIdentifier parameterst */
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else if(dataretVal_u8 == DCM_E_PENDING)
                {
                    /* Be in the same state as the application has returned E_PENDING */
                }
                else
                {
                    /*Incorrect dataFormatIdentifier - encryption and compression method - NRC 0x31 is set */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
            }
            else
            {
                /*Set NRC Request Length incorrect */
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
            /* If NRC is set in the above checks,update state machine to send negative response */
            if (*dataNegRespCode_u8!=0x00)
            {
                Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_ERROR;
            }
        }

        /* The state to call application for condition checks and to get the BlockLength */
        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_GETBLOCKNUM)
        {
            /* Call the DcmAppl API for the application to do the conditions checks and to retrieve the block length of each TranferData request from the application */
            dataretVal_u8 = DcmAppl_Dcm_ProcessRequestUpload(Dcm_stRequestUploadOpstatus_u8,Dcm_dataFormatIdentifier_u8,Dcm_dataMemoryAddress_u32,Dcm_dataMemoryLength_u32,&dataBlockLength_u32,dataNegRespCode_u8);

                /* If the application returns OK */
                if(dataretVal_u8==E_OK)
                {

                    *dataNegRespCode_u8=0x00;
                    Dcm_DataTransfer_st.dataMaxBlockLength_u32  = dataBlockLength_u32;
                    Dcm_DataTransfer_st.dataMemoryAddress_u32   = Dcm_dataMemoryAddress_u32;
                    Dcm_DataTransfer_st.dataMemorySize_u32      = Dcm_dataMemoryLength_u32;
                    Dcm_DataTransfer_st.compressionMethod_u8	= s_dataCompressionMethod_u8;
                    dataretVal_u8=E_OK;
                    /* Reset the state back to idle */
                    Dcm_stDspStateRequestUpload_en=DCM_DSP_REQUESTUPLOAD_IDLE;
                    Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
                    /* Logic for getting response bytes */
                    if(dataBlockLength_u32<=0xFFu)
                    {
                        pMsgContext->resData[0]=0x10;
                        pMsgContext->resData[1]=(uint8)dataBlockLength_u32;
                        pMsgContext->resDataLen=0x02;
                    }
                    else if(dataBlockLength_u32<=0xFFFFuL)
                    {
                        pMsgContext->resData[0]=0x20;
                        pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>8u);
                        pMsgContext->resData[2]=(uint8)dataBlockLength_u32;
                        pMsgContext->resDataLen=0x03;
                    }
                    else if(dataBlockLength_u32<=0xFFFFFFuL)
                    {
                        pMsgContext->resData[0]=0x30;
                        pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>16u);
                        pMsgContext->resData[2]= (uint8)(dataBlockLength_u32>>8u);
                        pMsgContext->resData[3]=(uint8)dataBlockLength_u32;
                        pMsgContext->resDataLen=0x04;
                    }
                    else
                    {
                        pMsgContext->resData[0]=0x40;
                        pMsgContext->resData[1]= (uint8)(dataBlockLength_u32>>24u);
                        pMsgContext->resData[2]= (uint8)(dataBlockLength_u32>>16u);
                        pMsgContext->resData[3]= (uint8)(dataBlockLength_u32>>8u);
                        pMsgContext->resData[4]= (uint8)dataBlockLength_u32;
                        pMsgContext->resDataLen=0x05;
                    }
                }
                /* If application needs more time for processing, update the Opstatus to PENDING */
                else if(dataretVal_u8==DCM_E_PENDING)
                {
                    *dataNegRespCode_u8=0x00;
                    Dcm_stRequestUploadOpstatus_u8 = DCM_PENDING;
                    /* Do nothing as state is unchanged */
                }
                /* If application returns any value other than E_OK and E_PENDING */
                else
                {
                    if(*dataNegRespCode_u8 == 0x00u)
                    {
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                }
            /* If NRC is set by application , reset the Opstatus to INITIAL state  and update state machine to send negative response*/
            if(*dataNegRespCode_u8!=0x00u)
            {
                Dcm_stDspStateRequestUpload_en = DCM_DSP_REQUESTUPLOAD_ERROR;
            }
        }
        /* State to send negative response code to the tester */
        if(Dcm_stDspStateRequestUpload_en==DCM_DSP_REQUESTUPLOAD_ERROR)
        {
            Dcm_stRequestUploadOpstatus_u8 = DCM_INITIAL;
            /* Reset the state of WMBA state machine to IDLE */
            Dcm_stDspStateRequestUpload_en=DCM_DSP_REQUESTUPLOAD_IDLE;
            dataretVal_u8=E_NOT_OK;

        }
    }
    return dataretVal_u8;
}



/**
 ***********************************************************************************************************************
 * Dcm_DspActivateRequestUploadPermission :Function called to start the permission for Transfer Data after RequestUpload
 * and set the necessary global variables
 *
 * \param           void:
 *
 * \retval          None
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_DspActivateRequestUploadPermission(void)
{
    /*Initialize RequestUpload is to TRUE*/
    Dcm_DataTransfer_st.isUploadStarted_b  = TRUE;
    /*Initialize RequestDownload to FALSE*/
    Dcm_DataTransfer_st.isDownloadStarted_b  = FALSE;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_UpdateTransferRequestCount();
}
/**
 *******************************************************************************
 * Dcm_Prv_DspReqUploadConfirmation : API used for confirmation of response sent   
 *										     for   RequestUpload (0x35) service.
 * \param           dataIdContext_u8    Service Id 
 * \param           dataRxPduId_u8      PDU Id on which request is Received
 * \param           dataSourceAddress_u16    Tester Source address id
 * \param           status_u8                Status of Tx confirmation function
 *
 * \retval          None
 * \seealso
 *
 *******************************************************************************
 */
 FUNC(void, DCM_CODE) Dcm_Prv_DspReqUploadConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspActivateRequestUploadPermission();
            }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																	status_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

