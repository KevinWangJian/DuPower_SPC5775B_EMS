

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "Fee.h"
#include "Fee_Cfg.h"
#include "Fee_Prv.h"

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

#define FEE_PRV_CONFIG_DOUBLESTORAGE_BITS           (0x0001u)
#define FEE_PRV_CONFIG_FIRST_INIT_MIGRATION_BITS    (0x0002u)
#define FEE_PRV_CONFIG_VAR_BLOCK_LENGTH_BITS        (0x0004u)
#define FEE_PRV_CONFIG_SURVIVAL_BITS                (0x0010u)
#define FEE_PRV_CONFIG_ROBUSTNESS_BITS              (0x0020u)
#define FEE_PRV_CONFIG_REQUESTER_BITS               (0x0300u)

#define FEE_PRV_CONFIG_REQUESTER_POS    (8u)

/*
 **********************************************************************************************************************
 * Static declarations
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
static uint16 Fee_Prv_ConfigFindIndex(uint16 persistentId_u16);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Implementation
 **********************************************************************************************************************
*/

/*
 * In the end this shall be a constant "variable" or a define.
 * To better find out the maximal limit that is possible it is currently located in RAM.
 * Here we can change it with the debugger which is important for testing.
 *
 */

#define FEE_START_SEC_CONST_32
#include "Fee_MemMap.h"
uint32 const Fee_Prv_ConfigMaxEffort_cu32 = 1024u;
#define FEE_STOP_SEC_CONST_32
#include "Fee_MemMap.h"

/**
 * \brief   Find the index in the block properties struct by persistent ID.
 *
 * \param   persistentId_u16    The persistent ID that shall be checked
 *
 * \return  The index of the corresponding block in the block properties table - 0xFFFF if not known.
*/
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
static uint16 Fee_Prv_ConfigFindIndex(uint16 persistentId_u16)
{
    register uint16_least   a_u16       = 0;
    register uint16_least   b_u16       = FEE_NUM_BLOCKS;
    register uint16_least   check_u16   = 0;
    uint16                  result_u16  = 0xFFFFu;

    /*
     * The Fee_BlockProperties_st struct is stored ascending by persistent ID.
     * This function uses that fact and does a binary search.
     */
    while(a_u16 != b_u16)
    {
        check_u16 = a_u16 + ((b_u16 - a_u16) / 2u);
        if(Fee_BlockProperties_st[check_u16].BlockPersistentId_u16 < persistentId_u16)
        {
            if(check_u16 == a_u16)
            {
                /*
                 * This can only happen if a_u16 + 1 = b_u16.
                 * Either b_u16 was once checked and was not index of the searched persistent ID
                 * or b_u16 is still = FEE_NUM_BLOCKS (which is 1 bigger than the last valid index of Fee_BlockProperties_st)
                 * and the searched persistent ID is bigger than the biggest configured persistent ID.
                 * So if this branch is reached the persistent ID is not known.
                 */
                b_u16 = a_u16;
            }
            else
            {
                a_u16 = check_u16;
            }
        }
        else if(Fee_BlockProperties_st[check_u16].BlockPersistentId_u16 > persistentId_u16)
        {
            b_u16 = check_u16;
        }
        else
        {
            b_u16       = a_u16;
            result_u16  = (uint16)check_u16;
        }
    }

    return(result_u16);
}

/**
 * \brief   Get the length of a block specified by its block number.
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \return  The length of the specified block
*/
uint16 Fee_Prv_ConfigGetBlockLengthByBlockNr(uint16 blocknumber_u16)
{
    return(Fee_BlockProperties_st[blocknumber_u16].Length_u16);
}

/**
 * \brief   Get the length of a block specified by its persistent ID.
 *
 * \param   persistentId_u16    Persistent ID of this block
 *
 * \return  The length of the specified block
*/
uint16 Fee_Prv_ConfigGetBlockLengthByPersistentId(uint16 persistentId_u16)
{
    uint16 result_u16   = 0u;
    uint16 index_u16    = Fee_Prv_ConfigFindIndex(persistentId_u16);

    if(0xFFFFu != index_u16)
    {
        result_u16 = Fee_BlockProperties_st[index_u16].Length_u16;
    }

    return(result_u16);
}

/**
 * \brief   Get the persistent ID of a specified block.
 *
 * \param   blocknumber_u16 Block number as defined in Fee_Cfg.h
 *
 * \return  Persistent ID of the specified block
*/
uint16 Fee_Prv_ConfigGetPersistentId(uint16 blocknumber_u16)
{
    return(Fee_BlockProperties_st[blocknumber_u16].BlockPersistentId_u16);
}

/**
 * \brief   Check whether migration feature is active for a block.
 *
 * \param   persistentId_u16 Persistent ID of the specified block
 *
 * \return  TRUE: migration is active, FALSE: migration is not active
*/
boolean Fee_Prv_ConfigIsMigrationActive(uint16 persistentId_u16)
{
   boolean result_b = FALSE;

   uint16 blocknumber_u16 = Fee_Prv_ConfigFindIndex(persistentId_u16);

   if ( (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 &
           FEE_PRV_CONFIG_FIRST_INIT_MIGRATION_BITS) == FEE_PRV_CONFIG_FIRST_INIT_MIGRATION_BITS
      )

   {
       result_b = TRUE;
   }

   return(result_b);
}

/**
 * \brief   Check whether the block length is variable and calculated on runtime.
 *
 * \param  blocknumber_u16 Block number as defined in Fee_Cfg.h
 *
 * \return  TRUE: block length is variable, FALSE: block length is not variable
*/
boolean Fee_Prv_ConfigIsBlockLengthVariable(uint16 blocknumber_u16)
{
   boolean result_b = FALSE;

   if ( (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 &
           FEE_PRV_CONFIG_VAR_BLOCK_LENGTH_BITS) == FEE_PRV_CONFIG_VAR_BLOCK_LENGTH_BITS
      )
   {
       result_b = TRUE;
   }

   return(result_b);
}

/**
 * \brief   Check whether a block with the specified persistent ID is known by configuration.
 *
 * \param persistentId_u16  Peristent ID which shall be checked
 *
 * \retval  TRUE    There exists a block in the configuration with the specified persistent ID
 * \retval  FALSE   There does not exist a block in the configuration with the specified persistent ID
*/
boolean Fee_Prv_ConfigIsKnown(uint16 persistentId_u16)
{
    boolean result_b = FALSE;

    if(0xFFFFu != Fee_Prv_ConfigFindIndex(persistentId_u16))
    {
        result_b = TRUE;
    }

    return(result_b);
}

/**
 * \brief   Does a specified block support writing from an unstable buffer? (For example EnvRam)
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  TRUE    The block does support writing from an unstable buffer
 *                  This means if the flash content is not equal to the RAM content after writing this is not an error
 * \retval  FALSE   The block does not support writing from an unstable buffer
*/
boolean Fee_Prv_ConfigIsRobust(uint16 blocknumber_u16)
{
    boolean result_b = FALSE;

    if(0u != (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 & FEE_PRV_CONFIG_ROBUSTNESS_BITS))
    {
        result_b = TRUE;
    }

    return(result_b);
}

/**
 * \brief   Is a specified block stored twice in write or invalidate order?
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  TRUE    The block is stored twice when writing or invalidating
 * \retval  FALSE   The block is single stored when writing or invalidating
*/
boolean Fee_Prv_ConfigIsDoubleStorage(uint16 blocknumber_u16)
{
    boolean result_b = FALSE;

    if(0u != (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 & FEE_PRV_CONFIG_DOUBLESTORAGE_BITS))
    {
        result_b = TRUE;
    }

    return(result_b);
}

/**
 * \brief   Shall the block be ignored during flash reorganization even when the software does not know it by configuration?
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  TRUE    The block shall not be ignored during flash reorganization even when the software does not know it by configuration
 * \retval  FALSE   The block shall be ignored during flash reorganization if it is not known by configuration
*/
boolean Fee_Prv_ConfigIsSurvival(uint16 blocknumber_u16)
{
    boolean result_b = FALSE;

    if(0u != (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 & FEE_PRV_CONFIG_SURVIVAL_BITS))
    {
        result_b = TRUE;
    }

    return(result_b);
}

/**
 * \brief   Get the requester of that block. Can be either NvM or adapter.
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \retval  FEE_PRV_REQUESTER_NVM_E     Block is handled by the NvM
 * \retval  FEE_PRV_REQUESTER_ADAPTER_E Block is handled by the adapter
*/
Fee_Prv_ConfigRequester_ten Fee_Prv_ConfigGetRequester(uint16 blocknumber_u16)
{
    Fee_Prv_ConfigRequester_ten result_en;
    uint32 requesterId_u32 = (Fee_BlockProperties_st[blocknumber_u16].Flags_u16 & FEE_PRV_CONFIG_REQUESTER_BITS) >> FEE_PRV_CONFIG_REQUESTER_POS;
    if(1u == requesterId_u32)
    {
        result_en = FEE_PRV_REQUESTER_NVM_E;
    }
    else if(2u == requesterId_u32)
    {
        result_en = FEE_PRV_REQUESTER_ADAPTER_E;
    }
    else
    {
        result_en = FEE_PRV_REQUESTER_DEBUG_E;
    }
    return(result_en);
}

/**
 * \brief   Get the job configured job end notification for a specified block.
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \return Function pointer that is called after finishing a job successfully.
*/
Fee_Prv_ConfigNotification_tpfn Fee_Prv_ConfigGetJobEndNotification(uint16 blocknumber_u16)
{
   return(Fee_BlockProperties_st[blocknumber_u16].JobEndNotification_pfn);
}

/**
 * \brief   Get the job configured job error notification for a specified block.
 *
 * \param   blocknumber_u16     Block number as defined in Fee_Cfg.h - This is not the persistent ID!
 *
 * \return Function pointer that is called after finishing a job with errors.
*/
Fee_Prv_ConfigNotification_tpfn Fee_Prv_ConfigGetJobErrorNotification(uint16 blocknumber_u16)
{
    return(Fee_BlockProperties_st[blocknumber_u16].JobErrorNotification_pfn);
}

#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
 **********************************************************************************************************************
 * $History___:$
 **********************************************************************************************************************
</BASDKey>*/
