/*******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2006-2012 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
********************************************************************************
*
* $File Name:       FS65xx.h$
* @file             FS65xx.h
*
* $Date:            Jul-31-2014$
* @date             Jul-31-2014
*
* $Version:         1.5$
* @version          1.5
*
* Description:      PowerSBC driver header file
* @brief            PowerSBC driver header file
*
* --------------------------------------------------------------------
* $Name:  $
*******************************************************************************/
/****************************************************************************//*!
*
*  @mainpage FS65xx driver for MPC5744P
*
*  @section Intro Introduction
*
*	This package contains PowerSBC driver allowing to control MC33FS65xx and MC33FS45xx.
*	FS65xx driver was created as a demo code to enable our customers
*	to start their development quickly and to demonstrate functionality of the PowerSBC
*	chip. Presented driver is not AUTOSAR nor ISO26262 compliant. This driver package
*	needs so-called MPC5744P Basic software drivers, which present the basic layer
*	for this application.
*
*  The key features of this package are the following:
*  - Offer driver allowing to write and read into and from FS65xx registers
*  - Switch FS65xx modes (low power, normal etc.)
*  - Treat all interrupt sources (events)
*  - Supervise voltages presented in the FS65xx interface
*
*  For more information about the functions and configuration items see these documents:
*
*******************************************************************************
*
* @attention
*
*******************************************************************************/
/*==================================================================================================
*   Project              : FS65xx
*   Platform             : MCU agnostic
*   Dependencies         :
*   All Rights Reserved.
==================================================================================================*/

/*==================================================================================================
Revision History:
                             Modification     Function
Author (core ID)              Date D/M/Y       Name		  		Description of Changes
B35993, BRNY001				10/07/2015 	   		  		Driver created
BRNY001						18/08/2015       			AMUX defines
BRNY001						30/11/2016	   				Corrected register definition for V1.1 (INIT_FAULT, INIT_SUPERVISOR)
BRNY001						04/10/2017					Bug correction in the union LDT_WAKE_UP_3_Tx_32B_tag


---------------------------   ----------    ------------  ------------------------------------------
==================================================================================================*/

#ifndef __NXP_FS65_H__
#define __NXP_FS65_H__

#define FS65_V11 1

#include "typedefs.h"

/****************************************************************************\
* Addresses of the FS6500/FS4500 registers
\****************************************************************************/
#define INIT_VREG_ADR								0x01
#define INIT_WU1_ADR								0x02
#define INIT_WU2_ADR								0x03
#define INIT_INT_ADR								0x04
#define INIT_INH_INT_ADR							0x05
#define LONG_DURATION_TIMER_ADR						0x06
#define HW_CONFIG_ADR								0x08
#define WU_SOURCE_ADR								0x09
#define DEVICE_ID_ADR								0x0A
#define IO_INPUT_ADR								0x0B
#define DIAG_VPRE_ADR								0x0C
#define DIAG_VCORE_ADR								0x0D
#define DIAG_VCCA_ADR								0x0E
#define DIAG_VAUX_ADR								0x0F
#define DIAG_VSUP_VCAN_ADR							0x10
#define DIAG_CAN_FD_ADR								0x11
#define DIAG_CAN_LIN_ADR							0x12
#define DIAG_SPI_ADR								0x13
#define MODE_ADR									0x15
#define REG_MODE_ADR								0x16
#define IO_OUT_AMUX_ADR								0x17
#define CAN_LIN_MODE_ADR							0x18
#define LDT_AFTER_RUN_1_ADR							0x1A
#define LDT_AFTER_RUN_2_ADR							0x1B
#define LDT_WAKE_UP_1_ADR							0x1C
#define LDT_WAKE_UP_2_ADR							0x1D
#define LDT_WAKE_UP_3_ADR							0x1E

