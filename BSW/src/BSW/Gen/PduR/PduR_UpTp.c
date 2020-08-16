


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/



#include "PduR_Prv.h"
#include "PduR_Cfg.h"
/* Appropriate header files are included to declare the prototypes
 */
#include "PduR_UpTp.h"

#if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)
#include "PduR_CanTp.h"
#endif
#if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)
#include "PduR_FrTp.h"
#endif

#include "PduR_Dcm.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_DcmTransmit
 *      This function is called by the DCM to request a transmission.
 *
 * \param           PduIdType id: ID of DCM I-PDU to be transmitted.
 *                  P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr: Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer
 *
 * \retval          E_OK Transmit request has been accepted
 *                  E_NOT_OK Transmit request has not been accepted
 *
 * \seealso         PDUR202, PDUR206
 * \usedresources
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return (PduR_rDcmTransmit( (id) , (ptr)));
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"



/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_DcmCancelTransmit
 *      This function is called by the DCM to request a transmission cancellation
 *
 * \param           PduIdType id: ID of DCM I-PDU to be cancelled the transmission.
 *
 * \retval          E_OK Cancellation request has been accepted
 *                  E_NOT_OK Cancellation request has not been accepted
 *
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmCancelTransmit( VAR(PduIdType,AUTOMATIC) id)
{
    VAR( Std_ReturnType, AUTOMATIC) r;

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
    /* DET Checks if DET is enabled */
    PDUR_CHECK_STATE_RET(PDUR_SID_DCMCNCLTX, E_NOT_OK)

    if ( ( id >= PDUR_NR_VALID_DCM_IDS ) || ( PduR_iDcmCancelTransmitFunc(id) == NULL_PTR ) )
    {
        PDUR_REPORT_ERROR(PDUR_SID_DCMCNCLTX, PDUR_E_PDU_ID_INVALID);
        return  E_NOT_OK;
    }
#endif /* PDUR_DEV_ERROR_DETECT */

    r = PduR_iDcmCancelTransmitFunc(id)( PduR_iDcmCancelTransmitID(id) );

    return r;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"



/* ------------------------------------------------------------------------ */
/* Begin section for code */

#if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0)
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_DcmChangeParameter
 *      This service primitive is used to request the change of the value of the PDUR_STMIN parameter.
 *
 * \param           parameter: Specify the parameter to which the value has to be changed (BS or STmin).
 *                  PduId: Gives the ID of the connection (message) for whose channel the change shall be done.
 *                  value: The new value of the parameter
 *
 * \retval          None
 *
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmChangeParameter(VAR(PduIdType, AUTOMATIC) id,
                                                    VAR(TPParameterType, AUTOMATIC) parameter,
                                                    VAR(uint16, AUTOMATIC) value)
{

#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)

    PDUR_CONFIG_SINGLE_TPTX_LO(ChangeParameter)(id,parameter,value);

#else
    Std_ReturnType          retval;
    PduR_LowerTpModuleName  lowerModule;
    PduIdType               lowerId;

    retval = E_NOT_OK;
    /*Checks the validity of id : if valid, calls the lower Tp module(CANTP/FRTP) change parameter function */
    if ( id < PDUR_NR_VALID_DCM_IDS  )
    {
        /*Gets the lower Tp module name */
        lowerModule = PDUR_CHANGEPARAM_SUPPORT[id].loTp;
        /*Gets the id of I_PDU,corresponding to the lower module */
        lowerId     = PDUR_CHANGEPARAM_SUPPORT[id].loId;

        if(lowerModule == (PduR_LowerTpModuleName)PDUR_CANTP)
        {
            #if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = CanTp_ChangeParameter(lowerId,parameter,value);

            #endif

        }
        else if(lowerModule == (PduR_LowerTpModuleName)PDUR_FRTP)
        {
            #if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = FrTp_ChangeParameter(lowerId,parameter,value);

            #endif

        }
        else
        {
            /*To remove Misra Warning*/
        }
    }
    else
    {
        /*Report error in case of invalid Id  */
        /* If the PDU identifier is not within the specified range then PDUR_E_PDU_ID_INVALID is reported via DET.*/
        PDUR_REPORT_ERROR(PDUR_SID_DCMCHANGEPARAMETER, PDUR_E_PDU_ID_INVALID);
    }

    return retval;
#endif /*PDUR_ZERO_COST_OPERATION*/
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif  /* #if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0) */


/* ------------------------------------------------------------------------ */
/* Begin section for code */
#if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0)
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_DcmReadParameter
 *      This service primitive is used to request the change of the value of the PDUR_STMIN parameter.
 *
 * \param           parameter: Specify the parameter to which the value has to be read (BS or STmin).
 *                  id: Gives the ID of the connection (message).
 *                  value: Pointer where the parameter value is stored
 *
 * \retval          E_OK    : The STmin value is updated in the buffer provided.
                    E_NOT_OK: Invalid request / NULL_PTR passed etc
 *
 **************************************************************************************************
 */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmReadParameter( VAR(PduIdType, AUTOMATIC) id,
                                                          VAR(TPParameterType, AUTOMATIC) parameter,
                                                          P2VAR(uint16, AUTOMATIC, PDUR_APPL_DATA) value)
{
#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION!= STD_OFF)

    return (PDUR_CONFIG_SINGLE_TPTX_LO(ReadParameter)(id,parameter,value));

#else
    Std_ReturnType          retval;
    PduR_LowerTpModuleName  lowerModule;
    PduIdType               lowerId;

    retval      = E_NOT_OK;
    /*Checks the validity of id And value is not null  */
    if ( (id < PDUR_NR_VALID_DCM_IDS ) && (value != NULL_PTR))
    {
        /* Gets the low layer name(cantp/frtp) and Id,then calls the lower Tp layer read parameter function */
        lowerModule = PDUR_CHANGEPARAM_SUPPORT[id].loTp;
        lowerId     = PDUR_CHANGEPARAM_SUPPORT[id].loId;


        if(lowerModule == (PduR_LowerTpModuleName)PDUR_CANTP)
        {
            #if defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_CANTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = CanTp_ReadParameter(lowerId,parameter,value);

            #endif

        }
        else if(lowerModule == (PduR_LowerTpModuleName)PDUR_FRTP)
        {
            #if defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT) && (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT != 0)

                retval = FrTp_ReadParameter(lowerId,parameter,value);

            #endif

        }
        else
        {
            /*To remove Misra Warning*/
        }
    }
    else
    {
        /*Report error in case of invalid Id and value is a null pointer */
        /* If the PDU identifier is not within the specified range then PDUR_E_PDU_ID_INVALID is reported via DET.*/
        #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
        if(id >= PDUR_NR_VALID_DCM_IDS)
        {
            PDUR_REPORT_ERROR(PDUR_SID_DCMREADPARAMETER, PDUR_E_PDU_ID_INVALID);
        }
        if(value == NULL_PTR)
        {
            PDUR_REPORT_ERROR(PDUR_SID_DCMREADPARAMETER, PDUR_E_NULL_POINTER);
        }
        #endif

    }
    return retval;
#endif /*PDUR_ZERO_COST_OPERATION*/



}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif  /* #if defined(PDUR_CHANGE_PARAMETER_SUPPORT) && (PDUR_CHANGE_PARAMETER_SUPPORT != 0) */

