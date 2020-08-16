


#ifndef DCMCORE_DSLDSD_PUB_H
#define DCMCORE_DSLDSD_PUB_H

/************************************************************************************************/
/* Included  header files                                                                       */
/************************************************************************************************/

/*
 ***************************************************************************************************
 *    definitions and Typedefs
 ***************************************************************************************************
 */

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *
 * Definitions of DID/PID Signal DataTypes\n
 *
 *
 */
#define DCM_BOOLEAN                     0x00u
#define DCM_UINT8                       0x01u
#define DCM_UINT16                      0x02u
#define DCM_UINT32                      0x03u
#define DCM_SINT8                       0x04u
#define DCM_SINT16                      0x05u
#define DCM_SINT32                      0x06u
#define DCM_VARIABLE_LENGTH             0x07u
#define DCM_UINT8_N                     0x08u
#define DCM_UINT16_N                    0x09u
#define DCM_UINT32_N                    0x0Au
#define DCM_SINT8_N                     0x0Bu
#define DCM_SINT16_N                    0x0Cu
#define DCM_SINT32_N                    0x0Du


/* Value from which the Array Data Types for Routine Control Starts */
#define DCM_RCARRAYINDEX  0x08u

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *
 * Definitions of DID/PID/RID Endianness Types\n
 *
 *
 */
#define DCM_LITTLE_ENDIAN               0x00u
#define DCM_BIG_ENDIAN                  0x01u
#define DCM_OPAQUE                      0x02u


/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *
 * Definitions of Dcm Service OpStatus Type
 *
 *
 */
typedef uint8 Dcm_SrvOpStatusType;



/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *
 * Macros for Internal API's\n
 *
 *
 */
#define DsdInternal_SetNegResponse  Dcm_SetNegResponse
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *
 * Macros for Internal API's\n
 *
 *
 */
#define DsdInternal_ProcessingDone  Dcm_ProcessingDone


/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * This type defines data structure for the delay information and the failed attempt count per security level \n
 */
#if(DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF)
typedef struct
{
    uint8  SecurityLevel;       /* Security Level */
    uint16 DelayCount;          /* Number of failed attempt count per security level */
    uint32 ResidualDelay;       /* The remaining delay per security level */
}Dcm_Dsp_Seca_t;
#endif


/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Used in Dcm_SetProgConditions() to allow the integrator to store relevant information prior to jumping to bootloader.\n
 *  uint8  ProtocolId                       Active Protocol ID \n
 *  uint8  Sid;                             Active Service Identifier\n
 *  uint8  SubFncId;                        Active Subfunction Id\n
 *  uint8  StoreType;                       Storing Type used for Storing the information\n
 *  uint8  SessionLevel;                    Active Session\n
 *  uint8  SecurityLevel;                   Active Security\n
 *  uint8  ReqResLen;                       Request / Response Length\n
 *  uint8  NumWaitPend;                     Number of waitpends triggered\n
 *  uint8  ReqResBuf[8];                    Request / Response buffer\n
 *  uint16 TesterSourceAddr;                Tester address of the active Rx PduId\n
 *  uint32 ElapsedTime;                     Total elapsed time\n
 *  boolean ReprogramingRequest             Reprograming of ecu requested or not\n
 *  boolean ApplUpdated                     Application has to be updated or not \n
 *  boolean ResponseRequired                Response has to be sent by flashloader or application \n
 *  uint8 NumOfSecurityLevels               Number of security levels configured  \n
 *  Dcm_Dsp_Seca_t SecurityInformation      array of structure for storing the delay and the failed attempt count info per security level  \n
 *  uint8 freeForProjectUse                 6 bytes of free space is provided for projects to store additional information like CAN ID, BAUD Rate, etc.. \n
 */
 /* INFORMATION: New parameters introduced in the below structure (Dcm_ProgConditionsType) should always be added at the end to enable compatability with existing boot block.
 * Kindly do not remove this comment without clear investigation.
 */
typedef struct
{
	uint8  ProtocolId;			/* Active Protocol ID */
	uint8  Sid;                  /* Active Service Identifier */
	uint8  SubFncId;             /* Active Subfunction Id */
	uint8  StoreType;            /* Storing Type used for Storing the information */
	uint8  SessionLevel;         /* Active Session */
	uint8  SecurityLevel;        /* Active Security */
	uint8  ReqResLen;            /* Request / Response Length */
	uint8  NumWaitPend;          /* Number of waitpends triggered */
	uint8  ReqResBuf[8];         /* Request / Response buffer */
	uint16 TesterSourceAddr;     /* Teseter address of the active Rx PduId */
	uint32 ElapsedTime;          /* Total elapsed time */
	boolean ReprogramingRequest; /* Reprograming of ecu requested or not*/
	boolean ApplUpdated;         /* Application has to be updated or not*/
	boolean ResponseRequired;    /* Response has to be sent by flashloader or application*/
#if(DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF)
    uint8 NumOfSecurityLevels;   /* Number of security levels configured */
    Dcm_Dsp_Seca_t SecurityInformation[DCM_CFG_NUM_SECURITY_LEVEL - 1u];  /* array of structure for storing the delay and the failed attempt count info per security level */
#endif
	uint8 freeForProjectUse[6];  /*6 bytes of free space is provided for projects to store additional information like CAN ID, BAUD Rate, etc..*/
}Dcm_ProgConditionsType;


/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * This type defines data structure for the post build parameters of the dcm.At initialization the dcm\n
 * gets a pointer to a structure of this type to get access to its configuration data which is necessary for initialization.
 *
 *
 */
typedef struct
{
	uint8  ConfigSetId;			/** selected configuration,allows upto 8 config variants */
}Dcm_ConfigType;


/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * This will specify the Ecu Start mode.If it  is set ,the Ecu starts from a bootloader jump.
 * If it is zero,Ecu starts normally.
 * DCM_COLD_START\n
 * DCM_WARM_START\n
 *
 *
 */

typedef uint8 Dcm_EcuStartModeType;
#define DCM_COLD_START   0x0u /* The ECU starts normally */
#define DCM_WARM_START   0x1u /* The ECU starts from a bootloader jump */



#define DCM_VENDOR_ID                   6u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Module id of DCM
 *
 */
#define DCM_MODULE_ID                   0x35u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Instance Id refers to an ID assigned by Autosar to identify every unique instance of one Module/Component, used to indicate that module instance which is reporting the error during the call of Det_ReportError()
 *
 */
#define DCM_INSTANCE_ID                 0x00u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare the Major Release Number of Autosar Main Baseline under which this Component Dcm is delivered.
 *
 */
#define DCM_AR_RELEASE_MAJOR_VERSION	4u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare the Minor Release Number of Autosar Main Baseline under which this Component Dcm is delivered.
 *
 */
#define DCM_AR_RELEASE_MINOR_VERSION    2u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare the Revision Release Number of Autosar Main Baseline under which this Component Dcm is delivered
 *
 */
#define DCM_AR_RELEASE_REVISION_VERSION 2u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare Software Major Version number of Component Dcm, used during the call of Dcm_GetVersionInfo().
 *
 */

