/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "BswM.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

#define BSWM_CFG_VERSION_INFO  {    /*Version details*/  \
                    6U, /*Vendor Id*/  \
                    42U, /*Module Id*/  \
                    2U, /*SW Major version*/  \
                    0U, /*SW Minor version*/  \
                    0U /*SW Patch version*/  \
               }

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */

#define BSWM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED 
#include "BswM_Cfg_MemMap.h"

static CONST(BswM_Cfg_ActionListType_tst, BSWM_CONST) BswM_Cfg_AL_cast [9];

/* static declaration for Rule Structures */

static CONST(BswM_Cfg_RuleType_tst, BSWM_CONST) BswM_Cfg_Rule_cast[9];

/* Definition for Rule Structures */

static CONST(BswM_Cfg_RuleType_tst, BSWM_CONST) BswM_Cfg_Rule_cast[9]=
{
	{ /*   Rule Structure for the configuration container BswM_AR_DCM_DISABLE_RX_TX_NORMAL    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_DCM_DISABLE_RX_TX_NORMAL,
		&BswM_Cfg_AL_cast[6], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_DCM_ENABLE_RX_DISABLE_TX_NORMAL    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL,
		&BswM_Cfg_AL_cast[7], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_DCM_ENABLE_RX_TX_NORMAL    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_TX_NORMAL,
		&BswM_Cfg_AL_cast[8], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_Godown    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_Shutdown,
		&BswM_Cfg_AL_cast[1], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_PostRun    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_PostRun,
		&BswM_Cfg_AL_cast[2], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_Run    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_Run,
		&BswM_Cfg_AL_cast[0], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_Shutdown    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_PrepShutdown,
		&BswM_Cfg_AL_cast[4], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_StartupOne    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_StartupOne,
		&BswM_Cfg_AL_cast[5], /* trueActionList */
		NULL_PTR
	},
	{ /*   Rule Structure for the configuration container BswM_AR_StartupTwo    */
		BSWM_FALSE,
		&BswM_Cfg_LE_BswM_LE_StartupTwo,
		&BswM_Cfg_AL_cast[3], /* trueActionList */
		NULL_PTR
	}
};

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_ComM_Can1. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_ComM_Can1_cau16[ ] = {6};

/* ModeRequestPort structure for MRP BswM_MRP_ComM_Can1. Variant : __KW_COMMON
 * - ModeInit Value Present flag (isModeInitValuePresent_b) 
 * - NetworkID (idNetwork_u8)
 * - ModeInit Value (dataModeInitValue_en)
 * - RequestProcessing (dataReqProcessing_en)
 * - Number of associated rules (nrAssociatedRules_u16)
 * - Reference to ListOfRules Array (adrRulesRef_pu16)
 */
#define BSWM_CFG_BSWM_MRP_COMM_CAN1 { \
        FALSE,      \
        0,       \
        COMM_NO_COMMUNICATION,        \
        BSWM_IMMEDIATE,      \
        1,       \
        &BswM_Cfg_ListOfRules_BswM_MRP_ComM_Can1_cau16[0]        \
}

/* Array of ComM Indication MRP structs. Variant : __KW_COMMON */
#define BSWM_CFG_COMMINDICATION_MRPS {   \
       BSWM_CFG_BSWM_MRP_COMM_CAN1,      \
}

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_Dcm_Com. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_Dcm_Com_cau16[ ] = {0 , 1 , 2};

/* ModeRequestPort structure for MRP BswM_MRP_Dcm_Com. Variant : __KW_COMMON
 * - ModeInit Value Present flag (isModeInitValuePresent_b) 
 * - NetworkHandleType (idNetwork_u8)
 * - ModeInit Value (dataModeInitValue_en)
 * - RequestProcessing (dataReqProcessing_en)
 * - Number of associated rules (nrAssociatedRules_u16)
 * - Reference to ListOfRules Array (adrRulesRef_pu16)
 */
#define BSWM_CFG_BSWM_MRP_DCM_COM { \
        FALSE,      \
        1,       \
        DCM_ENABLE_RX_TX_NORM,        \
        BSWM_DEFERRED,      \
        3,       \
        &BswM_Cfg_ListOfRules_BswM_MRP_Dcm_Com_cau16[0]        \
}

