


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: Com / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/

#ifndef COM_CFG_INTERNAL_H
#define COM_CFG_INTERNAL_H

/*  START: Local #defines  */


#define COM_TX_TIME_BASE         ( 0.01f )

#define COM_RX_TIME_BASE         ( 0.01f )

#define COM_GW_TIME_BASE         ( 0.005f )

/************************************************************************/
/************************ UPDATE_BIT switches ***************************/
/************************************************************************/

/* #define COM_RxSigUpdateBit */

/* #define COM_TxSigUpdateBit */

/* #define COM_RxSigGrpUpdateBit */

/* #define COM_TxSigGrpUpdateBit */

#if (defined(COM_RxSigUpdateBit) || defined(COM_TxSigUpdateBit) || defined(COM_RxSigGrpUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_UPDATEBIT
#endif /* #if (defined(COM_RxSigUpdateBit) || defined(COM_TxUpdateBit) || defined(COM_RxSigGrpUpdateBit) || defined(COM_TxSigGrpUpdateBit)) */
/************************************************************************/
/************************************************************************/

/************************ RX TIME OUT switches **************************/
/************************************************************************/

/* #define COM_RxSigUpdateTimeout */

/* #define COM_RxSigGrpUpdateTimeout */

/* #define  COM_RxUpdateTimeoutNotify */

#define COM_RxIPduTimeout

#define COM_RxIPduTimeoutNotify
/************************************************************************/

/************************ TX TIME OUT switches **************************/
/************************************************************************/

#define COM_TxIPduTimeOut

/* #define COM_TxIPduTimeOutNotify */
/************************************************************************/
/************************************************************************/

/********************* RX NOTIFICATION switches *************************/
/************************************************************************/

#define COM_RxSignalNotify

/* #define COM_RxIPduNotification */

/* #define COM_RxSignalGrpNotify */
/************************************************************************/
/************************************************************************/


/********************* FILTER related switches **************************/
/************************************************************************/

/* #define COM_RxFilters */

/* #define COM_TxFilters */

#if (defined(COM_RxFilters) || defined(COM_TxFilters))
#define COM_FILTERS
#endif

/* #define COM_F_MASKEDNEWEQUALSX */

/* #define COM_F_MASKEDNEWDIFFERSX */

/* #define COM_F_MASKEDNEWDIFFERSOLD */

/* #define COM_F_NEWISWITHIN_POS */

/* #define COM_F_NEWISWITHIN_NEG */

/* #define COM_F_NEWISOUTSIDE_POS */

/* #define COM_F_NEWISOUTSIDE_NEG */

/* #define COM_F_ONEEVERYN */
/************************************************************************/
/************************************************************************/

/*********************** RX INVALID switches ****************************/
/************************************************************************/

/* #define COM_RxSigInvalid */

/* #define COM_RxSigInvalidNotify */

/* #define COM_RxSigGrpInvalid */

/* #define COM_RxSigGrpInvalidNotify */

/* #define COM_RxSigGrpInvalidActionReplace */

/************************************************************************/
/************************************************************************/

/*********************** TX INVALID switches ****************************/
/************************************************************************/
/* #define COM_TxInvalid */

/* #define COM_TxGrpSigInvalid */
/************************************************************************/
/************************************************************************/

/********************* UINT64/SINT64 switches ***************************/
/* #define COM_TXSIG_INT64 */

/* #define COM_RXSIG_INT64 */

/* #define COM_TXGRPSIG_INT64 */

/* #define COM_RXGRPSIG_INT64 */
/************************************************************************/

/********************* DYNAMIC SIGNAL switches **********************/
/************************************************************************/
/* #define COM_TX_DYNAMIC_SIGNAL_SUPPORT */


/* #define COM_RX_DYNAMIC_SIGNAL_SUPPORT */

/********************* FLOAT64 switches **********************/
/************************************************************************/
/* #define COM_TXGRPSIG_FLOAT64SUPP */

/* #define COM_TXSIG_FLOAT64SUPP */

/* #define COM_RXSIG_FLOAT64SUPP */

/* #define COM_RXGRPSIG_FLOAT64SUPP */

/* #define COM_FLOAT32SUPP */
/* #define COM_GRPSIGFLOAT32SUPP */

