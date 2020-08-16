/**
* @file         Global_Define.h
* @author       Zhongsheng Ji
* @version      V1.0
* @date         2020.06.15 10:26:41
* @brief         
* @note          
* @attention    COPYRIGHT Fengchen
**/

#ifndef RTW_HEADER_Global_Define_h_
#define RTW_HEADER_Global_Define_h_
#include "rtwtypes.h"


#if 0
extern const boolean_T ASWTYPE_TRUE;
extern const boolean_T ASWTYPE_FALSE;
extern const boolean_T ASWTYPE_ACTIVE;
extern const boolean_T ASWTYPE_IDLE;
#endif


#define ASWTYPE_TRUE 1
#define ASWTYPE_FALSE 0
#define ASWTYPE_ACTIVE 1
#define ASWTYPE_IDLE 0
#define CELLVOLT_NUMB 13
#define CELLTEMP_NUMB 2
#define THERMTEMP_NUMB 0
#define PCBTEMP_NUMB 2


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAHVSysStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAHVSysStat_

typedef enum {
    Enum_BCRBMSAHVSysStat_Notready = 0,
    Enum_BCRBMSAHVSysStat_Standby,
    Enum_BCRBMSAHVSysStat_Precharge,
    Enum_BCRBMSAHVSysStat_Discharge,
	Enum_BCRBMSAHVSysStat_Charge,
	Enum_BCRBMSAHVSysStat_Powerdown,
	Enum_BCRBMSAHVSysStat_Error,
}Enum_BCRBMSAHVSysStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAMainNegCntStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAMainNegCntStat_

typedef enum {
    Enum_BCRBMSAMainNegCntStat_Open = 0,
    Enum_BCRBMSAMainNegCntStat_Close,
    Enum_BCRBMSAMainNegCntStat_Adhesion,
    Enum_BCRBMSAMainNegCntStat_NormallyOpen,
}Enum_BCRBMSAMainNegCntStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAMainPosCntStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAMainPosCntStat_

typedef enum {
    Enum_BCRBMSAMainPosCntStat_Open = 0,
    Enum_BCRBMSAMainPosCntStat_Close,
    Enum_BCRBMSAMainPosCntStat_Adhesion,
    Enum_BCRBMSAMainPosCntStat_NormallyOpen,
}Enum_BCRBMSAMainPosCntStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAPack1RechrgNegStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAPack1RechrgNegStat_

typedef enum {
    Enum_BCRBMSAPack1RechrgNegStat_Open = 0,
    Enum_BCRBMSAPack1RechrgNegStat_Close,
    Enum_BCRBMSAPack1RechrgNegStat_Adhesion,
    Enum_BCRBMSAPack1RechrgNegStat_NormallyOpen,
}Enum_BCRBMSAPack1RechrgNegStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAPack1RechrgPosStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSAPack1RechrgPosStat_

typedef enum {
    Enum_BCRBMSAPack1RechrgPosStat_Open = 0,
    Enum_BCRBMSAPack1RechrgPosStat_Close,
    Enum_BCRBMSAPack1RechrgPosStat_Adhesion,
    Enum_BCRBMSAPack1RechrgPosStat_NormallyOpen,
}Enum_BCRBMSAPack1RechrgPosStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBHVSysStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBHVSysStat_

typedef enum {
    Enum_BCRBMSBHVSysStat_Notready = 0,
    Enum_BCRBMSBHVSysStat_Standby,
    Enum_BCRBMSBHVSysStat_Precharge,
    Enum_BCRBMSBHVSysStat_Discharge,
	Enum_BCRBMSBHVSysStat_Charge,
	Enum_BCRBMSBHVSysStat_Powerdown,
	Enum_BCRBMSBHVSysStat_Error,
}Enum_BCRBMSBHVSysStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBMainNegCntStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBMainNegCntStat_

typedef enum {
    Enum_BCRBMSBMainNegCntStat_Open = 0,
    Enum_BCRBMSBMainNegCntStat_Close,
    Enum_BCRBMSBMainNegCntStat_Adhesion,
    Enum_BCRBMSBMainNegCntStat_NormallyOpen,
}Enum_BCRBMSBMainNegCntStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBMainPosCntStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBMainPosCntStat_

