


#ifndef RBA_ETHARP_PRV_H
#define RBA_ETHARP_PRV_H

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/

#if (TCPIP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

#include "TcpIp_Prv.h"

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

/*********************************************/
/* ARP Protocol                              */
/*********************************************/

/* ARP message types (opcodes) */
#define RBA_ETHARP_ETH_HW_TYPE                  1U
#define RBA_ETHARP_ARP_REQUEST                  1U
#define RBA_ETHARP_ARP_REPLY                    2U
#define RBA_ETHARP_HDR_LENGTH                   28U

/*********************************************/
/* ARP code - Define Value                   */
/*********************************************/

/* Type of ARP Frame to send */
#define RBA_ETHARP_ARP_REQUEST_FRAME            0U
#define RBA_ETHARP_ARP_REPLY_FRAME              1U

/*********************************************/
/* Development Error Codes for DET Support   */
/*********************************************/
/*
 * RBA_ETHARP: DET Error ID'd*
 * RBA_ETHARP_E_NOTINIT: API service used without rba_EthArp_Init module initialisation
 * */
#define RBA_ETHARP_E_NOTINIT                        TCPIP_E_NOTINIT

/*
 * RBA_ETHARP: DET Error ID'd*
 * RBA_ETHARP_E_INV_ARG: Invalid argument received
 * */
#define RBA_ETHARP_E_INV_ARG                        TCPIP_E_INV_ARG

/*
 * RBA_ETHARP: DET Error ID'd*
 * RBA_ETHARP_E_INV_ARG: Invalid ARP table entry
 * */
#define RBA_ETHARP_E_INV_TBL_ENTRY                  TCPIP_E_INV_ARG


/*
 * RBA_ETHARP: DET Error ID'd*
 * RBA_ETHARP_E_NULL_PTR: API service called with NULL pointer as an argument
 * */
#define RBA_ETHARP_E_NULL_PTR                       TCPIP_E_NULL_PTR

/*
 * RBA_ETHARP: DET Error ID'd*
 * RBA_ETHARP_E_INIT_FAILED: API service called without TcpIp module initialization
 * */
#define RBA_ETHARP_E_INIT_FAILED                    TCPIP_E_INIT_FAILED

/*********************************************/
/* DET macros                                */
/*********************************************/

/* API IDs of rba_EthArp */

/* Indicates the Api Id passed in the call of Det_ReportError */

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_Init()  */
#define RBA_ETHARP_E_INIT_API_ID                                  (0x01U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_UpdateArpTable()  */
#define RBA_ETHARP_E_UPDATE_ARPTABLE_API_ID                       (0x02U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_ReadArpTable()  */
#define RBA_ETHARP_E_READ_ARPTABLE_API_ID                         (0x03U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_CleanArpTable() */
#define RBA_ETHARP_E_CLEAN_ARPTABLE_API_ID                        (0x04U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_GetDestEthAddr() */
#define RBA_ETHARP_E_GET_DEST_ETHADDR_API_ID                      (0x05U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_IpConflictDetection() */
#define RBA_ETHARP_E_IPCONFLICT_DETECTION_API_ID                  (0x06U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_RxIndication()  */
#define RBA_ETHARP_E_RXINDICATION_API_ID                          (0x07U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_SendArpFrame()  */
#define RBA_ETHARP_E_SEND_ARPFRAME_API_ID                         (0x08U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_SendArpGratuitousFrame()  */
#define RBA_ETHARP_E_SEND_ARP_GRATUITOUSFRAME_API_ID              (0x09U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_MainFunction()  */
#define RBA_ETHARP_E_MAIN_FUNCTION_API_ID                         (0x0AU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_UpdateArpTableEntry()  */
#define RBA_ETHARP_E_UPDATE_ARPTABLE_ENTRY_API_ID                 (0x0BU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_CleanArpTableEntry()  */
#define RBA_ETHARP_E_CLEAN_ARPTABLE_ENTRY_API_ID                  (0x0CU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_GetEthAddrInTableEntry()  */
#define RBA_ETHARP_E_GET_ETHADDR_IN_TABLEENTRY_API_ID             (0x0DU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_GetUsableEntry()  */
#define RBA_ETHARP_E_GET_USABLE_ENTRY_API_ID                      (0x0EU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_CheckIpTableEntry()  */
#define RBA_ETHARP_E_CHECK_IPTABLE_ENTRY_API_ID                   (0x0FU)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_ChkMACAddrMatch()  */
#define RBA_ETHARP_E_CHK_MACADDRMATCH_API_ID                      (0x10U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_BufferToHeader()  */
#define RBA_ETHARP_E_BUFFER_TO_HEADER_API_ID                      (0x11U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_HeaderToBuffer()  */
#define RBA_ETHARP_E_HEADER_TO_BUFFER_API_ID                      (0x12U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_ConflictDet_CurrAsgndIP()  */
#define RBA_ETHARP_E_CONFLICTDET_CURR_ASGNDIP_API_ID              (0x13U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_UpdateConflictTblEntry()  */
#define RBA_ETHARP_E_UPDATE_CONFLICT_TBLENTRY_API_ID              (0x14U)