/************************** Misc FEATURES *******************************/
/************************************************************************/

/* #define COM_ERRORNOTIFICATION */

/* #define COM_TXDOUBLEBUFFER */

#define COM_RxIPduCallOuts

/* #define COM_TxIPduCallOuts */

#define COM_TxIPduNotification

#define COM_CONFIGURATION_USE_DET           STD_OFF

/*Currently for PBL support, this macro should always be enabled */
#define COM_VERSION_INFO_API                STD_OFF


#define COM_COMMON_TX_PERIOD                STD_OFF
#define COM_ENABLE_JITTERFLITER             STD_OFF
/* #define COM_ENABLE_READRXIPDULENGTH */

/* #define COM_TX_IPDUCONTROL_VIA_CALIBRATION */

/* #define COM_RX_IPDUCONTROL_VIA_CALIBRATION */

/* #define COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */

/* #define COM_RXPDU_TIMEOUT_VIA_CALIBRATION */
/* #define COM_TXPDU_DEFERREDPROCESSING */

#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
#define COM_TX_TIME_BASE_IN_MS   ( (uint16)10 )
#endif

#define COM_ARSRVLIB_SUPPORT
/* #define COM_PROVIDE_IPDU_STATUS */

/* #define COM_MULTICORE_SUPPORT */

/* #define COM_METADATA_SUPPORT */

/* #define COM_SIGNALGATEWAY */

/* #define COM_SIGNALGROUPGATEWAY */

/* #define COM_TP_IPDUTYPE */

/* #define COM_CANCELTRANSMITSUPPORT */


/* #define COM_TX_SIGNALGROUP_ARRAY */


/* #define COM_RX_SIGNALGROUP_ARRAY */


/************************************************************************/
/************************************************************************/



#define COM_RXTIMER_MAX            0xFFFFu

/********************* TRANSFER PROPERTY  switches **********************/
/************************************************************************/

/*#define COM_SigTriggeredOnChange*/


/*#define COM_SigGrpTriggeredOnChange*/

/************************************************************************/
/************************************************************************/

#define COM_CONFIGURATION_ID                0

#define COM_NUM_TOTAL_IPDU_GRP              2u


/******************* RX IPdu Deferred Processing ************************/
/************************************************************************/
/* #define COM_RxIPduDeferredProcessing */
/* #define COM_RxSignalGrpDeferredProcessing */

/************************************************************************/
/************************************************************************/

/*#define COM_MIXEDPHASESHIFT*/

  

/*  END: Local #defines  */

/* Start Type Declarations*/


/* Filter type */
#if defined(COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)
    typedef struct
    {
        uint32 Mask;
        uint32 X_Val;
    }Com_MaskXType;
#endif
#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
    typedef struct
    {
        uint32 Min;
        uint32 Max;
    }Com_POSMinMaxType;
#endif
#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
    typedef struct
    {
        sint32 Min;
        sint32 Max;
    }Com_NEGMinMaxType;
#endif
#ifdef COM_F_ONEEVERYN
    typedef struct
    {
        uint32 Period;
        uint32 Offset;
        uint8  Occurrence;
    }Com_OneEveryNType;
#endif


typedef uint16    Com_NoOfTxGrpSignalType;


typedef uint16    Com_NoOfRxGrpSignalType;


#ifdef COM_TX_SIGNALGROUP
typedef uint8    Com_TxIntGrpSignalIdType;
#endif

#ifdef COM_RX_SIGNALGROUP
typedef uint8    Com_RxIntGrpSignalIdType;
#endif


typedef uint16    Com_TxIntSignalIdType;
typedef uint16    Com_RxIntSignalIdType;

#ifdef COM_TX_SIGNALGROUP
 typedef uint8 Com_TxIntSignalGroupIdType;
#endif

#ifdef COM_RX_SIGNALGROUP
 typedef uint8 Com_RxIntSignalGroupIdType;
#endif


#if defined(COM_SigTriggeredOnChange) || defined(COM_SigGrpTriggeredOnChange)
typedef uint8   Com_OldValType;

typedef uint32 Com_OldValTrigOnChngType;
#endif

