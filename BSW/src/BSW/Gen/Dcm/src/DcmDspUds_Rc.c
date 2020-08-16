

#include "DcmDspUds_Rc_Inf.h"
#include "DcmDspUds_Uds_Prot.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)

#define DSP_RC_MINREQLEN            0x03u      /* Minimum request length of RC service excluding SID */
#define DSP_RC_SUBFUNCTION_ONE      0x01u
#define DSP_RC_SUBFUNCTION_THREE    0x03u


/* Definition of Routine Control Service State */
typedef enum
{
    DCM_RC_IDLE = 1,        /* Routine Control Service is IDLE, it is ready to accept a new request */
    DCM_RC_PENDING,         /* Routine Control Service is processing already received request */
    DCM_RC_CANCEL           /* Routine Control Service is cancelled by DSL-DSD */
}Dcm_DspRCStateType_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA)                                Dcm_RCInPtr_pu8;
P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA)                                Dcm_RCOutPtr_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static P2CONST(Dcm_DspRoutineType_tst, DCM_VAR, DCM_INTERN_CONST)   Dcm_adrRoutinePtr_pcst;
static P2CONST(Dcm_DspRoutineType_tst, AUTOMATIC, DCM_INTERN_CONST) s_adrRoutine_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspRCStateType_ten, DCM_VAR)                             Dcm_stDspRCState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint16,DCM_VAR)                                          s_dataStatusIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8,DCM_VAR)                                           Dcm_dataRCSubFunc_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint16,DCM_VAR)                                                 Dcm_RCCurrDataLength_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_NegativeResponseCodeType,DCM_VAR)                           Dcm_RCNegResCode_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_OpStatusType,DCM_VAR)                                       Dcm_RCOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean,DCM_VAR)                                             s_IsRCSubfunctionCalled_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 ******************************************************************************************************************
 * Dcm_Dsp_RC_Ini :
 *  Service Initialization for initializing Routine Control Service
 *
 * \param           None
 * \retval          None
 * \seealso
 ******************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_RC_Ini ( void )
                                {
    VAR(uint16_least,AUTOMATIC)                                     idxLoop_qu16;
    Dcm_RCOpStatus_u8 = DCM_CANCEL;
    if ( Dcm_stDspRCState_en == DCM_RC_PENDING )
    {
        /* Service Initialization may have been triggered due to protocol preemption, thus
        it is required to inform the Application/RTE about the CANCEL operation */
        /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
         * Hence tehre is no data inconsistency involved and the lock is not necessary. */
        /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
        s_IsRCSubfunctionCalled_b = TRUE;
        (void)(*Dcm_adrRoutinePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);
        /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
        s_IsRCSubfunctionCalled_b = FALSE;
    }

    /* Initialise the RoutinePtr to the first routine */
    s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];
    /* Search through the complete list of Routines */
    for ( idxLoop_qu16 = 0 ; idxLoop_qu16 < DCM_CFG_RC_NUMRIDS ; idxLoop_qu16++ )
    {
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)

        /*Check the status of the routine;if it is  DCM_ROUTINE_STOP_PENDING, call the StopRoutine function with Opstatus set to CANCEL*/
        if ( (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE) && (s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineStatus_aen[idxLoop_qu16]== DCM_ROUTINE_STOP_PENDING )  )
        {
            /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
             * Hence tehre is no data inconsistency involved and the lock is not necessary. */
            /*Set the flag for s_IsIOCBISubfuncCalled is to TRUE*/
            s_IsRCSubfunctionCalled_b = TRUE;
            (void)(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);
            /*Set the flag for s_IsIOCBISubfuncCalled is to FALSE*/
            s_IsRCSubfunctionCalled_b = FALSE;
        }
#endif
        if (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 >= DCM_CFG_MAX_WAITPEND)
        {
            /* Do nothing*/
            /* Service ini is called because of general reject.no need to reset the status of started  routines*/
        }
        else
        {
            /*Now set the status of the routine to default*/
            Dcm_RoutineStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
        }
        /* Increment the pointer to point to the next RId */

        s_adrRoutine_pcst++;
    }


    Dcm_RCOpStatus_u8 = DCM_INITIAL;
    Dcm_stDspRCState_en = DCM_RC_IDLE;
                                }

/**
 ******************************************************************************************************************
 * Dcm_DcmRoutineControl :
 *  Service Interpreter for controlling routines.
 *  This service is used for activation of routines in ECU from tester.
 *  This service has below given sub-functions.
 *  dataSubFunc_u8 0x01: 'StartRoutine'. Start the routine specified by RoutineIdentifier
 *  dataSubFunc_u8 0x02: 'StopRoutine'. Stop the routine specified by RoutineIdentifier
 *  dataSubFunc_u8 0x03: 'RequestRoutineResults'. Return the results of the routine specified by RoutineIdentifier
 *
 * \param           pMsgContext    Pointer to message structure
 *                                 (parameter in : RequestLength, Response buffer size, request bytes)
 *                                 (parameter out: Response bytes and Response length )
 *
 * \retval          None
 * \seealso
 *
 ******************************************************************************************************************
 */

