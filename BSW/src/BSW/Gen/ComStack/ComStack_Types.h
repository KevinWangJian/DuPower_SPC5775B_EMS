 

/*
*****************************************************************************************************************
* Based on AUTOSAR_SWS_CommunicationStackTypes.pdf; AR4.2; Rev 2 and BSW_CodingGuidelines_Cur_v.1.10.pdf
*****************************************************************************************************************
*/

/* TRACE[SWS_COMTYPE_00016]: protected against multiple inclusion. */
#ifndef COMSTACK_TYPES_H
#define COMSTACK_TYPES_H

/*
******************************************************************************************************************
* Includes
******************************************************************************************************************
*/

/*TRACE[SWS_COMTYPE_00001]: include file structure */
#include "Std_Types.h"                  /* Standard AUTOSAR types */
#include "ComStack_Cfg.h"               /* ECU dependent part of ComStack Types */

/*
*******************************************************************************************************************
* Types and Defines
*******************************************************************************************************************
*/

/* TRACE[Rule BSW_VersionInfo_002]: Module Vendor Identifier */
/* TRACE[SRS_BSW_00374]  */
#define COMTYPE_VENDOR_ID 0x0006u

/* TRACE[Rule BSW_VersionInfo_003]: Module Identifier  */
/* TRACE[SRS_BSW_00374]  */
#define COMTYPE_MODULE_ID 0x00C4u

/* TRACE[Rule BSW_VersionInfo_004]: Software Version Number and AUTOSAR Specification Version Number. */
/* TRACE[SRS_BSW_00374]  */
#define COMTYPE_SW_MAJOR_VERSION 0x01u
#define COMTYPE_SW_MINOR_VERSION 0x00u
#define COMTYPE_SW_PATCH_VERSION 0x00u
#define COMTYPE_AR_RELEASE_MAJOR_VERSION 0x04u
#define COMTYPE_AR_RELEASE_MINOR_VERSION 0x02u
#define COMTYPE_AR_RELEASE_REVISION_VERSION 0x02u

/* COMTYPE018 - General codes for NotifResultType */

/* NotifResultType related below macros are provided to ensure backward compatibility to AR40,although not applicable
 as per AR422 specifcation. They shall be removed later, when ComStack package adapt to AR422 requirements in
CommunicationStackTypes*/


#define NTFRSLT_OK                     0x00u
#define NTFRSLT_E_NOT_OK               0x01u
#define NTFRSLT_E_TIMEOUT_A            0x02u
#define NTFRSLT_E_TIMEOUT_BS           0x03u
#define NTFRSLT_E_TIMEOUT_CR           0x04u
#define NTFRSLT_E_WRONG_SN             0x05u
#define NTFRSLT_E_INVALID_FS           0x06u
#define NTFRSLT_E_UNEXP_PDU            0x07u
#define NTFRSLT_E_WFT_OVRN             0x08u
#define NTFRSLT_E_ABORT                0x09u
#define NTFRSLT_E_NO_BUFFER            0x0Au
#define NTFRSLT_E_CANCELATION_OK       0x0Bu
#define NTFRSLT_E_CANCELATION_NOT_OK   0x0Cu
#define NTFRSLT_PARAMETER_OK           0x0Du
#define NTFRSLT_E_PARAMETER_NOT_OK     0x0Eu
#define NTFRSLT_E_RX_ON                0x0Fu
#define NTFRSLT_E_VALUE_NOT_OK         0x10u
/*TRACE[SWS_COMTYPE_00011]: PduInfoType*/
typedef struct
{
    P2VAR(uint8,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
    PduLengthType SduLength;
} PduInfoType;

/*TRACE[SWS_COMTYPE_00036]: PNCHandleType used to store the identifier of a partial network cluster.*/
typedef uint8   PNCHandleType;

/*TRACE[SWS_COMTYPE_00031]: TPParameterType-Specify the parameter to which the value has to be changed (TP_STMIN or TP_BS or TP_BC or BS or TP_BFS).*/
typedef enum
{
    TP_STMIN = 0x00,
    TP_BS    = 0x01,
    TP_BC    = 0x02,
    TP_BFS   = 0x03
} TPParameterType;

/*TRACE[SWS_COMTYPE_00012]: BufReq_ReturnType-Variables*/
typedef enum
{
    BUFREQ_OK       = 0x00,
    BUFREQ_E_NOT_OK = 0x01,
    BUFREQ_E_BUSY   = 0x02,
    BUFREQ_E_OVFL   = 0x03
} BufReq_ReturnType;

/* Chapter 8.1.6: Result status of a notification */

/* NotifResultType is provided to ensure backward compatibility to AR40,although not applicable as per AR422 
specifcation and shall be removed later, when ComStack package adapt to AR422 requirements in
CommunicationStackTypes*/
typedef uint8   NotifResultType;

/*TRACE[SWS_COMTYPE_00020]: Variables of this type shall be used to return the bus status evaluated by a transceiver.*/
typedef uint8   BusTrcvErrorType;

/*TRACE[SWS_COMTYPE_00021]: General codes for BusTrcvErrorType.*/
#define BUSTRCV_OK                     0x00
#define BUSTRCV_E_ERROR                0x01

/*TRACE[SWS_COMTYPE_00027]: TpDataStateType-Variables of this type shall be used to store the state of TP buffer.*/
typedef enum
{
    TP_DATACONF = 0x00,
    TP_DATARETRY = 0x01,
    TP_CONFPENDING = 0x02
} TpDataStateType;

/*TRACE[SWS_COMTYPE_00037]:RetryInfoType-Variables */
typedef struct
{
    TpDataStateType TpDataState;
    PduLengthType TxTpDataCnt;
} RetryInfoType;

/*TRACE[SWS_COMTYPE_00038]:NetworkHandleType-Variables*/
typedef uint8   NetworkHandleType;

/*TRACE[SWS_COMTYPE_00039]: IcomConfigIdType-IcomConfigIdType defines the configuration ID.*/
typedef uint8   IcomConfigIdType;

/*TRACE[SWS_COMTYPE_00040]: IcomSwitch_ErrorType-IcomSwitch_ErrorType*/
typedef enum
{
    ICOM_SWITCH_E_OK,
    ICOM_SWITCH_E_FAILED
} IcomSwitch_ErrorType;

#endif /* COMSTACK_TYPES_H */

