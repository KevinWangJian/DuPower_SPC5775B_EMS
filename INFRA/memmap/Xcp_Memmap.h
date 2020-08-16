/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



 /*
 * The symbol 'START_WITH_IF' is undefined.
 *
 * Thus, the preprocessor continues searching for defined symbols
 * This first #ifdef makes integration of delivered parts of MemMap.h
 * easier because every supplier starts with #elif
 */


#if defined (START_WITH_IF)

/***************************************************************************************************
* Variables - uninitialized RAM
***************************************************************************************************/
/***************************************************************************************************
* Start up measurement shall be supported:  Variables shall not be deleted/initialized during SW reset.
* Start up measurement not needed:          Variables can be located in normal cleared RAM
***************************************************************************************************/
/* XCP uninitialized DAQ normal (PD) RAM: 32 bit values */
#elif defined (XCP_START_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32)
  #define  BSW_START_SEC_DEFAULT_RESET_SAFE_RAM0_32
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32
#elif defined (XCP_STOP_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32)
  #define  BSW_STOP_SEC_DEFAULT_RESET_SAFE_RAM0_32
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32

/* XCP uninitialized DAQ ED RAM: 32 bit values */
#elif defined (XCP_START_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32)
  #pragma  section ".bss.edram_protected" awB
  /* #error "ED RAM is only available in product line MDG1" */
  #undef   XCP_START_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32
#elif defined (XCP_STOP_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32)
  #pragma  section
  /* #error "ED RAM is only available in product line MDG1" */
  #undef   XCP_STOP_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32

/* XCP Uninitialized RAM: unspecified size */
#elif defined (XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
    #define  BSW_START_SEC_DEFAULT_RESET_SAFE_RAM0_UNSPECIFIED
    #include"Bsw_MemMap.h"
  #undef   XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#elif defined (XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
    #define  BSW_STOP_SEC_DEFAULT_RESET_SAFE_RAM0_UNSPECIFIED
    #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED

/***************************************************************************************************
* Variables - cleared RAM (set to zero)
***************************************************************************************************/
/* XCP Cleared RAM: unspecified size */
#elif defined (XCP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #define  BSW_START_SEC_VAR_CLEARED_UNSPECIFIED
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined (XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #define  BSW_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED

/***************************************************************************************************
* Special Purpose RAM
***************************************************************************************************/

/* only needed, if CAN Direct Transmit is switched on, place on peripheral core for fast access */
#elif defined (XCP_START_PERIPHERAL_CORE_FAST_RAM)
  #define  BSW_START_SEC_VAR_INIT_32
  #include "Bsw_MemMap.h"
  #undef   XCP_START_PERIPHERAL_CORE_FAST_RAM
#elif defined (XCP_STOP_PERIPHERAL_CORE_FAST_RAM)
  #define  BSW_STOP_SEC_VAR_INIT_32
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_PERIPHERAL_CORE_FAST_RAM

/***************************************************************************************************
* Constants
***************************************************************************************************/
/* XCP Const (ROM): 32 bit values */
#elif defined (XCP_START_SEC_CONST_32)
  #define  BSW_START_SEC_DEFAULT_CONST_32
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CONST_32
#elif defined (XCP_STOP_SEC_CONST_32)
  #define  BSW_STOP_SEC_DEFAULT_CONST_32
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CONST_32

/* XCP Const (ROM): unspecified size */
#elif defined (XCP_START_SEC_CONST_UNSPECIFIED)
  #define  BSW_START_SEC_DEFAULT_CONST_UNSPECIFIED
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CONST_UNSPECIFIED
#elif defined (XCP_STOP_SEC_CONST_UNSPECIFIED)
  #define  BSW_STOP_SEC_DEFAULT_CONST_UNSPECIFIED
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CONST_UNSPECIFIED

/***************************************************************************************************
* Code
***************************************************************************************************/
/* XCP Code */
#elif defined (XCP_START_SEC_CODE)
  #define  BSW_START_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CODE
#elif defined (XCP_STOP_SEC_CODE)
  #define  BSW_STOP_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CODE

/* XCP Fast Code */
/* Functions which are called from Xcp_<module>TxConfirmation (transmission of sampled data) */
#elif defined (XCP_START_SEC_CODE_FAST)
  #define  BSW_START_SEC_SPRAM_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CODE_FAST
#elif defined (XCP_STOP_SEC_CODE_FAST)
  #define  BSW_STOP_SEC_SPRAM_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CODE_FAST

/* XCP Event Channel Code */
/* Functions which are called from Xcp_EventChannel() (sampling of measurement data) */
#elif defined (XCP_START_SEC_CODE_EVENTCHANNEL)
  #define  BSW_START_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CODE_EVENTCHANNEL
#elif defined (XCP_STOP_SEC_CODE_EVENTCHANNEL)
  #define  BSW_STOP_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CODE_EVENTCHANNEL

/* XCP Callout Code: Appl Functions */
/* Functions which are called from Xcp and are implemented outside of Xcp component */
#elif defined (XCP_START_SEC_CALLOUT_CODE)
  #define  BSW_START_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_START_SEC_CALLOUT_CODE
#elif defined (XCP_STOP_SEC_CALLOUT_CODE)
  #define  BSW_STOP_SEC_DEFAULT_CODE
  #include "Bsw_MemMap.h"
  #undef   XCP_STOP_SEC_CALLOUT_CODE


#else
  #error "Xcp_MemMap.h: No valid section define found"

/* The following lines need to be exactly in this order to make cchecker (v2.2.0) recognize the MISRA-Violation-comment for QAC_883 (DIR 4.10, RULE 1.2)*/
/* MR12 DIR 4.10, 1.2 VIOLATION: Multiple includes of this file are necessary as the memory mapping is done this way */
#endif /* START_WITH_IF */
/* MR12 DIR 4.10, 1.2 VIOLATION: Multiple includes of this file are necessary as the memory mapping is done this way */
