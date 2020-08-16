

#ifndef COM_H
#define COM_H

/*Start: Common Published information*/
/**
 * \defgroup COM_H    COM - AUTOSAR interfaces to upper layers and lower layers.
 * This interface provides the public export of Component Com and is to be included by the upper layer Component
 * and lower layer Component.\n
 * To use this interface include the header <b>Com.h</b>
 */

/*End: Common Published information*/

#include "Com_Cfg.h"

/* DET Error ID's */

/**
 * @ingroup COM_H
 *
 * This macro represents the Error Id for the event when API service is called with wrong parameter. \n
 */
#define COM_E_PARAM         0x01
/**
 * @ingroup COM_H
 *
 * This macro represents the Error Id for the event when API service is called before COM module is uninitialised. \n
 */
#define COM_E_UNINIT        0x02
/**
 * @ingroup COM_H
 *
 * This macro represents the Error Id for the event when API service is called with NULL pointer. \n
 */
#define COM_E_PARAM_POINTER    0x03
/**
 * @ingroup COM_H
 *
 * This macro represents the Return code for the event when the service is currently not available. \n
 */
#define COM_SERVICE_NOT_AVAILABLE   0x80

/**
 * @ingroup COM_H
 *
 * This macro represents the Return code for the event when the buffer of a large I-PDU is locked. \n
 */
#define COM_BUSY                    0x81
/**
 * @ingroup COM_H
 *
 * This macro represents the identifier of the index based instance of COM module. \n
 */
#define COM_INSTANCE_ID  0u



/* START: Com_ServiceIdType - Service Id's   */

/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_Init(). \n
 */
#define COMServiceId_Init                       0x01
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_DeInit(). \n
 */
#define COMServiceId_Deinit                     0x02
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_IpduGroupControl(). \n
 */
#define COMServiceId_IpduGroupControl           0x03
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceptionDMControl(). \n
 */
#define COMServiceId_ReceptionDMControl            0x06
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_GetStatus(). \n
 */
#define COMServiceId_GetStatus                  0x07
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_GetConfigurationId(). \n
 */
#define COMServiceId_GetConfigurationId         0x08
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_GetVersionInfo(). \n
 */
#define COMServiceId_GetVersionInfo             0x09

/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SendSignal(). \n
 */
#define COMServiceId_SendSignal                 0x0a
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceiveSignal(). \n
 */
#define COMServiceId_ReceiveSignal              0x0b

/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceiveDynSignal(). \n
 */
#define COMServiceId_ReceiveDynSignal           0x22

/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SendDynSignal(). \n
 */
#define COMServiceId_SendDynSignal              0x21
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_UpdateShadowSignal(). \n
 */
#define COMServiceId_UpdateShadowSignal         0x0c
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SendSignalGroup(). \n
 */
#define COMServiceId_SendSignalGroup            0x0d
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceiveSignalGroup(). \n
 */
#define COMServiceId_ReceiveSignalGroup         0x0e
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceiveShadowSignal(). \n
 */
#define COMServiceId_ReceiveShadowSignal        0x0f
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_InvalidateSignal(). \n
 */
#define COMServiceId_InvalidateSignal           0x10
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_InvalidateShadowSignal(). \n
 */
#define COMServiceId_InvalidateShadowSignal     0x16
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_InvalidateSignalGroup(). \n
 */
#define COMServiceId_InvalidateSignalGroup      0x1b
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TriggerIpduSend(). \n
 */
#define COMServiceId_TriggerIpduSend            0x17
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_MainFunctionRx(). \n
 */
#define COMServiceId_MainFunctionRx             0x18
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_MainFunctionTx(). \n
 */
#define COMServiceId_MainFunctionTx             0x19
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_MainFunctionRouteSignals(). \n
 */
#define COMServiceId_MainFunctionRouteSignals   0x1a
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TxConfirmation(). \n
 */
#define COMServiceId_TxConfirmation             0x40
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TriggerTransmit(). \n
 */
#define COMServiceId_TriggerTransmit            0x41
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_RxIndication(). \n
 */
#define COMServiceId_RxIndication               0x42
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ClearIpduGroupVector(). \n
 */
#define COMServiceId_ClearIpduGroupVector        0x1C
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SetIpduGroup(). \n
 */
#define COMServiceId_SetIpduGroup               0x1D
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SwitchIpduTxMode(). \n
 */
