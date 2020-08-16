

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_ByteCopyInit
 Syntax           : void Com_ByteCopyInit(uint8 *dest,uint32 Init_Val,uint32 Len)
 Description      : Service for copying the value passed to destination for UINT8_N Signal
 Parameter        : Pointer to Destination, Initial value and Length
 Return value     : None
***************************************************************************************************/

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ByteCopyInit(P2VAR(uint8,AUTOMATIC, COM_APPL_DATA) dest,VAR(uint32, AUTOMATIC) Init_Val,
                                        VAR(uint32, AUTOMATIC) Len)
{
    while(Len > (uint32)0)
    {
        *(dest) = (uint8)(Init_Val >> (8UL*(Len-1UL)));
        dest++;
        --Len;
    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

