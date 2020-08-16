

#ifndef DCMDSPUDS_UDS_PROT_H
#define DCMDSPUDS_UDS_PROT_H

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF)
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_SetActiveServiceTable      : API used to set the new servive table from the application.
 * @param[in]      Sid_tableid_u8 : new Sid table to going to set.
 * @retval         Std_ReturnType :E_NOT_OK setting of table is unsucessfull.
 *                                 E_OK   setting of table issucessfull .
 *
 */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveServiceTable(VAR(uint8,AUTOMATIC) Sid_tableid_u8);
#endif


#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
extern FUNC(void,DCM_CODE) Dcm_ControlDtcSettingExit(void);
#endif

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)   ||  \
     (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)                              ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern FUNC(void,DCM_CODE) Dcm_ResetDIDIndexstruct (P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st);
#endif

#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
extern FUNC (void,DCM_CODE) Dcm_ResetAsynchFlags(void);
#endif

#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
extern FUNC (void,DCM_CODE) Dcm_ResetAsynchSecaFlag(void);
#endif

#if ((DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)||(DCM_CFG_DIDSUPPORT != DCM_CFG_OFF ))
extern FUNC(void,DCM_CODE) Dcm_ConvBitsToBytes(P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)DataLenInBits) ;
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Macros for the service identifiers in DSP */
#define  DCM_DSP_SID_ECURESET                           0x11u
#define  DCM_DSP_SID_TESTERPRESENT                      0x3Eu
#define  DCM_DSP_SID_SECURITYACCESS                     0x27u
#define  DCM_DSP_SID_ROUTINECONTROL                     0x31u
#define  DCM_DSP_SID_CONTROLDTCSETTING                  0x85u
#define  DCM_DSP_SID_READDTCINFORMATION                 0x19u
#define  DCM_DSP_SID_COMMUNICATIONCONTROL               0x28u
#define  DCM_DSP_SID_READDATABYIDENTIFIER               0x22u
#define  DCM_DSP_SID_WRITEDATABYIDENTIFIER              0x2Eu
#define  DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL           0x10u
#define  DCM_DSP_SID_CLEARDIAGNOSTICINFORMATION         0x14u
#define  DCM_DSP_SID_DYNAMICALLYDEFINEDATAIDENTIFIER    0x2Cu
#define  DCM_DSP_SID_INPUTOUTPUTCONTROLBYIDENTIFIER     0x2Fu
#define  DCM_DSP_SID_REQUESTDOWNLOAD                    0x34u
#define  DCM_DSP_SID_REQUESTUPLOAD                      0x35u
#define  DCM_DSP_SID_REQUESTTRANSFEREXIT                0x37u
#define  DCM_MINSIZE                                    0x00u
#define  DCM_MAXSIZE                                    0x04u


/*
 **********************************************************************************************************
 * Globals Macros for converting byte lengths
 **********************************************************************************************************
 */

/* Convert two uint8 variables to a uint16 variable */

# define DSP_CONV_2U8_TO_U16(hi,lo)                     ((uint16)((uint16)(((uint16)(hi))<<(uint8)8u)| ((uint16)(lo))))

/* Convert four uint8 variables to a uint32 variable */

# define DSP_CONV_4U8_TO_U32(hihi, hilo, lohi, lolo)    ((uint32)((((uint32)(hihi))<<24u)| (((uint32)(hilo))<<16u)| \
                                                (((uint32)(lohi))<<8u) | ((uint32)(lolo))))

/* Convert a uint16 variable to a uint8 MSByte variable */

# define DSP_GET_MSBU16_TO_U8(var)                     ((uint8)(((uint16)(var))>>8u))

/* Convert a uint16 variable to a uint8 LSByte variable */

# define DSP_GET_LSBU16_TO_U8(var)                     ((uint8)(var))

/* Convert two uint16 variables to a uint32 variable */

# define DSP_CONV_2U16_TO_U32(hi,lo)                    ((uint32)((((uint32)(hi))<<16u)| ((uint32)(lo))))

/* Convert a uint32 variable to a uint8 Most Significant Byte variable */

# define DSP_GET_BYTE3U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>24u))

/* Convert a uint32 variable to a uint8 More Significant Byte variable */

# define DSP_GET_BYTE2U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>16u))

/* Convert a uint32 variable to a uint8 Less Significant Byte variable */

# define DSP_GET_BYTE1U32_TO_U8(var)                   ((uint8)(((uint32)(var))>>8u))

/* Convert a uint32 variable to a uint8 Least Significant Byte variable */

# define DSP_GET_BYTE0U32_TO_U8(var)                   ((uint8)(var))

