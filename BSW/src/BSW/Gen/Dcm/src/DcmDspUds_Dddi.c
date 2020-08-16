

#include "DcmDspUds_Dddi_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Variable to store state of function Dcm_DcmDddiAddIdRecords_u8 */
VAR (Dcm_DddiDefineById_ten,DCM_VAR) Dcm_stAddIdRecords_en;

#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
static VAR (Dcm_DddiWriteOrClear_ten,DCM_VAR) s_isWriteOrClear_en; /* Enum to inform application whether it is a clear operation or Write operation */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (uint16 ,DCM_VAR) Dcm_AddIdCurrentBlockIndex_u16;       /* Variable to store the index of the current block */

static VAR (uint16,DCM_VAR) s_ActiveDDDI_u16; /* DDDI for which the write and clear NvM APIs are called */


#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (uint32,DCM_VAR) Dcm_AddIdCurrentLength_u32;            /* Variable to store the length of the DDDI */

static VAR (uint32,DCM_VAR) s_dataLength_u32; /* Variable to store the length of the DID */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspDddidOpStatus_u8;    /* Variable to store the opstatus*/

static VAR (Std_ReturnType, DCM_VAR) s_dataFunctionRetVal_u8;

static VAR (Std_ReturnType, DCM_VAR) s_dataLengthFuncRetVal_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxSrcDidIndexType_st;  /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
VAR (Dcm_DddiDefineByMem_ten,DCM_VAR) Dcm_stAddMemRecords_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Variable to store the index of the block being added */
VAR (uint16 ,                 DCM_VAR) Dcm_AddMemCurrentBlockIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (Dcm_DddiServiceStatus_ten ,DCM_VAR)   Dcm_DspStDddi_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/**
 **************************************************************************************************
 * Dcm_DddiCheckOverflow : Function to check memory requirements in case of SubFunction - DefineByMemoryAddress
 *
 * \param           MemLength_u32 : Requested memory size from the request
 *                  AddIdCurrentLength_u32 : Current length of memory updated
 *                  MaxDidLen_u16 : Maximum data size configured for the DID
 * \retval         boolean :  TRUE : The memory requirements are valid
 *                            FALSE : Memory requirements are not met (possibly overflow memory exceeds uint32 value)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

static FUNC(boolean,DCM_CODE)Dcm_DddiCheckOverflow(VAR(uint32,AUTOMATIC) MemLength_u32, VAR(uint32,AUTOMATIC) AddIdCurrentLength_u32, VAR(uint16,AUTOMATIC) MaxDidLen_u16);

static FUNC(boolean,DCM_CODE)Dcm_DddiCheckOverflow(VAR(uint32,AUTOMATIC) MemLength_u32, VAR(uint32,AUTOMATIC) AddIdCurrentLength_u32, VAR(uint16,AUTOMATIC) MaxDidLen_u16)
{
    VAR(boolean,AUTOMATIC) flag_b;
    flag_b = FALSE;

  if( (uint32)MaxDidLen_u16 > MemLength_u32)
  {
       if(((uint32)(MaxDidLen_u16) - ( MemLength_u32)) >= AddIdCurrentLength_u32)
       {
           flag_b = TRUE;
       }
       /* Dummy Else to remove Misra */
       else
       {

       }
  }
  /* Dummy else to remove misra */
  else
  {

  }
  return flag_b;
}


/**
 **************************************************************************************************
 * Dcm_GetDynamicSignalConfiguration : Function to get the dynamic configuration(position and size)
 *                                    of the signals of a DID
 *
 * \param           DidIndex_u16 : Index of the DID
 *
 * \retval          Std_ReturnType : E_OK,E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetDynamicSignalConfiguration(uint16 DidIndex_u16);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_GetDynamicSignalConfiguration(uint16 DidIndex_u16)
{
    VAR (uint32,        AUTOMATIC) dataSigLength_u32;  /* Local variable to store the adrTotalLength_pu16                            */
    VAR (uint16,        AUTOMATIC) dataSigLength_u16;  /* Local variable to store the adrTotalLength_pu16                            */
    VAR (uint16,        AUTOMATIC) index_u16;          /* Local variable to loop through the DID signals                             */
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;      /* Local variable to store the return value of the API                        */
    VAR(boolean,        AUTOMATIC) stVariableLength_b; /* Local variable to store if the signal is the first variable length signal  */

    /* Initialization of local variables */
    dataSigLength_u32   = 0x00;
    dataSigLength_u16   = 0x00;
    /*Initialize the variable length signal value to FALSE*/
    stVariableLength_b  = FALSE;
    dataRetVal_u8       = E_NOT_OK;

    /* Loop through all the DIDs of the signal */
    for(index_u16=0;index_u16<Dcm_DIDConfig[DidIndex_u16].nrSig_u16;index_u16++)
    {
        /* If the signal is of fixed length */

        if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataFixedLength_b   !=FALSE)
        {
            /* If the signal is not of type boolean */
            if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataType_u8!=DCM_BOOLEAN)
            {
                /* Store the position and data size */
                Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32=Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16;
                Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32=Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataSize_u16;
            }
            /* If the signal is of type boolean */
            else
            {
                /* Set the position to the start position of the byte */
                Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32  = (Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16/8)*8;
                /* Set the data size of the boolean signal to 8 */
                Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = 8 ;
            }
            /* Set the return value to E_OK */
            dataRetVal_u8=E_OK;
        }
        /* If the signal is the first variable length signal */

        else if(stVariableLength_b==FALSE)
        {
            /*Set the variable length signal value to TRUE*/
            stVariableLength_b=TRUE;
            /* Set the position to the configured position */
            Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32 =Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].posnSigBit_u16;
        }
        /* If the signal is of type variable length but not the first variable length signal */
        else
        {
            /* Calculate the position from the previous signal position and size */
            Dcm_DynamicSignalConfig_cast[index_u16].sigPosnBit_u32 =Dcm_DynamicSignalConfig_cast[(index_u16-1)].sigPosnBit_u32+Dcm_DynamicSignalConfig_cast[(index_u16-1)].sigDataSize_u32;
        }
        /* If the signal is of variable length type */

        if(Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataFixedLength_b   ==FALSE)
        {
            /* Check for USE FUNC and valid Read Data length function configuration */
            if(((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_FNC) || \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC) ||    \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) ||   \
                    (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)) &&     \
                    ((Dcm_DIDConfig[DidIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32 >0x00u) && (Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct != NULL_PTR)))

            {
                /* Check if the DID is a dynamically defined or not, if it is a dynamically defined DID one typecast it to ReadDataLengthFnc2_pf whose data length *
                 *  parameter is of uint32 type where as if it is a normal one typecast it to ReadDataLengthFnc1_pf whose data length parameter is of 2bytes       */

                if(FALSE==Dcm_DIDConfig[DidIndex_u16].dataDynamicDid_b)
                {
                    /* Get the length from the configured API */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    if ((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_FNC) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
                    {
                        dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(&dataSigLength_u16);
                    }
                    else
                    {
                        if((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                                ||  (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
    #endif
                        )
                        {
                            dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(s_Dcm_idxSrcDidIndexType_st.dataopstatus_b,&dataSigLength_u16);
                        }
                   }
                   Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = dataSigLength_u16*8uL;
                }
                else
                {
                    /* Get the length from the configured API */
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetVal_u8 = (*(ReadDataLengthFnc2_pf)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrReadDataLengthFnc_pfct))(&dataSigLength_u32);
                    /*Convert the Data length returned by DDDI length function in to bits, since DDDI length function returns the length always in bytes*/
                    Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 = dataSigLength_u32*8uL;

                }

                if(dataRetVal_u8==E_OK)
                {

                    /* If the length received in more than the configured maximum length for a length then return error */

                    if(((Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32 > Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].dataSize_u16) ||(Dcm_DynamicSignalConfig_cast[index_u16].sigDataSize_u32==0u)) &&(Dcm_DIDConfig[DidIndex_u16].dataDynamicDid_b == FALSE))
                    {
                        dataRetVal_u8 = E_NOT_OK;
                        break;
                    }
                }
                else if((dataRetVal_u8==DCM_E_PENDING) && ((Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) || (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        ||  (Dcm_DspDataInfo_st[Dcm_DIDConfig[DidIndex_u16].adrDidSignalConfig_pcst[index_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
#endif
                ))
                {
                }
                else
                {
                    /* Do nothing. Infrastructure error is not returned separately as the NRC 0x10 is sent to the tester for any return type other than E_OK */
                }
            }
        }
    }
    return(dataRetVal_u8);
}

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
/**
 **************************************************************************************************
 * Dcm_isDDDIDSupported : Function to check if the DDDId is supported in current variant
 *                                    of the signals of a DID
 *
 * \param           DynamicIdentifier_u16 : DynamicallyDefinedDataIdentifier to be checked
 *
 * \retval          Std_ReturnType : E_OK,E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(Std_ReturnType, DCM_CODE) Dcm_isDDDIDSupported(uint16 DynamicIdentifier_u16);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_isDDDIDSupported(uint16 DynamicIdentifier_u16)
{
    VAR(uint16,AUTOMATIC) index_u16;
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    retVal_u8 =E_OK;

    for(index_u16 =0x00;index_u16<Dcm_DIDcalculateTableSize_u16();index_u16++)
    {
        if(Dcm_DIDConfig[index_u16].dataDid_u16==DynamicIdentifier_u16)
        {
            break;
        }
    }
    if(index_u16==Dcm_DIDcalculateTableSize_u16())
    {
        retVal_u8= E_NOT_OK;
    }
    else
    {
        if(*Dcm_DIDIsAvail[Dcm_DIDConfig[index_u16].idxDIDSupportedFnc_u16]!=NULL_PTR)
        {
            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[index_u16].idxDIDSupportedFnc_u16]))(DynamicIdentifier_u16)!=E_OK)
            {
                retVal_u8 = E_NOT_OK;
            }
        }
    }
    return retVal_u8;
}
#endif
/**
 **************************************************************************************************
 * Dcm_DDDI_Ini : Initialisation function for DDDI Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC (void,DCM_CODE) Dcm_DDDI_Ini (void)
{
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED == DCM_CFG_OFF)
    VAR (uint32,AUTOMATIC) idxLoop_u32;
    /* Get the number of DDDIs/PDIs configured */
    VAR (uint16,AUTOMATIC) dataSize_u16= Dcm_DddiCalculateTableSize_u16 ();
    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
#endif

    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) NegResCode_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataCondChkRetVal_u8;

    dataCondChkRetVal_u8 = E_OK;
    NegResCode_u8 = 0x0;

    if((Dcm_DspDddidOpStatus_u8 == DCM_PENDING) && (Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETSUPPORT))
    {
        if(((Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16 >0u) && (Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32 >0x00u))&&
                ((Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrCondChkRdFnc_cpv)!= NULL_PTR)&&
                ((Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) ||
                        (Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_ASYNCH_FNC)))
        {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].adrCondChkRdFnc_cpv))(DCM_CANCEL, &NegResCode_u8);
        }
    }
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
    if((Dcm_DspDddidOpStatus_u8 == DCM_PENDING)&&(Dcm_DspStDddi_en == DCM_DDDI_SENDRESP))
    {
        /* canceling the operation of storing/clearing */
        (void)DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR,
                s_ActiveDDDI_u16,
                DCM_CANCEL,
                s_isWriteOrClear_en);
    }
    /* clearing the DDDID */
    s_ActiveDDDI_u16 = 0;
