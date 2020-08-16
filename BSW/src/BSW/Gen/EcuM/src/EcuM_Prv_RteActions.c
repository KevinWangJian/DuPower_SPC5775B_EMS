



/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "EcuM_Cfg.h"                       //for the macro ECUM_CFG_ECUC_RB_RTE_IN_USE
#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
#include "EcuM.h"
#else
#include "Rte_EcuM.h"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE
#include "EcuM_Prv_RteActions.h"            // for function prototypes of EcuM_Prv_RteModeSwitch,EcuM_Prv_GetRteMode
/*************************************************************************************************
 Variables
*************************************************************************************************
*/

#if (ECUM_CFG_MODE_HANDLING == STD_ON)

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

/***********************************************************************************
 Function name  :   void EcuM_Prv_RteModeSwitch( Rte_ModeType_EcuM_Mode Mode)
 Description    :   Service to switch the RTE mode to the passed mode
 Parameter in   :   Mode
 Parameter out  :   none
 return         :   none
 ************************************************************************************/
FUNC(void, ECUM_CODE) EcuM_Prv_RteModeSwitch( VAR(Rte_ModeType_EcuM_Mode, AUTOMATIC) Mode)
{
    VAR(uint8, AUTOMATIC) mode;
    mode = Mode;

    /*Call to RTE generated function with prototype in Rte_EcuM.h if RTE environment present.*/
    /* Or if RTE environment is absent to the stub provided in EcuM.h */
    (void)Rte_Switch_currentMode_EcuM_Mode(mode);      //Return value not required
}

/***********************************************************************************
 Function name  :   uint8 EcuM_Prv_GetRteMode(void)
 Description    :   Returns the  current RTE mode
 Parameter in   :   None
 Parameter out  :   none
 return         :   uint8
 ************************************************************************************/
FUNC( uint8, ECUM_CODE ) EcuM_Prv_GetRteMode(void)
{
    VAR(uint8, AUTOMATIC) return_value;

    /*Call to RTE generated function with prototype in Rte_EcuM.h if RTE environment present.*/
    /* Or if RTE environment is absent to the stub provided in EcuM.h */
    return_value = Rte_Mode_currentMode_EcuM_Mode();

    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#else /*ECUM_CFG_MODE_HANDLING*/
   /*This fuction is not compiled because mode handling parameter is not configured or feature is disabled */
#endif /*ECUM_CFG_MODE_HANDLING*/