typedef enum {
    Enum_BCRBMSBMainPosCntStat_Open = 0,
    Enum_BCRBMSBMainPosCntStat_Close,
    Enum_BCRBMSBMainPosCntStat_Adhesion,
    Enum_BCRBMSBMainPosCntStat_NormallyOpen,
}Enum_BCRBMSBMainPosCntStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBPack1RechrgNegStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBPack1RechrgNegStat_

typedef enum {
    Enum_BCRBMSBPack1RechrgNegStat_Open = 0,
    Enum_BCRBMSBPack1RechrgNegStat_Close,
    Enum_BCRBMSBPack1RechrgNegStat_Adhesion,
    Enum_BCRBMSBPack1RechrgNegStat_NormallyOpen,
}Enum_BCRBMSBPack1RechrgNegStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBPack1RechrgPosStat_
#define _DEFINED_TYPEDEF_FOR_Enum_BCRBMSBPack1RechrgPosStat_

typedef enum {
    Enum_BCRBMSBPack1RechrgPosStat_Open = 0,
    Enum_BCRBMSBPack1RechrgPosStat_Close,
    Enum_BCRBMSBPack1RechrgPosStat_Adhesion,
    Enum_BCRBMSBPack1RechrgPosStat_NormallyOpen,
}Enum_BCRBMSBPack1RechrgPosStat;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCSBMSABMSCntctrReq_
#define _DEFINED_TYPEDEF_FOR_Enum_BCSBMSABMSCntctrReq_

typedef enum {
    Enum_EBSBMSABMSCntctrReq_RequestChrgCntOpen = 0,
    Enum_EBSBMSABMSCntctrReq_RequestChrgCntClose,
    Enum_EBSBMSABMSCntctrReq_Undetermined,
}Enum_BCSBMSABMSCntctrReq;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_BCSBMSBBMSCntctrReq_
#define _DEFINED_TYPEDEF_FOR_Enum_BCSBMSBBMSCntctrReq_

typedef enum {
    Enum_EBSBMSBBMSCntctrReq_RequestChrgCntOpen = 0,
    Enum_EBSBMSBBMSCntctrReq_RequestChrgCntClose,
    Enum_EBSBMSBBMSCntctrReq_Undetermined,
}Enum_BCSBMSBBMSCntctrReq;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACCACDCARunMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EACCACDCARunMode_

typedef enum {
    Enum_EACCACDCARunMode_Offline = 0,
    Enum_EACCACDCARunMode_Standby,
    Enum_EACCACDCARunMode_Prechrg,
    Enum_EACCACDCARunMode_Run,
}Enum_EACCACDCARunMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACCACDCBRunMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EACCACDCBRunMode_

typedef enum {
    Enum_EACCACDCBRunMode_Offline = 0,
    Enum_EACCACDCBRunMode_Standby,
    Enum_EACCACDCBRunMode_Prechrg,
    Enum_EACCACDCBRunMode_Run,
}Enum_EACCACDCBRunMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACMCCU1CCVChargeType_
#define _DEFINED_TYPEDEF_FOR_Enum_EACMCCU1CCVChargeType_

typedef enum {
    Enum_EACMCCU1CCVChargeType_No = 0,
    Enum_EACMCCU1CCVChargeType_CreditCard,
    Enum_EACMCCU1CCVChargeType_RFCard,
    Enum_EACMCCU1CCVChargeType_APP,
    Enum_EACMCCU1CCVChargeType_SWCode,
}Enum_EACMCCU1CCVChargeType;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACMCCU1MCVCardType_
#define _DEFINED_TYPEDEF_FOR_Enum_EACMCCU1MCVCardType_
typedef enum {
    Enum_EACMCCU1MCVCardType_None = 0,
    Enum_EACMCCU1MCVCardType_CrdtCrd,
    Enum_EACMCCU1MCVCardType_RFIDCrd,
}Enum_EACMCCU1MCVCardType;
#endif
#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACMCCU2CCVChargeType_
#define _DEFINED_TYPEDEF_FOR_Enum_EACMCCU2CCVChargeType_