#else
    for (idxLoop_u32=0; idxLoop_u32<dataSize_u16;idxLoop_u32++)
    {
        /* Clearing the definition of all the DDDIs/PDIs configured */
        stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDDDIRecordContext_pst;
        Dcm_DddiResetCompleteContext (stContext_st);
        stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataPDIRecordContext_pst;
        Dcm_DddiResetCompleteContext (stContext_st);
    }
#endif
    /* Set DDDI state machine to DCM_DDDI_IDLE */
    Dcm_DspStDddi_en  = DCM_DDDI_IDLE;

    /* Set the state machine for functions Dcm_DcmDddiAddIdRecords_u8 and Dcm_DcmDddiAddMemRecords_u8 to init status */
    Dcm_stAddIdRecords_en  = DCM_DDDI_DEFINE_BY_ID_INIT;
    Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
    /* Reset the Signal idxIndex_u16 */
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxSrcDidIndexType_st);      /*This function is invoked to reset all the elements of DID index structure to its default value*/

    (void)dataCondChkRetVal_u8;
    (void)NegResCode_u8;
}


/**
 **************************************************************************************************
 * Dcm_DcmDynamicalDefineDataIdentifier :
 *
 * UDS service for definition of DynamicalDefinedID.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDDDI (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (uint8, AUTOMATIC) dataSubFunction_u8;  /* static variable for storing the subfunction */
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
    static VAR (uint16, AUTOMATIC) s_idxIndexForStore_u16;  /* static varaible to store the index of the active DDDID for storing in NvM */
    VAR (Std_ReturnType, AUTOMATIC) dataRetValFromNvMStorage_u8;  /* Local variable to store the return value from the NvM storage/Clear */
