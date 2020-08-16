/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef IPDUM_CFG_SCHM_H
#define IPDUM_CFG_SCHM_H

#include "SchM.h"
#include "SchM_Default.h"

/* If the RTE code generation is Involved please include the below file */
#if defined(IPDUM_ECUC_RB_RTE_IN_USE) && (IPDUM_ECUC_RB_RTE_IN_USE != STD_OFF)
#include "SchM_IpduM.h"
#endif

#include "rba_BswSrv.h"


LOCAL_INLINE FUNC(void, IPDUM_CODE) SchM_Enter_IpduM_LockTxContainerBuffer(void);
LOCAL_INLINE FUNC(void, IPDUM_CODE) SchM_Exit_IpduM_LockTxContainerBuffer(void);

/* The integrator shall implement the particular services SchM_Enter and SchM_Exit.*/

/* Since there is currently only one resource used (IPDUM_RESOURCE), there is no need to consider the resource name*/

LOCAL_INLINE FUNC(void, IPDUM_CODE) SchM_Enter_IpduM_LockTxContainerBuffer(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, IPDUM_CODE) SchM_Exit_IpduM_LockTxContainerBuffer(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_EXIT_DEFAULT();
}

#endif /* IPDUM_CFG_SCHM_H */

/* -------- END OF FILE -------------------------------------------------------*/


