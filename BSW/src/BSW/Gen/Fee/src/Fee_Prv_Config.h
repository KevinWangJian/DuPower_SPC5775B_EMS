

#ifndef FEE_PRV_CONFIG_H
#define FEE_PRV_CONFIG_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 * The Config unit provides easy access to the configuration of the Fee.
 * With the help of this unit the configuration can be stored in a packed way.
 * Then this unit can read the information can provide it in an easy-to-handle way to the Fee.
*/

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

typedef enum
{
    FEE_PRV_REQUESTER_NVM_E         = 0,
    FEE_PRV_REQUESTER_ADAPTER_E     = 1,
    FEE_PRV_REQUESTER_DEBUG_E       = 2,
    FEE_PRV_REQUESTER_MAX_E         = 3
} Fee_Prv_ConfigRequester_ten;

typedef void(*Fee_Prv_ConfigNotification_tpfn)(void);

typedef struct
{
    uint16  BlockPersistentId_u16;
    uint16  Flags_u16;
    uint16  Length_u16;
    Fee_Prv_ConfigNotification_tpfn const JobEndNotification_pfn;
    Fee_Prv_ConfigNotification_tpfn const JobErrorNotification_pfn;
} Fee_BlockPropertiesType_tst;

typedef struct
{
    uint32  Fee_PhysStartAddress_u32;       /* Physical sector: start address */
    uint32  Fee_PhysEndAddress_u32;         /* physical sector: end address */
    uint32  Fee_LogStartAddress_u32;        /* logical sector: start address */
    uint32  Fee_LogEndAddress_u32;          /* logical sector: end address */
} Fee_FlashProp_tst;

typedef struct
{
    void(* Fee_ResetUsedSectors_pfn)(void);     /* Function for resetting the amount of used sectors */
}Fee_LinkedFunctions_tst;

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/*
 * Conditionally put Fee_BlockProperties_st into RAM.
 * This is a workaround for GS-TC where it is required to write blocks with a changing length.
 * For the actual release there shall be a proper API to do this.
 */
#ifdef FEE_PRV_USE_ROM_TABLE

#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
extern const Fee_BlockPropertiesType_tst  Fee_BlockProperties_st[FEE_NUM_BLOCKS];
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#else

#define FEE_START_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"
extern       Fee_BlockPropertiesType_tst  Fee_BlockProperties_st[FEE_NUM_BLOCKS];
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "Fee_MemMap.h"

#endif

#define FEE_START_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"
extern const Fee_FlashProp_tst            Fee_FlashProp_st[FEE_NUM_FLASH_BANKS_AVAILABLE];
extern const Fee_LinkedFunctions_tst      Fee_LinkedFunctions_cst;
#define FEE_STOP_SEC_CONST_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_CONST_32
#include "Fee_MemMap.h"
extern uint32 const Fee_Prv_ConfigMaxEffort_cu32;
#define FEE_STOP_SEC_CONST_32
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern uint16                           Fee_Prv_ConfigGetBlockLengthByBlockNr       (uint16 blocknumber_u16 );
extern uint16                           Fee_Prv_ConfigGetBlockLengthByPersistentId  (uint16 persistentId_u16);
extern uint16                           Fee_Prv_ConfigGetPersistentId               (uint16 blocknumber_u16);
extern boolean                          Fee_Prv_ConfigIsMigrationActive             (uint16 persistentId_u16);
extern boolean                          Fee_Prv_ConfigIsBlockLengthVariable         (uint16 blocknumber_u16);
extern boolean                          Fee_Prv_ConfigIsKnown                       (uint16 persistentId_u16);
extern boolean                          Fee_Prv_ConfigIsRobust                      (uint16 blocknumber_u16);
extern boolean                          Fee_Prv_ConfigIsDoubleStorage               (uint16 blocknumber_u16);
extern boolean                          Fee_Prv_ConfigIsSurvival                    (uint16 blocknumber_u16);
extern Fee_Prv_ConfigRequester_ten      Fee_Prv_ConfigGetRequester                  (uint16 blocknumber_u16);
extern Fee_Prv_ConfigNotification_tpfn  Fee_Prv_ConfigGetJobEndNotification         (uint16 blocknumber_u16);
extern Fee_Prv_ConfigNotification_tpfn  Fee_Prv_ConfigGetJobErrorNotification       (uint16 blocknumber_u16);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Inlines
 **********************************************************************************************************************
*/

/**
 * \brief   Shall unknown blocks be reorganized or not by default (CB-Mode yes or no)
 *
 * \retval  FALSE   ASW-Mode:   Do throw away unknown blocks during reorganization (if not survival)
 * \retval  TRUE    CB-Mode:    Do not throw away unknown blocks during reorganization
*/

LOCAL_INLINE boolean Fee_Prv_ConfigIsReorgUnknown(void)
{
    return(FEE_RB_ACT_UNKNOWN_BLOCK_REORG);
}

/**
 * \brief   Does the flash preprogram all cells before erasing (yes or no)
 *
 * \retval  FALSE   No preprogramming before erase
 * \retval  TRUE    Preprogramming before erase
*/
LOCAL_INLINE boolean Fee_Prv_ConfigIsPreprogramming(void)
{
    return(FEE_PRV_CFG_ISPREPROGRAMMING);
}

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_CONFIG_H */
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
