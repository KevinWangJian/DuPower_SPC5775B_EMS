/*----------------------------------------------------------------------------*/
/************** *SAMPLE* of MemMap.h. Not for production purposes *************/
/*----------------------------------------------------------------------------*/
#define MEM_VENDOR_ID        (11U)
#define MEM_AR_MAJOR_VERSION (4U)
#define MEM_AR_MINOR_VERSION (2U)
#define MEM_AR_PATCH_VERSION (2U)
#define MEM_SW_MAJOR_VERSION (5U)
#define MEM_SW_MINOR_VERSION (4U)
#define MEM_SW_PATCH_VERSION (2U)

/* -------------------------------------------------------------------------- */
/*             OS (Operating System)                                          */
/* -------------------------------------------------------------------------- */
#include <Os_MemMap.h>

/*******************************************************************************
**                      Default section mapping                               **
*******************************************************************************/
#if defined (START_WITH_IF)

/* -------------------------------------------------------------------------- */
/* RAM variables not initialized                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_NOINIT_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_8BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_8BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_16BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_16BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_32BIT)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_32BIT

#elif defined (DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_NOINIT_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_NOINIT_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables power-on initialized                                         */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_8BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_8BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_16BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_16BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_32BIT)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_32BIT

#elif defined (DEFAULT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables initialized from ROM on reset                                */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_8BIT)
  #undef      DEFAULT_START_SEC_VAR_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_8BIT

#elif defined (DEFAULT_START_SEC_VAR_16BIT)
  #undef      DEFAULT_START_SEC_VAR_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_16BIT

#elif defined (DEFAULT_START_SEC_VAR_32BIT)
  #undef      DEFAULT_START_SEC_VAR_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_32BIT

#elif defined (DEFAULT_START_SEC_VAR_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* RAM variables frequently used or accessed bitwise                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_VAR_FAST_BOOLEAN)
  #undef      DEFAULT_START_SEC_VAR_FAST_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_BOOLEAN

#elif defined (DEFAULT_START_SEC_VAR_FAST_8BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_8BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_8BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_8BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_16BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_16BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_16BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_16BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_32BIT)
  #undef      DEFAULT_START_SEC_VAR_FAST_32BIT
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_32BIT)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_32BIT

#elif defined (DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_VAR_FAST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_VAR_FAST_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* ROM constants                                                              */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_BOOLEAN)
  #undef      DEFAULT_START_SEC_CONST_BOOLEAN
#elif defined (DEFAULT_STOP_SEC_CONST_BOOLEAN)
  #undef      DEFAULT_STOP_SEC_CONST_BOOLEAN

#elif defined (DEFAULT_START_SEC_CONST_8BIT)
  #undef      DEFAULT_START_SEC_CONST_8BIT
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT)
  #undef      DEFAULT_STOP_SEC_CONST_8BIT

#elif defined (DEFAULT_START_SEC_CONST_16BIT)
  #undef      DEFAULT_START_SEC_CONST_16BIT
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT)
  #undef      DEFAULT_STOP_SEC_CONST_16BIT

#elif defined (DEFAULT_START_SEC_CONST_32BIT)
  #undef      DEFAULT_START_SEC_CONST_32BIT
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT)
  #undef      DEFAULT_STOP_SEC_CONST_32BIT

#elif defined (DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED)
  #undef      DEFAULT_START_SEC_CONST_UNSPECIFIED
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED)
  #undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED

/* -------------------------------------------------------------------------- */
/* ROM FAR constants                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CONST_BOOLEAN_FAR)
  #undef      DEFAULT_START_SEC_CONST_BOOLEAN_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_BOOLEAN_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_BOOLEAN_FAR

#elif defined (DEFAULT_START_SEC_CONST_8BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_8BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_8BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_8BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_16BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_16BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_16BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_16BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_32BIT_FAR)
  #undef      DEFAULT_START_SEC_CONST_32BIT_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_32BIT_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_32BIT_FAR

#elif defined (DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR)
  #undef      DEFAULT_START_SEC_CONST_UNSPECIFIED_FAR
#elif defined (DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR)
  #undef      DEFAULT_STOP_SEC_CONST_UNSPECIFIED_FAR

/* -------------------------------------------------------------------------- */
/* ROM code                                                                   */
/* -------------------------------------------------------------------------- */
#elif defined (DEFAULT_START_SEC_CODE)
  #undef      DEFAULT_START_SEC_CODE
