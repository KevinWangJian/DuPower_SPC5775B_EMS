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

/** \mainpage NXP TJA1100 Example Low Level Driver
*
* This is the TJA1100 example driver to get access to all registers and logical values
*
* \author XML Parser V1.2
* \version V2.0
* \date 07/08/2014
*
* - The following registers are supported:
*   - <b>Basic Control</b> - Address = 0x00, Access = READ/WRITE, 
*   - <b>Basic Status</b> - Address = 0x01, Access = READ, 
*   - <b>PHY Identifier 1</b> - Address = 0x02, Access = READ, 
*   - <b>PHY Identifier 2</b> - Address = 0x03, Access = READ, 
*   - <b>Extended Status</b> - Address = 0x0F, Access = READ, 
*   - <b>Extended Control</b> - Address = 0x11, Access = READ/WRITE, 
*   - <b>Configuration 1</b> - Address = 0x12, Access = READ/WRITE, 
*   - <b>Configuration 2</b> - Address = 0x13, Access = READ/WRITE, 
*   - <b>Symbol Error Counter</b> - Address = 0x14, Access = READ, 
*   - <b>Interrupt Source</b> - Address = 0x15, Access = READ, 
*   - <b>Interrupt Mask</b> - Address = 0x16, Access = READ/WRITE, 
*   - <b>Communication Status</b> - Address = 0x17, Access = READ, 
*   - <b>General Status</b> - Address = 0x18, Access = READ, 
*   - <b>External Status</b> - Address = 0x19, Access = READ, 
*   - <b>Link Fail Counter</b> - Address = 0x1A, Access = READ, 
*
* - The following functions are available to get register access:  (each function uses the return type [<b>NXP_TJA1100_Error_Code_t</b>])
*   -  TJA1100_getBasicControl(TJA1100_RESET_t* penRST, TJA1100_LOOPBACK_t* penLB, TJA1100_SPEED_SELECT_LSB_t* penSS_LSB, TJA1100_AUTONEG_ENABLE_t* penANE, TJA1100_POWER_DOWN_t* penPWRD, TJA1100_ISOLATE_t* penISL, TJA1100_RE_AUTONEG_t* penRAN, TJA1100_DUPLEX_MODE_t* penDM, TJA1100_COLLISION_TEST_t* penCT, TJA1100_SPEED_SELECT_MSB_t* penSS_MSB, TJA1100_Unidirectional_enable_t* penUDE, Byte enPhyAddr)
*   -  TJA1100_setBasicControl(TJA1100_RESET_t enRST, TJA1100_LOOPBACK_t enLB, TJA1100_SPEED_SELECT_LSB_t enSS_LSB, TJA1100_AUTONEG_ENABLE_t enANE, TJA1100_POWER_DOWN_t enPWRD, TJA1100_ISOLATE_t enISL, TJA1100_RE_AUTONEG_t enRAN, TJA1100_DUPLEX_MODE_t enDM, TJA1100_COLLISION_TEST_t enCT, TJA1100_SPEED_SELECT_MSB_t enSS_MSB, TJA1100_Unidirectional_enable_t enUDE, Byte enPhyAddr)
*   -  TJA1100_getBasicStatus(TJA1100_100BASE_T4_t* pen100BASE_T4, TJA1100_100BASE_X_Full_Duplex_t* pen100BASE_X_FD, TJA1100_100BASE_X_Half_Duplex_t* pen100BASE_X_HD, TJA1100_10Mbps_Full_Duplex_t* pen10MBPS_FD, TJA1100_10Mbps_Half_Duplex_t* pen10MBPS_HD, TJA1100_100BASE_T2_Full_Duplex_t* pen100BASE_T2_FD, TJA1100_100BASE_T2_Half_Duplex_t* pen100BASE_T2_HD, TJA1100_EXTENDED_STATUS_t* penES, TJA1100_Unidirectional_ability_t* penUDA, TJA1100_MF_Preamble_Suppression_t* penMFPS, TJA1100_AUTONEG_COMPLETE_t* penANC, TJA1100_REMOTE_FAULT_t* penRF, TJA1100_AUTONEG_ABILITY_t* penANA, TJA1100_LINK_STATUS_t* penLS, TJA1100_JABBER_DETECT_t* penJD, TJA1100_EXTENDED_CAPABILITY_t* penEC, Byte enPhyAddr)
*   -  TJA1100_getPHYIdentifier1(TJA1100_PHY_ID_1_t* penPHY_ID1, Byte enPhyAddr)
*   -  TJA1100_getPHYIdentifier2(TJA1100_PHY_ID_2_t* penPHY_ID2, TJA1100_TYPE_No_t* penTYPE, TJA1100_REVISION_No_t* penREV, Byte enPhyAddr)
*   -  TJA1100_getExtendedStatus(TJA1100_1000BASE_X_Full_Duplex_t* pen1000BASE_X_FD, TJA1100_1000BASE_X_Half_Duplex_t* pen1000BASE_X_HD, TJA1100_1000BASE_T_Full_Duplex_t* pen1000BASE_T_FD, TJA1100_1000BASE_T_Half_Duplex_t* pen1000BASE_T_HD, TJA1100_100BASE_BroadR_Reach_t* pen100BASE_BR, TJA1100_1000BASE_RTPGE_t* pen1000BASE_RTPGE, Byte enPhyAddr)
*   -  TJA1100_getExtendedControl(TJA1100_LINK_CONTROL_t* penLC, TJA1100_POWER_MODE_t* penPM, TJA1100_SLAVE_JITTER_TEST_t* penSJT, TJA1100_TRAINING_RESTART_t* penTRS, TJA1100_TEST_MODE_t* penTM, TJA1100_CABLE_TEST_t* penCBT, TJA1100_LOOPBACK_MODE_t* penLM, TJA1100_CONFIG_EN_t* penCFEN, TJA1100_CONFIG_INH_t* penCF_INH, TJA1100_WAKE_REQUEST_t* penWR, Byte enPhyAddr)
*   -  TJA1100_setExtendedControl(TJA1100_LINK_CONTROL_t enLC, TJA1100_POWER_MODE_t enPM, TJA1100_SLAVE_JITTER_TEST_t enSJT, TJA1100_TRAINING_RESTART_t enTRS, TJA1100_TEST_MODE_t enTM, TJA1100_CABLE_TEST_t enCBT, TJA1100_LOOPBACK_MODE_t enLM, TJA1100_CONFIG_EN_t enCFEN, TJA1100_CONFIG_INH_t enCF_INH, TJA1100_WAKE_REQUEST_t enWR, Byte enPhyAddr)
*   -  TJA1100_getConfiguration1(TJA1100_MASTER_SLAVE_t* penMS, TJA1100_AUTO_OP_t* penAOP, TJA1100_LINK_LENGTH_t* penLL, TJA1100_TX_Amplitude_t* penTXA, TJA1100_MII_Mode_t* penMIIM, TJA1100_MII_DRIVER_t* penMIID, TJA1100_SLEEP_CONFIRM_t* penSCNFM, TJA1100_LED_MODE_t* penLEDM, TJA1100_LED_ENABLE_t* penLEDEN, TJA1100_CONFIG_WAKE_t* penCFW, TJA1100_AUTO_PWD_t* penAPD, TJA1100_LPS_ACTIVE_t* penLPSACT, Byte enPhyAddr)
*   -  TJA1100_setConfiguration1(TJA1100_MASTER_SLAVE_t enMS, TJA1100_AUTO_OP_t enAOP, TJA1100_LINK_LENGTH_t enLL, TJA1100_TX_Amplitude_t enTXA, TJA1100_MII_Mode_t enMIIM, TJA1100_MII_DRIVER_t enMIID, TJA1100_SLEEP_CONFIRM_t enSCNFM, TJA1100_LED_MODE_t enLEDM, TJA1100_LED_ENABLE_t enLEDEN, TJA1100_CONFIG_WAKE_t enCFW, TJA1100_AUTO_PWD_t enAPD, TJA1100_LPS_ACTIVE_t enLPSACT, Byte enPhyAddr)
*   -  TJA1100_getConfiguration2(TJA1100_PHYAD4to0_t* penPHYAD, TJA1100_SNR_Averaging_t* penSNRA, TJA1100_SNR_WLIMIT_t* penSNRWL, TJA1100_SNR_FAILLIMIT_t* penSNRFL, TJA1100_JUMBO_ENABLE_t* penJE, TJA1100_SLEEP_REQUEST_TO_t* penSRT, Byte enPhyAddr)
*   -  TJA1100_setConfiguration2(TJA1100_PHYAD4to0_t enPHYAD, TJA1100_SNR_Averaging_t enSNRA, TJA1100_SNR_WLIMIT_t enSNRWL, TJA1100_SNR_FAILLIMIT_t enSNRFL, TJA1100_JUMBO_ENABLE_t enJE, TJA1100_SLEEP_REQUEST_TO_t enSRT, Byte enPhyAddr)
*   -  TJA1100_getSymbolErrorCounter(TJA1100_SYM_ERR_CNT_t* penSEC, Byte enPhyAddr)
*   -  TJA1100_getInterruptSource(TJA1100_PWON_t* penPO, TJA1100_WAKEUP_t* penWU, TJA1100_WUR_RECEIVED_t* penWUR, TJA1100_LPS_RECEIVED_t* penLPSR, TJA1100_PHY_INIT_FAIL_t* penPHYIF, TJA1100_LINK_STATUS_FAIL_t* penLSF, TJA1100_LINK_STATUS_UP_t* penLSU, TJA1100_SYM_ERROR_t* penSYMBE, TJA1100_TRAINING_FAILED_t* penTF, TJA1100_SNR_WARNING_t* penSNRW, TJA1100_CONTROL_ERROR_t* penCTRLE, TJA1100_TXEN_CLAMPED_t* penTXEC, TJA1100_UV_ERROR_t* penUVE, TJA1100_UV_RECOVERY_t* penUVR, TJA1100_TEMP_ERROR_t* penTER, TJA1100_SLEEP_ABORT_t* penSLPABRT, Byte enPhyAddr)
*   -  TJA1100_getInterruptMask(TJA1100_PWON_EN_t* penPOEN, TJA1100_WAKEUP_EN_t* penWUEN, TJA1100_WUR_RECEIVED_EN_t* penWUREN, TJA1100_LPS_RECEIVED_EN_t* penLPSREN, TJA1100_PHY_INIT_FAIL_EN_t* penPHYIFEN, TJA1100_LINK_STATUS_FAIL_EN_t* penLSFEN, TJA1100_LINK_STATUS_UP_EN_t* penLSUEN, TJA1100_SYM_ERROR_EN_t* penSEEN, TJA1100_TRAINING_FAILED_EN_t* penTFEN, TJA1100_SNR_WARNING_EN_t* penSNWEN, TJA1100_CONTROL_ERROR_EN_t* penCTRLEREN, TJA1100_TXEN_CLAMPED_EN_t* penTXECEN, TJA1100_UV_ERROR_EN_t* penUVEEN, TJA1100_UV_RECOVERY_EN_t* penUVREN, TJA1100_TEMP_ERROR_EN_t* penTEREN, TJA1100_SLEEP_ABORT_EN_t* penSLPABRTEN, Byte enPhyAddr)
*   -  TJA1100_setInterruptMask(TJA1100_PWON_EN_t enPOEN, TJA1100_WAKEUP_EN_t enWUEN, TJA1100_WUR_RECEIVED_EN_t enWUREN, TJA1100_LPS_RECEIVED_EN_t enLPSREN, TJA1100_PHY_INIT_FAIL_EN_t enPHYIFEN, TJA1100_LINK_STATUS_FAIL_EN_t enLSFEN, TJA1100_LINK_STATUS_UP_EN_t enLSUEN, TJA1100_SYM_ERROR_EN_t enSEEN, TJA1100_TRAINING_FAILED_EN_t enTFEN, TJA1100_SNR_WARNING_EN_t enSNWEN, TJA1100_CONTROL_ERROR_EN_t enCTRLEREN, TJA1100_TXEN_CLAMPED_EN_t enTXECEN, TJA1100_UV_ERROR_EN_t enUVEEN, TJA1100_UV_RECOVERY_EN_t enUVREN, TJA1100_TEMP_ERROR_EN_t enTEREN, TJA1100_SLEEP_ABORT_EN_t enSLPABRTEN, Byte enPhyAddr)
*   -  TJA1100_getCommunicationStatus(TJA1100_LINK_UP_t* penLU, TJA1100_TX_MODE_t* penTXM, TJA1100_LOC_RCVR_STATUS_t* penLRS, TJA1100_REM_RCVR_STATUS_t* penRRS, TJA1100_SCR_LOCKED_t* penSCRL, TJA1100_SSD_ERROR_t* penSSDE, TJA1100_ESD_ERROR_t* penESDE, TJA1100_SNR_t* penSNR, TJA1100_RECEIVE_ERROR_t* penRXE, TJA1100_TRANSMIT_ERROR_t* penTXE, TJA1100_PHY_STATE_t* penPHYS, Byte enPhyAddr)
*   -  TJA1100_getGeneralStatus(TJA1100_INT_STATUS_t* penINTS, TJA1100_PLL_LOCKED_t* penPLLL, TJA1100_LOCAL_WU_t* penLWU, TJA1100_REMOTE_WU_t* penRWU, TJA1100_DATA_DET_WU_t* penDDWU, TJA1100_EN_STATUS_t* penENS, TJA1100_RESET_STATUS_t* penRSTS, TJA1100_LINKFAIL_COUNT_t* penLFCNT, Byte enPhyAddr)
*   -  TJA1100_getExternalStatus(TJA1100_UV_VDDA_3V3_t* penUV3V3S, TJA1100_UV_VDDD_1V8_t* penUVD1V8S, TJA1100_UV_VDDA_1V8_t* penUVA1V8S, TJA1100_UV_VDDIO_t* penUVIOS, TJA1100_TEMP_HIGH_t* penTEMPHS, TJA1100_TEMP_WARN_t* penTEMPWS, TJA1100_SHORT_DETECT_t* penSDS, TJA1100_OPEN_DETECT_t* penODS, TJA1100_POLARITY_DETECTOR_MDI_t* penPDMS, TJA1100_INTERLEAVE_DETECT_t* penIDS, Byte enPhyAddr)
*   -  TJA1100_getLinkFailCounter(TJA1100_LOC_RCVR_COUNTER_t* penLRC, TJA1100_REM_RCVR_COUNTER_t* penRRC, Byte enPhyAddr)
*/
//******************************************************************
// function header include
#include "NXP_TJA1100_Functions.h"