#define DCM_SW_MAJOR_VERSION            3u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare Software Minor Version number of Component Dcm, used during the call of Dcm_GetVersionInfo
 *
 */
#define DCM_SW_MINOR_VERSION            0u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Used to declare Software Patch Version number of Component Dcm, used during the call of Dcm_GetVersionInfo()
 *
 */
#define DCM_SW_PATCH_VERSION            0u

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * define for  functional request
 *
 */
#define DCM_PRV_FUNCTIONAL_REQUEST          1u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * define for  physical request
 *
 */
#define DCM_PRV_PHYSICAL_REQUEST            0u

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Defines for maximum number of dcm config sets
 *
 */
#define DCM_PRV_MAXNUM_OF_CONFIG            8u

/*  Base item type to transport status information.
 *
 *                                             */


/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Base item type to transport status information.\n
 * DCM_E_OK This value is representing a successful operation.\n
 * DCM_E_TI_PREPARE_LIMITS New timing parameters are not ok, since requested values are not within the defined limits (used at API: Dcm_PrepareSesTimingValues()).\n
 * DCM_E_TI_PREPARE_INCONSTENT New timing parameters are not ok, since requested values are not consistent (e.g. P2min not smaller than P2max)(used at API: Dcm_PrepareSesTimingValues())\n
 * DCM_E_ROE_NOT_ACCEPTED ResponseOnOneEvent request is not accepted by DCM (e.g. old ResponseOnOneEvent is not finished) (used at API: Dcm_ResponseOnOneEvent())\n
 * DCM_E_PERIODICID_NOT_ACCEPTED Periodic transmission request is not accepted by DCM (e.g. old Periodic transmission is not finished) (used at API: Dcm_ResponseOnOneDataByPeriodicId ())\n
 *
 */
typedef uint8 Dcm_StatusType;

/* positive case return by the Appl fucntion                                                    */
#define DCM_E_OK                        0u

/* New timing parameter are not ok, since requested values are not within the defined limits    */
#define DCM_E_TI_PREPARE_LIMITS         2u

/* New timing parameter are not ok, since requested values are not consistent(e.g.P2min not     */
/* smaller than P2max)                                                                          */
#define DCM_E_TI_PREPARE_INCONSTENT     3u

/* ResponseOnOneEvent request is not accepted by DCM (e.g. old ResponseOnOneEvent is            */
/* not finished)                                                                                */
#define DCM_E_ROE_NOT_ACCEPTED          6u

/* Periodic transmission request is not accepted by DCM (e.g. old Periodic transmission is      */
/* not finished)                                                                                */
#define DCM_E_PERIODICID_NOT_ACCEPTED   7u

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Seed sent by application is not correct
 *
 */

#define DCM_E_SEED_NOK                   11u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Time Monitoring is required for SECA request
 *
 */
#define DCM_E_MONITORING_REQ             12u
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Time Monitoring is not required for SECA request
 *
 */

#define DCM_E_MONITORING_NOTREQ          13u


#define DCM_UNUSED_PARAM(P)   ((void)(P))

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *Base type for diagnostic message item.
 *
 */
typedef uint8 Dcm_MsgItemType;
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Base type for diagnostic message (request, positive or negative response).
 *
 */
typedef P2VAR(Dcm_MsgItemType,TYPEDEF,DCM_INTERN_DATA)  Dcm_MsgType;

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Length of diagnostic message (request, positive or negative response).\n
 * The maximum length is dependent of the underlying transport protocol/media.\n
 * E. g. the maximum message length for CAN Transport Layer is 4095bytes. \n
 */

typedef uint32 Dcm_MsgLenType;

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Additional information on message request.\n
 * uint8 reqType  (Position LSB+0)0 = physical request,1 = functional request\n
 * uint8   suppressPosResponse (Position LSB+1 )0 = no (do not suppress),1 = yes (no positive response will be sent)\n
 * uint8   sourceofRequest  0=Diagnostic request (from tester),1=ROE requested service call,2=RDPI requested service call\n
 */
typedef struct
{
    /* 0 = physical request               */
    /* 1 = functional request             */
    uint8   reqType;

    /* 0 = no (do not suppress)                      */
    /* 1 = yes (no positive response will be sent)   */
    boolean   suppressPosResponse;
    /* 0 = Dignostic request (from tester)           */
    /* 1 = ROE requested service call                */
    /* 2 = RDPI requested service call               */
    uint8   sourceofRequest;
}Dcm_MsgAddInfoType;

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * This message context identifier can be used to determine the relation between request and response confirmation.
 */
typedef uint8 Dcm_IdContextType;

/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * This data structure contains all information which is necessary to process a diagnostic message from request to response and response confirmation.\n
 * resData    :Positive response data, starting directly after service identifier(which is not part of this data)\n
 * reqData    :starting directly after service identifier(which is not part of this data)\n
 * msgAddInfo :Additional information about service request and response\n
 * resDataLen :Positive response data length (excluding service identifier)\n
 * reqDataLen :Request data length (excluding service identifier)\n
 * resMaxDataLen : The maximal length of a response is restricted by the size of the buffer.\n
 * idContext  :This message context identifier can be used to determine the relation between request and response confirmation.\n
 * dcmRxPduId :Pdu identifier on which the request was received.
 *
 */
typedef struct
{
    /**
     * Positive response data, starting directly after service identifier (which
     * is not part of this data).
     * The service identifier will be determined by DCM itself.
     */
    Dcm_MsgType resData;

    /**
     * Request data, starting directly after service identifier
     * (which is not part of this data)
     */
    Dcm_MsgType reqData;

    /**
     * Additional information about service request and response
     * (see: Dcm_MsgAddInfo)
     */
    Dcm_MsgAddInfoType msgAddInfo;


    /**
     * Positive response data length (excluding service identifier)
     */
    Dcm_MsgLenType resDataLen;

    /**
     * Request data length (excluding service identifier)
     */
    Dcm_MsgLenType reqDataLen;

    /**
     * The maximal length of a response is restricted by the size of the buffer.
     * The buffer size can depend on the diagnostic protocol identifier which
     * is assigned to this message,
     \ifnot COMP_DCM
     * FC_VariationPoint_START
     \endif
     * e. g. an OBD protocol id can obtain other
     \ifnot COMP_DCM
     * FC_VariationPoint_END
     \endif
     * properties than the enhanced diagnostic protocol id. The resMaxDataLen is
     * a property of the diagnostic protocol assigned by the DSL. The value does
     * not change during communication. It cannot be implemented as a constant,
     * because it can differ between different diagnostic protocols.
     */
    Dcm_MsgLenType resMaxDataLen;

    /**
     * This message context identifier can be used to determine the relation
     * between request and response confirmation. This identifier can be stored
     * within the application at request time, so that the response can be
     * assigned to the original request.
     * Background: Within the confirmation, the message context is no more valid,
     * all message data is lost. You need an additional information to determine
     * the request to which this confirmation belongs.
     */
    Dcm_IdContextType idContext;

    /**
     * Pdu identifier on which the request was received. The PduId of the request
     * can have consequences for message processing.
     \ifnot COMP_DCM
     * FC_VariationPoint_START
     \endif
     * E. g. an OBD request will be
     * received on the OBD PduId and will be processed slightly different than an
     * enhanced diagnostic request received on the physical PduId.
      \ifnot COMP_DCM
     * FC_VariationPoint_END
      \endif
     */
    PduIdType dcmRxPduId;

}Dcm_MsgContextType;