#elif defined (DEFAULT_STOP_SEC_CODE)
  #undef      DEFAULT_STOP_SEC_CODE

#elif defined (DEFAULT_START_SEC_CODE_FAST)
  #undef      DEFAULT_START_SEC_CODE_FAST
#elif defined (DEFAULT_STOP_SEC_CODE_FAST)
  #undef      DEFAULT_STOP_SEC_CODE_FAST

#elif defined (DEFAULT_START_SEC_CODE_SLOW)
  #undef      DEFAULT_START_SEC_CODE_SLOW
#elif defined (DEFAULT_STOP_SEC_CODE_SLOW)
  #undef      DEFAULT_STOP_SEC_CODE_SLOW

#elif defined (DEFAULT_START_SEC_CODE_LIB)
  #undef      DEFAULT_START_SEC_CODE_LIB
#elif defined (DEFAULT_STOP_SEC_CODE_LIB)
  #undef      DEFAULT_STOP_SEC_CODE_LIB

#elif defined (DEFAULT_START_SEC_VECTORS)
  #undef      DEFAULT_START_SEC_VECTORS
#elif defined (DEFAULT_STOP_SEC_VECTORS)
  #undef      DEFAULT_STOP_SEC_VECTORS
/* -------------------------------------------------------------------------- */
/* End of default section mapping                                             */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* Section mapping for RTE code                                               */
/* -------------------------------------------------------------------------- */
#elif defined (RTE_START_SEC_CODE)
  #undef	   RTE_START_SEC_CODE
#elif defined (RTE_STOP_SEC_CODE)
  #undef	   RTE_STOP_SEC_CODE

 /* ------------------------------------------------------------------------- */
/* Section mapping for App                                                    */
/* -------------------------------------------------------------------------- */
#elif defined (RTE_START_SEC_Partition_Core0_CODE)
  #undef	   RTE_START_SEC_Partition_Core0_CODE
  #define CPU0_START_SEC_CODE
#elif defined (RTE_STOP_SEC_Partition_Core0_CODE)
  #undef	   RTE_STOP_SEC_Partition_Core0_CODE
  #define CPU0_STOP_SEC_CODE

#elif defined (RTE_START_SEC_Partition_Core1_CODE)
  #undef	   RTE_START_SEC_Partition_Core1_CODE
  #define CPU1_START_SEC_CODE
#elif defined (RTE_STOP_SEC_Partition_Core1_CODE)
  #undef	   RTE_STOP_SEC_Partition_Core1_CODE
  #define CPU1_STOP_SEC_CODE

#elif defined (RTE_START_SEC_CODE)
  #undef	   RTE_START_SEC_CODE
  #define SHARED_START_SEC_CODE
#elif defined (RTE_STOP_SEC_CODE)
  #undef	   RTE_STOP_SEC_CODE
  #define SHARED_STOP_SEC_CODE
/* -------------------------------------------------------------------------- */
/* Section data mapping for App                                               */
/* -------------------------------------------------------------------------- */
#elif defined (RTE_START_SEC_Partition_Core0_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_CLEARED_UNSPECIFIED
  #define CPU0_START_SEC_RAM_CLEARED_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_UNSPECIFIED
  #define CPU0_STOP_SEC_RAM_CLEARED_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core0_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_CLEARED_BOOLEAN
  #define CPU0_START_SEC_RAM_CLEARED_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_BOOLEAN
  #define CPU0_STOP_SEC_RAM_CLEARED_BOOL

#elif defined (RTE_START_SEC_Partition_Core0_VAR_CLEARED_8)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_CLEARED_8
  #define CPU0_START_SEC_RAM_CLEARED_8
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_8)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_8
  #define CPU0_STOP_SEC_RAM_CLEARED_8

