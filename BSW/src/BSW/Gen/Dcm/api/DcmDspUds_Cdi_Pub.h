

#ifndef DCMDSPUDS_CDI_PUB_H
#define DCMDSPUDS_CDI_PUB_H

/**
 ***************************************************************************************************
            Clear diagnostics information (CDI) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_CDI_CONDITIONCHECK_ENABLED!=DCM_CFG_OFF)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Pointer to the function which checks whether the mode rule is failed or not.
 */
extern P2FUNC(boolean,DCM_APPL_CODE,Dcm_CdiModeRuleRef_pf) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);
extern P2FUNC(Std_ReturnType,DCM_APPL_CODE,Dcm_CDIUserConditionCheck_pf)(VAR(uint32,AUTOMATIC) GoDTC,P2VAR( Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
#endif   /* _DCMDSPUDS_CDI_PUB_H */