/* Convert a uint32 variable to a uint16 Most Significant variable */

# define DSP_GET_MSWU32_TO_U16(var)                    ((uint16)(((uint32)(var))>>16u))

/* Convert a uint32 variable to a uint16 Least Significant variable */

# define DSP_GET_LSWU32_TO_U16(var)                    ((uint16)(var))

#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) ||((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0)) || \
    (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
/* Macro to define RTE infrastructure error*/
#define DCM_INFRASTRUCTURE_ERROR 0x80u
#endif

/* Macro to define lenth of VIN*/
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))

#define DCM_VIN_DATALEN  17

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,DCM_VAR) Dcm_VInData_au8[DCM_VIN_DATALEN];  /*Buffer to store VIN data*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( boolean, DCM_VAR )Dcm_VinReceived_b;/*Flag to indicate VIN data is received successfully or not */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif


/* Definitions of states of ROE service */
typedef enum
{
    DCM_ROE_CLEARED=0,              /* Initialisation state of ROE events*/
    DCM_ROE_STOPPED,              /* State of ROE events when a valid ROE set up request is received from the tester */
    DCM_ROE_STARTED               /* State of ROE events when a ROE start request is received from the tester */
}Dcm_DspRoeEventState_ten;

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF)
typedef struct
{
    P2FUNC(Std_ReturnType,TYPEDEF,ROEDID_fp)    (VAR(Dcm_DspRoeEventState_ten,AUTOMATIC));
    uint16 RoeEventDid_u16;         /*DID for ROE monitoring*/
    uint8 RoeEventId_u8;            /*RoeeventID configured for the DID*/
} DcmDspRoeDidEvents_tst;

typedef struct
{

    boolean Is_PreConfigured_b;/*The flag will be set to TRUE if the event is preconfigured*/
    boolean stDspRoeCtrlStorageState_b;/* Variable to store the storage bit information for ctrl */
    boolean stDspRoeStorageState_b;     /* Variable to store the storage bit information */
    boolean stDspRoeSessionIsDefault_b;  /* Variable stDspRoeSessionIsDefault_b will be TRUE if the session is Default session and the ROE event is started*/
    uint8 stRoeEventWindowTime_u8;      /* Event Window Time information */
    Dcm_DspRoeEventState_ten RoeEventStatus;    /*State of the ROE event for OnchangeofDid or On DTC status change*/
    uint16 SourceAddress_u16;           /*Tester SourceAddress on which the ROE request was Received*/
    uint16 stRoeEventRecord_u16;        /* Event Record Information */
    uint16 stSrvToRespDid_u16;        /* DID for performing service to respond to action */

}DcmDspRoeDidStateVariables_tst;

#endif

#endif
typedef struct
{
	P2FUNC(Std_ReturnType,TYPEDEF,ROEDTC_fp)    (VAR(Dcm_DspRoeEventState_ten,AUTOMATIC));
    uint8 RoeEventId_u8;            /*RoeeventID configured for the Dtc*/

}DcmDspRoeOnDtcStatusChg_tst;

typedef struct
{
    boolean Is_PreConfigured_b;/*The flag will be set to TRUE if the event is preconfigured*/
    boolean stDspRoeStorageState_b; /* Variable to store the storage bit information */
    boolean stDspRoeCtrlStorageState_b;/* Variable to store the storage bit information for ctrl */
    boolean stDspRoeSessionIsDefault_b; /* Variable stDspRoeSession_b will be TRUE if the session is Default session and the ROE event is started*/
    Dcm_DspRoeEventState_ten RoeEventStatus;    /*State of the ROE event for OnchangeofDid or On DTC status change*/
    uint8 testerReqDTCStatusMask_u8;      /*DTCStatusMask requested to monitor by tester*/
    uint8 stRoeEventWindowTime_u8;     /* Event Window Time information */
    uint16 SourceAddress_u16;           /*Tester SourceAddress on which the ROE request was Received*/
}DcmDspRoeDtcStateVariable_tst;

#if(DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED!=DCM_CFG_OFF)
extern FUNC(void,DCM_CODE)Dcm_ResetRoeOnDtcevents(void);
#endif
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_INVALID_NVDBLOCK    0u

/* Definitions of DID signal Data Port Interface Types */


