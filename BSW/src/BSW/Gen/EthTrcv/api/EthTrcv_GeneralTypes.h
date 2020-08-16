


#ifndef ETHTRCV_GENERALTYPES_H_
# define ETHTRCV_GENERALTYPES_H_
/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/
#include "ComStack_Types.h"
#include "EthTrcv_Cfg_Time.h"


typedef enum
{
    ETHTRCV_BAUD_RATE_10MBIT    = 0u,     // 0x00: 10MBIT Ethnernet connection
    ETHTRCV_BAUD_RATE_100MBIT   = 1u,     // 0x01: 100MBit Ethernet connection
    ETHTRCV_BAUD_RATE_1000MBIT  = 2u,     // 0x02: 1000MBit Ethernet connection
    ETHTRCV_BAUD_RATE_UNDEF     = 3u      // 0x03: undef
}EthTrcv_BaudRateType;

typedef enum
{
    ETHTRCV_DUPLEX_MODE_HALF    = 0u,     // 0x00: Half duplex Ethernet connection
    ETHTRCV_DUPLEX_MODE_FULL    = 1u,     // 0x01: Full duplex Ethernet connection
    ETHTRCV_DUPLEX_MODE_UNDEF   = 2u
}EthTrcv_DuplexModeType;

typedef enum
{
    ETHTRCV_LINK_STATE_DOWN    = 0u,     // 0x00: No physical Ethernet connection established
    ETHTRCV_LINK_STATE_ACTIVE  = 1u,     // 0x01: Physical Ethernet connection established
    ETHTRCV_LINK_STATE_UNDEF   = 2u      // 0x02: Undefined
}EthTrcv_LinkStateType;

typedef enum
{
    ETHTRCV_MODE_DOWN   = 0u,             // 0x00: Transceiver disabled
    ETHTRCV_MODE_ACTIVE = 1u              // 0x01: Transceiver enabled
}EthTrcv_ModeType;

typedef enum
{
    ETHTRCV_WUP_NOT_SUPPORTED   = 0u,
    ETHTRCV_WUP_POWON           = 1u,
    ETHTRCV_WUP_REMOTE          = 2u
}EthTrcv_WupReasonType;


/* Describes the possible PHY test modes */
typedef enum
{
    ETHTRCV_PHYTESTMODE_NONE    = 0u,   /* normal operation */
    ETHTRCV_PHYTESTMODE_1       = 1u,   /* test transmitter droop */
    ETHTRCV_PHYTESTMODE_2       = 2u,   /* test master timing jitter */
    ETHTRCV_PHYTESTMODE_3       = 3u,   /* test slave timing jitter */
    ETHTRCV_PHYTESTMODE_4       = 4u,   /* test transmitter distortion */
    ETHTRCV_PHYTESTMODE_5       = 5u    /* test power spectral density (PSD) mask */
}EthTrcv_PhyTestModeType;

/* Describes the possible PHY loopback modes */
typedef enum
{
    ETHTRCV_PHYLOOPBACK_NONE       = 0x00U,   /* normal operation */
    ETHTRCV_PHYLOOPBACK_INTERNAL   = 0x01U,   /* internal loopback */
    ETHTRCV_PHYLOOPBACK_EXTERNAL   = 0x02U,   /* external loopback */
    ETHTRCV_PHYLOOPBACK_REMOTE     = 0x03U    /* remote loopback */
}EthTrcv_PhyLoopbackModeType;

/* Describes the results of the cable diagnostics */
typedef enum
{
    ETHTRCV_CABLEDIAG_OK        = 0x00, /* Cable diagnostic ok */
    ETHTRCV_CABLEDIAG_ERROR     = 0x01, /* Cable diagnostic failed */
    ETHTRCV_CABLEDIAG_SHORT     = 0x02, /* Short circuit detected */
    ETHTRCV_CABLEDIAG_OPEN      = 0x03  /* Open circuit detected */
}EthTrcv_CableDiagResultType;

/* Describes about the access to Phy */
typedef enum
{
    ETHTRCV_PHYACCESS_AVAILABLE     = 0x00, /* EthTrcv Software has access to Phy Hardware */
    ETHTRCV_PHYACCESS_NOT_AVAILABLE = 0x01  /* EthTrcv Software does not have access to Phy Hardware */
}EthTrcv_PhyAccessStatusType;

/* Management structure for EthTrcv_LinkStatisticsType used in static counter for diagnstic for link statistics */
typedef struct
{
    VAR(uint8,  AUTOMATIC) etherStatslinklosses_u8;     /* number of link fails */
    VAR(uint16, AUTOMATIC) etherStatsSymbolFailure_u16; /* The symbol error counter when an invalid code symbol is received(including the idle symbols) */
}EthTrcv_LinkStatisticsType;

#endif  /* ETHTRCV_GENERALTYPES_H_ */

