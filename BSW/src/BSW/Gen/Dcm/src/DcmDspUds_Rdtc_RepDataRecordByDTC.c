


#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint8,                   DCM_VAR) s_nrRDTCLoopEnd_u8; /* End value of loop*/

static VAR (uint8,                  DCM_VAR) s_dataRDTCSubFunc_u8;     /* local variable to store sub function*/

static VAR(Dem_DTCOriginType,       DCM_VAR) s_dataDemDTCOrigin_u8;        /* Variable to store DTC origin */

static VAR(boolean,                 DCM_VAR) s_IsRecordSupported;   /* Flag to indicate that atleast one record is supported */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_ReportDataRecordByDTCNumber :
 * The following are done by this function
 *      Report one or all Snapshot Data Records for a particular DTC.
 *      If the tester sends a valid Record Number (0x00 to 0xFE) only that Record will be read
 *      If the tester sends a Record Number=0xff, all the Records for the DTC will be read.
 *
 *      Report one or all Extended Data Record for a particular DTC.
 *      If the tester sends a valid Record Number (0x01 to 0xEF) only that Record will be read
 *      If the tester sends a Record Number=0xFF all the Records for the DTC from 0x01 to 0xEF will be read
 *      If the tester sends a Record Number=0xFE all the Records for the DTC from 0x90 to 0xEF will be read
 *
 *      Report one or all user defined Memory Snapshot Record by DTC number for a particular DTC  .
 *      If the tester sends a valid Record Number (0x00 to 0xFE) only that Record will be read
 *      If the tester sends a Record Number=0xff, all the Records for the DTC will be read.
 *
 *      Report one or all user defined Memory Extended Data Record by DTC number for a particular DTC.
 *      If the tester sends a valid Record Number (0x01 to 0xEF) along with Memory selection then only that Record will be read
 *      If the tester sends a Record Number=0xFF along with Memory selection all the Records for the DTC from 0x01 to 0xEF will be read
 *      If the tester sends a Record Number=0xFE along with Memory selection all the Records for the DTC from 0x90 to 0xEF will be read
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDataRecordByDTCNumber (VAR(Dcm_SrvOpStatusType,AUTOMATIC) Opstatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    VAR(Dcm_MsgLenType,AUTOMATIC) dataRemainBuffer_u32;    /* Local variable for maximum response buffer available*/
    VAR(Dcm_MsgLenType,AUTOMATIC) dataFillRespLen_u32;     /* Local variable to store the response length filled*/
    VAR(uint8_least,AUTOMATIC) idxLoop_qu8;            /* Loop counter index for record numbers*/
    VAR(uint8,AUTOMATIC) nrReqLength_u8 = 0x00u;  /*Variable to store request length */
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
    VAR (uint16,                         AUTOMATIC) nrSizeOfFreezeFrame_u16;
    VAR(Dem_ReturnGetFreezeFrameDataByDTCType,   AUTOMATIC) dataRetGetFFDataRecByDTC_u8;  /* Return type of
                                                                                   Dem_GetFreezeFrameDataByDTC*/
    VAR(Dem_ReturnGetSizeOfFreezeFrameByDTCType,   AUTOMATIC) dataRetGetFFDataRecSizeByDTC_u8;  /* Return type of
                                                                                    Dem_GetSizeOfFreezeFrameByDTC*/
#endif
    VAR(Dem_ReturnGetStatusOfDTCType,            AUTOMATIC) stRetGetStatusOfDTC_u8;    /* Return type of Dem_GetStatusOfDTC */
    VAR(  Dem_ReturnDisableDTCRecordUpdateType   ,     AUTOMATIC) stRetDisableDTCRecUpdate_u8; /*Return type from Dem_DisableDTCRecordUpdate*/
    VAR( uint8,                         AUTOMATIC) stDTCStatus_u8;        /* Variable to store the DTC status */
    VAR(Std_ReturnType,                          AUTOMATIC) dataRetEnableDTCRecUpdate_u8;/*Return Value of
                                                                                      Dem_EnableDTCRecordUpdate*/
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
    VAR(Dem_ReturnGetExtendedDataRecordByDTCType,AUTOMATIC) dataRetGetExtDataRecByDTC_u8; /* Return type of
                                                                                   Dem_GetExtendedDataRecordByDTC*/
#endif
    /* Variable to indicate if API Dem_GetExtendedDataRecordByDTC or Dem_GetFreezeFrameDataByDTC  returns Pending*/
    VAR(boolean,                        AUTOMATIC) isPendingReturned_b;
   VAR(Std_ReturnType,                             AUTOMATIC)  dataretVal_u8;              /* Variable to store the service return value */
    /* Initialization of variables */
    *dataNegRespCode_u8 = 0x00;
    /*Initialize the variable isPendingReturned_b to FALSE*/
    isPendingReturned_b = FALSE;
    dataFillRespLen_u32 = 0;
    dataretVal_u8 = DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(Opstatus);
    /* State machine */
    /* Initialization state */
    if ( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
        s_dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))
        /* Check if the subfunction is 0x04,0x06,0x10*/
        if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
        {   /* Update the request length */
            nrReqLength_u8 = DSP_RDTC_04_06_10_REQUEST_LENGTH;
        }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
        if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
        {

            /* Update the request length */
            nrReqLength_u8 = DSP_RDTC_18_19_REQUEST_LENGTH;
        }

