/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef DCMAPPL_H
#define DCMAPPL_H

#include "DcmDspUds_Cdtcs_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/


/*************************************************************************************************/
/* Included header files                                                                         */
/*************************************************************************************************/

/*
 *************************************************************************************************
 *    definitions and Typedefs                                                                   */
/*************************************************************************************************
 */
/*
 * Standard negative response (0x11,0x12 & 0x31)are suppressed during a functional request.
 * This part is implemented in the function Dcm_ProcessingDone().
 * Some customers may need the suppression of additional NRCs. These additional NRCs can be added in the below MACRO.
 * Please refer the example given below to configure additional NRCs to suppress during functional request.
 * NOTE : If 0x78 response is sent first and the NRC generated later is either 0x11, 0x12, 0x31 or one of the NRC
 * configured below, then NRC will not be suppressed.(ISO requirement)
 * As per the ISO requirement When this response code is used, the server shall always send a final response
 * (positive or negative) independently of the suppressPosRspMsgIndicationBit value or the supress requirement for
 * responses with NRCs SNS, SRNS and ROOR on functionally addressed requests.
 * If there is no additional NRC to suppress, the MACRO should be expanded to (0)
 */
/* Ex :
 * #define DCMAPPL_SUPPRESS_NRC(NegRespCode) (((NegRespCode) == NRC_1) || ((NegRespCode) == NRC_2))
*/
#define DCMAPPL_SUPPRESS_NRC(NegRespCode) (0u)


/* User can enter the address definitions, or include the file containing the address definitions, if the address range is entered as a string in
DcmDspWriteMemoryRangeHigh
DcmDspWriteMemoryRangeLow
DcmDspReadMemoryRangeHigh
DcmDspReadMemoryRangeLow */

/****************************************************************************************************
*        APPLICATION API DECLARATIONS
****************************************************************************************************/
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/*TESTCODE-START
#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
#define DCM_STORE_DEFINITION_BY_ID                (0x01)
#define DCM_STORE_DEFINITION_BY_MEMORYADDRESS     (0x02)
#endif
TESTCODE-END*/
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmNotification (
                                                     VAR(uint8,AUTOMATIC) SID,
                                                     CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
                                                     VAR(uint16,AUTOMATIC) RequestLength,
                                                     VAR(uint8,AUTOMATIC) RequestType,
                                                     VAR(PduIdType,AUTOMATIC) DcmRxPduId,
                                                     VAR(uint16,AUTOMATIC) SourceAddress,
                                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                     );
#endif

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_ManufacturerNotification (
                                               VAR(uint8,AUTOMATIC) SID,
                                               CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
                                               VAR(uint16,AUTOMATIC) RequestLength,
                                               VAR(uint8,AUTOMATIC) RequestType,
                                               VAR(PduIdType,AUTOMATIC) DcmRxPduId,
                                               VAR(uint16,AUTOMATIC) SourceAddress,
                                               P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) adrMsgContext_pst,
                                               P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                         );
#endif

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmGetNRCForMinLengthCheck (
		                                       VAR(Dcm_ProtocolType,AUTOMATIC) dataProtocolId_u8,
		                                       VAR(uint8,AUTOMATIC) dataSid_u8,
                                               P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
                                                                   );

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation
(
    VAR(Dcm_IdContextType,AUTOMATIC) idContext,
    VAR(PduIdType,AUTOMATIC) dcmRxPduId,
    VAR(uint16,AUTOMATIC) SourceAddress,
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmSesCtrlChangeIndication
(
    VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeOld,
    VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeNew
);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_ConfirmationRespPend(
                                                        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                       );



#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmCancelPagedBufferProcessing(VAR(Dcm_IdContextType,AUTOMATIC) idContext);
#endif

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF))
extern FUNC(void,DCM_APPL_CODE) DcmAppl_P3TimeoutIndication(void);
#if(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF)
extern FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetRemainingResponseLength(
                                        VAR(uint8, AUTOMATIC) dataSID_u8,
                                        P2VAR(PduLengthType,AUTOMATIC,DCM_INTERN_DATA) dataResponseLength
                                        );
#endif
#endif

#if((DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF))

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmationRDPI
(
    VAR(Dcm_IdContextType,AUTOMATIC) idContext,
    VAR(PduIdType,AUTOMATIC) dcmRxPduId,
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);
#endif

#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_DcmNegResp(
                                                        VAR(Dcm_IdContextType,AUTOMATIC) idContext,
                                                        VAR(PduIdType,AUTOMATIC) dcmRxPduId,
                                                        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                      );
#endif

FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_GeneralReject (
                                                            VAR(Dcm_IdContextType,AUTOMATIC) idContext,
                                                            VAR(PduIdType,AUTOMATIC) dcmRxPduId,
                                                            VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                               );



extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmIndicationFuncTpr(void);
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmUpdateRxTable (void);

/* Application function to check if the new request can be accepted.
   for particular project variant*/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRxPermission (VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolId,
		VAR(PduIdType, AUTOMATIC) DcmRxPduId,
		P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
		VAR(PduLengthType, AUTOMATIC) TpSduLength);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmComModeError (VAR(uint8,AUTOMATIC) NetworkId);
#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF))
extern FUNC(uint32, DCM_APPL_CODE) DcmAppl_Dcm_CheckUsedCore(void);
#endif
/* FC_VariationPoint_START */
#if((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_OBD_Mode04(void);
#endif
/* FC_VariationPoint_END */
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_CODE) DcmAppl_DDDI_Read_Memory_Condition (
    P2CONST(Dcm_DDDI_DEF_MEM_t,AUTOMATIC,DCM_INTERN_CONST) record,
    P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) NegRespCode);

#if(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmWriteOrClearDddiInNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                            VAR (uint16,AUTOMATIC) dataDddId_u16,
                                                                            VAR (Dcm_OpStatusType,AUTOMATIC) Dcm_StoreDDDiOpstatus_u8,
                                                                            VAR (Dcm_DddiWriteOrClear_ten,AUTOMATIC) Dcm_DddiWriteOrClear_en);

extern FUNC(Dcm_RestoreDddiReturn_ten,DCM_APPL_CODE) DcmAppl_DcmReadDddiFromNvM (P2CONST(Dcm_DddiMainConfig_tst,AUTOMATIC,DCM_INTERN_CONST) dataDefinitionOfDDDI,
                                                                                 VAR (uint16,AUTOMATIC) dataDddId_u16);
#endif

#endif
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckControlMaskAndState(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint8,AUTOMATIC) dataIoParam_u8,
													P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrCtlStateAndMask_pcst,VAR(uint16,AUTOMATIC) dataCtlStateAndMaskLen_u16
													);
#endif

#if ((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)\
		|| (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermissionForMemoryAccess_u8(VAR(uint32,  AUTOMATIC) adrMemoryAddress_u32,
																		  VAR(uint32,  AUTOMATIC) dataDataLength_u32,
																		  VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en);
#endif

#if ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) 			||	\
	(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)    ||  \
	(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)           || \
	(DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Dcm_ReturnReadMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_ReadMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Rmba_Opstatus,
																	  VAR(uint8,  AUTOMATIC) memoryid,
																	  VAR(uint32,  AUTOMATIC) memoryaddress,
																	  VAR(uint32,  AUTOMATIC) datalength,
																	  P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) respbuf,
																	  P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckWDBIReqLen(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint32,AUTOMATIC) dataReqLen_u32);
#endif

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Dcm_ReturnWriteMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_WriteMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Wmba_Opstatus,
																		VAR(uint8,  AUTOMATIC) memoryid,
																		VAR(uint32,  AUTOMATIC) memoryaddress,
																		VAR(uint32,  AUTOMATIC) datalength,
																		P2CONST (uint8,AUTOMATIC,DCM_INTERN_DATA) reqbuf,
																		P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * DcmAppl_Init :
 *  This fucntion will be called before Dcm_Init() function and it is the responsibility of the
 *  customer / production team to initialize the Dcm_ActiveConfigSet_Ptr with the Dcm configuration
 *  set which is of interest to them, if this pointer is a null pointer a default Dcm configuration set
 *  will be chosen, with the current implementation it is Dcm_ConfigType_dataSetName1.
 * @param
 * @retval          None
 */
extern FUNC(void,DCM_APPL_CODE) DcmAppl_Init (void);
#endif

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DisableDTCSetting (
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                          );
extern FUNC (void, DCM_APPL_CODE) DcmAppl_EnableDTCSetting(
													VAR(Dem_ReturnControlDTCSettingType,AUTOMATIC) DtcEnableStatus
														);
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DcmControlDtcSettingEnableStatus(
		VAR(boolean,AUTOMATIC) ControlDtcSettingEnableStatus
		);

extern FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckCDTCRecord (
                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlOptionRecord,
                                    VAR(uint8,AUTOMATIC) Length,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                       );
#endif



 #define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/******************************************************************************************************/
 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DcmSwitchCommunicationControl( VAR(uint8,DCM_VAR) NetworkID ,Dcm_CommunicationModeType RequestedMode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmCommControlConditionCheck(VAR(uint8,AUTOMATIC) ControlType_u8,
                                                                                VAR(uint8,AUTOMATIC) DataCommType_u8,
                                                                                P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData,
                                                                                VAR(uint16,AUTOMATIC) RequestLength,
                                                                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8 );
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
extern FUNC (boolean, DCM_APPL_CODE) DcmAppl_DcmIsComModeDefault( VAR(uint8,DCM_VAR) NetworkID );
#endif
#endif



#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermTxWarmResp(void);
extern FUNC(Dcm_EcuStartModeType,DCM_APPL_CODE) Dcm_GetProgConditions
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions );
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
extern FUNC(void, DCM_APPL_CODE) DcmAppl_DcmRespWarmInit(void);
extern FUNC(uint8,DCM_APPL_CODE) DcmAppl_DcmGetStoreType(VAR(uint8, AUTOMATIC) dataBootType_u8);


extern FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_SetProgConditions(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                                    P2CONST(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions);
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmStoreRespForJump
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions );
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)&& (DCM_ROE_ENABLED != DCM_CFG_OFF))
extern FUNC (void,DCM_APPL_CODE) DcmAppl_DcmClearRoeEventInformation (void);
#endif

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetSesChgPermission(
                                            VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeActive,
                                            VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeNew,
                                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                        );

#endif

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmEcuResetPreparation(
                                                                VAR(uint8,AUTOMATIC) ResetType,
                                                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                );

#endif

/**
 ***************************************************************************************************
            Response On Event (ROE) service
 ***************************************************************************************************
 */
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

#if (DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStoreRoeDidInfo( VAR(uint16,AUTOMATIC)  Did,
                                                                      VAR(uint8,AUTOMATIC)  RoeeventID,
                                                                      VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus,
                                                                      VAR(uint16,AUTOMATIC)  SourceAddress,
                                                                      VAR(boolean,AUTOMATIC)  dspRoeStorageState_b,
                                                                      VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                                      VAR(boolean,AUTOMATIC) dspRoeSessionIsDefault_b,
                                                                      P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetROEDidInfo(VAR(uint16,AUTOMATIC)Did,
                                                  VAR(uint8,AUTOMATIC)  RoeeventID,
                                                  P2VAR(Dcm_DspRoeEventState_ten,AUTOMATIC,DCM_INTERN_DATA) RoeEventStatus,
                                                  P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) RoeEventWindowTime_u8,
                                                  P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA)  SourceAddress,
                                                  P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeCtrlStorageState_b,
                                                  P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeSetUpStorageState_b,
                                                  P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) dspRoeSessionIsDefault_b);
#endif
#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)

extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRoeDTCInfo(VAR(uint8,AUTOMATIC)  RoeeventID,
        P2VAR(Dcm_DspRoeEventState_ten,AUTOMATIC,DCM_INTERN_DATA) RoeEventStatus,
        P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) RoeEventWindowTime_u8,
        P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA)  SourceAddress,
        P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) StatusMask,
        P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeCtrlStorageState_b,
        P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeSetUpStorageState_b,
        P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) dspRoeSession_b);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStoreRoeDTCInfo( VAR(uint8,AUTOMATIC)  RoeeventID,
                                                             VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus,
                                                             VAR(uint16,AUTOMATIC)  SourceAddress,
                                                             VAR(uint8,AUTOMATIC) StatusMask,
                                                             VAR(boolean,AUTOMATIC) dspRoeStorageState_b,
                                                             VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                             VAR(boolean,AUTOMATIC) dspRoeSession_b,
                                                             P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

#endif
#if ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmResponseOnEvent(VAR(uint8,AUTOMATIC) RoeEventId_u8,
                                                                   VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus_en);
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmStoreROEcycleCounter ( VAR(uint8,AUTOMATIC) RoeeventID,
                                                                         VAR(uint8,AUTOMATIC) CycleValue);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSetUpRoeEvent (VAR(uint8,AUTOMATIC) RoeeventID,
                                        VAR(uint8,AUTOMATIC) eventType,
                                        VAR(boolean,AUTOMATIC) storageState,
                                        VAR(uint8,AUTOMATIC) eventWindowTime,
                                                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) eventTypeRecord,
                                                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) serviceToRespondToRecord,
                                                                    VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

#endif  /* End of DCM_CFG_DSP_RESPONSEONEVENT_ENABLED */


#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )

#define DCMAPPL_NUMATTGETSEED   0x05            /* Define for number of Attempts to get the valid seed */


extern FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayTime
(
    VAR(uint8,AUTOMATIC) SecurityLevel,
    VAR(uint8,AUTOMATIC) Delaycount,
    VAR(uint32,AUTOMATIC) DelayTime
);

extern FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayForPowerOn
(
    VAR(uint8,AUTOMATIC) SecurityLevel,
    VAR(uint8,AUTOMATIC) Delaycount,
    VAR(uint32,AUTOMATIC) DelayTime
);


extern FUNC(Dcm_StatusType,DCM_APPL_CODE) DcmAppl_DcmCheckSeed
(
    VAR(uint8,AUTOMATIC) SeedLen,
    P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) Seed
);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmSecurityLevelLocked(VAR(uint8,AUTOMATIC) SecTabIdx);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSecaInvalidKey(VAR(uint8,AUTOMATIC) SecTabIdx);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSecaValidKey(VAR(uint8,AUTOMATIC) SecTabIdx);


#endif
#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED == DCM_CFG_OFF)
extern FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetP2Timings(
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2Timing_pu32,
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2StarTiming_pu32,
                                        VAR(Dcm_SesCtrlType, AUTOMATIC) dataSessionId_u8
                                     );
#endif
#endif

extern FUNC(void, DCM_APPL_CODE) DcmAppl_DcmModifyResponse (
									VAR(uint8,AUTOMATIC) dataSid_u8,
									VAR(uint8,AUTOMATIC) dataNRC_u8,
									P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrBufPtr_pu8,
									P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) nrBufSize_pu32
							   		);
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckRoutineControlOptionRecord(VAR(uint16,AUTOMATIC) nrRID_u16,
                                           VAR(uint8,AUTOMATIC) dataSubFunc_u8,P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrRoutineCtrlOptRec_pcst,VAR(uint16,AUTOMATIC) dataRoutineCtrlOptRecSize_u16);
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!= DCM_CFG_OFF)))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_CheckEncryptionCompressionMethod(
        VAR(uint8,AUTOMATIC) Sid_u8,
        VAR(uint8,AUTOMATIC) CompressionMethod,
        VAR(uint8,AUTOMATIC) EncryptionMethod );
#endif
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestUpload(
        VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
        VAR(uint8,AUTOMATIC) DataFormatIdentifier,
        VAR(uint32,AUTOMATIC) MemoryAddress,
        VAR(uint32,AUTOMATIC) MemorySize,
        P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength,
        P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);
#endif
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestDownload(
        VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
        VAR(uint8,AUTOMATIC) DataFormatIdentifier,
        VAR(uint32,AUTOMATIC) MemoryAddress,
        VAR(uint32,AUTOMATIC) MemorySize,
        P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength,
        P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);
#endif
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestTransferExit(
        VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
        P2CONST(uint8,DCM_INTERN_DATA,AUTOMATIC) transferRequestParameterRecord,
        VAR(uint32,AUTOMATIC) transferRequestParameterRecordSize,
        P2VAR(uint8,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecord,
        P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecordSize,
        P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode);
#endif
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_CheckPermissionForTransferData(
                                                    VAR(uint8,AUTOMATIC) BlockSequenceCounter,
                                                    VAR(uint8,AUTOMATIC) memoryId,
                                                    VAR(uint32,AUTOMATIC) memoryAddress,
                                                    P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) memorySize,
                                                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) TransferRequestParameterRecord,
                                                    VAR(uint32,AUTOMATIC) TransferRequestParameterRecordLength,
                                                    VAR(Dcm_TrasferDirection_en,AUTOMATIC) dataTransferDirection_ten,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                    );
extern FUNC(void,DCM_APPL_CODE) DcmAppl_DcmMemSizeCheckForTransferData    (
                                                    VAR(uint8,AUTOMATIC) dataCompressionMethod_u8,
                                                    VAR(uint8,AUTOMATIC) dataMemoryId_u8,
                                                    VAR(uint32,AUTOMATIC) dataTransferRequestParameterRecordLength_u32,
                                                    VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
                                                    );
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckRdbiResponseLength(
                                                    VAR(uint32,AUTOMATIC) dataTotalRespLength_u32,
                                                    VAR(uint16,AUTOMATIC) dataNumOfDids_u16,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_APPL_DATA) ErrorCode
                                                );
#endif

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
extern FUNC(void,DCM_APPL_CODE) DcmAppl_StartOfReception(VAR(Dcm_IdContextType,AUTOMATIC) idContext ,
                                                            VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                            VAR(PduLengthType, AUTOMATIC) RequestLength,
                                                            VAR(uint32, AUTOMATIC) RxBufferPtr);

extern FUNC(void,DCM_APPL_CODE) DcmAppl_CopyRxData(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                      VAR(PduLengthType, AUTOMATIC) RxBufferSize
                                                      );

extern FUNC(void,DCM_APPL_CODE) DcmAppl_TpRxIndication( VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                         VAR(Std_ReturnType, AUTOMATIC) Result);
#endif
/*TESTCODE-START
#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
typedef struct
{
  Dcm_DddiRecord_tst addrRecord_ast[10]; // the size of this array should be atleast the number of records to be added to DDDID
  Dcm_DddiIdContext_tst dataDDDIRecordContext_st;
  Dcm_DddiIdContext_tst dataPDIRecordContext_st;
  uint16 dataDddId_u16;
  uint16 nrMaxNumOfRecords_u16;
} Dcm_DddiStoreInNvMConfig_tst;
extern Dcm_DddiStoreInNvMConfig_tst dataToStoreInNvM_pst[10];
extern uint16 indexOfDDDIToStoreinNvM ;
#endif
TESTCODE-END*/
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
