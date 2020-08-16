
#include "DcmDspObd_Mode8_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE8_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode8_Priv.h"
#include "rba_BswSrv.h"



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/****************************************************************************************************
* Dcm_DcmObdMode08 :
*The purpose of this service is to enable the external test equipment to control the operation
*of an on-board system, test or component.By this service $08, following operations can be done,
*when the tester sends corresponding single test id in request format
*1) Turn on-board system/test/component ON
*2) Turn on-board system/test/component OFF
*3) Cycle on-board system/test/component for 'n' seconds.
*This service $08 can also provide supported Test Ids information in ECU,
*when the tester requests with supported Tids in request format
*
* \param           pMsgContext    Pointer to message structure
*
* \retval          None
* \seealso
*
**************************************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode08 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8; /* Pointer to Response buffer                               */
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8;  /* Pointer to Request buffer                                */
    VAR(uint32,         AUTOMATIC) dataTidMaskVal_u32;      /* For supported TIDs,each TID is bit coded value of 4bytes */
    VAR(uint32,         AUTOMATIC) dataCalTidBitMask_u32;   /* Calculated Bit mask based on TID value                   */
    VAR(Dcm_MsgLenType, AUTOMATIC) nrReqDataLen_u32;      /* Requested data length check                              */
    VAR(uint16_least,   AUTOMATIC) idxTidRes_qu16;     /* Index to response buffer for valid TIDs                  */
    VAR(uint8_least,    AUTOMATIC) nrTid_qu8;      /* Number of TIDs needs to be searched in TID configuration */
    VAR(uint8_least,    AUTOMATIC) idxTidStart_qu8;      /* Start index in TID configuration                         */
    VAR(uint8_least,    AUTOMATIC) nrNumTids_qu8;          /* Number of TIDs in configuration structure                */
    VAR(uint8_least,    AUTOMATIC) nrTidChk_qu8;      /* Number of requested Tids that is to be searched in config structure */
    VAR(uint8,          AUTOMATIC) adrTmpBuf_au8[DCM_OBDMODE08_REQ_LEN_MAX]; /* Temp buffer maximum of 6 TIDs         */
    VAR(uint8,          AUTOMATIC) idxTID_u8;         /* Tid index in bitmask configuration list                  */
    VAR(uint8,          AUTOMATIC) nrMultiple_u8;       /* Number of special TIDS requested are multiples of 0x20   */
    VAR(Std_ReturnType, AUTOMATIC) stRetTID_u8;            /* Return type of TID which triggers turn ON/OFF of test    */
    VAR(boolean,        AUTOMATIC) stTIDFound_u8;       /* Set to 1 if requested TID is found in configuration      */
    VAR(Std_ReturnType, AUTOMATIC) dataRetval_u8;            /* Return type of TID which triggers turn ON/OFF of test    */

    /* Initialisation of local variables */
    *dataNegRespCode_u8   = 0x0u;
    idxTidRes_qu16 = 0;
    nrTid_qu8 = 0;
    idxTidStart_qu8 = 0;
    nrNumTids_qu8 = 0;
    dataCalTidBitMask_u32 = 0;                     /*to remove warning */
    adrTmpBuf_au8[0] = 0;                        /*to remove misra warning */
    /*Initialize TID to FALSE*/
    stTIDFound_u8 = FALSE;
    nrMultiple_u8 = 0;
    idxTID_u8 = 0;
    stRetTID_u8 = 0;
    dataRetval_u8=E_NOT_OK;

    nrReqDataLen_u32 = (pMsgContext->reqDataLen);   /* Copy the requested data length into local variable */

    adrReqBuf_pu8 = pMsgContext->reqData;            /* Pointer to request buffer */
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

    /* Check whether requested Tid is multiple of 0x20 */
    /* For eg: TID 0x20 --> 0010 0000 & 0001 1111 = 0000 0000 hence its supported TID in request format
              TID 0x01 --> 0000 0001 & 0001 1111 = 0000 0001 hence its TID to turn ON/OFF the test/system */
    if (((adrReqBuf_pu8[0] & 0x1Fu) != 0x00u) && (nrReqDataLen_u32 > DCM_OBDMODE08_REQ_LEN_MIN))
    {
        /* Calculate the TID  whether TID is supported or not */
        /* Set NRC to 0x12- NRC 0x12 is suppressed in DCM module for OBD service since it is functional addressing */
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        /* Index for Dcm_Dsp_Mode8Bitmask_acs is calculated based on TID number index number = TID number/0x20 */
        idxTID_u8 =(uint8) (adrReqBuf_pu8[0] / DCM_OBDMODE08_SUPPTID);
        /* Based on TID number,access the TID mask value corresponding to index in Dcm_Dsp_Mode8Bitmask_acs*/
        dataTidMaskVal_u32 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].BitMask_u32;
        /* Based on requested TID value, calculate the corresponding TID Bit mask for the range 01-1F,21-3F .
            For eg: TID 01 is requested then generate BIT mask as 80 00 00 00 since BIT 31 is mapped to TID 01 */
        dataCalTidBitMask_u32 = ((uint32)1u << ((uint32)32u - ((adrReqBuf_pu8[0]) % 0x20)));

        if((dataTidMaskVal_u32 & dataCalTidBitMask_u32) > 0u)
        {

            /* Requested TID is supported in ECU. Based on the index value in Dcm_Dsp_Mode8Bitmask_acs, get the
               starting index,number of TIDS to be searched in Dcm_Dsp_Mode8TidArray_acs( TID configurations) */
            idxTidStart_qu8 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].StartIndex_u8;
            nrNumTids_qu8 =  Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].NumTids_u8;
            /*Set TID to value FALSE*/
            stTIDFound_u8 = FALSE;
            /* Get the number of TIDS(its number of iterations) for which below for loop has to be looped for
               Eg: if in the range TID 01 to 1F, only 5TIDs are supported and TID 01 is requested by tester then
               its sufficient to search TID 01 in the range TID 01 to 1F with only 5 iterations since only 5 TIDs
               are configured in that range */
            for(nrTid_qu8 = idxTidStart_qu8;((nrTid_qu8 <(idxTidStart_qu8 + nrNumTids_qu8)) &&(stTIDFound_u8 == FALSE));nrTid_qu8++)
            {
            	/* If TID is found to be configured */
                if( adrReqBuf_pu8[0] == (Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].Tid_Id_u8))
                {
                    /* Set the TIDFound to 1, this indicates TID is found in configuration structure and not
                    required to continue executing the above for loop */
                    stTIDFound_u8 = TRUE;
                    /* Check if response buffer is sufficient to hold the data and the TID */
					if(pMsgContext->resMaxDataLen>(uint32)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].OutBuffer_u8))
					{
						/* Check whether the configured Inbuffer is equal to obtained requested data length
						  (ReqdataLen - 1 (TID Number)). For eg: 08 01 00 02 is requested by tester, configured Inbuffer is 2bytes
						   reqdatalen = 3 (Tid number + 2 data bytes) then this valid length check */
						if(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].InBuffer_u8 == (nrReqDataLen_u32 - 1u))
						{
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u )
						   /* Copy TID Data Record from Request into Buffer */
						    if(nrReqDataLen_u32 != 1u)
						    {
						      /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
						        DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]), &(adrReqBuf_pu8[1]) ,nrReqDataLen_u32 - 1u);
						    }
