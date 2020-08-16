


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#ifndef PDUR_CFG_INTERNAL_H
#define PDUR_CFG_INTERNAL_H

#include "ComStack_Types.h"


#if !defined(PDUR_DEV_ERROR_DETECT)
#define PDUR_DEV_ERROR_DETECT    (STD_OFF)
#endif /* PDUR_DEV_ERROR_DETECT */

#if !defined(PDUR_VERSION_INFO_API)
#define PDUR_VERSION_INFO_API    (STD_OFF)
#endif /* PDUR_VERSION_INFO_API */

#if !defined(PDUR_ZERO_COST_OPERATION)
#define PDUR_ZERO_COST_OPERATION    (STD_OFF)
#endif /* PDUR_ZERO_COST_OPERATION */

#if !defined(PDUR_IFGATEWAY_SUPPORT)
#define PDUR_IFGATEWAY_SUPPORT    (STD_OFF)
#endif /* PDUR_IFGATEWAY_SUPPORT */

#if !defined(PDUR_TPGATEWAY_SUPPORT)
#define PDUR_TPGATEWAY_SUPPORT    (STD_OFF)
#endif /* PDUR_TPGATEWAY_SUPPORT */



#define PDUR_RPGID_NULL   (0)

#if !defined(PDUR_DISABLE_MULTICAST_SUPPORT)
#define PDUR_DISABLE_MULTICAST_SUPPORT    (1) /* used internally to disable */
#endif /* PDUR_DISABLE_MULTICAST_SUPPORT */


#if !defined(PDUR_MULTICAST_TO_IF_SUPPORT)
#define PDUR_MULTICAST_TO_IF_SUPPORT    (0) /* Disabled as there are no Multicast routes to IF Modules */
#endif /* PDUR_MULTICAST_TO_IF_SUPPORT */




#if !defined(PDUR_MULTICAST_TO_TP_SUPPORT)
#define PDUR_MULTICAST_TO_TP_SUPPORT    (0) /* Disabled as there are no Multicast routes to TP Modules */
#endif /* PDUR_MULTICAST_TO_TP_SUPPORT */



#define PDUR_CONFIGURATION_ID (0)



#if !defined(PDUR_MULTICAST_FROM_TP_SUPPORT)
#define PDUR_MULTICAST_FROM_TP_SUPPORT    (0) /* Disabled as there are no Multicast routes from TP Modules */
#endif /* PDUR_MULTICAST_FROM_TP_SUPPORT */




#if !defined(PDUR_MODE_DEPENDENT_ROUTING)

    #define PDUR_MODE_DEPENDENT_ROUTING (0)
#endif /* PDUR_MODE_DEPENDENT_ROUTING */


/* Array used to maintain RPG Status with the value of PduRIsEnabledAtInit for each RPG */
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
 /* ------------------------------------------------------------------------ */
/* Begin section for constants */
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"

extern CONST(boolean, PDUR_CONST) PduR_RPG_EnRouting[];

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_8
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_POSTBUILD_8
#include "PduR_MemMap.h"

/* This array is used to maintain the status of each RPG */
extern VAR(boolean, PDUR_VAR) PduR_RPG_Status[];

#define PDUR_STOP_SEC_VAR_CLEARED_POSTBUILD_8
#include "PduR_MemMap.h"
/* ------------------------------------------------------------------------ */
/* End section for extern constant */

#endif


/*These Macros are used to indicate a unique no. assigned to each upper layer & is used in PduR_MC_SetTxConfirmationFlag() function if
    there are muticast routing paths existing from UpIf to Multiple LoIf*/

#define COM_PDURBSWMODNAME (0u)
#define IPDUM_PDURBSWMODNAME (1u)

#define PDUR_NULL_BSWMODNAME 255
#define PDUR_NULL_PDUID 0



#if !defined(PDUR_CANTP_CHANGE_PARAMETER_SUPPORT)
    #define PDUR_CANTP_CHANGE_PARAMETER_SUPPORT (0)
#endif /* PDUR_CANTP_CHANGE_PARAMETER_SUPPORT */

#if !defined(PDUR_FRTP_CHANGE_PARAMETER_SUPPORT)
    #define PDUR_FRTP_CHANGE_PARAMETER_SUPPORT (0)
#endif /* PDUR_FRTP_CHANGE_PARAMETER_SUPPORT */

#if ((PDUR_CANTP_CHANGE_PARAMETER_SUPPORT == 1) || (PDUR_FRTP_CHANGE_PARAMETER_SUPPORT == 1))
    #define PDUR_CHANGE_PARAMETER_SUPPORT   (1)
