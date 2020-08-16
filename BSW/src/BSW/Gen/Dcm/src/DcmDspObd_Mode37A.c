

#include "DcmDspObd_Mode37A_Inf.h"

#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#include "DcmDspObd_Mode37A_Priv.h"

#if(DCM_CFG_DSP_OBDMODE37A_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_DcmOBDMODE37A :
 * This OBD service is used to obtain all emission related confirmed, pending and permanent diagnostic information.
 * OBD service 0x03 is used to obtain confirmed DTCs.
 * OBD service 0x07 is used to obtain pending DTCs.
 * OBD service 0x0A is used to obtain permanent DTCs.
 * This function is called by DSD, when SID is 0x03 or 0x07 or 0x0A,
 * this service is provided in DSP module and configured in DCM identifier table.
 * DEM function Dem_SetDTCFilte is used to set the filter mask and function Dem_GetNextFilteredDTC is used
 * to extract corresponding Emission related DTCs.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmObdMode37A (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    VAR(uint32_least,   AUTOMATIC)  cntrLoop_qu32;            /* variable for loop counter */
    VAR(uint32,        AUTOMATIC)  dataMode37ADtc_u32;       /* Variable to store DTC */
    VAR(Dcm_MsgLenType,AUTOMATIC)  nrResMaxDataLen_u32;     /* Variable to store max response length */
    VAR(Dcm_MsgLenType,AUTOMATIC)  nrResDTCDataLen_u32;     /* Local variable number of DTCs and response length */
    VAR(uint8,         AUTOMATIC)  dataDTCStatusMask_u8;      /* variable for DTCStatusMask for different modes */
    VAR(Dem_DTCOriginType,AUTOMATIC)    dataDTCOrigin_u8;     /* variable for DTCOrigin for different modes */
    VAR(Dem_ReturnSetFilterType,AUTOMATIC) dataRetSetDTCFilter_u8;   /* Return type for Dem_SetDTCFilter */
    VAR(uint8,       AUTOMATIC)     stMode37ADTC_u8;           /* Variable to store the DTC status */
    VAR(Dem_ReturnGetNextFilteredDTCType,AUTOMATIC)   dataRetGetNextFilt_u8; /* Return type for Dem_GetNextFilteredDTC */
    VAR(Std_ReturnType,         AUTOMATIC)  dataRetVal_u8;      /* variable for Return value */

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);
    *dataNegRespCode_u8     = 0x0u;                  /* Initialisation of local variables */

    /* Initilization of DTC status mask and DTC origin for OBD service 0x03 */
    dataDTCStatusMask_u8  = 0x08;
    dataDTCOrigin_u8      = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
    dataRetVal_u8=E_NOT_OK;

    /* Check if the request Data Length is equal to 0 */
    if(pMsgContext->reqDataLen == DCM_OBDMODE37A_REQLEN)
    {
        /* Copy the Maximum response length into local variable */
        nrResMaxDataLen_u32 = pMsgContext->resMaxDataLen;

        switch(pMsgContext->idContext)
        {
            case 0x03u:
            {
                /* Request for confirmed emission related DTCs */
                /* Set the DTC Filter for OBD service 0x03 */
                /* DTC status mask and DTC origin for OBD service 0x03 */
                dataDTCStatusMask_u8 = 0x08;
                dataDTCOrigin_u8     =  DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x07u:
            {
                /* Request for confirmed emission related DTCs */
                /* Set the DTC Filter for OBD service 0x07 */
                /* DTC status mask and DTC origin for OBD service 0x03 */
                dataDTCStatusMask_u8 = 0x04;
                dataDTCOrigin_u8     =  DEM_DTC_ORIGIN_PRIMARY_MEMORY;
                break;
            }
            case 0x0Au:
            {
                /* Request for confirmed emission related DTCs */
                /* Set the DTC Filter for OBD service 0x0A */
                /* DTC status mask and DTC origin for OBD service 0x03 */
                dataDTCStatusMask_u8 = 0x00;
                dataDTCOrigin_u8     = DEM_DTC_ORIGIN_PERMANENT_MEMORY;
                break;
            }
            default:
            {
                /* NRC 0x12 is sent if the SID is other than 0x03 or 0x07 or 0x0A */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                break;
            }
        }
        /* Stop processing the request in case of any Negative response code */
        if(*dataNegRespCode_u8 == 0x0)
        {
            dataRetSetDTCFilter_u8 = Dem_SetDTCFilter( dataDTCStatusMask_u8,
                                                   DEM_DTC_KIND_EMISSION_REL_DTCS,
                                                   DEM_DTC_FORMAT_OBD,
                                                   dataDTCOrigin_u8,
                                                   DEM_FILTER_WITH_SEVERITY_NO,
                                                   DEM_SEVERITY_NO_SEVERITY,
                                                   DEM_FILTER_FOR_FDC_NO
                                                 );

            if(dataRetSetDTCFilter_u8 == DEM_FILTER_ACCEPTED)
            {
                /* Filter mask accepted by DEM */
                /* Response length will be at least 1 byte if no matched DTCs are found */
            	nrResDTCDataLen_u32 = 1;

                /* Restrict the for loop for Max number of DTC than can be fit in with the available buffer size */
                nrResMaxDataLen_u32 = nrResMaxDataLen_u32>>1u;

                for(cntrLoop_qu32=0x0u; ((cntrLoop_qu32 < nrResMaxDataLen_u32) && (*dataNegRespCode_u8 == 0x0u)); cntrLoop_qu32++)
                {
                    /* Get the filtered DTC */
                    dataRetGetNextFilt_u8 = Dem_GetNextFilteredDTC(&dataMode37ADtc_u32, &stMode37ADTC_u8);

                    if(dataRetGetNextFilt_u8 == DEM_FILTERED_OK)
                    {
                        /* Fill the response buffer with DTC and status */
                        pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 16uL);
                        nrResDTCDataLen_u32++;
                        pMsgContext->resData[nrResDTCDataLen_u32] = (uint8)(dataMode37ADtc_u32 >> 8uL);
                        nrResDTCDataLen_u32++;
                    }
                    else if(dataRetGetNextFilt_u8 == DEM_FILTERED_NO_MATCHING_DTC)
                    {
                        /* All the matched DTCs are read */
                        /* Fill first byte of response buffer with the number of DTCs */
                        /* one DTC is of length 2 bytes */
                        pMsgContext->resData[0] = (uint8)nrResDTCDataLen_u32 >> 1uL;
                        dataRetVal_u8=E_OK;
                        /* break loop operation if no further matching DTCs are found */
                        break;
                    }
                    else
                    {
                        /* NRC 0x12 is sent, problems has occurred in DEM while reading DTC */
                        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                        DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_RET_E_NOT_OK)

                    }
                }
                /* Update the response length */
                pMsgContext->resDataLen = nrResDTCDataLen_u32;
            }
            else
            {
                /* NRC 0x12 is sent if the filter mask is not accepted DEM */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_PARAM)
            }
        }
    }
    /* Request Length not correct */
    else
    {
        /* Set Negative response code
        NRC 0x12 is suppressed in DCM module for OBD service since its functional addressing */
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        DCM_DET_ERROR(DCM_OBDMODE37A_ID, DCM_E_INVALID_LENGTH)
    }

    /* If Negative response is set */
    if(*dataNegRespCode_u8 !=0)
    {
        dataRetVal_u8=E_NOT_OK;
    }

    return dataRetVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
