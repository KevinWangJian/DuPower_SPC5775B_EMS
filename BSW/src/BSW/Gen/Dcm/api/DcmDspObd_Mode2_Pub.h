

#ifndef DCMDSPOBD_MODE2_PUB_H
#define DCMDSPOBD_MODE2_PUB_H

/**
 ***************************************************************************************************
            OBD Mode 02
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE2_ENABLED != DCM_CFG_OFF)

/*supported PID configuration for OBD MODE 02 service */
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode2BitMask_Type:Sructure contains,\n
 * uint32 BitMask_u32;             Bit mask for the special PID \n
 * uint8  StartIndex_u8;           Starting index of PID array (Dcm_Dsp_PidArray_acs) for this special PID \n
 * uint8  NumPids_u8;              Number of PID configured for this special PID\n
 */
typedef struct
{
    uint32 BitMask_u32;                /* Bit mask for the special PID */
    uint8  StartIndex_u8;              /* Starting index of PID array (Dcm_Dsp_PidArray_acs) for this special PID */
    uint8  NumPids_u8;                 /* Number of PID configured for this special PID */
}Dcm_Dsp_Mode2BitMask_Type;
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode2Pid_Type:Structure contains PID related info.\n
 * uint8 Pid_Id_u8;                     PID number  \n
 * uint8 Num_DataSourcePids_u8;         Number of data bytes for each PID\n
 * uint16 DataSourcePid_ArrayIndex_u16; Array index to data associated with each PID\n
 * uint16 Pid_Size_u8;                  Total size of the PIDs \n
 */

typedef struct
{
    uint8 Pid_Id_u8;                    /* PID number      */
    uint8 Num_DataSourcePids_u8;        /* Number of data bytes for each PID */
    uint16 DataSourcePid_ArrayIndex_u16; /* Array index to data associated with each PID */
    uint16 Pid_Size_u8;                 /* Total size of the PIDs */
}Dcm_Dsp_Mode2Pid_Type;
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode2DataSourcePid_Type:Structure contains
 * uint16 Length_data_u8;                   Length of the data in bytes \n
 * uint16 Pos_data_u8;                      Position of data in bytes\n
 *
 */
typedef struct
{
    uint16 Length_data_u8;                    /* Length of the data in bytes */
    uint16 Pos_data_u8;                       /* Position of data in bytes */
}Dcm_Dsp_Mode2DataSourcePid_Type;

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Bitmask array for OBDmode2
 */

extern CONST(Dcm_Dsp_Mode2BitMask_Type,DCM_CONST) Dcm_Dsp_Mode2Bitmask_acs[8];
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * PID array  for OBD mode2
 */
extern CONST(Dcm_Dsp_Mode2Pid_Type,DCM_CONST) Dcm_Dsp_Mode2PidArray_acs[DCM_CFG_DSP_NUMPIDSUPP_MODE2];

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * data elements array configured for the PIDs for OBD MODE $02
 */
extern CONST(Dcm_Dsp_Mode2DataSourcePid_Type,DCM_CONST)  Dcm_Dsp_Mode2DataSourcePid_acs[DCM_CFG_DSP_NUMPIDDATA_MODE2];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* End of DCM_CFG_DSP_OBDMODE2_ENABLED */
#endif /* _DCMDSPOBD_MODE2_PUB_H  */
