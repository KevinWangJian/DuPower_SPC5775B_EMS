

#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"


#if(DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_ReportDTCSnapshotRecordIdentification :
 * Report corresponding DTCs and Record numbers for all FreezeFrame records present in primary memory of ECU (0x03)
 * Response to this subfunction shall include the DTC followed by the Record number for all the records

 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCSnapshotRecordIdentification (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                          AUTOMATIC) dataDTC_u32;          /* Variable to store DTC */
    VAR(uint16,                          AUTOMATIC) nrFiltRec_u16;
   /* Local variable to store the number of filtered records */
    VAR(Dcm_MsgLenType,                  AUTOMATIC) nrResDataLen_u32;   /* Local variable for response length */
    VAR(Dcm_MsgLenType,                  AUTOMATIC) nrResMaxDataLen_u32;/* Local variable to store max response length */
    VAR(uint8_least,                     AUTOMATIC) idxLoop_qu8;       /* Local variable for loop counter */
    VAR(uint8,                           AUTOMATIC) dataRecordNum_u8;           /* Variable to store Record Number */
    VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC) dataRetGetNextFiltRec_u8;
    /* Return Value for Dem_GetNextFilteredRecord */
    VAR(Dem_ReturnSetFilterType,         AUTOMATIC) dataRetSetDTCFilterForRec_u8; /* Return Value for Dem_SetDTCFilter */
    VAR(Std_ReturnType,                      AUTOMATIC) dataretVal_u8;                  /* Variable to store the returnType from subservice API          */

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8 = 0;  /* Initialization to zero - No error */
    dataretVal_u8=DCM_E_PENDING;
    /* Initial state */
    if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT )
    {
        /* check for request length */
        if(pMsgContext->reqDataLen == DSP_RDTC_03_REQUEST_LENGTH)
        {
            /* Set the DTC Filter for records in DEM */
            dataRetSetDTCFilterForRec_u8 = Dem_SetFreezeFrameRecordFilter(DEM_DTC_FORMAT_UDS,&nrFiltRec_u16);

            /* If the Filter is accepted by DEM */
            if(dataRetSetDTCFilterForRec_u8 == DEM_FILTER_ACCEPTED)
            {
				pMsgContext->resData[0] = DSP_REPORT_DTC_SNAPSHOT_RECORD;
                pMsgContext->resDataLen = 0x01;
                /* Move the state to fill the response */
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
            }
            /* If Filter is not accepted by DEM */
            else
            {
                /* Set Negative response */
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8=E_NOT_OK;
            }
        }
        /* Request Length not correct */
        else
        {
            /* Set Negative response */
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8=E_NOT_OK;
        }
    }

    /* State to get the DTC and record number of filtered records from DEM */
    else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP )
    {
        /* Initialize idxLoop_qu8 to zero */
        idxLoop_qu8 = 0x00;
        dataRetGetNextFiltRec_u8 = DEM_FILTERED_OK;

        /* Copy the Maximum response length into local variable */
        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        /* Copy the response data length to local variable */
        nrResDataLen_u32 = pMsgContext->resDataLen;

        /* Loop for maximum number of records to read in a cycle */
        while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMRECREAD) &&(dataRetGetNextFiltRec_u8 == DEM_FILTERED_OK)&&(*dataNegRespCode_u8==0))
        {
            idxLoop_qu8++;
            /* Get the  DTC and record number of the filtered record from DEM */
            dataRetGetNextFiltRec_u8 = Dem_GetNextFilteredRecord(&dataDTC_u32, &dataRecordNum_u8);

            /* If the record was filtered without any error */
            if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_OK)
            {
                /* Check if the response buffer is available for filling the response */
                if((nrResDataLen_u32 + 0x04u) <= nrResMaxDataLen_u32)
                {
                    /* Fill the response buffer with DTC and status */
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32 >> 16u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32 >> 8u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = dataRecordNum_u8;
                    nrResDataLen_u32++;
                }
                else
                {
                    /* Response buffer exceeded - set negative response code */
                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8=E_NOT_OK;
                }
            }
            /* If more time is needed to get the DTC number and record number of the filtered record */
            else if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_PENDING)
            {
                /* Nothing to be done */
                dataretVal_u8=DCM_E_PENDING;
            }
            /* If all the records are read completely */
            else if(dataRetGetNextFiltRec_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {
                /* Reset the status to default state */
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8=E_OK;
            }
            else
            {
                /* Some problems has occurred in DEM while reading DTC number and record number of filtered record */
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }

        /* Update the response length */
        pMsgContext->resDataLen = nrResDataLen_u32;
    }
	else
	{
		/* Do nothing */
        dataretVal_u8=E_NOT_OK;
	}
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

