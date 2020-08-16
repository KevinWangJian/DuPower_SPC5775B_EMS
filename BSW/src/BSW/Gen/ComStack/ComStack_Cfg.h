 

/*
*******************************************************************************************************************
* Based on AUTOSAR_SWS_CommunicationStackTypes.pdf; AR4.2; Rev 2 and BSW_CodingGuidelines_Cur_v.1.10.pdf
*******************************************************************************************************************
*/

/* TRACE[SWS_COMTYPE_00016]: protected against multiple inclusion. */
#ifndef COMSTACK_CFG_H
#define COMSTACK_CFG_H

/*
*******************************************************************************************************************
* Types and Defines
*******************************************************************************************************************
*/


/* TRACE[SWS_COMTYPE_00005], TRACE[SWS_COMTYPE_00029] and TRACE[SWS_COMTYPE_00030]:
  Type of PDU ID. Allowed ranges: uint8/uint16 */
typedef uint16    PduIdType;

/* TRACE[SWS_COMTYPE_00008], TRACE[SWS_COMTYPE_00029] and TRACE[SWS_COMTYPE_00030]:
  Type of PDU Length. Allowed ranges: uint8/uint16/uint32 */
typedef uint16    PduLengthType;

#endif /* COMSTACK_CFG_H */

