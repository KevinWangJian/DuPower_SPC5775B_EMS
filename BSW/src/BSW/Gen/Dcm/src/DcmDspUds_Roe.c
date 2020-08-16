

#include "DcmDspUds_Roe_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Roe_Priv.h"

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 VAR (uint8,DCM_VAR) Dcm_RoeDidIdx_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspRoeState_ten, DCM_VAR) Dcm_stDspRoeState_en;                  /* State for ROE state machine */
static VAR(Dcm_DspRoeEventState_ten, DCM_VAR) s_DcmOldRoeDtcState;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8,  DCM_VAR) Dcm_stRoeEventWindowTime_u8; /* Variable to store the Roe Event window Time */
static VAR(uint8, DCM_VAR) Dcm_stEventType_u8; /* Variable to store the Roe Event Type */
static VAR(Dcm_OpStatusType,  DCM_VAR) Dcm_stRoeOpstatus_u8; /* Variable to store the Roe Opstatus*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeStorageState_b; /* Variable to store the storage bit information */
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeDidOpStatusIsPending_b; /* Variable to store the storage bit information */
static VAR(boolean,     DCM_VAR) Dcm_stDspRoeDtcOpStatusIsPending_b; /* Variable to store the storage bit information */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDidEventType(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDidEvent(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDidEventInfo(VAR(Std_ReturnType, AUTOMATIC) dataDoeDidIdx_u8,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDtcEvent(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDtcEventType(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDtcEventInfo(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
#endif

static FUNC(void,DCM_CODE)Dcm_RoeLengthCheck(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
static FUNC(void,DCM_CODE) Dcm_CheckRoeEventType(void);
static FUNC(void,DCM_CODE) Dcm_ReportRoeEvents(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext);
static FUNC(void,DCM_CODE)Dcm_RoeCtrlConditionAndSequenceCheck(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

/**
 **************************************************************************************************
 * Dcm_DcmResponseOnEventIni:
 * Initialisation function for Response On Event Service.
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DcmResponseOnEventIni (void)
                                                                                                {
VAR(Dcm_NegativeResponseCodeType, AUTOMATIC) NegRespCode_u8 = 0u ;
    if((DCM_PENDING == Dcm_stRoeOpstatus_u8) && (Dcm_stDspRoeState_en == DCM_DSP_ROE_SETUPEVENT))
    {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
        if (Dcm_stDspRoeDidOpStatusIsPending_b != FALSE)
        {
            /*Call DcmAppl_DcmSetUpRoeEvent with OpStatus DCM_CANCEL */
            (void)DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8, \
                    Dcm_stEventType_u8, \
                    FALSE, \
                    0x0u, \
                    NULL_PTR, \
                    NULL_PTR, \
                    DCM_CANCEL, \
                    &NegRespCode_u8 );
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE)
        {
            (void)DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDtcEvent.RoeEventId_u8, \
                    Dcm_stEventType_u8, \
                    Dcm_stDspRoeStorageState_b, \
                    Dcm_stRoeEventWindowTime_u8, \
                    NULL_PTR, \
                    NULL_PTR, \
                    DCM_CANCEL, \
                    &NegRespCode_u8 );
            Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        }
#endif
    }
    else if ((DCM_PENDING == Dcm_stRoeOpstatus_u8) && (Dcm_stDspRoeState_en == DCM_DSP_ROE_CONTROLEVENT))
    {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDidOpStatusIsPending_b != FALSE)
        {
            /*Call  DcmAppl_DcmStoreRoeDidInfo with OpStatus DCM_CANCEL*/
            (void)DcmAppl_DcmStoreRoeDidInfo(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventDid_u16,
                    DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8,
                    DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus,
                    DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].SourceAddress_u16,
                    DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeStorageState_b,
                    DCM_CANCEL,
                    DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeSessionIsDefault_b,
                    &NegRespCode_u8);
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE)
        {
            /*Call  DcmAppl_DcmStoreRDTCInfo with OpStatus DCM_CANCEL*/

            (void)DcmAppl_DcmStoreRoeDTCInfo (DcmDspRoeDtcEvent.RoeEventId_u8,
                    DcmDspRoeDtcStateVariable.RoeEventStatus,
                    DcmDspRoeDtcStateVariable.SourceAddress_u16,
                    DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8,
                    DcmDspRoeDtcStateVariable.stDspRoeStorageState_b,
                    DCM_CANCEL,
                    DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b,
                    &NegRespCode_u8);
            Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        }
#endif
    }
    else
    {
        /* Do nothing */
    }

    Dcm_stRoeOpstatus_u8=DCM_INITIAL;
    Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
    Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
    /* Reset the ROE state to default state */
    Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
    /* Reset all the static global variables */

    Dcm_stDspRoeStorageState_b = FALSE;
    (void)NegRespCode_u8;
                                                                                                }

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_ResetRoeOnDtcevents:
 * This function is used to unactivate all the Roeevents which was started iin a particular session
 * before transistioning to new session.
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */

FUNC(void,DCM_CODE)Dcm_ResetRoeOnDtcevents(void)
                                                                                                {
    VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];


    DcmDspRoeDtcStateVariable.SourceAddress_u16=0xFFu;
    DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;
    /*Initialize the Variable to store the storage bit information is to FALSE*/
    DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=FALSE;
    DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8=0x0u;


#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
    (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
    DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);

    if ((DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b != FALSE) && (dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]))
    {
        DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STARTED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STARTED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STARTED);
    }


                                                                                                }

#endif
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_ResetRoeDidevents:
 * This function is used to unactivate all the Roeevents which was started in a particular session
 * before transistioning to new session.
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ResetRoeDidevents(void)
                                                                                                {

    VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];

    /*Loop through all the ROE dids and invoke its Xxx_activate event indicating appication that the
     * ROE event is unactivated because of session transtion, it needs to send one start event to
     * activate the same now. */
    Dcm_RoeDidIdx_u8=0;
    while(Dcm_RoeDidIdx_u8<DCM_MAX_DIDROEEVENTS)
    {
        if(DCM_ROE_STARTED==DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)
        {
            /*If the application activates the ROE event for a particular DID, set the state machine of that
             * particular DID to start.*/
            /*Trigger the activate event to the application*/
            /*activate event successful, move the state variables to stopped state, otherwise remain in the
             * old state since activate was not successful*/

            DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus=DCM_ROE_STOPPED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8,DCM_ROE_STOPPED);
        }
        if ((DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].stDspRoeSessionIsDefault_b != FALSE) && (dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]))
        {
            DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus=DCM_ROE_STARTED;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].ROEDID_fp))(DCM_ROE_STARTED);
#endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[Dcm_RoeDidIdx_u8].RoeEventId_u8,DCM_ROE_STARTED);
        }
    Dcm_RoeDidIdx_u8++;
    }
                                                                                                }
#endif
/**
 **************************************************************************************************
 * Dcm_DcmResponseOnEvent : The ResponseOnEvent service requests a server to start stop or clear
 * transmission of responses on a specified event and setting up of events.
 * This service provides the possibility of automatically executing a diagnostic service in the
 * event that a specified event occurs in the server.
 *
 * \parameters           pMsgContext: Pointer to message structure
 *                                   (input : RequestLength, Response buffer size, request bytes)
 *                                   (output: Response bytes and Response length )
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 *                       OpStatus           : Information regarding the status of the service processing
 * \return value         None
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmResponseOnEvent (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {

    VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8;             /* Local variable to store return from DcmAppl API */

    *dataNegRespCode_u8 = 0x0u; /* Local variable initialisation */
    dataReturnVal_u8=E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/
    DCM_UNUSED_PARAM(OpStatus);

    if(DCM_CANCEL == OpStatus)
    {

        Dcm_DcmResponseOnEventIni();
        dataReturnVal_u8=E_OK;
    }
    else
    {

        /* Initialised state */
        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_INIT)
        {
            Dcm_RoeLengthCheck(pMsgContext,dataNegRespCode_u8);

        }

        /* EventType is startROE, stopROE or clearROE */
        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_CONTROLEVENT)
        {

            /* Copy the event window time to static  variable */
                       Dcm_stRoeEventWindowTime_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSWINDOWTIME];
            if(Dcm_stRoeOpstatus_u8!=DCM_PENDING)
            {
                Dcm_RoeCtrlConditionAndSequenceCheck(dataNegRespCode_u8);
            }

            if((*dataNegRespCode_u8 == 0x0u))
            {

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
                if( ((Dcm_stRoeOpstatus_u8==DCM_INITIAL)&&( Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)) || ( Dcm_stDspRoeDtcOpStatusIsPending_b == TRUE))
                {
                    dataReturnVal_u8 = Dcm_ControlRoeDtcEventType(dataNegRespCode_u8);
                }
#endif
                if((((Dcm_stRoeOpstatus_u8==DCM_INITIAL)&&( Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)) || ( Dcm_stDspRoeDidOpStatusIsPending_b == TRUE)) && (*dataNegRespCode_u8 == 0x0u))
                {
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

                    dataReturnVal_u8 = Dcm_ControlRoeDidEventType(dataNegRespCode_u8);
#endif
                }
                else
                {
                    /* Do nothing */
                }
                if((dataReturnVal_u8==E_OK) &&(*dataNegRespCode_u8 == 0x0u))
                {

                    /* Fill the response buffer */
                    pMsgContext->resData[2] = Dcm_stRoeEventWindowTime_u8;
                    pMsgContext->resData[1] = 0x0u; /* Number of Identified events are zero for start/stop/clear */
                    pMsgContext->resData[0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
                    pMsgContext->resDataLen   = 0x03u;

                }

            }
        }
        /* Event Type is OnDTCStatusChange or OnChangeOfDataIdentifier */
        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_SETUPEVENT)
        {
            /* Copy the event window time to static  variable */
            Dcm_stRoeEventWindowTime_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSWINDOWTIME];


            if((*dataNegRespCode_u8 == 0u) && (Dcm_stRoeEventWindowTime_u8 != 0u)  )
            {

                if (Dcm_stRoeOpstatus_u8 == DCM_INITIAL)
                {

                    if((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_INFINITE) || (Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_CYCLE) ||(Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_AND_FOLLOWING_CYCLE))
                    {
                        if(((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_INFINITE) && (DCM_ROE_VALIDATE_STORAGESTATE_INFINITE == TRUE)) ||\
                                ((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_CYCLE) && (DCM_ROE_VALIDATE_STORAGESTATE_CURRENT == TRUE)) ||\
                                ((Dcm_stRoeEventWindowTime_u8 == DCM_ROE_EVENTWINDOWTIME_CURRENT_AND_FOLLOWING_CYCLE) && (DCM_ROE_VALIDATE_STORAGESTATE_CURRENT_FOLLOWING == TRUE)))

                        {
                            /*Check if the storage state is set for event window time any other than INFINITY & CURRENT_FOLLOWING cycles*/
                            if(( ((Dcm_stRoeEventWindowTime_u8 == 0x02u) || (Dcm_stRoeEventWindowTime_u8 == 0x04u)) && (Dcm_stDspRoeStorageState_b == FALSE))||((Dcm_stRoeEventWindowTime_u8 == 0x03u) &&(Dcm_stDspRoeStorageState_b != FALSE) ) )
                            {
                                /*Set negative response code */
                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            }

                        }
                    }
                    else
                    {
                        /*Set negative response code */
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                }

                if(*dataNegRespCode_u8 == 0u)
                {

                    if(Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID)
                    {
#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
                        /* Call the API to register the events */
                        dataReturnVal_u8 = Dcm_SetUpRoeDidEvent(pMsgContext,dataNegRespCode_u8);

                        if(dataReturnVal_u8 == DCM_E_PENDING)
                        {

                            //do nothing
                        }
                        else
                        {
                            if(dataReturnVal_u8!=E_OK)
                            {
                                /*Check whether any NRC is set already*/
                                if(*dataNegRespCode_u8 ==0x0u)
                                {

                                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                }

                            }
                            /*Reset the service state machine and the service opstatus*/
                            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
                            Dcm_stRoeOpstatus_u8 =DCM_INITIAL;
                        }
#endif
                    }
                    else
                    {
                       if(Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)
                       {
 #if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
                            /* Call the API to register the events */
                            dataReturnVal_u8 = Dcm_SetUpRoeDtcEvent(pMsgContext,dataNegRespCode_u8);

                            if(dataReturnVal_u8 == DCM_E_PENDING)
                            {

                                //do nothing
                            }
                            else
                            {
                                if(dataReturnVal_u8!=E_OK)
                                {
                                    /*Check whether any NRC is set already*/
                                    if(*dataNegRespCode_u8 ==0x0u)
                                    {

                                        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                                    }
                                    /*Reset the service state machine and the service opstatus*/
                                    Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
                                    Dcm_stRoeOpstatus_u8 =DCM_INITIAL;
                                }
                            }

 #endif
                          }
                      }
                }

            }

            else
            {
                /*Set negative response code */
                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            }

        }

        /* Event Type is reportActiveEvents */
        if(Dcm_stDspRoeState_en == DCM_DSP_ROE_REPORTEVENTS)
        {
            dataReturnVal_u8=E_OK;
            Dcm_ReportRoeEvents(pMsgContext);
            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
        }


        /* Check if Negative response code is set */
        if(*dataNegRespCode_u8 != 0x0u)
        {   /* Retrun E_NOT_OK from the service */
            dataReturnVal_u8=E_NOT_OK;
            /* Reset ROE state */
            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
        }
        if(dataReturnVal_u8 == E_OK)
        {
            /* Reset ROE state */
            Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
            Dcm_stRoeOpstatus_u8 = DCM_INITIAL;
        }
    }
    return dataReturnVal_u8;
                                                                                                }



