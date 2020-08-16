

#include "DcmDspUds_Uds_Inf.h"


#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (uint32, DCM_VAR) s_datasignallength_u32; /* Local variable to store the length for a particular signal*/
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspDataOpstatus_u8;  /* Variable to store the opstatus*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (uint16       ,DCM_VAR)         Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)	|| \
(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) 	|| \
(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

static VAR (Std_ReturnType, DCM_VAR) s_dataRetVal_u8;       /* Variable to store the return type of the function */
#endif
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

static VAR (Std_ReturnType, DCM_VAR) s_dataLengthFnc_retVal_u8; /* Local variable to store return value */
#endif
VAR (boolean,DCM_VAR) Dcm_PeriodicSchedulerRunning_b;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (boolean   ,DCM_VAR) Dcm_flgDspDidRangePending_b;
/* Flag for Asynchronous server point handling ,to indicate invocation of Rte_Call API */
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
    static VAR (boolean ,DCM_VAR) s_DcmReadDataLengthRteCallPlaced_b;
    static VAR (boolean ,DCM_VAR) s_DcmReadDataConditionsRteCallPlaced_b;
    static VAR (boolean ,DCM_VAR) s_DcmReadDataRteCallPlaced_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if ((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))

#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
/**
 ****************************************************************************************************************************
 * Dcm_ResetAsynchFlags:
 *
 * Reset all the Flags for Asynchronous server call point handling
 * This API is invoked by Rdbi_Ini to reset Flags in case of Protocol Preemption
 *
 * \param     void
 * \retval    void
 * \seealso
 *
 ****************************************************************************************************************************
 */
FUNC (void,DCM_CODE) Dcm_ResetAsynchFlags(void)
{
     /* Reset all the Flags defined for Asynchronous handling to FALSE*/
     s_DcmReadDataLengthRteCallPlaced_b = FALSE;
     s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
     s_DcmReadDataRteCallPlaced_b = FALSE;
}
#endif

/**
 ****************************************************************************************************************************
 * Dcm_ConvBitsToBytes:
 *
 * The dataLenInBits is converted into its byte equivalent
 *
 * \param   - InOut:  DataLenInBits
 * \retval    void
 * \seealso
 *
 ****************************************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ConvBitsToBytes(P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)DataLenInBits)
{
    VAR(uint32,AUTOMATIC) dataLen_u32;
    /* Conversion of Bits to Bytes */
    dataLen_u32 = (uint32)(*DataLenInBits/8u);
    if((*DataLenInBits%8u) != 0u)
    {   /* Move to the next applicable Byte */
        *DataLenInBits = (uint16)(dataLen_u32+1u);
    }
    else
    {
        *DataLenInBits = dataLen_u32;
    }
}

/**
 ****************************************************************************************************************************
 * Dcm_ResetDIDIndexstruct:
 *
 * Reset all the elements of Dcm_DIDIndexType_tst to its default value
 *
 * \param     idxDidIndexType_st    :   index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on the dataRange_b parameter
 * \retval    void
 * \seealso
 *
 ****************************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_ResetDIDIndexstruct (P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st)
{
    idxDidIndexType_st->dataNegRespCode_u8=0x0;         /*Reset the NRC to zero*/
    /*Reset the data range to false*/
    idxDidIndexType_st->dataRange_b = FALSE;
    idxDidIndexType_st->idxIndex_u16 = 0x0;             /*Reset the index of DID to 0x0*/
    idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;   /*Reset the number of signals read to zero*/
    idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0; /*Reset the signals length information to zero*/
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    /*Reset the DID flag to FALSE indicating normal DID*/
    idxDidIndexType_st->flagPageddid_b = FALSE;
#endif
#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
    idxDidIndexType_st->dataRangeDid_16= 0x00u;
#endif
    /*Reset the flag to FALSE*/
    idxDidIndexType_st->flgNvmReadPending_b = FALSE;
}


/**
 ****************************************************************************************************************************
 * Dcm_GetLengthOfDIDIndex:
 *
 * Calculate the length of the ID at position index in Dcm_DIDConfig
 *
 * \param     idxDidIndexType_st    :   index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on the dataRange_b parameter
 *            *length               :   length calculated in case E_OK is returned
 *            did                   :   DID in the request
 * \retval     E_OK: calculation finished successfully
 *             E_NOT_OK: error in configuration or in the called length calculating function
 * \seealso    Dcm_GetLengthOfDID_u8
 *
 **************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetLengthOfDIDIndex (VAR   (Dcm_DIDIndexType_tst ,AUTOMATIC)     idxDidIndexType_st,
                                                        P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)    length,
                                                        VAR   (uint16,AUTOMATIC) did)
{
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8; /* Local variable to store return value */
    VAR (uint32, AUTOMATIC) dataSigLength_u32; /* Local variable to store the adrTotalLength_pu16 */
    VAR (uint16, AUTOMATIC) dataSigLength_u16; /* Local variable to store the adrTotalLength_pu16 */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;

#if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
    VAR (uint16, AUTOMATIC) idxSig_u16; /* Local variable to store the adrTotalLength_pu16 */
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
#endif

#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
    P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrDIDRangeConfig;
