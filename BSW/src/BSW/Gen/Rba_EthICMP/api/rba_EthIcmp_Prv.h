

#ifndef RBA_ETHICMP_PRV_H
#define RBA_ETHICMP_PRV_H

#if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) )

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

/*********************************************/
/* ICMP Protocol                             */
/*********************************************/

/* All ICMP packets will have an 8-byte header and variable-sized data section. The first 4 bytes of the header */
/* will be consistent. The first byte is for the ICMP type. The second byte is for the ICMP code. The third and */
/* fourth bytes are a checksum of the entire ICMP message. The contents of the remaining 4 bytes of the header  */
/* will vary based on the ICMP type and code. */
#define RBA_ETHICMP_PRV_HDR_LENGTH_PARTIAL              4U

/* Size of ICMP header */
#define RBA_ETHICMP_PRV_HDR_LENGTH                      8U

/* ICMP header offsets */
#define RBA_ETHICMP_PRV_TYPE_OFFSET                     0U
#define RBA_ETHICMP_PRV_CODE_OFFSET                     1U
#define RBA_ETHICMP_PRV_CHKSUM_OFFSET                   2U
#define RBA_ETHICMP_PRV_IDENTIFIER_OFFSET               4U
#define RBA_ETHICMP_PRV_SEQNUM_OFFSET                   6U

#define RBA_ETHICMP_PRV_IDENTIFIER_FIELD                0xCAFEU

/*********************************************/
/* Development Error Codes for DET Support   */
/*********************************************/
/*
 * RBA_ETHICMP: DET Error ID'd*
 * RBA_ETHICMP_E_NOTINIT: API service used without rba_EthIcmp_Init module initialisation
 * */
#define RBA_ETHICMP_E_NOTINIT                        TCPIP_E_NOTINIT

/*
 * RBA_ETHICMP: DET Error ID'd*
 * RBA_ETHICMP_E_INV_ARG: Invalid argument received
 * */
#define RBA_ETHICMP_E_INV_ARG                        TCPIP_E_INV_ARG

/*
 * RBA_ETHICMP: DET Error ID'd*
 * RBA_ETHICMP_E_NULL_PTR: API service called with NULL pointer as an argument
 * */
#define RBA_ETHICMP_E_NULL_PTR                      TCPIP_E_NULL_PTR

/*
 * RBA_ETHICMP: DET Error ID'd*
 * RBA_ETHICMP_E_INIT_FAILED: API service called without TcpIp module initialization
 * */
#define RBA_ETHICMP_E_INIT_FAILED                   TCPIP_E_INIT_FAILED

/*********************************************/
/* DET macros                                */
/*********************************************/

/* API IDs of rba_EthIcmp */

/* Indicates that Api Id passed in the call of Det_ReportError */

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthIcmp_Init()  */
#define RBA_ETHICMP_E_INIT_API_ID                                 (0x01U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthIcmp_Transmit()  */
#define RBA_ETHICMP_E_TRANSMIT_API_ID                             (0x02U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthIcmp_RxIndication() */
#define RBA_ETHICMP_E_RX_INDICATION_API_ID                        (0x03U)


#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )

    /* DET For functions with return type as 'void' */
    #define RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                      \
            if( CONDITION )                                                                                   \
            {                                                                                                 \
                (void)Det_ReportError( (RBA_ETHICMP_MODULE_ID), (RBA_ETHICMP_INSTANCE_ID), (API), (ERROR) );  \
                return;                                                                                       \
            }

    /* For functions with a return value */
    #define RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )                           \
            if( CONDITION )                                                                                   \
            {                                                                                                 \
                (void)Det_ReportError( (RBA_ETHICMP_MODULE_ID), (RBA_ETHICMP_INSTANCE_ID), (API), (ERROR) );  \
                return ( RETVAL );                                                                            \
            }

#else
    #define RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( CONDITION, API, ERROR )

    #define RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )

#endif /* #if TCPIP_DEV_ERROR_DETECT */


/********************************************************************************************************************/
/****************************            Variables                          *****************************************/
/********************************************************************************************************************/

#define RBA_ETHICMP_START_SEC_VAR_INIT_8
#include "rba_EthIcmp_MemMap.h"
extern VAR( boolean,     RBA_ETHICMP_CODE )   rba_EthIcmp_InitFlag_b;
#define RBA_ETHICMP_STOP_SEC_VAR_INIT_8
#include "rba_EthIcmp_MemMap.h"

#define RBA_ETHICMP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"
extern P2CONST( rba_EthIcmp_Config_to, AUTOMATIC, AUTOMATIC )      rba_EthIcmp_CurrConfig_pco;
#define RBA_ETHICMP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"

#endif /* #if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHICMP_PRV_H */

