

#ifndef COM_TYPES_H
#define COM_TYPES_H

/**
 * \defgroup COM_TYPES_H
 * This interface provides the public exported types of Com module.\n
 * To use this interface include the header <b>Com_Types.h</b>
 */

/**
 * @ingroup COM_TYPES_H
 * This structure is contains the Transmission Mode information \n
 *
 * typedef struct\n
 * {\n
 *   uint16              TimePeriodFact;     Time Period Factor\n
 *   uint16              TimeOffsetFact;     Time Offset Factor\n
 *   uint16              RepetitionPeriodFact; Repetition Period Factor\n
 *   uint8               NumOfRepetitions;   Number of repetitions\n
 *   uint8               Mode;               Transmission Mode\n
 * }Com_TransModeInfo;
 */
typedef struct
{
    uint16              TimePeriodFact;
    uint16              TimeOffsetFact;
    uint16              RepetitionPeriodFact;
    uint8               NumOfRepetitions;
    /* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
    uint8               Mode;               /*Transmission Mode*/
    boolean             MixedPhaseShift;    /* If Mode is MIXED , then this bit will indicate whether Phase Shift
                                               is enabled on event*/
#else
    /* FC_VariationPoint_END */
    uint8               Mode;
    /* FC_VariationPoint_START */
#endif /* #ifdef COM_MIXEDPHASESHIFT */
    /* FC_VariationPoint_END */
}Com_TransModeInfo;

/**
 * @ingroup COM_TYPES_H
 * This structure contains flags that are intialized before calling Com_SendIpdu internal API \n
 *
 * typedef struct \n
 * { \n
 *     unsigned int isEventTrig                   : 1; Set, If the call to Com_SendIpdu is from Event/Proc function \n
 *     unsigned int isTriggerIpduSend             : 1; Set, If call is from Com_TriggerIpduSend API \n
 *     unsigned int isTriggerIpduSendWithMetadata : 1; Set, If call is from Com_TriggerIpduSendWithMetadata API \n
 *     unsigned int isGwIpduSend                  : 1; Set, If call is from Com_MainFunctionRouteSignals API \n
 *     unsigned int isModeChangd                  : 1; Set, If Mode change has happened for the Ipdu \n
 *     unsigned int sigTransProp                  : 1; Set, If signal transfer property is triggered/pending \n
 *     unsigned int isTimeoutReq                  : 1; Set, If Timeout monitoring is required \n
 * } Com_SendIpduInfo; \n
 *
 * Note: If new bitfields are added here, make sure to add same number of initialize('0') bits in
 * COM_CLEAR_SENDIPDU_FLAGS macro too, which is used to intialize instance of 'Com_SendIpduInfo' structure
 */
typedef struct
{
    unsigned int isEventTrig                   : 1;
    unsigned int isTriggerIpduSend             : 1;
    unsigned int isTriggerIpduSendWithMetadata : 1;
    unsigned int isGwIpduSend                  : 1;
    unsigned int isModeChangd                  : 1;
    unsigned int sigTransProp                  : 1;
    unsigned int isTimeoutReq                  : 1;
} Com_SendIpduInfo;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the current TxMode State.\n
 *
 * typedef P2CONST( Com_TransModeInfo, AUTOMATIC, COM_APPL_CONST)  Com_TMConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST( Com_TransModeInfo, AUTOMATIC, COM_APPL_CONST)  Com_TMConstPtrType;

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Tx Signals \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_TxInvalid\n
 *      uint32                  DataInvalid_Val;    DataInvalid Value\n
 *   #endif\n
 *      uint32                  Init_Val;           Initial Value\n
 *
 *   #ifdef COM_TxSigUpdateBit\n
 *      Com_BitpositionType     Update_Bit_Pos;     Update Bit Position of the signal\n
 *   #endif\n
 *      Com_BitpositionType     Bit_Pos;            Bit Position of the signal\n
 *      Com_BitsizeType         BitSize;            BitSize of the signal if Signal Type is != uint8_N\n
 *                                                   Len of the Signal if Signal Type is == uint8_N\n
 *   #ifdef COM_TxFilters\n
 *      Com_FilterType          Filter_Index;       Index to the Filter Array depending on Filter Algorithm\n
 *   #endif\n
 *
 *   #ifdef COM_SigTriggeredOnChange\n
 *      Com_OldValType          OldValue_Index;     Index to old value of the signal\n
 *   #endif\n
 *
 *      Com_IpduIdType          IpduRef;            Ipdu Refernce Id\n
 *      uint8                   General;            Type/Endianess of the signal\n
 *      uint8                   txSignalFields;     Transfer Property/FilterAlgorithm of the signal\n
 *
 * }Com_Prv_xTxSigCfg_tst;
 */
typedef struct
{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification
        /*
         * Notification callback function for Signal. This function is called by Com_CallTxNotifyCallback().
         */
        P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif /* #ifdef COM_TxIPduNotification */

#ifdef COM_ERRORNOTIFICATION
    /* Error Notification part*/
    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif/* #if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */
#ifdef COM_TxInvalid
    uint32                  DataInvalid_Val;
#endif /* #if Com_TxInvalid */
    uint32                  Init_Val;

#ifdef COM_TxSigUpdateBit
    Com_BitpositionType     Update_Bit_Pos;
#endif

    Com_BitpositionType     Bit_Pos;

    Com_BitsizeType         BitSize;

#ifdef COM_TxFilters
    /* Filter */
    Com_FilterType          Filter_Index;
#endif

#ifdef COM_SigTriggeredOnChange
    Com_OldValType          OldValue_Index;
#endif

    Com_IpduIdType          IpduRef;
    /*
    typedef struct
    {
        uint8 Type:5;        DataType
        uint8 Endianess:1;   Endianess
        uint8 UpdBitConf:1;  IsUpdateBitConfigured
        uint8 Not_Used:1;
    } Com_GeneralType;
    */
    uint8         General;
    /*
    typedef struct
    {
        uint8 TransProp : 2;          Transfer Property of signal
        uint8 FilterAlgorithm : 4;    Filter Algorithm of signal
        uint8 DataInvalidType : 1;    DataInvalid Action
        uint8 TimeOutEnabled: 1;      Check If time out is configured
    } Com_TxSigPropType;
    */
    uint8          txSignalFields;

}Com_Prv_xTxSigCfg_tst;
/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx signal static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xTxSigCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_TxSigConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xTxSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigConstPtrType;


/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Rx Signals \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_RxSignalNotify\n
 *      P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);    Notification Signal part\n
 *   #endif\n
 *   #ifdef COM_RxSigInvalidNotify\n
 *      P2FUNC(void, COM_APPL_CODE, Sig_DataInvalid_Indication_Cbk)(void);    Invalid Notification\n
 *   #endif\n
 *   #ifdef COM_RxSigInvalid\n
 *      uint32                  DataInvalid_Val;    DataInvalid Value\n
 *   #endif\n
 *      uint32                  Init_Val;           Initial Value\n
 *
 *   #ifdef COM_RxSigUpdateBit\n
 *      Com_BitpositionType     Update_Bit_Pos;     Update Bit Position of the signal\n
 *   #endif\n
 *       Com_BitpositionType     Bit_Pos;            Bit Position of the signal\n
 *       Com_SigBuffIndexType    SigBuff_Index;      Index to signal buffer\n
 *       Com_BitsizeType         BitSize;            BitSize of the signal if Signal Type is != uint8_N\n
 *                                                  Len of the Signal if Signal Type is == uint8_N\n

 *
 *   #ifdef COM_RxFilters\n
 *      Com_FilterType          Filter_Index;       Index to the Filter Array depending on Filter Algorithm\n
 *   #endif\n
 *      Com_IpduIdType          IpduRef;            Ipdu Refernce Id\n
 *      uint8                   General;            Type/Endianess of the signal\n
 *      uint8                   rxSignalFields;     Transfer Property/DataTimeoutAction/DataInvalidAction/FilterAlgorithm of the signal\n
 *
 * }Com_Prv_xRxSigCfg_tst;
 */
