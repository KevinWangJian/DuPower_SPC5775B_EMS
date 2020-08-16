

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 **************************************************************************************************
 * Dcm_RestartP3timer : Function called by Kline TP to restart P3 timer after getting the first
 *                          byte of request
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void, DCM_CODE) Dcm_RestartP3timer(void)
{
    /* Restart P3 timer */
    Dcm_StartS3MaxMonitoring();
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

