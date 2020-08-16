///////////////////////////////////////////////////////////////////////////////////////////////////
// 锟� NXP B.V. 2014. All rights reserved.
// Disclaimer
// 1.         The NXP Software/Source Code is provided to Licensee "AS IS" without any warranties of
// any kind. NXP makes no warranties to Licensee and shall not indemnify Licensee or hold it harmless
// for any reason related to the NXP Software/Source Code or otherwise be liable to the NXP customer.
// The NXP customer acknowledges and agrees that the NXP Software/Source Code is provided AS-IS and
// accepts all risks of utilizing the NXP Software under the conditions set forth according to this
// disclaimer.
//
// 2.         NXP EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
// NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS. NXP SHALL HAVE NO LIABILITY TO THE NXP CUSTOMER,
// OR ITS SUBSIDIARIES, AFFILIATES, OR ANY OTHER THIRD PARTY FOR ANY DAMAGES, INCLUDING WITHOUT
// LIMITATION, DAMAGES RESULTING OR ALLEGDED TO HAVE RESULTED FROM ANY DEFECT, ERROR OR OMMISSION IN
// THE NXP SOFTWARE/SOURCE CODE, THIRD PARTY APPLICATION SOFTWARE AND/OR DOCUMENTATION, OR AS A
// RESULT OF ANY INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHT OF ANY THIRD PARTY. IN NO EVENT
// SHALL NXP BE LIABLE FOR ANY INCIDENTAL, INDIRECT, SPECIAL, EXEMPLARY, PUNITIVE, OR CONSEQUENTIAL
// DAMAGES (INCLUDING LOST PROFITS) SUFFERED BY NXP CUSTOMER OR ITS SUBSIDIARIES, AFFILIATES,
// OR ANY OTHER THIRD PARTY ARISING OUT OF OR RELATED TO THE NXP SOFTWARE/SOURCE CODE EVEN IF
// NXP HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
///////////////////////////////////////////////////////////////////////////////////////////////////

// $id:$
// XML Version: V1.2  Software Version: V2.0  Date: 07/08/2014  Time: 11:37

//--------------------------------------------------------------------------------
// pre-processor directive
#ifndef NXP_TJA1100_FUNCTIONS_H
#define NXP_TJA1100_FUNCTIONS_H

//--------------------------------------------------------------------------------
// general header include
#include "NXP_TJA1100_Defines.h"


//--------------------------------------------------------------------------------
// register depending enumerations
//--------------------------------------------------------------------------------
// register 0x00
//---------------------------------------------------
#define TJA1101_BASIC_CONTROL_REG      (0x00)
#define TJA1101_BASIC_CONTROL_REG_MASK (0xFFE0)
//--------------------------------------
typedef enum
{
  TJA1101_RST_PHY_RESET	= 1,
  TJA1101_RST_NORMAL_OPERATION = 0
}TJA1101_RESET_t;

#define TJA1101_RST_MASK   (0x8000)   // bit [15]
#define TJA1101_RST_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_LB_LOOPBACK_MODE	= 1,
  TJA1101_LB_NORMAL_OPERATION = 0
}TJA1101_LOOPBACK_t;

#define TJA1101_LB_MASK   (0x4000)   // bit [14]
#define TJA1101_LB_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_SS_LSB_1 = 1,
  TJA1101_SS_LSB_0 = 0
}TJA1101_SPEED_SELECT_LSB_t;

#define TJA1101_SS_LSB_MASK   (0x2000)   // bit [13]
#define TJA1101_SS_LSB_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_ANE_DISABLE_AUTONEGOTIATION_PROCESS = 0
}TJA1101_AUTONEG_ENABLE_t;

#define TJA1101_ANE_MASK   (0x1000)   // bit [12]
#define TJA1101_ANE_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_PWRD_POWER_DOWN_INTO_STANDBY	= 1,
  TJA1101_PWRD_NORMAL_OPERATION	= 0
}TJA1101_POWER_DOWN_t;

#define TJA1101_PWRD_MASK   (0x800)   // bit [11]
#define TJA1101_PWRD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_ISL_ISOLATION_OF_PHY_FROM_MII_RMII = 1,
  TJA1101_ISL_NORMAL_OPERATION	= 0
}TJA1101_ISOLATE_t;

#define TJA1101_ISL_MASK   (0x400)   // bit [10]
#define TJA1101_ISL_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_RAN_NORMAL_OPERATION = 0
}TJA1101_RE_AUTONEG_t;

#define TJA1101_RAN_MASK   (0x200)   // bit [9]
#define TJA1101_RAN_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_DM_FULL_DUPLEX = 1
}TJA1101_DUPLEX_MODE_t;

#define TJA1101_DM_MASK   (0x100)   // bit [8]
#define TJA1101_DM_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_CT_DISABLE_COL_SIGNAL_TEST = 0
}TJA1101_COLLISION_TEST_t;

#define TJA1101_CT_MASK   (0x80)   // bit [7]
#define TJA1101_CT_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_SS_MSB_0 = 0,
  TJA1101_SS_MSB_1 = 1
}TJA1101_SPEED_SELECT_MSB_t;

#define TJA1101_SS_MSB_MASK   (0x40)   // bit [6]
#define TJA1101_SS_MSB_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_UDE_EN_MII_TRANSMIT_WITHOUT_PHY_VALID_LINK	= 1,
  TJA1101_UDE_EN_MII_TRANSMIT_ONLY_WHEN_PHY_VALID_LINK	= 0
}TJA1101_Unidirectional_enable_t;

#define TJA1101_UDE_MASK   (0x20)   // bit [5]
#define TJA1101_UDE_SHIFT  (5)

/* a write access value other than 01 is ignored. */
typedef enum
{
	BASE_10MBIT_S   = 0,	// SPEED_SELECT_LSB = 0 & SPEED_SELECT_MSB = 0;
	BASE_100MBIT_S  = 1,	// SPEED_SELECT_LSB = 1 & SPEED_SELECT_MSB = 0;
	BASE_1000MBIT_S = 2,	// Not implemented.
	BASE_RESERVED   = 3		// Not implemented.
}TJA1101_SPEED_SELECT_t;


//---------------------------------------------------
// register 0x01
//---------------------------------------------------
#define TJA1101_BASIC_STATUS_REG      (0x01)
#define TJA1101_BASIC_STATUS_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_T4_PHY_100BASET4_CAPABLE	= 1,
  TJA1101_100BASE_T4_PHY_NOT_100BASET4_CAPABLE	= 0
}TJA1101_100BASE_T4_t;

#define TJA1101_100BASE_T4_MASK   (0x8000)   // bit [15]
#define TJA1101_100BASE_T4_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_X_FD_PHY_100BASEX_FD_CAPABLE	= 1,
  TJA1101_100BASE_X_FD_PHY_NOT_100BASETX_FD_CAPABLE	= 0
}TJA1101_100BASE_X_Full_Duplex_t;

#define TJA1101_100BASE_X_FD_MASK   (0x4000)   // bit [14]
#define TJA1101_100BASE_X_FD_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_X_HD_PHY_100BASEX_HD_CAPABLE	= 1,
  TJA1101_100BASE_X_HD_PHY_NOT_100BASETX_HD_CAPABLE	= 0
}TJA1101_100BASE_X_Half_Duplex_t;

#define TJA1101_100BASE_X_HD_MASK   (0x2000)   // bit [13]
#define TJA1101_100BASE_X_HD_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_10MBPS_FD_PHY_10MBPS_FD_CAPABLE	= 1,
  TJA1101_10MBPS_FD_PHY_NOT_10MBPS_FD_CAPABLE	= 0
}TJA1101_10Mbps_Full_Duplex_t;

#define TJA1101_10MBPS_FD_MASK   (0x1000)   // bit [12]
#define TJA1101_10MBPS_FD_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_10MBPS_HD_PHY_10MBPS_HD_CAPABLE	= 1,
  TJA1101_10MBPS_HD_PHY_NOT_10MBPS_HD_CAPABLE	= 0
}TJA1101_10Mbps_Half_Duplex_t;

#define TJA1101_10MBPS_HD_MASK   (0x800)   // bit [11]
#define TJA1101_10MBPS_HD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_T2_FD_PHY_100BASET2_FD_CAPABLE	= 1,
  TJA1101_100BASE_T2_FD_PHY_NOT_100BASET2_FD_CAPABLE	= 0
}TJA1101_100BASE_T2_Full_Duplex_t;

#define TJA1101_100BASE_T2_FD_MASK   (0x400)   // bit [10]
#define TJA1101_100BASE_T2_FD_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_T2_HD_PHY_100BASET2_HD_CAPABLE	= 1,
  TJA1101_100BASE_T2_HD_PHY_NOT_100BASET2_HD_CAPABLE	= 0
}TJA1101_100BASE_T2_Half_Duplex_t;

#define TJA1101_100BASE_T2_HD_MASK   (0x200)   // bit [9]
#define TJA1101_100BASE_T2_HD_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_ES_EXTENDED_STATUS_INFORMATION_IN_REG_15	= 1,
  TJA1101_ES_NO_EXTENDED_INFORMATION_IN_REG_15	= 0
}TJA1101_EXTENDED_STATUS_t;