typedef struct
{
#ifdef COM_RxSignalNotify
    /* Notification Signal part */
    P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif
#ifdef COM_RxSigInvalidNotify
    P2FUNC(void, COM_APPL_CODE, Sig_DataInvalid_Indication_Cbk)(void);
#endif /* #ifdef COM_RxSigInvalidNotify */
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif /* #if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */
#ifdef COM_RxSigInvalid
    uint32                  DataInvalid_Val;
#endif /* #ifdef COM_RxSigInvalid */
    uint32                  Init_Val;
#ifdef COM_RxSigUpdateBit
    Com_BitpositionType     Update_Bit_Pos;
#endif
    Com_BitpositionType     Bit_Pos;
    Com_SigBuffIndexType    SigBuff_Index;
    Com_BitsizeType         BitSize;
#ifdef COM_RxFilters
    /* Filter */
    Com_FilterType          Filter_Index;
#endif

    Com_IpduIdType          IpduRef;
    /*
    typedef struct
    {
        uint8 Type:5;        DataType
        uint8 Endianess:1;   Endianess
        uint8 UpdBitConf:1;  IsUpdateBitConfigured
        uint8 Not_Used:1;
    } Com_GeneralType;
    */
    uint8         General;
    /*
    typedef struct
    {
        uint8 DataInvalidType:2;    Data Invalid Action
        uint8 FilterAlgorithm:4;    Filter Algorithm
        uint8 DataTimeoutType:1;    DataTimeout Action
        uint8 IsGwSignal:1;         Is gateway signal
    }Com_RxSigPropType;
    */
    uint8         rxSignalFields;

}Com_Prv_xRxSigCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx signal static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xRxSigCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_RxSigConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xRxSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigConstPtrType;



/* Structure for Tx Signal Group  */
#ifdef COM_TX_SIGNALGROUP

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Tx SignalGroupArray static configuration \n
 *
 * typedef struct\n
 * {\n
 *      PduLengthType  FirstByteNo;  The start position of the uint8-array representation of the communication data
 *                                    shall be the byte offset of the group signal in this signal group with the
 *                                    smallest ComBitPosition.
 *      PduLengthType  Length;       The length of the uint8-array representation of the communication data shall
 *                                    be the number of bytes which all the ComGroupSignals in this ComSignalGroup
 *                                    occupy in the ComIPdu.
 * } Com_Prv_xTxSigGrpArrayCfg_tst;\n
 */
# ifdef COM_TX_SIGNALGROUP_ARRAY
typedef struct
{
    PduLengthType    FirstByteNo;
    PduLengthType    Length;

} Com_Prv_xTxSigGrpArrayCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx SignalGroup Array static configuration.\n
 */
typedef P2CONST(Com_Prv_xTxSigGrpArrayCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigGrpArrayConstPtrType;

# endif /* # ifdef COM_TX_SIGNALGROUP_ARRAY */

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Tx Signal Groups \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_TxSigGrpUpdateBit\n
 *      Com_BitpositionType     Update_Bit_Pos;         Update Bit Position of the signal group\n
 *   #endif\n
 *      Com_IpduIdType          IpduRef;                Ipdu Refernce Id\n
 *      Com_TxIntGrpSignalIdType    FirstGrpSig_Index;  Index to First Group Signal in the Signal group\n
 *      Com_NoOfTxGrpSignalType     No_Of_GrpSig;           No Of Group Signals present in the Signal group\n
 *      uint8                   txSignalGrpFields;      Properties of Tx Signal Group\n
 * }Com_Prv_xTxSigGrpCfg_tst;
 *
 */
typedef struct
{
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_TxIPduNotification
    /*
     * Notification callback function for SignalGroup. This function is called by Com_CallTxNotifyCallback().
     */
    P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif /* #ifdef COM_TxIPduNotification */

#ifdef COM_ERRORNOTIFICATION
    /* Error Notification part*/
    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif/* #if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */

#ifdef COM_TxSigGrpUpdateBit
    Com_BitpositionType         Update_Bit_Pos;
#endif
    Com_IpduIdType              IpduRef;
    Com_TxIntGrpSignalIdType    FirstGrpSig_Index;
    Com_NoOfTxGrpSignalType     No_Of_GrpSig;

#ifdef COM_TX_SIGNALGROUP_ARRAY
    Com_TxSigGrpArrayIndexType  SigGrpArray_Index;
#endif
    /* FC_VariationPoint_START */
    /*
        typedef struct
        {
            uint8 TransProp:2;          Transfer Property of a SignalGroup
            uint8 TimeOutEnabled: 1;    COM_TRUE : If time out is confifured
                                        COM_FALSE: If time out is not confifured for the signal group
            uint8 FilterEvalReq:1;      COM_TRUE : If there exist group signal's with filter configured
                                        COM_FALSE: If there don't exist group signal's with filter configured
            uint8 UpdBitConf:1          COM_TRUE - Configured, COM_FALSE - Not configured
            uint8 ArrayAccess:1;        COM_TRUE - Array Access Enabled, COM_FALSE - Array Access Disabled
            uint8 Not_Used:2;
        } Com_TxSigGrpPropType;
     */
    /* FC_VariationPoint_END */
    uint8                       txSignalGrpFields;

}Com_Prv_xTxSigGrpCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx signal group static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xTxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_TxSigGrpConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xTxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxSigGrpConstPtrType;

#endif



#ifdef COM_RX_SIGNALGROUP

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Rx SignalGroupArray static configuration \n
 *
 * typedef struct\n
 * {\n
 *      PduLengthType             FirstByteNo;       The start position of the uint8-array representation of the
 *                                                    communication data shall be the byte offset of the group signal
 *                                                    in this signal group with the smallest ComBitPosition.
 *      Com_RxSigGrpBuffIndexType RxSigGrpBuf_Index; Index to RxSignalGroup buffer for each of the SignalGroup enabled
 *                                                    with ComSignalGroupArrayAccess
 * } Com_Prv_xRxSigGrpArrayCfg_tst;\n
 */
# ifdef COM_RX_SIGNALGROUP_ARRAY
typedef struct
{
    PduLengthType               FirstByteNo;
    Com_RxSigGrpBuffIndexType   RxSigGrpBuf_Index;

} Com_Prv_xRxSigGrpArrayCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx SignalGroup Array static configuration.\n
 */
typedef P2CONST(Com_Prv_xRxSigGrpArrayCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigGrpArrayConstPtrType;

# endif /* # ifdef COM_RX_SIGNALGROUP_ARRAY */

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Rx Signal Groups \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_RxSignalGrpNotify\n
 *      P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);    Notification Signal part\n
 *   #endif\n
 *   #ifdef COM_RxSigGrpInvalidNotify\n
 *      P2FUNC(void, COM_APPL_CODE, DataInvalid_Indication_Cbk)(void);    Invalid Notification\n
 *   #endif\n
 *    #ifdef COM_RxSigGrpUpdateBit\n
 *      Com_BitpositionType         Update_Bit_Pos;         Update Bit Position of the signal group\n
 *   #endif\n
 *      Com_IpduIdType              IpduRef;                Ipdu Refernce Id\n
 *      Com_RxIntGrpSignalIdType    FirstGrpSig_Index;      Index to First Group Signal in the Signal group\n
 *      Com_NoOfRxGrpSignalType     No_Of_GrpSig;           No Of Group Signals present in the Signal group\n
 *      uint8                       rxSignalGrpFields;      Properties of Signal Group\n
 * }Com_Prv_xRxSigGrpCfg_tst;
 */
