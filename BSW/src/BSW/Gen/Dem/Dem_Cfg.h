/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_H
#define DEM_CFG_H

/* ---------------------------------------- */
/* OBD and BFM switches included for
 COMASSO Configuration                    */
/* ---------------------------------------- */

/* ----------------------------------------------------------------------------
 OBD switch
 ----------------------------------------------------------------------------
 */

#define DEM_CFG_OBD_OFF 	0                /* OBD not supported */
#define DEM_CFG_OBD_ON  	1                /* OBD supported */
#define DEM_CFG_OBD        DEM_CFG_OBD_OFF

/* ----------------------------------------------------------------------------
 J1939DCM switch
 ----------------------------------------------------------------------------
 */

#define DEM_CFG_J1939DCM_OFF     0                /* J1939DCM not supported */
#define DEM_CFG_J1939DCM_ON      1                /* J1939DCM supported */
#define DEM_CFG_J1939DCM       DEM_CFG_J1939DCM_OFF

#define DEM_CFG_J1939DCM_CLEAR_SUPPORT       DEM_CFG_J1939DCM_OFF

/* ----------------------------------------------------------------------------
 BFM switch
 ----------------------------------------------------------------------------
 */
#ifndef DEM_BFM_ON
#define DEM_BFM_ON 1                    /* BFM supported */
#endif
#ifndef DEM_BFM_OFF                     /* BFM not supported */
#define DEM_BFM_OFF 0
#endif

#ifndef DEM_CATPRIO_ON
#define DEM_CATPRIO_ON   1              /*Event category priority supported*/
#endif
#ifndef DEM_CATPRIO_OFF
#define DEM_CATPRIO_OFF  0              /*Event category priority not supported*/
#endif

#define DEM_BFM_ENABLED  DEM_BFM_OFF

#ifndef DEM_BFM_ENABLED
#define DEM_BFM_ENABLED  DEM_BFM_OFF
#endif

/* ---------------------------------------- */
/* Dem API Features                         */
/* ---------------------------------------- */
/* Only define switches here that enable or disable the availability of an API */

#define DEM_CFG_TRIGGER_TO_STORE_NVM_SUPPORTED            FALSE
#define DEM_CFG_SUSPICIOUS_SUPPORT                        FALSE
#define DEM_CFG_DEBTIMEBASED_CONFIGURED_CYCLICTASKTIME    FALSE
#define DEM_CFG_EVMEMGENERIC_SUPPORTED                    TRUE

#define DEM_CFG_VERSION_INFO_API_OFF          STD_OFF
#define DEM_CFG_VERSION_INFO_API_ON           STD_ON
#define DEM_CFG_VERSION_INFO_API              DEM_CFG_VERSION_INFO_API_OFF

#define DEM_CFG_ALTERNATIVEDTC_OFF                   STD_OFF
#define DEM_CFG_ALTERNATIVEDTC_ON                    STD_ON
#define DEM_CFG_ALTERNATIVEDTC  DEM_CFG_ALTERNATIVEDTC_OFF

#define DEM_CFG_ERASE_ALL_OFF                           0u
#define DEM_CFG_ERASE_ALL_WITHOUT_HASHID_CHECK          1u
#define DEM_CFG_ERASE_ALL_WITH_HASHID_CHECK             2u
#define DEM_CFG_ERASE_ALL_DATA_SUPPORTED                DEM_CFG_ERASE_ALL_OFF

#define DEM_CFG_DEPENDENCY_OFF         STD_OFF
#define DEM_CFG_DEPENDENCY_ON          STD_ON
#define DEM_CFG_DEPENDENCY             DEM_CFG_DEPENDENCY_OFF

#define DEM_CFG_TESTMODE_SUPPORT_ON       STD_ON
#define DEM_CFG_TESTMODE_SUPPORT_OFF      STD_OFF

#define DEM_CFG_TESTMODE_SUPPORT          DEM_CFG_TESTMODE_SUPPORT_OFF

/* ---------------------------------------- */
/* Check Consistency between RTE and C API  */
/* ---------------------------------------- */
#define DEM_CFG_CHECKAPICONSISTENCY    TRUE

/* ---------------------------------------- */
/* DEM_CFG_DEBUGDATA                        */
/* ---------------------------------------- */
#define DEM_CFG_DEBUGDATA_OFF     0
#define DEM_CFG_DEBUGDATA_8BIT    (0+1)
#define DEM_CFG_DEBUGDATA_32BIT   (0+4)
#define DEM_CFG_DEBUGDATA         DEM_CFG_DEBUGDATA_32BIT

#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
/* MR12 RULE 20.7 VIOLATION: Macro parameter may not be enclosed in (). */
#define DEM_DEBUGDATA_PARAM(A,B)    ,A,B
#else
#define DEM_DEBUGDATA_PARAM(A,B)
#endif

#endif

