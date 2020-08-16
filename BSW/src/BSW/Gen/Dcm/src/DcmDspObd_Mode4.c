

#include "DcmDspObd_Mode4_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode4_Priv.h"


#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspObdMode04Type_ten,DCM_VAR) Dcm_stDspObdMode04State_en;   /* Variable to store the state of OBD service 0X04 */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 **************************************************************************************************
 * Dcm_DcmObdMode04_Ini : Initialisaton function for OBD Mode 0x04 service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DcmObdMode04_Ini(void)
{
	/* Call the API Dem_DcmCancelOperation if the state is not INIT/UNINIT */
    if((Dcm_stDspObdMode04State_en != DCM_DSP_MODE04_INIT) && (Dcm_stDspObdMode04State_en != DCM_DSP_MODE04_UNINIT))
    {
    	Dem_DcmCancelOperation();
    }
    /* Initialisation of OBD Service 0x04 state to INIT state  */
    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
}


/**
 **************************************************************************************************
 * Dcm_DcmOBDMODE04 :
 * This OBD service is used to clear all emission related diagnostic information.
 * This function is called by DSD, when SID is 0x04,
 * this service is provided in DSP module and configured in DCM identifier table.
 * When the DSP receives such a request it executes DEM function Dem_ClearDTC with
 * parameter DTCGroup Emission related DTCs and all related information from the fault memory.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmObdMode04 (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Dcm_ReturnClearDTCType_tu8,AUTOMATIC) dataDemClrRetVal_u8;      /* for temporary storage of the DEM return values (enum) */
    VAR(Std_ReturnType,AUTOMATIC) stObdMode04Appl_u8;            /* check conditions for OBD Mode 04 */
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;            /* check conditions for OBD Mode 04 */
    *dataNegRespCode_u8   = 0x0u;                  /* Initialisation of local variables */
    dataDemClrRetVal_u8 = DEM_CLEAR_OK;
    stObdMode04Appl_u8 = E_NOT_OK;
    dataRetVal_u8=E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_DcmObdMode04_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    {
        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_INIT)
        {
            /* Check if the request Data Length is equal to 0 */
            if(pMsgContext->reqDataLen == DCM_OBDMODE04_REQ_LEN)
            {
                /* check whether the conditions like ignition is ON, engine is not running are satisfied
                this check is done by APPL function call DcmAppl_OBD_Mode04() */
                stObdMode04Appl_u8 = DcmAppl_OBD_Mode04();

                /* if the above conditions are satisfied then application function DcmAppl_OBD_Mode04() returns E_OK
                if the conditions are not satisfied then application function returns E_NOT_OK*/
                if(stObdMode04Appl_u8 == E_OK)
                {
                    /* Update the OBD MODE 04 state to call DEM */
                    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_CLEAR;
                }
                else
                {
                    /*Set Negative response code */
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            else
            {
                /*Set Negative response code Request Length Invalid
                NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing*/
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                /*report development error "INVALID LENGTH" to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_INVALID_LENGTH)
            }
        }

        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_CLEAR)
        {
            /* Request DEM to clear all emission related diagnostic information
               Parameter to Dem_ClearDTC are DTCGROUP is group of emission related DTCS,
                                             DTCFORMATTYPE is the format of DTCS
                                             DTCORIGIN is DTCS in primary memory*/

            dataDemClrRetVal_u8 = Dem_ClearDTC( DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_FORMAT_OBD,
                                                      DEM_DTC_ORIGIN_PRIMARY_MEMORY);

            switch(dataDemClrRetVal_u8)
            {
                /* if the clearing of emission related diagnostic information is successful */
                case (Dem_ReturnClearDTCType)DEM_CLEAR_OK:
                {
                    /* reset the state machine */
                    Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
                    dataRetVal_u8=E_OK;
                    break;
                }
                /* If DEM needs more time to clear the information */
                case (Dem_ReturnClearDTCType)DEM_CLEAR_PENDING:
                {
                    /* Remain in the same state */
                    dataRetVal_u8=DCM_E_PENDING;
                    break;
                }
                /* If the wrong DTC or the DTC origin is incorrect or some problems in DEM or error when writing to a memory location  */
                case (Dem_ReturnClearDTCType)DEM_CLEAR_WRONG_DTC:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_WRONG_DTCORIGIN:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_FAILED:
                case (Dem_ReturnClearDTCType)DEM_CLEAR_MEMORY_ERROR:
                default:
                {
                    /*Report DET error that Parameter passed to DEM interface are incorrect*/
                    DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_PARAM)
                    *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT; /* Set NRC 0x22*/
                    break;
                }
            }
        }

        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_UNINIT)
        {
            /*report development error "DCM uninitialised" to DET module if the DET module is enabled */
            DCM_DET_ERROR(DCM_OBDMODE04_ID, DCM_E_UNINIT)
            /*in order to avoid the Dcm layer to call this service handler once again,
            send negative response 0x12 and due to functional addressing this negative response
            is suppressed hence no response is sent by ECU */
            /* Call function to set Negative response code */
            *dataNegRespCode_u8  = DCM_E_SUBFUNCTIONNOTSUPPORTED; /* Set NRC 0x12*/;
        }
     }

        /* If negative response code is set */
        if(*dataNegRespCode_u8 != 0x0u)
        {
            /* reset the state machine */
            Dcm_stDspObdMode04State_en = DCM_DSP_MODE04_INIT;
            dataRetVal_u8=E_NOT_OK;
        }
        if(Dcm_stDspObdMode04State_en == DCM_DSP_MODE04_INIT)
        {
            pMsgContext->resDataLen = 0x0u; /* Set response length to 0 */

        }

    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

