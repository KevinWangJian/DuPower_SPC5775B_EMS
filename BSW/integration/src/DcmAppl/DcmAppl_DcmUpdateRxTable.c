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
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmUpdateRxTable:-\n
 * This API is called by Dcm_Init function during power on,so that the application can switch the rx table(assign rx table to Dcm_Dsld_rxtable_pca),
 *  if they want, based on the ecu type(master/slave).
 *
 *
 *
 *  @param[in]         None
 *
 *  @param[out]        None
 *
 *  @retval            None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmUpdateRxTable (void)
{
    /* User can switch the rx table, if they want, based on the ecu type(master/slave). */
    /* If the rx table is not switched by the application, it will take the rx table
     *  from the configuration*/
     /* Dummy code
	 if ( ECU_IS_MASTER )
	{
		Dcm_Dsld_rxtable_pca = Dcm_Dsld_Conf_cs.ptr_rxtable_pca;
	}
	else
	{
		Dcm_Dsld_rxtable_pca = Dcm_Dsld_rx_table_slave_acu8;
	}*/
	/*TESTCODE-START
	DcmTest_DcmAppl_DcmUpdateRxTable();
	TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