#endif
        /* Check if request length is correct */
        if(nrReqLength_u8 == pMsgContext->reqDataLen)
        {
            /* copy the 3 byte DTC into Dsp_RdtcDTC_u32 from request*/
            Dsp_RdtcDTC_u32 =  ((((uint32) pMsgContext->reqData[0x01]) << DSP_RDTC_LSH_16BITS) |
                    (((uint32) pMsgContext->reqData[0x02]) << DSP_RDTC_LSH_08BITS) |
                    ((uint32) pMsgContext->reqData[0x03]));
            s_dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

#if ((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                    (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {
                /* Set DTC origin as Memory selection from the request */
                s_dataDemDTCOrigin_u8 = pMsgContext->reqData[0x05];

            }
#endif
#if (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)
            if(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)
            {
                /* Set DTC origin to mirror memory if subfunction is 0x10 */
                s_dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_MIRROR_MEMORY;

            }
#endif
            /* Call DEM API to get the status of DTC sent from tester */
            stRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(Dsp_RdtcDTC_u32,
                    DEM_DTC_KIND_ALL_DTCS,
                    s_dataDemDTCOrigin_u8,
                    &stDTCStatus_u8);



            /* If the DTC is correct and valid status is available */
            if(DEM_STATUS_OK == stRetGetStatusOfDTC_u8)
            {
                /* Copy the record number from the request */
                Dcm_DspRDTCRecordNum_u8 = pMsgContext->reqData[0x04];

#if ((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {
                    /* Fill the response buffer */
                    pMsgContext->resData[0x04] = pMsgContext->reqData[0x03];
                    pMsgContext->resData[0x03] = pMsgContext->reqData[0x02];
                    pMsgContext->resData[0x02] = pMsgContext->reqData[0x01];
                    pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                    pMsgContext->resData[0x01] = s_dataDemDTCOrigin_u8;
                    pMsgContext->resData[0x05] = stDTCStatus_u8;
                    /* Update the Response data length information */
                    pMsgContext->resDataLen = 0x06;

                }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
                {
				    /* Fill the response buffer */
                    pMsgContext->resData[0x03] = pMsgContext->reqData[0x03];
                    pMsgContext->resData[0x02] = pMsgContext->reqData[0x02];
                    pMsgContext->resData[0x01] = pMsgContext->reqData[0x01];
                    pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                    pMsgContext->resData[0x04] = stDTCStatus_u8;
                    /* Update the Response data length information */
                    pMsgContext->resDataLen = 0x05;
                }