#define COMServiceId_SwitchIpduTxMode           0x27
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_StartOfReception(). \n
 */
#define COMServiceId_StartOfReception           0x25
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_CopyRxData(). \n
 */
#define COMServiceId_CopyRxData                 0x44
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_CopyTxData(). \n
 */
#define COMServiceId_CopyTxData                 0x43
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TpRxIndication(). \n
 */
#define COMServiceId_TpRxIndication             0x1E
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TpTxConfirmation(). \n
 */
#define COMServiceId_TpTxConfirmation           0x26
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_TriggerIPDUSendWithMetaData() \n
 */
#define COMServiceId_TriggerIPDUSendWithMetaData    0x28
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SendSignalGroupArray() \n
 */
#define COMServiceId_SendSignalGroupArray       0x23
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_ReceiveSignalGroupArray() \n
 */
#define COMServiceId_ReceiveSignalGroupArray    0x24
/* FC_VariationPoint_START */
#ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SetRxIPduControlViaRbaNdsEcuVariant()
 * This is some random number assigned to this API \n
 */
#define COMServiceId_SetRxIPduControlViaRbaNdsEcuVariant       0x91
#endif /* #ifdef COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
#ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT
/**
 * @ingroup COM_H
 *
 * This macro represents the service ID for the API Com_SetTxIPduControlViaRbaNdsEcuVariant()
 * This is some random number assigned to this API \n
 */
#define COMServiceId_SetTxIPduControlViaRbaNdsEcuVariant    0x92
#endif /* #ifdef COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
/* FC_VariationPoint_END */
/* End : Com_ServiceIdType */

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
/**
 * @ingroup COM_H
 *
 * typedef struct \n
 * { \n
 *     P2CONST(void,AUTOMATIC,COM_APPL_CONST) Com_ConfigData; \n
 *     P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST)  versionInfo; \n
 * } Com_ConfigType;
 */
typedef struct
{
    P2CONST(void,AUTOMATIC,COM_APPL_CONST) Com_ConfigData;
    /* Pointer to version info of the module , generated post-build time */
    P2CONST(Std_VersionInfoType, AUTOMATIC, COM_APPL_CONST)  versionInfo;
} Com_ConfigType;

/**
 * @ingroup COM_H
 *
 * COM Configuration base structure used for initialization in case of PBL variant
 */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_ConfigType, COM_CONST) ComConfig;
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"


/* END: Service Id's   */

/****************************************************************************************************************
**                                   Global Function Prototypes                                                **
****************************************************************************************************************/

/* START: API declarations  */

/**
 * @ingroup COM_H
 *
 * This API initializes the Com Interface.\n
 *
 * @param in       config - Pointer to Com module's configuration data.\n
 *
 * @Param None \n
 * @return None \n
 */
/*COM432: Com_Init()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_CONST) config);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
  * @ingroup COM_H
  *
  * This API deinitializes the Com Interface.\n
  *
  * @param None \n
  * @return None \n
  */
/*COM130: Com_DeInit()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_DeInit(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for controlling the Ipdu groups.\n
 *
 * @param in       ipduGroupVector - I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.\n
 * @param in       initialize - Flag to request initialization of the I-PDUs which are newly started.\n
 *
 * @return None \n
 */
/*COM564: Com_IpduGroupControl()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_IpduGroupControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(boolean, AUTOMATIC) initialize );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service to clear Ipdu group vector.\n
 *
 * @param in       ipduGroupVector - I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.\n
 *
 * @return None \n
 */
/*COM562: Com_ClearIpduGroupVector()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_ClearIpduGroupVector(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service to set bit of the given Ipdu group vector that corresponds to the given I-PDU group.\n
 *
 * @param in       ipduGroupVector - I-PDU group vector containing the activation state (stopped = 0/ started = 1) for all I-PDU groups.\n
 * @param in       IpduGroupId - Id of the IpduGroup.\n
 * @param in       bitval - New value of the corresponding bit.\n
 *
 * @return None \n
 */
/*COM563: Com_SetIpduGroup()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_SetIpduGroup(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector, VAR(Com_IpduGroupIdType, AUTOMATIC) IpduGroupId, VAR(boolean, AUTOMATIC) bitval );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service to enable deadline monitoring for the I-PDU groups within the given I-PDU group.\n
 *
 * @param in       ipduGroupVector - Contains the requested deadline monitoring state (disabled = 0/ enabled = 1) for all I-PDU groups.\n
 *
 * @return None \n
 */
