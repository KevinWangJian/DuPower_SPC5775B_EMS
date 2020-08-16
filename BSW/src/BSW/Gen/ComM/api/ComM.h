

/**
\defgroup COMM_H    COMM - AUTOSAR interfaces Upper Layer
*/

#ifndef COMM_H
#define COMM_H
/* EasyCASE ( 106
   Includes */
#include "ComM_Cfg.h"
#include "ComM_Dcm.h"
#include "ComM_BusSM.h"
#include "ComM_EcuMBswM.h"
#include "ComM_Nm.h"
#include "ComM_Main.h"

/* EasyCASE ) */
/* EasyCASE ( 162
   #Defines */
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/* ComM global config type structure */
typedef struct
{
    P2CONST(void,AUTOMATIC,COMM_APPL_CONST) ComM_GlobalConfigData_pcs;
    P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST)  versionInfo;
}ComM_ConfigType;

/* EasyCASE ) */
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
/* EasyCASE ( 195
   Code */
/**
 * @ingroup COMM_H
 *
 * Macro used to define ComM Code Section
 */
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/* EasyCASE ( 226
   Function declaration */
/* EasyCASE ( 253
   ComM_Init */
/**
 * @ingroup COMM_H
 *
 * Description : Initializes the AUTOSAR Communication Manager and the
 *               communication stack and restarts the internal state
 *              machines. ComM shall initialize the communication
 *              stack with the corresponding configuration passed by
 *              EcuM.   \n
 *
 * @Param None \n
 * @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_Init(
                                    P2CONST(ComM_ConfigType,AUTOMATIC,COMM_APPL_CONST) config
                                    );
/* EasyCASE ) */
/* EasyCASE ( 254
   ComM_DeInit */
/**
 * @ingroup COMM_H
 *
 * Description : De-initializes (terminates) the AUTOSAR Communication
 *               Manager. This function shall De-initialize the
 *               Communication modul.Initializes the AUTOSAR
 *               Communication Manager. \n
 *  @Param None \n
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_DeInit(void);

/**
 * @ingroup COMM_H
 *
 * This function Return current state, including sub-state,of the ComM state machine. \n
 *
 *  @param  In:      Channel - The Network Channel for the requested state of ComM state machine. \n
 *
 *  @param  Out:     State - State of the ComM channel state machine. \n
 *
 *  @return          E_OK: Successfully return current state of ComM state machine \n
 *                   E_NOT_OK: Return of current state of ComM state machine failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetState(
                                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                                        P2VAR(ComM_StateType, AUTOMATIC, COMM_VAR) State
                                                    );

/**
 * @ingroup COMM_H
 *
 * This function Returns the initialization status of the AUTOSAR Communication Manager. \n
 *
 *  @param  Out:     Status - COMM_UNINIT: The ComM is not initialized or not usable. Default value after startup \n
 *                                         or after ComM_DeInit() is called. \n
 *                            COMM_INIT: The ComM is initialized and usable. \n
 *
 *  @return          E_OK: Successfully return of initialization status \n
 *                   E_NOT_OK: Return of initialization status failed \n
 */
extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetStatus
                                                (
                                                 P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_VAR) Status
                                                );

/* EasyCASE ) */
/* EasyCASE ( 267
   ComM_GetVersionInfo */
/**
 * @ingroup COMM_H
 *
 * This function returns the published information   \n
 *
 *  @param  Out: Versioninfo \n
 *
 *  @return None \n
 */

extern FUNC(void,COMM_CODE) ComM_GetVersionInfo
                                        (
                                          P2VAR(Std_VersionInfoType, AUTOMATIC, COMM_VAR) versioninfo
                                        );

/* EasyCASE ) */
/* EasyCASE ( 257
   ComM_RequestComMode */
/**
 * @ingroup COMM_H
 *
 * Requesting of a communication mode by a user.  \n
 *
 *  @param  In:     User - Handle of the user who requests a mode \n
 *                  ComMode - COMM_FULL_COMMUNICATION \n
 *                            COMM_NO_COMMUNICATION \n
 *
 *  @return          E_OK: Successfully changed to the new mode \n
 *                   E_NOT_OK: Changing to the new mode failed \n
 *                   COMM_E_MODE_LIMITATION: Mode can not be granted because of mode inhibition. \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType,COMM_CODE) ComM_RequestComMode
                                             (
                                              VAR(ComM_UserHandleType, COMM_VAR) User,
                                              VAR(ComM_ModeType, COMM_VAR) ComMode
                                             );

/* EasyCASE ) */
/* EasyCASE ( 258
   ComM_GetMaxComMode */
