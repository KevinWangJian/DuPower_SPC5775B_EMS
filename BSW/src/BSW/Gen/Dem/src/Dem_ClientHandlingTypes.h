

#ifndef DEM_CLIENTHANDLINGTYPES_H
#define DEM_CLIENTHANDLINGTYPES_H

#include "Dem_Types.h"

/******************************************************************************************/
/****************  Client States  *********************************************************/
#define DEM_CLIENT_STATE_INIT                   0x00u
#define DEM_CLIENT_STATE_PARAMETERS_SET         0x01u
#define DEM_CLIENT_STATE_REQUESTED_OPERATION    0x02u

/******************************************************************************************/
/****************  Dem_ClientSelectionType  ***********************************************/

#define DEM_CLIENT_SELECTION_TYPE_INVALID                   0X00u
#define DEM_CLIENT_SELECTION_TYPE_ALL_DTCS                  0X01u
#define DEM_CLIENT_SELECTION_TYPE_GROUP_DTC                 0X02u
#define DEM_CLIENT_SELECTION_TYPE_SINGLE_DTC                0X03u
#define DEM_CLIENT_SELECTION_TYPE_EMISSION_RELATED_DTCS     0X04u

/******************************************************************************************/
/****************  Dem_ClientRequestType  ************************************************/

#define DEM_CLIENT_REQUEST_NONE                         0x00u
#define DEM_CLIENT_REQUEST_CLEAR                        0x02u
#define DEM_CLIENT_REQUEST_CANCEL_CLEAR                 0x03u
#define DEM_CLIENT_REQUEST_GETSTATUS                    0x04u
#define DEM_CLIENT_REQUEST_CANCEL_GETSTATUS             0x05u
#define DEM_CLIENT_REQUEST_GETSELECTIONRESULT           0x06u
#define DEM_CLIENT_REQUEST_CANCEL_GETSELECTIONRESULT    0x07u
#define DEM_CLIENT_REQUEST_DISABLERECORDUPDATE          0x08u
#define DEM_CLIENT_REQUEST_CANCEL_DISABLERECORDUPDATE   0x09u
#define DEM_CLIENT_REQUEST_ENABLERECORDUPDATE           0x0Au
#define DEM_CLIENT_REQUEST_CANCEL_ENABLERECORDUPDATE    0x0Bu

/******************************************************************************************/
/***********************  INVALID PARAMS  ************************************************/
#define DEM_INVALID_DTC_ORIGIN_MEMORY   0u
#define DEM_INVALID_DTC_FORMAT          0xFFu
#define DEM_INVALID_DTC                 0xAA000000u   /*As per Autosar, the 4th byte(uint32) is unused which is used here internally to invalidate DTC */

typedef uint16 Dem_ClientRequestType;
typedef uint16 Dem_ClientResultType;
typedef uint32 Dem_ClientSelectionType;

/** To adpat to AR4.3 */
#define DEM_BUSY                DEM_CLEAR_BUSY
#define DEM_WRONG_DTC           DEM_CLEAR_WRONG_DTC
#define DEM_WRONG_DTCORIGIN     DEM_CLEAR_WRONG_DTCORIGIN
#define DEM_PENDING             DEM_CLEAR_PENDING
#define DEM_FAILED              DEM_CLEAR_FAILED
#define DEM_WRONG_CLIENTID      E_NOT_OK

#endif
