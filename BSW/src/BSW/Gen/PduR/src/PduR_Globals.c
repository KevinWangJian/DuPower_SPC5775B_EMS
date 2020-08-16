
/* Provide definition of PduR variables that are independent of PDUR_DEV_ERROR_DETECT and
 * which always need to be linked into any application using the Pdu Router
 */

#include "PduR_Prv.h"
/* ------------------------------------------------------------------------ */
/* Begin a set of variable definitions */

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

P2CONST(PduR_PBConfigType, PDUR_VAR, PDUR_APPL_CONST) PduR_Base;

/* ------------------------------------------------------------------------ */
/* End section for variable */

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin a set of variable definitions */

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

VAR(PduR_StateType, PDUR_VAR) PduR_State;

/* ------------------------------------------------------------------------ */
/* End section for variable */

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"


#if (PDUR_DSM_REINT_SUPPORT != STD_OFF)

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

VAR(PduR_DsmReInitType, PDUR_VAR) PduR_DsmReInitStruct;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
#endif

