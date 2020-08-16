


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

/*** BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION ***/
#if (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstParityEven_u8_u8(uint8 Data)
    {
        return (Bfx_Prv_TstParityEven_u8_u8_Inl(Data));
    }

    #if (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTPARITYEVEN_U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/



