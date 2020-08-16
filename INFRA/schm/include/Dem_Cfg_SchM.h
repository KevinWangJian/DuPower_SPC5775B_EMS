/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




#ifndef DEM_CFG_SCHM_H
#define DEM_CFG_SCHM_H

#include "SchM_Default.h"

/**
 * \file
 * \ingroup DEM_PRJ_TPL
 * \brief Exclusive area handling for Dem
 *
 * Defines macros to lock critical regions in Dem. They can be adapted to avoid the overhead of locking in deployments
 * where that is not necessary (e.g. if Dem and Dcm are running in the same task, the lock between them can be avoided).
 */


/* This lock is always required, as the monitorings are usually runing in different tasks as DEM and
 * therefore may interrupt the processing of DEM at any time.
 */
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Enter_Dem_Monitoring(void)
{
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Exit_Dem_Monitoring(void)
{
    SCHM_EXIT_DEFAULT();
}

/* This lock is required if DEM and NVM may interrupt each other, e.g. if both components
 * are running in different tasks on a single CPU
 */
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Enter_Dem_Nvm(void)
{
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Exit_Dem_Nvm(void)
{
    SCHM_EXIT_DEFAULT();
}

/* This lock is required if DEM and DCM may interrupt each other, e.g. if both components
 * are running in different tasks on a single CPU
 */
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Enter_Dem_Dcm(void)
{
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void,DEM_CODE) SchM_Exit_Dem_Dcm(void)
{
    SCHM_EXIT_DEFAULT();
}


#endif


