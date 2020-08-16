/* BASDKey_start */

/* BASDKey_end */
/* Administrative Information (automatically filled in)
 * $Domain____:BASD$
 * $Namespace_:\Comp\Dcm$
 * $Class_____:C$
 * $Name______:DcmDspUds_Iocbi$
 * $Variant___:AR40.11.0.0$
 * $Revision__:1$
 **********************************************************************************************************************
 </BASDKey>*/

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "DcmDspUds_Iocbi_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Iocbi_Priv.h"

/*
 **********************************************************************************************************************
 * Globals
 **********************************************************************************************************************
 */
/* Index of the requested DID in the array Dcm_DspUDS_IOCBI_DIDs_a */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* State machine control variable for IOCBI service */
static VAR(Dcm_DspIOCBIStates_ten, DCM_VAR) Dcm_stDspIocbiState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8, DCM_VAR) Dcm_dataDspIocbiCtrlParam_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_OpStatusType, DCM_VAR) Dcm_stDspIocbiOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR (Dcm_DIDIndexType_tst,DCM_VAR) s_Dcm_idxIocbiDidIndexType_st; /*Store the index of DID of either Dcm_DidConfig or Dcm_DIDRangeCOnfig structure*/
static VAR (uint16,DCM_VAR) s_ActiveDid_u16;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (uint16,DCM_VAR) Dcm_ReadSignalLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean, DCM_VAR) s_IsIOCBISubfuncCalled_b;
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
static VAR (boolean,DCM_VAR) s_IocbiRteCallPlaced_b; /* Variable to hold whether RTE call is placed for async client server*/
#endif
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
static VAR (boolean,DCM_VAR) s_DcmReadLengthRteCallPlaced_b; /* Variable to indicate whether Rte_Call API is invoked for ReadLength call */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **********************************************************************************************************************
 Array for storing Active IOCBI DIDs and their active status
 **********************************************************************************************************************
 **/
#if(DCM_CFG_NUM_IOCBI_DIDS != 0x0)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_Dsp_IocbiStatusType_tst,DCM_VAR) DcmDsp_IocbiStatus_array[DCM_CFG_NUM_IOCBI_DIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/* Length of Control option record */

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **********************************************************************************************************************
 * Dcm_Dsp_IOCBI_Ini :
 *  This function initializes the Input Output Control by Identifier Service to DCM_IOCBI_IDLE.
 *  This function has to be called by DSLDSD during a protocol start and before any service request.
 *
 * \param           :None
 * \return          :None
 * \retval          :Not Applicable
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_IOCBI_Ini(void)
{
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8; /* Negative response code indicator */
    VAR(Std_ReturnType,AUTOMATIC) dataRetIocbiFunc_u8;
    VAR(uint16_least,AUTOMATIC) idxIocbiIndex_u16; /*Index to loop through the IOCBI status array DcmDsp_IocbiStatus_array*/

#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
    VAR(uint8 ,AUTOMATIC) ControlMask_u8;
    VAR(uint16 ,AUTOMATIC) ControlMask_u16;
    VAR(uint32 ,AUTOMATIC) ControlMask_u32;
    ControlMask_u8 = 0;
    ControlMask_u16 = 0;
    ControlMask_u32 = 0;
#endif
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrIOSigConfig;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidExtendedConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA) ptrIOCBIFnc;
    VAR(uint16_least ,AUTOMATIC) idxDidSignal_u16;
    idxDidSignal_u16 = 0;

    /*Initialising local variables*/
    dataNegResCode_u8 = 0x00;
    dataRetIocbiFunc_u8 = 0x00;
    ptrDidConfig = NULL_PTR;
    ptrSigConfig = NULL_PTR;
    ptrIOSigConfig = NULL_PTR;
    ptrIOCBIFnc = NULL_PTR;


    /* To call cancellation of SWCD operation in case API was called with Opstatus as DCM_PENDING */
#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
    if (Dcm_stDspIocbiOpStatus_u8 == DCM_PENDING)
    {
        ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        ptrIOSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
        ptrDidExtendedConfig = ptrDidConfig->adrExtendedConfig_pcst;

        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
        if ((ptrSigConfig->idxDcmDspControlInfo_u16 > 0) && (ptrIOSigConfig->idxDcmDspIocbiInfo_u16 > 0))
        {
            /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
            s_IsIOCBISubfuncCalled_b = TRUE;
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT) && ((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x08u)==0x08u))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;
                /* Check if the Control function is configured */
                if((ptrIOCBIFnc!= NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Short Term Adjustment was requested */
                            /* Call the Rte_Call API with In and Inout parameter to cancel the ongoing operation */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8=(*(ShortTermAdjustment9_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            /*add with control mask*/
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment10_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment11_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment12_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Short Term Adjustment was requested */
                            /* Call the configured API  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetIocbiFunc_u8=(*(ShortTermAdjustment2_pfct)(ptrIOCBIFnc))  (NULL_PTR,DCM_CANCEL, &dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            /*add with control mask*/
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment6_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment7_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ShortTermAdjustment8_pfct)(ptrIOCBIFnc)) (NULL_PTR,DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }
                }
            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE) && ((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x04u)==0x04u ))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;
                /* Check if the Control function is configured */
                if((ptrIOCBIFnc != NULL_PTR) &&  ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Freeze current state was requested */
                            /* Invoke the Generated Rte_Call API to cancel the pending operation */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8=(*(FreezeCurrentState9_pfct)(ptrIOCBIFnc)) (DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            /*add with control mask*/
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Freeze current state was requested */
                                /* Invoke the Generated Rte_Call API to cancel the pending operation */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState10_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Freeze current state was requested */
                                /* Invoke the Generated Rte_Call API to cancel the pending operation */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState11_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {
                                /* Freeze current state was requested */
                                /* Invoke the Generated Rte_Call API to cancel the pending operation */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState12_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Freeze current state was requested */
                            /* Call the configured API  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetIocbiFunc_u8=(*(FreezeCurrentState2_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, &dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            /*add with control mask*/
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState6_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState7_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(FreezeCurrentState8_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }
                }
            }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED == DCM_CFG_ON)
            if((Dcm_dataDspIocbiCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT) && ((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x02u)==0x02u ))
            {
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;
                /* Check if the Control function is configured */
                if((ptrIOCBIFnc != NULL_PTR) &&   ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                {
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED == DCM_CFG_ON)
                    if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Reset to Default value was requested */
                            /* Call the generated Rte_call  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8 = (*(ResetToDefault9_pfct) (ptrIOCBIFnc))(DCM_CANCEL);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            /*add with control mask*/
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Reset to Default value was requested */
                                /* Call the generated Rte_call  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ResetToDefault10_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Reset to Default value was requested */
                                /* Call the generated Rte_call  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ResetToDefault11_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16);
                            }
                            else
                            {
                                /* Reset to Default value was requested */
                                /* Call the generated Rte_call  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ResetToDefault12_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32);
                            }
#endif
                        }
                    }
                    else
#endif
                {
                    if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                    {
                        /* Reset to Default value was requested */
                        /* Call the configured API  with Opstatus as DCM_CANCEL */
                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetIocbiFunc_u8 = (*(ResetToDefault2_pfct) (ptrIOCBIFnc))(DCM_CANCEL, &dataNegResCode_u8);
                    }
                    else
                    {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                        /*add with control mask*/
                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                        {
                            /* Short Term Adjustment was requested */
                            /* Call the configured API  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8=(*(ResetToDefault6_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u8,&dataNegResCode_u8);
                        }
                        else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                        {
                            /* Short Term Adjustment was requested */
                            /* Call the configured API  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8=(*(ResetToDefault7_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u16,&dataNegResCode_u8);
                        }
                        else
                        {
                            /* Short Term Adjustment was requested */
                            /* Call the configured API  with Opstatus as DCM_CANCEL */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8=(*(ResetToDefault8_pfct)(ptrIOCBIFnc)) (DCM_CANCEL, ControlMask_u32,&dataNegResCode_u8);
                        }
#endif
                    }
                }
            }
            }
#endif
            /*subfunction called is not valid and reset to FALSE*/
            s_IsIOCBISubfuncCalled_b = FALSE;
            (void) dataRetIocbiFunc_u8;
        }
    }