/* ------------------------------------------------------------------- */
/*Change Parameter Support*/
#define PDUR_NONE   0
#define PDUR_CANTP  1
#define PDUR_FRTP   2

/* ------------------------------------------------------------------- */
#else
    #define PDUR_CHANGE_PARAMETER_SUPPORT   (0)
#endif





#if !defined(PDUR_DEM_INIT_FAILED)
#define PDUR_DEM_INIT_FAILED        (0) /* STD_OFF */
#endif /* PDUR_DEM_INIT_FAILED */



#if !defined(PDUR_DEM_PDU_INSTANCE_LOST)
#define PDUR_DEM_PDU_INSTANCE_LOST  (0) /* STD_OFF */
#endif /* PDUR_DEM_PDU_INSTANCE_LOST */



#define PDUR_DSM_REINT_SUPPORT      STD_OFF






#if !defined(PDUR_CANTP_RXIND_BASE)
#define PDUR_CANTP_RXIND_BASE    (PDUR_BASE_LOTP(0,LoTpRxToUp))
#endif /* PDUR_CANTP_RXIND_BASE */
#if !defined(PDUR_CANTP_TXCONF_BASE)
#define PDUR_CANTP_TXCONF_BASE    (PDUR_BASE_LOTP(0,LoTpTxToUp))
#endif /* PDUR_CANTP_TXCONF_BASE */
#if !defined(PDUR_NR_VALID_CANTPTPRXTOUP_IDS)
#define PDUR_NR_VALID_CANTPTPRXTOUP_IDS    (PDUR_BASE_LOTP(0,LoTpRxToUp_NrEntries))
#endif /* PDUR_NR_VALID_CANTPTPRXTOUP_IDS */
#if !defined(PDUR_NR_VALID_CANTPTPTXTOUP_IDS)
#define PDUR_NR_VALID_CANTPTPTXTOUP_IDS    (PDUR_BASE_LOTP(0,LoTpTxToUp_NrEntries))
#endif /* PDUR_NR_VALID_CANTPTPTXTOUP_IDS */



#if !defined(PDUR_CANIF_RXIND_BASE)
#define PDUR_CANIF_RXIND_BASE    (PDUR_BASE_LOIFD(0,LoIfRxToUp))
#endif /* PDUR_CANIF_RXIND_BASE */
#if !defined(PDUR_CANIF_TXCONF_BASE)
#define PDUR_CANIF_TXCONF_BASE    (PDUR_BASE_LOIFD(0,LoIfTxToUp))
#endif /* PDUR_CANIF_TXCONF_BASE */
#if !defined(PDUR_NR_VALID_CANIFIFRXTOUP_IDS)
#define PDUR_NR_VALID_CANIFIFRXTOUP_IDS    (PDUR_BASE_LOIFD(0,LoIfRxToUp_NrEntries))
#endif /* PDUR_NR_VALID_CANIFIFRXTOUP_IDS */
#if !defined(PDUR_NR_VALID_CANIFIFTXTOUP_IDS)
#define PDUR_NR_VALID_CANIFIFTXTOUP_IDS    (PDUR_BASE_LOIFD(0,LoIfTxToUp_NrEntries))
#endif /* PDUR_NR_VALID_CANIFIFTXTOUP_IDS */



#if !defined(PDUR_IPDUM_RXIND_BASE)
#define PDUR_IPDUM_RXIND_BASE    (PDUR_BASE_LOIFTT(0,LoIfRxToUp))
#endif /* PDUR_IPDUM_RXIND_BASE */
#if !defined(PDUR_IPDUM_TXCONF_BASE)
#define PDUR_IPDUM_TXCONF_BASE    (PDUR_BASE_LOIFTT(0,LoIfTxToUp))
#endif /* PDUR_IPDUM_TXCONF_BASE */
#if !defined(PDUR_NR_VALID_IPDUMIFRXTOUP_IDS)
#define PDUR_NR_VALID_IPDUMIFRXTOUP_IDS    (PDUR_BASE_LOIFTT(0,LoIfRxToUp_NrEntries))
#endif /* PDUR_NR_VALID_IPDUMIFRXTOUP_IDS */
#if !defined(PDUR_NR_VALID_IPDUMIFTXTOUP_IDS)
#define PDUR_NR_VALID_IPDUMIFTXTOUP_IDS    (PDUR_BASE_LOIFTT(0,LoIfTxToUp_NrEntries))
#endif /* PDUR_NR_VALID_IPDUMIFTXTOUP_IDS */

#if !defined(PDUR_DCM_TX_BASE)
#define PDUR_DCM_TX_BASE    (PDUR_BASE_UPTP(0,UpToLo))
#endif /* PDUR_DCM_TX_BASE */

#if !defined(PDUR_DCM_MC_TX_BASE)
#define PDUR_DCM_MC_TX_BASE    (PDUR_BASE_UPTP(0,UpToLoMc))
#endif /* PDUR_DCM_MC_TX_BASE */

#if !defined(PDUR_NR_VALID_DCM_IDS)
#define PDUR_NR_VALID_DCM_IDS    (PDUR_BASE_UPTP(0,UpToLo_NrEntries))
#endif /* PDUR_NR_VALID_DCM_IDS */
#if !defined(PDUR_SOADIF_RXIND_BASE)
#define PDUR_SOADIF_RXIND_BASE    (PDUR_BASE_LOIFTT(1,LoIfRxToUp))
#endif /* PDUR_SOADIF_RXIND_BASE */
#if !defined(PDUR_SOADIF_TXCONF_BASE)
#define PDUR_SOADIF_TXCONF_BASE    (PDUR_BASE_LOIFTT(1,LoIfTxToUp))
#endif /* PDUR_SOADIF_TXCONF_BASE */
#if !defined(PDUR_NR_VALID_SOADIFIFRXTOUP_IDS)
#define PDUR_NR_VALID_SOADIFIFRXTOUP_IDS    (PDUR_BASE_LOIFTT(1,LoIfRxToUp_NrEntries))
#endif /* PDUR_NR_VALID_SOADIFIFRXTOUP_IDS */
#if !defined(PDUR_NR_VALID_SOADIFIFTXTOUP_IDS)
#define PDUR_NR_VALID_SOADIFIFTXTOUP_IDS    (PDUR_BASE_LOIFTT(1,LoIfTxToUp_NrEntries))
#endif /* PDUR_NR_VALID_SOADIFIFTXTOUP_IDS */
#if !defined(PDUR_COM_TX_BASE)
#define PDUR_COM_TX_BASE    (PDUR_BASE_UPIF(0,UpToLo))
#endif /* PDUR_COM_TX_BASE */
#if !defined(PDUR_COM_MC_TX_BASE)
#define PDUR_COM_MC_TX_BASE    (PDUR_BASE_UPIF(0,UpToLoMc))
#endif /* PDUR_COM_MC_TX_BASE */
#if !defined(PDUR_NR_VALID_COM_IDS)
#define PDUR_NR_VALID_COM_IDS    (PDUR_BASE_UPIF(0,UpToLo_NrEntries))
#endif /* PDUR_NR_VALID_COM_IDS */
#if !defined(PDUR_IPDUM_TX_BASE)
#define PDUR_IPDUM_TX_BASE    (PDUR_BASE_UPIF(1,UpToLo))
#endif /* PDUR_IPDUM_TX_BASE */
#if !defined(PDUR_IPDUM_MC_TX_BASE)
#define PDUR_IPDUM_MC_TX_BASE    (PDUR_BASE_UPIF(1,UpToLoMc))
#endif /* PDUR_IPDUM_MC_TX_BASE */
#if !defined(PDUR_NR_VALID_IPDUM_IDS)
#define PDUR_NR_VALID_IPDUM_IDS    (PDUR_BASE_UPIF(1,UpToLo_NrEntries))
#endif /* PDUR_NR_VALID_IPDUM_IDS */




/*Macro used for getting the size of Cdd config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_CddCfg     0

/*Macro used for getting the size of LoTp Rx config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoTpRxCfg  1

/*Macro used for getting the size of LoTp Tx config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoTpTxCfg  1

/*Macro used for getting the size of LoIf Rx with Direct data provision config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoIfRxDCfg  1

/*Macro used for getting the size of LoIf Tx with Direct data provision config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoIfTxDCfg  1

/*Macro used for getting the size of LoIf Rx with Trigger Transmit data provision config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoIfRxTTCfg  2

/*Macro used for getting the size of LoIf Tx with Trigger Transmit data provision config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_LoIfTxTTCfg  1

/*Macro used for getting the size of LoIf Tx with Trigger Transmit data provision config, this will be use in the reference configuration unit testing only*/
#define TableSize_PduR_UpTpCfg      1
#endif /* PDUR_CFG_INTERNAL_H */
