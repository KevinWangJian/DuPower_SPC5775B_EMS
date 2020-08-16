

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
LOCAL_INLINE uint8* Xcp_CopyOdt             (uint8* dest_pu8, uint16 AbsOdtNum, uint32* lastAddressPtr, uint32* lastValuePtr, uint8 protLayerId);
#if (XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL == STD_ON)
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_Appl (uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId);
#else
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_Safe (uint8* dest_pu8, uint16 AbsOdtNum, uint32* lastAddressPtr, uint32* lastValuePtr, uint8 protLayerId);
# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_32   (uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId); /* Function is generated using GEN_OPTIMIZED_COPY_FUNCTION(32) */
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_16   (uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId); /* Function is generated using GEN_OPTIMIZED_COPY_FUNCTION(16) */
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_8    (uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId); /* Function is generated using GEN_OPTIMIZED_COPY_FUNCTION(8) */
# endif
#endif
LOCAL_INLINE uint8* Xcp_PutIdField          (uint8* dest_pu8, uint16 AbsOdtNum, uint16 daqListNo, uint8 protLayerId);
#if (XCP_TIMESTAMP == STD_ON)
LOCAL_INLINE uint8* Xcp_PutTimestamp        (uint8* dest_pu8, uint8 protLayerId);
#endif

/***************************************************************************************************
* Functions
***************************************************************************************************/

/**
****************************************************************************************************
This function processes the DaqList (direction DAQ) by setting the queue destination,
placing IdField and Timestamp and calls the subfunction Xcp_CopyOdt for each ODT.
\param[in]  daqListNo_u16   daq list number to process
\param[in]  protLayerId     protocol layer id
\return     status bits
\retval     0x01  XCP_STATUSBIT_DAQ_STARTED: always set, because DAQ is being processed
\retval     0x02  XCP_STATUSBIT_DAQ_ERR_OVERLOAD: set, when an overload occurs
***************************************************************************************************/
uint8 Xcp_DaqEvent(uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_DaqList_t* daqListPtr;
  uint8* dest_pu8;
  uint32 lastAddress;
  uint32 lastValue;
  uint16 WritePos_u16;
  uint16 maxDtoAligned;
  uint16 AbsODTNo_u16;
  uint16 OdtFirst_u16;
  uint8  OdtCnt_u8;
  uint8  retval;

#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON && CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  uint32  tempval;
  uint32* address;
#endif
  /* when function is called, DAQ was already started */
  retval = XCP_STATUSBIT_DAQ_STARTED;

  /* each ODT buffer shall start at 4 byte aligned address */
  maxDtoAligned = XCP_MAXDTO_4ALIGNED(protLayerId);

  daqListPtr = &(XCP_DAQ(daqListNo_u16, protLayerId));
  /** Start of DAQ_FACTOR_1 Runtime measurement **/
  XCP_RTM(0);
  /* Is the cycle counter equal to prescaler value */
  if(daqListPtr->CycleCnt_u8 == daqListPtr->Prescaler_u8 )
  {
    /* Reset cycle counter */
    daqListPtr->CycleCnt_u8 = 1;

    /* Copy the global ODT values to local variable */
    OdtCnt_u8 = daqListPtr->OdtCnt_u8;
    OdtFirst_u16 = daqListPtr->OdtFirst_u16;

    /* reset last read address/value */
    lastAddress = 0xFFFFFFFFu;
    lastValue = 0xFFFFFFFFu;

    /* fetch write and read position */
    WritePos_u16 = daqListPtr->DaqListQuePos.WritePos_u16;

    /** End of DAQ_FACTOR_1 Runtime measurement **/
    XCP_RTM(1);
    /** Start of ODT_FACTOR_1 Runtime measurement **/
    XCP_RTM(0);
    /* Loop until the last ODT */

    for (AbsODTNo_u16 = OdtFirst_u16; AbsODTNo_u16 < (OdtFirst_u16 + OdtCnt_u8); AbsODTNo_u16++)
    {
      /* check if next item fits into queue */
      if (((WritePos_u16 + 1) % daqListPtr->DaqListQuePos.QueSize_u16) != daqListPtr->DaqListQuePos.ReadPos_u16)
      {
        /* set destination pointer to 4 byte aligned queue buffer */
        dest_pu8 = &(daqListPtr->DaqListQue_p[WritePos_u16 * maxDtoAligned]);
#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON && CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
        /* MR12 RULE 11.5, 1.1 VIOLATION: The calling layers ensure 4-Byte-Alignment. address is then used to do an atomic access to 32bit
                                          Casting over void* is necessary as otherwise some compilers complain */
        address = (uint32*) (void*)(dest_pu8);
#endif
        /* place identification field inside queue */
        dest_pu8 = Xcp_PutIdField(dest_pu8, AbsODTNo_u16, daqListNo_u16, protLayerId);
#if (XCP_TIMESTAMP == STD_ON)
        /* check if timestamp needs to be put */
        if ( (AbsODTNo_u16 == OdtFirst_u16) && ((daqListPtr->Mode_u8 & XCP_DAQLISTMODE_TIMESTAMP) == XCP_DAQLISTMODE_TIMESTAMP) ) /* only on first ODT and if enabled by master*/
        {
          dest_pu8 = Xcp_PutTimestamp(dest_pu8, protLayerId); /* put the timestamp, store pointer to next available address */
        }
#endif
        /** End of ODT_FACTOR_1 Runtime measurement **/
        XCP_RTM(1);

        /* Process one ODT: Copy the data of the OdtEntries into the internal buffer (dest_pu8) */
        dest_pu8 = Xcp_CopyOdt(dest_pu8, AbsODTNo_u16, &lastAddress, &lastValue, protLayerId);

#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON && CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
        /* swap endianness in CAN packets */
        if (daqListPtr->XcpTxPduId != XCP_PDU_ID_UNKNOWN)
        {
          /* MR12 RULE 11.4 VIOLATION: Cast from pointer to uint32 is OK as the addresses are 32bit long */
          while ( ((uint32) address) < (((uint32) dest_pu8)))
          {
            /* store content temporarily */
            tempval = *address;
            /* change endianness of each byte for faster transmission */
            *address = (tempval << 24u) | ((tempval & 0xFF00u) << 8u) | ((tempval >> 8u) & 0xFF00u) | (tempval >> 24u);
            /* increase address */
            address++;
          }
        }
#endif
        /** Start of ODT_FACTOR_1 Runtime measurement **/
        XCP_RTM(1);
        /* Check if was the end of the queue */
        if (WritePos_u16 == (daqListPtr->DaqListQuePos.QueSize_u16 - 1))
        {
          /* end of the Queue is reached, wrap around */
            WritePos_u16 = 0;
        }
        else
        {
          /* increment index to the next available buffer */
          WritePos_u16++;
        }
      }
      else
      {
        /* overload detected */
        /* no further processing in this event, return overload */
        retval = (XCP_STATUSBIT_DAQ_STARTED|XCP_STATUSBIT_DAQ_ERR_OVERLOAD);
        /** End of DAQ_FACTOR_1 Runtime measurement **/
        XCP_RTM(1);
        break;
      }
    } /* Loop until the last ODT */
    /** Start of DAQ_FACTOR_2 Runtime measurement **/
    XCP_RTM(0);

    /* check if overload occurred */
    if ((retval & XCP_STATUSBIT_DAQ_ERR_OVERLOAD) == 0u)
    {
      /* update the write position of the DAQ queue */
      daqListPtr->DaqListQuePos.WritePos_u16 = WritePos_u16;
      /* transmit first packet */
      Xcp_SendDaq(daqListNo_u16, protLayerId);
    }
    else
    {
      /* overload detected */
#if (XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED == STD_ON)
      Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b = TRUE;
#endif
      if (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OverloadType_en == XCP_DAQ_OVERLOAD_INDICATION_EVENT)
      {
#if (XCP_DAQ_OVERLOAD_DEBUG_EVENT == STD_ON)
        /* local variables only needed here */
        Xcp_Cto8_t XcpEvPacket;
        Xcp_EvDebugOverload_t* EvPtr;
        /* initialize overload debug event packet */
        XcpEvPacket.Length_u32 = XCP_EV_DEBUG_OVERLOAD_LENGTH;
        /* MR12 RULE 11.5 VIOLATION: The calling layers ensure 4-Byte-Alignment. This cast allows easier (= safer) access to the data in the buffer */
        EvPtr = (Xcp_EvDebugOverload_t*) (void*) XcpEvPacket.Buffer_au8;
        EvPtr->DaqListNum_u16 = daqListNo_u16;
        /* send Event if configured for this transport layer */
        EvPtr->PacketId_u8 = XCP_PACKET_ID_EV;
        EvPtr->EventCode_u8 = XCP_EV_DAQ_OVERLOAD;
        Xcp_SendEv(&XcpEvPacket, protLayerId);
#else /* (XCP_DAQ_OVERLOAD_DEBUG_EVENT == STD_ON) */
        /* send XCP_EV_DAQ_OVERLOAD event */
        Xcp_SendEv_Code(XCP_EV_DAQ_OVERLOAD, protLayerId);
#endif /* (XCP_DAQ_OVERLOAD_DEBUG_EVENT == STD_ON) */
      }
    }
    /** End of DAQ_FACTOR_2 Runtime measurement **/
    XCP_RTM(1);
  }
  else
  {
    /* Increment cycle counter */
    daqListPtr->CycleCnt_u8++;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return retval;
}


/**
****************************************************************************************************
This function processes the given ODT.
\param[in]  dest_pu8        pointer to destination
\param[in]  AbsOdtNum       ODT number that shall be processed
\param[in]  lastAddressPtr  pointer to last address that has been read
\param[in]  lastValuePtr    pointer to last value of that address
\param[in]  protLayerId     protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
LOCAL_INLINE uint8 * Xcp_CopyOdt(uint8* dest_pu8, uint16 AbsOdtNum, uint32* lastAddressPtr, uint32* lastValuePtr, uint8 protLayerId)
{
#if (XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL == STD_ON)
  XCP_PARAM_UNUSED(lastAddressPtr);
  XCP_PARAM_UNUSED(lastValuePtr);

  /* Call application function to copy the OdtEntries */
  dest_pu8 = Xcp_CopyOdtEntries_Appl(dest_pu8, AbsOdtNum, protLayerId);
#else
# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
  /* Determine the copy routine to be used */
  switch (XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId))
  {
    case XCP_ODT_COPY_32:
    {
      dest_pu8 = Xcp_CopyOdtEntries_32(dest_pu8, AbsOdtNum, protLayerId);
    }
    break;
    case XCP_ODT_COPY_16:
    {
      dest_pu8 = Xcp_CopyOdtEntries_16(dest_pu8, AbsOdtNum, protLayerId);
    }
    break;
    case XCP_ODT_COPY_8:
    {
      dest_pu8 = Xcp_CopyOdtEntries_8(dest_pu8, AbsOdtNum, protLayerId);
    }
    break;
    case XCP_ODT_COPY_SAFE:
    default:
# endif
    {
      /* Use safe copy routine */
      dest_pu8 = Xcp_CopyOdtEntries_Safe(dest_pu8, AbsOdtNum, lastAddressPtr, lastValuePtr, protLayerId);
    }
# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
    break;
  }
# endif
#endif

  return dest_pu8;
}


#if (XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL == STD_ON)

/**
****************************************************************************************************
This function process each OdtEntry in the given ODT placing the measurement variables
into the queue using an optimized copy routine for 8-bit values.
\param[in]  dest_pu8      pointer to destination
\param[in]  AbsOdtNum     absolute ODT number
\param[in]  protLayerId   Protocol Layer ID
\return     pointer to destination after inserted data
***************************************************************************************************/
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_Appl(uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId)
{
  const Xcp_AdrPtr* OdtEntryAdrPtr;
  const uint8*      OdtEntrySizePtr;
  uint8_least       OdtEntryCnt;

  /* Initialize local pointer to OdtEntryAdr and OdtEntrySize for first OdtEntry of this ODT */
  OdtEntryAdrPtr  = &XCP_ODTENTRY_ADR(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);
  OdtEntrySizePtr = &XCP_ODTENTRY_SIZE(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);

  /* loop through all OdtEntries for this ODT */
  for (OdtEntryCnt = XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId); OdtEntryCnt > 0u; OdtEntryCnt--)
  {
    /** Start of ODT_ENTRY_FACTOR Runtime measurement **/
    XCP_RTM(0);

    /* Call Application function to copy the data from ecu memory to the destination buffer */
    XcpAppl_OdtEntryRead(dest_pu8, *OdtEntryAdrPtr, *OdtEntrySizePtr);

    /* Move pointer of the destination buffer */
    dest_pu8 += *OdtEntrySizePtr;

    /* Get next OdtEntry */
    OdtEntryAdrPtr++;
    OdtEntrySizePtr++;

    /** End of ODT_ENTRY_FACTOR Runtime measurement **/
    XCP_RTM(1);
  }

  return dest_pu8;
}

#else /* XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL */

/**
****************************************************************************************************
This function processes each OdtEntry in the given ODT placing the measurement variables into the queue.
\param[in]  dest_pu8        pointer to destination
\param[in]  AbsOdtNum       absolute ODT number
\param[in]  lastAddressPtr  pointer to last address that has been read
\param[in]  lastValuePtr    pointer to last value of that address
\param[in]  protLayerId     protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_Safe(uint8* dest_pu8, uint16 AbsOdtNum, uint32* lastAddressPtr, uint32* lastValuePtr, uint8 protLayerId)
{
  /* Local variables */
  uint32 lastReadAddress;
  uint32 lastReadValue;
  const Xcp_AdrPtr* OdtEntryAdrPtr;
  const uint8* OdtEntrySizePtr;
  uint8_least  OdtEntryCnt;
  uint32 address;
  uint8  numBytesToReadAtAddress;
  sint8  index;

  /* Copy last read address and value to local variable for faster access */
  lastReadAddress = *lastAddressPtr;
  lastReadValue   = *lastValuePtr;
  address         = lastReadAddress;

  /* Initialize local pointer to OdtEntryAdr and OdtEntrySize for first OdtEntry of this ODT */
  OdtEntryAdrPtr  = &XCP_ODTENTRY_ADR(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);
  OdtEntrySizePtr = &XCP_ODTENTRY_SIZE(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);

  /* Initialize OdtEntryCnt for first OdtEntry of this ODT */
  OdtEntryCnt = XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId);

  /* loop all OdtEntries for this ODT */
  while(OdtEntryCnt > 0u)
  {
    /** Start of ODT_ENTRY_FACTOR Runtime measurement **/
    XCP_RTM(0);
    /* Get OdtEntryAdr and OdtEntrySize */
    /* MR12 RULE 11.4 VIOLATION: The pointer is 4-byte-aligned, so casting is no problem */
    address = (uint32) (*OdtEntryAdrPtr); /* get the value (which is the address) and cast it to uint32 for further operation */
    numBytesToReadAtAddress = *OdtEntrySizePtr;

    if (lastReadAddress != (uint32) (address & (~0x3uL)))
    {
      lastReadAddress = (uint32) (address & (~0x3uL));
      /* MR12 RULE 11.4 VIOLATION: The pointer is 4-byte-aligned, so casting is no problem */
      lastReadValue = *((uint32*) lastReadAddress);
    }

    while (TRUE) /* to avoid checking for numBytesToReadAtAddress > 0 twice */
    {
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      {
        /* MR12 RULE 10.8 VIOLATION: cast to signed datatype is not a problem, as only 2 bits of an uint32 are multiplied with 8 -> result < 127 */
        index = (sint8) (8u * (3u - (address & 0x03u)));
        while ((index >= 0) && (numBytesToReadAtAddress > 0))
        {
          /** Start of SIZE_FACTOR_IFX Runtime measurement **/
          XCP_RTM(0);

          *dest_pu8 = (uint8) (lastReadValue >> (uint8) index);
          dest_pu8++;
          /* decrease bytes to copy */
          numBytesToReadAtAddress--;
          /* decrease byte pointer within address */
          index = index - 8;
          /** End of SIZE_FACTOR_IFX Runtime measurement **/
          XCP_RTM(1);
        }
      }
#else
      {
        /* MR12 RULE 10.8 VIOLATION: cast to signed datatype is not a problem, as only 2 bits of an uint32 are multiplied with 8 -> result < 127 */
        index = (sint8) (8u * ((address & 0x03u)));
        while ((index <= 24) && (numBytesToReadAtAddress > 0))
        {
          /** Start of SIZE_FACTOR_JDP Runtime measurement **/
          XCP_RTM(0);
          *dest_pu8 = (uint8) (lastReadValue >> (uint8) index);
          dest_pu8++;
          /* decrease bytes to copy */
          numBytesToReadAtAddress--;
          /* increase byte pointer within address */
          index = index + 8;
          /** End of SIZE_FACTOR_JDP Runtime measurement **/
          XCP_RTM(1);
        }
      }
#endif

      if (numBytesToReadAtAddress == 0 ) /* check if no more bytes to read in this OdtEntry */
      {
        /* Increment pointers to next OdtEntry and decrement OdtEntryCnt */
        OdtEntryAdrPtr++;
        OdtEntrySizePtr++;
        OdtEntryCnt--;
        break; /* exit while TRUE */
      }
      else /* OdtEntry is not completed */
      {
        address = (uint32) (address & (~0x3uL)) + 4u; /* increase address to read further bytes */
        /* MR12 RULE 11.4 VIOLATION: address is 4-byte-aligned, so cast is not a problem */
        lastReadValue = *((uint32*) (address)); /* fetch the value from the new address */
      } /* continue */
    }

    /** End of ODT_ENTRY_FACTOR Runtime measurement **/
    XCP_RTM(1);
  } /*End of while loop*/

  /* Update last read address and value */
  *lastAddressPtr = (uint32) (address & (~0x3uL));
  *lastValuePtr = lastReadValue;
  return dest_pu8;
}


