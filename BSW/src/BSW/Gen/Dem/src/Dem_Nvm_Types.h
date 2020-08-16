 


#ifndef DEM_NVM_TYPES_H
#define DEM_NVM_TYPES_H

#include "Dem_Cfg_Nvm.h"
#include "Dem_Types.h"
#include "Dem_EvMemTypes.h"
#include "Dem_GenericNvData.h"
#include "Nvm.h"
#include "Dem_Bfm.h"

typedef DEM_NVM_CFG_BLOCKID_TYPE Dem_NvmBlockIdType;

typedef union
{
    Dem_EvMemEventMemoryType evMemData;
    Dem_GenericNvDataType genericNvData;
    /* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_PdtcMemType obdPdtcMemData[DEM_CFG_PERMANENT_MEMORY_SIZE];
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
    rba_DemBfm_Record bfmRecord;
#if(RBA_DEMBFM_EXTENDED_DEBUG_DATA_SUPPORTED == DEM_BFM_ON)
    rba_DemBfm_ExtendedDebugDataRecord bfmExtDbgDataRecord;
#endif
    rba_DemBfm_RecordManagementDataNvm bfmManagementData;
#if (RBA_DEMBFM_COUNTER_IN_NVM_ENABLED == DEM_BFM_ON)
    rba_DemBfm_CounterNvm bfmCounterData;
#endif
#endif
    /* FC_VariationPoint_END */

} Dem_NvMStorageBufferData;


typedef void (*Dem_NvmCopyFunction) (void *destination, const void* source, uint32 size);


typedef struct
{
    Dem_NvmBlockIdType id;
    Dem_NvMStorageBufferData data;
    boolean busy;
} Dem_NvMStorageBufferType;


typedef struct
{
    void* ramAdress;
    uint8 nvmBlockSize;
    uint8 copyFunctionPointerIndex;
} Dem_NvmBlockIdExtendedType;


typedef uint8 Dem_NvmBlockStatusType;
#define DEM_NVM_STATUSBITMASK_NONE                  0x00u
#define DEM_NVM_STATUSBITMASK_SHUTDOWN              0x01u
#define DEM_NVM_STATUSBITMASK_IMMEDIATE             0x02u
#define DEM_NVM_STATUSBITMASK_IMMEDIATE_REQ         0x04u
#define DEM_NVM_STATUSBITMASK_CLEAR                 0x08u
#define DEM_NVM_STATUSBITMASK_INVALIDATE            0x10u
#define DEM_NVM_STATUSBITMASK_CLEAR_REQ             0x20u
#define DEM_NVM_STATUSBITMASK_EXCLUDE               0x40u


typedef Dem_NvmBlockStatusType Dem_NvMBlockStatusDoubleBufferType[5];
#define DEM_NVM_STATUSINDEX_INTERNAL                0u
#define DEM_NVM_STATUSINDEX_SHUTDOWN                1u
#define DEM_NVM_STATUSINDEX_IMMEDIATE               2u
#define DEM_NVM_STATUSINDEX_CLEAR                   3u
#define DEM_NVM_STATUSINDEX_EXCLUDE                 4u


typedef NvM_RequestResultType Dem_NvmResultType;
#define DEM_NVM_PENDING           NVM_REQ_PENDING
#define DEM_NVM_SUCCESS           NVM_REQ_OK
#define DEM_NVM_CANCELED          NVM_REQ_CANCELED
#define DEM_NVM_FAILED            NVM_REQ_NOT_OK
#define DEM_NVM_INVALID           NVM_REQ_NV_INVALIDATED
#define DEM_NVM_INTEGRITY_FAILED  NVM_REQ_INTEGRITY_FAILED
#define DEM_NVM_BLOCK_SKIPPED     NVM_REQ_BLOCK_SKIPPED

typedef uint8 Dem_NvmHashIdType;

#endif