#endif
    VAR (uint16,AUTOMATIC) idxIndex_u16;
    VAR (uint32,AUTOMATIC) idxLoop_u32; /* Local variable to loop through the DDDIs configured */
    VAR(Std_ReturnType, AUTOMATIC) dataRetVal_u8;
    /* Initialisation of local variables */
    *dataNegRespCode_u8             = 0;
    idxIndex_u16 = 0;
    dataRetVal_u8=DCM_E_PENDING;

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    if(OpStatus == DCM_CANCEL)
    {
        /* If OpStatus is set to DCM_CANCEL , then invoke the Ini function from the service */
        Dcm_DDDI_Ini();
        /* Return E_OK as Ini function will always be serviced */
        dataRetVal_u8 = E_OK;
    }
    else
    {
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
    dataRetValFromNvMStorage_u8 = E_OK;
#endif
        if (Dcm_DspStDddi_en==DCM_DDDI_IDLE)
        {
            /* Get the subfunction byte from the request */
            dataSubFunction_u8=pMsgContext->reqData[0];

            /* If sub-function is clearDynamicallyDefinedDataIdentifier (0x03) */
            if (dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER)
            {
#if( DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                VAR (uint32,AUTOMATIC) idxRdpi_u32; /* Local variable to loop through the DDDIs configured */
#endif
                /* Check for request length of 1 byte , idxLoop_u32.e, only sub-function byte is present in request */
                /* No identifier provided in the request for sub-function 0x03 means to clear all the DDDIs defined */
                if (pMsgContext->reqDataLen == DCM_DDDI_MIN_LENGTH)
                {
                    /* Get the total number of DDDIs configured */
                    VAR (uint16,AUTOMATIC) nrIds_u16 = Dcm_DddiCalculateTableSize_u16 ();
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* Looping through the DDDIs */
                    for (idxLoop_u32=0; idxLoop_u32<nrIds_u16;idxLoop_u32++)
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
                        *dataNegRespCode_u8 =0x00;
                        if(Dcm_isDDDIDSupported(Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16)!=E_OK)
                        {
                            /* Set negative response code */
                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                            /* Report development error "DCM_E_DDDI_NOT_CONFIGURED " to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                        }
                        if(*dataNegRespCode_u8 ==0x00)
#endif
                        {
                            P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDDDIRecordContext_pst;
                            /* Resetting the definition of DIDs for the DDDI */
                            Dcm_DddiResetCompleteContext (stContext_st);
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataPDIRecordContext_pst;
                            /* Resetting the definition of DIDs for the PDI */
                            Dcm_DddiResetCompleteContext (stContext_st);
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                            for(idxRdpi_u32=0;idxRdpi_u32<DCM_CFG_MAX_DID_SCHEDULER;idxRdpi_u32++)
                            {
                                if(Dcm_PeriodicInfo_st[idxRdpi_u32].dataId_u16==Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16)
                                {
                                    Dcm_PeriodicInfo_st[idxRdpi_u32].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                                    Dcm_NumOfActivePeriodicId_u8--;
                                }
                            }
#endif
                        }
                    }
                    /* Change the state to Send Response*/
                    Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                }
                /* If the tester request is to clear the DDDI provided in the request */
                /* Checking if the request length is 3 bytes(subfunction and DDDI(2 bytes)) */
                else if ((pMsgContext->reqDataLen) == (DCM_DDDI_MIN_LENGTH + 2u))
                {
                    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                    VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                    /* Get the DDDI from the request */
                    VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                    dataDid_u16  <<=  8u;
                    dataDid_u16   |= (uint16)pMsgContext->reqData[2];

                    /* Get the idxIndex_u16 of the  DDDI in request */
                    dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);
                    /* If the DDDI is configured and idxIndex_u16 is obtained */
                    if (dataFuncRetVal_u8==E_OK)
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                        if(Dcm_isDDDIDSupported(dataDid_u16)!=E_OK)
                        {
                            /* Set negative response code */
                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                            /* Report development error "DCM_E_DDDI_NOT_CONFIGURED " to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                        }
#endif
                        if(*dataNegRespCode_u8==0x00)
                        {
                            /* updating the active DDDI */
                            s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;
                            /* Clear the definition of the DDDI */
                            Dcm_DddiResetCompleteContext (stContext_st);
                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;
                            /* Clear the definition of the PDI */
                            Dcm_DddiResetCompleteContext (stContext_st);
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
                            for(idxRdpi_u32=0;idxRdpi_u32<DCM_CFG_MAX_DID_SCHEDULER;idxRdpi_u32++)
                            {
                                if(Dcm_PeriodicInfo_st[idxRdpi_u32].dataId_u16==Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16)
                                {
                                    Dcm_PeriodicInfo_st[idxRdpi_u32].dataOverflowValue_en=DCM_RDPI_NO_TRANMISSION;
                                    Dcm_NumOfActivePeriodicId_u8--;
                                }
                            }
#endif
                            /* Change the state to Send Response*/
                            Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                        }
                    }
                    /* If DDDI is not configured */
                    else
                    {
                        /* Set negative response code */
                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                        /* Report development error "DCM_E_DDDI_NOT_CONFIGURED " to DET module if the DET module is enabled */
                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED )
                    }
                }
                /* If the request length is incorrect */
                else
                {
                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }
            /* If sub-function is defineByIdentifier (0x01) */
            else if (dataSubFunction_u8==DCM_DEFINITION_BY_ID)
            {
                /* Calculate request length excluding sub-function and DDDI(2 bytes) */
                VAR (uint32,AUTOMATIC) dataReqMsgLen_u32=((uint32)pMsgContext->reqDataLen)-3uL;
                /* Check if request length calculated is greater than 0 and divisible by 4.4 is the number of bytes of  */
                /* information present in the request for each source identifier which includes sourceDataIdentifier    */
                /* (2 bytes), posnInSourceDataRecord_u8(1 byte) and dataMemorySize_u8(1 byte).                                */
                if ((dataReqMsgLen_u32>0u) && ((dataReqMsgLen_u32 % 4u)==0u))
                {
                    VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8; /* Local variable to store the return value of function */
                    /* Get the DDDI from the request */
                    VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                    dataDid_u16  <<=  8u;
                    dataDid_u16   |= (uint16)pMsgContext->reqData[2];
                    /* Call the sub function to get the idxIndex_u16 of DDDI in the configuration table */
                    dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);
                    /* If the DDDI is supported and the idxIndex_u16 is obtained correctly */
                    if (dataFuncRetVal_u8==E_OK)
                    {
                        VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st; /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
                        /* Call the function to get the idxIndex_u16 of the DID from Dcm_DIDConfig*/
                        dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&idxsrcDidIndexType_st);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                        /* Check if the DID is supported in current variant */

                        if((dataFuncRetVal_u8 == E_OK) && (idxsrcDidIndexType_st.dataRange_b == FALSE) && (*Dcm_DIDIsAvail[Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                        {
                            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                            {
                                dataFuncRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif
                        if(dataFuncRetVal_u8==E_OK)
                        {
                            /* If the DDDI is supported in current session and the idxIndex_u16 is obtained correctly */
                            if (((Dcm_DsldGetActiveSessionMask_u32() & \
                                    (Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32))!= 0x00uL))
                            {
                                /* If the DDDI is supported in current security level */
                                if((Dcm_DsldGetActiveSecurityMask_u32()& \
                                        (Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSecRead_u32))!=0x00uL)
                                {
                                    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                                    P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst =Dcm_DDDIBaseConfig_cast[idxIndex_u16].addrRecord_pst;
                                    /* Get the number of records in the request by dividing the length by 4 (block size) */
                                    VAR (uint16,AUTOMATIC) nrBlocks_u16=(uint16)(dataReqMsgLen_u32/4uL);
                                    stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;
                                    /* If the number of records already defined for the DDDI + number of records in the request
                                       exceeds total number of records allowed for the DDDI */
                                    if ((nrBlocks_u16+(stContext_st->nrCurrentlyDefinedRecords_u16)) <=
                                            Dcm_DDDIBaseConfig_cast[idxIndex_u16].nrMaxNumOfRecords_u16)
                                    {
                                        /* Pointer pointing to the source identifier of the first block */
                                        P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8=&pMsgContext->reqData[3];
                                        /* updating the active DDDI */
                                        s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                                        /* store the index for future use in case the storing of DDDID returns Pending */
                                        s_idxIndexForStore_u16 = idxIndex_u16;
#endif
                                        /* Call the function to add the records in the request to the definition of the DDDI */
                                        dataFuncRetVal_u8=Dcm_DcmDddiAddIdRecords_u8(nrBlocks_u16,stContext_st->nrCurrentlyDefinedRecords_u16,
                                                adrSourceBuffer_pcu8,adrRecord_pst,dataNegRespCode_u8,idxIndex_u16,(pMsgContext->resMaxDataLen-2u));
                                        /* If the records are successfully added */
                                        if (dataFuncRetVal_u8==E_OK)
                                        {
                                            /* Update the number of currently defined records for the DDDI and PDI */
                                            stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);
                                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;
                                            stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);

                                            Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                                            /* Change the state to Send Response*/
                                            Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                                        }
                                        else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                                        {
                                            /* wait and come back to the service */
                                            Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                                        }
                                        /* If any record is not added to the DDDI definition successfully */
                                        else
                                        {
                                            /* Negative response code already set within function Dcm_DcmDddiAddIdRecords_u8 */
                                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                            Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                                        }
                                    }
                                    /* If the total number of records defined for DDDI exceeds the maximum number allowed */
                                    else
                                    {
                                        /* Set negative response code */
                                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                        /* Report development error "DCM_E_EXCEEDED_MAX_RECORDS " to DET module if the DET module is enabled */
                                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_EXCEEDED_MAX_RECORDS )
                                    }
                                }
                                /*IF Security access failed for defining the DDDI*/
                                else
                                {
                                    /* Set negative response code */
                                    *dataNegRespCode_u8      = DCM_E_SECURITYACCESSDENIED;
                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                }
                            }
                            /*If DDDI is not supported in current active session*/
                            else
                            {
                                /* Set negative response code */
                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                /* Report development error "DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION " to DET module if the DET module is enabled */
                                DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION )
                            }
                        }
                        /*If DDDI is not supported in current variant */
                        else
                        {
                            /* Set negative response code */
                            *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                            /* Report development error "DCM_E_DDDI_NOT_CONFIGURED " to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_DDDI_NOT_CONFIGURED)
                        }
                    }
                    /* If the DDDI is not supported */
                    else
                    {
                        /* Set negative response code */
                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                    }
                }
                else
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }
            /* If subfunction is defineByMemoryAddress (0x02) */
            else if (dataSubFunction_u8==DCM_DEFINITION_BY_MEMORYADDRESS)
            {
                /* Check for minimum request length (Subfunction(1 byte,DDDI(2 bytes),dataAdrAndLenFormatIdentifier_u8
                   (1 byte),memoryAddress(at least 1 byte) and dataMemorySize_u8 (at least 1 byte) */
                if (pMsgContext->reqDataLen>=DCM_DDDI_MEMADDR_MINLEN)
                {
                    /* Get the dataAdrAndLenFormatIdentifier_u8 from the request */
                    VAR (uint8,AUTOMATIC) dataAdrAndLenFormatIdentifier_u8 = pMsgContext->reqData[3];

                    /* Calculate number of bytes assigned for address in request from dataAdrAndLenFormatIdentifier_u8 */
                    VAR (uint8,AUTOMATIC) nrBytesForAddress_u8 = dataAdrAndLenFormatIdentifier_u8 & 0x0Fu;

                    /* Calculate number of bytes assigned for length in request from dataAdrAndLenFormatIdentifier_u8 */
                    VAR (uint8,AUTOMATIC) nrBytesForLength_u8 = (dataAdrAndLenFormatIdentifier_u8>>4u);

                    /* Calculate the block length */
                    VAR (uint8,AUTOMATIC) dataBlockLen_u8 = nrBytesForAddress_u8 + nrBytesForLength_u8;

                    /* Calculate the request length excluding  subfunction , DDDI and dataAdrAndLenFormatIdentifier_u8 */
                    VAR (uint16,AUTOMATIC) dataReqMsgLen_u16 = (uint16)(pMsgContext->reqDataLen-4u);

                    /* If  dataAdrAndLenFormatIdentifier_u8 in request is invalid*/
                    if (( nrBytesForAddress_u8 == 0 ) || ( nrBytesForLength_u8 == 0 ) || ( nrBytesForAddress_u8 > 4 ) || ( nrBytesForLength_u8 > 4))
                    {
                        /* Set negative response code */
                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                        /* Report development error "DCM_E_INVALID_ADDRLENGTH_FORMAT " to DET module if the DET module is enabled */
                        DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_INVALID_ADDRLENGTH_FORMAT )
                    }
                    /* If dataAdrAndLenFormatIdentifier_u8 in request is valid */
                    else
                    {
                        /* If the calculated request length has no extra bytes of data */
                        if ((dataReqMsgLen_u16%dataBlockLen_u8)==0)
                        {
                            /* Local variable to store the return value of function Dcm_DspGetIndexOfDDDI_u8 */
                            VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;

                            /* Get the DDDI from the request */
                            VAR (uint16,AUTOMATIC) dataDid_u16 = (uint16)pMsgContext->reqData[1];
                            dataDid_u16  <<=  8u;
                            dataDid_u16   |= (uint16)pMsgContext->reqData[2];

                            /* Call the function to get the idxIndex_u16 of DDDI in the configuration table */
                            dataFuncRetVal_u8 = Dcm_DspGetIndexOfDDDI_u8 (dataDid_u16,&idxIndex_u16);
                            /* If the DDDI is supported and the idxIndex_u16 is obtained correctly */
                            if (dataFuncRetVal_u8==E_OK)
                            {
                                VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxDidIndexType_st;    /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
                                /* Call the function to get the idxIndex_u16 of the DID from Dcm_DIDConfig*/
                                dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&idxDidIndexType_st);
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                                /* Check if the DID is supported in current variant */
                                if((dataFuncRetVal_u8 == E_OK) && (idxDidIndexType_st.dataRange_b ==FALSE)&& (*Dcm_DIDIsAvail[Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                                {
                                    if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                                    {
                                        dataFuncRetVal_u8 = E_NOT_OK;
                                    }
                                }
#endif
                                if(dataFuncRetVal_u8==E_OK)
                                {
                                    /* If the DDDI is supported in current session and the idxIndex_u16 is obtained correctly */
                                    if (((Dcm_DsldGetActiveSessionMask_u32() & \
                                            (Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSessRead_u32))!= 0x00uL))
                                    {
                                        /* If the DDDI is supported in current security level */
                                        if((Dcm_DsldGetActiveSecurityMask_u32()& \
                                                (Dcm_DIDConfig[idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst->dataAllowedSecRead_u32))!=0x00uL)
                                        {
                                            P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) stContext_st;
                                            P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst =
                                                    Dcm_DDDIBaseConfig_cast[idxIndex_u16].addrRecord_pst;

                                            /* Calculate the number of blocks in the request */
                                            VAR (uint16,AUTOMATIC) nrBlocks_u16 = (uint16)(dataReqMsgLen_u16/dataBlockLen_u8);

                                            stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDDDIRecordContext_pst;
                                            /* If the number of records already defined for the DDDI + number of records in the request
                                               exceeds total number of records allowed for the DDDI */
                                            if ((nrBlocks_u16+(stContext_st->nrCurrentlyDefinedRecords_u16)) <=
                                                    Dcm_DDDIBaseConfig_cast[idxIndex_u16].nrMaxNumOfRecords_u16)
                                            {
                                                P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8 = &pMsgContext->reqData[4];
                                                    /* updating the active DDDI */
                                                    s_ActiveDDDI_u16 = Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16;
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                                                    /* store the index for future use in case the storing of DDDID returns Pending */
                                                    s_idxIndexForStore_u16 = idxIndex_u16;
#endif
                                                /* Call the function to add the record to the current definition of the DDDI */
                                                dataFuncRetVal_u8=Dcm_DcmDddiAddMemRecords_u8(nrBlocks_u16,stContext_st->nrCurrentlyDefinedRecords_u16,
                                                        adrSourceBuffer_pcu8,adrRecord_pst,dataNegRespCode_u8, nrBytesForAddress_u8,nrBytesForLength_u8,
                                                        idxIndex_u16,(pMsgContext->resMaxDataLen-2u));
                                                /* If all records are successfully added to the definition of the DDDI */
                                                if (dataFuncRetVal_u8==E_OK)
                                                {
                                                    /* Update number of currently defined records for the DDDI/PDI */
                                                    stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);
                                                    stContext_st=Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataPDIRecordContext_pst;
                                                    stContext_st->nrCurrentlyDefinedRecords_u16 = (uint16)(stContext_st->nrCurrentlyDefinedRecords_u16 + nrBlocks_u16);

                                                    /* Change the state to Send Response*/
                                                    Dcm_DspStDddi_en = DCM_DDDI_SENDRESP;
                                                }
                                                else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                                                {
                                                    /* wait and come back to the service */
                                                }
                                                /* If any record is not added to the DDDI definition successfully */
                                                else
                                                {
                                                    /* Negative response code already set within function Dcm_DcmDddiAddMemRecords_u8 */
                                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                                }
                                            }
                                            /* If the total number of records defined for DDDI exceeds the maximum number allowed */
                                            else
                                            {
                                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                            }
                                        }
                                        /*IF DDDI is not supported in the current active security level*/
                                        else
                                        {
                                            *dataNegRespCode_u8      = DCM_E_SECURITYACCESSDENIED;
                                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                        }
                                    }
                                    /*If DDDI is not supported in current active session*/
                                    else
                                    {
                                        *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                        Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                    }
                                }
                                else
                                {
                                    *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                                }
                            }
                            /* If the DDDI/PDI is not supported */
                            else
                            {
                                *dataNegRespCode_u8      = DCM_E_REQUESTOUTOFRANGE;
                                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                            }
                        }
                        /* For incorrect request length for subfunction 0x02 */
                        else
                        {
                            *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                            Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                        }
                    }
                }
                /* If the request length is less than the minimum request length for the subfunction */
                else
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8      = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                    Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
                }
            }
            /* If the subfunction in the request is invalid */
            else
            {
                /* Set negative response code */
                *dataNegRespCode_u8      = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                Dcm_DspStDddi_en = DCM_DDDI_NEGRESP;
            }
        }

        /* if storing of DDDIDs is enabled, then call the application accordingly. Otherwise, just trigger Dcm_ProcessingDone call */
        if(Dcm_DspStDddi_en == DCM_DDDI_SENDRESP)
        {
            dataSubFunction_u8=pMsgContext->reqData[0];
            if((dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER) && (pMsgContext->reqDataLen == DCM_DDDI_MIN_LENGTH))
            {
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                s_isWriteOrClear_en = DCM_DDDI_CLEARALL;
                /* calling the application to store the DDDI definition in NvM. In this case, stored DDDIDs in NvM shall be cleared by the application */
                dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR,
                        0,
                        Dcm_DspDddidOpStatus_u8,
                        s_isWriteOrClear_en);
                if(dataRetValFromNvMStorage_u8==DCM_E_PENDING)
                {
                    /* change the opstatus to PENDING */
                    Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataRetValFromNvMStorage_u8 != E_OK)
                {
                    /* Reporting the DET error */
                    DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NVM_UPDATION_NOT_OK )
                            /* clearing the opstatus for storing the DDDID in NvM */
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* clearing the DDDID */
                    s_ActiveDDDI_u16 = 0;
                    s_idxIndexForStore_u16 = 0;
                }
                else
                {
                    /**dummy else*/
                }
                if(dataRetValFromNvMStorage_u8!= DCM_E_PENDING)
                {
                    /* clearing the opstatus for storing the DDDID in NvM */
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* clearing the DDDID */
                    s_ActiveDDDI_u16 = 0;
                    s_idxIndexForStore_u16 = 0;
                    dataRetVal_u8 = E_OK;
                }