#ifndef DEFAULT_SESSION
/* Macro according to SWS.2.1.1 */
/**
 *   @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Session type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Default session\n
 *  DEFAULT_SESSION 0x01\n
 */
#define DEFAULT_SESSION DCM_DEFAULT_SESSION
#endif

#ifndef PROGRAMMING_SESSION
/* Macro according to SWS.2.1.1 */
/**
 *   @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Session type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Programming session\n
 *  PROGRAMMING_SESSION 0x02\n
 */
#define PROGRAMMING_SESSION  DCM_PROGRAMMING_SESSION
#endif

#ifndef EXTENDED_DIAGNOSTIC_SESSION
/* Macro according to SWS.2.1.1 */
/**
 *   @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Session type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Extended diagnostic session\n
 *  EXTENDED_DIAGNOSTIC_SESSION 0x03\n
 */
#define EXTENDED_DIAGNOSTIC_SESSION    DCM_EXTENDED_DIAGNOSTIC_SESSION
#endif

#ifndef SAFETY_SYSTEM_DIAGNOSTIC_SESSION
/* Macro according to SWS.2.1.1 */
/**
 *   @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Session type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Safety  system diagnostics session\n
 *  SAFETY_SYSTEM_DIAGNOSTICS_SESSION 0x04\n
 */
#define SAFETY_SYSTEM_DIAGNOSTIC_SESSION  DCM_SAFETY_SYSTEM_DIAGNOSTICS_SESSION
#endif

#ifndef DCM_ALL_SESSION_LEVEL
/**
 *   @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Session type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  All sessions\n
 *  DCM_ALL_SESSION_LEVEL 0xFF\n
 *  (Reserved by Document 0x7F...0xFE)
 */
#define DCM_ALL_SESSION_LEVEL 0xFFu
#endif

#ifndef DCM_SEC_LEV_LOCKED
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Security level type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Security level locked\n
 *  DCM_SEC_LEV_LOCKED 0x00\n
 */
#define DCM_SEC_LEV_LOCKED  0x00u
#endif

#ifndef DCM_SEC_LEV_ALL
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Security level type definition:This type is defined in Rte_Dcm_Type.h header file, which is generated by the RTE generator\n
 *  Security level all\n
 *  DCM_SEC_LEV_ALL     0xFF\n
 */
#define DCM_SEC_LEV_ALL     0xFFu
#endif

#ifndef DCM_RES_POS_OK
/* POS response sent successfully */
#define DCM_RES_POS_OK      0u
#endif

#ifndef DCM_RES_POS_NOT_OK
/* unable to sent POS response   */
#define DCM_RES_POS_NOT_OK  1u
#endif

#ifndef DCM_RES_NEG_OK
/* NEG response sent successfully */
#define DCM_RES_NEG_OK      2u
#endif

#ifndef DCM_RES_NEG_NOT_OK
/* unable to sent NEG response   */
#define DCM_RES_NEG_NOT_OK  3u
#endif


#ifndef DCM_UDS_TESTER_SOURCE
/* Source of request is tester */
#define DCM_UDS_TESTER_SOURCE   0u
#endif

#ifndef DCM_ROE_SOURCE
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 *  Source of request is ROE application\n
 */
#define DCM_ROE_SOURCE          1u
#endif


#ifndef DCM_RDPI_SOURCE
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 *  Source of request is RDPI application\n
 */
#define DCM_RDPI_SOURCE          2u
#endif

#ifndef DCM_RDPI_SID
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 *  Service Identifier for RDPI\n
 */
#define DCM_RDPI_SID        0x2Au
#endif
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Dcm_CommunicationModeType:\n
 *  DCM_ENABLE_RX_TX_NORM 0x00  Enable the Rx and Tx for normal communication\n
 *  DCM_ENABLE_RX_DISABLE_TX_NORM 0x01 Enable the Rx and disable the Tx for normal communication\n
 *  DCM_DISABLE_RX_ENABLE_TX_NORM 0x02 Disable the Rx and enable the Tx for normal communication\n
 *  DCM_DISABLE_RX_TX_NORMAL 0x03 Disable Rx and Tx for normal communication\n
 *  DCM_ENABLE_RX_TX_NM  0x04 Enable the Rx and Tx for network management communication\n
 *  DCM_ENABLE_RX_DISABLE_TX_NM 0x05 Enable Rx and disable the Tx for network management communication\n
 *  DCM_DISABLE_RX_ENABLE_TX_NM 0x06 Disable the Rx and enable the Tx for network management communication\n
 *  DCM_DISABLE_RX_TX_NM 0x07 Diable Rx and Tx for network management communication\n
 *  DCM_ENABLE_RX_TX_NORM_NM 0x08 Enable Rx and Tx for normal and network management communication\n
 *  DCM_ENABLE_RX_DISABLE_TX_NORM_NM 0x09 Enable the Rx and disable the Tx for normal and network management communication\n
 *  DCM_DISABLE_RX_ENABLE_TX_NORM_NM 0x0A Disable the Rx and enable the Tx for normal and network management communication\n
 *  DCM_DISABLE_RX_TX_NORM_NM 0x0B Disable Rx and Tx for normal and network management communication.
 */

typedef uint8 Dcm_CommunicationModeType;

#ifndef DCM_ENABLE_RX_TX_NORM
#define DCM_ENABLE_RX_TX_NORM 0x00u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NORM
#define DCM_ENABLE_RX_DISABLE_TX_NORM 0x01u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NORM
#define DCM_DISABLE_RX_ENABLE_TX_NORM 0x02u
#endif

#ifndef DCM_DISABLE_RX_TX_NORMAL
#define DCM_DISABLE_RX_TX_NORMAL 0x03u
#endif

#ifndef DCM_ENABLE_RX_TX_NM
#define DCM_ENABLE_RX_TX_NM 0x04u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NM
#define DCM_ENABLE_RX_DISABLE_TX_NM 0x05u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NM
#define DCM_DISABLE_RX_ENABLE_TX_NM 0x06u
#endif

#ifndef DCM_DISABLE_RX_TX_NM
#define DCM_DISABLE_RX_TX_NM 0x07u
#endif

#ifndef DCM_ENABLE_RX_TX_NORM_NM
#define DCM_ENABLE_RX_TX_NORM_NM 0x08u
#endif

#ifndef DCM_ENABLE_RX_DISABLE_TX_NORM_NM
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM 0x09u
#endif

#ifndef DCM_DISABLE_RX_ENABLE_TX_NORM_NM
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM 0x0Au
#endif

