

#include "TcpIp.h"

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

#include "rba_EthArp.h"

#if ( TCPIP_AUTOIP_ENABLED == STD_ON )
#include "rba_EthAutoIp.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#include "rba_EthArp_Prv.h"

/* DET version check */
#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* ( TCPIP_DEV_ERROR_DETECT != STD_OFF ) */

#define RBA_ETHARP_START_SEC_VAR_INIT_8
#include "rba_EthArp_MemMap.h"
/* Flag to indicate whether rba_EthArp_Init has been executed or not */
VAR( boolean, AUTOMATIC ) rba_EthArp_InitFlag_b = FALSE;
#define RBA_ETHARP_STOP_SEC_VAR_INIT_8
#include "rba_EthArp_MemMap.h"

#define RBA_ETHARP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"
/* Pointer - will be initialized in the Init Function */
P2CONST( rba_EthArp_Config_to, AUTOMATIC, AUTOMATIC )   rba_EthArp_ConfigPtr_pco;
#define RBA_ETHARP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
/*
****************************************************************************************************
*                                   Prototype static Functions
****************************************************************************************************
*/

LOCAL_INLINE void  rba_EthArp_Proc_ReqToBeSent (      P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,  P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst,     VAR( uint16, AUTOMATIC )           rba_EthArp_EntryLoop_u16);

LOCAL_INLINE void  rba_EthArp_Proc_ReplyToBeSent (      P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,  P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst,     VAR( uint16, AUTOMATIC )           rba_EthArp_EntryLoop_u16);

LOCAL_INLINE void  rba_EthArp_Proc_ReplyPending (      P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst );

LOCAL_INLINE void  rba_EthArp_Proc_EntryUsed (         P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst);

LOCAL_INLINE void  rba_EthArp_Proc_ConflictDetect (   P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,  P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst);

/*
****************************************************************************************************
****************************************************************************************************
*/



/*************************************************************************************************/
/* rba_EthArp_Init() - Initialize ARP table                                                      */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_Config_cst        - Configuration data of the ARP module.                          */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
FUNC( void,                 RBA_ETHARP_CODE )   rba_EthArp_Init (
                                                        P2CONST( rba_EthArp_Config_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_Config_cst )
{
/* Local variable declaration */
P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
VAR( uint16, AUTOMATIC )    lTableEntryLoop_u16;
VAR( uint8, AUTOMATIC ) lTableLoop_u8;

    /* Initialise the Init flag */
    rba_EthArp_InitFlag_b   = FALSE;
    rba_EthArp_ConfigPtr_pco = NULL_PTR;

    /* Report DET if TcpIp_CurrConfig_pco is not intialized */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == TcpIp_CurrConfig_pco ),                                        \
                                          RBA_ETHARP_E_INIT_API_ID, RBA_ETHARP_E_INIT_FAILED )


    /* Report DET if rba_EthArp_Config_cst does not contain a valid configuration */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( rba_EthArp_Config_cst != ( TcpIp_CurrConfig_pco->EthArpConfig_pco) ),      \
                                          RBA_ETHARP_E_INIT_API_ID, RBA_ETHARP_E_INV_ARG )

    /* Copy General ARP structure into the local structure */
    rba_EthArp_ConfigPtr_pco = rba_EthArp_Config_cst;
    /***************************************************************/

    /* Initialize all the entries as free entries */
    /* Initialize the entire ARP table. */

    for( lTableLoop_u8 = 0; lTableLoop_u8 < ( rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ); lTableLoop_u8++ )
    {
        /* Local Copy of the ARP Sub-Config Struct */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        for( lTableEntryLoop_u16 = 0; lTableEntryLoop_u16 < ( rba_EthArp_ConfigPtr_pco->TableSizeMax_u16 ); lTableEntryLoop_u16++ )
        {
            /* Initialize state of the entry (free entry )*/
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].procEntryState_en        = RBA_ETHARP_FREE_ENTRY;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].procIpAddrType_en        = TCPIP_SUBNET_EXT_IPV4ADDR;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destIpAddr_u32           = 0;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].procTimeOutEntryCnt_u32  = 0;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].procTxFrameCnt_u16       = 0;

            /* Initialize MAC Address value */
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[0] = 0x00 ;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[1] = 0x00 ;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[2] = 0x00 ;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[3] = 0x00 ;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[4] = 0x00 ;
            lArpSubCfg_pco->ArpTable_past[lTableEntryLoop_u16].destHwAddr_au8[5] = 0x00 ;
        }
    }

    /* Initialize with Autosar configuration */
    /* rba_EthArp_ArpConfig_cs.ArpNumGratuitousARPonStartup_u8; */

    /* Flag to indicate that ARP init function have been called */
    rba_EthArp_InitFlag_b = TRUE;

}

