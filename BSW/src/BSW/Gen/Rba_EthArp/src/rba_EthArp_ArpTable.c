
#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )
#include "rba_EthArp.h"

#include "rba_EthArp_Prv.h"

/*************************************************************************************************/
/* rba_EthArp_UpdateArpTable() -                                                                 */
/*  Update the ARP Table with the new IP Address received from EthIF                             */
/*  All the IP/MAC Addresses received are stored, even if we have to overwrite an entry.         */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  CtrlIdx_u8      - Controller index used to transmit the ethernet frame                       */
/*  *lSrcEthAddr_au8- MAC Address received to store in the ARP Table                             */
/*  SrcIpAddr_u32   - IP Address received to check and to store in the ARP Table                 */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetVal - Return if the update of ARP Table is OK or NOT_OK                                  */
/*                                                                                               */
/*************************************************************************************************/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
FUNC( TcpIp_ReturnType,     RBA_ETHARP_CODE )   rba_EthArp_UpdateArpTable       (
                                                                VAR( uint8, AUTOMATIC )         lCtrlIdx_u8,
                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )      lSrcEthAddr_au8,
                                                                VAR( uint32, AUTOMATIC )    lSrcIpAddr_u32 )
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC )    lArpSubCfg_pco;
    VAR( uint16, AUTOMATIC )                                    lIndexTable_u16;
    VAR( uint8, AUTOMATIC )                                     lTableLoop_u8;
    VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC )         lIpAddrInArpTable_en;
    VAR( TcpIp_ReturnType, AUTOMATIC )                          lRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                            lStdRetVal_en;

    /* Local variable initialization */
    lRetVal_en      = TCPIP_E_NOT_OK;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_UPDATE_ARPTABLE_API_ID,   \
                                             RBA_ETHARP_E_NOTINIT, TCPIP_E_NOT_OK )

    /* Report DET if lSrcEthAddr_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lSrcEthAddr_au8 ), RBA_ETHARP_E_UPDATE_ARPTABLE_API_ID,      \
                                             RBA_ETHARP_E_NULL_PTR, TCPIP_E_NOT_OK )

    for (lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++)
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        if( lArpSubCfg_pco->EthIfCtrIdx_cu8 == lCtrlIdx_u8 )
        {
            /* Check in the ARP Table if the IP Address is known */
        	lStdRetVal_en = rba_EthArp_CheckIpTableEntry( lArpSubCfg_pco,
                                                          (uint16 *) &lIndexTable_u16,
                                                          lSrcIpAddr_u32,
                                                          &lIpAddrInArpTable_en );

            if( lStdRetVal_en == E_OK )
            {
                /* If IP Addr found */
                if(lIpAddrInArpTable_en != RBA_ETHARP_FREE_ENTRY)
                {
                    /* Keep the same lIndexTable_u16 and
                     * Overwrite the entry with the IP Address */
                }
                /* If IP Address not found */
                else
                {
                    /* Check entry available to store the new IP */
                	lStdRetVal_en =   rba_EthArp_GetUsableEntry( lArpSubCfg_pco,
                                                                 &lIndexTable_u16 );
                }

                if( ( ( lIpAddrInArpTable_en != RBA_ETHARP_FREE_ENTRY ) && ( lIpAddrInArpTable_en != RBA_ETHARP_CONFLICT_DETECTED ) ) ||
                    ( ( lIpAddrInArpTable_en == RBA_ETHARP_FREE_ENTRY ) && ( E_OK == lStdRetVal_en ) ) )
                {
                    /* Store the IP Address */
                    rba_EthArp_UpdateArpTableEntry(
                                    &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                                    lCtrlIdx_u8,
                                    RBA_ETHARP_ENTRY_USED,
                                    lSrcIpAddr_u32,
                                    &lSrcEthAddr_au8[0],
                                    TCPIP_IPADDR_ASSIGNMENT_INVALID );

                    lRetVal_en = TCPIP_OK;
                }
            }

            /* Break the loop */
            break;
        }
    } /* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid and return TCPIP_E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE(( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),       \
    		                                RBA_ETHARP_E_UPDATE_ARPTABLE_API_ID, RBA_ETHARP_E_INV_ARG, TCPIP_E_NOT_OK )

    return lRetVal_en;
}


/*************************************************************************************************/
/* rba_EthArp_ReadArpTable() -   API is used to read out the Arp table for the EthIfCrtl         */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  EthIfCtrlIdx_u8     - index of the EthIf controller, for which Arp table shall be read out   */
/*                                                                                               */
/* Inout Parameters :                                                                            */
/* NumberEntries_pu16   - number of Arp table entries.                                           */
/*                      - As input parameter specifies the number of Arp table entries to be read*/
/*                       (size of the provided buffer ArpTable_pu8 in entries).                  */
/*                      - As output parameter specifies the number of Arp table entries read     */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  ArpTable_pu8        - Pointer to first element of array, which contains the ARP table        */
/*                        per EthIfCtrl                                                          */
/*                                                                                               */
/* Return :                                                                                      */
/*  lRetVal_tu8         - E_OK: The request was successful, ArpTable_pu8 and NumberEntries_pu16  */
/*                       were successfully updated and contain valid data.                       */
/*                      - E_NOT_OK: The request was not successful.                              */
/*                                                                                               */
/*************************************************************************************************/

