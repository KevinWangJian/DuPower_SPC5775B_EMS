


#include "DcmDspUds_Wmba_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Wmba_Priv.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"
static VAR(uint32,DCM_VAR) Dcm_adrMemoryAddress_u32;    /*Variable to store the memory address requested by the tester*/
static VAR(uint32,DCM_VAR) Dcm_nrWriteMemoryLength_u32; /*Variable to store the memory length requested by the tester*/
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.h"
/*Variable to store the idxLoop_u8 of the Memory address in Dcm_WMBAConfig_cast table */
static VAR(uint16,            DCM_VAR) Dcm_idxDspWmba_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stWmbaOpstatus_u8;
static VAR (uint8,  DCM_VAR) Dcm_nrMemDataSize_u8;              /* variable for storing the data record dataSize_u16*/
static VAR (uint8,  DCM_VAR) Dcm_nrMemAddrSize_u8;            /* variable for storing the memory address dataSize_u16*/
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
/**
 **********************************************************************************************************************
 * Dcm_Dcm_WMBAIni : Initialisaton function for Write Memory By Address (0x3D) Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_WMBAIni (void)
{
    if(DCM_PENDING == Dcm_stWmbaOpstatus_u8)
    {
        (void)(DcmAppl_Dcm_WriteMemory(DCM_CANCEL,Dcm_WMBAConfig_cast[Dcm_idxDspWmba_u16].dataMemoryValue_u8,
                                   Dcm_adrMemoryAddress_u32,Dcm_nrWriteMemoryLength_u32,
                                   NULL_PTR,NULL_PTR));
    }

    /* Initialize the state to INITIAL */
    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

    /* Reset the OpStatus */
    Dcm_stWmbaOpstatus_u8 = DCM_INITIAL;

}

/**
 **********************************************************************************************************************
 * Dcm_Prv_GetAddressRangeIndex_u8:
 *
 * Calculate the idxLoop_u8 of an MemoryAddress received from the tester in the Dcm_Prv_GetAddressRangeIndex_u8
 *
 * \param       dataMemAddr_u32             :   It is the address from which the tester has requested for write request
 *              dataMemLength_u32           :   The length of the data to be written from the start of dataMemAddr_u32
 *              idxLoop_u8(Out parameter)   :   Index of Dcm_WMBAConfig_cast where the memory address is found.
 * \retval
 *              E_OK                        : idxLoop_u8 successfully calculated
 *              E_NOT_OK                    : Memory address was not found.
 * \seealso:
 *
 **********************************************************************************************************************
 */

static FUNC (Std_ReturnType,DCM_CODE) Dcm_Prv_GetAddressRangeIndex_u8(VAR (uint32,AUTOMATIC) dataMemAddr_u32,
        VAR   (uint32,AUTOMATIC) dataMemLength_u32,
        P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) idxLoop_u8)
{

    VAR (uint16,         AUTOMATIC) dataSize_u16;
    VAR (uint16,         AUTOMATIC) idxWmba_u16;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_en;

    dataRetVal_en=E_NOT_OK;



    if((uint32)0u != dataMemLength_u32)
    {
        dataSize_u16 = Dcm_WmbacalculateTableSize_u16();
        for(idxWmba_u16 = 0;idxWmba_u16<dataSize_u16;idxWmba_u16++)
        {
            if((dataMemAddr_u32 >= Dcm_WMBAConfig_cast[idxWmba_u16].dataWriteMemoryRangeLow_u32) && \
               ((dataMemAddr_u32 + (dataMemLength_u32-1uL))<= \
               (Dcm_WMBAConfig_cast[idxWmba_u16].dataWriteMemoryRangeHigh_u32)))
            {
                *idxLoop_u8 = idxWmba_u16;
                dataRetVal_en = E_OK;
                break;
            }
        }
    }

    return (dataRetVal_en);
}

/**
 **********************************************************************************************************************
 * Dcm_WMBACheckLength : Checking Received Length
 * Checks the length of the requested Address And Length Format Identifier
 *
 * \param          pMsgContext: Pointer to message structure
 *                 dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code in case of
 *                                     detection of an error in the request.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
 /*TRACE:[SWS_Dcm_00489]*/


LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_Prv_WMBATotalCheckLength (
                                       P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC)   dataRetGetIdxWmba_u8; /* Variable to store the return from Binary Search function */
    *dataNegRespCode_u8 = 0x00;


    /*address and data dataSize_u16 cannot be 0 bytes and beyond 4 bytes(Implicit requirement as callout to
     *  Dcm_WriteMemory has address and data
     * dataSize_u16 parameter is of type uint32)*/
   if((DCM_MINSIZE!=Dcm_nrMemAddrSize_u8)&&
      (DCM_MINSIZE!=Dcm_nrMemDataSize_u8)&&
      (Dcm_nrMemDataSize_u8 <=DCM_MAXSIZE)&&
      (Dcm_nrMemAddrSize_u8<=DCM_MAXSIZE))
   {
     /*Calculate the Memory address to write requested by the tester*/
     Dcm_GetMemoryInfo(Dcm_nrMemAddrSize_u8,&(pMsgContext->reqData[1]),&Dcm_adrMemoryAddress_u32);
     /*Calculate the memory dataSize_u16 requested by the tester*/
     Dcm_GetMemoryInfo(Dcm_nrMemDataSize_u8,&(pMsgContext->reqData[Dcm_nrMemAddrSize_u8+1]),
                       &Dcm_nrWriteMemoryLength_u32);

     /*Total Length Check*/
      if(pMsgContext->reqDataLen == (Dcm_nrMemAddrSize_u8 + Dcm_nrMemDataSize_u8 + Dcm_nrWriteMemoryLength_u32 + 1u))
      {
        /* Check if the Memory Address sent from tester is configured in the Server */
        dataRetGetIdxWmba_u8 = Dcm_Prv_GetAddressRangeIndex_u8(Dcm_adrMemoryAddress_u32,
                                                               Dcm_nrWriteMemoryLength_u32,
                                                               &Dcm_idxDspWmba_u16);



            if(E_OK == dataRetGetIdxWmba_u8)
            {
              Dcm_SrvOpstatus_u8 = DCM_CHECKDATA;
            }
            /*Set NRC 0x31 addressAndLengthFormat-Identifier is not applicable */
            else
            {
              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }
       }
       else
       {
          /*Set NRC 0x13 TOTAL Length check has failed */
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
 ***********************************************************************************************************************
 * Dcm_Prv_WMBAUpdateStatus:
 * Updates the Status after writing to the memory
 *
 * \param       dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                                      an error in the request.
 *              pMsgContext: Pointer to message structure
 *
 *
 * \retval          E_OK : If write pass
 *                  DCM_E_PENDING : If State returns Pending
 *                  DCM_FORCE_RCRRP_OK :If State returns FORCE_RCRRP
 *                  E_NOT_OK : If writes fails
 *
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_Prv_WMBAUpdateStatus (
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)

   {

      VAR (uint8,  AUTOMATIC) idxLoop_u8;
      VAR(Std_ReturnType,AUTOMATIC)   dataRetVal_u8;      /* Variable to store the return from service*/

      /*variable for storing the memory address dataSize_u16*/
      VAR (Dcm_WriteMemoryRet_t, AUTOMATIC) dataWriteReturnVal_en;

      dataWriteReturnVal_en = DCM_WRITE_FAILED;/*Initilization*/

      /*TRACE:[SWS_Dcm_00491]*/

      /*All the conditions met, Place a call out to Dcm_WriteMemory*/
      dataWriteReturnVal_en= DcmAppl_Dcm_WriteMemory(
                                                Dcm_stWmbaOpstatus_u8,
                                                Dcm_WMBAConfig_cast[Dcm_idxDspWmba_u16].dataMemoryValue_u8,
                                                Dcm_adrMemoryAddress_u32,Dcm_nrWriteMemoryLength_u32,
                                               &(pMsgContext->reqData[Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8 + 1]),
                                                dataNegRespCode_u8);


      if(DCM_WRITE_OK==dataWriteReturnVal_en)
      {
        /* Set final response length, in the below statement 1 is added for the Address and Length Format Identifier)*/
         pMsgContext->resDataLen =  Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8 + 1;
         /*Copy the response based on the dataSize_u16 of Dcm_nrMemDataSize_u8 and Dcm_nrMemDataSize_u8*/
        for(idxLoop_u8=Dcm_nrMemDataSize_u8 + Dcm_nrMemAddrSize_u8+1;idxLoop_u8!=0;idxLoop_u8--)
        {
         /*Copy the memory address and memory dataSize_u16 in to the buffer from the request buffer to
         * response buffer using bottom up approach*/
          pMsgContext->resData[idxLoop_u8-1] = pMsgContext->reqData[idxLoop_u8-1];
        }

        /*Return E_OK from the service*/
        dataRetVal_u8=E_OK;
        /* Reset the state of WMBA state machine to IDLE */
        Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        Dcm_stWmbaOpstatus_u8 = DCM_INITIAL;
        *dataNegRespCode_u8=0x00;
      }
      else if(DCM_WRITE_PENDING==dataWriteReturnVal_en)
      {
        Dcm_stWmbaOpstatus_u8=DCM_PENDING;
        dataRetVal_u8=DCM_E_PENDING;
        *dataNegRespCode_u8=0x00;
      }
      else if(DCM_WRITE_FORCE_RCRRP == dataWriteReturnVal_en)
      {
           Dcm_stWmbaOpstatus_u8 = DCM_FORCE_RCRRP_OK;
           *dataNegRespCode_u8=0x00;
           dataRetVal_u8=DCM_E_FORCE_RCRRP;
      }
      else
      {
            if(*dataNegRespCode_u8 ==0x00)
            {
               *dataNegRespCode_u8 =   DCM_E_GENERALPROGRAMMINGFAILURE;
            }
            /*Write has failed*/
            Dcm_stWmbaOpstatus_u8=DCM_INITIAL;
            dataRetVal_u8=E_NOT_OK;
      }

      return dataRetVal_u8;
   }

/**
 ***********************************************************************************************************************
 * Dcm_Prv_WMBASecurityCheck : WMBASecurityCheck
 * Checks requested memory is allowed to write in current security level
 *
 * \param
 *          dataSecurityMask_u32 : It is the security level
 *          adrWmbaConfig_pcst: Pointer to WMBA configuration
 *          adrNegRespCode_pu8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                              an error in the request.
 *
 *
 * \retval
 *          DCM_WMBA_SUPPORT_CONDITION_VIOLATED : when the support condition is voilated
 *          DCM_SUPPORT_SECURITY_VIOLATED, ID is not supported in the current security level;
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */



LOCAL_INLINE FUNC(Dcm_WmbaSupportRet_t,DCM_CODE) Dcm_Prv_WMBASecurityCheck (
                                     VAR (uint32,AUTOMATIC) dataSecurityMask_u32,
                                     P2CONST(Dcm_WMBAConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrWmbaConfig_pcst,
                                     P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) adrNegRespCode_pu8)
   {

        VAR (Dcm_WmbaSupportRet_t, AUTOMATIC) dataRetVal_en; /* return value of this function */
        VAR (Std_ReturnType,   AUTOMATIC) dataModeChkRetval_u8; /*Return value of mode rule check API*/

        dataRetVal_en = DCM_WMBA_SUPPORT_OK;  /* Return value of this function */

/*TRACE:[SWS_Dcm_00490]*/

        /* Check if the Write is allowed in the active security level*/
        if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
        {

/*TRACE:[SWS_Dcm_00825]*/
            if(adrWmbaConfig_pcst->adrUserMemWriteModeRule_pfct!=NULL_PTR)
            {
                /* Call the configured API to check for conditions before writing to the memory location */
                dataModeChkRetval_u8 =(*adrWmbaConfig_pcst->adrUserMemWriteModeRule_pfct)(adrNegRespCode_pu8,
                                                                                          Dcm_adrMemoryAddress_u32,
                                                                                          Dcm_nrWriteMemoryLength_u32,
                                                                                          DCM_SUPPORT_WRITE);
            }
            else
            {
                /* Call the DcmAppl API to check for conditions before writing to the memory location */
                dataModeChkRetval_u8 =DcmAppl_UserMemoryRangeModeRuleService(adrNegRespCode_pu8,
                                                                             Dcm_adrMemoryAddress_u32,
                                                                             Dcm_nrWriteMemoryLength_u32,
                                                                             DCM_SUPPORT_WRITE);
            }
            /* If the mode rule returns TRUE , ignore the NRC value */
            if(dataModeChkRetval_u8!=E_OK)
            {
                if(*adrNegRespCode_pu8 ==0x00)
                {
                    *adrNegRespCode_pu8 = DCM_E_CONDITIONSNOTCORRECT;
                }
                dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
            }
            else
            {
                *adrNegRespCode_pu8=0;
            }
#if (DCM_CFG_DSP_MODERULEFORWRITEMEMORY != DCM_CFG_OFF)
            if((*adrNegRespCode_pu8==0x00)&&(NULL_PTR != adrWmbaConfig_pcst->addrWmbaModeRuleChkFnc_pfct))
            {
                (void)(*(adrWmbaConfig_pcst->addrWmbaModeRuleChkFnc_pfct))(adrNegRespCode_pu8);
            }

            if(*adrNegRespCode_pu8 !=0x00)
            {
                dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
            }
#endif


        }
        /* If write is not supported in active security level */
        else
        {
            *adrNegRespCode_pu8 = DCM_E_SECURITYACCESSDENIED;
            dataRetVal_en       = DCM_WMBA_SUPPORT_SECURITY_VIOLATED;
        }

        return dataRetVal_en;
   }


/**
 ***********************************************************************************************************************
 * Dcm_Prv_WmbaAccessCheck_u8:
 *
 * Calculate if the ID at position idxLoop_u8 in the Dcm_DIDConfig is supported at this point in time or not.
 *
 * \param     idxLoop_u8: idxLoop_u8 in Dcm_DIDConfig
 *            direction: check for read or write support:     DCM_SUPPORT_READ,    DCM_SUPPORT_WRITE
 *            adrNegRespCode_pu8: Pointer to a Byte in which to store a negative Response code in case of detection of
 *                         an error in the request.
 *
 * \retval
 * DCM_SUPPORT_OK,                ID is supported
 * DCM_SUPPORT_SESSION_VIOLATED,  ID is not supported in the current session;
 *                                negative response code is set to adrNegRespCode_pu8
 * DCM_SUPPORT_SECURITY_VIOLATED, ID is not supported in the current security level;
 *                                negative response code is set to adrNegRespCode_pu8
 * DCM_SUPPORT_CONDITION_VIOLATED,ID is not supported as per configured callback function;
 *                                negative response code is set to adrNegRespCode_pu8
 * DCM_SUPPORT_CONDITION_PENDING  checking needs more time. call again.
 * \seealso
 *
 ***********************************************************************************************************************
 */

static FUNC (Dcm_WmbaSupportRet_t,DCM_CODE) Dcm_Prv_WmbaAccessCheck_u8 (VAR (uint16,AUTOMATIC) idxLoop_u8,
        P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) adrNegRespCode_pu8)
{

    VAR (uint32,AUTOMATIC) dataSessionMask_u32;   /* Variable to hold the configured sessions value */
    VAR (uint32,AUTOMATIC) dataSecurityMask_u32;  /* Variable to hold the configured security value */
    P2CONST(Dcm_WMBAConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrWmbaConfig_pcst; /* Pointer to WmBA configuration */
    VAR (Dcm_WmbaSupportRet_t, AUTOMATIC) dataRetVal_en; /* return value of this function */
    VAR (Std_ReturnType,   AUTOMATIC) stGetMemAccess_u8; /* Return value of Memory access check API */


    /* Initialize local variables */
    dataRetVal_en = DCM_WMBA_SUPPORT_OK;  /* Return value of this function */
    *adrNegRespCode_pu8     = 0x00;
    adrWmbaConfig_pcst = &Dcm_WMBAConfig_cast[idxLoop_u8];

    /*Copy the session and security level of WMBA configured*/
    dataSessionMask_u32 = adrWmbaConfig_pcst -> dataAllowedSessWrite_u32;
    dataSecurityMask_u32 = adrWmbaConfig_pcst -> dataAllowedSecWrite_u32;

    /* Check if the Write is allowed in the active session*/
    if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
    {
        /* The DcmAppl  function to check the memory access permission*/
        stGetMemAccess_u8 = DcmAppl_DcmGetPermissionForMemoryAccess_u8(Dcm_adrMemoryAddress_u32,
                                                                       Dcm_nrWriteMemoryLength_u32,DCM_SUPPORT_WRITE);
        if(stGetMemAccess_u8 != E_OK)
        {
            *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
            dataRetVal_en = DCM_WMBA_SUPPORT_CONDITION_VIOLATED;
        }
        else
        {
            dataRetVal_en = Dcm_Prv_WMBASecurityCheck (dataSecurityMask_u32,adrWmbaConfig_pcst,adrNegRespCode_pu8);
        }
    }
    /* If write is not supported in active session Dcm_Prv_WmbaAccessCheck_u8*/
    else
    {
        *adrNegRespCode_pu8 = DCM_E_REQUESTOUTOFRANGE;
        dataRetVal_en       = DCM_WMBA_SUPPORT_SESSION_VIOLATED;
    }
    return dataRetVal_en;
}

/**
 ***********************************************************************************************************************
 * Dcm_DcmWriteDataByAddress : Write Data By Address (0x3D) Service
 * WMBA service is used to write the Data using a physical memory address
 *                  sent in the request by the tester
 *
 * \param           pMsgContext: Pointer to message structure
 *                  OpStatus: Output status of service
 *                  dataNegRespCode_u8: Pointer to a Byte in which to store a negative Response code
 *                                         in case of detection of an error in the request.
 * \retval          E_OK : If write pass
 *                  DCM_E_PENDING : If State returns Pending
 *                  DCM_FORCE_RCRRP_OK :If State returns FORCE_RCRRP
 *                  E_NOT_OK : If writes fails
 * \seealso
 * \usedresources
 ***********************************************************************************************************************
 */
 /*TRACE:[SWS_Dcm_00488]*/


FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmWriteMemoryByAddress (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{


    VAR (Dcm_WmbaSupportRet_t, AUTOMATIC) dataRetWriteSupport_en;
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8; /* Variable to store the return from service*/

    /*Initialization of Local Variables*/
    dataRetVal_u8=E_NOT_OK;
    *dataNegRespCode_u8 = 0x0;

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_WMBAIni();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    { /* WMBA State Machine */
        if(Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {
            /* Check for the minimum request length equal to 0x04 bytes as 1 byte addressAndLengthFormatIdentifier
             and  one byte of memoryAddress,
             one byte of memorySize and one byte of dataRecord is mandatory in WMBA request */
            if(pMsgContext->reqDataLen >= DCM_DSP_WMBA_MINREQLEN)
            {
                /* Extract the memory address and data record dataSize_u16 information from the request buffer */
                Dcm_nrMemAddrSize_u8 = ((pMsgContext->reqData[0])& (0xFu));
                Dcm_nrMemDataSize_u8 = (uint8)(((pMsgContext->reqData[0])& (0xF0u))>>4u);

                /*Check for Total length received by the tester*/
                Dcm_Prv_WMBATotalCheckLength (pMsgContext,dataNegRespCode_u8);
            }
            else
            {
                /*Set NRC Request Length incorrect */
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }

       if(Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {


            /* Call the function to see if there is a write support at the address requested by tester */
            dataRetWriteSupport_en = Dcm_Prv_WmbaAccessCheck_u8(Dcm_idxDspWmba_u16,dataNegRespCode_u8);
            /* If the conditions of writing is supported */
            if(dataRetWriteSupport_en == DCM_WMBA_SUPPORT_OK)
            {
                /* Move the state to Write the DID data record */
                Dcm_SrvOpstatus_u8 = DCM_PROCESSSERVICE;
            }
        }

        if(Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {
            dataRetVal_u8 =  Dcm_Prv_WMBAUpdateStatus (pMsgContext,dataNegRespCode_u8);

        }
        /* Check if Negative response is set */
        if(*dataNegRespCode_u8 != 0)
        {
            /* Reset the state of WMBA state machine to IDLE */
            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
