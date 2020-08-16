


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/



#include "PduR_Prv.h"

#include "PduR_Cfg.h"
/* Appropriate header files are included to declare the prototypes
 */
#include "PduR_LoIf.h"


/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_CanIfTxConfirmation - PDU Router CanIfTxConfirmation
 *      This function is called by the CanIf after the PDU has been transmitted on the network.
 *
 * \param           PduIdType Id: ID of  L-PDU that has been transmitted.
 *
 *
 * \retval          None
 * \seealso         PDUR194
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_CanIfTxConfirmation( VAR(PduIdType, AUTOMATIC) id )
{
    PduR_rCanIfTxConfirmation( id );
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_CanIfRxIndication - PDU Router CanIfRxIndication
 *      This function is called by the CanIf after a L-PDU has been received.
 *
 * \param           PduIdType id
 *                  const uint8 *ptr
 *
 * \retval          None
 * \seealso         PDUR193 and PDUR258
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_CanIfRxIndication( VAR(PduIdType, AUTOMATIC) id,
                                                P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    PduR_rCanIfRxIndication((id), (ptr));
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"


