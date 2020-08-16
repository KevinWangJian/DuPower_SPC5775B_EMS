/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef FIM_CFG_PBCFG_H
#define FIM_CFG_PBCFG_H

#include "FiM_Types.h"

/*
 ***************************************************************************************************
 * Function Prototypes
 ***************************************************************************************************
 */

/* FiMConfigSet global structure of type FiM_ConfigType */
#define FIM_START_SEC_ROM_CONST
#include "FiM_MemMap.h"

extern const FiM_ConfigType FiMConfigSet;
#define FIM_POSTBUILD_CONFIGSET_NAME FiMConfigSet

#define FIM_STOP_SEC_ROM_CONST
#include "FiM_MemMap.h"
#endif /* include protection */ 
