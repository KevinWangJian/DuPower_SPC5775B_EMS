
/**
 * \defgroup IPDUM_H    IpduM - AUTOSAR interfaces to PduR (Upper Layer)
 * This interface provides the public export of Component IpduM and is to be included by the upper layer Component PduR\n
 * To use this interface include the header <b>IpduM.h</b>
 */
/**
 *********************************************************************
 * \moduledescription
 *
 *
 * \scope           [PUBLIC]
 *********************************************************************
 */

#ifndef IPDUM_H
#define IPDUM_H

/**
 * @ingroup IPDUM_H
 * IPDUM: DET Error ID'd*
 * IPDUM_E_PARAM: API service called with wrong parameter */
#define IPDUM_E_PARAM             0x10
/**
 * @ingroup IPDUM_H
 *  * IPDUM_E_PARAM_POINTER: API service called with a NULL pointer. In case of this error,
 *  the API service shall return immediately without any further action, except for reporting this development error. */
#define IPDUM_E_PARAM_POINTER   0x11
/**
 * @ingroup IPDUM_H
 *  * IPDUM_E_UNINIT: API service used without module initialization */
#define IPDUM_E_UNINIT            0x20
/**
 * @ingroup IPDUM_H
 *  * IPDUM_E_HEADER: API service used without module initialization */
#define IPDUM_E_HEADER            0x30

/**
 * @ingroup IPDUM_H
 *
 * Instance Id refers to an ID assigned by Autosar to identify every unique instance of one Module/Component, used to indicate that module instance which is reporting the error during the call of Det_ReportError()\n
 */
#define IPDUM_INSTANCE_ID  0u

/* START: Service Id's   */
/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_Init
 */
#define IPDUMServiceId_Init                       0x00
/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_GetVersionInfo
 */
#define IPDUMServiceId_GetVersionInfo             0x01
/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_Transmit
 */
#define IPDUMServiceId_Transmit                      0x03

/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_MainFunctionRx
 */
#define IPDUMServiceId_MainFunctionRx               0x11

/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_MainFunctionTx
 */
#define IPDUMServiceId_MainFunctionTx               0x12

/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_TxConfirmation
 */
#define IPDUMServiceId_TxConfirmation             0x40
/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_TriggerTransmit
 */
#define IPDUMServiceId_TriggerTransmit            0x41
/**
 * @ingroup IPDUM_H
 *
 * Indicates that Api Id passed in the call of Det_ReportError corresponds to @see IpduM_RxIndication
 */
#define IPDUMServiceId_RxIndication               0x42

/* END: Service Id's   */

/* AUTOSAR SPECIFICATION VERSION */
/**
 * @ingroup IPDUM_H
 *
 * Used to declare the Major Release Number of Autosar Main Baseline under which this Component IpduM is delivered
 */
#define IPDUM_AR_RELEASE_MAJOR_VERSION  4u
/**
 * @ingroup IPDUM_H
 *
 * Used to declare the Minor Release Number of Autosar Main Baseline under which this Component IpduM is delivered
 */
#define IPDUM_AR_RELEASE_MINOR_VERSION  2u
/**
 * @ingroup IPDUM_H
 *
 * Used to declare the Revision Release Number of Autosar Main Baseline under which this Component IpduM is delivered
 */
#define IPDUM_AR_RELEASE_REVISION_VERSION  2u
/**
 * @ingroup IPDUM_H
 *
 * Macro used by EcuM to initialize IpduM module
 */
#define IpduM_Config    NULL_PTR

/*
 *********************************************************************
 * Includes
 *********************************************************************
 */

#include "IpduM_Types.h"
#include "IpduM_Cfg.h"


#ifdef IPDUM_RXDIRECT_COMINVOCATION
#include "Com.h"
#if (!defined(COM_AR_RELEASE_MAJOR_VERSION) || (COM_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COM_AR_RELEASE_MINOR_VERSION) || (COM_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif


/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
/**
 * @ingroup IPDUM_H
 *
 * IPDUM PDU static type
 */
#define IPDUM_PDUTYPE_STATIC        0
/**
 * @ingroup IPDUM_H
 *
 * IPDUM PDU Dynamic type
 */
#define IPDUM_PDUTYPE_DYNAMIC       1
/**
 * @ingroup IPDUM_H
 * This structure is used for IpduM Config type \n
 *
 * typedef struct \n
 *  { \n
 *      P2CONST(IpduM_TxRequestType, TYPEDEF, IPDUM_APPL_CONST) TxReqTabPtr;    Pointer to the Transmission Request Table\n
        P2CONST(IpduM_TxMPduType, TYPEDEF, IPDUM_APPL_CONST)    TxMPduTabPtr;   Pointer to the Multiplexed-Pdu\n
        P2CONST(IpduM_RxMPduType, TYPEDEF, IPDUM_APPL_CONST)    RxMPduTabPtr;   Pointer to the Reception Request Table\n
        P2CONST(IpduM_RxUpPduType, TYPEDEF, IPDUM_APPL_CONST)   RxUpPduTabPtr;  Pointer to the Received Pdu\n
        P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContainer_pcst; Pointer to the TxContainer Const Pdu table\n
        P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContained_pcst; Pointer to the TxContained Const Pdu table\n
        P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainer_pcst; Pointer to the RxContainer Const Pdu table\n
        P2CONST(IpduM_RxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContained_pcst; Pointer to the RxContained Const Pdu table\n
 *  } IpduM_ConfigType ;
 */
