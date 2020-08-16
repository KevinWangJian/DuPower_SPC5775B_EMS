/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




#ifndef COMM_CFG_SCHM_H
#define COMM_CFG_SCHM_H

#include "SchM_Default.h"

#if ( COMM_ECUC_RB_RTE_IN_USE == STD_ON )
/* If the RTE code generation is Involved please include the below file */
#include "SchM_ComM.h"
#endif /* #if ( COMM_ECUC_RB_RTE_IN_USE == STD_ON ) */

/* The integrator shall implement the particular services SchM_Enter and SchM_Exit */

/* Since there is currently only one resource used, there is no need to consider the resource name */

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_UserNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_UserNoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ChannelNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ChannelNoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_EIRANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_EIRANoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ERANoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ERANoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCNoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCWakeUpNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCWakeUpNoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_LimitationNoNest(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_LimitationNoNest(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_Channel(void);
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_Channel(void);

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCNoNest(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect channel parameter,if multiple PNC's are mapped to at least one channel.
     The following resource is protected by this lock:
     ComM_PncRamStructType[].PncRequestCtr_u8

       Enable this lock, if
     1. A channel is associated with multiple PNC's and
     2. PNC main functions can run concurrently  */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCNoNest(void)
{
    SCHM_EXIT_DEFAULT();

}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_EIRANoNest(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect PNC parameter,if a PNC has multiple EIRA signals configured.
     The following resource is protected by this lock:
     ComM_PncRamStructType[].EIRACnt_u8

      Enable this lock only if
     1. Multiple bus types are configured in ComM and
     2. All the used <Bus>Nm's main functions can run concurrently */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_EIRANoNest(void)
{
    SCHM_EXIT_DEFAULT();

}

/* EIRA signal is per bus type and ERA signal is per channel.
   Currently, all the CUBAS Nm's don't support multiple <Bus>Nm main functions which can
   be scheduled independently. Hence the scope of ERANoNest lock is limited to <Bus>Nm's main functions
   running concurrently. If any of the <Bus>Nm's support main functions which can scheduled independently,
   then the scope of this lock has to be changed to multiple channels running concurrently */

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ERANoNest(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect PNC parameters, if a PNC has multiple ERA signals configured.
     The following resource is protected by this lock:
     ComM_PncRamStructType[].ERACnt_u8

      Enable this lock only if
     1. Multiple bus types are configured in ComM and
     2. All the used <Bus>Nm's main functions can run concurrently  */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ERANoNest(void)
{
    SCHM_EXIT_DEFAULT();

}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_PNCWakeUpNoNest(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect PNC related parameters if COMM_SYNCHRONOUS_WAKE_UP == STD_ON.
     This lock protects the following resources:
     ComM_PncRamStructType[].WakeUpStatus_b

     In addition, it also ensures that ComM_PncRamStructType[].WakeUpStatus_b and
     ComM_PncRamStructType[].PncState_e consistently.

      Enable this lock only if
     1. COMM_SYNCHRONOUS_WAKE_UP == STD_ON or
     2. any of PNC main function, ComM_EcuM_WakeUpIndication, ComM_EcuM_PNCWakeUpIndication can run concurrently */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_PNCWakeUpNoNest(void)
{
    SCHM_EXIT_DEFAULT();

}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_UserNoNest(void)
{
    SCHM_ENTER_DEFAULT();
   /* This lock is to protect channel parameter, if there are multiple users assigned to a channel or
      multiple users assigned to a PNC.
      This lock protects the following resources:
      ComM_ChannelVarType[].UserRequestCtr_u8 and
      ComM_PncRamStructType[].UserRequestCnt_u8

    Enable this lock only if
    1. multiple users are configured in ComM and User requests can run concurrently or
    2. If ComM channel Main function and ComM_RequestComMode() api can interrupt each other */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_UserNoNest(void)
{
    SCHM_EXIT_DEFAULT();

}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_ChannelNoNest(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect the channel related parameters.
     This lock protects the following resources:
     ComM_ChannelVarType[].NmBusSleepIndicationStatus_b
     ComM_ChannelVarType[].NmPrepareBusSleepIndicationStatus_b
     ComM_ChannelVarType[].NmNetworkModeStatus_b
     ComM_ChannelVarType[].PassiveRequestState_u8

     In addition,it also ensures that all the above parameters and
     ComM_ChannelVarType[].ChannelMode_u8 are updated consistently.

       Enable this lock if ComM_EcuM_WakeUpIndication, Nm call backs and ComM
     channel main function can run concurrently. */
}

LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_ChannelNoNest(void)
{
    SCHM_EXIT_DEFAULT();
}
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_LimitationNoNest(void)
{
    SCHM_ENTER_DEFAULT();
  /* This lock is to protect, inhibition related parameters:
     This lock protects the following resources:
     ComM_ChannelVarType[].InhibitionReqStatus_u8
     ComM_PncRamStructType[].WakeUpInhibitionCtr_u16
     ComM_PncRamStructType[].LimitToNoComCtr_u16
     ComM_UserVarType[].LimitToNoComCtr_u16
     ComM_UserVarType[].WakeUpInhibitionCtr_u16
     Enable this lock if
     Either of ComMModeLimitationEnabled or ComMWakeupInhibitionEnabled is configured as TRUE and
     If the api's ComM_LimitChannelToNoComMode(), ComM_LimitECUToNoComMode() and ComM_PreventWakeUp()
     can interrupt each other or themselves.
     */
}
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_LimitationNoNest(void)
{
    SCHM_EXIT_DEFAULT();
}
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Enter_ComM_Channel(void)
{
    SCHM_ENTER_DEFAULT();
    /* This lock is to protect channel mode counters for users.
     * Following resources are protected by this lock:
     * userRamPtr_ps->numChannelsInNoCom_u8
     * userRamPtr_ps->numChannelsInFullCom_u8
     * userRamPtr_ps->numChannelsInSilentCom_u8
     *
     *
     * Enable this lock if
     * 1. Channel main functions can interrupt each other and
     * 2. If there are common users accross channels
     *
     * Configure this lock as Common lock if,
     * 1. ComMRteEnabled is configured as True and
     * 2. Sender receiver interface ComM_CurrentMode is used
     *
     * otherwise
     *
     * This lock can be configured as a NoNest lock
     */
}
LOCAL_INLINE FUNC(void, COMM_CODE) SchM_Exit_ComM_Channel(void)
{
    SCHM_EXIT_DEFAULT();
}
#endif /* _COMM_CFG_SCHM_H */



