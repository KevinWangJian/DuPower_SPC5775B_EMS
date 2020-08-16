
#ifndef BSWM_PRV_PROCESS_DELAYED_REQ_H
#define BSWM_PRV_PROCESS_DELAYED_REQ_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Type Definitions
 **********************************************************************************************************************
*/

typedef BswM_ReqProcessing_ten(*BswM_GetDelayedReqInfoType_tpfct) ( VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16,
        P2VAR(uint16, AUTOMATIC, BSWM_VAR) nrRules_pu16, P2VAR(const uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);

/*
 **********************************************************************************************************************
 * Function definitions
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

FUNC(void, BSWM_CODE) BswM_Prv_ProcessDelayedReqst(void);

#if (defined(BSWM_NO_OF_MRP_CANSM_INDICATION) && (BSWM_NO_OF_MRP_CANSM_INDICATION > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetCanSMIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_COMM_INDICATION) && (BSWM_NO_OF_MRP_COMM_INDICATION > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_COMM_INITIATE_RESET) && (BSWM_NO_OF_MRP_COMM_INITIATE_RESET > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMInitiateResetInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_COMMPNCS_REQUEST) && (BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMPncReqstInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION) && (BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetDcmAppUpdateIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_DCM_COM_MODE_REQ) && (BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetDcmComModeReqstInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_ECUMWKP_SOURCES) && (BSWM_NO_OF_ECUMWKP_SOURCES > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMWkpSrcInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_ETHIF_PORTFGROUP) && (BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEthIfPortGroupStateInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_ETHSM_INDICATION) && (BSWM_NO_OF_MRP_ETHSM_INDICATION > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEthSMIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_MRP_FRSM_INDICATION) && (BSWM_NO_OF_MRP_FRSM_INDICATION > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetFrSMIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_GENREQ_TOTAL) && (BSWM_NO_OF_GENREQ_TOTAL > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetGenReqInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_NM_CHANNELS) && (BSWM_NO_OF_NM_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNmIfWkupIndInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_NVM_REQUESTS) && (BSWM_NO_OF_NVM_REQUESTS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNvMBlockModeInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_NVM_SERVICE_IDS) && (BSWM_NO_OF_NVM_SERVICE_IDS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNvMJobModeInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif
#if (defined(BSWM_NO_OF_ECUM_INDICATION) && (BSWM_NO_OF_ECUM_INDICATION>0))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_ECUMRUNREQ_STATES) && (BSWM_NO_OF_ECUMRUNREQ_STATES > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMRUNReqIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_J1939DCM_CHANNELS) && (BSWM_NO_OF_J1939DCM_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetJ1939DcmInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_J1939NM_CHANNELS) && (BSWM_NO_OF_J1939NM_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetJ1939NmInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_LINSM_CHANNELS) && (BSWM_NO_OF_LINSM_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinSmIdicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_LINSMSCH_CHANNELS) && (BSWM_NO_OF_LINSMSCH_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinSmScheduleIndicationInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_LINTP_CHANNELS) && (BSWM_NO_OF_LINTP_CHANNELS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinTpModeReqInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_SDCLIENTSRV_CS) && (BSWM_NO_OF_SDCLIENTSRV_CS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdClientServiceCurrentStateInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS) && (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdConsumedEventGroupCurrentStateInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#if (defined(BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS) && (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0 ))
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdEventHandlerCurrentStateInfo_en(VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16, P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16, P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16);
#endif

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

extern VAR(BswM_GetDelayedReqInfoType_tpfct, BSWM_VAR) BswM_GetDelayedReqInfo_capfct[];

#define BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
