/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



/* <component>_MemMap.h for AUTOSAR Memory Mapping R4.0 Rev 3 */
/* MISRA RULE 19.15 VIOLATION: MemMap header concept - no protection against repeated inclusion intended */
/**/
#if defined RBA_BSWSRV_START_SEC_ENVRAM_32
    #undef  RBA_BSWSRV_START_SEC_ENVRAM_32
    /* MISRA RULE 3.4 VIOLATION: MemMap header concept - pragma is required */
    #pragma section ".bss.envram.a4" awB
#elif defined RBA_BSWSRV_STOP_SEC_ENVRAM_32
    #undef    RBA_BSWSRV_STOP_SEC_ENVRAM_32
    #pragma section

#elif defined RBA_BSWSRV_START_SEC_VAR_CLEARED_32
    #undef    RBA_BSWSRV_START_SEC_VAR_CLEARED_32
    #define BSW_START_SEC_DEFAULT_RAM0_CLEARED_32
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_VAR_CLEARED_32
    #undef    RBA_BSWSRV_STOP_SEC_VAR_CLEARED_32
    #define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_32
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_RAM0_CLEARED_UNSPECIFIED
    #include "Bsw_MemMap.h"

/* CPU instanced memory instead of an array element for each core */
/* IFX supports local RAM addressing in hardware. For JDP it is emulated with small addressing */
/* only used if RBA_MEMLAY_DATA_RAM_ALL is defined */
#elif defined RBA_BSWSRV_START_SEC_RAMALL_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_RAMALL_CLEARED_UNSPECIFIED
    /* MISRA RULE 3.4 VIOLATION: MemMap header concept - pragma is required */
    #if (MCU_RB_MACHINE_FAM == MCU_RB_IFX_UC1)
    #  pragma section ".zbss.ram_all.a4" awBz
    #else
    #  pragma section ".sbss.ram_all.a4" awBs
    #endif
#elif defined RBA_BSWSRV_STOP_SEC_RAMALL_CLEARED_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_RAMALL_CLEARED_UNSPECIFIED
    #pragma section

#elif defined RBA_BSWSRV_START_SEC_CONST_UNSPECIFIED
    #undef    RBA_BSWSRV_START_SEC_CONST_UNSPECIFIED
    #define BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CONST_UNSPECIFIED
    #undef    RBA_BSWSRV_STOP_SEC_CONST_UNSPECIFIED
    #define BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
    #include "Bsw_MemMap.h"

#elif defined RBA_BSWSRV_START_SEC_CODE
    #undef    RBA_BSWSRV_START_SEC_CODE
    #define  BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE
    #undef    RBA_BSWSRV_STOP_SEC_CODE
    #define  BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"

/* Code for simple lock, common lock and interrupt suspend */
#elif defined RBA_BSWSRV_START_SEC_CODE_FAST
    #undef    RBA_BSWSRV_START_SEC_CODE_FAST
    #define  BSW_START_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_FAST
    #undef    RBA_BSWSRV_STOP_SEC_CODE_FAST
    #define  BSW_STOP_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"

/* Code for nonest lock */
#elif defined RBA_BSWSRV_START_SEC_CODE_NONEST
    #undef    RBA_BSWSRV_START_SEC_CODE_NONEST
    #define  BSW_START_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_NONEST
    #undef    RBA_BSWSRV_STOP_SEC_CODE_NONEST
    #define  BSW_STOP_SEC_SPRAM_CODE
    #include "Bsw_MemMap.h"

/* Code for low priority lock and low priority interrupt suspend */
#elif defined RBA_BSWSRV_START_SEC_CODE_LOW_PRIO
    #undef    RBA_BSWSRV_START_SEC_CODE_LOW_PRIO
    #define  BSW_START_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
#elif defined RBA_BSWSRV_STOP_SEC_CODE_LOW_PRIO
    #undef    RBA_BSWSRV_STOP_SEC_CODE_LOW_PRIO
    #define  BSW_STOP_SEC_DEFAULT_CODE
    #include "Bsw_MemMap.h"
    
#else
    #error "unknown MemMap define"
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History___:
* 
* AR40.2.0.0; 1     14.02.2014 HCJ2FE
*   release 2/2014
* 
* AR40.2.0.0; 0     19.12.2013 HCJ2FE
*   release 2/2014
* 
* $
**********************************************************************************************************************
</BASDKey>*/

/*<BASDKey>
**********************************************************************************************************************
* End of header file: $Name______:rba_BswSrv_MemMap$
**********************************************************************************************************************
</BASDKey>*/
