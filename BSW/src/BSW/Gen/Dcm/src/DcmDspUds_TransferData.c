

#include "DcmDspUds_TransferData_Inf.h"
#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#include "DcmDspUds_TransferData_Priv.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DataTransfer_tst,AUTOMATIC) Dcm_DataTransfer_st;
static VAR(Dcm_DspTransferDataStates_ten,       DCM_VAR  ) s_stTransferDataState_en; /*State machine control variable for TransferData service*/
VAR (Dcm_TransferData_tst,DCM_VAR) Dcm_TransferData_st;     /* TransferData structure to store all the required parameters */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint32,DCM_VAR) s_dataCurrentBlockSize_u32; /* The variable to store the size of the block requested */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) s_stTransferOpstatus_u8;     /* opstatus for handling transfer Data */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
static FUNC(uint32,DCM_CODE) Dcm_GetLastBlockSize(void);
#endif
static FUNC(Std_ReturnType,AUTOMATIC)Dcm_CheckNRCfromApplication(VAR(uint32,AUTOMATIC) dataLengthReceived_u32,
                                                                 P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8);
/**
 **************************************************************************************************
 * Dcm_Dsp_TransferDataIni : Initialisation function for TransferData (0x36) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_Dsp_TransferDataIni(void)
{
    /* Canceling the read operation if INI of the service is called */
    if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isUploadStarted_b != FALSE))
    {
        /* canceling the read operation if INI is called due to general reject behaviour */
        (void)(DcmAppl_Dcm_ReadMemory(DCM_CANCEL,
                                      Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                      Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                      s_dataCurrentBlockSize_u32,
                                      NULL_PTR,
                                      NULL_PTR));
    }

    else if((DCM_PENDING == s_stTransferOpstatus_u8 ) && (Dcm_DataTransfer_st.isDownloadStarted_b != FALSE))
    {
        /* canceling the read operation if INI is called due to general reject behaviour */
        (void)(DcmAppl_Dcm_WriteMemory(DCM_CANCEL,
                                      Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                      Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                      s_dataCurrentBlockSize_u32,
                                      NULL_PTR,
                                      NULL_PTR));
    }
    else
    {
        /* Dummy else to remove the MISRA warning */
    }

    /* Initializing the block sequence counter */
    Dcm_TransferData_st.cntCurrentBlockCount = 0u;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
    /* Initializing the opstatus to INITIAL */
    s_stTransferOpstatus_u8 = DCM_INITIAL;
    /* Initializing the state variable of Transfer data to IDLE state */
    s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_IDLE;
    /* Resetting the complete context of sequence */
    Dcm_DspDeactivateRequestUploadDownloadPermission();
}

