

#ifndef DCMDSPUDS_IOCBI_PROT_H
#define DCMDSPUDS_IOCBI_PROT_H


/**
 ***************************************************************************************************
            Input Output Control By Identifier (IOCBI) service
 ***************************************************************************************************
 */

#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
/*synch c/s and control mask is NO_MASK*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu1_pfct)
		                     (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu2_pfct)
		                     (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
		                      P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
/*synch c/s and control mask is internal*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
/*Asynch c/s and control mask is external*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu6_pfct)
                              (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                     VAR(uint8,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                     VAR(uint16,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReturnControlEcu8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                     VAR(uint32,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);


/*synch fnc and asycnh fnc and control mask is NO_MASK*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault1_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault2_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/*synch c/s and control mask is internal*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
/*Asynch c/s and control mask is external*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault6_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/*synch fnc and asycnh fnc and control mask is NO_MASK*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState1_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState2_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/*synch c/s and control mask is internal*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState3_pfct)
                             (VAR(uint8,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState4_pfct)
                             (VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState5_pfct)
                             (VAR(uint32,AUTOMATIC) controlMask,
                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
/*Asynch c/s and control mask is external*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState6_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState7_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState8_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);


/*synch fnc and asycnh fnc and control mask is NO_MASK*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment1_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment2_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/*synch c/s and control mask is internal*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment3_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(uint8,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment4_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment5_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(uint32,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
/*Asynch c/s and control mask is external*/
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment6_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment7_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment8_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask,
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#if(DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment9_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment10_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment11_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment12_pfct)
                             (P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlStateInfo,
                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ShortTermAdjustment13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState9_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState10_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState11_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState12_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, FreezeCurrentState13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault9_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault10_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint8,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault11_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint16,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault12_pfct)
                             (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                              VAR(uint32,AUTOMATIC) controlMask);
typedef P2FUNC(Std_ReturnType,TYPEDEF, ResetToDefault13_pfct)
                             (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,IOControlrequest_pfct)
                                        ( VAR(Dcm_InputOutputControlParameterType,AUTOMATIC) IoctrlParam,
                                        P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData,
                                        VAR(uint16,AUTOMATIC)  dataSignalLength_u16,
                                        VAR(uint8,AUTOMATIC)  controlMaskLength_u8,
                                        VAR(Dcm_OpStatusType, AUTOMATIC) IocbiOpStatus_u8,
                                        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif

/* Definitions of states of IOCBI service */
typedef enum
{
    DCM_IOCBI_IDLESTATE,              		        /* Idle state */
    DCM_IOCBI_FCS_ACTIVE,						/* Freeze current state for a DID is active */
    DCM_IOCBI_FCS_PENDING,						/* Freeze current state for a DID is pending */
    DCM_IOCBI_RTD_ACTIVE,						/* Reset to default state for a DID is active */
    DCM_IOCBI_RTD_PENDING,         				/* Reset to default state for a DID is pending*/
    DCM_IOCBI_STA_ACTIVE,          				/* Short term adjustment for a DID is active */
    DCM_IOCBI_STA_PENDING,             			/* Short term adjustment for a DID is pending */
    DCM_IOCBI_RCE_ACTIVE,              			/* Return Control To Ecu for a DID is active*/
    DCM_IOCBI_RCE_PENDING             			/* Return Control To Ecu for a DID is pending*/
  }Dcm_Dsp_IocbiDidStatus_ten;

/*Structure to store the index of IOCBI DIDs and their status*/
typedef struct
{
	uint16    	idxindex_u16;
	Dcm_Dsp_IocbiDidStatus_ten IocbiStatus_en;
} Dcm_Dsp_IocbiStatusType_tst;


/**
 **********************************************************************************************************************
		Array for storing Active IOCBI DIDs and their active status
 **********************************************************************************************************************
**/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_Dsp_IocbiStatusType_tst,DCM_VAR) DcmDsp_IocbiStatus_array[DCM_CFG_NUM_IOCBI_DIDS];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_ResetActiveIoCtrl(VAR (uint32,AUTOMATIC) dataSessionMask_u32,
												 VAR (uint32,AUTOMATIC) dataSecurityMask_u32,
												 VAR (boolean,AUTOMATIC) flgSessChkReqd_b);
extern FUNC(void, DCM_CODE) Dcm_Prv_DspIOCBIConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
													    );
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif   /* _DCMDSPUDS_IOCBI_PROT_H */

