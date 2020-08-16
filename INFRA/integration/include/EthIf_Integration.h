/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */
#ifndef NOT_READY_FOR_TESTING_OR_DEPLOYMENT
//#error The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#else
#warning The content of this file is a template which provides empty stubs. The content of this file must be completed by the integrator accordingly to project specific requirements
#endif /* NOT_READY_FOR_TESTING_OR_DEPLOYMENT */

#ifndef ETHIF_INTEGRATION_H
#define ETHIF_INTEGRATION_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "Eth_GeneralTypes.h"

/* According to the [SWS_TCPIP_00131] and the current source code version, EthIf_TxConfirmation
 * will not be called by EthDriver until EthTSyn module is integrated.
 * Therefore, by default, ETHIF_TXCONFIRMATION_USED is set to STD_OFF. In case EthIf_TxConfirmation is
 * used, please change this macro to STD_ON.
 */
#define ETHIF_TXCONFIRMATION_USED STD_OFF

/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */
#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

extern FUNC(Std_ReturnType, ETH_CODE) Eth_ControllerInit( VAR(uint8, AUTOMATIC) CtrlIdx_u8,
                                                          VAR(uint8, AUTOMATIC) CfgIdx_u8 );

extern FUNC(Std_ReturnType, ETHTRCV_CODE) EthTrcv_TransceiverInit( VAR(uint8, AUTOMATIC) TrcvIdx,
                                                                   VAR(uint8, AUTOMATIC) CfgIdx );


/* ETHIF231: Called asynchronously when mode has been read out. Triggered by previous Eth_SetControllerMode call.
   Can directly be called within the trigger functions. */
extern void EthIf_CtrlModeIndication(uint8 CtrlIdx, Eth_ModeType CtrlMode);

///** EthIf_TxConfirmation: Confirms frame transmission by the indexed controller
//    When using MCAL 4.0.3, please change this function name to EthIf_Cbk_TxConfirmation. */
//extern void EthIf_TxConfirmation( uint8 CtrlIdx, uint8 BufIdx);

/* The following extern functions' declaration are for supporting Ifx TC26x MCAL v4.0.3. Please uncomment them if you are using this target. */
//extern Std_ReturnType Eth_ReadMii(uint8 CtrlIdx,uint8 TrcvIdx,uint8 RegIdx, uint16* RegValPtr);
//extern Std_ReturnType Eth_WriteMii(uint8 CtrlIdx,uint8 TrcvIdx,uint8 RegIdx, uint16 RegVal);
//extern Std_ReturnType Eth_UpdatePhysAddrFilter( uint8 CtrlIdx, const uint8* PhysAddrPtr, Eth_FilterActionType Action );
//extern void EthIf_Cbk_RxIndication(uint8 CtrlIdx, Eth_DataType* DataPtr, uint16 LenByte);


#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif /* ETHIF_INTEGRATION_H */
