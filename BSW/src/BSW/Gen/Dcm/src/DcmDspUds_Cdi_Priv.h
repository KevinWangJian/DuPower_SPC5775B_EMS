


#ifndef DCMDSPUDS_CDI_PRIV_H
#define DCMDSPUDS_CDI_PRIV_H

/**
 ***************************************************************************************************
            Clear diagnostics information (CDI) service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
#define DCM_CDI_REQ_LEN              0x03u     /* Request length for CDI */
#define DCM_POS_DTC_HIGHBYTE         0x00u     /* High byte number in request */
#define DCM_POS_DTC_MIDDLEBYTE       0x01u     /* Middle byte number in request */
#define DCM_POS_DTC_LOWBYTE          0x02u     /* Low byte number in request */
#define DCM_POS_DTC_BIT16            16u       /*shift DTC to 16 bits */
#define DCM_POS_DTC_BIT8             8u         /*shift DTC to 8  bits */
#define DCM_DTC_GRP_MASK             0x00FFFFFFu
#endif
#endif   /* _DCMDSPUDS_CDI_PRIV_H */

