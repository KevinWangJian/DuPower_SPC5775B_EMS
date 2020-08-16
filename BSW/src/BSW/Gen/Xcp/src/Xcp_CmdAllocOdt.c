

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


#if (XCP_CMD_ALLOC_ODT_AVAILABLE == STD_ON)

/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static void Xcp_InitDaqOdt(uint16 daqListNo_u16, uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles ODT allocation required by the DAQ List.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdAllocOdt(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdAllocOdt_t* const CmdPtr = (const Xcp_CmdAllocOdt_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;
  uint8 ODTCount = CmdPtr->OdtCount_u8;

  /* Check if the previous state is correct */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_ALLOC_DAQ)
  {
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_ALLOC_ODT;
  }

  /* ALLOC_ODT command must be received after an ALLOC_DAQ or an ALLOC_ODT */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en != XCP_DAQ_STATE_ALLOC_ODT)
  {
    /* Send error response ERR_SEQUENCE. Next possible command for DAQ must be FREE_DAQ. */
    Error = XCP_ERR_SEQUENCE;
  }
  else if(  (ODTCount == 0)
         || (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16) /* DAQ list must exist. */
         || (ODTCount > XCP_ODT_COUNT_DAQ) /* ODT_COUNT must be in range 0x00-0xFC */
         || (
# if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
              /* If identification field is absolute the total number of ODTs can't be bigger than the 0xFC. */
              (Xcp_NoInit[protLayerId].Session.IdFieldType_en == XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE) &&
# endif
              ((Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16 + ODTCount) > XCP_ODT_COUNT_DAQ)
            )
          )
  {
    /* Wrong parameters. Send ERR_OUT_OF_RANGE. */
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  /* Check if ALLOC_ODT was already receive for this DaqList */
  else if (XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId) != 0)
  {
    /* Send error response ERR_SEQUENCE. */
    Error = XCP_ERR_SEQUENCE;
  }
  /* If there is not enough memory to allocate this list, send negative response */
  else if (Xcp_DaqRamCheck(0, ODTCount, 0, protLayerId) == FALSE)
  {
    /* Not sufficient memory. Send ERR_MEMORY_OVERFLOW. */
    Error = XCP_ERR_MEMORY_OVERFLOW;
  }
  else
  {
    /* Store data to DaqList */
    XCP_DAQ_ODTFIRST(CmdPtr->DaqListNum_u16, protLayerId) = Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16;
    XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId) = ODTCount;
    /* Add OdtCount to global OdtCnt */
    Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16 += ODTCount;
    /* Initialize Odts for current DaqList */
    Xcp_InitDaqOdt(CmdPtr->DaqListNum_u16, protLayerId);
    /* Prepare positive response. */
    Error = XCP_NO_ERROR;
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
This function initializes the ODT for current DAQ.
\param[in]  daqListNo_u16   absolute DaqList number
\param[in]  protLayerId     Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_InitDaqOdt(uint16 daqListNo_u16, uint8 protLayerId)
{
  /* Initialize Odt array with 0 for given DaqList number */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemSet() are declared as (void*) for generic implementation of MemSet. */
  Xcp_MemSet(&XCP_ODT(XCP_DAQ_ODTFIRST(daqListNo_u16, protLayerId), protLayerId), 0, XCP_DAQ_ODTCNT(daqListNo_u16, protLayerId) * XCP_SIZEOF_ODT);
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdAllocOdt.c: The command is not enabled - no code is needed in this file */
#endif



