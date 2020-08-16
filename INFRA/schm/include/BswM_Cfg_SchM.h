/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef BSWM_CFG_SCHM_H
#define BSWM_CFG_SCHM_H

// ---- Includes --------------------------------------------------------------
#include "SchM_Default.h"

// The integrator shall implement the particular services SchM_Enter and SchM_Exit.


#define SchM_Enter_BswM(BSWM_RESOURCE)  SCHM_ENTER_DEFAULT()
#define SchM_Exit_BswM(BSWM_RESOURCE)   SCHM_EXIT_DEFAULT()

#endif /* BSWM_CFG_SCHM_H */

/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