typedef enum {
    Enum_EACMCCU2CCVChargeType_No = 0,
    Enum_EACMCCU2CCVChargeType_CreditCard,
    Enum_EACMCCU2CCVChargeType_RFCard,
    Enum_EACMCCU2CCVChargeType_APP,
    Enum_EACMCCU2CCVChargeType_SWCode,
}Enum_EACMCCU2CCVChargeType;
#endif
#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACMCCU2MCVCardType_
#define _DEFINED_TYPEDEF_FOR_Enum_EACMCCU2MCVCardType_
typedef enum {
    Enum_EACMCCU2MCVCardType_None = 0,
    Enum_EACMCCU2MCVCardType_CrdtCrd,
    Enum_EACMCCU2MCVCardType_RFIDCrd,
}Enum_EACMCCU2MCVCardType;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EACMCCVFaultState_
#define _DEFINED_TYPEDEF_FOR_Enum_EACMCCVFaultState_

typedef enum {
    Enum_EACMCCVFaultState_No = 0,
    Enum_EACMCCVFaultState_MachineFault,
    Enum_EACMCCVFaultState_CardFault,
}Enum_EACMCCVFaultState;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EAMMACDCAWorkMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EAMMACDCAWorkMode_

typedef enum {
    Enum_EAMMACDCAWorkMode_Offline = 0,
    Enum_EAMMACDCAWorkMode_GunA,
    Enum_EAMMACDCAWorkMode_GunB,
    Enum_EAMMACDCAWorkMode_PackA,
    Enum_EAMMACDCAWorkMode_PackB,
    Enum_EAMMACDCAWorkMode_TMS,
}Enum_EAMMACDCAWorkMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EAMMACDCBWorkMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EAMMACDCBWorkMode_

typedef enum {
    Enum_EAMMACDCBWorkMode_Offline = 0,
    Enum_EAMMACDCBWorkMode_GunA,
    Enum_EAMMACDCBWorkMode_GunB,
    Enum_EAMMACDCBWorkMode_PackA,
    Enum_EAMMACDCBWorkMode_PackB,
    Enum_EAMMACDCBWorkMode_TMS,
}Enum_EAMMACDCBWorkMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBCRHVSystemStatus_
#define _DEFINED_TYPEDEF_FOR_Enum_EBCRHVSystemStatus_

typedef enum {
    Enum_EBCRHVSystemStatus_NotReady = 0,
    Enum_EBCRHVSystemStatus_Standby,
    Enum_EBCRHVSystemStatus_PreChg,
    Enum_EBCRHVSystemStatus_DisChg,
    Enum_EBCRHVSystemStatus_Chg,
    Enum_EBCRHVSystemStatus_Powerdown,
    Enum_EBCRHVSystemStatus_Error,
}Enum_EBCRHVSystemStatus;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBCRMainNegCntState_
#define _DEFINED_TYPEDEF_FOR_Enum_EBCRMainNegCntState_

typedef enum {
    Enum_EBCRMainNegCntState_Open = 0,
    Enum_EBCRMainNegCntState_Close,
    Enum_EBCRMainNegCntState_CloseFlt,
    Enum_EBCRMainNegCntState_OpenFlt,
}Enum_EBCRMainNegCntState;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBCRMainPosCntState_
#define _DEFINED_TYPEDEF_FOR_Enum_EBCRMainPosCntState_

typedef enum {
    Enum_EBCRMainPosCntState_Open = 0,
    Enum_EBCRMainPosCntState_Close,
    Enum_EBCRMainPosCntState_CloseFlt,
    Enum_EBCRMainPosCntState_OpenFlt,
}Enum_EBCRMainPosCntState;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBSWACDCAFltLvl_
#define _DEFINED_TYPEDEF_FOR_Enum_EBSWACDCAFltLvl_

typedef enum {
    Enum_EBSWACDCAFltLvl_Normal = 0,
    Enum_EBSWACDCAFltLvl_Warning,
    Enum_EBSWACDCAFltLvl_Alarm,
    Enum_EBSWACDCAFltLvl_Res,
}Enum_EBSWACDCAFltLvl;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBSWACDCBFltLvl_
#define _DEFINED_TYPEDEF_FOR_Enum_EBSWACDCBFltLvl_

typedef enum {
    Enum_EBSWACDCBFltLvl_Normal = 0,
    Enum_EBSWACDCBFltLvl_Warning,
    Enum_EBSWACDCBFltLvl_Alarm,
    Enum_EBSWACDCBFltLvl_Res,
}Enum_EBSWACDCBFltLvl;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBSWDCDCAFltLvl_
#define _DEFINED_TYPEDEF_FOR_Enum_EBSWDCDCAFltLvl_

