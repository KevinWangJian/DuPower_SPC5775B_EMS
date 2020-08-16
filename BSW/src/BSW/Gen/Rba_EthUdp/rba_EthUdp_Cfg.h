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
 * $Generator__: rba_EthUdp / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4          	  ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#ifndef RBA_ETHUDP_CFG_H
#define RBA_ETHUDP_CFG_H

/*
 *************************************************************************************************
 * Defines
 *************************************************************************************************
 */

/* DD: The checksum validation for an UDP-over-IPv6 received frame is performed in the UDP Rx Indication API. 
 * The reason for the change from IPv4 is the fact that there is no checksum calculation at IPv6 level. 
 * Therefore, most of the upper layer protocols are performing by their own the checksum validation/update. 
 * Note: If hardware checksum for UDP is not supported, software checksum will not be enabled if Scalability Class is 1 (IPv4 only). */
#define RBA_ETHUDP_SW_CHKSUM_RX_IPV6    (STD_OFF) /* STD_ON/STD_OFF: UDP checksum is verified by software/hardware for the received frame */



#endif  /* RBA_ETHUDP_CFG_H */

