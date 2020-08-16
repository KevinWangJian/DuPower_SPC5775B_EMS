
/* Support for PduR_Dcmxxx()  */


#include "PduR_Prv.h"
/* FC_FileVariationPoint_START */

/*
 * khs4kor: RTA-BSW Release: As multicast gateway involving any UpTp module is not supported as of now(due to patenting issue), this API will never be called.
 * So this entire file is not required for RTA-BSW release. Whenever, this API is supported, that time we can remove the RTA-BSW tags.
 */

/* Only enabled if Multicast from Tp support is enabled */
/* This macro has to be generated in PduR_Cfg.h if TP Multicast is required */
#if defined(PDUR_MULTICAST_FROM_TP_SUPPORT) && (PDUR_MULTICAST_FROM_TP_SUPPORT != 0)

#if defined(PDUR_DCM_SUPPORT) && (PDUR_DCM_SUPPORT != 0)
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)

#include "PduR_Dcm.h"
#include "PduR_Gw.h"
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_Dcm_Transmit
 *      Handle "transmission" to DCM (TP) as part of a combined gateway and reception operation
 *
 * \param           PduIdType dcmId      :ID of I-PDU to be transmitted.
 *                  PduR_TxPduInfoPtr src:Pointer to pointer to PduInfoStructure containing SDU data pointer and
 *                                        SDU length of a transmit buffer.
 *
 * \retval          E_OK, E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_Dcm_Transmit_Func( VAR(PduIdType, AUTOMATIC) dcmId,
                                                             P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) src)
{
    P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA )   dcmBuf;
/*  Start: MEDC17 Core Adaptation, added following declaration  */
    VAR(uint16_least, AUTOMATIC)  i;
/* END: MEDC17 Core Adaptation, added following declaration  */

    Std_ReturnType rtn;

    /* Request a buffer for reception */
    BufReq_ReturnType req = BUFREQ_E_NOT_OK; /* Dcm_ProvideRxBuffer(dcmId, src->SduLength, &dcmBuf); */
    if (BUFREQ_OK == req)
    {
        /* Buffer request succeeded: perform the data copy */

        /* START: MEDC17 Core Adaptation as memcpy( ) is present in string.h file which we are not including  */

        for(i = 0 ; i < src->SduLength ; i++)
        {
            dcmBuf->SduDataPtr[i] = src->SduDataPtr[i];
        }

        /* END: MEDC17 Core Adaptation as memcpy( ) is present in string.h file which we are not including  */

        /* Inform the higher layer that reception has completed */
        Dcm_TpRxIndication(dcmId, E_OK);

        rtn = E_OK;
    }
    else
    {
        /* Buffer request failed */
        rtn = E_NOT_OK;
    }

    return rtn;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_TPGATEWAY_SUPPORT */
#endif /* PDUR_DCM_SUPPORT */

#endif /* PDUR_MULTICAST_FROM_TP_SUPPORT */
/* FC_FileVariationPoint_END */