#define USE_BLOCK_ID                                0x00u
#define USE_DATA_ASYNCH_CLIENT_SERVER               0x01u
#define USE_DATA_SENDER_RECEIVER                    0x02u
#define USE_DATA_SENDER_RECEIVER_AS_SERVICE         0x03u
#define USE_DATA_SYNCH_CLIENT_SERVER                0x04u
#define USE_ECU_SIGNAL                              0x05u
#define USE_DATA_SYNCH_FNC                          0x06u
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
#define USE_DATA_RDBI_PAGED_FNC                     0x07u
#endif
#define USE_DATA_ASYNCH_FNC                         0x08u



/* Definitions of IOCONTROLMASK configured for DID */
typedef enum
{
    DCM_CONTROLMASK_NO=0,                            /* NO Control Mask support */
    DCM_CONTROLMASK_INTERNAL,                        /* Internal Control Mask support, Dcm to do the control mask handling internally */
    DCM_CONTROLMASK_EXTERNAL                         /* External Control Mask support, Dcm to forward the control mask received from tester to application, application will do the handling */
}Dcm_Dsp_IocbiCtrlMask_ten;

/* Did Extended Structure Definition */
typedef struct
{
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
  uint32 dataAllowedSessRead_u32;          /* Allowed sessions for RDBI (for writing on to dcm buffer by application) */
  uint32 dataAllowedSecRead_u32;           /* Allowed security levels for RDBI(for writing on to dcm buffer by application)*/
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserReadModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDREAD != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrRdbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8); /* Mode rule check funtion pointer */
#endif
#endif
#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  uint32 dataAllowedSessWrite_u32;          /* Allowed sessions For wdbi(for reading) */
  uint32 dataAllowedSecWrite_u32;           /* Allowed security levels for wdbi (for reading) */
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserWriteModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDWRITE != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrWdbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8); /* Mode rule check funtion pointer */
#endif
#endif
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  uint32  dataSessBitMask_u32;      /* Session value bit mask for the DID Control */
  uint32  dataSecBitMask_u32;       /* Security level bit mask for the DID Control */
  P2FUNC(Std_ReturnType,TYPEDEF,adrUserControlModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint16,AUTOMATIC),VAR(Dcm_Direction_t,AUTOMATIC));
#if(DCM_CFG_DSP_MODERULEFORDIDCONTROL != DCM_CFG_OFF )
  P2FUNC(boolean,TYPEDEF,adrIocbiModeRuleChkFnc_pfct)(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8); /* Mode rule check funtion pointer */
#endif
  Dcm_Dsp_IocbiCtrlMask_ten dataCtrlMask_en;        /*Control mask type configured by the use, wheher no control Mask or internal or external*/
  uint8     dataCtrlMaskSize_u8;        /*Control mask size*/
  boolean dataIocbirst_b;               /* enable/disable the iocontrol to be reset on session/security change */
  uint8   statusmaskIOControl_u8;      /* Mask to provide info on the supported IO COntrol parameters */
#endif
} Dcm_ExtendedDIDConfig_tst;

#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
typedef struct
{
#if( DCM_CFG_DSP_IOCBI_SR_ENABLED != DCM_CFG_OFF)
  void* const ioControlRequest_cpv;        /*Function pointer for SR interface for IO request*/
#endif
  void* const adrReturnControlEcu_cpv;      /* ReturnControlToEcu Function Pointer */
  void* const adrResetToDefault_cpv;        /* ResetToDefault Function Pointer */
  void* const adrFreezeCurrentState_cpv;    /* FreezeCurrentState Function Pointer */
  void* const adrShortTermAdjustment_cpv;   /* ShortTermAdjustment Function Pointer */
#if (DCM_CFG_DSP_IOCBI_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrResetToDefaultResults_cpv;      /* ResetToDefault Results Function Pointer */
  void* const adrFreezeCurrentStateResults_cpv;  /* FreezeCurrentState Results Function Pointer */
  void* const adrShortTermAdjustmentResults_cpv; /* ShortTermAdjustment Results Function Pointer */
#endif
}Dcm_SignalDIDIocbiConfig_tst;
#endif
typedef struct
{
  void* const adrCondChkRdFnc_cpv;      /* Condition Check Read Function pointer (optional)*/
  /* Function to get the data length (optional) */
  void* const adrReadDataLengthFnc_pfct;
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrCondChkRdFncResults_cpv;      /* Condition Check Read Results Function pointer (optional)*/
 void* const adrReadDataLengthFncResults_pfct; /* Function pointer to get result of Read data length  */
#endif
#if (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFnc_cpv;      /* Write Function pointer */
#if (DCM_CFG_DSP_WRITE_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrWriteFncResults_cpv;     /* Write Function results pointer */
#endif
#endif
#if (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
  VAR(uint16,AUTOMATIC) idxDcmDspIocbiInfo_u16; /*Index to DID Signal Substructure Configuration for IOCBI */
#endif
}Dcm_SignalDIDSubStructConfig_tst;