#define INIT_FS1B_TIMING_ADR						0x21
#define BIST_ADR									0x22
#define INIT_SUPERVISOR_ADR							0x23
#define INIT_FAULT_ADR								0x24
#define INIT_FSSM_ADR								0x25
#define INIT_SF_IMPACT_ADR							0x26
#define WD_WINDOW_ADR								0x27
#define WD_LFSR_ADR									0x28
#define WD_ANSWER_ADR								0x29
#define RELEASE_FSxB_ADR							0x2A
#define SF_OUTPUT_REQUEST_ADR						0x2B
#define INIT_WD_CNT_ADR								0x2C
#define DIAG_SF_IOS_ADR								0x2D
#define WD_COUNTER_ADR								0x2E
#define DIAG_SF_ERR_ADR								0x2F
#define INIT_VCORE_OVUV_IMPACT_ADR					0x31
#define INIT_VCCA_OVUV_IMPACT_ADR					0x32
#define INIT_VAUX_OVUV_IMPACT_ADR					0x33
#define DEVICE_ID_FS_ADR							0x34

/*==================================================================================================
*   Structures/Type defines
==================================================================================================*/
/****************************************************************************\
* Write registers
\****************************************************************************/

typedef union { ///INIT_VREG_Tx
	vuint32_t R;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t ICCA_LIM						: 1;
		vuint32_t TCCA_LIM_OFF					: 1;
		vuint32_t IPFF_DIS						: 1;
		vuint32_t VCAN_OV_MON					: 1;
		vuint32_t 								: 1;
		vuint32_t TAUX_LIM_OFF					: 1;
		vuint32_t VAUX_TRK_EN					: 1;
		vuint32_t 								: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_VREG_Tx_32B_tag;

typedef union { ///INIT_WU1_Tx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WU_IO0							: 2;
		vuint32_t WU_IO2							: 2;
		vuint32_t WU_IO3							: 2;
		vuint32_t WU_IO4							: 2;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;

} INIT_WU1_Tx_32B_tag;


typedef union { ///INIT_WU2_Tx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WU_IO5							: 2;
		vuint32_t CAN_DIS_CFG						: 1;
		vuint32_t CAN_WU_TO							: 1;
		vuint32_t 									: 1;
		vuint32_t LIN_J2602_DIS						: 1;
		vuint32_t LIN_SR							: 2;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_WU2_Tx_32B_tag;

typedef union { ///INIT_INT_Tx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t INT_DURATION						: 1;
		vuint32_t INT_INH_LIN						: 1;
		vuint32_t INT_INH_ALL						: 1;
		vuint32_t INT_INH_VSNS						: 1;
		vuint32_t INT_INH_VPRE						: 1;
		vuint32_t INT_INH_VCORE						: 1;
		vuint32_t INT_INH_VOTHER					: 1;
		vuint32_t INT_INH_CAN						: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_INT_Tx_32B_tag;

typedef union { ///INIT_INH_INT_Tx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t 								: 1;
		vuint32_t 								: 1;
		vuint32_t 								: 1;
		vuint32_t INT_INH_IO5						: 1;
		vuint32_t INT_INH_IO4						: 1;
		vuint32_t INT_INH_IO3						: 1;
		vuint32_t INT_INH_IO2						: 1;
		vuint32_t INT_INH_IO0						: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_INH_INT_Tx_32B_tag;

typedef union { ///LONG_DURATION_TIMER_Tx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t F								: 3;
		vuint32_t REG_SE						: 1;
		vuint32_t 								: 1;
		vuint32_t MODE							: 1;
		vuint32_t LDT_ENABLE				: 1;
		vuint32_t 								: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LONG_DURATION_TIMER_Tx_32B_tag;

typedef union { ///MODE_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VKAM_EN						: 1;
		vuint32_t LP_OFF_AUTO_WU		: 1;
		vuint32_t GO_LPOFF					: 1;
		vuint32_t INT_REQ						: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} MODE_Tx_32B_tag;

typedef union { ///REG_MODE_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VCORE_EN					: 1;
		vuint32_t VCCA_EN						: 1;
		vuint32_t VAUX_EN						: 1;
		vuint32_t VCAN_EN						: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} REG_MODE_Tx_32B_tag;

typedef union { ///IO_OUT_AMUX_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t IO_OUT_4_EN				: 1;
		vuint32_t IO_OUT_4					: 1;
		vuint32_t 								: 1;
		vuint32_t 								: 1;
		vuint32_t 								: 1;
		vuint32_t AMUX						: 3;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} IO_OUT_AMUX_Tx_32B_tag;

typedef union { ///CAN_LIN_MODE_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t CAN_MODE				: 2;
		vuint32_t CAN_AUTO_DIS			: 1;
		vuint32_t LIN_MODE				: 2;
		vuint32_t LIN_AUTO_DIS			: 1;
		vuint32_t 								: 1;
		vuint32_t 								: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} CAN_LIN_MODE_Tx_32B_tag;

typedef union { ///LDT_AFTER_RUN_1_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t B15_8								: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LDT_AFTER_RUN_1_Tx_32B_tag;

typedef union { ///LDT_AFTER_RUN_2_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t B7_0								: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LDT_AFTER_RUN_2_Tx_32B_tag;

typedef union { ///LDT_WAKE_UP_1_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t B23_16							: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LDT_WAKE_UP_1_Tx_32B_tag;

typedef union { ///LDT_WAKE_UP_2_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t B15_8								: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LDT_WAKE_UP_2_Tx_32B_tag;

typedef union { ///LDT_WAKE_UP_3_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t B7_0								: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} LDT_WAKE_UP_3_Tx_32B_tag;

/***************************************************************************************************************
**************                            FAIL-SAFE REGISTERS                                    **************
**************************************************************************************************************/

#ifdef FS65_V11
  typedef union { ///INIT_FS1B_TIMING_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t FS1B_TIME						: 4;
		vuint32_t SECURE3						: 1;
		vuint32_t SECURE2						: 1;
		vuint32_t SECURE1						: 1;
		vuint32_t SECURE0						: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_FS1B_TIMING_Tx_32B_tag;
#else
  typedef union { ///INIT_FS1B_TIMING_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t TDUR_DELAY						: 4;
		vuint32_t SECURE3						: 1;
		vuint32_t SECURE2						: 1;
		vuint32_t SECURE1						: 1;
		vuint32_t SECURE0						: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_FS1B_TIMING_Tx_32B_tag;
#endif


typedef union { ///BIST_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t 								: 1;
		vuint32_t ABIST2_FS1B				: 1;
		vuint32_t ABIST2_VAUX				: 1;
		vuint32_t 								: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} BIST_Tx_32B_tag;

#ifdef FS65_V11
  typedef union { ///INIT_SUPERVISOR _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P						: 1;
		vuint32_t VCORE_5D					: 1;
		vuint32_t VCCA_5D					: 1;
		vuint32_t VAUX_5D					: 1;
		vuint32_t FS1B_TIME_RANGE				: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_SUPERVISOR_Tx_32B_tag;
#else
  typedef union { ///INIT_SUPERVISOR _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VCORE_5D					: 1;
		vuint32_t VCCA_5D						: 1;
		vuint32_t VAUX_5D						: 1;
		vuint32_t 								: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_SUPERVISOR_Tx_32B_tag;
#endif

#ifdef FS65_V11
  typedef union { ///INIT_FAULT _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t FLT_ERR_FS				: 1;
		vuint32_t FS1B_CAN_IMPACT	: 1;
		vuint32_t FLT_ERR_IMPACT		: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_FAULT_Tx_32B_tag;
#else
  typedef union { ///INIT_FAULT _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t FLT_ERR_FS				: 1;
		vuint32_t FS1B_CAN_IMPACT	: 1;
		vuint32_t 								: 1;
		vuint32_t FLT_ERR_IMPACT		: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
  } INIT_FAULT_Tx_32B_tag;
#endif


typedef union { ///INIT_FSSM _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t IO_45_FS					: 1;
		vuint32_t IO_23_FS					: 1;
		vuint32_t PS								: 1;
		vuint32_t RSTB_DURATION			: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_FSSM_Tx_32B_tag;

typedef union { ///INIT_SF_IMPACT _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t TDLY_DUR					: 1;
		vuint32_t DIS_8S						: 1;
		vuint32_t WD_IMPACT				: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_SF_IMPACT_Tx_32B_tag;

typedef union { ///WD_WINDOW _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WD_WINDOW				: 4;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} WD_WINDOW_Tx_32B_tag;

typedef union { ///WD_LFSR _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WD_LFSR					: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} WD_LFSR_Tx_32B_tag;

typedef union { ///WD_ANSWER _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WD_ANSWER				: 8;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} WD_ANSWER_Tx_32B_tag;

typedef union { ///RELEASE_FSxB _Tx
	vuint32_t R;
	struct {
		vuint32_t					:16;
		vuint32_t RW				: 1;
		vuint32_t ADR				: 6;
		vuint32_t P					: 1;
		vuint32_t RELEASE_FSxB_7		: 1;
		vuint32_t RELEASE_FSxB_6		: 1;
		vuint32_t RELEASE_FSxB_5		: 1;
		vuint32_t RELEASE_FSxB_4		: 1;
		vuint32_t RELEASE_FSxB_3		: 1;
		vuint32_t RELEASE_FSxB_2		: 1;
		vuint32_t RELEASE_FSxB_1		: 1;
		vuint32_t RELEASE_FSxB_0		: 1;
	} B;
} RELEASE_FSxB_Tx_32B_tag;

typedef union { ///SF_OUTPUT_REQUEST _Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t FS1B_LOW_REQ			: 1;
		vuint32_t FS1B_DLY_REQ			: 1;
		vuint32_t FS0B_LOW_REQ			: 1;
		vuint32_t RSTB_REQ					: 1;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} SF_OUTPUT_REQUEST_Tx_32B_tag;

typedef union { ///INIT_WD_CNT_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t WD_CNT_ERR			: 2;
		vuint32_t WD_CNT_RFR			: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_WD_CNT_Tx_32B_tag;

typedef union { ///INIT_VCORE_OVUV_IMPACT_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VCORE_FS_OV			: 2;
		vuint32_t VCORE_FS_UV			: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_VCORE_OVUV_IMPACT_Tx_32B_tag;

typedef union { ///INIT_VCCA_OVUV_IMPACT_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VCCA_FS_OV			: 2;
		vuint32_t VCCA_FS_UV			: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_VCCA_OVUV_IMPACT_Tx_32B_tag;

typedef union { ///INIT_VAUX_OVUV_IMPACT_Tx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t RW								: 1;
		vuint32_t ADR								: 6;
		vuint32_t P									: 1;
		vuint32_t VAUX_FS_OV			: 2;
		vuint32_t VAUX_FS_UV			: 2;
		vuint32_t Secure_3					: 1;
		vuint32_t Secure_2					: 1;
		vuint32_t Secure_1					: 1;
		vuint32_t Secure_0					: 1;
	} B;
	struct {
		vuint32_t								:16;
		vuint32_t RW							: 1;
		vuint32_t ADR							: 6;
		vuint32_t P								: 1;
		vuint32_t BYTE_FIELD					: 8;
	} Bytes;
} INIT_VAUX_OVUV_IMPACT_Tx_32B_tag;

/****************************************************************************\
* Read registers
\****************************************************************************/
typedef union { ///INIT_VREG_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t ICCA_LIM					: 1;
		vuint32_t TCCA_LIM_OFF			: 1;
		vuint32_t IPFF_DIS					: 1;
		vuint32_t VCAN_OV_MON				: 1;
		vuint32_t RESERVED					: 1;
		vuint32_t TAUX_LIM_OFF			: 1;
		vuint32_t VAUX_TRK_EN				: 1;
		vuint32_t BAT_FAIL						: 1;
	} B;
} INIT_VREG_Rx_32B_tag;

typedef union { ///INIT_WU1_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t WU_IO0					: 2;
		vuint32_t WU_IO2					: 2;
		vuint32_t WU_IO3					: 2;
		vuint32_t WU_IO4					: 2;
	} B;
} INIT_WU1_Rx_32B_tag;

typedef union { ///INIT_WU2_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t WU_IO5					: 2;
		vuint32_t CAN_DIS_CFG				: 1;
		vuint32_t CAN_WU_TO					: 1;
		vuint32_t RESERVED					: 1;
		vuint32_t LIN_J2602_DIS			: 1;
		vuint32_t LIN_SR					: 2;
	} B;
} INIT_WU2_Rx_32B_tag;

typedef union { ///INIT_INT_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t INT_DURATION			: 1;
		vuint32_t INT_INH_LIN				: 1;
		vuint32_t INT_INH_ALL			: 1;
		vuint32_t INT_INH_VSNS			: 1;
		vuint32_t INT_INH_VPRE			: 1;
		vuint32_t INT_INH_VCORE		: 1;
		vuint32_t INT_INH_VOTHERS	: 1;
		vuint32_t INT_INH_CAN				: 1;
	} B;
} INIT_INT_Rx_32B_tag;

typedef union { ///INIT_INH_INT_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t INT_INH_5					: 1;
		vuint32_t INT_INH_4					: 1;
		vuint32_t INT_INH_3					: 1;
		vuint32_t INT_INH_2					: 1;
		vuint32_t INT_INH_0					: 1;
	} B;
} INIT_INH_INT_Rx_32B_tag;

typedef union { ///LONG_DURATION_TIMER_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t F2								: 1;
		vuint32_t F1								: 1;
		vuint32_t F0								: 1;
		vuint32_t REG_SE						: 1;
		vuint32_t LDT_RUNNING				: 1;
		vuint32_t MODE							: 1;
		vuint32_t LDT_ENABLE				: 1;
		vuint32_t LDT_INT						: 1;
	} B;
} LONG_DURATION_TIMER_Rx_32B_tag;

typedef union { ///HW_CONFIG_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t LS_DETECT					: 1;
		vuint32_t RESERVED					: 1;
		vuint32_t VCCA_PNP_DETECT					: 1;
		vuint32_t VCCA_HW						: 1;
		vuint32_t VAUX_HW						: 1;
		vuint32_t 							: 1;
		vuint32_t DFS_HW						: 1;
		vuint32_t DBG_HW						: 1;
	} B;
} HW_CONFIG_Rx_32B_tag;

typedef union { ///WU_SOURCE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t IO_5_WU						: 1;
		vuint32_t IO_4_WU						: 1;
		vuint32_t IO_3_WU						: 1;
		vuint32_t IO_2_WU						: 1;
		vuint32_t IO_0_WU						: 1;
		vuint32_t AUTO_WU						: 1;
		vuint32_t LDT_WU						: 1;
		vuint32_t PHY_WU						: 1;
	} B;
} WU_SOURCE_Rx_32B_tag;

typedef union { ///IO_INPUT_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t IO_5							: 1;
		vuint32_t IO_4							: 1;
		vuint32_t 									: 1;
		vuint32_t IO_3							: 1;
		vuint32_t IO_2							: 1;
		vuint32_t 									: 1;
		vuint32_t 									: 1;
		vuint32_t IO_0							: 1;
	} B;
} IO_INPUT_Rx_32B_tag;

typedef union { ///DEVICE_ID_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t VCORE							: 2;
		vuint32_t PHY							: 2;
		vuint32_t VKAM							: 1;
		vuint32_t DEV_REV					: 3;
	} B;
} DEVICE_ID_Rx_32B_tag;

typedef union { ///DIAG_VPRE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t BOB								: 1;
		vuint32_t VPRE_STATE				: 1;
		vuint32_t TWARN_PRE				: 1;
		vuint32_t TSD_PRE						: 1;
		vuint32_t VPRE_OV						: 1;
		vuint32_t VPRE_UV						: 1;
		vuint32_t ILIM_PRE					: 1;
		vuint32_t 									: 1;
	} B;
} DIAG_VPRE_Rx_32B_tag;

typedef union { ///DIAG_VCORE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t 									: 1;
		vuint32_t VCORE_STATE				: 1;
		vuint32_t TWARN_CORE				: 1;
		vuint32_t TSD_CORE					: 1;
		vuint32_t VCORE_FB_OV				: 1;
		vuint32_t VCORE_FB_UV				: 1;
		vuint32_t 									: 1;
		vuint32_t 									: 1;
	} B;
} DIAG_VCORE_Rx_32B_tag;

typedef union { ///DIAG_VCCA_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t 									: 1;
		vuint32_t 									: 1;
		vuint32_t TWARN_CCA					: 1;
		vuint32_t TSD_CCA						: 1;
		vuint32_t VCCA_OV						: 1;
		vuint32_t VCCA_UV						: 1;
		vuint32_t ILIM_CCA					: 1;
		vuint32_t ILIM_CCA_OFF			: 1;
	} B;
} DIAG_VCCA_Rx_32B_tag;

typedef union { ///DIAG_VAUX_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t 									: 1;
		vuint32_t 									: 1;
		vuint32_t 									: 1;
		vuint32_t TSD_AUX						: 1;
		vuint32_t VAUX_OV						: 1;
		vuint32_t VAUX_UV						: 1;
		vuint32_t ILIM_AUX					: 1;
		vuint32_t ILIM_AUX_OFF			: 1;
	} B;
} DIAG_VAUX_Rx_32B_tag;

typedef union { ///DIAG_VSUP_VCAN_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t VSNS_UV						: 1;
		vuint32_t VSUP_UV_7				: 1;
		vuint32_t IPFF							: 1;
		vuint32_t TSD_CAN						: 1;
		vuint32_t VCAN_OV						: 1;
		vuint32_t VCAN_UV						: 1;
		vuint32_t ILIM_CAN					: 1;
		vuint32_t 									: 1;
	} B;
} DIAG_VSUP_VCAN_Rx_32B_tag;

typedef union { ///DIAG_CAN_FD_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t CANH_BATT					: 1;
		vuint32_t CANH_GND					: 1;
		vuint32_t CANL_BATT					: 1;
		vuint32_t CANL_GND					: 1;
		vuint32_t CAN_DOM					: 1;
		vuint32_t 									: 1;
		vuint32_t RXD_REC					: 1;
		vuint32_t TXD_DOM					: 1;
	} B;
} DIAG_CAN_FD_Rx_32B_tag;

typedef union { ///DIAG_CAN_LIN_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t LIN_DOM					: 1;
		vuint32_t TXDL_DOM					: 1;
		vuint32_t 									: 1;
		vuint32_t RXDL_REC					: 1;
		vuint32_t LIN_OT						: 1;
		vuint32_t 									: 1;
		vuint32_t CAN_OT						: 1;
		vuint32_t CAN_OC						: 1;
	} B;
} DIAG_CAN_LIN_Rx_32B_tag;

typedef union { ///DIAG_SPI_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t SPI_ERR						: 1;
		vuint32_t bit6									: 1;
		vuint32_t SPI_CLK						: 1;
		vuint32_t bit4									: 1;
		vuint32_t SPI_REQ						: 1;
		vuint32_t bit2									: 1;
		vuint32_t SPI_PARITY				: 1;
		vuint32_t bit0									: 1;
	} B;
} DIAG_SPI_Rx_32B_tag;

typedef union { ///MODE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t VKAM_EN						: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t INIT							: 1;
		vuint32_t NORMAL						: 1;
		vuint32_t DFS								: 1;
		vuint32_t LPOFF							: 1;
	} B;
} MODE_Rx_32B_tag;

typedef union { ///REG_MODE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t VCORE_EN					: 1;
		vuint32_t VCCA_EN						: 1;
		vuint32_t VAUX_EN						: 1;
		vuint32_t VCAN_EN						: 1;
	} B;
} REG_MODE_Rx_32B_tag;

typedef union { ///IO_OUT_AMUX_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t IO_OUT_4_EN				: 1;
		vuint32_t IO_OUT_4					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t 					: 1;
		vuint32_t AMUX						: 3;
	} B;
} IO_OUT_AMUX_Rx_32B_tag;

typedef union { ///CAN_LIN_MODE_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t CAN_MODE				: 2;
		vuint32_t CAN_AUTO_DIS			: 1;
		vuint32_t LIN_MODE				: 2;
		vuint32_t LIN_AUTO_DIS			: 1;
		vuint32_t CAN_WU						: 1;
		vuint32_t LIN_WU						: 1;
	} B;
} CAN_LIN_MODE_Rx_32B_tag;

