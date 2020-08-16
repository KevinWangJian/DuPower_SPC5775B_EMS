

#ifndef FIM_H
#define FIM_H

#include "FiM_Types.h"
#include "Dem_Types.h"
#include "FiM_Cfg.h"
#include "FiM_Cfg_Fids.h"
#include "FiM_Cfg_PbCfg.h"
#include "FiM_Cfg_Version.h"

/**
 * \defgroup FIM_H
 *  The header file contains all the interface functions required in Autosar.
 *  see AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 *  To use this interface include the header <b>FiM.h</b>
 */

/**
 * @ingroup FIM_H
 *
 * This service returns the version information of this module.
 * The function FiM_GetVersionInfo shall return the version information of the FIM module.
 * The version information includes: Module Id, Vendor Id, Vendor specific version numbers.
 *\n
 * @param[in]         versioninfo A pointer to the struct with the version information.\n
 * @see [AR402:FIM078],[AR402:STD015]
 *@return void
 */

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

#if (FIM_CFG_VERSION_INFO_API == FIM_CFG_ON)
void FiM_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (FIM_CFG_CHECK_API_CONSISTENCY == TRUE)
/**
 * @ingroup FIM_H
 * This service reports the permission state to the functionality.
 *\n
 * @param[in]         FID - The function ID that is going to be checked for its inhibition status.\n
 * @param[in]         Permission A pointer to a variable that will contain the result of the inhibition check. true/false function may/may not run.\n
 * @see [AR402:FIM011]
 * @return            E_OK The request is accepted.\n
 *                    E_NOT_OK: if the request is not accepted.
 */
Std_ReturnType FiM_GetFunctionPermission(FiM_FunctionIdType FID, boolean* Permission);
#endif

#if (FIM_CFG_SERVICE07_VISIBLE_ERROR_API == FIM_CFG_ON)
/**
 * @ingroup FIM_H
 * This service reports the service$07 visible entry for the FID.
 *\n
 * @param[in]         FID - The function ID that is going to be checked for its service$07 visibility.\n
 * @param[in]         Visibility A pointer to a variable that will contain the result of the service07 visibility counter.
 * @return            E_OK The request is accepted.\n
 *                    E_NOT_OK: if the request is not accepted.
 */
Std_ReturnType FiM_GetService07Visibility(FiM_FunctionIdType FID, boolean* Visibility);
#endif

/**
 * @ingroup FIM_H
 *  This service initializes the FiM at init time
 *  The ECU State Manager shall call the function FiM_Init during the startup phase of the ECU in order to initialize
 *  the permission states of the FIDs based on the event data of the DEM.
 *  The FIM is not functional until this function has been called.
 * @param[in] FiMConfigPtr Pointer to a data structure for the post build parameters of the FIM.
 * @see [AR402:FIM077]
 * @return void
 */

void FiM_Init(const FiM_ConfigType* FiMConfigPtr);

/**
 *  @ingroup FIM_H
 *  This service is provided to the Dem in order to call the FiM upon status changes.
 *   If the FIM module does not calculate the inhibition states in a cyclic way (as defined in
 *   configuration parameter FIM_CFG_DEM_TRIGGERFIMREPORTS = FIM_CFG_OFF), the module DEM shall call the function
 *   FiM_DemTriggerOnEventStatus whenever the status of an event changes.
 *   In case the FIM module calculates the inhibition states in a cyclic way (as defined in configuration
 *   parameter FIM_CFG_DEM_TRIGGERFIMREPORTS = FIM_CFG_ON), the FIM has to query all event status information from the DEM.
 *   In that case, the DEM does not have to call the function FiM_DemTriggerOnEventStatus.
 * @param[in] EventId The id of the event that's status has changed.
 * @param[in] EventStatusOld The old value of the status.
 * @param[in] EventStatusNew The new value of the status.
 * @see [AR402:FIM021]
 * @return void
 */
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)
void FiM_DemTriggerOnEventStatus(Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld,
        Dem_UdsStatusByteType EventStatusNew);
#endif

/**
 *  @ingroup FIM_H
 *  This service is provided to the Dem in order to call the FiM upon status changes.
 *   If the FIM module does not calculate the inhibition states in a cyclic way (as defined in
 *   configuration parameter FIM_CFG_DEM_TRIGGERFIMREPORTS = FIM_CFG_OFF), the module DEM shall call the function
 *   FiM_DemTriggerOnComponentStatus whenever the status of an component changes.
 *   In case the FIM module calculates the inhibition states in a cyclic way (as defined in configuration
 *   parameter FIM_CFG_DEM_TRIGGERFIMREPORTS = FIM_CFG_ON), the FIM has to query all component status information from the DEM.
 *   In that case, the DEM does not have to call the function FiM_DemTriggerOnComponentStatus.
 * @param[in] ComponentId Identification of a DemComponent.
 * @param[in] ComponentFailedStatus New FAILED status of the component.
 * @see [AR422:SWS_Fim_00101]
 * @return void
 */
#if (FIM_CFG_DEM_TRIGGERFIMREPORTS == FIM_CFG_ON)
void FiM_DemTriggerOnComponentStatus(Dem_ComponentIdType ComponentId, boolean ComponentFailedStatus);
#endif

/**
 *  @ingroup FIM_H
 *  Initialize the DEM funtionality.\n
 *  The DEM shall call FiM_DemInit to re-initialize the FIM module in case the DEM detects a status change \n
 *  of a certain number of events (DEM implementation specific), e.g. clearance of event memory in the DEM.\n
 * @param void
 * @see [AR402:FIM006]\n
 * @return void
 */
void FiM_DemInit(void);

/**
 * @ingroup FIM_H
 * The main function of the FIM.
 * AUTOSAR deviations:
 *         in contrast to requirement AR402:FIM070, this function is always there, regardless of the value of the
 *         configuration parameter FIM_CFG_DEM_TRIGGERFIMREPORTS.
 * @param void
 * @see [AR402:FIM060]
 * @return void
 */
void FiM_MainFunction(void);

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* include protection */