#if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
/**
****************************************************************************************************
* The following macro is used to generate the optimized copy-routines.
*
* These functions are generated using a macro instead of writing them directly, as lots of code is
* identical and now maintainability is better (less duplicated code vs. preprocessor-code).
*
* Also it is not possible to use function-pointers for the copy-routine itself as this would lead
* to a function-call for the copy routine (Xcp_MemCopy...) whereas now the function can be inlined.
***************************************************************************************************/
#define GEN_OPTIMIZED_COPY_FUNCTION(size)                                                                     \
LOCAL_INLINE uint8* Xcp_CopyOdtEntries_##size(uint8* dest_pu8, uint16 AbsOdtNum, uint8 protLayerId)           \
{                                                                                                             \
  const Xcp_AdrPtr* OdtEntryAdrPtr;                                                                           \
  const uint8*      OdtEntrySizePtr;                                                                          \
                                                                                                              \
  uint8_least OdtEntryCnt;                                                                                    \
                                                                                                              \
  /* Initialize local pointer to OdtEntryAdr and OdtEntrySize for first OdtEntry of this ODT */               \
  OdtEntryAdrPtr  = &XCP_ODTENTRY_ADR(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);            \
  OdtEntrySizePtr = &XCP_ODTENTRY_SIZE(XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId), protLayerId);           \
                                                                                                              \
  /* loop through all OdtEntries for this ODT */                                                              \
  for (OdtEntryCnt = XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId); OdtEntryCnt > 0u; OdtEntryCnt--)            \
  {                                                                                                           \
    /** Start of ODT_ENTRY_FACTOR Runtime measurement **/                                                     \
    XCP_RTM(0);                                                                                               \
                                                                                                              \
    /* Copy the OdtEntry-Data into the destination buffer */                                                  \
    /* MR12 RULE 11.5, 1.1 VIOLATION: The calling layers ensure correct alignment; Cast to const is no problem, as the variable is only read  \
                                      DIR 1.1: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */ \
    Xcp_MemCopy##size((uint##size *)(void *)dest_pu8, (const uint##size *)(void *)*OdtEntryAdrPtr, (uint32)*OdtEntrySizePtr);  \
                                                                                                              \
    /* Move pointer of the destination buffer */                                                              \
    dest_pu8 += *OdtEntrySizePtr;                                                                             \
                                                                                                              \
    /* Get next OdtEntry */                                                                                   \
    OdtEntryAdrPtr++;                                                                                         \
    OdtEntrySizePtr++;                                                                                        \
                                                                                                              \
    /** End of ODT_ENTRY_FACTOR Runtime measurement **/                                                       \
    XCP_RTM(1);                                                                                               \
  }                                                                                                           \
                                                                                                              \
  return dest_pu8;                                                                                            \
}


/**
****************************************************************************************************
This function process each OdtEntry in the given ODT placing the measurement variables
into the queue using an optimized copy routine for 32-bit values.
\param[in]  dest_pu8      pointer to destination
\param[in]  AbsOdtNum     absolute ODT number
\param[in]  protLayerId   protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
/* MR12 RULE 11.5, 1.1 VIOLATION: Xcp_MemCopy*: The calling layers ensure correct alignment; Cast to const is no problem, as the variable is only read */  \
GEN_OPTIMIZED_COPY_FUNCTION(32)


/**
****************************************************************************************************
This function process each OdtEntry in the given ODT placing the measurement variables
into the queue using an optimized copy routine for 16-bit values.
\param[in]  dest_pu8      pointer to destination
\param[in]  AbsOdtNum     absolute ODT number
\param[in]  protLayerId   protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
/* MR12 RULE 11.5, 1.1 VIOLATION: Xcp_MemCopy*: The calling layers ensure correct alignment; Cast to const is no problem, as the variable is only read */  \
GEN_OPTIMIZED_COPY_FUNCTION(16)