#endif

    /* Initializations */
    dataRetVal_u8 = E_NOT_OK;
    *length = 0x0u;
    dataSigLength_u32 = 0x0u;
    dataSigLength_u16 = 0x0u;
    if(length!= NULL_PTR)
    {
        /*Check if data range is set to FALSE*/
        if(idxDidIndexType_st.dataRange_b == FALSE)
        {
    #if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
            /**Typecasted to void to avoid any compilation warnings issues*/
            (void)did;
            (void)dataSigLength_u32;
            (void)dataSigLength_u16;
            ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16];
            /* DID has signals of fixed length TYPE? */

            if(ptrDidConfig->dataFixedLength_b != FALSE)
            {    /* Return the maximum data length from configuration structure */
                *length = ptrDidConfig->dataMaxDidLen_u16;
                dataRetVal_u8 = E_OK;
            }
            else
            {
                /*The below portion of code is enabled only when atleast one variable length signal exists in RDBI or IOCBI
                 * DID*/
    #if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
                for(idxSig_u16=0;idxSig_u16<ptrDidConfig->nrSig_u16;idxSig_u16++)
                {
                    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
                    /* Check for USE FUNC and valid Read Data length function configuration */
                    if(((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)           ||
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)          ||
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)      ||
    #endif
                        (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)     ||
                        (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)) &&
                        (ptrControlSigConfig->adrReadDataLengthFnc_pfct != NULL_PTR))

                    {
                        ptrDIDFnc=ptrControlSigConfig->adrReadDataLengthFnc_pfct;
                        /*Check if the DID is a dynamically defined or not, if it is a dynamically defined DID one typecast it to ReadDataLengthFnc2_pf
                         * whose datalength parameter is of uint32 type where as if it is a normal one typecast it to ReadDataLengthFnc1_pf whose datalength
                         * parameter is of 2bytes*/

                        if(FALSE==Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].dataDynamicDid_b)
                        {
                            /* Get the length from the configured API */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
    #endif
                                    )
                            {
    #if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                                /* Check whether Asynchronous server call point handling is requested for this DID */
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                {
                                    if(!s_DcmReadDataLengthRteCallPlaced_b)
                                    {
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataRetVal_u8 = (*(ReaddatalengthFnc5_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))();
                                        if(dataRetVal_u8 == E_OK)
                                        {
                                            /* the Rte_Result API will be invoked in the next raster */
                                            s_DcmReadDataLengthRteCallPlaced_b = TRUE;
                                            dataRetVal_u8 = DCM_E_PENDING;
                                        }
                                        /* Dummy else to remove Misra Warnings */
                                        /* The calling API will set the NRC in this case */
                                        else
                                        {

                                        }
                                    }
                                    else
                                    {
                                        /* Invoke the Rte_Result API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFncResults_pfct))(&dataSigLength_u16);
                                        if (dataRetVal_u8 == E_OK)
                                        {
                                            s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                        }
                                        else if(dataRetVal_u8 == RTE_E_NO_DATA)
                                        {
                                            /* The Rte_Result API will be invoked again in hte next raster to get the result */
                                            dataRetVal_u8 = DCM_E_PENDING;
                                        }
                                        else
                                        {
                                            /* Reset the Flag to FALSE */
                                            s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                        }
                                    }
                                }
                                else
    #endif
                                {
                                    dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrDIDFnc))(idxDidIndexType_st.dataopstatus_b, &dataSigLength_u16);
                                }
                            }
                            else
							{
								if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                            	{
                            		dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrDIDFnc))(&dataSigLength_u16);
                            	}
							}
                            dataSigLength_u32 = (uint32)dataSigLength_u16;
                        }
                        else
                        {
                            /* Get the length from the configured API */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetVal_u8 = (*(ReadDataLengthFnc2_pf)(ptrDIDFnc))(&dataSigLength_u32);
                        }

                        if(dataRetVal_u8==E_OK)
                        {
                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
    #endif
                                    )
                            {
                                idxDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                            }
                            /* If the length received in more than the configured maximum length for a length  then return error */
                            /* IF RTE interface AR3.2.1 or AR3.1.4 is used the read data length function returns length in bytes, where as for AR4.X interface it is in bits*/
                            /*If Dynamically Defined DID is set to value FALSE*/
                            if((((dataSigLength_u32*8u) > ptrSigConfig->dataSize_u16) ||(dataSigLength_u32==0u)) &&    \
                                    (ptrDidConfig->dataDynamicDid_b == FALSE))

                            {
                                dataRetVal_u8 = E_NOT_OK;
                                break;
                            }
                            else
                            {
                                /*If Dynamically Defined DID value is set to FALSE*/
                                if(FALSE==ptrDidConfig->dataDynamicDid_b)
                                {

                                    /*Length returned is in bytes */
                                    *length+=dataSigLength_u32;


                                }
                                else
                                {
                                    *length+=dataSigLength_u32;
                                }
                            }
                        }
                        else if((dataRetVal_u8==DCM_E_PENDING) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
    #endif
                        ))
                        {
                            idxDidIndexType_st.dataopstatus_b = DCM_PENDING;
                            /*MR12 RULE 15.4 VIOLATION :More than one 'break' statement has been used to terminate this iteration statement. MISRA C:2012 Rule-15.4*/
                            break;
                        }
                        else
                        {
                        if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                                  || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
    #endif
                                    )
                            {
                                idxDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                            }
                            if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                            {
                                if(Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE)
                                {
                                    dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
                                }
                            }
                            /*Signal has returned E_NOT_OK, length is no more valid for the DID, don't proceed further for other signals*/
                            /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                            break;
                        }
                    }
                    else
                    {
                        if((ptrSigConfig->dataType_u8!=DCM_BOOLEAN))
                        {
                            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].idxDcmDspDatainfo_u16];
                            /*Check if the next signal is a fixedlength signal or not*/

                            if (ptrSigConfig->dataFixedLength_b == FALSE)
                            {
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                                dataSigLength_u32 = (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8)+(ptrSigConfig->dataSize_u16/8);
                            }
                            else
                            {
                                dataSigLength_u32 =0x00;
                            }
                        }
                        else
                        {
                            /* If the boolean signal is the last signal of the DID or the byte */
                            if((idxSig_u16==(ptrDidConfig->nrSig_u16-1))||                                          \
                                ((ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8) !=            \
                                 (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].posnSigBit_u16/8)))
                            {
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16+1].idxDcmDspDatainfo_u16];
                                /*Check if the next signal is a fixedlength signal or not*/
                                if (ptrSigConfig->dataFixedLength_b == FALSE)
                                {
                                    dataSigLength_u32 = (ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].posnSigBit_u16/8)+1;
                                }
                                else
                                {
                                    dataSigLength_u32 =0x00;
                                }
                                ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                            }
                        }
                        *length += dataSigLength_u32;
                        dataRetVal_u8 = E_OK;
                    }
                }
    #endif
            }
    #endif
        }
        else
        {
    #if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
            ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxDidIndexType_st.idxIndex_u16];
            /* Check for USE FUNC and valid Read Data length function configuration and length returned will be in bits*/
            if(ptrDIDRangeConfig->adrReadDataLengthFnc_pfct != NULL_PTR)
            {   /* Function  call to Get the length from the configured API */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                dataRetVal_u8 = (*(ReaddatalengthFnc3_pf)(ptrDIDRangeConfig->adrReadDataLengthFnc_pfct))(did,idxDidIndexType_st.dataopstatus_b,&dataSigLength_u16);
                if((dataSigLength_u16 > ptrDIDRangeConfig->dataMaxDidLen_u16)||(dataRetVal_u8==E_NOT_OK))
                {
                    dataRetVal_u8 = E_NOT_OK;
                    idxDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                }
                else if(dataRetVal_u8 == DCM_E_PENDING)
                {
                    idxDidIndexType_st.dataopstatus_b = DCM_PENDING;
                }
                else
                {
                    *length = (uint32)dataSigLength_u16;
                    idxDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                }
            }
    #endif
        }
    }
    else
    {
        /*return dataRetVal_u8 = NOT_OK */
    }
    return dataRetVal_u8;
}
#endif
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF )
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

/**
 ****************************************************************************************************************************
 * Dcm_GetDIDRangeStatus:
 *
 * Calculations to check if the DID is in the DID Range limits
 * @param[in]       did: The did for which the length is requested
 * @param[out]      idxDidIndexType_st : Index of the requested DID in Dcm_DIDRangeConfig structure if it is a range DID.
 *
 * @retval
 *             E_OK: DID range limit check done successfully
 *             E_NOT_OK: DID range limit check not done
 *
 ****************************************************************************************************************************
 */
FUNC (Std_ReturnType,DCM_CODE) Dcm_GetDIDRangeStatus (
                                        VAR (uint16,AUTOMATIC) did,
                                        P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
                                      )
{
    P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrDIDRangeConfig;
    VAR (Std_ReturnType, AUTOMATIC) dataDIDExists_u8;           /* to store return value from ISDIDAVAILABLE function pointer */
    VAR (uint16,AUTOMATIC) idxRange_u16;                            /*To store the index of requested DIDS*/
    VAR (Dcm_DidSupportedType, AUTOMATIC) isDIDAvailable_u8;                /*uint8 parameter which conveys whether the requested DID is available in DID Range*/
    VAR (boolean, AUTOMATIC) isInfrastructureErrorPresent_b = FALSE; /*paramter to check infrastructure error*/

    isDIDAvailable_u8 = DCM_DID_NOT_SUPPORTED;

    dataDIDExists_u8 = E_NOT_OK;
    if(idxDidIndexType_st != NULL_PTR)
    {
        /*Set the data range of Did value to FALSE*/
        idxDidIndexType_st->dataRange_b = FALSE;

        /*Loop through the complete list of available DID Ranges parameter to decide
         if the requested DID falls under any of the DIDRanges*/
        for(idxRange_u16=0;idxRange_u16<DCM_CFG_NUMOFDIDRANGES;idxRange_u16++)
        {
            ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxRange_u16];
            if((did >= ptrDIDRangeConfig->nrDidRangeLowerLimit_u16) && ( did <= ptrDIDRangeConfig->nrDidRangeUpperLimit_u16))
            {
                isDIDAvailable_u8 = DCM_DID_SUPPORTED;
                dataDIDExists_u8 = E_OK;
                /*Call to application to check if the DID is available in case of gaps*/

                if(FALSE != ptrDIDRangeConfig->dataRangeHasGaps_b )
                {
                    dataDIDExists_u8 = (*(ptrDIDRangeConfig->adrDIDAvailableFnc_pfct))(did,idxDidIndexType_st->dataopstatus_b,&isDIDAvailable_u8);

                    isInfrastructureErrorPresent_b = Dcm_IsInfrastructureErrorPresent_b(dataDIDExists_u8);
                    if((ptrDIDRangeConfig->nrRangeUsePort_b != FALSE) &&  (isInfrastructureErrorPresent_b != FALSE))
                    {
                        dataDIDExists_u8 = DCM_INFRASTRUCTURE_ERROR;
                    }
                }
                break;
            }
        }
        /*If the DID is available in any of the range write the index of the same and set isDIDAvailable_u8 parameter to one*/
        if((isDIDAvailable_u8 != DCM_DID_NOT_SUPPORTED) && (dataDIDExists_u8==E_OK))
        {
            /*update the variable and set the data range of Did to value TRUE*/
            idxDidIndexType_st->dataRange_b = TRUE;
            idxDidIndexType_st->idxIndex_u16 = idxRange_u16;
            idxDidIndexType_st->dataRangeDid_16 = did;
        }
    }
    else
    {
        /* return dataDIDExists_u8 = E_NOT_OK */
    }
    return(dataDIDExists_u8);
}
#endif
#endif

#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF )
/**
 *************************************************************************************************************************
 * Dcm_GetIndexOfDID:
 *
 * Dcm_GetIndexOfDID function is used to determine the index of did/range Did (which is an IN parameter), this function will write
 * the value of index of DID in  Dcm_DIDConfig structure array in case of normal DID /Dcm_DIDRangeConfig_cast structure array in case
 * of range DID on  to idxIndex_u16 which is an element in structure  idxDidIndexType_st(which is an out parameter).
 * The "dataRange_b" element of structure-idxDidIndexType_st is set to
 * FALSE in this function if DID is found in teh DCM_DIDConfig structure array.
 *
 * \param      did              : The did for which the length is requested
 *           idxDidIndexType_st : index in Dcm_DIDConfig or Dcm_DidRangeConfig structure based on the dataRange_b status
 *
 * \retval
 *                   E_OK: index successfully calculated
 *                   DCM_E_REQUEST_NOT_ACCEPTED: DID was not found
 * \seealso         Dcm_DspGetIndexOfDDDI_u8
 *
 *************************************************************************************************************************
 */
FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfDID (
                                                VAR (uint16,AUTOMATIC) did,
                                                P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
                                                  )
{
    VAR (uint32,         AUTOMATIC) posnDid_u32;
    VAR (uint32,         AUTOMATIC) posnStart_u32;
    VAR (uint32,         AUTOMATIC) posnEnd_u32;
    VAR (uint32,         AUTOMATIC) dataSize_u32;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;            /* read interface return value */
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;


#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
        /*Function call to check if the requested DID is available with in any of the Range parameters*/
        dataRetVal_u8 = Dcm_GetDIDRangeStatus(did, idxDidIndexType_st);
        if(dataRetVal_u8==E_OK)
        {
            /* Do nothing */
        }

        else if(dataRetVal_u8==DCM_E_PENDING)
        {
            /* Do nothing */
        }
        else
#endif
        {
            dataSize_u32 = Dcm_DIDcalculateTableSize_u16();
            posnStart_u32 = 0;
            posnEnd_u32 = dataSize_u32 -1u;
            posnDid_u32 = posnEnd_u32/2u;
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
            /* If First element is the matching local id */
            if (Dcm_DIDConfig[posnStart_u32].dataDid_u16 == did)
            {
                idxDidIndexType_st->idxIndex_u16 = (uint16)posnStart_u32;
                /*set the data range of Did value to FALSE and update info*/
                idxDidIndexType_st->dataRange_b = FALSE;
                idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8=E_OK;
            }
            /* If Last element is the matching local id */
            else if (Dcm_DIDConfig[posnEnd_u32].dataDid_u16 == did)
            {
                idxDidIndexType_st->idxIndex_u16=(uint16)posnEnd_u32;
                /*set the data range of Did value to FALSE and update info*/
                idxDidIndexType_st->dataRange_b = FALSE;
                idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                dataRetVal_u8=E_OK;
            }
            else
            {
                while (posnDid_u32 > 0u)
                {
                    posnDid_u32 += posnStart_u32;
                    if (Dcm_DIDConfig[posnDid_u32].dataDid_u16 == did)
                    {
                        idxDidIndexType_st->idxIndex_u16=(uint16)posnDid_u32;
                        /*Set did range status to FALSE*/
                        idxDidIndexType_st->dataRange_b = FALSE;
                        idxDidIndexType_st->nrNumofSignalsRead_u16 = 0x0;
                        idxDidIndexType_st->dataSignalLengthInfo_u32 = 0x0;
                        dataRetVal_u8=E_OK;
                        break;
                    }
                    else if (Dcm_DIDConfig[posnDid_u32].dataDid_u16 > did)
                    {
                        posnEnd_u32 = posnDid_u32;
                    }
                    else
                    {
                        posnStart_u32 = posnDid_u32;
                    }
                    posnDid_u32 = (posnEnd_u32-posnStart_u32)/2u ;
                }
            }
#endif
        }

    return (dataRetVal_u8);
}

#endif





#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
/**
 ********************************************************************************************************************************************
 * Dcm_GetSupportOfIndex:
 *
 * Calculate if the ID at position index in the Dcm_DIDConfig is supported at this point in time or not.
 *
 * \param     idxDidIndexType_st    :           index in Dcm_DIDConfig or Dcm_DIDRangeConfig strcture based on the dataRange_b status
 *            direction             :           check for read or write support:     DCM_SUPPORT_READ,    DCM_SUPPORT_WRITE
 *            dataNegRespCode_u8    :           Pointer to a Byte in which to store a negative Response code in case of detection of
 *                                              an error in the request.
 * \retval
 *
 * DCM_SUPPORT_OK,                ID is supported
 * DCM_SUPPORT_SESSION_VIOLATED,  ID is not supported in the current session; negative response code is set to dataNegRespCode_u8
 * DCM_SUPPORT_SECURITY_VIOLATED, ID is not supported in the current security level; negative response code is set to dataNegRespCode_u8
 * DCM_SUPPORT_CONDITION_VIOLATED,ID is not supported as per configured callback function; negative response code is set to dataNegRespCode_u8
 * DCM_SUPPORT_CONDITION_PENDING  checking needs more time. call again.
 * \seealso
 *
 ********************************************************************************************************************************************
 */

FUNC (Dcm_SupportRet_t,DCM_CODE) Dcm_GetSupportOfIndex( P2VAR   (Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA)   idxDidIndexType_st,
                                                        VAR (Dcm_Direction_t,AUTOMATIC) direction,
                                                        P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (uint32,AUTOMATIC) dataSessionMask_u32;   /* Variable to hold the configured sessions value */
    VAR (uint32,AUTOMATIC) dataSecurityMask_u32;  /* Variable to hold the configured security value */
    VAR (uint16, AUTOMATIC) dataDid_u16;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Pointer to extended configuration */
    VAR (Dcm_SupportRet_t, AUTOMATIC) dataRetVal_u8; /* return value of this function */
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
    VAR (Std_ReturnType,   AUTOMATIC) dataModeChkRetval_u8; /*Return value of mode rule check API*/
#endif
    VAR (boolean,   AUTOMATIC) flgModeRetVal_b; /*Return value of mode rule check API*/
    VAR (Dcm_NegativeResponseCodeType,   AUTOMATIC) dataNrc_u8;             /* Negative Response code for mode rule  */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;

    /* Initialize local variables */
    dataRetVal_u8 = DCM_SUPPORT_OK;  /* Return value of this function */
    ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
    ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
    ptrDIDFnc=NULL_PTR;

#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
    /*Check if did is a range did or not*/
    if(idxDidIndexType_st->dataRange_b == FALSE)
    {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        adrExtendedConfig_pcst = ptrDidConfig->adrExtendedConfig_pcst;
        dataDid_u16 = ptrDidConfig->dataDid_u16;
#endif
    }
    else
    {
        adrExtendedConfig_pcst = Dcm_DIDRangeConfig_cast[idxDidIndexType_st->idxIndex_u16].adrExtendedConfig_pcst;
        dataDid_u16 = idxDidIndexType_st->dataRangeDid_16;
    }
#else
    #if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
        adrExtendedConfig_pcst = ptrDidConfig->adrExtendedConfig_pcst;
        dataDid_u16 = ptrDidConfig->dataDid_u16;
    #endif
#endif
    *dataNegRespCode_u8     = 0x00;
    dataNrc_u8 = 0x0;
    /* Function is called by RDBI service */
    if (direction == DCM_SUPPORT_READ)
    {
#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
        /* Copy the session and security levels for read configured */
        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;
#endif
    }
#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
     /* Direction = DCM_SUPPORT_WRITE, Function is called by WDBI service */
    else
    {   /* Copy the session and security levels for write configured */
        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessWrite_u32;
        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecWrite_u32;
    }
#endif
    /* Check if the DID is allowed to be read/written in the active session and in current active configuration set*/
    if (((Dcm_DsldGetActiveSessionMask_u32 () & dataSessionMask_u32) != 0x0uL)
#if ((DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
         &&
         ((ptrDidConfig->dataConfigMask_u8 & Dcm_ActiveConfiguration_u8) != 0)
#endif
        )
    {
        /* Dcm435: Check if this DID is allowed  to be read/written in the current security level */
        if ((Dcm_DsldGetActiveSecurityMask_u32 () & dataSecurityMask_u32) != 0x0uL)
        {
            dataCondChkRetVal_u8 = E_OK; /* Initialize to E_OK */
            flgModeRetVal_b=TRUE;   /*Initialize to TRUE*/
            /* Request for reading */
            if (direction == DCM_SUPPORT_READ)
            {   /* Call the Read Condition check function if configured */
#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
                if(adrExtendedConfig_pcst->adrUserReadModeRule_pfct!=NULL_PTR)
                {
                    dataModeChkRetval_u8 = (*adrExtendedConfig_pcst->adrUserReadModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
                }
                else
                {
                    dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_READ);
                }
                if(dataModeChkRetval_u8!=E_OK)
                {
                    if(dataNrc_u8==0x00)
                    {
                        dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                    /*Update mode return value to FALSE*/
                    flgModeRetVal_b = FALSE;
                }
                else
                {
                    dataNrc_u8 =0x00;
                }

#if (DCM_CFG_DSP_MODERULEFORDIDREAD != DCM_CFG_OFF)
                if((dataNrc_u8==0x00)&& (NULL_PTR != adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))
                {
                    flgModeRetVal_b = (*(adrExtendedConfig_pcst->adrRdbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                }
#endif
                /*Check if flag for mode return value is set to TRUE*/
                if(FALSE != flgModeRetVal_b)
#endif
                {
                    /*Check if the DID request received false in the DID Range or not, if yes use Dcm_DIDRangeConfig_cast structure else use Dcm_DIDConfig*/

                    if(FALSE == idxDidIndexType_st->dataRange_b)
                    {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)
                        while((Dcm_DidSignalIdx_u16<ptrDidConfig->nrSig_u16)&&(dataCondChkRetVal_u8==E_OK))
                        {
                            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                            ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

                            if(ptrSigConfig->usePort_u8 != USE_BLOCK_ID)
                            {
                                if((ptrSigConfig->adrReadFnc_cpv)!= NULL_PTR)
                                {
                                    if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
                                    {
                                        ptrDIDFnc=ptrControlSigConfig->adrCondChkRdFnc_cpv;
                                    /* Call function to check if conditions are fulfilled to read the DID */
                                        if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||             \
                                            (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                                        {
                                            if(ptrDidConfig->dataDynamicDid_b != FALSE)
                                            {
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
                                                Dcm_DspDataOpstatus_u8  = idxDidIndexType_st->dataopstatus_b;
#endif
                                            }
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrDIDFnc))(dataNegRespCode_u8);
                                        }
                                        else
                                        {
                                            if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                               (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC) ||
#endif
                                               (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                                                {
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                                    /* Check whether Asynchronous server call point handling is requested for this DID */
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        if(!s_DcmReadDataConditionsRteCallPlaced_b)
                                        {
                                            /* Call Rte_Call API with only In and InOut Parameters */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc3_pfct)(ptrControlSigConfig->adrCondChkRdFnc_cpv))(idxDidIndexType_st->dataopstatus_b);
                                            if(dataCondChkRetVal_u8 == E_OK)
                                            {
                                                s_DcmReadDataConditionsRteCallPlaced_b = TRUE;
                                                /* So that the Rte_Result API will be invoked in the next raster */
                                                dataCondChkRetVal_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {

                                            }
                                        }
                                        else
                                        {
                                            /* Call the Rte_Result API to get the result of the Rte_Call */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrControlSigConfig->adrCondChkRdFncResults_cpv))(dataNegRespCode_u8);
                                            if (dataCondChkRetVal_u8 == E_OK)
                                            {
                                                s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataCondChkRetVal_u8 == RTE_E_NO_DATA)
                                            {
                                                /* The Rte_Result API will be invoked again in the next raster */
                                                dataCondChkRetVal_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
												/* Reset the Flag and update the NRC to General Reject */
                                                s_DcmReadDataConditionsRteCallPlaced_b = FALSE;
                                            }
                                        }
                                    }
                                    else
#endif
                                        {
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, dataNegRespCode_u8);
                                        }
                                     }
                                   }
                                        /* Check for infrastructural errors in case of RTE*/

                                        if((Dcm_IsInfrastructureErrorPresent_b(dataCondChkRetVal_u8) != FALSE)&&((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)))
                                        {
                                            /* Reset the nrc code so that general reject will be send*/
                                            *dataNegRespCode_u8 =0;
                                        }
                                        /* Don't continue if there is no permissions */
                                        if(dataCondChkRetVal_u8!=E_OK)
                                        {
                                            break;
                                        }
                                        else
                                        {
                                            *dataNegRespCode_u8=0x00;
                                        }
                                    }
                                }
                                else
                                {
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    /* Report development error "DCM_E_PARAM_POINTER" to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_RDBI_ID, DCM_E_PARAM_POINTER)
                                }
                            }
						Dcm_DidSignalIdx_u16++;	
                        }
#endif
                    }
                }
#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
                else
                {
                    *dataNegRespCode_u8 = dataNrc_u8;
                }
#endif
            }
#if ( DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
            else if(direction == DCM_SUPPORT_WRITE)
            {
                if(adrExtendedConfig_pcst->adrUserWriteModeRule_pfct!=NULL_PTR)
                {
                    /* Call the use configured API to check for conditions before writing to the DID */
                    dataModeChkRetval_u8 = (*adrExtendedConfig_pcst->adrUserWriteModeRule_pfct)(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
                }
                else
                {
                    /* Call the DcmAppl API to check for conditions before writing to the DID */
                    dataModeChkRetval_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,dataDid_u16,DCM_SUPPORT_WRITE);
                }

                if(dataModeChkRetval_u8!=E_OK)
                {
                    if(dataNrc_u8==0x00)
                    {
                        dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                    /*Reset the flag for mode return value to FALSE*/
                    flgModeRetVal_b = FALSE;
                }
                else
                {
                    dataNrc_u8=0x00;
                }

#if(DCM_CFG_DSP_MODERULEFORDIDWRITE !=DCM_CFG_OFF)
                if((dataNrc_u8==0x00)&&(NULL_PTR != adrExtendedConfig_pcst->adrWdbiModeRuleChkFnc_pfct))
                {
                    flgModeRetVal_b = (*(adrExtendedConfig_pcst->adrWdbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                }
#endif
                /*Check if flag for mode return value is set to FALSE*/
                if(FALSE == flgModeRetVal_b)
                {
                    *dataNegRespCode_u8 = dataNrc_u8;
                }

            }
            else
            {
                /*Dummy else*/
            }
#endif


                if ((dataCondChkRetVal_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00))
                {   /* All conditions are met */
                    /* RetVal is already set to DCM_SUPPORT_OK */
                    Dcm_DidSignalIdx_u16 = 0x0;
                    idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                }
                else if (dataCondChkRetVal_u8 == DCM_E_PENDING)
                {   /* More time needed for API processing */
                    *dataNegRespCode_u8=0x00;
                    dataRetVal_u8 = DCM_SUPPORT_CONDITION_PENDING;
                    idxDidIndexType_st->dataopstatus_b = DCM_PENDING;
                }
                else
                {   /* Update the ErrorCode to General Reject */
                    if(*dataNegRespCode_u8==0x00)
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }
                    dataRetVal_u8       = DCM_SUPPORT_CONDITION_VIOLATED;
                    Dcm_DidSignalIdx_u16 = 0x0;
                    idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                }

        }
        /* If DID read/write is not supported in active security level */
        else
        {
            *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
            dataRetVal_u8       = DCM_SUPPORT_SECURITY_VIOLATED;
        }
    }
    /* If DID read/write is not supported in active session */
    else
    {
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        dataRetVal_u8       = DCM_SUPPORT_SESSION_VIOLATED;
    }
    return dataRetVal_u8;
}
#endif

#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
/**
 *********************************************************************************************************************************
 * Dcm_GetDIDData:
 *
 * The function is used to read the DID data of the requested DID by calling the corresponding
 * configured function for reading the data. The DID value is not written in the buffer
 *
 * \param     idxDidIndexType_st    :           index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on dataRange_b status
 *            targetBuffer          :           Pointer to the buffer where the data is to be written
 *
 * \retval
 * E_OK                                         DID data is read successfully
 * DCM_E_PENDING                                More time is required to read the data
 * E_NOT_OK                                     DID data was not read successfully
 * \seealso
 *
 **********************************************************************************************************************************
 */
FUNC (Std_ReturnType,DCM_CODE) Dcm_GetDIDData (P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA ) idxDidIndexType_st,
                                               P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) targetBuffer)
{
#if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
    VAR (uint16, AUTOMATIC) datasignallength_u16; /* Local variable to store the length for a particular signal*/
#endif
#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
VAR(uint16,DCM_VAR) idxRange_u16;
#endif

    /* Local variables to read the signals */
    VAR (uint32, AUTOMATIC) posnTargetSig_u32;

#if(DCM_CFG_DSP_READ_SR_ENABLED!=DCM_CFG_OFF)
    VAR (uint16, AUTOMATIC) nrElements_u16;
    VAR (uint16, AUTOMATIC) idxLoop_u16;
    VAR (uint32, AUTOMATIC) dataSignal_u32;
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
    VAR (uint16, AUTOMATIC) dataSignal_u16;
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint16, AUTOMATIC) dataSignal_s16;
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint32, AUTOMATIC) dataSignal_s32;
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
    VAR (sint8,  AUTOMATIC) dataSignal_s8;