typedef enum {
    Enum_EBSWDCDCAFltLvl_Normal = 0,
    Enum_EBSWDCDCAFltLvl_Warning,
    Enum_EBSWDCDCAFltLvl_Alarm,
    Enum_EBSWDCDCAFltLvl_Res,
}Enum_EBSWDCDCAFltLvl;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBSWDCDCBFltLvl_
#define _DEFINED_TYPEDEF_FOR_Enum_EBSWDCDCBFltLvl_

typedef enum {
    Enum_EBSWDCDCBFltLvl_Normal = 0,
    Enum_EBSWDCDCBFltLvl_Warning,
    Enum_EBSWDCDCBFltLvl_Alarm,
    Enum_EBSWDCDCBFltLvl_Res,
}Enum_EBSWDCDCBFltLvl;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EBSWTPState_
#define _DEFINED_TYPEDEF_FOR_Enum_EBSWTPState_

typedef enum {
    Enum_EBSWTPState_Idle = 0,
    Enum_EBSWTPState_Work,
    Enum_EBSWTPState_BusErr,
    Enum_EBSWTPState_Fault,
}Enum_EBSWTPState;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU1CCUCC1State_
#define _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU1CCUCC1State_

typedef enum {
    Enum_ECCRCCU1CCUCC1State_NoConnect = 0,
    Enum_ECCRCCU1CCUCC1State_HalfConnect,
    Enum_ECCRCCU1CCUCC1State_FullConnect,
}Enum_ECCRCCU1CCUCC1State;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU1State_
#define _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU1State_

typedef enum {
    Enum_ECCRCCU1State_NotReady = 0,
    Enum_ECCRCCU1State_Standby,
    Enum_ECCRCCU1State_ISOdetect,
    Enum_ECCRCCU1State_PreChg,
    Enum_ECCRCCU1State_Chging,
    Enum_ECCRCCU1State_StopChg,
    Enum_ECCRCCU1State_ChgFault,
    Enum_ECCRCCU1State_Powerdown,
}Enum_ECCRCCU1State;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU2CCUCC1State_
#define _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU2CCUCC1State_

typedef enum {
    Enum_ECCRCCU2CCUCC1State_NoConnect = 0,
    Enum_ECCRCCU2CCUCC1State_HalfConnect,
    Enum_ECCRCCU2CCUCC1State_FullConnect,
}Enum_ECCRCCU2CCUCC1State;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU2State_
#define _DEFINED_TYPEDEF_FOR_Enum_ECCRCCU2State_

typedef enum {
    Enum_ECCRCCU2State_NotReady = 0,
    Enum_ECCRCCU2State_Standby,
    Enum_ECCRCCU2State_ISOdetect,
    Enum_ECCRCCU2State_PreChg,
    Enum_ECCRCCU2State_Chging,
    Enum_ECCRCCU2State_StopChg,
    Enum_ECCRCCU2State_ChgFault,
    Enum_ECCRCCU2State_Powerdown,
}Enum_ECCRCCU2State;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECECCCU1ChargeStatus_
#define _DEFINED_TYPEDEF_FOR_Enum_ECECCCU1ChargeStatus_

typedef enum {
    Enum_ECECCCU1ChargeStatus_NoCharge = 0,
    Enum_ECECCCU1ChargeStatus_Charging,
    Enum_ECECCCU1ChargeStatus_CompleCharge,
}Enum_ECECCCU1ChargeStatus;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECECCCU2ChargeStatus_
#define _DEFINED_TYPEDEF_FOR_Enum_ECECCCU2ChargeStatus_

typedef enum {
    Enum_ECECCCU2ChargeStatus_NoCharge  = 0,
    Enum_ECECCCU2ChargeStatus_Charging,
    Enum_ECECCCU2ChargeStatus_CompleCharge,
}Enum_ECECCCU2ChargeStatus;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECECChargeType_
#define _DEFINED_TYPEDEF_FOR_Enum_ECECChargeType_

typedef enum {
    Enum_ECECChargeType_No = 0,
    Enum_ECECChargeType_Time,
    Enum_ECECChargeType_Energe,
    Enum_ECECChargeType_Rate,
    Enum_ECECChargeType_AutoFullCharge,
}Enum_ECECChargeType;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECIMGunAIntactMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECIMGunAIntactMode_