/**
 **************************************************************************************************
 * Dcm_RoeLengthCheck:
 * This function is used to check if the request length received in the request is correct or not.
 *
 * \parameters           pMsgContext    Pointer to message structure
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         None
 *
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_RoeLengthCheck(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(uint16,         AUTOMATIC)   dataReqLen_u16;           /* Local variable to store Response Length */

    /* Copy event type to local variable */
    Dcm_stEventType_u8 = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];

    /* Extract the storage state from the eventType */
    Dcm_stDspRoeStorageState_b = ((Dcm_stEventType_u8 & DCM_DSP_ROE_STORAGEBIT_MSK) != 0x00u);

    /* Clear the storage state bit in the local variable */
    Dcm_stEventType_u8 = (Dcm_stEventType_u8 & ((uint8)(~DCM_DSP_ROE_STORAGEBIT_MSK)));

    /* Set the minimum request length */
    dataReqLen_u16 = 0x02u;

    /* Check if the eventType sent in the request is DCM_ROE_ONCHANGEOFDID */
    if(Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID)
    {
        /* Calculate the actual request length considering event record length and service record length */
        dataReqLen_u16 = (dataReqLen_u16 + DCM_DSP_ROE_DIDRECORDLEN);
    }
    /* Check if the eventType sent in the request is DCM_ROE_ONDTCSTATUSCHANGE */
    else if(Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)
    {
        /* Calculate the actual request length considering event record length and service record length */
        dataReqLen_u16 = (dataReqLen_u16 + DCM_DSP_ROE_DTCRECORDLEN);
    }
    /* Check if the request length for an event type is correct */
#if(DCM_CFG_ROE_WINTIMEINREPEVENTSREQ == DCM_CFG_OFF)
    /* If the event type requested is reportActiveEvents */
    else if(Dcm_stEventType_u8 == DCM_ROE_REPORTACTIVEEVENTS)
    {   /* Set the minimum request length to 1 byte */
        dataReqLen_u16 = DCM_DSP_ROE_MINREQLEN;
    }
#endif
    else
    {
        /* Do nothing */
    }
    /* Check for the request length */
    if(pMsgContext->reqDataLen == dataReqLen_u16)
    {
        /* Call Dcm_CheckRoeEventType() to check if the is Event Type is Start/Stop/Clear event or Setup event or ReportActivatedEvents*/
        Dcm_CheckRoeEventType();
    }
    else
    {   /* The request either fails maxmimum length check or minimum length check, so set Negative response code  */
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
                                                                                                }
