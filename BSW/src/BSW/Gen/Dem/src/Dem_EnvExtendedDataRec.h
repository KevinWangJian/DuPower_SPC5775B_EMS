


#ifndef DEM_ENVEXTENDEDDATAREC_H
#define DEM_ENVEXTENDEDDATAREC_H


#include "Dem_Types.h"
#include "Dem_EnvDataElement.h"
#include "Dem_Cfg_EnvExtendedDataRec.h"
#include "Dem_InternalEnvData.h"
#include "Dem_EnvTrigger.h"

typedef struct
{
   uint8 recordNumber;
   Dem_TriggerType trigger;
   boolean update;
   uint16 dataElementIndex;
} Dem_EnvExtDataRec;

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const uint8 Dem_Cfg_EnvExtData2DataElement[];
extern const Dem_EnvExtDataRec Dem_Cfg_EnvExtDataRec[DEM_CFG_ENVEXTDATAREC_ARRAYLENGTH];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_INLINE uint8 Dem_EnvEDRGetRecordNumber (uint8 extDataRecId)
{
   return Dem_Cfg_EnvExtDataRec[extDataRecId].recordNumber;
}

DEM_INLINE boolean Dem_EnvEDRGetUpdate (uint8 extDataRecId)
{
   return Dem_Cfg_EnvExtDataRec[extDataRecId].update;
}


DEM_INLINE Dem_TriggerType Dem_EnvEDRGetRecordTrigger (uint8 extDataRecId)
{
   return Dem_Cfg_EnvExtDataRec[extDataRecId].trigger;
}

DEM_INLINE void Dem_EnvEDRCapture (uint8 extDataRecId, uint8** start, const uint8* end, const Dem_InternalEnvData* internalEnvData)
{
   uint32 i;
   for (i = Dem_Cfg_EnvExtDataRec[extDataRecId-1].dataElementIndex;
        i < Dem_Cfg_EnvExtDataRec[extDataRecId].dataElementIndex;
        i++)
   {
      Dem_EnvDACapture(Dem_Cfg_EnvExtData2DataElement[i], start, end, internalEnvData);
   }
}



/* MR12 RULE 8.13 VIOLATION: parameter src not made const, as it is modified in subfunction */
DEM_INLINE void Dem_EnvEDRCopyRaw (uint8 extDataRecId, uint8** start, const uint8* end, const uint8** src, Dem_EnvTriggerParamType* triggerParam)
{
	uint32 i;
	Dem_TriggerType trigger;
	boolean update;

	/* Extended Data Record will be modified if
	 * 1. Trigger is set for this Extended Data Record
	 *    and
	 * 2. Trigger is set for this Extended Data Record the first time or Update is configured
	 */

	trigger = Dem_EnvEDRGetRecordTrigger(extDataRecId);
	update  = Dem_EnvEDRGetUpdate(extDataRecId);

	if ( (Dem_EnvIsTriggerSet(triggerParam->currentTrigger,trigger) &&
		(!Dem_EnvIsTriggerSet(triggerParam->storedTrigger, trigger) || update))

	    || (Dem_EnvIsTriggerSet(Dem_GetSmallerTrigger(triggerParam->currentTrigger),trigger) &&
	            (!Dem_EnvIsTriggerSet(triggerParam->storedTrigger, trigger))))

	{
		Dem_EnvSetTrigger(&triggerParam->matchingTrigger, trigger);
		for (i = Dem_Cfg_EnvExtDataRec[extDataRecId-1].dataElementIndex;
				i < Dem_Cfg_EnvExtDataRec[extDataRecId].dataElementIndex;
				i++)
		{
			Dem_EnvDACopy(Dem_Cfg_EnvExtData2DataElement[i], start, end, src);
		}
	}
	else
	{
		for (i = Dem_Cfg_EnvExtDataRec[extDataRecId-1].dataElementIndex;
				i < Dem_Cfg_EnvExtDataRec[extDataRecId].dataElementIndex;
				i++)
		{
			Dem_EnvDASkip(Dem_Cfg_EnvExtData2DataElement[i], start, end, src);
		}
	}
}



/* MR12 RULE 8.13 VIOLATION: parameter src not made const, as it is modified in subfunction */
DEM_INLINE Dem_boolean_least Dem_EnvEDRRetrieve (uint8 extDataRecId, uint8** start, const uint8* end, const uint8** const src, const Dem_InternalEnvData* internalEnvData)
{
   uint32 i;
   for (i = Dem_Cfg_EnvExtDataRec[extDataRecId-1].dataElementIndex;
        i < Dem_Cfg_EnvExtDataRec[extDataRecId].dataElementIndex;
        i++)
   {
      if (!Dem_EnvDARetrieve(Dem_Cfg_EnvExtData2DataElement[i], start, end, src, internalEnvData))
      {
         return FALSE;
      }
   }
   return TRUE;
}


DEM_INLINE uint16 Dem_EnvEDRGetSize (uint8 extDataRecId)
{
   uint32 i;
   uint16 byteSize = 0;
   for (i = Dem_Cfg_EnvExtDataRec[extDataRecId-1].dataElementIndex;
        i < Dem_Cfg_EnvExtDataRec[extDataRecId].dataElementIndex;
        i++)
   {
      byteSize += Dem_EnvDAGetSizeOf(Dem_Cfg_EnvExtData2DataElement[i]);
   }
   return byteSize;
}


DEM_INLINE void Dem_EnvEDRSkipSrc (uint8 extDataRecId, const uint8** src)
{
	*src += Dem_EnvEDRGetSize(extDataRecId);
}
#endif

