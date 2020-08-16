

#ifndef DCMDSPUDS_ROE_PUB_H
#define DCMDSPUDS_ROE_PUB_H


/**
 ***************************************************************************************************
            Response On Event (ROE) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * ROE structure global configuration.\n
 * Member elements/n
 * uint8  EventType_u8;
 * uint8  EventRecordLen_u8;
 * uint8  ServiceRecordLen_u8;
*/
typedef struct
{
    uint8  EventType_u8;
    uint8  EventRecordLen_u8;
    uint8  ServiceRecordLen_u8;
} DcmDspRoeConf_t;
#define DCM_START_SEC_CONST_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(DcmDspRoeConf_t, DCM_CONST) DcmDspRoeEvents[DCM_ROE_MAX_EVENTS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* End of DCM_CFG_DSP_RESPONSEONEVENT_ENABLED */

#endif /* _DCMDSPUDS_ROE_PUB_H  */
