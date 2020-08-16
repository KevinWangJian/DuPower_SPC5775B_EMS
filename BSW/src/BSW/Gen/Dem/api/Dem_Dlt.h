

#ifndef DEM_DLT_H
#define DEM_DLT_H


#include "Dem_Types.h"

/**
 * \defgroup DEM_DLT    DEM - Interface for the Dlt
 *
 * This interface may only be used by the Dlt. Use by other components is prohibited because some of the functions
 * are non-reentrant and therefore need to be called without interference.
 *
 * To use this interface include the header <b>Dem.h</b>
 * @{
 */
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

/**
 *
 * Gets the data of all extended data records of an event.
 *
 * @param [in] EventId     : Identification of an event by assigned EventId
 * @param [out] DestBuffer : This parameter contains a byte pointer that points to the buffer, to which the extended data shall be
 *                           written to. The format is raw hexadecimal values and contains no header-information.
 * @param [in,out] BufSize : When the function is called this parameter contains the maximum
 *                           number of data bytes that can be written to the buffer.
 *                           The function returns the actual number of written data bytes in this
 *                           parameter.
 *
 * @return  E_OK = Operation was successful, E_NOT_OK: Operation failed.
 */
Std_ReturnType Dem_DltGetAllExtendedDataRecords(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);


/**
 *
 * Gets the data of an most recent freeze frame record by event.
 *
 * @param [in] EventId     : Identification of an event by assigned EventId
 * @param [out] DestBuffer : This parameter contains a byte pointer that points to the buffer, to which the extended data shall be
 *                           written to. The format is raw hexadecimal values and contains no header-information.
 * @param [in,out] BufSize : When the function is called this parameter contains the maximum
 *                           number of data bytes that can be written to the buffer.
 *                           The function returns the actual number of written data bytes in this
 *                           parameter.
 *
 * @return  E_OK = Operation was successful, E_NOT_OK: Operation failed.
 */
Std_ReturnType Dem_DltGetMostRecentFreezeFrameRecordData(Dem_EventIdType EventId, uint8* DestBuffer, uint16* BufSize);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/**@}*//* End of Doxygen group DEM_DLT */

#endif /* DEM_DLT_H */
