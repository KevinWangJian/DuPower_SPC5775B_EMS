

#include "Dem_Dcm.h"

#include "Dem_DTCGroup.h"

#include "Dem_DTCs.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DEFINE_CONST(Dem_DtcGroupParam, Dem_AllDTCGroupsParam, DEM_DTCGROUPID_ARRAYLENGTH, DEM_CFG_DTCGROUPPARAMS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


/*-- DTC GROUP CODE-------------------------------------------------------------*/


DEM_INLINE void Dem_DtcGroupApplyDTCSetting(Dem_DTCGroupType DTCGroup, uint8 groupId, boolean newDtcSettingState)
{

	Dem_DtcIdListIterator dtcIt;

	if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
	{
		for (Dem_DtcIdListIteratorNewFromDtcGroup(&dtcIt, groupId);
				Dem_DtcIdListIteratorIsValid(&dtcIt);
				Dem_DtcIdListIteratorNext(&dtcIt))
		{
			Dem_DtcSetDTCSetting(Dem_DtcIdListIteratorCurrent(&dtcIt), newDtcSettingState);
		}
	}
	else
	{
		Dem_DtcIdIterator dtcId = DEM_DTCIDITERATOR_NEW();
		/*
		 * looping through all DTCs and if DTCKind configured as DEM_DTC_KIND_EMISSION_REL_DTCS(OBD-relevant DTCs) shall be enabled or disabled.
		 * DTCgroup iterator function shall not be considered here because zeroth index is considered as INVALID
		 * and DEM_DTC_GROUP_EMISSION_REL_DTCS(0x000000) is not from configuration.
		 */
		for (Dem_DtcIdIteratorNew(&dtcId); Dem_DtcIdIteratorIsValid(&dtcId);Dem_DtcIdIteratorNext(&dtcId))
		{
			if(Dem_DtcGetKind(Dem_DtcIdIteratorCurrent(&dtcId)) == DEM_DTC_KIND_EMISSION_REL_DTCS)
			{
				Dem_DtcSetDTCSetting(Dem_DtcIdIteratorCurrent(&dtcId), newDtcSettingState);
			}
		}
	}
}
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
Dem_DTCGroupIdType Dem_DtcGroupIdFromDtcGroupCode (Dem_DTCGroupType dtcGrpCode)
{
   Dem_DtcGroupIdIterator dtcGroupId;

   for (Dem_DtcGroupIdIteratorNew(&dtcGroupId);
        Dem_DtcGroupIdIteratorIsValid(&dtcGroupId);
        Dem_DtcGroupIdIteratorNext(&dtcGroupId))
   {
      if (Dem_DtcGroupGetCode(Dem_DtcGroupIdIteratorCurrent(&dtcGroupId)) == dtcGrpCode)
      {
         return Dem_DtcGroupIdIteratorCurrent(&dtcGroupId);
      }
   }
   return DEM_DTCGROUPID_INVALID;
}

Dem_ReturnControlDTCSettingType Dem_EnableDTCSetting (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind)
{

	Dem_DTCGroupIdType DtcGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTCGroup);
	DEM_UNUSED_PARAM(DTCKind);

	/* Validate the DTCGroupcode when OBD project is enabled or Disabled */
	if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
	{
		if(!Dem_DtcGroupIdIsValid(DtcGroupId))
		{
			return DEM_CONTROL_DTC_WRONG_DTCGROUP;
		}
	}

/* FC_VariationPoint_START */
#if(DEM_CFG_OBD == DEM_CFG_OBD_OFF)
/* FC_VariationPoint_END */
	{
		if(DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS)
		{
			return DEM_CONTROL_DTC_WRONG_DTCGROUP;
		}
	}
/* FC_VariationPoint_START */
#endif
/* FC_VariationPoint_END */

	Dem_DtcGroupApplyDTCSetting(DTCGroup, DtcGroupId, DEM_DTC_SETTING_ENABLED);

	return DEM_CONTROL_DTC_SETTING_OK;
}

Dem_ReturnControlDTCSettingType Dem_DisableDTCSetting (Dem_DTCGroupType DTCGroup, Dem_DTCKindType DTCKind)
{


	Dem_DTCGroupIdType DtcGroupId = Dem_DtcGroupIdFromDtcGroupCode(DTCGroup);
	DEM_UNUSED_PARAM(DTCKind);

	/* Validate the DTCGroupcode when OBD project is enabled or Disabled */
	if(DTCGroup != DEM_DTC_GROUP_EMISSION_REL_DTCS)
	{
		if(!Dem_DtcGroupIdIsValid(DtcGroupId))
		{
			return DEM_CONTROL_DTC_WRONG_DTCGROUP;
		}
	}

/* FC_VariationPoint_START */
#if(DEM_CFG_OBD == DEM_CFG_OBD_OFF)
/* FC_VariationPoint_END */
	{
		if(DTCGroup == DEM_DTC_GROUP_EMISSION_REL_DTCS)
		{
			return DEM_CONTROL_DTC_WRONG_DTCGROUP;
		}
	}
/* FC_VariationPoint_START */
#endif
/* FC_VariationPoint_END */

	Dem_DtcGroupApplyDTCSetting(DTCGroup, DtcGroupId, DEM_DTC_SETTING_DISABLED);

	return DEM_CONTROL_DTC_SETTING_OK;
}


void Dem_DtcsClearDtcInGroup(uint8 GroupId, Dem_DTCOriginType DTCOrigin, Dem_ClientClearMachineType *Dem_ClientClearMachinePtr)
{
    Dem_DtcIdType dtcId;

    /* Check whether the Clear is requested newly */
    if (Dem_ClientClearMachinePtr->IsNewClearRequest)
    {
        Dem_DtcIdListIteratorNewFromDtcGroup(&(Dem_ClientClearMachinePtr->DtcIt), GroupId);
    }

    while (Dem_DtcIdListIteratorIsValid(&(Dem_ClientClearMachinePtr->DtcIt)))
    {
        dtcId = Dem_DtcIdListIteratorCurrent(&(Dem_ClientClearMachinePtr->DtcIt));
        Dem_ClearSingleDTC(dtcId, DTCOrigin, Dem_ClientClearMachinePtr);
        /* Check whether the number of events processed reached the Max limit */
        if (Dem_ClientClearMachinePtr->IsClearInterrupted)
        {
            return;
        }
        Dem_DtcIdListIteratorNext(&(Dem_ClientClearMachinePtr->DtcIt));
    }
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
