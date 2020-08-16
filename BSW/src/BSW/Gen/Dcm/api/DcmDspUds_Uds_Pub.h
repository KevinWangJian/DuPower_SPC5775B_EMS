

#ifndef DCMDSPUDS_UDS_PUB_H
#define DCMDSPUDS_UDS_PUB_H

#if (DCM_CFG_DSP_READDTCINFORMATION_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rdtc_Pub.h"
#endif

#if (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Pub.h"
#endif

#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Dsc_Pub.h"
#endif

#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_CC_Pub.h"
#endif

#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Cdtcs_Pub.h"
#endif

#if(DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Wmba_Pub.h"
#endif

#if(DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Rmba_Pub.h"
#endif

#if(DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Cdi_Pub.h"
#endif
/**
 **************************************************************************************************
 * @ingroup DCMCORE_DSLDSD_AUTOSAR
 * Dcm_DemTriggerOnDTCStatus :  This function is invoked by Dem on an interrupt context to inform DCM about the
 * status mask change for a particular DTC, this information can be used by DTC
 * to check if RDTC service has to be invoked or not based on the DTC if it was
 * setup by tester for ROE onchangeofDTC.
 *
 * @param [in]                 Dtc                 :   This is the DTC the change trigger is assigned
 * @param [in]                 DTCStatusOld        :   Old Status
 * @param [in]                 DTCStatusNew        :   New Status
 * @retval                     E_Ok      :   This value is always returned
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_DemTriggerOnDTCStatus( uint32 Dtc, uint8 DTCStatusOld, uint8 DTCStatusNew );

/**
 ***************************************************************************************************
            DID RELATED declarations
 ***************************************************************************************************
 */
#if((DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_DddiWriteOrClear_ten:-This is used to indicate to the application whether the WRITE is initiated or CLEAR of DDDI is initiated in NvM \n
 * DCM_DDDI_CLEAR\n
 * DCM_DDDI_WRITE\n
 */
typedef enum
{
    DCM_DDDI_CLEAR = 0,
    DCM_DDDI_CLEARALL,
    DCM_DDDI_WRITE
}Dcm_DddiWriteOrClear_ten;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_RestoreDddiReturn_ten:-Return type for restoring the DDDIDs during Dcm_Init \n
 * DCM_DDDI_READ_OK\n
 * DCM_DDDI_READ_NOT_OK\n
 * DCM_DDDI_READ_NOTAVAILABLE\n
 */
typedef enum
{
    DCM_DDDI_READ_OK = 0, /* in case the read is successful */
    DCM_DDDI_READ_NOT_OK, /* in case there is no access or error while reading */
    DCM_DDDI_READ_NOTAVAILABLE /* in case the configured DDDID is not available in NVRAM */
}Dcm_RestoreDddiReturn_ten;
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the memory records to DDDI.\n
 *  uint32 adrDddiMem_u32            memory address \n
 *  uint32 dataMemLength_u32         length of the memory record\n
 */

typedef struct
{
  uint32 adrDddiMem_u32;
  uint32 dataMemLength_u32;
} Dcm_DDDI_DEF_MEM_t;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the records to DDDI.\n
 * uint16 dataSrcDid_u16            DID to be added \n
 * uint16 idxOfDid_u16         Index of the DID to be added\n
 * uint8  posnInSourceDataRecord_u8   position in source data record\n
 * uint8  dataMemorySize_u8           memory size\n
 * boolean stCurrentDidRangeStatus_b  status of DID range\n
 */
typedef struct
{
  uint16 dataSrcDid_u16;
  uint16 idxOfDid_u16; /* index in the Dcm_DIDConfig (calculated at definition time on base of the DID in the request) */
  uint8  posnInSourceDataRecord_u8;
  uint8  dataMemorySize_u8;
  boolean stCurrentDidRangeStatus_b;
} Dcm_DddiDefId_tst;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the records to DDDI.\n
 * Dcm_DDDI_DEF_MEM_t dataMemAccess_st            structure for memory access \n
 * Dcm_DddiDefId_tst  dataIdAccess_st             structure for data access\n
 */
typedef union              /* Struct used instead of Union, to remove MISRA warning 750*/
{
  Dcm_DDDI_DEF_MEM_t dataMemAccess_st;
  Dcm_DddiDefId_tst  dataIdAccess_st;
} Dcm_DddiDef_tst;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the records to DDDI.\n
 * Dcm_DddiDef_tst dataDddi_st            structure for DDDI definition \n
 * uint8 dataDefinitionType_u8            definition type whether it is defined by ID or define by Address\n
 */
