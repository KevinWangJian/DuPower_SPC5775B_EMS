

#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
/**
 **************************************************************************************************
 * Dcm_Dsp_ReportFaultDetectionCounter :
 *  This function is used to implement the  subfunction 0x14(reportDTCFaultDetectionCounter).
 *  From this function  Dem_SetDTCFilter is called to set  the filter and then  Dem_GetNumberOfFilteredDTC
 *  is called to get the number of filtered DTCs. Dem_GetNextFilteredDTCAndFDC will be called to get the
 *  DTC and its corresponding Fault counter.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */




FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFaultDetectionCounter (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	VAR(uint8_least,                      AUTOMATIC) cntrLoop_qu8;         /* Variable for loop counter */
	VAR(sint8,                            AUTOMATIC) cntrFault_s8;       /* Variable to store Fault detection counter */
	VAR(Dem_ReturnSetFilterType,       AUTOMATIC)    dataRetSetDTCFilter_u8; /* Return type for Dem_SetDTCFilter */
	VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8; /* Return type for Dem_GetNextFilteredDTC */
	VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8; /* Return type for Dem_GetNumberOfFilteredDTC */
	VAR(uint16,                          AUTOMATIC)  nrFltDTC_u16;     /* Variable to store number of filtered DTCs */
	VAR(uint32,                           AUTOMATIC) dataDTC_u32;            /* Variable to store DTC */
	VAR(Dcm_MsgLenType,                   AUTOMATIC) dataRespLen_u32;        /* Local variable for response length */
	VAR(Dcm_MsgLenType,                   AUTOMATIC) dataResMaxLen_u32;  /* Variable to store max response length */
    VAR(Std_ReturnType,             AUTOMATIC)  dataServRetval_u8;        /* Variable to store service return value */
    VAR(boolean,            AUTOMATIC) isProtocolIPCanFD_b = FALSE;

	/* Initialization of local variables */
	*dataNegRespCode_u8      = 0x0;
    dataServRetval_u8=DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

	/* State machine for ReportFaultDetectionCounter */

	/* Initialization state */
	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
	{
		/* check for request length */
		if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
		{
			/* Initializing the filled response length in page and the total filled response length */
			Dcm_DspRDTCFilledRespLen_u32 = 0x0;
			Dcm_DspTotalRespLenFilled_u16 = 0x0;
			/* Set the variable to FALSE to indicate that the zero's should not be filled in page */

			Dcm_DspFillZeroes_b     = FALSE;
			/* Set the DTC Filter in DEM */
			dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( 0x00,
					DEM_DTC_KIND_ALL_DTCS,
					DEM_DTC_FORMAT_UDS,
					DEM_DTC_ORIGIN_PRIMARY_MEMORY,
					DEM_FILTER_WITH_SEVERITY_NO,
					DEM_SEVERITY_NO_SEVERITY,
					DEM_FILTER_FOR_FDC_YES
			);
			/* If the Filter Mask sent is accepted by DEM */
			if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
			{
				/* Update the subfunction in the response buffer */
				pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
				/* Update the response length */
				pMsgContext->resDataLen=1;

				/* Move the state to calculate the total number of DTC's */
				Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
			}
			/* Filter Mask not accepted by DEM */
			else
			{
				/* Set Negative response */
				*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                /*Return E_NOT_OK from the service*/
                dataServRetval_u8=E_NOT_OK;
			}
		}
		/* Request Length not correct */
		else
		{
			/* Set Negative response */
			*dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            /*Return E_NOT_OK from the service*/
            dataServRetval_u8=E_NOT_OK;
		}
	}

	/* State to calculate the number of filtered DTC */

	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
	{
		/* Call the DEM API to get filtered number of DTC */
		dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

		/* If filtered DTC number is obtained without error */
		if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
		{
			/* Check if number of filtered DTC's is greater than 0 */
			if(nrFltDTC_u16 !=0)
			{
				/* Calculate total response length */
		        pMsgContext->resDataLen = (Dcm_MsgLenType)(nrFltDTC_u16);
				pMsgContext->resDataLen <<= (Dcm_MsgLenType)0x02u;
		        pMsgContext->resDataLen += (Dcm_MsgLenType)(0x01u);
				/*Check if the total response data length is valid*/
				if(Dcm_Dsld_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE)
				{
					/* Set the variable to FALSE to indicate that the first page is not sent */
					Dcm_DspFirstPageSent_b  = FALSE;

					/* Move the state to next state */
					Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

					Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

					/* Call the DCm API and start Paged processing */
					Dcm_StartPagedProcessing(pMsgContext);

					/* Update the response length variables */
					Dcm_DspRDTCFilledRespLen_u32 = 0x01;
					Dcm_DspTotalRespLenFilled_u16 = 0x01;

				}
				else
				{
					/* Response buffer exceeded - set negative response code */
					*dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;

                    /*Return E_NOT_OK from the service*/
                    dataServRetval_u8=E_NOT_OK;
				}
			}
			else
			{
				/* Move the state to default state */
				Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
				dataServRetval_u8=E_OK;
			}
		}
		/* If more time is needed for getting the number of filtered DTC */
		else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
		{
			/* Do nothing - remain in the same state and call the API again */
            /*Return E_NOT_OK from the service*/
            dataServRetval_u8=DCM_E_PENDING;
		}
		else
		{
			/* Set negative response */
			*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

            /*Return E_NOT_OK from the service*/
            dataServRetval_u8=E_NOT_OK;
		}
	}
	/* State to get the filtered DTC, Fault counter value from DEM */
	else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
	{
		cntrLoop_qu8 = 0;
		/* Copy the maximum response length */
		dataResMaxLen_u32 = pMsgContext->resMaxDataLen;
		do
		{
			cntrLoop_qu8++;
			/* Get the DTC filtered and its fault count from DEM */
			dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(&dataDTC_u32, &cntrFault_s8);

			/* If the DTC was filtered without any error */
			if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
			{
				/* Copy the response length to local variable */
				dataRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32;
				/* Fill the response buffer with DTC and status */
				pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 16u);
				dataRespLen_u32++;
				pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 8u);
				dataRespLen_u32++;
				pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32);
				dataRespLen_u32++;
				pMsgContext->resData[dataRespLen_u32] = (uint8)(cntrFault_s8);
				dataRespLen_u32++;

				/* Copy back the response length to static variable */
				Dcm_DspRDTCFilledRespLen_u32 = dataRespLen_u32;

				/* Update the total response length filled with the bytes filled in the response in this iteration*/
				Dcm_DspTotalRespLenFilled_u16 = (uint16)(Dcm_DspTotalRespLenFilled_u16 + 0x04u);
				/* Check if total response length filled is greater than actual response length calculated */
				if(Dcm_DspTotalRespLenFilled_u16 >=  pMsgContext->resDataLen)
				{
					dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
				}

			}
			/* If more time is needed to get the filtered DTC */
			else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
			{
                /*Return E_NOT_OK from the service*/
                dataServRetval_u8=DCM_E_PENDING;
				break;
			}
			/* If all the DTC's are read completely */
			else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
			{
				/* Do nothing */
			}
			else
			{
				/* Check if first page is already sent or not */

				if(Dcm_DspFirstPageSent_b == FALSE)
				{
					/* Set Negative response */
					*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    /*Return E_NOT_OK from the service*/
                    dataServRetval_u8=E_NOT_OK;

				}
				/* First page is already sent so NRC cannot be set */
				else
				{
					/* Call process page with zero length to stop the response transmission immediately */
					Dcm_ProcessPage(0);

					/* Move the state to default state */
					Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
				}
			}
			/* Check if the buffer overflow happens or all filtered DTC's are read */

			isProtocolIPCanFD_b = Dcm_IsProtocolIPCanFD();
			if((dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC) || (((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > dataResMaxLen_u32) && (isProtocolIPCanFD_b!=FALSE))||  ((Dcm_DspRDTCFilledRespLen_u32>=7u)&&(isProtocolIPCanFD_b==FALSE)))
			{

				/* If first page is not sent yet */

				if(Dcm_DspFirstPageSent_b == FALSE)
				{
					/* Set the variable to TRUE indicating first page is sent */

					Dcm_DspFirstPageSent_b = TRUE;
				}
				if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
				{
					/* Calculating the number of remaining number of bytes to be filled in response */
					dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;

					Dcm_Dsp_RDTCFillZero(dataRespLen_u32);
				}
				/* Move the state to next state */
				Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

				/* Send the page for transmission */
				Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);

				/* Reset the response length */
				Dcm_DspRDTCFilledRespLen_u32 = 0x0;

				/* Change the return so that the loop won't get executed again */
				dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
			}

		}while((cntrLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK));
	}
	else
	{
		/* Do nothing */
	}

	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
	{
		/* Wait in this state for transmission of page */
	}
	/* State where zero's are filled in page if total response length filled is less than actual response length */
	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLZERO)
	{
		/* Calculating the number of remaining number of bytes to be filled in response */
		dataRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;

		Dcm_Dsp_RDTCFillZero(dataRespLen_u32);

		/* Move the state to next state */
		Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;

		/* Send the page for transmission */
		Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);

		Dcm_DspRDTCFilledRespLen_u32 = 0;
	}

	return dataServRetval_u8;
}



