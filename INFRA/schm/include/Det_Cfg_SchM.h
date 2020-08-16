/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef DET_CFG_SCHM_H
#define DET_CFG_SCHM_H

#include "SchM_Default.h"

/* This lock is always required, as the component using the DET are usually runing in different tasks as DET and
 * therefore may interrupt the processing of DET at any time.
 */
#define SchM_Enter_Det_Monitoring()      SCHM_ENTER_DEFAULT()
#define SchM_Exit_Det_Monitoring()		 SCHM_EXIT_DEFAULT()

#endif /* include protection */