/**
 **************************************************************************************************
 * Dcm_CheckRoeEventType:
 * This function is used to check if the event type is to Start/Stop/Clear event or SetUp event
 * or ReportActiveEvents and assign the correct state to state machine .
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_CheckRoeEventType(void)
                                                                                                {
    /* EventType is a control eventType (Start/Stop/Clear event) */
    if((Dcm_stEventType_u8 == DCM_ROE_STOP) || \
            (Dcm_stEventType_u8 == DCM_ROE_START)|| \
            (Dcm_stEventType_u8 == DCM_ROE_CLEAR))
    {
        /* Change the state to control the event */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_CONTROLEVENT;
    }
    /* EventType is OnDTCStatusChange or OnChangeOfDataIdentifier */
    else if((Dcm_stEventType_u8 == DCM_ROE_ONDTCSTATUSCHANGE)|| \
            (Dcm_stEventType_u8 == DCM_ROE_ONCHANGEOFDID))
    {
        /* Change the state to setup an event */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_SETUPEVENT;
    }
    /* EventType is ReportActivatedEvents */
    else if(Dcm_stEventType_u8 == DCM_ROE_REPORTACTIVEEVENTS)
    {
        /* Change the state to read the events activated */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_REPORTEVENTS;
    }
    /* Incorrect Event type */
    else
    {
        /* The code should not reach here - dummy else */
    }
                                                                                                }
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_ControlRoeDidEventType:
 * This function is called when the event type is of Control Event Type (start/stop/clear ROE).
 * \parameters           pMsgContext    Pointer to message structure
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Storing the ROE DID Info is successful
 *                                          DCM_E_PENDING: Need more time to store the ROE DID Info
 *                                          E_NOT_OK: Storing the ROE DID Info is unsuccessful
 *
 **************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDidEventType(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {

    VAR(boolean, AUTOMATIC) dataStoreEventInfo_b;    /*Local variable to chk if event of Did in the loop was either started/stopped/cleared*/
    VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    VAR(uint8,   AUTOMATIC)   dataidxLoop_u8;
    VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8;             /* Local variable to store return from DcmAppl API */
    /*Loop through all the ROE dids and obtain the RoeEventStatus from the application */
    VAR(Dcm_DspRoeEventState_ten,  AUTOMATIC) dataRoeEvtStatus_u8 = DCM_ROE_CLEARED;
    dataReturnVal_u8=E_OK;
    *dataNegRespCode_u8 =0x0u;
    /*Initialise the loop variable based on the operation status*/
    if(Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)
    {
        dataidxLoop_u8 =0x0u;
    }
    else
    {
        dataidxLoop_u8 = Dcm_RoeDidIdx_u8;
    }
    /*Get the current active session */
    dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
    for(;((dataidxLoop_u8<DCM_MAX_DIDROEEVENTS) && (*dataNegRespCode_u8 == 0x0u));dataidxLoop_u8++)
    {
        dataStoreEventInfo_b=FALSE;
        if(Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)
        {
            /*If the requested event is StopResponseEvent,
             *  it is possible to move to stopped state from both cleard and started state*/
            if((Dcm_stEventType_u8 == DCM_ROE_STOP) && (DCM_ROE_STARTED==DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus))
            {
                dataRoeEvtStatus_u8=DCM_ROE_STOPPED;
                /*event of Did in the loop was set to TRUE*/
                dataStoreEventInfo_b=TRUE;
                DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = FALSE;

            }
            /*If the requested event is StartResponseEvent, make sure the current state of event is either started or stopped*/
            else if((Dcm_stEventType_u8 == DCM_ROE_START) && (DCM_ROE_STOPPED==DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus))
            {
                dataRoeEvtStatus_u8=DCM_ROE_STARTED;
                /*event of Did in the loop was started*/
                dataStoreEventInfo_b=TRUE;
                /* If the current session flag is Default session, Set the Session flag to true */
                if(dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
                {
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = TRUE;
                }
                else
                {
                    DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = FALSE;

                }
            }
            /*If the requested event is ClearResponseEvent, since
             *  it is possible to move to clear state from both cleard and started state*/
            else if(Dcm_stEventType_u8 == DCM_ROE_CLEAR)
            {
                dataRoeEvtStatus_u8=DCM_ROE_CLEARED;
                /*event of Did in the loop was cleared*/
                dataStoreEventInfo_b=TRUE;
                DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeSessionIsDefault_b = FALSE;

            }
            else
            {
                /*Do nothing*/
            }
        }
        /*Check if any of the DID event has changed the status*/
        if((dataStoreEventInfo_b != FALSE) ||(Dcm_stDspRoeDidOpStatusIsPending_b != FALSE))
        {
            DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus=dataRoeEvtStatus_u8;
            DcmDspRoeDidStateVariables[dataidxLoop_u8].SourceAddress_u16=Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            /*inform application regarding the status change of the event and store the information in the NVM via application*/
            dataReturnVal_u8 = Dcm_StoreRoeDidEventInfo(dataidxLoop_u8,dataNegRespCode_u8);

            if(dataReturnVal_u8 != E_OK)
            {
                break;
            }
        }


    }

    if((dataReturnVal_u8 == E_NOT_OK) && (*dataNegRespCode_u8 != 0x0u))
    {
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        dataReturnVal_u8 = E_NOT_OK;
    }
    else if(dataReturnVal_u8 == DCM_E_PENDING)
    {
        /*store the index of the current DID event to static varaiable*/
        Dcm_RoeDidIdx_u8 = dataidxLoop_u8;
    }
    else
    {
        //do nothing
    }

    return dataReturnVal_u8;
                                                                                                }

/*
 **************************************************************************************************
 * Dcm_SetUpRoeDidEvent:
 * This function is called to Setup OnChangeOfDataIdentifier Event Type request.
 * \parameters           pMsgContext    Pointer to message structure
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Registering the ROE DID is successful
 *                                          DCM_E_PENDING: Need more time to register the ROE DID
 *                                          E_NOT_OK: Registering the ROE DID is unsuccessful
 *
 **************************************************************************************************
 */

static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDidEvent(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8;             /* Local variable to store return from DcmAppl API */
    VAR(uint16,         AUTOMATIC)   dataRoeDid_u16;           /* Local variable to store Response Length */
    VAR(uint16,   AUTOMATIC)   StoreVar_u16;
    VAR(uint8,   AUTOMATIC)   dataidxLoop_u8;               /* Index for loop counter */
    Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
    dataReturnVal_u8 = E_NOT_OK;

    /*Extract the DID information from the request*/
    StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]);
    StoreVar_u16=StoreVar_u16<<8u;
    StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+1u]);
    dataRoeDid_u16=StoreVar_u16;