typedef struct
{
#ifdef COM_RxSignalGrpNotify
    /* Notification Signal part */
     P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif
#ifdef COM_RxSigGrpInvalidNotify
    P2FUNC(void, COM_APPL_CODE, DataInvalid_Indication_Cbk)(void);
#endif /* #ifdef COM_RxSigGrpInvalidNotify */
#if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE)
#ifdef COM_RxIPduTimeoutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#endif /* #if (COM_CONFIGURATION_VARIANT != COM_VARIANT_PRE_COMPILE) */
#ifdef COM_RxSigGrpUpdateBit
    Com_BitpositionType         Update_Bit_Pos;
#endif
    Com_IpduIdType              IpduRef;

    Com_RxIntGrpSignalIdType    FirstGrpSig_Index;

    Com_NoOfRxGrpSignalType     No_Of_GrpSig;
#ifdef COM_SIGNALGROUPGATEWAY
    uint16                      numOfGwSrcGrpSignals;
#endif /* COM_SIGNALGROUPGATEWAY */
    /* Last byte in the IPdu to which the signal group spans till.
     * Now lasyByte is also used in Com_ReceiveSignalGroupArray() to calculate SignalGroup Array Length.
     */
    PduLengthType               lastByte_u8;

#ifdef COM_RX_SIGNALGROUP_ARRAY
    Com_RxSigGrpArrayIndexType  SigGrpArray_Index;
#endif

/* FC_VariationPoint_START */
    /*
    typedef struct
    {
        uint8 DataInvalidType:2; DataInvalid Action
        uint8 DataTimeoutType:1; DataTimeout Action
        uint8 IsGwSignal:1;      SignalGroup Gateway
        uint8 UpdBitConf:1;      Is UpdateBit set
        uint8 ArrayAccess:1;     Is SignalGroup Array Access enabled
        uint8 FilterEvalReq:1;   Is Filter processing required at any of its GroupSignal
        uint8 Not_Used:1;
    } Com_RxSigGrpPropertyType;
    */
/* FC_VariationPoint_END */
    uint8                       rxSignalGrpFields;

}Com_Prv_xRxSigGrpCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx signal group static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xRxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_RxSigGrpConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xRxSigGrpCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxSigGrpConstPtrType;
#endif


#ifdef COM_TX_SIGNALGROUP

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Tx Group Signals \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_TxGrpSigInvalid\n
 *      uint32                  DataInvalid_Val;    DataInvalid Value\n
 *   #endif\n
 *      uint32                  Init_Val;           Initial Value\n
 *      Com_BitpositionType     Bit_Pos;            Bit Position of the signal\n
 *      Com_TxGrpSigBuffIndexType   TxGrpSigBuff_Index;   Group Signal Buffer Index\n
 *      Com_TxIntSignalGroupIdType  SigGrpRef;      Signal Group Id
 *      Com_BitsizeType         BitSize;            BitSize of the signal\n
 *
 *   #ifdef COM_TxFilters\n
 *      Com_FilterType          Filter_Index;       Index to the Filter Array depending on Filter Algorithm\n
 *      uint8                   Filter_Algo;        Filter Algorithm of the Group Signal
 *   #endif\n
 *
 *   #ifdef COM_SigGrpTriggeredOnChange\n
 *      Com_OldValType          OldValue_Index;     Index to old value of the signal\n
 *   #endif\n
 *
 *      uint8                   txGrpSigFields;     Type/Endianess/FilterAlgorithm of the signal\n
 *
 * }Com_Prv_xTxGrpSigCfg_tst;
 */

typedef struct
{

#ifdef COM_TxGrpSigInvalid
    uint32                      DataInvalid_Val;
#endif
    uint32                      Init_Val;
    Com_BitpositionType         Bit_Pos;
    Com_TxGrpSigBuffIndexType   TxGrpSigBuff_Index;

    Com_TxIntSignalGroupIdType  SigGrpRef;

    Com_BitsizeType             BitSize;
#ifdef COM_TxFilters
    /* Filter */
    Com_FilterType          Filter_Index;
    uint8                   Filter_Algo;
#endif

#ifdef COM_SigGrpTriggeredOnChange
    Com_OldValType          OldValue_Index;
#endif
    /*
    typedef struct
    {
        uint8 Type:5;           DataType
        uint8 Endianess:1;      Endianess of Grp signal
        uint8 TransProp:1;      set, if the group signal contributes to the evaluation of transfer property signal group
        uint8 GrpSigInvalid:1;  Indicates if the group signal has configured invalid value

    } Com_TxGrpSigPropertyType;
    */
    uint8    txGrpSigFields;

}Com_Prv_xTxGrpSigCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx group signal static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xTxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_TxGrpSigConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xTxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxGrpSigConstPtrType;
#endif

#ifdef COM_RX_SIGNALGROUP
/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Rx Group Signals \n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_RxSigGrpInvalid\n
 *      uint32                  DataInvalid_Val;    DataInvalid Value\n
 *   #endif\n
 *      uint32                  Init_Val;           Initial Value\n
 *      Com_BitpositionType     Bit_Pos;            Bit Position of the signal\n
 *      Com_RxGrpSigBuffIndexType   RxGrpSigBuff_Index;   Group Signal Buffer Index\n
 *      Com_RxIntSignalGroupIdType  SigGrpRef;      Signal Group Id
 *      Com_BitsizeType         BitSize;            BitSize of the signal\n
 *   #ifdef COM_RxFilters
 *      Com_FilterType          Filter_Index;       Index to the filter properties\n
 *      uint8                   Filter_Algo;        Filter algorithm as per the configuration
 *   #endif

 *      uint8                   rxGrpSigFields;     Type/Endianess of the group signal\n
 *
 * }Com_Prv_xRxGrpSigCfg_tst;
 */
