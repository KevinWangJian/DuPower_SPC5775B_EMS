

#ifndef DCMCORE_DSLDSD_INL_H
#define DCMCORE_DSLDSD_INL_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/


/**
 **************************************************************************************************
 * Dcm_StartS3MaxMonitoring :  Inline function to start P3 timer monitoring
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */


LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_StartS3MaxMonitoring (void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_StartS3MaxMonitoring (void)
{

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {
        /* if KWP is running protocol start P3 timer */

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, Dcm_DsldTimer_st.dataTimeoutP3max_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
    }
    else
    {
        /* if UDS is running protocol start S3 timer */

        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, DCM_CFG_S3MAX_TIME,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
    }
#else
    /* if UDS is running protocol start S3 timer */

    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, DCM_CFG_S3MAX_TIME,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
#endif
}

/**
 **************************************************************************************************
 * Dcm_StartProtocol : Function to call all RTE configured functions.
 *
 * \param           ProtocolID: protocol id
 *
 *
 * \retval          Std_ReturnType (E_OK,E_NOT_OK,DCM_E_PROTOCOL_NOT_ALLOWED)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
LOCAL_INLINE  FUNC(Std_ReturnType,DCM_CODE) Dcm_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) idxIndex_qu32;
#endif
    VAR(Std_ReturnType,AUTOMATIC) dataReturnType_u8;

    /* Call DcmAppl function to start the protocol */
    dataReturnType_u8 = DcmAppl_DcmStartProtocol(ProtocolID);

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    if(dataReturnType_u8 == E_OK)
    {
        /* Call all configured functions in RTE */
        for(idxIndex_qu32 = 0x00 ; idxIndex_qu32<Rte_NPorts_CallbackDCMRequestServices_R() ; idxIndex_qu32++)
        {
            dataReturnType_u8 =((Rte_Ports_CallbackDCMRequestServices_R())[idxIndex_qu32].Call_StartProtocol)(ProtocolID);

            if(Dcm_IsInfrastructureErrorPresent_b(dataReturnType_u8) != FALSE )
            {
                dataReturnType_u8 = DCM_INFRASTRUCTURE_ERROR;

            }
            else if((dataReturnType_u8 == DCM_E_PROTOCOL_NOT_ALLOWED) || (dataReturnType_u8 == E_NOT_OK))
            {
                /* Do nothing */
            }
            else
            {
                dataReturnType_u8 = E_OK;
            }
            if(dataReturnType_u8 != E_OK)
            {
                break;
            }
        }
    }
#endif
    return(dataReturnType_u8);
}

/**
 **************************************************************************************************
 * Dcm_StopProtocol : Function to call all RTE configured functions.
 *
 * \param           ProtocolID: protocol id
 *
 *
 * \retval          Std_ReturnType (ignored)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

LOCAL_INLINE  FUNC(Std_ReturnType,DCM_CODE) Dcm_StopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) idxIndex_qu32;
#endif
    VAR(Std_ReturnType,AUTOMATIC) dataReturnType_u8;

    /* Call DcmAppl function to stop the protocol */
    dataReturnType_u8 = DcmAppl_DcmStopProtocol(ProtocolID);

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_CALL_BACK_NUM_PORTS!=0))
    if(dataReturnType_u8 == E_OK)
    {
        /* Call all configured functions in RTE */
        for(idxIndex_qu32 =0x00 ; idxIndex_qu32<Rte_NPorts_CallbackDCMRequestServices_R() ; idxIndex_qu32++)
        {
            (void)((Rte_Ports_CallbackDCMRequestServices_R())[idxIndex_qu32].Call_StopProtocol)(ProtocolID);
        }
    }
#endif
    (void)dataReturnType_u8;
    return(E_OK);
}








