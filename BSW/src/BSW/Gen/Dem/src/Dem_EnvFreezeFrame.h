
#ifndef DEM_ENVFREEZEFRAME_H
#define DEM_ENVFREEZEFRAME_H

#include "Dem_Types.h"

#include "Dem_EnvDid.h"
#include "Dem_Cfg_EnvFreezeFrame.h"
#include "Dem_Cfg_Main.h"


typedef struct
{
	uint16 didIndex;
	uint16 rawByteSize;
} Dem_EnvFreezeFrame;
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const uint8 Dem_Cfg_EnvFreezeFrame2Did[];
DEM_ARRAY_DECLARE_CONST(Dem_EnvFreezeFrame, Dem_Cfg_EnvFreezeFrame, DEM_CFG_ENVFREEZEFRAME_ARRAYLENGTH);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


DEM_INLINE void Dem_EnvFFCapture(uint8 freezeFrameId, uint8* buffer, uint16 size, const Dem_InternalEnvData* internalEnvData)
{
	uint32 i;
	uint8* end = buffer + size;

	for (i = Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex; i < Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex; i++)
	{
		Dem_EnvDIDCapture (Dem_Cfg_EnvFreezeFrame2Did[i], &buffer, end, internalEnvData);
	}

#if (DEM_CFG_BUILDTARGET==DEM_CFG_BUILDTARGET_DEMTESTSUITE)
	DEM_MEMSET(buffer,0xFF,end-buffer);
#endif
}

DEM_INLINE uint16 Dem_EnvFFGetRawByteSize(uint8 freezeFrameId)
{
	return Dem_Cfg_EnvFreezeFrame[freezeFrameId].rawByteSize;
}

DEM_INLINE Dem_ReturnGetFreezeFrameDataByDTCType Dem_EnvFFRetrieve(uint8 freezeFrameId,
		uint8 RecNum,
		uint8* dest,
		uint16* bufsize,
		const uint8* src,
		const Dem_InternalEnvData* internalEnvData)
{
	uint8* writepos = dest;
	uint8* end = dest + *bufsize;
	uint16_least i;

	if (*bufsize < 2)
	{
		return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
	}

	*writepos = RecNum;
	writepos++;

	*writepos = (uint8)(Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex - Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex);
	writepos++;

	for (i = Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex; i < Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex; i++)
	{
		if (!Dem_EnvDIDRetrieve (Dem_Cfg_EnvFreezeFrame2Did[i], &writepos, end, &src, internalEnvData))
		{
			return DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE;
		}
	}

	*bufsize = (uint16)(writepos - dest); /* current writing position - starting writing position */
	return DEM_GET_FFDATABYDTC_OK;
}

DEM_INLINE Dem_ReturnGetSizeOfFreezeFrameByDTCType Dem_EnvFFGetSize(uint8 freezeFrameId, uint16* size)
{
	uint16_least i;
	*size = 2;

	for (i = Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex; i < Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex; i++)
	{
		*size += (Dem_EnvDIDGetSize (Dem_Cfg_EnvFreezeFrame2Did[i]));
	}

	return DEM_GET_SIZEOFFF_OK;
}

DEM_INLINE void Dem_EnvFFRetrieveRaw(uint8 freezeFrameId, uint8* dest, uint16* bufsize, const uint8* src, const Dem_InternalEnvData *internalEnvData)
{
	uint8* writepos = dest;
	uint8* end = dest + *bufsize;
	uint16_least i;

	for (i = Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex; i < Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex; i++)
	{
		(void)Dem_EnvDIDRetrieveRaw (Dem_Cfg_EnvFreezeFrame2Did[i], &writepos, end, &src, internalEnvData);
	}

	*bufsize = (uint16)(writepos - dest); /* current writing position - starting writing position */
}

DEM_INLINE Dem_boolean_least Dem_EnvFFRetrieveDid(uint8 freezeFrameId,
		uint8* dest,
		uint16* bufsize,
		uint16 did,
		const uint8* src,
		const Dem_InternalEnvData* internalEnvData)
{
	uint8* writepos = dest;
	uint8* end = dest + *bufsize;
	uint16_least i;

	for (i = Dem_Cfg_EnvFreezeFrame[freezeFrameId - 1].didIndex; i < Dem_Cfg_EnvFreezeFrame[freezeFrameId].didIndex; i++)
	{
		if (Dem_EnvDIDRetrieveSpecificDid (Dem_Cfg_EnvFreezeFrame2Did[i], did, &writepos, end, &src, internalEnvData))
		{
			*bufsize = (uint16)(writepos - dest); /* current writing position - starting writing position */
			return TRUE;
		}
	}

	*bufsize = 0;
	return FALSE;
}

DEM_INLINE void Dem_EnvFFCopyRaw(uint8 freezeFrameId, uint8* dest, uint16 bufsize, const uint8* src)
{
	const uint16 bytesize = Dem_Cfg_EnvFreezeFrame[freezeFrameId].rawByteSize;

	DEM_ASSERT(bytesize <= bufsize, DEM_DET_APIID_ENVFFCOPYRAW, 0);
	DEM_MEMCPY (dest, src, bytesize);
}

#endif
