
#ifndef _DCM_LCFG_DSLDSD_H
#define _DCM_LCFG_DSLDSD_H


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmTesterPresent(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmSecurityAccess(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmWriteDataByIdentifier(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadDataByIdentifier(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadDTCInformation(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmClearDiagnosticInformation(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmControlDTCSetting(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmDiagnosticSessionControl(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmEcuReset(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmCommunicationControl(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmRoutineControl(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmInputOutputControlByIdentifier(VAR( Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(void,DCM_CODE) Dcm_Dsp_SecaIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dcm_WDBIInit(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RdbiIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_ReadDTCInfo_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CDIIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CDTCSIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_DscIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_EcuReset_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_CCIni(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_RC_Ini(void);
extern FUNC(void,DCM_CODE) Dcm_Dsp_IOCBI_Ini(void);


extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserServiceModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint8,AUTOMATIC) Sid_u8);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserSubServiceModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint8,AUTOMATIC) Sid_u8,VAR(uint8,AUTOMATIC) Subfunc_u8);



extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint16,AUTOMATIC) did_u16,VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserRIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint16,AUTOMATIC) rid_u16, VAR(uint8,AUTOMATIC) subfunction_u8);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserCommCtrlReEnableModeRuleService(void);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDTCSettingEnableModeRuleService(void);

/* Extern declarations For DcmAppl SessionMode Switch function */
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmDiagnosticSessionControl(VAR(Dcm_SesCtrlType,AUTOMATIC) SessionMode);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmExecuteDscReset(VAR(uint8,AUTOMATIC) SessionLevel_u8);

/* Extern declarations For DcmAppl ResetMode Switch function */
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmEcuReset(VAR(uint8,AUTOMATIC) ResetMode);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmExecuteReset(void);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmExecuteEcuReset(VAR(uint8,AUTOMATIC) ResetType_u8);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmBootLoaderReset(void);
extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmSysSupplierReset(void);

extern FUNC(void,DCM_CODE)  DcmAppl_Switch_DcmDriveToDriveReset(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* _DCM_LCFG_DSLDSD_H */

