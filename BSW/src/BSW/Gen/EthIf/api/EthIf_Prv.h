

#ifndef ETHIF_PRV_H
#define ETHIF_PRV_H

/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/

#if (ETHIF_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*
***************************************************************************************************
* defines
***************************************************************************************************
*/

#define ETHIF_ETHTYPE_BYTE1 					12U
#define ETHIF_ETHTYPE_BYTE2 					13U

#define ETHIF_ETHTHDR_OFFSET 					14U

#define ETHIF_VLANTAG_BYTE1 					0U
#define ETHIF_VLANTAG_BYTE2 					1U

#define ETHIF_ETHTYPE_IN_VLAN_BYTE1				2U
#define ETHIF_ETHTYPE_IN_VLAN_BYTE2				3U

#define ETHIF_ETHTYPEFIELD_LENGTH				2U
#define ETHIF_VLANTAG_LENGTH					4U
#define ETHIF_MACHDR_LENGTH						12U

#define ETHIF_E_INV_CTRL_IDX					0x1U /* Invalid controller index */
#define ETHIF_E_INV_TRCV_IDX					0x2U /* Invalid transceiver index */
#define ETHIF_E_INV_PORT_GROUP_IDX              0x3U /* Invalid Port Group index */
#define ETHIF_E_NOT_INITIALIZED					0x4U /* EthIf module was not initialized */
#define ETHIF_E_PARAM_POINTER				    0x5U /* Invalid pointer in parameter list */
#define ETHIF_E_INV_PARAM						0x6U /* Invalid parameter */
#define ETHIF_E_INIT_FAILED                     0x7U /* Initialization failed */

#define ETHIF_SID_ETHIF_INIT					    0x1U
#define ETHIF_SID_ETHIF_PRV_CONTROLLERINIT			0x2U
#define ETHIF_SID_ETHIF_SETCONTROLLERMODE		    0x3U
#define ETHIF_SID_ETHIF_GETCONTROLLERMODE		    0x4U
#define ETHIF_SID_ETHIF_MAINFUNCTIONSTATE           0x5U
#define ETHIF_SID_ETHIF_SWITCHPORTGROUPREQUESTMODE  0x6U
#define ETHIF_SID_ETHIF_STARTALLPORTS               0x7U
#define	ETHIF_SID_ETHIF_GETPHYSADDR				    0x8U
#define ETHIF_SID_ETHIF_PROVIDETXBUFFER			    0x9U
#define ETHIF_SID_ETHIF_TRANSMIT				    0xAU
#define ETHIF_SID_ETHIF_GETVERSIONINFO			    0xBU
#define ETHIF_SID_ETHIF_UPDATE_PHYSADDRFILTER	    0xCU
#define ETHIF_SID_ETHIF_TRCVMODEINDICATION          0xFU
#define ETHIF_SID_ETHIF_CBK_RXINDICATION		    0x10U
#define	ETHIF_SID_ETHIF_CBK_TXCONFIRMATION	    	0x11U
#define ETHIF_SID_ETHIF_MAINFUNCTIONRX		    	0x20U
#define ETHIF_SID_ETHIF_MAINFUNCTIONTX		    	0x21U
#define ETHIF_SID_ETHIF_GETCURRENTTIME              0x22U
#define ETHIF_SID_ETHIF_ENABLE_EGRESS_TIMESTAMP     0x23U
#define ETHIF_SID_ETHIF_GET_EGRESS_TIMESTAMP        0x24U
#define ETHIF_SID_ETH_GETINGRESSTIMESTAMP           0x25U
#define ETHIF_SID_ETHIF_GETVLANID                   0x43U
#define ETHIF_SID_ETHIF_PRV_TRANSCEIVERINIT			0x50U
#define ETHIF_SID_ETHIF_PRV_SETTRANSCEIVERMODE      0x51U

#define ETHIF_OFFSET_SOURCEMACADDR              0x06U
#define ETHIF_OFFSET_PAYLOAD_NOVLAN             0x0EU
#define ETHIF_OFFSET_PAYLOAD_VLAN               0x12U

/* FramePrio is a 3 bit field in Vlan header, it's maximun value is 7 */
#define ETHIF_FRAMEPRIO_MAXVAL				    7U

/*
***************************************************************************************************
* Private Typedefs
***************************************************************************************************
*/

#if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )
/* This data type defines the virtual address entry structure which is used by the virtual filter */
 typedef struct
 {
     uint32 ReferenceCounter_u32;                       /* Reference counter for the virtual address filter`s entries. */
     uint8 HardwareControllerIndex_u8;                  /* Index of the Ethernet controller within the context of the Ethernet Driver */
     uint8 PhysicalAddress_u8[6];                       /* Physical source address (MAC address) in network byte order */

 }EthIf_PhysAddrFilterRefCounterType;
