

#ifndef DCMDSPUDS_DSC_PUB_H
#define DCMDSPUDS_DSC_PUB_H

/**
 ***************************************************************************************************
            DSC service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)

/* Configuration of Diagnostic Session */
/**
 * @ingroup  DCMDSP_UDS_EXTENDED
 * Dcm_SessionForBootType:\n
 * DCM_NO_BOOT = 0,  This diagnostic session doesn't allow to jump to Bootloader \n
 * DCM_OEM_BOOT,     This diagnostic session allows to jump to OEM Bootloader \n
 * DCM_SYS_BOOT     This diagnostic session allows to jump to System Supplier Bootloader\n
 *
 */
typedef enum
{
    DCM_NO_BOOT = 0, /* This diagnostic session doesn't allow to jump to Bootloader */
    DCM_OEM_BOOT,    /* This diagnostic session allows to jump to OEM Bootloader */
    DCM_SYS_BOOT     /* This diagnostic session allows to jump to System Supplier Bootloader */
}Dcm_SessionForBootType;


/**
 *  @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsp_Session_t: Configuration of Diagnostic Session\n
 * uint32                   P2_max_u32;        P2 Server Max Timing\n
 * uint32                   P2str_max_u32;    P2* Server Max Timing\n
 * Dcm_SesCtrlType          session_level;    Session level Ex:0x01\n
 * Rte_ModeType_DcmDiagnosticSessionControl SessionMode;  Session Mode (Only if RTE enabled and RTE_VERSION!=DCM_PRV_AR_3_2_1 and RTE_VERSION!=DCM_PRV_AR_3_1_4)\n
 * Dcm_SessionForBootType   sessionForBoot;    Diagnostic session used for jump to Bootloader\n
 */
typedef struct
{
    uint32                   P2_max_u32;        /* P2 Server Max Timing      */
    uint32                   P2str_max_u32;     /* P2* Server Max Timing     */
    Dcm_SesCtrlType          session_level;     /* Session level Ex:0x01     */
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
	Rte_ModeType_DcmDiagnosticSessionControl SessionMode; /* Session Mode */
#endif
    Dcm_SessionForBootType   sessionForBoot;    /* Diagnostic session used for jump to Bootloader */
}
Dcm_Dsp_Session_t;
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *@ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsp_DscChgSession : This function performs the following\n
 *                     1. Check for Session transitions default - Non default etc\n
 *                     2. Updation of Session Timers\n
 *                     3. Activate New Session using Dcm_SetSessCtrlType.\n
 *                     4. Change the state of DSC state machine to DCM_DSP_DSC_INIT.\n
 *
 * @param[in]         status    Status of Tx confirmation function.
 * @retval            None
 *
 */
extern FUNC(void, DCM_CODE) Dcm_Prv_DspDscConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8
												   );
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_Dsp_Session_t, DCM_CONST) Dcm_Dsp_Session[DCM_CFG_DSP_NUMSESSIONS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *@ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetP2Timings :\n
 *  This API is used to get the timings of a particular session. This API is used in jump to boot\n
 *  feature implementation to retrieve the same session timings.\n
 *
 * @param [out]          dP2Timing_pu32: Pointer to P2max timings of the session requested\n
 * @param [out]          dP2StarTiming_pu32: Pointer to P2Starmax timings of the session requested\n
 * @param [in]           dSessionId_u8: Session Id for which timings have to be retrieved\n
 *
 * @retval          None
 *
 */
extern FUNC(void, DCM_CODE) Dcm_GetP2Timings(
                                                P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2Timing_pu32,
                                                P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2StarTiming_pu32,
                                                VAR(Dcm_SesCtrlType, AUTOMATIC) dSessionId
                                            );
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
#endif /* _DCMDSPUDS_DSC_PUB_H  */
