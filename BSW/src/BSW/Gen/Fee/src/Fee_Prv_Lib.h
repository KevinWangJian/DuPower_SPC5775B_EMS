

#ifndef FEE_PRV_LIB_H
#define FEE_PRV_LIB_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 * The lib unit contains various helper functions that shall only be implemented once.
 * It also contains functions to limit the duration of a main function call.
 * See more about that topic below at the functions used for that.
 */

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

/*
 * Set the state of a state machine struct to another state.
 * Then set the entry_b variable to indicate the state is newly entered.
 * Since C neither supports templates nor inheritance this is the only way to do it type safe.
 */
#define FEE_PRV_LIBTRANS(FSM_STRUCT, FSM_STATE) \
{                                               \
    (FSM_STRUCT).state_en   = (FSM_STATE);      \
    (FSM_STRUCT).entry_b    = (TRUE);           \
}

#define FEE_PRV_LIBSC(FSM_STATE) FEE_PRV_LIBTRANS((*fsm_pst), (FSM_STATE))

#define FEE_PRV_LIBENTRY (Fee_Prv_LibEnter(&fsm_pst->entry_b))

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

/* The following operations are considered when limiting the duration of a main function call */
typedef enum
{
    FEE_PRV_LIMIT_CRCINRAM_E    = 0,    /* CRC calculation in RAM                                           */
    FEE_PRV_LIMIT_CRCINFLS_E    = 1,    /* CRC calculation in flash                                         */
    FEE_PRV_LIMIT_HDR_E         = 2,    /* Handling one FAT entry - no matter what "handling" exactly means */
    FEE_PRV_LIMIT_CACHEREORG_E  = 3,    /* Reorganizing the cache is expensive                              */
    FEE_PRV_LIMIT_MAX_E         = 4     /* Maximum enum value used for defining an array                    */
} Fee_Prv_LibEffortLimit_ten;

/* Struct to measure the amount of already executed effort. */
typedef struct
{
    uint32  effortCtr_u32;  /* Effort that can still be spent - if 0 the main function shall not continue   */
    boolean enabled_b;      /* Effort limitation enabled, TRUE = yes, FALSE = no                            */
} Fee_Prv_LibEffortMeasure_tst;

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

#define FEE_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"
extern Fee_Prv_LibEffortMeasure_tst         Fee_Prv_LibEffortMeasure_st;
#define FEE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fee_MemMap.h"

#define FEE_START_SEC_CONST_8
#include "Fee_MemMap.h"
extern uint8                        const   Fee_Prv_LibEffortWeights_au8[FEE_PRV_LIMIT_MAX_E];
#define FEE_STOP_SEC_CONST_8
#include "Fee_MemMap.h"

/*
 **********************************************************************************************************************
 * Inlines
 **********************************************************************************************************************
*/

/**
 * \brief   Check whether a state of a state machine is entered the 1. time or the >1. time
 *
 * \param   entry_pb    Pointer to the entry_b variable of the state machine
*/
LOCAL_INLINE boolean Fee_Prv_LibEnter(boolean * entry_pb)
{
    boolean result_b = FALSE;

    /* If not already entered then set the entry_b to FALSE and return TRUE (= state is entered) */
    if(*entry_pb == TRUE)
    {
        result_b    = TRUE;
        *entry_pb   = FALSE;
    }

    return(result_b);
}

/**
 * \brief   Simply limiter.
 *
 * \param   in_u32  Value
 * \param   max_u32 Limit of the value, if smaller then the value max_u32 is returned
*/
LOCAL_INLINE uint32 Fee_Prv_LibLimit(uint32 in_u32, uint32 max_u32)
{
    uint32 result_u32 = in_u32;
    if(result_u32 > max_u32)
    {
        result_u32 = max_u32;
    }
    return(result_u32);
}

/**
 * \brief   Simple maximum chooser.
 *
 * \param   a_u32   First value
 * \param   b_u32   Second value
 *
 * \return  The biggest of both values
*/
LOCAL_INLINE uint32 Fee_Prv_LibMax(uint32 a_u32, uint32 b_u32)
{
    uint32 result_u32 = a_u32;
    if(a_u32 < b_u32)
    {
        result_u32 = b_u32;
    }
    return(result_u32);
}

