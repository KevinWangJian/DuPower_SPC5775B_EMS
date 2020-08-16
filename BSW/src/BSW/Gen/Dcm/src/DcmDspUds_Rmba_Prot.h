

#ifndef DCMDSPUDS_RMBA_PROT_H
#define DCMDSPUDS_RMBA_PROT_H


/**
 ***************************************************************************************************
            Read Memory By Address (RMBA) service
 ***************************************************************************************************
 */

#if (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)

#include "DcmDspUds_Memaddress_Calc_Prot.h"

typedef struct
{
	uint32 dataReadMemoryRangeLow_u32;			/*Lower memory address range allowed for writing*/
	uint32 dataReadMemoryRangeHigh_u32;			/*High memory address range allowed for writing*/
	uint32 dataAllowedSecRead_u32;          /* Allowed security levels(for Reading) */
	uint32 dataAllowedSessRead_u32;         /* Allowed session (for Reading)*/
	P2FUNC(Std_ReturnType,TYPEDEF,adrUserMemReadModeRule_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8,VAR(uint32,AUTOMATIC) adrMemoryAddress_u32,VAR(uint32,AUTOMATIC) dataDataLength_u32,VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en); /* User Mode rule check function pointer */
#if (DCM_CFG_DSP_MODERULEFORREADMEMORY != DCM_CFG_OFF)
	P2FUNC(boolean,TYPEDEF,addrRmbaModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8); /* Mode rule check funtion pointer */
#endif
	uint8 dataMemoryValue_u8;				/*Value of Memory Identifier to select the desired memory device*/
} Dcm_RMBAConfig_tst;
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_RMBAConfig_tst, DCM_CONST) Dcm_RMBAConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(uint16,DCM_CODE) Dcm_RmbacalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#endif

#endif   /* _DCMDSPUDS_RMBA_PROT_H */

