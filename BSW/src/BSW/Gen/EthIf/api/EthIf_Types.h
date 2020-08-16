

#ifndef ETHIF_TYPES_H
#define ETHIF_TYPES_H

#include "Eth_GeneralTypes.h"
#include "EthTrcv_GeneralTypes.h"
#include "EthIf_Cfg.h"

#ifndef ETHIF_HWADDR_LEN
#define ETHIF_HWADDR_LEN           	6U
#endif

/* Data Type that represents the Ethernet interface switch port group index. The index is zero based and unique for every configured switch port group. */
typedef uint8    EthIf_SwitchPortGroupIdxType;

#define ETHIF_TRCV                  0x00U     /* The reference is to a physical transceiver */
#define ETHIF_SWITCH                0x01U     /* The reference is to an ethernet switch */
#define ETHIF_PORTGRP_LINKINFO      0x02U     /* The reference is to a switch port group. The semantic of the reference is 'link-information'. */
#define ETHIF_PORTGRP_CTRL          0x03U     /* The reference is to a switch port group. The semantic of the reference is 'control'. */
#define ETHIF_PORTGRP_UNREFERENCED  0x04U     /* The switch port group is not referenced by any EthIf controller. The port group is derived per partial network */
#define ETHIF_NO_REF                0xFFU     /* No reference is configured for the EthIf controller */

/* Status supervision used for Development Error Detection. The state shall be available for debugging.*/
typedef enum {
	ETHCTRL_STATE_UNINIT	 	= 0x00U,		/* Ethernet Interface is not yet configured */
	ETHCTRL_STATE_INIT		    = 0x01U			/* Ethernet Interface is configured */
}EthIf_StateType;

/* These are the states defined internally for EthIf to maintain Trcv/EthIfSwitchPortGroup/EthIfSwitch state per EthIf controller */
typedef enum {
    ETHIF_ETHIFCTRL_STATE_DOWN                  = 0x00U,   /* EthIfCtrl is in state DOWN */
    ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_ACTIVE  = 0x01U,   /* EthIfCtrl is requested for ACTIVE, but Trcv Mode indication is not yet given */
    ETHIF_ETHIFCTRL_STATE_WAIT_TRCVMODE_DOWN    = 0x02U,   /* EthIfCtrl is requested for DOWN, but Trcv Mode indication is not yet given */
    /* EthIfCtrl is in state active: mode of HW configured for this EthIfCtrl (EthCtrl and optionally EthTrcv or EthSwt or PG) is active */
    ETHIF_ETHIFCTRL_STATE_ACTIVE                = 0x03U
}EthIf_EthIfCtrlStateType_ten;

/* These are the link states defined internally for EthIf to maintain Trcv/EthIfSwitchPortGroup/EthIfSwitch link status per EthIf controller */
/* These are the link states defined internally for EthIf to maintain standalone EthIfSwitchPortGroup link status */
typedef enum {
    ETHIF_ETHIFCTRL_LINKSTATE_DOWN                 = 0x00U,
    ETHIF_ETHIFCTRL_LINKSTATE_ACTIVE               = 0x01U,
    ETHIF_STANDALONE_PG_LINKSTATE_DOWN             = 0x02U,
    ETHIF_STANDALONE_PG_LINKSTATE_ACTIVE           = 0x03U
}EthIf_LinkStateType;

/* These are the states defined internally for EthIf to maintain standalone EthIfSwitchPortGroup state */
typedef enum {
    ETHIF_STANDALONE_PG_MODE_DOWN           = 0x00U,   /*  EthIfSwitchPortGroup is in state DOWN   */
    ETHIF_STANDALONE_PG_MODE_STARTUP        = 0x01U,   /*  EthIfSwitchPortGroup is made ACTIVE for configured time EthIfPortStartupActiveTime  */
    ETHIF_STANDALONE_PG_MODE_ACTIVE         = 0x02U,   /*  EthIfSwitchPortGroup is made ACTIVE by BswM */
    ETHIF_STANDALONE_PG_MODE_WAITDOWN       = 0x03U    /*  EthIfSwitchPortGroup is requested for DOWN, and changes after configured time EthIfSwitchOffPortTimeDelay  */
}EthIf_Standalone_SwtPrtGrpStateType_ten;