#endif
                if(Dcm_DspDddidOpStatus_u8 != DCM_PENDING)
                {
                    /* Copy the sub function byte from source buffer to target buffer */
                    pMsgContext->resData[0] = pMsgContext->reqData[0];

                    /* Set final response length */
                    pMsgContext->resDataLen =  1;
                    Dcm_DspStDddi_en = DCM_DDDI_IDLE;
                    dataRetVal_u8=E_OK;
                }
            }
            else
            {
#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
                if((dataSubFunction_u8==DCM_DDDI_CLEAR_DYNAMIC_IDENTIFIER) && (pMsgContext->reqDataLen == (DCM_DDDI_MIN_LENGTH + 2u)))
                {
                    s_isWriteOrClear_en = DCM_DDDI_CLEAR;
                    /* calling the application to store the DDDI definition in NvM. In this case, stored DDDIDs in NvM shall be cleared by the application */
                    dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(NULL_PTR,
                            s_ActiveDDDI_u16,
                            Dcm_DspDddidOpStatus_u8,
                            s_isWriteOrClear_en);
                }
                else if((dataSubFunction_u8==DCM_DEFINITION_BY_ID)||(dataSubFunction_u8==DCM_DEFINITION_BY_MEMORYADDRESS))
                {
                    s_isWriteOrClear_en = DCM_DDDI_WRITE;
                    /* calling the application to store the DDDI definition in NvM. In this case, DDDID shall be written into NvM */
                    dataRetValFromNvMStorage_u8 = DcmAppl_DcmWriteOrClearDddiInNvM(&Dcm_DDDIBaseConfig_cast[s_idxIndexForStore_u16],
                            s_ActiveDDDI_u16,
                            Dcm_DspDddidOpStatus_u8,
                            s_isWriteOrClear_en);
                }
                else
                {
                    /* dummy else */
                }
                if(dataRetValFromNvMStorage_u8==DCM_E_PENDING)
                {
                    /* change the opstatus to PENDING */
                    Dcm_DspDddidOpStatus_u8 = DCM_PENDING;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataRetValFromNvMStorage_u8 != E_OK)
                {
                    /* Reporting the DET error */
                    DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NVM_UPDATION_NOT_OK )
                   /* clearing the opstatus for storing the DDDID in NvM */
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* clearing the static variable */
                    s_idxIndexForStore_u16 = 0;
                    /* clearing the DDDID */
                    s_ActiveDDDI_u16 = 0;
                }
                else
                {
                    /*Dummy else**/
                }
                if(dataRetValFromNvMStorage_u8!= DCM_E_PENDING)
                {
                    /* clearing the static variable */
                    s_idxIndexForStore_u16 = 0;
                    /* clearing the opstatus for storing the DDDID in NvM */
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* clearing the DDDID */
                    s_ActiveDDDI_u16 = 0;
                    dataRetVal_u8=E_OK;
                }
