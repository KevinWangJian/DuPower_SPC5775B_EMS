

#include "TcpIp.h"
#ifdef TCPIP_CONFIGURED

#include "TcpIp_EthSM.h"
#include "TcpIp_Prv.h"

/********************************************************************************************************************/
/* TcpIp_RequestComMode()   - By this API service the TCP/IP stack is requested to change the TcpIp state of the    */
/*                       communication network identified by EthIf controller index.                                */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  CtrlIdx            - EthIf controller index to identify the communication network where the TcpIp state is      */
/*                       requested.                                                                                 */
/*  State              - Requested TcpIp state.                                                                     */
/*                                                                                                                  */
/* Return  :                                                                                                        */
/*      Std_ReturnType    E_OK: The request has been accepted.                                                      */
/*                        E_NOT_OK: The request was not successful,                                                 */
/*                                  e.g. no unique Ctrl specified via IpAddrId.                                     */
/*                                                                                                                  */
/********************************************************************************************************************/
#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestComMode(    VAR( uint8, AUTOMATIC )             CtrlIdx,
                                                            VAR( TcpIp_StateType, AUTOMATIC )   State )
{
    /* Report DET if TcpIp module is uninitialised */
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == TcpIp_InitFlag_b ), TCPIP_E_REQUEST_COM_MODE_API_ID, TCPIP_E_NOTINIT, E_NOT_OK )

    /* SWS_TCPIP_00089: If TCPIP_STATE_STARTUP or TCPIP_STATE_SHUTDOWN is requested as state the function   */
    /* TcpIp_RequestComMode() shall abort with E_NOT_OK and report TCPIP_E_INV_ARG to DET if DET is enabled.*/
    TCPIP_DET_REPORT_ERROR_RET_VALUE( ( ( TCPIP_STATE_STARTUP  == State ) || ( TCPIP_STATE_SHUTDOWN == State ) ),  \
                                      TCPIP_E_REQUEST_COM_MODE_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )
									  
	/* Report DET if CtrlIdx is equal to or greater than TCPIP_NUMETHIFCTRL. */
	TCPIP_DET_REPORT_ERROR_RET_VALUE( ( CtrlIdx >= TCPIP_NUMETHIFCTRL ),  \
									  TCPIP_E_REQUEST_COM_MODE_API_ID, TCPIP_E_INV_ARG, E_NOT_OK )

    /* Store the request */
    ( TcpIp_EthIfCtrlReqSt_aen[CtrlIdx] ) = State;

    return( E_OK );
}
#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/

