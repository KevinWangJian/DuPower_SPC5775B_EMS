
#include "EthIf.h"

#ifdef ETHIF_CONFIGURED

#include "Eth.h"
#include "EthIf_Prv.h"

#if( ETHIF_ENABLE_GLOBAL_TIME_SUPPORT == STD_ON )

/**
 ***************************************************************************************************
 * \moduledescription
 * EthIf_GetCurrentTime:
 * Returns a time value out of the HW registers according to the capability of the HW.
 * Is the HW resolution is lower than the Eth_TimeStampType resolution resp. range,
 * than an the remaining bits will be filled with 0.
 *
 * \par Service ID 0x22, Synchronous, Non-reentrant for the same CtrlIdx, reentrant for different CtrlIdx
 *
 * Parameter In:
 * \param CtrlIdx            Index of EthIf controller.
 *
 * Parameters Out:
 * \param timeQualPtr       quality of HW time stamp, e.g. based on current drift.
 * \param timeStampPtr      current time stamp
 *
 * \return                  Std_ReturnType {E_OK: success; E_NOT_OK: failed to get the current time}
 *
 ***************************************************************************************************
 */
#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_GetCurrentTime(    VAR  ( uint8,                   AUTOMATIC)             CtrlIdx,
                                                              P2VAR( Eth_TimeStampQualType,   AUTOMATIC, AUTOMATIC ) timeQualPtr,
                                                              P2VAR( Eth_TimeStampType,       AUTOMATIC, AUTOMATIC ) timeStampPtr )
{
    /* Local variables declaration */
    uint8                  lEthCtrlIdx_u8;
    Std_ReturnType         lStdRetVal_en;

    /* DET Checks */
    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VALUE( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_GETCURRENTTIME, ETHIF_E_NOT_INITIALIZED, E_NOT_OK )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VALUE( ( ( CtrlIdx + 1 ) > ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ), ETHIF_SID_ETHIF_GETCURRENTTIME,   \
    		                         ETHIF_E_INV_CTRL_IDX, E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( NULL_PTR == timeQualPtr, ETHIF_SID_ETHIF_GETCURRENTTIME, ETHIF_E_PARAM_POINTER, E_NOT_OK )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VALUE( NULL_PTR == timeStampPtr, ETHIF_SID_ETHIF_GETCURRENTTIME, ETHIF_E_PARAM_POINTER, E_NOT_OK )

	/* Read out CtrlIdx from configuration */
	lEthCtrlIdx_u8  = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    lStdRetVal_en      = Eth_GetCurrentTime( lEthCtrlIdx_u8,
    		                                 timeQualPtr,
    		                                 timeStampPtr);

    return (lStdRetVal_en);

}

/**
 ***************************************************************************************************
 * \module description
 * Activates egress time stamping on a dedicated message object. Some HW does store once the egress
 * time stamp marker and some HW needs it always before transmission. There will be no "disable"
 * functionality, due to the fact, that the message type is always "time stamped" by network design.
 *
 * \par Service ID 0x23, Synchronous, Non Reentrant
 *
 * Parameter In:
 * CtrlIdx              Index of EthIf controller.
 * BufIdx               Index of the message buffer, where Application expects egress time stamping
 *
 * Parameters Inout:    None
 *
 * Parameters Out:      None
 *
 * Return value         None
 *
 * \return  None
 *
 ***************************************************************************************************
 */
FUNC( void, RBA_ETHIF_CODE ) EthIf_EnableEgressTimeStamp(   VAR( uint8,     AUTOMATIC )             CtrlIdx,
                                                            VAR( uint8,     AUTOMATIC )             BufIdx  )
{
    /* Local variables declaration */
    uint8        lEthCtrlIdx_u8;

    /* Initialise local variables */
    lEthCtrlIdx_u8  = 0xFF;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_ENABLE_EGRESS_TIMESTAMP, ETHIF_E_NOT_INITIALIZED )

	/* Report DET : Development Error: CtrlIdx is not valid */
	ETHIF_REPORT_ERROR_RET_VOID( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),     \
								   ETHIF_SID_ETHIF_ENABLE_EGRESS_TIMESTAMP,                                         \
								   ETHIF_E_INV_CTRL_IDX )

	/* Read out CtrlIdx from configuration */
	lEthCtrlIdx_u8  = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

	Eth_EnableEgressTimeStamp( lEthCtrlIdx_u8, BufIdx );

}

/**
 ***************************************************************************************************
 * \module description
 * Reads back the egress time stamp on a dedicated message object.
 * Note: EthIf_GetEgressTimeStamp() API must be called by the UL of EthIf
 *       within the UL_TxConfirmation() callback function
 *
 * \par Service ID 0x24, Synchronous, Non Reentrant
 * Parameter In:
 * CtrlIdx              Index of EthIf controller.
 * BufIdx               Index of the message buffer, where Application expects egress time stamping
 *
 * Parameters Inout:     None
 *
 * Parameters Out:
 * timeQualPtr          quality of HW time stamp, e.g. based on current drift
 * timeStampPtr         current time stamp
 *
 * Return value         None
 *
 * \return  None
 *
 ***************************************************************************************************
 */

FUNC( void, RBA_ETHIF_CODE ) EthIf_GetEgressTimeStamp(   VAR( uint8,     AUTOMATIC )                            CtrlIdx,
                                                         VAR( uint8,     AUTOMATIC )                            BufIdx,
                                                         P2VAR( Eth_TimeStampQualType,  AUTOMATIC, AUTOMATIC )  timeQualPtr,
                                                         P2VAR( Eth_TimeStampType,  AUTOMATIC, AUTOMATIC )      timeStampPtr )
{
    /* Local variables declaration */
    uint8     lEthCtrlIdx_u8;

    /* Initialise local variables */
    lEthCtrlIdx_u8  = 0xFF;

    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETHIF_GET_EGRESS_TIMESTAMP, ETHIF_E_NOT_INITIALIZED )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VOID( ( ( CtrlIdx + 1 ) > EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ),     \
                                   ETHIF_SID_ETHIF_GET_EGRESS_TIMESTAMP,                                            \
                                   ETHIF_E_INV_CTRL_IDX )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID( ( NULL_PTR == timeQualPtr ), ETHIF_SID_ETHIF_GET_EGRESS_TIMESTAMP, ETHIF_E_PARAM_POINTER )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID( ( NULL_PTR == timeStampPtr ), ETHIF_SID_ETHIF_GET_EGRESS_TIMESTAMP, ETHIF_E_PARAM_POINTER )

    /* Read out CtrlIdx from configuration */
    lEthCtrlIdx_u8  = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

    Eth_GetEgressTimeStamp( lEthCtrlIdx_u8,
                            BufIdx,
                            timeQualPtr,
                            timeStampPtr );

}

/**
 ***************************************************************************************************
 * \moduledescription
 * EthIf_GetIngressTimeStamp:
 * Reads back the ingress time stamp on a dedicated message object.
 * It must be called within the RxIndication() function.
 *
 * \par Service ID 0x25, Synchronous, Non-reentrant for the same CtrlIdx, reentrant for different CtrlIdx
 *
 * Parameter In:
 * \param CtrlIdx           Index of EthIf controller.
 * \param DataPtr           Pointer to the message buffer, where Application expects ingress time stamping
 *
 * Parameters Out:
 * \param timeQualPtr       quality of HW time stamp, e.g. based on current drift.
 * \param timeStampPtr      current time stamp
 *
 * \return                  none
 *
 ***************************************************************************************************
 */

FUNC(void, RBA_ETHIF_CODE) EthIf_GetIngressTimeStamp( VAR   ( uint8,                            AUTOMATIC ) CtrlIdx,
                                                      P2VAR ( Eth_DataType,          AUTOMATIC, AUTOMATIC ) DataPtr,
                                                      P2VAR ( Eth_TimeStampQualType, AUTOMATIC, AUTOMATIC ) timeQualPtr,
                                                      P2VAR ( Eth_TimeStampType,     AUTOMATIC, AUTOMATIC ) timeStampPtr )
{
    /* Local variables declaration */
    uint8       lEthCtrlIdx_u8;

    /* DET Checks */
    /* Report DET : Development Error: Module not initialised */
    ETHIF_REPORT_ERROR_RET_VOID( ( EthIf_InitStatus_en != ETHCTRL_STATE_INIT ), ETHIF_SID_ETH_GETINGRESSTIMESTAMP, ETHIF_E_NOT_INITIALIZED )

    /* Report DET : Development Error: CtrlIdx is not valid */
    ETHIF_REPORT_ERROR_RET_VOID( (   ( CtrlIdx + 1 ) > ( EthIf_CfgPtr_pco->EthIfCtrlState_pst->nrOfEthIfCtrl_cu8 ) ), ETHIF_SID_ETH_GETINGRESSTIMESTAMP, ETHIF_E_INV_CTRL_IDX )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID(NULL_PTR == DataPtr, ETHIF_SID_ETH_GETINGRESSTIMESTAMP, ETHIF_E_PARAM_POINTER )

    /* Report DET : Development Error: Pointer is invalid */
    ETHIF_REPORT_ERROR_RET_VOID(NULL_PTR == timeQualPtr, ETHIF_SID_ETH_GETINGRESSTIMESTAMP, ETHIF_E_PARAM_POINTER )

    /* check if provided pointer is a NULL pointer*/
    ETHIF_REPORT_ERROR_RET_VOID(NULL_PTR == timeStampPtr, ETHIF_SID_ETH_GETINGRESSTIMESTAMP, ETHIF_E_PARAM_POINTER)

	/* Read out CtrlIdx from configuration */
	lEthCtrlIdx_u8  = ( EthIf_CfgPtr_pco->EthIfControllerConfig_pst[CtrlIdx].idxEthCtrRef_cu8 );

	Eth_GetIngressTimeStamp(lEthCtrlIdx_u8,
			                DataPtr,
			                timeQualPtr,
			                timeStampPtr);

    return;
}

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif  /* #if(ETHIF_ENABLE_GLOBAL_TIME_SUPPORT == STD_ON) */
#endif /* ETHIF_CONFIGURED */


/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