typedef union { ///LDT_AFTER_RUN_1_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t B15_8								: 8;
	} B;
} LDT_AFTER_RUN_1_Rx_32B_tag;

typedef union { ///LDT_AFTER_RUN_2_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t B7_0								: 8;
	} B;
} LDT_AFTER_RUN_2_Rx_32B_tag;

typedef union { ///LDT_WAKE_UP_1_Rx
	vuint32_t R;
	struct {
		vuint32_t								:16;
		vuint32_t Status						: 8;
		vuint32_t B23_16						: 1;
	} B;
} LDT_WAKE_UP_1_Rx_32B_tag;

typedef union { ///LDT_WAKE_UP_2_Rx
	vuint32_t R;
	struct {
		vuint32_t									:16;
		vuint32_t Status							: 8;
		vuint32_t B15_8								: 8;
	} B;
} LDT_WAKE_UP_2_Rx_32B_tag;

typedef union { ///LDT_WAKE_UP_3_Rx
	vuint32_t R;
	struct {
		vuint32_t										:16;
		vuint32_t Status						: 8;
		vuint32_t B7_0								: 8;
	} B;
} LDT_WAKE_UP_3_Rx_32B_tag;

typedef union { ///INIT_FS1B_TIMING_Rx
	uint32_t R;
	struct {
			uint32_t										:16;
			uint32_t Status						: 8;
			uint32_t SPI_FS_ERR				: 1;
			uint32_t SPI_FS_CLK				: 1;
			uint32_t SPI_FS_REQ				: 1;
			uint32_t SPI_FS_PARITY		: 1;
			uint32_t TDUR_DELAY			: 4;

	} B;
} INIT_FS1B_TIMING_Rx_32B_tag;

typedef union { ///BIST_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t LBIST_OK					: 1;
		uint32_t ABIST2_FS1B_OK		: 1;
		uint32_t ABIST2_VAUX_OK		: 1;
		uint32_t ABIST1_OK					: 1;
	} B;
} BIST_Rx_32B_tag;

#ifdef FS65_V11
  typedef union { ///INIT_SUPERVISOR_Rx
	uint32_t R;
	  struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t VCORE_5D					: 1;
		uint32_t VCCA_5D						: 1;
		uint32_t VAUX_5D						: 1;
		uint32_t FS1B_TIME_RANGE				: 1;
	  } B;
  } INIT_SUPERVISOR_Rx_32B_tag;
#else
  typedef union { ///INIT_SUPERVISOR_Rx
	uint32_t R;
	  struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t VCORE_5D					: 1;
		uint32_t VCCA_5D						: 1;
		uint32_t VAUX_5D						: 1;
		uint32_t RESERVED					: 1;
	  } B;
  } INIT_SUPERVISOR_Rx_32B_tag;
#endif


#ifdef FS65_V11
  typedef union { ///INIT_FAULT_Rx
	uint32_t R;
  	  struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t FLT_ERR_FS				: 1;
		uint32_t FS1B_CAN_IMPACT	: 1;
		uint32_t FLT_ERR_IMPACT		: 2;
	  } B;
  } INIT_FAULT_Rx_32B_tag;
#else
  typedef union { ///INIT_FAULT_Rx
	uint32_t R;
	  struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t FLT_ERR_FS				: 1;
		uint32_t FS1B_CAN_IMPACT	: 1;
		uint32_t RESERVED					: 1;
		uint32_t FLT_ERR_IMPACT		: 1;
	  } B;
  } INIT_FAULT_Rx_32B_tag;
#endif


typedef union { ///INIT_FSSM_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t IO_45_FS					: 1;
		uint32_t IO_23_FS					: 1;
		uint32_t PS								: 1;
		uint32_t RSTB_DURATION			: 1;
	} B;
} INIT_FSSM_Rx_32B_tag;

typedef union { ///INIT_SF_IMPACT_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t TDLY_TDUR					: 1;
		uint32_t DIS_8S						: 1;
		uint32_t WD_IMPACT				: 2;
	} B;
} INIT_SF_IMPACT_Rx_32B_tag;

typedef union { ///WD_WINDOW_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t WD_WINDOW			: 4;
	} B;
} WD_WINDOW_Rx_32B_tag;

typedef union { ///WD_LFSR_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t WD_LFSR				: 8;
	} B;
} WD_LFSR_Rx_32B_tag;

typedef union { ///WD_ANSWER_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t RSTB							: 1;
		uint32_t FSxB							: 1;
		uint32_t WD_BAD_DATA			: 1;
		uint32_t FSO_G							: 1;
		uint32_t IO_FS_G						: 1;
		uint32_t WD_BAD_TIMING		: 1;
		uint32_t ERR_INT_HW				: 1;
		uint32_t ERR_INT_SW				: 1;
	} B;
} WD_ANSWER_Rx_32B_tag;