/* Enumeration to denote the reference type of EthIfController to either the transceiver, switch or switch port group. */
typedef uint32 EthIf_Trcv_Swt_PortGrp_RefType_ten;

/* State of EthCtrl in context of EthIf */
typedef enum {
    ETHIF_ETHCTRLSTATE_UNINIT           = 0x00U,        /* EthCtrl is not yet initialized  */
    ETHIF_ETHCTRLSTATE_INIT             = 0x01U,        /* EthCtrl is initialized */
    ETHIF_ETHCTRLSTATE_ACTIVE           = 0x02U         /* EthCtrl state is ETH_MODE_ACTIVE */
}EthIf_EthCtrlStateType_ten;

/* State of EthSwt in context of EthIf */
typedef enum {
    ETHIF_ETHSWTSTATE_UNINIT           = 0x00U,        /* EthSwitch is not yet initialized  */
    ETHIF_ETHSWTSTATE_INIT             = 0x01U         /* EthSwitch is initialized */
}EthIf_EthSwt_InitStateType_ten;

/* Structure to maintain the EthSwt port states in context of EthIf */
typedef struct {
    VAR( uint32,  AUTOMATIC )    PortOffDelay_u32;           /* Timer to switch off a port after a request for DOWN is received */
    CONST( uint8, AUTOMATIC )    PortIdx_cu8;                /* The EthSwt port index fetched as a symbolic name. */
    VAR( uint8,   AUTOMATIC )    ActiveCnt_u8;               /* Indicates in how many EthIf SwitchPortGroups the port is active. Applies also to EthIfSwitch, if the reference is EthIfSwitch */
    VAR( boolean, AUTOMATIC )    IsPortActive_b;             /* Indicates whether the port is active in context of EthIf */
}EthIf_EthSwt_PortStateType_tst;

typedef struct {
    CONST( uint8,          AUTOMATIC )                                PortGrpIdx_u8;                /* PortGroupIdx of the Standalone EthIfSwitchPortGroup */
    VAR( EthIf_Standalone_SwtPrtGrpStateType_ten,     AUTOMATIC )     Standalone_PG_State_en;       /* Stores state of standalone switch portgroups */
    VAR( EthIf_LinkStateType, AUTOMATIC )                             Standalone_PG_LinkStatus_en;  /* Stores link status of standalone switch portgroups */
    VAR( EthTrcv_ModeType,                     AUTOMATIC )            Standalone_PG_ReqMode_en;     /* Requested mode of the Standalone EthIfSwitchPortGroup, if the semantic is Unreferenced. */
}EthIf_StandalonePG_Type_tst;

/*  Port group structure */
typedef struct {
    CONST( EthIf_Trcv_Swt_PortGrp_RefType_ten, AUTOMATIC )        semantic_en;               /* Semantic of the EthIf SwitchPortGroup. It is either link-information, control or unreferenced. */
    CONST( uint8,                              AUTOMATIC )        EthSwtIdx_cu8;             /* The index of the EthSwt in which the ports of the group are present */
    CONST( uint8,                              AUTOMATIC )        HostPortIdx_cu8;           /* The host port index of the EthSwt. */
    CONST( uint8,                              AUTOMATIC )        nrOfPorts_cu8;             /* Number of ports of the EthIfSwitchPortGroup excluding the host port */
    P2CONST( uint8,             AUTOMATIC,     AUTOMATIC )        RefPorts_cpu8;             /* Refers to an array of ports which do not have any role */
}EthIf_Swt_PortGrpConfig_tst;

