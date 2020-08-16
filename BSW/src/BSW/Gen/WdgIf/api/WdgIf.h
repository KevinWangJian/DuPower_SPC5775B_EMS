

#ifndef WDGIF_H
#define WDGIF_H

/*
***************************************************************************************************
* Defines
***************************************************************************************************
*/

#define WDGIF_AR_RELEASE_MAJOR_VERSION          (4)
#define WDGIF_AR_RELEASE_MINOR_VERSION          (2)
#define WDGIF_AR_RELEASE_REVISION_VERSION       (2)

#define WDGIF_SW_MAJOR_VERSION                  (3)
#define WDGIF_SW_MINOR_VERSION                  (0)
#define WDGIF_SW_PATCH_VERSION                  (0)

#define WDGIF_MODULE_ID                         (43)
#define WDGIF_VENDOR_ID                         (6)
#define WDGIF_INSTANCE_ID                       (1)

/*TRACE[WDGIF001] Implementation of API for WdgIf*/
/*TRACE[WDGIF052] No global variables in WdgIf*/
/*TRACE[WDGIF053] No variables for debugging in WdgIf*/
/*TRACE[WDGIF054] No variables for sizeof*/
/*TRACE[WDGIF055] No Variables available for
 *debugging hence none in BSMD file?*/
/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/
/*TRACE[WDGIF002] Implementation of HeaderFile structure as per WdgIf */
/*TRACE[WDGIF041] Use Standard types */
#include "Std_Types.h"
/*TRACE[WDGIF005] Perform Version Checks*/
#if (!defined(STD_TYPES_AR_RELEASE_MAJOR_VERSION) || (STD_TYPES_AR_RELEASE_MAJOR_VERSION != 4))
//#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(STD_TYPES_AR_RELEASE_MINOR_VERSION) || (STD_TYPES_AR_RELEASE_MINOR_VERSION != 2))
//#error 揂UTOSAR minor version undefined or mismatched�
#endif
/*TRACE[WDGIF049] Implementation that WdgIF shall include WdgIf_Types.h*/

/*TRACE[WDGIF050] Implementation that WdgIF shall include WdgIf_Cfg.h*/
#include "WdgIf_Cfg.h"


/*
***************************************************************************************************
* Defines
***************************************************************************************************
*/
/*TRACE[WDGIF030] Dev Error of type uint8*/
#define WDGIF_SETMODE_SERVICEID                 ((uint8)0x01)
#define WDGIF_TRIGGER_SERVICEID                 ((uint8)0x02)
#define WDGIF_GETVERSIONINFO_SERVICEID          ((uint8)0x03)

/*TRACE[WDGIF006] Error and Exception Detectable*/
/*TRACE[WDGIF009] Only the listed error should be reported*/
#define WDGIF_E_PARAM_DEVICE                    (1)
#define WDGIF_E_INV_POINTER                     (2)


#define WDGIF_E_MODULE_ID                       (WDGIF_MODULE_ID)


#define WDGIF_PRV_C_ZERO                         (0)
#define WDGIF_PRV_C_ONE                          (1)
#define WDGIF_PRV_C_TWO                          (2)

#endif /* WDGIF_H */
