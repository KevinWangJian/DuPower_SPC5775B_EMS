/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmCore_Main_Inf.h"
 /*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
 /* Product lines/Customer Teams shall take responsibility to define their required ConfigSet here until BCT supports Post Build - Start */
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName1 = { 0 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName2 = { 1 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName3 = { 2 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName4 = { 3 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName5 = { 4 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName6 = { 5 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName7 = { 6 };
static CONST(Dcm_ConfigType,DCM_INTERN_CONST) Dcm_ConfigType_DataSetName8 = { 7 };
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_Init :-\n
 *  This API will be called before Dcm_Init() function and it is the responsibility of the
 *  customer / production team to initialize the Dcm_ActiveConfigSet_Ptr with the Dcm configuration
 *  set which is of interest to them, if this pointer is a null pointer a default Dcm configuration set
 *  will be chosen, with the current implementation it is Dcm_ConfigType_dataSetName1.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_Init (void)
{
    /* Initialize the configuration pointer with the necessary DcmConfigSet
       as shown below which is for the first DCM configuration set which
       holds an ConfigSetId of 0*/

	/*TESTCODE-START
	DcmTest_DcmAppl_Init();
	TESTCODE-END*/
	/* Dcm_ActiveConfigSet_Ptr = &Dcm_ConfigType_DataSetName1;*/

    return;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

