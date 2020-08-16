

#ifndef DEM_LIB_H
#define DEM_LIB_H

#include "Dem_Types.h"
#include "Dem_Prv_Det.h"
#include "rba_DiagLib_MemUtils.h"

/* Macro for static assertion Check */
/* either array length is (2*1)-1->valid or (2*0)-1->invalid*/
#define DEM_STATIC_ASSERT(COND,MSG) typedef uint8 Dem_static_assertion_##MSG[(2*(((COND)!=(FALSE))?1:0))-1]

/* mapping of memset and memcpy */
#define DEM_MEMCPY  RBA_DIAGLIB_MEMCPY
#define DEM_MEMSET  RBA_DIAGLIB_MEMSET

/* Defines */
#define DEM_MAXSINT16   0x7FFF



// these functions are necessary to avoid compiler warnings of the kind "statement is always FALSE"
DEM_INLINE uint32 Dem_LibGetParamUI32( uint32 parameter )
{
    return parameter;
}

DEM_INLINE uint16 Dem_LibGetParamUI16( uint16 parameter )
{
    return parameter;
}

DEM_INLINE uint8 Dem_LibGetParamUI8( uint8 parameter )
{
    return parameter;
}

DEM_INLINE boolean Dem_LibGetParamBool( boolean parameter )
{
    return parameter;
}



DEM_INLINE uint32 Dem_BigEndian_ReadValueFromBuffer(const uint8 *buffer, uint32 size)
{
    uint32 i;
    uint32 result = 0;

    for(i=0; i<size; i++)
    {
        result = (uint32)( (result << 8) + buffer[i]) ;
    }
    return result;

}
DEM_INLINE void Dem_BigEndian_WriteValue2Buffer(uint8 *buffer, uint32 value, uint32 size)
{
    while (size > 0u)
    {
        size--;
        buffer[size] = (uint8)(value & 0xFFu);
        value = value / 0x100u;
    }
}

#endif