typedef struct
{
#ifdef COM_RxSigGrpInvalid
    uint32                      DataInvalid_Val;
#endif
    uint32                      Init_Val;
    Com_BitpositionType         Bit_Pos;
    Com_RxGrpSigBuffIndexType   RxGrpSigBuff_Index;

    Com_RxIntSignalGroupIdType  SigGrpRef;

    Com_BitsizeType             BitSize;
#ifdef COM_RxFilters
    /* Filter */
    Com_FilterType              Filter_Index;
    uint8                       Filter_Algo;
#endif
    /*
    typedef struct
    {
        uint8 Type:5;               DataType
        uint8 Endianess:1;          Endianess of grp signal
        uint8 GrpSigInvalid:1;      Has group signal configured invalid value
        uint8 Not_Used:1;
    } Com_RxGrpSigPropertyType;
    */
    uint8     rxGrpSigFields;
}Com_Prv_xRxGrpSigCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx group signal static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xRxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_RxGrpSigConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST (Com_Prv_xRxGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxGrpSigConstPtrType;
#endif

/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Tx IPDU \n
 *
 * typedef struct\n
 * {\n
 *      P2VAR(uint8, TYPEDEF, COM_APPL_DATA) BuffPtr;  Pointer to the Ipdu Buffer\n
 *      P2CONST(Com_TransModeInfo, TYPEDEF,COM_APPL_CONST) Com_TMConstPtr;  Pointer to Transfer mode information\n
 *   #ifdef COM_TxIPduCallOuts\n
 *      P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2VAR(uint8, TYPEDEF, COM_APPL_DATA)); Ipdu Callout Function\n
 *   #endif\n
 *   #ifdef COM_TxIPduNotification\n
 *      P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void); Notification callback function for IPDU\n
 *   #endif\n
 *   #ifdef COM_ERRORNOTIFICATION \n
 *      P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void); Error Notification part\n
 *   #endif\n
 *   #ifdef COM_TxIPduTimeOutNotify\n
 *      P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void); Timeout Notification part\n
 *   #endif\n
 *   #ifdef COM_TXDOUBLEBUFFER\n
 *      P2VAR(uint8, TYPEDEF, COM_APPL_DATA) LocalBuffPtr;      Pointer to the Local Ipdu Buffer\n
 *   #endif\n
 *   #ifdef COM_METADATA_SUPPORT\n
 *    Com_MetaDataInfoPtr         MetaDataPtr;\n
 *   #endif\n
 *      uint16                  Size;               Size in Bits\n
 *   #ifdef COM_TxIPduTimeOut\n
 *      uint16                  Timeout_Fact;       Support Tx IPDU Timeout \n
 *   #endif\n
 *      uint16                  Min_Delay_Time_Fact;        MinDelay Time factor\n
 *      uint16                  No_Of_Sig_Ref;      No Of Signals present in the IPDU\n
 *   #ifdef COM_TX_SIGNALGROUP\n
 *      uint16                  No_Of_SigGrp_Ref;   No of Signal Groups present in the IPDU\n
 *   #endif\n
 *       PduIdType               PdurId;             Lower Layer ID\n
 *       Com_TxIntSignalIdType   TxSigId_Index;        Index to First Signal within this Ipdu\n
 *   #ifdef COM_TX_SIGNALGROUP\n
 *      Com_TxIntSignalGroupIdType  FirstTxSigGrp_Index;   Index to First Signal Group within this Ipdu\n
 *   #endif\n
 *      uint8                   txIPduFields;       Transmission Type\n
 *      uint8                   PaddingByte;        Padding Byte\n
 *
 * }Com_Prv_xTxIpduInfoCfg_tst;
 */
typedef struct
{
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) BuffPtr;

    P2CONST(Com_TransModeInfo, TYPEDEF,COM_APPL_CONST) Com_TMConstPtr;
#ifdef COM_TxIPduCallOuts
    /*Ipdu Callout Function*/
    P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2VAR(uint8, TYPEDEF, COM_APPL_DATA));
#endif
#ifdef COM_TxIPduNotification
        /*
         * Notification callback function for IPDU. This function is generated through code generator.
         * Individual signal and signal group notifications functions are called from within this function.
         */
        P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void);
#endif /* #ifdef COM_TxIPduNotification */

#ifdef COM_ERRORNOTIFICATION
    /* Error Notification part*/
    P2FUNC(void, COM_APPL_CODE, NotificationError_Cbk)(void);
#endif

#ifdef COM_TxIPduTimeOutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif


#ifdef COM_TXDOUBLEBUFFER
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) LocalBuffPtr;
#endif

#ifdef COM_METADATA_SUPPORT
    Com_MetaDataInfoPtr         MetaDataPtr;
#endif

    PduLengthType               Size;

#ifdef COM_TxIPduTimeOut
    uint16                      Timeout_Fact;
#endif /* #ifdef COM_TxIPduTimeOut */

    uint16                      Min_Delay_Time_Fact;

    uint16                      No_Of_Sig_Ref;
#ifdef COM_TX_SIGNALGROUP
    uint16                      No_Of_SigGrp_Ref;
#endif
    PduIdType                   PdurId;
    Com_TxIntSignalIdType       TxSigId_Index;
#ifdef COM_TX_SIGNALGROUP
    Com_TxIntSignalGroupIdType  FirstTxSigGrp_Index;
#endif
/*
typedef struct
{
    uint16 Signal_Processing:1;         Signal Processing of each signal within the IPDU(DEFERRED(1)/IMMEDIATE(0))
    uint16 TMSCalclation:2;             Transmission mode status
                                            COM_MODE_VALID      (0)  If both the modes are configured
                                            COM_TRUEMODE_VALID  (1)  If TRUE mode is configured
                                            COM_FALSEMODE_VALID (2)  If FALSE mode is configured
                                            COM_MODE_INVALID    (3)  If both the modes are not configured
    uint16 NoneModeTimeOut:1;           Set, if Deadline monitoring for the IPdu for TX mode none
    uint16 ClearUpdBit:2;               Status of where to clear update bit
                                            TRANSMIT        (1)
                                            TRIGGERTRANSMIT (2)
                                            CONFIRMATION    (3)
    uint16 FilterEvalReq:1;             Set, if Filter evaluation required
    uint16 IsDynPdu:1;                  Set, if the Ipdu is of Dynamic type
    uint16 IsGwDestPdu:1;               Set, if the Ipdu has Gw destination signal
    uint16 IsCalloutFrmTrigTrans:1;     Set, if the callout is from Com_TriggerTransmit
    uint16 IsLargeDataPdu:1;            Set, if the IPdu is of Large data TP IPdu
    uint16 isCancelTransmitSupported:1; Set, if the IPdu supports CancelTransmit
    uint16 IsMetaDataSupported:1;       Set, if MetaData is supported for the IPdu
    uint16 Not_Used:3;                  Unused bits
}Com_TxIpduFlagType;
*/
    uint16                      txIPduFields;
    uint8                       PaddingByte;

}Com_Prv_xTxIpduInfoCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx IPDU static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xTxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_TxIpduConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST(Com_Prv_xTxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_TxIpduConstPtrType;



/* Time out information structure for signals/signal groups with update-bit */
#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
/**
 * @ingroup COM_TYPES_H
 * This structure contains the Time out information for signals\n
 *
 * typedef struct\n
 * {\n
 *   #ifdef COM_RxUpdateTimeoutNotify\n
 *      P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void); Notification function for timeout\n
 *   #endif\n
 *      uint16          First_Timeout;    First timeout value\n
 *      uint16          Timeout;          Ttimeout value\n
 *      uint16          SigId;            Signal Id\n
 * }Com_SignalTimeoutInfo;
 */
typedef struct
{
    /* Error Notification part*/
#ifdef COM_RxUpdateTimeoutNotify
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif /* #ifdef COM_RxUpdateTimeoutNotify */
    uint16          First_Timeout;
    uint16          Timeout;
    uint16          SigId;
}Com_SignalTimeoutInfo;

/**
 * @ingroup COM_TYPES_H
 * This structure contains the Time out information for signals/signal groups with update-bit\n
 *
 * typedef struct\n
 * {\n
 *      P2CONST(Com_SignalTimeoutInfo, TYPEDEF, COM_APPL_CONST) TimeoutInfo_Ref;    Reference to timeout information structure for all signals/signal groups, with update-bit\n
 *      P2VAR(uint16,TYPEDEF, COM_APPL_DATA) TimeoutTicks_p;    Pointer to timer array\n
 *      uint8           numWithUpdateBit;       Number of signals/signal groups with update-bit, with enabled deadline monitoring\n
 * }Com_UpdatebitTimeoutInfo;
 */
typedef struct
{
    /* Reference to timeout information structure for all signals/signal groups, with update-bit */
    P2CONST(Com_SignalTimeoutInfo, TYPEDEF, COM_APPL_CONST) TimeoutInfo_Ref;
    P2VAR(uint16,TYPEDEF, COM_APPL_DATA) TimeoutTicks_p;
    uint8           numWithUpdateBit;
}Com_UpdatebitTimeoutInfo;

#endif /* #if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)) */




/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for Rx IPDU \n
 *
 * typedef struct\n
 * {\n
 *      P2VAR(uint8, TYPEDEF, COM_APPL_DATA) BuffPtr;  Pointer to the Ipdu Buffer\n
 *   #ifdef  COM_RxSigUpdateTimeout\n
 *      P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST) SignalTimeout_Ref;   Pointer to timeout information structure for signals with update-bits, within the IPdu\n
 *   #endif\n
 *   #ifdef  COM_RxSigGrpUpdateTimeout\n
 *      P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST) SignalGrpTimeout_Ref;    Pointer to timeout information structure for signal groups with update-bits, within the IPdu\n
 *   #endif
 *   #ifdef COM_RxIPduCallOuts\n
 *      P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2CONST(uint8, TYPEDEF, COM_APPL_CONST)); Ipdu Callout Function\n
 *   #endif\n
 *   #ifdef COM_RxIPduTimeoutNotify\n
 *      P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void); Timeout Notification part\n
 *   #endif\n
 *   #ifdef COM_RxIPduNotification\n
 *      P2FUNC(void, COM_APPL_CODE, Notification_Cbk)(void); Notification callback function for IPDU\n
 *   #endif\n
 *      uint16                  Size;               Size in Bits\n
 *   #ifdef COM_RxIPduTimeout\n
 *      uint16                  FirstTimeout_Factor; First time out value after IPDU group start\n
 *      uint16                  Timeout_Fact;       Support Rx IPDU Timeout \n
 *   #endif\n
 *      uint16                  No_Of_Sig_Ref;      No Of Signals present in the IPDU\n
 *   #ifdef COM_RX_SIGNALGROUP\n
 *      uint16                  No_Of_SigGrp_Ref;   No of Signal Groups present in the IPDU\n
 *   #endif\n
 *      Com_RxIntSignalIdType   RxSigId_Index;        Index to First Signal within this Ipdu\n
 *    #ifdef COM_RX_SIGNALGROUP\n
 *      Com_RxIntSignalGroupIdType  FirstRxSigGrp_Index;        Index to First Signal Group within this Ipdu\n
 *    #endif\n
 *      uint8        rxIPduFields;   Transmission Type\n
 * }Com_Prv_xRxIpduInfoCfg_tst;
 */