/**
 **************************************************************************************************
 * Dcm_CheckNrcForTransferData : This funtion is for doing the NRC checks for TransferData service
 *
 * \param           pMsgContext(in) : The service message context
 *                  dataNegResponseCode_u8(out) : The ErrorCode to be updated by the function if any
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* Function for checking the NRC */
static FUNC(void,DCM_CODE) Dcm_CheckNrcForTransferData(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                                 P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8);
static FUNC(void,DCM_CODE) Dcm_CheckNrcForTransferData(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                                 P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8)
{
    VAR(uint8,AUTOMATIC) dataReceivedBlockSequenceNr_u8;    /* Block sequence number from the request */
    VAR(uint32,AUTOMATIC) dataLengthReceived_u32;    /* Received block size in the request apart from the Block Sequence number */

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    VAR(uint32,AUTOMATIC) lastDataBlockSize_u32; /* variable to store the last block size */
#endif



    /* Storing the block sequence number in the request locally */
    dataReceivedBlockSequenceNr_u8 = pMsgContext->reqData[0];
    dataLengthReceived_u32 = pMsgContext->reqDataLen-1uL;

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    lastDataBlockSize_u32 = Dcm_GetLastBlockSize();
#endif


    /* Minimum length check if Previous request was RequestUpload - NRC 0X13*/
    if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(pMsgContext->reqDataLen < DCM_TRANSFERDATAUPLOAD_MIN_LEN))
    {
        *dataNegResponseCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* Minimum length check if Previous request was RequestDownload - NRC 0X13*/
    else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(pMsgContext->reqDataLen < DCM_TRANSFERDATADOWNLOAD_MIN_LEN))
    {
        *dataNegResponseCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* RequestSequence check if there was no Previous request of RequestUpload/RequestDownlaod - NRC 0X24*/
    /* If the requested memory size from requestUpload/requestDownload service is already uploaded/downloaded to/from the client and the sequence number is not repeated -  NRC 0x24 */
    else if(((Dcm_DataTransfer_st.isUploadStarted_b == FALSE)&&(Dcm_DataTransfer_st.isDownloadStarted_b == FALSE)) ||
    (((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)||(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE))&&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32 == Dcm_DataTransfer_st.dataMemorySize_u32) && (dataReceivedBlockSequenceNr_u8 !=  Dcm_TransferData_st.cntCurrentBlockCount)))
    {
        *dataNegResponseCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
    }
    /* application can use the below function to update the NRC 0x24 and NRC 0x71 in case the data is compressed. */
    else if( ((Dcm_CheckNRCfromApplication(dataLengthReceived_u32,dataNegResponseCode_u8))!= E_OK) && (Dcm_DataTransfer_st.compressionMethod_u8 != 0x00) )
    {
        /* do not do anything as the NRC is set by the application */
    }
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    /* This NRC check is for the total memory size that is requested to be transfered. This 0x71 check is done only for the last block of data.
     * For the blocks other than the last block, block size is checked against NRC 0x31.
     * 1. If its is a download data request
     * 2. if the request is repeated for the last block
     * 3. if it is a fresh request for the last block
     * check if the datalength to be transfered is consistent with the memory size*/
    else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE) &&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00) &&
            (((Dcm_TransferData_st.dataTransferedDataSize_u32 == Dcm_DataTransfer_st.dataMemorySize_u32)&&(dataReceivedBlockSequenceNr_u8 ==  Dcm_TransferData_st.cntCurrentBlockCount)) ||
             ((Dcm_TransferData_st.dataTransferedDataSize_u32 == (Dcm_DataTransfer_st.dataMemorySize_u32 - lastDataBlockSize_u32)) && (dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u)))) &&
            (dataLengthReceived_u32!=lastDataBlockSize_u32))

    {
        *dataNegResponseCode_u8 = DCM_E_TRANSFERDATASUSPENDED;
    }
#else
    /* application can use the below function to update the 0x71 in case the data is compressed and the data is flexible. */
    else if( ((Dcm_CheckNRCfromApplication(dataLengthReceived_u32,dataNegResponseCode_u8))!= E_OK) && (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00) )
    {
        /* do not do anything as the NRC is set by the application */
    }
