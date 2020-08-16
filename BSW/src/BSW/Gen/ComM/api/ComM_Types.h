

/**
\defgroup COMM_TYPES_H    COMM - AUTOSAR interfaces Upper Layer
*/
#ifndef COMM_TYPES_H
#define COMM_TYPES_H

#include "ComStack_Types.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/**
 * @ingroup COMM_TYPES_H
 *
 * Macro used to define passive ComMPncGatewayType.
 */
typedef enum
{
    COMM_GATEWAY_TYPE_ACTIVE = 0,
    COMM_GATEWAY_TYPE_PASSIVE
}ComM_PncGatewayType;
/**
 * @ingroup COMM_TYPES_H
 *
 * Macro used to define ComM transmission.
 */
#define COMM_TX       0
/**
 * @ingroup COMM_TYPES_H
 *
 * Macro used to define ComM reception.
 */
#define COMM_RX        1
/**
 * @ingroup COMM_TYPES_H
 *
 * Macro used to define ComM EIRA
 */
#define COMM_EIRA   0
/**
 * @ingroup COMM_TYPES_H
 *
 * Macro used to define ComM ERA
 */
#define COMM_ERA    1

#define COMM_NO_COMMUNICATION        (uint8)(0)
#define COMM_SILENT_COMMUNICATION    (uint8)(1)
#define COMM_FULL_COMMUNICATION        (uint8)(2)
/*--------------------------------------------------------------*/
/*   Initialization status of ComM                              */
/*--------------------------------------------------------------*/
/**
 * @ingroup COMM_TYPES_H
 *  This enum is used to define the initialization status of ComM           \n
 *  typedef enum                                                            \n
 *  {
 *   COMM_UNINIT = 0,   The COM Manager is not initialized or not usable.   \n
 *   COMM_INIT          The COM Manager is initialized and usable.          \n
 *  }ComM_InitStatusType;
 */
typedef enum
{
  COMM_UNINIT = 0,
  COMM_INIT
}ComM_InitStatusType;

/* ComM_BusType */
/**
 * @ingroup COMM_TYPES_H
 *  This enum is used to define the bus types of ComM   \n
 *  typedef enum                                        \n
 *  {
 *      COMM_BUS_TYPE_CAN,          CAN bus type        \n
 *      COMM_BUS_TYPE_FR,           FlexRay bus type    \n
 *      COMM_BUS_TYPE_INTERNAL,     Internal bus type   \n
 *      COMM_BUS_TYPE_LIN,          LIN bus type        \n
 *      COMM_BUS_TYPE_ETH           Ethernet bus type   \n
 *  } ComM_BusType;
 */
typedef enum
{
    COMM_BUS_TYPE_CAN,
    COMM_BUS_TYPE_ETH,
    COMM_BUS_TYPE_FR,
    COMM_BUS_TYPE_INTERNAL,
    COMM_BUS_TYPE_LIN

} ComM_BusType;

/* ComM_NMVariantType */
   /**
 * @ingroup COMM_TYPES_H
 *  This enum is used to define the variant types of ComM   \n
 *  typedef enum    \n
 *  {
 *     FULL,    NM available (default). \n
 *     LIGHT,   NM not available but functionality to shut down a channel is available. \n
 *     NONE,    No NM available \n
 *     PASSIVE  NM running in passive mode available.   \n
 *   } ComM_NMVariantType;
 */
typedef enum
{
   FULL,
   LIGHT,
   NONE,
   PASSIVE
} ComM_NMVariantType;

   /* Type Definitions */
   /* ComM_StateType */

/**
 * @ingroup COMM_TYPES_H
 *  This enum is used to define the state types of ComM \n
 *  typedef enum                                        \n
 *  {
 *      COMM_NO_COM_NO_PENDING_REQUEST = 0, no pending request in no communication mode \n
 *      COMM_NO_COM_REQUEST_PENDING,        request pending in no communication mode    \n
 *      COMM_FULL_COM_NETWORK_REQUESTED,    network requested in full communication mode    \n
 *      COMM_FULL_COM_READY_SLEEP,          full communication ready sleep state    \n
 *      COMM_SILENT_COM                     silent communication state  \n
 *  } ComM_StateType;
 */
typedef enum
{
   COMM_NO_COM_NO_PENDING_REQUEST = 0,
   COMM_NO_COM_REQUEST_PENDING,
   COMM_FULL_COM_NETWORK_REQUESTED,
   COMM_FULL_COM_READY_SLEEP,
   COMM_SILENT_COM
} ComM_StateType;



/**
 * @ingroup COMM_TYPES_H
 *  This enum is used to define the PNC mode types of ComM  \n
 *  typedef enum    \n
 *  {
 *      PNC_REQUESTED,              PNC is requested by a local ComM user   \n
 *      PNC_READY_SLEEP,            PNC is requested by a remote ComM user  \n
 *      PNC_PREPARE_SLEEP,          PNC is active with no deadline monitoring\n
 *      PNC_NO_COMMUNICATION,       PNC does not communicate    \n
 *      PNC_FULL_COMMUNICATION      PNC is able to communicate  \n
 *  } ComM_PncModeType;
 */
typedef enum
{
       PNC_REQUESTED,
       PNC_READY_SLEEP,
       PNC_PREPARE_SLEEP,
       PNC_NO_COMMUNICATION,
       PNC_FULL_COMMUNICATION
} ComM_PncModeType;

/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */
#endif /*COMM_TYPES_H*/

