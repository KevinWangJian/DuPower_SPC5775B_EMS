


#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF)||\
/* FC_VariationPoint_START */ \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF)||\
	/* FC_VariationPoint_END */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 ***************************************************************************************************
 * Dcm_Dsp_ReportNumberOfDTC
 * This function is used to implement the RDTC service for the following sub functions:
 * 0x01(reportNumberOfDTCByStatusMask),
 * 0x07 (reportNumberOfDTCBySeverityMaskRecord),
 * 0x11(reportNumberOfMirrorMemoryDTCByStatusMask),
 \ifnot COMP_DCM
 * FC_VariationPoint_START
 \endif
 * 0x12(reportNumberOfEmissionsRelatedOBDDTCByStatusMask)
  \ifnot COMP_DCM
 * FC_VariationPoint_END
  \endif

 * The request contains the Status mask sent from the tester for subfunctions 0x01,0x11,0x12 and contains
 * severity mask and status mask for subfunction 0x07. The valid bits of the DTC Severity Mask are bits 5
 * to 7 as described in ISO-14229-1. Response sent to the tester contains the Status Availability Mask of
 * the ECU,the format Identifier and the Count of number of DTCs matching the tester Request.
 * \param            pMsgContext    Pointer to message structure

 * \retval           None

 * \seealso
 *
 ***************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportNumberOfDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	VAR(uint16,                              AUTOMATIC) nrFltDTC_u16;      /* Number of filtered DTCs */
    VAR(uint8,                               AUTOMATIC) dataRDTCSubFunc_u8;    /* Local Variable to store sub-function level */
    VAR(Dem_DTCKindType,                     AUTOMATIC) dataDTCKind_u8;         /* Local Variable to store DTC KIND */
    VAR(Dem_DTCOriginType,                   AUTOMATIC) dataDTCOrigin_u8;       /* Local Variable to store DTC ORIGIN*/
    VAR(uint8,                               AUTOMATIC)	stDTCStatus_u8;       /* Variable to store the DTC status */
	VAR(uint8,                               AUTOMATIC) nrReqLength_u8;       /* Variable to store request length */
    VAR(uint8,                               AUTOMATIC) dataStatusAvailMask_u8;
   /* Variable to store status availability mask */
    VAR (Dem_DTCSeverityType,                AUTOMATIC) dataDTCSeverity_u8;     /* Variable to store DTC Severity Mask */
    VAR(Dem_FilterWithSeverityType,          AUTOMATIC) dataDTCSeverityType_u8; /* Variable to store Severity type */
    VAR(Dem_ReturnSetFilterType,          AUTOMATIC) dataRetSetDTCFilter_u8; /* Return type for Dem_SetDTCFilter*/
    VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetGetNumOfFiltDTC_u8; /* Return type Dem_GetNumberOfFilteredDTC */
    VAR(Std_ReturnType,AUTOMATIC)  dataretVal_u8;                  /* Variable to store the returnType from DcmAppl API          */

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
	*dataNegRespCode_u8 = 0;  /* Initialization to zero - No error */
    dataretVal_u8=DCM_E_PENDING;

    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
		dataRDTCSubFunc_u8  =  pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
		 /* FC_VariationPoint_START */ \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
	 /* FC_VariationPoint_END */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF))
		nrReqLength_u8     =  DSP_RDTC_01_11_12_REQUEST_LENGTH;
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
		if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
		{
			nrReqLength_u8 = DSP_RDTC_07_REQUEST_LENGTH;
		}
#endif
        /* check for request length */
        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {
			/* Set dataDTCSeverity_u8 to DEM_SEVERITY_NO_SEVERITY for subfunctions 0x01,0x11 and 0x12 */
			dataDTCSeverity_u8     = DEM_SEVERITY_NO_SEVERITY;

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
			if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
			{
				dataDTCSeverity_u8 = pMsgContext->reqData[1];
				if((dataDTCSeverity_u8 & 0x1Fu) != 0x0u)
				{
					*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataretVal_u8=E_NOT_OK;
				}
			}
#endif
            if (*dataNegRespCode_u8 == 0x0)
			{
				/* If the status availability mask is read successfully */
				if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
				{
					   /* Fill the response bytes */
					stDTCStatus_u8   			= pMsgContext->reqData[1];

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
					if(dataRDTCSubFunc_u8 == DSP_REPORT_NUM_SEVERMASK_DTC)
					{
						stDTCStatus_u8 = pMsgContext->reqData[2];
					}
#endif
					pMsgContext->resData[0] = dataRDTCSubFunc_u8;
					pMsgContext->resData[1] = dataStatusAvailMask_u8;

					/* Get the DTC Format Identifier and fill into the response buffer */
					pMsgContext->resData[2] = Dem_GetTranslationType();

					/* Calculate the effective status Mask */
					stDTCStatus_u8 = (dataStatusAvailMask_u8 & stDTCStatus_u8);

					/* If effective status mask is not equal to zero */
					if(stDTCStatus_u8 != 0x0)
					{
						switch (dataRDTCSubFunc_u8)
						{
							case DSP_REPORT_NUM_STATUS_MASK_DTC:
							dataDTCKind_u8         = DEM_DTC_KIND_ALL_DTCS;
							dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
							dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
							break;

							case DSP_REPORT_NUM_MIRROR_DTC:
							dataDTCKind_u8   	   = DEM_DTC_KIND_ALL_DTCS;
							dataDTCOrigin_u8       = DEM_DTC_ORIGIN_MIRROR_MEMORY;
							dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
							break;
							/* FC_VariationPoint_START */
							case DSP_REPORT_NUM_EMISSION_DTC:
							dataDTCKind_u8         = DEM_DTC_KIND_EMISSION_REL_DTCS;
							dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
							dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_NO;
							break;
							/* FC_VariationPoint_END */
							case DSP_REPORT_NUM_SEVERMASK_DTC:
							default:
							dataDTCKind_u8         = DEM_DTC_KIND_ALL_DTCS;
							dataDTCOrigin_u8       = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
							dataDTCSeverityType_u8 = DEM_FILTER_WITH_SEVERITY_YES;
							break;
						}

						/* Set the DTC Filter in DEM */
						dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( stDTCStatus_u8,
															   dataDTCKind_u8,
															   DEM_DTC_FORMAT_UDS,
															   dataDTCOrigin_u8,
															   dataDTCSeverityType_u8,
															   dataDTCSeverity_u8,
															   DEM_FILTER_FOR_FDC_NO
												             );

						/* If the Filter Mask sent is accepted by DEM */
						if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
						{
							/* Move the state to fill the response */
							Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
						}
						/* Filter Mask not accepted by DEM */
						else
						{
							/* Set Negative response */
							*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            dataretVal_u8=E_NOT_OK;
						}
					}
					/* If effective status mask is equal to zero, fill response with DTC count = 0x0 */
					else
					{
						/* No record to read and fill the DTC count as 0x0000*/
						pMsgContext->resData[3] = 0x0;
						pMsgContext->resData[4] = 0x0;
						pMsgContext->resDataLen = 0x05;
                        dataretVal_u8=E_OK;
					}
				}
				/* Status mask is not read properly from DEM */
				else
				{
					/* Set Negative response */
					*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8=E_NOT_OK;
				}
			}
			else
			{
				/* Do nothing */
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

    if (Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        dataRetGetNumOfFiltDTC_u8 = Dem_GetNumberOfFilteredDTC ( &nrFltDTC_u16);

        if (dataRetGetNumOfFiltDTC_u8 == DEM_NUMBER_OK)
        {
            /* Fill the high byte of the DTC count */
            pMsgContext->resData[3] = (uint8) (nrFltDTC_u16>>0x08u);

            /*Fill Low Byte of DTC Count*/
            pMsgContext->resData[4] = (uint8) (nrFltDTC_u16);

			/* Update the response length */
            pMsgContext->resDataLen = 0x05;

            /* Reset the state to default state */
            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
            dataretVal_u8=E_OK;
        }
        else if (dataRetGetNumOfFiltDTC_u8 == DEM_NUMBER_PENDING)
        {
             /* Do Nothing, the function will be called in the next Raster */
             dataretVal_u8=DCM_E_PENDING;
        }
        else
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8=E_NOT_OK;
        }
    }
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