/* Array of Dcm Com Mode Request MRP structs. Variant : __KW_COMMON */
#define BSWM_CFG_DCMCOMMODEREQ_MRPS {   \
       BSWM_CFG_BSWM_MRP_DCM_COM,      \
}

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_BswM_MDG. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_BswM_MDG_cau16[ ] = {3 , 5 , 6 , 7 , 8};

/* ModeRequestPort structure for MRP BswM_MRP_BswM_MDG. Variant : __KW_COMMON
 * - ModeInit Value Present flag (isModeInitValuePresent_b) 
 * - UserId (idUser_u16)
 * - Max requested mode (dataModeMax_u16)
 * - ModeInit Value (dataModeInitValue_u16)
 * - RequestProcessing (dataReqProcessing_en)
 * - Number of associated rules (nrAssociatedRules_u16)
 * - Reference to ListOfRules Array (adrRulesRef_pu16)
 */
#define BSWM_CFG_BSWM_MRP_BSWM_MDG { \
        FALSE,        \
        0,    \
        65535,                \
        0,         \
        BSWM_DEFERRED,    \
        5, \
        &BswM_Cfg_ListOfRules_BswM_MRP_BswM_MDG_cau16[0]  \
}

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_SwcModeRequest. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_SwcModeRequest_cau16[ ] = {4};

/* ModeRequestPort structure for MRP BswM_MRP_SwcModeRequest. Variant : __KW_COMMON
 * - ModeInit Value Present flag (isModeInitValuePresent_b) 
 * - UserId (idUser_u16)
 * - Max requested mode (dataModeMax_u16)
 * - ModeInit Value (dataModeInitValue_u16)
 * - RequestProcessing (dataReqProcessing_en)
 * - Number of associated rules (nrAssociatedRules_u16)
 * - Reference to ListOfRules Array (adrRulesRef_pu16)
 */
#define BSWM_CFG_BSWM_MRP_SWCMODEREQUEST { \
        FALSE,        \
        1,    \
        65535,                \
        0,         \
        BSWM_DEFERRED,    \
        1, \
        &BswM_Cfg_ListOfRules_BswM_MRP_SwcModeRequest_cau16[0]  \
}

/* Array of GenericRequest MRP structs. Variant : __KW_COMMON */
#define BSWM_CFG_GENERICREQ_MRPS {   \
    BSWM_CFG_BSWM_MRP_BSWM_MDG,      \
    BSWM_CFG_BSWM_MRP_SWCMODEREQUEST,      \
}

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_NvMReadAllComplete. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_NvMReadAllComplete_cau16[ ] = {8};

/* ModeRequestPort structure for MRP BswM_MRP_NvMReadAllComplete. Variant : __KW_COMMON
 * - Mode Init Value present flag 
 * - Configured NvM Service
 * - Configured/Default Mode Init Value
 * - RequestProcessing Enum - Immediate/Deferred 
 * - Number of rules referring to this MRP 
 * - Pointer to array containing indexes of associated rules
 */
#define BSWM_CFG_BSWM_MRP_NVMREADALLCOMPLETE { \
    TRUE,        \
    BSWM_NVMREADALL,       \
    NVM_REQ_PENDING,         \
    BSWM_IMMEDIATE,       \
    1,          \
    &BswM_Cfg_ListOfRules_BswM_MRP_NvMReadAllComplete_cau16[0]  \
}

/*Array of BswMRule indexes associated with ModeReqPort BswM_MRP_NvMWriteAllComplete. Variant :  __KW_COMMON*/
static CONST(uint16, BSWM_CONST) BswM_Cfg_ListOfRules_BswM_MRP_NvMWriteAllComplete_cau16[ ] = {3};

/* ModeRequestPort structure for MRP BswM_MRP_NvMWriteAllComplete. Variant : __KW_COMMON
 * - Mode Init Value present flag 
 * - Configured NvM Service
 * - Configured/Default Mode Init Value
 * - RequestProcessing Enum - Immediate/Deferred 
 * - Number of rules referring to this MRP 
 * - Pointer to array containing indexes of associated rules
 */
#define BSWM_CFG_BSWM_MRP_NVMWRITEALLCOMPLETE { \
    TRUE,        \
    BSWM_NVMWRITEALL,       \
    NVM_REQ_PENDING,         \
    BSWM_IMMEDIATE,       \
    1,          \
    &BswM_Cfg_ListOfRules_BswM_MRP_NvMWriteAllComplete_cau16[0]  \
}