#elif defined (RTE_START_SEC_Partition_Core0_VAR_CLEARED_16)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_CLEARED_16
  #define CPU0_START_SEC_RAM_CLEARED_16
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_16)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_16
  #define CPU0_STOP_SEC_RAM_CLEARED_16

#elif defined (RTE_START_SEC_Partition_Core0_VAR_CLEARED_32)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_CLEARED_32
  #define CPU0_START_SEC_RAM_CLEARED_32
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_32)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_CLEARED_32
  #define CPU0_STOP_SEC_RAM_CLEARED_32

#elif defined (RTE_START_SEC_Partition_Core0_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_INIT_UNSPECIFIED
  #define CPU0_START_SEC_RAM_INIT_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_INIT_UNSPECIFIED
  #define CPU0_STOP_SEC_RAM_INIT_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core0_VAR_INIT_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_INIT_BOOLEAN
  #define CPU0_START_SEC_RAM_INIT_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_INIT_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_INIT_BOOLEAN
  #define CPU0_STOP_SEC_RAM_INIT_BOOL


#elif defined (RTE_START_SEC_Partition_Core0_VAR_INIT_8)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_INIT_8
  #define CPU0_START_SEC_RAM_INIT_8
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_INIT_8)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_INIT_8
  #define CPU0_STOP_SEC_RAM_INIT_8

#elif defined (RTE_START_SEC_Partition_Core0_VAR_INIT_16)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_INIT_16
  #define CPU0_START_SEC_RAM_INIT_16
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_INIT_16)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_INIT_16
  #define CPU0_STOP_SEC_RAM_INIT_16

#elif defined (RTE_START_SEC_Partition_Core0_VAR_INIT_32)
  #undef	   RTE_START_SEC_Partition_Core0_VAR_INIT_32
  #define CPU0_START_SEC_RAM_INIT_32
#elif defined (RTE_STOP_SEC_Partition_Core0_VAR_INIT_32)
  #undef	   RTE_STOP_SEC_Partition_Core0_VAR_INIT_32
  #define CPU0_STOP_SEC_RAM_INIT_32

#elif defined (RTE_START_SEC_Partition_Core0_CONST_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core0_CONST_UNSPECIFIED
  #define CPU0_START_SEC_CONST_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core0_CONST_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core0_CONST_UNSPECIFIED
  #define CPU0_STOP_SEC_CONST_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core0_CONST_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core0_CONST_BOOLEAN
  #define CPU0_START_SEC_CONST_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core0_CONST_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core0_CONST_BOOLEAN
  #define CPU0_STOP_SEC_CONST_BOOL


#elif defined (RTE_START_SEC_Partition_Core0_CONST_8)
  #undef	   RTE_START_SEC_Partition_Core0_CONST_8
  #define CPU0_START_SEC_CONST_8
#elif defined (RTE_STOP_SEC_Partition_Core0_CONST_8)
  #undef	   RTE_STOP_SEC_Partition_Core0_CONST_8
  #define CPU0_STOP_SEC_CONST_8

#elif defined (RTE_START_SEC_Partition_Core0_CONST_16)
  #undef	   RTE_START_SEC_Partition_Core0_CONST_16
  #define CPU0_START_SEC_CONST_16
#elif defined (RTE_STOP_SEC_Partition_Core0_CONST_16)
  #undef	   RTE_STOP_SEC_Partition_Core0_CONST_16
  #define CPU0_STOP_SEC_CONST_16

#elif defined (RTE_START_SEC_Partition_Core0_CONST_32)
  #undef	   RTE_START_SEC_Partition_Core0_CONST_32
  #define CPU0_START_SEC_CONST_32
#elif defined (RTE_STOP_SEC_Partition_Core0_CONST_32)
  #undef	   RTE_STOP_SEC_Partition_Core0_CONST_32
  #define CPU0_STOP_SEC_CONST_32

#elif defined (RTE_START_SEC_Partition_Core1_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_CLEARED_UNSPECIFIED
  #define CPU1_START_SEC_RAM_CLEARED_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_UNSPECIFIED
  #define CPU1_STOP_SEC_RAM_CLEARED_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core1_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_CLEARED_BOOLEAN
  #define CPU1_START_SEC_RAM_CLEARED_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_BOOLEAN
  #define CPU1_STOP_SEC_RAM_CLEARED_BOOL

