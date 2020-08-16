/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef FIM_CFG_H
#define FIM_CFG_H

#include "FiM_Types.h"

/*
 **********************************************************************************************************************
 * FiM global configuration values
 **********************************************************************************************************************
 */

#define FIM_CFG_ON  1
#define FIM_CFG_OFF 0

/*
 **********************************************************************************************
 * global configuration switches
 **********************************************************************************************
 */
/* availability of version info API */
#define FIM_CFG_VERSION_INFO_API                 (FIM_CFG_ON)

/* availability of SERVICE$07 visible error info API */
#define FIM_CFG_SERVICE07_VISIBLE_ERROR_API      (FIM_CFG_OFF)

/* activates error reporting to Det */
#define FIM_CFG_DEV_ERROR_DETECT                 (FIM_CFG_ON)

/* configuration parameter in DemGeneral which says whether Dem triggers Fim on dem Events status change */
#define FIM_CFG_DEM_TRIGGERFIMREPORTS            (FIM_CFG_ON)

/*
 **********************************************************************************************
 * FiM configuration constants as defined in ECUC
 **********************************************************************************************
 */
/* configured number of FIDs that can be processed during a monitoring scheduling cycle */
#define  FIM_CFG_FIDS_PER_MONITORCYCLE_ECUC      FIM_CFG_NUMBEROFFIDS

/*  configured number of Dem events that can be processed during a monitoring scheduling cycle */
#define FIM_CFG_EVENTS_PER_MONITORCYCLE_ECUC     (FIM_CFG_NUMBEROFDEMEVENTIDS + FIM_CFG_NUMBEROFDEMCOMPONENTIDS)

/*
 **********************************************************************************************
 * FiM configuration values calculated from ECUC configuration
 **********************************************************************************************
 */
/* calculated total number of links between FIDs and components */
#define FIM_CFG_MAX_TOTAL_LINKS_COMPONENT_CALC   (1)

/* maximum number of events and components that can be linked to a single FID */
#define FIM_CFG_MAXIMUM_LINKS_PER_FID_CALC       (2)

/* configured number of Dem event IDs */
#define FIM_CFG_NUMBEROFDEMEVENTIDS              (207)

/* configured number of Dem component IDs */
#define FIM_CFG_NUMBEROFDEMCOMPONENTIDS          (201)

/* FiM main function task time in ms */
#define FIM_CFG_TASK_TIME                        (10)

/* fiMRbCheckApiConsistency used to avoid double inclusion of function FiM_GetVersionInfo */
#define FIM_CFG_CHECK_API_CONSISTENCY            (TRUE)

#endif /* include protection */
