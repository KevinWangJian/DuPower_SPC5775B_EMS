

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )
#include "rba_EthArp.h"
#include "rba_EthArp_Types.h"

#include "EthIf.h"
#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - TcpIp and EthIf"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - TcpIp and EthIf"
#endif

#include "rba_EthArp_Prv.h"

/*
****************************************************************************************************
*                           Internal Functions of the ARP Component
****************************************************************************************************
*/

/*************************************************************************************************/
/* rba_EthArp_CleanArpTableEntry() -                                                             */
/* Clean the entry to the ARP Table authorized defined by Index parameter                        */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*      lArpTableEntry_pst  - Pointer to the ARP Table Entry to clean                            */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_CleanArpTableEntry     ( P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )  lArpTableEntry_pst)
{
    /* Report DET if lArpTableEntry_pst is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lArpTableEntry_pst ), RBA_ETHARP_E_CLEAN_ARPTABLE_ENTRY_API_ID,      \
                                          RBA_ETHARP_E_NULL_PTR )

    /* Initialize state of the entry (free entry )*/
    lArpTableEntry_pst->procEntryState_en       = RBA_ETHARP_FREE_ENTRY;
    lArpTableEntry_pst->procIpAddrType_en       = TCPIP_SUBNET_EXT_IPV4ADDR;
    lArpTableEntry_pst->destIpAddr_u32          = 0;
    lArpTableEntry_pst->procTimeOutEntryCnt_u32 = 0;
    lArpTableEntry_pst->procTxFrameCnt_u16      = 0;

    /* Initialize MAC Address value */
    lArpTableEntry_pst->destHwAddr_au8[0]       = 0 ;
    lArpTableEntry_pst->destHwAddr_au8[1]       = 0 ;
    lArpTableEntry_pst->destHwAddr_au8[2]       = 0 ;
    lArpTableEntry_pst->destHwAddr_au8[3]       = 0 ;
    lArpTableEntry_pst->destHwAddr_au8[4]       = 0 ;
    lArpTableEntry_pst->destHwAddr_au8[5]       = 0 ;
}

