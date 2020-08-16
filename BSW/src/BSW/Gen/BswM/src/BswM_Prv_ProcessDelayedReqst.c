

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/

#include "BswM.h"
#include "BswM_Prv.h"


/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Functions                                                      -*/
/*---------------------------------------------------------------------------------------*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#if (defined(BSWM_NO_OF_MRP_CANSM_INDICATION) && (BSWM_NO_OF_MRP_CANSM_INDICATION > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetCanSMIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               CanSM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetCanSMIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;
	CONST(CanSM_BswMCurrentStateType, BSWM_CONST) CanSM_BswMCurrentStateType_caen[] =
	{
	    CANSM_BSWM_NO_COMMUNICATION,
	    CANSM_BSWM_SILENT_COMMUNICATION,
	    CANSM_BSWM_FULL_COMMUNICATION,
	    CANSM_BSWM_BUS_OFF,
	    CANSM_BSWM_CHANGE_BAUDRATE
	};

    /* MRP RAM Buffer initialized at required index */

    BswM_Cfg_CanSMIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_CanSMIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_en = CanSM_BswMCurrentStateType_caen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataCanSM_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataCanSM_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataCanSM_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}


#endif /* BSWM_NO_OF_MRP_CANSM_INDICATION > 0 */


#if (defined(BSWM_NO_OF_MRP_COMM_INDICATION) && (BSWM_NO_OF_MRP_COMM_INDICATION > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetComMIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               ComM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_ComMIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_ComMIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_u8 = (ComM_ModeType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComM_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComM_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComM_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_COMM_INDICATION > 0 */


#if (defined(BSWM_NO_OF_MRP_COMM_INITIATE_RESET) && (BSWM_NO_OF_MRP_COMM_INITIATE_RESET > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetComMInitiateResetInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               ComM Initiate Reset type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMInitiateResetInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_ComMInitiateResetModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_ComMInitiateResetModeInfo_ast[idxMRPChnl_u16].dataMode_b = TRUE;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMReset_st[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMReset_st[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMReset_st[idxMRPChnl_u16].dataReqProcessing_en;

    (void)dataReqMode_u16;  /* To avoid MISRA warning of unused variable */
    return retVal;
}

#endif /* BSWM_NO_OF_MRP_COMM_INITIATE_RESET > 0 */


#if (defined(BSWM_NO_OF_MRP_COMMPNCS_REQUEST) && (BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetComMPncReqstInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               ComM Pnc Request type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetComMPncReqstInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;
    CONST(ComM_PncModeType, BSWM_CONST) ComM_PncModeType_caen[] =
    {
        COMM_PNC_REQUESTED,
        COMM_PNC_READY_SLEEP,
        COMM_PNC_PREPARE_SLEEP,
        COMM_PNC_NO_COMMUNICATION,
        COMM_PNC_FULL_COMMUNICATION /*This state need to be removed once ComM confirms to AR42 */
    };

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_ComMPncRequestModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_ComMPncRequestModeInfo_ast[idxMRPChnl_u16].dataMode_en = ComM_PncModeType_caen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMPnc_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMPnc_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataComMPnc_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_COMMPNCS_REQUEST > 0 */


#if (defined(BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION) && (BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetDcmAppUpdateIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               Dcm Application Updated Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetDcmAppUpdateIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_DcmApplicationUpdatedindicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_DcmApplicationUpdatedindicationModeInfo_ast[idxMRPChnl_u16].dataMode_b = TRUE;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmAppUpdateInd_st[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmAppUpdateInd_st[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmAppUpdateInd_st[idxMRPChnl_u16].dataReqProcessing_en;

    (void)dataReqMode_u16;  /* To avoid MISRA warning of unused variable */
    return retVal;
}

#endif /* BSWM_NO_OF_MRP_DCM_APP_UPDATE_INDICATION > 0 */


#if (defined(BSWM_NO_OF_MRP_DCM_COM_MODE_REQ) && (BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetDcmComModeReqstInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               Get Dcm Com Mode Request type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetDcmComModeReqstInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_DcmComModeRequestModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_DcmComModeRequestModeInfo_ast[idxMRPChnl_u16].dataMode_u8 = (Dcm_CommunicationModeType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmCom_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmCom_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataDcmCom_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_DCM_COM_MODE_REQ > 0 */


