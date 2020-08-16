

#ifndef EA_CFG_H
#define EA_CFG_H

#include "MemIf_Types.h"
#include "Eep.h"

#define EA_PRESENT   1

/* *********************************************************************************************************************
 * SWS Item:        EA039_Conf
 * Container Name:  EaGeneral
 * Description:     Container for general parameters. These parameters are not specific to a block.
 ******************************************************************************************************************** */
#define EA_VENDOR_ID                   6     
#define EA_MODULE_ID                   40     /* Module ID of Ea */
#define EA_INSTANCE_ID                 0   /* Instance ID Ea */

/* Ea Software Version in BASD is AR40.10.1.0
 * -> version has to be modified for each delivery in function GetVersionInformation */
#define EA_SW_MAJOR_VERSION            10
#define EA_SW_MINOR_VERSION            1
#define EA_SW_PATCH_VERSION            0

/* Ea is compatible with Autosar 4.2Rev2 */
#define EA_AR_RELEASE_MAJOR_VERSION    4
#define EA_AR_RELEASE_MINOR_VERSION    2
#define EA_AR_RELEASE_REVISION_VERSION 2

/* *********************************************************************************************************************
 * SWS Item:        EA120_Conf
 * Name:            EaDevErrorDetect
 * Description:     Pre-processor switch to enable and disable development error detection.
 *                  true: Development error detection enabled.
 *                  false: Development error detection disabled.
 * Multiplicity:    1
 * Type:            EcucBooleanParamDef
 ********************************* ********************************************************************************** */
#define EA_DEV_ERROR_DETECT        TRUE

/* *********************************************************************************************************************
 * SWS Item:        EA118_Conf
 * Name:            EaIndex
 * Description:     Specifies the InstanceId of this module instance. If only one instance is present it shall have
 *                  the Id 0.
 * Multiplicity:    1
 * Type:            EcucIntegerParamDef
 * Range:           0 .. 254
  ******************************************************************************************************************* */
#define EA_EAINDEX      0

/* *********************************************************************************************************************
 * SWS Item:        EA121_Conf
 * Name:            EaNvmJobEndNotification
 * Description:     Mapped to the job end notification routine provided by the upper layer module
 *                  (NvM_JobEndNotification).
 * Multiplicity:    0 .. 1
 * Type:            EcucFunctionNameDef
  ******************************************************************************************************************* */
#define EA_NVM_JOB_END_NOTIFICATION    NULL_PTR

/* *********************************************************************************************************************
 * SWS Item:        EA122_Conf
 * Name:            EaNvmJobErrorNotification
 * Description:     Mapped to the job error notification routine provided by the upper layer module
 *                  (NvM_JobErrorNotification).
 * Multiplicity:    0 .. 1
 * Type:            EcucFunctionNameDef
  ******************************************************************************************************************* */
#define EA_NVM_JOB_ERROR_NOTIFICATION  NULL_PTR

/* *********************************************************************************************************************
 * SWS Item:        EA123_Conf
 * Name:            EaPollingMode
 * Description:     Pre-processor switch to enable and disable the polling mode for this module.
 *                  true:  Polling mode enabled, callback functions (provided to FLS module) disabled.
 *                  false: Polling mode disabled, callback functions (provided to FLS module) enabled.
 * Multiplicity:    1
 * Type:            EcucBooleanParamDef
  ******************************************************************************************************************* */
#define EA_POLLING_MODE  TRUE

/* *********************************************************************************************************************
 * SWS Item:        EA001_Conf
 * Name:            EaSetModeSupported
 * Description:     Compiler switch to enable/disable the 'SetMode' functionality of the EA module.
 *                  TRUE: SetMode functionality supported / code present,
 *                  FALSE: SetMode functionality not supported / code not present. Note: This configuration setting has
 *                  to be consistent with that of all underlying flash device drivers (configuration parameter
 *                  FlsSetModeApi).
 * Multiplicity:    1
 * Type:            EcucBooleanParamDef
  ******************************************************************************************************************* */
