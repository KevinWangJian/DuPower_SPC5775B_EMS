

#ifndef RBA_ETHARP_TYPES_H
#define RBA_ETHARP_TYPES_H

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

/*
****************************************************************************************************
* 									Structures
****************************************************************************************************
*/

#define RBA_ETHARP_HWADDR_LENGTH                6U
#define RBA_ETHARP_IPADDR_LENGTH                4U

/* ARP Table entries state */
typedef enum
{
	RBA_ETHARP_FREE_ENTRY  = 1,			/* State of the entry when she is free/not used in the process */
	RBA_ETHARP_REQ_TO_BE_SENT,			/* State of the entry when a ARP request must be sent. This state appears when we cannot send the frame to the first time */
	RBA_ETHARP_RPLY_TO_BE_SENT,         /* State of the entry when a ARP reply must be sent for the ARP request received. */
	RBA_ETHARP_RPLY_PENDING,			/* State of the entry when a request have been sent and that we are waiting a Reply */
	RBA_ETHARP_ENTRY_USED,				/* State of the entry when she is complete (IP and MAC address) */
	RBA_ETHARP_TIME_OUT,				/* State of the entry when she is Timed Out */
	RBA_ETHARP_CONFLICT_DETECTED		/* State of the entry when a conflict is detected for the Assigned Ip Addr. Gratuitous Frame shall be triggered in the next mainfunction to defend the Ip Address*/
}rba_EthArp_ArpTableEntryState_ten;

typedef enum
{
	RBA_ETHARP_ETHADDR_INIT		= 0,
	RBA_ETHARP_ETHADDR_MATCH,
	RBA_ETHARP_ETHADDR_NO_MATCH
}rba_EthArp_EthAddrMatch_ten;

/* ARP message format */
typedef struct
{
	uint32			srcIpAddr_u32;
	uint32			destIpAddr_u32;
	uint16          hwType_u16;
	uint16          protoType_u16;
	uint16          arpOpCode_u16;
	uint8           hwAddrLen_u8;
	uint8           protoLen_u8;
	uint8	      	srcHwAddr_au8[RBA_ETHARP_HWADDR_LENGTH];
	uint8      		destHwAddr_au8[RBA_ETHARP_HWADDR_LENGTH];
}rba_EthArp_Hdr_tst;

/*
 * Bytes ARP Header Frame.
 * Enum used to fill the ARP header byte by byte.
 */
typedef enum
{
	RBA_ETHARP_HWTYPE 			= 0, /* Byte 0 + Byte 1 */
	RBA_ETHARP_PROTOTYPE 		= 2, /* Byte 2 + Byte 3 */
	RBA_ETHARP_HWADDRLENGTH 	= 4, /* Byte 4 */
	RBA_ETHARP_PROTOLENGTH 		= 5, /* Byte 5 */
	RBA_ETHARP_ARPOPCODE	 	= 6, /* Byte 6 + Byte 7 */
	RBA_ETHARP_SRCHWADDR	 	= 8, /* Byte 8 + Byte 9 + Byte 10 + Byte 11 + Byte 12 + Byte 13 */
	RBA_ETHARP_SRCIPADDR	 	= 14,/* Byte 14 + Byte 15 + Byte 16 + Byte 17 */
	RBA_ETHARP_DSTHWADDR	 	= 18,/* Byte 18 + Byte 19 + Byte 20 + Byte 21 + Byte 22 + Byte 23 */
	RBA_ETHARP_DSTIPADDR	 	= 24 /* Byte 24 + Byte 25 + Byte 26 + Byte 27 */
} rba_EthArp_HdrByte_ten ;

/* ARP Table Entry
 * Struct that contains the specific parameters to strore for one entry */
typedef struct
{
	rba_EthArp_ArpTableEntryState_ten	procEntryState_en;							/* Empty / Used / Pending 					*/
	TcpIp_IPv4AddrType_ten				procIpAddrType_en;							/* Ip Type : Dynamic or Static Ip			*/
	TcpIp_IpAddrAssignmentType          procIpAssignMeth_en;                        /* IP assignment method. Required for IP conflict Detection */
	uint32								destIpAddr_u32;								/* IP address 								*/
    uint32          					procTimeOutEntryCnt_u32;					/* Time during which the frame is not used	*/
    uint16          					procTxFrameCnt_u16;							/* Counter of frames send for a request 	*/
    uint8		    					destHwAddr_au8[RBA_ETHARP_HWADDR_LENGTH];	/* Ethernet MAC address 					*/
}rba_EthArp_ArpTable_tst;

/*
 * This container is a sub-container of rba_EthArp_Config_to and defines the
 * specific configuration parameters of the ARP (Address Resolution Protocol) sub-module
 */
typedef struct
{
	rba_EthArp_ArpTable_tst 	    * ArpTable_past;                                     /* Pointer to ARP table                                               */
    const uint8                     AgeingDisabled_cu8;                                  /* Enable/Disable ageing of Arp Table Entries                         */
	const uint8						EthIfCtrIdx_cu8;                                     /* Controller Index to match with the ARP Table                       */
	const uint8                     TcpIpCtrlFramePrio_cu8;                              /* Frame priority configured per TcpIpCtrl (TcpIpIpFramePrioDefault)  */
}rba_EthArp_SubConfig_to;

/*
 * This container is a sub-container of TcpIpConfig and specifies the
 * configuration parameters of the ARP (Address Resolution Protocol) sub-module
 */
typedef struct
{

	const rba_EthArp_SubConfig_to 	* ArpSubConfig_past;                            /* Pointer to ARP table */
	uint32						    TableEntryTimeout_u32;                          /* Timeout in milliseconds after which an unused ARP entry is removed ( TcpIpArpTableEntryTimeout ) */
    uint32						    TablePendingEntryTimeout_u32;                   /* Timeout in milliseconds after which an unused pending ARP entry is removed (TcpIpArpTblPendingEntryTimeout) */
	uint16						    TableSizeMax_u16;                               /* Maximum number of entries in the ARP table */
	uint16						    MaxRequests_u16;                                /* RB specific parameter: Maximum number of ARP requests that can be sent for a particular destination IP address. */
	uint8						    NumArpTbl_u8;                                   /* Number of ARP Table configured */
	uint8						    NumGratARPonStartup_u8;                         /* Specifies the number of gratuitous ARP replies which shall be sent on assignment of a new IP address (TcpIpArpNumGratuitousARPonStartup) */
}rba_EthArp_Config_to;

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHARP_TYPES_H */

