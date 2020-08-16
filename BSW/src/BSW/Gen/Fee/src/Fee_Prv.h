

#ifndef FEE_PRV_H
#define FEE_PRV_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

/*
 * Collect all sub headers of the Fee as described in the coding guidelines.
*/

#include "Fee_Prv_Config.h"
#include "Fee_Prv_Lib.h"
#include "Fee_Prv_Order.h"

#include "Fee_Prv_Medium.h"

#include "Fee_Prv_FsIf.h"

#include "Fee_Prv_Dbg.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

/*
 * CPTBLTY: Provide the define FEE_FLAG_SEC_LEVEL_MSK since it is used by BC: MemApl
 *          The define must have the same value as FEE_PRV_CONFIG_DOUBLESTORAGE_BITS
 *          Since FEE_PRV_CONFIG_DOUBLESTORAGE_BITS is private to the config unit,
 *          it must be defined again with the same value.
 */
#define FEE_FLAG_SEC_LEVEL_MSK  (0x0001)

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

typedef enum
{
    FEE_PRV_DRIVERSTATE_UNINIT_E            = 0,    /* MEMIF_UNINIT                     */
    FEE_PRV_DRIVERSTATE_INIT_E              = 1,    /* MEMIF_BUSY_INTERNAL              */
    FEE_PRV_DRIVERSTATE_BACKGROUND_E        = 2,    /* MEMIF_BUSY_INTERNAL              */
    FEE_PRV_DRIVERSTATE_IDLE_E              = 3,    /* MEMIF_IDLE                       */
    FEE_PRV_DRIVERSTATE_READ_E              = 4,    /* MEMIF_BUSY/MEMIF_BUSY_INTERNAL   */
    FEE_PRV_DRIVERSTATE_WRITE_E             = 5,    /* MEMIF_BUSY/MEMIF_BUSY_INTERNAL   */
    FEE_PRV_DRIVERSTATE_INVALIDATEBLOCK_E   = 6,    /* MEMIF_BUSY/MEMIF_BUSY_INTERNAL   */
    FEE_PRV_DRIVERSTATE_BLOCKMAINTENANCE_E  = 7     /* MEMIF_BUSY/MEMIF_BUSY_INTERNAL   */
} Fee_Prv_DriverState_ten;

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/* Central variables */
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_Prv_DriverState_ten  Fee_Prv_DriverState_en;
extern MemIf_ModeType           Fee_Prv_DriverMode_en;
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

/*
 * We cannot use the AUTOSAR MemIf_StatusType for the driver state because the Fee supports > 1 order slot.
 * Because of this reason calculating the AUTOSAR MemIf_StatusType is a little more complex.
 * It is done in Fee_GetStatus() (see in the "Order" unit)
 */

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#else
#include "rba_FeeFs1_Prv.h"/* Include the header file for backward compatibility. */
#endif

/* FEE_PRV_H */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
 **********************************************************************************************************************
 * End of header file: $Name______:$
 **********************************************************************************************************************
</BASDKey>*/
