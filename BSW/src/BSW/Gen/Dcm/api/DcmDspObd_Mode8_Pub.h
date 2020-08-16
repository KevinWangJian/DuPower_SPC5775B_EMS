

#ifndef DCMDSPOBD_MODE8_PUB_H
#define DCMDSPOBD_MODE8_PUB_H

/* When UsePort is configured TRUE i.e. RTE is enabled */
typedef  P2FUNC(Std_ReturnType,TYPEDEF,RequestControl1_pf)(
                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Outdata_pu8,
                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) Indata_pu8
                     );
typedef  P2FUNC(Std_ReturnType,TYPEDEF,RequestControl2_pf)(
                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Outdata_pu8,
                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) Indata_pu8
                     );


/**
 ***************************************************************************************************
            OBD Mode 08
 ***************************************************************************************************
 */
#if(DCM_CFG_DSP_OBDMODE8_ENABLED != DCM_CFG_OFF)

/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode8BitMask_Type:supported TID configuration for OBD MODE 08 service\n
 * Memeber elements:\n
 * uint32 BitMask_u32;             Bit mask for the special TID \n
 * uint8  StartIndex_u8;           Starting index of TID array (Dcm_Dsp_Mode8TidArray_acs) for this special TID\n
 * uint8  NumTids_u8;              Number of TID configured for this special TID\n
 */
typedef struct
{
    uint32 BitMask_u32;            /* Bit mask for the special TID */
    uint8  StartIndex_u8;          /* Starting index of TID array (Dcm_Dsp_Mode8TidArray_acs) for this special TID */
    uint8  NumTids_u8;             /* Number of TID configured for this special TID */
}Dcm_Dsp_Mode8BitMask_Type;


/* TID Configuration (TID to trigger turn ON/OFF the system/test/component) for OBD MODE 08 service */
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Dcm_Dsp_Mode8Tid_Type:TID Configuration (TID to trigger turn ON/OFF the system/test/component) for OBD MODE 08 service\n
 * Member elements:\n
 * void* const adrRequestControl_cpv  function pointer to turn on/off the test/system/component \n
 * uint8 Tid_Id_u8;                   TID number of 1byte\n
 * uint8 InBuffer_u8;                 number of data bytes in Inbuffer\n
 * uint8 OutBuffer_u8;                number of data bytes in OutBuffer\n
 * boolean UsePort_b;                 Useport is enabled/disabled\n
 */
typedef struct
{
    void* const adrRequestControl_cpv; /*function to turn on/off the test/system/component */
    uint8 Tid_Id_u8;                   /* TID number of 1byte   */
    uint8 InBuffer_u8;                 /*number of data bytes in Inbuffer */
    uint8 OutBuffer_u8;                /*number of data bytes in OutBuffer */
    boolean UsePort_b;                 /* Useport is enabled/disabled */
}Dcm_Dsp_Mode8Tid_Type;

#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCMDSP_OBD_EXTENDED
 * Bitmask array for OBD mode8
 */
extern CONST(Dcm_Dsp_Mode8BitMask_Type,DCM_CONST) Dcm_Dsp_Mode8Bitmask_acs[8];
/**
 *@ingroup DCMDSP_OBD_EXTENDED
 * TID array for OBD mode8
 */
extern CONST(Dcm_Dsp_Mode8Tid_Type,DCM_CONST) Dcm_Dsp_Mode8TidArray_acs[DCM_CFG_DSP_MODE8NUMTIDSUPP];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif  /* End of DCM_CFG_DSP_OBDMODE8_ENABLED */

#endif /* _DCMDSPOBD_MODE8_PUB_H  */
