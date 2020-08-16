/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef FIM_CFG_SCHM_H
#define FIM_CFG_SCHM_H

#include "SchM_Default.h"

LOCAL_INLINE FUNC(void,FIM_CODE)  SchM_Enter_FiM_Monitor_NoNest(void)
{
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void,FIM_CODE)  SchM_Exit_FiM_Monitor_NoNest(void)
{
    SCHM_EXIT_DEFAULT();
}

LOCAL_INLINE FUNC(void,FIM_CODE)  SchM_Enter_FiM_Status_NoNest(void)
{
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void,FIM_CODE)  SchM_Exit_FiM_Status_NoNest(void)
{
    SCHM_EXIT_DEFAULT();
}

#endif /* include protection */