typedef struct
{
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) BuffPtr;
#ifdef  COM_RxSigUpdateTimeout
    P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST) SignalTimeout_Ref;
#endif /* #ifdef  COM_RxSigUpdateTimeout */
#ifdef  COM_RxSigGrpUpdateTimeout
    P2CONST(Com_UpdatebitTimeoutInfo, TYPEDEF, COM_APPL_CONST) SignalGrpTimeout_Ref;
#endif /* #ifdef  COM_RxSigGrpUpdateTimeout */


#ifdef COM_RxIPduCallOuts
    P2FUNC(boolean, COM_APPL_CODE, CallOut)(PduIdType, P2CONST(uint8, TYPEDEF, COM_APPL_CONST));
#endif

#ifdef COM_RxIPduTimeoutNotify
    /* Timeout Notification part*/
    P2FUNC(void, COM_APPL_CODE, TimeOutNotification_Cbk)(void);
#endif
#ifdef COM_RxIPduNotification
        /*
         * Notification callback function for IPDU. This function is generated through code generator.
         * .
         */
        P2FUNC(void, COM_APPL_CODE, RxNotification_Cbk)(void);
#endif /* #ifdef COM_RxIPduNotification */

    PduLengthType                  Size;
#ifdef COM_RxIPduTimeout
    uint16                  FirstTimeout_Factor;
    uint16                  Timeout_Fact;
#endif /* #ifdef COM_RxIPduTimeout */
    uint16                  No_Of_Sig_Ref;      /*No Of Signals present in the IPDU*/
#ifdef COM_RX_SIGNALGROUP
    uint16                  No_Of_SigGrp_Ref;   /*No of Signal Groups present in the IPDU*/
#endif
    Com_RxIntSignalIdType   RxSigId_Index;        /*Index to First Signal within this Ipdu*/
#ifdef COM_RX_SIGNALGROUP
    Com_RxIntSignalGroupIdType  FirstRxSigGrp_Index;        /*Index to First Signal Group within this Ipdu*/
#endif
#ifdef COM_SIGNALGATEWAY
    uint16     numOfGwSrcSignals;
#endif /* #ifdef COM_SIGNALGATEWAY  */
#ifdef COM_SIGNALGROUPGATEWAY
    uint16   numOfGwSrcSignalGrps;
#endif /* #ifdef COM_SIGNALGROUPGATEWAY*/

    /*
    typedef struct
    {
        uint8 Signal_Processing:1;  Signal Processing of each signal within the IPDU
                                     COM_TRUE  : It is required to copy the data from the lower layer buffer to
                                                 IPdu buffer, for later processing
                                     COM_FALSE : Not required
        uint8 Notify_Cbk:1;         Set, If any of the Signal within the Ipdu has Notification cbk configured
        uint8 IsRxGwIPdu:1;         Set, if RxIpdu has any data to be Gatewayed
        uint8 Not_Used:5;           Not used Bit field

    } Com_RxIpduFlagType;
    */
    uint8        rxIPduFields;   /*Transmission Type*/

}Com_Prv_xRxIpduInfoCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx IPDU static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xRxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_RxIpduConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST(Com_Prv_xRxIpduInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_RxIpduConstPtrType;



/**
 * @ingroup COM_TYPES_H
 * This structure contains the information for IPDU Group \n
 *
 * typedef struct\n
 * {\n
 *      uint16      FirstIpdu_Index;     First ipdu index in the group \n
 *      uint16      NoOfPdus;            No. of ipdus in a particular group\n
 * }Com_Prv_xIpduGrpInfoCfg_tst;
 */
typedef struct
{
    uint16 FirstIpdu_Index;
    uint16 NoOfPdus;

}Com_Prv_xIpduGrpInfoCfg_tst;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the IPDU Group static configuration.\n
 *
 * typedef P2CONST( Com_Prv_xIpduGrpInfoCfg_tst, AUTOMATIC, COM_APPL_CONST)  Com_IPduGrpConstPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2CONST(Com_Prv_xIpduGrpInfoCfg_tst, AUTOMATIC, COM_APPL_CONST) Com_IPduGrpConstPtrType;

/**
 * @ingroup COM_TYPES_H
 * This structure contains the Tx signal flags \n
 *
 * typedef struct\n
 * {\n
 *      uint8   txSigRAMFields; \n
 * }Com_TxSignalFlagType;
 */
typedef struct
{
    uint8 txSigRAMFields;

}Com_TxSignalFlagType;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx Signal dynamic configuration.\n
 *
 * typedef P2CONST( Com_TxSignalFlagType, AUTOMATIC, COM_APPL_CONST)  Com_TxSigRamPtrType;\n
 */
typedef P2VAR( Com_TxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxSigRamPtrType;

#ifdef COM_TX_SIGNALGROUP
/**
 * @ingroup COM_TYPES_H
 * This structure contains the Tx group signal flags \n
 *
 * typedef struct\n
 * {\n
 *      uint8   txGrpSigRAMFields; \n
 * }Com_TxGrpSignalFlagType;
 */
typedef struct
{
    uint8 txGrpSigRAMFields;

}Com_TxGrpSignalFlagType;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx Group Signal dynamic configuration.\n
 *
 * typedef P2CONST( Com_TxGrpSignalFlagType, AUTOMATIC, COM_APPL_CONST)  Com_TxGrpSigRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_TxGrpSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxGrpSigRamPtrType;

#endif


/**
 * @ingroup COM_TYPES_H
 * This structure contains the Rx signal flags \n
 *
 * typedef struct\n
 * {\n
 *      uint8   rxSigRAMFields;     Flag used to check if there was any Data Timeout for the signal\n
 * }Com_RxSignalFlagType;
 */
typedef struct
{
    uint8 rxSigRAMFields;

}Com_RxSignalFlagType;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx Signal dynamic configuration.\n
 *
 * typedef P2CONST( Com_RxSignalFlagType, AUTOMATIC, COM_APPL_CONST)  Com_RxSigRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_RxSignalFlagType, AUTOMATIC, COM_APPL_DATA)  Com_RxSigRamPtrType;




#ifdef COM_RX_SIGNALGROUP
/**
 * @ingroup COM_TYPES_H
 * This structure contains the Rx signal group flags \n
 *
 * typedef struct\n
 * {\n
 *      uint8   rxSigGrpRAMFields; \n
 * }Com_RxSignalGrpFlagType;
 */
typedef struct
{
    uint8 rxSigGrpRAMFields;

}Com_RxSignalGrpFlagType;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx Signal Group dynamic configuration.\n
 *
 * typedef P2CONST( Com_RxSignalGrpFlagType, AUTOMATIC, COM_APPL_CONST)  Com_RxSigGrpRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_RxSignalGrpFlagType, AUTOMATIC, COM_APPL_DATA)  Com_RxSigGrpRamPtrType;
