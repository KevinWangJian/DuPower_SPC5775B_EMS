

#ifndef BSWM_PRV_MRP_H
#define BSWM_PRV_MRP_H

/*
 **********************************************************************************************************************
 * Function declarations
 **********************************************************************************************************************
*/

/*Note : This type represents the number of possible MRP types
 * i.e. it corresponds to the number of types available in the BswM_Cfg_MRPType_ten enum
 * If the number of elements in the enum changes, this macro must be changed to reflect the new count
 */
#define BSWM_PRV_NO_OF_MRPTYPES 22

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#if (defined(BSWM_NO_OF_MRP_CANSM_INDICATION) && (BSWM_NO_OF_MRP_CANSM_INDICATION > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetCanSMMRPIndex_b ( VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_CANSM_INDICATION > 0 */

#if (defined(BSWM_NO_OF_MRP_COMM_INDICATION) && (BSWM_NO_OF_MRP_COMM_INDICATION > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetComMMRPIndex_b  ( VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_COMM_INDICATION > 0 */

#if (defined(BSWM_NO_OF_MRP_COMMPNCS_REQUEST) && (BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetCurrentPncMRPIndex_b ( VAR(PNCHandleType, AUTOMATIC) PNC_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0 */

#if (defined(BSWM_NO_OF_MRP_DCM_COM_MODE_REQ) && (BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetDcmComModeRequestMRPIndex_b ( VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0 */

#if (defined(BSWM_NO_OF_ECUMWKP_SOURCES) && (BSWM_NO_OF_ECUMWKP_SOURCES > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetEcuMWkpSrcMRPIndex_b( VAR(uint8, AUTOMATIC) idEcuMWkpSrc_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_ECUMWKP_SOURCES > 0 */

#if (defined(BSWM_NO_OF_MRP_ETHIF_PORTFGROUP) && (BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetEthIfMRPIndex_b ( VAR(EthIf_SwitchPortGroupIdxType, AUTOMATIC) idxPortGroup_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0 */

#if (defined(BSWM_NO_OF_MRP_ETHSM_INDICATION) && (BSWM_NO_OF_MRP_ETHSM_INDICATION > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetEthSMMRPIndex_b ( VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_ETHSM_INDICATION > 0 */

#if (defined(BSWM_NO_OF_MRP_FRSM_INDICATION) && (BSWM_NO_OF_MRP_FRSM_INDICATION > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetFrSMMRPIndex_b ( VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_MRP_FRSM_INDICATION > 0 */

#if (defined(BSWM_NO_OF_GENREQ_TOTAL) && (BSWM_NO_OF_GENREQ_TOTAL > 0))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetGenReqMRPIndex_b( VAR(uint16, AUTOMATIC) idRequester_u16, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_GENREQ_TOTAL > 0 */

#if (defined(BSWM_NO_OF_NM_CHANNELS) && (BSWM_NO_OF_NM_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetNmIfWkupIndMRPIndex_b( VAR(uint8, AUTOMATIC)   idChannel_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_NM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_NVM_REQUESTS) && (BSWM_NO_OF_NVM_REQUESTS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetNvMBlockModeMRPIndex_b( VAR(uint16, AUTOMATIC) idBlock_u16, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_NVM_REQUESTS > 0 */

#if (defined(BSWM_NO_OF_NVM_SERVICE_IDS) && (BSWM_NO_OF_NVM_SERVICE_IDS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetNvMJobModeMRPIndex_b( VAR(uint8, AUTOMATIC) idService_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_NVM_SERVICE_IDS > 0 */

#if (defined(BSWM_NO_OF_ECUMRUNREQ_STATES) && (BSWM_NO_OF_ECUMRUNREQ_STATES > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetEcuMRUNReqIndicationMRPIndex_b  ( VAR(EcuM_StateType, AUTOMATIC) State, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_ECUMRUNREQ_STATES > 0 */

#if (defined(BSWM_NO_OF_J1939DCM_CHANNELS) && (BSWM_NO_OF_J1939DCM_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetJ1939DcmIndex_b( VAR(uint16, AUTOMATIC) idNetworkMask_u16, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA) idx_pu16);
#endif /* BSWM_NO_OF_J1939DCM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_J1939NM_CHANNELS) && (BSWM_NO_OF_J1939NM_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetJ1939NmNodeChnIndex_b(VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, VAR(uint8, AUTOMATIC) idNode_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_J1939NM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINSM_CHANNELS) && (BSWM_NO_OF_LINSM_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetLinSmCurrentStateIndex_b(VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8,  P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_LINSM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINSMSCH_CHANNELS) && (BSWM_NO_OF_LINSMSCH_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetLinSmCurrentScheduleChnIndex_b(VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_LINSMSCH_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINTP_CHANNELS) && (BSWM_NO_OF_LINTP_CHANNELS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetLinTpModeReqChnIndex_b(VAR(NetworkHandleType, AUTOMATIC) idNetwork_u8,  P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_LINTP_CHANNELS > 0 */


#if (defined(BSWM_NO_OF_SDCLIENTSRV_CS) && (BSWM_NO_OF_SDCLIENTSRV_CS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetSdclientSrvCSMRPIndex_b(VAR(uint16, AUTOMATIC) idNetwork_u16,  P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_SDCLIENTSRV_CS > 0 */

#if (defined(BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS) && (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetSdConsEvntGrpCSMRPIndex_b(VAR(uint16, AUTOMATIC) idNetwork_u16, P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0 */

#if (defined(BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS) && (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0 ))
FUNC(boolean, BSWM_CODE) BswM_Prv_GetSdEvntHndrCSMRPIndex_b(VAR(uint16, AUTOMATIC) idNetwork_u16,  P2VAR(uint16, AUTOMATIC, BSWM_APPL_DATA)  idx_pu16);
#endif /* BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0 */

FUNC(boolean, BSWM_CODE) BswM_Prv_ReqProcessOrQueue_b( VAR(BswM_Cfg_MRPType_ten, AUTOMATIC) dataMRPType_en, VAR(uint16, AUTOMATIC) idChannel_u16, VAR(uint16, AUTOMATIC) idxMRPChnl_u16, VAR(uint16, AUTOMATIC) dataReqMode_u16);
FUNC(void, BSWM_CODE) BswM_Prv_RuleEval ( VAR(BswM_ReqProcessing_ten, AUTOMATIC) dataReqProcessing_en, VAR(BswM_Cfg_MRPType_ten, AUTOMATIC) MRPType, VAR(uint16, AUTOMATIC) requesting_user, P2CONST(uint16, AUTOMATIC, BSWM_CONST)  adrRulesRef_pu16, VAR(uint16, AUTOMATIC) nrAssociatedRules_u16);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_PRV_MRP_H_ */
