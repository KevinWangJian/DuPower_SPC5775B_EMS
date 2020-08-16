

#ifndef DCMDSPOBD_MODE9_PUB_H
#define DCMDSPOBD_MODE9_PUB_H

/**
 ***************************************************************************************************
            OBD Mode 09
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE9_ENABLED != DCM_CFG_OFF)

typedef P2FUNC(Std_ReturnType,TYPEDEF,GetInfotypeValueData_pf1)(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) DataValueBuffer,P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) DataValueBufferSize);

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode9BitMask_t:            Supported INFOTYPE configuration for OBD MODE 09 service\n
 * Member elements:\n
 * uint32 BitMask_u32;                Bit mask for the special INFOTYPEs \n
 * uint8  StartIndex_u8;              Starting index of INFOTYPE array (Dcm_Dsp_VehInfoArray_acs) for this special INFOTYPE\n
 * uint8  NumInfotypes_u8;            Number of Infotypes configured for this special INFOTYPE\n
 *
 */
typedef struct
{
    uint32 BitMask_u32;                /* Bit mask for the special INFOTYPEs */
    uint8  StartIndex_u8;              /* Starting index of INFOTYPE array (Dcm_Dsp_VehInfoArray_acs)
                                                                          for this special INFOTYPE */
    uint8  NumInfotypes_u8;            /* Number of Infotypes configured for this special INFOTYPE */
}Dcm_Dsp_Mode9BitMask_t;

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode9_API_Type:Identifies the API type(whether it is DEM api/RTE api/user defined api)\n
 * OBD_MODE9_DEM_FNC: DEM api\n
 * OBD_MODE9_USE_FNC: RTE api\n
 * OBD_MODE9_RTE_FNC: User defined api\n
 */
typedef enum
{
    OBD_MODE9_DEM_FNC,
    OBD_MODE9_USE_FNC,
    OBD_MODE9_RTE_FNC
}Dcm_Dsp_Mode9_API_Type;

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_VehInfoData_t:Member elements \n
 * void* const GetInfotypeValueData_pf;            Function to get Infotype data \n
 * uint8  Infodatatype_size_u8;                    Length of the data \n
 * Dcm_Dsp_Mode9_API_Type InfoType_APIType_e;      Flag to determine if the API type Dem/user function/RTE\n
 */
typedef struct
{
    /* Function to get Infotype data */
    void* const GetInfotypeValueData_pf;
    uint8  Infodatatype_size_u8;                                /* Length of the data */
    Dcm_Dsp_Mode9_API_Type InfoType_APIType_e;     /* Flag to determine if the API type Dem/user function/RTE*/
}Dcm_Dsp_VehInfoData_t;


/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_VehInfo_t:INFOTYPE Configuration for OBD MODE 09 service\n
 * uint8 Infotype_u8;                 Infotype number \n
 * uint8 NumOfInfoData_u8;            Number of Veh Info data for the Veh Info\n
 * uint16 InfoDatatypeIndex_u16;     Index to VehInfo data array\n
 */
typedef struct
{
    /* Pointer to structure containing details of Infotype */
    uint8 Infotype_u8;               /* Infotype number */
    uint8 NumOfInfoData_u8;          /* Number of Veh Info data for the Veh Info */
    uint16 InfoDatatypeIndex_u16;    /* Index to VehInfo data array */
    boolean Is_NODI_Enabled_b ; /*responsible to fill NOfdataitems*/


}Dcm_Dsp_VehInfo_t;
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Bitmask array for OBDmode9
 */
extern CONST(Dcm_Dsp_Mode9BitMask_t,DCM_CONST) Dcm_Dsp_Mode9Bitmask_acs[8];
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * VehicleInfo array for OBDmode9
 */
extern CONST(Dcm_Dsp_VehInfo_t,     DCM_CONST) Dcm_Dsp_VehInfoArray_acs[DCM_CFG_DSP_NUMINFOTYPESUPP];
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * VehicleInfoData array for OBDmode9
 */
extern CONST(Dcm_Dsp_VehInfoData_t, DCM_CONST) Dcm_Dsp_VehInfoData_acs[DCM_CFG_DSP_NUMOFINFOTYPEDATA];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* End of DCM_CFG_DSP_OBDMODE9_ENABLED */



#endif /* _DCMDSPOBD_MODE9_PUB_H  */
