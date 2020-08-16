

#ifndef DCMDSPUDS_RDTC_PUB_H
#define DCMDSPUDS_RDTC_PUB_H


/**
 ***************************************************************************************************
            Read DTC info (RDTC) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsp_RDTCInfoType: Configuration of Read DTC Information\n
 * P2FUNC(void,TYPEDEF,SubFunc_fp) (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA)); Function pointer for the subfunction\n
 * uint8    SubFuncLevel_u8;        SubFunction Level
 */

typedef struct
{
    P2FUNC(Std_ReturnType,TYPEDEF,SubFunc_fp) (VAR(Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));/* Function pointer for the subfunction             */
    uint8    SubFuncLevel_u8;                    /* SubFunction Level                                */
    boolean isDspRDTCSubFnc_b;				 	/* Is Dsp RDTC function or not*/
}Dcm_Dsp_RDTCInfoType;
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_Dsp_RDTCInfoType,DCM_CONST) DcmDspRDTCInfo[DCM_CFG_NUMRDTCSUBFUNC];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_RDTCPAGEDBUFFERSUPPORT != DCM_CFG_OFF) &&\
    ((DCM_CFG_DSP_RDTCSUBFUNC_0x02_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0A_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x15_ENABLED != DCM_CFG_OFF) ||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x08_ENABLED != DCM_CFG_OFF) ||\
	/* FC_VariationPoint_START */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x13_ENABLED != DCM_CFG_OFF)||\
	/* FC_VariationPoint_END */ \
    (DCM_CFG_DSP_RDTCSUBFUNC_0x0F_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x14_ENABLED != DCM_CFG_OFF)||\
    (DCM_CFG_DSP_RDTCSUBFUNC_0x17_ENABLED != DCM_CFG_OFF)))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsp_RDTCUpdatePage : This function is used to update the Page length and the Response buffer pointer .\n
 *
 * @param[in]       PageBufPtr    Pointer to response buffer\n
 * @param[in]       PageLen       Page length which can be filled\n
 *
 * @retval          None
 *
 */
extern FUNC(void,DCM_CODE) Dcm_Dsp_RDTCUpdatePage(
                                                    VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr,
                                                    VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
                                                 );
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsp_RDTCFillZero      :Used in  paged buffering to fill the  free space in  page buffer with Zeros.\n
 * @param[in]  RemTotalResLen: Remaining response bytes \n
 */
extern FUNC(void,DCM_CODE) Dcm_Dsp_RDTCFillZero (VAR(Dcm_MsgLenType,AUTOMATIC) RemTotalResLen);
extern FUNC(boolean,DCM_CODE) Dcm_IsProtocolIPCanFD(void);

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif  /* End of DCM_CFG_DSP_READDTCINFORMATION_ENABLED */

#endif /* _DCMDSPUDS_RDTC_PUB_H  */
