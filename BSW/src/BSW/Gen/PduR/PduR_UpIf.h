


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#ifndef PDUR_UPIF_H
#define PDUR_UPIF_H

#include "PduR.h"

#include "PduR_Com.h"
#include "PduR_Com_Up.h"

/* Service IDs */

#define PDUR_SID_COMTX  (11)    /* PduR_ComTransmit */
#define PDUR_SID_COMCNCLTX  (12)    /* PduR_ComCancelTransmit */
#define PDUR_SID_COMCNCLRX  (13)    /* PduR_ComCancelReceive */


#include "PduR_IpduM.h"
#include "PduR_IpduM_Up.h"

/* Service IDs */

#define PDUR_SID_IPDUMTX  (21)    /* PduR_IpduMTransmit */
#define PDUR_SID_IPDUMCNCLTX  (22)    /* PduR_IpduMCancelTransmit */
#define PDUR_SID_IPDUMCNCLRX  (23)    /* PduR_IpduMCancelReceive */


#define PDUR_SID_IPDUMRXIND  (24)    /* PduR_IpduMRxIndication */
#define PDUR_SID_IPDUMTXCONF  (25)    /* PduR_IpduMTxConfirmation */
#define PDUR_SID_IPDUMTRIGTX  (26)    /* PduR_IpduMTriggerTranmsit */


#endif /* PDUR_UPIF_H */