#if (defined(BSWM_NO_OF_MRP_ETHIF_PORTFGROUP) && (BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetEthIfPortGroupStateInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  :
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEthIfPortGroupStateInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;
    CONST(EthTrcv_LinkStateType, BSWM_CONST) linkStateType_caen[] =
    {
        ETHTRCV_LINK_STATE_DOWN,
        ETHTRCV_LINK_STATE_ACTIVE
    };

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_EthIfPortGroupStateInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_EthIfPortGroupStateInfo_ast[idxMRPChnl_u16].dataMode_en = linkStateType_caen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthIfPortGroup_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthIfPortGroup_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthIfPortGroup_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_ETHIF_PORTFGROUP > 0 */

#if (defined(BSWM_NO_OF_MRP_ETHSM_INDICATION) && (BSWM_NO_OF_MRP_ETHSM_INDICATION > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetEthSMIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               EthSM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEthSMIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;
    CONST(EthSM_NetworkModeStateType, BSWM_CONST) EthSM_NetworkModeStateType_caen[] =
    {
        ETHSM_STATE_OFFLINE,
        ETHSM_STATE_WAIT_TRCVLINK,
        ETHSM_STATE_WAIT_ONLINE,
        ETHSM_STATE_ONLINE,
        ETHSM_STATE_ONHOLD,
        ETHSM_STATE_WAIT_OFFLINE
    };

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_EthSMIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_EthSMIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_en = EthSM_NetworkModeStateType_caen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthSM_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthSM_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEthSM_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_ETHSM_INDICATION > 0 */


#if (defined(BSWM_NO_OF_MRP_FRSM_INDICATION) && (BSWM_NO_OF_MRP_FRSM_INDICATION > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetFrSMIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               FrSM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetFrSMIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;
    CONST(FrSM_BswM_StateType, BSWM_CONST) FrSM_BswM_StateType_caen[] =
    {
            FRSM_BSWM_READY,
            FRSM_BSWM_READY_ECU_PASSIVE,
            FRSM_BSWM_STARTUP,
            FRSM_BSWM_STARTUP_ECU_PASSIVE,
            FRSM_BSWM_WAKEUP,
            FRSM_BSWM_WAKEUP_ECU_PASSIVE,
            FRSM_BSWM_HALT_REQ,
            FRSM_BSWM_HALT_REQ_ECU_PASSIVE,
            FRSM_BSWM_KEYSLOT_ONLY,
            FRSM_BSWM_KEYSLOT_ONLY_ECU_PASSIVE,
            FRSM_BSWM_ONLINE,
            FRSM_BSWM_ONLINE_ECU_PASSIVE,
            FRSM_BSWM_ONLINE_PASSIVE,
            FRSM_BSWM_ONLINE_PASSIVE_ECU_PASSIVE
           
    };

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_FrSMIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_FrSMIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_en = FrSM_BswM_StateType_caen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataFrSM_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataFrSM_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataFrSM_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_MRP_FRSM_INDICATION > 0 */

