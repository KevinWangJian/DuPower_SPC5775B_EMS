

/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * Generator__: ComM / AR42.4.0.0                Module Package Version
 * Editor_____: 9.0                Tool Version
 * Model______: 2.3.0.4             ECU Parameter Definition Version
 *
 </VersionHead>*/


/***********************************************************************************/
/*                                        INCLUDES                                 */
/***********************************************************************************/
#include "ComStack_Types.h"
#include "ComM_Cfg.h"
#include "ComM_PBcfg.h"
#include "ComM_Priv.h"
#include "Std_Types.h"

/**************************************Start of channel data***************************************/

#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

#if (COMM_PNC_ENABLED != STD_OFF)






#endif      /* #if (COMM_PNC_ENABLED == STD_ON)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
#endif
#if (COMM_INHIBITION_ENABLED)

static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_1_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_1_Channel};


static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_2_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_2_Channel};


static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_3_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_3_Channel};


static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_4_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_4_Channel};


static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_5_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_5_Channel};


static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Can_Network_6_Channel[] = {
ComMConf_ComMUser_ComMUser_Can_Network_6_Channel};

static CONST(uint8, COMM_CONST) ComM_DirectUsersPerChannel_ComMChannel_Eth_Network_Channel[] = {
ComMConf_ComMUser_ComMUser_Eth_Network_Channel};
#endif


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_1_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_1_Channel    };


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_2_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_2_Channel    };


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_3_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_3_Channel    };


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_4_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_4_Channel    };


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_5_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_5_Channel    };


static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Can_Network_6_Channel[] = {
    ComMConf_ComMUser_ComMUser_Can_Network_6_Channel    };

static CONST(uint8, COMM_CONST) ComM_AllUsersPerChannel_ComMChannel_Eth_Network_Channel[] = {
    ComMConf_ComMUser_ComMUser_Eth_Network_Channel    };

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
/**************************************End of channel data**************************************/

/********************************* Start of channel list *******************************************/
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

CONST(ComM_ChannelType,COMM_CONST) ComM_ChanelList[] = {
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_1_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_1_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_1_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    0,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
,
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_2_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_2_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_2_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    1,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
,
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_3_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_3_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_3_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    2,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
,
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_4_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_4_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_4_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    3,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
,
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_5_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_5_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_5_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    4,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
,
{
    /* Main function period is 10 */
    /* Channel : ComMChannel_Can_Network_6_Channel */
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    NULL_PTR,
#endif /* ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    ComM_DirectUsersPerChannel_ComMChannel_Can_Network_6_Channel,
#endif /*#if (COMM_INHIBITION_ENABLED)  */
    ComM_AllUsersPerChannel_ComMChannel_Can_Network_6_Channel,
    COMM_BUS_TYPE_CAN,
    NONE,
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    COMM_GATEWAY_TYPE_ACTIVE,
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    1000,
    1,
    5,
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    0,
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    1,
    0x3,
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    FALSE,
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
/*****************************************End of channel list*******************************************/

/*****************************************Start of user data*******************************************/
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"


static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_1_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_1_Channel    
};



static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_2_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_2_Channel    
};



static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_3_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_3_Channel    
};



static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_4_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_4_Channel    
};



static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_5_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_5_Channel    
};



static CONST(uint8,COMM_CONST) ComM_DirectChannelsPerUser_ComMUser_Can_Network_6_Channel[] = {
    ComMConf_ComMChannel_ComMChannel_Can_Network_6_Channel    
};



#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"


/*****************************************Start of user list*******************************************/
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

CONST(ComM_UsersType,COMM_CONST) ComM_UserList[] =
{
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_1_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
,
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_2_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
,
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_3_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
,
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_4_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
,
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_5_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
,
{
    ComM_DirectChannelsPerUser_ComMUser_Can_Network_6_Channel,
#if (COMM_PNC_ENABLED != STD_OFF)
    NULL_PTR,
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    1,
    1,
#if (COMM_PNC_ENABLED != STD_OFF)
    0
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
/*****************************************End of user list*******************************************/


#if (COMM_PNC_ENABLED == STD_ON)

/*****************************************Start of pnc data*******************************************/
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"


#if(COMM_INHIBITION_ENABLED)

#endif

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

/*****************************************End of pnc data*******************************************/
/*****************************************Start of pnc list*******************************************/
#if (COMM_PNC_ENABLED != STD_OFF)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

CONST(ComM_PncConfigStruct_t,COMM_CONST) ComM_PncList[] =
{
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
/*****************************************End of pnc list*******************************************/

#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */

#if (COMM_PNC_GW_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#endif /* #if (COMM_PNC_GW_ENABLED == STD_ON)  */

#if (COMM_PNC_ENABLED == STD_ON)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

CONST(uint16, COMM_CONST) ComM_EIRA_RxSig[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA][COMM_NO_OF_PNCS] =
{
{   /* COMM_BUS_TYPE_CAN  */
}
,
{   /* COMM_BUS_TYPE_CAN  */

}

};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */

#if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
/* Definition of Global config structure of ComM  */
CONST(ComM_GlobalConfigType, COMM_CONST) ComM_GlobalConfigData_cs =
{
    ComM_ChanelList,                /* Pointer to channel list  */
    ComM_UserList,                  /* Pointer to user list  */
#if(COMM_PNC_ENABLED != STD_OFF)
    ComM_PncList,                   /* Pointer to PNC list  */
    ComM_EIRA_RxSig,                /* Pointer to EIRA Rx Signal table  */
#if(COMM_PNC_GW_ENABLED != STD_OFF)
    ComM_ERA_RxSig,                 /* Pointer to ERA Rx Signal table  */
#endif
    FALSE    /* Actual value of PNC switch  */
#endif
};

#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
static CONST(Std_VersionInfoType, COMM_CONST)  ComM_VersionInfo =
{
    6,
    12,
    4,
    0,
    0
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#endif      /* #if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)  */

#if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

/* Definition of Base config structure  */
CONST(ComM_ConfigType, COMM_CONST) ComM_Config =
{
    /* Void pointer initialised with pointer to an instance of structure ComM_GlobalConfigData_cs */
    &ComM_GlobalConfigData_cs,
    &ComM_VersionInfo
};
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
#endif      /* #if (COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)  */

