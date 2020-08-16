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
 * $Generator__: EthIf/ AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.0.2.1          	  ECU Parameter Definition Version
 *
 
 </VersionHead>*/



#ifndef ETHIF_CFG_H
#define ETHIF_CFG_H

/* If macro is not defined, component will not be compiled */
#define ETHIF_CONFIGURED


/* Macro to define DET check to be enabled or disabled */
#define ETHIF_DEV_ERROR_DETECT					STD_ON


/* Macro to Enable/Disable Recieve Intrrupt */
#define ETHIF_ENABLE_RX_INTERRUPT				STD_OFF


/* Macro to Enable/Disable Transmit Intrrupt */
#define ETHIF_ENABLE_TX_INTERRUPT				STD_OFF


/* Macro to Enable/Disable Global time support APIs */
#define ETHIF_ENABLE_GLOBAL_TIME_SUPPORT		STD_OFF


/* Macro to Enable/Disable EthIf_GetVlanId API */
#define ETHIF_ENABLE_ETHIF_GET_VLANID       STD_OFF

/* Macro to define the main function calling time in millisecond */
#define ETHIF_MAINFUNCTION_PERIOD 				10

/* Macro to define the calling time for EthIf_MainFunctionState() in millisecond */
#define ETHIF_MAINFUNCTION_STATE_PERIOD         10UL

/* Macro to define Maximum number of Ethernet frames per Ethernet controller polled from the Ethernet driver within EthIf_MainFunctionRx */
#define ETHIF_RX_INDICATION_ITERATIONS          10U

/* Macro to define the time after wihich Trcv link state will get polled */
#define ETHIF_TRCV_LINKSTATECHGMAIN_RELOAD		10


/* Macro to Enable/Disable Version API */
#define ETHIF_VERSIONINFO_API					STD_OFF


/* Enables/disables calling Eth_UpdatePhysAddrFilter API */
#define ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT  STD_OFF




/* Port startup timer not configured */
#define ETHIF_PORT_STARTUP_ACTIVE_TIME  0UL


/* EthIf Switch Off Port delay not configured */
#define ETHIF_PORT_SWITCHOFF_DELAY   0UL

/* Definition of supported module variant. */
#define ETHIF_CFG_VARIANT_PRE_COMPILE     0U

/* Macro to hold configured module variant. Hardcoded to pre-compile since Post build is not yet supported. */
#define ETHIF_CFG_CONFIGURATION_VARIANT                     ETHIF_CFG_VARIANT_PRE_COMPILE

/*****************************************************************************************/
/*                          EthIfController Symbolic Names                               */
/*****************************************************************************************/

#define EthIfConf_EthIfController_EthIfController       ((uint8)0)

/*****************************************************************************************/

/*****************************************************************************************/
/*                          EthIfSwitchPortGroup Symbolic Names                          */
/*****************************************************************************************/

/*****************************************************************************************/


#define EthIf_Config (EthIf_ConfigSet[0])

#endif /* ETHIF_CFG_H */

