

#ifndef RBA_DIAGLIB_BITS16_H
#define RBA_DIAGLIB_BITS16_H

#include "Std_Types.h"

#define RBA_DIAGLIB_ISBITSET16       rba_DiagLib_Bit16IsBitSet
#define RBA_DIAGLIB_GETBITS16        rba_DiagLib_Bit16GetBits
#define RBA_DIAGLIB_OVERWRITEBIT16   rba_DiagLib_Bit16OverwriteBit
#define RBA_DIAGLIB_OVERWRITEBITS16  rba_DiagLib_Bit16OverwriteBits

LOCAL_INLINE uint16 rba_DiagLib_Bit16Mask(uint8 pos, uint8 len)
{
    uint16 bit2shift = 1;
    return (((bit2shift << len) - 1u) << pos);
}

LOCAL_INLINE void rba_DiagLib_Bit16SetBitMask(uint16 *buffer, uint16 bitMask)
{
    *buffer |= bitMask;
}

LOCAL_INLINE void rba_DiagLib_Bit16ClearBitMask(uint16 *buffer, uint16 bitMask)
{
    *buffer &= ((uint16) (~bitMask));
}

LOCAL_INLINE void rba_DiagLib_Bit16SetBit(uint16 *buffer, uint8 bit_position)
{
    uint16 bit2shift = 1;
    *buffer |= ((uint16) (bit2shift << bit_position));
}

LOCAL_INLINE void rba_DiagLib_Bit16ClearBit(uint16 *buffer, uint8 bit_position)
{
    uint16 bit2shift = 1;
    *buffer &= ((uint16) (~((uint16) (bit2shift << bit_position))));
}

LOCAL_INLINE void rba_DiagLib_Bit16OverwriteBit(uint16 *buffer, uint8 bit_position, boolean will_bit_be_set)
{
    if (will_bit_be_set)
    {
        rba_DiagLib_Bit16SetBit(buffer, bit_position);
    }
    else
    {
        rba_DiagLib_Bit16ClearBit(buffer, bit_position);
    }
}

LOCAL_INLINE boolean rba_DiagLib_Bit16IsBitSet(uint16 value, uint8 bit_position)
{
    return (boolean) (((value >> bit_position) & 1u) != 0u);
}

LOCAL_INLINE uint16 rba_DiagLib_Bit16GetBits(uint16 value, uint8 bit_position, uint8 number_of_bits)
{
    uint16 bit2shift = 1;
    value = value >> bit_position;
    value = value % ((uint16) (bit2shift << number_of_bits));
    return value;
}

LOCAL_INLINE void rba_DiagLib_Bit16ClearBits(uint16 *value, uint8 bit_position, uint8 number_of_bits)
{
    uint16 bit2shift = 1;
    *value &= ((uint16) (~((uint16) ((((uint16) (bit2shift << number_of_bits)) - 1u) << bit_position))));
}

LOCAL_INLINE void rba_DiagLib_Bit16OverwriteBits(uint16 *value, uint8 bit_position, uint8 number_of_bits, uint16 newValue)
{
    uint16 bit2shift = 1;
    rba_DiagLib_Bit16ClearBits(value, bit_position, number_of_bits);
    *value |= ((uint16) ((newValue % ((uint16) (bit2shift << number_of_bits))) << bit_position));
}

LOCAL_INLINE void rba_DiagLib_Bit16ClearAll(uint16 *buffer)
{
    *buffer = 0u;
}

#endif