/**
 * \brief   Simple minimum chooser.
 *
 * \param   a_u32   First value
 * \param   b_u32   Second value
 *
 * \return  The smallest of both values
*/
LOCAL_INLINE uint32 Fee_Prv_LibMin(uint32 a_u32, uint32 b_u32)
{
    uint32 result_u32 = a_u32;
    if(a_u32 > b_u32)
    {
        result_u32 = b_u32;
    }
    return(result_u32);
}

/**
 * \brief   Convert uint32 to big endian format.
 *
 * \param   in_u32      uint32 that shall be converted to big endian
 * \param   out_pu8     Pointer to result buffer
*/
LOCAL_INLINE void Fee_Prv_LibU32ToBigEndian(uint32 in_u32, uint8 * out_pu8)
{
    out_pu8[0] = (uint8)(in_u32 >> 24u);
    out_pu8[1] = (uint8)(in_u32 >> 16u);
    out_pu8[2] = (uint8)(in_u32 >> 8u );
    out_pu8[3] = (uint8)(in_u32 >> 0u );
}

/**
 * \brief   Convert uint16 to big endian format.
 *
 * \param   in_u16      uint16 that shall be converted to big endian
 * \param   out_pu8     Pointer to result buffer
*/
LOCAL_INLINE void Fee_Prv_LibU16ToBigEndian(uint16 in_u16, uint8 * out_pu8)
{
    out_pu8[0] = (uint8)(in_u16 >> 8u);
    out_pu8[1] = (uint8)(in_u16 >> 0u);
}

/**
 * \brief   Create an uint32 from a big endian buffer.
 *
 * \param   in_pcu8     Big endian buffer that shall be converted to a uint32
 * \param   out_pu32    Pointer to result buffer
*/
LOCAL_INLINE void Fee_Prv_LibU32FromBigEndian(uint8 const * in_pcu8, uint32 * out_pu32)
{
    *out_pu32  = (((uint32)(in_pcu8[0])) << 24u);
    *out_pu32 |= (((uint32)(in_pcu8[1])) << 16u);
    *out_pu32 |= (((uint32)(in_pcu8[2])) <<  8u);
    *out_pu32 |= (((uint32)(in_pcu8[3])) <<  0u);
}

/**
 * \brief   Create an uint16 from a big endian buffer.
 *
 * \param   in_pcu8     Big endian buffer that shall be converted to a uint16
 * \param   out_pu16    Pointer to result buffer
*/
LOCAL_INLINE void Fee_Prv_LibU16FromBigEndian(uint8 const * in_pcu8, uint16 * out_pu16)
{
    *out_pu16  = (uint16)(((uint32)in_pcu8[0]) << 8u);
    *out_pu16 |= (uint16)(((uint32)in_pcu8[1]) << 0u);
}

/**
 * \brief   Round an address up to the next page border.
 *
 * \param   adr_u32     Address to round up
 *
 * \return  Address rounded up to the next page border
 *
 * \attention   Whenever a flash must be supported which does NOT have 2^n page size this function must be changed!
*/
LOCAL_INLINE uint32 Fee_Prv_LibAdrCeil(uint32 adr_u32)
{
    /*
     * Example with adr 0x12345 and page size 8.
     *
     *      0001 0010 0011 0100 0101
     *  &   0000 0000 0000 0000 0111 (VIRTUAL_PAGE_SIZE - 1)
     *  =   0000 0000 0000 0000 0101
     *  ~   1111 1111 1111 1111 1010
     * +1   1111 1111 1111 1111 1011
     *  &   0000 0000 0000 0000 0111 (VIRTUAL_PAGE_SIZE - 1)
     *  =   0000 0000 0000 0000 0011 (=3)
     *
     * Result: 0x12345 + 0x3 = 0x12348
     *
     * NOTE: VIRTUAL_PAGE_SIZE - 1 is a const expression and can be evaluated at compile time.
     * NOTE: This strategy only works with page sizes which are % 2 = 0!
     */
    uint32 summand_u32 = (((~(adr_u32 & (uint32)(FEE_VIRTUAL_PAGE_SIZE - 1u)))) + 1u) & (uint32)(FEE_VIRTUAL_PAGE_SIZE - 1u);
    return(adr_u32 + summand_u32);
}