#elif defined (RTE_START_SEC_Partition_Core1_VAR_CLEARED_8)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_CLEARED_8
  #define CPU1_START_SEC_RAM_CLEARED_8
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_8)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_8
  #define CPU1_STOP_SEC_RAM_CLEARED_8

#elif defined (RTE_START_SEC_Partition_Core1_VAR_CLEARED_16)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_CLEARED_16
  #define CPU1_START_SEC_RAM_CLEARED_16
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_16)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_16
  #define CPU1_STOP_SEC_RAM_CLEARED_16

#elif defined (RTE_START_SEC_Partition_Core1_VAR_CLEARED_32)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_CLEARED_32
  #define CPU1_START_SEC_RAM_CLEARED_32
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_32)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_CLEARED_32
  #define CPU1_STOP_SEC_RAM_CLEARED_32

#elif defined (RTE_START_SEC_Partition_Core1_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_INIT_UNSPECIFIED
  #define CPU1_START_SEC_RAM_INIT_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_UNSPECIFIED
  #define CPU1_STOP_SEC_RAM_INIT_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core1_VAR_INIT_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_INIT_BOOLEAN
  #define CPU1_START_SEC_RAM_INIT_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_BOOLEAN
  #define CPU1_STOP_SEC_RAM_INIT_BOOL


#elif defined (RTE_START_SEC_Partition_Core1_VAR_INIT_8)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_INIT_8
  #define CPU1_START_SEC_RAM_INIT_8
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_8)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_8
  #define CPU1_STOP_SEC_RAM_INIT_8

#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_8)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_8
  #define CPU1_START_SEC_RAM_INIT_16
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_16)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_16
  #define CPU1_STOP_SEC_RAM_INIT_16

#elif defined (RTE_START_SEC_Partition_Core1_VAR_INIT_32)
  #undef	   RTE_START_SEC_Partition_Core1_VAR_INIT_32
  #define CPU1_START_SEC_RAM_INIT_32
#elif defined (RTE_STOP_SEC_Partition_Core1_VAR_INIT_32)
  #undef	   RTE_STOP_SEC_Partition_Core1_VAR_INIT_32
  #define CPU1_STOP_SEC_RAM_INIT_32

#elif defined (RTE_START_SEC_Partition_Core1_CONST_UNSPECIFIED)
  #undef	   RTE_START_SEC_Partition_Core1_CONST_UNSPECIFIED
  #define CPU1_START_SEC_CONST_UNSPECIFIED
#elif defined (RTE_STOP_SEC_Partition_Core1_CONST_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_Partition_Core1_CONST_UNSPECIFIED
  #define CPU1_STOP_SEC_CONST_UNSPECIFIED

#elif defined (RTE_START_SEC_Partition_Core1_CONST_BOOLEAN)
  #undef	   RTE_START_SEC_Partition_Core1_CONST_BOOLEAN
  #define CPU1_START_SEC_CONST_BOOL
#elif defined (RTE_STOP_SEC_Partition_Core1_CONST_BOOLEAN)
  #undef	   RTE_STOP_SEC_Partition_Core1_CONST_BOOLEAN
  #define CPU1_STOP_SEC_CONST_BOOL


#elif defined (RTE_START_SEC_Partition_Core1_CONST_8)
  #undef	   RTE_START_SEC_Partition_Core1_CONST_8
  #define CPU1_START_SEC_CONST_8
#elif defined (RTE_STOP_SEC_Partition_Core1_CONST_8)
  #undef	   RTE_STOP_SEC_Partition_Core1_CONST_8
  #define CPU1_STOP_SEC_CONST_8

#elif defined (RTE_START_SEC_Partition_Core1_CONST_16)
  #undef	   RTE_START_SEC_Partition_Core1_CONST_16
  #define CPU1_START_SEC_CONST_16
#elif defined (RTE_STOP_SEC_Partition_Core1_CONST_16)
  #undef	   RTE_STOP_SEC_Partition_Core1_CONST_16
  #define CPU1_STOP_SEC_CONST_16

