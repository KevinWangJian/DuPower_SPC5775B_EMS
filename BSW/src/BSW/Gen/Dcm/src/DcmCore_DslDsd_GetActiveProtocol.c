

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetActiveProtocol : API to get the active protocol id
 *
 * \param           ActiveProtocol: Address of global variable Passed by the application.
 *
 *
 * \retval          Std_ReturnType E_OK always
 * \seealso
 * \usedresources
 **************************************************************************************************
 */


FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocol(CONSTP2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol)
{
    Std_ReturnType retVal = E_NOT_OK;

    if(ActiveProtocol != NULL_PTR)
    {
        /* If protocol is active then only DCM can give protocol id */
        /*Check if the Comm Active protocal flag is set*/
        if(Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
        {
            *(ActiveProtocol) = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;

        }
        else
        {
            *(ActiveProtocol) = DCM_NO_ACTIVE_PROTOCOL;
        }

        retVal= E_OK;
    }
    else
    {
        /* NULL_PTR -> return NOT OK*/
    }

    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

