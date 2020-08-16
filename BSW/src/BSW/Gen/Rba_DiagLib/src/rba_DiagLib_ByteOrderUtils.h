

#ifndef RBA_DIAGLIB_BYTEORDERUTILS_H
#define RBA_DIAGLIB_BYTEORDERUTILS_H

#include "Std_Types.h"
#include "rba_BswSrv.h"

#define RBA_DIAGLIB_START_SEC_ROM_CODE
#include "rba_DiagLib_MemMap.h"

/**
 * Utility functions for endianess handling.
 *
 * Remarks:
 * 1. Network byte order is big endian byte order.
 * 2. Motorola format stands for big endian byte order.
 * 3. Intel format stands for little endian byte order.
 *
 * SwapByteOrderS: swaps byte order for short (16bit) variables
 * SwapByteOrderL: swaps byte order for long  (32bit) variables
 *
 * IsBigEndian: returns TRUE if host (CPU) has big endian byte order, else FALSE
 *
 * Htons: Host to network for short (16bit) variables.
 *        Swaps byte order if host (CPU) has not big endian byte order.
 * Htonl: Host to network for long  (32bit) variables.
 *        Swaps byte order if host (CPU) has not big endian byte order.
 * Ntohs: Network to host for short (16bit) variables.
 *        Swaps byte order if host (CPU) has not big endian byte order.
 * Ntohl: Network to host for long  (32bit) variables.
 *        Swaps byte order if host (CPU) has not big endian byte order.
 */

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_SwapByteOrderS(uint16 val)
{
    return rba_BswSrv_ByteOrderSwap16(val);
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_SwapByteOrderL(uint32 val)
{
    return rba_BswSrv_ByteOrderSwap32(val);
}

LOCAL_INLINE boolean rba_DiagLib_ByteOrderUtils_IsBigEndian(void)
{
    boolean isBigEndian = TRUE;
    if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
        isBigEndian = FALSE;
    }
    return isBigEndian;
}

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_Htons(uint16 val)
{
    uint16 ret = val;
    if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
        ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderS(val);
    }
    return ret;
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_Htonl(uint32 val)
{
    uint32 ret = val;
    if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
        ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderL(val);
    }
    return ret;
}

LOCAL_INLINE uint16 rba_DiagLib_ByteOrderUtils_Ntohs(uint16 val)
{
    uint16 ret = val;
    if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
        ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderS(val);
    }
    return ret;
}

LOCAL_INLINE uint32 rba_DiagLib_ByteOrderUtils_Ntohl(uint32 val)
{
    uint32 ret = val;
    if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
    {
        ret = rba_DiagLib_ByteOrderUtils_SwapByteOrderL(val);
    }
    return ret;
}

//this function is only necessary until another function is implemented
//it is only temporarely necessary for the coverage and misra tests
boolean rba_DiagLib_ByteOrderUtils_Dummy(void);

#define RBA_DIAGLIB_STOP_SEC_ROM_CODE
#include "rba_DiagLib_MemMap.h"

#endif