/*MR12 RULE 8.3 VIOLATION: : The parameter identifiers in this function declaration differ from those in a previous declaration. MISRA C:2012 Rule-8.3*/
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmRoutineControl(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegResCode_u8)
{
    P2CONST(Dcm_DspRoutineSignalInfo_tst, AUTOMATIC, DCM_INTERN_CONST)  adrSignal_pcst;
#if (DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
    VAR(uint32, AUTOMATIC)                                          dataSigVal_u32;
#endif
    VAR(uint16,AUTOMATIC)                                           dataRId_u16;
    VAR(uint16,AUTOMATIC)                                           nrCtrlOptRecSize_u16;
    VAR(uint16_least,AUTOMATIC)                                     idxLoop_qu16;
    VAR(Std_ReturnType,AUTOMATIC)                                   dataRetVal_u8;
    VAR(uint8,AUTOMATIC)                                            dataSubFunc_u8;
    VAR(uint8,AUTOMATIC)                                            nrSig_u8;
    VAR(boolean, AUTOMATIC)                                         flgModeRetVal_b;
    VAR(boolean, AUTOMATIC)                                         flgProcessReq_b;
    VAR(boolean, AUTOMATIC)                                         flgReqSequenceError_b;
    *dataNegResCode_u8 = 0;
    adrSignal_pcst = NULL_PTR;
    /*Initialize the flag for mode return value is to TRUE*/
    flgModeRetVal_b =TRUE;
    /*Initialize the flag for Process request flag is to TRUE*/
    flgProcessReq_b =TRUE;
    /*Initialize the flag for Request sequence error is to FALSE*/
    flgReqSequenceError_b = FALSE;
    dataRetVal_u8=DCM_E_PENDING;

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_RC_Ini();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    {
        if ( Dcm_stDspRCState_en == DCM_RC_IDLE )
        {
            /* Routine Control Service is IDLE i.e. this is the first call of this service for this request */
            if ( pMsgContext->reqDataLen >= DSP_RC_MINREQLEN )
            {
                /* At least the sub-function and two bytes of dataRId_u16 should have been received to validate further */
                dataSubFunc_u8 = pMsgContext->reqData[0];
                /* uint32 variable for storing RID in a single variable */
                dataRId_u16 = (uint16)((uint16)pMsgContext->reqData[1] <<(uint8)8);
                dataRId_u16 = (uint16)(dataRId_u16 | pMsgContext->reqData[2]);
                /* From the received length indicated to this service check what is left after these three bytes */
                nrCtrlOptRecSize_u16 = (uint16)(pMsgContext->reqDataLen - 3u);

                /* Initialise the s_adrRoutine_pcst to the first routine */
                s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];

                /* Search through the complete list of Routines to find if the received dataRId_u16 matches to any of the configured dataRId_u16 */
                for ( idxLoop_qu16 = 0 ; idxLoop_qu16 < DCM_CFG_RC_NUMRIDS ; idxLoop_qu16++ )
                {
                    if ( dataRId_u16 == s_adrRoutine_pcst->dataRId_u16 )
                    {
                        /* Match found, break free from the for loop */

#if(DCM_CFG_DSP_NUMISRIDAVAIL>0)
                        /* Check if the RIS is supported in current variant */
                        if(*Dcm_RIDIsAvail[s_adrRoutine_pcst->idxRIDSupportedFnc_u16] != NULL_PTR)
                        {
                            if((*(IsRIDAvailFnc_pf)(Dcm_RIDIsAvail[s_adrRoutine_pcst->idxRIDSupportedFnc_u16]))(s_adrRoutine_pcst->dataRId_u16)!=E_OK)
                            {
                                /* Routine Identifier is not supported  in the current variant */
                                *dataNegResCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            }
                        }
#endif

#if (DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
                        /*If negative respone code is set to 0x00 and stop routine flag is set to TRUE for the routine session and Dcm Routine stop call returns pending */
                        if((*dataNegResCode_u8 ==0x00) && (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE)&& (s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && ( Dcm_RoutineStatus_aen[idxLoop_qu16] == DCM_ROUTINE_STOP_PENDING ))
                        {
                            /*Since the status of the Routine is DCM_ROUTINE_STOP_PENDING ,call the StopRoutine with OpStatus set to DCM_CANCEL  */
                            Dcm_RCOpStatus_u8 = DCM_CANCEL;
                            /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
                             * Hence tehre is no data inconsistency involved and the lock is not necessary. */
                            /*Set the flag for s_IsRCSubfunctionCalled is to TRUE*/
                            s_IsRCSubfunctionCalled_b = TRUE;
                            (void)(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);
                            /*Set the flag for s_IsRCSubfunctionCalled and Process request status are FALSE*/
                            s_IsRCSubfunctionCalled_b = FALSE;
                            flgProcessReq_b = FALSE;
                            Dcm_RoutineStatus_aen[idxLoop_qu16] = DCM_ROUTINE_STOP;
                        }

                        Dcm_RCOpStatus_u8 = DCM_INITIAL;
#endif
                        /* If NRC is not set */
                        if(*dataNegResCode_u8 ==0x00)
                        {
                            /*Store the index for getting the status in the next main function call*/
                            s_dataStatusIdx_u16 = (uint16)(idxLoop_qu16);
                        }
                        break;
                    }
                    /* Increment the pointer to point to the next dataRId_u16 */

                    s_adrRoutine_pcst++;
                }
                /*If Process request status is set to TRUE and negative response code is set 0x00 */
                if((flgProcessReq_b != FALSE) && (*dataNegResCode_u8 ==0x00u))
                {
                    /* If dataRId_u16 is valid, then check if its allowed to execute that Routine in the active session and check if it is available in current DCM configuration if post build is enabled */
                    if ( ( idxLoop_qu16 != DCM_CFG_RC_NUMRIDS ) &&
                          ( (( dataSubFunc_u8 == 0x01u ) &&  ( ( Dcm_DsldGetActiveSessionMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMaskStartRoutine_u32 )) != 0u ))
                                  ||  (( dataSubFunc_u8 == 0x02u ) &&  ( ( Dcm_DsldGetActiveSessionMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMaskStopRoutine_u32 )) != 0u ))
                                  ||  (( dataSubFunc_u8 == 0x03u ) &&  ( ( Dcm_DsldGetActiveSessionMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMaskRequestResults_u32 )) != 0u )))
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
                            &&
                            ( (Dcm_ActiveConfiguration_u8 & Dcm_DspRoutine_cast[idxLoop_qu16].dataConfigMask_u8)!= 0u)
#endif
                    )
                    {
                        /* Check now if its allowed to execute that Routine in the active security level */
                        if( (( dataSubFunc_u8 == 0x01u ) && ( ( Dcm_DsldGetActiveSecurityMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMaskStartRoutine_u32 )) != 0u ))
                                || (( dataSubFunc_u8 == 0x02u ) && ( ( Dcm_DsldGetActiveSecurityMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMaskStopRoutine_u32 )) != 0u ))
                                || (( dataSubFunc_u8 == 0x03u ) && ( ( Dcm_DsldGetActiveSecurityMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMaskRequestResults_u32 )) != 0u )))
                        {

                            /* StartRoutine sub-function is a mandatory for any routine, but RequestResults and StopRoutine
                             * aren't. Thus, it is required to check if requested sub-function is supported for that routine
                             * which was requested */
                            if (( ( dataSubFunc_u8 == 0x01u ) && ( s_adrRoutine_pcst->flgStartRoutine_b != FALSE ))||   \
                                    ( ( dataSubFunc_u8 == 0x02u ) && ( s_adrRoutine_pcst->flgStopRoutine_b != FALSE  ))||   \
                                    ( ( dataSubFunc_u8 == 0x03u ) && ( s_adrRoutine_pcst->dataReqRslt_b != FALSE ) ) )
                            {
                                /* Initialize the global variables to retain the values in case of DCM_E_PENDING */
                                Dcm_adrRoutinePtr_pcst = s_adrRoutine_pcst;
                                Dcm_dataRCSubFunc_u8 = dataSubFunc_u8;
                                Dcm_RCOpStatus_u8 = DCM_INITIAL;
                                Dcm_RCNegResCode_u8 = 0;
                                Dcm_RCCurrDataLength_u16 = 0;
                                Dcm_stDspRCState_en = DCM_RC_PENDING;
                                nrSig_u8 = 0;

                                /*
                                 * Now check if the total request length is valid based on
                                 * 1. If that routine is FixedLength or not
                                 *   a. If FixedLength is TRUE, then the match should be for the exact length
                                 *   b. If FixedLength is FALSE, then the check should be that the received length is not more
                                 *   than the maximum length, but also not less to miss out the fixed signals within that dataRId_u16
                                 */
                                if ( ( dataSubFunc_u8 == 0x01u ) &&
                                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) ||
                                                ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStart_u16 ) &&
                                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16 ) ) ) )
                                {


#if(DCM_CFG_STARTSUPPORTED != DCM_CFG_OFF)
                                        adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrStartInSignalRef_cpcst;
                                        nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrStartInSignals_u8;
                                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16);
                                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStart_u16]);
                                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16]);