/* Did Signal Data Structure Definition */
typedef struct
{
  void* const adrReadFnc_cpv;   /* Read Function pointer */
#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
  void* const adrReadFncResults_cpv;   /* Read Function pointer to get the Result of Read function */
#endif
  uint16 dataSize_u16;              /* DID Data Size in bits */
  uint16 dataNvmBlockId_u16;        /*NVM block id for USE_BLOCK_ID*/
  uint16 idxDcmDspControlInfo_u16;  /*Index to DID Control Info structure */
  uint8 dataType_u8;                /* Type of Data configured */
  uint8 usePort_u8;                 /* Type of interface to obtains Data */
  uint8 dataEndianness_u8;          /* Signal endianness type of the signal */
  boolean dataFixedLength_b;        /*Signal is of fixed or variable length*/
#if (DCM_CFG_DSP_DATA_ASYNCHCS_ENABLED != DCM_CFG_OFF)
  boolean UseAsynchronousServerCallPoint_b;
#endif
}Dcm_DataInfoConfig_tst;


typedef struct
{
  uint16 posnSigBit_u16;              /* Signal Position */
  uint16 idxDcmDspDatainfo_u16;  /*DID Signal Substructure Configuration for condition check for read and write and read datalength function*/
} Dcm_SignalDIDConfig_tst;
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
typedef P2FUNC(Std_ReturnType,TYPEDEF,IsDIDAvailFnc_pf) (VAR(uint16,AUTOMATIC) DID_u16);
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST (IsDIDAvailFnc_pf,DCM_CONST) Dcm_DIDIsAvail[DCM_CFG_DSP_NUMISDIDAVAIL];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/* Did Structure Definition */
typedef struct
{
  uint16 dataDid_u16;       /* Data Identifier Value */
  uint16 nrSig_u16;         /* No of signals in the DID */
  uint16 dataMaxDidLen_u16;     /* Maximum size of the DID including Gaps */
  boolean dataFixedLength_b;            /* Fixed length or obtainable using ReadDataLengthFnc */
  boolean dataDynamicDid_b;         /* Dynamically Defined DID */
  P2CONST(Dcm_SignalDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrDidSignalConfig_pcst;  /* Did Signal Data Configuration */
#if(DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)   /*DID configuration mask, included only if post build is enabled*/
  uint8 dataConfigMask_u8;
#endif
#if(DCM_CFG_DSP_NUMISDIDAVAIL > 0)
uint16      idxDIDSupportedFnc_u16;
#endif
  P2CONST(Dcm_ExtendedDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Extended Configuration */
} Dcm_DIDConfig_tst;

typedef struct
{
  P2FUNC(Std_ReturnType,TYPEDEF,adrDIDAvailableFnc_pfct)( VAR(uint16,AUTOMATIC) DID, VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                       P2VAR(Dcm_DidSupportedType,AUTOMATIC,DCM_INTERN_DATA) supported); /* IsDidAvailable function pointer */
  P2FUNC(Std_ReturnType,TYPEDEF,adrReadFnc_pfct)( VAR(uint16,AUTOMATIC) DID,
                                             CONSTP2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,
                                             VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                             CONSTP2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength,
                                             CONSTP2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                            );      /* ReadDIDdata function pointer */

  void* const adrReadDataLengthFnc_pfct; /* ReadDIDdataLength function pointer */
  void* const adrWriteFnc_pfct; /* WriteDIDdata function pointer */
  P2CONST(Dcm_ExtendedDIDConfig_tst, DCM_VAR, DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Extended Configuration */
  uint16 nrDidRangeUpperLimit_u16;      /* Upper limit of DID range */
  uint16 nrDidRangeLowerLimit_u16;      /* Lower limit of DID range */
  uint16 dataMaxDidLen_u16;                 /* Maximum data length in bytes */
  boolean dataRangeHasGaps_b;               /* Dynamically Defined DID */
  boolean nrRangeUsePort_b;             /* Fixed length or obtainable using ReadDataLengthFnc */
} Dcm_DIDRangeConfig_tst;
/* Condition Check Read Function Pointer Types */


/*ReadDatalength function pointer for a normal DID and not a dynamically defined DID*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc1_pf) (P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength);



typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc4_pf) (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength);

/*ReadDatalength function pointer for a dynamically defined DID*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadDataLengthFnc2_pf) (P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) DataLength);

/*ReadDataLength function pointer for a range did*/
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReaddatalengthFnc3_pf)( VAR(uint16,AUTOMATIC) DID,VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                       P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) DataLength); /* ReadDIDdataLength function pointer */

/* When Asynchronous server point handling is requested */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReaddatalengthFnc5_pf)(void);

