

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


#if (XCP_CMD_ALLOC_DAQ_AVAILABLE == STD_ON)

/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static void Xcp_InitDaqList(uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to allocate the DAQ List required by the DAQ.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdAllocDaq(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdAllocDaq_t* const CmdPtr = (const Xcp_CmdAllocDaq_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check if the previous state is correct */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_FREE_DAQ)
  {
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_ALLOC_DAQ;
  }

  /* Check if ALLOC_DAQ was received in the correct sequence. The command must be received after ALLOC_DAQ or FREE_DAQ. */
  if(Xcp_NoInit[protLayerId].DaqConfig.DaqState_en != XCP_DAQ_STATE_ALLOC_DAQ )
  {
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    /* Search and set dynamic Daq memory */
    Error = Xcp_DaqRamSetRam(protLayerId);
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Check if the memory is sufficient for the new number of DAQ lists. */
    if (Xcp_DaqRamCheck(CmdPtr->DaqCount_u16, 0 ,0, protLayerId) == FALSE)
    {
      /* Not sufficient memory. Send ERR_MEMORY_OVERFLOW. */
      Error = XCP_ERR_MEMORY_OVERFLOW;
    }
    else
    {
      /* Update the DAQ count in the configuration with the new allocated number. */
      Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16 = CmdPtr->DaqCount_u16;
      /* Initialize DaqList parameters */
      Xcp_InitDaqList(protLayerId);
    }
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Send positive response */
    Xcp_SendPosRes(protLayerId);
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/***************************************************************************************************
* Local functions
***************************************************************************************************/

/**
****************************************************************************************************
This function initialises the DAQ list parameters for defined DAQs.
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_InitDaqList(uint8 protLayerId)
{
  /* Local variables */
  uint16 i;

  /* Initialize complete DaqList array with 0 */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemSet() are declared as (void*) for generic implementation of MemSet. */
  Xcp_MemSet(&XCP_DAQ(0, protLayerId), 0, Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16 * XCP_SIZEOF_DAQ);

  /* Initialize DaqList array for parameters which must be != 0 */
  for (i = 0; i < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; i++)
  {
    XCP_DAQ(i, protLayerId).XcpTxPduId = 0xFF;
    Xcp_InitDaqQueue(i, protLayerId);
  }
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdAllocDaq.c: The command is not enabled - no code is needed in this file */
#endif



