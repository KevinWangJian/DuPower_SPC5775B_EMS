

#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(   (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF)\
       /* FC_VariationPoint_START */                        \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)\
       /* FC_VariationPoint_END */                          \
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)\
     ||(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
static FUNC(Dcm_MsgLenType, DCM_CODE)Dcm_Dsp_CalTotalResLengthForDTC(VAR(uint16,AUTOMATIC) NumOfFltDTC_u16,VAR(uint8,AUTOMATIC) reqSubfunction);
#endif
static FUNC(uint8, DCM_CODE)Dcm_Dsp_GetDTCRequestLength(CONST(uint8,AUTOMATIC) reqSubfunction);
static FUNC(uint8, DCM_CODE)Dcm_Dsp_CalDTCActiveMask(CONST(uint8,AUTOMATIC) statusAvailMask_u8,
                                                     CONST(uint8,AUTOMATIC) reqDtcStatus_u8,
                                                     CONST(uint8,AUTOMATIC) reqSubfunction);
static FUNC(void, DCM_CODE)Dcm_Dsp_CalDTCKindAndOrigin(P2VAR(Dem_DTCOriginType,AUTOMATIC,DCM_INTERN_DATA) dataDtcOrigin_u8,
                                                       P2VAR(Dem_DTCKindType,AUTOMATIC,DCM_INTERN_DATA) dataDtcKind_u8,
                                                       P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) dataDtcStatus_u8,
                                                       CONST(uint8,AUTOMATIC) reqSubfunction,
                                                       CONST(uint8,AUTOMATIC) reqDtcOriginData);
static FUNC(void, DCM_CODE)Dcm_Dsp_FillResBytesAndLength(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                         CONST(uint8,AUTOMATIC) reqSubfunction,
                                                         CONST(uint8,AUTOMATIC) statusAvailMask_u8);
static FUNC(Dem_ReturnGetNextFilteredDTCType, DCM_CODE)Dcm_Dsp_FillResDtcBuffer(VAR(uint32,AUTOMATIC) dtcData_u32,
                                                                                P2VAR(Dcm_MsgLenType,AUTOMATIC,DCM_INTERN_DATA) respLenNr_u32,
                                                                                VAR(uint8,AUTOMATIC) stDTCStatus_u8,
                                                                                P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
                                                                               );

