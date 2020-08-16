

#include "DcmDspObd_Mode2_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode2_Priv.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/****************************************************************************************************
* Dcm_DcmObdMode02 :
The purpose of this service is to allow access to emission-related data values in a freeze frame.
The request message includes parameter identification (PID) value that indicates to the on-board system the specific
information requested.It's not necessarily to contain the same current data values as the required freeze frame data.
When the tester request for freeze frame data through mode 02. The ECU(s) shall respond to this message by
transmitting the requested data value stored by the system at the time of fault occurrence in error memory.
All data values returned for sensor readings shall be actual stored readings, not default or substitute values used
by the system be-cause of a fault with that sensor.
*
* \param           pMsgContext    Pointer to message structure
*
* \retval          None
* \seealso
*
**************************************************************************************************
*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DcmObdMode02 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrRespBuf_pu8;/* Pointer to Response buffer                                */
    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrReqBuf_pu8; /* Pointer to Request buffer                                 */
    VAR(uint32,        AUTOMATIC)   dataPIDBitMask_u32;    /* For supported PIDs,each PID is bit coded value of 4bytes  */
    VAR(uint32,        AUTOMATIC)   dataCalBitMask_u32;    /* Calculated Bit mask based on PID value                    */
    VAR(uint32,        AUTOMATIC)   nrDTC_u32;        /* DTC number for PID 02                                     */
    VAR(Dcm_MsgLenType,AUTOMATIC)   nrResDataLen_u32;    /* Response data length                                      */
    VAR(Dcm_MsgLenType,AUTOMATIC)   nrReqDataLen_u32;    /* Requested data length check                               */
    VAR(Dcm_MsgLenType,AUTOMATIC)   nrResMaxDataLen_u32; /* Maximum available response buffer                         */
    VAR(uint16,		   AUTOMATIC)   idxDataSource_u16;/* Index to the data element of a PID                      */
    VAR(uint8_least,   AUTOMATIC)   nrPIDChk_qu8;    /* Number of Pids in request format                          */
    VAR(uint8_least,   AUTOMATIC)   nrPIDValid_qu8;     /* Number of valid Pids in temp request buffer               */
    VAR(uint8_least,   AUTOMATIC)   idxPIDStart_qu8;    /* Start index in PID configuration                          */
    VAR(uint8_least,   AUTOMATIC)   idxPIDData_qu8;     /* Start of data index associated with each PID              */
    VAR(uint8,         AUTOMATIC)   nrMultiple_u8;     /* Number of special PIDS requested are multiples of 0x20    */
    VAR(uint8,         AUTOMATIC)   idxPID_u8;       /* Pid index in bit mask configuration list                  */
    VAR(uint8,         AUTOMATIC)   adrTmpBuf_au8[3];    /* Temporary buffer maximum of 3PIDs                         */
    VAR(uint8,         AUTOMATIC)   nrBufSize_u8;        /* Size of response buffer size                              */
    VAR(uint8,         AUTOMATIC)   nrPid_u8;    /* Number of PIDs needs to be searched in PID configuration  */
    VAR(Std_ReturnType,AUTOMATIC)   dataRetGet_u8;        /* Return type of API Dem_ReadDataOfOBDFreezeFrame           */
    VAR(Std_ReturnType,AUTOMATIC)   dataRetVal_u8;        /* Return type of API Dem_ReadDataOfOBDFreezeFrame           */
    VAR(boolean,       AUTOMATIC)   isPIDFound_b;      /* If PID is found to be configured  						*/
    VAR(boolean,       AUTOMATIC)   flgGetDTCNum_b;       /* if TRUE, call DEM API to get DTC,else don't call DEM API  */


    /* Initialization of local variables */
    *dataNegRespCode_u8    		 = 0x0u;
    nrDTC_u32     		 = 0x00;
    adrTmpBuf_au8[0] 		 = 0x00;                       /* To remove Misra warning */
    nrReqDataLen_u32       = (pMsgContext->reqDataLen);  /* Copy the requested data length into local variable */
    nrPIDValid_qu8        = 0x00;
    nrResDataLen_u32 		 = 0x00;
    nrMultiple_u8  		 = 0;
    /*Initialise flgGetDTCNum with True*/
    flgGetDTCNum_b          = TRUE;
    idxPIDStart_qu8       = 0x00;
    nrPid_u8       = 0x00;
    idxDataSource_u16 = 0x00;
    idxPIDData_qu8        = 0x00;
    /*Initialise PIDFound with false*/
    isPIDFound_b         = FALSE;
    dataRetVal_u8=E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* Check if requested data length is equal to 2 or 4 or 6*/
    if((nrReqDataLen_u32==0x02uL)||(nrReqDataLen_u32==0x04uL)||(nrReqDataLen_u32==0x06uL))
    {
        /* Pointer to request buffer */
        adrReqBuf_pu8 = pMsgContext->reqData;

        /* Check if it is pure multiple of 0x20 or pure non multiple of 0x20
        In mode $02, each PID number is associated with freeze frame number of 1byte */
        for(nrPIDChk_qu8=0;(nrPIDChk_qu8 < nrReqDataLen_u32);nrPIDChk_qu8 +=2u)
        {
            /* Check whether requested PIDs are availability PIDS 0x00,0x20,0x40,0x60,0x80,0xa0,0xc0,0xe0
            this check can be done by performing bitwise AND 00011111 with requested PID.
            In case of availability PID, pid number BIT 7(MSB),6,5 can be set to 1 and BIT 4,3,2,1,0(LSB)is set to 0
            always */
            if((adrReqBuf_pu8[nrPIDChk_qu8] & 0x1Fu)==0u)
            {
                /* In case of pure multiple of 0x20, the counter value = reqdatalen/2
                for eg: request 02 00 00 20 00 40 00, reqdatalen = 6 since all requested PIDs are special PIDs
                hence the counter is incremented 3times (counter == reqdatalen/2).
                In case all requested PIDs which reports freeze frame data is requested,then this counter is
                always zero */
                nrMultiple_u8++;
            }

            /* Check whether freeze frame number is always 00 for all requested PIDs*/
            if((adrReqBuf_pu8[nrPIDChk_qu8 + 1u]) == 0x00u)
            {
                /* Copy only PID to temporary buffer */
                adrTmpBuf_au8[nrPIDValid_qu8] = adrReqBuf_pu8[nrPIDChk_qu8];

                /* Increment the index of temporary buffer */
                nrPIDValid_qu8++;
            }

        }
        /* The request is mixed up with multiple and non multiple of 0x20
        if only availability PID is requested then the counter value == requested data length / 2
        if only PID which report freeze frame data value is requested then the counter value is equal to 0*/
        if((nrMultiple_u8 == 0u) || (nrMultiple_u8 == (uint8)(nrReqDataLen_u32 >> 1u) ))
        {
            /* Pointer to response data buffer */
            adrRespBuf_pu8 = pMsgContext->resData;

            /* Set Negative response code 0x12
            NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            /* Get the maximum response data length in response buffer */
            nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

            /* Check for only availability PIDS in requested format */
            /* Check for PIDs which are requested by tester and which has freeze frame number as 00 associated
            with each PID. nrPIDValid_qu8 has count of valid PIDS which has freeze frame number as 00 for each PID*/
            for(nrPIDChk_qu8=0;(nrPIDChk_qu8 < nrPIDValid_qu8);nrPIDChk_qu8++)
            {
                /* Index for Dcm_Dsp_Mode1Bitmask_acs is calculated based on PID number index number = PID number/0x20*/
                idxPID_u8 = (uint8)((adrTmpBuf_au8[nrPIDChk_qu8]) / DCM_OBDMODE02_SUPPPID);

                /* Based on PID number,access the PID mask value corresponding to index in Dcm_Dsp_Mode2Bitmask_acs*/
                dataPIDBitMask_u32 = Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].BitMask_u32;

                /* If only availability PID is requested then the counter value == requested data length/2
                if only PID which report freeze frame data value is requested then the counter value is equal to 0*/
                if(nrMultiple_u8 != 0)
                {
                	if(dataPIDBitMask_u32 > 0u)
					{
                		/* Check if the response buffer is sufficient to hold the PID, freeze frame and PID bit mask  */
                		if(nrResMaxDataLen_u32>=0x06uL)
                		{
							/* Copy PID to response buffer */
							adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
							nrResDataLen_u32++;
							/* Load the freeze frame number as 0x00 to next byte in response data buffer immediately after PID number */
							adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
							nrResDataLen_u32++;

							/* Copy bit mask to response buffer of service */
							adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 24u);
							nrResDataLen_u32++;
							adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 16u);
							nrResDataLen_u32++;
							adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(dataPIDBitMask_u32 >> 8u);
							nrResDataLen_u32++;
							adrRespBuf_pu8[nrResDataLen_u32] = (uint8) dataPIDBitMask_u32;
							nrResDataLen_u32++;

							/* Update the maximum response data length */
							nrResMaxDataLen_u32 = nrResMaxDataLen_u32 - 0x06uL;

							/* Send positive response code */
							*dataNegRespCode_u8 = 0x0u;
                		}
                		/* If response buffer is insufficient */
                		else
                		{
                			/* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW" to DET module if the DET module is enabled */
							DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

							/* Set Negative response code 0x12
							NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
							*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

							break;
                		}
                	}
                }
                /* If the requested PID is to obtain freeze frame data, Eg : PID 0x02,0x03 etc */
                else
                {
                    /* Calculate the Bit mask based on requested PID For eg: PID 01 is requested, this PID is within
                    the range 01 to 1f hence availability PID is PID 00 & its Bit mask is of 4bytes in which BIT 31
                    is mapped to PID 01.hence calculated bit mask 0x80000000 for PID 01*/
                	dataCalBitMask_u32 = ((uint32)1u << ((uint32)32u - ((adrTmpBuf_au8[nrPIDChk_qu8]) % 0x20)));

                    /* If the requested PID is supported */
					if((dataPIDBitMask_u32 & dataCalBitMask_u32)> 0uL)
					{
						/* If PID requested is $02 if DTC that caused the freeze frame is to be obtained */
					    /*Check whether flgGetDTCNum is True*/
						if((DCM_DSPMODE02_PID02 == adrTmpBuf_au8[nrPIDChk_qu8])||(flgGetDTCNum_b != FALSE))
						{

							/* If requested PID is 02, then below DEM API needs to be called to get
							the DTC number in case of other PID,the below DEM API needs to be executed only
							once in order to obtain DTC number for eg: Request 07 02 03 00 04 00 05 00,
							 for this request DEM API function can be
							called only once in order to obtain DTC number*/
						    /*Update flgGetDTCNum with False */
							flgGetDTCNum_b = FALSE;


							/* Call the DEM interface function to find whether there is DTC number stored
							in error memory for which freeze frame data is stored (either PID 02 is requested
							or not) */
							/*PID 02 is requested (read DTC which caused freeze frame to be stored),
							Dem_GetDTCOfOBDFreezeFrame( ) is called and the parameter passed is record
							number (its always 00)*/

							if(Dem_GetDTCOfOBDFreezeFrame(0x00, &nrDTC_u32) != E_OK)
							{
								nrDTC_u32 = 0x00;
							}
						}
						/* DEM API function has returned value E_OK or E_NOT_OK
						in case of PID 02 is supported then send positive response with DTC number in
						nrDTC_u32.in case of other PIDS, if DTC number is non zero then use DEM API to get
						freeze frame data else send no response for other PID (Since DTC number is zero which
						indicates no freeze frame data is available */

						/* Check whether special PID 02 which reports DTC number is requested */
						if(DCM_DSPMODE02_PID02 == adrTmpBuf_au8[nrPIDChk_qu8])
						{
							if(nrResMaxDataLen_u32 >= 0x04uL)
							{
								/* Copy the PID 02 number from temporary buffer into response buffer */
								adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
								nrResDataLen_u32++;

								/* Fill the freeze frame number as 0x00 */
								adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
								nrResDataLen_u32++;

								/* In case if Dem interface function Dem_GetDTCOfOBDFreezeFrame()
								returns E_OK then DTCnumber is available in parameter nrDTC_u32.
								nrDTC_u32    3 (MSB)       2       1       0(LSB)
											 ---         DTC high  DTC Low  ----
														  byte     byte

								byte 2 of nrDTC_u32 holds DTC high byte
								byte 1 of nrDTC_u32 holds DTC low byte */

								adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(nrDTC_u32 >> 16u);
								nrResDataLen_u32++;
								adrRespBuf_pu8[nrResDataLen_u32] = (uint8)(nrDTC_u32 >> 8u);
								nrResDataLen_u32++;

								/* Update the remaining maximum response data length of response buffer*/
								nrResMaxDataLen_u32 = nrResMaxDataLen_u32 - 0x04uL;

								/* Send positive response code */
								*dataNegRespCode_u8 = 0u;
							}
							else
							{
	                			/* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW" to DET module if the DET module is enabled */
								DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)

								/* Set Negative response code 0x12
								NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
								*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

								/* Break out of the for loop in case of buffer overflow */
								nrPIDValid_qu8 = nrPIDChk_qu8 ;
							}

						}
						else
						{
							/* Byte 2,1 gives the DTC number high byte & low byte */
							if((nrDTC_u32 & 0xFFFF00uL)> 0uL)
							{
								/* If the DTCNum is non zero then freeze frame data is stored in memory */

								/* If the requested PID value is other than PID 02 do the following
								get the maximum available response data length in response buffer */
								/*if the available response data length is greater than 255 then pass the
								bufsize as 255bytes to DEM function otherwise pass the remaining buffer
								size to bufsize */
								/* Get the start index from the bit mask array */
								idxPIDStart_qu8 = Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].StartIndex_u8;

								/* Set the flag to FALSE to indicate the PID has not been found */
								/*Update PIDFound with False*/
								isPIDFound_b = FALSE;
							    dataRetGet_u8   = E_OK;

								/* Get the number of PIDS(its number of iterations) for which below for loop has to be
								looped for. Eg: If in the range PID 01 to 1F, only 5 PIDs are supported and PID 01 is
								requested by tester then its sufficient to search PID 01 in the range pid 01 to 1F
								with only 5 iterations since only 5 PIDs are configured in that range*/
								for(nrPid_u8 = (uint8)idxPIDStart_qu8;((nrPid_u8 <(idxPIDStart_qu8 +(Dcm_Dsp_Mode2Bitmask_acs[idxPID_u8].NumPids_u8))) && (isPIDFound_b == FALSE));nrPid_u8++)
								{
									/* If the PID is configured */
									if( adrTmpBuf_au8[nrPIDChk_qu8] == (Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Id_u8))
									{
										/* Set the PIDFound to TRUE. This indicates PID is found in configuration structure and
										not required to continue executing the above for loop*/
										isPIDFound_b = TRUE;

										/* If response buffer is sufficient to hold the PID data, PID and freeze frame requested */
										if(nrResMaxDataLen_u32>=(uint32)(Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8+2))
										{
											/* Access data index of data structure Dcm_Dsp_Mode1DataPid_acs associated with each requested PID */
											idxPIDData_qu8 = Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].DataSourcePid_ArrayIndex_u16;

											/* Fill the number of bytes corresponding to length of the PID with fill bytes */
											for(idxDataSource_u16=(uint16)(nrResDataLen_u32+2uL);idxDataSource_u16<(nrResDataLen_u32+Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8+2u);idxDataSource_u16++)
											{
												adrRespBuf_pu8[idxDataSource_u16] = 0x00;
											}
											/* Loop through each of the data elements and call the configured function to read PID data */
											for(idxDataSource_u16= (uint16)idxPIDData_qu8;((idxDataSource_u16<(idxPIDData_qu8+Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Num_DataSourcePids_u8)) && (dataRetGet_u8==E_OK));idxDataSource_u16++)
											{
												/* Get the maximum length of the data element configured */
												nrBufSize_u8 = (uint8)Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8;

												/* call the API to get the data and pass the pointer to the buffer location */
												dataRetGet_u8 = Dem_ReadDataOfOBDFreezeFrame(adrTmpBuf_au8[nrPIDChk_qu8],(uint8)(idxDataSource_u16-idxPIDData_qu8),
																						  &adrRespBuf_pu8[nrResDataLen_u32 +Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Pos_data_u8+2u],
																						  &nrBufSize_u8);
												/* Check if API returns E_OK */
												if(dataRetGet_u8 == E_OK)
												{
													/* Check if length of data written is greater than the allowed length */
													if(nrBufSize_u8 >Dcm_Dsp_Mode2DataSourcePid_acs[idxDataSource_u16].Length_data_u8)
													{
														/* Set the return value to E_NOT_OK */
														dataRetGet_u8=E_NOT_OK;
													}
												}
											}

											if(dataRetGet_u8 == E_OK)
											{
												/* Copy the PID Number from temporary buffer to response buffer */
												adrRespBuf_pu8[nrResDataLen_u32] = adrTmpBuf_au8[nrPIDChk_qu8];
												nrResDataLen_u32++;

												/* Fill the freeze frame number as 0x00 */
												adrRespBuf_pu8[nrResDataLen_u32] = 0x00;
												nrResDataLen_u32++;

												/* Increment the index of response buffer by	PID number(1byte)+freeze frame number(1byte)+Bufsize_u8
												nrBufSize_u8 is length of data bytes updated into response buffer.This variable is passed as input
												parameter to DEM function with maximum available response buffer size & DEM function returns the
												exact data value filled in response buffer which is updated in nrBufSize_u8 only if the return value is E_OK */
												nrResDataLen_u32 = nrResDataLen_u32 + Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8;

												/* Update the maximum available response buffer size */
												nrResMaxDataLen_u32 =  nrResMaxDataLen_u32 - (2uL + (Dcm_MsgLenType)Dcm_Dsp_Mode2PidArray_acs[nrPid_u8].Pid_Size_u8);

												/* Send positive response code */
												*dataNegRespCode_u8 = 0u;
											}
											else
											{
												/* Report development error "E_NOT_OK" to DET module if the DET module is enabled */
												DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_RET_E_NOT_OK)
											}
										}
										else
										{
				                			/* Report development error "DCM_E_INTERFACE_BUFFER_OVERFLOW" to DET module if the DET module is enabled */
											DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
											/* Set Negative response code 0x12
											NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
												*dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

											/* Update the index to break out of the for loop */
											nrPIDValid_qu8 = nrPIDChk_qu8;

											break;
										}
									}
								} /* End of for loop */
							}
						}
					}
                }
            } /* End of for loop */

            /* Set the response length for requested PID */
            pMsgContext->resDataLen = nrResDataLen_u32;
        }
        else
        {
            /*Set Negative response code 0x12 for the combination of both supported PID
            and PID which report data value in single request format
            NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

            /* Report development error "MIXED MODE" to DET module if the DET module is enabled */
            DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_MIXED_MODE)
        }
    }
    else
    {
        /* Requested data length is not equal to 2 or 4 or 6 then Send Negative response code Request
        Length Invalid NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;

        /*report development error "Invalid length" to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_OBDMODE02_ID, DCM_E_INVALID_LENGTH)
    }

    /* If negative response code is set */
    if(*dataNegRespCode_u8 != 0x0u)
    {
        /* Call function to set Negative response code */
        dataRetVal_u8=E_NOT_OK;

    }
    else{
        dataRetVal_u8=E_OK;
    }

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif


