/** @file     Rte_Dcm.h
  *
  * @brief    Application header file
  *
  * @note     AUTOMATICALLY GENERATED FILE! DO NOT EDIT!
  *
  * @note     Generated by ETAS RTA-RTE
  * @note     Version 6.4.1 
  */

#ifndef RTE_DCM_H
#define RTE_DCM_H

#ifndef RTE_CORE
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple application header files included.
#endif /* RTE_APPLICATION_HEADER_FILE */
#define RTE_APPLICATION_HEADER_FILE
#endif /* RTE_CORE */

/*******************************************************
 ***
 *** Includes
 ***
 *******************************************************/

#include "Rte.h"
#include "Rte_Intl.h"
#include "Rte_Dcm_Type.h"

#include "Rte_DataHandleType.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(RTE_RUNNABLEAPI_Dcm_GetActiveProtocol)
   /* Do nothing for this and all elif clauses below (rte_sws_2751) */
#elif defined(RTE_RUNNABLEAPI_Dcm_GetSecurityLevel)
#elif defined(RTE_RUNNABLEAPI_Dcm_GetSesCtrlType)
#elif defined(RTE_RUNNABLEAPI_Dcm_MainFunction)
#elif defined(RTE_RUNNABLEAPI_Dcm_ResetToDefaultSession)
#elif defined(RTE_RUNNABLEAPI_Dcm_SetActiveDiagnostic)
#else
   /* None of above defined so define value including all APIs (rte_sws_2751) */
   #define RTE_PRV_ALL_API
#endif

/*******************************************************
 ***
 *** Constants
 ***
 *******************************************************/

#ifndef RTE_CORE
#define RTE_E_DCMServices_E_NOT_OK ((Std_ReturnType)1)
#define RTE_E_DCMServices_E_OK ((Std_ReturnType)0)
#endif /* RTE_CORE */

/*******************************************************
 ***
 *** Public Types
 ***
 *******************************************************/

/* BEGIN: SWC types (core visible) */
struct Rte_CDS_Dcm {
   uint8 Rte_Dummy;
};
typedef struct Rte_CDS_Dcm Rte_CDS_Dcm;
/* END: SWC types (core visible) */

/*******************************************************
 ***
 *** Private Types
 ***
 *******************************************************/

/* BEGIN: SWC types (private) */
/* END: SWC types (private) */

/*******************************************************
 ***
 *** Instance Declarations
 ***
 *******************************************************/

#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(struct Rte_CDS_Dcm, RTE_CONST) Rte_Inst_Dcm;
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */


#ifndef RTE_CORE
typedef CONSTP2CONST(struct Rte_CDS_Dcm, AUTOMATIC, RTE_CONST) Rte_Instance;
#endif /* RTE_CORE */

/*******************************************************
 ***
 *** API Mapping macros
 ***
 *******************************************************/

/* API Mapping Macros */
#ifndef RTE_CORE

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_Pp_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_MDGP_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(VAR(uint8, AUTOMATIC) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_Pp_DcmControlDTCSetting_MDGP_DcmControlDTCSetting(VAR(uint8, AUTOMATIC) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_Pp_DcmDiagnosticSessionControl_MDGP_DcmDiagnosticSessionControl(VAR(uint8, AUTOMATIC) data);
FUNC(Std_ReturnType, RTE_CODE) Rte_Switch_Dcm_Pp_DcmEcuReset_MDGP_DcmEcuReset(VAR(uint8, AUTOMATIC) data);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#if defined(RTE_PRV_ALL_API) || defined(RTE_RUNNABLEAPI_Dcm_MainFunction)
#define Rte_Switch_Pp_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_MDGP_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel( data ) (Rte_Switch_Dcm_Pp_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel_MDGP_DcmCommunicationControl_ComMChannel_Can_Network_2_Channel(data))
#endif
#if defined(RTE_PRV_ALL_API) || defined(RTE_RUNNABLEAPI_Dcm_MainFunction)
#define Rte_Switch_Pp_DcmControlDTCSetting_MDGP_DcmControlDTCSetting( data ) (Rte_Switch_Dcm_Pp_DcmControlDTCSetting_MDGP_DcmControlDTCSetting(data))
#endif
#if defined(RTE_PRV_ALL_API) || defined(RTE_RUNNABLEAPI_Dcm_MainFunction)
#define Rte_Switch_Pp_DcmDiagnosticSessionControl_MDGP_DcmDiagnosticSessionControl( data ) (Rte_Switch_Dcm_Pp_DcmDiagnosticSessionControl_MDGP_DcmDiagnosticSessionControl(data))
#endif
#if defined(RTE_PRV_ALL_API) || defined(RTE_RUNNABLEAPI_Dcm_MainFunction)
#define Rte_Switch_Pp_DcmEcuReset_MDGP_DcmEcuReset( data ) (Rte_Switch_Dcm_Pp_DcmEcuReset_MDGP_DcmEcuReset(data))
#endif

#endif /* RTE_CORE */

/*******************************************************
 ***
 *** RE Prototypes
 ***
 *******************************************************/

#define Dcm_START_SEC_CODE
#include "Dcm_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(CONSTP2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocol);
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(CONSTP2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);
FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(CONSTP2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);
FUNC(Std_ReturnType, Dcm_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) active);
#define Dcm_STOP_SEC_CODE
#include "Dcm_MemMap.h" /*lint !e537 permit multiple inclusion */

/* Initial values for data element prototypes */

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */

#endif /* !RTE_DCM_H */
