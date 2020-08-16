

#ifndef DCMDSPUDS_RDTC_PRIV_H
#define DCMDSPUDS_RDTC_PRIV_H



/**
 ***************************************************************************************************
            Read DTC info (RDTC) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)

#define DSP_RDTC_MINREQLEN                   0x01u
#define DSP_RDTC_POSSUBFUNC                  0x00u
#define DSP_REPDTCBYSTMASK_REQLEN            0x02u
#define DSP_REPDTCBYSEVMASK_REQLEN           0x03u
#define DSP_RDTC_0A_15_REQLEN                0x01u
#define DSP_RDTC_LSH_16BITS                  0x10u
#define DSP_RDTC_LSH_08BITS                  0x08u
#define DSP_REPORT_ALL_DTC                   0x00u

/*Definitions for the subfunctions */
#define DSP_REPORT_DTC_PERMANENT_STATUS      0x15u
#define DSP_REPORT_SUPPORTED_DTCS            0x0Au
#define DSP_REPORT_DTC_BY_STATUS_MASK        0x02u
#define DSP_REPORT_DTC_BY_SEVERITY_MASK      0x08u
#define DSP_REPORT_NUM_STATUS_MASK_DTC       0x01u
#define DSP_REPORT_NUM_MIRROR_DTC            0x11u
#define DSP_REPORT_USER_DEFMEMORY_DTC_BY_STATUS_MASK      0x17u
/* FC_VariationPoint_START */
#define DSP_REPORT_NUM_EMISSION_DTC          0x12u
/* FC_VariationPoint_END */
#define DSP_REPORT_NUM_SEVERMASK_DTC         0x07u
#define DSP_REPORT_DTC_SNAPSHOT_RECORD       0x03u
#define DSP_REPORT_MIRROR_MEMORY_DTC         0x0Fu
#define DSP_REPORT_EXTENDED_REC_MIRROR_MEM   0x10u
#define DSP_REPORT_EXTENDED_DATA_RECORD      0x06u
#define DSP_REPORT_USER_DEFMEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER     0x19u
#define DSP_REPORT_SNAPSHOT_RECORD_BY_DTC    0x04u
#define DSP_REPORT_USER_DEFMEMORY_DTC_SNAPSHOT_RECORD_BY_DTC_NUMBER    0x18u
/* FC_VariationPoint_START */
#define DSP_REPORT_OBD_DTC_BY_STATUS_MASK    0x13u
/* FC_VariationPoint_END */
#define DSP_REPORT_DTC_FAULT_DETECTION_COUNTER    0x14u
#define DSP_REPORT_FIRST_TEST_FAILED_DTC		  0x0Bu
#define DSP_REPORT_FIRST_CONFIRMED_DTC	          0x0Cu
#define DSP_REPORT_MOST_RECENT_TEST_FAILED_DTC	  0x0Du
#define DSP_REPORT_MOST_RECENT_CONFIRMED_DTC	  0x0Eu
#define DSP_REPORT_DTC_STORED_DATA_BY_RECORD_NUMBER  0x05u
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || \
(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_04_06_10_REQUEST_LENGTH 0x05u
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_18_19_REQUEST_LENGTH 0x06u
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_09_REQUEST_LENGTH 0x04u
#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_07_REQUEST_LENGTH 0x03u
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
		/* FC_VariationPoint_START */ \
		(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
		/* FC_VariationPoint_END */ \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF))
#define  DSP_RDTC_01_11_12_REQUEST_LENGTH 0x02u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)
#define  DSP_RDTC_03_REQUEST_LENGTH 0x01u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_14_REQLEN     0x01u
#endif

#if ((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF) || \
	 (DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF) || \
	 (DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))
#define DSP_RDTC_B_C_D_E_REQLEN     0x01u
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_05_REQLEN     0x02u
#endif
#if (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)
#define DSP_RDTC_17_REQLEN     0x03u
#endif
/* Definitions for RDTC state machine */
typedef enum
{
    DSP_RDTC_UNINIT,                         /* Un-Initialized state */
    DSP_RDTC_INIT,                           /* Default state after Initialisation */
    DSP_RDTC_CALLSERVICE                     /* State in which subfunction service handler is called */
}Dcm_DspRDTCStates_ten;

