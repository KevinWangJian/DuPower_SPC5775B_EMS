
#include "DcmDspUds_Rdtc_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"


#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_ReportFailedDTC :
 *  This function is used to implement the  subfunctions 0x0B,0x0C,0x0D,0x0E(reportFirstTestFailedDTC, reportFirstConfirmedDTC, reportMostRecentTestFailedDTC,
 *  reportMostRecentConfirmedDTC).
 *  From this, function  Dem_GetDTCStatusAvailabilityMask is called to get  the status availability mask.
 *  Dem_GetDTCByOccurrenceTime is called to get the FirstTestFailedDTC(DTCRequest param set to DEM_FIRST_FAILED_DTC)/
 *  FirstConfirmedDTC(DTCRequest param set to DEM_FIRST_DET_CONFIRMED_DTC)/MostRecentTestFailedDTC(DEM_MOST_RECENT_FAILED_DTC)/
 *  MostRecentConfirmedDTC(DEM_MOST_REC_DET_CONFIRMED_DTC).Then Dem_GetStatusOfDTC is called to get the status of the DTC
 *  which received by calling the Dem_GetDTCByOccurrenceTime.
 *
 *
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFailedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                      AUTOMATIC)    dataDTC_u32;            /* Variable to store DTC */
    VAR(Dem_ReturnGetDTCByOccurrenceTimeType,AUTOMATIC)    dataRetGetDTCByOccurTime_u8;    /* Return type of Dem_GetDTCByOccurrenceTime */
    VAR(Dem_ReturnGetStatusOfDTCType,AUTOMATIC)    dataRetGetStatusOfDTC_u8;    /* Return type of Dem_GetStatusOfDTC */
    VAR(uint8,AUTOMATIC)                           stDTCStatus_u8;        /* Variable to store the DTC status */
    VAR(uint8,                       AUTOMATIC)    dataStatusAvailMask_u8;  /* Variable to store status availability mask */
    VAR(uint8,AUTOMATIC)                           dataRDTCSubFunc_u8;        /* Local variable to store the subfunction */
    VAR(Std_ReturnType,AUTOMATIC)                  dataRetVal_u8;        /* Local variable to store the service return value */
    VAR(boolean,          AUTOMATIC) flgSubFnSupp_b;

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* Initialization of  variables */
    *dataNegRespCode_u8      =0x00;
    dataDTC_u32 = 0x00;
    /*Initialize flag flgSubFnSupp_b to TRUE */
    flgSubFnSupp_b = TRUE;
    dataRetGetDTCByOccurTime_u8 = DEM_OCCURR_FAILED;
    /* Copy the subfunction parameter to local variable */
    dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
    dataRetVal_u8=DCM_E_PENDING;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* check for request length */
    if(pMsgContext->reqDataLen == DSP_RDTC_B_C_D_E_REQLEN)
    {
        /* Request for status avilabilty mask */
        if(Dem_GetDTCStatusAvailabilityMask(&dataStatusAvailMask_u8) == E_OK)
        {
            /* Update the subfunction in the response buffer */
            pMsgContext->resData[0]=pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];
            /* Update the response length */
            pMsgContext->resDataLen=1;
            if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_TEST_FAILED_DTC)
            {
                /*call Dem_GetDTCByOccurrenceTime to get the  first failed DTC*/
                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_FIRST_FAILED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_FIRST_CONFIRMED_DTC)
            {
                /*call Dem_GetDTCByOccurrenceTime to get the  first confirmed DTC*/
                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_FIRST_DET_CONFIRMED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_TEST_FAILED_DTC)
            {
                /*call Dem_GetDTCByOccurrenceTime to get the most recent failed DTC*/
                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_MOST_RECENT_FAILED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else if(dataRDTCSubFunc_u8 == DSP_REPORT_MOST_RECENT_CONFIRMED_DTC)
            {
                /*call Dem_GetDTCByOccurrenceTime to get the most recent confirmed DTC*/
                dataRetGetDTCByOccurTime_u8 = Dem_GetDTCByOccurrenceTime(DEM_MOST_REC_DET_CONFIRMED_DTC,DEM_DTC_KIND_ALL_DTCS,&dataDTC_u32);
            }
            else
            {
                /*Set the flag flgSubFnSupp_b to FALSE*/
                
                flgSubFnSupp_b = FALSE;
               /*Retun E_OK from the service*/
                dataRetVal_u8=E_OK;
            }
            /*Check if the flag flgSubFnSupp_b is set to TRUE*/
            if (flgSubFnSupp_b != FALSE)
            {
                if((DEM_OCCURR_OK == dataRetGetDTCByOccurTime_u8) && (*dataNegRespCode_u8 == 0x00))
                {
                    /*Received the DTC from Dem_GetDTCByOccurrenceTime correctly.Now request for the DTC's status */
                    dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(dataDTC_u32,DEM_DTC_KIND_ALL_DTCS,DEM_DTC_ORIGIN_PRIMARY_MEMORY,&stDTCStatus_u8);
                    if(DEM_STATUS_OK == dataRetGetStatusOfDTC_u8)
                    {
                        /*Fill the response, status availability mask,DTC and DTC status*/
                        pMsgContext->resData[1] = dataStatusAvailMask_u8;
                        pMsgContext->resData[2] = (uint8)(dataDTC_u32>>16u);
                        pMsgContext->resData[3] = (uint8)(dataDTC_u32>>8u);
                        pMsgContext->resData[4] = (uint8)(dataDTC_u32);
                        pMsgContext->resData[5] = stDTCStatus_u8;
                        /* Update the message table with response data length */
                        pMsgContext->resDataLen = 6;
                        /*Retun E_OK from the service*/
                        dataRetVal_u8=E_OK;
                    }
                    /* If the DTC sent by the tester is not correct */
                    else if(DEM_STATUS_FAILED==dataRetGetStatusOfDTC_u8)
                    {
                        /*When DEM_STATUS_FAILED Dcm should send an positive response with SID and subfunction alone*/
                        pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                        /* Update the Response data length information */
                        pMsgContext->resDataLen = 0x01;
                        /*Retun E_OK from the service*/
                         dataRetVal_u8=E_OK;
                    }
                    /* If the DTC sent by the tester is not correct */
                    else if((DEM_STATUS_WRONG_DTC == dataRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== dataRetGetStatusOfDTC_u8)||       \
                            (DEM_STATUS_WRONG_DTCKIND== dataRetGetStatusOfDTC_u8))
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        /*Retun E_NOT_OK from the service*/
                         dataRetVal_u8=E_NOT_OK;
                    }
                    /*If DEM returns any invalid value */
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        /*Retun E_NOT_OK from the service*/
                         dataRetVal_u8=E_NOT_OK;
                    }
                }
                /*There is no failed /confirmed DTC available after the last CDI request.So send positive response with only status availability mask.*/

                else if (DEM_OCCURR_FAILED == dataRetGetDTCByOccurTime_u8)
                {
                    pMsgContext->resData[1] = dataStatusAvailMask_u8;
                    pMsgContext->resDataLen = 2;
                    /*Retun E_OK from the service*/
                    dataRetVal_u8=E_OK;
                }
                else
                {
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    /*Retun E_NOT_OK from the service*/
                    dataRetVal_u8=E_NOT_OK;
                }
            }
        }
        else
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            /*Retun E_NOT_OK from the service*/
            dataRetVal_u8=E_NOT_OK;
        }
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        /*Retun E_NOT_OK from the service*/
        dataRetVal_u8=E_NOT_OK;
    }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
