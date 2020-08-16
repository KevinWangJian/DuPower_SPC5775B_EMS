

/*
 * The medium unit is the lowest layer in the Fee architecture.
 * It abstracts direct flash access and Fls_Read flash access.
 * The Fee assumes that it is the only flash user.
 * To reduce the number of error paths it is not visible to higher layers,
 * whether starting a flash job returned with E_NOT_OK or
 * whether the flash job finished with MEMIF_JOB_FAILED.
 * Additionally it contains a big buffer which is used for various operations,
 * mainly the buffer is used for writing internal management data and during the data sector change.
 * The medium unit does also provide blocking flash access,
 * this means polling until Fls_GetJobResult != MEMIF_JOB_PENDING
 * or asynchronous flash access.
*/

#ifndef FEE_PRV_MEDIUM_H
#define FEE_PRV_MEDIUM_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

/* Prefetch modes */
typedef enum
{
    FEE_PRV_PRELOAD_E,
    FEE_PRV_POSTLOAD_E
} Fee_Prv_MediumLoadMode_ten;

/* States for loading data from flash to RAM */
typedef enum
{
    FEE_PRV_LOAD_IDLE_E = 0,    /* Nothing to do        */
    FEE_PRV_LOAD_BUSY_E         /* Currently loading    */
} Fee_Prv_MediumLoad_ten;

/* State for programming data from RAM to flash */
typedef enum
{
    FEE_PRV_MEDIUM_WRITE_IDLE_E = 0,    /* Nothing to do                                        */
    FEE_PRV_MEDIUM_WRITE_BLANKCHECK_E,  /* Make sure the target space is not already programmed */
    FEE_PRV_MEDIUM_WRITE_PROGRAM_E,     /* Program data from RAM to flash                       */
    FEE_PRV_MEDIUM_WRITE_COMPARE_E,     /* Compare RAM to flash                                 */
    FEE_PRV_MEDIUM_WRITE_FINAL_E        /* Programming finished successfully                    */
} Fee_Prv_MediumWrite_ten;

/* Union for the big buffer forces 32bit alignment */
typedef union
{
    uint32  u32[FEE_PRV_CFG_BFRSIZE/4u];    /* This union member shall NEVER be used - it only forces 32bit alignment   */
    uint8   u8[FEE_PRV_CFG_BFRSIZE];        /* uint8 indexing of the buffer                                             */
} Fee_Prv_MediumBuffer_tst;

typedef struct
{
    Fee_Prv_MediumBuffer_tst    buffer_u;           /* Big buffer for flash I/O operations                  */
    uint32                      iterator_u32;       /* Iterator used to iterate through the flash in steps  */
    uint32                      limitHi_u32;        /* Upper limit of data from flash in the medium buffer  */
    uint32                      limitLo_u32;        /* Lower limit of data from flash in the medium buffer  */
    Std_ReturnType              lastFlsResult_en;   /* Result of the last flash job start                   */
    boolean                     sync_b;             /* Polling = TRUE or Asynchronous = FALSE flash access  */
}  Fee_Prv_Medium_tst;

typedef struct
{
    Fee_Prv_MediumLoad_ten  state_en;           /* Current state                */
    uint32                  reloadAdr_u32;      /* Address to reload from       */
} Fee_Prv_MediumLoad_tst;

typedef struct
{
    uint32      nrBytesDone_u32;    /* Already considered number of bytes   */
    uint32      length_u32;         /* Total number of bytes to consider    */
    uint32 *    crc_pu32;           /* Pointer to the result                */
    boolean     firstCall_b;        /* First CRC call yes or no             */
} Fee_Prv_MediumCalcCrc_tst;

typedef struct
{
    Fee_Prv_MediumWrite_ten state_en;           /* State of the programming operation   */
    void const *            bfr_pcv;            /* Buffer where to program from         */
    uint32                  adr_u32;            /* Address where to program to          */
    uint32                  length_u32;         /* Bytes to program in total            */
    uint32                  done_u32;           /* Bytes already programmed             */
    uint32                  bytes2Program_u32;  /* Bytes to program with the next cycle */
    boolean                 entry_b;            /* Next state shall be entered          */
} Fee_Prv_MediumWrite_tst;

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern void Fee_Prv_MediumSetSync(boolean newSync_b);
extern void Fee_Prv_MediumRead(uint32 adr_u32, void * bfr_pv, uint32 length_u32);
extern void Fee_Prv_MediumWrite(uint32 adr_u32, void const * bfr_pcv, uint32 length_u32);
extern void Fee_Prv_MediumErase(uint32 adr_u32, uint32 length_u32);
extern void Fee_Prv_MediumCompare(uint32 flsAdr_u32, void const * bfr_pcv, uint32 length_u32);
extern void Fee_Prv_MediumBlankCheck(uint32 adr_u32, uint32 length_u32);
extern void Fee_Prv_MediumShredder(uint32 adr_u32, uint32 length_u32);
extern void Fee_Prv_MediumCalcCrc(uint32 adr_u32, uint32 length_u32, uint32 * crc_pu32, boolean firstCall_b);

extern MemIf_JobResultType Fee_Prv_MediumReadDo         (void);
extern MemIf_JobResultType Fee_Prv_MediumWriteDo        (void);
extern MemIf_JobResultType Fee_Prv_MediumEraseDo        (void);
extern MemIf_JobResultType Fee_Prv_MediumCompareDo      (void);
extern MemIf_JobResultType Fee_Prv_MediumBlankCheckDo   (void);
extern MemIf_JobResultType Fee_Prv_MediumShredderDo     (void);
extern MemIf_JobResultType Fee_Prv_MediumCalcCrcDo      (void);

extern void                 Fee_Prv_MediumSetIterator   (uint32 adr_u32                             );
extern uint32               Fee_Prv_MediumGetIterator   (void                                       );
extern MemIf_JobResultType  Fee_Prv_MediumNext          (uint32 length_u32, void const * * ptr_cppcv);
extern MemIf_JobResultType  Fee_Prv_MediumPre           (uint32 length_u32, void const * * ptr_cppcv);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

#if (defined(FLS_RB_ROBUST_PROG_STATUS_API) && (TRUE == FLS_RB_ROBUST_PROG_STATUS_API))
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern uint32           Fee_Prv_MediumGetWlSize(void);
extern boolean          Fee_Prv_MediumHasWlError(void);
extern uint32           Fee_Prv_MediumGetWlErrorAdr(void);
extern uint32           Fee_Prv_MediumGetWlErrorLength(void);
extern void             Fee_Prv_MediumRescueWlData(void);
extern uint8    const * Fee_Prv_MediumGetWlData(void);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

#else
LOCAL_INLINE uint32             Fee_Prv_MediumGetWlSize(void)           { return(0u);       }
LOCAL_INLINE boolean            Fee_Prv_MediumHasWlError(void)          { return(FALSE);    }
LOCAL_INLINE uint32             Fee_Prv_MediumGetWlErrorAdr(void)       { return(0u);       }
LOCAL_INLINE uint32             Fee_Prv_MediumGetWlErrorLength(void)    { return(0u);       }
LOCAL_INLINE void               Fee_Prv_MediumRescueWlData(void)        {                   }
LOCAL_INLINE uint8      const * Fee_Prv_MediumGetWlData(void)           { return(NULL_PTR); }

/*
 * Use inlines instead of defines since defines lead to compiler warnings, example: Comparison >= 0
 * Compiler should still be able to perfomr maximum optimizations with inlines.
 */
#endif

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_MEDIUM_H */
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