/* When UsePort is USE_DATA_SYNCH_FNC / DATA_SYNC_CLIENT_SERVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc1_pfct)
                                   (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNCH_FNC / DATA_ASYNC_CLIENT_SERVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc2_pfct)
                                   (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When Asynchronous server call point handling is used */
typedef P2FUNC(Std_ReturnType,TYPEDEF,CondChkReadFunc3_pfct)
                                   (VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);


/* Read Data Function Pointer Types */

/* When UsePort is USE_DATA_SYNCH_FNC / DATA_SYNC_CLIENT_SERVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc1_pfct)(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
/* When UsePort is USE_DATA_SYNCH_FNC / DATA_SYNC_CLIENT_SERVER and when the read call id for DDDID */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc10_pfct)(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);

/* When UsePort is USE_DATA_ASYNCH_FNC/DATA_ASYNC_CLIENT_SERVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc2_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data);
/* When UsePort is SENDER_RECEIVER */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc3_pfct)(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc4_pfct)(P2VAR(uint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc5_pfct)(P2VAR(uint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc6_pfct)(P2VAR(sint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc7_pfct)(P2VAR(sint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc8_pfct)(P2VAR(sint32, AUTOMATIC,DCM_INTERN_DATA) Data);

#if (DCM_CFG_DSP_READ_ASP_ENABLED != DCM_CFG_OFF)
/* When Asynchronous server call point handling is used */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc11_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus);
#endif

#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
/* When UsePort is USE_DATA_RDBI_PAGED_FNC */
typedef P2FUNC(Std_ReturnType,TYPEDEF,ReadFunc9_ptr)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,      \
                                                     P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Data,   \
                                                     P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) BufSize,   \
                                                     P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode);
#endif


#if(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#endif
#if(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveWDBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#endif
#if(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveIOCBIDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#endif
#if(DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiIsDidCondtionChkReadSupported(P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st);
#endif
#if(DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDDDid(P2VAR (uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);
#endif
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(uint16,DCM_CODE) Dcm_DIDcalculateTableSize_u16(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_DIDConfig_tst, DCM_CONST) Dcm_DIDConfig [];
extern CONST(Dcm_DataInfoConfig_tst, DCM_CONST)  Dcm_DspDataInfo_st[];
extern CONST(Dcm_SignalDIDSubStructConfig_tst, DCM_CONST)  Dcm_DspDid_ControlInfo_st[];
#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
extern CONST(Dcm_SignalDIDIocbiConfig_tst, DCM_CONST)  Dcm_DspIOControlInfo[];
#endif
extern CONST (Dcm_DIDRangeConfig_tst, DCM_CONST) Dcm_DIDRangeConfig_cast[];
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern CONST(DcmDspRoeDidEvents_tst, DCM_CONST) DcmDspRoeDidEvents[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern CONST(DcmDspRoeOnDtcStatusChg_tst,DCM_CONST) DcmDspRoeDtcEvent;
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
extern VAR(DcmDspRoeDidStateVariables_tst, DCM_VAR) DcmDspRoeDidStateVariables[DCM_MAX_DIDROEEVENTS];
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) &&  (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))
extern VAR(DcmDspRoeDtcStateVariable_tst, DCM_VAR) DcmDspRoeDtcStateVariable;
#endif
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (uint16,DCM_VAR) Dcm_DidSignalIdx_u16;
#define DCM_STOP_SEC_VAR_CLEARED_16 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (boolean   ,DCM_VAR) Dcm_flgDspDidRangePending_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* temporary solution--> to be removed together with RDPI */
extern VAR(boolean ,DCM_VAR) Dcm_PeriodicSchedulerRunning_b;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


#if ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_ResetRoeDidevents(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

extern VAR (uint8,DCM_VAR) Dcm_RoeDidIdx_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC (void,DCM_CODE) Dcm_Dsp_SecaClearSeed (void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /*( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) && (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)*/
#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_ResetAccessType (void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif /* DCM_CFG_DSPUDSSUPPORT_ENABLED */
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(Std_ReturnType ,DCM_CODE)  Dcm_VinBuffer_Init(void);
extern FUNC(Std_ReturnType ,DCM_CODE)  Dcm_ReadVinBuffer(P2VAR(uint8, AUTOMATIC, DCM_VAR) Data);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif /* _DCMDSPUDS_UDS_PROT_H  */