#define TJA1101_ES_MASK   (0x100)   // bit [8]
#define TJA1101_ES_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_UDA_PHY_ABLE_TO_TRANSMIT_FROM_MII_WITHOUT_VALID_LINK	= 1,
  TJA1101_UDA_PHY_ABLE_TO_TRANSMIT_FROM_MII_ONLY_WHEN_VALID_LINK = 0
}TJA1101_Unidirectional_ability_t;

#define TJA1101_UDA_MASK   (0x80)   // bit [7]
#define TJA1101_UDA_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_MFPS_PHY_WILL_ACCEPT_PREAMBLE_SUPPRESSED_MANAGEMENT_FRAMES	= 1,
  TJA1101_MFPS_PHY_WILL_NOT_ACCEPT_PREAMBLE_SUPPRESSED_MANAGEMENT_FRAMES = 0
}TJA1101_MF_Preamble_Suppression_t;

#define TJA1101_MFPS_MASK   (0x40)   // bit [6]
#define TJA1101_MFPS_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_ANC_AUTONEGOTIATION_PROCESS_COMPLETED	= 1,
  TJA1101_ANC_AUTONEGOTIATION_PROCESS_NOT_COMPLETED	= 0
}TJA1101_AUTONEG_COMPLETE_t;

#define TJA1101_ANC_MASK   (0x20)   // bit [5]
#define TJA1101_ANC_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1101_RF_REMOTE_FAULT_CONDITION_DETECTED	= 1,
  TJA1101_RF_NO_REMOTE_FAULT_CONDITION_DETECTED	= 0
}TJA1101_REMOTE_FAULT_t;

#define TJA1101_RF_MASK   (0x10)   // bit [4]
#define TJA1101_RF_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1101_ANA_PHY_IS_ABLE_TO_PERFORM_AUTONEGOTIATION	= 1,
  TJA1101_ANA_PHY_NOT_ABLE_TO_PERFORM_AUTONEGOTIATION	= 0
}TJA1101_AUTONEG_ABILITY_t;

#define TJA1101_ANA_MASK   (0x08)   // bit [3]
#define TJA1101_ANA_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1101_LS_LINK_IS_UP	= 1,
  TJA1101_LS_LINK_IS_DOWN = 0
}TJA1101_LINK_STATUS_t;

#define TJA1101_LS_MASK   (0x04)   // bit [2]
#define TJA1101_LS_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1101_JD_JABBER_CONDITION_DETECTED	= 1,
  TJA1101_JD_NO_JABBER_CONDITION_DETECTED	= 0
}TJA1101_JABBER_DETECT_t;

#define TJA1101_JD_MASK   (0x02)   // bit [1]
#define TJA1101_JD_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1101_EC_EXTENDED_REGISTER_CAPABILITIES	= 1,
  TJA1101_EC_BASIC_REGISTER_SET_CAPABILITIES = 0
}TJA1101_EXTENDED_CAPABILITY_t;

#define TJA1101_EC_MASK   (0x01)   // bit [0]
#define TJA1101_EC_SHIFT  (0)



//---------------------------------------------------
// register 0x02
//---------------------------------------------------
#define TJA1101_PHY_IDENTIFIER_1_REG      (0x02)
#define TJA1101_PHY_IDENTIFIER_1_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1101_PHY_ID_1_t;

#define TJA1101_PHY_ID1_MASK   (0xFFFF)   // bit [15:0]
#define TJA1101_PHY_ID1_SHIFT  (0)



//---------------------------------------------------
// register 0x03
//---------------------------------------------------
#define TJA1101_PHY_IDENTIFIER_2_REG      (0x03)
#define TJA1101_PHY_IDENTIFIER_2_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1101_PHY_ID_2_t;

#define TJA1101_PHY_ID2_MASK   (0xFC00)   // bit [15:10]
#define TJA1101_PHY_ID2_SHIFT  (10)
//--------------------------------------
typedef unsigned short TJA1101_TYPE_No_t;

#define TJA1101_TYPE_MASK   (0x3F0)   // bit [9:4]
#define TJA1101_TYPE_SHIFT  (4)
//--------------------------------------
typedef unsigned short TJA1101_REVISION_No_t;

#define TJA1101_REV_MASK   (0x0F)   // bit [3:0]
#define TJA1101_REV_SHIFT  (0)




//---------------------------------------------------
// register 0x0F
//---------------------------------------------------
#define TJA1101_EXTENDED_STATUS_REG      (0x0F)
#define TJA1101_EXTENDED_STATUS_REG_MASK (0xF0C0)
//--------------------------------------
typedef enum
{
  TJA1101_1000BASE_X_FD_PHY_1000BASEX_FD_CAPABLE	= 1,
  TJA1101_1000BASE_X_FD_PHY_NOT_1000BASEX_FD_CAPABLE = 0
}TJA1101_1000BASE_X_Full_Duplex_t;

#define TJA1101_1000BASE_X_FD_MASK   (0x8000)   // bit [15]
#define TJA1101_1000BASE_X_FD_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_1000BASE_X_HD_PHY_1000BASEX_HD_CAPABLE	= 1,
  TJA1101_1000BASE_X_HD_PHY_NOT_1000BASEX_HD_CAPABLE	= 0
}TJA1101_1000BASE_X_Half_Duplex_t;

#define TJA1101_1000BASE_X_HD_MASK   (0x4000)   // bit [14]
#define TJA1101_1000BASE_X_HD_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_1000BASE_T_FD_PHY_1000BASET_FD_CAPABLE	= 1,
  TJA1101_1000BASE_T_FD_PHY_NOT_1000BASET_FD_CAPABLE	= 0
}TJA1101_1000BASE_T_Full_Duplex_t;

#define TJA1101_1000BASE_T_FD_MASK   (0x2000)   // bit [13]
#define TJA1101_1000BASE_T_FD_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_1000BASE_T_HD_PHY_1000BASET_HD_CAPABLE	= 1,
  TJA1101_1000BASE_T_HD_PHY_NOT_1000BASET_HD_CAPABLE	= 0
}TJA1101_1000BASE_T_Half_Duplex_t;

#define TJA1101_1000BASE_T_HD_MASK   (0x1000)   // bit [12]
#define TJA1101_1000BASE_T_HD_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_100BASE_T1_PHY_ABLE_TO_1_PAIR_100BASE_T1_100MBPS	= 1,
  TJA1101_100BASE_BR_PHY_NOT_ABLE_TO_1_PAIR_100BASE_T1_100MBPS	= 0
}TJA1101_100BASE_T1_t;

#define TJA1101_100BASE_T1_MASK   (0x80)   // bit [7]
#define TJA1101_100BASE_T1_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_1000BASE_RTPGE_PHY_ABLE_TO_RTPGE	= 1,
  TJA1101_1000BASE_RTPGE_PHY_NOT_ABLE_TO_RTPGE	= 0
}TJA1101_1000BASE_RTPGE_t;

#define TJA1101_1000BASE_RTPGE_MASK   (0x40)   // bit [6]
#define TJA1101_1000BASE_RTPGE_SHIFT  (6)




//---------------------------------------------------
// register 0x11
//---------------------------------------------------
#define TJA1101_EXTENDED_CONTROL_REG      (0x11)
#define TJA1101_EXTENDED_CONTROL_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1101_LC_LINK_CONTROL_ENABLED	= 1,
  TJA1101_LC_LINK_CONTROL_DISABLED	= 0
}TJA1101_LINK_CONTROL_t;

#define TJA1101_LC_MASK   (0x8000)   // bit [15]
#define TJA1101_LC_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_PM_NO_CHANGE		= 0,		// No change
  TJA1101_PM_NORMAL_MODE	= 3,		// Normal mode(command)
  TJA1101_PM_SLEEP_REQUEST	= 11,		// Sleep Request mode(command)
  TJA1101_PM_STANDBY_MODE	= 12		// Standby mode(command)
}TJA1101_POWER_MODE_t;

#define TJA1101_PM_MASK   (0x7800)   // bit [14:11]
#define TJA1101_PM_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_SJT_SLAVE_JITTER_TEST_ENABLED	 = 1,
  TJA1101_SJT_SLAVE_JITTER_TEST_DISABLED = 0
}TJA1101_SLAVE_JITTER_TEST_t;

#define TJA1101_SJT_MASK   (0x400)   // bit [10]
#define TJA1101_SJT_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_TRS_FORCES_RESTART_OF_TRAINING_PHASE	= 1,	/* Forces a restart of training phase */
  TJA1101_TRS_STOPS_TRAINING_PHASE	= 0					/* halts the training phase */
}TJA1101_TRAINING_RESTART_t;

#define TJA1101_TRS_MASK   (0x200)   // bit [9]
#define TJA1101_TRS_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_TM_NO_TEST_MODE	= 0,
  TJA1101_TM_BROADR_REACH_TEST_MODE_1	= 1,
  TJA1101_TM_BROADR_REACH_TEST_MODE_2	= 2,
  TJA1101_TM_BROADR_REACH_TEST_MODE_3	= 3,
  TJA1101_TM_BROADR_REACH_TEST_MODE_4	= 4,
  TJA1101_TM_BROADR_REACH_TEST_MODE_5	= 5
}TJA1101_TEST_MODE_t;

