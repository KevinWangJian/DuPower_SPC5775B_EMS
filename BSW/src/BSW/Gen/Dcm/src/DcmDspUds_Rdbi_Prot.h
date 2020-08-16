

#ifndef DCMDSPUDS_RDBI_PROT_H
#define DCMDSPUDS_RDBI_PROT_H


/**
 ***************************************************************************************************
            Read Data By Identifier (RDBI) service
 ***************************************************************************************************
 */

#if (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_RDBI_SIZE_DID            (0x02u) /* Minimum length of request for RDBI */

/* Definitions of states of RDBI service */
typedef enum
{
    DCM_RDBI_IDLE,                      /* Idle state */
    DCM_RDBI_NEG_RESP,
    DCM_RDBI_PROCESS_NEW_DID,           /* "process new DID"  state */
    DCM_RDBI_CHECK_READACCESS,          /* "Check read access" state */
    DCM_RDBI_CHECK_CONDITIONS,          /* "Check conditions" state */
    DCM_RDBI_GET_LENGTH,                /* "Get length" state */
    DCM_RDBI_GET_DATA                   /* "Get data" state */
}Dcm_StRdbi_ten;
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint16             ,DCM_VAR) Dcm_RdbiReqDidNb_u16; /* Number of requested DIDs          */
extern VAR(uint16             ,DCM_VAR) Dcm_NumOfIndices_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_StRdbi_ten     ,DCM_VAR) Dcm_stRdbi_en;           /* State of RDBI state machine        */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (uint32            ,DCM_VAR) Dcm_TotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* Condition Check Read Function Pointer Types */



typedef enum {
  DCM_LENCALC_RETVAL_OK,
  DCM_LENCALC_RETVAL_ERROR,
  DCM_LENCALC_RETVAL_PENDING
}
Dcm_LenCalcRet_ten;

typedef enum {
  DCM_LENCALC_STATUS_INIT,
  DCM_LENCALC_STATUS_GETINDEX,
  DCM_LENCALC_STATUS_GETLENGTH,
  DCM_LENCALC_STATUS_GETSUPPORT
}
Dcm_LenCalc_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_LenCalc_ten, DCM_VAR) Dcm_StLenCalc_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2VAR(uint8,DCM_VAR,DCM_INTERN_DATA) Dcm_IdxList_pu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint32 ,DCM_VAR)  Dcm_NumberOfBytesInResponse_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint16 ,DCM_VAR)  Dcm_NumberOfProcessedDIDs_u16;
extern VAR(uint16 ,DCM_VAR)  Dcm_NumberOfAcceptedDIDs_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspReadDidOpStatus_u8;	/* Variable to store the opstatus*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(Dcm_LenCalcRet_ten,DCM_CODE) Dcm_DspGetTotalLengthOfDIDs_en(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrSourceIds_pu8,
                                                             VAR(uint16,AUTOMATIC) nrDids_u16,
                                                             P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) adrNumOfIndices_pu16,
                                                             P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrTotalLength_pu32,
                                                             P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(void, DCM_CODE) Dcm_Prv_DspRdbiConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
													);															 
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
typedef enum
  {
    DCM_GETDATA_RETVAL_OK,
    DCM_GETDATA_RETVAL_INTERNALERROR,
    DCM_GETDATA_RETVAL_PENDING,
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    DCM_GETDATA_PAGED_BUFFER_TX,
#endif
    DCM_GETDATA_RETVAL_INVALIDCONDITIONS
  } Dcm_GetDataRet_ten;

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
  /**
   * @ingroup DCM_H
   * This macro will be RDBI service for paged buffer handling and used to transmit data available within the current page
   *
   *
   * DCM_E_REQUEST_PROCESS_COMPLETED\n
   *
   *
   */
  #ifndef DCM_E_DATA_PAGE_FILLED
  #define DCM_E_DATA_PAGE_FILLED  45u
  #endif
#endif

typedef enum
  {
    DCM_GETDATA_STATUS_INIT,
    DCM_GETDATA_STATUS_GETLENGTH,
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
    DCM_GETDATA_STATUS_TRANSMITPAGE,
#endif
    DCM_GETDATA_STATUS_GETDATA
  } Dcm_GetData_ten;
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_GetData_ten, DCM_VAR) Dcm_GetDataState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint16 ,DCM_VAR)  Dcm_GetDataNumOfIndex_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint32 ,DCM_VAR)  Dcm_GetDataTotalLength_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
FUNC(Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en(P2CONST(uint8, AUTOMATIC,DCM_INTERN_CONST) adrIdBuffer_pcu8,
                                            P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8,
                                            VAR(uint16,DCM_INTERN_DATA) nrIndex_u16,
                                            P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8
                                            );
#else
FUNC(Dcm_GetDataRet_ten,DCM_CODE) Dcm_GetData_en(P2CONST(uint8, AUTOMATIC,DCM_INTERN_CONST) adrIdBuffer_pcu8,
                                            P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) adrTargetBuffer_pu8,
                                            VAR(uint16,DCM_INTERN_DATA) nrIndex_u16,
                                            P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8,
                                            VAR(uint32,DCM_INTERN_DATA) adrTotalLength_pu32);

#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif


#endif   /* _DCMDSPUDS_RDBI_PROT_H */

