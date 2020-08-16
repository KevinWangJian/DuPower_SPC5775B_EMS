
   

     

/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: CanSM / AR42.4.0.1           Module Package Version
 * $Editor_____: 9.0             Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *

 </VersionHead>*/

#ifndef CANSM_CFG_H
#define CANSM_CFG_H

/*
 ***************************************************************************************************
 * Version Information Defines
 ***************************************************************************************************
*/

 /*
 * Vendor Id refers to a unique ID assigned by Autosar to every Member of Autosar Consortium, used during the call of CanSM_GetVersionInfo() \n
 */
#define CANSM_VENDOR_ID                                6u
/*
 * Module Id refers to a unique ID assigned by Autosar to every Module/Component within the Autosar, used during the call of CanSM_GetVersionInfo() BSW\n
 */
#define CANSM_MODULE_ID                                140u

/* AUTOSAR specification version */
/*
 * Used to declare the Major Release Number of Autosar Main Baseline under which this Component CanSM is delivered
 */

#define CANSM_AR_RELEASE_MAJOR_VERSION                 4u
/*
 * Used to declare the Minor Release Number of Autosar Main Baseline under which this Component CanSM is delivered
 */
#define CANSM_AR_RELEASE_MINOR_VERSION                 2u
/*
 * Used to declare the Revision Release Number of Autosar Main Baseline under which this Component CanSM is delivered
 */
#define CANSM_AR_RELEASE_REVISION_VERSION              2u
/* Software version information */
/*
 * Used to declare Software Major Version number of Component CanSM, used during the call of CanSM_GetVersionInfo()
 */
#define CANSM_SW_MAJOR_VERSION                         4u
/*
 * Used to declare Software Minor Version number of Component CanSM, used during the call of CanSM_GetVersionInfo()
 */
#define CANSM_SW_MINOR_VERSION                         0u
/*
 * Used to declare Software Patch Version number of Component CanSM, used during the call of CanSM_GetVersionInfo()
 */
#define CANSM_SW_PATCH_VERSION                         1u

   
/*
 ***************************************************************************************************
 * Protected  Includes
 ***************************************************************************************************
 */
   
/**
 ***************************************************************************************************
 * \moduledescription
 *                      CanSM Dem Auto generated configuration header file
                         Generated only when CanSMDemBusOffReport is True and Dem module is present
 *
 * \scope               CONF
 ***************************************************************************************************
 */

/* Import all the ErrorIds from dem_interrid.h and Production errors will be reported to Diagnostic Event manager */
 #include "Dem.h" 
 #if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != CANSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION))
//#error "AUTOSAR minor version undefined or mismatched"
#endif
 
#include "SchM_CanSM.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
 




/* Start :All the Defines extracted from the Configuration Files comes here */
       
/************* START : GLOBAL CANSM CONFIGURATION ********************/

/*Development Error ON or OFF*/
#define CANSM_DEV_ERROR_DETECT                              (STD_OFF)

/*Version Info API enabled or not*/
#define CANSM_VERSION_INFO_API                              (STD_OFF)

/* Main Function Cycle time in seconds */
#define CANSM_MAINFUNCTION_CYCLE_TIME                   0.01

/*Enable/Disable CanSM_ChangeBaudrate API*/
#define CANSM_CHANGE_BAUDRATE_API                        STD_OFF

/*Enable/Disable CanSM_SetBaudrate API*/
#define CANSM_SET_BAUDRATE_API                          STD_OFF

/*CanSMBorTxConfirmation enabled or not  */
#define CANSM_BOR_TX_CONFIRMATION_POLLING               STD_OFF

#define CANSM_VARIANT_PRE_COMPILE                       1

#define CANSM_VARIANT_POSTBUILD_SELECTABLE              2

/*CanSM variant info*/
#define CANSM_VARIANT_INFO                                CANSM_VARIANT_PRE_COMPILE

/*Enable/Disable CanSM Calibration*/
#define CANSM_CALIBRATION                         STD_OFF

/*RTE Enabled or Disabled*/
#define CANSM_ECUC_RB_RTE_IN_USE                         STD_ON



/*Enable/Disable ECU passive feature*/
#define CANSM_TX_OFFLINE_ACTIVE_SUPPORT              STD_OFF 

/************* END : GLOBAL CANSM CONFIGURATION ************************/

/* FC_VariationPoint_START */
/* Switch to enable/Disable Dem reporting to DSM after Re-Initialization. */
#define CANSM_DSM_REINIT_ENABLED           STD_OFF
/* FC_VariationPoint_END */


    
/************* START : CanSM CLUSTER CONFIGURATION **********************/
/*Number of CANSM Networks configured*/
#define CANSM_NUM_CAN_NETWORKS    6u

/*Number of CAN Controllers configured*/
#define CANSM_NUM_CAN_CONTROLLERS  6u


/* PN support */
#define CANSM_PN_SUPPORT_CONFIGD             STD_OFF

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"

/*LUT for network index*/
extern CONST(uint8, CANSM_CONST) CanSM_NetworkId_LUT[1][CANSM_NUM_CAN_NETWORKS];

#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"




/************* END: CanSM CLUSTER CONFIGURATION ***********************/


#define CanSM_Config CanSM_ConfigSet[0]





/* End : All the Defines extracted from the Configuration Files comes here  */

/* CANSM_CFG_H*/
#endif
