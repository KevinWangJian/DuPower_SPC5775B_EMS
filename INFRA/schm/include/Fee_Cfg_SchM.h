/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
//#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif /* NOT_READY_FOR_TESTING_OR_DEPLOYMENT */




#ifndef FEE_CFG_SCHM_H
#define FEE_CFG_SCHM_H

/**
 **********************************************************************************************************************
 * \file   SchM_Fee.h
 * \brief  Schedule manager interface to be used by the Fee driver
 * \par    Module Description
 * \Schedule manager for FEE description
 **********************************************************************************************************************
 */


/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
/* Include if available */
//#include "SchM_Default.h


/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */
/*
 * The implementation of this macro has to ensure that no other
 * Fee component code is executed while the code between
 * SchM_Enter_Fee_Order() and SchM_Exit_Fee_Order() is executed.
 */
#define SchM_Enter_Fee_Order()    (void)0
#define SchM_Exit_Fee_Order()     (void)0

/* FEE_CFG_SCHM_H */
#endif

/*<BASDKey>
 ***********************************************************************************************************************
 * $History___:$
 ***********************************************************************************************************************
</BASDKey>*/