#endif
                                }

#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
                                else if ( ( dataSubFunc_u8 == 0x02u ) &&
                                        ( ( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) ||
                                                ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                                        ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeStop_u16 ) &&
                                                        ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16 ) ) ) )
                                {
                                    /* Process the Stop request in case -
                                     * 1.If Stop request comes without a start request in case Start routine is not supported
                                     * 2.If Stop request comes without a start request or after a stop request in case RequestSequenceError is disabled and Start Routine is supported
                                     * 3.If Stop request comes after a start request or start and request results request in case RequestSequenceError is enabled or disabled
                                     */

                                    if (((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])&& (s_adrRoutine_pcst->flgStartRoutine_b==FALSE ))||
                                            (((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) || (DCM_ROUTINE_STOP == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]))&& ( s_adrRoutine_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                                            ((DCM_ROUTINE_IDLE != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) &&(DCM_ROUTINE_STOP != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])))
                                    {
                                        adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrStopInSignalRef_cpcst;
                                        nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrStopInSignals_u8;
                                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16);
                                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeStop_u16]);
                                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16]);
                                    }
                                    else
                                    {
                                        /* Checking for the request sequence error */
                                        /*Flag for request Sequence Error is set TRUE*/
                                        flgReqSequenceError_b = TRUE;
                                    }
                                }
