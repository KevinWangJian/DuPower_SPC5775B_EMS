

#ifndef DCMDSPUDS_WMBA_PUB_H
#define DCMDSPUDS_WMBA_PUB_H

/**
 ***************************************************************************************************
            Read Data By Id (RDBI) service
 ***************************************************************************************************
 */

#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_WmbaSupportRet_t:\n
 * DCM_WMBA_SUPPORT_OK,\n
 * DCM_WMBA_SUPPORT_SESSION_VIOLATED,\n
 * DCM_WMBA_SUPPORT_SECURITY_VIOLATED,\n
 * DCM_WMBA_SUPPORT_CONDITION_VIOLATED
 */
typedef enum
{
    DCM_WMBA_SUPPORT_OK,
    DCM_WMBA_SUPPORT_SESSION_VIOLATED,
    DCM_WMBA_SUPPORT_SECURITY_VIOLATED,
    DCM_WMBA_SUPPORT_CONDITION_VIOLATED
} Dcm_WmbaSupportRet_t;


#endif

#endif /* _DCMDSPUDS_WMBA_PUB_H  */