typedef enum {
    Enum_ECIMGunAIntactMode_Offline = 0,
    Enum_ECIMGunAIntactMode_ISO,
    Enum_ECIMGunAIntactMode_Unload,
    Enum_ECIMGunAIntactMode_BCP,
    Enum_ECIMGunAIntactMode_BCL,
}Enum_ECIMGunAIntactMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECIMGunBIntactMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECIMGunBIntactMode_

typedef enum {
    Enum_ECIMGunBIntactMode_Offline = 0,
    Enum_ECIMGunBIntactMode_ISO,
    Enum_ECIMGunBIntactMode_Unload,
    Enum_ECIMGunBIntactMode_BCP,
    Enum_ECIMGunBIntactMode_BCL,
}Enum_ECIMGunBIntactMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECMMChrgCtrAMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECMMChrgCtrAMode_

typedef enum {
    Enum_ECMMChrgCtrAMode_Offline = 0,
    Enum_ECMMChrgCtrAMode_Idle,
    Enum_ECMMChrgCtrAMode_Chrg,
    Enum_ECMMChrgCtrAMode_ReChrg,
    Enum_ECMMChrgCtrAMode_CChrg,
    Enum_ECMMChrgCtrAMode_BCChrg,
}Enum_ECMMChrgCtrAMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECMMChrgCtrBMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECMMChrgCtrBMode_

typedef enum {
    Enum_ECMMChrgCtrBMode_Offline = 0,
    Enum_ECMMChrgCtrBMode_Idle,
    Enum_ECMMChrgCtrBMode_Chrg,
    Enum_ECMMChrgCtrBMode_ReChrg,
    Enum_ECMMChrgCtrBMode_CChrg,
    Enum_ECMMChrgCtrBMode_BCChrg,
}Enum_ECMMChrgCtrBMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCBCChrgCtrAMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCBCChrgCtrAMode_

typedef enum {
    Enum_ECTCBCChrgCtrAMode_Offline = 0,
    Enum_ECTCBCChrgCtrAMode_Prechrg,
    Enum_ECTCBCChrgCtrAMode_Online,
    Enum_ECTCBCChrgCtrAMode_Preshut,
    Enum_ECTCBCChrgCtrAMode_Shutdown,
}Enum_ECTCBCChrgCtrAMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCBCChrgCtrBMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCBCChrgCtrBMode_

typedef enum {
    Enum_ECTCBCChrgCtrBMode_Offline = 0,
    Enum_ECTCBCChrgCtrBMode_Prechrg,
    Enum_ECTCBCChrgCtrBMode_Online,
    Enum_ECTCBCChrgCtrBMode_Preshut,
    Enum_ECTCBCChrgCtrBMode_Shutdown,
}Enum_ECTCBCChrgCtrBMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCCChrgCtrAMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCCChrgCtrAMode_

typedef enum {
    Enum_ECTCCChrgCtrAMode_Offline = 0,
    Enum_ECTCCChrgCtrAMode_Prechrg,
    Enum_ECTCCChrgCtrAMode_Online,
    Enum_ECTCCChrgCtrAMode_Preshut,
    Enum_ECTCCChrgCtrAMode_Shutdown,
}Enum_ECTCCChrgCtrAMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCCChrgCtrBMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCCChrgCtrBMode_

typedef enum {
    Enum_ECTCCChrgCtrBMode_Offline = 0,
    Enum_ECTCCChrgCtrBMode_Prechrg,
    Enum_ECTCCChrgCtrBMode_Online,
    Enum_ECTCCChrgCtrBMode_Preshut,
    Enum_ECTCCChrgCtrBMode_Shutdown,
}Enum_ECTCCChrgCtrBMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCReChrgCtrAMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCReChrgCtrAMode_

typedef enum {
    Enum_ECTCReChrgCtrAMode_Offline = 0,
    Enum_ECTCReChrgCtrAMode_Prechrg,
    Enum_ECTCReChrgCtrAMode_Online,
    Enum_ECTCReChrgCtrAMode_Preshut,
    Enum_ECTCReChrgCtrAMode_Shutdown,
}Enum_ECTCReChrgCtrAMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ECTCReChrgCtrBMode_
#define _DEFINED_TYPEDEF_FOR_Enum_ECTCReChrgCtrBMode_