typedef struct
{
  Dcm_DddiDef_tst dataDddi_st;
  uint8 dataDefinitionType_u8;
} Dcm_DddiRecord_tst;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the records to DDDI.\n
 * uint16 nrCurrentlyDefinedRecords_u16             number of defined records per DDDID \n
 * uint16 posnCurrentPosInDataBuffer_u16            position in data buffer\n
 * uint16 idxCurrentRecord_u16
 */
typedef struct
{
  /* current state of configuration for the ID */
  uint16 nrCurrentlyDefinedRecords_u16;
  /* currently ID is being processed */
  /* current processing status */
  uint16 posnCurrentPosInDataBuffer_u16;
  uint16 idxCurrentRecord_u16;
} Dcm_DddiIdContext_tst;

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Used in Dcm_DcmDDDI service while adding the records to DDDI.\n
 * Dcm_DddiRecord_tst* addrRecord_pst   definition of the records in DDDID
 * Dcm_DddiIdContext_tst* dataDDDIRecordContext_pst   DDDID record context
 * Dcm_DddiIdContext_tst* dataPDIRecordContext_pst    PDI record context
 * uint16 dataDddId_u16                               value of the DDDID
 * uint16 nrMaxNumOfRecords_u16                       maximum number of records configured for DDDID
 */
typedef struct
{
  P2VAR(Dcm_DddiRecord_tst,TYPEDEF,DCM_INTERN_DATA) addrRecord_pst;
  P2VAR(Dcm_DddiIdContext_tst,TYPEDEF,DCM_INTERN_DATA) dataDDDIRecordContext_pst;
  P2VAR(Dcm_DddiIdContext_tst,TYPEDEF,DCM_INTERN_DATA) dataPDIRecordContext_pst;
  uint16 dataDddId_u16;
  uint16 nrMaxNumOfRecords_u16;
} Dcm_DddiMainConfig_tst;


#endif


#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)       ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)      ||  \
     (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)                      ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)||  \
     (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)        ||  \
     (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF))

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_Direction_t:-This is used check for the read/write/IO Control support\n
 * DCM_SUPPORT_READ,\n
 * DCM_SUPPORT_WRITE\n
 * DCM_SUPPORT_IOCONTROL\n
 */
typedef enum
{
    DCM_SUPPORT_READ,
    DCM_SUPPORT_WRITE,
    DCM_SUPPORT_IOCONTROL
} Dcm_Direction_t;

#endif
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)		||	\
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) 	||	\
	 (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) 					|| 	\
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_SupportRet_t:-This is used as the return value from the function Dcm_GetSupportIndex\n
 * DCM_SUPPORT_OK,                ID is supported\n
 * DCM_SUPPORT_SESSION_VIOLATED,  ID is not supported in the current session; negative response code is set to NegRespCode\n
 * DCM_SUPPORT_SECURITY_VIOLATED, ID is not supported in the current security level; negative response code is set to NegRespCode\n
 * DCM_SUPPORT_CONDITION_VIOLATED,ID is not supported as per configured callback function; negative response code is set to NegRespCode\n
 * DCM_SUPPORT_CONDITION_PENDING  checking needs more time. call again.\n
 */
typedef enum
{
    DCM_SUPPORT_OK,
    DCM_SUPPORT_SESSION_VIOLATED,
    DCM_SUPPORT_SECURITY_VIOLATED,
    DCM_SUPPORT_CONDITION_VIOLATED,
    DCM_SUPPORT_CONDITION_PENDING
} Dcm_SupportRet_t;



/* Did index Structure Definition, this structure provides information about the type of DID if it is a range DID or a normal DID
 * based of dataRange_b status, idxIndex_u16 contains the index of DID in Dcm_DIDConfig or Dcm_DIDRangeConfig based on the status of
 * dataRange_b boolean parameter, nrNumofSignalsRead_u16 parameter provides info to the application about number of signals read by the application */