#ifndef DCM_DISABLE_RX_TX_NORM_NM
#define DCM_DISABLE_RX_TX_NORM_NM 0x0Bu
#endif

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 *
 *Service has to finish the filling of data into current page with in these many call of service.
*/
#define DCM_PRV_PAGEBUFFER_TIMEIN_CYCLES ((DCM_PAGEDBUFFER_TIMEOUT)/(DCM_CFG_TASK_TIME_US))


/* *******************************************************************************************************************/

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))


/* ROE or RDPI types */
#define DCM_PRV_DSLD_TYPE1      0x01u
#define DCM_PRV_DSLD_TYPE2      0x02u

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Protocol's ROE-RDPI information
 * Dcm_MsgType txbuffer_ptr;  \n
 * Dcm_MsgLenType txbuffer_length_u32;   \n
 * uint8 servicetable_Id_u8;   \n
 * uint8   roerdpi_type_u8;
 *
*/

typedef struct
{
    Dcm_MsgType txbuffer_ptr;                        /* Tx buffer */
    Dcm_MsgLenType txbuffer_length_u32;              /* Tx buffer length */
    uint8 servicetable_Id_u8;                        /* ROE service table */
    uint8   roerdpi_type_u8;                              /* Roe type  */
}Dcm_RoeRdpiInfo_type;
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Protocol's RDPI TYPE2 TX information
 *  PduIdType   txpduid_num_u8                        TxPduId number \n
 *  Dcm_MsgType txbuffer_ptr                        Tx buffer   \n
 *  boolean     isTxPduId_Busy                        Roe type
 *
*/
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
typedef struct
{
    PduIdType txpduid_num_u8;                        /* TxPduId number */
    Dcm_MsgType txbuffer_ptr;                        /* Tx buffer */
    boolean   isTxPduId_Busy;                              /* Roe type  */
    uint8 cntFreeTxPduRdpi2Cntr_u8;                 /**Counter to relieve the TxPduID once the configured timeout is reached*/
}Dcm_RdpiTxInfo_type;

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Protocol's RDPI TYPE2 TX information array.
 */
#if(DCM_CFG_NUM_RDPITYPE2_TXPDU>0)
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
    extern VAR(Dcm_RdpiTxInfo_type, DCM_VAR) Dcm_Dsld_RDPIType2tx_table[DCM_CFG_NUM_RDPITYPE2_TXPDU];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

#endif
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * protocol structure :This structure will contain all the protocol related information.\n
 * Dcm_MsgType  tx_buffer_pa;                        Tx buffer address \n
 * Dcm_MsgType  rx_buffer_pa;                        Rx buffer address \n
 * P2CONST(Dcm_RoeRdpiInfo_type,TYPEDEF,DCM_INTERN_CONST) roe_info_pcs;   Ptr to ROE info structure \n
 * P2CONST(Dcm_RoeRdpiInfo_type,TYPEDEF,DCM_INTERN_CONST) rdpi_info_pcs;        Ptr to RDPI info structure \n
 * Dcm_MsgLenType tx_buffer_size_u32;                Tx buffer size \n
 * Dcm_MsgLenType rx_buffer_size_u32;              Rx buffer size \n
 * uint8  protocolid_u8;                           Protocol id\n
 * uint8  sid_tableid_u8;                           Id of distributor table\n
 * uint8  premption_level_u8;                        Preemption level\n
 * uint8  pduinfo_idx_u8;                           Index to the RAM Pduinfo structure\n
 * uint8  timings_limit_idx_u8;                     Index to KWP default timing structure unused variable for UDS\n
 * uint8  timings_idx_u8;                            Index to KWP default timing structure unused variable for UDS\n
 * boolean Endianness_ConvEnabled_b;				  Endianness Conversion enabled ro disabled for this protocol\n
 * uint8 Config_Mask;								  Configuration mask to indicate the availability of protocol in different configsets\n
 * boolean nrc21_b;                                  React with NRC-21 if this protocol is received and rejected during pre-emption assertion\n
 * boolean sendRespPendTransToBoot;                  Resp Pend on Transit to Boot enabled or disabled for this protocol
*/

/* FC_VariationPoint_START */
                    /*Obsolete*/
#ifndef     DCM_FUNCTIONAL_REQUEST
#define     DCM_FUNCTIONAL_REQUEST      DCM_PRV_FUNCTIONAL_REQUEST
#endif
#ifndef     DCM_PHYSICAL_REQUEST
#define     DCM_PHYSICAL_REQUEST        DCM_PRV_PHYSICAL_REQUEST
#endif
#ifndef     DCM_MAXNUM_OF_CONFIG
#define     DCM_MAXNUM_OF_CONFIG        DCM_PRV_MAXNUM_OF_CONFIG
#endif
#ifndef     DCM_PAGEBUFFER_TIMEIN_CYCLES
#define     DCM_PAGEBUFFER_TIMEIN_CYCLES DCM_PRV_PAGEBUFFER_TIMEIN_CYCLES
#endif
#ifndef     DCM_DSLD_TYPE1
#define     DCM_DSLD_TYPE1              DCM_PRV_DSLD_TYPE1
#endif
#ifndef     DCM_DSLD_TYPE2
#define     DCM_DSLD_TYPE2              DCM_PRV_DSLD_TYPE2
#endif
/* FC_VariationPoint_END */




/* protocol structure */
typedef struct
{
    Dcm_MsgType  tx_buffer_pa;                       /* Tx buffer address */
    Dcm_MsgType  rx_buffer1_pa;                       /* Rx buffer address */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  rx_buffer2_pa;                       /* Rx buffer address */
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    P2CONST(Dcm_RoeRdpiInfo_type,TYPEDEF,DCM_INTERN_CONST) roe_info_pcs;        /* Ptr to ROE info structure */
#endif
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
    P2CONST(Dcm_RoeRdpiInfo_type,TYPEDEF,DCM_INTERN_CONST) rdpi_info_pcs;       /* Ptr to RDPI info structure */
#endif
    Dcm_MsgLenType tx_buffer_size_u32;               /* Tx buffer size */
    Dcm_MsgLenType rx_buffer_size_u32;               /* Rx buffer size */
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_MsgLenType maxResponseLength_u32;
#endif
    uint32 dataP2TmrAdjust;						     /* P2 server time adjust*/
    uint32 dataP2StarTmrAdjust;						 /* P2star server time adjust*/
    uint8  protocolid_u8;                            /* Protocol id */
    uint8  sid_tableid_u8;                           /* Id of distributor table */
    uint8  premption_level_u8;                       /* Preemption level */
    uint8  pduinfo_idx_u8;                           /* Index to the RAM Pduinfo structure */
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    uint8  timings_limit_idx_u8;                     /* Index to KWP default timing structure unused variable for UDS */
    uint8  timings_idx_u8;                           /* Index to KWP default timing structure unused variable for UDS */
#endif
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
    uint8 Config_Mask;								 /* Configuration mask to indicate the availability of protocol in different configsets*/
#endif
    boolean nrc21_b;                                 /* React with NRC-21 if this protocol is received and rejected during pre-emption assertion */
    boolean sendRespPendTransToBoot;                 /* Resp Pend on Transit to Boot enabled or disabled for this protocol */
}Dcm_Dsld_protocol_tableType;

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_Dsld_SubServiceType:-GIves all subfunction related info.
 * uint32 allowed_session_b32;        Allowed sessions \n
 * uint32 allowed_security_b32;       Allowed security levels \n
 * P2FUNC(boolean,TYPEDEF,moderule_fp)	(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));\n
 * uint8  subservice_id_u8;           Subservice identifier\n
 *
 */
