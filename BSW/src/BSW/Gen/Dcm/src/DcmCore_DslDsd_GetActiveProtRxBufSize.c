

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetActiveProtocolRxBufferSize : API to get the Active protocol RX buffer size
 *
 * \param           rxBufferLength: Address of global variable in which the buffer size should be written.
 *
 *
 * \retval          E_OK: RX buffer size read successfully
 *                  E_NOT_OK: RX Buffer size not read, possibly because of no active protocol
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_GetActiveProtocolRxBufferSize(CONSTP2VAR(Dcm_MsgLenType, AUTOMATIC, DCM_APPL_DATA) rxBufferLength)
{
    VAR(Std_ReturnType,AUTOMATIC) dataReturnValue_u8;

    /* Default return value */
    dataReturnValue_u8= E_NOT_OK;

    /* If protocol is active then only DCM can give protocol id */

    if (Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
    {
        /* Update the Rx buffer size */
        *rxBufferLength = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_buffer_size_u32;
        dataReturnValue_u8 = E_OK;
    }
    return (dataReturnValue_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

