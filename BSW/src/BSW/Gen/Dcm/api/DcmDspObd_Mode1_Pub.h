

#ifndef DCMDSPOBD_MODE1_PUB_H
#define DCMDSPOBD_MODE1_PUB_H

/**
 ***************************************************************************************************
            OBD Mode 01
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Read Data Function Pointer Types\n
 * When UsePort is USE_DATA_SYNC_FNC or DATA_SYNC_CLIENT_SERVER or USE_DATA_SENDER_RECEIVER \n
 */
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue1_pf)(P2VAR(uint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue2_pf)(P2VAR(uint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue3_pf)(P2VAR(uint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue4_pf)(P2VAR(sint8,  AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue5_pf)(P2VAR(sint16, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue6_pf)(P2VAR(sint32, AUTOMATIC,DCM_INTERN_DATA) Data);
typedef P2FUNC(Std_ReturnType,TYPEDEF,GetPIDvalue7_pf)(P2VAR(boolean, AUTOMATIC,DCM_INTERN_DATA) Data);

/**
 * @ingroup DCMDSP_OBD_AUTOSAR
 * DcmDspPidDataUsePort:This can have the values\n
 * OBD_USE_DATA_SENDER_RECEIVER,
 * OBD_USE_DATA_SYNCH_CLIENT_SERVER,
 * OBD_USE_DATA_SYNCH_FNC
 */
typedef enum
{
	OBD_USE_DATA_SENDER_RECEIVER,
	OBD_USE_DATA_SYNCH_CLIENT_SERVER,
	OBD_USE_DATA_SYNCH_FNC
}DcmDspPidDataUsePort;
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * supported PID configuration for OBD MODE 01 service\n
 * uint32 BitMask_u32;                  Bit mask for the special PID\n
 * uint8  StartIndex_u8;                Starting index of PID array (Dcm_Dsp_PidArray_acs) for this special PID \n
 * uint8  NumPids_u8;                   Number of PID configured for this special PID\n
 */
typedef struct
{
    uint32 BitMask_u32;                  /* Bit mask for the special PID */
    uint8  StartIndex_u8;                /* Starting index of PID array (Dcm_Dsp_PidArray_acs) for this special PID */
    uint8  NumPids_u8;                   /* Number of PID configured for this special PID */
}Dcm_Dsp_Mode1BitMask_Type;
/**
 * @ingroup DCMDSP_OBD_EXTENDED
* PID Configuration (PID which reports data value) for OBD MODE 01 service\n
* uint8  Pid_Id_u8;                     PID number\n
* uint8  Num_DataSourcePids_u8;         Number of data bytes for each PID \n
* uint16 DataSourcePid_ArrayIndex_u16;  Array index to data associated with each PID \n
* Include the config_mask only if DCM_CFG_POSTBUILD_SUPPORT is enabled\n
* uint8 Config_Mask;                   Config mask indicating PID is active which configuration\n
* uint16 Pid_Size_u8;                  Total size of the PIDs
*/
typedef struct
{
    uint8 Pid_Id_u8;                     /* PID number      */
    uint8 Num_DataSourcePids_u8;         /* Number of data bytes for each PID */
    uint16 DataSourcePid_ArrayIndex_u16; /* Array index to data associated with each PID */
	/* Include the config_mask only if DCM_CFG_POSTBUILD_SUPPORT is enabled*/
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF)
    uint8 Config_Mask;                   /*Config mask indicating PID is active which configuration*/
#endif
    uint16 Pid_Size_u8;                  /* Total size of the PIDs */
}Dcm_Dsp_Mode1Pid_Type;

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode1SupportInfo_Type has member elements,\n
 * uint8 SupportInfoLen_u8;             Length of Support Information in bytes \n
 * uint8 SupportInfoPos_u8;            Position of Support Information in bytes\n
 * */
typedef struct
{
	uint8 SupportInfoLen_u8;             /* Length of Support Information in bytes */
	uint8 SupportInfoPos_u8;             /* Position of Support Information in bytes */
}Dcm_Dsp_Mode1SupportInfo_Type;


/**
 * @ingroup DCMDSP_OBD_EXTENDED
 *   void* const GetPIDvalue_pf;           Function to get PID data \n
 *   P2CONST(Dcm_Dsp_Mode1SupportInfo_Type,TYPEDEF,DCM_INTERN_CONST) ptr_supportinfo_pcs;  Reference to support info table \n
 *   DcmDspPidDataUsePort PidUsePort;      Use port type \n
 *   uint16 Length_data_u16;               Length of the data in bits \n
 *   uint16 Pos_data_u16;                  Position of data in bits \n
 *   uint8 dataType_u8;                    DataType of the signal \n
 *   uint8 dataEndianness_u8;             Data endianness\n
 *   uint8 SupportInfoBit_u8;             Support Info bit\n
 * */



typedef struct
{
    void* const GetPIDvalue_pf;          /* Function to get PID data */
    P2CONST(Dcm_Dsp_Mode1SupportInfo_Type,TYPEDEF,DCM_INTERN_CONST) ptr_supportinfo_pcs;  /* Reference to support info table */
    DcmDspPidDataUsePort PidUsePort;     /* Use port type */
    uint16 Length_data_u16;              /* Length of the data in bits */
    uint16 Pos_data_u16;                 /* Position of data in bits */
    uint8 dataType_u8;                   /* DataType of the signal */
    uint8 dataEndianness_u8;             /*Data endianness*/
    uint8 SupportInfoBit_u8;             /* Support Info bit */
}Dcm_Dsp_Mode1DataSourcePid_Type;
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Bitmask array for OBDmode1
 */
extern CONST(Dcm_Dsp_Mode1BitMask_Type,DCM_CONST) Dcm_Dsp_Mode1Bitmask_acs[8];
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * PID array  for OBD mode1
 */
extern CONST(Dcm_Dsp_Mode1Pid_Type,DCM_CONST) Dcm_Dsp_Mode1PidArray_acs[DCM_CFG_DSP_NUMPIDSUPP_MODE1];
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * data elements array configured for the PIDs for OBD MODE $01
 */
extern CONST(Dcm_Dsp_Mode1DataSourcePid_Type,DCM_CONST) Dcm_Dsp_Mode1DataSourcePid_acs[DCM_CFG_DSP_NUMPIDDATA_MODE1];
#if (DCM_CFG_DSP_NUMSUPPINFO_MODE1 != 0)
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Array for support information for the PIDs for MODE $01
 *
 * */
extern CONST(Dcm_Dsp_Mode1SupportInfo_Type,DCM_CONST) Dcm_Dsp_Mode1SupportInfo_acs[DCM_CFG_DSP_NUMSUPPINFO_MODE1];

#endif
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* End of DCM_CFG_DSP_OBDMODE1_ENABLED */
#endif /* _DCMDSPOBD_MODE1_PUB_H  */
