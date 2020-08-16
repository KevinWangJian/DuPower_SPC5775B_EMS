

#ifndef DCMDSPUDS_REQUESTDOWNLOAD_PROT_H
#define DCMDSPUDS_REQUESTDOWNLOAD_PROT_H


/**
 ***************************************************************************************************
            RequestUpload (RequestUpload) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if (DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)

typedef struct
{
	uint32 dataRequestDownloadMemoryRangeLow_u32;		 /*Lower memory address range allowed*/
	uint32 dataRequestDownloadMemoryRangeHigh_u32;	 /*High memory address range allowed*/
	uint32 dataAllowedSec_u32;                  /* Allowed security*/
	uint8  dataMemoryValue_u8;				         /*Value of Memory Identifier to select the desired memory device*/
} Dcm_RequestDownloadConfig_tst;

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_RequestDownloadConfig_tst, DCM_CONST) Dcm_RequestDownloadConfig_cast [];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(uint16,DCM_CODE) Dcm_RequestDownloadCalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#endif


#endif   /* _DCMDSPUDS_REQUESTDOWNLOAD_PROT_H */
#endif
