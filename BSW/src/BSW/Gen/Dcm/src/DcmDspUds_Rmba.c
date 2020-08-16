

#include "DcmDspUds_Rmba_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Rmba_Priv.h"

/* Global varibale declaration */
#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"
static VAR(uint32,DCM_VAR) Dcm_dataMemoryAddress_u32; /*Variable to store the memory address requested by the tester*/
static VAR(uint32,DCM_VAR) Dcm_nrReadMemoryLength_u32; /*Variable to store the memory length requested by the tester*/
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.h"
static VAR(uint16,DCM_VAR) Dcm_idxDspRmba_u16; /* Variable to store the index of the Memory address in
                                                   Dcm_RMBAConfig_cast table */
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRmbaOpstatus_u8;
static VAR (uint8,  DCM_VAR) Dcm_dataMemdatasize_u8;                /* variable for storing the data record size*/
static VAR (uint8,  DCM_VAR) Dcm_dataMemaddrsize_u8;                /* variable for storing the memory address size*/
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_RMBAIni : Initialisation function for Read Memory By Address (0x23) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_RMBAIni (void)
{

    if(DCM_PENDING == Dcm_stRmbaOpstatus_u8 )
    {
        (void)(DcmAppl_Dcm_ReadMemory(DCM_CANCEL,Dcm_RMBAConfig_cast[Dcm_idxDspRmba_u16].dataMemoryValue_u8,
                                      Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,NULL_PTR,NULL_PTR));
    }


    /* Initialize the state of Rmba to IDLE */
    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

    /* Reset the OpStatus */
    Dcm_stRmbaOpstatus_u8 = DCM_INITIAL;

}

/**
 ****************************************************************************************************************
 * Dcm_Prv_GetAddressRangeIndex_u8:
 *
 * Calculate the idxIndex_u16 of an MemoryAddress received from the tester in the Dcm_GetIndexOfRmba_u8
 *
 * \param     dataMemAddr_u32             : It is the address from which the tester has requested for read request
 *            nrMemLength_u32             : The length of the data to be read from the start of dataMemAddr_u32
 *            idxIndex_u16(Out parameter) : Index of Dcm_RMBAConfig_cast within which the range of memory address falls.
 * \retval
 *            E_OK                        : idxIndex_u16 successfully calculated
 *            E_NOT_OK                    : Memory address was not found.
 * \seealso:
 *
 ****************************************************************************************************************
 */

static FUNC (Std_ReturnType,DCM_CODE) Dcm_Prv_GetAddressRangeIndex_u8(VAR (uint32,AUTOMATIC) dataMemAddr_u32,
                                                            VAR (uint32,AUTOMATIC) nrMemLength_u32,
                                                            P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxIndex_u16)
{

    VAR (uint16,         AUTOMATIC) dataSize_u16;
    VAR (uint16,         AUTOMATIC) idxLoop_u16;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8;

    /* Initialize local variables */
    dataRetVal_u8=E_NOT_OK;

    if(0u != nrMemLength_u32)
    {
        dataSize_u16 = Dcm_RmbacalculateTableSize_u16();
        for(idxLoop_u16 = 0;idxLoop_u16<dataSize_u16;idxLoop_u16++)
        {
            if((dataMemAddr_u32 >= Dcm_RMBAConfig_cast[idxLoop_u16].dataReadMemoryRangeLow_u32) &&
                                   ((dataMemAddr_u32 + (nrMemLength_u32-1u))<=
                                   (Dcm_RMBAConfig_cast[idxLoop_u16].dataReadMemoryRangeHigh_u32)))
            {
                *idxIndex_u16 = idxLoop_u16;
                dataRetVal_u8 = E_OK;
                break;
            }
        }
    }
    return (dataRetVal_u8);
}

/**
 **************************************************************************************************
 * Dcm_Prv_RmbaTotalCheckLength :    Checks the address and data size
 *                                   address and data size cannot be 0 bytes and beyond 4 bytes
 *
 * \param               pMsgContext             :   Pointer to message structure
 *                      dataNegRespCode_u8      :   Pointer to a Byte in which to store a negative Response code
 *                                                  in case of detection of an error in the request.
 *
 * \retval              None
 **************************************************************************************************
*/
/*TRACE[SWS_Dcm_00853]
  TRACE[SWS_Dcm_00493]*/
LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Prv_RmbaTotalCheckLength(
                                 P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                 P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType, AUTOMATIC) dataRetGetIdxRMBA_u8;/* Variable to store the return from Binary Search function */
    *dataNegRespCode_u8 = 0x00;

    if((DCM_MINSIZE!=Dcm_dataMemaddrsize_u8)&&(DCM_MINSIZE!=Dcm_dataMemdatasize_u8)&&
      ((Dcm_dataMemdatasize_u8 <=DCM_MAXSIZE)&&(Dcm_dataMemaddrsize_u8<=DCM_MAXSIZE)))
    {
        /*Total Length Check, 1 added is for the address length field format identifier field*/
        if(pMsgContext->reqDataLen == (Dcm_dataMemaddrsize_u8 + Dcm_dataMemdatasize_u8 + 1u))
        {
            /*Calculate the Memory address to read requested by the tester*/
            Dcm_GetMemoryInfo(Dcm_dataMemaddrsize_u8,&(pMsgContext->reqData[1]),&Dcm_dataMemoryAddress_u32);
            /*Calculate the memory size requested by the tester*/
            Dcm_GetMemoryInfo(Dcm_dataMemdatasize_u8,&(pMsgContext->reqData[Dcm_dataMemaddrsize_u8+1]),
                                                       &Dcm_nrReadMemoryLength_u32);

            /* Check if the Memory Address sent from tester is configured in the Server */
            dataRetGetIdxRMBA_u8 = Dcm_Prv_GetAddressRangeIndex_u8(Dcm_dataMemoryAddress_u32,
                                                                   Dcm_nrReadMemoryLength_u32,
                                                                   &Dcm_idxDspRmba_u16);


            if(E_OK == dataRetGetIdxRMBA_u8)
            {
                Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }
            else
            {
                /*Set NRC 0x31 Memory address is not configured or
                 * it is outside the boundaries of lower and upper limits */
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
        }
        else
        {
            /*Set NRC 0x31 Total Length check has failed */
            *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }

    }
    else
    {
        /*Set NRC 0x31 addressAndLengthFormat-Identifier is not applicable */
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }
}

/**
 **************************************************************************************************
 * Dcm_RmbaActiveSecurityLevel :     Check if the Read is allowed in the active security level
 *
 * \param     dataSecurityMask_u32    :   Variable to hold the configured security value
 *            adrRmbaConfig_pcst      :   Pointer to RMBA configuration
 *            adrNegRespCode_pu8      :   Pointer to a Byte in which to store a negative Response code
 *                                        in case of detection of an error in the request.
 *
 * \retval    DCM_RMBA_SUPPORT_CONDITION_VIOLATED   :   Conditions for reading not supported
 *            DCM_RMBA_SUPPORT_SECURITY_VIOLATED    :   Range of Address is not supported in the current security level;
 *                                                      negative response code is set to adrNegRespCode_pu8
 **************************************************************************************************
 */