/* Array of NvM BlockRequest MRP structs. Variant : __KW_COMMON */
#define BSWM_CFG_NVMJOBMODEIND_MRPS {   \
    BSWM_CFG_BSWM_MRP_NVMREADALLCOMPLETE,      \
    BSWM_CFG_BSWM_MRP_NVMWRITEALLCOMPLETE,      \
}

/* BswM_Cfg_MRPType_tst : Array of structures for different MRP types. Variant : __KW_COMMON
 */
#define BSWM_CFG_MODEREQPORT {       \
	BSWM_CFG_COMMINDICATION_MRPS,      \
	BSWM_CFG_DCMCOMMODEREQ_MRPS,      \
	BSWM_CFG_GENERICREQ_MRPS,      \
	BSWM_CFG_NVMJOBMODEIND_MRPS,      \
            }

/* ModeArbitration Type structure  
 * - ModeRequestPortType structure (BswM_Cfg_MRPType_tst)
 * - Number of rules configured for the chosen variant 
 * - Pointer to base address of array of rules (BswM_Cfg_RuleType_tst)
 */
#define BSWM_CFG_MODEARBITRATION {      \
        BSWM_CFG_MODEREQPORT,     \
        9, \
        &BswM_Cfg_Rule_cast[0] \
}

/*
 **********************************************************************************************************************
 * Arrays of BswMPduGroupSwitch Group References for the variant  with contents: 
 *   # BswMPduEnableGroupSwitch Reference/References
 *   # BswMPduDisableGroupSwitch Reference/References
 **********************************************************************************************************************
 */

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL_BswMPduEnableGrpRef_cau16[1] =
{
	0
};

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_TX_NORMAL_BswMPduEnableGrpRef_cau16[2] =
{
	0,
	1
};

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_StartPdu_BswMPduEnableGrpRef_cau16[2] =
{
	0,
	1
};

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_DCM_DISABLE_RX_TX_NORMAL_BswMPduDisableGrpRef_cau16[2] =
{
	0,
	1
};

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL_BswMPduDisableGrpRef_cau16[1] =
{
	1
};

static CONST(Com_IpduGroupIdType, BSWM_CONST) BswM_Cfg_AC_BswM_AI_StopPdu_BswMPduDisableGrpRef_cau16[2] =
{
	0,
	1
};

/*
 **********************************************************************************************************************
 * Array of BswMPduRouterControl Action for the variant  with contents: 
 *   # Reinit 
 *   # No of EnabledPduGroupRef
 *   # No of DisabledPduGroupRef
 *   # Base Addr of EnabledPduGroupRef
 *   # Base Addr of DisabledPduGroupRef
 **********************************************************************************************************************
 */

static CONST(BswM_Cfg_AC_PduGroupSwitchType_tst, BSWM_CONST) BswM_Cfg_AC_BswMPduGroupSwitch_cast[BSWM_NO_OF_AC_IPDUGROUPSWITCH] =
{
	{
		/* BswM_AI_DCM_DISABLE_RX_TX_NORMAL */
		FALSE,
		0,
		2,

		NULL_PTR,

		&BswM_Cfg_AC_BswM_AI_DCM_DISABLE_RX_TX_NORMAL_BswMPduDisableGrpRef_cau16[0]

	},
	{
		/* BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL */
		FALSE,
		1,
		1,

		&BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL_BswMPduEnableGrpRef_cau16[0],

		&BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL_BswMPduDisableGrpRef_cau16[0]

	},
	{
		/* BswM_AI_DCM_ENABLE_RX_TX_NORMAL */
		FALSE,
		2,
		0,

		&BswM_Cfg_AC_BswM_AI_DCM_ENABLE_RX_TX_NORMAL_BswMPduEnableGrpRef_cau16[0],

		NULL_PTR

	},
	{
		/* BswM_AI_StartPdu */
		FALSE,
		2,
		0,

		&BswM_Cfg_AC_BswM_AI_StartPdu_BswMPduEnableGrpRef_cau16[0],

		NULL_PTR

	},
	{
		/* BswM_AI_StopPdu */
		FALSE,
		0,
		2,

		NULL_PTR,

		&BswM_Cfg_AC_BswM_AI_StopPdu_BswMPduDisableGrpRef_cau16[0]

	}
};

