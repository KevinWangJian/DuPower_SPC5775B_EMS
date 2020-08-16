

#ifndef DCM_EXPORT_H
#define DCM_EXPORT_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF))
/*
 ***************************************************************************************************
 *    Function prototypes                                                                          */
/**************************************************************************************************/
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetActiveProtocol :API to get the active protocol id
 * @param[in]            :ActiveProtocol: Address of global variable Passed by the appl.
 * @retval               :E_OK:If the protocol is active
 * @retval               :E_NOT_OK:If the protocol is  not active
 */
/*MR12 RULE 8.5 VIOLATION: This extern declaration is  required for rba_DiagAdapt support */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(CONSTP2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocol);
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetSecurityLevel : API to get the active session id
 * @param[in]           :SesCtrlType: Address of global variable Passed by the appl.
 * @retval              : E_OK
 */
/*MR12 RULE 8.5 VIOLATION: This extern declaration is  required for rba_DiagAdapt support */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(CONSTP2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetSecurityLevel : API to get the active security level
 * @param[in]           :SecLevel: Address of global variable Passed by the appl.
 * @retval              :E_OK
 */
/*MR12 RULE 8.5 VIOLATION: This extern declaration is  required for rba_DiagAdapt support */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(CONSTP2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);


/**
* @ingroup DCMCORE_DSLDSD_AUTOSAR
*  Dcm_ResetToDefaultSession: The call to this function allows the application to reset the current session to
*  Default Session.
*  @param                   : None
*  @retval                  : E_OK - The request for resetting the session to default session is accepted.The session transition will be processed in the next Dcm main function
*                             E_NOT_OK - If Dcm is not free and processing some other request.The application has to call the service again in this case to Reset the session to Default
*/
/* MR12 RULE 8.5 VIOLATION:This is required for providing Dcm_ResetToDefaultSession declaration to rba_DiagAdapt RTE AR4.0 enabled configuration */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);

#endif
#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
/* DCM_EXPORT_H_ */
