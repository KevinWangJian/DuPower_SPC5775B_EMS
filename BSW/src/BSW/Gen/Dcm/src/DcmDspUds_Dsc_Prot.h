

#ifndef DCMDSPUDS_DSC_PROT_H
#define DCMDSPUDS_DSC_PROT_H

#include "Dcm.h"

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
/* Definitions of states of DSC service */
typedef enum
{
    DCM_DSP_DSC_INIT = 1,                         /* DSC Initialization state                       */
    DCM_DSP_DSC_WAIT,                             /* DSC Service waiting for call back              */
    DCM_DSP_DSC_CHECK_PERMISSION,                 /* Get Session change permissions                 */
    DCM_DSP_DSC_SEND_RESP,                        /* Send Positive response state                   */
    DCM_DSP_DSC_ERROR                             /* Send negative response state                   */
}Dcm_DscStateType_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DscStateType_ten,  DCM_VAR) Dcm_stDsc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,             DCM_VAR) Dcm_ctDiaSess_u8;
extern VAR(uint8,             DCM_VAR) Dcm_ReqSess_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


#endif /* #ifndef _DCMDSPUDS_DSC_PROT_H */

