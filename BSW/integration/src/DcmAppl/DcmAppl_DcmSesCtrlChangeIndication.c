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

#if (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
#include "rba_DcmPma_Prot.h"
#endif

/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmSesCtrlChangeIndication :-\n
 *  This API is invoked to as an indication to application, that value of active session control is changed.
 *  This change was either initiated by DiagnosticSessionControl command or S3Server timeout.
 *  The application needs to provide this function as a callback function.\n
 *  DCM provides only the prototype of this function.
 *
 * @param[in]           SesCtrlTypeOld : Former active session control type value
 * @param[in]           SesCtrlTypeNew : Newly set session control type value
 * @param[out]          None
 * @retval              None
 *
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmSesCtrlChangeIndication(
                                                        VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeOld,
                                                        VAR(Dcm_SesCtrlType,AUTOMATIC) SesCtrlTypeNew
                                                           )
{

#if (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)

        if((SesCtrlTypeNew == DCM_DEFAULT_SESSION) && (rba_DcmPma_PlantModeStatus_b != FALSE))
        {
            /*Exit Plant mode*/

            rba_DcmPma_PlantModeActivation (FALSE);
        }
#endif

    /* dummy code to remove compiler warning */
    (void)(SesCtrlTypeOld);

    /*
    #if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) NegResponseCode;
    #endif
    #if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)
    VAR(Dem_ReturnControlDTCStorageType, AUTOMATIC) RetVal;
    #endif
    */
    /*TESTCODE-START
	DcmTest_DcmAppl_DcmSesCtrlChangeIndication();
	TESTCODE-END*/

    /* Check for transition to default session */
    if(SesCtrlTypeNew != DCM_DEFAULT_SESSION)
    {
        /* Transition to non default session */

        /***************************
         * Response On Event (ROE)
         ***************************
         * The ROE implemented in DCM is of persistent type, which means that ROE events once
         * registered is active across different sessions and protocols until ECU is reset again.
         * Therefore, ROE event table and state machine should not be reset for any session transition.
         * If however, ROE event table is reset by the application then there could be incosistencies
         * in DCM ROE state machine */
    }
    else
    {
        /* Transition to default session*/

        /***************************
         * Response On Event (ROE)
         ***************************
         * The ROE implemented in DCM is of persistent type, which means that ROE events once
         * registered is active across different sessions and protocols until ECU is reset again.
         * Therefore, ROE event table and state machine should not be reset for any session transition.
         * If however, ROE event table is reset by the application then there could be incosistencies
         * in DCM ROE state machine */


        if(SesCtrlTypeOld != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])
        {
            /*****************************************
             * Read Data By Periodic Identifier (RDPI)
             *****************************************
             * Whenever a transition to default session happens, the periodic scheduler maintained in
             * the application needs to be cleared. Necessary reset of DCM RDPI state machine will
             * already be done before this session change indication.
             * Application needs to add the contents to reset the periodic Scheduler in this part */
        }

        /********************************************
        * Input Output Control By Identifier (IOCBI)
        ********************************************
        * Whenever a transition to default session happens, all Services that are not available in
        * default session must be reset. But in the case of IOCBI, there may be a use case, where
        * the transition to default session takes place due to an S3 timeout, while the control
        * still exists with the tester.In such a situation,it is the responsibility of the user,
        * to ensure that the control is transferred to the ECU, to reset the service.
        * The application can add the contents to reset the IOCBI Service and IOControls in this part.
        */

        /**********************
        * Routine Control (RC)
        ***********************
        * Whenever a transition to default session happens, all Services that are not available in
        * default session must be reset.The Routine control service is not mandatory to be present
        * in default session, as defined in Table 24, ISO 14229-1.
        * If the RC Service is configured only in the non default sessions, it has to be reset when
        * a transition from non default to default session happens. In this case, there may be a
        * use case, where, a routine is started, but a session transition to default session occurs
        * before the routine is stopped. Presently,there is no facility for tracking of the routine,
        * and it is the responsibility of the user to ensure that the Routine is stopped, before reset
        * of the service.
        * The application can add the contents to reset (stop) the RC controls in this part.
        */

        /*****************************************
        * Communication Control (CC)
        *****************************************
        * The settings in the communication control service is reset by calling the API
        * DcmAppl_DcmCommunicationControl() with parameters
        * ControlType = 0x00 (enableRxAndTx) and
        * CommunicationType = 0x03 (NM and Normal Communication Messages)
        */

        /****************************************************************************************/
        /*#if(DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)                               */
        /*Transition from non-default to default session                                        */
        /*if(SesCtrlTypeOld != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])             */
        /*{                                                                                     */
        /* Call API to reset Communication Control to Normal Communication and enable Tx/Rx     */
        /*    DcmAppl_DcmCommunicationControl(&NegResponseCode, 0x00, 0x03);                    */
        /*}                                                                                     */
        /*else                                                                                  */
        /*{                                                                                     */
        /* It is the responsibility of the user to enable Rx and Tx messages of NM and COM if   */
        /* CC service is also configured to work in default session                             */
        /*}                                                                                     */
        /*#endif                                                                                */
        /****************************************************************************************/

        /*****************************************
        * ControlDTCSetting (CDTCS)
        *****************************************
        * The settings in the Control DTC Setting service is reset by calling the DEM API
        * Dem_EnableDTCStorage() with parameters
        * DTCGroup = DEM_DTC_GROUP_ALL_DTCS and
        * DTCKind = DEM_DTC_KIND_ALL_DTCS
        */

       /******************************************************************************************/
        /*#if(DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)                                    */
        /* Transition from non-default to default session                                         */
        /*if(SesCtrlTypeOld != Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX])               */
        /*{                                                                                       */
        /* Call DEM API to reset CDTCS and enable DTC Storage                                     */
        /*    RetVal = Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);       */
        /* It is assumed that the RetVal returned from API Dem_EnableDTCSetting is always         */
        /* DEM_CONTROL_DTC_SETTING_OK. In case of other returns no action is performed            */
        /*    (void)(RetVal);                                                               */
        /*}                                                                                       */
        /*else                                                                                    */
        /*{                                                                                       */
        /* It is the responsibility of the user to enable the DTC storage if CDTC service         */
        /* is also configured to work in default session                                          */
        /*}                                                                                       */
        /*#endif                                                                                  */
        /******************************************************************************************/


        /*********************************************************************************************
        * ALL the above mentioned solutions for Implementation of ISO 14229-1 Specification regarding
        * session transition, are applicable only  to those services present in DcmDsp. If any code
        * external to DcmDsp are used, the user has to handle the requirements appropriately.
        **********************************************************************************************
        */
    }

    #if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROE_QUEUE_ENABLED != DCM_CFG_OFF))
    /* If reset the ROE scheduler is required then user has to uncomment the below code */
    /* Clear the ROE transmission queue */
    /* Dcm_DslDsd_ResetROEScheduler(); */
    #endif


    return;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"