#endif

    /* Checking if the TransferData begins with Block sequence count 0x01 otherwise NRC 0x73 */
    else if((Dcm_TransferData_st.dataTransferedDataSize_u32 == 0u)&&(dataReceivedBlockSequenceNr_u8!=1u))
    {
        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
    /* Checking if the block sequence count rolls over to zero after reaching oxff otherwise NRC 0x73 */
    else if((Dcm_TransferData_st.cntCurrentBlockCount == 0xFFu)&&
            (dataReceivedBlockSequenceNr_u8!=0x00u) &&
            (dataReceivedBlockSequenceNr_u8!=0xFFu))
    {
        /* When the block sequence counter reaches 0xff */
        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
    /* Block sequence check - checking if the block is repeated or if it is the next block - NRC 0X73 */
    else if((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&
            (dataReceivedBlockSequenceNr_u8 != Dcm_TransferData_st.cntCurrentBlockCount)&&
            (dataReceivedBlockSequenceNr_u8 != (Dcm_TransferData_st.cntCurrentBlockCount+1u)))
    {
        /* When the block sequence is less than 0xff */
        *dataNegResponseCode_u8 = DCM_E_WRONGBLOCKSEQUENCECOUNTER;
    }
#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
    else if((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&
            (Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&
            (Dcm_TransferData_st.dataTransferedDataSize_u32 != (Dcm_DataTransfer_st.dataMemorySize_u32 - lastDataBlockSize_u32))&&
            (Dcm_TransferData_st.dataTransferedDataSize_u32 != Dcm_DataTransfer_st.dataMemorySize_u32)&&
            (dataLengthReceived_u32!= (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u)))
    {
        /* The blocks except the last blocks, if have the size less than the MaxBlockSize */
        *dataNegResponseCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }
#endif
    else
    {
        /* NRC check is passed */
        *dataNegResponseCode_u8 = 0;
    }
}

/**
 **************************************************************************************************
 * Dcm_DcmTransferData : TransferData (0x36) Service
 * The TransferData service is used by the client to transfer data either from the client to the server (download)
 * or from the server to the client (upload).The service currently supports onlu upload of data
 *
 * \param           pMsgContext: Pointer to message structure
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmTransferData(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
                                                  P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE; /* Variable to indicate the direction of data transfer i.e. either Upload or DOwnload */
    VAR(Dcm_ReadMemoryRet_t,AUTOMATIC) dataReadMemRetValue_en = DCM_READ_NOT_AVAILABLE;
    VAR(Dcm_WriteMemoryRet_t,AUTOMATIC)dataWriteMemRetValue_en = DCM_WRITE_NOT_AVAILABLE;
    VAR(Std_ReturnType,AUTOMATIC) dataReturnValue_u8;    /* return value from the application */
    VAR(Std_ReturnType,AUTOMATIC) dataServRetValue_u8;    /* return value from the application */
    VAR(uint8,AUTOMATIC) dataReceivedBlockSequenceNr_u8;    /* Block sequence number from the request */

    /* Initializing the local variables */
    *dataNegRespCode_u8 = 0u;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_TransferDataIni();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataServRetValue_u8 = E_OK;
    }
    else
    {
        /* Storing the block sequence number in the request locally */
        dataReceivedBlockSequenceNr_u8 = pMsgContext->reqData[0];
        dataServRetValue_u8=E_NOT_OK;

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_IDLE)
        {
            /* setting the state to Error state before doing all the NRC checks */
            s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;
            /* call the function to do the NRC checks */
            Dcm_CheckNrcForTransferData(pMsgContext,dataNegRespCode_u8);
            if(*dataNegRespCode_u8 == 0)
            {
                /* increment the address and the block size only if it is the next block */
                if(((Dcm_TransferData_st.cntCurrentBlockCount == 0xffu) && (dataReceivedBlockSequenceNr_u8==0x00u)) ||
                        ((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&(dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u))))
                {
    /* update the address for every new block of data transfer, in case the compression is OFF, else pass the base address always */
                    /* incrementing the address */
                    /* Updating the memory address to read the requested block */
                    /* if it is not the 1st block, increment the address. The base address has to be sent for the first block */
                   if((Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)&&(Dcm_TransferData_st.dataTransferedDataSize_u32!=0u))
                    {
                        /* The memory address is incremented in terms of MaxBlockSize */
                        Dcm_DataTransfer_st.dataMemoryAddress_u32 = Dcm_DataTransfer_st.dataMemoryAddress_u32 + (s_dataCurrentBlockSize_u32);
                    }
    #if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
                    /* updatint the block size */
                    /* Checking if the block expected is not the last block */
                   if(Dcm_DataTransfer_st.compressionMethod_u8 == 0x00)
                   {
                       if(Dcm_TransferData_st.dataTransferedDataSize_u32 < (Dcm_DataTransfer_st.dataMemorySize_u32 - Dcm_GetLastBlockSize()))
                       {
                           /* update the size with the maxLength possible */
                           s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                       }
                       /* Checking if the block expected is the last block */
                       else
                       {
                           /* Update the remaining size as this is the last block */
                           s_dataCurrentBlockSize_u32 = Dcm_GetLastBlockSize();
                       }
                   }
                   else
                   {
                       if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                       {
                           /* In case of upload, always give application the Maxblocklen-2(SID,BSN), so that the application can modify the number of bytes to be transfered */
                           s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                       }
                       else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                       {
                           /* In case of download, always give application the request length that is recieved */
                           s_dataCurrentBlockSize_u32 = pMsgContext->reqDataLen-1u;
                       }
                       else
                       {
                           /* dummy else to remove MISRA warning */
                       }
                   }
    #else
                    /* If either compression is enabled or if the data in the request is less than the expected Maxlength */
                    if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                    {
                        /* In case of upload, always give application the Maxblocklen-2(SID,BSN), so that the application can modify the number of bytes to be transfered */
                        s_dataCurrentBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32-2u;
                    }
                    else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                    {
                        /* In case of download, always give application the request length that is recieved */
                        s_dataCurrentBlockSize_u32 = pMsgContext->reqDataLen-1uL;
                    }
                    else
                    {
                        /* dummy else to remove the MISRA warning */
                    }

    #endif

                }
                /* Moving the state to check the permission from application */
                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_CHECKACCESS;
            }
        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_CHECKACCESS)
        {
            if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
            {
                /* set the data transfer direction as UPLOAD if there was a RequestUpload request active previously */
                dataTransferDirection_ten = DCM_UPLOAD;
            }
            else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
            {
                /* set the data transfer direction as DOWNLOAD if there was a RequestDownload request active previously */
                dataTransferDirection_ten = DCM_DOWNLOAD;
            }
            else
            {
                /* dummy else to remove the MISRA warning */
            }
            /* calling the application to do NRC checks for 0x31,0x72,0x92,0x93 and manufacturer/supplier specific checks */
            /* If Transfer request paramter record is present in the request */
            if(pMsgContext->reqDataLen>1u)
            {
                /*MR12 RULE 9.1 VIOLATION: Control flow will not enter the else part of the above if statement.Therefor the  variable will always have a valid value. */
                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8,
                        Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                        Dcm_DataTransfer_st.dataMemoryAddress_u32,
                        &s_dataCurrentBlockSize_u32,
                        &pMsgContext->reqData[1],
                        (pMsgContext->reqDataLen)-1u,
                        dataTransferDirection_ten,
                        dataNegRespCode_u8
                );
            }
            /* If Transfer request paramter record is not present in the request */
            else
            {
                /*MR12 RULE 9.1 VIOLATION: Control flow will not enter the else part of the above if statement.Therefor the  variable will always have a valid value. */
                dataReturnValue_u8 = DcmAppl_Dcm_CheckPermissionForTransferData(dataReceivedBlockSequenceNr_u8,
                        Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                        Dcm_DataTransfer_st.dataMemoryAddress_u32,
                        &s_dataCurrentBlockSize_u32,
                        NULL_PTR,
                        0,
                        dataTransferDirection_ten,
                        dataNegRespCode_u8
                );

            }

                /* Moving to the error state */
            if(dataReturnValue_u8 == DCM_E_PENDING)
            {
                /* Do nothing. Be in the same state */
                dataServRetValue_u8=DCM_E_PENDING;
            }
            else if(dataReturnValue_u8 == E_OK)
            {
                /* Moving the state to call the application to read from the memory if requestUpload service is active previously */
                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_READWRITE;
            }
            else
            {
                if(*dataNegRespCode_u8 == 0)
                {
                /* In case the application does not NRC, but returns E_NOT_OK(or any value other than E_OK, E_PENDING and E_NOT_OK), then Dcm shall send NRC 0x22 */
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
                /* Moving to the error state */
                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;
            }

        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_READWRITE)
        {
            /* Call the application if the requested memory size is less than the Dcm transmission buffer size */
            if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(s_dataCurrentBlockSize_u32 > pMsgContext->resMaxDataLen))
            {
                /* in case the requested memory size exceeds the Dcm buffer size */
                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                /* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW" to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_TRANSFERDATA_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
            }
            else if((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(s_dataCurrentBlockSize_u32 <=pMsgContext->resMaxDataLen))
            {
                /* Calling the application to read the data from the memory */
                dataReadMemRetValue_en =  DcmAppl_Dcm_ReadMemory(s_stTransferOpstatus_u8,
                                                             Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                                             Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                                             s_dataCurrentBlockSize_u32,
                                                             &pMsgContext->resData[1],
                                                             dataNegRespCode_u8);
            }
            else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
            {
                /* Calling the application to read the data from the memory */
                dataWriteMemRetValue_en =  DcmAppl_Dcm_WriteMemory(s_stTransferOpstatus_u8,
                                                             Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
                                                             Dcm_DataTransfer_st.dataMemoryAddress_u32,
                                                             s_dataCurrentBlockSize_u32,
                                                             &pMsgContext->reqData[1],
                                                             dataNegRespCode_u8);

            }
            else
            {
                /* dummy else to remove the MISRA warning */
            }

            /*MR12 RULE 9.1 VIOLATION: Control flow will not enter the else part of the above if statement.Therefor the  variable will always have a valid value. */
             if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_PENDING == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_PENDING == dataWriteMemRetValue_en)))
            {
                s_stTransferOpstatus_u8 = DCM_PENDING;
                /* Return  DCM_E_PENDING from the service*/
                dataServRetValue_u8=DCM_E_PENDING;
            }
            else if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_FORCE_RCRRP == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_FORCE_RCRRP == dataWriteMemRetValue_en)))
            {
                s_stTransferOpstatus_u8 = DCM_FORCE_RCRRP_OK;
                /* Return  DCM_E_FORCE_RCRRP from the service*/
                dataServRetValue_u8=DCM_E_FORCE_RCRRP;
            }
            else if(((Dcm_DataTransfer_st.isUploadStarted_b != FALSE)&&(DCM_READ_OK == dataReadMemRetValue_en))||
                    ((Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)&&(DCM_WRITE_OK == dataWriteMemRetValue_en)))
            {
                /* if this is not the repeated block, update the block sequence count and the number of completed transfers */
                /* update the block sequence count to zero when it reaches 0xff and the tester client requests for the next block which is 0x00 */
                if((Dcm_TransferData_st.cntCurrentBlockCount == 0xffu)&&(dataReceivedBlockSequenceNr_u8==0u))
                {
                    /* increment the block sequence counter everytime the trasnferData is done for a new block and not the repeated block */
                    Dcm_TransferData_st.cntCurrentBlockCount = 0;
                    /* update the size of the data transfered in case it is a new block and the data is not compressed */
                    Dcm_TransferData_st.dataTransferedDataSize_u32 = Dcm_TransferData_st.dataTransferedDataSize_u32 + s_dataCurrentBlockSize_u32;
                }
                /* If the block sequence counter is below 0xff and the client has requested for the next block,
                 * increment the internal block sequence count and the number of completed transfers */
                else if((Dcm_TransferData_st.cntCurrentBlockCount != 0xffu)&&(dataReceivedBlockSequenceNr_u8 == (Dcm_TransferData_st.cntCurrentBlockCount+1u)))
                {
                    /* increment the block sequence counter everytime the trasnferData is done for a new block and not the repeated block */
                    Dcm_TransferData_st.cntCurrentBlockCount++;
                    /* update the size of the data transfered in case it is a new block and the data is not compressed */
                    Dcm_TransferData_st.dataTransferedDataSize_u32 = Dcm_TransferData_st.dataTransferedDataSize_u32 + s_dataCurrentBlockSize_u32;
                }
                else
                {
                    /* dummy else */
                }

                /*Response is already filled by the application*/
                if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
                {
                    /* Set final response length */
                    pMsgContext->resDataLen =  s_dataCurrentBlockSize_u32+1u;
                }
                else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {
                    /* Set final response length */
                    pMsgContext->resDataLen =  1u;
                }
                else
                {
                    /* dummy else to remove the MISRA warning */
                }
                /* updating the block sequence count in the response */
                pMsgContext->resData[0]= dataReceivedBlockSequenceNr_u8;

                /* Reset the state of transferData state machine to IDLE */
                s_stTransferDataState_en  = DCM_DSP_TRANSFERDATA_IDLE;
                /* reset the opstatus to INITIAL */
                s_stTransferOpstatus_u8    = DCM_INITIAL;
                /* Return E_OK from the service*/
                dataServRetValue_u8=E_OK;

            }
            else
            {

                s_stTransferOpstatus_u8 = DCM_INITIAL;

                if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
                {
                    if(*dataNegRespCode_u8 == 0x00)
                    {
                        /*Write has failed*/
                        *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
                    }
                }
                else
                {
                    if(*dataNegRespCode_u8 == 0)
                    {
                            /*Read has failed*/
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }
                }

                s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_ERROR;
            }
        }

        if(s_stTransferDataState_en == DCM_DSP_TRANSFERDATA_ERROR)
        {
            /* If negative response code is not set, send NRC 0x22 */
            if(*dataNegRespCode_u8==0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
            /* resetting the complete context of sequence */
            Dcm_DspDeactivateRequestUploadDownloadPermission();
            /* Reset the TransferData state machine */
            s_stTransferDataState_en = DCM_DSP_TRANSFERDATA_IDLE;
            /* reset the opstatus to INITIAL */
            s_stTransferOpstatus_u8    = DCM_INITIAL;
            /* Return E_NOT_OK from the service*/
            dataServRetValue_u8=E_NOT_OK;
        }
    }
    return dataServRetValue_u8;
}

