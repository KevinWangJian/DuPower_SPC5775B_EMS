

/*
 * The order unit is responsible for handling all external calls to the Fee besides the main and init function.
 * It stores the received orders in internal order slots.
 * The main function will poll orders from the order unit and inform the order unit if an order is finished.
 */

#ifndef FEE_PRV_ORDER_H
#define FEE_PRV_ORDER_H

/* Disable the Fee common part when the Fs1 is selected - currently the Fs1 is a complete Fee */
#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 != FEE_PRV_CFG_SELECTED_FS))

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/

typedef enum
{
    FEE_PRV_ORDERTYPE_NONE_E = 0,
    FEE_PRV_ORDERTYPE_READ_E,
    FEE_PRV_ORDERTYPE_WRITE_E,
    FEE_PRV_ORDERTYPE_INVALIDATE_E,
    FEE_PRV_ORDERTYPE_BLOCKMAINTENANCE_E
} Fee_Prv_OrderType_ten;

/*
 * Every order is stored in such a order struct.
 * There are two order slots, one for the NVM and one for an adapter.
 */
typedef struct
{
    Fee_Prv_OrderType_ten           type_en;                /* Read/Write/Invalidate order                                              */
    MemIf_Rb_MigrationResult_ten *  migrationResult_pen;    /* Pointer to the migration result of the appropriate active block          */
    uint8                        *  bfr_pu8;                /* Pointer to a variable buffer - needed for read orders                    */
    uint8                  const *  bfr_pcu8;               /* Pointer to a constant buffer - needed for write orders                   */
    uint16                          blockNumber_u16;        /* Blocknumber as defined in Fee_Cfg.h - this is NOT the persistent ID !    */
    uint16                          length_u16;             /* Length of the block operation                                            */
    uint16                          offset_u16;             /* Offset of the block operation                                            */
} Fee_Prv_OrderJob_tst;

/* All jobs and their results */
typedef struct
{
    Fee_Prv_OrderJob_tst            jobs_ast[FEE_PRV_REQUESTER_MAX_E];      		/* Current jobs             				*/
    MemIf_JobResultType             results_aen[FEE_PRV_REQUESTER_MAX_E];   		/* Results of the last jobs                 */
    MemIf_Rb_MigrationResult_ten    firstInitMigrationResult_aen[FEE_NUM_BLOCKS];   /* Migration result of the first read job 	*/
    MemIf_Rb_MigrationResult_ten    currentMigrationResult_en;                      /* Migration result of the last read job    */
} Fee_Prv_Order_tst;

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
extern Fee_Prv_OrderJob_tst *   Fee_Prv_OrderBegin(void);
extern void                     Fee_Prv_OrderEnd(Fee_Prv_OrderJob_tst * order_pst, MemIf_JobResultType result_en);
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"

/* 1 != FEE_PRV_CFG_SELECTED_FS */
#endif

/* FEE_PRV_ORDER_H */
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
