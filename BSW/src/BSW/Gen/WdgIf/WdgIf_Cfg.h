/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/



#ifndef WDGIF_CFG_H
#define WDGIF_CFG_H


/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */



//#include "Wdg.h"
#if (!defined(WDG_AR_RELEASE_MAJOR_VERSION) || (WDG_AR_RELEASE_MAJOR_VERSION != 4))
//#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(WDG_AR_RELEASE_MINOR_VERSION) || (WDG_AR_RELEASE_MINOR_VERSION != 2))
//#error 揂UTOSAR minor version undefined or mismatched�
#endif


#include "WdgIf_Types.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#define WDGIF_DEV_ERROR_DETECT                                       (STD_ON)
#define WDGIF_VERSION_INFO_API                                       (STD_ON)
#define WDGIF_NUMBER_OF_DEVICES                                      (1)

/* Symbolic names for Watchdog instances */
#define WdgIfConf_WdgIfDevice_WdgIfDevice                            ((uint8) (0))

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */



/* 	According to WDGIF020 it is a case of single watchdog driver, to have
	efficient mechanisms to map the API calls to the appropriate watchdog
	driver without additional overhead, DeviceIndex is ignored */

#define WdgIf_SetMode(DeviceIndex, WdgMode)  Wdg_SetMode(WdgMode)
#define WdgIf_SetTriggerCondition(DeviceIndex, WdgTimeout)  Wdg_SetTriggerCondition(WdgTimeout)


/*
***************************************************************************************************
* External declaration
***************************************************************************************************
*/





/* WdgIf Autosar Version info Api */
#define WDGIF_START_SEC_CODE_SLOW
#include "WdgIf_MemMap.h"

extern FUNC(void, WDGIF_CODE_SLOW) WdgIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA) VersionInfoPtr);

#define WDGIF_STOP_SEC_CODE_SLOW
#include "WdgIf_MemMap.h"



#endif /*WDGIF_CFG_H*/