#if(DCM_CFG_DSP_FLEXIBLEDATA_ENABLED == DCM_CFG_OFF)
/**
 ***********************************************************************************************************************
 * Dcm_GetLastBlockSize : Function to calculate the last block size
 *
 * \param           void:
 *
 * \retval          uint32 : The last block size
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
static FUNC(uint32,AUTOMATIC) Dcm_GetLastBlockSize(void)
{
    VAR(uint32,AUTOMATIC) dataLastBlockSize_u32;    /* variable to store the last block size */
    /* if the last block is a multiple of MaxBlockLength */
    if((Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u))==0u)
    {
        dataLastBlockSize_u32 = Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u;
    }
    /* if the last block is not a multiple of MaxBlockLength */
    else
    {
        dataLastBlockSize_u32 = (Dcm_DataTransfer_st.dataMemorySize_u32 % (Dcm_DataTransfer_st.dataMaxBlockLength_u32 - 2u));
    }
    return dataLastBlockSize_u32;
}

#endif
/**
 ***********************************************************************************************************************
 * Dcm_CheckNRCfromApplication : Function to call application to get the NRC checks for NRC 0x24 and NRC 0x71.
 *
 * \param           dataNegResponseCode_u8: NRC to be updated by the application
 *                  dataLengthReceived_u32: Length received in the request exluding the sequence number
 *
 * \retval          Std_ReturnType : E_OK : NRC updated by the application is zero
 *                                  E_NOT_OK : NRC updated by the application is non zero
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
static FUNC(Std_ReturnType,AUTOMATIC)Dcm_CheckNRCfromApplication(VAR(uint32,AUTOMATIC) dataLengthReceived_u32,
                                                                 P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResponseCode_u8)
{
    VAR(uint8,AUTOMATIC) dataReturnValue_u8;
    VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten = DCM_TRANSFER_NOT_AVAILABLE; /* Variable to indicate the direction of data transfer i.e. either Upload or DOwnload */
    dataReturnValue_u8 = E_OK;
    if(Dcm_DataTransfer_st.isUploadStarted_b != FALSE)
    {
        /* set the data transfer direction as UPLOAD if there was a RequestUpload request active previously */
        dataTransferDirection_ten = DCM_UPLOAD;
    }
    else if(Dcm_DataTransfer_st.isDownloadStarted_b != FALSE)
    {
        /* set the data transfer direction as DOWNLOAD if there was a RequestDownload request active previously */
        dataTransferDirection_ten = DCM_DOWNLOAD;
    }
    else
    {

       /* dummy else to remove the MISRA warning */
    }
    /* call the application to get the NRC value */
    /*MR12 RULE 9.1 VIOLATION: Control flow will not enter the else part of the above if statement.Therefor the  variable will always have a valid value. */
    (void)DcmAppl_DcmMemSizeCheckForTransferData(Dcm_DataTransfer_st.compressionMethod_u8,
            Dcm_DataTransfer_st.dataMemoryIdentifier_u8,
            dataLengthReceived_u32,
            dataTransferDirection_ten,
            dataNegResponseCode_u8);
    if(*dataNegResponseCode_u8 != 0)
    {
        dataReturnValue_u8 = E_NOT_OK;
    }
    return dataReturnValue_u8;
}