if(Dcm_stDspRoeDidOpStatusIsPending_b != TRUE)
{
    /*Check if the DID is enabled for ROE monitoring*/
    for(dataidxLoop_u8=0;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
    {
        if(dataRoeDid_u16 == DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16)
        {
            break;
        }
    }

}
else
{
    dataidxLoop_u8 = Dcm_RoeDidIdx_u8 ;
}
    if(dataidxLoop_u8<DCM_MAX_DIDROEEVENTS)
    {
        /* Call the API to register the events */
        dataReturnVal_u8 = DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8, \
                Dcm_stEventType_u8, \
                Dcm_stDspRoeStorageState_b, \
                Dcm_stRoeEventWindowTime_u8, \
                &pMsgContext->reqData[DCM_ROE_POSEVENTRECORD], \
                &pMsgContext->reqData[DCM_ROE_POSDIDSRVTORESPTORECORD], \
                Dcm_stRoeOpstatus_u8, \
                dataNegRespCode_u8 );
        /* The events are registered */
        if(dataReturnVal_u8 == E_OK)
        {
            *dataNegRespCode_u8 = 0;
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
            Dcm_stRoeOpstatus_u8=DCM_INITIAL;

            /*DID is configured for ROE monitoring*/
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventWindowTime_u8 = Dcm_stRoeEventWindowTime_u8;
            StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD]);
            StoreVar_u16=StoreVar_u16<<8u;
            StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+1u]);
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventRecord_u16=StoreVar_u16;
            StoreVar_u16=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+3u]);
            StoreVar_u16=StoreVar_u16<<8u;
            StoreVar_u16+=(uint16)(pMsgContext->reqData[DCM_ROE_POSEVENTRECORD+4u]);
            DcmDspRoeDidStateVariables[dataidxLoop_u8].stSrvToRespDid_u16=StoreVar_u16;

                /*Move the event status to DCM_ROE_STOPPED*/
                DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus=DCM_ROE_STOPPED;
                DcmDspRoeDidStateVariables[dataidxLoop_u8].stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (*(DcmDspRoeDidEvents[dataidxLoop_u8].ROEDID_fp))(DCM_ROE_STOPPED);
#endif
                DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventId_u8,DCM_ROE_STOPPED);
                /* Fill the response buffer with the event and service record parameters */
                for(dataidxLoop_u8=(uint8)(pMsgContext->reqDataLen-1u); dataidxLoop_u8 > 0u; dataidxLoop_u8--)
                {
                    /* Fill the response buffer */
                    pMsgContext->resData[dataidxLoop_u8+0x1u] = pMsgContext->reqData[dataidxLoop_u8];
                }
                /* Fill the response buffer */
                pMsgContext->resData[0x1] = 0x0u;
                pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
                pMsgContext->resDataLen   = (pMsgContext->reqDataLen+0x1u);
                /* Reset ROE state */
                Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;

        }
        else if(dataReturnVal_u8 == DCM_E_PENDING)
        {
            /* Nothing to do, service will be called again */
            Dcm_stDspRoeDidOpStatusIsPending_b = TRUE;
            *dataNegRespCode_u8 =0x0u;
            Dcm_stRoeOpstatus_u8=DCM_PENDING;
            Dcm_RoeDidIdx_u8 =dataidxLoop_u8;

        }
        else
        {
            Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
            Dcm_stRoeOpstatus_u8=DCM_INITIAL;
            if(*dataNegRespCode_u8 == 0x0u)
            {
                /*Set negative response code */
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }
    }
    else
    {
        /*DID is not configured set NRC 31*/
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
    }
    return dataReturnVal_u8;
                                                                                                }

/**
 **************************************************************************************************
 * Dcm_StoreRoeDidEventInfo:
 * This function is used to provide relevant information to the application.
 *
 * \parameters           dataDoeDidIdx_u8 : Index of the current ROE DID
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Storing the ROE DTC Info is successful
 *                                          DCM_E_PENDING: Need more time to store the ROE DTC Info
 *                                          E_NOT_OK: Storing the ROE DTC Info is unsuccessful
 *
 **************************************************************************************************
 */