/*************************************************************************************************/
/* rba_EthArp_GetEthAddrInTableEntry() -                                                         */
/*  This API is called to return the MAC address contained in the ARP Table entry defined by     */
/*  the index given as parameter.                                                                */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lArpTableEntry_pst - Pointer to the ARP Table Entry to read                                  */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  uint8 *lEthMacAddr_au8 - Buffer to fill with MAC Address                                     */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_GetEthAddrInTableEntry ( P2CONST( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )  lArpTableEntry_pst,
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      lEthMacAddr_au8 )
{
    /* Local variable declaration */
    VAR( uint8, AUTOMATIC ) lLoop_u8;

    /* Report DET if lArpTableEntry_pst is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lArpTableEntry_pst ), RBA_ETHARP_E_GET_ETHADDR_IN_TABLEENTRY_API_ID,      \
                                          RBA_ETHARP_E_NULL_PTR )

    /* Report DET if lEthMacAddr_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lEthMacAddr_au8 ), RBA_ETHARP_E_GET_ETHADDR_IN_TABLEENTRY_API_ID,         \
                                          RBA_ETHARP_E_NULL_PTR )

    /* Return the MAC address */
    for(lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
    {
        lEthMacAddr_au8[lLoop_u8] = lArpTableEntry_pst->destHwAddr_au8[lLoop_u8];
    }
}

/*************************************************************************************************/
/* rba_EthArp_GetUsableEntry() -                                                                 */
/* This API is called to check the status of ARP Table entries and return the index of one       */
/* usable Entry to store IP and MAC address. The "Overwriting" priority must be done in this     */
/* API : if any free entry is found, the oldest entry for each new frame received is overwrited. */
/*                                                                                               */
/* Define the priority to use free entry or reuse entry                                          */
/* return the index of the entry that we can use or overwrite                                    */
/* Priority defined :                                                                            */
/* - We use in a first time the first Free entry or timed out entry is found ;                   */
/* - If no free entry or timed out entry:                                                        */
/*          - We use the oldest pending entry                                                    */
/*          - If no pending entry : we use the oldest used entry.                                */
/*          - We cannot remove entry with Static IP.                                             */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lArpSubCfg_pco - Pointer to the ARP Table                                                    */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  lUsableEntryIdx_pu16 - Buffer to fill with Index of the ARP Table                            */
/*                         where we can store the new pair IP/MAC Address                        */
/*                                                                                               */
/* Return :                                                                                      */
/*  Std_ReturnType -                                                                             */
/*  E_OK -  lUsableEntryIdx_pu16 contains a valid usable entry                                   */
/*  E_NOT_OK - lUsableEntryIdx_pu16 does not contain a valid usable entry                        */
/*                                                                                               */
/*************************************************************************************************/
FUNC( Std_ReturnType,           RBA_ETHARP_CODE ) rba_EthArp_GetUsableEntry ( P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco,
		                                                                      P2VAR( uint16, AUTOMATIC, AUTOMATIC )                    lUsableEntryIdx_pu16 )
{
    /* Local variable declaration */
    VAR( uint32,                             AUTOMATIC )    lTimeUsedEntry_u32;     /* Save the biggest time of a free entry */
    VAR( uint32,                             AUTOMATIC )    lTimePendEntry_u32;     /* Save the biggest time of a pending entry */
    VAR( uint16,                             AUTOMATIC )    lOldestUsedEntry_u16;   /* Save the idx of the oldest used entry */
    VAR( uint16,                             AUTOMATIC )    lOldestPendEntry_u16;   /* Save the idx of the oldest pending entry */
    VAR( uint16,                             AUTOMATIC )    lSaveEntry_u16;         /* Save the idx of the first free entry */
    VAR( uint16,                             AUTOMATIC )    lLoop_u16;
    VAR( rba_EthArp_ArpTableEntryState_ten , AUTOMATIC )    lEntryState_en;         /* Save the state of the entry */
    VAR( Std_ReturnType,                     AUTOMATIC )    lPendEntryInTable_tu8;  /* Flag to inform whether a pending entry has been found */
    VAR( Std_ReturnType,                     AUTOMATIC )    lEmptEntryInTable_tu8;  /* Flag to inform whether a free entry has been found */

    /* Local variable initialization */
    lPendEntryInTable_tu8= E_NOT_OK;
    lEmptEntryInTable_tu8= E_NOT_OK;
    lSaveEntry_u16       = 0;
    lOldestUsedEntry_u16 = 0;
    lOldestPendEntry_u16 = 0;
    lTimeUsedEntry_u32   = 0;
    lTimePendEntry_u32   = 0;

    /* Report DET if lArpSubCfg_pco is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lArpSubCfg_pco ), RBA_ETHARP_E_GET_USABLE_ENTRY_API_ID,         \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if lUsableEntryIdx_pu16 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lUsableEntryIdx_pu16 ), RBA_ETHARP_E_GET_USABLE_ENTRY_API_ID,   \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    /* If Entry available */
    for (lLoop_u16 = 0;((lEmptEntryInTable_tu8 == E_NOT_OK) && (lLoop_u16 < (rba_EthArp_ConfigPtr_pco->TableSizeMax_u16))); lLoop_u16++ )
    {
        /* Get the current state of the entry */
        lEntryState_en = lArpSubCfg_pco->ArpTable_past[lLoop_u16].procEntryState_en;

        /* If free entry or timed out entry found => Save the Idx of this entry */
        if ((lEntryState_en == RBA_ETHARP_FREE_ENTRY) || ( lEntryState_en == RBA_ETHARP_TIME_OUT ))
        {
            /* remember index empty entry */
            lSaveEntry_u16 = lLoop_u16;

            /* Empty entry in the table
             * We break the loop. */
            lEmptEntryInTable_tu8 = E_OK;

        }
        /* If no free entry found
         * => check the others entries and save the oldest */
        else
        {
            /* Priority 1 : Look for oldest Pending entry */
            if (lEntryState_en == RBA_ETHARP_RPLY_PENDING)
            {
                if (lArpSubCfg_pco->ArpTable_past[lLoop_u16].procTimeOutEntryCnt_u32 >= lTimePendEntry_u32)
                {
                    /* Remember entry with oldest pending entry */
                    lOldestPendEntry_u16 = lLoop_u16;
                    lTimePendEntry_u32   = lArpSubCfg_pco->ArpTable_past[lLoop_u16].procTimeOutEntryCnt_u32;

                    /* Indicate that there are Pending Entries in the Table */
                    lPendEntryInTable_tu8 = E_OK;

                }
            }
            /* Priority 2 : Look for oldest Used entry ? */
            else if ( ( lEntryState_en == RBA_ETHARP_ENTRY_USED ) || ( lEntryState_en == RBA_ETHARP_RPLY_TO_BE_SENT ) )
            {
                /* We cannot remove Static Entries (internal IP addresses) */
                if ( TCPIP_SUBNET_INT_IPV4ADDR != lArpSubCfg_pco->ArpTable_past[lLoop_u16].procIpAddrType_en )
                {
                    if (lArpSubCfg_pco->ArpTable_past[lLoop_u16].procTimeOutEntryCnt_u32 >= lTimeUsedEntry_u32)
                    {
                        /* Remember entry with oldest stable entry */
                        lOldestUsedEntry_u16 = lLoop_u16;
                        lTimeUsedEntry_u32   = lArpSubCfg_pco->ArpTable_past[lLoop_u16].procTimeOutEntryCnt_u32;
                    }
                }
            }
            /* RBA_ETHARP_REQ_TO_BE_SENT and RBA_ETHARP_CONFLICT_DETECTED entries shall not be overwritten. */
            else
            {
            	/* Nothing to do */
            }
        }
    }

    /* If free entry found */
    if (E_OK == lEmptEntryInTable_tu8)
    {
    	*lUsableEntryIdx_pu16 = lSaveEntry_u16;
    }
    /* if no free entry */
    else if (E_OK == lPendEntryInTable_tu8)
    {
        /* Return the oldest pending entry if pending entry in ARP Table */
    	*lUsableEntryIdx_pu16 = lOldestPendEntry_u16;
    }
    /* if no free entry / no pending entry */
    else
    {   /* return the oldest used entry */
    	*lUsableEntryIdx_pu16 = lOldestUsedEntry_u16;
    }

    return E_OK;
}

/*************************************************************************************************/
/* rba_EthArp_CheckIpTableEntry() -                                                              */
/* Check if the IP address is already in the ARP Table : if yes, flag true and index to find the */
/* entry with the IP address, if not we return flag false                                        */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lArpSubCfg_pco  - Pointer to the ARP Table                                                   */
/*  lIpAddr_u32     - IP Address to check in the ARP Table                                       */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  uint16 * lIdxIpInTable_pu16 -   Buffer to fill with Index of the ARP Table in which          */
/*                                  the IP is stored.                                            */
/* rba_EthArp_ArpTableEntryState_ten* lTblEntryState_en -  Pointer to the                        */
/*                                                                                               */
/* return - Std_ReturnType  lRetVal_tu8                                                          */
/*      E_OK : Function call successful                                                          */
/*      E_NOT_OK : Function call unsuccessful                                                    */
/*                                                                                               */
/*************************************************************************************************/
FUNC( Std_ReturnType ,          RBA_ETHARP_CODE ) rba_EthArp_CheckIpTableEntry(   P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC )         lArpSubCfg_pco,
                                                                                  P2VAR( uint16, AUTOMATIC, AUTOMATIC )                            lIdxIpInTable_pu16,
                                                                                  VAR( uint32, AUTOMATIC )                                         lIpAddr_u32,
                                                                                  P2VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC, AUTOMATIC ) lTblEntryState_pen )

{
    /* Local variable declaration */
    VAR( uint16, AUTOMATIC )                                lLoop_u16;

    /* Report DET if lArpSubCfg_pco is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lArpSubCfg_pco ), RBA_ETHARP_E_CHECK_IPTABLE_ENTRY_API_ID,         \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if lIdxIpInTable_pu16 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lIdxIpInTable_pu16 ), RBA_ETHARP_E_CHECK_IPTABLE_ENTRY_API_ID,     \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK  )

    /* Report DET if lTblEntryState_pen is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lTblEntryState_pen ), RBA_ETHARP_E_CHECK_IPTABLE_ENTRY_API_ID,     \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK  )
    /* Set Table entry state to FREE */
    *lTblEntryState_pen = RBA_ETHARP_FREE_ENTRY;

    /* Cover all the ARP Table static entries */
    for (lLoop_u16 = 0; lLoop_u16 < (rba_EthArp_ConfigPtr_pco->TableSizeMax_u16); lLoop_u16++)
    {
        /* Compare IP Address */
        if( lArpSubCfg_pco->ArpTable_past[lLoop_u16].destIpAddr_u32 == lIpAddr_u32 )
        {
            /* Save the state of the entry */
        	*lTblEntryState_pen = lArpSubCfg_pco->ArpTable_past[lLoop_u16].procEntryState_en;
            /* Save the value of the entry */
            *lIdxIpInTable_pu16 = lLoop_u16;

            break;
        }
    }

    return E_OK;
}

/*************************************************************************************************/
/* rba_EthArp_UpdateArpTableEntry() -                                                            */
/* Add or overwrite an entry in the ARP Table with a new IP/MAC Address and State.               */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*      lArpTableEntry_pst  - Pointer to the ARP Table Entry to update                           */
/*      lCtrlIdxr_u8        - Controller index for which the Ip address is stored                */
/*      lEntryState_en      - State of the entry to update in the ARP Table                      */
/*      lIpAddr_u32         - IP Address to store in the ARP Table                               */
/*      lEthAddr_au8        - MAC Address to store in the ARP Table                              */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_UpdateArpTableEntry    ( P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )     lArpTableEntry_pst,
                                                                                      VAR( uint8, AUTOMATIC )                                    lCtrlIdxr_u8,
                                                                                      VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC )        lEntryState_en,
                                                                                      VAR( uint32, AUTOMATIC )                                   lIpAddr_u32,
                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )                     lEthAddr_au8,
                                                                                      VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )               lAssignMeth_en  )
{
    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )                lStdRetType_tu8;
    VAR( TcpIp_IPv4AddrType_ten, AUTOMATIC )        lAddrType_en;
    VAR( uint8, AUTOMATIC )                         lLoop_u8;

    /* Local variable initialization */
    lStdRetType_tu8 = E_NOT_OK;
    lAddrType_en = TCPIP_SUBNET_EXT_IPV4ADDR;

    /* Report DET if lArpTableEntry_pst is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lArpTableEntry_pst ), RBA_ETHARP_E_UPDATE_ARPTABLE_ENTRY_API_ID,     \
                                          RBA_ETHARP_E_NULL_PTR )

    /* Report DET if lEthAddr_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lEthAddr_au8 ), RBA_ETHARP_E_UPDATE_ARPTABLE_ENTRY_API_ID,           \
                                          RBA_ETHARP_E_NULL_PTR )

    /* Check if the IP to store is equal to 0 */
    if(lIpAddr_u32 != 0UL)
    {
        /* Get the ARP table index corresponding to the EthIfCtrl */
        for( lLoop_u8 = 0; lLoop_u8 < ( rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ); lLoop_u8++ )
        {
            if ( rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lLoop_u8].EthIfCtrIdx_cu8 == lCtrlIdxr_u8 )
            {
                break;
            }
        }

        /* Check If Arp Table Entries Ageing is disabled for the EthIfCtrl */
        if ( rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lLoop_u8].AgeingDisabled_cu8 == STD_ON )
        {
            /* Check if IP address is a fixed or a static IP address */
            lStdRetType_tu8 = TcpIp_SubnetMskChkRemoteIpAddr(   lCtrlIdxr_u8,
                                                                lIpAddr_u32,
                                                                &lAddrType_en );
        }

        if( E_OK == lStdRetType_tu8 )
        {
            /* If Return Type E_OK and Ageing Disabled => Store IP Type returned by TcpIp function */
            lArpTableEntry_pst->procIpAddrType_en = lAddrType_en;
        }
        else
        {
            /* Ageing enabled and/or TcpIp function returned E_NOT_OK => Store TCPIP_SUBNET_EXT_IPV4ADDR */
            lArpTableEntry_pst->procIpAddrType_en = TCPIP_SUBNET_EXT_IPV4ADDR;
        }

        /* Update Entry */
        lArpTableEntry_pst->procEntryState_en       = lEntryState_en;
        lArpTableEntry_pst->destIpAddr_u32          = lIpAddr_u32;
        lArpTableEntry_pst->procTimeOutEntryCnt_u32 = 0;
        lArpTableEntry_pst->procIpAssignMeth_en     = lAssignMeth_en;
        /*lArpTableEntry_pst->procTxFrameCnt_u16        = 0;*/

        /* Update MAC Address */
        for(lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
        {
            lArpTableEntry_pst->destHwAddr_au8[lLoop_u8] = lEthAddr_au8[lLoop_u8];
        }
    }
    else
    {
        /* It's avoided to store an IP Address == 0 in the ARP Table.
         * It can be the case if ARP Probe frame is received (SrcIp.Addr = 0) */
    }
}

/****************************************************************************************************/
/* rba_EthArp_ConflictDet_CurrAsgndIP() -                                                           */
/* Checks if there is an IP conflict with the currently assigned IP address                         */
/*                                                                                                  */
/* Input Parameters :                                                                               */
/*      lCtrlIdx_u8              - Index of the EthIf Controller                                    */
/*      lAssignMeth_en           - Assignment method of the currently assigned IP address           */
/*      lRxSrcIpAddress_u32      - Source IP address received, which has to be checked for conflict */
/*      lEthAddr_au8             - MAC Address received from the remote node                        */
/*                                                                                                  */
/* Return - Std_ReturnType  lRetVal_tu8                                                             */
/*      E_OK :    IP Conflict has been detected.                                                    */
/*      E_NOT_OK : No IP Conflict has been detected.                                                */
/*                                                                                                  */
/****************************************************************************************************/
FUNC( Std_ReturnType,    RBA_ETHARP_CODE ) rba_EthArp_ConflictDet_CurrAsgndIP ( VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                                VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )      lAssignMeth_en,
                                                                                VAR( uint32, AUTOMATIC )                          lRxSrcIpAddress_u32,
                                                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )            lRxSrcEthAddress_au8 )

{
    /* Local variable declaration */
	VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_tu8;
    VAR( Std_ReturnType, AUTOMATIC )                    lRetFctVal_tu8;
    VAR( uint32, AUTOMATIC )                            lCurrentIpAddr_u32;
    VAR( uint32, AUTOMATIC )                            lNetMask_u32;
    VAR( rba_EthArp_EthAddrMatch_ten, AUTOMATIC )       lEthAddrMatch_en;

    /* Local variable initialization */
    lCurrentIpAddr_u32              = 0;
    lRetVal_tu8                     = E_NOT_OK;
    lRetFctVal_tu8                  = E_NOT_OK;
    lEthAddrMatch_en                = RBA_ETHARP_ETHADDR_NO_MATCH;


    /* Report DET if lRxSrcEthAddress_au8 is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == lRxSrcEthAddress_au8 ), RBA_ETHARP_E_CONFLICTDET_CURR_ASGNDIP_API_ID,      \
                                           RBA_ETHARP_E_NULL_PTR, E_NOT_OK )

    lRetFctVal_tu8 = TcpIp_GetIPv4AddrFrmCtrlIdx( lCtrlIdx_u8, &lCurrentIpAddr_u32, &lNetMask_u32 );

    if( lRetFctVal_tu8 == E_OK )
    {

		#if (RBA_ETHARP_MAC_ADDRS_CHECKS==STD_ON)
		lEthAddrMatch_en = rba_EthArp_ChkMACAddrMatch(lCtrlIdx_u8,lRxSrcEthAddress_au8);
		#endif

		/* we have a conflict if : ip.src == lCurrentIpAddr_u32 && hw.src != lMyEthAddr_au8 */
		if( ( lRxSrcIpAddress_u32 == lCurrentIpAddr_u32 ) && ( RBA_ETHARP_ETHADDR_NO_MATCH == lEthAddrMatch_en ))
		{
			rba_EthArp_UpdateConflictTblEntry( lCtrlIdx_u8,
											   lAssignMeth_en,
											   lRxSrcIpAddress_u32,
											   &lRxSrcEthAddress_au8[0] );

			/* Return E_OK to inform about the conflict */
		    lRetVal_tu8 = E_OK;
		}
    }

    return lRetVal_tu8;
}

