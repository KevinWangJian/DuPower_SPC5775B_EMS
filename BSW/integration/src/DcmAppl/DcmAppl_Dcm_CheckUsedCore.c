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
#include "rba_BswSrv.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF))
/**
 * @ingroup DCM_TPL
 * DcmAppl_Dcm_CheckUsedCore:-\n
 * The API returns the current coreID which is obtained by the API rba_BswSrv_GetPhysCore().The API rba_BswSrv_GetPhysCore() supports only IFX and POWERPC architecture .\n
 * In case the project is using another microcontroller, they shall modify the API DcmAppl_Dcm_CheckUsedCore() accordingly.Projects can use GetCoreID() from Os.h instead of rba_BswSrv_GetPhysCore().\n
 * The function GetCoreID() is available on all Autosar MultiCore systems but not on single core systems. So, it has to be encapsulated.
 *
 *
 * @param[in]  None \n
 * @param[out] None \n
 * @retval     Current core Id \n
 *
 *
 */
FUNC(uint32, DCM_APPL_CODE) DcmAppl_Dcm_CheckUsedCore(void)
{
   VAR(uint32,AUTOMATIC) Core_u32;
#ifdef CPU_SINGLECORE

   Core_u32=0;
  /*TESTCODE-START
      Core_u32 = DcmTest_Dcm_GetUsedCoreID();
  TESTCODE-END*/
   return( Core_u32);
#else
  Core_u32 = rba_BswSrv_GetPhysCore();
  return(Core_u32);
#endif
}

#endif

