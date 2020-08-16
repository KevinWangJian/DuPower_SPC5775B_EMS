

#ifndef ETH_GENERAL_TYPES_H
#define ETH_GENERAL_TYPES_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "ComStack_Types.h"
#include "EthTrcv_GeneralTypes.h"

/* EthTrcv_StateType: Status supervision used for Development Error Detection. The state shall be available for debugging. */
typedef enum
{
    ETHTRCV_STATE_UNINIT    = 0u,         /* Driver is not yet configured */
    ETHTRCV_STATE_INIT      = 1u,         /* Driver is configured */
    ETHTRCV_STATE_ACTIVE    = 2u          /* Driver is active */
} EthTrcv_StateType;

/* EthTrcv_WakeupModeType: This type controls the transceiver wake up modes and/or clears the wake-up reason */
typedef enum
{
	ETHTRCV_WUM_DISABLE 	= 0u, 	/* Transceiver wake up disabled */
	ETHTRCV_WUM_ENABLE 		= 1u, 	/* Transceiver wake up enabled */
	ETHTRCV_WUM_CLEAR 		= 2u 	/* Transceiver wake up reason cleared */
} EthTrcv_WakeupModeType;


/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */

/* Eth_ReturnType : Ethernet Driver specific return type */
typedef enum
{
	ETH_OK   		= 0U,	/* success */
	ETH_E_NOT_OK 	= 1U,   	/* general failure */
	ETH_E_NO_ACCESS = 3U		/* Ethernet hardware access failure */
} Eth_ReturnType;


/* Eth_ModeType: This type defines the controller modes */
typedef enum
{
    ETH_MODE_DOWN   = 0U,	/* Controller disabled */
    ETH_MODE_ACTIVE = 1U    	/* Controller enabled */
} Eth_ModeType;

/* Eth_StateType: Status supervision used for Development Error Detection. The state shall be available for debugging */
typedef enum
{
    ETH_STATE_UNINIT = 0U,   /* Driver is not yet configured */
    ETH_STATE_INIT   = 1U,   /* Driver is configured */
    ETH_STATE_ACTIVE = 2U    /* Driver is active */
} Eth_StateType;


/* This type defines the Ethernet frame type used in the Ethernet frame header */
typedef uint16 Eth_FrameType;

/* This type defines the Ethernet data type used for data transmission. Its definition depends on the used CPU */
typedef uint8 Eth_DataType;

typedef P2VAR(Eth_DataType, TYPEDEF, ETH_DMA_BUFFER) Eth_DataRefType_t;

/* Eth_RxStatusType : Used as out parameter in Eth_Receive() indicates whether a frame has been received and if so,
 * whether more frames are available or frames got lost. */
typedef enum
{
    ETH_RECEIVED                     = 0U,   /* Ethernet frame has been received, no further frames available */
    ETH_NOT_RECEIVED                 = 1U,   /* Ethernet frame has not been received, no further frames available */
    ETH_RECEIVED_MORE_DATA_AVAILABLE = 2U,   /* Ethernet frame has been received, more frames are available */
    ETH_RECEIVED_FRAMES_LOST		 = 3U	 /* Ethernet frame has been received, some frames got lost */
} Eth_RxStatusType;

/* Eth_FilterActionType: The Enumeration Type Eth_FilterActionType describes the action to be taklen for the MAC address given in *PhysAddrPtr.*/
typedef enum
{
    ADD_TO_FILTER 			= 0U,		/* add the MAC address to the filter, meaning allow reception */
    ETH_ADD_TO_FILTER 		= 0U,  		/* add the MAC address to the filter, meaning allow reception */
    REMOVE_FROM_FILTER 		= 1U,		/* remove the MAC address from the filter, meaning reception is blocked in the lower layer */
    ETH_REMOVE_FROM_FILTER	= 1U	    /* remove the MAC address from the filter, meaning reception is blocked in the lower layer */
} Eth_FilterActionType;

/* Eth_TimeStampQualType: Depending on the HW, quality information regarding the evaluated time stamp might be supported */
/* If not supported, the value shall always be valid. For Uncertain and Invalid values, the upper layer shall discard the time stamp */
typedef enum
{
    ETH_VALID               = 0U,
    ETH_INVALID             = 1U,
    ETH_UNCERTAIN           = 2U
} Eth_TimeStampQualType;

typedef struct
{
    VAR( uint32, AUTOMATIC )        nanoseconds;   /* Nanoseconds part of the time */
    VAR( uint32, AUTOMATIC )        seconds;       /* 32 bit LSB of the 48 bits Seconds part of the time */
    VAR( uint16, AUTOMATIC )        secondsHi;     /* 16 bit MSB of the 48 bits Seconds part of the time */
} Eth_TimeStampType;

