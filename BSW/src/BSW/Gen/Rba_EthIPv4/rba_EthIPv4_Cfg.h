/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/



/*<VersionHead>
 ***************************************************************************************************
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: rba_EthIPv4 / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4          	  ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#ifndef RBA_ETHIPV4_CFG_H
#define RBA_ETHIPV4_CFG_H

/*
 *************************************************************************************************
 * Defines
 *************************************************************************************************
 */                                 

#define RBA_ETHIPV4_DEV_ERROR_DETECT               		(STD_ON)    /* STD_ON/STD_OFF:DET is enabled/disabled  for IPv4 */       

#define RBA_ETHIPV4_SW_CHKSUM_RX				        (STD_ON)    /* STD_ON/STD_OFF: IPV4 checksum is verified by software/hardware for the received frame */

#define RBA_ETHIPV4_SW_CHKSUM_TX_IPV4 					(STD_ON)    /* STD_ON/STD_OFF: IPv4 checksum is calculated by software/hardware for the frame to be transmitted */

#define RBA_ETHIPV4_SW_CHKSUM_TX_UDP                    (STD_ON)    /* STD_ON/STD_OFF: UDP checksum is calculated by software/hardware for the frame to be transmitted  */

#define RBA_ETHIPV4_SW_CHKSUM_TX_ICMP                   (STD_ON)    /* STD_ON/STD_OFF: ICMP checksum is calculated by software/hardware for the frame to be transmitted  */

#define RBA_ETHIPV4_SW_CHKSUM_RX_UDP                     (STD_ON)        /* STD_ON/STD_OFF: UDP checksum is verified by software/hardware for the received frame */

#define RBA_ETHIPV4_SW_CHKSUM_RX_ICMP                    (STD_ON)        /* STD_ON/STD_OFF: UDP checksum is verified by software/hardware for the received frame */

#define RBA_ETHIPV4_FRAG_ENABLED                        (STD_OFF)    /* STD_ON/STD_OFF: Fragmentation is enabled/disabled for any of the IPv4 controller */

#define RBA_ETHIPV4_REASSEMBLY_ENABLED                  (STD_OFF)    /* STD_ON/STD_OFF: Reassembly is enabled/disabled for any of the IPv4 controller */

#endif  /* RBA_ETHIPV4_CFG_H */