/* Structure to maintain the state of each Switch and its ports, configured in EthSwt */
typedef struct {
    CONST( uint8,                AUTOMATIC )                      EthSwtIdx_cu8;        /* Switch index */
    CONST( uint8,                AUTOMATIC )                      HostPortIdx_cu8;      /* host port index of the switch */
    CONST( uint8,               AUTOMATIC )                       LastPortIdx_cu8;        /* Last PortIdx number after sorting it in ascending order */
    CONST( uint8,               AUTOMATIC )                       nrOfStdPorts_cu8;        /* Number of standard ports of the switch */
    VAR ( EthIf_EthSwt_InitStateType_ten, AUTOMATIC )             EthIfSwt_State_en;    /* The initialization status of the switch */
    P2VAR( EthIf_EthSwt_PortStateType_tst, AUTOMATIC, AUTOMATIC ) EthIf_SwtPort_past;   /* Pointer to the state data structure of individual ports */
    P2CONST( uint8,             AUTOMATIC,     AUTOMATIC )        RefStdPorts_cpu8;     /* Refers to an array of standard ports */
}EthIf_EthSwtConfig_tst;

typedef struct{
    P2VAR( EthIf_EthCtrlStateType_ten,    AUTOMATIC,  AUTOMATIC )       EthCtrlState_pa;             /* Pointer to an array, to store EthCtrl state within EthIf context */
    P2VAR( Eth_ModeType,                  AUTOMATIC,  AUTOMATIC )       EthIfCtrlMode_pa;            /* Pointer to an array, to store the Current mode of an EthIf Controller */
    P2VAR( Eth_ModeType,                  AUTOMATIC,  AUTOMATIC )       EthIfCtrlReqMode_pa;         /* Pointer to an array, to store the requested mode of EthIf Controller  */
    P2VAR( EthTrcv_ModeType,              AUTOMATIC,  AUTOMATIC )       Trcv_IndicatedMode_en;       /* Pointer to an array, to store the mode indicated by the transceiver */
    P2VAR( uint8,                         AUTOMATIC,  AUTOMATIC )       TrcvInitFlg_pa;              /* Pointer to TrcvInit Flag */
    P2VAR( EthIf_StandalonePG_Type_tst,   AUTOMATIC, AUTOMATIC )        StandalonePG_Type_pst;     /* Refers to a structure containing the standalone PG state, link and request mode info. */
    CONST( uint8,                         AUTOMATIC )                   nrOfEthIfCtrl_cu8;           /* EthIf Ctrl Count */
    CONST( uint8,                         AUTOMATIC )                   nrOfEthCtrl_cu8;             /* EthCtrl Count */
    CONST( uint8,                         AUTOMATIC )                   nrOfTrcv_cu8;                /* Max Transceiver Count */
    CONST( uint8,                         AUTOMATIC )                   nrOfEthIfTrcvs_cu8;          /* Number of EthIfTransceivers configured in EthIf */
    CONST( uint8,                         AUTOMATIC )                   nrOfSwitch_cu8;              /* Number of EthIf Switches configured in EthIf */
    CONST( uint8,                         AUTOMATIC )                   nrOfEthSwtes_cu8;            /* Number of EthSwtes configured in EthSwt module */
    CONST( uint8,                         AUTOMAITC )                   nrOfSwtPortGrps_cu8;         /* Number of EthIf SwitchPortGroups configured */
    CONST( uint8,                         AUTOMATIC )                   nrOfStdAlone_PrtGrps_cu8;    /* Number of standalone EthIf SwitchPortGroups configured */
    CONST( uint8,                         AUTOMATIC )                   nrOfFrameOwners_cu8;         /* Number of Frame Owners */
    P2VAR( boolean,                       AUTOMATIC,  AUTOMATIC )       EthIfCtrl_TrcvError_pa;      /* Pointer to an array, to store whether error occured in transceiver */
}EthIf_CtrlStateType_tst;

