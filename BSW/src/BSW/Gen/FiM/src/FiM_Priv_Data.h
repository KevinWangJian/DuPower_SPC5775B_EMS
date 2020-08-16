

#ifndef FIM_PRIV_DATA_H
#define FIM_PRIV_DATA_H

/**
 **************************************************************************************************
 * Includes
 **************************************************************************************************
 */

#include "FiM_Cfg_Fids.h"
#include "FiM_Cfg.h"
/**
 **************************************************************************************************
 * FiM configuration derived types
 **************************************************************************************************
 */

/* Fim inhibition mask configuration [AR402:FIM096_Conf], */
/* values for FiM_InhibitionMaskType */
#define FIM_RB_NO_INHIBITS              0u  /* limit added for neutral calibration, RB-specific */
#define FIM_CFG_LAST_FAILED             1u  /* TESTFAILED = 1 */
#define FIM_CFG_NOT_TESTED              2u  /* TNCTOC = 1 */
#define FIM_CFG_TESTED                  3u  /* TNCTOC = 0 */
#define FIM_CFG_TESTED_AND_FAILED       4u  /* TESTFAILED = 1 AND TNCTOC = 0 */
#define FIM_CFG_FAILED_OR_NOT_TESTED    5u  /* TESTFAILED = 1 OR TNCTOC = 1, RB-specific */

/* type for FiM status handling */

#if (FIM_CFG_MAXIMUM_LINKS_PER_FID_CALC <= 0xFF)
typedef uint8 FiM_FIdStatusCounterType;
#define FIM_CFG_STATUSCOUNTERMAX 0xFF
#else
typedef uint16 FiM_FIdStatusCounterType;
#define FIM_CFG_STATUSCOUNTERMAX 0xFFFF
#endif


#endif /* include protection */