typedef struct
{
	uint32 dataSignalLengthInfo_u32;
	uint16  nrNumofSignalsRead_u16;
	uint16  idxIndex_u16;
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
	uint16 dataRangeDid_16;
#endif
	Dcm_NegativeResponseCodeType dataNegRespCode_u8;
	boolean dataRange_b;
	boolean flgNvmReadPending_b;
	Dcm_OpStatusType dataopstatus_b;
#if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
	boolean flagPageddid_b;		/*If this flag is set to true it indicates the DID is a paged DID or special DID, if false it indicates a normal did without paged functions*/
#endif
} Dcm_DIDIndexType_tst;

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetIndexOfDID function is used to determine the index of did/range Did (which is an IN parameter), this function will write
 * the value of index of DID in  Dcm_DIDConfig structure array in case of normal DID /Dcm_DIDRangeConfig_cast structure array in case
 * of range DID on  to idxIndex_u16 which is an element in structure  idxDidIndexType_st(which is an out parameter).
 * The "dataRange_b" element of structure-idxDidIndexType_st is set to
 * FALSE in this function if DID is found in the DCM_DIDConfig structure array.
 *
 * @param[in]               did   : The did for which the index is requested\n
 * @param[out]              idxDidIndexType_st : Structure with index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on the status of dataRange_b
 * @see                     Dcm_Dsp_GetIndexOfDDDI
 *
 */
extern FUNC (Std_ReturnType,DCM_CODE) Dcm_GetIndexOfDID (
														VAR (uint16,AUTOMATIC) did,
														P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
														 );

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetSupportOfIndex:Calculate if the ID at position index in the Dcm_DIDConfig is supported at this point in time or not.\n
 *
 * @param [in]            index      : index in Dcm_DIDConfig\n
 * @param [in]            direction  : check for read or write support: DCM_SUPPORT_READ,DCM_SUPPORT_WRITE\n
 * @param [out]           NegRespCode: Pointer to a Byte in which to store a negative Response code in case of detection of an error in the request.\n
 * @param [in]            rangestatus:Status to indicate if the Did is configured as a range Did
 * @retval				 DCM_SUPPORT_OK,                ID is supported\n
 *                       DCM_SUPPORT_SESSION_VIOLATED,  ID is not supported in the current session; negative response code is set to NegRespCode\n
 *                       DCM_SUPPORT_SECURITY_VIOLATED, ID is not supported in the current security level; negative response code is set to NegRespCode\n
 *                       DCM_SUPPORT_CONDITION_VIOLATED,ID is not supported as per configured callback function; negative response code is set to NegRespCode\n
 *                       DCM_SUPPORT_CONDITION_PENDING  checking needs more time. call again.
 */
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)				||		\
	 (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)				||		\
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern FUNC (Dcm_SupportRet_t,DCM_CODE) Dcm_GetSupportOfIndex( P2VAR   (Dcm_DIDIndexType_tst , AUTOMATIC,DCM_INTERN_DATA) 	idxDidIndexType_st,
															   VAR (Dcm_Direction_t,AUTOMATIC) 		direction,
															   P2VAR (Dcm_NegativeResponseCodeType, AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);

#endif

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetDIDRangeStatus:Calculations to check if the DID is in the DID Range limits
 * @param[in]       did: The did for which the length is requested
 * @param[out]      idxDidIndexType_st : Index of the requested DID in Dcm_DIDRangeConfig structure if it is a range DID.
 *
 * @retval
 *             E_OK: DID range limit check done successfully
 *             E_NOT_OK: DID not in the range DID limit
 */
#if ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)          ||  \
     (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)         ||  \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetDIDRangeStatus (
                                                            VAR (uint16,AUTOMATIC) did,
                                                            P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st
                                                            );
#endif
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 *
 *  Dcm_GetLengthOfDIDIndex:
 *  Calculate the length of the ID at position index in Dcm_DIDConfig
 *
 * @param [in]      idxDidIndexType_st	: 	index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on the dataRange_b parameter
 * @param [in]       did 					: 	DID in the request
 * @param [out]     *length				: 	length calculated in case E_OK is returned
 * @retval     E_OK: calculation finished successfully
 *             E_NOT_OK: error in configuration or in the called length calculating function
 * @see    Dcm_GetLengthOfDID_u8
 *
 **************************************************************************************************
 */
extern 	FUNC (Std_ReturnType,DCM_CODE) Dcm_GetLengthOfDIDIndex(VAR   (Dcm_DIDIndexType_tst ,AUTOMATIC) 	idxDidIndexType_st,
        													   P2VAR (uint32,AUTOMATIC,DCM_INTERN_DATA)	length,
        													   VAR   (uint16,AUTOMATIC) did);

#if((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)|| (DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF))
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 *
 * Dcm_GetActiveDid:
 * This API will update the normal DID currently being processed by Dsp supported RDBI/WDBI/IOCBI services .The API can be polled from  Read/CondionCheckRead/ReadDataLength functions
 * during RDBI request processing, from Write function during WDBI request processing and from FreezeCurrentState/ResetToDefault/ShortTermAdjustment/ReturnControlToEcu/Read
 * function during IOCBI request processing.The API can be used to identify the appropriate data requested by the application.If the API is called from anywhere outside
 * the mentioned  application APIs while processing the requested services, the DID value may not be correct.In case the DID currently under process is a normal DID,
 * E_OK is returned and a valid value is filled in the parameter passed.In case the DID currently under process is a range DID, E_NOT_OK is returned.
 *
 * @param [out]     dataDid_u16: Pointer to a variable for updating of the DID under processing. The DID value returned is valid only if return value is E_OK.\n
 * @retval          E_OK : The DID under processing is a normal DID.The parameter dataDid_u16 contains valid DID in this case \n
 *                  E_NOT_OK: The DID under processing is a range DID. The parameter dataDid_u16 contains invalid data in this case. \n
 * @see
 *
 **************************************************************************************************
 */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveDid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataDid_u16);

