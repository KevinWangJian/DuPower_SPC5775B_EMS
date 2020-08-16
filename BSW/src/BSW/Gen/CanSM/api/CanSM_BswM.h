
#ifndef  CANSM_BSWM_H
#define  CANSM_BSWM_H



/***************************************************************************************************
* Includes
***************************************************************************************************
*/
#include "CanSM_Cfg.h"
/*
 ********************************************************************************
**                     Enumeration
*******************************************************************************
*/

/*CAN specific communication modes / states notified to the BswM module*/
typedef enum
{
CANSM_BSWM_NO_COMMUNICATION = 0,
CANSM_BSWM_SILENT_COMMUNICATION,
CANSM_BSWM_FULL_COMMUNICATION,
CANSM_BSWM_BUS_OFF,
CANSM_BSWM_CHANGE_BAUDRATE

}CanSM_BswMCurrentStateType;



#endif /*CANSM_BSWM_H*/