/*************************************************************************************************/
/* rba_EthArp_MainFunction() - Function called by an OS_Schedul_Task.                            */
/* This function is called to update the ARP Table, clean entries if necessary (TimeToLive of    */
/* the entries overtime ) and to check  if an ARP frame must be send (ARP Reply / ARP            */
/* Request / ARP Gratuitous.                                                                     */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* param    - void                                                                               */
/* return   - void                                                                               */
/*                                                                                               */
/*************************************************************************************************/
FUNC( void, RBA_ETHARP_CODE ) rba_EthArp_MainFunction ( void )
{
    /* Local variable declaration */
    P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) lArpSubCfg_pco;
    P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   lArpTableEntry_pst;

    VAR( uint16, AUTOMATIC )                            lEntryLoop_u16;
    VAR( uint8, AUTOMATIC )                             lTableLoop_u8;
    VAR( rba_EthArp_ArpTableEntryState_ten, AUTOMATIC ) lEntryState_en;

    /* Local variable initialization */
    lEntryState_en  = RBA_ETHARP_FREE_ENTRY;

    /* Check for DET errors */
    /* Report DET if rba_EthArp module is uninitialised */
    RBA_ETHARP_DET_REPORT_ERROR_RET_VOID( ( FALSE == rba_EthArp_InitFlag_b ), RBA_ETHARP_E_MAIN_FUNCTION_API_ID,     \
                                          RBA_ETHARP_E_NOTINIT )

    /* Go through the Table */
    for(lTableLoop_u8 = 0; ( lTableLoop_u8 < ( rba_EthArp_ConfigPtr_pco->NumArpTbl_u8 ) ); lTableLoop_u8++ )
    {
        /* Local Copy of the ARP SubConfig Structure */
        lArpSubCfg_pco = &rba_EthArp_ConfigPtr_pco->ArpSubConfig_past[lTableLoop_u8];

        /* Loop through the ARP Table Entries */
        for( lEntryLoop_u16 = 0; (lEntryLoop_u16 < ( rba_EthArp_ConfigPtr_pco->TableSizeMax_u16 )); lEntryLoop_u16++ )
        {
            /* Local Copy of the ARP Table Entry */
            lArpTableEntry_pst = &lArpSubCfg_pco->ArpTable_past[lEntryLoop_u16];

            /* State of the ARP Table entry */
            lEntryState_en = lArpTableEntry_pst->procEntryState_en;

            switch ( lEntryState_en )
            {
                /* The Entry is FREE*/
                case RBA_ETHARP_FREE_ENTRY :
                {
                    /* Nothing to Do */
                }
                break;

                /* If entry have to send an ARP Request */
                case RBA_ETHARP_REQ_TO_BE_SENT :
                {

                    rba_EthArp_Proc_ReqToBeSent (      lArpSubCfg_pco,
                                                       lArpTableEntry_pst,
                                                       lEntryLoop_u16 );
                }
                break;

                /* If entry have to send an ARP Reply */
                case RBA_ETHARP_RPLY_TO_BE_SENT :
                {
                    rba_EthArp_Proc_ReplyToBeSent (    lArpSubCfg_pco,
                                                       lArpTableEntry_pst,
                                                       lEntryLoop_u16 );
                }
                break;

                /* If entry is waiting for an ARP Reply */
                case RBA_ETHARP_RPLY_PENDING :
                {
                    rba_EthArp_Proc_ReplyPending (     lArpTableEntry_pst );
                }
                break;

                /* If entry is used by an Ip Address */
                case RBA_ETHARP_ENTRY_USED :
                {

                    rba_EthArp_Proc_EntryUsed (        lArpTableEntry_pst);
                }
                break;

                /* If state entry is Time Out */
                case RBA_ETHARP_TIME_OUT :
                {
                    /* Remove the entry */
                    rba_EthArp_CleanArpTableEntry( lArpTableEntry_pst );
                }
                break;

                /* If state entry is Conflict detected*/
                case RBA_ETHARP_CONFLICT_DETECTED :
                {

                    rba_EthArp_Proc_ConflictDetect (  lArpSubCfg_pco,
                                                      lArpTableEntry_pst) ;
                }
                break;

                default :
                    /*Nothing to do*/
                break;
            }
        }/* End FOR Entry Loop*/
    }/* End FOR Table Loop*/


}