#define EA_SET_MODE_SUPPORTED  FALSE

/* *********************************************************************************************************************
 * SWS Item:        EA124_Conf
 * Name:            EaVersionInfoApi
 * Description:     Pre-processor switch to enable / disable the API to read out the modules version information.
 *                  true:  Version info API enabled.
 *                  false: Version info API disabled.
 * Multiplicity:    1
 * Type:            EcucBooleanParamDef
  ******************************************************************************************************************* */
#define EA_VERSION_INFO_API    TRUE

/* *********************************************************************************************************************
 * SWS Item:        EA125_Conf
 * Name:            EaVirtualPageSize
 * Description:     The size in bytes to which logical blocks shall be aligned.
 * Multiplicity:    1
 * Type:            EcucIntegerParamDef
 * Range:           0 .. 65535
  ******************************************************************************************************************* */
#define EA_VIRTUAL_PAGE_SIZE   32

/* *********************************************************************************************************************
 * SWS Item:        RB add-on
 * Name:            EaRbAddonsCCAS
 * Description:     Pre-processor switch to enable and disable addons for CCAS which are realized is an adapter:
 *                  - rba_EaAddOnAS_EnterStopMode
 *                  - rba_EaAddOnAS_WriteAdr
 *                  - rba_EaAddOnAS_ReadAdr
 * Multiplicity:    0
 * Type:            EcucBooleanParamDef
 ******************************************************************************************************************** */
#define EA_RB_ADDONS_CCAS   TRUE

/* *********************************************************************************************************************
 * SWS Item:        Conf
 * Name:            EaRbActSurvivalEval
 * Description:     Pre-processor switch to enable or disable an additional block specific reorganization for unknown
 *                  blocks with an active survival setting ("EaRbSurvival") in the medium.
 *                  true:  Feature enabled  ("block specific afterburner" on for blocks with active survival setting).
 *                  false: Feature disabled ("block specific afterburner" off for blocks with active survival setting).
 *                  Hint:  If activated, this block will be overtaken independent from the "EaRbActUnknownBlockReorg"
 *                         setting ("general afterburner"). To delete all unknown survival blocks, it should be
 *                         deactivated.
 * Multiplicity:    0
 * Type:            EcucBooleanParamDef
 ******************************************************************************************************************** */
#define EA_RB_ACT_SURVIVAL_EVAL     FALSE

/* *********************************************************************************************************************
 * SWS Item:        Conf
 * Name:            EaRbActUnknownBlockMig
 * Description:     Pre-processor switch to enable or disable an additional reorganization for any unknown block in
 *                  the medium.
 *                  true:  Feature enabled  ("general afterburner" on for all unknown blocks).
 *                  false: Feature disabled ("general afterburner" off for all unknown blocks).
 *                  Hints: If activated, all unknown blocks will be overtaken independent from the setting "RbSurvival"
 *                  ("block specific afterburner").
 *                         Only the CB (Customer Block) is allowed to enable this feature, because this is affecting the
 *                         thresholds of Migration. It must be deactivated
 *                         for the ASW!
 * Multiplicity:    0
 * Type:            EcucBooleanParamDef
 ******************************************************************************************************************** */
#define EA_RB_ACT_UNKNOWN_BLOCK_MIG     FALSE

/* *********************************************************************************************************************
 * SWS Item:        Conf
 * Name:            EaRbMigEraseBufferSize
 * Description:     This parameter defines the size of an internal array (of uint32) used during migration.
 *                  The array holds the address of the blocks to be Erased in Eeprom. Inside Ea Init during migration
 *                  unnecessary blocks were erased. each block Erase is consuming 4ms, this was increasing the
 *                  Ea Init timing. In order to reduce the Ea Init time Erasing is moved to cyclic Migration.
 *                  During Ea Init if the array size is not enough to hold the address then the remaining blocks
 *                  willbe Erased in Ea Init function itself.
 *                  Hints:   For optimal performance the size of this array must be equal to or more than the number
 *                           of blocks that are removed from old layout to new layout.
 * Multiplicity:    0
 * Type:            EcucIntegerParamDef
 * Range:           1 .. 65535
 ******************************************************************************************************************** */
#define EA_RB_MIG_ERASE_BUFFER_SIZE    256


/* ******************************************************************************************************************
   ******************************************** EaPublishedInformation *********************************************
   ****************************************************************************************************************** */

/* EA126_Conf: EaBlockOverhead {EA_BLOCK_OVERHEAD}
 * Management overhead per logical block in bytes.
 * Note:
 * If the management overhead depends on the block size or block location a formula has to be provided that allows the
 * configurator to calculate the management overhead correctly.
 * Type:    EcucIntegerParamDef
 * Range:   0 .. 65535 */
#define EA_BLOCK_OVERHEAD          14

/* EA070_Conf: EaMaximumBlockingTime {EA_MAXIMUM_BLOCKING_TIME}
 * The maximum time the EA module's API routines shall be blocked (delayed) by internal operations.
 * Note:
 * Internal operations in that case means operations that are not explicitly invoked from the upper layer module but
 * need to be handled for proper operation of this module or the underlying memory driver.
 * Type:    EcucFloatParamDef
 * Range:   0.0 .. Inf */
#define EA_MAXIMUM_BLOCKING_TIME   5

/* EA127_Conf: EaPageOverhead {EA_PAGE_OVERHEAD}
 * Management overhead per page in bytes.
 * Note:
 * If the management overhead depends on the block size or block location a formula has to be provided that allows the
 * configurator to calculate the management overhead correctly.
 * Type:    EcucIntegerParamDef
 * Range:   0 .. 65535 */
#define EA_PAGE_OVERHEAD           0



/* ******************************************************************************************************************
   *************************************** Ea internally used configuration ****************************************
   ****************************************************************************************************************** */
/* number of EaBlocks */
#define EA_NUM_BLOCKS                     (16u)
/* reserved persistent ID */
#define EA_RESERVED_BLK_ID                (0xFFFFu)
/* number of survival EaBlocks */
#define EA_NUM_SURVIVAL_BLOCKS            (0u)
/* the biggest block length in the layout */
#define EA_BLK_SIZE_MAX                   (2064u)
/* Size of Ea data receive buffer, if EA_BLK_SIZE_MAX < 128, then equal to EA_BLK_SIZE_MAX */
#define EA_DATA_BUFFER_SIZE               (128u)
/* marker for migration */
#define EA_MIGRATION_MARKER               (0x8EEF7576uL)

/* ******************************************************************************************************************
   ******************************************* generate EEPROM configuration *****************************************
   ****************************************************************************************************************** */
#define EA_EEP_START_OFFSET               (64u)   /* Offset for Layout start */
#define EA_ERASE_PATTERN                  (0u)      /* Erase value */

/* ******************************************************************************************************************
   ********************************** external declarations, provided to upper layer (NvM) ***************************
   ****************************************************************************************************************** */
/*Ea-BlkIdx-Handle                                              Ea-BlkIdx */
#define EaConf_EaBlockConfiguration_NVDataBlock1                    0          
#define EaConf_EaBlockConfiguration_DiagDataBlock1                  1          
#define EaConf_EaBlockConfiguration_EOLDataBlock                    2          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory4  3          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory5  4          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory6  5          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory7  6          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory8  7          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_GenericNvData  8          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory9  9          
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory1  10         
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_AllEventsStatusByte  11         
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory0  12         
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory3  13         
#define EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory2  14         
#define EaConf_EaBlockConfiguration_ECUM_CFG_NVM_BLOCK              15         



#endif /* EA_CFG_H */

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

