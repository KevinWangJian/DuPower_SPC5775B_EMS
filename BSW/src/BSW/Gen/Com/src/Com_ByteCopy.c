

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ByteCopy
 Syntax           : void Com_ByteCopy(uint8 *dest,const uint8 *src,uint32 Len)
 Description      : Service for copying the bytes from source to destination
 Parameter        : dest -> Pointer to Destination
                  : src  -> Pointer to Source
                  : Length -> No.of bytes
 Return value     : None
***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_ByteCopy(P2VAR(uint8, AUTOMATIC, COM_APPL_DATA) dest,P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) src, VAR(uint32, AUTOMATIC) Len)
{
/* FC_VariationPoint_START */
    /* Call to rba_BswSrv_MemCopy8 is made, the implementation is a rb specific Memory copy */
    rba_BswSrv_MemCopy8(dest,src,Len);
/* FC_VariationPoint_END */

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

