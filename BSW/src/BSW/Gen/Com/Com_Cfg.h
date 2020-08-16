


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: Com / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/

#ifndef COM_CFG_H
#define COM_CFG_H

/*
 ***************************************************************************************************
 * Version Information Defines
 ***************************************************************************************************
 */
/**
 * @ingroup COM_CFG_H
 *
 * Com module id(according to AUTOSAR BSW module list)
 */
#define COM_MODULE_ID                                                   50u
/**
 * @ingroup COM_CFG_H
 *
 * Com module id(according to AUTOSAR BSW module list)
 */
#define COM_VENDOR_ID                                                   6u

/* Version of AUTOSAR Com specification */
/**
 * @ingroup COM_CFG_H
 *
 * Major Version of AUTOSAR Com specification
 */
#define COM_AR_RELEASE_MAJOR_VERSION                                    4u
/**
 * @ingroup COM_CFG_H
 *
 * Minor Version of AUTOSAR Com specification
 */
#define COM_AR_RELEASE_MINOR_VERSION                                    2u
/**
 * @ingroup COM_CFG_H
 *
 * Revision Version of AUTOSAR Com specification
 */
#define COM_AR_RELEASE_REVISION_VERSION                                 2u

/* Version of AUTOSAR Com implementation */
/**
 * @ingroup COM_CFG_H
 *
 * Major Version of AUTOSAR Com implementation
 */
#define COM_SW_MAJOR_VERSION                                            4u
/**
 * @ingroup COM_CFG_H
 *
 * Minor Version of AUTOSAR Com implementation
 */
#define COM_SW_MINOR_VERSION                                            0u
/**
 * @ingroup COM_CFG_H
 *
 * Patch Version of AUTOSAR Com implementation
 */
#define COM_SW_PATCH_VERSION                                            0u



/* START: Include Part   */
#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/* END: Include Part   */

#define COM_NUM_ARR_IPDUGRPVECT    1u

#define COM_ECUC_RB_RTE_IN_USE  ( STD_ON  )

/************************ SIGNAL GROUP switches *************************/
/************************************************************************/
/* SIGNAL GROUP switches */

/* #define COM_TX_SIGNALGROUP */

/* #define COM_RX_SIGNALGROUP */

/* #define COM_TXSCHEDULED_DIFF_TIMEBASE */

/* #define COM_TXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
/* #define COM_RXIPDUCONTROL_VIA_RBA_NDS_ECUVARIANT */
/************************************************************************/

#include "Com_Cfg_SymbolicNames.h"

/* Start Type Declarations*/

typedef uint16 Com_SignalIdType;

typedef uint16 Com_SignalGroupIdType;

typedef uint8 Com_IpduIdType;


typedef uint8    Com_GrpSignalIdType;


typedef uint16 Com_IpduGroupIdType;

typedef uint8 Com_IpduGroupVector[COM_NUM_ARR_IPDUGRPVECT];

/*  END: Type Declaration  */

/* Enum for Com status, Init/uninit */
typedef enum
{
    COM_UNINIT,
    COM_INIT
}Com_StatusType;

#endif   /* COM_CFG_H */
