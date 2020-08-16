

#include "DcmDspUds_Tp_Inf.h"
#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Tp_Priv.h"


#if(DCM_CFG_DSP_TESTERPRESENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DcmTesterPresent :
 *  This service is used to keep one or multiple servers in a diagnostic session being different than
 *  the defaultSession. Dcm_DcmTesterPresent() function is called by DSD, when TesterPresent service
 *  is recognised (SID set to 0x3E), this service provided in DSP module and configured in DCM
 *  identifier table.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmTesterPresent (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8=E_NOT_OK;
    *dataNegRespCode_u8=0;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
     /* Check if the request Data Length is greater than zero(Minimum Length Check) */
    if(pMsgContext->reqDataLen > 0uL)
    {
       if(pMsgContext->reqData[DCM_TPR_POSITION_SUBFUNC] == DCM_TPR_RESP_REQUIRED)
       {
           /* Check if the request Data Length is equal to 1(Exact length check) */
           if(pMsgContext->reqDataLen == DCM_TPR_REQ_LEN)
            {
              pMsgContext->resDataLen = DCM_TPR_POSITIVE_RESP_LEN;
              pMsgContext->resData[DCM_TPR_POSITION_SUBFUNC] = 0x00u;
              retVal_u8=E_OK;
            }
                 /* Incorrect message length */
            else
            {
                /*Set Negative response code */
              *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
       }
            /* sub function not supported */
       else
       {
               /*Set Negative response code */
               *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
       }
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if(*dataNegRespCode_u8 != 0x0u)
    {
        /* Call function to set Negative response code */
        retVal_u8=E_NOT_OK;
    }
    return retVal_u8;
}


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#if(DCM_CFG_DSP_TESTERPRESENTSB_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DcmTesterPresentSB is a variant of UDS 14229 Tester present which is used for DGS SB reprogramming
 * This tester present gives responses for both 3e and 3e 00 requests. The request without sub function byte
 * being used for DGS SB re-programming.
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmTesterPresentSB (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8=E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    /* Check if the request Data Length is equal to 1 ; UDS Tester Present Case which has Subfunction Byte */
    if(pMsgContext->reqDataLen == DCM_TPR_REQ_LEN)
    {
        /* check whether Subfunction is correct */
        if(pMsgContext->reqData[DCM_TPR_POSITION_SUBFUNC] == DCM_TPR_RESP_REQUIRED)
        {
            /* Set length of response: */
            pMsgContext->resDataLen = DCM_TPR_POSITIVE_RESP_LEN;
            pMsgContext->resData[DCM_TPR_POSITION_SUBFUNC] = 0x00u;
            retVal_u8=E_OK;
        }
        /* subfunction not supported */
        else
        {
            /*Set Negative response code */
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
    /* Request Length Zero Check DGS SB Tester Present Case which does not have SubFunction Byte */
    else if(pMsgContext->reqDataLen == 0x00u)
    {
        /* Set length of response as zero since this is a DGS SB Tester Present */
        pMsgContext->resDataLen = 0x00u;
        retVal_u8=E_OK;
    }
    else
    {
        /*Set Negative response code */
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }

    if(*dataNegRespCode_u8 != 0x0u)
    {
        /* Call function to set Negative response code */
        retVal_u8=E_NOT_OK;
    }

    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