#endif

    /*Loop through all the IOCBI DIDs through DcmDsp_IocbiStatus_array, this case is mainly to handle the issue of protocol preemption,
    to reset all the IOCTRLs which was active in the previos protocol before preemption*/
    for(idxIocbiIndex_u16=0u;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
    {
        ptrDidConfig =&Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];
        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16 ;
    }
    if (s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b == DCM_PENDING)
    {
        ptrSigConfig = &Dcm_DspDataInfo_st[Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
        /* If the read operation is Asynchronous */
        if((ptrSigConfig->adrReadFnc_cpv!=NULL_PTR) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)|| (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
        {
            /* Call the Read function with  Opstatus as DCM_CANCEL */
            /*subfunction called is valid and set to TRUE*/
            s_IsIOCBISubfuncCalled_b = TRUE;
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
			if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
			{
				/* Call the Rte_Call Read Function ot cancel the operation */
			    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
            	dataRetIocbiFunc_u8 = (*(ReadFunc11_ptr) (ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL);
			}
			else
#endif
			{
	            /* Call the Read function with  Opstatus as DCM_CANCEL */
	            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
	            dataRetIocbiFunc_u8 = (*(ReadFunc2_ptr) (ptrSigConfig->adrReadFnc_cpv))(DCM_CANCEL, NULL_PTR);
			}
				/*subfunction called is not valid and set to FALSE*/
            s_IsIOCBISubfuncCalled_b = FALSE;
            (void) dataRetIocbiFunc_u8;
        }
    }

    /* Initialize IOCBI Service state machine to IDLE state */
    Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
    Dcm_DidSignalIdx_u16 = 0x0;
    Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
		s_DcmReadLengthRteCallPlaced_b = FALSE;
#endif
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
	s_IocbiRteCallPlaced_b = FALSE;
#endif
    Dcm_ResetDIDIndexstruct(&s_Dcm_idxIocbiDidIndexType_st); /*This function is invoked to reset all the elements of DID index structure to its default value*/
    DCM_UNUSED_PARAM(dataNegResCode_u8);
    DCM_UNUSED_PARAM(idxIocbiIndex_u16);
    DCM_UNUSED_PARAM(Dcm_dataDspIocbiCtrlParam_u8);
    DCM_UNUSED_PARAM(ptrDidConfig);
    DCM_UNUSED_PARAM(ptrIOSigConfig);
    DCM_UNUSED_PARAM(ptrSigConfig);
    DCM_UNUSED_PARAM(ptrIOCBIFnc);
    DCM_UNUSED_PARAM(idxDidSignal_u16);
}

/**
 **********************************************************************************************************************
 * Dcm_DcmInputOutputControlbyIdentifier :
 *  Service Interpreter for Input Output Control by Identifier (0x2F) service.
 *  The InputOutputControlByIdentifier service is used by the client to substitute a value for an input signal,
 *  internal server function and/or force control to a value for an output (actuator) of an electronic system.
 *  There are four ways in which tester can make use of this service by sending the various values for
 *  Input Output Control Parameter in the request:
 *  0x00:   Return Control To ECU. This value shall indicate to the server that the client does no longer have
 *          control about the input signal(s), internal parameter(s) and/or output signal(s) referenced by the
 *          dataIdentifier.
 *  0x01:   This value shall indicate to the server that it is requested to reset the input signal(s), internal
 *          parameter(s) and/or output signal(s) referenced by the dataIdentifier to its default state.
 *  0x02:   This value shall indicate to the server that it is requested to freeze the current state of the
 *          input signal(s), internal parameter(s) and/or output signal referenced by the dataIdentifier.
 *  0x03:   This value shall indicate to the server that it is requested to adjust the input signal(s), internal
 *          parameter(s) and/or controlled output signal(s) referenced by the dataIdentifier in RAM to the value(s)
 *          included in the controlOption parameter(s) (e.g., set Idle Air Control Valve to a specific step number,
 *          set pulse width of valve to a specific value/duty cycle).
 *
 * \param   pMsgContext    Pointer to message structure
 *                                 (parameter in : RequestLength, Response buffer size, request bytes)
 *                                 (parameter out: Response bytes and Response length )
 *
 * \retval  None
 * \seealso
 *
 **********************************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmInputOutputControlByIdentifier(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,AUTOMATIC) dataLength_u32; /* Local variable of store length of DID */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrIOSigConfig;
    P2CONST(Dcm_SignalDIDIocbiConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrIOCBIsigConfig;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidExtendedConfig;
    P2VAR(Dcm_Dsp_IocbiStatusType_tst,AUTOMATIC, DCM_INTERN_DATA )ptrIOCBIStatusArrayConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA) ptrIOCBIFnc;
    VAR(uint16,AUTOMATIC) dataSignalLength_u16; /* Variable to hold the length of the signal*/
    VAR(uint16,AUTOMATIC) posnSigByte_u16;/* Signal Byte position*/
    VAR(uint16,AUTOMATIC) dataControlMaskLen_u16;
    VAR(uint16,AUTOMATIC) dataCtlMaskOffset_u16;/* Offset for control mask*/
    VAR(uint16,AUTOMATIC) nrDID_u16; /* Data Identifier */
    VAR(uint16_least,AUTOMATIC) idxIocbiIndex_u16; /*Index to loop through the IOCBI status array DcmDsp_IocbiStatus_array*/
    VAR(Std_ReturnType,AUTOMATIC) dataIocbiExeResult_u8; /* Return value of IOCBI execution function */
    VAR(Std_ReturnType,AUTOMATIC) dataRetGetDid_u8;
    VAR(Std_ReturnType,AUTOMATIC) dataValidateIoMaskStatus_u8; /* Return value for IOCBI Mask and Status Validation Appl */
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
#if((DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   != DCM_CFG_OFF) || (DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   != DCM_CFG_OFF) )
    VAR(uint8,AUTOMATIC) ControlMask_u8; /* Control Mask */
    VAR(uint16,AUTOMATIC) ControlMask_u16; /* Control Mask */
    VAR(uint32,AUTOMATIC) ControlMask_u32; /* Control Mask */
#endif
#endif
    VAR(uint8,AUTOMATIC) dataIoCtrlParam_u8; /* Input Output Control parameter */
    VAR(uint8,AUTOMATIC) posnSigBit_u8; /* Signal Bit position*/
    VAR(uint8,AUTOMATIC) posnCtlMaskByte_u8;/* Control mask Byte position*/
    VAR(uint8,AUTOMATIC) posnCtlMaskBit_u8; /* Control mask Bit position*/
    VAR(boolean,AUTOMATIC) isModeChkRetval_b; /*Return value of mode rule check API*/
    VAR(boolean, AUTOMATIC) flgProcessReq_b; /*Flag process request*/
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNrc_u8; /* Negative response code indicator */
    VAR(Std_ReturnType,AUTOMATIC)  dataretVal_u8;
    VAR(Std_ReturnType, AUTOMATIC) dataFuncRetVal_u8; /* Local variable to store function return value */
    VAR(Std_ReturnType,AUTOMATIC)  dataServretVal_u8;/* Local variable to store service return value */

    /* Initialization of local variables */
    *dataNegRespCode_u8 = 0x00;
    dataNrc_u8 = 0x00;
    dataIocbiExeResult_u8 = E_OK;
    /*Initialize the Process request flag to value TRUE*/
    flgProcessReq_b = TRUE;
    dataFuncRetVal_u8 = E_OK;
    dataServretVal_u8=DCM_E_PENDING;
    idxIocbiIndex_u16=0;

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_IOCBI_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataServretVal_u8 = E_OK;
    }
    else
    {
        /* Process the request, Check for the state machine */
        switch (Dcm_stDspIocbiState_en)
        {
            case DCM_IOCBI_IDLE:
            { /* Validate the request, check for the minimum request length first */
                if (pMsgContext->reqDataLen >= DSP_IOCBI_MINREQLEN)
                { /* Check if it is a valid Input Output Control parameter byte */
                    if (pMsgContext->reqData[2] <= 3)
                    { /* Get the DID from the request */
                        nrDID_u16 = (uint16)(DSP_CONV_2U8_TO_U16 (pMsgContext->reqData[0], pMsgContext->reqData[1]));
                        /* Check if DID is configured */
                        if (Dcm_GetIndexOfDID (nrDID_u16,&s_Dcm_idxIocbiDidIndexType_st) == E_OK)
                        {
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                            /* Check if the DID is supported in current variant */
                            /*If the data range of Did is not range did and supported in current variant */
                            if((s_Dcm_idxIocbiDidIndexType_st.dataRange_b==FALSE) && (*Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16] != NULL_PTR))
                            {
                                if((*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].idxDIDSupportedFnc_u16]))(nrDID_u16)!=E_OK)
                                {
                                    /* DID is not supported in current variant */
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                }
                            }
#endif
                            Dcm_DidSignalIdx_u16 = 0x0;
                            Dcm_ReadSignalLength_u16 = 0x0;
                            /*Loop through the complete list of IOCBI Dids and check if the status of the index matches with any in the status array*/
                            for(idxIocbiIndex_u16=0u;((idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS) && (*dataNegRespCode_u8 ==0x00u ));idxIocbiIndex_u16++)
                            {
                                if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16)
                                {
                                    ptrDidConfig = &Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];
                                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16 ;
                                }
                                /* Dummy else to remove Misra Warnings */
                                else
                                {

                                }
                            }
                            /*If Process request flag is set to TRUE and negative response code is set to 0x00 */
                            if((flgProcessReq_b!= FALSE)&&(*dataNegRespCode_u8==0x00u))
                            {
                                Dcm_stDspIocbiState_en = DCM_IOCBI_CHKSUPPORT;
                            }
                        }
                        else
                        { /* DID is not configured */
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        }
                    }
                    else
                    { /* Invalid IO control parameter */
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                        /* Report development error "DCM_E_INVALID_CONTROL_PARAM "to DET module if the DET module is enabled */
                        DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_INVALID_CONTROL_PARAM)
                    }
                }
                else
                { /* Minimum number of bytes are not received */
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
                if(*dataNegRespCode_u8 != 0x0)
                {
                    break;
                }
            }
            /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3 */
            case DCM_IOCBI_CHKSUPPORT:
            {
                ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                /* Check if this DID is allowed in the current active session*/
                if ((Dcm_DsldGetActiveSessionMask_u32()& (ptrDidConfig->adrExtendedConfig_pcst->dataSessBitMask_u32))!= 0x00uL)
                {
                    /* Get the DID from the request */
                    nrDID_u16 = (uint16)(DSP_CONV_2U8_TO_U16 (pMsgContext->reqData[0], pMsgContext->reqData[1]));
                    while((Dcm_DidSignalIdx_u16<ptrDidConfig->nrSig_u16) && (*dataNegRespCode_u8==0u))
                    {
                        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                        ptrIOSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
                        ptrIOCBIsigConfig = &Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16];

                        /*Check if the DID is supported for IOCTRL or not by comparing against the structure index*/
                        if((ptrSigConfig->idxDcmDspControlInfo_u16 >0u) && (ptrIOSigConfig->idxDcmDspIocbiInfo_u16>0u))
                        {
                            /* Check if short term adjustment is requested */
                            if((pMsgContext->reqData[2] == DCM_IOCBI_SHORTTERMADJUSTMENT) && ((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x08u)==0x08u ))
                            { /* Check if the control function is configured */
                                /* MR12 RULE 12.1 VIOLATION: Nesting of control structures (statements) exceeds 15 - program is non-conforming - The code should be  reached after multiple checks done prior to this */
                                if( ((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrShortTermAdjustment_cpv == NULL_PTR))
                                {
                                    /* Control Function is not configured */
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                    {
                                        /* Control Function is not configured */
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_FREEZECURRENTSTATE)&& ((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x04u)==0x04u ) )
                            { /* Check if the Control function is configured */
                                /* Check if the Control function is configured */
                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrFreezeCurrentState_cpv == NULL_PTR))
                                {
                                    /* Control Function is not configured */
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                    {
                                        /* Control Function is not configured */
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_RESETTODEFAULT) &&((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x02u)==0x02u ))
                            { /* Check if the Control function is configured */
                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrResetToDefault_cpv == NULL_PTR))
                                {
                                    /* Control Function is not configured */
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                    {
                                        /* Control Function is not configured */
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
#endif
                                }
                            }
                            else if((pMsgContext->reqData[2] == DCM_IOCBI_RETURNCONTROLTOECU) &&((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x01u)==0x01u ))
                            { /* Check if the Control function is configured */

                                if(((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)) && (ptrIOCBIsigConfig->adrReturnControlEcu_cpv == NULL_PTR))
                                {
                                    /* Control Function is not configured */
                                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                                }
                                else
                                {
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                                    if((ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER) && (ptrIOCBIsigConfig->ioControlRequest_cpv == NULL_PTR))
                                    {
                                        /* Control Function is not configured */
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
#endif
                                }
                            }
                            else
                            {
                                /* Control Function is not configured */
                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                                DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                            }
                        }
                        else
                        {
                            /* Control Function is not configured */
                            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            /* Report development error "DCM_E_CONTROL_FUNC_NOT_CONFIGURED "to DET module if the DET module is enabled */
                            DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_CONTROL_FUNC_NOT_CONFIGURED)
                        }
					 Dcm_DidSignalIdx_u16++;	
                    }
                    if(*dataNegRespCode_u8 == 0x00)
                    {
                        /*Initialize the control mask and control state size as 0*/
                        dataControlMaskLen_u16 = 0x0;
                        dataLength_u32 = 0x0;
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                        /* Control state is applicable for short term adjustment*/
                        if(pMsgContext->reqData[2] == DCM_IOCBI_SHORTTERMADJUSTMENT)
                        {
                            /*Set the flag for s_IsIOCBISubfuncCalled to TRUE*/
                            s_IsIOCBISubfuncCalled_b = TRUE;
                            /* Get the total length for the signal*/
                            dataFuncRetVal_u8=Dcm_GetLengthOfDIDIndex(s_Dcm_idxIocbiDidIndexType_st,&dataLength_u32,nrDID_u16);
                            /*Set the flag for s_IsIOCBISubfuncCalled to FALSE*/
                            s_IsIOCBISubfuncCalled_b = FALSE;
                        }
#endif
                        if(dataFuncRetVal_u8==E_OK)
                        {
                            /* IF the IOCONTROL DID is of typ DCM_CONTROLMASK_INTERNAL or DCM_CONTROLMASK_EXTERNAL
                             * obtain the ccontrlmask size from the conifugruation and check for the length if not report Incorrect Msg length NRC*/
                            ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                            ptrDidExtendedConfig = ptrDidConfig->adrExtendedConfig_pcst;
                            if(ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_NO)
                            {
                                dataControlMaskLen_u16 = ptrDidExtendedConfig->dataCtrlMaskSize_u8;
                            }
                            /**Exact length check*/
                            if ((pMsgContext->reqDataLen-3u) != (dataLength_u32 + dataControlMaskLen_u16))
                            { /* Request length error, Send negative response */
                                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                            }
                            else
                            {
                                /* If control state or control mask is present*/
                                if((dataLength_u32 != 0u) || (dataControlMaskLen_u16 != 0u))
                                {
                                    /* Call the appl function to validate the control mask and control state*/
                                    dataValidateIoMaskStatus_u8 = DcmAppl_DcmCheckControlMaskAndState(nrDID_u16,pMsgContext->reqData[2],&(pMsgContext->reqData[3]),(uint16)(pMsgContext->reqDataLen-3u));
                                    if(dataValidateIoMaskStatus_u8 != E_OK)
                                    {
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                        DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_INVALID_CONTROL_DATA)
                                    }
                                }
                            }

                        }
                        /* check for infrastructural errors*/
                        else if(dataFuncRetVal_u8 == DCM_INFRASTRUCTURE_ERROR)
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                        else if (dataFuncRetVal_u8 == DCM_E_PENDING)
                        {
                            /* Do nothing, just call again*/
                        }
                        else
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                    }
                }
                else
                { /* DID is not allowed in the current session */
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    /* Report development error "DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION "to DET module if the DET module is enabled */
                    DCM_DET_ERROR(DCM_IOCBI_ID , DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION)
                }

                if((*dataNegRespCode_u8 == 0x0) && (dataFuncRetVal_u8 != DCM_E_PENDING))
                { /* Move to next state where the request length is validated */
                    Dcm_stDspIocbiState_en = DCM_IOCBI_CHKCOND;
                    /* Reset the signal index */
                    Dcm_DidSignalIdx_u16 = 0x0;
                }
                else
                {
                    break;
                }
            }
            /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3 */
            case DCM_IOCBI_CHKCOND:
            {
                if (*dataNegRespCode_u8 == 0)
                {
                    ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                    ptrDidExtendedConfig = ptrDidConfig->adrExtendedConfig_pcst;

                    /* Check if this DID is allowed in the current security level */
                    if ((Dcm_DsldGetActiveSecurityMask_u32()& (ptrDidExtendedConfig->dataSecBitMask_u32))!=0x00uL)
                    {
                        /*Set the flag for mode check return value to TRUE*/
                        isModeChkRetval_b = TRUE;
                        if(ptrDidExtendedConfig->adrUserControlModeRule_pfct!=NULL_PTR)
                        {
                            /* Call the configured API to do DID specific checks before IO control operation */
                            dataFuncRetVal_u8 = (*ptrDidExtendedConfig->adrUserControlModeRule_pfct)(&dataNrc_u8,ptrDidConfig->dataDid_u16,DCM_SUPPORT_IOCONTROL);
                        }
                        else
                        {
                            /* Call the Dcm Appl API to do DID specific checks before IO control operation */
                            dataFuncRetVal_u8 = DcmAppl_UserDIDModeRuleService(&dataNrc_u8,ptrDidConfig->dataDid_u16,DCM_SUPPORT_IOCONTROL);
                        }
                        if(dataFuncRetVal_u8!=E_OK)
                        {
                            if(dataNrc_u8==0x00)
                            {
                                dataNrc_u8 = DCM_E_CONDITIONSNOTCORRECT;
                            }
                            /*Set the flag for mode check return value to FALSE*/
                            isModeChkRetval_b = FALSE;
                        }
                        else
                        {
                            dataNrc_u8=0;
                        }
#if(DCM_CFG_DSP_MODERULEFORDIDCONTROL!=DCM_CFG_OFF)
                        if((dataNrc_u8==0x00 ) &&(NULL_PTR != ptrDidExtendedConfig->adrIocbiModeRuleChkFnc_pfct))
                        {
                            isModeChkRetval_b = (*(ptrDidExtendedConfig->adrIocbiModeRuleChkFnc_pfct))(&dataNrc_u8);
                        }
#endif
                        /*chek if the flag for mode check return value is set to TRUE*/
                        if(FALSE!= isModeChkRetval_b)
                        {
                            /* Check if the response length fits into the buffer */
                            if (pMsgContext->resMaxDataLen >= (uint16)(ptrDidConfig->dataMaxDidLen_u16+3u))
                            { /* Move the state to perform the Control operation */
                                Dcm_stDspIocbiState_en = DCM_IOCBI_RUNNING;
                            }
                            else
                            { /* Response length is too long, Send negative response */
                                *dataNegRespCode_u8 = DCM_E_RESPONSETOOLONG;
                            }
                        }
                        else
                        {
                            *dataNegRespCode_u8 = dataNrc_u8;
                        }
                    }
                    else
                    { /* DID is not allowed in the current security level */
                        *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                    }
                }
                if(*dataNegRespCode_u8 != 0x0)
                /* Nothing to do */
                {
                    break;
                }
            }
            /* MR12 RULE 16.3 VIOLATION:The preceding 'switch' clause is not empty and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3 */
            case DCM_IOCBI_RUNNING:
            {
                ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
                ptrDidExtendedConfig = ptrDidConfig->adrExtendedConfig_pcst;
                /* Copy the control parameter to local variable */
                dataIoCtrlParam_u8 = pMsgContext->reqData[2];
                Dcm_dataDspIocbiCtrlParam_u8 = pMsgContext->reqData[2];
                if(ptrDidConfig->adrExtendedConfig_pcst->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                {
                    /* Get the start index of the control mask */
                    dataCtlMaskOffset_u16 = (uint16)(pMsgContext->reqDataLen - ((uint32)((ptrDidConfig->nrSig_u16-1u)/8u) + 1u));
                    /* Loop for all the signals configured for a DID */
                    while((Dcm_DidSignalIdx_u16 < ptrDidConfig->nrSig_u16)&&(*dataNegRespCode_u8==0x0u))
                    {
                        posnCtlMaskBit_u8 = 0x80;
                        if(ptrDidConfig->nrSig_u16 > 1u)
                        {
                            /*Get the byte position of the signal*/
                            posnSigByte_u16 = (uint16)(Dcm_DidSignalIdx_u16/8u);
                            /*Get the bit position of the signal*/
                            posnSigBit_u8 = (uint8)(Dcm_DidSignalIdx_u16%8);
                            /*Get the control mask value byte*/
                            posnCtlMaskByte_u8 = pMsgContext->reqData[dataCtlMaskOffset_u16 + posnSigByte_u16];
                            /*Get the control mask bit value for the signal*/
                            posnCtlMaskBit_u8 = (uint8)(((uint8)(posnCtlMaskByte_u8 << posnSigBit_u8)) & ((uint8)0x80));

                        }
                        /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                        s_IsIOCBISubfuncCalled_b = TRUE;
                        /* Get the length for each signal, which will be for passing the pointer for short term adjustment and for sending the response*/
                        dataFuncRetVal_u8=Dcm_GetLengthOfSignal(&dataSignalLength_u16);
                        /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                        s_IsIOCBISubfuncCalled_b = FALSE;
                        if(dataFuncRetVal_u8 == E_OK)
                        {
                            /* Do nothing. Base pointer will be incremented at the end of for loop */
                        }
                        else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                        {
                            /* Wait for next cycle*/
                            dataIocbiExeResult_u8= DCM_E_PENDING;
                            break;
                        }
                        /* Send GeneralReject for either Infrastructure Error or for any other return values */
                        else
                        {
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }

                        /*Check whether signal is masked or not*/
                        s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
                        ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                        ptrIOSigConfig= &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

                        if((posnCtlMaskBit_u8 == 0x80) && (*dataNegRespCode_u8 == 0x00))
                        {
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                            /* Short Term adjustment is requested? */
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;
                                /* Check if the Control function is configured */
                                if(ptrIOCBIFnc != NULL_PTR)
                                {
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                    s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment1_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],dataNegRespCode_u8);
                                    }

#endif
#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {
                                            /* Check whether Rte_Call API hasn't been invoked already */
                                            if (!s_IocbiRteCallPlaced_b)
                                            {
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment9_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {
                                                    /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {
                                                    /* For any return value other than E_OK send NRC General Reject */
                                                    *dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustmentResults_cpv;
                                               /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                               dataIocbiExeResult_u8=(*(ShortTermAdjustment13_pfct)(ptrIOCBIFnc)) (dataNegResCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {
                                                   /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   *dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment2_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN+Dcm_ReadSignalLength_u16)],Dcm_stDspIocbiOpStatus_u8, dataNegRespCode_u8);
                                       }
                                    }

#endif
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;
                                /* Check if the Control function is configured */
                                if(ptrIOCBIFnc != NULL_PTR)
                                {
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                    s_IsIOCBISubfuncCalled_b = TRUE;

                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {
                                        /* Freeze current state is requested */
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }

                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {
                                            /* Check whether Rte_Call API hasn't been invoked already */
                                            if (!s_IocbiRteCallPlaced_b)
                                            {
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                 dataIocbiExeResult_u8=(*(FreezeCurrentState9_pfct)(ptrIOCBIFnc)) (Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {
                                                    /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {
                                                    /* For any return value other than E_OK send NRC General Reject */
                                                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                                 ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentStateResults_cpv;
                                               /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                               dataIocbiExeResult_u8=(*(FreezeCurrentState13_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {
                                                   /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {
                                        /* Freeze current state is requested */
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState2_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);
                                         }
                                    }
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;
                                /* Check if the Control function is configured */
                                if(ptrIOCBIFnc != NULL_PTR)
                                {
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                    s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED== DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC)))
                                    {
                                        /* Freeze current state is requested */
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }
#endif

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
                                    if((ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC)))
                                    {
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
                                        if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                        {
                                            /* Check whether Rte_Call API hasn't been invoked already */
                                            if (!s_IocbiRteCallPlaced_b)
                                            {
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                 dataIocbiExeResult_u8=(*(ResetToDefault9_pfct)(ptrIOCBIFnc)) (Dcm_stDspIocbiOpStatus_u8);
                                                if(dataIocbiExeResult_u8 == E_OK)
                                                {
                                                    /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                    s_IocbiRteCallPlaced_b = TRUE;
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                                }
                                                else
                                                {
                                                    /* For any return value other than E_OK send NRC General Reject */
                                                    dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                                }
                                            }
                                            else
                                            {
                                               ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefaultResults_cpv;
                                               /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                               dataIocbiExeResult_u8=(*(ResetToDefault13_pfct)(ptrIOCBIFnc)) (&dataNegResCode_u8);
                                               if(dataIocbiExeResult_u8 == E_OK)
                                               {
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                               }
                                               else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                               {
                                                    dataIocbiExeResult_u8 = DCM_E_PENDING;
                                               }
                                               else
                                               {
                                                   /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                                   s_IocbiRteCallPlaced_b = FALSE;
                                                   dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                               }
                                            }
                                        }
                                        else
#endif
                                        {
                                        /* Freeze current state is requested */
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataIocbiExeResult_u8=(*(ResetToDefault2_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);
                                        }
                                    }
#endif
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
#endif
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {
                                ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;
                                /* Check if the Control function is configured */
                                if(ptrIOCBIFnc != NULL_PTR)
                                {
                                    /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                    s_IsIOCBISubfuncCalled_b = TRUE;

                                    /*As ReturnControlToEcu is a synchronous API , the same API is invoked for both Synch and ASynch Fnc and ClientServer Configuration */
                                    if( (ptrDidExtendedConfig->dataCtrlMask_en!=DCM_CONTROLMASK_EXTERNAL) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE) && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER))
                                    {
                                        /* ReturnControlToECU is a synchronous API irrespective of any UsePort configuration.So the function signature is same for Asynch as well as Sync implementation */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ReturnControlEcu1_pfct)(ptrIOCBIFnc)) (dataNegRespCode_u8);
                                    }

                                    /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                    s_IsIOCBISubfuncCalled_b = FALSE;
                                }
                            }
                            /* Check for infrastructural errors in case of RTE*/

                            if((Dcm_IsInfrastructureErrorPresent_b(dataIocbiExeResult_u8) != FALSE) && ((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
                            {
                                /* Set the nrc as general reject*/
                                *dataNegRespCode_u8 =DCM_E_GENERALREJECT;
                            }
                            else if(dataIocbiExeResult_u8 == E_OK)
                            {
                                *dataNegRespCode_u8 = 0x00;
                            }
                            else
                            {
                                /* MR12 RULE 15.4 VIOLATION: More than one break statement is being used to terminate an iteration statement */
                                break;
                            }
                        }

                        if((dataIocbiExeResult_u8 == E_OK) && (*dataNegRespCode_u8 == 0x00) )
                        {
                            Dcm_ReadSignalLength_u16 += dataSignalLength_u16;
                        }

					Dcm_DidSignalIdx_u16++;
                    }

                    if ((E_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    { /* Move the state to read control status record */
                        Dcm_stDspIocbiState_en = DCM_IOCBI_READSTREC;
                        /* Reset the signal index */
                        Dcm_DidSignalIdx_u16 = 0x0;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;

                    }
                    else if((E_NOT_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    {
                        /* Send negative response code DCM_E_GENERALREJECT as the application has returned E_NOT_OK */
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        break;
                    }
                    else
                    {
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;

                        if(DCM_E_PENDING == dataIocbiExeResult_u8)
                        {
                            *dataNegRespCode_u8 = 0x00;
                            dataServretVal_u8=DCM_E_PENDING;
                            Dcm_stDspIocbiOpStatus_u8 = DCM_PENDING;
                        }
                        break;
                    }
                }
                else if(ptrDidConfig->adrExtendedConfig_pcst->dataCtrlMask_en == DCM_CONTROLMASK_EXTERNAL)
                {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)

                    dataFuncRetVal_u8=Dcm_GetLengthOfSignal(&dataSignalLength_u16);
                    if(dataFuncRetVal_u8 == E_OK)
                    {
                        /* Do nothing. Base pointer will be incremented at the end of for loop */
                    }
                    else if(dataFuncRetVal_u8 == DCM_E_PENDING)
                    {
                        /* Wait for next cycle*/
                        dataIocbiExeResult_u8= DCM_E_PENDING;
                        dataServretVal_u8=DCM_E_PENDING;
                        break;
                    }
                    else
                    {
                        /* Send GeneralReject for either Infrastructure Error or for any other return values */
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }

                    /*Check whether signal is masked or not*/
                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
                    ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
                    ptrIOSigConfig= &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                    if(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)

                    {
                        ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].ioControlRequest_cpv;
                        if(ptrIOCBIFnc != NULL_PTR)
                        {
                            /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                            s_IsIOCBISubfuncCalled_b = TRUE;
                            dataIocbiExeResult_u8 =(*(IOControlrequest_pfct)(ptrIOCBIFnc))(Dcm_dataDspIocbiCtrlParam_u8,&pMsgContext->reqData[DSP_IOCBI_MINREQLEN],dataSignalLength_u16,ptrDidExtendedConfig->dataCtrlMaskSize_u8,Dcm_stDspIocbiOpStatus_u8,dataNegRespCode_u8);
                            /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                            s_IsIOCBISubfuncCalled_b = FALSE;
                        }
                    }
                    else
#endif
                    {
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                        /* Short Term adjustment is requested? */
                        if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustment_cpv;
                            /* Check if the Control function is configured */
                            if(ptrIOCBIFnc != NULL_PTR)
                            {
                                /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                s_IsIOCBISubfuncCalled_b = TRUE;

#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED   == DCM_CFG_ON)

                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment3_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment4_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment5_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                    }
                                }
#endif
#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED   == DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {
#if (DCM_CFG_DSP_IOCBI_ASP == DCM_CFG_ON)
                                    if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        if (!s_IocbiRteCallPlaced_b)
                                        {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment10_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment11_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ShortTermAdjustment12_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {
                                                /*Dummy else clause*/
                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                                /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                                /* For any return value other than E_OK send NRC General Reject */
                                                *dataNegRepsCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                            ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrShortTermAdjustmentResults_cpv;
                                            /* Call the configured API */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataIocbiExeResult_u8=(*(ShortTermAdjustment13_pfct)(ptrIOCBIFnc)) (&dataNegResCode_u8);

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                               /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                               s_IocbiRteCallPlaced_b = FALSE;
                                               *dataNegpResCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                            /* Call the configured API */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment6_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment7_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ShortTermAdjustment8_pfct)(ptrIOCBIFnc)) (&pMsgContext->reqData[(DSP_IOCBI_MINREQLEN)],Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                        }
                                    }
                                }
#endif
                                /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }

                        }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)
                        /* Short Term adjustment is requested? */
                        if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentState_cpv;
                            /* Check if the Control function is configured */
                            if(ptrIOCBIFnc != NULL_PTR)
                            {
                                /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                s_IsIOCBISubfuncCalled_b = TRUE;

                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                    }
                                }

                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {
#if (DCM_CFG_DSP_IOCBI_ASP == DCM_CFG_ON)
                                    if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        /* If the Rte_Call API is not invoked already */
                                        if (!s_IocbiRteCallPlaced_b)
                                        {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(FreezeCurrentState10_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(FreezeCurrentState11_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(FreezeCurrentState12_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {
                                                /*Dummy else clause*/
                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                                /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                                /* For any return value other than E_OK send NRC General Reject */
                                                dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrFreezeCurrentStateResults_cpv;
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(FreezeCurrentState13_pfct)(ptrIOCBIFnc)) (&dataNegResCode_u8);
                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                               /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                               s_IocbiRteCallPlaced_b = FALSE;
                                               dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState6_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState7_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(FreezeCurrentState8_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                        }
                                    }
                                }

                                /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }
#endif
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)
                        /* Short Term adjustment is requested? */
                        if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefault_cpv;
                            /* Check if the Control function is configured */
                            if(ptrIOCBIFnc != NULL_PTR)
                            {
                                /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                s_IsIOCBISubfuncCalled_b = TRUE;
#if(DCM_CFG_DSP_CONTROL_SYNCH_FNC_ENABLED== DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                    }
                                }
#endif

#if(DCM_CFG_DSP_CONTROL_ASYNCH_FNC_ENABLED == DCM_CFG_ON)
                                if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)||(ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC))
                                {
#if (DCM_CFG_DSP_IOCBI_ASP == DCM_CFG_ON)
                                    if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && (ptrSigConfig->UseAsynchronousServerCallPoint_b))
                                    {
                                        /* If the Rte_Call API is not invoked already */
                                        if (!s_IocbiRteCallPlaced_b)
                                        {
                                            /* Based on the Control Mask Size invoke the Rte_Call API with In and InOut parameters */
                                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                            {
                                               ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ResetToDefault10_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                            {
                                                ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ResetToDefault11_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16);
                                            }
                                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                            {
                                                ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                                pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                                /* Call the configured API */
                                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                                dataIocbiExeResult_u8=(*(ResetToDefault12_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32);
                                            }
                                            else
                                            {
                                                /*Dummy else clause*/
                                            }

                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                                /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                                                 s_IocbiRteCallPlaced_b = TRUE;
                                                 dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                                /* For any return value other than E_OK send NRC General Reject */
                                                dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                        else
                                        {
                                            ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrResetToDefaultResults_cpv;
                                            /* Based on the size of controlMaskSize configured invoke the Rte_Result API */
                                                                                    /* Call the configured API */
                                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                            dataIocbiExeResult_u8=(*(ResetToDefault13_pfct)(ptrIOCBIFnc)) (&dataNegResCode_u8);
                                            if(dataIocbiExeResult_u8 == E_OK)
                                            {
                                               s_IocbiRteCallPlaced_b = FALSE;
                                            }
                                            else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                                            {
                                                dataIocbiExeResult_u8 = DCM_E_PENDING;
                                            }
                                            else
                                            {
                                               /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag and send NRC General Reject */
                                               s_IocbiRteCallPlaced_b = FALSE;
                                               dataNegResCode_u8 = DCM_E_GENERALREJECT;
                                            }
                                        }
                                    }
                                    else
#endif
                                    {
                                        if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                        {
                                            ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        dataIocbiExeResult_u8=(*(ResetToDefault6_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault7_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],                  \
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ResetToDefault8_pfct)(ptrIOCBIFnc))(Dcm_stDspIocbiOpStatus_u8,ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                        }
                                    }
                                }
#endif
                                /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }
#endif
                        /* Return Control to is requested? */
                        if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                        {
                            ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;
                            /* Check if the Control function is configured */
                            if(ptrIOCBIFnc != NULL_PTR)
                            {
                                /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                                s_IsIOCBISubfuncCalled_b = TRUE;

                                    /*As ReturnControlToEcu is a synchronous API , the same API is invoked for both Synch and ASynch Fnc and ClientServer Configuration */
                                if((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)&& (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE))
                                {
                                    if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                                    {
                                        ControlMask_u8=pMsgContext->reqData[(pMsgContext->reqDataLen-1u)];
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ReturnControlEcu3_pfct)(ptrIOCBIFnc))(ControlMask_u8,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                                    {
                                        ControlMask_u16=DSP_CONV_2U8_TO_U16(pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ReturnControlEcu4_pfct)(ptrIOCBIFnc))(ControlMask_u16,dataNegRespCode_u8);
                                    }
                                    else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8>=3)
                                    {
                                        ControlMask_u32=DSP_CONV_4U8_TO_U32(pMsgContext->reqData[(pMsgContext->reqDataLen-4u)],pMsgContext->reqData[(pMsgContext->reqDataLen-3u)],
                                        pMsgContext->reqData[(pMsgContext->reqDataLen-2u)],pMsgContext->reqData[(pMsgContext->reqDataLen-1u)]);
                                        /* Call the configured API */
                                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                        dataIocbiExeResult_u8=(*(ReturnControlEcu5_pfct)(ptrIOCBIFnc))(ControlMask_u32,dataNegRespCode_u8);
                                    }
                                    else
                                    {
                                        /*Dummy else clause*/
                                    }
                                }

                                /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                                s_IsIOCBISubfuncCalled_b = FALSE;
                            }
                        }

                    }
                    if (E_OK == dataIocbiExeResult_u8)
                    { /* Move the state to read control status record */
                        Dcm_stDspIocbiState_en = DCM_IOCBI_READSTREC;
                        /* Reset the signal index */
                        Dcm_DidSignalIdx_u16 = 0x0;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        Dcm_ReadSignalLength_u16=(uint16)(pMsgContext->reqDataLen-ptrDidExtendedConfig->dataCtrlMaskSize_u8-DSP_IOCBI_MINREQLEN);
                    }
                    else if((E_NOT_OK == dataIocbiExeResult_u8) && (*dataNegRespCode_u8 == 0x0))
                    {
                        /* Send negative response code DCM_E_GENERALREJECT as the application has returned E_NOT_OK */
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        Dcm_ReadSignalLength_u16=0;
                        break;
                    }
                    else
                    {
                        Dcm_stDspIocbiOpStatus_u8 = DCM_INITIAL;
                        if(DCM_E_PENDING == dataIocbiExeResult_u8)
                        {
                            *dataNegRespCode_u8 = 0x00;
                            dataServretVal_u8=DCM_E_PENDING;
                            Dcm_stDspIocbiOpStatus_u8 = DCM_PENDING;
                        }
                        break;
                    }
