

/******************************************************************************
 * Header Includes *
 ******************************************************************************/

#include "BswM.h"
#include "BswM_Prv.h"

/******************************************************************************
 * Definition of Global Variables *
 ******************************************************************************/
#define BSWM_START_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

VAR(boolean, BSWM_VAR) BswM_Prv_flgDelayedReqstProgress_b;
VAR(boolean, BSWM_VAR) BswM_Prv_flgDeferredReqstProgress_b;
VAR(boolean, BSWM_VAR) BswM_Prv_flgNewReqstProgress_b;
VAR(boolean, BSWM_VAR) BswM_Prv_flgDelayDeferredReqst_b;
VAR(boolean, BSWM_VAR) BswM_Prv_isReqstDelayed_b;

#define BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

VAR(boolean, BSWM_VAR) BswM_Prv_isModuleInitialised_b = FALSE;

#define BSWM_STOP_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_CLEARED_8
#include "BswM_Cfg_MemMap.h"

VAR(uint8, BSWM_VAR) BswM_Prv_ctrInterrupt_u8;
VAR(uint8, BSWM_VAR) BswM_Rb_ctrInterrupt_au8[2];

#define BSWM_STOP_SEC_VAR_CLEARED_8
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_CLEARED_32
#include "BswM_Cfg_MemMap.h"

P2CONST(BswM_ConfigType, BSWM_VAR, BSWM_APPL_CONST) BswM_Prv_adrSelectedConfig_pcst;

#define BSWM_STOP_SEC_VAR_CLEARED_32
#include "BswM_Cfg_MemMap.h"
#if (defined(BSWM_NO_OF_AC_IPDUGROUPSWITCH) && (BSWM_NO_OF_AC_IPDUGROUPSWITCH > 0 ))
#define BSWM_START_SEC_VAR_CLEARED_8
#include "BswM_Cfg_MemMap.h"
/* PDU group vector which holds the information of the PDu Groups that need initiliation or are newly added */
VAR(Com_IpduGroupVector, BSWM_VAR) BswM_IPduGrpVctr_ReinitTrue_au8;
/* PDU group vector which holds the information of all the  PDu Groups */
VAR(Com_IpduGroupVector, BSWM_VAR) BswM_IPduGrpVctr_ReinitAll_au8;

#define BSWM_STOP_SEC_VAR_CLEARED_8
#include "BswM_Cfg_MemMap.h"


#define BSWM_START_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"
/* Holds the information that PDU group switch action has been performed. */
VAR(boolean, BSWM_VAR) BswM_PduGrpSwt_b;
#define BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_NO_OF_AC_IPDUGROUPSWITCH ) */

