

#ifndef DCMDSPUDS_CDTCS_PUB_H
#define DCMDSPUDS_CDTCS_PUB_H

/**
 ***************************************************************************************************
            Control DTC setting  service
 ***************************************************************************************************
 */

#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Position of subfunction in the request
 */
#define DCM_PRV_CDTC_POSITION_SUBFUNC    0x00u
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Length of request
 */
#define DCM_PRV_CDTC_REQUEST_LENGTH      0x01u

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Length of the control option record
 */
#define DCM_PRV_CDTC_RECORD_LENGTH      0x03u
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * DTC OFF
 */
#define DCM_PRV_CDTC_OFF                 0x02u
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * DTC ON
 */
#define DCM_PRV_CDTC_ON                  0x01u
#if (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Function to get the status of control dtc setting\n
 * Returns true, if Dtc setting is enabled\n
 * and returns false if dtc setting is disabled\n
 * Can be used by other SWCs and BSW modules in case RTE is not supported\n
 * @param[in] None\n
 * @retval None
 */
extern FUNC(boolean,DCM_CODE) Dcm_GetControlDTCSetting_EnableStatus(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif	/* (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)*/

/* FC_VariationPoint_START */
                /*Obsolete*/
#ifndef     DCM_CDTC_POSITION_SUBFUNC
#define     DCM_CDTC_POSITION_SUBFUNC   DCM_PRV_CDTC_POSITION_SUBFUNC
#endif
#ifndef     DCM_CDTC_REQUEST_LENGTH
#define     DCM_CDTC_REQUEST_LENGTH     DCM_PRV_CDTC_REQUEST_LENGTH
#endif
#ifndef     DCM_CDTC_OFF
#define     DCM_CDTC_OFF                DCM_PRV_CDTC_OFF
#endif
#ifndef     DCM_CDTC_ON
#define     DCM_CDTC_ON                 DCM_PRV_CDTC_ON
#endif
/* FC_VariationPoint_END */

#endif  /* _DCMDSPUDS_CDTCS_PUB_H */