/**
 **************************************************************************************************
 * Dcm_Dsp_ReportSupportedDTC :
 *  This function is used to implement the following subfunctions:
 *  0x02( Report DTC By Status Mask       )
 *  0x0A( Report Supported DTCs           )
 *  0x15( Report DTC By Permanent Status  )
 *  0x0F( Report Mirror Memory DTC By StatusMask  )
 *  0x17( ReportUserDefMemoryDTCByStatusMask)
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSupportedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                              AUTOMATIC) dataDTC_u32;              /* Variable to store DTC */
    VAR(uint8_least,                         AUTOMATIC) idxLoop_qu8;              /* Variable for loop counter */
    VAR(Dcm_MsgLenType,                      AUTOMATIC) nrRespLen_u32;            /* Local variable for response length */
    VAR(Dcm_MsgLenType,                      AUTOMATIC) nrResMaxDataLen_u32;      /* Variable to store max response length */
    VAR(uint16,                              AUTOMATIC) nrFltDTC_u16;             /* Variable to store number of filtered DTCs */
    VAR(uint8,                               AUTOMATIC) nrReqLength_u8;           /*Variable to store request length */
    VAR(uint8,                               AUTOMATIC) dataStatusAvailMask_u8;   /* Variable to store status availability mask */
    VAR(uint8,                               AUTOMATIC) stDTCStatus_u8;           /* Variable to store effective status mask */
    VAR(Dem_ReturnGetNextFilteredDTCType,    AUTOMATIC) dataRetGetNextFiltDTC_u8; /* Return type for Dem_GetNextFilteredDTC */
    VAR(Dem_ReturnGetNumberOfFilteredDTCType,AUTOMATIC) dataRetNumFltDTC_u8;      /* Return type for Dem_GetNumberOfFilteredDTC */
    VAR(Dem_ReturnSetFilterType,             AUTOMATIC) dataRetSetDTCFilter_u8;   /* Return type for Dem_SetDTCFilter */
    VAR(uint8,                               AUTOMATIC) dataSubfunc_u8;           /* Local variable to store the subfunction */
    VAR(Dem_DTCOriginType,                   AUTOMATIC) dataDemDTCOrigin_u8;      /* Local variable to store the memory type */
    VAR(Dem_DTCKindType,                     AUTOMATIC) dataDemDTCKind_u8;        /* Local variable to store the DTC Kind */
    VAR(Std_ReturnType,                      AUTOMATIC) dataretVal_u8;            /* Variable to store the returnType from DcmAppl API          */
    VAR(boolean,                             AUTOMATIC) IsProtocolIPCanFD_b;      /* Local variable to check whether the protocol is CANFD SPECIFIC PROTOCOLS*/
    static VAR(boolean,                        DCM_VAR) dataPending_flag_b;       /* varible to indicate datapending */

    /* Initialization of local variables */
    dataRetGetNextFiltDTC_u8 = DEM_FILTERED_OK;
    *dataNegRespCode_u8     = 0x0;
    dataretVal_u8 = DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

    /* State machine for Report Supported DTC */
    /* Initialization state */
    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
        /* Copy the subfunction parameter to the local variable */
        dataSubfunc_u8 = pMsgContext->reqData[0];
        /* calculate the request length according to the request data (subfunction No.) */
        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        /* Check for request length */
        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {
            /* If the available status mask is read successfully */
            if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
            {
                /* Initializing the filled response length in page and the total filled response length */
                Dcm_DspRDTCFilledRespLen_u32 = 0x00;
                Dcm_DspTotalRespLenFilled_u16 = 0x00;
                /* Set the variable to FALSE to indicate that the zero's should not be filled in page */
                Dcm_DspFillZeroes_b     = FALSE;
                /* initial the local copy of available mask */
                stDTCStatus_u8 = dataStatusAvailMask_u8;

                /* calculate the active DTC status mask for the service 0x02,0x13,0x0F and 0x17 */
                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                /* If the status mask is 0 */
                if(stDTCStatus_u8 != 0x0)
                {
                    /* Assign the DTC Origin as Primary memory */
                    dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                    /* Assign the Dtc kind as all DTCs*/
                    dataDemDTCKind_u8 = DEM_DTC_KIND_ALL_DTCS;

                    /* calculation of DTC Origin and DTC kind, update DTC mask */
                    Dcm_Dsp_CalDTCKindAndOrigin(&dataDemDTCOrigin_u8,
                                                &dataDemDTCKind_u8,
                                                &stDTCStatus_u8,
                                                dataSubfunc_u8,
                                                pMsgContext->reqData[2]
                                               );

                    /* Set the calculated info. to the DTC Filter in DEM */
                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(stDTCStatus_u8,
                                                              dataDemDTCKind_u8,
                                                              DEM_DTC_FORMAT_UDS,
                                                              dataDemDTCOrigin_u8,
                                                              DEM_FILTER_WITH_SEVERITY_NO,
                                                              DEM_SEVERITY_NO_SEVERITY,
                                                              DEM_FILTER_FOR_FDC_NO
                                                             );

                    /* If the Filter Mask sent is accepted by DEM */
                    if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
                    {
                        /* Move the state to calculate the number of filtered DTC */
                        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFCALCNUMDTC;
                    }
                    /* Filter Mask not accepted by DEM */
                    else
                    {
                        /* Set Negative response */
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataretVal_u8 = E_NOT_OK;
                    }
                }
                else
                {
                    /* Do Nothing */
                    dataretVal_u8 = E_OK;
                }
                /* Fill response bytes for subfunction 0x02,0x13,0x0F,0x15,0x17 or 0x0A */
                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }
            /* Status mask is not read properly from DEM */
            else
            {
                /* Set Negative response */
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
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
        dataSubfunc_u8 = pMsgContext->reqData[0];
        /* Call the DEM API to get filtered number of DTC */
        dataRetNumFltDTC_u8 = Dem_GetNumberOfFilteredDTC(&nrFltDTC_u16);

        /* If filtered DTC number is obtained without error */
        if(dataRetNumFltDTC_u8 == DEM_NUMBER_OK)
        {
            /* Check if number of filtered DTCs is nonzero */
            if(nrFltDTC_u16 !=0)
            {
                /* Calculate total response length */
                pMsgContext->resDataLen = Dcm_Dsp_CalTotalResLengthForDTC(nrFltDTC_u16,dataSubfunc_u8);

                if(Dcm_Dsld_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE)
                {
                    /* Set variable to FALSE to indicate that first page has not been sent */
                    Dcm_DspFirstPageSent_b  = FALSE;

                    /* Move the state to next state */
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;

                    Dcm_adrUpdatePage_pfct = &Dcm_Dsp_RDTCUpdatePage;

                    /* Call the DCM API and start Paged processing */
                    Dcm_StartPagedProcessing(pMsgContext);
                    /* Update the filled response length variable and total response length filled */
                    Dcm_DspRDTCFilledRespLen_u32 = 2;
                    Dcm_DspTotalRespLenFilled_u16 = 2;

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                    if(dataSubfunc_u8 == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                    {
                        /* Update the filled response length variable and total response length filled */
                        Dcm_DspRDTCFilledRespLen_u32 = 3;
                        Dcm_DspTotalRespLenFilled_u16 = 3;
                    }
#endif
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
            dataretVal_u8 = DCM_E_PENDING;
        }
        else
        {
            /* Set negative response */
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8 = E_NOT_OK;
        }
    }

    /* State to get the filtered DTC and status from DEM then fill the response */
    else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu8 = 0;
        /* Store the maximum response length in local variable */
        nrResMaxDataLen_u32 = Dcm_DspRDTCMaxRespLen_u32;

        /* loop till the maximum DTC's are read and the filtered DTC is read without error */
        do
        {
            idxLoop_qu8++;
            /* Call the DEM API and read DTC and its status */
            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(&dataDTC_u32, &stDTCStatus_u8);
            /* If the DTC is filtered without error */
            if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                if (   (Dcm_DsldPduInfo_st.SduLength != 0u)
                     &&(dataPending_flag_b == FALSE)
                   )
                {
                    nrRespLen_u32 = 0 ;
                    Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                    dataPending_flag_b = TRUE;
                }

                dataRetGetNextFiltDTC_u8 = Dcm_Dsp_FillResDtcBuffer(dataDTC_u32,&nrRespLen_u32,stDTCStatus_u8,pMsgContext);
            }
            /* If more time is needed to get the filtered DTC */
            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                /* Nothing to do - Remain in the same state */
                dataretVal_u8 = DCM_E_PENDING;
                break;
            }
            /* If all the filtered DTC's are read */
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

            IsProtocolIPCanFD_b = Dcm_IsProtocolIPCanFD();
            /* Check if the buffer overflow happens or all filtered DTC's are read */
            if(     ((IsProtocolIPCanFD_b) && ((Dcm_DspRDTCFilledRespLen_u32 + 0x04u) > nrResMaxDataLen_u32))
                ||  ((!IsProtocolIPCanFD_b) && (Dcm_DspRDTCFilledRespLen_u32>=7u))
                ||  (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
              )
            {
                /* If first page is not sent yet */
                if(Dcm_DspFirstPageSent_b == FALSE)
                {
                    /* Set the variable to TRUE indicating first page is sent */
                    Dcm_DspFirstPageSent_b = TRUE;
                }

                if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                {
                    if((Dcm_DsldPduInfo_st.SduLength != 0u) && (dataPending_flag_b == FALSE))
                    {
                        nrRespLen_u32 = 0 ;
                        Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
                        dataPending_flag_b = TRUE;
                    }

                    /* Calculating the number of remaining number of bytes to be filled in response */
                    nrRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;
                    Dcm_Dsp_RDTCFillZero(nrRespLen_u32);
                }

                if(  ((Dcm_DspRDTCFilledRespLen_u32 +2u) >= Dcm_DsldTransmit_st.dataTxDataLength_u32)
                   ||((Dcm_DspRDTCFilledRespLen_u32 +2u) >= nrResMaxDataLen_u32)
                   ||((Dcm_DspTotalRespLenFilled_u16+1u) >= Dcm_DsldTransmit_st.dataTxDataLength_u32)
                  )
                {
                    /* Move the state to next state */
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;
                    /* Send the page for transmission */
                    Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
                    dataPending_flag_b =FALSE;
                    /* Reset the response length */
                    Dcm_DspRDTCFilledRespLen_u32 = 0x0;
                    /* Change the return so that the loop won't get executed again */
                    dataRetGetNextFiltDTC_u8 = DEM_FILTERED_NO_MATCHING_DTC;
                }
            }

        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK));
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
        if((Dcm_DsldPduInfo_st.SduLength != 0u ) && (dataPending_flag_b == FALSE))
        {
            nrRespLen_u32 = 0 ;
            Dcm_DspRDTCFilledRespLen_u32 = Dcm_DspRDTCFilledRespLen_u32 + Dcm_DsldPduInfo_st.SduLength;
            dataPending_flag_b = TRUE;
        }
        /* Calculating the number of remaining number of bytes to be filled in response */
        nrRespLen_u32 = pMsgContext->resDataLen - Dcm_DspTotalRespLenFilled_u16;
        Dcm_Dsp_RDTCFillZero(nrRespLen_u32);
        /* Move the state to next state */
        Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFTXPAGE;
        /* Send the page for transmission */
        Dcm_ProcessPage(Dcm_DspRDTCFilledRespLen_u32);
        dataPending_flag_b = FALSE ;
        Dcm_DspRDTCFilledRespLen_u32 = 0;
    }
    return dataretVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_Dsp_CalTotalResLengthForDTC :
 *  This function is used to calcualte the total response length for the all dtcs for paged buffer
 * \param           uint16    Nummer of filtered dtc
 *                  uint8     requested sub function
 *
 * \retval          Dcm_MsgLenType  total length
 *
 **************************************************************************************************
 */

static FUNC(Dcm_MsgLenType, DCM_CODE)Dcm_Dsp_CalTotalResLengthForDTC(VAR(uint16,AUTOMATIC) NumOfFltDTC_u16, VAR(uint8,AUTOMATIC) reqSubfunction)
{
    Dcm_MsgLenType totalLength = 0;

    totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x02);
#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if (reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {
        totalLength = (Dcm_MsgLenType) ((((uint16) NumOfFltDTC_u16) << 0x02u) + 0x03);
    }