#endif
                if( Dcm_DspDddidOpStatus_u8 != DCM_PENDING)
                {
                    /* Copy the sub-function byte and the DDDI from the source buffer to target buffer */
                    pMsgContext->resData[2] = pMsgContext->reqData[2];
                    pMsgContext->resData[1] = pMsgContext->reqData[1];
                    pMsgContext->resData[0] = pMsgContext->reqData[0];

                    /* Set final response length */
                    pMsgContext->resDataLen =  3;
                    /* reset the opstatus */
                    Dcm_DspDddidOpStatus_u8 = DCM_INITIAL;
                    /* reset the state of DDDID state machine */
                    Dcm_DspStDddi_en = DCM_DDDI_IDLE;
                    /* Send positive response */
                    dataRetVal_u8=E_OK;
                }

            }
        }

        /* If an error was encountered and negative response code is set*/
        if (Dcm_DspStDddi_en == DCM_DDDI_NEGRESP)
        {
            /* Update the state machine status to DCM_DDDI_IDLE */
            Dcm_DspStDddi_en = DCM_DDDI_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_DddiResetCompleteContext
 *  A processing context gets reset by call to this function including the definition for the DID
 *
 * \param           adrContext_pst The pointer to the Context to be reset
 *
 * \retval          None
 * \seealso         Dcm_DddiResetProcessingInfoInContext
 *
 **************************************************************************************************
 */

FUNC (void,DCM_CODE) Dcm_DddiResetCompleteContext(P2VAR(Dcm_DddiIdContext_tst, AUTOMATIC,DCM_INTERN_DATA) adrContext_pst)
{
    /* Reset the number of currently defined records ,current position in data buffer and current record idxIndex_u16 to 0 */
    adrContext_pst->nrCurrentlyDefinedRecords_u16=0;
    adrContext_pst->posnCurrentPosInDataBuffer_u16=0;
    adrContext_pst->idxCurrentRecord_u16=0;
}

/**
 **************************************************************************************************
 * Dcm_DddiResetProcessingInfoInContext:
 *
 * A processing context gets reset by call to this function with respect to the current processing status
 * only. The number of records defined in this context stays unchanged.
 *
 * \param           adrContext_pst The pointer to the Context to be reset
 *
 * \retval          None
 * \seealso         Dcm_DddiResetCompleteContext
 *
 **************************************************************************************************
 */

FUNC (void,DCM_CODE) Dcm_DddiResetProcessingInfoInContext (
        P2VAR(Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrPtrToContext_pst
)
{
    /* Reset the current position in data buffer and current record idxIndex_u16 to 0 */
    adrPtrToContext_pst->posnCurrentPosInDataBuffer_u16=0;
    adrPtrToContext_pst->idxCurrentRecord_u16=0;
}

/**
 **************************************************************************************************
 * Dcm_DddiReadById_u8:
 *
 * read data from an DDID as per the specification in a DynamicalDefinedID record
 *
 * \param     adrRecord_pst: The pointer to the Dcm_DddiDefId_tst specifies from which DID this function shall
 *                    read how many bytes using which offset
 *            adrLength_pu16: The reference in which to tell the calling function how many bytes were filled in.
 *            adrData_pu8: The pointer to RAM were to put the memory content
 *
 * \retval    E_OK:      in case of success
 *            DCM_E_PENDING: in case of more time is required and the function needs to be called again
 *            E_NOT_OK:  in case the DDID could not be read
 * \seealso   DcmAppl_DDDI_Read_Memory
 *
 **************************************************************************************************
 */


FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiReadById_u8 (P2CONST (Dcm_DddiDefId_tst,AUTOMATIC,DCM_INTERN_CONST) adrRecord_pst,
        P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) adrLength_pu16,
        P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8)
{
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    VAR (Std_ReturnType, AUTOMATIC)  dataReadIfcRetVal_u8; /* Local variable to store the return value of Read function */
#if(DCM_CFG_DSP_DIDBUFFER == DCM_STACK_BUFFER)
    VAR (uint8,AUTOMATIC) Dcm_DspDidBuffer_au8[DCM_CFG_LONGESTSINGLEDID]; /* Temporary buffer to store data of record */
#else
    static VAR (uint8,AUTOMATIC) Dcm_DspDidBuffer_au8[DCM_CFG_LONGESTSINGLEDID];
#endif
    /*If Current Did Range Status is valid or not*/
    if(FALSE == adrRecord_pst->stCurrentDidRangeStatus_b)
    {
        s_Dcm_idxSrcDidIndexType_st.idxIndex_u16 = adrRecord_pst->idxOfDid_u16;
        /*data range of did is set to value FALSE*/
        s_Dcm_idxSrcDidIndexType_st.dataRange_b = FALSE;

        dataReadIfcRetVal_u8 = Dcm_GetDIDData(&s_Dcm_idxSrcDidIndexType_st,Dcm_DspDidBuffer_au8);
    }
    else
    {
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
        s_Dcm_idxSrcDidIndexType_st.dataRangeDid_16 = adrRecord_pst->dataSrcDid_u16;
#endif
        /*Data range of Did is a range did*/
        s_Dcm_idxSrcDidIndexType_st.dataRange_b = TRUE;
        dataReadIfcRetVal_u8 = Dcm_GetDIDData(&s_Dcm_idxSrcDidIndexType_st,Dcm_DspDidBuffer_au8);
    }
    if(s_Dcm_idxSrcDidIndexType_st.dataNegRespCode_u8 == 0x00)
    {
        switch (dataReadIfcRetVal_u8)
        {
            /* IF data is read successfully */
            case (Std_ReturnType)E_OK:
                {
                /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
                DCM_MEMCOPY(adrData_pu8, &Dcm_DspDidBuffer_au8[adrRecord_pst->posnInSourceDataRecord_u8-1],adrRecord_pst->dataMemorySize_u8);
                /* Updating the length with the current record length */
                *adrLength_pu16 = adrRecord_pst->dataMemorySize_u8;
                s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;   /*All the signals read correctly, therefore reset it to zero*/
                s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0; /*All the signals read correctly, therefore reset the signal data length to zero*/
                dataRetVal_u8 = E_OK;
                }
            break;
            case (Std_ReturnType)DCM_E_PENDING:
                    dataRetVal_u8 = DCM_E_PENDING;
            break;
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
            case (Std_ReturnType)DCM_E_REQUEST_ENV_NOK:
                    s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;   /*All the signals not read correctly, therefore reset it to zero*/
            s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0; /*All the signals read correctly, therefore reset the signal data length to zero*/
            dataRetVal_u8 = DCM_E_REQUEST_ENV_NOK;
            break;
#endif
            /*If data is not read successfully*/
            case (Std_ReturnType)E_NOT_OK:
            default:
                s_Dcm_idxSrcDidIndexType_st.nrNumofSignalsRead_u16 = 0x0;   /*All the signals not read correctly, therefore reset it to zero*/
                s_Dcm_idxSrcDidIndexType_st.dataSignalLengthInfo_u32 = 0x0; /*All the signals read correctly, therefore reset the signal data length to zero*/
                dataRetVal_u8 = E_NOT_OK;
                break;
        }
    }
    else
    {
        dataRetVal_u8 = E_NOT_OK;
    }
    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_DddiRead_u8:
 *
 * Read data from the complete DDID as per the specification in the array of DynamicalDefinedID records passed
 * as an argument. The status of the processing in this function is stored in the one of the contexts of the
 * DID; one for readDataByIdentifier Service and one for ReadDataByPeriodicDataIdentifier.
 *
 * \param    adrConfig_pcst:       Reference to the records for which the processing shall be performed
 *           adrData_pu8:     The pointer to the message buffer were the DID shall be written to.
 *
 * \retval   E_OK:      in case of success
 *           DCM_E_PENDING: in case of more time is required and the function needs to be called again
 *           E_NOT_OK:  in case the DDID could not be read
 * \seealso
 *
 **************************************************************************************************
 */


FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiRead_u8 (P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst,
        P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8,
        P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Local variable to store return value of function */
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8=E_OK;

    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;
    /* if periodic scheduler is running */
    /* MR12 RULE 14.4 VIOLATION: Controlling expression is not 'essentially Boolean' expression. MISRA C:2012 Rule-14.4*/
    if (Dcm_PeriodicSchedulerRunning_b)
    {
        adrContext_pst = adrConfig_pcst->dataPDIRecordContext_pst;
    }
    else
    {
        adrContext_pst = adrConfig_pcst->dataDDDIRecordContext_pst;
    }
    if(adrContext_pst->nrCurrentlyDefinedRecords_u16>0)
    {
        /* Looping through the defined records */
        while ((adrContext_pst->idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16) &&
                (dataRetVal_u8 == E_OK))
        {
            /* If the record has definition type as DCM_DEFINITION_BY_ID */
            if (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
            {
                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8; /* Local variable to store return value of API */
                VAR (uint16,AUTOMATIC) dataLength_u16; /* Local variable to store length of record */
                /* Call the function to read  the data corresponding to the record */
                dataFuncRetVal_u8 = Dcm_DddiReadById_u8 (&(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st),
                        &dataLength_u16,&adrData_pu8[adrContext_pst->posnCurrentPosInDataBuffer_u16]);
                /* If data is read successfully */
                if (dataFuncRetVal_u8 == E_OK)
                {
                    /* Update the current position of record in data buffer and record idxIndex_u16 */
                    adrContext_pst->posnCurrentPosInDataBuffer_u16 = (uint16)(adrContext_pst->posnCurrentPosInDataBuffer_u16 + dataLength_u16);
                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else if (dataFuncRetVal_u8 == E_NOT_OK)
                {
                    dataRetVal_u8=E_NOT_OK;
                    /* Call the function to reset the current position in data buffer and current record idxIndex_u16 to 0 */
                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
                else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                {
                    dataRetVal_u8=DCM_E_PENDING;
                }
#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
                else if (dataFuncRetVal_u8 == DCM_E_REQUEST_ENV_NOK)
                {
                    dataRetVal_u8=DCM_E_REQUEST_ENV_NOK;
                    /* Calling API to reset the current position in data buffer and current record idxIndex_u16 to 0 */
                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
#endif
                /* For any other return values */
                else
                {
                    dataRetVal_u8=E_NOT_OK;
                    /* Calling API to reset the current position in data buffer and current record idxIndex_u16 to 0 */
                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
            }
            /* If the record has definition type as DCM_DEFINITION_BY_MEMORYADDRESS */
            else if (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
            {
                VAR (Dcm_ReadMemoryRet_t,AUTOMATIC) dataFuncRetVal_en; /* Local variable to store return value of API */

                /* Call the API to read  the data corresponding to the record */
                dataFuncRetVal_en =DcmAppl_Dcm_ReadMemory (Dcm_DspDddidOpStatus_u8,0,
                        (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32),
                        (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32),
                        &adrData_pu8[adrContext_pst->posnCurrentPosInDataBuffer_u16],
                        dataNegRespCode_u8);

                if (dataFuncRetVal_en == DCM_READ_OK)
                {
                    *dataNegRespCode_u8 =0x00;
                    /* Update the current position of record in data buffer and record idxIndex_u16 */
                    adrContext_pst->posnCurrentPosInDataBuffer_u16 = (uint16)(adrContext_pst->posnCurrentPosInDataBuffer_u16 + adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32);
                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else if (dataFuncRetVal_en == DCM_READ_PENDING)
                {
                    *dataNegRespCode_u8 =0x00;
                    dataRetVal_u8=DCM_E_PENDING;
                }
                else if(dataFuncRetVal_en == DCM_READ_FORCE_RCRRP)
                {
                    *dataNegRespCode_u8 =0x00;
                    dataRetVal_u8=DCM_E_PENDING;
                    /* Trigger DSL/DSD to send NRC-78 forcefully */
                    (void)Dcm_ForceRespPend();
                }
                else
                {
                    dataRetVal_u8=E_NOT_OK;
                    if(*dataNegRespCode_u8 == 0x00)
                    {
                        *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                    }
                    /* Call the function to reset the current position in data buffer and current record idxIndex_u16 to 0 */
                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }

            }
            /* If definition type is invalid */
            else
            {
                dataRetVal_u8=E_NOT_OK;
                Dcm_DddiResetCompleteContext (adrContext_pst);
            }
        }
    }
    else
    {
        dataRetVal_u8 = E_NOT_OK;
    }
    if (dataRetVal_u8 == E_OK)
    {
        /* Call the function to reset the current position in data buffer and current record idxIndex_u16 to 0 */
        Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
    }
    return dataRetVal_u8;
}


/**
 **************************************************************************************************
 * Dcm_DspGetIndexOfDDDI_u8:
 *
 * Determine the idxIndex_u16 of the entry for the DID in the table Dcm_DDDIBaseConfig_cast.
 * Dcm_DDDIBaseConfig_cast holds all defined DIDs and PDID.
 * Dcm_DDDIBaseConfig_cast needs to be sorted by the field id.
 *
 * \param   dataDid_u16: The dataDid_u16 searched for
 *          idxIndex_u16: A reference to which the idxIndex_u16 is written in case of success.
 *
 * \retval   E_OK: The dataDid_u16 is configured and was found.The idxIndex_u16 is written to the argument idxIndex_u16 passed to this
 *           function
 *           DCM_E_REQUEST_NOT_ACCEPTED: The dataDid_u16 was not found. The argument idxIndex_u16 is not modified.
 * \seealso
 *
 **************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_DspGetIndexOfDDDI_u8 (VAR (uint16,AUTOMATIC) dataDid_u16,
        P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16)
{
    VAR (uint32,         AUTOMATIC) posnValue_u32;
    VAR (uint32,         AUTOMATIC) posnStart_u32;
    VAR (uint32,         AUTOMATIC) posnEnd_u32;
    VAR (uint32,         AUTOMATIC) dataSize_u32;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;            /* read interface return value */
    dataRetVal_u8=DCM_E_REQUEST_NOT_ACCEPTED;

    /* Storing the number of DDDIs configured */
    dataSize_u32 = Dcm_DddiCalculateTableSize_u16 ();
    posnStart_u32 = 0;
    posnEnd_u32 = dataSize_u32 -1u;
    posnValue_u32 = posnEnd_u32/2u;

    /* If First element is the matching local id */
    if (Dcm_DDDIBaseConfig_cast[posnStart_u32].dataDddId_u16 == dataDid_u16)
    {
        *idxIndex_u16=(uint16)posnStart_u32;
        dataRetVal_u8=E_OK;
    }
    /* If Last element is the matching local id */
    else if (Dcm_DDDIBaseConfig_cast[posnEnd_u32].dataDddId_u16 == dataDid_u16)
    {
        *idxIndex_u16=(uint16)posnEnd_u32;
        dataRetVal_u8=E_OK;
    }
    else
    {
        while (posnValue_u32 > 0u)
        {
            posnValue_u32 += posnStart_u32;
            if (Dcm_DDDIBaseConfig_cast[posnValue_u32].dataDddId_u16 == dataDid_u16)
            {
                *idxIndex_u16=(uint16)posnValue_u32;
                dataRetVal_u8=E_OK;
                break;
            }
            else if (Dcm_DDDIBaseConfig_cast[posnValue_u32].dataDddId_u16 > dataDid_u16)
            {
                posnEnd_u32 = posnValue_u32;
            }
            else
            {
                posnStart_u32 = posnValue_u32;
            }
            posnValue_u32 = (posnEnd_u32-posnStart_u32)/2u ;
        }
    }
    return (dataRetVal_u8);
}


/**
 **************************************************************************************************
 * Dcm_DcmDddiAddIdRecords_u8:
 *
 * Add DDDI-Records to the internal data structure which is evaluated on RDBI for DDDIs.  The function
 * evaluates one or more blocks from the request and checks the support and the availability of the IDs
 *
 * \param nrBlocks_u16: The number of blocks in the request. A block consists of the sourceDataIdentifier[],
 *                     posnInSourceDataRecord_u8 and dataMemorySize_u8
 *        nrCurrentlyDefinedRecords_u16: The number of blocks defined in this DDDI till now (to support appending)
 *        adrSourceBuffer_pcu8: Pointer to the message Buffer
 *        adrRecord_pst: Pointer to the DDDI's record
 *        dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                     an error in the request.
 *        idxIndex_u16 : Index of the DDDI in the DDDI configuration table
 *        nrResponseBufferLen_u32 : Maximum response buffer length available for the DDDI data for the current active protocol
 *
 * \retval    E_OK: Message was O.K. and the blocks (as defined in nrBlocks_u16 ) were successfully added to the record
 *            E_NOT_OK:  an error was detected and the Negative Response code was set by this function
 *            DCM_E_PENDING: in case of more time is required and the function needs to be called again
 * \seealso
 *
 **************************************************************************************************
 */



FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddIdRecords_u8 (VAR (uint16,AUTOMATIC)nrBlocks_u16,
        VAR (uint16,AUTOMATIC) nrCurrentlyDefinedRecords_u16,
        P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8,
        P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst,
        P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8,
        VAR (uint16,AUTOMATIC) idxIndex_u16,
        VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32)
{
    /* Local variable to store the return value of the function Dcm_DddiGetLen_u8 */
    VAR (Std_ReturnType,AUTOMATIC) dataRetValGetLen_u8;

    /* Local variable to store the return value of function */
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    VAR (boolean, AUTOMATIC) flgRdpi_b;
    static VAR (uint16,AUTOMATIC) Dcm_dataDID_u16;

    flgRdpi_b = FALSE ;            /* read interface return value */
    dataRetVal_u8        = E_OK;

    if (Dcm_stAddIdRecords_en==DCM_DDDI_DEFINE_BY_ID_INIT)
    {
        /* Initialize the idxIndex_u16 of current block to 0 */
        Dcm_AddIdCurrentBlockIndex_u16 = 0;
        Dcm_stAddIdRecords_en            = DCM_DDDI_DEFINE_BY_ID_GETINDEX;
        /* Initialize the current length of DDDI to 0 */
        Dcm_AddIdCurrentLength_u32     = 0;
        s_dataLength_u32 = 0;
        s_dataFunctionRetVal_u8 = E_OK;
        s_dataLengthFuncRetVal_u8 = E_OK;
    }

    /* Call the function to get the current length of records of the DDDI */
    dataRetValGetLen_u8=Dcm_DddiGetLen_u8 (&Dcm_DDDIBaseConfig_cast[idxIndex_u16], &Dcm_AddIdCurrentLength_u32);
    if(dataRetValGetLen_u8==E_OK)
    {
        /* Loop till all the records are added and no error occurs while adding the records to the DDDI definition */
        while ((Dcm_AddIdCurrentBlockIndex_u16<nrBlocks_u16) && (dataRetVal_u8==E_OK))
        {
            if (Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETINDEX)
            {
                /* Variable to store return value of function Dcm_GetIndexOfDID */
                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                VAR (uint16,        AUTOMATIC) dataDid_u16;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                VAR (uint16,        AUTOMATIC) idxLoop_u16;
#endif

                /* Get the DID(source identifier) of the current record */
                dataDid_u16=(uint16)((uint16)(((uint16)adrSourceBuffer_pcu8[Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH])<<8u)+
                        ((uint8)adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+1u]));
                Dcm_dataDID_u16=dataDid_u16;

                /* Check if the DDDI to be added is same as the source DDDI */
                /* If yes, then set the NRC to 0x31 */
                if(dataDid_u16 == Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16)
                {
                    *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                    dataRetVal_u8 = E_NOT_OK;
                }
                /* If the record to be added is not referring to the source DDDI*/
                else
                {
                    /* Call the function to get the idxIndex_u16 of the DID */
                    dataFuncRetVal_u8 = Dcm_GetIndexOfDID (dataDid_u16,&s_Dcm_idxSrcDidIndexType_st);
                    if(E_OK == dataFuncRetVal_u8 )
                    {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                        /* Check if the DID is supported in current variant */

                        if((s_Dcm_idxSrcDidIndexType_st.dataRange_b ==FALSE)&& (*Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                        {
                            if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(dataDid_u16)!=E_OK)
                            {
                                dataFuncRetVal_u8 = E_NOT_OK;
                            }
                        }
#endif

                        /*Check if the src DID to be added has use port of type USE_RDBI_PAGED_FNC, if yes reject the DID and send NRC0x31 for the same*/
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                        if(E_OK == dataFuncRetVal_u8 )
                        {
                            for(idxLoop_u16=0;idxLoop_u16<Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16;idxLoop_u16++)
                            {
                                if(Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[idxLoop_u16].idxDcmDspDatainfo_u16].usePort_u8 == USE_DATA_RDBI_PAGED_FNC)
                                {
                                    dataFuncRetVal_u8=E_NOT_OK;
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    break;
                                }
                            }
                        }
#endif
                    }

                    /* If the DID is supported */
                    if (dataFuncRetVal_u8==E_OK)
                    {
                        VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st; /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
                        /* Call the function to get the idxIndex_u16 of the DID from Dcm_DIDConfig*/
                        dataFuncRetVal_u8 = Dcm_GetIndexOfDID (Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16,&idxsrcDidIndexType_st);
                        if((dataFuncRetVal_u8 ==E_OK) &&  (((adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+3u])+ Dcm_AddIdCurrentLength_u32) <=  Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16))
                        {
                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_GETSUPPORT;
                        }
                        else
                        {
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8 = E_NOT_OK;
                        }
                    }
                    else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                    {
                        /*s_Dcm_idxSrcDidIndexType_st.dataopstatus_b=DCM_PENDING;*/
                        dataRetVal_u8 = DCM_E_PENDING;
                    }
                    /* If DID is not supported */
                    else
                    {
                        /* Set the negative response code and reset the state machine */
                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                        /*Check if flag Rdpi is set to FALSE*/
                        if(FALSE== flgRdpi_b)
                        {
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                        }

                        dataRetVal_u8               = E_NOT_OK;
                    }
                }
            }
            if (Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETSUPPORT)
            {
                VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_en;

                /* Call the function to check for support for the DID */
                dataSupportInfo_en=Dcm_GetSupportOfIndex (&s_Dcm_idxSrcDidIndexType_st,DCM_SUPPORT_READ,dataNegRespCode_u8);
                /* Critical: assumption is that we at least require the read access for possible later write access */
                switch (dataSupportInfo_en)
                {
                    case DCM_SUPPORT_OK:
                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_GETLENGTH;
                        s_dataLength_u32 = 0;
                        s_dataFunctionRetVal_u8 = E_OK;
                        s_dataLengthFuncRetVal_u8 = E_OK;
                        break;
                    case DCM_SUPPORT_SESSION_VIOLATED:
                    case DCM_SUPPORT_SECURITY_VIOLATED:
                    case DCM_SUPPORT_CONDITION_VIOLATED:
                        /* Negative Response code is already set by function Dcm_GetSupportOfIndex */
                        Dcm_stAddIdRecords_en=DCM_DDDI_DEFINE_BY_ID_INIT;
                        dataRetVal_u8=E_NOT_OK;
                        break;
                    case DCM_SUPPORT_CONDITION_PENDING:
                        /* Keep the status unchanged and get back to this function */
                        dataRetVal_u8=DCM_E_PENDING;
                        break;
                    default:
                        /* Reset the state and set the return value and negative response code */
                        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                        dataRetVal_u8               = E_NOT_OK;
                        *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                        break;
                }
            }
            if (Dcm_stAddIdRecords_en == DCM_DDDI_DEFINE_BY_ID_GETLENGTH)
            {
                if(((s_dataFunctionRetVal_u8==E_OK)&&(s_dataLengthFuncRetVal_u8==E_OK))||(s_dataFunctionRetVal_u8==DCM_E_PENDING))
                {

                    /* Call the function to get the length of the DID */
                    s_dataFunctionRetVal_u8 = Dcm_GetLengthOfDIDIndex (s_Dcm_idxSrcDidIndexType_st,&s_dataLength_u32,Dcm_dataDID_u16);

                }

                if (s_dataFunctionRetVal_u8==E_OK)
                {
                    /* Check if the length returned is less than the size configured for the DID */
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF )
                    /*If the did is a range did or not and Maximum size of the DID including Gaps is less than or equal to configured Did */
                    if(((s_dataLength_u32 <=  Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16) && (FALSE== s_Dcm_idxSrcDidIndexType_st.dataRange_b)) ||((s_dataLength_u32 <=  Dcm_DIDRangeConfig_cast[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16)&& (FALSE != s_Dcm_idxSrcDidIndexType_st.dataRange_b )))
#else
                        if ( s_dataLength_u32 <=  Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16 )
#endif
                        {
                            /* Get the posnInSourceDataRecord_u8 for the current record */
                            VAR (uint8,AUTOMATIC) posnInSourceDataRecord_u8=
                                    adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+2u];
                            /* Check if the posnInSourceDataRecord_u8 is zero */
                            /* Valid range for posnInSourceDataRecord_u8 starts at value 1 */
                            if (posnInSourceDataRecord_u8==0)
                            {
                                /* Reset the state machine and set the negative response code and the return value */
                                Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                dataRetVal_u8               = E_NOT_OK;
                            }
                            else
                            {
                                /* Get the memory size for the current record */
                                VAR (uint8,AUTOMATIC) dataMemorySize_u8=
                                        adrSourceBuffer_pcu8[(Dcm_AddIdCurrentBlockIndex_u16*DCM_DDDI_DEFINE_BY_ID_BLOCKLENGTH)+3u];
                                /* If memory size is greater than length of the DID or if the dataMemorySize_u8 bytes of data
                               from posnInSourceDataRecord_u8  exceeds actual number of bytes of data available */
                                if ((s_dataLength_u32+1u) >= (posnInSourceDataRecord_u8+dataMemorySize_u8))
                                {
                                    /* Error Indicator */
                                    /*Error Indicator flag value set to FALSE*/
                                    VAR(boolean,AUTOMATIC) flgErrorIndn_b = FALSE;
                                    /*Initialize the variable value to FALSE*/
                                    VAR(boolean,AUTOMATIC) flgValidDef_b = FALSE;
                                    VAR(uint16,AUTOMATIC) idxSignal1_u16;
                                    VAR(uint16,AUTOMATIC) idxSignal2_u16;
                                    if(FALSE== s_Dcm_idxSrcDidIndexType_st.dataRange_b)
                                    {
                                        /* Call the API to get the dynamic configuration of signals of the DID */
                                        s_dataLengthFuncRetVal_u8 = Dcm_GetDynamicSignalConfiguration(s_Dcm_idxSrcDidIndexType_st.idxIndex_u16);
                                        if(s_dataLengthFuncRetVal_u8 == E_OK)
                                        {
                                            /* Loop for all the signals configured for this DID */
                                            for(idxSignal1_u16=0; (idxSignal1_u16 < Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16)&&(flgErrorIndn_b==FALSE);idxSignal1_u16++)
                                            {   /* Check if the Position in the request is the Start position of the current signal */
                                                if((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32) ==((posnInSourceDataRecord_u8-(uint8)1u)*8u))
                                                {   /* Loop through all the signals */
                                                    for(idxSignal2_u16=idxSignal1_u16;(idxSignal2_u16<Dcm_DIDConfig[s_Dcm_idxSrcDidIndexType_st.idxIndex_u16].nrSig_u16)&&(flgErrorIndn_b==FALSE);
                                                            idxSignal2_u16++)
                                                    {   /* Check if the Size in the request ends at the Signal boundary */
                                                        if(((Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigPosnBit_u32) +
                                                                (Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigDataSize_u32)) ==
                                                                        (((posnInSourceDataRecord_u8-(uint8)1u) + dataMemorySize_u8)*8u))
                                                        {   /* Valid position and size */
                                                            /*Set the variable value to TRUE*/
                                                            flgValidDef_b = TRUE;
                                                            break;
                                                        }
                                                        else
                                                        {   /* Check if the size in the request is ending in the middle of the signal */
                                                            if(((Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigPosnBit_u32) +
                                                                    (Dcm_DynamicSignalConfig_cast[idxSignal2_u16].sigDataSize_u32)) >
                                                            ((((posnInSourceDataRecord_u8-(uint8)1u) + dataMemorySize_u8)*8u)))
                                                            {
                                                                /*Set the Error Indication flag value to TRUE*/
                                                                flgErrorIndn_b = TRUE;
                                                            }
                                                        }
                                                    }
                                                }

                                                else
                                                {   /* Check if the Position in the request is in between the signals and indication flag value to FALSE */
                                                    if(((((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32) < (((uint8)(posnInSourceDataRecord_u8-1)*8)))&& (((Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigPosnBit_u32)+Dcm_DynamicSignalConfig_cast[idxSignal1_u16].sigDataSize_u32)>(((uint8)(posnInSourceDataRecord_u8-1u)*8u)))))&& (flgValidDef_b == FALSE))
                                                    {
                                                        /*Set the Error Indication flag value to TRUE */
                                                        flgErrorIndn_b = TRUE;
                                                    }
                                                }
                                                /*Check if for Error Indication*/
                                                if(flgValidDef_b != FALSE)
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        /* For pending return value */
                                        else if(s_dataLengthFuncRetVal_u8 == DCM_E_PENDING)
										{
                                            /* Set the return value as E_PENDING and break out 0f the loop */
                                            dataRetVal_u8               = DCM_E_PENDING;

                                        }
                                        /* For any other return values */
                                        else
                                        {
                                            /* Set the negative response code, return value and reset the state machine for the function */
                                            *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                                            Dcm_stAddIdRecords_en       = DCM_DDDI_DEFINE_BY_ID_INIT;
                                            dataRetVal_u8               = E_NOT_OK;
                                        }
                                    }
                                    else
                                    {
                                        if(s_dataLength_u32 == (uint32)((posnInSourceDataRecord_u8-(uint8)1) + dataMemorySize_u8))
                                        {   /* Valid position and size */
                                            /* dummy if */

                                        }
                                        else
                                        {
                                            if(s_dataLength_u32 > (uint32)((posnInSourceDataRecord_u8-(uint8)1) + dataMemorySize_u8))
                                            {
                                                /*Error Indication flag is set*/
                                                flgErrorIndn_b = TRUE;
                                            }

                                        }
                                        s_dataLengthFuncRetVal_u8 = E_OK;
                                    }
                                    if(s_dataLengthFuncRetVal_u8 != DCM_E_PENDING)
                                    {
                                        if(flgErrorIndn_b == FALSE)
                                        {
                                            /* If current length of the DDDI + memory size is less than the size of longest single
                                           DID allowed and if entire DDDI definition will fit in response buffer during read */
                                            if((Dcm_AddIdCurrentLength_u32+dataMemorySize_u8) <= (uint16)nrResponseBufferLen_u32)
                                            {
                                                /* Update definition type,idxIndex_u16,position from where data is retrieved and size */
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDefinitionType_u8
                                                = DCM_DEFINITION_BY_ID;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataIdAccess_st.
                                                idxOfDid_u16 = s_Dcm_idxSrcDidIndexType_st.idxIndex_u16;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataIdAccess_st.
                                                posnInSourceDataRecord_u8 = posnInSourceDataRecord_u8;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.dataMemorySize_u8 =  dataMemorySize_u8;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.stCurrentDidRangeStatus_b =  s_Dcm_idxSrcDidIndexType_st.dataRange_b;
                                                adrRecord_pst[Dcm_AddIdCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.
                                                dataIdAccess_st.dataSrcDid_u16 =  Dcm_dataDID_u16;

                                                /* Increment the block idxIndex_u16 to get the next block in the request */
                                                Dcm_AddIdCurrentBlockIndex_u16++;
                                                /* Update the length of DDDI */
                                                Dcm_AddIdCurrentLength_u32 = (uint16)(Dcm_AddIdCurrentLength_u32 + dataMemorySize_u8);
                                                Dcm_stAddIdRecords_en         = DCM_DDDI_DEFINE_BY_ID_GETINDEX;
                                            }
                                            else
                                            {
                                                /* Set negative response code and reset state machine for the function */
                                                Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                                *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                                dataRetVal_u8               = E_NOT_OK;
                                            }
                                        }
                                        else
                                        {
                                            /* Set negative response code and reset state machine for the function */
                                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                            dataRetVal_u8               = E_NOT_OK;
                                        }
                                    }
                                }
                                else
                                {
                                    /* Set  negative response code and reset the state machine for the function */
                                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                                    *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                                    dataRetVal_u8               = E_NOT_OK;
                                }
                            }
                        }
                        else
                        {
                            /* Set  negative response code and reset the state machine for the function */
                            Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                            *dataNegRespCode_u8         = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8               = E_NOT_OK;
                        }
                }
                else if (s_dataFunctionRetVal_u8 == DCM_E_PENDING)
                {
                    /* Keep the status unchanged and get back to this function */
                    dataRetVal_u8=DCM_E_PENDING;
                }
                /* For any other return values */
                else
                {
                    /* Set the negative response code, return value and reset the state machine for the function */
                    *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
                    Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
                    dataRetVal_u8               = E_NOT_OK;
                }
            }
        }
    }
    /* If the current length is not obtained correctly */
    else
    {
        *dataNegRespCode_u8         = DCM_E_GENERALREJECT;
        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
        dataRetVal_u8               = E_NOT_OK;
    }
    if (dataRetVal_u8 == E_OK)
    {
        Dcm_stAddIdRecords_en = DCM_DDDI_DEFINE_BY_ID_INIT;
    }
    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_DcmDddiAddMemRecords_u8:
 *
 * Add DDDI-Records to the internal data structure which is evaluated on RDBI for DDDIs.  The function
 * evaluates one or more blocks from the request and checks the support and the availability of the memory
 *
 * \param nrBlocks_u16: The number of blocks in the request. A block consists of the memoryAddress and the
 *                     dataMemorySize_u8
 *        nrCurrentlyDefinedRecords_u16: The number of blocks defined in this DDDI till now (to support appending)
 *        adrSourceBuffer_pcu8: Pointer to the message Buffer
 *        adrRecord_pst: Pointer to the DDDI's record
 *        dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                     an error in the request.
 *        idxIndex_u16 : Index of the DDDI in the DDDI configuration table
 *        nrResponseBufferLen_u32 : Maximum response buffer length available for the DDDI data for the current active protocol
 *
 *
 * \retval    E_OK: Message was O.K. and the blocks (as defined in nrBlocks_u16) were successfully added to the record
 *            E_NOT_OK:  an error was detected and the Negative Response code was set by this function
 *            DCM_E_PENDING: in case of more time is required and the function needs to be called again
 * \seealso
 *
 **************************************************************************************************
 */


FUNC (Std_ReturnType,DCM_CODE) Dcm_DcmDddiAddMemRecords_u8 (VAR (uint16,AUTOMATIC)nrBlocks_u16,
        VAR (uint16,AUTOMATIC)nrCurrentlyDefinedRecords_u16,
        P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrSourceBuffer_pcu8,
        P2VAR (Dcm_DddiRecord_tst,AUTOMATIC,DCM_INTERN_DATA) adrRecord_pst,
        P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8,
        VAR (uint8,AUTOMATIC)nrBytesForAddress_u8,
        VAR (uint8,AUTOMATIC)nrBytesForLength_u8,
        VAR (uint16,AUTOMATIC) idxIndex_u16,
        VAR (Dcm_MsgLenType,AUTOMATIC) nrResponseBufferLen_u32)
{
    VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxsrcDidIndexType_st; /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8;        /* Variable to store the return value of the function */
    VAR (Std_ReturnType,AUTOMATIC) stGetMemAccess_u8;   /* Variable to store the return value of the function DcmAppl_DcmGetPermissionForMemoryAccess_u8*/
    VAR (Std_ReturnType,AUTOMATIC) dataRetValGetLen_u8; /* Variable to store the return value of the API Dcm_DddiGetLen_u8 */

    dataRetVal_u8        = E_OK;

    if (Dcm_stAddMemRecords_en==DCM_DDDI_DEFINE_BY_MEM_INIT)
    {
        Dcm_AddIdCurrentLength_u32     = 0;
        /* If the nrBytesForAddress_u8 or nrBytesForLength_u8 is invalid */
        if ((nrBytesForAddress_u8>4u) || (nrBytesForLength_u8>4u) || (nrBytesForAddress_u8==0) || (nrBytesForLength_u8==0))
        {
            /* Set negative response code */
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_u8       = E_NOT_OK;
        }
        else
        {
            /* Initialize the current block idxIndex_u16 to 0 */
            Dcm_AddMemCurrentBlockIndex_u16= 0;
            Dcm_stAddMemRecords_en           = DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT;
        }
    }
    /* Call the function to get the current length of the DDDI*/
    dataRetValGetLen_u8 = Dcm_DddiGetLen_u8 (&Dcm_DDDIBaseConfig_cast[idxIndex_u16], &Dcm_AddIdCurrentLength_u32);
    if(dataRetValGetLen_u8 == E_OK)
    {
        /* Loop till all records are added to DDDI definition successfully */
        while ((Dcm_AddMemCurrentBlockIndex_u16<nrBlocks_u16) &&(dataRetVal_u8==E_OK))
        {
            if (Dcm_stAddMemRecords_en == DCM_DDDI_DEFINE_BY_MEM_GETSUPPORT)
            {
                /* Variable to store return value of API DcmAppl_DDDI_Read_Memory_Condition */
                VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8;
                VAR (Dcm_DDDI_DEF_MEM_t,AUTOMATIC) dataMemRecord_st;
                VAR (uint32,AUTOMATIC) idxLoop_u32;
                P2CONST (uint8,AUTOMATIC,DCM_INTERN_CONST) adrInputBuffer_pcu8;
                VAR(boolean,AUTOMATIC) flgValidMemoryAccess_b;

                flgValidMemoryAccess_b = FALSE;
                dataMemRecord_st.adrDddiMem_u32   =0x00;
                dataMemRecord_st.dataMemLength_u32 =0x00;

                /* Calculate where to read the memory address and the length from. Keep in mind that after a pending
                message the function is left and entered again. In this case a simple usage of the adrSourceBuffer_pcu8
                would fail because it would get reset in the second call to this function.*/

                adrInputBuffer_pcu8=adrSourceBuffer_pcu8+ ((nrBytesForLength_u8+nrBytesForAddress_u8)*Dcm_AddMemCurrentBlockIndex_u16);
                /* Get the memory address of the record */
                for (idxLoop_u32=0;idxLoop_u32<nrBytesForAddress_u8;idxLoop_u32++)
                {
                    dataMemRecord_st.adrDddiMem_u32 = (dataMemRecord_st.adrDddiMem_u32<<8u)+(*adrInputBuffer_pcu8);

                    adrInputBuffer_pcu8++;
                }
                /* Get the length of data to be added to the definition of DDDI for the record */
                for (idxLoop_u32=0;idxLoop_u32<nrBytesForLength_u8;idxLoop_u32++)
                {
                    dataMemRecord_st.dataMemLength_u32 = ((dataMemRecord_st.dataMemLength_u32<<8u)+(*adrInputBuffer_pcu8));

                    adrInputBuffer_pcu8++;
                }

                /* Call the function to get the idxIndex_u16 of the DID from Dcm_DIDConfig*/
                dataFuncRetVal_u8 = Dcm_GetIndexOfDID (Dcm_DDDIBaseConfig_cast[idxIndex_u16].dataDddId_u16,&idxsrcDidIndexType_st);
                flgValidMemoryAccess_b = Dcm_DddiCheckOverflow(dataMemRecord_st.dataMemLength_u32,Dcm_AddIdCurrentLength_u32,Dcm_DIDConfig[idxsrcDidIndexType_st.idxIndex_u16].dataMaxDidLen_u16);
                if((dataFuncRetVal_u8 ==E_OK) &&  (flgValidMemoryAccess_b == TRUE))
                {
                    /* Call the API to check if it is permitted to read from the ECU memory as specified in request */
                    dataFuncRetVal_u8=DcmAppl_DDDI_Read_Memory_Condition (&dataMemRecord_st, dataNegRespCode_u8);
                    if (dataFuncRetVal_u8 == E_NOT_OK)
                    {
                        if(*dataNegRespCode_u8 ==0x00)
                        {
                            *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                        }
                        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                        dataRetVal_u8 = E_NOT_OK;
                    }
                    else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                    {
                        /* keep the status unchanged and get back to this function */
                        dataRetVal_u8 = DCM_E_PENDING;
                        *dataNegRespCode_u8          = 0;
                    }
                    else if (dataFuncRetVal_u8 == E_OK)
                    {
                        *dataNegRespCode_u8= 0;
                        /* The appl function to check the memory access permission*/
                        stGetMemAccess_u8=DcmAppl_DcmGetPermissionForMemoryAccess_u8(dataMemRecord_st.adrDddiMem_u32,dataMemRecord_st.dataMemLength_u32,DCM_SUPPORT_WRITE);
                        if(stGetMemAccess_u8 == E_OK)
                        {
                            /* If entire DDDI definition will fit in response buffer during a read */
                            if((Dcm_AddIdCurrentLength_u32+dataMemRecord_st.dataMemLength_u32) <= nrResponseBufferLen_u32)
                            {
                                /* Update definition type,memory address and length of data */
                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDefinitionType_u8
                                = DCM_DEFINITION_BY_MEMORYADDRESS;
                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32
                                = dataMemRecord_st.dataMemLength_u32;
                                adrRecord_pst[Dcm_AddMemCurrentBlockIndex_u16+nrCurrentlyDefinedRecords_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32
                                = dataMemRecord_st.adrDddiMem_u32;
                                Dcm_AddMemCurrentBlockIndex_u16++;
                                /* Update the length of the DDDI */
                                Dcm_AddIdCurrentLength_u32 = (uint16)(Dcm_AddIdCurrentLength_u32 + dataMemRecord_st.dataMemLength_u32);
                            }
                            else
                            {
                                /* Set the negative response code and reset the state machine for the function */
                                Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                                *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                                dataRetVal_u8                = E_NOT_OK;
                            }
                        }
                        else
                        {
                            /* Set the negative response code and reset the state machine for the function */
                            Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                            *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                            dataRetVal_u8                = E_NOT_OK;
                        }
                    }
                    /* For any other return values */
                    else
                    {
                        if(*dataNegRespCode_u8 == 0x00)
                        {
                            /* Set the negative response code, return value and reset the state machine for the function */
                            *dataNegRespCode_u8          = DCM_E_GENERALREJECT;
                        }
                        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                        dataRetVal_u8                = E_NOT_OK;
                    }
                }
                /* For any other return values */
                else
                {
                    /* Set the negative response code, return value and reset the state machine for the function */
                    *dataNegRespCode_u8          = DCM_E_REQUESTOUTOFRANGE;
                    Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
                    dataRetVal_u8                = E_NOT_OK;
                }
            }
        }
    }
    /* If the current length of DDDI is not obtained correctly */
    else
    {
        /* Set the negative response code, return value and reset the state machine for the function */
        *dataNegRespCode_u8          = DCM_E_GENERALREJECT;
        Dcm_stAddMemRecords_en = DCM_DDDI_DEFINE_BY_MEM_INIT;
        dataRetVal_u8                = E_NOT_OK;
    }
    if (dataRetVal_u8 == E_OK)
    {
        /* Reset the state machine for the function */
        Dcm_stAddMemRecords_en=DCM_DDDI_DEFINE_BY_MEM_INIT;
    }
    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 *   Dcm_DddiGetLen_u8:
 *
 * Calculate the length of an DDDI.
 * \param      *adrConfig_pcst       : pointer to the configuration of the DDDI in RAM of the ECU
 *             *uint16 adrLen_pu16: pointer to an uint16 in which the length of the DIDI is returned.
 * \retval        E_OK:  in case of success
 *            E_NOT_OK:  in case the internal memory structure was found to include invalid dataDddi_st.
 * \seealso
 *
 **************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiGetLen_u8 (P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst,
        P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA) adrLen_pu32)
{
    VAR (uint32,AUTOMATIC) idxCurrentRecord_u16 = 0; /* Variable to store current record idxIndex_u16 */
    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8 = E_OK;
    /* Initializing DDDI length to 0 */
    *adrLen_pu32=0;

    /* If periodic scheduler is running */
    /* MR12 RULE 14.4 VIOLATION: Controlling expression is not 'essentially Boolean' expression. MISRA C:2012 Rule-14.4 */
    if (Dcm_PeriodicSchedulerRunning_b)
    {
        adrContext_pst=adrConfig_pcst->dataPDIRecordContext_pst;
    }
    else
    {
        adrContext_pst=adrConfig_pcst->dataDDDIRecordContext_pst;
    }
    /* Looping through the records */
    for (; idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16; idxCurrentRecord_u16++)
    {
        /* If definition type is DCM_DEFINITION_BY_ID */
        if (adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
        {
            /* Variable to store length of the record */
            VAR (uint32,AUTOMATIC) dataLenOfThisRecord_u32=adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.dataMemorySize_u8;
            /* Updating the total length of DDDI */
            *adrLen_pu32 = *adrLen_pu32 + dataLenOfThisRecord_u32;
        }
        /* If definition type is DCM_DEFINITION_BY_MEMORYADDRESS */
        else if (adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
        {
            /* Variable to store length of the record */
            VAR (uint32,AUTOMATIC) dataLenOfThisRecord_u32 = adrConfig_pcst->addrRecord_pst[idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32;
            /* Updating the total length of DDDI */
            *adrLen_pu32 = (uint16)(*adrLen_pu32 + dataLenOfThisRecord_u32);
        }
        /* If definition type is invalid */
        else
        {
            dataRetVal_u8 = E_NOT_OK;
            Dcm_DddiResetCompleteContext (adrContext_pst);
            break;
        }
    }
    return dataRetVal_u8;
}


/**
 **************************************************************************************************
 * Dcm_DddiGetCondition_u8:
 *
 * Calculate if the DID is supported at this point in time or not.  Calculation is based on the context valid
 * at the point of the time of this function call. Context is either for periodic data processing or normal
 * processing based on the value of the global variable Dcm_PeriodicSchedulerRunning_b
 *
 * \param    *adrConfig_pcst       : pointer to the configuration of the DDDI in RAM of the ECU
 *              dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                           an error.
 * \retval           E_OK: ID is supported
 *               E_NOT_OK: An Error or negative result for the support of one of the included IDs or memory
 *                         blocks in this DID was detected during the calculation of the support of this ID
 *              DCM_E_PENDING: More time is required to calculate the support
 *
 * \seealso    Dcm_PeriodicSchedulerRunning_b
 *
 **************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_DddiGetCondition_u8(P2CONST (Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrConfig_pcst,
        P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (Std_ReturnType,AUTOMATIC) dataRetVal_u8=E_OK; /* Variable to store the return value */
    VAR (Std_ReturnType,   AUTOMATIC) stGetMemAccess_u8; /* Return value of Memory access check API */
    P2VAR (Dcm_DddiIdContext_tst,AUTOMATIC,DCM_INTERN_DATA) adrContext_pst;
    /* If periodic scheduler is running */
    /* MR12 RULE 14.4 VIOLATION: Controlling expression is not 'essentially Boolean' expression. MISRA C:2012 Rule-14.4 */
    if (Dcm_PeriodicSchedulerRunning_b)
    {
        adrContext_pst=adrConfig_pcst->dataPDIRecordContext_pst;
    }
    else
    {
        adrContext_pst=adrConfig_pcst->dataDDDIRecordContext_pst;
    }
    /* Looping through the records defined for the DDDI */
    while ((adrContext_pst->idxCurrentRecord_u16 < adrContext_pst->nrCurrentlyDefinedRecords_u16) &&
            (dataRetVal_u8 == E_OK))
    {
        /* If definition type of record is DCM_DEFINITION_BY_ID */
        if (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_ID)
        {
            VAR (Dcm_SupportRet_t, AUTOMATIC) dataSupportInfo_en;
            VAR (Dcm_DIDIndexType_tst,AUTOMATIC) idxDidCondIndexType_st;    /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
            /* Variable to store idxIndex_u16 of record in DID configuration table */
            idxDidCondIndexType_st.idxIndex_u16 = adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.idxOfDid_u16;
            idxDidCondIndexType_st.dataRange_b =  adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataIdAccess_st.stCurrentDidRangeStatus_b;
            idxDidCondIndexType_st.dataopstatus_b = Dcm_DspDataOpstatus_u8;

            /* Call the API to check support for DID */
            dataSupportInfo_en = Dcm_GetSupportOfIndex (&idxDidCondIndexType_st, DCM_SUPPORT_READ,dataNegRespCode_u8);

            if (dataSupportInfo_en == DCM_SUPPORT_OK)
            {
                Dcm_DspDataOpstatus_u8 = DCM_INITIAL;
                /* Increment the current idxIndex_u16 and proceed  */
                adrContext_pst->idxCurrentRecord_u16++;
            }
            else if (dataSupportInfo_en == DCM_SUPPORT_CONDITION_PENDING)
            {
                Dcm_DspDataOpstatus_u8 = DCM_PENDING;
                dataRetVal_u8 = DCM_E_PENDING;
            }
            else
            {
                Dcm_DspDataOpstatus_u8 = DCM_INITIAL;
                dataRetVal_u8 = E_NOT_OK;
                /* Call the function to reset the current position in data buffer and record idxIndex_u16 */
                Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
            }
        }
        /* If definition type of record is DCM_DEFINITION_BY_MEMORYADDRESS */
        else if (adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDefinitionType_u8 == DCM_DEFINITION_BY_MEMORYADDRESS)
        {
            VAR (Std_ReturnType,AUTOMATIC) dataFuncRetVal_u8; /* Variable to store the return value */
            /* Call the function to check support for DID */
            dataFuncRetVal_u8 = DcmAppl_DDDI_Read_Memory_Condition   (
                    &(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st),
                    dataNegRespCode_u8
            );
            if (dataFuncRetVal_u8 == E_OK)
            {
                *dataNegRespCode_u8=0x00;
                /* The appl function to check the memory access permission*/
                stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.adrDddiMem_u32,adrConfig_pcst->addrRecord_pst[adrContext_pst->idxCurrentRecord_u16].dataDddi_st.dataMemAccess_st.dataMemLength_u32,
                        DCM_SUPPORT_READ);
                if(stGetMemAccess_u8 == E_OK)
                {
                    /* Increment the current idxIndex_u16 and proceed  */
                    adrContext_pst->idxCurrentRecord_u16++;
                }
                else
                {
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    dataRetVal_u8=E_NOT_OK;
                    /* Call the function to reset the current position in data buffer and record idxIndex_u16 */
                    Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
                }
            }
            else if (dataFuncRetVal_u8 == DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;
                dataRetVal_u8 = DCM_E_PENDING;
            }
            else
            {
                if(*dataNegRespCode_u8 == 0x00)
                {
                    *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                }
                dataRetVal_u8=E_NOT_OK;
                /* Call the function to reset the current position in data buffer and record idxIndex_u16 */
                Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
            }
        }
        /* If definition type is invalid */
        else
        {
            dataRetVal_u8 = E_NOT_OK;
            Dcm_DddiResetCompleteContext (adrContext_pst);
        }
    }
    if (dataRetVal_u8 == E_OK)
    {
        Dcm_DddiResetProcessingInfoInContext (adrContext_pst);
    }
    return dataRetVal_u8;
}

/**
 *************************************************************************************************************************************************************
 * Dcm_GetActiveDDDIDid:
 *
 * This API returns the active DDDID being processed when RDBI service request is being processed. This function is called from the Dcm API Dcm_GetActiveDid
 *
 *
 * \param     uint16* dataDid_u16 : Parameter for updating of the DDDI under processing. The DDDI value returned is valid only if return value is E_OK.
 * \retval    Std_ReturnType : E_OK : The DDDI under processing is a normal DDDI.The parameter dataDid_u16 contains valid DDDI value in this case.
 *
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDDDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{
    /* Update the DDDID value currently under process */
    *dataDid_u16 = s_ActiveDDDI_u16;
    return (E_OK);
}


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
