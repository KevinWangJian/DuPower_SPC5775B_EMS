

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_InvalidateSignalGroup
 Syntax           : uint8 Com_InvalidateSignalGroup(Com_SignalGroupIdType   SignalGroupId)
 Description      : Service for Invalidating the Signal Group
 Parameter        : SignalGroupId -> Id of the Signal Group
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
***************************************************************************************************/

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_START */
uint8 Com_InvalidateSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
/* FC_VariationPoint_END */
{

#ifdef COM_TxGrpSigInvalid
    Com_TxSigGrpConstPtrType     TxSigGrpConstPtr; /* Local pointer to Tx SignalGroup static configuration */
    Com_TxGrpSigConstPtrType     TxGrpSigConstPtr; /* Local pointer to Tx GroupSignal static configuration */
    Com_TxIpduRamPtrType         TxIpduRamPtr;     /* Local pointer to Tx IPdu        static configuration */
    VAR(uint16_least, AUTOMATIC) Index_ui;
    VAR(uint16_least, AUTOMATIC) No_Of_GrpSig_ui;  /* Local variable to store the no. of group signals for a signal group */
    VAR(uint8, AUTOMATIC)        Status;           /* return status */

    /* Start: Det */
    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_InvalidateSignalGroup, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_InvalidateSignalGroup,COM_E_PARAM)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    SignalGroupId = COM_GET_TXSIGNALGRP_ID(SignalGroupId);

    /* check if the IpduGroup is started
     * If the IPdu group is stopped the call to the function shall still update the values
     * in the COM internal buff-ers but the COM_SERVICE_NOT_AVAILABLE is returned */
   /* For Each Group signal of this Signal Group perform the Invalidate shadow signal */

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

    TxIpduRamPtr     = &COM_GET_TXPDURAM_S( TxSigGrpConstPtr->IpduRef );

    No_Of_GrpSig_ui  = (uint32)TxSigGrpConstPtr->FirstGrpSig_Index + (uint32)TxSigGrpConstPtr->No_Of_GrpSig;
    for(Index_ui=(uint16_least)TxSigGrpConstPtr->FirstGrpSig_Index;Index_ui<No_Of_GrpSig_ui;Index_ui++)
    {
        /*Note: Uint8[n] check is done in Com_InvalidateShadowSignal() so no need of Checking here*/
        /* Call to  Com_InternalInvalidateShadowSignal( ) has to be done to invalidate the signal, with the signal Id */

        /* if (TxGrpSigConstPtr->txGrpSigFields.GrpSigInvalid) */
        if (Com_GetValue(TXGRPSIG,_INVACTION,TxGrpSigConstPtr->txGrpSigFields))
        {
            Com_InternalInvalidateShadowSignal((Com_SignalIdType)Index_ui);
        }
        TxGrpSigConstPtr++;
    }

    /* Proceed only if Large Data tranmission is not in Progress */
    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
    {
        /* SWS_Com_00645: Com_SendSignalGroup() is performed internally. As per design Com_InternalSendSignalGroup()
         * is called. */
        Status = Com_InternalSendSignalGroup(SignalGroupId);
    }
    else
    {
        Status = COM_BUSY;
    }

    return (Status);
#else
    (void)SignalGroupId;
    return( COM_SERVICE_NOT_AVAILABLE );
#endif /* #ifdef COM_TxGrpSigInvalid */

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif


