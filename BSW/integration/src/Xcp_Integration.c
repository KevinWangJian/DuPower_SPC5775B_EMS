/*
 * Xcp_Integration.c
 *
 *  Created on: May 20, 2018
 *      Author: CIX2SGH
 */

/*******************************************************************************
* Include Files
*******************************************************************************/
#include "Xcp_Integration.h"
#include "Xcp_Priv.h"

/*******************************************************************************
* Macro Definitions
*******************************************************************************/
static uint32 Xcp_SWC_Timestamp_1ms;

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
/*******************************************************************************
* Function Definitions
*******************************************************************************/
/*******************************************************************************
  Function name     :   Xcp_UpdateTimeStampe

  Description       :
  Parameter         :   none
  Return value      :   none

*******************************************************************************/
void Xcp_UpdateTimeStamp(void)
{
    Xcp_SWC_Timestamp_1ms++;
}

/*******************************************************************************
  Function name     :   Xcp_UpdateTimeStampe

  Description       :
  Parameter         :   none
  Return value      :   uint32

*******************************************************************************/
uint32 Xcp_GetTimeStamp(void)
{
    return Xcp_SWC_Timestamp_1ms;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