/*Eth_TimeIntDiffType: Variables of this type are used to express time differences. */
typedef struct
{
    VAR( Eth_TimeStampType, AUTOMATIC ) diff;   /* time difference */
    VAR( boolean,           AUTOMATIC ) sign;   /* Positive (True) / negative (False) time */

}Eth_TimeIntDiffType;

/*Eth_RateRatioType: Variables of this type are used to express frequency ratios. */
typedef struct
{
    VAR( Eth_TimeIntDiffType, AUTOMATIC ) IngressTimeStampDelta;  /* IngressTimeStampSync2 - IngressTimeStampSync1 */
    VAR( Eth_TimeIntDiffType, AUTOMATIC ) OriginTimeStampDelta;   /* OriginTimeStampSync2[FUP2] - OriginTimeStampSync1[FUP1] */

}Eth_RateRatioType;


/* management structure for Eth Counter Type used in static counter for diagnostic */
typedef struct
{
     VAR(uint32, AUTOMATIC)DropPktBufOverrun;
     VAR(uint32, AUTOMATIC) DropPktCrc;
     VAR(uint32, AUTOMATIC) UndersizePkt;
     VAR(uint32, AUTOMATIC) OversizePkt;
     VAR(uint32, AUTOMATIC) AlgnmtErr;
     VAR(uint32, AUTOMATIC) SqeTestErr;
     VAR(uint32, AUTOMATIC) DiscInbdPkt;
     VAR(uint32, AUTOMATIC) ErrInbdPkt;
     VAR(uint32, AUTOMATIC) DiscOtbdPkt;
     VAR(uint32, AUTOMATIC) ErrOtbdPkt;
     VAR(uint32, AUTOMATIC)SnglCollPkt;
     VAR(uint32, AUTOMATIC) MultCollPkt;
     VAR(uint32, AUTOMATIC) DfrdPkt;
     VAR(uint32, AUTOMATIC) LatCollPkt;
     VAR(uint32, AUTOMATIC) HwDepCtr0;
     VAR(uint32, AUTOMATIC) HwDepCtr1;
     VAR(uint32, AUTOMATIC) HwDepCtr2;
     VAR(uint32, AUTOMATIC) HwDepCtr3;
}Eth_CounterType;


/* management structure for Eth_RxStats Type used in static counter for diagnstic for Rx Frame */
typedef struct
{
	 VAR(uint64, AUTOMATIC) RxStatsOctets;
     VAR(uint32, AUTOMATIC) RxStatsDropEvents;     
     VAR(uint32, AUTOMATIC) RxStatsPkts;
     VAR(uint32, AUTOMATIC) RxStatsBroadcastPkts;
     VAR(uint32, AUTOMATIC) RxStatsMulticastPkts;
     VAR(uint32, AUTOMATIC) RxStatsCrcAlignErrors;
     VAR(uint32, AUTOMATIC) RxStatsUndersizePkts;
     VAR(uint32, AUTOMATIC) RxStatsOversizePkts;
     VAR(uint32, AUTOMATIC) RxStatsFragments;
     VAR(uint32, AUTOMATIC) RxStatsJabbers;
     VAR(uint32, AUTOMATIC) RxStatsCollisions;
     VAR(uint32, AUTOMATIC) RxStatsPkts64Octets;
     VAR(uint32, AUTOMATIC) RxStatsPkts65to127Octets;
     VAR(uint32, AUTOMATIC) RxStatsPkts128to255Octets;
     VAR(uint32, AUTOMATIC) RxStatsPkts256to511Octets;
     VAR(uint32, AUTOMATIC) RxStatsPkts512to1023Octets;
     VAR(uint32, AUTOMATIC) RxStatsPkts1024to1518Octets;
     VAR(uint32, AUTOMATIC) RxUnicastFrames;
}Eth_RxStatsType;


/* management structure for Eth_TxStats Type used in static counter for diagnstic for Tx Frame */
typedef struct
{
     VAR(uint64, AUTOMATIC) TxNumberOfOctets;
     VAR(uint32, AUTOMATIC) TxNUcastPkts;
     VAR(uint32, AUTOMATIC) TxUniCastPkts;
}Eth_TxStatsType;

/* management structure for Eth_TxErrorCounterValuesType used in static counter for diagnstic for Tx Frame */
typedef struct
{
     VAR(uint32, AUTOMATIC) TxDroppedNoErrorPkts;
     VAR(uint32, AUTOMATIC) TxDroppedErrorPkts;
     VAR(uint32, AUTOMATIC) TxDeferredTrans;
     VAR(uint32, AUTOMATIC) TxSingleCollision;
     VAR(uint32, AUTOMATIC) TxMultipleCollision;
     VAR(uint32, AUTOMATIC) TxLateCollision;
     VAR(uint32, AUTOMATIC) TxExcessiveCollision;
}Eth_TxErrorCounterValuesType;


/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */

#endif /* ETH_GENERAL_TYPES_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