typedef struct
{
    uint32 allowed_session_b32;                      /* Allowed sessions */
    uint32 allowed_security_b32;                     /* Allowed security levels */
#if((DCM_CFG_DSD_MODERULESUBFNC_ENABLED!=DCM_CFG_OFF))
    P2FUNC(boolean,TYPEDEF,moderule_fp)	(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));
#endif
    P2FUNC(Std_ReturnType,TYPEDEF,adrUserSubServiceModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint8,AUTOMATIC),VAR(uint8,AUTOMATIC));
    P2FUNC(Std_ReturnType,TYPEDEF,SubFunc_fp) (VAR(Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));/* Function pointer for the subfunction*/
    uint8  subservice_id_u8;                         /* Subservice identifier */
    boolean isDspRDTCSubFnc_b;                  /* Is Dsp RDTC function or not*/
}Dcm_Dsld_SubServiceType;

typedef void (*Dcm_ConfirmationApiType)(Dcm_IdContextType dataIdContext_u8,PduIdType dataRxPduId_u8, uint16 dataSourceAddress_u16,Dcm_ConfirmationStatusType status_u8);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * This structure contains the configuration of service \n
 * uint32 allowed_session_b32;                        Allowed sessions \n
 * uint32 allowed_security_b32;                      Allowed security levels\n
 * P2FUNC(boolean,TYPEDEF,moderule_fp)	(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA))\n
 * P2FUNC(void,TYPEDEF,adrServiceHandler_pfct) (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA));  Service handler\n
 * P2FUNC(void,TYPEDEF,adrServiceInit_pfct) (void);                  Init function of service\n
 * uint8 sid_u8;                                     Service id\n
 * boolean  subfunction_exist_b;                     Is sub function exist for this service ?\n
 * boolean servicelocator_b;                         Is Service existing in DSP?\n
 * boolean mainscheduler_b;                          Does this service use mainscheduler or cooperative scheduler?\n
 *                                                    TRUE : Main Scheduler FALSE : Cooperative scheduler \n
 * uint8 unused_param_u8;                            Unused variable\n
 * P2CONST(Dcm_Dsld_SubServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_subservice_table_pcs;  Reference subservice table\n
 * uint8 num_sf_u8;
 * Dcm_ConfirmationApiType Dcm_ConfirmationService;     Reference Service confirmation Apis
*/
typedef struct
{
    uint32 allowed_session_b32;                      /* Allowed sessions */
    uint32 allowed_security_b32;                     /* Allowed security levels */
#if((DCM_CFG_DSD_MODERULESERVICE_ENABLED!=DCM_CFG_OFF))
    P2FUNC(boolean,TYPEDEF,moderule_fp)	(P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA));
#endif
    /* Service handler */
    P2FUNC(Std_ReturnType,TYPEDEF,service_handler_fp) (VAR( Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));
    P2FUNC(void,TYPEDEF,Service_init_fp) (void);                 /* Init function of service */
    uint8 sid_u8;                                    /* Service id */
    boolean  subfunction_exist_b;                    /* Is sub function exist for this service ? */
    boolean servicelocator_b;                        /* Is Service existing in DSP? */
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    boolean mainscheduler_b;                      /* Does this service use mainscheduler or cooperative scheduler?
                                                        TRUE : Main Scheduler FALSE : Cooperative scheduler */
#else
    uint8 unused_param_u8;                           /* Unused variable */
#endif
    P2CONST(Dcm_Dsld_SubServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_subservice_table_pcs;  /* Reference subservice table */
    uint8 num_sf_u8;
    P2FUNC(Std_ReturnType,TYPEDEF,adrUserServiceModeRule_pfct) (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA),VAR(uint8,AUTOMATIC));
	 /*Confirmation Callbacks */
    Dcm_ConfirmationApiType Dcm_ConfirmationService;    /* Reference Service confirmation Apis */
} Dcm_Dsld_ServiceType;



