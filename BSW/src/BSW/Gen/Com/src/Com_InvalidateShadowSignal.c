

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_InvalidateShadowSignal
 Syntax           : void Com_InvalidateShadowSignal(Com_SignalIdType   SignalId)
 Description      : Service for Invalidating the shadow signal (i.e Group signal)
 Parameter        : SignalId
 Return value     : None
***************************************************************************************************/
#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_InvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId)
{
#ifdef COM_TxGrpSigInvalid

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_InvalidateShadowSignal, COM_E_UNINIT)
    COM_REPORT_ERROR((SignalId >= COM_GET_NUM_TX_GRPSIGNALS), COMServiceId_InvalidateShadowSignal, COM_E_PARAM)
    /* End: Det */

    /* Convert external HandleId to internal HandleId for Tx Group Signal
       IMP : before accessing the tables, it is required to converth the IDs
       For pre-compile , conversion is not required. Access Macro will return the same ID, which is passed to it */
    SignalId = COM_GET_TXGRPSIGNAL_ID(SignalId);

    Com_InternalInvalidateShadowSignal(SignalId);

#else
    (void)SignalId;
#endif /* #ifdef COM_TxGrpSigInvalid */
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_TxGrpSigInvalid
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/***************************************************************************************************
 Function name    : Com_InternalInvalidateShadowSignal
 Syntax           : void Com_InternalInvalidateShadowSignal(Com_SignalIdType   SignalId)
 Description      : Service for Invalidating the shadow signal (i.e Group signal)
                    This is an internal function to invalidate a group signal
                    This function doesnt do DET checks, these checks are done in the API itself.
 Parameter        : SignalId -> Internal Id of the group signal. (Relevant for post-build case)
 Return value     : None
***************************************************************************************************/
FUNC(void, COM_CODE) Com_InternalInvalidateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId)
{
    Com_TxGrpSigConstPtrType                   TxGrpSigConstPtr;
    VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC)  GrpSigBuff_Index;
    /* TxGrpSig_NewVal datatype is uint32, as currently maximum 32bits are supported for Invalid value */
    VAR(uint32, AUTOMATIC)                     TxGrpSig_NewVal;
    VAR(uint8, AUTOMATIC)                      ConstByteValue_u8;

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);

    ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
    SchM_Enter_Com_TxGrpSigBuffer();

    /* As per the SWS Page 42/43 (V2.1), we are supposed to call the Com_SendSignal( ) i.e Com_UpdateShadowSignal */
    /* As per COM286:By this call no send request shall be initiated */
    /*As per COM288, there is statement as "For processing, a Data invalid value must have been configured" */
    /* Pack the data invalid value into the shadow buffer for normal signals*/
    /*no call to UpdateShadow Signal is required for the same*/
    /* if(TxGrpSigConstPtr->txGrpSigFields.DataInvalidType)) */
    if(Com_GetValue(TXGRPSIG,_INVACTION,ConstByteValue_u8))
    {

        TxGrpSig_NewVal  = TxGrpSigConstPtr->DataInvalid_Val;
        GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;
        /* switch((TxGrpSigConstPtr->txGrpSigFields.Type) >> 1) */
        switch(Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8) >> 1u)
        {

            case 0x00u:
            /* UINT08 signal */
                COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index)  = (uint8)TxGrpSig_NewVal;
                break;

            case 0x01u:
            /* UINT16 signal */
                COM_GET_TXGRPSIGTYPEU16_BUFF(GrpSigBuff_Index)  = (uint16)TxGrpSig_NewVal;
                break;

            /* UINT32 signal */
            case 0x02u:
            /* FC_VariationPoint_START */
            /* FLOAT32 signal */
            case (COM_FLOAT32 >> 1u):
            /* FC_VariationPoint_END */
                COM_GET_TXGRPSIGTYPEU32_BUFF(GrpSigBuff_Index)  = (uint32)TxGrpSig_NewVal;
                break;

#ifdef COM_TXGRPSIG_INT64
            /* UINT64 signal */
            case 0x08u:
                COM_GET_TXGRPSIGTYPEU64_BUFF(GrpSigBuff_Index)  = (uint64)TxGrpSig_NewVal;
            break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */

            case 0x03u:
            /*Boolean Signal*/
                COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index)  = (uint8)TxGrpSig_NewVal;
                break;

            case 0x04u:
            /* UINT8_N signal */
                Com_ByteCopyInit(&COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index),
                                 TxGrpSig_NewVal,(uint32)TxGrpSigConstPtr->BitSize);
                break;
            default:
                /**
                 * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal types are
                 * allowed to be configured, hence default case is intentionally left empty.
                 */
                break;

       }
    }
    SchM_Exit_Com_TxGrpSigBuffer();

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_TxGrpSigInvalid */

#endif /* #ifdef COM_TX_SIGNALGROUP */

