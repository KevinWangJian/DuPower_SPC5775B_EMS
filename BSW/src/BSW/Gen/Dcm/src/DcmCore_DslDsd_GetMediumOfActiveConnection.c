

#include "DcmCore_DslDsd_Inf.h"

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)

/**
 **************************************************************************************************
 * Dcm_GetMediumOfActiveConnection: API to get Medium information(ie.Can,Flexray..etc) available in the ComMChannel the active connection.
 *                                  This is explicitly provided only for rba_DiagAdapt.This should be invoked only by rba_DiagAdapt only when new protocol request is received from Tester.
 *
 * \param[out]          ActiveMediumId  : Variable Passed by the rba_DiagAdapt to get active Medium information of ComMChannel for the active connection.
 *
 *
 * \retval              E_OK.
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetMediumOfActiveConnection(CONSTP2VAR(Dcm_DslDsd_MediumType_ten, AUTOMATIC, DCM_APPL_DATA) ActiveMediumId)
{

    VAR(Std_ReturnType,AUTOMATIC) dataReturnVaule_u8;

    /*Get the MediumId of the active connection*/
    *ActiveMediumId = Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].MediumId;

    dataReturnVaule_u8 = E_OK;

    return(dataReturnVaule_u8);

}

#endif