/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * sid table structure\n
 * Member elements are\n
 * P2CONST(Dcm_Dsld_ServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_service_table_pcs: Reference service table \n
 * uint8 num_services_u8:                                                        No of services in table \n
 * uint8 nrc_sessnot_supported_u8:                                               NRC for service not supported in active session\n
 * uint8 cdtc_index_u8:                                                          Unused variable\n
 *
 */
typedef struct
{
    P2CONST(Dcm_Dsld_ServiceType,TYPEDEF,DCM_INTERN_CONST) ptr_service_table_pcs;     /* Reference service table */
    uint8 num_services_u8;                           /* No of services in table   */
    uint8 nrc_sessnot_supported_u8;                  /* NRC for service not supported in active session */
    uint8 cdtc_index_u8;                       /* Unused variable */
} Dcm_Dsld_sid_tableType;

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Structure for Connection to channel and Tx Pdu Mapping\n
 * Member elements are\n
 * uint8 protocol_num_u8       :Protocol number \n
 * PduIdType txpduid_num_u8    :TxPduId number \n
 * PduIdType roetype2_txpdu_u8 :ROE type2 tx pduid\n
 * PduIdType rdpitype2_txpdu_u8:RDPI type2 tx pduid\n
 * uint16 testaddr_u16         :Tester source address\n
 * uint8   channel_idx_u8      :Index of corresponding channelid\n
 *
 * */
typedef struct
{
    uint8 protocol_num_u8;                           /* Protocol number */
    PduIdType txpduid_num_u8;                        /* TxPduId number */
    PduIdType roetype2_txpdu_u8;                     /* ROE type2 tx pduid */
    PduIdType rdpitype2_txpdu_u8;                    /* RDPI type2 tx pduid */
    uint16 testaddr_u16;                             /* Tester source address */
 	uint8   channel_idx_u8;						 /* Index of corresponding channelid */
} Dcm_Dsld_connType;


/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Structure for RXPduId to tester source ID Mapping.This is used ROE implementation\n
 * Member elements are\n
 * uint16 testaddr_u16         :Tester source address\n
 * PduIdType   rxpduid_num_u8      :Index of corresponding channelid\n
 *
 * */
typedef struct
{
    PduIdType rxpduid_num_u8;                        /* RxPduId number */
    uint16 testsrcaddr_u16;                          /* Tester source address */
} Dcm_Dsld_RoeRxToTestSrcMappingType;



/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * This enum is defined in Boot software where ComM is not peresent\n
 * DCM_DSLD_NO_COM_MODE    :No COM mode in COM manager\n
 * DCM_DSLD_SILENT_COM_MODE:Silent COM mode in COM manager\n
 * DCM_DSLD_FULL_COM_MODE  :Full COM mode in COM manager\n
 */
typedef enum
{
    DCM_DSLD_NO_COM_MODE,                            /* No COM mode in COM manager */
    DCM_DSLD_SILENT_COM_MODE,                        /* Silent COM mode in COM manager */
    DCM_DSLD_FULL_COM_MODE                           /* Full COM mode in COM manager */
}Dcm_Dsld_commodeType;

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * This enum describes the Mediums that are supported by the ComMChannel \n
 */
typedef enum
{
    DCM_NONE=0,            /* no medium */
    DCM_CAN,               /* CAN       */
    DCM_KLINE,             /* KLINE     */
    DCM_FLEX,              /* FLEX      */
    DCM_LIN,               /* LIN       */
    DCM_IP,                /* IP        */
    DCM_INTERNAL           /* INTERNAL  */
}Dcm_DslDsd_MediumType_ten;

#endif

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * This enum describes the state of the active diagnostics \n
 * DCM_COMM_ACTIVE    :Active diagnostics is on and ComM_DCM_ActiveDiagnostic will be called\n
 * DCM_COMM_NOT_ACTIVE :Active diagnostics is off, and ComM_DCM_ActiveDiagnostic will not be called \n
 */
typedef enum
{
	DCM_COMM_ACTIVE,                            /* No COM mode in COM manager */
	DCM_COMM_NOT_ACTIVE
}Dcm_Dsld_activediagnostic_ten;
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Structure for storing ComM channel IDs and corresponding state\n
 * Member elements are\n
 * uint8   ComMChannelId          : Channel ID for the communication channel\n
 * Dcm_Dsld_commodeType ComMState :The communication state (FULL_COMM/SILENT_COMM/NO_COMM)of the channel which is identified by ComMChannelId.
 * Dcm_DslDsd_MediumType_ten  MediumId  :The MediumId of the configured Medium in the ComMChannel.This parameter exists only when rba_DiagAdapt is Enabled.
 * */
typedef struct
{
    uint8   ComMChannelId;
    Dcm_Dsld_commodeType ComMState;
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    Dcm_DslDsd_MediumType_ten  MediumId;
#endif
}Dcm_Dsld_ComMChannel;

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Structure containing timings for KWP type protocol\n
 * uint32 P2_max_u32:P2 max time in micro second \n
 * uint32 P3_max_u32:P3 max time in micro second
 */
typedef struct
{
    uint32 P2_max_u32;                               /* P2 max time in micro second */
    uint32 P3_max_u32;                               /* P3 max time in micro second */
} Dcm_Dsld_KwpTimerServerType;
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Enum to different type of timing set \n
 * DCM_CURRENT: Current timing set\n
 * DCM_LIMIT  : Limit timing set  \n
 *
 * */
typedef enum
{
    DCM_CURRENT,                                    /* Current timing set             */
    DCM_LIMIT                                      /* Limit timing set               */
}Dcm_TimerModeType;

#endif
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Final structre of DSL-DSD.It contains references to Rx table ,Tx table ,Connection table,protocol table,sid table,session look up table,security look up table.\n
 * P2CONST(uint8, TYPEDEF,  DCM_INTERN_CONST)ptr_rxtable_pca                        :Reference to Rx table array\n
 * P2CONST(PduIdType,TYPEDEF,DCM_INTERN_CONST)ptr_txtable_pca                       :Reference to Tx table array\n
 * P2CONST(Dcm_Dsld_connType,TYPEDEF,  DCM_INTERN_CONST)ptr_conntable_pcs           :Reference to Connection table structure\n
 * P2CONST(Dcm_Dsld_protocol_tableType,TYPEDEF,DCM_INTERN_CONST)protocol_table_pcs  :Reference to protocol table\n
 * P2CONST(Dcm_Dsld_sid_tableType,     TYPEDEF,  DCM_INTERN_CONST)sid_table_pcs     :Reference to sid table\n
 * P2CONST(uint8, TYPEDEF,  DCM_INTERN_CONST) session_lookup_table_pcau8            :Session look up table\n
 *  P2CONST(uint8 ,TYPEDEF, DCM_INTERN_CONST)security_lookup_table_pcau8            :Security look up table.
 */
typedef struct
{
    /* Reference to Rx table array */
    P2CONST(uint8,                      TYPEDEF,  DCM_INTERN_CONST)        ptr_rxtable_pca;
    /* Reference to Tx table array */
    P2CONST(PduIdType,                  TYPEDEF,  DCM_INTERN_CONST)        ptr_txtable_pca;
    /* Reference to Connection table structure */
    P2CONST(Dcm_Dsld_connType,          TYPEDEF,  DCM_INTERN_CONST)        ptr_conntable_pcs;
    /* Reference to protocol table */
    P2CONST(Dcm_Dsld_protocol_tableType,TYPEDEF,  DCM_INTERN_CONST)        protocol_table_pcs;
    /* Reference to sid table */
    P2CONST(Dcm_Dsld_sid_tableType,     TYPEDEF,  DCM_INTERN_CONST)        sid_table_pcs;
     /* Session look up table */
    P2CONST(uint8,                      TYPEDEF,  DCM_INTERN_CONST)        session_lookup_table_pcau8;
    /* Security look up table */
    P2CONST(uint8                      ,TYPEDEF,  DCM_INTERN_CONST)        security_lookup_table_pcau8;
} Dcm_Dsld_confType;


#if(((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)) && (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_Notification403_ptr) (
                                       VAR(uint8, AUTOMATIC) SID,
                                       P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) RequestData,
                                       VAR(uint16,AUTOMATIC) DataSize,
                                       VAR(uint8, AUTOMATIC) ReqType,
                                       VAR(uint16, AUTOMATIC) SourceAddress,
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                             );

typedef P2FUNC(Std_ReturnType,TYPEDEF,Dcm_Confirmation403_ptr) (
                                       VAR(uint8, AUTOMATIC) SID,
                                       VAR(uint8, AUTOMATIC) ReqType,
                                       VAR(uint16, AUTOMATIC) SourceAddress,
                                       VAR(Dcm_ConfirmationStatusType,AUTOMATIC) ConfirmationStatus
                                                             );
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SUPPNOT_NUM_PORTS !=0))
extern CONST (Dcm_Notification403_ptr,DCM_CONST) Dcm_Rte_SupplierNotification_a[DCM_CFG_SUPPNOT_NUM_PORTS];
extern CONST (Dcm_Confirmation403_ptr,DCM_CONST) Dcm_Rte_SupplierConfirmation_a[DCM_CFG_SUPPNOT_NUM_PORTS];
#endif
#if((DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF) && (DCM_CFG_MANUNOT_NUM_PORTS != 0))
extern CONST (Dcm_Notification403_ptr,DCM_CONST) Dcm_Rte_ManufacturerNotification_a[DCM_CFG_MANUNOT_NUM_PORTS];
extern CONST (Dcm_Confirmation403_ptr,DCM_CONST) Dcm_Rte_ManufacturerConfirmation_a[DCM_CFG_MANUNOT_NUM_PORTS];
#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/*
 ***************************************************************************************************
 *    Variables prototypes
 ***************************************************************************************************
 */
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * GLobal variable which will hold the current active configuration
 */
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8, DCM_VAR) Dcm_ActiveConfiguration_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Global variable which will hold the current active diagnostic state
 */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_Dsld_activediagnostic_ten, DCM_VAR) Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * final structre of DSL-DSD
 */
