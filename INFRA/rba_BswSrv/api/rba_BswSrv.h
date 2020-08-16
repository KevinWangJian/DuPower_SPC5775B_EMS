/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */

#ifndef RBA_BSWSRV_H
#define RBA_BSWSRV_H



/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "Std_Types.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/* Vendor and module identification */
#define RBA_BSWSRV_VENDOR_ID   (6)
#define RBA_BSWSRV_MODULE_ID   (255)
#define RBA_BSWSRV_INSTANCE_ID (0)

/* Module version information */
#define RBA_BSWSRV_SW_MAJOR_VERSION (3)
#define RBA_BSWSRV_SW_MINOR_VERSION (0)
#define RBA_BSWSRV_SW_PATCH_VERSION (0)




#  define RBA_BSWSRV_PARAM_UNUSED(param)          (void)(param)         /* iwm7abt workaround for defect CSCRM00957569 */
#  define RBA_BSWSRV_PRV_C_IMPL


/*
 *********************************************************************
 * Type definition
 *********************************************************************
 */

typedef unsigned long long rba_BswSrv_uint64;


/*
 ***************************************************************************************************
 * Variable declarations
 ***************************************************************************************************
 */

 /*
 ***************************************************************************************************
 * Prototypes
 ***************************************************************************************************
 */

#define RBA_BSWSRV_START_SEC_CODE
#include "rba_BswSrv_MemMap.h"
extern void* rba_BswSrv_MemCopy(void* xDest_pv, const void* xSrc_pcv, uint32 numBytes_u32);
extern void* rba_BswSrv_MemSet(void* xDest_pv, sint32 xPattern_u32, uint32 numBytes_u32);
extern sint32 rba_BswSrv_MemCompare(const void* xSrc1_pcv, const void* xSrc2_pcv, uint32 numBytes_u32);
#define RBA_BSWSRV_STOP_SEC_CODE
#include "rba_BswSrv_MemMap.h"

