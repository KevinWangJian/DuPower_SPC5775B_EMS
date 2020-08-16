/*******************************************************************************
 *
 * Freescale Semiconductor Inc.
 * (c) Copyright 2006-2012 Freescale Semiconductor, Inc.
 * ALL RIGHTS RESERVED.
 *
 ********************************************************************************
 *
 * $File Name:       FS65xx.c$
 * @file             FS65xx.c
 *
 * $Date:            Aug-18-2015$
 * @date             Aug-18-2015
 *
 * $Version:         1.5$
 * @version          1.5
 *
 * Description      		FS65xx driver source file
 * @brief The function           FS65xx driver source file
 *
 * --------------------------------------------------------------------
 * $Name:  $
 *******************************************************************************/

/*******************************************************************************
 *
 *  @mainpage FS65xx driver for MPC574xP
 *
 *  @section Intro Introduction
 *
 *	This package contains PowerSBC driver allowing to control FS65xx.
 *	PwSBC driver was created as a demo code to enable our customers
 *	to start their development quickly and to demonstrate functionality of the FS65xx
 *	chip. Presented driver is not AUTOSAR nor ISO26262 compliant. This driver package
 *	needs so-called MPC5744P Basic software drivers, which present the basic layer
 *	for this application.
 *
 *  The key features of this package are the following:
 *  - Offer driver allowing to write and read into and from PwSBC registers
 *  - Switch PwSBC modes (low power, normal etc.)
 *  - Treat all interrupt sources (events)
 *  - Supervise voltages presented in the PwSBC interface
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
 *   Platform             : MPC574xP
 *   Dependencies         : MPC574xP - Basic SW drivers.
 *   All Rights Reserved.
 ==================================================================================================*/

/*==================================================================================================
  Revision History:
  Modification     This function
  Author (core ID)              Date D/M/Y       Name		  		Description of Changes
  B35993 / BRNY001		18/08/2015 	   ALL		  		Driver ported from MC33908
  BRNY001				30/10/2016	FS65_ProcessSPI		Added missing registers (WU_source, Diag_Vcore, Diag_vcca)
  BRNY001				04/10/2017  LDT related functions  Bug correction

  ---------------------------   ----------    ------------  ------------------------------------------
  ==================================================================================================*/

#include "typedefs.h"
//#include "mpc5744p.h"
#include "FS65xx_driver.h"
#include "FS65xx.h"
#include "sbc_65xx.h"
//#include "SIUL.h"
//#include "LINFLEX.h"
//#include "ADC.h"
#include "SpiIf.h"
#include "common.h"



struct {
	uint32_t				writeCmd;					///last write command
	uint32_t				readCmd;					///last read command
	uint32_t				stateSPI;					///actual state of the state machine
	Status_32B_tag			statusPwSBC;			///actual PwSBC status
	uint32_t				response;					///last PwSBC response
	uint32_t				FSdelayDisabled;	///disables delay 3.5 us after a secure command, 1 - disabled, 0 - enabled
} SPIstruct;

struct {
	uint32_t	WD_answer;				///current content of the WD_answer register
	register32_struct currentLFSR;		///last LFSR state
} PITstruct;

/*==================================================================================================
/                    Global Variables
 *==================================================================================================*/
uint8_t	FS65_Error = FS65_ERROR_OK;


/*==================================================================================================*
 *                   User-Defined Initial Values for FS65xx registers                               *
 *==================================================================================================*
 *  Fill-in this table with the initialization values for the INIT registers							*
 *  Don't bother with the secured bits, they are comuted by the initialization functions			*
 *==================================================================================================*/

FS65_RegVal_struct FS65_Registers_InitValues = {
    0x00,	//	INIT_VREG;
    0x43, //0x41,	//	INIT_WU1;   io_0 up and high, io_4 any edge
    0xC0, //0x40,	//	INIT_WU2;   io_5 any edge
    0x00,	//	INIT_INT;
    0x00,	//	INIT_INH_INT;
    0xF4,	//	CAN_LIN_MODE; CAN in Normal mode
    0x60,	//	INIT_FS1B_TIMING;
    0x00,	//	INIT_SUPERVISOR;
    0x30,	//	INIT_FAULT;
    //0x4D,	//	INIT_FSSM: IO_23 is fail-safe
    0x00,	//	INIT_FSSM: IO_23 not fail-safe
    0x10,	//	INIT_SF_IMPACT;
    //(WD_WIN_4 << 4),
	(WD_DISABLE<<4),//	WD_WINDOW;0x30
    0xB2,	//	WD_LFSR;
    0x00,	//	INIT_WD_CNT;
    0xE0,	//	INIT_VCORE_OVUV_IMPACT;
    0xE0,	//	INIT_VCCA_OVUV_IMPACT;
    0xE0,	//	INIT_VAUX_OVUV_IMPACT;
};



static uint32    txData, rxData;
static uint32_t  sbc_start = 0;
static uint32_t  fs65_error_code;
uint32_t reset_source;
uint32_t fault_error_counter = 0;


/*==================================================================================================*/
/*                    User Callback																	*/
/*==================================================================================================*/
/****************************************************************************!
 *   @par Description
 *       When an error is detected by the functions FS65_Init() or FS65_GetStatus(),
 *       this function is called. In the default implementation of this callback,
 *       the port PA1 is toggled every 1second.
 *       The users can change this behavior according to its application.
 ********************************************************************************/
void FS65_ErrorCallback(void) {
    //Add your code below -----------

}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a SPI error, this
 *       user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_SPI_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a CAN or LIN
 *       wake-up, this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_PHYWU_INT_Callback(void) {
	//Add your code below
}


/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of automatic
 *       wake-up, this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_AutoWU_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of the Long Duration Timer
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_LDTWU_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a CAN event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_CAN_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a LIN event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_LIN_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a Vaux/Vcan/Vcca event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_VXXX_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a Vcore event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_VCORE_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a Vpre event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_VPRE_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       When an INTb pulse is generated by the FS65 because of a IO event
 *       this user callback is called by the interrupt routine FS65_IsrSIUL
 ********************************************************************************/
void FS65_IO_INT_Callback(void) {
	//Add your code below
}

/****************************************************************************!
 *   @par Description
 *       This callback is called by the function FS65_Config_NonInit().
 *       The user can complete the configuration of the non INIT registers in this function.
 ********************************************************************************/
void FS65_UserConfigNonInit(void) {
	//Add your code below ----------
}

/*==================================================================================================*/
/*                    PUBLIC FUNCTIONS																*/
/*==================================================================================================*/

/****************************************************************************!
 *   @brief 	The function FS65_Config_NonInit initialize the non-INIT registers
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *       This function initializes some NORMAL registers of the FSSM and MSM.
 *       The register CAN_LIN_MODE is updated and the function FS65_UserConfigNonInit()
 *       is called. The user should add its own configuration in the function
 *       FS65_UserConfigNonInit().
 *       The initial value is recorded in the structure "FS65_Registers_InitValues".
 *   @return
 *		- FS65_RETURN_OK 		- Operation successful
 *		- OTHERS			 	- Number of errors encountered
 ********************************************************************************/
uint32_t FS65_Config_NonInit(void)
{
    uint32_t errorCode = FS65_RETURN_OK;

    errorCode += FS65_Set_CAN_LIN_MODE(FS65_Registers_InitValues.CAN_LIN_MODE);
    FS65_UserConfigNonInit();

    return errorCode;
}


/****************************************************************************!
 *   @brief 	The function FS65_Init_FSSM initialize the Fail-Safe State Machine
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function initializes all the INIT registers of the Fail-Safe State Machine
 *		according to the values stored in the structure "FS65_Registers_InitValues"
 *		In addition, the registers WD_WINDOW and WD_LFSR are also initialized
 *   @return
 *		- FS65_RETURN_OK 		- Operation sucessful
 *		- OTHERS			 	- Number of errors encountered
 ********************************************************************************/
uint32_t FS65_Init_FSSM(void)
{
    uint32_t errorCode = FS65_RETURN_OK;

    errorCode = FS65_Set_INIT_FS1B_TIMING(FS65_Registers_InitValues.INIT_FS1B_TIMING);
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_Set_INIT_SUPERVISOR(FS65_Registers_InitValues.INIT_SUPERVISOR);	//Normal threshold for Vcore/Vcca/Vaux
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_Set_INIT_FAULT(FS65_Registers_InitValues.INIT_FAULT);		//FLT_ERR final=6,FSx activated when FLT_ERR reaches intermediate
    delay_us(3);                                          //no CAN Tx when FS1b is activated

    errorCode += FS65_Set_INIT_FSSM(FS65_Registers_InitValues.INIT_FSSM);
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_Set_INIT_SF_IMPACT(FS65_Registers_InitValues.INIT_SF_IMPACT);	//FS1b in delay mode, 8sec timer enabled for reset,Reset act on WD accumulated error
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_ChangeWDwindow(FS65_Registers_InitValues.WD_WINDOW);				//3msec window
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_SendSeed(FS65_Registers_InitValues.WD_LFSR);							//0xB2
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_Set_INIT_WD_CNT(FS65_Registers_InitValues.INIT_WD_CNT);			//WD_CNT_ERR max=6, WD_CNT_RFR=6
    delay_us(3);  //Wait 3micsec

    errorCode += FS65_Set_INIT_VCORE_OVUV_IMPACT(FS65_Registers_InitValues.INIT_VCORE_OVUV_IMPACT);	//OV : RST&FS, UV : FS
    delay_us(3);  //Wait 3micsec
    errorCode += FS65_Set_INIT_VCCA_OVUV_IMPACT(FS65_Registers_InitValues.INIT_VCCA_OVUV_IMPACT);		//OV : RST&FS, UV : FS
    delay_us(3);  //Wait 3micsec
    errorCode += FS65_Set_INIT_VAUX_OVUV_IMPACT(FS65_Registers_InitValues.INIT_VAUX_OVUV_IMPACT);		//OV : RST&FS, UV : FS

    return errorCode;

}

/****************************************************************************!
 *   @brief 	The function FS65_Init_MSM initialize the Main State Machine
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function initializes all the INIT registers of the Main State Machine (excepted INIT_INT)
 *		according to the values stored in the structure "FS65_Registers_InitValues".
 *		INIT_INT should be initialized independently because after its initialization
 *		the INIT mode is exited.
 *   @return
 *		- FS65_RETURN_OK 		- Operation successful
 *		- OTHERS			 	- Number of errors encountered
 ********************************************************************************/
uint32_t FS65_Init_MSM(void)
{
    uint32_t errorCode = FS65_RETURN_OK;

    errorCode = FS65_Set_INIT_VREG(FS65_Registers_InitValues.INIT_VREG);//0x8300 0x0200
    errorCode += FS65_Set_INIT_WU1(FS65_Registers_InitValues.INIT_WU1); //0x8441 0x0400 IO0 IO4
    errorCode += FS65_Set_INIT_WU2(FS65_Registers_InitValues.INIT_WU2); //0x8440        IO5
    errorCode += FS65_Set_INIT_INH_INT(FS65_Registers_InitValues.INIT_INH_INT);

    return errorCode;
}

/****************************************************************************!
 *   @brief 	The function FS65_Init_MSM initialize the Main State Machine
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function implements the full initialization of the FS65 device.
 *		It calls the function FS65_Init_FSSM() and FS65_Init_MSM(). When an error is encountered,
 *		the function FS65_ErrorCallback is called. The user should define this callback function.
 *		For a complete description of this function, please refer to the document
 *		FS6500_Quick_Starter_Guide.pdf available on the web.
 *   @return
 *		- FS65_RETURN_OK 		- Operation successful
 *		- OTHERS			 	- Number of errors encountered
 ********************************************************************************/