/******************************************************************************
 * Definition of Global Functions *
 ******************************************************************************/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/***********************************************************
* Function name: void BswM_Prv_CopyModeInitValues(void)
* Description: Function to copy the initial mode values from the constant post build structure.
* Parameter: None
* Return value: None
* Remarks:
***********************************************************/
FUNC(void, BSWM_CODE) BswM_Prv_CopyModeInitValues(void)
{
    VAR(uint16,AUTOMATIC) cntrLoop_u16 = 0;

    /* CanSM MRP Enabled and CanSM Indication Present */
#if (defined(BSWM_NO_OF_MRP_CANSM_INDICATION) && (BSWM_NO_OF_MRP_CANSM_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_CANSM_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_CanSMIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataCanSM_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_CanSMIndicationModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataCanSM_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* ComM MRP Enabled and ComM Indication Present */
#if (defined(BSWM_NO_OF_MRP_COMM_INDICATION) && (BSWM_NO_OF_MRP_COMM_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_COMM_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_ComMIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComM_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_ComMIndicationModeInfo_ast[cntrLoop_u16].dataMode_u8          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComM_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* ComM MRP Enabled and ComM Initiate Reset Present */
#if (defined(BSWM_NO_OF_MRP_COMM_INITIATE_RESET) && (BSWM_NO_OF_MRP_COMM_INITIATE_RESET > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_COMM_INITIATE_RESET; cntrLoop_u16++)
    {
        BswM_Cfg_ComMInitiateResetModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMReset_st[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_ComMInitiateResetModeInfo_ast[cntrLoop_u16].dataMode_b           = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMReset_st[cntrLoop_u16].dataModeInitValue_b;
    }

#endif

    /* ComM MRP Enabled and ComM Pnc Request Present */
#if (defined(BSWM_NO_OF_MRP_COMMPNCS_REQUEST) && (BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_COMMPNCS_REQUEST; cntrLoop_u16++)
    {
        BswM_Cfg_ComMPncRequestModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMPnc_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_ComMPncRequestModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMPnc_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* Dcm MRP Enabled and Dcm Application Update Indication Present */
#if (defined(BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION) && (BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_DcmApplicationUpdatedindicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmAppUpdateInd_st[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_DcmApplicationUpdatedindicationModeInfo_ast[cntrLoop_u16].dataMode_b           = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmAppUpdateInd_st[cntrLoop_u16].dataModeInitValue_b;
    }

#endif

    /* Dcm MRP Enabled and Dcm Communication Mode Request Present */
#if (defined(BSWM_NO_OF_MRP_DCM_COM_MODE_REQ) && (BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_DCM_COM_MODE_REQ; cntrLoop_u16++)
    {
        BswM_Cfg_DcmComModeRequestModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmCom_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_DcmComModeRequestModeInfo_ast[cntrLoop_u16].dataMode_u8          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmCom_ast[cntrLoop_u16].dataModeInitValue_u8;
    }

#endif

    /* EcuM CurrentWakeup MRP Enabled and Present */
#if (defined(BSWM_NO_OF_ECUMWKP_SOURCES) && (BSWM_NO_OF_ECUMWKP_SOURCES > 0))

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_ECUMWKP_SOURCES; cntrLoop_u16++)
    {
        BswM_Cfg_EcuMWkpSrcInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_EcuMWkpSrcInfo_ast[cntrLoop_u16].dataState         = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[cntrLoop_u16].dataModeInitValue_u8;
    }

#endif

    /*EcuM MRP Enabled and EcuMIndication Present */
#if (defined(BSWM_NO_OF_ECUM_INDICATION) && (BSWM_NO_OF_ECUM_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_ECUM_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_EcuMIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_EcuMIndicationModeInfo_ast[cntrLoop_u16].dataMode_u8          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /*EcuM MRP Enabled and EcuMRUNReqIndication Present  */
#if (defined(BSWM_NO_OF_ECUMRUNREQ_STATES) && (BSWM_NO_OF_ECUMRUNREQ_STATES > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_ECUMRUNREQ_STATES; cntrLoop_u16++)
    {
        BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[cntrLoop_u16].dataMode_u8          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* EthIf MRP Enabled and EthIf PortGroupStateChng Present */
#if (defined(BSWM_NO_OF_MRP_ETHIF_PORTFGROUP) && (BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_ETHIF_PORTFGROUP; cntrLoop_u16++)
    {
        BswM_Cfg_EthIfPortGroupStateInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthIfPortGroup_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_EthIfPortGroupStateInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthIfPortGroup_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* EthSM MRP Enabled and EthSM Indication Present */
#if (defined(BSWM_NO_OF_MRP_ETHSM_INDICATION) && (BSWM_NO_OF_MRP_ETHSM_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_ETHSM_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_EthSMIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthSM_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_EthSMIndicationModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthSM_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* FrSM MRP Enabled and FrSM Indication Present */
#if (defined(BSWM_NO_OF_MRP_FRSM_INDICATION) && (BSWM_NO_OF_MRP_FRSM_INDICATION > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_MRP_FRSM_INDICATION; cntrLoop_u16++)
    {
        BswM_Cfg_FrSMIndicationModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataFrSM_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_FrSMIndicationModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataFrSM_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* Generic Request MRP Enabled and Present */
#if (defined(BSWM_NO_OF_GENREQ_TOTAL) && (BSWM_NO_OF_GENREQ_TOTAL > 0))

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_GENREQ_TOTAL; cntrLoop_u16++)
    {
        BswM_Cfg_GenericReqModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_GenericReqModeInfo_ast[cntrLoop_u16].dataMode_u16         = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[cntrLoop_u16].dataModeInitValue_u16;
    }

#endif

    /* NmIf CarWakeUpIndication MRP Enabled and Present */
#if (defined(BSWM_NO_OF_NM_CHANNELS) && (BSWM_NO_OF_NM_CHANNELS > 0))

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_NM_CHANNELS; cntrLoop_u16++)
    {
        BswM_Cfg_NmIfWKupIndInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNmIfCarWakeupInd_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_NmIfWKupIndInfo_ast[cntrLoop_u16].dataMode_b        = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNmIfCarWakeupInd_ast[cntrLoop_u16].dataModeInitValue_b;
    }

#endif

    /* NvM CurrentBlockMode MRP Enabled and Present */
#if (defined(BSWM_NO_OF_NVM_REQUESTS) && (BSWM_NO_OF_NVM_REQUESTS > 0))

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_NVM_REQUESTS; cntrLoop_u16++)
    {
        BswM_Cfg_NvMReqInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_NvMReqInfo_ast[cntrLoop_u16].dataMode_en        = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* NvM CurrentJobMode MRP Enabled and Present */
#if (defined(BSWM_NO_OF_NVM_SERVICE_IDS) && (BSWM_NO_OF_NVM_SERVICE_IDS > 0))

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_NVM_SERVICE_IDS; cntrLoop_u16++)
    {
        BswM_Cfg_NvMJobModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_NvMJobModeInfo_ast[cntrLoop_u16].dataMode_en        = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

  /* J1939Dcm MRP Enabled */
#if (defined(BSWM_NO_OF_J1939DCM_CHANNELS) && (BSWM_NO_OF_J1939DCM_CHANNELS > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_J1939DCM_CHANNELS; cntrLoop_u16++)
    {
        BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[cntrLoop_u16].dataMode_b          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[cntrLoop_u16].dataModeInitValue_b;
    }

#endif

    /* J1939Nm MRP Enabled */
#if (defined(BSWM_NO_OF_J1939NM_CHANNELS) && (BSWM_NO_OF_J1939NM_CHANNELS > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_J1939NM_CHANNELS; cntrLoop_u16++)
    {
        BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* LinSmIndication MRP Enabled */
  #if (defined(BSWM_NO_OF_LINSM_CHANNELS) && (BSWM_NO_OF_LINSM_CHANNELS > 0))

      for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_LINSM_CHANNELS; cntrLoop_u16++)
      {
          BswM_Cfg_LinSmCurrentStateInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[cntrLoop_u16].isModeInitValuePresent_b;
          BswM_Cfg_LinSmCurrentStateInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[cntrLoop_u16].dataModeInitValue_en;
      }

  #endif

      /* J1939Nm MRP Enabled */
  #if (defined(BSWM_NO_OF_LINSMSCH_CHANNELS) && (BSWM_NO_OF_LINSMSCH_CHANNELS > 0))

      for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_LINSMSCH_CHANNELS; cntrLoop_u16++)
      {
          BswM_Cfg_LinSmCurrentSchInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[cntrLoop_u16].isModeInitValuePresent_b;
          BswM_Cfg_LinSmCurrentSchInfo_ast[cntrLoop_u16].dataMode_u8          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[cntrLoop_u16].dataModeInitValue_u8;
      }

  #endif

      /* J1939Dcm MRP Enabled */
    #if (defined(BSWM_NO_OF_LINTP_CHANNELS) && (BSWM_NO_OF_LINTP_CHANNELS > 0))

        for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_LINTP_CHANNELS; cntrLoop_u16++)
        {
            BswM_Cfg_LinTpModeReqInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[cntrLoop_u16].isModeInitValuePresent_b;
            BswM_Cfg_LinTpModeReqInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[cntrLoop_u16].dataModeInitValue_en;
        }

    #endif

	/* Sd ClientServiceCurrentState MRP Enabled and Present */

