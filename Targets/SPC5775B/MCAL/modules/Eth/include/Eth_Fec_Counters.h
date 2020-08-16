/**
*   @file    Eth_Fec_Counters.h
*   @version 1.0.1
*
*   @brief   FEC controller counters macros
*   @details Macros to be used to reference the ETH counters
*
*   @addtogroup ETH_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : FEC
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_ASR_REL_4_0_REV_0003_20170519
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef ETH_FEC_COUNTERS_H
#define ETH_FEC_COUNTERS_H
#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Eth_Fec_Counters_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, A compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers.
* Name length of the macro is unfortunately longer than 31 characters required by the agreed file
* template and cannot be changed. Authors of the template have not taken the MISRA rules into
* account.
*
* @section Eth_Fec_Counters_h_REF_2
* Violates MISRA 2004 Required Rule 5.1,  Identifiers (internal and external)
* shall not rely on the significance of more than 31 characters.
* Name length of the macro is unfortunately longer than 31 characters required
* by the agreed file template and cannot be changed. Authors of the template
* have not taken the MISRA rules into account.
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros,
* objects and functions shall not be reused. All defines starting with upper
* letter E are reserved for future use inside <error.h> header file.
* All module define options and enumerations are restricted by JDP coding rules
* 5.6 and 5.8 and must follow format <MSN>_<NAME> where MSN is equal to ETH.
* It was agreed that this violation will not be commented above each line but
* only in header of affected file.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ETH_VENDOR_ID_CNT_H                    43
#define ETH_MODULE_ID_CNT_H                    88
/** @violates @ref Eth_Fec_Counters_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_Counters_h_REF_2 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MAJOR_VERSION_CNT_H     4
/** @violates @ref Eth_Fec_Counters_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_Counters_h_REF_2 MISRA rule 5.1 */
#define ETH_AR_RELEASE_MINOR_VERSION_CNT_H     0
/** @violates @ref Eth_Fec_Counters_h_REF_1 MISRA rule 1.4 */
/** @violates @ref Eth_Fec_Counters_h_REF_2 MISRA rule 5.1 */
#define ETH_AR_RELEASE_REVISION_VERSION_CNT_H  3
#define ETH_SW_MAJOR_VERSION_CNT_H             1
#define ETH_SW_MINOR_VERSION_CNT_H             0
#define ETH_SW_PATCH_VERSION_CNT_H             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* No checks provided because it may not be anything to check against - the
   Eth.h might not be present and still this file might be used e.g. by EthIf
   caller module.
