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
 * $Generator__: EthTrcv/ AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.0.2.1                ECU Parameter Definition Version
 *

 </VersionHead>*/

 
/**
 ***************************************************************************************************
 * \moduledescription
 *                      EthTrcv Auto generated configuration header file
 *
 * \scope               CONF
 ***************************************************************************************************
 */

#ifndef ETHTRCV_CFG_H_
#define ETHTRCV_CFG_H_

#include "EthTrcv_GeneralTypes.h"


/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#define ETHTRCV_GEN_MAJOR_VERSION    4
#define ETHTRCV_GEN_MINOR_VERSION    0
#define ETHTRCV_GEN_PATCH_VERSION    0

#define ETHTRCV_CONFIGURED

/* Current configuration variant is fix to Pre-compile ! */
#define ETHTRCV_CFG_CONFIG_VARIANT   1

#define ETHTRCV_CFG_NUMBER_OF_ETHTRCV  1

#define ETHTRCV_ETHTRCV_0    0      /*  Index for EthTrcv_0 DP83822 */
#define ETHTRCV_IDX_LIST ETHTRCV_ETHTRCV_0

/* Amount of max configurable EthTrcvs */
#define ETHTRCV_MAX_TRCVS_SUPPORTED 1

/* Enables or disables RTE headers inclusion */
#define ETHTRCV_ECUC_RB_RTE_IN_USE  (STD_ON)

/* flag if Dio is used  */
#define ETHTRCV_DIO_USED         STD_OFF

/* flag if TJA1100 is used */
#define ETHTRCV_TJA1100_USED     STD_OFF

/* flag if NO_PHY is used */
#define ETHTRCV_NO_PHY_USED     STD_OFF

/* flag if DP83822 is used */
#define ETHTRCV_DP83822_USED     STD_ON

/* flag if RTL9000AA is used */
#define ETHTRCV_RTL9000AA_USED   STD_OFF

/* Enable/disable DET */
#define ETHTRCV_CFG_DET_ENABLE  STD_ON

/* Enable/disable the API EthTrcv_GetBaudRate */
#define ETHTRCV_CFG_GET_BAUDRATE_API STD_OFF

/* Enable/disable the API EthTrcv_GetDuplexMode */
#define ETHTRCV_CFG_GET_DUPLEXMODE_API STD_OFF

/* Enable/disable the API EthTrcv_GetLinkState */
#define ETHTRCV_CFG_GET_LINKSTATE_API STD_ON

/* Enable/disable the API EthTrcv_GetTransceiverMode */
#define ETHTRCV_CFG_GET_TRANSCEIVERMODE_API STD_ON

/* Enable/disable the API EthTrcv_SetTransceiverMode*/
#define ETHTRCV_CFG_SET_TRANSCEIVERMODE_API STD_ON

/* Enable/disable the API EthTrcv_StartAutoNegotiation*/
#define ETHTRCV_CFG_START_AUTONEGOTIATION_API STD_ON

/* Enable/disable the API */
#define ETHTRCV_GET_VERSION_INFO STD_ON

/* Enable/disable the macro EthTrcv_GetVersionInfo (if enabled, the api EthTrcv_GetVersionInfo is not available) */
#define ETHTRCV_VERSION_INFO_API_MACRO STD_ON

/* Enable/disable the API */
#define ETHTRCV_CFG_DEM_ENABLE STD_OFF

#define ETHTRCV_CFG_MANAGEMENT_PREAMBLE_SUPPRESSION    STD_ON    /* TRUE if ALL Trcv supports Preamble Suppression */

/* Check if Read / Write MII api is required. If Std_Off parts of code is disabled */
#define ETHTRCV_MII_REQUIRED STD_ON

/* Register field commands */
#define ETHTRCV_PRV_LINKQUALITY_FIELD       (0x0000U)




#endif