typedef enum {
    Enum_ECTCReChrgCtrBMode_Offline = 0,
    Enum_ECTCReChrgCtrBMode_Prechrg,
    Enum_ECTCReChrgCtrBMode_Online,
    Enum_ECTCReChrgCtrBMode_Preshut,
    Enum_ECTCReChrgCtrBMode_Shutdown,
}Enum_ECTCReChrgCtrBMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EDCCDCDCARunMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EDCCDCDCARunMode_

typedef enum {
    Enum_EDCCDCDCARunMode_Offline = 0,
    Enum_EDCCDCDCARunMode_Standby,
    Enum_EDCCDCDCARunMode_Run,
}Enum_EDCCDCDCARunMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EDCCDCDCBRunMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EDCCDCDCBRunMode_

typedef enum {
    Enum_EDCCDCDCBRunMode_Offline = 0,
    Enum_EDCCDCDCBRunMode_Standby,
    Enum_EDCCDCDCBRunMode_Run,
}Enum_EDCCDCDCBRunMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EEPMPowerFaultLevel_
#define _DEFINED_TYPEDEF_FOR_Enum_EEPMPowerFaultLevel_

typedef enum {
    Enum_EEPMPowerFaultLevel_NoFault = 0,
    Enum_EEPMPowerFaultLevel_PLowFault,
    Enum_EEPMPowerFaultLevel_PHighFault,
    Enum_EEPMPowerFaultLevel_PLowMinFault,
    Enum_EEPMPowerFaultLevel_PHignMaxFault,
}Enum_EEPMPowerFaultLevel;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EETMHeatMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EETMHeatMode_

typedef enum {
    Enum_EETMHeatMode_NotReady = 0,
    Enum_EETMHeatMode_OffLine,
    Enum_EETMHeatMode_Standby,
    Enum_EETMHeatMode_SelfCirculation,
    Enum_EETMHeatMode_Cold,
    Enum_EETMHeatMode_Heat,
}Enum_EETMHeatMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EHCRHCUSystemMode_
#define _DEFINED_TYPEDEF_FOR_Enum_EHCRHCUSystemMode_

typedef enum {
    Enum_EHCRHCUSystemMode_Standby = 0,
    Enum_EHCRHCUSystemMode_PackCold,
    Enum_EHCRHCUSystemMode_PackHeat,
    Enum_EHCRHCUSystemMode_LiquidModuleCold,
    Enum_EHCRHCUSystemMode_Pack_LiquidModuleCold,
    Enum_EHCRHCUSystemMode_Reserved,
    Enum_EHCRHCUSystemMode_Fault,
    Enum_EHCRHCUSystemMode_SelfLoop,
}Enum_EHCRHCUSystemMode;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_EHVSHVSState_
#define _DEFINED_TYPEDEF_FOR_Enum_EHVSHVSState_

typedef enum {
    Enum_EHVSHVSState_Offline = 0,
    Enum_EHVSHVSState_LineA,
    Enum_EHVSHVSState_LineB,
    Enum_EHVSHVSState_SLVS,
}Enum_EHVSHVSState;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Enum_ETCRTBOXCCU1OcppAvailability_
#define _DEFINED_TYPEDEF_FOR_Enum_ETCRTBOXCCU1OcppAvailability_

typedef enum {
    Enum_ETCRTBOXCCU1OcppAvailability_Invalid = 0,
    Enum_ETCRTBOXCCU1OcppAvailability_Avlbl,
    Enum_ETCRTBOXCCU1OcppAvailability_UnAvlbl,
}Enum_ETCRTBOXCCU1OcppAvailability;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ETCRTBOXCCU2OcppAvailability_
#define _DEFINED_TYPEDEF_FOR_Enum_ETCRTBOXCCU2OcppAvailability_

typedef enum {
    Enum_ETCRTBOXCCU2OcppAvailability_Invalid = 0,
    Enum_ETCRTBOXCCU2OcppAvailability_Avlbl,
    Enum_ETCRTBOXCCU2OcppAvailability_UnAvlbl,
}Enum_ETCRTBOXCCU2OcppAvailability;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ETIMOCPPCCU1State_
#define _DEFINED_TYPEDEF_FOR_Enum_ETIMOCPPCCU1State_