#define DCM_START_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_Dsld_confType, DCM_CONST) Dcm_Dsld_Conf_cs;
#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include "Dcm_Cfg_MemMap.h"
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_ConfigType,DCM_VAR, DCM_INTERN_CONST) Dcm_ActiveConfigSet_Ptr;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CONST_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(uint8, DCM_CONST)  Dcm_Dsld_KWPsupported_sessions_acu8[];
#define DCM_STOP_SEC_CONST_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_Dsld_KwpTimerServerType, DCM_CONST) Dcm_Dsld_default_timings_acs[];
extern CONST(Dcm_Dsld_KwpTimerServerType, DCM_CONST) Dcm_Dsld_Limit_timings_acs[];
#define DCM_STOP_SEC_CONST_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


/*
 ***************************************************************************************************
 *    Function prototypes (APIs of DCM)
 ***************************************************************************************************
 */



/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetVersionInfo : API to get the version info\n
 * param[out]  DcmVerInfoPtr : Pointer to where to store the version information of this module.\n
 * retval                    :        None\n
 */

#if (DCM_CFG_VERSION_INFO_API != DCM_CFG_OFF )

#define Dcm_GetVersionInfo(DcmVerInfoPtr)                       \
do                       /*Do while, to remove MISRA Warning 3458*/ \
{                                                               \
    (DcmVerInfoPtr)->vendorID = DCM_VENDOR_ID;                  \
    (DcmVerInfoPtr)->moduleID = DCM_MODULE_ID;                  \
    (DcmVerInfoPtr)->sw_major_version = DCM_SW_MAJOR_VERSION;   \
    (DcmVerInfoPtr)->sw_minor_version = DCM_SW_MINOR_VERSION;   \
    (DcmVerInfoPtr)->sw_patch_version = DCM_SW_PATCH_VERSION;   \
}                                                               \
while(0)                                                       \

#endif
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_Init : Initilazation of DCM module
 * @param           None
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_Init(void);

/**
* @ingroup DCMCORE_DSLDSD_AUTOSAR
* Dcm_SetNegResponse: If this function is called, a negative response will be sent instead of a positive response.
*  The negative response code is taken from the first call duplicate calls are allowed but the
*  errorCode transmitted is ignored.
*  The transmission of the negative response will be performed after calling Dcm_ProcessingDone.
*
* @param[in]     pMsgContext        Message-related information for one diagnostic protocol identifier.
* @param[in]     ErrorCode          Error code to be set. This error code will be taken as negative response code (NRC).
* @retval    None.
*/

extern FUNC(void,DCM_CODE) Dcm_SetNegResponse ( P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,
                                                VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) ErrorCode
                                              );
/**
 *  @ingroup DCMCORE_DSLDSD_AUTOSAR
 *  Dcm_ProcessingDone :When this function is called, a response will be sent based on the data contained in
 *                       pMsgContext. If Dcm_SetNegResponse was called before, a negative response is sent,
 *                       otherwise a positive response will be sent.
 *                       The application does not have to care about any timing requirement to process a request.
 * @param[in]           pMsgContext   Message-related information for one one diagnostic protocol identifier.
 * @retval              None
 *
 */
extern FUNC(void,DCM_CODE) Dcm_ProcessingDone (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext);

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_ResponseOnOneEvent : Function called by the ROE service whenever the event occurred.
 *                          This function is not reentrant function and it not called in other than
 *                          Dcm_MainFunction() task.
 *
 * @param[in]                Dcm_MsgType MsgPtr :    Pointer to buffer which containing the request
 * @param[in]                Dcm_MsgLenType MsgLen : Length of the request
 * @param[in]                PduIdType DcmRxPduId  : Rx pduid on which ROE request is received.
 *
 * @retval                   DCM_E_OK: ResponseOnOneEvent request is accepted by DCM ,
 *                           DCM_E_ROE_NOT_ACCEPTED: ResponseOnOneEvent request is not accepted by DCM
 */
extern FUNC(Dcm_StatusType,DCM_CODE) Dcm_ResponseOnOneEvent( CONST(Dcm_MsgType,AUTOMATIC) MsgPtr,
                                                      VAR(Dcm_MsgLenType, AUTOMATIC) MsgLen,
                                                      VAR(uint16,AUTOMATIC) TesterSrcAddr
                                                    );
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_RoeSendFinalResponse_u8 :This API will be called by the application to transmit the Final response
 *                           when the window timer expires in application.
 * @param [in]    Dcm_MsgType MsgPtr    :  Pointer to buffer which containg the response.
 * @param [in]    Dcm_MsgLenType MsgLen : Length of the response.
 * @param [in]    PduIdType DcmRxPduId  :Rx pduid on which ROE request is received
 * @retval        Std_ReturnType
 */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_RoeSendFinalResponse ( CONST(Dcm_MsgType,AUTOMATIC)    MsgPtr,
                                                                VAR(Dcm_MsgLenType,AUTOMATIC) MsgLen,
                                                                VAR(PduIdType,AUTOMATIC)      DcmRxPduId);
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_StartPagedProcessing : With this API, the application gives the complete response length to DCM
 *                          and starts PagedBuffer handling. Complete response length information
 *                          (in bytes) is given in pMsgContext-> resDataLen Callback functions are used
 *                          to provide paged buffer handling in DSP and RTE. More information can be found
 *                          in the sequence chart in chapter 9.3.6 Process Service Request with PagedBuffer.
 *
 * @param[in]       pMsgContext: message context table given by the service.
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_StartPagedProcessing (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_ProcessPage: Application requests transmission of filled page More information can be found
 *                  in the sequence chart in chapter 9.3.6 Process Service Request with PagedBuffer.
 * @param[in]       FilledPageLen  : Filled data length in current page.
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_ProcessPage(VAR(Dcm_MsgLenType, AUTOMATIC) FilledPageLen );
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2FUNC(void,TYPEDEF,Dcm_adrUpdatePage_pfct) (
                                                 VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr,
                                                 VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
                                               );
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_RestartP3timer : Function called by Kline TP to restart P3 timer after getting the first
 *                      byte of request
 * @param           None
 * @retval          None
 */
extern FUNC(void, DCM_CODE) Dcm_RestartP3timer(void);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_GetKwpTimingValues : API to get the different set of timings
 * @param           TimerMode (in): Mode of timing
 *                  TimerServerCurrent (out) : Pointer to structure where timings are written by DCM
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_GetKwpTimingValues(
                                     VAR(Dcm_TimerModeType,AUTOMATIC) TimerMode,
                                     P2VAR(Dcm_Dsld_KwpTimerServerType,AUTOMATIC,DCM_APPL_DATA) TimerServerCurrent
                                                 );
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_PrepareKwpTimingValues : API to validate the given set of timings
 * @param[in]       TimerServerNew (in): Pointer to structure which timings to be validated.
 *
 * @retval          DCM_E_OK: preparation successful,
 *                  DCM_E_TI_PREPARE_LIMITS: requested values are not within the defined limits
 */
extern FUNC(Dcm_StatusType,DCM_CODE) Dcm_PrepareKwpTimingValues(
                                        P2CONST(Dcm_Dsld_KwpTimerServerType,AUTOMATIC,DCM_APPL_CONST) TimerServerNew
                                                               );
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_SetKwpTimingValues : API to Set the given set of timings.
 * @param           None
 *
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_SetKwpTimingValues (void);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_SetKwpDefaultTimingValues : API to Set the default timings
 * @param           None
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_SetKwpDefaultTimingValues(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_SetP3MaxMonitoring : Function called by service to enable the P3 monitoring.
 *
 * @param[in]              active  TRUE  : P3 monitoring required.
 *                                 FALSE : P3 monitoring not required.
 * @retval                 None
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void, DCM_CODE) Dcm_SetP3MaxMonitoring (VAR(boolean,AUTOMATIC) active);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define Dcm_SetS3MaxMonitoring Dcm_SetP3MaxMonitoring
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_GetActiveServiceTable : API to get the service table id
 * @param[out]      ActiveServiceTable: Address of global variable Passed by the appl.
 * @retval          None
 */
extern FUNC(void,DCM_CODE) Dcm_GetActiveServiceTable (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ActiveServiceTable);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_Dsld_CheckSubFunction : Function to do subservice specific checks in DSD.
 *
 * @param [in]          Msgcontext_s       - Pointer to Message structure
 * @param [in]          service_pcs        - Pointer to the service configuration structure
 * @param [out]         ErrorCode_u8       - Variable to  store negative response code
 * @retval              None
 */
extern FUNC(void,DCM_CODE) Dcm_Dsld_CheckSubFunction(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) Msgcontext_s,
		                                             P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) service_pcs,
		                                             P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) ErrorCode_u8);