/*************************************************************************************************/
/* rba_EthArp_Proc_ReqToBeSent() - Process the Request to be sent                                */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_SubCfg_pco            - Sub Configuration data of the ARP module.                  */
/* rba_EthArp_TableEntry_pst        - Pointer to the table entry                                 */
/* rba_EthArp_EntryLoop_u16         - Entry loop value                                           */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
LOCAL_INLINE void  rba_EthArp_Proc_ReqToBeSent (      P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,
                                                      P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst,
                                                      VAR( uint16, AUTOMATIC )           rba_EthArp_EntryLoop_u16)
{
    VAR( uint32, AUTOMATIC )                            lDestIPv4Addr_u32;
    VAR( uint8, AUTOMATIC )                             lCtrlIdx_u8;
    VAR( uint8, AUTOMATIC )                             lDestEthAddr[RBA_ETHARP_HWADDR_LENGTH];
    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_tu8;

    /* SWS_ RB_ARP _00011 : */
    /* If EthIf_ProvideTxBuffer returns with BUSY, the function */
    /* shall be called in the next ARP_MainFunction again */

    /* If number of attempt didn't exceed max number */
    if( ( rba_EthArp_ConfigPtr_pco->MaxRequests_u16 ) > (rba_EthArp_TableEntry_pst->procTxFrameCnt_u16))
    {
        /* Get controller index and IP Address store in the ARP Table */
        lCtrlIdx_u8         = rba_EthArp_SubCfg_pco->EthIfCtrIdx_cu8;
        lDestIPv4Addr_u32   = rba_EthArp_TableEntry_pst->destIpAddr_u32;

        /* Get MAC Address */
        rba_EthArp_GetEthAddrInTableEntry( rba_EthArp_TableEntry_pst, ( uint8 *) &lDestEthAddr[0]);

        /* Send an ARP Request Frame */
        lRetVal_tu8 = rba_EthArp_SendArpFrame(
                            lCtrlIdx_u8,
                            rba_EthArp_EntryLoop_u16,
                            lDestIPv4Addr_u32,
                            ( const uint8 *) &lDestEthAddr[0],
                            RBA_ETHARP_ARP_REQUEST_FRAME);

        if(E_OK == lRetVal_tu8)
        {
            /* If frame sent : counter updated */
            /* The state of the entry is modified in rba_EthArp_SendArpFrame() */
            /* the new state will be RBA_ETHARP_RPLY_PENDING */
            rba_EthArp_TableEntry_pst->procTxFrameCnt_u16++;
        }
        else
        {
            /* We keep the same State to retransmit the ARP REQUEST */
        }
    }
    else
    {
        /* No ARP REPLY has been received. */
        /* The number of attempt exceeds max number (ArpMaxRequests_u16) : we delete the entry.*/

        /* TIME OUT => The entry is removed */
        rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_TIME_OUT;
    }
}