#endif
#if(DCM_CFG_REQRESULTSSUPPORTED != DCM_CFG_OFF)
                                /*Special case:Request results with control option record*/
                                else if  ((dataSubFunc_u8 == 0x03u) &&
                                        (( nrCtrlOptRecSize_u16 == s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16) ||
                                        ( ( s_adrRoutine_pcst->dataFixedLen_b == FALSE ) &&
                                                ( nrCtrlOptRecSize_u16 <= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataCtrlOptRecSizeReqRslt_u16  ) &&
                                                ( nrCtrlOptRecSize_u16 >= s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16 ) ) ))

                                {
                                  /* Process the requestResults request -
                                     * 1. If Request results request comes without a start request for routines which so not support Start Routine
                                     * 2. If Request results request comes for a Routine which is not started but supports Start Routine and RequestSequenceError is disabled
                                     * 3. If Request results request comes for a Routine which is stared irrespective of whether RequestSequence error is enabled/disabled */
                                    if (((DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16]) && (s_adrRoutine_pcst->flgStartRoutine_b==FALSE) )||
                                            (( DCM_ROUTINE_IDLE == Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])&& ( s_adrRoutine_pcst->flgReqSequenceErrorSupported_b==FALSE))||
                                            ((DCM_ROUTINE_IDLE != Dcm_RoutineStatus_aen[s_dataStatusIdx_u16])))
                                    {
                                        adrSignal_pcst = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrReqRslInSignalRef_cpcst;
                                        nrSig_u8 = s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->nrReqRslInSignals_u8;
                                        Dcm_RCCurrDataLength_u16 = (uint16)(nrCtrlOptRecSize_u16 - s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16);
                                        Dcm_RCInPtr_pu8 = &(pMsgContext->reqData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinCtrlOptRecSizeReqRslt_u16]);
                                        Dcm_RCOutPtr_pu8 = &(pMsgContext->resData[3+s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16]);
                                    }
                                    else
                                    {
                                        /* Checking for the request sequence error */
                                        /*Flag for request Sequence Error is set TRUE*/
                                        flgReqSequenceError_b = TRUE;
                                    }
                                }