/*TRACE[SWS_Dcm_00494]*/
LOCAL_INLINE FUNC(Dcm_RmbaSupportRet_t,DCM_CODE) Dcm_Prv_RmbaActiveSecurityLevel (
             VAR (uint32,AUTOMATIC) dataSecurityMask_u32,
             P2CONST(Dcm_RMBAConfig_tst,AUTOMATIC,DCM_INTERN_CONST)adrRmbaConfig_pcst,
             P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) adrNegRespCode_pu8)
{
    VAR (Std_ReturnType,   AUTOMATIC)       dataModeChkRetval_u8;               /*Return value of mode rule check API*/
    VAR (Dcm_RmbaSupportRet_t, AUTOMATIC)   dataRetVal_en;                      /* return value of this function */

    *adrNegRespCode_pu8 = 0x00;
    dataRetVal_en = DCM_RMBA_SUPPORT_OK;

            /* Check if the Read is allowed in the active security level*/
           if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
           {

               if(adrRmbaConfig_pcst->adrUserMemReadModeRule_pfct!=NULL_PTR)
               {
                   /* Call the configured API to check for conditions before reading to the memory location */
                   dataModeChkRetval_u8 =(*adrRmbaConfig_pcst->adrUserMemReadModeRule_pfct)
                                         (adrNegRespCode_pu8,Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,
                                          DCM_SUPPORT_READ);
               }
               else
               {
                   /* Call the DcmAppl API to check for conditions before reading from the memory location */
                   dataModeChkRetval_u8 = DcmAppl_UserMemoryRangeModeRuleService(adrNegRespCode_pu8,
                                                                                 Dcm_dataMemoryAddress_u32,
                                                                                 Dcm_nrReadMemoryLength_u32,
                                                                                 DCM_SUPPORT_READ);
               }
               /* If the mode rule returns TRUE , ignore the NRC value */
               if((dataModeChkRetval_u8!=E_OK))
               {
                   if(*adrNegRespCode_pu8 ==0x00)
                   {
                       *adrNegRespCode_pu8 = DCM_E_CONDITIONSNOTCORRECT;
                   }
                   dataRetVal_en = DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
               }
               else
               {
                   *adrNegRespCode_pu8=0;
               }

#if (DCM_CFG_DSP_MODERULEFORREADMEMORY != DCM_CFG_OFF)
               if((*adrNegRespCode_pu8==0x00) && (NULL_PTR != adrRmbaConfig_pcst->addrRmbaModeRuleChkFnc_pfct))
               {
                  (void)(*(adrRmbaConfig_pcst->addrRmbaModeRuleChkFnc_pfct))(adrNegRespCode_pu8);
               }

               if(*adrNegRespCode_pu8 !=0x00)
               {
                   dataRetVal_en=DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
               }
#endif


           }
           /* If Read is not supported in active security level */
           else
           {
               *adrNegRespCode_pu8 = DCM_E_SECURITYACCESSDENIED;
               dataRetVal_en       = DCM_RMBA_SUPPORT_SECURITY_VIOLATED;
           }
   return dataRetVal_en;
}


/**
 **************************************************************************************************
 * Dcm_Prv_RmbaAccessCheck_u8:
 *
 * Calculate if the Address Range at position idxIndex_u16 in the Dcm_RMBAConfig_cast is supported
 * at this point in time or not.
 *
 * \param     idxIndex_u16:             idxIndex_u16 in Dcm_RMBAConfig_cast
 *            pMsgContext:              Pointer to message structure
 *            adrNegRespCode_pu8:       Pointer to a Byte in which to store a negative Response code
 *                                      in case of detection of
 *                                      an error in the request.
 *
 * \retval    none
 *
 **************************************************************************************************
 */

