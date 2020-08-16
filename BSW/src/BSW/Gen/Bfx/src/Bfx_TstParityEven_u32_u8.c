


/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

#define SRVLIBS

#include "Bfx.h"


/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
 */

/*** BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION ***/
#if (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstParityEven_u32_u8(uint32 Data)
    {
        /*** BFX_CFG_OPTIMIZATION ***/
        #if ((BFX_CFG_OPTIMIZATION == BFX_CFG_TCCOMMON) || (BFX_CFG_OPTIMIZATION == BFX_CFG_TC27XX))
        return (rba_BfxTCCommon_Prv_TstParityEven_u32_u8_Inl(Data));
        #elif ((BFX_CFG_OPTIMIZATION == BFX_CFG_MPCCOMMON) || (BFX_CFG_OPTIMIZATION == BFX_CFG_MPCCUT2))
        return (rba_BfxMPCCommon_Prv_TstParityEven_u32_u8_Inl(Data));
        #else
        return (Bfx_Prv_TstParityEven_u32_u8_Inl(Data));
        /*** BFX_CFG_OPTIMIZATION ***/
        #endif
    }

    #if (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTPARITYEVEN_U32_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/



