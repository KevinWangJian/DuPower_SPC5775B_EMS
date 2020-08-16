

#ifndef DET_H
#define DET_H

/**
 * \defgroup DET_H DET - AUTOSAR interface
 * Det.h includes all user relevant information for the tracing of development errors.
 * To use this interface include the header <b>Det.h</b>
 */

/**
 * @defgroup Macros
 * @ingroup DET_H
 */

/**
 * @defgroup API
 * @ingroup DET_H
 */

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Det_Types.h"
#include "Det_Cfg.h"

/*
 **********************************************************************************************************************
 * Funtion Prototypes
 **********************************************************************************************************************
 */
#define DET_START_SEC_ROM_CODE
#include "Det_MemMap.h"

/**
 * @ingroup API
 *
 * Det_GetLastBufferIndex   Service to provide the index of the last stored error entry.
 *
 * @param buffIdx           Pointer to store the index
 * @return                  E_OK                    successful execution.
 *                          E_NOT_OK                Det not initialized or no buffer entry.
 *                          DET_E_PARAM_POINTER     wrong parameter.
 */
#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetLastBufferIndex(Det_BufferIndexType* buffIdx);
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED) */

/**
 * @ingroup API
 *
 * Det_GetBufferEntry   Service to provide the error entry information for the given index.
 *
 * @param buffIdx       Index in buffer for the error entry that shall be provided.
 * @param entry         Pointer to store the error entry information.
 * @return              E_OK                    successful execution.
 *                      E_NOT_OK                Det not initialized, no buffer entry or invalid index.
 *                      DET_E_PARAM_POINTER     wrong parameter.
 */
#if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED)
Std_ReturnType Det_GetBufferEntry(Det_BufferIndexType buffIdx, Det_ErrorEntryBufferType* buffEntry);
#endif /* #if (DET_CFG_ERRORBUFFER_ENABLED && DET_CFG_ERRORBUFFERAPI_SUPPORTED) */

/**
 * @ingroup API
 *
 * Det_Init             Service to initialize the Default Error Tracer.
 *
 * @param ConfigPtr     Pointer to the selected configuration set.
 * @return              None
 */
void Det_Init(const Det_ConfigType* ConfigPtr);

/**
 * @ingroup API
 *
 * Det_Start            Service to start the Default Error Tracer.
 *
 * @param               None
 * @return              None
 */
void Det_Start(void);

/**
 * @ingroup API
 *
 * Det_GetVersionInfo   Returns the version information of this module.
 *
 * @param versioninfo   Pointer to where to store the version information of this module.
 * @return              None
 */
#if (DET_CFG_VERSIONINFO_SUPPORTED)
void Det_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif /* #if (DET_CFG_VERSIONINFO_SUPPORTED) */

#if (DET_CFG_CHECK_API_CONSISTENCY)
/**
 * @ingroup API
 *
 * Det_ReportError      Service to report development errors.
 *
 * @param ModuleId      Module ID of calling module.
 * @param InstanceId    The identifier of the index based instance of a module, starting from 0.
 *                      If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param ApiId         ID of API service in which error is detected (defined in SWS of calling module).
 * @param ErrorId       ID of detected development error (defined in SWS of calling module).
 * @return              returns always E_OK (is required for services).
 */
Std_ReturnType Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
 * @ingroup API
 * Det_ReportRuntimeError   Service to report runtime errors. If a callout has been configured then this callout
 *                          shall be called.
 *
 * @param ModuleId          Module ID of calling module.
 * @param InstanceId        The identifier of the index based instance of a module, starting from 0.
 *                          If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param ApiId             ID of API service in which error is detected (defined in SWS of calling module).
 * @param ErrorId           ID of detected runtime error (defined in SWS of calling module).
 * @return                  returns always E_OK (is required for services).
 */
Std_ReturnType Det_ReportRuntimeError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/**
 * @ingroup API
 * Det_ReportTransientFault     Service to report transient faults. If a callout has been configured then this
 *                              callout shall be called and the returned value of the callout shall be returned.
 *                              Otherwise it returns immediately with E_OK.
 *
 * @param ModuleId              Module ID of calling module.
 * @param InstanceId            The identifier of the index based instance of a module, starting from 0.
 *                              If the module is a single instance module it shall pass 0 as the InstanceId.
 * @param ApiId                 ID of API service in which transient fault is detected
 *                              (defined in SWS of calling module).
 * @param FaultId               ID of detected transient fault (defined in SWS of calling module).
 * @return                      Propagates return value of assigned callout if exists, otherwise E_OK.
 */
Std_ReturnType Det_ReportTransientFault(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 FaultId);
#endif /* #if (DET_CFG_CHECK_API_CONSISTENCY) */

#define DET_STOP_SEC_ROM_CODE
#include "Det_MemMap.h"

#endif /* #ifndef DET_H */