/**
****************************************************************************************************
This function process each OdtEntry in the given ODT placing the measurement variables
into the queue using an optimized copy routine for 8-bit values.
\param[in]  dest_pu8      pointer to destination
\param[in]  AbsOdtNum     absolute ODT number
\param[in]  protLayerId   protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
/* MR12 RULE 11.5, 1.1 VIOLATION: Xcp_MemCopy*: The calling layers ensure correct alignment; Cast to const is no problem, as the variable is only read */  \
GEN_OPTIMIZED_COPY_FUNCTION(8)

#endif /* XCP_OM_ODT_OPTIMIZATION_ENABLED */

#endif /* XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL */

/**
****************************************************************************************************
This function will write the id field at the given destination. The information, how many
bytes shall be written, will be read out of the protocol layer structure.
\param[in]  dest_pu8      pointer to destination
\param[in]  AbsOdtNum     absolute ODT number
\param[in]  daqListNo     DaqList
\param[in]  protLayerId   protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
LOCAL_INLINE uint8* Xcp_PutIdField(uint8* dest_pu8, uint16 AbsOdtNum, uint16 daqListNo, uint8 protLayerId)
{
#if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
  /* Local variables */
  Xcp_IdField_t IdFieldType_en;

  IdFieldType_en = Xcp_NoInit[protLayerId].Session.IdFieldType_en;

  if (IdFieldType_en == XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE)
  {
#endif
    /* when ID Field Type is absolute, AbsOdtNum is smaller than 256 */
    *dest_pu8 = (uint8) AbsOdtNum;
    /* to point to next byte in the buffer */
    dest_pu8++;
#if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
  }
  else /* not XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE */
  {
    *dest_pu8 = (uint8) Xcp_Daq_GetRelOdtNum(daqListNo, AbsOdtNum, protLayerId);
    dest_pu8++;

    /* add fill byte only if ID Field Type is word aligned */
    if (IdFieldType_en == XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_WORD_ALIGNED)
    {
      *dest_pu8 = 0; /* fill byte */
      dest_pu8++;
    }
    else
    {
      /* no else */
    }
# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* fetch low byte of absolute DaqList number */
    *dest_pu8 = (uint8) (daqListNo >> 8u);
    dest_pu8++;

    if (IdFieldType_en != XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_BYTE)
    {
      /* fetch high byte of absolute DaqList number */
      *dest_pu8 = (uint8) daqListNo;
      dest_pu8++;
    }
# else /* CPU_BYTE_ORDER != HIGH_BYTE_FIRST */
    /* fetch low byte of absolute DaqList number */
    *dest_pu8 = (uint8)daqListNo;
    dest_pu8++;

    if (IdFieldType_en != XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_BYTE)
    {
      /* fetch high byte of absolute DaqList number */
      *dest_pu8 = (uint8)(daqListNo >> 8u);
      dest_pu8++;
    }
# endif /* CPU_BYTE_ORDER */
  }
#else
  XCP_PARAM_UNUSED(daqListNo);
  XCP_PARAM_UNUSED(protLayerId);
#endif /* XCP_IDFIELD_OTHER_THAN_ABSOLUTE */

  return dest_pu8;
}


#if (XCP_TIMESTAMP == STD_ON)
/**
****************************************************************************************************
This function will write the actual timestamp at the given destination. The information, how many
bytes shall be written, will be read out of the protocol layer structure.
\param[in]  dest_pu8      pointer to destination
\param[in]  protLayerId   protocol layer id
\return     pointer to destination after inserted data
***************************************************************************************************/
LOCAL_INLINE uint8* Xcp_PutTimestamp(uint8* dest_pu8, uint8 protLayerId)
{
  /* Local variables */
  uint32 timestamp;
  sint8  i;

  timestamp = XcpAppl_GetTimestamp(); /* get timestamp */

# if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* Cast to sint8 is no problem as the enum will never have more the 127 entries */
  for (i = ((sint8) Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en - 1); i >= 0; i--)
# else /* LOW_BYTE_FIRST */
  for (i = 0; i < (uint8) Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en; i++)
# endif
  {
    /* put single bytes from timestamp */
    *dest_pu8 = (uint8) (timestamp >> ((uint8)i*8));
    dest_pu8++; /* increment destination pointer */
  }

  return dest_pu8; /* return pointer to next available buffer */
}
#endif


/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

#endif