#endif


#ifdef COM_TX_SIGNALGROUP
#if defined (COM_SigGrpTriggeredOnChange) || defined (COM_SIGNALGROUPGATEWAY)
/**
 * @ingroup COM_TYPES_H
 * This structure contains the Tx signal group flags \n
 *
 * typedef struct\n
 * {\n
 *      uint8   txSigGrpRAMFields; \n
 * }Com_TxSignalGrpFlagType;
 */
typedef struct
{
    uint8 txSigGrpRAMFields;

}Com_TxSignalGrpFlagType;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx Signal Group dynamic configuration.\n
 *
 * typedef P2CONST( Com_TxSignalGrpFlagType, AUTOMATIC, COM_APPL_CONST)  Com_TxSigGrpRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_TxSignalGrpFlagType, AUTOMATIC, COM_APPL_DATA)  Com_TxSigGrpRamPtrType;
#endif /* #if defined (COM_SigGrpTriggeredOnChange) || defined (COM_SIGNALGROUPGATEWAY) */
#endif

/**
 * @ingroup COM_TYPES_H
 * This is the Tx IPDU RAM structure \n
 *
 * typedef struct\n
 * {\n
 *      Com_TMConstPtrType  CurrentTxModePtr;       Current Tx Mode state of the Tx IPDU\n
 *   #ifdef COM_TP_IPDUTYPE \n
 *      PduLengthType       TxTPIPduLength; \n      Current Transmission TP Length\n
*    #endif  #ifdef COM_TP_IPDUTYPE \n
 *      uint16              Com_MinDelayTick;       Minimum Delay Tick for the Tx IPDU\n
 *      uint16              Com_TMSTrueCounter_u8;  Variable for keeping track of how many signals have TMS state as TRUE\n
 *      uint16              Com_Tick_Tx;            Tick for the Tx IPDU\n
 *      uint16              Com_n_Tick_Tx;          For Mixed Mode this Tick is used if N>0\n
 *   #ifdef COM_TxIPduTimeOut\n
 *      uint16              Com_TickTxTimeout;      Tick for the Tx Confirmation\n
 *   #endif\n
 *      uint16              Com_TxFlags;            Variable to hold the Tx flags\n
 *      uint8               Com_n;                  For Number of Repetition, this has to be updated only if
 *                                                  there is a request from RTE (i.e ComSendSignal, Com_SendSignalGroup)\n
 *      uint8               Com_TransMode;          Variable which holds the LatestTransmissionMode and TxModeState of each signal\n
 * }Com_TxIpduRamData;
 */
typedef struct
{
    Com_TMConstPtrType CurrentTxModePtr;
#ifdef COM_TP_IPDUTYPE
    PduLengthType       TxTPIPduLength;
#endif /* #ifdef COM_TP_IPDUTYPE */
    uint16              Com_MinDelayTick;
    uint16              Com_Tick_Tx;
    uint16              Com_TMSTrueCounter_u8;
    uint16              Com_n_Tick_Tx;
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    uint16                 Com_DynLength;
#endif
#ifdef COM_TxIPduTimeOut
    uint16              Com_TickTxTimeout;
#endif /* #ifdef COM_TxIPduTimeOut */
    /* FC_VariationPoint_START */
    /*
    typedef struct
    {
        uint16 PduStatus:1;            Flag gives the old status of the Pdu Activation status
        uint16 TxConfirFlag:1;         Used to check whether Confirmation for the Tx frame has been received or not
        uint16 TickTxTimeout_Flag:1;   Flag which tells whether Timer was started/Stopped
        uint16 MDT_Flag:1;             Flag which tells whether Minimum delay time has not completed
        uint16 EvenTriggeredTx:1;      Flag which stores the information whether IPdu is transmitted in event triggered
                                               call from Com_SendSignal/Com_SendSignalGroup/Com_SendDynSignal/Com_TriggerIpduSend
        uint16 IsGwTriggerred:1;       Flag which stores if there was a Trigger on the Gw Pdu
        uint16 IsTimeOutEnabled:1;     Flag which stores information if the Timeout timer has to be started for Ipdu.
        uint16 GwPduTransmitted:1;     Flag which stores information if the Gw Pdu is event triggered from Com_MainfunctionRouteSignals.
        uint16 isLargeDataPduFlag:1;   Flag which stores information if the Tp Pdu for large data pdu handling.
        uint16 GwTMSChanged:1;         Flag is set, if the Gw-IPDU's Tranmission Mode has changed after its last
                                               transmission from Com
        uint16 Not_Used:6;             Un-used bits
    } Com_TxFlagsType;
    */
    /* FC_VariationPoint_END */
    uint16              Com_TxFlags;
    uint8               Com_n;
    /* FC_VariationPoint_START */
    /*
    typedef struct
    {
        uint8 LatestTransMode:2;    Stores the Latest Transmission Mode of the IPDU
        uint8 TxModeState:2;        Stores the Transmission mode State i.e TRUE/FALSE
        uint8 MixedPhaseShift:1;    MixedPhaseShift status.If this is SET, then current mode is MixedPhaseShift
        uint8 Not_Used:3;           Not used Bit field
    }Com_TransModeType;
    */
    /* FC_VariationPoint_END */
    uint8                Com_TransMode;

}Com_TxIpduRamData;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Tx IPDU dynamic configuration.\n
 *
 * typedef P2CONST( Com_TxIpduRamData, AUTOMATIC, COM_APPL_CONST)  Com_TxIpduRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_TxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_TxIpduRamPtrType;

/*END:  RAM structure for TX IPDU */

/**
 * @ingroup COM_TYPES_H
 * This is the Rx IPDU RAM structure \n
 *
 * typedef struct\n
 * {\n
 *      PduLengthType   RxIPduLength;
 *  #ifdef COM_TP_IPDUTYPE \n
 *      PduLengthType   RxTPIPduLength; \n  Current Reception Tp Length\n
 *  #endif #ifdef COM_TP_IPDUTYPE\n
 *   #ifdef COM_RxIPduTimeout\n
 *      uint16              RxTicks_u16;      Counter for timeout\n
 *   #endif\n
 *      uint8               RxFlags;            Variable to hold the Tx flags
 * }Com_RxIpduRamData;
 */
typedef struct
{
    PduLengthType   RxIPduLength;
#ifdef COM_TP_IPDUTYPE
    PduLengthType   RxTPIPduLength;
#endif /* #ifdef COM_TP_IPDUTYPE */
#ifdef COM_RxIPduTimeout
    uint16          RxTicks_u16;
#endif /* #ifdef COM_RxIPduTimeout */

    /* FC_VariationPoint_START */
    /*
     typedef struct
    {
        uint8 PduStatus:1;              Flag gives the old status of the Pdu Activation status
        uint8 Pdu_DMStatus:1;           Flag gives the old status of the Pdu Activation status
        uint8 RxIndicationFlag:1;       Flag used to Indicate that Ipdu was received
        uint8 IsRxGwIpduProcessed:1;    Flag used to Indicate if the Gw Ipdu is processed after its reception
        uint8 rxTPIPduFlag:1;           Flag used to Indicate the reception of TP Rx Ipdu
        uint8 Not_Used:3;               Not used Bit field

    } Com_RxFlagsType;
     */
    /* FC_VariationPoint_END */

    uint8  RxFlags;

}Com_RxIpduRamData;

/**
 * @ingroup COM_TYPES_H
 * This type defines a pointer type that points to the Rx IPDU dynamic configuration.\n
 *
 * typedef P2CONST( Com_RxIpduRamData, AUTOMATIC, COM_APPL_CONST)  Com_RxIpduRamPtrType;\n
 */
/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_RxIpduRamData, AUTOMATIC, COM_APPL_DATA)  Com_RxIpduRamPtrType;

typedef struct
{
    P2VAR(PduIdType, TYPEDEF, COM_APPL_DATA) RxGwQueuePtr;
    VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueWrite_ux;
    VAR(Com_RxGwQueueIndexType, COM_VAR) Com_RxGwQueueRead_ux;
}Com_RxGwQueueRAMType;

/* The Below typedef can be used as local variable only */
typedef P2VAR( Com_RxGwQueueRAMType, AUTOMATIC, COM_APPL_DATA)  Com_RxGwQueuePtrType;

typedef struct
{
    Com_SignalIdType indexGwMapSigDestIdArray;
    uint8            destCount;
}Com_Prv_xGwMapSigCfg_tst;

/* The Below typedef can be used as local variable only */
typedef P2CONST( Com_Prv_xGwMapSigCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigConfPtrType;

typedef struct
{
    Com_SignalIdType GwMap_DestId;
}Com_Prv_xGwMapSigIdCfg_tst;

typedef P2CONST( Com_Prv_xGwMapSigIdCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapSigIdConfPtrType;

#ifdef COM_TX_SIGNALGROUP
typedef struct
{
    Com_TxIntGrpSignalIdType indexGwMapGrpSigDestIdArray;
    uint8                    destCount;
}Com_Prv_xGwMapGrpSigCfg_tst;

/* The Below typedef can be used as local variable only */
typedef P2CONST( Com_Prv_xGwMapGrpSigCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapGrpSigConfPtrType;

typedef struct
{
    Com_TxIntGrpSignalIdType GwMap_DestGrpSigId;
}Com_Prv_xGwMapGrpSigIdCfg_tst;

/* The Below typedef can be used as local variable only */
typedef P2CONST( Com_Prv_xGwMapGrpSigIdCfg_tst, AUTOMATIC, COM_APPL_CONST)   Com_GwMapGrpSigIdConfPtrType;
#endif /* #ifdef COM_TX_SIGNALGROUP */

typedef struct
{
    P2CONST(Com_Prv_xTxSigCfg_tst, COM_CONST, COM_APPL_CONST)             Com_TxSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_TxSignalMapping_pct;

    P2CONST(Com_Prv_xRxSigCfg_tst, COM_CONST, COM_APPL_CONST)             Com_RxSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_RxSignalMapping_pct;

#ifdef COM_TX_SIGNALGROUP
    P2CONST(Com_Prv_xTxSigGrpCfg_tst, COM_CONST, COM_APPL_CONST)          Com_TxSigGrp_pcst;

    P2CONST(Com_SignalGroupIdType, COM_CONST, COM_APPL_CONST)             Com_TxSignalGrpMapping_pct;

#endif

#ifdef  COM_RX_SIGNALGROUP
    P2CONST(Com_Prv_xRxSigGrpCfg_tst, COM_CONST, COM_APPL_CONST)          Com_RxSigGrp_pcst;

    P2CONST(Com_SignalGroupIdType, COM_CONST, COM_APPL_CONST)             Com_RxSignalGrpMapping_pct;

#endif

#ifdef COM_TX_SIGNALGROUP
    P2CONST(Com_Prv_xTxGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_TxGrpSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_TxGrpSignalMapping_pct;
#endif /* #ifdef COM_TX_SIGNALGROUP */

#ifdef COM_RX_SIGNALGROUP
    P2CONST(Com_Prv_xRxGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_RxGrpSig_pcst;

    P2CONST(Com_SignalIdType, COM_CONST, COM_APPL_CONST)                  Com_RxGrpSignalMapping_pct;
#endif /* #ifdef  COM_RX_SIGNALGROUP */

    P2CONST(Com_Prv_xTxIpduInfoCfg_tst, COM_CONST, COM_APPL_CONST)        Com_TxIpdu_pcst;

    P2CONST(PduIdType, COM_CONST, COM_APPL_CONST)                         Com_TxIpduMapping_pcst;

    P2CONST(Com_Prv_xRxIpduInfoCfg_tst, COM_CONST, COM_APPL_CONST)        Com_RxIpdu_pcst;

    P2CONST(PduIdType, COM_CONST, COM_APPL_CONST)                         Com_RxIpduMapping_pcst;

    P2CONST(Com_Prv_xIpduGrpInfoCfg_tst, COM_CONST, COM_APPL_CONST)       Com_IpduGrp_pcst;

    P2CONST(uint16, COM_CONST, COM_APPL_CONST)                            Com_IpduGrpMapping_pcu16;

#ifdef COM_SIGNALGATEWAY
    P2CONST(Com_Prv_xGwMapSigCfg_tst, COM_CONST, COM_APPL_CONST)          Com_GwSig_pcst;

    P2CONST(Com_Prv_xGwMapSigIdCfg_tst, COM_CONST, COM_APPL_CONST)        Com_GwSigIdMapping_pcst;
#endif

#ifdef COM_SIGNALGROUPGATEWAY
    P2CONST(Com_Prv_xGwMapGrpSigCfg_tst, COM_CONST, COM_APPL_CONST)       Com_GwGrpSig_pcst;

    P2CONST(Com_Prv_xGwMapGrpSigIdCfg_tst, COM_CONST, COM_APPL_CONST)     Com_GwGrpSigIdMapping_pcst;
#endif

    P2CONST(Com_IpduIdType, COM_CONST, COM_APPL_CONST)                    Com_IPduGrp_IpduRef_pcst;

#if defined ( COM_TX_SIGNALGROUP_ARRAY )
    Com_TxSigGrpArrayConstPtrType                                         Com_TxSigGrpArray_pcst;
#endif

#if defined ( COM_RX_SIGNALGROUP_ARRAY )
    Com_RxSigGrpArrayConstPtrType                                         Com_RxSigGrpArray_pcst;
#endif

#if defined(COM_TXSIG_FLOAT64SUPP ) || defined(COM_TXGRPSIG_FLOAT64SUPP) || defined(COM_RXGRPSIG_FLOAT64SUPP) || defined(COM_RXSIG_FLOAT64SUPP)
    P2CONST(float64, COM_CONST, COM_APPL_CONST)                           floatValArray_pcaf64;
#endif

#if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX)
    P2CONST(Com_MaskXType, COM_CONST, COM_APPL_CONST)                     Com_MaskX_pcst;
#endif /* #if defined (COM_F_MASKEDNEWEQUALSX ) || defined(COM_F_MASKEDNEWDIFFERSX) */

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    P2CONST(uint32, COM_CONST, COM_APPL_CONST)                            Com_Mask_pu32;
#endif /* #ifdef COM_F_MASKEDNEWDIFFERSOLD */

#if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS)
    P2CONST(Com_POSMinMaxType, COM_CONST, COM_APPL_CONST)                 Com_POSMinMax_pcst;
#endif /* #if defined (COM_F_NEWISWITHIN_POS) || defined(COM_F_NEWISOUTSIDE_POS) */

#if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG)
    P2CONST(Com_NEGMinMaxType, COM_CONST, COM_APPL_CONST)                 Com_NEGMinMax_pcst;
#endif /* #if defined (COM_F_NEWISWITHIN_NEG) || defined(COM_F_NEWISOUTSIDE_NEG) */

#ifdef COM_F_ONEEVERYN
    P2CONST(Com_OneEveryNType, COM_CONST, COM_APPL_CONST)                 Com_OneEveryN_Const_pcst;

    P2VAR(Com_OneEveryNType, TYPEDEF, COM_APPL_DATA)                      Com_OneEveryN_pe;
#endif /* #ifdef COM_F_ONEEVERYN */

#ifdef COM_F_MASKEDNEWDIFFERSOLD
    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_F_OldVal_pu32;
#endif /* #ifdef COM_F_MASKEDNEWDIFFERSOLD */

#if defined(COM_SigTriggeredOnChange) || defined(COM_SigGrpTriggeredOnChange)
    P2VAR(Com_OldValTrigOnChngType, TYPEDEF, COM_APPL_DATA)               Com_OldValTrigOnChng_puo;
#endif /* #if defined(COM_SigTriggeredOnChange) || defined(COM_SigGrpTriggeredOnChange) */

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SigType_pu8;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SigType_dyn_pu8;
#endif /* #ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT */

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu32;

#ifdef COM_RXSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_SigType_pu64;
#endif

#ifdef COM_RXSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_SigType_pf64;
#endif /* #ifdef COM_RXSIG_FLOAT64SUPP */

#ifdef COM_RX_SIGNALGROUP
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_RxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_RxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_RxGrpSigType_pf64;
#endif /* #ifdef COM_RXGRPSIG_FLOAT64SUPP */

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_SecondRxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu32;

#ifdef COM_RXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_SecondRxGrpSigType_pu64;
#endif

#ifdef COM_RXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_SecondRxGrpSigType_pf64;
#endif /* #ifdef COM_RXGRPSIG_FLOAT64SUPP */

#ifdef COM_RX_SIGNALGROUP_ARRAY
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_RxSigGrpArrayBuf_pu8;
#endif

#endif/* #ifdef COM_RX_SIGNALGROUP */

#ifdef COM_TX_SIGNALGROUP
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_TxGrpSigType_pu8;

    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu16;

    P2VAR(uint32, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu32;

#ifdef COM_TXGRPSIG_INT64
    P2VAR(uint64, TYPEDEF, COM_APPL_DATA)                                 Com_TxGrpSigType_pu64;
#endif

#ifdef COM_TXGRPSIG_FLOAT64SUPP
    P2VAR(float64, TYPEDEF, COM_APPL_DATA)                                Com_TxGrpSigType_pf64;
#endif /* #ifdef COM_TXGRPSIG_FLOAT64SUPP */

#endif/* #ifdef COM_TX_SIGNALGROUP */

    P2VAR(PduInfoType, TYPEDEF, COM_APPL_DATA)                            Com_PduInfo_ps;

    P2VAR(Com_TxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_TxIpduRam_ps;

    P2VAR(Com_RxIpduRamData, TYPEDEF, COM_APPL_DATA)                      Com_RxIpduRam_ps;

    P2VAR(Com_TxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_TxSignalFlag_ps;

    P2VAR(Com_RxSignalFlagType, TYPEDEF, COM_APPL_DATA)                   Com_RxSignalFlag_ps;

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_ps;

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_IpduCounter_DM_ps;

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    P2VAR(PduIdType, TYPEDEF, COM_APPL_DATA)                              Com_RxGwQueue_paux;

    P2VAR(Com_RxGwQueueRAMType, TYPEDEF, COM_APPL_DATA)                   Com_RxGwQueue_ps;
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */

#ifdef COM_RX_SIGNALGROUP
    P2VAR(Com_RxSignalGrpFlagType, TYPEDEF, COM_APPL_DATA)                Com_RxSignalGrpFlag_ps;
#endif/* #ifdef COM_RX_SIGNALGROUP */

#ifdef COM_TX_SIGNALGROUP
#if defined (COM_SigGrpTriggeredOnChange) || defined (COM_SIGNALGROUPGATEWAY)
    P2VAR(Com_TxSignalGrpFlagType, TYPEDEF, COM_APPL_DATA)                Com_TxSignalGrpFlag_ps;
#endif /* #if defined (COM_SigGrpTriggeredOnChange) || defined (COM_SIGNALGROUPGATEWAY) */

    P2VAR(Com_TxGrpSignalFlagType, TYPEDEF, COM_APPL_DATA)                Com_TxGrpSignalFlag_ps;
#endif /* #ifdef COM_TX_SIGNALGROUP */

    P2VAR(uint8, TYPEDEF, COM_APPL_DATA)                                  Com_DeferredBuffer_pu8;

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    P2VAR(uint16, TYPEDEF, COM_APPL_DATA)                                 Com_NumOfGwSignalsUpdated_pau16;
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */

    CONST(uint32, COM_CONST)                                              configId;

    CONST(uint16, COM_CONST)                                              noOfIpduGroup;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfTxSignals;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfRxSignals;

    CONST(Com_SignalGroupIdType, COM_CONST)                               noOfTxSignalGroup;

    CONST(Com_SignalGroupIdType, COM_CONST)                               noOfRxSignalGroup;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfTxGroupSignal;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfRxGroupSignal;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfTxIpdu;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfRxIpdu;

    CONST(Com_SignalIdType, COM_CONST)                                    noOfGwSrcSignals;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGwSrcGrpSignals;

    CONST(Com_IpduIdType, COM_CONST)                                      noOfGwSrcIpdu;

    CONST(Com_GrpSignalIdType, COM_CONST)                                 noOfGrpSigNoGw;

#ifdef COM_F_ONEEVERYN
    CONST(uint8, COM_CONST)                                               noOfOneEveryNSigAndGrpSig;
#endif /* #ifdef COM_F_ONEEVERYN */

}Com_ConfigData_tst;
#endif