/*COM193: Com_EnableReceptionDM()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_ReceptionDMControl(VAR(Com_IpduGroupVector, AUTOMATIC)  ipduGroupVector);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service to get the status of the AUTOSAR COM module.\n
 *
 * @return       COM_INIT :the AUTOSAR COM module is initialized and usable.\n
 * @return       COM_UNINIT:AUTOSAR COM module is not initialized and not usable \n
 */
/*COM194: Com_GetStatus()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 *  Service provides the configuration ID.\n
 *
 * @return          Configuration ID
 */
/*COM375: Com_GetConfigurationId()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint32, COM_CODE) Com_GetConfigurationId(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/*COM425:This function shall be pre compile time configurable On/Off by the configuration
            parameter: COM_VERSION_INFO_API */
/**
 * @ingroup COM_H
 *
 * Service for obtaining the Version info.\n
 * @param out       versioninfo - Pointer to where to store the version information of this module.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_DATA) versioninfo);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service updates the signal object identified by SignalId with the signal referenced by the SignalDataPtr parameter.\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @param in       SignalDataPtr - The pointer to the address where the application data is available.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for receiving the signal, This API copies the data to the application buffer.\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @param in       SignalDataPtr - The pointer to the address where the application data is available.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for Invalidating the signal.\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#ifdef COM_TX_SIGNALGROUP

/**
 * @ingroup COM_H
 *
 *  service updates a group signal with the data, referenced by SignalDataPtr
 *  The update of the group signal data is done in the shadow buffer\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @param in       SignalDataPtr - The pointer to the address where the application data is available.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_UpdateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service copies the content of the associated shadow buffer to the associated I-PDU buffer.Prior to this call,
   all group signals should be updated in the shadow buffer by the call of Com_UpdateShadowSignal.\n
 *
 * @param in       SignalGroupId - Id of the SignalGroup.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for Invalidating the shadow signal (i.e Group signal).\n
 *
 * @param in       SignalId - Id of the signal.\n
 *
 * @return None \n
 */
/*COM288: Com_InvalidateShadowSignal()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_InvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for Invalidating the Signal Group.\n
 *
 * @param in       SignalGroupId - Id of the Signal Group.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_InvalidateSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif
#ifdef COM_RX_SIGNALGROUP

/**
 * @ingroup COM_H
 *
 * Service used to copy the SignalGroup content from IpduBuffer to Shadowbuffer.\n
 *
 * @param in       SignalGroupId - Id of the Signal Group.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
 */
/*COM201: Com_ReceiveSignalGroup()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for receiving the shadow Signal.\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @param in       SignalDataPtr - Pointer to the the signal data .\n
 *
 * @return None \n
 */
/*COM202: Com_ReceiveShadowSignal()*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_ReceiveShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

/**
 * @ingroup COM_H
 *
 * Service updates the signal object identified by SignalId with the signal referenced by the SignalDataPtr parameter,
 * with length referenced by length parameter.\n
 * @param in       SignalId         - Id of the signal.\n
 * @param in       SignalDataPtr - The pointer to the address where the application data is available.\n
 * @param in       Length         - The Length of the signal to be transmitted.\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.\n
                   E_NOT_OK    - if the requested length is greater than maximum configured length.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
        VAR(uint16, AUTOMATIC) Length);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service for receiving the signal, This API copies the data to the application buffer, with length in LengthPtr.\n
 *
 * @param in       SignalId - Id of the signal.\n
 * @param in       SignalDataPtr - The pointer to the address where the application data is available.\n
 * @param in/out   LengthPtr - The pointer to the address where the received length of the signal is updated.\n
 *                     LengthPtr - The pointer to the address where the received length is expected to be greater or equal to received length\n
 * @return         E_OK - Service has been accepted.\n
                   COM_SERVICE_NOT_AVAILABLE - Corresponding I-PDU group was stopped.
                   E_NOT_OK - if application requests for length less than the received length\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId,P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
        P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) LengthPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service copies the content of the provided SignalGroupArrayPtr to the associated I-PDU.
 * The provided data shall correspond to the array representation of the signal group.
 *
 * @param in       SignalGroupId        - Id of signal group to be sent \n
 *                 *SignalGroupArrayPtr - Reference to the signal group array \n
 *
 * @return None    E_OK                      : service has been accepted
*                  COM_SERVICE_NOT_AVAILABLE : corresponding I-PDU group was stopped
*                                              (or service failed due to development error)
*                  COM_BUSY                  : in case the TP-Buffer is locked for large data types handling\n
 */