#else/*#if((DCM_PAGEDBUFFER_ENABLED!=DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT!=DCM_CFG_OFF))*/


FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFaultDetectionCounter (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
								{
	VAR(uint8_least,                      AUTOMATIC) cntrLoop_qu8;         /* Variable for loop counter */
	VAR(sint8,                            AUTOMATIC) cntrFault_s8;       /* Variable to store fault detection counter */
	VAR(Dem_ReturnSetFilterType,       AUTOMATIC) dataRetSetDTCFilter_u8; /* Return type for Dem_SetDTCFilter */
	VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8; /* Return type for Dem_GetNextFilteredDTC */
	VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8; /* Return type for Dem_GetNumberOfFilteredDTC */
	VAR(uint16,                          AUTOMATIC)  nrFltDTC_u16;     /* Variable to store number of filtered DTCs */
	VAR(uint32,                           AUTOMATIC) dataDTC_u32;            /* Variable to store DTC */
	VAR(Dcm_MsgLenType,                   AUTOMATIC) dataRespLen_u32;        /* Local variable for response length */
	VAR(Dcm_MsgLenType,                   AUTOMATIC) dataResMaxLen_u32;  /* Variable to store max response length */
    VAR(Std_ReturnType,                   AUTOMATIC)  dataServRetval_u8;
	/* Initialization of local variables */

    (void)(OpStatus);
    *dataNegRespCode_u8      = 0x0;
    dataServRetval_u8=DCM_E_PENDING;

	/* State machine for ReportFaultDetectionCounter */

	/* Initialization state */
	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
	{
		/* check for request length */
		if(pMsgContext->reqDataLen == DSP_RDTC_14_REQLEN)
		{
			/* Set the DTC Filter in DEM */
			dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( 0x00,
					DEM_DTC_KIND_ALL_DTCS,
					DEM_DTC_FORMAT_UDS,
					DEM_DTC_ORIGIN_PRIMARY_MEMORY,
					DEM_FILTER_WITH_SEVERITY_NO,
					DEM_SEVERITY_NO_SEVERITY,
					DEM_FILTER_FOR_FDC_YES
			);
			/* If the Filter Mask sent is accepted by DEM */
			if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
			{
				/* Update the subfunction in the response buffer */
				pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
				/* Update the response length */
				pMsgContext->resDataLen=1;

				/* Move the state to get the number of filtered DTCs */
				Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
			}
			/* Filter Mask not accepted by DEM */
			else
			{
				/* Set Negative response */
				*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataServRetval_u8=DCM_E_PENDING;
			}
		}
		/* Request Length not correct */
		else
		{
			/* Set Negative response */
			*dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataServRetval_u8=E_NOT_OK;
		}
	}

	/* State to get the  number of filtered DTC from DEM */
	if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFCALCNUMDTC)
	{
		/* Call the DEM API to get filtered number of DTC */
		dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);
		/* If filtered DTC number is obtained without error */
		if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
		{
			if(nrFltDTC_u16>0)
			{
			/* Move the state to fill the response */
			Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
			}
			else
			{
			/* Move the state to send positive response with only S/F in the response */
			Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
            dataServRetval_u8=E_OK;
			}
		}
		/* If more time is needed for getting the number of filtered DTC */
		else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
		{
			/* Do nothing - remain in the same state and call the API again */
            dataServRetval_u8=DCM_E_PENDING;
		}
		else
		{
			/* Set negative response */
			*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataServRetval_u8=E_NOT_OK;
		}

	}


	/* State to get the filtered DTC and status from DEM */
	else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
	{
		cntrLoop_qu8 = 0x00;
		/* Copy the maximum response length */
		dataResMaxLen_u32 = pMsgContext->resMaxDataLen;

		/* Copy the response length */
		dataRespLen_u32 = pMsgContext->resDataLen;

		/* Loop for maximum number of DTC's to read in a cycle */
		do
		{
			cntrLoop_qu8++;
			/* Get the DTC filtered and its fault count from DEM */
			dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndFDC(&dataDTC_u32, &cntrFault_s8);

						/* If the DTC was filtered without any error */
						if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
						{
							/* Check if the response buffer is available for filling the response */
							if((dataRespLen_u32 + 0x04u) <= dataResMaxLen_u32)
							{
								/* Fill the response buffer with DTC and status */
								pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 16u);
								dataRespLen_u32++;
								pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32 >> 8u);
								dataRespLen_u32++;
								pMsgContext->resData[dataRespLen_u32] = (uint8)(dataDTC_u32);
								dataRespLen_u32++;
								pMsgContext->resData[dataRespLen_u32] = (uint8)(cntrFault_s8);
								dataRespLen_u32++;
							}
							else
							{
								/* Response buffer exceeded - set negative response code */
								*dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                                dataServRetval_u8=E_NOT_OK;
							}
						}
						/* If more time is needed to get the filtered DTC */
						else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
						{

                            dataServRetval_u8=DCM_E_PENDING;
                            /* Nothing to do - Remain in the same state */
							break;;
						}
						/* If all the DTC's are read completely */
						else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
						{

			         	/*Reset State to DSP_RDTC_SFINIT*/
                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                            cntrLoop_qu8          = DCM_CFG_RDTC_MAXNUMDTCREAD;
                            dataServRetval_u8=E_OK;
		               	}
		            	else
		            	{
			          	/* Some problems has occured in DEM while reading DTC */
                            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            dataServRetval_u8=E_NOT_OK;
		             	}
		}while((cntrLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));


		/* Update the message table with response data length */
		pMsgContext->resDataLen = dataRespLen_u32;
	}
	else
	{
		dataServRetval_u8=E_NOT_OK;
	}

    return dataServRetval_u8;
}


#endif/*#if((DCM_PAGEDBUFFER_ENABLED!=DCM_CFG_OFF)&& (DCM_CFG_RDTCPAGEDBUFFERSUPPORT!=DCM_CFG_OFF))*/



#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