#endif
                }
                else
                {
                    /*Dummy else clause*/
                    dataServretVal_u8=E_NOT_OK;
                }
            }
            /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3 */
            case DCM_IOCBI_READSTREC:
            { /* Copy the control parameter */
                dataIoCtrlParam_u8 = pMsgContext->reqData[2];
                /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                s_IsIOCBISubfuncCalled_b = TRUE;
                /* Obtain ControlStatusRecord by calling ReadFunction */
                dataRetGetDid_u8 = Dcm_GetDIDData(&s_Dcm_idxIocbiDidIndexType_st,&pMsgContext->resData[3]);
                /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                s_IsIOCBISubfuncCalled_b = FALSE;
                /* if ReadFunc is OK */
                if(dataRetGetDid_u8 == E_OK)
                {
                    /*Update the DcmDsp_IocbiStatus_array with the state of subfunction which is active */
                    for(idxIocbiIndex_u16=0;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
                    {
                        ptrIOCBIStatusArrayConfig=&DcmDsp_IocbiStatus_array[idxIocbiIndex_u16];
                        if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == ptrIOCBIStatusArrayConfig->idxindex_u16)
                        {
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {
                                /*Set the status flag to IDLE state since returncontrol to ECU was successful*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_IDLESTATE;
                            }
#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {
                                /*Set the status flag to RTD active state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RTD_ACTIVE;
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {
                                /*Set the status flag to FCS active state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_FCS_ACTIVE;
                            }
#endif
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {
                                /*Set the status flag to STA active state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_STA_ACTIVE;
                            }
#endif
                        }
                    }
                    /* Reset the state machine */
                    Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                    s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16 = 0x0; /*All the signals read correctly, therefore reset it to zero*/
                    s_Dcm_idxIocbiDidIndexType_st.dataSignalLengthInfo_u32 = 0x0; /*All the signals read correctly, therefore reset the signal data length to zero*/
                    /* Prepare the DID bytes and the Input Output Control parameter in the response buffer */
                    pMsgContext->resData[0] = pMsgContext->reqData[0];
                    pMsgContext->resData[1] = pMsgContext->reqData[1];
                    pMsgContext->resData[2] = dataIoCtrlParam_u8;
                    pMsgContext->resDataLen = Dcm_ReadSignalLength_u16+DSP_IOCBI_MINREQLEN;
                    dataServretVal_u8=E_OK;
                }
                else if(dataRetGetDid_u8 == DCM_E_PENDING)
                { /* Do nothing, wait for next call */
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_PENDING;
                    dataServretVal_u8=DCM_E_PENDING;
                    Dcm_DidSignalIdx_u16 = s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16;

                    /*Update the DcmDsp_IocbiStatus_array with the state of subfunction which is active */
                    for(idxIocbiIndex_u16=0;idxIocbiIndex_u16<DCM_CFG_NUM_IOCBI_DIDS;idxIocbiIndex_u16++)
                    {
                        ptrIOCBIStatusArrayConfig=&DcmDsp_IocbiStatus_array[idxIocbiIndex_u16];
                        if(s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16 == ptrIOCBIStatusArrayConfig->idxindex_u16)
                        {

                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RETURNCONTROLTOECU)
                            {
                                /*Set the status flag to RCE pending state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RCE_PENDING;
                            }

#if(DCM_CFG_DSP_RESETTODEFAULT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_RESETTODEFAULT)
                            {
                                /*Set the status flag to RTD pending state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_RTD_PENDING;
                            }
#endif
#if(DCM_CFG_DSP_FREEZECURRENTSTATE_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_FREEZECURRENTSTATE)
                            {
                                /*Set the status flag to FCS pending state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_FCS_PENDING;
                            }
#endif
#if(DCM_CFG_DSP_SHORTTERMADJUSTMENT_ENABLED  == DCM_CFG_ON)
                            if(dataIoCtrlParam_u8 == DCM_IOCBI_SHORTTERMADJUSTMENT)
                            {
                                /*Set the status flag to STA pending state*/
                                ptrIOCBIStatusArrayConfig->IocbiStatus_en = DCM_IOCBI_STA_PENDING;
                            }
#endif
                        }
                    }
                }

                else
                {
                    if(dataRetGetDid_u8 == E_NOT_OK)
                    {
                        /* Invoke the DcmAPPl API to obtain the NRC from the Application*/
                        dataretVal_u8 = DcmAppl_DcmReadDataNRC(Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].dataDid_u16,Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16].adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].posnSigBit_u16,dataNegRespCode_u8);
                        if(dataretVal_u8!=E_OK)
                        {
                            /* Send negative response code DCM_E_GENERALREJECT as the application has returned E_NOT_OK from ReadNrc applfunction
                             * or has not set the NRC */
                            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                        }
                    }
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                    }
                    s_Dcm_idxIocbiDidIndexType_st.nrNumofSignalsRead_u16 = 0x0; /*E_NOT_OK set stop reading the signals, therefore reset the number of singals read to zero*/
                    s_Dcm_idxIocbiDidIndexType_st.dataSignalLengthInfo_u32 = 0x0; /*All the signals not read correctly, therefore reset the signal data length to zero*/
                    s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b = DCM_INITIAL;
                }
                break;
            }

            default:
            { /* IOCBI service is not in a valid state, Send negative response */
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                break;
            }
        }

        if(*dataNegRespCode_u8 != 0x00 )
        { /* Reset signal index */
            Dcm_DidSignalIdx_u16 = 0x0;
            dataServretVal_u8 = E_NOT_OK;
            Dcm_stDspIocbiState_en = DCM_IOCBI_IDLE;
        }
    }
    return dataServretVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_ResetActiveIoCtrl:
 *
 * Invoke the Return Control to ECU for all the signals of an IOCBI DID.
 *
 * \param     dataSessionMask_u32           :           Session mask in which the IOCBI DID is supported
 *            dataSecurityMask_u32          :           Security mask in which the IOCBI DID is supported
 *            flgSessChkReqd_b              :           Flag to check if session check needs to be done.
 *                                                      For security transition this flag is false,which
 *                                                      indicates no session check necessary
 * \retval
 *  void
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ResetActiveIoCtrl(VAR (uint32,AUTOMATIC) dataSessionMask_u32,
VAR (uint32,AUTOMATIC) dataSecurityMask_u32,
VAR (boolean,AUTOMATIC) flgSessChkReqd_b)
{
    /**The code which would loop through all the IOCBI DIDs and call all the returncontrol to ECU functions to reset all the  active IOctrls
     supported in the current session level*/

    VAR(uint16 ,AUTOMATIC) idxIocbiIndex_u16; /*Index to loop through all the IOCTRL DID*/
    VAR(uint16 ,AUTOMATIC) idxSig_u16; /*Index to loop through all the signals of the DID*/
    VAR(Std_ReturnType,AUTOMATIC) dataRetIocbiFunc_u8;
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegResCode_u8; /* Negative response code indicator */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA) ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrIOSigConfig;
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidExtendedConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA) ptrIOCBIFnc;
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
    VAR(uint8 ,AUTOMATIC) ControlMask_u8;
    VAR(uint16 ,AUTOMATIC) ControlMask_u16;
    VAR(uint32 ,AUTOMATIC) ControlMask_u32;
    ControlMask_u8 = 0;
    ControlMask_u16 = 0;
    ControlMask_u32 = 0;
