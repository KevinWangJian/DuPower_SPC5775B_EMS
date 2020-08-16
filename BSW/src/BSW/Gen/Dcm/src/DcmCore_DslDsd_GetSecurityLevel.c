

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetSecurityLevel : API to get the active security level
 * \param           None
 *
 *
 * \retval          active security
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetSecurityLevel (CONSTP2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel)
{
    if(SecLevel!= NULL_PTR)
    {
        *SecLevel = Dcm_Dsld_Conf_cs.security_lookup_table_pcau8[Dcm_DsldGlobal_st.idxActiveSecurity_u8];
    }
    else
    {
        /* DET ERROR REPORT */
        DCM_DET_ERROR(DCM_BOOTLOADER_ID, DCM_E_PARAM_POINTER);

    }

    return (E_OK);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