#endif
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetDIDData:The function is used to read the DID data of the requested DID by calling the corresponding\n
 * configured function for reading the data. The DID value is not written in the buffer.
 *
 * @param[inout]           idxDidIndexType_st         : index in Dcm_DIDConfig or Dcm_DIDRangeConfig based on dataRange_b status
 * @param[out]          targetBuffer      			  : Pointer to the buffer where the data is to be written\n
 *
 * @retval              Std_ReturnType : E_NOT_OK       : DID data was not read successfully
 *                                       E_OK           : DID data is read successfully\n
 *					                     DCM_E_PENDING  : More time is required to read the data\n
 *
 */
#if ((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF)							||		    \
	 (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)	||		    \
			 (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF) ||   \
			 (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

extern FUNC (Std_ReturnType,DCM_CODE) Dcm_GetDIDData (P2VAR (Dcm_DIDIndexType_tst,AUTOMATIC,DCM_INTERN_DATA ) idxDidIndexType_st,
 	  	   	   	   	   	   	   	   	   	   	   	   	  P2VAR (uint8, AUTOMATIC,DCM_INTERN_DATA) targetBuffer);
#endif

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_GetActiveRid :
 * API to provide the current active RID.
 * This API has to be called from the application callbacks of Start, Stop and Req.Results routine configured for the project.
 * Example scenarios:
 * 	a) This API has to be called by the application
 * 		a.1)during Start, Stop and Request Results operations for the normal tester request
 * 		a.2)during canceling the pending operations either Start or Stop or Request Results due to CANCEL operation triggered by Dcm by setting the Opstatus to DCM_CANCEL in the RC Ini function.
 * 		a.3)during the stop of the routines due to session transitions (either due to protocol start/stop or session time out/change).
 * By "Active RID", it means that the active RID index under processing and not the RIDs of already started routines.
 *
 * \param           dataRid_u16    Buffer to get the current active RID

 *
 * \retval          Std_ReturnType 	E_OK : The parameter dataRid_u16 contains valid RID value in this case.
 * 									E_NOT_OK : The parameter dataRid_u16 contains invalid data in case none of the Routine is under processing.
 * \seealso
 *
 ******************************************************************************************************************
 */


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#if(DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveRid(P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA) dataRid_u16);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_ReadMemoryRet_t:\n
 * DCM_READ_OK,\n
 * DCM_READ_FAILED,\n
 * DCM_READ_PENDING\n
 * DCM_READ_FORCE_RCRRP
 */
#if ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) || \
     (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))
typedef enum
{
    DCM_READ_OK,
    DCM_READ_FAILED,
    DCM_READ_PENDING,
    DCM_READ_FORCE_RCRRP,
    DCM_READ_NOT_AVAILABLE
} Dcm_ReadMemoryRet_t;

typedef Dcm_ReadMemoryRet_t Dcm_ReturnReadMemoryType;
#endif

#if((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * Dcm_WriteMemoryRet_t:/n
 * DCM_WRITE_OK,\n
 * DCM_WRITE_FAILED,\n
 * DCM_WRITE_PENDING,\n
 * DCM_WRITE_FORCE_RCRRP
 */
typedef enum
{
    DCM_WRITE_OK,
    DCM_WRITE_FAILED,
    DCM_WRITE_PENDING,
    DCM_WRITE_FORCE_RCRRP,
    DCM_WRITE_NOT_AVAILABLE
} Dcm_WriteMemoryRet_t;

typedef Dcm_WriteMemoryRet_t Dcm_ReturnWriteMemoryType;
#endif

#if(DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF)
typedef enum
{
    DCM_UPLOAD = 0,
    DCM_DOWNLOAD,
    DCM_TRANSFER_NOT_AVAILABLE
} Dcm_TrasferDirection_en;
#endif
#endif /* _DCMDSPUDS_UDS_PUB_H  */
