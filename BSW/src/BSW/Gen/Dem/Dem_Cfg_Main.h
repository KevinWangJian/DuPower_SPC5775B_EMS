/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_MAIN_H
#define DEM_CFG_MAIN_H

/* ---------------------------------------- */
/* DEM_CFG_BUILDTARGET                      */
/* ---------------------------------------- */
#define DEM_CFG_BUILDTARGET_ECU             1
#define DEM_CFG_BUILDTARGET_DEMTESTSUITE    2
#define DEM_CFG_BUILDTARGET_DIAGNOSISBUILD  3

#ifdef DEM_TESTSUITE
#define DEM_CFG_BUILDTARGET  DEM_CFG_BUILDTARGET_DEMTESTSUITE
#else
#ifdef DEV_DIAG
#define DEM_CFG_BUILDTARGET  DEM_CFG_BUILDTARGET_DIAGNOSISBUILD
#else
#define DEM_CFG_BUILDTARGET  DEM_CFG_BUILDTARGET_ECU
#endif
#endif

#define DEM_MAIN_CYCLETIME  10

/* ---------------------------------------- */
/* DEM_CFG_DEVERRORDETECT                   */
/* ---------------------------------------- */
#define DEM_CFG_DEVERRORDETECT_OFF          STD_OFF
#define DEM_CFG_DEVERRORDETECT_ON           STD_ON
#define DEM_CFG_DEVERRORDETECT              DEM_CFG_DEVERRORDETECT_ON

/* ---------------------------------------- */
/* DEM_CFG_EVENT_AND_DTCSUPPRESSION         */
/* ---------------------------------------- */
#define DEM_NO_SUPPRESSION						      STD_OFF
#define DEM_EVENT_SUPPRESSION				          STD_ON
#define DEM_DTC_SUPPRESSION 					      (STD_ON+STD_OFF+1)
#define DEM_EVENT_AND_DTC_SUPPRESSION			      (DEM_DTC_SUPPRESSION+1)
#define DEM_CFG_SUPPRESSION                           DEM_EVENT_SUPPRESSION

#define DEM_CFG_ADVANCEOPERATIONCYCLE_EVENTSPERLOCK      16u

#endif