/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_GetActiveProtocolRxBufferSize : API to get the Active protocol RX buffer size.
 *
 * @param[out]      rxBufferLength : Address of global variable in which the buffer size should be written.
 * @retval          E_OK           : RX buffer size read sucessfully
 *                  E_NOT_OK       : RX Buffer size not read, possibly because of no active protocol
 */

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocolRxBufferSize
		                    (CONSTP2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA) rxBufferLength);

/**
 * @ingroup DCMCORE_DSLDSD_EXTENDED
 * Dcm_Dsld_ForceRespPend : API used to trigger wait pend response by the Service.
 * @param           None
 * @retval          Std_ReturnType :E_NOT_OK/E_OK
 */

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_ForceRespPend(void);
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_IsInfrastructureErrorPresent_b : API to check for infrastructure error
 * @param           dataInfrastrutureCode_u8 : Parameter to be checked for infrastructure Error
 * @retval          boolean
 * 					TRUE : if infrastructure error is present
 * 					FALSE : if infrastructure error is not present
 */

extern FUNC(boolean,DCM_CODE) Dcm_IsInfrastructureErrorPresent_b(VAR(uint8,AUTOMATIC) dataInfrastrutureCode_u8);

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
/**
 @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetMediumOfActiveConnection: API to get Medium information(ie.Can,Flexray..etc) available in the ComMChannel for the active connection.
 *                                  This is explicitly provided only for rba_DiagAdapt.This should be called by only rba_DiagAdapt when a new protocol request is triggered from the Tester.

 * @param[out]           ActiveMediumId  : Variable Passed by the rba_DiagAdapt to get active Medium information of ComMChannel for the active connection.
 *
 *
 *@retval                E_OK

 */

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetMediumOfActiveConnection(CONSTP2VAR(Dcm_DslDsd_MediumType_ten, AUTOMATIC, DCM_APPL_DATA) ActiveMediumId);
#endif

#if((DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF))
/**
* @ingroup DCMCORE_DSLDSD_AUTOSAR
*  Dcm_TriggerOnEvent: The call to this function allows to trigger an event linked to a ResponseOnEvent request.
*  On the function call, the DCM will execute the associated service. This function
*  shall be called only if the associated event has been activated through a xxx_ActivateEvent() call.
*
*  @param [in]                   : RoeEventId
*  @retval                       : E_OK
*/
/* MR12 RULE 8.5 VIOLATION:This is required for as per the design */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_TriggerOnEvent( VAR(uint8,AUTOMATIC) RoeEventId );
#endif

#if(DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED==DCM_CFG_OFF)
/*
 ***************************************************************************************************
 *    Function prototypes                                                                          */
/**************************************************************************************************/
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetActiveProtocol :API to get the active protocol id
 * @param[in]            :ActiveProtocol: Address of global variable Passed by the appl.
 * @retval               :E_OK:If the protocol is active
 * @retval               :E_NOT_OK:If the protocol is  not active
 */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetActiveProtocol(CONSTP2VAR(Dcm_ProtocolType, AUTOMATIC, RTE_APPL_DATA) ActiveProtocol);
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetSecurityLevel : API to get the active session id
 * @param[in]           :SesCtrlType: Address of global variable Passed by the appl.
 * @retval              : E_OK
 */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSesCtrlType(CONSTP2VAR(Dcm_SesCtrlType, AUTOMATIC, RTE_APPL_DATA) SesCtrlType);
/**
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_GetSecurityLevel : API to get the active security level
 * @param[in]           :SecLevel: Address of global variable Passed by the appl.
 * @retval              :E_OK
 */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_GetSecurityLevel(CONSTP2VAR(Dcm_SecLevelType, AUTOMATIC, RTE_APPL_DATA) SecLevel);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)

/**
* @ingroup DCMCORE_DSLDSD_AUTOSAR
*  Dcm_ResetToDefaultSession: The call to this function allows the application to reset the current session to
*  Default Session.
*  @param                   : None
*  @retval                  : E_OK - The request for resetting the session to default session is accepted.The session transition will be processed in the next Dcm main function
*                             E_NOT_OK - If Dcm is not free and processing some other request.The application has to call the service again in this case to Reset the session to Default
*/
/* MR12 RULE 8.5 VIOLATION:This is required for providing Dcm_ResetToDefaultSession declaration to rba_DiagAdapt RTE AR4.0 enabled configuration */
extern FUNC(Std_ReturnType, Dcm_CODE) Dcm_ResetToDefaultSession(void);
#endif
#endif

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_Dsld_ComMChannel, DCM_VAR) Dcm_active_commode_e[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Const Array for storing ComM channels configured in DCM.The same will be used for initialising  Dcm_active_commode_e[]*/
extern  CONST(uint8, DCM_CONST) Dcm_Dsld_ComMChannelId_acu8[DCM_NUM_COMM_CHANNEL];
#define DCM_STOP_SEC_CONST_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif   /* _DCMCORE_DSLDSD_PUB_H  */