#endif
#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
    VAR (boolean,AUTOMATIC) dataSignal_b;
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
    VAR (uint8,  AUTOMATIC) dataSignal_u8;
#endif

    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
#if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
#endif
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
    P2CONST (Dcm_DIDRangeConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrDIDRangeConfig;
#endif

#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
    VAR (Std_ReturnType, AUTOMATIC) dataNvmGetErrorRetVal_u8;
    VAR (Std_ReturnType, AUTOMATIC) dataNvmReadBlockRetVal_u8;
    VAR (NvM_RequestResultType, AUTOMATIC) dataRequestResult_u8;
#endif
    /* Initialization of local variables */
#if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
    datasignallength_u16 = 0x0u;
#endif

#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_b   = FALSE;
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u8  = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u16 = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_u32 = 0x0u;
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s8  = 0x0;
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s16 = 0x0;
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
    dataSignal_s32 = 0x0;
#endif

    ptrDidConfig =&Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    ptrDIDFnc=NULL_PTR;
#if(DCM_CFG_DSP_READ_SR_ENABLED!=DCM_CFG_OFF)
    nrElements_u16=0x0u;
    idxLoop_u16=0x0u;
#endif

    if(targetBuffer!= NULL_PTR)
    {
        /*Check if Did is a range did or not*/
        if(idxDidIndexType_st->dataRange_b == FALSE)
        {
#if (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF)

            if(s_dataRetVal_u8 != DCM_E_PENDING)
            {
                /* Reset the TargetBuffer with Default values (DCM_CFG_SIGNAL_DEFAULT_VALUE) before filling data */
                /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMSET takes void pointer as input and object type pointer is converted to void pointer*/
                DCM_MEMSET(targetBuffer, (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, ptrDidConfig->dataMaxDidLen_u16);
            }

            /* Call ReadFnc for all DID data elements */
            for(;((idxDidIndexType_st->nrNumofSignalsRead_u16) < (ptrDidConfig->nrSig_u16));idxDidIndexType_st->nrNumofSignalsRead_u16++)
            {
                ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].idxDcmDspDatainfo_u16];
                posnTargetSig_u32 = (idxDidIndexType_st->dataSignalLengthInfo_u32);

                if(((s_dataLengthFnc_retVal_u8==E_OK)&&(s_dataRetVal_u8==E_OK))||(s_dataLengthFnc_retVal_u8==DCM_E_PENDING))
                {
                    /*Check if DID has signals of fixed length TYPE*/
                    if(FALSE != ptrSigConfig->dataFixedLength_b)
                    {
                        /*This portion is executed only for fixed length signal in a DID*/
                        posnTargetSig_u32 =(uint32)(ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16/8);
                        s_datasignallength_u32 = (uint32)((ptrSigConfig->dataSize_u16/8) + posnTargetSig_u32);
                        s_dataLengthFnc_retVal_u8 = E_OK;
                    }
                    else
                    {
#if ((DCM_CFG_DSP_READ_VARIABLE_LENGTH!=DCM_CFG_OFF) || (DCM_CFG_DSP_IOCTRL_VARIABLE_LENGTH!=DCM_CFG_OFF))
                        ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
                        /*This portion is executed only for variable length signal in a DID, to determine the target position for filling the Data in
                         * the buffer for all the signals based on the length returned by the application*/
                        /*If the DID is a DDDI the length returned will be bytes, where as for a normal DID it will be in bits.*/
                        /*If Dynamically Defined DID value is set to FALSE*/
                        if(FALSE==ptrDidConfig->dataDynamicDid_b)
                        {
                            /* Get the length from the configured API */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                            {
                                s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&datasignallength_u16);
                            }
                            else
                            {
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                            || (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                                  )
                                {
    #if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                                    /* If Asynchronous server point handling is requested for the DID Data */
                                    if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        if(!s_DcmReadDataLengthRteCallPlaced_b)
                                        {
                                            /* Invoke the Rte_Call API with In and InOut Parameters */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            s_dataLengthFnc_retVal_u8 = (*(ReaddatalengthFnc5_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))();
                                            if(s_dataLengthFnc_retVal_u8 == E_OK)
                                            {
                                                /* To Invoke the Rte_Result API in the next raster */
                                                s_DcmReadDataLengthRteCallPlaced_b = TRUE;
                                                s_dataLengthFnc_retVal_u8 = DCM_E_PENDING;
                                            }
                                            /* Dummy else to remove Misra Warnings */
                                            /* The requierd NRC will be set by the Calling API */
                                            else
                                            {

                                            }
                                        }
                                        else
                                        {
                                            /* Call the Rte_Result API */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrControlSigConfig->adrReadDataLengthFncResults_pfct))(&datasignallength_u16);
                                            if (s_dataLengthFnc_retVal_u8 == E_OK)
                                            {
                                                s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                            }
                                            else if(s_dataLengthFnc_retVal_u8 == RTE_E_NO_DATA)
                                            {
                                                /* The RTE_RESULT API will be invoked again i nthe next raster to get the result */
                                                s_dataLengthFnc_retVal_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                                s_DcmReadDataLengthRteCallPlaced_b = FALSE;
                                            }
                                        }
                                    }
                                    else
    #endif
                                    {
                                        s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(idxDidIndexType_st->dataopstatus_b,&datasignallength_u16);
                                    }
                                }
                            }
                            s_datasignallength_u32 = (uint32)datasignallength_u16;
                        }
                        else
                        {
                            /* Get the length from the configured API */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            s_dataLengthFnc_retVal_u8 = (*(ReadDataLengthFnc2_pf)(ptrControlSigConfig->adrReadDataLengthFnc_pfct))(&(s_datasignallength_u32));
                        }

                        if(E_OK==s_dataLengthFnc_retVal_u8)
                        {
                            /* If the length received in more than the configured maximum length for a length then return E_NOT_OK */
                            /*For Dynamic DID the length returned by the length function will be in bytes, so divide the signal datasize
                             * by 8 for converting signal size to bytes*/
                            /*If Dynamically Defined DID value is set to FALSE*/
                            if(   (ptrDidConfig->dataDynamicDid_b == FALSE)
                                &&(   ((s_datasignallength_u32*8u) > (ptrSigConfig->dataSize_u16))
                                    ||(s_datasignallength_u32==0u)
                                  )
                              )
                            {
                                s_dataLengthFnc_retVal_u8 = E_NOT_OK;
                                /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                                break;
                            }
                            idxDidIndexType_st->dataopstatus_b = DCM_INITIAL;
                        }
                        else
                        {
                                /* If infrastructure Error is present and check for the synch and asynch port */
                            if(    (Dcm_IsInfrastructureErrorPresent_b(s_dataLengthFnc_retVal_u8) != FALSE)
                                && (   (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                                     ||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                                   )
                              )
                            {
                                s_dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
                            }
                            else if(DCM_E_PENDING==s_dataLengthFnc_retVal_u8)
                            {
                                s_dataRetVal_u8 = DCM_E_PENDING;
                            }
                            else
                            {
                                s_dataRetVal_u8 = E_NOT_OK;
                            }
                            /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                            break;
                        }

#endif
                        s_datasignallength_u32 = (uint32)(s_datasignallength_u32 + idxDidIndexType_st->dataSignalLengthInfo_u32);
                    }
                }

                /* Find the port configured for the Signal */
                if (ptrSigConfig->adrReadFnc_cpv != NULL_PTR)
                {
                    ptrDIDFnc=ptrSigConfig->adrReadFnc_cpv;
                    /* If the read operation is synchronous */
                    if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||
                    (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                    {
#if((DCM_CFG_DSP_READ_SYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED!=DCM_CFG_OFF))
                        /*Check if Dynamically Defined DID value is set to FALSE*/
                        if(FALSE == ptrDidConfig->dataDynamicDid_b)
                        {
                            /* Dcm437: Call function to check if conditions are fulfilled to read the DID */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(&targetBuffer[posnTargetSig_u32]);
                        }
                        else
                        {
                            /* Dcm437: Call function to check if conditions are fulfilled to read the DID */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            s_dataRetVal_u8 = (*(ReadFunc10_pfct)(ptrDIDFnc))(&targetBuffer[posnTargetSig_u32],&(idxDidIndexType_st->dataNegRespCode_u8));
                            if(idxDidIndexType_st->dataNegRespCode_u8!=0)
                            {
                                s_dataRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif
                    }

#if((DCM_CFG_DSP_READ_ASYNCH_FNC_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED!= DCM_CFG_OFF))
                    /* If the read operation is Asynchronous */
                    else if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)||
                    (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                    {
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                        if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                        {
                            if(!s_DcmReadDataRteCallPlaced_b)
                            {
                                /* Call Rte_Call API with only In and InOut Parameters */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                s_dataRetVal_u8 = (*(ReadFunc11_ptr)(ptrSigConfig->adrReadFnc_cpv))(idxDidIndexType_st->dataopstatus_b);
                                if(s_dataRetVal_u8 == E_OK)
                                {
                                    s_DcmReadDataRteCallPlaced_b = TRUE;
                                    s_dataRetVal_u8 = DCM_E_PENDING;
                                }
                                /* Dummy else to remove Misra. The required NRC will be set by the calling API */
                                else
                                {

                                }
                            }
                            else
                            {
                                /* Call the Rte_Result API to get the result of the Rte_Call */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrSigConfig->adrReadFncResults_cpv))(&targetBuffer[posnTargetSig_u32]);
                                if (s_dataRetVal_u8 == E_OK)
                                {
                                    s_DcmReadDataRteCallPlaced_b = FALSE;
                                }
                                else if(s_dataRetVal_u8 == RTE_E_NO_DATA)
                                {
                                    /* The Rte_Result API will be invoked again in the next raster */
                                    s_dataRetVal_u8 = DCM_E_PENDING;
                                }
                                else
                                {
                                    s_DcmReadDataRteCallPlaced_b=FALSE;
                                }
                            }
                        }
                        else
#endif
                        {
                            /* Dcm437: Call function to check if conditions are fulfilled to read the DID */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            s_dataRetVal_u8 = (*(ReadFunc2_ptr)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &targetBuffer[posnTargetSig_u32]);
                        }
                    }
#endif
                    else
                    {
#if(DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)
                        /* Read operation is using Sender Receiver interfaces */
                        if(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)
                        { /* Check for the Data type of the signal */
                            switch(ptrSigConfig->dataType_u8)
                            {
#if(DCM_CFG_DSP_READ_BOOLEAN_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_BOOLEAN:
                                { /* Read Boolean signal */
                                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                    s_dataRetVal_u8 = (*(ReadFunc3_pfct)(ptrDIDFnc))(&dataSignal_b);

                                    dataSignal_u32 = 0x0;
                                    /*To suppress compiler warnings in case boolean signal alone is enabled in case of SENDER RECEIVER*/
                                    (void)nrElements_u16;
                                    (void)idxLoop_u16;
                                    /* Check if the signal is set and copy */
                                    if(dataSignal_b != (boolean)0x00u)
                                    {
                                        dataSignal_u32 = 0x01;
                                    }
                                    /* Store the read signal before proceeding to next signal */
                                    Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                    ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16,
                                    targetBuffer, dataSignal_u32,
                                    ptrSigConfig->dataEndianness_u8);
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_UINT8_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_UINT8:
                                {
                                    nrElements_u16 = (uint16)((uint32)ptrSigConfig->dataSize_u16/8u);
                                    if(ptrSigConfig->dataSize_u16 == 8)
                                    { /* Read uint8 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(&dataSignal_u8);
                                        Dcm_DspArraySignal_au8[0] = dataSignal_u8;
                                    }
                                    else /* Array of UINT8 */
                                    { /* Read uint8 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc1_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au8);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_au8[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_UINT16_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_UINT16:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);
                                    if(ptrSigConfig->dataSize_u16 == 16)
                                    { /* Read uint8 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc4_pfct)(ptrDIDFnc))(&dataSignal_u16);
                                        Dcm_DspArraySignal_au16[0] = dataSignal_u16;
                                    }
                                    else
                                    { /* Read uint16 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc4_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au16);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_au16[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_UINT32_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_UINT32:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);
                                    if(ptrSigConfig->dataSize_u16 == 32)
                                    { /* Read uint32 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc5_pfct)(ptrDIDFnc))(&dataSignal_u32);
                                        Dcm_DspArraySignal_au32[0] = dataSignal_u32;
                                    }
                                    else
                                    { /* Read uint32 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc5_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_au32);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = Dcm_DspArraySignal_au32[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_SINT8_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_SINT8:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/8u);
                                    if(ptrSigConfig->dataSize_u16 == 8)
                                    { /* Read sint8 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc6_pfct)(ptrDIDFnc))(&dataSignal_s8);
                                        Dcm_DspArraySignal_as8[0] = dataSignal_s8;
                                    }
                                    else
                                    { /* Read sint8 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc6_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as8);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as8[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*8))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_SINT16_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_SINT16:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/16u);
                                    if(ptrSigConfig->dataSize_u16 == 16)
                                    { /* Read sint16 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc7_pfct)(ptrDIDFnc))(&dataSignal_s16);
                                        Dcm_DspArraySignal_as16[0] = dataSignal_s16;
                                    }
                                    else
                                    { /* Read sint16 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc7_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as16);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as16[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*16))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
#if(DCM_CFG_DSP_READ_SINT32_SR_ENABLED != DCM_CFG_OFF)
                                case DCM_SINT32:
                                {
                                    nrElements_u16 = (uint16)((uint32)(ptrSigConfig->dataSize_u16)/32u);
                                    if(ptrSigConfig->dataSize_u16 == 32)
                                    { /* Read sint32 signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc8_pfct)(ptrDIDFnc))(&dataSignal_s32);
                                        Dcm_DspArraySignal_as32[0] = dataSignal_s32;
                                    }
                                    else
                                    { /* Read sint32 array of signal */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        s_dataRetVal_u8 = (*(ReadFunc8_pfct)(ptrDIDFnc))(Dcm_DspArraySignal_as32);
                                    }
                                    /* Copy the signals to Global buffer */
                                    for(idxLoop_u16=0; ((idxLoop_u16 < nrElements_u16)&&(s_dataRetVal_u8 == E_OK)); idxLoop_u16++)
                                    {
                                        dataSignal_u32 = (uint32)Dcm_DspArraySignal_as32[idxLoop_u16];
                                        /* Store the read signal before proceeding to next signal */
                                        Dcm_StoreSignal(ptrSigConfig->dataType_u8,
                                        (uint16)((ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16+(uint16)(idxLoop_u16*32))),
                                        targetBuffer, dataSignal_u32,
                                        ptrSigConfig->dataEndianness_u8);
                                    }
                                    break;
                                }
#endif
                                default:
                                { /* Dummy code */
                                    break;
                                }
                            }
                        }
#endif
                    }

                    /* Check for infrastructure errors, in case of rte*/
                    /*If DID signal Data Port Interface Types is supported*/
                    if(     (Dcm_IsInfrastructureErrorPresent_b(s_dataRetVal_u8) != FALSE)
                         && (   (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)
                              ||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)
                              ||(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)
                            )
                      )
                    {
                        s_dataRetVal_u8 =E_NOT_OK;
                    }
                    if(s_dataRetVal_u8 != E_OK)
                    {
                        /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                        break;
                    }
                    else
                    {
                        if(     (ptrSigConfig->dataType_u8==DCM_BOOLEAN)
                             && (    ( (idxDidIndexType_st->nrNumofSignalsRead_u16) == (ptrDidConfig->nrSig_u16-1u) )
                                   ||
                                     (    (ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].posnSigBit_u16/8u)
                                       != (ptrDidConfig->adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16+1].posnSigBit_u16/8u)
                                     )
                                )
                          )
                        {
                            idxDidIndexType_st->dataSignalLengthInfo_u32+=1u;
                        }
                        else
                        {
                            idxDidIndexType_st->dataSignalLengthInfo_u32 = s_datasignallength_u32;
                        }
                    }
                }
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                else if(ptrSigConfig->usePort_u8 == USE_BLOCK_ID)
                {
                    /*Check if Non volatile memory read status is pending or not*/
                    if(idxDidIndexType_st->flgNvmReadPending_b== FALSE)
                    {
						/*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as NvM_ReadBlock takes void pointer as input and object type pointer is converted to void pointer*/
                        dataNvmReadBlockRetVal_u8=NvM_ReadBlock(Dcm_DspDataInfo_st[Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16].adrDidSignalConfig_pcst[idxDidIndexType_st->nrNumofSignalsRead_u16].idxDcmDspDatainfo_u16].dataNvmBlockId_u16,&targetBuffer[posnTargetSig_u32]);
                        if(dataNvmReadBlockRetVal_u8 != E_OK)
                        {
                            /*NvmReadPending flag is pending*/
                            idxDidIndexType_st->flgNvmReadPending_b = FALSE;
                            s_dataRetVal_u8 =E_NOT_OK;
                        }
                        else
                        {
                            /*NvmReadPending flag is pending status is set TRUE*/
                            idxDidIndexType_st->flgNvmReadPending_b = TRUE;
                            s_dataRetVal_u8 =DCM_E_PENDING;
                        }
                    }
                    else
                    {
                        dataNvmGetErrorRetVal_u8= NvM_GetErrorStatus(ptrSigConfig->dataNvmBlockId_u16,&dataRequestResult_u8);
                        /*NvmReadPending flag status is set FALSE*/
                        idxDidIndexType_st->flgNvmReadPending_b =FALSE;
                        if(dataNvmGetErrorRetVal_u8 != E_OK)
                        {
                            s_dataRetVal_u8 =E_NOT_OK;
                        }
                        else
                        {
                            if((dataRequestResult_u8 == NVM_REQ_INTEGRITY_FAILED) || (dataRequestResult_u8 == NVM_REQ_NV_INVALIDATED) ||
                            (dataRequestResult_u8 == NVM_REQ_CANCELED) || (dataRequestResult_u8 == NVM_REQ_REDUNDANCY_FAILED) ||
                            (dataRequestResult_u8 == NVM_REQ_RESTORED_FROM_ROM) || (dataRequestResult_u8 == NVM_REQ_NOT_OK))
                            {
                                s_dataRetVal_u8 =DCM_E_REQUEST_ENV_NOK;
                            }
                            else if(dataRequestResult_u8 == NVM_REQ_PENDING)
                            {
                                /*NvmReadPending flag status is set TRUE*/
                                idxDidIndexType_st->flgNvmReadPending_b = TRUE;
                                s_dataRetVal_u8 = DCM_E_PENDING;
                            }
                            else if(dataRequestResult_u8==NVM_REQ_OK)
                            {
                                s_dataRetVal_u8 =E_OK;
                            }
                            else
                            {
                                s_dataRetVal_u8 =E_NOT_OK;
                            }
                        }
                    }
                }
                else
                {
                    /* Dummy else to remove MISRA warning */
                }
                if(s_dataRetVal_u8 != E_OK)
                {
                    /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement. */
                    break;
                }
