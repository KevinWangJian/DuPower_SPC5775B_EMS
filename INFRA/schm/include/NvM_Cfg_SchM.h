/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef NVM_CFG_SCHM_H
#define NVM_CFG_SCHM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "rba_BswSrv.h"
#include "SchM_Default.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

/*
 * Exclusive area "NvM_Main":
 * - This exclusive area protects all accesses to shared ressources within the NvM module, in particular between NvM's
 *   public service APIs and the NvM_MainFunction.
 * - On multi-core machines, a lock functionality is required which works across all cores which could invoke NvM's
 *   public service APIs or schedules the NvM_MainFunction. On single core machines, a global interrupt lock or
 *   (possibly NvM-specific) semaphore is sufficient.
 * - In NvM, all SchM_Enter/Exit_NvM_Main calls are in the same C block, so block enforcing lock macros can be used.
 */
/* The integrator shall implement the particular services SchM_Enter and SchM_Exit.*/

LOCAL_INLINE FUNC(void, NvM_CODE) SchM_Enter_NvM_Main(void);
LOCAL_INLINE FUNC(void, NvM_CODE) SchM_Exit_NvM_Main(void);

LOCAL_INLINE FUNC(void, NvM_CODE) SchM_Enter_NvM_Main(void)
{
	/*The integrator shall place his code here which would disable/lock the interrupt*/
	SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, NvM_CODE) SchM_Exit_NvM_Main(void)
{
	/*The integrator shall place his code here which would disable/lock the interrupt*/
	SCHM_EXIT_DEFAULT();
}

#endif /* NVM_CFG_SCHM_H */

