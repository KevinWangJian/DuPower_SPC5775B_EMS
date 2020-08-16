


 
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
#include "PduR_LoIfTT.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( void, PDUR_CODE ) PduR_SoAdIfRxIndication( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    PduR_rSoAdIfRxIndication((id), (ptr));
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
FUNC( void, PDUR_CODE ) PduR_SoAdIfTxConfirmation( VAR(PduIdType, AUTOMATIC) pduId_u8)
{
    PduR_rSoAdIfTxConfirmation(pduId_u8);
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
FUNC( Std_ReturnType, PDUR_CODE ) PduR_SoAdIfTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    return ((Std_ReturnType)PduR_rSoAdIfTriggerTransmit((id), (ptr)));
}
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
