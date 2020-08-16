

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_EvMemGen.h"

#include "Dem_Main.h"

/* -------------------------------------------------
   service Dem_GetDTCByOccurrenceTime
   -------------------------------------------------
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#if ( DEM_CFG_EVMEMGENERIC_SUPPORTED != FALSE )
Dem_ReturnGetDTCByOccurrenceTimeType Dem_GetDTCByOccurrenceTime(Dem_DTCRequestType DTCRequest, Dem_DTCKindType DTCKind, uint32* DTC)
{
      Dem_DtcIdType DtcId;

      /* is DEM Initialized ?*/
      if (!Dem_OpMoIsInitialized())
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_UNINIT);
         return DEM_OCCURR_FAILED;
      }
      /* parameter check: DTCRequest */
      if ((DTCRequest != DEM_FIRST_FAILED_DTC) &&
            (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) &&
            (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC) &&
            (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC))
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION);
         return DEM_OCCURR_FAILED;
      }
      if (DTC==NULL_PTR)
      {
          return DEM_OCCURR_FAILED;
      }

      /* parameter check: DTCKind */
      if (DTCKind != DEM_DTC_KIND_ALL_DTCS)
      {
         DEM_DET(DEM_DET_APIID_GETDTCBYOCCURRENCETIME, DEM_E_WRONG_CONFIGURATION);
         return DEM_OCCURR_WRONG_DTCKIND;
      }
      /* get the stored DtcId matching the DTCRequest */
      DtcId = Dem_EvMemGenGetDtcIdByOccIndex(DTCRequest);

      /* Is DtcId valid ?*/
      if (!Dem_isDtcIdValid(DtcId))
      {   /* No DTC is stored */
         return DEM_OCCURR_FAILED;
      }

      /* get the DTC code */
      *DTC = (uint32)Dem_DtcGetCode(DtcId);
      return DEM_OCCURR_OK;
   }
#endif

/* -------------------------------------------------
   service Dem_GetEventMemoryOverflow
   -------------------------------------------------
 */
Std_ReturnType Dem_GetEventMemoryOverflow(Dem_DTCOriginType DTCOrigin, boolean* OverflowIndication)
{

   if (Dem_LibGetParamBool(DEM_CFG_EVMEMGENERIC_SUPPORTED))
   {

       /*   Entry Condition Check   */
       DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);
       DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(OverflowIndication,DEM_DET_APIID_GETEVENTMEMORYOVERFLOW,E_NOT_OK);
      /* parameter check: DTCOrigin */
      if (!Dem_EvMemIsDtcOriginValid (&DTCOrigin))
      {
         DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONFIGURATION);
         return E_NOT_OK;
      }

      /* get the stored overflow indicator matching the DTCOrigin */
      *OverflowIndication = Dem_EvMemGenIsOverflow(DTCOrigin);
      return E_OK;
   }
   else
   {
	   DEM_DET(DEM_DET_APIID_GETEVENTMEMORYOVERFLOW, DEM_E_WRONG_CONDITION);
	   return E_NOT_OK;
   }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