LOCAL_INLINE uint32 rba_BswSrv_ByteOrderSwap32(uint32 Input_u32);
LOCAL_INLINE uint16 rba_BswSrv_ByteOrderSwap16(uint16 Input_u16);
LOCAL_INLINE void   rba_BswSrv_MemCopy64(rba_BswSrv_uint64* xDest_pu64, const rba_BswSrv_uint64* xSrc_pcu64, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy32(uint32* xDest_pu32, const uint32* xSrc_pcu32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy16(uint16* xDest_pu16, const uint16* xSrc_pcu16, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemCopy8(uint8* xDest_pu8, const uint8* xSrc_pcu8, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare64(const rba_BswSrv_uint64* xSrc1_pcu64, const rba_BswSrv_uint64* xSrc2_pcu64, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare32(const uint32* xSrc1_pcu32, const uint32* xSrc2_pcu32, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare16(const uint16* xSrc1_pcu16, const uint16* xSrc2_pcu16, uint32 numBytes_u32);
LOCAL_INLINE uint32 rba_BswSrv_MemCompare8(const uint8* xSrc1_pcu8, const uint8* xSrc2_pcu8, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet64(rba_BswSrv_uint64* xDest_pu64, rba_BswSrv_uint64 xPattern_u64, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet32(uint32* xDest_pu32, uint32 xPattern_u32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet16(uint16* xDest_pu16, uint32 xPattern_u32, uint32 numBytes_u32);
LOCAL_INLINE void   rba_BswSrv_MemSet8(uint8* xDest_pu8, uint32 xPattern_u32, uint32 numBytes_u32);

/*
 ***************************************************************************************************
 * Inline function definitions
 ***************************************************************************************************
 */



/**
 *********************************************************************
 * rba_BswSrv_ByteOrderSwap32
 *
 * Swaps the byte order of a 32 bit value for endianess conversion.
 *
 * \param   Input_u32: input value
 * \return  value with swapped byte order
 * \retval  uint32
 * \seealso
 * \usedresources
 *********************************************************************
 */
LOCAL_INLINE uint32 rba_BswSrv_ByteOrderSwap32(uint32 Input_u32)
{
    uint32 retVal_u32;


    retVal_u32 = (Input_u32 << 24) | ((Input_u32 & 0xFF00u) << 8) | ((Input_u32 & 0x00FF0000u) >> 8) | (Input_u32 >> 24);


    /* MISRA RULE 9.1 VIOLATION: variable is set by inline assembly but the checker does not understand this */
    return retVal_u32;
}

/**
 *********************************************************************
 * rba_BswSrv_ByteOrderSwap16
 *
 * Swaps the byte order of a 16 bit value for endianess conversion.
 *
 * \param   Input_u16: input value
 * \return  value with swapped byte order
 * \retval  uint16
 * \seealso
 * \usedresources
 *********************************************************************
 */
LOCAL_INLINE uint16 rba_BswSrv_ByteOrderSwap16(uint16 Input_u16)
{
    uint16 retVal_u16;


    retVal_u16 = ((Input_u16 & 0x00FFu) << 8) | ((Input_u16 & 0xFF00u) >> 8);


    /* MISRA RULE 9.1 VIOLATION: variable is set by inline assembly but the checker does not understand this */
    return retVal_u16;
}


/**
 ***************************************************************************************************
 * rba_BswSrv_MemCopy64 - copy non overlapping memory in 64 Bit blocks
 *
 * Memory copy routine. Source and destination must not overlap. Pointer parameters must be 8 Byte
 * aligned. The size should be a multiple of 8. If not, it is rounded down to the next multiple
 * of 8.
 *
 * \param   xDest_pu64      destination address
 * \param   xSrc_pcu64      source address
 * \param   numBytes_u32    number of bytes to be copied
 * \seealso     rba_BswSrv_MemCopy8, rba_BswSrv_MemCopy16, rba_BswSrv_MemCopy32
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemCopy64(rba_BswSrv_uint64* xDest_pu64, const rba_BswSrv_uint64* xSrc_pcu64, uint32 numBytes_u32)
{

    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {
        *xDest_pu64 = *xSrc_pcu64;
        xDest_pu64++;
        xSrc_pcu64++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCopy32 - copy non overlapping memory in 32 Bit blocks
 *
 * Memory copy routine. Source and destination must not overlap. Pointer parameters must be 4 Byte
 * aligned. The size should be a multiple of 4. If not, it is rounded down to the next multiple
 * of 4.
 *
 * \param   xDest_pu32      destination address
 * \param   xSrc_pcu32      source address
 * \param   numBytes_u32    number of bytes to be copied
 * \seealso     rba_BswSrv_MemCopy8, rba_BswSrv_MemCopy16, rba_BswSrv_MemCopy64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemCopy32(uint32* xDest_pu32, const uint32* xSrc_pcu32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {
        *xDest_pu32 = *xSrc_pcu32;
        xDest_pu32++;
        xSrc_pcu32++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCopy16 - copy non overlapping memory in 16 Bit blocks
 *
 * Memory copy routine. Source and destination must not overlap. Pointer parameters must be 2 Byte
 * aligned. The size should be a multiple of 2. If not, it is rounded down to the next multiple
 * of 2.
 *
 * \param   xDest_pu16      destination address
 * \param   xSrc_pcu16      source address
 * \param   numBytes_u32    number of bytes to be copied
 * \seealso     rba_BswSrv_MemCopy8, rba_BswSrv_MemCopy32, rba_BswSrv_MemCopy64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemCopy16(uint16* xDest_pu16, const uint16* xSrc_pcu16, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {
        *xDest_pu16 = *xSrc_pcu16;
        xDest_pu16++;
        xSrc_pcu16++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCopy8 - copy non overlapping memory
 *
 * Memory copy routine. Source and destination must not overlap.
 *
 * \param   xDest_pu8       destination address
 * \param   xSrc_pcu8       source address
 * \param   numBytes_u32    number of bytes to be copied
 * \seealso     rba_BswSrv_MemCopy16, rba_BswSrv_MemCopy32, rba_BswSrv_MemCopy64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemCopy8(uint8* xDest_pu8, const uint8* xSrc_pcu8, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = *xSrc_pcu8;
        xDest_pu8++;
        xSrc_pcu8++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCompare64 - compare memory in 64 Bit blocks
 *
 * Memory compare routine. Pointer parameters must be 8 Byte aligned. The size should be a
 * multiple of 8. If not, it is rounded down to the next multiple of 8.
 *
 * \param   xSrc1_pcu32     first source address
 * \param   xSrc2_pcu32     second source address
 * \param   numBytes_u32    number of bytes to be compared
 * \return  stEqual_u32     result of comparison
 * \retval  0               memory area contents are equal
 * \retval  1               memory area contents differ
 * \seealso     rba_BswSrv_MemCompare8, rba_BswSrv_MemCompare16, rba_BswSrv_MemCompare32
 ***************************************************************************************************
 */
LOCAL_INLINE uint32 rba_BswSrv_MemCompare64(const rba_BswSrv_uint64* xSrc1_pcu64, const rba_BswSrv_uint64* xSrc2_pcu64, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {
        /* MISRA RULE 12.13 VIOLATION: required for code optimization */
        if (*xSrc1_pcu64++ != *xSrc2_pcu64++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCompare32 - compare memory in 32 Bit blocks
 *
 * Memory compare routine. Pointer parameters must be 4 Byte aligned. The size should be a
 * multiple of 4. If not, it is rounded down to the next multiple of 4.
 *
 * \param   xSrc1_pcu32     first source address
 * \param   xSrc2_pcu32     second source address
 * \param   numBytes_u32    number of bytes to be compared
 * \return  stEqual_u32     result of comparison
 * \retval  0               memory area contents are equal
 * \retval  1               memory area contents differ
 * \seealso     rba_BswSrv_MemCompare8, rba_BswSrv_MemCompare16, rba_BswSrv_MemCompare64
 ***************************************************************************************************
 */
LOCAL_INLINE uint32 rba_BswSrv_MemCompare32(const uint32* xSrc1_pcu32, const uint32* xSrc2_pcu32, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {
        /* MISRA RULE 12.13 VIOLATION: required for code optimization */
        if (*xSrc1_pcu32++ != *xSrc2_pcu32++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCompare16 - compare memory in 16 Bit blocks
 *
 * Memory compare routine. Pointer parameters must be 2 Byte aligned. The size should be a
 * multiple of 2. If not, it is rounded down to the next multiple of 2.
 *
 * \param   xSrc1_pcu16     first source address
 * \param   xSrc2_pcu16     second source address
 * \param   numBytes_u32    number of bytes to be compared
 * \return  stEqual_u32     result of comparison
 * \retval  0               memory area contents are equal
 * \retval  1               memory area contents differ
 * \seealso     rba_BswSrv_MemCompare8, rba_BswSrv_MemCompare32, rba_BswSrv_MemCompare64
 ***************************************************************************************************
 */
LOCAL_INLINE uint32 rba_BswSrv_MemCompare16(const uint16* xSrc1_pcu16, const uint16* xSrc2_pcu16, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {
        /* MISRA RULE 12.13 VIOLATION: required for code optimization */
        if (*xSrc1_pcu16++ != *xSrc2_pcu16++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemCompare8 - compare memory
 *
 * Memory compare routine.
 *
 * \param   xSrc1_pcu8      pointer to the first source address
 * \param   xSrc2_pcu8      pointer to the second source address
 * \param   numBytes_u32    number of bytes to be compared
 * \return  stEqual_u32     result of comparison
 * \retval  0               memory area contents are equal
 * \retval  1               memory area contents differ
 * \seealso     rba_BswSrv_MemCompare16, rba_BswSrv_MemCompare32, rba_BswSrv_MemCompare64
 ***************************************************************************************************
 */
LOCAL_INLINE uint32 rba_BswSrv_MemCompare8(const uint8* xSrc1_pcu8, const uint8* xSrc2_pcu8, uint32 numBytes_u32)
{

    uint32 stEqual_u32 = 0ul;
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        /* MISRA RULE 12.13 VIOLATION: required for code optimization */
        if (*xSrc1_pcu8++ != *xSrc2_pcu8++)
        {
            stEqual_u32 = 1ul;
            break;
        }
    }

    return stEqual_u32;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemSet64 - initialize memory with 64 Bit data
 *
 * Memory initialization routine. 64 Bit Pattern is written to the destination.
 * Destination must be 4 Byte aligned. The size should be a multiple of 8. If not, it is rounded
 * down to the next multiple of 8.
 *
 * \param   xDest_pu32      destination address
 * \param   Pattern_u32     fill pattern
 * \param   numBytes_u32    number of bytes to be initialized
 * \seealso     rba_BswSrv_MemSet8, rba_BswSrv_MemSet16, rba_BswSrv_MemSet32
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemSet64(rba_BswSrv_uint64* xDest_pu64, rba_BswSrv_uint64 xPattern_u64, uint32 numBytes_u32)
{

    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 8); ctLoop_u32++)
    {
        *xDest_pu64 = xPattern_u64;
        xDest_pu64++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemSet32 - initialize memory with 32 Bit data
 *
 * Memory initialization routine. 32 Bit Pattern is written to the destination.
 * Destination must be 4 Byte aligned. The size should be a multiple of 4. If not, it is rounded
 * down to the next multiple of 4.
 *
 * \param   xDest_pu32      destination address
 * \param   Pattern_u32     fill pattern
 * \param   numBytes_u32    number of bytes to be initialized
 * \seealso     rba_BswSrv_MemSet8, rba_BswSrv_MemSet16, rba_BswSrv_MemSet64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemSet32(uint32* xDest_pu32, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 4); ctLoop_u32++)
    {
        *xDest_pu32 = xPattern_u32;
        xDest_pu32++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemSet16 - initialize memory with 16 Bit data
 *
 * Memory initialization routine. 16 Bit Pattern is written to the destination.
 * Destination must be 2 Byte aligned. The size should be a multiple of 2. If not, it is rounded
 * down to the next multiple of 2.
 *
 * \param   xDest_pu32      destination address
 * \param   Pattern_u32     fill pattern
 * \param   numBytes_u32    number of bytes to be initialized
 * \seealso     rba_BswSrv_MemSet8, rba_BswSrv_MemSet32, rba_BswSrv_MemSet64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemSet16(uint16* xDest_pu16, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < (numBytes_u32 / 2); ctLoop_u32++)
    {
        *xDest_pu16 = (uint16)xPattern_u32;
        xDest_pu16++;
    }

    return;
}

/**
 ***************************************************************************************************
 * rba_BswSrv_MemSet8 - initialize memory with 8 Bit data
 *
 * Memory initialization routine. 8 Bit Pattern is written to the destination.
 *
 * \param   xDest_pu8       destination address
 * \param   xPattern_u32    fill pattern, only lower 8 bit used
 * \param   numBytes_u32    number of bytes to be initialized
 * \seealso     rba_BswSrv_MemSet16, rba_BswSrv_MemSet32, rba_BswSrv_MemSet64
 ***************************************************************************************************
 */
LOCAL_INLINE void rba_BswSrv_MemSet8(uint8* xDest_pu8, uint32 xPattern_u32, uint32 numBytes_u32)
{
    uint32 ctLoop_u32;

    for(ctLoop_u32 = 0; ctLoop_u32 < numBytes_u32; ctLoop_u32++)
    {
        *xDest_pu8 = (uint8)xPattern_u32;
        xDest_pu8++;
    }

    return;
}

/* end of #ifndef RBA_BSWSRV_H */
#endif


/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name______:rba_BswSrv$
**********************************************************************************************************************
</BASDKey>*/