/*****************************************************************************************
 * Array of ActionListItems for __KW_COMMON with contents:
 * {
 *     AbortOnFailFlag,
 *     ActionListItemType,
 *     PointerToActionListItem
 * }
 *****************************************************************************************/

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchAppRun_Items_cast [14] =
{
	{
		/* ActionListItemName  :   BswM_ALI_StartPdu */
		FALSE,
		BSWM_ACTION_PDU_GRP_SWITCH,
		&BswM_Cfg_AC_BswMPduGroupSwitch_cast[3] /* BswM_AI_StartPdu */
	},
	{
		/* ActionListItemName  :   BswM_ALI_BswMAppRun */
		FALSE,
		BSWM_ACTION_SCHM_SWITCH,
		&BswM_Cfg_AC_BswMSchMSwitch_cast[0] /* BswM_AI_BswMSwitchAppRun */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can1 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[0] /* BswM_AI_ComMCommAllowed_Can1 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User1 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[0] /* BswM_AI_ComMReqFullComm_User1 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can2 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[1] /* BswM_AI_ComMCommAllowed_Can2 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User2 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[1] /* BswM_AI_ComMReqFullComm_User2 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can3 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[2] /* BswM_AI_ComMCommAllowed_Can3 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User3 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[2] /* BswM_AI_ComMReqFullComm_User3 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can4 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[3] /* BswM_AI_ComMCommAllowed_Can4 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User4 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[3] /* BswM_AI_ComMReqFullComm_User4 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can5 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[4] /* BswM_AI_ComMCommAllowed_Can5 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User5 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[4] /* BswM_AI_ComMReqFullComm_User5 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AllowComm_Can6 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[5] /* BswM_AI_ComMCommAllowed_Can6 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqFullComm_User6 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[5] /* BswM_AI_ComMReqFullComm_User6 */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchGoDown_Items_cast [3] =
{
	{
		/* ActionListItemName  :   BswM_ALI_RteStop */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[26] /* BswM_AI_RteStop */
	},
	{
		/* ActionListItemName  :   BswM_ALI_GoDown */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[19] /* BswM_AI_GoDown */
	},
	{
		/* ActionListItemName  :   BswM_ALI_EcuM_MainFunction */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[15] /* BswM_AI_EcuM_MainFunction */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchPrepShutdown_Items_cast [14] =
{
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can1 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[6] /* BswM_AI_ComMCommNotAllowed_Can1 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User1 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[6] /* BswM_AI_ComMReqNoComm_User1 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can2 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[7] /* BswM_AI_ComMCommNotAllowed_Can2 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User2 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[7] /* BswM_AI_ComMReqNoComm_User2 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can3 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[8] /* BswM_AI_ComMCommNotAllowed_Can3 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User3 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[8] /* BswM_AI_ComMReqNoComm_User3 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can4 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[9] /* BswM_AI_ComMCommNotAllowed_Can4 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User4 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[9] /* BswM_AI_ComMReqNoComm_User4 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can5 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[10] /* BswM_AI_ComMCommNotAllowed_Can5 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User5 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[10] /* BswM_AI_ComMReqNoComm_User5 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NotAllowComm_Can6 */
		FALSE,
		BSWM_ACTION_COMM_ALLOW_COM,
		&BswM_Cfg_AC_BswMComMAllowCom_cast[11] /* BswM_AI_ComMCommNotAllowed_Can6 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMReqNoComm_User6 */
		FALSE,
		BSWM_ACTION_COMM_MODE_SWITCH,
		&BswM_Cfg_AC_BswMComMModeSwitch_cast[11] /* BswM_AI_ComMReqNoComm_User6 */
	},
	{
		/* ActionListItemName  :   BswM_ALI_StopPdu */
		FALSE,
		BSWM_ACTION_PDU_GRP_SWITCH,
		&BswM_Cfg_AC_BswMPduGroupSwitch_cast[4] /* BswM_AI_StopPdu */
	},
	{
		/* ActionListItemName  :   BswM_ALI_BswMPrepShutdown */
		FALSE,
		BSWM_ACTION_SCHM_SWITCH,
		&BswM_Cfg_AC_BswMSchMSwitch_cast[2] /* BswM_AI_BswMSwitchPrepShutdown */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchRun_Items_cast [16] =
{
	{
		/* ActionListItemName  :   BswM_ALI_SbcRun */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[30] /* BswM_AI_SbcRun */
	},
	{
		/* ActionListItemName  :   BswM_ALI_CanInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[3] /* BswM_AI_CanInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_CanIfInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[2] /* BswM_AI_CanIfInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_CanSmInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[4] /* BswM_AI_CanSmInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_PduRInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[24] /* BswM_AI_PduRInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_IpduMInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[20] /* BswM_AI_IpduMInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[7] /* BswM_AI_ComInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_ComMInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[9] /* BswM_AI_ComMInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_XcpInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[32] /* BswM_AI_XcpInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_RteTimerStart */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[27] /* BswM_AI_RteTimerStart */
	},
	{
		/* ActionListItemName  :   BswM_ALI_BswMRun */
		FALSE,
		BSWM_ACTION_SCHM_SWITCH,
		&BswM_Cfg_AC_BswMSchMSwitch_cast[3] /* BswM_AI_BswMSwitchRun */
	},
	{
		/* ActionListItemName  :   BswM_ALI_CanTpInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[5] /* BswM_AI_CanTpInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_DcmInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[10] /* BswM_AI_DcmInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_FiMInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[17] /* BswM_AI_FiMInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_Dem_PreInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[13] /* BswM_AI_Dem_PreInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_DemInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[11] /* BswM_AI_DemInit */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchShutdown_Items_cast [4] =
{
	{
		/* ActionListItemName  :   BswM_ALI_ComMDeInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[8] /* BswM_AI_ComMDeInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_SbcPrepShutdown */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[29] /* BswM_AI_SbcPrepShutdown */
	},
	{
		/* ActionListItemName  :   BswM_ALI_WriteAll */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[23] /* BswM_AI_NvMWriteAll */
	},
	{
		/* ActionListItemName  :   BswM_ALI_BswMShutdown */
		FALSE,
		BSWM_ACTION_SCHM_SWITCH,
		&BswM_Cfg_AC_BswMSchMSwitch_cast[4] /* BswM_AI_BswMSwitchShutdown */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_BswMSwitchStartupTwo_Items_cast [12] =
{
	{
		/* ActionListItemName  :   BswM_ALI_AdcInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[0] /* BswM_AI_AdcInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_PwmInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[25] /* BswM_AI_PwmInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_SpiInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[31] /* BswM_AI_SpiInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_SbcInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[28] /* BswM_AI_SbcInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_EepInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[16] /* BswM_AI_EepInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_EaInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[14] /* BswM_AI_EaInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_FlsInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[18] /* BswM_AI_FlsInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_AfeInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[1] /* BswM_AI_AfeInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_CddInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[6] /* BswM_AI_CddInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NvMInit */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[21] /* BswM_AI_NvMInit */
	},
	{
		/* ActionListItemName  :   BswM_ALI_NvMReadAll */
		FALSE,
		BSWM_ACTION_USR_CALLOUT,
		&BswM_Cfg_AC_BswMUserCallout_cast[22] /* BswM_AI_NvMReadAll */
	},
	{
		/* ActionListItemName  :   BswM_ALI_BswMStartupTwo */
		FALSE,
		BSWM_ACTION_SCHM_SWITCH,
		&BswM_Cfg_AC_BswMSchMSwitch_cast[5] /* BswM_AI_BswMSwitchStartupTwo */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_DCM_DISABLE_RX_TX_NORMAL_Items_cast [1] =
{
	{
		/* ActionListItemName  :   BswM_ALI_DCM_DISABLE_RX_TX_NORMAL */
		FALSE,
		BSWM_ACTION_PDU_GRP_SWITCH,
		&BswM_Cfg_AC_BswMPduGroupSwitch_cast[0] /* BswM_AI_DCM_DISABLE_RX_TX_NORMAL */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_DCM_ENABLE_RX_DISABLE_TX_NORMAL_Items_cast [1] =
{
	{
		/* ActionListItemName  :   BswM_ALI_DCM_ENABLE_RX_DISABLE_TX_NORMAL */
		FALSE,
		BSWM_ACTION_PDU_GRP_SWITCH,
		&BswM_Cfg_AC_BswMPduGroupSwitch_cast[1] /* BswM_AI_DCM_ENABLE_RX_DISABLE_TX_NORMAL */
	}
};

static CONST(BswM_Cfg_ActionListItemType_tst, BSWM_CONST) BswM_Cfg_AL_BswM_AL_DCM_ENABLE_RX_TX_NORMAL_Items_cast [1] =
{
	{
		/* ActionListItemName  :   BswM_ALI_DCM_ENABLE_RX_TX_NORMAL */
		FALSE,
		BSWM_ACTION_PDU_GRP_SWITCH,
		&BswM_Cfg_AC_BswMPduGroupSwitch_cast[2] /* BswM_AI_DCM_ENABLE_RX_TX_NORMAL */
	}
};

/*****************************************************************************************
 * Array of ActionLists for __KW_COMMON with contents:
 * {
 *     ExecutionType,
 *     NumberOfActionListItems,
 *     BaseAddressOfActionListItemArray,
 *     Unique Number for ActionList
 * }
 ****************************************************************************************/

static CONST(BswM_Cfg_ActionListType_tst, BSWM_CONST) BswM_Cfg_AL_cast [9] =
{
	{
		/* ActionListName   :   BswM_AL_BswMSwitchAppRun */
		BSWM_TRIGGER,
		14,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchAppRun_Items_cast[0],
		0 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_BswMSwitchGoDown */
		BSWM_TRIGGER,
		3,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchGoDown_Items_cast[0],
		1 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_BswMSwitchPrepShutdown */
		BSWM_TRIGGER,
		14,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchPrepShutdown_Items_cast[0],
		2 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_BswMSwitchRun */
		BSWM_TRIGGER,
		16,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchRun_Items_cast[0],
		3 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_BswMSwitchShutdown */
		BSWM_TRIGGER,
		4,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchShutdown_Items_cast[0],
		4 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_BswMSwitchStartupTwo */
		BSWM_CONDITION,
		12,
		&BswM_Cfg_AL_BswM_AL_BswMSwitchStartupTwo_Items_cast[0],
		5 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_DCM_DISABLE_RX_TX_NORMAL */
		BSWM_TRIGGER,
		1,
		&BswM_Cfg_AL_BswM_AL_DCM_DISABLE_RX_TX_NORMAL_Items_cast[0],
		6 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_DCM_ENABLE_RX_DISABLE_TX_NORMAL */
		BSWM_TRIGGER,
		1,
		&BswM_Cfg_AL_BswM_AL_DCM_ENABLE_RX_DISABLE_TX_NORMAL_Items_cast[0],
		7 /* Unique Number for ActionList */
	},
	{
		/* ActionListName   :   BswM_AL_DCM_ENABLE_RX_TX_NORMAL */
		BSWM_TRIGGER,
		1,
		&BswM_Cfg_AL_BswM_AL_DCM_ENABLE_RX_TX_NORMAL_Items_cast[0],
		8 /* Unique Number for ActionList */
	}
};

/* PBAction Type structure Variant : __KW_COMMON
 * - Pointer to base address of array of IPduGroupSwitchType ActionType structure (BswM_Cfg_AC_PduGroupSwitchType_tst)
 */
#define BSWM_CFG_PBACTION                {      \
                &BswM_Cfg_AC_BswMPduGroupSwitch_cast[0],     \
}

/* ModeControl Type structure  
 * - ActionType structure (BswM_Cfg_PBActionType_tst)
 * - Pointer to base address of array of actionlists (BswM_Cfg_ActionListType_tst) Currently NULL_PTR
 */
#define BSWM_CFG_MODECONTROL {      \
        BSWM_CFG_PBACTION,     \
        &BswM_Cfg_AL_cast[0]   \
}

/* BswM_ConfigType  :
 * - ModeArbitration structure (BswM_Cfg_ModeArbitrationType_tst)
 * - ModeControl structure (BswM_Cfg_ModeControlType_tst)
 * - Version info to compare during module initialization
 */
CONST(BswM_ConfigType, BSWM_CONST) BswM_Config =
{
	BSWM_CFG_MODEARBITRATION,
	BSWM_CFG_MODECONTROL,
	BSWM_CFG_VERSION_INFO
};

#define BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED 
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "BswM_Cfg_MemMap.h"

CONSTP2CONST(BswM_ConfigType,AUTOMATIC,BSWM_CONST) BswM_Configurations_capcst[BSWM_NO_OF_CONFIGSETS]=
{
	&BswM_Config
};

#define BSWM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "BswM_Cfg_MemMap.h"
/**********************************************************************************************************************
 *																										
 **********************************************************************************************************************/