typedef struct {
	CONST( uint16,                              AUTOMATIC )				   VlanId_cu16;						 /* If parameter EthIfVlanId is configured, this structure member will hold configured value */
	                                                                                                         /* If parameter EthIfVlanId is not configured, this structure member will hold 0xffff */
	                                                                                                         /* EthIfVlanId can be configured to 0 if priority tagged frames are required  */
	CONST( uint16,                              AUTOMATIC )                MtuSize_cu16;                     /* Specifies the maximum transmission unit (MTU) of the EthIfCtrl in bytes */
	CONST( uint8,                               AUTOMATIC )				   idxEthCtrRef_cu8;    		     /* Reference to the controller in Ethernet driver on which this connection will be transmitted/received */
    CONST( uint8,                               AUTOMATIC )                TrcvIdx_cu8;                      /* Physical transceiver index. Set to invalid if EthIfCtrl does not refer a transceiver. */
	CONST( uint8,                               AUTOMATIC )                EthSwtIdx_cu8;                    /* Switch index. Set to invalid if EthIfCtrl does not refer a switch. */
	P2VAR( EthIf_Swt_PortGrpConfig_tst,       AUTOMATIC,  AUTOMATIC )      SwtPortGrp_pst;                   /* Pointer to data structure of a Switch Port group. Set to NULL_PTR if EthIfCtrl does not refer a EthIfSwitchPortGroup */
    VAR( EthIf_EthIfCtrlStateType_ten,          AUTOMATIC )                EthIfCtrlState_en;                /* State of the EthIf Controller */
    VAR( EthIf_LinkStateType,                   AUTOMATIC )                EthIfCtrl_LinkState_en;           /* Link status of the EthIf Controller */
	CONST( EthIf_Trcv_Swt_PortGrp_RefType_ten,  AUTOMATIC )                TrcvSwtPortGrp_RefType_en;        /* Reference type of EthIf controller */
}EthIf_ControllerConfig_tst;

typedef struct {
	CONST( Eth_FrameType,                   AUTOMATIC ) 				FrameType_tcu16;				      /* Selects the Ethernet frame type e.g. 0x800 = IPv4 */

	P2FUNC( void, AUTOMATIC, EthIfRxIndication) ( VAR( uint8,         AUTOMATIC )                 CtrlIdx,     /* Rx Indication function pointer */
	                                              VAR( Eth_FrameType, AUTOMATIC )          		  FrameType,
	                                              VAR( boolean,       AUTOMATIC )                 IsBroadcast,
	                                              P2VAR( uint8,       AUTOMATIC, AUTOMATIC )      PhysAddrPtr,
	                                              P2VAR( uint8,       AUTOMATIC, AUTOMATIC )      DataPtr,
	                                              VAR( uint16,        AUTOMATIC )                 LenByte );

	P2FUNC( void, AUTOMATIC, EthIfTxConfirmation)( 	VAR( uint8,       AUTOMATIC ) 			      EthIfCtrlIdx_u8,  /* Tx Confirmation function pointer */			                                        VAR( uint8,       AUTOMATIC ) 			      BufIdx_u8 );
}EthIf_FrameOwnerConfig_tst;

typedef struct {
	P2VAR( EthIf_ControllerConfig_tst,        AUTOMATIC,  AUTOMATIC )	    EthIfControllerConfig_pst;			    /* Pointer to Controller config structure     */
	P2CONST( EthIf_FrameOwnerConfig_tst,      AUTOMATIC,  AUTOMATIC )       EthIfFrameOwnerConfig_pst;			    /* Pointer to frame owner config structure    */
	P2CONST( EthIf_CtrlStateType_tst,         AUTOMATIC,  AUTOMATIC )		EthIfCtrlState_pst;					    /* Pointer to Controller link state structure */
	P2VAR( EthIf_Swt_PortGrpConfig_tst,       AUTOMATIC,  AUTOMATIC )       EthIfPrtGrpConfig_pst;                  /* Pointer to the EthIfSwitchPortGroup data structure */
	P2VAR( EthIf_EthSwtConfig_tst,            AUTOMATIC,  AUTOMATIC  )      EthIfSwtConfig_pst;                     /* Pointer to the Switch data structure */
} EthIf_ConfigType;

#endif /* ETHIF_TYPES_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
