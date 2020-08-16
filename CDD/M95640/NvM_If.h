/************************************************************************************
 *
 * Copyright (c) DU-POWER New Energy Technical Co., Ltd - All rights reserved 
 *
 * file name:    NvM_If.h
 *
 * description:  
 *  NvM interface
 * 
 *
 * revision history:
 *
 * Date        Author           Description
 * 2018/9/18	   Wu Jun           initial version
 *
*************************************************************************************/
#ifndef NVM_IF_H
#define NVM_IF_H

/************************************************************************************
 * INCLUDES
*************************************************************************************/
#include "typedefs.h"
#include "Platform_Types.h"
/************************************************************************************
*  Macro Definitions
*************************************************************************************/


/************************************************************************************
 * TYPE DEFINITIONS
*************************************************************************************/
typedef struct
{
    uint16_t ShutdownTimeYear;
    uint8_t ShutdownTimeMonth;
    uint8_t ShutdownTimeDay;
    uint8_t ShutdownTimeHour;
    uint8_t ShutdownTimeMinute;
    uint8_t ShutdownTimeSec;

	float MaxCellSOC;
	float MinCellSOC;
	float DisplaySOC;
	float MaxCellVolt;
	float MinCellVolt;

    uint16_t HVIsoValue_kohm;

    float TotalChrgCap_Ah;
    float TotalChrgPwr_kWh;
    float TotalDischrgCap_Ah;
    float TotalDischrgPwr_kWh;

    uint8_t NVMPreChrgFail_numb;
	uint8_t ACChrgCloseFltValue_numb;
    uint32_t PosCtlLoadOpenCnt_numb;
    float PosCtlLoadOpenCurr_A;
    uint32_t NegCtlLoadOpenCnt_numb;
    float NegCtlLoadOpenCurr_A;
    uint32_t DCChrgCtlLoadOpenCnt_numb;
    float DCChrgCtlLoadOpenCurr_A;
    uint32_t ACChrgCtlLoadOpenCnt_numb;
    float ACChrgCtlLoadOpenCurr_A;
    float MaxPackCurr_A;
	
//POS
    float POS_GcBSW_PackVolt_V;
    float POS_GcBSW_PackCurr_A;
    float POS_GcBSW_PreChrgVolt_V;
//NEG
    float NEG_GcBSW_PackVolt_V;
    float NEG_GcBSW_PackCurr_A;
    float NEG_GcBSW_PreChrgVolt_V;
//PRE
    float PRE_GcBSW_PackVolt_V;
    float PRE_GcBSW_PackCurr_A;
    float PRE_GcBSW_PreChrgVolt_V;
	/* add element here */

	unsigned short CRC;		// not use now 
}E2DataAsw_St;  /* Do not change the struct name */

extern E2DataAsw_St _st_NvmImage;
/**
* @brief		E2DataAsw_St init status
* @details	Used to differentiate if E2DataAsw_St is during init, initialized succeed or fail   
*
*/


/************************************************************************************
 * DATA DECLARATIONS
*************************************************************************************/

/************************************************************************************
 * FUNCTION PROTOTYPES
*************************************************************************************/

extern boolean DataE2_E2DataAsw_SetData(const E2DataAsw_St* vp_inputSrc, uint32_t size);
extern boolean DataE2_E2DataAsw_GetData(E2DataAsw_St* vp_outputSrc, uint32_t size);


 #endif      /* NVM_IF_H */ 

