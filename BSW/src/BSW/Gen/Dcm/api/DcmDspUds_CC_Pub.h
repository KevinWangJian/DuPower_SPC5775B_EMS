

#ifndef DCMDSPUDS_CC_PUB_H
#define DCMDSPUDS_CC_PUB_H


/**
 ***************************************************************************************************
            Communication Control service
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsld_SpecificSubnetInfo:Structure contains information about the specific subnets supported by DCM.\n
 * P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC)); Function pointer to the Schm_switch function.\n
 * P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);Pointer to function to check whether the ComMCahnnel is in the default mode.\n
 * NetworkHandleType 	SpecificSubNetId_u8; Subnet ID\n
 * uint8   				SpecificComMChannelId; ComM channel ID of the subnet
 */
typedef struct
{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
	P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC));
	P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);
#endif
	NetworkHandleType 						SpecificSubNetId_u8;
	uint8   								SpecificComMChannelId;
}Dcm_Dsld_SpecificSubnetInfo;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Dsld_AllChannelsInfoType:Structure contains information about ComMChannels supported by DCM.\n
 * P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC)); Function pointer to the Schm_switch function.\n
 * P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);Pointer to function to check whether the ComMCahnnel is in the default mode.\n
 * uint8   				AllComMChannelId; ComM channel ID
 */
typedef struct
{
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
	P2FUNC(Std_ReturnType,TYPEDEF,switch_fp)	(VAR(Dcm_CommunicationModeType,AUTOMATIC));
	P2FUNC(boolean,TYPEDEF,checkmode_fp)	(void);
#endif

	uint8   AllComMChannelId;
}Dcm_Dsld_AllChannelsInfoType;

#if ( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Stucture array to store specific subent info.
 */
extern CONST (Dcm_Dsld_SpecificSubnetInfo, DCM_CONST) Dcm_specific_subnet_table[DCM_CFG_NUM_SPECIFIC_SUBNETS];
#define DCM_STOP_SEC_CONST_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Stucture array to store  ComM channels info which are referred in DCM.
 */
extern CONST(Dcm_Dsld_AllChannelsInfoType, DCM_CONST) Dcm_AllChannels_ForModeInfo[DCM_CFG_NUM_ALLCHANNELS_MODE_INFO];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_DSP_MODERULEFORCC != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Pointer to the function which checks whether the mode rule is failed or not.
 */
extern P2FUNC(boolean,DCM_APPL_CODE,Dcm_ComMReEnableModeRuleRef) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8);

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Pointer to the user function which checks whether the mode rule is failed or not.
 */
extern P2FUNC(Std_ReturnType,DCM_APPL_CODE,Dcm_ComMUserReEnableModeRuleRef) (void);
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif   /* _DCMDSPUDS_CC_PUB_H */