#if (defined(BSWM_NO_OF_ECUMWKP_SOURCES) && (BSWM_NO_OF_ECUMWKP_SOURCES > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetEcuMWkpSrcInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               EcuM Wakeup Source type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMWkpSrcInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* EcuM Wakeup Source type MRP RAM Buffer initialized at required index */
    BswM_Cfg_EcuMWkpSrcInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_EcuMWkpSrcInfo_ast[idxMRPChnl_u16].dataState = (EcuM_WakeupStatusType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_ECUMWKP_SOURCES > 0 */

#if (defined(BSWM_NO_OF_GENREQ_TOTAL) && (BSWM_NO_OF_GENREQ_TOTAL > 0 ))

/*******************************************************************************************
*Function name  : BswM_Prv_GetGenReqInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               GenericRequest type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetGenReqInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* Generic Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_GenericReqModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_GenericReqModeInfo_ast[idxMRPChnl_u16].dataMode_u16 = dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}

#endif /* BSWM_NO_OF_GENREQ_TOTAL > 0 */

#if (defined(BSWM_NO_OF_NM_CHANNELS) && (BSWM_NO_OF_NM_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetNmIfWkupIndInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               NmIf wakeup indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNmIfWkupIndInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* NmIf wakeup indication type MRP RAM Buffer initialized at required index */
    BswM_Cfg_NmIfWKupIndInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    (void)dataReqMode_u16;/* To avoid compiler warning */

    BswM_Cfg_NmIfWKupIndInfo_ast[idxMRPChnl_u16].dataMode_b = TRUE;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNmIfCarWakeupInd_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNmIfCarWakeupInd_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNmIfCarWakeupInd_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_NM_CHANNELS > 0 */

#if  (defined(BSWM_NO_OF_ECUMRUNREQ_STATES) && (BSWM_NO_OF_ECUMRUNREQ_STATES > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetEcuMRUNReqIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               EcuMRUNReqIndication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/

FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMRUNReqIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */
    BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_u8 = (EcuM_StateType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_ECUMRUNREQ_STATES > 0 */

#if (defined(BSWM_NO_OF_ECUM_INDICATION) && (BSWM_NO_OF_ECUM_INDICATION > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetEcuMIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               EcuM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/

FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetEcuMIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* MRP RAM Buffer initialized at required index */

    BswM_Cfg_EcuMIndicationModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_EcuMIndicationModeInfo_ast[idxMRPChnl_u16].dataMode_u8 = (EcuM_StateType)dataReqMode_u16;


    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[idxMRPChnl_u16].adrRulesRef_pu16;
    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_ECUM_INDICATION */

#if (defined(BSWM_NO_OF_NVM_REQUESTS) && (BSWM_NO_OF_NVM_REQUESTS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetNvMBlockModeInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               NvM Block mode type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNvMBlockModeInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* NvM Block mode type MRP RAM Buffer initialized at required index */
    BswM_Cfg_NvMReqInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_NvMReqInfo_ast[idxMRPChnl_u16].dataMode_en = (NvM_RequestResultType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_NVM_REQUESTS > 0 */

#if (defined(BSWM_NO_OF_NVM_SERVICE_IDS) && (BSWM_NO_OF_NVM_SERVICE_IDS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetNvMJobModeInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               NvM Job mode type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetNvMJobModeInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* NvM Job mode type MRP RAM Buffer initialized at required index */
    BswM_Cfg_NvMJobModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    BswM_Cfg_NvMJobModeInfo_ast[idxMRPChnl_u16].dataMode_en = (NvM_RequestResultType)dataReqMode_u16;


    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_NVM_SERVICE_IDS > 0 */

#if (defined(BSWM_NO_OF_J1939DCM_CHANNELS) && (BSWM_NO_OF_J1939DCM_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetJ1939DcmInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               J1939Dcm type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/

FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetJ1939DcmInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* J1939Dcm Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;

    if (dataReqMode_u16 == (uint16)BSWM_NO_SOURCE_STATUS_TRUE)
    {
        BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[idxMRPChnl_u16].dataMode_b = TRUE;
    }
    else
    {
        BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[idxMRPChnl_u16].dataMode_b = FALSE;
    }

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_J1939DCM_CHANNELS > 0 */


#if (defined(BSWM_NO_OF_J1939NM_CHANNELS) && (BSWM_NO_OF_J1939NM_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetJ1939NmInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               J1939Nm type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetJ1939NmInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(Nm_StateType, AUTOMATIC) dataNmState_aen[] =
    {
            NM_STATE_UNINIT,
            NM_STATE_BUS_SLEEP,
            NM_STATE_PREPARE_BUS_SLEEP,
            NM_STATE_READY_SLEEP,
            NM_STATE_NORMAL_OPERATION,
            NM_STATE_REPEAT_MESSAGE,
            NM_STATE_SYNCHRONIZE,
            NM_STATE_OFFLINE
    };

    /* J1939Nm Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_J1939NmStateChangeNotificationInfo_ast[idxMRPChnl_u16].dataMode_en = dataNmState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Nm_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_J1939NM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINTP_CHANNELS) && (BSWM_NO_OF_LINTP_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetLinTpModeReqInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               LinTpModeReq type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinTpModeReqInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(LinTp_Mode, AUTOMATIC) dataLinTpStateState_aen[] =
    {
            LINTP_APPLICATIVE_SCHEDULE,
            LINTP_DIAG_REQUEST,
            LINTP_DIAG_RESPONSE
    };

    /* J1939Nm Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_LinTpModeReqInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_LinTpModeReqInfo_ast[idxMRPChnl_u16].dataMode_en = dataLinTpStateState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_LINTP_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINSM_CHANNELS) && (BSWM_NO_OF_LINSM_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetLinSmIdicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               LinSM Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinSmIdicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(LinSM_ModeType, AUTOMATIC) dataLinSmIndState_aen[] =
    {
            LINSM_NO_COM,
            LINSM_FULL_COM
    };

    /* LinSM Indication Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_LinSmCurrentStateInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_LinSmCurrentStateInfo_ast[idxMRPChnl_u16].dataMode_en = dataLinSmIndState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_LINSM_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_LINSMSCH_CHANNELS) && (BSWM_NO_OF_LINSMSCH_CHANNELS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetLinSmScheduleIndicationInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               LinSM Schedule Indication type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetLinSmScheduleIndicationInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    /* LinSM Schedule indication Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_LinSmCurrentSchInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_LinSmCurrentSchInfo_ast[idxMRPChnl_u16].dataMode_u8 = (LinIf_SchHandleType)dataReqMode_u16;

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_LINSMSCH_CHANNELS > 0 */

#if (defined(BSWM_NO_OF_SDCLIENTSRV_CS) && (BSWM_NO_OF_SDCLIENTSRV_CS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetSdClientServiceCurrentStateInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               SdClientServiceCurrentState type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdClientServiceCurrentStateInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(Sd_ClientServiceCurrentStateType, AUTOMATIC) dataSdClientServiceCurrentState_aen[] =
    {
            SD_CLIENT_SERVICE_DOWN,
            SD_CLIENT_SERVICE_AVAILABLE
    };

    /* Sd_ConsumedEventGroupCurrentState Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_SdClientSrvCSModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_SdClientSrvCSModeInfo_ast[idxMRPChnl_u16].dataMode_en = dataSdClientServiceCurrentState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_SDCLIENTSRV_CS > 0 */

#if (defined(BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS) && (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetSdConsumedEventGroupCurrentStateInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               SdConsumedEventGroupCurrentState type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdConsumedEventGroupCurrentStateInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(Sd_ConsumedEventGroupCurrentStateType, AUTOMATIC) dataSdConsumedEventGroupCurrentState_aen[] =
    {
            SD_CONSUMED_EVENTGROUP_DOWN   ,
            SD_CONSUMED_EVENTGROUP_AVAILABLE
    };

    /* Sd_ConsumedEventGroupCurrentState Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[idxMRPChnl_u16].dataMode_en = dataSdConsumedEventGroupCurrentState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0 */

#if (defined(BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS) && (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0 ))
/*******************************************************************************************
*Function name  : BswM_Prv_GetBSWM_NO_OF_SDEVNTHNDLR_HANDLE_CSInfo_en (uint16 idxMRPChnl_u16, uint16 dataReqMode_u16,
*                                            uint16* nrRules_pu16,  uint16* adrRules_pu16)
*
*Description  : This function accesses the PostBuild structure and MRP Ram Buffer of the
*               SdEventHandlerCurrentState type at the specified index. The Ram Buffer is updated with the
*               requested mode value and the required MRP information is accessed from the PB structure.
*
*Parameters(in) :
*     idxMRPChnl_u16- The index (in the PBstruct and RAM buffer) occupied by this channel.
*     dataReqMode_u16-  The mode currently requested.
*
*Parameters(out):
*   nrRules_pu16- The number of rules associated with the particular MRP.
*   adrRules_pu16- Pointer to the array containing the rule indexes associated with the particular MRP.
*
*Return value   : BswM_ReqProcessing_ten
*               BSWM_DEFERRED: The RequestProcessing configured for the MRP is Deferred.
*               BSWM_IMMEDIATE: The RequestProcessing configured for the MRP is Immediate.
*
******************************************************************************************/
FUNC(BswM_ReqProcessing_ten, BSWM_CODE) BswM_Prv_GetSdEventHandlerCurrentStateInfo_en
(
 VAR(uint16, AUTOMATIC) idxMRPChnl_u16,
 VAR(uint16, AUTOMATIC) dataReqMode_u16,
 P2VAR(uint16, AUTOMATIC, BSWM_VAR)nrRules_pu16,
 P2CONST(uint16*, AUTOMATIC, BSWM_VAR) adrRules_pu16
)
{
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) retVal;

    VAR(Sd_EventHandlerCurrentStateType, AUTOMATIC) dataSdEventHandlerCurrentState_aen[] =
    {
            SD_EVENT_HANDLER_RELEASED,
            SD_EVENT_HANDLER_REQUESTED
    };

    /* Sd_EventHandlerCurrentState Request MRP RAM Buffer initialized at required index */
    BswM_Cfg_SdEvntHndrCSModeInfo_ast[idxMRPChnl_u16].isValidModePresent_b = TRUE;
    BswM_Cfg_SdEvntHndrCSModeInfo_ast[idxMRPChnl_u16].dataMode_en = dataSdEventHandlerCurrentState_aen[dataReqMode_u16];

    /* Retrieving information from the PostBuild pointer*/
    *nrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[idxMRPChnl_u16].nrAssociatedRules_u16;
    *adrRules_pu16 = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[idxMRPChnl_u16].adrRulesRef_pu16;

    retVal = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[idxMRPChnl_u16].dataReqProcessing_en;

    return retVal;
}
#endif /* BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0 */

/*******************************************************************************************
*Function name  : BswM_Prv_ProcessDelayedReqst ( void )
*
*Description  : This function processes all the requests which have been stored in the interrupt queue.
*               The requests are de-queued and processed individually. Further, any incoming requests
*               which interrupt the processing of delayed requests are also queued.
*
*Parameters(in) :   None
*
*Parameters(out): None
*
*Return value  : None
*
******************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Prv_ProcessDelayedReqst
(
    void
)
{
    /* Variable declaration*/
    VAR(uint8, AUTOMATIC) queueSize_u8 = 0;

    VAR(BswM_Cfg_MRPType_ten, AUTOMATIC) dataMRPType_en = BSWM_MRP_DEFAULT;
    VAR(uint16, AUTOMATIC) idChannel_u16 = 0;
    VAR(uint16, AUTOMATIC) idxMRPChnl_u16 = 0;
    VAR(uint16, AUTOMATIC) dataReqMode_u16 = 0;
    VAR(Std_ReturnType, AUTOMATIC) queueOutRetVal_u8;

    VAR(uint16, AUTOMATIC) nrRules_u16 = 0;
    P2CONST(uint16, AUTOMATIC, BSWM_VAR) adrRules_pu16 = NULL_PTR;
    VAR(BswM_ReqProcessing_ten, AUTOMATIC) dataReqProc_u16;


    /* Set the Delayed Request processing flag to TRUE*/
    BswM_Prv_flgDelayedReqstProgress_b = TRUE;

    /*Enter Critical Section*/
    SchM_Enter_BswM(BSWM_SCHM_EXCLSV_AREA);

    /* Store queue size in local variable*/
    queueSize_u8 = BswM_Prv_IntrptQueueInfo_st.dataSize_u8;

    /*Exit Critical Section*/
    SchM_Exit_BswM(BSWM_SCHM_EXCLSV_AREA);

    while(queueSize_u8 != 0)
    {

        /*Enter Critical Section*/
        SchM_Enter_BswM(BSWM_SCHM_EXCLSV_AREA);

        /* De-queue the mode request at the head of the queue*/
        queueOutRetVal_u8 = BswM_Prv_IntrptQueueOut(&dataMRPType_en, &idChannel_u16, &idxMRPChnl_u16, &dataReqMode_u16);

        /*Exit Critical Section*/
        SchM_Exit_BswM(BSWM_SCHM_EXCLSV_AREA);

        if (E_OK == queueOutRetVal_u8)
        {
            /*Is a valid accessor function defined for the current MRP Type?*/
            if(BswM_GetDelayedReqInfo_capfct[dataMRPType_en] != NULL_PTR)
            {
                /* Call the relevant function via the array of function pointers*/
                dataReqProc_u16 = BswM_GetDelayedReqInfo_capfct[dataMRPType_en](idxMRPChnl_u16, dataReqMode_u16, &nrRules_u16, &adrRules_pu16);

                /* Request is configured for Deferred Request Processing?*/
                if (BSWM_DEFERRED == dataReqProc_u16)
                {
                    /* If the request is deferred, store it in the deferred request buffer */
                    BswM_Prv_StoreDeferredRequest(dataMRPType_en, idChannel_u16, adrRules_pu16, nrRules_u16);
                }
                else
                {
                    /* In case of Immediate Requests, call the rule arbitration function*/
                    BswM_Prv_Arbitrate_Rule(nrRules_u16, adrRules_pu16);
                }

                /* Resetting all the values before next iteration*/
                dataMRPType_en = BSWM_MRP_DEFAULT;
                idChannel_u16 = 0;
                idxMRPChnl_u16 = 0;
                dataReqMode_u16 = 0;
                nrRules_u16 = 0;
                adrRules_pu16 = NULL_PTR;
            }

            /* Decrement the queue size counter*/
            queueSize_u8--;

        }
        else
        {
            break;
        }
    }

#if ( BSWM_NO_OF_AC_IPDUGROUPSWITCH)
    /* IPdu Group Control action */
    BswM_Prv_CalcPduGrpSwt();
#endif /* (BSWM_NO_OF_AC_IPDUGROUPSWITCH) */

#if (defined(BSWM_NO_OF_AC_DEADLINE_MONITOR_CNTRL) && (BSWM_NO_OF_AC_DEADLINE_MONITOR_CNTRL > 0))
        if (FALSE != BswM_AC_DeadlineMonitoring_ExecFlag_b)
        {
            Com_ReceptionDMControl(BswM_AC_DeadlineMonitoring_IpduGroup);
            BswM_AC_DeadlineMonitoring_ExecFlag_b = FALSE;
        }
#endif

    /* Reset the Delayed Request processing flag */
    BswM_Prv_flgDelayedReqstProgress_b = FALSE;

    return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"
/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
