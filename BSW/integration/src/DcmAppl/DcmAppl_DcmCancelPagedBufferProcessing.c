/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmCore_DslDsd_Inf.h"



#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 *  DcmAppl_DcmCancelPagedBufferProcessing :-\n
 *  This API indicates the service to stop paged buffer transmission.This API has to call ini function of the service.
 *  @param[in]       idContext : SID of the service which is running.\n
 *  @param[out]      None
 *  @retval          None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmCancelPagedBufferProcessing(VAR(Dcm_IdContextType,AUTOMATIC) idContext)
{

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    /* If RDBI service is active */
    if(idContext == DCM_DSP_SID_READDATABYIDENTIFIER)
    {
        /* Call the RDBI Ini function */
        Dcm_Dsp_RdbiIni();
    }

#endif
#if ((DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    /* If RDTC service is active */
    if(idContext == DCM_DSP_SID_READDTCINFORMATION)
    {
        /* Call the RDTC Ini function */
        Dcm_Dsp_ReadDTCInfo_Ini();
    }
#else
    (void)(idContext);
#endif
#else
    (void)(idContext);
#endif
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

