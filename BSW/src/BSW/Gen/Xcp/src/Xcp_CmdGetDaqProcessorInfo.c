

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
#if (XCP_CMD_GET_DAQ_PROCESSOR_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns the general information on DAQ lists
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetDaqProcessorInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetDaqProcInfo_t* ResPtr = (Xcp_ResGetDaqProcInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Length of the response */
  XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_DAQ_PROCESSOR_INFO_LENGTH;

  /* Send the Response */

  /* Fill packet Id as 0xFF */
  ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;

  /* Fill General properties of DAQ lists - DAQ_PROPERTIES */
  /* DAQ_PROPERTIES - Bit0: DAQ_CONFIG_TYPE - dynamic DAQ list configuration */
  /* DAQ_PROPERTIES - Bit1: PRESCALER_SUPPORTED */
  ResPtr->DaqProperties_u8 = (XCP_DAQ_PROPERTIES_DAQ_CONFIG_TYPE | XCP_DAQ_PROPERTIES_PRESCALER_SUPPORTED);

# if (XCP_RESUME_MODE == STD_ON)
  /* DAQ_PROPERTIES - Bit2: RESUME_SUPPORTED */
  ResPtr->DaqProperties_u8 |= XCP_DAQ_PROPERTIES_RESUME_SUPPORTED;
# endif
  /* DAQ_PROPERTIES - Bit3: BIT_STIM_SUPPORTED - not supported and is 0 */
# if (XCP_TIMESTAMP == STD_ON)
  /* DAQ_PROPERTIES - Bit4: TIMESTAMP_SUPPORTED - time-stamped mode supported */
  if (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en != XCP_TIMESTAMP_TYPE_NO_TIME_STAMP)
  {
    ResPtr->DaqProperties_u8 |= XCP_DAQ_PROPERTIES_TIMESTAMP_SUPPORTED;
  }
# endif
  /* DAQ_PROPERTIES - Bit5: PID_OFF_SUPPORTED - not supported and is 0 */
  /* DAQ_PROPERTIES - Bit6 and Bit7: Overload indication type */
  if(Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OverloadType_en != XCP_DAQ_NO_OVERLOAD_INDICATION)
  {
    ResPtr->DaqProperties_u8 |= (uint8)(((uint8)Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OverloadType_en) << 6u);
  }

  /* MAX_DAQ: Total number of available DAQ lists */
  ResPtr->MaxDaq_u16          = XCP_MAX_DAQ;
  /* MAX_EVENT_CHANNEL: Total number of available event channels */
  ResPtr->MaxEventChannel_u16 = XCP_MAX_EVENT_CHANNEL;
  /* MIN_DAQ: Total number of predefined DAQ lists */
  ResPtr->MinDaq_u8           = XCP_GET_DAQ_PROCESSOR_INFO_MIN_DAQ;

  /* DAQ_KEY_BYTE - Bit0 to Bit3: Optimisation Type */
  ResPtr->DaqKeyByte_u8  = (uint8)Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OdtOptimizationType_en & 0x0Fu;

  /* DAQ_KEY_BYTE - Bit4 and Bit5: Address_Extension Type - ADDRESS_EXTENSION_FREE which is not allowed 0,1  */
  ResPtr->DaqKeyByte_u8 |= XCP_DAQ_KEY_BYTE_ADDRESS_EXTENSION_FREE;

  /* DAQ_KEY_BYTE - Bit 6 and Bit7: Identification field types */
  if(Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].IdFieldType_en != XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE)
  {
    ResPtr->DaqKeyByte_u8 |= (uint8)((((uint8)Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].IdFieldType_en) - 1u) << 6u);
  }

  /* Send positive response */
  Xcp_SendRes(protLayerId);
  XCP_PARAM_UNUSED(XcpPacket);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetDaqProcessorInfo.c: The command is not enabled - no code is needed in this file */
#endif



