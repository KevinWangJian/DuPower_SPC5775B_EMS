

#ifndef DCMDSPUDS_ROE_PRIV_H
#define DCMDSPUDS_ROE_PRIV_H


/**
 ***************************************************************************************************
            Response On Event (ROE) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if (DCM_CFG_ROE_WINTIMEINREPEVENTSREQ != DCM_CFG_OFF)
#define DCM_DSP_ROE_MINREQLEN        0x2u        /* Minimum request length including event window time */
#else
#define DCM_DSP_ROE_MINREQLEN        0x1u        /* Minimum request length excluding event window time */
#endif

#define DCM_DSP_ROE_STORAGEBIT_MSK   0x40u      /* Bit mask to obtain the storage state bit from event type */
#define DCM_DSP_ROE_POSEVENT         0x0u        /* Position of the eventType in request message */
#define DCM_DSP_ROE_POSWINDOWTIME    0x1u        /* Position of the event window time in the request message */
#define DCM_ROE_POSDIDEVENTRECORD       0x2u        /* Position of the event record in the ROE DID setup  request message */
#define DCM_ROE_POSDIDSRVTORESPTORECORD       0x4u        /* Position of DID event the service to respond to  record in the request message */
#define DCM_ROE_POSDTCEVENTRECORD       0x2u        /* Position of the event record in the ROE DTC setup  request message */
#define DCM_ROE_POSDTCSRVTORESPTORECORD       0x3u        /* Position of DID event the service to respond to  record in the request message */
#define DCM_ROE_POSEVENTRECORD  0x02u
#define DCM_DSP_ROE_DIDRECORDLEN     0X05u       /* Size of Event and Service Record Length in case the Event Type is OnChangeOfDataIdentifier*/
#define DCM_DSP_ROE_DTCRECORDLEN     0X03u       /* Size of Event and Service Record Length in case the Event Type is OnDTCStatusChange*/
#define DCM_ROE_INFINITETIME         0x02u       /* Macro for infinite event window time */

/* Definitions of states of DSC service */
typedef enum
{
    DCM_DSP_ROE_INIT,              /* Initialisation state           */
    DCM_DSP_ROE_CONTROLEVENT,      /* ROE state to clear events      */
    DCM_DSP_ROE_SETUPEVENT,        /* ROE state to setup events      */
    DCM_DSP_ROE_REPORTEVENTS       /* ROE state to report events     */
}Dcm_DspRoeState_ten;

#endif  /* DCM_CFG_DSP_RESPONSEONEVENT_ENABLED */

#endif   /* _DCMDSPUDS_ROE_PRIV_H */
