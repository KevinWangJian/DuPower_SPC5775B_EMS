/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */


		
#ifndef EA_CFG_SCHM_H
#define EA_CFG_SCHM_H

/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR EA
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "rba_BswSrv.h"
#include "SchM_Default.h"

/*
 ***************************************************************************************************
 * Type definition and enums
 ***************************************************************************************************
 */

/* The integrator shall implement the particular services SchM_Enter and SchM_Exit.*/

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Ea_Order(void);
LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Ea_Order(void);


LOCAL_INLINE FUNC(void, EA_CODE) SchM_Enter_Ea_Order(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
	SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, EA_CODE) SchM_Exit_Ea_Order(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
	SCHM_EXIT_DEFAULT();
}


#endif /* EA_CFG_SCHM_H */

/*<BASDKey>
 ***********************************************************************************************************************
 * $History___:$
 ***********************************************************************************************************************
</BASDKey>*/

