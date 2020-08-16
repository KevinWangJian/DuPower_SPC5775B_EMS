


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

/*** BFX_CFG_CLRBIT_U16U8_LOCATION ***/
#if (BFX_CFG_CLRBIT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBit_u16u8(uint16* Data, uint8 BitPn)
    {
        Bfx_Prv_ClrBit_u16u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBIT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_CLRBIT_U32U8_LOCATION ***/
#if (BFX_CFG_CLRBIT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBit_u32u8(uint32* Data, uint8 BitPn)
    {
        Bfx_Prv_ClrBit_u32u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBIT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_CLRBIT_U8U8_LOCATION ***/
#if (BFX_CFG_CLRBIT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBit_u8u8(uint8* Data, uint8 BitPn)
    {
        Bfx_Prv_ClrBit_u8u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBIT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBIT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_CLRBITMASK_U16U16_LOCATION ***/
#if (BFX_CFG_CLRBITMASK_U16U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBitMask_u16u16(uint16* Data, uint16 Mask)
    {
        Bfx_Prv_ClrBitMask_u16u16_Inl(Data, Mask);
    }

    #if (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBITMASK_U16U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_CLRBITMASK_U32U32_LOCATION ***/
#if (BFX_CFG_CLRBITMASK_U32U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBitMask_u32u32(uint32* Data, uint32 Mask)
    {
        Bfx_Prv_ClrBitMask_u32u32_Inl(Data, Mask);
    }

    #if (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBITMASK_U32U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_CLRBITMASK_U8U8_LOCATION ***/
#if (BFX_CFG_CLRBITMASK_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ClrBitMask_u8u8(uint8* Data, uint8 Mask)
    {
        Bfx_Prv_ClrBitMask_u8u8_Inl(Data, Mask);
    }

    #if (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_CLRBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_CLRBITMASK_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_COPYBIT_U16U8U16U8_LOCATION ***/
#if (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_CopyBit_u16u8u16u8(uint16* DestData, uint8 DestPn, uint16 SrcData, uint8 SrcPn)
    {
        Bfx_Prv_CopyBit_u16u8u16u8_Inl(DestData, DestPn, SrcData, SrcPn);
    }

    #if (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U16U8U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_COPYBIT_U16U8U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_COPYBIT_U32U8U32U8_LOCATION ***/
#if (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_CopyBit_u32u8u32u8(uint32* DestData, uint8 DestPn, uint32 SrcData, uint8 SrcPn)
    {
        Bfx_Prv_CopyBit_u32u8u32u8_Inl(DestData, DestPn, SrcData, SrcPn);
    }

    #if (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U32U8U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_COPYBIT_U32U8U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_COPYBIT_U8U8U8U8_LOCATION ***/
#if (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_CopyBit_u8u8u8u8(uint8* DestData, uint8 DestPn, uint8 SrcData, uint8 SrcPn)
    {
        Bfx_Prv_CopyBit_u8u8u8u8_Inl(DestData, DestPn, SrcData, SrcPn);
    }

    #if (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_COPYBIT_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_COPYBIT_U8U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBIT_U16U8_U8_LOCATION ***/
#if (BFX_CFG_GETBIT_U16U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_GetBit_u16u8_u8(uint16 Data, uint8 BitPn)
    {
        return (Bfx_Prv_GetBit_u16u8_u8_Inl(Data, BitPn));
    }

    #if (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U16U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBIT_U16U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBIT_U32U8_U8_LOCATION ***/
#if (BFX_CFG_GETBIT_U32U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_GetBit_u32u8_u8(uint32 Data, uint8 BitPn)
    {
        return (Bfx_Prv_GetBit_u32u8_u8_Inl(Data, BitPn));
    }

    #if (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U32U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBIT_U32U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBIT_U8U8_U8_LOCATION ***/
#if (BFX_CFG_GETBIT_U8U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_GetBit_u8u8_u8(uint8 Data, uint8 BitPn)
    {
        return (Bfx_Prv_GetBit_u8u8_u8_Inl(Data, BitPn));
    }

    #if (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBIT_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBIT_U8U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBITS_U16U8U8_U16_LOCATION ***/
#if (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    uint16 Bfx_GetBits_u16u8u8_u16(uint16 Data, uint8 BitStartPn, uint8 BitLn)
    {
        return (Bfx_Prv_GetBits_u16u8u8_u16_Inl(Data, BitStartPn, BitLn));
    }

    #if (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U16U8U8_U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBITS_U16U8U8_U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBITS_U32U8U8_U32_LOCATION ***/
#if (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    uint32 Bfx_GetBits_u32u8u8_u32(uint32 Data, uint8 BitStartPn, uint8 BitLn)
    {
        return (Bfx_Prv_GetBits_u32u8u8_u32_Inl(Data, BitStartPn, BitLn));
    }

    #if (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U32U8U8_U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBITS_U32U8U8_U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_GETBITS_U8U8U8_U8_LOCATION ***/
#if (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    uint8 Bfx_GetBits_u8u8u8_u8(uint8 Data, uint8 BitStartPn, uint8 BitLn)
    {
        return (Bfx_Prv_GetBits_u8u8u8_u8_Inl(Data, BitStartPn, BitLn));
    }

    #if (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_GETBITS_U8U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_GETBITS_U8U8U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBIT_U16U8U8_LOCATION ***/
#if (BFX_CFG_PUTBIT_U16U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBit_u16u8u8(uint16* Data, uint8 BitPn, boolean Value)
    {
        Bfx_Prv_PutBit_u16u8u8_Inl(Data, BitPn, Value);
    }

    #if (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U16U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBIT_U16U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBIT_U32U8U8_LOCATION ***/
#if (BFX_CFG_PUTBIT_U32U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBit_u32u8u8(uint32* Data, uint8 BitPn, boolean Value)
    {
        Bfx_Prv_PutBit_u32u8u8_Inl(Data, BitPn, Value);
    }

    #if (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U32U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBIT_U32U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBIT_U8U8U8_LOCATION ***/
#if (BFX_CFG_PUTBIT_U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBit_u8u8u8(uint8* Data, uint8 BitPn, boolean Value)
    {
        Bfx_Prv_PutBit_u8u8u8_Inl(Data, BitPn, Value);
    }

    #if (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBIT_U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBIT_U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITS_U16U8U8U16_LOCATION ***/
#if (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBits_u16u8u8u16(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint16 Pattern)
    {
        Bfx_Prv_PutBits_u16u8u8u16_Inl(Data, BitStartPn, BitLn, Pattern);
    }

    #if (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U16U8U8U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITS_U16U8U8U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITS_U32U8U8U32_LOCATION ***/
#if (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBits_u32u8u8u32(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint32 Pattern)
    {
        Bfx_Prv_PutBits_u32u8u8u32_Inl(Data, BitStartPn, BitLn, Pattern);
    }

    #if (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U32U8U8U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITS_U32U8U8U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITS_U8U8U8U8_LOCATION ***/
#if (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBits_u8u8u8u8(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Pattern)
    {
        Bfx_Prv_PutBits_u8u8u8u8_Inl(Data, BitStartPn, BitLn, Pattern);
    }

    #if (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITS_U8U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION ***/
#if (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBitsMask_u16u16u16(uint16* Data, uint16 Pattern, uint16 Mask)
    {
        Bfx_Prv_PutBitsMask_u16u16u16_Inl(Data, Pattern, Mask);
    }

    #if (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITSMASK_U16U16U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION ***/
#if (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBitsMask_u32u32u32(uint32* Data, uint32 Pattern, uint32 Mask)
    {
        Bfx_Prv_PutBitsMask_u32u32u32_Inl(Data, Pattern, Mask);
    }

    #if (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITSMASK_U32U32U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION ***/
#if (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_PutBitsMask_u8u8u8(uint8* Data, uint8 Pattern, uint8 Mask)
    {
        Bfx_Prv_PutBitsMask_u8u8u8_Inl(Data, Pattern, Mask);
    }

    #if (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_PUTBITSMASK_U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITLT_U16U8_LOCATION ***/
#if (BFX_CFG_ROTBITLT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitLt_u16u8(uint16* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitLt_u16u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITLT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITLT_U32U8_LOCATION ***/
#if (BFX_CFG_ROTBITLT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitLt_u32u8(uint32* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitLt_u32u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITLT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITLT_U8U8_LOCATION ***/
#if (BFX_CFG_ROTBITLT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitLt_u8u8(uint8* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitLt_u8u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITLT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITRT_U16U8_LOCATION ***/
#if (BFX_CFG_ROTBITRT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitRt_u16u8(uint16* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitRt_u16u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITRT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITRT_U32U8_LOCATION ***/
#if (BFX_CFG_ROTBITRT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitRt_u32u8(uint32* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitRt_u32u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITRT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_ROTBITRT_U8U8_LOCATION ***/
#if (BFX_CFG_ROTBITRT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_RotBitRt_u8u8(uint8* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_RotBitRt_u8u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_ROTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_ROTBITRT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBIT_U16U8_LOCATION ***/
#if (BFX_CFG_SETBIT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBit_u16u8(uint16* Data, uint8 BitPn)
    {
        Bfx_Prv_SetBit_u16u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBIT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBIT_U32U8_LOCATION ***/
#if (BFX_CFG_SETBIT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBit_u32u8(uint32* Data, uint8 BitPn)
    {
        Bfx_Prv_SetBit_u32u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBIT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBIT_U8U8_LOCATION ***/
#if (BFX_CFG_SETBIT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBit_u8u8(uint8* Data, uint8 BitPn)
    {
        Bfx_Prv_SetBit_u8u8_Inl(Data, BitPn);
    }

    #if (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBIT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBIT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITMASK_U16U16_LOCATION ***/
#if (BFX_CFG_SETBITMASK_U16U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBitMask_u16u16(uint16* Data, uint16 Mask)
    {
        Bfx_Prv_SetBitMask_u16u16_Inl(Data, Mask);
    }

    #if (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITMASK_U16U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITMASK_U32U32_LOCATION ***/
#if (BFX_CFG_SETBITMASK_U32U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBitMask_u32u32(uint32* Data, uint32 Mask)
    {
        Bfx_Prv_SetBitMask_u32u32_Inl(Data, Mask);
    }

    #if (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITMASK_U32U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITMASK_U8U8_LOCATION ***/
#if (BFX_CFG_SETBITMASK_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBitMask_u8u8(uint8* Data, uint8 Mask)
    {
        Bfx_Prv_SetBitMask_u8u8_Inl(Data, Mask);
    }

    #if (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITMASK_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITS_U16U8U8U8_LOCATION ***/
#if (BFX_CFG_SETBITS_U16U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBits_u16u8u8u8(uint16* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
    {
        Bfx_Prv_SetBits_u16u8u8u8_Inl(Data, BitStartPn, BitLn, Status);
    }

    #if (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U16U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITS_U16U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITS_U32U8U8U8_LOCATION ***/
#if (BFX_CFG_SETBITS_U32U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBits_u32u8u8u8(uint32* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
    {
        Bfx_Prv_SetBits_u32u8u8u8_Inl(Data, BitStartPn, BitLn, Status);
    }

    #if (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U32U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITS_U32U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SETBITS_U8U8U8U8_LOCATION ***/
#if (BFX_CFG_SETBITS_U8U8U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_SetBits_u8u8u8u8(uint8* Data, uint8 BitStartPn, uint8 BitLn, uint8 Status)
    {
        Bfx_Prv_SetBits_u8u8u8u8_Inl(Data, BitStartPn, BitLn, Status);
    }

    #if (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SETBITS_U8U8U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SETBITS_U8U8U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITLT_U16U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITLT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitLt_u16u8(uint16* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitLt_u16u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITLT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITLT_U32U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITLT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitLt_u32u8(uint32* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitLt_u32u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITLT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITLT_U8U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITLT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitLt_u8u8(uint8* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitLt_u8u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITLT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITLT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITRT_U16U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITRT_U16U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitRt_u16u8(uint16* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitRt_u16u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U16U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITRT_U16U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITRT_U32U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITRT_U32U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitRt_u32u8(uint32* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitRt_u32u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U32U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITRT_U32U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_SHIFTBITRT_U8U8_LOCATION ***/
#if (BFX_CFG_SHIFTBITRT_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ShiftBitRt_u8u8(uint8* Data, uint8 ShiftCnt)
    {
        Bfx_Prv_ShiftBitRt_u8u8_Inl(Data, ShiftCnt);
    }

    #if (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_SHIFTBITRT_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_SHIFTBITRT_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION ***/
#if (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBitMask_u16u16(uint16* Data, uint16 Mask)
    {
        Bfx_Prv_ToggleBitMask_u16u16_Inl(Data, Mask);
    }

    #if (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITMASK_U16U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION ***/
#if (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBitMask_u32u32(uint32* Data, uint32 Mask)
    {
        Bfx_Prv_ToggleBitMask_u32u32_Inl(Data, Mask);
    }

    #if (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITMASK_U32U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION ***/
#if (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBitMask_u8u8(uint8* Data, uint8 Mask)
    {
        Bfx_Prv_ToggleBitMask_u8u8_Inl(Data, Mask);
    }

    #if (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITMASK_U8U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITS_U16_LOCATION ***/
#if (BFX_CFG_TOGGLEBITS_U16_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBits_u16(uint16* Data)
    {
        Bfx_Prv_ToggleBits_u16_Inl(Data);
    }

    #if (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U16_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITS_U16_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITS_U32_LOCATION ***/
#if (BFX_CFG_TOGGLEBITS_U32_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBits_u32(uint32* Data)
    {
        Bfx_Prv_ToggleBits_u32_Inl(Data);
    }

    #if (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U32_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITS_U32_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TOGGLEBITS_U8_LOCATION ***/
#if (BFX_CFG_TOGGLEBITS_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    void Bfx_ToggleBits_u8(uint8* Data)
    {
        Bfx_Prv_ToggleBits_u8_Inl(Data);
    }

    #if (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TOGGLEBITS_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TOGGLEBITS_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION ***/
#if (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitLnMask_u16u16_u8(uint16 Data, uint16 Mask)
    {
        return (Bfx_Prv_TstBitLnMask_u16u16_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITLNMASK_U16U16_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION ***/
#if (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitLnMask_u32u32_u8(uint32 Data, uint32 Mask)
    {
        return (Bfx_Prv_TstBitLnMask_u32u32_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITLNMASK_U32U32_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION ***/
#if (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitLnMask_u8u8_u8(uint8 Data, uint8 Mask)
    {
        return (Bfx_Prv_TstBitLnMask_u8u8_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITLNMASK_U8U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION ***/
#if (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitMask_u16u16_u8(uint16 Data, uint16 Mask)
    {
        return (Bfx_Prv_TstBitMask_u16u16_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITMASK_U16U16_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION ***/
#if (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitMask_u32u32_u8(uint32 Data, uint32 Mask)
    {
        return (Bfx_Prv_TstBitMask_u32u32_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITMASK_U32U32_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/

/*** BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION ***/
#if (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION != BFX_CFG_LOCATION_INLINE)
    #if (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_START_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_START_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_START_SEC_CODE_FAST
    #else
        #define BFX_START_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"

    boolean Bfx_TstBitMask_u8u8_u8(uint8 Data, uint8 Mask)
    {
        return (Bfx_Prv_TstBitMask_u8u8_u8_Inl(Data, Mask));
    }

    #if (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_NORMAL)
        #define BFX_STOP_SEC_CODE
    #elif (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_SLOW)
        #define BFX_STOP_SEC_CODE_SLOW
    #elif (BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION == BFX_CFG_LOCATION_FAST)
        #define BFX_STOP_SEC_CODE_FAST
    #else
        #define BFX_STOP_SEC_CODE
    #endif
    #include "Bfx_MemMap.h"
/*** BFX_CFG_TSTBITMASK_U8U8_U8_LOCATION ***/
#endif

/*********************************************************************************************************************/