/* Arp table entry stored in the ArpTable_pu8 buffer shall have the structure as defined in Ethernet Bus Diagnostics LH: */
/* byte[0]= 0 if the entry uses IPv4, byte[0]= 1 if the entry uses IPv6. */
/* Byte[0] shall be always set to IPv4, as IPv6 is currently not supported */
/* For IPv4: byte[1] - byte[4]=IPv4 address starting with the first octet (e.g., byte[1]=0xC0, byte[2]=0xA8, byte[3]=0x00,  */
/* byte[4]=0x01 for IP address 192.168.0.1) */
/* byte[5-16]=0. For IPv6: byte[1-16]=IPv6 address. */
/* byte[17-22]=MAC address. */

FUNC( Std_ReturnType, RBA_ETHARP_CODE ) rba_EthArp_ReadArpTable(
                                        VAR(        uint8,      AUTOMATIC )                 EthIfCtrlIdx_u8,
                                        CONSTP2VAR( uint8,      AUTOMATIC, AUTOMATIC )      ArpTable_cpu8,
                                        CONSTP2VAR( uint16,     AUTOMATIC, AUTOMATIC )      NumberEntries_cpu16 )
{
    VAR     ( Std_ReturnType,           AUTOMATIC )             lRetVal_en;
    P2VAR   ( rba_EthArp_ArpTable_tst,  AUTOMATIC, AUTOMATIC )  lArpTable_past;
    VAR     ( uint16,                   AUTOMATIC )             lnrOfEntriesToBeRead_u16;
    VAR     ( uint16,                   AUTOMATIC )             lTableOffSet_u16;
    VAR     ( uint8,                    AUTOMATIC )             lArpTableLoop_u8;
    VAR     ( uint16,                   AUTOMATIC )             lArpTableEntryLoop_u16;
    VAR     ( uint8,                    AUTOMATIC )             lTableLoopIndx_u8;

    /* Local variable initialisation */
    lRetVal_en  = E_NOT_OK;
    lTableOffSet_u16 = 0;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_READ_ARPTABLE_API_ID,  \
                                             RBA_ETHARP_E_NOTINIT, E_NOT_OK )

    /* Report DET if ArpTable_cpu8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == ArpTable_cpu8 ), RBA_ETHARP_E_READ_ARPTABLE_API_ID,       \
                                             RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if NumberEntries_cpu16 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == NumberEntries_cpu16 ), RBA_ETHARP_E_READ_ARPTABLE_API_ID, \
                                             RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if value at address of NumberEntries_pu16 is equal 0 */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( ( *NumberEntries_cpu16 ) == 0 ), RBA_ETHARP_E_READ_ARPTABLE_API_ID,   \
                                             RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    /* Locally store the number of ARP entries to be read from inout parameter  NumberEntries_cpu16 and set NumberEntries_cpu16 to zero */
    lnrOfEntriesToBeRead_u16 = *NumberEntries_cpu16;
    *NumberEntries_cpu16 = 0;

    /* Get the base address of ARP table for the requested EthIf controller */
    /* Loop through all ARP tables configured */
    for(lArpTableLoop_u8 = 0; lArpTableLoop_u8 < (rba_EthArp_ConfigPtr_pco->NumArpTbl_u8); lArpTableLoop_u8++ )
    {
        /* If requested EthIf controller index is same as configured controller index, get the base address of ARP table */
        if( rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lArpTableLoop_u8].EthIfCtrIdx_cu8 == EthIfCtrlIdx_u8 )
        {
            /* Store the base address of ARP table */
            lArpTable_past = rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lArpTableLoop_u8].ArpTable_past;

            /* Loop through entries in the table until requested number ARP entries are read and ARP table pointer has not crossed size of the table */
            for( lArpTableEntryLoop_u16 = 0;
                 ((*NumberEntries_cpu16 < lnrOfEntriesToBeRead_u16) && (lArpTableEntryLoop_u16 < (rba_EthArp_ConfigPtr_pco->TableSizeMax_u16 )));
                 lArpTableEntryLoop_u16++ )
            {
                if( ( lArpTable_past[lArpTableEntryLoop_u16].procEntryState_en == RBA_ETHARP_ENTRY_USED ) ||
                    ( lArpTable_past[lArpTableEntryLoop_u16].procEntryState_en == RBA_ETHARP_RPLY_TO_BE_SENT ) )
                {
                    ArpTable_cpu8[lTableOffSet_u16] = 0;    /* Byte[0] shall be always set to IPv4 ( 0 indicates IP address is of IPv4 type ) */

                    /* Write IP address into table provided */
                    /* byte[1] - byte[4]=IPv4 address starting with the first octet */
                    ArpTable_cpu8[lTableOffSet_u16 + 1] = (uint8)( ( lArpTable_past[lArpTableEntryLoop_u16].destIpAddr_u32 & 0xFF000000UL ) >> 24U );
                    ArpTable_cpu8[lTableOffSet_u16 + 2] = (uint8)( ( lArpTable_past[lArpTableEntryLoop_u16].destIpAddr_u32 & 0x00FF0000UL ) >> 16U );
                    ArpTable_cpu8[lTableOffSet_u16 + 3] = (uint8)( ( lArpTable_past[lArpTableEntryLoop_u16].destIpAddr_u32 & 0x0000FF00UL ) >>  8U );
                    ArpTable_cpu8[lTableOffSet_u16 + 4] = (uint8)(   lArpTable_past[lArpTableEntryLoop_u16].destIpAddr_u32 & 0x000000FFUL );

                    /* Fill table entries with zero for index from 5 to 16 */
                    for(lTableLoopIndx_u8 = 5; lTableLoopIndx_u8 <= 16 ; lTableLoopIndx_u8 ++)
                    {
                        ArpTable_cpu8[lTableOffSet_u16 + lTableLoopIndx_u8] = 0;
                    }

                    /* MAC address is stored in the table starting from index 17 to 22 */
                    rba_EthArp_GetEthAddrInTableEntry( (lArpTable_past + lArpTableEntryLoop_u16), (ArpTable_cpu8 + lTableOffSet_u16 + 17) );


                    ( *NumberEntries_cpu16 )++;             /* Increment inout pointer parameter by 1, to indicate one element has been successfully read */
                    lTableOffSet_u16 = lTableOffSet_u16 + 23;   /* Increment table pointer by element size (23) so that table points to beginning of next entry  */
                }
            }
            lRetVal_en  = E_OK;

            /* break the loop */
            break;
        }
    }/* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid and return E_NOT_OK */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( lArpTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),      \
    		                                 RBA_ETHARP_E_READ_ARPTABLE_API_ID, RBA_ETHARP_E_INV_ARG, E_NOT_OK )

    return lRetVal_en;
}


/*************************************************************************************************/
/* rba_EthArp_CleanArpTable() - This API cleans the ARP Table corresponding to the EthIf         */
/*                              controller passed as input parameter                             */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*      EthIfCtrlIdxCurr_u8  - Current EthIf controller index, for which                        */
/*                              the corresponding ARP table is cleaned                           */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_CleanArpTable  (  VAR( uint8, AUTOMATIC ) EthIfCtrlIdxCurr_u8 )
{
    /*Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
    VAR( uint16, AUTOMATIC )                                 lEntryLoop_u16;
    VAR( uint8, AUTOMATIC )                                  lTableLoop_u8;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_CLEAN_ARPTABLE_API_ID, RBA_ETHARP_E_NOTINIT )

    for ( lTableLoop_u8 = 0; lTableLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lTableLoop_u8++ )
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        /* Check if the EthIf controller index matches with the current EthIf Ctrl */
        if( lArpSubCfg_pco->EthIfCtrIdx_cu8 == EthIfCtrlIdxCurr_u8 )
        {
            /* Reset the ARP table */
            for( lEntryLoop_u16 = 0; lEntryLoop_u16 < rba_EthArp_ConfigPtr_pco->TableSizeMax_u16; lEntryLoop_u16++ )
            {
                rba_EthArp_CleanArpTableEntry( &lArpSubCfg_pco->ArpTable_past[lEntryLoop_u16] );
            }
            /* break the loop */
            break;
        }
    } /* End of for Table loop */

    /* Report DET if value of lCtrlIdx_u8 is not valid */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( lTableLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),     \
    		                              RBA_ETHARP_E_CLEAN_ARPTABLE_API_ID, RBA_ETHARP_E_INV_ARG )


}

/*************************************************************************************************/
/* rba_EthArp_GetArpTablesize() - This API Provideds the max ARP Table size                      */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*      lArpTableSize_pu16  - Max ARP table size                                                 */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( Std_ReturnType ,            RBA_ETHARP_CODE ) rba_EthArp_GetArpTablesize (   P2VAR( uint16, AUTOMATIC, AUTOMATIC ) lArpTableSize_pu16 )
{
    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_GET_ARPTABLE_SIZE_API_ID, RBA_ETHARP_E_NOTINIT,E_NOT_OK )

    /* Report DET if ArpTable_cpu8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lArpTableSize_pu16 ), RBA_ETHARP_E_GET_ARPTABLE_SIZE_API_ID, RBA_ETHARP_E_NULL_PTR,E_NOT_OK)

    *lArpTableSize_pu16 = rba_EthArp_ConfigPtr_pco->TableSizeMax_u16;

    return E_OK;
}

#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