#define TJA1101_TM_MASK   (0x1C0)   // bit [8:6]
#define TJA1101_TM_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_CBT_FORCES_TDR_BASED_CABLE_TEST	= 1,
  TJA1101_CBT_STOPS_TDR_BASED_CABLE_TEST	= 0
}TJA1101_CABLE_TEST_t;

#define TJA1101_CBT_MASK   (0x20)   // bit [5]
#define TJA1101_CBT_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1101_LM_INTERNAL_LOOPBACK	= 0,
  TJA1101_LM_EXTERNAL_LOOPBACK1	= 1,
  TJA1101_LM_EXTERNAL_LOOPBACK2	= 2,
  TJA1101_LM_REMOTE_LOOPBACK	= 3
}TJA1101_LOOPBACK_MODE_t;

#define TJA1101_LM_MASK   (0x18)   // bit [4:3]
#define TJA1101_LM_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1101_CFEN_CONFIGURATION_REGISTER_ACCESS_ENABLED	= 1,
  TJA1101_CFEN_CONFIGURATION_REGISTER_ACCESS_DISABLED	= 0
}TJA1101_CONFIG_EN_t;

#define TJA1101_CFEN_MASK   (0x04)   // bit [2]
#define TJA1101_CFEN_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1101_WR_START_SENDING_IDLE_OR_WUR_SYMBOLS_AS_BUS_WAKEUP_SIGNAL	= 1,
  TJA1101_WR_NO_WAKEUP_SIGNAL_TO_BE_SENT	= 0
}TJA1101_WAKE_REQUEST_t;

#define TJA1101_WR_MASK   (0x01)   // bit [0]
#define TJA1101_WR_SHIFT  (0)





//---------------------------------------------------
// register 0x12
//---------------------------------------------------
#define TJA1101_CONFIGURATION_1_REG      (0x12)
#define TJA1101_CONFIGURATION_1_REG_MASK (0xCFF7)
//--------------------------------------
typedef enum
{
  TJA1101_MS_PHY_CONFIGURED_AS_MASTER	= 1,
  TJA1101_MS_PHY_CONFIGURED_AS_SLAVE	= 0
}TJA1101_MASTER_SLAVE_t;

#define TJA1101_MS_MASK   (0x8000)   // bit [15]
#define TJA1101_MS_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_WAKEUP_FORWARD_LOCALLY	= 1,
  TJA1101_WAKEUP_NOT_FORWARD_LOCALLY = 0
}TJA1101_WAKEUP_LOCAL_t;

#define TJA1101_WAKEUP_LOCAL_MASK   (0x4000)   // bit [14]
#define TJA1101_WAKEUP_LOCAL_SHIFT  (14)
//--------------------------------------
typedef enum
{
	TJA1101_DOES_NOT_REACT_REMOTE_WAKEUP = 0,
	TJA1101_REACT_REMOTE_WAKEUP = 1
}TJA1101_REACT_REMOTE_WAKEUP_t;

#define TJA1101_REACT_REMOTE_WAKEUP_MASK	(0x0800)
#define TJA1101_REACT_REMOTE_WAKEUP_SHIFT	(11)	// bit [11]
//--------------------------------------
typedef enum
{
  TJA1101_DOES_NOT_REACT_LOCAL_WAKEUP	= 0,
  TJA1101_REACT_LOCAL_WAKEUP	= 1
}TJA1101_REACT_LOCAL_WAKEUP_t;

#define TJA1101_REACT_LOCALWAKEUP_MASK   (0x0400)   // bit [10]
#define TJA1101_REACT_LOCALWAKEUP_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_MIIM_MII_MODE_ENABLED	= 0,
  TJA1101_MIIM_RMII_MODE_ENABLED_50MHZ_INPUT_AT_REFCLK_IN	= 1,
  TJA1101_MIIM_RMII_MODE_ENABLED_50MHZ_OUTPUT_AT_REFCLK_OUT	= 2,
  TJA1101_MIIM_REVERSE_MII_MODE	= 3
}TJA1101_MII_Mode_t;

#define TJA1101_MIIM_MASK   (0x300)   // bit [9:8]
#define TJA1101_MIIM_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_MIID_STANDARD_OUTPUT_DRIVER_STRENGTH	= 0,
  TJA1101_MIID_REDUCED_OUTPUT_DRIVER_STRENGTH	= 1
}TJA1101_MII_DRIVER_t;

#define TJA1101_MIID_MASK   (0x80)   // bit [7]
#define TJA1101_MIID_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_SCNFM_CONFIRMATION_NEEDED_TO_GO_TO_SLEEP	= 1,
  TJA1101_SCNFM_NO_CONFIRMATION_NEEDED_TO_GO_TO_SLEEP	= 0
}TJA1101_SLEEP_CONFIRM_t;

#define TJA1101_SCNFM_MASK   (0x40)   // bit [6]
#define TJA1101_SCNFM_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_LPS_WUR_ENABLED	= 0,
  TJA1101_LPS_WUR_DISABLED	= 1
}TJA1101_LPS_WUR_SETTINGS_t;

#define TJA1101_LPS_WUR_MASK   (0x20)   // bit [5]
#define TJA1101_LPS_WUR_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1101_SLEEP_ACKNOWLEDGE_TIMER_DISABLED = 0,
  TJA1101_SLEEP_ACKNOWLEDGE_TIMER_ENABLED
}TJA1101_SLEEP_ACK_t;

#define TJA1101_SLEEP_ACK_MASK	(0x10)	// bit[4]
#define TJA1101_SLEEP_ACK_SHIFT	(4)
//--------------------------------------
typedef enum
{
  TJA1101_WAKEUP_FORWARD_REMOTELY	= 1,
  TJA1101_WAKEUP_NOT_FORWARD_REMOTELY = 0
}TJA1101_FWD_REMOTE_WAKEUP_t;

#define TJA1101_FWD_REMOTE_WAKEUP_MASK   (0x04)   // bit [2]
#define TJA1101_FWD_REMOTE_WAKEUP_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1101_APD_AUTONOMOUS_POWER_DOWN_ENABLED	= 1,
  TJA1101_APD_AUTONOMOUS_POWER_DOWN_DISABLED	= 0
}TJA1101_AUTO_PWD_t;

#define TJA1101_APD_MASK   (0x02)   // bit [1]
#define TJA1101_APD_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1101_LPSACT_AUTONOMOUS_TRANSITION_NORMAL_TO_SLEEP_REQUEST_ENABLED	= 1,
  TJA1101_LPSACT_AUTONOMOUS_TRANSITION_NORMAL_TO_SLEEP_REQUEST_DISABLED	= 0
}TJA1101_LPS_ACTIVE_t;

#define TJA1101_LPSACT_MASK   (0x01)   // bit [0]
#define TJA1101_LPSACT_SHIFT  (0)



//---------------------------------------------------
// register 0x13
//---------------------------------------------------
#define TJA1101_CONFIGURATION_2_REG      (0x13)
#define TJA1101_CONFIGURATION_2_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1101_PHYAD4to0_t;

#define TJA1101_PHYAD_MASK   (0xF800)   // bit [15:11]
#define TJA1101_PHYAD_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_SQIA_SQI_AVERAGING_32_SYMBOLS	= 0,
  TJA1101_SQIA_SQI_AVERAGING_64_SYMBOLS	= 1,
  TJA1101_SQIA_SQI_AVERAGING_128_SYMBOLS = 2,
  TJA1101_SQIA_SQI_AVERAGING_256_SYMBOLS = 3
}TJA1101_SQI_Averaging_t;

#define TJA1101_SQIA_MASK   (0x600)   // bit [10:9]
#define TJA1101_SQIA_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_SQIWL_NO_WARNING_LIMIT			= 0,
  TJA1101_SQIWL_CLASS_A_SQI_WARNING_LIMIT	= 1,
  TJA1101_SQIWL_CLASS_B_SQI_WARNING_LIMIT	= 2,
  TJA1101_SQIWL_CLASS_C_SQI_WARNING_LIMIT	= 3,
  TJA1101_SQIWL_CLASS_D_SQI_WARNING_LIMIT	= 4,
  TJA1101_SQIWL_CLASS_E_SQI_WARNING_LIMIT	= 5,
  TJA1101_SQIWL_CLASS_F_SQI_WARNING_LIMIT	= 6,
  TJA1101_SQIWL_CLASS_G_SQI_WARNING_LIMIT	= 7
}TJA1101_SQI_WLIMIT_t;

#define TJA1101_SQIWL_MASK   (0x1C0)   // bit [8:6]
#define TJA1101_SQIWL_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_SQIFL_NO_FAIL_LIMIT	= 0,
  TJA1101_SQIFL_CLASS_A_SQI_FAIL_LIMIT	= 1,
  TJA1101_SQIFL_CLASS_B_SQI_FAIL_LIMIT	= 2,
  TJA1101_SQIFL_CLASS_C_SQI_FAIL_LIMIT	= 3,
  TJA1101_SQIFL_CLASS_D_SQI_FAIL_LIMIT	= 4,
  TJA1101_SQIFL_CLASS_E_SQI_FAIL_LIMIT	= 5,
  TJA1101_SQIFL_CLASS_F_SQI_FAIL_LIMIT	= 6,
  TJA1101_SQIFL_CLASS_G_SQI_FAIL_LIMIT	= 7
}TJA1101_SQI_FAILLIMIT_t;

