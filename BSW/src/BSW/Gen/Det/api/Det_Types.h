

#ifndef DET_TYPES_H
#define DET_TYPES_H

/**
 * @defgroup Typedefs
 * @ingroup DET_H
 */

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Std_Types.h"
#include "Rte_Det_Type.h"

/*
 **********************************************************************************************************************
 * Defines
 **********************************************************************************************************************
 */

/**
 * @ingroup Macros
 * The following service IDs are provided by Det
 * @{
 */
#define DET_APIID_INIT                  0x00u       /**< Det_Init service ID */
#define DET_APIID_REPORTERROR           0x01u       /**< Det_ReportError service ID */
#define DET_APIID_START                 0x02u       /**< Det_Start service ID */
#define DET_APIID_GETVERSIONINFO        0x03u       /**< Det_GetVersionInfo service ID */
#define DET_APIID_REPORTRUNTIMEERROR    0x04u       /**< Det_ReportRuntimeError service ID */
#define DET_APIID_REPORTTRANSIENTFAULT  0x05u       /**< Det_ReportTransientFault service ID */
#define DET_APIID_GETLASTBUFFERINDEX    0x06u       /**< Det_ReportTransientFault service ID */
#define DET_APIID_GETBUFFERENTRY        0x07u       /**< Det_ReportTransientFault service ID */
/**@}*/

/**
 * @ingroup Macros
 * The following development errors can be reported from DET
 * @{
 */
#define DET_E_PARAM_POINTER     0x01u       /**< Det_GetVersionInfo called with null parameter pointer */
#define DET_E_CANNOT_REPORT     0x01u       /**< Det unable to report errors, e.g. to lack of ressources */
#define DET_E_WRONG_MODULE      0x02u       /**< Wrong Module parameter */
#define DET_E_WRONG_INSTANCE    0x03u       /**< Wrong Instance ID */
#define DET_E_WRONG_API         0x04u       /**< Wrong API parameter */
#define DET_E_WRONG_ERROR       0x05u       /**< Wrong Error */
#define DET_E_UNAVAILABLE       0x01u       /**< Det currently unavailable */
/**@}*/

/*
 **********************************************************************************************************************
 * Typedefs
 **********************************************************************************************************************
 */

/**
 * @ingroup Typedefs
 * Det_BufferIndexType          Typedef for the buffer index to be independent of API changes when introducing
 *                              optimizations to the buffer.
 */
typedef uint16 Det_BufferIndexType;

/**
 * @ingroup Typedefs
 * Det_ConfigType               Configuration data structure of the Det module. Det does not have
 *                              post build parameters. This structure only contains a uint8 Dummy value.
 */
typedef struct
{
    uint8 Dummy; /**< 8 bit Dummy value */
} Det_ConfigType;

/**
 * @ingroup Typedefs
 * Det_ErrorEntryBufferType     Data structure for the RB Det Error Buffer. Used by Det_ReportError function.
 */
typedef struct
{
    uint16 ModuleId; /**< 16 bit Module ID */
    uint8 InstanceId; /**< 8 bit Instance ID */
    uint8 ApiId; /**< 8 bit API ID */
    uint8 ErrorId; /**< 8 bit Error ID */
} Det_ErrorEntryBufferType;

#endif /* #ifndef DET_TYPES_H */