#endif
    return totalLength;
}

#else

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSupportedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                           AUTOMATIC) dataDTC_u32;              /* Variable to store DTC */
    VAR(Dcm_MsgLenType,                   AUTOMATIC) nrRespLen_u32;            /* Local variable for response length */
    VAR(Dcm_MsgLenType,                   AUTOMATIC) nrResMaxDataLen_u32;      /* Variable to store max response length */
    VAR(uint8_least,                      AUTOMATIC) idxLoop_qu8;              /* Variable for loop counter */
    VAR(uint8,                            AUTOMATIC) nrReqLength_u8;           /* Variable to store request length */
    VAR(uint8,                            AUTOMATIC) stDTCStatus_u8;           /* Variable to store effective status mask */
    VAR(uint8,                            AUTOMATIC) dataStatusAvailMask_u8;   /* Variable to store status availability mask */
    VAR(uint8,                            AUTOMATIC) dataSubfunc_u8;           /* Local variable to store the subfunction */
    VAR(Dem_DTCOriginType,                AUTOMATIC) dataDemDTCOrigin_u8;      /* Local variable to store the memory type */
    VAR(Dem_DTCKindType,                  AUTOMATIC) dataDemDTCKind_u8;        /* Local variable to store the DTC Kind */
    VAR(Dem_ReturnSetFilterType,          AUTOMATIC) dataRetSetDTCFilter_u8;   /* Return type for Dem_SetDTCFilter */
    VAR(Dem_ReturnGetNextFilteredDTCType, AUTOMATIC) dataRetGetNextFiltDTC_u8; /* Return type for Dem_GetNextFilteredDTC */
    VAR(Std_ReturnType,                   AUTOMATIC) dataretVal_u8;            /* Variable to store the returnType from DcmAppl API */
    (void)OpStatus;
    /* Initialization of local variables */
    *dataNegRespCode_u8 = 0x0;
    dataretVal_u8=DCM_E_PENDING;

    /* State machine for Report Supported DTC */
    /* Initialization state */
    if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT)
    {
        /* Copy the subfunction parameter to the local variable */
        dataSubfunc_u8 = pMsgContext->reqData[0];
        /* calculate the request length according to the reqest data (subfunction No.) */
        nrReqLength_u8 = Dcm_Dsp_GetDTCRequestLength(dataSubfunc_u8);

        /* check for request length */
        if(pMsgContext->reqDataLen == nrReqLength_u8)
        {
            /* If the available status mask is read successfully */
            if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
            {
                /* Store Status Availability mask in stDTCStatus_u8 for S/F 0x0A and 0x15 */
                stDTCStatus_u8  = dataStatusAvailMask_u8;

                /* calculate the active DTC status mask for the service 0x02,0x13,0x0F and 0x17 */
                stDTCStatus_u8 = Dcm_Dsp_CalDTCActiveMask(dataStatusAvailMask_u8, pMsgContext->reqData[1],dataSubfunc_u8);

                /* If the status mask is 0 */
                if(stDTCStatus_u8 != 0x0u)
                {
                    /* Assign the DTC Origin as Primary memory */
                    dataDemDTCOrigin_u8 = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                    /* Assign the DTC kind as ALL DTCs */
                    dataDemDTCKind_u8 = DEM_DTC_KIND_ALL_DTCS;

                    /* calculation of DTC Origin and DTC kind, update DTC mask */
                     Dcm_Dsp_CalDTCKindAndOrigin(&dataDemDTCOrigin_u8,
                                                 &dataDemDTCKind_u8,
                                                 &stDTCStatus_u8,
                                                 dataSubfunc_u8,
                                                 pMsgContext->reqData[2]
                                                );


                    /* Set the DTC Filter in DEM */
                    dataRetSetDTCFilter_u8 = Dem_SetDTCFilter(stDTCStatus_u8,
                                                              dataDemDTCKind_u8,
                                                              DEM_DTC_FORMAT_UDS,
                                                              dataDemDTCOrigin_u8,
                                                              DEM_FILTER_WITH_SEVERITY_NO,
                                                              DEM_SEVERITY_NO_SEVERITY,
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
                else
                {
                    /* Do nothing. Response buffer already filled with subfunction and status availability mask */
                    dataretVal_u8=E_OK;
                }
                /* Fill the other response bytes for subfunction 0x02,0x13,0x0F,0x15,0x17 or 0x0A */
                Dcm_Dsp_FillResBytesAndLength(pMsgContext,dataSubfunc_u8, dataStatusAvailMask_u8);
            }
            /* Status mask is not read properly from DEM */
            else
            {
                /* Set Negative response */
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
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

    /* State to get the filtered DTC and status from DEM */
    else if(Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFFILLRESP)
    {
        idxLoop_qu8 = 0x00;
        /* Copy the maximum response length */
        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        /* Copy the response length */
        nrRespLen_u32 = pMsgContext->resDataLen;

        /* Loop for maximum number of DTC's to read in a cycle */
        do
        {
            idxLoop_qu8++;
            /* Get the DTC filtered and its status from DEM */
            dataRetGetNextFiltDTC_u8 = Dem_GetNextFilteredDTC(&dataDTC_u32, &stDTCStatus_u8);

            /* If the DTC was filtered without any error */
            if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_OK)
            {
                /* Check if the response buffer is available for filling the response */
                if((nrRespLen_u32 + 0x04u) <= nrResMaxDataLen_u32)
                {
                   (void)Dcm_Dsp_FillResDtcBuffer(dataDTC_u32, &nrRespLen_u32, stDTCStatus_u8,pMsgContext);
                }
                else
                {
                    /* Response buffer exceeded - set negative response code */
                    *dataNegRespCode_u8     = DCM_E_RESPONSETOOLONG;
                    dataretVal_u8=E_NOT_OK;
                }
            }
            /* If more time is needed to get the filtered DTC */
            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_PENDING)
            {
                /* Nothing to do - Remain in the same state */
                dataretVal_u8=DCM_E_PENDING;
                break;
            }
            /* If all the DTC's are read completely */
            else if(dataRetGetNextFiltDTC_u8 == DEM_FILTERED_NO_MATCHING_DTC)
            {

                /*Reset State to DSP_RDTC_SFINIT*/
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                idxLoop_qu8            = DCM_CFG_RDTC_MAXNUMDTCREAD;
                dataretVal_u8=E_OK;
            }
            else
            {
                /* Some problems has occurred in DEM while reading DTC */
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }while((idxLoop_qu8 < DCM_CFG_RDTC_MAXNUMDTCREAD) && (*dataNegRespCode_u8==0));


        /* Update the message table with response data length */
        pMsgContext->resDataLen = nrRespLen_u32;
    }
    else
    {
        /* Do nothing */
    }
    return dataretVal_u8;
}
#endif


/**
 **************************************************************************************************
 * Dcm_Dsp_GetDTCRequestLength :
 *  This function is used to calcualte the request length for different sub function
 * \param           cosnt uint8     requested sub function
 *
 * \retval          uint8           length
 *
 **************************************************************************************************
 */
static FUNC(uint8, DCM_CODE)Dcm_Dsp_GetDTCRequestLength(CONST(uint8,AUTOMATIC) reqSubfunction)
{
    VAR(uint8, AUTOMATIC) reqLength_u8;

    /* Update the request length for sub functions 0xA and 0x15 */
    reqLength_u8 = DSP_RDTC_0A_15_REQLEN;

    /* Check if the subfunction is 0x02,0x13,0x0F or 0x17 */
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)|| \
    /* FC_VariationPoint_START */                           \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)|| \
    /* FC_VariationPoint_END */                             \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF))

    if (    (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)
            /* FC_VariationPoint_START */
         || (reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
            /* FC_VariationPoint_END */
         || (reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
       )
    {   /* Update the request length */
        reqLength_u8 = DSP_REPDTCBYSTMASK_REQLEN;
    }
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
    if (reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
    {
        /* Update the request length */
        reqLength_u8 = DSP_RDTC_17_REQLEN;
    }
#endif

    return reqLength_u8;
}

/**
 **************************************************************************************************
 * Dcm_Dsp_CalDTCActiveMask :
 *  This function is used to calcualte effective dtc mask for sub function 0x02, 0x13, 0x0F, 0x17
 * \param           const uint8     statusAvailMask_u8
 *                  const uint8     reqDtcStatus_u8
 *                  const uint8     reqSubfunction
 *
 * \retval          uint8     calculated Dtc Status mask
 *
 **************************************************************************************************
 */
static FUNC(uint8, DCM_CODE)Dcm_Dsp_CalDTCActiveMask(CONST(uint8,AUTOMATIC) statusAvailMask_u8, CONST(uint8,AUTOMATIC) reqDtcStatus_u8,CONST(uint8,AUTOMATIC) reqSubfunction )
{
    uint8 calDTCStatus_u8 = statusAvailMask_u8;

/* calculate the DTC status mask for the service 0x02,0x13,0x0F and 0x17 */
#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)   \
      /* FC_VariationPoint_START */                           \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)   \
      /* FC_VariationPoint_END */                             \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)   \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

                /* Check if the subfunction is 0x02,0x13,0x0F or 0x17 */
                if(     (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)
                        /* FC_VariationPoint_START */
                      ||(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                        /* FC_VariationPoint_END */
                      ||(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                      ||(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                  )
                {
                    /* Calculate the effective status mask */
                    calDTCStatus_u8 = (statusAvailMask_u8 & reqDtcStatus_u8);
                }
#endif

    return calDTCStatus_u8;
}

/**
 **************************************************************************************************
 * Dcm_Dsp_CalDTCKindAndOrigin :
 *  This function is used to calcualte dtc kind, dtc origin and dtc status for different sub function
 * \param           *Dem_DTCOriginType     dtc origin
 *                  *Dem_DTCKindType       dtc kind
 *                  *uint8                 dtc status
 *                  const uint8            requested sub function
 *                  const uint8            requested origin data
 *
 * \retval          none
 *
 **************************************************************************************************
 */

static FUNC(void, DCM_CODE)Dcm_Dsp_CalDTCKindAndOrigin(P2VAR(Dem_DTCOriginType,AUTOMATIC,DCM_INTERN_DATA) dataDtcOrigin_u8,
                                                       P2VAR(Dem_DTCKindType,AUTOMATIC,DCM_INTERN_DATA) dataDtcKind_u8,
                                                       P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) dataDtcStatus_u8,
                                                       CONST(uint8,AUTOMATIC) reqSubfunction,
                                                       CONST(uint8,AUTOMATIC) reqDtcOriginData
                                                      )
{

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                    if(reqSubfunction == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                    {
                        /* Set DTC origin as Memory selection from the request */
                        *dataDtcOrigin_u8 = reqDtcOriginData;
                    }
#else
                    DCM_UNUSED_PARAM(reqDtcOriginData);
#endif

#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF))
                   /* If the subfunction sent is 0x0A or 0x15 */
                    if(  (reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)
                       ||(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                      )
                    {
                        /* Status Mask assigned 0x00 , to filter all DTCs */
                        *dataDtcStatus_u8 = DSP_REPORT_ALL_DTC;
                    }
                    /* If the sunfunction sent is 0x15 */
                    if(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                    {
                        /* Assign the DTC Origin as Permanent memory */
                        *dataDtcOrigin_u8 = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
                    }
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)
                    /* Check if the subfunction is 0x0F */
                    if(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                    {
                        /* Assign the DTC Origin as Mirror memory */
                        *dataDtcOrigin_u8 = DEM_DTC_ORIGIN_MIRROR_MEMORY;
                    }
#endif
                    /* FC_VariationPoint_START */
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)
                    /* Check if the subfunction is 0x13 */
                    if(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                    {
                        /* Assign the DTC kind as emission related OBD */
                        *dataDtcKind_u8 = DEM_DTC_KIND_EMISSION_REL_DTCS;
                    }
#else
                    DCM_UNUSED_PARAM(dataDtcKind_u8);
#endif
                    /* FC_VariationPoint_END */

}

/**
 **************************************************************************************************
 * Dcm_Dsp_FillResBytesAndLength :
 *  This function is used to fill the response bytes and update the length of pMsgcontext
 * \param           *Dcm_MsgContextType         pMsgContext
 *                  const uint8                 requested sub function
 *                  const uint8                 available status mask
 *
 * \retval          none
 *
 **************************************************************************************************
 */
static FUNC(void, DCM_CODE)Dcm_Dsp_FillResBytesAndLength(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                                         CONST(uint8,AUTOMATIC) reqSubfunction,
                                                         CONST(uint8,AUTOMATIC) statusAvailMask_u8)
{
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
                if(reqSubfunction  == DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK)
                {
                    pMsgContext->resData[1] = pMsgContext->reqData[2];
                    pMsgContext->resData[2] = statusAvailMask_u8;
                    pMsgContext->resDataLen = 0x03;
                }
#endif

#if(  (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)\
    /* FC_VariationPoint_START */                          \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)\
    /* FC_VariationPoint_END */                            \
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)\
    ||(DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF))

                /* Check if the subfunction is 0x02,0x13,0x0F,0x0A or 0x15 */
                if(   (reqSubfunction == DSP_REPORT_DTC_BY_STATUS_MASK)
                      /* FC_VariationPoint_START */
                    ||(reqSubfunction == DSP_REPORT_OBD_DTC_BY_STATUS_MASK)
                      /* FC_VariationPoint_END */
                    ||(reqSubfunction == DSP_REPORT_MIRROR_MEMORY_DTC)
                    ||(reqSubfunction == DSP_REPORT_SUPPORTED_DTCS)
                    ||(reqSubfunction == DSP_REPORT_DTC_PERMANENT_STATUS)
                  )
                {
                    pMsgContext->resData[1] = statusAvailMask_u8;
                    pMsgContext->resDataLen = 0x02;
                }

#endif
                /* Fill the first response byte with subfunction No. */
                pMsgContext->resData[0] = reqSubfunction;

}

/**
 **************************************************************************************************
 * Dcm_Dsp_FillResDtcBuffer :
 *  This function is used to fill response dtc buffer for paged buffer and none paged buffer
 * \param           uint32                      dtc Data
 *                  *Dcm_MsgLenType             response length
 *                  uint8                       dtc status mask
 *                  const * Dcm_MsgContextType  pMsgContext
 *
 * \retval          Dem_ReturnGetNextFilteredDTCType    next get dtc  return state
 *
 **************************************************************************************************
*/

static FUNC(Dem_ReturnGetNextFilteredDTCType, DCM_CODE)Dcm_Dsp_FillResDtcBuffer(    VAR(uint32,AUTOMATIC) dtcData_u32,
                                                                                  P2VAR(Dcm_MsgLenType,AUTOMATIC,DCM_INTERN_DATA) respLenNr_u32,
                                                                                    VAR(uint8,AUTOMATIC) stDTCStatus_u8,
                                                                                P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext
                                                                               )
{
    Dem_ReturnGetNextFilteredDTCType RetGetNextFiltDtc = DEM_FILTERED_OK;

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    /* Copy the response length to local variable */
    *respLenNr_u32 = Dcm_DspRDTCFilledRespLen_u32;


    /* Fill the response buffer */
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32 >> 16u);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32 >> 8u);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = (uint8)(dtcData_u32);
    (*respLenNr_u32)++;
    Dcm_DspRDTCRespBufPtr_u8[*respLenNr_u32] = stDTCStatus_u8;
    (*respLenNr_u32)++;

    /* Copy back the response length to static variable */
    Dcm_DspRDTCFilledRespLen_u32 = *respLenNr_u32;

    /* Update the total response length filled with the bytes filled in the response in this iteration*/
    Dcm_DspTotalRespLenFilled_u16 = (uint16)(Dcm_DspTotalRespLenFilled_u16 + 0x04u);

    /* Check if total response length filled is greater than actual response length calculated */
    if(Dcm_DspTotalRespLenFilled_u16 >= pMsgContext->resDataLen)
    {
        RetGetNextFiltDtc = DEM_FILTERED_NO_MATCHING_DTC;
    }
#else

        /* Fill the response buffer with DTC and status */
        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32 >> 16u);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32 >> 8u);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = (uint8)(dtcData_u32);
        (*respLenNr_u32)++;
        pMsgContext->resData[*respLenNr_u32] = stDTCStatus_u8;
        (*respLenNr_u32)++;

#endif
    return RetGetNextFiltDtc;

}



#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#endif

