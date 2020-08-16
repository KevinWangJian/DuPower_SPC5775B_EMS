

#ifndef DCMDSPUDS_ER_PROT_H
#define DCMDSPUDS_ER_PROT_H

#define DCM_NO_RESET                           0x00u
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET  0x04u
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET 0x05u

#if (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
/* Definition of ECU reset service state machine values */
typedef enum
{
    DCM_ECURESET_IDLE=1,        /* Ecu Reset service is IDLE, not processing any resets */
    DCM_ECURESET_REQPERMISSION, /* State to check for reset permissions and send response */
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
    DCM_ECURESET_WAIT,          /* State to jumpt o bootloader */
#endif
    DCM_ECURESET_SENDRESPONSE,  /* State to send ecu reset response */
    DCM_ECURESET_ERROR          /* Some error occurred during processing of Service */
}Dcm_EcuResetStateType_ten;

/**
 * @ingroup  DCMDSP_UDS_EXTENDED
 * Dcm_ResetForBootType:\n
 * DCM_RESET_NO_BOOT = 0,    This reset Type doesn't allow to jump to Bootloader \n
 * DCM_RESET_SYS_BOOT,       This reset Type allows to jump to OEM Bootloader \n
 * DCM_SYS_BOOT,             This reset Type allows to jump to System Supplier Bootloader \n
 * DCM_RESET_DRIVE_TO_DRIVE  This reset Type allows to jump from Drive to Drive
 */
typedef enum
{
    DCM_RESET_NO_BOOT = 0, /* This reset Type doesn't allow to jump to Bootloader */
    DCM_RESET_OEM_BOOT,    /* This reset Type allows to jump to OEM Bootloader */
    DCM_RESET_SYS_BOOT,     /* This reset Type allows to jump to System Supplier Bootloader */
    DCM_RESET_DRIVE_TO_DRIVE /* This reset Type allows to jump from Drive to Drive */
}Dcm_ResetForBootType;

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_EcuResetStateType_ten,       DCM_VAR  ) Dcm_stEcuResetState_en; /*State machine control variable for ECU Reset service*/
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8            ,           DCM_VAR  ) Dcm_dataEcuRType_u8;     /* Variable to store the received reset type */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
typedef struct
{
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
	uint8 dataResetMode_u8;   /* RTE Mode for DcmEcuReset */
#endif
    uint8 dataResetLevel_u8;        /* Ecu Reset Type     */
    Dcm_ResetForBootType  resetForBoot;
}
Dcm_DspEcuReset_tst;
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_DspEcuReset_tst, DCM_CONST)Dcm_DspEcuResetType_cast[DCM_CFG_DSP_NUMRESETTYPE];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_Prv_DspEcuResetConfirmation(
	VAR(Dcm_IdContextType,AUTOMATIC) dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC) dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
														);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif /* #ifndef _DCMDSPUDS_ER_PROT_H */