/* Definitions for RDTC subfunction state machine */
typedef enum
{
    DSP_RDTC_SFUNINIT,                      /* Un-initialized state */
    DSP_RDTC_SFINIT,                        /* Default state after Initialisation */
    DSP_RDTC_SFCALCNUMDTC,                  /* State to calculate the total number of DTC's */
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
    DSP_RDTC_SFTXPAGE,                      /* State in which the Page is transmitted */
    DSP_RDTC_SFFILLZERO,                    /* State in which zero's are filled in page */
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF))
    DSP_RDTC_GETFFSIZE,						/* State to calculate size of freezeframe*/
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED != DCM_CFG_OFF )||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF ))
    DSP_RDTC_UPDATEDISABLED,						/* State  when the Dem API Dem_DisableDTCRecordUpdate is called.*/
#endif
    DSP_RDTC_SFFILLRESP                     /* State in which Response is filled */
}Dcm_DspRDTCSubFuncStates_ten;
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( uint32,                     DCM_VAR )  Dsp_RdtcDTC_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( Dcm_DspRDTCStates_ten,         DCM_VAR )  Dcm_DspRDTCState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( Dcm_DspRDTCSubFuncStates_ten, DCM_VAR )  Dcm_DspRDTCSubFunc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF)|| \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint16,          DCM_VAR ) Dcm_DspMaxResDataLen_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,         DCM_VAR ) Dcm_DspRDTCRecordNum_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_MsgLenType,        DCM_VAR)  Dcm_DspRDTCMaxRespLen_u32;
extern VAR(Dcm_MsgLenType,        DCM_VAR)  Dcm_DspRDTCFilledRespLen_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint16,                DCM_VAR)  Dcm_DspNumFltDTC_u16;
extern VAR(uint16,                DCM_VAR)  Dcm_DspTotalRespLenFilled_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(boolean,               DCM_VAR)  Dcm_DspFirstPageSent_b;
extern VAR(boolean,               DCM_VAR)  Dcm_DspFillZeroes_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_MsgType,           DCM_VAR)  Dcm_DspRDTCRespBufPtr_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF)|| \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF)|| \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)|| \
	/* FC_VariationPoint_START */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)|| \
	/* FC_VariationPoint_END */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF))

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSupportedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
#endif

extern FUNC(void, DCM_CODE) Dcm_Prv_DspReadDTCInfoConfirmation(
VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
);

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x04_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED!=DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x18_ENABLED!=DCM_CFG_OFF)|| (DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED!=DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDataRecordByDTCNumber (
                                                                VAR(Dcm_SrvOpStatusType,AUTOMATIC) Opstatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                                   );
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x05_ENABLED!=DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_GetFreezeFrameDataByRecord (
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                            );
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x09_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportSeverityOfDTC (
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
#endif

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x11_ENABLED != DCM_CFG_OFF) || \
			/* FC_VariationPoint_START */ \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x12_ENABLED != DCM_CFG_OFF) || \
			/* FC_VariationPoint_END */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x01_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x07_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportNumberOfDTC (
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                     );
#endif

#if (DCM_CFG_DSP_RDTCSUBFUNC_0x03_ENABLED != DCM_CFG_OFF)

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCSnapshotRecordIdentification (
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                                          );

#endif

#if(DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED!=DCM_CFG_OFF)

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportDTCBySeverityMaskRecord(
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                                );
#endif
#if(DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED!=DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFaultDetectionCounter(
        VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                                                );
#endif
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x0B_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0C_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0D_ENABLED != DCM_CFG_OFF)|| \
	(DCM_CFG_DSP_RDTCSUBFUNC_0x0E_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_Dsp_ReportFailedDTC (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* DCM_CFG_DSP_READDTCINFORMATION_ENABLED */

#endif   /* _DCMDSPUDS_RDTC_PRIV_H */