/*************************************************************************************************/
/* rba_EthArp_Proc_ReplyToBeSent() - Process the Reply to be sent                                */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_SubCfg_pco            - Sub Configuration data of the ARP module.                  */
/* rba_EthArp_TableEntry_pst        - Pointer to the table entry                                 */
/* rba_EthArp_EntryLoop_u16         - Entry loop value                                           */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
LOCAL_INLINE void  rba_EthArp_Proc_ReplyToBeSent (     P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,
                                                       P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst,
                                                       VAR( uint16, AUTOMATIC )           rba_EthArp_EntryLoop_u16)
{
    VAR( uint32, AUTOMATIC )                            lDestIPv4Addr_u32;
    VAR( uint8, AUTOMATIC )                             lCtrlIdx_u8;
    VAR( uint8, AUTOMATIC )                             lDestEthAddr[RBA_ETHARP_HWADDR_LENGTH];
    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_tu8;

    /* Get controller index and IP Address */
    lCtrlIdx_u8         = rba_EthArp_SubCfg_pco->EthIfCtrIdx_cu8;
    lDestIPv4Addr_u32   = rba_EthArp_TableEntry_pst->destIpAddr_u32;

    /* Get MAC Address */
    rba_EthArp_GetEthAddrInTableEntry( rba_EthArp_TableEntry_pst, ( uint8 *) &lDestEthAddr[0]);

    /* Send an ARP Reply Frame */
    lRetVal_tu8 = rba_EthArp_SendArpFrame(
                                lCtrlIdx_u8,
                                rba_EthArp_EntryLoop_u16,
                                lDestIPv4Addr_u32,
                                ( const uint8 *) &lDestEthAddr[0],
                                RBA_ETHARP_ARP_REPLY_FRAME);

    if(E_OK == lRetVal_tu8)
    {
        /* If frame sent : the new state will be RBA_ETHARP_ENTRY_USED */
        rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_ENTRY_USED;
    }
    else
    {
        /* We keep the same State to retransmit the ARP REPLY */
    }

    /* We cannot remove Internal Ip Addresses */
    if( TCPIP_SUBNET_INT_IPV4ADDR != rba_EthArp_TableEntry_pst->procIpAddrType_en )
    {
        /* update Time To Live (TICK) */
        rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32++;
        /* If overtime */
        if(( rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32 * RBA_ETHARP_MAINCYCLE_TIME ) >= rba_EthArp_ConfigPtr_pco->TableEntryTimeout_u32 )
        {
            /* TIME OUT => The entry is removed */
            rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_TIME_OUT;
        }
    }
}



/*************************************************************************************************/
/* rba_EthArp_Proc_ReplyPending() - Process the Reply pending                                    */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_TableEntry_pst        - Pointer to the table entry                                 */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
LOCAL_INLINE void  rba_EthArp_Proc_ReplyPending (   P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst )
{
    /* update Time To Live (TICK)*/
    rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32++;
    /* Time to Live exceeded ? */
    if(( rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32 * RBA_ETHARP_MAINCYCLE_TIME ) >= rba_EthArp_ConfigPtr_pco->TablePendingEntryTimeout_u32 )
    {
        /* Go back to the previous state to resend an ARP REQUEST */
        rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_REQ_TO_BE_SENT;
        /* Reset Time To Live for the next Step */
        rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32 = 0;
    }
    else
    {
        /* Nothing to do */
    }

}



/*************************************************************************************************/
/* rba_EthArp_Proc_EntryUsed() - Process the Entry Used state                                    */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_TableEntry_pst        - Pointer to the table entry                                 */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
LOCAL_INLINE void  rba_EthArp_Proc_EntryUsed (      P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst)
{

    /* We cannot remove Internal Ip Addresses */
    if( TCPIP_SUBNET_INT_IPV4ADDR != rba_EthArp_TableEntry_pst->procIpAddrType_en )
    {
        /* update Time To Live (TICK) */
        rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32++;
        /* If overtime */
        if(( rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32 * RBA_ETHARP_MAINCYCLE_TIME ) >= rba_EthArp_ConfigPtr_pco->TableEntryTimeout_u32 )
        {
            /* TIME OUT => The entry is removed */
            rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_TIME_OUT;
        }
    }

}


/*************************************************************************************************/
/* rba_EthArp_Proc_ConflictDetect() - Process the Conflict detected State                        */
/*                                                                                               */
/* Input Parameters :                                                                            */
/* rba_EthArp_SubCfg_pco            - Sub Configuration data of the ARP module.                  */
/* rba_EthArp_TableEntry_pst        - Pointer to the table entry                                 */
/*                                                                                               */
/* return   - void                                                                               */
/*************************************************************************************************/
LOCAL_INLINE void  rba_EthArp_Proc_ConflictDetect (   P2CONST( rba_EthArp_SubConfig_to, AUTOMATIC, AUTOMATIC ) rba_EthArp_SubCfg_pco,  P2VAR( rba_EthArp_ArpTable_tst, AUTOMATIC, AUTOMATIC )   rba_EthArp_TableEntry_pst)
{
    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_tu8;
    VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC)         lAssignMeth_en;

    /* update Time To Live (TICK) */
    rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32++;
    /* If overtime */
    if(rba_EthArp_TableEntry_pst->procTimeOutEntryCnt_u32 >= (uint32) rba_EthArp_ConfigPtr_pco->TableEntryTimeout_u32 )
    {
        /* TIME OUT => The entry is removed */
        rba_EthArp_TableEntry_pst->procEntryState_en = RBA_ETHARP_TIME_OUT;
    }

    /* Get the IP address assignment method */
     lAssignMeth_en = rba_EthArp_TableEntry_pst->procIpAssignMeth_en;

    switch ( lAssignMeth_en )
    {

        case TCPIP_IPADDR_ASSIGNMENT_STATIC:
        {
            /* The IP Address must be defended by the ARP Component by sending Gratuitous Frames */
            lRetVal_tu8 = rba_EthArp_SendArpGratuitousFrame( rba_EthArp_SubCfg_pco->EthIfCtrIdx_cu8, rba_EthArp_TableEntry_pst->destIpAddr_u32);

            if(E_OK == lRetVal_tu8)
            {
                /* If frame sent : Remove the entry from the ARP table, */
                /* the new state will be RBA_ETHARP_FREE_ENTRY */
                rba_EthArp_CleanArpTableEntry( rba_EthArp_TableEntry_pst );
            }
            else
            {
                /* We keep the same State to retransmit the Gratuitous Frames */
            }
        }
        break;

        case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL:
        case TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP:
        {
            #if (TCPIP_AUTOIP_ENABLED == STD_ON)
            /* Inform the AutoIp Component of the conflict */
            (void)rba_EthAutoIp_IpConflictDetected (rba_EthArp_SubCfg_pco->EthIfCtrIdx_cu8);
            #endif
            /* If frame sent : Remove the entry from the ARP table, */
            /* the new state will be RBA_ETHARP_FREE_ENTRY */
            rba_EthArp_CleanArpTableEntry( rba_EthArp_TableEntry_pst );
        }
        break;

        case TCPIP_IPADDR_ASSIGNMENT_DHCP:
        {
            #if (TCPIP_DHCP_CLIENT_ENABLED == STD_ON)
            /* Inform the DHCP Component of the conflict */
            (void)rba_EthDHCP_IpConflictDetected (rba_EthArp_SubCfg_pco->EthIfCtrIdx_cu8);
            #endif
            /* If frame sent : Remove the entry from the ARP table, */
            /* the new state will be RBA_ETHARP_FREE_ENTRY */
            rba_EthArp_CleanArpTableEntry( rba_EthArp_TableEntry_pst );
        }
        break;

        default:
            /*Nothing to do*/
        break;

    }

}


#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */


