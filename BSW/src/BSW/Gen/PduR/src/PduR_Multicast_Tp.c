
/* Provide support for multicast transmission via CanTp */


#include "PduR_Prv.h"
#include "PduR_Mc.h"

/* Only enabled if Multicast to Tp support is enabled */
/* This macro has to be generated in PduR_Cfg.h if TP Multicast is required */
#if defined(PDUR_MULTICAST_TO_TP_SUPPORT) && (PDUR_MULTICAST_TO_TP_SUPPORT != 0)

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
/**
 **************************************************************************************************
 * PduR_MF_McTpTx_CanTp_TxConfirmation_Func
 *      Provide support for multicast transmission via CanTp
 *
 * \param           PduIdType id      :multicast ID to be transmitted.
 *                  Std_ReturnType result:
 *                           E_OK - after the complete Can TP data have successfully been transmitted
 *                     or    != E_OK if an error (e.g. timeout) has occurred.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_CanTp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) mcId,
                                                                  VAR(Std_ReturnType, AUTOMATIC) result)
{
    PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_CANTP, mcId, result );
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
 * PduR_MF_McTpTx_FrTp_TxConfirmation_Func
 *                  Provide support for multicast transmission via FrTp
 *
 *
 * \param           PduIdType mcId     :multicast ID that has been transmitted.
 *                  Std_ReturnType result:Result of the Tx confirmation.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_FrTp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) mcId,
                                                                 VAR(Std_ReturnType, AUTOMATIC) result)
{
    PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_FRTP, mcId, result );
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
 * PduR_MF_McTpTx_J1939Tp_TxConfirmation_Func
 *      Provide support for multicast transmission via J1939Tp
 *
 * \param           PduIdType id      :multicast ID to be transmitted.
 *                  Std_ReturnType result:
 *                           E_OK - after the complete Can TP data have successfully been transmitted
 *                     or    != E_OK if an error (e.g. timeout) has occurred.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_J1939Tp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) mcId,
                                                                  VAR(Std_ReturnType, AUTOMATIC) result)
{
    PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_J1939TP, mcId, result );
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
 * PduR_MF_McTpTx_LinTp_TxConfirmation_Func
 *                  Provide support for multicast transmission via LinTp
 *
 *
 * \param           PduIdType mcId     :multicast ID that has been transmitted.
 *                  Std_ReturnType nrt:Result of the Tx confirmation.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_LinTp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) mcId,
                                                                  VAR(Std_ReturnType, AUTOMATIC) result)
{
    PduR_MF_McTpTx_TxConfirmation( PDUR_LAYER_LINTP, mcId, result );
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

