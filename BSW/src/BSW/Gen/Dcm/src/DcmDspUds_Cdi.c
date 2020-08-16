

#include "DcmDspUds_Cdi_Inf.h"
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Cdi_Priv.h"

#define DCM_START_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"
static VAR(uint32,DCM_VAR) Dcm_dataDspReqDTCId_u32;       /* Requested DTC or group of DTC              */
#define DCM_STOP_SEC_VAR_CLEARED_32
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"
static VAR(Std_ReturnType,AUTOMATIC)  s_dataRetVal_u8;    /* Variable to store the return value of CDI service */
#define DCM_STOP_SEC_VAR_CLEARED_8
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

/*
**************************************************************************************************
* Dcm_PrivDTCLengthCheck : This function checks if the lentgh  check  for CDI request and
*                          type of Requested DTC (Single DTC or Group DTC)
*
* \parameters          Dcm_SrvOpStatusType: Operational status of service
*                      Dcm_MsgContextType:Pointer request and response data structure
*                      Dcm_NegativeResponseCodeType: Pointer to negative response code
*
*  * \return value     void
*
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_PrivDTCLengthCheck(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                  P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                                  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    if(pMsgContext->reqDataLen == DCM_CDI_REQ_LEN)
    {
        /* Get parameter 'groupOfDTC' HighByte + Middlebyte + LowByte */
        Dcm_dataDspReqDTCId_u32 = (  ((uint32)(pMsgContext->reqData[DCM_POS_DTC_HIGHBYTE]  ) << DCM_POS_DTC_BIT16) | \
                ((uint32)(pMsgContext->reqData[DCM_POS_DTC_MIDDLEBYTE]) << DCM_POS_DTC_BIT8) | \
                (uint32)(pMsgContext->reqData[DCM_POS_DTC_LOWBYTE]));

        /* Reset the 3rd nibble in group of DTC */
        /*MR12 RULE 2.2 VIOLATION :This operation is redundant. The value of the result is always that of the left-hand operand. MISRA C:2012 Rule-2.2*/
        Dcm_dataDspReqDTCId_u32 = (Dcm_dataDspReqDTCId_u32 & DCM_DTC_GRP_MASK);
        /* Check if the DTC sent from the Tester is 0xFFFFFF */

        if(Dcm_dataDspReqDTCId_u32 == DCM_DTC_GRP_MASK)
        {
            /* Set the Request DTC Id to DEM_DTC_GROUP_ALL_DTCS */
            Dcm_dataDspReqDTCId_u32 = DEM_DTC_GROUP_ALL_DTCS;
        }
        /* Update the Opstatus to DCM_CHECKDATA to perform conditon check on DTC */
        *OpStatus = DCM_CHECKDATA;
    }
    /* Request Length Invalid */
    else
    {
        /*Set Negative response code */
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
}
/*
**************************************************************************************************
* Dcm_PrivClearDTCInformation : This function clear DTC information
*
*
* \parameters          Dcm_SrvOpStatusType: Operational status of service
*                      Dcm_MsgContextType:Pointer request and response data structure
*                      Dcm_NegativeResponseCodeType: Pointer to negative response code
*
*  * \return value     void
*
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_PrivClearDTCInformation( P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
                                                        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;  /* For temporary storage of the DEM return values (enum) */

    dataDemClrRetVal_u8 = Dem_ClearDTC( Dcm_dataDspReqDTCId_u32, DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);
    switch(dataDemClrRetVal_u8)
    {
        /* If the clearing of DTC information is successful */
        case DEM_CLEAR_OK :
            #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
            DcmAppl_DcmClearRoeEventInformation();
            #endif
            /* Set Postive response with response length 0 */
            pMsgContext->resDataLen = 0x0u;
            /* Reset the state machine */
            *OpStatus = DCM_INITIAL;
            s_dataRetVal_u8 = E_OK;
            break;

        /* If DEM needs more time to clear the information */
        case  DEM_CLEAR_PENDING:
            /* Do nothing and remain in the same state */
            s_dataRetVal_u8 = DCM_E_PENDING;
            break;

        /* If the wrong DTC was sent from the tester */
        case DEM_CLEAR_WRONG_DTC:
            /* Set NRC */
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            break;

       /* If there is an error when writing to a memory location. */
        case DEM_CLEAR_MEMORY_ERROR:
            /* Set NRC */
            *dataNegRespCode_u8 = DCM_E_GENERALPROGRAMMINGFAILURE;
        break;

        /* If the DTC origin or DTC kind is incorrect or some problems in DEM */
        default:
            /* Set NRC */
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        break;
    }

}

