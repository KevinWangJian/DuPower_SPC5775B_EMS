

#include "DcmDspUds_RequestTransferExit_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRequestTranferExitOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

/**
 **************************************************************************************************
 * Dcm_Dsp_RequestTransferExit_Ini : Initialisation function for RequestTransferExit  (0x37) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_Dsp_RequestTransferExit_Ini (void)
{
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8;   /* Variable to store Negative response code                   */
    VAR(uint32,AUTOMATIC) transferResponseParameterRecordSize_u32;   /* Variable to store the transferResponseParameterRecord size */

    /* Cancel in the operation in case Opstatus is DCM_PENDING */
    if(Dcm_stRequestTranferExitOpstatus_u8 == DCM_PENDING)
    {
        /* Call the DcmAppl API to do the cancellation with Opstatus as DCM_CANCEL */
        (void)DcmAppl_Dcm_ProcessRequestTransferExit( DCM_CANCEL,NULL_PTR,0,NULL_PTR,&transferResponseParameterRecordSize_u32,&dataNegResCode_u8);
        (void)dataNegResCode_u8;
        (void)transferResponseParameterRecordSize_u32;
    }
    /* Reset of opstatus to INITIAL */
    Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;
    /* Call the API to complete the transfer of data */
    Dcm_DspDeactivateRequestUploadDownloadPermission();
}


/**
 **************************************************************************************************
 * Dcm_DcmRequestTransferExit : Service handler for RequestTransferExit service (0x37) . The service
 * is used to terminate the upload or download of data between client and server
 *
 * \param           pMsgContext: Pointer to message structure
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmRequestTransferExit (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC)  dataRetVal_u8;                    /* Variable to store the return Value                         */
    VAR(uint32,AUTOMATIC) transferRequestParameterRecordSize_u32;    /* Variable to store the transferRequestParameterRecord size  */
    VAR(uint32,AUTOMATIC) transferResponseParameterRecordSize_u32;   /* Variable to store the transferResponseParameterRecord size */
    VAR(boolean,AUTOMATIC) getDownloadStatus_b = FALSE;
    VAR(boolean,AUTOMATIC) getUploadStatus_b = FALSE;
    /* Initialization of variables to 0 */
    *dataNegRespCode_u8 = 0x00;
    transferResponseParameterRecordSize_u32 = 0x00;
    dataRetVal_u8=DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_RequestTransferExit_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    {
        /* If upload is already active and the complete transfer of data is over */

        getUploadStatus_b = Dcm_GetRequestUploadStatus();
        getDownloadStatus_b = Dcm_GetRequestDownloadStatus();

        if((getUploadStatus_b != FALSE )||(getDownloadStatus_b != FALSE ))
        {
            if((Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32 != Dcm_DataTransfer_st.dataMemorySize_u32))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
            }
            else if(*dataNegRespCode_u8==0)
            {
                /* Get the length of transferRequestParameterRecordSize in the request */
                transferRequestParameterRecordSize_u32 = pMsgContext->reqDataLen;
                /* If the transferRequestParameterRecord is  present in the request call the DcmAppl API with the request record and size*/
                if(transferRequestParameterRecordSize_u32 >0u)
                {
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8,
                            &pMsgContext->reqData[0],
                            transferRequestParameterRecordSize_u32,
                            &pMsgContext->resData[0],
                            &transferResponseParameterRecordSize_u32,
                            dataNegRespCode_u8);
                }
                /* If the transferRequestParameterRecord is not present in the request call the DcmAppl API with transferRequestParameterRecord as NULL_PTR and
                 *  transferRequestParameterRecordSize as 0 */
                else
                {
                    dataRetVal_u8 = DcmAppl_Dcm_ProcessRequestTransferExit(  Dcm_stRequestTranferExitOpstatus_u8,
                            NULL_PTR,
                            0,
                            &pMsgContext->resData[0],
                            &transferResponseParameterRecordSize_u32,
                            dataNegRespCode_u8);
                }
                /* If negative response is not set by the application*/

                /* If application returns E_OK */
                if(dataRetVal_u8==E_OK)
                {
                    *dataNegRespCode_u8=0x00;
                    /* Reset the OpStatus to INITIAL */
                    Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;

                    /* If length of the transferResponseParameterRecord is greater than the available response buffer */
                    if(transferResponseParameterRecordSize_u32>pMsgContext->resMaxDataLen)
                    {
                        *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                        /* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW" to DET module if the DET module is enabled */
                        DCM_DET_ERROR(DCM_TRANSFEREXIT_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                    }
                    else
                    {
                        /* Update the response data length to indicate the length of the transferResponseParameterRecord */
                        pMsgContext->resDataLen=transferResponseParameterRecordSize_u32;
                    }
                }
                /* If application needs more time for processing*/
                else if(dataRetVal_u8==DCM_E_PENDING)
                {
                    *dataNegRespCode_u8=0x00;
                    /* Set the Opstatus to DCM_PENDING */
                    Dcm_stRequestTranferExitOpstatus_u8 = DCM_PENDING;
                }
                /* Fo any other return values */
                else
                {
                    if(*dataNegRespCode_u8==0x00)
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }

                }
            }
            else
            {
                /* dummy else */
            }
        }
        /* If RequestUpload is not active or TansferData is not complete */
        else
        {
            *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
        }

        /* If negative response code is set */
        if(*dataNegRespCode_u8!=0x00)
        {
            /* Reset the Opstatus to INITIAL */
            Dcm_stRequestTranferExitOpstatus_u8 = DCM_INITIAL;
            /* Cancelling upload/download sequence */
            Dcm_DspDeactivateRequestUploadDownloadPermission();
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

