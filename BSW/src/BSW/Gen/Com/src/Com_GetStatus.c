

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/


/**************************************************************************************************/
/* Function name    : Com_GetStatus                                                               */
/* Syntax           : Com_StatusType Com_GetStatus(void)                                          */
/* Description      : Service returns the status of the AUTOSAR COM module                        */
/* Parameter        : void                                                                        */
/* Return value     : status of the AUTOSAR COM module: COM_INIT/COM_UNINIT                       */
/**************************************************************************************************/

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Com_StatusType, COM_CODE) Com_GetStatus(void)
{
    return Com_Uninit_Flag;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