/*
**************************************************************************************************
* DCM_PrivDTCConditionCheckfunc : This function will perform mode rule check or user condition check on DTC
*
*
* \parameters          Dcm_SrvOpStatusType: Operational status of service
*                      Dcm_NegativeResponseCodeType: Pointer to negative response code
*
*
*  * \return value     void
*
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE)  DCM_PrivDTCConditionCheckfunc(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                                          P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;     /* For temporary storage of the DEM return values (enum) */
#if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED!=DCM_CFG_OFF)
       VAR(Std_ReturnType,AUTOMATIC)  retVal_u8;
       VAR(boolean , AUTOMATIC) isModeChkRetval_b;
       VAR(boolean , AUTOMATIC) isConditionChkflag_b;
       retVal_u8 = E_OK;
       /*Initialize the mode rule value to FALSE*/
       isModeChkRetval_b = FALSE;
       isConditionChkflag_b = FALSE;
#endif

       dataDemClrRetVal_u8 = Dem_DcmCheckClearParameter (Dcm_dataDspReqDTCId_u32, DEM_DTC_FORMAT_UDS,DEM_DTC_ORIGIN_PRIMARY_MEMORY);
       switch(dataDemClrRetVal_u8)
       {
           case DEM_CLEAR_OK:


               #if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)
                   /* Change the state  DCM_DSP_CDI_CONDITIONCHECK to do manufacturer/supplier specific checks before the clearing the requested DTC*/
                   isConditionChkflag_b = TRUE;
               #else
                   /* Change the state  DCM_DSP_CDI_CLEAR to clear DTC */
                   *OpStatus = DCM_PROCESSSERVICE;
               #endif
               break;

           /* If DEM needs more time to clear the information */
           case DEM_CLEAR_PENDING:

           /* Do nothing and remain in the same state */
               s_dataRetVal_u8 = DCM_E_PENDING;
               break;

           /* If the wrong DTC was sent from the tester or origin is incorrect */
           case DEM_CLEAR_WRONG_DTC :
           case DEM_CLEAR_WRONG_DTCORIGIN:

              *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
               break;

           /* Any other return type */
           default:

               *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
               break;
       }




#if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED != DCM_CFG_OFF)
        /*To check  user specific condition for the DTC*/
  /* Check if the user function for condition check is available */
     if((isConditionChkflag_b ==  TRUE)&& (Dcm_CDIUserConditionCheck_pf != NULL_PTR))
    {
        /* Call the API to let application do a condition check for the DTC in the tester requeest */
        retVal_u8 = (*Dcm_CDIUserConditionCheck_pf) (Dcm_dataDspReqDTCId_u32,dataNegRespCode_u8);

        /* If the user configured condition check passes */
        if(retVal_u8 == E_OK)
        {
            /* ignore any NRC set by the application */
            *dataNegRespCode_u8 = 0x00;
            /* Change the state to clear DTCs */
            *OpStatus = DCM_PROCESSSERVICE;
        }
        /* If the condition check fails, i.e., application returns values other than E_OK */
        else
        {
            if(*dataNegRespCode_u8 == 0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
   }
    /* Check if the user has configured mode rule check for CDI service */
   if((isConditionChkflag_b ==  TRUE)&&(retVal_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00u) && (Dcm_CdiModeRuleRef_pf != NULL_PTR))
    {
        /* Call the mode rule API for mode rule check */
        isModeChkRetval_b = (*Dcm_CdiModeRuleRef_pf) (dataNegRespCode_u8);
        /* If the mode rule returns TRUE with NRC set to 0x00 */

        if  (( isModeChkRetval_b == TRUE ) && (*dataNegRespCode_u8 == 0u ))
        {
            /* Change the state to clear DTCs */
            *OpStatus = DCM_PROCESSSERVICE;
        }
        else
        {
            /* If the application has not updated the NRC when mode rule is returns FALSE */
            if(*dataNegRespCode_u8 == 0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
    }

#endif
}
 /**
 **************************************************************************************************
 * Dcm_Dsp_CDIIni : Initialisation function for CDI Service
 *
 * \param           void
 *
 * \retval          void
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_CDIIni(void)
{

    /* Call the API Dem_DcmCancelOperation if the state is not in INIT */
    if(Dcm_SrvOpstatus_u8 != DCM_INITIAL)
    {
        Dem_DcmCancelOperation();
    }

    /* Set CDI state to DCM_CDI_INIT */
    Dcm_SrvOpstatus_u8 = DCM_INITIAL;

}

/**
 **************************************************************************************************
 * Dcm_DcmClearDiagnosticInformation :
 * This service is used to clear diagnostic information.
 * This function is called by DSD, when SID is 0x14,
 * this service is provided in DSP module and configured in DCM identifier table.
 * When the DSP receives such a request it executes DEM function Dem_ClearDTC with
 * parameter DTCGroup equal to the value received in the request to remove either
 * one DTC or a group of DTCs and all related information from the fault memory.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 *  * \return value     Std_ReturnType :   E_OK : DTC cleared successful
 *                                         E_NOT_OK : DTC cleared failed
 *                                         E_PENDING : Need more time, call again
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmClearDiagnosticInformation (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,\
                                                                 P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
                                                                 P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    /* Initialization of local variables */
    *dataNegRespCode_u8   = 0x0u;
     s_dataRetVal_u8 = DCM_E_PENDING;

     /* If OpStatus is set to cancel then call the Ini Function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        Dcm_Dsp_CDIIni();

        /* Return E_OK as Ini function wil lalways be serviced */
        s_dataRetVal_u8 = E_OK;
    }

    else
    {
        /* If OpStatus is set to initial  then call the Dcm_PrivDTCLengthCheckFunction to check request length and DTC type check */
        if (Dcm_SrvOpstatus_u8 == DCM_INITIAL)
        {
            Dcm_PrivDTCLengthCheck(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);

        }
        /* If OpStatus is set to check data  then call the DCM_PrivDTCConditionCheck func to check user condition function or mode rule check for DTC */
        if (Dcm_SrvOpstatus_u8 == DCM_CHECKDATA)
        {
            DCM_PrivDTCConditionCheckfunc(&Dcm_SrvOpstatus_u8,dataNegRespCode_u8);

        }

        /* If OpStatus is set to process service then call the Dcm_PrivClearDTCInformation func to clear  user DTC information and
        set positive response if DTC cleared successsfully */
        if (Dcm_SrvOpstatus_u8 == DCM_PROCESSSERVICE)
        {
            Dcm_PrivClearDTCInformation(&Dcm_SrvOpstatus_u8, pMsgContext, dataNegRespCode_u8);

        }

        /* If negative response code is set */
        if(*dataNegRespCode_u8 != 0x0u)
        {
            s_dataRetVal_u8 = E_NOT_OK;
            /* Set response length to 0 */
            pMsgContext->resDataLen = 0x0u;
            /* Reset the state machine */
            Dcm_SrvOpstatus_u8 = DCM_INITIAL;

        }
    }

    return s_dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)*/

