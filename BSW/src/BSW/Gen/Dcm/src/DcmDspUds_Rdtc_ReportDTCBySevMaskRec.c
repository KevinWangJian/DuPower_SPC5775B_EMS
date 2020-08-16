


#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 **************************************************************************************************
 * Dcm_Dsp_ReportDTCBySeverityMaskRecord :
 *  This function is used to read a list of DTC severity and functional unit information,
 *  which satisfies a client-defined severity mask record
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCBySeverityMaskRecord
                                  (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                          AUTOMATIC)  dataDTC_u32;               /* Variable to store DTC */
    VAR(Dcm_MsgLenType,                  AUTOMATIC)  nrResDataLen_u32;        /* Local variable for response length */
    VAR(Dcm_MsgLenType,                  AUTOMATIC)  nrResMaxDataLen_u32;     /* Variable to store max response length */
    VAR(uint16,                          AUTOMATIC)  nrFltDTC_u16;     /* Variable to store number of filtered DTCs */
    VAR(uint8_least,                     AUTOMATIC)  idxLoop_qu8;            /* Variable for loop counter */
    VAR(uint8,                           AUTOMATIC)  dataDTCFunctionalUnit_u8;  /* Variable to store DTC functional unit */
    VAR(uint8,                           AUTOMATIC)  dataStatusAvailMask_u8;
    VAR(uint8,                           AUTOMATIC)  stDTCStatus_u8;     /* Variable for storing effective status mask */
    VAR(Dem_ReturnSetFilterType,         AUTOMATIC)  dataRetSetDTCFilter_u8;    /* Return value for Dem_SetDTCFilter */
    VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;
    VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)  dataretGetNextFiltDTC_u8;  /* Return from Dem_GetNextFilteredDTC */
    VAR(Dem_DTCSeverityType,             AUTOMATIC)  dataDTCSeverity_u8;        /* Variable to store DTC Severity Mask */
    VAR(Std_ReturnType,                  AUTOMATIC)  dataretVal_u8;
    static VAR(boolean, DCM_VAR) dataPending_flag_b; /* varible to indicate datapending */

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* Initialization of local variables */
    *dataNegRespCode_u8     = 0x00;
    dataretGetNextFiltDTC_u8 = DEM_FILTERED_OK;
    dataretVal_u8 = DCM_E_PENDING;

    /* State machine for Report DTC By Severity Mask */
    /* Initialization state */
    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
        /* check for request length */
        if(pMsgContext->reqDataLen == DSP_REPDTCBYSEVMASK_REQLEN )
        {
            /* Store the severity mask to local variable */
            dataDTCSeverity_u8 = pMsgContext->reqData[1] ;

            /*Check for any invalid Severity Bits set*/
            if ((dataDTCSeverity_u8 & 0x1Fu) == 0x00u)
            {
                /* If the available status mask is read successfully */
                if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
                {
                    /* Initializing the filled response length in page and the total filled response length */
                    Dcm_DspRDTCFilledRespLen_u32 = 0x0;
                    Dcm_DspTotalRespLenFilled_u16 = 0x0;

                    /* Set the variable to FALSE to indicate that the zero's should not be filled in page */

                    Dcm_DspFillZeroes_b     = FALSE;

                    /* Copy the status mask to the local variable */
                    stDTCStatus_u8 = pMsgContext->reqData[2];

                    /* Fill the response bytes */
                    pMsgContext->resData[0] = DSP_REPORT_DTC_BY_SEVERITY_MASK;
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;

                    /*Get the effective status mask*/
                    stDTCStatus_u8 = (stDTCStatus_u8 & dataStatusAvailMask_u8);

                    if(stDTCStatus_u8 != 0x0)
                    {
                        /*Call API to set the DTC Filter */
                        dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(   stDTCStatus_u8,
                                                                 DEM_DTC_KIND_ALL_DTCS,
                                                                 DEM_DTC_FORMAT_UDS,
                                                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                 DEM_FILTER_WITH_SEVERITY_YES,
                                                                 dataDTCSeverity_u8,
                                                                 DEM_FILTER_FOR_FDC_NO
                                                             );
                        if (dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                        {
                            /* Move the state to fill the response */
                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
                        }
                        else
                        {
                            /*Set Negative Response*/
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            dataretVal_u8 = E_NOT_OK;
                        }
                    }
                    else
                    {
                        /* Do Nothing */
                        dataretVal_u8 = E_OK;
                    }

                }
                /* Status mask is not read properly from DEM */
                else
                {
                    /* Set Negative response */
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else
            {
                /*Set Negative Response*/
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8 = E_NOT_OK;
            }
        }

        /* Request Length not correct */
        else
        {
            /* Set Negative response */
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8 = E_NOT_OK;
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

            if(nrFltDTC_u16 !=0)
            {
                /* Calculate total response length */
                pMsgContext->resDataLen = (Dcm_MsgLenType)((Dcm_MsgLenType)(nrFltDTC_u16 * 0x06u) + (Dcm_MsgLenType)0x02);
				/*Check if  Positive response data length is set to TRUE and max dat length is greater than 7*/
                if((Dcm_Dsld_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE) && (pMsgContext->resMaxDataLen > 7u))
                {
                    /* Set the variable to FALSE to indicate that the first page is not sent */

                    Dcm_DspFirstPageSent_b  = FALSE;

                    /* Move the state to next state */
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    /* Call the DCm API and start Paged processing */
                    Dcm_StartPagedProcessing(pMsgContext);

                    /* Update the response length variables */
                    Dcm_DspRDTCFilledRespLen_u32 = 0x02;
                    Dcm_DspTotalRespLenFilled_u16 = 0x02;

                }
                else
                {
                    /* Response buffer exceeded - set negative response code */
                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else
            {
                /* Move the state to default state */
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                dataretVal_u8 = E_OK;
            }
        }
        /* If more time is needed for getting the number of filtered DTC */
        else if(dataRetNumFltDTC_u8 == DEM_NUMBER_PENDING)
        {
            /* Do nothing - remain in the same state and call the API again */
        }
        else
        {
            /* Set negative response */
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8 = E_NOT_OK;
        }
    }

    /* State to get the filtered DTC, severity, status and functional unit information from DEM */
    else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu8 = 0;

        /* Store the maximum response length in local variable */
        nrResMaxDataLen_u32 = Dcm_DspRDTCMaxRespLen_u32;

        /* Loop for maximum number of DTC's to read in a cycle */
        do
        {
            idxLoop_qu8++;
            /* Get the DTC, severity, status and functional unit from DEM */
            dataretGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndSeverity(&dataDTC_u32,
                                                                     &stDTCStatus_u8,
                                                                     &dataDTCSeverity_u8,
                                                                     &dataDTCFunctionalUnit_u8);
            /* If the DTC was filtered without any error */
            if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                if (Dcm_DsldPduInfo_st.SduLength != 0u)
                {
                    if (dataPending_flag_b == FALSE)
                    {
                        nrResDataLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }
                }

                /* Copy the response length to local variable */
                 nrResDataLen_u32 = Dcm_DspRDTCFilledRespLen_u32;
                /* Fill the response buffer with DTC and status */
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = dataDTCSeverity_u8;
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = dataDTCFunctionalUnit_u8;
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32>>16u);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32>>8u);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                nrResDataLen_u32++;
                Dcm_DspRDTCRespBufPtr_u8[nrResDataLen_u32] = stDTCStatus_u8;
                nrResDataLen_u32++;

                /* Copy back the response length to static variable */
                Dcm_DspRDTCFilledRespLen_u32 = nrResDataLen_u32;

                /* Update the total response length filled with the bytes filled in the response in this iteration*/
                Dcm_DspTotalRespLenFilled_u16 = (uint16)(Dcm_DspTotalRespLenFilled_u16 + 0x06);

                /* Check if total response length filled is greater than actual response length calculated */
                if(Dcm_DspTotalRespLenFilled_u16 >=  pMsgContext->resDataLen)
                {
                    dataretGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }
            /* If more time is needed to get the filtered DTC */
            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                break;
            }
            /* If all the DTC's are read completely */
            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {
                /* Do nothing */
            }
            else
            {
                /* Check if first page is already sent or not */

                if(Dcm_DspFirstPageSent_b == FALSE)
                {
                    /* Set Negative response */
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    dataretVal_u8 = E_NOT_OK;
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
            /*If Return from Dem_GetNextFilteredDTC is equal to 0x01 and Dcm_IsProtocolIPCanFD is set to TRUE and Dcm_DspRDTC FilledRespLen is greater than or equal to 7*/

            /* MR12 RULE 13.5 VIOLATION: The right hand operand of '&&' or '||' has side effects - The statements inside needs to be executed only if all the conditions are satisfied */
            if((dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC) || (((Dcm_DspRDTCFilledRespLen_u32 + 0x06u) > nrResMaxDataLen_u32) && (Dcm_IsProtocolIPCanFD()!=FALSE))|| ((Dcm_DspRDTCFilledRespLen_u32>=7u)&&(Dcm_IsProtocolIPCanFD()==FALSE)))
            {

                /* If first page is not sent yet */

                if(Dcm_DspFirstPageSent_b == FALSE)
                {
                    /* Set the variable to TRUE indicating first page is sent */

                    Dcm_DspFirstPageSent_b = TRUE;
                }


                if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                {
                    if((Dcm_DsldPduInfo_st.SduLength != 0u)&& (dataPending_flag_b == FALSE))
                    {
                        nrResDataLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }
                    /* Calculating the number of remaining number of bytes to be filled in response */
                    nrResDataLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;
                    Dcm_Dsp_RDTCFillZero(nrResDataLen_u32);

                }
				if(
				        ((Dcm_DspRDTCFilledRespLen_u32 + 0x6u) >= Dcm_DsldTransmit_st.dataTxDataLength_u32)
				        ||
				        ((Dcm_DspRDTCFilledRespLen_u32 + 0x6u )>=   nrResMaxDataLen_u32)
				        ||
				        ((Dcm_DspTotalRespLenFilled_u16 + 1u)>= Dcm_DsldTransmit_st.dataTxDataLength_u32)
				        )
                {
				    /* Move the state to next state */
				    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;
				    /* Send the page for transmission */
				    Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
				    dataPending_flag_b = FALSE;
				    /* Reset the response length */
				    Dcm_DspRDTCFilledRespLen_u32 = 0x0;
				    /* Change the return so that the loop won't get executed again */
				    dataretGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }

        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK));
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
        if((Dcm_DsldPduInfo_st.SduLength != 0u )&& (dataPending_flag_b == FALSE))
        {
            nrResDataLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            dataPending_flag_b = TRUE;
        }
        /* Calculating the number of remaining number of bytes to be filled in response */
        nrResDataLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;
        Dcm_Dsp_RDTCFillZero(nrResDataLen_u32);
        /* Move the state to next state */
        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;
        /* Send the page for transmission */

        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        dataPending_flag_b =FALSE;

        Dcm_DspRDTCFilledRespLen_u32 = 0;
    }
        return dataretVal_u8;
}

#else

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCBySeverityMaskRecord
                                  (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    VAR(uint32,                          AUTOMATIC)  dataDTC_u32;               /* Variable to store DTC */
    VAR(Dcm_MsgLenType,                  AUTOMATIC)  nrResDataLen_u32;        /* Local variable for response length */
    VAR(Dcm_MsgLenType,                  AUTOMATIC)  nrResMaxDataLen_u32;     /* Variable to store max response length */
    VAR(uint8_least,                     AUTOMATIC)  idxLoop_qu8;            /* Variable for loop counter */
    VAR(uint8,                           AUTOMATIC)  dataDTCFunctionalUnit_u8;  /* Variable to store DTC functional unit */
    VAR(uint8,                           AUTOMATIC)  dataStatusAvailMask_u8; /* Variable to fill status availability mask*/
    VAR(Dem_ReturnSetFilterType,      AUTOMATIC)     dataRetSetDTCFilter_u8;    /* Return value for Dem_SetDTCFilter */
    VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)  dataretGetNextFiltDTC_u8;  /* Return from Dem_GetNextFilteredDTC */
    VAR(uint8,                           AUTOMATIC)  stDTCStatus_u8;          /* Variable for available status mask */
    VAR(Dem_DTCSeverityType,             AUTOMATIC)  dataDTCSeverity_u8;        /* Variable to store DTC Severity Mask */
    VAR(Std_ReturnType,                  AUTOMATIC)  dataretVal_u8;              /* Variable to store the service return value */

    (void)OpStatus;
    /* Initialization of local variables */
    *dataNegRespCode_u8     = 0x00;
    dataretVal_u8 = DCM_E_PENDING;

    /* State machine for Report DTC By Severity Mask  */
    /* Initialization state */
    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
        /* check for request length */
        if(pMsgContext->reqDataLen == DSP_REPDTCBYSEVMASK_REQLEN )
        {
            /* Store the severity mask to local variable */
            dataDTCSeverity_u8 = pMsgContext->reqData[1] ;

            /*Check for any invalid Severity Bits set*/
            if ((dataDTCSeverity_u8 & 0x1Fu) == 0x00u)
            {
                /* If the available status mask is read successfully */
                if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
                {
                    /* Copy the status mask to the local variable */
                    stDTCStatus_u8 = pMsgContext->reqData[2];

                    /* Fill the response bytes */
                    pMsgContext->resData[0] = DSP_REPORT_DTC_BY_SEVERITY_MASK;
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;

                    /*Get the effective status mask*/
                    stDTCStatus_u8 = (stDTCStatus_u8 & dataStatusAvailMask_u8);

                    if(stDTCStatus_u8 != 0x0)
                    {
                        /*Call API to set the DTC Filter */
                        dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(   stDTCStatus_u8,
                                                                 DEM_DTC_KIND_ALL_DTCS,
                                                                 DEM_DTC_FORMAT_UDS,
                                                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                                 DEM_FILTER_WITH_SEVERITY_YES,
                                                                 dataDTCSeverity_u8,
                                                                 DEM_FILTER_FOR_FDC_NO
                                                             );
                        if (dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                        {
                            /* Move the state to fill the response */
                            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
                        }
                        else
                        {
                            /*Set Negative Response*/
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            dataretVal_u8 = E_NOT_OK;
                        }
                    }
                    else
                    {
                        /* Do nothing. Response buffer is already filled with subfunction and availability status */
                        dataretVal_u8 = E_OK;
                    }

                }
                /* Status mask is not read properly from DEM */
                else
                {
                    /* Set Negative response */
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            else
            {
                /*Set Negative Response*/
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8 = E_NOT_OK;
            }
        }

        /* Request Length not correct */
        else
        {
            /* Set Negative response */
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            dataretVal_u8 = E_NOT_OK;
        }
    }
    /* State to get the filtered DTC , severity , status and functional unit information from DEM */
    else if( Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu8 = 0;

        /* Copy the maximum response length */
        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        /* Copy the response length */
        nrResDataLen_u32 = pMsgContext->resDataLen;

        /* Loop for maximum number of DTC's to read in a cycle */
        do
        {
            idxLoop_qu8++;
            /* Get the DTC, severity, status and functional unit from DEM */
            dataretGetNextFiltDTC_u8 = Dem_GetNextFilteredDTCAndSeverity(&dataDTC_u32,
                                                                     &stDTCStatus_u8,
                                                                     &dataDTCSeverity_u8,
                                                                     &dataDTCFunctionalUnit_u8);
            /* If the DTC was filtered without any error */
            if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                /* Check if the response buffer is available for filling the response */
                if((nrResDataLen_u32 + 0x06u) <= nrResMaxDataLen_u32)
                {
                    /* Fill the response buffer with DTC and status */
                    pMsgContext->resData[nrResDataLen_u32] = dataDTCSeverity_u8;
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = dataDTCFunctionalUnit_u8;
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32>>16u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32>>8u);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = (uint8)(dataDTC_u32);
                    nrResDataLen_u32++;
                    pMsgContext->resData[nrResDataLen_u32] = stDTCStatus_u8;
                    nrResDataLen_u32++;
                }
                else
                {
                    /* Response buffer exceeded - set negative response code */
                    *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8 = E_NOT_OK;
                }
            }
            /* If more time is needed to get the filtered DTC */
            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                break;
            }
            /* If all the DTC's are read completely */
            else if(dataretGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {
                /*Reset State to DSP_RDTC_SFINIT*/
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                idxLoop_qu8            = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataretVal_u8 = E_OK;
            }
            /* If DEM returns DEM_FILTERED_WRONG_DTCKIND */
            else
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8 = E_NOT_OK;
            }
        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));

        /* Update the message table with response data length */
        pMsgContext->resDataLen = nrResDataLen_u32;
    }
	else
	{
		/* Do nothing */
	}
    return dataretVal_u8;
}
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif


