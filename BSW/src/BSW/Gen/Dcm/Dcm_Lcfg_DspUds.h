
#ifndef DCM_LCFG_DSPUDS_H
#define DCM_LCFG_DSPUDS_H
/*
 ***************************************************************************************************
 *    DCM Appl API Prototyes generated from configuration
 ***************************************************************************************************
*/
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_DidServices_F186_ReadData(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrData_pu8);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/***Extern declarations to obtain NRC value from the application in case of E_NOT_OK return from ReadData API ***/
extern FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmReadDataNRC(VAR(uint16,AUTOMATIC)Did,VAR(uint32,AUTOMATIC)DidSignalPosn,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);


 /***Extern declarations for XXX_ReadData of type USE_DATA_SYNCH_FNC ***/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_0101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F183 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F187 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F190 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F18B (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F18C (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F191 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F194 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A1 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A2 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A3 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A4 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A5 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F1A6 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C001 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C002 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C003 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C004 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C005 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C006 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C007 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C008 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C009 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C010 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C011 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_C012 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D102 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D103 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D104 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D105 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D106 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D107 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D108 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D109 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D110 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D111 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D112 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D113 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D114 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D115 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D116 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D117 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D118 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D119 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D120 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D121 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D122 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_D123 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E100 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E101 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E102 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E103 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_F186 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataReadFnc_E104 (P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);

 






extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F187 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F190 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F18B (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F18C (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F191 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A2 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A3 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A4 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A5 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_F1A6 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C001 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C002 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C003 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C004 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C005 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C006 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C007 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C008 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C009 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C010 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C011 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspDataWriteFnc_C012 (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);





/***Extern declarations for XXX_FreezeCurrentStateFnc of type USE_DATA_SYNCH_FNC ***/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_FreezeCurrentState_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);


/***Extern declarations for XXX_ResetToDefaultFnc of type USE_DATA_SYNCH_FNC ***/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ResetToDefault_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/***Extern declarations for ReturnControlToEcuFnc.Only Synchronous API is used irrespective of UsePort Configuration to USE_DATA_SYNCH_FNC or USE_DATA_ASYNCH_FNC **/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ReturnControlToEcu_Fnc (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/***Extern declarations for ShortTermAdjustmentFnc of type USE_DATA_SYNCH_FNC  for Fixed LENGTH with no control mask or internal control mask handling***/
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_0101_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D107_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D108_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D109_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D111_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D113_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D115_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D116_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D121_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D122_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmDspData_D123_ShortTermAdjustment_Fnc (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);



/***Extern declarations for ShortTermAdjustmentFnc of type USE_DATA_SYNCH_FNC  for variable LENGTH with no control mask or internal control mask handling***/












/***Routine control Appl functions***/








/*** Extern declaration for DcmDspStartRoutine_4AF0 ***/
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DcmDspStartRoutine_4AF0(
VAR(uint8, AUTOMATIC) dataIn1,
                         VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
                         P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) dataOut1,
                          P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode);



/***Seca dcmDspSecurityGetSeedFnc functions with Useport  USE_ASYNCH_FNC ***/
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L1_GetSeed(VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,VAR(uint8,AUTOMATIC) Seedlen_u8,VAR(uint8,AUTOMATIC) AccDataRecsize_u8,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L2_GetSeed(VAR(Dcm_SecLevelType,AUTOMATIC) SecLevel_u8,VAR(uint8,AUTOMATIC) Seedlen_u8,VAR(uint8,AUTOMATIC) AccDataRecsize_u8,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) SecurityAccessDataRecord,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Seed,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/***Seca dcmDspSecurityCompareKeyFnc functions with Useport  USE_ASYNCH_FNC ***/
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L1_CompareKey(VAR(uint8,AUTOMATIC) KeyLen,P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) DCM_SEC_LEV_L2_CompareKey(VAR(uint8,AUTOMATIC) KeyLen,P2VAR(uint8,AUTOMATIC,DCM_INTERN_CONST) Key,VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);



#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* DCM_LCFG_DSPUDS_H */



