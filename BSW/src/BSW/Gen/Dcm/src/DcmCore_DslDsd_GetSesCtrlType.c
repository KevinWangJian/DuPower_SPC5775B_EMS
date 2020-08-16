

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetSesCtrlType : API to get the active session id
 * \param           SesCtrlType
 *
 *
 * \retval          active session id
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(CONSTP2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA)  SesCtrlType)
{

    if(SesCtrlType != NULL_PTR)
    {
        /*Check if the Dcm session flag is set to get the active session id*/
        if(Dcm_DsldSessionflag_b == TRUE)
        {

            *SesCtrlType = Dcm_DsldSessionTable_pcu8[Dcm_DsldGlobal_st.PreviousSessionIndex];

        }
        else
        {

            *SesCtrlType = Dcm_DsldSessionTable_pcu8[ Dcm_DsldGlobal_st.idxActiveSession_u8];

        }
    }
    else
    {
        /* DET ERROR REPORT */
        DCM_DET_ERROR(DCM_SETSESSION_ID, DCM_E_PARAM_POINTER);
    }

    return(E_OK);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