typedef uint8   Com_BitsizeType;
typedef uint16 Com_BitpositionType;
#if defined(COM_TxFilters) || defined (COM_RxFilters) 
typedef uint8   Com_FilterType;
#endif

typedef uint8 Com_RxGwQueueIndexType;


typedef uint16 Com_SigBuffIndexType;



typedef uint8 Com_RxGrpSigBuffIndexType;


typedef uint8 Com_TxGrpSigBuffIndexType;

#ifdef COM_TX_SIGNALGROUP_ARRAY


    /* Com_TxSigGrpArrayIndexType - is used as a typedef for SigGrpArray_Index member in
     * TxSignalGroup Configuration structure. Its typedef is generated based on the number of Tx-SignalGroup's
     * configured with the Array Access */
    typedef uint8 Com_TxSigGrpArrayIndexType;

# endif /* #ifdef COM_TX_SIGNALGROUP_ARRAY */

# ifdef COM_RX_SIGNALGROUP_ARRAY

    /* Com_RxSigGrpArrayIndexType - is used as a typedef for SigGrpArray_Index member in
     * RxSignalGroup Configuration structure. Its typedef is generated based on the number of Rx-SignalGroup's
     * configured with the Array Access */
    typedef uint8 Com_RxSigGrpArrayIndexType;

    /* Com_RxSigGrpBuffIndexType - is used as a typedef for RxSigGrpBuf_Index in RxSignalGroup Array 
     * configuration structure. Its typedef is generated based on the total number of bytes of all the RxSignalGroup's
     * configured with Array Access */
    typedef uint8 Com_RxSigGrpBuffIndexType;

# endif /* #ifdef COM_RX_SIGNALGROUP_ARRAY */


typedef uint32 Com_SigMaxType;

#ifdef COM_METADATA_SUPPORT

/* Maximum Length of the MetaData Supported by Com Module */
# define MAXIMUM_METADATA_LENGTH_IN_BYTES     ( 4U )

/**
 * @ingroup COM_TYPES_H
 * This typedef structure is data type for MetaData information\n
 *
 * typedef struct\n
 * {\n
 *   uint32 MetaDataLength;\n
 *   uint8  MetaDataDefaultValue[ MAXIMUM_METADATA_LENGTH_IN_BYTES ];\n
 * } Com_MetaDataInfo;
 */
typedef struct
{
    uint32  MetaDataLength;
    uint8   MetaDataDefaultValue[ MAXIMUM_METADATA_LENGTH_IN_BYTES ];
} Com_MetaDataInfo;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the current IPdu MetaData Information.\n
 *
 * typedef P2CONST( Com_MetaDataInfo, AUTOMATIC, COM_APPL_CONST ) Com_MetaDataInfoPtr;\n
 */
typedef P2CONST( Com_MetaDataInfo, AUTOMATIC, COM_APPL_CONST ) Com_MetaDataInfoPtr;

#endif /* #ifdef COM_METADATA_SUPPORT */

/*  END: Type Declaration  */

/* Filter type */
#if defined (COM_F_MASKEDNEWEQUALSX) || defined(COM_F_MASKEDNEWDIFFERSX)

/* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern  CONST(Com_MaskXType ,COM_CONST) Com_MaskX[];

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_F_MASKEDNEWDIFFERSOLD

/* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"
extern CONST(uint32 ,COM_CONST)  Com_Mask[];

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "Com_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of uint32 type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"
extern VAR(uint32,COM_VAR)  Com_F_OldVal[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of uint32 type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_32
#include "Com_MemMap.h"

#endif

#if defined(COM_SigTriggeredOnChange) || defined(COM_SigGrpTriggeredOnChange)

/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_OldValTrigOnChngType,COM_VAR) Com_OldValTrigOnChng[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if defined(COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)

/* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_POSMinMaxType ,COM_CONST) Com_POSMinMax[];

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#if defined(COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)

/* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_NEGMinMaxType ,COM_CONST) Com_NEGMinMax[];

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif

#ifdef COM_F_ONEEVERYN

/* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define COM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern CONST(Com_OneEveryNType,COM_CONST) Com_OneEveryN_Const[];

/* ------------------------------------------------------------------------ */
/* End section for constants */
#define COM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"


/* ------------------------------------------------------------------------ */
/* Begin section for RAM variables of struct/enum/pointer type */
#define COM_START_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"
extern VAR(Com_OneEveryNType,COM_VAR) Com_OneEveryN[];

/* ------------------------------------------------------------------------ */
/* End section for RAM variables of struct/enum/pointer type */
#define COM_STOP_SEC_VAR_CLEARED_POSTBUILD_UNSPECIFIED
#include "Com_MemMap.h"

#endif


#define Com_getfloat64InitValue(val) ((float64)0)

/* START: Miscellaneous Macros */

/* Maximum value for 32bits */
#define COM_MAX_U32_VALUE                       (uint32)(0xFFFFFFFFUL)

/* Maximum value for 64bits */
#define COM_MAX_U64_VALUE                       (uint64)(0xFFFFFFFFFFFFFFFFULL)

/* Mask used in the Code to identify the maximum unsigned long index of an array */
#define COM_MAX_U32_INDEX                       (COM_MAX_U32_VALUE)

/* Used for Sign Extention */
#define COM_SIGN_EXT_MASK                       (COM_MAX_U32_VALUE)

/* Maximum number of bits supported in Com */
#define COM_SIG_MAX_NO_OF_BITS                  (32u)

/* Maximum signal value */
#define COM_SIG_MAX_DATA                        (COM_MAX_U32_VALUE)

/* END: Miscellaneous Macros */

/* START : Tx IPDU notification functions */
#ifdef COM_TxIPduNotification
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Tx Notification callback function for IPDU : EMS2_ConntSts_Rx_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_TxNotify_EMS2_ConntSts_Rx_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Tx Notification callback function for IPDU : EMS_ConntSts_Rx_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_TxNotify_EMS_ConntSts_Rx_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_TxIPduNotification */
/* END : Tx IPDU notification functions */


/* START : Tx IPDU error notification functions */
/* END : Tx IPDU error notification functions */


/* START : Tx IPDU timeout  notification functions */
#ifdef COM_TxIPduTimeOutNotify
#endif /* #ifdef COM_TxIPduTimeOutNotify */
/* END : Tx IPDU timeout  notification functions */


/* START : Rx IPDU timeout  notification functions */
#ifdef COM_RxIPduTimeoutNotify
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Cell_18042701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Cell_18042701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_ConntSts_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_ConntSts_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Fault_18072701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Fault_18072701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_HV2_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_HV2_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_HV_Curr_18102701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_LongSOP_18032701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_LongSOP_18032701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_SystPara_18012701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_SystPara_18012701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_SystStat_18122701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_SystStat_18122701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS2_Temp_18152701h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS2_Temp_18152701h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Cell_18042701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Cell_18042701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_ConntSts_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_ConntSts_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Fault_18072701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Fault_18072701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV2_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV2_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV_18022701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV_18022701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_HV_Curr_18102701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_HV_Curr_18102701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_LongSOP_18032701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_LongSOP_18032701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_SystPara_18012701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_SystPara_18012701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_SystStat_18122701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_SystStat_18122701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : BMS_Temp_18152701h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_BMS_Temp_18152701h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_CCU2_SystStat_1801FAF2h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_CCU_SystStat_1801FAF2h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : HCU2_Syst_18220145h_Can_Network_CANNODE_3 */
FUNC(void,COM_CODE) Com_RxTONotify_HCU2_Syst_18220145h_Can_Network_CANNODE_3(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : HCU_Syst_18220145h_Can_Network_CANNODE_1 */
FUNC(void,COM_CODE) Com_RxTONotify_HCU_Syst_18220145h_Can_Network_CANNODE_1(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : TBOX_0x1803F102_Can_Network_CANNODE_5 */
FUNC(void,COM_CODE) Com_RxTONotify_TBOX_0x1803F102_Can_Network_CANNODE_5(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* Rx Timeout Notification callback function for IPDU : TBOX_0x1804F102_Can_Network_CANNODE_5 */
FUNC(void,COM_CODE) Com_RxTONotify_TBOX_0x1804F102_Can_Network_CANNODE_5(void);

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* #ifdef COM_RxIPduTimeoutNotify */

/* END : Rx IPDU timeout  notification functions */

#endif   /* COM_CFG_INTERNAL_H */