/**
 * @ingroup COMM_H
 *
 * Function to query the maximum allowed communication  mode of the corresponding user. \n
 *
 *  @param  In:     User - Handle of the user who requests a mode \n
 *
 *  @param out:     ComMode Name of the requested mode\n
 *
 *  @return          E_OK: Successfully returned maximum allowed Communication Mode \n
 *                   E_NOT_OK: Return of maximum allowed Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */
extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetMaxComMode
                                            (
                                               VAR(ComM_UserHandleType, COMM_VAR) User,
                                               P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                            );
/* EasyCASE ) */
/* EasyCASE ( 259
   ComM_GetRequestedComMode */
/**
 * @ingroup COMM_H
 *
 * Function to query the currently requested communication mode of the corresponding user. \n
 *
 *  @param  In:     User - Handle of the user who requests a mode \n
 *
 *  @param out:     ComMode - Name of the requested mode \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetRequestedComMode
                                                (
                                                   VAR(ComM_UserHandleType, COMM_VAR) User,
                                                   P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                                );

/* EasyCASE ) */
/* EasyCASE ( 260
   ComM_GetCurrentComMode */
/**
 * @ingroup COMM_H
 *
 * Function to query the current Communication Mode. \n
 *
 *  @param  In:     User - Handle of the user who requests a mode \n
 *
 *  @param out:     ComMode - Name of the Current mode \n
 *
 *  @return          E_OK: Successfully returned Communication Mode from Bus State Manager \n
 *                   E_NOT_OK: Return of Communication Mode from Bus State Manager failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType,COMM_CODE) ComM_GetCurrentComMode
                                                (
                                                   VAR(ComM_UserHandleType, COMM_VAR) User,
                                                   P2VAR(ComM_ModeType, AUTOMATIC, COMM_VAR) ComMode
                                                );


/**
 * @ingroup COMM_H
 *
 * Function to query the currently requested communication mode of the corresponding user. \n
 *
 *  @param  In:     User - Handle of the user who requests a mode \n
 *
 *  @param out:     ComMode - Name of the requested mode \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitChannelToNoComMode
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        VAR(boolean, COMM_VAR) Status
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to request or release limit to nocom  inhibition for the channel. \n
 *
*  @param  In:     Channel - Handle of the user who requests a mode  \n
 *
 *  @param out:     Status - request or release inhibition \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_LimitECUToNoComMode
                                        (
                                        VAR(boolean, COMM_VAR) Status
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to request or release wake up inhibition for a channel. \n
 *
 *  @param  In:     Channel - Handle of the user who requests a mode \n
 *
 *  @param out:     Status - request or release inhibition \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_PreventWakeUp
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        VAR(boolean, COMM_VAR) Status
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to change the group classification value. \n
 *
 *  @param  In:     None \n
 *
 *  @param out:     Status - requested value of group classification \n
 *
 *  @return          E_OK: Successfully updated group classification status \n
 *                   E_NOT_OK: Updation of group classification failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_SetECUGroupClassification
                                        (
                                        VAR(ComM_InhibitionStatusType,COMM_VAR) Status
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to query the inhibition counter value. \n
 *
 *  @param  In:     None \n
 *
 *  @param out:     CounterValue - pointer to store counter value \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_ReadInhibitCounter
                                        (
                                          P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to reset the value of inhibition counter. \n
 *
 *  @param  In:     None \n
 *
 *  @param out:     None \n
 *
 *  @return          E_OK: Successfully reset the counter \n
 *                   E_NOT_OK: resetting of counter failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_ResetInhibitCounter
                                        (
                                        void
                                        );

/**
 * @ingroup COMM_H
 *
 * Function to query the current inhibition status of the channel. \n
 *
 *  @param  In:     Channel - Handle of the channel  \n
 *
 *  @param In:     Status - pointer to store inhibition status \n
 *
 *  @return          E_OK: Successfully returned requested Communication Mode \n
 *                   E_NOT_OK: Return of requested Communication Mode failed \n
 *                   COMM_E_UNINIT: ComM not initialized \n
 */

extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetInhibitionStatus
                                        (
                                        VAR(NetworkHandleType, COMM_VAR) Channel,
                                        P2VAR(ComM_InhibitionStatusType, AUTOMATIC, COMM_VAR) Status
                                        );

/* EasyCASE ) */
/* EasyCASE ) */
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"


#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

extern CONST(ComM_ConfigType,COMM_CONST) ComM_Config;

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"



/* EasyCASE ) */
/* EasyCASE ) */
#endif /*COMM_H*/
/* EasyCASE ) */

