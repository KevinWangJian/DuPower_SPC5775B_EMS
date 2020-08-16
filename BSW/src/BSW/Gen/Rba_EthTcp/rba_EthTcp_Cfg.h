/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/

        

#ifndef RBA_ETHTCP_CFG_H
#define RBA_ETHTCP_CFG_H

/*
 *************************************************************************************************
 * Defines
 *************************************************************************************************
 */

/* -------------------------------------------- */
/* Features activation 							*/
/* -------------------------------------------- */

/* Enables (TRUE) or disables (FALSE) support of TCP congestion avoidance algorithm according to IETF RFC 5681 */
#define RBA_ETHTCP_CONGESTIONAVOIDANCE_ENABLED          (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Fast Recovery according to IETF RFC 5681 */
#define RBA_ETHTCP_FASTRECOVERY_ENABLED                 (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Fast Retransmission according to IETF RFC 5681 */
#define RBA_ETHTCP_FASTRETRANSMIT_ENABLED               (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Keep Alive Probes according to IETF RFC 1122 chapter 4.2.3.6 */
#define RBA_ETHTCP_KEEP_ALIVE_ENABLED                   (STD_ON)

/* Enables (TRUE) or disables (FALSE) support of Nagle algorithm according to IETF RFC 1122 chapter 4.2.3.4 */
#define RBA_ETHTCP_NAGLE_ENABLED						(STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP slow start algorithm according to IETF RFC 5681 */
#define RBA_ETHTCP_SLOWSTART_ENABLED					(STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Maximum Segment Size option sending according to IETF RFC 1122 chapter 4.2.2.6 */
#define RBA_ETHTCP_MSS_ENABLED                          (STD_ON)

/* Enables (TRUE) or disables (FALSE) support of TCP Delayed ACK according to IETF RFC 1122 chapter 4.2.3.2 */
#define RBA_ETHTCP_DLYACK_ENABLED                       (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Retransmission feature according to IETF RFC 1122 chapter 4.2.2.15 */
#define RBA_ETHTCP_RETX_ENABLED                         (STD_ON)

/* Enables (TRUE) or disables (FALSE) support of TCP Dynamic ReTransmission according to IETF RFC 6298 */
#define RBA_ETHTCP_DYNAMIC_RETX_TIMER					(STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP Zero Window Probes according to IETF RFC 1122 chapter 4.2.2.17 */
#define RBA_ETHTCP_ZWP_ENABLED                         	(STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of TCP User Timeout according to IETF RFC 5482 */
#define RBA_ETHTCP_USER_TIMEOUT_ENABLED                 (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of Half Duplex Close according to IETF RFC 1122 chapter 4.2.2.13 */
#define RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED				(STD_ON)

/* Enables (TRUE) or disables (FALSE) support of checksum calculation on reception */
#define RBA_ETHTCP_SW_CHKSUM_RX		                   	(STD_ON)

/* Provides the information about enable/disable of the IPv4 reassembly. */
#define RBA_ETHTCP_REASSMBLY_RX_ENABLED                 (STD_OFF)

/* Enables (TRUE) or disables (FALSE) support of checksum calculation on transmission */
#define RBA_ETHTCP_SW_CHKSUM_TX		                   	(STD_ON)

/* Enables (TRUE) or disables (FALSE) the generation of Initial Sequence Number using Pseudo Random method */
#define RBA_ETHTCP_ISN_PSEUDO_RANDOM_ENABLED            (STD_ON)

/* Enables (TRUE) or disables (FALSE) the generation of Initial Sequence Number using Clock Driven method according to IETF RFC 793 chapter 3.3 and IETF RFC 1122 chapter 4.2.2.9 */
#define RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED             (STD_OFF)

/* Enables (TRUE) or disables (FALSE) the generation of Initial Sequence Number using Cryptographic method according to IETF RFC 6528 chapter 3 */
#define RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED         (STD_OFF)


/* -------------------------------------------- */
/* Configuration values 						*/
/* -------------------------------------------- */

/* Number of local address id's configured */
#define RBA_ETHTCP_MAX_LOCALADDRID                      1U

/* TCP Internal TX Buffer Size */
#define RBA_ETHTCP_TXWNDSIZE							2048U

/* Default MSS - Maximum Segment Size assumed for the remote when the remote does not advertise its MSS */
#define RBA_ETHTCP_DFL_MSS								1024U /* MTU - RBA_ETHTCP_DFL_HDRLENGTH - RBA_ETHIPV4_HDRLENGTH */

/* Coefficients for dynamic RTO calculation (Jacobson's algorithm) */
#define RBA_ETHTCP_WEIGHT_SRTT      					125U
#define RBA_ETHTCP_WEIGHT_RTTVAR    					250U

/* Maximum number of time the ISN secret can be used (after this maximum usage, the secret need to be changed to keep protection) - This is used for Cryptographic method */
#define RBA_ETHTCP_ISN_MAX_SECRET_USAGE                 100U


#endif  /* RBA_ETHTCP_CFG_H */

