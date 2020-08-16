

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "ComM_Priv.h"
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/*******************************************************************************
 * Function name    : ComM_DCM_ActiveDiagnostic
 * Syntax           : void ComM_DCM_ActiveDiagnostic( NetworkHandleType Channel )
 * Description      : Indication of active diagnostic by the DCM.
 * Parameters       : Channel -> Channel needed for Diagnostic communication
 * Return value     : void
 ******************************************************************************/
FUNC(void,COMM_CODE) ComM_DCM_ActiveDiagnostic(VAR(NetworkHandleType, AUTOMATIC) Channel)

{
    /* Local Variables Declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;

    /* Local variable initialization */
    channelRamPtr_ps = &ComM_ChannelStruct[Channel];

    /* DET check for communication manager initialization */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    /* check if ComM is initialized */
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized*/
       (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_DCM_ACTIVEDIAG,COMM_E_NOT_INITED);
        return;
    }
    #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */

    /* Update the diagnostic request state for channel to Active_Diagnostics */
    channelRamPtr_ps->DiagnosticRequestState_b = COMM_ACTIVE_DIAGNOSTICS;

}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

