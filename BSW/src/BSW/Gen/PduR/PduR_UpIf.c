


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/



#include "PduR_Prv.h"
/* Appropriate header files are included to declare the prototypes
 */
#include "PduR_UpIf.h"

#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT == 1)
#include "PduR_Mc.h"
#endif


/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_ComTransmit
 *      This function is called by the COM to request a transmission.
 *
 * \param           PduIdType id: ID of COM I-PDU to be transmitted.
 *                  P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr: Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer
 *
 * \retval          E_OK Transmit request has been accepted
 *                  E_NOT_OK Transmit request has not been accepted
 *
 * \seealso         PDUR202, PDUR206
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_ComTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return ((Std_ReturnType)PduR_rComTransmit( (id) , (ptr)));
}

/* ------------------------------------------------------------------------ */
/* End section for code */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"







/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_IpduMTransmit
 *      This function is called by the IPDUM to request a transmission.
 *
 * \param           PduIdType id: ID of IPDUM I-PDU to be transmitted.
 *                  P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr: Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer
 *
 * \retval          E_OK Transmit request has been accepted
 *                  E_NOT_OK Transmit request has not been accepted
 *
 * \seealso         PDUR202, PDUR206
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_IpduMTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return ((Std_ReturnType)PduR_rIpduMTransmit( (id) , (ptr)));
}

/* ------------------------------------------------------------------------ */
/* End section for code */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"





/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_IpduMRxIndication
 *    This function is called by the IpduM (acting as a lower layer module) after the PDU has been received.
 *
 *
 * \param           PduIdType Id    : ID of IpduM I-PDU that has been received.
 *                  const uint8 *ptr: Pointer to IpduM SDU (buffer of received payload)
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_IpduMRxIndication( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    PduR_rIpduMRxIndication((id) , (ptr));
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_IpduMTxConfirmation - This function is called by the FlexRay Interface after the PDU has been transmitted on the
 *                           FlexRay network.
 *
 *
 * \param           PduIdType id -  ID of IpduM I-PDU to be transmitted.
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_IpduMTxConfirmation( VAR(PduIdType, AUTOMATIC) id)
{
    PduR_rIpduMTxConfirmation(id);
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"



/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_IpduMTriggerTransmit - This function is called by the IpduM for sending out a  frame.
 * The trigger transmit is initiated by the  schedule. Whether this function is called or not is statically
 * configured for each PDU.
 *
 *
 * \param           PduIdType id -  ID of FlexRay L-PDU that is requested to be transmitted.
 *                                  Range: 0..(maximum number of L-PDU IDs which may be transmitted by FlexRay
 *                                             Interface) - 1
 *
 *                  uint8 *  ptr - Pointer to place inside the transmit buffer of the L-PDU where data shall be copied
 *                                 to.
 *
 * \retval          None
 * \seealso         PDUR199
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_IpduMTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return ((Std_ReturnType)PduR_rIpduMTriggerTransmit((id), (ptr)));
}


/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"