/* Indicates the Api Id passed in the call of Det_ReportError, corresponding to rba_EthArp_GetArpTablesize()  */
#define RBA_ETHARP_E_GET_ARPTABLE_SIZE_API_ID                     (0x15U)

#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )

    /* DET Macro for functions with return type as 'void' */
    #define RBA_ETHARP_DET_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                             \
            if( CONDITION )                                                                                         \
            {                                                                                                       \
                (void)Det_ReportError( (RBA_ETHARP_MODULE_ID), (RBA_ETHARP_INSTANCE_ID), (API), (ERROR) ) ;         \
                return;                                                                                             \
            }

    /* DET Macro for functions with a return value */
    #define RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )                                \
            if( CONDITION )                                                                                       \
            {                                                                                                     \
                (void)Det_ReportError( (RBA_ETHARP_MODULE_ID), (RBA_ETHARP_INSTANCE_ID), (API), (ERROR) ) ;       \
                return ( RETVAL );                                                                                \
            }

   /* DET Macro for functions which reports error, but does not exit from function */
   #define RBA_ETHARP_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )                                              \
            if( CONDITION )                                                                                        \
            {                                                                                                      \
                (void)Det_ReportError( (RBA_ETHARP_MODULE_ID), ( RBA_ETHARP_INSTANCE_ID ), (API), (ERROR) );       \
            }

#else
    #define RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( CONDITION, API, ERROR )

    #define RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( CONDITION, API, ERROR, RETVAL )

    #define RBA_ETHARP_DET_REPORT_ERROR_NO_RET(CONDITION, API, ERROR )

#endif /* #if TCPIP_DEV_ERROR_DETECT */

#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
/*
****************************************************************************************************
*                                   Variables
****************************************************************************************************
*/
#define RBA_ETHARP_START_SEC_VAR_INIT_8
#include "rba_EthArp_MemMap.h"
/* Flag to indicate whether rba_EthArp_Init has been executed or not */
extern VAR( boolean, AUTOMATIC )  rba_EthArp_InitFlag_b;
#define RBA_ETHARP_STOP_SEC_VAR_INIT_8
#include "rba_EthArp_MemMap.h"

#define RBA_ETHARP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"
/* Pointer - will be initialized in the Init Function */
extern P2CONST( rba_EthArp_Config_to, AUTOMATIC, AUTOMATIC )    rba_EthArp_ConfigPtr_pco;
#define RBA_ETHARP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

/*
****************************************************************************************************
*                                   Prototype Functions
****************************************************************************************************
*/
extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE ) rba_EthArp_GetUsableEntry         ( P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco,
		                                                                              P2VAR( uint16, AUTOMATIC, AUTOMATIC )                    lUsableEntryIdx_pu16);

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_CleanArpTableEntry     ( P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )  lArpTableEntry_pst);

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_GetEthAddrInTableEntry ( P2CONST( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )  lArpTableEntry_pst,
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      lEthMacAddr_au8 );

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_UpdateArpTableEntry    ( P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )     lArpTableEntry_pst,
                                                                                      VAR( uint8, AUTOMATIC )                                    lCtrlIdxr_u8,
                                                                                      VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC )        lEntryState_en,
                                                                                      VAR( uint32, AUTOMATIC )                                   lIpAddr_u32,
                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )                     lEthAddr_au8,
                                                                                      VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )               lAssignMeth_en );

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_BufferToHeader         (  P2VAR( rba_EthArp_Hdr_tst, AUTOMATIC, AUTOMATIC )        lArpHdrPtr,
                                                                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )                   lRxDataPtr);

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_HeaderToBuffer         ( P2CONST( rba_EthArp_Hdr_tst, AUTOMATIC, AUTOMATIC )   lEthArpPtr_t,
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  lTxData);

extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE ) rba_EthArp_CheckIpTableEntry(  P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC )         lArpSubCfg_pco,
                                                                                 P2VAR( uint16, AUTOMATIC, AUTOMATIC )                            lIdxIpInTable_pu16,
                                                                                 VAR( uint32, AUTOMATIC )                                         lIpAddr_u32,
                                                                                 P2VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC, AUTOMATIC ) lTblEntryState_pen );


extern FUNC( Std_ReturnType,    RBA_ETHARP_CODE ) rba_EthArp_ConflictDet_CurrAsgndIP (
                                                                                       VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                                       VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )      lAssignMeth_en,
                                                                                       VAR( uint32, AUTOMATIC )                          lRxSrcIpAddress_u32,
                                                                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )            lRxSrcEthAddress_au8 );

extern FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_UpdateConflictTblEntry (
                                                                                       VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                                       VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )      lAssignMeth_en,
                                                                                       VAR( uint32, AUTOMATIC )                          lRxConflictIpAddress_u32,
                                                                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )            lRxSrcEthAddress_au8 );


#if (RBA_ETHARP_MAC_ADDRS_CHECKS==STD_ON)

extern FUNC( rba_EthArp_EthAddrMatch_ten, RBA_ETHARP_CODE ) rba_EthArp_ChkMACAddrMatch(VAR( uint8, AUTOMATIC )                          lCtrlIdx_u8,
                                                                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )       lRxSrcEthAddress_au8);
#endif
#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHARP_PRV_H */