#endif
                                else
                                {
                                    /* Received message has a invalid length for this RID */
                                    *dataNegResCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                                    /* Reset the RC State back to IDLE so that it does not process the request further */
                                    Dcm_stDspRCState_en = DCM_RC_IDLE;
                                }

                                if(*dataNegResCode_u8 == 0)
                                {
                                    /*If control option record is present in the request call the appl function to check the validity */
                                    if(nrCtrlOptRecSize_u16 > 0)
                                    {
                                        dataRetVal_u8 = DcmAppl_DcmCheckRoutineControlOptionRecord(dataRId_u16,dataSubFunc_u8,&pMsgContext->reqData[3],nrCtrlOptRecSize_u16);
                                        if (E_OK != dataRetVal_u8)
                                        {   /*Control option record is incorrect.*/
                                            *dataNegResCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                                        }
                                    }
                                    if(*dataNegResCode_u8 == 0)
                                    {
                                        /**********Mode rule Check*************/
                                        if(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct!=NULL_PTR)
                                        {
                                            /* Call the configured Dcm Appl API to do RID specific checks */
                                            dataRetVal_u8 = (*s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrUserRidModeRule_pfct)(dataNegResCode_u8,dataRId_u16,dataSubFunc_u8);
                                        }
                                        else
                                        {
                                            /* Call the user Dcm Appl API to do RID specific checks */
                                            dataRetVal_u8 = DcmAppl_UserRIDModeRuleService(dataNegResCode_u8,dataRId_u16,dataSubFunc_u8);
                                        }
                                        /* Ignore the NRC in case the DcmAppl API returns TRUE */
                                        if(dataRetVal_u8 !=E_OK)
                                        {
                                            if(*dataNegResCode_u8==0x00)
                                            {
                                                *dataNegResCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                                            }
                                            flgModeRetVal_b = FALSE;
                                        }
                                        else
                                        {
                                            *dataNegResCode_u8=0x00;
                                        }
#if(DCM_CFG_DSP_MODERULEFORROUTINES != DCM_CFG_OFF)
                                        if(*dataNegResCode_u8 == 0x00)
                                        {
                                            if (( dataSubFunc_u8 == 0x01u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct != NULL_PTR))
                                            {

                                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStart_pfct))(dataNegResCode_u8);
                                            }
                                            else if (( dataSubFunc_u8 == 0x02u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct != NULL_PTR))

                                            {
                                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForStop_pfct))(dataNegResCode_u8);
                                            }
                                            else if (( dataSubFunc_u8 == 0x03u ) && (s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct != NULL_PTR))
                                            {
                                                flgModeRetVal_b=(*(s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->adrModeRuleForRequestResult_pfct))(dataNegResCode_u8);
                                            }
                                            else
                                            {
                                                /*dummy else */
                                            }
                                        }
