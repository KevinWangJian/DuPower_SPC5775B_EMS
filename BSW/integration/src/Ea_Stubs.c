/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */

#include "Eep.h"

/* Eep_Rb_RealSize_u32 saves the real size of the connected EEPROM.
 * This is updated when Automatic EEPROM size detection in Init phase
 * of CUBAS EEPROM Driver is ON.
 *
 * Set it to EEP_SIZE for testing purpose with AUTOSAR EEPROM Driver.
 */
//Eep_LengthType Eep_Rb_RealSize_u32 = EEP_SIZE;

/* MemIf_SetMode is currently not supported from MemIf. Therefore, no
 * one triggers Eep_SetMode service. Set it Eep_Mode to MEMIF_MODE_SLOW
 * as a default value.
 */
//MemIf_ModeType Eep_Mode = MEMIF_MODE_SLOW;

/**
 *********************************************************************
 * Spi_MainFunction_Handling(): Spi Scheduled MainFunction
 *
 * By default, Spi_MainFunction_Handling is called from Ea during
 * initialization and in MemIf_Rb_MainFunction.
 *
 * This stub function is provided here because internal EEPROM device
 * is used for testing. This needs to be removed when using
 * External SPI EEPROM device.
 *
 * \param : None
 * \return: None
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
// void Spi_MainFunction_Handling(void)
// {
// 	return;
// }

// FUNC( void, EEP_CODE ) Eep_MainFunction( void )
// {

// }
// FUNC( void, EEP_CODE ) Eep_Cancel( void )
// {

// }
// FUNC( MemIf_JobResultType, EEP_CODE ) Eep_GetJobResult( void )
// {
// 	return MEMIF_JOB_OK;
// }
// FUNC( Std_ReturnType, EEP_CODE ) Eep_Compare
// (
//     VAR( Eep_AddressType, AUTOMATIC) u32SourceAddress,
//     P2CONST( uint8, AUTOMATIC, EEP_APPL_CONST ) pTargetAddressPtr,
//     VAR( Eep_LengthType, AUTOMATIC) u32Length
// )
// {
// 	return E_OK;
// }
// FUNC( Std_ReturnType, EEP_CODE ) Eep_Write
// (
// 	VAR( Eep_AddressType, AUTOMATIC) u32TargetAddress,
//     P2CONST( uint8, AUTOMATIC, EEP_APPL_CONST ) pSourceAddressPtr,
//     VAR( Eep_LengthType, AUTOMATIC) u32Length
// )
// {
// 	return E_OK;
// }
// FUNC( Std_ReturnType, EEP_CODE ) Eep_Erase
// (
//     VAR( Eep_AddressType, AUTOMATIC) u32TargetAddress,
//     VAR( Eep_LengthType, AUTOMATIC) u32Length
// )
// {
// 	return E_OK;
// }
// FUNC( Std_ReturnType, EEP_CODE ) Eep_Read
// (
//     VAR( Eep_AddressType, AUTOMATIC) u32SourceAddress,
//     P2VAR( uint8, AUTOMATIC, EEP_APPL_DATA ) pTargetAddressPtr,
//     VAR( Eep_LengthType, AUTOMATIC) u32Length
// )
// {
// 	return E_OK;
// }
// FUNC( void, EEP_CODE ) Eep_SetMode
// ( VAR( MemIf_ModeType, AUTOMATIC ) eMode )
// {

// }