#endif
    dataRetIocbiFunc_u8 = E_NOT_OK;
    dataNegResCode_u8 = 0x00;



    for (idxIocbiIndex_u16 = 0; idxIocbiIndex_u16 < DCM_CFG_NUM_IOCBI_DIDS; idxIocbiIndex_u16++)
    {
        /*Check if the DID is active,*/
        /*Check if IOCBI DIDs status is not ideal state and enable the iocontrol to be reset on session/security change */
        if((DCM_IOCBI_IDLESTATE != DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].IocbiStatus_en)                                                                           &&     \
                (Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].adrExtendedConfig_pcst->dataIocbirst_b  != FALSE)                                    &&     \
                (((0x0u == ((Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].adrExtendedConfig_pcst->dataSecBitMask_u32)  & dataSecurityMask_u32)))   ||     \
                        (((flgSessChkReqd_b) && (0x0u  == ((Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16].adrExtendedConfig_pcst->dataSessBitMask_u32) & dataSessionMask_u32))))))

        {
            ptrDidConfig = &Dcm_DIDConfig[DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].idxindex_u16];

            /*Loop through all the signals of the IOCBI DID and invoke return control to ECU*/
            for (idxSig_u16 = 0; idxSig_u16 < ptrDidConfig->nrSig_u16; idxSig_u16++)
            {
                ptrSigConfig = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16];
                ptrIOSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
                if(ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER_AS_SERVICE || ptrSigConfig->usePort_u8 == USE_DATA_SENDER_RECEIVER)

                {
                    ptrIOCBIFnc= Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].ioControlRequest_cpv;
                    if(ptrIOCBIFnc != NULL_PTR)
                    {
                        /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                        s_IsIOCBISubfuncCalled_b = TRUE;
                        dataRetIocbiFunc_u8 =(*(IOControlrequest_pfct)(ptrIOCBIFnc))(DCM_RETURN_CONTROL_TO_ECU,NULL_PTR,0,0,DCM_INITIAL,&dataNegResCode_u8);
                        /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                        s_IsIOCBISubfuncCalled_b = FALSE;
                    }
                    ptrIOCBIFnc = NULL_PTR;
                    (void)dataRetIocbiFunc_u8;
                    (void)dataNegResCode_u8;
                }

