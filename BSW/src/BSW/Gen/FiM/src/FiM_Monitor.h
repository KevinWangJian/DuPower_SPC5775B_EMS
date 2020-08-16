

/**
 **************************************************************************************************
 * FiM_Monitot.h
 * header for background monitor or FiM
 **************************************************************************************************
 */

#ifndef FIM_MONITOR_H
#define FIM_MONITOR_H

#include "FiM_Priv_Data.h"

/**
 **************************************************************************************************
 * type definitions
 **************************************************************************************************
 */

typedef enum
{
    FIM_PRIV_MONSTATE_INIT = 0, FIM_PRIV_MONSTATE_CHECK, FIM_PRIV_MONSTATE_CALLBACK
} FiM_Priv_MonitorStateType;

/* check the configured number of FIds per cycle, but maximum the total number of FIds */
#if (FIM_CFG_FIDS_PER_MONITORCYCLE_ECUC > FIM_CFG_NUMBEROFFIDS)
#define FIM_PRIV_FIDSPERMONITORCALLBACK         FIM_CFG_NUMBEROFFIDS
#else
#define FIM_PRIV_FIDSPERMONITORCALLBACK         FIM_CFG_FIDS_PER_MONITORCYCLE_ECUC
#endif

/* check the configured number of events and components per monitoring cycle,
 * but maximum is the total number of events plus components */
#if (FIM_CFG_EVENTS_PER_MONITORCYCLE_ECUC > FIM_CFG_NUMBEROFDEMEVENTIDS + FIM_CFG_NUMBEROFDEMCOMPONENTIDS)
#define FIM_PRIV_LINKSPERMONITORCHECK      (FIM_CFG_NUMBEROFDEMEVENTIDS + FIM_CFG_NUMBEROFDEMCOMPONENTIDS)
#else
#define FIM_PRIV_LINKSPERMONITORCHECK      FIM_CFG_EVENTS_PER_MONITORCYCLE_ECUC
#endif

/**
 **************************************************************************************************
 * function prototypes
 **************************************************************************************************
 */

#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_Priv_MonitorProc(void);

void FiM_Priv_MonitorInit(void);

/*functions are only required by test cases */
#ifdef FIM_UNIT_TEST_SUITE
FiM_Priv_MonitorStateType FiM_Priv_MonitorGetState(void);
void FiM_Priv_MonitorSetState(FiM_Priv_MonitorStateType newState);
#endif

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"

#endif /* include protection */