static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDidEventInfo(VAR(Std_ReturnType, AUTOMATIC) dataDoeDidIdx_u8,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;

    if(Dcm_stDspRoeDidOpStatusIsPending_b == FALSE)
    {
        /*Inform application regarding the status  change*/
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDidEvents[dataDoeDidIdx_u8].ROEDID_fp))(DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventId_u8,DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus);

        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

    }

    dataRetValue_u8=DcmAppl_DcmStoreRoeDidInfo(    DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventDid_u16,
            DcmDspRoeDidEvents[dataDoeDidIdx_u8].RoeEventId_u8,
            DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].RoeEventStatus,
            DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].SourceAddress_u16,
            DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].stDspRoeStorageState_b,
            Dcm_stRoeOpstatus_u8,
            DcmDspRoeDidStateVariables[dataDoeDidIdx_u8].stDspRoeSessionIsDefault_b,
            dataNegRespCode_u8);


    if(dataRetValue_u8 == E_OK)
    {
        dataRetValue_u8 = E_OK;
        *dataNegRespCode_u8 = 0x0u;
        Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;

    }
    else if(dataRetValue_u8 == DCM_E_PENDING)
    {
        dataRetValue_u8 = DCM_E_PENDING;
        Dcm_stDspRoeDidOpStatusIsPending_b = TRUE;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8 = 0x0u;
        /* Nothing to do. Service will be called again in next cycle */
    }
    else
    {
        dataRetValue_u8 = E_NOT_OK;
        Dcm_stDspRoeDidOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {
            /* Set the negative response code */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
        /* Reset ROE state */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
    }
    return dataRetValue_u8;
                                                                                                }



#endif

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_ControlRoeDtcEventType:
 * This function is called when the event type is of Control Event Type (start/stop/clear ROE)..
 * \parameters           dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Storing the ROE DTC Info is successful
 *                                          DCM_E_PENDING: Need more time to store the ROE DTC Info
 *                                          E_NOT_OK: Storing the ROE DTC Info is unsuccessful
 *
 **************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_ControlRoeDtcEventType(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(boolean, AUTOMATIC) dataDtcStatusflag_b = FALSE;    /*Local variable to chk if event of Did in the loop was either started/stopped/cleared*/
    VAR(Dcm_SesCtrlType,AUTOMATIC) dataCurrentSession_u8;
    VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8 = E_NOT_OK;             /* Local variable to store return from DcmAppl API */

    if ( Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)
    {
        /*Get the current active session */
        dataCurrentSession_u8 = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.idxActiveSession_u8];
        /*Get the Tester Source Address */
        DcmDspRoeDtcStateVariable.SourceAddress_u16=Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
        s_DcmOldRoeDtcState = DcmDspRoeDtcStateVariable.RoeEventStatus;
        /*Make sure the stop request received for a roe event is already setup or started*/
        if((DCM_ROE_STOP==Dcm_stEventType_u8) && (DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus))
        {
            /*Update the Roe event varaibles*/
            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b=FALSE;
        }
        /*Make sure the start request received for a roe event is already setup or stopped*/
        else if((DCM_ROE_START==Dcm_stEventType_u8) && (DCM_ROE_STOPPED==DcmDspRoeDtcStateVariable.RoeEventStatus))
        {
            /*Update the Roe event varaibles*/
            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STARTED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b =FALSE;

            /* If the current session flag is Default session, Set the Session flag to true */
            if(dataCurrentSession_u8 == Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
            {
                DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b =TRUE;
            }
        }
        else if(DCM_ROE_CLEAR == Dcm_stEventType_u8)
        {
            /*Update the Roe event varaibles*/
            DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_CLEARED;
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
            dataDtcStatusflag_b=TRUE;
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b=FALSE;

        }
        else
        {
            /*Do nothing flag status already updated*/
        }
    }
    /*Enter only if the Dtc which was either started/stopped/cleared*/
    if((dataDtcStatusflag_b != FALSE) ||  ( Dcm_stDspRoeDtcOpStatusIsPending_b != FALSE))
    {

        DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;

        dataReturnVal_u8 =Dcm_StoreRoeDtcEventInfo(dataNegRespCode_u8);
    }


    return dataReturnVal_u8;
                                                                                                }

/*
 **************************************************************************************************
 * Dcm_SetUpRoeDtcEvent:
 * This function is called to Setup OnDTCStatusChange Event Type request..
 * \parameters           pMsgContext    Pointer to message structure
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Registering the ROE Dtc is successful
 *                                          DCM_E_PENDING: Need more time to register the ROE Dtc
 *                                          E_NOT_OK: Registering the ROE Dtc is unsuccessful
 *
 **************************************************************************************************
 */