typedef struct
{

    P2CONST(IpduM_TxRequestType, TYPEDEF, IPDUM_APPL_CONST) TxReqTabPtr;
    P2CONST(IpduM_TxMPduType, TYPEDEF, IPDUM_APPL_CONST)    TxMPduTabPtr;
    P2CONST(IpduM_RxMPduType, TYPEDEF, IPDUM_APPL_CONST)    RxMPduTabPtr;
    P2CONST(IpduM_RxUpPduType, TYPEDEF, IPDUM_APPL_CONST)   RxUpPduTabPtr;
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContainer_pcst;
    P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxContained_pcst;
    P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainer_pcst;
    P2CONST(IpduM_RxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContained_pcst;

} IpduM_ConfigType;

/*
 *********************************************************************
 * Prototypes
 *********************************************************************
 */


/**
 * @ingroup IPDUM_H
 *
 *  Basic configuration structure
 */
 /* Begin of  variable section */
#define IPDUM_START_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"

extern  CONST(IpduM_ConfigType, IPDUM_APPL_CONST) IpduMConfig;

/* End of variable section */
#define IPDUM_STOP_SEC_CONST_UNSPECIFIED
#include "IpduM_MemMap.h"

/* Begin of code section
*/
#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**
 * @ingroup IPDUM_H
 *
 * This API initializes the I-PDU Multiplexer.\n
 *
 * @param in       config      - Implementation specific structure with configuration parameters.\n
 *
 * @return None \n
 */
extern  FUNC(void, IPDUM_CODE) IpduM_Init(
                                            P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_DATA) config
                                         );
/**
 * @ingroup IPDUM_H
 *
 *  This call Service is called by the PDU-Router to request a transmission.\n
 *
 * @param in         PdumTxPduId -  ID of I-PDU to be transmitted.
 *                                  Range: 0..(maximum number of I-PDU IDs which are multiplexed) - 1.\n
 * @param in         PduInfoPtr  -  A pointer to a structure with I-PDU related data that shall be
 *                                  transmitted: data length and pointer to I-SDU buffer.\n
 *\n
 * @return            E_OK: Transmit request has been accepted.\n
 *                    E_NOT_OK: Transmit request has not been accepted.\n
 */
extern  FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(
                                                        VAR(PduIdType, AUTOMATIC) PdumTxPduId,
                                                        P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                                       );
/**
 * @ingroup IPDUM_H
 *
 * This is the AUTOSAR callback to indicate successful transmission.\n
 *
 * @param in       PdumTxPduId      - ID of the I-PDU that has been transmitted.\n
 *
 * @return None \n
 */
extern  FUNC(void, IPDUM_CODE) IpduM_TxConfirmation(
                                                    VAR(PduIdType, AUTOMATIC) PdumTxPduId
                                                   );
/**
 * @ingroup IPDUM_H
 *
 *  This is the AUTOSAR callback function to indicate reception of an MPdu.\n
 *
 * @param in         PdumRxPduId    -  ID of the received I-PDU.\n
 *
 * @param in         PduInfoPtr -  Contains the length (SduLength) of the received I-PDU and
 *                                 a pointer to a buffer (SduDataPtr) containing the I-PDU.\n
 *
 * @return None \n
 */

extern  FUNC(void, IPDUM_CODE) IpduM_RxIndication(
                                                    VAR(PduIdType, AUTOMATIC) PdumRxPduId,
                                                    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                                 );

/**
 * @ingroup IPDUM_H
 *
 * This is the AUTOSAR interface for transmission of MPdus through trigger transmit mechanism \n
 *
 * @param in         PdumTxPduId    -  ID of the SDU that is requested to be transmitted.\n
 *
 * @param in         PduInfoPtr -  Contains a pointer to a buffer (SduDataPtr) to where the SDU shall be copied to.
 *                                 On return, the service will indicate the length of the copied SDU data in SduLength.\n
 *\n
 * @return            E_OK: SDU has been copied and SduLength indicates the num-ber of copied bytes.\n
 *                    E_NOT_OK: No SDU has been copied. PduInfoPtr must not be used since it may contain a NULL pointer or point to invalid data.\n
 */
extern  FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(
                                                     VAR(PduIdType, AUTOMATIC) PdumTxPduId,
                                                     P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                                    );
#if defined(IPDUM_ECUC_RB_RTE_IN_USE) && (IPDUM_ECUC_RB_RTE_IN_USE != STD_ON)
    /**
     * @ingroup IPDUM_H
     *
     *  This function performs the processing of the reception activities that are not directly handled within the calls from PduR.
     *  initiated by the calls from PDU-R.\n
     */
    extern  FUNC(void, IPDUM_CODE) IpduM_MainFunctionRx(void);
#endif

#if defined(IPDUM_ECUC_RB_RTE_IN_USE) && (IPDUM_ECUC_RB_RTE_IN_USE != STD_ON)
    /**
     * @ingroup IPDUM_H
     *
     *  This function performs the processing of the transmission activities that are not directly handled within the calls from PduR.
     *  initiated by the calls from PDU-R.\n
     */
    extern  FUNC(void, IPDUM_CODE) IpduM_MainFunctionTx(void);
#endif
/*IPDUM039:This function shall be pre compile time configurable On/Off by the configuration
            parameter: IPDUM_VERSION_INFO_API */
#if (IPDUM_VERSION_INFO_API == STD_ON)
/*IpduM_GetVersionInfo()*/
/**
 * @ingroup IPDUM_H
 *
 * Service for passing the Information through a pointer "*VersionInfo"\n
 * @param     versioninfo - Pointer to where to store the version information of this module.\n
 *\n
 * @return None \n
 */
    extern FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo);
#endif
/* End of code section
*/
#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

#endif /* IPDUM_H */