#elif defined (RTE_START_SEC_Partition_Core1_CONST_32)
  #undef	   RTE_START_SEC_Partition_Core1_CONST_32
  #define CPU1_START_SEC_CONST_32
#elif defined (RTE_STOP_SEC_Partition_Core1_CONST_32)
  #undef	   RTE_STOP_SEC_Partition_Core1_CONST_32
  #define CPU1_STOP_SEC_CONST_32

#elif defined (RTE_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_START_SEC_VAR_CLEARED_UNSPECIFIED
  #define SHARED_START_SEC_RAM_CLEARED_UNSPECIFIED
#elif defined (RTE_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #define SHARED_STOP_SEC_RAM_CLEARED_UNSPECIFIED

#elif defined (RTE_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_START_SEC_VAR_CLEARED_BOOLEAN
  #define SHARED_START_SEC_RAM_CLEARED_BOOL
#elif defined (RTE_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef	   RTE_STOP_SEC_VAR_CLEARED_BOOLEAN
  #define SHARED_STOP_SEC_RAM_CLEARED_BOOL

#elif defined (RTE_START_SEC_VAR_CLEARED_8)
  #undef	   RTE_START_SEC_VAR_CLEARED_8
  #define SHARED_START_SEC_RAM_CLEARED_8
#elif defined (RTE_STOP_SEC_VAR_CLEARED_8)
  #undef	   RTE_STOP_SEC_VAR_CLEARED_8
  #define SHARED_STOP_SEC_RAM_CLEARED_8

#elif defined (RTE_START_SEC_VAR_CLEARED_16)
  #undef	   RTE_START_SEC_VAR_CLEARED_16
  #define SHARED_START_SEC_RAM_CLEARED_16
#elif defined (RTE_STOP_SEC_VAR_CLEARED_16)
  #undef	   RTE_STOP_SEC_VAR_CLEARED_16
  #define SHARED_STOP_SEC_RAM_CLEARED_16

#elif defined (RTE_START_SEC_VAR_CLEARED_32)
  #undef	   RTE_START_SEC_VAR_CLEARED_32
  #define SHARED_START_SEC_RAM_CLEARED_32
#elif defined (RTE_STOP_SEC_VAR_CLEARED_32)
  #undef	   RTE_STOP_SEC_VAR_CLEARED_32
  #define SHARED_STOP_SEC_RAM_CLEARED_32

#elif defined (RTE_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_START_SEC_VAR_INIT_UNSPECIFIED
  #define SHARED_START_SEC_RAM_INIT_UNSPECIFIED
#elif defined (RTE_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
  #define SHARED_STOP_SEC_RAM_INIT_UNSPECIFIED

#elif defined (RTE_START_SEC_VAR_INIT_BOOLEAN)
  #undef	   RTE_START_SEC_VAR_INIT_BOOLEAN
  #define SHARED_START_SEC_RAM_INIT_BOOL
#elif defined (RTE_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef	   RTE_STOP_SEC_VAR_INIT_BOOLEAN
  #define SHARED_STOP_SEC_RAM_INIT_BOOL


#elif defined (RTE_START_SEC_VAR_INIT_8)
  #undef	   RTE_START_SEC_VAR_INIT_8
  #define SHARED_START_SEC_RAM_INIT_8
#elif defined (RTE_STOP_SEC_VAR_INIT_8)
  #undef	   RTE_STOP_SEC_VAR_INIT_8
  #define SHARED_STOP_SEC_RAM_INIT_8

#elif defined (RTE_START_SEC_VAR_INIT_16)
  #undef	   RTE_START_SEC_VAR_INIT_16
  #define SHARED_START_SEC_RAM_INIT_16
#elif defined (RTE_STOP_SEC_VAR_INIT_16)
  #undef	   RTE_STOP_SEC_VAR_INIT_16
  #define SHARED_STOP_SEC_RAM_INIT_16

#elif defined (RTE_START_SEC_VAR_INIT_32)
  #undef	   RTE_START_SEC_VAR_INIT_32
  #define SHARED_START_SEC_RAM_INIT_32
#elif defined (RTE_STOP_SEC_VAR_INIT_32)
  #undef	   RTE_STOP_SEC_VAR_INIT_32
  #define SHARED_STOP_SEC_RAM_INIT_32

#elif defined (RTE_START_SEC_CONST_UNSPECIFIED)
  #undef	   RTE_START_SEC_CONST_UNSPECIFIED
  #define SHARED_START_SEC_CONST_UNSPECIFIED
#elif defined (RTE_STOP_SEC_CONST_UNSPECIFIED)
  #undef	   RTE_STOP_SEC_CONST_UNSPECIFIED
  #define SHARED_STOP_SEC_CONST_UNSPECIFIED

#elif defined (RTE_START_SEC_CONST_BOOLEAN)
  #undef	   RTE_START_SEC_CONST_BOOLEAN
  #define SHARED_START_SEC_CONST_BOOL
#elif defined (RTE_STOP_SEC_CONST_BOOLEAN)
  #undef	   RTE_STOP_SEC_CONST_BOOLEAN
  #define SHARED_STOP_SEC_CONST_BOOL


#elif defined (RTE_START_SEC_CONST_8)
  #undef	   RTE_START_SEC_CONST_8
  #define SHARED_START_SEC_CONST_8
#elif defined (RTE_STOP_SEC_CONST_8)
  #undef	   RTE_STOP_SEC_CONST_8
  #define SHARED_STOP_SEC_CONST_8

#elif defined (RTE_START_SEC_CONST_16)
  #undef	   RTE_START_SEC_CONST_16
  #define SHARED_START_SEC_CONST_16
#elif defined (RTE_STOP_SEC_CONST_16)
  #undef	   RTE_STOP_SEC_CONST_16
  #define SHARED_STOP_SEC_CONST_16

#elif defined (RTE_START_SEC_CONST_32)
  #undef	   RTE_START_SEC_CONST_32
  #define SHARED_START_SEC_CONST_32
#elif defined (RTE_STOP_SEC_CONST_32)
  #undef	   RTE_STOP_SEC_CONST_32
  #define SHARED_STOP_SEC_CONST_32

/* Calibration */
#elif defined (RTE_START_SEC_CALIB_BOOLEAN)
  #undef      RTE_START_SEC_CALIB_BOOLEAN
  #define DEFAULT_START_SEC_CALIB_BOOLEAN
#elif defined (RTE_STOP_SEC_CALIB_BOOLEAN)
  #undef      RTE_STOP_SEC_CALIB_BOOLEAN
  #define DEFAULT_STOP_SEC_CALIB_BOOLEAN

#elif defined (RTE_START_SEC_CALIB_8)
  #undef      RTE_START_SEC_CALIB_8
  #define DEFAULT_START_SEC_CALIB_8
#elif defined (RTE_STOP_SEC_CALIB_8)
  #undef      RTE_STOP_SEC_CALIB_8
  #define DEFAULT_STOP_SEC_CALIB_8

#elif defined (RTE_START_SEC_CALIB_16)
  #undef      RTE_START_SEC_CALIB_16
  #define DEFAULT_START_SEC_CALIB_16
#elif defined (RTE_STOP_SEC_CALIB_16)
  #undef      RTE_STOP_SEC_CALIB_16
  #define DEFAULT_STOP_SEC_CALIB_16

#elif defined (RTE_START_SEC_CALIB_32)
  #undef      RTE_START_SEC_CALIB_32
  #define DEFAULT_START_SEC_CALIB_32
#elif defined (RTE_STOP_SEC_CALIB_32)
  #undef      RTE_STOP_SEC_CALIB_32
  #define DEFAULT_STOP_SEC_CALIB_32

#elif defined (RTE_START_SEC_CALIB_UNSPECIFIED)
  #undef	   RTE_START_SEC_CALIB_UNSPECIFIED
  #define DEFAULT_START_SEC_CALIB_UNSPECIFIED
#elif defined (RTE_STOP_SEC_CALIB_UNSPECIFIED)
  #undef      RTE_STOP_SEC_CALIB_UNSPECIFIED
  #define DEFAULT_STOP_SEC_CALIB_UNSPECIFIED

#else


#endif  /* START_WITH_IF */


#include "MemMap.h"

/*** End of file **************************************************************/
