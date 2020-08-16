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



#ifndef ETHTRCV_CFG_SCHM_H
#define ETHTRCV_CFG_SCHM_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "SchM_Default.h"
#if (ETHTRCV_ECUC_RB_RTE_IN_USE == STD_ON)
#include "SchM_EthTrcv.h"
#endif


LOCAL_INLINE FUNC(void, ETHTRCV_CODE) EthTrcv_SchM_Enter(void);
LOCAL_INLINE FUNC(void, ETHTRCV_CODE) EthTrcv_Schm_Exit(void);
LOCAL_INLINE FUNC(void, ETHTRCV_CODE) SchM_Enter_EthTrcv_RESOURCE(void);
LOCAL_INLINE FUNC(void, ETHTRCV_CODE) SchM_Exit_EthTrcv_RESOURCE(void);

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_EthTrcv_MiiCommunication(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_EthTrcv_MiiCommunication(void);

LOCAL_INLINE FUNC(void, ETHTRCV_CODE)  EthTrcv_SchM_Enter(void)
{
    /*The integrator should place the code here which Disables/Locks the interrupt*/
}

LOCAL_INLINE FUNC(void, ETHTRCV_CODE)  EthTrcv_Schm_Exit(void)
{
    /*The integrator should place the code here which Enables/Unlocks the interrupt*/
}

LOCAL_INLINE FUNC(void, ETHTRCV_CODE)  SchM_Enter_EthTrcv_RESOURCE(void)
{
    /*The integrator should place the code here which Disables/Locks the interrupt*/
}

LOCAL_INLINE FUNC(void, ETHTRCV_CODE)  SchM_Exit_EthTrcv_RESOURCE(void)
{
    /*The integrator should place the code here which Enables/Unlocks the interrupt*/
}


LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_EthTrcv_MiiCommunication(void)
{
  /* integrator shall place his code for locking/disabling interrupts */
  /* hint: In general it is not allowed to start multiple Mii Communication at the same time:
   *  Mii communication is started in EthTrcv_TransceiverInit and EthTrcv_MainFunction
   *  To avoid multiple starting of MII communication there is a global variable EthTrcv_Prv_MiiCommunicationFlag_b in
   *  EthTrcv component
   *  The access to this variable (EthTrcv_Prv_MiiCommunicationFlag_b) is under protection.
   */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_EthTrcv_MiiCommunication(void)
{
  /* integrator shall place his code for unlocking/enabling interrupts */
  /* for hints see SchM_Enter_EthTrcv_MiiCommunication */
}


#endif /* ETHTRCV_CFG_SCHM_H */


/*<BASDKey>
 **********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/
