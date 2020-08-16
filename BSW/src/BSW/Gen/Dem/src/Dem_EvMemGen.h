

#ifndef DEM_EVMEMGEN_H
#define DEM_EVMEMGEN_H

#include "Dem_EvMemGenTypes.h"
#include "Dem_EvMemTypes.h"
#include "Dem_EvMemBase.h"
#include "Dem_DTCs.h"
#include "Dem_GenericNvData.h"


#define DEM_EVMEMGEN_MEMORY_BASE   Dem_GenericNvData

#if DEM_CFG_EVMEMGENERIC_SUPPORTED
   #define DEM_EVMEMGEN_GET(OBJ)      (OBJ)
   #define DEM_EVMEMGEN_SET(OBJ,VAL)  (OBJ) = (VAL)
   #define DEM_EVMEMGEN_CLEAROBJ(OBJ) DEM_EVMEM_CLEAROBJ(OBJ)
#else
   #define DEM_EVMEMGEN_GET(OBJ)      0
   #define DEM_EVMEMGEN_SET(OBJ,VAL)  do {} while (0)
   #define DEM_EVMEMGEN_CLEAROBJ(OBJ) do {} while (0)
#endif

/* -------------------------------------------------
   service Dem_GetDTCByOccurrenceTime
   -------------------------------------------------
 */

/* Get stored DtcId by occurrence */
DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetDtcIdByOccIndex(uint32 OccIndex)
{
   return DEM_EVMEMGEN_GET(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime[OccIndex]);
}

/* Set stored DtcId by occurrence */
DEM_INLINE void Dem_EvMemGenSetDtcByOccIndex(Dem_DtcIdType DtcId,uint32 OccIndex)
{
   DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime[OccIndex],DtcId);
}

/* Translates MemId to DtcOrigin  */
DEM_INLINE Dem_DTCOriginType Dem_EvMemGenGetDtcOrginFromMemId(uint16_least MemId)
{
   Dem_DTCOriginType DtcOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;

   if (Dem_LibGetParamBool(DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED))
   {
      if (MemId == DEM_CFG_EVMEM_MEMID_SECONDARY)
      {
         DtcOrigin = DEM_DTC_ORIGIN_SECONDARY_MEMORY;
      }
   }

   if (Dem_LibGetParamBool(DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED))
   {

      if (MemId == DEM_CFG_EVMEM_MEMID_MIRROR)
      {
         DtcOrigin = DEM_DTC_ORIGIN_MIRROR_MEMORY;
      }
   }

   return DtcOrigin;

}

/* Report event prototype function */
DEM_INLINE void Dem_EvMemGenReportEvent(Dem_EventIdType EventId, uint32 FirstOccIndex, uint32 RecntOccIndex)
{
   Dem_DtcIdType DtcId;

   /* get the DtcId of the reported event */
   DtcId = Dem_DtcIdFromEventId (EventId);
   /* Is the DtcId valid ? */
   if (Dem_isDtcIdValid (DtcId))
   {
      /* Is stored DtcId of First Entry is invalid ? */
      /* HINT: the initial value is zero and therefore invalid! */
      if (!Dem_isDtcIdValid(Dem_EvMemGenGetDtcIdByOccIndex(FirstOccIndex)))
      {
         /* replace first entry */
         Dem_EvMemGenSetDtcByOccIndex(DtcId,FirstOccIndex);
         /* notify to store in NVM */
         Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
      }
      /* Is stored DtcId of Most Recent Entry is not yet stored ? */
      if (Dem_EvMemGenGetDtcIdByOccIndex(RecntOccIndex) != DtcId)
      {
         /* replace most recent entry */
         Dem_EvMemGenSetDtcByOccIndex(DtcId,RecntOccIndex);
         /* notify to store in NVM */
         Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
      }
   }
}

/* report function to report failed events */
DEM_INLINE void Dem_EvMemGenReportFailedEvent(Dem_EventIdType EventId)
{
	if(!Dem_GetEvMemLockInternal())
	{
	    /* service Dem_GetDTCByOccurrenceTime has implicit origin DEM_DTC_ORIGIN_PRIMARY_MEMORY */
	    if ( Dem_EvtIsDestPrimaryMemory(EventId) )
	    {
	        /* call prototype function with first and recent FAILED indices */
	        /* This call needs to be locked to avoid a simultaneous access in the Dem_Main task */
	        DEM_ENTERLOCK_MON();
	        Dem_EvMemGenReportEvent(EventId,DEM_FIRST_FAILED_DTC,DEM_MOST_RECENT_FAILED_DTC);
	        DEM_EXITLOCK_MON();
	    }
	}
}

/* report function to report confirmed events */
DEM_INLINE void Dem_EvMemGenReportConfirmedEvent(Dem_EventIdType EventId, uint16_least MemId)
{
   /* service Dem_GetDTCByOccurrenceTime has implicit origin DEM_DTC_ORIGIN_PRIMARY_MEMORY */
   if (MemId == DEM_CFG_EVMEM_MEMID_PRIMARY)
   {
      /* call prototype function with first and recent CONFIRMED indices */
      Dem_EvMemGenReportEvent(EventId,DEM_FIRST_DET_CONFIRMED_DTC,DEM_MOST_REC_DET_CONFIRMED_DTC);
   }
}

/* clears the DTC Occurrence Entries */
DEM_INLINE void Dem_EvMemGenClearDtcByOccurrenceTime(Dem_DTCOriginType DtcOrigin)
{
   DEM_UNUSED_PARAM(DtcOrigin);

   if (DtcOrigin == DEM_DTC_ORIGIN_PRIMARY_MEMORY)
   {
       /* This call needs to be locked to avoid a simultaneous access in SetEventStatus context */
      DEM_ENTERLOCK_MON();
      DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
      DEM_EXITLOCK_MON();
      /* notify to store in NVM */
      Dem_NvMClearBlockByWrite(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
   }
}

/* ------------------------------------------------------
  Service to get the Last failed and Last Confirmed DTCs
   -----------------------------------------------------
 */
/* Get the Last Failed DTC */
DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetLastFailedDtcFromGenNvData(void)
{
	return Dem_EvMemGenGetDtcIdByOccIndex(DEM_MOST_RECENT_FAILED_DTC);
}

/* Get the Last Confirmed DTCs */
DEM_INLINE Dem_DtcIdType Dem_EvMemGenGetLastConfirmedDtcFromGenNvData(void)
{
	return Dem_EvMemGenGetDtcIdByOccIndex(DEM_MOST_REC_DET_CONFIRMED_DTC);
}

/* -------------------------------------------------
   service Dem_GetEventMemoryOverflow
   -------------------------------------------------
 */

/* sets the memory overflow indicator */
DEM_INLINE void Dem_EvMemGenSetOverflow(Dem_DTCOriginType DtcOrigin)
{
   DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin],TRUE);
}

/* gets the overflow indicator */
DEM_INLINE boolean Dem_EvMemGenIsOverflow(Dem_DTCOriginType DtcOrigin)
{
   return DEM_EVMEMGEN_GET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin]);
}

/* reports overflow indication */
DEM_INLINE void Dem_EvMemGenReportEventMemoryOverflowByOrigin(Dem_DTCOriginType DtcOrigin)
{
   if (!Dem_EvMemGenIsOverflow(DtcOrigin))
   {
      Dem_EvMemGenSetOverflow(DtcOrigin);
      Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
   }
}

/* clears the memory overflow indicator */
DEM_INLINE void Dem_EvMemGenClearOverflow(Dem_DTCOriginType DtcOrigin)
{
   DEM_EVMEMGEN_SET(DEM_EVMEMGEN_MEMORY_BASE.Overflow[DtcOrigin],FALSE);
   Dem_NvMClearBlockByWrite(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
}

/* -------------------------------------------------
   common init
   -------------------------------------------------
 */

DEM_INLINE void Dem_EvMemGenInitEventMemoryGen(void)
{
    Dem_NvmResultType NvmResult;

    if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
    {
        /* Zero the content of the record */
        DEM_MEMSET(&Dem_GenericNvData, 0x00, sizeof(Dem_GenericNvDataType));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
    }
    else
    {
        /* get the Result of the NvM-Read (NvM_ReadAll) */
        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_DEM_GENERIC_NV_DATA);

        /* data Erased or Initial? */
        if (NvmResult == DEM_NVM_INVALID)
        {
            /* data init but no NVM storage! */
            DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
        }

        /* data successfull read ? */
        if (NvmResult == DEM_NVM_SUCCESS)
        {
            uint32 idx;
            /* check all entries */
            for (idx = 0; idx < DEM_EVMEMGEN_DTCIDS_BY_OCCURRENCE_TIME_ARRAYSIZE; idx++)
            {  /* DtcId needs to be valid or explicit DEM_DTCID_INVALID (zero) */
                if (!(Dem_isDtcIdValid(Dem_EvMemGenGetDtcIdByOccIndex(idx)) ||
                        (Dem_EvMemGenGetDtcIdByOccIndex(idx) == DEM_DTCID_INVALID)))
                {  /* mark as Failed */
                    NvmResult = DEM_NVM_FAILED;
                }
            }
        }

        /* re-initialize ? */
        if ((NvmResult != DEM_NVM_SUCCESS) && (NvmResult != DEM_NVM_INVALID))
        {
            /* data init but AND NVM storage! */
            DEM_EVMEMGEN_CLEAROBJ(DEM_EVMEMGEN_MEMORY_BASE.DtcIdsByOccurrenceTime);
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
        }
    }

}

#endif
