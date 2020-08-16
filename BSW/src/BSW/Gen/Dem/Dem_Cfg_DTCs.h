/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_DTCS_H
#define DEM_CFG_DTCS_H

#include "Std_Types.h"

/* ---------------------------------------- */
/* DEM_CFG_STOREWAITINGFORMONITORINGEVENT     */
/* ---------------------------------------- */
#define DEM_CFG_STOREWAITINGFORMONITORINGEVENT  FALSE

/* ---------------------------------------- */
/* DEM_CFG_DTCFILTER_EXTERNALPROCESSING     */
/* ---------------------------------------- */
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF  STD_OFF
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING_ON   STD_ON
#define DEM_CFG_DTCFILTER_EXTERNALPROCESSING      DEM_CFG_DTCFILTER_EXTERNALPROCESSING_OFF

/* --------------------------------------------------- */
/* DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED    */
/* --------------------------------------------------- */
#define DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED   FALSE

#define DEM_CFG_DTCSTATUS_AVAILABILITYMASK     0xFFu
#define DEM_CFG_DTC_TRANSLATION_TYPE           DEM_DTC_TRANSLATION_ISO14229_1

#define DEM_CFG_DTCSTATEMANGER_DTCS_PER_CYCLE   170u

/* --------------------------------------------------- */
/* DEM DTC STATE BITPOSITION                         */
/* --------------------------------------------------- */

#define DEM_DTC_BP_STATE_SUPPRESSED             0u
#define DEM_DTC_BP_GROUP_DTCSETTING_DISABLED    1u

typedef uint8 Dem_DtcStateType;
#define DEM_DTCSTATE_ISBITSET                    rba_DiagLib_Bit8IsBitSet
#define DEM_DTCSTATE_OVERWRITEBIT                rba_DiagLib_Bit8OverwriteBit
#define DEM_DTCSTATE_CLEARBIT                    rba_DiagLib_Bit8ClearBit
#define DEM_DTCSTATE_SETBIT                      rba_DiagLib_Bit8SetBit

/**
 * Selects a group of DTCs.
 */

/*                KIND                               SEVERITY                           NV-STORAGE  FUNC_UNIT                DTCCODE_IS_INDEX          */

#define DEM_CFG_DTCPARAMS8 \
{ \
    DEM_DTCS_INIT8(0u,                                0u,                                0u,         0u,                      FALSE                    )/* No DTC Assigned */ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P019900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x15u,                   FALSE                    )/*DemDTC_U010100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x16u,                   FALSE                    )/*DemDTC_U010200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x17u,                   FALSE                    )/*DemDTC_U010300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x18u,                   FALSE                    )/*DemDTC_U010400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x19u,                   FALSE                    )/*DemDTC_U010500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Au,                   FALSE                    )/*DemDTC_U010600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Bu,                   FALSE                    )/*DemDTC_U010700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Cu,                   FALSE                    )/*DemDTC_U010800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Du,                   FALSE                    )/*DemDTC_U010900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Eu,                   FALSE                    )/*DemDTC_U011000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x22u,                   FALSE                    )/*DemDTC_U011100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x26u,                   FALSE                    )/*DemDTC_U011200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Au,                   FALSE                    )/*DemDTC_U011300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Eu,                   FALSE                    )/*DemDTC_U011400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x32u,                   FALSE                    )/*DemDTC_U011500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x36u,                   FALSE                    )/*DemDTC_U011600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Cu,                   FALSE                    )/*DemDTC_U011700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Du,                   FALSE                    )/*DemDTC_U011800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Eu,                   FALSE                    )/*DemDTC_U011900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_U012000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_U012100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_U012288*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P020900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P021900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P022900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P023900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0241F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0242F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0243F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P024900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P025600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0101F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1u,                    FALSE                    )/*DemDTC_P0101F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2u,                    FALSE                    )/*DemDTC_P0102F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3u,                    FALSE                    )/*DemDTC_P0102F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x4u,                    FALSE                    )/*DemDTC_P010300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x5u,                    FALSE                    )/*DemDTC_P010400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x6u,                    FALSE                    )/*DemDTC_P010500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x7u,                    FALSE                    )/*DemDTC_P010600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x8u,                    FALSE                    )/*DemDTC_P010700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x9u,                    FALSE                    )/*DemDTC_P010800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xAu,                    FALSE                    )/*DemDTC_P010900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xBu,                    FALSE                    )/*DemDTC_P011000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xCu,                    FALSE                    )/*DemDTC_P011100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xDu,                    FALSE                    )/*DemDTC_P011200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xEu,                    FALSE                    )/*DemDTC_P011300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0xFu,                    FALSE                    )/*DemDTC_P011400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x10u,                   FALSE                    )/*DemDTC_P011500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x11u,                   FALSE                    )/*DemDTC_P011600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x12u,                   FALSE                    )/*DemDTC_P0117F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x13u,                   FALSE                    )/*DemDTC_P0117F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x14u,                   FALSE                    )/*DemDTC_P0117F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x1Fu,                   FALSE                    )/*DemDTC_P0118F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x20u,                   FALSE                    )/*DemDTC_P0118F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x21u,                   FALSE                    )/*DemDTC_P0118F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x23u,                   FALSE                    )/*DemDTC_P0119F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x24u,                   FALSE                    )/*DemDTC_P0119F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x25u,                   FALSE                    )/*DemDTC_P0119F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x27u,                   FALSE                    )/*DemDTC_P0120F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x28u,                   FALSE                    )/*DemDTC_P0120F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x29u,                   FALSE                    )/*DemDTC_P0120F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Bu,                   FALSE                    )/*DemDTC_P0121F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Cu,                   FALSE                    )/*DemDTC_P0121F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Du,                   FALSE                    )/*DemDTC_P0121F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x2Fu,                   FALSE                    )/*DemDTC_P0122F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x30u,                   FALSE                    )/*DemDTC_P0122F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x31u,                   FALSE                    )/*DemDTC_P0122F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x33u,                   FALSE                    )/*DemDTC_P0123F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x34u,                   FALSE                    )/*DemDTC_P0123F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x35u,                   FALSE                    )/*DemDTC_P0123F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x37u,                   FALSE                    )/*DemDTC_P012400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x38u,                   FALSE                    )/*DemDTC_P012500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x39u,                   FALSE                    )/*DemDTC_P012600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Au,                   FALSE                    )/*DemDTC_P012700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Bu,                   FALSE                    )/*DemDTC_P012800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x3Fu,                   FALSE                    )/*DemDTC_P012801*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x40u,                   FALSE                    )/*DemDTC_P012900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x41u,                   FALSE                    )/*DemDTC_P013000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x42u,                   FALSE                    )/*DemDTC_P013100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x43u,                   FALSE                    )/*DemDTC_P013200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x44u,                   FALSE                    )/*DemDTC_P013300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x45u,                   FALSE                    )/*DemDTC_P013400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x46u,                   FALSE                    )/*DemDTC_P0135F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x47u,                   FALSE                    )/*DemDTC_P0135F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x48u,                   FALSE                    )/*DemDTC_P0135F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x49u,                   FALSE                    )/*DemDTC_P0136F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x4Au,                   FALSE                    )/*DemDTC_P0136F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x4Bu,                   FALSE                    )/*DemDTC_P0136F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0137F0*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0137F1*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P0137F2*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P013800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P013900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P014900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P015900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P016900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017600*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017700*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017800*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P017900*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018000*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018100*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018200*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018300*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018400*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018500*/ \
    ,DEM_DTCS_INIT8(DEM_DTC_KIND_ALL_DTCS,             DEM_SEVERITY_NO_SEVERITY,          0u,         0x0u,                    FALSE                    )/*DemDTC_P018600*/ \
}

#define DEM_CFG_DTCPARAMS32 \
{ \
    DEM_DTCS_INIT32(0              )/* No DTC Assigned */ \
    ,DEM_DTCS_INIT32(0x18700        )/*DemDTC_P018700*/ \
    ,DEM_DTCS_INIT32(0x18800        )/*DemDTC_P018800*/ \
    ,DEM_DTCS_INIT32(0x18900        )/*DemDTC_P018900*/ \
    ,DEM_DTCS_INIT32(0x19000        )/*DemDTC_P019000*/ \
    ,DEM_DTCS_INIT32(0x19100        )/*DemDTC_P019100*/ \
    ,DEM_DTCS_INIT32(0x19200        )/*DemDTC_P019200*/ \
    ,DEM_DTCS_INIT32(0x19300        )/*DemDTC_P019300*/ \
    ,DEM_DTCS_INIT32(0x19400        )/*DemDTC_P019400*/ \
    ,DEM_DTCS_INIT32(0x19500        )/*DemDTC_P019500*/ \
    ,DEM_DTCS_INIT32(0x19600        )/*DemDTC_P019600*/ \
    ,DEM_DTCS_INIT32(0x19700        )/*DemDTC_P019700*/ \
    ,DEM_DTCS_INIT32(0x19800        )/*DemDTC_P019800*/ \
    ,DEM_DTCS_INIT32(0x19900        )/*DemDTC_P019900*/ \
    ,DEM_DTCS_INIT32(0xC10100       )/*DemDTC_U010100*/ \
    ,DEM_DTCS_INIT32(0xC10200       )/*DemDTC_U010200*/ \
    ,DEM_DTCS_INIT32(0xC10300       )/*DemDTC_U010300*/ \
    ,DEM_DTCS_INIT32(0xC10400       )/*DemDTC_U010400*/ \
    ,DEM_DTCS_INIT32(0xC10500       )/*DemDTC_U010500*/ \
    ,DEM_DTCS_INIT32(0xC10600       )/*DemDTC_U010600*/ \
    ,DEM_DTCS_INIT32(0xC10700       )/*DemDTC_U010700*/ \
    ,DEM_DTCS_INIT32(0xC10800       )/*DemDTC_U010800*/ \
    ,DEM_DTCS_INIT32(0xC10900       )/*DemDTC_U010900*/ \
    ,DEM_DTCS_INIT32(0xC11000       )/*DemDTC_U011000*/ \
    ,DEM_DTCS_INIT32(0xC11100       )/*DemDTC_U011100*/ \
    ,DEM_DTCS_INIT32(0xC11200       )/*DemDTC_U011200*/ \
    ,DEM_DTCS_INIT32(0xC11300       )/*DemDTC_U011300*/ \
    ,DEM_DTCS_INIT32(0xC11400       )/*DemDTC_U011400*/ \
    ,DEM_DTCS_INIT32(0xC11500       )/*DemDTC_U011500*/ \
    ,DEM_DTCS_INIT32(0xC11600       )/*DemDTC_U011600*/ \
    ,DEM_DTCS_INIT32(0xC11700       )/*DemDTC_U011700*/ \
    ,DEM_DTCS_INIT32(0xC11800       )/*DemDTC_U011800*/ \
    ,DEM_DTCS_INIT32(0xC11900       )/*DemDTC_U011900*/ \
    ,DEM_DTCS_INIT32(0xC12000       )/*DemDTC_U012000*/ \
    ,DEM_DTCS_INIT32(0xC12100       )/*DemDTC_U012100*/ \
    ,DEM_DTCS_INIT32(0xC12288       )/*DemDTC_U012288*/ \
    ,DEM_DTCS_INIT32(0x20000        )/*DemDTC_P020000*/ \
    ,DEM_DTCS_INIT32(0x20100        )/*DemDTC_P020100*/ \
    ,DEM_DTCS_INIT32(0x20200        )/*DemDTC_P020200*/ \
    ,DEM_DTCS_INIT32(0x20300        )/*DemDTC_P020300*/ \
    ,DEM_DTCS_INIT32(0x20400        )/*DemDTC_P020400*/ \
    ,DEM_DTCS_INIT32(0x20500        )/*DemDTC_P020500*/ \
    ,DEM_DTCS_INIT32(0x20600        )/*DemDTC_P020600*/ \
    ,DEM_DTCS_INIT32(0x20700        )/*DemDTC_P020700*/ \
    ,DEM_DTCS_INIT32(0x20800        )/*DemDTC_P020800*/ \
    ,DEM_DTCS_INIT32(0x20900        )/*DemDTC_P020900*/ \
    ,DEM_DTCS_INIT32(0x21000        )/*DemDTC_P021000*/ \
    ,DEM_DTCS_INIT32(0x21100        )/*DemDTC_P021100*/ \
    ,DEM_DTCS_INIT32(0x21200        )/*DemDTC_P021200*/ \
    ,DEM_DTCS_INIT32(0x21300        )/*DemDTC_P021300*/ \
    ,DEM_DTCS_INIT32(0x21400        )/*DemDTC_P021400*/ \
    ,DEM_DTCS_INIT32(0x21500        )/*DemDTC_P021500*/ \
    ,DEM_DTCS_INIT32(0x21600        )/*DemDTC_P021600*/ \
    ,DEM_DTCS_INIT32(0x21700        )/*DemDTC_P021700*/ \
    ,DEM_DTCS_INIT32(0x21800        )/*DemDTC_P021800*/ \
    ,DEM_DTCS_INIT32(0x21900        )/*DemDTC_P021900*/ \
    ,DEM_DTCS_INIT32(0x22000        )/*DemDTC_P022000*/ \
    ,DEM_DTCS_INIT32(0x22100        )/*DemDTC_P022100*/ \
    ,DEM_DTCS_INIT32(0x22200        )/*DemDTC_P022200*/ \
    ,DEM_DTCS_INIT32(0x22300        )/*DemDTC_P022300*/ \
    ,DEM_DTCS_INIT32(0x22400        )/*DemDTC_P022400*/ \
    ,DEM_DTCS_INIT32(0x22500        )/*DemDTC_P022500*/ \
    ,DEM_DTCS_INIT32(0x22600        )/*DemDTC_P022600*/ \
    ,DEM_DTCS_INIT32(0x22700        )/*DemDTC_P022700*/ \
    ,DEM_DTCS_INIT32(0x22800        )/*DemDTC_P022800*/ \
    ,DEM_DTCS_INIT32(0x22900        )/*DemDTC_P022900*/ \
    ,DEM_DTCS_INIT32(0x23000        )/*DemDTC_P023000*/ \
    ,DEM_DTCS_INIT32(0x23100        )/*DemDTC_P023100*/ \
    ,DEM_DTCS_INIT32(0x23200        )/*DemDTC_P023200*/ \
    ,DEM_DTCS_INIT32(0x23300        )/*DemDTC_P023300*/ \
    ,DEM_DTCS_INIT32(0x23400        )/*DemDTC_P023400*/ \
    ,DEM_DTCS_INIT32(0x23500        )/*DemDTC_P023500*/ \
    ,DEM_DTCS_INIT32(0x23600        )/*DemDTC_P023600*/ \
    ,DEM_DTCS_INIT32(0x23700        )/*DemDTC_P023700*/ \
    ,DEM_DTCS_INIT32(0x23800        )/*DemDTC_P023800*/ \
    ,DEM_DTCS_INIT32(0x23900        )/*DemDTC_P023900*/ \
    ,DEM_DTCS_INIT32(0x24000        )/*DemDTC_P024000*/ \
    ,DEM_DTCS_INIT32(0x241F0        )/*DemDTC_P0241F0*/ \
    ,DEM_DTCS_INIT32(0x242F1        )/*DemDTC_P0242F1*/ \
    ,DEM_DTCS_INIT32(0x243F0        )/*DemDTC_P0243F0*/ \
    ,DEM_DTCS_INIT32(0x24400        )/*DemDTC_P024400*/ \
    ,DEM_DTCS_INIT32(0x24500        )/*DemDTC_P024500*/ \
    ,DEM_DTCS_INIT32(0x24600        )/*DemDTC_P024600*/ \
    ,DEM_DTCS_INIT32(0x24700        )/*DemDTC_P024700*/ \
    ,DEM_DTCS_INIT32(0x24800        )/*DemDTC_P024800*/ \
    ,DEM_DTCS_INIT32(0x24900        )/*DemDTC_P024900*/ \
    ,DEM_DTCS_INIT32(0x25000        )/*DemDTC_P025000*/ \
    ,DEM_DTCS_INIT32(0x25100        )/*DemDTC_P025100*/ \
    ,DEM_DTCS_INIT32(0x25200        )/*DemDTC_P025200*/ \
    ,DEM_DTCS_INIT32(0x25300        )/*DemDTC_P025300*/ \
    ,DEM_DTCS_INIT32(0x25400        )/*DemDTC_P025400*/ \
    ,DEM_DTCS_INIT32(0x25500        )/*DemDTC_P025500*/ \
    ,DEM_DTCS_INIT32(0x25600        )/*DemDTC_P025600*/ \
    ,DEM_DTCS_INIT32(0x101F0        )/*DemDTC_P0101F0*/ \
    ,DEM_DTCS_INIT32(0x101F1        )/*DemDTC_P0101F1*/ \
    ,DEM_DTCS_INIT32(0x102F0        )/*DemDTC_P0102F0*/ \
    ,DEM_DTCS_INIT32(0x102F1        )/*DemDTC_P0102F1*/ \
    ,DEM_DTCS_INIT32(0x10300        )/*DemDTC_P010300*/ \
    ,DEM_DTCS_INIT32(0x10400        )/*DemDTC_P010400*/ \
    ,DEM_DTCS_INIT32(0x10500        )/*DemDTC_P010500*/ \
    ,DEM_DTCS_INIT32(0x10600        )/*DemDTC_P010600*/ \
    ,DEM_DTCS_INIT32(0x10700        )/*DemDTC_P010700*/ \
    ,DEM_DTCS_INIT32(0x10800        )/*DemDTC_P010800*/ \
    ,DEM_DTCS_INIT32(0x10900        )/*DemDTC_P010900*/ \
    ,DEM_DTCS_INIT32(0x11000        )/*DemDTC_P011000*/ \
    ,DEM_DTCS_INIT32(0x11100        )/*DemDTC_P011100*/ \
    ,DEM_DTCS_INIT32(0x11200        )/*DemDTC_P011200*/ \
    ,DEM_DTCS_INIT32(0x11300        )/*DemDTC_P011300*/ \
    ,DEM_DTCS_INIT32(0x11400        )/*DemDTC_P011400*/ \
    ,DEM_DTCS_INIT32(0x11500        )/*DemDTC_P011500*/ \
    ,DEM_DTCS_INIT32(0x11600        )/*DemDTC_P011600*/ \
    ,DEM_DTCS_INIT32(0x117F0        )/*DemDTC_P0117F0*/ \
    ,DEM_DTCS_INIT32(0x117F1        )/*DemDTC_P0117F1*/ \
    ,DEM_DTCS_INIT32(0x117F2        )/*DemDTC_P0117F2*/ \
    ,DEM_DTCS_INIT32(0x118F0        )/*DemDTC_P0118F0*/ \
    ,DEM_DTCS_INIT32(0x118F1        )/*DemDTC_P0118F1*/ \
    ,DEM_DTCS_INIT32(0x118F2        )/*DemDTC_P0118F2*/ \
    ,DEM_DTCS_INIT32(0x119F0        )/*DemDTC_P0119F0*/ \
    ,DEM_DTCS_INIT32(0x119F1        )/*DemDTC_P0119F1*/ \
    ,DEM_DTCS_INIT32(0x119F2        )/*DemDTC_P0119F2*/ \
    ,DEM_DTCS_INIT32(0x120F0        )/*DemDTC_P0120F0*/ \
    ,DEM_DTCS_INIT32(0x120F1        )/*DemDTC_P0120F1*/ \
    ,DEM_DTCS_INIT32(0x120F2        )/*DemDTC_P0120F2*/ \
    ,DEM_DTCS_INIT32(0x121F0        )/*DemDTC_P0121F0*/ \
    ,DEM_DTCS_INIT32(0x121F1        )/*DemDTC_P0121F1*/ \
    ,DEM_DTCS_INIT32(0x121F2        )/*DemDTC_P0121F2*/ \
    ,DEM_DTCS_INIT32(0x122F0        )/*DemDTC_P0122F0*/ \
    ,DEM_DTCS_INIT32(0x122F1        )/*DemDTC_P0122F1*/ \
    ,DEM_DTCS_INIT32(0x122F2        )/*DemDTC_P0122F2*/ \
    ,DEM_DTCS_INIT32(0x123F0        )/*DemDTC_P0123F0*/ \
    ,DEM_DTCS_INIT32(0x123F1        )/*DemDTC_P0123F1*/ \
    ,DEM_DTCS_INIT32(0x123F2        )/*DemDTC_P0123F2*/ \
    ,DEM_DTCS_INIT32(0x12400        )/*DemDTC_P012400*/ \
    ,DEM_DTCS_INIT32(0x12500        )/*DemDTC_P012500*/ \
    ,DEM_DTCS_INIT32(0x12600        )/*DemDTC_P012600*/ \
    ,DEM_DTCS_INIT32(0x12700        )/*DemDTC_P012700*/ \
    ,DEM_DTCS_INIT32(0x12800        )/*DemDTC_P012800*/ \
    ,DEM_DTCS_INIT32(0x12801        )/*DemDTC_P012801*/ \
    ,DEM_DTCS_INIT32(0x12900        )/*DemDTC_P012900*/ \
    ,DEM_DTCS_INIT32(0x13000        )/*DemDTC_P013000*/ \
    ,DEM_DTCS_INIT32(0x13100        )/*DemDTC_P013100*/ \
    ,DEM_DTCS_INIT32(0x13200        )/*DemDTC_P013200*/ \
    ,DEM_DTCS_INIT32(0x13300        )/*DemDTC_P013300*/ \
    ,DEM_DTCS_INIT32(0x13400        )/*DemDTC_P013400*/ \
    ,DEM_DTCS_INIT32(0x135F0        )/*DemDTC_P0135F0*/ \
    ,DEM_DTCS_INIT32(0x135F1        )/*DemDTC_P0135F1*/ \
    ,DEM_DTCS_INIT32(0x135F2        )/*DemDTC_P0135F2*/ \
    ,DEM_DTCS_INIT32(0x136F0        )/*DemDTC_P0136F0*/ \
    ,DEM_DTCS_INIT32(0x136F1        )/*DemDTC_P0136F1*/ \
    ,DEM_DTCS_INIT32(0x136F2        )/*DemDTC_P0136F2*/ \
    ,DEM_DTCS_INIT32(0x137F0        )/*DemDTC_P0137F0*/ \
    ,DEM_DTCS_INIT32(0x137F1        )/*DemDTC_P0137F1*/ \
    ,DEM_DTCS_INIT32(0x137F2        )/*DemDTC_P0137F2*/ \
    ,DEM_DTCS_INIT32(0x13800        )/*DemDTC_P013800*/ \
    ,DEM_DTCS_INIT32(0x13900        )/*DemDTC_P013900*/ \
    ,DEM_DTCS_INIT32(0x14000        )/*DemDTC_P014000*/ \
    ,DEM_DTCS_INIT32(0x14100        )/*DemDTC_P014100*/ \
    ,DEM_DTCS_INIT32(0x14200        )/*DemDTC_P014200*/ \
    ,DEM_DTCS_INIT32(0x14300        )/*DemDTC_P014300*/ \
    ,DEM_DTCS_INIT32(0x14400        )/*DemDTC_P014400*/ \
    ,DEM_DTCS_INIT32(0x14500        )/*DemDTC_P014500*/ \
    ,DEM_DTCS_INIT32(0x14600        )/*DemDTC_P014600*/ \
    ,DEM_DTCS_INIT32(0x14700        )/*DemDTC_P014700*/ \
    ,DEM_DTCS_INIT32(0x14800        )/*DemDTC_P014800*/ \
    ,DEM_DTCS_INIT32(0x14900        )/*DemDTC_P014900*/ \
    ,DEM_DTCS_INIT32(0x15000        )/*DemDTC_P015000*/ \
    ,DEM_DTCS_INIT32(0x15100        )/*DemDTC_P015100*/ \
    ,DEM_DTCS_INIT32(0x15200        )/*DemDTC_P015200*/ \
    ,DEM_DTCS_INIT32(0x15300        )/*DemDTC_P015300*/ \
    ,DEM_DTCS_INIT32(0x15400        )/*DemDTC_P015400*/ \
    ,DEM_DTCS_INIT32(0x15500        )/*DemDTC_P015500*/ \
    ,DEM_DTCS_INIT32(0x15600        )/*DemDTC_P015600*/ \
    ,DEM_DTCS_INIT32(0x15700        )/*DemDTC_P015700*/ \
    ,DEM_DTCS_INIT32(0x15800        )/*DemDTC_P015800*/ \
    ,DEM_DTCS_INIT32(0x15900        )/*DemDTC_P015900*/ \
    ,DEM_DTCS_INIT32(0x16000        )/*DemDTC_P016000*/ \
    ,DEM_DTCS_INIT32(0x16100        )/*DemDTC_P016100*/ \
    ,DEM_DTCS_INIT32(0x16200        )/*DemDTC_P016200*/ \
    ,DEM_DTCS_INIT32(0x16300        )/*DemDTC_P016300*/ \
    ,DEM_DTCS_INIT32(0x16400        )/*DemDTC_P016400*/ \
    ,DEM_DTCS_INIT32(0x16500        )/*DemDTC_P016500*/ \
    ,DEM_DTCS_INIT32(0x16600        )/*DemDTC_P016600*/ \
    ,DEM_DTCS_INIT32(0x16700        )/*DemDTC_P016700*/ \
    ,DEM_DTCS_INIT32(0x16800        )/*DemDTC_P016800*/ \
    ,DEM_DTCS_INIT32(0x16900        )/*DemDTC_P016900*/ \
    ,DEM_DTCS_INIT32(0x17000        )/*DemDTC_P017000*/ \
    ,DEM_DTCS_INIT32(0x17100        )/*DemDTC_P017100*/ \
    ,DEM_DTCS_INIT32(0x17200        )/*DemDTC_P017200*/ \
    ,DEM_DTCS_INIT32(0x17300        )/*DemDTC_P017300*/ \
    ,DEM_DTCS_INIT32(0x17400        )/*DemDTC_P017400*/ \
    ,DEM_DTCS_INIT32(0x17500        )/*DemDTC_P017500*/ \
    ,DEM_DTCS_INIT32(0x17600        )/*DemDTC_P017600*/ \
    ,DEM_DTCS_INIT32(0x17700        )/*DemDTC_P017700*/ \
    ,DEM_DTCS_INIT32(0x17800        )/*DemDTC_P017800*/ \
    ,DEM_DTCS_INIT32(0x17900        )/*DemDTC_P017900*/ \
    ,DEM_DTCS_INIT32(0x18000        )/*DemDTC_P018000*/ \
    ,DEM_DTCS_INIT32(0x18100        )/*DemDTC_P018100*/ \
    ,DEM_DTCS_INIT32(0x18200        )/*DemDTC_P018200*/ \
    ,DEM_DTCS_INIT32(0x18300        )/*DemDTC_P018300*/ \
    ,DEM_DTCS_INIT32(0x18400        )/*DemDTC_P018400*/ \
    ,DEM_DTCS_INIT32(0x18500        )/*DemDTC_P018500*/ \
    ,DEM_DTCS_INIT32(0x18600        )/*DemDTC_P018600*/ \
}

/*                DTCGROUPCODE  */

#define DEM_CFG_DTCGROUPPARAMS \
{ \
    DEM_DTCGROUPS_INIT(0       )/* No DTCGROUP Assigned */ \
,DEM_DTCGROUPS_INIT(DEM_DTC_GROUP_ALL_DTCS) /* DEM_DTC_GROUP_ALL_DTCS */\
}

#define DEM_DTC_FILTER_NUMBER_OF_EVENTS_PER_CYCLE    25u
#define DEM_DTC_FILTER_RETRIEVE_NUMBER_OF_DTCS       50u

#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF STD_OFF
#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON STD_ON

#define DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_OFF

#endif