static FUNC(Std_ReturnType,DCM_CODE) Dcm_SetUpRoeDtcEvent(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(Std_ReturnType, AUTOMATIC)   dataReturnVal_u8;             /* Local variable to store return from DcmAppl API */
    VAR(uint8,   AUTOMATIC)   dataidxLoop_u8;               /* Index for loop counter */

    dataReturnVal_u8 = E_NOT_OK;

    /* Call the API to register the events */
    dataReturnVal_u8 = DcmAppl_DcmSetUpRoeEvent(DcmDspRoeDtcEvent.RoeEventId_u8, \
            Dcm_stEventType_u8, \
            Dcm_stDspRoeStorageState_b, \
            Dcm_stRoeEventWindowTime_u8, \
            &pMsgContext->reqData[DCM_ROE_POSEVENTRECORD], \
            &pMsgContext->reqData[DCM_ROE_POSDTCSRVTORESPTORECORD], \
            Dcm_stRoeOpstatus_u8, \
            dataNegRespCode_u8 );
    /* The events are registered */
    if(dataReturnVal_u8 == E_OK)
    {
        *dataNegRespCode_u8 = 0;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        /*Extract the DTC status mask from the request*/

        DcmDspRoeDtcStateVariable.stRoeEventWindowTime_u8 = Dcm_stRoeEventWindowTime_u8;
        DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8=pMsgContext->reqData[DCM_ROE_POSEVENTRECORD];
        DcmDspRoeDtcStateVariable.RoeEventStatus=DCM_ROE_STOPPED;
        DcmDspRoeDtcStateVariable.stDspRoeStorageState_b=Dcm_stDspRoeStorageState_b;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DCM_ROE_STOPPED);
#endif
        DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DCM_ROE_STOPPED);
        /* Fill the response buffer with the event and service record parameters */
        for(dataidxLoop_u8=(uint8)(pMsgContext->reqDataLen-1u); dataidxLoop_u8 > 0u; dataidxLoop_u8--)
        {
            /* Fill the response buffer */
            pMsgContext->resData[dataidxLoop_u8+0x1u] = pMsgContext->reqData[dataidxLoop_u8];
        }
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        /* Fill the response buffer */
        pMsgContext->resData[0x1] = 0x0u;
        pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
        pMsgContext->resDataLen   = (pMsgContext->reqDataLen+0x1u);
        /* Reset ROE state */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
    }
    else if(dataReturnVal_u8 == DCM_E_PENDING)
    {
        /* Nothing to do, service will be called again */
        *dataNegRespCode_u8 =0x0u;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        Dcm_stDspRoeDtcOpStatusIsPending_b = TRUE;
    }
    else
    {
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {
            /*Set negative response code */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
    }
    return dataReturnVal_u8;


                                                                                                }




/**
 **************************************************************************************************
 * Dcm_StoreRoeDtcEventInfo:
 * This function is used to provide relevant information to the application
 *
 * \parameters           dataReturnVal_u8 : The return type of DcmAppl_DcmStoreRoeDidInfo() is E_OK or DCM_E_PENDING or E_NOT_OK.
 *                       dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value         Std_ReturnType :   E_OK: Storing the ROE DTC Info is successful
 *                                          DCM_E_PENDING: Need more time to store the ROE DTC Info
 *                                          E_NOT_OK: Storing the ROE DTC Info is unsuccessful
 *
 **************************************************************************************************
 */

