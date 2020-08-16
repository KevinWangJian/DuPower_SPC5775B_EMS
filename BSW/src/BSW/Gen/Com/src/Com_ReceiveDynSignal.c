

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ReceiveSignal
 Syntax           : uint8 Com_ReceiveDynSignal(Com_SignalIdType SignalId,void* SignalDataPtr,uint16 *LengthPtr)
 Description      : Service for receiving the signal, This API copies the data to the application buffer
 Parameter        : SignalId         -> Id of the Signal
                  : SignalDataPtr     -> Pointer to the address where signal data needs to be copied.
                  : LengthPtr        -> Pointer to length of the recieved length.
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_ReceiveDynSignal(        VAR(Com_SignalIdType, AUTOMATIC) SignalId,
                                              P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
                                            P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) LengthPtr      )
{
    Com_RxSigConstPtrType RxSigConstPtr; /* Local pointer holds the address of Rx signal static configuration */
    PduLengthType         StartByteNo;   /* Start Byte Number of Dynamic Signal */
    VAR(uint16,AUTOMATIC) DynLength;     /* Received Dynamic Signal Length  */
    VAR(Com_SigBuffIndexType, AUTOMATIC) SigBuff_Index;
    VAR(uint8, AUTOMATIC) Type;          /* Local variable holds the signal type */
    VAR(uint8, AUTOMATIC) Status;        /* Return status */

    Status = E_OK;

    /* Start: Det */

    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_ReceiveDynSignal, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalId >= COM_GET_NUM_RX_SIGNALS), COMServiceId_ReceiveDynSignal, COM_E_PARAM)

    COM_REPORT_ERROR1((SignalDataPtr == NULL_PTR), COMServiceId_ReceiveDynSignal, COM_E_PARAM_POINTER)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */
    SignalId = COM_GET_RXSIGNAL_ID(SignalId);

    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SignalId);
    SigBuff_Index = RxSigConstPtr->SigBuff_Index;
    /* Type = RxSigConstPtr->General.Type */
    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);

    /* Calculate Rx Dynamic Signal Start Position */
    StartByteNo = ( RxSigConstPtr->Bit_Pos >> 3u );

    /* Check if Dynamic Signal has been received with atleast one byte */
    if ( COM_GET_RXPDURAM_S(RxSigConstPtr->IpduRef).RxIPduLength > StartByteNo )
    {
        /* Calculate its received length */
        DynLength = (uint16)( COM_GET_RXPDURAM_S(RxSigConstPtr->IpduRef).RxIPduLength - StartByteNo );
    }
    else
    {
        /* Report it as 0, if it is not received yet */
        DynLength = 0u;
    }

    /*Check if Ipdu Group is started*/
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(!(COM_CheckRxIPduStatus(RxSigConstPtr->IpduRef)))
    {
        /*This part will be executed when IPDU Group is Stopped (old value will be returned)*/
        Status = COM_SERVICE_NOT_AVAILABLE;
    }

    /* If the requested length is less than the received length, then return E_NOT_OK */
    if(!(*LengthPtr < DynLength))
    {
        if(Type == COM_UINT8_DYN)
        {
            /*Copy each byte into the SignalDataPtr from Signal buffer  */
            /* The locks inside the function Com_ByteCopy() are removed.
             * Hence locks are used here
             */
            SchM_Enter_Com_RxSigDynBuff();
            * LengthPtr = DynLength;
            if(DynLength != 0)
            {
                /* MR12 RULE 11.5 VIOLATION: For SignalDataPtr is defined as void pointer in the AUTOSAR specification,
                   so suppressing warning "Cast from a pointer to void to a pointer to object" */
                Com_ByteCopy((uint8*)SignalDataPtr,&COM_GET_SIGTYPEUINT8DYN_BUFF(SigBuff_Index),DynLength);
            }
            SchM_Exit_Com_RxSigDynBuff();
        }

    }
    else
    {
        Status = E_NOT_OK;
    }


    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

