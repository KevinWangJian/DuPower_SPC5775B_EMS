/*
 * This is Os_Compiler_Cfg.h for target platform: PPCe200WR/MPC5744P
 */

/* [COMPILER054] [COMPILER055] */
#ifndef OS_COMPILER_CFG_H
#define OS_COMPILER_CFG_H

/* memclass and ptrclass macros */
#define OS_CODE               /* not required */ /* Code */
#define OS_CODE_FAST          /* not required */ /* Often-used code */
#define OS_CONST              /* not required */ /* Global or static constants. */
#define OS_APPL_DATA          /* not required */ /* References on application data (expected to be in RAM or ROM) passed via API. */
#define OS_APPL_CONST         /* not required */ /* References on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API */
#define OS_APPL_CODE          /* not required */ /* References on application functions. (e.g. call back function pointers) */
#define OS_VAR_NOINIT         /* not required */ /* Globals or statics which are never initialized. */
#define OS_VAR_POWER_ON_INIT  /* not required */ /* Globals or statics which are initialized after PO reset. */
#define OS_VAR_FAST           /* not required */ /* Globals or statics which require fast or bitwise access. */
#define OS_VAR                /* not required */ /* Globals or statics which are initialized after every reset. */

#define OS_VAR_CORE0_NOINIT   /* not required */ /* Core 0 local data  */
#define OS_VAR_CORE1_NOINIT   /* not required */ /* Core 1 local data  */
#define OS_VAR_CORE2_NOINIT   /* not required */ /* Core 2 local data  */
#define OS_VAR_CORE0_POWER_ON_INIT   /* not required */ /* Core 0 local data initialized after PO reset. */
#define OS_VAR_CORE1_POWER_ON_INIT   /* not required */ /* Core 1 local data initialized after PO reset. */
#define OS_VAR_CORE2_POWER_ON_INIT   /* not required */ /* Core 2 local data initialized after PO reset. */

#define OS_OS_CBK_GETABORTSTACK_CODE /* not required */ /* Code for Os_Cbk_GetAbortStack */

#endif /* OS_COMPILER_CFG_H */