typedef union { ///RELEASE_FSxB_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR			: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t RESERVED					: 1;
		uint32_t FS1B_SNS					: 1;
		uint32_t FS0B_SNS					: 1;
		uint32_t RSTB_SNS					: 1;
	} B;
} RELEASE_FSxB_Rx_32B_tag;

typedef union { ///SF_OUTPUT_REQUEST_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t FS1B_DRV					: 1;
		uint32_t FS1B_DLY_DRV			: 1;
		uint32_t FS0B_DRV					: 1;
		uint32_t RSTB_DRV					: 1;
	} B;
} SF_OUTPUT_REQUEST_Rx_32B_tag;

typedef union { ///INIT_WD_CNT_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t WD_CNT_ERR			: 2;
		uint32_t WD_CNT_RFR			: 2;
	} B;
} INIT_WD_CNT_Rx_32B_tag;

typedef union { ///DIAG_SF_IOS_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t RSTB_EXT					: 1;
		uint32_t RSTB_DIAG					: 1;
		uint32_t FS0B_DIAG				: 2;
		uint32_t FS1B_DIAG				: 2;
		uint32_t IO_23_FAIL				: 1;
		uint32_t IO_45_FAIL				: 1;
	} B;
} DIAG_SF_IOS_Rx_32B_tag;

typedef union { ///WD_COUNTER_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t WD_ERR					: 3;
		uint32_t 						: 1;
		uint32_t WD_RFR					: 3;
		uint32_t 						: 1;
	} B;
} WD_COUNTER_Rx_32B_tag;

typedef union { ///DIAG_SF_ERR_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t FLT_ERR					: 3;
		uint32_t RESERVED					: 1;
		uint32_t V2P5_M_A_OV					: 1;
		uint32_t V2P5_M_D_OV					: 1;
		uint32_t FCRBM_OV					: 1;
		uint32_t FCRBM_UV					: 1;
	} B;
} DIAG_SF_ERR_Rx_32B_tag;

typedef union { ///INIT_VCORE_OVUV_IMPACT_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY				: 1;
		uint32_t VCORE_FS_OV			: 2;
		uint32_t VCORE_FS_UV			: 2;
	} B;
} INIT_VCORE_OVUV_IMPACT_Rx_32B_tag;

typedef union { ///INIT_VCCA_OVUV_IMPACT_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t VCCA_FS_OV			: 2;
		uint32_t VCCA_FS_UV			: 2;
	} B;
} INIT_VCCA_OVUV_IMPACT_Rx_32B_tag;

typedef union { ///INIT_VAUX_OVUV_IMPACT_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t SPI_FS_ERR				: 1;
		uint32_t SPI_FS_CLK				: 1;
		uint32_t SPI_FS_REQ				: 1;
		uint32_t SPI_FS_PARITY		: 1;
		uint32_t VAUX_FS_OV			: 2;
		uint32_t VAUX_FS_UV			: 2;
	} B;
} INIT_VAUX_OVUV_IMPACT_Rx_32B_tag;

typedef union { ///DEVICE_ID_FS_Rx
	uint32_t R;
	struct {
		uint32_t										:16;
		uint32_t Status						: 8;
		uint32_t 					: 1;
		uint32_t 					: 1;
		uint32_t 					: 1;
		uint32_t 					: 1;
		uint32_t 					: 1;
		uint32_t 					: 1;
		uint32_t DFS_HW						: 1;
		uint32_t FS1								: 1;
	} B;
} DEVICE_ID_FS_Rx_32B_tag;


extern uint8_t	FS65_Error;

#endif