#endif

/* Variable declarations */
#define ETHIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"
/* EthIf_Init API call status flag */
extern VAR( EthIf_StateType, AUTOMATIC )                            EthIf_InitStatus_en;

/* EthIf configuration pointer */
extern P2CONST( EthIf_ConfigType, AUTOMATIC, AUTOMATIC )            EthIf_CfgPtr_pco;
#define ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_CLEARED_32
#include "EthIf_MemMap.h"

/* Global variable for EthIf Switch Ports active timer */
extern VAR( uint32,  AUTOMATIC )                            EthIf_PortActiveTime_u32;

#define ETHIF_STOP_SEC_VAR_CLEARED_32
#include "EthIf_MemMap.h"

/*************************MACRO Definitions for DET Error Handling*********************************/

#if (ETHIF_DEV_ERROR_DETECT  == STD_ON)

/* DET For functions with return type as 'void' */
#define ETHIF_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)                                                          \
                                       if(CONDITION)                                                                \
                                       {                                                                            \
                                            (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID, API, ERROR);  \
                                            return;                                                                 \
                                       }


/* DET For functions with return type as 'Std_ReturnType' */
#define ETHIF_REPORT_ERROR_RET_VALUE(CONDITION, API, ERROR, RETVAL)                                                 \
                                       if(CONDITION)                                                                \
                                       {                                                                            \
                                            (void)Det_ReportError(ETHIF_MODULE_ID, ETHIF_INSTANCE_ID, API, ERROR);  \
                                            return ( RETVAL );                                                      \
                                       }

#else

/* No DET Code Expansion if Development Detection Error is OFF */

#define ETHIF_REPORT_ERROR_RET_VOID(CONDITION, API, ERROR)

#define ETHIF_REPORT_ERROR_RET_VALUE(CONDITION, API, ERROR, RETVAL)

#endif

/*************************Private function declaration*********************************/

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"

/* Initializes the indexed controller */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_ControllerInit( VAR(uint8, AUTOMATIC)   CtrlIdx );

#if( ETHIF_TRANSCEIVER_CONFIGURED == STD_ON )

/* Initializes the indexed transceiver */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_TransceiverInit( VAR(uint8, AUTOMATIC)       TrcvIdx );

#endif

/* Enables / disables the indexed controller */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetControllerMode( VAR(uint8, AUTOMATIC)           CtrlIdx,
                                                                  VAR(Eth_ModeType, AUTOMATIC)    CtrlMode );

FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_EthIfCtrl_ActiveStatus( VAR(uint8, AUTOMATIC)           CtrlIdx,
                                                                       VAR(Eth_ModeType, AUTOMATIC)    CtrlMode );

#if( ETHIF_SWITCH_CONFIGURED == STD_ON )
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortMode( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )     EthSwtConfig_pst,
                                                                  VAR( uint8,                     AUTOMATIC )                EthIfCtrlIdx_u8,
                                                                  VAR( EthTrcv_ModeType,          AUTOMATIC )                TrcvMode   );
#endif

#if( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON )
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortGroupActive( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          EthSwtConfig_pst,
                                                                         P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   EthIf_PortGrp_pst );

FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Prv_SetSwitchPortGroupDown( P2VAR( EthIf_EthSwtConfig_tst,  AUTOMATIC, AUTOMATIC )          EthSwtConfig_pst,
                                                                       P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )   EthIf_PortGrp_pst );

FUNC(boolean,        RBA_ETHIF_CODE) EthIf_Prv_CheckPrtGrp_ActiveStatus( P2CONST( EthIf_Swt_PortGrpConfig_tst,  AUTOMATIC, AUTOMATIC )     EthIf_PortGrp_pst );
#endif

FUNC(void,           RBA_ETHIF_CODE) EthIf_Prv_Trigger_StateTransitions( void );

#if( ETHIF_STANDALONE_PORTGRPS_CONFIGURED == STD_ON )
FUNC(void,          RBA_ETHIF_CODE ) EthIf_Prv_StandalonePG_StateTransitions( void );
#endif

#if( ETHIF_UPDATE_PHYS_ADDR_FILTER_SUPPORT == STD_ON )
extern FUNC (void, RBA_ETHIF_CODE) EthIf_Prv_ResetPhysAddrFilterReferencesForEthHwCtrlIdx(VAR( uint8, AUTOMATIC ) PhysCtrlIdx_u8);
extern FUNC (void, RBA_ETHIF_CODE) EthIf_Prv_ResetPhysAddrFilterReferences(void);
#endif

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif /* ETHIF_PRV_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
