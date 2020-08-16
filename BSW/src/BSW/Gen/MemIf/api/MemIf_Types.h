

#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/
typedef enum
{
    MEMIF_UNINIT,
    MEMIF_IDLE,
    MEMIF_BUSY,
    MEMIF_BUSY_INTERNAL
}MemIf_StatusType;

typedef enum
{
    MEMIF_JOB_OK,
    MEMIF_JOB_FAILED,
    MEMIF_JOB_PENDING,
    MEMIF_JOB_CANCELED,
    MEMIF_BLOCK_INCONSISTENT,
    MEMIF_BLOCK_INVALID
}MemIf_JobResultType;

typedef enum
{
    MEMIF_MODE_SLOW,
    MEMIF_MODE_FAST
}MemIf_ModeType;

typedef enum
{
    MEMIF_RB_MIGRATION_RESULT_INIT_E              = 0,    // Initialization value, result not yet available
    MEMIF_RB_MIGRATION_RESULT_NOT_NECESSARY_E     = 1,    // RAM size == size on medium (no migration necessary)
    MEMIF_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E   = 2,    // RAM size < size on medium (remaining data discarded)
    MEMIF_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E    = 3,    // RAM size > size on medium (remaining data filled with zero)
    MEMIF_RB_MIGRATION_RESULT_NOT_DONE_E          = 4,    // Migration not done, because data was not read
    MEMIF_RB_MIGRATION_RESULT_DEACTIVATED_E       = 5     // Migration is deactivated by configuration
}MemIf_Rb_MigrationResult_ten;

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

/* MEMIF_TYPES_H */
#endif