typedef enum {
    
    Enum_ETIMOCPPCCU1State_Avalbl = 1,
    Enum_ETIMOCPPCCU1State_Prprg,
    Enum_ETIMOCPPCCU1State_Chrgng,
    Enum_ETIMOCPPCCU1State_Fnshng = 6,
	Enum_ETIMOCPPCCU1State_Unvalbl = 8,
    Enum_ETIMOCPPCCU1State_Flt,
}Enum_ETIMOCPPCCU1State;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_ETIMOCPPCCU2State_
#define _DEFINED_TYPEDEF_FOR_Enum_ETIMOCPPCCU2State_

typedef enum {
    
    Enum_ETIMOCPPCCU2State_Avalbl = 1,
    Enum_ETIMOCPPCCU2State_Prprg,
    Enum_ETIMOCPPCCU2State_Chrgng,
    Enum_ETIMOCPPCCU2State_Fnshng = 6,
	Enum_ETIMOCPPCCU2State_Unvalbl = 8,
    Enum_ETIMOCPPCCU2State_Flt,
}Enum_ETIMOCPPCCU2State;

#endif
#ifndef _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU1CCUCC1STATE_
#define _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU1CCUCC1STATE_

typedef enum {
    Enum_GeECCR_CCU1CCUCC1STATE_Non_Connected = 0,
    Enum_GeECCR_CCU1CCUCC1STATE_Half_Connected,
    Enum_GeECCR_CCU1CCUCC1STATE_Fully_Connected,
}Enum_GeECCR_CCU1CCUCC1STATE;

#endif
#ifndef _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU1CCUSTATE_
#define _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU1CCUSTATE_

typedef enum {
    Enum_GeECCR_CCU1CCUSTATE_NotReady = 0,
    Enum_GeECCR_CCU1CCUSTATE_Standby,
    Enum_GeECCR_CCU1CCUSTATE_ISO,
    Enum_GeECCR_CCU1CCUSTATE_PreCharge,
    Enum_GeECCR_CCU1CCUSTATE_Charge,
    Enum_GeECCR_CCU1CCUSTATE_PowerDown,
    Enum_GeECCR_CCU1CCUSTATE_Fault,
}Enum_GeECCR_CCU1CCUSTATE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU2CCUCC1STATE_
#define _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU2CCUCC1STATE_

typedef enum {
    Enum_GeECCR_CCU2CCUCC1STATE_Non_Connected = 0,
    Enum_GeECCR_CCU2CCUCC1STATE_Half_Connected,
    Enum_GeECCR_CCU2CCUCC1STATE_Fully_Connected,
}Enum_GeECCR_CCU2CCUCC1STATE;

#endif


#ifndef _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU2CCUSTATE_
#define _DEFINED_TYPEDEF_FOR_Enum_GeECCR_CCU2CCUSTATE_

typedef enum {
    Enum_GeECCR_CCU2CCUSTATE_NotReady = 0,
    Enum_GeECCR_CCU2CCUSTATE_Standby,
    Enum_GeECCR_CCU2CCUSTATE_ISO,
    Enum_GeECCR_CCU2CCUSTATE_PreCharge,
    Enum_GeECCR_CCU2CCUSTATE_Charge,
    Enum_GeECCR_CCU2CCUSTATE_PowerDown,
    Enum_GeECCR_CCU2CCUSTATE_Fault,
}Enum_GeECCR_CCU2CCUSTATE;

#endif

#ifndef _DEFINED_TYPEDEF_FOR_Enum_EHCSEMSHeatModeSelect_
#define _DEFINED_TYPEDEF_FOR_Enum_EHCSEMSHeatModeSelect_

typedef enum {
	Enum_EHCSEMSHeatModeSelect_Standby = 0,
	Enum_EHCSEMSHeatModeSelect_PackCold,
	Enum_EHCSEMSHeatModeSelect_PackHeat,
	Enum_EHCSEMSHeatModeSelect_LiquidCold,
	Enum_EHCSEMSHeatModeSelect_PackLiquidCold,
	Enum_EHCSEMSHeatModeSelect_Reserved,
	Enum_EHCSEMSHeatModeSelect_Reserved2,
	Enum_EHCSEMSHeatModeSelect_SelfLoop,
}Enum_EHCSEMSHeatModeSelect;

#endif
#endif
/********************* (C) COPYRIGHT Fengchen *******END OF FILE ********/
