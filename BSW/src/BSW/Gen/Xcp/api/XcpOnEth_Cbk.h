

#ifndef XCPONETH_CBK_H
#define XCPONETH_CBK_H

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Symbolic_Names_Cfg.h"  /* For symbolic names which is used in lower layer */

/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/


/***************************************************************************************************
* Type definitions
***************************************************************************************************/


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been received
\param[in]  XcpRxPduId    PduId that has been received
\param[in]  XcpRxPduPtr   Pointer to received Pdu
\return     -
***************************************************************************************************/
extern void Xcp_SoAdIfRxIndication(PduIdType XcpRxPduId, const PduInfoType* XcpRxPduPtr);

/**
****************************************************************************************************
This function is called by the lower layers when SoConMode changes
\param[in]  SoConId   Id of the socket connection
\param[in]  Mode      new socket connection mode
\return     -
***************************************************************************************************/
extern void Xcp_SoConModeChg(SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode);

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been transmitted
\param[in]  XcpTxPduId  PduId that has been transmitted
\return     -
***************************************************************************************************/
extern void Xcp_SoAdIfTxConfirmation(PduIdType XcpTxPduId);

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#endif   /* #ifndef XCPONETH_CBK_H */


