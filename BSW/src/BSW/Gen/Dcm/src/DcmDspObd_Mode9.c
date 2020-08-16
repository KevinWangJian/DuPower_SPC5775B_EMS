

#include "DcmDspObd_Mode9_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

#include "DcmDspObd_Mode9_Priv.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint8, DCM_VAR) Dcm_dataDspInfoType_u8; /* INFOTYPE which report data value */

static VAR(uint8, DCM_VAR) Dcm_idxDspInfoType_u8; /* Index of the INFOTYPE which report data value */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint16, DCM_VAR) Dcm_idxDspVehData_u16;/* Index to iterate through VehDataInfo for a VehInfo */
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,DCM_VAR) Dcm_stOpStatus_u8; /* Variable to store OpStatus passed to API reading Veh Info data */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspMode09Type_ten,DCM_VAR) Dcm_stDspMode09_en; /* Variable to store the state of Mode9 service */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DcmObdMode09_Ini : Initialisation function for Mode 09 Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DcmObdMode09_Ini(void)
{
    /* Set Mode 09 state machine to DCM_DSP_MODE09_INIT */
    if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
    {
        Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
#if (DCM_CFG_DSP_OBDMODE9_DEM_SUPP != DCM_CFG_OFF)
        /* If the Veh Info data API last accessed is a DEM API */
        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_DEM_FNC)
        {
            Dem_DcmCancelOperation();
        }
#endif
        /* If the Veh Info data API last accessed is a RTE API */
        if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
        {
            /* Fill the parameters DataValueBuffer and DataalueBuffersize pass NULL_PTR as the API is invoked to cancel the operation */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            (void)((*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(DCM_CANCEL,NULL_PTR,NULL_PTR));

        }
    }
    Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
    Dcm_stOpStatus_u8 = DCM_INITIAL;

}

/****************************************************************************************************
 * Dcm_DcmObdMode09 :
 * The purpose of this service is to read vehicle-specific information such as VIN, calibration IDs etc.
 * Some of this information may be required by regulations and some may be desired to be reported in a
 * standard format if supported by the vehicle manufacturer.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode09 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8; /* Pointer to Response buffer */
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8; /* Pointer to Request buffer */
    VAR(uint8,AUTOMATIC) DataValueBufferSize_u8; /* Pointer to DataValueBufferSize - Used by GetInfoType API*/
    VAR(uint32, AUTOMATIC) dataInfoTypeMaskVal_u32; /* Bit mask value for supported INFOTYPEs */
    VAR(uint32, AUTOMATIC) dataCalInfotypeBitMask_u32; /* Calculated Bit mask based on INFOTYPE value */
    VAR(Dcm_MsgLenType, AUTOMATIC) nrReqDataLen_u32; /* Requested data length check */
    VAR(uint16_least, AUTOMATIC) idxInfotypeResBuf_qu16; /* Index to response buffer for valid INFOTYPEs */
    VAR(uint8_least, AUTOMATIC) idxinfoTypeStart_qu8; /* Start index in INFOTYPE configuration */
    VAR(uint8_least, AUTOMATIC) nrInfoTypeMaxLoop_qu8; /* No of iteration to search INFOTYPE in configuration */
    VAR(uint8_least, AUTOMATIC) nrInfoTypeChk_qu8; /* Number of INFOTYPEs in the request */
    VAR(uint8_least, AUTOMATIC) nrInfotype_qu8; /* Number of INFOTYPEs to be searched in INFOTYPE configuration*/
    VAR(uint8, AUTOMATIC) adrTmpBuf_au8[DCM_OBDMODE09_REQ_LEN_MAX]; /* Temporary buffer maximum of 6 INFOTYPEs */
    VAR(uint8, AUTOMATIC) idxInfoType_u8; /* INFOTYPE index in bit mask configuration list */
    VAR(uint8, AUTOMATIC) nrMultiple_u8; /* Number of special INFOTYPES requested */
    VAR(Std_ReturnType, AUTOMATIC) dataInfotypeFnResult_u8; /* Return value of get infotype function  */
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;

    /* Initialization of local variables */
    *dataNegRespCode_u8 = 0x0u;
    idxInfotypeResBuf_qu16 = 0x0u;
    nrInfotype_qu8 = 0x0u;
    idxinfoTypeStart_qu8 = 0x0u;
    dataCalInfotypeBitMask_u32 = 0x0u; /* To remove warning */
    adrTmpBuf_au8[0] = 0x0u; /* To remove Misra warning */
    nrMultiple_u8 = 0x0u;
    nrReqDataLen_u32 = (pMsgContext->reqDataLen); /* copy the requested data length into local variable */
    dataInfotypeFnResult_u8 = E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    if (OpStatus == DCM_CANCEL)
    {
        Dcm_DcmObdMode09_Ini();
        dataRetVal_u8 = E_OK;
    }

    else
    {
        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_INIT)
        {
            /* Check if the request Data Length is greater than 0 and less than 7 */
            if((nrReqDataLen_u32 > DCM_OBDMODE09_REQ_LEN_MIN) && (nrReqDataLen_u32 < DCM_OBDMODE09_REQ_LEN_MAX))
            {
                /* Pointer to request buffer */
                adrReqBuf_pu8 = pMsgContext->reqData;

                /* Check if it is multiple of 0x20 or non multiple of 0x20 Infotypes */
                for(nrInfoTypeChk_qu8 = 0; (nrInfoTypeChk_qu8 < nrReqDataLen_u32); nrInfoTypeChk_qu8++)
                {
                    /* Check the multiple of 0x20 */
                    if((adrReqBuf_pu8[nrInfoTypeChk_qu8] & 0x1Fu)==0u)
                    {
                        /* It is pure multiple of 0x20 */
                        nrMultiple_u8++;
                    }

                    /* Copy INFOTYPE to temporary buffer */
                    adrTmpBuf_au8[nrInfoTypeChk_qu8] = adrReqBuf_pu8[nrInfoTypeChk_qu8];
                }

                /* The request may have INFOTYPE mix of multiple and non multiple of 0x20 */
                /* If only availability INFOTYPE is requested then the counter value = requested data length */
                /* If only INFOTYPE which report data value is requested then the counter value = 0 */
                if((nrMultiple_u8 == 0) || (nrMultiple_u8 == nrReqDataLen_u32))
                {
                    /* Calculate buffer index to be passed for the data */
                    adrRespBuf_pu8 = pMsgContext->resData;

                    /* Set Negative response code 0x12 */
                    /* NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing */
                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                    /* Processes availability INFOTYPEs */
                    if(nrMultiple_u8 != 0)
                    {
                        /* Check for INFOTYPEs which are requested by tester */
                        for(nrInfoTypeChk_qu8 = 0;(nrInfoTypeChk_qu8 < nrReqDataLen_u32);nrInfoTypeChk_qu8++)
                        {
                            /* Index for Dcm_Dsp_Mode9Bitmask_acs is calculated based on INFOTYPE number */
                            /* Index = INFOTYPE number/0x20 */
                            idxInfoType_u8 = (uint8)((adrTmpBuf_au8[nrInfoTypeChk_qu8]) / DCM_OBDMODE09_SUPPINFOTYPE);

                            /* Access the INFOTYPE mask value corresponding to index in Dcm_Dsp_Mode9Bitmask_acs */
                            dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].BitMask_u32;

                            /* Each supported INFOTYPE provides bit coded value for the range of INFOTYPEs
                             which are supported */
                            /* For eg: INFOTYPE 00 provides bit coded value for the range of INFOTYPE $01 to $20 */
                            /* For each supported INFOTYPE, 4bytes (32 INFOTYPES) are allocated in response format */

                            /* Copy the INFOTYPE number and INFOTYPEMask value only if the accessed INFOTYPEMask
                             value is not equal to 00 00 00 00*/
                            if(dataInfoTypeMaskVal_u32 > 0u)
                            {
                                /* Check if response is sufficient to hold the data and info type */
                                if((pMsgContext->resMaxDataLen - idxInfotypeResBuf_qu16) > 0x4u)
                                {
                                    /* Copy INFOTYPE to response buffer */
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = adrTmpBuf_au8[nrInfoTypeChk_qu8];
                                    idxInfotypeResBuf_qu16++;

                                    /* For supported INFOTYPE, 4bytes are allocated in response format */
                                    /* Copy bit mask to message buffer */
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 24u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 16u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8)(dataInfoTypeMaskVal_u32 >> 8u);
                                    idxInfotypeResBuf_qu16++;
                                    adrRespBuf_pu8[idxInfotypeResBuf_qu16] = (uint8) dataInfoTypeMaskVal_u32;
                                    idxInfotypeResBuf_qu16++;

                                    /* Send positive response code */
                                    *dataNegRespCode_u8 = 0x0u;
                                }
                                else
                                {
                                    /* Report development error "Buffer overflow" to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                                    /* Set Negative response code 0x12 */
                                    /* NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing */
                                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                                    /* Update index to request data length to exit out of the for loop */
                                    break;
                                }
                            }
                        }
                        /* Response length = INFOTYPE number + 4 data bytes for each requested INFOTYPE  */
                        pMsgContext->resDataLen = idxInfotypeResBuf_qu16;
                    }
                    else
                    {
                        /* Requests for INFOTYPEs which request data value should contain only one INFOTYPE */
                        /* Else NRC 0x12 will be sent */
                        if(nrReqDataLen_u32 == DCM_OBDMODE09_REQ_LEN)
                        {
                            /* INFOTYPE which report data value */
                            Dcm_dataDspInfoType_u8 = adrTmpBuf_au8[0];

                            /* Index for INFOTYPE which report data value */
                            /* Calculated based on INFOTYPE number. index number = INFOTYPE number/0x20 */
                            idxInfoType_u8 = (uint8)(Dcm_dataDspInfoType_u8 / DCM_OBDMODE09_SUPPINFOTYPE);

                            /* Access the INFOTYPE mask corresponding to INFOTYPE index in Dcm_Dsp_Mode9Bitmask_acs */
                            dataInfoTypeMaskVal_u32 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].BitMask_u32;

                            /* Based on requested INFOTYPE value, calculate the corresponding INFOTYPE Bit mask */
                            /* eg:for INFOTYPE 01 BIT mask will be 80 00 00 00, as BIT 31 is mapped to INFOTYPE 01 */
                            dataCalInfotypeBitMask_u32 = ((uint32)1u << ((uint32)32u - ((Dcm_dataDspInfoType_u8) % 0x20)));

                            /* If required bit in the BIT mask is set */
                            if((dataInfoTypeMaskVal_u32 & dataCalInfotypeBitMask_u32) > 0u)
                            {
                                /* Requested INFOTYPE is supported in ECU. */
                                /* Get starting index of the INFOTYPE to be searched in Dcm_Dsp_VehInfoArray_acs*/
                                idxinfoTypeStart_qu8 = Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].StartIndex_u8;

                                /* Get the number of INFOTYPES for which below loop has to be executed */
                                /* eg:if only 5INFOTYPEs are supported in the range 01 to 1F, and if INFOTYPE 01 is */
                                /* requested by tester then its sufficient to search INFOTYPE 01 in the range 01-1F */
                                /* with only 5 iterations since only 5 INFOTYPEs are configured in that range */
                                nrInfoTypeMaxLoop_qu8 = idxinfoTypeStart_qu8 +
                                (Dcm_Dsp_Mode9Bitmask_acs[idxInfoType_u8].NumInfotypes_u8);
                                for(nrInfotype_qu8 = idxinfoTypeStart_qu8;
                                        nrInfotype_qu8 < nrInfoTypeMaxLoop_qu8;
                                        nrInfotype_qu8++)
                                {
                                    /* If requested VehInfoType is found to be configured */
                                    if(Dcm_dataDspInfoType_u8 == (Dcm_Dsp_VehInfoArray_acs[nrInfotype_qu8].Infotype_u8))
                                    {
                                        /* Store the index of the requested INFOTYPE */
                                        Dcm_idxDspInfoType_u8 = (uint8)nrInfotype_qu8;

                                        /* Update the state machine to call software component API */
                                        Dcm_stDspMode09_en = DCM_DSP_MODE09_RUNNING;

                                        /* Get the starting index of the VehInfoData in Dcm_Dsp_VehInfoData_acs array */
                                        Dcm_idxDspVehData_u16 =Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16;

                                        /* Copy INFOTYPE to response buffer */
                                        pMsgContext->resData[0]=Dcm_dataDspInfoType_u8;
                                        /*Check Whether number of dataitems is configured as False*/
                                        if(Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].Is_NODI_Enabled_b!= TRUE)
                                        {
                                            /* Store the number of Data elements  corresponding to the VehInfotype in the response buffer */
                                            pMsgContext->resData[1]=(Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8);
                                            /* Update the response length by 2 bytes*/
                                            pMsgContext->resDataLen = 2;
                                        }
                                        else
                                        {
                                            pMsgContext->resDataLen = 1;
                                        }
                                        Dcm_stOpStatus_u8 = DCM_INITIAL;
                                        /* Send positive response code */
                                        *dataNegRespCode_u8 = 0x0u;
                                        /* INFOTYPE found Stop the search */
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            /* Invalid Request Length send NRC 0x12 */
                            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
                        }
                    }
                }
                else
                {
                    /* Set Negative response code 0x12 for the combination of both supported and Non supported */
                    /* INFOTYPEs in single request */
                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_MIXED_MODE)
                }
            }
            else
            {
                /* Invalid Request Length send NRC 0x12 */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INVALID_LENGTH)
            }
        }

        /* If the state is DCM_DSP_MODE09_RUNNING - Info type is found  */
        if(Dcm_stDspMode09_en == DCM_DSP_MODE09_RUNNING)
        {

            /* Loop through the data elements and read the data corresponding to the VehInfoType by calling the configured API */
            do
            {
                /* Check if response is sufficient to hold the data and info type */
                if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen)>=(uint32)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].Infodatatype_size_u8))
                {
                    /* If the function pointer is not a NULL_PTR */
                    if((Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf)!=NULL_PTR)
                    {
                        /* Update the parameter DataValueBufferSize with the Avaialble Buffer size with the Dcm */
                        /* The Parameter DatavalueBufferSize is a uint8 value - so if the buffer exceeds 255u then the maximum uint8 value is assigned to it */
                        if((pMsgContext->resMaxDataLen - pMsgContext->resDataLen) >= (uint32)255u)
                        {
                            DataValueBufferSize_u8 = (uint8)255u;
                        }
                        else
                        {
                            DataValueBufferSize_u8 = (uint8)(pMsgContext->resMaxDataLen - pMsgContext->resDataLen);
                        }

                            /* Call the function to get the vehinfo data */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataInfotypeFnResult_u8 = (*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(Dcm_stOpStatus_u8,&pMsgContext->resData[pMsgContext->resDataLen],&DataValueBufferSize_u8);

                        /* Data available from the software component */
                        if( dataInfotypeFnResult_u8 == E_OK)
                        {
                            /* Update the result data length with the DataBufferSize returned by the API GetInfoTypeValueData */
                            pMsgContext->resDataLen += (uint32)DataValueBufferSize_u8;
                            /* Increment the index to the VehInfo data array */
                            Dcm_idxDspVehData_u16++;
                            Dcm_stOpStatus_u8 = DCM_INITIAL;
                        }
                        else if(dataInfotypeFnResult_u8 == DCM_E_PENDING)
                        {
                            /* WaitPend response  is not allowed for InfoType 0x02,0x04,0x08,0x0A,0x0B */
                            if((Dcm_dataDspInfoType_u8 ==0x02)||(Dcm_dataDspInfoType_u8 ==0x04)||(Dcm_dataDspInfoType_u8 ==0x08)||(Dcm_dataDspInfoType_u8 ==0x0A)||(Dcm_dataDspInfoType_u8 ==0x0B))
                            {
    #if (DCM_CFG_DSP_OBDMODE9_DEM_SUPP != DCM_CFG_OFF)
                                if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_DEM_FNC)
                                {
                                    Dem_DcmCancelOperation();
                                }
    #endif
                                if(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].InfoType_APIType_e == OBD_MODE9_RTE_FNC)
                                {
                                    /* Pass the parameters DataValueBuffer and DataalueBuffersize as NULL_PTR , as the API is invoked to cancel the operation */
                                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                    (void)(*(GetInfotypeValueData_pf1)(Dcm_Dsp_VehInfoData_acs[Dcm_idxDspVehData_u16].GetInfotypeValueData_pf))(DCM_CANCEL,NULL_PTR,NULL_PTR);
                                }
                                /* NRC 0x12 is suppressed in DCM module */
                                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                                /* Error code for DCM_E_PENDING */
                                DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_PENDING)
                                /* Set OpStatus to DCM_INITIAL */
                                Dcm_stOpStatus_u8 = DCM_INITIAL;
                            }
                            else
                            {
                                /* Set OpStatus to DCM_PENDING */
                                dataRetVal_u8=DCM_E_PENDING;
                                Dcm_stOpStatus_u8 = DCM_PENDING;

                            }
                        }
                        else
                        {
                            /* NRC 0x12 is suppressed in DCM module */
                            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                            /* Set OpStatus to DCM_INITIAL */
                            Dcm_stOpStatus_u8 = DCM_INITIAL;
                            /* Error code for E_NOT_OK */
                            DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_RET_E_NOT_OK)
                        }
                    }
                }
                else
                {
                    /* NRC 0x12 is suppressed in DCM module */
                    *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                    /* Set return type to E_NOT_OK to break out of the do-while loop */
                    dataInfotypeFnResult_u8 = E_NOT_OK;
                    /* Report development error "Invalid length" to DET module if the DET module is enabled */
                    DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                }
            }
            while ( (Dcm_idxDspVehData_u16< (Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].InfoDatatypeIndex_u16+Dcm_Dsp_VehInfoArray_acs[Dcm_idxDspInfoType_u8].NumOfInfoData_u8)) && (dataInfotypeFnResult_u8==E_OK));

            /* If all the API for reading VehInfo data returns E_OK */
            if(dataInfotypeFnResult_u8 == E_OK)
            {
                /* Set the state to DCM_DSP_MODE09_INIT */
                Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
                dataRetVal_u8=E_OK;
            }
            /* Update the response length */
        }

        /* If negative response code is set */
        if(*dataNegRespCode_u8 != 0x0u)
        {
            dataRetVal_u8=E_NOT_OK;
            Dcm_stDspMode09_en = DCM_DSP_MODE09_INIT;
        }
    }
    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
