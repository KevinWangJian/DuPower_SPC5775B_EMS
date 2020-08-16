/*
 * Eep.c
 *
 *  Created on: Jun 29, 2018
 *      Author: CIX2SGH
 */

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/


#include "Eep.h"
#include "M95640.h"
#include "Dio.h"

typedef enum tagEep_JobType{
    EEP_JOB_NONE,
    EEP_JOB_READ,
    EEP_JOB_WRITE,
    EEP_JOB_COMPARE
}Eep_JobType;

typedef struct tagEep_JobInfo{
    Eep_JobType             job;
    Eep_AddressType         offset;
    uint8                   *buffer;
    Eep_LengthType          length;
    MemIf_JobResultType     result;
}Eep_JobInfo;

/* Eep_Rb_RealSize_u32 saves the real size of the connected EEPROM.
 * This is updated when Automatic EEPROM size detection in Init phase
 * of CUBAS EEPROM Driver is ON.
 *
 * Set it to EEP_SIZE for testing purpose with AUTOSAR EEPROM Driver.
 */
Eep_LengthType Eep_Rb_RealSize_u32 = EEP_SIZE;

/* MemIf_SetMode is currently not supported from MemIf. Therefore, no
 * one triggers Eep_SetMode service. Set it Eep_Mode to MEMIF_MODE_SLOW
 * as a default value.
 */
MemIf_ModeType Eep_Mode = MEMIF_MODE_SLOW;

static Eep_JobInfo eep_current_job;


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief        The function initializes Eep module.
* @details      The function sets the internal module variables according to given
*               configuration set.
*
* @param[in]    pConfigPtr        Pointer to eeprom driver configuration set.
*
* @api
*
* @pre          @p pConfigPtr must not be @p NULL_PTR and the module status must not
*               be @p MEMIF_BUSY.
*
* @implements     Eep_Init_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/

FUNC( void, EEP_CODE ) Eep_Init
( P2CONST( Eep_ConfigType, AUTOMATIC, EEP_APPL_CONST ) pConfigPtr )
{
    eep_current_job.job = EEP_JOB_NONE;
    eep_current_job.result = MEMIF_JOB_OK;
    Dio_WriteChannel(DioConf_DioChannel_EEPROM_WP, 1);
    Dio_WriteChannel(DioConf_DioChannel_EEPROM_HOLD, 1);
    Eepm95640_Init();
}

/**
* @brief            Erase memory by writing erase value.
* @details          Starts an erase job asynchronously. The actual job is performed
 *                  by the Eep_MainFunction.
*
* @param[in]        TargetAddress        Target address in eeprom memory.
* @param[in]        Length               Number of bytes to erase by writing the erased value.
*
* @return           Std_ReturnType
* @retval           E_OK                    Erase command has been accepted.
* @retval           E_NOT_OK                Erase command has not been accepted.
*
* @api
*
* @pre              The module has to be initialized and not busy.
* @post
*
* @implements       Eep_Erase_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( Std_ReturnType, EEP_CODE ) Eep_Erase
(
    VAR( Eep_AddressType, AUTOMATIC) u32TargetAddress,
    VAR( Eep_LengthType, AUTOMATIC) u32Length
)
{
    Std_ReturnType ret = E_OK;

    ret = Eepm95640_Erase((uint16_t)u32TargetAddress, (uint16_t)u32Length);

    return ret;
}

/**
* @brief            Write one or more complete eeprom pages to the eeprom device.
* @details          Starts a write job asynchronously. The actual job is performed by
*                   Eep_MainFunction.
*
* @param[in]        TargetAddress        Target address in eeprom memory.
* @param[in]        SourceAddressPtr     Pointer to source data buffer.
* @param[in]        Length               Number of bytes to write.
*
* @return           Std_ReturnType
* @retval           E_OK                 Write command has been accepted.
* @retval           E_NOT_OK             Write command has not been accepted.
*
* @api
*
* @pre              The module has to be initialized and not busy.
*
* @implements       Eep_Write_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( Std_ReturnType, EEP_CODE ) Eep_Write
(
    VAR( Eep_AddressType, AUTOMATIC) u32TargetAddress,
    P2CONST( uint8, AUTOMATIC, EEP_APPL_CONST ) pSourceAddressPtr,
    VAR( Eep_LengthType, AUTOMATIC) u32Length
)
{
    Std_ReturnType ret = E_OK;

    if (eep_current_job.job != EEP_JOB_NONE)
    {
        return E_NOT_OK;
    }

    eep_current_job.job = EEP_JOB_WRITE;

    eep_current_job.offset = u32TargetAddress;
    eep_current_job.buffer = pSourceAddressPtr;
    eep_current_job.length = u32Length;

    return ret;
}

/**
* @brief            Reads from eeprom memory.
* @details          Starts a read job asynchronously. The actual job is performed by
*                   @p Eep_MainFunction.
*
* @param[in]        SourceAddress        Source address in eeprom memory.
* @param[in]        Length               Number of bytes to read.
* @param[out]       TargetAddressPtr    Pointer to target data buffer.
*
* @return           MemIf_JobResultType
* @retval           MEMIF_JOB_OK              Successfully completed job.
* @retval           MEMIF_JOB_FAILED          Not successfully completed job.
* @retval           MEMIF_JOB_PENDING         Still pending job (not yet completed).
* @retval           MEMIF_JOB_CANCELED        Job has been canceled.
* @retval           MEMIF_BLOCK_INCONSISTENT  Inconsistent block requested, it may
*                                             contains corrupted data.
* @retval           MEMIF_BLOCK_INVALID       Invalid block requested.
*
* @api
*
* @pre            The module has to be initialized and not busy.
* @post
*
* @implements       Eep_Read_Activity
*
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( Std_ReturnType, EEP_CODE ) Eep_Read
(
    VAR( Eep_AddressType, AUTOMATIC) u32SourceAddress,
    P2VAR( uint8, AUTOMATIC, EEP_APPL_DATA ) pTargetAddressPtr,
    VAR( Eep_LengthType, AUTOMATIC) u32Length
)
{
    Std_ReturnType ret = E_OK;

    ret = Eepm95640_Read((uint16_t)u32SourceAddress, pTargetAddressPtr, (uint16_t)u32Length);

    return ret;
}

/**
* @brief           Compares a eeprom memory area with an application data buffer.
* @details         Starts a compare job asynchronously. The actual job is performed by
*                  Eep_MainFunction.
*
* @param[in]        SourceAddress          Source address in eeprom memory.
* @param[in]        TargetAddressPtr       Pointer to source data buffer.
* @param[in]        Length                 Number of bytes to compare.
*
* @return           Std_ReturnType
* @retval           E_OK                      Compare command has been accepted.
* @retval           E_NOT_OK                   Compare command has not been accepted.
*
* @api
*
* @pre            The module has to be initialized and not busy.
*
* @implements       Eep_Compare_Activity
*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( Std_ReturnType, EEP_CODE ) Eep_Compare
(
    VAR( Eep_AddressType, AUTOMATIC) u32SourceAddress,
    P2CONST( uint8, AUTOMATIC, EEP_APPL_CONST ) pTargetAddressPtr,
    VAR( Eep_LengthType, AUTOMATIC) u32Length
)
{
    Std_ReturnType ret = E_OK;

    ret = Eepm95640_Compare((uint16_t)u32SourceAddress, pTargetAddressPtr, (uint16_t)u32Length);

    return ret;
}

/**
* @brief            Performs actual eeprom read, write, erase and compare jobs.
* @details          Bytes number processed per cycle depends by job type (erase, write, read, compare)
*                   current EEP module's operating mode (normal, fast)
*                   and write, erase Mode of Execution (sync, async).
*
* @api
*
* @pre              The module has to be initialized.
*
*
* @implements       Eep_MainFunction_Activity
*
* @note             This function have to be called ciclically by the Basic Software Module;
*                   it will do nothing if there aren't pending job.
*/
/*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( void, EEP_CODE ) Eep_MainFunction( void )
{
    uint16 writeSize = 0;

	if (eep_current_job.job == EEP_JOB_WRITE)
	{
	    if (Eepm95640_IsInWriting())
	    {
	        // pending
	    }
	    else
	    {
	        if (eep_current_job.length > 0)
	        {
	            Eepm95640_Write(eep_current_job.offset, eep_current_job.buffer, eep_current_job.length, &writeSize);

	            if (0 < writeSize)
	            {
                    eep_current_job.offset += writeSize;
                    eep_current_job.length -= writeSize;
                    eep_current_job.buffer += writeSize;
	            }
	            else
	            {
	                eep_current_job.job = EEP_JOB_NONE;
	                eep_current_job.result = MEMIF_JOB_FAILED;
	            }
	        }
	        else
	        {
	            eep_current_job.job = EEP_JOB_NONE;
	            eep_current_job.result = MEMIF_JOB_OK;
	        }
	    }
	}
}

/**
* @brief            Cancel an ongoing eeprom read, write, erase or compare job.
* @details          Abort a running job synchronously so that directly after returning
*                   from this function a new job can be started.
*
* @api
*
* @pre              The module must be initialized.
* @post             @p Eep_Cancel changes module status and @p Eep_eJobResult
*                   internal variable.
*
* @implements       Eep_Cancel_Activity
*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( void, EEP_CODE ) Eep_Cancel( void )
{

}

/**
* @brief            Returns the result of the last job.
* @details          Returns synchronously the result of the last job.
*
* @return           MemIf_JobResultType
* @retval           MEMIF_JOB_OK              Successfully completed job.
* @retval           MEMIF_JOB_FAILED          Not successfully completed job.
* @retval           MEMIF_JOB_PENDING         Still pending job (not yet completed).
* @retval           MEMIF_JOB_CANCELED        Job has been canceled.
* @retval           MEMIF_BLOCK_INCONSISTENT  Inconsistent block requested, it may
*                                             contains corrupted data.
* @retval           MEMIF_BLOCK_INVALID       Invalid block requested.
*
* @api
*
* @implements       Eep_GetJobResult_Activity
*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( MemIf_JobResultType, EEP_CODE ) Eep_GetJobResult( void )
{
    if (eep_current_job.job != EEP_JOB_NONE)
    {
        return MEMIF_JOB_PENDING;
    }
    else
    {
        return eep_current_job.result;
    }
}

/**
* @brief           Sets the EEP module's operation mode to the given Mode.
* @details         Every given mode determinates maximum bytes for read-write
 *                 operations. Every mode has a set of pre-configured values.
*
* @param[in]        Mode        MEMIF_MODE_FAST or MEMIF_MODE_SLOW.
*
* @api
*
* @pre            The module has to be initialized and not busy.
* @post           @p Eep_SetMode changes internal variables @p Eep_u32MaxRead and
*                 @p Eep_u32MaxWrite.
*
* @implements       Eep_SetMode_Activity
*
* @violates @ref eep_c_REF_11 All declarations and definitions
* of objects or functions at file scope shall have internal linkage unless external linkage required
*/
FUNC( void, EEP_CODE ) Eep_SetMode
(
    VAR( MemIf_ModeType, AUTOMATIC ) eMode
)
{
    Eep_Mode = eMode;
}