*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
    /*******************************************************************************
    * MIB Counters Offset Macros
    *******************************************************************************/
    /**
    *   @def FEC_RMON_T_DROP_ADDR16
    *   @brief Count of frames not counted correctly
    *   @details RFC 1757 counter counting number of events where the 
    *            transmitted frame was dropped from counting due to lack 
    *            of resources.
    */
    #define FEC_RMON_T_DROP_ADDR16        0x0200U 
    /**
    *   @def FEC_RMON_T_PACKETS_ADDR16
    *   @brief Transmitted Packets count
    *   @details RFC 1757 counter counting number of all transmitted frames 
    *            (including broadcast and multicast frames).
    *                 
    */
    #define FEC_RMON_T_PACKETS_ADDR16     0x0204U
    /**
    *   @def FEC_RMON_T_BC_PKT_ADDR16 
    *   @brief Transmitted Broadcast Packets count
    *   @details RFC 1757 counter counting number of transmitted broadcast 
    *            frames (multicast frames are excluded).
    */
    #define FEC_RMON_T_BC_PKT_ADDR16      0x0208U
    /**
    *   @def FEC_RMON_T_MC_PKT_ADDR16
    *   @brief Transmitted Multicast Packets count
    *   @details RFC 1757 counter counting number of transmitted multicast 
    *            frames (broadcast frames excluded).
    */
    #define FEC_RMON_T_MC_PKT_ADDR16      0x020CU 
    /**
    *   @def FEC_RMON_T_CRC_ALIGN_ADDR16
    *   @brief Transmitted Packets with CRC or Align error count
    *   @details RFC 1757 counter counting number of transmitted frames of 
    *            length between 64 and 1518 bytes inclusive that were sent
    *            with bad CRC (or not integral number of octets - this can occur
    *            only when the controller is reset).
    */
    #define FEC_RMON_T_CRC_ALIGN_ADDR16   0x0210U
    /**
    *   @def FEC_RMON_T_UNDERSIZE_ADDR16
    *   @brief Transmitted Packets < 64 bytes, good CRC
    *   @details RFC 1757 counter counting number of frames transmitted with 
    *            good CRC and less then 64 bytes. This can occur only when the
    *            controller is stopped.
    */
    #define FEC_RMON_T_UNDERSIZE_ADDR16   0x0214U 
    /**
    *   @def FEC_RMON_T_OVERSIZE_ADDR16
    *   @brief Transmitted Packets > MAX_FL bytes, good CRC
    *   @details RFC 1757 counter counting number of frames transmitted with 
    *            good CRC but with length greater than length of one receive
    *            buffer (transmit buffer length shall be less than or equal
    *            to the receive buffer length).
    */
    #define FEC_RMON_T_OVERSIZE_ADDR16    0x0218U
    /**
    *   @def FEC_RMON_T_FRAG_ADDR16
    *   @brief Transmitted Packets < 64 bytes, bad CRC
    *   @details RFC 1757 counter counting number of transmitted frame 
    *            fragments - they have bad CRC and are shorter than 64 bytes
    *            (they have been cut - can occur when the controller is reset).
    */
    #define FEC_RMON_T_FRAG_ADDR16        0x021CU 
    /**
    *   @def FEC_RMON_T_JAB_ADDR16
    *   @brief Transmitted Packets > MAX_FL bytes, bad CRC
    *   @details RFC 1757 counter counting number of transmitted frames with 
    *            length greater than configured receive buffer length and bad 
    *            CRC.
    */
    #define FEC_RMON_T_JAB_ADDR16         0x0220U 
    /**
    *   @def FEC_RMON_T_COL_ADDR16
    *   @brief Transmission collisions count
    *   @details RFC 1757 counter counting number of collisions during
    *            transmission.
    */
    #define FEC_RMON_T_COL_ADDR16         0x0224U 
    /**
    *   @def FEC_RMON_T_P64_ADDR16
    *   @brief Transmitted packets with length equal to 64 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length equal to 64 bytes (including bad ones).
    */
    #define FEC_RMON_T_P64_ADDR16         0x0228U
    /**
    *   @def FEC_RMON_T_P65TO127_ADDR16
    *   @brief Transmitted packets with length 65 to 127 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length between 65 and 127 inclusive 
    *            (including bad frames).
    */
    #define FEC_RMON_T_P65TO127_ADDR16    0x022CU 
    /**
    *   @def FEC_RMON_T_P128TO255_ADDR16
    *   @brief Transmitted packets with length 128 to 255 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length between 128 and 255 inclusive 
    *            (including bad frames).
    */    
    #define FEC_RMON_T_P128TO255_ADDR16   0x0230U
    /**
    *   @def FEC_RMON_T_P256TO511_ADDR16
    *   @brief Transmitted packets with length 256 to 511 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length between 256 and 511 inclusive 
    *            (including bad frames).
    */                
    #define FEC_RMON_T_P256TO511_ADDR16   0x0234U 
    /**
    *   @def FEC_RMON_T_P512TO1023_ADDR16
    *   @brief Transmitted packets with length 512 to 1023 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length between 512 and 1023 inclusive 
    *            (including bad frames).
    */
    #define FEC_RMON_T_P512TO1023_ADDR16  0x0238U 
    /**
    *   @def FEC_RMON_T_P1024TO2047_ADDR16
    *   @brief Transmitted packets with length 1024 to 2047 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length between 1024 and 2047 inclusive 
    *            (including bad frames).
    */            
    #define FEC_RMON_T_P1024TO2047_ADDR16 0x023CU 
    /**
    *   @def FEC_RMON_T_P_GTE2048_ADDR16
    *   @brief Transmitted packets with length greater than 2047 byte count 
    *   @details RFC 1757 counter counting number of transmitted frames
    *            with length greater or equal to 2048 
    *            (including bad frames).
    */            
    #define FEC_RMON_T_P_GTE2048_ADDR16   0x0240U 
    /**
    *   @def FEC_RMON_T_OCTETS_ADDR16
    *   @brief Transmitted octets count
    *   @details RFC 1757 counter counting total number of transmitted bytes -
    *   header (14 B), frame payload, frame pad and crc (4 B) bytes are counted.
    */
    #define FEC_RMON_T_OCTETS_ADDR16      0x0244U 
    /**
    *   @def FEC_IEEE_T_DROP_ADDR16
    *   @brief Count of frames not counted correctly 
    *   @details IEEE 802.3 counter counting transmitted frames which could
    *            not be successfully counted due to a lack of needed resources.
    */    
    #define FEC_IEEE_T_DROP_ADDR16        0x0248U
    /**
    *   @def FEC_IEEE_T_FRAME_OK_ADDR16
    *   @brief  Frames Transmitted OK 
    *   @details IEEE 802.3 counter counting successfully transmitted frames 
    */    
    #define FEC_IEEE_T_FRAME_OK_ADDR16    0x024CU
    /**
    *   @def FEC_IEEE_T_1COL_ADDR16
    *   @brief Frames Transmitted with Single Collision
    *   @details IEEE 802.3 counter counting successfully transmitted frames 
    *           involved in one collision (collision and then successful 
    *           transmission).         
    */    
    #define FEC_IEEE_T_1COL_ADDR16        0x0250U
    /**
    *   @def FEC_IEEE_T_MCOL_ADDR16
    *   @brief  Frames Transmitted with Multiple Collisions
    *   @details IEEE 802.3 counter counting successfully transmitted frames 
    *            involved in more collisions (n collisions and then successful 
    *            transmission).   
    */    
    #define FEC_IEEE_T_MCOL_ADDR16        0x0254U
    /**
    *   @def FEC_IEEE_T_DEF_ADDR16
    *   @brief  Frames Transmitted after Deferral Delay
    *   @details IEEE 802.3 counter counting frames with delayed transmission 
    *            because of bussy medium.
    */    
    #define FEC_IEEE_T_DEF_ADDR16         0x0258U
    /**
    *   @def FEC_IEEE_T_LCOL_ADDR16
    *   @brief Frames Transmitted with Late Collision
    *   @details IEEE 802.3 counter counting transmitted frames with a 
    *           collision after the 512th bit. Other collision counters
    *           may be also implemented if their conditions are met.
    */    
    #define FEC_IEEE_T_LCOL_ADDR16        0x025CU
    /**
    *   @def FEC_IEEE_T_EXCOL_ADDR16
    *   @brief Frames Transmitted with Excessive Collisions
    *   @details IEEE 802.3 counter counting frames which transmission was 
    *            aborted due to excessive collisions. Frames have not been sent.
    */    
    #define FEC_IEEE_T_EXCOL_ADDR16       0x0260U
    /**
    *   @def FEC_IEEE_T_MACERR_ADDR16 
    *   @brief Frames Transmitted with Tx FIFO Underrun
    *   @details IEEE 802.3 counter counting number of transmit FIFO underruns.
    *            Transmit FIFO underrun results in discarding the frame being 
    *            currently transmitted.      
    */    
    #define FEC_IEEE_T_MACERR_ADDR16      0x0264U 
    /**
    *   @def FEC_IEEE_T_CSERR_ADDR16
    *   @brief Carrier Sense Errors count 
    *   @details IEEE 802.3 counter counting carrier sense deasertions while 
    *            transmitting a frame not involved in a collision.
    */    
    #define FEC_IEEE_T_CSERR_ADDR16       0x0268U 
    /**
    *   @def FEC_IEEE_T_SQE_ADDR16
    *   @brief SQE_TEST_ERROR receptions count
    */    
    #define FEC_IEEE_T_SQE_ADDR16         0x026CU 
    /**
    *   @def FEC_IEEE_T_FDXFC_ADDR16
    *   @brief Flow Control Pause frames transmitted count
    */    
    #define FEC_IEEE_T_FDXFC_ADDR16       0x0270U
    /**
    *   @def FEC_IEEE_T_OCTETS_OK_ADDR16
    *   @brief Octet count for Frames Transmitted w/o Error
    *   @details IEEE 802.3 counter ciounting number of correctly transmitted 
    *            bytes.
    */    
    #define FEC_IEEE_T_OCTETS_OK_ADDR16   0x0274U
    /**
    *   @def FEC_RMON_R_DROP_ADDR16
    *   @brief Count of frames not counted correctly
    *   @details RFC 1757 counter counting number of events where the 
    *            received frame was dropped from counting due to lack 
    *            of resources.
    */
    #define FEC_RMON_R_DROP_ADDR16        0x0280U 
    /**
    *   @def FEC_RMON_R_PACKETS_ADDR16
    *   @brief received Packets count
    *   @details RFC 1757 counter counting number of all received frames 
    *            (including broadcast and multicast frames).
    *                 
    */
    #define FEC_RMON_R_PACKETS_ADDR16     0x0284U 
    /**
    *   @def FEC_RMON_R_BC_PKT_ADDR16 
    *   @brief Received Broadcast Packets count
    *   @details RFC 1757 counter counting number of received broadcast 
    *            frames (multicast frames are excluded).
    */
    #define FEC_RMON_R_BC_PKT_ADDR16      0x0288U
    /**
    *   @def FEC_RMON_R_MC_PKT_ADDR16
    *   @brief Received Multicast Packets count
    *   @details RFC 1757 counter counting number of received multicast 
    *            frames (broadcast frames excluded).
    */
    #define FEC_RMON_R_MC_PKT_ADDR16      0x028CU
    /**
    *   @def FEC_RMON_R_CRC_ALIGN_ADDR16
    *   @brief Received Packets with CRC or Align error count
    *   @details RFC 1757 counter counting number of transmitted frames of 
    *            length between 64 and 1518 bytes inclusive that were received
    *            with bad CRC or not integral number of octets.
    */
    #define FEC_RMON_R_CRC_ALIGN_ADDR16   0x0290U 
    /**
    *   @def FEC_RMON_R_UNDERSIZE_ADDR16
    *   @brief Received Packets < 64 bytes, good CRC
    *   @details RFC 1757 counter counting number of frames received with 
    *            good CRC and less then 64 bytes.
    */    
    #define FEC_RMON_R_UNDERSIZE_ADDR16   0x0294U 
    /**
    *   @def FEC_RMON_R_OVERSIZE_ADDR16
    *   @brief Received Packets > MAX_FL bytes, good CRC
    *   @details RFC 1757 counter counting number of frames received with 
    *            good CRC but with length greater than length of one receive
    *            buffer (frame is stored into more buffers).
    */    
    #define FEC_RMON_R_OVERSIZE_ADDR16    0x0298U 
    /**
    *   @def FEC_RMON_R_FRAG_ADDR16
    *   @brief Received Packets < 64 bytes, bad CRC
    *   @details RFC 1757 counter counting number of received frame 
    *            fragments - they have bad CRC and are shorter than 64 bytes.
    */
    #define FEC_RMON_R_FRAG_ADDR16        0x029CU 
    /**
    *   @def FEC_RMON_R_JAB_ADDR16
    *   @brief Received Packets > MAX_FL bytes, bad CRC
    *   @details RFC 1757 counter counting number of received frames with 
    *            length greater than configured receive buffer length and bad 
    *            CRC.        
    */
    #define FEC_RMON_R_JAB_ADDR16         0x02A0U 
    /**
    *   @def FEC_RMON_R_P64_ADDR16
    *   @brief Received packets with length equal to 64 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length equal to 64 bytes (including bad frames).
    */
    #define FEC_RMON_R_P64_ADDR16         0x02A8U
    /**
    *   @def FEC_RMON_R_P65TO127_ADDR16
    *   @brief Received packets with length 65 to 127 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length between 65 and 127 inclusive 
    *            (including bad frames).
    */
    #define FEC_RMON_R_P65TO127_ADDR16    0x02ACU
    /**
    *   @def FEC_RMON_R_P128TO255_ADDR16
    *   @brief Received packets with length 128 to 255 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length between 128 and 255 inclusive 
    *            (including bad frames).*/

    #define FEC_RMON_R_P128TO255_ADDR16   0x02B0U
    /**
    *   @def FEC_RMON_R_P256TO511_ADDR16
    *   @brief Received packets with length 256 to 511 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length between 256 and 511 inclusive
    *            (including bad frames).
    */

    #define FEC_RMON_R_P256TO511_ADDR16   0x02B4U
    /**
    *   @def FEC_RMON_R_P512TO1023_ADDR16
    *   @brief Received packets with length 512 to 1023 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length between 512 and 1023 inclusive
    *            (including bad frames).
    */    

    #define FEC_RMON_R_P512TO1023_ADDR16  0x02B8U
    /**
    *   @def FEC_RMON_R_P1024TO2047_ADDR16
    *   @brief Received packets with length 1024 to 2047 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length between 1024 and 2047 inclusive
    *            (including bad frames).
    */    
    #define FEC_RMON_R_P1024TO2047_ADDR16 0x02BCU
    /**
    *   @def FEC_RMON_R_P_GTE2048_ADDR16
    *   @brief Received packets with length greater than 2047 byte count 
    *   @details RFC 1757 counter counting number of received frames
    *            with length greater or equal to 2048
    *            (including bad frames).
    */
    #define FEC_RMON_R_P_GTE2048_ADDR16   0x02C0U
    /**
    *   @def FEC_RMON_R_OCTETS_ADDR16
    *   @brief Received octets count
    *   @details RFC 1757 counter counting total number of received bytes
    *            (preamble and SFD are excluded) i.e. header (14 B), 
    *            frame payload, frame pad and crc (4 B) bytes are counted.
    */
    #define FEC_RMON_R_OCTETS_ADDR16      0x02C4U
    /**
    *   @def FEC_IEEE_R_DROP_ADDR16
    *   @brief Count of frames not counted correctly 
    *   @details IEEE 802.3 counter counting received frames which could
    *            not be successfully counted due to a lack of needed resources.
    */    
    #define FEC_IEEE_R_DROP_ADDR16        0x02C8U
    /**
    *   @def FEC_IEEE_R_FRAME_OK_ADDR16
    *   @brief Frames Received OK
    *   @details IEEE 802.3 counter counting received frames without CRC error, 
    *           alignment error which are not too long (64-1518 bytes).
    */    
    #define FEC_IEEE_R_FRAME_OK_ADDR16    0x02CCU
    /**
    *   @def FEC_IEEE_R_CRC_ADDR16
    *   @brief Frames Received with CRC Error
    *   @details IEEE 802.3 counter counting received frames with bad CRC but
    *            with integral number of octets.
    */    
    #define FEC_IEEE_R_CRC_ADDR16         0x02D0U
    /**
    *   @def FEC_IEEE_R_ALIGN_ADDR16
    *   @brief Frames Received with Alignment Error
    *   @details IEEE 802.3 counter counting received frames with bad CRC and
    *            with not integral number of octets.
    */    
    #define FEC_IEEE_R_ALIGN_ADDR16       0x02D4U
    /**
    *   @def FEC_IEEE_R_MACERR_ADDR16
    *   @brief Receive Fifo Overflow count
    *   @details IEEE 802.3 counter counting received frames which are damaged 
    *            due to internal receive FIFO overflow error.
    */    
    #define FEC_IEEE_R_MACERR_ADDR16      0x02D8U
    /**
    *   @def FEC_IEEE_R_FDXFC_ADDR16
    *   @brief Flow Control Pause frames received
    *   @details IEEE 802.3 counter counting  number of received flow control 
    *            pause frames.
    */    
    #define FEC_IEEE_R_FDXFC_ADDR16       0x02DCU
    /**
    *   @def FEC_IEEE_R_OCTETS_OK_ADDR16
    *   @brief Octet count for Frames received without an error 
    *   @details  IEEE 802.3 counter counting received bytes of data and pad
    *             in correctly received frames (no error).
    */    
    #define FEC_IEEE_R_OCTETS_OK_ADDR16   0x02E0U
/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* ETH_FEC_COUNTERS_H */