#endif
						    /* Calculate buffer index to be passed for the data */
							adrRespBuf_pu8 = pMsgContext->resData;
							/*Check whether Useport is Enabled Or Not*/
							if(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].UsePort_b != FALSE)
							{
                                /* Call back function which is configured for corresponding TID   pass the parameter
                                   InBuffer --> pointer to request Buffer,OutBuffer -->pointer to Response buffer in
                                   which data bytes can be filled, both Inbuffer & OutBuffer is passed with 1byte less
                                   as it contains 1byte TID number both in request & response buffer */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
							    if(nrReqDataLen_u32 != 1u)
							    {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u )
							        stRetTID_u8 = ((*(RequestControl1_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
                                                                  (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],&Dcm_InParameterBuf_au8[0]));
#endif
							    }
							    else
							    {
							        stRetTID_u8 = ((*(RequestControl1_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
							                                                                          (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],NULL_PTR));
							    }

							}
							else
							{
                                /* Call back function which is configured for corresponding TID   pass the parameter
                                   InBuffer --> pointer to request Buffer,OutBuffer -->pointer to Response buffer in
                                   which data bytes can be filled, both Inbuffer & OutBuffer is passed with 1byte less
                                   as it contains 1byte TID number both in request & response buffer */
								/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
							    if(nrReqDataLen_u32 != 1u)
							     {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u )
							         stRetTID_u8 = ((*(RequestControl2_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
							                                                                  (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],&Dcm_InParameterBuf_au8[0]));
#endif
							     }
							    else
							     {
							          stRetTID_u8 = ((*(RequestControl2_pf)(Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].adrRequestControl_cpv))
							                                                                                                 (&adrRespBuf_pu8[idxTidRes_qu16 + 1u],NULL_PTR));
							     }


							}
							if(stRetTID_u8==E_OK)
							{
									/* Copy the TID number into response buffer and increment the response buffer
									index by 1*/
									adrRespBuf_pu8[idxTidRes_qu16] = adrReqBuf_pu8[0];
									idxTidRes_qu16++;

									/* In case of other TIDs, response length = TID number + data length configured in
									   OutBuffer_u8 in Dcm_Dsp_Mode8TidArray_acs*/
									idxTidRes_qu16 = (idxTidRes_qu16 +
													 (Dcm_Dsp_Mode8TidArray_acs[nrTid_qu8].OutBuffer_u8));

									/* Set the response length for requested TID */
									pMsgContext->resDataLen = idxTidRes_qu16;

									/* Send positive response code */
									*dataNegRespCode_u8   = 0x0u;
							}
							else
							{
								/* Set Negative response code NRC 0x22 */
								*dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
							}
						}
						else
						{
							/* Requested data length should be TID number + InBuffer size configured then Send Negative
							response code Request Length Invalid NRC 0x12 is suppressed in DCM module for OBD service
							since its functional addressing*/
							*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

							/* Report development error "INVALID LENGTH" to DET module if the DET module is enabled */
							DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_INVALID_LENGTH)
						}
					}
					else
					{
						/* Set NRC to 0x12 - SubfunctionNotSupported */
						*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
						/* Report development error "Buffer overflow" to DET module if the DET module is enabled */
						DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
					}
				}
            }
        }
    }
    else
    {
        /* Length check for supported TIDS - Check if the request Data Length is greater than 0 and less than 7*/
        if((nrReqDataLen_u32 > DCM_OBDMODE08_REQ_LEN_MIN) && (nrReqDataLen_u32 < DCM_OBDMODE08_REQ_LEN_MAX))
        {
            /* Check if it is pure multiple of 0x20 or pure non multiple of 0x20 */
            for(nrTidChk_qu8=0;(nrTidChk_qu8 < nrReqDataLen_u32);nrTidChk_qu8++)
            {
                /* Check the multiple of 0x20 */
                if((adrReqBuf_pu8[nrTidChk_qu8] & 0x1Fu)==0u)
                {
                    /* It is pure multiple of 0x20 */
                    nrMultiple_u8++;
                }
                /* Copy TID to temporary buffer */
                adrTmpBuf_au8[nrTidChk_qu8] = adrReqBuf_pu8[nrTidChk_qu8];
            }
            /* If the all requested TIDs are supported TID then the ctMultiple shall be equal to nrReqDataLen_u32 */
            if (nrMultiple_u8 == nrReqDataLen_u32)
            {
                /* Set NRC 0x12- NRC 0x12 is suppressed in DCM  for OBD service since it is functional addressing */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                /* Calculate buffer index to be passed for the data */
                adrRespBuf_pu8 = pMsgContext->resData;
                /* Check for TIDs which are requested by tester */
                for(nrTidChk_qu8=0;(nrTidChk_qu8 < nrReqDataLen_u32);nrTidChk_qu8++)
                {
                    /* Index to Dcm_Dsp_Mode8Bitmask_acs is calculated using TID number-> indexnumber=TID number/0x20*/
                    idxTID_u8 = (uint8)((adrTmpBuf_au8[nrTidChk_qu8]) / DCM_OBDMODE08_SUPPTID);
                    /* Based on TID number,access the TID mask value corresponding to index in Dcm_Dsp_Mode8Bitmask_acs*/
                    dataTidMaskVal_u32 = Dcm_Dsp_Mode8Bitmask_acs[idxTID_u8].BitMask_u32;
                    /* Copy the TID number and TIDMask value only if accessed TIDMask value is not 00 00 00 00*/
                    if(dataTidMaskVal_u32 > 0u)
                    {
                    	if((pMsgContext->resMaxDataLen - idxTidRes_qu16) > 0x4u)
                    	{
							/* Copy TID to response buffer */
							adrRespBuf_pu8[idxTidRes_qu16] = adrTmpBuf_au8[nrTidChk_qu8];
							idxTidRes_qu16++;
							/* Increment the response buffer index by 1 since TID number is already filled */
							/* Copy bit mask to message buffer of service */
							adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 24u);
							idxTidRes_qu16++;
							adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 16u);
							idxTidRes_qu16++;
							adrRespBuf_pu8[idxTidRes_qu16] = (uint8)(dataTidMaskVal_u32 >> 8u);
							idxTidRes_qu16++;
							adrRespBuf_pu8[idxTidRes_qu16] = (uint8) dataTidMaskVal_u32;
							idxTidRes_qu16++;
							/* Send positive response code */
							*dataNegRespCode_u8   = 0x0;
                    	}
                    	else
                    	{
    						/* Report development error "Buffer overflow" to DET module if the DET module is enabled */
    						DCM_DET_ERROR(DCM_OBDMODE09_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
							/* Update index to request data length to exit out of the for loop */
							break;
                    	}
                    }
                }
                /* Set the response length for requested TID */
                /* In case of availability of TID, response length = Tid number + 4 data bytes for each requested TID  */
                pMsgContext->resDataLen = idxTidRes_qu16;
            }
            else
            {
                /* Set Negative response code 0x12 for the combination of both supported TID
                and TID which report data value in single request format
                NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                /* Report development error "MIXED MODE" to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_MIXED_MODE)
            }
        }
        else
        {
            /* In case of supported TIDS, the requested data length is invalid then set Negative response code - NRC 0x12
               NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            /* Report development error "INVALID LENGTH" to DET module if the DET module is enabled */
            DCM_DET_ERROR(DCM_OBDMODE08_ID, DCM_E_INVALID_LENGTH)
        }
    }
    /* If negative response code is set */
    if(*dataNegRespCode_u8 != 0x0u)
    {
        /* Call function to set Negative response code */
        dataRetval_u8=E_NOT_OK;
    }
    else{
        /* Call function to set Negative response code */
        dataRetval_u8=E_OK;
    }

    return dataRetval_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif


