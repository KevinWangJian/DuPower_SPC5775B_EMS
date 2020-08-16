

#include "DcmDspObd_Mode6_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE6_ENABLED != DCM_CFG_OFF)


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DcmObdMode06 :
 *  Purpose of this service is to read the stored OBDMID data (test results) from ECU.
 *  Request information includes OBDMID value based on that ECU has to send response for different TIDs
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */


FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode06(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /********************************/
    /* Definition of local variables */
    /********************************/

    VAR(Dcm_MsgType,				 AUTOMATIC) adrResData_pu8;            /* Local pointer to response buffer 			*/
    VAR(Dcm_MsgType,				 AUTOMATIC) adrReqData_pu8;            /* Local pointer to request buffer 			    */
    VAR(Dcm_MsgLenType,				 AUTOMATIC) nrResDataLen_u32;         /* Local variable for response length		    */
    VAR(Dcm_MsgLenType,				 AUTOMATIC) nrReqDataLen_u32;         /* Local variable for request length		    */
    VAR(uint32,						 AUTOMATIC) dataBitMask_u32;        /* Local variable to calculate bit mask			*/
    VAR(uint16_least,				 AUTOMATIC) idxTid_qu32;       /* Local traverse over TID array 				*/
    VAR(uint16,						 AUTOMATIC) idxTidarrayLimit_u16; /* Local variable traverse over TID array 		*/
    VAR(uint16,						 AUTOMATIC) dataTestVal_u16;       /* OUT parameter of API to read test data 		*/
    VAR(uint16,						 AUTOMATIC) dataMinLimit_u16;      /* OUT parameters of API to read test data 		*/
    VAR(uint16,					     AUTOMATIC) dataMaxLimit_u16;      /* OUT parameters of API to read test data 		*/
    VAR(uint8_least,				 AUTOMATIC) idxReq_qu32;       /* Local traverse over request stream 			*/
    VAR(uint8_least,				 AUTOMATIC) idxObdMid_qu32;    /* Local traverse over MID array 				*/
    VAR(uint8,				         AUTOMATIC) stStatus_u8;             /* OUT parameters of API to read test data 		*/
    VAR(Std_ReturnType,              AUTOMATIC) dataReturnValue_u8;       /* Local to hold return value of RTE function   */
    VAR(uint8,                       AUTOMATIC) adrTempBuffer_au8[8];     /* Temporary buffer to hold request				*/
    VAR(uint8,						 AUTOMATIC) nrRange_u8;           /* Local to hold range of requested MID         */
    VAR(uint8,						 AUTOMATIC) dataMidArrayLimit_u8;  /* Local variable traverse over MID array 		*/
    VAR(boolean,					 AUTOMATIC) flgSplObdMid_b;       /* Local variable handle data or special OBDMID */


    /************************************/
    /* Initialization of local variables */
    /************************************/

    adrResData_pu8       = pMsgContext->resData;
    adrReqData_pu8       = pMsgContext->reqData;
    nrReqDataLen_u32    = pMsgContext->reqDataLen;
    *dataNegRespCode_u8     = 0;
    dataReturnValue_u8=E_NOT_OK;
    nrResDataLen_u32    = 0;
    /* To avoid MISRA 30 */
    /*Initialise Local variable handle data or special OBDMID with False*/
    flgSplObdMid_b =  FALSE;
    adrTempBuffer_au8[0] = 0;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /********************************/
    /* Validation of request stream */
    /********************************/
    if((adrReqData_pu8[0] & 0x1fu) != 0x00u)
    {
        if(nrReqDataLen_u32 == 0x01u)
        {
            /* This is proper request for data OBDMID */
            /*Update Local variable handle data or special OBDMID with False*/
            flgSplObdMid_b = FALSE;
            adrTempBuffer_au8[0] = adrReqData_pu8[0];
        }
        else
        {
            /* Suppress the response and log the error in DET */
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INVALID_LENGTH)
        }
    }
    else if((nrReqDataLen_u32 != 0x00u)&&(nrReqDataLen_u32 < 0x07u))
    {
        /* This is Special OBDMID */
        /*Update Local variable handle data or special OBDMID with True*/
        flgSplObdMid_b = TRUE;
        /* Traverse through the request */
        for(idxObdMid_qu32=0; idxObdMid_qu32<nrReqDataLen_u32; idxObdMid_qu32++)
        {
            /* Check this request has only OBDMIDs which is divisible by 0x20 */
            if((adrReqData_pu8[idxObdMid_qu32] & 0x1fu)== 0x00u)
            {
                /* Copy into temporary buffer */
                adrTempBuffer_au8[idxObdMid_qu32] = adrReqData_pu8[idxObdMid_qu32];
            }
            else
            {
                /* Suppress the response and log the error in DET (request has both data and special OBDMIDs)*/
                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_MIXED_MODE)
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                break;
            }
        }
    }
    else
    {
        /* Suppress the response and log the error in DET (wrong length) */
        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INVALID_LENGTH)
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
    /********************************/
    /* Process the request          */
    /********************************/
    if(*dataNegRespCode_u8 == 0)
    {
        /*Update Local variable handle data or special OBDMID with False*/
        if(flgSplObdMid_b == FALSE)
        {
            /****************************************/
            /*     Handling of data OBDMID          */
            /****************************************/
            nrRange_u8 = (uint8)(adrTempBuffer_au8[0]/0x20);
            /* Check requested data OBDMID is configured or not? */
            if(((Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].BitMask_u32) & (0x80000000uL>>((adrTempBuffer_au8[0]%0x20)- 1u))) != 0x00u)
            {
                /* Search MIDs of this range */
                dataMidArrayLimit_u8 = Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8 +
                                                  Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].NumMids_u8;
                /* Search the requested OBDMID in MID array in proper range */
                for(idxObdMid_qu32= Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8;
                    idxObdMid_qu32 < dataMidArrayLimit_u8;
                    idxObdMid_qu32++)
                {
                    /* Check configured OBDMID is requested one? */
                    if(adrTempBuffer_au8[0] == Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8)
                    {
                        /* Calculate how many TIDs to be look for this OBDMID */
                        idxTidarrayLimit_u16 = (uint16)(Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Num_Tids_u8 +
                                                        Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16);

                        /* Traverse through TIDs of this OBDMID */
                        for(idxTid_qu32 = Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16;
                            idxTid_qu32 < idxTidarrayLimit_u16;
                            idxTid_qu32++)
                        {
                            /*Check whether Useport is Disabled*/
                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE)
                        	{
								/* Call DcmAppl function of this TID */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        		dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16,
                                                                                                					 &dataMinLimit_u16,
                                                                                                					 &dataMaxLimit_u16,
                                                                                                					 &stStatus_u8);
                        	}
                        	else
                        	{
                        		/* Call RTE function of this TID */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL,
                                																					 &dataTestVal_u16,
                                																					 &dataMinLimit_u16,
                                																					 &dataMaxLimit_u16,
                                																					 &stStatus_u8);
                        	}
                            if(dataReturnValue_u8 == E_OK)
                            {
                                /* Status is DCM_DTRSTATUS_VISIBLE means,this TID is supported */
                                if(stStatus_u8 == DCM_DTRSTATUS_VISIBLE)
                                {
                                	if((nrResDataLen_u32+9u)<=pMsgContext->resMaxDataLen)
                                	{
										/* Fill the response in buffer and increment the response length */
										adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[0];
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = Dcm_Dsp_TidArray_acs[idxTid_qu32].Tid_Id_u8;
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = Dcm_Dsp_TidArray_acs[idxTid_qu32].UnitScale_u8;
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16>>8u);
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataTestVal_u16);
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16>>8u);
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMinLimit_u16);
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16>>8u);
										nrResDataLen_u32++;
										adrResData_pu8[nrResDataLen_u32] = (uint8)(dataMaxLimit_u16);
										nrResDataLen_u32++;
                                	}
                                	else
                                	{
                                    	/* Report development error "Invalid length" to DET module if the DET module is enabled */
                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
                						/* Set Negative response code 0x12 */
                						/* NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing */
										*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                                        /* To break out of the for loop */
                                        dataMidArrayLimit_u8 = (uint8)idxObdMid_qu32;
                                        break;
                                	}
                                }
                                else
                                {
                                    if(stStatus_u8 != DCM_DTRSTATUS_INVISIBLE)
                                    {
                                        /* Wrong status value from RTE. Log the error. Go to next TID */
                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_WRONG_STATUSVALUE)
                                    }
                                }
                            }
                            else
                            {
                                /* Wrong status value from RTE. Log the error. Go to next TID */
                                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                            }
                        }
                        /* Requested MID is found no need to go for next MID */
                        break;
                    }
                }
            }
            else
            {
                /* Ignore the request, because this data OBDMID is not configured */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }
        }
        else
        {
            /****************************************/
            /*     Handling of special OBDMID          */
            /****************************************/

            /* Calculate the bit mask of all requested special OBDMIDs */
            for(idxReq_qu32=0;idxReq_qu32<nrReqDataLen_u32;idxReq_qu32++)
            {
                nrRange_u8 = (uint8)(adrTempBuffer_au8[idxReq_qu32]/0x20);

                /* Check at least one OBDMID is configured in this range or next range */
                if(Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].BitMask_u32 != 0x00uL)
                {
                    /* Reset or initialize the bit mask */
                    dataBitMask_u32 = 0x0;

                    /* Go to each MIDs of this range and next range to calculate the bit mask*/
                    /* Skip if one of MID found supported in next range */
                    for(idxObdMid_qu32=Dcm_Dsp_Mode6Bitmask_acs[nrRange_u8].StartIndex_u8;
                        ((idxObdMid_qu32 < DCM_CFG_DSP_OBDMIDARRAYSIZE) && ((dataBitMask_u32 & 0x01u) != 0x01u));
                        idxObdMid_qu32++)
                    {

                        /* Calculate how many TIDs to be look for this OBDMID */
                        idxTidarrayLimit_u16 = (uint16)(Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Num_Tids_u8 +
                                                    Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16);

                        /* Go to TIDs of this OBDMID */
                        for(idxTid_qu32 = Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Tid_ArrayIndex_u16;
                            idxTid_qu32 < idxTidarrayLimit_u16;
                            idxTid_qu32++)
                        {
                           /*Check whether Useport is Disabled*/
                        	if(Dcm_Dsp_TidArray_acs[idxTid_qu32].Is_UsePort_Enabled_b==FALSE)
                        	{
								/* Call DcmAppl function of this TID */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        		dataReturnValue_u8 = (*(GetDTRvalue_pf2)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(&dataTestVal_u16,
                                                                                                					 &dataMinLimit_u16,
                                                                                                					 &dataMaxLimit_u16,
                                                                                                					 &stStatus_u8);
                        	}
                        	else
                        	{
                        		/* Call RTE function of this TID */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataReturnValue_u8 = (*(GetDTRvalue_pf1)Dcm_Dsp_TidArray_acs[idxTid_qu32].GetDTRvalue_pf)(DCM_INITIAL,
                                																					 &dataTestVal_u16,
                                																					 &dataMinLimit_u16,
                                																					 &dataMaxLimit_u16,
                                																					 &stStatus_u8);
                        	}
                            if(dataReturnValue_u8 == E_OK)
                            {
                                /* Status is DCM_DTRSTATUS_VISIBLE means,this OBDMID is supported */
                                if(stStatus_u8 == DCM_DTRSTATUS_VISIBLE)
                                {
                                    /* Check this OBDMID belongs to this range or not */
                                    if(nrRange_u8 == (Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8/0x20))
                                    {
                                        /* Set the bit for this OBDMID */
                                        dataBitMask_u32 = dataBitMask_u32|(0x80000000u>>
                                            ((((Dcm_Dsp_ObdMidArray_acs[idxObdMid_qu32].Mid_Id_u8)%0x20) - 1)));
                                    }
                                    else
                                    {
                                        /* This OBDMID belongs to next range. hence set the LSB */
                                        dataBitMask_u32 = dataBitMask_u32|0x01uL;
                                    }
                                    /* No need to check the next TID of this OBDMID. come out of TID array */
                                    break;
                                }
                                else
                                {
                                    if(stStatus_u8 != DCM_DTRSTATUS_INVISIBLE)
                                    {
                                        /* Wrong status value from RTE. Log the error. Go to next TID */
                                        DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_WRONG_STATUSVALUE)
                                    }
                                }
                            }
                            else
                            {
                                /* Wrong status value from RTE. Log the error. Go to next TID */
                                DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_RET_E_NOT_OK)
                            }

                                /* Wrong return value from RTE. Log the error. Go to next TID */
                        }
                    }
                    /* Fill the response in buffer, if at least one OBDMID supported */
                    if(dataBitMask_u32 != 0x0uL)
                    {
                    	if((nrResDataLen_u32+5uL)<=pMsgContext->resMaxDataLen)
                    	{
							adrResData_pu8[nrResDataLen_u32] = adrTempBuffer_au8[idxReq_qu32];
							nrResDataLen_u32++;
							adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>24u);
							nrResDataLen_u32++;
							adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>16u);
							nrResDataLen_u32++;
							adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32>>8u);
							nrResDataLen_u32++;
							adrResData_pu8[nrResDataLen_u32] = (uint8)(dataBitMask_u32);
							nrResDataLen_u32++;
                    	}
                    	else
                    	{
                        	/* Report development error "Invalid length" to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_OBDMODE06_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

    						/* Set Negative response code 0x12 */
    						/* NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing */
							*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

                            /* To break out of the for loop */
                            dataBitMask_u32=0x01;

                            /* To break out of the for loop */
                            nrReqDataLen_u32 = idxReq_qu32;
                            break;
                    	}
                    }
                }
            }
        }
        if(nrResDataLen_u32 != 0x0uL)
        {
            /* Copy the local variable into global variable */
            pMsgContext->resDataLen = nrResDataLen_u32;
        }
        else
        {
            /* After the processing, still response length is zero means no need to send positive response */
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }

    }
    /* Is there any failure occurred? */
    if(*dataNegRespCode_u8 != 0)
    {
        dataReturnValue_u8=E_NOT_OK;
    }
    else{
        dataReturnValue_u8=E_OK;
    }

    return dataReturnValue_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

