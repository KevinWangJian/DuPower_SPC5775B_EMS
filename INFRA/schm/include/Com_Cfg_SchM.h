/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




#ifndef COM_CFG_SCHM_H
#define COM_CFG_SCHM_H

#include "SchM.h"
#include "SchM_Default.h"

#if ( COM_ECUC_RB_RTE_IN_USE == STD_ON )
/* If the RTE code generation is Involved please include the below file */
#include "SchM_Com.h"
#endif /* #if ( COM_ECUC_RB_RTE_IN_USE == STD_ON ) */

#define SchM_Enter_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Enter_Com_TxIpduProtArea_##FUNCTIONNAME()
#define SchM_Exit_Com_TxIpduProtArea(FUNCTIONNAME) SchM_Exit_Com_TxIpduProtArea_##FUNCTIONNAME()

#define SchM_Enter_Com_RxSigBuff(FUNCTIONNAME) SchM_Enter_Com_RxSigBuff_##FUNCTIONNAME()
#define SchM_Exit_Com_RxSigBuff(FUNCTIONNAME) SchM_Exit_Com_RxSigBuff_##FUNCTIONNAME()

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void);


LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void);

#ifdef COM_TX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxGrpSigBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxGrpSigBuffer(void);
#endif /* #ifdef COM_TX_SIGNALGROUP */

#ifdef COM_TXDOUBLEBUFFER
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxPduDoubleBuffer(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxPduDoubleBuffer(void);
#endif
#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigSecBuff (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigSecBuff (void);
#endif /* #ifdef COM_RX_SIGNALGROUP */

#if defined( COM_RX_SIGNALGROUP_ARRAY )
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpArrayBuff( void );
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpArrayBuff( void );
#endif /* #if defined( COM_RX_SIGNALGROUP_ARRAY ) */

#ifdef COM_RX_SIGNALGROUP
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigBuff(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigBuff (void);
#endif /* #ifdef COM_RX_SIGNALGROUP */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void);

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigDynBuff (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigDynBuff (void);
#endif /* #ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT */

#ifdef COM_RxSigUpdateTimeout
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigToTicks (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigToTicks (void);
#endif /* #ifdef COM_RxSigUpdateTimeout */

#ifdef COM_RxSigGrpUpdateTimeout
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpToTicks(void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpToTicks(void);
#endif /*#ifdef COM_RxSigGrpUpdateTimeout*/

#ifdef COM_SIGNALGATEWAY
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwQueueProtArea (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwQueueProtArea (void);

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwMcLockProtArea (void);
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwMcLockProtArea (void);

#endif /* #ifdef COM_SIGNALGATEWAY */
/* NOTE to Integrator : These below Exclusive areas can be defined depending on the project scenario,
 */

/* NOTE on Exclusive area SchM_Enter_Com_TxDoubleBufferNoNest:
 * If the project uses double buffer and alive counters(counters are updated in call-out functions
 * which is called in Com_SendIpdu()), then due to trigger transmit interrupt it is possible that
 * frame with same counter is transmitted twice.
 * To avoid this behaviour enable this exclusive area
 * IMP : If exclusive area SchM_Enter_Com_TxDoubleBufferNoNest is active, please ensure that exclusive area
 * SchM_Enter_Com_TxDoubleBufferRepErrNoNest is inactive.
 */
#ifdef COM_TXDOUBLEBUFFER
/* NOTE on exclusive area SchM_Enter_Com_TxPduDoubleBufferNoNest:
 * If double buffer is used and the mentioned behavior in the NOTE section of SchM_Enter_Com_TxDoubleBuffer is not
 * required, then please disable exclusive area SchM_Enter_Com_TxDoubleBuffer & enable SchM_Enter_Com_TxPduBufferNoNest
  * Write Operation:
 * 1) Com_MainfunctionTx
 * 2) Com_SendSignal
 * 3) Com_TriggerIpduSend
 * 4) Com_SendSignalGroup
 * Read Operation :
 * 1) Com_TriggerTransmit
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxPduDoubleBuffer(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxPduDoubleBuffer(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_TXDOUBLEBUFFER */

/* NOTE on Exclusive area INVALIDATESIGNAL:
Resource:
The signal value is being updated in the Tx Ipdu buffer
Scenario:
The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
If any other signal of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger- Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the stack
 * 3) Com_SendSignal
 *   a. If a signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_INVALIDATESIGNAL (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();

}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_INVALIDATESIGNAL (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();

}

/* NOTE on Exclusive area MAINFUNCTIONROUTESIGNALS:
Resource:
The Data from Tx shadow buffer is getting copied to the Tx Ipdu buffer
Scenario:
The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
If any other signal of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendSignal
 *   a. If a signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 * 2) Com_SigTxChangeMode
 *   a.The data of the Individual groups signals is fetched to evaluate TMS
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONROUTESIGNALS(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area MAINFUNCTIONTX:
Resource:
The set of Tx Timers and Tx flags are updated
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 2) Com_SigTxChangeMode
 *   a. a set of tx timers and Tx Flags are updated
 * 3) Com_TxConfirmation
 *   a. a set of tx timers and Tx Flags are updated
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_MAINFUNCTIONTX(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_MAINFUNCTIONTX(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area SENDDYNSIGNAL:
Resource:
The Data is updated into the Tx Ipdu buffer for a Dynamic signal
Scenario:
The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendSignal
 *   a. If a signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * 5)Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDDYNSIGNAL(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDDYNSIGNAL(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area SENDIPDU:
Resource:
a. The Data is updated into the Tx Ipdu buffer via Ipdu callout
b. Data is read by the other ComStack modules.
Scenario:
The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendSignal
 *   a. If a signal update is called for a signal from the same Ipdu
 * 3) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * 5)Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * Read Operation :
 * 6) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 * 7) Com_SigTxChangeMode
 *   a. The data of signal group buffers is read here
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_DATA(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_DATA(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area SENDIPDU_TXFLAGS:
Resource:
The set of Tx Timers and Tx flags are updated
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_MainfunctionTx
 *   a. The Tx Ipdu data and Tx Flags are updated
 * 2) Com_SigTxChangeMode
 *   a. a set of tx timers and Tx Flags are updated when called from Com_SendSignal/Com_SendSignalGroup
 * 3) Com_TxConfirmation
 *   a. a set of tx timers and Tx Flags are updated
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDIPDU_TXFLAGS(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area SENDSIGNAL:
Resource:
The Data is updated into the Tx Ipdu buffer for a signal
Scenario:
The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * 5)Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNAL(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNAL(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area SENDSIGNALGRP:
Resource:
The Data is updated into the Tx Ipdu buffer for a signal group from a shadow buffer
Scenario:
The below are the possibilites of shared resource access (Inconsistent Tx Ipdu data)
If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignal
 *   a. If a signal update is called for a signal  from the same Ipdu
 * 5) Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * 6) Com_SendSignalGroupArray:
 *   a. If a SignalGroup update is called for a SignalGroup from the same IPdu
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SENDSIGNALGRP(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SENDSIGNALGRP(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area TRIGGERTRANSMIT:
Resource:
The Data is being read from the Tx Ipdu buffer
Scenario:
The below are the possibilites of shared resource access (Inconsistent read of Tx Ipdu data)
If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 4) Com_SendSignal
 *   a. If a signal update is called for a signal  from the same Ipdu
 * 5)Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * 6) Com_SendSignalGroup
 *   a. If a signal group data update is called for a signal group  from the same Ipdu
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERTRANSMIT(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERTRANSMIT(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}

/* NOTE on Exclusive area TRIGGERIPDUSENDWITHMETADATA:
 * Resource:
 * The Data is updated into the Tx Ipdu buffer for a signal
 * Scenario:
 * The below are the possibilites of shared resource access(Inconsistent Tx Ipdu data)
 * If any other signal/Signal group of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1) Com_InvalidateSignal
 *   a. If a signal update is called for a signal from the same Ipdu with invalid value
 * 2) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update
 *      Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 3) Com_SendSignal
 *   a. If a signal update is called for a signal  from the same Ipdu
 * 4) Com_SendDynSignal
 *   a. If a dynamic signal update is called for a signal from the same Ipdu
 * 5) Com_SendSignalGroup
 *   a. If a signal group update is called for a signal group from the same Ipdu
 * 6) Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * 7) Com_TriggerIPDUSendWithMetaData:
 *      Tx IPdu Buffer can be updated in this API
 *
 * Read Operation :
 * 1) Com_TriggerTransmit
 *   a.The data of the Ipdu could be read here
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TRIGGERIPDUSENDWITHMETADATA(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}

/* NOTE on Exclusive area SIGTXCHANGEMODE:
Resource:
The set of Tx Timers and Tx flags are updated + Read operation of Tx group signal shadow buffers
Scenario:
The below are the possibilites of shared resource access(Inconsistent read of Tx Ipdu data)
If any other signal of a this particular Ipdu is being updated by any of the below API's
 * Write Operation:
 * 1)Com_MainfunctionRouteSignals:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu, this could result in inconsistent read here
 * 2)Com_SendSignalGroup:
 *   a. If a signal group data update is triggered for a signal group from the same Ipdu
 * 3) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 4) Com_MainfunctionTx
 *   a. a set of tx timers and Tx Flags are updated
 * 5) Com_TxConfirmation
 *   a. a set of tx timers and Tx Flags are updated
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_SIGTXCHANGEMODE(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_SIGTXCHANGEMODE(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area TXCONFIRMATION:
Resource:
The set of Tx Timers and Tx flags are updated
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_SendIPdu
 *   a. If the transmission is initiated for the Ipdu from Com_MainfunctionTx/Event trigger then Callout can update Tx Ipdu
 *   b. The Tx Ipdu data can be updated by other modules along the communication stack
 * 2) Com_SigTxChangeMode
 *   a. a set of tx timers and Tx Flags are updated when called from Com_SendSignal/Com_SendSignalGroup
 * 3) Com_MainfunctionTx
 *   a. a set of tx timers and Tx Flags are updated
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxIpduProtArea_TXCONFIRMATION(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxIpduProtArea_TXCONFIRMATION(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}

#ifdef COM_TX_SIGNALGROUP
/* NOTE on Exclusive area of GRPSIGNALBUFFER: Can be generated
 * The Group signal shadow buffer is read/written as below
 * Write Operation:
 * 1) Com_InvalidateShadowSignal
 * 2) Com_UpdateShadowSignal
 * Read Operation :
 * 1) Com_SendSignalGroup
 * 2) Com_IPduGroupControl to change the state of a Ipdu group to Started.
 */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_TxGrpSigBuffer(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_TxGrpSigBuffer(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_TX_SIGNALGROUP */

/* NOTE on Exclusive area of RXIPDUBUFFER:
 * The Rx Ipdu buffer is written in Com_RxIndication
 * The same data buffer is Read Com_MainFunctionRx for deferred processing

 * If there is a possibility that the above API can interrupt each other for Rx IPdu buffer access,
 * then this exclusive area needs to be enabled in Com_Cfg_SchM.h file.
 */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxPduBuffer(void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxPduBuffer(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}




#ifdef COM_RxSigUpdateTimeout
/* NOTE on Exclusive area of SigUpdatebitTimer: Can be generated
 * The Group signal shadow buffer is read/written as below
 * Write Operation:
 * 1) Com_ReceptionDMControl
 * 2) Com_MainFunctionRx
 * 3) Com_RxIndication
 * Read Operation :
 * 1) Com_ReceptionDMControl
 * 2) Com_MainFunctionRx
 * 3) Com_RxIndication
 * */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigToTicks (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigToTicks (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_RxSigUpdateTimeout */

#ifdef COM_RxSigGrpUpdateTimeout
/* NOTE on Exclusive area of SigUpdatebitTimer: Can be generated
 * The Group signal shadow buffer is read/written as below
 * Write Operation:
 * 1) Com_ReceptionDMControl
 * 2) Com_MainFunctionRx
 * 3) Com_RxIndication
 * Read Operation :
 * 1) Com_ReceptionDMControl
 * 2) Com_MainFunctionRx
 * 3) Com_RxIndication
 * */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpToTicks (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpToTicks (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /*#ifdef COM_RxSigGrpUpdateTimeout */

/* NOTE on Exclusive area MAINFUNCTIONRX:
Resource:
1. The Rx signal buffer is updated here in case of timeout
2. Rx Timeout operation consistency is to be ensured using this lock
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_RxIndication
 *   a. Signal data is updated per signal into the signal buffers
 *   b. Signal data is updated for float signals
 *    Read Operation:
 * 2) Com_ReceiveSignal
 *   a. Signal data is read from the signal buffers.
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_MAINFUNCTIONRX (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_MAINFUNCTIONRX (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area RXINDICATION:
Resource:
1. The Rx signal buffer is updated here in case of Ipdu reception
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_MainfunctionRx
 *   a. Signal data is updated per signal after timeout
 *    Read Operation:
 * 2) Com_ReceiveSignal
 *   a. Signal data is read from the signal buffers.
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RXINDICATION (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RXINDICATION (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
/* NOTE on Exclusive area RECEIVESIGNAL :
Resource:
1. The Rx signal buffer is read here after Ipdu reception
Scenario:
The below are the possibilites of shared resource access
 * Write Operation:
 * 1) Com_MainfunctionRx
 *   a. Signal data is updated per signal after timeout
 * 2) Com_RxIndication
 *   a. Signal data is updated per signal into the signal buffers
 *   b. Signal data is updated for float signals
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigBuff_RECEIVESIGNAL (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigBuff_RECEIVESIGNAL  (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
/* NOTE on Exclusive area of Rx Signal buffer: Can be generated
 * The application buffer is updated here, and the protection is intended for Rx dynamic signal buffer
 * Write Operation:
 * 1) Com_RxIndication
 * Read Operation :
 * 1) Com_ReceiveSignal
 */
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigDynBuff (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigDynBuff (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT */

#ifdef COM_RX_SIGNALGROUP
/* NOTE on Exclusive area of RXGRPSIGNALSECONDBUFFER: Can be generated
 * The Group signal shadow buffer is read/written as below
 * Write Operation:
 * 1) Com_RxIndication
 * 2) Com_MainfunctionRx
 * Read Operation :
 * 1) Com_ReceiveSignalGroup
 * 2) Com_PackRxSignalGrpGwBufferData - SignalGroup Gateway from Rx to Tx GroupSignal shadow buffer
 */
/* As the lock is around the loop for all the group signals the Interrupt locking time can vary*/
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigSecBuff (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigSecBuff(void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_RX_SIGNALGROUP */

#if defined( COM_RX_SIGNALGROUP_ARRAY )
/* NOTE on Exclusive area of RX SignalGroup Array Buffer: Can be generated
 * The SignalGroup Array buffer is read/written as below
 * Write Operation:
 *  1) Com_RxIndication
 *  2) Com_MainFunctionRx
 * Read Operation :
 *  1) Com_ReceiveSignalGroupArray
 */
/* As the lock is around the loop for all the group signals the Interrupt locking time can vary*/
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGrpArrayBuff( void )
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGrpArrayBuff( void )
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #if defined( COM_RX_SIGNALGROUP_ARRAY ) */

#ifdef COM_RX_SIGNALGROUP
/* NOTE on Exclusive area of Rx group Signal buffer: Can be generated
 * The application buffer is updated here, and the protection is intended for Rx group signal buffer
 * Write Operation:
 * 1) Com_ReceiveSignalGroup
 * Read Operation :
 * 1) Com_ReceiveShadowSignal
 *
 * Use case scenario: Use below locks only in case, Com_ReceiveSignalGroup & Com_ReceiveShadowSignal api's
 * can interrupt each other. If Com_ReceiveSignalGroup & Com_ReceiveShadowSignal api's are called from the
 * same task context, then below locks can be left empty.
 */
/* As the lock is around the loop for all the group signals the Interrupt locking time can vary*/
LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxGrpSigBuff (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();
}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxGrpSigBuff (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();
}
#endif /* #ifdef COM_RX_SIGNALGROUP */

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
/* NOTE on Exclusive area updating the queue:
 * If there is a possibility that this below APIs can interrupt Com_mainfucntionTx
 * The TXTIMEOUT timer is read/written as below
 * Write Operation:
 * 1) Com_MainfunctionRx
 * 2) Com_RxIndication (Multiple Calls of Com_RxIndication)
 * Read Operation :
 * 1) Com_MainfunctionRouteSignals
 */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwQueueProtArea (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();

}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwQueueProtArea (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();

}

/* NOTE on Exclusive area when accessing the Gw buffers of signals -- This is a multicore lock:
 * If there is a possibility that in an explicit multi-core scenario
 * Write Operation:
 * 1) Com_RxIndication (Multiple Calls of Com_RxIndication) in one core
 * Read Operation :
 * 1) Com_MainfunctionRouteSignals in other core
 * There can be inconsitencies in the data access, hence this area is enabled
 */

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Enter_Com_RxSigGwMcLockProtArea (void)
{
    /*The integrator shall place his code here which would disable/lock the interrupt*/
    SCHM_ENTER_DEFAULT();

}

LOCAL_INLINE FUNC(void, COM_CODE) SchM_Exit_Com_RxSigGwMcLockProtArea (void)
{
    /*The integrator shall place his code here which would enable/unlock the interrupt*/
    SCHM_EXIT_DEFAULT();

}
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)*/

#endif /* COM_CFG_SCHM_H */

