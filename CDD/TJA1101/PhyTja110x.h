/*
 * PhyTja110x.h
 *
 *  Created on:
 *      Author: admin
 */

#ifndef USERS_PHYTJA110X_H_
#define USERS_PHYTJA110X_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "Mcal.h"
#include "typedefs.h"
#include "Std_Types.h"
#include "Reg_eSys.h"
#include "StdRegMacros.h"
#include "Dio_Cfg.h"
#include "Dio.h"


#define  ETH_100BASET1_TRANSMIT_TEST_ENABLE		(0U)

#define  PHY_TJA1101_ADDRESS	 				(0x06U)

#define  PHY_TJA1101_ID1						(0x0180U)
#define  PHY_TJA1101_ID2						(0x0037U)
#define  PHY_TJA1101_TYPE_NO					(0x0010U)
#define  PHY_TJA1101_REVISION_NO				(0x0001U)


#define  PHY_TJA1101_ENABLE()					Dio_WriteChannel(DioConf_DioChannel_TJA1101_EN, STD_HIGH)
#define  PHY_TJA1101_DISABLE()					Dio_WriteChannel(DioConf_DioChannel_TJA1101_EN, STD_LOW)

#define  PHY_TJA1101_RESET_LOW()				Dio_WriteChannel(DioConf_DioChannel_TJA1101_RESET, STD_LOW)
#define  PHY_TJA1101_RESET_HIGH()				Dio_WriteChannel(DioConf_DioChannel_TJA1101_RESET, STD_HIGH)


typedef struct
{
	uint16 ID1;
	uint16 ID2;
	uint16 TYPE_NO;
	uint16 VISION_NO;
}PHY_TJA1101_ID_Info_t;


typedef enum 
{
	TJA1101_Configure_As_Slaver = 0,
	TJA1101_Configure_As_Master = 1
}PHY_TJA1101_MasterSlaver_Select_t;


typedef enum
{
    TJA1101_Init_Failed = 0,
    TJA1101_Init_Success = 1
}PHY_TJA1101_InitStatus_t;


typedef enum
{
	TJA1101_Linkup_Failed = 0,
	TJA1101_Linkup_Success = 1
}PHY_TJA1101_LinkupStatus_t;


typedef enum
{
	TJA1101_Iddle 		 = 0,
	TJA1101_Initializing = 1,
	TJA1101_Configured 	 = 2,
	TJA1101_Offline 	 = 3,
	TJA1101_Active 		 = 4,
	TJA1101_Isolate 	 = 5,
	TJA1101_CableTest 	 = 6,
	TJA1101_TestMode 	 = 7
}PHY_TJA1101_State_t;


typedef enum
{
	SQI_WRS_CLASS_A = 0,		/* Unstable link */
	SQI_CLASS_A     = 1,		/* Unstable link */
	SQI_CLASS_B		= 2,		/* Unstable link */
	SQI_CLASS_C		= 3,		/* Good link */
	SQI_CLASS_D		= 4,		/* Good link, bit error rate < 1e-10 */
	SQI_CLASS_E		= 5,		/* Good link */
	SQI_CLASS_F		= 6,		/* Very Good link */
	SQI_CLASS_G		= 7			/* Very Good link */
}PHY_TJA1101_SQI_Level_t;


typedef enum
{
	TJA1101_10Mbps   = 0,
	TJA1101_100Mbps  = 1,
	TJA1101_1000Mbps = 2
}PHY_TJA1101_SPEED_Select_t;


typedef enum
{
	NO_SHORT_CIRCUIT_DETECTED = 0,
	SHORT_CIRCUIT_DETECTED = 1
}PHY_TJA1101_SHORT_CIRCUIT_t;


typedef enum
{
	NO_OPEN_CIRCUIT_DETECTED = 0,
	OPEN_CIRCUIT_DETECTED = 1
}PHY_TJA1101_OPEN_CIRCUIT_t;


typedef struct 
{
	uint8_t 							PhyAddress;
	PHY_TJA1101_ID_Info_t				PhyIdInfo;
	PHY_TJA1101_MasterSlaver_Select_t 	PhyMode;
    PHY_TJA1101_InitStatus_t 			InitStatus;
    PHY_TJA1101_SPEED_Select_t 			PhySpeed;
    PHY_TJA1101_LinkupStatus_t 			LinkStatus;
    PHY_TJA1101_State_t    				PhyState;
    PHY_TJA1101_SQI_Level_t    			PhySQILevel;
    PHY_TJA1101_SHORT_CIRCUIT_t 		PhyShortCircuitStatus;
    PHY_TJA1101_OPEN_CIRCUIT_t  		PhyOpenCircuitStatus;
}PHY_TJA1101_ATTRIBUTE_t;


extern PHY_TJA1101_ATTRIBUTE_t TJA1101_AttributeInfo;


int PHY_TJA1101_Init(void);
int PHY_TJA1101_MainFunction(void);


#ifdef __cplusplus
}
#endif
#endif /* USERS_PHYTJA110X_H_ */
