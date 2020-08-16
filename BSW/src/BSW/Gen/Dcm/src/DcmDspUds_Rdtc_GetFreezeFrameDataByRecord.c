


#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_GetFreezeFrameDataByRecord :
 * The  function implements the RDTC subfunction 0x05.
 * This function will invoke the Dem APIs Dem_GetFreezeFrameDataByRecord and Dem_GetStatusOfDTC to get the
 * freeze frame data,DTC and DTC status related to the record  number send by the tester.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_GetFreezeFrameDataByRecord (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,                             AUTOMATIC) retVal_u8;
    VAR(boolean,                                    AUTOMATIC) isNRCSet_b;/*Variable to be set when a negative return type is returned from Dem API in case of record number 0xFF*/
    VAR(uint8,                                      AUTOMATIC) stDTCStatus_u8;        /* Variable to store the DTC status */
    VAR(uint8,                                      AUTOMATIC) dataRDTCSubFunc_u8;     /* Local variable to store sub function*/
    VAR(uint8,                                      AUTOMATIC) dataRecordNum_u8;           /* Variable to store Record Number */
    VAR(Dem_ReturnGetStatusOfDTCType,               AUTOMATIC) stRetGetStatusOfDTC_u8;    /* Return type of Dem_GetStatusOfDTC */
    VAR(Dem_ReturnGetFreezeFrameDataByRecordType,   AUTOMATIC) dataRetGetFreezeFrameDataByRecordType_u8; /* Return type of Dem_GetExtendedDataRecordByDTC*/
    VAR(uint8,                                      AUTOMATIC) idxLoop_u8;            /* Loop counter index for record numbers*/
    VAR(uint16,                                     AUTOMATIC) dataAvailableBuffLen_u16;/*Local variable to store and send available buffer size for Dem api Dem_GetFreezeFrameDataByRecord*/
    VAR(uint32,                                     AUTOMATIC) dataDTC_u32;            /* Variable to store DTC */
    VAR(Dcm_MsgLenType,                             AUTOMATIC) dataFillRespLen_u32;     /* Local variable to store the response length filled*/
    VAR(Dcm_MsgLenType,                             AUTOMATIC) dataRemainBuffer_u32;    /* Local variable for maximum response buffer available*/

    /*Initialize negative response code to ZERO*/
    *dataNegRespCode_u8 = 0x00;
    /* Initialization of variables */
    /*Initialize the variable isNRCSet_b to FALSE*/
    isNRCSet_b = FALSE;
    dataFillRespLen_u32 = 0;
    dataRetGetFreezeFrameDataByRecordType_u8 = DEM_GET_FFBYRECORD_OK ;
    stRetGetStatusOfDTC_u8  = DEM_STATUS_OK;
    retVal_u8=DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /*Copy subfunction value from the request to local variable*/
    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
    /*Check if the subfunction received is RDTC subfunction 0x05*/
    if(DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER == dataRDTCSubFunc_u8 )
    {
        /* Check if request length is correct(max request length ) */
        if(DSP_RDTC_05_REQLEN == pMsgContext->reqDataLen)
        {
            /*Copy record number from request to local variable*/
            dataRecordNum_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC +1u];
            /*store the subfunction value to response buffer and update the request length*/
            pMsgContext->resData[0] = DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER;
            pMsgContext->resDataLen = 0x01;
            /*Reserve 5 bytes for storing Record number(1 byte),DTC(3 bytes)and DTC status(1 byte) in the response buffer before passing the buffer to Dem API to fill the DataRecord*/
            dataFillRespLen_u32 = 6;
            /*IF the  record number is 0xFF ,loop through all the records and call Dem Apis to  get data record,DTC and DTC status */
            if(0xFF == dataRecordNum_u8 )
            {
                idxLoop_u8 = 0x00 ;
            }
            else
            {
                /*set the loop index to the requested record number*/
                idxLoop_u8 = dataRecordNum_u8 ;
            }
            do
            {
                /* Calculate the remaining buffer length available */
                if (pMsgContext->resMaxDataLen > dataFillRespLen_u32)
                {
                    dataRemainBuffer_u32 = (pMsgContext->resMaxDataLen - dataFillRespLen_u32);
                }
                else
                {
                    dataRemainBuffer_u32 = 0x00;
                }
                /* Copy the existing buffer size */
                dataAvailableBuffLen_u16 = (uint16)dataRemainBuffer_u32;

                dataRetGetFreezeFrameDataByRecordType_u8 = Dem_GetFreezeFrameDataByRecord(idxLoop_u8,DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                        &dataDTC_u32,&pMsgContext->resData[dataFillRespLen_u32],
                        &dataAvailableBuffLen_u16);

                /*DEM_GET_FFBYRECORD_OK from Dem_GetFreezeFrameDataByRecord*/
                if( DEM_GET_FFBYRECORD_OK == dataRetGetFreezeFrameDataByRecordType_u8)
                {
                    /* Call DEM API to get the status of DTC sent from tester */
                    stRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC( dataDTC_u32,
                            DEM_DTC_KIND_ALL_DTCS,
                            DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                            &stDTCStatus_u8);

                    if(DEM_STATUS_OK ==stRetGetStatusOfDTC_u8)
                    {
                        /*Dem_GetStatusOfDTCreturned ok.Now fill the record number,DTC and DTC status in the response buffer*/
                        pMsgContext->resData[dataFillRespLen_u32-5u] = idxLoop_u8;
                        pMsgContext->resData[dataFillRespLen_u32-4u] = (uint8)(dataDTC_u32>>16u);
                        pMsgContext->resData[dataFillRespLen_u32-3u] = (uint8)(dataDTC_u32>>8u);
                        pMsgContext->resData[dataFillRespLen_u32-2u] = (uint8)(dataDTC_u32);
                        pMsgContext->resData[dataFillRespLen_u32-1u] = stDTCStatus_u8;
                        /*Update response data length*/
                        pMsgContext->resDataLen = dataFillRespLen_u32+dataAvailableBuffLen_u16;
                        if(0xFF == dataRecordNum_u8 )
                        {
                            /*Update  dataFillRespLen_u32 where the next data can be written*/
                            dataFillRespLen_u32 = dataFillRespLen_u32 + dataAvailableBuffLen_u16 + 5u;
                        }
                        else{
                            retVal_u8=E_OK;
                        }
                    }
                     /* If the DTC sent by the tester is not correct */
                    else if(DEM_STATUS_FAILED==stRetGetStatusOfDTC_u8)
                    {
                        /*When DEM_STATUS_FAILED Dcm should send an positive response with SID and subfunction alone*/
                        pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                        /* Update the Response data length information */
                        pMsgContext->resDataLen = 0x01;
                        retVal_u8=E_OK;
                    }
                    /* If the DTC sent by the tester is not correct */
                    else if((DEM_STATUS_WRONG_DTC == stRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== stRetGetStatusOfDTC_u8)||       \
                            (DEM_STATUS_WRONG_DTCKIND== stRetGetStatusOfDTC_u8))
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        /*Set isNRCSet_b = TRUE,so that in the Record number FF case ,Dcm can send the NRC in case atleast  one wrong return value
                         *  is returned from Dem_GetStatusOfDTC for a DTC which is related to a valid REcord number   */

                        isNRCSet_b = TRUE;
                    }
                    /*If DEM returns any invalid value */
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        /*Set isNRCSet_b = TRUE,so that in the Record number FF case ,Dcm can send the NRC in case atleast  one wrong return value
                         *  is returned from Dem_GetStatusOfDTC for a DTC which is related to a valid REcord number   */

                        isNRCSet_b = TRUE;
                    }
                }
                /* Record number send by tester is wrong */
                else if(DEM_GET_FFBYRECORD_WRONG_RECORD == dataRetGetFreezeFrameDataByRecordType_u8 )
                {
                    /* set Negative Response*/
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                else if(DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD == dataRetGetFreezeFrameDataByRecordType_u8 )
                {
                    retVal_u8=E_OK;
                    /*DTCStoredDataRecordNumber  specified by the client is valid and supported by the server, but have no DTCStoredDataRecord data associated with it */
                    /* send positive response with only record number*/
                    if(0xFF == dataRecordNum_u8 )
                    {
                        if((dataRemainBuffer_u32 == 0u)&&((pMsgContext->resMaxDataLen - pMsgContext->resDataLen)>0u ))
                        {
                            pMsgContext->resData[pMsgContext->resDataLen] = idxLoop_u8;
                            pMsgContext->resDataLen +=1u;
                        }
                        else
                        {
                            /*Add the record number to the response and update the response length.Iterate through the next record*/

                            pMsgContext->resData[dataFillRespLen_u32-5u] = idxLoop_u8;
                            pMsgContext->resDataLen +=1u;
                            /*Increase the dataFillRespLen_u32 by one since we have added the One Record number(1 byte ) to the response buffer*/
                            dataFillRespLen_u32 = dataFillRespLen_u32+1u;
                        }
                    }
                    else
                    {
                        pMsgContext->resData[1] = dataRecordNum_u8;
                        pMsgContext->resDataLen =2;
                    }
                }

                else if(DEM_GET_FFBYRECORD_WRONG_BUFFERSIZE == dataRetGetFreezeFrameDataByRecordType_u8 )
                {
                    /* Response length is too long */
                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;

                }
                /*If the DTC Origin is not correct, or if DEM returns any other value */
                else
                {
                    if(0xFF != dataRecordNum_u8 )
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        /*Set isNRCSet_b to TRUE*/
                        isNRCSet_b = TRUE;
                    }
                }

                if( ((DEM_GET_FFBYRECORD_OK == dataRetGetFreezeFrameDataByRecordType_u8) && (DEM_STATUS_FAILED == stRetGetStatusOfDTC_u8)) ||
                          ((DEM_GET_FFBYRECORD_NO_DTC_FOR_RECORD == dataRetGetFreezeFrameDataByRecordType_u8 ) && (0xFF != dataRecordNum_u8)) )
                {
                    /*Break from loop so that positive respone with only record number can be sent directly*/
                    break;
                }

                if(0xFF != dataRecordNum_u8)
                {
                    /*For record number other than 0xFF set idxLoop_u8 to zero  to come out of the loop immediately*/
                    idxLoop_u8 = 0xFF;
                }
                else
                {
                    idxLoop_u8++;
                }
            /*Check for the negative response code and if current index is less than 0xFF and check if nrc is set ot not */
            }while((*dataNegRespCode_u8 != DCM_E_RESPONSETOOLONG )&&(idxLoop_u8 < 0xFFu)&& (isNRCSet_b != TRUE) );
            /*In case of record 0xFF positive response  check whether any  NRC other than DCM_E_RESPONSETOOLONG  is returned for any record and reset it*/
            if((0xFF == dataRecordNum_u8) && (pMsgContext->resDataLen >= 2u))
            {
                /*Check if negative response code is not ZERO and isNRCSet_b is set to FALSE*/
                if((*dataNegRespCode_u8 !=0u) &&  (*dataNegRespCode_u8 != DCM_E_RESPONSETOOLONG) && (isNRCSet_b != TRUE))
                {
                    *dataNegRespCode_u8 = 0;/* reset NRC*/
                }
            }
        }
        else
        {
            /*Incorrect request message length*/
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }

    if(0x0 != (*dataNegRespCode_u8))
    {
        retVal_u8=E_NOT_OK;
    }

    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