#endif
                ptrIOCBIFnc = Dcm_DspIOControlInfo[ptrIOSigConfig->idxDcmDspIocbiInfo_u16].adrReturnControlEcu_cpv;
                ptrDidExtendedConfig = ptrDidConfig->adrExtendedConfig_pcst;
                /*Cheeck if return control to ECU is supported or not for the DID, lower most bit represents return control to ECU*/
                if (((ptrDidConfig->adrExtendedConfig_pcst->statusmaskIOControl_u8 & 0x01u) > 0u)
                        && (ptrIOCBIFnc != NULL_PTR))
                {
                    s_ActiveDid_u16 = ptrDidConfig->dataDid_u16;
                    /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
                    s_IsIOCBISubfuncCalled_b = TRUE;

                        /*As ReturnControlToEcu is a synchronous API , the same API is invoked for both Synch and ASynch Fnc and ClientServer Configuration */
                    if ((ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER)
                            && (ptrSigConfig->usePort_u8 != USE_DATA_SENDER_RECEIVER_AS_SERVICE))
                    {
                        if (ptrDidExtendedConfig->dataCtrlMask_en != DCM_CONTROLMASK_EXTERNAL)
                        {
                            /* Return Control to ECU is requested */
                            /* Call the configured API */
                            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                            dataRetIocbiFunc_u8 = (*(ReturnControlEcu1_pfct) (ptrIOCBIFnc))(&dataNegResCode_u8);
                        }
                        else
                        {
#if(DCM_CFG_DSP_CONTROLMASK_EXTERNAL_ENABLED == DCM_CFG_ON)
                            if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==1)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ReturnControlEcu3_pfct)(ptrIOCBIFnc)) (ControlMask_u8,&dataNegResCode_u8);
                            }
                            else if(ptrDidExtendedConfig->dataCtrlMaskSize_u8==2)
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ReturnControlEcu4_pfct)(ptrIOCBIFnc)) (ControlMask_u16,&dataNegResCode_u8);
                            }
                            else
                            {
                                /* Short Term Adjustment was requested */
                                /* Call the configured API  with Opstatus as DCM_CANCEL */
                                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                                dataRetIocbiFunc_u8=(*(ReturnControlEcu5_pfct)(ptrIOCBIFnc)) (ControlMask_u32,&dataNegResCode_u8);
                            }
