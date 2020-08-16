/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/

       

 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: EthSM/ AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.0.2.1          	  ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#include "EthSM.h"
#include "EthSM_PbCfg.h"
#include "EthIf_Cfg.h"


#define ETHSM_START_SEC_CONST_UNSPECIFIED
#include "EthSM_MemMap.h"

/* EthSM network user configuration structure */
CONST( EthSM_NetworkUserConfig_tst, ETHSM_CONST )      EthSM_NetworkUsers_Ctrl0_acst[1] =
{
    {
        NULL_PTR,
       ETHSM_USER_TCPIP
    },
};


/* EthSM network configuration structure. The structure is generated on sorted list of EthSMNetwork config container based on EthIfCtrlIdx . */
CONST(EthSM_ConfigType, ETHSM_CONST) EthSM_NetConfig[1]=
{
	{
	   (&(EthSM_NetworkUsers_Ctrl0_acst[0])),                    /* Reference to network user data structure   */
		0,                                                       /* ETHSM_E_LINK_DOWN is not configured for the EthSM network */
		ComMConf_ComMChannel_ComMChannel_Eth_Network_Channel,		/* ComMNetworkHandle reference */
		1                                                        /* Number of users of the EthSM network   */
	},

};
#define ETHSM_STOP_SEC_CONST_UNSPECIFIED
#include "EthSM_MemMap.h"