#endif
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||\
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {
                	Dcm_DspRDTCSubFunc_en = DSP_RDTC_UPDATEDISABLED;
                }

            }
            /* If the DTC sent by the tester is not correct */
            else if(DEM_STATUS_FAILED==stRetGetStatusOfDTC_u8)
            {
                /*When DEM_STATUS_FAILED Dcm should send an positive response with SID and subfunction alone*/
                pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                /* Update the Response data length information */
                pMsgContext->resDataLen = 0x01;
                dataretVal_u8 = E_OK;
            }
            /* If the DTC sent by the tester is not correct */
            else if((DEM_STATUS_WRONG_DTC == stRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== stRetGetStatusOfDTC_u8)||       \
                    (DEM_STATUS_WRONG_DTCKIND== stRetGetStatusOfDTC_u8))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
            /*If DEM returns any invalid value */
            else
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }
        /* Request Length not correct */
        else
        {
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
    }
    if(DSP_RDTC_UPDATEDISABLED==Dcm_DspRDTCSubFunc_en)
    {
        stRetDisableDTCRecUpdate_u8 = Dem_DisableDTCRecordUpdate(Dsp_RdtcDTC_u32,s_dataDemDTCOrigin_u8);
        /* Disable the Record Update */
        if ( DEM_DISABLE_DTCRECUP_OK == stRetDisableDTCRecUpdate_u8)
        {
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {
                if(Dcm_DspRDTCRecordNum_u8 == 0xFF)
                {   /*Change End value of loop to 0xFF */
                    s_nrRDTCLoopEnd_u8   = 0xFF;
                }
                else if(Dcm_DspRDTCRecordNum_u8 == 0xFE)
                {
                    s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8;
                }
                else
                {
                    /*Loop end is pre-incremented so that the do-While loop end condition is correctly
                            implemented, when DEM API returns Pending*/
                    s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8 + 0x01;
                }
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_GETFFSIZE;
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if ((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM) \
                    ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {
                if (Dcm_DspRDTCRecordNum_u8 == 0x00)
                {
                    /* FC_VariationPoint_START */
                    /*  0x00 is reserved for future OBD use */
                    /* FC_VariationPoint_END */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                else
                {
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                    s_IsRecordSupported = FALSE;
                    /* If the tester wants to read only one record of the DTC */
                    if(Dcm_DspRDTCRecordNum_u8 == 0xEF)
                    {
                        s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8;
                    }
                    else if(Dcm_DspRDTCRecordNum_u8 < 0xF0)
                    {
                        /*Loop end is pre-incremented so that the do-While loop end condition is correctly
                                implemented, when DEM API returns Pending*/

                        s_nrRDTCLoopEnd_u8 = Dcm_DspRDTCRecordNum_u8 + 0x01;
                    }
                    else if (Dcm_DspRDTCRecordNum_u8 == 0xFE)
                    {
                        /* FC_VariationPoint_START */
                        /*Request is for the server to report legislated OBD DTC Extended Data records.
                                This is stored in Record Numbers 0x90 to 0xEF */
                        /* FC_VariationPoint_END */
                        /* Set the Record number to 0x90*/
                        Dcm_DspRDTCRecordNum_u8 = 0x90;
                        s_nrRDTCLoopEnd_u8   = 0xF0;
                    }
                    else if (Dcm_DspRDTCRecordNum_u8 == 0xFF)
                    {
                        /*Request is for the server to report all Extended Data records.
                                This is stored in Record Numbers 0x01 to 0xEF */
                        /* Set the Record number to 0x01 */
                        Dcm_DspRDTCRecordNum_u8 = 0x01;
                        s_nrRDTCLoopEnd_u8   = 0xF0;
                    }
                    else
                    {
                        *dataNegRespCode_u8   = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
            }
#endif
        }
        else if (DEM_DISABLE_DTCRECUP_WRONG_DTC==stRetDisableDTCRecUpdate_u8)
        {
            /* Set Negative Response */
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }
        else if (DEM_DISABLE_DTCRECUP_PENDING == stRetDisableDTCRecUpdate_u8 )
        {

            /*remain in the same state*/
        }
        else
        {
            /* Set Negative Response */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

        }

    }

    /* State to read multiple records */
    else if (Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu8 = 0;
        /* Loop through the maximum number of records that can be read at a time */
        do
        {
            idxLoop_qu8++;
            /* Update the response length to local variable */
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {
                dataFillRespLen_u32 = (pMsgContext->resDataLen);
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if ((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)\
                    ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {
                /* To consider Record number */
                dataFillRespLen_u32 = (pMsgContext->resDataLen + 1u);
            }
#endif
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
            Dcm_DspMaxResDataLen_u16 = (uint16)dataRemainBuffer_u32;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC)||(s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER))
            {
                /* Call the DEM API to get the Freeze frame for the record number */
                dataRetGetFFDataRecByDTC_u8 = Dem_GetFreezeFrameDataByDTC ( Dsp_RdtcDTC_u32,
                        DEM_DTC_KIND_ALL_DTCS,
                        s_dataDemDTCOrigin_u8,
                        Dcm_DspRDTCRecordNum_u8,
                        &pMsgContext->resData[dataFillRespLen_u32],
                        &Dcm_DspMaxResDataLen_u16
                );
                /* If the Freeze frame is read without any error */
                if(DEM_GET_FFDATABYDTC_OK == dataRetGetFFDataRecByDTC_u8)
                {
                    /* If at least one byte of data is returned from DEM */
                    if(Dcm_DspMaxResDataLen_u16 > 0x00)
                    {
                        /* Calculate the total response length */
                        pMsgContext->resDataLen = (Dcm_DspMaxResDataLen_u16 + dataFillRespLen_u32);
                    }
                    Dcm_DspRDTCRecordNum_u8++;
                    s_IsRecordSupported = TRUE;

                }
                /*If DEM requires more time to process the request*/
                else if (DEM_GET_FFDATABYDTC_PENDING == dataRetGetFFDataRecByDTC_u8)
                {
                    /*Change idxLoop_qu8 value to break out of the loop. DEM API has to be called in next raster*/
                    idxLoop_qu8 = DCM_CFG_RDTC_MAXNUMRECREAD;
                    /* Set the variable to TRUE */

                    isPendingReturned_b = TRUE;
                    dataretVal_u8 = DCM_E_PENDING;
                }
                /* If the record number is wrong */
                else if (DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER == dataRetGetFFDataRecByDTC_u8)
                {
                    if (s_nrRDTCLoopEnd_u8 != 0xFF)
                    {
                        /* If request is for a single Record, set Negative Response*/
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {
                        /* Increment and continue with the next record number */
                        Dcm_DspRDTCRecordNum_u8++;
                    }
                }
                /* If the DTC number is wrong */
                else if(DEM_GET_FFDATABYDTC_WRONG_DTC == dataRetGetFFDataRecByDTC_u8)
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                /* If there was no free space in buffer */
                else if(DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE == dataRetGetFFDataRecByDTC_u8)
                {
                    /* Response length is too long */
                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                }
                /* If the DTC Origin or the DTC Kind is not correct or DEM returns any
                other return value */
                else
                {
                    /* Set Negative Response */
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT ;
                }
            }
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
            if ((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) ||(s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| \
                    (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
            {
                /* Call the DEM API to get the extended data for the record number */
                dataRetGetExtDataRecByDTC_u8 = Dem_GetExtendedDataRecordByDTC( Dsp_RdtcDTC_u32,
                        DEM_DTC_KIND_ALL_DTCS,
                        s_dataDemDTCOrigin_u8,
                        Dcm_DspRDTCRecordNum_u8,
                        &pMsgContext->resData[dataFillRespLen_u32],
                        &Dcm_DspMaxResDataLen_u16
                );
                /* If the extended data record is read without any error */
                if(DEM_RECORD_OK == dataRetGetExtDataRecByDTC_u8)
                {
                    /* If at least one byte of data is returned from DEM */
                    if(Dcm_DspMaxResDataLen_u16 > 0x00)
                    {
                        /* Copy the response buffer with Record number */
                        pMsgContext->resData[pMsgContext->resDataLen] = Dcm_DspRDTCRecordNum_u8;

                        /* Calculate the total response length */
                        pMsgContext->resDataLen = (Dcm_DspMaxResDataLen_u16 + dataFillRespLen_u32);
                    }

                    s_IsRecordSupported = TRUE;
                    Dcm_DspRDTCRecordNum_u8++;


                }
                /*If DEM requires more time to process the request*/
                else if (DEM_RECORD_PENDING == dataRetGetExtDataRecByDTC_u8)
                {
                    /*Change idxLoop_qu8 value to break out of the loop. DEM API has to be called in next raster*/
                    idxLoop_qu8 = DCM_CFG_RDTC_MAXNUMRECREAD;
                    /* Set the variable to TRUE */

                    isPendingReturned_b = TRUE;
                    dataretVal_u8 = DCM_E_PENDING;
                }
                /* If the record number is wrong */
                else if(DEM_RECORD_WRONG_NUMBER == dataRetGetExtDataRecByDTC_u8)
                {
                    if (s_nrRDTCLoopEnd_u8 != 0xF0)
                    {
                        /*If request is for a single Record, set Negative Response*/
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {
                        /* Increment and continue with the next record number */
                        Dcm_DspRDTCRecordNum_u8++;
                    }
                }
                /* If the DTC number is wrong */
                else if(DEM_RECORD_WRONG_DTC == dataRetGetExtDataRecByDTC_u8)
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                /* If there was no free space in buffer */
                else if(DEM_RECORD_WRONG_BUFFERSIZE == dataRetGetExtDataRecByDTC_u8)
                {
                    /* Response length is too long */
                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                }
                /* If the DTC Origin or the DTC Kind is not correct or DEM returns any
                other return value */
                else
                {
                    /* Set Negative Response */
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;

                }
            }
#endif
        }while ((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMRECREAD)             &&
                (0x00 == *dataNegRespCode_u8)                         &&
                (Dcm_DspRDTCRecordNum_u8 < s_nrRDTCLoopEnd_u8));
        if((Dcm_DspRDTCRecordNum_u8 >= s_nrRDTCLoopEnd_u8) && (0x00 == *dataNegRespCode_u8))
        {
            dataretVal_u8 = E_OK;
        }
        /*Check if the record number is greater than or equal to the End value of the loop and  isPendingReturned_b status is set to FALSE*/
        if ((Dcm_DspRDTCRecordNum_u8 >= s_nrRDTCLoopEnd_u8) && (isPendingReturned_b == FALSE))
        {
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))

            if((s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_DATA_RECORD) || (s_dataRDTCSubFunc_u8 == DSP_REPORT_EXTENDED_REC_MIRROR_MEM)|| (s_dataRDTCSubFunc_u8 == DSP_REPORT_SNAPSHOT_RECORD_BY_DTC))
            {
                if((s_IsRecordSupported==FALSE)&&(*dataNegRespCode_u8==0x00u)&&(pMsgContext->resDataLen==0x05u))
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                else
                {
                    /* If all the requested record numbers are read, move the state machine to
                   DSP_RDTC_SFINIT State */
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                }
            }
#endif
#if ((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
                if((s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER)|| \
                        (s_dataRDTCSubFunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER))
                {
                    if((s_IsRecordSupported==FALSE)&&(*dataNegRespCode_u8==0x00u)&&(pMsgContext->resDataLen==0x06u))
                    {
                        /* Set negative response code */
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                    else
                    {
                        /* If all the requested record numbers are read, move the state machine to
                       DSP_RDTC_SFINIT State */
                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                    }

                }
#endif
        }
        else
        {
            /*Max Number of records for a service call are read, or DEM_GET_FFDATABYDTC_PENDING is returned
              by DEM. Therefore, remain in the state DSP_RDTC_SFFILLRESP */
        }
    }
    else
    {
        /* Do nothing */
    }

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF))
    if (Dcm_DspRDTCSubFunc_en == DSP_RDTC_GETFFSIZE)
    {   /* Call the DEM API to get the size of the Freeze frame for the record number */
        dataRetGetFFDataRecSizeByDTC_u8=Dem_GetSizeOfFreezeFrameByDTC(Dsp_RdtcDTC_u32,
                DEM_DTC_KIND_ALL_DTCS,
                s_dataDemDTCOrigin_u8,
                Dcm_DspRDTCRecordNum_u8,
                &nrSizeOfFreezeFrame_u16);
        if(DEM_GET_SIZEOFFF_OK == dataRetGetFFDataRecSizeByDTC_u8)
        {
            if(pMsgContext->resMaxDataLen >= (uint32)(nrSizeOfFreezeFrame_u16+0x5))
            {
                if(Dcm_DspRDTCRecordNum_u8 == 0xFF)
                {   /* Set the Record number to 0x00 */
                    Dcm_DspRDTCRecordNum_u8 = 0x00;
                }
                /*If sufficient buffer size is available, go to next stage */
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                s_IsRecordSupported = FALSE;
            }
            else
            {   /* Response length is too long */
                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
            }
        }
        /*If DEM requires more time to process the request*/
        else if(DEM_GET_SIZEOFFF_PENDING == dataRetGetFFDataRecSizeByDTC_u8)
        {   /* Do nothing, wait for next call */
        }
        /*If the record number or DTC is wrong*/
        else if((DEM_GET_SIZEOFFF_WRONG_RNUM == dataRetGetFFDataRecSizeByDTC_u8)||
                (DEM_GET_SIZEOFFF_WRONG_DTC  == dataRetGetFFDataRecSizeByDTC_u8))
        {   /* set Negative Response*/
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        }
        /* If DTC Origin or Kind is incorrect or any other return value */
        else
        {   /* Set Negative Response */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT ;
        }
    }
#endif


    if(*dataNegRespCode_u8 != 0)
    {
        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
        dataretVal_u8 = E_NOT_OK;
    }

    /* If the state machine is in default state */
    if(DSP_RDTC_SFINIT == Dcm_DspRDTCSubFunc_en)
    {
        /* Call the API to Enable Record update */
        dataRetEnableDTCRecUpdate_u8 = Dem_EnableDTCRecordUpdate();
        (void)dataRetEnableDTCRecUpdate_u8;
        s_IsRecordSupported = FALSE;
        /*Response Data Length is updated while Filling the Response.
        Hence, it need not be updated here*/
    }

    return dataretVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

