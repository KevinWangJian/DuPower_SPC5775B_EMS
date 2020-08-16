

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM.h"

#include "Rte_NvM.h"

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */

#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)

#define NVM_START_SEC_VAR_SAVED_ZONE_16
#include "NvM_MemMap.h"
/**
 * Number of write requests since last power-on.
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3119]
uint16 NvM_Rb_cntrWrites_u16;
#define NVM_STOP_SEC_VAR_SAVED_ZONE_16
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_SAVED_ZONE_32
#include "NvM_MemMap.h"
/**
 * Number of bytes written since last power-on.
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3123]
uint32 NvM_Rb_nrBytesWritten_u32;
#define NVM_STOP_SEC_VAR_SAVED_ZONE_32
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"
/**
 * ID of the last written block.
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3129]
NvM_BlockIdType NvM_Rb_idLastWrittenBlock_uo;
/**
 * Write request counters which will be stored in persistent way.
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3128]
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3135]
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3136]
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3137]
NvM_Rb_WriteMon_tst NvM_Rb_WriteMon_st;
#define NVM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"

#endif

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
 */
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
/**
 * \brief
 * This function clears all write monitoring counters.
 *
 * \details
 * This function always returns E_OK.
 *
 * \param[global out] NvM_Rb_WriteMon_st
 * Structure to store write request counters in persistant way.
 * \param[global out] NvM_Rb_idLastWrittenBlock_uo
 * ID of the last written block.
 * \param[global out] NvM_Rb_nrBytesWritten_u32
 * Number of bytes written since last power-on.
 * \param[global out] NvM_Rb_cntrWrites_u16
 * Number of write requests since last power-on.
 *
 * \return
 * - E_OK = write monitoring counters cleared successfully
 */
Std_ReturnType NvM_Rb_ClrWriteMonCntrs(void)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3122] Service to clear write monitoring counters.

    NvM_Rb_WriteMon_st.cntrWritesAbs_u32 = 0u;
    NvM_Rb_WriteMon_st.cntrWritesMax_u16 = 0u;
    NvM_Rb_WriteMon_st.nrBytesWrittenMax_u32 = 0u;

    NvM_Rb_idLastWrittenBlock_uo = 0u;
    NvM_Rb_nrBytesWritten_u32 = 0u;
    NvM_Rb_cntrWrites_u16 = 0u;

    return E_OK;
}

/**
 * \brief
 * This function increases all NvM internal counters required for write request monitoring.
 *
 * \details
 * All counters have an overflow protection, i.e. a counter cannot exceed the maximum value.
 *
 * \param idBlock_uo
 * ID of the last written block.
 * \param BlockLength_u16
 * Length of the last written block in bytes.
 * \param[global inout] NvM_Rb_WriteMon_st
 * Structure to store write request counters in persistant way.
 * \param[global inout] NvM_Rb_idLastWrittenBlock_uo
 * ID of the last written block.
 * \param[global in] NvM_Rb_nrBytesWritten_u32
 * Number of bytes written since last power-on.
 * \param[global in] NvM_Rb_cntrWrites_u16
 * Number of write requests since last power-on.
 */
void NvM_Prv_IncreaseWriteCounters(NvM_BlockIdType idBlock_uo, uint16 BlockLength_u16)
{
    // save last written block ID
    NvM_Rb_idLastWrittenBlock_uo = idBlock_uo;

    // increase the accumulated number of all write requests only if it has not reached the maximum
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3156] All counters shall have overflow protection
    if (NvM_Rb_WriteMon_st.cntrWritesAbs_u32 < NVM_PRV_CNTR_WRITES_ABS_MAX_VALUE)
    {
        ++NvM_Rb_WriteMon_st.cntrWritesAbs_u32;
    }

    // increase the number of write requests since last power-on only if it has not reached the maximum
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3156] All counters shall have overflow protection
    if (NvM_Rb_cntrWrites_u16 < NVM_PRV_CNTR_WRITES_MAX_VALUE)
    {
        ++NvM_Rb_cntrWrites_u16;

        // store new maximum value if current maximum value has been exceeded
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3156] All counters shall have overflow protection
        if (NvM_Rb_cntrWrites_u16 > NvM_Rb_WriteMon_st.cntrWritesMax_u16)
        {
            NvM_Rb_WriteMon_st.cntrWritesMax_u16 = NvM_Rb_cntrWrites_u16;
        }
    }

    // increase the number of bytes written since last power-on only if it has not reached the maximum
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3156] All counters shall have overflow protection
    if ((NVM_PRV_NR_BYTES_WRITTEN_MAX_VALUE > NvM_Rb_nrBytesWritten_u32) &&
        ((NVM_PRV_NR_BYTES_WRITTEN_MAX_VALUE - NvM_Rb_nrBytesWritten_u32) >= BlockLength_u16))
    {
        NvM_Rb_nrBytesWritten_u32 += BlockLength_u16;

        // store new maximum value if current maximum value has been exceeded
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3156] All counters shall have overflow protection
        if (NvM_Rb_nrBytesWritten_u32 > NvM_Rb_WriteMon_st.nrBytesWrittenMax_u32)
        {
            NvM_Rb_WriteMon_st.nrBytesWrittenMax_u32 = NvM_Rb_nrBytesWritten_u32;
        }
    }
}
#endif

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