#if (defined(BSWM_NO_OF_SDCLIENTSRV_CS) && (BSWM_NO_OF_SDCLIENTSRV_CS > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_SDCLIENTSRV_CS; cntrLoop_u16++)
    {
        BswM_Cfg_SdClientSrvCSModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_SdClientSrvCSModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* Sd ConsumedEventGroupCurrentState MRP Enabled and Present */

#if (defined(BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS) && (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS; cntrLoop_u16++)
    {
        BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    /* Sd EventHandlerCurrentState MRP Enabled and Present */

#if (defined(BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS) && (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0))

    for (cntrLoop_u16 = 0; cntrLoop_u16 < BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS; cntrLoop_u16++)
    {
        BswM_Cfg_SdEvntHndrCSModeInfo_ast[cntrLoop_u16].isValidModePresent_b = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[cntrLoop_u16].isModeInitValuePresent_b;
        BswM_Cfg_SdEvntHndrCSModeInfo_ast[cntrLoop_u16].dataMode_en          = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[cntrLoop_u16].dataModeInitValue_en;
    }

#endif

    (void)cntrLoop_u16;
    return;
}

/***********************************************************
* Function name: void BswM_Prv_CopyRuleInitSates(void)
* Description: Function to copy the initial rule states from the constant post build structure.
* Parameter: None
* Return value: None
* Remarks:
***********************************************************/
FUNC(void, BSWM_CODE) BswM_Prv_CopyRuleInitSates(void)
{


#ifdef BSWM_MAX_NO_OF_RULES
#if (BSWM_MAX_NO_OF_RULES > 0)

    VAR(uint16,AUTOMATIC) cntrLoop_u16 = 0;

    for(cntrLoop_u16 = 0; cntrLoop_u16 < BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.nrRules_u16; cntrLoop_u16++)
    {
        BswM_Prv_RuleState_aen[cntrLoop_u16] = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.adrArbitrationRule_pst[cntrLoop_u16].dataRuleInitState_en;
    }

#endif /* (BSWM_MAX_NO_OF_RULES > 0)*/
#endif /* BSWM_MAX_NO_OF_RULES */

    return;
}


/***********************************************************
* Function name: void BswM_Prv_CalcPduGrpSwt(void)
* Description: Function to handle the start of PduGroups by calling the interface Com_IpduGroupControl.
* Parameter: None
* Return value: None
* Remarks:
***********************************************************/

#if (defined(BSWM_NO_OF_AC_IPDUGROUPSWITCH) && (BSWM_NO_OF_AC_IPDUGROUPSWITCH > 0 ))
FUNC(void, BSWM_CODE) BswM_Prv_CalcPduGrpSwt
(
   void
)
{
    VAR(uint8, AUTOMATIC) idx_u8 = 0;
   /* PDU group switch action has been performed? */
   if ( FALSE != BswM_PduGrpSwt_b )
   {

      /* Call Com interface for PDU group switch with initilasation parameter as TRUE. */
      Com_IpduGroupControl( BswM_IPduGrpVctr_ReinitTrue_au8, TRUE );
      /* Call Com interface for PDU group switch with initilasation parameter as FALSE. */
      Com_IpduGroupControl( BswM_IPduGrpVctr_ReinitAll_au8, FALSE );

      for(idx_u8 = 0;idx_u8 < (sizeof(BswM_IPduGrpVctr_ReinitTrue_au8)/sizeof(Com_IpduGroupVector)) ;idx_u8++)
      {
          /*The PduGroup Vector which collects Pdugroups with reinit as TRUE is overwrritten with vector that collects pdugroups with both reinit TRUE and FALSE*/
          BswM_IPduGrpVctr_ReinitTrue_au8[idx_u8] = BswM_IPduGrpVctr_ReinitAll_au8[idx_u8];

      }
      /* Update the flag for Pdu Group Switch to False */
      BswM_PduGrpSwt_b = FALSE;
   }

   (void)idx_u8;
   return;
}

#endif /* (BSWM_NO_OF_AC_IPDUGROUPSWITCH) */

#if (defined(BSWM_DEBUG) && (BSWM_DEBUG == TRUE))
FUNC (void, BSWM_CODE) BswM_Prv_InterruptHandler (VAR(uint8, AUTOMATIC) dataApiId_u8)
{

    SchM_Enter_BswM( BSWM_SCHM_EXCLSV_AREA );

    if(BswM_Prv_ctrInterrupt_u8 > 1)
    {
        /* If the BswM_Prv_ctrInterrupt_u8 counter value is more than 1 then write into NvM */
        BswM_Rb_ctrInterrupt_au8[0]++;
        BswM_Rb_ctrInterrupt_au8[1] = dataApiId_u8;
        (void)NvM_SetRamBlockStatus( NvMConf_NvMBlockDescriptor_BSWM_CFG_NVM_BLOCK, TRUE );
    }

    /* Exit critical section */
    SchM_Exit_BswM( BSWM_SCHM_EXCLSV_AREA );

    BswM_Prv_ctrInterrupt_u8--;

}
#endif

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"




/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