#endif
                        }
                    }

                    /*if the resetting the IOcontrol was successful, reset the status array to DCM_IOCBI_IDLESTATE*/
                    if (E_OK == dataRetIocbiFunc_u8)
                    {
                        /*Update the Iocbistatus arrays status with DCM_IOCBI_IDLESTATE  when E_OK is returned from return control to ecu function pointer*/
                        DcmDsp_IocbiStatus_array[idxIocbiIndex_u16].IocbiStatus_en = DCM_IOCBI_IDLESTATE;
                    }
                    /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
                    s_IsIOCBISubfuncCalled_b = FALSE;
                    (void) dataNegResCode_u8;
                }
            }/*End of idxSig_u16 for loop*/
        }/*End of IF condition to check if IOCBI did is active*/

    }/*End of idxIocbiIndex_u16 for loop*/

    (void) dataSessionMask_u32;
    (void) dataSecurityMask_u32;
    (void) flgSessChkReqd_b;
}

/**
 ****************************************************************************************************************************
 * Dcm_GetLengthOfSignal:
 *
 * Get the read data length of the current active signal for IOCBI request
 *
 * \param     dataSigLength_u16 :   Pointer to hold the length of the signal
 * \retval     E_OK: calculation finished successfully
 *             E_NOT_OK: error in configuration or in the called length calculating function
 *             DCM_INFRASTRUCTURE_ERROR : Infrastructure error occured
 * \seealso
 *
 ****************************************************************************************************************************
 */

FUNC (Std_ReturnType,DCM_CODE) Dcm_GetLengthOfSignal(P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) dataSigLength_u16)
{
    VAR (uint32, AUTOMATIC) dataSigLength_u32;
    VAR (Std_ReturnType, AUTOMATIC) dataRetVal_u8; /* Local variable to store return value */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrIOSigConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA) ptrReadDataLenFnc;

    /* Initialisations */
    dataRetVal_u8 = E_NOT_OK;
    *dataSigLength_u16 = 0x0;
    ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxIocbiDidIndexType_st.idxIndex_u16];
    ptrSigConfig= &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[Dcm_DidSignalIdx_u16].idxDcmDspDatainfo_u16];
    ptrIOSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];
    ptrReadDataLenFnc = ptrIOSigConfig->adrReadDataLengthFnc_pfct;

    /* Check for USE FUNC and valid Read Data length function configuration */
    if((ptrSigConfig->idxDcmDspControlInfo_u16 >0)&& (ptrReadDataLenFnc != NULL_PTR))
    {
#if(DCM_CFG_DSP_CONTROL_VAR_LEN_ENABLED != DCM_CFG_OFF)
        /* Get the length from the configured API */
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
        if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
        {
            dataRetVal_u8 = (*(ReadDataLengthFnc1_pf)(ptrReadDataLenFnc))(dataSigLength_u16);
        }
        else
        {
            if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
            {
    #if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
                if ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER) && ((ptrSigConfig->UseAsynchronousServerCallPoint_b))
                {
                    if(!s_DcmReadLengthRteCallPlaced_b)
                    {
                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrReadDataLenFnc))(s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b);
                        if(dataIocbiExeResult_u8 == E_OK)
                         {
                            /* Set the Rte_Call Flag to TRUE and return Pending so that Rte_Result will be invoked in the next cycle */
                            s_DcmReadLengthRteCallPlaced_b = TRUE;
                            dataIocbiExeResult_u8 = DCM_E_PENDING;
                         }
                         /* Dummy Else to remove Misra Warning */
                         else
                         {

                         }
                    }
                    else
                    {
                        ptrReadDataLenFnc = ptrIOSigConfig->adrReadDataLengthFncResults_pfct;
                        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                        dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrReadDataLenFnc))(dataSigLength_u16);

                        if(dataIocbiExeResult_u8 == E_OK)
                        {
                           s_DcmReadLengthRteCallPlaced_b = FALSE;
                        }
                        else if(dataIocbiExeResult_u8 == RTE_E_NO_DATA)
                        {
                            dataIocbiExeResult_u8 = DCM_E_PENDING;
                        }
                        else
                        {
                           /* For any return value other than E_OK , RTE_E_NO_DATA ,  reset the Flag */
                           s_IocbiRteCallPlaced_b = FALSE;
                        }
                    }
                }
                else
    #endif
                {
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                    dataRetVal_u8 = (*(ReadDataLengthFnc4_pf)(ptrReadDataLenFnc))(s_Dcm_idxIocbiDidIndexType_st.dataopstatus_b,dataSigLength_u16);
                }
            }
        }
        if(dataRetVal_u8==E_OK)
        {
            /* If the length received in more than the configured maximum length for a lengththen return error */

#if (DCM_CFG_READDATALENGTH_BITS==DCM_CFG_OFF)
            /* Length is returned in bytes. Convert to bits */
            *dataSigLength_u16=*dataSigLength_u16 *8;
#endif
            if((*dataSigLength_u16 > ptrSigConfig->dataSize_u16) ||(*dataSigLength_u16==0))
            {
                dataRetVal_u8 = E_NOT_OK;
            }
        }
        else if((dataRetVal_u8 == DCM_E_PENDING) && ((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
        {
        }
        else
        {
            /* Check for infrastructural errors in case of RTE*/

            if((Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE)&&((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER) || (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER)))
            {
                dataRetVal_u8=DCM_INFRASTRUCTURE_ERROR;
            }
        }
#endif
    }
    else
    {
#if(DCM_CFG_DSP_CONTROL_FIXED_LEN_ENABLED != DCM_CFG_OFF)
        /*If the interface is RTE AR4.x retain the signal size in bits, else convert it to bytes*/
        *dataSigLength_u16 = ptrSigConfig->dataSize_u16;
        dataRetVal_u8 = E_OK;
#endif
    }

    if(dataRetVal_u8 == E_OK)
    {
        dataSigLength_u32=*dataSigLength_u16;
        /* Convert data length in Bits to the appropriate data length in bytes */
        Dcm_ConvBitsToBytes(&dataSigLength_u32);
        *dataSigLength_u16=(uint16)dataSigLength_u32;
    }
    return dataRetVal_u8;
}

/**
 *************************************************************************************************************************************************************
 * Dcm_SetFlagforIOCBI:
 *
 * This API sets/resets the flag which is required for getting the active DID based on the input parameter
 *
 *
 * \param     boolean isFlag_b : parameter for setting or resetting the flag to get the active DID
 * \retval    None
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_SetFlagforIOCBI(VAR (boolean,AUTOMATIC) isFlag_b)
{
    /* Setting/resetting the flag so that the application can call GetActiveDID 
	   function from DcmAppl_DcmConfirmation */
    s_IsIOCBISubfuncCalled_b = isFlag_b;
}

/**
 *******************************************************************************
 * Dcm_Prv_DspIOCBIConfirmation : API used for confirmation of response sent for  
 *							      InputOutputControlByIdentifier (0x2F) service.
 * \param           dataIdContext_u8    Service Id 
 * \param           dataRxPduId_u8      PDU Id on which request is Received
 * \param           dataSourceAddress_u16    Tester Source address id
 * \param           status_u8                Status of Tx confirmation function
 *
 * \retval          None
 * \seealso
 *
 *******************************************************************************
 */
 FUNC(void, DCM_CODE) Dcm_Prv_DspIOCBIConfirmation(
 VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
 VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
 VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
 VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
        if(dataIdContext_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)
        {

            Dcm_SetFlagforIOCBI(TRUE);
        }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																	status_u8);
        if(dataIdContext_u8 == DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER)
        {
            Dcm_SetFlagforIOCBI(FALSE);
        }
}

/**
 *************************************************************************************************************************************************************
 * Dcm_GetActiveIOCBIDid:
 *
 * This API returns the current active DID. This function is called from the Dcm API Dcm_GetActiveDid.
 *
 *
 * \param     uint16* dataDid_u16 : Parameter for updating of the DID under processing. The DID value returned is valid only if return value is E_OK.
 * \retval    Std_ReturnType : E_OK : The DID under processing is a normal DID.The parameter dataDid_u16 contains valid DID value in this case.
 *                             E_NOT_OK: The DID under processing is a range DID. The parameter dataDid_u16 contains invalid data in this case.
 *                             Also if the API is called from any other Appl function other than IO control parameter functions, E_NOT_OK shall be returned.
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveIOCBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16)
{

    /* Update the DID value currently under process */
    /*Check if s_IsIOCBISubfuncCalled is set to TRUE*/
    if (s_IsIOCBISubfuncCalled_b != FALSE)
    {
        *dataDid_u16 = s_ActiveDid_u16;
        return (E_OK);
    }
    else
    {
        /* if this API is called from anywhere else, other than from the supported sub-functions */
        return E_NOT_OK;
    }
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif      /* #if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) */

/* FC_VariationPoint_START */
/*<BASDKey>
 **********************************************************************************************************************
 * $History___:
 *
 * AR40.11.0.0; 1     07.01.2016 MER3KOR
 *   CSCRM01026022
 *
 * AR40.11.0.0; 0     21.12.2015 MER3KOR
 *   CSCRM1014809
 *
 * AR40.10.0.0; 5     14.07.2015 WUG3ABT
 *   Checkout by wug3abt
 *
 * AR40.10.0.0; 4     01.07.2015 GET1COB
 *   CSCRM00788438
 *
 * AR40.10.0.0; 3     14.05.2015 CRA4KOR
 *   CSCRM00737827
 *
 * AR40.10.0.0; 2     14.05.2015 CRA4KOR
 *   CSCRM00836371
 *
 * AR40.10.0.0; 1     17.02.2015 PJR4KOR
 *   CSCRM00649704
 *
 * AR40.10.0.0; 0     13.02.2015 GET1COB
 *   CSCRM00747026
 *
 * AR40.9.0.0; 3     30.12.2014 GET1COB
 *   CSCRM00724044
 *
 * AR40.9.0.0; 2     15.11.2014 GET1COB
 *   CSCRM00726622
 *
 * $
 **********************************************************************************************************************
 </BASDKey>*/

/* FC_VariationPoint_END */
