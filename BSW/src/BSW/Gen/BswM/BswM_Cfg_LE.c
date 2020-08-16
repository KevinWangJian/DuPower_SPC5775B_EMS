
/**********************************************************************************************************************
 *  Include files                                                                                                    
 **********************************************************************************************************************/

#include "BswM.h"
#include "BswM_Prv.h"

/**********************************************************************************************************************
 *  Definition of Global Functions                                                                                                    
 **********************************************************************************************************************/

/********************************  LogicalExpressionEvaluateFunctions  ***************************************/
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_DCM_DISABLE_RX_TX_NORMAL (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_DISABLE_RX_TX_NORMAL
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_DCM_DISABLE_RX_TX_NORMAL)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_DCM_DISABLE_RX_TX_NORMAL)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_DCM_ENABLE_RX_DISABLE_TX_NORMAL)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_TX_NORMAL (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_DCM_ENABLE_RX_TX_NORMAL
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_DCM_ENABLE_RX_TX_NORMAL)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_DCM_ENABLE_RX_TX_NORMAL)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_PostRun (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_PostRun
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_POSTRUN)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_POSTRUN)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_PrepShutdown (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_PrepShutdown
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_PREPSHUTDOWN)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_PREPSHUTDOWN)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_Run (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_Run
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_RUN)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_RUN)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_Shutdown (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_Shutdown
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_SHUTDOWN)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_SHUTDOWN)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_StartupOne (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_StartupOne
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_STARTUPONE)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_STARTUPONE)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

/*****************************************************************************************
 * Function name :   void BswM_Cfg_LE_BswM_LE_StartupTwo (boolean *validMode_pb,boolean *evalResult_pb)
 * Description   :   Evaluates the logical expression if the mode value is initialized and returns the result  
 * Parameter     :   *validMode_pb: evaluates if all the modes are valid and assigns true to this address if valid, 
 *evalResult_pb: result of the logical expression is copied to this address.
 * Return value  :   void
 * Remarks       :   
 *****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Cfg_LE_BswM_LE_StartupTwo
(
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) isValidMode_pb,
		P2VAR(boolean, AUTOMATIC, BSWM_APPL_DATA) hasLogExpRes_pb
)
{
	/* Initialize the pointers with default values */
	*isValidMode_pb = FALSE;
	*hasLogExpRes_pb = FALSE;

	if(FALSE != BSWMMODEVALUE_BSWM_LE_STARTUPTWO)
	{
		/* All the mode condition values are valid, assign TRUE to pointer */
		*isValidMode_pb = TRUE;
		if(FALSE != BSWMLOGEXP_BSWM_LE_STARTUPTWO)
		{
			/* Logical Expression evaluated to TRUE */
			*hasLogExpRes_pb = TRUE;
		}

	}

	return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/**********************************************************************************************************************
 *																										
 **********************************************************************************************************************/
