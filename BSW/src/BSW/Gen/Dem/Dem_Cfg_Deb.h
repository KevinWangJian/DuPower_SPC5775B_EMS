/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_DEB_H
#define DEM_CFG_DEB_H

#include "Std_Types.h"

/* ---------------------------------------- */
/* DEM_CFG_DEBMONINTBASE                    */
/* ---------------------------------------- */
#define DEM_CFG_DEBMONINTERNAL_OFF  STD_OFF
#define DEM_CFG_DEBMONINTERNAL_ON   STD_ON
#define DEM_CFG_DEBMONINTERNAL  DEM_CFG_DEBMONINTERNAL_OFF

/* ---------------------------------------- */
/* DEM_CFG_DEBARTIMEBASE                    */
/* ---------------------------------------- */
#define DEM_CFG_DEBARTIMEBASE_OFF  STD_OFF
#define DEM_CFG_DEBARTIMEBASE_ON   STD_ON
#define DEM_CFG_DEBARTIMEBASE  DEM_CFG_DEBARTIMEBASE_OFF

/* ---------------------------------------- */
/* DEM_CFG_DEBCOUNTERBASEDCLASS             */
/* ---------------------------------------- */
#define DEM_CFG_DEBCOUNTERBASECLASS_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS  DEM_CFG_DEBCOUNTERBASECLASS_ON

#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_OFF  STD_OFF
#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_ON   STD_ON
#define DEM_CFG_LIMIT_RELEVANTFOR_JUMPING DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_OFF

#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT 32767
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MINLIMIT -32768
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED TRUE
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_VALUE 0
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED TRUE
#define DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_VALUE 0

#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD  DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD  DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE  DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE  DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON

#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN  DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_OFF

#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_OFF  STD_OFF
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_ON   STD_ON
#define DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP  DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_OFF

#define DEMRB_DEBOUNCECOUNTERSETS_SIZE                                 2
/** Offset of the CounterSet Id where the custom counter sets start */
#define DEMRB_DEBOUNCECOUNTERSETS_CUSTOMSETSOFFSET                     2

#define DemConf_DemRbDebounceCounterSet_Standard                       0
#define DemConf_DemRbDebounceCounterSet_Alternative                    1

#define DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH 1

/*                 				ISJDOWN             ISJUP               MINLIMIT                      MAXLIMIT                      JDOWNValue          JUPValue            FDC_THRESHOLD       SUSPICIOUS_THRESHOLD STEPUP             STEPDOWN             */

#define DEM_CFG_DEBCOUNTERCLASS_PARAMSETS \
{ \
  { /* Default Debouncing Parameters */ \
   DEM_DEBCOUNTERBASECLASS_INIT (DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED,-2,2,0,                 0,                  DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,DEM_MAXSINT16,1,   -1                  ), \
}, \
  { /* Alternative Debouncing Parameters */  \
   DEM_DEBCOUNTERBASECLASS_INIT (DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED,DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED,-2,2,0,                 0,                  DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT,DEM_MAXSINT16,1,   -1                  ), \
  }, \
}

#define DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS   0

#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0101F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0101F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0102F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0102F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P010900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P011600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0117F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0117F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0117F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0118F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0118F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0118F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0119F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0119F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0119F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0120F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0120F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0120F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0121F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0121F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0121F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0122F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0122F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0122F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0123F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0123F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0123F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012801      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P012900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0135F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0135F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0135F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0136F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0136F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0136F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0137F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0137F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0137F2      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P013900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P014900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P015900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P016900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P017900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P018900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P019900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P020900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P021900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P022900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P023900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0241F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0242F1      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P0243F0      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P024900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_P025600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U010900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011200      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011300      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011400      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011500      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011600      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011700      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011800      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U011900      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U012000      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U012100      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS
#define DEM_DEBPARAM_IDX_DEMEVENTPARAMETER_U012288      DEM_DEBPARAMCLASS_IDX_DEMDEBOUNCECOUNTERBASEDCLASS

#define DEM_CFG_DEB_DEFINE_ALL_PARAMSETS \
static const Dem_DebCounterBaseClass_ParamSet  Dem_Cfg_DebCounterBaseClass_Paramsets[DEMRB_DEBOUNCECOUNTERSETS_SIZE][DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH] = DEM_CFG_DEBCOUNTERCLASS_PARAMSETS; \


#define  DEM_CFG_DEB_CLASSES \
{ \
   { \
      NULL_PTR, \
      NULL_PTR, \
      NULL_PTR, \
      0, \
      NULL_PTR \
   } \
   ,{ \
      &Dem_DebCounterBaseClass_GetLimits, \
      NULL_PTR, \
      &Dem_Cfg_DebCounterBaseClass_Paramsets[DemConf_DemRbDebounceCounterSet_Standard], \
      DEM_CFG_DEBCOUNTERBASECLASS_PARAMSET_LENGTH, \
      &Dem_DebCounterBaseClass_Filter \
   } \
}

#define  DEM_CFG_DEB_NUMBEROFCLASSES  2

#define DEM_DEBMETH_IDX_ARCTRBASECLASS      (1)

/* Support Debouncer Reset After StorageCondition */
#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_OFF                                    0u
#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_ACCORDING_DEBOUNCEBEHAVIOR             1u

#define DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO           DEM_CFG_SUPPORT_DEB_RESET_AFTER_STOCO_OFF

#endif