/**
 * \brief   Round down an address to the next page border.
 *
 * \param   adr_u32     Address to round down
 *
 * \return  Address rounded down to the next page border
 *
 * \attention   Whenever a flash must be supported which does NOT have 2^n page size this function must be changed!
*/
LOCAL_INLINE uint32 Fee_Prv_LibAdrFloor(uint32 adr_u32)
{
    /*
     * Example with adr 0x12345 and page size 8.
     *
     *
     *      0000 0000 0000 0000 0111 (VIRTUAL_PAGE_SIZE - 1)
     *  ~   1111 1111 1111 1111 1000
     *  &   0001 0010 0011 0100 0101 (adr)
     *  =   0001 0010 0011 0100 0000 (result)
     *
     * Result: 0x12345 => 0x12340
     *
     * NOTE: VIRTUAL_PAGE_SIZE - 1 is a const expression and can be evaluated at compile time.
     * NOTE: This strategy only works with page sizes which are % 2 = 0!
     */
    uint32 result_u32 = adr_u32 & (~((uint32)(FEE_VIRTUAL_PAGE_SIZE - 1u)));
    return(result_u32);
}

/**
 * \brief   Set a piece of RAM to a specified value.
 *
 * \param   bfr_pv      Pointer to piece of RAM which shall be set
 * \param   value_cu8   New value of the RAM
 * \param   size_cu32   Size of the RAM block
 *

*/
LOCAL_INLINE void Fee_Prv_LibMemSet(void * bfr_pv, const uint8 value_cu8, const uint32 size_cu32)
{
    uint32  a_u32;
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    uint8 * bfr_pu8 = bfr_pv;

    for(a_u32 = 0; a_u32 < size_cu32; a_u32++)
    {
        bfr_pu8[a_u32] = value_cu8;
    }
}

/**
 * \brief   Copy a piece of memory to another piece.
 *
 * \param   src_pcv     Source
 * \param   dst_pv      Destination
 * \param   size_cu32   Amount of bytes to copy
*/
LOCAL_INLINE void Fee_Prv_LibMemCopy(void const * src_pcv, void * dst_pv, uint32 const size_cu32)
{
    uint32          a_u32    = 0;
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    uint8   const * src_pcu8 = src_pcv;
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    uint8         * dst_pu8  = dst_pv;

    for(a_u32 = 0; a_u32 < size_cu32; a_u32++)
    {
        dst_pu8[a_u32] = src_pcu8[a_u32];
    }
}

/**
 * \brief   Find out whether a value is located within a certain range
 *
 * \param   val_u32     Value to check
 * \param   loBound_u32 Lower bound
 * \param   hiBound_u32 Upper bound
 *
 * \pre     loBound_u32 <= hiBound_u32
 * \post    if loBound_u32 <= val_u32 <= hiBound_u32 then true else false
*/
LOCAL_INLINE boolean Fee_Prv_LibIsInRange(uint32 val_u32, uint32 loBound_u32, uint32 hiBound_u32)
{
    boolean result_b;

    if((loBound_u32 <= val_u32) && (val_u32 <= hiBound_u32))
    {
        result_b = TRUE;
    }
    else
    {
        result_b = FALSE;
    }

    return(result_b);
}

/**
 * \brief   Check whether some data is equal to the erase pattern of the flash.
 *
 * \param   bfr_pcv     Buffer to the data
 * \param   length_u32  Amount of bytes to check for the erase pattern.
*/
LOCAL_INLINE boolean Fee_Prv_LibIsErased(void const * bfr_pcv, uint32 length_u32)
{
    uint32          a_u32;
    /* MR12 RULE 11.5 VIOLATION: uint8 * alignment is not stricter than void * alignment */
    uint8   const * bfr_pcu8 = bfr_pcv;

    for(a_u32 = 0; a_u32 < length_u32; a_u32++)
    {
        if(FEE_PRV_CFG_ERASE_PATTERN_8BIT != bfr_pcu8[a_u32])
        {
            return(FALSE);
        }
    }
    return(TRUE);
}

/**
 * \brief   Set the effort counter to its initial value.
 *          That means the main function is allowed to do some work.
 *          Typically this is only called at the beginning of the main function.
*/
LOCAL_INLINE void Fee_Prv_LibEffortReset(void)
{
    Fee_Prv_LibEffortMeasure_st.effortCtr_u32 = Fee_Prv_ConfigMaxEffort_cu32;
}

/**
 * \brief   Check whether the main function is allowed to continue its work or whether it shall exit to not break timing limitations.
 *          This function is always called if the main function want to execute a time consuming action.
 *          It is possible to specify for each time consuming action what the "costs" of this action are.
 *          This function multiplies the number of time consuming actions the main function wants to do with a weight factor.
 *          Then it checks whether the main function has the right to execute this action (there was not yet so much work done).
 *          Or whether the main function already did too much and it is getting dangerous to continue regarding timing limitations.
 *          Example:
 *              The main function already calculated 2k of CRC in the RAM.
 *              Now it wants to calculate again 2k of CRC in the flash.
 *              Regarding only one of both actions it would be still ok and no timing constraints are violated.
 *              Regading both actions together it might get dangerous to violate timing constraints regarding main function execution time.
 *              With the help of this function the main function will notice that and calculate the 2k CRC in the flash the next time it is called.
 *
 * \param   id_en           Which operation shall be executed
 *                          Currently can be:
 *                          - CRC in RAM
 *                          - CRC in flash
 *                          - Handle one FAT entry
 * \param   requested_u32   How often shall the operation be executed
 *                          Can mean:
 *                          - Amount of bytes for CRC calculation
 *                          - Amount of FAT entries to handle
 *
 * \return  The main function may continue or it shall stop and continue with the next call
 *
 * \retval  MEMIF_JOB_OK        The main function can continue
 * \retval  MEMIF_JOB_PENDING   The main function shall stop and continue with its next call
*/
LOCAL_INLINE MemIf_JobResultType Fee_Prv_LibEffortLimit(Fee_Prv_LibEffortLimit_ten id_en, uint32 requested_u32)
{
    MemIf_JobResultType result_en = MEMIF_JOB_OK;

    if(TRUE == Fee_Prv_LibEffortMeasure_st.enabled_b)
    {
        /*
         * Weighting an action is only allowed logarithmic.
         * That means an action costs 1,2,4 or 8..
         * This is to ensure fast calculation since the action*weight can be calculated with bit shifting.
         */
        uint32 cost_u32 = requested_u32 << Fee_Prv_LibEffortWeights_au8[(uint32)id_en];
        if(cost_u32 <= Fee_Prv_LibEffortMeasure_st.effortCtr_u32)
        {
            Fee_Prv_LibEffortMeasure_st.effortCtr_u32 -= cost_u32;
        }
        else
        {
            Fee_Prv_LibEffortMeasure_st.effortCtr_u32 = 0u;
            result_en = MEMIF_JOB_PENDING;
        }
    }

    return(result_en);
}


/**
 * \brief   Request an amount of work for a specific action.
 *          If it not possible to do all the work in one main function then return as much as possible.
 *
 * \param   id_en           ID of the action
 * \param   requested_u32   Requested amount of work to do
 *
 * \return  Allowed amount of work to do in this main function call
 *
 * \seealso Fee_Prv_LibEffortLimit
*/
LOCAL_INLINE uint32 Fee_Prv_LibEffortGet(Fee_Prv_LibEffortLimit_ten id_en, uint32 requested_u32)
{
    uint32 result_u32 = requested_u32;

    if(TRUE == Fee_Prv_LibEffortMeasure_st.enabled_b)
    {
        uint32 cost_u32                             = requested_u32 << Fee_Prv_LibEffortWeights_au8[id_en];
        result_u32                                  = Fee_Prv_LibMin(cost_u32, Fee_Prv_LibEffortMeasure_st.effortCtr_u32);
        Fee_Prv_LibEffortMeasure_st.effortCtr_u32   -= result_u32;
        result_u32                                  >>= Fee_Prv_LibEffortWeights_au8[id_en];
    }

    return(result_u32);
}

/**
 * \brief   Enable or disable the usage of the effort limitation.
 *          During init this is disabled since the only goal is to initalize as fast as possible.
 *          During cyclic operation this is enabled in order to not violate task execution time constraints.
*/
LOCAL_INLINE void Fee_Prv_LibUseEffortLimit(boolean use_b)
{
    Fee_Prv_LibEffortMeasure_st.enabled_b = use_b;
}

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_LIB_H */
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
