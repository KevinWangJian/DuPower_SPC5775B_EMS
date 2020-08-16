

/**
\defgroup COMM_NM_H    COMM - AUTOSAR interfaces Upper Layer
*/

/* EasyCASE - */
#ifndef COMM_NM_H
#define COMM_NM_H
/* EasyCASE ( 106
   Includes */

#include "ComM_Cfg.h"
#include "ComStack_Types.h"

/* EasyCASE ) */
/* EasyCASE ( 162
   #Defines */
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/* EasyCASE ) */
/* EasyCASE ( 168
   Type Definitions */
/* EasyCASE ) */
/* EasyCASE ( 38
   Compatibility Check */
/* EasyCASE ) */
/* EasyCASE ( 167
   Extern Declarations */
/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */
/* EasyCASE ( 274
   Code */
/* EasyCASE ( 269
   ComM_Nm_NetworkStartIndication */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/**
 * @ingroup COMM_NM_H
 *
 * Indication that a NM-message has been received in the Bus Sleep Mode, what indicates that some nodes in the network \n
 * have already entered the Network Mode. \n
 *
 *  @param  In:      Channel -Handle to identify a communication channel \n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_NetworkStartIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);
/* EasyCASE ) */
/* EasyCASE ( 270
   ComM_Nm_BusSleepMode */
/**
 * @ingroup COMM_NM_H
 *
 * Notification that the network management has entered Bus-Sleep Mode. This callback function should perform a \n
 * transition of the hardware and transceiver to bus-sleep mode. \n
 *
 *  @param  In:      Channel -Handle to identify a communication channel\n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_BusSleepMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);
/* EasyCASE ) */
/* EasyCASE ( 271
   ComM_Nm_NetworkMode */
/**
 * @ingroup COMM_NM_H
 *
 * Notification that the network management has entered Network Mode. \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel\n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_NetworkMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);
/* EasyCASE ) */
/* EasyCASE ( 272
   ComM_Nm_RestartIndication */

/**
 * @ingroup COMM_NM_H
 *
 * If NmIf has started to shut down the coordinated busses, AND not all coordinated busses have indicated bus sleep state, \n
 * AND on at least on one of the coordinated busses NM is restarted, THEN the NM Interface shall call the callback function \n
 * ComM_Nm_RestartIndication with the nmNetworkHandle of the channels which have already indicated bus sleep state. \n
 *
 *  @param  In:      Channel -Handle to identify a communication channel\n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_RestartIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);
/* EasyCASE ) */
/* EasyCASE ( 273
   ComM_Nm_PrepareBusSleepMode */
/**
 * @ingroup COMM_NM_H
 *
 * Notification that the network management has entered Prepare Bus-Sleep Mode. Reentrancy: Reentrant (but not for the same NM-Channel) \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel\n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_PrepareBusSleepMode
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);
/* EasyCASE ) */
/* EasyCASE ) */
/* EasyCASE ) */
/**
 * @ingroup COMM_NM_H
 *
 * Indicates that NM message transmission has failed \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel\n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Nm_TransmissionFailure
(
         VAR (NetworkHandleType,AUTOMATIC) Channel
);

/**
 * @ingroup COMM_NM_H
 *
 * Indicates that NM-Timeout time has expired when Network is still not released \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel \n
 *
 *  @return None \n
 */

extern FUNC(void,COMM_CODE) ComM_Nm_NetworkTimeoutException
(
         VAR(NetworkHandleType,AUTOMATIC) Channel
);

/**
 * @ingroup COMM_NM_H
 *
 * Indicates Reception \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel\n
 *
 *  @return None \n
 */

extern FUNC(void,COMM_CODE) ComM_Nm_RxIndication
(
       VAR(NetworkHandleType,AUTOMATIC) Channel
);


#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*COMM_NM_H*/
/* EasyCASE ) */

