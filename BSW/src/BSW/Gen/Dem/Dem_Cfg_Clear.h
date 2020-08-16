/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_CLEAR_H
#define DEM_CFG_CLEAR_H

/* ---------------------------------------- */
/* DEM_CFG_CLEAR_DTC_BEHAVIOR               */
/* ---------------------------------------- */
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH     1
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_TRIGGER    2
#define DEM_CFG_CLEAR_DTC_BEHAVIOR_VOLATILE               3
#define DEM_CFG_CLEAR_DTC_BEHAVIOR                        DEM_CFG_CLEAR_DTC_BEHAVIOR_NONVOLATILE_FINISH

/* ---------------------------------------- */
/* DEM_CFG_CLEAR_DTC_LIMITATION               */
/* ---------------------------------------- */
#define DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS     1
#define DEM_CFG_CLEAR_DTC_LIMITATION_ONLY_CLEAR_ALL_DTCS    2
#define DEM_CFG_CLEAR_DTC_LIMITATION                        DEM_CFG_CLEAR_DTC_LIMITATION_ALL_SUPPORTED_DTCS

/* ----------------------------------------------- */
/* DEM_CFG_CLEAR_DTC_NOTIFICATION_ALLOWEDCALLBACK  */
/* ----------------------------------------------- */
#define DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED_OFF		STD_OFF
#define DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED_ON 		STD_ON
#define DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED       DEM_CFG_CLEAR_DTC_NOTIFICATION_CALLBACK_ALLOWED_OFF

#define DEM_CFG_CLEAR_MAX_NO_OF_EVENTS_PER_CYCLE    207u

#endif

