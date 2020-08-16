/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_P3TimeoutIndication :-\n
 *  This API is used to indicate to the application that P3 timeout in DSL has occured.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_P3TimeoutIndication(void)
{
	/* FC_VariationPoint_START */
    /*VAR(Std_ReturnType,AUTOMATIC) ret_val; */

    /* USDT Response Parameter */
    /*VAR(PduInfoType,AUTOMATIC) Data_usdt; */

    /* Initializing to E_OK */
    /*ret_val = E_OK; */
    /* ProtocolID to find the active protocol */
    /*Dcm_ProtocolType protocol_id_u8;*/

    /* Fill Response of 0x60 for ReturnToNormalMode */

    /* Get Active Protocol */
    /*Dcm_GetActiveProtocol(&protocol_id_u8);*/

    /* The ret_val indicates if the transmission succeeded E_OK or E_NOT_OK */
    /* Depending on the ret_val the user can decide to retry or ignore */
	/* FC_VariationPoint_END */
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