void FS65_Init(void) {

    //uint32_t fs65_error_code;
	uint32_t error_count = 0;

    // 0. Get silicon version
    fs65_error_code = FS65_UpdateRegisterContent(DEVICE_ID_ADR);//0x1400

    // 1.Check LBIST & ABIST1 completion
    fs65_error_code = FS65_UpdateRegisterContent(BIST_ADR);//0x4400
    if (fs65_error_code != FS65_RETURN_OK ) {
		FS65_Error = FS65_SPI_FAIL;
		FS65_ErrorCallback();
    }

    if (INTstruct.BIST.B.LBIST_OK != 1) {
	// LBIST Fail, FSx can not be released, user action required
		FS65_Error = FS65_LBIST_FAIL;
		FS65_ErrorCallback();
    }
    if (INTstruct.BIST.B.ABIST1_OK !=1) {
	// ABIST1 Fail, FSx can not be relaesed, user action required
		FS65_Error = FS65_ABIST1_FAIL;
		FS65_ErrorCallback();
    }

    // 2. Get cause of SBC restart
    fs65_error_code = FS65_UpdateRegisterContent(INIT_VREG_ADR);//0x0200
    if (fs65_error_code != FS65_RETURN_OK ) {
		FS65_Error = FS65_SPI_FAIL;
		FS65_ErrorCallback();
    }



	// 3. Power-On Reset, Init Main registers should be initialized
    // only config in init module
	fs65_error_code = FS65_Init_MSM();  ////////////////////////write register
	if (fs65_error_code != FS65_RETURN_OK) {
	    // Error during initialization, user action required
			FS65_Error = FS65_INIT_MSM_FAIL;
			FS65_ErrorCallback();
	}
	// Exit INIT_MAIN mode
	// enter the normal module
	FS65_Set_INIT_INT(FS65_Registers_InitValues.INIT_INT); //all interrupts are enabled




	// 4. Check and clear wakeup source
	fs65_error_code = FS65_UpdateRegisterContent(WU_SOURCE_ADR); //Read and clear WU sources
	if (fs65_error_code != FS65_RETURN_OK ) {
	    FS65_Error = FS65_SPI_FAIL;
	    FS65_ErrorCallback();
	}else{
		reset_source = (INTstruct.WU_SOURCE.R); //add by psm 2018/8/30
	}

    // 5. Init FSSM registers
    fs65_error_code = FS65_Init_FSSM();    ////////////////////////write register
    if (fs65_error_code != FS65_RETURN_OK) {
        // Error during initialization, user action required
		FS65_Error = FS65_INIT_FSSM_FAIL;
		FS65_ErrorCallback();
    }

    // 5bis; Get current mode of operation
    fs65_error_code = FS65_UpdateRegisterContent(MODE_ADR);
    if (fs65_error_code != FS65_RETURN_OK) {
        // Error during initialization, user action required
    	FS65_Error = FS65_INIT_FSSM_FAIL;
    	FS65_ErrorCallback();
    }

    // 5ter; Check HW configuration of Vaux/Vcca
    fs65_error_code = FS65_UpdateRegisterContent(HW_CONFIG_ADR);
    if (fs65_error_code != FS65_RETURN_OK) {
        // Error during initialization, user action required
		FS65_Error = FS65_INIT_FSSM_FAIL;
		FS65_ErrorCallback();
    }

    // 6. Read all Diag registers to clear all bits
    fs65_error_code = FS65_RETURN_OK;
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VPRE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VCORE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VCCA_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VAUX_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VSUP_VCAN_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_CAN_FD_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_CAN_LIN_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SPI_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SF_IOS_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);
    if (fs65_error_code != FS65_RETURN_OK ) {
		FS65_Error = FS65_SPI_FAIL;
		FS65_ErrorCallback();
    }

    // 7. Check if FS1b implemented
    fs65_error_code = FS65_UpdateRegisterContent(DEVICE_ID_FS_ADR);
    if (fs65_error_code != FS65_RETURN_OK ) {
		FS65_Error = FS65_SPI_FAIL;
		FS65_ErrorCallback();
    }

    if (INTstruct.DEVICE_ID_FS.B.FS1 == 1)
    {
		//FS1B is implemented, it should be zero at this stage
		fs65_error_code = FS65_UpdateRegisterContent(RELEASE_FSxB_ADR);
		if (fs65_error_code != FS65_RETURN_OK ) {
			FS65_Error = FS65_SPI_FAIL;
			FS65_ErrorCallback();
		}
		//Read state of FS1B sense
		if (INTstruct.RELEASE_FSxB.B.FS1B_SNS == 1)
		{
			//FS1B already high
			//fs65_error_code = FS65_UpdateRegisterContent(DIAG_SF_IOS_ADR);
			if (fs65_error_code != FS65_RETURN_OK ) {
				FS65_Error = FS65_SPI_FAIL;
				FS65_ErrorCallback();
			}

			if (INTstruct.DIAG_SF_IOS.B.FS1B_DIAG >= 2)
			{
				//FS1b short-circuited to high, user action required
				FS65_Error = FS65_FS1B_SHORT2HIGH;
				FS65_ErrorCallback();
			}
			else
			{   //FS1B is still high because of the running delay, wait a little
				do {
					fs65_error_code = FS65_UpdateRegisterContent(RELEASE_FSxB_ADR);
					if (fs65_error_code != FS65_RETURN_OK ) {
						FS65_Error = FS65_SPI_FAIL;
						FS65_ErrorCallback();
					}
					if( (error_count++) >= 100 ){
						FS65_Error = FS65_SPI_FAIL;
						return;
					}
				}
				while (INTstruct.RELEASE_FSxB.B.FS1B_SNS == 1);
			}
		}

		//Run ABIST2_FS1B
		fs65_error_code = FS65_RunABIST2_FS1B();
		if (fs65_error_code != FS65_RETURN_OK) {
			// Error during ABIST2, user action required
			FS65_Error = FS65_ABIST2_FS1B_FAIL;
			FS65_ErrorCallback();
		}
		delay_us(200);  //Wait 200micsec

		fs65_error_code = FS65_UpdateRegisterContent(BIST_ADR);
		if (fs65_error_code != FS65_RETURN_OK ) {
			FS65_Error = FS65_SPI_FAIL;
			FS65_ErrorCallback();
		}

		if (INTstruct.BIST.B.ABIST2_FS1B_OK != 1) {
		   // Error during ABIST2, user action required
		   FS65_Error = FS65_ABIST2_FS1B_FAIL;
		   FS65_ErrorCallback();
		}
    }

    // 8. BIST Vaux if necessary
    fs65_error_code = FS65_UpdateRegisterContent(INIT_VAUX_OVUV_IMPACT_ADR);
    if (fs65_error_code != FS65_RETURN_OK ) {
		FS65_Error = FS65_SPI_FAIL;
		FS65_ErrorCallback();
    }

    if ((INTstruct.INIT_VAUX_OVUV_IMPACT.B.VAUX_FS_OV != 0) && (INTstruct.INIT_VAUX_OVUV_IMPACT.B.VAUX_FS_UV != 0))
    {   // Vaux is safety critical, need to BIST it
		//Run ABIST2_VAUX
		fs65_error_code = FS65_RunABIST2_VAUX();
		if (fs65_error_code != FS65_RETURN_OK) {
			// Error during ABIST2 VAUX, user action required
			FS65_Error = FS65_ABIST2_VAUX_FAIL;
			FS65_ErrorCallback();
		}

		delay_us(200);  //Wait 200micsec

		fs65_error_code = FS65_UpdateRegisterContent(BIST_ADR);
		if (fs65_error_code != FS65_RETURN_OK ) {
			FS65_Error = FS65_SPI_FAIL;
			FS65_ErrorCallback();
		}

		if (INTstruct.BIST.B.ABIST2_VAUX_OK != 1) {
			// Error during ABIST2 VAUX, user action required
			FS65_Error = FS65_ABIST2_VAUX_FAIL;
			FS65_ErrorCallback();
		}
     }

    FS65_Error = FS65_ERROR_OK;
    FS65_RequestFS1B_DLY(); //add by psm 2018-10-23
    sbc_start = 1;
}

/****************************************************************************!
 *   @brief 	The function FS65_GetStatus reads the contents of FS65xx registers
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function reads the contents of the main registers of the FS65 device
 *		(diagnostic registers, wake-up sources, Device_ID etc锟�) and updates the
 *		INTstruct accordingly. Please refer to the code for a list of registers being
 *		accessed by this function.
 *		When an error is detected when reading a register, the user callback
 *		鎻奡65_ErrorCallback()锟� is called.
 ********************************************************************************/
void FS65_GetStatus(void) {

    uint32_t fs65_error_code = 0;

    fs65_error_code += FS65_UpdateRegisterContent(BIST_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(INIT_VREG_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(WU_SOURCE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(MODE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(HW_CONFIG_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VPRE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VCORE_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VCCA_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VAUX_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_VSUP_VCAN_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_CAN_FD_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_CAN_LIN_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SPI_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SF_IOS_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(DEVICE_ID_FS_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(INIT_WD_CNT_ADR);
    fs65_error_code += FS65_UpdateRegisterContent(WD_LFSR_ADR);

    if (fs65_error_code != 0 ) {
	FS65_Error = FS65_STATUS_FAIL;
	FS65_ErrorCallback();
    }
}


/*==================================================================================================
 *=======================  Main logic LONG_DURATION_TIMER functions  ===============================
 *==================================================================================================*/

/****************************************************************************!
 *   @brief 	The function FS65_SelectLDTOperation selects the operating
 * 		function of the Long Duration Timer
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function configures the bits F2/F1/F0 of the register
 *		LONG_DURATION_TIMER
 *   @return
 *		- FS65_RETURN_OK 	- The operating function has been configured successfully
 *		- FS65_RETURN_ERROR 	- Operation failed or Wrong argument
 *   @remarks
 *		Mode 5, 6 and 7 are not implemented
 *   @par Code sample
 *		FS65_SelectLDTOperation(LDT_FUNCTION_1);
 *		- Configure the LDT to implement the function 1
 *		(Normal mode count and generate flag/int when counter reaches
 *		AfterRun Value)
 ********************************************************************************/
uint32_t FS65_SelectLDTOperation(uint32_t mode){

    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);

    if(mode > 4){
	return FS65_RETURN_ERROR;				//error -> mode not implemented
    }

    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.B.F = mode;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/****************************************************************************!
 *   @brief 	The function FS65_SetWakeUpReg configure the 3 registers
 *   LDT_WAKE_UP_x to read the 24bit Wake-up value and not the counter value
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears the bit REG_SE in the LONG_DURATION_TIMER register.
 *		The Counter register reads the programmed value of the Wake-Up register
 *   @return
 *		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_SetWakeUpReg();
 ********************************************************************************/
uint32_t FS65_SetWakeUpReg(void){
    uint32_t errorCode;
    LONG_DURATION_TIMER_Tx_32B_tag cmd;

    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.REG_SE = 0;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_SetWakeUpReg configure the 3 registers
 *   LDT_WAKE_UP_x to read the current 24bit counter value Wake-up value and
 *   not the wake-up value.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the bit REG_SE in the LONG_DURATION_TIMER register.
 *		The Counter register reads the programmed value of the RTC register
 *   @return
 * 		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_SetRTCReg();
 ********************************************************************************/
uint32_t FS65_SetRTCReg(void){

    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;

    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.REG_SE = 1;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_SetLDTNormalMode selects the normal mode of
 *		operation for the LDT. Resolutions is 1sec
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the bit MODE in the LONG_DURATION_TIMER register.
 *   @return
 *		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_SetLDTNormalMode();
 ********************************************************************************/
uint32_t FS65_SetLDTNormalMode(void){
    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.MODE = 1;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/****************************************************************************!
 *   @brief 	The function FS65_SetLDTCalibrationMode selects the calibration mode of
 *		operation for the LDT. Resolutions is 488绁峞c
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears the bit MODE in the LONG_DURATION_TIMER register.
 *   @return
 *		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_SetLDTCalibrationMode();
 ********************************************************************************/
uint32_t FS65_SetLDTCalibrationMode(void){
    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.MODE = 0;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/****************************************************************************!
 *   @brief 	The function FS65_StopLDTCounter stops the LDT
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears the bit LDT_ENABLE in the LONG_DURATION_TIMER register.
 *   @return
 *		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_StopLDTCounter();
 ********************************************************************************/
uint32_t FS65_StopLDTCounter(void){
    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.LDT_ENABLE = 0;

    errorCode = FS65_SendCmdRW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_StartLDTCounter starts the LDT
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the bit LDT_ENABLE in the LONG_DURATION_TIMER register.
 *   @return
 *		- FS65_RETURN_OK - Configuration successful
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		FS65_StartLDTCounter();
 ********************************************************************************/
uint32_t FS65_StartLDTCounter(void){
    uint32_t errorCode;

    LONG_DURATION_TIMER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = LONG_DURATION_TIMER_ADR;	//set address
    cmd.Bytes.BYTE_FIELD = (INTstruct.LONG_DURATION_TIMER.R & 0x000000FF);
    cmd.B.LDT_ENABLE = 1;

    errorCode =  FS65_SendCmdRW(cmd.R);
    return errorCode;
}


/******************************************************************************!
 *   @brief 	The function FS65_ConfAfterRunValue initializes the 2 registers
 *   LDT_AFTER_RUN_1 & LDT_AFTER_RUN_2 with the 16bit value given in argument
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function configures the registers LDT_AFTER_RUN_x
 *   @return
 *		- FS65_RETURN_OK - The operating function has been configured successfully
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *		Input value should be 16bit max
 *   @par Code sample
 *		FS65_ConfAfterRunValue(0xAAAA);
 *
 ********************************************************************************/
uint32_t FS65_ConfAfterRunValue(uint32_t value){

    uint32_t errorCode;

    LDT_AFTER_RUN_1_Tx_32B_tag cmd1;
    LDT_AFTER_RUN_2_Tx_32B_tag cmd2;

    //8 least significant bits
    cmd1.R = 0;

    if (value > MAX_AFTER_RUN_VALUE) {
	return FS65_RETURN_ERROR;
    }

    cmd1.B.RW = 1;				//write command
    cmd1.B.ADR = LDT_AFTER_RUN_1_ADR;		//set address
    cmd1.B.B15_8 = ((value & 0xFF00)>>8);

    errorCode =  FS65_SendCmdRW(cmd1.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    //8 most significant bits
    cmd2.R = 0;
    cmd2.B.RW = 1;				//write command
    cmd2.B.ADR = LDT_AFTER_RUN_2_ADR;		//set address
    cmd2.B.B7_0 = (value & 0x00FF);

    errorCode = FS65_SendCmdRW(cmd2.R);
    return errorCode;

}

/******************************************************************************!
 *   @brief 	The function FS65_ConfWakeUpValue configures the Wake_Up
 * 		value for the LDT operation
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function configures the registers LDT_WAKE_UP_x
 *   @return
 *		- FS65_RETURN_OK - The operating function has been configured successfully
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *		Input value should be 24bit max
 *   @par Code sample
 *		FS65_ConfWakeUpValue(0xAAAAAA);
 *
 ********************************************************************************/
uint32_t FS65_ConfWakeUpValue(uint32_t value){

    uint32_t errorCode;

    LDT_WAKE_UP_1_Tx_32B_tag cmd1;
    LDT_WAKE_UP_2_Tx_32B_tag cmd2;
    LDT_WAKE_UP_3_Tx_32B_tag cmd3;

    if (value > MAX_WAKE_UP_VALUE) {
	return FS65_RETURN_ERROR;
    }

    //8 least significant bits
    cmd1.R = 0;
    cmd1.B.RW = 1;				//write command
    cmd1.B.ADR = LDT_WAKE_UP_1_ADR;		//set address
    cmd1.B.B23_16 = ((value & 0x00FF0000)>>16);

    errorCode = FS65_SendCmdRW(cmd1.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    //8 intermediate bits
    cmd2.R = 0;
    cmd2.B.RW = 1;				//write command
    cmd2.B.ADR = LDT_WAKE_UP_2_ADR;		//set address
    cmd2.B.B15_8 = ((value & 0x0000FF00)>>8);

    errorCode = FS65_SendCmdRW(cmd2.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    //8 most significant bits
    cmd3.R = 0;
    cmd3.B.RW = 1;				//write command
    cmd3.B.ADR = LDT_WAKE_UP_3_ADR;		//set address
    cmd3.B.B7_0 = (value & 0x000000FF);

    errorCode = FS65_SendCmdRW(cmd3.R);
    return errorCode;

}

/*==================================================================================================
 *==================================  Main logic MODE functions  ===================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_SetLPOFFmode switches the current mode
 *          	of the FS65xxto the low power OFF mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit GO_LPOFF in the MODE register to switch FS65xx
 *		into the Low power Vreg OFF mode.
 *   @return
 *		Return value can be returned only in the case that the MCU is
 *		supplied externally (not using Vcore of the PwSBC). In the
 *		other case Vcore, FS65xx goes into the LPOFF mode, Vcore
 *		regulator is switched off and the MCU losts all data.
 *		- FS65_RETURN_OK - Device entered the LPOFF mode successfuly. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *		Applying this command will switch FS65xx into LPOFF mode, Vcore regulator
 *		will be switched OFF and MCU will lost all the data.
 *   @par Code sample
 *		while(FS65xx_SetLPmode());
 *		- Program stays in an infinite loop till the until the LPOFF mode
 *		is entered.
 ********************************************************************************/
uint32_t FS65_SetLPOFFmode(void){
    uint32_t errorCode;

    MODE_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;		//write command
    cmd.B.ADR = MODE_ADR;	//set address
    cmd.B.GO_LPOFF = 1;		//LPOFF mode

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_SetLPOFFmode_autoWU switches the current mode
 *          	of the FS65xx to the low power OFF mode with automatic WU 1msec after
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit LP_OFF_AUTO_WU in the MODE register to switch FS65xx
 *		into the Low power Vreg OFF mode with auto WU
 *   @return
 *		Return value can be returned only in the case that the MCU is
 *		supplied externally (not using Vcore of the PwSBC). In the
 *		other case  Vcore regulator is switched off and the MCU losts all data.
 *		- FS65_RETURN_OK - Device entered the LPOFF_AUTO_WU mode successfuly. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *		Normal mode has higher priority than LPOFF. Applying
 *		this command will switch FS65xx into LPOFF mode, Vcore regulator
 *		will be switched OFF and MCU will lost all the data.
 *   @par Code sample
 ********************************************************************************/
uint32_t FS65_SetLPOFFmode_autoWU(void){
    uint32_t errorCode;

    MODE_Tx_32B_tag cmd;
    cmd.R = 0;

    cmd.B.RW = 1;			//write command
    cmd.B.ADR = MODE_ADR;		//set address
    cmd.B.LP_OFF_AUTO_WU = 1;		//LPOFF mode with WU

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_RequestINT requests an interrupt.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit INT_request in the MODE register, which
 *		will generate an interrupt.
 *  @remarks 	INT_request will be cleared automatically when the interrupt is
 *		done.
 *  @par Code sample
 *		FS65_RequestINT();
 *		- Command requests an interrupt.
 ********************************************************************************/
uint32_t FS65_RequestINT(void){
    uint32_t errorCode;

    MODE_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;			//write command
    cmd.B.ADR = MODE_ADR;		//set address
    cmd.B.INT_REQ = 1;		//INTerruption request

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_EnableVKAM enables Vkam.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit VKAM_EN in the MODE register, which
 *		enables the Vkam regulator
 *  @remarks
 *
 *  @par Code sample
 *		FS65_EnableVKAM();
 *		- Command enables Vkam.
 ********************************************************************************/
uint32_t FS65_EnableVKAM(void){
    uint32_t errorCode;

    MODE_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;			//write command
    cmd.B.ADR = MODE_ADR;		//set address
    cmd.B.VKAM_EN = 1;			//VKAM enable

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.MODE.B.VKAM_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_DisableVKAM disables Vkam.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit VKAM_EN in the MODE register, which
 *		disables the Vkam regulator
 *  @remarks
 *
 *  @par Code sample
 *		FS65_DisableVKAM();
 *		- Command disables Vkam.
 ********************************************************************************/
uint32_t FS65_DisableVKAM(void){
    uint32_t errorCode;

    MODE_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;			//write command
    cmd.B.ADR = MODE_ADR;		//set address
    cmd.B.VKAM_EN = 0;		//VKAM disable

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.MODE.B.VKAM_EN == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}


/*==================================================================================================
 *======================================  REG_MODE functions  ======================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_EnableVcore enables the Vcore regulator during
 *		the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit Vcore_EN in the REG_MODE register, which
 *		enables the Vcore power supply. Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function
 *   @return
 *		- FS65_RETURN_OK - Vcore was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		uint32_t status;
 *		status = FS65_EnableVcore();
 *		- Command enables Vcore power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_EnableVcore(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCORE_EN = 1;				//enable Vcore

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCORE_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_DisableVcore disables the Vcore regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit Vcore_EN in the Reg Mode register,
 *		which disables the Vcore power supply.Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function.
 *		If Vcore has been defined to be safety-critical (register INIT_VCORE_OVUV_IMPACT),
 *		an error is returned and the regulator is not disabled.
 *   @return
 *		- FS65_RETURN_OK - Vcore was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Do not disable Vcore if it is configured as a safety critical.
 *   @par Code sample
 *		</para>
 *		uint32_t status;					</para>
 *		status = PwSBC_DisableVcore();		</para>
 *		- Command disables Vcore power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_DisableVcore(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;

    if(INTstruct.INIT_VCORE_OVUV_IMPACT.B.VCORE_FS_UV != 0){
	return FS65_RETURN_ERROR;				//error -> Vcore is safety critical
    }

    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCORE_EN = 0;				//disable Vcore

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCORE_EN == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_EnableVcca enables the Vcca regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit Vcca_EN in the Reg Mode register,
 *	 	which enables the Vcca power supply. Note that the register REG_MODE
 *	 	should have been read previously with the FS65_UpdateRegister() function.
 *   @return
 * 		- FS65_RETURN_OK - Vcca was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;		</para>
 *		status = FS65_EnableVcca();	</para>
 *		- Command enables Vcca power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_EnableVcca(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCCA_EN = 1;				//enable Vcca

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCCA_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_DisableVcca disables the Vcca regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit VCCA_EN in the REG Mode register,
 *		which disables the Vcca power supply.Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function.
 *		If Vcca has been defined to be safety-critical (register INIT_VCCA_OVUV_IMPACT),
 *		an error is returned and the regulator is not disabled.
 *   @return
 *		- FS65_RETURN_OK - Vcca was successfuly disabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Do not disable Vcca if it is configured as a safety critical.
 *   @par Code sample
 *		</para>
 *		uint32_t status;		</para>
 *		status = FS65_DisableVcca();	</para>
 *		- Command disables Vcca power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_DisableVcca(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;

    if(INTstruct.INIT_VCCA_OVUV_IMPACT.B.VCCA_FS_UV != 0){
	return FS65_RETURN_ERROR;				//error -> Vcca is safety critical
    }

    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCCA_EN = 0;				//disable Vcca

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCCA_EN == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
 }

/******************************************************************************!
 *   @brief 	The function FS65_EnableVaux enables the Vaux regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit Vaux_EN in the Reg Mode register, which
 *		enables the Vaux power supply.Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function
 *  @return
 *		- FS65_RETURN_OK - Vaux was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;		</para>
 *		status = FS65_EnableVaux();	</para>
 *		- Command enables Vaux power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_EnableVaux(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VAUX_EN = 1;				//enable Vaux

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VAUX_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_DisableVaux disables the Vaux regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit VAUX_EN in the Vreg Mode register,
 *		which disables the Vaux power supply.Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function.
 *		If Vaux has been defined to be safety-critical (register INIT_VAUX_OVUV_IMPACT),
 *		an error is returned and the regulator is not disabled.
 *   @return
 *		- FS65_RETURN_OK - Vaux was successfuly disabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Do not disable Vaux if it is configured as a safety critical.
 *   @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_DisableVaux();	</para>
 *		- Command disables Vaux power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_DisableVaux(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;

    if(INTstruct.INIT_VAUX_OVUV_IMPACT.B.VAUX_FS_UV != 0){
	return FS65_RETURN_ERROR;				//error -> Vaux is safety critical
    }

    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VAUX_EN = 0;				//disable Vaux

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VAUX_EN == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }					//success
}

/******************************************************************************!
 *   @brief 	The function FS65_EnableVcan enables the Vcan regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit Vcan_EN in the Vreg Mode register, which
 *		enables the Vcan power supply.Note that the register REG_MODE
 *		should have been read previously
 *   @return
 *		- FS65_RETURN_OK - Vcan was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_EnableVcan();	</para>
 *		Command enables Vcan power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_EnableVcan(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCAN_EN = 1;				//enable Vcan

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCAN_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_DisableVcan disables the Vcan regulator during the Normal mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit Vcan_EN in the Vreg Mode register,
 *		which disables the Vcan power supply.Note that the register REG_MODE
 *		should have been read previously with the FS65_UpdateRegister() function
 *   @return
 *		- FS65_RETURN_OK - Vcan was successfuly disabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 * @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_DisableVcan();	</para>
 *		- Command disables Vcan power supply and stores returned status.
 ********************************************************************************/
uint32_t FS65_DisableVcan(void){
    uint32_t errorCode;

    REG_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.REG_MODE.R << 4;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = REG_MODE_ADR;			//set address
    cmd.B.VCAN_EN = 0;				//disable Vcan

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.REG_MODE.B.VCAN_EN == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/*==================================================================================================
 *====================================  IO_OUT_AMUX functions  =====================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_EnableOUT4 enables an output gate driver
 *		for the IO4.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit IO_out_4_EN (register IO_out-AMUX),
 *		which enables output gate driver for IO_4. Note that the register
 *		IO_OUT_AMUX should have been read previously
 *   @return
 *		- FS65_RETURN_OK - Output gate driver was successfuly enabled. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_EnableOUT4();	</para>
 *		- Command enables output gate driver for IO_4 and stores returned status.
 ********************************************************************************/
uint32_t FS65_EnableOUT4(void){
    uint32_t errorCode;

    IO_OUT_AMUX_Tx_32B_tag cmd;
    cmd.R = INTstruct.IO_OUT_AMUX.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = IO_OUT_AMUX_ADR;			//set address
    cmd.B.IO_OUT_4_EN = 1;				//enable IO4 OUT

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.IO_OUT_AMUX.B.IO_OUT_4_EN == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_SetOUT4 sets the IO4.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit IO_out_4 (register IO_out-AMUX), which
 *		sets IO_4 to logical high state. Note that the register
 *		IO_OUT_AMUX should have been read previously
 *   @return
 *		- FS65_RETURN_OK - Output was successfuly set to high state. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_SetOUT4();		</para>
 *		- Command sets IO_4 to high state and stores returned status.
 ********************************************************************************/
uint32_t FS65_SetOUT4(void){
    uint32_t errorCode;

    IO_OUT_AMUX_Tx_32B_tag cmd;
    cmd.R = INTstruct.IO_OUT_AMUX.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = IO_OUT_AMUX_ADR;			//set address
    cmd.B.IO_OUT_4 = 1;				//set -> IO4 = 1

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.IO_OUT_AMUX.B.IO_OUT_4 == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
 }

/******************************************************************************!
 *   @brief  	The function FS65_ClearOUT4 clears the IO4 output (logic Low).
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function clears bit IO_out_4 (register IO_out-AMUX), which
 *		sets IO_4 to logical low state. Note that the register
 *		IO_OUT_AMUX should have been read previously
 *   @return
 *		- FS65_RETURN_OK - Output was successfuly set to low state. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_ClearOUT4();		</para>
 *		- Command sets IO_4 to low state and stores returned status.
 ********************************************************************************/
uint32_t FS65_ClearOUT4(void){
    uint32_t errorCode;

    IO_OUT_AMUX_Tx_32B_tag cmd;
    cmd.R = INTstruct.IO_OUT_AMUX.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = IO_OUT_AMUX_ADR;			//set address
    cmd.B.IO_OUT_4 = 0;				//clear -> IO4 = 0

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.IO_OUT_AMUX.B.IO_OUT_4 == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_SwitchAMUXchannel switches a desired channel to the output of AMUX.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *		This function switches AMUX channel to the desired configuration
 *		(bits Amux_2:0 in the IO_OUT_AMUX register. Note that the register
 *		IO_OUT_AMUX should have been read previously
 *
 * 	@param[in] nbChannel - Number of the desired AMUX channel (from 0 till 7).
 * 	@return
 *				- FS65_RETURN_OK - AMUX channel successfuly switched. <br>
 *				- FS65_RETURN_ERROR - Operation failed.
 *	@remarks
 *	@par Code sample
 *													</para>
 *			uint32_t status;						</para>
 *			status = FS65_SwitchAMUXchannel(5);	</para>
 *			- Command switches AMUX channel to the channel no. 5 and stores
 *			returned status.
 ********************************************************************************/
uint32_t FS65_SwitchAMUXchannel(uint32_t nbChannel){
    uint32_t errorCode;

    IO_OUT_AMUX_Tx_32B_tag cmd;

    if(nbChannel > 7){
	return FS65_RETURN_ERROR;			//error -> bad number of AMUX channel
    }

    cmd.R = INTstruct.IO_OUT_AMUX.R;	//restore old register setting
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = IO_OUT_AMUX_ADR;		//set address
    cmd.B.AMUX = nbChannel;			//set AMUX channel

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	  return errorCode;
    } else
    {
	  if (INTstruct.IO_OUT_AMUX.B.AMUX == nbChannel){
	    return FS65_RETURN_OK;			//success
	  }
	  else {
	    return FS65_RETURN_ERROR;			//error
	  }
   }
}

/*==================================================================================================
 *==================================  CAN_LIN_MODE functions  ======================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_SetCAN_LIN_mode sets the CAN mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function configures the CAN-LIN mode register.
 *   @param[in]
 *		Value - content to fill in the CAN_LIN_MODE register
 *   @return
 *		- FS65_RETURN_OK -  mode was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;							</para>
 *		status = FS65_SetCAN_LIN_MODE(0xFA00);		</para>
 ********************************************************************************/
uint32_t FS65_Set_CAN_LIN_MODE(uint32_t value){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;
    cmd.R 	=	0;
    cmd.B.RW 	=	1;
    cmd.B.ADR 	= 	CAN_LIN_MODE_ADR;
    cmd.Bytes.BYTE_FIELD = 	value;

    errorCode =  FS65_SendCmdRW(cmd.R);

    if(errorCode != FS65_RETURN_OK){
	return errorCode;		//error in the communication
    }
    else
    {
	if((INTstruct.CAN_LIN_MODE.R & 0x00FC) == value)
	{		//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_SetCANmode sets the CAN mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function changes CAN mode in the CAN-LIN mode register.
 *		Note that the CAN_LIN_MODE register should have been read previously
 *   @param[in]
 *		Mode - Desired CAN mode (from 0 till 3).
 *   @return
 *		- FS65_RETURN_OK - CAN mode was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;							</para>
 *		status = FS65_SetCANmode(CAN_SLEEP);		</para>
 *		- Command switches CAN transceiver into the Sleep mode without
 *		a wake-up capability.
 ********************************************************************************/
uint32_t FS65_SetCANmode(uint32_t mode){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;

    if(mode>3){
	return FS65_RETURN_ERROR;			//error -> bad mode number
    }

    cmd.R = INTstruct.CAN_LIN_MODE.R;	//restore old register setting
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;		//set address
    cmd.B.CAN_MODE = mode;			//set CAN mode

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.CAN_MODE == mode){
	    return FS65_RETURN_OK;			//success
	}
	else{
	    return FS65_RETURN_ERROR;			//error
	}
    }
}
/******************************************************************************!
 *   @brief 	The function FS65_SetAutoCANTxDisable sets the Automatic CAN Tx disable.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets bit CAN_AUTO_DIS in the CAN-LIN mode register.
 *		This will enable CAN transceiver to switch its mode from
 *		"Normal" to "Listen only" automatically when an event (CAN
 *		overtemperature/TXD dominant/RXD recessive) occurs.
 *		Note that the CAN_LIN_MODE register should have been read previously
 *   @return
 *		- FS65_RETURN_OK - CAN_AUTO_DIS bit was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;						</para>
 *		status = FS65_SetAutoCANTxDisable();	</para>
 *		- Command enables CAN transceiver to change its mode automatically.
 ********************************************************************************/
uint32_t FS65_SetAutoCANTxDisable(void){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.CAN_LIN_MODE.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;			//set address
    cmd.B.CAN_AUTO_DIS = 1;				//set automatic CAN disable

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.CAN_AUTO_DIS == 1){
	    return FS65_RETURN_OK;			//success
	}
	else{
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief The function FS65_ClearAutoCANTxDisable disables the automatic
 *			transition of the CAN transceiver to the low-power mode.
 *   @par Include
 *			FS65xx.h
 *   @par Description
 *			This function clears bit CAN_AUTO_DIS in the CAN-LIN mode register.
 *			In this configuration CAN transceiver will not change its
 *			mode automatically if any event occurs.
 *			Note that the CAN_LIN_MODE register should have been read previously
 *   @return
 *			- FS65_RETURN_OK - CAN_AUTO_DIS bit was successfuly cleared. <br>
 *			- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *			</para>
 *			uint32_t status;							</para>
 *			status = FS65_ClearAutoCANTxDisable();		</para>
 *			- Command  clears bit CAN_AUTO_DIS and stores returned status.
 ********************************************************************************/
uint32_t FS65_ClearAutoCANTxDisable(void){

    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.CAN_LIN_MODE.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;			//set address
    cmd.B.CAN_AUTO_DIS = 0;				//clear automatic CAN disable

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.CAN_AUTO_DIS == 0){
	    return FS65_RETURN_OK;			//success
	}
	else{
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_SetLINmode sets the LIN mode.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function changes LIN mode in the CAN-LIN mode register.
 *		Note that the CAN_LIN_MODE register should have been read previously
 *   @param[in]
 *		Mode - Desired LIN mode (from 0 till 3).
 *   @return
 *		- FS65_RETURN_OK - LIN mode was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;							</para>
 *		status = FS65_SetCANmode(LIN_SLEEP);		</para>
 *		- Command switches LIN transceiver into the Sleep mode without
 *		a wake-up capability.
 ********************************************************************************/
uint32_t FS65_SetLINmode(uint32_t mode){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;

    if(mode>3){
	return FS65_RETURN_ERROR;			//error -> bad mode number
    }

    cmd.R = INTstruct.CAN_LIN_MODE.R;	//restore old register setting
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;		//set address
    cmd.B.LIN_MODE = mode;			//set CAN mode

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.LIN_MODE == mode){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_SetAutoLINTxDisable sets the Automatic LIN Tx disable.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the Automatic LIN Tx disable.
 *		Note that the CAN_LIN_MODE register should have been read previously
 *   @param[in]
 *   @return
 *		- FS65_RETURN_OK - LIN TW disable was successfuly enabled.
 *		- FS65_RETURN_ERROR - Operation failed.
 *  @remarks
 *  @par Code sample
 *		</para>
 *		uint32_t status;							</para>
 *		status = FS65_SetAutoLINTxDisable();		</para>
 *		- Command enables LIN transceiver automatic Tx disabled
 ********************************************************************************/
uint32_t FS65_SetAutoLINTxDisable(void){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.CAN_LIN_MODE.R;	//restore old register setting
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;		//set address
    cmd.B.LIN_AUTO_DIS = 1;			//set CAN mode

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.LIN_AUTO_DIS == 1){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}

/******************************************************************************!
 *   @brief The function FS65_ClearAutoLINTxDisable disables the automatic
 *			transition of the LIN transceiver to the low-power mode.
 *   @par Include
 *			FS65xx.h
 *   @par Description
 *			This function clears bit LIN_AUTO_DIS in the CAN-LIN mode register.
 *			In this configuration LIN transceiver will not change its
 *			mode automatically if any event occurs.
 *			Note that the CAN_LIN_MODE register should have been read previously
 *   @return
 *			- FS65_RETURN_OK - LIN_AUTO_DIS bit was successfuly cleared. <br>
 *			- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *			</para>
 *			uint32_t status;							</para>
 *			status = FS65_ClearAutoLINTxDisable();		</para>
 *			- Command  clears bit LIN_AUTO_DIS and stores returned status.
 ********************************************************************************/
uint32_t FS65_ClearAutoLINTxDisable(void){
    uint32_t errorCode;

    CAN_LIN_MODE_Tx_32B_tag cmd;
    cmd.R = INTstruct.CAN_LIN_MODE.R;		//restore old register setting
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = CAN_LIN_MODE_ADR;			//set address
    cmd.B.LIN_AUTO_DIS = 0;				//clear automatic CAN disable

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else
    {
	if (INTstruct.CAN_LIN_MODE.B.LIN_AUTO_DIS == 0){
	    return FS65_RETURN_OK;			//success
	}
	else {
	    return FS65_RETURN_ERROR;			//error
	}
    }
}


/*==================================================================================================
 *======================================  BIST functions  ==========================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_RunABIST2_VAUX runs the ABIST2 for Vaux
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the bit ABIST2_VAUX in the register BIST.
 *   @param[in]
 *   @return
 *		- FS65_RETURN_OK - Seed was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed  <br>
 *   @remarks
 *   @par Code sample
 *		FS65_RunABIST2_VAUX();
 ********************************************************************************/
uint32_t FS65_RunABIST2_VAUX(void){
    uint32_t errorCode;

    BIST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = BIST_ADR;			//set address
    cmd.B.ABIST2_VAUX = 1;

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    return(errorCode);
}

/******************************************************************************!
 *   @brief 	The function FS65_RunABIST2_FS1B runs the ABIST2 for FS1B
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets the bit ABIST2_FS1B in the register BIST.
 *   @param[in]
 *   @return
 *		- FS65_RETURN_OK - Seed was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed. <br>
 *   @remarks
 *   @par Code sample
 *		FS65_RunABIST2_FS1B();
 ********************************************************************************/
uint32_t FS65_RunABIST2_FS1B(void){
    uint32_t errorCode;

    BIST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = BIST_ADR;			//set address
    cmd.B.ABIST2_FS1B = 1;

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    return(errorCode);
}

/*==================================================================================================
 *=======================================  WD_WINDOW functions  ====================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_ChangeWDwindow changes the WD window duration.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function changes WD window duration.
 *   @param[in] 	duration - WD window duration coded in binary (from 0 till 15).
 *		Predefined values:
 *		- WD_DISABLE - WD window disabled
 *		- WD_WIN_1 - 1 ms
 *		- WD_WIN_2 - 2 ms
 *		- WD_WIN_3 - 3 ms
 *		- WD_WIN_4 - 4 ms
 *		- WD_WIN_6 - 6 ms
 *		- WD_WIN_8 - 8 ms
 *		- WD_WIN_12	- 12 ms
 *		- WD_WIN_16	- 16 ms
 *		- WD_WIN_24	- 24 ms
 *		- WD_WIN_32	- 32 ms
 *		- WD_WIN_64	- 64 ms
 *		- WD_WIN_128 - 128 ms
 *		- WD_WIN_256 - 256 ms
 *		- WD_WIN_512 - 512 ms
 *		- WD_WIN_1024 - 1024 ms
 *   @return
 *		- FS65_RETURN_OK - WD window duration was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks
 *   @par Code sample
 *		</para>
 *		uint32_t status;							</para>
 *		status = FS65_ChangeWDwindow(WD_WIN_32);	</para>
 *		- Command changes WD window duration to 32 ms.
 ********************************************************************************/
uint32_t FS65_ChangeWDwindow(uint32_t value){
    uint32_t errorCode;

    WD_WINDOW_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR = WD_WINDOW_ADR;			//set address
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode = FS65_SendSecureCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }
    else {
	if( (INTstruct.WD_WINDOW.R & 0x0000000F) == ((value & 0x000000F0)>>4)){
	    return FS65_RETURN_OK;				//success
	}
	else {
	    return FS65_RETURN_ERROR;				//error
	}
    }
}


/*==================================================================================================
 *======================================  WD_LFSR functions  =======================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_SendSeed sends an LFSR seed from the MCU to the PwSBC.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sends new seed for the implemented LFSR.
 *   @param[in]
 *		seed - 	New seed for the LFSR. This can be any 8-bit value
 *		excluding 0.
 *   @return
 *		- FS65_RETURN_OK - Seed was successfuly changed. <br>
 *		- FS65_RETURN_ERROR - Operation failed. <br>
 *		- "2" - Wrong seed parameter (cannot be 0).
 *   @remarks 	Zero state is not allowed for this type of LFSR, because it
 *		should never evolve from this state.
 *   @par Code sample
 *		</para>
 *		uint32_t status;				</para>
 *		status = FS65_SendSeed(20);	</para>
 *		- Command changes LFSR value to 20 (decimal).
 ********************************************************************************/
uint32_t FS65_SendSeed(uint32_t seed){
    uint32_t errorCode;

    WD_LFSR_Tx_32B_tag cmd;

    if(seed == 0){
	return FS65_RETURN_ERROR;				//error ->	seed CANNOT be zero
    }

    cmd.R = 0;
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = WD_LFSR_ADR;			//set address
    cmd.B.WD_LFSR = seed;				//set LFSR seed

    errorCode = FS65_SendCmdRW(cmd.R);
    if (errorCode != FS65_RETURN_OK) {
	return FS65_RETURN_ERROR;
    }
    else
    {
	if(INTstruct.WD_LFSR.B.WD_LFSR == seed){
	    return FS65_RETURN_OK;				//success
	}
	else{
	    return FS65_RETURN_ERROR;				//error
	}
    }
}

/*==================================================================================================
 *======================================  WD_ANSWER functions  =====================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_RefreshWD refreshes the WD.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function refreshes WD using the given WD answer. This is
 *		done by writing into the WD answer register.
 *   @param[in] answer - 8-bit WD answer to be sent.
 *   @return
 *		- FS65_RETURN_OK - WD was successfuly refreshed. <br>
 *		- FS65_RETURN_ERROR - WD refresh error
 *
 *   @remarks 	8-bit answer must be constisted of the control computations
 *		that have been done on the actual LFSR content.
 *   @par Code sample
 *		</para>
 *		uint32_t status;					</para>
 *		status = FS65_RefreshWD(50);		</para>
 *		- Command sends WD answer with value 50.
 ********************************************************************************/
uint32_t FS65_RefreshWD(uint32_t answer){
    uint32_t errorCode;

    WD_ANSWER_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;					//write command
    cmd.B.ADR = WD_ANSWER_ADR;			//set address
    cmd.B.WD_ANSWER = answer;			//set answer

    errorCode =  FS65_SendCmdRW(cmd.R);
    return(errorCode);					//returns error status from the previous function
}

/******************************************************************************!
 *   @brief 	The function FS65_ComputeLFSR computes, stores and returns
 *		test based from actual LFSR.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function makes control computations with the given LFSR and
 *		returns result of the computation on the least 8 bits.
 *   @param[in] actualLFSR - 8-bit LFSR value on which will be applied control
 *		computations.
 *   @return 	Result of the control computations. Computations are made as
 *		follows:
 *		~(((lfsr*4 + 6 - 4)/4
 *  @par Code sample
 *		</para>
 *		uint32_t result;					</para>
 *		result = FS65_ComputeLFSR(50);		</para>
 *		- Command makes control computations with the given LFSRvalue (50)
 *		and returns result.
 ********************************************************************************/

 uint32_t FS65_ComputeLFSR(uint32_t	actualLFSR)
{
	 volatile uint32_t newLFSR;
	 newLFSR  = actualLFSR<<2;
	 newLFSR += 6;
	 newLFSR -= 4;
	 newLFSR  = ~newLFSR;
	 newLFSR  = newLFSR>>2;

	 return (newLFSR);
}

/*==================================================================================================
 *==================================  RELEASE_FSxB functions  ===================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_ReleaseFS0out releases the Fail Safe output FS0b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function handles current LFSR content (stored in the LFSR)
 *		and sends command to release safe output FS0b.
 *   @remarks 	Command should be applied to release fail safe outputs when RST
 *		error counter goes back to the state no. 0.
 *   @par Code sample
 *		FS65_ReleaseFS0out();
 *		- Command releases fail safe output FS0.
 ********************************************************************************/
uint32_t FS65_ReleaseFS0out(void){
    uint32_t errorCode;

    RELEASE_FSxB_Tx_32B_tag cmd;
    cmd.R = 0;

    errorCode = FS65_UpdateRegisterContent(WD_LFSR_ADR);					//get current LFSR content
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    PITstruct.currentLFSR.R = INTstruct.WD_LFSR.R;		//store current LFSR in PIT structure

    cmd.B.RELEASE_FSxB_0 = ~PITstruct.currentLFSR.B.bit4;
    cmd.B.RELEASE_FSxB_1 = ~PITstruct.currentLFSR.B.bit3;
    cmd.B.RELEASE_FSxB_2 = ~PITstruct.currentLFSR.B.bit2;
    cmd.B.RELEASE_FSxB_3 = ~PITstruct.currentLFSR.B.bit1;
    cmd.B.RELEASE_FSxB_4 = ~PITstruct.currentLFSR.B.bit0;
    cmd.B.RELEASE_FSxB_5 = 1;
    cmd.B.RELEASE_FSxB_6 = 1;
    cmd.B.RELEASE_FSxB_7 = 0;

    cmd.B.RW = 1;										//write command
    cmd.B.ADR = RELEASE_FSxB_ADR;								//set address

    errorCode = FS65_SendCmdW(cmd.R);
    return(errorCode);
}


/******************************************************************************!
 *   @brief 	The function FS65_ReleaseFS1out releases the Fail Safe output FS1b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function swaps actual LFSR content (stored in the LFSR)
 *		and sends command to release safe output FS0b.
 *   @remarks 	Command should be applied to release fail safe outputs when RST
 *		error counter goes back to the state no. 0.
 *   @par Code sample
 *		FS65_ReleaseFS1out();
 *		- Command releases fail safe output FS1.
 ********************************************************************************/
uint32_t FS65_ReleaseFS1out(void){
    uint32_t errorCode;

    RELEASE_FSxB_Tx_32B_tag cmd;
    cmd.R = 0;

    errorCode = FS65_UpdateRegisterContent(WD_LFSR_ADR);					//get current LFSR content
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    PITstruct.currentLFSR.R = INTstruct.WD_LFSR.R;		//store current LFSR in PIT structure

    cmd.B.RELEASE_FSxB_0 = ~PITstruct.currentLFSR.B.bit7;
    cmd.B.RELEASE_FSxB_1 = ~PITstruct.currentLFSR.B.bit6;
    cmd.B.RELEASE_FSxB_2 = ~PITstruct.currentLFSR.B.bit5;
    cmd.B.RELEASE_FSxB_3 = ~PITstruct.currentLFSR.B.bit4;
    cmd.B.RELEASE_FSxB_4 = ~PITstruct.currentLFSR.B.bit3;
    cmd.B.RELEASE_FSxB_5 = 0;
    cmd.B.RELEASE_FSxB_6 = 1;
    cmd.B.RELEASE_FSxB_7 = 1;

    cmd.B.RW = 1;						//write command
    cmd.B.ADR = RELEASE_FSxB_ADR;				//set address

    errorCode = FS65_SendCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_ReleaseFS0andFS1out releases the Fail Safe output FS1b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function swaps actual LFSR content (stored in the LFSR)
 *		and sends command to release safe output FS0b.
 *   @remarks 	Command should be applied to release fail safe outputs when RST
 *		error counter goes back to the state no. 0.
 *   @par Code sample
 *		FS65_ReleaseFS0andFS1out();
 *		- Command releases fail safe outputs.
 ********************************************************************************/
uint32_t FS65_ReleaseFS0andFS1out(void){
    uint32_t errorCode;


    RELEASE_FSxB_Tx_32B_tag cmd;
    cmd.R = 0;

    errorCode = FS65_UpdateRegisterContent(WD_LFSR_ADR);					//get current LFSR content
    if (errorCode != FS65_RETURN_OK) {
	return errorCode;
    }

    PITstruct.currentLFSR.R = INTstruct.WD_LFSR.R;		//store current LFSR in PIT structure

    cmd.B.RELEASE_FSxB_0 = ~PITstruct.currentLFSR.B.bit7;
    cmd.B.RELEASE_FSxB_1 = ~PITstruct.currentLFSR.B.bit6;
    cmd.B.RELEASE_FSxB_2 = ~PITstruct.currentLFSR.B.bit2;
    cmd.B.RELEASE_FSxB_3 = ~PITstruct.currentLFSR.B.bit1;
    cmd.B.RELEASE_FSxB_4 = ~PITstruct.currentLFSR.B.bit0;
    cmd.B.RELEASE_FSxB_5 = 1;
    cmd.B.RELEASE_FSxB_6 = 0;
    cmd.B.RELEASE_FSxB_7 = 1;

    cmd.B.RW = 1;						//write command
    cmd.B.ADR = RELEASE_FSxB_ADR;				//set address

    errorCode = FS65_SendCmdW(cmd.R);
    return errorCode;
}

/*==================================================================================================
 *==================================  SF_OUTPUT_REQ functions  ===================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_RequestReset requests a low pulse on the RSTb - MCU reset.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function requests one Reset pulse.
 *   @remarks 	Reset can cause a data loss due to the restart of the MCU.
 *   @par Code sample
 *		FS65_RequestReset();
 *		- Command requests one Reset pulse.
 ********************************************************************************/
uint32_t FS65_RequestReset(void){
    uint32_t errorCode;

    SF_OUTPUT_REQUEST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = SF_OUTPUT_REQUEST_ADR;		//set address
    cmd.B.RSTB_REQ = 1;

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_RequestFS1B asserts FS1b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function asserts FS1b.
 *   @remarks
 *		Tdelay is controlled by the FS logic
 *   @par Code sample
 *		FS65_RequestFS1B();
 ********************************************************************************/
uint32_t FS65_RequestFS1B(void){
    uint32_t errorCode;

    SF_OUTPUT_REQUEST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = SF_OUTPUT_REQUEST_ADR;		//set address
    cmd.B.FS1B_LOW_REQ = 1;

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_RequestFS1B_DLY asserts FS1b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function asserts FS1b.
 *   @remarks
 *		Tdelay is controlled by the back-up delay
 *   @par Code sample
 *		FS65_RequestFS1B_DLY();
 ********************************************************************************/
uint32_t FS65_RequestFS1B_DLY(void){
    uint32_t errorCode;

    SF_OUTPUT_REQUEST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = SF_OUTPUT_REQUEST_ADR;		//set address
    //cmd.B.FS1B_DLY_REQ = 1;
    cmd.B.FS1B_DLY_REQ = 0;                 //add by psm
    //1 default open the SW1,  0 is closed the SW1
    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}

/******************************************************************************!
 *   @brief 	The function FS65_RequestFS0B asserts FS0b.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function asserts FS0b.
 *   @remarks
 *   @par Code sample
 *		FS65_RequestFS0B();
 ********************************************************************************/
uint32_t FS65_RequestFS0B(void){
    uint32_t errorCode;

    SF_OUTPUT_REQUEST_Tx_32B_tag cmd;
    cmd.R = 0;
    cmd.B.RW = 1;				//write command
    cmd.B.ADR = SF_OUTPUT_REQUEST_ADR;		//set address
    cmd.B.FS0B_LOW_REQ = 1;

    errorCode = FS65_SendSecureCmdW(cmd.R);
    return errorCode;
}


/*==================================================================================================
 *============================= Setters for INIT functions  =========================================
 *==================================================================================================*/

/******************************************************************************!
 *   @brief 	The function FS65_Set_INIT_VREG sets register with the given value.
 *   @par 	Include
 *		FS65xx.h
 *   @par Description
 *		This function sets content of the INIT_VREG register.
 *   @param[in] 	cmd - Desired register setting placed on the lower 16 bits.
 *   @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *   @par Code sample
 *		</para>
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_VREG();		</para>
 *		- Command sets INIT_VREG register and stores the returned status.
 *		Security bits and parity bits can be neglected, because they will be
 *		set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_VREG(uint32_t value){
    uint32_t errorCode;

    INIT_VREG_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_VREG_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if((INTstruct.INIT_VREG.R & 0x000000F3) == (value & 0x000000FF)){	//compare lower Byte only
	    return FS65_RETURN_OK;						//success
	}
	else{
	    return FS65_RETURN_ERROR;						//error -> register content NOT verified
	}
    }

}
/******************************************************************************!
 *   @brief 	The function FS65_Set_INIT_WU1 sets register with the given value.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets content of the INIT_WU1 register.
 *   @param[in]  cmd - Desired register setting placed on the lower 16 bits.
 *   @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *   @par Code sample
 *												</para>
 *			uint32_t status;					</para>
 *			status = FS65_Set_INIT_WU1();			</para>
 *			- Command sets INIT_WU1 register and stores the returned status.
 *			Security bits and parity bits can be neglected, because they will be
 *			set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_WU1(uint32_t value){
    uint32_t errorCode;

    INIT_WU1_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_WU1_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendCmdRW(cmd.R);

    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_WU1.R & 0x000000FF) == (value & 0x000000FF) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_Set_INIT_WU2 sets register with the given value.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets content of the INIT_WU2 register.
 *   @param[in]  cmd - Desired register setting placed on the lower 16 bits.
 *   @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *   @par Code sample
 *												</para>
 *			uint32_t status;					</para>
 *			status = FS65_Set_INIT_WU2();			</para>
 *			- Command sets INIT_WU2 register and stores the returned status.
 *			Security bits and parity bits can be neglected, because they will be
 *			set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_WU2(uint32_t value){

    uint32_t errorCode;

    INIT_WU2_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_WU2_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendCmdRW(cmd.R);

    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_WU2.R & 0x000000F7) == (value & 0x000000FF) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}


/******************************************************************************!
 *   @brief 	The function FS65_Set_INIT_INT sets register with the given value.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets content of the INIT_INT register.
 *   @param[in] 	cmd - Desired register setting placed on the lower 16 bits.
 *   @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *   @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_INT();		</para>
 *		- Command sets INIT_INT register and stores the returned status.
 *		Security bits and parity bits can be neglected, because they will be
 *		set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_INT(uint32_t value){
    uint32_t errorCode;

    INIT_INT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_INT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_INT.R & 0x000000FF) == (value & 0x000000FF) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *   @brief 	The function FS65_Set_INIT_INH_INT sets register with the given value.
 *   @par Include
 *		FS65xx.h
 *   @par Description
 *		This function sets content of the INIT_INH_INT register.
 *   @param[in] 	cmd - Desired register setting placed on the lower 16 bits.
 *   @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *   @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *   @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_INH_INT();		</para>
 *		- Command sets INIT_INH_INT register and stores the returned status.
 *		Security bits and parity bits can be neglected, because they will be
 *		set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_INH_INT(uint32_t value){
    uint32_t errorCode;

    INIT_INH_INT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR 	= INIT_INH_INT_ADR;
    cmd.Bytes.BYTE_FIELD = value;

    errorCode =  FS65_SendCmdRW(cmd.R);

    if(errorCode != FS65_RETURN_OK){
	return errorCode;		//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_INH_INT.R & 0x0000001F) == (value & 0x0000001F) ){		//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_FS1B_TIMING sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the FS1B_TIMING register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_FS1B_TIMING();		</para>
 *		- Command sets FS1B_TIMING register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_FS1B_TIMING(uint32_t value){

    uint32_t errorCode;

    INIT_FS1B_TIMING_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_FS1B_TIMING_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_FS1B_TIMING.R & 0x0000000F) == ((value & 0x000000F0) >>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}


/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_SUPERVISOR sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_SUPERVISOR1 register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_SUPERVISOR();		</para>
 *		- Command sets INIT_SUPERVISOR register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_SUPERVISOR(uint32_t value){
    uint32_t errorCode;

    INIT_SUPERVISOR_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_SUPERVISOR_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_SUPERVISOR.R & 0x0000000F) == ((value & 0x000000F0)>>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_FAULT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_FAULT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_FAULT();		</para>
 *		- Command sets INIT_FAULT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_FAULT(uint32_t value){
    uint32_t errorCode;

    INIT_FAULT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_FAULT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_FAULT.R & 0x0000000F) == ((value & 0x000000F0)>>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_FSSM sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_FSSM register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_FSSM();		</para>
 *		- Command sets INIT_FSSM register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_FSSM(uint32_t value){
    uint32_t errorCode;

    INIT_FSSM_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_FSSM_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_FSSM.R & 0x0000000F) == ((value & 0x000000F0)>>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}


/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_SF_IMPACT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_FS_IMPACT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_SetINIT_SF_IMPACT();		</para>
 *		- Command sets INIT_SF_IMPACT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_SF_IMPACT(uint32_t value){
    uint32_t errorCode;

    INIT_SF_IMPACT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_SF_IMPACT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_SF_IMPACT.R & 0x0000000F) == ((value & 0x000000F0)>>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_WD_CNT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_WD_CNT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_WD_CNT();		</para>
 *		- Command sets INIT_WD_CNT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_WD_CNT(uint32_t value) {
    uint32_t errorCode;

    INIT_WD_CNT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_WD_CNT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_WD_CNT.R & 0x0000000F) == ( (value & 0x000000F0) >>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}


/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_VCORE_OVUV_IMPACT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_VCORE_OVUV_IMPACT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_Set_INIT_VCORE_OVUV_IMPACT();		</para>
 *		- Command sets INIT_VCORE_OVUV_IMPACT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_VCORE_OVUV_IMPACT(uint32_t value){
    uint32_t errorCode;

    INIT_VCORE_OVUV_IMPACT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_VCORE_OVUV_IMPACT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_VCORE_OVUV_IMPACT.R & 0x0000000F) == ((value & 0x000000F0) >>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_VCCA_OVUV_IMPACT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_VCCA_OVUV_IMPACT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_SetInitVCCA_OVUV_Impact();		</para>
 *		- Command sets INIT_VCCA_OVUV_IMPACT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_VCCA_OVUV_IMPACT(uint32_t value){
    uint32_t errorCode;

    INIT_VCCA_OVUV_IMPACT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_VCCA_OVUV_IMPACT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
	return errorCode;			//error in the communication
    }
    else
    {
	if( (INTstruct.INIT_VCCA_OVUV_IMPACT.R & 0x0000000F) == ((value & 0x000000F0) >>4) ){	//compare lower Byte only
	    return FS65_RETURN_OK;	//success
	}
	else{
	    return FS65_RETURN_ERROR;	//error -> register content NOT verified
	}
    }
}

/******************************************************************************!
 *    @brief 	The function FS65_Set_INIT_VAUX_OVUV_IMPACT sets register with the given value.
 *    @par Include
 *		FS65xx.h
 *    @par Description
 *		This function sets content of the INIT_VAUX_OVUV_IMPACT register.
 *    @param[in] cmd - Desired register setting placed on the lower 16 bits.
 *    @return
 *		- FS65_RETURN_OK - Register was successfuly set. <br>
 *		- FS65_RETURN_ERROR - Operation failed.
 *    @remarks 	Commmand cmd should be a full 16-bit register setting. Parity
 *		setting and security bits in this command can be neglected,
 *		because they will be recomputed by the function automatically.
 *    @par Code sample
 *		uint32_t status;					</para>
 *		status = FS65_SetInitVAUX_OVUV_Impact();		</para>
 *		- Command sets INIT_VAUX_OVUV_IMPACT register and stores the returned
 *		status. Security bits and parity bits can be neglected, because they
 *		will be set automatically by the function.
 ********************************************************************************/
uint32_t FS65_Set_INIT_VAUX_OVUV_IMPACT(uint32_t value){
    uint32_t errorCode;

    INIT_VAUX_OVUV_IMPACT_Tx_32B_tag cmd;
    cmd.R 	= 0;
    cmd.B.RW 	= 1;
    cmd.B.ADR	= INIT_VAUX_OVUV_IMPACT_ADR;
    cmd.Bytes.BYTE_FIELD =	value;

    errorCode =  FS65_SendSecureCmdRW(cmd.R);
    if(errorCode != FS65_RETURN_OK){
    	return errorCode;			//error in the communication
    }
    else
    {
		if( (INTstruct.INIT_VAUX_OVUV_IMPACT.R & 0x0000000F) == ((value & 0x000000F0) >>4) ){	//compare lower Byte only
			return FS65_RETURN_OK;	//success
		}
		else{
			return FS65_RETURN_ERROR;	//error -> register content NOT verified
		}
    }
}


/*==================================================================================================*/
/*=============================== UPDATE REGISTER CONTENT =============================================*/
/*==================================================================================================*/

/******************************************************************************!
 *    @brief 	The function FS65_UpdateRegisterContent updates the content of
 * 		the register whose address is entered as argument.
 *		The updated content is loaded in the structure INTstruct
 *    @par Include
 *		FS65xx.h
 *    @par Description

 *		The function FS65_UpdateRegisterContent updates the content of
 * 		the register whose name is entered as argument
 *    @param[in] register_address - address of the register to be read. Should match the
 *		register names in the specification.
 *    @return
 *		uint32_t
 *    @remarks
 *    @par Code sample
 *		FS65_UpdateRegisterContent("INIT_VREG_ADR");

 ********************************************************************************/
uint32_t FS65_UpdateRegisterContent(uint32_t register_address) {
    uint32_t errorCode;
    errorCode = FS65_SendCmdR( (register_address << 9) );
    return errorCode;
}



/*==================================================================================================*/
/*=============================== PRIVATE FUNCTIONS ================================================*/
/*==================================================================================================*/

/******************************************************************************!
 *   @brief The function FS65_ComputeParity computes a parity for a specified
 *			command and returns the whole command.
 *	@par Include
 *					PwSBC.h
 * 	@par Description
 *					This function computes odd parity for the given command and
 *					returns modified command.
 * 	@param[in] cmd - 16-bit command.
 * 	@return 	Modified 16-bit command including odd parity.
 *	@remarks 	If a secured command is being used, then the
 *				FS65_ComputeSecurityBits function must be applied before
 *				computing parity.
 *	@par Code sample
 *																		</para>
 *			uint32_t cmd_with_parity;									</para>
 *			cmd_with_parity = FS65_ComputeParity(0b1010111000000001);	</para>
 *			- This function computes parity for the command (IO_out - AMUX) and
 *			returns its modified version in the variable cmd_with_ parity.
 ********************************************************************************/
uint32_t FS65_ComputeParity(uint32_t cmd){
    uint8_t sum = 0;
    uint8_t i = 0;

    for(i = 0;i < 16;i++){
	if(i != 8){
	    sum = sum + (uint8_t)((cmd >> i) & 0x00000001);
	}
    }
    if(sum%2 == 0){			//even number -> P = 1
	cmd = cmd | 0x00000100;
    }
    else{
	cmd = cmd & 0xFFFFFEFF;
    }
    return cmd;
}


/******************************************************************************!
 *   @brief The function FS65_ComputeSecurityBits computes the security bits for a specified command and returns
 *			the whole command.
 *	@par Include
 *					PwSBC.h
 * 	@par Description
 *					This function computes 4 security bits for the given command and
 *					returns modified command.
 * 	@param[in] cmd - 16-bit command.
 * 	@return 	Modified 16-bit command including 4 security bits.
 *	@remarks 	This function should be used only for secure commands and has
 *				to be used before applying FS65_ComputeParity function.
 *	@par Code sample
 *																	</para>
 *			uint32_t cmd_secured;									</para>
 *			cmd_secured = FS65_ComputeParity(0b1010101001000000);	</para>
 *			- This function computes security bits for the command (MODE) and returns
 *			its modified version in the variable cmd_secured.
 ********************************************************************************/
uint32_t FS65_ComputeSecurityBits(uint32_t cmd){
    register32_struct command;

    command.R = cmd;
    command.B.bit0 = command.B.bit6;
    command.B.bit1 = command.B.bit7;
    command.B.bit2 = ~command.B.bit4;
    command.B.bit3 = ~command.B.bit5;

    return command.R;
}


/******************************************************************************!
 *   @brief The function FS65_ProcessSPI treats the data received on the SPI MISO line.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function reads word received on the SPI MISO line,
 *					decodes the frame address and stores received word in
 *					the global structures.
 *	@remarks 	This function is called everytime by the PwSBC_SendCmdXX and
 *				PwSBC_SendSecureCmdXX. This calling causes that the global
 *				structures are updated with every command sent to the PwSBC.
 *	@par Code sample
 *			FS65_ProcessSPI();
 *			- This function treats received command and stores its content in
 *			the global structures.
 ********************************************************************************/
void FS65_ProcessSPI(void){

    uint32_t address = 0;

    //SPIstruct.response = DSPI_Read(DSPI_NB);
    SPIstruct.response = rxData;
    SPIstruct.statusPwSBC.R = SPIstruct.response >> 8;

    address = (SPIstruct.readCmd & 0x00007E00) >> 9;									//mask register address from the read command
    switch(address){
		case	INIT_VREG_ADR				:	INTstruct.INIT_VREG.R = SPIstruct.response;           break;
		case	INIT_WU1_ADR				:	INTstruct.INIT_WU1.R = SPIstruct.response;            break;
		case	INIT_WU2_ADR				:	INTstruct.INIT_WU2.R = SPIstruct.response;            break;
		case 	INIT_INT_ADR				:	INTstruct.INIT_INT.R = SPIstruct.response;            break;
		case	INIT_INH_INT_ADR			:	INTstruct.INIT_INH_INT.R = SPIstruct.response;        break;
		case	LONG_DURATION_TIMER_ADR		:	INTstruct.LONG_DURATION_TIMER.R = SPIstruct.response; break;
		case	HW_CONFIG_ADR				:	INTstruct.HW_CONFIG.R = SPIstruct.response;           break;
		case	WU_SOURCE_ADR				:	INTstruct.WU_SOURCE.R = SPIstruct.response;           break;
		case	DEVICE_ID_ADR				:	INTstruct.DEVICE_ID.R = SPIstruct.response;           break;
		case	IO_INPUT_ADR				:	INTstruct.IO_INPUT.R = SPIstruct.response;            break;
		case	DIAG_VPRE_ADR				:	INTstruct.DIAG_VPRE.R = SPIstruct.response;           break;
		case	DIAG_VCORE_ADR				:	INTstruct.DIAG_VCORE.R = SPIstruct.response;          break;
		case	DIAG_VCCA_ADR				:	INTstruct.DIAG_VCCA.R = SPIstruct.response;           break;
		case	DIAG_VAUX_ADR				:	INTstruct.DIAG_VAUX.R = SPIstruct.response;           break;
		case	DIAG_VSUP_VCAN_ADR			:	INTstruct.DIAG_VSUP_VCAN.R = SPIstruct.response;      break;
		case	DIAG_CAN_FD_ADR				:	INTstruct.DIAG_CAN_FD.R = SPIstruct.response;         break;
		case	DIAG_CAN_LIN_ADR			:	INTstruct.DIAG_CAN_LIN.R = SPIstruct.response;        break;
		case	DIAG_SPI_ADR				:	INTstruct.DIAG_SPI.R = SPIstruct.response;            break;
		case	MODE_ADR					:	INTstruct.MODE.R = SPIstruct.response;                break;
		case	REG_MODE_ADR				:	INTstruct.REG_MODE.R = SPIstruct.response;            break;
		case	IO_OUT_AMUX_ADR				:	INTstruct.IO_OUT_AMUX.R = SPIstruct.response;         break;
		case	CAN_LIN_MODE_ADR			:	INTstruct.CAN_LIN_MODE.R = SPIstruct.response;        break;
		case	LDT_AFTER_RUN_1_ADR			:	INTstruct.LDT_AFTER_RUN_1.R = SPIstruct.response;     break;
		case	LDT_AFTER_RUN_2_ADR			:	INTstruct.LDT_AFTER_RUN_2.R = SPIstruct.response;     break;
		case	LDT_WAKE_UP_1_ADR			: 	INTstruct.LDT_WAKE_UP_1.R = SPIstruct.response;       break;
		case	LDT_WAKE_UP_2_ADR			: 	INTstruct.LDT_WAKE_UP_2.R = SPIstruct.response;       break;
		case	LDT_WAKE_UP_3_ADR			: 	INTstruct.LDT_WAKE_UP_3.R = SPIstruct.response;       break;
		case	INIT_FS1B_TIMING_ADR		:	INTstruct.INIT_FS1B_TIMING.R = SPIstruct.response;    break;
		case	BIST_ADR					: 	INTstruct.BIST.R = SPIstruct.response;                break;
		case	INIT_SUPERVISOR_ADR			:	INTstruct.INIT_SUPERVISOR.R = SPIstruct.response;     break;
		case	INIT_FAULT_ADR				:	INTstruct.INIT_FAULT.R = SPIstruct.response;          break;
		case	INIT_FSSM_ADR				:	INTstruct.INIT_FSSM.R = SPIstruct.response;           break;
		case	INIT_SF_IMPACT_ADR			:	INTstruct.INIT_SF_IMPACT.R = SPIstruct.response;      break;
		case	WD_WINDOW_ADR				:	INTstruct.WD_WINDOW.R = SPIstruct.response;           break;
		case	WD_LFSR_ADR				    :	INTstruct.WD_LFSR.R = SPIstruct.response;             break;
		case	WD_ANSWER_ADR				:	INTstruct.WD_ANSWER.R = SPIstruct.response;           break;
		case	RELEASE_FSxB_ADR			:	INTstruct.RELEASE_FSxB.R = SPIstruct.response;        break;
		case	SF_OUTPUT_REQUEST_ADR		:	INTstruct.SF_OUTPUT_REQUEST.R = SPIstruct.response;   break;
		case	INIT_WD_CNT_ADR				:	INTstruct.INIT_WD_CNT.R = SPIstruct.response;         break;
		case	DIAG_SF_IOS_ADR				: 	INTstruct.DIAG_SF_IOS.R = SPIstruct.response;         break;
		case	WD_COUNTER_ADR				:	INTstruct.WD_COUNTER.R = SPIstruct.response;          break;
		case	DIAG_SF_ERR_ADR				: 	INTstruct.DIAG_SF_ERR.R = SPIstruct.response;         break;
		case	INIT_VCORE_OVUV_IMPACT_ADR	:	INTstruct.INIT_VCORE_OVUV_IMPACT.R = SPIstruct.response; break;
		case	INIT_VCCA_OVUV_IMPACT_ADR	:	INTstruct.INIT_VCCA_OVUV_IMPACT.R = SPIstruct.response;  break;
		case	INIT_VAUX_OVUV_IMPACT_ADR	:	INTstruct.INIT_VAUX_OVUV_IMPACT.R = SPIstruct.response;  break;
		case	DEVICE_ID_FS_ADR			:	INTstruct.DEVICE_ID_FS.R = SPIstruct.response;           break;
    }
}

/******************************************************************************!
 *   @brief Sends a read command and waits until the end of transmission.
 *	@par Include:
 *					FS65xx.h
 * 	@par Description:
 *					Function sends a read command to the PwSBC and waits
 *					the end of transmission. Data received on the MISO pin are
 *					decoded and the global structure is refreshed using this
 *					value.
 * 	@param[in] cmd - 	16-bit read command (parity bit should be 0 for all read
 *						commands).
 * 	@return 	0 - Command was sent without any error. <br>
 *				(10)D - SPI disconnected or no SPI answer. <br>
 *				(11)D - SPI_G error detected.
 *	@remarks 	This presents the lowest level of the PwSBC driver to send
 *				commands to PwSBC and is being used by the other functions.
 *				Function is designed just for read commands.
 ********************************************************************************/
uint32_t FS65_SendCmdR(uint32_t cmd){
    uint32_t stockPriority = 0;

//    stockPriority = INTC_0.CPR[0].B.PRI;			//save current priority
//    INTC_0.CPR[0].B.PRI = INT_CEIL_PRIORITY;		//block DSPI resource

    SPIstruct.writeCmd = 0;					//NO write cmd
    SPIstruct.readCmd = cmd;				//set read cmd

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
    //DSPI_Send(DSPI_NB, DSPI_CS, 0xABBA);
    SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
    txData = SPIstruct.readCmd;
    FS65_ProcessSPI();									//read received cmd and save it in the global structure

    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
		if(SPIstruct.response == 0xFFFF){
			SPIstruct.writeCmd = 0;								//NO write cmd
			SPIstruct.readCmd = (DIAG_SPI_ADR <<9);				//set read cmd to Diag SPI command
			//DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
			SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
			FS65_ProcessSPI();
			if((INTstruct.DIAG_SPI.B.bit0 & INTstruct.DIAG_SPI.B.bit2) == 0){
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> SPI_G error
			}
			else{
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				//PwSBC_SignalError(ERR_SPI_NO_COMMUN);
				return FS65_RETURN_ERROR;										//error -> no answer on SPI
			}
		}
		else{
//			INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
			return FS65_RETURN_ERROR;										//error -> SPI_G error
		}
    }else{
//		INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
		return FS65_RETURN_OK;
    }

}

/******************************************************************************!
 *   @brief Sends a write command and waits until the end of transmission.
 *	@par Include:
 *					FS65xx.h
 * 	@par Description:
 *					Function sends a write command to the PwSBC and waits
 *					the end of transmission. Data received on the MISO pin are
 *					decoded and the global structure is refreshed using this
 *					value.
 * 	@param[in] cmd - 	16-bit write command. Parity bit will be computed and
 *						set automatically by this function.
 * 	@return 	0 - Command was sent without any error. <br>
 *				(10)D - SPI disconnected or no SPI answer. <br>
 *				(11)D - SPI_G error detected.
 *	@remarks 	This presents the lowest level of the PwSBC driver to send
 *				commands to PwSBC and is being used by the other functions.
 *				This function simply sends a write command, but does not apply
 *				any verification after writing.
 ********************************************************************************/
uint32_t FS65_SendCmdW(uint32_t cmd){
    uint32_t stockPriority = 0;

//    stockPriority = INTC_0.CPR[0].B.PRI;				//save current priority
//    INTC_0.CPR[0].B.PRI = INT_CEIL_PRIORITY;			//block DSPI resource

    SPIstruct.writeCmd = cmd;
    SPIstruct.writeCmd = FS65_ComputeParity(SPIstruct.writeCmd);
    SPIstruct.readCmd = cmd & 0x7E00;							//create read cmd

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.writeCmd);		//send the write command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.writeCmd, &rxData);
    txData = SPIstruct.writeCmd;
    FS65_ProcessSPI();											//read received cmd and save it in the global structure

    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
		if(SPIstruct.response == 0xFFFF){
			SPIstruct.writeCmd = 0;								//NO write cmd
			SPIstruct.readCmd = (DIAG_SPI_ADR <<9);				//set read cmd to Diag SPI command
			//DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
			SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
			FS65_ProcessSPI();
			if((INTstruct.DIAG_SPI.B.bit0 & INTstruct.DIAG_SPI.B.bit2) == 0){
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> SPI_G error
			}else{
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				//PwSBC_SignalError(ERR_SPI_NO_COMMUN);
				return FS65_RETURN_ERROR;										//error -> no answer on SPI
			}
		}else{
//			INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
			return FS65_RETURN_ERROR;										//error -> SPI_G error
		}
    }else{
//    	INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
    	return FS65_RETURN_OK;
    }
}


/******************************************************************************!
 *   @brief 	Sends a write and then a read command and waits until the end
 *			of transmission.
 *	@par Include:
 *					FS65xx.h
 * 	@par Description:
 *					Function sends a write command followed by a read command
 *					to PwSBC. Data sent on the MISO during the read command is
 *					stocked in global structure, so it can be used by functions
 *					on higher level to verify register content (if the write
 *					command was applied correctly or not).
 * 	@param[in] cmd - 	16-bit write or read command (function recomputes
 *						the R/W bit automatically so either read or write
 *						command can be given). Parity bit will be computed
 *						and set automatically by this function.
 * 	@return 	0 - Command was sent without any error. <br>
 *				(10)D - SPI disconnected or no SPI answer. <br>
 *				(11)D - SPI_G error detected.
 *	@remarks 	This presents the lowest level of the PwSBC driver to send
 *				commands to PwSBC and is being used by the other functions.
 *				This function should be used for Read/Write commands.
 ********************************************************************************/
uint32_t  FS65_SendCmdRW(uint32_t cmd){
    uint32_t stockPriority = 0;

//    stockPriority = INTC_0.CPR[0].B.PRI;			//save current priority
//    INTC_0.CPR[0].B.PRI = INT_CEIL_PRIORITY;		//block DSPI resource

    SPIstruct.writeCmd = cmd | 0x8000;							//create write cmd
    SPIstruct.readCmd = cmd & 0x7E00;							//create read cmd
    SPIstruct.writeCmd = FS65_ComputeParity(SPIstruct.writeCmd);

   // DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.writeCmd);			//send the write command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.writeCmd, &rxData);
    txData = SPIstruct.writeCmd;
    //SPIstruct.response = DSPI_Read(DSPI_NB);					//read result and release inp. buffer
    SPIstruct.response = rxData;
    SPIstruct.statusPwSBC.R = SPIstruct.response >> 8;

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);				//send the read command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
    txData = SPIstruct.readCmd;
    FS65_ProcessSPI();												//read received cmd and save it in the global structure

    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
		if(SPIstruct.response == 0xFFFF){
			SPIstruct.writeCmd = 0;								//NO write cmd
			SPIstruct.readCmd = (DIAG_SPI_ADR <<9);				//set read cmd to Diag SPI command
			//DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
			SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
			FS65_ProcessSPI();
			if((INTstruct.DIAG_SPI.B.bit0 & INTstruct.DIAG_SPI.B.bit2) == 0){
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> SPI_G error
			}else{
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				//PwSBC_SignalError(ERR_SPI_NO_COMMUN);
				return FS65_RETURN_ERROR;										//error -> no answer on SPI
			}
		}else{
//			INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
			return FS65_RETURN_ERROR;										//error -> SPI_G error
		}
    }else{
//    	INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
    	return FS65_RETURN_OK;
    }
}


/******************************************************************************!
 *   @brief 	Sends a write command with secure bits and then a read command
 and waits until the end of transmission.
 *	@par Include:
 *					FS65xx.h
 * 	@par Description:
 *					Function sends a secured write command (commands that use
 *					four security bits) followed by a read command to PwSBC.
 *					Data sent on the MISO during the read command is stocked in
 *					global structure, so it can be used by functions on higher
 *					level to verify register content (if the write command was
 *					applied correctly or not).
 * 	@param[in] cmd - 	16-bit write or read command (function recomputes
 *						the R/W bit automatically so either read or write command
 *						can be given). Parity bit and security bits will be
 *						computed and set automatically by this function.
 * 	@return 	0 - Command was sent without any error. <br>
 *				(10)D - SPI disconnected or no SPI answer. <br>
 *				(11)D - SPI_G error detected.
 *	@remarks 	This presents the lowest level of the PwSBC driver to send
 *				commands to PwSBC and is being used by the other functions.
 *				This function should be used for secured Read/Write commands.
 ********************************************************************************/
uint32_t FS65_SendSecureCmdRW(uint32_t cmd){
    uint32_t stockPriority = 0;

//    stockPriority = INTC_0.CPR[0].B.PRI;			//save current priority
//    INTC_0.CPR[0].B.PRI = INT_CEIL_PRIORITY;	//block DSPI resource

    SPIstruct.writeCmd = cmd | 0x8000;									//create write cmd
    SPIstruct.readCmd = cmd & 0x7E00;									//create read cmd


    SPIstruct.writeCmd = FS65_ComputeSecurityBits(SPIstruct.writeCmd);
    SPIstruct.writeCmd = FS65_ComputeParity(SPIstruct.writeCmd);

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.writeCmd);					//send the write command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.writeCmd, &rxData);
    txData = SPIstruct.writeCmd;
    //SPIstruct.response = DSPI_Read(DSPI_NB);							//read result and release inp. buffer
    SPIstruct.response = rxData;
    SPIstruct.statusPwSBC.R = SPIstruct.response >> 8;

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);						//send the read command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
    txData = SPIstruct.readCmd;
    FS65_ProcessSPI();														//read received cmd and save it in the global structure

    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
		if(SPIstruct.response == 0xFFFF){
			SPIstruct.writeCmd = 0;								//NO write cmd
			SPIstruct.readCmd = (DIAG_SPI_ADR <<9);				//set read cmd to Diag SPI command
			//DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
			SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
			FS65_ProcessSPI();
			if((INTstruct.DIAG_SPI.B.bit0 & INTstruct.DIAG_SPI.B.bit2) == 0){
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> SPI_G error
			}else{
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> no answer on SPI
			}
		}else{
//			INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
			return FS65_RETURN_ERROR;										//error -> SPI_G error
		}
    }else{
//    	INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
    	return FS65_RETURN_OK;
    }
}

/******************************************************************************!
 *   @brief 	Sends a write command with secure bits and waits until the end
 *			of transmission.
 *	@par Include:
 *					FS65xx.h
 * 	@par Description:
 *					Function sends a secured write command (commands that use
 *					four security bits) to the PwSBC and waits the end of
 *					transmission. Data received on the MISO pin are decoded
 *					and the global structure is refreshed using this value.
 * 	@param[in] cmd - 	16-bit write command. Parity bit and four security bits
 *						will be computed and set automatically by this function.
 * 	@return 	0 - Command was sent without any error. <br>
 *				(10)D - SPI disconnected or no SPI answer. <br>
 *				(11)D - SPI_G error detected.
 *	@remarks 	This presents the lowest level of the PwSBC driver to send
 *				commands to PwSBC and is being used by the other functions.
 *				This function simply sends a write command, but does not apply
 *				any verification after writing.
 ********************************************************************************/
uint32_t FS65_SendSecureCmdW(uint32_t cmd){
    uint32_t stockPriority = 0;

//    stockPriority = INTC_0.CPR[0].B.PRI;			//save current priority
//    INTC_0.CPR[0].B.PRI = INT_CEIL_PRIORITY;	//block DSPI resource

    SPIstruct.writeCmd = cmd;
    SPIstruct.writeCmd = FS65_ComputeSecurityBits(SPIstruct.writeCmd);
    SPIstruct.writeCmd = FS65_ComputeParity(SPIstruct.writeCmd);

    //DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.writeCmd);				//send the write command, function waits for result
    SpiIf_TransmitSbc(SPIstruct.writeCmd, &rxData);
    txData = SPIstruct.writeCmd;
    FS65_ProcessSPI();													//read received cmd and save it in the global structure

    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
		if(SPIstruct.response == 0xFFFF){
			SPIstruct.writeCmd = 0;								//NO write cmd
			SPIstruct.readCmd = (DIAG_SPI_ADR <<9);				//set read cmd to Diag SPI command
			//DSPI_Send(DSPI_NB, DSPI_CS, SPIstruct.readCmd);	//send the read command, function waits for result
			SpiIf_TransmitSbc(SPIstruct.readCmd, &rxData);
			FS65_ProcessSPI();
			if((INTstruct.DIAG_SPI.B.bit0 & INTstruct.DIAG_SPI.B.bit2) == 0){
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				return FS65_RETURN_ERROR;										//error -> SPI_G error
			}else{
//				INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
				//PwSBC_SignalError(ERR_SPI_NO_COMMUN);
				return FS65_RETURN_ERROR;										//error -> no answer on SPI
			}
		}else{
//			INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
			return FS65_RETURN_ERROR;										//error -> SPI_G error
		}
    }else{
//    	INTC_0.CPR[0].B.PRI = stockPriority;					//release DSPI resource
    	return FS65_RETURN_OK;
    }
}

/******************************************************************************!
 *   @brief The function FS65_GetVoltageTight reads a value from the ADC and recomputes it into a voltage considering
 *			a tight voltage range ratio.
 *	@par Include
 *					PwSBC.h
 * 	@par Description
 *					This function reads value from ADC and recomputes it into voltage
 *					considering tight voltage range ratio.
 * 	@return 	Voltage [V] that was measured on the active AMUX channel.
 *				The returned value is computed as follows:
 *				(Vcca/ADC_RESOLUTION)*x*VAMUX_TG_X, where:
 *				- Vcca - if the parameter ADC_SOURCE_CALIB is defined in
 *				the global defines, then its value is used as a Vcca. If this
 *				parameter is not defined, then either 3.3 or 5.0 V is used
 *				instead depending on the Vcca_HW bit. This bit is checked and
 *				the appropriate voltage is chosen automatically by this function.
 *				- ADC_RESOLUTION - this parameter is defined in the global
 *				defines. By default for the MPC5744P the 12-bit ADC is used,
 *				so the number (2^12)-1 = 4095 corresponds to this parameter.
 *				- x - number obtained from ADC in the 12-bit range (value from
 *				0 till 4095)
 *				- VAMUX_TG_X - divider ration tight input voltage range.
 *				(VAMUX_TG_X = 2 for Vcca = 5 V; VAMUX_TG_X = 3 for Vcca = 3.3 V)
 *	@remarks 	This function works only when the tight range is being used.
 *				This range allows to measure voltages from 2 till 10 V. If
 *				a wider range is necessary, then FS65_GetVoltageWide should be
 *				used instead.
 *				- Example of computations (Vcca = 3.3 V, ADC_SOURCE_CALIB is not
 *				defined, ADC_RESOLUTION = 4095 by default, VAMUX_TG_X = 3,
 *				x = 1089):	(3.3/4095)*1089*3 = 2.63V
 *	@par Code sample
 *													</para>
 *			float voltage;							</para>
 *			voltage = FS65_GetVoltageTight();		</para>
 *			- This function reads value from ADC (depending on actual AMUX channel)
 *			and returns value as a voltage [V].
 ********************************************************************************/
float FS65_GetVoltageTight(void){
#if 0
    double voltage = 0;
    uint32_t x;
#ifdef ADC_SOURCE_CALIB
    float treshold = 4.15;
#endif

//x = ADC_GetChannelValue(ADC_NB, ADC_CH);
#ifdef ADC_SOURCE_CALIB																	//reference voltage for ADC is stored in ADC_SOURCE_CALIB
    voltage = (ADC_SOURCE_CALIB / ADC_RESOLUTION) * x;
    if(ADC_SOURCE_CALIB < treshold){													//choose between 3.3V and 5V ratio for computations
	voltage *= VAMUX_TG_33;
    }
    else{
	voltage *= VAMUX_TG_5;
    }
#else																										//reference voltage is set to Vcca
    if(INTstruct.HW_CONFIG.B.VCCA_HW == 0){							//choose between 3.3V and 5V used as Vcca
	voltage = (3.3 / ADC_RESOLUTION) * x;
	voltage *= VAMUX_TG_33;
    }
    else{
	voltage = (5.0 / ADC_RESOLUTION) * x;
	voltage *= VAMUX_TG_5;
    }
#endif

    return (float)voltage;

#endif
    return 0;
}

/******************************************************************************!
 *   @brief The function FS65_GetVoltageWide reads a value from ADC and recomputes it into a voltage considering
 *			a wide voltage range ratio.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function reads value from ADC and recomputes it into voltage
 *					considering wide voltage range ratio.
 * 	@return 	Voltage [V] that was measured on the active AMUX channel.
 *				The returned value is computed as follows:
 *				(Vcca/ADC_RESOLUTION)*x*VAMUX_TG_X, where:
 *				- Vcca - if the parameter ADC_SOURCE_CALIB is defined in
 *				the global defines, then its value is used as a Vcca. If this
 *				parameter is not defined, then either 3.3 or 5.0 V is used
 *				instead depending on the Vcca_HW bit. This bit is checked
 *				and the appropriate voltage is chosen automatically by this
 *				function.
 *				- ADC_RESOLUTION - this parameter is defined in the global
 *				defines. By default for the MPC5744P the 12-bit ADC is used,
 *				so the number (2^12)-1 = 4095 corresponds to this parameter.
 *				- x - number obtained from ADC in the 12-bit range (value from 0
 *				till 4095)
 *				- VAMUX_WD_X - divider ration tight input voltage range
 *				(VAMUX_WD_X = 5 for Vcca = 5 V; VAMUX_WD_X = 7 for Vcca = 3.3 V)
 *	@remarks 	This function works for wide range of voltages
 *				(from 2 till 24 V). If the voltage is less than 10 V than usage
 *				of tight range (function FS65_GetVoltageTight) will be more
 *				precise.
 *				- Example of computations (Vcca = 3.3 V, ADC_SOURCE_CALIB is
 *				not defined, ADC_RESOLUTION = 4095 by default, VAMUX_WD_X = 7,
 *				x = 3054): (3.3/4095)*3054*7 = 17.23V
 *	@par Code sample
 *													</para>
 *			float voltage;							</para>
 *			voltage = FS65_GetVoltageWide();		</para>
 *			- This function reads value from ADC (depending on actual AMUX channel)
 *			and returns value as a voltage [V].
 ********************************************************************************/
float FS65_GetVoltageWide(void){
#if 0
    double voltage = 0;
    uint32_t x;
#ifdef ADC_SOURCE_CALIB
    float treshold = 4.15;
#endif

//x = ADC_GetChannelValue(ADC_NB, ADC_CH);
#ifdef ADC_SOURCE_CALIB																	//reference voltage for ADC is stored in ADC_SOURCE_CALIB
    voltage = (ADC_SOURCE_CALIB / ADC_RESOLUTION) * x;
    if(ADC_SOURCE_CALIB < treshold){													//choose between 3.3V and 5V ratio for computations
	voltage *= VAMUX_WD_33;
    }
    else{
	voltage *= VAMUX_WD_5;
    }
#else																										//reference voltage is set to Vcca
    if(INTstruct.HW_CONFIG.B.VCCA_HW == 0){							//choose between 3.3V and 5V used as Vcca
	voltage = (3.3 / ADC_RESOLUTION) * x;
	voltage *= VAMUX_WD_33;
    }
    else{
	voltage = (5.0 / ADC_RESOLUTION) * x;
	voltage *= VAMUX_WD_5;
    }
#endif

    return (float)voltage;
#endif
    return 0;
}

/******************************************************************************!
 *   @brief The function FS65_GetVoltage reads a value from the ADC and recomputes it into a voltage considering
 *			no voltage ratio.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function reads value from ADC and recomputes it into voltage
 *					considering no voltage ratio.
 * 	@return 	Voltage [V] that was measured on the active AMUX channel.
 *				The returned value is computed as follows:
 *				(Vcca/ADC_RESOLUTION)*x, where:
 *				- Vcca - if the parameter ADC_SOURCE_CALIB is defined in
 *				the global defines, then its value is used as a Vcca.
 *				If this parameter is not defined, then either 3.3 or 5.0 V
 *				is used instead depending on the Vcca_HW bit. This bit is
 *				checked and the appropriate voltage is chosen automatically
 *				by this function.
 *				- ADC_RESOLUTION - this parameter is defined in the global
 *				defines. By default for the MPC5744P the 12-bit ADC is used,
 *				so the number (2^12)-1 = 4095 corresponds to this parameter.
 *				- x - number obtained from ADC in the 12-bit range (value from
 *				0 till 4095)
 *	@remarks 	This function should be used for voltages between 0 and
 *				Vcca - voltages that does not use any ratio (Vref, Die
 *				temperature sensor). For other volatges please use either
 *				FS65_GetVoltageTight or FS65_GetVoltageWide.
 *				- Example of computations (Vcca = 5.0 V, ADC_SOURCE_CALIB is not
 *				defined, ADC_RESOLUTION = 4095 by default, x = 2056):
 *				(5.0/4095)*2056 = 2.51V
 *	@par Code sample
 *												</para>
 *			float voltage;						</para>
 *			voltage = FS65_GetVoltage();		</para>
 *			- This function reads value from ADC and returns value as a voltage [V].
 ********************************************************************************/
float FS65_GetVoltage(void){
#if 0
    double voltage = 0;
    uint32_t x;

//x = ADC_GetChannelValue(ADC_NB, ADC_CH);
#ifdef ADC_SOURCE_CALIB																	//reference voltage for ADC is stored in ADC_SOURCE_CALIB
    voltage = (ADC_SOURCE_CALIB / ADC_RESOLUTION) * x;
#else																										//reference voltage is set to Vcca
    if(INTstruct.HW_CONFIG.B.VCCA_HW == 0){							//choose between 3.3V and 5V used as Vcca
	voltage = (3.3 / ADC_RESOLUTION) * x;
    }
    else{
	voltage = (5.0 / ADC_RESOLUTION) * x;
    }
#endif

    return (float)voltage;
#endif
    return 0;
}

/******************************************************************************!
 *   @brief The function FS65_GetTemperature reads a value from the ADC and recomputes it into a temperature
 *			(no voltage ratio).
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function reads value from ADC and recomputes it into
 *					temperature.
 * 	@return 	Temperature in degrees of Celsius. Temerature is computed using
 *				the following formula:
 *				t = ((V*1000)-VAMUX_TP_0)/VAMUX_TP_C0, where:
 *				- V - voltage that is computed as shown in the function
 *				FS65_GetVoltage.
 *				- VAMUX_TP_0 - typical voltage for zero temperature (0 degrees
 *				of Celsius)
 *				- VAMUX_TP_CO - temperature coefficient for the implemented
 *				sensor
 *	@remarks 	Temperature coefficients are set by default in the global
 *				defines.
 *				- Example of computations (Vcca = 5.0 V, ADC_SOURCE_CALIB is not
 *				defined, ADC_RESOLUTION = 4095 by default, x = 2056, V = 2.51 V,
 *				VAMUX_TP_0 = 850 mV, VAMUX_TP_CO = 10 mV/degrees of Celsius):
 *				t = ((2.51*1000)-850)10 = 166 deg.
 *	@par Code sample
 *											</para>
 *			float temp;						</para>
 *			temp = FS65_GetTemperature();	</para>
 *			- This function reads value from ADC and returns it as a die temperature.
 ********************************************************************************/
float FS65_GetTemperature(void){
#if 0
    double voltage = 0;
    double temp = 0;
    uint32_t x;

//x = ADC_GetChannelValue(ADC_NB, ADC_CH);
#ifdef ADC_SOURCE_CALIB																	//reference voltage for ADC is stored in ADC_SOURCE_CALIB
    voltage = (ADC_SOURCE_CALIB / ADC_RESOLUTION) * x;
#else																										//reference voltage is set to Vcca
    if(INTstruct.HW_CONFIG.B.VCCA_HW == 0){							//choose between 3.3V and 5V used as Vcca
	voltage = (3.3 / ADC_RESOLUTION) * x;
    }
    else{
	voltage = (5.0 / ADC_RESOLUTION) * x;
    }
#endif

    // Temperature computations from input voltage:
    // temp				temperature in degrees of Celsius
    // VAMUX_TP_0		nominal voltage at 0 degrees of Celsius
    // VAMUX_TP_CO		coefficient in mV/degrees of Celsius

    temp = ((voltage * 1000) - VAMUX_TP_0)/VAMUX_TP_CO;

    return (float)temp;
#endif
    return 0;
}



/*==================================================================================================*/
/*=============================== Interrupt routines================================================*/
/*==================================================================================================*/


/*---------------------------------------------------------------------------\
 * PIT interruption service routine for WD refresh called by a TIF flag
 \****************************************************************************/

/*******************************************************************************
 *   @brief The function FS65xx_IsrPIT_WD is a PIT interrupt service routine for WD refresh.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function is an interrupt service routine for the periodical
 *					WD refresh that is launched by Periodical Interrupt Timer
 *					(PIT). On the beginning function gets actual LFSR value from
 *					the PwSBC, makes control computations and sends WD answer.
 *					If WD is refreshed without any error, function clears PIT
 *					interrupt flag and ends. If any error occurs, error strategy
 *					will be used reach a successfulWD refresh (see ALGORITHMS
 *					for details).
 *	@remarks 	PIT channel used for periodical WD refresh is defined in global
 *				defines as a PIT_WD_CH. This function shall be registered as
 *				an interrupt service routine for specified interrupt vector with
 *				specified priority (parameter INT_WD_PRIORITY in the global
 *				defines). This priority is set by default as the highest one.
 *	@par Code sample
 *			INTC_InstallINTCInterruptHandler(FS65xx_IsrPIT_WD,59,INT_WD_PRIORITY);
 *			- This function registers FS65xx_IsrPIT_WD interrupt routine with interrupt
 *			vector no. 59 and priority defined by parameter INT_WD_PRIORITY
 *			(placed in global defines).
 ********************************************************************************/
void FS65_IsrPIT_WD(void){
#if 0
    static uint32_t nbWDrefresh = 0;
    static uint32_t FSOUTreleased = 0;

    nbWDrefresh++;

    //DEBUG
    // SIUL_ToggleIO(SIUL_PA1);
    //DEBUG

    FS65_UpdateRegisterContent(WD_LFSR_ADR);					//get current LFSR content
    PITstruct.WD_answer = FS65_ComputeLFSR(INTstruct.WD_LFSR.R);
    FS65_RefreshWD(PITstruct.WD_answer);

    FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);				//refresh ERR counter
    FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);				//refresh ERR counter
    FS65_UpdateRegisterContent(WD_COUNTER_ADR);					//refresh WD counter

    if((FSOUTreleased == 0) & (nbWDrefresh >= 7)){
	  FSOUTreleased = 1;
	  FS65_ReleaseFS0andFS1out();
    }

    if(ADCstruct.scanVoltage.R > 0){
//ADC_StartNormalConversion(ADC_NB, ADC_MASK);				//start new ADC conversion if required by scanVoltage mask
    }

//PIT_ClearFlag(PIT_WD_CH);		//clear interrupt TIF flag
#endif
}

/*****************************************************************************\
 * EXTernal pin interruption service routine called by RFDF flag
 \****************************************************************************/

/*******************************************************************************
 *   @brief The function FS65xx_IsrSIUL is an SIUL external interrupt service routine.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function is an interrupt service routine for external event
 *					handling. This function reads general status register and looks
 *					for the interrupt source. If the an active interrupt flag
 *					in the FS65xx has been found, function calls appropriate
 *					event handler.
 *	@remarks 	Input that is being used for external interrupt handling is
 *				defined by parameter SIUL_INT_EIRQ. This function shall be registered
 *				as an interrupt service routine for specified interrupt vector
 *				with specified priority (parameter INT_SIUL_PRIORITY in the
 *				global defines).
 *	@par Code sample
 *			INTC_InstallINTCInterruptHandler(FS65xx_IsrSIUL,41, INT_SIUL_PRIORITY);
 *			- This function registers FS65xx_IsrSIUL interrupt routine with interrupt
 *			vector no. 41 (corresponds to EIRQ no. 7) and priority defined by
 *			parameter INT_SIUL_PRIORITY (placed in global defines).
 ********************************************************************************/
void FS65_IsrSIUL(void){
#if 0
// Any get function to update FS65xx status field
    FS65_UpdateRegisterContent(INIT_VREG_ADR);

// check SPI_G event
    if(SPIstruct.statusPwSBC.B.SPI_G == 1){
	FS65_UpdateRegisterContent(DIAG_SPI_ADR);
	FS65_SPI_INT_Callback();
    }

// check WU event
    if(SPIstruct.statusPwSBC.B.WU == 1)
    {
		FS65_UpdateRegisterContent(WU_SOURCE_ADR);
	    if(INTstruct.WU_SOURCE.B.PHY_WU == 1)
		{    //event in the physical layer of the CAN or LIN bus
			FS65_UpdateRegisterContent(DIAG_CAN_FD_ADR);
			FS65_UpdateRegisterContent(DIAG_CAN_LIN_ADR);
			FS65_PHYWU_INT_Callback();
		}
        if(INTstruct.WU_SOURCE.B.AUTO_WU == 1)
		{	//auto-wake up
			FS65_AutoWU_INT_Callback();
		}
        if(INTstruct.WU_SOURCE.B.LDT_WU == 1)
		{		//LDT-wake up
			FS65_LDTWU_INT_Callback();
	    }
    }

// check CAN_G event
    if(SPIstruct.statusPwSBC.B.CAN_G == 1){
	FS65_UpdateRegisterContent(DIAG_CAN_FD_ADR);
	FS65_UpdateRegisterContent(DIAG_CAN_LIN_ADR);
	FS65_CAN_INT_Callback();

    }

// check LIN_G event
    if(SPIstruct.statusPwSBC.B.LIN_G == 1){
	FS65_UpdateRegisterContent(DIAG_CAN_LIN_ADR);
	FS65_LIN_INT_Callback();
    }

// check IO_G event
    if(SPIstruct.statusPwSBC.B.IO_G == 1){
	FS65_UpdateRegisterContent(IO_INPUT_ADR);
	//write your code there...
	FS65_IO_INT_Callback();
    }

// check Vpre_G event
    if(SPIstruct.statusPwSBC.B.Vpre_G == 1){
	FS65_UpdateRegisterContent(DIAG_VPRE_ADR);
	FS65_VPRE_INT_Callback();
    }

// check Vcore_G event
    if(SPIstruct.statusPwSBC.B.Vcore_G == 1){
	FS65_UpdateRegisterContent(DIAG_VCORE_ADR);
	FS65_VCORE_INT_Callback();
    }

// Vothers_G
    if(SPIstruct.statusPwSBC.B.Vothers_G == 1){
	FS65_UpdateRegisterContent(DIAG_VCCA_ADR);
	FS65_UpdateRegisterContent(DIAG_VAUX_ADR);
	FS65_UpdateRegisterContent(DIAG_VSUP_VCAN_ADR);
	FS65_VXXX_INT_Callback();
    }

    SIUL_ClearExtIntFlag(SIUL_INT_EIRQ);											//clear interrupt EIF flag
#endif
}


/*---------------------------------------------------------------------------\
 * ADC interruption service routine called by EOC flag
 \****************************************************************************/

/***************************************************************************
 *   @brief The function FS65xx_IsrADC si an ADC interrupt service routine.
 *	@par Include
 *					FS65xx.h
 * 	@par Description
 *					This function is an interrupt service routine to process results
 *					from AD conversions (called with every end of conversion).
 *					Depending on the active AMUX channel, function treats ADC
 *					results and stores them in the global structures. Then AMUX
 *					channel is switched and function ends (for details see
 *					ALGORITHMS).
 *	@remarks 	ADC module that is being used for ADC conversions is defined by
 *				ADC_NB parameter in global defines. Priority of the ADC interrupt
 *				is defined by INT_ADC_PRIORITY parameter.
 *	@par Code sample
 *			INTC_InstallINTCInterruptHandler(FS65xx_IsrADC,(62 + 20*ADC_NB),
 *				INT_ADC_PRIORITY);
 *			- This function registers FS65xx_IsrADC function as an interrupt service
 *			routine for interrupt vector no. 62 (corresponds to the end of
 *			conversion event for ADC module no. 0) with priority
 *			INT_ADC_PRIORITY.
 ********************************************************************************/
void FS65_IsrADC(void){
#if 0
    uint8_t actualCH = 0;
    uint8_t nbAMUX = 0;
    uint8_t mask = 0;
    uint8_t i = 0;

    actualCH = (uint8_t)INTstruct.IO_OUT_AMUX.B.AMUX;				//actual channel used by ADC

/* store actual channel to the structure */
    switch(actualCH){
	case	AMUX_VREF	    :	ADCstruct.actualVoltage.Vref  = FS65_GetVoltage();       break;
	case	AMUX_VSNS_WIDE	:	ADCstruct.actualVoltage.VsnsW = FS65_GetVoltageWide();   break;
	case	AMUX_IO0_WIDE	:	ADCstruct.actualVoltage.IO0W  = FS65_GetVoltageWide();   break;
	case	AMUX_IO5_WIDE	:	ADCstruct.actualVoltage.IO5W  = FS65_GetVoltageWide();   break;
	case	AMUX_VSNS_TIGHT	:	ADCstruct.actualVoltage.VsnsT = FS65_GetVoltageTight();  break;
	case	AMUX_IO0_TIGHT	: 	ADCstruct.actualVoltage.IO0T  = FS65_GetVoltageTight();  break;
	case	AMUX_IO5_TIGHT	: 	ADCstruct.actualVoltage.IO5T  = FS65_GetVoltageTight();  break;
	case	AMUX_TEMP	    : 	ADCstruct.actualVoltage.Temp  = FS65_GetTemperature();   break;
    }

/* switch AMUX to the following masked channel and start next conversion */
    nbAMUX = actualCH;

    for(i = 0;i < 8;i++){
	  nbAMUX++;
	  if(nbAMUX >= 8){				//if higher number than number of channels -> return to the start index (0)
	    nbAMUX = 0;
	  }

	  mask = 1 << nbAMUX;				//mask just one bit every time - masks are powers of 2

	  if((ADCstruct.scanVoltage.R & mask) > 0){		//if the specified channel is masked
	    FS65_SwitchAMUXchannel(nbAMUX);									//change AMUX channel
	    break;
	  }
    }

    ADC_ClearAllEOCflags(ADC_NB);										//clear EOC flags
#endif

}


void FS65_FreshWatchdog(void)
{
	  static uint32_t nbWDrefresh = 0;
	  static uint32_t FSOUTreleased = 0;

//	  if(0 == sbc_start)
//	  {
//		  return;
//	  }


	  nbWDrefresh++;

	  FS65_UpdateRegisterContent(WD_LFSR_ADR);					//get current LFSR content
	  PITstruct.WD_answer = FS65_ComputeLFSR(INTstruct.WD_LFSR.R);
	  FS65_RefreshWD(PITstruct.WD_answer);

	  FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);				//refresh ERR counter
	  FS65_UpdateRegisterContent(DIAG_SF_ERR_ADR);				//refresh ERR counter
	  FS65_UpdateRegisterContent(WD_COUNTER_ADR);				//refresh WD counter

	  if((FSOUTreleased == 0) & (nbWDrefresh >= 7)){
//		  FSOUTreleased = 1;  //do only once
		  FS65_ReleaseFS0andFS1out();
//		 sbc_start = 0;
	  }
}