/*************************************************************************************************/
/* rba_EthArp_UpdateConflictTblEntry() -                                                         */
/* Add or overwrite an entry in the ARP Table with state RBA_ETHARP_CONFLICT_DETECTED.           */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*      lCtrlIdx_u8              - Controller index for which the Conflict Ip address is stored  */
/*      lAssignMeth_en           - IP address Assignment method to be stored in the Table entry  */
/*      lRxConflictIpAddress_u32 - Conflict IP Address to store in the Table entry               */
/*      lEthAddr_au8             - Received MAC Address to store in the Table entry              */
/*                                                                                               */
/* Return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,             RBA_ETHARP_CODE ) rba_EthArp_UpdateConflictTblEntry ( VAR( uint8, AUTOMATIC )                           lCtrlIdx_u8,
                                                                               VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )      lAssignMeth_en,
                                                                               VAR( uint32, AUTOMATIC )                          lRxConflictIpAddress_u32,
                                                                               P2CONST( uint8, AUTOMATIC, AUTOMATIC )            lRxSrcEthAddress_au8 )
{

    /* Local variable declaration */
   P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC )      lArpSubCfg_pco;
   VAR( rba_EthArp_ArpTableEntryState_ten,      AUTOMATIC )      lIpAddrInArpTable_en;
   VAR( uint16,                                 AUTOMATIC )      lIndexTable_u16;
   VAR( uint8,                                  AUTOMATIC )      lLoop_u8;
   VAR( Std_ReturnType, AUTOMATIC )                              lStdRetVal_en;

   /* Local variable initialization */
   lArpSubCfg_pco = NULL_PTR;

   /* Report DET if lRxSrcEthAddress_au8 is a Null Pointer */
   RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lRxSrcEthAddress_au8 ), RBA_ETHARP_E_UPDATE_CONFLICT_TBLENTRY_API_ID, RBA_ETHARP_E_NULL_PTR )

   for(lLoop_u8 = 0; lLoop_u8 < rba_EthArp_ConfigPtr_pco->NumArpTbl_u8; lLoop_u8++)
   {
       /* Local Copy of the ARP SubConfig Structure */
       lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lLoop_u8];

       if(lCtrlIdx_u8 == lArpSubCfg_pco->EthIfCtrIdx_cu8)
       {
           break;
       }
   }

    /* Report DET if value of lCtrlIdx_u8 is not valid and return */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( lLoop_u8 == rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ),                       \
    		                      RBA_ETHARP_E_UPDATE_CONFLICT_TBLENTRY_API_ID, RBA_ETHARP_E_INV_ARG  )

    /* Check in the ARP Table if the IP Address is known */
    lStdRetVal_en = rba_EthArp_CheckIpTableEntry( lArpSubCfg_pco,
                                                  (uint16 *) &lIndexTable_u16,
                                                  lRxConflictIpAddress_u32,
                                                  &lIpAddrInArpTable_en );

   if( lStdRetVal_en == E_OK )
   {
       /* If IP Addr found */
       if( lIpAddrInArpTable_en != RBA_ETHARP_FREE_ENTRY )
       {
           /* Keep the same lIndexTable_u16 and do nothing */
           /* Report DET error if the State of the entry is not RBA_ETHARP_TIME_OUT or RBA_ETHARP_CONFLICT_DETECTED */
              RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( ( lIpAddrInArpTable_en != RBA_ETHARP_CONFLICT_DETECTED ) && ( lIpAddrInArpTable_en != RBA_ETHARP_TIME_OUT ) ),   \
                                                    RBA_ETHARP_E_UPDATE_CONFLICT_TBLENTRY_API_ID, RBA_ETHARP_E_INV_TBL_ENTRY  )
       }
       /* If IP Address not found */
       else
       {
           /* Check entry available to store the new IP */
           lStdRetVal_en =   rba_EthArp_GetUsableEntry( lArpSubCfg_pco,
                                                        &lIndexTable_u16 );

           if( lStdRetVal_en == E_OK )
           {
               /* Store the IP Address */
               rba_EthArp_UpdateArpTableEntry(
                               &lArpSubCfg_pco->ArpTable_past[lIndexTable_u16],
                               lCtrlIdx_u8,
                               RBA_ETHARP_CONFLICT_DETECTED,
                               lRxConflictIpAddress_u32,
                               &lRxSrcEthAddress_au8[0],
                               lAssignMeth_en );
           }
       }
   }

    return;
}

/*************************************************************************************************/
/* rba_EthArp_ChkMACAddrMatch() -                                                                */
/*      Function to check the Src MAC and the Dest MAC address are same or not                   */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lEthIfCtrlId_u8      - Controller index                                                      */
/*  lRxSrcEthAddress_au8    - MAC Address received from the ARP Frame                            */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  NIL                                                                                          */
/*                                                                                               */
/* return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
#if (RBA_ETHARP_MAC_ADDRS_CHECKS==STD_ON)
FUNC( rba_EthArp_EthAddrMatch_ten, RBA_ETHARP_CODE ) rba_EthArp_ChkMACAddrMatch( VAR( uint8, AUTOMATIC )                        lCtrlIdx_u8,
                                                                                 P2CONST( uint8, AUTOMATIC, AUTOMATIC )         lRxSrcEthAddress_au8)
{
    VAR( uint8, AUTOMATIC )                             lLoop_u8;
    VAR( uint8, AUTOMATIC )                             lMyEthAddr_au8[RBA_ETHARP_HWADDR_LENGTH];
    VAR( rba_EthArp_EthAddrMatch_ten, AUTOMATIC )       lEthAddrMatch_en;

    lEthAddrMatch_en                = RBA_ETHARP_ETHADDR_INIT;

    /* check if lRxSrcEthAddress_au8 is a Null Pointer */
    if( NULL_PTR != lRxSrcEthAddress_au8 )
    {
        /* Get the source Ethernet address based on the controller index */
        EthIf_GetPhysAddr( lCtrlIdx_u8, (uint8 *)&lMyEthAddr_au8[0] );

        /* Check if MAC Address are similar */
        for ( lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++ )
        {
            if( lRxSrcEthAddress_au8[lLoop_u8] !=  lMyEthAddr_au8[lLoop_u8] )
            {   /* One Byte is different => Break the loop */
                lEthAddrMatch_en = RBA_ETHARP_ETHADDR_NO_MATCH;
                break;
            }
            else
            {   /* All the MAC Address Bytes match at the end of the Loop */
                lEthAddrMatch_en = RBA_ETHARP_ETHADDR_MATCH;
            }
        }
     }

    return lEthAddrMatch_en;
}
#endif

/*************************************************************************************************/
/* rba_EthArp_BufferToHeader() -                                                                 */
/* Function called to fill the header frame with the data received. Function develop to fix the  */
/* padding byte issue.                                                                           */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lRxDataPtr  - Buffer to fill in the ARP header                                           */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  lArpHdrPtr - Header to fill with the data received                                           */
/*                                                                                               */
/* return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_BufferToHeader         (  P2VAR( rba_EthArp_Hdr_tst, AUTOMATIC, AUTOMATIC )        lArpHdrPtr,
                                                                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )                   lRxDataPtr)
{
    /* Local variable declaration */
    VAR( uint8, AUTOMATIC ) lLoop_u8;

    /* Report DET if lArpHdrPtr is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lArpHdrPtr ), RBA_ETHARP_E_BUFFER_TO_HEADER_API_ID,     \
                                 RBA_ETHARP_E_NULL_PTR )

    /* Report DET if lRxDataPtr is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lRxDataPtr ), RBA_ETHARP_E_BUFFER_TO_HEADER_API_ID,     \
                                 RBA_ETHARP_E_NULL_PTR )

    (lArpHdrPtr->hwType_u16)    = (uint16)((uint16)((uint16)lRxDataPtr[RBA_ETHARP_HWTYPE] << 8U)    | (uint16)lRxDataPtr[(uint8)RBA_ETHARP_HWTYPE+1]);
    (lArpHdrPtr->protoType_u16) = (uint16)((uint16)((uint16)lRxDataPtr[RBA_ETHARP_PROTOTYPE] << 8U) | (uint16)lRxDataPtr[(uint8)RBA_ETHARP_PROTOTYPE+1]);

    (lArpHdrPtr->hwAddrLen_u8) = (uint8) lRxDataPtr[RBA_ETHARP_HWADDRLENGTH];
    (lArpHdrPtr->protoLen_u8)  = (uint8) lRxDataPtr[RBA_ETHARP_PROTOLENGTH];

    (lArpHdrPtr->arpOpCode_u16)= (uint16) ((uint16)((uint16)lRxDataPtr[RBA_ETHARP_ARPOPCODE] << 8U) | (uint16)lRxDataPtr[(uint8)RBA_ETHARP_ARPOPCODE+1]);

    /* MAC Addresses */
    for (lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
    {
        (lArpHdrPtr->srcHwAddr_au8[lLoop_u8] ) = (uint8) lRxDataPtr[lLoop_u8 + (uint8)RBA_ETHARP_SRCHWADDR];
        (lArpHdrPtr->destHwAddr_au8[lLoop_u8]) = (uint8) lRxDataPtr[lLoop_u8 + (uint8)RBA_ETHARP_DSTHWADDR];
    }

    /* IP Addresses */
    (lArpHdrPtr->srcIpAddr_u32)= (uint32)(  (uint32)((uint32)lRxDataPtr[RBA_ETHARP_SRCIPADDR ] << 24U ) |
                                            (uint32)((uint32)lRxDataPtr[(uint8)RBA_ETHARP_SRCIPADDR + 1 ] << 16U ) |
                                            (uint16)((uint16)lRxDataPtr[(uint8)RBA_ETHARP_SRCIPADDR + 2 ] << 8U  ) |
                                            (uint16)((uint16)lRxDataPtr[(uint8)RBA_ETHARP_SRCIPADDR + 3 ]  ) );

    (lArpHdrPtr->destIpAddr_u32)= (uint32)( (uint32)((uint32)lRxDataPtr[RBA_ETHARP_DSTIPADDR ]    << 24U ) |
                                            (uint32)((uint32)lRxDataPtr[(uint8)RBA_ETHARP_DSTIPADDR + 1 ] << 16U ) |
                                            (uint16)((uint16)lRxDataPtr[(uint8)RBA_ETHARP_DSTIPADDR + 2 ] << 8U  ) |
                                            (uint16)((uint16)lRxDataPtr[(uint8)RBA_ETHARP_DSTIPADDR + 3 ]  ) );
}

/*************************************************************************************************/
/* rba_EthArp_HeaderToBuffer() -                                                                 */
/* Function called to fill the buffer to send with the header frame previously filled.           */
/* Function implement to fix the padding byte issue.                                             */
/*                                                                                               */
/* Input Parameters :                                                                            */
/*  lEthArpPtr_t - Header to fill in the buffer                                                  */
/*                                                                                               */
/* Output Parameters :                                                                           */
/*  lTxData_pu8 - TxBuffer to fill with the data contained into the Structure                    */
/*                                                                                               */
/* return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void ,            RBA_ETHARP_CODE ) rba_EthArp_HeaderToBuffer         ( P2CONST( rba_EthArp_Hdr_tst, AUTOMATIC, AUTOMATIC )   lEthArpPtr_t,
                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  lTxData)
{
    /* Local variable declaration */
    VAR( uint8, AUTOMATIC ) lLoop_u8;

    /* Report DET if lEthArpPtr_t is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lEthArpPtr_t ), RBA_ETHARP_E_HEADER_TO_BUFFER_API_ID,     \
                                     RBA_ETHARP_E_NULL_PTR )

    /* Report DET if lTxData is a Null Pointer */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == lTxData ), RBA_ETHARP_E_HEADER_TO_BUFFER_API_ID,     \
                                     RBA_ETHARP_E_NULL_PTR )

    lTxData[RBA_ETHARP_HWTYPE]      = ( uint8 ) ( lEthArpPtr_t->hwType_u16 >> 8U ) ;
    lTxData[(uint8)RBA_ETHARP_HWTYPE+1]    = ( uint8 ) ( lEthArpPtr_t->hwType_u16 ) ;

    lTxData[RBA_ETHARP_PROTOTYPE]          = ( uint8 ) ( lEthArpPtr_t->protoType_u16 >> 8U ) ;
    lTxData[(uint8)RBA_ETHARP_PROTOTYPE+1] = ( uint8 ) ( lEthArpPtr_t->protoType_u16 ) ;

    lTxData[RBA_ETHARP_HWADDRLENGTH]= ( uint8 ) ( lEthArpPtr_t->hwAddrLen_u8 ) ;
    lTxData[RBA_ETHARP_PROTOLENGTH] = ( uint8 ) ( lEthArpPtr_t->protoLen_u8 ) ;

    lTxData[RBA_ETHARP_ARPOPCODE]          = ( uint8 ) ( lEthArpPtr_t->arpOpCode_u16 >> 8U) ;
    lTxData[(uint8)RBA_ETHARP_ARPOPCODE+1] = ( uint8 ) ( lEthArpPtr_t->arpOpCode_u16 ) ;

    /* MAC Addresses */
    for (lLoop_u8 = 0; lLoop_u8 < RBA_ETHARP_HWADDR_LENGTH; lLoop_u8++)
    {
        lTxData[lLoop_u8 + (uint8)RBA_ETHARP_SRCHWADDR] = (uint8) ( lEthArpPtr_t->srcHwAddr_au8[lLoop_u8] );
        lTxData[lLoop_u8 + (uint8)RBA_ETHARP_DSTHWADDR] = (uint8) ( lEthArpPtr_t->destHwAddr_au8[lLoop_u8]);
    }

    /* IP Addresses */
    lTxData[RBA_ETHARP_SRCIPADDR]          = (uint8) ( lEthArpPtr_t->srcIpAddr_u32 >> 24U);
    lTxData[(uint8)RBA_ETHARP_SRCIPADDR+1] = (uint8) ( lEthArpPtr_t->srcIpAddr_u32 >> 16U);
    lTxData[(uint8)RBA_ETHARP_SRCIPADDR+2] = (uint8) ( lEthArpPtr_t->srcIpAddr_u32 >> 8U );
    lTxData[(uint8)RBA_ETHARP_SRCIPADDR+3] = (uint8) ( lEthArpPtr_t->srcIpAddr_u32 );

    lTxData[RBA_ETHARP_DSTIPADDR]          = (uint8) ( lEthArpPtr_t->destIpAddr_u32 >> 24U);
    lTxData[(uint8)RBA_ETHARP_DSTIPADDR+1] = (uint8) ( lEthArpPtr_t->destIpAddr_u32 >> 16U);
    lTxData[(uint8)RBA_ETHARP_DSTIPADDR+2] = (uint8) ( lEthArpPtr_t->destIpAddr_u32 >> 8U );
    lTxData[(uint8)RBA_ETHARP_DSTIPADDR+3] = (uint8) ( lEthArpPtr_t->destIpAddr_u32 );
}
#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