//******************************************************************

//Extern declaration of SMI communication function 
extern NXP_TJA1100_Error_Code_t SMI_Send(Byte* data, Byte phyAddr, Byte* mask, NXP_TJA1100_Access_t type);

/// This function is used to set data of the Basic Control register
/** The function supports the following parameter:
* \param enRST  possible values:  PHY reset, normal operation
* \param enLB  possible values:  loopback mode, normal operation
* \param enSS_LSB  possible values:  100Mbps
* \param enANE  possible values:  disable autonegotiation process
* \param enPWRD  possible values:  power down into standby, normal operation
* \param enISL  possible values:  isolation of PHY from MII RMII, normal operation
* \param enRAN  possible values:  normal operation
* \param enDM  possible values:  full duplex
* \param enCT  possible values:  disable COL signal test
* \param enSS_MSB  possible values:  100Mbps
* \param enUDE  possible values:  EN MII transmit without PHY valid link, EN MII transmit only when PHY valid link
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_setBasicControl(TJA1100_Basic_Control_Reg_t* pTJA110xBCR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t enStatus;
  Byte	cData[3] = {0, 0, 0};
  Byte	cMask[3] = {0, 0, 0};
  Word	tmp = 0;

  tmp |= (Word) (pTJA110xBCR->TJA1100_RST << TJA1101_RST_SHIFT);		// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_LB << TJA1101_LB_SHIFT);			// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_SS_LSB << TJA1101_SS_LSB_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_ANE << TJA1101_ANE_SHIFT);		// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_PWRD << TJA1101_PWRD_SHIFT);		// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_ISL << TJA1101_ISL_SHIFT);		// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_RAN << TJA1101_RAN_SHIFT);		// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_DM << TJA1101_DM_SHIFT);			// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_CT << TJA1101_CT_SHIFT);			// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_SS_MSB << TJA1101_SS_MSB_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xBCR->TJA1100_UDE << TJA1101_UDE_SHIFT);		// shift valid value to correct bit position and add to data
  
  // create address to write data to
  cData[0] = TJA1101_BASIC_CONTROL_REG;
  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);		// MSB
  cData[2] = (Byte) (0x000000FF & tmp);				// LSB

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_BASIC_CONTROL_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_BASIC_CONTROL_REG_MASK);		// LSB

  // write data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Basic Control register
/** The function supports the following parameter:
* \param *penRST  possible values:  PHY reset, normal operation
* \param *penLB  possible values:  loopback mode, normal operation
* \param *penSS_LSB  possible values:  100Mbps
* \param *penANE  possible values:  disable autonegotiation process
* \param *penPWRD  possible values:  power down into standby, normal operation
* \param *penISL  possible values:  isolation of PHY from MII RMII, normal operation
* \param *penRAN  possible values:  normal operation
* \param *penDM  possible values:  full duplex
* \param *penCT  possible values:  disable COL signal test
* \param *penSS_MSB  possible values:  100Mbps
* \param *penUDE  possible values:  EN MII transmit without PHY valid link, EN MII transmit only when PHY valid link
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getBasicControl(TJA1100_Basic_Control_Reg_t* pTJA110xBCR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_BASIC_CONTROL_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_BASIC_CONTROL_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_BASIC_CONTROL_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RST_MASK);						// mask desired bits
  cResult >>= (Word)(TJA1101_RST_SHIFT);					// shift to right aligned position
  pTJA110xBCR->TJA1100_RST = (TJA1101_RESET_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LB_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LB_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_LB = (TJA1101_LOOPBACK_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SS_LSB_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SS_LSB_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_SS_LSB = (TJA1101_SPEED_SELECT_LSB_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ANE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ANE_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_ANE = (TJA1101_AUTONEG_ENABLE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PWRD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PWRD_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_PWRD = (TJA1101_POWER_DOWN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ISL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ISL_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_ISL = (TJA1101_ISOLATE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RAN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RAN_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_RAN = (TJA1101_RE_AUTONEG_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_DM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_DM_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_DM = (TJA1101_DUPLEX_MODE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_CT_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_CT_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_CT = (TJA1101_COLLISION_TEST_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SS_MSB_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SS_MSB_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_SS_MSB = (TJA1101_SPEED_SELECT_MSB_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UDE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UDE_SHIFT);				// shift to right aligned position
  pTJA110xBCR->TJA1100_UDE = (TJA1101_Unidirectional_enable_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Basic Status register
/** The function supports the following parameter:
* \param *pen100BASE_T4  possible values:  PHY 100BASET4 capable, PHY not 100BASET4 capable
* \param *pen100BASE_X_FD  possible values:  PHY 100BASEX FD capable, PHY not 100BASETX FD capable
* \param *pen100BASE_X_HD  possible values:  PHY 100BASEX HD capable, PHY not 100BASETX HD capable
* \param *pen10MBPS_FD  possible values:  PHY 10Mbps FD capable, PHY not 10Mbps FD capable
* \param *pen10MBPS_HD  possible values:  PHY 10Mbps HD capable, PHY not 10Mbps HD capable
* \param *pen100BASE_T2_FD  possible values:  PHY 100BASET2 FD capable, PHY not 100BASET2 FD capable
* \param *pen100BASE_T2_HD  possible values:  PHY 100BASET2 HD capable, PHY not 100BASET2 HD capable
* \param *penES  possible values:  Extended status information in Reg 15, No extended information in Reg 15
* \param *penUDA  possible values:  PHY able to transmit from MII without valid link, PHY able to transmit from MII only when valid link
* \param *penMFPS  possible values:  PHY will accept preamble suppressed management frames, PHY will not accept preamble suppressed management frames
* \param *penANC  possible values:  Autonegotiation process completed, Autonegotiation process not completed
* \param *penRF  possible values:  remote fault condition detected, no remote fault condition detected
* \param *penANA  possible values:  PHY is able to perform Autonegotiation, PHY not able to perform Autonegotiation
* \param *penLS  possible values:  link is up, link is down
* \param *penJD  possible values:  jabber condition detected, no jabber condition detected
* \param *penEC  possible values:  extended register capabilities, basic register set capabilities
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getBasicStatus(TJA110x_Basic_Status_Reg_t* pTJ110xBSR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_BASIC_STATUS_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_BASIC_STATUS_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_BASIC_STATUS_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_T4_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_T4_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_100BASE_T4 = (TJA1101_100BASE_T4_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_X_FD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_X_FD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_100BASE_X_FD = (TJA1101_100BASE_X_Full_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_X_HD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_X_HD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_100BASE_X_HD = (TJA1101_100BASE_X_Half_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_10MBPS_FD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_10MBPS_FD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_10MBPS_FD = (TJA1101_10Mbps_Full_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_10MBPS_HD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_10MBPS_HD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_10MBPS_HD = (TJA1101_10Mbps_Half_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_T2_FD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_T2_FD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_100BASE_T2_FD = (TJA1101_100BASE_T2_Full_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_T2_HD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_T2_HD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_100BASE_T2_HD = (TJA1101_100BASE_T2_Half_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ES_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ES_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_ES = (TJA1101_EXTENDED_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UDA_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UDA_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_UDA = (TJA1101_Unidirectional_ability_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_MFPS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_MFPS_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_MFPS = (TJA1101_MF_Preamble_Suppression_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ANC_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ANC_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_ANC = (TJA1101_AUTONEG_COMPLETE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RF_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RF_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_RF = (TJA1101_REMOTE_FAULT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ANA_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ANA_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_ANA = (TJA1101_AUTONEG_ABILITY_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LS_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_LS = (TJA1101_LINK_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_JD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_JD_SHIFT);				// shift to right aligned position
  pTJ110xBSR->TJA1100_JD = (TJA1101_JABBER_DETECT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_EC_MASK);					// mask desired bits
  pTJ110xBSR->TJA1100_EC = (TJA1101_EXTENDED_CAPABILITY_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the PHY Identifier 1 register
/** The function supports the following parameter:
* \param *penPHY_ID1  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getPHYIdentifier1(TJA110x_PHY_Identifier_1_Reg_t* penPHY_ID1, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_PHY_IDENTIFIER_1_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_PHY_IDENTIFIER_1_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_PHY_IDENTIFIER_1_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  penPHY_ID1->TJA1100_PHY_ID1 = (TJA1101_PHY_ID_1_t)( cResult );								// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the PHY Identifier 2 register
/** The function supports the following parameter:
* \param *penPHY_ID2  possible values: [0 - 65535]
* \param *penTYPE  possible values: [0 - 65535]
* \param *penREV  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getPHYIdentifier2(TJA110x_PHY_Identifier_2_Reg_t* penPHY_ID2, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_PHY_IDENTIFIER_2_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_PHY_IDENTIFIER_2_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_PHY_IDENTIFIER_2_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PHY_ID2_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PHY_ID2_SHIFT);				// shift to right aligned position
  penPHY_ID2->TJA1100_PHY_ID2 = (TJA1101_PHY_ID_2_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TYPE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TYPE_SHIFT);				// shift to right aligned position
  penPHY_ID2->TJA1100_TYPE = (TJA1101_TYPE_No_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_REV_MASK);					// mask desired bits
  penPHY_ID2->TJA1100_REV = (TJA1101_REVISION_No_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Extended Status register
/** The function supports the following parameter:
* \param *pen1000BASE_X_FD  possible values:  PHY 1000BASEX FD capable, PHY not 1000BASEX FD capable
* \param *pen1000BASE_X_HD  possible values:  PHY 1000BASEX HD capable, PHY not 1000BASEX HD capable
* \param *pen1000BASE_T_FD  possible values:  PHY 1000BASET FD capable, PHY not 1000BASET FD capable
* \param *pen1000BASE_T_HD  possible values:  PHY 1000BASET HD capable, PHY not 1000BASET HD capable
* \param *pen100BASE_BR  possible values:  PHY able to 1 pair BroadR Reach 100Mbps, PHY not able to 1 pair BroadR Reach 100Mbps
* \param *pen1000BASE_RTPGE  possible values:  PHY able to RTPGE, PHY not able to RTPGE
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getExtendedStatus(TJA110x_Extended_Status_Reg_t* pTJA110xESR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_EXTENDED_STATUS_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_EXTENDED_STATUS_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_EXTENDED_STATUS_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_1000BASE_X_FD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_1000BASE_X_FD_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_1000BASE_X_FD = (TJA1101_1000BASE_X_Full_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_1000BASE_X_HD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_1000BASE_X_HD_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_1000BASE_X_HD = (TJA1101_1000BASE_X_Half_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_1000BASE_T_FD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_1000BASE_T_FD_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_1000BASE_T_FD = (TJA1101_1000BASE_T_Full_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_1000BASE_T_HD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_1000BASE_T_HD_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_1000BASE_T_HD = (TJA1101_1000BASE_T_Half_Duplex_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_100BASE_T1_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_100BASE_T1_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_100BASE_T1 = (TJA1101_100BASE_T1_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_1000BASE_RTPGE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_1000BASE_RTPGE_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1100_1000BASE_RTPGE = (TJA1101_1000BASE_RTPGE_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Extended Control register
/** The function supports the following parameter:
* \param enLC  possible values:  link control enabled, link control disabled
* \param enPM  possible values:  no change, normal mode, standby mode, sleep request
* \param enSJT  possible values:  slave jitter test enabled, slave jitter test disabled
* \param enTRS  possible values:  forces restart of training phase, stops training phase
* \param enTM  possible values:  no test mode, BroadR Reach test mode 1, BroadR Reach test mode 2, BroadR Reach test mode 3, BroadR Reach test mode 4, BroadR Reach test mode 5
* \param enCBT  possible values:  forces TDR based cable test, stops TDR based cable test
* \param enLM  possible values:  internal loopback, external loopback1, external_loopback2, remote loopback
* \param enCFEN  possible values:  configuration register access enabled, configuration register access disabled
* \param enCF_INH  possible values:  INH switched off in Disable mode, INH switched on in Disable mode
* \param enWR  possible values:  Start sending idle symbols as bus wakeup signal, No wakeup signal to be sent
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_setExtendedControl(TJA110x_Extended_Control_Reg_t* pTJA110xECR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte	cData[3] = {0, 0, 0};
  Byte	cMask[3] = {0, 0, 0};
  Word	tmp = 0;

  tmp |= (Word) (pTJA110xECR->TJA1101_LC << TJA1101_LC_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_PM << TJA1101_PM_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_SJT << TJA1101_SJT_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_TRS << TJA1101_TRS_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_TM << TJA1101_TM_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_CBT << TJA1101_CBT_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_LM << TJA1101_LM_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_CFEN << TJA1101_CFEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xECR->TJA1101_WR << TJA1101_WR_SHIFT);	// shift valid value to correct bit position and add to data
  
  // create address to write data to
  cData[0] = TJA1101_EXTENDED_CONTROL_REG;
  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);	// MSB
  cData[2] = (Byte) (0x000000FF & tmp);			// LSB

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_EXTENDED_CONTROL_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_EXTENDED_CONTROL_REG_MASK);			// LSB

  // write data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

  return ((NXP_TJA1100_Error_Code_t)enStatus);
}
//************************************

/// This function is used to get data from the Extended Control register
/** The function supports the following parameter:
* \param *penLC  possible values:  link control enabled, link control disabled
* \param *penPM  possible values:  no change, normal mode, standby mode, sleep request
* \param *penSJT  possible values:  slave jitter test enabled, slave jitter test disabled
* \param *penTRS  possible values:  forces restart of training phase, stops training phase
* \param *penTM  possible values:  no test mode, BroadR Reach test mode 1, BroadR Reach test mode 2, BroadR Reach test mode 3, BroadR Reach test mode 4, BroadR Reach test mode 5
* \param *penCBT  possible values:  forces TDR based cable test, stops TDR based cable test
* \param *penLM  possible values:  internal loopback, external loopback1, external_loopback2, remote loopback
* \param *penCFEN  possible values:  configuration register access enabled, configuration register access disabled
* \param *penCF_INH  possible values:  INH switched off in Disable mode, INH switched on in Disable mode
* \param *penWR  possible values:  Start sending idle symbols as bus wakeup signal, No wakeup signal to be sent
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getExtendedControl(TJA110x_Extended_Control_Reg_t* pTJA110xECR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_EXTENDED_CONTROL_REG;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_EXTENDED_CONTROL_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_EXTENDED_CONTROL_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LC_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LC_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_LC = (TJA1101_LINK_CONTROL_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PM_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_PM = (TJA1101_POWER_MODE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SJT_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SJT_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_SJT = (TJA1101_SLAVE_JITTER_TEST_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TRS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TRS_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_TRS = (TJA1101_TRAINING_RESTART_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TM_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_TM = (TJA1101_TEST_MODE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_CBT_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_CBT_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_CBT = (TJA1101_CABLE_TEST_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LM_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_LM = (TJA1101_LOOPBACK_MODE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_CFEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_CFEN_SHIFT);				// shift to right aligned position
  pTJA110xECR->TJA1101_CFEN = (TJA1101_CONFIG_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_WR_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_WR_SHIFT);					// shift to right aligned position
  pTJA110xECR->TJA1101_WR = (TJA1101_WAKE_REQUEST_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to set data of the Configuration 1 register
/** The function supports the following parameter:
* \param enMS  possible values:  PHY configured as MASTER, PHY configured as SLAVE
* \param enAOP  possible values:  autonomous operation, managed operation
* \param enLL  possible values:  cable length less 5m, cable length 5to10m, cable length 10to15m, cable length longer 15m
* \param enTXA  possible values:  transmit amplitude nom 500mV, transmit amplitude nom 750 mV, transmit amplitude nom 1000mV, transmit amplitude nom 1250 mV
* \param enMIIM  possible values:  MII mode enabled, RMII mode enabled _50MHz input at REFCLK_IN, RMII mode enabled _25MHz XTAL, Reverse MII mode
* \param enMIID  possible values:  standard output driver strength, reduced output driver strength
* \param enSCNFM  possible values:  confirmation needed to go to sleep, no confirmation needed to go to sleep
* \param enLEDM  possible values:  link status, frame reception, symbol error, CRS signal
* \param enLEDEN  possible values:  LED output enabled, LED output disabled wakeup input enabled
* \param enCFW  possible values:  Ratio metric input threshold _VDDIO, Absolute input threshold
* \param enAPD  possible values:  Autonomous power down enabled, Autonomous power down disabled
* \param enLPSACT  possible values:  Autonomous transition Normal to Sleep Request enabled, Autonomous transition Normal to Sleep Request disabled
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_setConfiguration1(TJA110x_Configuration_1_Reg_t* pTJA110xCFG1R, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte	cData[3] = {0, 0, 0};
  Byte	cMask[3] = {0, 0, 0};
  Word	tmp = 0;

  tmp |= (Word) (pTJA110xCFG1R->TJA1101_MS << TJA1101_MS_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_WU_LOCAL << TJA1101_WAKEUP_LOCAL_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_REACT_RE_WU << TJA1101_REACT_REMOTE_WAKEUP_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_REACT_LO_WU << TJA1101_REACT_LOCALWAKEUP_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_MIIM << TJA1101_MIIM_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_MIID << TJA1101_MIID_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_SLEEPCONF << TJA1101_SCNFM_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_LPS_WUR << TJA1101_LPS_WUR_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_SLEEP_ACK << TJA1101_SLEEP_ACK_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_FW_REMOTE_WU << TJA1101_FWD_REMOTE_WAKEUP_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_APD << TJA1101_APD_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG1R->TJA1101_LPSACT << TJA1101_LPSACT_SHIFT);	// shift valid value to correct bit position and add to data
  
// create address to write data to
  cData[0] = TJA1101_CONFIGURATION_1_REG;
  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);		// MSB
  cData[2] = (Byte) (0x000000FF & tmp);		// LSB

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_CONFIGURATION_1_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_CONFIGURATION_1_REG_MASK);		// LSB

  // write data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Configuration 1 register
/** The function supports the following parameter:
* \param *penMS  possible values:  PHY configured as MASTER, PHY configured as SLAVE
* \param *penAOP  possible values:  autonomous operation, managed operation
* \param *penLL  possible values:  cable length less 5m, cable length 5to10m, cable length 10to15m, cable length longer 15m
* \param *penTXA  possible values:  transmit amplitude nom 500mV, transmit amplitude nom 750 mV, transmit amplitude nom 1000mV, transmit amplitude nom 1250 mV
* \param *penMIIM  possible values:  MII mode enabled, RMII mode enabled _50MHz input at REFCLK_IN, RMII mode enabled _25MHz XTAL, Reverse MII mode
* \param *penMIID  possible values:  standard output driver strength, reduced output driver strength
* \param *penSCNFM  possible values:  confirmation needed to go to sleep, no confirmation needed to go to sleep
* \param *penLEDM  possible values:  link status, frame reception, symbol error, CRS signal
* \param *penLEDEN  possible values:  LED output enabled, LED output disabled wakeup input enabled
* \param *penCFW  possible values:  Ratio metric input threshold _VDDIO, Absolute input threshold
* \param *penAPD  possible values:  Autonomous power down enabled, Autonomous power down disabled
* \param *penLPSACT  possible values:  Autonomous transition Normal to Sleep Request enabled, Autonomous transition Normal to Sleep Request disabled
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getConfiguration1(TJA110x_Configuration_1_Reg_t* pTJA110xCFG1R, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_CONFIGURATION_1_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_CONFIGURATION_1_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_CONFIGURATION_1_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_MS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_MS_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_MS = (TJA1101_MASTER_SLAVE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_WAKEUP_LOCAL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_WAKEUP_LOCAL_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_WU_LOCAL = (TJA1101_WAKEUP_LOCAL_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_REACT_REMOTE_WAKEUP_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_REACT_REMOTE_WAKEUP_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_REACT_RE_WU = (TJA1101_REACT_REMOTE_WAKEUP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_REACT_LOCALWAKEUP_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_REACT_LOCALWAKEUP_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_REACT_LO_WU = (TJA1101_REACT_LOCAL_WAKEUP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_MIIM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_MIIM_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_MIIM = (TJA1101_MII_Mode_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_MIID_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_MIID_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_MIID = (TJA1101_MII_DRIVER_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SCNFM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SCNFM_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_SLEEPCONF = (TJA1101_SLEEP_CONFIRM_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LPS_WUR_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LPS_WUR_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_LPS_WUR = (TJA1101_LPS_WUR_SETTINGS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SLEEP_ACK_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SLEEP_ACK_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_SLEEP_ACK = (TJA1101_SLEEP_ACK_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_FWD_REMOTE_WAKEUP_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_FWD_REMOTE_WAKEUP_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_FW_REMOTE_WU = (TJA1101_FWD_REMOTE_WAKEUP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_APD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_APD_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_APD = (TJA1101_AUTO_PWD_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LPSACT_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LPSACT_SHIFT);				// shift to right aligned position
  pTJA110xCFG1R->TJA1101_LPSACT = (TJA1101_LPS_ACTIVE_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to set data of the Configuration 2 register
/** The function supports the following parameter:
* \param enPHYAD  possible values: [0 - 65535]
* \param enSNRA  possible values:  SNR averaging over 32 symbols, SNR over 64 symbols, SNR averaging over 128 symbols, SNR averaging over 256 symbols
* \param enSNRWL  possible values:  no warning limit, class A SN ratio limit, class B SN ratio limit, class C SN ratio limit, class D SN ratio limit, class E SN ratio limit, class F SN ratio limit, class G SN ratio limit
* \param enSNRFL  possible values:  no fail limit, class A SN ratio limit, class B SN ratio limit, class C SN ratio limit, class D SN ratio limit, class E SN ratio limit, class F SN ratio limit, class G SN ratio limit
* \param enJE  possible values:  packets up to 16kB are supported, packets up to 4kB are supported
* \param enSRT  possible values:  400ns timeout, 1ms timeout, 4ms timeout, 16ms timeout
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_setConfiguration2(TJA110x_Configuration_2_Reg_t* pTJA110xCFG2R, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte	cData[3] = {0, 0, 0};
  Byte	cMask[3] = {0, 0, 0};
  Word	tmp = 0;

  tmp |= (Word) (pTJA110xCFG2R->TJA1101_PHYAD << TJA1101_PHYAD_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG2R->TJA1101_SQIAVG << TJA1101_SQIA_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG2R->TJA1101_SQIWL << TJA1101_SQIWL_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG2R->TJA1101_SQIFL << TJA1101_SQIFL_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG2R->TJA1101_JE << TJA1101_JE_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (pTJA110xCFG2R->TJA1101_SRT << TJA1101_SRT_SHIFT);	// shift valid value to correct bit position and add to data
  
// create address to write data to
  cData[0] = TJA1101_CONFIGURATION_2_REG;
  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);		// MSB
  cData[2] = (Byte) (0x000000FF & tmp);				// LSB

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_CONFIGURATION_2_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_CONFIGURATION_2_REG_MASK);			// LSB

  // write data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//************************************
/// This function is used to get data from the Configuration 2 register
/** The function supports the following parameter:
* \param *penPHYAD  possible values: [0 - 65535]
* \param *penSNRA  possible values:  SNR averaging over 32 symbols, SNR over 64 symbols, SNR averaging over 128 symbols, SNR averaging over 256 symbols
* \param *penSNRWL  possible values:  no warning limit, class A SN ratio limit, class B SN ratio limit, class C SN ratio limit, class D SN ratio limit, class E SN ratio limit, class F SN ratio limit, class G SN ratio limit
* \param *penSNRFL  possible values:  no fail limit, class A SN ratio limit, class B SN ratio limit, class C SN ratio limit, class D SN ratio limit, class E SN ratio limit, class F SN ratio limit, class G SN ratio limit
* \param *penJE  possible values:  packets up to 16kB are supported, packets up to 4kB are supported
* \param *penSRT  possible values:  400ns timeout, 1ms timeout, 4ms timeout, 16ms timeout
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getConfiguration2(TJA110x_Configuration_2_Reg_t* pTJA110xCFG2R, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_CONFIGURATION_2_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_CONFIGURATION_2_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_CONFIGURATION_2_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PHYAD_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PHYAD_SHIFT);				// shift to right aligned position
  pTJA110xCFG2R->TJA1101_PHYAD = (TJA1101_PHYAD4to0_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SQIA_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SQIA_SHIFT);				// shift to right aligned position
  pTJA110xCFG2R->TJA1101_SQIAVG = (TJA1101_SQI_Averaging_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SQIWL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SQIWL_SHIFT);				// shift to right aligned position
  pTJA110xCFG2R->TJA1101_SQIWL = (TJA1101_SQI_WLIMIT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SQIFL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SQIFL_SHIFT);				// shift to right aligned position
  pTJA110xCFG2R->TJA1101_SQIFL = (TJA1101_SQI_FAILLIMIT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_JE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_JE_SHIFT);				// shift to right aligned position
  pTJA110xCFG2R->TJA1101_JE = (TJA1101_JUMBO_ENABLE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SRT_MASK);					// mask desired bits
  pTJA110xCFG2R->TJA1101_SRT = (TJA1101_SLEEP_REQUEST_TO_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to get data from the Symbol Error Counter register
/** The function supports the following parameter:
* \param *penSEC  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getSymbolErrorCounter(TJA110x_Symbol_Error_Counter_Reg_t* penSEC, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_SYMBOL_ERROR_COUNTER_REG;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_SYMBOL_ERROR_COUNTER_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_SYMBOL_ERROR_COUNTER_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  penSEC->TJA1101_SEC = (TJA110x_SYM_ERR_CNT_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
#if 0
/// This function is used to get data from the Interrupt Source register
/** The function supports the following parameter:
* \param *penPO  possible values:  power on detected, no power on detected
* \param *penWU  possible values:  wake up detected, no wake up detected
* \param *penWUR  possible values:  wake up request detected, no wake up request detected
* \param *penLPSR  possible values:  LPS code groups received, no LPS code groups received
* \param *penPHYIF  possible values:  PHY initialization error detected, no PHY initialization error
* \param *penLSF  possible values:  link status changed from OK to FAIL, no change of link status
* \param *penLSU  possible values:  link status changed from FAIL to OK, no change of link status
* \param *penSYMBE  possible values:  symbol error detected, no symbol error detected
* \param *penTF  possible values:  training phase failure detected, no training phase failure detected
* \param *penSNRW  possible values:  SNR value below warning limit, SNR value above warning limit
* \param *penCTRLE  possible values:  SMI control error detected, no SMI control error detected
* \param *penTXEC  possible values:  TXEN clamping detected, no TXEN clamping detected
* \param *penUVE  possible values:  undervoltage detected, no undervoltage detected
* \param *penUVR  possible values:  undervoltage recovery detected, no undervoltage recovery
* \param *penTER  possible values:  overtemperature error detected, no overtemperature error detected
* \param *penSLPABRT  possible values:  sleep transition aborted, sleep transition not aborted
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA1100_getInterruptSource(TJA1100_PWON_t* penPO, TJA1100_WAKEUP_t* penWU, TJA1100_WUR_RECEIVED_t* penWUR, TJA1100_LPS_RECEIVED_t* penLPSR, TJA1100_PHY_INIT_FAIL_t* penPHYIF, TJA1100_LINK_STATUS_FAIL_t* penLSF, TJA1100_LINK_STATUS_UP_t* penLSU, TJA1100_SYM_ERROR_t* penSYMBE, TJA1100_TRAINING_FAILED_t* penTF, TJA1100_SNR_WARNING_t* penSNRW, TJA1100_CONTROL_ERROR_t* penCTRLE, TJA1100_TXEN_CLAMPED_t* penTXEC, TJA1100_UV_ERROR_t* penUVE, TJA1100_UV_RECOVERY_t* penUVR, TJA1100_TEMP_ERROR_t* penTER, TJA1100_SLEEP_ABORT_t* penSLPABRT, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1100_INTERRUPT_SOURCE_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1100_INTERRUPT_SOURCE_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1100_INTERRUPT_SOURCE_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_PO_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_PO_SHIFT);				// shift to right aligned position
  *penPO = (TJA1100_PWON_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_WU_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_WU_SHIFT);				// shift to right aligned position
  *penWU = (TJA1100_WAKEUP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_WUR_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_WUR_SHIFT);				// shift to right aligned position
  *penWUR = (TJA1100_WUR_RECEIVED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LPSR_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LPSR_SHIFT);				// shift to right aligned position
  *penLPSR = (TJA1100_LPS_RECEIVED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_PHYIF_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_PHYIF_SHIFT);				// shift to right aligned position
  *penPHYIF = (TJA1100_PHY_INIT_FAIL_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LSF_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LSF_SHIFT);				// shift to right aligned position
  *penLSF = (TJA1100_LINK_STATUS_FAIL_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LSU_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LSU_SHIFT);				// shift to right aligned position
  *penLSU = (TJA1100_LINK_STATUS_UP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SYMBE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_SYMBE_SHIFT);				// shift to right aligned position
  *penSYMBE = (TJA1100_SYM_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TF_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TF_SHIFT);				// shift to right aligned position
  *penTF = (TJA1100_TRAINING_FAILED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SNRW_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_SNRW_SHIFT);				// shift to right aligned position
  *penSNRW = (TJA1100_SNR_WARNING_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_CTRLE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_CTRLE_SHIFT);				// shift to right aligned position
  *penCTRLE = (TJA1100_CONTROL_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TXEC_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TXEC_SHIFT);				// shift to right aligned position
  *penTXEC = (TJA1100_TXEN_CLAMPED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_UVE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_UVE_SHIFT);				// shift to right aligned position
  *penUVE = (TJA1100_UV_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_UVR_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_UVR_SHIFT);				// shift to right aligned position
  *penUVR = (TJA1100_UV_RECOVERY_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TER_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TER_SHIFT);				// shift to right aligned position
  *penTER = (TJA1100_TEMP_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SLPABRT_MASK);					// mask desired bits
  *penSLPABRT = (TJA1100_SLEEP_ABORT_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Interrupt Mask register
/** The function supports the following parameter:
* \param enPOEN  possible values:  PWON interrupt enabled, PWON interrupt disabled
* \param enWUEN  possible values:  WAKEUP interrupt enabled, WAKEUP interrupt disabled
* \param enWUREN  possible values:  WAKEUP interrupt enabled, WAKEUP interrupt disabled
* \param enLPSREN  possible values:  LPS_RECEIVED interrupt enabled, LPS_RECEIVED interrupt disabled
* \param enPHYIFEN  possible values:  PHY_INIT_FAIL interrupt enabled, PHY_INIT_FAIL interrupt disabled
* \param enLSFEN  possible values:  LINK_STATUS_FAIL interrupt enabled, LINK_STATUS_FAIL interrupt disabled
* \param enLSUEN  possible values:  LINK_STATUS_UP interrupt enabled, LINK_STATUS_UP interrupt disabled
* \param enSEEN  possible values:  SYM_ERROR interrupt enabled, SYM_ERROR interrupt disabled
* \param enTFEN  possible values:  TRAINING_FAILED interrupt enabled, TRAINING_FAILED interrupt disabled
* \param enSNWEN  possible values:  SNR_WARNING interrupt enabled, SNR_WARNING interrupt disabled
* \param enCTRLEREN  possible values:  CONTROL_ERROR interrupt enabled, CONTROL_ERROR interrupt disabled
* \param enTXECEN  possible values:  TXEN_CLAMPED interrupt enabled, TXEN_CLAMPED interrupt disabled
* \param enUVEEN  possible values:  UV_ERROR interrupt enabled, UV_ERROR interrupt disabled
* \param enUVREN  possible values:  UV_RECOVERY interrupt enabled, UV_RECOVERY interrupt disabled
* \param enTEREN  possible values:  TEMP_ERROR interrupt enabled, TEMP_ERROR interrupt disabled
* \param enSLPABRTEN  possible values:  Sleep transition aborted interrupt enabled, Sleep transition aborted interrupt disabled
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA1100_setInterruptMask(TJA1100_PWON_EN_t enPOEN, TJA1100_WAKEUP_EN_t enWUEN, TJA1100_WUR_RECEIVED_EN_t enWUREN, TJA1100_LPS_RECEIVED_EN_t enLPSREN, TJA1100_PHY_INIT_FAIL_EN_t enPHYIFEN, TJA1100_LINK_STATUS_FAIL_EN_t enLSFEN, TJA1100_LINK_STATUS_UP_EN_t enLSUEN, TJA1100_SYM_ERROR_EN_t enSEEN, TJA1100_TRAINING_FAILED_EN_t enTFEN, TJA1100_SNR_WARNING_EN_t enSNWEN, TJA1100_CONTROL_ERROR_EN_t enCTRLEREN, TJA1100_TXEN_CLAMPED_EN_t enTXECEN, TJA1100_UV_ERROR_EN_t enUVEEN, TJA1100_UV_RECOVERY_EN_t enUVREN, TJA1100_TEMP_ERROR_EN_t enTEREN, TJA1100_SLEEP_ABORT_EN_t enSLPABRTEN, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte	cData[3] = {0, 0, 0};
  Byte	cMask[3] = {0, 0, 0};
  Word	tmp = 0;

  tmp |= (Word) (enPOEN << TJA1100_POEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enWUEN << TJA1100_WUEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enWUREN << TJA1100_WUREN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enLPSREN << TJA1100_LPSREN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enPHYIFEN << TJA1100_PHYIFEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enLSFEN << TJA1100_LSFEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enLSUEN << TJA1100_LSUEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enSEEN << TJA1100_SEEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enTFEN << TJA1100_TFEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enSNWEN << TJA1100_SNWEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enCTRLEREN << TJA1100_CTRLEREN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enTXECEN << TJA1100_TXECEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enUVEEN << TJA1100_UVEEN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enUVREN << TJA1100_UVREN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enTEREN << TJA1100_TEREN_SHIFT);	// shift valid value to correct bit position and add to data
  tmp |= (Word) (enSLPABRTEN << TJA1100_SLPABRTEN_SHIFT);	// shift valid value to correct bit position and add to data
  
// create address to write data to
  cData[0] = TJA1100_INTERRUPT_MASK_REG;
  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);		// MSB
  cData[2] = (Byte) (0x000000FF & tmp);		// LSB

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1100_INTERRUPT_MASK_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1100_INTERRUPT_MASK_REG_MASK);		// LSB

  // write data via SMI
  enStatus = SMI_Send (cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Interrupt Mask register
/** The function supports the following parameter:
* \param *penPOEN  possible values:  PWON interrupt enabled, PWON interrupt disabled
* \param *penWUEN  possible values:  WAKEUP interrupt enabled, WAKEUP interrupt disabled
* \param *penWUREN  possible values:  WAKEUP interrupt enabled, WAKEUP interrupt disabled
* \param *penLPSREN  possible values:  LPS_RECEIVED interrupt enabled, LPS_RECEIVED interrupt disabled
* \param *penPHYIFEN  possible values:  PHY_INIT_FAIL interrupt enabled, PHY_INIT_FAIL interrupt disabled
* \param *penLSFEN  possible values:  LINK_STATUS_FAIL interrupt enabled, LINK_STATUS_FAIL interrupt disabled
* \param *penLSUEN  possible values:  LINK_STATUS_UP interrupt enabled, LINK_STATUS_UP interrupt disabled
* \param *penSEEN  possible values:  SYM_ERROR interrupt enabled, SYM_ERROR interrupt disabled
* \param *penTFEN  possible values:  TRAINING_FAILED interrupt enabled, TRAINING_FAILED interrupt disabled
* \param *penSNWEN  possible values:  SNR_WARNING interrupt enabled, SNR_WARNING interrupt disabled
* \param *penCTRLEREN  possible values:  CONTROL_ERROR interrupt enabled, CONTROL_ERROR interrupt disabled
* \param *penTXECEN  possible values:  TXEN_CLAMPED interrupt enabled, TXEN_CLAMPED interrupt disabled
* \param *penUVEEN  possible values:  UV_ERROR interrupt enabled, UV_ERROR interrupt disabled
* \param *penUVREN  possible values:  UV_RECOVERY interrupt enabled, UV_RECOVERY interrupt disabled
* \param *penTEREN  possible values:  TEMP_ERROR interrupt enabled, TEMP_ERROR interrupt disabled
* \param *penSLPABRTEN  possible values:  Sleep transition aborted interrupt enabled, Sleep transition aborted interrupt disabled
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA1100_getInterruptMask(TJA1100_PWON_EN_t* penPOEN, TJA1100_WAKEUP_EN_t* penWUEN, TJA1100_WUR_RECEIVED_EN_t* penWUREN, TJA1100_LPS_RECEIVED_EN_t* penLPSREN, TJA1100_PHY_INIT_FAIL_EN_t* penPHYIFEN, TJA1100_LINK_STATUS_FAIL_EN_t* penLSFEN, TJA1100_LINK_STATUS_UP_EN_t* penLSUEN, TJA1100_SYM_ERROR_EN_t* penSEEN, TJA1100_TRAINING_FAILED_EN_t* penTFEN, TJA1100_SNR_WARNING_EN_t* penSNWEN, TJA1100_CONTROL_ERROR_EN_t* penCTRLEREN, TJA1100_TXEN_CLAMPED_EN_t* penTXECEN, TJA1100_UV_ERROR_EN_t* penUVEEN, TJA1100_UV_RECOVERY_EN_t* penUVREN, TJA1100_TEMP_ERROR_EN_t* penTEREN, TJA1100_SLEEP_ABORT_EN_t* penSLPABRTEN, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1100_INTERRUPT_MASK_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1100_INTERRUPT_MASK_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1100_INTERRUPT_MASK_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_POEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_POEN_SHIFT);				// shift to right aligned position
  *penPOEN = (TJA1100_PWON_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_WUEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_WUEN_SHIFT);				// shift to right aligned position
  *penWUEN = (TJA1100_WAKEUP_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_WUREN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_WUREN_SHIFT);				// shift to right aligned position
  *penWUREN = (TJA1100_WUR_RECEIVED_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LPSREN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LPSREN_SHIFT);				// shift to right aligned position
  *penLPSREN = (TJA1100_LPS_RECEIVED_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_PHYIFEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_PHYIFEN_SHIFT);				// shift to right aligned position
  *penPHYIFEN = (TJA1100_PHY_INIT_FAIL_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LSFEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LSFEN_SHIFT);				// shift to right aligned position
  *penLSFEN = (TJA1100_LINK_STATUS_FAIL_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_LSUEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_LSUEN_SHIFT);				// shift to right aligned position
  *penLSUEN = (TJA1100_LINK_STATUS_UP_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SEEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_SEEN_SHIFT);				// shift to right aligned position
  *penSEEN = (TJA1100_SYM_ERROR_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TFEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TFEN_SHIFT);				// shift to right aligned position
  *penTFEN = (TJA1100_TRAINING_FAILED_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SNWEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_SNWEN_SHIFT);				// shift to right aligned position
  *penSNWEN = (TJA1100_SNR_WARNING_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_CTRLEREN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_CTRLEREN_SHIFT);				// shift to right aligned position
  *penCTRLEREN = (TJA1100_CONTROL_ERROR_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TXECEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TXECEN_SHIFT);				// shift to right aligned position
  *penTXECEN = (TJA1100_TXEN_CLAMPED_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_UVEEN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_UVEEN_SHIFT);				// shift to right aligned position
  *penUVEEN = (TJA1100_UV_ERROR_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_UVREN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_UVREN_SHIFT);				// shift to right aligned position
  *penUVREN = (TJA1100_UV_RECOVERY_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_TEREN_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1100_TEREN_SHIFT);				// shift to right aligned position
  *penTEREN = (TJA1100_TEMP_ERROR_EN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1100_SLPABRTEN_MASK);					// mask desired bits
  *penSLPABRTEN = (TJA1100_SLEEP_ABORT_EN_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
#endif
//******************************************************************

/// This function is used to get data from the Communication Status register
/** The function supports the following parameter:
* \param *penLU  possible values:  OK, FAIL
* \param *penTXM  possible values:  transmitter disabled, tx_mode SEND_N, tx_mode SEND_I, tx_mode SEND_Z
* \param *penLRS  possible values:  loc_rcvr_status is OK, loc_rcvr_status is NOT_OK since last read
* \param *penRRS  possible values:  rem_rcvr_status is OK, rem_rcvr_status is NOT_OK since last read
* \param *penSCRL  possible values:  Descrambler locked, Descrambler unlocked
* \param *penSSDE  possible values:  SSD error detected since last read, no SSD error detected
* \param *penESDE  possible values:  ESD error detected since last read, no ESD error detected
* \param *penSNR  possible values:  no SN ratio value available, class A SN ratio, class B SN ratio, class C SN ratio, class D SN ratio, class E SN ratio, class F SN ratio, class G SN ratio
* \param *penRXE  possible values:  receive error detected since last read, no receive error detected
* \param *penTXE  possible values:  transmit error code received since last read, no transmit error code received
* \param *penPHYS  possible values:  PHY Idle, PHY Init, PHY Config, PHY Offline, PHY Active, PHY Isolate, PHY Cable test, PHY Testmode
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getCommunicationStatus(TJA110x_Communication_Status_Reg_t* pTJA110xCSR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_COMMUNICATION_STATUS_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_COMMUNICATION_STATUS_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_COMMUNICATION_STATUS_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LU_MASK);						// mask desired bits
  cResult >>= (Word)(TJA1101_LU_SHIFT);						// shift to right aligned position
  pTJA110xCSR->TJA1101_LU = (TJA1101_LINK_UP_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TXM_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TXM_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_TXM = (TJA1101_TX_MODE_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LRS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LRS_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_LRS = (TJA1101_LOC_RCVR_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RRS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RRS_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_RRS = (TJA1101_REM_RCVR_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SCRL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SCRL_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_SCRL = (TJA1101_SCR_LOCKED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SSDE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SSDE_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_SSDE = (TJA1101_SSD_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ESDE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ESDE_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_ESDE = (TJA1101_ESD_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SQI_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SQI_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_SQI = (TJA1101_SQI_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RXE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RXE_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_RXE = (TJA1101_RECEIVE_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TXE_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TXE_SHIFT);				// shift to right aligned position
  pTJA110xCSR->TJA1101_TXE = (TJA1101_TRANSMIT_ERROR_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PHYS_MASK);					// mask desired bits
  pTJA110xCSR->TJA1101_PHYS = (TJA1101_PHY_STATE_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to get data from the General Status register
/** The function supports the following parameter:
* \param *penINTS  possible values:  Unmasked interrupt currently active, all interrupts cleared
* \param *penPLLL  possible values:  PLL stable and locked, PLL unstable and not locked
* \param *penLWU  possible values:  local wakeup detected, no local wakeup detected
* \param *penRWU  possible values:  remote wakeup detected, no remote wakeup detected
* \param *penDDWU  possible values:  data detected in sleep request, no data detected in sleep request
* \param *penENS  possible values:  EN was Low since last read, EN not Low
* \param *penRSTS  possible values:  Hardware reset detected since last read, No hardware reset detected
* \param *penLFCNT  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getGeneralStatus(TJA110x_General_Status_Reg_t* pTJA110xGSR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_GENERAL_STATUS_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_GENERAL_STATUS_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_GENERAL_STATUS_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_INTS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_INTS_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_INTS = (TJA1101_INT_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PLLL_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PLLL_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_PLLL = (TJA1101_PLL_LOCKED_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LWU_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LWU_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_LWU = (TJA1101_LOCAL_WU_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RWU_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RWU_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_RWU = (TJA1101_REMOTE_WU_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_DDWU_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_DDWU_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_DDWU = (TJA1101_DATA_DET_WU_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ENS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ENS_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_ENS = (TJA1101_EN_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RSTS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_RSTS_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_RSTS = (TJA1101_RESET_STATUS_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LFCNT_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_LFCNT_SHIFT);				// shift to right aligned position
  pTJA110xGSR->TJA1101_LFCNT = (TJA1101_LINKFAIL_COUNT_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to get data from the External Status register
/** The function supports the following parameter:
* \param *penUV3V3S  possible values:  undervoltage detected on VDDA_3V3, no undervoltage detected on VDDA_3V3
* \param *penUVD1V8S  possible values:  undervoltage detected on VDDD_1V8, no undervoltage detected on VDDD_1V8
* \param *penUVA1V8S  possible values:  undervoltage detected on VDDA_1V8, no undervoltage detected on VDDA_1V8
* \param *penUVIOS  possible values:  undervoltage detected on VDDIO1 VDDIO2, no undervoltage detected on VDDIO1 VDDIO2
* \param *penTEMPHS  possible values:  temperature above high level, temperature below high level
* \param *penTEMPWS  possible values:  temperature above warning level, temperature below warning level
* \param *penSDS  possible values:  short circuit detected since last read, no short circuit detected
* \param *penODS  possible values:  open detected since last read, no open detected
* \param *penPDMS  possible values:  polarity inversion at MDI, no polarity inversion at MDI detected
* \param *penIDS  possible values:  interleaving ternary symbols detected, no interleaving ternary symbols detected
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getExternalStatus(TJA110x_External_Status_Reg_t* pTJA110xESR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_EXTERNAL_STATUS_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_EXTERNAL_STATUS_REG_MASK) >> 8);		// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_EXTERNAL_STATUS_REG_MASK);		// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UVD3V3S_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UVD3V3S_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_UVD3V3S = (TJA1101_UV_VDDD_3V3_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UV3V3S_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UV3V3S_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_UV3V3S = (TJA1101_UV_VDDA_3V3_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UVD1V8S_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UVD1V8S_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_UVD1V8S = (TJA1101_UV_VDDD_1V8_t)( cResult );	// deliver result

//  // split received byte into bit groups
//  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
//  cResult &= (Word)(TJA1100_UVA1V8S_MASK);					// mask desired bits
//  cResult >>= (Word)(TJA1100_UVA1V8S_SHIFT);				// shift to right aligned position
//  *penUVA1V8S = (TJA1100_UV_VDDA_1V8_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_UVIOS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_UVIOS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_UVIOS = (TJA1101_UV_VDDIO_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TEMPHS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TEMPHS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_TEMPHS = (TJA1101_TEMP_HIGH_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_TEMPWS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_TEMPWS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_TEMPWS = (TJA1101_TEMP_WARN_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_SDS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_SDS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_SDS = (TJA1101_SHORT_DETECT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_ODS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_ODS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_ODS = (TJA1101_OPEN_DETECT_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_PDMS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_PDMS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_PDMS = (TJA1101_POLARITY_DETECTOR_MDI_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_IDS_MASK);					// mask desired bits
  cResult >>= (Word)(TJA1101_IDS_SHIFT);				// shift to right aligned position
  pTJA110xESR->TJA1101_IDS = (TJA1101_INTERLEAVE_DETECT_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}
//******************************************************************
/// This function is used to get data from the Link Fail Counter register
/** The function supports the following parameter:
* \param *penLRC  possible values: [0 - 65535]
* \param *penRRC  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getLinkFailCounter(TJA110x_Link_Fail_Counter_Reg_t* pTJA110xLFCR, Byte enPhyAddr)
{
  NXP_TJA1100_Error_Code_t	enStatus;
  Byte		cData[3] = {0, 0, 0};
  Byte		cMask[3] = {0, 0, 0};
  Word		cResult = 0;

  // create address to read data from
  cData[0] = TJA1101_LINK_FAIL_COUNTER_REG ;

  cMask[0] = 0;
  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_LINK_FAIL_COUNTER_REG_MASK) >> 8);	// MSB
  cMask[2] = (Byte) (0x000000FF & TJA1101_LINK_FAIL_COUNTER_REG_MASK);			// LSB

  // read data via SMI
  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_LRC_MASK);									// mask desired bits
  cResult >>= (Word)(TJA1101_LRC_SHIFT);								// shift to right aligned position
  pTJA110xLFCR->TJA1100_LRC = (TJA1101_LOC_RCVR_COUNTER_t)( cResult );	// deliver result

  // split received byte into bit groups
  cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
  cResult &= (Word)(TJA1101_RRC_MASK);									// mask desired bits
  pTJA110xLFCR->TJA1100_RRC = (TJA1101_REM_RCVR_COUNTER_t)( cResult );	// deliver result

  return ((NXP_TJA1100_Error_Code_t) enStatus);
}

//******************************************************************
/// This function is used to get data from the Link Fail Counter register
/** The function supports the following parameter:
* \param *penLRC  possible values: [0 - 65535]
* \param *penRRC  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_getCommonConfiguration(TJA110x_Common_Config_Reg_t* pTJA110xCCR, Byte enPhyAddr)
{
	NXP_TJA1100_Error_Code_t enStatus;
	Byte		cData[3] = {0, 0, 0};
	Byte		cMask[3] = {0, 0, 0};
	Word		cResult = 0;

	cData[0] = TJA1101_COMMON_CONFIG_REG;

	cMask[0] = 0;
	cMask[1] = (Byte) ((0x0000FF00 & TJA1101_COMMON_CONFIG_REG_MASK) >> 8);		// MSB
	cMask[2] = (Byte) (0x000000FF & TJA1101_COMMON_CONFIG_REG_MASK);		// LSB

	// read data via SMI
	enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_READ);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_AUTO_OP_MASK);
	cResult >>= (Word)(TJA1101_AUTO_OP_SHIFT);
	pTJA110xCCR->TJA1101_AUTO_OP = (TJA1101_AUTO_OP_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_CLK_MODE_MASK);
	cResult >>= (Word)(TJA1101_CLK_MODE_SHIFT);
	pTJA110xCCR->TJA1101_CLK_MODE = (TJA1101_CLK_MODE_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_LDO_MODE_MASK);
	cResult >>= (Word)(TJA1101_LDO_MODE_SHIFT);
	pTJA110xCCR->TJA1101_LDO_MODE = (TJA1101_LDO_MODE_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_CLK_DRIVER_MASK);
	cResult >>= (Word)(TJA1101_CLK_DRIVER_SHIFT);
	pTJA110xCCR->TJA1101_CLK_DRIVER = (TJA1101_CLK_DRIVER_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_CLK_HOLD_MASK);
	cResult >>= (Word)(TJA1101_CLK_HOLD_SHIFT);
	pTJA110xCCR->TJA1101_CLK_HOLD = (TJA1101_CLK_HOLD_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_LOC_WU_TIME_MASK);
	cResult >>= (Word)(TJA1101_LOC_WU_TIME_SHIFT);
	pTJA110xCCR->TJA1101_LOC_WU_TIME = (TJA1101_LOC_WU_TIME_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_CONFIG_WAKE_MASK);
	cResult >>= (Word)(TJA1101_CONFIG_WAKE_SHIFT);
	pTJA110xCCR->TJA1101_CONFIG_WAKE = (TJA1101_CONFIG_WAKE_t)(cResult);

	cResult = (((Word)cData[1]) << 8) + ((Word)cData[2]);
	cResult &= (Word)(TJA1101_CONFIG_INH_MASK);
	cResult >>= (Word)(TJA1101_CONFIG_INH_SHIFT);
	pTJA110xCCR->TJA1101_INH = (TJA1101_CONFIG_INH_t)(cResult);

	return ((NXP_TJA1100_Error_Code_t) enStatus);
}

//******************************************************************
/// This function is used to get data from the Link Fail Counter register
/** The function supports the following parameter:
* \param *penLRC  possible values: [0 - 65535]
* \param *penRRC  possible values: [0 - 65535]
* \param enPhyAddr: address of PHY that shall be accessed
* \return <b>NXP_TJA1100_Error_Code_t</b>  possible values: TJA1100_ERROR = 0, TJA1100_SUCCESS = 1
*/
NXP_TJA1100_Error_Code_t TJA110x_setCommonConfiguration(TJA110x_Common_Config_Reg_t* pTJA110xCCR, Byte enPhyAddr)
{
	  NXP_TJA1100_Error_Code_t	enStatus;
	  Byte	cData[3] = {0, 0, 0};
	  Byte	cMask[3] = {0, 0, 0};
	  Word	tmp = 0;

	  tmp |= (Word) (pTJA110xCCR->TJA1101_AUTO_OP << TJA1101_AUTO_OP_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_CLK_MODE << TJA1101_CLK_MODE_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_LDO_MODE << TJA1101_LDO_MODE_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_CLK_DRIVER << TJA1101_CLK_DRIVER_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_CLK_HOLD << TJA1101_CLK_HOLD_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_LOC_WU_TIME << TJA1101_LOC_WU_TIME_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_CONFIG_WAKE << TJA1101_CONFIG_WAKE_SHIFT);	// shift valid value to correct bit position and add to data
	  tmp |= (Word) (pTJA110xCCR->TJA1101_INH << TJA1101_CONFIG_INH_SHIFT);	// shift valid value to correct bit position and add to data

	// create address to write data to
	  cData[0] = TJA1101_COMMON_CONFIG_REG;
	  cData[1] = (Byte) ((0x0000FF00 & tmp) >> 8);		// MSB
	  cData[2] = (Byte) (0x000000FF & tmp);				// LSB

	  cMask[0] = 0;
	  cMask[1] = (Byte) ((0x0000FF00 & TJA1101_COMMON_CONFIG_REG_MASK) >> 8);		// MSB
	  cMask[2] = (Byte) (0x000000FF & TJA1101_COMMON_CONFIG_REG_MASK);			// LSB

	  // write data via SMI
	  enStatus = SMI_Send(cData, enPhyAddr, cMask, NXP_TJA1100_WRITE);

	  return ((NXP_TJA1100_Error_Code_t) enStatus);
}

//******************************************************************