static FUNC(Std_ReturnType,DCM_CODE) Dcm_StoreRoeDtcEventInfo(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                                                                                                {
    VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;


    /*Request the application to store the roe event information in the Nvm*/
    dataRetValue_u8=DcmAppl_DcmStoreRoeDTCInfo (DcmDspRoeDtcEvent.RoeEventId_u8,
            DcmDspRoeDtcStateVariable.RoeEventStatus,
            DcmDspRoeDtcStateVariable.SourceAddress_u16,
            DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8,
            DcmDspRoeDtcStateVariable.stDspRoeStorageState_b,
            Dcm_stRoeOpstatus_u8,
            DcmDspRoeDtcStateVariable.stDspRoeSessionIsDefault_b,
            dataNegRespCode_u8);


    if(dataRetValue_u8 == E_OK)
    {
        dataRetValue_u8 = E_OK;

        if(Dcm_stDspRoeDtcOpStatusIsPending_b == FALSE)
        {
            /*Inform application regarding the status change of the ROE event*/
    #if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            (*(DcmDspRoeDtcEvent.ROEDTC_fp))(DcmDspRoeDtcStateVariable.RoeEventStatus);
    #endif
            DcmAppl_Switch_DcmResponseOnEvent(DcmDspRoeDtcEvent.RoeEventId_u8,DcmDspRoeDtcStateVariable.RoeEventStatus);

            Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        }


        *dataNegRespCode_u8 = 0x0u;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        /*Reset the service state machine and the service opstatus*/


    }
    else if(dataRetValue_u8 == DCM_E_PENDING)
    {
        dataRetValue_u8 = DCM_E_PENDING;
        Dcm_stDspRoeDtcOpStatusIsPending_b = TRUE;
        Dcm_stRoeOpstatus_u8=DCM_PENDING;
        *dataNegRespCode_u8 = 0x0u;
        /* Nothing to do. Service will be called again in next cycle */
    }
    else
    {
        dataRetValue_u8 = E_NOT_OK;

        DcmDspRoeDtcStateVariable.RoeEventStatus = s_DcmOldRoeDtcState;
        Dcm_stDspRoeDtcOpStatusIsPending_b = FALSE;
        Dcm_stRoeOpstatus_u8=DCM_INITIAL;
        if(*dataNegRespCode_u8 == 0)
        {
            /* Set the negative response code */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
        /* Reset ROE state */
        Dcm_stDspRoeState_en = DCM_DSP_ROE_INIT;
    }
    return dataRetValue_u8;
                                                                                                }

#endif
/**
 **************************************************************************************************
 * Dcm_ReportRoeEvents:
 * This function is called when Event Type is reportActiveEvents.
 * \parameters           pMsgContext    Pointer to message structure
 *
 * \return value         none
 *
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_ReportRoeEvents(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
                                                                                                {

    VAR(uint8,          AUTOMATIC) idxReportEvents_u8;
    VAR(uint8,          AUTOMATIC) idxRoeResponse_u8;
    VAR(uint8,          AUTOMATIC) dataidxLoop_u8;

    VAR(uint16,         AUTOMATIC) dataID_u16;

    idxReportEvents_u8 =0u;
    /* Initialise the response length to zero */

    /* Fill the response buffer */
    pMsgContext->resData[0x0] = pMsgContext->reqData[DCM_DSP_ROE_POSEVENT];
    idxRoeResponse_u8=0x2u;


#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
        /*Check if the DID is enabled for ROE monitoring*/
        for(dataidxLoop_u8=0;(dataidxLoop_u8<DCM_MAX_DIDROEEVENTS);dataidxLoop_u8++)
        {
            if(DcmDspRoeDidStateVariables[dataidxLoop_u8].RoeEventStatus == DCM_ROE_STARTED)
            {
                dataID_u16 = DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventRecord_u16;
                /*Update the event type */
                pMsgContext->resData[idxRoeResponse_u8] = DCM_ROE_ONCHANGEOFDID;
				idxRoeResponse_u8++;
                /*Update the event windowtime*/
                pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDidStateVariables[dataidxLoop_u8].stRoeEventWindowTime_u8;
                idxRoeResponse_u8++;
                /*Update the event type record DID  */
                pMsgContext->resData[idxRoeResponse_u8] = (uint8)(dataID_u16>>8u);/*Copy the MSB*/
                idxRoeResponse_u8++;
                pMsgContext->resData[idxRoeResponse_u8] =(uint8) dataID_u16;/*Copy the LSB*/
                idxRoeResponse_u8++;
                pMsgContext->resData[idxRoeResponse_u8] = 0x22u;/*Adding service ID*/
                idxRoeResponse_u8++;
                pMsgContext->resData[idxRoeResponse_u8] = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16>>8u);
				idxRoeResponse_u8++;
                pMsgContext->resData[idxRoeResponse_u8] = (uint8)(DcmDspRoeDidEvents[dataidxLoop_u8].RoeEventDid_u16);
				idxRoeResponse_u8++;
                idxReportEvents_u8++;/*Increment the counter for active events*/
            }

        }
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(DcmDspRoeDtcStateVariable.RoeEventStatus == DCM_ROE_STARTED)
        {
            pMsgContext->resData[idxRoeResponse_u8] = DCM_ROE_ONDTCSTATUSCHANGE;
            idxRoeResponse_u8=idxRoeResponse_u8+1;
            pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDtcStateVariable.stRoeEventWindowTime_u8;
            idxRoeResponse_u8=idxRoeResponse_u8+1;
            pMsgContext->resData[idxRoeResponse_u8] = DcmDspRoeDtcStateVariable.testerReqDTCStatusMask_u8;
            idxRoeResponse_u8=idxRoeResponse_u8+1;
            pMsgContext->resData[idxRoeResponse_u8] = 0x19u;
            idxRoeResponse_u8=idxRoeResponse_u8+1;
            pMsgContext->resData[idxRoeResponse_u8] = 0x0Eu;
            idxRoeResponse_u8=idxRoeResponse_u8+1;
            idxReportEvents_u8++;/*Increment the counter for active events*/
        }
#endif
        pMsgContext->resData[0x1] = idxReportEvents_u8; /*  Update the number of activated events */
        pMsgContext->resDataLen = idxRoeResponse_u8;/*Update the response length*/
                                                                                                }


/**
 **************************************************************************************************
 * Dcm_RoeCtrlConditionAndSequenceCheck:
 * This function is used to check if the control request leads to NRC 0x22 or 0x24 when validated against the existing states of the
 * roe events.
 *
 * \parameters           dataNegRespCode_u8 : Parameter to update the NRC value
 * \return value
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE)Dcm_RoeCtrlConditionAndSequenceCheck(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
                         {

    VAR(uint8,   AUTOMATIC)   dataidxLoop_u8;/*loop varaible*/


    if(Dcm_stEventType_u8 == DCM_ROE_START)
    {
        /*multiple client handling,atleast one of the event is started already and if the new start request came from a different protocol then the request shall be rejected with NRC 0x22*/
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

        if((DCM_ROE_STARTED==DcmDspRoeDtcStateVariable.RoeEventStatus)&&(DcmDspRoeDtcStateVariable.SourceAddress_u16!=Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16))
        {
            *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;

        }
#endif

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
        for(dataidxLoop_u8=0x0u;((dataidxLoop_u8<DCM_MAX_DIDROEEVENTS) &&  (*dataNegRespCode_u8 == 0x0u));dataidxLoop_u8++)
        {
            if((DCM_ROE_STARTED==DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)&& (DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].SourceAddress_u16!=Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16))
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                break;
            }

        }
#endif

    }
    /*checking request sequence error ;if start or stop is requested and if all the events are in the cleared state NRC ox24 needs to be sent*/
    if((Dcm_stEventType_u8 == DCM_ROE_START) ||(Dcm_stEventType_u8 == DCM_ROE_STOP))
    {
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)
        if(DcmDspRoeDtcStateVariable.RoeEventStatus==DCM_ROE_CLEARED)
#endif
        {
#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

            for(dataidxLoop_u8=0x0u;dataidxLoop_u8<DCM_MAX_DIDROEEVENTS;dataidxLoop_u8++)
            {
                if(DCM_ROE_CLEARED!=DcmDspRoeDidStateVariables[Dcm_RoeDidIdx_u8].RoeEventStatus)
                {
                    break;
                }
            }
            if(dataidxLoop_u8==DCM_MAX_DIDROEEVENTS)
#endif
            {

                *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
            }

        }

    }

                         }


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif




