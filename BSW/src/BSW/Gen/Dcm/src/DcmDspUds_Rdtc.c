

#include "DcmDspUds_Rdtc_Inf.h"
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Priv.h"
#include "Rte_Dcm.h"
#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( uint32,                     DCM_VAR )  Dsp_RdtcDTC_u32;       /* Variable to store DTC */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( Dcm_DspRDTCStates_ten,         DCM_VAR )  Dcm_DspRDTCState_en;    /* Global variable to store RDTC state */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( Dcm_DspRDTCSubFuncStates_ten, DCM_VAR )  Dcm_DspRDTCSubFunc_en;  /* State variable for subfunction state */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint8, DCM_VAR ) Dcm_idxDspRDTCTab_u8;         /* Variable for Table index  */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF) || \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint16,          DCM_VAR ) Dcm_DspMaxResDataLen_u16;  /* storage for response length that can be filled */
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,          DCM_VAR ) Dcm_DspRDTCRecordNum_u8; /* variable to store the record number */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_MsgLenType, DCM_VAR)  Dcm_DspRDTCMaxRespLen_u32;    /* Maximum response length */
VAR(Dcm_MsgLenType, DCM_VAR)  Dcm_DspRDTCFilledRespLen_u32;/* Response length filled */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint16,         DCM_VAR)  Dcm_DspNumFltDTC_u16;         /* Number of filtered DTC's */
VAR(uint16,         DCM_VAR)  Dcm_DspTotalRespLenFilled_u16;/* Variable to store total response length filled */
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean,        DCM_VAR)  Dcm_DspFirstPageSent_b;       /* Whether first page is sent or not? */
VAR(boolean,        DCM_VAR)  Dcm_DspFillZeroes_b;          /* Variable to check if zero's needs to be filled in page */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_MsgType,    DCM_VAR)  Dcm_DspRDTCRespBufPtr_u8;     /* Pointer to the response buffer */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_ReadDTCInfo_Ini :
 *  In this function initialisation of RDTC service is done.
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_ReadDTCInfo_Ini (void)
        {
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
    VAR(Std_ReturnType,AUTOMATIC) dataRetEnableDTCRecUpdate_u8;                /*Return Value of DEM API*/
#endif
    Dem_DcmCancelOperation();
    /* Reset RDTC Service state machine */
    Dcm_DspRDTCState_en = DSP_RDTC_INIT;

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF)|| \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
    /* If the init is called due to General reject response or protocol preemption
       and the record update is disabled then enable record update */
    dataRetEnableDTCRecUpdate_u8 = Dem_EnableDTCRecordUpdate();
    /* Return value from the function need not be minded */
    (void)dataRetEnableDTCRecUpdate_u8;
#endif
#if ((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    /* If init function is called , update page function pointer is
       configured as NULL_PTR */
    Dcm_adrUpdatePage_pfct = NULL_PTR;
#endif
        }


/**
 *******************************************************************************
 * Dcm_Prv_DspReadDTCInfoConfirmation : API used for confirmation of response 
 *                                   sent for ReadDTCInformation (0x19) Service.
 * \param           dataIdContext_u8    Service Id
 * \param           dataRxPduId_u8      PDU Id on which request is Received
 * \param           dataSourceAddress_u16    Tester Source address id
 * \param           status_u8                   Status of Tx confirmation function
 *
 * \retval          None
 * \seealso
 *
 *******************************************************************************
 */
FUNC(void, DCM_CODE) Dcm_Prv_DspReadDTCInfoConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && \
                                (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
				/* Set the state of main state machine to Initialized state */
                Dcm_Dsp_ReadDTCInfo_Ini();
#endif
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,
											dataSourceAddress_u16,status_u8);
}

/**
 **************************************************************************************************
 * Dcm_DcmReadDTCInformation :
 *  This service with its subfunction does the following.
 *  SubFunc 0x02: Report DTCs with the associated status information matching a specific status
 *                mask, memory location and DTC type
 *  SubFunc 0x0A: Report DTCs with the associated status information for all DTC's in a server
 *
 * \param           pMsgContext    Pointer to message structure
 *                                 (input : RequestLength, Response buffer size, request bytes)
 *                                 (output: Response bytes and Response length )
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadDTCInformation (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
        {
    VAR(uint8,AUTOMATIC)               dataRDTCSubFunc_u8;        /* Local variable to store the subfunction */
    /* local pointer to sub-service configuration structure*/
    P2CONST(Dcm_Dsld_SubServiceType,AUTOMATIC,DCM_INTERN_CONST) adrSubservice_pcst;
    VAR(Std_ReturnType,                   AUTOMATIC)  dataServRetval_u8;

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    if(pMsgContext->msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
    {

        adrSubservice_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldRoe2_pcst->servicetable_Id_u8].ptr_service_table_pcs[Dcm_DsldSrvIndex_u8].ptr_subservice_table_pcs;
    }
    else
#endif
    {
        /* get the active service configuration structure */
        adrSubservice_pcst = (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8]).ptr_subservice_table_pcs;
    }
    /* Initialization to zero - No error */
    *dataNegRespCode_u8 = 0x00;
    dataServRetval_u8=DCM_E_PENDING;

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_ReadDTCInfo_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataServRetval_u8 = E_OK;
    }
    else
    {
        /* RDTC State machine */
        /* Initialisation state */
        if (Dcm_DspRDTCState_en == DSP_RDTC_INIT)
        {
            /* Copy the subfunction parameter to local variable */
            dataRDTCSubFunc_u8 = pMsgContext->reqData[DSP_RDTC_POSSUBFUNC];

            /* loop through the configured subfunctions */
			Dcm_idxDspRDTCTab_u8=0; 
            while((Dcm_idxDspRDTCTab_u8 < DCM_CFG_NUMRDTCSUBFUNC) )
            {
                /* If the subfunction sent from tester if found in configuration */
                if(adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].subservice_id_u8 == dataRDTCSubFunc_u8)
                {
                    /* Sub function configured */
                    break;
                }
            Dcm_idxDspRDTCTab_u8++;
            }
            /* If the subfunction sent is not configured */
            if(Dcm_idxDspRDTCTab_u8 >= DCM_CFG_NUMRDTCSUBFUNC)
            {
                /* Set Negative response code */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                dataServRetval_u8=E_NOT_OK;
            }
            else
            {
                /* Switch the RDTC state to call service only for Dsp RDTC functions*/
                /*Check if call function for the configured subfunction is Dsp RDTC function or not */
                if(adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b != FALSE)
                {
                    /* Initialize the RDTC Subfunction state */
                    Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
                    /* Move the RDTC state to next state where the service is called */
                    Dcm_DspRDTCState_en = DSP_RDTC_CALLSERVICE;
                }
            }
        }
        /* State to call the service for the subfunction */
        /*If RDTC sate to next state where the service handler is called and function for call service is Dsp RDTC function or not*/
        if ((Dcm_DspRDTCState_en == DSP_RDTC_CALLSERVICE) ||	\
                ((Dcm_idxDspRDTCTab_u8 < DCM_CFG_NUMRDTCSUBFUNC) && (adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b == FALSE)))
        {
            /* Call the function for the sub function */
            dataServRetval_u8=(*adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].SubFunc_fp)(OpStatus,pMsgContext,dataNegRespCode_u8);
        }

        /* If Negative response code is set */
        /*Check if the function for call subfunction is Dsp RDTC function or not*/
        if((Dcm_idxDspRDTCTab_u8 >= DCM_CFG_NUMRDTCSUBFUNC)||((*dataNegRespCode_u8 != 0) && (adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b != FALSE)))
        {
            /* Move the state to default state */
            Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFINIT;
        }
        /* If the state is the default state */
        /*If RDTC state is in Default state after Initialisation and the function for call subfunction is Dsp RDTC function or not*/
        if((Dcm_idxDspRDTCTab_u8 >= DCM_CFG_NUMRDTCSUBFUNC)||((Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFINIT) && (adrSubservice_pcst[Dcm_idxDspRDTCTab_u8].isDspRDTCSubFnc_b != FALSE)))
        {
            /* Reset RDTC Service state machine */
            Dcm_DspRDTCState_en = DSP_RDTC_INIT;
        }
    }
    return dataServRetval_u8;
        }


#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF) &&\
        ((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)||\
                (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF) ||\
                (DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF) ||\
                (DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED != DCM_CFG_OFF) ||\
                /* FC_VariationPoint_START */ \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)||\
        /* FC_VariationPoint_END */ \
        (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)||\
        (DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF)||\
        (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)))
/**
 **************************************************************************************************
 * Dcm_Dsp_RDTCUpdatePage :
 *  This function is used to update the Page length and the Response buffer pointer .
 *
 * \param           PageBufPtr    Pointer to response buffer
 *                  PageLen       Page length which can be filled
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_RDTCUpdatePage(
        VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr,
        VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
)
{
    if(PageBufPtr != NULL_PTR)
    {
        /* If the RDTC state is DSP_RDTC_SFTXPAGE */
        if (Dcm_DspRDTCSubFunc_en == DSP_RDTC_SFTXPAGE)
        {
            /* Check if the next page should be filled with DTC information or zero's */

            if (Dcm_DspFillZeroes_b == FALSE)
            {
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLRESP;
            }
            else
            {
                Dcm_DspRDTCSubFunc_en = DSP_RDTC_SFFILLZERO;
            }

        }
        /* Update the Response length and the Response buffer pointer */
        Dcm_DspRDTCMaxRespLen_u32 = PageLen;
        Dcm_DspRDTCRespBufPtr_u8 = PageBufPtr;
    }
    else
    {
        /* DET ERROR REPORT */
        DCM_DET_ERROR(DCM_RDTC_ID, DCM_E_PARAM_POINTER);
    }
}



/**
 **************************************************************************************************
 * Dcm_Dsp_RDTCFillZero :
 *  This function is used in paged buffering to fill the  free space in  page buffer with Zeros.\n
 *
 * \param           RemTotalResLen    Remaining response bytes
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */


FUNC(void,DCM_CODE) Dcm_Dsp_RDTCFillZero(VAR(Dcm_MsgLenType,AUTOMATIC) RemTotalResLen )
        {
    VAR(uint32_least, AUTOMATIC) nrResLen_qu32 ;      /* Variable pointing to location to fill zeroes */
    VAR(uint32_least, AUTOMATIC) dataRemBuffer_qu32;    /* Variable to store available free space in buffer */
    /*Initialize Dcm_DspFillZeroes_b is to TRUE*/
    Dcm_DspFillZeroes_b = TRUE;
    /*Calculate the remaining available buffer */
    dataRemBuffer_qu32 = Dcm_DspRDTCMaxRespLen_u32 - Dcm_DspRDTCFilledRespLen_u32;

    /* If buffer is not full */
    if(RemTotalResLen !=0u)
    {
        /* Check if the remaining response bytes is greater than the available page size */
        if(RemTotalResLen > dataRemBuffer_qu32)
        {
            RemTotalResLen   = dataRemBuffer_qu32;
        }
        dataRemBuffer_qu32 = RemTotalResLen+Dcm_DspRDTCFilledRespLen_u32;

        /* Filling the page with zero's till the page is full or the total response is filled */
        for(nrResLen_qu32=Dcm_DspRDTCFilledRespLen_u32; nrResLen_qu32< dataRemBuffer_qu32; nrResLen_qu32++)
        {
            Dcm_DspRDTCRespBufPtr_u8[nrResLen_qu32] = 0x0;
        }

        /* Updating the total response length filled */
        Dcm_DspTotalRespLenFilled_u16 = (uint16)(Dcm_DspTotalRespLenFilled_u16 + (uint16)RemTotalResLen);
        /* Updating the filled response length in the page */
        Dcm_DspRDTCFilledRespLen_u32 += RemTotalResLen;
    }
        }


/**
 **************************************************************************************************
 * Dcm_IsProtocolIPCanFD : API called to get active protocol on which the paged buffer request is received.
 * The API returns TRUE in case of CANFD/IP/SUPPLIER SPECIFIC PROTOCOLS and FALSE in other cases
 * is
 *
 * \param           None
 *
 *
 * \retval          Boolean
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(boolean,DCM_CODE) Dcm_IsProtocolIPCanFD(void)
        {
    VAR(Dcm_ProtocolType,AUTOMATIC) activeProtocol_u8;

    VAR(boolean,AUTOMATIC) retValue_b;
    /*Initialize retValue_b is to value TRUE */
    retValue_b= TRUE;
    /* Get the running protocol */
    if(E_OK ==  Dcm_GetActiveProtocol(&activeProtocol_u8))
    {
        /* If the function returns E_OK */
        if(activeProtocol_u8!=DCM_NO_ACTIVE_PROTOCOL)
        {

            /* Return TRUE if active protocol is over CANFD */
            if ((DCM_CFG_CANFD_ENABLED==DCM_CFG_OFF)&&((activeProtocol_u8==DCM_UDS_ON_CAN)||(activeProtocol_u8==DCM_ACEA_ON_CAN)||(activeProtocol_u8==DCM_KWP_ON_CAN)
                    /* FC_VariationPoint_START */
                    || (activeProtocol_u8==DCM_OBD_ON_CAN)
                    /* FC_VariationPoint_END */
            ))
            {
                /*Set the value for retValue_b is to FALSE*/
                retValue_b= FALSE;
            }
            else if ((activeProtocol_u8==DCM_UDS_ON_FLEXRAY)||(activeProtocol_u8==DCM_ACEA_ON_FLEXRAY)
                    /* FC_VariationPoint_START */
                    || (activeProtocol_u8==DCM_OBD_ON_FLEXRAY)
                    /* FC_VariationPoint_END */
            )
            {
                /*Set the value for retValue_b is to FALSE*/
                retValue_b= FALSE;
            }
            else
            {
                /* Do nothing */
            }
        }
    }
    return (retValue_b);
        }

#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#endif