#endif
                else
                {

                }

            }
#endif
        }
        else
        {
#if (DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
            VAR(uint16,AUTOMATIC) dataSignallength_u16;

            /*The index in (idxDidIndexType_st->idxIndex_u16) represents the DID and not index in Dcm_DIDRangeConfig_cast structure array*/
            for(idxRange_u16=0;idxRange_u16<DCM_CFG_NUMOFDIDRANGES;idxRange_u16++)
            {
                ptrDIDRangeConfig=&Dcm_DIDRangeConfig_cast[idxRange_u16];
                if(    ((idxDidIndexType_st->dataRangeDid_16) >= (ptrDIDRangeConfig->nrDidRangeLowerLimit_u16))
                    && ((idxDidIndexType_st->dataRangeDid_16) <= (ptrDIDRangeConfig->nrDidRangeUpperLimit_u16))
                  )
                {
                    break;
                }
            }

            /*Check if the DID is valid*/
            if(idxRange_u16 < DCM_CFG_NUMOFDIDRANGES)
            {
                if ((ptrDIDRangeConfig->adrReadFnc_pfct)!= NULL_PTR)
                {
                    /* Fill Buffer with Default value configured in Dcm */
                    if(s_dataRetVal_u8 != DCM_E_PENDING)
                    {
                        /* Reset the TargetBuffer with Default values (DCM_CFG_SIGNAL_DEFAULT_VALUE) before filling data */
                        /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
                        DCM_MEMSET(targetBuffer, (sint32)DCM_CFG_SIGNAL_DEFAULT_VALUE, ptrDIDRangeConfig->dataMaxDidLen_u16);
                    }

                    dataSignallength_u16 = (uint16)(idxDidIndexType_st->dataSignalLengthInfo_u32);

                    s_dataRetVal_u8 = (*(ptrDIDRangeConfig->adrReadFnc_pfct))
                    (idxDidIndexType_st->dataRangeDid_16,targetBuffer,idxDidIndexType_st->dataopstatus_b,&(dataSignallength_u16),&(idxDidIndexType_st->dataNegRespCode_u8));

                    /* Check for infrastructure errors in case of RTE*/
                    /*If infrastructure error flag returns TRUE and Did data length is fixed and send negative response is valid */
                    if((Dcm_IsInfrastructureErrorPresent_b(s_dataRetVal_u8) != FALSE) && (ptrDIDRangeConfig->nrRangeUsePort_b != FALSE) && (&(idxDidIndexType_st->dataNegRespCode_u8) != NULL_PTR))
                    {
                        idxDidIndexType_st->dataNegRespCode_u8 = 0x00;
                    }
                    if((idxDidIndexType_st->dataNegRespCode_u8 != 0x00) && (&(idxDidIndexType_st->dataNegRespCode_u8) != NULL_PTR))
                    {
                        s_dataRetVal_u8=E_NOT_OK;
                    }
                }
            }
            else
            {
                /*Trigger Negative response*/
                s_dataRetVal_u8 = E_NOT_OK;
            }
#endif
        }
        if(s_dataRetVal_u8 != DCM_E_PENDING)
        /* Reset back the variable */
        {
            idxDidIndexType_st->nrNumofSignalsRead_u16=0x0; /*Reset the number of signals read variable to zero for E_OK and E_NOT_OK case*/
            idxDidIndexType_st->dataSignalLengthInfo_u32=0x0;/*Reset the number of signals length information to zero*/
        }
    }
    else
    {
        s_dataRetVal_u8 = E_NOT_OK;
    }
    return (s_dataRetVal_u8);
}

    #endif

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
/**
 *************************************************************************************************************************************************************
 * Dcm_GetActiveDid:
 *
 * This API will update the normal DID currently being processed by Dsp RDBI/WDBI/IOCBI services .The API can be polled from  Read/CondionCheckRead/ReadDataLength functions
 * during RDBI request processing, * Write function during WDBI request processing and from FreezeCurrentState/ResetToDefault/ShortTermAdjustment/ReturnControlToEcu/Read
 * function during IOCBI request processing.The API can be used to identify the appropriate data requested by the application.If the API is called from anywhere outside
 * the mentioned  application APIs while processing the requested services, the DID value may not be correct.In case the DID currently under process is a normal DID,
 * E_OK is returned and a valid value is filled in the parameter passed.In case the DID currently under process is a range DID, E_NOT_OK is returned.
 *
 *
 * \param     uint16* dataDid_u16 : Parameter for updating of the DID under processing. The DID value returned is valid only if return value is E_OK.
 * \retval    Std_ReturnType : E_OK : The DID under processing is a normal DID.The parameter dataDid_u16 contains valid DID value in this case.
 *                             E_NOT_OK: The DID under processing is a range DID. The parameter dataDid_u16 contains invalid data in this case.
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8; /* Variable to store the return value */

    /* Initialization of local variables  */
    dataRetVal_u8 = E_NOT_OK;
    /* If the service  being processed is a Dsp RDBI service */
    if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_READDATABYIDENTIFIER)
    {
#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveRDBIDid(dataDid_u16);
#endif
    }
    /* If the service  being processed is a Dsp WDBI service */
    else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_WRITEDATABYIDENTIFIER)
    {
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveWDBIDid(dataDid_u16);
#endif
    }
    /* If the service being processed is a Dsp DDDI service */
    else if(Dcm_DsldGlobal_st.dataSid_u8 == DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER)
    {
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
         dataRetVal_u8 = Dcm_GetActiveDDDid(dataDid_u16);
#endif
     }
    /* If the service  being processed is a Dsp IOCBI service */
    else
    {
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
        dataRetVal_u8 = Dcm_GetActiveIOCBIDid(dataDid_u16);
#endif
        /* Do nothing. Dummy else */
    }

    return (dataRetVal_u8);
}
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