/**
 **************************************************************************************************
 * Dcm_SupplierNotification : Function to call all RTE configured supplier indication functions.
 *
 * \param           SID: Service Id
 *                  RequestData: address of the request buffer
 *                  RequestLength: Length of request excluding Sid.
 *                  ReqType: Physical or functional request
 *                  DcmRxPduId: Rx Pdu number
 *                  ErrorCode: NRC code.
 *
 * \retval          Std_ReturnType (E_OK,E_NOT_OK,DCM_E_PENDING)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SupplierNotification(
        VAR(uint8,AUTOMATIC) SID,
        CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
        VAR(uint16,AUTOMATIC) RequestLength,
        VAR(uint8,AUTOMATIC) RequestType,
        VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        VAR(uint16,AUTOMATIC) SourceAddress,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SupplierNotification(
        VAR(uint8,AUTOMATIC) SID,
        CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
        VAR(uint16,AUTOMATIC) RequestLength,
        VAR(uint8,AUTOMATIC) RequestType,
        VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        VAR(uint16,AUTOMATIC) SourceAddress,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
)
{

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SUPPNOT_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) index_ui;
#endif
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegRespCode_u8; /* Local variable to get negative response code */
    VAR(boolean,     AUTOMATIC) requestNotaccepted_b;
    VAR(Std_ReturnType,AUTOMATIC) returnType;

    returnType=E_OK;
    requestNotaccepted_b=FALSE;
    dataNegRespCode_u8=0x00;
    *ErrorCode = 0;
    /* Call DcmAppl function to indicate new request */
    returnType = DcmAppl_DcmNotification(SID,RequestData,RequestLength,RequestType,DcmRxPduId,SourceAddress,&dataNegRespCode_u8);

    if(returnType == E_OK)
    {
        /* Do Nothing */
        dataNegRespCode_u8=0x00;
    }
    else if(returnType == DCM_E_REQUEST_NOT_ACCEPTED)
    {
        requestNotaccepted_b=TRUE;

    }
    else if(returnType == DCM_E_PENDING)
    {
        *ErrorCode = 0;/*Do nothing*/
    }
    else
    {
        if(dataNegRespCode_u8 == 0)
        {
            dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
        }
		else
		{
		         /*do Nothing*/
		}
    }

    if(returnType != DCM_E_PENDING)
    {
#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_SUPPNOT_NUM_PORTS !=0))
        /* Fill the default value */
        /* Call all configured functions in RTE */
        for(index_ui=0x00u; index_ui<DCM_CFG_SUPPNOT_NUM_PORTS; index_ui++)
        {

            returnType =(*Dcm_Rte_SupplierNotification_a[index_ui])(SID, RequestData, RequestLength, RequestType, SourceAddress,ErrorCode);
            /*If infrastructural Error is present*/
            if(Dcm_IsInfrastructureErrorPresent_b(returnType) != FALSE)
            {
                *ErrorCode = 0;
                if(dataNegRespCode_u8 == 0x00)
                {
                    dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                }

            }
            else if(returnType == E_OK)
            {
                *ErrorCode = 0;
            }
            else if(returnType == DCM_E_REQUEST_NOT_ACCEPTED && requestNotaccepted_b != TRUE)
            {
                requestNotaccepted_b=TRUE;
            }
            else
            {
                if((*ErrorCode == 0)&&(dataNegRespCode_u8 == 0x00))
                {
                    dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                }
                else if((*ErrorCode != 0)&&(dataNegRespCode_u8 == 0x00))
                {
                    dataNegRespCode_u8=*ErrorCode;
                }
                else
                {
                    /*do Nothing*/
                }
            }

        }


#endif

        if(requestNotaccepted_b != FALSE)
        {
            *ErrorCode = 0;
            returnType=DCM_E_REQUEST_NOT_ACCEPTED;
        }
        else if(dataNegRespCode_u8 !=0x00)
        {
            *ErrorCode=dataNegRespCode_u8;
            returnType = E_NOT_OK;
        }
        else
        {
            /*do Nothing*/
        }

    }

    return(returnType);

}
#endif



/**
 **************************************************************************************************
 * Dcm_ManufacturerNotification : Function to call all RTE configured manufacturer indication functions.
 *
 * \param           SID: Service Id
 *                  RequestData: address of the request buffer
 *                  RequestLength: Length of request excluding Sid.
 *                  ReqType: Physical or functional request
 *                  DcmRxPduId: Rx Pdu number
 *                  ErrorCode: NRC code.
 *
 * \retval          Std_ReturnType (E_OK, DCM_E_REQUEST_NOT_ACCEPTED,E_NOT_OK)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ManufacturerNotification(
        VAR(uint8,AUTOMATIC) SID,
        CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
        VAR(uint16,AUTOMATIC) RequestLength,
        VAR(uint8,AUTOMATIC) RequestType,
        VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        VAR(uint16,AUTOMATIC) SourceAddress,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ManufacturerNotification(
        VAR(uint8,AUTOMATIC) SID,
        CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
        VAR(uint16,AUTOMATIC) RequestLength,
        VAR(uint8,AUTOMATIC) RequestType,
        VAR(PduIdType,AUTOMATIC) DcmRxPduId,
        VAR(uint16,AUTOMATIC) SourceAddress,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
)
{

#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_MANUNOT_NUM_PORTS !=0))
    VAR(uint32_least,AUTOMATIC) index_ui;
#endif
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegRespCode_u8; /* Local variable to get negative response code */
    VAR(boolean,     AUTOMATIC) requestNotaccepted_b;
    VAR(Std_ReturnType,AUTOMATIC) returnType;

    returnType=E_OK;
    requestNotaccepted_b = FALSE;
    dataNegRespCode_u8=0x00;
    *ErrorCode = 0;
    /* Call DcmAppl function to indicate new request */
    returnType = DcmAppl_ManufacturerNotification(SID, RequestData, RequestLength, RequestType, DcmRxPduId,SourceAddress,&Dcm_DsldMsgContext_st,&dataNegRespCode_u8);

    if(returnType == E_OK)
    {
        /* Nothing to do as already Dcm_DsldMsgContext_st have been updated*/
        dataNegRespCode_u8=0x00;
    }
    else if(returnType == DCM_E_REQUEST_NOT_ACCEPTED)
    {
        requestNotaccepted_b=TRUE;

    }
    else
    {
        if(dataNegRespCode_u8 == 0)
        {
            dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
        }
		else
		{
		      /*do Nothing*/
		}
    }


#if((DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_MANUNOT_NUM_PORTS !=0))
    /* Fill the default value */
    /* Call all configured functions in RTE */
    for(index_ui=0x00u; index_ui<DCM_CFG_MANUNOT_NUM_PORTS; index_ui++)
    {

        returnType =(*Dcm_Rte_ManufacturerNotification_a[index_ui])(SID, RequestData, RequestLength, RequestType, SourceAddress,ErrorCode);
        /*If infrastructural Error is present*/
        if(Dcm_IsInfrastructureErrorPresent_b(returnType) != FALSE)
        {
            *ErrorCode = 0;
            if(dataNegRespCode_u8 == 0x00)
            {
                dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }

        }
        else if(returnType == E_OK)
        {
            *ErrorCode = 0;
        }
        else if(returnType == DCM_E_REQUEST_NOT_ACCEPTED && requestNotaccepted_b != TRUE)
        {
            requestNotaccepted_b=TRUE;
        }
        else
        {
            if((*ErrorCode == 0)&&(dataNegRespCode_u8 == 0x00))
            {
                dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
            }
            else if((*ErrorCode != 0)&&(dataNegRespCode_u8 == 0x00))
            {
                dataNegRespCode_u8=*ErrorCode;
            }
            else
            {
                /*do Nothing*/
            }
        }

    }


#endif

    if(requestNotaccepted_b != FALSE)
    {
        *ErrorCode = 0;
        returnType=DCM_E_REQUEST_NOT_ACCEPTED;
    }
    else if(dataNegRespCode_u8 !=0x00)
    {
        *ErrorCode=dataNegRespCode_u8;
        returnType = E_NOT_OK;
    }
    else
    {
        /*do Nothing*/
    }


    return(returnType);
}
#endif


/**
 **************************************************************************************************
 * Dcm_SesCtrlChangeIndication : Function to call all RTE configured functions.
 *
 * \param           dataSesCtrlTypeOld_u8: Old  session
 *                  dataSesCtrlTypeNew_u8: Changed session
 *
 * \retval          Std_ReturnType (but ignored)
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8,
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
);

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_SesCtrlChangeIndication(
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeOld_u8,
        VAR(Dcm_SesCtrlType,AUTOMATIC) dataSesCtrlTypeNew_u8
)
{

    /* Call DcmAppl function to indicate the session change */
    DcmAppl_DcmSesCtrlChangeIndication(dataSesCtrlTypeOld_u8,dataSesCtrlTypeNew_u8);
    return(E_OK);
}


/**
 **************************************************************************************************
 * Dcm_ConfirmationRespPend: Function to call all RTE configured functions on reception of a forced response pend.
 *
 * \param           status: ConfirmationStatus of the forced resp pend
 *
 * \retval          Std_ReturnType
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
);
LOCAL_INLINE FUNC(Std_ReturnType,DCM_CODE) Dcm_ConfirmationRespPend(
        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
)
{

    /* Call DcmAppl function for response pend */
    DcmAppl_ConfirmationRespPend(status);
    return(E_OK);
}

#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF))

/***************************************************************************************************************
 *
 * Dcm_MainFunctionsCheckUsedCore():Dcm_MainFunction and Co-Op scheduler should run in the same core
 * and Co-op scheduler should not interrupt Dcm_MainFunction.Otherwise there is a possibility  that service
 * calls processing done when Dcm_MainFunction is active leading to data inconsistencies.This function
 * checks the Current CoreID by calling the Appl function DcmAppl_Dcm_CheckUsedCore().If the current
 * CoreID returned from the Appl function does not match the already stored ID,it logs a DET error.
 *
 *
 * @param[in] None \n
 * @retval    None \n
 *
 *
 **************************************************************************************************************/

LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MainFunctionsCheckUsedCore(void);
LOCAL_INLINE FUNC(void, DCM_CODE) Dcm_MainFunctionsCheckUsedCore(void)
{
    static VAR(uint32, DCM_VAR) Dcm_Dsp_UsedCore_u32;

    uint32 Core_u32 = 0x1uL + DcmAppl_Dcm_CheckUsedCore();

    if (Dcm_Dsp_UsedCore_u32 != Core_u32)
    {
        if (Dcm_Dsp_UsedCore_u32 != 0uL)
        {
            /* different core detected. error reaction */
            DCM_DET_ERROR(DCM_CHKUSEDCOREMAIN_ID,DCM_E_PARALLEL_PROCESSING_ID)
        }
        else
        {
            /* not yet initialised: initialise used core number */
            Dcm_Dsp_UsedCore_u32 = Core_u32;
        }
    }
    else
    {
        /* fast path: function used on same core, nothing to do */
    }
}
#endif
#endif   /* for _DCMCORE_DSLDSD_INL_H */

