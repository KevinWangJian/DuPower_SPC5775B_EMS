

#ifndef XCP_H
#define XCP_H

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "ComStack_Types.h"
#include "Xcp_Types.h"
#include "Xcp_Cfg.h"
#include "Xcp_Commands.h"

#if (XCP_ON_CAN_ENABLED == STD_ON)
#include "XcpOnCan.h"
#endif
#if (XCP_ON_ETHERNET_ENABLED == STD_ON)
#include "XcpOnEth.h"
#endif
#if (XCP_ON_FLEXRAY_ENABLED == STD_ON)
#include "XcpOnFr.h"
#endif
#include "rba_BswSrv.h"


/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/

/* AUTOSAR version checks */
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != XCP_AR_RELEASE_MAJOR_VERSION))
  #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != XCP_AR_RELEASE_MINOR_VERSION))
  #error "AUTOSAR minor version undefined or mismatched"
#endif

/** Macro to mark a parameter as unused (Needed as otherwise compiler/MISRA would complain) */
#define XCP_PARAM_UNUSED(param)                 RBA_BSWSRV_PARAM_UNUSED(param)


/***************************************************************************************************
* Type definitions
***************************************************************************************************/


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/
#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/**
****************************************************************************************************
This function looks for daq lists in all protocol layers, that are configured for this eventchannel.\n
Depending on the direction of the DAQ, it will call Xcp_DaqEvent or Xcp_StimEvent, collecting the
status bits to return them to the caller
\param[in]  XcpEventChannelNumber_u16   eventchannel number to process
\return     Status of the requested Eventchannel
\retval     status_u8   May contain the following status-bits
                        - 0x01: XCP_STATUSBIT_DAQ_STARTED: set, when DAQ is being processed
                        - 0x02: XCP_STATUSBIT_DAQ_ERR_OVERLOAD: set, when an overload occurs
                        - 0x10: XCP_STATUSBIT_STIM_STARTED: set, when STIM is being processed
                        - 0x20: XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE: set, when STIM does not have a complete set of data
\retval     numOfReceivedStimdata_u8  counter, how many complete sets of STIM data have been received. \n
                                      lowest counter will be taken, when there are several DAQ lists in this eventchannel
***************************************************************************************************/
extern Xcp_EventChannelStatus_t Xcp_EventChannel(uint16 XcpEventChannelNumber_u16);
#endif
#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service initializes interfaces and variables of the XCP layer
\param[in]  Xcp_ConfigPtr   pointer to the xcp config structure
\return     -
***************************************************************************************************/
extern void Xcp_Init(const Xcp_ConfigType* Xcp_ConfigPtr);

/**
****************************************************************************************************
Scheduled function of the XCP module
\param[in]  -
\return     -
***************************************************************************************************/
extern void Xcp_MainFunction(void);

/**
****************************************************************************************************
This service enables or disables XCP resources
\param[in]  Xcp_CtlMode_u8  Control mode to enable or to disable the below resource
                            - Bit 0: calibration/paging activated (1) or not (0) -> \ref XCP_RESOURCE_CALPAG
                            - Bit 1: reserved
                            - Bit 2: DAQ lists activated (1) or not (0)          -> \ref XCP_RESOURCE_DAQ
                            - Bit 3: stimulation activated (1) or not (0)        -> \ref XCP_RESOURCE_STIM
                            - Bit 4: Flash programming activated (1) or not (0)  -> \ref XCP_RESOURCE_PGM
                            - Bit 5: reserved
                            - Bit 6: reserved
                            - Bit 7: reserved
\return     -
***************************************************************************************************/
extern void Xcp_SetControlMode(uint8 Xcp_CtlMode_u8);

/**
****************************************************************************************************
This service returns the actual control mode or enabled resource from Xcp
\param[in]  -
\return     Returns enabled resource from Xcp \n
\retval     Control mode to enable or to disable the below resource
            - Bit 0: calibration/paging activated (1) or not (0) -> \ref XCP_RESOURCE_CALPAG
            - Bit 1: reserved
            - Bit 2: DAQ lists activated (1) or not (0)          -> \ref XCP_RESOURCE_DAQ
            - Bit 3: stimulation activated (1) or not (0)        -> \ref XCP_RESOURCE_STIM
            - Bit 4: Flash programming activated (1) or not (0)  -> \ref XCP_RESOURCE_PGM
            - Bit 5: reserved
            - Bit 6: reserved
            - Bit 7: reserved
***************************************************************************************************/
extern uint8 Xcp_GetControlMode(void);

/**
****************************************************************************************************
This service returns the connected transport layer id to a given protocol layer
\param[in]  ProtocolLayerId - Protocol layer Id \n
\return     Connected transport layer id
***************************************************************************************************/
extern uint8 Xcp_GetConnectedTransportLayerId(uint8 ProtocolLayerId);

/**
****************************************************************************************************
This function will return the actual status of XCP:
- connected if any protocol layer is connected
- daq state
- stim state
\param[in]  -
\return     Status of Xcp
\retval     XcpState_en
            - XCP_STATE_DISCONNECTED
            - XCP_STATE_CONNECTED
\retval     DaqState_u8
            - 0x01 XCP_STATE_DAQ_HAS_STOPPED: daq transmission has been stopped (changed since last call)
\retval     StimState_u8
            - 0x01 XCP_STATE_DAQ_HAS_STOPPED: stim transmission has been stopped (changed since last call)
            - 0x02 XCP_STATE_ALL_STIM_DATA_RECEIVED: all stim daq lists have a complete data set
\retval     reserved_u8  for future use, no viable output
***************************************************************************************************/
extern Xcp_GetState_t Xcp_GetState(void);

#if (XCP_VERSION_INFO_API == STD_ON)
/**
****************************************************************************************************
Function updates the version information of this module
\param[in]  versioninfo   version info pointer
\return     -
***************************************************************************************************/
extern void Xcp_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#endif   /* #ifndef XCP_H */