# define COM_START_SEC_CODE
# include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_SendSignalGroupArray( Com_SignalGroupIdType  SignalGroupId,
                                                                 const uint8 *SignalGroupArrayPtr );
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service copies the received signal group array representation from the PDU to the location designated by
 * SignalGroupArrayPtr. \n
 *
 * @param in    : SignalGroupId        - Id of signal group to be sent \n
 * @param out   : *SignalGroupArrayPtr - reference to the location where the received signal group array
 *                                       shall be stored \n
 *
 * @return None : E_OK                      : service has been accepted
 *                COM_SERVICE_NOT_AVAILABLE : corresponding I-PDU group was stopped
 *                                            (or service failed due to development error)
 *                COM_BUSY                  : in case the TP-Buffer is locked for large data types handling\n
 */
# define COM_START_SEC_CODE
# include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReceiveSignalGroupArray( Com_SignalGroupIdType  SignalGroupId,
                                                                          uint8 *SignalGroupArrayPtr );
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service used within the Ipdu-Callout. The I-PDU with the given ID is triggered for transmission.\n
 *
 * @param in       PduId - Id of the Tx Ipdu.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_TriggerIPDUSend(VAR(PduIdType, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service is triggered to transmit I-PDU with Metadata.\n
 *
 * @param in       PduId   -> The I-PDU-ID of the I-PDU that shall be triggered for sending \n
 *                 Metadata -> A pointer to the metadata for the triggered send-request \n
 *
 * @return         Std_ReturnType \n
 *                  E_OK:     I-PDU was triggered for transmission \n
 *                  E_NOT_OK: I-PDU is stopped, the transmission could not be triggered \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"

extern FUNC( Std_ReturnType, COM_CODE ) Com_TriggerIPDUSendWithMetaData( VAR( PduIdType, AUTOMATIC ) PduId,
                                                            P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) MetaData );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * Service called by the lower layer when an AUTOSAR COM I-PDU shall be transmitted. Copies the contents of
   I-PDU transmit buffer to the L-PDU buffer given by PduInfoPtr.\n
 *
 * @param in       TxPduId - Id of the Tx Ipdu.\n
 * @param in       PduInfoPtr - Pointer to the address where the COM module shall copy the Ipdu data and length information.\n
 * @return         E_OK - SDU has been copied and SduLength indicates the number of copied bytes. \n
                   E_NOT_OK - No SDU has been copied. PduInfoPtr must not be used since it may contain a\n
                              NULL pointer or point to invalid data.
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(VAR(PduIdType, AUTOMATIC) TxPduId,P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service called by the lower layer after an I-PDU has been received.\n
 *
 * @param in       RxPduId - Id of the received Ipdu.\n
 * @param in       PduInfoPtr - Contains the length of the received I-PDU and a pointer to a buffer containing the I-PDU.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_RxIndication(VAR(PduIdType, AUTOMATIC) RxPduId,P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service called by the lower layer after the PDU has been transmitted on the network.\n
 *
 * @param in       TxPduId - Id of the Tx Ipdu.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_TxConfirmation(VAR(PduIdType, AUTOMATIC) TxPduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#if ( COM_ECUC_RB_RTE_IN_USE == STD_OFF )
/**
 * @ingroup COM_H
 *
 * Service to perform the processing of the AUTOSAR COM reception activities
 * that are not directly initiated by the calls from the RTE and PDU-R.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_MainFunctionRx(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Service to perform the processing of the AUTOSAR COM transmission activities
 * that are not directly initiated by the calls from the RTE and PDU-R.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_MainFunctionTx(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
 * @ingroup COM_H
 *
 * Calls the signal gateway part of the AUTOSAR COM module to forward received signals to be routed.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_MainFunctionRouteSignals(void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* #if ( COM_ECUC_RB_RTE_IN_USE == STD_OFF ) */

/* FC_VariationPoint_START */
/**
* @ingroup COM_H
*
* The below function is used to change the Periodicity of all the Tx frames .\n
*
* @param in      CommonPeriod - New period (interms of multiples of Com_mainFunctionTx() raster time)\n
*
* @return None \n
*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_ReduceBusload(VAR(uint16, AUTOMATIC) CommonPeriod);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/**
* @ingroup COM_H
*
* The below function is used to change the period of all the Tx frames to a old period from common TX period, set by \n
* function Com_ReduceBusload().\n
*
* @return None \n
*/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_RestoreBusload (void);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_END */

/* FC_VariationPoint_START */
/* CC specific function */
 /**
 * @ingroup COM_H
 *
 * this function checks whether the Tx frame is scheduled to be sent in the coming cycle.\n
 *
 * @param in       ComTxPduId - Tx ipdu ID.\n
 * @param ComCallerTaskCycle , this parameter is the value of caller's task cycle in ms.
 * i.e : if the Caller is in 1ms, then the ComCallerTaskCycle = 1
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(boolean, COM_CODE) Com_IsTxScheduled(VAR(PduIdType, AUTOMATIC) ComTxPduId, VAR(uint16, AUTOMATIC)ComCallerTaskCycle);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_END */
/* FC_VariationPoint_START */
/**
 * @ingroup COM_H
 *
 *  Service for Reading the length of the received IPdu.\n
 *
 * @param in       ComRxPduId - Id of the I-PDU of which the transmission mode shall be changed.\n
 * @param in       RxIPduLengthPtr - The transmission mode that shall be set.\n
 *
 * @return         E_OK - Service has been accepted.\n
 * @return         COM_SERVICE_NOT_AVAILABLE-\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(uint8, COM_CODE) Com_ReadRxIPduLength(VAR(PduIdType, AUTOMATIC) ComRxPduId, P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) RxIPduLengthPtr);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_END */
/**
 * @ingroup COM_H
 *
 * The service Com_SwitchIpduTxMode sets the transmission mode of the I-PDU referenced by PduId to Mode.\n
 *
 * @param in       PduId - Id of the I-PDU of which the transmission mode shall be changed.\n
 * @param in       Mode - The transmission mode that shall be set.\n
 *
 * @return None \n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void,COM_CODE) Com_SwitchIpduTxMode(VAR(PduIdType, AUTOMATIC) PduId, VAR(boolean, AUTOMATIC)  Mode);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * The service COM_ProvideRxIpduStatus returns the status of Rx I-PDU referenced by PduId.\n
 *
 * @param in       PduId - Id of the I-PDU of which the IPDU status is required.\n
 *
 * @return boolean - the service returns TRUE,  if the Ipdu is STARTED,\n
 *                                  returns FALSE, if the Ipdu is STOPPED.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(boolean,COM_CODE) Com_ProvideRxIpduStatus(VAR(PduIdType, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/**
 * @ingroup COM_H
 *
 * The service COM_ProvideTxIpduStatus returns the status of Tx I-PDU referenced by PduId.\n
 *
 * @param in       PduId - Id of the I-PDU of which the IPDU status is required.\n
 *
 * @return boolean - the service returns TRUE,  if the Ipdu is STARTED,\n
 *                                  returns FALSE, if the Ipdu is STOPPED.\n
 */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(boolean,COM_CODE) Com_ProvideTxIpduStatus(VAR(PduIdType, AUTOMATIC) PduId);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception(PduIdType ComRxPduId, const PduInfoType* TpSduInfoPtr, PduLengthType TpSduLength, PduLengthType* RxBufferSizePtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData( PduIdType PduId, const PduInfoType* PduInfoPointer, PduLengthType* RxBufferSizePtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(BufReq_ReturnType, COM_CODE) Com_CopyTxData( PduIdType PduId, PduInfoType* PduInfoPtr, RetryInfoType* RetryInfoPtr, PduLengthType* TxDataCntPtr );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_TpRxIndication( PduIdType PduId, Std_ReturnType Result );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_TpTxConfirmation( PduIdType PduId, Std_ReturnType Result );
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_START */
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_SetTxIPduControlViaRbaNdsEcuVariant(VAR(PduIdType, AUTOMATIC) IpduId, VAR(boolean, AUTOMATIC) IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
extern FUNC(void, COM_CODE) Com_SetRxIPduControlViaRbaNdsEcuVariant(VAR(PduIdType, AUTOMATIC) IpduId, VAR(boolean, AUTOMATIC) IpduStatus);
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_END */
/* END: API declarations  */

#endif /* #ifndef COM_H */

