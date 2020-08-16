

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetActiveServiceTable : API to get the service table id
 *
 * \param           ActiveServiceTable: Address of global variable Passed by the application.
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_GetActiveServiceTable (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ActiveServiceTable)
{
    (*ActiveServiceTable) = Dcm_DsldGlobal_st.datActiveSrvtable_u8;

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

