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



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_ConfirmationRespPend :-\n
 *  This API confirms the successful transmission of waitpend response.
 *
 *  @param[in]       status :  A Status indication about confirmation\n
 *  @param[out]      None
 *  @retval          None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_ConfirmationRespPend(
                                                    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                )
{
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_ConfirmationRespPend(status);
#else
(void)status;
#endif
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