#endif
                                        if(flgModeRetVal_b == FALSE)
                                        {
                                            Dcm_stDspRCState_en = DCM_RC_IDLE;
                                        }
                                        else
                                        {
                                            /* Request sequence error check */

                                            if(flgReqSequenceError_b !=FALSE)
                                            {
                                                *dataNegResCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
                                                Dcm_stDspRCState_en = DCM_RC_IDLE;
                                            }
                                            else
                                            {
                                                /*DCM_CFG_ROUTINEVARLENGTH shall be DCM_CFG_ON only if all the RIDs are of variable length and no fixed length signals are configured under them*/
#if (DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
                                                for ( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && (*dataNegResCode_u8==0x00)&& (adrSignal_pcst!=NULL_PTR) &&( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
                                                {
#if (DCM_CFG_ROUTINEARRAY_INSIG != DCM_CFG_OFF)
                                                   if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
                                                   {
                                                     Dcm_RcSetSignalArray(adrSignal_pcst,&(pMsgContext->reqData[3]));
                                                   }
                                                   else
#endif
                                                   {
                                                        dataSigVal_u32 = 0;
                                                        dataSigVal_u32 = Dcm_GetSignal_u32(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->reqData[3]),adrSignal_pcst->dataEndianness_u8);
                                                        Dcm_RCSetSigVal(adrSignal_pcst->dataType_u8,adrSignal_pcst->idxSignal_u16,dataSigVal_u32);
                                                   }
                                                    adrSignal_pcst++;
                                                }

#endif
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u)
                                               if(adrSignal_pcst != NULL_PTR)
                                               {
                                                /* Copy Varialble length Control Option Record into buffer */
                                                   if((adrSignal_pcst->dataType_u8 == DCM_VARIABLE_LENGTH) && (Dcm_RCCurrDataLength_u16 != 0x00))
                                                   {
                                                       /*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
                                                       DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]),Dcm_RCInPtr_pu8 ,Dcm_RCCurrDataLength_u16);
                                                   }
                                               }
#endif
                                             }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                /* Requested Sub-Function is not supported for this RID */
                                *dataNegResCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                            }
                        }
                        else
                        {
                            /* Routine Control has failed the Security Check */
                            *dataNegResCode_u8 = DCM_E_SECURITYACCESSDENIED;
                        }
                    }
                    else
                    {
                        if((dataSubFunc_u8 >= DSP_RC_SUBFUNCTION_ONE) && (dataSubFunc_u8 <= DSP_RC_SUBFUNCTION_THREE))
                        {
                            *dataNegResCode_u8=DCM_E_REQUESTOUTOFRANGE;
                        }
                        else
                        {
                            *dataNegResCode_u8 =DCM_E_SUBFUNCTIONNOTSUPPORTED;
                        }
                    }
                }
            }
            else
            {
                /* Invalid message length */
                *dataNegResCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        if (Dcm_stDspRCState_en == DCM_RC_PENDING )
        {
            /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
             * Hence tehre is no data inconsistency involved and the lock is not necessary. */
            /*Set the Flag for s_IsRCSubfunctionCalled_b is set to TRUE*/
            s_IsRCSubfunctionCalled_b = TRUE;
            dataRetVal_u8 = (*Dcm_adrRoutinePtr_pcst->adrCallRoutine_pfct)(Dcm_dataRCSubFunc_u8);
            /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
             * Hence tehre is no data inconsistency involved and the lock is not necessary. */
            s_IsRCSubfunctionCalled_b = FALSE;
            /*Check for Infrastructure Error present or not and use routine port is supported */
            if((Dcm_IsInfrastructureErrorPresent_b(dataRetVal_u8) != FALSE) && (Dcm_adrRoutinePtr_pcst->UsePort != FALSE))
            {
                dataRetVal_u8 = DCM_INFRASTRUCTURE_ERROR;
            }
            if (dataRetVal_u8 == E_OK)
            {
                if ( Dcm_dataRCSubFunc_u8 == 0x01 )
                {
#if(DCM_CFG_STARTSUPPORTED != DCM_CFG_OFF)
                    adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrStartOutSignalRef_cpcst;
                    nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrStartOutSignals_u8;
                    pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStart_u16;

                    /*Routine is Started  ,Set the status to RC_START_OK  */
                    Dcm_RoutineStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STARTED;
#endif
                }
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
                else if ( Dcm_dataRCSubFunc_u8 == 0x02 )
                {
                    adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrStopOutSignalRef_cpcst;
                    nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrStopOutSignals_u8;
                    pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeStop_u16;
                    /*Routine is Stopped   ,Set the  status to default status DCM_ROUTINE_STOP  */
                    Dcm_RoutineStatus_aen[s_dataStatusIdx_u16] = DCM_ROUTINE_STOP;
                }
#endif
                else
                {
#if(DCM_CFG_REQRESULTSSUPPORTED != DCM_CFG_OFF)
                    adrSignal_pcst = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->adrReqRsltOutSignalRef_cpcst;
                    nrSig_u8 = Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->nrReqRsltOutSignals_u8;
                    pMsgContext->resDataLen = 3u + (uint32)Dcm_adrRoutinePtr_pcst->adrRoutineInfoRef_cpcst->dataMinStsOptRecSizeReqRslt_u16;
#endif
                }
                for ( idxLoop_qu16 = 0 ; ( ( idxLoop_qu16 < nrSig_u8 ) && ( adrSignal_pcst->dataType_u8 != DCM_VARIABLE_LENGTH ) ) ; idxLoop_qu16++ )
                {
#if(DCM_CFG_ROUTINEVARLENGTH == DCM_CFG_OFF)
#if(DCM_CFG_ROUTINEARRAY_OUTSIG != DCM_CFG_OFF)
                    if(adrSignal_pcst->dataType_u8 >= DCM_RCARRAYINDEX)
                    {
                        Dcm_RcStoreSignalArray(adrSignal_pcst,&(pMsgContext->resData[3]));
                    }
                    else
#endif
                    {
                        dataSigVal_u32 = Dcm_RCGetSigVal_u32 ( adrSignal_pcst->dataType_u8, adrSignal_pcst->idxSignal_u16 );
                        Dcm_StoreSignal(adrSignal_pcst->dataType_u8, adrSignal_pcst->posnStart_u16, &(pMsgContext->resData[3]), dataSigVal_u32, adrSignal_pcst->dataEndianness_u8 );
                    }
#endif
                    adrSignal_pcst++;
                }

                if ( idxLoop_qu16 != nrSig_u8 )
                {
                    /* You enter here only if the last signal has dynamic or variable length */
                    pMsgContext->resDataLen = pMsgContext->resDataLen + Dcm_RCCurrDataLength_u16;
                }

                /* First byte after Service Id is the routineControlType or Sub-function byte */
                pMsgContext->resData[0] = Dcm_dataRCSubFunc_u8;
                /* Second and third byte is the two byte dataRId_u16 */
                pMsgContext->resData[1] = ( uint8 )( Dcm_adrRoutinePtr_pcst->dataRId_u16 >> 8u ) ;
                pMsgContext->resData[2] = ( uint8 )( Dcm_adrRoutinePtr_pcst->dataRId_u16 & 0x00ffu ) ;

                Dcm_stDspRCState_en = DCM_RC_IDLE;
            }
            else if (dataRetVal_u8 == E_NOT_OK)
            {
                /* Copy the NRC value which has been updated by Application to the local variable */
                if ( Dcm_RCNegResCode_u8 != 0 )
                {
                    *dataNegResCode_u8 = Dcm_RCNegResCode_u8;
                }
                else
                {
                    /* Conditions Not Correct is set as the Application did not fill in any NegativeResponseCode but have returned E_NOT_OK */
                    *dataNegResCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            else if (dataRetVal_u8 == DCM_E_PENDING)
            {
                /* Nothing to be done here except for setting the OpStatus, DSL/DSD shall trigger this service again in the next main function call */
                Dcm_RCOpStatus_u8 = DCM_PENDING;

                /* As NRC code has been updated, terminate processing and send NRC to tester */
            }
            else if (dataRetVal_u8 == DCM_E_FORCE_RCRRP)
            {
                /*Do nothing NRC78 is triggered from the Statemachine*/
                Dcm_RCOpStatus_u8=DCM_FORCE_RCRRP_OK;
            }
            else if ((dataRetVal_u8 == DCM_INFRASTRUCTURE_ERROR) && (Dcm_adrRoutinePtr_pcst->UsePort != FALSE))
            {
                *dataNegResCode_u8 = DCM_E_GENERALREJECT;
            }
            else
            {
                if ( Dcm_RCNegResCode_u8 == 0 )
                {
                    /* Function returns a return value not defined within Routine Control service, but hasn't set NRC */
                    *dataNegResCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
                else
                {
                    /* As NRC code has been updated, terminate processing and send NRC to tester */
                    *dataNegResCode_u8 = Dcm_RCNegResCode_u8;
                }
            }
        }

        if (*dataNegResCode_u8 != 0 )
        {
            /* dataNegResCode_u8 has been set, inform DSL-DSD of Negative Response and end the service processing */
            Dcm_stDspRCState_en = DCM_RC_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}

/**
 ******************************************************************************************************************
 * Dcm_DcmcallStopRoutine :
 * This API stops all the routines in case there is a session transition.
 * The API is called by Dcm_RoutineSetSesCtrlType() function.
 *
 * \param           idxLoop_qu16    index of the Routine that has to be stopped
 *
 * \retval          None
 *
 * \seealso
 *
 ******************************************************************************************************************
 */
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_DcmcallStopRoutine(VAR(uint16_least,AUTOMATIC) idxLoop_qu16);
static FUNC(void,DCM_CODE) Dcm_DcmcallStopRoutine(VAR(uint16_least,AUTOMATIC) idxLoop_qu16)
        {
    VAR(Std_ReturnType, AUTOMATIC) dataRetType_u8;
    /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
     * Hence tehre is no data inconsistency involved and the lock is not necessary. */
    /*Set the s_IsRCSubfunctionCalled flag to TRUE*/
    s_IsRCSubfunctionCalled_b = TRUE;
    dataRetType_u8=(*s_adrRoutine_pcst->adrCallRoutine_pfct)(DCM_RC_STOPROUTINE);
    /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
     * Hence tehre is no data inconsistency involved and the lock is not necessary. */
    s_IsRCSubfunctionCalled_b = FALSE;


    /*If the return value is E_PENDING ,set the status of the routine to  DCM_ROUTINE_STOP_PENDING. that in the next service
                    call for the same RID the stop routine will be called with Opstatus set to DCM_CANCEL */
    if  (dataRetType_u8 == DCM_E_PENDING)
    {
        /* StopRoutine returned DCM_E_PENDING.Set the routine status to DCM_ROUTINE_STOP_PENDING */
        Dcm_RoutineStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP_PENDING;
    }
    else
    {
        /* StopRoutine returned return value other than DCM_E_PENDING.Set the routine status to DCM_ROUTINE_STOP */
        Dcm_RoutineStatus_aen[idxLoop_qu16]  = DCM_ROUTINE_STOP;
    }

        }
#endif

/**
 ******************************************************************************************************************
 * Dcm_RoutineSetSesCtrlType :
 * This API stops all the routines in case there is a session transition.
 * The API is called by Dcm_SetSesCtrlType() function.
 *
 * \param           dataSesCtrlType_u8    New session control type value
 *
 * \retval          None
 *
 * \seealso
 *
 ******************************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_RoutineSetSesCtrlType (VAR(Dcm_SesCtrlType, AUTOMATIC) dataSesCtrlType_u8)
{

    VAR (uint16_least,AUTOMATIC) idxLoop_qu16;


    /* Initialise the RoutinePtr to the first routine */
    s_adrRoutine_pcst =  &Dcm_DspRoutine_cast[0];
    /* Search through the complete list of Routines */
    for ( idxLoop_qu16 = 0 ; idxLoop_qu16 < DCM_CFG_RC_NUMRIDS ; idxLoop_qu16++ )
    {
#if(DCM_CFG_STOPSUPPORTED != DCM_CFG_OFF)
        /* Check whether the flgStopRoutineOnSessionChange_b is supported for this RID and the routine is already started
         * The condition will never be satisfied for Routines which does not support Start sub function or Supports  Start start subfunction but sequence error is disabled as
         * the state of thr Routine will be DCM_ROUTINE_STARTED only if a Start request is received */
        if ( (s_adrRoutine_pcst->flgStopRoutine_b!= FALSE)&&(s_adrRoutine_pcst->flgStopRoutineOnSessionChange_b != FALSE) && (Dcm_RoutineStatus_aen[idxLoop_qu16] == DCM_ROUTINE_STARTED))
        {
            if(dataSesCtrlType_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
            {
                Dcm_DcmcallStopRoutine(idxLoop_qu16);
            }
            else
            {
                /* Check whether the RID is supported in the current session and security */
                if  (( (Dcm_DsldGetActiveSessionMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSessBitMaskStopRoutine_u32 )) == 0u )|| ( ( Dcm_DsldGetActiveSecurityMask_u32() & ( s_adrRoutine_pcst->adrRoutineInfoRef_cpcst->dataSecBitMaskStopRoutine_u32 )) == 0u ) )
                {
                    /* Call stop routine for the RID*/
                    Dcm_DcmcallStopRoutine(idxLoop_qu16);
                }
            }
        }
#endif
        /* Increment the pointer to point to the next RId */

        s_adrRoutine_pcst++;
    }

}

/**
 *************************************************************************************************************************************************************
 * Dcm_SetFlagforRC:
 *
 * This API sets/resets the flag which is required for getting the active RID based on the input parameter
 *
 *
 * \param     boolean isFlag_b : parameter for setting or resetting the flag to get the active RID
 * \retval    None
 * \seealso
 *
 **************************************************************************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_SetFlagforRC(VAR (boolean,AUTOMATIC) isFlag_b)
 {
    /* Setting/resetting the flag so that the application can call GetActiveRID function from DcmAppl_DcmConfirmation */
    s_IsRCSubfunctionCalled_b = isFlag_b;
}
/**
 *******************************************************************************
 * Dcm_Prv_DspRCConfirmation : API used for confirmation of response sent for
 *                                      RoutineControl (0x31) service.
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
 FUNC(void, DCM_CODE) Dcm_Prv_DspRCConfirmation(
    VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
    VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
    VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
        if(dataIdContext_u8 == DCM_DSP_SID_ROUTINECONTROL)
        {

            Dcm_SetFlagforRC(TRUE);
        }
DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
                                                                    status_u8);
        if(dataIdContext_u8 == DCM_DSP_SID_ROUTINECONTROL)
        {
            Dcm_SetFlagforRC(FALSE);
        }
}

/**
 ******************************************************************************************************************
 * Dcm_GetActiveRid :
 * API to provide the current active RID.
 * This API has to be called from the application callbacks of Start, Stop and Req.Results routine configured for the project and also from the DcmAppl_DcmConfirmation.
 * Example scenarios:
 *  a) This API has to be called by the application
 *      a.1)during Start, Stop and Request Results operations for the normal tester request
 *      a.2)during canceling the pending operations either Start or Stop or Request Results due to CANCEL operation triggered by Dcm by setting the Opstatus to DCM_CANCEL in the RC Ini function.
 *      a.3)during the stop of the routines due to session transitions (either due to protocol start/stop or session time out/change).
 * By "Active RID", it means that the active RID index under processing and not the RIDs of already started routines.
 *
 * \param           dataRid_u16    Buffer to get the current active RID

 *
 * \retval          Std_ReturnType  E_OK : The parameter dataRid_u16 contains valid RID value in this case.
 *                                  E_NOT_OK : The parameter dataRid_u16 contains invalid data in case none of the Routine is under processing.
 * \seealso
 *
 ******************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataRid_u16)
{
    /* Multicore: There is a constraint on the callback that GetActiveRid can only be called from Start, Stop and Request results subfunction.
     * Hence tehre is no data inconsistency involved and the lock is not necessary. */
     /*Check if the s_IsRCSubfunctionCalled flag is set to TRUE and current active id is valid*/
    if ((s_IsRCSubfunctionCalled_b != FALSE) && (dataRid_u16!= NULL_PTR))
    {
        if ( Dcm_stDspRCState_en == DCM_RC_PENDING )
        {
            *dataRid_u16 = Dcm_adrRoutinePtr_pcst->dataRId_u16 ;
        }
        else
        {
            *dataRid_u16 = s_adrRoutine_pcst->dataRId_u16 ;
        }
        return E_OK;
    }
    else
    {
        return E_NOT_OK;
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif      /* DCM_CFG_DSP_ROUTINECONTROL_ENABLED */
#endif

