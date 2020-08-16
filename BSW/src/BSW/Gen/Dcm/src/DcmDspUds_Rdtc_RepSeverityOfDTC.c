

#include "DcmDspUds_Rdtc_Inf.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_ReportSeverityInfoOfDTC :
 * This function is used to read the Severity and Functional unit information of DTC.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSeverityOfDTC(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,AUTOMATIC)          dataDTC_u32;                 /* Local variable for getting DTC from request*/
    VAR(uint8,AUTOMATIC)           dataHighByte_u8;             /* Local variable to copy byte 1 of request */
    VAR(uint8,AUTOMATIC)           dataMiddleByte_u8;           /* Local variable to copy byte 2 of request */
    VAR(uint8,AUTOMATIC)           dataLowByte_u8;              /* Local variable to copy byte 3 of request */
    VAR( uint8,AUTOMATIC)		   stDTCStatus_u8;        /* Variable to store the DTC status */
	VAR(uint8,AUTOMATIC)           dataFunctionalUnit_u8;       /* Local variable to store functional unit information */
    VAR(Dem_ReturnGetStatusOfDTCType,AUTOMATIC)    dataRetGetStatusOfDTC_u8;    /* Return type of Dem_GetStatusOfDTC */
    VAR(Dem_ReturnGetSeverityOfDTCType,AUTOMATIC)  dataRetGetSeverityOfDTC_u8;  /*Return type of Dem_GetSeverityOfDTC */
	VAR(Dem_ReturnGetFunctionalUnitOfDTCType,AUTOMATIC) dataRetGetFuncUnitOfDTC_u8;
	/*Return type of Dem_GetFunctionalUnitOfDTC */
    VAR(Dem_DTCSeverityType, AUTOMATIC) dataDTCSeverity_u8; /*Variable to get the severity of DTC */
    VAR(uint8,AUTOMATIC)  dataRDTC0x09StMask_u8;         /* variable to calculate available status mask */
    VAR(Std_ReturnType,                      AUTOMATIC) dataretVal_u8;                  /* Variable to store the returnType from DcmAppl API          */
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* Initialization of variables */
    *dataNegRespCode_u8 = 0x00;
    dataretVal_u8=DCM_E_PENDING;
    /* Check for the correct request length */
    if(pMsgContext->reqDataLen == DSP_RDTC_09_REQUEST_LENGTH)
    {
        /* copy the 3 byte DTC into Dsp_RdtcDTC_u32 from request*/
        dataHighByte_u8     =   pMsgContext->reqData[0x01];
        dataMiddleByte_u8   =   pMsgContext->reqData[0x02];
        dataLowByte_u8      =   pMsgContext->reqData[0x03];
        dataDTC_u32         =   dataHighByte_u8;
        dataDTC_u32         =   (dataDTC_u32 << 0x8u);
        dataDTC_u32         =   (dataDTC_u32 | dataMiddleByte_u8);
        dataDTC_u32         =   (dataDTC_u32 << 0x8u);
        dataDTC_u32         =   (dataDTC_u32 | dataLowByte_u8);

        /* Get the DTC Status Availability Mask */
        if(Dem_GetDTCStatusAvailabilityMask(&dataRDTC0x09StMask_u8) == E_OK)
        {
            /* Call DEM API to get the status of DTC sent from tester */
            dataRetGetStatusOfDTC_u8 = Dem_GetStatusOfDTC(dataDTC_u32,
                                                    DEM_DTC_KIND_ALL_DTCS,
                                                    DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                                    &stDTCStatus_u8
                                                  );

            /* If the available status mask is read successfully */
            if(dataRetGetStatusOfDTC_u8 == DEM_STATUS_OK)
            {
                /* Get the Severity of the DTC */
                dataRetGetSeverityOfDTC_u8 = Dem_GetSeverityOfDTC(dataDTC_u32,&dataDTCSeverity_u8);
                /* If the Severity of DTC was read without any errors OR */
                /* If the severity information is not available for this DTC */
                if((dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_OK)||
                   (dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_NOSEVERITY))
                {
					dataRetGetFuncUnitOfDTC_u8 = Dem_GetFunctionalUnitOfDTC(dataDTC_u32,&dataFunctionalUnit_u8);
					if(dataRetGetFuncUnitOfDTC_u8 == DEM_GET_SEVERITYOFDTC_OK)
					{
						/* Fill the response buffer */
						pMsgContext->resData[0x00] = pMsgContext->reqData[0x0]; /* Sub function */
						pMsgContext->resData[0x01] = dataRDTC0x09StMask_u8;      /* Availability Mask */

						/* If the return type is DEM_GET_SEVERITYOFDTC_NOSEVERITY then severity information is filled as 0x00*/
						if(dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_NOSEVERITY)
						{
							dataDTCSeverity_u8 = 0x00;
						}
						pMsgContext->resData[0x02] = dataDTCSeverity_u8;   /* DTC Severity */
						pMsgContext->resData[0x03] = dataFunctionalUnit_u8; /* Functional Unit */
						pMsgContext->resData[0x04] = dataHighByte_u8;            /* DTC High Byte */
						pMsgContext->resData[0x05] = dataMiddleByte_u8;          /* DTC Middle Byte */
						pMsgContext->resData[0x06] = dataLowByte_u8;             /* DTC Low Byte */
						pMsgContext->resData[0x07] = stDTCStatus_u8;  /* DTC Status */
						pMsgContext->resDataLen    = 0x08;
                        dataretVal_u8=E_OK;
					}
					else
					{
						*dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        dataretVal_u8=E_NOT_OK;
					}
                }
                else if(dataRetGetSeverityOfDTC_u8 == DEM_GET_SEVERITYOFDTC_WRONG_DTC)
                {
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataretVal_u8=E_NOT_OK;
                }
                else
                {
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    dataretVal_u8=E_NOT_OK;
                }
            }
            /* If the DTC sent by the tester is not correct */
            else if(DEM_STATUS_FAILED==dataRetGetStatusOfDTC_u8)
            {
                /*When DEM_STATUS_FAILED Dcm should send an positive response with SID and subfunction alone*/
                pMsgContext->resData[0x00] = pMsgContext->reqData[0x00];
                /* Update the Response data length information */
                pMsgContext->resDataLen = 0x01;
                dataretVal_u8=E_OK;
            }
            /* If the DTC sent by the tester is not correct */
            else if((DEM_STATUS_WRONG_DTC == dataRetGetStatusOfDTC_u8)||(DEM_STATUS_WRONG_DTCORIGIN== dataRetGetStatusOfDTC_u8)||       \
                    (DEM_STATUS_WRONG_DTCKIND== dataRetGetStatusOfDTC_u8))
            {
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                dataretVal_u8=E_NOT_OK;
            }
            /*If DEM returns any invalid value */
            else
            {
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                dataretVal_u8=E_NOT_OK;
            }
        }
        /* If the available status mask is not correct */
        else
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            dataretVal_u8=E_NOT_OK;
        }
    }
    else
    {
        /* Request Length not correct */
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        dataretVal_u8=E_NOT_OK;
    }
    return dataretVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