#define TJA1101_SQIFL_MASK   (0x38)   // bit [5:3]
#define TJA1101_SQIFL_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1101_JE_PACKETS_UP_TO_16KB_ARE_SUPPORTED	= 1,
  TJA1101_JE_PACKETS_UP_TO_4KB_ARE_SUPPORTED	= 0
}TJA1101_JUMBO_ENABLE_t;

#define TJA1101_JE_MASK   (0x04)   // bit [2]
#define TJA1101_JE_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1101_SRT_400NS_TIMEOUT	= 0,
  TJA1101_SRT_1MS_TIMEOUT	= 1,
  TJA1101_SRT_4MS_TIMEOUT	= 2,
  TJA1101_SRT_16MS_TIMEOUT	= 3
}TJA1101_SLEEP_REQUEST_TO_t;

#define TJA1101_SRT_MASK   (0x03)   // bit [1:0]
#define TJA1101_SRT_SHIFT  (0)




//---------------------------------------------------
// register 0x14
//---------------------------------------------------
#define TJA1101_SYMBOL_ERROR_COUNTER_REG      (0x14)
#define TJA1101_SYMBOL_ERROR_COUNTER_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA110x_SYM_ERR_CNT_t;

#define TJA1101_SYM_ERR_CNT_MASK   (0xFFFF)   // bit [15:0]
#define TJA1101_SYM_ERR_CNT_SHIFT  (0)




//---------------------------------------------------
// register 0x15
//---------------------------------------------------
#define TJA1101_INTERRUPT_SOURCE_REG      (0x15)
#define TJA1101_INTERRUPT_SOURCE_REG_MASK (0xFFEF)
//--------------------------------------
typedef enum
{
  TJA1101_PO_POWER_ON_DETECTED	= 1,
  TJA1101_PO_NO_POWER_ON_DETECTED = 0
}TJA1101_PWON_t;

#define TJA1101_PO_MASK   (0x8000)   // bit [15]
#define TJA1101_PO_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_WU_WAKE_UP_DETECTED	= 1,
  TJA1101_WU_NO_WAKE_UP_DETECTED	= 0
}TJA1101_WAKEUP_t;

#define TJA1101_WU_MASK   (0x4000)   // bit [14]
#define TJA1101_WU_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_WUR_WAKE_UP_REQUEST_DETECTED	= 1,
  TJA1101_WUR_NO_WAKE_UP_REQUEST_DETECTED	= 0
}TJA1101_WUR_RECEIVED_t;

#define TJA1101_WUR_MASK   (0x2000)   // bit [13]
#define TJA1101_WUR_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_LPSR_LPS_CODE_GROUPS_RECEIVED	= 1,
  TJA1101_LPSR_NO_LPS_CODE_GROUPS_RECEIVED	= 0
}TJA1101_LPS_RECEIVED_t;

#define TJA1101_LPSR_MASK   (0x1000)   // bit [12]
#define TJA1101_LPSR_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_PHYIF_PHY_INITIALIZATION_ERROR_DETECTED	= 1,
  TJA1101_PHYIF_NO_PHY_INITIALIZATION_ERROR	= 0
}TJA1101_PHY_INIT_FAIL_t;

#define TJA1101_PHYIF_MASK   (0x800)   // bit [11]
#define TJA1101_PHYIF_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_LSF_LINK_STATUS_CHANGED_FROM_OK_TO_FAIL	= 1,
  TJA1101_LSF_NO_CHANGE_OF_LINK_STATUS	= 0
}TJA1101_LINK_STATUS_FAIL_t;

#define TJA1101_LSF_MASK   (0x400)   // bit [10]
#define TJA1101_LSF_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_LSU_LINK_STATUS_CHANGED_FROM_FAIL_TO_OK	= 1,
  TJA1101_LSU_NO_CHANGE_OF_LINK_STATUS	= 0
}TJA1101_LINK_STATUS_UP_t;

#define TJA1101_LSU_MASK   (0x200)   // bit [9]
#define TJA1101_LSU_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_SYMBE_SYMBOL_ERROR_DETECTED	= 1,
  TJA1101_SYMBE_NO_SYMBOL_ERROR_DETECTED	= 0
}TJA1101_SYM_ERROR_t;

#define TJA1101_SYMBE_MASK   (0x100)   // bit [8]
#define TJA1101_SYMBE_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_TF_TRAINING_PHASE_FAILURE_DETECTED	= 1,
  TJA1101_TF_NO_TRAINING_PHASE_FAILURE_DETECTED	= 0
}TJA1101_TRAINING_FAILED_t;

#define TJA1101_TF_MASK   (0x80)   // bit [7]
#define TJA1101_TF_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_SQIW_SQI_VALUE_BELOW_WARNING_LIMIT	= 1,
  TJA1101_SQIW_SQI_VALUE_ABOVE_WARNING_LIMIT	= 0
}TJA1101_SQI_WARNING_t;

#define TJA1101_SQIW_MASK   (0x40)   // bit [6]
#define TJA1101_SQIW_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_CTRLE_SMI_CONTROL_ERROR_DETECTED	= 1,
  TJA1101_CTRLE_NO_SMI_CONTROL_ERROR_DETECTED	= 0
}TJA1101_CONTROL_ERROR_t;

#define TJA1101_CTRLE_MASK   (0x20)   // bit [5]
#define TJA1101_CTRLE_SHIFT  (5)
//--------------------------------------
//typedef enum
//{
//  TJA1100_TXEC_TXEN_CLAMPING_DETECTED	= 1,
//  TJA1100_TXEC_NO_TXEN_CLAMPING_DETECTED	= 0
//}TJA1100_TXEN_CLAMPED_t;
//
//#define TJA1100_TXEC_MASK   (0x10)   // bit [4]
//#define TJA1100_TXEC_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1101_UVE_UNDERVOLTAGE_DETECTED	= 1,
  TJA1101_UVE_NO_UNDERVOLTAGE_DETECTED	= 0
}TJA1101_UV_ERROR_t;

#define TJA1101_UVE_MASK   (0x08)   // bit [3]
#define TJA1101_UVE_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1101_UVR_UNDERVOLTAGE_RECOVERY_DETECTED	= 1,
  TJA1101_UVR_NO_UNDERVOLTAGE_RECOVERY	= 0
}TJA1101_UV_RECOVERY_t;

#define TJA1101_UVR_MASK   (0x04)   // bit [2]
#define TJA1101_UVR_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1101_TER_OVERTEMPERATURE_ERROR_DETECTED	= 1,
  TJA1101_TER_NO_OVERTEMPERATURE_ERROR_DETECTED	= 0
}TJA1101_TEMP_ERROR_t;

#define TJA1101_TER_MASK   (0x02)   // bit [1]
#define TJA1101_TER_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1101_SLPABRT_SLEEP_TRANSITION_ABORTED	= 1,
  TJA1101_SLPABRT_SLEEP_TRANSITION_NOT_ABORTED	= 0
}TJA1101_SLEEP_ABORT_t;

#define TJA1101_SLPABRT_MASK   (0x01)   // bit [0]
#define TJA1101_SLPABRT_SHIFT  (0)



//---------------------------------------------------
// register 0x16
//---------------------------------------------------
#define TJA1101_INTERRUPT_MASK_REG      (0x16)
#define TJA1101_INTERRUPT_MASK_REG_MASK (0xFFEF)
//--------------------------------------
typedef enum
{
  TJA1100_POEN_PWON_INTERRUPT_ENABLED	= 1,
  TJA1100_POEN_PWON_INTERRUPT_DISABLED	= 0
}TJA1100_PWON_EN_t;

#define TJA1100_POEN_MASK   (0x8000)   // bit [15]
#define TJA1100_POEN_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1100_WUEN_WAKEUP_INTERRUPT_ENABLED	= 1,
  TJA1100_WUEN_WAKEUP_INTERRUPT_DISABLED	= 0
}TJA1100_WAKEUP_EN_t;

#define TJA1100_WUEN_MASK   (0x4000)   // bit [14]
#define TJA1100_WUEN_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1100_WUREN_WAKEUP_INTERRUPT_ENABLED	= 1,
  TJA1100_WUREN_WAKEUP_INTERRUPT_DISABLED	= 0
}TJA1100_WUR_RECEIVED_EN_t;

#define TJA1100_WUREN_MASK   (0x2000)   // bit [13]
#define TJA1100_WUREN_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1100_LPSREN_LPS_RECEIVED_INTERRUPT_ENABLED	= 1,
  TJA1100_LPSREN_LPS_RECEIVED_INTERRUPT_DISABLED	= 0
}TJA1100_LPS_RECEIVED_EN_t;

#define TJA1100_LPSREN_MASK   (0x1000)   // bit [12]
#define TJA1100_LPSREN_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1100_PHYIFEN_PHY_INIT_FAIL_INTERRUPT_ENABLED	= 1,
  TJA1100_PHYIFEN_PHY_INIT_FAIL_INTERRUPT_DISABLED	= 0
}TJA1100_PHY_INIT_FAIL_EN_t;

#define TJA1100_PHYIFEN_MASK   (0x800)   // bit [11]
#define TJA1100_PHYIFEN_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1100_LSFEN_LINK_STATUS_FAIL_INTERRUPT_ENABLED	= 1,
  TJA1100_LSFEN_LINK_STATUS_FAIL_INTERRUPT_DISABLED	= 0
}TJA1100_LINK_STATUS_FAIL_EN_t;

#define TJA1100_LSFEN_MASK   (0x400)   // bit [10]
#define TJA1100_LSFEN_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1100_LSUEN_LINK_STATUS_UP_INTERRUPT_ENABLED	= 1,
  TJA1100_LSUEN_LINK_STATUS_UP_INTERRUPT_DISABLED	= 0
}TJA1100_LINK_STATUS_UP_EN_t;

#define TJA1100_LSUEN_MASK   (0x200)   // bit [9]
#define TJA1100_LSUEN_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1100_SEEN_SYM_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_SEEN_SYM_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_SYM_ERROR_EN_t;

#define TJA1100_SEEN_MASK   (0x100)   // bit [8]
#define TJA1100_SEEN_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1100_TFEN_TRAINING_FAILED_INTERRUPT_ENABLED	= 1,
  TJA1100_TFEN_TRAINING_FAILED_INTERRUPT_DISABLED	= 0
}TJA1100_TRAINING_FAILED_EN_t;

#define TJA1100_TFEN_MASK   (0x80)   // bit [7]
#define TJA1100_TFEN_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1100_SNWEN_SNR_WARNING_INTERRUPT_ENABLED	= 1,
  TJA1100_SNWEN_SNR_WARNING_INTERRUPT_DISABLED	= 0
}TJA1100_SNR_WARNING_EN_t;

#define TJA1100_SNWEN_MASK   (0x40)   // bit [6]
#define TJA1100_SNWEN_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1100_CTRLEREN_CONTROL_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_CTRLEREN_CONTROL_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_CONTROL_ERROR_EN_t;

#define TJA1100_CTRLEREN_MASK   (0x20)   // bit [5]
#define TJA1100_CTRLEREN_SHIFT  (5)
//--------------------------------------
//typedef enum
//{
//  TJA1100_TXECEN_TXEN_CLAMPED_INTERRUPT_ENABLED	= 1,
//  TJA1100_TXECEN_TXEN_CLAMPED_INTERRUPT_DISABLED	= 0
//}TJA1100_TXEN_CLAMPED_EN_t;
//
//#define TJA1100_TXECEN_MASK   (0x10)   // bit [4]
//#define TJA1100_TXECEN_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1100_UVEEN_UV_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_UVEEN_UV_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_UV_ERROR_EN_t;

#define TJA1100_UVEEN_MASK   (0x08)   // bit [3]
#define TJA1100_UVEEN_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1100_UVREN_UV_RECOVERY_INTERRUPT_ENABLED	= 1,
  TJA1100_UVREN_UV_RECOVERY_INTERRUPT_DISABLED	= 0
}TJA1100_UV_RECOVERY_EN_t;

#define TJA1100_UVREN_MASK   (0x04)   // bit [2]
#define TJA1100_UVREN_SHIFT  (2)
//--------------------------------------
typedef enum
{
  TJA1100_TEREN_TEMP_ERROR_INTERRUPT_ENABLED	= 1,
  TJA1100_TEREN_TEMP_ERROR_INTERRUPT_DISABLED	= 0
}TJA1100_TEMP_ERROR_EN_t;

#define TJA1100_TEREN_MASK   (0x02)   // bit [1]
#define TJA1100_TEREN_SHIFT  (1)
//--------------------------------------
typedef enum
{
  TJA1100_SLPABRTEN_SLEEP_TRANSITION_ABORTED_INTERRUPT_ENABLED	= 1,
  TJA1100_SLPABRTEN_SLEEP_TRANSITION_ABORTED_INTERRUPT_DISABLED	= 0
}TJA1100_SLEEP_ABORT_EN_t;

#define TJA1100_SLPABRTEN_MASK   (0x01)   // bit [0]
#define TJA1100_SLPABRTEN_SHIFT  (0)




//---------------------------------------------------
// register 0x17
//---------------------------------------------------
#define TJA1101_COMMUNICATION_STATUS_REG      (0x17)
#define TJA1101_COMMUNICATION_STATUS_REG_MASK (0xFFFF)
//--------------------------------------
typedef enum
{
  TJA1101_LU_OK	= 1,
  TJA1101_LU_FAIL	= 0
}TJA1101_LINK_UP_t;

#define TJA1101_LU_MASK   (0x8000)   // bit [15]
#define TJA1101_LU_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_TXM_TRANSMITTER_DISABLED	= 0,
  TJA1101_TXM_TX_MODE_SEND_N	= 1,
  TJA1101_TXM_TX_MODE_SEND_I	= 2,
  TJA1101_TXM_TX_MODE_SEND_Z	= 3
}TJA1101_TX_MODE_t;

#define TJA1101_TXM_MASK   (0x6000)   // bit [14:13]
#define TJA1101_TXM_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_LRS_LOC_RCVR_STATUS_IS_OK	= 1,
  TJA1101_LRS_LOC_RCVR_STATUS_IS_NOT_OK_SINCE_LAST_READ	= 0
}TJA1101_LOC_RCVR_STATUS_t;

#define TJA1101_LRS_MASK   (0x1000)   // bit [12]
#define TJA1101_LRS_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_RRS_REM_RCVR_STATUS_IS_OK	= 1,
  TJA1101_RRS_REM_RCVR_STATUS_IS_NOT_OK_SINCE_LAST_READ	= 0
}TJA1101_REM_RCVR_STATUS_t;

#define TJA1101_RRS_MASK   (0x800)   // bit [11]
#define TJA1101_RRS_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_SCRL_DESCRAMBLER_LOCKED	= 1,
  TJA1101_SCRL_DESCRAMBLER_UNLOCKED	= 0
}TJA1101_SCR_LOCKED_t;

#define TJA1101_SCRL_MASK   (0x400)   // bit [10]
#define TJA1101_SCRL_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_SSDE_SSD_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1101_SSDE_NO_SSD_ERROR_DETECTED	= 0
}TJA1101_SSD_ERROR_t;

#define TJA1101_SSDE_MASK   (0x200)   // bit [9]
#define TJA1101_SSDE_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_ESDE_ESD_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1101_ESDE_NO_ESD_ERROR_DETECTED	= 0
}TJA1101_ESD_ERROR_t;

#define TJA1101_ESDE_MASK   (0x100)   // bit [8]
#define TJA1101_ESDE_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_SQI_NO_SQI_VALUE_AVAILABLE = 0,
  TJA1101_SQI_CLASS_A_SQI_RATIO	= 1,
  TJA1101_SQI_CLASS_B_SQI_RATIO	= 2,
  TJA1101_SQI_CLASS_C_SQI_RATIO	= 3,
  TJA1101_SQI_CLASS_D_SQI_RATIO	= 4,
  TJA1101_SQI_CLASS_E_SQI_RATIO	= 5,
  TJA1101_SQI_CLASS_F_SQI_RATIO	= 6,
  TJA1101_SQI_CLASS_G_SQI_RATIO	= 7
}TJA1101_SQI_t;

#define TJA1101_SQI_MASK   (0xE0)   // bit [7:5]
#define TJA1101_SQI_SHIFT  (5)
//--------------------------------------
typedef enum
{
  TJA1101_RXE_RECEIVE_ERROR_DETECTED_SINCE_LAST_READ	= 1,
  TJA1101_RXE_NO_RECEIVE_ERROR_DETECTED	= 0
}TJA1101_RECEIVE_ERROR_t;

#define TJA1101_RXE_MASK   (0x10)   // bit [4]
#define TJA1101_RXE_SHIFT  (4)
//--------------------------------------
typedef enum
{
  TJA1101_TXE_TRANSMIT_ERROR_CODE_RECEIVED_SINCE_LAST_READ	= 1,
  TJA1101_TXE_NO_TRANSMIT_ERROR_CODE_RECEIVED	= 0
}TJA1101_TRANSMIT_ERROR_t;

#define TJA1101_TXE_MASK   (0x08)   // bit [3]
#define TJA1101_TXE_SHIFT  (3)
//--------------------------------------
typedef enum
{
  TJA1101_PHYS_PHY_IDLE	= 0,
  TJA1101_PHYS_PHY_INITIALIZING	= 1,
  TJA1101_PHYS_PHY_CONFIGURED	= 2,
  TJA1101_PHYS_PHY_OFFLINE	= 3,
  TJA1101_PHYS_PHY_ACTIVE	= 4,
  TJA1101_PHYS_PHY_ISOLATE	= 5,
  TJA1101_PHYS_PHY_CABLE_TEST	= 6,
  TJA1101_PHYS_PHY_TESTMODE	= 7
}TJA1101_PHY_STATE_t;

#define TJA1101_PHYS_MASK   (0x07)   // bit [2:0]
#define TJA1101_PHYS_SHIFT  (0)




//---------------------------------------------------
// register 0x18
//---------------------------------------------------
#define TJA1101_GENERAL_STATUS_REG      (0x18)
#define TJA1101_GENERAL_STATUS_REG_MASK (0xFEF8)
//--------------------------------------
typedef enum
{
  TJA1101_INTS_UNMASKED_INTERRUPT_CURRENTLY_ACTIVE	= 1,
  TJA1101_INTS_ALL_INTERRUPTS_CLEARED	= 0
}TJA1101_INT_STATUS_t;

#define TJA1101_INTS_MASK   (0x8000)   // bit [15]
#define TJA1101_INTS_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_PLLL_PLL_STABLE_AND_LOCKED	= 1,
  TJA1101_PLLL_PLL_UNSTABLE_AND_NOT_LOCKED	= 0
}TJA1101_PLL_LOCKED_t;

#define TJA1101_PLLL_MASK   (0x4000)   // bit [14]
#define TJA1101_PLLL_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_LWU_LOCAL_WAKEUP_DETECTED	= 1,
  TJA1101_LWU_NO_LOCAL_WAKEUP_DETECTED	= 0
}TJA1101_LOCAL_WU_t;

#define TJA1101_LWU_MASK   (0x2000)   // bit [13]
#define TJA1101_LWU_SHIFT  (13)
//--------------------------------------
typedef enum
{
  TJA1101_RWU_REMOTE_WAKEUP_DETECTED	= 1,
  TJA1101_RWU_NO_REMOTE_WAKEUP_DETECTED	= 0
}TJA1101_REMOTE_WU_t;

#define TJA1101_RWU_MASK   (0x1000)   // bit [12]
#define TJA1101_RWU_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_DDWU_DATA_DETECTED_IN_SLEEP_REQUEST	= 1,
  TJA1101_DDWU_NO_DATA_DETECTED_IN_SLEEP_REQUEST	= 0
}TJA1101_DATA_DET_WU_t;

#define TJA1101_DDWU_MASK   (0x800)   // bit [11]
#define TJA1101_DDWU_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_ENS_EN_WAS_LOW_SINCE_LAST_READ	= 1,
  TJA1101_ENS_EN_NOT_LOW	= 0
}TJA1101_EN_STATUS_t;

#define TJA1101_ENS_MASK   (0x400)   // bit [10]
#define TJA1101_ENS_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_RSTS_HARDWARE_RESET_DETECTED_SINCE_LAST_READ	= 1,
  TJA1101_RSTS_NO_HARDWARE_RESET_DETECTED	= 0
}TJA1101_RESET_STATUS_t;

#define TJA1101_RSTS_MASK   (0x200)   // bit [9]
#define TJA1101_RSTS_SHIFT  (9)
//--------------------------------------
typedef unsigned short TJA1101_LINKFAIL_COUNT_t;

#define TJA1101_LFCNT_MASK   (0xF8)   // bit [7:3]
#define TJA1101_LFCNT_SHIFT  (3)




//---------------------------------------------------
// register 0x19
//---------------------------------------------------
#define TJA1101_EXTERNAL_STATUS_REG      (0x19)
#define TJA1101_EXTERNAL_STATUS_REG_MASK (0xEFE0)

//--------------------------------------
typedef enum
{
  TJA1101_UV3V3S_UNDERVOLTAGE_DETECTED_ON_VDDD_3V3	= 1,
  TJA1101_UV3V3S_NO_UNDERVOLTAGE_DETECTED_ON_VDDD_3V3	= 0
}TJA1101_UV_VDDD_3V3_t;

#define TJA1101_UVD3V3S_MASK   (0x8000)   // bit [15]
#define TJA1101_UVD3V3S_SHIFT  (15)
//--------------------------------------
typedef enum
{
  TJA1101_UV3V3S_UNDERVOLTAGE_DETECTED_ON_VDDA_3V3	= 1,
  TJA1101_UV3V3S_NO_UNDERVOLTAGE_DETECTED_ON_VDDA_3V3	= 0
}TJA1101_UV_VDDA_3V3_t;

#define TJA1101_UV3V3S_MASK   (0x4000)   // bit [14]
#define TJA1101_UV3V3S_SHIFT  (14)
//--------------------------------------
typedef enum
{
  TJA1101_UVD1V8S_UNDERVOLTAGE_DETECTED_ON_VDDD_1V8	= 1,
  TJA1101_UVD1V8S_NO_UNDERVOLTAGE_DETECTED_ON_VDDD_1V8	= 0
}TJA1101_UV_VDDD_1V8_t;

#define TJA1101_UVD1V8S_MASK   (0x2000)   // bit [13]
#define TJA1101_UVD1V8S_SHIFT  (13)
//--------------------------------------
//typedef enum
//{
//  TJA1100_UVA1V8S_UNDERVOLTAGE_DETECTED_ON_VDDA_1V8	= 1,
//  TJA1100_UVA1V8S_NO_UNDERVOLTAGE_DETECTED_ON_VDDA_1V8	= 0
//}TJA1100_UV_VDDA_1V8_t;
//
//#define TJA1100_UVA1V8S_MASK   (0x1000)   // bit [12]
//#define TJA1100_UVA1V8S_SHIFT  (12)
//--------------------------------------
typedef enum
{
  TJA1101_UVIOS_UNDERVOLTAGE_DETECTED_ON_VDDIO1_VDDIO2	= 1,
  TJA1101_UVIOS_NO_UNDERVOLTAGE_DETECTED_ON_VDDIO1_VDDIO2 = 0
}TJA1101_UV_VDDIO_t;

#define TJA1101_UVIOS_MASK   (0x800)   // bit [11]
#define TJA1101_UVIOS_SHIFT  (11)
//--------------------------------------
typedef enum
{
  TJA1101_TEMPHS_TEMPERATURE_ABOVE_HIGH_LEVEL	= 1,
  TJA1101_TEMPHS_TEMPERATURE_BELOW_HIGH_LEVEL	= 0
}TJA1101_TEMP_HIGH_t;

#define TJA1101_TEMPHS_MASK   (0x400)   // bit [10]
#define TJA1101_TEMPHS_SHIFT  (10)
//--------------------------------------
typedef enum
{
  TJA1101_TEMPWS_TEMPERATURE_ABOVE_WARNING_LEVEL	= 1,
  TJA1101_TEMPWS_TEMPERATURE_BELOW_WARNING_LEVEL	= 0
}TJA1101_TEMP_WARN_t;

#define TJA1101_TEMPWS_MASK   (0x200)   // bit [9]
#define TJA1101_TEMPWS_SHIFT  (9)
//--------------------------------------
typedef enum
{
  TJA1101_SDS_SHORT_CIRCUIT_DETECTED_SINCE_LAST_READ = 1,
  TJA1101_SDS_NO_SHORT_CIRCUIT_DETECTED	= 0
}TJA1101_SHORT_DETECT_t;

#define TJA1101_SDS_MASK   (0x100)   // bit [8]
#define TJA1101_SDS_SHIFT  (8)
//--------------------------------------
typedef enum
{
  TJA1101_ODS_OPEN_DETECTED_SINCE_LAST_READ	= 1,
  TJA1101_ODS_NO_OPEN_DETECTED	= 0
}TJA1101_OPEN_DETECT_t;

#define TJA1101_ODS_MASK   (0x80)   // bit [7]
#define TJA1101_ODS_SHIFT  (7)
//--------------------------------------
typedef enum
{
  TJA1101_PDMS_POLARITY_INVERSION_AT_MDI	= 1,
  TJA1101_PDMS_NO_POLARITY_INVERSION_AT_MDI_DETECTED	= 0
}TJA1101_POLARITY_DETECTOR_MDI_t;

#define TJA1101_PDMS_MASK   (0x40)   // bit [6]
#define TJA1101_PDMS_SHIFT  (6)
//--------------------------------------
typedef enum
{
  TJA1101_IDS_INTERLEAVING_TERNARY_SYMBOLS_DETECTED	= 1,
  TJA1101_IDS_NO_INTERLEAVING_TERNARY_SYMBOLS_DETECTED	= 0
}TJA1101_INTERLEAVE_DETECT_t;

#define TJA1101_IDS_MASK   (0x20)   // bit [5]
#define TJA1101_IDS_SHIFT  (5)




//---------------------------------------------------
// register 0x1A
//---------------------------------------------------
#define TJA1101_LINK_FAIL_COUNTER_REG      (0x1A)
#define TJA1101_LINK_FAIL_COUNTER_REG_MASK (0xFFFF)
//--------------------------------------
typedef unsigned short TJA1101_LOC_RCVR_COUNTER_t;

#define TJA1101_LRC_MASK   (0xFF00)   // bit [15:8]
#define TJA1101_LRC_SHIFT  (8)
//--------------------------------------
typedef unsigned short TJA1101_REM_RCVR_COUNTER_t;

#define TJA1101_RRC_MASK   (0xFF)   // bit [7:0]
#define TJA1101_RRC_SHIFT  (0)




//---------------------------------------------------
// register 0x1B
//---------------------------------------------------
#define TJA1101_COMMON_CONFIG_REG		(0x1B)
#define TJA1101_COMMON_CONFIG_REG_MASK	(0xBFE0)

typedef enum
{
	AUTONOMOUS_OPERATION = 1,
	MANAGED_OPERATION = 0
}TJA1101_AUTO_OP_t;

#define TJA1101_AUTO_OP_MASK			(0x8000)
#define TJA1101_AUTO_OP_SHIFT			(15)

typedef enum
{
	CLK_25MHZ_XTAL_NOCLK_AT_CLKINOUT = 0,
	CLK_25MHZ_XTAL_25MHZ_OUTPUT_AT_CLKINOUT = 1,
	CLK_25MHZ_EXTERNAL_CLK_AT_CLKINOUT = 2,
	CLK_50MHZ_INPUT_AT_REF_CLK = 3
}TJA1101_CLK_MODE_t;

#define TJA1101_CLK_MODE_MASK			(0x3000)
#define TJA1101_CLK_MODE_SHIFT			(12)

typedef enum
{
	INTERNAL_1V8_LDO_ENABLED = 0,
	EXTERNAL_1V8_SUPPLY = 1
}TJA1101_LDO_MODE_t;

#define TJA1101_LDO_MODE_MASK			(0x0800)
#define TJA1101_LDO_MODE_SHIFT			(11)

typedef enum
{
	STANDARD_OUTPUT_DRIVER_STRENGTH_AT_CLK_IN_OUT = 0,
	REDUCED_OUTPUT_DRIVER_STRENGTH_AT_CLK_IN_OUT = 1
}TJA1101_CLK_DRIVER_t;

#define TJA1101_CLK_DRIVER_MASK			(0x0400)
#define TJA1101_CLK_DRIVER_SHIFT		(10)

typedef enum
{
	XTAL_AND_CLK_IN_OUTPUT_SWITCHED_OFF_SLEEP_MODE = 0,
	XTAL_AND_CLK_IN_OUTPUT_REMAIN_ACTIVE = 1
}TJA1101_CLK_HOLD_t;

#define TJA1101_CLK_HOLD_MASK			(0x0200)
#define TJA1101_CLK_HOLD_SHIFT			(9)

typedef enum
{
	LONGEST_10MS_20MS = 0,
	LONG_250US_500US = 1,
	SHORT_100US_200US = 2,
	SHORTEST_10US_40US = 3
}TJA1101_LOC_WU_TIME_t;

#define TJA1101_LOC_WU_TIME_MASK		(0x0180)
#define TJA1101_LOC_WU_TIME_SHIFT		(7)

typedef enum
{
	ABSOLUTE_INPUT_THRESHOLD = 0,
	RATIOMETRIC_INPUT_THRESHOLD = 1
}TJA1101_CONFIG_WAKE_t;

#define TJA1101_CONFIG_WAKE_MASK		(0x0040)
#define TJA1101_CONFIG_WAKE_SHIFT		(6)

typedef enum
{
	INH_SWITCHED_OFF_DISABLE_MODE = 0,
	INH_SWITCHED_ON_DISABLE_MODE = 1
}TJA1101_CONFIG_INH_t;

#define TJA1101_CONFIG_INH_MASK			(0x0020)
#define TJA1101_CONFIG_INH_SHIFT		(5)



//---------------------------------------------------
// register 0x1C
//---------------------------------------------------
#define TJA1101_CONFIG3_REG	(0x1C)
#define TJA1101_CONFIG3_REG_MASK		(0x0002)



//--------------------------------------------------------------------------------
// register depending structures
//--------------------------------------------------------------------------------
// register 0x00
typedef struct
{
	TJA1101_RESET_t	TJA1100_RST;
	TJA1101_LOOPBACK_t	TJA1100_LB;
	TJA1101_SPEED_SELECT_LSB_t	TJA1100_SS_LSB;
	TJA1101_AUTONEG_ENABLE_t	TJA1100_ANE;
	TJA1101_POWER_DOWN_t	TJA1100_PWRD;
	TJA1101_ISOLATE_t	TJA1100_ISL;
	TJA1101_RE_AUTONEG_t	TJA1100_RAN;
	TJA1101_DUPLEX_MODE_t	TJA1100_DM;
	TJA1101_COLLISION_TEST_t	TJA1100_CT;
	TJA1101_SPEED_SELECT_MSB_t	TJA1100_SS_MSB;
	TJA1101_Unidirectional_enable_t	TJA1100_UDE;
}TJA1100_Basic_Control_Reg_t;
//---------------------------------------------------
// register 0x01
typedef struct
{
  TJA1101_100BASE_T4_t	TJA1100_100BASE_T4;
  TJA1101_100BASE_X_Full_Duplex_t	TJA1100_100BASE_X_FD;
  TJA1101_100BASE_X_Half_Duplex_t	TJA1100_100BASE_X_HD;
  TJA1101_10Mbps_Full_Duplex_t	TJA1100_10MBPS_FD;
  TJA1101_10Mbps_Half_Duplex_t	TJA1100_10MBPS_HD;
  TJA1101_100BASE_T2_Full_Duplex_t	TJA1100_100BASE_T2_FD;
  TJA1101_100BASE_T2_Half_Duplex_t	TJA1100_100BASE_T2_HD;
  TJA1101_EXTENDED_STATUS_t	TJA1100_ES;
  TJA1101_Unidirectional_ability_t	TJA1100_UDA;
  TJA1101_MF_Preamble_Suppression_t	TJA1100_MFPS;
  TJA1101_AUTONEG_COMPLETE_t	TJA1100_ANC;
  TJA1101_REMOTE_FAULT_t	TJA1100_RF;
  TJA1101_AUTONEG_ABILITY_t	TJA1100_ANA;
  TJA1101_LINK_STATUS_t	TJA1100_LS;
  TJA1101_JABBER_DETECT_t	TJA1100_JD;
  TJA1101_EXTENDED_CAPABILITY_t	TJA1100_EC;
}TJA110x_Basic_Status_Reg_t;
//---------------------------------------------------
// register 0x02
typedef struct
{
  TJA1101_PHY_ID_1_t	TJA1100_PHY_ID1;
}TJA110x_PHY_Identifier_1_Reg_t;
//---------------------------------------------------
// register 0x03
typedef struct
{
  TJA1101_PHY_ID_2_t	TJA1100_PHY_ID2;
  TJA1101_TYPE_No_t	TJA1100_TYPE;
  TJA1101_REVISION_No_t	TJA1100_REV;
}TJA110x_PHY_Identifier_2_Reg_t;
//---------------------------------------------------
// register 0x0F
typedef struct
{
  TJA1101_1000BASE_X_Full_Duplex_t	TJA1100_1000BASE_X_FD;
  TJA1101_1000BASE_X_Half_Duplex_t	TJA1100_1000BASE_X_HD;
  TJA1101_1000BASE_T_Full_Duplex_t	TJA1100_1000BASE_T_FD;
  TJA1101_1000BASE_T_Half_Duplex_t	TJA1100_1000BASE_T_HD;
  TJA1101_100BASE_T1_t	TJA1100_100BASE_T1;
  TJA1101_1000BASE_RTPGE_t	TJA1100_1000BASE_RTPGE;
}TJA110x_Extended_Status_Reg_t;
//---------------------------------------------------
// register 0x11
typedef struct
{
  TJA1101_LINK_CONTROL_t	TJA1101_LC;
  TJA1101_POWER_MODE_t	TJA1101_PM;
  TJA1101_SLAVE_JITTER_TEST_t	TJA1101_SJT;
  TJA1101_TRAINING_RESTART_t	TJA1101_TRS;
  TJA1101_TEST_MODE_t	TJA1101_TM;
  TJA1101_CABLE_TEST_t	TJA1101_CBT;
  TJA1101_LOOPBACK_MODE_t	TJA1101_LM;
  TJA1101_CONFIG_EN_t	TJA1101_CFEN;
  TJA1101_WAKE_REQUEST_t	TJA1101_WR;
}TJA110x_Extended_Control_Reg_t;
//---------------------------------------------------

// register 0x12
typedef struct
{
  TJA1101_MASTER_SLAVE_t	TJA1101_MS;
  TJA1101_WAKEUP_LOCAL_t  TJA1101_WU_LOCAL;
  TJA1101_REACT_REMOTE_WAKEUP_t TJA1101_REACT_RE_WU;
  TJA1101_REACT_LOCAL_WAKEUP_t TJA1101_REACT_LO_WU;
  TJA1101_MII_Mode_t	TJA1101_MIIM;
  TJA1101_MII_DRIVER_t	TJA1101_MIID;
  TJA1101_SLEEP_CONFIRM_t	TJA1101_SLEEPCONF;
  TJA1101_LPS_WUR_SETTINGS_t TJA1101_LPS_WUR;
  TJA1101_SLEEP_ACK_t TJA1101_SLEEP_ACK;
  TJA1101_FWD_REMOTE_WAKEUP_t TJA1101_FW_REMOTE_WU;
  TJA1101_AUTO_PWD_t	TJA1101_APD;
  TJA1101_LPS_ACTIVE_t	TJA1101_LPSACT;
}TJA110x_Configuration_1_Reg_t;

//---------------------------------------------------
// register 0x13
typedef struct
{
  TJA1101_PHYAD4to0_t	TJA1101_PHYAD;
  TJA1101_SQI_Averaging_t	TJA1101_SQIAVG;
  TJA1101_SQI_WLIMIT_t	TJA1101_SQIWL;
  TJA1101_SQI_FAILLIMIT_t	TJA1101_SQIFL;
  TJA1101_JUMBO_ENABLE_t	TJA1101_JE;
  TJA1101_SLEEP_REQUEST_TO_t	TJA1101_SRT;
}TJA110x_Configuration_2_Reg_t;
//---------------------------------------------------

// register 0x14
typedef struct
{
  TJA110x_SYM_ERR_CNT_t	TJA1101_SEC;
}TJA110x_Symbol_Error_Counter_Reg_t;
//---------------------------------------------------

#if 0
// register 0x15
typedef struct
{
  TJA1100_PWON_t	TJA1100_PO;
  TJA1100_WAKEUP_t	TJA1100_WU;
  TJA1100_WUR_RECEIVED_t	TJA1100_WUR;
  TJA1100_LPS_RECEIVED_t	TJA1100_LPSR;
  TJA1100_PHY_INIT_FAIL_t	TJA1100_PHYIF;
  TJA1100_LINK_STATUS_FAIL_t	TJA1100_LSF;
  TJA1100_LINK_STATUS_UP_t	TJA1100_LSU;
  TJA1100_SYM_ERROR_t	TJA1100_SYMBE;
  TJA1100_TRAINING_FAILED_t	TJA1100_TF;
  TJA1100_SNR_WARNING_t	TJA1100_SNRW;
  TJA1100_CONTROL_ERROR_t	TJA1100_CTRLE;
  TJA1100_TXEN_CLAMPED_t	TJA1100_TXEC;
  TJA1100_UV_ERROR_t	TJA1100_UVE;
  TJA1100_UV_RECOVERY_t	TJA1100_UVR;
  TJA1100_TEMP_ERROR_t	TJA1100_TER;
  TJA1100_SLEEP_ABORT_t	TJA1100_SLPABRT;
}TJA1100_Interrupt_Source_Reg_t;
//---------------------------------------------------

// register 0x16
typedef struct
{
  TJA1100_PWON_EN_t	TJA1100_POEN;
  TJA1100_WAKEUP_EN_t	TJA1100_WUEN;
  TJA1100_WUR_RECEIVED_EN_t	TJA1100_WUREN;
  TJA1100_LPS_RECEIVED_EN_t	TJA1100_LPSREN;
  TJA1100_PHY_INIT_FAIL_EN_t	TJA1100_PHYIFEN;
  TJA1100_LINK_STATUS_FAIL_EN_t	TJA1100_LSFEN;
  TJA1100_LINK_STATUS_UP_EN_t	TJA1100_LSUEN;
  TJA1100_SYM_ERROR_EN_t	TJA1100_SEEN;
  TJA1100_TRAINING_FAILED_EN_t	TJA1100_TFEN;
  TJA1100_SNR_WARNING_EN_t	TJA1100_SNWEN;
  TJA1100_CONTROL_ERROR_EN_t	TJA1100_CTRLEREN;
  TJA1100_TXEN_CLAMPED_EN_t	TJA1100_TXECEN;
  TJA1100_UV_ERROR_EN_t	TJA1100_UVEEN;
  TJA1100_UV_RECOVERY_EN_t	TJA1100_UVREN;
  TJA1100_TEMP_ERROR_EN_t	TJA1100_TEREN;
  TJA1100_SLEEP_ABORT_EN_t	TJA1100_SLPABRTEN;
}TJA1100_Interrupt_Mask_Reg_t;
//---------------------------------------------------
#endif


// register 0x17
typedef struct
{
  TJA1101_LINK_UP_t	TJA1101_LU;
  TJA1101_TX_MODE_t	TJA1101_TXM;
  TJA1101_LOC_RCVR_STATUS_t	TJA1101_LRS;
  TJA1101_REM_RCVR_STATUS_t	TJA1101_RRS;
  TJA1101_SCR_LOCKED_t	TJA1101_SCRL;
  TJA1101_SSD_ERROR_t	TJA1101_SSDE;
  TJA1101_ESD_ERROR_t	TJA1101_ESDE;
  TJA1101_SQI_t	TJA1101_SQI;
  TJA1101_RECEIVE_ERROR_t	TJA1101_RXE;
  TJA1101_TRANSMIT_ERROR_t	TJA1101_TXE;
  TJA1101_PHY_STATE_t	TJA1101_PHYS;
}TJA110x_Communication_Status_Reg_t;
//---------------------------------------------------

// register 0x18
typedef struct
{
  TJA1101_INT_STATUS_t	TJA1101_INTS;
  TJA1101_PLL_LOCKED_t	TJA1101_PLLL;
  TJA1101_LOCAL_WU_t	TJA1101_LWU;
  TJA1101_REMOTE_WU_t	TJA1101_RWU;
  TJA1101_DATA_DET_WU_t	TJA1101_DDWU;
  TJA1101_EN_STATUS_t	TJA1101_ENS;
  TJA1101_RESET_STATUS_t	TJA1101_RSTS;
  TJA1101_LINKFAIL_COUNT_t	TJA1101_LFCNT;
}TJA110x_General_Status_Reg_t;
//---------------------------------------------------

// register 0x19
typedef struct
{
  TJA1101_UV_VDDD_3V3_t TJA1101_UVD3V3S;
  TJA1101_UV_VDDA_3V3_t	TJA1101_UV3V3S;
  TJA1101_UV_VDDD_1V8_t	TJA1101_UVD1V8S;
  TJA1101_UV_VDDIO_t	TJA1101_UVIOS;
  TJA1101_TEMP_HIGH_t	TJA1101_TEMPHS;
  TJA1101_TEMP_WARN_t	TJA1101_TEMPWS;
  TJA1101_SHORT_DETECT_t	TJA1101_SDS;
  TJA1101_OPEN_DETECT_t	TJA1101_ODS;
  TJA1101_POLARITY_DETECTOR_MDI_t	TJA1101_PDMS;
  TJA1101_INTERLEAVE_DETECT_t	TJA1101_IDS;
}TJA110x_External_Status_Reg_t;
//---------------------------------------------------

// register 0x1A
typedef struct
{
  TJA1101_LOC_RCVR_COUNTER_t	TJA1100_LRC;
  TJA1101_REM_RCVR_COUNTER_t	TJA1100_RRC;
}TJA110x_Link_Fail_Counter_Reg_t;
//---------------------------------------------------

// register 0x1B
typedef struct
{
	TJA1101_AUTO_OP_t TJA1101_AUTO_OP;
	TJA1101_CLK_MODE_t TJA1101_CLK_MODE;
	TJA1101_LDO_MODE_t TJA1101_LDO_MODE;
	TJA1101_CLK_DRIVER_t TJA1101_CLK_DRIVER;
	TJA1101_CLK_HOLD_t TJA1101_CLK_HOLD;
	TJA1101_LOC_WU_TIME_t TJA1101_LOC_WU_TIME;
	TJA1101_CONFIG_WAKE_t TJA1101_CONFIG_WAKE;
	TJA1101_CONFIG_INH_t TJA1101_INH;
}TJA110x_Common_Config_Reg_t;




//---------------------------------------------------
//--------------------------------------------------------------------------------
// function prototypes
//--------------------------------------------------------------------------------

NXP_TJA1100_Error_Code_t TJA110x_setBasicControl(TJA1100_Basic_Control_Reg_t* pTJA110xBCR, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_getBasicControl(TJA1100_Basic_Control_Reg_t* pTJA110xBCR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getBasicStatus(TJA110x_Basic_Status_Reg_t* pTJ110xBSR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getPHYIdentifier1(TJA110x_PHY_Identifier_1_Reg_t* penPHY_ID1, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_getPHYIdentifier2(TJA110x_PHY_Identifier_2_Reg_t* penPHY_ID2, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getExtendedStatus(TJA110x_Extended_Status_Reg_t* pTJA110xESR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_setExtendedControl(TJA110x_Extended_Control_Reg_t* pTJA110xECR, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_getExtendedControl(TJA110x_Extended_Control_Reg_t* pTJA110xECR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_setConfiguration1(TJA110x_Configuration_1_Reg_t* pTJA110xCFG1R, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_getConfiguration1(TJA110x_Configuration_1_Reg_t* pTJA110xCFG1R, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_setConfiguration2(TJA110x_Configuration_2_Reg_t* pTJA110xCFG2R, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_getConfiguration2(TJA110x_Configuration_2_Reg_t* pTJA110xCFG2R, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getSymbolErrorCounter(TJA110x_Symbol_Error_Counter_Reg_t* penSEC, Byte enPhyAddr);


NXP_TJA1100_Error_Code_t TJA110x_getCommunicationStatus(TJA110x_Communication_Status_Reg_t* pTJA110xCSR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getGeneralStatus(TJA110x_General_Status_Reg_t* pTJA110xGSR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getExternalStatus(TJA110x_External_Status_Reg_t* pTJA110xESR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getLinkFailCounter(TJA110x_Link_Fail_Counter_Reg_t* pTJA110xLFCR, Byte enPhyAddr);

NXP_TJA1100_Error_Code_t TJA110x_getCommonConfiguration(TJA110x_Common_Config_Reg_t* pTJA110xCCR, Byte enPhyAddr);
NXP_TJA1100_Error_Code_t TJA110x_setCommonConfiguration(TJA110x_Common_Config_Reg_t* pTJA110xCCR, Byte enPhyAddr);



//--------------------------------------------------------------------------------
#endif