static FUNC (void, DCM_CODE) Dcm_Prv_RmbaAccessCheck_u8 (VAR (uint16,AUTOMATIC) idxIndex_u16,
                                     P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) adrNegRespCode_pu8)
{

    VAR (uint32,AUTOMATIC)                 dataSessionMask_u32; /* Variable to hold the configured sessions value */
    VAR (uint32,AUTOMATIC)                 dataSecurityMask_u32; /* Variable to hold the configured security value */
    P2CONST(Dcm_RMBAConfig_tst,AUTOMATIC,DCM_INTERN_CONST)  adrRmbaConfig_pcst; /* Pointer to RMBA configuration */
    VAR (Dcm_RmbaSupportRet_t, AUTOMATIC)  dataRetVal_en;        /* return value of this function */
    VAR (Std_ReturnType,   AUTOMATIC)      stGetMemAccess_u8;    /* Return value of Memory access check API */

    /* Initialize local variables */
    dataRetVal_en = DCM_RMBA_SUPPORT_OK;
    *adrNegRespCode_pu8     = 0x00;
    adrRmbaConfig_pcst = &Dcm_RMBAConfig_cast[idxIndex_u16];

    /*Copy the session and security level of RMBA configured*/
    dataSessionMask_u32 = adrRmbaConfig_pcst -> dataAllowedSessRead_u32;
    dataSecurityMask_u32 = adrRmbaConfig_pcst -> dataAllowedSecRead_u32;

    /* Check if the Read is allowed in the active session*/
    if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
    {
        /* The DcmAppl function to check the memory access permission*/
        stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(Dcm_dataMemoryAddress_u32,
                                                                       Dcm_nrReadMemoryLength_u32,DCM_SUPPORT_READ);
        if(stGetMemAccess_u8 != E_OK)
        {
            *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_en = DCM_RMBA_SUPPORT_CONDITION_VIOLATED;
        }
        else
        {
            /* Check if the Read is allowed in the active security level*/
            dataRetVal_en = Dcm_Prv_RmbaActiveSecurityLevel(dataSecurityMask_u32,adrRmbaConfig_pcst,adrNegRespCode_pu8);
        }
    }
    /* If Read is not supported in active session */
    else
    {
        *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
        dataRetVal_en       = DCM_RMBA_SUPPORT_SESSION_VIOLATED;
    }

    /* Checks if the length of the data to be read is less than available DCM buffer */
    if(dataRetVal_en == DCM_RMBA_SUPPORT_OK)
    {
        if(Dcm_nrReadMemoryLength_u32 <= pMsgContext->resMaxDataLen)
         {
            Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
         }
        else
        {
            *adrNegRespCode_pu8 = DCM_E_RESPONSETOOLONG;
        }
    }

}

/**
 **************************************************************************************************
 * Dcm_RmbaDataReadRetValue : Checks the read operation status and operates accordingly.
 *
 * \param               pMsgContext         : Pointer to message structure
 *                      dataNegRespCode_u8  : Pointer to a Byte in which to store a negative Response code
 *                                            in case of detection of an error in the request
 *
 * \retval              E_OK            :   Request for read is successful
 *                      DCM_E_PENDING   :   Request for read is not yet finished
 *                      DCM_E_FORCE_RCRRP:  Application requests the transmission of a response Pending
 *                      E_NOT_OK        :   Request for read not successful
 **************************************************************************************************
 */
/*TRACE[SWS_Dcm_00495]*/
LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_Prv_RmbaReadMemory(
                                 P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                 P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (Dcm_ReadMemoryRet_t, AUTOMATIC) dataReadReturnVal_en; /* variable for storing the memory address size*/
    VAR(Std_ReturnType, AUTOMATIC) dataServRet_u8;

    /*Initialization of Local Variables*/
    dataReadReturnVal_en = DCM_READ_FAILED;
    dataServRet_u8=DCM_E_PENDING;

    /*All the conditions met, Place a call out to Dcm_ReadMemory*/
    dataReadReturnVal_en = DcmAppl_Dcm_ReadMemory (
                          Dcm_stRmbaOpstatus_u8,Dcm_RMBAConfig_cast[Dcm_idxDspRmba_u16].dataMemoryValue_u8,
                          Dcm_dataMemoryAddress_u32,Dcm_nrReadMemoryLength_u32,pMsgContext->resData,dataNegRespCode_u8);

    if(DCM_READ_OK == dataReadReturnVal_en)
    {
        /*Response is already filled by the application*/
        /* Set final response length */
        pMsgContext->resDataLen =  Dcm_nrReadMemoryLength_u32;
        dataServRet_u8=E_OK;
        /* Reset the state of RMBA state machine to Initial */
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_stRmbaOpstatus_u8   = DCM_INITIAL;
        *dataNegRespCode_u8=0X00;
    }
    else if(DCM_READ_PENDING==dataReadReturnVal_en)
    {
        Dcm_stRmbaOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8=0;
        dataServRet_u8=DCM_E_PENDING;
    }
    else if(DCM_READ_FORCE_RCRRP == dataReadReturnVal_en)
    {
        Dcm_stRmbaOpstatus_u8 = DCM_FORCE_RCRRP_OK;
        *dataNegRespCode_u8=0;
        dataServRet_u8=DCM_E_FORCE_RCRRP;
    }
    else
    {
        if(*dataNegRespCode_u8 == 0)
        {
            /*Read has failed*/
            *dataNegRespCode_u8 =   DCM_E_GENERALREJECT;
            dataServRet_u8=E_NOT_OK;
        }

        Dcm_stRmbaOpstatus_u8=DCM_INITIAL;
    }
    return dataServRet_u8;
}

/**
 **************************************************************************************************
 * Dcm_DcmReadMemoryByAddress : Read Memory By Address (0x23) Service
 * RMBA service is used to read the Data using a physical memory address
 *                  sent in the request by the tester
 *
 * \param       OpStatus           : Output status of service
 *              pMsgContext        : Pointer to message structure.
 *              dataNegRespCode_u8 : Pointer to a Byte in which to store a negative Response code
 *                                   in case of detection of an error in the request.
 *
 * \retval      E_OK                :   Request is successful
 *              DCM_E_PENDING       :   Request for read is not yet finished
 *              DCM_E_FORCE_RCRRP   :   Application requests the transmission of a response Pending
 *              E_NOT_OK            :   Request is not successful
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* TRACE[SWS_Dcm_00492] */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadMemoryByAddress (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType, AUTOMATIC) dataServRet_u8;   /* Variable to store the return from service */

    /*Initialization of Local Variables*/
    dataServRet_u8=E_NOT_OK;
    *dataNegRespCode_u8=0x0;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

   /* For cancellation of service -Rmba is called with opstatus set to Dcm_cancel */
    if(OpStatus == DCM_CANCEL)
    {
        Dcm_RMBAIni();
        dataServRet_u8 = E_OK;
    }
    else
    {
        /* Rmba State Machine */
        if (Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {
            /* Check for the minimum request length equal to 0x03 bytes as 1 byte addressAndLengthFormatIdentifier
            and  one byte of memoryAddress, one byte of memorySize is mandatory in RMBA request */
            if(pMsgContext->reqDataLen >= DCM_DSP_RMBA_MINREQLEN)
            {
                /* Extract the memory address and data record size information from the request buffer */
                Dcm_dataMemaddrsize_u8 = ((pMsgContext->reqData[0])& (0xFu));
                Dcm_dataMemdatasize_u8 = (uint8)(((pMsgContext->reqData[0])& (0xF0u))>>4u);

                /*address and data size cannot be 0 bytes and beyond 4 bytes(Implicit requirement as call of
                 Dcm_ReadMemory for address and data size parameter is of type uint32)*/
                Dcm_Prv_RmbaTotalCheckLength(pMsgContext, dataNegRespCode_u8);
            }
            else
            {
                /*Set NRC Request Length incorrect */
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        /* Rmba State Machine */
        if (Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {
            /* Call the function to see if there is a Read support @ the address requested by tester */
            Dcm_Prv_RmbaAccessCheck_u8(Dcm_idxDspRmba_u16,pMsgContext,dataNegRespCode_u8);
        }

        if (Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {

            dataServRet_u8 = Dcm_Prv_RmbaReadMemory(pMsgContext, dataNegRespCode_u8);

        }

        /* Check if Negative response is set */
        if(*dataNegRespCode_u8 != 0)
        {
            /* Reset the state of RMBA state machine to Initial */
            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            dataServRet_u8=E_NOT_OK;
        }
    }
    return dataServRet_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif

