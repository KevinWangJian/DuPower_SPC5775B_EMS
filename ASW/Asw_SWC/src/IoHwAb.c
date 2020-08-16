/* *****************************************************************************
 * BEGIN: Banner
 *-----------------------------------------------------------------------------
 *                                 ETAS GmbH
 *                      D-70469 Stuttgart, Borsigstr. 14
 *-----------------------------------------------------------------------------
 *    Administrative Information (automatically filled in by ISOLAR)         
 *-----------------------------------------------------------------------------
 * Name: Code-Frame generation feature
 * Description:
 * Version: 9.3
 *-----------------------------------------------------------------------------
 * END: Banner
 ******************************************************************************

 * Project : ETAS_AR_BSW3P1
 * Component: /IoHwAb/IoHwAb
 * Runnable : All Runnables in SwComponent
 *****************************************************************************
 * Tool Version: ISOLAR-A V 9.0
 * Author: Zhang Yawei
 * Date : ������ ���� 29 13:58:13 2018
 ****************************************************************************/

#include "IoAb.h"
#include "Rte_IoHwAb.h"

/*PROTECTED REGION ID(FileHeaderUserDefinedIncludes :IoHwAb_MainFunction) ENABLED START */
/* Start of user defined includes  - Do not remove this comment */
/* End of user defined includes - Do not remove this comment */
/*PROTECTED REGION END */
#include "fan.h"
#include "relay.h"

/*PROTECTED REGION ID(FileHeaderUserDefinedConstants :IoHwAb_MainFunction) ENABLED START */
/* Start of user defined constant definitions - Do not remove this comment */
/* End of user defined constant definitions - Do not remove this comment */
/*PROTECTED REGION END */

/*PROTECTED REGION ID(FileHeaderUserDefinedVariables :IoHwAb_MainFunction) ENABLED START */
/* Start of user variable defintions - Do not remove this comment  */
/* End of user variable defintions - Do not remove this comment  */
/*PROTECTED REGION END */
#define IoHwAb_START_SEC_CODE                   
#include "IoHwAb_MemMap.h"
FUNC (void, IoHwAb_CODE) IoHwAb_MainFunction // return value & FctID 
(
		void
)
{
	{
		Cdd_MainFunction();
	}
    {
    	Get_BottomInterface_Mainfunc();
    }
}

#define IoHwAb_STOP_SEC_CODE                       
#include "IoHwAb_MemMap.h"