/**
 ***********************************************************************************************************************
 * Dcm_DspDeactivateRequestUploadDownloadPermission :Function called to stop the permission for Transfer Data after RequestDownload/RequestUpload
 * and reset the necessary global variables set
 *
 * \param           void:
 *
 * \retval          None
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DspDeactivateRequestUploadDownloadPermission(void)
{
    /*Initialize  RequestDownload request is to FALSE*/
    Dcm_DataTransfer_st.isDownloadStarted_b       = FALSE;
    /*Initialize RequestUpload request is to FALSE*/
    Dcm_DataTransfer_st.isUploadStarted_b       = FALSE;
    Dcm_DataTransfer_st.nrMaxBlockSequenceNum_u32 = 0x00;
    Dcm_TransferData_st.cntCurrentBlockCount = 0x00;
    Dcm_TransferData_st.dataTransferedDataSize_u32 = 0;
	Dcm_DataTransfer_st.compressionMethod_u8  = 0x00;
}

/**
 *******************************************************************************
 * Dcm_Prv_DspReqTrfExitConfirmation :API used for confirmation of response sent   
 *										 for RequestTransferExit (0x37) service.
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
 FUNC(void, DCM_CODE) Dcm_Prv_DspReqTrfExitConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
#if( DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
            if(status_u8 == DCM_RES_POS_OK)
            {
                Dcm_DspDeactivateRequestUploadDownloadPermission();
            }
#endif
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																	status_u8);
}

/**
 ***********************************************************************************************************************
 * Dcm_GetRequestUploadStatus :Function called to get the status if RequestUpload is started
 *
 * \param           void:
 *
 * \retval          boolean : Status if RequestUpload is started
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
FUNC(boolean,DCM_CODE)Dcm_GetRequestUploadStatus(void)
{
    return (Dcm_DataTransfer_st.isUploadStarted_b);
}

/**
 ***********************************************************************************************************************
 * Dcm_GetRequestDownloadStatus :Function called to get the status if RequestDownload is started
 *
 * \param           void:
 *
 * \retval          boolean : Status if RequestDownload is started
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
FUNC(boolean,DCM_CODE)Dcm_GetRequestDownloadStatus(void)
{
    return (Dcm_DataTransfer_st.isDownloadStarted_b);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF)) */

